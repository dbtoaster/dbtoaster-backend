package ddbt.lib.store.deep

import ch.epfl.data.sc.pardis.deep.scalalib.StringComponent
import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.types.PardisTypeImplicits.{typeUnit, typeAny}
import ddbt.ast.{TypeDouble, TypeLong, Type}
import ddbt.lib.store._
import lifter.{SCLMSInterop, TypeToTypeRep}

/**
 * Created by khayyam on 4/8/15.
 */

trait StoreDSL extends MStoreComponent with SCLMSInterop with DateComponent with StringComponent with GenericEntryComponent with TypeToTypeRep {
  implicit case object EntryType extends TypeRep[Entry] {
    def rebuild(newArguments: TypeRep[_]*): TypeRep[_] = EntryType
    val name = "Entry"
    val typeArguments = Nil
    val typeTag = scala.reflect.runtime.universe.typeTag[Entry]
  }

  implicit def entryRepToGenericEntryOps(self : Rep[Entry]) = new GenericEntryRep(self.asInstanceOf[Rep[GenericEntry]])
  implicit def storeRepToStoreOps[E <: ddbt.lib.store.Entry](self : Rep[Store[E]])(implicit typeE : TypeRep[E]) = new MStoreRep[E](self.asInstanceOf[Rep[MStore[E]]])

  // Global variables
  val USE_UNIQUE_INDEX_WHEN_POSSIBLE = true
  val USE_STORE1 = true // whether we specialize temporary maps in Store1

  // cases classes
  case class M3Apply[T: TypeRep](name1:String,args1:List[Rep[_]]) extends FunctionDef[T](None, "U" + name1, List(args1)) {

  }
  def m3_apply[T: TypeRep](name1: String, args: List[Rep[_]]): Rep[T] = M3Apply[T](name1, args)

  case class M3Add[E<:Entry:TypeRep](s:Rep[Store[E]], e:Rep[E]) extends FunctionDef[E](Some(s), "add", List(List(e)))

  case class StNewStore   [E<:Entry:TypeRep](tE: TypeRep[E]) extends ConstructorDef[Store[E]](List(tE), "Store", List(Nil))

  case class SteGet[E<:Entry:TypeRep](x: Rep[E], i: Int) extends FunctionDef[E](None, "get", List(List(x), List(unit(i))))

  case class SteNewSEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[Rep[Any]]) extends FunctionDef[E](None, "GenericEntry", List(x::args.toList))

  case class SteSampleSEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[(Int,Rep[Any])]) extends FunctionDef[E](None, "GenericEntry", List(x::args.map(_._2).toList))

  case class StDelete[E<:Entry:TypeRep](x: Rep[Store[E]], e: Rep[E]) extends FunctionDef[Unit](Some(x), "delete", List(List(e)))

  case class StClear[E<:Entry:TypeRep](x: Rep[Store[E]]) extends FunctionDef[Unit](Some(x), "clear", List())

  case class StUnsafeInsert[E<:Entry:TypeRep](s: Rep[Store[E]], e:Rep[E], idx:Int) extends FunctionDef[Unit](Some(s), "unsafeInsert", List(List(unit(idx), e)))

    // case class SteNewSEntry   [E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[Rep[Any]]) extends Def[E]
  // case class SteSampleSEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[(Int,Rep[Any])]) extends Def[E]

  def m3apply(fn:String,args:List[Rep[_]],tp:Type): Rep[_] = {
    fn match {
      case "div" => div(args(0).asInstanceOf[Rep[Double]])
      case "mul" => tp match {
        case TypeLong => mulLong(args(0).asInstanceOf[Rep[Long]], args(1).asInstanceOf[Rep[Long]])
        case TypeDouble => mulDouble(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
        case _ => m3_apply(fn,args)(man(tp))
      }
      case "listmax" => max(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "listmin" => min(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "substring" => substring(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[Long]],args(2).asInstanceOf[Rep[Long]])
      case "date" => args(0) match {
        case Constant(strDate) => Constant(ddbt.lib.Functions.Udate(strDate.asInstanceOf[String]))
        case _ => m3_apply(fn,args)(man(tp))
      }
      case _ => m3_apply(fn,args)(man(tp)) // fallback for large or unknown functions
    }
  }

  def m3temp[E<:Entry]()(implicit tp:TypeRep[E]):Rep[Store[E]] = {
    val sym = StNewStore[E](tp)
    //sym.asInstanceOf[Sym[_]].attributes.put("_isTemp",true);
    sym
//    null
  }

  def isTemp(s:Sym[_]):Boolean = false//s.attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)

  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:TypeRep[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = unit(m.typeArguments.size)
    val lastMan = m.typeArguments.last

    //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
    //var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
    var idx = 0

    val entVal = ent.get(n.asInstanceOf[Rep[Int]])
    if(tmp) {
      // we don't remove 0-elements
      if (USE_STORE1) {
        //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
        //addIndicesToEntryClass[E](map, (xx, m) => { val idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
        __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()), M3Add(map,ent).asInstanceOf[Rep[Store[E]]])// look at there :)
      } else {
        __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()), {
          ///////
          val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
          __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt += (n, entVal))
          ///////
        })
      }
    } else {
      // we remove 0-elements
      __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()), {
        ///////
        val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
        __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),{
          currentEnt += (n, entVal)
          val currentEntVal = currentEnt.get(n)
          __ifThenElse(infix_==(currentEntVal,unit(zero(lastMan))), map.delete(currentEnt), unit(())) // question ???? changed delete - stDelete
        })
        ///////
      })
    }
    unit(())
  }

  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:TypeRep[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = m.typeArguments.size.asInstanceOf[Rep[Int]]
    val lastMan = m.typeArguments.last
    val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
    val entVal = ent.get(n)

    //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
    //var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
    var idx = 0
    if(tmp) { // this never happens in practice
      __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt.update(n, entVal)) // same
    } else {
      __ifThenElse(infix_==(entVal,unit(zero(lastMan))),{
        __ifThenElse(infix_==(currentEnt,unit(null)),unit(()), map.delete(currentEnt))
      },{
        __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt.update(n, entVal)) // same
      })
    }
  }

  def steGet[E<:Entry:TypeRep](x: Rep[E], i: Int):Rep[Any] = SteGet[E](x, i).asInstanceOf[Rep[Any]]
  def stGet[E<:Entry:TypeRep](x: Rep[Store[E]], idx:Int, key:Rep[E]):Rep[E] = x.get(unit(idx), key)
  def stClear[E<:Entry:TypeRep](x: Rep[Store[E]]):Rep[Unit] = StClear[E](x)

  def stUnsafeInsert[E<:Entry:TypeRep](x: Rep[Store[E]], e: Rep[E], idx:Int):Rep[Unit] = StUnsafeInsert[E](x, e, idx)

  def stNewEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[Rep[Any]]) = SteNewSEntry[E](x, args)
  def stNewEntry2[E<:Entry:TypeRep](x: Rep[Store[E]], args:Rep[Any]*):Rep[E] = stNewEntry[E](x, args)

  def storeEntryType(sym:Rep[_]) = "GenericEntry" //XXX FIXIT extractEntryClassName(getStoreSym(sym))._1
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
  def stProxyGet[E<:Entry: TypeRep](x: Rep[Store[E]], args:(Int,Rep[Any])*):Rep[E] = steGet(stSampleEntry(x, args),-1).asInstanceOf[Rep[E]]
  def stSampleEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[(Int,Rep[Any])]):Rep[E] = SteSampleSEntry[E](x, args)

  def stDelete[E<:Entry:TypeRep](x: Rep[Store[E]], e: Rep[E]):Rep[Unit] = StDelete[E](x, e)


  // FIXME
  def store2StoreOpsCls[E <: Entry](store: Rep[Store[E]]) = new MStoreRep(store.asInstanceOf[Rep[MStore[E]]])(runtimeType[Int].asInstanceOf[TypeRep[E]])
  // def dtGetYear(x: Rep[Date]): Rep[Long] = dateGetYear(x)

  // helper functions
  def div(x: Rep[Double]): Rep[Double] = unit(1.0) / x

  def mulLong(l: Rep[Long], r: Rep[Long]): Rep[Long] = {
    val ll = (l match {
      case Constant(v) if l.tp.toString=="Double" => Constant(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => l
    })
    val rr = (r match {
      case Constant(v) if r.tp.toString=="Double" => Constant(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => r
    })
    numeric_times[Long](ll,rr)
  }
  def mulDouble(l: Rep[Double], r: Rep[Double]): Rep[Double] = {
    val ll = (l match {
      case Constant(v) if l.tp.toString=="Long" => Constant(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => l
    })
    val rr = (r match {
      case Constant(v) if r.tp.toString=="Long" => Constant(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => r
    })
    numeric_times[Double](ll,rr)
  }
  def max(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = __ifThenElse(v1 > v2, v1, v2)
  def min(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = __ifThenElse(v1 < v2, v1, v2)
  def substring(str: Rep[String], start: Rep[Long], length: Rep[Long]): Rep[String] = null


  // code generator functions // XXX fixeit
  def generateNewStore(c: Sym[_], mname:String = "", isClassLevel:Boolean=false):String = {
    val outStream = new java.io.StringWriter
    val out = new java.io.PrintWriter(outStream)

//    val idxArr = c.attributes.get(ENTRY_INDICES_KEY) match {
//      case Some(m) => m.asInstanceOf[collection.mutable.ArrayBuffer[(IndexType,Seq[Int],Boolean,Int)]]
//      case None => val m = new collection.mutable.ArrayBuffer[(IndexType,Seq[Int],Boolean,Int)]
//        m += ((IList, (1 to c.tp.typeArguments.size),false,-1))
//    }
    val idxArr = List()
    val cName = mname//c.name + c.id //XXX - fixeit quote(c, true)
    val entTp = storeEntryType(c)
//    out.println("val "+cName+" = new Store["+entTp+"]("+idxArr.size+",Array[EntryIdx["+entTp+"]]("+(0 until idxArr.size).map(i=>entTp+"_Idx"+i).mkString(",")+"))")
    out.println("val "+cName+" = new Store["+entTp+"](0)")
    out.println(s"val ${c.name+c.id} = $cName")

//    idxArr.zipWithIndex.foreach { case ((idxType, idxLoc, idxUniq, idxSliceIdx), i) => idxType match {
//      case IList => out.println("%s.index(%d,IList,%s)".format(cName, i, idxUniq))
//      case IHash => out.println("%s.index(%d,IHash,%s)".format(cName, i, idxUniq))
//      case ISliceHeapMax => out.println("%s.index(%d,ISliceHeapMax,%s,%d)".format(cName, i, idxUniq, idxSliceIdx))
//      case ISliceHeapMin => out.println("%s.index(%d,ISliceHeapMin,%s,%d)".format(cName, i, idxUniq, idxSliceIdx))
//      case _ => sys.error("Index type "+idxType+" not supported")
//    }}


    outStream.toString
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
  implicit def typeStore[E <: ddbt.lib.store.Entry: TypeRep]: TypeRep[Store[E]] = MStoreType(implicitly[TypeRep[E]]).asInstanceOf[TypeRep[Store[E]]]
}