package ddbt.lib

/**
 * User-library functions, prefixed with 'U' (to avoid name clashes).
 * They represent 'built-in' functions in the M3 language.
 *
 * @TODO: For further optimization, these can be immediately inlined in the
 * generated code instead of being shipped apart (their body is very small).
 *
 * @author TCK, Milos Nikolic
 */

object Functions {

  import scala.language.implicitConversions

  implicit def boolConv(b: Boolean): Long = if (b) 1L else 0L

  // --------  Regular expression functions
  import java.util.regex.Pattern

  private val regExpCache = new collection.mutable.HashMap[String, Pattern]()

  def Uregexp_match(re: String, str: String): Long = 
    Upreg_match(regExpCache.getOrElseUpdate(re, Pattern.compile(re)), str)

  def Upreg_match(p: Pattern, str: String): Long =
    if (p.matcher(str).find) 1L else 0L

  // --------  Arithmetic functions
  def Udiv(x: Long): Double = if (x == 0L) 0.0 else 1.0 / x

  def Udiv(x: Double): Double = if (x == 0.0) 0.0 else 1.0 / x

  def Umul(x: Double, y: Double): Double = x * y

  def Umul(x: Long, y: Long): Long = x * y

  def Ulistmax(v1: Long, v2: Long): Long = Math.max(v1, v2)

  def Ulistmax(v1: Double, v2: Double): Double = Math.max(v1, v2)

  // --------  Date functions
  def Udate(str: String): Long = {
    val s = str.split("-")
    (s(0).toLong * 100 + s(1).toLong) * 100 + s(2).toLong
  }

  def Udate_year(date: Long)  = date / 10000

  def Udate_month(date: Long) = (date / 100) % 100

  def Udate_day(date: Long)   = date % 100

  def Udate_part(field: String, date: Long): Long = field.toLowerCase match {
    case "year"  => Udate_year(date)
    case "month" => Udate_month(date)
    case "day"   => Udate_day(date)
    case p => throw new Exception("Invalid date part: "+p)
  }

  // --------  String functions
  def Usubstring(s: String, b: Long, e: Long = -1L) = 
    if (e == -1L) s.substring(b.toInt) else s.substring(b.toInt, e.toInt)

  // --------  Vector operations
  case class UVector(x: Double, y: Double, z: Double) {
    def length: Double = Math.sqrt(x * x + y * y + z * z)
    def apply(v: UVector) = x * v.x + y * v.y + z * v.z // dot product
    def -(v: UVector) = UVector(x - v.x, y - v.y, z - v.z)
    def *(v: UVector) = UVector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x)
    def angle(v: UVector) = Math.acos( apply(v) / (length * v.length) )
  }

  def Uvec_length(x: Double, y: Double, z: Double): Double = 
    UVector(x,y,z).length

  def Uvec_dot(x1: Double, y1: Double, z1: Double, x2: Double, y2: Double, z2: Double) = 
    UVector(x1,y1,z1) * UVector(x2,y2,z2)

  def Uradians(degree: Double) = degree * Math.PI / 180

  def Udegrees(radian: Double) = radian * 180 / Math.PI

  def Upow(x: Double, y: Double) = Math.pow(x, y)

  def Usqrt(x: Double): Double = Math.sqrt(x)

  def Ucos(x: Double): Double = Math.cos(x)

  def Uvector_angle(x1: Double, y1: Double, z1: Double, x2: Double, y2: Double, z2: Double): Double = 
    UVector(x1, y1, z1).angle(UVector(x2, y2, z2))
  
  def Udihedral_angle(x1: Double, y1: Double, z1: Double,
                      x2: Double, y2: Double, z2: Double,
                      x3: Double, y3: Double, z3: Double,
                      x4: Double, y4: Double, z4: Double) = {
    val p1 = UVector(x1, y1, z1)
    val p2 = UVector(x2, y2, z2)
    val p3 = UVector(x3, y3, z3)
    val p4 = UVector(x4, y4, z4)
    val v1 = p2 - p1
    val v2 = p3 - p2
    val v3 = p4 - p3
    val n1 = v1 * v2
    val n2 = v2 * v3
    Math.atan2(v2.length * v1(n2), n1(n2))
  }

  def Uhash(n: Long): Long = { // mddb/query2_full.sql
    var v: Long = n * 3935559000370003845L + 2691343689449507681L
    v ^= v >> 21; v ^= v << 37; v ^= v >> 4
    v *= 4768777413237032717L
    v ^= v >> 20; v^= v << 41; v ^= v >> 5
    v
  }
}

/**  
  --- UNUSED LEGACY FUNCTIONS

  def max(v1:Double, v2:Double):Double = if(v1 > v2) v1 else v2
  def min(v1:Double, v2:Double):Double = if(v1 < v2) v1 else v2
  def listmax(v1:Long, v2:Long):Double = max (v1, v2)
  def listmax(v1:Double, v2:Long):Double = max (v1, v2)
  def listmax(v1:Long, v2:Double):Double = max (v1, v2)
  def listmax(v1:Double, v2:Double):Double = max (v1, v2)
  def year_part(date:java.util.Date) = {
    val c = java.util.Calendar.getInstance; c.setTime(date)
    c.get(java.util.Calendar.YEAR)
  }
  def month_part(date:java.util.Date) = {
    val c = java.util.Calendar.getInstance; c.setTime(date)
    c.get(java.util.Calendar.MONTH)
  }
  def day_part(date:java.util.Date):Long = {
    val c = java.util.Calendar.getInstance; c.setTime(date)
    c.get(java.util.Calendar.DAY_OF_MONTH)
  }
  def cast_int(l:Long) = l
  def cast_int(d:Double) = d.toInt
  def cast_int(s:String) = s.toLong
  def cast_float(l:Long) = l.toDouble
  def cast_float(d:Double) = d
  def cast_float(s:String) = s.toDouble
  def cast_string(a:Any) = a.toString
  def cast_string(d:java.util.Date) = new java.text.SimpleDateFormat("yyyy-MM-dd").format(d)
  def cast_date(d:java.util.Date):java.util.Date = d
  def cast_date(s:String):java.util.Date = new java.text.SimpleDateFormat("yyyy-MM-dd").parse(s)
*/
