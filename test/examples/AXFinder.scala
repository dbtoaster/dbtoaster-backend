package ddbt.test.examples
import ddbt.lib._

import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import scala.reflect.ClassTag

object AXFinder extends Helper {
  def test[Q<:akka.actor.Actor](name:String,count:Int=10)(implicit cq:ClassTag[Q]) =
        bench(name,count,()=>run[Q,Map[Long,Double]](streamsFinance(""),false))

  def main(args:Array[String]) {
    //val r1=test[AXFinderRef]      ("Reference   ")
    val r2=test[AXFinder]         ("Gen2        "); //assert(r1==r2)
    val r4=test[AXFinderSimpleLMS]("Simple LMS  ")
    val r5=test[AXFinderSimple]   ("Simple Gen2 "); assert(r4==r5)
    println(K3Helper.toStr(r2))
  }
}

// -----------------------------------------------------------------------------
abstract class AXFinderBase extends Actor {
  import Messages._
  import scala.language.implicitConversions  
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L
  
  var t0:Long = 0
  //override def preStart(): Unit = println("Started")
  //override def postStop(): Unit = println("Stopped")
  def result:Map[_,_]
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"BIDS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddBIDS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"BIDS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelBIDS(t,id,b,v,p)
    case TupleEvent(TupleInsert,"ASKS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddASKS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"ASKS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelASKS(t,id,b,v,p)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,result)
  }
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double):Unit
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double):Unit
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double):Unit
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double):Unit
}

// -----------------------------------------------------------------------------
class AXFinder extends AXFinderBase {
  val AXFINDER = K3Map.make[Long,Double]();
  val mASKS1 = K3Map.makeIdx[(Long,Double),Double](List(0));
  val mASKS2 = K3Map.makeIdx[(Long,Double),Long](List(0));
  val mBIDS1 = K3Map.makeIdx[(Long,Double),Long](List(0));
  val mBIDS3 = K3Map.makeIdx[(Long,Double),Double](List(0));
  def result = AXFINDER.toMap
  
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg1 = mBIDS1.slice(0,BIDS_BROKER_ID).aggr { case (k2,v3) =>
      val A_PRICE = k2._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      v3 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    val agg4 = mBIDS3.slice(0,BIDS_BROKER_ID).aggr { case (k5,v6) =>
      val A_PRICE = k5._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      v6 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg1 * -BIDS_VOLUME) + agg4));
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),1L);
  }
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg7 = mBIDS1.slice(0,BIDS_BROKER_ID).aggr { case (k8,v9) => val A_PRICE = k8._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      v9 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    val agg10 = mBIDS3.slice(0,BIDS_BROKER_ID).aggr { case (k11,v12) => val A_PRICE = k11._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      v12 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg7 * BIDS_VOLUME) + (agg10 * -1L)));
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),-1L);
  }
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val agg13 = mASKS1.slice(0,ASKS_BROKER_ID).aggr { case (k14,v15) => val B_PRICE = k14._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      v15 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    val agg16 = mASKS2.slice(0,ASKS_BROKER_ID).aggr { case (k17,v18) => val B_PRICE = k17._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      v18 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    AXFINDER.add(ASKS_BROKER_ID,((agg13 * -1L) + (agg16 * ASKS_VOLUME)));
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
  }
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    var agg19 = mASKS1.slice(0,ASKS_BROKER_ID).aggr { case (k20,v21) => val B_PRICE = k20._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      v21 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    val agg22 = mASKS2.slice(0,ASKS_BROKER_ID).aggr { case (k23,v24) => val B_PRICE = k23._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      v24 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
    AXFINDER.add(ASKS_BROKER_ID,(agg19 + (agg22 * -ASKS_VOLUME)));
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),-1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
  }
}

// -----------------------------------------------------------------------------
class AXFinderSimple extends AXFinderBase {
  val COUNT = K3Map.make[Long,Long]();
  val COUNT_mASKS2 = new K3Var[Long]();
  val COUNT_mBIDS2 = new K3Var[Long]();
  def result = COUNT.toMap

  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * COUNT_mBIDS2.get()));
    COUNT_mASKS2.add(1L);
  }
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * (COUNT_mBIDS2.get() * -1L)));
    COUNT_mASKS2.add(-1L);
  }
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * COUNT_mASKS2.get()));
    COUNT_mBIDS2.add(1L);
  }
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * (COUNT_mASKS2.get() * -1L)));
    COUNT_mBIDS2.add(-1L);
  }
}

// -----------------------------------------------------------------------------
// Original result: 1 -> 270

class AXFinderSimpleLMS extends AXFinderBase {
  val COUNT = K3Map.make[Long,Long](); // out
  val COUNT_mASKS2 = K3Var[Long]();
  val COUNT_mBIDS2 = K3Var[Long]();
  def result = COUNT.toMap

  def onAddBIDS(COUNT4: Double, COUNT5: Long, COUNT6: Long, COUNT7: Double, COUNT8: Double): Unit = {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val COUNT_mASKS25 = COUNT_mBIDS2.get
    x9.foreach { COUNT_mASKS22 =>
      val COUNT_mASKS23 = COUNT_mASKS22._1
      val COUNT_mASKS24 = COUNT_mASKS22._2
      val COUNT_mASKS26 = COUNT_mASKS24 * COUNT_mASKS25
      val COUNT_mASKS28 = COUNT.get(COUNT_mASKS23)!=0L
      val COUNT_mBIDS20 = if (COUNT_mASKS28) COUNT.get(COUNT_mASKS23) else 0L
      val COUNT_mBIDS21 = COUNT_mBIDS20 + COUNT_mASKS26
      COUNT.set(COUNT_mASKS23, COUNT_mBIDS21)
    }
    val COUNT_mBIDS25 = COUNT_mASKS2.get
    val COUNT_mBIDS26 = COUNT_mBIDS25 + 1L
    COUNT_mASKS2.set(COUNT_mBIDS26)
   }

  def onDelBIDS(COUNT_mBIDS29: Double, x80: Long, x81: Long, x82: Double, x83: Double) {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val x90 = COUNT_mBIDS2.get
    x9.foreach { x87 =>
      val x88 = x87._1
      val x89 = x87._2
      val x91 = x89 * x90
      val x93 = x91 * -1L
      val x95 = COUNT.get(x88)!=0L
      val x97 = if (x95) COUNT.get(x88) else 0L
      val x98 = x97 + x93
      COUNT.set(x88, x98)
    }
    val x102 = COUNT_mASKS2.get
    val x103 = x102 + -1L
    COUNT_mASKS2.set(x103)
   }

  def onAddASKS(x0: Double, x1: Long, x2: Long, x3: Double, x4: Double) {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val x13 = COUNT_mASKS2.get
    x9.foreach { x10 =>
      val x11 = x10._1
      val x12 = x10._2
      val x14 = x12 * x13
      val x16 = COUNT.get(x11)!=0L
      val x18 = if (x16) COUNT.get(x11) else 0L
      val x19 = x18 + x14
      COUNT.set(x11, x19)
    }
    val x23 = COUNT_mBIDS2.get
    val x24 = x23 + 1L
    COUNT_mBIDS2.set(x24)
   }

  def onDelASKS(x27: Double, x28: Long, x29: Long, x30: Double, x31: Double) {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val x38 = COUNT_mASKS2.get
    x9.foreach { x35 =>
      val x36 = x35._1
      val x37 = x35._2
      val x39 = x37 * x38
      val x41 = x39 * -1L
      val x43 = COUNT.get(x36)!=0L
      val x45 = if (x43) COUNT.get(x36) else 0L
      val x46 = x45 + x41
      COUNT.set(x36, x46)
    }
    val COUNT0 = COUNT_mBIDS2.get
    val COUNT1 = COUNT0 + -1L
    COUNT_mBIDS2.set(COUNT1)
   }
}

// -----------------------------------------------------------------------------

/*
class AXFinderRef extends AXFinderBase {

import org.dbtoaster.dbtoasterlib.StreamAdaptor._;
import org.dbtoaster.dbtoasterlib.K3Collection._;
import org.dbtoaster.dbtoasterlib.Source._;
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._;
import org.dbtoaster.dbtoasterlib.StdFunctions._;
import org.dbtoaster.dbtoasterlib.QueryInterface._;
import scala.collection.mutable.Map;

  def result = AXFINDER.elems.toMap.filter{case(k,v)=>v!=0.0}

  var AXFINDER = new K3PersistentCollection[(Long), Double]("AXFINDER", Map(), None);
  var AXFINDER_mASKS1 = new K3PersistentCollection[Tuple2[Long,Double], Double]("AXFINDER_mASKS1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Double](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  ))));
  var AXFINDER_mASKS2 = new K3PersistentCollection[Tuple2[Long,Double], Long]("AXFINDER_mASKS2", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Long](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  ))));
  var AXFINDER_mBIDS1 = new K3PersistentCollection[Tuple2[Long,Double], Long]("AXFINDER_mBIDS1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Long](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  ))));
  var AXFINDER_mBIDS3 = new K3PersistentCollection[Tuple2[Long,Double], Double]("AXFINDER_mBIDS3", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple2[Long,Double], Double](x => x match {
    case Tuple2(x1,x2) => (x1) 
  }
  ))));

  def onAddBIDS(var_BIDS_T: Double,var_BIDS_ID: Long,var_BIDS_BROKER_ID: Long,var_BIDS_VOLUME: Double,var_BIDS_PRICE: Double) = {
    if((AXFINDER).contains((var_BIDS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_BIDS_BROKER_ID))) + ((((AXFINDER_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__1:Long = x._2;
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
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__2:Double = x._2;
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
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__1:Long = x._2;
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
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__2:Double = x._2;
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
  def onDelBIDS(var_BIDS_T: Double,var_BIDS_ID: Long,var_BIDS_BROKER_ID: Long,var_BIDS_VOLUME: Double,var_BIDS_PRICE: Double) = {
    if((AXFINDER).contains((var_BIDS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_BIDS_BROKER_ID))) + (((AXFINDER_mBIDS1.slice((var_BIDS_BROKER_ID), List(0)).foldLong(0L, {
          (x:Tuple2[(Tuple2[Long,Double]), Long]) => {
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__3:Long = x._2;
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
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__4:Double = x._2;
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
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__3:Long = x._2;
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
            val var_BIDS_BROKER_ID:Long = x._1._1;
            val var_A_PRICE:Double = x._1._2;
            val var___map_ret__4:Double = x._2;
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
  def onAddASKS(var_ASKS_T: Double,var_ASKS_ID: Long,var_ASKS_BROKER_ID: Long,var_ASKS_VOLUME: Double,var_ASKS_PRICE: Double) = {
    if((AXFINDER).contains((var_ASKS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_ASKS_BROKER_ID))) + (((AXFINDER_mASKS1.slice((var_ASKS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__5:Double = x._2;
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
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__6:Long = x._2;
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
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__5:Double = x._2;
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
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__6:Long = x._2;
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
  def onDelASKS(var_ASKS_T: Double,var_ASKS_ID: Long,var_ASKS_BROKER_ID: Long,var_ASKS_VOLUME: Double,var_ASKS_PRICE: Double) = {
    if((AXFINDER).contains((var_ASKS_BROKER_ID))) {        {
        val nv = ((AXFINDER).lookup((var_ASKS_BROKER_ID))) + ((AXFINDER_mASKS1.slice((var_ASKS_BROKER_ID), List(0)).fold(0.0, {
          (x:Tuple2[(Tuple2[Long,Double]), Double]) => {
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__7:Double = x._2;
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
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__8:Long = x._2;
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
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__7:Double = x._2;
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
            val var_ASKS_BROKER_ID:Long = x._1._1;
            val var_B_PRICE:Double = x._1._2;
            val var___map_ret__8:Long = x._2;
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
}
*/
