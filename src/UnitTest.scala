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
  import Utils._
  val path_examples = "examples/queries"
  val path_sources = "test/gen"
  val path_classes = "target/scala-2.10/test-classes"
  val skip = List("11","11a","12","52","53","56","57","58","62","63","64","65","66","66a", // front-end failure (SQL constructs not supported)
                  "15", // regular expressions not supported by front-end: LIKE 'S____' ==> "^S____$" where "^S....$" is expected
                  "35b","36b").map("employee/query"+_) ::: // front-end swaps table order in JOIN .. ON, test (and Scala typing) fails
             List("mddb/query3","chrissedtrades") // too long to compile, incorrect result
             // Also TPCH11c is incorrect with -O3 (front-end) option
  var csv:PrintWriter = null
  var csvFile:String = null
  var tmp = makeTempDir()
  var benchmark = false // enable benchmarks
  var samples = 10      // number of samples to take in the benchmark
  var verify = false    // enforce correctness verification in benchmark
  var modes = List[String]() // selected modes
  var datasets = List[String]() // selected datasets
  var q_f = (s:String)=>true // query filter (sql file name)

  def parseArgs(args:Array[String]) {
    import scala.collection.mutable.{Set=>MSet}
    val qinc=MSet[String](); val qexcl=MSet[String](); var qskip=false
    var i=0; val l=args.length; var as=List[String]()
    def eat(f:String=>Unit,s:Boolean=false) { i+=1; if (i<l) f(if(s) args(i).toLowerCase else args(i)) }
    while(i<l) { args(i) match {
      case "-d" => eat(s=>if(!datasets.contains(s)) datasets=datasets:+s,true)
      case "-dd"=> val ds=List("tiny","tiny_del","standard","standard_del"); datasets=ds:::datasets.filter(!ds.contains(_))
      case "-m" => eat(s=>if(!modes.contains(s)) modes=modes:+s,true)
      case "-q" => eat(s=>qinc+=s)
      case "-qx" => eat(s=>qexcl+=s)
      case "-qskip" => qskip=true
      case "-x" => benchmark=true
      case "-v" => verify=true
      case "-samples" => eat(s=>samples=s.toInt)
      case "-csv" => eat(s=>csvFile=s)
      case "-h"|"-help"|"--help" => import Compiler.{error=>e}
        e("Usage: Unit [options] [compiler options]")
        e("Filtering options:")
        e("  -d <dataset>  add a dataset: tiny, standard, big, huge (_del)?")
        e("  -dd           add tiny,tiny_del,standard,standard_del datasets")
        e("  -m <mode>     add mode : scala, lms, akka (_spec|_full|_0-10)?")
        e("                           lscala, lcpp, llms")
        e("  -q <filter>   add an inclusion filter for queries")
        e("  -qx <filter>  add an exclusion filter for queries")
        e("  -qskip        skip queries that are known to fail")
        e("Benchmarking options:")
        e("  -v            verification against reference result") // consistency verification is always enabled
        e("  -x            enable benchmarks (compile and execute)")
        e("  -samples <n>  number of samples to take (default=10)")
        e("  -csv <file>   store benchmarking results in a file")
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
    if (qskip) { val q0=q_f; q_f=(s:String)=> !skip.exists(e=>s.endsWith(e+".sql")) && q0(s) }
    Compiler.in=List(""); Compiler.parseArgs(as.reverse.toArray)
  }

  def name(f:String) = { val s=f.replaceAll("tmp/|test/queries/|finance/|simple/|/query|.sql|[/_]",""); (s(0)+"").toUpperCase+s.substring(1) }
  def main(args:Array[String]) {
    parseArgs(args)
    // Regular mode
    println("Tests total    : %6d".format(all.size))
    println("Front-end skip : %6d".format(skip.size))
    val sel = all.filter(q=>q_f(q.sql)).map{ q=> QueryTest(q.sql,q.sets.filterKeys(datasets.contains(_))
                                                    .filterKeys{d=>q.sql.indexOf("missedtrades")== -1 || d.matches("tiny.*")}) // missedtrades is very slow
    }.filter(q=>q.sets.size>0)
    println("Tests selected : %6d".format(sel.size))
    if (sel.size==0) { System.err.println("No tests selected, exiting."); return; }
    val dir = new File(path_sources); if (dir.isDirectory()) dir.listFiles().foreach { f=>f.delete() } else dir.mkdirs() // directory cleanup (erase previous tests)
    if (csvFile!=null) csv=new PrintWriter(new File (csvFile+(if(csvFile.endsWith(".csv")) "" else ".csv")))
    def mn(s:String) = (s(0)+"").toUpperCase+s.substring(1)

    if (csv!=null) { // CSV format: query,sql->m3,(codegen,compile,(med,min,max,)*)*
      csv.print(samples+",samples,"); for (m<-modes) csv.println(mn(m)+",,"+datasets.map(d=>d+",,,").mkString)
      csv.print("Query,SQLtoM3,"); for (m<-modes) csv.println("M3toCode,Compile,"+datasets.map(d=>"Med,Min,Max,").mkString)
    }
    for (q <- sel) {
      println("--------[[ "+name(q.sql)+" ]]--------")
      val (t0,m3) = Compiler.toast("m3",q.sql)
      println("SQL -> M3           : "+time(t0))
      if (csv!=null) csv.print(name(q.sql)+","+time(t0,0)+",")
      for (m <- modes) m match {
        case "lscala"|"llms" if (repo!=null && benchmark) => legacyScala(q,new Printer("LScala"),t0,m=="llms")
        case "lcpp" if (repo!=null && benchmark) => legacyCPP(q,new Printer("LCPP"),t0)
        case _ => genQuery(q,new Printer(mn(m)),m3,m)
      }
      if (csv!=null) csv.println
    }
    if (csv!=null) csv.close
    if (!benchmark) println("Now run 'test-only ddbt.test.gen.*' to pass tests")

    // XXX: Zeus mode
    // XXX: Untested mode (execute non-tested queries)
    // XXX: option for HTML report with bar graphs?
    // XXX: Use tags to filter test sizes in ScalaTest
    // XXX: Order by test or by backend first
    // XXX: use script/cluster.sh to execute Akka tests ==> to be moved in the compiler
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
      "implicit def dateConv(d:Long) = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();\n"+
      "implicit def strConv(d:Long) = \"\"+d\n"+ // fix for TPCH22
      q.sets.map { case (sz,set) =>
        (if (full) cls+"." else "")+"execute(Array(\"-n1\",\"-d"+sz+"\",\"-h\"),(res:List[Any])=>"+(if (full) "describe(\"Dataset '"+sz+"'\") " else "")+"{\n"+ind(
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
    def inject(pre:String,str:String) { val src=read(tmp.getPath+"/"+cls+".scala").split("\\Q"+pre+"\\E"); write(tmp,cls+".scala",src(0)+pre+str+src(1)) }
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
    Compiler.exec_args = "-n"+samples :: "-s" :: datasets.filter(d=>q.sets.contains(d)).map(d=>"-d"+d).toList
    val ((t_gen,t_comp),out,err) = captureOut(()=>Compiler.compile(m3,post)); p.gen(t_gen)
    if (benchmark) { p.comp(t_comp)
      if (err!="") System.err.println(err)
      else out.split("\n").foreach{ l =>
        if (!l.matches("[a-z]+: [0-9.]+ \\[[0-9.]+, [0-9.]+\\] \\(sec, [0-9]+ samples\\)$")) println(l)
        else { val e=l.split("[^-a-z_0-9.]+"); p.run(e(0),e.slice(1,4),e(5)) }
      }
      p.close
    }
    // Append correctness spec and move to test/gen/
    if (genSpec) {
      inject("import java.util.Date\n",sp)
      val f1=new File(tmp,cls+".scala")
      val f2=new File(path_sources,cls+".scala")
      if (f2.exists) f2.delete; f1.renameTo(f2)
    }
  }

  // ---------------------------------------------------------------------------
  // Legacy testing
  private var legacySC:List[String]=>Unit = null
  def legacyScala(q:QueryTest,p:Printer,t0:Long,lms:Boolean=false) {
    val libs = (if (path_repo!=null) path_repo+"/" else "")+"lib/dbt_scala/dbtlib.jar"
    if (legacySC==null) {
      legacySC=scalaCompiler(tmp,libs,Compiler.exec_sc)
      write(tmp,"RunQuery.scala","package org.dbtoaster\n"+
      "import org.dbtoaster.dbtoasterlib.DBToasterExceptions._\n"+
      "import org.dbtoaster.dbtoasterlib.QueryInterface._\n"+
      "object RunQuery {\n"+
      "  def run1 = {\n"+
      "    val q = new Query(); var time=0L; val timeStart=System.nanoTime()\n"+
      "    val msgRcvr = new DBTMessageReceiver {\n"+
      "      def onTupleProcessed {}\n"+
      "      def onQueryDone { time=System.nanoTime()-timeStart; RunQuery.synchronized { RunQuery.notifyAll } }\n"+
      "    }\n"+
      "    val r = new QuerySupervisor(q, msgRcvr); r.start; RunQuery.synchronized { r.start; RunQuery.wait; }; time\n"+
      "  }\n"+
      "  def main(args: Array[String]) = (0 until "+samples+").foreach { x=> println(run1) }\n}\n")
    }
    val (t1,sc) = if (!lms) Compiler.toast("scala",q.sql) else {
      val f="tmp.scala"; val (t1,_) = Compiler.toast("scala","-O4","-o",f,q.sql);
      val fl=if (repo!=null) new File(repo,f) else new File(f); val s=read(fl.getPath); fl.delete;
      (t1,s.replaceAll("../../experiments/data",path_repo+"/dbtoaster/experiments/data"))
    }
    p.gen(math.max(0,t1-t0))
    p.all(q){dataset=> write(tmp,"Query.scala",sc.replaceAll("/standard/","/"+dataset+"/"))
      val t2 = ns(()=>legacySC(List(tmp.getPath+"/Query.scala",tmp.getPath+"/RunQuery.scala")))._1; p.comp(t2)
      val rt = scalaExec(List(tmp,new File(libs)),"org.dbtoaster.RunQuery",Array(),Compiler.exec_vm)._1.split("\n").filter(x=>x.trim!="").map(x=>x.toLong);
      p.run(dataset,rt)
    }
  }

  def legacyCPP(q:QueryTest,p:Printer,t0:Long) {
    val boost = prop("lib_boost",null)
    val (t1,cc) = Compiler.toast("cpp",q.sql); p.gen(math.max(0,t1-t0))
    p.all(q){dataset=> write(tmp,"query.hpp",cc.replaceAll("/standard/","/"+dataset+"/"))
      val pl = path_repo+"/lib/dbt_c++"
      val po = tmp.getPath+"/query"
      val as = List("g++",pl+"/main.cpp","-include",po+".hpp","-o",po,"-O3","-lpthread","-ldbtoaster","-I"+pl,"-L"+pl) :::
               List("program_options","serialization","system","filesystem","chrono","thread").map("-lboost_"+_) :::
               (if (boost==null) Nil else List("-I"+boost+"/include","-L"+boost+"/lib"))
      val t2 = ns(()=>exec(as.toArray))._1; p.comp(t2)
      def run() = exec(Array(po),null,if (boost!=null) Array("DYLD_LIBRARY_PATH="+boost+"/lib","LD_LIBRARY_PATH="+boost+"/lib") else null)._1
      p.run(dataset,(0 until samples).map(x=>ns(run)._1))
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
  class Printer(name:String) { var tg=Seq[Long](); var tc=Seq[Long](); var tr=""
    private def med(ts:Seq[Long]) = if (ts.size==0) 0L else { val s=ts.sorted; val n=ts.size; if (n%2==0) (s(n/2)+s(n/2-1))/2 else ts(n/2) }
    def gen(t:Long) { println("%-20s: ".format(name+" codegen")+time(t)); tg=tg:+t; }
    def comp(t:Long) { println("%-20s: ".format(name+" compile")+time(t)); tc=tc:+t; }
    def run(set:String,ts:Array[String],n:String) { println("%-20s: %6s".format(name+" "+set,ts(0))+" ["+ts(1)+", "+ts(2)+"] (sec, "+n+" samples)"); tr+=ts(0)+","+ts(1)+","+ts(2)+"," }
    def run(set:String,t_runs:Seq[Long]) { val ts=t_runs.sorted; val(t0,t1,t2)=(med(ts),ts(0),ts(ts.size-1))
      println("%-20s: ".format(name+" "+set)+time(t0)+" ["+time(t1,0)+", "+time(t2,0)+"] (sec, "+ts.size+" samples)"); tr+=time(t0,0)+","+time(t1,0)+","+time(t2,0)+","
    }
    def all(q:QueryTest)(f:String=>Unit) { datasets.foreach { d=> if (!q.sets.contains(d)) tr+=",,," else f(d) }; close }
    def close { var s=time(med(tg),0)+","+time(med(tc),0)+","+tr; if (csv!=null) csv.print(s) }
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
