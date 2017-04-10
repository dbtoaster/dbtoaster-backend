package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.ir.CNodes.{Malloc, StrStr, StructCopy}
import ch.epfl.data.sc.pardis.ir.CTypes.PointerType
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.prettyprinter.CCodeGenerator
import ch.epfl.data.sc.pardis.types._
import ch.epfl.data.sc.pardis.utils.document._
import ddbt.codegen.Optimizer
import ddbt.lib.store.{IHash, IList}
import ddbt.lib.store.deep.{ProfileEnd, ProfileStart, StoreDSL, StructDynamicFieldAccess, StructFieldDecr, StructFieldIncr}
import ddbt.transformer.{Index, IndexesFlag, ScalaConstructsToCTranformer}
import sun.security.x509.CRLDistributionPointsExtension


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

    case Statement(sym, EntryIdxGenericCmpObject(_, _)) => Document.empty
    case Statement(sym, EntryIdxGenericOpsObject(_)) => Document.empty
    case Statement(sym, EntryIdxGenericFixedRangeOpsObject(_)) => Document.empty
    case Statement(sym, ab@ArrayApplyObject(_)) if ab.typeT.isInstanceOf[EntryIdxType[_]] => Document.empty

    case Statement(sym, ab@ArrayApplyObject(Def(LiftedSeq(ops)))) => doc"${sym.tp} $sym = { ${ops.mkDocument(",")} };"
    case Statement(sym, ArrayNew(size)) => doc"${sym.tp.asInstanceOf[ArrayType[_]].elementType} $sym[$size];"
    case Statement(sym, ArrayUpdate(self, i, r@Constant(rhs: String))) if rhs.length == 1 => doc"""$self[$i].data_[0] = '$rhs';"""
    case Statement(sym, ArrayUpdate(self, i, r@Constant(rhs: String))) => doc"strcpy($self[$i].data_, $r);"
    case Statement(sym, ArrayUpdate(self, i, x)) => doc"$self[$i] = $x;"
    case Statement(sym, a@ArrayApply(self, i)) if a.typeT == StringType => doc"PString& $sym = $self[$i];"

    case Statement(sym, ab@ArrayBufferNew2()) => doc"vector<${ab.typeA}*> $sym;"
    case Statement(sym, ArrayBufferSortWith(self, f)) => doc"sort($self.begin(), $self.end(), $f);"

    case Statement(sym, s@SetApplyObject1(Def(PardisLiftedSeq(es)))) => doc"unordered_set<${s.typeT}> $sym(${es.mkDocument("{", ", ", "}")}); //setApply1"
    case Statement(sym, s@SetApplyObject2()) => doc"unordered_set<${s.typeT}> $sym; //setApply2"
    case Statement(sym, `Set+=`(self, elem)) => doc"$self.insert($elem);"

    case Statement(sym, v@PardisNewVar(Constant(0))) if v.typeT == StringType => doc"${sym.tp} $sym;"

    case Statement(sym, agg@AggregatorMaxObject(f)) =>
      doc"${agg.typeE}* ${sym}result = nullptr;" :/:
        doc"MaxAggregator<${agg.typeE}, ${agg.typeR}> $sym($f, &${sym}result);"
    case Statement(sym, agg@AggregatorMinObject(f)) =>
      doc"${agg.typeE}* ${sym}result = nullptr;" :/:
        doc"MinAggregator<${agg.typeE}, ${agg.typeR}> $sym($f, &${sym}result);"
    case Statement(sym, agg@AggregatorMedianObject(f)) =>
      doc"std::vector<${agg.typeE}*> ${sym}results;" :/:
        doc"MedianAggregator<${agg.typeE}, ${agg.typeR}> $sym($f, ${sym}results);"

    case Statement(sym, StoreNew3(_, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) =>
      val entryTp = sym.tp.asInstanceOf[StoreType[_]].typeE match {
        case PointerType(tp) => tp
        case tp => tp
      }

      val names = ops.collect {
        //TODO: COMMON part. Move.
        case Def(EntryIdxApplyObject(_, _, Constant(name))) => name
        case Def(n: EntryIdxGenericOpsObject) =>
          val cols = n.cols.asInstanceOf[Constant[List[Int]]].underlying.mkString("")
          if (cols.isEmpty)
            s"GenericOps"
          else {
            s"GenericOps_$cols"
          }
        case Def(n: EntryIdxGenericCmpObject[_]) =>
          val ord = Index.getColumnNumFromLambda(Def.unapply(n.f).get.asInstanceOf[PardisLambda[_, _]])
          val cols = n.cols.asInstanceOf[Constant[List[Int]]].underlying.mkString("")
          s"GenericCmp_${cols.mkString("")}_$ord"

        case Def(n: EntryIdxGenericFixedRangeOpsObject) =>
          val cols = n.colsRange.asInstanceOf[Constant[List[(Int, Int, Int)]]].underlying.map(t => s"${t._1}f${t._2}t${t._3}").mkString("_")
          s"GenericFixedRange_$cols"

      }
      val idxes = sym.attributes.get(IndexesFlag).get.indexes
      def idxToDoc(t: (Index, String)) = t._1.tp match {
        case IHash => doc"HashIndex<$entryTp, char, ${t._2}, ${if (t._1.unique) "1" else "0"}>"
        case IList => doc"ListIndex<$entryTp, char, ${t._2},  ${if (t._1.unique) "1" else "0"}>"
      }
      val initSize = if (Optimizer.initialStoreSize) doc"(${sym}ArrayLengths, ${sym}PoolSizes);" else doc";"
      val idxTypeDefs = idxes.zip(names).map(t => doc"typedef ${idxToDoc(t)} ${sym}_Idx_${t._1.idxNum}_Type;").mkDocument("\n")
      idxTypeDefs :/:
        doc"MultiHashMap<$entryTp, char," :: idxes.map(i => doc"${sym}_Idx_${i.idxNum}_Type").mkDocument(", ") :: doc"> $sym$initSize"

    case Statement(sym, StoreIndex(self, idxNum, _, _, _)) => doc"${self}_Idx_${idxNum}_Type& $sym = * (${self}_Idx_${idxNum}_Type *)$self.index[$idxNum];"


    case Statement(sym, IdxSliceRes(idx@Def(StoreIndex(self, idxNum, _, _, _)), key)) if Optimizer.sliceInline =>
      val h = "h" + sym.id
      val IDX_FN = "IDXFN" + sym.id

      doc"//sliceRes " :\\:
        doc"typedef typename ${self}Idx${idxNum}Type::IFN $IDX_FN;" :\\:
        doc"HASH_RES_t $h = $IDX_FN::hash($key);" :\\:
        doc"auto* $sym = &($idx.buckets_[$h % $idx.size_]);" :\\:
        doc"if($sym -> head.obj) {" :\\:
        doc"   do {" :\\:
        doc"     if($h == $sym->hash && !$IDX_FN::cmp($key, *$sym->head.obj))" :\\:
        doc"       break;" :\\:
        doc"   } while(($sym = $sym->nxt));" :\\:
        doc"} else { " :\\:
        doc"   $sym = nullptr;" :\\:
        doc"}"

    case Statement(sym, IdxSliceRes(idx, key)) => doc"auto* $sym = $idx.sliceRes($key);"

    case Statement(sym, IdxSliceResMap(idx@Def(StoreIndex(self, idxNum, _, _, _)), key, Def(PardisLambda(_, i, o)), res: Sym[_])) if Optimizer.sliceInline =>
      val h = "h" + res.id
      val IDX_FN = "IDXFN" + res.id

      val pre = doc"//sliceResMap " :\\:
        doc"auto* n$res = &$res->head;" :\\:
        doc"std::vector<${i.tp}> entVector$res;" :\\:
        doc"do entVector$res.push_back(n$res->obj); while((n$res = n$res->nxt));" :\\:
        doc"for(auto $i: entVector$res) {"
      val post = doc"}"
      pre :: Document.nest(2, blockToDocument(o)) :/: post

    case Statement(sym, IdxSliceResMapNoUpd(idx@Def(StoreIndex(self, idxNum, _, _, _)), key, Def(PardisLambda(_, i, o)), res: Sym[_])) if Optimizer.sliceInline =>
      val h = "h" + res.id
      val IDX_FN = "IDXFN" + res.id

      val pre = doc"//sliceResMapNoUpd " :\\:
        doc"auto* n$res = &$res->head;" :\\:
        doc"do {" :\\:
        doc"  auto $i = n$res->obj;"
      val post = doc"} while((n$res = n$res->nxt));"
      pre :: Document.nest(2, blockToDocument(o)) :/: post

    case Statement(sym, IdxForeachRes(idx@Def(StoreIndex(self, Constant(idxNum), _, _, _)))) if Optimizer.sliceInline => doc"auto* $sym = $idx.dataHead;"

    case Statement(sym, IdxForeachRes(idx)) => doc"auto* $sym = $idx.foreachRes();"

    case Statement(sym, IdxForeachResMap(idx@Def(StoreIndex(self, Constant(idxNum), _, _, _)), Def(PardisLambda(_, i, o)), res: Sym[_])) if Optimizer.sliceInline =>
      val pre =
        doc"//foreach" :\\:
          doc"${i.tp} $i= $res;" :\\:
          doc"while($i) {"
      val post =
        doc"  $i = $i -> nxt;" :\\:
          doc"}"
      pre :: Document.nest(2, blockToDocument(o)) :/: post

    case Statement(sym, IdxSlice(idx@Def(StoreIndex(self, idxNum, _, _, _)), key, Def(PardisLambda(_, i, o)))) if Optimizer.sliceInline =>
      val symid = sym.id.toString

      val IDX_FN = "IDXFN" + sym.id
      val pre =
        doc"//slice " :\\:
          doc"typedef typename ${self}Idx${idxNum}Type::IFN $IDX_FN;" :\\:
          doc"HASH_RES_t h$symid = $IDX_FN::hash($key);" :\\:
          doc"std::vector<${i.tp}> entVector$symid;" :\\:
          doc"auto* e$symid = &($idx.buckets_[h$symid % $idx.size_]);" :\\:
          doc"if(e$symid->head.obj)" :\\:
          doc"  do {" :\\:
          doc"    auto* n$symid = &e$symid->head;" :\\:
          doc"    if(h$symid == e$symid->hash && !$IDX_FN::cmp($key, *n$symid->obj)) {" :\\:
          doc"      do entVector$symid.push_back(n$symid->obj); while((n$symid = n$symid->nxt));" :\\:
          doc"      break;" :\\:
          doc"    }" :\\:
          doc"  } while((e$symid = e$symid->nxt));" :\\:
          doc"  for(auto $i: entVector$symid) {"
      val post =
        doc"      }"

      pre :: Document.nest(4, blockToDocument(o)) :/: post

    case Statement(sym, IdxSliceNoUpdate(idx@Def(StoreIndex(self, idxNum, _, _, _)), key, Def(PardisLambda(_, i, o)))) if Optimizer.sliceInline =>
      val symid = sym.id.toString

      val IDX_FN = "IDXFN" + sym.id
      val pre =
        doc"//sliceNoUpdate " :\\:
          doc"typedef typename ${self}Idx${idxNum}Type::IFN $IDX_FN;" :\\:
          doc"HASH_RES_t h$symid = $IDX_FN::hash($key);" :\\:
          doc"auto* e$symid = &($idx.buckets_[h$symid % $idx.size_]);" :\\:
          doc"if(e$symid->head.obj)" :\\:
          doc"  do {" :\\:
          doc"    auto* n$symid = &e$symid->head;" :\\:
          doc"    if(h$symid == e$symid->hash && !$IDX_FN::cmp($key, *n$symid->obj)) {" :\\:
          doc"      do {" :\\:
          doc"        auto $i = n$symid->obj;"
      val post =
        doc"      } while((n$symid = n$symid->nxt));" :\\:
          doc"      break;" :\\:
          doc"    }" :\\:
          doc"  } while((e$symid = e$symid->nxt));"

      pre :: Document.nest(8, blockToDocument(o)) :/: post

    case Statement(sym, IdxForeach(idx@Def(StoreIndex(self, Constant(idxNum), _, _, _)), Def(PardisLambda(_, i, o)))) if Optimizer.sliceInline =>
      val symid = sym.id.toString
      if (idxNum != 0)
        throw new Error("For-each on secondary index !")
      val pre =
        doc"//foreach" :\\:
          doc"${i.tp} $i= $idx.dataHead;" :\\:
          doc"while($i) {"
      val post =
        doc"  $i = $i -> nxt;" :\\:
          doc"}"
      pre :: Document.nest(2, blockToDocument(o)) :/: post

    case Statement(sym, n@StructFieldGetter(self: Sym[_], idx)) if sym.tp == StringType =>
      doc"const PString& $sym = " :: nodeToDocument(n) :: ";"
    case Statement(sym, n@GenericEntryGet(self: Sym[_], idx)) if sym.tp == StringType =>
      doc"const PString& $sym = " :: nodeToDocument(n) :: ";"
    case Statement(sym, n@StructDynamicFieldAccess(_, _, _)) if sym.tp == StringType =>
      doc"const PString& $sym = " :: nodeToDocument(n) :: ";"
    case Statement(sym, StoreMap(self, f@Def(PardisLambda(_, _, o)))) =>
      val typeE = sym.tp.asInstanceOf[StoreType[_]].typeE.asInstanceOf[PointerType[_]].contentsType
      val entidx = o.res.asInstanceOf[Rep[Any]] match {
        case Def(GenericEntryApplyObject(Constant("SteNewSEntry"), Def(LiftedSeq(args)))) => "GenericOps_" + (1 to args.length).mkString("")
        case Def(mc@Malloc(_)) =>
          val tp = mc.typeT.asInstanceOf[RecordType[_]].tag.typeName
          val cols = tp.drop(6).split("_")(0).toInt //SBJ: Assuming SEntry<number>_.....
          tp + "_Idx" + (1 to cols).mkString("")

      }
      val idx = doc"HashIndex<$typeE, char, $entidx, 1>"
      doc"auto& $sym = $self.map<$typeE, $idx>($f);"
    case Statement(sym, StoreFold(self, z, f)) =>
      doc"${z.tp} $sym = $self.fold<${z.tp}>($z, $f);"
    case Statement(sym, StoreFilter(self, f)) =>
      doc"auto& $sym = $self.filter($f);"

    case Statement(sym, ProfileStart(n@Constant(str))) =>
      val id = str.split(",")(3)
      doc"auto start$id = Now;"
    case Statement(sym, ProfileEnd(n@Constant(str))) =>
      val id = str.split(",")(3)
      doc"auto end$id = Now;" :/:
        doc"if(durations.find($n) == durations.end()) {" :/:
        doc"  durations[$n] = DurationNS(end$id - start$id);" :/:
        doc"  counters[$n] = 1;" :/:
        doc"} else  {" :/:
        doc"  durations[$n] += DurationNS(end$id- start$id);" :/:
        doc"  counters[$n]++;" :/:
        doc"}"

    case Statement(sym, m@Malloc(Constant(1))) =>
      val tp = sym.tp.asInstanceOf[PointerType[_]].contentsType
      val id = sym.id.toString
      doc"$tp y$id; " ::
        doc"${sym.tp} $sym = &y$id;"

    case Statement(sym, SteNewSEntry(_, args)) =>
      val id = sym.id.toString
      doc"GenericEntry y$id(false_type(),${args.mkDocument(", ")});" :: doc"GenericEntry* $sym = &y$id;"

    case Statement(sym, SteSampleSEntry(_, args)) =>
      val newargs = args.map(t => List(Constant(t._1), t._2)).flatten
      val argsDoc = newargs.mkDocument(", ")
      val id = sym.id.toString
      doc"GenericEntry y$id(true_type(), $argsDoc); GenericEntry* $sym = &y$id;"
    case Statement(sym, GenericEntryApplyObject(Constant("SteSampleSEntry"), Def(LiftedSeq(args)))) =>
      val newargs = args.zipWithIndex.collect({
        case (a, i) if i < args.size / 2 => List(a, args(i + args.size / 2))
      }).flatten
      val argsDoc = newargs.mkDocument(", ")
      val id = sym.id.toString
      doc"GenericEntry y$id(true_type(), $argsDoc); GenericEntry* $sym = &y$id;"
    case Statement(sym, GenericEntryApplyObject(_, Def(LiftedSeq(args)))) =>
      val id = sym.id.toString
      doc"GenericEntry y$id(false_type(), ${args.mkDocument(", ")}); GenericEntry* $sym = &y$id;"
    case _ => super.stmtToDocument(stmt)
  }

  override def symToDocument(sym: ExpressionSymbol[_]): Document = if (sym.tp == UnitType)
    doc"()"
  else {
    sym match {
      case Def(l: PardisLambdaDef) => nodeToDocument(l)
      case _ => if (sym.name != "x" && sym.name != "ite") {
        Document.text(sym.name.stripSuffix("_$"))
      } else {
        super.symToDocument(sym)
      }
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
    case StringExtraSubstringObject(self, pos, len) => doc"$self.substr($pos, $len)" //Different from scala substring
    case StringExtraStringCompareObject(str1, str2) => doc"strcmpi($str1.data_, $str2.data_)"

    case MultiResIsEmpty(self: Sym[_]) => doc"$self == nullptr"

    case AggregatorResult(self: Sym[_]) => doc"$self.result()"

    case StoreInsert(self, e) => doc"$self.add($e)"
    case StoreUnsafeInsert(self, e) => doc"$self.insert_nocheck($e)"
    case StoreGet(self, idx, key) => doc"$self.get($key, $idx)"
    case StoreGetCopy(self, idx, key) => doc"$self.getCopy($key, $idx)"
    case StoreGetCopyDependent(self, idx, key) => doc"$self.getCopyDependent($key, $idx)"
    case StoreUpdate(self, key) => doc"$self.update($key)"
    case StoreUpdateCopy(self, key) => doc"$self.updateCopy($key)"
    case StoreUpdateCopyDependent(self, key) => doc"$self.updateCopyDependent($key)"
    case StoreDelete1(self, key) => doc"$self.del($key)"
    case StoreDeleteCopyDependent(self, key) => doc"$self.delCopyDependent($key)"
    case StoreDeleteCopy(self, key) => doc"$self.delCopy($key)"
    case StoreSlice(self, idx, key, f) => doc"$self.slice($idx, $key, $f)"
    case StoreSliceCopy(self, idx, key, f) => doc"$self.sliceCopy($idx, $key, $f)"
    case StoreSliceCopyDependent(self, idx, key, f) => doc"$self.sliceCopyDependent($idx, $key, $f)"
    case StoreForeach(self, f) => doc"$self.foreach($f)"
    case StoreForeachCopy(self, f) => doc"$self.foreachCopy($f)"
    case StoreClear(self) => doc"$self.clear()"
    case StoreCopyIntoPool(self, e) => doc"$self.copyIntoPool($e)"

    case IdxGet(self, key) => doc"$self.get($key)"
    case IdxGetCopy(self, key) => doc"$self.getCopy($key)"
    case IdxGetCopyDependent(self, key) => doc"$self.getCopyDependent($key)"
    case IdxUpdate(self, key) => doc"$self.update($key)"
    case IdxUpdateCopy(self, key, primary) => doc"$self.updateCopy($key, &$primary)"
    case IdxUpdateCopyDependent(self, key, ref) => doc"$self.updateCopyDependent($key, $ref)"
    case IdxDelete(self, key) => doc"$self.del($key)"
    case IdxDeleteCopy(self, key, primary) => doc"$self.delCopy($key, &$primary)"
    case IdxDeleteCopyDependent(self, key) => doc"$self.delCopyDependent($key)"
    case IdxSlice(self, key, f) => doc"$self.slice($key, $f)"
    case IdxSliceNoUpdate(self, key, f) => doc"$self.sliceNoUpdate($key, $f)"
    case IdxSliceCopy(self, key, f) => doc"$self.sliceCopy($key, $f)"
    case IdxSliceCopyDependent(self, key, f) => doc"$self.sliceCopyDependent($key, $f)"
    case IdxForeach(self, f) => doc"$self.foreach($f)"
    case IdxForeachCopy(self, f) => doc"$self.foreachCopy($f)"
    case IdxClear(self) => doc"$self.clear()"
    case IdxForeachResMap(idx, f, res: Sym[_]) => doc"$idx.foreachResMap($f, $res)"
    case IdxSliceResMap(idx, key, f, res: Sym[_]) => doc"$idx.sliceResMap($key, $f, $res)"
    case IdxSliceResMapNoUpd(idx, key, f, res: Sym[_]) => doc"$idx.sliceResMapNoUpd($key, $f, $res)"

    case ArrayBufferAppend(self, elem) => doc"$self.push_back($elem)"
    case ArrayBufferApply(Def(ArrayBufferSortWith(self, _)), i) => doc"$self[$i]"
    case ArrayBufferApply(self, i) => doc"$self[$i]"
    case ArrayBufferSize(self) => doc"$self.size()"

    case SetSize(self) => doc"$self.size()"

    case ArrayApply(self, i) => doc"$self[$i]"

    case StructFieldSetter(self: Sym[_], idx, rhs) if refSymbols.contains(self) => doc"$self.$idx = $rhs"
    case StructFieldGetter(self: Sym[_], idx) if refSymbols.contains(self) => doc"$self.$idx"
    case StructImmutableField(self: Sym[_], idx) if refSymbols.contains(self) => doc"$self.$idx"
    case StructFieldIncr(self, idx, rhs) if refSymbols.contains(self) => doc"$self.$idx += $rhs"
    case StructFieldDecr(self, idx, rhs) if refSymbols.contains(self) => doc"$self.$idx -= $rhs"
    case StructFieldIncr(self, idx, rhs) => doc"$self->$idx += $rhs"
    case StructFieldDecr(self, idx, rhs) => doc"$self->$idx -= $rhs"
    case StructDynamicFieldAccess(self, i, o) if refSymbols.contains(self) => doc"*(&$self._$i + ($o-1))" //assuming continuous range of same typed elements
    case StructDynamicFieldAccess(self, i, o) => doc"*(&$self->_$i + ($o-1))" //assuming continuous range of same typed elements

    case g@GenericEntryGet(self, i) => doc"$self->get${g.typeE.name}($i)"
    case GenericEntryIncrease(self, i, v) => doc"$self->increase($i, $v)"
    case GenericEntry$plus$eq(self, i, v) => doc"$self->increase($i, $v)"
    case GenericEntryDecrease(self, i, v) => doc"$self->decrease($i, $v)"
    case GenericEntry$minus$eq(self, i, v) => doc"$self->decrease($i, $v)"
    case GenericEntryUpdate(self, i, v) => doc"$self->update($i, $v)"


    case LiftedSeq(ops) if node.tp.isInstanceOf[SeqType[EntryIdx[_]]] => Document.empty
    case PardisLambda(_, i, o) =>
      val retTp = if (o.res.tp == UnitType) doc" {" else doc" -> ${o.res.tp} {"
      doc"[&](${i.tp} $i)" :: retTp :: Document.nest(NEST_COUNT, blockToDocument(o) :/: getBlockResult(o, true)) :/: "}"

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
      val retTp = if (o.res.tp == UnitType) doc" {" else doc" -> ${o.res.tp} {"
      doc"[&](${i1.tp} $i1, ${i2.tp} $i2)" :: retTp :: Document.nest(NEST_COUNT, blockToDocument(o) :/: getBlockResult(o, true)) :/: "}"

    case BooleanExtraConditionalObject(cond, ift, iff) => doc"$cond ? $ift : $iff"

    case `Int>>>1`(self, Constant(v)) if (v < 0) => doc"$self >> ${v & 31}"
    case `Int>>>1`(self, x) => doc"$self >> $x"
    case Equal(a, Constant(null)) if a.tp == StringType => doc"$a.data_ == nullptr"
    //    case Equal(a, b) if a.tp == StringType => //doc"!strcmpi($a, $b)"
    case EntryIdxApplyObject(Def(h: PardisLambda[_, _]), Def(c: PardisLambda2[_, _, _]), Constant(name)) =>
      refSymbols ++= List(h.i, c.i1, c.i2).map(_.asInstanceOf[Sym[_]])
      doc" struct $name {" :/: Document.nest(NEST_COUNT,
        doc"#define int unsigned int" :\\:
          doc"FORCE_INLINE static size_t hash(const ${h.i.tp}& ${h.i})  { " :: Document.nest(NEST_COUNT, blockToDocument(h.o) :/: getBlockResult(h.o, true)) :/: "}" :\\:
          doc"#undef int" :\\:
          doc"FORCE_INLINE static char cmp(const ${c.i1.tp}& ${c.i1}, const ${c.i2.tp}& ${c.i2}) { " :: Document.nest(NEST_COUNT, blockToDocument(c.o) :/: getBlockResult(c.o, true)) :/: "}") :/: "};"

    case EntryIdxGenericOpsObject(Constant(cols)) =>
      if (cols != Nil) {
        val name = "GenericOps_" + cols.mkString("")
        val hash = doc"FORCE_INLINE static size_t hash(const GenericEntry& e) {" :/: Document.nest(2,
          "unsigned int h = 0;" :/:
            cols.map(c => s"h = h ^ (HASH(e.map.at($c)) + 0x9e3779b9 + (h<<6) + (h>>2));").mkDocument("\n") :\\:
            "return h;"
        ) :/: "}"
        val cmp = doc"FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { " :/: Document.nest(2,
          (if (!Optimizer.secondaryIndex)
            s"""if (e1.isSampleEntry) {
                |  for (auto it : e1.map) {
                |    if (e2.map.at(it.first) != it.second)
                |        return 1;
                |  }
                |} else if (e2.isSampleEntry) {
                | for (auto it : e2.map) {
                |     if (e1.map.at(it.first) != it.second)
                |         return 1;
                |  }
                |}else """.stripMargin
          else "")
            ::
            s"""if(${cols.map(c => s"e1.map.at($c) != e2.map.at($c)").mkString(" || ")})
                |   return 1;""".stripMargin
            :/:
            "return 0;"
        ) :/: "}"
        doc"struct $name {" :/: Document.nest(2, hash :/: cmp) :/: "};"
      } else Document.empty

    case EntryIdxGenericCmpObject(Constant(cols), Def(l@PardisLambda(_, _, _))) =>
      val ordCol = Index.getColumnNumFromLambda(l)
      val name = "GenericCmp_" + cols.mkString("") + "_" + ordCol
      val hash = doc"FORCE_INLINE static size_t hash(const GenericEntry& e) {" :/: Document.nest(2,
        "unsigned int h = 0;" :/:
          cols.map(c => s"h = h ^ (HASH(e.map.at($c)) + 0x9e3779b9 + (h<<6) + (h>>2));").mkDocument("\n") :\\:
          "return h;"
      ) :/: "}"
      val cmp = doc"FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { " :: Document.nest(2,
        s"""
           |const Any &r1 = e1.map.at($ordCol);
           |const Any &r2 = e2.map.at($ordCol);
           |if (r1 == r2)
           |  return 0;
           |else if( r1 < r2)
           |  return -1;
           |else
           |  return 1;
      """.stripMargin) :/: "}"
      doc"struct $name {" :/: Document.nest(2, hash :/: cmp) :/: "};"

    case EntryIdxGenericFixedRangeOpsObject(Constant(cols)) =>
      val name = "GenericFixedRange_" + cols.map(t => s"${t._1}f${t._2}t${t._3}").mkString("_")
      val hash = doc"FORCE_INLINE static size_t hash(const GenericEntry& e) {" :/: Document.nest(2,
        doc"unsigned int h = 0;  //Defined only for int fields" :/:
          cols.collect { case (c, l, u) if (u - l) > 1 => s"""h = h * ${u - l} + e.getInt($c) - $l; """ }.mkDocument("\n") :\\:
          doc"return h;"
      ) :/: "}"
      val cmp = doc"FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { " :: Document.nest(2, "return 0;") :: "}"
      doc"struct $name {" :/: Document.nest(2, hash :/: cmp) :/: "};"

    case PardisIfThenElse(cond, thenp, elsep) => //more compact compared to super
      "if(" :: expToDocument(cond) :: ") {" :: Document.nest(NEST_COUNT, blockToDocument(thenp)) :/:
        "}" :: {
        if (elsep.stmts.size != 0) " else {" :: Document.nest(NEST_COUNT, blockToDocument(elsep)) :/: "}"
        else Document.text("")
      }
    case HashCode(a) => doc"HASH($a)"
    case StringExtraStringNewObject(len) => doc"PString($len)"
    case StringExtraStringAppendObject(str, obj) => obj.tp match {
      case d if d == DateType => doc"$str.appendDate($obj)"
      case _ => doc"$str.append($obj)"
    }
    case StringExtraStringAppendNObject(str, obj, n) =>
      val arg = obj match {
        case Def(_) => doc"$obj.data_"
        case c@Constant(_) => expToDocument(c)
      }
      doc"$str.append($arg, $n)"
    case StructCopy(s, orig) =>
      val origStruct = orig.correspondingNode.asInstanceOf[PardisStruct[Any]]
      origStruct.elems.collect { case x if (x.init != nullValue(x.init.tp)) =>
        expToDocument(s) :: "->" :: x.name :: " = " :: expToDocument(x.init)
      }.mkDocument("; ")
    case _ => super.nodeToDocument(node)
  }
}
