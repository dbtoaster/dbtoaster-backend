package ddbt.lib

trait Ring[V] {
  val zero:V
  def +(v1:V,v2:V):V
  def *(v1:V,v2:V):V
}

object Ring {
  implicit object LongRing extends Ring[Long] {
    val zero=0L
    def +(x:Long,y:Long):Long = x+y
    def *(x:Long,y:Long):Long = x*y
  }

  implicit object DoubleRing extends Ring[Double] {
    val zero=0.0
    def +(x:Double,y:Double):Double = x+y
    def *(x:Double,y:Double):Double = x*y
  }
}

case class MapVal[V](val m:Int, val v:V)(implicit ring:Ring[V]) {
  def +(that:MapVal[V]) = { MapVal(m+that.m,ring.+(this.v,that.v)) }
  def *(that:MapVal[V]) = { MapVal(m*that.m,ring.*(this.v,that.v)) }
  def unary_-() = { MapVal(-m,v) }
}
