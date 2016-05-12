package sc.tpcc


//import ddbt.lib.store.{Store, GenericEntry}
import java.io.{FileWriter, PrintStream, PrintWriter}
import java.util.concurrent.Executor

import ch.epfl.data.sc.pardis
import ch.epfl.data.sc.pardis.ir.{Statement, StructElemInformation, PardisStructDef, StructTags}
import ch.epfl.data.sc.pardis.types.{RecordType, AnyType}
import ch.epfl.data.sc.pardis.utils.document.Document
import ddbt.codegen.{Optimizer, TransactionProgram}
import ddbt.codegen.prettyprinter.StoreScalaCodeGenerator
import sc.tpcc.compiler.TpccCompiler

import ddbt.lib.store.deep._

import ch.epfl.data.sc.pardis.prettyprinter.{ASTCodeGenerator, ScalaCodeGenerator, CodeGenerator}
import ch.epfl.data.sc.pardis.types.PardisTypeImplicits.typeUnit
import pardis.optimization._
import pardis.compiler._
import ddbt.transformer._
import scala.language.implicitConversions

object TpccXactGenerator_SC {

  class Prog(val Context: StoreDSL) {

    //    import Context.Predef._
    //    import Context.{__newStore, Date, overloaded2, typeGenericEntry}
    //    import Context.{entryRepToGenericEntryOps => _ , _}
    import Context.{EntryType => _, entryRepToGenericEntryOps => _, typeStore => _, typeNull => _, println => _, _}

    implicit val DSL = Context

    val NewOrderEntry = List(IntType, IntType, IntType)
    val HistoryEntry = List(IntType, IntType, IntType, IntType, IntType, DateType, DoubleType, StringType)
    val WarehouseEntry = List(IntType, StringType, StringType, StringType, StringType, StringType, StringType, DoubleType, DoubleType)
    val ItemEntry = List(IntType, IntType, StringType, DoubleType, StringType)
    val OrderEntry = List(IntType, IntType, IntType, IntType, DateType, /*Option[Int]*/ IntType, IntType, BooleanType)
    val DistrictEntry = List(IntType, IntType, StringType, StringType, StringType, StringType, StringType, StringType, DoubleType, DoubleType, IntType)
    val OrderLineEntry = List(IntType, IntType, IntType, IntType, IntType, IntType, /*Option[Date]*/ DateType, IntType, DoubleType, StringType)
    val CustomerEntry = List(IntType, IntType, IntType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, DateType, StringType, DoubleType, DoubleType, DoubleType, DoubleType, IntType, IntType, StringType)
    val StockEntry = List(IntType, IntType, IntType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, IntType, IntType, IntType, StringType)

    val newOrderTbl = __newStore[GenericEntry]
    val historyTbl = __newStore[GenericEntry]
    val warehouseTbl = __newStore[GenericEntry]
    val itemTbl = __newStore[GenericEntry]
    val orderTbl = __newStore[GenericEntry]
    val districtTbl = __newStore[GenericEntry]
    val orderLineTbl = __newStore[GenericEntry]
    val customerTbl = __newStore[GenericEntry]
    val stockTbl = __newStore[GenericEntry]
    val schema = List[(Rep[_], List[TypeRep[_]])](newOrderTbl -> NewOrderEntry, historyTbl -> HistoryEntry, warehouseTbl -> WarehouseEntry, itemTbl -> ItemEntry, orderTbl -> OrderEntry, districtTbl -> DistrictEntry, orderLineTbl -> OrderLineEntry, customerTbl -> CustomerEntry, stockTbl -> StockEntry)

    def newOrderTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], c_id: Rep[Int], o_ol_count: Rep[Int], o_all_local: Rep[Int], itemid: Rep[Array[Int]], supware: Rep[Array[Int]], quantity: Rep[Array[Int]], price: Rep[Array[Double]], iname: Rep[Array[String]], stock: Rep[Array[Int]], bg: Rep[Array[String]], amt: Rep[Array[Double]]): Rep[Int] = {

      __ifThenElse(showOutput, {
        val output = unit("Started NewOrder transaction for warehouse=%d, district=%d, customer=%d").format(unit("FIX ME"), w_id, d_id, c_id)
        Context.println(output)
      }, unit())

      val ol_number = __newVar(unit(0))
      val failed = __newVar(unit(false))
      val idata = __newArray[String](o_ol_count)

      val all_items_exist = __newVar(unit(true))
      __whileDo((readVar(ol_number) < o_ol_count) && all_items_exist, {

        val itemEntry /*(i_id, _, i_name, i_price, i_data)*/ = itemTbl.get1((1, itemid(readVar(ol_number))))
        __ifThenElse(itemEntry __== unit[GenericEntry](null), {
          __assign(all_items_exist, unit(false))
          unit()
        }, {
          iname.update(readVar(ol_number), itemEntry.get[String](unit(3))) //i_name
          price.update(readVar(ol_number), itemEntry.get[Double](unit(4))) //i_price
          idata.update(ol_number, itemEntry.get[String](unit(5))) //i_data
        })
        __assign(ol_number, readVar(ol_number) + unit(1))
        unit()
      })
      __ifThenElse(readVar(all_items_exist), {

        /*(c_id,d_id,w_id, c_discount, c_last, c_credit, w_tax)*/
        val customerEntry = customerTbl.get1((1, c_id), (2, d_id), (3, w_id))
        val warehouseEntry = warehouseTbl.get1((1, w_id))
        val districtEntry = districtTbl.get1((1, d_id), (2, w_id))
        val o_id = districtEntry.get[Int](unit(11))
        districtEntry +=(unit(11), unit(1)) //d_next_o_id+1
        districtTbl.update(districtEntry)


        orderTbl.insert(GenericEntry(unit("SteNewSEntry"), o_id, d_id, w_id, c_id, datetime, unit(-1), o_ol_count, o_all_local > unit(0)))
        newOrderTbl.insert(GenericEntry(unit("SteNewSEntry"), o_id, d_id, w_id))

        val total = __newVar(unit(0.0))

        __assign(ol_number, unit(0))
        __whileDo(readVar(ol_number) < o_ol_count, {
          val ol_supply_w_id = supware(readVar(ol_number))
          val ol_i_id = itemid(readVar(ol_number))
          val ol_quantity = quantity(readVar(ol_number))

          val stockEntry = stockTbl.get1((1, ol_i_id), (2, ol_supply_w_id))
          val ol_dist_info =
            dsl""" if ($d_id == 1) {
                 ${stockEntry.get[String](unit(4))} //s_dist_01
               } else if ($d_id == 2) {
                 ${stockEntry.get[String](unit(5))} //s_dist_02
               } else if ($d_id == 3) {
                 ${stockEntry.get[String](unit(6))} //s_dist_03
               } else if (d_id == 4) {
                 ${stockEntry.get[String](unit(7))} //s_dist_04
               } else if (d_id == 5) {
                 ${stockEntry.get[String](unit(8))} //s_dist_05
               } else if (d_id == 6) {
                 ${stockEntry.get[String](unit(9))} //s_dist_06
               } else if (d_id == 7) {
                ${stockEntry.get[String](unit(10))} //s_dist_07
               } else if (d_id == 8) {
                 ${stockEntry.get[String](unit(11))} //s_dist_08
               } else if (d_id == 9) {
                 ${stockEntry.get[String](unit(12))} //s_dist_09
               } else /*if(d_id == 10)*/ {
                 ${stockEntry.get[String](unit(13))} //s_dist_10
               }"""

          val s_quantity = stockEntry.get[Int](unit(3)) //s_quantity
          stock.update(readVar(ol_number), s_quantity)

          __ifThenElse(customerEntry.get[String](unit(14)).contains(unit("original")) && /*s_data*/ stockEntry.get[String](unit(17)).contains(unit("original")), {
            bg.update(readVar(ol_number), unit("B"))
            unit()
          }, {
            bg.update(readVar(ol_number), unit("G"))
            unit()
          })

          stockEntry.update(unit(3), s_quantity - ol_quantity)
          __ifThenElse(s_quantity <= ol_quantity, stockEntry +=(unit(3), unit(91)), unit())

          val s_remote_cnt_increment = __newVar(unit(0))
          dsl"""if ($ol_supply_w_id != $w_id) $s_remote_cnt_increment = 1"""

          //TODO this is the correct version but is not implemented in the correctness test
          //stockEntry._14 += ol_quantity //s_ytd
          //stockEntry._15 += 1 //s_order_cnt
          //stockEntry._16 += s_remote_cnt_increment //s_remote_cnt
          stockTbl.update(stockEntry)

          val c_discount = customerEntry.get[Double](unit(16))
          val w_tax = warehouseEntry.get[Double](unit(8))
          val d_tax = districtEntry.get[Double](unit(9))
          val ol_amount = (ol_quantity * price(readVar(ol_number)) * (unit(1.0) + w_tax + d_tax) * (unit(1.0) - c_discount)) /*.asInstanceOf[Double]*/
          amt.update(readVar(ol_number), ol_amount)
          __assign(total, readVar(total) + ol_amount)

          orderLineTbl.insert(GenericEntry(unit("SteNewSEntry"), o_id, d_id, w_id, readVar(ol_number) + unit(1) /*to start from 1*/ , ol_i_id, ol_supply_w_id, unit[Date](null), ol_quantity, ol_amount, ol_dist_info))

          __assign(ol_number, readVar(ol_number) + unit(1))
          unit()
        })
        //             if (showOutput) println("An error occurred in handling NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id, d_id, c_id))
        unit()
      }, unit())

      unit(1)
    }

    def paymentTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], c_by_name: Rep[Int], c_w_id: Rep[Int], c_d_id: Rep[Int], c_id: Rep[Int], c_last_input: Rep[String], h_amount: Rep[Double]): Rep[Int] = {
      val warehouseEntry = warehouseTbl.get1((1, w_id))
      warehouseEntry +=(unit(9), h_amount) //w_ytd
      warehouseTbl.update(warehouseEntry)

      val districtEntry = districtTbl.get1((1, d_id), (2, w_id))
      districtEntry +=(unit(10), h_amount)
      districtTbl.update(districtEntry)

      val customerEntry = __newVar(unit[GenericEntry](null))
      __ifThenElse(c_by_name > unit(0), {
        val customersWithLastName = __newArrayBuffer[GenericEntry]()
        customerTbl.slice(unit(0), GenericEntry(unit("SteSampleSEntry"), unit(2), unit(3), unit(6), c_d_id, c_w_id, c_last_input), __lambda { custEntry => customersWithLastName.append(custEntry)
        })
        val index = __newVar(customersWithLastName.size / unit(2))
        __ifThenElse(customersWithLastName.size % unit(2) __== unit(0), {
          __assign(index, readVar(index) - unit(1))
        }, unit())
        __assign(customerEntry, customersWithLastName.sortWith(__lambda { (c1, c2) => c1.get[String](unit(4)).diff(c2.get[String](unit(4))) < unit(0) })(readVar(index)))

      }, {
        __assign(customerEntry, customerTbl.get1((1, c_id), (2, c_d_id), (3, c_w_id)))

      })

      val c_data = __newVar(readVar(customerEntry).get[String](unit(21)))

      __ifThenElse(readVar(customerEntry).get[String](unit(14)).contains(unit("BC")), {
        //c_credit
        //TODO this is the correct version but is not implemented in the correctness test
        //c_data = found_c_id + " " + c_d_id + " " + c_w_id + " " + d_id + " " + w_id + " " + h_amount + " | " + c_data
        __assign(c_data, unit("%d %d %d %d %d $%f %s | %s").format(unit("FIX ME"), readVar(customerEntry).get[Int](unit(1)), c_d_id, c_w_id, d_id, w_id, h_amount, datetime, readVar(c_data)))
        __ifThenElse(readVar(c_data).length > unit(500), __assign(c_data, readVar(c_data).substring(unit(0), unit(500))), unit())
        readVar(customerEntry) +=(unit(17) /*c_balance*/ , h_amount)
        //TODO this is the correct version but is not implemented in the correctness test
        //customerEntry += (18 /*c_ytd_payment*/, h_amount)
        //customerEntry += (19 /*c_payment_cnt*/, 1)
        readVar(customerEntry).update(unit(21) /*c_data*/ , readVar(c_data))
        unit()
      }, {
        readVar(customerEntry) +=(unit(17) /*c_balance*/ , h_amount)
        //TODO this is the correct version but is not implemented in the correctness test
        //customerEntry += (18 /*c_ytd_payment*/, h_amount)
        //customerEntry += (19 /*c_payment_cnt*/, 1)
      })
      customerTbl.update(readVar(customerEntry))
      val w_name = warehouseEntry.get[String](unit(2))
      val d_name = districtEntry.get[String](unit(3))
      //TODO this is the correct version but is not implemented in the correctness test
      val h_data =
        dsl"""{
        if (${w_name.length} > 10) $w_name.substring(0, 10) else $w_name
      } + "    " + {
        if (${d_name.length} > 10) $d_name.substring(0, 10) else $d_name
      }"""
      historyTbl.insert(GenericEntry(unit("SteNewSEntry"), readVar(customerEntry).get[Int](unit(1)), c_d_id, c_w_id, d_id, w_id, datetime, h_amount, h_data))
      //      if ($showOutput) {
      //        var output = "\n+---------------------------- PAYMENT ----------------------------+" +
      //          "\n Date: %s" + $datetime +
      //          "\n\n Warehouse: " + $w_id +
      //          "\n   Street:  " + /*w_street_1*/ warehouseEntry.get(3) +
      //          "\n   Street:  " + /*w_street_2*/ warehouseEntry.get(4) +
      //          "\n   City:    " + /*w_city*/ warehouseEntry.get(5) +
      //          "   State: " + /*w_state*/ warehouseEntry.get(6) +
      //          "  Zip: " + /*w_zip*/ warehouseEntry.get(7) +
      //          "\n\n District:  " + $d_id +
      //          "\n   Street:  " + /*d_street_1*/ districtEntry.get(4) +
      //          "\n   Street:  " + /*d_street_2*/ districtEntry.get(5) +
      //          "\n   City:    " + /*d_city*/ districtEntry.get(6) +
      //          "   State: " + /*d_state*/ districtEntry.get(7) +
      //          "  Zip: " + /*d_zip*/ districtEntry.get(8) +
      //          "\n\n Customer:  " + customerEntry.get(1) +
      //          "\n   Name:    " + /*c_first*/ customerEntry.get(4) +
      //          " " + /*c_middle*/ customerEntry.get(5) +
      //          " " + /*c_last*/ customerEntry.get(6) +
      //          "\n   Street:  " + /*c_street_1*/ customerEntry.get(7) +
      //          "\n   Street:  " + /*c_street_2*/ customerEntry.get(8) +
      //          "\n   City:    " + /*c_city*/ customerEntry.get(9) +
      //          "   State: " + /*c_state*/ customerEntry.get(10) +
      //          "  Zip: " + /*c_zip*/ customerEntry.get(11) +
      //          "\n   Since:   " +
      //          (if ( /*c_since*/ customerEntry.get(13) != null) {
      //            /*c_since*/ customerEntry.get(13)
      //          }
      //          else {
      //            ""
      //          }) + "\n   Credit:  " + /*c_credit*/ customerEntry.get(14) +
      //          "\n   Disc:    " + /*c_discount*/ (customerEntry.get(16).asInstanceOf[Double] * 100) + "%" +
      //          "\n   Phone:   " + /*c_phone*/ customerEntry.get(12) +
      //          "\n\n Amount Paid:      " + h_amount +
      //          "\n Credit Limit:     " + /*c_credit_lim*/ customerEntry.get(15) +
      //          "\n New Cust-Balance: " + /*c_balance*/ customerEntry.get(17)
      //        if (customerEntry.get(14) == "BC") {
      //          val cdata = c_data
      //          if (cdata.length > 50) {
      //            output = output + "\n\n Cust-Data: " + cdata.substring(0, 50)
      //            val data_chunks = (if (cdata.length > 200) 4 else cdata.length / 50)
      //            var n = 1
      //            while (n < data_chunks) {
      //              output = output + "\n            " + cdata.substring(n * 50, (n + 1) * 50)
      //              n += 1
      //            }
      //          } else {
      //            output = output + "\n\n Cust-Data: " + cdata
      //          }
      //        }
      //        output = output + "\n+-----------------------------------------------------------------+\n\n"
      //        println(output)
      //      }
      unit(1)
    }

    def orderStatusTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], c_by_name: Rep[Int], c_id: Rep[Int], c_last: Rep[String]): Rep[Int] = {

      val customerEntry = __newVar[GenericEntry](unit(null))
      __ifThenElse(c_by_name > unit(0), {
        val customersWithLastName = __newArrayBuffer[GenericEntry]()
        customerTbl.slice(unit(0), GenericEntry(unit("SteSampleSEntry"), unit(2), unit(3), unit(6), d_id, w_id, c_last), __lambda {
          custEntry => customersWithLastName.append(custEntry)
        })
        val index = __newVar(customersWithLastName.size / unit(2))
        __ifThenElse(customersWithLastName.size % unit(2) __== unit(0), {
          __assign(index, readVar(index) - unit(1))
        }, unit())

        __assign(customerEntry, customersWithLastName.sortWith(__lambda { (c1, c2) => c1.get[String](unit(4)).diff(c2.get[String](unit(4))) < unit(0) })(readVar(index)))
      }, {
        __assign(customerEntry, customerTbl.get1((1, c_id), (2, d_id), (3, w_id)))
      })

      val found_c_id = readVar(customerEntry).get[Int](unit(3))
      val agg = Aggregator.max[GenericEntry, Int](__lambda { e => e.get[Int](unit(1)) })
      orderTbl.slice(unit(0), GenericEntry(unit("SteSampleSEntry"), unit(2), unit(3), unit(4), d_id, w_id, found_c_id), agg)
      val newestOrderEntry = agg.result
      val dceBlocker = __newVar(unit(0))
      /*
dsl"""
      if (!$showOutput) {
        if ($newestOrderEntry != ${unit[GenericEntry](null)}) {
          //o_id != -1
//          $orderLineTbl.slice(1, GenericEntry("SteSampleSEntry".asInstanceOf[Any], 1, 2, 3, $newestOrderEntry.get[Int](1), $d_id, $w_id), { orderLineEntry /*(o_id,d_id,w_id,ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, _)*/ =>
//            $dceBlocker = 1 // fooling the effect system, in order not to remove this part, because that's not fare in benchmarking results!
//          })
        }
      } else {
        val orderLines = ${ArrayBuffer[String]()}
        if ($newestOrderEntry != ${unit[GenericEntry](null)}) {
          //o_id != -1
          //          $orderLineTbl.slice(1, GenericEntry("SteSampleSEntry".asInstanceOf[Any], 1, 2, 3, $newestOrderEntry.get[Int](1), $d_id, $w_id), { orderLineEntry /*(o_id,d_id,w_id,ol_i_id,ol_supply_w_id,ol_delivery_d, ol_quantity, ol_amount, _)*/ =>
          //            orderLines += "[%d - %d - %d - %f - %s]".format(orderLineEntry.get[Int](6) /*ol_supply_w_id*/ , orderLineEntry.get[Int](5) /*ol_i_id*/ , orderLineEntry.get[Int](8) /*ol_quantity*/ , orderLineEntry.get[Double](9) /*ol_amount*/ , if (orderLineEntry.get[Date](7) == null) "99-99-9999" else (orderLineEntry.get[Date](7)))
          //          })
        }

        val output = "\n+-------------------------- ORDER-STATUS -------------------------+\n" +
          " Date: " + $datetime +
          "\n\n Warehouse: " + $w_id +
          "\n District:  " + $d_id +
          "\n\n Customer:  " + $found_c_id +
          "\n   Name:    " + ${readVar(customerEntry).get[String](unit(4))} +
          " " + ${readVar(customerEntry).get[String](unit(5))} +
          " " + ${readVar(customerEntry).get[String](unit(6))} +
          "\n   Balance: " + $customerEntry.get[Double](17) + "\n\n" +
          (if ( /*o_id*/ ${newestOrderEntry.get[Int](unit(1))} == -1) {
            " Customer has no orders placed.\n"
          } else {
//            " Order-Number: " + /*o_id*/ $newestOrderEntry.get[Int](1) +
//              "\n    Entry-Date: " + /*o_entry_d*/ $newestOrderEntry.get[Date](5) +
//              "\n    Carrier-Number: " + /*o_carrier_id*/ $newestOrderEntry.get[Int](6) + "\n\n" +
              (if (orderLines.size != 0) {
                var out = " [Supply_W - Item_ID - Qty - Amount - Delivery-Date]\n"
                var i:Int = 0

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
        ()
      }"""
      */
      unit(1)
    }

    def deliveryTx(showOutput: Rep[Boolean], datetime: Rep[Date], w_id: Rep[Int], o_carrier_id: Rep[Int]): Rep[Int] = {
      //        def deliveryTx(showOutput: Boolean, datetime: Date, w_id: Int, o_carrier_id: Int): Int = {

      val DIST_PER_WAREHOUSE = unit(10)
      val orderIDs = __newArray[Int](unit(10))
      val d_id = __newVar(unit(1))
      __whileDo(readVar(d_id) <= DIST_PER_WAREHOUSE, {
        val agg = Aggregator.min[GenericEntry, Int](__lambda { e => e.get[Int](unit(1)) })
        newOrderTbl.slice(unit(0) /*no_o_id*/ , GenericEntry(unit("SteSampleSEntry"), unit(2), unit(3), readVar(d_id), w_id), agg)
        val firstOrderEntry = agg.result
        __ifThenElse(firstOrderEntry __!= unit[GenericEntry](null), {
          // found
          val no_o_id = firstOrderEntry.get[Int](unit(1))
          orderIDs.update(readVar(d_id) - unit(1), no_o_id)
          newOrderTbl.delete(firstOrderEntry)
          val orderEntry = orderTbl.get1((1, no_o_id), (2, readVar(d_id)), (3, w_id))
          val c_id = orderEntry.get[Int](unit(4))
          orderEntry.update(unit(6) /*o_carrier_id*/ , o_carrier_id)
          orderTbl.update(orderEntry)

          val ol_total = __newVar(unit(0.0))
          orderLineTbl.slice(unit(0), GenericEntry(unit("SteSampleSEntry"), unit(1), unit(2), unit(3), no_o_id, readVar(d_id), w_id), __lambda { orderLineEntry =>
            orderLineEntry.update(unit(7), datetime) //ol_delivery_d
            __assign(ol_total, readVar(ol_total) + orderLineEntry.get[Double](unit(9))) //ol_amount
            orderLineTbl.update(orderLineEntry)
          })

          val customerEntry = customerTbl.get1((1, c_id), (2, readVar(d_id)), (3, w_id))
          customerEntry.+=(unit(17) /*c_balance*/ , readVar(ol_total))
          customerEntry.+=(unit(20) /*c_delivery_cnt*/ , unit(1))
          customerTbl.update(customerEntry)

        }, {
          // not found
          orderIDs.update(readVar(d_id) - unit(1), unit(0))
        })
        __assign(d_id, readVar(d_id) + unit(1))
      })

      dsl"""
      if ($showOutput) {
        var output = "\n+---------------------------- DELIVERY ---------------------------+\n" +
          " Date: " + $datetime +
          "\n\n Warehouse: " + $w_id +
          "\n Carrier:   " + $o_carrier_id +
          "\n\n Delivered Orders\n"
        var skippedDeliveries = 0
        var i:Int = 1

        while (i <= 10) {
          if ($orderIDs(i -1) >= 0) {
            output = output + ("  District ") +
              (if (i < 10) " " else "") +
              (i) +
              (": Order number ") +
              ($orderIDs(i - 1)) +
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
        ()
      }
      """
      unit(1)

    }


    def stockLevelTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], threshold: Rep[Int]): Rep[Int] = {
      //          def stockLevelTx(showOutput: Boolean, datetime: Date, t_num: Int, w_id: Int, d_id: Int, threshold: Int): Int = {

      val districtEntry = districtTbl.get1((1, d_id), (2, w_id))
      val o_id = districtEntry.get[Int](unit(11))
      val i = __newVar(o_id - unit(20))
      val unique_ol_i_id = Set[Int]()
      __whileDo(readVar(i) < o_id, {
        orderLineTbl.slice(unit(0), GenericEntry(unit("SteSampleSEntry"), unit(1), unit(2), unit(3), readVar(i), d_id, w_id), __lambda { orderLineEntry =>
          val ol_i_id = orderLineEntry.get[Int](unit(5))
          val stockEntry = stockTbl.get1((1, ol_i_id), (2, w_id))
          val s_quantity = stockEntry.get[Int](unit(3))
          //                val s_quantity = unit(3)
          __ifThenElse(s_quantity < threshold, {
            unique_ol_i_id += ol_i_id
            unit()
          }, {
            unit()
          })
        })
        __assign(i, readVar(i) + unit(1))
      })
      val stock_count = unique_ol_i_id.size
      dsl"""
              if ($showOutput) {
                val output = "\n+-------------------------- STOCK-LEVEL --------------------------+" +
                  "\n Warehouse: " + $w_id +
                  "\n District:  " + $d_id +
                  "\n\n Stock Level Threshold: " + $threshold +
                  "\n Low Stock Count:       " + $stock_count +
                  "\n+-----------------------------------------------------------------+\n\n"
                println(output)
                ()
              }
            """
      unit(1)
    }
  }

  implicit object Context extends StoreDSLOptimized

  import Context.{EntryType => _, entryRepToGenericEntryOps => _, typeStore => _, typeNull => _, _}

  def main(args: Array[String]): Unit = {
    var prog: Prog = null
    import java.nio.file.Files.copy
    import java.nio.file.Paths.get
    import java.nio.file.StandardCopyOption.REPLACE_EXISTING

    val initB = reifyBlock {
      prog = new Prog(Context)
      unit((1))
    }
    val codeGen = new StoreScalaCodeGenerator(Context)
    val header =
      """
        |package tpcc.sc
        |import ddbt.lib.store._
        |import scala.collection.mutable.{ArrayBuffer,Set}
        |import java.util.Date
        |""".stripMargin
    val genDir = "../runtime/tpcc/pardisgen"
    val file = new PrintWriter(s"$genDir/TpccGenSC.scala")
    val codeBlocks: collection.mutable.ArrayBuffer[(String, List[Sym[_]], Block[Int])] = collection.mutable.ArrayBuffer()
    prog.schema.foreach(x => x._1.asInstanceOf[Sym[_]].attributes += StoreSchema(x._2))


    codeBlocks += codeGen.emitSource4[Boolean, Date, Int, Int, Int](prog.deliveryTx, "DeliveryTx")
    codeBlocks += codeGen.emitSource6[Boolean, Date, Int, Int, Int, Int, Int](prog.stockLevelTx, "StockLevelTx")
    codeBlocks += codeGen.emitSource8[Boolean, Date, Int, Int, Int, Int, Int, String, Int](prog.orderStatusTx, "OrderStatusTx")
    codeBlocks += codeGen.emitSource11[Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double, Int](prog.paymentTx, "PaymentTx")
    codeBlocks += codeGen.emitSource16[Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double], Int](prog.newOrderTx, "NewOrderTx")


    val initialTP = TransactionProgram(initB, List(prog.newOrderTbl, prog.historyTbl, prog.warehouseTbl, prog.itemTbl, prog.orderTbl, prog.districtTbl, prog.orderLineTbl, prog.customerTbl, prog.stockTbl).map(_.asInstanceOf[Sym[_]]),codeBlocks , Nil, Nil)

    implicit def toPath(filename: String) = get(filename)

    if (Optimizer.analyzeEntry) {
      copy(s"$genDir/SCTxSplEntry.txt", s"$genDir/SCTx.scala", REPLACE_EXISTING)
    } else {
      copy(s"$genDir/SCTxGenEntry.txt", s"$genDir/SCTx.scala", REPLACE_EXISTING)
    }

    val optTP = new Optimizer(Context).optimize(initialTP)
    var codestr = codeGen.blockToDocument(optTP.initBlock).toString
    var i = codestr.lastIndexOf("1")
    val storesnames = List("newOrderTbl", "historyTbl", "warehouseTbl", "itemTbl", "orderTbl", "districtTbl", "orderLineTbl", "customerTbl", "stockTbl")
    val allstores = storesnames.mkString(",")
    val executor = "class SCExecutor \n" + codestr.substring(0, i) + "\n" + storesnames.zip(optTP.global).map(t => {
      s"""  val ${t._1} = ${codeGen.expToDocument(t._2)}""".stripMargin
    }).mkString("\n") +
      s"""
         |  val newOrderTxInst = new NewOrderTx($allstores)
         |  val paymentTxInst = new PaymentTx($allstores)
         |  val orderStatusTxInst = new OrderStatusTx($allstores)
         |  val deliveryTxInst = new DeliveryTx($allstores)
         |  val stockLevelTxInst = new StockLevelTx($allstores)

      """.stripMargin
    file.println(header)
    val entries = optTP.structsDefs.map(codeGen.getStruct).mkDocument("\n")
    file.println(entries)
    file.println(executor)
    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    implicit val tp = IntType.asInstanceOf[TypeRep[Any]]
    val tempVars = optTP.tempVars.map(t => codeGen.stmtToDocument(Statement(t._1, t._2))).mkDocument("\n")
    val r =  Document.nest(2, entryIdxes :/: tempVars)
    file.println(r)
    optTP.codeBlocks.foreach { case (className, args : List[Sym[_]], body) => {
      val genCode = "  class " + className + "(" + optTP.global.map(_.asInstanceOf[Sym[_]]).map(m => m.name + m.id + s": Store[${storeType(m).name}]").mkString(", ") + ") extends ((" + args.map(s => codeGen.tpeToDocument(s.tp)).mkString(", ") + ") => " + codeGen.tpeToDocument(body.typeT) + ") {\n" +
        "    def apply(" + args.map(s => s + ": " + codeGen.tpeToDocument(s.tp)).mkString(", ") + ") = "
      val cgDoc = Document.nest(4, codeGen.blockToDocument(body))
      file.println(genCode + cgDoc + "\n  }")
    }
    }
    file.println("\n}")

    //    new TpccCompiler(Context).compile(codeBlock, "test/gen/tpcc")
    file.close()
  }

}

