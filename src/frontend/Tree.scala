package ddbt.ast

/**
 * This defines the generic nodes that we manipulate during transformations
 * and optimization phases between SQL/M3 and target code. To obtain the exact
 * syntax, refer to ddbt.frontend.Parsers (to avoid outdated documentation).
 * @author TCK
 */
sealed abstract class Tree // Generic AST node

// ---------- Data types
sealed abstract class Type extends Tree { def toScala=toString.substring(0,1).toUpperCase+toString.substring(1).toLowerCase; def toCpp=toString; def toCppRefType=toCpp; def zero:String; def zeroScala=zero; def zeroCpp=zero; def simpleName=toString.substring(0,1).toUpperCase }
//case object TypeChar extends Type /*  8 bit */ { override def toString="char" }
//case object TypeShort extends Type /*16 bit */ { override def toString="short" }
//case object TypeInt  extends Type /* 32 bit */ { override def toString="int" }
case object TypeLong   extends Type /* 64 bit */ { override def toString="long"; val zero="0L" }
//case object TypeFloat extends Type /*32 bit */ { override def toString="float" }
case object TypeDouble extends Type /* 64 bit */ { override def toString="double"; val zero="0.0"; override def toCpp="DOUBLE_TYPE"; }
case object TypeDate   extends Type              { override def toString="date"; val zero="0L"; override def zeroScala="new Date(0L)"; override def zeroCpp="00000000"; override def simpleName="A" }
//case object TypeTime extends Type              { override def toString="timestamp" }
case object TypeString extends Type              { override def toString="string"; val zero="\"\""; override def toCpp="STRING_TYPE"; override def toCppRefType=toCpp+"&"; }
// case class TypeBinary(maxBytes:Int) extends Type { override def toString="binary("+max+")" } // prefix with number of bytes such that prefix minimize number of bytes used
case class TypeTuple(ts:List[Type]) extends Type { override def toString="<"+ts.mkString(",")+">"; val zero="<"+ts.map(_.zero).mkString(",")+">"; override val zeroScala="<"+ts.map(_.zeroScala).mkString(",")+">"; override def simpleName=ts.map(_.simpleName).mkString}

// ---------- Comparison operators
sealed abstract class OpCmp extends Tree { def toM3=toString; def toSQL=toString } // toString is C/Scala notation
case object OpEq extends OpCmp { override def toString="=="; override def toM3="="; override def toSQL="=" }
case object OpNe extends OpCmp { override def toString="!="; override def toSQL="<>" }
case object OpGt extends OpCmp { override def toString=">" } // OpLt by reversing arguments
case object OpGe extends OpCmp { override def toString=">=" } // OpGe by reversing arguments

// ---------- Source definitions, see ddbt.frontend.ExtParser
case class Source(stream:Boolean, schema:Schema, in:SourceIn, split:Split, adaptor:Adaptor) extends Tree { override def toString = "CREATE "+(if (stream) "STREAM" else "TABLE")+" "+schema+"\n  FROM "+in+" "+split+" "+adaptor+";" }
case class Schema(name:String, fields:List[(String,Type)]) extends Tree { override def toString=name+" ("+fields.map(x=>x._1+" "+x._2).mkString(", ")+")"; val deltaSchema="DELTA_"+name }
case class Adaptor(name:String, options:Map[String,String]) extends Tree { override def toString=name+(if (options.isEmpty) "" else " ("+options.map{case(k,v)=>k+":='"+v+"'"}.mkString(", ")+")") }

sealed abstract class SourceIn extends Tree
case class SourceFile(path:String) extends SourceIn { override def toString="FILE '"+path+"'" }
//case class SourcePort(port:Int) // TCP server
//case class SourceRemote(host:String, port:Int, proto:Protocol) proto=bootstrap/authentication protocol (TCP client)

sealed abstract class Split extends Tree
case object SplitLine extends Split { override def toString="LINE DELIMITED" } // deal with \r, \n and \r\n ?
case class SplitSize(bytes:Int) extends Split { override def toString="FIXEDWIDTH "+bytes }
case class SplitSep(delim:String) extends Split { override def toString="'"+delim+"' DELIMITED" }
case class SplitPrefix(bytes:Int) extends Split { override def toString="PREFIXED "+bytes } // records are prefixed with their length in bytes

// ---------- Map update operators
sealed abstract class OpMap extends Tree
case object OpSet extends OpMap { override def toString=":=" }
case object OpAdd extends OpMap { override def toString="+=" }

// ---------- Trigger events
sealed abstract class EvtTrigger extends Tree { def args=List[(String,Type)](); def evtName:String }
case object EvtReady extends EvtTrigger { override def toString="SYSTEM READY"; override val evtName="system_ready" }
case class EvtAdd(schema:Schema) extends EvtTrigger { override def toString="+ "+schema.name+" ("+schema.fields.map(x=>x._1).mkString(", ")+")"; override def args=schema.fields; override val evtName="insert_"+schema.name }
case class EvtDel(schema:Schema) extends EvtTrigger { override def toString="- "+schema.name+" ("+schema.fields.map(x=>x._1).mkString(", ")+")"; override def args=schema.fields; override val evtName="delete_"+schema.name }
case class EvtBatchUpdate(schema:Schema) extends EvtTrigger { override def toString="BATCH UPDATE OF "+schema.name; override def args=Nil; override val evtName="batch_"+schema.name }
// Cleanup/Failure/Shutdown/Checkpoint

// -----------------------------------------------------------------------------
// M4 language (WIP)
/*
sealed abstract class M4 // XXX: build ddbt.frontend.M4Parser
object M4 {
  sealed abstract class OpAgg extends M4
  case object OpSum extends OpAgg
  case object OpMin extends OpAgg
  case object OpMax extends OpAgg
  // ---------- System
  case class System(sources:List[Source], maps:List[MapDef], triggers:List[Trigger]) extends M4
  case class MapDef(name:String, tp:Type, keys:List[(String,Type)], aggs:List[(String,Type,OpAgg,Boolean)], expr:Expr, opts:Map[String,Any]) extends M4
  case class Trigger(evt:EvtTrigger, stmts:List[Stmt]) extends M4
  // ---------- Expressions
  sealed abstract class Expr extends M4
  case class Const(tp:Type,v:String) extends Expr
  case class Ref(name:String) extends Expr
  case class MapRef(name:String, keys:List[String]=Nil, aggs:List[String]=Nil) extends Expr
  case class Add(l:Expr,r:Expr) extends Expr
  case class Mul(l:Expr,r:Expr) extends Expr
  case class Agg(ks:List[String], op:OpAgg, e:Expr) extends Expr
  case class Lift(name:String, e:Expr) extends Expr
  case class Apply(fun:String,args:List[Expr]) extends Expr
  case class Cmp(l:Expr,r:Expr,op:OpCmp) extends Expr
  // ---------- Statements
  sealed abstract class Stmt extends M4
  case class StmtMap(m:MapRef,e:Expr,op:OpMap,init:Option[Expr]) extends Stmt
  case class StmtCall(evt:EvtTrigger) extends Stmt
}
*/

// -----------------------------------------------------------------------------
// M3 language

sealed abstract class M3 // see ddbt.frontend.M3Parser
object M3 {
  import ddbt.Utils.ind
  case class System(sources:List[Source], maps:List[MapDef], queries:List[Query], triggers:List[Trigger]) extends M3 {
    // String => (List[Type],Type)
    lazy val mapType = (maps.map { m => (m.name,(m.keys.map{x=>x._2},m.tp)) } ++
                        sources.map { s => (s.schema.deltaSchema,(s.schema.fields.map{x=>x._2},TypeLong)) }).toMap
    override def toString =
      "-------------------- SOURCES --------------------\n"+sources.mkString("\n\n")+"\n\n"+
      "--------------------- MAPS ----------------------\n"+maps.mkString("\n\n")+"\n\n"+
      "-------------------- QUERIES --------------------\n"+queries.mkString("\n\n")+"\n\n"+
      "------------------- TRIGGERS --------------------\n"+triggers.mkString("\n\n")
  }
  case class MapDef(name:String, tp:Type, keys:List[(String,Type)], expr:Expr) extends Stmt {
    override def toString="DECLARE MAP "+name+(if (tp!=null)"("+tp+")" else "")+"[]["+keys.map{case (n,t)=>n+":"+t}.mkString(",")+"] :=\n"+ind(expr+";")
    def toCppType=if(keys.size == 0) tp.toCpp else name+"_map"; def toCppRefType=if(keys.size == 0) toCppType else toCppType+"&"
  }
  case class Query(name:String, map:Expr) extends M3 {
    var keys:List[(String,Type)] = null
    var tp:Type = null
    override def toString="DECLARE QUERY "+name+" := "+map+";"; def toCppType=if(keys.size == 0) tp.toCpp else name+"_map"; def toCppRefType=if(keys.size == 0) toCppType else toCppType+"&"
  }
  case class Trigger(evt:EvtTrigger, stmts:List[Stmt]) extends M3 { override def toString="ON "+evt+" {\n"+ind(stmts.mkString("\n"))+"\n}" }

  // ---------- Expressions (values)
  sealed abstract class Expr extends M3 {
    def tp:Type // expression type
    def collect[T](f:PartialFunction[Expr,Set[T]]):Set[T] = f.applyOrElse(this,(ex:Expr)=>ex match {
      case Mul(l,r) => l.collect(f)++r.collect(f)
      case Add(l,r) => l.collect(f)++r.collect(f)
      case Cmp(l,r,op) => l.collect(f)++r.collect(f)
      case Exists(e) => e.collect(f)
      case Lift(n,e) => e.collect(f)
      case AggSum(ks,e) => e.collect(f)
      case Apply(fn,tp,as) => as.flatMap(a=>a.collect(f)).toSet
      case _ => Set()
    })
    def replace(f:PartialFunction[Expr,Expr]):Expr = f.applyOrElse(this,(ex:Expr)=>ex match { // also preserve types
      case Mul(l,r) => val t=Mul(l.replace(f),r.replace(f)); t.tp=tp; t
      case a@Add(l,r) => val t=Add(l.replace(f),r.replace(f)); t.tp=tp; t.agg=a.agg; t
      case Cmp(l,r,op) => Cmp(l.replace(f),r.replace(f),op)
      case Exists(e) => Exists(e.replace(f))
      case Lift(n,e) => Lift(n,e.replace(f))
      case a@AggSum(ks,e) => val t=AggSum(ks,e.replace(f)); t.tks=a.tks; t
      case Apply(fn,tp,as) => Apply(fn,tp,as.map(e=>e.replace(f)))
      case _ => ex
    })
    def rename(r:String=>String):Expr = replace {
      case Ref(n) => val t=Ref(r(n)); t.tp=tp; t
      case MapRef(n,tp,ks) => val t=MapRef(n,tp,ks.map(r)); t.tp=tp; t
      case Lift(n,e) => val t=Lift(r(n),e.rename(r)); t
      case a@AggSum(ks,e) => val t=AggSum(ks map r,e.rename(r)); t.tks=a.tks; t
      case a@Add(el,er) => val t=Add(el.rename(r),er.rename(r)); t.tp=tp; t.agg=a.agg.map{case(n,t)=>(r(n),t)}; t
    }
    def rename(m:Map[String,String]):Expr = rename((s:String)=>m.getOrElse(s,s))
    def rename(os:String,ns:String):Expr = rename((s:String)=>if(s==os) ns else s)
  }

  // Constants
  case class Const(tp:Type,v:String) extends Expr { override def toString=if (tp==TypeString) "'"+v+"'" else v }
  // Variables
  case class Ref(name:String) extends Expr { override def toString=name; var tp:Type=null }
  case class MapRef(name:String, var tp:Type /*M3 bug*/, keys:List[String]) extends Expr { override def toString=name+(if (tp!=null)"("+tp+")" else "")+"[]["+keys.mkString(",")+"]"; var tks:List[Type]=Nil; var isTemp:Boolean=false; def toCppType=if(keys.size == 0) tp.toCpp else name+"_map"; def toCppRefType=if(keys.size == 0) toCppType else toCppType+"&"}
  case class Lift(name:String, e:Expr) extends Expr { override def toString="("+name+" ^= "+e+")"; val tp=TypeLong } // 'Let name=e in ...' semantics (combined with Mul)
  case class MapRefConst(schema:String, proj:List[String]) extends Expr { override def toString=schema+"("+proj.mkString(", ")+")"; val tp=TypeLong } // appear in Map definition and constant table lookups
  case class DeltaMapRefConst(schema:String, proj:List[String]) extends Expr { override def toString="(DELTA "+schema+")("+proj.mkString(", ")+")"; val tp=TypeLong; def deltaSchema=Schema(schema,null).deltaSchema } //used for delta relations used while batching is used
  // Operations
  case class AggSum(ks:List[String], e:Expr) extends Expr { override def toString="AggSum(["+ks.mkString(",")+"],\n"+ind(e.toString)+"\n)"; def tp=e.tp; var tks:List[Type]=Nil } // (grouping_keys)->sum relation
  case class Mul(l:Expr,r:Expr) extends Expr { override def toString="("+l+" * "+r+")"; var tp:Type=null } // cross-product semantics
  case class Add(l:Expr,r:Expr) extends Expr { override def toString="("+l+" + "+r+")"; var tp:Type=null; var agg:List[(String,Type)]=Nil } // set union semantics, agg!=Nil if union with free vars
  case class Exists(e:Expr) extends Expr { override def toString="EXISTS("+e+")"; val tp=TypeLong } // returns 0 or 1 (check that there is at least one tuple)
  case class Apply(fun:String,var tp:Type /*=>typeCheck*/,args:List[Expr]) extends Expr { override def toString="["+fun+":"+tp+"]("+args.mkString(",")+")" } // function application
  case class Cmp(l:Expr,r:Expr,op:OpCmp) extends Expr { override def toString="{"+l+" "+op.toM3+" "+r+"}"; val tp=TypeLong } // comparison, returns 0 or 1
  // Tupling
  case class Tuple(es:List[Expr]) extends Expr { override def toString="<"+es.mkString(",")+">"; var tp:Type=null }
  case class TupleLift(ns:List[String], e:Expr) extends Expr { override def toString="(<"+ns.mkString(",")+"> ^= "+e+")"; val tp=TypeLong }

  // ---------- Statements (no return)
  sealed abstract class Stmt extends M3 { var stmtId:Int=(-1) }
  case class StmtMap(m:MapRef,e:Expr,op:OpMap,init:Option[Expr]) extends Stmt { override def toString=m+(init match { case Some(i) => ":("+i+")" case None => ""} )+" "+op+" "+e+";" }
  // case class StmtCall(external function) extend Stmt
}

// -----------------------------------------------------------------------------
// SQL (http://www.contrib.andrew.cmu.edu/~shadow/sql/sql1992.txt)

sealed abstract class SQL // see ddbt.frontend.SQLParser
object SQL {
  import ddbt.Utils.ind
  sealed abstract class OpAgg extends SQL
  case object OpSum extends OpAgg
  case object OpMin extends OpAgg
  case object OpMax extends OpAgg
  case object OpAvg extends OpAgg
  case object OpCount extends OpAgg
  case object OpCountDistinct extends OpAgg

  sealed abstract class Join extends SQL
  case object JoinInner extends Join
  case object JoinLeft extends Join
  case object JoinRight extends Join
  case object JoinFull extends Join

  // ---------- System
  case class System(sources:List[Source], queries:List[Query]) extends SQL { override def toString = sources.mkString("\n\n")+"\n\n"+queries.mkString("\n\n"); }
  // ---------- Queries
  abstract sealed class Query extends SQL
  case class Lst(es:List[Expr]) extends Query { override def toString=es.mkString(", ") }
  case class Union(q1:Query,q2:Query,all:Boolean=false) extends Query { override def toString="("+q1+") UNION"+(if (all) " ALL" else "")+" ("+q2+")" }
  case class Inter(q1:Query,q2:Query) extends Query { override def toString="("+q1+") INTERSECT ("+q2+")" }
  case class Select(distinct:Boolean,cs:List[Expr],ts:List[Table],wh:Cond=null,gb:GroupBy=null,ob:OrderBy=null) extends Query {
    override def toString="SELECT "+(if(distinct)"DISTINCT " else "")+cs.mkString(", ")+"\nFROM "+ts.mkString(", ")+
                          (if(wh!=null) "\nWHERE "+wh else "")+(if(gb!=null) "\n"+gb else "")+(if(ob!=null) "\n"+ob else "")
  }
    case class GroupBy(fs:List[Field],cond:Cond=null) extends SQL { override def toString="GROUP BY "+fs.mkString(", ")+(if(cond!=null) " HAVING "+cond else "") }
    case class OrderBy(cs:List[(Field,Boolean)]) extends SQL { override def toString="ORDER BY "+cs.map{case (f,d) => f+" "+(if (d) "DESC" else "ASC") }.mkString(", ") }
  // ---------- Tables
  abstract sealed class Table extends SQL
  case class TableQuery(q:Query) extends Table { override def toString="("+ind("\n"+q.toString)+"\n)" }
  case class TableNamed(n:String) extends Table { override def toString=n }
  case class TableAlias(t:Table, n:String) extends Table { override def toString=t+" "+n }
  case class TableJoin(t1:Table, t2:Table, j:Join, c:Cond) extends Table { // empty condition = natural join
    override def toString=t1+"\n  "+(j match {
      case JoinInner => (if (c==null) "NATURAL " else "")+"JOIN"
      case JoinLeft => "LEFT JOIN"
      case JoinRight => "RIGHT JOIN"
      case JoinFull => "FULL JOIN"
    })+" "+t2+(if (c!=null) " ON "+c else "")
  }
  // ---------- Expressions
  abstract sealed class Expr extends SQL
  case class Alias(e:Expr,n:String) extends Expr { override def toString=e+" AS "+n }
  case class Field(n:String,t:String) extends Expr { override def toString=if (t==null) n else t+"."+n }
  case class Const(v:String, tp:Type) extends Expr { override def toString=if (tp==TypeString) "'"+v+"'" else v }
  case class Apply(fun:String,args:List[Expr]) extends Expr { override def toString=fun+"("+args.mkString(", ")+")" }
  case class Nested(q:Query) extends Expr { override def toString="("+ind("\n"+q.toString)+"\n)" }
  case class Case(ce:List[(Cond,Expr)],d:Expr) extends Expr {
    override def toString = "CASE"+ind(ce.map{ case (c,t) => "\nWHEN "+c+" THEN "+t }.mkString+"\nELSE "+d)+"\nEND"
  }
  // ---------- Arithmetic
  case class Add(l:Expr,r:Expr) extends Expr { override def toString="("+l+" + "+r+")" }
  case class Sub(l:Expr,r:Expr) extends Expr { override def toString="("+l+" - "+r+")" }
  case class Mul(l:Expr,r:Expr) extends Expr { override def toString="("+l+" * "+r+")" }
  case class Div(l:Expr,r:Expr) extends Expr { override def toString="("+l+" / "+r+")" }
  case class Mod(l:Expr,r:Expr) extends Expr { override def toString="("+l+" % "+r+")" }
  // ---------- Aggregation
  case class Agg(e:Expr,op:OpAgg) extends Expr { override def toString=(op match { case OpCountDistinct => "COUNT(DISTINCT " case _ => op.toString.substring(2).toUpperCase+"(" })+e+")" }
  case class All(q:Query) extends Expr { override def toString="ALL("+ind("\n"+q)+"\n)" }
  case class Som(q:Query) extends Expr { override def toString="SOME("+ind("\n"+q)+"\n)" }
  // ---------- Conditions
  sealed abstract class Cond
  case class And(l:Cond, r:Cond) extends Cond { override def toString="("+l+" AND "+r+")" }
  case class Or(l:Cond, r:Cond) extends Cond { override def toString="("+l+" OR "+r+")" }
  case class Exists(q:Query) extends Cond { override def toString="EXISTS("+ind("\n"+q)+"\n)" }
  case class In(e:Expr,q:Query) extends Cond { override def toString=e+" IN ("+ind("\n"+q)+"\n)" }
  case class Not(e:Cond) extends Cond { override def toString="NOT("+e+")" }
  case class Like(l:Expr,p:String) extends Cond { override def toString=l+" LIKE '"+p+"'" }
  case class Cmp(l:Expr, r:Expr, op:OpCmp) extends Cond { override def toString=l+" "+op.toSQL+" "+r }
}
