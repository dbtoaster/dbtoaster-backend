package examples
import ddbt.lib._

import spark.SparkContext
import SparkContext._

import spark.RDD
import spark.HashPartitioner
import spark.Partitioner
import scala.reflect.ClassTag

// Idea: use a Partitioner to create buckets (?)
// http://ampcamp.berkeley.edu/wp-content/uploads/2012/06/matei-zaharia-amp-camp-2012-advanced-spark.pdf

object AXSpark {
  val sc = new SparkContext("local[4]", "Simple Job", "$YOUR_SPARK_HOME",
             List("target/scala-2.10/distributeddbtoaster_2.10-0.1.jar")) // Match SBT name/version

  // This is manually written for the moment, needs to go into ddbt.lib
  import scala.language.implicitConversions  
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  // new HashPartitioner(2)); // XXX: this might be a bad decision, but gives better perf locally
  /*
  object Part extends Partitioner {
    val N = 2
    def numPartitions = N
    def getPartition(key:(Long,Double)) = (key._1%20)
    def getPartition(key: Any):Int = key.hashCode()%N
  }
  */

  var AXFINDER = sc.parallelize(Seq[(Long,Double)]()) //.partitionBy(Part);
  var AXFINDER_mASKS1 = sc.parallelize(Seq[((Long,Double),Double)]()) //.partitionBy(Part);
  var AXFINDER_mASKS2 = sc.parallelize(Seq[((Long,Double),Long)]()) //.partitionBy(Part);
  var AXFINDER_mBIDS1 = sc.parallelize(Seq[((Long,Double),Long)]()) //.partitionBy(Part);
  var AXFINDER_mBIDS3 = sc.parallelize(Seq[((Long,Double),Double)]()) //.partitionBy(Part);

  var ctr:Int = 0
  def count { ctr=ctr+1; println("Events: "+ctr); }

  // Without merge: 24.74
  // With merge: 47.10

  def add[K:ClassTag](c:RDD[(K,Long)],k:K,v:Long):RDD[(K,Long)] = if (v==0) c
     else if (c.lookup(k).size>0) c.map{case (k0,v0) => (k0,if (k0==k) v0+v else v0) }
     else ( c ++ sc.parallelize(Seq((k,v))) )

  def add[K:ClassTag](c:RDD[(K,Double)],k:K,v:Double):RDD[(K,Double)] = if (v==0) c
     else if (c.lookup(k).size>0) c.map{case (k0,v0) => (k0,if (k0==k) v0+v else v0) }
     else ( c ++ sc.parallelize(Seq((k,v))) )

  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg1 = sc.accumulator(0L)
    AXFINDER_mBIDS1.foreach { case (k,v) => if (k._1==BIDS_BROKER_ID) { val A_PRICE = k._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg1 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    val agg4 = sc.accumulator(0.0)
    AXFINDER_mBIDS3.foreach { case (k,v) => if (k._1==BIDS_BROKER_ID) { val A_PRICE = k._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg4 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    AXFINDER = add(AXFINDER,BIDS_BROKER_ID,((agg1.value * -BIDS_VOLUME) + agg4.value));
    AXFINDER_mASKS1 = add(AXFINDER_mASKS1,(BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME);
    AXFINDER_mASKS2 = add(AXFINDER_mASKS2,(BIDS_BROKER_ID,BIDS_PRICE),1L);
    count
  }
  
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg7 = sc.accumulator(0L)
    AXFINDER_mBIDS1.foreach { case (k,v) => if (k._1==BIDS_BROKER_ID) { val A_PRICE = k._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg7 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    val agg10 = sc.accumulator(0.0)
    AXFINDER_mBIDS3.foreach { case (k,v) => if (k._1==BIDS_BROKER_ID) { val A_PRICE = k._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg10 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    AXFINDER = add(AXFINDER,BIDS_BROKER_ID,((agg7.value * BIDS_VOLUME) + (agg10.value * -1L)));
    AXFINDER_mASKS1 = add(AXFINDER_mASKS1,(BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME);
    AXFINDER_mASKS2 = add(AXFINDER_mASKS2,(BIDS_BROKER_ID,BIDS_PRICE),-1L);
    count
  }

  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val agg13 = sc.accumulator(0.0)
    AXFINDER_mASKS1.foreach { case (k,v) => if (k._1==ASKS_BROKER_ID) { val B_PRICE = k._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg13 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    val agg16 = sc.accumulator(0L)
    AXFINDER_mASKS2.foreach { case (k,v) => if (k._1==ASKS_BROKER_ID) { val B_PRICE = k._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg16 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    AXFINDER = add(AXFINDER,ASKS_BROKER_ID,((agg13.value * -1L) + (agg16.value * ASKS_VOLUME)));
    AXFINDER_mBIDS1 = add(AXFINDER_mBIDS1,(ASKS_BROKER_ID,ASKS_PRICE),1L);
    AXFINDER_mBIDS3 = add(AXFINDER_mBIDS3,(ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
    count
  }

  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    var agg19 = sc.accumulator(0.0)
    AXFINDER_mASKS1.foreach { case (k,v) => if (k._1==ASKS_BROKER_ID) { val B_PRICE = k._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg19 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    val agg22 = sc.accumulator(0L)
    AXFINDER_mASKS2.foreach { case (k,v) => if (k._1==ASKS_BROKER_ID) { val B_PRICE = k._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg22 += (v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }}
    AXFINDER = add(AXFINDER,ASKS_BROKER_ID,(agg19.value + (agg22.value * -ASKS_VOLUME)));
    AXFINDER_mBIDS1 = add(AXFINDER_mBIDS1,(ASKS_BROKER_ID,ASKS_PRICE),-1L);
    AXFINDER_mBIDS3 = add(AXFINDER_mBIDS3,(ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
    count
  }

  def dispatch(ev:TupleEvent):Unit = ev match {
    case TupleEvent(TupleInsert,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddBIDS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelBIDS(t,id,b,v,p)
    case TupleEvent(TupleInsert,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddASKS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelASKS(t,id,b,v,p)
  }

  // Run with
  //
  //   sbt ';package;run-main examples.AXSpark'
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

    AXFINDER.collect.foreach{ case (k,v) => println(k+" => "+v); }

    in.close()
    sc.stop

    val t = (t1-t0) / 1000
    println("Running time: %d.%06d".format(t/1000000,t%1000000))

  }
}

