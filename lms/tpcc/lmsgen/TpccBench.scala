import storage._
import DummyPrint._
package tpcc.lmsgen {

/* Function: newOrderTx */
/**
 * ***************************************
 * Emitting Generated Code
 * *****************************************
 */
class newOrderTx(x0: storage.Store[SEntry3_III], x1: storage.Store[SEntry8_IIIIIAFS], x2: storage.Store[SEntry9_ISSSSSSFD], x3: storage.Store[SEntry5_IISFS], x4: storage.Store[SEntry8_IIIIAIIB], x5: storage.Store[SEntry11_IISSSSSSFDI], x6: storage.Store[SEntry10_IIIIIIAIFS], x7: storage.Store[SEntry21_IIISSSSSSSSSASFFFFIIS], x8: storage.Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, java.util.Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Float], Array[java.lang.String], Array[Int], Array[Char], Array[Float]) => (Int)) {
  def apply(x9: Boolean, x10: java.util.Date, x11: Int, x12: Int, x13: Int, x14: Int, x15: Int, x16: Int, x17: Array[Int], x18: Array[Int], x19: Array[Int], x20: Array[Float], x21: Array[java.lang.String], x22: Array[Int], x23: Array[Char], x24: Array[Float]): Int = {
    if (x9) {
      println(("- Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x12, x13, x14)))
      ()
    } else {
      ()
    }
    val x29 = x0 /*store made mutable*/
    val x31 = x2 /*store made mutable*/
    val x32 = x3 /*store made mutable*/
    val x33 = x4 /*store made mutable*/
    val x34 = x5 /*store made mutable*/
    val x35 = x6 /*store made mutable*/
    val x36 = x7 /*store made mutable*/
    val x37 = x8 /*store made mutable*/
    val x38 = x20 //array made mutable
    val x39 = x21 //array made mutable
    val x40 = x22 //array made mutable
    val x41 = x23 //array made mutable
    val x42 = x24 //array made mutable
    var x43: Int = 0
    val x45 = new Array[java.lang.String](x15)
    var x46: Boolean = true
    val x47 = 0 < x15
    if ((if (x47) {

      (x46)
    } else false)) {
      do {
        val x52 = x43
        val x56 = (x32.idxs(0).get(({ se54._1 = (x17(x52)); se54 }))) /*made mutable*/
        if ((x56 == null)) {
          x46 = false
          ()
        } else {
          x39(x52) = (x56._3)
          x38(x52) = (x56._4)
          x45(x52) = (x56._5)
          ()
        }
        x43 += 1
        ()
      } while ({
        (if (((x43) < x15)) {

          (x46)
        } else false)
      })
      ()
    } else {
      ()
    }
    val x449 = if ((!(x46))) {
      1
    } else {
      val x86 = (x36.idxs(0).get(({ se84._1 = x14; se84._2 = x13; se84._3 = x12; se84 }))) /*made mutable*/
      val x89 = (x31.idxs(0).get(({ se87._1 = x12; se87 }))) /*made mutable*/
      val x92 = (x34.idxs(0).get(({ se90._1 = x13; se90._2 = x12; se90 }))) /*made mutable*/
      val x103 = x92._11
      x92._11 += 1
      x34.update(x92)
      val x107 = SEntry8_IIIIAIIB(x103, x13, x12, x14, x10, -1, x15, (x16 > 0))
      x33.insert(x107)
      val x109 = SEntry3_III(x103, x13, x12)
      x29.insert(x109)
      var x111: Float = 0.0000000000f
      x43 = 0
      if (x47) {
        val x120 = x13 == 1
        val x139 = x13 == 2
        val x158 = x13 == 3
        val x177 = x13 == 4
        val x196 = x13 == 5
        val x215 = x13 == 6
        val x234 = x13 == 7
        val x253 = x13 == 8
        val x272 = x13 == 9
        do {
          val x113 = x43
          val x114 = x18(x113)
          val x115 = x17(x113)
          val x119 = (x37.idxs(0).get(({ se117._1 = x115; se117._2 = x114; se117 }))) /*made mutable*/
          val x328 = x119._3
          x40(x113) = x328
          if ((if (((x86._14).contains("original"))) {

            ((x119._17).contains("original"))
          } else false)) {
            x41(x113) = 'B'
            ()
          } else {
            x41(x113) = 'G'
            ()
          }
          val x116 = x19(x113)
          x119._3 = (x328 - x116)
          if ((x328 <= x116)) {
            x119._3 += 91
            ()
          } else {
            ()
          }
          var x398: Int = 0
          if ((x114 != x12)) {
            x398 = 1
            ()
          } else {
            ()
          }
          x37.update(x119)
          val x430 = ((x116 * (x38(x113))) * ((1.0000000000f + (x89._8)) + (x92._9))) * (1.0000000000f - (x86._16))
          x42(x113) = x430
          x111 += x430
          val x434 = SEntry10_IIIIIIAIFS(x103, x13, x12, (x113 + 1), x115, x114, null, x116, x430, (if (x120) {
            (x119._4)
          } else {
            (if (x139) {
              (x119._5)
            } else {
              (if (x158) {
                (x119._6)
              } else {
                (if (x177) {
                  (x119._7)
                } else {
                  (if (x196) {
                    (x119._8)
                  } else {
                    (if (x215) {
                      (x119._9)
                    } else {
                      (if (x234) {
                        (x119._10)
                      } else {
                        (if (x253) {
                          (x119._11)
                        } else {
                          (if (x272) {
                            (x119._12)
                          } else {
                            (x119._13)
                          })
                        })
                      })
                    })
                  })
                })
              })
            })
          }))
          x35.insert(x434)
          x43 += 1
          ()
        } while ({
          ((x43) < x15)
        })
        ()
      } else {
        ()
      }
      if (x9) {
        println(("An error occurred in handling NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x12, x13, x14)))
        ()
      } else {
        ()
      }
      1
    }
    x449
  }
  val se117 = new SEntry17_IIISSSSSSSSSSIIIS
  val se54 = new SEntry5_IISFS
  val se87 = new SEntry9_ISSSSSSFD
  val se90 = new SEntry11_IISSSSSSFDI
  val se84 = new SEntry21_IIISSSSSSSSSASFFFFIIS
}
/**
 * ***************************************
 * End of Generated Code
 * *****************************************
 */


/* Function: paymentTx */
/**
 * ***************************************
 * Emitting Generated Code
 * *****************************************
 */
class paymentTx(x0: storage.Store[SEntry3_III], x1: storage.Store[SEntry8_IIIIIAFS], x2: storage.Store[SEntry9_ISSSSSSFD], x3: storage.Store[SEntry5_IISFS], x4: storage.Store[SEntry8_IIIIAIIB], x5: storage.Store[SEntry11_IISSSSSSFDI], x6: storage.Store[SEntry10_IIIIIIAIFS], x7: storage.Store[SEntry21_IIISSSSSSSSSASFFFFIIS], x8: storage.Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, java.util.Date, Int, Int, Int, Int, Int, Int, Int, java.lang.String, Float) => (Int)) {
  def apply(x451: Boolean, x452: java.util.Date, x453: Int, x454: Int, x455: Int, x456: Int, x457: Int, x458: Int, x459: Int, x460: java.lang.String, x461: Float): Int = {
    val x463 = x1 /*store made mutable*/
    val x464 = x2 /*store made mutable*/
    val x467 = x5 /*store made mutable*/
    val x469 = x7 /*store made mutable*/
    val x473 = (x464.idxs(0).get(({ se471._1 = x454; se471 }))) /*made mutable*/
    x473._9 += x461
    x464.update(x473)
    val x478 = (x467.idxs(0).get(({ se476._1 = x455; se476._2 = x454; se476 }))) /*made mutable*/
    x478._10 += x461
    x467.update(x478)
    var x481: SEntry21_IIISSSSSSSSSASFFFFIIS = null
    if ((x456 > 0)) {
      val x483 = scala.collection.mutable.ArrayBuffer[SEntry21_IIISSSSSSSSSASFFFFIIS]()
      x469.idxs(1).slice(({ se484._2 = x458; se484._3 = x457; se484._6 = x460; se484 }), {
        x485 =>
          x483 += x485
      })
      val x489 = x483.size
      var x491: Int = (x489 >> 1)
      if (((x489 & 1) == 0)) {
        x491 -= 1
        ()
      } else {
        ()
      }
      x481 = (x483((x491)))
      ()
    } else {
      val x503 = (x469.idxs(0).get(({ se501._1 = x459; se501._2 = x458; se501._3 = x457; se501 }))) /*made mutable*/
      x481 = x503
      ()
    }
    val x507 = x481
    val x528 = x507._21
    var x529: java.lang.String = x528
    val x521 = x507._14
    val x508 = x507._1
    if ((x521.contains("BC"))) {
      val x531 = "%d %d %d %d %d $%f %s | %s".format(x508, x458, x457, x455, x454, x461, x452, x528)
      x529 = x531
      if (((x531.length) > 500)) {
        x529 = (x531.substring(0, 500))
        ()
      } else {
        ()
      }
      x507._17 += x461
      x507._21 = (x529)
      ()
    } else {
      x507._17 += x461
      ()
    }
    x469.update(x507)
    val x548 = x473._2
    val x549 = x473._3
    val x550 = x473._4
    val x551 = x473._5
    val x552 = x473._6
    val x553 = x473._7
    val x558 = x478._3
    val x559 = x478._4
    val x560 = x478._5
    val x561 = x478._6
    val x562 = x478._7
    val x563 = x478._8
    val x579 = SEntry8_IIIIIAFS(x508, x458, x457, x455, x454, x452, x461, (((if (((x548.length) > 10)) {
      (x548.substring(0, 10))
    } else {
      x548
    }) + "    ") + (if (((x558.length) > 10)) {
      (x558.substring(0, 10))
    } else {
      x558
    })))
    x463.insert(x579)
    if (x451) {
      val x520 = x507._13
      val x642 = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((("\n+---------------------------- PAYMENT ----------------------------+\n Date: %s" + x452) + "\n\n Warehouse: ") + x454) + "\n   Street:  ") + x549) + "\n   Street:  ") + x550) + "\n   City:    ") + x551) + "   State: ") + x552) + "  Zip: ") + x553) + "\n\n District:  ") + x455) + "\n   Street:  ") + x559) + "\n   Street:  ") + x560) + "\n   City:    ") + x561) + "   State: ") + x562) + "  Zip: ") + x563) + "\n\n Customer:  ") + x508) + "\n   Name:    ") + (x507._4)) + " ") + (x507._5)) + " ") + (x507._6)) + "\n   Street:  ") + (x507._7)) + "\n   Street:  ") + (x507._8)) + "\n   City:    ") + (x507._9)) + "   State: ") + (x507._10)) + "  Zip: ") + (x507._11)) + "\n   Since:   ") + (if ((x520 != null)) {
        x520
      } else {
        ""
      })) + "\n   Credit:  ") + x521) + "\n   Disc:    ") + ((x507._16) * (100))) + "%") + "\n   Phone:   ") + (x507._12)) + "\n\n Amount Paid:      ") + x461) + "\n Credit Limit:     ") + (x507._15)) + "\n New Cust-Balance: ") + (x507._17)
      var x643: java.lang.String = x642
      if ((x521 == "BC")) {
        val x645 = x529
        val x646 = x645.length
        if ((x646 > 50)) {
          x643 = ((x642 + "\n\n Cust-Data: ") + (x645.substring(0, 50)))
          var x655: Int = 1
          val x654 = if ((x646 > 200)) {
            4
          } else {
            val x653 = x646 / 50
            x653
          }
          if ((1 < x654)) {
            do {
              val x659 = x655
              x643 = (((x643) + "\n            ") + (x645.substring((x659 * 50), ((x659 + 1) * 50))))
              x655 += 1
              ()
            } while ({
              ((x655) < x654)
            })
            ()
          } else {
            ()
          }
          ()
        } else {
          x643 = ((x642 + "\n\n Cust-Data: ") + x645)
          ()
        }
        ()
      } else {
        ()
      }
      val x683 = (x643) + "\n+-----------------------------------------------------------------+\n\n"
      x643 = x683
      println(x683)
      ()
    } else {
      ()
    }
    1
  }
  val se476 = new SEntry11_IISSSSSSFDI
  val se501 = new SEntry21_IIISSSSSSSSSASFFFFIIS
  val se484 = new SEntry21_IIISSSSSSSSSASFFFFIIS
  val se471 = new SEntry9_ISSSSSSFD
}
/**
 * ***************************************
 * End of Generated Code
 * *****************************************
 */


/* Function: orderStatusTx */
/**
 * ***************************************
 * Emitting Generated Code
 * *****************************************
 */
class orderStatusTx(x0: storage.Store[SEntry3_III], x1: storage.Store[SEntry8_IIIIIAFS], x2: storage.Store[SEntry9_ISSSSSSFD], x3: storage.Store[SEntry5_IISFS], x4: storage.Store[SEntry8_IIIIAIIB], x5: storage.Store[SEntry11_IISSSSSSFDI], x6: storage.Store[SEntry10_IIIIIIAIFS], x7: storage.Store[SEntry21_IIISSSSSSSSSASFFFFIIS], x8: storage.Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, java.util.Date, Int, Int, Int, Int, Int, java.lang.String) => (Int)) {
  def apply(x689: Boolean, x690: java.util.Date, x691: Int, x692: Int, x693: Int, x694: Int, x695: Int, x696: java.lang.String): Int = {
    val x701 = x4 /*store made mutable*/
    val x703 = x6 /*store made mutable*/
    val x704 = x7 /*store made mutable*/
    var x706: SEntry21_IIISSSSSSSSSASFFFFIIS = null
    if ((x694 > 0)) {
      val x708 = scala.collection.mutable.ArrayBuffer[SEntry21_IIISSSSSSSSSASFFFFIIS]()
      x704.idxs(1).slice(({ se709._2 = x693; se709._3 = x692; se709._6 = x696; se709 }), {
        x710 =>
          x708 += x710
      })
      val x714 = x708.size
      var x716: Int = (x714 >> 1)
      if (((x714 & 1) == 0)) {
        x716 -= 1
        ()
      } else {
        ()
      }
      x706 = (x708((x716)))
      ()
    } else {
      val x728 = (x704.idxs(0).get(({ se726._1 = x695; se726._2 = x693; se726._3 = x692; se726 }))) /*made mutable*/
      x706 = x728
      ()
    }
    val x732 = x706
    val x735 = x732._3
    val x756 = (x701.idxs(1).get(({ se754._2 = x693; se754._3 = x692; se754._4 = x735; se754 })) /* max */ ) /*made mutable*/
    var x757: Int = 0
    if ((!x689)) {
      if ((x756 != null)) {
        x703.idxs(0).slice(({ se768._1 = (x756._1); se768._2 = x693; se768._3 = x692; se768 }), {
          x769 =>
            x757 = 1
        })
        ()
      } else {
        ()
      }
      ()
    } else {
      val x776 = scala.collection.mutable.ArrayBuffer[java.lang.String]()
      if ((x756 != null)) {
        x703.idxs(0).slice(({ se786._1 = (x756._1); se786._2 = x693; se786._3 = x692; se786 }), {
          x787 =>
            val x794 = x787._7
            x776 += ("[%d - %d - %d - %f - %s]".format((x787._6), (x787._5), (x787._8), (x787._9), (if ((x794 == null)) {
              "99-99-9999"
            } else {
              val x800 = sdf799.format(x794)
              x800
            })))
        })
        ()
      } else {
        ()
      }
      val x824 = x756._1
      val x828 = x756._5
      val x829 = x756._6
      println((((((((((((((((((("\n+-------------------------- ORDER-STATUS -------------------------+\n Date: " + x690) + "\n\n Warehouse: ") + x692) + "\n District:  ") + x693) + "\n\n Customer:  ") + x735) + "\n   Name:    ") + (x732._4)) + " ") + (x732._5)) + " ") + (x732._6)) + "\n   Balance: ") + (x732._17)) + "\n\n") + (if ((x824 == -1)) {
        " Customer has no orders placed.\n"
      } else {
        val x839 = x776.size
        (((((((" Order-Number: " + x824) + "\n    Entry-Date: ") + x828) + "\n    Carrier-Number: ") + x829) + "\n\n") + (if ((x839 != 0)) {
          var x841: java.lang.String = " [Supply_W - Item_ID - Qty - Amount - Delivery-Date]\n"
          var x842: Int = 0
          val x839 = x776.size
          if ((0 < x839)) {
            do {
              x841 = ((((x841) + " ") + (x776((x842)))) + "\n")
              x842 += 1
              ()
            } while ({
              ((x842) < (x776.size))
            })
            ()
          } else {
            ()
          }
          (x841)
        } else {
          " This Order has no Order-Lines.\n"
        }))
      })) + "+-----------------------------------------------------------------+\n\n"))
      ()
    }
    1
  }
  val se754 = new SEntry8_IIIIAIIB
  val sdf799 = new java.text.SimpleDateFormat("yyyy-MM-dd")
  val se709 = new SEntry21_IIISSSSSSSSSASFFFFIIS
  val se786 = new SEntry10_IIIIIIAIFS
  val se768 = new SEntry10_IIIIIIAIFS
  val se726 = new SEntry21_IIISSSSSSSSSASFFFFIIS
}
/**
 * ***************************************
 * End of Generated Code
 * *****************************************
 */


/* Function: deliveryTx */
/**
 * ***************************************
 * Emitting Generated Code
 * *****************************************
 */
class deliveryTx(x0: storage.Store[SEntry3_III], x1: storage.Store[SEntry8_IIIIIAFS], x2: storage.Store[SEntry9_ISSSSSSFD], x3: storage.Store[SEntry5_IISFS], x4: storage.Store[SEntry8_IIIIAIIB], x5: storage.Store[SEntry11_IISSSSSSFDI], x6: storage.Store[SEntry10_IIIIIIAIFS], x7: storage.Store[SEntry21_IIISSSSSSSSSASFFFFIIS], x8: storage.Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, java.util.Date, Int, Int) => (Int)) {
  def apply(x872: Boolean, x873: java.util.Date, x874: Int, x875: Int): Int = {
    val x876 = x0 /*store made mutable*/
    val x880 = x4 /*store made mutable*/
    val x882 = x6 /*store made mutable*/
    val x883 = x7 /*store made mutable*/
    val x885 = new Array[Int](10)
    var x886: Int = 1
    val x887 = 1 <= 10
    if (x887) {
      do {
        val x888 = x886
        val x891 = (x876.idxs(1).get(({ se889._2 = x888; se889._3 = x874; se889 })) /* min */ ) /*made mutable*/
        if ((x891 != null)) {
          val x893 = x891._1
          val x896 = x888 - 1
          x885(x896) = x893
          x876.delete(x891)
          val x901 = (x880.idxs(2).get(({ se899._1 = x893; se899._2 = x888; se899._3 = x874; se899 }))) /*made mutable*/
          x901._6 = x875
          x880.update(x901)
          var x912: Float = 0.0000000000f
          x882.idxs(0).slice(({ se913._1 = x893; se913._2 = x888; se913._3 = x874; se913 }), {
            x914 =>
              x914._7 = x873
              x912 += (x914._9)
              x882.update(x914)
          })
          val x932 = (x883.idxs(0).get(({ se930._1 = (x901._4); se930._2 = x888; se930._3 = x874; se930 }))) /*made mutable*/
          x932._17 += (x912)
          x932._20 += 1
          x883.update(x932)
          ()
        } else {
          val x896 = x888 - 1
          x885(x896) = 0
          ()
        }
        x886 += 1
        ()
      } while ({
        ((x886) <= 10)
      })
      ()
    } else {
      ()
    }
    if (x872) {
      var x955: java.lang.String = (((((("\n+---------------------------- DELIVERY ---------------------------+\n Date: " + x873) + "\n\n Warehouse: ") + x874) + "\n Carrier:   ") + x875) + "\n\n Delivered Orders\n")
      var x956: Int = 0
      var x957: Int = 1
      if (x887) {
        do {
          val x958 = x957
          val x960 = x885((x958 - 1))
          if ((x960 >= 0)) {
            val x964 = x958 < 10
            val x965 = if (x964) {
              " "
            } else {
              ""
            }
            x955 = (((((((x955) + "  District ") + x965) + x958) + ": Order number ") + x960) + " was delivered.\n")
            ()
          } else {
            val x964 = x958 < 10
            val x965 = if (x964) {
              " "
            } else {
              ""
            }
            x955 = (((((x955) + "  District ") + x965) + x958) + ": No orders to be delivered.\n")
            x956 += 1
            ()
          }
          x957 += 1
          ()
        } while ({
          ((x957) <= 10)
        })
        ()
      } else {
        ()
      }
      val x991 = (x955) + "+-----------------------------------------------------------------+\n\n"
      x955 = x991
      println(x991)
      ()
    } else {
      ()
    }
    1
  }
  val se899 = new SEntry8_IIIIAIIB
  val se889 = new SEntry3_III
  val se913 = new SEntry10_IIIIIIAIFS
  val se930 = new SEntry21_IIISSSSSSSSSASFFFFIIS
}
/**
 * ***************************************
 * End of Generated Code
 * *****************************************
 */


/* Function: stockLevelTx */
/**
 * ***************************************
 * Emitting Generated Code
 * *****************************************
 */
class stockLevelTx(x0: storage.Store[SEntry3_III], x1: storage.Store[SEntry8_IIIIIAFS], x2: storage.Store[SEntry9_ISSSSSSFD], x3: storage.Store[SEntry5_IISFS], x4: storage.Store[SEntry8_IIIIAIIB], x5: storage.Store[SEntry11_IISSSSSSFDI], x6: storage.Store[SEntry10_IIIIIIAIFS], x7: storage.Store[SEntry21_IIISSSSSSSSSASFFFFIIS], x8: storage.Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, java.util.Date, Int, Int, Int, Int) => (Int)) {
  def apply(x997: Boolean, x998: java.util.Date, x999: Int, x1000: Int, x1001: Int, x1002: Int): Int = {
    val x1008 = x5 /*store made mutable*/
    val x1009 = x6 /*store made mutable*/
    val x1011 = x8 /*store made mutable*/
    val x1014 = (x1008.idxs(0).get(({ se1012._1 = x1001; se1012._2 = x1000; se1012 }))) /*made mutable*/
    val x1025 = x1014._11
    val x1026 = x1025 - 20
    var x1027: Int = x1026
    val x1028 = collection.mutable.HashSet[Int]()
    if ((x1026 < x1025)) {
      do {
        x1009.idxs(0).slice(({ se1031._1 = (x1027); se1031._2 = x1001; se1031._3 = x1000; se1031 }), {
          x1032 =>
            val x1037 = x1032._5
            val x1045 = (x1011.idxs(0).get(({ se1043._1 = x1037; se1043._2 = x1000; se1043 }))) /*made mutable*/
            if (((x1045._3) < x1002)) {
              x1028.add(x1037)
              ()
            } else {
              ()
            }
        })
        x1027 += 1
        ()
      } while ({
        ((x1027) < x1025)
      })
      ()
    } else {
      ()
    }
    val x1077 = x1028.size
    if (x997) {
      println((((((((("\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: " + x1000) + "\n District:  ") + x1001) + "\n\n Stock Level Threshold: ") + x1002) + "\n Low Stock Count:       ") + x1077) + "\n+-----------------------------------------------------------------+\n\n"))
      ()
    } else {
      ()
    }
    1
  }
  val se1031 = new SEntry10_IIIIIIAIFS
  val se1012 = new SEntry11_IISSSSSSFDI
  val se1043 = new SEntry17_IIISSSSSSSSSSIIIS
}
/**
 * ***************************************
 * End of Generated Code
 * *****************************************
 */

  case class SEntry11_IISSSSSSFDI(var _1:Int = 0, var _2:Int = 0, var _3:java.lang.String = null, var _4:java.lang.String = null, var _5:java.lang.String = null, var _6:java.lang.String = null, var _7:java.lang.String = null, var _8:java.lang.String = null, var _9:Float = 0f, var _10:Double = 0D, var _11:Int = 0) extends storage.Entry(11) {
    def hash(i: Int):Int = {
      //println("hash is district => " + ((_2-1) * ddbt.tpcc.loadtest.TpccConstants.DIST_PER_WARE + (_1-1)))
      (_2-1) * ddbt.tpcc.loadtest.TpccConstants.DIST_PER_WARE + (_1-1)
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry11_IISSSSSSFDI]
      if(_1 == e._1 && _2 == e._2) 0 else 1
    }
    def copy = SEntry11_IISSSSSSFDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)
  }
  case class SEntry8_IIIIIAFS(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0, var _4:Int = 0, var _5:Int = 0, var _6:java.util.Date = null, var _7:Float = 0f, var _8:java.lang.String = null) extends storage.Entry(8) {
    def hash(i: Int):Int = {
      var hash:Int = 0xcafebabe
      if(i == 0) {
        var mix:Int = _1 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _2 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _3 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _4 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _5 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _6.## * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _7.## * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _8.## * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 8
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      }
      hash
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry8_IIIIIAFS]
      if(i == 0) {
        if(_1 == e._1 && _2 == e._2 && _3 == e._3 && _4 == e._4 && _5 == e._5 && _6 == e._6 && _7 == e._7 && _8 == e._8) 0 else 1
      } else { 0 }
    }
    def copy = SEntry8_IIIIIAFS(_1, _2, _3, _4, _5, _6, _7, _8)
  }
  case class SEntry8_IIIIAIIB(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0, var _4:Int = 0, var _5:java.util.Date = null, var _6:Int = 0, var _7:Int = 0, var _8:Boolean = false) extends storage.Entry(8) {
    def hash(i: Int):Int = {
      var hash:Int = 0xcafebabe
      if(i == 0) {
        var mix:Int = _2 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _3 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _4 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 3
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      } else if(i == 1) {
        var mix:Int = _1 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 1
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      } else if(i == 2) {
        var mix:Int = _1 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _2 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _3 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 3
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      }
      hash
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry8_IIIIAIIB]
      if(i == 0) {
        if(_2 == e._2 && _3 == e._3 && _4 == e._4) 0 else 1
      } else if(i == 1) {
        if(_1 < e._1) { 1 } else if(_1 > e._1) { -1 } else { 0 }
      } else if(i == 2) {
        if(_1 == e._1 && _2 == e._2 && _3 == e._3) 0 else 1
      } else { 0 }
    }
    def copy = SEntry8_IIIIAIIB(_1, _2, _3, _4, _5, _6, _7, _8)
  }
  case class SEntry17_IIISSSSSSSSSSIIIS(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0, var _4:java.lang.String = null, var _5:java.lang.String = null, var _6:java.lang.String = null, var _7:java.lang.String = null, var _8:java.lang.String = null, var _9:java.lang.String = null, var _10:java.lang.String = null, var _11:java.lang.String = null, var _12:java.lang.String = null, var _13:java.lang.String = null, var _14:Int = 0, var _15:Int = 0, var _16:Int = 0, var _17:java.lang.String = null) extends storage.Entry(17) {
    def hash(i: Int):Int = {
      //println("hash is stock => " + ((_2-1) * ddbt.tpcc.loadtest.TpccConstants.MAXITEMS + (_1-1)))
      (_2-1) * ddbt.tpcc.loadtest.TpccConstants.MAXITEMS + (_1-1)
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry17_IIISSSSSSSSSSIIIS]
      if(_1 == e._1 && _2 == e._2) 0 else 1
    }
    def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17)
  }
  case class SEntry21_IIISSSSSSSSSASFFFFIIS(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0, var _4:java.lang.String = null, var _5:java.lang.String = null, var _6:java.lang.String = null, var _7:java.lang.String = null, var _8:java.lang.String = null, var _9:java.lang.String = null, var _10:java.lang.String = null, var _11:java.lang.String = null, var _12:java.lang.String = null, var _13:java.util.Date = null, var _14:java.lang.String = null, var _15:Float = 0f, var _16:Float = 0f, var _17:Float = 0f, var _18:Float = 0f, var _19:Int = 0, var _20:Int = 0, var _21:java.lang.String = null) extends storage.Entry(21) {
    def hash(i: Int):Int = {
      var hash:Int = 0xcafebabe
      if(i == 0) {
        ////println("hash is customer => " + (((_3-1) * ddbt.tpcc.loadtest.TpccConstants.DIST_PER_WARE + (_2-1)) * ddbt.tpcc.loadtest.TpccConstants.CUST_PER_DIST + (_1-1)))
        hash = ((_3-1) * ddbt.tpcc.loadtest.TpccConstants.DIST_PER_WARE + (_2-1)) * ddbt.tpcc.loadtest.TpccConstants.CUST_PER_DIST + (_1-1)
      } else if(i == 1) {
        var mix:Int = _2 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _3 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _6.## * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 3
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      }
      hash
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry21_IIISSSSSSSSSASFFFFIIS]
      if(i == 0) {
        if(_1 == e._1 && _2 == e._2 && _3 == e._3) 0 else 1
      } else if(i == 1) {
        if(_2 == e._2 && _3 == e._3 && _6 == e._6) 0 else 1
      } else { 0 }
    }
    def copy = SEntry21_IIISSSSSSSSSASFFFFIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21)
  }
  case class SEntry10_IIIIIIAIFS(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0, var _4:Int = 0, var _5:Int = 0, var _6:Int = 0, var _7:java.util.Date = null, var _8:Int = 0, var _9:Float = 0f, var _10:java.lang.String = null) extends storage.Entry(10) {
    def hash(i: Int):Int = {
      var hash:Int = 0xcafebabe
      if(i == 0) {
        var mix:Int = _1 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _2 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _3 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 3
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      }
      hash
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry10_IIIIIIAIFS]
      if(i == 0) {
        if(_1 == e._1 && _2 == e._2 && _3 == e._3) 0 else 1
      } else { 0 }
    }
    def copy = SEntry10_IIIIIIAIFS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10)
  }
  case class SEntry3_III(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0) extends storage.Entry(3) {
    def hash(i: Int):Int = {
      var hash:Int = 0xcafebabe
      if(i == 0) {
        var mix:Int = _2 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        mix = _3 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 2
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      } else if(i == 1) {
        var mix:Int = _1 * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = (mix << 1) + mix + 0xe6546b64
        hash ^= 1
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      }
      hash
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry3_III]
      if(i == 0) {
        if(_2 == e._2 && _3 == e._3) 0 else 1
      } else if(i == 1) {
        if(_1 < e._1) { -1 } else if(_1 > e._1) { 1 } else { 0 }
      } else { 0 }
    }
    def copy = SEntry3_III(_1, _2, _3)
  }
  case class SEntry5_IISFS(var _1:Int = 0, var _2:Int = 0, var _3:java.lang.String = null, var _4:Float = 0f, var _5:java.lang.String = null) extends storage.Entry(5) {
    def hash(i: Int):Int = {
      //println("hash is item => " + _1)
      _1
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry5_IISFS]
      if(_1 == e._1) 0 else 1
    }
    def copy = SEntry5_IISFS(_1, _2, _3, _4, _5)
  }
  case class SEntry9_ISSSSSSFD(var _1:Int = 0, var _2:java.lang.String = null, var _3:java.lang.String = null, var _4:java.lang.String = null, var _5:java.lang.String = null, var _6:java.lang.String = null, var _7:java.lang.String = null, var _8:Float = 0f, var _9:Double = 0D) extends storage.Entry(9) {
    def hash(i: Int):Int = {
      //println("hash is warehouse => " + _1)
      _1
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry9_ISSSSSSFD]
      if(_1 == e._1) 0 else 1
    }
    def copy = SEntry9_ISSSSSSFD(_1, _2, _3, _4, _5, _6, _7, _8, _9)
  }
  class EfficientExecutor {
    val x0 = new storage.Store[SEntry3_III](2)
    x0.index(0,INone,false)
    x0.index(1,ISliceMin,false,0)
    
    val x1 = new storage.Store[SEntry8_IIIIIAFS](1)
    x1.index(0,IList,false)

    val x2 = new storage.Store[SEntry9_ISSSSSSFD](1)
    x2.index(0,IHash,true)

    val x3 = new storage.Store[SEntry5_IISFS](1)
    x3.index(0,IHash,true)

    val x4 = new storage.Store[SEntry8_IIIIAIIB](3)
    x4.index(0,INone,false)
    x4.index(1,ISliceMax,false,0)
    x4.index(2,IHash,true)

    val x5 = new storage.Store[SEntry11_IISSSSSSFDI](1)
    x5.index(0,IHash,true)

    val x6 = new storage.Store[SEntry10_IIIIIIAIFS](1)
    x6.index(0,IHash,false)

    val x7 = new storage.Store[SEntry21_IIISSSSSSSSSASFFFFIIS](2)
    x7.index(0,IHash,true)
    x7.index(1,IHash,false)

    val x8 = new storage.Store[SEntry17_IIISSSSSSSSSSIIIS](1)
    x8.index(0,IHash,true)

    def gotoOperationalStage = {
      x2.index(0,IDirect,true) //warehouse
      x3.index(0,IDirect,true) //item
      x5.index(0,IDirect,true) //district
      x7.index(0,IDirect,true) //customer
      x8.index(0,IDirect,true) //stock
      x4.index(1,ISliceHeapMax,false,0)
      x0.index(1,ISliceHeapMin,false,0)
      // x0.startPerfCounters
      // x1.startPerfCounters
      // x2.startPerfCounters
      // x3.startPerfCounters
      // x4.startPerfCounters
      // x5.startPerfCounters
      // x6.startPerfCounters
      // x7.startPerfCounters
      // x.startPerfCounters
    }

    val newOrderTxInst = new newOrderTx(x0, x1, x2, x3, x4, x5, x6, x7, x8)
    val paymentTxInst = new paymentTx(x0, x1, x2, x3, x4, x5, x6, x7, x8)
    val orderStatusTxInst = new orderStatusTx(x0, x1, x2, x3, x4, x5, x6, x7, x8)
    val deliveryTxInst = new deliveryTx(x0, x1, x2, x3, x4, x5, x6, x7, x8)
    val stockLevelTxInst = new stockLevelTx(x0, x1, x2, x3, x4, x5, x6, x7, x8)
  }
}

object DummyPrint { // TODO (Mohammad) What should we do here?
  def println(s: Any): Unit = ()
}