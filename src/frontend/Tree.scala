package ddbt.ast

/**
 * This defines the generic nodes that we manipulate during transformations
 * and optimization phases between source SQL and target code.
 * @author TCK
 */

sealed abstract class Tree // Generic AST node

// ---------- Data types
sealed abstract class Type extends Tree
//case object TypeChar   extends Type /*  8 bit */ { override def toString="char" }
//case object TypeShort  extends Type /* 16 bit */ { override def toString="short" }
//case object TypeInt    extends Type /* 32 bit */ { override def toString="int" }
case object TypeLong   extends Type /* 64 bit */ { override def toString="long" }
//case object TypeFloat  extends Type /* 32 bit */ { override def toString="float" }
case object TypeDouble extends Type /* 64 bit */ { override def toString="double" }
case object TypeDate   extends Type              { override def toString="date" }
// case object TypeTime extends Type                { override def toString="timestamp" }
case object TypeString extends Type              { override def toString="string" } // how to encode it?
// case class TypeBinary(maxBytes:Int) extends Type { override def toString="binary("+max+")" } // prefix with number of bytes such that prefix minimize number of bytes used

// ---------- Comparison operators
sealed abstract class OpCmp extends Tree
case object OpEq extends OpCmp { override def toString="=" }
case object OpNe extends OpCmp { override def toString="!=" }
case object OpGt extends OpCmp { override def toString=">" } // OpLt by reversing arguments
case object OpGe extends OpCmp { override def toString=">=" } // OpGe by reversing arguments

// ---------- Statement operators (for maps updates)
sealed abstract class OpUpdate extends Tree
case object OpSet extends OpUpdate { override def toString=":=" }
case object OpAdd extends OpUpdate { override def toString="+=" }

// ---------- Source definitions
case class Source(stream:Boolean, schema:Schema, in:SourceIn, split:Split, adaptor:Adaptor) { override def toString = "CREATE "+(if (stream) "STREAM" else "TABLE")+" "+schema+"\n  FROM "+in+" "+split+" "+adaptor+";" }
case class Schema(name:String, fields:List[(String,Type)]) { override def toString=name+" ("+fields.map(x=>x._1+" "+x._2).mkString(", ")+")" }
case class Adaptor(name:String, options:collection.Map[String,String]) { override def toString=name+(if (options.isEmpty) "" else " ("+options.map{case(k,v)=>k+":='"+v+"'"}.mkString(", ")+")") }

sealed abstract class SourceIn
case class SourceFile(path:String) extends SourceIn { override def toString="FILE '"+path+"'" }
//case class SourcePort(port:Int) // TCP server
//case class SourceRemote(host:String, port:Int, proto:Protocol) proto=bootstrap/authentication protocol (TCP client)

sealed abstract class Split
case object SplitLine extends Split { override def toString="LINE DELIMITED" } // deal with \r, \n and \r\n ?
case class SplitSize(bytes:Int) extends Split { override def toString="FIXEDWIDTH "+bytes }
case class SplitSep(delim:String) extends Split { override def toString="'"+delim+"' DELIMITED" }
//case class SplitPrefix(bytes:Int) extends Split { override def toString="PREFIXED "+bytes } // records are prefixed with their length in bytes

// ---------- Maps declarations
/*
case class MapDef(name:String, tp:Type, keys:List[(String,Type)]) extends Tree {
  var idxs = Set[Int]() // list of secondary indices that are used for slicing
}
*/


// -----------------------------------------------------------------------------
// M3 language

abstract sealed class M3
object M3 {
  def i(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll(" +$","").replace("\n","\n"+i) } // indent

  case class System(sources:List[Source], maps:List[Map], queries:List[Query], triggers:List[Trigger]) extends M3 {
    override def toString =
      "-------------------- SOURCES --------------------\n"+sources.mkString("\n\n")+"\n\n"+
      "--------------------- MAPS ----------------------\n"+maps.mkString("\n\n")+"\n\n"+
      "-------------------- QUERIES --------------------\n"+queries.mkString("\n\n")+"\n\n"+
      "------------------- TRIGGERS --------------------\n"+triggers.mkString("\n\n")
  }
  case class Map(name:String, tp:Type, keys:List[(String,Type)], expr:Expr) extends M3 {
    override def toString="DECLARE MAP "+name+(if (tp!=null)"("+tp+")" else "")+"[]["+keys.map{case (n,t)=>n+":"+t}.mkString(",")+"] :=\n"+i(expr+";")
  }
  case class Query(name:String, m:MapRef) extends M3 { override def toString="DECLARE QUERY "+name+" := "+m+";" }

  // ---------- Triggers
  abstract sealed class Trigger extends M3
  case class TriggerReady(stmts:List[Stmt]) extends Trigger { override def toString="ON SYSTEM READY {\n"+i(stmts.mkString("\n"))+"\n}" }
  case class TriggerAdd(schema:Schema, stmts:List[Stmt]) extends Trigger { override def toString="ON + "+schema.name+" ("+schema.fields.map(x=>x._1).mkString(", ")+") {\n"+i(stmts.mkString("\n"))+"\n}" }
  case class TriggerDel(schema:Schema, stmts:List[Stmt]) extends Trigger { override def toString="ON - "+schema.name+" ("+schema.fields.map(x=>x._1).mkString(", ")+") {\n"+i(stmts.mkString("\n"))+"\n}" }
  // case class TriggerCleanup/Failure/Shutdown/Checkpoint(acts:List[Stmt]) extends Trigger
  
  // ---------- Expressions (values)
  sealed abstract class Expr extends M3
  // Constants
  case class Const(tp:Type,v:String) extends Expr { override def toString=if (tp==TypeString) "'"+v+"'" else v }
  // Variables
  case class Ref(name:String) extends Expr { override def toString=name }
  case class MapRef(name:String, tp:Type, keys:List[String]) extends Expr { override def toString=name+(if (tp!=null)"("+tp+")" else "")+"[]["+keys.mkString(",")+"]" }
  case class Lift(name:String, e:Expr) extends Expr { override def toString="( "+name+" ^= "+e+")" } // 'Let name=e in' semantics (usually followed by * ...)
  case class Tuple(schema:String, proj:List[String]) extends Expr { override def toString=schema+"("+proj.mkString(", ")+")" } // appear only in Map declaration
  // Operations
  case class AggSum(ks:List[String], e:Expr) extends Expr { override def toString="AggSum(["+ks.mkString(",")+"],\n"+i(e.toString)+"\n)" } // returns a {[tuple(group_keys)] => count} relation
  case class Mul(l:Expr,r:Expr) extends Expr { override def toString="("+l+" * "+r+")" } // cross-product semantics
  case class Add(l:Expr,r:Expr) extends Expr { override def toString="("+l+" + "+r+")" } // union semantics
  case class Exists(e:Expr) extends Expr { override def toString="EXISTS("+e+")" } // returns 0 or 1 (check that there is at least one tuple)
  case class Apply(fun:String,tp:Type,args:List[Expr]) extends Expr { override def toString="["+fun+":"+tp+"]("+args.mkString(",")+")" } // function application
  case class Cmp(l:Expr,r:Expr,op:OpCmp) extends Expr { override def toString="{"+l+" "+op+" "+r+"}"} // comparison, returns 0 or 1
  // ---------- Statements (no return)
  sealed class Stmt extends M3
  
  // XXX: missing initialization, see TPCH-13
  case class StmtMap(m:MapRef,e:Expr,op:OpUpdate,init:Option[Expr]) extends Stmt { override def toString=m+(init match { case Some(i) => ":("+i+")" case None => ""} )+" "+op+" "+e+";" }
  // case class StmtCall(external function) extend Stmt
}

// -----------------------------------------------------------------------------
// SQL

abstract sealed class SQL
object SQL {
  case class System(in:List[Source], out:List[SQL.Query]) extends SQL { override def toString = in.mkString("\n\n")+"\n\n"+out.mkString("\n\n"); }
  // ---------- Queries
  abstract sealed class Query extends SQL
  case class View(raw:String) extends Query // SQL query, to be implemented later
  case class Lst(es:List[Expr]) extends Query
  // ---------- Expressions
  abstract sealed class Expr extends SQL
  case class Alias(e:Expr,n:String) extends Expr
  case class Field(n:String,t:String) extends Expr
  case class Const(v:String) extends Expr
  case class Apply(fun:String,args:List[Expr]) extends Expr
  case class Nested(q:Query) extends Expr
  case class Cast(tp:Type,e:Expr) extends Expr
  case class Case(c:Cond,et:Expr,ee:Expr) extends Expr
  case class Substr(e:Expr,start:Int,end:Int= -1) extends Expr
  // ---------- Arithmetic
  case class Add(a:Expr,b:Expr) extends Expr
  case class Sub(a:Expr,b:Expr) extends Expr
  case class Mul(a:Expr,b:Expr) extends Expr
  case class Div(a:Expr,b:Expr) extends Expr
  case class Mod(a:Expr,b:Expr) extends Expr
  // ---------- Aggregation
  sealed abstract class Aggr extends Expr
  case class Min(e:Expr) extends Aggr
  case class Max(e:Expr) extends Aggr
  case class Avg(e:Expr) extends Aggr
  case class Sum(e:Expr) extends Aggr
  case class Count(e:Expr,d:Boolean=false) extends Aggr
  case class All(q:Query) extends Aggr
  case class Som(q:Query) extends Aggr
  // ---------- Conditions
  sealed abstract class Cond
  case class And(a:Cond, b:Cond) extends Cond
  case class Or(a:Cond, b:Cond) extends Cond
  case class Exists(q:Query) extends Cond
  case class In(e:Expr,q:Query) extends Cond
  case class Not(b:Cond) extends Cond
  case class Like(l:Expr,p:String) extends Cond
  case class Range(l:Expr,min:Expr,max:Expr) extends Cond
  case class Cmp(l:Expr, r:Expr, op:OpCmp) extends Cond
};

/*
case class Concat(es:List[Expr]) extends Expr
case class Ceil(e:Expr) extends Expr
case class Floor(e:Expr) extends Expr
// Math
case class Rad(e:Expr) extends Expr
case class Deg(e:Expr) extends Expr
case class Pow(b:Expr, x:Expr) extends Expr
case class Sqrt(e:Expr) extends Expr
case class Cos(e:Expr) extends Expr
case class Sin(e:Expr) extends Expr
// Vectors
case class VecLength(x:Expr,y:Expr,z:Expr) extends Expr
case class VecDot(x1:Expr,y1:Expr,z1:Expr, x2:Expr,y2:Expr,z2:Expr) extends Expr
case class VecAngle(x1:Expr,y1:Expr,z1:Expr, x2:Expr,y2:Expr,z2:Expr) extends Expr
case class DihedralAngle(x1:Expr,y1:Expr,z1:Expr, x2:Expr,y2:Expr,z2:Expr,
                         x3:Expr,y3:Expr,z3:Expr, x4:Expr,y4:Expr,z4:Expr) extends Expr
// Misc
case class Cast(tp:Type,e:Expr) extends Tree
case class Hash(e:Expr) extends Expr
*/

/**
 *** File format definitions
 * FileSQL	:= stream+ sql
 * FileM3	:= /--+/ "SOURCES" /--+/ (stream)+
 *             /--+/ "MAPS" /--+/ (map)+
 *             /--+/ "QUERIES" /--+/ (query)+
 *             /--+/ "TRIGGERS" /--+/ (trigger)+
 *** Stream definition
 * stream := "create" "stream" name "(" field ("," field)* ")" "FROM" source 
 * field  := name type
 * type   := int | float | order | hash | date | string
 * name   := /[a-zA-Z_0-9]+/
 * string := /'[^']*'/
 * source := "FILE" string "LINE" "DELIMITED" format ";"
 * format := ("CSV" | "ORDERBOOK") ("(" (name ":=" string)+ ")")?
 *
 * Note that in M3, fields name is '<table>_<field>'
 *
 *** SQL Query definition
 * sql		:= "SELECT" <XXX> "FROM" <XXX> (WHERE <XXX>)? ("GROUP" "BY" <XXX>)? ";"
 *
 *** M3 common definitions
 * addsum
 * expr
 * stmt
 *
 *** M3 Maps definition
 * map		:= "DECLARE" "MAP" name "(" type ")" "[" "]" "[" name ":" type ("," name ":" type)* "]" := aggsum ";"
 *** M3 Query definition
 * query	:= "DECLARE" "QUERY" name ":=" expr ";"
 *** M3 Trigger definition
 * trigger	:= "ON" ("SYSTEM" READY" | ("+"|"-") name "(" name ("," name)* ")") "{" stmt* "}"
 */
