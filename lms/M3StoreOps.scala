package ddbt.codegen.lms

import ddbt.ast._
import oltp.opt.lifters._
import ddbt.lib.store._
import ddbt.lib.ManifestHelper._
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

  def named(name: String, tp: Type, mutable: Boolean = false): Rep[_]  
  
  def named[T](name: String, mutable: Boolean = false)(implicit mT: Manifest[T]): Rep[T]
  
  def namedVar(name: String, tp: Type): Rep[_]
              
  // M3-specific operations
  def m3temp[E <: Entry]()(implicit tp: Manifest[E]): Rep[Store[E]]

  def m3add[E <: Entry](map: Rep[Store[E]], ent: Rep[E])(implicit m: Manifest[E]): Rep[Unit]
  
  def m3set[E <: Entry](map: Rep[Store[E]], ent: Rep[E])(implicit m: Manifest[E]): Rep[Unit]

  // Map annotations
  def setStoreType(s: Sym[_], storeType: StoreType)
}

trait M3StoreOpsExp extends BaseExp 
                       with EffectExp 
                       with M3StoreOps 
                       with StoreExpOpt
                       with EqualExp 
                       with IfThenElseExp {

  val USE_STORE1 = true // whether we specialize temporary maps in Store1
  val USE_UNIQUE_INDEX_WHEN_POSSIBLE = true
  val STORE_TYPE = "M3StoreOpsExp.STORE_TYPE"
  val NAME_ATTRIBUTE = "_name"
  val STORE_WATCHED = "StoreOps.watched"

  def named(name: String, tp: Type, mutable: Boolean = false) = 
    named(name, mutable)(man(tp))

  def named[T](name: String, mutable: Boolean = false)(implicit mT: Manifest[T]) = { 
    val n = Named(name)(mT)
    if (mutable) reflectMutable(n) else n 
  }

  override def namedVar(name: String, tp: Type): Rep[_] = {
    val init = tp match {
      case TypeLong   => unit(0L)
      case TypeDouble => unit(0.0)
      case TypeString => unit("")
      case _ => sys.error("Unsupported type " + tp) 
    }
    val rep = reflectMutable(NewVar(init))
    rep.asInstanceOf[Sym[_]].attributes.update(NAME_ATTRIBUTE, name)
    rep
  }

  def m3temp[E <: Entry]()(implicit tp: Manifest[E]): Rep[Store[E]] = {
    val sym = newStore[E]
    sym.asInstanceOf[Sym[_]].attributes.put("_isTemp", true)
    if (!USE_STORE1) setStoreType(sym.asInstanceOf[Sym[_]], IndexedStore)
    sym
  }

  def isTemp(s: Sym[_]) = 
    s.attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)

  def getStoreType(s: Sym[_]) = 
    s.attributes.get(STORE_TYPE).asInstanceOf[Option[StoreType]].getOrElse(null)

  def setStoreType(s: Sym[_], storeType: StoreType) = {
    s.attributes.put(STORE_TYPE, storeType)
  }

  def m3add[E <: Entry](map: Rep[Store[E]], ent: Rep[E])(implicit m: Manifest[E]) = {
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last
    val entVal = ent.get(n)
    
    getStoreType(map.asInstanceOf[Sym[_]]) match {
      case LogStore | PartitionStore(_) =>
        __ifThenElse(
          __equal(entVal, unit(ddbt.lib.ManifestHelper.zero(lastMan))), 
          unit(()),
          stInsert(map, ent)
        )    
      case _ =>
        val tupVal = (IHash, (1 until manifest[E].typeArguments.size).toList, USE_UNIQUE_INDEX_WHEN_POSSIBLE, -1)
        var idx = -1
        addIndicesToEntryClass[E](map, (xx, m) => { 
          idx = m.indexOf(tupVal)
          if (idx < 0) { m += tupVal; idx = m.size - 1 }
        })

        if (isTemp(map.asInstanceOf[Sym[_]])) {
          // we don't remove 0-elements
          if (USE_STORE1) {
            //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
            //addIndicesToEntryClass[E](map, (xx, m) => { val idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
            __ifThenElse(
              __equal(entVal, unit(zero(lastMan))), 
              unit(()),
              reflectWrite(map)(M3Add(map, ent))
            )
          } 
          else {
            __ifThenElse(
              __equal(entVal, unit(zero(lastMan))), 
              unit(()), 
              { val currentEnt = stGet(map, -1, ent) 
                //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
                __ifThenElse(
                  __equal(currentEnt, unit(null)), 
                  stUnsafeInsert(map, ent, idx),
                  currentEnt += (n, entVal)
                )
              }
            )
          }
        } 
        else {
          // we remove 0-elements
          __ifThenElse(
            __equal(entVal, unit(zero(lastMan))), 
            unit(()), 
            { val currentEnt = stGet(map, -1, ent) 
              //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
              __ifThenElse(
                __equal(currentEnt, unit(null)),
                stUnsafeInsert(map, ent, idx), 
                {
                  val watched = map.asInstanceOf[Sym[_]].attributes.get(STORE_WATCHED).asInstanceOf[Option[Boolean]].getOrElse(false)
                  if (watched) {
                    val oldEnt = steCopy(currentEnt)
                    currentEnt += (n, entVal)
                    steLogUpdate(map, oldEnt, currentEnt)
                  } else {
                    currentEnt += (n, entVal)
                  }
                  val currentEntVal = currentEnt.get(n)
                  __ifThenElse(
                    __equal(currentEntVal, unit(zero(lastMan))),
                    map.delete(currentEnt),
                    unit(())
                  )
                }
              )
            }
          )
        }
    }
  }

  def m3set[E <: Entry](map: Rep[Store[E]], ent: Rep[E]) (implicit m: Manifest[E]) = {    
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last
    val currentEnt = stGet(map, -1, ent) 
    //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
    val entVal = ent.get(n)

    val tupVal = (IHash, (1 until manifest[E].typeArguments.size).toList, USE_UNIQUE_INDEX_WHEN_POSSIBLE, -1)
    var idx = -1
    addIndicesToEntryClass[E](map, (xx, m) => { 
      idx = m.indexOf(tupVal)
      if (idx < 0) { 
        m += tupVal
        idx = m.size - 1 
      } 
    })

    if (isTemp(map.asInstanceOf[Sym[_]])) { // this never happens in practice
      __ifThenElse(
        __equal(currentEnt, unit(null)),
        stUnsafeInsert(map, ent, idx), 
        currentEnt.update(n, entVal)
      ) // same
    } 
    else {
      __ifThenElse(
        __equal(entVal, unit(zero(lastMan))),
        { __ifThenElse(
            __equal(currentEnt, unit(null)),
            unit(()),
            map.delete(currentEnt)
          )
        },
        { __ifThenElse(
            __equal(currentEnt, unit(null)),
            stUnsafeInsert(map, ent, idx), 
            currentEnt.update(n, entVal)
          ) // same
        }
      )
    }
  }

  override def stGet[E <: Entry: Manifest]
    (x: Exp[Store[E]], idx_in: Int, key: Exp[E]): Exp[E] = {
    var idx = idx_in
    key match {
      case Def(Reflect(SteSampleSEntry(_, args), _, _)) => addIndicesToEntryClass[E](x, (xx, m) => {
        val tupVal = (
          IHash,
          args.map(_._1),
          USE_UNIQUE_INDEX_WHEN_POSSIBLE,
          -1
        ) 
        //if(isTemp) ((IHash,args.map(_._1),false,-1)) else ((IHash,args.map(_._1),true,-1))
        idx = m.indexOf(tupVal)
        if(idx < 0) {
          m += tupVal
          idx = m.size - 1
        }
      })
      case _ =>
        val tupVal = (
          IHash,
          (1 until manifest[E].typeArguments.size).toList,
          USE_UNIQUE_INDEX_WHEN_POSSIBLE,
          -1
        )
        addIndicesToEntryClass[E](x, (xx, m) => {
          idx = m.indexOf(tupVal)
          if (idx < 0) { 
            m += tupVal
            idx = m.size - 1 
          }
        })
        //throw new GenerationFailedException("You should provide a sample entry to this method: Store.get")
    }
    val elem: Exp[E] = StGet[E](x, idx, key)
    steMakeMutable(elem)
  }

  case class Named[T](n: String)(implicit mT: Manifest[T]) extends Def[T]
  case class M3Add[E <: Entry: Manifest](s: Exp[Store[E]], e: Exp[E]) 
    extends Def[Unit]

  def stUnsafeInsert[E<:Entry:Manifest](x: Exp[Store[E]], e: Exp[E], idx:Int):Exp[Unit] = reflectWrite(x)(StUnsafeInsert[E](x, e, idx))
  case class StUnsafeInsert[E<:Entry:Manifest](s: Exp[Store[E]], e:Exp[E],idx:Int) extends Def[Unit]
}

trait ScalaGenM3StoreOps extends ScalaGenBase 
                            with ScalaGenEffect 
                            with ScalaGenStore {

  val IR: M3StoreOpsExp with ExtendedExpressions with Effects
  import IR._
  import ddbt.Utils.{ind,tup}

  // Specialization of temporary maps into Entry1 / Store1
  override def generateStore(s: Sym[_]): String =
    if (USE_STORE1 && isTemp(s)) 
      "val " + quote(s, true) + " = new Store1[" + storeEntryType(s) + "]()\n"
    else super.generateStore(s)

  override def emitDataStructures(out: java.io.PrintWriter): Unit = {
    if (USE_STORE1) {
      val (temp, global) = storeSyms.partition(isTemp)
      out.println
      temp.foreach { sym =>
        val indices = 
          sym.attributes.get(ENTRY_INDICES_KEY)
            .asInstanceOf[Option[collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)]]]
            .getOrElse(new collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)])
        val idx0loc = indices(0)._2
        val (clsName, argTypes) = extractEntryClassName(sym)
        val n = argTypes.size
        out.println(
          "case class " + clsName + "(" + 
          argTypes.zipWithIndex.map { case (tp, i) => 
            "var _" + (i + 1) + ":" + tp + " = " + zeroValue(tp) 
          }.mkString(", ") + ") extends Entry1[" + clsName + "] {")
        out.println("  val hash = " + hashFun(argTypes, idx0loc))
        out.println(
          "  def merge(e: " + clsName + ") = if (" + 
            idx0loc.map(i => "_" + i + " == e._" + i).mkString(" && ") + 
            ") { _" + n + " += e._" + n + "; true } else false")
        out.println("}")
      }
      storeSyms = global
    }
    super.emitDataStructures(out)
  }

  protected def getBlockContents(blk: Block[_]): String = {
    val save = stream
    val wr = new java.io.StringWriter
    stream = new java.io.PrintWriter(wr)
    emitBlock(blk)
    val res = ind(wr.toString)
    stream = save
    res
  }

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(NAME_ATTRIBUTE, n)
    case StUnsafeInsert(x, e, i) =>
      emitValDef(sym, quote(x) + ".unsafeInsert(" + i + "," + quote(e) + ")")
    case M3Add(s, e) =>
      stream.println(quote(s) + ".add(" + quote(e) + ")")
    case StForeach(x, blockSym, block) 
      if (USE_STORE1 && isTemp(x.asInstanceOf[Sym[Store[Entry]]])) =>
        emitValDef(sym, quote(x) + ".foreach { ")
        stream.println(quote(blockSym) + " => ")
        emitBlock(block)
        stream.println("}")
    case _ => super.emitNode(sym, rhs)
  }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean): String = {
    def printSym(s: Sym[Any]): String = {
      if (s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            case _ =>
              val strWriter = new java.io.StringWriter
              val stream = new java.io.PrintWriter(strWriter)
              withStream(stream) { emitNode(s, d) }
              strWriter.toString
          }
          case None => 
            if (s.attributes.contains(NAME_ATTRIBUTE)) s.attributes(NAME_ATTRIBUTE).toString 
            else "x" + s.id
        }
      } else {
        if (s.attributes.contains(NAME_ATTRIBUTE)) s.attributes(NAME_ATTRIBUTE).toString 
        else "x" + s.id
      }
    }
    x match {
      case Const(s: String) => // TODO: more escapes?
        "\"" + s.replace("\"", "\\\"").replace("\n", "\\n") + "\""         
      case Const(c: Char) => "'" + c + "'"
      case Const(f: Float) => "%1.10f".format(f) + "f"
      case Const(l: Long) => l.toString + "L"
      case Const(null) => "null"
      case Const(z) => z.toString
      case s @ Sym(n) => 
        if (forcePrintSymbol) {
          if (s.attributes.contains(NAME_ATTRIBUTE)) s.attributes(NAME_ATTRIBUTE).toString 
          else "x" + s.id
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
    val extra = 
      if ((Config.sourceinfo < 2) || sym.pos.isEmpty) "" 
      else {
        val context = sym.pos(0)
        "      // " + relativePath(context.fileName) + ":" + context.line
      }
    sym match {
      case s @ Sym(n) => isVoidType(s.tp) match {
        case true => stream.println("" + rhs + extra)
        case false => 
          if (s.possibleToInline || s.noReference) stream.print("(" + rhs + ")")
          else stream.println(
            "val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
      }
      case _ => stream.println(
        "val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
    }
  }

  def getSymTypeStr(s: Sym[_]): String = {
    if (remap(s.tp).startsWith("ddbt.lib.store.Store[")) 
      ":Store[" + storeEntryType(s) + "]" 
    else ""
  }
}


trait SparkGenM3StoreOps extends ScalaGenM3StoreOps 
                            with SparkGenStore {

  val IR: M3StoreOpsExp with ExtendedExpressions with Effects
  import IR._
  import ddbt.Utils.{ind, tup, block}

  private def extractIndices(sym: Sym[_]) = 
    sym.attributes.get(ENTRY_INDICES_KEY) match {
      case Some(m) => 
        m.asInstanceOf[collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)]]
      case None => 
        val m = new collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)]
        m += ((IList, (1 to sym.tp.typeArguments.size), false, -1))
    }

  private def indicesToString(entryType: String,
      indices: Seq[(IndexType, Seq[Int], Boolean, Int)]): Seq[String] =
    indices.zipWithIndex.map { 
      case ((idxType, idxLoc, idxUniq, idxSliceIdx), i) => idxType match {
        case IHash => 
          "new HashIndex[%s](%d, %s) with %s_Idx%d".format(
            entryType, i, idxUniq, entryType, i)
        case IList => "new ListIndex[%s](%d, %s) with %s_Idx%d".format(
            entryType, i, idxUniq, entryType, i)
        case _ => sys.error("Index type " + idxType + " not supported")
      }
    }

  override def emitDataStructures(out: java.io.PrintWriter): Unit = {   
    if (USE_STORE1) {
      val (temp, global) = storeSyms.partition(isTemp)
      out.println
      temp.foreach { sym =>
        val indices = 
          sym.attributes.get(ENTRY_INDICES_KEY)
             .asInstanceOf[Option[collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)]]]
             .getOrElse(new collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)])
        val idx0loc = indices(0)._2
        val (clsName, argTypes) = extractEntryClassName(sym)
        val strArgs = argTypes.zipWithIndex.map { case (tp, i) => 
            "var _" + (i + 1) + ":" + tp + " = " + zeroValue(tp) 
          }.mkString(", ")
        val cond = idx0loc.map(i => s"_$i == e._$i").mkString(" && ")
        val n = argTypes.size
        out.println(
          s"""|case class $clsName($strArgs) extends Entry1[$clsName] {
              |  val hash = ${hashFun(argTypes, idx0loc)}
              |  def merge(e: $clsName) = 
              |    if ($cond) { _$n += e._$n; true } else false
              |}""".stripMargin)
      }
      storeSyms = global
    }
    storeSyms.foreach { sym =>
      val (entryClsName, entryArgTypes) = extractEntryClassName(sym)     
      val entryClsParams = entryArgTypes.zipWithIndex.map { case (argTp, i) => 
        s"var _${i + 1}: ${argTp} = ${zeroValue(argTp)}"
      }.mkString(", ")           
      out.println(
        s"case class $entryClsName($entryClsParams) extends MapEntry(${entryArgTypes.size})")
      getStoreType(sym) match {
        case IndexedStore => 
          extractIndices(sym).zipWithIndex.foreach { 
            case ((idxType, idxLoc, idxUniq, idxSliceIdx), i) =>
            val hashBody = idxType match {
              case IHash | IList => hashFun(entryArgTypes, idxLoc, "e")
              case _ => sys.error("index_hash not supported")
            }
            val cmpBody = idxType match {
              case IHash | IList =>            
                val cond = idxLoc.map(i => s"e1._$i == e2._$i").mkString(" && ") 
                s"{ if ($cond) 0 else 1 }"
              case _ => sys.error("index_cmp not supported")
            }
            out.println(
              s"""|trait ${entryClsName}_Idx$i extends IndexOperations[$entryClsName] {
                  |  def hash(e: $entryClsName) = $hashBody
                  |  def cmp(e1: $entryClsName, e2: $entryClsName) = $cmpBody
                  |}""".stripMargin)
          }
        case LogStore | PartitionStore(_) => 
          val argTypes = sym.tp.typeArguments(0).typeArguments
          val colStoreName = logStoreName(sym)
          val attributes = argTypes.zipWithIndex.map { case (argTp, i) =>
            s"val _${i + 1} = buffers($i)${emitCastBuffer(argTp)}"
          }.mkString("\n") 
          val appendBody = (1 to argTypes.length).map(i => s"_$i += e._$i").mkString("; ")
          val setEntry = (1 to argTypes.length).map(i => s"entry._$i = _$i(i)").mkString("; ")
          val bufferList = argTypes.map(tp => s"${emitCreateBuffer(tp)}").mkString(", ") 
          out.println(
            s"""|class $colStoreName(buffers: Array[Buffer]) extends ColumnarStore(buffers) with WriteStore[$entryClsName] {
                |  def this() = this(Array[Buffer]($bufferList))
                |${ind(attributes)} 
                |  val entry = $entryClsName()
                |  def +=(e: $entryClsName) = { $appendBody }
                |  def foreach(f: $entryClsName => Unit) = {
                |    var i = 0
                |    while (i < size) {
                |      ${setEntry}
                |      f(entry)
                |      i += 1 
                |    }
                |  }
                |}""".stripMargin)
          getStoreType(sym) match { 
            case PartitionStore(pkeys) => 
              val containerName = partitionStoreName(sym)
              if (pkeys.length == 0) 
                out.println(
                  s"""|class $containerName(numPartitions: Int) 
                      |  extends PartitionContainer[$entryClsName](
                      |    Array.fill[$colStoreName](numPartitions)(new $colStoreName()))""".stripMargin)
              else if (pkeys.length == 1) {
                if (pkeys(0) >= argTypes.length) sys.error("Invalid partition column index.")
                else 
                  out.println(
                    s"""|class $containerName(numPartitions: Int) 
                        |  extends PartitionContainer[$entryClsName](
                        |    Array.fill[$colStoreName](numPartitions)(new $colStoreName())) {
                        |  override def +=(e: $entryClsName) = {
                        |    val partitionId = (e._${pkeys(0) + 1}.hashCode) % numPartitions
                        |    partitions(partitionId) += e
                        |  }
                        |}""".stripMargin)
              } else sys.error("Multiple-column partitioning is not supported yet.")
            case _ =>  
          }
      }
      out.println
    }
  }

  override def generateStore(s: Sym[_]): String = {
    val cName = quote(s, true)
    if (USE_STORE1 && isTemp(s)) {
      val entryType = storeEntryType(s)
      s"val $cName = new Store1[$entryType]()\n"
    } 
    else {
      val sym = getStoreSym(s).asInstanceOf[Sym[Store[Entry]]]
      getStoreType(sym) match {
        case IndexedStore => 
          val entryType = storeEntryType(s)
          val indices = extractIndices(s)
          val strIndices = indicesToString(entryType, indices).mkString(",\n")
          s"val $cName = new Store[$entryType](Vector(${block(ind(strIndices))}))"
        case LogStore => 
          s"val $cName = new ${logStoreName(sym)}()"  
        case PartitionStore(_) => 
          s"val $cName = new ${partitionStoreName(sym)}(numPartitions)"
        case _ => sys.error(s"Store type is not specified for $cName.")
      }
    }
  }

  def emitCreateBuffer(manifest: Manifest[_]): String = manifest.toString match {
    case "Long"   | "long"   => "new IntBuffer(16)"
    case "Double" | "double" => "new DoubleBuffer(16)"
    case "java.lang.String" | "char*" => "new CharArrayBuffer(16, 30)" 
    case _ => sys.error("Unsupported buffer type")
  }

  def emitCastBuffer(manifest: Manifest[_]): String = manifest.toString match {
    case "Long"   | "long"   => ".asInstanceOf[IntBuffer]"
    case "Double" | "double" => ".asInstanceOf[DoubleBuffer]"
    case "java.lang.String" | "char*" => ".asInstanceOf[CharArrayBuffer]" 
    case _ => sys.error("Unsupported buffer type")
  }

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case StInsert(x, e) => getStoreType(x.asInstanceOf[Sym[_]]) match {
      case LogStore | PartitionStore(_) => 
        emitValDef(sym, quote(x) + " += (" + quote(e) + ")")
      case _ => super.emitNode(sym, rhs)
    }
    case StForeach(x, blockSym, block) => getStoreType(x.asInstanceOf[Sym[_]]) match {
      case LogStore | PartitionStore(_) => 
        emitValDef(sym, quote(x) + ".foreach {")
        stream.println(quote(blockSym) + " => ")
        emitBlock(block)
        stream.println("}")    
      case _ => super.emitNode(sym, rhs)
    }
    case _ => super.emitNode(sym, rhs) 
  }

  protected def indexedStoreName(sym: Sym[_]): String = {
    val storeSym = sym.asInstanceOf[Sym[Store[Entry]]]
    val entryClsName = extractEntryClassName(storeSym)._1
    s"Store[$entryClsName]"
  }

  protected def logStoreName(sym: Sym[_]): String = {
    val storeSym = sym.asInstanceOf[Sym[Store[Entry]]]
    val argTypes = storeSym.tp.typeArguments(0).typeArguments
    val argSuffix = argTypes.map(tp => simplifyTypeName(remap(tp))).mkString
    s"ColumnarStore_x${sym.id}_$argSuffix"
  }

  protected def partitionStoreName(sym: Sym[_]): String = {
    val storeSym = sym.asInstanceOf[Sym[Store[Entry]]]
    val argTypes = storeSym.tp.typeArguments(0).typeArguments
    val argSuffix = argTypes.map(tp => simplifyTypeName(remap(tp))).mkString
    s"PartitionContainer_x${sym.id}_$argSuffix"
  }

  override def storeType(sym: Exp[_]): String = {
    val storeSym = getStoreSym(sym)
    getStoreType(storeSym) match {
      case IndexedStore => indexedStoreName(storeSym)
      case LogStore => logStoreName(storeSym)
      case PartitionStore(_) => partitionStoreName(storeSym)
    }
  }  
}

trait CGenM3StoreOps extends CGenBase 
                        with CGenEffect 
                        with CGenStore {

  val IR: M3StoreOpsExp with ExtendedExpressions with Effects
  import IR._
  import ddbt.Utils.{ind,tup}

  // Specialization of temporary maps into Entry1 / Store1
  override def generateStore(s: Sym[_]): String =
    if (USE_STORE1 && isTemp(s)) 
      "val " + quote(s, true) + " = new Store1[" + storeEntryType(s) + "]()\n"
    else super.generateStore(s)

  override def emitDataStructures(out: java.io.PrintWriter): Unit = {
    if (USE_STORE1) {
      val (temp, global) = storeSyms.partition(isTemp)
      out.println
      temp.foreach { sym =>
        val indices = 
          sym.attributes.get(ENTRY_INDICES_KEY)
            .asInstanceOf[Option[collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)]]]
            .getOrElse(new collection.mutable.ArrayBuffer[(IndexType, Seq[Int], Boolean, Int)])
        val idx0loc = indices(0)._2
        val (clsName, argTypes) = extractEntryClassName(sym)
        val n = argTypes.size
        out.println(
          "case class " + clsName + "(" + 
          argTypes.zipWithIndex.map { case (tp, i) => 
            "var _" + (i + 1) + ":" + tp + " = " + zeroValue(tp) 
          }.mkString(", ") + ") extends Entry1[" + clsName + "] {")
        out.println("  val hash = " + hashFun(argTypes,idx0loc))
        out.println(
          "  def merge(e:" + clsName + ") = if(" + 
            idx0loc.map(i => "_" + i + " == e._" + i).mkString(" && ") + 
            ") { _" + n + " += e._" + n + "; true } else false")
        out.println("}")
      }
      storeSyms = global
    }
    super.emitDataStructures(out)
  }

  protected def getBlockContents(blk: Block[_]): String = {
    val save = stream
    val wr = new java.io.StringWriter
    stream = new java.io.PrintWriter(wr)
    emitBlock(blk)
    val res = ind(wr.toString)
    stream = save
    res
  }

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(NAME_ATTRIBUTE, n)
    case StUnsafeInsert(x, e, i) => 
      emitValDef(sym, quote(x) + ".unsafeInsert(" + i + "," + quote(e) + ")")
    case M3Add(s, e) =>
      stream.println(quote(s) + ".add(" + quote(e) + ")")
    case StForeach(x, blockSym, block) 
        if (USE_STORE1 && isTemp(x.asInstanceOf[Sym[Store[Entry]]])) =>
      emitValDef(sym, quote(x) + ".foreach{ ")
      stream.println(quote(blockSym) + " => ")
      emitBlock(block)
      stream.println("}")
    case _ => super.emitNode(sym, rhs)
  }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean): String = {
    //System.out.println("quote(" + x + ", "+forcePrintSymbol+") => " + Def.unapply(x))
    def printSym(s: Sym[Any]): String = {
      //System.out.println("printSym(" + s + ") => " + Def.unapply(s))
      if(s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            case _ =>
              val strWriter = new java.io.StringWriter
              val stream = new java.io.PrintWriter(strWriter)
              withStream(stream) { emitNode(s, d) }
              strWriter.toString
          }
          case None => 
            if (s.attributes.contains(NAME_ATTRIBUTE)) s.attributes(NAME_ATTRIBUTE).toString 
            else "x" + s.id
        }
      } else {
        if (s.attributes.contains(NAME_ATTRIBUTE)) s.attributes(NAME_ATTRIBUTE).toString 
        else "x" + s.id
      }
    }
    x match {
      case Const(s: String) => // TODO: more escapes?
        "\"" + s.replace("\"", "\\\"").replace("\n", "\\n") + "\"" 
      case Const(c: Char) => "'" + c + "'"
      case Const(f: Float) => "%1.10f".format(f) + "f"
      case Const(l: Long) => l.toString + "L"
      case Const(null) => "null"
      case Const(z) => z.toString
      case s @ Sym(n) => 
        if (forcePrintSymbol) {
          if (s.attributes.contains(NAME_ATTRIBUTE)) s.attributes(NAME_ATTRIBUTE).toString 
          else "x" + s.id
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
    val extra = 
      if ((Config.sourceinfo < 2) || sym.pos.isEmpty) "" 
      else {
        val context = sym.pos(0)
        "      // " + relativePath(context.fileName) + ":" + context.line
      }
    sym match {
      case s @ Sym(n) => isVoidType(s.tp) match {
        case true => stream.println("" + rhs + extra)
        case false => 
          if (s.possibleToInline || s.noReference) stream.print("(" + rhs + ")")
          else stream.println(
            "val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
      }
      case _ => stream.println(
        "val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
    }
  }

  def getSymTypeStr(s:Sym[_]):String = {
    if (remap(s.tp).startsWith("ddbt.lib.store.Store[")) 
      ":Store[" + storeEntryType(s) + "]" 
    else ""
  }
}
