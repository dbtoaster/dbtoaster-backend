package ddbt.lib

import ddbt.ast._

case class TypeMismatchException(msg: String) extends Exception(msg) 

/* Helper to convert AST types into language-specific string constants */
object TypeHelper {

  // C++-type specific string functions
  object Cpp {

    def typeToString(t: Type) = t match {
      case TypeChar   => "char"
      case TypeShort  => "short"
      case TypeInt    => "int"
      case TypeLong   => "long"      
      case TypeFloat  => "float"
      case TypeDouble => "DOUBLE_TYPE"
      case TypeDate   => "date"
      case TypeString => "STRING_TYPE"
      case TypeCustom(d, p) => d.name + p.mkString
    }

    def refTypeToString(t: Type) = t match {
      case TypeChar   => "char"
      case TypeShort  => "short"
      case TypeInt    => "int"
      case TypeLong   => "long"
      case TypeFloat  => "float"
      case TypeDouble => "DOUBLE_TYPE"
      case TypeDate   => "date"
      case TypeString => "STRING_TYPE&"
      case TypeCustom(d, p) => d.name + p.mkString + "&"
    }

    def typeToChar(t: Type) = t match {
      case TypeChar   => "c"
      case TypeShort  => "s"
      case TypeInt    => "I"
      case TypeLong   => "L"
      case TypeFloat  => "f"
      case TypeDouble => "D"
      case TypeDate   => "T"
      case TypeString => "S"
      case TypeCustom(d, p) => d.name + p.mkString
    }

    def zeroOfType(t: Type) = t match {
      case TypeChar   => "0"
      case TypeShort  => "0"
      case TypeInt    => "0"
      case TypeLong   => "0L"      
      case TypeFloat  => "0.0f"
      case TypeDouble => "0.0"
      case TypeDate   => "0"
      case TypeString => "\"\""
      case TypeCustom(d, p) => d.name + p.mkString + "::zero"
    }
  }

  // C++-type specific string functions
  object Scala {
    
    def typeToString(t: Type) = t match {
      case TypeChar | TypeShort | TypeInt | TypeLong => "Long"
      case TypeFloat | TypeDouble => "Double"
      case TypeDate   => "Long"
      case TypeString => "String"
      case t: TypeCustom => sys.error("Custom types not supported")
    }

    def typeToChar(t: Type) = t match {
      case TypeChar | TypeShort | TypeInt | TypeLong => 'L'
      case TypeFloat | TypeDouble => 'D'
      case TypeDate => 'T'
      case TypeString => 'S'
      case t: TypeCustom => sys.error("Custom types not supported")
    }

    def zeroOfType(t: Type) = t match {
      case TypeChar | TypeShort | TypeInt | TypeLong => "0L"
      case TypeFloat | TypeDouble => "0.0"
      case TypeDate => "0"
      case TypeString => "\"\""
      case t: TypeCustom => sys.error("Custom types not supported")
    }
  }

  def fromString(s: String, tp: Type) = tp match {
    case TypeChar | TypeShort | TypeInt | TypeLong => s.trim.replaceAll("(l|L)$", "").toLong
    case TypeFloat | TypeDouble => s.trim.replaceAll("(l|L|f|F)$", "").toDouble
    case TypeString => s.replaceAll("^\"|\"$", "")
    case TypeDate => s.trim.replaceAll("(l|L)$", "").toLong   // dateConv(v.toLong)
    case _ => sys.error("Cannot convert " + s + " into " + tp)
  }

  // Implicit castings allowed by second-stage compiler ('a' can be promoted to 'b'?)
  def cast(a: Type, b: Type): Boolean = 
    try { b == a.resolve(b) } catch { case TypeMismatchException(msg) => false }

}