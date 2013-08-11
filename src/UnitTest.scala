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
  lazy val num = "-?[0-9]+(\\.[0-9]*)?([eE][\\-+]?[0-9]+)?".r //^^ { case x => try { java.lang.Long.parseLong(x) } catch { case _:Exception=> java.lang.Double.parseDouble(x) } }
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

  def toast(f:String) = exec(Array("bin/dbtoaster_release","-l","M3",f),true)._1.replaceAll("../../experiments/data",path_repo+"/dbtoaster/experiments/data")
  def clname(f:String) = { val s = f.replaceAll("test/queries/|finance/|simple/|/query|.sql|[/_]",""); (s(0)+"").toUpperCase+s.substring(1) }
  val dir=new java.io.File("test/gen") // output folder

  // Arguments are the dataset name you want to generate test for.
  // Once generated, use sbt to test.
  //
  //   sbt ';run-main ddbt.UnitTest tiny standard;test-only * -- -l ddbt.SlowTest'
  //
  def makeTest(t:QueryTest,fsz:String=>Boolean) = {
    val sys = (toast _ andThen M3Parser andThen TypeCheck)(t.sql)
      val cls = clname(t.sql)
      val gen = ScalaGen(cls)
      val str = gen.genStreams(sys.sources)
      val qid = sys.queries.map{_.name}.zipWithIndex.toMap
      val qtp = sys.queries.map{q=> val n:String=q.m.name; val m=sys.mapType(n); (n,"["+tup(m._1.map(gen.tpe))+","+gen.tpe(m._2)+"]") }.toMap
      
      val helper =
      "package ddbt.test.gen\n"+
      "import ddbt.lib._\n\n"+
      "import org.scalatest._\n"+
      "import akka.actor.Actor\n"+
      "import java.util.Date\n\n"+
      "class "+cls+"Spec extends Helper with FunSpec {"+ind("\n"+
      t.sets.filter{x=>fsz(x._1)}.map { case (sz,set) =>
        "describe(\"Dataset '"+sz+"'\") {"+ind("\n"+
        "val (t,res) = run["+cls+","+gen.genViewType(sys)+"]("+(str /: set.subs){ case (s,(o,n)) => s.replaceAll("\\Q"+o+"\\E",n) }+")\n"+ // XXX: fix types and retrieval
        "it(\"Runnning time = \"+time(t)+\" sec\") {}\n"+
        set.out.map { case (n,o) => "it(\"Correctness "+n+"\") { diff(res"+(if (sys.queries.size>1) "._"+(qid(n)+1) else "")+", "+(o match {
            case QueryMap(m) => "Map"+qtp(n)+"("+m.map{ case (k,v)=> "("+k+","+v+")" }.mkString(",")+")"// inline in the code
            case QueryFile(path,sep) => "decode(\""+path+"\""+(if (sep!=null) ",\""+sep+"\"" else "")+")" // XXX: pass data type
            case QuerySingleton(v) => v
          })+") }"
        }.mkString("\n"))+"\n}"
      }.mkString("\n"))+"\n}\n\n"
     
      write(dir,cls+".scala",helper+gen.genSystem(sys))
      println("Query "+cls+" generated")
  }
  
  def main(args: Array[String]) {
    val fsz = if (args.length>0) (s:String)=>args.contains(s) else (s:String)=>true // filtering datasets
    val exclude=List("11","11a","12","52","53","56","57","58","62","63","64","65","66","66a").map{x=>"employee/query"+x}.toArray // Original DBToaster failing there
    val files=Utils.exec(Array("find","test/unit/queries","-type","file","-and","-not","-path","*/.*"),true)._1.split("\n").filter{ f=> !exclude.exists{ e=>f.endsWith(e) } }
    
    val tests = files.map { f=> UnitParser(Utils.read(path_repo+"/"+path_base+"/"+f)) }
    //tests.foreach{ t =>
      val t = tests.filter{t=>t.sql.indexOf("axfinder")!= -1}(0) // we pick one single test for purposes of debugging
      try {
        println("---------------- "+t.sql)
        makeTest(t,fsz)     
        // XXX: create helpers for diff and loading from disk
      } catch {
        case th:Throwable => println("Failed to generate "+t.sql+" because "+th.getMessage); th.getStackTrace.foreach { l => println("   "+l) }
      }
    //}
    
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
