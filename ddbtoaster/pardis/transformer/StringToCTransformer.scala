package ddbt.transformer

import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.lib.store.deep.StoreDSL

/**
  * Transforms (Optimal)String objects to their corresponding C implementation.
  *
  * @param IR the polymorphic embedding trait which contains the reified program.
  */
class StringToCTransformer(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) with CTransformer {

  import IR._
  import ch.epfl.data.sc.pardis.ir.CNodes._
  import ch.epfl.data.sc.pardis.ir.CTypes._

  def super_optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val analyseProgram = classOf[RuleBasedTransformer[StoreDSL]].getDeclaredMethod("analyseProgram", classOf[Block[T]], classOf[TypeRep[T]])
    analyseProgram.setAccessible(true)
    val isDone = classOf[RecursiveRuleBasedTransformer[StoreDSL]].getDeclaredField("isDone")
    isDone.setAccessible(true)
    var currentBlock = node
    var counter = 0
    while (isDone.get(this) == false && counter < THRESHOLD) {

      analyseProgram.invoke(this, currentBlock, implicitly[TypeRep[T]])
      postAnalyseProgram(currentBlock)
      isDone.set(this, true)
      currentBlock = transformProgram(currentBlock)
      counter += 1
    }
    if (counter >= THRESHOLD) {
      System.err.println(s"Recursive transformer ${getName} is not converted yet after [${scala.Console.RED}$counter${scala.Console.RESET}] rounds")
    }
    currentBlock
  }

  override def optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val res = super_optimize(node)
    ruleApplied()
    res
  }

  private[StringToCTransformer] implicit def StringToCharPointer(x: Rep[String]) = x.asInstanceOf[Rep[Pointer[Char]]]

  implicit class StringRep(self: Rep[String]) {
    def getBaseValue(s: Rep[String]): Rep[Pointer[Char]] = apply(s).asInstanceOf[Rep[Pointer[Char]]]
  }

  //  rewrite += rule { case StringNew(self) => self }
  //  rewrite += rule {
  //    case StringString(self) =>
  //      new StringRep(self).getBaseValue(self)
  //  }
  //  rewrite += rule {
  //    case StringDiff(self, y) =>
  //      CString.strcmp(new StringRep(self).getBaseValue(self), new StringRep(self).getBaseValue(y))
  //  }
  //  rewrite += rule {
  //    case StringEndsWith(self, y) => {
  //      val lenx: Rep[ch.epfl.data.sc.cscala.CLangTypes.CSize] = CString.strlen(new StringRep(self).getBaseValue(self));
  //      val leny: Rep[ch.epfl.data.sc.cscala.CLangTypes.CSize] = CString.strlen(new StringRep(self).getBaseValue(y));
  //      val len: Rep[Int] = lenx.$minus(leny);
  //      infix_$eq$eq(CString.strncmp(CLang.pointer_add[Char](new StringRep(self).getBaseValue(self), len)(typeRep[Char], CLangTypes.charType), new StringRep(self).getBaseValue(y), len), unit(0))
  //    }
  //  }
  //  rewrite += rule {
  //    case StringStartsWith(self, y) =>
  //      infix_$eq$eq(CString.strncmp(new StringRep(self).getBaseValue(self), new StringRep(self).getBaseValue(y), CString.strlen(new StringRep(self).getBaseValue(y))), unit(0))
  //  }
  //  rewrite += rule {
  //    case StringCompare(self, y) =>
  //      CString.strcmp(new StringRep(self).getBaseValue(self), new StringRep(self).getBaseValue(y))
  //  }
  //  rewrite += rule { case StringCompare(x, y) => strcmp(x, y) }
  //  rewrite += rule { case StringCompare(x, y) => strcmp(x, y) }
  rewrite += rule { case StringLength(x) => strlen(x) }
  //  rewrite += rule { case String$eq$eq$eq(x, y) => strcmp(x, y) __== unit(0) }
  //  rewrite += rule { case String$eq$bang$eq(x, y) => infix_!=(strcmp(x, y), unit(0)) }
  rewrite += rule { case StringContains(x, y) => infix_!=(strstr(x, y), unit(null)) }
  //  rewrite += rule {
  //    case StringLength(self) =>
  //      CString.strlen(new StringRep(self).getBaseValue(self))
  //  }
  //  rewrite += rule {
  //    case String$eq$eq$eq(self, y) =>
  //      infix_$eq$eq(CString.strcmp(new StringRep(self).getBaseValue(self), new StringRep(self).getBaseValue(y)), unit(0))
  //  }
  //  rewrite += rule {
  //    case String$eq$bang$eq(self, y) =>
  //      infix_$bang$eq(CString.strcmp(new StringRep(self).getBaseValue(self), new StringRep(self).getBaseValue(y)), unit(0))
  //  }
  //  rewrite += rule {
  //    case StringContainsSlice(self, y) =>
  //      infix_$bang$eq(CString.strstr(new StringRep(self).getBaseValue(self), new StringRep(self).getBaseValue(y)), CLang.NULL[Char])
  //  }
  //  rewrite += rule {
  //    case StringIndexOfSlice(self, y, idx) => {
  //      val substr: Rep[ch.epfl.data.sc.cscala.CLangTypes.Pointer[Char]] = CString.strstr(CLang.pointer_add[Char](new StringRep(self).getBaseValue(self), idx)(typeRep[Char], CLangTypes.charType), new StringRep(self).getBaseValue(y));
  //      __ifThenElse(infix_$eq$eq(substr, CLang.NULL[Char]), unit(-1), CString.str_subtract(substr, new StringRep(self).getBaseValue(self)))
  //    }
  //  }
  //  rewrite += rule {
  //    case StringApply(self, idx) =>
  //      CLang.*(CLang.pointer_add[Char](new StringRep(self).getBaseValue(self), idx)(typeRep[Char], CLangTypes.charType))
  //  }
  //  rewrite += rule {
  //    case StringSlice(self, start, end) => {
  //      val len: Rep[Int] = end.$minus(start).$plus(unit(1));
  //      //FIXME CStdLib.malloc should be generated in a proper way
  //      val newbuf: Rep[ch.epfl.data.sc.cscala.CLangTypes.Pointer[Char]] = CStdLib.malloc[Char](len);
  //      CString.strncpy(newbuf, CLang.pointer_add[Char](new StringRep(self).getBaseValue(self), start)(typeRep[Char], CLangTypes.charType), len.$minus(unit(1)));
  //      pointer_assign_content(newbuf.asInstanceOf[Expression[Pointer[Any]]], len - unit(1), unit('\u0000'))
  //      newbuf
  //    }
  //  }
  //  rewrite += rule {
  //    case StringReverse(x) =>
  //      val len: Rep[Int] = strlen(apply(x)) + unit(1)
  //      val newbuf: Rep[ch.epfl.data.sc.cscala.CLangTypes.Pointer[Char]] = CStdLib.malloc[Char](len);
  //      CString.strncpy(newbuf, new StringRep(x).getBaseValue(x), len.$minus(unit(1)));
  //      pointer_assign_content(newbuf.asInstanceOf[Expression[Pointer[Any]]], len - unit(1), unit('\u0000'))
  //
  //      val str = infix_asInstanceOf(newbuf)(typeArray(typePointer(CharType))).asInstanceOf[Rep[Array[Pointer[Char]]]]
  //      val i = __newVar[Int](unit(0))
  //      val j = __newVar[Int](strlen(str) - unit(1))
  //
  //      __whileDo((i: Rep[Int]) < (j: Rep[Int]), {
  //        val _i = (i: Rep[Int])
  //        val _j = (j: Rep[Int])
  //        val temp = str(_i)
  //        str(_i) = str(_j)
  //        str(_j) = temp
  //        __assign(i, _i + unit(1))
  //        __assign(j, _j - unit(1))
  //      })
  //      str
  //  }
  //  // FIXME should not use NameAlias
  //  rewrite += rule {
  //    case StringSplit(str, delim) =>
  //      NameAlias[Pointer[Char]](None, "tokenizeString", List(List(str)))
  //  }
}