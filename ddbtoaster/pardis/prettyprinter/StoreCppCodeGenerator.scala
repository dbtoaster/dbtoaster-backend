package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.ir.CTypes.{Pointer, PointerType}
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.prettyprinter.CCodeGenerator
import ch.epfl.data.sc.pardis.utils.document._
import ddbt.lib.store.deep.{StoreDSL, StringPrintf, StructFieldDecr, StructFieldIncr}
import ddbt.transformer.ScalaConstructsToCTranformer


/**
  * Created by sachin on 28.04.16.
  */
class StoreCppCodeGenerator(override val IR: StoreDSL) extends CCodeGenerator with StoreCodeGenerator {

  import IR._

  val refSymbols = collection.mutable.ArrayBuffer[Sym[_]]()

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, StringPrintf(Constant(size), f, Def(LiftedSeq(args)))) => doc"char* $sym = new char[${size + 1}];" :\\: doc"snprintf($sym, $size, $f, ${args.map(expToDocument).mkDocument(",")});"

    case Statement(sym, ArrayApplyObject(Def(LiftedSeq(ops)))) => doc"/* SBJ */" :: tpeToDocument(sym.tp) :: expToDocument(sym) :: ops.map(expToDocument).mkDocument("= {", ",", "};")
    case Statement(sym, ArrayNew(size)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: doc"[${expToDocument(size)}];"
    case Statement(sym, ArrayUpdate(self, i, Constant(rhs: String))) => (rhs.zipWithIndex.map(t => expToDocument(self) :: doc"[$i][${t._2}] = '" :: t._1.toString :: "\';") :+ (expToDocument(self) :: doc"[$i][${rhs.length}] = 0;")).mkDocument("\n")
    case Statement(sym, ArrayUpdate(self, i, x)) => doc"${expToDocument(self)}[${expToDocument(i)}] = ${expToDocument(x)};"

    case Statement(sym, ab@ArrayBufferNew2()) => "vector<" :: tpeToDocument(ab.typeA) :: "*> " :: symToDocument(sym) :: ";"
    case Statement(sym, ArrayBufferSortWith(self, f)) => "sort(" :: expToDocument(self) :: ".begin(), " :: expToDocument(self) :: ".end(), " :: expToDocument(f) :: ");"
    case Statement(sym, s@SetApplyObject2()) => "unordered_set<" :: tpeToDocument(s.typeT) :: "> " :: symToDocument(sym) :: ";"
    case Statement(sym, `Set+=`(self, elem)) => expToDocument(self) :: ".insert(" :: expToDocument(elem) :: ");"

    //    case Statement(sym, StoreGetCopy(self, idx, key, _)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: " = " :: expToDocument(self) :: doc".getCopy(${expToDocument(idx)}, ${expToDocument(key)});"
    //    case Statement(sym, StoreGet(self, idx, key)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: " = " :: expToDocument(self) :: doc".get(${expToDocument(idx)}, ${expToDocument(key)});"
    //    case Statement(sym, StoreGetCopyDependent(self, idx, key)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: " = " :: expToDocument(self) :: doc".getCopyDependent(${expToDocument(idx)}, ${expToDocument(key)});"
    //    case Statement(sym, StoreUpdateCopyDependent(self, key)) => expToDocument(self) :: doc".updateCopyDependent(${expToDocument(key)});"
    //    case Statement(sym, StoreUpdate(self, key)) => expToDocument(self) :: doc".update(${expToDocument(key)});"
    //    case Statement(sym, StoreUpdateCopy(self, key)) => expToDocument(self) :: doc".updateCopy(${expToDocument(key)});"
    //    case Statement(sym, StoreDeleteCopyDependent(self, key)) => expToDocument(self) :: doc".deleteCopyDependent(${expToDocument(key)});"
    //    case Statement(sym, StoreDeleteCopy(self, key)) => expToDocument(self) :: doc".deleteCopy(${expToDocument(key)});"
    //    case Statement(sym, StoreDelete1(self, key)) => expToDocument(self) :: doc".del(${expToDocument(key)});"
    //    case Statement(_, StoreSlice(self, idx, key, f)) => expToDocument(self) :: ".slice(" :: expToDocument(idx) :: ", " :: expToDocument(key) :: ", " :: expToDocument(f) :: ");"
    //
    //    case Statement(sym, IdxGet(self, key)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: " = " :: expToDocument(self) :: doc".get(${expToDocument(key)});"
    //    case Statement(sym, IdxGetCopy(self, key)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: " = " :: expToDocument(self) :: doc".getCopy(${expToDocument(key)});"
    //    case Statement(sym, IdxGetCopyDependent(self, key)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: " = " :: expToDocument(self) :: doc".getCopyDependent(${expToDocument(key)});"
    //    case Statement(sym, IdxUpdateCopyDependent(self, key, _)) => expToDocument(self) :: doc".updateCopyDependent(${expToDocument(key)});"
    //    case Statement(sym, IdxUpdate(self, key)) => expToDocument(self) :: doc".update(${expToDocument(key)});"
    //    case Statement(sym, IdxUpdateCopy(self, key, _)) => expToDocument(self) :: doc".updateCopy(${expToDocument(key)});"
    //    case Statement(sym, IdxDeleteCopyDependent(self, key)) => expToDocument(self) :: doc".deleteCopyDependent(${expToDocument(key)});"
    //    case Statement(sym, IdxDeleteCopy(self, key, _)) => expToDocument(self) :: doc".deleteCopy(${expToDocument(key)});"
    //    case Statement(sym, IdxDelete(self, key)) => expToDocument(self) :: doc".del(${expToDocument(key)});"
    //    case Statement(_, IdxSlice(self, key, f)) => expToDocument(self) :: ".slice(" :: expToDocument(key) :: ", " :: expToDocument(f) :: ");"

    case Statement(sym, StringDiff(str1, str2)) => "int " :: expToDocument(sym) :: doc" = strcmpi(${expToDocument(str1)}, ${expToDocument(str2)});"
    case _ => super.stmtToDocument(stmt)
  }

  override def expToDocument(exp: Expression[_]): Document = exp match {
    case c@Constant(null) if c.tp == DateType => "-1"
    case _ => super.expToDocument(exp)
  }

  override def nodeToDocument(node: PardisNode[_]): Document = node match {
    case StoreInsert(self, e) =>
      expToDocument(self) :: ".add(" :: expToDocument(e) :: ")"
    //    case StoreGetCopy(self, idx, key, _) => expToDocument(self) :: doc".getCopy(${expToDocument(idx)}, ${expToDocument(key)})"
    case StoreGet(self, idx, key) => expToDocument(self) :: doc".get(${expToDocument(key)})" //SBJ: Assumes idx 0
    //    case StoreGetCopyDependent(self, idx, key) => expToDocument(self) :: doc".getCopyDependent(${expToDocument(idx)}, ${expToDocument(key)})"
    //    case StoreUpdateCopyDependent(self, key) => expToDocument(self) :: doc".updateCopyDependent(${expToDocument(key)})"
    case StoreUpdate(self, key) => expToDocument(self) :: doc".update(${expToDocument(key)})" //SBJ: No update in c++
    //    case StoreUpdateCopy(self, key) => expToDocument(self) :: doc".updateCopy(${expToDocument(key)})"
    //    case StoreDeleteCopyDependent(self, key) => expToDocument(self) :: doc".deleteCopyDependent(${expToDocument(key)})"
    //    case StoreDeleteCopy(self, key) => expToDocument(self) :: doc".deleteCopy(${expToDocument(key)})"
    case StoreDelete1(self, key) => expToDocument(self) :: doc".del(${expToDocument(key)})"
    case StoreSlice(self, idx, key, f) => expToDocument(self) :: ".slice(" :: expToDocument(idx) :: ", " :: expToDocument(key) :: ", " :: expToDocument(f) :: ")"

    case IdxGet(self, key) => expToDocument(self) :: doc"->get(${expToDocument(key)})"
    //    case IdxGetCopy(self, key) => expToDocument(self) :: doc".getCopy(${expToDocument(key)})"
    //    case IdxGetCopyDependent(self, key) => expToDocument(self) :: doc".getCopyDependent(${expToDocument(key)})"
    //    case IdxUpdateCopyDependent(self, key, _) => expToDocument(self) :: doc".updateCopyDependent(${expToDocument(key)})"
    case IdxUpdate(self, key) => expToDocument(self) :: doc"->update(${expToDocument(key)})" //SBJ: No update in C++
    //    case IdxUpdateCopy(self, key, _) => expToDocument(self) :: doc".updateCopy(${expToDocument(key)})"
    //    case IdxDeleteCopyDependent(self, key) => expToDocument(self) :: doc".deleteCopyDependent(${expToDocument(key)})"
    //    case IdxDeleteCopy(self, key, _) => expToDocument(self) :: doc".deleteCopy(${expToDocument(key)})"
    case IdxDelete(self, key) => expToDocument(self) :: doc"->del(${expToDocument(key)});"
    case IdxSlice(self, key, f) => expToDocument(self) :: "->slice(" :: expToDocument(key) :: ", " :: expToDocument(f) :: ");"

    case ArrayBufferAppend(self, elem) => expToDocument(self) :: ".push_back(" :: expToDocument(elem) :: ")"
    case ArrayBufferApply(Def(ArrayBufferSortWith(self, _)), i) => expToDocument(self) :: "[" :: expToDocument(i) :: "]"
    case ArrayBufferApply(self, i) => expToDocument(self) :: "[" :: expToDocument(i) :: "]"
    case ArrayBufferSize(self) => expToDocument(self) :: ".size()"

    case SetSize(self) => expToDocument(self) :: ".size()"

    case ArrayApply(self, i) => expToDocument(self) :: "[" :: expToDocument(i) :: "]"

    case StructFieldSetter(self: Sym[_], idx, rhs) if refSymbols.contains(self) => expToDocument(self) :: "." :: idx :: " = " :: expToDocument(rhs)
    case StructFieldGetter(self: Sym[_], idx) if refSymbols.contains(self) => expToDocument(self) :: "." :: idx
    case StructFieldIncr(self, idx, rhs) if refSymbols.contains(self) => expToDocument(self) :: "." :: idx :: " += " :: expToDocument(rhs)
    case StructFieldDecr(self, idx, rhs) if refSymbols.contains(self) => expToDocument(self) :: "." :: idx :: " -= " :: expToDocument(rhs)
    case StructFieldIncr(self, idx, rhs) => expToDocument(self) :: "->" :: idx :: " += " :: expToDocument(rhs)
    case StructFieldDecr(self, idx, rhs) => expToDocument(self) :: "->" :: idx :: " -= " :: expToDocument(rhs)

    case PardisLambda(_, i, o) =>
      val tp = i.tp.typeArguments match {
        case content :: tail => content
        case Nil => i.tp
      }
      val refToPtr = tpeToDocument(i.tp) :: " " :: expToDocument(i) :: " = const_cast < " :: tpeToDocument(i.tp) :: ">(&sliceVar);"
      "[&](const " :: tpeToDocument(tp) :: "&  sliceVar) {" :/: Document.nest(NEST_COUNT, refToPtr :: blockToDocument(o) :/: getBlockResult(o, true)) :/: "}"
    case PardisLambda2(_, i1, i2, o) =>
      refSymbols ++= List(i1, i2).map(_.asInstanceOf[Sym[_]])
      val t1 = i1.tp.typeArguments match {
        case content :: tail => content
        case Nil => i1.tp
      }
      val t2 = i2.tp.typeArguments match {
        case content :: tail => content
        case Nil => i2.tp
      }
      "[&](" :: tpeToDocument(t1) :: " & " :: expToDocument(i1) :: ", " :: tpeToDocument(t2) :: " & " :: expToDocument(i2) :: ") {" :/: Document.nest(NEST_COUNT, blockToDocument(o) :/: getBlockResult(o, true)) :/: "}"
    case BooleanExtraConditionalObject(cond, ift, iff) => doc"${expToDocument(cond)} ? ${expToDocument(ift)} : ${expToDocument(iff)}"
    case `Int>>>1`(self, x) => doc"$self >> ($x & (sizeof($self)-1))"
    case EntryIdxApplyObject(Def(h: PardisLambda[_, _]), Def(c: PardisLambda2[_, _, _]), Constant(name)) =>
      refSymbols ++= List(h.i, c.i1, c.i2).map(_.asInstanceOf[Sym[_]])
      val t = new ScalaConstructsToCTranformer(IR, false)
      val ho = t(IR)(h.o)(h.o.typeT)
      val co = t(IR)(c.o)(c.o.typeT)

      doc" struct $name {" :/: Document.nest(NEST_COUNT,
        doc"FORCE_INLINE static size_t hash(const " :: tpeToDocument(h.i.tp) :: "& " :: expToDocument(h.i) :: ")  { " :: Document.nest(NEST_COUNT, blockToDocument(ho) :/: getBlockResult(ho, true)) :/: "}" :\\:
          doc"FORCE_INLINE static bool equals(const " :: tpeToDocument(c.i1.tp) :: "& " :: expToDocument(c.i1) :: ", const " :: tpeToDocument(c.i2.tp) :: "& " :: expToDocument(c.i2) :: ") { " :: Document.nest(NEST_COUNT, blockToDocument(co) :/: getBlockResult(co, true)) :/: "}") :/: "};"
    case HashCode(a) => doc"HASH(${expToDocument(a)})"
    case _ => super.nodeToDocument(node)
  }
}
