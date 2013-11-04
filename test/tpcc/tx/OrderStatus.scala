package ddbt.tpcc.tx
import java.io._
import scala.collection.mutable._
import java.util.Date
import ddbt.tpcc.loadtest.TpccUnitTest._

/**
 * OrderStatus Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
object OrderStatus {

  //Partial Tables (containing all rows, but not all columns)
  //removed columns are commented out
  //val customerPartialTbl = new HashMap[(Int,Int,Int),(String,String,String/*,String,String,String,String,String,String,Date,String,Double,Double*/,Double/*,Double,Int,Int,String*/)]
  //val orderPartialTbl = new HashMap[(Int,Int,Int),(Int,Date,Option[Int]/*,Int,Boolean*/)]
  //val orderLinePartialTbl = new HashMap[(Int,Int,Int,Int),(Int,Int,Option[Date],Int,Double/*,String*/)]

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
  def orderStatusTx(w_id: Int, d_id: Int, c_id: Int, c_last: String, c_by_name: Boolean):Int = {
    try {
      val datetime = new java.util.Date()

      var c: (String,String,String,String,String,String,String,String,String,Date,String,Double,Double,Double,Double,Int/*,Int,String*/,Int) = null
      if (c_by_name) {
        c = SharedData.findCustomerByName(w_id, d_id, c_last)
      } else {
        c = SharedData.findCustomerById(w_id, d_id, c_id)
      }
      val found_c_id = c._17
      val (o_id,entdate,o_carrier_id) = OrderStatusTxOps.findNewestOrder(w_id,d_id,found_c_id)
      val orderLineResults = OrderStatusTxOps.findOrderLines(w_id,d_id,o_id)
      val orderLines: ArrayBuffer[String] = new ArrayBuffer[String]
      orderLineResults.foreach { case (ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, _) =>
        val orderLine: StringBuilder = new StringBuilder
        orderLine.append("[").append(ol_supply_w_id).append(" - ").append(ol_i_id).append(" - ").append(ol_quantity).append(" - ").append(ol_amount).append(" - ")
        //if (ol_delivery_d != null) orderLine.append(ol_delivery_d)
        //else orderLine.append("99-99-9999")
        orderLine.append(ol_delivery_d.getOrElse("99-99-9999"))
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
      output.append("\n   Balance: ").append(c._14).append("\n\n")
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
    } catch {
      case e: Throwable => {
        println("An error occurred in handling OrderStatus transaction for warehouse=%d, district=%d".format(w_id,d_id))
        1
      }
    }
  }
  
  object OrderStatusTxOps {
    def findNewestOrder(o_w_id_arg:Int, o_d_id_arg:Int, c_id_arg:Int) = {
      var max_o_id = -1
      SharedData.orderTbl.foreach { case ((o_id,o_d_id,o_w_id), (o_c_id,_,_,_,_)) =>
        if(o_d_id_arg == o_d_id && o_w_id_arg == o_w_id && c_id_arg == o_c_id) {
          if(o_id > max_o_id) {
            max_o_id = o_id
          }
        }
      }
      val (_,o_entry_d,o_carrier_id,_,_) = SharedData.orderTbl((max_o_id,o_d_id_arg,o_w_id_arg))
      (max_o_id,o_entry_d,o_carrier_id)
    }

    def findOrderLines(ol_w_id_arg:Int, ol_d_id_arg:Int, ol_o_id_arg:Int) = {
      val result = new ArrayBuffer[(Int,Int,Option[Date],Int,Double,String)]
      //slice over first three parts of key
      SharedData.orderLineTbl.foreach { case ((ol_o_id, ol_d_id, ol_w_id, _) , ol_val) =>
        if(ol_o_id == ol_o_id_arg && ol_d_id == ol_d_id_arg && ol_w_id == ol_w_id_arg) {
          result += ol_val
        }
      }
      result
    }
  }
}




