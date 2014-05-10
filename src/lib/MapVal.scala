package ddbt.lib
import scala.reflect.ClassTag

trait Ring[V] {
  val zero:V
  val one:V
  def -(x:V):V
  def +(x:V,y:V):V
  def *(x:V,y:V):V
  def >(x:V,y:V):Boolean
  def <(x:V,y:V):Boolean
  def <=(x:V,y:V):Boolean
  def >=(x:V,y:V):Boolean
  def toList(x:V):List[Any]
}

object Ring {
  implicit object LongRing extends Ring[Long] {
    val zero = 0L
    val one = 1L
    def -(x:Long):Long = -x 
    def +(x:Long,y:Long):Long = x + y
    def *(x:Long,y:Long):Long = x * y
    def >(x:Long,y:Long):Boolean = x > y
    def <(x:Long,y:Long):Boolean = x < y
    def <=(x:Long,y:Long):Boolean = x <= y
    def >=(x:Long,y:Long):Boolean = x >= y
    def toList(x:Long):List[Any] = List(x)
  }

  implicit object DoubleRing extends Ring[Double] {
    val zero = 0.0
    val one = 1.0
    def -(x:Double):Double = -x 
    def +(x:Double,y:Double):Double = x + y
    def *(x:Double,y:Double):Double = x * y
    def >(x:Double,y:Double):Boolean = x > y
    def <(x:Double,y:Double):Boolean = x < y
    def <=(x:Double,y:Double):Boolean = x <= y
    def >=(x:Double,y:Double):Boolean = x >= y
    def toList(x:Double):List[Any] = List(x)
  }

  implicit object StringRing extends Ring[String] {
    val zero = ""
    val one = ""
    def -(x:String):String = ???
    def +(x: String,y: String): String = ???
    def *(x: String,y: String): String = ??? 
    def >(x:String,y:String):Boolean = ???
    def <(x:String,y:String):Boolean = ???
    def <=(x:String,y:String):Boolean = ???
    def >=(x:String,y:String):Boolean = ???
    def toList(x:String):List[Any] = List(x)
  }

  implicit object DateRing extends Ring[java.util.Date] {
    val zero = new java.util.Date(0)
    val one = new java.util.Date(0)
    def -(x:java.util.Date): java.util.Date = ???
    def +(x: java.util.Date,y: java.util.Date): java.util.Date = ???
    def *(x: java.util.Date,y: java.util.Date): java.util.Date = ???
    def >(x:java.util.Date,y:java.util.Date):Boolean = x.getTime > y.getTime
    def <(x:java.util.Date,y:java.util.Date):Boolean = x.getTime < y.getTime
    def <=(x:java.util.Date,y:java.util.Date):Boolean = x.getTime <= y.getTime
    def >=(x:java.util.Date,y:java.util.Date):Boolean = x.getTime >= y.getTime
    def toList(x:java.util.Date):List[Any] = List(x)
  }
}

case class MapVal[V](val m:Int, val v:V)(implicit ring:Ring[V]) {
  def +(that:MapVal[V]) = { MapVal(m+that.m,ring.+(this.v,that.v)) }
  def *(that:MapVal[V]) = { MapVal(m*that.m,ring.*(this.v,that.v)) }
  def >(that:MapVal[V]) = { ring.>(this.v, that.v) }
  def <(that:MapVal[V]) = { ring.<(this.v, that.v) }
  def <=(that:MapVal[V]) = { ring.<=(this.v, that.v) }
  def >=(that:MapVal[V]) = { ring.>=(this.v, that.v) }
  def unary_-() = { MapVal(-m,ring.-(v)) }
  def isZero() = v == ring.zero
  def exists() = m != 0
  def isNoVal() = isZero && !exists
  def toList() = ring.toList(v)
}

object MapVal {
  def apply[V](v:V)(implicit ring:Ring[V]):MapVal[V] = MapVal[V](1,v)
  def zero[V](implicit ring:Ring[V]) = MapVal[V](1,ring.zero)
  def noVal[V](implicit ring:Ring[V]) = MapVal[V](0,ring.zero)
  def one[V](implicit ring:Ring[V]) = MapVal[V](1,ring.one)
}
