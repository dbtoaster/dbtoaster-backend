package ddbt

/**
 * This class reuses the compiler phases to generate test cases based on the unit
 * tests of the original DBToaster. It needs to have access to a checkout of the
 * original DBToaster repository (configured through conf/ddbt.properties with
 * variable ddbt.base_repo).
 *
 * This object decodes the unit tests of the original DBToaster repository and
 * generates plain Scala unit tests. Arguments passed are the datasets names that
 * you want to generate test for. Once finished, you need to manually invoke
 * 'sbt test' to run the tests.
 *
 * Usage examples:
 *
 *    sbt ';run-main ddbt.UnitTest tiny tiny_del standard standard_del;test-only * -- -l ddbt.SlowTest'
 *
 *    sbt ';queries;test-only * -- -l ddbt.SlowTest'
 * 
 * @author TCK
 */

object UnitTest {
  import ddbt.Utils._
  import ddbt.frontend._
  import ddbt.codegen._

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

  val dir=new java.io.File("test/gen") // output folder

  def toast(f:String) = exec(Array("bin/dbtoaster_release","-l","M3",f),true)._1.replaceAll("../../experiments/data",path_repo+"/dbtoaster/experiments/data")
  def clname(f:String) = { val s = f.replaceAll("test/queries/|finance/|simple/|/query|.sql|[/_]",""); (s(0)+"").toUpperCase+s.substring(1) }
  def clean = if (dir.isDirectory()) dir.listFiles().foreach { f=>f.delete() }

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
      "implicit def dateConv(d:Long):Date = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();\n"+
      "implicit def strConv(d:Long):String = \"\"+d\n"+
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
          "it(\""+n+" correct\") {"+ind("\n"+kv+
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
    val exclude=("missedtrades" :: // correct on tiny dataset, timeout (>10 minutes) on standard
                 List("11","11a","12","52","53","56","57","58","62","63","64","65","66","66a").map{x=>"employee/query"+x}).toArray // DBToaster SQL->M3 failing there
    val all=Utils.exec(Array("find","test/unit/queries","-type","file","-and","-not","-path","*/.*"),true)._1.split("\n").filter{ f=> !exclude.exists{ e=>f.endsWith(e) } }

    val failing = ( // TPCH 1, 3, 4, 6, 11a, 12, 13, 14, 17a, 18, 18a are also failing on tiny/del
      List("brokervariance","brokerspread","vwap") :::
      List("15","35c","36c","37","38a","40").map("employee/query"+_) :::
      List("r_indynamic","r_starofnestedagg","rs_joinwithnestedagg").map("simple/"+_)
    ).map{x=>"test/unit/queries/"+x}.toArray

    val nocompile = (
      List("ssb4") ::: List("10","11","11c","15","16","2","20","21","22","22a","5","7","8","9").map("tpch"+_) :::
      List("35b","36b","39","52a","56a","57a","58a","60","61").map("employee/query"+_) :::
      List("inequality_selfjoin","miraculous_minus","miraculous_minus2","r_agtb","r_count_of_one","r_count_of_one_prime","r_existsnestedagg","r_lift_of_count","r_multinest",
           "rs_ineqwithnestedagg","ss_math").map("simple/"+_) :::
      List("12811747","48183500","52548748","96434723").map("zeus/"+_)
    ).map{x=>"test/unit/queries/"+x}.toArray

    val passing = (all.toSet -- failing.toSet -- nocompile.toSet).toList.sorted.toArray

    println("Passing  : "+passing.size) // 131 (10 tpch still failing on tiny/del datasets)
    println("Failing  : "+failing.size) // 12
    println("NoCompile: "+nocompile.size) // 39
    val files = passing // Array("test/unit/queries/simple/r_indynamic")

    clean // remove all previous tests
    val tests = files.map { f=> UnitParser(Utils.read(path_repo+"/"+path_base+"/"+f)) }
    tests.foreach{ t =>
      // val t = tests.filter{t=>t.sql.indexOf("axfinder")!= -1}(0) // we pick one single test for purposes of debugging
      if (t.sets.size>0) try {
        println("---------------- "+t.sql); makeTest(t,fsz)
        // if ((files==nocompile)) { println(exec(Array("sbt","test-only * -- -l ddbt.SlowTest"))); clean }
      } catch {
        case th:Throwable => println("Failed to generate "+t.sql+" because "+th.getMessage); th.getStackTrace.foreach { l => println("   "+l) }
      }
    }
    println("Now run 'sbt test' to pass tests")
  }
}
