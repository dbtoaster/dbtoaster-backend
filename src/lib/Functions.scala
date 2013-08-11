package ddbt.lib
import java.util.Date;

object Functions {
  import scala.language.implicitConversions
  // Implicit conversions
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L
  implicit def dateOps(d:Date):DateWrapper = new DateWrapper(d)
  class DateWrapper(d:Date) {
    def < (d2:Date) = d.getTime < d2.getTime
    def > (d2:Date) = d.getTime > d2.getTime
    def <= (d2:Date) = d.getTime <= d2.getTime
    def >= (d2:Date) = d.getTime >= d2.getTime
  }

  // User functions that can be called using apply
  // These are prefixed by U (user) to avoid name clash with possible other functions
  def Udate(str:String):Date = {
    val s=str.split("-")
    new java.util.GregorianCalendar(s(0).toInt,s(1).toInt - 1,s(2).toInt).getTime();
  }
  
  private val re_cache = new java.util.HashMap[String, java.util.regex.Pattern]()
  def Uregexp_match(re:String, str:String): Int = if ((re_cache.get(re) match {
    case null => val p=java.util.regex.Pattern.compile(re); re_cache.put(re,p); p
    case p => p
  }).matcher(str).find) 1 else 0

  def Udiv(x: Double): Double = 1.0 / x
}
