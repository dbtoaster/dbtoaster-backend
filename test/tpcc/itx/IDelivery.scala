package ddbt.tpcc.itx

import java.util.Date

/**
 * Delivery Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IDelivery {
  def deliveryTx(datetime:Date, w_id: Int, o_carrier_id: Int): Int
}
