package ddbt.tpcc.itx

import java.util.Date

/**
 * NewOrder Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait INewOrder {
  def newOrderTx(datetime:Date, t_num: Int, w_id:Int, d_id:Int, c_id:Int, o_ol_count:Int, o_all_local:Int, itemid:Array[Int], supware:Array[Int], quantity:Array[Int], price:Array[Double], iname:Array[String], stock:Array[Int], bg:Array[String], amt:Array[Double]): Int
}

/**
 * Payment Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IPayment {
  def paymentTx(datetime:Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_w_id: Int, c_d_id: Int, c_id: Int, c_last: String, h_amount: Double):Int
}

/**
 * OrderStatus Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IOrderStatus {
  def orderStatusTx(datetime:Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_id: Int, c_last: String):Int
}

/**
 * Delivery Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IDelivery {
  def deliveryTx(datetime:Date, w_id: Int, o_carrier_id: Int): Int
}

/**
 * StockLevel Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IStockLevel {
  def stockLevelTx(t_num: Int, w_id: Int, d_id: Int, threshold: Int):Int
}

