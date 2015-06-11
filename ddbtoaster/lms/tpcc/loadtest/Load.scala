package ddbt.tpcc.loadtest

import ddbt.tpcc.loadtest.load.Record
import ddbt.tpcc.loadtest.load.RecordLoader
import java.sql.Statement
import java.sql.Connection
import java.sql.SQLException
import java.util.Calendar
import java.util.Date
import TpccConstants._

object Load{

  private var optionDebug: Boolean = false

  def loadItems(loadConfig: TpccLoadConfig, option_debug: Boolean) {
    optionDebug = option_debug
    var i_id = 0
    var i_im_id = 0
    var i_name: String = null
    var i_price = 0f
    var i_data: String = null
    val orig = Array.ofDim[Int](MAXITEMS + 1)
    var pos = 0
    var i = 0
    System.out.print("Loading Item \n")
    i = 0
    while (i < MAXITEMS / 10) {
      orig(i) = 0
      i += 1
    }
    i = 0
    while (i < MAXITEMS / 10) {
      do {
        pos = Util.randomNumber(0, MAXITEMS)
      } while (orig(pos) != 0);
      orig(pos) = 1
      i += 1
    }
    val ITEM_COLUMN_NAME = Array("i_id", " i_im_id", " i_name", " i_price", " i_data")
    val itemRecord = new Record(5)
    val itemLoader = loadConfig.createLoader("item", ITEM_COLUMN_NAME)
    i_id = 1
    while (i_id <= MAXITEMS) {
      i_im_id = Util.randomNumber(1, 10000)
      i_name = Util.makeAlphaString(14, 24)
      if (i_name == null) {
        println("I_name null.")
        System.exit(1)
      }
      i_price = ((Util.randomNumber(100, 10000)).toInt / 100f).toFloat
      i_data = Util.makeAlphaString(26, 50)
      if (orig(i_id) != 0) {
        pos = Util.randomNumber(0, i_data.length - 8)
        i_data = i_data.substring(0, pos) + "original" + i_data.substring(pos + 8)
      }
      itemRecord.reset()
      itemRecord.add(i_id)
      itemRecord.add(i_im_id)
      itemRecord.add(i_name)
      itemRecord.add(i_price)
      itemRecord.add(i_data)
      itemLoader.load(itemRecord)
      if ((i_id % 100) == 0) {
        System.out.print(".")
        if ((i_id % 5000) == 0) System.out.print(" %d\n".format(i_id))
      }
      i_id += 1
    }
    itemLoader.close()
    System.out.print("Item Done. \n")
  }

  def loadWare(loadConfig: TpccLoadConfig, 
      shardCount: Int, 
      min_ware: Int, 
      max_ware: Int, 
      option_debug: Boolean, 
      shardId: Int) {
    var w_id: Int = 0
    var w_name: String = null
    var w_street_1: String = null
    var w_street_2: String = null
    var w_city: String = null
    var w_state: String = null
    var w_zip: String = null
    var w_tax = 0D
    var w_ytd = 0D
    val tmp = 0
    var currentShard = 0
    System.out.print("Loading Warehouse \n")
    val WAREHOUSE_COLUMN_NAME = Array("w_id", " w_name", " w_street_1", " w_street_2", " w_city", " w_state", " w_zip", " w_tax", " w_ytd")
    val warehouseRecord = new Record(9)
    val warehouseLoader = loadConfig.createLoader("warehouse", WAREHOUSE_COLUMN_NAME)
    w_id = min_ware
    while (w_id <= max_ware) {
      if (shardCount > 0) {
        currentShard = (w_id % shardCount)
        if (currentShard == 0) {
          currentShard = shardCount
        }
      }
      if ((currentShard == shardId) || (shardId == 0)) {
        println("Current Shard: " + currentShard)
        w_name = Util.makeAlphaString(6, 10)
        w_street_1 = Util.makeAlphaString(10, 20)
        w_street_2 = Util.makeAlphaString(10, 20)
        w_city = Util.makeAlphaString(10, 20)
        w_state = Util.makeAlphaString(2, 2)
        w_zip = Util.makeAlphaString(9, 9)
        w_tax = (Util.randomNumber(10, 20).toFloat / 100f)
        w_ytd = 3000000.00f
        System.out.print("WID = %d, Name= %s, Tax = %f\n".format(w_id, w_name, w_tax))
        warehouseRecord.reset()
        warehouseRecord.add(w_id)
        warehouseRecord.add(w_name)
        warehouseRecord.add(w_street_1)
        warehouseRecord.add(w_street_2)
        warehouseRecord.add(w_city)
        warehouseRecord.add(w_state)
        warehouseRecord.add(w_zip)
        warehouseRecord.add(w_tax)
        warehouseRecord.add(w_ytd)
        warehouseLoader.load(warehouseRecord)
        warehouseLoader.commit()
        stock(loadConfig, w_id)
        district(loadConfig, w_id)
      }
      w_id += 1
    }
    warehouseLoader.close()
  }

  def loadCust(loadConfig: TpccLoadConfig, 
      shardCount: Int, 
      min_ware: Int, 
      max_ware: Int, 
      shardId: Int) {
    var w_id = min_ware
    while (w_id <= max_ware) {
      var d_id = 1
      while (d_id <= DIST_PER_WARE) {
        loadCustomer(loadConfig, d_id, w_id, shardCount, shardId)
        d_id += 1
      }
      w_id += 1
    }
  }

  def loadOrd(loadConfig: TpccLoadConfig, 
      shardCount: Int, 
      max_ware: Int, 
      shardId: Int) {
    var w_id = 1
    while (w_id <= max_ware) {
      var d_id = 1
      while (d_id <= DIST_PER_WARE) {
        loadOrders(loadConfig, d_id, w_id, shardCount, shardId)
        d_id += 1
      }
      w_id += 1
    }
  }

  def stock(loadConfig: TpccLoadConfig, w_id: Int): Boolean = {
    var s_i_id = 0
    var s_w_id = 0
    var s_quantity = 0
    var s_dist_01: String = null
    var s_dist_02: String = null
    var s_dist_03: String = null
    var s_dist_04: String = null
    var s_dist_05: String = null
    var s_dist_06: String = null
    var s_dist_07: String = null
    var s_dist_08: String = null
    var s_dist_09: String = null
    var s_dist_10: String = null
    var s_data: String = null
    val orig = Array.ofDim[Int](MAXITEMS + 1)
    var pos = 0
    var i = 0
    val error = false
    val STOCK_COLUMN_NAME = Array("s_i_id", " s_w_id", " s_quantity", " " + "s_dist_01", " s_dist_02", " s_dist_03", " s_dist_04", " s_dist_05", " s_dist_06", " " + "s_dist_07", " s_dist_08", " s_dist_09", " s_dist_10", " s_ytd", " s_order_cnt", " " + "s_remote_cnt", " s_data")
    val stockRecord = new Record(17)
    val stockLoader = loadConfig.createLoader("stock", STOCK_COLUMN_NAME)
    System.out.print("Loading Stock Wid=%d\n".format(w_id))
    s_w_id = w_id
    i = 0
    while (i < MAXITEMS / 10) {
      orig(i) = 0
      i += 1
    }
    i = 0
    while (i < MAXITEMS / 10) {
      do {
        pos = Util.randomNumber(0, MAXITEMS)
      } while (orig(pos) != 0);
      orig(pos) = 1
      i += 1
    }
    s_i_id = 1
    while (s_i_id <= MAXITEMS) {
      s_quantity = Util.randomNumber(10, 100)
      s_dist_01 = Util.makeAlphaString(24, 24)
      s_dist_02 = Util.makeAlphaString(24, 24)
      s_dist_03 = Util.makeAlphaString(24, 24)
      s_dist_04 = Util.makeAlphaString(24, 24)
      s_dist_05 = Util.makeAlphaString(24, 24)
      s_dist_06 = Util.makeAlphaString(24, 24)
      s_dist_07 = Util.makeAlphaString(24, 24)
      s_dist_08 = Util.makeAlphaString(24, 24)
      s_dist_09 = Util.makeAlphaString(24, 24)
      s_dist_10 = Util.makeAlphaString(24, 24)
      s_data = Util.makeAlphaString(26, 50)
      if (orig(s_i_id) != 0) {
        s_data = "original"
      }
      stockRecord.reset()
      stockRecord.add(s_i_id)
      stockRecord.add(s_w_id)
      stockRecord.add(s_quantity)
      stockRecord.add(s_dist_01)
      stockRecord.add(s_dist_02)
      stockRecord.add(s_dist_03)
      stockRecord.add(s_dist_04)
      stockRecord.add(s_dist_05)
      stockRecord.add(s_dist_06)
      stockRecord.add(s_dist_07)
      stockRecord.add(s_dist_08)
      stockRecord.add(s_dist_09)
      stockRecord.add(s_dist_10)
      stockRecord.add(0)
      stockRecord.add(0)
      stockRecord.add(0)
      stockRecord.add(s_data)
      stockLoader.load(stockRecord)
      if (optionDebug) System.out.print("SID = %d, WID = %d, Quan = %d\n".format(s_i_id, s_w_id, s_quantity))
      if ((s_i_id % 100) == 0) {
        System.out.print(".")
        if ((s_i_id % 5000) == 0) System.out.print(" %d\n".format(s_i_id))
      }
      s_i_id += 1
    }
    stockLoader.close()
    System.out.print(" Stock Done.\n")
    error
  }

  def district(loadConfig: TpccLoadConfig, w_id: Int): Boolean = {
    var d_id: Int = 0
    var d_w_id: Int = 0
    var d_name: String = null
    var d_street_1: String = null
    var d_street_2: String = null
    var d_city: String = null
    var d_state: String = null
    var d_zip: String = null
    var d_tax: Float = 0f
    var d_ytd: Float = 0f
    var d_next_o_id: Int = 0
    val error = false
    System.out.print("Loading District\n")
    d_w_id = w_id
    d_ytd = 30000f.toFloat
    d_next_o_id = 3001
    val DISTRICT_COLUMN_NAME = Array("d_id", " d_w_id", " d_name", " d_street_1", " d_street_2", " d_city", " d_state", " d_zip", " d_tax", " d_ytd", " d_next_o_id")
    val districtRecord = new Record(11)
    val districtLoader = loadConfig.createLoader("district", DISTRICT_COLUMN_NAME)
    d_id = 1
    while (d_id <= DIST_PER_WARE) {
      d_name = Util.makeAlphaString(6, 10)
      d_street_1 = Util.makeAlphaString(10, 20)
      d_street_2 = Util.makeAlphaString(10, 20)
      d_city = Util.makeAlphaString(10, 20)
      d_state = Util.makeAlphaString(2, 2)
      d_zip = Util.makeAlphaString(9, 9)
      d_tax = (Util.randomNumber(10, 20).toFloat / 100f).toFloat
      districtRecord.reset()
      districtRecord.add(d_id)
      districtRecord.add(d_w_id)
      districtRecord.add(d_name)
      districtRecord.add(d_street_1)
      districtRecord.add(d_street_2)
      districtRecord.add(d_city)
      districtRecord.add(d_state)
      districtRecord.add(d_zip)
      districtRecord.add(d_tax)
      districtRecord.add(d_ytd)
      districtRecord.add(d_next_o_id)
      districtLoader.load(districtRecord)
      if (optionDebug) System.out.print("DID = %d, WID = %d, Name = %s, Tax = %f\n".format(d_id, d_w_id, d_name, 
        d_tax))
      d_id += 1
    }
    districtLoader.close()
    error
  }

  def loadCustomer(loadConfig: TpccLoadConfig, 
      d_id: Int, 
      w_id: Int, 
      shardCount: Int, 
      shardId: Int) {
    var c_id = 0
    var c_d_id = 0
    var c_w_id = 0
    var c_first: String = null
    var c_middle: String = null
    var c_last: String = null
    var c_street_1: String = null
    var c_street_2: String = null
    var c_city: String = null
    var c_state: String = null
    var c_zip: String = null
    var c_phone: String = null
    var c_credit: String = null
    var c_credit_lim = 0
    var c_discount = 0f
    var c_balance = 0f
    var c_data: String = null
    var h_amount = 0f
    var h_data: String = null
    System.out.print("Loading Customer for DID=%d, WID=%d\n".format(d_id, w_id))
    var currentShard = 0
    if (shardCount > 0) {
      currentShard = (w_id % shardCount)
      if (currentShard == 0) {
        currentShard = shardCount
      }
    }
    val CUSTOMER_COLUMNS = Array("c_id", "c_d_id", "c_w_id", "c_first", "c_middle", "c_last", "c_street_1", "c_street_2", "c_city", "c_state", "c_zip", "c_phone", "c_since", "c_credit", "c_credit_lim", "c_discount", "c_balance", "c_ytd_payment", "c_payment_cnt", "c_delivery_cnt", "c_data")
    val customerRecord = new Record(21)
    val customerLoader = loadConfig.createLoader("customer", CUSTOMER_COLUMNS)
    val HISTORY_COLUMN_NAME = Array("h_c_id", "h_c_d_id", "h_c_w_id", "h_d_id", "h_w_id", "h_date", "h_amount", "h_data")
    val historyRecord = new Record(8)
    val historyLoader = loadConfig.createLoader("history", HISTORY_COLUMN_NAME)
    if ((currentShard == shardId) || (shardId == 0)) {
      c_id = 1
      while (c_id <= CUST_PER_DIST) {
        c_d_id = d_id
        c_w_id = w_id
        c_first = Util.makeAlphaString(8, 16)
        c_middle = "O" + "E"
        c_last = if (c_id <= 1000) Util.lastName(c_id - 1) else Util.lastName(Util.nuRand(255, 0, 999))
        c_street_1 = Util.makeAlphaString(10, 20)
        c_street_2 = Util.makeAlphaString(10, 20)
        c_city = Util.makeAlphaString(10, 20)
        c_state = Util.makeAlphaString(2, 2)
        c_zip = Util.makeAlphaString(9, 9)
        c_phone = Util.makeNumberString(16, 16)
        c_credit = if (Util.randomNumber(0, 1) == 1) "G" else "B"
        c_credit += "C"
        c_credit_lim = 50000
        c_discount = (Util.randomNumber(0, 50).toFloat / 100f).toFloat
        c_balance = -10f.toFloat
        c_data = Util.makeAlphaString(300, 500)
        val calendar = Calendar.getInstance
        val date = new java.sql.Date(calendar.getTimeInMillis)
        customerRecord.reset()
        customerRecord.add(c_id)
        customerRecord.add(c_d_id)
        customerRecord.add(c_w_id)
        customerRecord.add(c_first)
        customerRecord.add(c_middle)
        customerRecord.add(c_last)
        customerRecord.add(c_street_1)
        customerRecord.add(c_street_2)
        customerRecord.add(c_city)
        customerRecord.add(c_state)
        customerRecord.add(c_zip)
        customerRecord.add(c_phone)
        customerRecord.add(date)
        customerRecord.add(c_credit)
        customerRecord.add(c_credit_lim)
        customerRecord.add(c_discount)
        customerRecord.add(c_balance)
        customerRecord.add(10f)
        customerRecord.add(1)
        customerRecord.add(0)
        customerRecord.add(c_data)
        customerLoader.load(customerRecord)
        h_amount = 10f
        h_data = Util.makeAlphaString(12, 24)
        historyRecord.reset()
        historyRecord.add(c_id)
        historyRecord.add(c_d_id)
        historyRecord.add(c_w_id)
        historyRecord.add(c_d_id)
        historyRecord.add(c_w_id)
        historyRecord.add(date)
        historyRecord.add(h_amount)
        historyRecord.add(h_data)
        historyLoader.load(historyRecord)
        if (optionDebug) {
          System.out.print("CID = %d, LST = %s, P# = %s\n".format(c_id, c_last, c_phone))
        }
        if ((c_id % 100) == 0) {
          System.out.print(".")
          if ((c_id % 1000) == 0) System.out.print(" %d\n".format(c_id))
        }
        c_id += 1
      }
    }
    customerLoader.close()
    historyLoader.close()
    System.out.print("Customer Done.\n")
  }

  def loadOrders(loadConfig: TpccLoadConfig, 
      d_id: Int, 
      w_id: Int, 
      shardCount: Int, 
      shardId: Int) {
    var o_id: Int = 0
    var o_c_id: Int = 0
    var o_d_id: Int = 0
    var o_w_id: Int = 0
    var o_carrier_id: Int = 0
    var o_ol_cnt: Int = 0
    var ol: Int = 0
    var ol_i_id: Int = 0
    var ol_supply_w_id: Int = 0
    var ol_quantity: Int = 0
    var ol_amount: Float = 0f
    var ol_dist_info: String = null
    var tmp_float: Float = 0f
    var currentShard = 0
    if (shardCount > 0) {
      currentShard = (w_id % shardCount)
      if (currentShard == 0) {
        currentShard = shardCount
      }
    }
    val ORDERS_COLUMN_NAME = Array("o_id", "o_d_id", "o_w_id", "o_c_id", "o_entry_d", "o_carrier_id", "o_ol_cnt", "o_all_local")
    val orderRecord = new Record(8)
    val orderLoader = loadConfig.createLoader("orders", ORDERS_COLUMN_NAME)
    val NEW_ORDERS_COLUMN_NAMES = Array("no_o_id", "no_d_id", "no_w_id")
    val newOrderRecord = new Record(3)
    val newOrderLoader = loadConfig.createLoader("new_orders", NEW_ORDERS_COLUMN_NAMES)
    val ORDER_LINE_COLUMN_NAME = Array("ol_o_id", "ol_d_id", "ol_w_id", "ol_number", "ol_i_id", "ol_supply_w_id", "ol_delivery_d", "ol_quantity", "ol_amount", "ol_dist_info")
    val orderLineRecord = new Record(10)
    val orderLineLoader = loadConfig.createLoader("order_line", ORDER_LINE_COLUMN_NAME)
    if ((currentShard == shardId) || (shardId == 0)) {
      System.out.print("Loading Orders for D=%d, W=%d\n".format(d_id, w_id))
      o_d_id = d_id
      o_w_id = w_id
      Util.initPermutation()
      o_id = 1
      while (o_id <= ORD_PER_DIST) {
        o_c_id = Util.getPermutation
        o_carrier_id = Util.randomNumber(1, 10)
        o_ol_cnt = Util.randomNumber(5, 15)
        val date = new java.sql.Date(System.currentTimeMillis())
        if (o_id > 2100) {
          orderRecord.reset()
          orderRecord.add(o_id)
          orderRecord.add(o_d_id)
          orderRecord.add(o_w_id)
          orderRecord.add(o_c_id)
          orderRecord.add(date)
          orderRecord.add(null)
          orderRecord.add(o_ol_cnt)
          orderRecord.add(1)
          orderLoader.load(orderRecord)
          newOrderRecord.reset()
          newOrderRecord.add(o_id)
          newOrderRecord.add(o_d_id)
          newOrderRecord.add(o_w_id)
          newOrderLoader.load(newOrderRecord)
        } else {
          orderRecord.reset()
          orderRecord.add(o_id)
          orderRecord.add(o_d_id)
          orderRecord.add(o_w_id)
          orderRecord.add(o_c_id)
          orderRecord.add(date)
          orderRecord.add(o_carrier_id)
          orderRecord.add(o_ol_cnt)
          orderRecord.add(1)
          orderLoader.load(orderRecord)
        }
        if (optionDebug) System.out.print("OID = %d, CID = %d, DID = %d, WID = %d\n".format(o_id, o_c_id, 
          o_d_id, o_w_id))
        ol = 1
        while (ol <= o_ol_cnt) {
          ol_i_id = Util.randomNumber(1, MAXITEMS)
          ol_supply_w_id = o_w_id
          ol_quantity = 5
          ol_amount = 0f.toFloat
          ol_dist_info = Util.makeAlphaString(24, 24)
          tmp_float = ((Util.randomNumber(10, 10000)).toFloat / 100f).toFloat
          if (o_id > 2100) {
            orderLineRecord.reset()
            orderLineRecord.add(o_id)
            orderLineRecord.add(o_d_id)
            orderLineRecord.add(o_w_id)
            orderLineRecord.add(ol)
            orderLineRecord.add(ol_i_id)
            orderLineRecord.add(ol_supply_w_id)
            orderLineRecord.add(null)
            orderLineRecord.add(ol_quantity)
            orderLineRecord.add(ol_amount)
            orderLineRecord.add(ol_dist_info)
            orderLineLoader.load(orderLineRecord)
          } else {
            orderLineRecord.reset()
            orderLineRecord.add(o_id)
            orderLineRecord.add(o_d_id)
            orderLineRecord.add(o_w_id)
            orderLineRecord.add(ol)
            orderLineRecord.add(ol_i_id)
            orderLineRecord.add(ol_supply_w_id)
            orderLineRecord.add(date)
            orderLineRecord.add(ol_quantity)
            orderLineRecord.add(tmp_float)
            orderLineRecord.add(ol_dist_info)
            orderLineLoader.load(orderLineRecord)
          }
          if (optionDebug) {
            System.out.print("OL = %d, IID = %d, QUAN = %d, AMT = %f\n".format(ol, ol_i_id, ol_quantity, ol_amount))
          }
          ol += 1
        }
        if ((o_id % 100) == 0) {
          System.out.print(".")
          if ((o_id % 1000) == 0) {
            System.out.print(" %d\n".format(o_id))
          }
        }
        o_id += 1
      }
      orderLoader.close()
      orderLineLoader.close()
      newOrderLoader.close()
    }
    System.out.print("Orders Done.\n")
  }
}
