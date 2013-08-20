package ddbt.test
import org.scalatest._
import java.io._

/**
 * This class compare execution time of different compilation options.
 *
 * Arguments:
 *   -csv        : output the results in 'benchmark-<dataset>.csv'
 *   -d<dataset> : select exactly one dataset for benchmark
 *   -q<pattern> : queries filtering, any matching pattern will select the query
 *
 * Usage examples:
 *
 *    sbt 'test:run-main ddbt.test.Benchmark -csv -dstandard'
 * 
 * @author TCK
 */
object Benchmark {
  import ddbt.UnitTest
  import ddbt.Utils._
  import ddbt.frontend._
  import ddbt.codegen._

  // XXX: shall we do a 2-step process using SBT instead ?

  private val tmp = makeTempDir()
  def scalac(fs:String*) { val p=tmp.getAbsolutePath(); exec("fsc -cp target/scala-2.10/classes -d "+p+fs.map(f=>" "+p+"/"+f+".scala").mkString) }
  def scala(cl:String) = exec("scala -J-Xss512m -J-Xmx2G -cp target/scala-2.10/classes:"+tmp.getAbsolutePath()+" "+cl)._1 // -J-verbose:gc
  
  var dataset="standard"
  var csv:PrintWriter = null
  
  // XXX: split this into column-wise test that you execute one after another
  // this would improve composability to compare anything
  def scalaBench(t:String) {
    val n = t.replaceAll(".*queries/|\\.sql","")
    println("------- "+n)
    val (t0,m3) = ns(()=>UnitTest.toast(t,List("-l","M3")))
    println("SQL -> M3       : "+time(t0))
    val (t1,s1) = ns(()=>UnitTest.toast(t,List("-l","scala")))
    println("Old M3 -> Scala : "+time(math.max(0,t1-t0)))
    write(tmp,"Query.scala",s1.replaceAll("/standard/","/"+dataset+"/"))
    val (t2,s2) = ns(()=>(M3Parser andThen TypeCheck andThen ScalaGen("NewQuery"))(m3))
    println("New M3 -> Scala : "+time(t2))
    write(tmp,"NewQuery.scala",s2.replaceAll("/standard/","/"+dataset+"/"))
    val t3 = ns(()=>scalac("Query","RunQuery"))._1
    println("Old compile     : "+time(t3))
    val t4 = ns(()=>scalac("NewQuery"))._1
    println("New compile     : "+time(t4))
    val s3=scala("org.dbtoaster.RunQuery").split("\n")(0); println(s3)
    val s4=scala("ddbt.generated.NewQuery").split("\n")(0); println(s4)
    if (csv!=null) csv.println(n+","+time(t0,0)+","+time(math.max(0,t1-t0),0)+","+time(t2,0)+","+time(t3,0)+","+time(t4,0)+","+
                               (s3+s4).replaceAll("(Old|New)Gen : +|\\(sec\\)","").replaceAll(", +| +\\[|\\] +",","))
  }

  def main(args:Array[String]) {
    args.foreach { a => if (a.startsWith("-d")) dataset=a.substring(2) }
    val f_qs = { val ps = args.filter(_.startsWith("-q")).map(p=>java.util.regex.Pattern.compile(p.substring(2)))
      if (ps.length>0) (s:String)=>ps.exists(p=>p.matcher(s).matches()) else (s:String)=>true
    }
    val tests = UnitTest.sqlFiles(dataset)._2.filter(f_qs)
    
    if (args.contains("-csv")) {
      csv = new PrintWriter (new File ("benchmarks-"+dataset+".csv"));
      csv.println("Dataset,"+dataset)
      csv.println("Query,SQLtoM3,OldM3toScala,NewM3toScala,OldCompile,NewCompile,OldMedian,OldMin,OldMax,NewMedian,NewMin,NewMax")
    }
    // run benchmarks
    write(tmp,"RunQuery.scala",helper)

    tests.filter{x=> !x.endsWith("missedtrades.sql")}.foreach { t => scalaBench(t) }
    if (csv!=null) csv.close
  }

  private val helper =
// ----------------------------------------------------------
"""
package org.dbtoaster
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._
import org.dbtoaster.dbtoasterlib.QueryInterface._
object RunQuery {
  def run1() = {
    val q = new Query()
    var time : Long = 0
    val timeStart = System.nanoTime()
    val msgRcvr = new DBTMessageReceiver {
      def onTupleProcessed {}
      def onQueryDone {
        time = System.nanoTime()-timeStart
        RunQuery.synchronized { RunQuery.notifyAll }
      }
    }
    val r = new QuerySupervisor(q, msgRcvr)
    RunQuery.synchronized { r.start; RunQuery.wait; }
    time
  }
  def time(ns:Long) = { val ms=ns/1000000; "%d.%03d".format(ms/1000,ms%1000) }
  def main(args: Array[String]) {
    val count = 10
    val ts = (0 until count).map(x=>run1()).sorted
    println("OldGen : "+time(ts(count/2))+" ["+time(ts(0))+", "+time(ts(count-1))+"] (sec)")
  }
}
"""
// ----------------------------------------------------------

}

