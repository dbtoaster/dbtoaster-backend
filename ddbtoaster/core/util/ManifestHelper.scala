package ddbt.lib

import ddbt.ast._
import ddbt.lib.store.{ Store, Entry }

/* Helper to convert AST types into manifests */
object ManifestHelper {

  def man(tp: Type): Manifest[_] = tp match {
    case TypeByte | TypeShort | TypeInt | TypeLong   => manifest[Long]
    case TypeFloat | TypeDouble => manifest[Double]
    case TypeChar => manifest[Char]
    case TypeString => manifest[String]
    case TypeDate   => manifest[Long]    //java.util.Date
    case t: TypeCustom => sys.error("Custom types not supported")      
    case _ => sys.error("No manifest for " + tp)
  }

  def man(ts: List[Type]): Manifest[_] = ts.size match {
    case 1 => man(ts.head)
    case _ => 
      val ms: List[Manifest[_]] = ts map man
      val cls: java.lang.Class[_] = Class.forName("scala.Tuple" + ts.size)
      scala.reflect.ManifestFactory.classType(cls, ms.head, ms.tail : _*)
  }

  def manEntry(ts: List[Type]): Manifest[Entry] = {
    val ms: List[Manifest[_]] = ts map man
    val cls: java.lang.Class[_] = Class.forName("ddbt.lib.store.SEntry" + ts.size)
    scala.reflect.ManifestFactory.classType(cls, ms.head, ms.tail : _*).asInstanceOf[Manifest[Entry]]
  }

  def manStore(ts: List[Type]): Manifest[Store[Entry]] = manStore(manEntry(ts))

  def manStore(entryMan: Manifest[Entry]): Manifest[Store[Entry]] = {
    val cls: java.lang.Class[_] = Class.forName("ddbt.lib.store.Store")
    scala.reflect.ManifestFactory.classType(cls, entryMan).asInstanceOf[Manifest[Store[Entry]]]
  }

  def manContainer(ts:List[Type]):Manifest[Store[Entry]] = manStore(manEntry(ts))

  def manContainer(entryMan:Manifest[Entry]):Manifest[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Container")
    scala.reflect.ManifestFactory.classType(cls,entryMan).asInstanceOf[Manifest[Store[Entry]]]
  }

  def zero(tp: Type) = tp match {
    case TypeByte | TypeShort | TypeInt | TypeLong => 0L
    case TypeFloat | TypeDouble => 0.0
    case TypeChar => 0.toChar
    case TypeString => ""
    case TypeDate   => 0L         // new java.util.Date()
    case t: TypeCustom => sys.error("Custom types not supported")  
    case _ => sys.error("Bad Type")
  }

  def zero(m: Manifest[_]) = m.toString match {
    case "Byte" | "Short" | "Int" | "Long" => 0L
    case "Float" | "Double" => 0.0
    case "Char" => 0.toChar
    case "String" => ""
    case "java.util.Date" => 0L   // new java.util.Date()
    case _ => sys.error("Bad manifest")
  }
}