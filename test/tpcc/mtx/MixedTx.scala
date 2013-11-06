package ddbt.tpcc.mtx

import ddbt.tpcc.itx._
import java.util.Date

class NewOrderMixedImpl(val newOrderDB: ddbt.tpcc.loadtest.NewOrder, val newOrderMem: ddbt.tpcc.tx.NewOrder) extends INewOrder {
  override def newOrderTx(datetime:Date, t_num: Int, w_id:Int, d_id:Int, c_id:Int, o_ol_count:Int, o_all_local:Int, itemid:Array[Int], supware:Array[Int], quantity:Array[Int], price:Array[Float], iname:Array[String], stock:Array[Int], bg:Array[Char], amt:Array[Float]): Int = {
    newOrderDB.newOrderTx(datetime,t_num, w_id, d_id, c_id, o_ol_count, o_all_local, itemid, supware, quantity, price, iname, stock, bg, amt)
    newOrderMem.newOrderTx(datetime,t_num, w_id, d_id, c_id, o_ol_count, o_all_local, itemid, supware, quantity, price, iname, stock, bg, amt)
  }
}

class DeliveryMixedImpl(val deliveryDB: ddbt.tpcc.loadtest.Delivery, val deliveryMem: ddbt.tpcc.tx.Delivery) extends IDelivery {
  override def deliveryTx(datetime:Date, w_id: Int, o_carrier_id: Int): Int = {
    deliveryDB.deliveryTx(datetime, w_id, o_carrier_id)
    deliveryMem.deliveryTx(datetime, w_id, o_carrier_id)
  }
}

class OrderStatusMixedImpl(val orderStatusDB: ddbt.tpcc.loadtest.OrderStat, val orderStatusMem: ddbt.tpcc.tx.OrderStatus) extends IOrderStatus {
  override def orderStatusTx(datetime:Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_id: Int, c_last: String):Int = {
    orderStatusDB.orderStatusTx(datetime, t_num, w_id, d_id, c_by_name, c_id, c_last)
    orderStatusMem.orderStatusTx(datetime, t_num, w_id, d_id, c_by_name, c_id, c_last)
  }
}

class PaymentMixedImpl(val paymentDB: ddbt.tpcc.loadtest.Payment, val paymentMem: ddbt.tpcc.tx.Payment) extends IPayment {
  override def paymentTx(datetime:Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_w_id: Int, c_d_id: Int, c_id: Int, c_last: String, h_amount: Float):Int = {
    paymentDB.paymentTx(datetime, t_num, w_id, d_id, c_by_name, c_w_id, c_d_id, c_id, c_last, h_amount)
    paymentMem.paymentTx(datetime, t_num, w_id, d_id, c_by_name, c_w_id, c_d_id, c_id, c_last, h_amount)
  }
}

class StockLevelMixedImpl(val stockLevelDB: ddbt.tpcc.loadtest.Slev, val stockLevelMem: ddbt.tpcc.tx.StockLevel) extends IStockLevel {
  override def stockLevelTx(t_num: Int, w_id: Int, d_id: Int, threshold: Int):Int = {
    stockLevelDB.stockLevelTx(t_num, w_id, d_id, threshold)
    stockLevelMem.stockLevelTx(t_num, w_id, d_id, threshold)
  }
}