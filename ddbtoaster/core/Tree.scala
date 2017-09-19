package ddbt.ast

/**
 * This defines the generic nodes that we manipulate during transformations
 * and optimization phases between SQL/M3 and target code. To obtain the exact
 * syntax, refer to ddbt.frontend.Parsers (to avoid outdated documentation).
 * @author TCK
 */
sealed abstract class Tree // Generic AST node

// ---------- Data types
sealed abstract class Type extends Tree { 
  def zero: String
  def zeroScala: String = zero
  def zeroCpp: String = zero
  def toScala: String = toString.capitalize
  def toCpp: String = toString
  def toCppRefType: String = toCpp
  def simpleName: String = toString.substring(0, 1).toUpperCase 
  def castScala: String = "to" + toScala
}

// case object TypeChar extends Type /*  8 bit */ { 
//   val zero = "0"
//   override def toString = "char" 
// }

// case object TypeShort extends Type /*16 bit */ { 
//   val zero = "0"
//   override def toString = "short" 
// }

// case object TypeInt  extends Type /* 32 bit */ { 
//   val zero = "0"
//   override def toString = "int" 
// }

case object TypeLong extends Type /* 64 bit */ { 
  val zero = "0L"
  override def toString = "long"
}

// case object TypeFloat extends Type /*32 bit */ { 
//  val zero = "0.0F"
//  override def toString = "float" 
// }

case object TypeDouble extends Type /* 64 bit */ { 
  val zero = "0.0"
  override def toString = "double"
  override def toCpp = "DOUBLE_TYPE"
}

case object TypeDate extends Type {
  val zero = "0L"
  override def toString = "date"
  override def toScala = "Long"
  // override def toCpp = "long"
  override def zeroScala = "0"
  override def zeroCpp = "00000000"
  override def simpleName = "A" 
}

//case object TypeTime extends Type { 
//  override def toString = "timestamp" 
//}

case object TypeString extends Type { 
  val zero="\"\""
  override def toString = "string"
  override def toCpp = "STRING_TYPE"
  override def toCppRefType = toCpp + "&"
}

//case class TypeBinary(maxBytes:Int) extends Type { 
//  override def toString = "binary(" + max + ")" 
//} 
// prefix with number of bytes such that prefix minimize number of bytes used

case class TypeTuple(ts: List[Type]) extends Type { 
  val zero = "<" + ts.map(_.zero).mkString(", ") + ">"
  override val zeroScala = "<" + ts.map(_.zeroScala).mkString(", ") + ">" 
  override def toString = "<" + ts.mkString(", ") + ">"  
  override def simpleName = ts.map(_.simpleName).mkString
}

// ---------- Comparison operators
sealed abstract class OpCmp extends Tree { 
  def toM3 = toString
  def toSQL = toString 
} // toString is C/Scala notation

case object OpEq extends OpCmp { 
  override def toString = "=="
  override def toM3 = "="
  override def toSQL = "=" 
}

case object OpNe extends OpCmp { 
  override def toString = "!="
  override def toSQL = "<>" 
}

// OpLt by reversing arguments
case object OpGt extends OpCmp { override def toString = ">" } 

// OpGe by reversing arguments
case object OpGe extends OpCmp { override def toString = ">=" } 


// ---------- Expression locality types
abstract sealed class LocalityType
case object LocalExp extends LocalityType {
  override def toString = "<Local>"
}
case object DistRandomExp extends LocalityType {
  override def toString = "<DistRandom>"
}
case class DistByKeyExp(pkeys: List[(String, Type)]) extends LocalityType {
  override def toString = "<DistByKey(" + pkeys.map(_._1).mkString(", ") + ")>"
}

// ---------- Source definitions, see ddbt.frontend.ExtParser
case class Source(stream: Boolean, schema: Schema, in: SourceIn, split: Split, adaptor: Adaptor, locality: LocalityType) extends Tree { 
  override def toString = 
    "CREATE " + (if (stream) "STREAM" else "TABLE") + " " + schema + 
    "\n  FROM " + in + " " + split + " " + adaptor + 
    (locality match { 
      case LocalExp => "" 
      case DistRandomExp => "\n  PARTITIONED RANDOMLY"
      case DistByKeyExp(pk) => 
        "\n  PARTITIONED BY [" + pk.map(_._1).mkString(", ") + "]"
    }) + ";" 
}

case class Schema(name: String, fields: List[(String, Type)]) extends Tree { 
  val deltaName = "DELTA_" + name 
  override def toString = 
    name + " (" + fields.map(x => x._1 + " " + x._2).mkString(", ") + ")"
}

case class Adaptor(name: String, options: Map[String, String]) extends Tree { 
  override def toString =     
    name + (if (options.isEmpty) "" 
            else " (" + options.map { case (k, v) => k + " := '" + v + "'" }.mkString(", ") + ")")
}

sealed abstract class SourceIn extends Tree

case class SourceFile(path: String) extends SourceIn { 
  override def toString = "FILE '" + path + "'" 
}

//case class SourcePort(port: Int) // TCP server
//case class SourceRemote(host: String, port: Int, proto: Protocol)
// proto=bootstrap/authentication protocol (TCP client)

sealed abstract class Split extends Tree

case object SplitLine extends Split { 
  override def toString = "LINE DELIMITED" 
} // deal with \r, \n and \r\n ?

case class SplitSize(bytes: Int) extends Split { 
  override def toString = "FIXEDWIDTH " + bytes 
}

case class SplitSep(delim: String) extends Split { 
  override def toString = "'" + delim + "' DELIMITED" 
}

case class SplitPrefix(bytes: Int) extends Split { 
  override def toString = "PREFIXED " + bytes 
} // records are prefixed with their length in bytes


// ---------- Map update operators
sealed abstract class OpMap extends Tree
case object OpSet extends OpMap { override def toString = " := " }
case object OpAdd extends OpMap { override def toString = " += " }

//---------- Map types
sealed abstract class StoreType 
case object IndexedStore extends StoreType       // Default store type (row-oriented Store)
case object ArrayStore   extends StoreType       // Array store (row-oriented, only foreach)
case object LogStore     extends StoreType       // Columnar store (only append and foreach)
case class  PartitionStore(pkeys: List[Int]) extends StoreType     // Multiple log stores 


// ---------- Trigger events
sealed abstract class EvtTrigger extends Tree { 
  def evtName: String
  def schema: Schema 
  def args = List[(String, Type)]()
}

case object EvtReady extends EvtTrigger { 
  override val evtName = "system_ready"
  override val schema = null 
  override def toString = "SYSTEM READY"
}

case class EvtAdd(schema: Schema) extends EvtTrigger { 
  override val evtName = "insert_" + schema.name 
  override def args = schema.fields 
  override def toString = 
    "+ " + schema.name + " (" + schema.fields.map(_._1).mkString(", ") + ")"
}

case class EvtDel(schema: Schema) extends EvtTrigger { 
  override val evtName = "delete_" + schema.name 
  override def args = schema.fields
  override def toString = 
    "- " + schema.name + " (" + schema.fields.map(_._1).mkString(", ") + ")"
}

case class EvtBatchUpdate(schema: Schema) extends EvtTrigger { 
  override val evtName = "batch_" + schema.name 
  override def args = Nil
  override def toString = "BATCH UPDATE OF " + schema.name
}


// Cleanup/Failure/Shutdown/Checkpoint
// -----------------------------------------------------------------------------
// M3 language

sealed abstract class M3 // see ddbt.frontend.M3Parser

object M3 {

  import ddbt.lib.Utils.ind

  case class System(sources: List[Source], maps: List[MapDef], queries: List[Query], triggers: List[Trigger]) extends M3 {
    lazy val mapType =              // String => (List[Type], Type)
      ( maps.map { m => 
          (m.name, (m.keys.map {_._2}, m.tp)) 
        } ++
        sources.map { s => 
          (s.schema.deltaName, (s.schema.fields.map {_._2}, TypeLong)) 
        } 
      ).toMap

    override def toString =
      "-------------------- SOURCES --------------------\n" + 
      sources.mkString("\n\n") + "\n\n" + 
      "--------------------- MAPS ----------------------\n" + 
      maps.mkString("\n\n") + "\n\n" +
      "-------------------- QUERIES --------------------\n" + 
      queries.mkString("\n\n") + "\n\n" +
      "------------------- TRIGGERS --------------------\n" + 
      triggers.mkString("\n\n")
  }

  case class MapDef(name: String, tp: Type, keys: List[(String, Type)], expr: Expr, locality: LocalityType) extends Stmt {    
    override def toString = 
      "DECLARE MAP " + name + (if (tp != null) "(" + tp + ")" else "") + "[][" + 
      keys.map { case (n, t) => n + ": " + t }.mkString(", ") + "] :=\n" + 
      ind(expr.toString) + 
      (locality match { 
        case LocalExp => "" 
        case DistRandomExp => "\n  PARTITIONED RANDOMLY"
        case DistByKeyExp(pk) => 
          "\n  PARTITIONED BY [" + pk.map(_._1).mkString(", ") + "]"
      }) + ";"

    def toCppType = if (keys.size == 0) tp.toCpp else name + "_map"

    def toCppRefType = if (keys.size == 0) toCppType else toCppType + "&"
  }

  case class Query(name: String, map: Expr) extends M3 {
    var keys: List[(String, Type)] = null
    var tp: Type = null

    override def toString = "DECLARE QUERY " + name + " := " + map + ";"
    
    def toCppType = if (keys.size == 0) tp.toCpp else name + "_map"
    
    def toCppRefType = if (keys.size == 0) toCppType else toCppType + "&"
  }

  case class Trigger(evt: EvtTrigger, stmts: List[Stmt]) extends M3 { 
    override def toString = "ON " + evt + " {\n" + ind(stmts.mkString("\n")) + "\n}" 
  }

  // ---------- Expressions (values)
  sealed abstract class Expr extends M3 {
    def tp: Type                          // expression type

    def locality: Option[LocalityType]    // expression locality type
   
    def collect[T](f: PartialFunction[Expr, List[T]]): List[T] = 
      f.applyOrElse(this, (ex: Expr) => ex match {
        case Mul(l, r) => l.collect(f) ++ r.collect(f)
        case Add(l, r) => l.collect(f) ++ r.collect(f)
        case Cmp(l, r, op) => l.collect(f) ++ r.collect(f)
        case CmpOrList(l, r) => l.collect(f) ++ r.flatMap(_.collect(f))
        case Exists(e) => e.collect(f)
        case Lift(n, e) => e.collect(f)
        case AggSum(ks, e) => e.collect(f)
        case Apply(fn, tp, as) => as.flatMap(_.collect(f))
        case Tuple(es) => es.flatMap(_.collect(f))
        case TupleLift(ns, e) => e.collect(f)
        case Repartition(ks, e) => e.collect(f)
        case Gather(e) => e.collect(f)
        case _ => List()
      })

    def replace(f: PartialFunction[Expr, Expr]): Expr = 
      f.applyOrElse(this, (ex: Expr) => ex match { // also preserve types
        case Mul(l, r) => 
          val newEx = Mul(l.replace(f), r.replace(f))
          newEx.tp = tp
          newEx
        case a @ Add(l, r) => 
          val newEx = Add(l.replace(f), r.replace(f))
          newEx.tp = tp
          newEx
        case Cmp(l, r, op) => Cmp(l.replace(f), r.replace(f), op)
        case CmpOrList(l, r) => CmpOrList(l.replace(f), r.map(_.replace(f)))
        case Exists(e) => Exists(e.replace(f))
        case Lift(n, e) => Lift(n, e.replace(f))
        case AggSum(ks, e) => AggSum(ks, e.replace(f))
        case Apply(fn, tp, as) => Apply(fn, tp, as.map(_.replace(f)))
        case Tuple(es) => 
          val newEx = Tuple(es.map(_.replace(f)))
          newEx.tp = tp
          newEx
        case TupleLift(ns, e) => TupleLift(ns, e.replace(f))
        case Repartition(ks, e) => Repartition(ks, e.replace(f))
        case Gather(e) => Gather(e.replace(f))
        case _ => ex
      })

    def rename(r: String => String): Expr = replace {
      case Ref(n) => 
        val newEx = Ref(r(n))
        newEx.tp = tp
        newEx
      case m @ MapRef(n, tp, ks) => 
        val newEx = MapRef(r(n), tp, ks.map(x => (r(x._1), x._2)))
        newEx.isTemp = m.isTemp
        newEx.locality = m.locality match { 
          case Some(DistByKeyExp(pkeys)) => Some(DistByKeyExp(pkeys.map(x => (r(x._1), x._2))))
          case Some(DistRandomExp) => Some(DistRandomExp)
          case Some(LocalExp) => Some(LocalExp)
          case None => None
        }
        newEx
      case Lift(n, e) => Lift(r(n), e.rename(r))
      case AggSum(ks, e) => AggSum(ks.map(x => (r(x._1), x._2)), e.rename(r)) 
      case Repartition(ks, e) => Repartition(ks.map(x => (r(x._1), x._2)), e.rename(r))
      case a @ Add(el, er) => 
        val newEx = Add(el.rename(r), er.rename(r))
        newEx.tp = a.tp
        newEx
    }

    def rename(m: Map[String, String]): Expr = 
      rename((s: String) => m.getOrElse(s, s))

    def rename(os: String, ns: String): Expr = 
      rename((s: String) => if (s == os) ns else s)

    /**
      * Computes the set of input variables and the set of output variables for 
      * the given expression.
      *
      * @return A pair of lists, holding input variables and output variables
      */
    def schema: (List[(String, Type)], List[(String, Type)]) = {
      def union(l1: List[(String, Type)],l2: List[(String, Type)])  = (l1 ++ l2).distinct
      def diff(l1: List[(String, Type)], l2: List[(String, Type)])  = l1.filterNot(l2.contains)
      def inter(l1: List[(String, Type)], l2: List[(String, Type)]) = l1.filter(l2.contains)

      this match {
        case Const(tp, v) => (List(), List())
        case Ref(n) => (List((n, this.tp)), List())
        case MapRef(n, tp, ks) => (List(), ks)
        case MapRefConst(n, ks) => (List(), ks)
        case DeltaMapRefConst(n, ks) => (List(), ks)        
        case Cmp(l, r, op) => (union(l.schema._1, r.schema._1), List())
        case CmpOrList(l, r) => (l.schema._1, List())
        case Apply(fn, tp, as) =>
          val (ivs, ovs) = as.map(_.schema).unzip
          (ivs.flatten.distinct, ovs.flatten.distinct)
        case Mul(el, er) =>
          val (iv1, ov1) = el.schema
          val (iv2, ov2) = er.schema
          (union(diff(iv2, ov1), iv1), diff(union(ov1, ov2), iv1))
        case Add(el, er) =>
          val (iv1, ov1) = el.schema
          val (iv2, ov2) = er.schema
          val iv0 = iv1 union iv2
          val ov0 = ov1 union iv2
          val iv = diff(ov0, (inter(ov1, ov2)))
          (union(iv0, iv), diff(ov0, iv))
        case Lift(n, e) => 
          val (iv, ov) = e.schema
          (union(iv, ov), List((n, e.tp)))
        case Exists(e) => e.schema                
        case AggSum(ks, e) => (e.schema._1, ks)
        case Repartition(ks, e) => e.schema
        case Gather(e) => e.schema
        case _ => sys.error("Don't know how to compute schema of " + this)
      }
    }

    def ivars: List[(String, Type)] = schema._1

    def ovars: List[(String, Type)] = schema._2

    def cmp(that: Expr): Option[Map[(String, Type), (String, Type)]] = {
      val empty: Option[Map[(String, Type), (String, Type)]] = Some(Map())
      def merge(a: Option[Map[(String, Type), (String, Type)]],
                b: => Option[Map[(String, Type), (String, Type)]]) =
        if (a == None) None
        else (a, b) match {
          case (Some(a), Some(b)) =>
            if (a.keySet.intersect(b.keySet).exists(k => a(k) != b(k))) None
            else Some(a ++ b)
          case _ => None
        }

      if (this.tp != that.tp) None else (this, that) match {
        case (Const(_, v1), Const(_, v2)) => 
          if (v1 == v2) empty else None
        case (a @ Ref(n1), b @ Ref(n2)) => 
          Some(Map((n1, a.tp) -> (n2, b.tp)))
        case (Apply(fn1, tp1, as1), Apply(fn2, tp2, as2)) =>
          if (fn1 != fn2 || as1.length != as2.length) None 
          else as1.zip(as2).foldLeft (empty) {
            case (fmap, (a, b)) => merge(fmap, a.cmp(b)) }
        case (MapRef(n1, tp1, ks1), MapRef(n2, tp2, ks2)) =>
          if (n1 != n2 || ks1.length != ks2.length) None
          else ks1.zip(ks2).foldLeft (empty) {
            case (fmap, (a, b)) => merge(fmap, Some(Map(a -> b))) }
        case (MapRefConst(n1, ks1), MapRefConst(n2, ks2)) => 
          if (n1 != n2 || ks1.length != ks2.length) None 
          else ks1.zip(ks2).foldLeft (empty) {
            case (fmap, (a, b)) => merge(fmap, Some(Map(a -> b))) }
        case (DeltaMapRefConst(n1, ks1), DeltaMapRefConst(n2, ks2)) =>          
          if (n1 != n2 || ks1.length != ks2.length) None 
          else ks1.zip(ks2).foldLeft (empty) {
            case (fmap, (a, b)) => merge(fmap, Some(Map(a -> b))) }
        case (Cmp(l1, r1, op1), Cmp(l2, r2, op2)) =>
          if (op1 != op2) None else merge(l1.cmp(l2), r1.cmp(r2))
        case (Mul(l1, r1), Mul(l2, r2)) =>
          merge(l1.cmp(l2), r1.cmp(r2))
        case (Add(l1, r1), Add(l2, r2)) =>
          merge(l1.cmp(l2), r1.cmp(r2))
        case (Lift(v1, e1), Lift(v2, e2)) =>
          merge(e1.cmp(e2), Some(Map((v1, e1.tp) -> (v2, e2.tp))))
        case (Exists(e1), Exists(e2)) => e1.cmp(e2)
        case (AggSum(ks1, e1), AggSum(ks2, e2)) =>
          if (ks1.length != ks2.length) None else e1.cmp(e2) match {
            case Some(mapping) if ks1.map(mapping.apply).toSet == ks2.toSet =>
              val rvars = (e1.schema._1 ++ ks1).toSet
              val rmapping = rvars.map(v => (v, mapping.apply(v))).toMap
              Some(rmapping)
            case _ => None
          }
        case (Repartition(ks1, e1), Repartition(ks2, e2)) =>
          if (ks1.length != ks2.length) None else e1.cmp(e2) match {
            case f @ Some(mapping) if ks1.map(mapping.apply).toSet == ks2.toSet => f
            case _ => None
          }
        case (Gather(e1), Gather(e2)) => e1.cmp(e2)
        case _ => None
      }
    }
  }

  // Constants
  case class Const(tp: Type, v: String) extends Expr { 
    val locality: Option[LocalityType] = None
    override def toString = if (tp == TypeString) "'" + v + "'" else v 
  }

  // Variables
  case class Ref(name: String) extends Expr { 
    var tp: Type = null 
    val locality: Option[LocalityType] = None
    override def toString = name
  }

  // Map reference
  case class MapRef(name: String, var tp: Type, var keys: List[(String, Type)]) extends Expr {
    var isTemp:  Boolean = false
    var locality: Option[LocalityType] = Some(LocalExp)
    
    override def toString = 
      name + (if (tp != null) "(" + tp + ")" else "") + "[][" + 
      keys.map(_._1).mkString(", ") + "]" + locality.getOrElse("")

    def toCppType = if (keys.size == 0) tp.toCpp else name + "_map"

    def toCppRefType = if (keys.size == 0) toCppType else toCppType + "&"
  }

  // Lifting operator ('Let name=e in ...' semantics)
  case class Lift(name: String, e: Expr) extends Expr { 
    val tp = TypeLong
    def locality = e.locality
    override def toString = "(" + name + " ^= " + e + ")"
  }

  // Map reference of a table
  case class MapRefConst(name: String, keys: List[(String, Type)]) extends Expr { 
    val tp = TypeLong 
    var locality: Option[LocalityType] = None
    override def toString = name + "(" + keys.map(_._1).mkString(", ") + ")"
  }

  // Map reference of a delta update
  case class DeltaMapRefConst(name: String, keys: List[(String, Type)]) extends Expr { 
    val tp = TypeLong
    var locality: Option[LocalityType] = None
    override def toString = "(DELTA " + name + ")(" + keys.map(_._1).mkString(", ") + ")"
    def deltaName = Schema(name, null).deltaName 
  } //used for delta relations used while batching is used
  
  // Sum aggregate
  case class AggSum(var keys: List[(String, Type)], e: Expr) extends Expr {
    def tp = e.tp
    def locality = e.locality match {
      case l @ Some(DistByKeyExp(pk)) =>
        val expVars = (e.schema._1 ++ keys).toSet
        if (pk.forall(expVars.contains)) l else Some(DistRandomExp)
      case l => l
    }
    override def toString =
      "AggSum([" + keys.map(_._1).mkString(", ") + "],\n" + ind(e.toString) + "\n)"
  }

  // Multiplication operator
  case class Mul(l: Expr, r: Expr) extends Expr { 
    var tp: Type = null 
    def locality = (l.locality, r.locality) match {
      case (Some(LocalExp), Some(LocalExp)) => Some(LocalExp)
      case (Some(DistByKeyExp(a)), Some(DistRandomExp)) 
        if (a == Nil) => Some(DistRandomExp)
      case (Some(DistRandomExp), Some(DistByKeyExp(b))) 
        if (b == Nil) => Some(DistRandomExp)
      case (Some(DistByKeyExp(a)), Some(DistByKeyExp(b))) 
        if (a == b || b == Nil) => Some(DistByKeyExp(a))
      case (Some(DistByKeyExp(a)), Some(DistByKeyExp(b))) 
        if (a == Nil) => Some(DistByKeyExp(b))        
      case (Some(a), None) => Some(a)
      case (None, Some(b)) => Some(b)
      case (None, None) => None
      case _ => sys.error("Merging incompatible expression types in Mul: l = " + l + " r = " + r)
    }
    override def toString = "(" + l + " * " + r + ")"
  }

  // Union operator
  case class Add(l: Expr, r: Expr) extends Expr { 
    var tp: Type = null
    def locality = (l.locality, r.locality) match {
      case (Some(LocalExp), Some(LocalExp)) => Some(LocalExp)
      case (Some(DistRandomExp), Some(DistRandomExp)) => Some(DistRandomExp)
      case (Some(DistByKeyExp(a)), Some(DistByKeyExp(b))) 
        if (a == b) => Some(DistByKeyExp(a))
      case (Some(a), None) => Some(a)
      case (None, Some(b)) => Some(b)
      case (None, None) => None
      case _ => sys.error("Merging incompatible expression types in Add: l = " + l + " r = " + r)
    }
    override def toString = "(" + l + " + " + r + ")"
  }

  // Exists operator - returns 0 or 1 (checks if there is at least one tuple)
  case class Exists(e: Expr) extends Expr { 
    val tp = TypeLong 
    def locality = e.locality
    override def toString = "EXISTS(" + e + ")"
  }

  // Function application
  case class Apply(fun: String, var tp: Type, args: List[Expr]) extends Expr {
    val locality: Option[LocalityType] = None
    override def toString = "[" + fun + ": " + tp + "](" + args.mkString(", ") + ")"
  }

  // Comparison, returns 0 or 1
  case class Cmp(l: Expr, r: Expr, op: OpCmp) extends Expr { 
    val tp = TypeLong    
    val locality: Option[LocalityType] = None
    override def toString = "{" + l + " " + op + " " + r + "}"
  }

  // OR comparison with a given expr list, returns 0 or 1
  case class CmpOrList(l: Expr, r: List[Expr]) extends Expr {
    val tp = TypeLong
    val locality: Option[LocalityType] = None
    override def toString = "{" + l + " IN [" + r.mkString(", ") + "]}"
  }

  // Tupling
  case class Tuple(es: List[Expr]) extends Expr { 
    var tp: Type = null 
    val locality: Option[LocalityType] = None
    override def toString = "<" + es.mkString(", ") + ">"
  }

  // Lifting operator with tuples
  case class TupleLift(ns: List[String], e: Expr) extends Expr { 
    val tp = TypeLong
    val locality: Option[LocalityType] = None
    override def toString = "(<" + ns.mkString(", ") + "> ^= " + e + ")"
  }

  // Distributed operation - repartion by key
  case class Repartition(var ks: List[(String, Type)], e: Expr) extends Expr { 
    def tp = e.tp    
    def locality = Some(DistByKeyExp(ks))
    override def toString = 
      "Repartition([" + ks.map(_._1).mkString(", ") + "],\n" + ind(e.toString) + "\n)"  
  } 

  // Distributed operation - gather on master
  case class Gather(e: Expr) extends Expr { 
    def tp = e.tp    
    val locality = Some(LocalExp)    
    override def toString = "Gather(" + e + ")"  
  } 

  // ---------- Statements (no return)
  sealed abstract class Stmt extends M3 { var stmtId: Int = (-1) }

  case class StmtMap(m: MapRef, e: Expr, op: OpMap, init: Option[Expr]) extends Stmt { 
    override def toString = 
      m + (init match { case Some(i) => ":(" + i + ")" case None => "" }) + 
      " " + op + " " + e + ";" 
  } // case class StmtCall(external function) extend Stmt
}

// -----------------------------------------------------------------------------
// SQL (http://www.contrib.andrew.cmu.edu/~shadow/sql/sql1992.txt)

sealed abstract class SQL // see ddbt.frontend.Parsers

object SQL {

  import ddbt.lib.Utils.ind

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
  case class System(sources: List[Source], queries: List[Query]) extends SQL { 
    override def toString = sources.mkString("\n\n") + "\n\n" + queries.mkString("\n\n")
  }

  // ---------- Queries
  abstract sealed class Query extends SQL

  case class Lst(es: List[Expr]) extends Query { 
    override def toString = es.mkString(", ") 
  }

  case class Union(q1: Query, q2: Query, all: Boolean = false) extends Query {
    override def toString = 
      "(" + q1 + ") UNION" + (if (all) " ALL" else "") + " (" + q2 + ")" 
  }

  case class Inter(q1: Query, q2: Query) extends Query { 
    override def toString = "(" + q1 + ") INTERSECT (" + q2 + ")" 
  }

  case class Select(distinct: Boolean, cs: List[Expr], ts: List[Table], 
                    wh: Option[Cond], gb: Option[GroupBy], ob: Option[OrderBy])  extends Query {
    override def toString = 
      "SELECT " + (if (distinct) "DISTINCT " else "") + cs.mkString(", ") + 
      "\nFROM " + ts.mkString(", ") +
      wh.map("\nWHERE " + _).getOrElse("") +
      gb.map("\n" + _).getOrElse("") + 
      ob.map("\n" + _).getOrElse("")
  }

  case class GroupBy(fs: List[Field], cond: Option[Cond]) extends SQL { 
    override def toString = 
      "GROUP BY " + fs.mkString(", ") +
      cond.map(" HAVING " + _).getOrElse("")
  }
  
  case class OrderBy(cs: List[(Field, Boolean)]) extends SQL { 
    override def toString = 
      "ORDER BY " + cs.map { case (f, d) => 
        f + " " + (if (d) "DESC" else "ASC") 
      }.mkString(", ") 
  }

  // ---------- Tables
  abstract sealed class Table extends SQL
  
  case class TableQuery(q: Query) extends Table { 
    override def toString = "(" + ind("\n" + q.toString) + "\n)" 
  }

  case class TableNamed(n: String) extends Table { 
    override def toString = n 
  }

  case class TableAlias(t: Table, n: String) extends Table { 
    override def toString = t + " " + n 
  }

  case class TableJoin(t1: Table, t2: Table, j: Join, c: Option[Cond]) extends Table {
    // empty condition = natural join
    override def toString = t1 + "\n  " + (j match {
        case JoinInner => if (c == None) "NATURAL JOIN" else "JOIN"
        case JoinLeft  => "LEFT JOIN"
        case JoinRight => "RIGHT JOIN"
        case JoinFull  => "FULL JOIN"
      }) + " " + t2 + c.map(" ON " + _).getOrElse("")
  }

  // ---------- Expressions
  abstract sealed class Expr extends SQL

  case class Alias(e: Expr, n: String) extends Expr { 
    override def toString = e + " AS " + n 
  }

  case class Field(n: String, t: Option[String]) extends Expr { 
    override def toString = t.map(_ + "." + n).getOrElse(n)
  }

  case class Const(v: String, tp: Type) extends Expr { 
    override def toString = if (tp == TypeString) "'" + v + "'" else v 
  }

  case class Apply(fun: String, args: List[Expr]) extends Expr { 
    override def toString = fun + "(" + args.mkString(", ") + ")" 
  }

  case class Nested(q: Query) extends Expr { 
    override def toString = "(" + ind("\n" + q.toString) + "\n)" 
  }

  case class Case(ce: List[(Cond, Expr)], d: Expr) extends Expr {
    override def toString = 
      "CASE" + ind(
        ce.map { case (c, t) => "\nWHEN " + c + " THEN " + t }.mkString + 
        "\nELSE " + d) + 
      "\nEND"
  }

  // ---------- Arithmetic
  case class Add(l: Expr, r: Expr) extends Expr { 
    override def toString = "(" + l + " + " + r + ")" 
  }

  case class Sub(l: Expr, r: Expr) extends Expr { 
    override def toString = "(" + l + " - " + r + ")" 
  }

  case class Mul(l: Expr, r: Expr) extends Expr { 
    override def toString = "(" + l + " * " + r + ")" 
  }

  case class Div(l: Expr, r: Expr) extends Expr { 
    override def toString = "(" + l + " / " + r + ")" 
  }

  case class Mod(l: Expr, r: Expr) extends Expr { 
    override def toString = "(" + l + " % " + r + ")" 
  }

  // ---------- Aggregation
  case class Agg(e: Expr, op: OpAgg) extends Expr { 
    override def toString = (op match { 
        case OpCountDistinct => "COUNT(DISTINCT " 
        case _ => op.toString.substring(2).toUpperCase + "(" 
      }) + e + ")" 
  }

  case class All(q: Query) extends Expr { 
    override def toString = "ALL(" + ind("\n" + q) + "\n)" 
  }

  case class Som(q: Query) extends Expr { 
    override def toString = "SOME(" + ind("\n" + q) + "\n)" 
  }

  // ---------- Conditions
  sealed abstract class Cond

  case class And(l: Cond, r: Cond) extends Cond { 
    override def toString = "(" + l + " AND " + r + ")" 
  }

  case class Or(l: Cond, r: Cond) extends Cond { 
    override def toString = "(" + l + " OR " + r + ")" 
  }

  case class Exists(q: Query) extends Cond { 
    override def toString = "EXISTS(" + ind("\n" + q) + "\n)" 
  }

  case class In(e: Expr, q: Query) extends Cond { 
    override def toString = e + " IN (" + ind("\n" + q) + "\n)" 
  }

  case class Not(e: Cond) extends Cond { 
    override def toString = "NOT(" + e + ")" 
  }

  case class Like(l: Expr, p: String) extends Cond { 
    override def toString = l + " LIKE '" + p + "'" 
  }

  case class Cmp(l: Expr, r: Expr, op: OpCmp) extends Cond { 
    override def toString = l + " " + op + " " + r 
  }
}
