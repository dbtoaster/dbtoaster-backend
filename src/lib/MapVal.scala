package ddbt.lib

trait Ring[V] {
  val zero:V
  val one:V
  def +(v1:V,v2:V):V
  def *(v1:V,v2:V):V
}

object Ring {
  implicit object LongRing extends Ring[Long] {
    val zero = 0L
    val one = 1L
    def +(x:Long,y:Long):Long = x+y
    def *(x:Long,y:Long):Long = x*y
  }

  implicit object DoubleRing extends Ring[Double] {
    val zero = 0.0
    val one = 1.0
    def +(x:Double,y:Double):Double = x+y
    def *(x:Double,y:Double):Double = x*y
  }

  implicit object StringRing extends Ring[String] {
    val zero = ""
    val one = ???
    def +(v1: String,v2: String): String = ???
    def *(v1: String,v2: String): String = ??? 
  }

  implicit object DateRing extends Ring[java.util.Date] {
    val zero = ???
    val one = ???
    def +(v1: java.util.Date,v2: java.util.Date): java.util.Date = ???
    def *(v1: java.util.Date,v2: java.util.Date): java.util.Date = ???
  }
}

case class MapVal[V](val m:Int, val v:V)(implicit ring:Ring[V]) {
  def +(that:MapVal[V]) = { MapVal(m+that.m,ring.+(this.v,that.v)) }
  def *(that:MapVal[V]) = { MapVal(m*that.m,ring.*(this.v,that.v)) }
  def unary_-() = { MapVal(-m,v) }
}

object MapVal {
  def apply[V](v:V)(implicit ring:Ring[V]):MapVal[V] = MapVal[V](1,v)
  def zero[V](implicit ring:Ring[V]) = MapVal[V](1,ring.zero)
  def one[V](implicit ring:Ring[V]) = MapVal[V](1,ring.one)
}
