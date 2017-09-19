package ddbt.codegen

import ddbt.lib.spark.GlobalMapContext

/**
  * Generates code for the Spark parallel backend.
  *
  * @author Milos Nikolic, Mohammad Dashti
  */
class LMSSparkGen(cls: String = "Query") extends DistributedM3Gen(cls, SparkExpGen) {  
  
  import ddbt.ast.M3._
  import ddbt.ast._
  import ddbt.lib.Utils.{ ind, block, tup, fresh, freshClear } // common functions
  import ddbt.lib.ManifestHelper.{ man, zero, manEntry, manStore }
  import ddbt.lib.store._
  import impl.Rep

  var deltaMapInfo = List[(String, MapInfo)]()  
  val linkMaps  = collection.mutable.Set[MapInfo]()
  val localMaps = collection.mutable.Set[MapInfo]()
  val distributedMaps = collection.mutable.Set[MapInfo]()

  var isInputDistributed: Boolean = false

  val OPTIMIZATION_PIPELINE_COMPUTATION = true

  val contextRDD = "ctx.rdd"

  // SPARK CODE GENERATION - HERE WE PRODUCE SOME STRINGS

  override def apply(s0: System): String = {
    
    // Create MapInfo definitions and load partitioning information
    mapInfo ++= s0.maps.map { case MapDef(name, tp, keys, expr, loc) =>
      (name, MapInfo(name, tp, keys, expr, loc, IndexedStore))
    }

    // Create delta MapInfo definitions
    deltaMapInfo = s0.triggers.flatMap { _.event match {
      case EventBatchUpdate(s @ Schema(name, _)) => 
        val source = s0.sources.filter(_.schema.name == name).head
        val keys = source.schema.fields
        val storeType = if (UNSAFE_OPTIMIZATION_USE_ARRAYS_FOR_DELTA_BATCH) ArrayStore else IndexedStore
        List((s.deltaName, MapInfo(s.deltaName, TypeLong, keys, DeltaMapRefConst(name, keys), source.locality, storeType)))
      case EventInsert(_) | EventDelete(_) => 
        sys.error("Distributed programs run only in batch mode.")
      case _ => Nil
    }}
    mapInfo ++= deltaMapInfo

    // Determine if input data is local (on master) or distributed (on workers)
    if ( deltaMapInfo.forall(_._2.locality == LocalExp) ) 
      isInputDistributed = false
    else if ( deltaMapInfo.forall(_._2.locality == DistRandomExp) )
      isInputDistributed = true
    else sys.error ("Mixing local and distributed input is not supported")

    // Lift and merge trigger statements 
    val updateStmts = reorderTriggers(s0.triggers).flatMap { 
      case Trigger(EventBatchUpdate(_), stmts) => stmts.flatMap(prepareStatement)
      case _ => Nil
    }
    val systemReadyStmts = s0.triggers.flatMap { 
      case Trigger(EventReady, stmts) => stmts.flatMap(prepareStatement)
      case _ => Nil
    }

    // Optimize statements
    val optUpdateStmts = if (OPTIMIZATION_STATEMENT_LEVEL) Optimizer.optimize(updateStmts) else updateStmts
    val optSystemReadyStmts = if (OPTIMIZATION_STATEMENT_LEVEL) Optimizer.optimize(systemReadyStmts) else systemReadyStmts

    // Create statement blocks 
    val updateBlocks = createBlocks(optUpdateStmts)
    val systemReadyBlocks = createBlocks(optSystemReadyStmts)

    // Optimize statement blocks
    val optUpdateBlocks = if (OPTIMIZATION_BLOCK_LEVEL) Optimizer.optimizeBlocks(updateBlocks) else updateBlocks
    // optUpdateBlocks.map(b => java.lang.System.err.println("UPDATE\n" + b.toString))
    val optSystemReadyBlocks = if (OPTIMIZATION_BLOCK_LEVEL) Optimizer.optimizeBlocks(systemReadyBlocks) else systemReadyBlocks
    // optSystemReadyBlocks.map(b => java.lang.System.err.println("SYSREADY\n" + b.toString))

    // Remove unused maps
    val referencedMaps = 
      (optUpdateBlocks ++ optSystemReadyBlocks).map { case block => 
        block.lhsMapNames ++ block.rhsMapNames
      }.reduceOption(_ ++ _).getOrElse(Set[String]())
    mapInfo.retain((n, _) => referencedMaps.contains(n))

    // Extract local, distributed, and link maps
    mapInfo.foreach { case (_, map) => 
      if (map.linkMap) linkMaps += map
      else map.locality match {
        case LocalExp => localMaps += map
        case DistByKeyExp(_) | DistRandomExp => distributedMaps += map      
      }
    }

    ctx0 = mapInfo.map { case (_, MapInfo(name, tp, keys, _, locality, storeType, linkMap)) =>  
      if (keys.size == 0) {
        // hack -- distributed variables are prefixed by "localCtx."
        val prefix = if (locality == LocalExp || linkMap) "" else "localCtx." 
        val rep = impl.namedVar(prefix + name, tp)
        rep.emitted = true
        (name, (rep, keys, tp))
      } 
      else {
        val manifestEntry = me(keys.map(_._2), tp)
        val rep = impl.named(name, true)(manStore(manifestEntry))
        impl.collectStore(rep)(manifestEntry)
        impl.setStoreType(rep.asInstanceOf[impl.codegen.IR.Sym[_]], storeType)
        (name, (rep, keys, tp))
      }
    }.toMap   // XXX missing indexes

    // GENERATE CODE
    val sMainClass = emitMainClass(s0)
    val sActorClass = emitActorClass(s0, optUpdateBlocks, optSystemReadyBlocks)
    val sMapContext = emitMapContext(distributedMaps.toSeq)  // contains distributed maps
    val sDataStructures = emitDataStructures 
    val sProgram = List(sMainClass, sDataStructures, sMapContext, sActorClass).mkString("\n")
    freshClear()
    clearOut
    sProgram
  }

  def emitBlocksNoPipeline(blocks: List[StatementBlock]): String = {

    val linkMapNames = linkMaps.map(_.name)
    val unifiedBlocks = collection.mutable.Map[String, (String, Int)]()
    def tuple(elems: List[String], delim: String = ""): String =
      "(" + (for (group <- elems.grouped(10)) yield
               group.mkString(", " + delim)).mkString("), " + delim + "(") + ")"
    blocks.map {
      case StatementBlock(LocalMode, stmts) =>
        val (actions, others) = stmts.partition (_.rhsTransformer match {
          case ScatterTransformer(_, _) |
               RepartitionTransformer(_, _) |
               GatherTransformer(_) => true
          case _ => false
        })
        val scatterStmts = actions.filter(_.rhsTransformer match {
          case ScatterTransformer(_, _) => true; case _ => false
        })
        val repartStmts = actions.filter(_.rhsTransformer match {
          case RepartitionTransformer(_, _) => true; case _ => false
        })
        val gatherStmts = actions.filter(_.rhsTransformer match {
          case GatherTransformer(_) => true; case _ => false
        })
        val localBlock = StatementBlock(LocalMode, others)
        val lmsLocalBlock = liftBlockToLMS(localBlock)
        val strLocalBlock = block(impl.emitTrigger(lmsLocalBlock, null, null))


        // SCATTER BLOCK
        val strScatterBlock = if (scatterStmts.size == 0) "" else {
          val unifiedId = fresh("unified")
          val (singletons, partitions) =
            scatterStmts.partition(_.lhsMap.keys.size == 0)
          val (singletonsL, singletonsD) =
            singletons.partition(_.lhsMap.tp == TypeLong)
          val wrapL = singletonsL.zipWithIndex.map { case (stmt, i) => {
              val lhsName = stmt.lhsMap.name
              val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
              unifiedBlocks += ((lhsName, (unifiedId, i)))
              s"${rhsName}"
            }}
          val wrapD = singletonsD.zipWithIndex.map { case (stmt, i) => {
              val lhsName = stmt.lhsMap.name
              val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
              unifiedBlocks += ((lhsName, (unifiedId, i)))
              s"${rhsName}"
            }}
          val wrapP = partitions.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            unifiedBlocks += ((lhsName, (unifiedId, i)))
            s"new ColumnarPartition(i, ${rhsName}.partitions(i).buffers)"
          }}
          val unwrapL = Array.tabulate(singletonsL.length)(i =>
            s"w.lArray($i)").toList
          val unwrapD = Array.tabulate(singletonsD.length)(i =>
            s"w.dArray($i)").toList
          val unwrapP = partitions.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val storeType = impl.codegen.storeType(ctx0(lhsName)._1)
            s"new $storeType(w.pArray($i).buffers)"
          }}
          val wrapArgs = List(
              "id = i",
              if (wrapL.isEmpty) "" else s"""|lArray = Array[Long](
                                             |${ind(wrapL.mkString(",\n"))}
                                             |)""".stripMargin,
              if (wrapD.isEmpty) "" else s"""|dArray = Array[Double](
                                             |${ind(wrapD.mkString(",\n"))}
                                             |)""".stripMargin,
              if (wrapP.isEmpty) "" else s"""|pArray = Array[ColumnarPartition](
                                             |${ind(wrapP.mkString(",\n"))}
                                             |)""".stripMargin
            ).filter(_ != "").mkString(",\n")
          val wrap = s"""|new StoreWrapper(
                         |${ind(wrapArgs)}
                         |)""".stripMargin
          val unwrap =
            List("w.id",
              if (unwrapL.isEmpty) "" else s"""|(
                                               |${ind(tuple(unwrapL, "\n"))}
                                               |)""".stripMargin,
              if (unwrapD.isEmpty) "" else s"""|(
                                               |${ind(tuple(unwrapD, "\n"))}
                                               |)""".stripMargin,
              if (unwrapP.isEmpty) "" else s"""|(
                                               |${ind(tuple(unwrapP, "\n"))}
                                               |)""".stripMargin
            ).filterNot(_ == "").mkString(",\n")
          s"""|val ${unifiedId} = ctx.sc.parallelize(
              |  Array.tabulate(numPartitions)(i =>
              |${ind(wrap, 2)}
              |  ), numPartitions)
              |  .mapPartitions(_.toList.map { w =>
              |    (
              |${ind(unwrap, 3)}
              |    )
              |  }.iterator, true)""".stripMargin
        }

        // REPARTITION BLOCK
        val strRepartitionBlock = if (repartStmts.size == 0) "" else {
          // No repartitioning of partial singletons (TODO: enable this option)
          assert(repartStmts.forall(_.lhsMap.keys.size != 0))
          val unifiedId = fresh("unified")
          val wrap = repartStmts.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            unifiedBlocks += ((lhsName, (unifiedId, i)))
            s"""|localCtx.${rhsName}.partitions.zipWithIndex.map {
                |  case (store, i) => (i, new ColumnarPartition($i, store.buffers))
                |}""".stripMargin
          }}.mkString(" ++ \n")
          val unwrap = repartStmts.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            val entryType = impl.codegen.storeEntryType(ctx0(rhsName)._1)
            val storeType = "ColumnarStore" + entryType.substring(entryType.indexOf("_")) // TODO: fix this hack
            s"""|new PartitionContainer[$entryType](
                |  storeGroups($i).map(s => new $storeType(s.buffers)).toArray)""".stripMargin
          }}
          s"""|val ${unifiedId} =
              |  ctx.rdd.mapPartitions(_.toList.flatMap { case (_, localCtx) =>
              |//    Stopwatch.time("Repartition processing time: ", {
              |${ind(wrap, 3)}
              |//    })
              |  }.iterator, false)
              |  .groupByKey(ctx.partitioner)
              |  .mapValues(stores => {
              |    val storeGroups = stores.groupBy(_.id)
              |    (
              |${ind(tuple(unwrap, "\n"), 3)}
              |    )
              |  })""".stripMargin
        }

        // GATHER BLOCK
        val strGatherBlock = if (gatherStmts.size == 0) "" else {
          val unifiedId = fresh("unified")
          val (singletons, partitions) =
            gatherStmts.partition(_.lhsMap.keys.size == 0)
          val (singletonsL, singletonsD) =
            singletons.partition(_.lhsMap.tp == TypeLong)
          val wrapL = singletonsL.map { stmt =>
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            stmt.rhsTransformer.expr.locality match {
              case Some(DistByKeyExp(Nil)) => s"if (id == 0) localCtx.${rhsName} else 0L"
              case Some(DistByKeyExp(_)) | Some(DistRandomExp)  => s"localCtx.${rhsName}"
              case _ => sys.error("Gather of a local expression")
            }
          }
          val wrapD = singletonsD.map { stmt =>
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            stmt.rhsTransformer.expr.locality match {
              case Some(DistByKeyExp(Nil)) => s"if (id == 0) localCtx.${rhsName} else 0.0"
              case Some(DistByKeyExp(_)) | Some(DistRandomExp)  => s"localCtx.${rhsName}"
              case _ => sys.error("Gather of a local expression")
            }
          }
          val wrapP = partitions.map { stmt =>
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            stmt.rhsTransformer.expr.locality match {
              case Some(DistByKeyExp(Nil)) =>
                s"new ColumnarPartition(id, { if (id > 0) localCtx.${rhsName}.size = 0; localCtx.${rhsName}.buffers })"
              case Some(DistByKeyExp(_)) | Some(DistRandomExp) =>
                s"new ColumnarPartition(id, localCtx.${rhsName}.buffers)"
              case _ => sys.error("Gather of a local expression")
            }
          }
          val unwrapL = Array.tabulate(singletonsL.length)(i =>
            s"${unifiedId}L.map(_($i)).reduce(_ + _)").toList
          val unwrapD = Array.tabulate(singletonsD.length)(i =>
            s"${unifiedId}D.map(_($i)).reduce(_ + _)").toList
          val unwrapP = partitions.zipWithIndex.map { case (stmt, i) =>
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            val entryType = impl.codegen.storeEntryType(ctx0(rhsName)._1)
            val storeType = "ColumnarStore" + entryType.substring(entryType.indexOf("_")) // TODO: fix this hack
            s"""|new PartitionContainer[$entryType](${unifiedId}P.map(stores =>
                |  new $storeType(stores($i).buffers)))""".stripMargin
          }
          val wrapArgs = List(
              "id = id",
              if (wrapL.isEmpty) "" else s"""|lArray = Array[Long](
                                             |${ind(wrapL.mkString(",\n"))}
                                             |)""".stripMargin,
              if (wrapD.isEmpty) "" else s"""|dArray = Array[Double](
                                             |${ind(wrapD.mkString(",\n"))}
                                             |)""".stripMargin,
              if (wrapP.isEmpty) "" else s"""|pArray = Array[ColumnarPartition](
                                             |${ind(wrapP.mkString(",\n"))}
                                             |)""".stripMargin
            ).filter(_ != "").mkString(",\n")
          val wrap = s"""|new StoreWrapper(
                         |${ind(wrapArgs)}
                         |)""".stripMargin
          val extract = List(
              if (wrapL.isEmpty) "" else s"val ${unifiedId}L = $unifiedId.map(_.lArray)",
              if (wrapD.isEmpty) "" else s"val ${unifiedId}D = $unifiedId.map(_.dArray)",
              if (wrapP.isEmpty) "" else s"val ${unifiedId}P = $unifiedId.map(_.pArray)"
            ).filter(_ != "").mkString("\n")
          val unwrap = List(
              if (unwrapL.isEmpty) "" else {
                (for (g <- (singletonsL.zip(unwrapL)).grouped(10)) yield {
                  val (lhs, rhs) = g.unzip
                  s"""|val ${tuple(lhs.map(_.lhsMap.name))} = (
                      |${ind(tuple(rhs, "\n"))}
                      |)""".stripMargin
                }).mkString("\n")
              },
              if (unwrapD.isEmpty) "" else {
                (for (g <- (singletonsD.zip(unwrapD)).grouped(10)) yield {
                  val (lhs, rhs) = g.unzip
                  s"""|val ${tuple(lhs.map(_.lhsMap.name))} = (
                      |${ind(tuple(rhs, "\n"))}
                      |)""".stripMargin
                }).mkString("\n")
              },
              if (unwrapP.isEmpty) "" else {
                (for (g <- (partitions.zip(unwrapP)).grouped(10)) yield {
                  val (lhs, rhs) = g.unzip
                  s"""|val ${tuple(lhs.map(_.lhsMap.name))} = (
                      |${ind(tuple(rhs, "\n"))}
                      |)""".stripMargin
                }).mkString("\n")
              }
            ).filterNot(_ == "").mkString("\n")
          s"""|val $unifiedId = ctx.rdd.map { case (id, localCtx) =>
              |  (
              |${ind(wrap, 2)}
              |  )
              |}.collect
              |$extract
              |$unwrap""".stripMargin
        }

        "//  --- LOCAL BLOCK ---\n" +
        List(
          strGatherBlock,           // Pull Gather to the beginning
          strLocalBlock,
          strScatterBlock,          // Push Scatter/Repartition to the end
          strRepartitionBlock
        ).filterNot(_ == "").mkString("\n") + "\n"

      case distBlock @ StatementBlock(DistributedMode, statements) =>
        val mapNames = distBlock.mapNames.toList
        val (inputNames, distNames) = mapNames.partition(linkMapNames.contains)

        // Generate foreach body
        val strRenaming = distNames.filter(n => mapInfo(n).keys.size > 0)
                                   .map(n => s"val $n = localCtx.$n")
                                   .mkString("\n")

        val lmsDistBlock = liftBlockToLMS(distBlock)
        val strDistBlock = impl.emitTrigger(lmsDistBlock, null, null)

        val strConstRenaming =
          (cs.map { case (_, n) => s"val $n = localCtx.$n" } ++
           regexpCacheMap.map { case (_, n) => s"val $n = localCtx.$n" }).mkString("\n")

        // Generate foreach header
        val unifiedIds = inputNames.map(n => unifiedBlocks(n)._1).distinct
        val strZip = if (unifiedIds.size == 0) "" else
          ".zip(" + unifiedIds.mkString(").zip(") + ")"
        val strCaseList = "(id, localCtx)" ::
          unifiedIds.zipWithIndex.map { case (unifiedId, i) =>
            val unifiedNames = unifiedBlocks.filter(_._2._1 == unifiedId)
                                            .map(_._1).toSet
            val matchInputs  = inputNames.filter(unifiedNames.contains)
            val (singletons, partitions) =
              matchInputs.partition(n => mapInfo(n).keys.size == 0)
            val (singletonsL, singletonsD) =
              singletons.partition(n => mapInfo(n).tp == TypeLong)

            val caseMaps = (
              (if (singletonsL.size == 0) Nil
               else List(
                 "(" + tuple(singletonsL.map(n => (unifiedBlocks(n)._2, n))
                                        .sortBy(_._1).map(_._2)) + ")"))
              ++

              (if (singletonsD.size == 0) Nil
               else List(
                 "(" + tuple(singletonsD.map(n => (unifiedBlocks(n)._2, n))
                                        .sortBy(_._1).map(_._2)) + ")"))
              ++
              (if (partitions.size == 0) Nil
               else List(
                 "(" + tuple(partitions.map(n => (unifiedBlocks(n)._2, n))
                                       .sortBy(_._1).map(_._2)) + ")"))
            ).mkString(", ")
            s"(id${i + 2}, $caseMaps)"
          }
        def caseToString(cases: List[String]): String = cases match {
          case Nil => sys.error("Empty case list.")
          case hd :: Nil => hd
          case hd1 :: (hd2 :: tail) => caseToString(s"($hd1, $hd2)" :: tail)
        }

        s"""|//  --- DISTRIBUTED BLOCK ---
            |ctx.rdd${strZip}.foreach {
            |  case ${caseToString(strCaseList)} =>
            |//    Stopwatch.time("Distributed block processing time: ", {
            |${ind(strRenaming, 3)}
            |${ind(strConstRenaming, 3)}
            |
            |${ind(strDistBlock, 3)}
            |//    })
            |}""".stripMargin
    }.mkString("\n")
  }

  def emitBlocks(blocks: List[StatementBlock], baseRDD: String = contextRDD): String = {

    // Pipeline RDD foreach operations
    var lastRDD = baseRDD
    
    // def nextRDDPipe(): String =
    //   s"rddPipe${pipeCounter = pipeCounter + 1; pipeCounter}"

    val linkMapNames = linkMaps.map(_.name)    
    val unifiedBlocks = collection.mutable.Map[String, (String, Int)]()
    def tuple(elems: List[String], delim: String = ""): String = 
      "(" + (for (group <- elems.grouped(10)) yield 
               group.mkString(", " + delim)).mkString("), " + delim + "(") + ")"
    blocks.map { 
      case StatementBlock(LocalMode, stmts) =>
        val (actions, others) = stmts.partition (_.rhsTransformer match {
          case ScatterTransformer(_, _) | 
               RepartitionTransformer(_, _) | 
               GatherTransformer(_) => true
          case _ => false
        })
        val scatterStmts = actions.filter(_.rhsTransformer match {
          case ScatterTransformer(_, _) => true; case _ => false          
        })
        val repartStmts = actions.filter(_.rhsTransformer match {
          case RepartitionTransformer(_, _) => true; case _ => false          
        })        
        val gatherStmts = actions.filter(_.rhsTransformer match {
          case GatherTransformer(_) => true; case _ => false          
        })
        val localBlock = StatementBlock(LocalMode, others)
        val lmsLocalBlock = liftBlockToLMS(localBlock)
        val strLocalBlock = block(impl.emitTrigger(lmsLocalBlock, null, null))


        // GATHER BLOCK
        val strGatherBlock = if (gatherStmts.size == 0) "" else {
          val unifiedId = fresh("unified")
          val (singletons, partitions) = 
            gatherStmts.partition(_.lhsMap.keys.size == 0)
          val (singletonsL, singletonsD) = 
            singletons.partition(_.lhsMap.tp == TypeLong)
          val wrapL = singletonsL.map { stmt =>
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            stmt.rhsTransformer.expr.locality match {
              case Some(DistByKeyExp(Nil)) => s"if (id == 0) localCtx.${rhsName} else 0L"
              case Some(DistByKeyExp(_)) | Some(DistRandomExp)  => s"localCtx.${rhsName}"
              case _ => sys.error("Gather of a local expression")
            }            
          }
          val wrapD = singletonsD.map { stmt =>
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            stmt.rhsTransformer.expr.locality match {
              case Some(DistByKeyExp(Nil)) => s"if (id == 0) localCtx.${rhsName} else 0.0"
              case Some(DistByKeyExp(_)) | Some(DistRandomExp)  => s"localCtx.${rhsName}"
              case _ => sys.error("Gather of a local expression")
            }
          }
          val wrapP = partitions.map { stmt => 
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            stmt.rhsTransformer.expr.locality match {
              case Some(DistByKeyExp(Nil)) =>
                s"new ColumnarPartition(id, { if (id > 0) localCtx.${rhsName}.size = 0; localCtx.${rhsName}.buffers })"
              case Some(DistByKeyExp(_)) | Some(DistRandomExp) =>
                s"new ColumnarPartition(id, localCtx.${rhsName}.buffers)"
              case _ => sys.error("Gather of a local expression")
            }
          }
          val unwrapL = Array.tabulate(singletonsL.length)(i => 
            s"${unifiedId}L.map(_($i)).reduce(_ + _)").toList
          val unwrapD = Array.tabulate(singletonsD.length)(i => 
            s"${unifiedId}D.map(_($i)).reduce(_ + _)").toList
          val unwrapP = partitions.zipWithIndex.map { case (stmt, i) =>
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            val entryType = impl.codegen.storeEntryType(ctx0(rhsName)._1)
            val storeType = "ColumnarStore" + entryType.substring(entryType.indexOf("_")) // TODO: fix this hack
            s"""|new PartitionContainer[$entryType](${unifiedId}P.map(stores =>
                |  new $storeType(stores($i).buffers)))""".stripMargin
          }
          val wrapArgs = List(
              "id = id",              
              if (wrapL.isEmpty) "" else s"""|lArray = Array[Long](
                                             |${ind(wrapL.mkString(",\n"))} 
                                             |)""".stripMargin,
              if (wrapD.isEmpty) "" else s"""|dArray = Array[Double](
                                             |${ind(wrapD.mkString(",\n"))} 
                                             |)""".stripMargin,
              if (wrapP.isEmpty) "" else s"""|pArray = Array[ColumnarPartition](
                                             |${ind(wrapP.mkString(",\n"))}
                                             |)""".stripMargin
            ).filter(_ != "").mkString(",\n")
          val wrap = s"""|new StoreWrapper(
                         |${ind(wrapArgs)} 
                         |)""".stripMargin
          val extract = List(
              if (wrapL.isEmpty) "" else s"val ${unifiedId}L = $unifiedId.map(_.lArray)",
              if (wrapD.isEmpty) "" else s"val ${unifiedId}D = $unifiedId.map(_.dArray)",
              if (wrapP.isEmpty) "" else s"val ${unifiedId}P = $unifiedId.map(_.pArray)"
            ).filter(_ != "").mkString("\n")
          val unwrap = List(
              if (unwrapL.isEmpty) "" else {
                (for (g <- (singletonsL.zip(unwrapL)).grouped(10)) yield {
                  val (lhs, rhs) = g.unzip
                  s"""|val ${tuple(lhs.map(_.lhsMap.name))} = (
                      |${ind(tuple(rhs, "\n"))}
                      |)""".stripMargin
                }).mkString("\n")
              },            
              if (unwrapD.isEmpty) "" else {
                (for (g <- (singletonsD.zip(unwrapD)).grouped(10)) yield {
                  val (lhs, rhs) = g.unzip
                  s"""|val ${tuple(lhs.map(_.lhsMap.name))} = (
                      |${ind(tuple(rhs, "\n"))}
                      |)""".stripMargin
                }).mkString("\n")
              },
              if (unwrapP.isEmpty) "" else {
                (for (g <- (partitions.zip(unwrapP)).grouped(10)) yield {
                  val (lhs, rhs) = g.unzip
                  s"""|val ${tuple(lhs.map(_.lhsMap.name))} = (
                      |${ind(tuple(rhs, "\n"))}
                      |)""".stripMargin
                }).mkString("\n")
              }
            ).filterNot(_ == "").mkString("\n")
          // reset pipeline 
          val sourceRDD = lastRDD
          lastRDD = contextRDD
          s"""|val $unifiedId = ${sourceRDD}.map { case (id, localCtx) =>
              |  (
              |${ind(wrap, 2)}  
              |  ) 
              |}.collect
              |$extract
              |$unwrap""".stripMargin
        }

        // SCATTER BLOCK
        val strScatterBlock = if (scatterStmts.size == 0) "" else {
          val unifiedId = fresh("unified")
          val (singletons, partitions) = 
            scatterStmts.partition(_.lhsMap.keys.size == 0)
          val (singletonsL, singletonsD) = 
            singletons.partition(_.lhsMap.tp == TypeLong)
          val wrapL = singletonsL.zipWithIndex.map { case (stmt, i) => {
              val lhsName = stmt.lhsMap.name
              val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
              unifiedBlocks += ((lhsName, (unifiedId, i)))
              s"${rhsName}"
            }}
          val wrapD = singletonsD.zipWithIndex.map { case (stmt, i) => {
              val lhsName = stmt.lhsMap.name
              val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
              unifiedBlocks += ((lhsName, (unifiedId, i)))
              s"${rhsName}"
            }}  
          val wrapP = partitions.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            unifiedBlocks += ((lhsName, (unifiedId, i)))
            s"new ColumnarPartition(i, ${rhsName}.partitions(i).buffers)"
          }}
          val unwrapL = Array.tabulate(singletonsL.length)(i => 
            s"w.lArray($i)").toList
          val unwrapD = Array.tabulate(singletonsD.length)(i => 
            s"w.dArray($i)").toList
          val unwrapP = partitions.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val storeType = impl.codegen.storeType(ctx0(lhsName)._1)
            s"new $storeType(w.pArray($i).buffers)"
          }}
          val wrapArgs = List(
              "id = i",              
              if (wrapL.isEmpty) "" else s"""|lArray = Array[Long](
                                             |${ind(wrapL.mkString(",\n"))} 
                                             |)""".stripMargin,
              if (wrapD.isEmpty) "" else s"""|dArray = Array[Double](
                                             |${ind(wrapD.mkString(",\n"))} 
                                             |)""".stripMargin,
              if (wrapP.isEmpty) "" else s"""|pArray = Array[ColumnarPartition](
                                             |${ind(wrapP.mkString(",\n"))}
                                             |)""".stripMargin
            ).filter(_ != "").mkString(",\n")
          val wrap = s"""|new StoreWrapper(
                         |${ind(wrapArgs)} 
                         |)""".stripMargin
          val unwrap = 
            List("w.id",
              if (unwrapL.isEmpty) "" else s"""|(
                                               |${ind(tuple(unwrapL, "\n"))}
                                               |)""".stripMargin,
              if (unwrapD.isEmpty) "" else s"""|(
                                               |${ind(tuple(unwrapD, "\n"))}
                                               |)""".stripMargin,
              if (unwrapP.isEmpty) "" else s"""|(
                                               |${ind(tuple(unwrapP, "\n"))}
                                               |)""".stripMargin
            ).filterNot(_ == "").mkString(",\n")
          s"""|val ${unifiedId} = ctx.sc.parallelize(
              |  Array.tabulate(numPartitions)(i =>
              |${ind(wrap, 2)}
              |  ), numPartitions)
              |  .mapPartitions(_.toList.map { w =>
              |    (
              |${ind(unwrap, 3)}
              |    )
              |  }.iterator, true)""".stripMargin
        }

        // REPARTITION BLOCK
        val strRepartitionBlock = if (repartStmts.size == 0) "" else {
          // No repartitioning of partial singletons (TODO: enable this option)
          assert(repartStmts.forall(_.lhsMap.keys.size != 0))
          val unifiedId = fresh("unified")
          val wrap = repartStmts.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name          
            unifiedBlocks += ((lhsName, (unifiedId, i)))
            s"""|localCtx.${rhsName}.partitions.zipWithIndex.map {
                |  case (store, i) => (i, new ColumnarPartition($i, store.buffers))
                |}""".stripMargin
          }}.mkString(" ++ \n")
          val unwrap = repartStmts.zipWithIndex.map { case (stmt, i) => {
            val lhsName = stmt.lhsMap.name
            val rhsName = stmt.rhsTransformer.expr.asInstanceOf[MapRef].name
            val entryType = impl.codegen.storeEntryType(ctx0(rhsName)._1)
            val storeType = "ColumnarStore" + entryType.substring(entryType.indexOf("_")) // TODO: fix this hack
            s"""|new PartitionContainer[$entryType](
                |  storeGroups($i).map(s => new $storeType(s.buffers)).toArray)""".stripMargin
          }}
          s"""|val ${unifiedId} = 
              |  ${lastRDD}.mapPartitions(_.toList.flatMap { case (_, localCtx) =>
              |//    Stopwatch.time("Repartition processing time: ", {
              |${ind(wrap, 3)}
              |//    })
              |  }.iterator, false)
              |  .groupByKey(ctx.partitioner)
              |  .mapValues(stores => {
              |    val storeGroups = stores.groupBy(_.id)
              |    (
              |${ind(tuple(unwrap, "\n"), 3)}
              |    )
              |  })""".stripMargin
        }

        "//  --- LOCAL BLOCK ---\n" +
        List(
          strGatherBlock,           // Pull Gather to the beginning
          strLocalBlock,            
          strScatterBlock,          // Push Scatter/Repartition to the end
          strRepartitionBlock
        ).filterNot(_ == "").mkString("\n") + "\n"

      case distBlock @ StatementBlock(DistributedMode, statements) =>
        val mapNames = distBlock.mapNames.toList
        val (inputNames, distNames) = mapNames.partition(linkMapNames.contains)
        
        // Generate foreach body
        val strRenaming = distNames.filter(n => mapInfo(n).keys.size > 0)
                                   .map(n => s"val $n = localCtx.$n")
                                   .mkString("\n")

        val lmsDistBlock = liftBlockToLMS(distBlock)
        val strDistBlock = impl.emitTrigger(lmsDistBlock, null, null)

        val strConstRenaming = 
          (cs.map { case (_, n) => s"val $n = localCtx.$n" } ++
           regexpCacheMap.map { case (_, n) => s"val $n = localCtx.$n" }).mkString("\n")

        // Generate foreach header 
        val unifiedIds = inputNames.map(n => unifiedBlocks(n)._1).distinct
        val strZip = if (unifiedIds.size == 0) "" else 
          ".zip(" + unifiedIds.mkString(").zip(") + ")"
        val strCaseList = "(id, localCtx)" :: 
          unifiedIds.zipWithIndex.map { case (unifiedId, i) =>
            val unifiedNames = unifiedBlocks.filter(_._2._1 == unifiedId)
                                            .map(_._1).toSet
            val matchInputs  = inputNames.filter(unifiedNames.contains)
            val (singletons, partitions) = 
              matchInputs.partition(n => mapInfo(n).keys.size == 0)
            val (singletonsL, singletonsD) = 
              singletons.partition(n => mapInfo(n).tp == TypeLong) 

            val caseMaps = (
              (if (singletonsL.size == 0) Nil
               else List(
                 "(" + tuple(singletonsL.map(n => (unifiedBlocks(n)._2, n))
                                        .sortBy(_._1).map(_._2)) + ")"))
              ++

              (if (singletonsD.size == 0) Nil
               else List(
                 "(" + tuple(singletonsD.map(n => (unifiedBlocks(n)._2, n))
                                        .sortBy(_._1).map(_._2)) + ")"))
              ++
              (if (partitions.size == 0) Nil
               else List(
                 "(" + tuple(partitions.map(n => (unifiedBlocks(n)._2, n))
                                       .sortBy(_._1).map(_._2)) + ")"))
            ).mkString(", ")
            s"(id${i + 2}, $caseMaps)"
          }
        def caseToString(cases: List[String]): String = cases match {
          case Nil => sys.error("Empty case list.")
          case hd :: Nil => hd
          case hd1 :: (hd2 :: tail) => caseToString(s"($hd1, $hd2)" :: tail)
        }

        // Assumption: there is at most one unified RDD derived from the
        // context RDD. RDDs created using sc.parallelize() are harmless.
        val sourceRDD = if (unifiedIds.size == 0) lastRDD else contextRDD
        val destRDD = fresh("rddPipe")
        lastRDD = destRDD
        s"""|//  --- DISTRIBUTED BLOCK ---
            |val ${destRDD} = ${sourceRDD}${strZip}.mapPartitions(_.toList.map {
            |  case ${caseToString(strCaseList)} =>
            |//    Stopwatch.time("Distributed block processing time: ", {
            |${ind(strRenaming, 3)}
            |${ind(strConstRenaming, 3)}
            |
            |${ind(strDistBlock, 3)}
            |//    })
            |
            |  (id, localCtx)
            |}.iterator, true)""".stripMargin
    }.mkString("\n") + 
    (if (lastRDD == contextRDD) "" 
     else s"""|
              |
              |// Run job
              |ctx.sc.runJob(${lastRDD}, (iter: Iterator[_]) => {})""".stripMargin) 
  }

  protected def emitMaps(f: (MapInfo => String), maps: Seq[MapInfo]): String = 
    maps.map(f).mkString("\n")

  protected def emitLocalMap(m: MapInfo): String = {
    if (m.keys.size == 0) createVarDefinition(m.name, m.tp)
    else {
      val sym = ctx0(m.name)._1.asInstanceOf[impl.codegen.IR.Sym[_]]
      impl.codegen.generateStore(sym)
    }
  }

  protected def emitDistributedMap(m: MapInfo): String = 
    if (m.keys.size == 0) 
      // hack -- distributed variables are prefixed by "localCtx."
      createVarDefinition(m.name.stripPrefix("localCtx."), m.tp)
    else {
      val sym = ctx0(m.name)._1.asInstanceOf[impl.codegen.IR.Sym[_]]
      impl.codegen.generateStore(sym)
    }

  override val additionalImports: String = List(
      "import ddbt.lib.spark._",
      "import ddbt.lib.spark.store._",
      "import ddbt.lib.spark.store.CharArrayImplicits._",
      "import scala.util.hashing.MurmurHash3.stringHash",
      "import org.apache.spark.SparkContext",
      "import org.apache.spark.SparkContext._",
      "import scala.collection.mutable.ArrayBuffer"
    ).mkString("\n")

  def liftBlockToLMS(block: StatementBlock): impl.Block[Unit] = {
    // Trigger context: global maps + local maps + trigger arguments (batch)
    cx = Ctx(ctx0.map { case (name, (sym, keys, tp)) => (name, sym) })    
    impl.reifyEffects {
      block.stmts.map { case stmt =>
        cx.load()
        val lhsMap = stmt.lhsMap
        if (lhsMap.keys.size == 0) {
          val lhsRep = lhsMap.tp match {      
            case TypeLong   => impl.Variable(cx(lhsMap.name).asInstanceOf[Rep[impl.Variable[Long]]])
            case TypeDouble => impl.Variable(cx(lhsMap.name).asInstanceOf[Rep[impl.Variable[Double]]])
            case TypeString => impl.Variable(cx(lhsMap.name).asInstanceOf[Rep[impl.Variable[String]]])
            case _ => sys.error("Unsupported type " + lhsMap.tp)
          }
          expr(stmt.rhsTransformer.expr, (rhsRep: Rep[_]) => stmt.opMap match { 
            case OpAdd => impl.var_plusequals(lhsRep, rhsRep) 
            case OpSet => impl.__assign(lhsRep, rhsRep) 
          })
        } 
        else {
          val lhsRep = cx(lhsMap.name).asInstanceOf[Rep[Store[Entry]]]
          implicit val manifestEntry = manEntry(lhsMap.keys.map(_._2) ++ List(lhsMap.tp)).asInstanceOf[Manifest[Entry]]

          if (stmt.opMap == OpSet) impl.stClear(lhsRep)
          stmt.initTransformer.map { case initTransformer =>
            expr(initTransformer.expr, (ivcRep: Rep[_]) => {
              val entryRep = impl.stNewEntry(lhsRep, (lhsMap.keys.map(x => cx(x._1)) ++ List(ivcRep)))
              impl.__ifThenElse(
                impl.equals(
                  mapProxy(lhsRep).get(lhsMap.keys.zipWithIndex.map { case (k, i) => (i + 1, cx(k._1)) }: _*),
                  impl.unit(null)
                ),
                impl.m3set(lhsRep, entryRep),
                impl.unit(()))
            })
          }
          cx.load()
          expr(stmt.rhsTransformer.expr, (rhsRep: Rep[_]) => {
            val entryRep = impl.stNewEntry(lhsRep, (lhsMap.keys.map(x => cx(x._1)) ++ List(rhsRep)))
            stmt.opMap match { case OpAdd | OpSet => impl.m3add(lhsRep, entryRep)(manifestEntry) }
          }, Some(lhsMap.keys))

          // val batch = cx(stmt.conditions.head).asInstanceOf[Rep[Store[Entry]]]
          // val cond = if (batch == null) impl.unit(true)
          //            else impl.ordering_gt(impl.stSize(batch), impl.unit(0))
          // impl.__ifThenElse(
          //   cond,
          //   impl.notequals(
          //     if (stmt.opMap == OpSet) impl.stSize(guard) else impl.unit(1),
          //     impl.unit(0)
          //   ),
          //   <BLOCK>,
          //   impl.unit()
          // )
        }
      }
      impl.unit(())
    }
  }

  protected def emitSources(sources: List[Source]): String = streams(sources)

  protected def emitQueryResults(queries: List[Query]): String =
    queries.zipWithIndex.map { case (q, i) => 
      "logWriter.println(\"%s:\\n\" + M3Map.toStr(res(%d)) + \"\\n\")".format(q.name, i)
    }.mkString("\n")

  protected def emitMainClass(s0: System): String = {
    val sSources = if (isInputDistributed) "Seq()"
                   else "\n|" + ind(emitSources(s0.sources), 5)
    val sQueryResult = ind(emitQueryResults(s0.queries), 4)
    s"""|import ddbt.lib._ 
        |import akka.actor.Actor
        |$additionalImports
        |
        |object $sSparkObject {
        |  import Helper._
        |  import org.apache.hadoop.fs.{ Path, FileSystem, FSDataOutputStream }
        |
        |  var configFile: String = "/spark.config"
        |  var batchSize: Int = 0
        |  var noOutput: Boolean = false
        |  var logCount: Long = 0L
        |  var numPartitions: Int = 0
        |  var dataset: String = null
        |  var distInputPath: String = null
        |  
        |  // Handle for reading from HDFS
        |  val fs = FileSystem.get(new org.apache.hadoop.conf.Configuration())
        |
        |  var logWriter: LogWriter = null 
        |
        |  // Spark related variables
        |  private var cfg: SparkConfig = null
        |  private var sc: SparkContext = null
        |  var ctx: ${sGlobalMapContextClass} = null
        |
        |  def execute(args: Array[String], f: List[Any] => Unit) =
        |    bench(args, (dataset: String, parallelMode: Int, timeout: Long, batchSize: Int) => 
        |      {
        |        $sSparkObject.dataset = dataset
        |        $sSparkObject.batchSize = batchSize
        |        run[$sSparkObject]($sSources, parallelMode, timeout, batchSize) 
        |      }, f)
        | 
        |  def initContext(sc: SparkContext, numPartitions: Int) = {
        |    ctx = new ${sGlobalMapContextClass}(sc, numPartitions,
        |      (id => new ${sLocalMapContextClass}(id, numPartitions)))
        |    ctx.init()
        |  }
        |
        |  def destroyContext() = ctx.destroy()
        |
        |  def disableLog4j() = {
        |    import org.apache.log4j.{Logger, Level}
        |    Logger.getLogger("org").setLevel(Level.WARN)
        |    Logger.getLogger("akka").setLevel(Level.WARN)
        |  }
        |
        |  def main(args: Array[String]) = {
        |    val argMap = parseArgs(args)
        |    dataset = argMap.get("dataset").map(_.asInstanceOf[String]).getOrElse(dataset)
        |    configFile = argMap.get("configFile").map(_.asInstanceOf[String]).getOrElse(configFile)
        |    batchSize = argMap.get("batchSize").map(_.asInstanceOf[Int]).getOrElse(batchSize)
        |    noOutput = argMap.get("noOutput").map(_.asInstanceOf[Boolean]).getOrElse(noOutput)
        |    logCount = argMap.get("logCount").map(_.asInstanceOf[Long]).getOrElse(logCount)
        |    numPartitions = argMap.get("numPartitions").map(_.asInstanceOf[Int]).getOrElse(numPartitions)
        |
        |    if (dataset == null) { sys.error("Dataset is missing.") }
        |    if (configFile == null) { sys.error("Config file is missing.") }
        |    if (batchSize == 0) { sys.error("Invalid batch size.") }
        |
        |    disableLog4j()
        |
        |    cfg = new SparkConfig(getClass().getResourceAsStream(configFile))
        |
        |    if (numPartitions == 0) { numPartitions = cfg.sparkNumPartitions }
        |    if (numPartitions == 0) { sys.error("Invalid number of partitions.") }
        |    distInputPath = cfg.distInputPath
        | 
        |    // Init logger
        |    logWriter = new LogWriter("$sSparkObject", cfg.logOutputPath)
        |
        |    // Init Spark context
        |    sc = new SparkContext(cfg.sparkConf.setAppName("$sSparkObject"))
        |
        |    // START EXECUTION
        |    execute(args, (res: List[Any]) => {
        |      if (!noOutput) {
        |$sQueryResult      
        |      }
        |    })
        |  }
        |}
        |
        |""".stripMargin
  }

  protected def emitDataStructures: String = {
    var outStream = new java.io.StringWriter
    impl.codegen.emitDataStructures(new java.io.PrintWriter(outStream))
    outStream.toString
  }

  protected def emitMapContext(distributedMaps: Seq[MapInfo]): String = {
    val sBatchQueues = if (!isInputDistributed) "" else
      ( "// Queues for storing preloaded distributed batches" :: 
        deltaMapInfo.map { case (name, _) =>
          val storeEntryType = impl.codegen.storeEntryType(ctx0(name)._1)
          if (GlobalMapContext.QUICK_LOAD_OF_INSERT_STREAMS)
            s"val ${name}_QUEUE = new collection.mutable.Queue[Array[$storeEntryType]]()"
          else
            s"val ${name}_QUEUE = new collection.mutable.Queue[ArrayBuffer[$storeEntryType]]()"
        }
      ).mkString("\n")          

    val sDistributedMaps = emitMaps(emitDistributedMap, distributedMaps)
    s"""|class $sLocalMapContextClass(val partitionId: Int, numPartitions: Int) {
        |  import ddbt.lib.Functions._
        | 
        |${ind(sDistributedMaps)}
        |
        |  // Constants   
        |${ind(consts)}
        |  
        |${ind(sBatchQueues)}
        |}
        |""".stripMargin
  }
  
  def fieldsToArgList(fields: List[(String, Type)]): String = 
    fields.zipWithIndex.map { case ((_, _), i) => "v" + i }.mkString(", ")

  def fieldsToParamList(fields: List[(String, Type)]): String = 
    fields.zipWithIndex.map { case ((_, tp), i) => s"v$i: ${tp.toScala}" }.mkString(", ")

  protected def emitEventHandlers(s0: System, skipExec: Boolean): String = {
    val step = 128 // periodicity of timeout verification, must be a power of 2
    val (batchEvents, otherEvents) = s0.triggers.map(_.event).partition {
      case EventBatchUpdate(_) => true
      case _ => false
    }
    val sBatchEventHandler = 
      if (batchEvents.size == 0 | isInputDistributed)
        "case BatchUpdateEvent(streamData) =>"
      else if (skipExec) {
        """|case BatchUpdateEvent(streamData) =>
           |  val batchSize = streamData.map(_._2.length).sum
           |  tuplesSkipped += batchSize
           |""".stripMargin
      }
      else {
        lazy val batchTupleTimeoutCheck =
          s"""|// Timeout check
              |if (endTime > 0 && (tuplesProcessed / $step) < ((tuplesProcessed + batchSize) / $step)) {
              |  val t = System.nanoTime
              |  if (t > endTime) { 
              |    endTime = t
              |    tuplesSkipped = batchSize
              |    $sEscapeFn 
              |  }
              |}
              |""".stripMargin      
        val sStreamCase = batchEvents.map {
          case EventBatchUpdate(s) =>
            val schema = s0.sources.filter(_.schema.name == s.name).head.schema
            val deltaName = schema.deltaName
            val params = fieldsToParamList(schema.fields)
            val addBatchTuple = ind(genAddBatchTuple(deltaName, schema.fields, "vv"), 2)
            s"""|case ("${schema.name}", dataList) => 
                |  dataList.foreach { case List(${params}, vv: TupleOp) =>
                |$addBatchTuple
                |  }""".stripMargin
          case _ => ""
        }.mkString("\n")
        val deltaNames = batchEvents.flatMap {
          case EventBatchUpdate(s) => List(s.deltaName)
          case _ => Nil
        } 
        val onBatchArgs = deltaNames.mkString(", ")
        val clearDeltas = deltaNames.map(_ + ".clear").mkString("\n")
        s"""|case BatchUpdateEvent(streamData) =>
            |  val batchSize = streamData.map(_._2.length).sum
            |${ind(batchTupleTimeoutCheck)}
            |  tuplesProcessed += batchSize
            |
            |${ind(clearDeltas)}
            |  streamData.foreach { 
            |${ind(sStreamCase, 2)}
            |    case (s, _) => sys.error("Unknown stream event name " + s)
            |  }
            |  onBatchUpdate($onBatchArgs)
            |  if (logCount > 0 && tuplesProcessed % logCount == 0) 
            |    logWriter.println(tuplesProcessed + " tuples processed at " + 
            |      ((System.nanoTime - startTime) / 1000000) + "ms")
            |""".stripMargin
    }
    val sTupleEventHandler = {
      lazy val singleTupleTimeoutCheck =
        s"""|// Timeout check
            |if (endTime > 0 && (tuplesProcessed & ${step - 1}) == 0) {
            |  val t = System.nanoTime
            |  if (t > endTime) { 
            |    endTime = t
            |    tuplesSkipped = 1
            |    $sEscapeFn
            |  }
            |}
            |""".stripMargin      
      otherEvents.map {
        case EventInsert(schema) => if (skipExec) {
            s"""|case TupleEvent(TupleInsert, "${schema.name}", _) =>
                |  tuplesSkipped += 1
                |""".stripMargin
          }
          else {
            s"""|case TupleEvent(TupleInsert, "${schema.name}", List(${fieldsToParamList(schema.fields)})) =>
                |%s
                |  tuplesProcessed += 1
                |  onAdd${schema.name}(${fieldsToArgList(schema.fields)})  
                |""".stripMargin
          }
        case EventDelete(schema) =>  if (skipExec) {
            s"""|case TupleEvent(TupleDelete, "${schema.name}", _) =>
                |  tuplesSkipped += 1
                |""".stripMargin
          }
          else {
            """|case TupleEvent(TupleDelete, "${schema.name}", List(${fieldsToParamList(schema.fields)})) =>
               |%s
               |  tuplesProcessed += 1
               |  onDel${schema.name}(${fieldsToArgList(schema.fields)})  
               |""".stripMargin
          }
        case _ => ""
      }.mkString("\n") 
    }
    (sTupleEventHandler + sBatchEventHandler)
  }

  protected def emitLoadTablesBody(sources: List[Source]): String = 
    sources.filterNot { _.isStream }.map { table => {
      val keys = table.schema.fields.zipWithIndex.map { case ((_, t), i) => ("v" + i, t) }
      val tuple = genTuple(keys.map { case (v, t) => (t, v) })
      val (_, adaptor, split) = genStream(table)
      val inputStream = table.in match {
        case SourceFile(path) =>
          if (isInputDistributed) {
            val filename = path.substring(path.lastIndexOf("/") + 1)
            // TODO: remove hard-coded standard dataset
            val distPath = "distInputPath + \"/standard/" + filename + "\"" 
            s"fs.open(new org.apache.hadoop.fs.Path(${distPath}))"
          }
          else s"""new java.io.FileInputStream("${path}")"""
      }
      s"""|SourceMux({ 
          |  case TupleEvent(TupleInsert, _, List(${fieldsToParamList(table.schema.fields)})) =>
          |${ind(genInitializationFor(table.schema.name, keys, tuple), 2)}
          |  }, Seq((
          |    $inputStream,
          |    $adaptor,
          |    $split
          |))).read""".stripMargin
    }}.mkString("\n")

  protected def emitLoadInsertStreamsBody(sources: List[Source]): String = {
    if (!isInputDistributed) return ""

    val streams = sources.filter {
      case Source(true, _, _, _, _, DistRandomExp) => true
      case Source(true, _, _, _, _, _) => sys.error("Stream is not randomly distributed")
      case _ => false
    }
    
    val sDistInputSources = streams.map (s => {
      val origPath = s.in match { case SourceFile(path) => path }
      val path = "distInputPath + \"/\" + dataset + \"/" +
        origPath.substring(origPath.lastIndexOf("/") + 1) + "\""
      val name = s.schema.name.toUpperCase 
      val schema = s.schema.fields.map(_._2).mkString(",")
      val sep = java.util.regex.Pattern.quote(
          s.adaptor.options.getOrElse("delimiter", ",")
        ).replaceAll("\\\\", "\\\\\\\\")
      s"""|(${path},
          | (\"${name}\", \"${schema}\", \"${sep}\", "insert"))""".stripMargin
    }).mkString(",\n")

    val sEnqueueBatches = streams.zipWithIndex.map { case (s, ind) => {
        val name = s.schema.deltaName
        val params = fieldsToParamList(s.schema.fields)
        val args = fieldsToArgList(s.schema.fields)
        s"""|ctx.rdd.zip(batchedStreams(${ind})).foreach {
            |  case ((id, localCtx), batches) =>
            |    for (batch <- batches)
            |    {
            |      localCtx.${s.schema.deltaName}_QUEUE.enqueue(
            |        batch.map { case List(${params}) => 
            |          ${impl.codegen.storeEntryType(ctx0(name)._1)}(${args}, Messages.TupleInsert)
            |      })
            |    }  
            |}
            |""".stripMargin
      }}.mkString("\n")

    s"""|assert(!dataset.endsWith("_del"))
        |
        |val streams = ctx.loadInsertStreams(Array(
        |${ind(sDistInputSources)}
        |))
        |
        |val streamCounts = streams.map(_.count).toArray
        |val batchWeights = GlobalMapContext.uniformBatchSizes(streamCounts, batchSize)
        |
        |assert(batchWeights.map(_.size).toSet.size == 1)
        |
        |numTuples = streamCounts.sum
        |numBatches = batchWeights.map(_.size).max
        |
        |// Run GC on workers and master
        |ctx.rdd.foreach(x => System.gc())
        |System.gc()
        |
        |printSummary()
        |
        |val batchedStreams = streams.zipWithIndex.map { case (s, i) => 
        |  s.mapPartitions(it => List(GlobalMapContext.chop(it.toArray, batchWeights(i))).iterator, true) }
        |
        |${sEnqueueBatches}
        |
        |// Run GC on workers and master
        |ctx.rdd.foreach(x => System.gc())
        |System.gc()
        |""".stripMargin

  }

  protected def emitLoadStreamsBody(sources: List[Source]): String = {
    if (!isInputDistributed) return ""

    val streams = sources.filter {
      case Source(true, _, _, _, _, DistRandomExp) => true
      case Source(true, _, _, _, _, _) => sys.error("Stream is not randomly distributed")
      case _ => false
    }
    val sDistInputSources = streams.map (s => {
      val origPath = s.in match { case SourceFile(path) => path }
      val path = "distInputPath + \"/\" + dataset + \"/" +
        origPath.substring(origPath.lastIndexOf("/") + 1) + "\""
      val name = s.schema.name.toUpperCase 
      val schema = s.schema.fields.map(_._2).mkString(",")
      val sep = java.util.regex.Pattern.quote(
          s.adaptor.options.getOrElse("delimiter", ",")
        ).replaceAll("\\\\", "\\\\\\\\")
      val del = "if (dataset.endsWith(\"_del\")) \"ins + del\" else \"insert\""
      s"""|(${path},
          | (\"${name}\", \"${schema}\", \"${sep}\", ${del}))""".stripMargin
    }).mkString(",\n")

    val sDistInputList = streams.map (s => {
        val name = s.schema.deltaName
        s"val ${name}_BATCHES = new ArrayBuffer[${impl.codegen.storeEntryType(ctx0(name)._1)}](16)"
      }).mkString("\n")

    val sQueueList = streams.map (s => 
        s"localCtx.${s.schema.deltaName}_QUEUE.enqueue(${s.schema.deltaName}_BATCHES)"
      ).mkString("\n")

    val sCaseList = streams.zipWithIndex.map { case (s, ind) => {
        val name = s.schema.deltaName
        val params = fieldsToParamList(s.schema.fields)
        val args = fieldsToArgList(s.schema.fields)
        s"""|case (List(${params}, vv: TupleOp), (ind, $ind)) =>
            |  ${name}_BATCHES += ${impl.codegen.storeEntryType(ctx0(name)._1)}(${args}, vv)
            |""".stripMargin
      }}.mkString("\n")

    s"""|val streamRDD = ctx.loadStreams("$sSparkObject", List(
        |${ind(sDistInputSources)}
        |))
        |
        |numTuples = streamRDD.map(_.size.toLong).reduce(_ + _)
        |numBatches = math.ceil(numTuples.toDouble / batchSize).toInt 
        |
        |val bBatchSize = sc.broadcast(batchSize)  
        |val bNumBatches = sc.broadcast(numBatches)
        |
        |printSummary()
        |
        |ctx.rdd.zip(streamRDD).foreach {
        |  case ((id, localCtx), tuples) =>
        |    val batchedTuples =  tuples.groupBy(_._2._1 / bBatchSize.value)
        |    (0 until bNumBatches.value).foreach { batchId =>
        |
        |${ind(sDistInputList, 3)}
        |
        |      if (batchedTuples.contains(batchId)) {
        |        batchedTuples(batchId).foreach {
        |${ind(sCaseList, 5)}
        |        }
        |      }
        |${ind(sQueueList, 3)}
        |    }
        |}
        |
        |// Run GC on workers and master
        |ctx.rdd.foreach(x => System.gc())
        |System.gc()
        |""".stripMargin
  }

  override def toMapFunction(q: Query) = {
    val mapName = q.name
    val mapType = q.map.tp.toScala
    val mapDef = mapInfo(mapName)
    val mapKeyTypes = mapDef.keys.map(_._2)
    val args = tup(mapKeyTypes.zipWithIndex.map { case (_, i) => "e._" + (i + 1) })
    val params = tup(mapKeyTypes.map(_.toScala))
    val resultMapName = mapName + "Result"
    mapDef.locality match {
      case LocalExp => 
        s"""|{
            |  val $resultMapName = new collection.mutable.HashMap[$params, $mapType]()
            |  $mapName.foreach { e => 
            |    $resultMapName += ($args -> e._${mapKeyTypes.size + 1})
            |  }
            |  $resultMapName.toMap
            |}""".stripMargin
      case DistByKeyExp(_) | DistRandomExp => 
        val filter = mapDef.locality match {
          case DistByKeyExp(Nil) => "first"
          case _ => "reduce(_ ++ _)"
        }
        s"""|{
            |  ctx.rdd.map { case (_, localCtx) =>
            |    val $resultMapName = new collection.mutable.HashMap[$params, $mapType]()
            |    localCtx.${mapName}.foreach { e =>
            |      $resultMapName += ($args -> e._${mapKeyTypes.size + 1})  
            |    }
            |    $resultMapName.toMap
            |  }.collect.${filter}
            |}""".stripMargin
    }
  }

  override protected def emitGetSnapshotBody(queries: List[Query]): String = {
    val sCreateHashMap = queries.map(q => 
      if (q.keys.size > 0) toMapFunction(q) else q.name
    ).mkString(", ")
    s"""|(StreamStat(endTime - startTime, tuplesProcessed, tuplesSkipped), List(
        |
        |${ind(sCreateHashMap)}
        |
        |))""".stripMargin    
  }

  protected def emitActorClass(s0: System, updateBlocks: List[StatementBlock], 
      systemReadyBlocks: List[StatementBlock]): String = {
    // The order of these statements is important
    val sEventHandlersSkip = ind(emitEventHandlers(s0, true), 2)
    val sEventHandler = ind(emitEventHandlers(s0, false), 2)
    val sLoadTablesBody = ind(emitLoadTablesBody(s0.sources), 2)
    val sLoadStreamsBody = 
      if (GlobalMapContext.QUICK_LOAD_OF_INSERT_STREAMS) 
        ind(emitLoadInsertStreamsBody(s0.sources), 2)
      else ind(emitLoadStreamsBody(s0.sources), 2)
    val sEmitBody = ind(emitActorBody(updateBlocks, systemReadyBlocks))
    val sGetSnapshotBody = ind(emitGetSnapshotBody(s0.queries), 2)
    val sProcessBatches = if (isInputDistributed) "processBatches(numBatches)" else ""
    val sConstants = ind(consts)
    s"""|class $sSparkObject extends Actor {
        |  import ddbt.lib.Messages._        
        |  import ddbt.lib.Functions._
        |  import $sSparkObject._ 
        |
        |$sEmitBody
        |
        |  var startTime = 0L
        |  var endTime = 0L
        |  var tuplesProcessed = 0L
        |  var tuplesSkipped = 0L
        |
        |  var numTuples = 0L
        |  var numBatches = 0
        |
        |  def loadTables() = { ${block(sLoadTablesBody)} }
        |
        |  def loadStreams() = { ${block(sLoadStreamsBody)} }
        |
        |  def getSnapshot = { ${block(sGetSnapshotBody)} }
        |
        |  def printSummary() = {
        |    logWriter.println("### ${sSparkObject}")
        |    logWriter.println("### DATASET:    " + dataset)
        |    logWriter.println("### PARTITIONS: " + numPartitions)
        |    logWriter.println("### TUPLES:     " + numTuples)
        |    logWriter.println("### BATCHES:    " + numBatches)
        |    logWriter.println("### BATCH SIZE: " + batchSize)
        |    logWriter.println("### DISTRIBUTED INPUT: ${isInputDistributed}")
        |  }
        |
        |  def receive_skip: Receive = { 
        |    case StreamInit(_) =>
        |    case EndOfStream => 
        |      sender ! getSnapshot
        |      destroyContext()
        |    case GetSnapshot(_) => 
        |      sender ! getSnapshot
        |$sEventHandlersSkip
        |  }
        | 
        |  def receive = {
        |    case StreamInit(timeout) => 
        |      initContext(sc, numPartitions)
        |      loadTables()
        |      onSystemReady()
        |      loadStreams()
        |      startTime = System.nanoTime
        |      if (timeout > 0) endTime = startTime + timeout * 1000000L
        |    case EndOfStream => 
        |      $sProcessBatches
        |      endTime = System.nanoTime
        |      sender ! getSnapshot
        |      destroyContext()
        |    case GetSnapshot(_) => 
        |      sender ! getSnapshot
        |$sEventHandler
        |  }
        | 
        |  // Constants 
        |$sConstants
        |}
        |""".stripMargin
  }

  protected def emitActorBody(updateBlocks: List[StatementBlock],
      systemReadyBlocks: List[StatementBlock]): String = {

    val sSystemReadyBlocks = ind(emitBlocks(systemReadyBlocks))

    val sProcessFn =
      if (isInputDistributed) {

        val rddPipeId = fresh("rddPipe")
        val sUpdateBlocks =
          if (OPTIMIZATION_PIPELINE_COMPUTATION) emitBlocks(updateBlocks, rddPipeId)
          else emitBlocksNoPipeline(updateBlocks)

        val sDequeueBlock = 
          if (UNSAFE_OPTIMIZATION_USE_ARRAYS_FOR_DELTA_BATCH) {

            val sDequeueList = deltaMapInfo.map { case (name, mapInfo) =>
                s"localCtx.${name} = localCtx.${name}_QUEUE.dequeue"
              }.mkString("\n")

            if (OPTIMIZATION_PIPELINE_COMPUTATION)
              s"""|// Dequeue next batch
                  |val ${rddPipeId} = ctx.rdd.mapPartitions(_.toList.map { case (id, localCtx) =>
                  |${ind(sDequeueList, 2)}
                  |
                  |  (id, localCtx)
                  |}.iterator, true)""".stripMargin
            else
              s"""|// Dequeue next batch
                  |ctx.rdd.foreach { case (id, localCtx) =>
                  |${ind(sDequeueList, 2)}
                  |}""".stripMargin
          }
          else {

            val sRenaming = deltaMapInfo.map { case (name, _) =>
                s"val ${name} = localCtx.${name}"
              }.mkString("\n")

            val sDequeueList = deltaMapInfo.map { case (name, mapInfo) =>
                val (rep, keys, tp) = ctx0(name)
                val storeEntryType = impl.codegen.storeEntryType(rep)
                val params = fieldsToParamList(keys)
                val addBatchTuple = genAddBatchTuple(name, keys, "vv")
                s"""|${name}.clear
                    |if (!localCtx.${name}_QUEUE.isEmpty) {
                    |  val ${name}_TMP = localCtx.${name}_QUEUE.dequeue
                    |  ${name}_TMP.foreach {
                    |    case ${storeEntryType}(${params}, vv: ${tp.toScala}) =>
                    |${ind(addBatchTuple, 3)}
                    |  }
                    |}
                    |""".stripMargin
              }.mkString("\n")

            if (OPTIMIZATION_PIPELINE_COMPUTATION)
              s"""|// Dequeue next batch
                  |val ${rddPipeId} = ctx.rdd.mapPartitions(_.toList.map { case (id, localCtx) =>
                  |${ind(sRenaming, 2)}
                  |
                  |${ind(sDequeueList, 2)}
                  |
                  |  (id, localCtx)
                  |}.iterator, true)""".stripMargin
            else
              s"""|// Dequeue next batch
                  |ctx.rdd.foreach { case (id, localCtx) =>
                  |${ind(sRenaming)}
                  |
                  |${ind(sDequeueList)}
                  |}""".stripMargin
          }

        s"""|def processBatches(numBatches: Int) = {
            |  logWriter.println("### PROCESSING START: " + numBatches, true)
            |  var runningTime = 0L
            |  for (i <- 0 until numBatches) {
            |    val batchStartTime = System.nanoTime
            |
            |${ind(sDequeueBlock, 2)}
            |
            |${ind(sUpdateBlocks, 2)}
            |
            |    val batchElapsedTime = System.nanoTime - batchStartTime
            |    runningTime += batchElapsedTime
            |    logWriter.println(s"###   Batch $${i}: $${(batchElapsedTime / 1000000L)} ms", true)
            |  }
            |  val endTime = System.nanoTime
            |
            |  logWriter.println(s"###   Running time: $${(runningTime / 1000000L)} ms") 
            |  logWriter.println(s"###   Total time (running + hsync): $${((endTime - startTime) / 1000000)} ms")
            |  logWriter.println("### PROCESSING END", true)
            |}""".stripMargin
      }
      else {
        val sUpdateBlocks =
          if (OPTIMIZATION_PIPELINE_COMPUTATION) emitBlocks(updateBlocks)
          else emitBlocksNoPipeline(updateBlocks)
        val sUpdateBatchArgs = deltaMapInfo.map { case (name, _) =>
            s"${name}: ${impl.codegen.storeType(ctx0(name)._1)}"
          }.mkString(", ")

        s"def onBatchUpdate($sUpdateBatchArgs) = { ${block(ind(sUpdateBlocks))} }"
      }

    val sLocalMaps = emitMaps(emitLocalMap, localMaps.toSeq)

    s"""|$sLocalMaps
        |
        |$sProcessFn
        | 
        |def onSystemReady() = { ${block(sSystemReadyBlocks)} }
        |""".stripMargin
  }
}
