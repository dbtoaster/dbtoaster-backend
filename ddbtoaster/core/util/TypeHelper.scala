package ddbt.lib

import ddbt.ast._

case class TypeMismatchException(msg: String) extends Exception(msg) 

/* Helper to convert AST types into language-specific string constants */
object TypeHelper {

  // C++-type specific string functions
  object Cpp {

    def typeToString(t: Type): String = t match {
      case TypeByte   => "int8_t"
      case TypeShort  => "short"
      case TypeInt    => "int"
      case TypeLong   => "long"      
      case TypeFloat  => "float"
      case TypeDouble => "DoubleType"
      case TypeDate   => "DateType"
      case TypeChar   => "char"
      case TypeString => "StringType"
      case TypeCustom(d, ps) =>
        if (ps.isEmpty) d.name
        else d.name + "<" + ps.map(paramToString).mkString(", ") + ">"
    }

    private def paramToString(p: GenericParameter): String = p match {
      case ConstParameter(c) => c.toString
      case PrimitiveTypeParameter(tp) => typeToString(tp)
      case PrioritizedParameterList(p, l) =>
        (p.toString :: l.map(paramToString)).mkString(", ")
    }

    def refTypeToString(t: Type): String = t match {
      case TypeByte   => "int8_t"
      case TypeShort  => "short"
      case TypeInt    => "int"
      case TypeLong   => "long"
      case TypeFloat  => "float"
      case TypeDouble => "DoubleType"
      case TypeDate   => "DateType"
      case TypeChar   => "char"
      case TypeString => "StringType&"
      case TypeCustom(_, _) => typeToString(t) + "&"
    }

    def constRefTypeToString(t: Type): String = t match {
      case TypeByte   => "int8_t"
      case TypeShort  => "short"
      case TypeInt    => "int"
      case TypeLong   => "long"
      case TypeFloat  => "float"
      case TypeDouble => "DoubleType"
      case TypeDate   => "DateType"
      case TypeChar   => "char"
      case TypeString => "const StringType&"
      case TypeCustom(_, _) => "const " + typeToString(t) + "&"
    }    

    def typeToChar(t: Type): String = t match {
      case TypeByte   => "b"
      case TypeShort  => "s"
      case TypeInt    => "I"
      case TypeLong   => "L"
      case TypeFloat  => "f"
      case TypeDouble => "D"
      case TypeDate   => "T"
      case TypeChar   => "c"
      case TypeString => "S"
      case TypeCustom(d, ps) =>
        if (ps.isEmpty) d.name
        else d.name + ps.map(paramToChar).mkString
    }

    private def paramToChar(p: GenericParameter): String = p match {
      case ConstParameter(c) => c.toString
      case PrimitiveTypeParameter(tp) => typeToChar(tp)
      case PrioritizedParameterList(p, l) => 
        (p.toString :: l.map(paramToChar)).mkString
    }

    def zeroOfType(t: Type): String = t match {
      case TypeByte   => "0"
      case TypeShort  => "0"
      case TypeInt    => "0"
      case TypeLong   => "0L"      
      case TypeFloat  => "0.0f"
      case TypeDouble => "0.0"
      case TypeDate   => "0"
      case TypeChar   => "0"
      case TypeString => "\"\""
      case TypeCustom(_, _) => typeToString(t) + "()"
    }

    def isPrimitiveType(t: Type): Boolean = t match {
      case TypeByte | TypeShort | TypeInt | TypeLong | 
           TypeFloat | TypeDouble | TypeDate | TypeChar => true
      case TypeString | _: TypeCustom => false
    }
  }

  // C++-type specific string functions
  object Scala {
    
    def typeToString(t: Type) = t match {
      case TypeByte | TypeShort | TypeInt | TypeLong => "Long"
      case TypeFloat | TypeDouble => "Double"
      case TypeDate   => "Long"
      case TypeChar => "Char"
      case TypeString => "String"
      case t: TypeCustom => sys.error("Custom types not supported")
    }

    def typeToChar(t: Type) = t match {
      case TypeByte | TypeShort | TypeInt | TypeLong => 'L'
      case TypeFloat | TypeDouble => 'D'
      case TypeDate => 'T'
      case TypeChar => 'C'
      case TypeString => 'S'
      case t: TypeCustom => sys.error("Custom types not supported")
    }

    def zeroOfType(t: Type) = t match {
      case TypeByte | TypeShort | TypeInt | TypeLong => "0L"
      case TypeFloat | TypeDouble => "0.0"
      case TypeDate => "0"
      case TypeChar => "0"
      case TypeString => "\"\""
      case t: TypeCustom => sys.error("Custom types not supported")
    }
  }

  def fromString(s: String, tp: Type) = tp match {
    case TypeByte | TypeShort | TypeInt | TypeLong =>
        s.trim.replaceAll("(l|L)$", "").toLong
    case TypeFloat | TypeDouble =>
        s.trim.replaceAll("(l|L|f|F)$", "").toDouble
    case TypeChar =>
        val t = s.replaceAll("^('|\")|('|\")$", "")
        assert(t.size == 1, "Unexpected character size: " + t)
        t(0)
    case TypeString =>
      s.replaceAll("^\"|\"$", "")
    case TypeDate =>
      s.trim.replaceAll("(l|L)$", "").toLong   // dateConv(v.toLong)
    case _ =>
      sys.error("Cannot convert " + s + " into " + tp)
  }

  // Implicit castings allowed by second-stage compiler ('a' can be promoted to 'b'?)
  def cast(a: Type, b: Type): Boolean = 
    try { b == a.resolve(b) }
    catch { case TypeMismatchException(msg) => false }

}