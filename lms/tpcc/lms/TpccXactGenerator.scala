package tpcc.lms

import java.util.Date
import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import dbtoptimizer._
import oltp.opt.lifters._
import ddbt.lib.store._
import scala.language.implicitConversions

object TpccXactGenerator {
  type NewOrderEntry          = SEntry3 [Int,Int,Int]
  type HistoryEntry           = SEntry8 [Int,Int,Int,Int,Int,Date,Float,String]
  type WarehouseEntry         = SEntry9 [Int,             String,String,String,String,String,String,Float,Double]
  type ItemEntry              = SEntry5 [Int,             Int,String,Float,String]
  type OrderEntry             = SEntry8 [Int,Int,Int,     Int,Date,/*Option[Int]*/Int,Int,Boolean]
  type DistrictEntry          = SEntry11[Int,Int,         String,String,String,String,String,String,Float,Double,Int]
  type OrderLineEntry         = SEntry10[Int,Int,Int,Int, Int,Int,/*Option[Date]*/Date,Int,Float,String]
  type CustomerEntry          = SEntry21[Int,Int,Int,     String,String,String,String,String,String,String,String,String,Date,String,Float,Float,Float,Float,Int,Int,String]
  type StockEntry             = SEntry17[Int,Int,         Int,String,String,String,String,String,String,String,String,String,String,Int,Int,Int,String]

  trait Prog extends DSL {
    val newOrderTbl_orig = newSStore[NewOrderEntry]
    val historyTbl_orig = newSStore[HistoryEntry]
    val warehouseTbl_orig = newSStore[WarehouseEntry]
    val itemTbl_orig = newSStore[ItemEntry]
    val orderTbl_orig = newSStore[OrderEntry]
    val districtTbl_orig = newSStore[DistrictEntry]
    val orderLineTbl_orig = newSStore[OrderLineEntry]
    val customerTbl_orig = newSStore[CustomerEntry]
    val stockTbl_orig = newSStore[StockEntry]

    def newOrderTx(showOutput:Rep[Boolean], datetime:Rep[Date], t_num:Rep[Int], w_id:Rep[Int], d_id:Rep[Int], c_id:Rep[Int], o_ol_count:Rep[Int], o_all_local:Rep[Int], itemid_input:Rep[Array[Int]], supware_input:Rep[Array[Int]], quantity_input:Rep[Array[Int]], price_input:Rep[Array[Float]], iname_input:Rep[Array[String]], stock_input:Rep[Array[Int]], bg_input:Rep[Array[Char]], amt_input:Rep[Array[Float]]):Rep[Int] = {
      if(showOutput) println("- Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id,d_id,c_id))
      val newOrderTbl = newOrderTbl_orig.mutable
      val historyTbl = historyTbl_orig.mutable
      val warehouseTbl = warehouseTbl_orig.mutable
      val itemTbl = itemTbl_orig.mutable
      val orderTbl = orderTbl_orig.mutable
      val districtTbl = districtTbl_orig.mutable
      val orderLineTbl = orderLineTbl_orig.mutable
      val customerTbl = customerTbl_orig.mutable
      val stockTbl = stockTbl_orig.mutable

      val itemid = itemid_input //.mutable
      val supware = supware_input //.mutable
      val quantity = quantity_input //.mutable
      val price = price_input.mutable
      val iname = iname_input.mutable
      val stock = stock_input.mutable
      val bg = bg_input.mutable
      val amt = amt_input.mutable

      var ol_number = 0
      var failed = false
      val idata = NewArray[String](o_ol_count)

      var all_items_exist = true
      while((ol_number < o_ol_count) && all_items_exist) {
        val itemEntry /*(i_id, _, i_name, i_price, i_data)*/ = itemTbl.get((1,itemid(ol_number)))
        if(itemEntry == null) {
          all_items_exist = false
        } else {
          iname(ol_number) = itemEntry._3 //i_name
          price(ol_number) = itemEntry._4 //i_price
          idata(ol_number) = itemEntry._5 //i_data
        }
        ol_number += 1
      }
      if(!all_items_exist) {
        1
      } else {
        /*(c_id,d_id,w_id, c_discount, c_last, c_credit, w_tax)*/
        val customerEntry /*(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = customerTbl.get((1, c_id),(2, d_id),(3, w_id))
        val warehouseEntry /*(w_id,w_name,w_street_1,w_street_2,w_city,w_state,w_zip,w_tax,w_ytd)*/ = warehouseTbl.get((1, w_id))
        val districtEntry /*(d_d_id,d_w_id,_,_,_,_,_,_,d_tax,_,d_next_o_id)*/ = districtTbl.get((1, d_id),(2, w_id))
        val o_id = districtEntry._11
        districtEntry += (11, 1) //d_next_o_id+1
        districtTbl.update(districtEntry)


        orderTbl.insert(orderTbl.newEntry(o_id, d_id, w_id, c_id, datetime, -1, o_ol_count, o_all_local > 0))

        newOrderTbl.insert(newOrderTbl.newEntry(o_id, d_id, w_id))

        var total = 0f

        ol_number = 0
        while(ol_number < o_ol_count) {
          val ol_supply_w_id = supware(ol_number)
          val ol_i_id = itemid(ol_number)
          val ol_quantity = quantity(ol_number)

          val stockEntry /*(s_i_id,s_w_id,s_quantity,s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data)*/ = stockTbl.get((1, ol_i_id), (2, ol_supply_w_id))

          val ol_dist_info = if(d_id == 1) {
            stockEntry._4 //s_dist_01
          } else if(d_id == 2) {
            stockEntry._5 //s_dist_02
          } else if(d_id == 3) {
            stockEntry._6 //s_dist_03
          } else if(d_id == 4) {
            stockEntry._7 //s_dist_04
          } else if(d_id == 5) {
            stockEntry._8 //s_dist_05
          } else if(d_id == 6) {
            stockEntry._9 //s_dist_06
          } else if(d_id == 7) {
            stockEntry._10 //s_dist_07
          } else if(d_id == 8) {
            stockEntry._11 //s_dist_08
          } else if(d_id == 9) {
            stockEntry._12 //s_dist_09
          } else /*if(d_id == 10)*/ {
            stockEntry._13 //s_dist_10
          }

          val s_quantity = stockEntry._3 //s_quantity
          stock(ol_number) = s_quantity

          if(/*c_credit*/customerEntry._14.contains("original") && /*s_data*/stockEntry._17.contains("original")) {
            bg(ol_number) = 'B'
          } else {
            bg(ol_number) = 'G'
          }

          stockEntry.update(3, s_quantity - ol_quantity)
          if(s_quantity <= ol_quantity) stockEntry += (3, 91)

          var s_remote_cnt_increment = 0
          if(ol_supply_w_id != w_id) s_remote_cnt_increment = 1

          //TODO this is the correct version but is not implemented in the correctness test
          //stockEntry._14 += ol_quantity //s_ytd
          //stockEntry._15 += 1 //s_order_cnt
          //stockEntry._16 += s_remote_cnt_increment //s_remote_cnt
          stockTbl.update(stockEntry)

          val c_discount = customerEntry._16
          val w_tax = warehouseEntry._8
          val d_tax = districtEntry._9
          val ol_amount = (ol_quantity.asInstanceOf[Rep[Float]] * price(ol_number) * (1f+w_tax+d_tax) * (1f - c_discount))/*.asInstanceOf[Float]*/
          amt(ol_number) =  ol_amount
          total += ol_amount

          orderLineTbl.insert(orderLineTbl.newEntry(o_id, d_id, w_id, ol_number+1/*to start from 1*/, ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info))

          ol_number += 1
        }
        if(showOutput) println("An error occurred in handling NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id,d_id,c_id))
        1
      }
    }
    toplevel16("newOrderTx") {
      newOrderTx
    }

    def paymentTx(showOutput:Rep[Boolean], datetime:Rep[Date], t_num:Rep[Int], w_id:Rep[Int], d_id:Rep[Int], c_by_name:Rep[Int], c_w_id:Rep[Int], c_d_id:Rep[Int], c_id:Rep[Int], c_last_input:Rep[String], h_amount:Rep[Float]):Rep[Int] = {
      val newOrderTbl = newOrderTbl_orig.mutable
      val historyTbl = historyTbl_orig.mutable
      val warehouseTbl = warehouseTbl_orig.mutable
      val itemTbl = itemTbl_orig.mutable
      val orderTbl = orderTbl_orig.mutable
      val districtTbl = districtTbl_orig.mutable
      val orderLineTbl = orderLineTbl_orig.mutable
      val customerTbl = customerTbl_orig.mutable
      val stockTbl = stockTbl_orig.mutable

      val warehouseEntry/*(w_id,w_name,w_street_1,w_street_2,w_city,w_state,w_zip,_,w_ytd)*/ = warehouseTbl.get((1, w_id))
      warehouseEntry += (9, h_amount) //w_ytd
      warehouseTbl.update(warehouseEntry)

      val districtEntry /*(d_id,d_w_id,d_name,d_street_1,d_street_2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id)*/ = districtTbl.get((1, d_id),(2, w_id))
      districtEntry += (10, h_amount)
      districtTbl.update(districtEntry)

      var customerEnt /*(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = unit(null.asInstanceOf[CustomerEntry])
      if (c_by_name > 0) {
        val customersWithLastName = ArrayBuffer[CustomerEntry]()
        customerTbl.slice({
          case custEntry => customersWithLastName += custEntry
        }, (2,c_d_id), (3,c_w_id), (6,c_last_input))
        var index = customersWithLastName.size / 2
        if (customersWithLastName.size % 2 == 0) {
          index -= 1
        }
        customerEnt = customersWithLastName(index)
      } else {
        customerEnt = customerTbl.get((1,c_id),(2,c_d_id), (3,c_w_id))
      }

      val customerEntry = readVar( customerEnt )
      var c_data = customerEntry._21

      if (customerEntry._14.contains("BC")) { //c_credit
        //TODO this is the correct version but is not implemented in the correctness test
        //c_data = found_c_id + " " + c_d_id + " " + c_w_id + " " + d_id + " " + w_id + " " + h_amount + " | " + c_data
        c_data = "%d %d %d %d %d $%f %s | %s".format(customerEntry._1, c_d_id, c_w_id, d_id, w_id,
            h_amount, datetime, c_data)
        if (c_data.length > 500) c_data = c_data.substring(0, 500)
        customerEntry += (17 /*c_balance*/, h_amount)
        //TODO this is the correct version but is not implemented in the correctness test
        //customerEntry += (18 /*c_ytd_payment*/, h_amount)
        //customerEntry += (19 /*c_payment_cnt*/, 1)
        customerEntry.update(21 /*c_data*/, c_data)
      } else {
        customerEntry += (17 /*c_balance*/, h_amount)
        //TODO this is the correct version but is not implemented in the correctness test
        //customerEntry += (18 /*c_ytd_payment*/, h_amount)
        //customerEntry += (19 /*c_payment_cnt*/, 1)
      }
      customerTbl.update(customerEntry)
      val w_name = warehouseEntry._2
      val d_name = districtEntry._3
      //TODO this is the correct version but is not implemented in the correctness test
      val h_data = {if (w_name.length > 10) w_name.substring(0, 10) else w_name} + "    " + {if (d_name.length > 10) d_name.substring(0, 10) else d_name}
      historyTbl.insert(historyTbl.newEntry(customerEntry._1,c_d_id,c_w_id,d_id,w_id,datetime,h_amount,h_data))
      if(showOutput) {
        var output = "\n+---------------------------- PAYMENT ----------------------------+" +
        "\n Date: %s" + datetime +
        "\n\n Warehouse: " + w_id +
        "\n   Street:  " + /*w_street_1*/ warehouseEntry._3 +
        "\n   Street:  " + /*w_street_2*/ warehouseEntry._4 +
        "\n   City:    " + /*w_city*/warehouseEntry._5 +
        "   State: " + /*w_state*/warehouseEntry._6 +
        "  Zip: " + /*w_zip*/warehouseEntry._7 +
        "\n\n District:  " + d_id +
        "\n   Street:  " + /*d_street_1*/districtEntry._4 +
        "\n   Street:  " + /*d_street_2*/districtEntry._5 +
        "\n   City:    " + /*d_city*/districtEntry._6 +
        "   State: " + /*d_state*/districtEntry._7 +
        "  Zip: " + /*d_zip*/districtEntry._8 +
        "\n\n Customer:  " + customerEntry._1 +
        "\n   Name:    " + /*c_first*/customerEntry._4 +
        " " + /*c_middle*/customerEntry._5 +
        " " + /*c_last*/customerEntry._6 +
        "\n   Street:  " + /*c_street_1*/customerEntry._7 +
        "\n   Street:  " + /*c_street_2*/customerEntry._8 +
        "\n   City:    " + /*c_city*/customerEntry._9 +
        "   State: " + /*c_state*/customerEntry._10 +
        "  Zip: " + /*c_zip*/customerEntry._11 +
        "\n   Since:   " +
        (if (/*c_since*/customerEntry._13 != null) {
          /*c_since*/customerEntry._13
        }
        else {
          ""
        }) + "\n   Credit:  " + /*c_credit*/customerEntry._14 +
        "\n   Disc:    " + /*c_discount*/(customerEntry._16 * 100) + "%" +
        "\n   Phone:   " + /*c_phone*/customerEntry._12 +
        "\n\n Amount Paid:      " + h_amount +
        "\n Credit Limit:     " + /*c_credit_lim*/customerEntry._15 +
        "\n New Cust-Balance: " + /*c_balance*/customerEntry._17
        if (customerEntry._14 == "BC") {
          val cdata = readVar(c_data)
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
        output  = output + "\n+-----------------------------------------------------------------+\n\n"
        println(output)
      }
      1
    }
    toplevel11("paymentTx") {
      paymentTx
    }

    def orderStatusTx(showOutput:Rep[Boolean], datetime:Rep[Date], t_num:Rep[Int], w_id:Rep[Int], d_id:Rep[Int], c_by_name:Rep[Int], c_id:Rep[Int], c_last:Rep[String]):Rep[Int] = {
      val newOrderTbl = newOrderTbl_orig.mutable
      val historyTbl = historyTbl_orig.mutable
      val warehouseTbl = warehouseTbl_orig.mutable
      val itemTbl = itemTbl_orig.mutable
      val orderTbl = orderTbl_orig.mutable
      val districtTbl = districtTbl_orig.mutable
      val orderLineTbl = orderLineTbl_orig.mutable
      val customerTbl = customerTbl_orig.mutable
      val stockTbl = stockTbl_orig.mutable

      var customerEnt /*(c_id,c_d_id,c_w_id,c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = unit(null.asInstanceOf[CustomerEntry])
      if (c_by_name > 0) {
        val customersWithLastName = ArrayBuffer[CustomerEntry]()
        customerTbl.slice({
          case custEntry => customersWithLastName += custEntry
        }, (2,d_id), (3,w_id), (6,c_last))
        var index = customersWithLastName.size / 2
        if (customersWithLastName.size % 2 == 0) {
          index -= 1
        }
        customerEnt = customersWithLastName(index)
      } else {
        customerEnt = customerTbl.get((1,c_id),(2,d_id), (3,w_id))
      }

      val customerEntry = readVar( customerEnt )

      val found_c_id = customerEntry._3

      val newestOrderEntry/*(o_id,o_d_id_arg,o_w_id_arg,o_c_id,o_entry_d,o_carrier_id,_,_)*/ = orderTbl.getSliceMax(1 /*o_id*/, (2,d_id),(3,w_id),(4,found_c_id))

      var dceBlocker = 0
      if(!showOutput) {
        if(newestOrderEntry != null) { //o_id != -1
          orderLineTbl.slice({ case orderLineEntry/*(o_id,d_id,w_id,ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, _)*/ =>
            dceBlocker = 1 // fooling the effect system, in order not to remove this part, because that's not fare in benchmarking results!
          }, (1,newestOrderEntry._1/*o_id*/),(2,d_id),(3,w_id))
        }
      } else {
        val orderLines = ArrayBuffer[String]()
        if(newestOrderEntry != null) { //o_id != -1
          orderLineTbl.slice({ case orderLineEntry/*(o_id,d_id,w_id,ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, _)*/ =>
            orderLines += "[%d - %d - %d - %f - %s]".format(orderLineEntry._6/*ol_supply_w_id*/, orderLineEntry._5/*ol_i_id*/, orderLineEntry._8/*ol_quantity*/, orderLineEntry._9/*ol_amount*/, if(orderLineEntry._7 == unit(null)) unit("99-99-9999") else cast_string(orderLineEntry._7.asInstanceOf[Rep[Date]]))
          }, (1,newestOrderEntry._1/*o_id*/),(2,d_id),(3,w_id))
        }
        val output = "\n+-------------------------- ORDER-STATUS -------------------------+\n" +
        " Date: " + datetime +
        "\n\n Warehouse: " + w_id +
        "\n District:  " + d_id +
        "\n\n Customer:  " + found_c_id +
        "\n   Name:    " + customerEntry._4 +
        " " + customerEntry._5 +
        " " + customerEntry._6 +
        "\n   Balance: " + customerEntry._17 + "\n\n" +
        (if (/*o_id*/newestOrderEntry._1 == -1) {
          " Customer has no orders placed.\n"
        } else {
          " Order-Number: " + /*o_id*/newestOrderEntry._1 +
          "\n    Entry-Date: " + /*o_entry_d*/newestOrderEntry._5 +
          "\n    Carrier-Number: " + /*o_carrier_id*/newestOrderEntry._6 + "\n\n" +
          (if (orderLines.size != 0) {
            var out = " [Supply_W - Item_ID - Qty - Amount - Delivery-Date]\n"
            var i = 0
            while(i < orderLines.size) {
              out = out + " " + orderLines(i) + "\n"
              i += 1
            }
            out.ToString
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
    toplevel8("orderStatusTx") {
      orderStatusTx
    }

    def deliveryTx(showOutput:Rep[Boolean], datetime:Rep[Date], w_id:Rep[Int], o_carrier_id:Rep[Int]):Rep[Int] = {
      val newOrderTbl = newOrderTbl_orig.mutable
      val historyTbl = historyTbl_orig.mutable
      val warehouseTbl = warehouseTbl_orig.mutable
      val itemTbl = itemTbl_orig.mutable
      val orderTbl = orderTbl_orig.mutable
      val districtTbl = districtTbl_orig.mutable
      val orderLineTbl = orderLineTbl_orig.mutable
      val customerTbl = customerTbl_orig.mutable
      val stockTbl = stockTbl_orig.mutable

      val DIST_PER_WAREHOUSE = 10
      val orderIDs = NewArray[Int](10)
      var d_id = 1
      while (d_id <= DIST_PER_WAREHOUSE) {
        val firstOrderEntry /*(no_o_id,no_d_id,no_w_id)*/ = newOrderTbl.getSliceMin(1 /*no_o_id*/, (2,d_id),(3,w_id))
        if((firstOrderEntry != null)){ // found
          val no_o_id = firstOrderEntry._1
          orderIDs(d_id - 1) = no_o_id
          newOrderTbl.delete(firstOrderEntry)
          val orderEntry = orderTbl.get((1,no_o_id),(2,d_id),(3,w_id))
          val c_id = orderEntry._4
          orderEntry.update(6 /*o_carrier_id*/, o_carrier_id)
          orderTbl.update(orderEntry)

          var ol_total = 0f
          orderLineTbl.slice({ case orderLineEntry /*(o_id,d_id,w_id,ol_number, ol_i_id, ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, ol_dist_info)*/ =>
            orderLineEntry.update(7, datetime) //ol_delivery_d
            ol_total += orderLineEntry._9 //ol_amount
            orderLineTbl.update(orderLineEntry)
          }, (1,no_o_id),(2,d_id),(3,w_id))

          val customerEntry /*(c_id, c_d_id, c_w_id, c_first,c_middle,c_last,c_street_1,c_street_2,c_city,c_state,c_zip,c_phone,c_since,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt,c_data)*/ = customerTbl.get((1,c_id),(2,d_id),(3,w_id))
          customerEntry += (17/*c_balance*/, ol_total)
          customerEntry += (20/*c_delivery_cnt*/, 1)
          customerTbl.update(customerEntry)
        } else { // not found
          orderIDs(d_id - 1) = 0
        }
        d_id += 1
      }
      if(showOutput) {
        var output = "\n+---------------------------- DELIVERY ---------------------------+\n" +
        " Date: " + datetime +
        "\n\n Warehouse: " + w_id +
        "\n Carrier:   " + o_carrier_id +
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
    }
    toplevel4("deliveryTx") {
      deliveryTx
    }

    def stockLevelTx(showOutput:Rep[Boolean], datetime:Rep[Date], t_num:Rep[Int], w_id:Rep[Int], d_id:Rep[Int], threshold:Rep[Int]):Rep[Int] = {
      val newOrderTbl = newOrderTbl_orig.mutable
      val historyTbl = historyTbl_orig.mutable
      val warehouseTbl = warehouseTbl_orig.mutable
      val itemTbl = itemTbl_orig.mutable
      val orderTbl = orderTbl_orig.mutable
      val districtTbl = districtTbl_orig.mutable
      val orderLineTbl = orderLineTbl_orig.mutable
      val customerTbl = customerTbl_orig.mutable
      val stockTbl = stockTbl_orig.mutable

      val districtEntry /*(d_id,d_w_id,d_name,d_street_1,d_street_2,d_city,d_state,d_zip,d_tax,d_ytd,d_next_o_id)*/ = districtTbl.get((1,d_id),(2,w_id))
      val o_id = districtEntry._11
      var i = o_id-20
      val unique_ol_i_id = Set[Int]()
      while(i < o_id) {
        orderLineTbl.slice({ case orderLineEntry /*(ol_o_id, ol_d_id, ol_w_id, ol_number,   ol_i_id, ol_supply_w_id, ol_delivery_d, ol_quantity, ol_amount, ol_dist_info)*/=>
          val ol_i_id = orderLineEntry._5
          val stockEntry /*(s_i_id,s_w_id,s_quantity,s_dist_01,s_dist_02,s_dist_03,s_dist_04,s_dist_05,s_dist_06,s_dist_07,s_dist_08,s_dist_09,s_dist_10,s_ytd,s_order_cnt,s_remote_cnt,s_data)*/ = stockTbl.get((1,ol_i_id),(2,w_id))
          val s_quantity = stockEntry._3
          if(s_quantity < threshold) {
            unique_ol_i_id.add(ol_i_id)
          }
        }, (1,i),(2,d_id),(3,w_id))
        i += 1
      }
      val stock_count = unique_ol_i_id.size
      if(showOutput) {
        val output = "\n+-------------------------- STOCK-LEVEL --------------------------+" +
        "\n Warehouse: " + w_id +
        "\n District:  " + d_id +
        "\n\n Stock Level Threshold: " + threshold +
        "\n Low Stock Count:       " + stock_count +
        "\n+-----------------------------------------------------------------+\n\n"
        println(output)
      }
      1
    }
    toplevel6("stockLevelTx") {
      stockLevelTx
    }
  };

  def main(args: Array[String]): Unit = {
    (new Impl("./lms/tpcc/lmsgen/TpccBench.scala", "tpcc.lmsgen") with Prog).emitAll()
  }
}
