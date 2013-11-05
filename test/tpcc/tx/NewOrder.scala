package ddbt.tpcc.tx
import java.io._
import scala.collection.mutable._
import java.util.Date
import ddbt.tpcc.loadtest.TpccUnitTest._

/**
 * NewOrder Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
object NewOrder {
  val r = new scala.util.Random

  //Tables
  //val stockTbl: Map[(Int,Int),(Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String)] = new HashMap[(Int,Int),(Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String)]
  //val newOrderTbl = new HashSet[(Int,Int,Int)]

  //Partial Tables (containing all rows, but not all columns)
  //removed columns are commented out
  //val districtPartialTbl = new HashMap[(Int,Int),(/*String,String,String,String,String,String,*/Double,/*Double,*/Int)]
  //val orderPartialTbl = new HashMap[(Int,Int,Int),(Int,Date/*,Option[Int]*/,Int,Boolean)]
  //val itemPartialTbl = new HashMap[Int,(/*Int,*/String,Double,String)]
  //val orderLinePartialTbl = new HashMap[(Int,Int,Int,Int),(Int,Int/*,Date*/,Int,Double,String)]

  //Materialized query results
  //val customerWarehouseFinancialInfoMap = new HashMap[(Int,Int,Int),(Double, String, String, Double)]

  /**
   * @param w_id is warehouse id
   * @param d_id is district id
   * @param c_id is customer id
   *
   * Table interactions:
   *   - [Warehouse: R] in
   *      + findCustomerWarehouseFinancialInfo
   *   - [District: RW] where R in
   *      + findDistrictInfo
   *     and W in
   *      + updateDistrictNextOrderId
   *   - [Customer: R] in
   *      + findCustomerWarehouseFinancialInfo
   *   - [Order: W] in
   *      + insertOrder
   *   - [NewOrder: W] in
   *      + insertNewOrder
   *   - [Item: R] in
   *      + findItem
   *   - [Stock: RW] where R in
   *      + findStock
   *     and W in
   *      + updateStock
   *   - [OrderLine: W] in
   *      + insertOrderLine
   *
   */
  def newOrderTx(datetime:Date, w_id:Int, d_id:Int, c_id:Int, o_all_local:Boolean, o_ol_count:Int, itemid:Array[Int], supware:Array[Int], quantity:Array[Int], price:Array[Double], iname:Array[String], stock:Array[Int], bg:Array[Char], amt:Array[Double]): Int = {
    try {
      printMapInfo
      println("Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id,d_id,c_id))

      var ol_number = 0
      var failed = false

      while(ol_number < o_ol_count) {
        try {
          NewOrderTxOps.findItem(itemid(ol_number))
        } catch {
          case nsee: java.util.NoSuchElementException => {
            println("An item was not found in handling NewOrder transaction for warehouse=%d, district=%d, customer=%d, items=%s".format(w_id,d_id,c_id, java.util.Arrays.toString(itemid)))
            failed = true
          }
        }
        if(failed) return rollBack
        ol_number += 1
      }

      val (c_discount, c_last, c_credit, w_tax) = NewOrderTxOps.findCustomerWarehouseFinancialInfo(w_id,d_id,c_id)

      val (_,_,_,_,_,_,d_tax,_,d_next_o_id) = NewOrderTxOps.findDistrictInfo(w_id,d_id)

      NewOrderTxOps.updateDistrictNextOrderId(w_id,d_id,d_tax,d_next_o_id+1)

      //no need to copy
      val o_id = d_next_o_id
      
      //var o_all_local:Boolean = true
      //supware.foreach { s_w_id => if(s_w_id != w_id) o_all_local = false }
      //val o_ol_count = supware.length

      NewOrderTxOps.insertOrder(o_id, w_id, d_id, c_id, datetime, o_ol_count, o_all_local)

      NewOrderTxOps.insertNewOrder(o_id, w_id, d_id)

      var total = 0.0

      ol_number = 0
      while(ol_number < o_ol_count) {
        val ol_supply_w_id = supware(ol_number)
        val ol_i_id = itemid(ol_number)
        val ol_quantity = quantity(ol_number)
        
        val (/*_, */i_name, i_price, i_data) = NewOrderTxOps.findItem(ol_i_id)
        price(ol_number) = i_price
        iname(ol_number) = i_name

        val (s_quantity,s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data) = NewOrderTxOps.findStock(ol_supply_w_id, ol_i_id)

        val ol_dist_info = d_id match {
          case 1  => s_dist_01
          case 2  => s_dist_02
          case 3  => s_dist_03
          case 4  => s_dist_04
          case 5  => s_dist_05
          case 6  => s_dist_06
          case 7  => s_dist_07
          case 8  => s_dist_08
          case 9  => s_dist_09
          case 10 => s_dist_10
        }

        stock(ol_number) = s_quantity

        if(i_data.contains("original") && s_data.contains("original")) {
          bg(ol_number) = 'B'
        } else {
          bg(ol_number) = 'G'
        }

        var new_s_quantity = s_quantity - ol_quantity
        if(s_quantity <= ol_quantity) new_s_quantity += 91

        var s_remote_cnt_increment = 0
        if(ol_supply_w_id != w_id) s_remote_cnt_increment = 1

        //TODO this is the correct version but is not implemented in the correctness test
        NewOrderTxOps.updateStock(ol_supply_w_id, ol_i_id, new_s_quantity,s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,
          s_ytd/*+ol_quantity*/,s_order_cnt/*+1*/,s_remote_cnt/*+s_remote_cnt_increment*/, s_data)

        val ol_amount = ol_quantity * i_price * (1+w_tax+d_tax) * (1 - c_discount)
        amt(ol_number) =  ol_amount
        total += ol_amount

        NewOrderTxOps.insertOrderLine(w_id, d_id, o_id, ol_number+1/*to start from 1*/, ol_i_id, ol_supply_w_id, ol_quantity, ol_amount, ol_dist_info)
      
        ol_number += 1
      }

      println("Finished NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id,d_id,c_id))
      printMapInfo


      

      0
    } catch {
      case e: Throwable => {
        println("An error occurred in handling NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id,d_id,c_id))
        throw e
        1
      }
    }
  }

  def rollBack = { 2 }

  def printMapInfo {
    // println("customerWarehouseFinancialInfoMap = %s".format(customerWarehouseFinancialInfoMap))
    // println("districtPartialTbl = %s".format(districtPartialTbl))
  }

  object NewOrderTxOps {
    /**
     * @param w_id is warehouse id
     * @param d_id is district id
     * @param c_id is customer id
     * @return (c_discount, c_last, c_credit, w_tax)
     */
    def findCustomerWarehouseFinancialInfo(w_id:Int, d_id:Int, c_id:Int) = {
      SharedData.customerWarehouseFinancialInfoMap(c_id,d_id,w_id)
    }

    /**
     * @param w_id is warehouse id
     * @param d_id is district id
     * @return (d_next_o_id, d_tax)
     */
    def findDistrictInfo(w_id:Int, d_id:Int) = {
      SharedData.districtTbl(d_id,w_id)
    }

    /**
     * @param w_id is warehouse id
     * @param d_id is district id
     *
     * @param new_d_next_o_id is the next order id
     * @param d_tax is the district tax value for this dirstrict
     */
    def updateDistrictNextOrderId(w_id:Int, d_id:Int, d_tax:Double, new_d_next_o_id:Int): Unit = {
      SharedData.onUpdate_District_forNewOrder(d_id, w_id, d_tax,new_d_next_o_id)
    }

    /**
     * @param w_id is warehouse id
     * @param d_id is district id
     */
    def insertOrder(o_id:Int, w_id:Int, d_id:Int, c_id:Int, o_entry_d:Date, o_ol_cnt:Int, o_all_local:Boolean): Unit = {
      SharedData.onInsert_Order(o_id,d_id,w_id , c_id, o_entry_d, None, o_ol_cnt, o_all_local)
    }

    /**
     * @param w_id is warehouse id
     * @param d_id is district id
     */
    def insertNewOrder(o_id:Int, w_id:Int, d_id:Int): Unit = {
      SharedData.onInsert_NewOrder(o_id,d_id,w_id)
    }

    /**
     * @param item_id is the item id
     */
    def findItem(item_id:Int) = {
      SharedData.itemPartialTbl(item_id)
    }

    /**
     * @param w_id is warehouse id
     */
    def findStock(w_id:Int, item_id:Int) = {
      SharedData.stockTbl((item_id,w_id))
    }

    /**
     * @param w_id is warehouse id
     */
    def updateStock(w_id:Int, item_id:Int, s_quantity:Int, s_dist_01:String, s_dist_02:String, s_dist_03:String, s_dist_04:String, s_dist_05:String, s_dist_06:String, s_dist_07:String, s_dist_08:String, s_dist_09:String, s_dist_10:String, s_ytd:Int, s_order_cnt:Int, s_remote_cnt:Int, s_data:String) = {
      SharedData.onUpdateStock(item_id,w_id, s_quantity, s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data)
    }

    /**
     * @param w_id is warehouse id
     * @param d_id is district id
     */
    def insertOrderLine(w_id:Int, d_id:Int, o_id:Int, ol_number:Int, ol_i_id:Int, ol_supply_w_id:Int, ol_quantity:Int, ol_amount:Double, ol_dist_info:String): Unit = {
      SharedData.onInsertOrderLine(o_id, d_id, w_id, ol_number, ol_i_id, ol_supply_w_id, None, ol_quantity, ol_amount, ol_dist_info)
    }
  }

  // def main(args: Array[String]) {
  //   val w_id = 1
  //   val d_id = 2
  //   val c_id = 3
  //   val item_id = Array[Int](4,5,6)
  //   val supply_w_id = Array[Int](1,1,1)
  //   //orderQuantities
  //   val quantity = Array[Int](10,11,12)
  //   //itemPrices
  //   val price = new Array[Double](3)
  //   //itemNames
  //   val iname = new Array[String](3)
  //   //stockQuantities
  //   val stock = new Array[Int](3)
  //   //brandGeneric
  //   val bg = new Array[Char](3)
  //   //orderLineAmounts
  //   val amount = new Array[Double](3)

  //   // loadDataTables(w_id,d_id,c_id)
  //   // newOrderTx(w_id,d_id,c_id,item_id,supply_w_id,quantity,price,iname,stock,bg,amount)
  // }

  // def loadDataTables(w_id:Int, d_id:Int, c_id:Int) {
  //   val (c_discount, c_last, c_credit, w_tax) = (r.nextDouble, r.nextString(10), if(r.nextBoolean) "BC" else "GC",r.nextDouble)
  //   val (d_next_o_id, d_tax) = (r.nextInt(10000000), r.nextDouble)

  //   customerWarehouseFinancialInfoMap += ((w_id,d_id,c_id) -> (c_discount, c_last, c_credit, w_tax))
  //   districtPartialTbl += ((w_id,d_id) -> (d_tax,d_next_o_id))
  // }
}
