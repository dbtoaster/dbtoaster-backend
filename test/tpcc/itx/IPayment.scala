package ddbt.tpcc.itx

import java.util.Date

/**
 * Payment Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IPayment {
  def paymentTx(datetime:Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_w_id: Int, c_d_id: Int, c_id: Int, c_last: String, h_amount: Float):Int
}
