package org.dbtoaster.dbtoasterlib {
  object K3Tuple {
    sealed trait K3Tuple {
      def toList: List[Any]
      def append[V](v: V): K3Tuple
    }

    final case class K3TupleCons[H, T <: K3Tuple](head: H, tail: T) 
            extends K3Tuple {
      def :+:[H](v: H) = K3TupleCons(v, this)
      def append[V](v: V): K3Tuple = K3TupleCons(head, tail.append(v))

      override def toString = {
        def strList(ls: K3Tuple): String = ls match {
          case x :+: K3TNil => x.toString
          case x :+: xs => x + ", " + strList(xs)
          case _ => ""
        }
        "(" + strList(this) + ")"
      }

      def toList: List[Any] = head :: tail.toList
    }

    final case object K3TupleNil extends K3Tuple {
      def :+:[H](v: H) = K3TupleCons(v, this)
      def append[V](v: V): K3TupleCons[V, K3TupleNil.type] = 
        K3TupleCons(v, K3TupleNil)

      def toList: List[Any] = List[Any]()

      override def toString = "()"
    }

    type :+:[H, T <: K3Tuple] = K3TupleCons[H, T]
    val :+: = K3TupleCons
    val K3TNil = K3TupleNil
  }
}