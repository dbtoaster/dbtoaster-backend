package ddbt.tpcc.itx

import java.util.Date

/**
 * OrderStatus Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IOrderStatus {
  def orderStatusTx(datetime:Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_id: Int, c_last: String):Int
}
