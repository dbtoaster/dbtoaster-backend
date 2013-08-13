package ddbt

// AST of query unit testing
case class QueryTest(sql:String,sets:Map[String,QuerySet]) { override def toString = sql+Utils.ind(sets.map{case (k,v)=>"\n - "+k+": "+v.out.toString}.mkString) }
case class QuerySet(subs:List[(String,String)],out:Map[String,QueryOut])
abstract sealed class QueryOut
case class QueryMap(m:Map[String,String]) extends QueryOut
case class QueryFile(path:String,sep:String=null) extends QueryOut
case class QuerySingleton(v:String) extends QueryOut

// Parser for unit testing declarations
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
  lazy val qrow = ("[" ~> repsep(num|(str^^{s=>"\""+s+"\""}),",") <~ "]") ~ ("=>" ~> num) ^^ { case cs ~ n => (Utils.tup(cs),n) }
  def apply(input: String): QueryTest = parseAll(qtest, input) match { case Success(r,_) => r case f => sys.error(f.toString) }
}

// This object is meant to decode the unit tests of original DBtoaster and
// convert them into plain Scala tests
object UnitTest {
  import ddbt.Utils._
  import ddbt.frontend._
  import ddbt.codegen._

  val dir=new java.io.File("test/gen") // output folder
  
  def toast(f:String) = exec(Array("bin/dbtoaster_release","-l","M3",f),true)._1.replaceAll("../../experiments/data",path_repo+"/dbtoaster/experiments/data")
  def clname(f:String) = { val s = f.replaceAll("test/queries/|finance/|simple/|/query|.sql|[/_]",""); (s(0)+"").toUpperCase+s.substring(1) }
  def clean = if (dir.isDirectory()) dir.listFiles().foreach { f=>f.delete() }

  // Arguments are the dataset name you want to generate test for.
  // Once generated, use sbt to test.
  //
  //   sbt ';run-main ddbt.UnitTest standard;test-only * -- -l ddbt.SlowTest'
  //
  def makeTest(t:QueryTest,fsz:String=>Boolean) = {
    val sys = (toast _ andThen M3Parser andThen TypeCheck)(t.sql)
    val cls = clname(t.sql)
    val gen = ScalaGen(cls)
    val str = gen.genStreams(sys.sources)
    val qid = sys.queries.map{_.name}.zipWithIndex.toMap
    val qt = sys.queries.map{q=>(q.name,sys.mapType(q.m.name)) }.toMap

    val helper =
      "package ddbt.test.gen\n"+
      "import ddbt.lib._\n\n"+
      "import org.scalatest._\n"+
      "import akka.actor.Actor\n"+
      "import java.util.Date\n\n"+
      "class "+cls+"Spec extends Helper with FunSpec {"+ind("\n"+
      "import scala.language.implicitConversions\n"+
      "implicit def dateConv(d:Long):Date = new Date(d)\n"+
      t.sets.filter{x=>fsz(x._1)}.map { case (sz,set) =>
        "describe(\"Dataset '"+sz+"'\") {"+ind("\n"+
        "val (t,res) = run["+cls+","+gen.genViewType(sys)+"]("+(str /: set.subs){ case (s,(o,n)) => s.replaceAll("\\Q"+o+"\\E",n) }+")\n"+ // XXX: fix types and retrieval
        //"it(\"Runnning time = \"+time(t)+\" sec\") {}\n"+
        set.out.map { case (n,o) =>
          val (kt,vt) = qt(n)
          val qtp = "["+tup(kt.map(gen.tpe))+","+gen.tpe(vt)+"]"
          val fmt = (kt:::vt::Nil).mkString(",")
          val kv = if (kt.size==0) "" else {
            val ll=(kt:::vt::Nil).zipWithIndex
            "def kv(l:List[Any]) = l match { case List("+ll.map{case (t,i)=>"v"+i+":"+gen.tpe(t)}.mkString(",")+") => ("+tup(ll.reverse.tail.reverse.map{ case (t,i)=>"v"+i })+",v"+ll.last._2+") }\n"
          }
          "it(\"Correctness "+n+"\") {"+ind("\n"+kv+
          "diff(res"+(if (sys.queries.size>1) "._"+(qid(n)+1) else "")+", "+(o match {
            case QueryMap(m) => "Map"+qtp+"("+m.map{ case (k,v)=> "("+k+","+v+")" }.mkString(",")+")"// inline in the code
            case QueryFile(path,sep) => "loadCSV"+qtp+"(kv,\""+path_repo+"/"+path_base+"/"+path+"\",\""+fmt+"\""+(if (sep!=null) ",\"\\\\Q"+sep.replaceAll("\\\\\\|","|")+"\\\\E\"" else "")+")" // XXX: pass data type
            case QuerySingleton(v) => v
          })+")")+"\n}"
        }.mkString("\n"))+"\n}"
      }.mkString("\n"))+"\n}\n\n"
     
      write(dir,cls+".scala",helper+gen.genSystem(sys))
      println("Query "+cls+" generated")
  }
  
  def main(args: Array[String]) {
    val fsz = if (args.length>0) (s:String)=>args.contains(s) else (s:String)=>true // filtering datasets
    val exclude=List("11","11a","12","52","53","56","57","58","62","63","64","65","66","66a").map{x=>"employee/query"+x}.toArray // DBToaster SQL->M3 failing there
    val all=Utils.exec(Array("find","test/unit/queries","-type","file","-and","-not","-path","*/.*"),true)._1.split("\n").filter{ f=> !exclude.exists{ e=>f.endsWith(e) } }
    
    val passing = (
      List("axfinder","pricespread") :::
      List("3","4","6","11a","12","13","14","17","17a","18","18a","19").map("tpch"+_) :::
      List("02","02a","03","03a","04","04a","05","06","07","12a","22","45","48","49","50","51","54","55","62a","64a","65a").map("employee/query"+_) :::
      List("r_aggcomparison","r_gtealldynamic","r_impossibleineq","r_ltalldynamic","r_possibleineq","r_possibleineqwitheq","r_nonjoineq","rs_column_mapping_3","singleton_renaming_conflict",
           "t_lifttype","m3k3unable2escalate","rst","r_ineqandeq","r_aggofnestedagg").map("simple/"+_) :::
      List("75453299","95497049","94384934").map("zeus/"+_)
    ).map{x=>"test/unit/queries/"+x}
    
    val failing = (
      List("brokervariance","brokerspread","vwap") :::
      List("01","01a","08","08a","09","09a","10","10a","11b","13","14","15","16","16a","35c","36c","37","38a","40").map("employee/query"+_) :::
      List("r_agtbexists","r_avg","r_count","r_bigsumstar","r_btimesa","r_btimesacorrelated","r_deepscoping","r_gbasumb","r_gtesomedynamic","r_gtsomedynamic","r_instatic","r_ltallagg",
           "r_natselfjoin","r_nogroupby","r_selectstar","r_simplenest","r_smallstar","r_starofnested","r_starofnestedagg","r_sumdivgrp","r_sumstar","rs_column_mapping_1",
           "rs_column_mapping_2","rs_eqineq","rs_joinon","rs_natjoin","rs_natjoinineq","rs_natjoinpartstar","rs_selectconstcmp","rs_selectpartstar","rs_selectstar","rs_simple","rs_stringjoin",
           "r_divb","r_ltallavg","rs_joinwithnestedagg","r_sum_out_of_aggregate","rs","rs_cmpnest","r_aggofnested","r_sumadivsumb","rstar","rs_inequality","r_sumnestedintargetwitheq",
           "rs_ineqonnestedagg").map("simple/"+_) :::
      List("11564068","37494577","59977251").map("zeus/"+_)
    ).map{x=>"test/unit/queries/"+x}.toArray
    
    val nocompile = (all.toSet -- passing.toSet -- failing.toSet).toArray
    /*
    List(,"missedtrades","ssb4") :::
    List("1","10","11","11a","11c","14","15","16","17a","18","18a","2","20","21","22","22a","4","5","7","8","9").map("tpch"+_) :::
    List("07","11","11a","12","17a","23a","24a","35b","36b","39","46","47","47a","52","52a","53","53a","56","56a","57","57a","58","58a","59","60","61","62","63","63a",
         "64","65","65a","66","66a").map("employee/query"+_) :::
    List("inequality_selfjoin","invalid_schema_fn","","miraculous_minus","miraculous_minus2","r_agtb","r_count_of_one",
         "r_count_of_one_prime","r_existsnestedagg","r_indynamic","r_lift_of_count","r_ltallcorravg","r_multinest","r_sum_gb_all_out_of_aggregate",
         "r_sum_gb_out_of_aggregate","rr_ormyself"
         ,"r_sumnestedintarget"
         ,"r_sumoutsideofagg","r_unique_counts_by_a",
         ,"rs_ineqwithnestedagg","rtt_or_with_stars","ss_math").map("simple/"+_) :::
    List("12811747","39765730","48183500","52548748","96434723").map("zeus/"+_)
    */
    
    println("Passing  : "+passing.size) // 52
    println("Failing  : "+failing.size) // 70
    println("NoCompile: "+nocompile.size) // 61
    val files = nocompile //Array("test/unit/queries/simple/r_aggofnested") //"test/unit/queries/tpch1")
    
    val independent = (files==nocompile)
    
    clean // remove all previous tests
    val tests = files.map { f=> UnitParser(Utils.read(path_repo+"/"+path_base+"/"+f)) }
    tests.foreach{ t =>
    //  val t = tests.filter{t=>t.sql.indexOf("axfinder")!= -1}(0) // we pick one single test for purposes of debugging
      try {
        println("---------------- "+t.sql); makeTest(t,fsz)
        if (independent) { println(exec(Array("sbt","test-only * -- -l ddbt.SlowTest"))); clean }
      } catch {
        case th:Throwable => println("Failed to generate "+t.sql+" because "+th.getMessage); th.getStackTrace.foreach { l => println("   "+l) }
      }
    }
    println("Now run 'sbt test' to pass tests") 
  }
}

/*
Steps: 
1. Forall test/unit/query (to be executed before tests or manually)
   - generate the corresponding query executor
   - generate a custom companion object that will create a test for all sets
   - generate the result either in a destination file (easier) or in scala code
   -> the companion object must extend FunSpec or a JUnit test
2. run sbt tests
*/
