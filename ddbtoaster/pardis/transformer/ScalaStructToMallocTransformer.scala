package ddbt.transformer
import ch.epfl.data.sc.pardis.annotations.typeRep
import ch.epfl.data.sc.pardis.deep.scalalib.collection.TreeSetIRs.TreeSetType
import ch.epfl.data.sc.pardis.ir.{PardisCast, PardisLambdaDef, PardisStruct, PardisStructArg}
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ch.epfl.data.sc.pardis.types.{OptionType, PardisType}
import ddbt.lib.store.deep.StoreDSL

import scala.language.existentials

/**
  * Transforms `new Struct` in Scala to `malloc(..)` in C.
  *
  * @param IR the polymorphic embedding trait which contains the reified program.
  */
class ScalaStructToMallocTransformer(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) with CTransformer {
  import IR._
  import ch.epfl.data.sc.pardis.ir.CNodes._
  import ch.epfl.data.sc.pardis.ir.CTypes._


  override def transformType[T: PardisType]: PardisType[Any] = {
    val tp = implicitly[PardisType[T]]
    tp match {
      case c if c.isPrimitive   => super.transformType[T]
//      case ArrayBufferType(args) => typePointer(typeGArray)
//      // case ArrayType(x) if x == ByteType => typePointer(ByteType)
//      // case ArrayType(args) => typePointer(typeCArray({
//      //   if (args.isArray) typeCArray(args)
//      //   else args
//      // }))
//      case ArrayType(args)       => typePointer(args)
       case c if c.isRecord => tp.typeArguments match {
         case Nil     => typePointer(tp)
         case List(t) => typePointer(transformType(t))
       }
      case GenericEntryType | EntryType => typePointer(tp)

//      case TreeSetType(args)     => typePointer(typeGTree)
      case OptionType(args)      => typePointer(transformType(args))
      case _                     => super.transformType[T]
    }
  }.asInstanceOf[PardisType[Any]]

//  rewrite += rule {
//    case pc @ PardisCast(x) => PardisCast(apply(x))(apply(pc.castFrom), apply(pc.castTp))
//  }

  rewrite += rule {
    case s @ PardisStruct(tag, elems, methods) =>
      // TODO if needed method generation should be added
      val x = toAtom(Malloc(unit(1))(s.tp))(typePointer(s.tp))
      val newElems = elems.map(el => PardisStructArg(el.name, el.mutable, transformExp(el.init)(el.init.tp, apply(el.init.tp))))
      implicit  val tp = s.tp
      structCopy(x, toAtom(PardisStruct(tag, newElems, methods.map(m => m.copy(body =
        transformDef(m.body.asInstanceOf[Def[Any]]).asInstanceOf[PardisLambdaDef])))))
      x
  }
}