package ddbt.codegen.lms
import ddbt.ast._
import oltp.opt.lifters._
import ddbt.lib.store._
import ManifestHelper._

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.reflect.SourceContext
import ddbt.Utils.ind

/**
 * The following LMS operations are implemented by these traits:
 * - Named expressions (possibly mutable) to beautify the emitted code
 * - M3 maps specific operations (get, set, add, foreach, slice, clear)
 * - Abstraction of user-library function application (inlined in m3apply)
 *
 * @author Mohammad Dashti
 */
trait M3StoreOps extends StoreOps with Equal with IfThenElse {
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]
  // M3-specific operations
  def m3temp[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]]
  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]):Rep[Unit]
  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]):Rep[Unit]
}

trait M3StoreOpsExp extends BaseExp with EffectExp with M3StoreOps with StoreExp with EqualExp with IfThenElseExp {
  import ManifestHelper.man
  val USE_STORE1 = true // whether we specialize temporary maps in Store1

  def named(name:String,tp:Type,mutable:Boolean=false) = named(name,mutable)(man(tp))
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]) = { val n=Named(name)(mT); if (mutable) reflectMutable(n) else n }
  def m3temp[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]] = {
    val sym=newStore[E]; sym.asInstanceOf[Sym[_]].attributes.put("_isTemp",true); sym
  }
  def isTemp(s:Sym[_]) = s.attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)

  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last

    val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,false,-1))
    var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })

    if(tmp) {
      // we don't remove 0-elements
      if (USE_STORE1) {
        //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,false,-1))
        //addIndicesToEntryClass[E](map, (xx, m) => { val idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
        reflectWrite(map)(M3Add(map,ent))
      } else {
        val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
        __ifThenElse(__equal(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt += (n, ent.get(n)))
      }
    } else {
      // we remove 0-elements
      val entVal = ent.get(n)
      __ifThenElse(__equal(entVal,unit(zero(lastMan))), unit(()), {
        ///////
        val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
        __ifThenElse(__equal(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),{
          currentEnt += (n, entVal)
          val currentEntVal = currentEnt.get(n)
          __ifThenElse(__equal(currentEntVal,unit(zero(lastMan))),map.delete(currentEnt),unit(()))
        })
        ///////
      })
    }
    unit(())
  }
  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last
    val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
    val entVal = ent.get(n)

    val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,false,-1))
    var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })

    if(tmp) { // this never happens in practice
      __ifThenElse(__equal(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt.update(n, entVal)) // same
    } else {
      __ifThenElse(__equal(entVal,unit(zero(lastMan))),{
        __ifThenElse(__equal(currentEnt,unit(null)),unit(()),map.delete(currentEnt))
      },{
        __ifThenElse(__equal(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt.update(n, entVal)) // same
      })
    }
  }

  override def stGet[E<:Entry:Manifest](x: Exp[Store[E]], idx_in:Int,key:Exp[E]):Exp[E] = {
    var idx = idx_in
    key match {
      case Def(Reflect(SteSampleSEntry(_, args),_,_)) => addIndicesToEntryClass[E](x, (xx, m) => {
        val tupVal = ((IHash,args.map(_._1),false,-1)) //if(isTemp) ((IHash,args.map(_._1),false,-1)) else ((IHash,args.map(_._1),true,-1))
        idx = m.indexOf(tupVal)
        if(idx < 0) {
          m += tupVal
          idx = m.size - 1
        }
      })
      case _ =>
        val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,false,-1))
        addIndicesToEntryClass[E](x, (xx, m) => {
          idx = m.indexOf(tupVal)
          if(idx < 0) { m+=tupVal; idx=m.size-1 }
        })
        //throw new GenerationFailedException("You should provide a sample entry to this method: Store.get")
    }
    val elem:Exp[E]=StGet[E](x,idx,key)
    steMakeMutable(elem)
  }

  case class Named[T](n:String)(implicit mT:Manifest[T]) extends Def[T]
  case class M3Add[E<:Entry:Manifest](s: Exp[Store[E]], e:Exp[E]) extends Def[Unit]

  def stUnsafeInsert[E<:Entry:Manifest](x: Exp[Store[E]], e: Exp[E], idx:Int):Exp[Unit] = reflectWrite(x)(StUnsafeInsert[E](x, e, idx))
  case class StUnsafeInsert[E<:Entry:Manifest](s: Exp[Store[E]], e:Exp[E],idx:Int) extends Def[Unit]
}

trait ScalaGenM3StoreOps extends ScalaGenBase with ScalaGenEffect with ScalaGenStore {
  val IR: M3StoreOpsExp with ExtendedExpressions with Effects
  import IR._
  import ddbt.Utils.{ind,tup}

  // Specialization of temporary maps into Entry1 / Store1
  override def generateNewStore(s: Sym[_]):String =
    if (USE_STORE1 && isTemp(s)) "val "+quote(s,true)+" = new Store1["+storeEntryType(s)+"]()\n"
    else super.generateNewStore(s)
  override def emitDataStructures(out: java.io.PrintWriter): Unit = {
    if (USE_STORE1) {
      val (temp,global) = storeSyms.partition(s => isTemp(s))
      out.println
      temp.foreach { sym =>
        val indices = sym.attributes.get(ENTRY_INDICES_KEY).asInstanceOf[Option[collection.mutable.ArrayBuffer[(IndexType,Seq[Int],Boolean,Int)]]].getOrElse(new collection.mutable.ArrayBuffer[(IndexType,Seq[Int],Boolean,Int)])
        val idx0loc = indices(0)._2
        val (clsName, argTypes) = extractEntryClassName(sym)
        val n = argTypes.size
        out.println("case class "+clsName+"("+argTypes.zipWithIndex.map{ case (tp,i) => "var _"+(i+1)+":"+tp+" = "+zeroValue(tp) }.mkString(", ")+") extends Entry1["+clsName+"] {")
        out.println("  val hash = "+hashFun(argTypes,idx0loc))
        out.println("  def merge(e:"+clsName+") = if("+idx0loc.map(i=>"_"+i+"==e._"+i).mkString(" && ")+") { _"+n+" += e._"+n+"; true } else false");
        out.println("}")
      }
      storeSyms = global
    }
    super.emitDataStructures(out)
  }
  protected def getBlockContents(blk:Block[_]):String = {
    val save=stream; val wr=new java.io.StringWriter; stream=new java.io.PrintWriter(wr)
    emitBlock(blk); val res=ind(wr.toString); stream=save; res
  }

  private val nameAttr = "_name"
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case StUnsafeInsert(x,e,i) => emitValDef(sym, quote(x)+".unsafeInsert("+i+","+quote(e)+")")
    case M3Add(s,e) =>
      stream.println(quote(s)+".add("+quote(e)+")")
    case StForeach(x, blockSym, block) if (USE_STORE1 && isTemp(x.asInstanceOf[Sym[Store[Entry]]])) =>
      emitValDef(sym, quote(x)+".foreach{ ")
      stream.println(quote(blockSym) + " => ")
      emitBlock(block)
      stream.println("}")
    case _ => super.emitNode(sym,rhs)
  }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean) : String = {
    def printSym(s: Sym[Any]): String = {
      if(s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            case _ =>
              val strWriter: java.io.StringWriter = new java.io.StringWriter;
              val stream = new java.io.PrintWriter(strWriter);
              withStream(stream) { emitNode(s, d) }
              strWriter.toString
          }
          case None => if (s.attributes.contains(nameAttr)) s.attributes(nameAttr).toString else "x"+s.id
        }
      } else {
        if (s.attributes.contains(nameAttr)) s.attributes(nameAttr).toString else "x"+s.id
      }
    }
    x match {
      case Const(s: String) => "\""+s.replace("\"", "\\\"").replace("\n", "\\n")+"\"" // TODO: more escapes?
      case Const(c: Char) => "'"+c+"'"
      case Const(f: Float) => "%1.10f".format(f) + "f"
      case Const(l: Long) => l.toString + "L"
      case Const(null) => "null"
      case Const(z) => z.toString
      case s@Sym(n) => if (forcePrintSymbol) {
        printSym(s)
      } else {
        isVoidType(s.tp) match {
          case true => "(" + /*"x" + n +*/ ")"
          case false => printSym(s)
        }
      }
      case _ => throw new RuntimeException("could not quote %s".format(x))
    }
  }

  override def emitValDef(sym: Sym[Any], rhs: String): Unit = {
    val extra = if ((Config.sourceinfo < 2) || sym.pos.isEmpty) "" else {
      val context = sym.pos(0)
      "      // " + relativePath(context.fileName) + ":" + context.line
    }
    sym match {
      case s@Sym(n) => isVoidType(s.tp) match {
        case true => stream.println("" + rhs + extra)
        case false => if(s.possibleToInline || s.noReference) stream.print("("+rhs+")")
                      else stream.println("val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
      }
      case _ => stream.println("val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
    }
  }

  def getSymTypeStr(s:Sym[_]):String = {
    if(remap(s.tp).startsWith("ddbt.lib.store.Store[")) ":Store["+storeEntryType(s)+"]" else ""
  }
}
