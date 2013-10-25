package ddbt.experimental
import java.io._
import scala.collection.mutable._
import java.util.Date

/**
 * StockLevel Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
class StockLevel {

  //Partial Tables (containing all rows, but not all columns)
  //removed columns are commented out
  val districtPartialTbl = new HashMap[(Int,Int),(/*String,String,String,String,String,String,Double,Double,*/Int)]

  //Materialized query results

  //Key: orderLine key
  //Value: (ol_i_id,s_quantity)
  val orderLineStockJoin = new HashMap[(Int,Int,Int,Int),(/**OrderLine Fields**/Int/*,Int,Date,Int,Double,String*//**Stock Fields**/,Int/*,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String*/)]

  def stockLevelTransaction(w_id: Int, d_id: Int, threshold: Int):Int= {
    try {
        val o_id = StockLevelTxOps.findDistrictnextOrderId(w_id,d_id)
        val stock_count = StockLevelTxOps.findOrderLineStockRecentItemsUnderThresholds(o_id, threshold)

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
        1
      }
    }
  }

  object StockLevelTxOps {
      def findDistrictnextOrderId(w_id:Int, d_id:Int) = {
        districtPartialTbl(w_id,d_id)
      }

      def findOrderLineStockRecentItemsUnderThresholds(o_id:Int, threshold:Int) = {
        val unique_ol_i_id = new HashSet[Int]
        orderLineStockJoin.foreach { case (ols_k,ols_v) =>
            if(ols_k._1 < o_id && ols_k._1 > (o_id-20) && ols_v._2 < threshold) {
                unique_ol_i_id += ols_v._1
            }
        }
        unique_ol_i_id.size
      }
  }
}

