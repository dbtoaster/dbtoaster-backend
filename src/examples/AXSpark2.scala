package examples
import ddbt.lib._

import spark.SparkContext
import SparkContext._
import spark.RDD
import scala.reflect.ClassTag

// Idea: use a Partitioner to create buckets (?)
// http://ampcamp.berkeley.edu/wp-content/uploads/2012/06/matei-zaharia-amp-camp-2012-advanced-spark.pdf

// Store hash maps instead of values within the sequences

import scala.collection.immutable.HashMap

case class KSMap[K,V](v0:V,idxs:List[KSIndex[_,K,V]]=Nil) {
  val elems = HashMap[K,V]()
  def plus(v1:V,v2:V) = (v1,v2) match { // manual type conversion required
    case (n1:Long,n2:Long) => (n1+n2).asInstanceOf[V]
    case (n1:Long,n2:Double) => (n1+n2).toLong.asInstanceOf[V]
    case (n1:Double,n2:Long) => (n1+n2).asInstanceOf[V]
    case (n1:Double,n2:Double) => (n1+n2).asInstanceOf[V]
    case _ => throw new Exception("No addition property")
  }
  // Public interface
  def contains(key:K) = elems.contains(key)
  def get(key:K) = elems.get(key) match { case None => v0 case Some(v)=>v }
  def set(key:K, value:V) : KSMap[K,V] = { val el0=elems; new KSMap[K,V](v0,idxs.map{ x=>x.set(key,value) }) { override val elems=el0+((key,value)) } }
  def add(key:K, value:V) : KSMap[K,V] = if (value==v0) this else elems.get(key) match {
    case None => set(key,value)
    case Some(vv) => val v1=plus(vv,value); if (v1!=v0) set(key,v1)
      else { val el0=elems; new KSMap[K,V](v0,idxs.map{ x=>x.del(key) }) { override val elems = el0 - key } }
  }
  def foreach(f:(K,V)=>Unit) = elems.foreach{ case (k,v)=>f(k,v) } 
  def slice[P](part:Int, partKey:P):KSMap[K,V] = {
    val ix=idxs(part); new KSSlice(elems,ix.asInstanceOf[KSIndex[P,K,V]].slice(partKey)) // type information P is erased anyway
  }
  class KSSlice(elems:HashMap[K,V], slice:HashMap[K,V]) extends KSMap[K,V](v0,idxs) {
    override def foreach(f:(K,V)=>Unit) = slice.foreach{ case (k,v)=>f(k,v) } 
  }
  // Debug
  def size = elems.size
  def dump = elems
}

class KSIndex[P,K,V](proj:K=>P) extends java.io.Serializable {
  val idx = HashMap[P,HashMap[K,V]]()
  def set(key:K,value:V) = {
    val p=proj(key); val idx0=idx
    idx.get(p) match {
      case Some(m) => new KSIndex[P,K,V](proj) { override val idx = idx0 + ((p, m + ((key,value)))) }
      case None => new KSIndex[P,K,V](proj) { override val idx = idx0 + ((p, HashMap(((key,value))))) }
    }
  }
  def del(key:K) = {
    val p=proj(key);
    idx.get(p) match {
      case Some(m) => m.get(key) match {
        case Some(v) => val idx0=idx; new KSIndex[P,K,V](proj) { override val idx = idx0 + ((p, ((m - key)))) }
        case None => this
      }
      case None => this
    }
  }
  def slice(part:P):HashMap[K,V] = idx.get(part) match { case Some(m) => m case None => HashMap[K,V]() }
}

// -----------------------------------------------------------------------------

object AXSpark2 {
  val sc = new SparkContext("local[8]", "Simple Job", "$YOUR_SPARK_HOME",
             List("target/scala-2.10/distributeddbtoaster_2.10-0.1.jar")) // Match SBT name/version

  // This is manually written for the moment, needs to go into ddbt.lib
  import scala.language.implicitConversions  
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  // XXX: bug do not appear if N=1
  val N = 16 // approximately #nodes x #cpus/nodes
  type Bulk[K,V] = RDD[(Int,KSMap[K,V])] // partition id, internal map

  def makeBulk[K,V](v0:V,projs:List[K=>_]=Nil) : Bulk[K,V] = {
    def idx[P](f:K=>P) = new KSIndex[P,K,V](f)
    sc.makeRDD((0 until N).map{x=>(x,new KSMap(v0,projs.map(idx(_))))},N)
  }

  // Pay attention to modulo for negative numbers
  def h(k:Any):Int = { val x = k.hashCode % N; (x + N) % N }

  def add[K,V](b:Bulk[K,V],k:K,v:V):Bulk[K,V] = b.map{ case (n,m) => if (h(k)==n) (n,m.add(k,v)) else (n,m) }

  var AXFINDER : Bulk[Long,Double] = makeBulk[Long,Double](0.0)
  var AXFINDER_mASKS1 : Bulk[(Long,Double),Double] = makeBulk[(Long,Double),Double](0.0,List((x:(Long,Double))=>x._1))
  var AXFINDER_mASKS2 : Bulk[(Long,Double),Long] = makeBulk[(Long,Double),Long](0L,List((x:(Long,Double))=>x._1))
  var AXFINDER_mBIDS1 : Bulk[(Long,Double),Long] = makeBulk[(Long,Double),Long](0L,List((x:(Long,Double))=>x._1))
  var AXFINDER_mBIDS3 : Bulk[(Long,Double),Double] = makeBulk[(Long,Double),Double](0.0,List((x:(Long,Double))=>x._1))

  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg1 = sc.accumulator(0L)
    AXFINDER_mBIDS1.foreach { case (n,m) => var lacc=0L
      m.slice(0,BIDS_BROKER_ID).foreach { case (k,v) => val A_PRICE = k._2;
        val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg1 += lacc
    }
    val agg4 = sc.accumulator(0.0)
    AXFINDER_mBIDS3.foreach { case (n,m) =>  var lacc = 0.0;
      m.slice(0,BIDS_BROKER_ID).foreach { case (k,v) => val A_PRICE = k._2;
        val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg4 += lacc
    }
    AXFINDER = add(AXFINDER,BIDS_BROKER_ID,((agg1.value * -BIDS_VOLUME) + agg4.value));
    AXFINDER_mASKS1 = add(AXFINDER_mASKS1,(BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME);
    AXFINDER_mASKS2 = add(AXFINDER_mASKS2,(BIDS_BROKER_ID,BIDS_PRICE),1L);
  }

  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg7 = sc.accumulator(0L)
    AXFINDER_mBIDS1.foreach { case (n,m) => var lacc=0L
      m.slice(0,BIDS_BROKER_ID).foreach { case (k,v) => val A_PRICE = k._2;
        val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg7 += lacc
    }
    val agg10 = sc.accumulator(0.0)
    AXFINDER_mBIDS3.foreach { case (n,m) => var lacc=0.0
      m.slice(0,BIDS_BROKER_ID).foreach { case (k,v) => val A_PRICE = k._2;
        val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg10 += lacc
    }
    AXFINDER = add(AXFINDER,BIDS_BROKER_ID,((agg7.value * BIDS_VOLUME) + (agg10.value * -1L)));
    AXFINDER_mASKS1 = add(AXFINDER_mASKS1,(BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME);
    AXFINDER_mASKS2 = add(AXFINDER_mASKS2,(BIDS_BROKER_ID,BIDS_PRICE),-1L);
  }

  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val agg13 = sc.accumulator(0.0)
    AXFINDER_mASKS1.foreach { case (n,m) => var lacc=0.0
      m.slice(0,ASKS_BROKER_ID).foreach { case (k,v) => val B_PRICE = k._2;
        val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg13 += lacc
    }
    val agg16 = sc.accumulator(0L)
    AXFINDER_mASKS2.foreach { case (n,m) => var lacc=0L
      m.slice(0,ASKS_BROKER_ID).foreach { case (k,v) => val B_PRICE = k._2;
        val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg16 += lacc
    }
    AXFINDER = add(AXFINDER,ASKS_BROKER_ID,((agg13.value * -1L) + (agg16.value * ASKS_VOLUME)));
    AXFINDER_mBIDS1 = add(AXFINDER_mBIDS1,(ASKS_BROKER_ID,ASKS_PRICE),1L);
    AXFINDER_mBIDS3 = add(AXFINDER_mBIDS3,(ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
  }

  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    var agg19 = sc.accumulator(0.0)
    AXFINDER_mASKS1.foreach { case (n,m) => var lacc=0.0
      m.slice(0,ASKS_BROKER_ID).foreach { case (k,v) => val B_PRICE = k._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg19 += lacc
    }
    val agg22 = sc.accumulator(0L)
    AXFINDER_mASKS2.foreach { case (n,m) => var lacc=0L
      m.slice(0,ASKS_BROKER_ID).foreach { case (k,v) => val B_PRICE = k._2;
        val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
        lacc += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
      }
      agg22 += lacc
    }
    AXFINDER = add(AXFINDER,ASKS_BROKER_ID,(agg19.value + (agg22.value * -ASKS_VOLUME)));
    AXFINDER_mBIDS1 = add(AXFINDER_mBIDS1,(ASKS_BROKER_ID,ASKS_PRICE),-1L);
    AXFINDER_mBIDS3 = add(AXFINDER_mBIDS3,(ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
  }

  def dispatch(ev:TupleEvent):Unit = ev match {
    case TupleEvent(TupleInsert,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddBIDS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelBIDS(t,id,b,v,p)
    case TupleEvent(TupleInsert,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddASKS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelASKS(t,id,b,v,p)
  }

  // Run with
  //
  //   sbt ';package;run-main examples.AXSpark2'
  //
  def main(args:Array[String]) {
    val d = Decoder(dispatch);
    // read all
    val bufSize:Int=128*1024
    val in = new java.io.FileInputStream("resources/data/finance.csv") // -standard
    // AXFinder
    // 33.064829 for standard
    // 1. accumulator avoids building intermediate filtered lists: -10 sec
    // 2. disabling log4j (echo 'log4j.rootLogger=OFF' > conf/log4j.properties): -5 sec
    // 3. Local tweak #cores workers, 2 paritions: -9 sec
    // CPS: 0.314622 for current implementation
    val buf = new Array[Byte](bufSize)
    var n:Int = 0

    val t0 = System.nanoTime()
    do { n=in.read(buf); d.add(buf,n); } while (n>0);
    val t1 = System.nanoTime()

    AXFINDER.collect.foreach { case (n,m) => m.foreach { case (k,v) => println(k+" => "+v); }}

    in.close()
    sc.stop

    val t = (t1-t0) / 1000
    println("Running time: %d.%06d".format(t/1000000,t%1000000))

  }
}

/*

AXFinderRef (0.063869)
0 => 7590.0
1 => 0.0
2 => -1395.0
3 => 95.0
4 => 0.0
5 => 1080.0
6 => 490.0
7 => -907.0
8 => 2419.0
9 => 45.0

AXFinder (0.010786)
0 => 7590.0
2 => -1395.0
3 => 95.0
5 => 1080.0
6 => 490.0
7 => -907.0
8 => 2419.0
9 => 45.0

AXSpark (47.074355)
0 => 7590.0
1 => 0.0
2 => -1395.0
3 => 95.0
5 => 1080.0
6 => 490.0
7 => -907.0
8 => 2419.0
9 => 45.0

AXSpark2 (2.811278)
0 => 3890.0
1 => 70.0
2 => -1395.0 <== OK
3 => -5.0
5 => 1080.0 <== OK
7 => -769.0
8 => 1310.0
9 => 45.0 <== OK

*/


