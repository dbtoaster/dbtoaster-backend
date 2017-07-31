package ddbt.squid.transformer

import ddbt.codegen.{Embedding, SquidProgram}
import ddbt.transformer.Index
import ddbt.lib.store._

object IndexTransformer {

  import Embedding.Predef._
  import Embedding.{Hole, IR, RepDef}

  def optimize[T](prg: SquidProgram[T]): SquidProgram[T] = {

    def getNameFromHole[T, C](r: IR[T, C]) = r match {
      case IR(RepDef(Hole(name))) => name
    }
    def getColsFromGE[T, C](args: Seq[IR[T, C]]) = args.zipWithIndex.collect { case (ir"${Const(v)}: Int", i) if i < args.size / 2 => v }

    prg.codeBlocks.foreach(b => b._2.analyse({
      //case ir"($store: Store[GenericEntry]).sliceCopy($idx, ddbt.lib.store.GenericEntry.apply($_, $args*), $_)" =>
      case ir"($store: Store[GenericEntry]).sliceCopy($idx, ddbt.lib.store.GenericEntry.apply($_, $args*), $_)" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        prg.globalMaps(name)._2.secondary += cols
        println(s"slice on $store with $cols in block ${b._1 }")
      case ir"($store: Store[GenericEntry]).sliceCopyAgg($idx, ddbt.lib.store.GenericEntry.apply($_, $args*), ()=> Aggregator.max[GenericEntry, $rtp]($f)($o))" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        val (ordC, typ) = Index.getColumnNumFromLambda(f)
        prg.globalMaps(name)._2.max += ((cols, ordC) -> typ)
        println(s"slice MAX on $store with $cols and $ordC in block ${b._1 }")
      case ir"($store: Store[GenericEntry]).sliceCopyAgg($idx, ddbt.lib.store.GenericEntry.apply($_, $args*), ()=> Aggregator.min[GenericEntry, $rtp]($f)($o))" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        val (ordC, typ) = Index.getColumnNumFromLambda(f)
        prg.globalMaps(name)._2.min += ((cols, ordC) -> typ)
        println(s"slice MIN on $store with $cols and $ordC in block ${b._1 }")
      case ir"($store: Store[GenericEntry]).sliceCopyAgg($idx, ddbt.lib.store.GenericEntry.apply($_, $args*), ()=> Aggregator.median[GenericEntry, $rtp]($f)($o))" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        val (ordC, typ) = Index.getColumnNumFromLambda(f)
        prg.globalMaps(name)._2.med += ((cols, ordC) -> typ)
        println(s"slice MED on $store with $cols and $ordC in block ${b._1 } with $typ")
    }))
    val idxes = prg.globalMaps.map(b => {
      val i = b._2._3
      i.add(b._2._2)
      b._1 -> i
    }).toMap


    val cb = prg.codeBlocks.map(b => b._1 -> b._2.rewrite({
      case ir"($store: Store[GenericEntry]).sliceCopy($idx, ddbt.lib.store.GenericEntry.apply($str, $args*), $f)" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        val idx2 = idxes(name).getIdxForSlice(cols)
        val ir2 = ir"$store.sliceCopy(${Const(idx2) }, GenericEntry.apply($str, $args*), $f)"
        //        println(s"\nChanging SLICE to $ir2\n")
        ir2
      case ir"($store: Store[GenericEntry]).sliceCopyAgg($idx, ddbt.lib.store.GenericEntry.apply($str, $args*), ()=> Aggregator.max[GenericEntry, Int]($f)($o))" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        val ordC = Index.getColumnNumFromLambda(f)._1
        val idx2 = idxes(name).getIdxForMax(cols)
        val ir2 = ir"$store.getCopy(${Const(idx2) }, GenericEntry.apply($str, $args*))"
        //        println(s"\nChanging MAX to $ir2\n")
        ir2
      case ir"($store: Store[GenericEntry]).sliceCopyAgg($idx, ddbt.lib.store.GenericEntry.apply($str, $args*), ()=> Aggregator.min[GenericEntry, $rtp]($f)($o))" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        val ordC = Index.getColumnNumFromLambda(f)._1
        val idx2 = idxes(name).getIdxForMin(cols)
        val ir2 = ir"$store.getCopy(${Const(idx2) }, GenericEntry.apply($str, $args*))"
        //        println(s"\nChanging MIN to $ir2\n")
        ir2
      case ir"($store: Store[GenericEntry]).sliceCopyAgg($idx, ddbt.lib.store.GenericEntry.apply($str, $args*), ()=> Aggregator.median[GenericEntry, $rtp]($f)($o))" =>
        val name = getNameFromHole(store)
        val cols = getColsFromGE(args)
        val ordC = Index.getColumnNumFromLambda(f)._1
        val idx2 = idxes(name).getIdxForMedian(cols)
        val ir2 = ir"$store.getCopy(${Const(idx2) }, GenericEntry.apply($str, $args*))"
        //        println(s"\nChanging MEDIAN to $ir2\n")
        ir2
    }))
    cb.foreach(println)
    SquidProgram(prg.globalMaps, cb)
  }
}