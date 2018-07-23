package ddbt.ast

import ddbt.lib.Utils.ind
import ddbt.lib.TypeMismatchException

/**
  * Defines basic types AST nodes for M3 and SQL 
  */
sealed abstract class Tree    // Generic AST node

// ------ Data types 
sealed abstract class Type extends Tree {
  def resolve(b: Type): Type
}
case object TypeChar extends Type {
  def resolve(b: Type) = b match {
    case TypeChar | TypeShort | TypeInt | TypeLong | TypeFloat | TypeDouble => b
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }
  override def toString = "char"
}
case object TypeShort extends Type {
  def resolve(b: Type) = b match {
    case TypeChar | TypeShort => this
    case TypeInt | TypeLong | TypeFloat | TypeDouble => b
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }
  override def toString = "short" 
}
case object TypeInt extends Type {
  def resolve(b: Type) = b match {
    case TypeChar | TypeShort | TypeInt | TypeDate => this
    case TypeLong | TypeFloat | TypeDouble => b
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }
  override def toString = "int" 
}
case object TypeLong extends Type {
  def resolve(b: Type) = b match {
    case TypeChar | TypeShort | TypeInt | TypeLong | TypeDate => this
    case TypeFloat | TypeDouble => b
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }
  override def toString = "long" 
}
case object TypeFloat extends Type { 
  def resolve(b: Type) = b match {
    case TypeChar | TypeShort | TypeInt | TypeLong | TypeFloat => this
    case TypeDouble => b
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }
  override def toString = "float" 
}
case object TypeDouble extends Type { 
  def resolve(b: Type) = b match {
    case TypeChar | TypeShort | TypeInt | TypeLong | TypeFloat | TypeDouble => this
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }
  override def toString = "double" 
}
case object TypeDate extends Type {
  def resolve(b: Type) = b match {
    case TypeDate => this
    case TypeInt | TypeLong => b    // no other integer types allowed
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }  
  override def toString = "date" 
}
case object TypeString extends Type { 
  def resolve(b: Type) = b match {
    case TypeString => this
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }    
  override def toString = "string" 
}
case class TypeCustom(val name: String, val typeDef: TypeDefinition) extends Type { 
  def resolve(b: Type) = b match {
    case TypeChar | TypeShort | TypeInt | TypeLong | TypeFloat | TypeDouble => this
    case b: TypeCustom if typeDef == b.typeDef => this
    case _ => throw new TypeMismatchException("Type mismatch (" + this + ", " + b + ")")
  }
  override def toString = name
}

// ------ Comparison operators
sealed abstract class OpCmp extends Tree
case object OpEq extends OpCmp { override def toString = "=" }
case object OpNe extends OpCmp { override def toString = "!=" }
case object OpGt extends OpCmp { override def toString = ">" }
case object OpGe extends OpCmp { override def toString = ">=" }

// ---------- Schema, adaptor, and source definitions
case class Source(isStream: Boolean, schema: Schema, in: SourceIn, split: Split, adaptor: Adaptor, locality: LocalityType) extends Tree { 
  override def toString = 
    "CREATE " + (if (isStream) "STREAM" else "TABLE") + " " + schema + 
    "\n  FROM " + in + " " + split + " " + adaptor + 
    (locality match {
      case LocalExp => ""
      case DistRandomExp => "\n  PARTITIONED RANDOMLY"
      case DistByKeyExp(pk) => "\n  PARTITIONED BY [" + pk.map(_._1).mkString(", ") + "]"
    }) + ";"
}

case class Schema(name: String, fields: List[(String, Type)]) extends Tree { 
  override def toString = 
    name + " (" + fields.map { case (n, t) => n + " " + t }.mkString(", ") + ")"
}

sealed abstract class SourceIn extends Tree
case class SourceFile(path: String) extends SourceIn { 
  override def toString = "FILE '" + path + "'" 
}

sealed abstract class Split extends Tree
case object SplitLine extends Split {
  override def toString = "LINE DELIMITED" 
}
case class SplitSize(bytes: Int) extends Split {
  override def toString = "FIXEDWIDTH " + bytes 
}
case class SplitSep(delim: String) extends Split { 
  override def toString = "'" + delim + "' DELIMITED" 
}
case class SplitPrefix(bytes: Int) extends Split {
  override def toString = "PREFIXED " + bytes 
} // records are prefixed with their length in bytes

case class Adaptor(name: String, options: Map[String, String]) extends Tree {
  override def toString = 
    name + ( if (options.isEmpty) ""
             else " (" + options.map { case (k, v) => k + " := '" + v + "'" }.mkString(", ") + ")" )
}

// ------ Custom type definitions
case class TypeDefinition(val name: String, val path: String) {
  override def toString = "CREATE TYPE " + name + " FROM FILE " + path + ";"
}

// ------ Expression locality types
abstract sealed class LocalityType extends Tree
case object LocalExp extends LocalityType {
  override def toString = "<Local>"
}
case object DistRandomExp extends LocalityType {
  override def toString = "<DistRandom>"
}
case class DistByKeyExp(pkeys: List[(String, Type)]) extends LocalityType {
  override def toString = "<DistByKey(" + pkeys.map(_._1).mkString(", ") + ")>"
}


// -----------------------------------------------------------------------------
// M3 language

sealed abstract class M3 extends Tree   // see ddbt.frontend.Parsers

object M3 {

  // ---------- Map update operators
  sealed abstract class OpMap extends M3
  case object OpSet extends OpMap { override def toString = " := " }
  case object OpAdd extends OpMap { override def toString = " += " }

  //---------- Map types
  sealed abstract class StoreType extends M3
  case object IndexedStore extends StoreType       // Default store type (row-oriented Store)
  case object ArrayStore   extends StoreType       // Array store (row-oriented, only foreach)
  case object LogStore     extends StoreType       // Columnar store (only append and foreach)
  case class  PartitionStore(pkeys: List[Int]) extends StoreType     // Multiple log stores

  // -------- M3 system
  case class System(typeDefs: List[TypeDefinition], sources: List[Source], maps: List[MapDef], queries: List[Query], triggers: List[Trigger]) extends M3 {
    override def toString =
      "---------------- TYPE DEFINITIONS ---------------\n" +
      typeDefs.mkString("\n\n") + "\n\n" + 
      "-------------------- SOURCES --------------------\n" + 
      sources.mkString("\n\n") + "\n\n" + 
      "--------------------- MAPS ----------------------\n" + 
      maps.mkString("\n\n") + "\n\n" +
      "-------------------- QUERIES --------------------\n" + 
      queries.mkString("\n\n") + "\n\n" +
      "------------------- TRIGGERS --------------------\n" + 
      triggers.mkString("\n\n")
  }

  // ---------- Map definition statement
  case class MapDef(name: String, tp: Type, keys: List[(String, Type)], expr: Expr, locality: LocalityType) extends M3 {
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
  }

  // -------- Query definition
  case class Query(name: String, expr: Expr) extends M3 {
    override def toString = "DECLARE QUERY " + name + " := " + expr + ";"
  }

  // -------- Trigger definition
  case class Trigger(event: EventTrigger, stmts: List[Statement]) extends M3 {
    override def toString = "ON " + event + " {\n" + ind(stmts.mkString("\n")) + "\n}" 
  }

  sealed abstract class EventTrigger extends M3 { 
    def name: String
    def schema: Schema 
    def params: List[(String, Type)]
  }

  case object EventReady extends EventTrigger { 
    override val name = "system_ready"
    override val schema = Schema("", Nil) 
    override val params = Nil
    override def toString = "SYSTEM READY"
  }

  case class EventInsert(schema: Schema) extends EventTrigger { 
    override val name = "insert_" + schema.name 
    override val params = schema.fields
    override def toString = 
      "+ " + schema.name + " (" + schema.fields.map(_._1).mkString(", ") + ")"
  }

  case class EventDelete(schema: Schema) extends EventTrigger { 
    override val name = "delete_" + schema.name 
    override val params = schema.fields
    override def toString = 
      "- " + schema.name + " (" + schema.fields.map(_._1).mkString(", ") + ")"
  }

  case class EventBatchUpdate(schema: Schema) extends EventTrigger { 
    override val name = "batch_" + schema.name 
    override val params = Nil
    override def toString = "BATCH UPDATE OF " + schema.name
  }

  // ---------- Update or assign statement
  abstract class Statement extends M3

  case class TriggerStmt(target: MapRef, expr: Expr, op: OpMap, initExpr: Option[Expr]) extends Statement { 
    override def toString =
      target + initExpr.map(":(" + _ + ")").getOrElse("") + " " + op + " " + expr + ";"
  }

  case class IfStmt(cond: Cmp, thenBlk: List[Statement], elseBlk: List[Statement]) extends Statement {
    override def toString = 
      "if (" + cond + ") {" +
        ind(thenBlk.mkString("\n")) +
      "} else {" +
        ind(elseBlk.mkString("\n")) +
      "}"
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
        case Mul(l, r) => new Mul(l.replace(f), r.replace(f), tp)          
        case a @ Add(l, r) => new Add(l.replace(f), r.replace(f), tp)
        case Cmp(l, r, op) => Cmp(l.replace(f), r.replace(f), op)
        case CmpOrList(l, r) => CmpOrList(l.replace(f), r.map(_.replace(f)))
        case Exists(e) => Exists(e.replace(f))
        case Lift(n, e) => Lift(n, e.replace(f))
        case AggSum(ks, e) => AggSum(ks, e.replace(f))
        case Apply(fn, tp, as) => Apply(fn, tp, as.map(_.replace(f)))
        case Tuple(es) => new Tuple(es.map(_.replace(f)), tp)
        case TupleLift(ns, e) => TupleLift(ns, e.replace(f))
        case Repartition(ks, e) => Repartition(ks, e.replace(f))
        case Gather(e) => Gather(e.replace(f))
        case _ => ex
      })

    def rename(r: String => String): Expr = replace {
      case Ref(n) => new Ref(r(n), tp)
      case m @ MapRef(n, tp, ks, isTemp) =>
        new MapRef(r(n), tp, ks.map(x => (r(x._1), x._2)), isTemp, 
          m.locality match { 
            case Some(DistByKeyExp(pkeys)) => Some(DistByKeyExp(pkeys.map(x => (r(x._1), x._2))))
            case Some(DistRandomExp) => Some(DistRandomExp)
            case Some(LocalExp) => Some(LocalExp)
            case None => None
          })
      case Lift(n, e) => Lift(r(n), e.rename(r))
      case AggSum(ks, e) => AggSum(ks.map(x => (r(x._1), x._2)), e.rename(r)) 
      case Repartition(ks, e) => Repartition(ks.map(x => (r(x._1), x._2)), e.rename(r))
      case a @ Add(el, er) => new Add(el.rename(r), er.rename(r), a.tp)
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
        case MapRef(n, tp, ks, tmp) => (List(), ks)
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
        case (MapRef(n1, tp1, ks1, tmp1), MapRef(n2, tp2, ks2, tmp2)) =>
          if (n1 != n2 || ks1.length != ks2.length || tmp1 != tmp2) None
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

    def toDecoratedString: String
  }

  // Constants
  case class Const(tp: Type, v: String) extends Expr { 
    val locality: Option[LocalityType] = None
    override def toString = if (tp == TypeString) "'" + v + "'" else v 
    def toDecoratedString = toString + ": " + tp
  }

  // Variables
  case class Ref(name: String) extends Expr { 
    var tp: Type = null 
    def this(name0: String, tp0: Type) = { this(name0); tp = tp0 }
    val locality: Option[LocalityType] = None
    override def toString = name
    def toDecoratedString = name + ": " + tp
  }

  // Map reference
  case class MapRef(name: String, var tp: Type, var keys: List[(String, Type)], val isTemp: Boolean = false) extends Expr {
    var locality: Option[LocalityType] = Some(LocalExp)

    def this(name0: String, tp0: Type, keys0: List[(String, Type)], 
             isTemp0: Boolean, locality0: Option[LocalityType]) = {
      this(name0, tp0, keys0, isTemp0)
      locality = locality0;
    }

    override def toString = 
      name + (if (tp != null) "(" + tp + ")" else "") + "[][" + 
      keys.map(_._1).mkString(", ") + "]" + locality.getOrElse("")

    def toDecoratedString = 
      name + (if (tp != null) "(" + tp + ")" else "") + "[][" + 
      keys.map(k => k._1 + ": " + k._2).mkString(", ") + "]" + locality.getOrElse("")
  }

  // Lifting operator ('Let name=e in ...' semantics)
  case class Lift(name: String, e: Expr) extends Expr { 
    val tp = TypeChar
    def locality = e.locality
    override def toString = "(" + name + " ^= " + e + ")"
    def toDecoratedString = "(" + name + " ^= " + e.toDecoratedString + ")" + ": " + tp
  }

  // Map reference of a table
  case class MapRefConst(name: String, keys: List[(String, Type)]) extends Expr { 
    val tp = TypeLong
    var locality: Option[LocalityType] = None
    override def toString = name + "(" + keys.map(_._1).mkString(", ") + ")"
    def toDecoratedString = name + "(" + keys.map(k => k._1 + ": " + k._2).mkString(", ") + "): " + tp
  }

  // Map reference of a delta update
  case class DeltaMapRefConst(name: String, keys: List[(String, Type)]) extends Expr { 
    val tp = TypeLong
    var locality: Option[LocalityType] = None
    override def toString = "(DELTA " + name + ")(" + keys.map(_._1).mkString(", ") + ")"
    def toDecoratedString = "(DELTA " + name + ")(" + keys.map(k => k._1 + ": " + k._2).mkString(", ") + "): " + tp
  }

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
    def toDecoratedString =
      "AggSum([" + keys.map(k => k._1 + ": " + k._2).mkString(", ") + "],\n" + ind(e.toDecoratedString) + "\n): " + tp
  }

  // Multiplication operator
  case class Mul(l: Expr, r: Expr) extends Expr { 
    var tp: Type = null 
    def this(l0: Expr, r0: Expr, tp0: Type) = { this(l0, r0); tp = tp0 }
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
    def toDecoratedString = "(" + l.toDecoratedString + " * " + r.toDecoratedString + ")"
  }

  // Union operator
  case class Add(l: Expr, r: Expr) extends Expr { 
    var tp: Type = null
    def this(l0: Expr, r0: Expr, tp0: Type) = { this(l0, r0); tp = tp0 }
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
    def toDecoratedString = "(" + l.toDecoratedString + " + " + r.toDecoratedString + ")"
  }

  // Exists operator - returns 0 or 1 (checks if there is at least one tuple)
  case class Exists(e: Expr) extends Expr { 
    val tp = TypeChar 
    def locality = e.locality
    override def toString = "EXISTS(" + e + ")"
    def toDecoratedString = "EXISTS(" + e.toDecoratedString + "): " + tp
  }

  // Function application
  case class Apply(fun: String, var tp: Type, args: List[Expr]) extends Expr {
    val locality: Option[LocalityType] = None
    override def toString = "[" + fun + ": " + tp + "](" + args.mkString(", ") + ")"
    def toDecoratedString = "[" + fun + ": " + tp + "](" + args.map(_.toDecoratedString).mkString(", ") + ")"
  }

  // Comparison, returns 0 or 1
  case class Cmp(l: Expr, r: Expr, op: OpCmp) extends Expr { 
    val tp = TypeChar    
    val locality: Option[LocalityType] = None
    override def toString = "{" + l + " " + op + " " + r + "}"
    def toDecoratedString = "{" + l.toDecoratedString + " " + op + " " + r.toDecoratedString + "}: " + tp
  }

  // OR comparison with a given expr list, returns 0 or 1
  case class CmpOrList(l: Expr, r: List[Expr]) extends Expr {
    val tp = TypeChar
    val locality: Option[LocalityType] = None
    override def toString = "{" + l + " IN [" + r.mkString(", ") + "]}"
    def toDecoratedString = "{" + l.toDecoratedString + " IN [" + r.map(_.toDecoratedString).mkString(", ") + "]}: " + tp
  }

  // Tupling
  case class Tuple(es: List[Expr]) extends Expr { 
    var tp: Type = null 
    def this(es0: List[Expr], tp0: Type) = { this(es0); tp = tp0 }
    val locality: Option[LocalityType] = None
    override def toString = "<" + es.mkString(", ") + ">"
    def toDecoratedString = "<" + es.map(_.toDecoratedString).mkString(", ") + ">: " + tp
  }

  // Lifting operator with tuples
  case class TupleLift(ns: List[String], e: Expr) extends Expr { 
    val tp = TypeChar
    val locality: Option[LocalityType] = None
    override def toString = "(<" + ns.mkString(", ") + "> ^= " + e + ")"
    def toDecoratedString = 
      "(<" + ns.mkString(", ") + "> ^= " + e.toDecoratedString + "): " + tp
  }

  // Distributed operation - repartion by key
  case class Repartition(var ks: List[(String, Type)], e: Expr) extends Expr { 
    def tp = e.tp    
    def locality = Some(DistByKeyExp(ks))
    override def toString = 
      "Repartition([" + ks.map(_._1).mkString(", ") + "],\n" + ind(e.toString) + "\n)"
    def toDecoratedString = 
      "Repartition([" + ks.map(k => k._1 + ": " + k._2).mkString(", ") + "],\n" + ind(e.toDecoratedString) + "\n): " + tp
  } 

  // Distributed operation - gather on master
  case class Gather(e: Expr) extends Expr { 
    def tp = e.tp    
    val locality = Some(LocalExp)    
    override def toString = "Gather(" + e + ")"
    def toDecoratedString = "Gather(" + e.toDecoratedString + "): " + tp
  } 
}

// -----------------------------------------------------------------------------
// SQL (http://www.contrib.andrew.cmu.edu/~shadow/sql/sql1992.txt)

sealed abstract class SQL // see ddbt.frontend.Parsers

object SQL {

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
