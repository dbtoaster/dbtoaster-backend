package ddbt.tpcc.tx
import java.io._
import scala.collection.mutable._
import java.util.Date
import ddbt.tpcc.loadtest.TpccUnitTest._

/**
 * Payment Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
object Payment {
  //Tables
  //val historyTbl = new HashSet[(Int,Int,Int,Int,Int,Date,Double,String)]

  //Partial Tables (containing all rows, but not all columns)
  //removed columns are commented out
  //val warehousePartialTbl = new HashMap[Int,(String,String,String,String,String,String,/*Double,*/Double)]
  //val districtPartialTbl = new HashMap[(Int,Int),(String,String,String,String,String,String/*,Double*/,Double/*,Int*/)]
  //val customerPartialTbl = new HashMap[(Int,Int,Int),(String,String,String,String,String,String,String,String,String,Date,String,Double,Double,Double,Double,Int/*,Int*/,String)]


  /**
   * @param w_id is warehouse id
   * @param d_id is district id
   * @param c_id is customer id
   *
   * Table interactions:
   *   - [Warehouse: RW] where R in
   *      + findWarehouse
   *     and W in
   *      + updateWarehouseYtd
   *   - [District: RW] where R in
   *      + findDistrict
   *     and W in
   *      + updateDistrict
   *   - [Customer: RW] where R in
   *      + findCustomerByName
   *      + findCustomerById
   *      + findCustomerData
   *     and W in
   *      + updateCustomerBalance
   *      + updateCustomerBalanceAndData
   *   - [History: W] in
   *      + insertHistory
   *
   */
  def paymentTx(w_id: Int, c_w_id: Int, h_amount: Double, d_id: Int, c_d_id: Int, c_id: Int, c_last: String, c_by_name: Boolean):Int = {
    try {
      val datetime = new java.util.Date()

      NewOrderTxOps.updateWarehouseYtd(w_id, h_amount)

      val (w_name,w_street_1,w_street_2,w_city,w_state,w_zip) = NewOrderTxOps.findWarehouse(w_id)

      NewOrderTxOps.updateDistrict(w_id,d_id,h_amount)

      val (d_name,d_street_1,d_street_2,d_city,d_state,d_zip) = NewOrderTxOps.findDistrict(w_id,d_id)

      var c: (String,String,String,String,String,String,String,String,String,Date,String,Double,Double,Double,Double,Int/*,Int,String*/,Int) = null
      if (c_by_name) {
        c = SharedData.findCustomerByName(c_w_id, c_d_id, c_last)
      } else {
        c = SharedData.findCustomerById(c_w_id, c_d_id, c_id)
      }
      val found_c_id = c._17
      var c_data:String = null
      if (c._11 == "BC") {
        c_data = NewOrderTxOps.findCustomerData(c_w_id, c_d_id, c_id)
        c_data = found_c_id + " " + c_d_id + " " + c_w_id + " " + d_id + " " + w_id + " " + h_amount + " | " + c_data
        if (c_data.length > 500) c_data = c_data.substring(0, 500)
        NewOrderTxOps.updateCustomerBalanceAndData(c_w_id,c_d_id,c_id,
          c._13-h_amount,
          c._14+h_amount,
          c._16+1,
          c_data)
      } else {
        NewOrderTxOps.updateCustomerBalance(c_w_id,c_d_id,c_id,
          c._13-h_amount,
          c._14+h_amount,
          c._16+1)
      }
      val h_data: String = {if (w_name.length > 10) w_name.substring(0, 10) else w_name} + "    " + {if (d_name.length > 10) d_name.substring(0, 10) else d_name}
      NewOrderTxOps.insertHistory(found_c_id,c_d_id,c_w_id,d_id,w_id,datetime,h_amount,h_data)

      val output: StringBuilder = new StringBuilder
      output.append("\n+---------------------------- PAYMENT ----------------------------+")
      .append("\n Date: " + datetime)
      .append("\n\n Warehouse: ").append(w_id)
      .append("\n   Street:  ").append(w_street_1)
      .append("\n   Street:  ").append(w_street_2)
      .append("\n   City:    ").append(w_city)
      .append("   State: ").append(w_state)
      .append("  Zip: ").append(w_zip)
      .append("\n\n District:  ").append(d_id)
      .append("\n   Street:  ").append(d_street_1)
      .append("\n   Street:  ").append(d_street_2)
      .append("\n   City:    ").append(d_city)
      .append("   State: ").append(d_state)
      .append("  Zip: ").append(d_zip)
      .append("\n\n Customer:  ").append(found_c_id)
      .append("\n   Name:    ").append(c._1).append(" ").append(c._2).append(" ").append(c._3)
      .append("\n   Street:  ").append(c._4)
      .append("\n   Street:  ").append(c._5)
      .append("\n   City:    ").append(c._6)
      .append("   State: ").append(c._7)
      .append("  Zip: ").append(c._8)
      .append("\n   Since:   ")
      if (c._10 != null) {
        output.append(c._10)
      }
      else {
        output.append("")
      }
      output.append("\n   Credit:  ").append(c._11)
      .append("\n   %Disc:   ").append(c._13)
      .append("\n   Phone:   ").append(c._9)
      .append("\n\n Amount Paid:      ").append(h_amount)
      .append("\n Credit Limit:     ").append(c._12)
      .append("\n New Cust-Balance: ").append(c._14)
      if (c._11 == "BC") {
        if (c_data.length > 50) {
          output.append("\n\n Cust-Data: ").append(c_data.substring(0, 50))
          val data_chunks: Int = (if (c_data.length > 200) 4 else c_data.length / 50)
          var n: Int = 1
          while (n < data_chunks) {
            output.append("\n            ").append(c_data.substring(n * 50, (n + 1) * 50))
            n += 1
          }
        } else {
          output.append("\n\n Cust-Data: " + c_data)
        }
      }
      output.append("\n+-----------------------------------------------------------------+\n\n")
      println(output.toString)
      0
    } catch {
      case e: Throwable => {
        println("An error occurred in handling Payment transaction for warehouse=%d, district=%d, customer=%d".format(w_id,d_id,c_id))
        1
      }
    }
  }
  object NewOrderTxOps {
    def updateWarehouseYtd(w_id:Int, h_amount:Double) = {
      val (w_name,w_street_1,w_street_2,w_city,w_state,w_zip,w_tax,w_ytd) = SharedData.warehouseTbl(w_id)
      SharedData.onUpdate_Warehouse(w_id,w_name,w_street_1,w_street_2,w_city,w_state,w_zip,w_tax,w_ytd+h_amount)
    }
    def findWarehouse(w_id:Int) = {
      val (w_name,w_street_1,w_street_2,w_city,w_state,w_zip,_,w_ytd) = SharedData.warehouseTbl(w_id)
      (w_name,w_street_1,w_street_2,w_city,w_state,w_zip)
    }
    def updateDistrict(w_id:Int, d_id:Int, h_amount:Double) = {
      val (d_name,d_street_1,d_street_2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id) = SharedData.districtTbl((w_id,d_id))
      SharedData.onUpdate_District(w_id,d_id, d_name,d_street_1,d_street_2,d_city,d_state,d_zip,d_tax,d_ytd+h_amount,d_next_o_id)
    }
    def findDistrict(w_id:Int, d_id:Int) = {
      val (d_name,d_street_1,d_street_2,d_city,d_state,d_zip,_,d_ytd,_) = SharedData.districtTbl((w_id,d_id))
      (d_name,d_street_1,d_street_2,d_city,d_state,d_zip)
    }
    def findCustomerData(c_w_id: Int, c_d_id: Int, c_id: Int) = {
      val (_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,c_data) = SharedData.customerTbl(c_id,c_d_id,c_w_id)
      c_data
    }
    def updateCustomerBalance(c_w_id: Int, c_d_id: Int, c_id: Int, c_balance:Double, c_ytd_payment:Double, c_payment_cnt:Int) = {
      val (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,_,_,_,c_delivery_cnt,c_data) = SharedData.customerTbl((c_id,c_d_id,c_w_id))
      SharedData.onUpdateCustomer(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)
    }
    def updateCustomerBalanceAndData(c_w_id: Int, c_d_id: Int, c_id: Int, c_balance:Double, c_ytd_payment:Double, c_payment_cnt:Int, c_data:String) = {
      val (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,_,_,_,c_delivery_cnt,_) = SharedData.customerTbl((c_id,c_d_id,c_w_id))
      SharedData.onUpdateCustomer(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)
    }
    def insertHistory(h_c_id:Int,h_c_d_id:Int,h_c_w_id:Int,h_d_id:Int,h_w_id:Int,h_date:Date,h_amount:Double,h_data:String) = {
      SharedData.onInsert_HistoryTbl(h_c_id,h_c_d_id,h_c_w_id,h_d_id,h_w_id,h_date,h_amount,h_data)
    }
  }
}

