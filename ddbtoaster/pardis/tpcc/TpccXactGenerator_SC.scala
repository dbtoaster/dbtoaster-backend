package sc.tpcc


import java.util.Date

import ddbt.codegen.{Optimizer, TransactionProgram}
import ddbt.lib.store.deep._
import ddbt.lib.store.{GenericEntry, Store, StringExtra, Aggregator}
import ddbt.newqq.DBToasterSquidBinding
import ddbt.transformer._

import scala.collection.mutable.{ArrayBuffer, Set}
import scala.language.implicitConversions

object TpccXactGenerator_SC {

  def main(args: Array[String]): Unit = {
    var numWare = 1
    var lang = ""
    def opts(o: String) = o match {
      case "entry" => Optimizer.analyzeEntry = true
      case "index" => Optimizer.secondaryIndex = true
      case "online" => Optimizer.onlineOpts = true
      case "m3cmpmult" => Optimizer.m3CompareMultiply = true
      case "tmpvar" => Optimizer.tmpVarHoist = true
      case "tmpmap" => Optimizer.tmpMapHoist = true
      case "idxinline" => Optimizer.indexInline = true
      case "sliceinline" => Optimizer.sliceInline = true
      case "lookupfusion" => Optimizer.indexLookupFusion = true
      case "partiallookupfusion" => Optimizer.indexLookupPartialFusion = true
      case "deadidx" => Optimizer.deadIndexUpdate = true
      case "codemotion" => Optimizer.codeMotion = true
      case "refcounter" => Optimizer.refCounter = true
      case "fixedrange" => Optimizer.fixedRange = true
      case "regex" => Optimizer.regexHoister = true
      case "multires" => Optimizer.multiResSplitter = true
      case "initsize" => Optimizer.initialStoreSize = true
      case "slicenoupd" => Optimizer.sliceNoUpd = true
      case "spl" => Optimizer.splSecondaryIdx = true
      case "minmax" => Optimizer.minMaxIdx = true
      case "med" => Optimizer.medIdx = true
      case "coldmotion" => Optimizer.coldMotion = true
      case "profileblocks" => Optimizer.profileBlocks = true
      case "profilestore" => Optimizer.profileStoreOperations = true
      case _ => throw new IllegalArgumentException(s"Unknown option $o")

    }

    def parseArgs(args: Array[String]) {
      val l = args.length
      var i = 0

      def eat(f: String => Unit, s: Boolean = false) {
        i += 1;
        if (i < l) f(if (s) args(i).toLowerCase else args(i))
      }

      while (i < l) {
        args(i) match {
          case "-opt" => eat(s => opts(s), true)
          case "-ware" => eat(s => numWare = s.toInt)
          case "-lang" => eat(s => lang = s)
          case "-info" => eat(s => Optimizer.infoFileName = s)
          case _ =>
        }
        i += 1
      }
    }

    parseArgs(args)

    import Optimizer._

    val all_opts = Map("Entry" -> analyzeEntry, "Index" -> secondaryIndex, "FixedRange" -> fixedRange, "Online" -> onlineOpts, "TmpVar" -> tmpVarHoist, "TmpMap" -> tmpMapHoist, "Inline" -> indexInline, "Fusion full" -> indexLookupFusion, "Fusion" -> indexLookupPartialFusion, "SliceInline" -> sliceInline,  "DeadIdx" -> deadIndexUpdate, "CodeMotion" -> codeMotion, "CmpMult" -> m3CompareMultiply, "RegexHoister" -> regexHoister, "RefCnt" -> refCounter, "MultiResSplitter" -> multiResSplitter, "InitialStoreSize" -> initialStoreSize, "SliceNoUpdate" -> sliceNoUpd, "Spl"->splSecondaryIdx, "MinMax"->minMaxIdx, "Med"->medIdx, "ColdMotion"->coldMotion)
    java.lang.System.err.println("Optimizations :: " + all_opts.filter(_._2).map(_._1).mkString(", "))


    var prog: Prog = null
    val Context = if (Optimizer.onlineOpts) new StoreDSLOptimized {
    } else new StoreDSL {
    }

    import Context._

    val initB = reifyBlock {
      prog = new Prog(Context, numWare)
      unit((1))
    }

    val codeGen = lang match {
      case "scala" => new TpccPardisScalaGen(Context)
      case "cpp" => Optimizer.cTransformer = true;
        new TpccPardisCppGen(Context)
    }
    val codeBlocks: collection.mutable.ArrayBuffer[(String, List[Sym[_]], Block[Int])] = collection.mutable.ArrayBuffer()
    prog.schema.foreach(x => x._1.asInstanceOf[Sym[_]].attributes += StoreSchema(x._2))
    prog.allKeys.foreach {
      case (tbl, key) => {
        val i = new IndexedCols
        i.primary = key
        i.fixedrange = prog.allRanges getOrElse(tbl, Nil)
        tbl.asInstanceOf[Sym[_]].attributes += i
      }
    }

    codeBlocks += codeGen.codeGen.emitSource4[Boolean, Date, Int, Int, Int](prog.deliveryTx, "DeliveryTx")
    codeBlocks += codeGen.codeGen.emitSource6[Boolean, Date, Int, Int, Int, Int, Int](prog.stockLevelTx, "StockLevelTx")
    codeBlocks += codeGen.codeGen.emitSource8[Boolean, Date, Int, Int, Int, Int, Int, String, Int](prog.orderStatusTx, "OrderStatusTx")
    codeBlocks += codeGen.codeGen.emitSource11[Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double, Int](prog.paymentTx, "PaymentTx")
    codeBlocks += codeGen.codeGen.emitSource16[Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double], Int](prog.newOrderTx, "NewOrderTx")


    val initialTP = TransactionProgram(initB, List(prog.newOrderTbl, prog.historyTbl, prog.warehouseTbl, prog.itemTbl, prog.orderTbl, prog.districtTbl, prog.orderLineTbl, prog.customerTbl, prog.stockTbl).map(_.asInstanceOf[Sym[_]]), codeBlocks, Nil, Nil)
    val optTP = new Optimizer(Context).optimize(initialTP)
    codeGen.generate(optTP)
  }

  class Prog(val Context: StoreDSL, val numWare: Int) extends DBToasterSquidBinding(Context) {

    import Sqd.Predef.{anyContextIsEmptyContext => _, _}
    import Sqd.Quasicodes._

    import Context.Predef._
    import Context.{__newStore, __newStoreNamed, Date, overloaded2, typeGenericEntry}
    import Context.{IntType, StringType, DoubleType, DateType, BooleanType}

    lazy val districtRange = List((1, 1, 11), (2, 1, numWare + 1))
    lazy val warehouseRange = List((1, 1, numWare + 1))
    lazy val customerRange = List((1, 1, 3001), (2, 1, 11), (3, 1, numWare + 1))
    lazy val itemRange = List((1, 1, 100001))
    lazy val stockRange = List((1, 1, 100001), (2, 1, numWare + 1))
    lazy val allRanges = List(warehouseTbl -> warehouseRange, districtTbl -> districtRange, customerTbl -> customerRange, itemTbl -> itemRange, stockTbl -> stockRange).toMap

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

    val newOrderKey = List(1, 2, 3)
    val historyKey = List(1, 2, 3, 4, 5, 6, 7, 8)
    val wareHouseKey = List(1)
    val itemKey = List(1)
    val orderKey = List(1, 2, 3)
    val districtKey = List(1, 2)
    val orderLineKey = List(1, 2, 3, 4)
    val customerKey = List(1, 2, 3)
    val stockKey = List(1, 2)

    val newOrderTbl = __newStoreNamed[GenericEntry]("newOrderTbl")
    val historyTbl = __newStoreNamed[GenericEntry]("historyTbl")
    val warehouseTbl = __newStoreNamed[GenericEntry]("warehouseTbl")
    val itemTbl = __newStoreNamed[GenericEntry]("itemTbl")
    val orderTbl = __newStoreNamed[GenericEntry]("orderTbl")
    val districtTbl = __newStoreNamed[GenericEntry]("districtTbl")
    val orderLineTbl = __newStoreNamed[GenericEntry]("orderLineTbl")
    val customerTbl = __newStoreNamed[GenericEntry]("customerTbl")
    val stockTbl = __newStoreNamed[GenericEntry]("stockTbl")

    val codeForOutput = false
    val allKeys = List(newOrderTbl -> newOrderKey, historyTbl -> historyKey, warehouseTbl -> wareHouseKey, itemTbl -> itemKey, orderTbl -> orderKey, districtTbl -> districtKey, orderLineTbl -> orderLineKey, customerTbl -> customerKey, stockTbl -> stockKey)
    val schema = List[(Rep[_], List[TypeRep[_]])](newOrderTbl -> NewOrderEntry, historyTbl -> HistoryEntry, warehouseTbl -> WarehouseEntry, itemTbl -> ItemEntry, orderTbl -> OrderEntry, districtTbl -> DistrictEntry, orderLineTbl -> OrderLineEntry, customerTbl -> CustomerEntry, stockTbl -> StockEntry)

    def newOrderTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], c_id: Rep[Int], o_ol_count: Rep[Int], o_all_local: Rep[Int], itemid: Rep[Array[Int]], supware: Rep[Array[Int]], quantity: Rep[Array[Int]], price: Rep[Array[Double]], iname: Rep[Array[String]], stock: Rep[Array[Int]], bg: Rep[Array[String]], amt: Rep[Array[Double]]): Rep[Int] = {
      if (codeForOutput) {
        ir"""
                    if($showOutput) println("Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format($w_id, $d_id, $c_id))
                  """
      }
      ir {
        var ol_number = 0
        var failed = 0
        val idata = new Array[String]($(o_ol_count))

        var all_items_exist = true

        while ((ol_number < $(o_ol_count)) && all_items_exist) {

          val itemEntry /*(i_id, _, i_name, i_price, i_data)*/ = $(itemTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, $(itemid)(ol_number)))
          if (itemEntry == null) {
            all_items_exist = false
          } else {
            $(iname).update(ol_number, itemEntry.get[String](3)) //i_name
            $(price).update(ol_number, itemEntry.get[Double](4)) //i_price
            idata.update(ol_number, itemEntry.get[String](5)) //i_data
          }
          ol_number += 1
        }

        if (all_items_exist) {
          /*(c_id,d_id,w_id, c_discount, c_last, c_credit, w_tax)*/
          val customerEntry = $(customerTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, 3, $(c_id), $(d_id), $(w_id)))
          val warehouseEntry = $(warehouseTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, $(w_id)))
          val districtEntry = $(districtTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, $(d_id), $(w_id)))
          val o_id = districtEntry.get[Int](11)
          districtEntry +=(11, 1) //d_next_o_id+1
          $(districtTbl).updateCopy(districtEntry)


          $(orderTbl).insert(GenericEntry("SteNewSEntry", o_id, $(d_id), $(w_id), $(c_id), $(datetime), -1, $(o_ol_count), $(o_all_local) > 0))
          $(newOrderTbl).insert(GenericEntry("SteNewSEntry", o_id, $(d_id), $(w_id)))



          var total = 0.0
          ol_number = 0


          while (ol_number < $(o_ol_count)) {
            val ol_supply_w_id = $(supware)(ol_number)
            val ol_i_id = $(itemid)(ol_number)
            val ol_quantity = $(quantity)(ol_number)

            //            val stockEntry = null.asInstanceOf[GenericEntry]
            //            val x = ol_i_id
            //            val y = ol_supply_w_id
            //            val stockEntry = $(ir"$stockTbl".get2[Any {val x: Int; val y: Int}]((1, ir"$$x:Int"), (2, ir"$$y : Int")))
            val stockEntry = $(stockTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id))
            //            println("""SBJ: FIXME""", ol_i_id, ol_supply_w_id)

            //            val t2 = t1.subs('x -> ol_i_id)
            //            val stockEntry = t2.subs('y -> ol_supply_w_id)
            //              $ {
            //              stockTbl.get1((1, ol_i_id), (2, ol_supply_w_id))
            //            }
            val ol_dist_info = stockEntry.get[String](3 + $(d_id))
            val s_quantity = stockEntry.get[Int](3) //s_quantity
            $(stock).update(ol_number, s_quantity)

            if (idata(ol_number).contains("original") && /*s_data*/ stockEntry.get[String](17).contains("original"))
              $(bg)(ol_number) = "B"
            else
              $(bg)(ol_number) = "G"


            stockEntry(3) = s_quantity - ol_quantity
            if (s_quantity <= ol_quantity) {
              stockEntry +=(3, 91)
              ()
            }

            var s_remote_cnt_increment = 0

            if (ol_supply_w_id != $(w_id)) s_remote_cnt_increment = 1


            //TODO this is the correct version but is not implemented in the correctness test
            //stockEntry._14 += ol_quantity //s_ytd
            //stockEntry._15 += 1 //s_order_cnt
            //stockEntry._16 += s_remote_cnt_increment //s_remote_cnt
            $(stockTbl).updateCopy(stockEntry)

            val c_discount = customerEntry.get[Double](16)
            val w_tax = warehouseEntry.get[Double](8)
            val d_tax = districtEntry.get[Double](9)
            val ol_amount = (ol_quantity * $(price)(ol_number) * (1.0 + w_tax + d_tax) * (1.0 - c_discount)) /*.asInstanceOf[Double]*/
            $(amt).update(ol_number, ol_amount)
            total += ol_amount

            $(orderLineTbl).insert(GenericEntry("SteNewSEntry", o_id, $(d_id), $(w_id), ol_number + 1 /*to start from 1*/ , ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info))

            ol_number += 1

            //             if (showOutput) println("An error occurred in handling NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(w_id, d_id, c_id))


          }

          //        dbg_ir"""
          //          $ol_number := 0
          //            val ol_supply_w_id = $supware($ol_number!)
          //            val ol_i_id = $itemid($ol_number!)
          //
          //            val x = ol_i_id
          //            val y = ol_supply_w_id
          //            val stockEntry = ${
          //          val stbl: IR[Store[GenericEntry], {}] = stockTbl
          ////          val ir1 : IR[Int, Any{val x: Int}] =
          //          stbl.get2[Any{val x: Int}]((1, ir"$$x:Int"))
          //        }
          //        ()
          //        """.toRep
        }

        1
      }.toRep
    }

    def paymentTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], c_by_name: Rep[Int], c_w_id: Rep[Int], c_d_id: Rep[Int], c_id: Rep[Int], c_last_input: Rep[String], h_amount: Rep[Double]): Rep[Int] = {
      ir {
        val warehouseEntry = $(warehouseTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, $(w_id)))
        warehouseEntry +=(9, $(h_amount)) //w_ytd
        $(warehouseTbl).updateCopy(warehouseEntry)

        val districtEntry = $(districtTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, $(d_id), $(w_id)))
        districtEntry +=(10, $(h_amount))
        $(districtTbl).updateCopy(districtEntry)

        val customerEntry = if ($(c_by_name) > 0) {
          val custagg = Aggregator.median[GenericEntry, String](e => e.get[java.lang.String](4))
          $(customerTbl).sliceCopy(0, GenericEntry("SteSampleSEntry", 2, 3, 6, $(c_d_id), $(c_w_id), $(c_last_input)), custagg)
          custagg.result
        }
        else {
          $(customerTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, 3, $(c_id), $(c_d_id), $(c_w_id)))
        }



        val c_data = customerEntry.get[String](21)

        if (customerEntry.get[String](14).contains("BC")) {
          //c_credit
          //TODO this is the correct version but is not implemented in the correctness test
          //c_data = found_c_id + " " + c_d_id + " " + c_w_id + " " + d_id + " " + w_id + " " + h_amount + " | " + c_data
          val c_new_data = StringExtra.StringPrintf(500, "%d %d %d %d %d $%f %s | %s", customerEntry.get[Int](1), $(c_d_id), $(c_w_id), $(d_id), $(w_id), $(h_amount), $(datetime), c_data)
          customerEntry +=(17 /*c_balance*/ , $(h_amount))
          //TODO this is the correct version but is not implemented in the correctness test
          //customerEntry += (18 /*c_ytd_payment*/, h_amount)
          //customerEntry += (19 /*c_payment_cnt*/, 1)
          customerEntry.update(21 /*c_data*/ , c_new_data)
          ()

        } else {
          customerEntry +=(17 /*c_balance*/ , $(h_amount))
          //TODO this is the correct version but is not implemented in the correctness test
          //customerEntry += (18 /*c_ytd_payment*/, h_amount)
          //customerEntry += (19 /*c_payment_cnt*/, 1)
          ()
        }


        $(customerTbl).updateCopy(customerEntry)
        val w_name = warehouseEntry.get[String](2)
        val d_name = districtEntry.get[String](3)
        //TODO this is the correct version but is not implemented in the correctness test
        val h_data = StringExtra.StringPrintf(24, "%.10s    %.10s", w_name, d_name)


        $(historyTbl).insert(GenericEntry("SteNewSEntry", customerEntry.get[Int](1), $(c_d_id), $(c_w_id), $(d_id), $(w_id), $(datetime), $(h_amount), h_data))
        1
      }.toRep
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
    }

    def orderStatusTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], c_by_name: Rep[Int], c_id: Rep[Int], c_last: Rep[String]): Rep[Int] = {
      ir {
        val customerEntry = if ($(c_by_name) > 0) {
          val custagg = Aggregator.median[GenericEntry, String](e => e.get[java.lang.String](4))
          $(customerTbl).sliceCopy(0, GenericEntry("SteSampleSEntry", 2, 3, 6, $(d_id), $(w_id), $(c_last)), custagg)
          custagg.result
        }
        else {
          $(customerTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, 3, $(c_id), $(d_id), $(w_id)))
        }

        val found_c_id = customerEntry.get[Int](3)
        val agg = Aggregator.max[GenericEntry, Int](e => e.get[Int](1))
        $(orderTbl).sliceCopy(0, GenericEntry("SteSampleSEntry", 2, 3, 4, $(d_id), $(w_id), found_c_id), agg)
        val newestOrderEntry = agg.result
        var dceBlocker = 0
        dceBlocker = newestOrderEntry.get[Int](1) //SBJ : TO avoid removal by DCE
        1
      }.toRep
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
    }

    def deliveryTx(showOutput: Rep[Boolean], datetime: Rep[Date], w_id: Rep[Int], o_carrier_id: Rep[Int]): Rep[Int] = {
      //        def deliveryTx(showOutput: Boolean, datetime: Date, w_id: Int, o_carrier_id: Int): Int = {
      ir {
        val DIST_PER_WAREHOUSE = 10
        val orderIDs = new Array[Int](DIST_PER_WAREHOUSE)
        var d_id = 1
        while (d_id <= DIST_PER_WAREHOUSE) {
          val agg = Aggregator.min[GenericEntry, Int](e => e.get[Int](1))
          $(newOrderTbl).sliceCopy(0 /*no_o_id*/ , GenericEntry("SteSampleSEntry", 2, 3, d_id, $(w_id)), agg)
          val firstOrderEntry = agg.result
          if (firstOrderEntry != null) {
            // found
            val no_o_id = firstOrderEntry.get[Int](1)
            orderIDs.update(d_id - 1, no_o_id)
            $(newOrderTbl).deleteCopy(firstOrderEntry)
            val orderEntry = $(orderTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, 3, no_o_id, d_id, $(w_id)))
            val c_id = orderEntry.get[Int](4)
            orderEntry.update(6 /*o_carrier_id*/ , $(o_carrier_id))
            $(orderTbl).updateCopy(orderEntry)

            var ol_total = 0.0

            $(orderLineTbl).sliceCopy(0, GenericEntry("SteSampleSEntry", 1, 2, 3, no_o_id, d_id, $(w_id)), { orderLineEntry =>
              orderLineEntry.update(7, $(datetime)) //ol_delivery_d
              ol_total = ol_total + orderLineEntry.get[Double](9) //ol_amount
              $(orderLineTbl).updateCopy(orderLineEntry) //UPDATE Inside Slice
            })

            val customerEntry = $(customerTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, 3, c_id, d_id, $(w_id)))
            customerEntry.+=(17 /*c_balance*/ , ol_total)
            customerEntry.+=(20 /*c_delivery_cnt*/ , 1)
            $(customerTbl).updateCopy(customerEntry)

          } else {
            // not found
            orderIDs.update(d_id - 1, 0)
          }
          d_id = d_id + 1
        }
        //        if ($(showOutput)) {
        //          var output = "\n+---------------------------- DELIVERY ---------------------------+\n" +
        //            " Date: " + $(datetime) +
        //            "\n\n Warehouse: " + $(w_id) +
        //            "\n Carrier:   " + $(o_carrier_id) +
        //            "\n\n Delivered Orders\n"
        //          var skippedDeliveries = 0
        //          var i: Int = 1
        //
        //          while (i <= 10) {
        //            if (orderIDs(i - 1) >= 0) {
        //              output = output + ("  District ") +
        //                (if (i < 10) " " else "") +
        //                (i) +
        //                (": Order number ") +
        //                (orderIDs(i - 1)) +
        //                (" was delivered.\n")
        //            }
        //            else {
        //              output = output + ("  District ") +
        //                (if (i < 10) " " else "") +
        //                (i) +
        //                (": No orders to be delivered.\n")
        //              skippedDeliveries += 1
        //            }
        //            i += 1
        //          }
        //          output = output + ("+-----------------------------------------------------------------+\n\n")
        //          println(output)
        //          ()
        //        }
        1
      }.toRep
    }

    def stockLevelTx(showOutput: Rep[Boolean], datetime: Rep[Date], t_num: Rep[Int], w_id: Rep[Int], d_id: Rep[Int], threshold: Rep[Int]): Rep[Int] = {
      //          def stockLevelTx(showOutput: Boolean, datetime: Date, t_num: Int, w_id: Int, d_id: Int, threshold: Int): Int = {
      ir {
        val districtEntry = $(districtTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, $(d_id), $(w_id)))
        val o_id = districtEntry.get[Int](11)
        var i = o_id - 20
        val unique_ol_i_id = Set[Int]()
        while (i < o_id) {
          $(orderLineTbl).sliceCopy(0, GenericEntry("SteSampleSEntry", 1, 2, 3, i, $(d_id), $(w_id)), { orderLineEntry =>
            val ol_i_id = orderLineEntry.get[Int](5)
            val stockEntry = $(stockTbl).getCopy(0, GenericEntry("SteSampleSEntry", 1, 2, ol_i_id, $(w_id)))
            val s_quantity = stockEntry.get[Int](3)
            //                val s_quantity = unit(3)
            if (s_quantity < $(threshold)) {
              unique_ol_i_id += ol_i_id
            }
          })
          i += 1
        }
        val stock_count = unique_ol_i_id.size
        //        if ($(showOutput)) {
        //          val output = "\n+-------------------------- STOCK-LEVEL --------------------------+" +
        //            "\n Warehouse: " + $(w_id) +
        //            "\n District:  " + $(d_id) +
        //            "\n\n Stock Level Threshold: " + $(threshold) +
        //            "\n Low Stock Count:       " + stock_count +
        //            "\n+-----------------------------------------------------------------+\n\n"
        //          println(output)
        //        }
        1
      }.toRep
    }

    //    implicit class StoreRep2[E <: ddbt.lib.store.Entry, C](self: IR[Store[E], C])(implicit typeE: IRType[E]) {
    //      def get2[D](args: (Int, IR[Int, D])*): IR[E, D] = {
    //        val arg2 = args.map(x => (x._1, x._2.toRep))
    //        implicit val typerep = typeE.rep.asInstanceOf[TypeRep[E]]
    //        Sqd.`internal IR`[E, D](stGet(self.toRep, args.map(_._1), stSampleEntry(self.toRep, arg2)))
    //      }
    //    }

  }

}
