package ddbt
import java.io._

/**
 * Benchmarking and correctness verification generator. Instruments the
 * compiler such that options can be shared. To get more information:
 *
 * Usage: sbt 'run-main ddbt.UnitTest -help'
 *
 * @author TCK
 */
object UnitTest {
  def med(ts:Seq[Long]) = if (ts.size==0) 0L else { val s=ts.sorted; val n=ts.size; if (n%2==0) (s(n/2)+s(n/2-1))/2 else ts(n/2) }

  import Utils._
  val path_examples = "examples/queries"
  val path_sources = "test/gen"
  val path_classes = "target/scala-2.10/test-classes"
  val path_cache = "target/m3"
  val skip = List("11","11a","12","52","53","56","57","58","62","63","64","65","66","66a", // front-end failure (SQL constructs not supported)
                  "15", // regular expressions not supported by front-end: LIKE 'S____' ==> "^S____$" where "^S....$" is expected
                  "35b","36b").map("employee/query"+_) ::: // front-end swaps table order in JOIN .. ON, test (and Scala typing) fails
             List("mddb/query3","chrissedtrades") // too long to compile, incorrect result
             // Also TPCH11c is incorrect with -O3 (front-end) option
  var csv:PrintWriter = null
  var csvFile:String = null
  var dump:PrintWriter = null
  var dumpFile:String = null
  var tmp = makeTempDir() //(auto_delete=false)
  var cache = true      // cache is enabled
  var benchmark = false // enable benchmarks
  var samples = 10      // number of samples to take in the benchmark
  var warmup = 0        // number of warm-up transients to remove
  var timeout = 0L      // test duration timeout (milliseconds)
  var verify = false    // enforce correctness verification in benchmark
  var parallel = 0      // parallel streams mode
  var zeus = false      // zeus mode
  var seed = 0          // zeus seed
  var modes = List[String]() // selected modes
  var datasets = List[String]() // selected datasets
  var q_f = (s:String)=>true // query filter (sql file name)

  def parseArgs(args:Array[String]) {
    import scala.collection.mutable.{Set=>MSet}
    val qinc=MSet[String](); val qexcl=MSet[String](); var qfail=false
    var i=0; val l=args.length; var as=List[String]()
    def eat(f:String=>Unit,s:Boolean=false) { i+=1; if (i<l) f(if(s) args(i).toLowerCase else args(i)) }
    while(i<l) { args(i) match {
      case "-d" => eat(s=>if(!datasets.contains(s)) datasets=datasets:+s,true)
      case "-dd"=> val ds=List("tiny","tiny_del","standard","standard_del"); datasets=ds:::datasets.filter(!ds.contains(_))
      case "-m"|"-l" => eat(s=>if(!modes.contains(s)) modes=modes:+s,true)
      case "-q" => eat(s=>qinc+=s)
      case "-qx" => eat(s=>qexcl+=s)
      case "-qfail" => qfail=true
      case "-x" => benchmark=true
      case "-v" => verify=true
      case "-p" => eat(s=>parallel=s.toInt)
      case "-z" => zeus=true
      case "-seed" => eat(s=>seed=s.toInt)
      case "-s" => eat(s=>samples=s.toInt)
      case "-w" => eat(s=>warmup=s.toInt)
      case "-t" => eat(s=>timeout=s.toLong)
      case "-csv" => eat(s=>csvFile=s)
      case "-dump" => eat(s=>dumpFile=s)
      case "-nocache" => cache=false
      case "-h"|"-help"|"--help" => import Compiler.{error=>e}
        e("Usage: Unit [options] [compiler options]")
        e("Zeus mode:")
        e("  -z            enable zeus mode")
        e("  -s <n>        number of samples to test (default: 10, 0=infinite)")
        e("  -seed <int>   set the seed to test (implies 1 sample)")
        e("Filtering options:")
        e("  -d <dataset>  add a dataset: tiny, standard, big, huge (_del)?")
        e("  -dd           add tiny,tiny_del,standard,standard_del datasets")
        e("  -m <mode>     add mode: scala, lms, akka (_spec|_full|_0-10)?")
        e("                          lscala, lcpp, llms")
        e("  -q <filter>   add an inclusion filter for queries")
        e("  -qx <filter>  add an exclusion filter for queries")
        e("  -qfail        also include queries that are known to fail")
        e("Benchmarking options:")
        e("  -x            enable benchmarks (compile and execute)")
        e("  -v            verification against reference result") // consistency verification is always enabled
        e("  -p <mode>     parallel streams (0=off, 1=thread, 2=deterministic)")
        e("  -s <n>        number of samples to take (default: 10)")
        e("  -w <n>        number of warm-up transients (default: 0)")
        e("  -t <ms>       test duration timeout (in ms, default: 0)")
        e("  -csv <file>   store benchmark results in a file")
        e("  -dump <file>  dump raw benchmark samples in a file")
        e("  -nocache      disable M3 cache")
        e("")
        e("Other options are forwarded to the compiler:")
        Compiler.parseArgs(Array[String]())
      case s => as=s::as
    }; i+=1 }
    if (datasets.size==0) datasets=List("standard"); if (modes.size==0) modes=List("scala")
    if ((modes.toSet&Set("lscala","lcpp","llms")).size>0 && !benchmark) warning("Legacy modes are meaningful only with benchmarks enabled")
    def re(set:MSet[String]) = java.util.regex.Pattern.compile(".*("+set.mkString("|")+")(\\.sql)?")
    if (qinc.size>0) { val pi=re(qinc); q_f=(s:String)=>pi.matcher(s).matches }
    if (qexcl.size>0) { val px=re(qexcl); val q0=q_f; q_f=(s:String)=> q0(s) && !px.matcher(s).matches }
    if (!qfail) { val q0=q_f; println("Front-end skip : %4d".format(skip.size)); q_f=(s:String)=> !skip.exists(e=>s.endsWith(e+".sql")) && q0(s) }
    Compiler.in=List(""); Compiler.parseArgs(as.reverse.toArray)
  }

  private def tf(ns:Long) = "%7s".format(time(ns,false))

  def name(f:String) = { val s=f.replaceAll("tmp/|test/queries/|finance/|simple/|/query|.sql|[/_]",""); (s(0)+"").toUpperCase+s.substring(1) }
  def main(args:Array[String]) {
    parseArgs(args)
    // Zeus mode
    if (zeus) { genZeus; return; }
    // Regular mode
    val sel = all.filter(q=>q_f(q.sql)).map{ q=> QueryTest(q.sql,q.sets.filterKeys(datasets.contains(_))
                                                    .filterKeys{d=>q.sql.indexOf("missedtrades")== -1 || d.matches("tiny.*")}) // missedtrades is very slow
    }.filter(q=>q.sets.size>0)
    println("Tests total    : %4d".format(all.size))
    println("Tests selected : %4d".format(sel.size))
    if (sel.size==0) { System.err.println("No tests selected, exiting."); return; }
    val dir = new File(path_sources); if (dir.isDirectory()) dir.listFiles().foreach { f=>f.delete() } else dir.mkdirs() // directory cleanup (erase previous tests)
    if (csvFile!=null) csv=new PrintWriter(new File (csvFile+(if(csvFile.endsWith(".csv")) "" else ".csv")))
    if (dumpFile!=null) { dump=new PrintWriter(new File (dumpFile)); dump.println("Mode,Dataset,Time,Processed,Skipped") }
    def mn(s:String) = (s(0)+"").toUpperCase+s.substring(1)

    if (csv!=null) { // CSV format: query,sql->m3,(codegen,compile,(med,min,max,)*)*
      csv.print("s"+samples+"_w"+warmup+"_t"+timeout+",,"); for (m<-modes) csv.print(mn(m)+",,"+datasets.map(d=>d+",,,,,,,,,").mkString); csv.println
      csv.print("Query,SQLtoM3,"); for (m<-modes) csv.print("M3toCode,Compile,"+datasets.map(d=>"MedT,MedN,_,MinT,MinN,_,MaxT,MaxN,_,").mkString); csv.println
    }

    if (cache) new File(path_cache).mkdirs;
    for (q <- sel) {
      println("---------[[ "+name(q.sql)+" ]]---------")
      val (t0,m3) = {
        val f = "target/m3/"+name(q.sql)+".m3"
        if (cache && new File(f).exists) ns(()=>Utils.read(f))
        else {
          val r=Compiler.toast("m3",q.sql); Utils.write(f,r._2);
          println("SQL -> M3           : "+tf(r._1))
          r
        }
      }
      ;
      if (csv!=null) csv.print(name(q.sql)+","+time(t0)+",")
      ;
      for (m <- modes) m match {
        case "lscala"|"llms" if (repo!=null && benchmark) => ;legacyScala(q,new Printer(if(m=="llms") "LLMS" else "LScala"),t0,m=="llms")
        case "lcpp" if (repo!=null && benchmark) => legacyCPP(q,new Printer("LCPP"),t0)
        case _ => genQuery(q,new Printer(mn(m)),m3,m)
      }
      if (csv!=null) csv.println
      System.gc
    }
    if (csv!=null) csv.close
    if (dump!=null) dump.close
    if (!benchmark) println("Now run 'test-only ddbt.test.gen.*' to pass tests")

    // XXX: Untested mode (execute non-tested queries)
    // XXX: option for HTML report with bar graphs?
    // XXX: Use tags to filter test sizes in ScalaTest
    // XXX: use sbt ';reload;pkg;exec ddbt.test.gen.Axfinder -n10' to execute Akka distributed tests
  }

  // ---------------------------------------------------------------------------
  // Zeus mode
  def genZeus {
    val num=if(seed!=0) 1 else samples; samples=1; warmup=0; timeout=0; benchmark=true
    var i=0; while(i<num) { i+=1
      val sql = exec("scripts/zeus.rb"+(if (seed!=0) " -s "+seed else ""))._1.replaceAll("@@DATA@@",path_repo+"/../../experiments/data/simple/tiny")
      val ma = java.util.regex.Pattern.compile("^-- seed *= *([0-9]+).*").matcher(sql.split("\n")(0))
      val id = if (ma.matches) ma.group(1).toLong else sys.error("No seed")
      println("---------[[ Zeus "+id+" ]]---------")
      val f=tmp+"/zeus"+id+".sql";
      val m3={ write(f,sql); Compiler.in=List(f); Compiler.toast("m3")._2 }
      genQuery(QueryTest(f),new Printer("Scala"),m3,"scala")
    }
  }

  // ---------------------------------------------------------------------------
  // Query generator
  def genQuery(q:QueryTest,p:Printer,m3:String,mode:String,genSpec:Boolean=true) {
    val cls = name(q.sql)
    var sp=""
    // Correctness
    def spec(sys:ddbt.ast.M3.System,full:Boolean=true) = {
      val qid = sys.queries.map{_.name}.zipWithIndex.toMap
      val qt = sys.queries.map{q=>(q.name,sys.mapType(q.map.name)) }.toMap
      val body = "import scala.language.implicitConversions\n"+
      "implicit def dateConv(d:Long) = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime;\n"+
      "implicit def strConv(d:Long) = \"\"+d\n"+ // fix for TPCH22
      q.sets.map { case (sz,set) =>
        (if (full) cls+"." else "")+"execute(Array(\"-n1\",\"-m0\",\"-d"+sz+"\"),(res:List[Any])=>"+(if (full) "describe(\"Dataset '"+sz+"'\") " else "")+"{\n"+ind(
        set.out.map { case (n,o) => val (kt,vt) = qt(n); val qtp = "["+tup(kt.map(_.toScala))+","+vt.toScala+"]"
          val kv = if (kt.size==0) "" else { val ll=(kt:::vt::Nil).zipWithIndex; "def kv(l:List[Any]) = l match { case List("+ll.map{case (t,i)=>"v"+i+":"+t.toScala}.mkString(",")+") => ("+tup(ll.init.map{ case (t,i)=>"v"+i })+",v"+ll.last._2+") }\n" }
          val cmp = "diff(res("+qid(n)+").asInstanceOf["+(if(kt.size>0) "Map"+qtp else vt.toScala)+"], "+(o match {
            case QueryMap(m) => "Map"+qtp+"("+m.map{ case (k,v)=> "("+k+","+v+")" }.mkString(",")+")"// inline in the code
            case QueryFile(path,sep) => "loadCSV"+qtp+"(kv,\""+path_repo+"/"+path+"\",\""+(kt:::List(vt)).mkString(",")+"\""+(if (sep!=null) ",\"\\\\Q"+sep.replaceAll("\\\\\\|","|")+"\\\\E\"" else "")+")"
            case QuerySingleton(v) => v
          })+")"
          (if (full) "it(\""+n+" correct\") " else "")+"{\n"+ind(kv+cmp)+"\n}"
        }.mkString("\n"))+"\n})"
      }.mkString("\n")
      if (full) "import org.scalatest._\n\n"+
      "class "+cls+"Spec extends FunSpec {\n"+ind("import Helper._\n"+body)+"\n}\n" else body
    }
    def inject(pre:String,str:String,dir:String=null) { val src=read(tmp.getPath+"/"+cls+".scala").split("\\Q"+pre+"\\E"); write((if (dir!=null) dir else tmp)+"/"+cls+".scala",src(0)+pre+str+src(1)) }
    def post(sys:ddbt.ast.M3.System) { sp=spec(sys,true); if (verify) inject("  def main(args:Array[String]) {\n",ind(spec(sys,false),2)+"\n") }
    // Benchmark (and codegen)
    val m=mode.split("_"); // Specify the inlining as a suffix of the mode
    Compiler.inl = if (m.length==1) 0 else if (m(1)=="spec") 5 else if (m(1)=="full") 10 else try { m(1).toInt } catch { case _:Throwable => 0 }
    Compiler.lang = m(0)
    Compiler.name = cls
    Compiler.pkg = "ddbt.test.gen"
    Compiler.out = tmp.getPath+"/"+cls+".scala"
    Compiler.exec = benchmark
    Compiler.exec_dir = path_classes
    Compiler.exec_args = "-n"+(samples+warmup) :: "-t"+timeout :: "-p"+parallel :: "-m1" :: datasets.filter(d=>q.sets.contains(d)).map(d=>"-d"+d).toList
    p.run(()=>Compiler.compile(m3,post,p.gen,p.comp))
    p.close
    // Append correctness spec and move to test/gen/
    if (genSpec) inject("import java.util.Date\n",sp,path_sources)
  }

  // ---------------------------------------------------------------------------
  // Legacy testing
  private var legacySC:List[String]=>Unit = null
  def legacyScala(q:QueryTest,p:Printer,t0:Long,lms:Boolean=false) {
    val libs = (if (path_repo!=null) path_repo+"/" else "")+"lib/dbt_scala/dbtlib.jar"
    if (legacySC==null) {
      legacySC=scalaCompiler(tmp,libs,Compiler.exec_sc)
      write(tmp+"/RunQuery.scala","package org.dbtoaster\n"+
      "import org.dbtoaster.dbtoasterlib.DBToasterExceptions._\n"+
      "import org.dbtoaster.dbtoasterlib.QueryInterface._\n"+
      "object RunQuery {\n"+
      "  def run1(set:String,p:Int,timeout:Long) = {\n"+
      "    val to = timeout * 1000000L;\n"+
      "    val q = new Query(); var time=0L; val t0=System.nanoTime; var tN=0L; var tS=0L;\n"+
      "    val msgRcvr = new DBTMessageReceiver {\n"+
      "      def onTupleProcessed { "+(if (timeout==0) "tN+=1" else "if (q.skip) tS+=1; else tN+=1; if(to>0 && (tN & 0xf)==0) { val t=System.nanoTime-t0; if(t>to) { time=t; q.skip=true } }")+" }\n"+
      "      def onQueryDone { if (tS==0) time=System.nanoTime-t0; RunQuery.synchronized { RunQuery.notifyAll } }\n"+
      "    }\n"+
      "    val r = new QuerySupervisor(q, msgRcvr); RunQuery.synchronized { r.start; RunQuery.wait; }\n"+
      "    (ddbt.lib.Messages.StreamStat(time,tN,tS),Nil)\n"+
      "  }\n"+
      "  def main(args: Array[String]) = ddbt.lib.Helper.bench(args,run1)\n}\n")
    }
    var (t1,sc) = if (!lms) Compiler.toast("scala",q.sql) else {
      val f="tmp.scala"; val (t1,_) = Compiler.toast("scala","-O4","-o",f,q.sql);
      val fl=if (repo!=null) new File(repo,f) else new File(f); val s=read(fl.getPath); fl.delete;
      (t1,s.replaceAll("../../experiments/data",path_repo+"/../../experiments/data"))
    }
    if (timeout>0) sc=sc.replaceAll("(case StreamEvent.*=>)","$1 if (!skip)").replace("def act(): Unit","var skip = false;\n    def act(): Unit")
    p.gen(math.max(0,t1-t0))
    p.all(q){dataset=> write(tmp+"/Query.scala",{ val res = sc.replaceAll("/standard/","/"+dataset+"/"); if(dataset.contains("_del")) res.replace(", delimiter = \"\\\\|\")", ", deletions = \"true\", delimiter = \"\\\\|\")") else res })
      val t2 = ns(()=>legacySC(List(tmp.getPath+"/Query.scala",tmp.getPath+"/RunQuery.scala")))._1; p.comp(t2)
      val args = Array("-n"+(samples+warmup),"-m1","-t"+timeout,"-d"+dataset)
      p.run(()=>scalaExec(tmp :: libs.split(":").map(new File(_)).toList,"org.dbtoaster.RunQuery",args,Compiler.exec_vm))
    }
  }

  def legacyCPP(q:QueryTest,p:Printer,t0:Long) {
    val boost = prop("lib_boost",null)
    val (t1,cc) = Compiler.toast("cpp",q.sql); p.gen(math.max(0,t1-t0))
    p.all(q){dataset=>
      write(tmp+"/query.hpp", {
        def tc(p:String="") = "gettimeofday(&("+p+"t),NULL); "+p+"tT=(("+p+"t).tv_sec-("+p+"t0).tv_sec)*1000000L+(("+p+"t).tv_usec-("+p+"t0).tv_usec);"
        val res=cc.replaceAll("/standard/","/"+dataset+"/")
                .replaceAll("tlq_t().*\n +\\{\\}","struct timeval t0,t; long tT,tN,tS; tlq_t() { tN=0; tS=0; gettimeofday(&t0,NULL); }")
                .replaceAll("(BEGIN_TRIGGER.*\n +\\{)","$1 "+(if (timeout>0) "if (tS>0) { ++tS; return; } if (tN%100==0) { "+tc()+" if (tT>"+(timeout*1000L)+"L) { tS=1; return; } }" else "")+" ++tN;")
                .replaceAll("(snapshot_t take_snapshot\\(\\)\\{)","$1 tlq_t d=(tlq_t&)data; if (d.tS==0) { "+tc("d.")+" } printf(\"SAMPLE="+dataset+",%ld,%ld,%ld\\\\n\",d.tT,d.tN,d.tS);")
        if(dataset.contains("_del")) res.replace("make_pair(\"schema\",\"", "make_pair(\"deletions\",\"true\"), make_pair(\"schema\",\"").replace("\"),2,", "\"),3,") else res
      })
      val pl = path_repo+"/lib/dbt_c++"
      val po = tmp.getPath+"/query"
      val as = List("g++",pl+"/main.cpp","-include",po+".hpp","-o",po,"-O3","-lpthread","-ldbtoaster","-I"+pl,"-L"+pl) :::
               List("program_options","serialization","system","filesystem","chrono","thread").map("-lboost_"+_) ::: // thread-mt
               (if (boost==null) Nil else List("-I"+boost+"/include","-L"+boost+"/lib"))
      val t2 = ns(()=>exec(as.toArray))._1; p.comp(t2)
      p.run(()=>{ var i=0; while (i<warmup+samples) { i+=1
        val (out,err)=exec(Array(po),null,if (boost!=null) Array("DYLD_LIBRARY_PATH="+boost+"/lib","LD_LIBRARY_PATH="+boost+"/lib") else null)
        if (err!="") System.err.println(err); println(out)
      }})
    }
  }

  // ---------------------------------------------------------------------------
  // Common helpers
  private val repo = if (path_repo!=null) new File(path_repo) else null
  val all = if (repo!=null) exec(Array("find","test/unit/queries","-type","f","-and","-not","-path","*/.*"),repo)._1.split("\n").sorted.map(x=>UnitParser(read(repo.getPath+"/"+x)))
            else if (!new java.io.File(path_examples).exists) { warning("folder '"+path_examples+"' does not exist, tests skipped !"); Array[QueryTest]() }
            else exec(Array("find",path_examples,"-name","*.sql","-and","-not","-name","schemas.sql"))._1.split("\n").sorted.map(f=>QueryTest(f))
  // Helper for other tests
  def sqlFiles(valid:Boolean=true) = { val qs=all.map(q=>q.sql); if (valid) qs.filter(s=> !skip.exists(e=>s.endsWith(e+".sql"))) else qs }

  // Helper for displaying information and emitting a CSV file
  case class Sample(us:Long,count:Long,skip:Long) extends Ordered[Sample] {
    override def toString = { (us/1000000L)+".%06d".format(us%1000000L)+","+count+","+skip+"," } // CSV format
    def compare(s:Sample) = { val (a,b) = (count*s.us,s.count*us); if (a<b) -1 else if (a>b) 1 else 0 }
    def t = { val ms=math.round(us/1000.0); "%d.%03d".format(ms/1000,ms%1000) } // time in seconds
    def f = { val tps=if (us==0) 0 else count*1000000.0/us; val t=math.round(tps*10); "%d.%01d".format(t/10,t%10) } // frequency in views/sec
  }
  class Printer(name:String) {
    private val (c0,s0)=(scala.Console.out,System.out)
    @inline private def pr(op:String,s:String,c:Boolean=false) = { c0.println("%-70s".format("%-20s".format(name+" "+op)+": "+s)); if (c) c0.print("\033[F"+"[info] "); c0.flush; s0.flush } // assumes terminal + SBT
    @inline private def add(s:String=",,,,,,,,,") { tr+=s; ds+=1 }
    var tg=Seq[Long](); var tc=Seq[Long](); var tr=""; var ds=0;
    def gen(t:Long) { pr("codegen",tf(t)); tg=tg:+t; }
    def comp(t:Long) { pr("compile",tf(t)); tc=tc:+t; }
    def run(f:()=>Unit) {
      val (r,o) = { val p=new PipedOutputStream; (new BufferedReader(new InputStreamReader(new PipedInputStream(p))),new PrintStream(p)) }
      var w=0; var dn=""; var ts=List[Sample]();
      val t = new Thread { override def run { var l=r.readLine; while(l!=null) { if (l.startsWith("SAMPLE=")) { val d=l.trim.substring(7).split(",")
        if (dump!=null) { dump.println(name+","+l.trim.substring(7)); dump.flush }
        if (d(0)!=dn) { w=0; ts=Nil; dn=d(0) }
        if (w<warmup) { w+=1; pr(d(0),"  "+("."*w),true) }
        else {
          ts = (Sample(d(1).toLong,d(2).toLong,d(3).toLong) :: ts).sorted
          val n=ts.size; val m=ts(n/2);
          val med = if (n%2==1) m else { val b=ts(n/2-1); Sample((m.us+b.us)/2,(m.count+b.count)/2,(m.skip+b.skip+1)/2) } // if 1 skip, result must skip
          val (min,max) = (ts(0),ts(n-1))
          val abs_time = min.skip==0 && med.skip==0 && max.skip==0
          pr(d(0),(if (abs_time) "%7s".format(med.t)+" ["+max.t+", "+min.t+"] (" else med.f+" ["+min.f+", "+max.f+"] (views/sec, ")+""+ts.size+(if (ts.size<samples) "/"+samples else "")+" samples)",n<samples)
          if (ts.size==samples) { while (ds<datasets.size && d(0)!=datasets(ds)) add(); add(""+med+min+max) }
        }
      }; l=r.readLine }}}
      t.start; try { scala.Console.setOut(o); System.setOut(o); f() } finally { scala.Console.setOut(c0); System.setOut(s0); o.close }; t.join
    }
    def all(q:QueryTest)(f:String=>Unit) { datasets.foreach { d=> if (!q.sets.contains(d)) add() else f(d) }; close }
    def close { while (ds<datasets.size) add(); var s=time(med(tg))+","+time(med(tc))+","+tr; if (csv!=null) { csv.print(s); csv.flush } }
  }

  // ---------------------------------------------------------------------------
  // AST of query unit tests
  case class QueryTest(sql:String,sets:Map[String,QuerySet]=Map(("standard",QuerySet()))) { override def toString = sql+ind(sets.map{case (k,v)=>"\n - "+k+": "+v.out.toString}.mkString) }
  case class QuerySet(subs:List[(String,String)]=Nil,out:Map[String,QueryOut]=Map())
  abstract sealed class QueryOut
  case class QueryMap(m:Map[String,String]) extends QueryOut
  case class QueryFile(path:String,sep:String=null) extends QueryOut
  case class QuerySingleton(v:String) extends QueryOut

  // Parser for unit tests declarations
  import scala.util.parsing.combinator.RegexParsers
  object UnitParser extends RegexParsers {
    lazy val str = "\"" ~> """(\\.|[^\"])*""".r <~ "\"" | "'" ~> """(\\.|[^'])*""".r <~ "'"
    lazy val num = "-?[0-9]+(\\.[0-9]*)?([eE][\\-+]?[0-9]+)?".r ^^ { case x => if (x.matches("^-?[0-9]+$")) x+"L" else x }
    lazy val pat = "/" ~> """(\\.|[^/])*""".r <~ "/" ^^ { x=>x.replaceAll("\\\\/","/") } // might need a better solution
    private def map[T](p:Parser[T]) = "{" ~> repsep((str <~ "=>") ~ p,",") <~ "}" ^^ { case rs => rs.map{case n~v=>(n,v)}.toMap } // JSON-like map String -> T
    lazy val qtest = ("{" ~> ":path" ~> "=>" ~> str <~ ",") ~ (":datasets" ~> "=>" ~> map(qset) <~ "}") ^^ { case n~qs => QueryTest(n,qs) }
    lazy val qset = "{" ~> opt(":subs" ~> "=>" ~> "[" ~> repsep(qsub,",") <~ "]" <~ ",") ~ (":toplevels" ~> "=>" ~> map(qout)) <~ "}" ^^ { case ss ~os => QuerySet(ss match { case Some(s)=>s case None=>Nil },os) }
    lazy val qsub = ("[" ~> pat <~ ",") ~ (str <~ "]") ^^ { case p~r => (p,r) }
    lazy val qout = "{"~>":type"~>"=>"~>((":onelevel"~>","~>":expected"~"=>"~>(qfile|qmap)) | (":singleton"~>","~>":expected"~>"=>"~>num ^^ { case n => QuerySingleton(n) })) <~ opt(",") <~"}" ^^ { case q => q }
    lazy val qfile:Parser[QueryOut] = ("results_file" ~> "(" ~> str) ~ (opt("," ~> pat) <~ ")") ^^ { case f~op => QueryFile(f,op match { case Some(p)=>p case None => null}) }
    lazy val qmap:Parser[QueryOut] = "{" ~> repsep(qrow,",") <~ opt(",") <~ "}" ^^ { case rs => QueryMap(rs.toMap) }
    lazy val qrow = ("[" ~> repsep(num|(str^^{s=>"\""+s+"\""}),",") <~ "]") ~ ("=>" ~> num) ^^ { case cs ~ n => (tup(cs),n) }
    def apply(input: String): QueryTest = parseAll(qtest, input) match { case Success(r,_) => r case f => sys.error(f.toString) }
  }
}
