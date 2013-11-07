package ddbt.tpcc.loadtest


object TpccConstants {

  var TRANSACTION_COUNT: Int = 5

  var MAXITEMS: Int = 100000

  var CUST_PER_DIST: Int = 3000

  var DIST_PER_WARE: Int = 10

  var ORD_PER_DIST: Int = 3000

  var nums: Array[Int] = new Array[Int](CUST_PER_DIST)

  var MAX_NUM_ITEMS: Int = 15

  var MAX_ITEM_LEN: Int = 24

  val SHOW_OUTPUT = false
}
