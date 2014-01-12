package ddbt.frontend

import scala.util.parsing.combinator.syntactical.StandardTokenParsers
import scala.util.parsing.combinator.lexical.StdLexical
import scala.util.parsing.combinator.token.StdTokens
import ddbt.ast._

/**
 * These class define the parsers for SQL and M3 languages into corresponding AST.
 *
 * @author TCK
 */

class ExtParser extends StandardTokenParsers {
  class CaseInsensitiveLexical extends StdLexical {
    override protected def processIdent(name: String) = {
      val n=name.toLowerCase; val r=reserved.filter(x=>x.toLowerCase==n)
      if (r.size>0) Keyword(r.head) else super.processIdent(name)
    }
    import scala.util.parsing.input.CharArrayReader.EofCh
    override def whitespace: Parser[Any] = rep(
      whitespaceChar
    | ('/' ~ '/' | '-' ~ '-') ~ rep( chrExcept(EofCh, '\n') )
    | '/' ~ '*' ~ comment
    | '/' ~ '*' ~ failure("unclosed comment")
    )
  }
  // Add case insensitivity to keywords
  override val lexical:StdLexical = new CaseInsensitiveLexical
  // Allow matching non-reserved keywords
  import scala.language.implicitConversions
  override implicit def keyword(chars: String) = keywordCache.getOrElseUpdate(chars,
    acceptIf(x=>x.chars.toLowerCase==chars.toLowerCase)(x=>"Expected '"+chars+"'") ^^ (_.chars))

  import lexical._
  //lexical.reserved ++= List("")
  lexical.delimiters ++= List("(",")",",",".",";","+","-",":=")

  // ------------ Literals
  lazy val longLit = opt("+"|"-") ~ numericLit ^^ { case s~n => s.getOrElse("")+n }
  lazy val doubleLit = (longLit <~ ".") ~ opt(numericLit) ~ opt(("E"|"e") ~> longLit) ^^ { case i~d~e => val f=i+"."+d.getOrElse("")+(e match { case Some(j)=>"E"+j case _=>"" }); if (f.endsWith(".")) f+"0" else f }

  // ------------ Types
  lazy val tpe: Parser[Type] = (("string" | ("char"|"varchar") ~> "(" ~> numericLit <~  ")") ^^^ TypeString
  | ("char"|"short"|"int"|"long") ^^^ TypeLong //| "char" ^^^ TypeChar | "short" ^^^ TypeShort | "int" ^^^ TypeInt | "long" ^^^ TypeLong
  | ("float"|"decimal"|"double") ^^^ TypeDouble // | ("float"|"decimal") ^^^ TypeFloat | "double" ^^^ TypeDouble
  | "date" ^^^ TypeDate | failure("Bad type")
  )

  // ------------ Source declaration
  lazy val source = "CREATE" ~> ("STREAM"|"TABLE") ~ schema ~ ("FROM" ~> sourceIn) ~ split ~ adaptor <~ ";" ^^ { case t~s~i~b~a => Source(t=="STREAM",s,i,b,a) }
  lazy val schema = ident ~ ("(" ~> rep1sep(ident ~ tpe, ",") <~ ")") ^^ { case n~f => Schema(n,f.map{case n~t=>(n,t)}) }
  lazy val sourceIn = "FILE" ~> stringLit ^^ { case f => SourceFile(f) }
  lazy val split = (
    "LINE" ~ "DELIMITED" ^^^ { SplitLine }
  | stringLit <~ "DELIMITED" ^^ { SplitSep(_) }
  | "FIXEDWIDTH" ~> numericLit ^^ { x => SplitSize(Integer.parseInt(x)) }
  | "PREFIX" ~> numericLit ^^ { x => SplitPrefix(Integer.parseInt(x)) }
  )
  lazy val adaptor = ident ~ opt("(" ~> repsep(ident ~ (":=" ~> stringLit),",") <~ ")") ^^ { case n~os =>
    Adaptor(n,os.getOrElse(Nil).map{case x~y => (x,y) }.toMap)
  }
}

// -----------------------------------------------------------------------------
// M3 parser

object M3Parser extends ExtParser with (String => M3.System) {
  import ddbt.ast.M3._
  lexical.delimiters ++= List("{","}",":",":=","+","-","*","/","=","!=","<","<=",">=",">","[","]","^=","+=")

  // ------------ Expressions
  lazy val mapref = ident ~ opt("(" ~> tpe <~ ")") ~ ("[" ~> "]" ~> "[" ~> repsep(ident,",") <~ "]") ^^
                    { case n~ot~ks=>MapRef(n,ot.getOrElse(null),ks) }

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
  | doubleLit ^^ { Const(TypeDouble,_) }
  | longLit ^^ { Const(TypeLong,_) }
  | stringLit ^^ { Const(TypeString,_) }
  )

  // ------------ System definition
  lazy val map = ("DECLARE" ~> "MAP" ~> ident) ~ opt("(" ~> tpe <~ ")") ~ ("[" ~> "]" ~> "[" ~> repsep(ident ~ (":" ~> tpe),",") <~ "]" <~ ":=") ~ expr <~ ";" ^^
                 { case n~t~ks~e => MapDef(n,t.getOrElse(null),ks.map{case n~t=>(n,t)},e) }
  lazy val query = ("DECLARE" ~> "QUERY" ~> ident <~ ":=") ~ mapref <~ ";" ^^ { case n~m=>Query(n,m) } | failure("Bad M3 query")
  lazy val trigger = (("ON" ~> ("+"|"-")) ~ ident ~ ("(" ~> rep1sep(ident, ",") <~ ")") ~ ("{" ~> rep(stmt) <~ "}") ^^
                        { case op~n~f~ss=> val s=Schema(n,f.map{(_,null)}); Trigger(if (op=="+") EvtAdd(s) else EvtDel(s),ss) }
                     | "ON" ~> "SYSTEM" ~> "READY" ~> "{" ~> rep(stmt) <~ "}" ^^ { Trigger(EvtReady,_) } | failure("Bad M3 trigger"))
  lazy val stmt = mapref ~ opt(":" ~> "(" ~> expr <~ ")") ~ ("+="|":=") ~ expr <~ ";" ^^ { case m~oi~op~e=>StmtMap(m,e,op match { case "+="=>OpAdd case ":="=>OpSet },oi) }

  lazy val system = rep(source) ~ rep(map) ~ rep(query) ~ rep(trigger) ^^ { case ss~ms~qs~ts => System(ss,ms,qs,ts) }

  def load(path:String) = apply(scala.io.Source.fromFile(path).mkString)
  def apply(str:String) = phrase(system)(new lexical.Scanner(str)) match {
    case Success(x, _) => x
    case e => sys.error(e.toString)
  }
}

// -----------------------------------------------------------------------------
// SQL parser

object SQLParser extends ExtParser with (String => SQL.System) {
  import ddbt.ast.SQL._
  lexical.reserved ++= List("SELECT","FROM","WHERE","GROUP","LEFT","RIGHT","JOIN","NATURAL","ON") // reduce this list by conditional accepts
  lexical.delimiters ++= List("+","-","*","/","%","=","<>","!=","<","<=",">=",">")
  lazy val field = opt(ident<~".")~(ident|"*") ^^ { case t~n => Field(n,t.getOrElse(null)) } // if '*' compute the expansion

  // ------------ Expressions
  lazy val expr = prod ~ rep(("+"|"-") ~ prod) ^^ { case a~l => (a/:l) { case (l,o~r)=> o match { case "+" => Add(l,r) case "-" => Sub(l,r) }} }
  lazy val prod = atom ~ rep(("*"|"/"|"%") ~ atom) ^^ { case a~l => (a/:l) { case (l,o~r)=> o match { case "*" => Mul(l,r) case "/" => Div(l,r) case "%" => Mod(l,r) }} }
  lazy val atom:Parser[Expr] = (
    "COUNT" ~> "(" ~>"DISTINCT" ~> expr <~ ")" ^^ { Agg(_,OpCountDistinct) }
  | ("SUM"^^^OpSum|"AVG"^^^OpAvg|"COUNT"^^^OpCount|"MIN"^^^OpMin|"MAX"^^^OpMax) ~ ("(" ~> expr <~ ")") ^^ { case f~e => Agg(e,f) }
  | ("ALL"|"SOME") ~ ("(" ~> query <~ ")") ^^ { case op~e => op match { case "ALL"=> All(e) case "SOME"=> Som(e) } }
  | ("DATE"|"SUBSTRING"|("SUBSTR"^^^"substring")|"YEAR"|"MONTH"|"DAY"|"vec_length"|"dihedral_angle"|"listmin"|"listmax") ~ ("(" ~> rep1sep(expr,",") <~ ")") ^^ { case n~as => Apply(n.toLowerCase,as) }
  | "CASE"~> rep1(("WHEN"~>cond) ~ ("THEN"~>expr)) ~ ("ELSE"~>expr) <~"END" ^^ { case ct~e=>Case(ct.map{case c~t => (c,t)}.toList,e) }
  | ("CASE"~>expr) ~ rep1(("WHEN"~>expr) ~ ("THEN"~>expr)) ~ ("ELSE"~>expr) <~"END" ^^ { case c~vt~e=>Case(vt.map{ case v~t => (Cmp(c,v,OpEq),t)}.toList,e) }
  | ( ("DATE_PART"~>"("~>stringLit)~(","~>expr<~")") | ("EXTRACT"~>"("~>ident)~("FROM"~>expr<~")")) ^^ { case p~e => Apply(p.toLowerCase,List(e)) }
  | field
  | "(" ~> expr <~ ")"
  | "(" ~> query <~ ")" ^^ Nested
  | doubleLit ^^ { Const(_,TypeDouble) }
  | longLit ^^ { Const(_,TypeLong) }
  | stringLit ^^ { Const(_,TypeString) }
  | failure("SQL expression")
  )

  // ------------ Conditions
  def disj = rep1sep(conj,"OR") ^^ { case cs => (cs.head/:cs.tail)((x,y)=>Or(x,y)) }
  def conj = rep1sep(cond,"AND") ^^ { case cs => (cs.head/:cs.tail)((x,y)=>And(x,y)) }
  lazy val cond:Parser[Cond] = (
    "EXISTS" ~> "(" ~> query <~ ")" ^^ Exists
  | "NOT" ~> cond ^^ Not
  | expr ~ opt("NOT") ~ ("LIKE" ~> stringLit) ^^ { case e~o~s => o match { case Some(_)=>Not(Like(e,s)) case None=>Like(e,s) } }
  | expr ~ ("BETWEEN" ~> expr) ~ ("AND" ~> expr) ^^ { case e~m~n => And(Cmp(e,m,OpGt),Cmp(n,e,OpGt)) }
  | expr ~ (opt("NOT") <~ "IN") ~ query ^^ { case e~Some(_)~q => Not(In(e,q)) case e~None~q => In(e,q) }
  | expr ~ ("="^^^OpEq|"<>"^^^OpNe|">"^^^OpGt|">="^^^OpGe|"!="^^^OpNe) ~ expr ^^ { case l~op~r => Cmp(l,r,op) }
  | expr ~ ("<"^^^OpGt|"<="^^^OpGe) ~ expr ^^ { case l~op~r => Cmp(r,l,op) }
  | "(" ~> disj <~ ")"
  | failure("SQL condition")
  )

  // ------------ Queries
  lazy val query:Parser[Query] = qconj ~ opt("UNION"~>opt("ALL")~query) ^^ { case q1~Some(a~q2) => Union(q1,q2,a.isDefined) case q1~None => q1 }
  lazy val qconj:Parser[Query] = qatom ~ opt("INTERSECT"~>qconj) ^^ { case q1~Some(q2) => Inter(q1,q2) case q1~None => q1 }

  lazy val tab:Parser[Table] = ("(" ~> query <~ ")" ^^ TableQuery | ident ^^ TableNamed) ~ opt(opt("AS")~>ident) ^^ { case t~Some(n) => TableAlias(t,n) case t~None => t}
  lazy val join:Parser[Table] = tab ~ rep( // joins should be left-associative
      ("NATURAL"~"JOIN") ~> tab ^^ { (_,JoinInner,null) }
    | (opt("LEFT"^^^JoinLeft|"RIGHT"^^^JoinRight|"FULL"^^^JoinFull)<~opt("OUTER")<~"JOIN")~tab~("ON"~>cond) ^^ { case j~t~c => (t,j.getOrElse(JoinInner),c) }
    ) ^^ { case t~js => (t/:js) { case (t1,(t2,j,c)) => TableJoin(t1,t2,j,c) }}

  lazy val alias = expr ~ opt("AS"~>ident) ^^ { case e~o => o match { case Some(n) => Alias(e,n) case None => e } }
  lazy val groupBy = "GROUP"~>"BY"~>rep1sep(field,",") ~ opt("HAVING"~>disj) ^^ { case fs~ho => GroupBy(fs,ho.getOrElse(null)) }
  lazy val orderBy = "ORDER"~>"BY"~>rep1sep(field~opt("ASC"|"DESC"),",") ^^ { case fs => OrderBy(fs.map{ case f~o => (f,o.getOrElse("").toUpperCase=="DESC") }) }

  lazy val qatom:Parser[Query] = (
    select
  | opt("LIST")~>"("~>repsep(expr,",")<~")" ^^ { Lst(_) }
  | "(" ~> query <~ ")"
  )
  lazy val select = ("SELECT" ~> opt("DISTINCT")) ~ rep1sep(alias,",") ~ opt("FROM" ~> repsep(join,",")) ~ opt("WHERE" ~> disj) ~ opt(groupBy) ~ opt(orderBy) ^^ {
    case d~cs~ts~wh~gb~ob => Select(d.isDefined,cs,ts.getOrElse(Nil),wh.getOrElse(null),gb.getOrElse(null),ob.getOrElse(null)) }

  // ------------ System definition
  lazy val system = rep(source) ~ rep(select <~ opt(";")) ^^ { case ss ~ qs => System(ss,qs) }
  def apply(str:String) = phrase(system)(new lexical.Scanner(str)) match {
    case Success(x, _) => x
    case e => sys.error(e.toString)
  }
  def load(path:String,base:String=null) = {
    def f(p:String) = scala.io.Source.fromFile((if (base!=null) base+"/" else "")+p).mkString
    apply("(?i)INCLUDE [\"']?([^\"';]+)[\"']?;".r.replaceAllIn(f(path),m=>f(m.group(1))).trim)
  }
}
