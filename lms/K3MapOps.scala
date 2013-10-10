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
  final val DEFAULT_INITIAL_CAPACITY: Int = 512
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
  def k3temp(key:List[Type],value:Type) = reflectMutable(NewK3Map(key,value,man(key),man(value)))

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
  case class NewK3Map[K,V](key:List[Type],value:Type,mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[_,_]]
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
    case NewK3Map(ks,v,_,_) => emitValDef(sym, K3MapCommons.createK3TempDefinition(v,ks))
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
