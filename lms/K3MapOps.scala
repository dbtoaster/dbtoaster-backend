package ddbt.codegen.lms
import ddbt.ast._
import ddbt.lib.{K3Temp,K3Var}

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.reflect.SourceContext
import toasterbooster.lifters._
import ddbt.Utils.ind

/**
 * The following LMS operations are implemented by these traits:
 * - Named expressions (possibly mutable) to beautify the emitted code
 * - M3 maps specific operations (get, set, add, foreach, slice, clear)
 * - Abstraction of user-library function application (inlined in k3apply)
 *
 * @author Mohammad Dashti
 */
trait K3MapOps extends Base {
  // Nodes creation
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]
  def namedK3Var[T](name: String,tp:Type)(implicit mT:Manifest[T]): Rep[K3Var[T]]
  def namedK3Map[K,V](name: String,key:List[Type],value:Type,indexList: List[List[Int]])(implicit mK:Manifest[K], mV:Manifest[V]): Rep[K3Temp[K,V]]
  def k3var(value:Type) : Rep[K3Var[_]]
  def k3temp(key_tp:List[Type],value_tp:Type):Rep[K3Temp[_,_]]
  // Operations on K3Map, K3Var and K3Temp
  def k3get(map:Rep[_], key:List[Rep[_]]=Nil,value_tp:Type):Rep[_]
  def k3set(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3add(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3foreach(map:Rep[_], key: Rep[_], value: Rep[_], body: => Rep[Unit]) : Rep[Unit]
  def k3slice(map:Rep[_],part:Int,partKey:List[Rep[_]]):Rep[_]
  def k3clear(map:Rep[_]):Rep[Unit]
}

trait K3MapOpsExp extends BaseExp with EffectExp with K3MapOps{
  import ManifestHelper.man
  def named(name:String,tp:Type,mutable:Boolean=false) = named(name,mutable)(man(tp))
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]) = { val n=Named(name)(mT); if (mutable) reflectMutable(n) else n }
  def namedK3Var[T](name: String,tp:Type)(implicit mT:Manifest[T]) = reflectMutable(NamedK3Var(name,tp)(mT))
  def namedK3Map[K, V](name: String,key:List[Type],value:Type,indexList: List[List[Int]])(implicit mK:Manifest[K], mV:Manifest[V]) = reflectMutable(NamedK3Map(name,key,value,indexList,mK,mV))
  def k3var(value:Type) = reflectMutable(NewK3Var(value,man(value)))
  def k3temp(key:List[Type],value:Type) = reflectMutable(NewK3Temp(key,value,man(key),man(value)))

  def k3get(map:Exp[_], key:List[Exp[_]],value_tp:Type) = K3Get(map,key,man(value_tp))
  def k3set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Set(map,key,value))
  def k3add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Add(map,key,value))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body: => Exp[Unit]) = k3foreach(map,key,value,reifyEffects(body))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body:Block[Unit]) = reflectEffect(K3Foreach(map,key,value,body),summarizeEffects(body).star)
  def k3slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) = K3Slice(map,part,partKey)
  def k3clear(map:Exp[_]) = reflectWrite(map)(K3Clear(map))

  case class Named[T](n:String)(implicit mT:Manifest[T]) extends Def[T]
  case class NamedK3Var[T](n:String,tp:Type)(implicit mT:Manifest[T]) extends Def[K3Var[T]]
  case class NamedK3Map[K,V](n:String,key:List[Type],value:Type,indexList: List[List[Int]],mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[K,V]]
  case class NewK3Var[K,V](value:Type,mV:Manifest[V]) extends Def[K3Var[_]]
  case class NewK3Temp[K,V](key:List[Type],value:Type,mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[_,_]]
  case class K3Get[T](map:Exp[_], key:List[Exp[_]],mt:Manifest[T]) extends Def[T]
  case class K3Set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Foreach(map:Exp[_], key:Exp[_], value:Exp[_], body:Block[Unit]) extends Def[Unit]
  case class K3Slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) extends Def[Exp[_]]
  case class K3Clear(map:Exp[_]) extends Def[Unit]

  override def syms(e: Any): List[Sym[Any]] = e match {
    case K3Foreach(m,k,v,b) => syms(k):::syms(v):::syms(b)
    case _ => super.syms(e)
  }
  override def boundSyms(e: Any): List[Sym[Any]] = e match {
    case K3Foreach(m,k,v,b) => effectSyms(k):::effectSyms(v):::effectSyms(b)
    case _ => super.boundSyms(e)
  }
  override def symsFreq(e: Any): List[(Sym[Any], Double)] = e match {
    case K3Foreach(m,k,v,b) => freqHot(k):::freqHot(v):::freqHot(b)
    case _ => super.symsFreq(e)
  }
  override def aliasSyms(e: Any): List[Sym[Any]] = e match {
    case K3Set(m,k,v) => Nil
    case K3Add(m,k,v) => Nil
    case _ => super.aliasSyms(e)
  }
}

trait ScalaGenK3MapOps extends ScalaGenBase with ScalaGenEffect {
  val IR: K3MapOpsExp with ExtendedExpressions
  import IR._
  import ddbt.Utils.{ind,tup}

  protected def getBlockContents(blk:Block[_]):String = {
    val save=stream; val wr=new java.io.StringWriter; stream=new java.io.PrintWriter(wr)
    emitBlock(blk); val res=ind(wr.toString); stream=save; res
  }

  def isPossibleToInlineExpr(expr: Exp[_]) = expr match {
    case s@Sym(x) => s.possibleToInline
    case _ => true
  }

  /**
   * If we are using an expression result inside an operation,
   * and this expression is possible to inline, and the result
   * should be used several times in this operation, we should
   * first creat a symbol for it
   */
  def genValDefForNonInlinableExpr(exprList: List[Exp[_]], nodeName: String) = exprList.map{ expr => expr match {
      case s@Sym(x) => if(isPossibleToInlineExpr(expr)) {
        "val x"+x+"_"+nodeName+" = "+quote(expr)+"\n"
      } else {
        ""
      }
      case _ => ""
    }
  }.mkString

  /**
   * Tightly related to genValDefForNonInlinableExpr
   * If we have created val-def for an inlinable expression,
   * we should take care of its symbol
   */
  def genQuoteExpr(exprList: List[Exp[_]], nodeName: String) = exprList.map{ expr => expr match {
      case s@Sym(x) => if(isPossibleToInlineExpr(expr)) {
        "x"+x+"_"+nodeName
      } else {
        quote(expr)
      }
      case _ => quote(expr)
    }
  }

  private val nameAttr = "_name"
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NamedK3Var(n,_) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NamedK3Map(n,_,_,_,_,_) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NewK3Var(v,_) => stream.println(K3MapCommons.createK3VarDefinition(quote(sym), v))
    case NewK3Temp(ks,v,_,_) => if(K3MapCommons.InliningLevel >= K3MapCommons.InliningLevelMax) {
      stream.println(K3MapCommons.createK3TempDefinition(quote(sym),v,ks))
    } else {
      emitValDef(sym, "K3Map.temp["+tup(ks map (_.toScala))+","+v.toScala+"]()")
    }
    case K3Get(m,ks,_) => if(K3MapCommons.InliningLevel >= K3MapCommons.InliningLevelMax) {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => emitValDef(sym, quote(m))
        case Some(Reflect(NewK3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
          val map = quote(m)
          val nodeName = createNodeName(sym)
          genGetMap(nodeName, map, K3MapCommons.entryClassName(value, key),value.toScala+" = "+K3MapCommons.zeroValue(value), (0 until ks.size).toList, ks)
        })
        case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
          val map = quote(m)
          val nodeName = createNodeName(sym)
          genGetMap(nodeName, map, K3MapCommons.entryClassName(value, key, indexList),value.toScala+" = "+K3MapCommons.zeroValue(value), (0 until ks.size).toList, ks)
        })
        case _ => emitValDef(sym, quote(m)+".getonly("+tup(ks map quote)+")")
      }
    } else {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => emitValDef(sym, quote(m))
        case _ => emitValDef(sym, quote(m)+".get("+tup(ks map quote)+")")
      }

    }
    case K3Set(m,ks,v) => if(K3MapCommons.InliningLevel >= K3MapCommons.InliningLevelMax) {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => stream.println(quote(m)+" = "+quote(v))
        case Some(Reflect(NewK3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
          val map = quote(m)
          val nodeName = createNodeName(sym)
          genSetTempMap(nodeName, map, K3MapCommons.entryClassName(value, key, List[List[Int]]()), (0 until ks.size).toList, ks, v)
        })
        case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
          val map = quote(m)
          val nodeName = createNodeName(sym)
          genSetNamedMap(nodeName, map, key, value, indexList, ks, v)
        })
        case _ => stream.println(quote(m)+".setonly("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
      }
    } else {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => stream.println(quote(m)+" = "+quote(v))
        case _ => stream.println(quote(m)+".set("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
      }
    }
    case K3Add(m,ks,v) => if(K3MapCommons.InliningLevel >= K3MapCommons.InliningLevelMax) {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => stream.println(quote(m)+" += "+quote(v))
        case Some(Reflect(NewK3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
          val map = quote(m)
          val nodeName = createNodeName(sym)
          genAddTempMap(nodeName, map, value, K3MapCommons.entryClassName(value, key, List[List[Int]]()), (0 until ks.size).toList, ks, v)
        })
        case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
          val map = quote(m)
          val nodeName = createNodeName(sym)
          genAddNamedMap(nodeName, map, key, value, indexList, ks, v)
        })
        case _ => stream.println(quote(m)+".addonly("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
      }
    } else {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => stream.println(quote(m)+" += "+quote(v))
        case _ => stream.println(quote(m)+".add("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
      }
    }
    case K3Foreach(m,k,v,body) => {
      val block=getBlockContents(body) // enables both the renaming trick and allow nested block indentation
      if(K3MapCommons.InliningLevel >= K3MapCommons.InliningLevelMax) {
        Def.unapply(m) match {
          case Some(Reflect(NewK3Temp(key,_,_,_),_,_)) => stream.println({
            val map = quote(m)
            val nodeName = createNodeName(sym)
            
            genForeachMap(nodeName, map, quote(k), quote(v), block, key.size == 1)
          })
          case Some(Reflect(NamedK3Map(_,key,_,_,_,_),_,_)) => stream.println({
            val map = quote(m)
            val nodeName = createNodeName(sym)
            
            genForeachMap(nodeName, map, quote(k), quote(v), block, key.size == 1)
          })
          case Some(Reflect(K3Slice(name,part,partKey),_,_)) => stream.println({
            val nodeName = createNodeName(sym)
            val map = genQuoteExpr(List(m),nodeName).apply(0)

            val elemKeyPostfix = Def.unapply(m) match {
              case Some(Reflect(NamedK3Map(_,_,_,indexList,_,_),_,_)) => stream.println({
                val indexLoc = indexList(part)
                if(indexLoc.size == 1) {
                  "._"+indexLoc(0)
                } else ""
              })
              case _ => ""
            }
            
            //f= foreach
            val i = nodeName+"_fi"
            val len = nodeName+"_flen"
            val e = nodeName+"_fe"
            val sliceValDef = ind(genValDefForNonInlinableExpr(List(m),nodeName))
            "; {\n" +
            (if(sliceValDef.length > 2) sliceValDef+"\n" else "") +
            "  //SLICEK3FOREACH\n" +
            "  var "+i+":Int = 0\n" +
            "  val "+len+":Int = "+map+".length\n" +
            "  while("+i+" < "+len+") {\n" +
            "    val "+e+" = "+map+"("+i+")\n" +
            "    if("+e+" != null) {\n"+
            "      val "+quote(k)+" = "+e+elemKeyPostfix+"\n"+
            "      val "+quote(v)+" = "+e+".v\n" +
            ind(block,2)+"\n" +
            "    }\n" +
            "    "+i+" += 1\n" +
            "  }\n" +
            "}"
          })
          case _ => stream.println(quote(m)+".foreach only{ ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
        }
      } else {
        stream.println(quote(m)+".foreach { ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
      }
    }
    case K3Slice(m,p,pks) => if(K3MapCommons.InliningLevel >= K3MapCommons.InliningLevelMax) {
      Def.unapply(m) match {
        case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
          val map = quote(m)
          val mapClass = K3MapCommons.entryClassName(value,key,indexList)
          val nodeName = createNodeName(sym)
          val indexLoc = indexList(p)
          val targetIndex = K3MapCommons.indexMapName(map,indexLoc)
          val targetIndexClass = K3MapCommons.indexEntryClassName(mapClass,indexLoc)
          //TODOOOO
          //emitValDef(sym, quote(m)+".namedmapslice("+p+","+tup(pks map quote)+")")
          genGetMap(nodeName, targetIndex, targetIndexClass,"scala.collection.mutable.ArrayBuffer["+mapClass+"] = new scala.collection.mutable.ArrayBuffer["+mapClass+"](0)", indexLoc, pks)
        })
        case _ => emitValDef(sym, quote(m)+".sliceonly("+p+","+tup(pks map quote)+")")
      }
    } else {
      emitValDef(sym, quote(m)+".slice("+p+","+tup(pks map quote)+")")
    }
    case K3Clear(m) => if(K3MapCommons.InliningLevel >= K3MapCommons.InliningLevelMax) {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(tp,_),_,_)) => stream.println(quote(m)+" = "+K3MapCommons.zeroValue(tp))
        case Some(Reflect(NamedK3Var(_,tp),_,_)) => stream.println(quote(m)+" = "+K3MapCommons.zeroValue(tp))
        case Some(Reflect(NewK3Temp(_,_,_,_),_,_)) => stream.println({
          genClearMap(createNodeName(sym), quote(m))+"\n"
        })
        case Some(Reflect(NamedK3Map(_,_,_,indexList,_,_),_,_)) => stream.println({
          val map = quote(m)
          val nodeName = createNodeName(sym)
          genClearMap(nodeName, map)+"\n"+
          indexList.map(is => genClearMap(nodeName+K3MapCommons.indexNamePostfix(is), K3MapCommons.indexMapName(map,is))+"\n").mkString
        })
        case _ => stream.println(quote(m)+".clearonly")
      }
    } else {
      Def.unapply(m) match {
        case Some(Reflect(NewK3Var(tp,_),_,_)) => stream.println(quote(m)+" = "+K3MapCommons.zeroValue(tp))
        case Some(Reflect(NamedK3Var(_,tp),_,_)) => stream.println(quote(m)+" = "+K3MapCommons.zeroValue(tp))
        case _ => stream.println(quote(m)+".clear")
      }
    }
    case _ => super.emitNode(sym,rhs)
  }

  def createNodeName(s: Sym[_]) = "x"+s.id

  def genForeachMap(nodeName:String, map:String, k:String, v:String, block: String, singleValueKey: Boolean) = {
    //f= foreach
    val i = nodeName+"_fi"
    val len = nodeName+"_flen"
    val e = nodeName+"_fe"
    "; {\n" +
    "  //K3FOREACH\n" +
    "  var "+i+" = 0\n" +
    "  val "+len+" = "+map+".length\n" +
    "  while("+i+" < "+len+") {\n" +
    "    var "+e+" = "+map+"("+i+")\n" +
    "    while("+e+" != null) {\n"+
    "      val "+k+" = "+e+(if(singleValueKey) "._1" else "")+"\n"+
    "      val "+v+" = "+e+".v\n" +
    ind(block,2)+"\n" +
    "      "+e+" = "+e+".next\n" +
    "    }\n" +
    "    "+i+" += 1\n" +
    "  }\n" +
    "}"
  }

  def genAddNamedMap(nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_]) = {
    //an = add named map
    var isConstant:Boolean = false
    var isZero:Boolean = false

    inputValueSymbol match {
      case Const(c) => {
        isConstant = true
        if(c == K3MapCommons.actualZeroValue(value)) {
          isZero = true
        }
      }
      case _ => ()
    }

    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
    val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)
    K3MapCommons.genGenericAddNamedMap(isConstant,isZero,prefixValue,prefixKey,nodeName,map,key,value,indexList,keyNames,valueName)
  }

  def genSetNamedMap(nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_], operation: String="") = {
    //sn = set named map
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
    val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)

    K3MapCommons.genGenericSetNamedMap(prefixValue,prefixKey,nodeName,map,key,value,indexList,keyNames,valueName,operation)
  }

  def genDelNamedMap(nodeName:String, map:String, key:List[Type], value:Type, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_], indexList: List[List[Int]], operation: String="") = {
    //d = del
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)

    K3MapCommons.genGenericDelNamedMap(prefixKey,nodeName,map,key,value,indexList,keyIndicesInEntery,keyNames)
  }

  def genAddTempMap(nodeName:String, map:String, value:Type, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_]) : String = {
    //at = add temp map
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)

    "//K3ADDTEMP\n" +
    genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName) +
    "if("+valueName+" != "+K3MapCommons.zeroValue(value)+") {\n" +
    ind(genSetTempMap(nodeName,map,entryClsName,keyIndicesInEntery,inputKeySymbols,inputValueSymbol,false,"+="))+"\n" +
    "}"
  }

  def genSetTempMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_],insideBlock: Boolean=true, operation: String="=", indexList: List[List[Int]] = List[List[Int]](), indexEntryClsName: List[String]=List[String]()) : String = {
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
    val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)
    K3MapCommons.genGenericSetTempMap(prefixValue, prefixKey, nodeName, map, entryClsName, keyIndicesInEntery, keyNames, valueName, insideBlock, operation, indexList, indexEntryClsName)
  }

  def genGetMap(nodeName:String, map:String, entryClsName:String, valueTypeAndZeroVal:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]]) = {
    //g = get
    val hash = nodeName+"_ghash"
    val e = nodeName+"_ge"
    val found = nodeName+"_gfound"
    val result = nodeName+"_gresult"
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    "{\n" +
    "  //K3GET\n" +
    genValDefForNonInlinableExpr(inputKeySymbols,nodeName) +
    "  val "+hash+" =" + ind(K3MapCommons.hashFunction(keyNames)) + "\n" +
    "  var "+e+":" + entryClsName + " = " + map + "(" + K3MapCommons.indexForFunction(hash, map+".length") + ")\n" +
    "  var "+found+":Boolean = false\n" +
    "  var "+result+":"+valueTypeAndZeroVal+"\n" +
    "  while(!"+found+" && "+e+" != null) {\n" +
    "    if("+e+".hs == "+hash+" && "+keyNames.zip(keyIndicesInEntery).map{case (x, i) => e+"._"+(i+1)+" == "+x}.mkString(" && ")+") {\n"+
    "      "+found+" = true\n"+
    "      "+result+" = "+e+".v\n" +
    "    }\n" +
    "    "+e+" = "+e+".next\n" +
    "  }\n" +
    "  "+result+"\n" +
    "}"
  }

  def genClearMap(nodeName:String, map:String) = {
    val currentSize = nodeName + "__csz"
    val currentCounter = nodeName + "__ctr"
    "; {\n" +
    "  //K3CLEAR\n" +
    "  val " + currentSize + ":Int = " + map + ".length\n" +
    "  var " + currentCounter + ":Int = 0\n" +
    "  while("+currentCounter+" < "+currentSize+") {\n" +
    "    "+map+"("+currentCounter+")=null\n" +
    "    "+currentCounter+"+=1\n" +
    "  }\n" +
    "  "+map+"__sz = 0\n" +
    "  "+map+"__ts = (" + currentSize + "*" + K3MapCommons.DEFAULT_LOAD_FACTOR + ").toInt\n" +
    "}"
  }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean) : String = {
    def printSym(s: Sym[Any]): String = {
      if(s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            case NamedK3Var(n,_) => n
            case NamedK3Map(n,_,_,_,_,_) => n
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

  // 
  // override def quote(x: Exp[Any]) : String = x match {
  //   case sym@Sym(_) if sym.attributes.contains(nameAttr) => sym.attributes(nameAttr).toString
  //   case _ => super.quote(x)
  // }
}
