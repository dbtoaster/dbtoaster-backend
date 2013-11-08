package ddbt.tpcc.tx3
import java.io._
import scala.collection.mutable._
import java.util.Date
import ddbt.tpcc.itx._
import org.slf4j.LoggerFactory
import Delivery._

object Delivery {

  private val logger = LoggerFactory.getLogger(classOf[Delivery])

  private val DEBUG = logger.isDebugEnabled

  private val TRACE = logger.isTraceEnabled

  private val SHOW_OUTPUT = ddbt.tpcc.loadtest.TpccConstants.SHOW_OUTPUT
}

/**
 * Delivery Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
class Delivery extends InMemoryTxImpl with IDeliveryInMem {

  //Tables
  //val newOrderTbl = new HashSet[(Int,Int,Int)]

  //Partial Tables (containing all rows, but not all columns)
  //removed columns are commented out
  //val orderPartialTbl = new HashMap[(Int,Int,Int),(Int/*,Date*/,Option[Int]/*,Int,Boolean*/)]
  //only the slice over first three key parts is used
  //val orderLinePartialTbl = new HashMap[(Int,Int,Int,Int),(/*Int,Int,*/Option[Date]/*,Int*/,Float/*,String*/)]
  //val customerPartialTbl = new HashMap[(Int,Int,Int),(/*String,String,String,String,String,String,String,String,String,Date,String,Float,Float,*/Float/*,Float,Int*/,Int/*,String*/)]
  /**
   * @param w_id is warehouse id
   * @param o_carrier_id is the carrier id for this warehouse
   *
   * Table interactions:
   *   - [NewOrder: RW] where R in
   *      + findFirstNewOrder
   *     and W in
   *      + deleteNewOrder
   *   - [Order: RW] where R in
   *      + updateOrderCarrierAndFindCID
   *   - [OrderLine: RW] where R in
   *      + findOrderLineTotalAmount
   *     and W in
   *      + updateOrderLineDeliveryDate
   *   - [Customer: W] in
   *      + updateCustomerBalance
   */
  override def deliveryTx(datetime:Date, w_id: Int, o_carrier_id: Int): Int = {
    try {
      val DIST_PER_WAREHOUSE = 10
      val orderIDs = new Array[Int](10)
      var d_id = 1
      while (d_id <= DIST_PER_WAREHOUSE) {
        DeliveryTxOps.findFirstNewOrder(w_id,d_id) match {
          case Some(no_o_id) => {
            orderIDs(d_id - 1) = no_o_id
            DeliveryTxOps.deleteNewOrder(w_id,d_id,no_o_id)
            var c_id = 0
            DeliveryTxOps.updateOrderCarrierAndFindCID(w_id,d_id,no_o_id,(cv => { c_id = cv._1; ((cv._1,cv._2,Some(o_carrier_id),cv._4,cv._5)) }))
            val ol_total = DeliveryTxOps.updateOrderLineDeliveryDateAndFindOrderLineTotalAmount(w_id,d_id,no_o_id,datetime)
            DeliveryTxOps.updateCustomerBalance(w_id,d_id,c_id,ol_total)
          }
          case None => orderIDs(d_id - 1) = 0
        }
        d_id += 1
      }

      val output: StringBuilder = new StringBuilder
      output.append("\n+---------------------------- DELIVERY ---------------------------+\n")
      output.append(" Date: ").append(datetime)
      output.append("\n\n Warehouse: ").append(w_id)
      output.append("\n Carrier:   ").append(o_carrier_id)
      output.append("\n\n Delivered Orders\n")
      var skippedDeliveries: Int = 0
      var i: Int = 1
      while (i <= 10) {
        if (orderIDs(i - 1) >= 0) {
          output.append("  District ")
          output.append(if (i < 10) " " else "")
          output.append(i)
          output.append(": Order number ")
          output.append(orderIDs(i - 1))
          output.append(" was delivered.\n")
        }
        else {
          output.append("  District ")
          output.append(if (i < 10) " " else "")
          output.append(i)
          output.append(": No orders to be delivered.\n")
          skippedDeliveries += 1
        }
        i += 1
      }
      output.append("+-----------------------------------------------------------------+\n\n")
      if(SHOW_OUTPUT) logger.info(output.toString)
      // skippedDeliveries
      1
    } catch {
      case e: Throwable => {
        logger.error("An error occurred in handling Delivery transaction for warehouse=%d, carrier=%d".format(w_id,o_carrier_id))
        0
      }
    }
  }

  object DeliveryTxOps {
    def findFirstNewOrder(no_w_id_input:Int, no_d_id_input:Int):Option[Int] = {
      var first_no_o_id:Option[Int] = None
      SharedData.newOrderTbl.slice(0, (no_d_id_input, no_w_id_input)).foreach { case ((no_o_id,_,_),_) =>
        if(no_o_id <= first_no_o_id.getOrElse(Integer.MAX_VALUE)) {
          first_no_o_id = Some(no_o_id)
        }
      }
      first_no_o_id
    }

    def deleteNewOrder(no_w_id:Int, no_d_id:Int, no_o_id:Int) = {
      SharedData.onDelete_NewOrder(no_o_id,no_d_id,no_w_id)
    }

    def findOrderCID(o_w_id:Int, o_d_id:Int, o_id:Int) = {
      SharedData.orderTbl((o_id,o_d_id,o_w_id))._1
    }

    def updateOrderCarrierAndFindCID(o_w_id:Int, o_d_id:Int, o_id:Int, updateFunc:((Int, Date, Option[Int], Int, Boolean)) => (Int, Date, Option[Int], Int, Boolean)) {
      SharedData.onUpdate_Order_byFunc(o_id,o_d_id,o_w_id, updateFunc)
    }

    def updateOrderLineDeliveryDateAndFindOrderLineTotalAmount(ol_w_id_input:Int, ol_d_id_input:Int, ol_o_id_input:Int, ol_delivery_d_input:Date):Float = {
      var ol_total = 0f
      SharedData.orderLineTbl.slice(0, (ol_o_id_input, ol_d_id_input, ol_w_id_input)).foreachEntry { cv => 
        val k = cv.key
        k.value = k.value.copy(_3 = Some(ol_delivery_d_input))
        ol_total += k.value._5
      }
      ol_total
    }

    def updateCustomerBalance(c_w_id:Int, c_d_id:Int, c_id:Int, ol_total:Float) = {
      val (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data) = SharedData.customerTbl((c_id,c_d_id,c_w_id))
      SharedData.onUpdateCustomer(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance+ol_total,c_ytd_payment,c_payment_cnt,c_delivery_cnt+1,c_data)
    }
  }
}

