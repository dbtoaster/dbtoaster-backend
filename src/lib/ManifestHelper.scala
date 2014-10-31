package ddbt.lib

import ddbt.ast._
import ddbt.lib.store._

/* Helper to convert AST types into manifests */
object ManifestHelper {
  def man(tp:Type):Manifest[_] = tp match {
    case TypeLong => manifest[Long]
    case TypeDouble => manifest[Double]
    case TypeString => manifest[String]
    case TypeDate => manifest[java.util.Date]
    case _ => sys.error("No manifest for "+tp)
  }
  def man(ts:List[Type]):Manifest[_] = ts.size match {
    case 1 => man(ts.head)
    case _ => val ms:List[Manifest[_]] = ts map man
      val cls:java.lang.Class[_] = Class.forName("scala.Tuple"+ts.size)
      scala.reflect.ManifestFactory.classType(cls,ms.head,ms.tail:_*)
  }
  def manEntry(ts:List[Type]):Manifest[Entry] = {
    val ms:List[Manifest[_]] = ts map man
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.SEntry"+ts.size)
    scala.reflect.ManifestFactory.classType(cls,ms.head,ms.tail:_*).asInstanceOf[Manifest[Entry]]
  }
  def manStore(ts:List[Type]):Manifest[Store[Entry]] = manStore(manEntry(ts))

  def manStore(entryMan:Manifest[Entry]):Manifest[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Store")
    scala.reflect.ManifestFactory.classType(cls,entryMan).asInstanceOf[Manifest[Store[Entry]]]
  }
  def manContainer(ts:List[Type]):Manifest[Store[Entry]] = manStore(manEntry(ts))

  def manContainer(entryMan:Manifest[Entry]):Manifest[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Container")
    scala.reflect.ManifestFactory.classType(cls,entryMan).asInstanceOf[Manifest[Store[Entry]]]
  }
  def zero(tp: Type) = tp match {
    case TypeLong => 0L
    case TypeDouble => 0.0
    case TypeString => ""
    case TypeDate => new java.util.Date()
    case _ => sys.error("Bad Type")
  }
  def zero(m: Manifest[_]) = m.toString match {
    case "Long" => 0L
    case "Double" => 0.0
    case "String" => ""
    case "java.util.Date" => new java.util.Date()
    case _ => sys.error("Bad manifest")
  }
}