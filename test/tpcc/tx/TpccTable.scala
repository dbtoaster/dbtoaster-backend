package ddbt.tpcc.tx
import java.io._
import scala.collection.mutable._
import java.util.Date
import java.sql.Connection
import java.sql.Statement
import java.sql.ResultSet
import ddbt.tpcc.loadtest.Util._
import ddbt.tpcc.loadtest.DatabaseConnector._
import ddbt.tpcc.lib.SHMap
import ddbt.tpcc.lib.SEntry
import ddbt.tpcc.lib.SHMapPooled
import ddbt.tpcc.lib.BinaryHeap
import ddbt.tpcc.loadtest.TpccConstants._

/**
 * Delivery Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
class TpccTable {
	//NewOrder: W
	//Delivery: RW

	val newOrderTbl:SHMap[(Int,Int,Int),Boolean] = if(testSpecialDsUsed) {
		null.asInstanceOf[SHMap[(Int,Int,Int),Boolean]]
	} else {
		new SHMap[(Int,Int,Int),Boolean](0.9f, 262144, (k:(Int,Int,Int),v:Boolean) => ((k._2, k._3)) )
	}
	val newOrderSetImpl:SHMap[(Int,Int),BinaryHeap[Int]] = if(testSpecialDsUsed) {
		new SHMapPooled[/*(no_d_id, no_w_id)*/(Int,Int),BinaryHeap[Int]](0.9f, 32)
	} else {
		null.asInstanceOf[SHMap[(Int,Int),BinaryHeap[Int]]]
	}
	if(testSpecialDsUsed) {
		for(i <- 1 to 10) {
			newOrderSetImpl += ((i,1), new BinaryHeap[Int])
		}
	}

	val historyTbl:SHMap[(Int,Int,Int,Int,Int,Date,Float,String),Boolean] = if(testSpecialDsUsed) {
		new SHMapPooled[(Int,Int,Int,Int,Int,Date,Float,String),Boolean](0.9f, 4194304)
	} else {
		new SHMap[(Int,Int,Int,Int,Int,Date,Float,String),Boolean]/*(0.9f, 4194304)*/
	}

	val warehouseTbl:SHMap[Int,(String,String,String,String,String,String,Float,Double)] = if(testSpecialDsUsed) {
		new SHMapPooled[Int,(String,String,String,String,String,String,Float,Double)]
	} else {
		new SHMap[Int,(String,String,String,String,String,String,Float,Double)]
	}

	val itemPartialTbl:SHMap[Int,(/*Int,*/String,Float,String)] = if(testSpecialDsUsed) {
		new SHMapPooled[Int,(/*Int,*/String,Float,String)](1f, 262144)
	} else {
		new SHMap[Int,(/*Int,*/String,Float,String)]/*(1f, 262144)*/
	}

	val orderTbl:SHMap[(Int,Int,Int),(Int,Date,Option[Int],Int,Boolean)] = if(testSpecialDsUsed) {
		new SHMapPooled[(Int,Int,Int),(Int,Date,Option[Int],Int,Boolean)](0.9f, 4194304)
	} else {
		new SHMap[(Int,Int,Int),(Int,Date,Option[Int],Int,Boolean)](/*0.9f, 4194304,*/ (k:(Int,Int,Int), v:(Int,Date,Option[Int],Int,Boolean)) => ((k._2, k._3, v._1)) )
	}

	val orderMaxOrderSetImpl:SHMap[/*(o_d_id, o_w_id, o_c_id)*/(Int,Int,Int),BinaryHeap[Int]] = if(testSpecialDsUsed) {
		new SHMapPooled[/*(o_d_id, o_w_id, o_c_id)*/(Int,Int,Int),BinaryHeap[Int]](0.9f, 65536)
	} else {
		new SHMap[/*(o_d_id, o_w_id, o_c_id)*/(Int,Int,Int),BinaryHeap[Int]]/*(0.9f, 65536)*/
	}

	val districtTbl:SHMap[(Int,Int),(String,String,String,String,String,String,Float,Double,Int)] = if(testSpecialDsUsed) {
		new SHMapPooled[(Int,Int),(String,String,String,String,String,String,Float,Double,Int)](1f, 32)
	} else {
		new SHMap[(Int,Int),(String,String,String,String,String,String,Float,Double,Int)]/*(1f, 32)*/
	}

	val orderLineTbl:SHMap[(Int,Int,Int,Int),(Int,Int,Option[Date],Int,Float,String)] = if(testSpecialDsUsed) {
		new SHMapPooled[(Int,Int,Int,Int),(Int,Int,Option[Date],Int,Float,String)](0.9f, 33554432, List((0.9f, 4194304)), (k:(Int,Int,Int,Int), v:(Int,Int,Option[Date],Int,Float,String)) => ((k._1, k._2, k._3)) )
	} else {
		new SHMap[(Int,Int,Int,Int),(Int,Int,Option[Date],Int,Float,String)](/*0.9f, 33554432, List((0.9f, 4194304)),*/ (k:(Int,Int,Int,Int), v:(Int,Int,Option[Date],Int,Float,String)) => ((k._1, k._2, k._3)) )
	}
	val customerTbl:SHMap[(Int,Int,Int),(String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String)] = if(testSpecialDsUsed) {
		new SHMapPooled[(Int,Int,Int),(String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String)] (/*1f, 65536, List((1f, 16384)),*/ (k:(Int,Int,Int), v:(String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String)) => ((k._2, k._3, v._3)) )
	} else {
		new SHMap[(Int,Int,Int),(String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String)] (/*1f, 65536, List((1f, 16384)),*/ (k:(Int,Int,Int), v:(String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String)) => ((k._2, k._3, v._3)) )
	}
	val stockTbl:SHMap[(Int,Int),(Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String)] = if(testSpecialDsUsed) {
		new SHMapPooled[(Int,Int),(Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String)](1f, 262144)
	} else {
		new SHMap[(Int,Int),(Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String)]/*(1f, 262144)*/
	}

	val customerWarehouseFinancialInfoMap:SHMap[(Int,Int,Int),(Float,String,String,Float)] = if(testSpecialDsUsed) {
		new SHMapPooled[(Int,Int,Int),(Float,String,String,Float)](1f, 65536)
	} else {
		new SHMap[(Int,Int,Int),(Float,String,String,Float)]/*(1f, 65536)*/
	}

	def testSpecialDsUsed = IN_MEMORY_IMPL_VERSION_UNDER_TEST >= 5

	def onInsert_NewOrder(no_o_id:Int, no_d_id:Int, no_w_id:Int) = {
		if(testSpecialDsUsed) {
			newOrderSetImpl((no_d_id, no_w_id)).add(no_o_id)
		} else {
			newOrderTbl += ((no_o_id, no_d_id, no_w_id), (true))
		}
	}

	def onDelete_NewOrder(no_o_id:Int, no_d_id:Int, no_w_id:Int) = {
		if(testSpecialDsUsed) {
			if(newOrderSetImpl((no_d_id, no_w_id)).remove != no_o_id) {
				throw new RuntimeException("Some operations executed out of order => newOrderSetImpl((%d,%d)).remove != %d".format(no_d_id, no_w_id, no_o_id))
			}
		} else {
			newOrderTbl -= ((no_o_id, no_d_id, no_w_id))
		}
	}

	def onInsert_HistoryTbl(h_c_id:Int, h_c_d_id:Int, h_c_w_id:Int, h_d_id:Int, h_w_id:Int, h_date:Date, h_amount:Float, h_data:String) = {
		historyTbl += ((h_c_id,h_c_d_id,h_c_w_id,h_d_id,h_w_id,roundDate(h_date),h_amount,h_data), (true))
	}

	def onInsert_Item(i_id:Int, i_im_id:Int, i_name:String, i_price:Float, i_data:String) = {
		itemPartialTbl += (i_id, ((/*i_im_id,*/i_name,i_price,i_data)))
	}

	def onInsert_Order(o_id:Int, o_d_id:Int, o_w_id:Int, o_c_id:Int, o_entry_d:Date, o_carrier_id:Option[Int], o_ol_cnt:Int, o_all_local:Boolean) = {
		orderTbl += ((o_id,o_d_id,o_w_id), (o_c_id,o_entry_d,o_carrier_id,o_ol_cnt,o_all_local))
		if(testSpecialDsUsed) {
			orderMaxOrderSetImpl((o_d_id, o_w_id,o_c_id)).add(o_id)
		}
	}

	def onUpdate_Order_forDelivery(o_id:Int, o_d_id:Int, o_w_id:Int, o_c_id:Int/*, o_entry_d:Date*/, o_carrier_id:Option[Int]/*, o_ol_cnt:Int, o_all_local:Boolean*/) = {
		orderTbl.update((o_id,o_d_id,o_w_id),(currentVal/*:(Int, java.util.Date, Option[Int], Int, Boolean))*/ => ((o_c_id,currentVal._2,o_carrier_id,currentVal._4,currentVal._5))))
	}

	def onUpdate_Order_byFunc(o_id:Int, o_d_id:Int, o_w_id:Int, updateFunc:((Int, Date, Option[Int], Int, Boolean)) => (Int, Date, Option[Int], Int, Boolean)) = {
		orderTbl.update((o_id,o_d_id,o_w_id),updateFunc)
	}

	def onInsert_Warehouse(w_id:Int, w_name:String, w_street_1:String, w_street_2:String, w_city:String, w_state:String, w_zip:String, w_tax:Float, w_ytd:Double) = {
		warehouseTbl += (w_id, (w_name,w_street_1,w_street_2,w_city,w_state,w_zip,w_tax,w_ytd))
	}

	def onUpdate_Warehouse(w_id:Int, w_name:String, w_street_1:String, w_street_2:String, w_city:String, w_state:String, w_zip:String, w_tax:Float, w_ytd:Double) = {
		warehouseTbl.updateVal(w_id,(w_name,w_street_1,w_street_2,w_city,w_state,w_zip,w_tax,w_ytd))
	}

	def onUpdate_Warehouse_byFunc(w_id:Int, updateFunc:((String, String, String, String, String, String, Float, Double)) => (String, String, String, String, String, String, Float, Double)) = {
		warehouseTbl.update(w_id,updateFunc)
	}

	def onInsert_District(d_id:Int, d_w_id:Int, d_name:String, d_street1:String, d_street2:String, d_city:String, d_state:String, d_zip:String, d_tax:Float, d_ytd:Double, d_next_o_id:Int) = {
		districtTbl += ((d_id,d_w_id), (d_name,d_street1,d_street2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id))
	}

	def onUpdate_District(d_id:Int, d_w_id:Int, d_name:String, d_street1:String, d_street2:String, d_city:String, d_state:String, d_zip:String, d_tax:Float, d_ytd:Double, d_next_o_id:Int) = {
		districtTbl.updateVal((d_id,d_w_id), (d_name,d_street1,d_street2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id))
	}

	def onUpdate_District_forNewOrder(d_id:Int, d_w_id:Int/*, d_name:String, d_street1:String, d_street2:String, d_city:String, d_state:String, d_zip:String*/, d_tax:Float/*, d_ytd:Float*/, d_next_o_id:Int) = {
		val (d_name,d_street1,d_street2,d_city,d_state,d_zip,_,d_ytd,_) = districtTbl(d_id,d_w_id)
		onUpdate_District(d_id,d_w_id, d_name,d_street1,d_street2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id)
	}

	def onUpdate_District_byFunc(d_id:Int, d_w_id:Int, updateFunc:((String, String, String, String, String, String, Float, Double, Int)) => (String, String, String, String, String, String, Float, Double, Int)) = {
		districtTbl.update((d_id,d_w_id), updateFunc)
	}

	def onInsertOrderLine(ol_o_id:Int, ol_d_id:Int, ol_w_id:Int, ol_number:Int, ol_i_id:Int, ol_supply_w_id:Int, ol_delivery_d:Option[Date], ol_quantity:Int, ol_amount:Float, ol_dist_info:String): Unit = {
      orderLineTbl += ((ol_o_id, ol_d_id, ol_w_id, ol_number), (ol_i_id, ol_supply_w_id, ol_delivery_d, ol_quantity, ol_amount, ol_dist_info))
    }

	def onUpdateOrderLine(ol_o_id:Int, ol_d_id:Int, ol_w_id:Int, ol_number:Int, ol_i_id:Int, ol_supply_w_id:Int, ol_delivery_d:Option[Date], ol_quantity:Int, ol_amount:Float, ol_dist_info:String): Unit = {
      orderLineTbl.updateVal((ol_o_id, ol_d_id, ol_w_id, ol_number) , (ol_i_id, ol_supply_w_id, ol_delivery_d, ol_quantity, ol_amount, ol_dist_info))
    }

    def onInsertCustomer(c_id: Int, c_d_id: Int, c_w_id: Int, c_first:String, c_middle:String, c_last:String, c_street_1:String, c_street_2:String, c_city:String, c_state:String, c_zip:String, c_phone:String, c_since:Date, c_credit:String, c_credit_lim:Float, c_discount:Float, c_balance:Float, c_ytd_payment:Float, c_payment_cnt:Int, c_delivery_cnt:Int, c_data:String) = {
      customerTbl += ((c_id,c_d_id,c_w_id), (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data))
      val (_,_,_,_,_,_,w_tax,_) = warehouseTbl(c_w_id)
      customerWarehouseFinancialInfoMap += ((c_id,c_d_id,c_w_id), (c_discount, c_last, c_credit, w_tax))

      if(testSpecialDsUsed) {
        for(i <- 1 to 10) {
          orderMaxOrderSetImpl += ((i,1,c_id), new BinaryHeap[Int](true))
        }
      }
    }

    def onUpdateCustomer(c_id: Int, c_d_id: Int, c_w_id: Int, c_first:String, c_middle:String, c_last:String, c_street_1:String, c_street_2:String, c_city:String, c_state:String, c_zip:String, c_phone:String, c_since:Date, c_credit:String, c_credit_lim:Float, c_discount:Float, c_balance:Float, c_ytd_payment:Float, c_payment_cnt:Int, c_delivery_cnt:Int, c_data:String) = {
      customerTbl.updateVal((c_id,c_d_id,c_w_id),(c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data))
    }

    def onUpdateCustomer_byFunc(c_id: Int, c_d_id: Int, c_w_id: Int, updateFunc:((String, String, String, String, String, String, String, String, String, Date, String, Float, Float, Float, Float, Int, Int, String)) => (String, String, String, String, String, String, String, String, String, Date, String, Float, Float, Float, Float, Int, Int, String)) = {
      customerTbl.update((c_id,c_d_id,c_w_id),updateFunc)
    }

    def onInsertStock(s_i_id:Int, s_w_id:Int, s_quantity:Int, s_dist_01:String, s_dist_02:String, s_dist_03:String, s_dist_04:String, s_dist_05:String, s_dist_06:String, s_dist_07:String, s_dist_08:String, s_dist_09:String, s_dist_10:String, s_ytd:Int, s_order_cnt:Int, s_remote_cnt:Int, s_data:String) = {
      stockTbl += ((s_i_id,s_w_id), (s_quantity, s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data))
    }

    def onUpdateStock(s_i_id:Int, s_w_id:Int, s_quantity:Int, s_dist_01:String, s_dist_02:String, s_dist_03:String, s_dist_04:String, s_dist_05:String, s_dist_06:String, s_dist_07:String, s_dist_08:String, s_dist_09:String, s_dist_10:String, s_ytd:Int, s_order_cnt:Int, s_remote_cnt:Int, s_data:String) = {
      stockTbl.updateVal((s_i_id,s_w_id), (s_quantity, s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data))
    }

    def onUpdateStock_byFunc(s_i_id:Int, s_w_id:Int, updateFunc:((Int, String, String, String, String, String, String, String, String, String, String, Int, Int, Int, String)) => (Int, String, String, String, String, String, String, String, String, String, String, Int, Int, Int, String)) = {
      stockTbl.update((s_i_id,s_w_id), updateFunc)
    }

	class MiniCustomer(val cust_id:Int, val cust_first:String) extends Ordered[MiniCustomer] {
		def compare(that: MiniCustomer) = this.cust_first.compareToIgnoreCase(that.cust_first)
		override def toString = "MiniCustomer(%s,%s)".format(cust_id, cust_first)
	} 

    def findCustomerEntryByName(input_c_w_id: Int, input_c_d_id: Int, input_c_last: String) = {
      var customers = new ArrayBuffer[MiniCustomer]
      //we should slice over input_c_last
      customerTbl.slice(0, (input_c_d_id, input_c_w_id, input_c_last)).foreach { case ((c_id,_,_) , (c_first,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_)) =>
          customers += new MiniCustomer(c_id,c_first)
      }
      if (customers.size == 0) {
        throw new RuntimeException("The customer C_LAST=" + input_c_last + " C_D_ID=" + input_c_d_id + " C_W_ID=" + input_c_w_id + " not found!")
      }
      // println("**********************************")
      // println("Customers before:",customers)
      customers = customers.sorted
      // println("Customers after:",customers)
      // println("**********************************")
      var index: Int = customers.size / 2
      if (customers.size % 2 == 0) {
        index -= 1
      }
      val c_id = customers(index).cust_id
      customerTbl.getEntry((c_id,input_c_d_id,input_c_w_id))
    }
    def findCustomerEntryById(input_c_w_id: Int, input_c_d_id: Int, c_id: Int) = {
      customerTbl.getEntry((c_id,input_c_d_id,input_c_w_id))
    }

    def findCustomerByName(input_c_w_id: Int, input_c_d_id: Int, input_c_last: String) = {
      var customers = new ArrayBuffer[MiniCustomer]
      //we should slice over input_c_last
      customerTbl.slice(0, (input_c_d_id, input_c_w_id, input_c_last)).foreach { case ((c_id,_,_) , (c_first,_,c_last,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_)) =>
        customers += new MiniCustomer(c_id,c_first)
      }
      if (customers.size == 0) {
        throw new RuntimeException("The customer C_LAST=" + input_c_last + " C_D_ID=" + input_c_d_id + " C_W_ID=" + input_c_w_id + " not found!")
      }
      // println("**********************************")
      // println("Customers before:",customers)
      customers = customers.sorted
      // println("Customers after:",customers)
      // println("**********************************")
      var index: Int = customers.size / 2
      if (customers.size % 2 == 0) {
        index -= 1
      }
      val c_id = customers(index).cust_id
      val (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data) = customerTbl((c_id,input_c_d_id,input_c_w_id))
      (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data,c_id)
    }
    def findCustomerById(input_c_w_id: Int, input_c_d_id: Int, c_id: Int) = {
      val (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data) = customerTbl((c_id,input_c_d_id,input_c_w_id))
      (c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data,c_id)
    }

    def wareHouseCmp(t1:Product, t2:Product) = {
		val v1 = t1.asInstanceOf[(String,String,String,String,String,String,Float,Double)]
		val v2 = t2.asInstanceOf[(String,String,String,String,String,String,Float,Double)]
		// println("\t------------------------------------------")
		// println("\t(v1._1(%s) equals v2._1(%s)) = %s".format(v1._1, v2._1,(v1._1 equals v2._1)))
		// println("\t(v1._2(%s) equals v2._2(%s)) = %s".format(v1._2, v2._2,(v1._2 equals v2._2)))
		// println("\t(v1._3(%s) equals v2._3(%s)) = %s".format(v1._3, v2._3,(v1._3 equals v2._3)))
		// println("\t(v1._4(%s) equals v2._4(%s)) = %s".format(v1._4, v2._4,(v1._4 equals v2._4)))
		// println("\t(v1._5(%s) equals v2._5(%s)) = %s".format(v1._5, v2._5,(v1._5 equals v2._5)))
		// println("\t(v1._6(%s) equals v2._6(%s)) = %s".format(v1._6, v2._6,(v1._6 equals v2._6)))
		// println("\tfloatEq(v1._7(%s), v2._7(%s)) = %s".format(v1._7, v2._7,floatEq(v1._7,v2._7)))
		// println("\tfloatEq(v1._8(%s), v2._8(%s)) = %s , Math.abs(v1._8-v2._8) = %s".format(v1._8, v2._8,floatEq(v1._8,v2._8),Math.abs(v1._8-v2._8)))
		// println("\t##########################################")
		((v1._1 equals v2._1) && (v1._2 equals v2._2) && (v1._3 equals v2._3) && (v1._4 equals v2._4) && (v1._5 equals v2._5) && (v1._6 equals v2._6) && floatEq(v1._7,v2._7) && doubleEq(v1._8,v2._8))
	}

	def itemCmp(t1:Product, t2:Product) = {
		val v1 = t1.asInstanceOf[(/*Int,*/String,Float,String)]
		val v2 = t2.asInstanceOf[(/*Int,*/String,Float,String)]
		((v1._1 equals v2._1) && floatEq(v1._2,v2._2) && (v1._3 equals v2._3))
	}

	def orderCmp(t1:Product, t2:Product) = {
		val v1 = t1.asInstanceOf[(Int,Date,Option[Int],Int,Boolean)]
		val v2 = t2.asInstanceOf[(Int,Date,Option[Int],Int,Boolean)]
		((v1._1 == v2._1) && (v1._3 eq v2._3) && (v1._4 == v2._4) && (v1._5 == v2._5) && dateEq(v1._2,v2._2))
	}

	def districtCmp(t1:Product, t2:Product) = {
		val v1 = t1.asInstanceOf[(String,String,String,String,String,String,Float,Double,Int)]
		val v2 = t2.asInstanceOf[(String,String,String,String,String,String,Float,Double,Int)]
		// println("\t------------------------------------------")
		// println("\t(v1._1(%s) equals v2._1(%s)) = %s".format(v1._1, v2._1,(v1._1 equals v2._1)))
		// println("\t(v1._2(%s) equals v2._2(%s)) = %s".format(v1._2, v2._2,(v1._2 equals v2._2)))
		// println("\t(v1._3(%s) equals v2._3(%s)) = %s".format(v1._3, v2._3,(v1._3 equals v2._3)))
		// println("\t(v1._4(%s) equals v2._4(%s)) = %s".format(v1._4, v2._4,(v1._4 equals v2._4)))
		// println("\t(v1._5(%s) equals v2._5(%s)) = %s".format(v1._5, v2._5,(v1._5 equals v2._5)))
		// println("\t(v1._6(%s) equals v2._6(%s)) = %s".format(v1._6, v2._6,(v1._6 equals v2._6)))
		// println("\tfloatEq(v1._7(%s), v2._7(%s)) = %s".format(v1._7, v2._7,floatEq(v1._7,v2._7)))
		// println("\tfloatEq(v1._8(%s), v2._8(%s)) = %s , Math.abs(v1._8-v2._8) = %s".format(v1._8, v2._8,floatEq(v1._8,v2._8),Math.abs(v1._8-v2._8)))
		// println("\t(v1._9(%s) == v2._9(%s)) = %s".format(v1._9, v2._9,(v1._9 == v2._9)))
		// println("\t##########################################")
		((v1._1 equals v2._1) && (v1._2 equals v2._2) && (v1._3 equals v2._3) && (v1._4 equals v2._4) && (v1._5 equals v2._5) && (v1._6 equals v2._6) && floatEq(v1._7,v2._7) && doubleEq(v1._8,v2._8) && (v1._9 == v2._9))
	}

	def orderLineCmp(t1:Product, t2:Product) = {
		val v1 = t1.asInstanceOf[(Int,Int,Option[Date],Int,Float,String)]
		val v2 = t2.asInstanceOf[(Int,Int,Option[Date],Int,Float,String)]
		if((v1._1 == v2._1) && (v1._2 == v2._2) && (v1._4 == v2._4) && floatEq(v1._5,v2._5) && (v1._6 equals v2._6)) {
			((v1._3,v2._3)) match {
				case (Some(d1), Some(d2)) => dateEq(d1,d2)
				case (None, None) => true
				case _ => false
			}
		} else {
			// println("\t(v1._1 == v2._1) = %s".format((v1._1 == v2._1)))
			// println("\t(v1._2 == v2._2) = %s".format((v1._2 == v2._2)))
			// println("\t(v1._4 == v2._4) = %s".format((v1._4 == v2._4)))
			// println("\tdateEq(v1._5, v2._5) = %s".format({((v1._3,v2._3)) match {
			// 	case (Some(d1), Some(d2)) => dateEq(d1,d2)
			// 	case (None, None) => true
			// 	case _ => false
			// }}))
			// println("\t(v1._5,v2._5) = %s".format(floatEq(v1._5,v2._5)))
			// println("\t(v1._6 eq v2._6) = %s".format((v1._6 equals v2._6)))
			false
		}
	}

	def customerCmp(t1:Product, t2:Product) = {
		val v1 = t1.asInstanceOf[(String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String)]
		val v2 = t2.asInstanceOf[(String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String)]
		// println("\t------------------------------------------")
		// println("\t(v1._1(%s) equals v2._1(%s)) = %s".format(v1._1, v2._1,(v1._1 equals v2._1)))
		// println("\t(v1._2(%s) equals v2._2(%s)) = %s".format(v1._2, v2._2,(v1._2 equals v2._2)))
		// println("\t(v1._3(%s) equals v2._3(%s)) = %s".format(v1._3, v2._3,(v1._3 equals v2._3)))
		// println("\t(v1._4(%s) equals v2._4(%s)) = %s".format(v1._4, v2._4,(v1._4 equals v2._4)))
		// println("\t(v1._5(%s) equals v2._5(%s)) = %s".format(v1._5, v2._5,(v1._5 equals v2._5)))
		// println("\t(v1._6(%s) equals v2._6(%s)) = %s".format(v1._6, v2._6,(v1._6 equals v2._6)))
		// println("\t(v1._7(%s) equals v2._7(%s)) = %s".format(v1._7, v2._7,(v1._7 equals v2._7)))
		// println("\t(v1._8(%s) equals v2._8(%s)) = %s".format(v1._8, v2._8,(v1._8 equals v2._8)))
		// println("\t(v1._9(%s) equals v2._9(%s)) = %s".format(v1._9, v2._9,(v1._9 equals v2._9)))
		// println("\tdateEq(v1._10(%s), v2._10(%s)) = %s".format(v1._10, v2._10, dateEq(v1._10, v2._10)))
		// println("\t(v1._11(%s) equals v2._11(%s)) = %s".format(v1._11, v2._11, (v1._11 equals v2._11)))
		// println("\tfloatEq(v1._12(%.2f), v2._12(%.2f)) = %s".format(v1._12, v2._12, floatEq(v1._12, v2._12)))
		// println("\tfloatEq(v1._13(%.2f), v2._13(%.2f)) = %s".format(v1._13, v2._13, floatEq(v1._13, v2._13)))
		// println("\tfloatEq(v1._14(%.2f), v2._14(%.2f)) = %s".format(v1._14, v2._14, floatEq(v1._14, v2._14)))
		// println("\tfloatEq(v1._15(%.2f), v2._15(%.2f)) = %s".format(v1._15, v2._15, floatEq(v1._15, v2._15)))
		// println("\t(v1._16(%s) == v2._16(%s)) = %s".format(v1._16, v2._16, (v1._16 == v2._16)))
		// println("\t(v1._17(%s) == v2._17(%s)) = %s".format(v1._17, v2._17, (v1._17 == v2._17)))
		// println("\t(v1._18(%s) equals v2._18(%s)) = %s".format(v1._18, v2._18, (v1._18 equals v2._18)))
		// println("\t##########################################")
		((v1._1 equals v2._1) && (v1._2 equals v2._2) && (v1._3 equals v2._3) && (v1._4 equals v2._4) && (v1._5 equals v2._5) && (v1._6 equals v2._6) && (v1._7 equals v2._7) && (v1._8 equals v2._8) && (v1._9 equals v2._9) && dateEq(v1._10, v2._10) && (v1._11 equals v2._11) && floatEq(v1._12, v2._12) && floatEq(v1._13, v2._13) && floatEq(v1._14, v2._14) && floatEq(v1._15, v2._15) && (v1._16 == v2._16) && (v1._17 == v2._17) && (v1._18 equals v2._18))
	}

	def stockCmp(t1:Product, t2:Product) = {
		// val v1 = t1.asInstanceOf[(Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String)]
		// val v2 = t2.asInstanceOf[(Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String)]
		// println("\t(v1._1 == v2._1) = %s".format((v1._1 == v2._1)))
		// println("\t(v1._2 equals v2._2) = %s".format((v1._2 equals v2._2)))
		// println("\t(v1._3 equals v2._3) = %s".format((v1._3 equals v2._3)))
		// println("\t(v1._4 equals v2._4) = %s".format((v1._4 equals v2._4)))
		// println("\t(v1._5 equals v2._5) = %s".format((v1._5 equals v2._5)))
		// println("\t(v1._6 equals v2._6) = %s".format((v1._6 equals v2._6)))
		// println("\t(v1._7 equals v2._7) = %s".format((v1._7 equals v2._7)))
		// println("\t(v1._8 equals v2._8) = %s".format((v1._8 equals v2._8)))
		// println("\t(v1._9 equals v2._9) = %s".format((v1._9 equals v2._9)))
		// println("\t(v1._10 equals v2._10) = %s".format((v1._10 equals v2._10)))
		// println("\t(v1._11 equals v2._11) = %s".format((v1._11 equals v2._11)))
		// println("\t(v1._12 == v2._12) = %s".format((v1._12 == v2._12)))
		// println("\t(v1._13 == v2._13) = %s".format((v1._13 == v2._13)))
		// println("\t(v1._14 == v2._14) = %s".format((v1._14 == v2._14)))
		// println("\t(v1._15 equals v2._15) = %s".format((v1._15 equals v2._15)))
		// ((v1._1 == v2._1) && (v1._2 equals v2._2) && (v1._3 equals v2._3) && (v1._4 equals v2._4) && (v1._5 equals v2._5) && (v1._6 equals v2._6) && (v1._7 equals v2._7) && (v1._8 equals v2._8) && (v1._9 equals v2._9) && (v1._10 equals v2._10) && (v1._11 equals v2._11) && (v1._12 == v2._12) && (v1._13 == v2._13) && (v1._14 == v2._14) && (v1._15 equals v2._15))
		defaultCmp(t1,t2)
	}

	def defaultCmp(t1:Product, t2:Product) = (t1 equals t2)

	def defaultCmpSimpleVal[V](t1:V, t2:V) = (t1 == t2)

    override def equals(o: Any) : Boolean = {
    	if(o.isInstanceOf[TpccTable]) {
	    	val other = o.asInstanceOf[TpccTable]
	    	if(
	    		( (testSpecialDsUsed && (newOrderSetImpl equals other.newOrderSetImpl)) || (!testSpecialDsUsed && ((newOrderTbl equals other.newOrderTbl) || deepEqual(newOrderTbl, other.newOrderTbl, defaultCmpSimpleVal[Boolean]))) ) &&
				((historyTbl equals other.historyTbl) || deepEqual(historyTbl, other.historyTbl, defaultCmpSimpleVal[Boolean])) &&
				((warehouseTbl equals other.warehouseTbl) || deepEqual(warehouseTbl, other.warehouseTbl, wareHouseCmp)) &&
				((itemPartialTbl equals other.itemPartialTbl) || deepEqual(itemPartialTbl, other.itemPartialTbl, itemCmp)) &&
				((orderTbl equals other.orderTbl) || deepEqual(orderTbl, other.orderTbl, orderCmp)) &&
				((districtTbl equals other.districtTbl) || deepEqual(districtTbl, other.districtTbl, districtCmp)) &&
				((orderLineTbl equals other.orderLineTbl) || deepEqual(orderLineTbl, other.orderLineTbl, orderLineCmp)) &&
				((customerTbl equals other.customerTbl) || deepEqual(customerTbl, other.customerTbl, customerCmp)) &&
				((stockTbl equals other.stockTbl) || deepEqual(stockTbl, other.stockTbl, stockCmp))
			) true else {
				var valx = false
				valx = (!testSpecialDsUsed && ((newOrderTbl equals other.newOrderTbl) || deepEqual(newOrderTbl, other.newOrderTbl, defaultCmpSimpleVal[Boolean])) ) || (testSpecialDsUsed && (newOrderSetImpl equals other.newOrderSetImpl))
				println("\n(newOrderTbl equals other.newOrderTbl) => %s".format(valx))
				if(!testSpecialDsUsed && !valx) {
					showDiff(newOrderTbl , other.newOrderTbl, defaultCmp)
				} else if(testSpecialDsUsed) {
					val addedElements: SHMap[(Int,Int),BinaryHeap[Int]] = new SHMap[(Int,Int),BinaryHeap[Int]]
			    	val removedElements: SHMap[(Int,Int),BinaryHeap[Int]] = new SHMap[(Int,Int),BinaryHeap[Int]]
			    	other.newOrderSetImpl.foreach{ case (k,v) =>
			    		if(!newOrderSetImpl.contains(k) || (!(newOrderSetImpl(k) equals v) && (v != newOrderSetImpl(k)))) {
			    			addedElements += (k, v)
			    		}
			    	}
			    	newOrderSetImpl.foreach{ case (k,v) =>
			    		if(!other.newOrderSetImpl.contains(k) || (!(other.newOrderSetImpl(k) equals v) && (v != newOrderSetImpl(k)))) {
			    			removedElements += (k, v)
			    		}
			    	}
			    	println("added elements => %s".format(addedElements))
			    	println("removed elements => %s".format(removedElements))
				}
				valx = (historyTbl equals other.historyTbl) || deepEqual(historyTbl, other.historyTbl, defaultCmpSimpleVal[Boolean])
				println("(historyTbl equals other.historyTbl) => %s".format(valx))
				if(!valx) {
					showDiff(historyTbl , other.historyTbl, defaultCmp)
				}
				valx = ((warehouseTbl equals other.warehouseTbl) || deepEqual(warehouseTbl, other.warehouseTbl, wareHouseCmp))
				println("(warehouseTbl equals other.warehouseTbl) => %s".format(valx))
				if(!valx) {
					showDiff(warehouseTbl , other.warehouseTbl, wareHouseCmp)
				}
				valx = ((itemPartialTbl equals other.itemPartialTbl) || deepEqual(itemPartialTbl, other.itemPartialTbl, itemCmp))
				println("(itemPartialTbl equals other.itemPartialTbl) => %s".format(valx))
				if(!valx) {
					showDiff(itemPartialTbl , other.itemPartialTbl, itemCmp)
				}
				valx = ((orderTbl equals other.orderTbl) || deepEqual(orderTbl, other.orderTbl, orderCmp))
				println("(orderTbl equals other.orderTbl) => %s".format(valx))
				if(!valx) {
					showDiff(orderTbl , other.orderTbl, orderCmp)
				}
				valx = ((districtTbl equals other.districtTbl) || deepEqual(districtTbl, other.districtTbl, districtCmp))
				println("(districtTbl equals other.districtTbl) => %s".format(valx))
				if(!valx) {
					showDiff(districtTbl , other.districtTbl, districtCmp)
				}
				valx = ((orderLineTbl equals other.orderLineTbl) || deepEqual(orderLineTbl, other.orderLineTbl, orderLineCmp))
				println("(orderLineTbl equals other.orderLineTbl) => %s".format(valx))
				if(!valx) {
					showDiff(orderLineTbl , other.orderLineTbl, orderLineCmp)
				}
				valx = ((customerTbl equals other.customerTbl) || deepEqual(customerTbl, other.customerTbl, customerCmp))
				println("(customerTbl equals other.customerTbl) => %s".format(valx))
				if(!valx) {
					showDiff(customerTbl , other.customerTbl, customerCmp)
				}
				valx = ((stockTbl equals other.stockTbl) || deepEqual(stockTbl, other.stockTbl, stockCmp))
				println("(stockTbl equals other.stockTbl) => %s".format(valx))
				if(!valx) {
					showDiff(stockTbl , other.stockTbl, stockCmp)
				}
	    		false
	    	}
	    } else false
    }

    def loadDataIntoMaps(driverClassName:String, jdbcUrl:String, db_user:String, db_password:String) = {
    	
    	val conn = connectToDB(driverClassName,jdbcUrl,db_user,db_password)
    	var stmt:Statement = null
		var rs:ResultSet = null
    	try {
	        stmt = conn.createStatement();

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_WAREHOUSES);
	        while (rs.next()) {
	        	onInsert_Warehouse(
	        		rs.getInt("w_id"),
					rs.getString("w_name"),
					rs.getString("w_street_1"),
					rs.getString("w_street_2"),
					rs.getString("w_city"),
					rs.getString("w_state"),
					rs.getString("w_zip"),
					rs.getFloat("w_tax"),
					rs.getDouble("w_ytd")
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_CUSTOMERS);
	        while (rs.next()) {
	        	onInsertCustomer(
	        		rs.getInt("c_id"),
					rs.getInt("c_d_id"),
					rs.getInt("c_w_id"),
					rs.getString("c_first"),
					rs.getString("c_middle"),
					rs.getString("c_last"),
					rs.getString("c_street_1"),
					rs.getString("c_street_2"),
					rs.getString("c_city"),
					rs.getString("c_state"),
					rs.getString("c_zip"),
					rs.getString("c_phone"),
					rs.getTimestamp("c_since"),
					rs.getString("c_credit"),
					rs.getFloat("c_credit_lim"),
					rs.getFloat("c_discount"),
					rs.getFloat("c_balance"),
					rs.getFloat("c_ytd_payment"),
					rs.getInt("c_payment_cnt"),
					rs.getInt("c_delivery_cnt"),
					rs.getString("c_data")
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_DISTRICTS);
	        while (rs.next()) {
	        	onInsert_District(
					rs.getInt("d_id"),
					rs.getInt("d_w_id"),
					rs.getString("d_name"),
					rs.getString("d_street_1"),
					rs.getString("d_street_2"),
					rs.getString("d_city"),
					rs.getString("d_state"),
					rs.getString("d_zip"),
					rs.getFloat("d_tax"),
					rs.getDouble("d_ytd"),
					rs.getInt("d_next_o_id")
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_HISTORIES);
	        while (rs.next()) {
	        	onInsert_HistoryTbl(
	        		rs.getInt("h_c_id"),
					rs.getInt("h_c_d_id"),
					rs.getInt("h_c_w_id"),
					rs.getInt("h_d_id"),
					rs.getInt("h_w_id"),
					rs.getTimestamp("h_date"),
					rs.getFloat("h_amount"),
					rs.getString("h_data")
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_ITEMS);
	        while (rs.next()) {
	        	onInsert_Item(
	        		rs.getInt("i_id"),
					rs.getInt("i_im_id"),
					rs.getString("i_name"),
					rs.getFloat("i_price"),
					rs.getString("i_data")
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_NEW_ORDERS);
	        while (rs.next()) {
	        	onInsert_NewOrder(
	        		rs.getInt("no_o_id"),
					rs.getInt("no_d_id"),
					rs.getInt("no_w_id")
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_ORDER_LINES);
	        while (rs.next()) {
	        	val ol_delivery_d = rs.getTimestamp("ol_delivery_d")
	        	onInsertOrderLine(
	        		rs.getInt("ol_o_id"),
					rs.getInt("ol_d_id"),
					rs.getInt("ol_w_id"),
					rs.getInt("ol_number"),
					rs.getInt("ol_i_id"),
					rs.getInt("ol_supply_w_id"),
					(if(ol_delivery_d == null) None else Some(ol_delivery_d)),
					rs.getInt("ol_quantity"),
					rs.getFloat("ol_amount"),
					rs.getString("ol_dist_info")
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_ORDERS);
	        while (rs.next()) {
	        	val o_carrier_id = rs.getInt("o_carrier_id")
	        	val o_carrier_id_wasNull = rs.wasNull
	        	val o_all_local = (rs.getInt("o_all_local") > 0)
	        	onInsert_Order(
	        		rs.getInt("o_id"),
					rs.getInt("o_d_id"),
					rs.getInt("o_w_id"),
					rs.getInt("o_c_id"),
					rs.getTimestamp("o_entry_d"),
					(if(o_carrier_id_wasNull) None else Some(o_carrier_id)),
					rs.getInt("o_ol_cnt"),
					o_all_local
	        	)
	        }
	        rs.close

	        rs = stmt.executeQuery(TpccSelectQueries.ALL_STOCKS);
	        while (rs.next()) {
	        	onInsertStock(
	        		rs.getInt("s_i_id"),
					rs.getInt("s_w_id"),
					rs.getInt("s_quantity"),
					rs.getString("s_dist_01"),
					rs.getString("s_dist_02"),
					rs.getString("s_dist_03"),
					rs.getString("s_dist_04"),
					rs.getString("s_dist_05"),
					rs.getString("s_dist_06"),
					rs.getString("s_dist_07"),
					rs.getString("s_dist_08"),
					rs.getString("s_dist_09"),
					rs.getString("s_dist_10"),
					rs.getInt("s_ytd"),
					rs.getInt("s_order_cnt"),
					rs.getInt("s_remote_cnt"),
					rs.getString("s_data")
	        	)
	        }
	        rs.close

	        // println("All Tables loaded...")
	        // println("Warehouse => " + warehouseTbl)
	    } finally {
	        if (stmt != null) { stmt.close(); }
	    }
    }

    def deepEqual[K,V](map1:SHMap[K,V],map2:SHMap[K,V], f:((V,V) => Boolean)):Boolean = {
    	map2.foreach{ case (k,v) =>
    		if(!map1.contains(k) || (!(map1(k) equals v) && !f(v, map1(k)))) {
    			return false
     		}
    	}
    	map1.foreach{ case (k,v) =>
    		if(!map2.contains(k) || (!(map2(k) equals v) && !f(v, map2(k)))) {
    			return false
    		}
    	}
    	true
    }

    def showDiff[K,V](map1:SHMap[K,V],map2:SHMap[K,V], f:((Product,Product) => Boolean)) {
    	val addedElements: SHMap[K,V] = new SHMap[K,V]
    	val removedElements: SHMap[K,V] = new SHMap[K,V]
    	map2.foreach{ case (k,v) =>
    		if(!map1.contains(k) || (!(map1(k) equals v) && !f(v.asInstanceOf[Product], map1(k).asInstanceOf[Product]))) {
    			addedElements += (k, v)
    		}
    	}
    	map1.foreach{ case (k,v) =>
    		if(!map2.contains(k) || (!(map2(k) equals v) && !f(v.asInstanceOf[Product], map2(k).asInstanceOf[Product]))) {
    			removedElements += (k, v)
    		}
    	}
    	println("added elements => %s".format(addedElements))
    	println("removed elements => %s".format(removedElements))
    }

    // def showDiff[K](map1:HashSet[K],map2:HashSet[K]/*, f:((Product,Product) => Boolean)*/) {
    // 	val addedElements: HashSet[K] = new HashSet[K]
    // 	val removedElements: HashSet[K] = new HashSet[K]
    // 	map2.foreach{ k =>
    // 		if(!map1.contains(k)) {
    // 			addedElements += k
    // 		}
    // 	}
    // 	map1.foreach{ k =>
    // 		if(!map2.contains(k)) {
    // 			removedElements += k
    // 		}
    // 	}
    // 	println("added elements => %s".format(addedElements))
    // 	println("removed elements => %s".format(removedElements))
    // }

    def getAllMapsInfoStr:String = {
	    new StringBuilder("\nTables Info:\nnewOrderTbl => ").append({if(testSpecialDsUsed) "---" else newOrderTbl.getInfoStr}).append("\n")
		.append("newOrderSetImpl => ").append(if(testSpecialDsUsed) newOrderSetImpl.getInfoStr else "---").append("\n")
		.append("historyTbl => ").append(historyTbl.getInfoStr).append("\n")
		.append("warehouseTbl => ").append(warehouseTbl.getInfoStr).append("\n")
		.append("itemPartialTbl => ").append(itemPartialTbl.getInfoStr).append("\n")
		.append("orderTbl => ").append(orderTbl.getInfoStr).append("\n")
		.append("orderMaxOrderSetImpl => ").append(if(testSpecialDsUsed) orderMaxOrderSetImpl.getInfoStr else "---").append("\n")
		.append("districtTbl => ").append(districtTbl.getInfoStr).append("\n")
		.append("orderLineTbl => ").append(orderLineTbl.getInfoStr).append("\n")
		.append("customerTbl => ").append(customerTbl.getInfoStr).append("\n")
		.append("stockTbl => ").append(stockTbl.getInfoStr).toString
	}
}

object TpccSelectQueries {
	val ALL_CUSTOMERS = "SELECT `customer`.`c_id`,\n" +
	"    `customer`.`c_d_id`,\n" +
	"    `customer`.`c_w_id`,\n" +
	"    `customer`.`c_first`,\n" +
	"    `customer`.`c_middle`,\n" +
	"    `customer`.`c_last`,\n" +
	"    `customer`.`c_street_1`,\n" +
	"    `customer`.`c_street_2`,\n" +
	"    `customer`.`c_city`,\n" +
	"    `customer`.`c_state`,\n" +
	"    `customer`.`c_zip`,\n" +
	"    `customer`.`c_phone`,\n" +
	"    `customer`.`c_since`,\n" +
	"    `customer`.`c_credit`,\n" +
	"    `customer`.`c_credit_lim`,\n" +
	"    `customer`.`c_discount`,\n" +
	"    `customer`.`c_balance`,\n" +
	"    `customer`.`c_ytd_payment`,\n" +
	"    `customer`.`c_payment_cnt`,\n" +
	"    `customer`.`c_delivery_cnt`,\n" +
	"    `customer`.`c_data`\n" +
	"FROM `customer`;";

	val ALL_DISTRICTS = "SELECT `district`.`d_id`,\n" +
	"    `district`.`d_w_id`,\n" +
	"    `district`.`d_name`,\n" +
	"    `district`.`d_street_1`,\n" +
	"    `district`.`d_street_2`,\n" +
	"    `district`.`d_city`,\n" +
	"    `district`.`d_state`,\n" +
	"    `district`.`d_zip`,\n" +
	"    `district`.`d_tax`,\n" +
	"    `district`.`d_ytd`,\n" +
	"    `district`.`d_next_o_id`\n" +
	"FROM `district`;";

	val ALL_HISTORIES = "SELECT `history`.`h_c_id`," +
	"    `history`.`h_c_d_id`," +
	"    `history`.`h_c_w_id`," +
	"    `history`.`h_d_id`," +
	"    `history`.`h_w_id`," +
	"    `history`.`h_date`," +
	"    `history`.`h_amount`," +
	"    `history`.`h_data`" +
	"FROM `history`;";

	val ALL_ITEMS = "SELECT `item`.`i_id`," +
	"    `item`.`i_im_id`," +
	"    `item`.`i_name`," +
	"    `item`.`i_price`," +
	"    `item`.`i_data`" +
	"FROM `item`;";

	val ALL_NEW_ORDERS = "SELECT `new_orders`.`no_o_id`," +
	"    `new_orders`.`no_d_id`," +
	"    `new_orders`.`no_w_id`" +
	"FROM `new_orders`;";

	val ALL_ORDER_LINES = "SELECT `order_line`.`ol_o_id`," +
	"    `order_line`.`ol_d_id`," +
	"    `order_line`.`ol_w_id`," +
	"    `order_line`.`ol_number`," +
	"    `order_line`.`ol_i_id`," +
	"    `order_line`.`ol_supply_w_id`," +
	"    `order_line`.`ol_delivery_d`," +
	"    `order_line`.`ol_quantity`," +
	"    `order_line`.`ol_amount`," +
	"    `order_line`.`ol_dist_info`" +
	"FROM `order_line`;";

	val ALL_ORDERS = "SELECT `orders`.`o_id`," +
	"    `orders`.`o_d_id`," +
	"    `orders`.`o_w_id`," +
	"    `orders`.`o_c_id`," +
	"    `orders`.`o_entry_d`," +
	"    `orders`.`o_carrier_id`," +
	"    `orders`.`o_ol_cnt`," +
	"    `orders`.`o_all_local`" +
	"FROM `orders`;";

	val ALL_STOCKS = "SELECT `stock`.`s_i_id`," +
	"    `stock`.`s_w_id`," +
	"    `stock`.`s_quantity`," +
	"    `stock`.`s_dist_01`," +
	"    `stock`.`s_dist_02`," +
	"    `stock`.`s_dist_03`," +
	"    `stock`.`s_dist_04`," +
	"    `stock`.`s_dist_05`," +
	"    `stock`.`s_dist_06`," +
	"    `stock`.`s_dist_07`," +
	"    `stock`.`s_dist_08`," +
	"    `stock`.`s_dist_09`," +
	"    `stock`.`s_dist_10`," +
	"    `stock`.`s_ytd`," +
	"    `stock`.`s_order_cnt`," +
	"    `stock`.`s_remote_cnt`," +
	"    `stock`.`s_data`" +
	"FROM `stock`;";

	val ALL_WAREHOUSES = "SELECT `warehouse`.`w_id`," +
	"    `warehouse`.`w_name`," +
	"    `warehouse`.`w_street_1`," +
	"    `warehouse`.`w_street_2`," +
	"    `warehouse`.`w_city`," +
	"    `warehouse`.`w_state`," +
	"    `warehouse`.`w_zip`," +
	"    `warehouse`.`w_tax`," +
	"    `warehouse`.`w_ytd`" +
	"FROM `warehouse`;";
}