package ddbt.tpcc.loadtest

import java.sql.Connection
import java.sql.ResultSet
import java.sql.SQLException
import java.sql.Statement
import java.sql.Timestamp
import java.util.Calendar
import java.util.Date
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import Payment._

object Payment {

  private val logger = LoggerFactory.getLogger(classOf[Driver])

  private val DEBUG = logger.isDebugEnabled

  private val TRACE = logger.isTraceEnabled
}

class Payment(var pStmts: TpccStatements) extends TpccConstants {

  def payment(t_num: Int, 
      w_id_arg: Int, 
      d_id_arg: Int, 
      byname: Int, 
      c_w_id_arg: Int, 
      c_d_id_arg: Int, 
      c_id_arg: Int, 
      c_last_arg: String, 
      h_amount_arg: Float): Int = {
    1
    //ddbt.tpcc.tx.Payment.paymentTx(w_id_arg, c_w_id_arg, h_amount_arg, d_id_arg, c_d_id_arg, c_id_arg, c_last_arg, byname >= 1)
    // try {
    //   pStmts.setAutoCommit(false)
    //   if (DEBUG) logger.debug("Transaction:	PAYMENT")
    //   val w_id = w_id_arg
    //   val d_id = d_id_arg
    //   var c_id = c_id_arg
    //   var w_name: String = null
    //   var w_street_1: String = null
    //   var w_street_2: String = null
    //   var w_city: String = null
    //   var w_state: String = null
    //   var w_zip: String = null
    //   val c_d_id = c_d_id_arg
    //   val c_w_id = c_w_id_arg
    //   var c_first: String = null
    //   var c_middle: String = null
    //   var c_last: String = null
    //   var c_street_1: String = null
    //   var c_street_2: String = null
    //   var c_city: String = null
    //   var c_state: String = null
    //   var c_zip: String = null
    //   var c_phone: String = null
    //   var c_since: String = null
    //   var c_credit: String = null
    //   var c_credit_lim = 0
    //   var c_discount = 0f
    //   var c_balance = 0f
    //   var c_data: String = null
    //   var c_new_data: String = null
    //   val h_amount = h_amount_arg
    //   var h_data: String = null
    //   var d_name: String = null
    //   var d_street_1: String = null
    //   var d_street_2: String = null
    //   var d_city: String = null
    //   var d_state: String = null
    //   var d_zip: String = null
    //   var namecnt = 0
    //   var n: Int = 0
    //   var proceed = 0
    //   val currentTimeStamp = new Timestamp(System.currentTimeMillis())
    //   proceed = 1
    //   try {
    //     pStmts.getStatement(9).setFloat(1, h_amount)
    //     pStmts.getStatement(9).setInt(2, w_id)
    //     if (TRACE) logger.trace("UPDATE warehouse SET w_ytd = w_ytd + " + h_amount + " WHERE w_id = " + 
    //       w_id)
    //     pStmts.getStatement(9).executeUpdate()
    //   } catch {
    //     case e: SQLException => {
    //       logger.error("UPDATE warehouse SET w_ytd = w_ytd + " + h_amount + " WHERE w_id = " + 
    //         w_id, e)
    //       throw new Exception("Payment Update transaction error", e)
    //     }
    //   }
    //   proceed = 2
    //   try {
    //     pStmts.getStatement(10).setInt(1, w_id)
    //     if (TRACE) logger.trace("SELECT w_street_1, w_street_2, w_city, w_state, w_zip, w_name FROM warehouse WHERE w_id = " + 
    //       w_id)
    //     val rs = pStmts.getStatement(10).executeQuery()
    //     if (rs.next()) {
    //       w_street_1 = rs.getString(1)
    //       w_street_2 = rs.getString(2)
    //       w_city = rs.getString(3)
    //       w_state = rs.getString(4)
    //       w_zip = rs.getString(5)
    //       w_name = rs.getString(6)
    //     }
    //     rs.close()
    //   } catch {
    //     case e: SQLException => {
    //       logger.error("SELECT w_street_1, w_street_2, w_city, w_state, w_zip, w_name FROM warehouse WHERE w_id = " + 
    //         w_id, e)
    //       throw new Exception("Payment select transaction error", e)
    //     }
    //   }
    //   proceed = 3
    //   try {
    //     pStmts.getStatement(11).setFloat(1, h_amount)
    //     pStmts.getStatement(11).setInt(2, w_id)
    //     pStmts.getStatement(11).setInt(3, d_id)
    //     if (TRACE) logger.trace("UPDATE district SET d_ytd = d_ytd + " + h_amount + " WHERE d_w_id = " + 
    //       w_id + 
    //       " AND d_id = " + 
    //       d_id)
    //     pStmts.getStatement(11).executeUpdate()
    //   } catch {
    //     case e: SQLException => {
    //       logger.error("UPDATE district SET d_ytd = d_ytd + " + h_amount + " WHERE d_w_id = " + 
    //         w_id + 
    //         " AND d_id = " + 
    //         d_id, e)
    //       throw new Exception("Payment update transaction error", e)
    //     }
    //   }
    //   proceed = 4
    //   try {
    //     pStmts.getStatement(12).setInt(1, w_id)
    //     pStmts.getStatement(12).setInt(2, d_id)
    //     if (TRACE) logger.trace("SELECT d_street_1, d_street_2, d_city, d_state, d_zip, d_name FROM district WHERE d_w_id = " + 
    //       w_id + 
    //       " AND d_id = " + 
    //       d_id)
    //     val rs = pStmts.getStatement(12).executeQuery()
    //     if (rs.next()) {
    //       d_street_1 = rs.getString(1)
    //       d_street_2 = rs.getString(2)
    //       d_city = rs.getString(3)
    //       d_state = rs.getString(4)
    //       d_zip = rs.getString(5)
    //       d_name = rs.getString(6)
    //     }
    //     rs.close()
    //   } catch {
    //     case e: SQLException => {
    //       logger.error("SELECT d_street_1, d_street_2, d_city, d_state, d_zip, d_name FROM district WHERE d_w_id = " + 
    //         w_id + 
    //         " AND d_id = " + 
    //         d_id, e)
    //       throw new Exception("Payment select transaction error", e)
    //     }
    //   }
    //   if (byname >= 1) {
    //     c_last = c_last_arg
    //     proceed = 5
    //     try {
    //       pStmts.getStatement(13).setInt(1, c_w_id)
    //       pStmts.getStatement(13).setInt(2, c_d_id)
    //       pStmts.getStatement(13).setString(3, c_last)
    //       if (TRACE) logger.trace("SELECT count(c_id) FROM customer WHERE c_w_id = " + c_w_id + 
    //         " AND c_d_id = " + 
    //         c_d_id + 
    //         " AND c_last = " + 
    //         c_last)
    //       val rs = pStmts.getStatement(13).executeQuery()
    //       if (rs.next()) {
    //         namecnt = rs.getInt(1)
    //       }
    //       rs.close()
    //     } catch {
    //       case e: SQLException => {
    //         logger.error("SELECT count(c_id) FROM customer WHERE c_w_id = " + c_w_id + 
    //           " AND c_d_id = " + 
    //           c_d_id + 
    //           " AND c_last = " + 
    //           c_last, e)
    //         throw new Exception("Payment select transaction error", e)
    //       }
    //     }
    //     try {
    //       pStmts.getStatement(14).setInt(1, c_w_id)
    //       pStmts.getStatement(14).setInt(2, c_d_id)
    //       pStmts.getStatement(14).setString(3, c_last)
    //       if (TRACE) logger.trace("SELECT c_id FROM customer WHERE c_w_id = " + c_w_id + 
    //         " AND c_d_id = " + 
    //         c_d_id + 
    //         " AND c_last = " + 
    //         c_last + 
    //         " ORDER BY c_first")
    //       if (namecnt % 2 == 1) {
    //         namecnt += 1
    //       }
    //       val rs = pStmts.getStatement(14).executeQuery()
    //       n = 0
    //       while (n < namecnt / 2) {
    //         if (rs.next()) {
    //           c_id = rs.getInt(1)
    //         } else {
    //           throw new IllegalStateException()
    //         }
    //         n += 1
    //         n += 1
    //       }
    //       rs.close()
    //     } catch {
    //       case e: SQLException => {
    //         logger.error("SELECT c_id FROM customer WHERE c_w_id = " + c_w_id + 
    //           " AND c_d_id = " + 
    //           c_d_id + 
    //           " AND c_last = " + 
    //           c_last + 
    //           " ORDER BY c_first", e)
    //         throw new Exception("Payment select transaction error", e)
    //       }
    //     }
    //   }
    //   proceed = 6
    //   try {
    //     pStmts.getStatement(15).setInt(1, c_w_id)
    //     pStmts.getStatement(15).setInt(2, c_d_id)
    //     pStmts.getStatement(15).setInt(3, c_id)
    //     if (TRACE) logger.trace("SELECT c_first, c_middle, c_last, c_street_1, c_street_2, c_city, c_state, c_zip, c_phone, c_credit, c_credit_lim, c_discount, c_balance, c_since FROM customer " + 
    //       "WHERE c_w_id = " + 
    //       c_w_id + 
    //       " AND c_d_id = " + 
    //       c_d_id + 
    //       " AND c_id = " + 
    //       c_id + 
    //       " FOR UPDATE")
    //     val rs = pStmts.getStatement(15).executeQuery()
    //     if (rs.next()) {
    //       c_first = rs.getString(1)
    //       c_middle = rs.getString(2)
    //       c_last = rs.getString(3)
    //       c_street_1 = rs.getString(4)
    //       c_street_2 = rs.getString(5)
    //       c_city = rs.getString(6)
    //       c_state = rs.getString(7)
    //       c_zip = rs.getString(8)
    //       c_phone = rs.getString(9)
    //       c_credit = rs.getString(10)
    //       c_credit_lim = rs.getInt(11)
    //       c_discount = rs.getFloat(12)
    //       c_balance = rs.getFloat(13)
    //       c_since = rs.getString(14)
    //     }
    //     rs.close()
    //   } catch {
    //     case e: SQLException => {
    //       logger.error("SELECT c_first, c_middle, c_last, c_street_1, c_street_2, c_city, c_state, c_zip, c_phone, c_credit, c_credit_lim, c_discount, c_balance, c_since FROM customer " + 
    //         "WHERE c_w_id = " + 
    //         c_w_id + 
    //         " AND c_d_id = " + 
    //         c_d_id + 
    //         " AND c_id = " + 
    //         c_id + 
    //         " FOR UPDATE", e)
    //       throw new Exception("Payment select transaction error", e)
    //     }
    //   }
    //   c_balance += h_amount
    //   if (c_credit != null) {
    //     if (c_credit.contains("BC")) {
    //       proceed = 7
    //       try {
    //         pStmts.getStatement(16).setInt(1, c_w_id)
    //         pStmts.getStatement(16).setInt(2, c_d_id)
    //         pStmts.getStatement(16).setInt(3, c_id)
    //         if (TRACE) logger.trace("SELECT c_data FROM customer WHERE c_w_id = " + c_w_id + 
    //           " AND c_d_id = " + 
    //           c_d_id + 
    //           " AND c_id = " + 
    //           c_id)
    //         val rs = pStmts.getStatement(16).executeQuery()
    //         if (rs.next()) {
    //           c_data = rs.getString(1)
    //         }
    //         rs.close()
    //       } catch {
    //         case e: SQLException => {
    //           logger.error("SELECT c_data FROM customer WHERE c_w_id = " + c_w_id + 
    //             " AND c_d_id = " + 
    //             c_d_id + 
    //             " AND c_id = " + 
    //             c_id, e)
    //           throw new Exception("Payment select transaction error", e)
    //         }
    //       }
    //       c_new_data = "| %d %d %d %d %d $%f %s %s".format(c_id, c_d_id, c_w_id, d_id, w_id, 
    //         h_amount, currentTimeStamp.toString, c_data)
    //       proceed = 8
    //       try {
    //         pStmts.getStatement(17).setFloat(1, c_balance)
    //         pStmts.getStatement(17).setString(2, c_data)
    //         pStmts.getStatement(17).setInt(3, c_w_id)
    //         pStmts.getStatement(17).setInt(4, c_d_id)
    //         pStmts.getStatement(17).setInt(5, c_id)
    //         if (TRACE) logger.trace("UPDATE customer SET c_balance = " + c_balance + ", c_data = " + 
    //           c_data + 
    //           " WHERE c_w_id = " + 
    //           c_w_id + 
    //           " AND c_d_id = " + 
    //           c_d_id + 
    //           " AND c_id = " + 
    //           c_id)
    //         pStmts.getStatement(17).executeUpdate()
    //       } catch {
    //         case e: SQLException => {
    //           logger.error("UPDATE customer SET c_balance = " + c_balance + ", c_data = " + 
    //             c_data + 
    //             " WHERE c_w_id = " + 
    //             c_w_id + 
    //             " AND c_d_id = " + 
    //             c_d_id + 
    //             " AND c_id = " + 
    //             c_id, e)
    //           throw new Exception("Payment update transaction error", e)
    //         }
    //       }
    //     } else {
    //       proceed = 9
    //       try {
    //         pStmts.getStatement(18).setFloat(1, c_balance)
    //         pStmts.getStatement(18).setInt(2, c_w_id)
    //         pStmts.getStatement(18).setInt(3, c_d_id)
    //         pStmts.getStatement(18).setInt(4, c_id)
    //         if (TRACE) logger.trace("UPDATE customer SET c_balance = " + c_balance + " WHERE c_w_id = " + 
    //           c_w_id + 
    //           " AND c_d_id = " + 
    //           c_d_id + 
    //           " AND c_id = " + 
    //           c_id)
    //         pStmts.getStatement(18).executeUpdate()
    //       } catch {
    //         case e: SQLException => {
    //           logger.error("UPDATE customer SET c_balance = " + c_balance + " WHERE c_w_id = " + 
    //             c_w_id + 
    //             " AND c_d_id = " + 
    //             c_d_id + 
    //             " AND c_id = " + 
    //             c_id, e)
    //           throw new Exception("Payment update transaction error", e)
    //         }
    //       }
    //     }
    //   } else {
    //     proceed = 9
    //     try {
    //       pStmts.getStatement(18).setFloat(1, c_balance)
    //       pStmts.getStatement(18).setInt(2, c_w_id)
    //       pStmts.getStatement(18).setInt(3, c_d_id)
    //       pStmts.getStatement(18).setInt(4, c_id)
    //       if (TRACE) logger.trace("UPDATE customer SET c_balance = " + c_balance + " WHERE c_w_id = " + 
    //         c_w_id + 
    //         " AND c_d_id = " + 
    //         c_d_id + 
    //         " AND c_id = " + 
    //         c_id)
    //       pStmts.getStatement(18).executeUpdate()
    //     } catch {
    //       case e: SQLException => {
    //         logger.error("UPDATE customer SET c_balance = " + c_balance + " WHERE c_w_id = " + 
    //           c_w_id + 
    //           " AND c_d_id = " + 
    //           c_d_id + 
    //           " AND c_id = " + 
    //           c_id, e)
    //         throw new Exception("Payment update transaction error", e)
    //       }
    //     }
    //   }
    //   h_data = h_data + '\0' + d_name + ' ' + ' ' + ' ' + ' ' + '\0'
    //   proceed = 10
    //   try {
    //     pStmts.getStatement(19).setInt(1, c_d_id)
    //     pStmts.getStatement(19).setInt(2, c_w_id)
    //     pStmts.getStatement(19).setInt(3, c_id)
    //     pStmts.getStatement(19).setInt(4, d_id)
    //     pStmts.getStatement(19).setInt(5, w_id)
    //     pStmts.getStatement(19).setString(6, currentTimeStamp.toString)
    //     pStmts.getStatement(19).setFloat(7, h_amount)
    //     pStmts.getStatement(19).setString(8, h_data)
    //     if (TRACE) logger.trace("INSERT INTO history(h_c_d_id, h_c_w_id, h_c_id, h_d_id, h_w_id, h_date, h_amount, h_data)" + 
    //       " VALUES( " + 
    //       c_d_id + 
    //       "," + 
    //       c_w_id + 
    //       "," + 
    //       c_id + 
    //       "," + 
    //       d_id + 
    //       "," + 
    //       w_id + 
    //       "," + 
    //       currentTimeStamp.toString + 
    //       "," + 
    //       h_amount + 
    //       ",")
    //     pStmts.getStatement(19).executeUpdate()
    //   } catch {
    //     case e: SQLException => {
    //       logger.error("INSERT INTO history(h_c_d_id, h_c_w_id, h_c_id, h_d_id, h_w_id, h_date, h_amount, h_data)" + 
    //         " VALUES( " + 
    //         c_d_id + 
    //         "," + 
    //         c_w_id + 
    //         "," + 
    //         c_id + 
    //         "," + 
    //         d_id + 
    //         "," + 
    //         w_id + 
    //         "," + 
    //         currentTimeStamp.toString + 
    //         "," + 
    //         h_amount + 
    //         ",", e)
    //       throw new Exception("Payment insert transaction error", e)
    //     }
    //   }
    //   pStmts.commit()
    //   1
    // } catch {
    //   case e: Exception => try {
    //     pStmts.rollback()
    //     0
    //   } catch {
    //     case th: Throwable => throw new RuntimeException("Payment error", th)
    //   } finally {
    //     logger.error("Payment error", e)
    //   }
    // }
  }
}
