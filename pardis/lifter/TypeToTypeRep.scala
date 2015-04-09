package lifter

import ddbt.ast._
import ddbt.lib.store.{Store, Entry}
import ddbt.lib.store.deep.StoreDSL

import ch.epfl.data.sc.pardis.types._

/**
 * Created by khayyam on 4/9/15.
 */
trait TypeToTypeRep { this: StoreDSL =>
  def man(tp:Type):TypeRep[_] = tp match {
    case TypeLong => runtimeType[Long]
    case TypeDouble => runtimeType[Double]
    case TypeString => runtimeType[String]
    case TypeDate => runtimeType[java.util.Date]
    case _ => sys.error("No typeRep for "+tp)
  }
  def man(ts:List[Type]):TypeRep[_] = ts.size match {
    case 1 => man(ts.head)
    case _ => val ms:List[TypeRep[_]] = ts map man
      val cls:java.lang.Class[_] = Class.forName("scala.Tuple"+ts.size)
      val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
      // FIXME have to apply to arguments
      new ReflectionType(tpe)
  }
  def manEntry(ts:List[Type]):TypeRep[Entry] = {
    val ms:List[Manifest[_]] = ts map man
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.SEntry"+ts.size)
    val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
    // FIXME have to apply to arguments
    new ReflectionType(tpe).asInstanceOf[TypeRep[Entry]]
  }
  def manStore(ts:List[Type]):TypeRep[Store[Entry]] = manStore(manEntry(ts))

  def manStore(entryMan:TypeRep[Entry]):TypeRep[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Store")
    val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
    // FIXME have to apply to arguments
    new ReflectionType(tpe).asInstanceOf[TypeRep[Store[Entry]]]
  }
  def manContainer(ts:List[Type]):TypeRep[Store[Entry]] = manStore(manEntry(ts))

  def manContainer(entryMan:TypeRep[Entry]):TypeRep[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Container")
    val tpe = scala.reflect.runtime.universe.runtimeMirror(cls.getClassLoader).classSymbol(cls).typeSignature
    // FIXME have to apply to arguments
    new ReflectionType(tpe).asInstanceOf[TypeRep[Store[Entry]]]
  }
  def zero(tp: Type) = tp match {
    case TypeLong => 0L
    case TypeDouble => 0.0
    case TypeString => ""
    case TypeDate => new java.util.Date()
    case _ => sys.error("Bad Type")
  }
  def zero(m: TypeRep[_]) = m.name match {
    case "Long" => 0L
    case "Double" => 0.0
    case "String" => ""
    case "java.util.Date" => new java.util.Date()
    case _ => sys.error("Bad manifest")
  }
}
