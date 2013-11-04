package ddbt.tpcc.loadtest

import java.sql.SQLException
import java.util.Calendar
import java.util.Date
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import NewOrder._

object NewOrder {

  private val logger = LoggerFactory.getLogger(classOf[Driver])

  private val DEBUG = logger.isDebugEnabled

  private val TRACE = logger.isTraceEnabled
}

class NewOrder(var pStmts: TpccStatements) extends TpccConstants {

  private var s_dist_01: String = null

  private var s_dist_02: String = null

  private var s_dist_03: String = null

  private var s_dist_04: String = null

  private var s_dist_05: String = null

  private var s_dist_06: String = null

  private var s_dist_07: String = null

  private var s_dist_08: String = null

  private var s_dist_09: String = null

  private var s_dist_10: String = null

  var iname: Array[String] = new Array[String](MAX_NUM_ITEMS)

  var bg: Array[String] = new Array[String](MAX_NUM_ITEMS)

  var amt: Array[Float] = new Array[Float](MAX_NUM_ITEMS)

  var price: Array[Float] = new Array[Float](MAX_NUM_ITEMS)

  var stock: Array[Int] = new Array[Int](MAX_NUM_ITEMS)

  var ol_num_seq: Array[Int] = new Array[Int](MAX_NUM_ITEMS)

  private def pickDistInfo(ol_dist_info: String, ol_supply_w_id: Int): String = {
    val new_ol_dist_info = ol_supply_w_id match {
      case 1 => s_dist_01
      case 2 => s_dist_02
      case 3 => s_dist_03
      case 4 => s_dist_04
      case 5 => s_dist_05
      case 6 => s_dist_06
      case 7 => s_dist_07
      case 8 => s_dist_08
      case 9 => s_dist_09
      case 10 => s_dist_10
    }
    new_ol_dist_info
}

  def neword(t_num: Int, 
      w_id_arg: Int, 
      d_id_arg: Int, 
      c_id_arg: Int, 
      o_ol_cnt_arg: Int, 
      o_all_local_arg: Int, 
      itemid: Array[Int], 
      supware: Array[Int], 
      qty: Array[Int]): Int = {
    val time = new java.sql.Timestamp(System.currentTimeMillis())
    ddbt.tpcc.tx.NewOrder.newOrderTx(time, w_id_arg, d_id_arg, c_id_arg, o_all_local_arg > 0, o_ol_cnt_arg, itemid, supware, qty, new Array[Double](o_ol_cnt_arg), new Array[String](o_ol_cnt_arg), new Array[Int](o_ol_cnt_arg), new Array[Char](o_ol_cnt_arg), new Array[Double](o_ol_cnt_arg))

    try {
      pStmts.setAutoCommit(false)
      if (DEBUG) logger.debug("Transaction:	New Order")
      val w_id = w_id_arg
      val d_id = d_id_arg
      val c_id = c_id_arg
      val o_ol_cnt = o_ol_cnt_arg
      val o_all_local = o_all_local_arg
      var c_discount = 0f
      var c_last: String = null
      var c_credit: String = null
      var w_tax = 0f
      var d_next_o_id = 0
      var d_tax = 0f
      var o_id = 0
      var i_name: String = null
      var i_price = 0f
      var i_data: String = null
      var ol_i_id = 0
      var s_quantity = 0
      var s_data: String = null
      var ol_dist_info: String = null
      var ol_supply_w_id = 0
      var ol_amount = 0f
      var ol_quantity = 0
      var min_num = 0
      var i = 0
      var j = 0
      var tmp = 0
      var swp = 0
      val currentTimeStamp = time.toString
      try {
        var column = 1
        val pstmt0 = pStmts.getStatement(0)
        pstmt0.setInt({ column += 1; column - 1} , w_id)
        pstmt0.setInt({ column += 1; column - 1} , w_id)
        pstmt0.setInt({ column += 1; column - 1} , d_id)
        pstmt0.setInt({ column += 1; column - 1} , c_id)
        if (TRACE) logger.trace("SELECT c_discount, c_last, c_credit, w_tax FROM customer, warehouse WHERE w_id = " + 
          w_id + 
          " AND c_w_id = " + 
          w_id + 
          " AND c_d_id = " + 
          d_id + 
          " AND c_id = " + 
          c_id)
        val rs = pstmt0.executeQuery()
        if (rs.next()) {
          c_discount = rs.getFloat(1)
          c_last = rs.getString(2)
          c_credit = rs.getString(3)
          w_tax = rs.getFloat(4)
        }
        rs.close()
      } catch {
        case e: SQLException => {
          logger.error("SELECT c_discount, c_last, c_credit, w_tax FROM customer, warehouse WHERE w_id = " + 
            w_id + 
            " AND c_w_id = " + 
            w_id + 
            " AND c_d_id = " + 
            d_id + 
            " AND c_id = " + 
            c_id, e)
          throw new Exception("NewOrder select transaction error", e)
        }
      }
      try {
        val pstmt1 = pStmts.getStatement(1)
        pstmt1.setInt(1, d_id)
        pstmt1.setInt(2, w_id)
        if (TRACE) logger.trace("SELECT d_next_o_id, d_tax FROM district WHERE d_id = " + 
          d_id + 
          "  AND d_w_id = " + 
          w_id + 
          " FOR UPDATE")
        val rs = pstmt1.executeQuery()
        if (rs.next()) {
          d_next_o_id = rs.getInt(1)
          d_tax = rs.getFloat(2)
        } else {
          logger.error("Failed to obtain d_next_o_id. No results to query: " + 
            "SELECT d_next_o_id, d_tax FROM district WHERE d_id = " + 
            d_id + 
            "  AND d_w_id = " + 
            w_id + 
            " FOR UPDATE")
        }
        rs.close()
      } catch {
        case e: SQLException => {
          logger.error("SELECT d_next_o_id, d_tax FROM district WHERE d_id = " + 
            d_id + 
            "  AND d_w_id = " + 
            w_id + 
            " FOR UPDATE", e)
          throw new Exception("Neworder select transaction error", e)
        }
      }
      try {
        val pstmt2 = pStmts.getStatement(2)
        pstmt2.setInt(1, d_next_o_id)
        pstmt2.setInt(2, d_id)
        pstmt2.setInt(3, w_id)
        if (TRACE) logger.trace("UPDATE district SET d_next_o_id = " + d_next_o_id + " + 1 WHERE d_id = " + 
          d_id + 
          " AND d_w_id = " + 
          w_id)
        pstmt2.executeUpdate()
      } catch {
        case e: SQLException => {
          logger.error("UPDATE district SET d_next_o_id = " + d_next_o_id + " + 1 WHERE d_id = " + 
            d_id + 
            " AND d_w_id = " + 
            w_id, e)
          throw new Exception("NewOrder update transaction error", e)
        }
      }
      o_id = d_next_o_id
      try {
        val pstmt3 = pStmts.getStatement(3)
        pstmt3.setInt(1, o_id)
        pstmt3.setInt(2, d_id)
        pstmt3.setInt(3, w_id)
        pstmt3.setInt(4, c_id)
        pstmt3.setString(5, currentTimeStamp)
        pstmt3.setInt(6, o_ol_cnt)
        pstmt3.setInt(7, o_all_local)
        if (TRACE) logger.trace("INSERT INTO orders (o_id, o_d_id, o_w_id, o_c_id, o_entry_d, o_ol_cnt, o_all_local) " + 
          "VALUES(" + 
          o_id + 
          "," + 
          d_id + 
          "," + 
          w_id + 
          "," + 
          c_id + 
          "," + 
          currentTimeStamp + 
          "," + 
          o_ol_cnt + 
          "," + 
          o_all_local + 
          ")")
        pstmt3.executeUpdate()
      } catch {
        case e: SQLException => {
          logger.error("INSERT INTO orders (o_id, o_d_id, o_w_id, o_c_id, o_entry_d, o_ol_cnt, o_all_local) " + 
            "VALUES(" + 
            o_id + 
            "," + 
            d_id + 
            "," + 
            w_id + 
            "," + 
            c_id + 
            "," + 
            currentTimeStamp + 
            "," + 
            o_ol_cnt + 
            "," + 
            o_all_local + 
            ")", e)
          throw new Exception("NewOrder insert transaction error", e)
        }
      }
      try {
        val pstmt4 = pStmts.getStatement(4)
        pstmt4.setInt(1, o_id)
        pstmt4.setInt(2, d_id)
        pstmt4.setInt(3, w_id)
        if (TRACE) logger.trace("INSERT INTO new_orders (no_o_id, no_d_id, no_w_id) VALUES (" + 
          o_id + 
          "," + 
          d_id + 
          "," + 
          w_id + 
          ")")
        pstmt4.executeUpdate()
      } catch {
        case e: SQLException => {
          logger.error("INSERT INTO new_orders (no_o_id, no_d_id, no_w_id) VALUES (" + 
            o_id + 
            "," + 
            d_id + 
            "," + 
            w_id + 
            ")", e)
          throw new Exception("NewOrder insert transaction error", e)
        }
      }
      i = 0
      while (i < o_ol_cnt) {
        ol_num_seq(i) = i
        i += 1
      }
      i = 0
      while (i < (o_ol_cnt - 1)) {
        tmp = (MAXITEMS + 1) * supware(ol_num_seq(i)) + itemid(ol_num_seq(i))
        min_num = i
        j = i + 1
        while (j < o_ol_cnt) {
          if ((MAXITEMS + 1) * supware(ol_num_seq(j)) + itemid(ol_num_seq(j)) < 
            tmp) {
            tmp = (MAXITEMS + 1) * supware(ol_num_seq(j)) + itemid(ol_num_seq(j))
            min_num = j
          }
          j += 1
        }
        if (min_num != i) {
          swp = ol_num_seq(min_num)
          ol_num_seq(min_num) = ol_num_seq(i)
          ol_num_seq(i) = swp
        }
        i += 1
      }
      var ol_number = 1
      while (ol_number <= o_ol_cnt) {
        ol_supply_w_id = supware(ol_num_seq(ol_number - 1))
        ol_i_id = itemid(ol_num_seq(ol_number - 1))
        ol_quantity = qty(ol_num_seq(ol_number - 1))
        try {
          val pstmt5 = pStmts.getStatement(5)
          pstmt5.setInt(1, ol_i_id)
          if (TRACE) logger.trace("SELECT i_price, i_name, i_data FROM item WHERE i_id =" + 
            ol_i_id)
          val rs = pstmt5.executeQuery()
          if (rs.next()) {
            i_price = rs.getFloat(1)
            i_name = rs.getString(2)
            i_data = rs.getString(3)
          } else {
            if (DEBUG) {
              logger.debug("No item found for item id " + ol_i_id)
            }
            throw new AbortedTransactionException()
          }
          rs.close()
        } catch {
          case e: SQLException => {
            logger.error("SELECT i_price, i_name, i_data FROM item WHERE i_id =" + 
              ol_i_id, e)
            throw new Exception("NewOrder select transaction error", e)
          }
        }
        price(ol_num_seq(ol_number - 1)) = i_price
        iname(ol_num_seq(ol_number - 1)) = i_name
        try {
          val pstmt6 = pStmts.getStatement(6)
          pstmt6.setInt(1, ol_i_id)
          pstmt6.setInt(2, ol_supply_w_id)
          if (TRACE) logger.trace("SELECT s_quantity, s_data, s_dist_01, s_dist_02, s_dist_03, s_dist_04, s_dist_05, s_dist_06, s_dist_07, s_dist_08, s_dist_09, s_dist_10 FROM " + 
            "stock WHERE s_i_id = " + 
            ol_i_id + 
            " AND s_w_id = " + 
            ol_supply_w_id + 
            " FOR UPDATE")
          val rs = pstmt6.executeQuery()
          if (rs.next()) {
            s_quantity = rs.getInt(1)
            s_data = rs.getString(2)
            s_dist_01 = rs.getString(3)
            s_dist_02 = rs.getString(4)
            s_dist_03 = rs.getString(5)
            s_dist_04 = rs.getString(6)
            s_dist_05 = rs.getString(7)
            s_dist_06 = rs.getString(8)
            s_dist_07 = rs.getString(9)
            s_dist_08 = rs.getString(10)
            s_dist_09 = rs.getString(11)
            s_dist_10 = rs.getString(12)
          }
          rs.close()
        } catch {
          case e: SQLException => {
            logger.error("SELECT s_quantity, s_data, s_dist_01, s_dist_02, s_dist_03, s_dist_04, s_dist_05, s_dist_06, s_dist_07, s_dist_08, s_dist_09, s_dist_10 FROM " + 
              "stock WHERE s_i_id = " + 
              ol_i_id + 
              " AND s_w_id = " + 
              ol_supply_w_id + 
              " FOR UPDATE", e)
            throw new Exception("NewOrder select transaction error", e)
          }
        }
        ol_dist_info = pickDistInfo(ol_dist_info, d_id)
        stock(ol_num_seq(ol_number - 1)) = s_quantity
        bg(ol_num_seq(ol_number - 1)) = if ((i_data.contains("original")) && (s_data.contains("original"))) "B" else "G"
        s_quantity = if (s_quantity > ol_quantity) s_quantity - ol_quantity else s_quantity - ol_quantity + 91
        try {
          val pstmt7 = pStmts.getStatement(7)
          pstmt7.setInt(1, s_quantity)
          pstmt7.setInt(2, ol_i_id)
          pstmt7.setInt(3, ol_supply_w_id)
          if (TRACE) logger.trace("UPDATE stock SET s_quantity = " + s_quantity + " WHERE s_i_id = " + 
            ol_i_id + 
            " AND s_w_id = " + 
            ol_supply_w_id)
          pstmt7.executeUpdate()
        } catch {
          case e: SQLException => {
            logger.error("UPDATE stock SET s_quantity = " + s_quantity + " WHERE s_i_id = " + 
              ol_i_id + 
              " AND s_w_id = " + 
              ol_supply_w_id, e)
            throw new Exception("NewOrder update transaction error", e)
          }
        }
        ol_amount = ol_quantity * i_price * (1 + w_tax + d_tax) * (1 - c_discount)
        amt(ol_num_seq(ol_number - 1)) = ol_amount
        try {
          val pstmt8 = pStmts.getStatement(8)
          pstmt8.setInt(1, o_id)
          pstmt8.setInt(2, d_id)
          pstmt8.setInt(3, w_id)
          pstmt8.setInt(4, ol_number)
          pstmt8.setInt(5, ol_i_id)
          pstmt8.setInt(6, ol_supply_w_id)
          pstmt8.setInt(7, ol_quantity)
          pstmt8.setFloat(8, ol_amount)
          pstmt8.setString(9, ol_dist_info)
          if (TRACE) logger.trace("INSERT INTO order_line (ol_o_id, ol_d_id, ol_w_id, ol_number, ol_i_id, ol_supply_w_id, ol_quantity, ol_amount, ol_dist_info) " + 
            "VALUES (" + 
            o_id + 
            "," + 
            d_id + 
            "," + 
            w_id + 
            "," + 
            ol_number + 
            "," + 
            ol_i_id + 
            "," + 
            ol_supply_w_id + 
            "," + 
            ol_quantity + 
            "," + 
            ol_amount + 
            "," + 
            ol_dist_info + 
            ")")
          pstmt8.executeUpdate()
        } catch {
          case e: SQLException => {
            logger.error("INSERT INTO order_line (ol_o_id, ol_d_id, ol_w_id, ol_number, ol_i_id, ol_supply_w_id, ol_quantity, ol_amount, ol_dist_info) " + 
              "VALUES (" + 
              o_id + 
              "," + 
              d_id + 
              "," + 
              w_id + 
              "," + 
              ol_number + 
              "," + 
              ol_i_id + 
              "," + 
              ol_supply_w_id + 
              "," + 
              ol_quantity + 
              "," + 
              ol_amount + 
              "," + 
              ol_dist_info + 
              ")", e)
            throw new Exception("NewOrder insert transaction error", e)
          }
        }
        ol_number += 1
      }
      pStmts.commit()
      1
    } catch {
      case ate: AbortedTransactionException => {
        if (logger.isDebugEnabled) {
          logger.debug("Caught AbortedTransactionException")
        }
        pStmts.rollback()
        1
      }
      case e: Exception => {
        logger.error("New Order error", e)
        pStmts.rollback()
        0
      }
    }
  }
}
