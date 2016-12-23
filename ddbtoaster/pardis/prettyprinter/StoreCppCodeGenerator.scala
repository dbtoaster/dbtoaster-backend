package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.ir.CNodes.StrStr
import ch.epfl.data.sc.pardis.ir.CTypes.PointerType
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.prettyprinter.CCodeGenerator
import ch.epfl.data.sc.pardis.types.{ArrayType, PardisVariableType, SeqType, UnitType}
import ch.epfl.data.sc.pardis.utils.document._
import ddbt.lib.store.IHash
import ddbt.lib.store.deep.{StoreDSL, StructFieldDecr, StructFieldIncr}
import ddbt.transformer.{Index, IndexesFlag, ScalaConstructsToCTranformer}


/**
  * Created by sachin on 28.04.16.
  */
class StoreCppCodeGenerator(override val IR: StoreDSL) extends CCodeGenerator with StoreCodeGenerator {

  import IR._

  val refSymbols = collection.mutable.ArrayBuffer[Sym[_]]()

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, StringExtraStringPrintfObject(Constant(size), f, Def(LiftedSeq(args)))) =>
      def ArgToDoc(arg: Rep[_]) = arg.tp match {
        case StringType => doc"$arg.data_"
        case DateType => doc"IntToStrdate($arg)"
        case _ => doc"$arg"
      }
      doc"PString $sym($size);" :\\: doc"snprintf($sym.data_, ${size + 1}, $f, ${args.map(ArgToDoc).mkDocument(", ")});"
    case Statement(sym, StrStr(x, y)) => doc"char* ${sym} = strstr($x.data_, $y);"

    case Statement(sym, ab@ArrayApplyObject(_)) if ab.typeT.isInstanceOf[EntryIdxType[_]] => Document.empty
    case Statement(sym, ab@ArrayApplyObject(Def(LiftedSeq(ops)))) => doc"${sym.tp} $sym = { ${ops.mkDocument(",")} };"
    case Statement(sym, ArrayNew(size)) => doc"${sym.tp.asInstanceOf[ArrayType[_]].elementType} $sym[$size];"
//    case Statement(sym, ArrayUpdate(self, i, r@Constant(rhs: String))) => doc"strcpy($self[$i], $r);"
    case Statement(sym, ArrayUpdate(self, i, x)) => doc"$self[$i] = $x;"

    case Statement(sym, ab@ArrayBufferNew2()) => doc"vector<${ab.typeA}*> $sym;"
    case Statement(sym, ArrayBufferSortWith(self, f)) => doc"sort($self.begin(), $self.end(), $f);"
    case Statement(sym, s@SetApplyObject2()) => doc"unordered_set<${s.typeT}> $sym;"
    case Statement(sym, `Set+=`(self, elem)) => doc"$self.insert($elem);"

    case Statement(sym, StoreNew3(_, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) =>
      val entryTp = sym.tp.asInstanceOf[StoreType[_]].typeE.asInstanceOf[PointerType[_]].contentsType
      val names = ops.collect {
        case Def(EntryIdxApplyObject(_, _, Constant(name))) => name
      }
      val idxes = sym.attributes.get(IndexesFlag).get.indexes
      def idxToDoc(t: (Index, String)) = t._1.tp match {
        case IHash => doc"HashIndex<$entryTp, char, ${t._2}, ${if (t._1.unique) "1" else "0"}>"
      }
      val idxTypeDefs = idxes.zip(names).map(t => doc"typedef ${idxToDoc(t)} ${sym}_Idx_${t._1.idxNum}_Type;").mkDocument("\n")
      idxTypeDefs :/:
        doc"MultiHashMap<$entryTp, char," :: idxes.map(i => doc"${sym}_Idx_${i.idxNum}_Type").mkDocument(", ") :: doc"> $sym;"

    case Statement(sym, StoreIndex(self, idxNum, _, _, _)) => doc"${self}_Idx_${idxNum}_Type& $sym = * (${self}_Idx_${idxNum}_Type *)$self.index[$idxNum];"
    case _ => super.stmtToDocument(stmt)
  }

  override def symToDocument(sym: ExpressionSymbol[_]): Document = if (sym.tp == UnitType)
    doc"()"
  else {
    if (sym.name != "x" && sym.name != "ite") {
      Document.text(sym.name.stripSuffix("_$"))
    } else {
      super.symToDocument(sym)
    }
  }

  override def expToDocument(exp: Expression[_]): Document = exp match {
    case Constant(null) if exp.tp == DateType => "0"
    case Constant(null) if exp.tp == StringType => "PString()"
    case _ => super.expToDocument(exp)
  }

  override def tpeToDocument[T](tp: TypeRep[T]): Document = tp match {
    case StringType => "PString"
    case DateType => "date"
    case IR.ArrayType(atp) => doc"$atp*"
    case PardisVariableType(vtp) => tpeToDocument(vtp)
    case _ => super.tpeToDocument(tp)
  }

  override def nodeToDocument(node: PardisNode[_]): Document = node match {
//    case ToString(a) if a.tp == DateType => doc"IntToStrDate($a)"
    case StringSubstring2(self, pos, len) => doc"$self.substr($pos, $len)" //Different from scala substring
    case StringExtraStringCompareObject(str1, str2) => doc"strcmpi($str1.data_, $str2.data_)"


    case StoreInsert(self, e) => doc"$self.add($e)"
    case StoreUnsafeInsert(self, idx, e) => doc"$self.insert_nocheck(*$e)" //ignoring idx for now
    case StoreGet(self, idx, key) if refSymbols.contains(key) => doc"$self.get($key)" //SBJ: Assumes idx 0
    case StoreGet(self, idx, key) => doc"$self.get(*$key)" //SBJ: Assumes idx 0
    case StoreUpdate(self, key) => doc"$self.update($key)" //SBJ: No update in c++. All cases of updates in current benchmark should be removed by DeadIdxUpdate
    case StoreDelete1(self, key) => doc"$self.del($key)"
    case StoreSlice(self, idx, key, f) => doc"$self.slice($idx, $key, $f)"
    case StoreForeach(self, f) => doc"$self.foreach($f)"
    case StoreClear(self) => doc"$self.clear()"

    case IdxGet(self, key) if refSymbols.contains(key) => doc"$self.get($key)"
    case IdxGet(self, key) => doc"$self.get(*$key)"
    case IdxUpdate(self, key) => doc"$self.update($key)" //SBJ: No update in C++
    case IdxDelete(self, key) => doc"$self.del($key)"
    case IdxSlice(self, key, f) => doc"$self.slice($key, $f)"
    case IdxForeach(self, f) => doc"$self.foreach($f)"
    case IdxClear(self) => doc"$self.clear()"

    case ArrayBufferAppend(self, elem) => doc"$self.push_back($elem)"
    case ArrayBufferApply(Def(ArrayBufferSortWith(self, _)), i) => doc"$self[$i]"
    case ArrayBufferApply(self, i) => doc"$self[$i]"
    case ArrayBufferSize(self) => doc"$self.size()"

    case SetSize(self) => doc"$self.size()"

    case ArrayApply(self, i) => doc"$self[$i]"

    case StructFieldSetter(self: Sym[_], idx, rhs) if refSymbols.contains(self) => doc"$self.$idx = $rhs"
    case StructFieldGetter(self: Sym[_], idx) if refSymbols.contains(self) => doc"$self.$idx"
    case StructFieldIncr(self, idx, rhs) if refSymbols.contains(self) => doc"$self.$idx += $rhs"
    case StructFieldDecr(self, idx, rhs) if refSymbols.contains(self) => doc"$self.$idx -= $rhs"
    case StructFieldIncr(self, idx, rhs) => doc"$self->$idx += $rhs"
    case StructFieldDecr(self, idx, rhs) => doc"$self->$idx -= $rhs"

    case LiftedSeq(ops) if node.tp.isInstanceOf[SeqType[EntryIdx[_]]] => Document.empty
    case PardisLambda(_, i, o) =>
      val tp = i.tp.typeArguments match {
        case content :: tail => content
        case Nil => i.tp
      }
      val refToPtr = doc"${i.tp} $i = const_cast<${i.tp}>(&sliceVar);"
      doc"[&](const $tp&  sliceVar) {" :/: Document.nest(NEST_COUNT, refToPtr :: blockToDocument(o) :/: getBlockResult(o, true)) :/: "}"

    //    case PardisLambda2(_, i1, i2, o) if refSymbols.contains(i1) =>
    //      val t1 = i1.tp.typeArguments match {
    //        case content :: tail => content
    //        case Nil => i1.tp
    //      }
    //      val t2 = i2.tp.typeArguments match {
    //        case content :: tail => content
    //        case Nil => i2.tp
    //      }
    //      "[&](" :: tpeToDocument(t1) :: " & " :: expToDocument(i1) :: ", " :: tpeToDocument(t2) :: " & " :: expToDocument(i2) :: ") {" :/: Document.nest(NEST_COUNT, blockToDocument(o) :/: getBlockResult(o, true)) :/: "}"
    //
    case PardisLambda2(_, i1, i2, o) =>
      doc"[&](${i1.tp} $i1, ${i2.tp} $i2) {" :/: Document.nest(NEST_COUNT, blockToDocument(o) :/: getBlockResult(o, true)) :/: "}"

    case BooleanExtraConditionalObject(cond, ift, iff) => doc"$cond ? $ift : $iff"

    case `Int>>>1`(self, x) => doc"$self >> ($x & (8*sizeof($self)-1))"
    //    case Equal(a, b) if a.tp == StringType => //doc"!strcmpi($a, $b)"
    case EntryIdxApplyObject(Def(h: PardisLambda[_, _]), Def(c: PardisLambda2[_, _, _]), Constant(name)) =>
      refSymbols ++= List(h.i, c.i1, c.i2).map(_.asInstanceOf[Sym[_]])
      val t = new ScalaConstructsToCTranformer(IR, false)
      val ho = t(IR)(h.o)(h.o.typeT)
      val co = t(IR)(c.o)(c.o.typeT)

      doc" struct $name {" :/: Document.nest(NEST_COUNT,
        doc"FORCE_INLINE static size_t hash(const ${h.i.tp}& ${h.i})  { " :: Document.nest(NEST_COUNT, blockToDocument(ho) :/: getBlockResult(ho, true)) :/: "}" :\\:
          doc"FORCE_INLINE static char cmp(const ${c.i1.tp}& ${c.i1}, const ${c.i2.tp}& ${c.i2}) { " :: Document.nest(NEST_COUNT, blockToDocument(co) :/: getBlockResult(co, true)) :/: "}") :/: "};"

    case HashCode(a) => doc"HASH($a)"
    case _ => super.nodeToDocument(node)
  }
}
