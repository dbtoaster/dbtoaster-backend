package ddbt.tpcc.itx

import java.util.Date

/**
 * StockLevel Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IStockLevel {
  def stockLevelTx(t_num: Int, w_id: Int, d_id: Int, threshold: Int):Int
}
