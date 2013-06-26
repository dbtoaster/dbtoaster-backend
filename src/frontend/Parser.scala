package ddbt.frontend

import scala.util.parsing.combinator.syntactical.StandardTokenParsers
import scala.util.parsing.combinator.lexical.StdLexical
import scala.util.parsing.combinator.token.StdTokens

// -----------------------------------------------------------------------------

class ExtParser extends StandardTokenParsers {
  class CaseInsensitiveLexical extends StdLexical {
    override protected def processIdent(name: String) = {
      val n=name.toLowerCase; val r=reserved.filter(x=>x.toLowerCase==n)
      if (r.size>0) Keyword(r.head) else super.processIdent(name)
    }
  }
  // Add case insensitivity to keywords
  override val lexical:StdLexical = new CaseInsensitiveLexical
  // Allow matching non-reserved keywords
  import scala.language.implicitConversions
  override implicit def keyword(chars: String) = keywordCache.getOrElseUpdate(chars,
    acceptIf(x=>x.chars.toLowerCase==chars.toLowerCase)(x=>"Expected '"+chars+"'") ^^ (_.chars))

  import lexical._
  import ddbt.ast._

  //lexical.reserved ++= List("")
  lexical.delimiters ++= List("(",")",",",".",";","+","-",":=")

  // ------------ Literals
  lazy val long = opt("+"|"-") ~ numericLit ^^ { case s~n => (s match { case Some("-") => "-" case _ => ""})+n }
  lazy val double = (long <~ ".") ~ opt(numericLit) ~ opt(("E"|"e") ~> long) ^^ { case i ~ d ~ e => i+"."+(d match { case Some(s)=>s case None=>"" })+(e match { case Some(j)=>"E"+j case _=>"" }) }

  // ------------ Types
  lazy val tpe: Parser[Type] = (("string" | ("char"|"varchar") ~> "(" ~> numericLit <~  ")") ^^^ TypeString
  | ("char"|"short"|"int"|"long") ^^^ TypeLong //| "char" ^^^ TypeChar | "short" ^^^ TypeShort | "int" ^^^ TypeInt | "long" ^^^ TypeLong
  | ("float"|"decimal"|"double") ^^^ TypeDouble // | ("float"|"decimal") ^^^ TypeFloat | "double" ^^^ TypeDouble
  | "date" ^^^ TypeDate | failure("Bad type")
  )

  // ------------ Source declaration
  lazy val source = "CREATE" ~> ("STREAM"|"TABLE") ~ schema ~ ("FROM" ~> sourceIn) ~ split ~ adaptor <~ ";" ^^ { case t~s~i~b~a => Source(t=="STREAM",s,i,b,a) }
  lazy val schema = ident ~ ("(" ~> repsep(ident ~ tpe, ",") <~ ")") ^^ { case n~f => Schema(n,f.map{case n~t=>(n,t)}) }
  lazy val sourceIn = "FILE" ~> stringLit ^^ { case f => SourceFile(f) }
  lazy val split = (
    "LINE" ~ "DELIMITED" ^^^ { SplitLine }
  | stringLit <~ "DELIMITED" ^^ { SplitSep(_) }
  | "FIXEDWIDTH" ~> numericLit ^^ { case x => SplitSize(Integer.parseInt(x)) }
  //| "PREFIX" ~> numericLit ^^ { SplitPrefix(Integer.parseInt(_)) }
  )
  lazy val adaptor = ident ~ opt("(" ~> repsep(ident ~ (":=" ~> stringLit),",") <~ ")") ^^ { case n~oos =>
    Adaptor(n,oos match { case Some(os)=> os.map{case x~y => (x,y) }.toMap case None=>List[(String,String)]().toMap })
  }
}

// -----------------------------------------------------------------------------
// M3 parser

object M3Parser extends ExtParser {
  import ddbt.ast._
  import ddbt.ast.M3._
  lexical.delimiters ++= List("{","}",":",":=","+","-","*","/","=","!=","<","<=",">=",">","[","]","^=","+=")

  // ------------ Expressions
  lazy val mapref = ident ~ opt("(" ~> tpe <~ ")") ~ ("[" ~> "]" ~> "[" ~> repsep(ident,",") <~ "]") <~ opt(":" ~ "(" ~ expr ~ ")") ^^
                    { case n~ot~ks=>MapRef(n,ot match { case Some(t)=>t case None=>null },ks) }

  lazy val expr:Parser[Expr] = prod ~ opt("+" ~> expr) ^^ { case l~or=>or match{ case Some(r)=>Add(l,r) case None=>l } }
  lazy val prod:Parser[Expr] = atom ~ opt("*" ~> prod) ^^ { case l~or=>or match{ case Some(r)=>Mul(l,r) case None=>l } }
  lazy val atom = (
    ("AggSum" ~> "(" ~> "[" ~> repsep(ident,",") <~  "]" <~ ",") ~ expr <~ ")"  ^^ { case ks~e => AggSum(ks,e) }
  | mapref
  | ident ~ ("(" ~> repsep(ident, ",") <~ ")") ^^ { case n~f => Tuple(n,f) } // only in map declaration
  | ("[" ~> "/" ~> ":" ~> tpe <~ "]") ~ ("(" ~> expr <~ ")") ^^ { case t~e => Apply("/",t,List(e)) }
  | ("[" ~> ident <~ ":") ~ (tpe <~ "]") ~ ("(" ~> repsep(expr,",") <~ ")") ^^ { case n~t~as => Apply(n,t,as) }
  | "EXISTS" ~> "(" ~> expr <~ ")" ^^ { Exists(_) }
  | "DATE" ~> "(" ~> expr <~ ")" ^^ { case e => Apply("date",TypeDate,List(e)) }
  | ("(" ~> ident <~ "^=") ~ (expr <~ ")") ^^ { case n~v => Lift(n,v) }
  |  "(" ~> expr <~ ")"
  | "{" ~> expr ~ opt(("="|"!="|">"|"<"|">="|"<=") ~ expr) <~ "}" ^^ {
    case l~Some(op~r) => op match { case "="=>Cmp(l,r,OpEq) case "!="=>Cmp(l,r,OpNe) case ">"=>Cmp(l,r,OpGt) case ">="=>Cmp(l,r,OpGe) case "<"=>Cmp(r,l,OpGt) case "<="=>Cmp(r,l,OpGe) }
    case l~None => l
  }
  | ident ^^ { Ref(_) }
  | double ^^ { Const(TypeDouble,_) }
  | long ^^ { Const(TypeLong,_) }
  | stringLit ^^ { Const(TypeString,_) }
  )

  // ------------ System definition
  lazy val map = ("DECLARE" ~> "MAP" ~> ident) ~ opt("(" ~> tpe <~ ")") ~ ("[" ~> "]" ~> "[" ~> repsep(ident ~ (":" ~> tpe),",") <~ "]" <~ ":=") ~ expr <~ ";" ^^
                 { case n~t~ks~e => Map(n,t match { case Some(t)=>t case None=>null},ks.map{case n~t=>(n,t)},e) }
  lazy val query = ("DECLARE" ~> "QUERY" ~> ident <~ ":=") ~ mapref <~ ";" ^^ { case n~m=>Query(n,m) } | failure("Bad M3 query")
  lazy val trigger = (("ON" ~> ("+"|"-")) ~ ident ~ ("(" ~> repsep(ident, ",") <~ ")") ~ ("{" ~> rep(stmt) <~ "}") ^^
                        { case op~n~f~ss=> val s=Schema(n,f.map{(_,null)}); if (op=="+") TriggerAdd(s,ss) else TriggerDel(s,ss) }
                     | "ON" ~> "SYSTEM" ~> "READY" ~> "{" ~> rep(stmt) <~ "}" ^^ { TriggerReady(_) } | failure("Bad M3 trigger"))
  lazy val stmt = mapref ~ ("+="|":=") ~ expr <~ ";" ^^ { case m~op~e=>StmtMap(m,e,op match { case "+="=>OpAdd case ":="=>OpSet }) }

  lazy val system = {
    val spc = ("-"~"-"~rep("-"))
    ((spc ~ "SOURCES" ~ spc) ~> rep(source)) ~
    ((opt(spc) ~ "MAPS" ~ spc) ~> rep(map)) ~
    ((opt(spc) ~ "QUERIES" ~ spc) ~> rep(query)) ~
    ((spc ~ "TRIGGERS" ~ spc) ~> rep(trigger)) ^^ { case ss~ms~qs~ts => System(ss,ms,qs,ts) }
  }

  def load(path:String) = parse(scala.io.Source.fromFile(path).mkString)
  def parse(str:String) = phrase(system)(new lexical.Scanner(str)) match {
    case Success(x, _) => x
    case e => sys.error(e.toString)
  }
}

// -----------------------------------------------------------------------------
// SQL parser

object SQLParser extends ExtParser {
  import ddbt.ast._
  import ddbt.ast.SQL._

  // XXX: THIS IS INCOMPLETE, PLEASE REVIEW ALL, IN PARTICULAR MAIN QUERIES OBJECTS

  lexical.reserved ++= List("FROM","WHERE","GROUP","JOIN","NATURAL","ON") // reduce this list by conditional accepts
  lexical.delimiters ++= List("+","-","*","/","%","=","<>","<","<=",">=",">")

  lazy val field = opt(ident<~".")~(ident|"*") ^^ { case ot~n => Field(n,ot match {case Some(t)=>t case None=>null}) } // if '*' compute the expansion

  // ------------ Expressions
  lazy val expr = prod ~ rep(("+"|"-") ~ prod) ^^ { case a~l => (a/:l) { case (l,o~r)=> o match { case "+" => Add(l,r) case "-" => Sub(l,r) }} }
  lazy val prod = atom ~ rep(("*"|"/"|"%") ~ atom) ^^ { case a~l => (a/:l) { case (l,o~r)=> o match { case "*" => Mul(l,r) case "/" => Div(l,r) case "%" => Mod(l,r) }} }
  lazy val atom:Parser[Expr] = (
    "COUNT" ~> "(" ~>"DISTINCT" ~> expr <~ ")" ^^ { Count(_,true) }
  | ("ALL"|"SOME") ~ ("(" ~> query <~ ")") ^^ { case op~e => op match { case "ALL"=> All(e) case "SOME"=> Som(e) } }
  | ("SUM"|"AVG"|"COUNT") ~ ("(" ~> expr <~ ")") ^^ { case f~e => f.toUpperCase match { case "SUM"=>Sum(e) case "AVG"=>Avg(e) case "COUNT"=>Count(e) } }
  | "DATE" ~> "(" ~> expr <~ ")" ^^ { Cast(TypeDate,_) }
  | ("SUBSTRING"|"SUBSTR")~>"("~> expr ~ (","~>numericLit) ~ opt(","~>numericLit) <~")" ^^ { case v~s~oe=> Substr(v,Integer.parseInt(s),oe match{ case Some(n)=>Integer.parseInt(n) case _=> -1 }) }
  | ("CASE"~>"WHEN"~>cond) ~ ("THEN"~>expr) ~ ("ELSE"~>expr) <~"END" ^^ { case c~t~e=>Case(c,t,e) }
  
  | ("CASE"~>expr) ~ ("WHEN"~>expr) ~ ("THEN"~>expr) ~ ("ELSE"~>expr) <~"END" ^^ { case c1~c2~t~e=>Case(Cmp(c1,c2,OpEq),t,e) }
  | ( ("DATE_PART"~>"("~>stringLit)~(","~>expr<~")")
    | ("EXTRACT"~>"("~>ident)~("FROM"~>expr<~")")
    | ("YEAR"|"MONTH"|"DAY")~("("~>expr<~")")) ^^ { case p~e => Apply(p.toLowerCase,List(e)) } // day(e), month(e), year(e)
  | ("vec_length"|"dihedral_angle"|"listmin"|"listmax") ~ ("(" ~> repsep(expr,",") <~ ")") ^^ { case n~as => Apply(n,as) } // allow API functions only
  | field
  | "(" ~> expr <~ ")"
  | "(" ~> query <~ ")" ^^ { Nested(_) }
  | (double | long | stringLit) ^^ { Const(_) }
  | failure("SQL expression")
  )
  
  // ------------ Conditions
  def disj = rep1sep(conj,"OR") ^^ { case cs => (cs.head/:cs.tail)((x,y)=>Or(x,y)) }
  def conj = rep1sep(cond,"AND") ^^ { case cs => (cs.head/:cs.tail)((x,y)=>And(x,y)) }
  lazy val cond:Parser[Cond] = (
    "EXISTS" ~> "(" ~> query <~ ")" ^^ { Exists(_) }
  | "NOT" ~> cond ^^ { Not(_) }
  | expr ~ opt("NOT") ~ ("LIKE" ~> stringLit) ^^ { case e~o~s => o match { case Some(_)=>Not(Like(e,s)) case None=>Like(e,s) } }
  | expr ~ ("BETWEEN" ~> expr) ~ ("AND" ~> expr) ^^ { case e~m~n => Range(e,m,n) }
  | expr ~ (opt("NOT") <~ "IN") ~ query ^^ { case e~o~q => o match { case Some(_)=>Not(In(e,q)) case None=>In(e,q) } }
  | expr ~ ("="|"<>"|">"|"<"|">="|"<=") ~ expr ^^ { case l~op~r => op match {
      case "="=>Cmp(l,r,OpEq) case "<>"=>Cmp(l,r,OpNe) case ">"=>Cmp(l,r,OpGt) case ">="=>Cmp(l,r,OpGe) case "<"=>Cmp(r,l,OpGt) case "<="=>Cmp(r,l,OpGe) } }
  | "(" ~> disj <~ ")"
  )
  
  // ------------ Queries
  lazy val tab = ("(" ~ query ~ ")" | ident) ~ opt(opt("AS")~ident)
  lazy val join = tab ~ "NATURAL"~"JOIN"~ tab | tab ~ "JOIN" ~ tab ~ "ON" ~ cond | tab
  lazy val from = "FROM" ~> repsep(join,",")
  lazy val group = rep1sep(field<~opt("ASC"|"DESC"),",")
    
  lazy val query:Parser[Query] = (
   "LIST"~>"("~>repsep(expr,",")<~")" ^^ { Lst(_) }
  | ("SELECT" ~> opt("DISTINCT")) ~ repsep(expr ~ opt("AS"~>ident),",") ~ opt(from) ~ opt("WHERE" ~> disj) ~ opt("GROUP"~>"BY"~> group) ^^ { case s => View("XXX")}
  | "(" ~> query <~ ")"
  )
  lazy val sqlAny = rep(ident|numericLit|stringLit|"."|","|"("|")"|"+"|"-"|"*"|"/"|"%"|"="|"<>"|"<"|"<="|">="|">") ^^ { _.mkString(" ") }
  
  // ------------ System definition
  lazy val system = rep(source) ~ rep(query <~ ";") ^^ { case ss ~ qs => System(ss,qs) }
  def parse(str:String) = phrase(system)(new lexical.Scanner(str)) match {
    case Success(x, _) => x
    case e => sys.error(e.toString)
  }
  def load(path:String) = {
    def f(p:String) = scala.io.Source.fromFile(p).mkString
    parse("(?i)INCLUDE [\"']?([^\"';]+)[\"']?;".r.replaceAllIn(f(path),m=>f(m.group(1))).trim)
  }
}
