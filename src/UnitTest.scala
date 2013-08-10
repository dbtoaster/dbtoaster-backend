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
  lazy val str = ("\"" ~> """(\\.|[^\"])*""".r <~ "\"" | "'" ~> """(\\.|[^'])*""".r <~ "'") ^^ { x=>x }
  lazy val num = "-?[0-9]+(\\.[0-9]*)?([eE][\\-+]?[0-9]+)?".r //^^ { case x => try { java.lang.Long.parseLong(x) } catch { case _:Exception=> java.lang.Double.parseDouble(x) } }
  lazy val pat  = "/" ~> """(\\.|[^/])*""".r <~ "/" ^^ { x=>x.replaceAll("\\\\/","/") } // might need a better solution

  // JSON-like map String -> T
  private def map[T](p:Parser[T]) = "{" ~> repsep((str <~ "=>") ~ p,",") <~ "}" ^^ { case rs => rs.map{case n~v=>(n,v)}.toMap }

  lazy val qtest = ("{" ~> ":path" ~> "=>" ~> str <~ ",") ~ (":datasets" ~> "=>" ~> map(qset) <~ "}") ^^ { case n~qs => QueryTest(n,qs) }
  lazy val qset = "{" ~> opt(":subs" ~> "=>" ~> "[" ~> repsep(qsub,",") <~ "]" <~ ",") ~ (":toplevels" ~> "=>" ~> map(qout)) <~ "}" ^^ {
    case ss ~os => QuerySet(ss match { case Some(s)=>s case None=>Nil },os)
  }
  lazy val qsub = ("[" ~> pat <~ ",") ~ (str <~ "]") ^^ { case p~r => (p,r) }
  lazy val qout = "{"~>":type"~>"=>"~>(
    (":onelevel"~>","~>":expected"~"=>"~>(qfile|qmap))
  | (":singleton"~>","~>":expected"~>"=>"~>num ^^ { case n => QuerySingleton(n) })
  ) <~ opt(",") <~"}" ^^ { case q => q }
  lazy val qfile:Parser[QueryOut] = ("results_file" ~> "(" ~> str) ~ (opt("," ~> pat) <~ ")") ^^ { case f~op => QueryFile(f,op match { case Some(p)=>p case None => null}) }
  lazy val qmap:Parser[QueryOut] = "{" ~> repsep(qrow,",") <~ opt(",") <~ "}" ^^ { case rs => QueryMap(rs.toMap) }
  lazy val qrow = ("[" ~> repsep(num|(str^^{s=>"\""+s+"\""}),",") <~ "]") ~ ("=>" ~> num) ^^ { case cs ~ n => (Utils.tup(cs),n) }

  def apply(input: String): QueryTest = parseAll(qtest, input) match {
    case Success(result, _) => result
    case failure => sys.error(failure.toString)
  }
}

// This object is meant to decode the unit tests of original DBtoaster and
// convert them into plain Scala tests
object UnitTest {
  import ddbt.Utils._
  import ddbt.frontend._
  import ddbt.codegen._

  def toast(f:String) = exec(Array("bin/dbtoaster_release","-l","M3",f),true)._1.replaceAll("../../experiments/data",path_repo+"/dbtoaster/experiments/data")
  def clname(f:String) = { val s = f.replaceAll("test/queries/|finance/|simple/|/query|.sql|[/_]",""); (s(0)+"").toUpperCase+s.substring(1) }

  // First argument is a filter to generate only a particular dataset
  // sbt run-main ddbt.UnitTest tiny
  def main(args: Array[String]) {
    val fsz = if (args.length>0 && args(0)!="") (s:String)=>s==args(0) else (s:String)=>true // filtering by size
    val files=Utils.exec(Array("find","test/unit/queries","-type","file","-and","-not","-path","*/.*"),true)._1.split("\n")
    val tests = files.map { f=> UnitParser(Utils.read(path_repo+"/"+path_base+"/"+f)) }
    
    //tests.foreach{ t => 
      val t = tests.filter{t=>t.sql.indexOf("axfinder")!= -1}(0) // we pick one single test for purposes of debugging
      val sys = (toast _ andThen M3Parser andThen TypeCheck)(t.sql)
      val cls = clname(t.sql)
      val gen = ScalaGen(cls)
      val str = gen.genStreams(sys.sources)
      
      //println(gen.genStreams(sys.sources)+)

      // XXX: instead create a full test wrapper
      
      // andThen ScalaGen(clname(t.sql))
      // package: ddbt.test.generated
      
      //println(c(t.sql))
      var helper = "object "+cls+"Spec extends Helper {"+ind("\n"+
      t.sets.filter{x=>fsz(x._1)}.map { case (sz,set) =>
        "describe(\""+sz+"\") {"+ind("\n"+
        "val (t,res) = run["+cls+",Long,Long]("+(str /: set.subs){ case (s,(o,n)) => s.replaceAll("\\Q"+o+"\\E",n) }+")\n"+ // XXX: fix types and retrieval
        "it(\"Runnning time = \"+time(t)+\" sec\") {}\n"+
        set.out.map { case (n,o) => "it(\""+n+"\") { diff( res.get(\""+n+"\"), "+(o match {
            case QueryMap(m) => "Map("+m.map{ case (k,v)=> "("+k+","+v+")" }.mkString(",")+")"// inline in the code
            case QueryFile(path,sep) => "decode(\""+path+"\""+(if (sep!=null) ",\""+sep+"\"" else "")+")"
            case QuerySingleton(v) => v
          })+") }"
        }.mkString("\n"))+"\n}"
      }.mkString("\n"))+"\n}\n\n"
      
      println(helper+gen.genSystem(sys))
      // XXX: write in a file
      // XXX: create helpers for diff and loading from disk
    //}
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
