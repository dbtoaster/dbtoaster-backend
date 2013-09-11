package examples
import ddbt.lib._

import akka.actor.Actor
import java.util.Date

object BrokerSpread extends Helper {  
  import scala.language.implicitConversions
  implicit def dateConv(d:Long):Date = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();
  //implicit def strConv(d:Long):String = ""+d
  
  def main(args:Array[String]) {
    val (t,res) = run[BrokerSpread,Map[Long,Double]](Seq(
      (new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/finance/standard/finance.csv"),new Adaptor.OrderBook(),Split())
    ))
  
    val (t2,ref) = run[BrokerSpreadRef,Map[Long,Double]](Seq(
      (new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/finance/standard/finance.csv"),new Adaptor.OrderBook(),Split())
    ))
  
    println("---------------- gen:")
    println(K3Helper.toStr(res))
    println("---------------- vanilla:")
    println(K3Helper.toStr(ref))
    println("---------------- gen/vanilla diff:")
    diff(res, ref)
    println("---------------- actual test diff:")
    def kv(l:List[Any]) = l match { case List(v0:Long,v1:Double) => (v0,v1) }
    try {
      diff(res, Map[Long,Double]((6L,-55136926200L),(9L,140073076900L),(0L,78933620700L),(5L,158875988600L),(1L,-114956214400L),(4L,18596229300L),(2L,186526996800L),(7L,-27166878800L),(3L,85729885500L),(8L,92711476900L)))
    } catch { case e:Exception => println("Failed: "+e.getMessage) }
  }
}

class BrokerSpread extends Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._

  val BSP = K3Map.make[Long,Double]();
  val BSP_mBIDS1 = K3Map.make[(Long,Double),Long](List((k:(Long,Double))=>k._1));
  val BSP_mBIDS5 = K3Map.make[(Long,Double),Double](List((k:(Long,Double))=>k._1));
  
  var t0:Long = 0
  def receive = {
    case TupleEvent(TupleInsert,"BIDS",tx,List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",tx,List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelBIDS(v0,v1,v2,v3,v4)
    case SystemInit => onSystemReady(); t0=System.nanoTime()
    case EndOfStream | GetSnapshot => val time=System.nanoTime()-t0; sender ! (time,BSP.toMap)
  }
  
  def onAddBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    var agg1:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k1,v1) =>
      val y_t = k1._2;
      agg1 += (v1 * (if (bids_t > y_t) 1L else 0L));
    }
    var agg2:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k2,v2) =>
      val x_t = k2._2;
      agg2 += (v2 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg3:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k3,v3) =>
      val x_t = k3._2;
      agg3 += (v3 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg4:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k4,v4) =>
      val y_t = k4._2;
      agg4 += (v4 * (if (bids_t > y_t) 1L else 0L));
    }
    BSP.add(bids_broker_id,(((agg1 + (agg2 * -1L)) * (bids_price * bids_volume)) + (agg3 + (agg4 * -1L))));
    BSP_mBIDS1.add((bids_broker_id,bids_t),1L);
    BSP_mBIDS5.add((bids_broker_id,bids_t),(bids_volume * bids_price));
  }
  
  def onDelBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    var agg5:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k5,v5) =>
      val y_t = k5._2;
      agg5 += (v5 * (if (bids_t > y_t) 1L else 0L));
    }
    var agg6:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k6,v6) =>
      val x_t = k6._2;
      agg6 += (v6 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg7:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k7,v7) =>
      val x_t = k7._2;
      agg7 += (v7 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg8:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k8,v8) =>
      val y_t = k8._2;
      agg8 += (v8 * (if (bids_t > y_t) 1L else 0L));
    }
    BSP.add(bids_broker_id,((((agg5 * -1L) + agg6) * (bids_price * bids_volume)) + ((agg7 * -1L) + agg8)));
    BSP_mBIDS1.add((bids_broker_id,bids_t),-1L);
    BSP_mBIDS5.add((bids_broker_id,bids_t),(-1L * (bids_volume * bids_price)));
  }
  
  def onSystemReady() {
    
  }
}


class BrokerSpreadRef extends Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._

  var t0:Long = 0
  def receive = {
    case TupleEvent(TupleInsert,"BIDS",tx,List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",tx,List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelBIDS(v0,v1,v2,v3,v4)
    case SystemInit => /*onSystemReady();*/ t0=System.nanoTime()
    case EndOfStream | GetSnapshot => val time=System.nanoTime()-t0; sender ! (time,BSP.elems.toMap)
  }

  import org.dbtoaster.dbtoasterlib.K3Collection._;
  import org.dbtoaster.dbtoasterlib.DBToasterExceptions._;
  import org.dbtoaster.dbtoasterlib.ImplicitConversions._;
  import org.dbtoaster.dbtoasterlib.StdFunctions._;

  import scala.collection.mutable.Map;
  import scala.collection.JavaConversions.mapAsScalaMap;

  val BSP = new K3PersistentCollection[(Long), Double]("BSP", Map(), None) /* out */;
  val BSP_mBIDS1 = new K3PersistentCollection[Tuple2[Long,Double], Long]("BSP_mBIDS1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Long](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  )))) /* out */;
  val BSP_mBIDS5 = new K3PersistentCollection[Tuple2[Long,Double], Double]("BSP_mBIDS5", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Double](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  )))) /* out */;
  def getBSP():K3PersistentCollection[(Long), Double] = {
    BSP
  };
  def onAddBIDS(var_BIDS_T: Double,var_BIDS_ID: Long,var_BIDS_BROKER_ID: Long,var_BIDS_VOLUME: Double,var_BIDS_PRICE: Double) = {      {
      if((BSP).contains((var_BIDS_BROKER_ID))) {          {
          val nv = ((BSP).lookup((var_BIDS_BROKER_ID))) + ((((((BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__1:Long = x._2
              (var___accv_1:Long) => {
                (var___accv_1) + ((var___map_ret__1) * ((if((var_Y_T) < (var_BIDS_T)) 1L else 0L))) 
              }
            }
          }
          )) + ((BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__2:Long = x._2
              (var___accv_2:Long) => {
                (var___accv_2) + ((var___map_ret__2) * ((if((var_BIDS_T) < (var_X_T)) 1L else 0L))) 
              }
            }
          }
          )) * (-1L))) * (var_BIDS_PRICE)) * (var_BIDS_VOLUME)) + (BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__3:Double = x._2
              (var___accv_3:Double) => {
                (var___accv_3) + ((var___map_ret__3) * ((if((var_BIDS_T) < (var_X_T)) 1.0 else 0.0))) 
              }
            }
          }
          ))) + ((BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__4:Double = x._2
              (var___accv_4:Double) => {
                (var___accv_4) + ((var___map_ret__4) * ((if((var_Y_T) < (var_BIDS_T)) 1.0 else 0.0))) 
              }
            }
          }
          )) * (-1L)));
          BSP.updateValue((var_BIDS_BROKER_ID), nv)
        }
      }
      else {          {
          val nv = (((((BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__1:Long = x._2
              (var___accv_1:Long) => {
                (var___accv_1) + ((var___map_ret__1) * ((if((var_Y_T) < (var_BIDS_T)) 1L else 0L))) 
              }
            }
          }
          )) + ((BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__2:Long = x._2
              (var___accv_2:Long) => {
                (var___accv_2) + ((var___map_ret__2) * ((if((var_BIDS_T) < (var_X_T)) 1L else 0L))) 
              }
            }
          }
          )) * (-1L))) * (var_BIDS_PRICE)) * (var_BIDS_VOLUME)) + (BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__3:Double = x._2
              (var___accv_3:Double) => {
                (var___accv_3) + ((var___map_ret__3) * ((if((var_BIDS_T) < (var_X_T)) 1.0 else 0.0))) 
              }
            }
          }
          ))) + ((BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__4:Double = x._2
              (var___accv_4:Double) => {
                (var___accv_4) + ((var___map_ret__4) * ((if((var_Y_T) < (var_BIDS_T)) 1.0 else 0.0))) 
              }
            }
          }
          )) * (-1L));
          BSP.updateValue((var_BIDS_BROKER_ID), nv)
        }
      };
      if((BSP_mBIDS1).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) {          {
          val nv = ((BSP_mBIDS1).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) + (1L);
          BSP_mBIDS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      }
      else {          {
          val nv = 1L;
          BSP_mBIDS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      };
      if((BSP_mBIDS5).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) {          {
          val nv = ((BSP_mBIDS5).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) + ((var_BIDS_VOLUME) * (var_BIDS_PRICE));
          BSP_mBIDS5.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      }
      else {          {
          val nv = (var_BIDS_VOLUME) * (var_BIDS_PRICE);
          BSP_mBIDS5.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      }
    }
  };
  def onDelBIDS(var_BIDS_T: Double,var_BIDS_ID: Long,var_BIDS_BROKER_ID: Long,var_BIDS_VOLUME: Double,var_BIDS_PRICE: Double) = {      {
      if((BSP).contains((var_BIDS_BROKER_ID))) {          {
          val nv = ((BSP).lookup((var_BIDS_BROKER_ID))) + (((((((BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__5:Long = x._2
              (var___accv_5:Long) => {
                (var___accv_5) + ((var___map_ret__5) * ((if((var_Y_T) < (var_BIDS_T)) 1L else 0L))) 
              }
            }
          }
          )) * (-1L)) + (BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__6:Long = x._2
              (var___accv_6:Long) => {
                (var___accv_6) + ((var___map_ret__6) * ((if((var_BIDS_T) < (var_X_T)) 1L else 0L))) 
              }
            }
          }
          ))) * (var_BIDS_PRICE)) * (var_BIDS_VOLUME)) + ((BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__7:Double = x._2
              (var___accv_7:Double) => {
                (var___accv_7) + ((var___map_ret__7) * ((if((var_BIDS_T) < (var_X_T)) 1.0 else 0.0))) 
              }
            }
          }
          )) * (-1L))) + (BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__8:Double = x._2
              (var___accv_8:Double) => {
                (var___accv_8) + ((var___map_ret__8) * ((if((var_Y_T) < (var_BIDS_T)) 1.0 else 0.0))) 
              }
            }
          }
          )));
          BSP.updateValue((var_BIDS_BROKER_ID), nv)
        }
      }
      else {          {
          val nv = ((((((BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__5:Long = x._2
              (var___accv_5:Long) => {
                (var___accv_5) + ((var___map_ret__5) * ((if((var_Y_T) < (var_BIDS_T)) 1L else 0L))) 
              }
            }
          }
          )) * (-1L)) + (BSP_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
            (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__6:Long = x._2
              (var___accv_6:Long) => {
                (var___accv_6) + ((var___map_ret__6) * ((if((var_BIDS_T) < (var_X_T)) 1L else 0L))) 
              }
            }
          }
          ))) * (var_BIDS_PRICE)) * (var_BIDS_VOLUME)) + ((BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_X_T:Double = x._1._2
              val var___map_ret__7:Double = x._2
              (var___accv_7:Double) => {
                (var___accv_7) + ((var___map_ret__7) * ((if((var_BIDS_T) < (var_X_T)) 1.0 else 0.0))) 
              }
            }
          }
          )) * (-1L))) + (BSP_mBIDS5.slice((var_BIDS_BROKER_ID), List(0)).fold(0.0, {
            (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
              val var_BIDS_BROKER_ID:Long = x._1._1
              val var_Y_T:Double = x._1._2
              val var___map_ret__8:Double = x._2
              (var___accv_8:Double) => {
                (var___accv_8) + ((var___map_ret__8) * ((if((var_Y_T) < (var_BIDS_T)) 1.0 else 0.0))) 
              }
            }
          }
          ));
          BSP.updateValue((var_BIDS_BROKER_ID), nv)
        }
      };
      if((BSP_mBIDS1).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) {          {
          val nv = ((BSP_mBIDS1).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) + (-1L);
          BSP_mBIDS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      }
      else {          {
          val nv = -1L;
          BSP_mBIDS1.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      };
      if((BSP_mBIDS5).contains(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) {          {
          val nv = ((BSP_mBIDS5).lookup(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T))) + (((-1L) * (var_BIDS_VOLUME)) * (var_BIDS_PRICE));
          BSP_mBIDS5.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      }
      else {          {
          val nv = ((-1L) * (var_BIDS_VOLUME)) * (var_BIDS_PRICE);
          BSP_mBIDS5.updateValue(Tuple2(var_BIDS_BROKER_ID,var_BIDS_T), nv)
        }
      }
    }
  };
}
