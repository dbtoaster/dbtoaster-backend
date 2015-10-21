package ddbt.lib
import scala.reflect.ClassTag

/**
 * The M3Map can be seen as a HashMap with secondary indices, its values form
 * an abelian group with respect to addition, where zero and plus operation are
 * implicitly defined by the value type.
 *
 * @author TCK
 */

trait M3Map[K,V] {
  def get(key:K):V;           // returns the value or zero if it is not present
  def set(key:K, value:V);    // inserts or set the value
  def add(key:K, value:V);    // combines new value with existing one using 'plus'
  def foreach(f:(K,V)=>Unit); // iterates through all non-zero values of the map
  def slice[T](index:Int,subKey:T):M3Map[K,V]; // partition where the secondary index is equal to subKey
  def sum(acc:M3Map[K,V]);    // accumulate in acc: acc <- element_wise_sum(this,acc)
  def clear();                // erases all elements of the map or slice
  def size:Int;               // number of key-value mappings in the map
  def toMap:Map[K,V];         // convert to a Scala map
}

/**
 * Helper for constructing maps. Examples:
 *   val map1 = M3Map.makeIdx[(Long,Long),Long](0,1)
 *   val map2 = M3Map.make[(Long,Long),Long]( (x:(Long,Long))=>x._1, (x:(Long,Long))=>x._2 )
 *   val tmp1 = M3Map.temp[Long,Long]();
 */
object M3Map {
  def temp[K,V:ClassTag]():M3Map[K,V] = new M3MapBase[K,V](zero[V](),false,null)
  def make[K,V:ClassTag](projs:K=>_ *):M3Map[K,V] = {
    new M3MapBase(zero[V](),true,projs.toArray)
  }
  def makeIdx[K<:Product,V:ClassTag](projs:Int *):M3Map[K,V] = {
    new M3MapBase(zero[V](),true,projs.map(i => (k:K)=>k.productElement(i)).toArray)
  }
  // Implicit default zero
  def zero[V]()(implicit cV:ClassTag[V]):V = (cV.toString match {
    case "Long" => 0L
    case "Double" => 0.0
    case "java.lang.String" => ""
    case "java.util.Date" => new java.util.Date(0)
    case n => sys.error("No zero for "+n)
  }).asInstanceOf[V]
  // Pretty-print a map
  def toStr(o:Any):String = if (o.isInstanceOf[Map[_,_]]) toStr(o.asInstanceOf[Map[_,_]]) else o.toString
  def toStr[K,V](m:Map[K,V]):String = m.toList.map{case(k,v)=>(str(k),str(v))}.sortBy(x=>x._1).map{case(k,v)=>k+" -> "+v}.mkString("\n")
  // Convert a map into XML (for debug purposes)
  def toXML[K,V](m:Map[K,V]): List[xml.Elem] = {
    var l = List[xml.Elem]()
    m.foreach{case (k,v) =>
      val key = try {
          (k.asInstanceOf[Product].productIterator.foldLeft((0,List[xml.Elem]())) {
                case ((i,l), k) => (i+1, <xml>{ str(k) }</xml>.copy(label=("__a" + i)) :: l)
          })._2.reverse
        } catch { case e:java.lang.ClassCastException => <__a0>{ str(k) }</__a0> }
      l = <item>{ key }<__av>{ str(v) }</__av></item> :: l
    }
    l.sortBy(_.toString)
  }
  private val ft = new java.text.SimpleDateFormat("yyyyMMdd")
  private def str(v:Any) = v match {
    case p:Product => "("+(0 until p.productArity).map{x=>p.productElement(x)}.mkString(",")+")"
    case d:java.util.Date => ft.format(d)
    case x => x.toString
  }
}
