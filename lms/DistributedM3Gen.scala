package ddbt.codegen

import ddbt.codegen.lms._
import ddbt.ast._

/**
  * Creates a distributed M3 program.
  *
  * @author Milos Nikolic, Mohammad Dashti
  */
class DistributedM3Gen(cls: String = "Query", impl: LMSExpGen) 
    extends LMSGen(cls, impl) with IScalaGen {
  
  import ddbt.ast.M3._
  import ddbt.lib.Utils.{ ind, block, tup, fresh, freshClear } // common functions
  import ManifestHelper.{man,zero,manEntry,manStore}
  import impl.Rep

  
  //----------
  case class MapInfo(name: String, tp: Type, keys: List[(String, Type)], 
                     expr: Expr, locality: LocalityType, storeType: StoreType,
                     linkMap: Boolean = false)
  
  val mapInfo = collection.mutable.Map[String, MapInfo]()  
  
  //----------

  abstract sealed class Transformer { 
    var expr: Expr

    def rename(mapping: Map[String, String]): Unit = expr = expr.rename(mapping)
  }
  case class DefaultTransformer(var expr: Expr) extends Transformer {
    override def toString = ""
  }
  case class ScatterTransformer(var expr: Expr, val pkeys: List[(String, Type)]) extends Transformer {
    assert(expr.locality match { 
      case Some(LocalExp) => true 
      case _ => false 
    }, "ScatterTransformer: Locality check failed")
    assert(mapInfo(expr.asInstanceOf[MapRef].name).storeType match {
      case PartitionStore(_) => true  
      case _ => false
    }, "ScatterTransformer: Store type check failed")

    override def toString = "SCATTER<" + pkeys.mkString(", ") + ">"
  }
  case class RepartitionTransformer(var expr: Expr, val pkeys: List[(String, Type)]) extends Transformer {
    assert(expr.locality match { 
      case Some(DistByKeyExp(_)) | Some(DistRandomExp) => true 
      case _ => false 
    }, "RepartitionTransformer: Locality check failed")
    assert(mapInfo(expr.asInstanceOf[MapRef].name).storeType match {
      case PartitionStore(_) => true 
      case _ => false
    }, "RepartitionTransformer: Store type check failed")      

    override def toString = "REPARTITION<" + pkeys.mkString(", ") + ">"
  }
  case class GatherTransformer(var expr: Expr) extends Transformer {
    assert(expr.locality match { 
      case Some(DistByKeyExp(_)) | Some(DistRandomExp) => true 
      case _ => false 
    }, "GatherTransformer: Locality check failed")
    assert(mapInfo(expr.asInstanceOf[MapRef].name).storeType match {
      case PartitionStore(_) | LogStore => true 
      case _ => false
    }, "GatherTransformer: Store type check failed")

    override def toString = "GATHER"
  }
  case class IndexStoreTransformer(var expr: Expr) extends Transformer { 
    override def toString = "TO_INDEX" 
  }
  case class LogStoreTransformer(var expr: Expr) extends Transformer { 
    override def toString = "TO_LOG" 
  }
  case class PartitionStoreTransformer(var expr: Expr, val pkeys: List[(String, Type)]) extends Transformer { 
    override def toString = "TO_PARTITION<" + pkeys.mkString(", ") + ">"
  }

  //----------

  abstract sealed class ExecutionMode
  case object LocalMode extends ExecutionMode { override def toString = "LOCAL" }
  case object DistributedMode extends ExecutionMode { override def toString = "DISTRIBUTED" }

  def execMode(locality: LocalityType): ExecutionMode = locality match {
    case LocalExp => LocalMode
    case DistByKeyExp(_) | DistRandomExp => DistributedMode
  }
  //----------

  val sSparkObject = cls
  val sLocalMapContextClass  = s"${cls}LocalMapContext"
  val sGlobalMapContextClass = s"GlobalMapContext[${sLocalMapContextClass}]"
  val sEscapeFn = "context.become(receive_skip)"

  //----------

  case class Statement(var lhsMap: MapRef, val rhsTransformer: Transformer, 
      var initTransformer: Option[Transformer], val opMap: OpMap, val execMode: ExecutionMode) {
    
    def rhsMapNames = 
      rhsTransformer.expr.collect { case m: MapRef => List(m.name) }.toSet ++
      initTransformer.map(_.expr.collect { case m: MapRef => List(m.name) }.toSet).getOrElse(Set())

    def commute(that: Statement): Boolean = 
      (!that.rhsMapNames.contains(this.lhsMap.name) && 
       !this.rhsMapNames.contains(that.lhsMap.name))

    def rename(mapping: Map[String, String]): Unit = {     // renaming only map names
      lhsMap = lhsMap.rename(mapping).asInstanceOf[MapRef]
      rhsTransformer.rename(mapping)
      initTransformer.map(_.rename(mapping))
    }

    override def toString = {
      val initExpr = initTransformer.map(":(" + _.expr + ")").getOrElse("") 
      s"${execMode} ${lhsMap} ${initExpr} ${opMap} ${rhsTransformer}(${rhsTransformer.expr});"
    }

    def toShortString = {
      val rhsList = rhsMapNames.mkString(", ")
      s"${execMode} ${lhsMap.name} ${opMap} ${rhsTransformer} { ${rhsList} }"
    }
  }

  object Statement {

    def transformToLog(prefix: String, rhsMap: MapRef): Statement = {
      val lhsName = fresh(prefix + "ToLog")
      val rhsInfo = mapInfo(rhsMap.name)
      val rhsStoreType = LogStore
      val lhsInfo = MapInfo(lhsName, rhsInfo.tp, rhsMap.keys, rhsInfo.expr, rhsInfo.locality, rhsStoreType)
      mapInfo += ((lhsInfo.name, lhsInfo))
      val lhsRef = MapRef(lhsInfo.name, lhsInfo.tp, lhsInfo.keys)
      lhsRef.locality = Some(lhsInfo.locality)
      lhsRef.isTemp = true
      Statement(lhsRef, LogStoreTransformer(rhsMap), None, OpSet, execMode(lhsInfo.locality))
    }

    def transformToPartition(prefix: String, rhsMap: MapRef, pkeys: List[(String, Type)]): Statement = {
      val lhsName = fresh(prefix + "ToPartition")
      val rhsInfo = mapInfo(rhsMap.name)
      val rhsStoreType = PartitionStore(pkeys.map(k => rhsMap.keys.indexOf(k)))
      val lhsInfo = MapInfo(lhsName, rhsInfo.tp, rhsMap.keys, rhsInfo.expr, rhsInfo.locality, rhsStoreType)
      mapInfo += ((lhsInfo.name, lhsInfo))
      val lhsRef = new MapRef(lhsInfo.name, lhsInfo.tp, lhsInfo.keys)
      lhsRef.locality = Some(lhsInfo.locality)
      lhsRef.isTemp = true
      Statement(lhsRef, PartitionStoreTransformer(rhsMap, pkeys), None, OpSet, execMode(lhsInfo.locality))
    }

    def transformToIndex(prefix: String, rhsMap: MapRef): Statement = {
      val lhsName = fresh(prefix + "ToIndex")
      val rhsInfo = mapInfo(rhsMap.name)
      val rhsStoreType = IndexedStore
      val lhsInfo = MapInfo(lhsName, rhsInfo.tp, rhsMap.keys, rhsInfo.expr, rhsInfo.locality, rhsStoreType)
      mapInfo += ((lhsInfo.name, lhsInfo))
      val lhsRef = new MapRef(lhsInfo.name, lhsInfo.tp, lhsInfo.keys)
      lhsRef.locality = Some(lhsInfo.locality)
      lhsRef.isTemp = true
      Statement(lhsRef, IndexStoreTransformer(rhsMap), None, OpSet, execMode(lhsInfo.locality))
    }

    def createScatter(expr: Expr, pkeys: List[(String, Type)]): List[Statement] = {
      val (iv, ov) = expr.schema
      if (iv != Nil) sys.error("Distributed map (Scatter) with input vars")
      /* DIST_SCATTER := SCATTER(EXPR, PKEYS) gets transformed into
       *
       * LOCAL_SCATTER    := EXPR unless EXPR == MapRef
       * LOCAL_PARTITIONS := SPLIT_INTO_PARTITIONS(LOCAL_SCATTER)
       * DIST_PARTITIONS  := SCATTER(LOCAL_PARTITIONS)
       * DIST_SCATTER     := LOG_TO_INDEX(DIST_PARTITIONS)       
       */
      val (localRef, localStmt) = expr match {
        case m: MapRef if mapInfo(m.name).storeType == IndexedStore => (m, Nil)
        case m: MapRef if mapInfo(m.name).storeType != IndexedStore => sys.error("Transformation not implemented yet")
        case _ =>
          val localName = fresh("scatter")
          val localLocality = expr.locality match {
            case Some(LocalExp) => LocalExp
            case Some(DistByKeyExp(_)) | Some(DistRandomExp) | None => sys.error("Scattering of a distributed expression")
          }
          val localInfo = MapInfo(localName, expr.tp, ov, expr, localLocality, IndexedStore)
          mapInfo += ((localInfo.name, localInfo))
          val localRef = new MapRef(localInfo.name, localInfo.tp, localInfo.keys)
          localRef.locality = Some(localInfo.locality)
          localRef.isTemp = true
          val localStmt = Statement(localRef, DefaultTransformer(expr), None, OpSet, LocalMode)
          (localRef, List(localStmt))
      }
      val toPartitionStmt = Statement.transformToPartition("scatter", localRef, pkeys)
      val scatterStmt = {        
        val distName = fresh("scatter")
        val distInfo = MapInfo(distName, expr.tp, ov, expr, DistByKeyExp(pkeys), LogStore, true)
        mapInfo += ((distInfo.name, distInfo))
        val distRef = new MapRef(distInfo.name, distInfo.tp, distInfo.keys)
        distRef.locality = Some(distInfo.locality)
        distRef.isTemp = true
        Statement(distRef, ScatterTransformer(toPartitionStmt.lhsMap, pkeys), None, OpSet, LocalMode)
      }
      val toStoreStmt = Statement.transformToIndex("scatter", scatterStmt.lhsMap)
      localStmt ++ List(toPartitionStmt, scatterStmt, toStoreStmt)
    }

    def createRepartition(expr: Expr, pkeys: List[(String, Type)]): List[Statement] = {
      val (iv, ov) = expr.schema
      if (iv != Nil) sys.error("Distributed map (Repartition) with input vars")
      /* DIST_DEST := REPARTITION(EXPR, PKEYS) gets transformed into
       *
       * DIST_SRC := EXPR unless EXPR == MapRef
       * DIST_PARTITIONS_SRC := INDEX_TO_PART(DIST_SRC)
       * !!! TODO: PRE-AGGREGATION OF PARTITIONS
       * DIST_PARTITIONS_DST := REPARTITION(DIST_PARTITIONS_SRC)
       * DIST_DEST           := MERGE_PARTITIONS(DIST_PARTITIONS_DST)
       */
      val (distSrcRef, distSrcStmt) = expr match {
        case m: MapRef if mapInfo(m.name).storeType == IndexedStore => (m, Nil)
        case m: MapRef if mapInfo(m.name).storeType != IndexedStore => sys.error("Transformation not implemented yet")
        case _ =>  
          val distName = fresh("repartition")
          val distLocality = expr.locality match {
            case Some(DistByKeyExp(pk)) => DistByKeyExp(pk)
            case Some(DistRandomExp) => DistRandomExp
            case Some(LocalExp) | None => sys.error("Repartitioning of a local expression")
          }
          val distInfo = MapInfo(distName, expr.tp, ov, expr, distLocality, IndexedStore)
          mapInfo += ((distInfo.name, distInfo))
          val distRef = new MapRef(distInfo.name, distInfo.tp, distInfo.keys)    
          distRef.locality = Some(distInfo.locality)
          distRef.isTemp = true    
          val distStmt = Statement(distRef, DefaultTransformer(expr), None, OpSet, DistributedMode)
          (distRef, List(distStmt))
      }
      val srcToPartitionStmt = Statement.transformToPartition("repartition", distSrcRef, pkeys)
      val repartitionStmt = {
        val distName = fresh("repartition")
        val distStoreType = PartitionStore(pkeys.map(k => ov.indexOf(k)))
        val distInfo = MapInfo(distName, expr.tp, ov, expr, DistByKeyExp(pkeys), distStoreType, true)
        mapInfo += ((distInfo.name, distInfo))
        val distRef = new MapRef(distInfo.name, distInfo.tp, distInfo.keys)
        distRef.locality = Some(distInfo.locality)
        distRef.isTemp = true
        Statement(distRef, RepartitionTransformer(srcToPartitionStmt.lhsMap, pkeys), None, OpSet, LocalMode)
      }
      val dstToIndexStmt = Statement.transformToIndex("repartition", repartitionStmt.lhsMap)
      (distSrcStmt ++ List(srcToPartitionStmt, repartitionStmt, dstToIndexStmt))
    }

    def createGather(expr: Expr): List[Statement] = {
      val (iv, ov) = expr.schema
      if (iv != Nil) sys.error("Distributed map (Gather) with input vars")
      /* LOCAL_GATHER := GATHER(DIST_GATHER) gets transformed into
       *
       * DIST_GATHER      := EXPR unless EXPR == MapRef
       * DIST_PARTITIONS  := INDEX_TO_LOG(DIST_GATHER)
       * !!! TODO: PRE-AGGREGATION OF PARTITIONS
       * LOCAL_PARTITIONS := GATHER(DIST_PARTITIONS)
       * LOCAL_GATHER     := MERGE_PARTITIONS(LOCAL_PARTITIONS)  
       */
       val (distRef, distStmt) = expr match {
        case m: MapRef if mapInfo(m.name).storeType == IndexedStore => (m, Nil)
        case m: MapRef if mapInfo(m.name).storeType != IndexedStore => sys.error("Transformation not implemented yet")
        case _ =>  
          val distName = fresh("gather")
          val distLocality = expr.locality match {
            case Some(DistByKeyExp(pk)) => DistByKeyExp(pk)
            case Some(DistRandomExp) => DistRandomExp
            case Some(LocalExp) | None => sys.error("Gathering of a local expression")
          }
          val distInfo = MapInfo(distName, expr.tp, ov, expr, distLocality, IndexedStore)
          mapInfo += ((distInfo.name, distInfo))
          val distRef = new MapRef(distInfo.name, distInfo.tp, distInfo.keys)
          distRef.locality = Some(distInfo.locality)
          distRef.isTemp = true
          val distStmt = Statement(distRef, DefaultTransformer(expr), None, OpSet, DistributedMode)
          (distRef, List(distStmt))
        }
        val toLogStmt = Statement.transformToLog("gather", distRef)
        val gatherStmt = {        
          val partName = fresh("gather")
          val partInfo = MapInfo(partName, expr.tp, ov, expr, LocalExp, PartitionStore(Nil), true)
          mapInfo += ((partInfo.name, partInfo))
          val partRef = new MapRef(partInfo.name, partInfo.tp, partInfo.keys)
          partRef.locality = Some(partInfo.locality)
          partRef.isTemp = true
          Statement(partRef, GatherTransformer(toLogStmt.lhsMap), None, OpSet, LocalMode)
        }
        val toIndexStmt = Statement.transformToIndex("gather", gatherStmt.lhsMap)
        distStmt ++ List(toLogStmt, gatherStmt, toIndexStmt)
    }
  }

  case class StatementBlock(val execMode: ExecutionMode, val stmts: List[Statement]) {
    def lhsMapNames = stmts.map(_.lhsMap.name).toSet
    def rhsMapNames = stmts.flatMap(_.rhsMapNames).toSet
    def mapNames = lhsMapNames ++ rhsMapNames

    def commute(that: StatementBlock): Boolean = 
      stmts.forall(lhs => that.stmts.forall(rhs => lhs.commute(rhs)))

    override def toString = 
      s"""|>> BLOCK START (${execMode})
          |${ind(stmts.map(_.toString).mkString("\n"))}
          |<< BLOCK END (${execMode})
          |""".stripMargin

    def toShortString = 
      s"""|>> BLOCK START (${execMode})
          |${ind(stmts.map(_.toShortString).mkString("\n"))}
          |<< BLOCK END (${execMode})
          |""".stripMargin
  }

  object Optimizer {

    def optBlockFusion = new Function1[List[StatementBlock], List[StatementBlock]] {
      def apply(blocks: List[StatementBlock]): List[StatementBlock] = blocks match {
        case Nil => Nil
        case head :: tail =>
          val (newHead, newTail) = tail.foldLeft (head, List[StatementBlock]()) {
            case ((b1, rhs), b2) => 
              if (b1.execMode == b2.execMode && rhs.forall(_.commute(b2)))
                (StatementBlock(b1.execMode, b1.stmts ++ b2.stmts), rhs)
              else
                (b1, rhs ++ List(b2))  
          }
          if (head == newHead) newHead :: apply(tail)
          else apply(newHead :: newTail)
      }
    }
    
    // An alternative block fusion
    def optBlockFusion2 = new Function1[List[StatementBlock], List[StatementBlock]] {
      def apply(blocks: List[StatementBlock]): List[StatementBlock] = blocks match {
        case Nil => Nil
        case List(b) => List(b)
        case head :: tail => 
          val (lhs, curr, rhs) = tail.foldLeft (List[StatementBlock](), head, List[StatementBlock]()) { 
            case ( (lhsBlocks, blockA, rhsBlocks), blockB ) => (blockA, blockB) match {
              
              case (a @ StatementBlock(execModeA, stmtsA), b @ StatementBlock(execModeB, stmtsB)) 
                   if (execModeA == execModeB) =>  
                if (rhsBlocks.forall(_.commute(b)))        // Try to push b to the left 
                  (lhsBlocks, StatementBlock(execModeA, stmtsA ++ stmtsB), rhsBlocks)  
                else if (rhsBlocks.forall(a.commute))      // Try to push a to the right
                  (lhsBlocks ++ rhsBlocks, StatementBlock(execModeA, stmtsA ++ stmtsB), Nil)
                else 
                  (lhsBlocks, blockA, rhsBlocks ++ List(blockB))

              case _ => (lhsBlocks, blockA, rhsBlocks ++ List(blockB))
            }
          } 
          val newBlocks = lhs ++ (curr :: rhs)
          if (blocks.length > newBlocks.length) apply(newBlocks)
          else head :: apply(tail)
      }  
    }

    def optCSE = new Function1[List[Statement], List[Statement]] {
      var mapDefs = Map[String, (List[(String, Type)], Transformer)]()
      var equiMaps = Map[String, List[String]]()

      def mapping = equiMaps.mapValues(_.head)

      def invalidate(name: String): Unit = {
        equiMaps = (equiMaps - name).mapValues(_.filterNot(_ == name))
        mapDefs = mapDefs - name
        val affected = mapDefs.flatMap { case (n, (_, t)) => 
          val rhsMaps = t.expr.collect { case m: MapRef => List(m.name) }.toSet
          if (rhsMaps.contains(name)) List(n) else Nil
        }
        affected.foreach(invalidate)
      }

      def rewrite(map: MapRef, op: OpMap, transformer: Transformer): Unit = {
        // invalidate map definitions
        invalidate(map.name)
        // rename RHS expression
        transformer.rename(mapping)        

        if (op == OpSet) {
          // Update equiMaps - try to find equivalent expression definitions          
          val ta = transformer
          val ka = map.keys
          val matchingNames = mapDefs.filter { case (_, (kb, tb)) => (ta, tb) match {
            case (DefaultTransformer(e1), DefaultTransformer(e2)) => 
              e1.cmp(e2) match {
                case Some(mapping) => ka.map(mapping.apply) == kb
                case _ => false
              }
            case (ScatterTransformer(e1, pk1), ScatterTransformer(e2, pk2)) =>
              e1.cmp(e2) match {
                case Some(mapping) => ka.map(mapping.apply) == kb &&
                                      pk1.map(mapping.apply) == pk2
                case _ => false
              }
            case (RepartitionTransformer(e1, pk1), RepartitionTransformer(e2, pk2)) =>
              e1.cmp(e2) match {
                case Some(mapping) => ka.map(mapping.apply) == kb && 
                                      pk1.map(mapping.apply) == pk2
                case _ => false
              }              
            case (GatherTransformer(e1), GatherTransformer(e2)) =>
              e1.cmp(e2) match {
                case Some(mapping) => ka.map(mapping.apply) == kb
                case _ => false
              }
            case (IndexStoreTransformer(e1), IndexStoreTransformer(e2)) =>
              e1.cmp(e2) match {
                case Some(mapping) => ka.map(mapping.apply) == kb
                case _ => false
              }
            case (LogStoreTransformer(e1), LogStoreTransformer(e2)) =>
              e1.cmp(e2) match {
                case Some(mapping) => ka.map(mapping.apply) == kb
                case _ => false
              }
            case (PartitionStoreTransformer(e1, pk1), PartitionStoreTransformer(e2, pk2)) =>
              e1.cmp(e2) match {
                case Some(mapping) => ka.map(mapping.apply) == kb && 
                                      pk1.map(mapping.apply) == pk2
                case _ => false
              }
            case _ => false
          }}.map(_._1).toList
          if (matchingNames.length == 0) equiMaps = equiMaps + ((map.name, List(map.name)))
          else {
            val equiClass = equiMaps(matchingNames.head) ++ List(map.name)
            equiMaps = equiMaps ++ (map.name :: matchingNames).map((_, equiClass))
          }
          // Create new map definition, avoid aliases
          transformer match {
            case DefaultTransformer(m: MapRef) 
              if mapDefs.contains(m.name) && mapDefs(m.name)._1 == map.keys =>
              mapDefs = mapDefs + ((map.name, (map.keys, mapDefs(m.name)._2)))
            case _ => mapDefs = mapDefs + ((map.name, (map.keys, transformer)))
          }
        }
      }

      def apply(stmts: List[Statement]): List[Statement] = {
        stmts.foreach { stmt => {
          rewrite(stmt.lhsMap, stmt.opMap, stmt.rhsTransformer)
          stmt.initTransformer.map(t => rewrite(stmt.lhsMap, OpSet, t))
        }}
        stmts
      }
    }

    def optDCE = new Function1[List[Statement], List[Statement]] {
      def isReferenced(map: MapRef, stmts: List[Statement]): Boolean = stmts match {
        case Nil => false
        case head :: tail =>
          if (map == head.lhsMap) !(head.opMap == OpSet)    
          else (head.rhsMapNames.contains(map.name) || isReferenced(map, tail))
      }

      def deadStatements(stmts: List[Statement]): List[Statement] = stmts match {
        case Nil => Nil
        case head :: tail =>
          if (head.lhsMap.isTemp && !isReferenced(head.lhsMap, tail)) head :: deadStatements(tail) 
          else deadStatements(tail)
      }

      def apply(stmts: List[Statement]): List[Statement] = {
        val deadStmts = deadStatements(stmts).toSet
        stmts.filterNot(deadStmts.contains)
      }
    }

    def optDropTopLevelStmts = new Function1[List[Statement], List[Statement]] {

      def topLevelStatements(stmts: List[Statement]): List[Statement] = stmts match {
        case Nil => Nil
        case head :: tail =>
          val isReferenced = tail.exists(_.rhsMapNames.contains(head.lhsMap.name))
          if (isReferenced) topLevelStatements(tail)
          else head :: topLevelStatements(tail)
      }

      def apply(stmts: List[Statement]): List[Statement] = {
        val topLevelReeval = topLevelStatements(stmts).filter(_.opMap == OpSet)
        val uniqueReeval = topLevelReeval.groupBy(_.lhsMap.name).map(_._2.head)
        val topLevelMaps = uniqueReeval.map(_.lhsMap.name).toSet
        stmts.filterNot(s => topLevelMaps.contains(s.lhsMap.name)) ++ uniqueReeval
      }
    }

    def optimize(stmts: List[Statement]): List[Statement] = {
      val optStmts = (optCSE andThen optDCE andThen optDropTopLevelStmts)(stmts)
      if (stmts == optStmts) optStmts else optimize(optStmts)
    }
  }

  // CLASS DEFINITIONS FOR DISTRIBUTED EXECUTION (END)


  def prepareStatement(stmt: Stmt): List[Statement] = stmt match {
    case StmtMap(map, expr, op, ivc) => 
      val mapInf = mapInfo(map.name)
      map.locality = mapInf.locality match {
        case LocalExp => Some(LocalExp)
        case DistRandomExp => Some(DistRandomExp)
        case DistByKeyExp(pk) => Some(DistByKeyExp(pk.map(k => map.keys(mapInf.keys.indexOf(k))))) 
      }
      val (aStmts, aTransformer) = {
        val (aStmts, aExpr) = prepareExpression(expr)
        (aStmts, DefaultTransformer(aExpr))
      }

      // Sanity check
      assert(        
        aTransformer.expr.locality match {
          case Some(LocalExp) => (map.locality == Some(LocalExp))
          case Some(DistRandomExp) => (map.locality == Some(DistRandomExp))
          case Some(DistByKeyExp(pk1)) => map.locality match {
            case Some(DistByKeyExp(pk2)) if pk1 == pk2 => true
            case _ => false
          }
          case None => true          
        })

      val (bStmts, bTransformer) = ivc.map(e => {
        val (bStmts, bExpr) = prepareExpression(e)       
      
        // Sanity check
        assert(
          bExpr.locality match {
            case Some(LocalExp) => (map.locality == Some(LocalExp))
            case Some(DistRandomExp) => (map.locality == Some(DistRandomExp))
            case Some(DistByKeyExp(pk1)) => map.locality match {
              case Some(DistByKeyExp(pk2)) if pk1 == pk2 => true
              case _ => false
            }
            case None => true          
          })        

        (bStmts, Some(DefaultTransformer(bExpr)))
      }).getOrElse((Nil, None))

      val execMode = map.locality match {
        case Some(LocalExp) => LocalMode
        case Some(DistByKeyExp(_)) | Some(DistRandomExp) => DistributedMode
        case _ => sys.error ("Map without locality information") 
      }
      ( aStmts ++ bStmts ++ List(Statement(map, aTransformer, bTransformer, op, execMode)))
    case m: MapDef => Nil  
  }

  def prepareExpression(expr: Expr): (List[Statement], Expr) = expr match {
    case Const(tp, v) => (Nil, expr)
    case Ref(name) => (Nil, expr)
    case m @ MapRef(name, tp, keys) => 
      val map = mapInfo(name)
      m.locality  = map.locality match {
        case LocalExp => Some(LocalExp)
        case DistRandomExp => Some(DistRandomExp)
        case DistByKeyExp(pk) => Some(DistByKeyExp(pk.map(k => keys(map.keys.indexOf(k)))))
      }
      (Nil, m)
    case MapRefConst(name, keys) => (Nil, expr)
    case DeltaMapRefConst(name, keys) => (Nil, expr)
    case Lift(name, e) => 
      val (stmts, subexp) = prepareExpression(e)
      (stmts, Lift(name, subexp))
    case AggSum(ks, e) => 
      val (stmts, subexp) = prepareExpression(e)
      (stmts, AggSum(ks, subexp))
    case Mul(l, r) => 
      val (la, le) = prepareExpression(l)
      val (ra, re) = prepareExpression(r)
      val newExpr = Mul(le, re)
      newExpr.tp = expr.tp
      (la ++ ra, newExpr)
    case a @ Add(l, r) =>           
      val (la, le) = prepareExpression(l)
      val (ra, re) = prepareExpression(r)
      val newExpr = Add(le, re)
      newExpr.tp = a.tp
      (la ++ ra, newExpr)
    case Exists(e) => 
      val (stmts, subexp) = prepareExpression(e)
      (stmts, Exists(subexp))
    case Apply(fn, tp, as) => 
      val (stmts, args) = as.map(prepareExpression).unzip
      (stmts.flatten, Apply(fn, tp, args))
    case Cmp(l, r, op) => 
      val (la, le) = prepareExpression(l)
      val (ra, re) = prepareExpression(r)
      (la ++ ra, Cmp(le, re, op))
    case Tuple(es) => 
      val (stmts, args) = es.map(prepareExpression).unzip
      val newExpr = Tuple(args)
      newExpr.tp = expr.tp
      (stmts.flatten, newExpr)
    case TupleLift(ns, e) =>     
      val (stmts, subexp) = prepareExpression(e)
      (stmts, TupleLift(ns, subexp))    
    case Repartition(ks, e) => 
      val (stmts, subexp0) = prepareExpression(e)
      val (iv, ov) = expr.schema
      if (iv != Nil) sys.error("Repartitioning a map with input vars: " + e)
      val subexp = subexp0 match {
        case a @ Add(l, r) =>
          val newAdd = Add(l, r)
          newAdd.tp = a.tp
          newAdd
        case _ => subexp0
      }
      subexp.locality match {
        case Some(LocalExp) =>
          val scatterStmts = Statement.createScatter(subexp, ks)
          (stmts ++ scatterStmts, scatterStmts.last.lhsMap)
        case Some(DistRandomExp) =>
          val repartStmts = Statement.createRepartition(subexp, ks)
          (stmts ++ repartStmts, repartStmts.last.lhsMap)
        case Some(DistByKeyExp(pkeys)) if (pkeys != ks) =>
          val repartStmts = Statement.createRepartition(subexp, ks)
          (stmts ++ repartStmts, repartStmts.last.lhsMap)
        case Some(DistByKeyExp(_)) | None => (stmts, subexp)
      }
    case Gather(e) => 
      val (stmts, subexp0) = prepareExpression(e)
      val (iv, ov) = expr.schema
      if (iv != Nil) sys.error("Gathering a map with input vars")
      val subexp = subexp0 match {
        case a @ Add(l, r) =>
          val newAdd = Add(l, r)
          newAdd.tp = a.tp
          newAdd
        case _ => subexp0
      }
      subexp.locality match {
        case Some(DistByKeyExp(_)) | Some(DistRandomExp) =>
          val gatherStmts = Statement.createGather(subexp)
          (stmts ++ gatherStmts, gatherStmts.last.lhsMap)
        case Some(LocalExp) | None => (stmts, subexp) 
      }
  }

  def createBlocks(stmts: List[Statement]): List[StatementBlock] = 
    stmts.map(s => StatementBlock(s.execMode, List(s)))

  def reorderTriggers(triggers: List[Trigger]): List[Trigger] = triggers
}