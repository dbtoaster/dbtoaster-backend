package org.dbtoaster.dbtoasterlib {
  
  /** In this object, the standard external functions that can be called by
    * queries are defined.
    */
  object StdFunctions {

    def div(x: Double): Double = 1.0 / x
    
    def max(v1: Double, v2: Double): Double = if(v1 > v2) v1 else v2
    def min(v1: Double, v2: Double): Double = if(v1 < v2) v1 else v2
    
    /* This is some sort of a hack */
    def listmax(v1: Long, v2: Long): Double = max (v1, v2)
    def listmax(v1: Double, v2: Long): Double = max (v1, v2)
    def listmax(v1: Long, v2: Double): Double = max (v1, v2)
    def listmax(v1: Double, v2: Double): Double = max (v1, v2)
        
    def year_part(date: java.util.Date): Long = {
      val c = java.util.Calendar.getInstance
      c.setTime(date)   
      c.get(java.util.Calendar.YEAR) 
    }

    def month_part(date: java.util.Date): Long = {
      val c = java.util.Calendar.getInstance
      c.setTime(date)   
      c.get(java.util.Calendar.MONTH) 
    }
    
    def day_part(date: java.util.Date): Long = {
      val c = java.util.Calendar.getInstance
      c.setTime(date)   
      c.get(java.util.Calendar.DAY_OF_MONTH) 
    }    
    
    def date_part(field: String, date: java.util.Date): Long = {
      val c = java.util.Calendar.getInstance
      c.setTime(date)
      field.toUpperCase() match {
        case "YEAR"  => c.get(java.util.Calendar.YEAR)
        case "MONTH" => c.get(java.util.Calendar.MONTH)
        case "DAY"   => c.get(java.util.Calendar.DAY_OF_MONTH)
        case _ => throw new DBToasterExceptions.DBTFatalError(
                                "Invalid date part.")
      }
    }
    
	import scala.collection.mutable.Map
	val regexpCache = Map[String, java.util.regex.Pattern]()
    def regexp_match(regexp: String, str: String): Int = {
	  val pattern = regexpCache.get(regexp) match {
	    case Some(x) => x
	    case _ => {
		  val pattern = java.util.regex.Pattern.compile(regexp)
		  regexpCache += ((regexp, pattern))
		  pattern
		}
	  }
	  
      val matcher = pattern.matcher(str)
      if (matcher.find) 1 else 0
    }
    
    def substring(str: String, start: Long, length: Long): String =
      str.substring (start.toInt, (start + length).toInt)
      
      
    def vec_length = VectorFunctions.vec_length _
    def vec_dot = VectorFunctions.vec_dot _
    def vector_angle = VectorFunctions.vector_angle _
    def dihedral_angle = VectorFunctions.dihedral_angle _
    
    def hash(number: Long): Long = {
      var v: Long = number * 3935559000370003845L + 2691343689449507681L
      v ^= v >> 21; v^= v << 37; v ^= v >> 4
      v *= 4768777413237032717L
      v ^= v >> 20; v^= v << 41; v ^= v >> 5
      v
    }
    
    val PI = 3.141592653589793238462643383279502884
    def radians(degree: Double): Double = degree * PI / 180
    def degrees(radian: Double): Double = radian * 180 / PI 
    def pow(x: Double, y: Double): Double = math.pow(x, y)
    def sqrt(x: Double): Double = math.sqrt(x)
    def cos(x: Double): Double = math.cos(x)

    /* Type conversion functions */
    def cast_int(l: Long): Long = l
    def cast_int(d: Double): Long = d.toInt
    def cast_int(s: String): Long = s.toLong
    
    def cast_float(l: Long): Double = l.toDouble
    def cast_float(d: Double): Double = d
    def cast_float(s: String): Double = s.toDouble
    
    def cast_string(a: Any): String = a.toString
    def cast_string(d: java.util.Date): String = {
      val dateFormat = new java.text.SimpleDateFormat("yyyy-MM-dd")
        dateFormat.format(d)
    }

    def cast_date(d: java.util.Date): java.util.Date = d
    def cast_date (s: String): java.util.Date = {
      val dateFormat = new java.text.SimpleDateFormat("yyyy-MM-dd")
        dateFormat.parse(s)
    }
  }
  
  object VectorFunctions {
    case class Vector(val x: Double, y: Double, z: Double) {
      def -(v: Vector): Vector = {
        Vector(x-v.x, y-v.y, z-v.z)
      }
      
      def length: Double = 
        math.sqrt(x*x + y*y + z*z)
      
      def apply(v: Vector): Double =
        x*v.x + y*v.y + z*v.z
        
      def *(v: Vector): Vector = { 
        val nx = (y*v.z-z*v.y)
        val ny = (z*v.x-x*v.z)
        val nz = (x*v.y-y*v.x)
        Vector(nx, ny, nz)
      }
      
      def angle(v: Vector): Double = 
        math.acos (
          this.apply(v) / (
            this.length * v.length
          )
        )
    }
    
    def vec_length(x: Double, y: Double, z: Double): Double =
      Vector(x, y, z).length
      
    def vec_dot(x1: Double, y1: Double, z1: Double,
                x2: Double, y2: Double, z2: Double): Double = {
      val v1 = Vector(x1, y1, z1)
      val v2 = Vector(x2, y2, z2)
      v1(v2)
    }
    
    def vector_angle(x1: Double, y1: Double, z1: Double,
                x2: Double, y2: Double, z2: Double): Double = {
      val v1 = Vector(x1, y1, z1)
      val v2 = Vector(x2, y2, z2)
      v1.angle(v2)
    }
    
    def dihedral_angle(x1: Double, y1: Double, z1: Double,
                       x2: Double, y2: Double, z2: Double,
                       x3: Double, y3: Double, z3: Double,
                       x4: Double, y4: Double, z4: Double): Double = {
      val p1 = Vector(x1, y1, z1)
      val p2 = Vector(x2, y2, z2)
      val p3 = Vector(x3, y3, z3)
      val p4 = Vector(x4, y4, z4)
      
      val v1 = p2 - p1
      val v2 = p3 - p2
      val v3 = p4 - p3

      val n1 = v1 * v2
      val n2 = v2 * v3
      
      math.atan2 ( v2.length * v1(n2) , n1(n2) )
    }
  }
}
