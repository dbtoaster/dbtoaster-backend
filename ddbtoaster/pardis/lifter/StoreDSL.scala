package ddbt.lib.store.deep

import java.util.regex.Pattern

import ch.epfl.data.sc.pardis.deep.scalalib._
import ch.epfl.data.sc.pardis.deep.scalalib.collection.{ArrayBufferComponent, SeqComponent, SetComponent}
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.quasi.anf.BaseQuasiExp
import ch.epfl.data.sc.pardis.types.{NullType, PardisType, PardisVariableType}
import ch.epfl.data.sc.pardis.types.PardisTypeImplicits.{typeAny, typeUnit}
import ddbt.ast.{Type, TypeDouble, TypeLong}
import ddbt.lib.store._
import ddbt.transformer.{SEntry, SEntryFlag}
import lifter.{OnlineOptimizations, SCLMSInterop, TypeToTypeRep}

/**
  * Created by khayyam on 4/8/15.
  */

trait EntryOps extends Base {
  implicit val EntryType = EntryIRs.EntryType
  type Entry = ddbt.lib.store.Entry
}

trait EntryComponent extends EntryOps

object EntryIRs extends Base {

  case object EntryType extends TypeRep[Entry] {
    def rebuild(newArguments: TypeRep[_]*): TypeRep[_] = EntryType

    val name = "GenericEntry"
    val typeArguments = Nil
    val typeTag = scala.reflect.runtime.universe.typeTag[Entry]
  }

  implicit val typeEntry: TypeRep[Entry] = EntryType
}

case class StructFieldDecr[T: PardisType](struct: Expression[Any], index: String, rhs: Expression[T]) extends FunctionNode[Unit](Some(struct), s"${index} -=", List(List(rhs))) {
  override def curriedConstructor = (x: Expression[Any]) => { (r: Expression[T]) => copy[T](x, index, r) }

  override def rebuild(children: PardisFunArg*) = curriedConstructor.asInstanceOf[PardisFunArg => (PardisFunArg => PardisNode[Unit])](children(0))(children(1))
}

case class StructFieldIncr[T: PardisType](struct: Expression[Any], index: String, rhs: Expression[T]) extends FunctionNode[Unit](Some(struct), s"${index} +=", List(List(rhs))) {
  override def curriedConstructor = (x: Expression[Any]) => { (r: Expression[T]) => copy[T](x, index, r) }

  override def rebuild(children: PardisFunArg*) = curriedConstructor.asInstanceOf[PardisFunArg => (PardisFunArg => PardisNode[Unit])](children(0))(children(1))
}

trait StoreDSLOptimized extends StoreDSL with OnlineOptimizations {

  override def fieldIncr[T](struct: Expression[Any], index: String, rhs: Expression[T])(implicit tp: TypeRep[T]) = StructFieldIncr(struct, index, rhs)

  override def fieldDecr[T](struct: Expression[Any], index: String, rhs: Expression[T])(implicit tp: TypeRep[T]) = StructFieldDecr(struct, index, rhs)

}

trait StoreDSL extends
  StoreComponent with
  SCLMSInterop with
  BooleanComponent with
  DateComponent with
  StringComponent with
  StringExtraComponent with
  GenericEntryComponent with
  TypeToTypeRep with
  BaseQuasiExp with
  SetComponent with
  ArrayComponent with
  ArrayBufferComponent with
  ScalaPredefOps with
  AggregatorComponent with
  EntryComponent with
  EntryIdxComponent with
  IdxComponent with
  SeqComponent with
  BooleanExtraComponent with
  Tuple3Component with
  CFunctions with
  squid.scback.PardisBinding.DefaultPardisMixin {

  override val _IRReifier: IRReifier = new AnfIRReifier(this) {
    override def findOrCreateSymbol[T: TypeRep](definition: Def[T]): Sym[T] = {
      definition match {
        case Struct(tag, elems, _) => createAndReflectStatement[T](definition)
        case _ => super.findOrCreateSymbol(definition)
      }
    }
  }

  def fieldIncr[T](struct: Expression[Any], index: String, rhs: Expression[T])(implicit tp: TypeRep[T]): Expression[Unit] = fieldSetter(struct, index, numeric_plus(fieldGetter(struct, index)(tp), rhs))(tp)

  def fieldDecr[T](struct: Expression[Any], index: String, rhs: Expression[T])(implicit tp: TypeRep[T]): Expression[Unit] = fieldSetter(struct, index, numeric_minus(fieldGetter(struct, index)(tp), rhs))(tp)

  def nullValue(tp: TypeRep[_]): Expression[Any] = tp match {
    case IntType => unit(scala.Int.MinValue)
    case LongType => unit(scala.Int.MinValue.asInstanceOf[scala.Long])
    case DoubleType => unit(scala.Double.MinValue)
    case BooleanType => unit(false)
    case StringType => unit[String](null)
    case DateType => unit[Date](null)
    case PardisVariableType(ctp) => nullValue(ctp)
    case NullType => unit(null)
    case _ => System.err.println(s"Type $tp doesn't have nullValue defined"); unit(null)
  }

  def storeType(s: Sym[_]) = s.attributes.get[SEntry](SEntryFlag).getOrElse(SEntry())

  implicit def entryRepToGenericEntryOps(self: Rep[Entry]) = new GenericEntryRep(self.asInstanceOf[Rep[GenericEntry]])

  implicit def storeRepToStoreOps[E <: ddbt.lib.store.Entry](self: Rep[Store[E]])(implicit typeE: TypeRep[E]) = new StoreRep[E](self.asInstanceOf[Rep[Store[E]]])

  implicit class StoreRep1[E <: ddbt.lib.store.Entry](self: Rep[Store[E]])(implicit typeE: TypeRep[E]) {

    def slice1(f: Rep[E] => Rep[Unit], args: (Int, Rep[Any])*): Rep[Unit] = slice2(stSampleEntry(self.asInstanceOf[Rep[Store[E]]], args), f, -1)

    def slice2(key: Rep[E], f: Rep[E] => Rep[Unit], idx: Int = (-1)): Rep[Unit] = stSlice(self.asInstanceOf[Rep[Store[E]]], idx, key, f)

    //For TPCC
    def get1(args: (Int, Rep[Any])*): Rep[E] = {
      stGet(self.asInstanceOf[Rep[Store[E]]], stSampleEntry(self.asInstanceOf[Rep[Store[E]]], args))
    }


  }

  def __newStoreNamed[E <: ddbt.lib.store.Entry](name: String)(implicit cE: Manifest[E], typeE: TypeRep[E]): Rep[Store[E]] = IRReifier.reflectStm(Stm(freshNamed[Store[E]](name), StoreNew2[E]()(typeE, cE)))

  def __newStoreNamed2[E <: ddbt.lib.store.Entry](name: String, n: Rep[Int], ops: Rep[Array[EntryIdx[E]]])(implicit cE: Manifest[E], typeE: TypeRep[E]): Rep[Store[E]] = IRReifier.reflectStm(Stm(freshNamed[Store[E]](name), StoreNew3[E](n, ops)(typeE, cE)))

  override def storeIndex[E <: ddbt.lib.store.Entry](self: Rep[Store[E]], idx: Rep[Int], idxType: Rep[String], uniq: Rep[Boolean], otherIdx: Rep[Int])(implicit typeE: TypeRep[E]): Rep[Idx[E]] = {

    val sym = self.asInstanceOf[Sym[_]]
    val name = (if (sym.name.startsWith("x")) sym.name + sym.id else sym.name) + "Idx" + idx.asInstanceOf[Constant[_]].underlying
    IRReifier.reflectStm(Stm(freshNamed[Idx[E]](name), StoreIndex[E](self, idx, idxType, uniq, otherIdx)(typeE)))
  }

  //override   def record_newDef[T: TypeRep](fields: Seq[(String, Boolean, Rep[Any])]): Def[T] = {
  //  val fieldSyms = createFieldsSyms(fields)
  //  val tp = getRecordType[T]
  //  val tag = tp match {
  //    case tpe: RecordType[T] => tpe.tag
  //  }
  //  lazy val copyfn = doLambda0Def(() => record_new[T](fields)).asInstanceOf[PardisLambdaDef]
  //  Struct[T](tag, fieldSyms, List(PardisStructMethod("copy", copyfn, true)))(tp)
  //}
  //  case Def(v: PardisNewVar[_]) => {
  //          implicit val tp =v.tp.asInstanceOf[TypeRep[PardisVar[Any]]]
  //          implicit val tp2 =v.init.tp.asInstanceOf[TypeRep[Any]]
  //          val var_ = Var(rhs.asInstanceOf[Rep[PardisVar[Any]]])
  //          val val_ = readVar(var_)(tp2)
  //          PardisStructArg(index, true, val_)
  //        }
  override def createFieldsSyms(fields: Seq[(String, Boolean, Rep[Any])]): Seq[PardisStructArg] = {
    fields map {
      case (index, false, rhs) => PardisStructArg(index, false, rhs)
      case (index, true, rhs) => PardisStructArg(index, true, rhs)
    }
  }

  case object RegexType extends TypeRep[Pattern] {
    def rebuild(newArguments: TypeRep[_]*): TypeRep[_] = RegexType

    val name = "java.util.Pattern"
    val typeArguments = Nil
  }

  // Global variables
  val USE_UNIQUE_INDEX_WHEN_POSSIBLE = true
  val USE_STORE1 = true

  // whether we specialize temporary maps in Store1

  // cases classes
  case class M3Apply[T: TypeRep](name1: String, args1: List[Rep[_]]) extends FunctionDef[T](None, "U" + name1, List(args1)) {
    override def rebuild(children: FunctionArg*) = M3Apply[T](name1, children.asInstanceOf[List[Rep[Any]]])

    override def isPure: Boolean = true
  }

  def m3_apply[T: TypeRep](name1: String, args: List[Rep[_]]): Rep[T] = M3Apply[T](name1, args)


  //case class M3Add[E<:Entry:TypeRep](s:Rep[Store[E]], e:Rep[E]) extends FunctionDef[E](Some(s), "add", List(List(e)))

  // case class StNewStore[E<:Entry:TypeRep](tE: TypeRep[E]) extends ConstructorDef[Store[E]](List(tE), "Store", List(Nil))

  // case class SteGet[E<:Entry:TypeRep, T: TypeRep](x: Rep[E], i: Int) extends FunctionDef[T](Some(x), "get", List(List(unit(i))), List(implicitly[TypeRep[T]]))

  case class SteNewSEntry[E <: Entry : TypeRep](x: Rep[Store[E]], args: Seq[Rep[Any]]) extends FunctionDef[E](None, "GenericEntry", List(unit("SteNewSEntry") :: args.toList)) {
    override def rebuild(children: FunctionArg*) = SteNewSEntry(children(0).asInstanceOf[Rep[Store[E]]], children.drop(1).asInstanceOf[Seq[Rep[Any]]])
  }

  case class SteSampleSEntry[E <: Entry : TypeRep](x: Rep[Store[E]], args: Seq[(Int, Rep[Any])]) extends FunctionDef[E](None, "GenericEntry", List(unit("SteSampleSEntry") :: (args.map(e => unit(e._1)).toList ++ args.map(e => e._2).toList))) {
    override def rebuild(children: FunctionArg*) = {
      val argsSeq = children.drop(1)
      val (indices, values) = argsSeq.zipWithIndex.partition(x => x._2 < argsSeq.size / 2)
      val result = indices.map(_._1 match { case Constant(v) => v }).zip(values.map(_._1))
      SteSampleSEntry(children(0).asInstanceOf[Rep[Store[E]]], result.asInstanceOf[Seq[(Int, Rep[Any])]])
    }
  }

  //case class StDelete[E<:Entry:TypeRep](x: Rep[Store[E]], e: Rep[E]) extends FunctionDef[Unit](Some(x), "delete", List(List(e)))

  //case class StClear[E<:Entry:TypeRep](x: Rep[Store[E]]) extends FunctionDef[Unit](Some(x), "clear", List())

  //case class StUnsafeInsert[E<:Entry:TypeRep](s: Rep[Store[E]], e:Rep[E], idx:Int) extends FunctionDef[Unit](Some(s), "unsafeInsert", List(List(unit(idx), e)))

  //case class StSlice[E<:Entry:TypeRep](x: Rep[Store[E]], idx:Int, key:Rep[E], blockSym: Sym[E], block: Block[Unit]) extends FunctionDef[Unit](Some(x), "slice", List(Nil))


  def m3apply(fn: String, args: List[Rep[_]], tp: Type): Rep[_] = {
    fn match {
      case "div" => div(args(0).asInstanceOf[Rep[Double]])
      case "mul" => tp match {
        case TypeLong => mulLong(args(0).asInstanceOf[Rep[Long]], args(1).asInstanceOf[Rep[Long]])
        case TypeDouble => mulDouble(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
        case _ => m3_apply(fn, args)(man(tp))
      }
      case "listmax" => max(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
      case "listmin" => min(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
      case "substring" => substring(args(0).asInstanceOf[Rep[String]], args(1).asInstanceOf[Rep[Long]], args(2).asInstanceOf[Rep[Long]])
      case "date" => args(0) match {
        case Constant(strDate) => Constant(ddbt.lib.Functions.Udate(strDate.asInstanceOf[String]))
        case _ => m3_apply(fn, args)(man(tp))
      }
      case "date_part" => args(0) match {
        case Constant(t: String) if t.toLowerCase == "year" => m3_apply("year_part", args.drop(1))(man(tp))
        case _ => m3_apply(fn, args)(man(tp))
      }
      case _ => m3_apply(fn, args)(man(tp)) // fallback for large or unknown functions
    }
  }

  def m3temp[E <: Entry]()(implicit tp: TypeRep[E]): Rep[Store[E]] = {
    // val sym = StNewStore[E](tp)
    //sym.asInstanceOf[Sym[_]].attributes.put("_isTemp",true);
    implicit val manE = manifest[Int].asInstanceOf[Manifest[E]]
    val sym = __newStore[E]()
    sym.asInstanceOf[Rep[Store[E]]]
    //    null
  }

  def isTemp(s: Sym[_]): Boolean = false //s.attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)

  def m3add[E <: Entry](map: Rep[Store[E]], ent: Rep[E])(implicit m: TypeRep[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = unit(m.typeArguments.size)
    val lastMan = m.typeArguments.last

    //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
    //var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
    //println(s"tpeeee: ${m.typeArguments}")
    val entVal = ent.get(n.asInstanceOf[Rep[Int]])(lastMan)
    // if(tmp) {
    //   // we don't remove 0-elements
    //   if (USE_STORE1) {
    //     //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
    //     //addIndicesToEntryClass[E](map, (xx, m) => { val idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
    //     __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()), M3Add(map,ent).asInstanceOf[Rep[Store[E]]])// look at there :)
    //   } else {
    //     __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()), {
    //       ///////
    //       val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
    //       __ifThenElse(infix_==(currentEnt,unit(null)),/*stUnsafeInsert(map,ent,idx)*/ map.unsafeInsert(unit(idx), ent),currentEnt += (n, entVal))
    //       ///////
    //     })
    //   }
    // } else {
    // we remove 0-elements
    __ifThenElse(infix_==(entVal, unit(zero(lastMan))), unit(()), {
      ///////
      val currentEnt = stGet(map, ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
      __ifThenElse(infix_==(currentEnt, unit(null)), /*stUnsafeInsert(map,ent,idx)*/ map.unsafeInsert(ent), {
        currentEnt +=(n, entVal)
        val currentEntVal = currentEnt.get(n)(lastMan)
        __ifThenElse(infix_==(currentEntVal, unit(zero(lastMan))), map.deleteCopy(currentEnt), map.updateCopy(currentEnt)) // question ???? changed delete - stDelete
      })
      ///////
    })
    // }
    unit(())
  }

  def m3set[E <: Entry](map: Rep[Store[E]], ent: Rep[E])(implicit m: TypeRep[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = unit(m.typeArguments.size)
    val lastMan = m.typeArguments.last
    val currentEnt = stGet(map, ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
    val entVal = ent.get(n)(lastMan)

    //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
    //var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
    if (tmp) {
      // this never happens in practice
      __ifThenElse(infix_==(currentEnt, unit(null)), /*stUnsafeInsert(map,ent,idx)*/ map.unsafeInsert(ent), {
        currentEnt.update(n, entVal);
        map.updateCopy(currentEnt)
      }) // same
    } else {
      __ifThenElse(infix_==(entVal, unit(zero(lastMan))), {
        __ifThenElse(infix_==(currentEnt, unit(null)), unit(()), map.deleteCopy(currentEnt))
      }, {
        __ifThenElse(infix_==(currentEnt, unit(null)), /*stUnsafeInsert(map,ent,idx)*/ map.unsafeInsert(ent), {
          currentEnt.update(n, entVal);
          map.updateCopy(currentEnt)
        }) // same
      })
    }
  }

  def steGet[E <: Entry : TypeRep, T: TypeRep](x: Rep[E], i: Int): Rep[T] = //SteGet[E, T](x, i)
    x.get[T](unit(i))

  def stGet[E <: Entry : TypeRep](x: Rep[Store[E]], key: Rep[E]): Rep[E] = storeGetCopy(x, unit(0), key)(EntryType.asInstanceOf[TypeRep[E]])

  def stClear[E <: Entry : TypeRep](x: Rep[Store[E]]): Rep[Unit] = x.clear //StClear[E](x)

  def stUnsafeInsert[E <: Entry : TypeRep](x: Rep[Store[E]], e: Rep[E]): Rep[Unit] = x.unsafeInsert(e) //StUnsafeInsert[E](x, e)

  def stNewEntry[E <: Entry : TypeRep](x: Rep[Store[E]], args: Seq[Rep[Any]]) = SteNewSEntry[E](x, args)

  def stNewEntry2[E <: Entry : TypeRep](x: Rep[Store[E]], args: Rep[Any]*): Rep[E] = stNewEntry[E](x, args)

  def storeEntryType(sym: Rep[_]) = "GenericEntry" //XXX FIXIT extractEntryClassName(getStoreSym(sym))._1
  //
  //  def getStoreSym(s:Rep[_]) = s.asInstanceOf[Sym[_]]
  //
  //  def extractEntryClassName(n:Rep[_]) = {
  //    val sym = n.asInstanceOf[Sym[Store[Entry]]]
  //    val m = sym.tp
  //    val ms = m.typeArguments(0).toString
  //    val targs = m.typeArguments(0).typeArguments
  //    val fullClsName = ms.take(ms.indexOf("["))
  //    val baseClsName = fullClsName.takeRight(fullClsName.size - fullClsName.lastIndexOf('.') - 1)
  //    val targsStrList = targs.map(_.toString)//XXX FIXEIT targs.map(tp => remap(tp))
  //    val clsName = baseClsName+"_x"+sym.id+"_"+targsStrList.map(tp => simplifyTypeName(tp)).mkString
  //    (clsName, targsStrList)
  //  }

  def dtGetTime(x: Rep[Date]): Rep[Long] = dateGetTime(x)

  def stProxyGet[E <: Entry : TypeRep](x: Rep[Store[E]], args: (Int, Rep[Any])*): Rep[E] = stGet[E](x, stSampleEntry[E](x, args))

  def stSampleEntry[E <: Entry : TypeRep](x: Rep[Store[E]], args: Seq[(Int, Rep[Any])]): Rep[E] = SteSampleSEntry[E](x, args)

  def stDelete[E <: Entry : TypeRep](x: Rep[Store[E]], e: Rep[E]): Rep[Unit] = x.deleteCopy(e) //StDelete[E](x, e)


  def stSlice[E <: Entry : TypeRep](x: Rep[Store[E]], idx: Int, key: Rep[E], f: Rep[E] => Rep[Unit]): Rep[Unit] = {
    x.sliceCopy(unit(idx), key, f)

  }

  def stSlice[E <: Entry : TypeRep](x: Rep[Store[E]], f: Rep[E] => Rep[Unit], args: (Int, Rep[Any])*): Rep[Unit] = stSlice(x, 0, stSampleEntry(x, args), f)

  // FIXME
  def store2StoreOpsCls[E <: Entry](store: Rep[Store[E]]) = new StoreRep(store.asInstanceOf[Rep[Store[E]]])(runtimeType[Int].asInstanceOf[TypeRep[E]])

  // def dtGetYear(x: Rep[Date]): Rep[Long] = dateGetYear(x)

  // helper functions
  def div(x: Rep[Double]): Rep[Double] = __ifThenElse(unit(0) __== x, unit(0.0), unit(1.0) / x)

  def mulLong(l: Rep[Long], r: Rep[Long]): Rep[Long] = {
    val ll = (l match {
      case Constant(v) if l.tp.toString == "Double" => Constant(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => l
    })
    val rr = (r match {
      case Constant(v) if r.tp.toString == "Double" => Constant(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => r
    })
    numeric_times[Long](ll, rr)
  }

  def mulDouble(l: Rep[Double], r: Rep[Double]): Rep[Double] = {
    val ll = (l match {
      case Constant(v) if l.tp.toString == "Long" => Constant(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => l
    })
    val rr = (r match {
      case Constant(v) if r.tp.toString == "Long" => Constant(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => r
    })
    numeric_times[Double](ll, rr)
  }

  def max(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = __ifThenElse(v1 > v2, v1, v2)

  def min(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = __ifThenElse(v1 < v2, v1, v2)

  def substring(str: Rep[String], start: Rep[Long], length: Rep[Long]): Rep[String] = (str, start, length) match {
    case (Constant(s), Constant(t), Constant(l)) => Constant(s.substring(t.toInt, l.toInt))
    case (s, Constant(t), Constant(l)) => str.substring(unit(t.toInt), unit(l.toInt))
    case _ => str.substring(start.toInt, length.toInt)
  }

  // FIXIT -- deleted some parts from original quote
  //  def quote(x: Rep[Any], forcePrintSymbol: Boolean) : String = {
  //    x match {
  //      case Constant(s: String) => "\""+s.replace("\"", "\\\"").replace("\n", "\\n")+"\"" // TODO: more escapes?
  //      case Constant(c: Char) => "'"+c+"'"
  //      case Constant(f: Float) => "%1.10f".format(f) + "f"
  //      case Constant(l: Long) => l.toString + "L"
  //      case Constant(null) => "null"
  //      case Constant(z) => z.toString
  //      case s@Sym(n) => "burdayiq" //if (s.attributes.contains(nameAttr)) s.attributes(nameAttr).toString else "x"+s.id
  //      case _ => throw new RuntimeException("could not quote %s".format(x))
  //    }
  //  }

  implicit val typeNull = ch.epfl.data.sc.pardis.types.PardisTypeImplicits.typeAny.asInstanceOf[TypeRep[Null]]

  //implicit def typeStore[E <: ddbt.lib.store.Entry : TypeRep]: TypeRep[Store[E]] = MStoreType(implicitly[TypeRep[E]]).asInstanceOf[TypeRep[Store[E]]]
}