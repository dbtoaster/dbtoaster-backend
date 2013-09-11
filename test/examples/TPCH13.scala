package ddbt.test.examples
import ddbt.lib._

import akka.actor.Actor
import java.util.Date
import org.dbtoaster.dbtoasterlib.StdFunctions._

/**
 * This query demonstrates that we _NEED_ to use intermediate maps
 * for aggregation with multiple keys. We need to decompose in 2 steps:
 * 1. for all mapping, we write into the map (body of AggSum)
 * 2. We do a foreach on the map and execute the continuation.
 */

object TPCH13 extends Helper {
  def main(args:Array[String]) {
    val ref = bench("ReferenceLMS ",10,()=>run[TPCH13Ref,Map[Long,Long]](streamsTPCH13()))
    val res = bench("HandOptimized",10,()=>run[TPCH13,Map[Long,Long]](streamsTPCH13()))
    val gen = bench("TCK-Generated",10,()=>run[TPCH13Gen,Map[Long,Long]](streamsTPCH13()))
    def eq(m1:Map[Long,Long],m2:Map[Long,Long]) = m1.filter{case (k,v) => v!=0}==m2.filter{case (k,v) => v!=0}
    println("Correctness: "+(if(eq(ref,res)) "OK" else "FAILURE !!!!"))
    println("Correctness: "+(if(eq(ref,gen)) "OK" else "FAILURE !!!!"))
    println("Reference:"); println(K3Helper.toStr(ref));
    if(!eq(ref,res)) { println("HandOpt:"); println(K3Helper.toStr(res)); }
    if(!eq(ref,gen)) { println("Generated:"); println(K3Helper.toStr(gen)); }
  }
}

// NB: only inserts have been optimized
class TPCH13 extends Actor {
  import Messages._
  import scala.language.implicitConversions
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  var t0:Long = 0
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"ORDERS",tx,List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onInsertORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",tx,List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDeleteORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",tx,List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) =>
       onInsertCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
       onInsertCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
       onDeleteCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",tx,List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDeleteCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,result.toMap)
  }

  val CUSTDIST = K3Map.make[Long,Long]()
  val CUSTDIST_mORDERS1_E1_4 = K3Map.make[Long,Long]()
  val CUSTDIST_mCUSTOMER1_E1_1 = K3Map.make[Long,Long]()
  val CUSTDIST_mCUSTOMER1_E1_3 = K3Map.make[Long,Long]()
  def result:Map[Long,Long] = CUSTDIST.toMap

  def onInsertORDERS(x6: Long, x7: Long, x8: String, x9: Double, x10: Date, x11: String, x12: String, x13: Long, x14: String): Unit = {
    val temp = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val l0 = CUSTDIST_mCUSTOMER1_E1_1.get(x7)
    val l4 = CUSTDIST_mORDERS1_E1_4.get(x7)
    val x64 = 0L == regexp_match("^.*special.*requests.*$", x14)
    val x70 = x64 * l4
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) =>
      temp.add(v, (v != 0L) * 4)
      temp.add(v + (((x7 == k) * x64) * l4), v != 0L)
    }
    temp.add(l0, (x70 != 0L) * 2)
    temp.add(l0 + (x64 * l4), x70 != 0L)
    temp.foreach { case (k,v) =>
        CUSTDIST.set(k, (if (CUSTDIST.get(k)!=0) CUSTDIST.get(k) else {
          CUSTDIST_mCUSTOMER1_E1_1.aggr((k2:Long,v2:Long) => (v2!=0L)*(v2==k))
        }) + v)
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(x7, x70)
    CUSTDIST_mCUSTOMER1_E1_3.add(x7, x64)
  }

  // unoptimized as not used
  def onDeleteCUSTOMER(x265: Long, x266: String, x267: String, x268: Long, x269: String, x270: Double, x271: String, x272: String): Unit = {
    val x279 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x280 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x281 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x281.add(v, v != 0L) }
    x281.foreach { case (k,v) => x280.add(k, v) }
    val x310 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x310.add(k, v) }
    val x325 = CUSTDIST_mCUSTOMER1_E1_3.get(x265) * -1L
    x310.add(x265, x325)
    val x330 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x310.foreach { case (k,v) => x330.add(CUSTDIST_mCUSTOMER1_E1_1.get(k), v != 0L) }
    x330.foreach { case (k,v) => x280.add(k, v) }
    x280.foreach { case (k,v) => x279.add(k,-v) }
    val x369 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x369.add(k, v) }
    x369.add(x265, x325)
    val x383 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x369.foreach { case (k,v) => x383.add(CUSTDIST_mCUSTOMER1_E1_1.get(k), v != 0L) }
    x383.foreach { case (k,v) => x279.add(k,v) }
    val x412 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x412.add(k, v) }
    x412.add(x265, x325)
    val x426 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x412.foreach { case (k,v) =>
      val x445 = CUSTDIST_mCUSTOMER1_E1_1.get(k) + (((x265 == k) * CUSTDIST_mCUSTOMER1_E1_3.get(x265)) * -1L)
      x426.add(x445, v != 0L)
    }
    x426.foreach { case (k,v) => x279.add(k, v) }
    x279.foreach { case (k,v) =>
        CUSTDIST.set(k, (if (CUSTDIST.get(k)!=0) CUSTDIST.get(k) else {
          var x470: Long = 0L
          CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k2,v2) => x470 += (v2 != 0L) * (v2 == k) }
          x470
        }) + v)
    }
    CUSTDIST_mORDERS1_E1_4.add(x265, -1L)
    CUSTDIST_mCUSTOMER1_E1_1.add(x265, x325)
  }

  def onInsertCUSTOMER(c_custkey: Long, x513: String, x514: String, x515: Long, x516: String, x517: Double, x518: String, x519: String): Unit = {
    val e = CUSTDIST_mCUSTOMER1_E1_3.get(c_custkey)

    // manually optimized version
    val tmp = K3Map.temp[Long, Long]()
    def gen(k:Long,v:Long) { val x=v+(k==c_custkey)*e; tmp.add(v,-(v!=0)); tmp.add(x,x!=0) }
    CUSTDIST_mCUSTOMER1_E1_1.foreach(gen)
    if (CUSTDIST_mCUSTOMER1_E1_1.get(c_custkey)==0L) gen(c_custkey,0L)
    tmp.foreach{ (k,v) =>
      if (CUSTDIST.get(k)==0L) CUSTDIST.set(k,CUSTDIST_mCUSTOMER1_E1_1.aggr { (k2,v2) => (v2!=0L)*(v2==k) })
      CUSTDIST.add(k, v)
    }
    // XXX: for network, create a K3MapWrapper that executes remotely and contains code for executing locally, then chain responder for messages

    /*
    // (A + B) * -1 + C + D
    val x526 = K3Map.temp[Long, Long]()
    // (A + B)
    val x527 = K3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x527.add(v, v != 0L) }
    val x557 = K3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x557.add(k, v) }
    x557.add(c_custkey, e)
    x557.foreach { (k,v) => val x585 = CUSTDIST_mCUSTOMER1_E1_1.get(k); x527.add(x585, v != 0L) }
    x527.foreach { (k,v) => x526.add(k, v * -1L) }
    // C
    val x614 = K3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x614.add(k, v) }
    x614.add(c_custkey, e)
    x614.foreach { (k,v) => val x638 = CUSTDIST_mCUSTOMER1_E1_1.get(k); x526.add(x638, v != 0L) }
    // D
    val x657 = K3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x657.add(k, v) }
    x657.add(c_custkey, e)
    x657.foreach { (k,v) =>
        val x689 = CUSTDIST_mCUSTOMER1_E1_1.get(k) + ((c_custkey == k) * e)
        x526.add(x689, v != 0L)
    }
    // Update
    x526.foreach { (k,v) =>
      if (CUSTDIST.get(k)==0L) CUSTDIST.set(k, CUSTDIST_mCUSTOMER1_E1_1.aggr{ (k2,v2) =>(v2 != 0L) * (v2 == k)})
      CUSTDIST.add(k, v)
    }
    */

    CUSTDIST_mORDERS1_E1_4.add(c_custkey, 1L)
    CUSTDIST_mCUSTOMER1_E1_1.add(c_custkey, e)
  }
  /*
  CUSTDIST(int)[][C_ORDERS_C_COUNT]:(AggSum([C_ORDERS_C_COUNT],((Exists(CUSTDIST_mCUSTOMER1_E1_1(int)[][C_ORDERS_C_CUSTKEY]) * (C_ORDERS_C_COUNT ^= CUSTDIST_mCUSTOMER1_E1_1(int)[][C_ORDERS_C_CUSTKEY]))))) +=
  let k = C_ORDERS_C_CUSTKEY
  let v = CUSTDIST_mCUSTOMER1_E1_1(int)[][k]
  let e = CUSTDIST_mCUSTOMER1_E1_3(int)[][CUSTOMER_CUSTKEY]
  let x = v + ((k ^= CUSTOMER_CUSTKEY) * e))
  (((
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS(v) *
    (C_ORDERS_C_COUNT ^= v)))
  +
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS((x) *
    (C_ORDERS_C_COUNT ^= v)))
  ) * -1) +
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS((x) *
    (C_ORDERS_C_COUNT ^= v)))
  +
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS((x) *
    (C_ORDERS_C_COUNT ^= x))
  );
  */

  // unoptimized as not used
  def onDeleteORDERS(x756: Long, x757: Long, x758: String, x759: Double, x760: Date, x761: String, x762: String, x763: Long, x764: String): Unit = {
    val x771 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x772 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x773 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x773.add(v, v != 0L) }
    x773.foreach { case (k,v) => x772.add(k, v) }
    val x802 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x802.add(k, v) }
    val x814 = 0L == regexp_match("^.*special.*requests.*$", x764)
    val x822 = (x814 * CUSTDIST_mORDERS1_E1_4.get(x757)) * -1L
    x802.add(x757, x822)
    val x827 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x802.foreach { case (k,v) =>
      val x837 = CUSTDIST_mCUSTOMER1_E1_1.get(k)
      x827.add(x837, v != 0L)
    }
    x827.foreach { case (k,v) => x772.add(k, v) }
    x772.foreach { case (k,v) => x771.add(k, v * -1L) }
    val x866 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x866.add(k, v) }
    x866.add(x757, x822)
    val x880 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x866.foreach { case (k,v) =>
      val x882 = k
      val x890 = CUSTDIST_mCUSTOMER1_E1_1.get(x882)
      x880.add(x890, v != 0L)
    }
    x880.foreach { case (k,v) => x771.add(k, v) }
    val x909 = K3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x909.add(k, v) }
    x909.add(x757, x822)
    val x923 = K3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x909.foreach { case (k,v) =>
      val x943 = CUSTDIST_mCUSTOMER1_E1_1.get(k) + ((((x757 == k) * x814) * CUSTDIST_mORDERS1_E1_4.get(x757)) * -1L)
      x923.set(x943, ((x923.get(x943)) + (v != 0L)))
    }
    x923.foreach { case (k,v) => x771.add(k,v) }
    x771.foreach { case (k,v) =>
        CUSTDIST.set(k, (if (CUSTDIST.get(k)!=0) CUSTDIST.get(k) else {
          var x968: Long = 0L
          CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k2,v2) =>
              x968 += (v2 != 0L) * (v2 == k)
          }
          x968
        }) + v)
    }
    CUSTDIST_mCUSTOMER1_E1_1.set(x757, ((CUSTDIST_mCUSTOMER1_E1_1.get(x757)) + x822))
    CUSTDIST_mCUSTOMER1_E1_3.set(x757, ((CUSTDIST_mCUSTOMER1_E1_3.get(x757)) + (x814 * -1L)))
  }
}

// -----------------------------------------------------------------------------

import scala.collection.JavaConversions.mapAsScalaMap
import java.util.HashMap
import org.dbtoaster.dbtoasterlib.K3Collection._

class TPCH13Ref extends Actor {
  import Messages._
  import scala.language.implicitConversions  
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  var t0:Long = 0
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"ORDERS",tx,List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onInsertORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",tx,List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDeleteORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",tx,List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onInsertCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",tx,List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDeleteCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,result.toMap)
  }

   val CUSTDIST = new K3PersistentCollection[(Long), Long]("CUSTDIST", new java.util.HashMap[(Long), Long], None) /* out */; // == x2
   val CUSTDIST_mORDERS1_E1_4 = new K3PersistentCollection[(Long), Long]("CUSTDIST_mORDERS1_E1_4", new java.util.HashMap[(Long), Long], None) /* out */; // ==x3
   val CUSTDIST_mCUSTOMER1_E1_1 = new K3PersistentCollection[(Long), Long]("CUSTDIST_mCUSTOMER1_E1_1", new java.util.HashMap[(Long), Long], None) /* out */; // ==CUSTDIST_mCUSTOMER1_E1_1 
   val CUSTDIST_mCUSTOMER1_E1_3 = new K3PersistentCollection[(Long), Long]("CUSTDIST_mCUSTOMER1_E1_3", new java.util.HashMap[(Long), Long], None) /* out */; // ==x5
   def result:Map[Long,Long] = CUSTDIST.elems.toMap

   def onInsertORDERS(x6: Long, x7: Long, x8: String, x9: Double, x10: Date, x11: String, x12: String, x13: Long, x14: String): Unit = {
      val x17 = CUSTDIST // mutable K3PersistentCollection
      val x18 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x19 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x20 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x21 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x22 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x23 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x19.foreach {
         x24 =>
            val x25 = x24._1
            val x33 = x19.lookup(x25, 0L)
            x23.updateValue(x33, ((x23.lookup(x33, 0L)) + ((x24._2) != 0L)))
      }
      x23.foreach {
         x44 =>
            val x45 = x44._1
            x22.updateValue(x45, ((x22.lookup(x45, 0)) + (x44._2)))
      }
      val x52 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x19.foreach {
         x53 =>
            val x54 = x53._1
            x52.updateValue(x54, ((x52.lookup(x54, 0)) + (x53._2)))
      }
      val x64 = if ((0L == (regexp_match("^.*special.*requests.*$", x14)))) {
         1L
      } else {
         0L
      }
      val x70 = x64 * (x18.lookup(x7, 0L))
      x52.updateValue(x7, ((x52.lookup(x7, 0)) + x70))
      val x75 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x52.foreach {
         x76 =>
            val x77 = x76._1
            val x85 = x19.lookup(x77, 0L)
            x75.updateValue(x85, ((x75.lookup(x85, 0L)) + ((x76._2) != 0L)))
      }
      x75.foreach {
         x96 =>
            val x97 = x96._1
            x22.updateValue(x97, ((x22.lookup(x97, 0)) + (x96._2)))
      }
      x22.foreach {
         x104 =>
            val x105 = x104._1
            x21.updateValue(x105, ((x21.lookup(x105, 0)) + ((x104._2) * -1L)))
      }
      val x114 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x19.foreach {
         x115 =>
            val x116 = x115._1
            x114.updateValue(x116, ((x114.lookup(x116, 0)) + (x115._2)))
      }
      x114.updateValue(x7, ((x114.lookup(x7, 0)) + x70))
      val x128 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x114.foreach {
         x129 =>
            val x130 = x129._1
            val x138 = x19.lookup(x130, 0L)
            x128.updateValue(x138, ((x128.lookup(x138, 0L)) + ((x129._2) != 0L)))
      }
      x128.foreach {
         x149 =>
            val x150 = x149._1
            x21.updateValue(x150, ((x21.lookup(x150, 0)) + (x149._2)))
      }
      val x157 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x19.foreach {
         x158 =>
            val x159 = x158._1
            x157.updateValue(x159, ((x157.lookup(x159, 0)) + (x158._2)))
      }
      x157.updateValue(x7, ((x157.lookup(x7, 0)) + x70))
      val x171 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x157.foreach {
         x172 =>
            val x173 = x172._1
            val x190 = (x19.lookup(x173, 0L)) + (((x7 == x173) * x64) * (x18.lookup(x7, 0L)))
            x171.updateValue(x190, ((x171.lookup(x190, 0L)) + ((x172._2) != 0L)))
      }
      x171.foreach {
         x201 =>
            val x202 = x201._1
            x21.updateValue(x202, ((x21.lookup(x202, 0)) + (x201._2)))
      }
      x21.foreach {
         x209 =>
            val x210 = x209._1
            x17.updateValue(x210, ((if ((x17.contains(x210))) {
               (x17.lookup(x210, 0))
            } else {
               var x215: Long = 0L
               x19.foreach {
                  x216 =>
                     val x217 = x216._1
                     x215 = ((x215) + (((x216._2) != 0L) * ((x19.lookup(x217, 0L)) == x210)))
               }
               (x215)
            }) + (x209._2)))
      }
      x19.updateValue(x7, ((x19.lookup(x7, 0L)) + x70))
      x20.updateValue(x7, ((x20.lookup(x7, 0L)) + x64))
      ()
   }

   def onDeleteCUSTOMER(x265: Long, x266: String, x267: String, x268: Long, x269: String, x270: Double, x271: String, x272: String): Unit = {
      val x275 = CUSTDIST // mutable K3PersistentCollection
      val x276 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x277 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x278 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x279 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x280 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x281 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x277.foreach {
         x282 =>
            val x283 = x282._1
            val x291 = x277.lookup(x283, 0L)
            x281.updateValue(x291, ((x281.lookup(x291, 0L)) + ((x282._2) != 0L)))
      }
      x281.foreach {
         x302 =>
            val x303 = x302._1
            x280.updateValue(x303, ((x280.lookup(x303, 0)) + (x302._2)))
      }
      val x310 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x277.foreach {
         x311 =>
            val x312 = x311._1
            x310.updateValue(x312, ((x310.lookup(x312, 0)) + (x311._2)))
      }
      val x325 = (x278.lookup(x265, 0L)) * -1L
      x310.updateValue(x265, ((x310.lookup(x265, 0)) + x325))
      val x330 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x310.foreach {
         x331 =>
            val x332 = x331._1
            val x340 = x277.lookup(x332, 0L)
            x330.updateValue(x340, ((x330.lookup(x340, 0L)) + ((x331._2) != 0L)))
      }
      x330.foreach {
         x351 =>
            val x352 = x351._1
            x280.updateValue(x352, ((x280.lookup(x352, 0)) + (x351._2)))
      }
      x280.foreach {
         x359 =>
            val x360 = x359._1
            x279.updateValue(x360, ((x279.lookup(x360, 0)) + ((x359._2) * -1L)))
      }
      val x369 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x277.foreach {
         x370 =>
            val x371 = x370._1
            x369.updateValue(x371, ((x369.lookup(x371, 0)) + (x370._2)))
      }
      x369.updateValue(x265, ((x369.lookup(x265, 0)) + x325))
      val x383 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x369.foreach {
         x384 =>
            val x385 = x384._1
            val x393 = x277.lookup(x385, 0L)
            x383.updateValue(x393, ((x383.lookup(x393, 0L)) + ((x384._2) != 0L)))
      }
      x383.foreach {
         x404 =>
            val x405 = x404._1
            x279.updateValue(x405, ((x279.lookup(x405, 0)) + (x404._2)))
      }
      val x412 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x277.foreach {
         x413 =>
            val x414 = x413._1
            x412.updateValue(x414, ((x412.lookup(x414, 0)) + (x413._2)))
      }
      x412.updateValue(x265, ((x412.lookup(x265, 0)) + x325))
      val x426 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x412.foreach {
         x427 =>
            val x428 = x427._1
            val x445 = (x277.lookup(x428, 0L)) + (((x265 == x428) * (x278.lookup(x265, 0L))) * -1L)
            x426.updateValue(x445, ((x426.lookup(x445, 0L)) + ((x427._2) != 0L)))
      }
      x426.foreach {
         x456 =>
            val x457 = x456._1
            x279.updateValue(x457, ((x279.lookup(x457, 0)) + (x456._2)))
      }
      x279.foreach {
         x464 =>
            val x465 = x464._1
            x275.updateValue(x465, ((if ((x275.contains(x465))) {
               (x275.lookup(x465, 0))
            } else {
               var x470: Long = 0L
               x277.foreach {
                  x471 =>
                     val x472 = x471._1
                     x470 = ((x470) + (((x471._2) != 0L) * ((x277.lookup(x472, 0L)) == x465)))
               }
               (x470)
            }) + (x464._2)))
      }
      x276.updateValue(x265, ((x276.lookup(x265, 0L)) + -1L))
      x277.updateValue(x265, ((x277.lookup(x265, 0L)) + x325))
   }

   def onInsertCUSTOMER(x512: Long, x513: String, x514: String, x515: Long, x516: String, x517: Double, x518: String, x519: String): Unit = {
      val x522 = CUSTDIST // mutable K3PersistentCollection
      val x523 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x524 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x525 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x526 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x527 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x528 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x524.foreach {
         x529 =>
            val x530 = x529._1
            val x538 = x524.lookup(x530, 0L)
            x528.updateValue(x538, ((x528.lookup(x538, 0L)) + ((x529._2) != 0L)))
      }
      x528.foreach {
         x549 =>
            val x550 = x549._1
            x527.updateValue(x550, ((x527.lookup(x550, 0)) + (x549._2)))
      }
      val x557 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x524.foreach {
         x558 =>
            val x559 = x558._1
            x557.updateValue(x559, ((x557.lookup(x559, 0)) + (x558._2)))
      }
      val x570 = x525.lookup(x512, 0L)
      x557.updateValue(x512, ((x557.lookup(x512, 0)) + x570))
      val x575 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x557.foreach {
         x576 =>
            val x577 = x576._1
            val x585 = x524.lookup(x577, 0L)
            x575.updateValue(x585, ((x575.lookup(x585, 0L)) + ((x576._2) != 0L)))
      }
      x575.foreach {
         x596 =>
            val x597 = x596._1
            x527.updateValue(x597, ((x527.lookup(x597, 0)) + (x596._2)))
      }
      x527.foreach {
         x604 =>
            val x605 = x604._1
            x526.updateValue(x605, ((x526.lookup(x605, 0)) + ((x604._2) * -1L)))
      }
      val x614 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x524.foreach {
         x615 =>
            val x616 = x615._1
            x614.updateValue(x616, ((x614.lookup(x616, 0)) + (x615._2)))
      }
      x614.updateValue(x512, ((x614.lookup(x512, 0)) + x570))
      val x628 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x614.foreach {
         x629 =>
            val x630 = x629._1
            val x638 = x524.lookup(x630, 0L)
            x628.updateValue(x638, ((x628.lookup(x638, 0L)) + ((x629._2) != 0L)))
      }
      x628.foreach {
         x649 =>
            val x650 = x649._1
            x526.updateValue(x650, ((x526.lookup(x650, 0)) + (x649._2)))
      }
      val x657 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x524.foreach {
         x658 =>
            val x659 = x658._1
            x657.updateValue(x659, ((x657.lookup(x659, 0)) + (x658._2)))
      }
      x657.updateValue(x512, ((x657.lookup(x512, 0)) + x570))
      val x671 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x657.foreach {
         x672 =>
            val x673 = x672._1
            val x689 = (x524.lookup(x673, 0L)) + ((x512 == x673) * (x525.lookup(x512, 0L)))
            x671.updateValue(x689, ((x671.lookup(x689, 0L)) + ((x672._2) != 0L)))
      }
      x671.foreach {
         x700 =>
            val x701 = x700._1
            x526.updateValue(x701, ((x526.lookup(x701, 0)) + (x700._2)))
      }
      x526.foreach {
         x708 =>
            val x709 = x708._1
            x522.updateValue(x709, ((if ((x522.contains(x709))) {
               (x522.lookup(x709, 0))
            } else {
               var x714: Long = 0L
               x524.foreach {
                  x715 =>
                     val x716 = x715._1
                     x714 = ((x714) + (((x715._2) != 0L) * ((x524.lookup(x716, 0L)) == x709)))
               }
               (x714)
            }) + (x708._2)))
      }
      x523.updateValue(x512, ((x523.lookup(x512, 0L)) + 1L))
      x524.updateValue(x512, ((x524.lookup(x512, 0L)) + x570))
   }

   def onDeleteORDERS(x756: Long, x757: Long, x758: String, x759: Double, x760: Date, x761: String, x762: String, x763: Long, x764: String): Unit = {
      val x767 = CUSTDIST // mutable K3PersistentCollection
      val x768 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x769 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x770 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x771 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x772 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x773 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x769.foreach {
         x774 =>
            val x775 = x774._1
            val x783 = x769.lookup(x775, 0L)
            x773.updateValue(x783, ((x773.lookup(x783, 0L)) + ((x774._2) != 0L)))
      }
      x773.foreach {
         x794 =>
            val x795 = x794._1
            x772.updateValue(x795, ((x772.lookup(x795, 0)) + (x794._2)))
      }
      val x802 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x769.foreach {
         x803 =>
            val x804 = x803._1
            x802.updateValue(x804, ((x802.lookup(x804, 0)) + (x803._2)))
      }
      val x814 = if ((0L == (regexp_match("^.*special.*requests.*$", x764)))) {
         1L
      } else {
         0L
      }
      val x822 = (x814 * (x768.lookup(x757, 0L))) * -1L
      x802.updateValue(x757, ((x802.lookup(x757, 0)) + x822))
      val x827 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x802.foreach {
         x828 =>
            val x829 = x828._1
            val x837 = x769.lookup(x829, 0L)
            x827.updateValue(x837, ((x827.lookup(x837, 0L)) + ((x828._2) != 0L)))
      }
      x827.foreach {
         x848 =>
            val x849 = x848._1
            x772.updateValue(x849, ((x772.lookup(x849, 0)) + (x848._2)))
      }
      x772.foreach {
         x856 =>
            val x857 = x856._1
            x771.updateValue(x857, ((x771.lookup(x857, 0)) + ((x856._2) * -1L)))
      }
      val x866 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x769.foreach {
         x867 =>
            val x868 = x867._1
            x866.updateValue(x868, ((x866.lookup(x868, 0)) + (x867._2)))
      }
      x866.updateValue(x757, ((x866.lookup(x757, 0)) + x822))
      val x880 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x866.foreach {
         x881 =>
            val x882 = x881._1
            val x890 = x769.lookup(x882, 0L)
            x880.updateValue(x890, ((x880.lookup(x890, 0L)) + ((x881._2) != 0L)))
      }
      x880.foreach {
         x901 =>
            val x902 = x901._1
            x771.updateValue(x902, ((x771.lookup(x902, 0)) + (x901._2)))
      }
      val x909 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x769.foreach {
         x910 =>
            val x911 = x910._1
            x909.updateValue(x911, ((x909.lookup(x911, 0)) + (x910._2)))
      }
      x909.updateValue(x757, ((x909.lookup(x757, 0)) + x822))
      val x923 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x909.foreach {
         x924 =>
            val x925 = x924._1
            val x943 = (x769.lookup(x925, 0L)) + ((((x757 == x925) * x814) * (x768.lookup(x757, 0L))) * -1L)
            x923.updateValue(x943, ((x923.lookup(x943, 0L)) + ((x924._2) != 0L)))
      }
      x923.foreach {
         x954 =>
            val x955 = x954._1
            x771.updateValue(x955, ((x771.lookup(x955, 0)) + (x954._2)))
      }
      x771.foreach {
         x962 =>
            val x963 = x962._1
            x767.updateValue(x963, ((if ((x767.contains(x963))) {
               (x767.lookup(x963, 0))
            } else {
               var x968: Long = 0L
               x769.foreach {
                  x969 =>
                     val x970 = x969._1
                     x968 = ((x968) + (((x969._2) != 0L) * ((x769.lookup(x970, 0L)) == x963)))
               }
               (x968)
            }) + (x962._2)))
      }
      x769.updateValue(x757, ((x769.lookup(x757, 0L)) + x822))
      x770.updateValue(x757, ((x770.lookup(x757, 0L)) + (x814 * -1L)))
   }
}
