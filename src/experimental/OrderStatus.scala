package ddbt.experimental
import java.io._
import scala.collection.mutable._
import java.util.Date

/**
 * OrderStatus Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
object OrderStatus {

  //Partial Tables (containing all rows, but not all columns)
  //removed columns are commented out
  val customerPartialTbl = new HashMap[(Int,Int,Int),(String,String,String/*,String,String,String,String,String,String,Date,String,Double,Double*/,Double/*,Double,Int,Int,String*/)]
  val orderPartialTbl = new HashMap[(Int,Int,Int),(/*Int,*/Date,Option[Int]/*,Int,Boolean*/)]
  val orderLinePartialTbl = new HashMap[(Int,Int,Int,Int),(Int,Int,Date,Int,Double/*,String*/)]

  /**
   * @param w_id is warehouse id
   * @param d_id is district id
   * @param c_id is customer id
   *
   * Table interactions:
   *   - [Customer: R] in
   *      + findCustomerByName
   *      + findCustomerById
   *   - [Order: R] in
   *      + findNewestOrder
   *   - [OrderLine: R] in
   *      + findOrderLines
   */
  def orderStatusTransaction(w_id: Int, d_id: Int, c_id: Int, c_last: String, c_by_name: Boolean):Int = {
    try {
      val datetime = new java.util.Date()

      var c: (String,String,String/*,String,String,String,String,String,String,Date,String,Double,Double*/,Double/*,Double,Int,Int,String*/,Int) = null
      if (c_by_name) {
        c = OrderStatusTxOps.findCustomerByName(w_id, d_id, c_last)
      } else {
        c = OrderStatusTxOps.findCustomerById(w_id, d_id, c_id)
      }
      val found_c_id = c._5
      val (o_id,entdate,o_carrier_id) = OrderStatusTxOps.findNewestOrder(w_id,d_id,found_c_id)
      val orderLineResults = OrderStatusTxOps.findOrderLines(w_id,d_id,o_id)
      val orderLines: ArrayBuffer[String] = new ArrayBuffer[String]
      orderLineResults.foreach { case (ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount) =>
        val orderLine: StringBuilder = new StringBuilder
        orderLine.append("[").append(ol_supply_w_id).append(" - ").append(ol_i_id).append(" - ").append(ol_quantity).append(" - ").append(ol_amount).append(" - ")
        if (ol_delivery_d != null) orderLine.append(ol_delivery_d)
        else orderLine.append("99-99-9999")
        orderLine.append("]")
        orderLines += orderLine.toString
      }
      val output: StringBuilder = new StringBuilder
      output.append("\n")
      output.append("+-------------------------- ORDER-STATUS -------------------------+\n")
      output.append(" Date: ").append(datetime)
      output.append("\n\n Warehouse: ").append(w_id)
      output.append("\n District:  ").append(d_id)
      output.append("\n\n Customer:  ").append(found_c_id)
      output.append("\n   Name:    ").append(c._1).append(" ").append(c._2).append(" ").append(c._3)
      output.append("\n   Balance: ").append(c._4).append("\n\n")
      if (o_id == -1) {
        output.append(" Customer has no orders placed.\n")
      } else {
        output.append(" Order-Number: ").append(o_id)
        output.append("\n    Entry-Date: ").append(entdate)
        output.append("\n    Carrier-Number: ").append(o_carrier_id).append("\n\n")
        if (orderLines.size != 0) {
          output.append(" [Supply_W - Item_ID - Qty - Amount - Delivery-Date]\n")
          for (orderLine <- orderLines) {
            output.append(" ").append(orderLine).append("\n")
          }
        }
        else {
          println(" This Order has no Order-Lines.\n")
        }
      }
      output.append("+-----------------------------------------------------------------+\n\n")
      println(output.toString)
      0
/**
 * Payment Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
  }

  object OrderStatusTxOps {
    def findCustomerByName(c_w_id: Int, c_d_id: Int, input_c_last: String) = {
      class MiniCustomer(val cust_id:Int, val cust_first:String) extends Ordered[MiniCustomer] {
        def compare(that: MiniCustomer) = this.cust_first.compareTo(that.cust_first)
      } 
      var customers = new ArrayBuffer[MiniCustomer]
      //we should slice over input_c_last
      customerPartialTbl.foreach { case (c_k,c_v) =>
        if(c_v._3 == input_c_last) {
          customers += new MiniCustomer(c_k._1,c_v._1)
        }
      }
      if (customers.size == 0) {
        throw new RuntimeException("The customer C_LAST=" + input_c_last + " C_D_ID=" + c_d_id + " C_W_ID=" + c_w_id + " not found!")
      }
      customers = customers.sorted
      var index: Int = customers.size / 2
      if (customers.size % 2 == 0) {
        index -= 1
      }
      val c_id = customers(index).cust_id
      val (c_first,c_middle,c_last/*,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount*/,c_balance/*,c_ytd_payment,c_payment_cnt,_*/) = customerPartialTbl((c_id,c_d_id,c_w_id))
      (c_first,c_middle,c_last/*,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount*/,c_balance/*,c_ytd_payment,c_payment_cnt*/,c_id)
    }
    def findCustomerById(c_w_id: Int, c_d_id: Int, c_id: Int) = {
      val (c_first,c_middle,c_last/*,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount*/,c_balance/*,c_ytd_payment,c_payment_cnt,_*/) = customerPartialTbl((c_id,c_d_id,c_w_id))
      (c_first,c_middle,c_last/*,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount*/,c_balance/*,c_ytd_payment,c_payment_cnt*/,c_id)
    }

    def findNewestOrder(o_w_id:Int, o_d_id:Int, o_c_id:Int) = {
      var max_o_id = -1
      orderPartialTbl.foreach { o =>
        if(o._1._2 == o_d_id && o._1._3 == o_w_id && o._2._1 == o_c_id) {
          if(o._1._1 > max_o_id) max_o_id = o._1._1
        }
      }
      val (o_entry_d,o_carrier_id) = orderPartialTbl((max_o_id,o_d_id,o_w_id))
      (max_o_id,o_entry_d,o_carrier_id)
    }

    def findOrderLines(ol_w_id:Int, ol_d_id:Int, ol_o_id:Int) = {
      val result = new ArrayBuffer[(Int,Int,Date,Int,Double/*,String*/)]
      //slice over first three parts of key
      orderLinePartialTbl.foreach { case ol =>
        if(ol._1._1 == ol_o_id && ol._1._2 == ol_d_id && ol._1._3 == ol_w_id) result += ol._2
      }
      result
    }
  }
}




