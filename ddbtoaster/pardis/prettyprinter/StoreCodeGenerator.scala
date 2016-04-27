package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.prettyprinter.ASTCodeGenerator
import ch.epfl.data.sc.pardis.utils.document.Document
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 27.04.16.
  */
trait StoreCodeGenerator extends ASTCodeGenerator[StoreDSL]{
  import IR._
  def emitSource4[T1, T2, T3, T4, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val body = reifyBlock(f(s1, s2, s3, s4))
    (className, List(s1, s2, s3, s4), body)
  }


  def emitSource6[T1, T2, T3, T4, T5, T6, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6))
    (className, List(s1, s2, s3, s4, s5, s6), body)
  }

  def emitSource8[T1, T2, T3, T4, T5, T6, T7, T8, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8))
    (className, List(s1, s2, s3, s4, s5, s6, s7, s8), body)
  }

  def emitSource11[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val s9 = fresh[T9]
    val s10 = fresh[T10]
    val s11 = fresh[T11]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11))
    (className, List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11), body)

  }

  def emitSource16[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11], Rep[T12], Rep[T13], Rep[T14], Rep[T15], Rep[T16]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], e12: TypeRep[T12], e13: TypeRep[T13], e14: TypeRep[T14], e15: TypeRep[T15], e16: TypeRep[T16], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val s9 = fresh[T9]
    val s10 = fresh[T10]
    val s11 = fresh[T11]
    val s12 = fresh[T12]
    val s13 = fresh[T13]
    val s14 = fresh[T14]
    val s15 = fresh[T15]
    val s16 = fresh[T16]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16))
    (className, List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16), body)
  }
  def blockToDocumentNoBraces(block: Block[_]): Document
}
