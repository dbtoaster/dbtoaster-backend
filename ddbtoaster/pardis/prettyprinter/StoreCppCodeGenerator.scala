package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.prettyprinter.CCodeGenerator
import ch.epfl.data.sc.pardis.utils.document._
import ddbt.lib.store.deep.StoreDSL


/**
  * Created by sachin on 28.04.16.
  */
class StoreCppCodeGenerator(override val IR: StoreDSL) extends CCodeGenerator with StoreCodeGenerator {

  import IR._


  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, StringFormat(self, _, Def(LiftedSeq(args)))) => doc"/* val $sym = $self.format(${args.map(expToDocument).mkDocument(",")}) */"

    case Statement(sym, ArrayApplyObject(Def(LiftedSeq(ops)))) => doc"/* SBJ */" :: tpeToDocument(sym.tp) :: expToDocument(sym) :: ops.map(expToDocument).mkDocument("= {", ",", "};")
    case Statement(sym, ArrayNew(size)) => tpeToDocument(sym.tp) :: " " :: expToDocument(sym) :: doc"[${expToDocument(size)}];"
    case Statement(sym, ArrayUpdate(self, i, x)) => doc"${expToDocument(self)}[${expToDocument(i)}] = ${expToDocument(x)};"


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

  override def nodeToDocument(node: PardisNode[_]): Document = node match {

    case StoreGetCopy(self, idx, key, _) => expToDocument(self) :: doc".getCopy(${expToDocument(idx)}, ${expToDocument(key)})"
    case StoreGet(self, idx, key) => expToDocument(self) :: doc".get(${expToDocument(idx)}, ${expToDocument(key)})"
    case StoreGetCopyDependent(self, idx, key) => expToDocument(self) :: doc".getCopyDependent(${expToDocument(idx)}, ${expToDocument(key)})"
    case StoreUpdateCopyDependent(self, key) => expToDocument(self) :: doc".updateCopyDependent(${expToDocument(key)})"
    case StoreUpdate(self, key) => expToDocument(self) :: doc".update(${expToDocument(key)})"
    case StoreUpdateCopy(self, key) => expToDocument(self) :: doc".updateCopy(${expToDocument(key)})"
    case StoreDeleteCopyDependent(self, key) => expToDocument(self) :: doc".deleteCopyDependent(${expToDocument(key)})"
    case StoreDeleteCopy(self, key) => expToDocument(self) :: doc".deleteCopy(${expToDocument(key)})"
    case StoreDelete1(self, key) => expToDocument(self) :: doc".del(${expToDocument(key)})"
    case StoreSlice(self, idx, key, f) => expToDocument(self) :: ".slice(" :: expToDocument(idx) :: ", " :: expToDocument(key) :: ", " :: expToDocument(f) :: ")"

    case IdxGet(self, key) => expToDocument(self) :: doc".get(${expToDocument(key)})"
    case IdxGetCopy(self, key) => expToDocument(self) :: doc".getCopy(${expToDocument(key)})"
    case IdxGetCopyDependent(self, key) => expToDocument(self) :: doc".getCopyDependent(${expToDocument(key)})"
    case IdxUpdateCopyDependent(self, key, _) => expToDocument(self) :: doc".updateCopyDependent(${expToDocument(key)})"
    case IdxUpdate(self, key) => expToDocument(self) :: doc".update(${expToDocument(key)})"
    case IdxUpdateCopy(self, key, _) => expToDocument(self) :: doc".updateCopy(${expToDocument(key)})"
    case IdxDeleteCopyDependent(self, key) => expToDocument(self) :: doc".deleteCopyDependent(${expToDocument(key)})"
    case IdxDeleteCopy(self, key, _) => expToDocument(self) :: doc".deleteCopy(${expToDocument(key)})"
    case IdxDelete(self, key) => expToDocument(self) :: doc".del(${expToDocument(key)});"
    case IdxSlice(self, key, f) => expToDocument(self) :: ".slice(" :: expToDocument(key) :: ", " :: expToDocument(f) :: ");"
    case PardisLambda(_, i, o) =>
      "[&](" :: tpeToDocument(i.tp) :: " " :: expToDocument(i) :: ") {" :: Document.nest(NEST_COUNT, blockToDocument(o)) :/: "}"
    case PardisLambda2(_, i1, i2, o) =>
      "[&](" :: tpeToDocument(i1.tp) :: " " :: expToDocument(i1) :: "," :: tpeToDocument(i2.tp) :: " " :: expToDocument(i2) :: ") {" :: Document.nest(NEST_COUNT, blockToDocument(o)) :/: "}"
    case _ => super.nodeToDocument(node)
  }
}
