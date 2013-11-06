package ddbt.tpcc.itx

import java.util.Date

/**
 * NewOrder Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait INewOrder {
  def newOrderTx(datetime:Date, t_num: Int, w_id:Int, d_id:Int, c_id:Int, o_ol_count:Int, o_all_local:Int, itemid:Array[Int], supware:Array[Int], quantity:Array[Int], price:Array[Float], iname:Array[String], stock:Array[Int], bg:Array[Char], amt:Array[Float]): Int
}
