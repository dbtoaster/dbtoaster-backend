package ddbt.tpcc.loadtest

import java.sql.Timestamp
import java.sql.SQLException
import java.util.Calendar
import java.util.Date
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import ddbt.tpcc.itx.IDelivery
import Delivery._
import TpccConstants._

object Delivery {

  private val logger = LoggerFactory.getLogger(classOf[Delivery])

  private val DEBUG = logger.isDebugEnabled

  private val TRACE = logger.isTraceEnabled

  private val SHOW_OUTPUT = TpccConstants.SHOW_OUTPUT
}

class Delivery(var pStmts: TpccStatements) extends IDelivery {

  override def deliveryTx(currentTimeStamp:Date, w_id_arg: Int, o_carrier_id_arg: Int): Int = {
    val orderIDs = new Array[Int](10)
    try {
      pStmts.setAutoCommit(false)
      if (DEBUG) logger.debug("Transaction:	Delivery")
      val w_id = w_id_arg
      val o_carrier_id = o_carrier_id_arg
      var c_id = 0
      var no_o_id = 0
      var ol_total = 0f
      var d_id = 1
      while (d_id <= DIST_PER_WARE) {
        if (TRACE) logger.trace("SELECT COALESCE(MIN(no_o_id),0) FROM new_orders WHERE no_d_id = " + 
          d_id + 
          " AND no_w_id = " + 
          w_id)
        try {
          pStmts.getStatement(25).setInt(1, d_id)
          pStmts.getStatement(25).setInt(2, w_id)
          val rs = pStmts.getStatement(25).executeQuery()
          if (rs.next()) {
            no_o_id = rs.getInt(1)
          }
          rs.close()
        } catch {
          case e: SQLException => {
            logger.error("SELECT COALESCE(MIN(no_o_id),0) FROM new_orders WHERE no_d_id = " + 
              d_id + 
              " AND no_w_id = " + 
              w_id, e)
            throw new Exception("Delivery Select transaction error", e)
          }
        }
        orderIDs(d_id - 1) = no_o_id
        if (no_o_id == 0) {
          //continue
        } else {
            if (DEBUG) logger.debug("No_o_id did not equal 0 -> " + no_o_id)

            if (TRACE) logger.trace("DELETE FROM new_orders WHERE no_o_id = " + no_o_id + 
              " AND no_d_id = " + 
              d_id + 
              " AND no_w_id = " + 
              w_id)
            try {
              pStmts.getStatement(26).setInt(1, no_o_id)
              pStmts.getStatement(26).setInt(2, d_id)
              pStmts.getStatement(26).setInt(3, w_id)
              pStmts.getStatement(26).executeUpdate()
            } catch {
              case e: SQLException => {
                logger.error("DELETE FROM new_orders WHERE no_o_id = " + no_o_id + 
                  " AND no_d_id = " + 
                  d_id + 
                  " AND no_w_id = " + 
                  w_id, e)
                throw new Exception(" Delivery Delete transaction error", e)
              }
            }
            if (TRACE) logger.trace("SELECT o_c_id FROM orders WHERE o_id = " + no_o_id + 
              " AND o_d_id = " + 
              d_id + 
              " AND o_w_id = " + 
              w_id)
            try {
              pStmts.getStatement(27).setInt(1, no_o_id)
              pStmts.getStatement(27).setInt(2, d_id)
              pStmts.getStatement(27).setInt(3, w_id)
              val rs = pStmts.getStatement(27).executeQuery()
              if (rs.next()) {
                c_id = rs.getInt(1)
              }
              rs.close()
            } catch {
              case e: SQLException => {
                logger.error("SELECT o_c_id FROM orders WHERE o_id = " + no_o_id + 
                  " AND o_d_id = " + 
                  d_id + 
                  " AND o_w_id = " + 
                  w_id, e)
                throw new Exception(" Delivery Select transaction error", e)
              }
            }
            if (TRACE) logger.trace("UPDATE orders SET o_carrier_id = " + o_carrier_id + " WHERE o_id = " + 
              no_o_id + 
              " AND o_d_id = " + 
              d_id + 
              " AND o_w_id = " + 
              w_id)
            try {
              pStmts.getStatement(28).setInt(1, o_carrier_id)
              pStmts.getStatement(28).setInt(2, no_o_id)
              pStmts.getStatement(28).setInt(3, d_id)
              pStmts.getStatement(28).setInt(4, w_id)
              pStmts.getStatement(28).executeUpdate()
            } catch {
              case e: SQLException => {
                logger.error("UPDATE orders SET o_carrier_id = " + o_carrier_id + " WHERE o_id = " + 
                  no_o_id + 
                  " AND o_d_id = " + 
                  d_id + 
                  " AND o_w_id = " + 
                  w_id, e)
                throw new Exception("Delivery Update transcation error", e)
              }
            }
            if (TRACE) logger.trace("UPDATE order_line SET ol_delivery_d = " + currentTimeStamp.toString + 
              " WHERE ol_o_id = " + 
              no_o_id + 
              " AND ol_d_id = " + 
              d_id + 
              " AND ol_w_id = " + 
              w_id)
            try {
              pStmts.getStatement(29).setString(1, currentTimeStamp.toString)
              pStmts.getStatement(29).setInt(2, no_o_id)
              pStmts.getStatement(29).setInt(3, d_id)
              pStmts.getStatement(29).setInt(4, w_id)
              pStmts.getStatement(29).executeUpdate()
            } catch {
              case e: SQLException => {
                logger.error("UPDATE order_line SET ol_delivery_d = " + currentTimeStamp.toString + 
                  " WHERE ol_o_id = " + 
                  no_o_id + 
                  " AND ol_d_id = " + 
                  d_id + 
                  " AND ol_w_id = " + 
                  w_id, e)
                throw new Exception("Delivery Update transaction error", e)
              }
            }
            if (TRACE) logger.trace("SELECT SUM(ol_amount) FROM order_line WHERE ol_o_id = " + 
              no_o_id + 
              " AND ol_d_id = " + 
              d_id + 
              " AND ol_w_id = " + 
              w_id)
            try {
              pStmts.getStatement(30).setInt(1, no_o_id)
              pStmts.getStatement(30).setInt(2, d_id)
              pStmts.getStatement(30).setInt(3, w_id)
              val rs = pStmts.getStatement(30).executeQuery()
              if (rs.next()) {
                ol_total = rs.getFloat(1)
              }
              rs.close()
            } catch {
              case e: SQLException => {
                logger.error("SELECT SUM(ol_amount) FROM order_line WHERE ol_o_id = " + 
                  no_o_id + 
                  " AND ol_d_id = " + 
                  d_id + 
                  " AND ol_w_id = " + 
                  w_id, e)
                throw new Exception("Delivery Select transaction error", e)
              }
            }
            if (TRACE) logger.trace("UPDATE customer SET c_balance = c_balance + " + ol_total + 
              ", c_delivery_cnt = c_delivery_cnt + 1 WHERE c_id = " + 
              c_id + 
              " AND c_d_id = " + 
              d_id + 
              " AND c_w_id = " + 
              w_id)
            try {
              pStmts.getStatement(31).setFloat(1, ol_total)
              pStmts.getStatement(31).setInt(2, c_id)
              pStmts.getStatement(31).setInt(3, d_id)
              pStmts.getStatement(31).setInt(4, w_id)
              pStmts.getStatement(31).executeUpdate()
            } catch {
              case e: SQLException => {
                logger.error("UPDATE customer SET c_balance = c_balance + " + ol_total + 
                  ", c_delivery_cnt = c_delivery_cnt + 1 WHERE c_id = " + 
                  c_id + 
                  " AND c_d_id = " + 
                  d_id + 
                  " AND c_w_id = " + 
                  w_id, e)
                throw new Exception("Delivery Update transaction error", e)
              }
            }
        }
        d_id += 1
      }
      pStmts.commit()

      val output: StringBuilder = new StringBuilder
      output.append("\n+############################ DELIVERY ###########################+\n")
      output.append(" Date: ").append(currentTimeStamp)
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
      output.append("+#################################################################+\n\n")
      if(Delivery.SHOW_OUTPUT) logger.info(output.toString)

      1
    } catch {
      case e: Exception => try {
        pStmts.rollback()
        0
      } catch {
        case th: Throwable => throw new RuntimeException("Delivery error", th)
      } finally {
        logger.error("Delivery error", e)
      }
    }
  }
}
