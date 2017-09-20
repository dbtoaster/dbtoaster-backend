package ddbt.lib

import ddbt.ast._

/* Helper to convert AST types into language-specific string constants */
object TypeHelper {

  // C++-type specific string functions
  object Cpp {

    def typeToString(t: Type) = t match {
      case TypeLong => "long"
      case TypeDouble => "DOUBLE_TYPE"
      case TypeDate => "date"
      case TypeString => "STRING_TYPE"
    }

    def refTypeToString(t: Type) = t match {
      case TypeLong => "long"
      case TypeDouble => "DOUBLE_TYPE"
      case TypeDate => "date"
      case TypeString => "STRING_TYPE&"
    }

    def typeToChar(t: Type) = t match {
      case TypeLong => 'L'
      case TypeDouble => 'D'
      case TypeDate => 'A'
      case TypeString => 'S'
    }

    def zeroOfType(t: Type) = t match {
      case TypeLong => "0L"
      case TypeDouble => "0.0"
      case TypeDate => "0"
      case TypeString => "\"\""
    }
  }

  // C++-type specific string functions
  object Scala {
    
    def typeToString(t: Type) = t match {
      case TypeLong => "Long"
      case TypeDouble => "Double"
      case TypeDate => "Long"
      case TypeString => "String"
    }

    def typeToChar(t: Type) = t match {
      case TypeLong => 'L'
      case TypeDouble => 'D'
      case TypeDate => 'A'
      case TypeString => 'S'
    }

    def zeroOfType(t: Type) = t match {
      case TypeLong => "0L"
      case TypeDouble => "0.0"
      case TypeDate => "0"
      case TypeString => "\"\""
    }
  }

  def fromString(s: String, tp: Type) = tp match {
    case TypeLong => s.replaceAll("L$", "").toLong
    case TypeDouble => s.replaceAll("L$", "").toDouble
    case TypeString => s.replaceAll("^\"|\"$", "")
    case TypeDate => s.replaceAll("L$", "").toLong   // dateConv(v.toLong)
    case _ => scala.sys.error("Cannot convert " + s + " into " + tp)
  }
}