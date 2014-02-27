package ddbt.codegen.lms
import ddbt.ast._
import oltp.opt.lifters._
import ddbt.lib.store._
import ManifestHelper._

// Legacy classes are now renamed:
//class M3Temp[K,V] {} // -> M3Map[K,V]
//class M3Var[T] {} // -> Var[T]

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
  // class M3StoreOpsCls[E<:Entry:Manifest](x: Rep[E]) {
  //   def get(key:K):V;           // returns the value or zero if it is not present
  //   def set(key:K, value:V);    // inserts or set the value
  //   def add(key:K, value:V);    // combines new value with existing one using 'plus'
  //   def foreach(f:(K,V)=>Unit); // iterates through all non-zero values of the map
  //   def slice[T](index:Int,subKey:T):M3Map[K,V]; // partition where the secondary index is equal to subKey
  //   def sum(acc:M3Map[K,V]);    // accumulate in acc: acc <- element_wise_sum(this,acc)
  //   def clear();                // erases all elements of the map or slice
  //   def size:Int;               // number of key-value mappings in the map
  //   def toMap:Map[K,V];         // convert to a Scala map
  // }
  // Nodes creation

  // def newM3Store(key_tp:List[Type],value_tp:Type):Rep[Store[_]] = newM3Store()(manEntry(key_tp, value_tp).asInstanceOf[Manifest[Entry]])
  // def newM3Store[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]]
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]
  // def namedM3Var[T](name: String,tp:Type)(implicit mT:Manifest[T]): Rep[M3Var[T]]
  // def namedM3Map[K,V](name: String,key:List[Type],value:Type,indexList: List[List[Int]])(implicit mK:Manifest[K], mV:Manifest[V]): Rep[M3Temp[K,V]]
  // def m3var(value:Type) : Rep[M3Var[_]]

  //def m3temp[E<:Entry](key_tp:List[Type],value_tp:Type):Rep[Store[E]] = m3temp()(manEntry(key_tp, value_tp).asInstanceOf[Manifest[E]])
  def m3temp[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]]
  // Operations on M3Map, M3Var and M3Temp
  // def m3get[E<:SEntry:Manifest](map:Rep[Store[E]], key:Rep[E]):Rep[E]
  // def m3set[E<:SEntry:Manifest](map:Rep[Store[E]], ent:Rep[E]):Rep[Unit]
  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]):Rep[Unit]
  // def m3foreach[E<:SEntry:Manifest](map:Rep[Store[E]], body: Rep[E] => Rep[Unit]):Rep[Unit]
  // def m3slice[E<:SEntry:Manifest](map:Rep[Store[E]],part:Int,partKey:Rep[E],body: Rep[E] => Rep[Unit]):Rep[Unit]
  // def m3clear[E<:SEntry:Manifest](map:Rep[Store[E]]):Rep[Unit]
}

trait M3StoreOpsExp extends BaseExp with EffectExp with M3StoreOps with StoreExp with EqualExp with IfThenElseExp {
  import ManifestHelper.man

//  case class M3Entry[E<:Entry](vs:List[Rep[_]], m:Manifest[E]) extends Exp[E]

//  def newEntry[E<:Entry](vs:List[Rep[_]], m:Manifest[E]):Rep[E] = M3Entry(vs,m)
  // def newM3Store[E<:Entry](implicit tp:Manifest[E]):Rep[Store[E]] = {
  //   newStore[E]
  // }
  def named(name:String,tp:Type,mutable:Boolean=false) = named(name,mutable)(man(tp))
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]) = { val n=Named(name)(mT); if (mutable) reflectMutable(n) else n }
  // def namedM3Var[T](name: String,tp:Type)(implicit mT:Manifest[T]) = reflectMutable(NamedM3Var(name,tp)(mT))
  // def namedM3Map[K, V](name: String,key:List[Type],value:Type,indexList: List[List[Int]])(implicit mK:Manifest[K], mV:Manifest[V]) = reflectMutable(NamedM3Map(name,key,value,indexList,mK,mV))
  def m3temp[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]] = {
    val sym = newStore[E]
    sym.asInstanceOf[Sym[_]].attributes.put("_isTemp",true)
    sym
  }
  // def m3get(map:Exp[_], key:List[Exp[_]],value_tp:Type) = M3Get(map,key,man(value_tp))
  // def m3set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(M3Set(map,key,value))
  // def m3add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(M3Add(map,key,value))
  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]) = {
    val isTemp = map.asInstanceOf[Sym[_]].attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last
    if(isTemp) {
      // we don't remove 0-elements
      val currentEnt = map.get((1 until n).map(i => (i, ent.get(i))) : _*)
      __ifThenElse(__equal(currentEnt,unit(null)),map.insert(ent),currentEnt += (n, ent.get(n)))
    } else {
      // we remove 0-elements
      val entVal = ent.get(n)
      __ifThenElse(__equal(entVal,unit(zero(lastMan))), unit(()), {
        ///////
        val currentEnt = map.get((1 until n).map(i => (i, ent.get(i))) : _*)
        __ifThenElse(__equal(currentEnt,unit(null)),map.insert(ent),{
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
    val isTemp = map.asInstanceOf[Sym[_]].attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last
    val currentEnt = map.get((1 until n).map(i => (i, ent.get(i))) : _*)
    val entVal = ent.get(n)
    if(isTemp) {
      __ifThenElse(__equal(currentEnt,unit(null)),map.insert(ent),currentEnt.update(n, entVal)) // same
    } else {
      __ifThenElse(__equal(entVal,unit(zero(lastMan))),{
        __ifThenElse(__equal(currentEnt,unit(null)),unit(()),map.delete(currentEnt))
      },{
        __ifThenElse(__equal(currentEnt,unit(null)),map.insert(ent),currentEnt.update(n, entVal)) // same
      })
    }
    /*
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last
    val entVal = ent.get(n)
    __ifThenElse(__equal(entVal,unit(zero(lastMan))), unit(()), {
      val currentEnt = map.get((1 until n).map(i => (i, ent.get(i))) : _*)
      __ifThenElse(__equal(currentEnt,unit(null)),map.insert(ent),{
        val entVal = ent.get(n)
        currentEnt.update(n, entVal)
      })
    })
    */
  }

  override def stGet        [E<:Entry:Manifest](x: Exp[Store[E]], idx_in:Int,key:Exp[E]):Exp[E] = {
    var idx = idx_in
    key match {
      case Def(Reflect(SteSampleSEntry(_, args),_,_)) => addIndicesToEntryClass[E](x, (xx, m) => {
        // val xSym = getStoreSym(x).asInstanceOf[Sym[Store[E]]]
        // val isTemp = xSym.attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)
        val tupVal = ((IHash,args.map(_._1),false,-1)) //if(isTemp) ((IHash,args.map(_._1),false,-1)) else ((IHash,args.map(_._1),true,-1))
        idx = m.indexOf(tupVal)
        if(idx < 0) {
          m += tupVal
          idx = m.size - 1
        }
      })
      case _ => throw new GenerationFailedException("You should provide a sample entry to this method: Store.get")
    }
    val elem:Exp[E]=StGet[E](x,idx,key)
    steMakeMutable(elem)
  }
  // def m3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body: => Exp[Unit]) = m3foreach(map,key,value,reifyEffects(body))
  // def m3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body:Block[Unit]) = reflectEffect(M3Foreach(map,key,value,body),summarizeEffects(body).star)
  // def m3slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) = M3Slice(map,part,partKey)
  // def m3clear(map:Exp[_]) = reflectWrite(map)(M3Clear(map))

  case class Named[T](n:String)(implicit mT:Manifest[T]) extends Def[T]
  // case class NamedM3Var[T](n:String,tp:Type)(implicit mT:Manifest[T]) extends Def[M3Var[T]]
  // case class NamedM3Map[K,V](n:String,key:List[Type],value:Type,indexList: List[List[Int]],mK:Manifest[K],mV:Manifest[V]) extends Def[M3Temp[K,V]]
  // case class NewM3Var[K,V](value:Type,mV:Manifest[V]) extends Def[M3Var[_]]
  // case class NewM3Temp[K,V](key:List[Type],value:Type,mK:Manifest[K],mV:Manifest[V]) extends Def[M3Temp[_,_]]

  // case class StNewStoreTemp[E<:Entry:Manifest](s:Rep[Store[E]])

  // case class M3Get[T](map:Exp[_], key:List[Exp[_]],mt:Manifest[T]) extends Def[T]
  // case class M3Set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  // case class M3Add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  // case class M3Foreach(map:Exp[_], key:Exp[_], value:Exp[_], body:Block[Unit]) extends Def[Unit]
  // case class M3Slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) extends Def[Exp[_]]
  // case class M3Clear(map:Exp[_]) extends Def[Unit]

  // override def syms(e: Any): List[Sym[Any]] = e match {
  //   case M3Foreach(m,k,v,b) => syms(k):::syms(v):::syms(b)
  //   case _ => super.syms(e)
  // }
  // override def boundSyms(e: Any): List[Sym[Any]] = e match {
  //   case M3Foreach(m,k,v,b) => effectSyms(k):::effectSyms(v):::effectSyms(b)
  //   case _ => super.boundSyms(e)
  // }
  // override def symsFreq(e: Any): List[(Sym[Any], Double)] = e match {
  //   case M3Foreach(m,k,v,b) => freqHot(k):::freqHot(v):::freqHot(b)
  //   case _ => super.symsFreq(e)
  // }
  // override def aliasSyms(e: Any): List[Sym[Any]] = e match {
  //   case M3Set(m,k,v) => Nil
  //   case M3Add(m,k,v) => Nil
  //   case _ => super.aliasSyms(e)
  // }
}

trait ScalaGenM3StoreOps extends ScalaGenBase with ScalaGenEffect with ScalaGenStore {
  val IR: M3StoreOpsExp with ExtendedExpressions with Effects
  import IR._
  import ddbt.Utils.{ind,tup}

  protected def getBlockContents(blk:Block[_]):String = {
    val save=stream; val wr=new java.io.StringWriter; stream=new java.io.PrintWriter(wr)
    emitBlock(blk); val res=ind(wr.toString); stream=save; res
  }

  // def isPossibleToInlineExpr(expr: Exp[_]) = expr match {
  //   case s@Sym(x) => s.possibleToInline
  //   case _ => true
  // }

  /**
   * If we are using an expression result inside an operation,
   * and this expression is possible to inline, and the result
   * should be used several times in this operation, we should
   * first creat a symbol for it
   */
  // def genValDefForNonInlinableExpr(exprList: List[Exp[_]], nodeName: String) = exprList.map{ expr => expr match {
  //     case s@Sym(x) => if(isPossibleToInlineExpr(expr)) {
  //       "val x"+x+"_"+nodeName+getSymTypeStr(s)+" = "+quote(expr)+"\n"
  //     } else {
  //       ""
  //     }
  //     case _ => ""
  //   }
  // }.mkString

  /**
   * Tightly related to genValDefForNonInlinableExpr
   * If we have created val-def for an inlinable expression,
   * we should take care of its symbol
   */
  // def genQuoteExpr(exprList: List[Exp[_]], nodeName: String) = exprList.map{ expr => expr match {
  //     case s@Sym(x) => if(isPossibleToInlineExpr(expr)) {
  //       "x"+x+"_"+nodeName
  //     } else {
  //       quote(expr)
  //     }
  //     case _ => quote(expr)
  //   }
  // }

  private val nameAttr = "_name"
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    //case M3Entry(vs,m) => emitValDef(sym, "new "+m.toString+"("+(vs map quote).mkString(",")+")")
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
  //   case NamedM3Var(n,_) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
  //   case NamedM3Map(n,_,_,_,_,_) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
  //   case NewM3Var(v,_) => stream.println(M3MapCommons.createM3VarDefinition(quote(sym), v))
  //   case NewM3Temp(ks,v,_,_) => if(M3MapCommons.isInliningHigherThanNone) {
  //     stream.println(M3MapCommons.createM3TempDefinition(quote(sym),v,ks))
  //   } else {
  //     emitValDef(sym, "M3Map.temp["+tup(ks map (_.toScala))+","+v.toScala+"]()")
  //   }
  //   case M3Get(m,ks,_) => if(M3MapCommons.isInliningHigherThanNone) {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(_,_),_,_)) | Some(Reflect(NamedM3Var(_,_),_,_)) => emitValDef(sym, quote(m))
  //       case Some(Reflect(NewM3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
  //         val map = quote(m)
  //         val nodeName = createNodeName(sym)
  //         genGetMap(nodeName, map, M3MapCommons.entryClassName(value, key),value.toScala+" = "+value.zero, (0 until ks.size).toList, ks)
  //       })
  //       case Some(Reflect(NamedM3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
  //         val map = quote(m)
  //         val nodeName = createNodeName(sym)
  //         genGetMap(nodeName, map, M3MapCommons.entryClassName(value, key, indexList),value.toScala+" = "+value.zero, (0 until ks.size).toList, ks)
  //       })
  //       case _ => emitValDef(sym, quote(m)+".getonly("+tup(ks map quote)+")")
  //     }
  //   } else {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(_,_),_,_)) | Some(Reflect(NamedM3Var(_,_),_,_)) => emitValDef(sym, quote(m))
  //       case _ => emitValDef(sym, quote(m)+".get("+tup(ks map quote)+")")
  //     }

  //   }
  //   case M3Set(m,ks,v) => if(M3MapCommons.isInliningHigherThanNone) {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(_,_),_,_)) | Some(Reflect(NamedM3Var(_,_),_,_)) => stream.println(quote(m)+" = "+quote(v))
  //       case Some(Reflect(NewM3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
  //         val map = quote(m)
  //         val nodeName = createNodeName(sym)
  //         genSetTempMap(nodeName, map, M3MapCommons.entryClassName(value, key, List[List[Int]]()), (0 until ks.size).toList, ks, v)
  //       })
  //       case Some(Reflect(NamedM3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
  //         val map = quote(m)
  //         val nodeName = createNodeName(sym)
  //         genSetNamedMap(nodeName, map, key, value, indexList, ks, v)
  //       })
  //       case _ => stream.println(quote(m)+".setonly("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
  //     }
  //   } else {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(_,_),_,_)) | Some(Reflect(NamedM3Var(_,_),_,_)) => stream.println(quote(m)+" = "+quote(v))
  //       case _ => stream.println(quote(m)+".set("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
  //     }
  //   }
  //   case M3Add(m,ks,v) => if(M3MapCommons.isInliningHigherThanNone) {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(_,_),_,_)) | Some(Reflect(NamedM3Var(_,_),_,_)) => stream.println(quote(m)+" += "+quote(v))
  //       case Some(Reflect(NewM3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
  //         val map = quote(m)
  //         val nodeName = createNodeName(sym)
  //         genAddTempMap(nodeName, map, value, M3MapCommons.entryClassName(value, key, List[List[Int]]()), (0 until ks.size).toList, ks, v)
  //       })
  //       case Some(Reflect(NamedM3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
  //         val map = quote(m)
  //         val nodeName = createNodeName(sym)
  //         genAddNamedMap(nodeName, map, key, value, indexList, ks, v)
  //       })
  //       case _ => stream.println(quote(m)+".addonly("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
  //     }
  //   } else {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(_,_),_,_)) | Some(Reflect(NamedM3Var(_,_),_,_)) => stream.println(quote(m)+" += "+quote(v))
  //       case _ => stream.println(quote(m)+".add("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
  //     }
  //   }
  //   case M3Foreach(m,k,v,body) => {
  //     val block=getBlockContents(body) // enables both the renaming trick and allow nested block indentation
  //     if(M3MapCommons.isInliningHigherThanNone) {
  //       Def.unapply(m) match {
  //         case Some(Reflect(NewM3Temp(key,value,_,_),_,_)) => stream.println({
  //           val map = quote(m)
  //           val nodeName = createNodeName(sym)

  //           genForeachMap(nodeName, map, quote(k), quote(v), block, key, value, M3MapCommons.entryClassName(value, key, List[List[Int]]()))
  //         })
  //         case Some(Reflect(NamedM3Map(_,key,value,indexList,_,_),_,_)) => stream.println({
  //           val map = quote(m)
  //           val nodeName = createNodeName(sym)

  //           genForeachMap(nodeName, map, quote(k), quote(v), block, key, value, M3MapCommons.entryClassName(value, key, indexList))
  //         })
  //         case Some(Reflect(M3Slice(name,part,partKey),_,_)) => stream.println({
  //           val nodeName = createNodeName(sym)
  //           val map = genQuoteExpr(List(m),nodeName).apply(0)

  //           val (entryClsName, elemValueType) = Def.unapply(name) match {
  //             case Some(Reflect(NamedM3Map(_,key,value,indexList,_,_),_,_)) => {
  //               (":"+M3MapCommons.entryClassName(value,key,indexList),":"+value.toScala)
  //             }
  //             case m => ("","")
  //           }

  //           //f= foreach
  //           val i = nodeName+"_fi"
  //           val len = nodeName+"_flen"
  //           val e = nodeName+"_fe"
  //           val sliceValDef = ind(genValDefForNonInlinableExpr(List(m),nodeName))
  //           "; {\n" +
  //           (if(sliceValDef.length > 2) sliceValDef+"\n" else "") +
  //           "  //SLICEM3FOREACH\n" +
  //           "  var "+i+":Int = 0\n" +
  //           "  val "+len+":Int = "+map+".length\n" +
  //           "  while("+i+" < "+len+") {\n" +
  //           "    val "+e+entryClsName+" = "+map+"("+i+")\n" +
  //           "    if("+e+" != null) {\n"+
  //           "      val "+quote(k)+entryClsName+" = "+e+"\n"+
  //           "      val "+quote(v)+elemValueType+" = "+e+".v\n" +
  //           ind(block,2)+"\n" +
  //           "    }\n" +
  //           "    "+i+" += 1\n" +
  //           "  }\n" +
  //           "}"
  //         })
  //         case _ => stream.println(quote(m)+".foreach only{ ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
  //       }
  //     } else {
  //       stream.println(quote(m)+".foreach { ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
  //     }
  //   }
  //   case M3Slice(m,p,pks) => if(M3MapCommons.isInliningHigherThanNone) {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NamedM3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
  //         val map = quote(m)
  //         val mapClass = M3MapCommons.entryClassName(value,key,indexList)
  //         val nodeName = createNodeName(sym)
  //         val indexLoc = indexList(p)
  //         val targetIndex = M3MapCommons.indexMapName(map,indexLoc)
  //         val targetIndexClass = M3MapCommons.indexEntryClassName(mapClass,indexLoc)
  //         //TODOOOO
  //         //emitValDef(sym, quote(m)+".namedmapslice("+p+","+tup(pks map quote)+")")
  //         genGetMap(nodeName, targetIndex, targetIndexClass,"scala.collection.mutable.ArrayBuffer["+mapClass+"] = new scala.collection.mutable.ArrayBuffer["+mapClass+"](0)", indexLoc, pks)
  //       })
  //       case _ => emitValDef(sym, quote(m)+".sliceonly("+p+","+tup(pks map quote)+")")
  //     }
  //   } else {
  //     emitValDef(sym, quote(m)+".slice("+p+","+tup(pks map quote)+")")
  //   }
  //   case M3Clear(m) => if(M3MapCommons.isInliningHigherThanNone) {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(tp,_),_,_)) => stream.println(quote(m)+" = "+tp.zero)
  //       case Some(Reflect(NamedM3Var(_,tp),_,_)) => stream.println(quote(m)+" = "+tp.zero)
  //       case Some(Reflect(NewM3Temp(_,_,_,_),_,_)) => stream.println({
  //         val map = quote(m)
  //         genClearMap(createNodeName(sym), map, M3MapCommons.genMapSize(map), M3MapCommons.genMapThreshold(map))+"\n"
  //       })
  //       case Some(Reflect(NamedM3Map(_,_,_,indexList,_,_),_,_)) => stream.println({
  //         val map = quote(m)
  //         val nodeName = createNodeName(sym)
  //         genClearMap(nodeName, map, M3MapCommons.genMapSize(map), M3MapCommons.genMapThreshold(map))+"\n"+
  //         indexList.zipWithIndex.map{case (is, i) => genClearMap(nodeName+M3MapCommons.indexNamePostfix(is), M3MapCommons.indexMapName(map,is), M3MapCommons.genIndexMapSize(map,i), M3MapCommons.genIndexMapThreshold(map,i))+"\n"}.mkString
  //       })
  //       case _ => stream.println(quote(m)+".clearonly")
  //     }
  //   } else {
  //     Def.unapply(m) match {
  //       case Some(Reflect(NewM3Var(tp,_),_,_)) => stream.println(quote(m)+" = "+tp.zero)
  //       case Some(Reflect(NamedM3Var(_,tp),_,_)) => stream.println(quote(m)+" = "+tp.zero)
  //       case _ => stream.println(quote(m)+".clear")
  //     }
  //   }
    case _ => super.emitNode(sym,rhs)
  }

  // def createNodeName(s: Sym[_]) = "x"+s.id

  // def genForeachMap(nodeName:String, map:String, k:String, v:String, block: String, key:List[Type], value:Type, entryClsName: String) = {
  //   //f= foreach
  //   val i = nodeName+"_fi"
  //   val len = nodeName+"_flen"
  //   val e = nodeName+"_fe"
  //   val singleValueKey: Boolean = (key.size == 1)
  //   "; {\n" +
  //   "  //M3FOREACH\n" +
  //   "  var "+i+":Int = 0\n" +
  //   "  val "+len+":Int = "+map+".length\n" +
  //   "  while("+i+" < "+len+") {\n" +
  //   "    var "+e+":"+entryClsName+" = "+map+"("+i+")\n" +
  //   "    while("+e+" != null) {\n"+
  //   "      val "+k+":"+(if(singleValueKey) key(0).toScala else entryClsName)+" = "+e+(if(singleValueKey) "._1" else "")+"\n"+
  //   "      val "+v+":"+value.toScala+" = "+e+".v\n" +
  //   ind(block,2)+"\n" +
  //   "      "+e+" = "+e+".next\n" +
  //   "    }\n" +
  //   "    "+i+" += 1\n" +
  //   "  }\n" +
  //   "}"
  // }

  // def genAddNamedMap(nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_]) = {
  //   //an = add named map
  //   var isConstant:Boolean = false
  //   var isZero:Boolean = false

  //   inputValueSymbol match {
  //     case Const(c) => {
  //       isConstant = true
  //       if(c == M3MapCommons.actualZeroValue(value)) {
  //         isZero = true
  //       }
  //     }
  //     case _ => ()
  //   }

  //   val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
  //   val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)

  //   if(isZero) {
  //     "//M3ADDNAMED_CANCELLED"
  //   } else {
  //     "//M3ADDNAMED\n" +
  //     prefixValue +
  //     (if(isConstant) {
  //       genSetDetailedTempMap("",nodeName,map,M3MapCommons.entryClassName(value, key, indexList),(0 until inputKeySymbols.size).toList,inputKeySymbols,valueName,false,"+=",indexList,indexList.map(M3MapCommons.indexEntryClassName(value,key,indexList,_)), true, value.zero)
  //     } else {
  //       "if("+valueName+" != "+value.zero+") {\n" +
  //       ind(genSetDetailedTempMap("",nodeName,map,M3MapCommons.entryClassName(value, key, indexList),(0 until inputKeySymbols.size).toList,inputKeySymbols,valueName,false,"+=",indexList,indexList.map(M3MapCommons.indexEntryClassName(value,key,indexList,_)), true, value.zero))+"\n" +
  //       "}"
  //     })
  //   }
  // }

  // def genSetNamedMap(nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_]) = {
  //   //sn = set named map
  //   //val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
  //   val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
  //   //val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
  //   val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)

  //   //sn = set named map
  //   "//M3SETNAMED\n" +
  //   prefixValue +
  //   "if("+valueName+" == "+value.zero+") {\n" +
  //   genDelNamedMap(nodeName,map,key,value,indexList,(0 until inputKeySymbols.size).toList,inputKeySymbols)+ "\n" +
  //   "} else {\n" +
  //   ind(genSetDetailedTempMap("",nodeName,map,M3MapCommons.entryClassName(value, key, indexList),(0 until inputKeySymbols.size).toList,inputKeySymbols,valueName,false,"=",indexList,indexList.map(M3MapCommons.indexEntryClassName(value,key,indexList,_)), true, value.zero))+"\n" +
  //   "}"
  // }

  // def genDelNamedMap(nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]]) = {
  //   if(M3MapCommons.isInliningInSpecializedLevel) {
  //     M3MapCommons.entryClassName(value, key, indexList) + "Ops.remove(" + map + ", " + map + "__md, " + (inputKeySymbols map quote).mkString(", ") + ")"
  //   } else {
  //     //d = del
  //     val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
  //     val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)

  //     M3MapCommons.genGenericDelNamedMap(prefixKey,nodeName,map,key,value,indexList,keyIndicesInEntery,keyNames)
  //   }
  // }

  // def genAddTempMap(nodeName:String, map:String, value:Type, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_]) : String = {
  //   //at = add temp map
  //   val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
  //   val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)

  //   "//M3ADDTEMP\n" +
  //   prefixValue +
  //   "if("+valueName+" != "+value.zero+") {\n" +
  //   ind(genSetDetailedTempMap("",nodeName,map,entryClsName,keyIndicesInEntery,inputKeySymbols,valueName,false,"+="))+"\n" +
  //   "}"
  // }

  // def genSetTempMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_],insideBlock: Boolean=true, operation: String="=", indexList: List[List[Int]] = List[List[Int]](), indexEntryClsName: List[String]=List[String]()) : String = {
  //   val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
  //   val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)

  //   genSetDetailedTempMap(prefixValue,nodeName,map,entryClsName,keyIndicesInEntery,inputKeySymbols,valueName,insideBlock, operation, indexList,indexEntryClsName)
  // }

  // def genSetDetailedTempMap(prefixValue:String, nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], valueName:String, insideBlock: Boolean=true, operation: String="=", indexList: List[List[Int]] = List[List[Int]](), indexEntryClsName: List[String]=List[String](), fromNamedMap: Boolean=false, zeroValue: String = "") : String = {
  //   if(M3MapCommons.isInliningInSpecializedLevel) {
  //     prefixValue + entryClsName + "Ops."+(if (fromNamedMap) "putRemoveOnZero" else "put")+"("+ (if(operation == "=") "false" else "true") + "," + map + ", " + map + "__md, " + (inputKeySymbols map quote).mkString(", ") + ", " + valueName + indexList.map(idx => ", "+M3MapCommons.indexMapName(map,idx)).mkString + ")\n" +
  //     M3MapCommons.genIncreaseMapAndIndicesCapacity(nodeName,map,entryClsName,indexList,indexEntryClsName)
  //   } else {
  //     val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
  //     val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
  //     M3MapCommons.genGenericSetTempMap(prefixValue, prefixKey, nodeName, map, entryClsName, keyIndicesInEntery, keyNames, valueName, insideBlock, operation, indexList, indexEntryClsName, fromNamedMap, zeroValue)
  //   }
  // }

  // def genGetMap(nodeName:String, map:String, entryClsName:String, valueTypeAndZeroVal:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]]) = {
  //   if(M3MapCommons.isInliningInSpecializedLevel) {
  //     entryClsName + "Ops.get(" + map + ", " + (inputKeySymbols map quote).mkString(", ") + ")"
  //   } else {
  //     val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
  //     val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
  //     M3MapCommons.genGenericGetMap(prefixKey, nodeName, map, entryClsName, valueTypeAndZeroVal, keyIndicesInEntery, keyNames)
  //   }
  // }

  // def genClearMap(nodeName:String, map:String, mapSizeVar:String, mapThresholdVar:String) = {
  //   val currentSize = nodeName + "__csz"
  //   val currentCounter = nodeName + "__ctr"
  //   "; {\n" +
  //   "  //M3CLEAR\n" +
  //   "  val " + currentSize + ":Int = " + map + ".length\n" +
  //   "  var " + currentCounter + ":Int = 0\n" +
  //   "  while("+currentCounter+" < "+currentSize+") {\n" +
  //   "    "+map+"("+currentCounter+")=null\n" +
  //   "    "+currentCounter+"+=1\n" +
  //   "  }\n" +
  //   "  "+mapSizeVar+" = 0\n" +
  //   "  "+mapThresholdVar+"= (" + currentSize + "*" + M3MapCommons.DEFAULT_LOAD_FACTOR + ").toInt\n" +
  //   "}"
  // }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean) : String = {
    def printSym(s: Sym[Any]): String = {
      if(s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            // case NamedM3Var(n,_) => n
            // case NamedM3Map(n,_,_,_,_,_) => n
            case _ =>
              val strWriter: java.io.StringWriter = new java.io.StringWriter;
              val stream = new java.io.PrintWriter(strWriter);
              withStream(stream) {
                emitNode(s, d)
              }
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
        case false => if(s.possibleToInline || s.noReference) {
            stream.print("("+rhs+")")
          } else {
            stream.println("val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
          }
      }
      case _ => stream.println("val " + quote(sym) + getSymTypeStr(sym) + " = " + rhs + extra)
    }
  }

  def getSymTypeStr(s:Sym[_]):String = {
    val typeStr:String = remap(s.tp)
    var theType = ""
    if(typeStr.startsWith("ddbt.lib.store.Store[")) {
      theType = ":Store["+storeEntryType(s)+"]"
    }
    // if((typeStr.contains("Any")) || (typeStr.contains("$")) || (typeStr.contains("@"))) {
    //   Def.unapply(s) match {
    //     case Some(Reflect(M3Slice(name,part,partKey),_,_)) => {
    //       val elemKeyType = Def.unapply(name) match {
    //         case Some(Reflect(NamedM3Map(_,key,value,indexList,_,_),_,_)) => {
    //           theType = (if(M3MapCommons.isInliningHigherThanNone) ":scala.collection.mutable.ArrayBuffer["+M3MapCommons.entryClassName(value,key,indexList)+"]" else ":M3Map["+tup(key map (_.toScala))+","+value.toScala+"]")
    //         }
    //         case _ => theType = ""
    //       }
    //     }
    //     case _ => theType = ""
    //   }
    // } else {
    //   theType = ":"+typeStr
    // }
    theType
  }

  // override def quote(x: Exp[Any]) : String = x match {
  //   case sym@Sym(_) if sym.attributes.contains(nameAttr) => sym.attributes(nameAttr).toString
  //   case _ => super.quote(x)
  // }
}
