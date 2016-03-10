package sc.tpcc


//import ddbt.lib.store.{MStore, GenericEntry}
import ch.epfl.data.sc.pardis
import sc.tpcc.compiler.TpccCompiler

import scala.collection.mutable.ArrayBuffer

import ddbt.lib.store.deep._

import ch.epfl.data.sc.pardis.prettyprinter.{ASTCodeGenerator, ScalaCodeGenerator, CodeGenerator}
import pardis.optimization._
import pardis.compiler._

import scala.language.implicitConversions

object TpccXactGenerator_SC extends StoreDSL {

  implicit object Context extends StoreDSL
  import Context.Predef._
  //  type NewOrderEntry          = SEntry3 [Int,Int,Int]
  //  type HistoryEntry           = SEntry8 [Int,Int,Int,Int,Int,Date,Float,String]
  //  type WarehouseEntry         = SEntry9 [Int,             String,String,String,String,String,String,Float,Double]
  //  type ItemEntry              = SEntry5 [Int,             Int,String,Float,String]
  //  type OrderEntry             = SEntry8 [Int,Int,Int,     Int,Date,/*Option[Int]*/Int,Int,Boolean]
  //  type DistrictEntry          = SEntry11[Int,Int,         String,String,String,String,String,String,Float,Double,Int]
  //  type OrderLineEntry         = SEntry10[Int,Int,Int,Int, Int,Int,/*Option[Date]*/Date,Int,Float,String]
  //  type CustomerEntry          = SEntry21[Int,Int,Int,     String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String]
  //  type StockEntry             = SEntry17[Int,Int,         Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String]

  val newOrderTbl = __newMStore[GenericEntry]
  val historyTbl = __newMStore[GenericEntry]
  val warehouseTbl = __newMStore[GenericEntry]
  val itemTbl = __newMStore[GenericEntry]
  val orderTbl = __newMStore[GenericEntry]
  val districtTbl = __newMStore[GenericEntry]
  val orderLineTbl = __newMStore[GenericEntry]
  val customerTbl = __newMStore[GenericEntry]
  val stockTbl = __newMStore[GenericEntry]
  /*
      //TODO: SBJ: check index numbers
      def newOrderTx(showOutput: Boolean, datetime: Date, t_num: Int, w_id: Int, d_id: Int, c_id: Int, o_ol_count: Int, o_all_local: Int, itemid: Array[Int], supware: Array[Int], quantity: Array[Int], price: Array[Float], iname: Array[String], stock: Array[Int], bg: Array[Char], amt: Array[Float]): Int = {

        if (showOutput) println("- Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id, d_id, c_id))

        var ol_number = 0
        var failed = false
        val idata = new Array[String](o_ol_count)

        var all_items_exist = true
        while ((ol_number < o_ol_count) && all_items_exist) {

          val itemEntry /*(i_id, _, i_name, i_price, i_data)*/ = itemTbl.get(0, GenericEntry("SteSampleSEntry", 1, itemid(ol_number)))
          if (itemEntry == null) {
            all_items_exist = false
          } else {
            iname(ol_number) = itemEntry.get(3) //i_name
            price(ol_number) = itemEntry.get(4) //i_price
            idata(ol_number) = itemEntry.get(5) //i_data
          }
          ol_number += 1
        }
        if (!all_items_exist) {
          1
        } else {
          /*(c_id,d_id,w_id, c_discount, c_last, c_credit, w_tax)*/
          val customerEntry /*(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = customerTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, 3, c_id, d_id, w_id))
          val warehouseEntry /*(w_id,w_name,w_street_1,w_street_2,w_city,w_state,w_zip,w_tax,w_ytd)*/ = warehouseTbl.get(0, GenericEntry("SteSampleSEntry", 1, w_id))
          val districtEntry /*(d_d_id,d_w_id,_,_,_,_,_,_,d_tax,_,d_next_o_id)*/ = districtTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, d_id, w_id))
          val o_id: Int = districtEntry.get(11)
          districtEntry +=(11, 1) //d_next_o_id+1
          districtTbl.update(districtEntry)


          orderTbl.insert(GenericEntry("SteNewSEntry", o_id, d_id, w_id, c_id, datetime, -1, o_ol_count, o_all_local > 0))

          newOrderTbl.insert(GenericEntry("SteNewSEntry", o_id, d_id, w_id))

          var total = 0f

          ol_number = 0
          while (ol_number < o_ol_count) {
            val ol_supply_w_id = supware(ol_number)
            val ol_i_id = itemid(ol_number)
            val ol_quantity = quantity(ol_number)

            val stockEntry /*(s_i_id,s_w_id,s_quantity,s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data)*/ = stockTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id))

            val ol_dist_info = if (d_id == 1) {
              stockEntry.get(4) //s_dist_01
            } else if (d_id == 2) {
              stockEntry.get(5) //s_dist_02
            } else if (d_id == 3) {
              stockEntry.get(6) //s_dist_03
            } else if (d_id == 4) {
              stockEntry.get(7) //s_dist_04
            } else if (d_id == 5) {
              stockEntry.get(8) //s_dist_05
            } else if (d_id == 6) {
              stockEntry.get(9) //s_dist_06
            } else if (d_id == 7) {
              stockEntry.get(10) //s_dist_07
            } else if (d_id == 8) {
              stockEntry.get(11) //s_dist_08
            } else if (d_id == 9) {
              stockEntry.get(12) //s_dist_09
            } else /*if(d_id == 10)*/ {
              stockEntry.get(13) //s_dist_10
            }

            val s_quantity: Byte = stockEntry.get(3) //s_quantity
            stock(ol_number) = s_quantity

            if ( /*c_credit*/ customerEntry.get(14).asInstanceOf[String].contains("original") && /*s_data*/ stockEntry.get(17).asInstanceOf[String].contains("original")) {
              bg(ol_number) = 'B'
            } else {
              bg(ol_number) = 'G'
            }

            stockEntry.update(3, s_quantity - ol_quantity)
            if (s_quantity <= ol_quantity) stockEntry +=(3, 91)

            var s_remote_cnt_increment = 0
            if (ol_supply_w_id != w_id) s_remote_cnt_increment = 1

            //TODO this is the correct version but is not implemented in the correctness test
            //stockEntry._14 += ol_quantity //s_ytd
            //stockEntry._15 += 1 //s_order_cnt
            //stockEntry._16 += s_remote_cnt_increment //s_remote_cnt
            stockTbl.update(stockEntry)

            val c_discount: Float = customerEntry.get(16)
            val w_tax: Float = warehouseEntry.get(8)
            val d_tax: Float = districtEntry.get(9)
            val ol_amount = (ol_quantity * price(ol_number) * (1f + w_tax + d_tax) * (1f - c_discount)) /*.asInstanceOf[Float]*/
            amt(ol_number) = ol_amount
            total += ol_amount

            orderLineTbl.insert(GenericEntry("SteNewSEntry", o_id, d_id, w_id, ol_number + 1 /*to start from 1*/ , ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info))

            ol_number += 1
          }
          if (showOutput) println("An error occurred in handling NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id, d_id, c_id))
          1
        }
      }

      //    def paymentTx(showOutput:Rep[Boolean], datetime:Rep[Date], t_num:Rep[Int], w_id:Rep[Int], d_id:Rep[Int], c_by_name:Rep[Int], c_w_id:Rep[Int], c_d_id:Rep[Int], c_id:Rep[Int], c_last_input:Rep[String], h_amount:Rep[Float]):Rep[Int] = {
      def paymentTx(showOutput: Boolean, datetime: Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_w_id: Int, c_d_id: Int, c_id: Int, c_last_input: String, h_amount: Float): Int = {


        val warehouseEntry /*(w_id,w_name,w_street_1,w_street_2,w_city,w_state,w_zip,_,w_ytd)*/ = warehouseTbl.get(0, GenericEntry("SteSampleSEntry", 1, w_id))
        warehouseEntry +=(9, h_amount) //w_ytd
        warehouseTbl.update(warehouseEntry)

        val districtEntry /*(d_id,d_w_id,d_name,d_street_1,d_street_2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id)*/ = districtTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, d_id, w_id))
        districtEntry +=(10, h_amount)
        districtTbl.update(districtEntry)

        var customerEntry: GenericEntry /*(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = null
        if ($c_by_name > 0) {
          val customersWithLastName = ArrayBuffer[GenericEntry]()
          customerTbl.slice(1, GenericEntry("SteSampleSEntry", 2, 3, 6, $c_d_id, $c_w_id, $c_last_input), {
            case custEntry => customersWithLastName += custEntry
          })
          var index = customersWithLastName.size / 2
          if (customersWithLastName.size % 2 == 0) {
            index -= 1
          }
          customerEntry = customersWithLastName(index)
        } else {
          customerEntry = customerTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, 3, $c_id, $c_d_id, $c_w_id))
        }

        var c_data: String = customerEntry.get(21)

        if (customerEntry.get(14).asInstanceOf[String].contains("BC")) {
          //c_credit
          //TODO this is the correct version but is not implemented in the correctness test
          //c_data = found_c_id + " " + c_d_id + " " + c_w_id + " " + d_id + " " + w_id + " " + h_amount + " | " + c_data
          c_data = "%d %d %d %d %d $%f %s | %s".format(customerEntry.get(1), $c_d_id, $c_w_id, $d_id, $w_id,
            h_amount, $datetime, c_data)
          if (c_data.length > 500) c_data = c_data.substring(0, 500)
          customerEntry +=(17 /*c_balance*/ , h_amount)
          //TODO this is the correct version but is not implemented in the correctness test
          //customerEntry += (18 /*c_ytd_payment*/, h_amount)
          //customerEntry += (19 /*c_payment_cnt*/, 1)
          customerEntry.update(21 /*c_data*/ , c_data)
        } else {
          customerEntry +=(17 /*c_balance*/ , h_amount)
          //TODO this is the correct version but is not implemented in the correctness test
          //customerEntry += (18 /*c_ytd_payment*/, h_amount)
          //customerEntry += (19 /*c_payment_cnt*/, 1)
        }
        customerTbl.update(customerEntry)
        val w_name: String = warehouseEntry.get(2)
        val d_name: String = districtEntry.get(3)
        //TODO this is the correct version but is not implemented in the correctness test
        val h_data = {
          if (w_name.length > 10) w_name.substring(0, 10) else w_name
        } + "    " + {
          if (d_name.length > 10) d_name.substring(0, 10) else d_name
        }
        historyTbl.insert(GenericEntry("SteNewSEntry", customerEntry.get(1), $c_d_id, $c_w_id, $d_id, $w_id, $datetime, h_amount, h_data))
        if ($showOutput) {
          var output = "\n+---------------------------- PAYMENT ----------------------------+" +
            "\n Date: %s" + $datetime +
            "\n\n Warehouse: " + $w_id +
            "\n   Street:  " + /*w_street_1*/ warehouseEntry.get(3) +
            "\n   Street:  " + /*w_street_2*/ warehouseEntry.get(4) +
            "\n   City:    " + /*w_city*/ warehouseEntry.get(5) +
            "   State: " + /*w_state*/ warehouseEntry.get(6) +
            "  Zip: " + /*w_zip*/ warehouseEntry.get(7) +
            "\n\n District:  " + $d_id +
            "\n   Street:  " + /*d_street_1*/ districtEntry.get(4) +
            "\n   Street:  " + /*d_street_2*/ districtEntry.get(5) +
            "\n   City:    " + /*d_city*/ districtEntry.get(6) +
            "   State: " + /*d_state*/ districtEntry.get(7) +
            "  Zip: " + /*d_zip*/ districtEntry.get(8) +
            "\n\n Customer:  " + customerEntry.get(1) +
            "\n   Name:    " + /*c_first*/ customerEntry.get(4) +
            " " + /*c_middle*/ customerEntry.get(5) +
            " " + /*c_last*/ customerEntry.get(6) +
            "\n   Street:  " + /*c_street_1*/ customerEntry.get(7) +
            "\n   Street:  " + /*c_street_2*/ customerEntry.get(8) +
            "\n   City:    " + /*c_city*/ customerEntry.get(9) +
            "   State: " + /*c_state*/ customerEntry.get(10) +
            "  Zip: " + /*c_zip*/ customerEntry.get(11) +
            "\n   Since:   " +
            (if ( /*c_since*/ customerEntry.get(13) != null) {
              /*c_since*/ customerEntry.get(13)
            }
            else {
              ""
            }) + "\n   Credit:  " + /*c_credit*/ customerEntry.get(14) +
            "\n   Disc:    " + /*c_discount*/ (customerEntry.get(16).asInstanceOf[Float] * 100) + "%" +
            "\n   Phone:   " + /*c_phone*/ customerEntry.get(12) +
            "\n\n Amount Paid:      " + h_amount +
            "\n Credit Limit:     " + /*c_credit_lim*/ customerEntry.get(15) +
            "\n New Cust-Balance: " + /*c_balance*/ customerEntry.get(17)
          if (customerEntry.get(14) == "BC") {
            val cdata = c_data
            if (cdata.length > 50) {
              output = output + "\n\n Cust-Data: " + cdata.substring(0, 50)
              val data_chunks = (if (cdata.length > 200) 4 else cdata.length / 50)
              var n = 1
              while (n < data_chunks) {
                output = output + "\n            " + cdata.substring(n * 50, (n + 1) * 50)
                n += 1
              }
            } else {
              output = output + "\n\n Cust-Data: " + cdata
            }
          }
          output = output + "\n+-----------------------------------------------------------------+\n\n"
          println(output)
        }
        1
      }

      //    def orderStatusTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], c_by_name: Rep[Int], c_id: Rep[Int], c_last: Rep[String]): Rep[Int] = {
      def orderStatusTx(showOutput: Boolean, datetime: Date, t_num: Int, w_id: Int, d_id: Int, c_by_name: Int, c_id: Int, c_last: String): Int = {

        var customerEntry: GenericEntry /*(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = null
        if ($c_by_name > 0) {
          val customersWithLastName = ArrayBuffer[GenericEntry]()
          customerTbl.slice(1, GenericEntry("SteSampleSEntry", 2, 3, 6, $d_id, $w_id, $c_last), {
            case custEntry => customersWithLastName += custEntry
          })
          var index = customersWithLastName.size / 2
          if (customersWithLastName.size % 2 == 0) {
            index -= 1
          }
          customerEntry = customersWithLastName(index)
        } else {
          customerEntry = customerTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, 3, $c_id, $d_id, $w_id))
        }



        val found_c_id: Int = customerEntry.get(3)

        val newestOrderEntry: GenericEntry /*(o_id,o_d_id_arg,o_w_id_arg,o_c_id,o_entry_d,o_carrier_id,_,_)*/ = orderTbl.getSliceMax(1 /*o_id*/ , (2, $d_id), (3, $w_id), (4, found_c_id))

        var dceBlocker = 0
        if (!$showOutput) {
          if (newestOrderEntry != null) {
            //o_id != -1
            orderLineTbl.slice(1, GenericEntry("SteSampleSEntry", 1, 2, 3, newestOrderEntry.get(1), $d_id, $w_id), { case orderLineEntry /*(o_id,d_id,w_id,ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, _)*/ =>
              dceBlocker = 1 // fooling the effect system, in order not to remove this part, because that's not fare in benchmarking results!
            })
          }
        } else {
          val orderLines = ArrayBuffer[String]()
          if (newestOrderEntry != null) {
            //o_id != -1
            orderLineTbl.slice(1, GenericEntry("SteSampleSEntry", 1, 2, 3, newestOrderEntry.get(1), $d_id, $w_id), { case orderLineEntry /*(o_id,d_id,w_id,ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, _)*/ =>
              orderLines += "[%d - %d - %d - %f - %s]".format(orderLineEntry.get(6) /*ol_supply_w_id*/ , orderLineEntry.get(5) /*ol_i_id*/ , orderLineEntry.get(8) /*ol_quantity*/ , orderLineEntry.get(9) /*ol_amount*/ , if (orderLineEntry.get(7) == null) "99-99-9999" else (orderLineEntry.get(7)))
            })
          }
          val output = "\n+-------------------------- ORDER-STATUS -------------------------+\n" +
            " Date: " + $datetime +
            "\n\n Warehouse: " + $w_id +
            "\n District:  " + $d_id +
            "\n\n Customer:  " + found_c_id +
            "\n   Name:    " + customerEntry.get(4) +
            " " + customerEntry.get(5) +
            " " + customerEntry.get(6) +
            "\n   Balance: " + customerEntry.get(17) + "\n\n" +
            (if ( /*o_id*/ newestOrderEntry.get(1) == -1) {
              " Customer has no orders placed.\n"
            } else {
              " Order-Number: " + /*o_id*/ newestOrderEntry.get(1) +
                "\n    Entry-Date: " + /*o_entry_d*/ newestOrderEntry.get(5) +
                "\n    Carrier-Number: " + /*o_carrier_id*/ newestOrderEntry.get(6) + "\n\n" +
                (if (orderLines.size != 0) {
                  var out = " [Supply_W - Item_ID - Qty - Amount - Delivery-Date]\n"
                  var i = 0
                  while (i < orderLines.size) {
                    out = out + " " + orderLines(i) + "\n"
                    i += 1
                  }
                  out.toString
                }
                else {
                  " This Order has no Order-Lines.\n"
                })
            }) +
            "+-----------------------------------------------------------------+\n\n"
          println(output)
        }
        1
      }

  //        def deliveryTx(showOutput: Rep[Boolean], datetime: Rep[Date], w_id: Rep[Int], o_carrier_id: Rep[Int]): Rep[Int] = {
      def deliveryTx(showOutput: Boolean, datetime: Date, w_id: Int, o_carrier_id: Int): Int = {
  //          dsl """
        val DIST_PER_WAREHOUSE = 10
        val orderIDs = new Array[Int](10)
        var d_id = 1
        while (d_id <= DIST_PER_WAREHOUSE) {
          val firstOrderEntry: GenericEntry /*(no_o_id,no_d_id,no_w_id)*/ = $newOrderTbl.getSliceMin(1 /*no_o_id*/ , (2, d_id), (3, $w_id))
          if ((firstOrderEntry != null)) {
            // found
            val no_o_id = firstOrderEntry.get[Int](1)
            orderIDs(d_id - 1) = no_o_id
            $newOrderTbl.delete(firstOrderEntry)
            val orderEntry = $orderTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, 3, no_o_id, $d_id, $w_id))
            val c_id = orderEntry.get[Int](4)
            orderEntry.update(6 /*o_carrier_id*/ , $o_carrier_id)
            $orderTbl.update(orderEntry)

            var ol_total = 0f
            $orderLineTbl.slice(1, GenericEntry("SteSampleSEntry", 1, 2, 3, no_o_id, $d_id, $w_id), { case orderLineEntry /*(o_id,d_id,w_id,ol_number, ol_i_id, ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, ol_dist_info)*/ =>
              orderLineEntry.update(7, $datetime) //ol_delivery_d
              ol_total += orderLineEntry.get[Float](9) //ol_amount
              orderLineTbl.update(orderLineEntry)
            })

            val customerEntry /*(c_id, c_d_id, c_w_id, c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = $customerTbl.get(0, GenericEntry("SteSampleSEntry", 1, 2, 3, c_id, d_id, $w_id))
            customerEntry +=(17 /*c_balance*/ , ol_total)
            customerEntry +=(20 /*c_delivery_cnt*/ , 1)
            customerTbl.update(customerEntry)
          } else {
            // not found
            orderIDs(d_id - 1) = 0
          }
          d_id += 1
        }
        if ($showOutput) {
          var output = "\n+---------------------------- DELIVERY ---------------------------+\n" +
            " Date: " + $datetime +
            "\n\n Warehouse: " + $w_id +
            "\n Carrier:   " + $o_carrier_id +
            "\n\n Delivered Orders\n"
          var skippedDeliveries = 0
          var i = 1
          while (i <= 10) {
            if (orderIDs(i - 1) >= 0) {
              output = output + ("  District ") +
                (if (i < 10) " " else "") +
                (i) +
                (": Order number ") +
                (orderIDs(i - 1)) +
                (" was delivered.\n")
            }
            else {
              output = output + ("  District ") +
                (if (i < 10) " " else "") +
                (i) +
                (": No orders to be delivered.\n")
              skippedDeliveries += 1
            }
            i += 1
          }
          output = output + ("+-----------------------------------------------------------------+\n\n")
          println(output)
        }
        1
  //          """
      }
  */

  def stockLevelTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], threshold: Rep[Int]): Rep[Int] = {
    //    def stockLevelTx(showOutput: Boolean, datetime: Date, t_num: Int, w_id: Int, d_id: Int, threshold: Int): Int = {
    dsl"""

      val districtEntry /*(d_id,d_w_id,d_name,d_street_1,d_street_2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id)*/ = $districtTbl.get(0, GenericEntry("SteSampleSEntry",1,2, $d_id, $w_id))
      val o_id: = districtEntry.get[Int](11)
      var i = o_id - 20
      var unique_ol_i_id = Set[Int]()
      while (i < o_id) {
        $orderLineTbl.slice(1, GenericEntry("SteSampleSEntry",1,2,3,i,$d_id, $w_id), { case orderLineEntry /*(ol_o_id, ol_d_id, ol_w_id, ol_number,   ol_i_id, ol_supply_w_id, ol_delivery_d, ol_quantity, ol_amount, ol_dist_info)*/ =>
          val ol_i_id = orderLineEntry.get[Int](5)
          val stockEntry /*(s_i_id,s_w_id,s_quantity,s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data)*/ = $stockTbl.get(0, GenericEntry("SteSampleSEntry",1,2, ol_i_id, $w_id))
          val s_quantity = stockEntry.get[Int](3)
          if (s_quantity < $threshold) {
            unique_ol_i_id += (ol_i_id) //TODO: SBJ: Check if okay
          }
        })
        i += 1
      }
      val stock_count = unique_ol_i_id.size
      if ($showOutput) {
        val output = "\n+-------------------------- STOCK-LEVEL --------------------------+" +
          "\n Warehouse: " + $w_id +
          "\n District:  " + $d_id +
          "\n\n Stock Level Threshold: " + $threshold +
          "\n Low Stock Count:       " + stock_count +
          "\n+-----------------------------------------------------------------+\n\n"
        println(output)
      }
      1
    """.asInstanceOf[Rep[Int]]
  }


  def main(args: Array[String]): Unit = {
    //    (new Impl("./lms/tpcc/lmsgen/TpccBench.scala", "tpcc.lmsgen") with Prog).emitAll()
    val prgm = stockLevelTx(unit(true), unit(null.asInstanceOf[Date]), unit(0), unit(1), unit(2), unit(3))
    new TpccCompiler(Context).compile(prgm, "test/gen/tpcc.scala")
  }
}
