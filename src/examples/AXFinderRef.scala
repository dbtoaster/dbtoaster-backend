package examples

import java.io._;
import org.dbtoaster.dbtoasterlib.StreamAdaptor._;
import org.dbtoaster.dbtoasterlib.K3Collection._;
import org.dbtoaster.dbtoasterlib.Source._;
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._;
import org.dbtoaster.dbtoasterlib.ImplicitConversions._;
import org.dbtoaster.dbtoasterlib.StdFunctions._;
import org.dbtoaster.dbtoasterlib.QueryInterface._;
import scala.collection.mutable.Map;
import java.util.Date;
import java.util.GregorianCalendar;
import xml._;
import scala.actors.Actor;
import scala.actors.Actor._;

// Reference for correctness

object AXFinderRef {
  val onTupleProc = (u:Unit)=>{}
  val onQDone = (u:Unit)=>{}
  val q = new AXFinderRef("resources/data/finance.csv")

  def main(args: Array[String]): Unit = {
    var counter = 0
    val logCountIdx = args.indexOf("--log-count")
    val logCount: Int = if (logCountIdx >= 0) args(logCountIdx + 1).toInt else -1
    val logMapSizes = args.contains("--log-map-sizes")

    def printProgress(i: Int) {
      val t = System.nanoTime() / 1000
      val us = t % 1000000
      val s = t / 1000000
      println(i + " tuples processed at " + s + "s+" + us + "us")
      if (logMapSizes) q.printMapSizes
    }

    val timeStart = System.nanoTime()

    val msgRcvr = new DBTMessageReceiver {
      def onTupleProcessed(): Unit = {
        onTupleProc();
        if (logCount > 0) {
          counter += 1
          if (counter % logCount == 0) printProgress(counter)
        }
      }
      def onQueryDone(): Unit = {
        onQDone();
        if (logCount > 0 && counter % logCount != 0) printProgress(counter)
        val runtime = (System.nanoTime() - timeStart) / 1000000000.0
        println("<runtime>" + runtime + "</runtime>")
        q.printResults()
      }
    }

    val r = new QuerySupervisor(q, msgRcvr)
    if (logCount > 0) printProgress(0)
    r.start
  }
}

class AXFinderRef(file:String) extends DBTQuery {
  var supervisor: Actor = null;
  def setSupervisor(supervisor: Actor) = this.supervisor = supervisor;
  val s1 = createInputStreamSource(new FileReader(file), List(createAdaptor("orderbook", "BIDS", List(("book", "bids"),("brokers", "10"),("deterministic", "yes"))),createAdaptor("orderbook", "ASKS", List(("book", "asks"),("brokers", "10"),("deterministic", "yes")))), Delimited("\n"));;
  val sources = new SourceMultiplexer(this, List(s1));
  var AXFINDER = new K3PersistentCollection[(Long), Double]("AXFINDER", Map(), None) /* out */;
  var AXFINDER_mASKS1 = new K3PersistentCollection[Tuple2[Long,Double], Double]("AXFINDER_mASKS1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Double](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  )))) /* out */;
  var AXFINDER_mASKS2 = new K3PersistentCollection[Tuple2[Long,Double], Long]("AXFINDER_mASKS2", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Long](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  )))) /* out */;
  var AXFINDER_mBIDS1 = new K3PersistentCollection[Tuple2[Long,Double], Long]("AXFINDER_mBIDS1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Long](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  )))) /* out */;
  var AXFINDER_mBIDS3 = new K3PersistentCollection[Tuple2[Long,Double], Double]("AXFINDER_mBIDS3", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Double](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  )))) /* out */;
  def getAXFINDER():K3PersistentCollection[(Long), Double] = {
    AXFINDER
  };
  def onInsertBIDS(var_BIDS_T: Double,var_BIDS_ID: Long,var_BIDS_BROKER_ID: Long,var_BIDS_VOLUME: Double,var_BIDS_PRICE: Double) = {
    if((AXFINDER).contains((var_BIDS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_BIDS_BROKER_ID))) + ((((AXFINDER_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__1:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_1 => {
                  (var___accv_1) + ((var___map_ret__1) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L)) * (var_BIDS_VOLUME)) + (AXFINDER_mBIDS3.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__2:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_2 => {
                  (var___accv_2) + ((var___map_ret__2) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )));
        AXFINDER.updateValue((var_BIDS_BROKER_ID), nv)
      }
    }
    else {        {
        val nv = (((AXFINDER_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__1:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_1 => {
                  (var___accv_1) + ((var___map_ret__1) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L)) * (var_BIDS_VOLUME)) + (AXFINDER_mBIDS3.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__2:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_2 => {
                  (var___accv_2) + ((var___map_ret__2) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        ));
        AXFINDER.updateValue((var_BIDS_BROKER_ID), nv)
      }
    };
    if((AXFINDER_mASKS1).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) {        {
        val nv = ((AXFINDER_mASKS1).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) + (var_BIDS_VOLUME);
        AXFINDER_mASKS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    }
    else {        {
        val nv = var_BIDS_VOLUME;
        AXFINDER_mASKS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    };
    if((AXFINDER_mASKS2).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) {        {
        val nv = ((AXFINDER_mASKS2).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) + (1L);
        AXFINDER_mASKS2.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    }
    else {        {
        val nv = 1L;
        AXFINDER_mASKS2.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    }
  };
  def onDeleteBIDS(var_BIDS_T: Double,var_BIDS_ID: Long,var_BIDS_BROKER_ID: Long,var_BIDS_VOLUME: Double,var_BIDS_PRICE: Double) = {
    if((AXFINDER).contains((var_BIDS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_BIDS_BROKER_ID))) + (((AXFINDER_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__3:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_3 => {
                  (var___accv_3) + ((var___map_ret__3) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (var_BIDS_VOLUME)) + ((AXFINDER_mBIDS3.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__4:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_4 => {
                  (var___accv_4) + ((var___map_ret__4) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L)));
        AXFINDER.updateValue((var_BIDS_BROKER_ID), nv)
      }
    }
    else {        {
        val nv = ((AXFINDER_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__3:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_3 => {
                  (var___accv_3) + ((var___map_ret__3) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (var_BIDS_VOLUME)) + ((AXFINDER_mBIDS3.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_A_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__4:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_4 => {
                  (var___accv_4) + ((var___map_ret__4) * ((0L) < (((if((1000L) < ((var_A_PRICE) + ((-1L) * (var_BIDS_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_BIDS_PRICE) + ((-1L) * (var_A_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L));
        AXFINDER.updateValue((var_BIDS_BROKER_ID), nv)
      }
    };
    if((AXFINDER_mASKS1).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) {        {
        val nv = ((AXFINDER_mASKS1).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) + ((-1L) * (var_BIDS_VOLUME));
        AXFINDER_mASKS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    }
    else {        {
        val nv = (-1L) * (var_BIDS_VOLUME);
        AXFINDER_mASKS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    };
    if((AXFINDER_mASKS2).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) {        {
        val nv = ((AXFINDER_mASKS2).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE))) + (-1L);
        AXFINDER_mASKS2.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    }
    else {        {
        val nv = -1L;
        AXFINDER_mASKS2.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_PRICE), nv)
      }
    }
  };
  def onInsertASKS(var_ASKS_T: Double,var_ASKS_ID: Long,var_ASKS_BROKER_ID: Long,var_ASKS_VOLUME: Double,var_ASKS_PRICE: Double) = {
    if((AXFINDER).contains((var_ASKS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_ASKS_BROKER_ID))) + (((AXFINDER_mASKS1.slice((var_ASKS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__5:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_5 => {
                  (var___accv_5) + ((var___map_ret__5) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L)) + ((AXFINDER_mASKS2.slice((var_ASKS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__6:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_6 => {
                  (var___accv_6) + ((var___map_ret__6) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (var_ASKS_VOLUME)));
        AXFINDER.updateValue((var_ASKS_BROKER_ID), nv)
      }
    }
    else {        {
        val nv = ((AXFINDER_mASKS1.slice((var_ASKS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__5:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_5 => {
                  (var___accv_5) + ((var___map_ret__5) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L)) + ((AXFINDER_mASKS2.slice((var_ASKS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__6:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_6 => {
                  (var___accv_6) + ((var___map_ret__6) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (var_ASKS_VOLUME));
        AXFINDER.updateValue((var_ASKS_BROKER_ID), nv)
      }
    };
    if((AXFINDER_mBIDS1).contains(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) {        {
        val nv = ((AXFINDER_mBIDS1).lookup(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) + (1L);
        AXFINDER_mBIDS1.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    }
    else {        {
        val nv = 1L;
        AXFINDER_mBIDS1.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    };
    if((AXFINDER_mBIDS3).contains(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) {        {
        val nv = ((AXFINDER_mBIDS3).lookup(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) + (var_ASKS_VOLUME);
        AXFINDER_mBIDS3.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    }
    else {        {
        val nv = var_ASKS_VOLUME;
        AXFINDER_mBIDS3.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    }
  };
  def onDeleteASKS(var_ASKS_T: Double,var_ASKS_ID: Long,var_ASKS_BROKER_ID: Long,var_ASKS_VOLUME: Double,var_ASKS_PRICE: Double) = {
    if((AXFINDER).contains((var_ASKS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_ASKS_BROKER_ID))) + ((AXFINDER_mASKS1.slice((var_ASKS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__7:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_7 => {
                  (var___accv_7) + ((var___map_ret__7) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) + (((AXFINDER_mASKS2.slice((var_ASKS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__8:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_8 => {
                  (var___accv_8) + ((var___map_ret__8) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L)) * (var_ASKS_VOLUME)));
        AXFINDER.updateValue((var_ASKS_BROKER_ID), nv)
      }
    }
    else {        {
        val nv = (AXFINDER_mASKS1.slice((var_ASKS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__7:Double = x._2 /* Double => Double */;
            (y:Double) => {
              y match {
                case var___accv_7 => {
                  (var___accv_7) + ((var___map_ret__7) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) + (((AXFINDER_mASKS2.slice((var_ASKS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1 /* Long => Long */;
            val var_B_PRICE:Double = x._1._2 /* Double => Double */;
            val var___map_ret__8:Long = x._2 /* Long => Long */;
            (y:Long) => {
              y match {
                case var___accv_8 => {
                  (var___accv_8) + ((var___map_ret__8) * ((0L) < (((if((1000L) < ((var_ASKS_PRICE) + ((-1L) * (var_B_PRICE)))) 1L else 0L)) + ((if((1000L) < ((var_B_PRICE) + ((-1L) * (var_ASKS_PRICE)))) 1L else 0L)))))
                }
              }
            }
          }
        }
        )) * (-1L)) * (var_ASKS_VOLUME));
        AXFINDER.updateValue((var_ASKS_BROKER_ID), nv)
      }
    };
    if((AXFINDER_mBIDS1).contains(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) {        {
        val nv = ((AXFINDER_mBIDS1).lookup(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) + (-1L);
        AXFINDER_mBIDS1.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    }
    else {        {
        val nv = -1L;
        AXFINDER_mBIDS1.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    };
    if((AXFINDER_mBIDS3).contains(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) {        {
        val nv = ((AXFINDER_mBIDS3).lookup(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE))) + ((-1L) * (var_ASKS_VOLUME));
        AXFINDER_mBIDS3.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    }
    else {        {
        val nv = (-1L) * (var_ASKS_VOLUME);
        AXFINDER_mBIDS3.updateValue(Tuple2(var_ASKS_BROKER_ID,var_ASKS_PRICE), nv)
      }
    }
  };
  def onSystemInitialized() = {}
  def fillTables(): Unit = {}
  def dispatcher(event: DBTEvent): Unit = {
    event match {
      case StreamEvent(InsertTuple, o, "BIDS", (var_BIDS_T: Double)::(var_BIDS_ID: Long)::(var_BIDS_BROKER_ID: Long)::(var_BIDS_VOLUME: Double)::(var_BIDS_PRICE: Double)::Nil) => onInsertBIDS(var_BIDS_T,var_BIDS_ID,var_BIDS_BROKER_ID,var_BIDS_VOLUME,var_BIDS_PRICE);
      case StreamEvent(DeleteTuple, o, "BIDS", (var_BIDS_T: Double)::(var_BIDS_ID: Long)::(var_BIDS_BROKER_ID: Long)::(var_BIDS_VOLUME: Double)::(var_BIDS_PRICE: Double)::Nil) => onDeleteBIDS(var_BIDS_T,var_BIDS_ID,var_BIDS_BROKER_ID,var_BIDS_VOLUME,var_BIDS_PRICE);
      case StreamEvent(InsertTuple, o, "ASKS", (var_ASKS_T: Double)::(var_ASKS_ID: Long)::(var_ASKS_BROKER_ID: Long)::(var_ASKS_VOLUME: Double)::(var_ASKS_PRICE: Double)::Nil) => onInsertASKS(var_ASKS_T,var_ASKS_ID,var_ASKS_BROKER_ID,var_ASKS_VOLUME,var_ASKS_PRICE);
      case StreamEvent(DeleteTuple, o, "ASKS", (var_ASKS_T: Double)::(var_ASKS_ID: Long)::(var_ASKS_BROKER_ID: Long)::(var_ASKS_VOLUME: Double)::(var_ASKS_PRICE: Double)::Nil) => onDeleteASKS(var_ASKS_T,var_ASKS_ID,var_ASKS_BROKER_ID,var_ASKS_VOLUME,var_ASKS_PRICE);
      case StreamEvent(SystemInitialized, o, "", Nil) => onSystemInitialized();
      case EndOfStream => ();
      case _ => throw DBTFatalError("Event could not be dispatched: " + event)
    }
    supervisor ! DBTTupleProcessed;
  }
  def act(): Unit ={
    fillTables();
    onSystemInitialized();
    sources.start;
    while(true) {
      receive {
        case EndOfStream => {
          supervisor ! DBTDone;
          exit();
        }
        case e: DBTEvent => dispatcher(e) 
      }
    }
  }
  def printResults(): Unit = {
    val pp = new PrettyPrinter(8000, 2);
    println(pp.format(<AXFINDER>{
      getAXFINDER().toXML() 
    }
    </AXFINDER>));
  }
  def printMapSizes() = {
    AXFINDER.printSize;
    AXFINDER_mASKS1.printSize;
    AXFINDER_mASKS2.printSize;
    AXFINDER_mBIDS1.printSize;
    AXFINDER_mBIDS3.printSize;
  }
}
