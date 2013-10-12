package ddbt.codegen.lms
import ddbt.ast._
import ddbt.lib.{K3Temp,K3Var}

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.reflect.SourceContext
import toasterbooster.lifters._

/**
 * The following LMS operations are implemented by these traits:
 * - Named expressions (possibly mutable) to beautify the emitted code
 * - M3 maps specific operations (get, set, add, foreach, slice, clear)
 * - Abstraction of user-library function application (inlined in k3apply)
 *
 * @author Mohammad Dashti
 */

object K3MapCommons {
  /**
   * The default initial capacity - MUST be a power of two.
   */
  final val DEFAULT_INITIAL_CAPACITY: Int = 1024
  final val DEFAULT_INITIAL_CAPACITY_INDEX: Int = 512
  final val DEFAULT_INITIAL_CAPACITY_INDEX_INNER: Int = 16
  /**
   * The maximum capacity, used if a higher value is implicitly specified
   * by either of the constructors with arguments.
   * MUST be a power of two <= 1<<30.
   */
  final val MAXIMUM_CAPACITY: Int = 1 << 30
  /**
   * The load factor used when none specified in constructor.
   */
  final val DEFAULT_LOAD_FACTOR: Float = 0.75f
  /**
   * The load factor used when none specified in constructor.
   */
  final val INITIAL_THRESHOLD: Int = (DEFAULT_INITIAL_CAPACITY * DEFAULT_LOAD_FACTOR).asInstanceOf[Int]
  final val INITIAL_THRESHOLD_INDEX: Int = (DEFAULT_INITIAL_CAPACITY_INDEX * DEFAULT_LOAD_FACTOR).asInstanceOf[Int]
  final val INITIAL_THRESHOLD_INDEX_INNER: Int = (DEFAULT_INITIAL_CAPACITY_INDEX_INNER * DEFAULT_LOAD_FACTOR).asInstanceOf[Int]

  var entryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type])]()
  var indexEntryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type],List[Int])]()

  def entryClassName(value:Type, key:List[Type]) = "EntryK"+key.map(x => shortName(x)).mkString+"_V"+shortName(value)
  def indexEntryClassName(value:Type, key:List[Type], indexLoc: List[Int]) = "IdxEntryK"+key.map(x => shortName(x)).mkString+"_V"+shortName(value)+"_I"+indexLoc.mkString("_")
  def indexMapName(map: String, indexLoc: List[Int]) = map+"_Idx"+indexLoc.mkString("_")

  def generateAllEntryClasses = generateEntryClasses + "\n" + generateIndexEntryClasses
  def generateEntryClasses = entryClasses.map { case (name, kv) =>
    val value = kv._1
    val key = kv._2
    "  class " + name + "(" +
      key.zipWithIndex.map{case (ktp, i) => "val _"+(i+1)+":"+ktp.toScala+", "}.mkString +
      "var v:" + value.toScala + ") {\n" +
    "    val hs: Int = " + hashFunction(key.zipWithIndex, "    ") + "\n" +
    "    var next:" + name + " = null\n" +
    "  }\n"
  }.mkString

  def generateIndexEntryClasses = indexEntryClasses.map { case (name, kv) =>
    val value = kv._1
    val key = kv._2
    val indexLoc = kv._3
    val entryCls = entryClassName(value, key)
    "  class " + name + " (" +
      indexLoc.map(i => "val _"+(i+1)+":"+key(i).toScala).mkString(", ") + ") {\n" +
    "    var elems: Array["+entryCls+"] = new Array["+entryCls+"]("+DEFAULT_INITIAL_CAPACITY_INDEX_INNER+");\n" +
    "    var elems__sz: Int = 0;\n" +
    "    var elems__ts: Int = "+INITIAL_THRESHOLD_INDEX_INNER+";\n" +
    "    val hs: Int = " + hashFunction(indexLoc.map(i => (key(i), i)), "    ") + "\n" +
    "    var next:" + name + " = null\n" +
    "  }\n"
  }.mkString

  /*
   * Implementation of MurmurHash3
   * based on scala.util.hashing.MurmurHash3
   * for Products
   * 
   * https://github.com/scala/scala/blob/v2.10.2/src/library/scala/util/hashing/MurmurHash3.scala
   */
  def hashFunction(keyWithIndex: List[(Type,Int)], linePrefix: String) = {
    //TODO: Is it better to do MurmurHash3 for single values?
    if(keyWithIndex.size == 1) {
      val i = keyWithIndex(0)._2
      "_"+(i+1)+".##"
    } else {
      val tupleHashSeed = "0xcafebabe"
      def rotl(i: String, distance: String) = "("+i+" << "+distance+") | ("+i+" >>> -"+distance+")"
      var counter:Int = 0
      linePrefix + "{\n"+
      linePrefix + "  var hash:Int = "+tupleHashSeed+"\n" +
      keyWithIndex.map { case (key, i) =>
        counter+=1
        //TODO: Check whether hashCode works better compared to ##
        //      as we know that everything is type-checked
        linePrefix + (if(counter == 1) "  var mix:Int" else "  mix") + " = _"+(i+1)+".## * 0xcc9e2d51\n" +
        linePrefix + "  mix = " + rotl("mix", "15")+"\n" +
        linePrefix + "  mix *= 0x1b873593\n" +
        linePrefix + "  mix ^= hash\n" +
        linePrefix + "  mix = " + rotl("mix", "13")+"\n" +
        linePrefix + "  hash = mix * 5 + 0xe6546b64\n"
      }.mkString +
      linePrefix + "  hash ^= " + keyWithIndex.size + "\n" +
      linePrefix + "  hash ^= hash >>> 16\n" +
      linePrefix + "  hash *= 0x85ebca6b\n" +
      linePrefix + "  hash ^= hash >>> 13\n" +
      linePrefix + "  hash *= 0xc2b2ae35\n" +
      linePrefix + "  hash ^= hash >>> 16\n" +
      linePrefix + "  hash\n" +
      linePrefix + "}"
    }
  }

  def shortName(tp: Type) = tp match {
    case TypeLong => "L"
    case TypeDouble => "D"
    case TypeString => "S"
    case TypeDate => "A"
  }

  def zeroValue(v: Type) = v match {
    case TypeLong => "0L"
    case TypeDouble => "0.0"
    case TypeString => "\"\""
    case TypeDate => "new Date()"
  }

  def createK3VarDefinition(name: String, value:Type) = "var "+name+" = "+zeroValue(value)

  def createK3MapDefinition(name: String, value:Type, key:List[Type], indexList: List[List[Int]]) = {
    val tk = ddbt.Utils.tup(key.map(_.toScala))
    val ix = if (indexList.size==0) "" else "List("+indexList.map{is=>"(k:"+tk+")=>"+ddbt.Utils.tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ")+")"
    "val "+name+" = K3Map.make["+tk+","+value.toScala+"]("+ix+");"
  }

  def createK3TempDefinition(value:Type, key:List[Type]) = {
    val tk = ddbt.Utils.tup(key.map(_.toScala))
    "K3Map.temp["+tk+","+value.toScala+"]();"
  }
}

trait K3MapOps extends Base {
  // Nodes creation
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]
  def namedK3Var[T](name: String)(implicit mT:Manifest[T]): Rep[K3Var[T]]
  def namedK3Map[K,V](name: String)(implicit mK:Manifest[K], mV:Manifest[V]): Rep[K3Temp[K,V]]
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
  def namedK3Var[T](name: String)(implicit mT:Manifest[T]) = reflectMutable(NamedK3Var(name)(mT))
  def namedK3Map[K, V](name: String)(implicit mK:Manifest[K], mV:Manifest[V]) = reflectMutable(NamedK3Map(name)(mK,mV))
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
  case class NamedK3Var[T](n:String)(implicit mT:Manifest[T]) extends Def[K3Var[T]]
  case class NamedK3Map[K,V](n:String)(implicit mK:Manifest[K], mV:Manifest[V]) extends Def[K3Temp[K,V]]
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

  private val nameAttr = "_name"
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NamedK3Var(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NamedK3Map(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NewK3Var(v,_) => stream.println(K3MapCommons.createK3VarDefinition(quote(sym), v))
    case NewK3Temp(ks,v,_,_) => emitValDef(sym, K3MapCommons.createK3TempDefinition(v,ks))
    case K3Get(m,ks,_) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_),_,_)) => emitValDef(sym, quote(m))
      case _ => emitValDef(sym, quote(m)+".get("+tup(ks map quote)+")")
    }
    case K3Set(m,ks,v) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_),_,_)) => stream.println(quote(m)+" = "+quote(v))
      case _ => stream.println(quote(m)+".set("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    }
    case K3Add(m,ks,v) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_),_,_)) => stream.println(quote(m)+" += "+quote(v))
      case _ => stream.println(quote(m)+".add("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    }
    case K3Foreach(m,k,v,body) =>
      val block=getBlockContents(body) // enables both the renaming trick and allow nested block indentation
      stream.println(quote(m)+".foreach { ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
    case K3Slice(m,p,pks) => emitValDef(sym, quote(m)+".slice("+p+","+tup(pks map quote)+")")
    case K3Clear(m) => stream.println(quote(m)+".clear")
    case _ => super.emitNode(sym,rhs)
  }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean) : String = {
    def printSym(s: Sym[Any]): String = {
      if(s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            case NamedK3Var(n) => n
            case NamedK3Map(n) => n
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
