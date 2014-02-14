package ddbt.tpcc.loadtest

import java.io.PrintWriter
import java.sql.Connection
import java.sql.SQLException
import java.util.Arrays
import java.util.Calendar
import java.util.Date
import java.sql.Timestamp
import java.util.concurrent._
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import ddbt.tpcc.itx._
import Driver._
import TpccConstants._

object Driver {

  private val logger = LoggerFactory.getLogger(classOf[Driver])

  private val DEBUG = logger.isDebugEnabled

  /**
   * For debug use only.
   */
  private val DETECT_LOCK_WAIT_TIMEOUTS = false

  /**
   * Can be disabled for debug use only.
   */
  private val ALLOW_MULTI_WAREHOUSE_TX = true
}

class Driver(var conn: java.sql.Connection, 
    fetchSize: Int, 
    val success: Array[Int], 
    val late: Array[Int], 
    val retry: Array[Int], 
    val failure: Array[Int], 
    val success2: Array[Array[Int]], 
    val late2: Array[Array[Int]], 
    val retry2: Array[Array[Int]], 
    val failure2: Array[Array[Int]],
    val newOrder: INewOrder,
    val payment: IPayment,
    val orderStat: IOrderStatus,
    val slev: IStockLevel,
    val delivery: IDelivery) {

  var num_ware: Int = _

  var num_conn: Int = _

  var num_node: Int = _

  var max_rt: Array[Float] = new Array[Float](TRANSACTION_COUNT)
  for (i <- 0 until TRANSACTION_COUNT) {
    max_rt(i) = 0f
  }

  private val MAX_RETRY = 2000

  private val RTIME_NEWORD = 5 * 1000

  private val RTIME_PAYMENT = 5 * 1000

  private val RTIME_ORDSTAT = 5 * 1000

  private val RTIME_DELIVERY = 5 * 1000

  private val RTIME_SLEV = 20 * 1000

  private val exec = Executors.newSingleThreadExecutor()

  def runTransaction(t_num: Int, numWare: Int, numConn: Int, loopConditionChecker: (Int => Boolean)): Int = {
    num_ware = numWare
    num_conn = numConn
    var count = 0
    var sequence = Util.seqGet()
    while (loopConditionChecker(count)) {
      try {
        if (DEBUG) logger.debug("BEFORE runTransaction: sequence: " + sequence)
        if (DETECT_LOCK_WAIT_TIMEOUTS) {
          val _sequence = sequence
          val t = new FutureTask[Any](new Callable[Any]() {

            def call(): AnyRef = {
              doNextTransaction(t_num, _sequence)
              return null
            }
          })
          exec.execute(t)
          try {
            t.get(15, TimeUnit.SECONDS)
          } catch {
            case e: InterruptedException => {
              logger.error("InterruptedException", e)
              Tpcc.activate_transaction = 0
            }
            case e: ExecutionException => {
              logger.error("Unhandled exception", e)
              Tpcc.activate_transaction = 0
            }
            case e: TimeoutException => {
              logger.error("Detected Lock Wait", e)
              Tpcc.activate_transaction = 0
            }
          }
        } else {
          doNextTransaction(t_num, sequence)
        }
        count += 1
      } catch {
        case th: Throwable => {
          logger.error("FAILED", th)
          Tpcc.activate_transaction = 0
          try {
            conn.rollback()
          } catch {
            case e: SQLException => logger.error("", e)
          }
          return -1
        }
      } finally {
        if (DEBUG) logger.debug("AFTER runTransaction: sequence: " + sequence)
      }
      sequence = Util.seqGet()
    }
    logger.debug("Driver terminated after {} transactions", count)
    (0)
  }

  private def doNextTransaction(t_num: Int, sequence: Int) {
    if (sequence == 0) {
      doNeword(t_num)
    } else if (sequence == 1) {
      doPayment(t_num)
    } else if (sequence == 2) {
      doOrdstat(t_num)
    } else if (sequence == 3) {
      doDelivery(t_num)
    } else if (sequence == 4) {
      doSlev(t_num)
    } else {
      throw new IllegalStateException("Error - Unknown sequence")
    }
  }

  private def doNeword(t_num: Int): Int = {
    var c_num = 0
    var i = 0
    var ret = 0
    var rt = 0f
    var beginTime = 0L
    var endTime = 0L
    var w_id = 0
    var d_id = 0
    var c_id = 0
    var ol_cnt = 0
    var all_local = 1
    val notfound = MAXITEMS + 1
    var rbk = 0
    val itemid = Array.ofDim[Int](MAX_NUM_ITEMS)
    val supware = Array.ofDim[Int](MAX_NUM_ITEMS)
    val qty = Array.ofDim[Int](MAX_NUM_ITEMS)
    var price = Array.ofDim[Float](MAX_NUM_ITEMS)
    var amt = Array.ofDim[Float](MAX_NUM_ITEMS)
    var iname = Array.ofDim[String](MAX_NUM_ITEMS)
    var bg = Array.ofDim[Char](MAX_NUM_ITEMS)
    var stock = Array.ofDim[Int](MAX_NUM_ITEMS)

    if (num_node == 0) {
      w_id = Util.randomNumber(1, num_ware)
    } else {
      c_num = ((num_node * t_num) / num_conn)
      w_id = Util.randomNumber(1 + (num_ware * c_num) / num_node, (num_ware * (c_num + 1)) / num_node)
    }
    if (w_id < 1) {
      throw new IllegalStateException("Invalid warehouse ID " + w_id)
    }
    d_id = Util.randomNumber(1, DIST_PER_WARE)
    c_id = Util.nuRand(1023, 1, CUST_PER_DIST)
    ol_cnt = Util.randomNumber(5, 15)
    rbk = Util.randomNumber(1, 100)
    i = 0
    while (i < ol_cnt) {
      itemid(i) = Util.nuRand(8191, 1, MAXITEMS)
      if ((i == ol_cnt - 1) && (rbk == 1)) {
        itemid(i) = notfound
      }
      if (ALLOW_MULTI_WAREHOUSE_TX) {
        if (Util.randomNumber(1, 100) != 1) {
          supware(i) = w_id
        } else {
          supware(i) = otherWare(w_id)
          all_local = 0
        }
      } else {
        supware(i) = w_id
      }
      qty(i) = Util.randomNumber(1, 10)
      i += 1
    }
    beginTime = System.currentTimeMillis()
    i = 0
    while (i < MAX_RETRY) {
      if (DEBUG) logger.debug("t_num: " + t_num + " w_id: " + w_id + " c_id: " + c_id + 
        " ol_cnt: " + 
        ol_cnt + 
        " all_local: " + 
        all_local + 
        " qty: " + 
        Arrays.toString(qty))

      val time = new java.sql.Timestamp(System.currentTimeMillis())
      ret = newOrder.newOrderTx(time, t_num, w_id, d_id, c_id, ol_cnt, all_local, itemid, supware, qty, price, iname, stock, bg, amt)
      endTime = System.currentTimeMillis()
      if (ret == 1) {
        rt = (endTime - beginTime).toFloat
        if (DEBUG) logger.debug("BEFORE rt value: " + rt + " max_rt[0] value: " + max_rt(0))
        if (rt > max_rt(0)) max_rt(0) = rt
        if (DEBUG) logger.debug("AFTER rt value: " + rt + " max_rt[0] value: " + max_rt(0))
        RtHist.histInc(0, rt)
        if (Tpcc.counting_on) {
          if (DEBUG) logger.debug(" rt: " + rt + " RTIME_NEWORD " + RTIME_NEWORD)
          if (rt < RTIME_NEWORD) {
            if (DEBUG) logger.debug("Rt < RTIME_NEWORD")
            success(0) += 1
            success2(0)(t_num) += 1
          } else {
            if (DEBUG) logger.debug("Rt > RTIME_NEWORD")
            late(0) += 1
            late2(0)(t_num) += 1
          }
        }
        return (1)
      } else {
        if (Tpcc.counting_on) {
          retry(0) += 1
          retry2(0)(t_num) += 1
        }
      }
      i += 1
    }
    if (Tpcc.counting_on) {
      retry(0) -= 1
      retry2(0)(t_num) -= 1
      failure(0) += 1
      failure2(0)(t_num) += 1
    }
    (0)
  }

  private def otherWare(home_ware: Int): Int = {
    var tmp: Int = 0
    if (num_ware == 1) return home_ware
    while ({(tmp = Util.randomNumber(1, num_ware)); tmp} == home_ware) {
      // NOTHING
    }
    tmp
  }

  private def doPayment(t_num: Int): Int = {
    var c_num = 0
    var byname = 0
    var i = 0
    var ret = 0
    var rt = 0f
    var beginTime = 0L
    var endTime = 0L
    var w_id = 0
    var d_id = 0
    var c_w_id = 0
    var c_d_id = 0
    var c_id = 0
    var h_amount = 0
    var c_last: String = null
    if (num_node == 0) {
      w_id = Util.randomNumber(1, num_ware)
    } else {
      c_num = ((num_node * t_num) / num_conn)
      w_id = Util.randomNumber(1 + (num_ware * c_num) / num_node, (num_ware * (c_num + 1)) / num_node)
    }
    d_id = Util.randomNumber(1, DIST_PER_WARE)
    c_id = Util.nuRand(1023, 1, CUST_PER_DIST)
    c_last = Util.lastName(Util.nuRand(255, 0, 999))
    h_amount = Util.randomNumber(1, 5000)
    byname = if (Util.randomNumber(1, 100) <= 60) 1 else 0
    if (ALLOW_MULTI_WAREHOUSE_TX) {
      if (Util.randomNumber(1, 100) <= 85) {
        c_w_id = w_id
        c_d_id = d_id
      } else {
        c_w_id = otherWare(w_id)
        c_d_id = Util.randomNumber(1, DIST_PER_WARE)
      }
    } else {
      c_w_id = w_id
      c_d_id = d_id
    }
    beginTime = System.currentTimeMillis()
    i = 0
    while (i < MAX_RETRY) {
      val currentTimeStamp = new Timestamp(System.currentTimeMillis())
      ret = payment.paymentTx(currentTimeStamp, t_num, w_id, d_id, byname, c_w_id, c_d_id, c_id, c_last, h_amount)
      endTime = System.currentTimeMillis()
      if (ret >= 1) {
        rt = (endTime - beginTime).toFloat
        if (rt > max_rt(1)) max_rt(1) = rt
        RtHist.histInc(1, rt)
        if (Tpcc.counting_on) {
          if (rt < RTIME_PAYMENT) {
            success(1) += 1
            success2(1)(t_num) += 1
          } else {
            late(1) += 1
            late2(1)(t_num) += 1
          }
        }
        return (1)
      } else {
        if (Tpcc.counting_on) {
          retry(1) += 1
          retry2(1)(t_num) += 1
        }
      }
      i += 1
    }
    if (Tpcc.counting_on) {
      retry(1) -= 1
      retry2(1)(t_num) -= 1
      failure(1) += 1
      failure2(1)(t_num) += 1
    }
    (0)
  }

  private def doOrdstat(t_num: Int): Int = {
    var c_num = 0
    var byname = 0
    var i = 0
    var ret = 0
    var rt = 0f
    var beginTime = 0L
    var endTime = 0L
    var w_id = 0
    var d_id = 0
    var c_id = 0
    var c_last: String = null
    if (num_node == 0) {
      w_id = Util.randomNumber(1, num_ware)
    } else {
      c_num = ((num_node * t_num) / num_conn)
      w_id = Util.randomNumber(1 + (num_ware * c_num) / num_node, (num_ware * (c_num + 1)) / num_node)
    }
    d_id = Util.randomNumber(1, DIST_PER_WARE)
    c_id = Util.nuRand(1023, 1, CUST_PER_DIST)
    c_last = Util.lastName(Util.nuRand(255, 0, 999))
    byname = if (Util.randomNumber(1, 100) <= 60) 1 else 0
    beginTime = System.currentTimeMillis()
    i = 0
    while (i < MAX_RETRY) {
      val datetime = new java.util.Date()
      ret = orderStat.orderStatusTx(datetime, t_num, w_id, d_id, byname, c_id, c_last)
      endTime = System.currentTimeMillis()
      if (ret >= 1) {
        rt = (endTime - beginTime).toFloat
        if (rt > max_rt(2)) max_rt(2) = rt
        RtHist.histInc(2, rt)
        if (Tpcc.counting_on) {
          if (rt < RTIME_ORDSTAT) {
            success(2) += 1
            success2(2)(t_num) += 1
          } else {
            late(2) += 1
            late2(2)(t_num) += 1
          }
        }
        return (1)
      } else {
        if (Tpcc.counting_on) {
          retry(2) += 1
          retry2(2)(t_num) += 1
        }
      }
      i += 1
    }
    if (Tpcc.counting_on) {
      retry(2) -= 1
      retry2(2)(t_num) -= 1
      failure(2) += 1
      failure2(2)(t_num) += 1
    }
    (0)
  }

  private def doDelivery(t_num: Int): Int = {
    var c_num = 0
    var i = 0
    var ret = 0
    var rt = 0f
    var beginTime = 0L
    var endTime = 0L
    var w_id = 0
    var o_carrier_id = 0
    if (num_node == 0) {
      w_id = Util.randomNumber(1, num_ware)
    } else {
      c_num = ((num_node * t_num) / num_conn)
      w_id = Util.randomNumber(1 + (num_ware * c_num) / num_node, (num_ware * (c_num + 1)) / num_node)
    }
    o_carrier_id = Util.randomNumber(1, 10)
    beginTime = System.currentTimeMillis()
    i = 0
    while (i < MAX_RETRY) {
      val calendar = Calendar.getInstance
      val now = calendar.getTime
      val currentTimeStamp = new Timestamp(now.getTime)
      ret = delivery.deliveryTx(currentTimeStamp, w_id, o_carrier_id)
      endTime = System.currentTimeMillis()
      if (ret >= 1) {
        rt = (endTime - beginTime).toFloat
        if (rt > max_rt(3)) max_rt(3) = rt
        RtHist.histInc(3, rt)
        if (Tpcc.counting_on) {
          if (rt < RTIME_DELIVERY) {
            success(3) += 1
            success2(3)(t_num) += 1
          } else {
            late(3) += 1
            late2(3)(t_num) += 1
          }
        }
        return (1)
      } else {
        if (Tpcc.counting_on) {
          retry(3) += 1
          retry2(3)(t_num) += 1
        }
      }
      i += 1
    }
    if (Tpcc.counting_on) {
      retry(3) -= 1
      retry2(3)(t_num) -= 1
      failure(3) += 1
      failure2(3)(t_num) += 1
    }
    (0)
  }

  private def doSlev(t_num: Int): Int = {
    var c_num = 0
    var i = 0
    var ret = 0
    var rt = 0f
    var beginTime = 0L
    var endTime = 0L
    var w_id = 0
    var d_id = 0
    var level = 0
    if (num_node == 0) {
      w_id = Util.randomNumber(1, num_ware)
    } else {
      c_num = ((num_node * t_num) / num_conn)
      w_id = Util.randomNumber(1 + (num_ware * c_num) / num_node, (num_ware * (c_num + 1)) / num_node)
    }
    d_id = Util.randomNumber(1, DIST_PER_WARE)
    level = Util.randomNumber(10, 20)
    beginTime = System.currentTimeMillis()
    i = 0
    while (i < MAX_RETRY) {
      ret = slev.stockLevelTx(t_num, w_id, d_id, level)
      endTime = System.currentTimeMillis()
      if (ret >= 1) {
        rt = (endTime - beginTime).toFloat
        if (rt > max_rt(4)) max_rt(4) = rt
        RtHist.histInc(4, rt)
        if (Tpcc.counting_on) {
          if (rt < RTIME_SLEV) {
            success(4) += 1
            success2(4)(t_num) += 1
          } else {
            late(4) += 1
            late2(4)(t_num) += 1
          }
        }
        return (1)
      } else {
        if (Tpcc.counting_on) {
          retry(4) += 1
          retry2(4)(t_num) += 1
        }
      }
      i += 1
    }
    if (Tpcc.counting_on) {
      retry(4) -= 1
      retry2(4)(t_num) -= 1
      failure(4) += 1
      failure2(4)(t_num) += 1
    }
    (0)
  }
}
