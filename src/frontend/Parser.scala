package ddbt.frontend

import scala.util.parsing.combinator.syntactical.StandardTokenParsers
import scala.util.parsing.combinator.lexical.StdLexical
import scala.util.parsing.combinator.token.StdTokens

object Parser extends StandardTokenParsers {
  // add case insensitivity to keywords
  var caseSensitive = false
  override val lexical = new StdLexical {
    override protected def processIdent(name: String) = if (!caseSensitive) {
      val n=name.toLowerCase; val r=reserved.filter(x=>x.toLowerCase==n)
      if (r.size>0) Keyword(r.head) else super.processIdent(name)
    } else super.processIdent(name)
  }
  // allow matching non-reserved keywords
  import scala.language.implicitConversions
  override implicit def keyword(chars: String): Parser[String] = keywordCache.getOrElseUpdate(chars,
    acceptIf(x=> if (caseSensitive) x.chars==chars else x.chars.toLowerCase==chars.toLowerCase)(x=>"Expected '"+chars+"'") ^^ (_.chars))

  //lexical.reserved ++= List("SOURCES","MAPS","CREATE","STREAM","float","int","FROM","FILE","LINE","DELIMITED","DECLARE","MAP")
  //lexical.reserved ++= List("AggSum","Exists")
  //lexical.reserved ++= List("CREATE","STREAM","char","short","int","long","float","double","date","string","FROM","FILE") // "E","e","D","S","L","IF","THEN","ELSE","AND","OR","NOT","LIKE","IN","NOT","YEAR","MONTH","DAY","SUBSTR","CONCAT","CEIL","FLOOR"
  
  lexical.delimiters ++= List("(",")","{","}",",",";",":",":=",".","+","-","*","/","%","=","<>","!=","<","<=",">=",">","[","]","^=","+=") // ,"!"
  import lexical.NumericLit
  import lexical.StringLit
  import lexical._
  import ddbt.ast._

  def tpe: Parser[Type] = (
    "char" ~> "(" ~> numericLit <~  ")" ^^ { n => TypeChar(Integer.parseInt(n)) }
  | "varchar" ~> "(" ~> numericLit <~  ")" ^^ { n=> TypeVarchar(Integer.parseInt(n)) }
  | "string" ^^^ TypeString
  | "char" ^^^ TypeChar | "short" ^^^ TypeShort | "int" ^^^ TypeInt | "long" ^^^ TypeLong | ("float"|"decimal") ^^^ TypeFloat | "double" ^^^ TypeDouble | "date" ^^^ TypeDate | failure("Bad type"))

  // XXX: replace by lazy vals

  // ------------ Source declaration
  def source(sql:Boolean=false) = "CREATE" ~> ("STREAM"|"TABLE") ~ schema(sql) ~ ("FROM" ~> sourcein) ~ split ~ adaptor <~ ";" ^^ { case t~s~i~b~a => Source(t=="STREAM",s,i,b,a) }
  def schema(sql:Boolean=false) = ident ~ ("(" ~> repsep(ident ~ tpe, ",") <~ ")") ^^ { case n~f => Schema(n,f.map{case n~t=>(n,t)}) }
  lazy val sourcein:Parser[SourceIn] = "FILE" ~> stringLit ^^ { case f => SourceFile(f) }
  lazy val split:Parser[Split] = (
    "LINE" ~ "DELIMITED" ^^^ { SplitLine }
  | stringLit <~ "DELIMITED" ^^ { SplitSep(_) }
  | "FIXEDWIDTH" ~> numericLit ^^ { case x => SplitSize(Integer.parseInt(x)) }
  //| "PREFIX" ~> numericLit ^^ { ByPrefix(Integer.parseInt(_)) }
  )
  lazy val adaptor = ident ~ opt("(" ~> repsep(ident ~ (":=" ~> stringLit),",") <~ ")") ^^ { case n~oos =>
    Adaptor(n,oos match { case Some(os)=> os.map{case x~y => (x,y) }.toMap case None=>List[(String,String)]().toMap })
  }
  
  
  
  lazy val sql = "SELECT" ~> sqlAny <~ ";" ^^ { case s =>
   SQL(s)
  }
  lazy val sqlAny = rep(ident|numericLit|stringLit|"."|","|"("|")"|"+"|"-"|"*"|"/"|"%"|"="|"<>"|"<"|"<="|">="|">") ^^ { _.mkString(" ") }
  

  // ------------ Map declaration

  lazy val long = opt("+"|"-") ~ numericLit ^^ { case s~n => Const((s match { case Some("-") => "-" case _ => ""})+n) }
  lazy val double = (long <~ ".") ~ opt(numericLit) ~ opt(("E"|"e") ~> long)  ^^ { case i ~ d ~ e => Const(i+"."+(d match { case Some(s)=>s case None=>"" })+(e match { case Some(j)=>"E"+j case _=>"" })) }
  lazy val tuple = ident ~ ("(" ~> repsep(ident, ",") <~ ")") ^^ { case n~f => Tuple(n,f) }
  lazy val mapref = ident ~ opt("(" ~> tpe <~ ")") ~ ("[" ~> "]" ~> "[" ~> repsep(ident,",") <~ "]") <~ opt(":" ~ "(" ~ expr ~ ")") ^^ { case n~ot~ks=>MapRef(n,ot match { case Some(t)=>t case None=>null },ks) }

  lazy val atom = (
    ("AggSum" ~> "(" ~> "[" ~> repsep(ident,",") <~  "]" <~ ",") ~ expr <~ ")"  ^^ { case ks~e => AggSum(ks,e) }
  | mapref
  | tuple
  | ("[" ~> "/" ~> ":" ~> tpe <~ "]") ~ ("(" ~> expr <~ ")") ^^ { case t~e => Cast(t,e) }
  | ("[" ~> ident <~ ":") ~ (tpe <~ "]") ~ ("(" ~> repsep(expr,",") <~ ")") ^^ { case n~t~as => Apply(n,t,as) }
  | "EXISTS" ~> "(" ~> expr <~ ")" ^^ { Exists(_) }
  | "DATE" ~> "(" ~> expr <~ ")" ^^ { Cast(TypeDate,_) }
  | ("(" ~> ident <~ "^=") ~ (expr <~ ")") ^^ { case n~v => Let(n,v) }
  |  "(" ~> expr <~ ")"
  | "{" ~> cond <~ "}" ^^ { case c=> CondVal(c) }
  | ident ^^ { Val(_) }
  | double | long | stringLit ^^ { Const(_) }
  )
  
  lazy val prod:Parser[Expr] = atom ~ opt("*" ~> prod) ^^ { case l~or=>or match{ case Some(r)=>Mul(l,r) case None=>l } }
  lazy val expr:Parser[Expr] = prod ~ opt("+" ~> expr) ^^ { case l~or=>or match{ case Some(r)=>Add(l,r) case None=>l } }
  
  lazy val cond:Parser[Cond] = (
    expr ~ ("="|"<>"|">"|"<"|">="|"<="|"!=") ~ expr ^^ { case l~op~r => op match {
      case "="=>CmpEq(l,r) case "<>"|"!="=>CmpNe(l,r) case ">"=>CmpGt(l,r) case ">="=>CmpGe(l,r) case "<"=>CmpLt(l,r) case "<="=>CmpLe(l,r) }
    }
  | expr ^^ { case e=>CmpNe(e,Val("0")) }
  )
  
  lazy val stmt = (
    (mapref <~ "+=") ~  expr <~ ";" ^^ { case m~e=>StAdd(m,e) }
  | (mapref <~ ":=") ~  expr <~ ";" ^^ { case m~e=>StSet(m,e) }
  )
  
  
  lazy val query = ("DECLARE" ~> "QUERY" ~> ident <~ ":=") ~ mapref <~ ";" ^^ { case n~m=>Query(n,m) }
  
  lazy val trigger = (
    ("ON" ~> ("+"|"-")) ~ tuple ~ ("{" ~> rep(stmt) <~ "}") ^^ { case op~t~ss=> if (op=="+") TriggerAdd(t,ss) else TriggerDel(t,ss) }
  | "ON" ~> "SYSTEM" ~> "READY" ~> "{" ~> rep(stmt) <~ "}" ^^ { TriggerInit(_) }
  )
  
  lazy val map : Parser[Map] = ("DECLARE" ~> "MAP" ~> ident) ~ opt("(" ~> tpe <~ ")") ~
    ("[" ~> "]" ~> "[" ~> repsep(ident ~ (":" ~> tpe),",") <~ "]" <~ ":=") ~ expr <~ ";" ^^ { case n ~ t ~ ks ~ e => Map(n,t match { case Some(t)=>t case None=>null},ks.map{case n~t=>(n,t)},e) }
  
  lazy val defSQL : Parser[DefSQL] = rep(source(true)) ~ rep(sql) ^^ { case ss ~ qs => DefSQL(ss,qs) }
  lazy val defM3 : Parser[DefM3] = {
    val spc = ("-"~"-"~rep("-"))
    ((spc ~ "SOURCES" ~ spc) ~> rep(source(false))) ~
    ((opt(spc) ~ "MAPS" ~ spc) ~> rep(map)) ~
    ((opt(spc) ~ "QUERIES" ~ spc) ~> rep(query)) ~
    ((spc ~ "TRIGGERS" ~ spc) ~> rep(trigger)) ^^ { case ss ~ ms ~ qs ~ ts => DefM3(ss, ms, qs, ts) }
  }
  
  // Externally accessible
  def parseSQL(str:String):DefSQL = {
    val tokens = new lexical.Scanner(str);
    phrase(defSQL)(tokens) match {
      case Success(x, _) => x
      case e => sys.error(e.toString)
    }
  }

  def parseM3(str:String):DefM3 = {
    val tokens = new lexical.Scanner(str);
    phrase(defM3)(tokens) match {
      case Success(x, _) => x
      case e => sys.error(e.toString())
    }
  }

  def loadM3(path:String):DefM3 = parseM3(scala.io.Source.fromFile(path).mkString)
  def loadSQL(path:String):DefSQL = {
    def f(p:String) = scala.io.Source.fromFile(p).mkString
    parseSQL("(?i)INCLUDE [\"']?([^\"';]+)[\"']?;".r.replaceAllIn(f(path),m=>f(m.group(1))).trim)
  }



}
/*
object Parser extends StandardTokenParsers {
  lexical.delimiters ++= List("(", ")","<","<=",">=",">","=","<>",".","+","-","*","/","%",",","!")
  lexical.reserved ++= List("E","e","D","S","L","IF","THEN","ELSE","AND","OR","NOT","LIKE","IN","NOT","YEAR","MONTH","DAY","SUBSTR","CONCAT","CEIL","FLOOR")
  import lexical.NumericLit
  import lexical.StringLit
  import m2.data.Table.Type
  import m2.data.Filter._
  import m2.data.Expr._

  // Relations naming store
  val tables = new HashMap[String,Table]()
  def addTable(name:String, descr:String) = tables.synchronized { tables.put(name, new Table(name, descr)) }
  def getTable(name:String):Table = { val p=name.indexOf("_"); var t=tables.get(name); if (t==null && -1!=p) t=tables.get(name.substring(0,p)); t; }

   * type    ::= "D" | "S" | "L"                           types: double, string, long
   * str     ::= "'" [^']* "'"                             quoted string
   * long    ::= ("-"|"+")? [0-9]+                         formatted integer
   * double  ::= long "." [0-9]+ (("E"|"e") long)?         formatted double
   * col     ::= [0-9]+                                    column index
   * op      ::= "<" | "<=" | ">" | ">=" | "=" | "<>"      comparison operator
   * list    ::= "(" (str ("," str)* )? ")"                list of comma separated strings
   *
   * exprList::= "!" ? expr ("," "!"? expr )*              expression list (possibly inverted)
   * expr    ::= term ( ("+" | "-") term )?                expression
   * term    ::= atom ( ("*" | "/") atom )?
   * atom    ::= "(" expr ")"                              parenthesis
   *           | type col                                  tuple column
   *           | long | double | str                       immediate value
   *           | "IF" disj "THEN" expr "ELSE" expr         ternary operator
   *           | ("YEAR"|"MONTH"|"DAY") "(" expr ")"       date operations
   *           | ("CEIL"|"FLOOR") "(" expr ")"             ceil/floor
   *           | "SUBSTR" "(" expr "," long ("," long)? ")"
   *           | "CONCAT" "(" exprList ")"                 concatenation
   *
   * disj    ::= conj ("OR" conj)?                         disjunction
   * conj    ::= cmp ("AND" cmp)?                          conjunction
   * cmp     ::= "(" disj ")"                              parenthesis
   *           | expr op expr                              comparison
   *           | expr "NOT"? "IN" list                     set inclusion/exclusion
   *           | expr "LIKE" str                           pattern matching
  

  Simple values
  def long : Parser[java.lang.Long] = opt("+"|"-") ~ numericLit ^^ { case s ~ n =>
    (s match { case Some("-") => -1L case _ => 1L}) * java.lang.Long.parseLong(n.toString())
  }
  def double : Parser[Double] = (long <~ ".") ~ numericLit ~ opt(("E"|"e") ~> long)  ^^ {
    case i ~ d ~ e => java.lang.Double.parseDouble(i+"."+d.toString()+(e match { case Some(j) => "E"+j case _ => "" }))
  }

  Expressions
  def exprList(t:Table) : Parser[Array[Expr]] = repsep(invExpr(t),",") ^^ { case es => es.toArray }
  def invExpr(t:Table) : Parser[Expr] = opt("!") ~ expr(t) ^^ { case Some(_)~e => new Invert(e) case None ~ e=>e }

  def expr(t:Table) : Parser[Expr] = term(t) ~ rep(("+"|"-") ~ term(t)) ^^ { case f~l =>
    (f /: l){ case (t1,o~t2)=>o match { case "+" => new Add(t1,t2) case "-" => new Sub(t1,t2) }}
  }
  def term(t:Table) : Parser[Expr] = atom(t) ~ rep(("*"|"/"|"%") ~ atom(t)) ^^ { case a ~ l => (a /: l) { case (t1,o~t2)=> o match {
    case "*" => new Mul(t1,t2) case "/" => new Div(t1,t2) case "%" => new Mod(t1,t2) }}
  }
  def atom(t:Table) : Parser[Expr] = ("(" ~> expr(t) <~ ")" ^^ { case x=>x }
    | ident ^^ { case n => val i:Int=if (t==null) -1 else t.idx(n); if (-1!=i) new Col(t.getType(i), i)
      else new Col(Type.get(n.substring(0,1)),Integer.parseInt(n.substring(1))) }
    | ("D"|"S"|"L") ~ numericLit ^^ { case tp ~ c => new Col(Type.get(tp),Integer.parseInt(c.toString())) }
    | double ^^ { x => new Const(x) } | long ^^ { x => new Const(x) } | stringLit ^^ { x=> new Const(x) }
    | ("IF" ~> disj(t)) ~ ("THEN" ~> expr(t)) ~ ("ELSE" ~> expr(t)) ^^ { case c ~ t ~ e => if (t.tp!=e.tp) sys.error("No type match"); new Cond(t.tp,c,t,e) }
    | ("YEAR"|"MONTH"|"DAY"|"CEIL"|"FLOOR") ~ ("(" ~> expr(t) <~ ")") ^^ { case t ~ e => t.toString match {
      case "YEAR" => new Year(e) case "MONTH" => new Month(e) case "DAY" => new Day(e)
      case "CEIL" => new Ceil(e) case "FLOOR" => new Floor(e) }}
    | ("SUBSTR" ~> "(" ~> expr(t)) ~ ("," ~> long) ~ (opt("," ~> long) <~ ")") ^^ { case e ~ n ~ o => val s=Integer.parseInt(n.toString());
      o match { case Some(n2) => new Substr(e,s,Integer.parseInt(n2.toString)) case None => new Substr(e,s) }}
    | "CONCAT" ~> "(" ~> exprList(t) <~ ")" ^^ { es => new Concat(es) }
    | failure("illegal expression")
  )

  Disjunction
  def disj(t:Table) : Parser[Filter] = repsep(conj(t),"OR") ^^ { case cs => val css = cs.sortWith((x,y)=>x.cost>y.cost);
    css match { case x::xs => (x/:xs)((x,y)=>new Or(y,x)) case Nil=>null }}
  Conjunction
  def conj(t:Table) : Parser[Filter] = repsep(cmp(t),"AND") ^^ { case cs => val css = cs.sortWith((x,y)=>x.cost>y.cost);
    css match { case x::xs => (x/:xs)((x,y)=>new And(y,x)) case Nil=>null }}
  Comparison filter
  def cmp(t:Table) : Parser[Filter] = (
      "(" ~> disj(t) <~ ")" ^^ { x=>x }
    | "NOT" ~> ("(" ~> disj(t) <~ ")" | disj(t)) ^^ { case e1 => new Not(e1) }
    | expr(t) ~ ("<"|"<="|">="|">"|"="|"<>") ~ expr(t) ^^ { case e1 ~ o ~ e2 => new Compare(e1,Op.get(o),e2) }
    | expr(t) ~ opt("NOT") ~ ("IN" ~> "(" ~> repsep(stringLit,",") <~ ")") ^^ { case  e ~ o ~ lst =>
      val set = new HashSet[String](); lst.map(x=>set.add(x)); new Contain(e,o match {case Some(_)=>true case None=>false},set) }
    | expr(t) ~ opt("NOT") ~ ("IN" ~> "(" ~> repsep(long,",") <~ ")") ^^ { case  e ~ o ~ lst =>
      val set = new HashSet[String](); lst.map(x=>set.add(x.toString())); new Contain(e,o match {case Some(_)=>true case None=>false},set) }
    | expr(t) ~ ("LIKE" ~> stringLit) ^^ { case e ~ p => new Like(e,p.toString()) }
    | failure("illegal filter")
  )

  def parseFilter(str:String):Filter = parseFilter(null,str)
  private def parseFilter(t:Table, str:String):Filter = {
    val tokens = new lexical.Scanner(str);
    phrase(disj(t))(tokens) match {
      case Success(filter, _) => filter
      case e => sys.error(e.toString())
    }
  }

  def parseExpr(str:String):Expr = parseExpr(null,str)
  private def parseExpr(t:Table, str:String):Expr = {
    val tokens = new lexical.Scanner(str);
    phrase(expr(t))(tokens) match {
      case Success(x, _) => x
      case e => sys.error(e.toString())
    }
  }

  def parseExprList(str:String):Array[Expr] = parseExprList(null,str)
  private def parseExprList(t:Table, str:String):Array[Expr] = {
    val tokens = new lexical.Scanner(str);
    phrase(exprList(t))(tokens) match {
      case Success(x, _) => x
      case e => sys.error(e.toString())
    }
  }

  def resolveExpr(t:String, str:String):Expr = parseExpr(getTable(t),str);
  def resolveFilter(t:String, str:String):Filter = parseFilter(getTable(t),str);
  def resolveProj(t:String, str:String):Array[Expr] = parseExprList(getTable(t),str)
}
*/
