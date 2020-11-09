package lifter

import ch.epfl.data.sc.pardis.utils
import ddbt.ast._
import ddbt.lib.store.{Store, Entry}
import ddbt.lib.store.deep.StoreDSL

import ch.epfl.data.sc.pardis.types._

/**
 * Created by khayyam on 4/9/15.
 */
trait TypeToTypeRep { this: StoreDSL =>
  
  def man(tp: Type): TypeRep[_] = tp match {
    case TypeShort | TypeInt | TypeLong => runtimeType[Long]
    case TypeFloat | TypeDouble => runtimeType[Double]
    case TypeChar => runtimeType[Char]
    case TypeString => runtimeType[String]
    case TypeDate => runtimeType[java.util.Date]
    case _ => sys.error("No typeRep for "+tp)
  }

  def man(ts: List[Type]): TypeRep[_] = ts.size match {
    case 1 => man(ts.head)
    case _ => val ms:List[TypeRep[_]] = ts map man
      val cls:java.lang.Class[_] = Class.forName("scala.Tuple"+ts.size)
      val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
      // FIXME have to apply to arguments
      new ExtendedReflectionType(tpe, ms)
  }

  def manEntry(ts:List[Type]):TypeRep[Entry] = {
    // val ms:List[TypeRep[_]] = ts map man
    // val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.SEntry"+ts.size)
    // val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
    // // FIXME have to apply to arguments
    // new ExtendedReflectionType(tpe, ms).asInstanceOf[TypeRep[Entry]]
    val ms:List[TypeRep[_]] = ts map man
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.GenericEntry")
    val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
    // FIXME have to apply to arguments
    new ExtendedReflectionType(tpe, ms).asInstanceOf[TypeRep[Entry]]
  }

  def manStore(ts:List[Type]):TypeRep[Store[Entry]] = manStore(manEntry(ts))

  def manStore(entryMan:TypeRep[Entry]):TypeRep[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Store")
    val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
    // FIXME have to apply to arguments
    new ExtendedReflectionType(tpe, Nil).asInstanceOf[TypeRep[Store[Entry]]]
  }
  def manContainer(ts:List[Type]):TypeRep[Store[Entry]] = manStore(manEntry(ts))

  def manContainer(entryMan:TypeRep[Entry]):TypeRep[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Container")
    val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
    // FIXME have to apply to arguments
    new ExtendedReflectionType(tpe, Nil).asInstanceOf[TypeRep[Store[Entry]]]
  }

  def zero(tp: Type) = tp match {
    case TypeShort | TypeInt | TypeLong => 0L
    case TypeFloat | TypeDouble => 0.0
    case TypeChar => 0.toChar
    case TypeString => ""
    case TypeDate => new java.util.Date()
    case _ => sys.error("Bad Type")
  }

  def zero(m: TypeRep[_]) = m.name match {
    case "Long" => 0L
    case "Double" => 0.0
    case "Char" => 0.toChar
    case "String" => ""
    case "java.util.Date" => new java.util.Date()
    case _ => sys.error("Bad manifest")
  }
}

// TODO Amir: move it to SC
class ExtendedReflectionType(tpe: scala.reflect.runtime.universe.Type, override val typeArguments: List[PardisType[_]] ) extends ReflectionType(tpe) {

  override def rebuild(newArguments: PardisType[_]*): PardisType[_] = new ExtendedReflectionType(tpe, typeArguments)

//  val typeTag: TypeTag[Any] = null //sys.error("No typetag available for a type constructed from a reflection type")
}
