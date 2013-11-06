package ddbt.tpcc.tx1
import java.io._
import scala.collection.mutable._
import java.util.Date
import ddbt.tpcc.itx._

/**
 * StockLevel Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
class StockLevel extends InMemoryTxImpl with IStockLevelInMem {

  //Partial Tables (containing all rows, but not all columns)
  //removed columns are commented out
  //val districtPartialTbl = new HashMap[(Int,Int),(/*String,String,String,String,String,String,Float,Float,*/Int)]

  //Materialized query results

  //Key: orderLine key
  //Value: (ol_i_id,s_quantity)
  //val orderLineStockJoin = new HashMap[(Int,Int,Int,Int),(/**OrderLine Fields**/Int/*,Int,Date,Int,Float,String*//**Stock Fields**/,Int/*,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String*/)]

  /**
   * @param w_id is warehouse id
   * @param d_id is district id
   * @param threshold is the threshold for the items in stock
   *
   * Table interactions:
   *   - [District: R] n
   *      + findDistrictnextOrderId
   *   - [Stock: R] in
   *      + findOrderLineStockRecentItemsUnderThresholds
   *   - [OrderLine: R] in
   *      + findOrderLineStockRecentItemsUnderThresholds
   *
   */
  override def stockLevelTx(t_num: Int, w_id: Int, d_id: Int, threshold: Int):Int= {
    try {
        val o_id = StockLevelTxOps.findDistrictnextOrderId(w_id,d_id)
        val stock_count = StockLevelTxOps.findOrderLineStockRecentItemsUnderThresholds(w_id, d_id, o_id, threshold)

        val output: StringBuilder = new StringBuilder
        output.append("\n+-------------------------- STOCK-LEVEL --------------------------+")
        output.append("\n Warehouse: ").append(w_id)
        output.append("\n District:  ").append(d_id)
        output.append("\n\n Stock Level Threshold: ").append(threshold)
        output.append("\n Low Stock Count:       ").append(stock_count)
        output.append("\n+-----------------------------------------------------------------+\n\n")
        println(output.toString)
        1
    } catch {
      case e: Throwable => {
        println("An error occurred in handling StockLevel transaction for warehouse=%d, district=%d, threshold=%d".format(w_id,d_id,threshold))
        0
      }
    }
  }

  object StockLevelTxOps {
      def findDistrictnextOrderId(w_id:Int, d_id:Int) = {
        SharedData.districtTbl(d_id,w_id)._9
      }

      def findOrderLineStockRecentItemsUnderThresholds(w_id:Int, d_id:Int, o_id:Int, threshold:Int) = {
        val unique_ol_i_id = new HashSet[Int]
        SharedData.orderLineTbl.foreach { case ((ol_o_id,ol_d_id,ol_w_id,_) ,(ol_i_id,_,_,_,_,_)) =>
          if(ol_w_id==w_id && ol_d_id==d_id && ol_o_id < o_id && ol_o_id>=(o_id-20)) {
            val (s_quantity,_,_,_,_,_,_,_,_,_,_,_,_,_,_) = SharedData.stockTbl(ol_i_id,ol_w_id)
            if(s_quantity < threshold) {
              unique_ol_i_id += ol_i_id
            }
          }
        }

        unique_ol_i_id.size
      }
  }
}

