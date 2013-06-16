package ddbt.ast

sealed abstract class Tree // Generic AST node

// ---------- Data types
sealed abstract class Type extends Tree
case object TypeChar   extends Type /*  8 bit */ { override def toString="char" }
case object TypeShort  extends Type /* 16 bit */ { override def toString="short" }
case object TypeInt    extends Type /* 32 bit */ { override def toString="int" }
case object TypeLong   extends Type /* 64 bit */ { override def toString="long" }
case object TypeFloat  extends Type /* 32 bit */ { override def toString="float" }
case object TypeDouble extends Type /* 64 bit */ { override def toString="double" }
case object TypeDate   extends Type              { override def toString="date" }
case object TypeString extends Type              { override def toString="string" }
case class  TypeChar(n:Int) extends Type         { override def toString="char("+n+")" }
case class  TypeVarchar(n:Int) extends Type      { override def toString="varchar("+n+")" }

// ---------- Source definitions
case class Source(stream:Boolean, schema:Schema, in:SourceIn, split:Split, adaptor:Adaptor) { override def toString = "CREATE "+(if (stream) "STREAM" else "TABLE")+" "+schema+"\n  FROM "+in+" "+split+" "+adaptor+";" }
case class Schema(name:String, fields:List[(String,Type)]) { override def toString=name+" ("+fields.map(x=>x._1+" "+x._2).mkString(", ")+")" }
case class Adaptor(name:String, options:collection.Map[String,String]) { override def toString=name+(if (options.isEmpty) "" else " ("+options.map{case(k,v)=>k+":='"+v+"'"}.mkString(", ")+")") }

sealed abstract class SourceIn
case class SourceFile(path:String) extends SourceIn { override def toString="FILE '"+path+"'" }
//case class SourcePort(port:Int)
//case class SourceRemote(host:String, port:Int, proto:Protocol) proto=bootstrap/authentication protocol

sealed abstract class Split
case object SplitLine extends Split { override def toString="LINE DELIMITED" } // deal with \r, \n and \r\n ?
case class SplitSize(bytes:Int) extends Split { override def toString="FIXEDWIDTH "+bytes }
case class SplitSep(delim:String) extends Split { override def toString="'"+delim+"' DELIMITED" }
//case class SplitPrefix(bytes:Int) extends Split { override def toString="PREFIXED "+bytes } // records are prefixed with their length in bytes

// ---------- System definition (file format)
// SQL
case class DefSQL(in:List[Source], out:List[SQL]) extends Tree { override def toString = in.mkString("\n\n")+"\n\n"+out.mkString("\n\n"); }
// M3
case class DefM3(in:List[Source], maps:List[Map], queries:List[Query], triggers:List[Trigger]) extends Tree {
  override def toString =
    "-------------------- SOURCES --------------------\n"+in.mkString("\n")+
    "--------------------- MAPS ----------------------\n"+maps.mkString("\n")+
    "-------------------- QUERIES --------------------\n"+queries.mkString("\n")+
    "------------------- TRIGGERS --------------------\n"+triggers.mkString("\n")
}

// -----------------------------------------------------------------------------
// SQL-SPECIFIC DEFINTIONS

// ---------- SQL queries definitions
case class SQL(raw:String) extends Tree // SQL query, to be implemented later

// -----------------------------------------------------------------------------
// M3 OBJECTS

// ---------- M3 objects
case class Map(name:String, tp:Type, keys:List[(String,Type)], expr:Expr)
case class Query(name:String, m:MapRef)
abstract sealed class Trigger extends Tree
case class TriggerAdd(tuple:Tuple, acts:List[Stmt]) extends Trigger
case class TriggerDel(tuple:Tuple, acts:List[Stmt]) extends Trigger
case class TriggerInit(acts:List[Stmt]) extends Trigger

// ---------- Expressions (values)
sealed abstract class Expr extends Tree
case class AggSum(ks:List[String], e:Expr) extends Expr
case class Tuple(schema:String, proj:List[String]) extends Expr
case class Let(n:String, v:Expr) extends Expr
case class CondVal(c:Cond) extends Expr
case class Val(name:String) extends Expr
case class MapRef(name:String, tp:Type, ks:List[String]) extends Expr

case class Const(v:String) extends Expr
case class Mul(l:Expr,r:Expr) extends Expr
case class Add(l:Expr,r:Expr) extends Expr

case class Apply(fun:String,tp:Type,args:List[Expr]) extends Expr
case class Cast(tp:Type,e:Expr) extends Expr

case class Exists(e:Expr) extends Expr

// ---------- Boolean conditions (boolean values)
sealed abstract class Cond extends Tree
case class CmpEq(l:Expr, r:Expr) extends Cond { override def toString=l+" = "+r }
case class CmpNe(l:Expr, r:Expr) extends Cond { override def toString=l+" <> "+r }
case class CmpGt(l:Expr, r:Expr) extends Cond { override def toString=l+" > "+r }
case class CmpGe(l:Expr, r:Expr) extends Cond { override def toString=l+" >= "+r }
case class CmpLt(l:Expr, r:Expr) extends Cond { override def toString=l+" < "+r }
case class CmpLe(l:Expr, r:Expr) extends Cond { override def toString=l+" <= "+r }

// ---------- Statement with no return
sealed class Stmt extends Tree
case class StAdd(m:MapRef, e:Expr) extends Stmt
case class StSet(m:MapRef, e:Expr) extends Stmt

//case class MapWrite(map:Map, keys:List[Expr], expr:Expr) extends Stmt
//case class NewVal(name:String, expr:Expr)

/*
case class Const(v:String) extends Expr
case class Col(name:String, table:String) extends Expr
case class Alias(name:String, e:Expr) extends Expr
// Aggregation
case class Avg(e:Expr) extends Expr
case class Min(e:Expr) extends Expr
case class Max(e:Expr) extends Expr
case class Avg(e:Expr) extends Expr
case class Count(e:Expr) extends Expr
// Arithmetic
case class Add(a:Expr,b:Expr) extends Expr
case class Sub(a:Expr,b:Expr) extends Expr
case class Mul(a:Expr,b:Expr) extends Expr
case class Div(a:Expr,b:Expr) extends Expr
case class Mod(a:Expr,b:Expr) extends Expr
// Type-specific
case class Day(e:Expr) extends Expr
case class Month(e:Expr) extends Expr
case class Year(e:Expr) extends Expr
case class Substr(e:Expr,start:Int,end:Int= -1) extends Expr
case class Concat(es:List[Expr]) extends Expr
case class Ceil(e:Expr) extends Expr
case class Floor(e:Expr) extends Expr
case class Cond(c:Bool, t:Expr, e:Expr) extends Expr
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

sealed abstract class Bool
case class And(a:Bool, b:Bool) extends Bool
case class Or(a:Bool, b:Bool) extends Bool
case class Not(b:Bool) extends Bool

case class Cmp(a:Expr, b:Expr op:Op) extends Bool
case class Like(e:Expr, pattern:String) extends Bool
case class In(e:Expr, vs:List[Const]) extends Bool || subquery
*/



/*
   MST_mBIDS1(int)[][BIDS_BROKER_ID, BIDS_PRICE] += 1;
   MST_mBIDS1_L1_1(float)[][] += BIDS_VOLUME;
   MST_mBIDS1_L2_1(float)[][BIDS_PRICE] += BIDS_VOLUME;
   MST_mBIDS3(float)[][BIDS_BROKER_ID, BIDS_PRICE] += (BIDS_PRICE * BIDS_VOLUME);
   MST(float)[][B_BROKER_ID] := 
  ((AggSum([B_BROKER_ID], 
    ((__sql_inline_agg_1 ^= (MST_mBIDS1_L1_1[][] * 0.25)) *
      MST_mBIDS1(int)[][B_BROKER_ID, B_PRICE] *
      (__sql_inline_agg_2 ^=
        AggSum([], (MST_mBIDS1_L2_1[][B2_PRICE] * {B2_PRICE > B_PRICE}))) *
      {__sql_inline_agg_1 > __sql_inline_agg_2})) *
   AggSum([], 
     ((__sql_inline_agg_3 ^= (MST_mBIDS2_L1_1[][] * 0.25)) *
       MST_mBIDS2[][A_PRICE] *
       (__sql_inline_agg_4 ^= AggSum([], (MST_mBIDS2_L2_1[][A2_PRICE] * {A2_PRICE > A_PRICE}))) *
       {__sql_inline_agg_3 > __sql_inline_agg_4}))) +
  (AggSum([B_BROKER_ID], 
     ((__sql_inline_agg_1 ^= (MST_mBIDS1_L1_1[][] * 0.25)) *
       MST_mBIDS3[][B_BROKER_ID, B_PRICE] *
       (__sql_inline_agg_2 ^=
         AggSum([], (MST_mBIDS1_L2_1[][B2_PRICE] * {B2_PRICE > B_PRICE}))) *
       {__sql_inline_agg_1 > __sql_inline_agg_2})) *
    AggSum([], 
      ((__sql_inline_agg_3 ^= (MST_mBIDS2_L1_1[][] * 0.25)) *
        MST_mBIDS4(int)[][A_PRICE] *
        (__sql_inline_agg_4 ^= AggSum([], (MST_mBIDS2_L2_1[][A2_PRICE] * {A2_PRICE > A_PRICE}))) *
        {__sql_inline_agg_3 > __sql_inline_agg_4})) *
    -1));

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
 *
 *** M3 common definitions
 * addsum
 * expr
 * stmt
 *
 *
 *** M3 Maps definition
 * map		:= "DECLARE" "MAP" name "(" type ")" "[" "]" "[" name ":" type ("," name ":" type)* "]" := aggsum ";"
 *** M3 Query definition
 * query	:= "DECLARE" "QUERY" name ":=" expr ";"
 *** M3 Trigger definition
 * trigger	:= "ON" ("SYSTEM" READY" | ("+"|"-") name "(" name ("," name)* ")") "{" stmt* "}"

 
 */
