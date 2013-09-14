package ddbt
import ddbt.frontend._
import ddbt.codegen._

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
 *
 * Arguments:
 *   -q<pattern> : queries filtering, any matching pattern will select the query
 *   -d<dataset> : set filtering, name must be exact, takes the union
 *   -o<option>  : add an option that is directly passed to dbtoaster
 *
 * Usage examples:
 *
 *    sbt ';run-main ddbt.UnitTest -dtiny -dtiny_del -dstandard -dstandard_del;test-only * -- -l ddbt.SlowTest'
 *
 *    sbt ';check -dbig -q.*axfinder;test-only ddbt.test.gen.*'
 * 
 * @author TCK
 */
object UnitTest {
  import ddbt.Utils._

  // AST of query unit testing
  case class QueryTest(sql:String,sets:Map[String,QuerySet]) { override def toString = sql+ind(sets.map{case (k,v)=>"\n - "+k+": "+v.out.toString}.mkString) }
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
    lazy val qrow = ("[" ~> repsep(num|(str^^{s=>"\""+s+"\""}),",") <~ "]") ~ ("=>" ~> num) ^^ { case cs ~ n => (tup(cs),n) }
    def apply(input: String): QueryTest = parseAll(qtest, input) match { case Success(r,_) => r case f => sys.error(f.toString) }
  }
  
  // Repository-specific functions shared with tests (Parsers at least)
  private val rbase = new java.io.File(path_repo+"/"+path_base)
  def load(file:String) = UnitParser(read(path_repo+"/"+path_base+"/"+file))
  def toast(f:String,opts:List[String]=Nil):String = if (path_repo=="") exec((List(path_bin,"-l","m3"):::opts:::List(f)).toArray)._1 else
    exec((List("bin/dbtoaster_release","-l","m3"):::opts:::List(f)).toArray,rbase,null,false)._1.replaceAll("../../experiments/data",path_repo+"/dbtoaster/experiments/data")
  
  val all = try { exec(Array("find","test/unit/queries","-type","f","-and","-not","-path","*/.*"),rbase)._1.split("\n") } catch { case e:Exception => println("Repository not configured"); Array[String]() }
  val exclude = List("11","11a","12","52","53","56","57","58","62","63","64","65","66","66a", // front-end failure (SQL constructs not supported)
                          "15", // regular expressions not supported by front-end: LIKE 'S____' ==> "^S____$" where "^S....$" is expected
                          "35b","36b").map("employee/query"+_) // front-end swaps table order in JOIN .. ON, test (and Scala typing) fails
  val filtered = all.filter{ f=> !exclude.exists{ e=>f.endsWith(e) } }.sorted // exclude.map{"test/unit/queries/"+_}.sorted.toArray

  // Testing helper (used only in test files)
  def sqlFiles(dataset:String="standard"):(Array[String],Array[String],String) = if (Utils.path_repo!="") {
    val fs = filtered.map(f=>load(f)).filter(t=>t.sets.contains(dataset)).map(t=>t.sql)
    (all.map(x=>load(x).sql),fs,path_repo+"/"+path_base)
  } else {
      val dir = "examples/queries"
      val files = if (new java.io.File(dir).exists) Utils.exec(Array("find",dir,"-name","*.sql","-and","-not","-name","schemas.sql"))._1.split("\n")
      else { System.err.println(("@"*80)+"\n@"+(" "*78)+("@\n@ %-76s @".format("WARNING: folder '"+dir+"' does not exist, tests skipped !\n@"+(" "*78))+"@\n"+("@"*80))); Array[String]() }
      (files,files,null)
  }
  
  // ---------------------------------------------------------------------------

  // Test generator
  private val dir=new java.io.File("test/gen") // output folder
  def makeTest(t:QueryTest,opts:List[String]=Nil) = {
    def clname(f:String) = { val s = f.replaceAll("test/queries/|finance/|simple/|/query|.sql|[/_]",""); (s(0)+"").toUpperCase+s.substring(1) }
    val sys = (((f:String)=>toast(f,opts)) andThen M3Parser andThen TypeCheck)(t.sql)
    val cls = clname(t.sql)
    val gen = ScalaGen(cls)
    val str = gen.genStreams(sys.sources)
    val qid = sys.queries.map{_.name}.zipWithIndex.toMap
    val qt = sys.queries.map{q=>(q.name,sys.mapType(q.m.name)) }.toMap
    val helper =
      "package ddbt.test.gen\nimport ddbt.lib._\n\nimport org.scalatest._\nimport akka.actor.Actor\nimport java.util.Date\n\n"+
      "class "+cls+"Spec extends Helper with FunSpec {"+ind("\n"+
      "import scala.language.implicitConversions\n"+
      "implicit def dateConv(d:Long):Date = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();\n"+
      "implicit def strConv(d:Long):String = \"\"+d\n"+ // fix for TPCH22
      t.sets.map { case (sz,set) =>
        // val mystr = (str /: set.subs){ case (s,(o,n)) => s.replaceAll("\\Q"+o+"\\E",n) } // seems that set.subs are useless here
        val mystr = (if (sz.endsWith("_del")) str.replaceAll("\\),Split\\(\\)",",\"add+del\""+"),Split()") else str).replaceAll("/standard/","/"+sz+"/") // streams for this dataset
        "describe(\"Dataset '"+sz+"'\") {"+ind("\n"+
        "val (t,res) = run["+cls+","+gen.genViewType(sys)+"]("+mystr+")\n"+
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
            case QueryFile(path,sep) => "loadCSV"+qtp+"(kv,\""+path_repo+"/"+path_base+"/"+path+"\",\""+fmt+"\""+(if (sep!=null) ",\"\\\\Q"+sep.replaceAll("\\\\\\|","|")+"\\\\E\"" else "")+")"
            case QuerySingleton(v) => v
          })+")")+"\n}"
        }.mkString("\n"))+"\n}"
      }.mkString("\n"))+"\n}\n\n"
      write(dir,cls+".scala",helper+gen.genSystem(sys))
      println("Query "+cls+" generated")
  }

  // Generate all tests
  def main(args: Array[String]) {
    val f_ds = { val ds = args.filter(_.startsWith("-d")).map(_.substring(2)); if (ds.length>0) (s:String)=>ds.contains(s) else (s:String)=>true }
    val f_qs = { val ps = args.filter(_.startsWith("-q")).map(p=>java.util.regex.Pattern.compile(p.substring(2)))
      if (ps.length>0) (s:String)=>ps.exists(p=>p.matcher(s).matches()) else (s:String)=>true
    }
    val opts = args.filter(_.startsWith("-o")).map(_.substring(2)).toList

    val files = filtered.filter(f_qs)
    println("Tests total     : %4d".format(all.size))
    println("Tests excluded  : %4d".format(exclude.size)+" (front-end issues)")
    println("Tests selected  : %4d".format(files.size))

    if (dir.isDirectory()) dir.listFiles().foreach { f=>f.delete() } else dir.mkdirs() // directory cleanup (erase previous tests)
    files.map(load).foreach{ t0 =>
      val t = QueryTest(t0.sql,t0.sets.filter(x=>f_ds(x._1))
                 // missedtrades is very slow, brokerspread drifts due to rounding errors, similarly as original DBToaster
                 .filter{x=> !t0.sql.matches(".*(missedtrades|brokerspread).*") || x._1.matches("tiny.*")})
      if (t.sets.size>0) try { println("---------------- "+t.sql); makeTest(t,opts) }
      catch { case th:Throwable => println("Compiling '"+t.sql+"' failed because "+th.getMessage); th.getStackTrace.foreach { l => println("   "+l) } }
    }
    println("Now run 'test-only ddbt.test.gen.*' to pass tests")
  }
}
