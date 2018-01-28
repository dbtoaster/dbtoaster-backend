package ddbt.frontend

import scala.util.parsing.combinator.syntactical.StandardTokenParsers
import scala.util.parsing.combinator.lexical.StdLexical
import ddbt.ast._

/**
  * Define parsers for SQL and M3 languages 
  *
  * @author TCK
  */

class ExtParser extends StandardTokenParsers {

  class CaseInsensitiveLexical extends StdLexical {

    override protected def processIdent(name: String) = {
      val n = name.toLowerCase
      val r = reserved.filter(_.toLowerCase == n)
      if (r.size > 0) Keyword(r.head) else super.processIdent(name)
    }

    import scala.util.parsing.input.CharArrayReader.EofCh
    override def whitespace: Parser[Any] = rep(
      whitespaceChar
      | ('/' ~ '/' | '-' ~ '-') ~ rep(chrExcept(EofCh, '\n'))
      | '/' ~ '*' ~ comment
      | '/' ~ '*' ~ failure("unclosed comment")
    )
  }

  // Add case insensitivity to keywords
  override val lexical: StdLexical = new CaseInsensitiveLexical

  // Allow matching non-reserved keywords
  import scala.language.implicitConversions
  override implicit def keyword(chars: String) = 
    keywordCache.getOrElseUpdate(
      chars,
      acceptIf(_.chars.toLowerCase == chars.toLowerCase)
              (_ => "Expected '" + chars + "'") ^^ 
              (_.chars)
    )

  import lexical._
  //lexical.reserved ++= List("")
  lexical.delimiters ++= List("(", ")", ",", ".", ";", "+", "-", ":=", "<", ">")

  // ------------ Literals
  lazy val longLit = 
    opt("+" | "-") ~ numericLit ^^ { 
      case s ~ n => s.getOrElse("") + n 
    }

  lazy val doubleLit = 
    (longLit <~ ".") ~ opt(numericLit) ~ 
    opt(("E" | "e") ~> longLit) ^^ { 
      case i ~ d ~ e => 
        val f = i + "." + d.getOrElse("") + (e match { 
                                               case Some(j) => "E" + j 
                                               case _ => "" 
                                             })
        if (f.endsWith(".")) f + "0" else f 
    }
 
  // ------------ Types
  lazy val tpe: Parser[Type] = (
    ("string" | ("char" | "varchar") ~> "(" ~> numericLit <~ ")") ^^^ TypeString
    | ("char" | "short" | "int" | "long") ^^^ TypeLong
    | ("float" | "decimal" | "double") ^^^ TypeDouble
    | "date" ^^^ TypeDate
    // | "<" ~> repsep(tpe, ",") <~ ">" ^^ { TypeTuple(_) }
    | failure("Bad type")
  )

  // ------------ Library function (validates name)
  lazy val func: Parser[String] = 
    acceptIf (x => Library(x.chars.toLowerCase)) (x => 
      "No such function '" + x.chars + "'") ^^ (_.chars.toLowerCase)
    
  // ------------ Partitioning information
  lazy val partitioning = 
    ( ("PARTITIONED" ~> "BY" ~> "[" ~> 
       repsep(ident ~ (":" ~> tpe), ",") <~ "]") ^^ { 
        case ks => DistByKeyExp(ks.map { case n ~ t => (n, t) })
      }
    | ("PARTITIONED" ~> "RANDOMLY") ^^^ DistRandomExp
    )

  // ------------ Source declaration
  lazy val source = 
    "CREATE" ~> ("STREAM" | "TABLE") ~ schema ~ ("FROM" ~> sourceIn) ~ 
    split ~ adaptor ~ opt(partitioning) <~ ";" ^^ { 
      case t ~ s ~ i ~ b ~ a ~ p => 
        Source(t == "STREAM", s, i, b, a, p.getOrElse(LocalExp))
    }

  lazy val schema = 
    ident ~ ("(" ~> rep1sep(ident ~ tpe, ",") <~ ")") ^^ { 
      case n ~ f => Schema(n, f map { case n ~ t => (n, t) }) 
    }

  lazy val sourceIn = "FILE" ~> stringLit ^^ { case f => SourceFile(f) }
  
  lazy val split = 
    ( "LINE" ~ "DELIMITED" ^^^ { SplitLine }
    | stringLit <~ "DELIMITED" ^^ { SplitSep(_) }
    | "FIXEDWIDTH" ~> numericLit ^^ { x => SplitSize(Integer.parseInt(x)) }
    | "PREFIX" ~> numericLit ^^ { x => SplitPrefix(Integer.parseInt(x)) }
    )

  lazy val adaptor = 
    ident ~ opt("(" ~> repsep(ident ~ (":=" ~> stringLit), ",") <~ ")") ^^ 
    { case n ~ os => 
        Adaptor(n, os.getOrElse(Nil).map { case x ~ y => (x, y) }.toMap)
    }
}

// -----------------------------------------------------------------------------
// M3 parser

object M3Parser extends ExtParser with (String => M3.System) {

  import M3._

  lexical.delimiters ++= 
    List("{", "}", ":", ":=", "+", "-", "*", "/", "=", "!=", "<", "<=", ">=", ">", "[", "]", "^=", "+=")

  // ------------ Expressions
  lazy val mapref = 
    ident ~ opt("(" ~> tpe <~ ")") ~ ("[" ~> "]" ~> "[" ~> 
    repsep(ident,",") <~ "]") ^^ { case n ~ ot ~ ks => 
      MapRef(n, ot.getOrElse(null), ks.map ((_, null))) 
    }

  lazy val expr: Parser[Expr] = 
    prod ~ opt("+" ~> expr) ^^ { case l ~ or => or match { 
      case Some(r) => Add(l, r) 
      case None => l 
    }}

  lazy val prod: Parser[Expr] = 
    atom ~ opt("*" ~> prod) ^^ { case l ~ or => or match { 
      case Some(r) => Mul(l, r) 
      case None => l 
    }}

  lazy val cond =
    expr ~ ("=" | "!=" | ">" | "<" | ">=" | "<=") ~ expr ^^ {
      case l ~ op ~ r => op match {
        case "="  => Cmp(l, r, OpEq)
        case "!=" => Cmp(l, r, OpNe)
        case ">"  => Cmp(l, r, OpGt)
        case ">=" => Cmp(l, r, OpGe)
        case "<"  => Cmp(r, l, OpGt)
        case "<=" => Cmp(r, l, OpGe)
      }
    }

  lazy val atom = (
      ("AggSum" ~> "(" ~> "[" ~> repsep(ident, ",") <~  "]" <~ ",") ~ 
        expr <~ ")"  ^^ { case ks ~ e => AggSum(ks.map((_, null)), e) }
    | ("EXISTS"|"DOMAIN") ~> "(" ~> expr <~ ")" ^^ { Exists(_) }
    | ("Repartition" ~> "(" ~> "[" ~> repsep(ident, ",") <~  "]" <~ ",") ~ 
        expr <~ ")"  ^^ { case ks ~ e => Repartition(ks.map((_, null)), e) }
    | "Gather" ~> "(" ~> expr <~ ")"  ^^ { Gather(_) }
    | mapref
    | ident ~ ("(" ~> repsep(ident, ",") <~ ")") ^^ { 
        case n ~ f => MapRefConst(n, f.map((_, null))) 
      } // only in map declaration
    | ("(" ~> "DELTA" ~> ident <~ ")") ~ 
      ("(" ~> repsep(ident, ",") <~ ")") ^^ { 
        case n ~ f => DeltaMapRefConst(n, f.map((_, null))) 
      }
    | ("[" ~> "/" ~> ":" ~> tpe <~ "]") ~ 
      ("(" ~> expr <~ ")") ^^ { 
        case t ~ e => Apply("/", t, List(e)) 
      }
    | ("[" ~> func <~ ":") ~ (tpe <~ "]") ~ 
      ("(" ~> repsep(expr,",") <~ ")") ^^ { 
        case n ~ t ~ as => Apply(n, t, as) 
      }
    | "DATE" ~> "(" ~> expr <~ ")" ^^ { 
        case e => Apply("date", TypeDate, List(e)) 
      }
    | ("(" ~> ident <~ "^=") ~ (expr <~ ")") ^^ { 
        case n ~ v => Lift(n,v) 
      }
    | "(" ~> expr <~ ")"
    | "{" ~> (cond | expr) <~ "}" ^^ {
        case c => c
      }
    | "{" ~> expr ~ ("IN" ~> "[" ~> repsep(expr, ",") <~ "]") <~ "}" ^^ {
        case v ~ consts => CmpOrList(v, consts)
      }
    | ident ^^ { Ref(_) }
    | doubleLit ^^ { Const(TypeDouble, _) }
    | longLit ^^ { Const(TypeLong, _) }
    | stringLit ^^ { Const(TypeString, _) }
    // Tupling
    | ("(" ~> "<" ~> repsep(ident,",") <~ ">" <~ "^=") ~ 
      (expr <~ ")") ^^ { case ns ~ v => TupleLift(ns, v) }
    | ("<" ~> repsep(expr, ",") <~ ">") ^^ { Tuple(_) }
    )

  // ------------ System definition
  lazy val map = 
    ("DECLARE" ~> "MAP" ~> ident) ~ opt("(" ~> tpe <~ ")") ~ 
    ("[" ~> "]" ~> "[" ~> repsep(ident ~ (":" ~> tpe), ",") <~ "]") ~ 
    opt(":=" ~> expr) ~ opt(partitioning) <~ ";" ^^ { 
      case n ~ t ~ ks ~ e ~ p => 
        MapDef(n, t.getOrElse(null), ks.map { case n ~ t => (n, t) }, 
               e.getOrElse(null), p.getOrElse(LocalExp))
    }

  lazy val query = 
    ( ("DECLARE" ~> "QUERY" ~> ident <~ ":=") ~ expr <~ ";" ^^ { 
        case n ~ e => Query(n, e) 
      }
    | failure("Bad M3 query")
    )

  lazy val trigger = 
    ( ("ON" ~> ("+" | "-")) ~ ident ~ ("(" ~> rep1sep(ident, ",") <~ ")") ~ 
      ("{" ~> rep(stmt) <~ "}") ^^ { 
        case op ~ n ~ f ~ ss => 
          val s = Schema(n, f.map{ (_,null) })
          Trigger(if (op == "+") EventInsert(s) else EventDelete(s), ss) 
      }
    | "ON" ~> "BATCH" ~> "UPDATE" ~> "OF" ~> ident ~ 
      ("{" ~> rep(stmt) <~ "}") ^^ { 
        case n ~ ss => 
          val s = Schema(n, Nil)
          Trigger(EventBatchUpdate(s), ss) 
      }      
    | "ON" ~> "SYSTEM" ~> "READY" ~> "{" ~> rep(stmt) <~ "}" ^^ { 
        Trigger(EventReady, _) 
      } 
    | failure("Bad M3 trigger")
    )

  lazy val stmt: Parser[Statement] = 
    (
      mapref ~ opt(":" ~> "(" ~> expr <~ ")") ~ ("+=" | ":=") ~ expr <~ ";" ^^ { 
        case m ~ oi ~ op ~ e =>
          TriggerStmt(m, e, op match { case "+=" => OpAdd case ":=" => OpSet }, oi)
      }
    | "if" ~> ("(" ~> cond <~ ")") ~ ("{" ~> rep(stmt) <~ "}") ~ opt("else" ~> "{" ~> rep(stmt) <~ "}") ^^ {
        case c ~ tss ~ ess => 
          IfStmt(c, tss, ess.getOrElse(Nil))
      }
    )

  lazy val system = 
    rep(source) ~ rep(map) ~ rep(query) ~ 
    rep(trigger) ^^ { 
      case ss ~ ms ~ qs ~ ts => System(ss, ms, qs, ts) 
    }

  def load(path: String) = apply(scala.io.Source.fromFile(path).mkString)

  def apply(str: String) = phrase(system)(new lexical.Scanner(str)) match {
    case Success(x, _) => x
    case e => sys.error(e.toString)
  }
}


// -----------------------------------------------------------------------------
// SQL parser

object SQLParser extends ExtParser with (String => SQL.System) {

  import SQL._

  lexical.reserved ++= 
    List("SELECT", "FROM", "WHERE", "GROUP", "LEFT", "RIGHT", 
         "JOIN", "NATURAL", "ON") // reduce this list by conditional accepts

  lexical.delimiters ++= 
    List("+", "-", "*", "/", "%", "=", "<>", "!=", "<", "<=", ">=", ">")

  lazy val field = 
    opt(ident <~ ".") ~ (ident | "*") ^^ { 
      case t ~ n => Field(n, t)
    } // if '*' compute the expansion

  // ------------ Expressions
  lazy val expr = 
    prod ~ rep(("+" | "-") ~ prod) ^^ { 
      case a ~ l => 
        (a /: l) { 
          case (l, o ~ r) => o match { 
            case "+" => Add(l, r) 
            case "-" => Sub(l, r) 
          }
        } 
    }

  lazy val prod = 
    atom ~ rep(("*" | "/" | "%") ~ atom) ^^ { 
      case a ~ l => 
        (a /: l) { 
          case (l, o ~ r) => o match { 
            case "*" => Mul(l, r) 
            case "/" => Div(l, r) 
            case "%" => Mod(l, r) 
          }
        }  
    }

  lazy val atom: Parser[Expr] = 
    ( "COUNT" ~> "(" ~>"DISTINCT" ~> expr <~ ")" ^^ { Agg(_,OpCountDistinct) }
    //| "INTERVAL" ~> stringLit ~ 
    //  ("year" | "month" | "day" | 
    //   "hours" | "minute" | "second") ^^ { case e ~ u => 
    //    Const(e + ";" + u, TypeDate) 
    //   }
    | ( "SUM" ^^^ OpSum 
      | "AVG" ^^^ OpAvg 
      | "COUNT" ^^^ OpCount 
      | "MIN" ^^^ OpMin 
      | "MAX" ^^^ OpMax
      ) ~ ("(" ~> expr <~ ")") ^^ { case f ~ e => Agg(e, f) }
    | ("ALL" | "SOME") ~ ("(" ~> query <~ ")") ^^ { 
        case op ~ e => op match {
          case "ALL"  => All(e) 
          case "SOME" => Som(e) 
        }
      }
    | ( "DATE" 
      | "SUBSTRING" 
      | ("SUBSTR" ^^^ "substring") 
      | "YEAR" 
      | "MONTH" 
      | "DAY"
      | func
      ) ~ ("(" ~> rep1sep(expr, ",") <~ ")") ^^ { 
        case n ~ as => Apply(n.toLowerCase, as) 
      }
    | "CASE" ~> rep1(("WHEN" ~> cond) ~ ("THEN" ~> expr)) ~ 
      ("ELSE" ~> expr) <~ "END" ^^ { 
        case ct ~ e => Case(ct.map{ case c ~ t => (c, t) }.toList, e) 
      }
    | ("CASE" ~> expr) ~ rep1(("WHEN" ~> expr) ~ ("THEN" ~> expr)) ~ 
      ("ELSE" ~> expr) <~ "END" ^^ { 
        case c ~ vt ~ e =>
          Case(vt.map { case v ~ t => (Cmp(c, v, OpEq), t) }.toList, e) 
      }
    | ( ("DATE_PART" ~> "(" ~> stringLit) ~ ("," ~> expr <~ ")") 
      | ("EXTRACT" ~> "(" ~> ident) ~ ("FROM" ~> expr <~ ")")
      ) ^^ { case p ~ e => Apply(p.toLowerCase, List(e)) }
    | field
    | "(" ~> expr <~ ")"
    | "(" ~> query <~ ")" ^^ Nested
    | doubleLit ^^ { Const(_, TypeDouble) }
    | longLit ^^ { Const(_, TypeLong) }
    | stringLit ^^ { Const(_, TypeString) }
    | failure("SQL expression")
    )

  // ------------ Conditions
  def disj = 
    rep1sep(conj, "OR") ^^ { 
      case cs => (cs.head /: cs.tail) ((x, y) => Or(x, y)) 
    }

  def conj = 
    rep1sep(cond, "AND") ^^ { 
      case cs => (cs.head /: cs.tail) ((x, y) => And(x, y)) 
    }

  lazy val cond: Parser[Cond] = 
    ( "EXISTS" ~> "(" ~> query <~ ")" ^^ Exists
    | "NOT" ~> cond ^^ Not
    | expr ~ opt("NOT") ~ 
      ("LIKE" ~> stringLit) ^^ {
        case e ~ o ~ s => o match { 
          case Some(_) => Not(Like(e, s)) 
          case None => Like(e, s) 
      }}
    | expr ~ ("BETWEEN" ~> expr) ~ 
      ("AND" ~> expr) ^^ { 
        case e ~ m ~ n => And(Cmp(e, m, OpGt), Cmp(n, e, OpGt)) 
      }
    | expr ~ (opt("NOT") <~ "IN") ~ query ^^ { 
        case e ~ Some(_) ~ q => Not(In(e, q)) 
        case e ~ None ~ q => In(e,q) 
      }
    | expr ~ 
      ( "=" ^^^ OpEq 
      | "<>" ^^^ OpNe 
      | ">" ^^^ OpGt 
      | ">=" ^^^ OpGe 
      | "!=" ^^^ OpNe
      ) ~ expr ^^ { 
        case l ~ op ~ r => Cmp(l, r, op) 
      }
    | expr ~ ("<" ^^^ OpGt | "<=" ^^^ OpGe) ~ expr ^^ { 
        case l ~ op ~ r => Cmp(r, l, op) 
      }
    | "(" ~> disj <~ ")"
    | failure("SQL condition")
    )

  // ------------ Queries
  lazy val query: Parser[Query] = 
    qconj ~ opt("UNION" ~> opt("ALL") ~ query) ^^ { 
      case q1 ~ Some(a ~ q2) => Union(q1, q2, a.isDefined) 
      case q1 ~ None => q1 
    }

  lazy val qconj: Parser[Query] = 
    qatom ~ opt("INTERSECT" ~> qconj) ^^ { 
      case q1 ~ Some(q2) => Inter(q1,q2) 
      case q1 ~ None => q1 
    }

  lazy val tab: Parser[Table] = 
    ( "(" ~> query <~ ")" ^^ TableQuery | ident ^^ TableNamed) ~ 
    opt(opt("AS") ~> ident) ^^ { 
      case t ~ Some(n) => TableAlias(t, n) 
      case t ~ None => t
    }

  lazy val join: Parser[Table] = 
    tab ~ 
    rep( // joins should be left-associative
      ("NATURAL" ~ "JOIN") ~> tab ^^ { (_, JoinInner, None) }
    | ( opt(
        "LEFT" ^^^ JoinLeft
      | "RIGHT" ^^^ JoinRight
      | "FULL" ^^^ JoinFull
      ) <~ 
      opt("OUTER") <~ "JOIN") ~ tab ~ ("ON" ~> cond) ^^ { 
        case j ~ t ~ c => (t, j.getOrElse(JoinInner), Some(c))
      }
    ) ^^ { 
      case t ~ js => (t /: js) { 
        case (t1, (t2, j, c)) => TableJoin(t1, t2, j, c)
      }
    }

  lazy val alias = 
    expr ~ opt("AS" ~> ident) ^^ { 
      case e ~ o => o match { 
        case Some(n) => Alias(e, n) 
        case None => e 
      } 
    }

  lazy val groupBy = 
    "GROUP" ~> "BY" ~> rep1sep(field, ",") ~ opt("HAVING" ~> disj) ^^ { 
      case fs ~ ho => GroupBy(fs, ho) 
    }

  lazy val orderBy = 
    "ORDER" ~> "BY" ~> rep1sep(field ~ opt("ASC" | "DESC"), ",") ^^ { 
      case fs => OrderBy(fs.map { 
        case f ~ o => (f, o.getOrElse("").toUpperCase == "DESC") 
      }) 
    }

  lazy val qatom: Parser[Query] = 
    ( select
    | opt("LIST") ~> "(" ~> repsep(expr, ",") <~ ")" ^^ { Lst(_) }
    | "(" ~> query <~ ")"
    )

  lazy val select = 
    ("SELECT" ~> opt("DISTINCT")) ~ rep1sep(alias, ",") ~ 
    opt("FROM" ~> repsep(join, ",")) ~ 
    opt("WHERE" ~> disj) ~ 
    opt(groupBy) ~ 
    opt(orderBy) ^^ {
      case d ~ cs ~ ts ~ wh ~ gb ~ ob => 
        Select(d.isDefined, cs, ts.getOrElse(Nil), wh, gb, ob)
    }

  // ------------ System definition
  lazy val system = 
    rep(source) ~ rep(select <~ opt(";")) ^^ { case ss ~ qs => System(ss, qs) }
  
  def apply(str: String) = phrase(system)(new lexical.Scanner(str)) match {
    case Success(x, _) => x
    case e => sys.error(e.toString)
  }

  def load(path: String, base: String = null) = {
    def f(p: String) = 
      scala.io.Source.fromFile(
        (if (base != null) base + "/" else "") + p).mkString
    apply("(?i)INCLUDE [\"']?([^\"';]+)[\"']?;".r.replaceAllIn(
      f(path), 
      m => f(m.group(1))
    ).trim)
  }
}
