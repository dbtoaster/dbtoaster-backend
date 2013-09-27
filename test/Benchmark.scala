package ddbt.test
import org.scalatest._
import java.io._

/**
 * This class compare execution time of different compilation options.
 * You can fix boost libraries path in conf/ddbt.properties by setting the
 * appropriate path for the key "ddbt.lib_boost".
 *
 * Arguments:
 *   -csv        : output the results in 'benchmark-<dataset>.csv'
 *   -d<dataset> : select exactly one dataset for benchmark
 *   -q<pattern> : queries filtering, any matching pattern will select the query
 *   -m<mode>    : add a benchmarked compiler mode (default=scala), modes are
 *                 - scala, lms, akka   : new compiler
 *                 - lscala, lcpp, llms : legacy dbtoaster
 *
 * Usage examples:
 *
 *    sbt 'test:run-main ddbt.test.Benchmark -qaxfinder -mscala -mlcpp -mlscala -mllms -dstandard -csv'
 *
 *    sbt 'test:run-main ddbt.test.Benchmark -csv -q.*axfinder.sql -dbig'
 *
 * @author TCK
 */

/** Automated tests */
class BenchmarkSpec extends FunSpec {
  import ddbt.UnitTest
  import ddbt.Utils._
  val tests = UnitTest.sqlFiles("standard")._2
  tests.filter{x=> !x.endsWith("missedtrades.sql")}.foreach { t =>
    val n = t.replaceAll(".*queries/|/query|\\.sql","")
    it ("Query "+n) {
      val (t0,m3) = ns(()=>UnitTest.toast(t,List("-l","M3")))
      info("SQL -> M3      : "+time(t0))
      val (_,o,e) = captureOut(()=>Benchmark.benchScala("scala")(m3,t0))
      o.trim.split("\n").foreach{ info(_) }
      if (e.trim!="") assert(false,e)
    }
  }
}

/** Actual configurable program */
object Benchmark {
  import ddbt.UnitTest
  import ddbt.Utils._
  import ddbt.frontend._
  import ddbt.codegen._

  val tmp = new java.io.File("tmp") //makeTempDir()
  private val boost = try { val p=new java.util.Properties(); p.load(new java.io.FileInputStream("conf/ddbt.properties")); p.getProperty("ddbt.lib_boost",null) } catch { case _:Throwable => null }
  private val path_dbt = if (path_repo!="") path_repo+"/"+path_base+"/" else ""
  private val scalac2 = { val dbt=path_dbt+"lib/dbt_scala/dbtlib.jar"; if (!new File(dbt).exists) sys.error("Cannot find the DBToaster Scala library"); scalaCompiler(tmp,dbt) }
  // New approach: run everything in the same JVM for speed, dependencies: scala-compiler
  def scalac(fs:String*) = scalac2(fs.map(f=>tmp.getAbsolutePath()+"/"+f+".scala").toList) 
  def scalax(cl:String) = loadMain(tmp,cl)._1
  //def scalax(cl:String) = { val args="-cp "+tmp.getAbsolutePath()+":"+path_cp+" "+cl // -J-verbose:gc
  //  try { exec("scala -J-Xss512m -J-Xmx2G "+args)._1 } catch { case _:IOException => exec(java_cmd+" "+args)._1 } }

  var dataset="standard"
  var modes = List[String]()
  var csv:PrintWriter = null

  // Merge argument parsing with unit test ?

  def main(args:Array[String]) {
    args.foreach { a => if (a.startsWith("-d")) dataset=a.substring(2) }
    val f_qs = { val ps = args.filter(_.startsWith("-q")).map(p=>java.util.regex.Pattern.compile(".*"+p.substring(2)+"(\\.sql)?"))
      if (ps.length>0) (s:String)=>ps.exists(p=>p.matcher(s).matches()) else (s:String)=>true
    }
    val tests = UnitTest.sqlFiles(dataset)._2.filter(f_qs)
    modes = args.filter(_.startsWith("-m")).map(_.substring(2)).filter(m=>m match { case "scala"|"lms"|"akka"|"lscala"|"llms"|"lcpp" => true case _ => false }).toList
    if (modes==Nil) modes = List("scala")
    if (args.contains("-csv")) {
      csv = new PrintWriter (new File ("benchmarks-"+dataset+".csv"));
      csv.println("Dataset,"+dataset+","+modes.map {
        case "scala" => "Scala"
        case "lms" => "LMS"
        case "akka" => "Akka"
        case "lscala" => "Scala-legacy"
        case "llms" => "LMS-legacy"
        case "lcpp" => "CPP-legacy"
      }.mkString(",,,,,"))
      csv.println("Query,SQLtoM3,"+modes.map(m=>"M3toCode,Compile,Min,Max,Median").mkString(","))
    }
    // run benchmarks
    if (modes.contains("lscala")||modes.contains("llms")) write(tmp,"RunQuery.scala",legacyHelper)
    tests.filter{x=> !x.endsWith("missedtrades.sql")}.foreach { t =>
      val n = t.replaceAll(".*queries/|/query|\\.sql","")
      println("--------------- "+n)
      val (t0,m3) = ns(()=>UnitTest.toast(t,List("-l","M3")))
      println("SQL -> M3      : "+time(t0))
      if (csv!=null) csv.print(n+","+time(t0,0)+",")
      modes.foreach {
        case "scala" => benchScala("scala")(m3,t0)
        case "lms" => benchScala("lms")(m3,t0)
        case "akka" => benchScala("akka")(m3,t0)
        case "lscala" => legacyScala(false)(t,t0)
        case "llms" => legacyScala(true)(t,t0)
        case "lcpp" => legacyCPP(t,t0)
      }
      if (csv!=null) csv.println
    }
    if (csv!=null) csv.close
  }

  def csvTime(t_gen:Long,t_comp:Long,t_run:String) { // SQL->Code,Compile,Running: avg [min, max]
    if (csv!=null) csv.print(time(math.max(0,t_gen),0)+","+time(t_comp,0)+","+t_run.replaceAll("^[^:]*: +|\\(sec\\)","").replaceAll(", +| +\\[|\\] +",","))
  }

  def benchScala(lang:String)(m3:String,t0:Long) {
    val (n,sp) = (lang.substring(0,1).toUpperCase+lang.substring(1)," "* (6-lang.length()))
    val gen:CodeGen = lang match {
      case "scala" => new ScalaGen("NewQuery")
      case "lms" => new LMSGen("NewQuery")
      case _ => scala.sys.error("Generator "+lang+" not supported")
    }
    val (t1,sc) = ns(()=>(M3Parser andThen TypeCheck andThen (x=>gen.helper(x)+gen(x)))(m3))
    println(n+" codegen"+sp+" : "+time(t1))
    write(tmp,"NewQuery.scala",(if (dataset.endsWith("_del")) sc.replaceAll("\\),Split\\(\\)",",\"add+del\""+"),Split()") else sc).replaceAll("/standard/","/"+dataset+"/"))
    val t2 = ns(()=>scalac("NewQuery"))._1
    println(n+" compile"+sp+" : "+time(t2))
    val s=scalax("ddbt.generated.NewQuery").split("\n")(0); println(s.replaceAll(".*:",n+" running"+sp+" : "))
    csvTime(t1,t2,s)
    if (csv!=null) csv.flush
  }

  def legacyScala(lms:Boolean)(t:String,t0:Long) {
    val (n,sp)=if (lms) ("LLMS","  ") else ("LScala","")
    val (t1,sc) = ns(()=> if (!lms) UnitTest.toast(t,List("-l","scala")) else {
      val f="tmp.scala"; UnitTest.toast(t,List("-l","scala","-O4","-o",f));
      val s=read(path_dbt+f); new File(path_dbt+f).delete;
      s.replaceAll("../../experiments/data",path_repo+"/dbtoaster/experiments/data")
    })
    println(n+" codegen"+sp+" : "+time(math.max(0,t1-t0)))
    write(tmp,"Query.scala",sc.replaceAll("/standard/","/"+dataset+"/"))
    val t2 = ns(()=>scalac("Query","RunQuery"))._1
    println(n+" compile"+sp+" : "+time(t2))
    val s = scalax("org.dbtoaster.RunQuery").split("\n")(0); println(s.replaceAll(".*:",n+" running"+sp+" :"))
    csvTime(t1-t0,t2,s)
    if (csv!=null) csv.flush
  }

  def legacyCPP(t:String,t0:Long) {
    val count = 10 // number of tests
    val (t1,cc) = ns(()=>UnitTest.toast(t,List("-l","cpp")))
    println("LCPP codegen   : "+time(t1))
    write(tmp,"query.hpp",cc.replaceAll("/standard/","/"+dataset+"/"))
    val pl = path_repo+"/"+path_base+"/lib/dbt_c++"
    val po = tmp.getPath+"/query"
    val as = List("g++",pl+"/main.cpp","-include",po+".hpp","-o",po,"-O3","-lpthread","-ldbtoaster","-I"+pl,"-L"+pl) :::
             List("program_options","serialization","system","filesystem","chrono","thread").map("-lboost_"+_) :::
             (if (boost==null) Nil else List("-I"+boost+"/include","-L"+boost+"/lib"))
    val t2 = ns(()=>exec(as.toArray))._1
    println("LCPP compile   : "+time(t2))
    def run() = exec(Array(po),null,if (boost!=null) Array("DYLD_LIBRARY_PATH="+boost+"/lib","LD_LIBRARY_PATH="+boost+"/lib") else null)._1
    val ts = (0 until 10).map(x=>ns(run)._1).sorted
    val s = "LCPP running   : "+time(ts(count/2))+" ["+time(ts(0),0)+", "+time(ts(count-1),0)+"] (sec)"; println(s)
    csvTime(t1-t0,t2,s)
  }

  private val legacyHelper =
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
    r.start
    RunQuery.synchronized { r.start; RunQuery.wait; }
    time
  }
  def time(ns:Long,n:Int=2) = { val us=ns/1000; "%d.%06d".format(us/1000000,us%1000000) }
  def main(args: Array[String]) {
    val count = 10
    val ts = (0 until count).map(x=>run1()).sorted
    println("Running      : "+time(ts(count/2))+" ["+time(ts(0),1)+", "+time(ts(count-1),1)+"] (sec)")
  }
}
"""
// ----------------------------------------------------------
}
