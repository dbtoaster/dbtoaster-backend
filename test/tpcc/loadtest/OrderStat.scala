package ddbt.tpcc.loadtest

import java.sql.Connection
import java.sql.ResultSet
import java.sql.SQLException
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import OrderStat._

object OrderStat {

  private val logger = LoggerFactory.getLogger(classOf[Driver])

  private val DEBUG = logger.isDebugEnabled

  private val TRACE = logger.isTraceEnabled
}

class OrderStat(var pStmts: TpccStatements) extends TpccConstants {

  def ordStat(t_num: Int, 
      w_id_arg: Int, 
      d_id_arg: Int, 
      byname: Int, 
      c_id_arg: Int, 
      c_last_arg: String): Int = {
    ddbt.tpcc.tx.OrderStatus.orderStatusTx(w_id_arg, d_id_arg, c_id_arg, c_last_arg, byname > 0)
    try {
      pStmts.setAutoCommit(false)
      if (DEBUG) logger.debug("Transaction: ORDER STAT")
      val w_id = w_id_arg
      val d_id = d_id_arg
      val c_id = c_id_arg
      val c_d_id = d_id
      val c_w_id = w_id
      var c_first: String = null
      var c_middle: String = null
      var c_last: String = null
      var c_balance = 0f
      var o_id = 0
      var o_entry_d: String = null
      var o_carrier_id = 0
      var ol_i_id = 0
      var ol_supply_w_id = 0
      var ol_quantity = 0
      var ol_amount = 0f
      var ol_delivery_d: String = null
      var namecnt = 0
      var n = 0
      if (byname > 0) {
        c_last = c_last_arg
        try {
          pStmts.getStatement(20).setInt(1, c_w_id)
          pStmts.getStatement(20).setInt(2, c_d_id)
          pStmts.getStatement(20).setString(3, c_last)
          if (TRACE) logger.trace("SELECT count(c_id) FROM customer WHERE c_w_id = " + c_w_id + 
            " AND c_d_id = " + 
            c_d_id + 
            " AND c_last = " + 
            c_last)
          val rs = pStmts.getStatement(20).executeQuery()
          if (rs.next()) {
            namecnt = rs.getInt(1)
          }
          rs.close()
        } catch {
          case e: SQLException => {
            logger.error("SELECT count(c_id) FROM customer WHERE c_w_id = " + c_w_id + 
              " AND c_d_id = " + 
              c_d_id + 
              " AND c_last = " + 
              c_last, e)
            throw new Exception("OrderStat Select transaction error", e)
          }
        }
        try {
          pStmts.getStatement(21).setInt(1, c_w_id)
          pStmts.getStatement(21).setInt(2, c_d_id)
          pStmts.getStatement(21).setString(3, c_last)
          if (TRACE) logger.trace("SELECT c_balance, c_first, c_middle, c_last FROM customer WHERE " + 
            "c_w_id = " + 
            c_w_id + 
            " AND c_d_id = " + 
            c_d_id + 
            " AND c_last = " + 
            c_last + 
            " ORDER BY c_first")
          val rs = pStmts.getStatement(21).executeQuery()
          if (namecnt % 2 == 1) {
            namecnt += 1
          }
          n = 0
          while (n < namecnt / 2) {
            rs.next()
            c_balance = rs.getFloat(1)
            c_first = rs.getString(2)
            c_middle = rs.getString(3)
            c_last = rs.getString(4)
            n += 1
            n += 1
          }
          rs.close()
        } catch {
          case e: SQLException => {
            logger.error("SELECT c_balance, c_first, c_middle, c_last FROM customer WHERE " + 
              "c_w_id = " + 
              c_w_id + 
              " AND c_d_id = " + 
              c_d_id + 
              " AND c_last = " + 
              c_last + 
              " ORDER BY c_first", e)
            throw new Exception("OrderStat Select transaction error", e)
          }
        }
      } else {
        try {
          pStmts.getStatement(22).setInt(1, c_w_id)
          pStmts.getStatement(22).setInt(2, c_d_id)
          pStmts.getStatement(22).setInt(3, c_id)
          if (TRACE) logger.trace("SELECT c_balance, c_first, c_middle, c_last FROM customer WHERE " + 
            "c_w_id = " + 
            c_w_id + 
            " AND c_d_id = " + 
            c_d_id + 
            " AND c_id = " + 
            c_id)
          val rs = pStmts.getStatement(22).executeQuery()
          if (rs.next()) {
            c_balance = rs.getFloat(1)
            c_first = rs.getString(2)
            c_middle = rs.getString(3)
            c_last = rs.getString(4)
          }
          rs.close()
        } catch {
          case e: SQLException => {
            logger.error("SELECT c_balance, c_first, c_middle, c_last FROM customer WHERE " + 
              "c_w_id = " + 
              c_w_id + 
              " AND c_d_id = " + 
              c_d_id + 
              " AND c_id = " + 
              c_id, e)
            throw new Exception("OrderStat select transaction error", e)
          }
        }
      }
      try {
        pStmts.getStatement(23).setInt(1, c_w_id)
        pStmts.getStatement(23).setInt(2, c_d_id)
        pStmts.getStatement(23).setInt(3, c_id)
        pStmts.getStatement(23).setInt(4, c_w_id)
        pStmts.getStatement(23).setInt(5, c_d_id)
        pStmts.getStatement(23).setInt(6, c_id)
        if (TRACE) logger.trace("SELECT o_id, o_entry_d, COALESCE(o_carrier_id,0) FROM orders " + 
          "WHERE o_w_id = " + 
          c_w_id + 
          " AND o_d_id = " + 
          c_d_id + 
          " AND o_c_id = " + 
          c_id + 
          " AND o_id = " + 
          "(SELECT MAX(o_id) FROM orders WHERE o_w_id = " + 
          c_w_id + 
          " AND o_d_id = " + 
          c_d_id + 
          " AND o_c_id = " + 
          c_id)
        val rs = pStmts.getStatement(23).executeQuery()
        if (rs.next()) {
          o_id = rs.getInt(1)
          o_entry_d = rs.getString(2)
          o_carrier_id = rs.getInt(3)
        }
        rs.close()
      } catch {
        case e: SQLException => {
          logger.error("SELECT o_id, o_entry_d, COALESCE(o_carrier_id,0) FROM orders " + 
            "WHERE o_w_id = " + 
            c_w_id + 
            " AND o_d_id = " + 
            c_d_id + 
            " AND o_c_id = " + 
            c_id + 
            " AND o_id = " + 
            "(SELECT MAX(o_id) FROM orders WHERE o_w_id = " + 
            c_w_id + 
            " AND o_d_id = " + 
            c_d_id + 
            " AND o_c_id = " + 
            c_id, e)
          throw new Exception("OrderState select transaction error", e)
        }
      }
      try {
        pStmts.getStatement(24).setInt(1, c_w_id)
        pStmts.getStatement(24).setInt(2, c_d_id)
        pStmts.getStatement(24).setInt(3, o_id)
        if (TRACE) logger.trace("SELECT ol_i_id, ol_supply_w_id, ol_quantity, ol_amount, ol_delivery_d FROM order_line " + 
          "WHERE ol_w_id = " + 
          c_w_id + 
          " AND ol_d_id = " + 
          c_d_id + 
          " AND ol_o_id = " + 
          o_id)
        val rs = pStmts.getStatement(24).executeQuery()
        while (rs.next()) {
          ol_i_id = rs.getInt(1)
          ol_supply_w_id = rs.getInt(2)
          ol_quantity = rs.getInt(3)
          ol_amount = rs.getFloat(4)
          ol_delivery_d = rs.getString(5)
        }
        rs.close()
      } catch {
        case e: SQLException => {
          logger.error("SELECT ol_i_id, ol_supply_w_id, ol_quantity, ol_amount, ol_delivery_d FROM order_line " + 
            "WHERE ol_w_id = " + 
            c_w_id + 
            " AND ol_d_id = " + 
            c_d_id + 
            " AND ol_o_id = " + 
            o_id, e)
          throw new Exception("OrderStat select transaction error", e)
        }
      }
      pStmts.commit()
      1
    } catch {
      case e: Exception => try {
        pStmts.rollback()
        0
      } catch {
        case th: Throwable => throw new RuntimeException("Order stat error", th)
      } finally {
        logger.error("Order stat error", e)
      }
    }
  }
}
