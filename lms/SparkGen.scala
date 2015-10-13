package ddbt.codegen

import ddbt.codegen.lms._
import ddbt.ast._
import ddbt.lib._

/**
  * Generates code for the Spark parallel backend.
  *
  * @author Milos Nikolic, Mohammad Dashti
  */
class LMSSparkGen(cls: String = "Query") extends LMSGen(cls, SparkExpGen) 
                                            with IScalaGen {
  
  import ddbt.ast.M3._
  import ddbt.Utils.{ind, block, tup, fresh, freshClear} // common functions
  import ManifestHelper.{man,zero,manEntry,manStore}
  import ddbt.lib.store._
  import impl.Rep

  
  //----------
  case class MapInfo(name: String, tp: Type, keys: List[(String, Type)], 
                     expr: Expr, locality: LocalityType, storeType: StoreType,
                     linkMap: Boolean = false)
  
  val mapInfo = collection.mutable.Map[String, MapInfo]()  
  var deltaMapInfo = List[(String, MapInfo)]() 
  
  val linkMaps  = collection.mutable.Set[MapInfo]()
  val localMaps = collection.mutable.Set[MapInfo]()
  val distributedMaps = collection.mutable.Set[MapInfo]()
  
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
    
    //// An alternative block fusion
    // def optBlockFusion2 = new Function1[List[StatementBlock], List[StatementBlock]] {
    //   def apply(blocks: List[StatementBlock]): List[StatementBlock] = blocks match {
    //     case Nil => Nil
    //     case List(b) => List(b)
    //     case head :: tail => 
    //       val (lhs, curr, rhs) = tail.foldLeft (List[StatementBlock](), head, List[StatementBlock]()) { 
    //         case ( (lhsBlocks, blockA, rhsBlocks), blockB ) => (blockA, blockB) match {
              
    //           case (a @ StatementBlock(execModeA, stmtsA), b @ StatementBlock(execModeB, stmtsB)) 
    //                if (execModeA == execModeB) =>  
    //             if (rhsBlocks.forall(_.commute(b)))        // Try to push b to the left 
    //               (lhsBlocks, StatementBlock(execModeA, stmtsA ++ stmtsB), rhsBlocks)  
    //             else if (rhsBlocks.forall(a.commute))      // Try to push a to the right
    //               (lhsBlocks ++ rhsBlocks, StatementBlock(execModeA, stmtsA ++ stmtsB), Nil)
    //             else 
    //               (lhsBlocks, blockA, rhsBlocks ++ List(blockB))

    //           case _ => (lhsBlocks, blockA, rhsBlocks ++ List(blockB))
    //         }
    //       } 
    //       val newBlocks = lhs ++ (curr :: rhs)
    //       if (blocks.length > newBlocks.length) apply(newBlocks)
    //       else head :: apply(tail)
    //   }  
    // }

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

    def optimize(stmts: List[Statement]): List[Statement] = {
      val optStmts = (optCSE andThen optDCE)(stmts)
      if (stmts == optStmts) optStmts else optimize(optStmts)
    }
  }

  // CLASS DEFINITIONS FOR DISTRIBUTED EXECUTION (END)

  val partitioningMap = List[(String, Option[List[Int]])](
      ("QUERY3",                   None), //Some(List(0))),
      ("QUERY3LINEITEM1",          Some(List(0))),
      ("QUERY3LINEITEM1CUSTOMER1", Some(List(0))),
      ("QUERY3ORDERS1_P_1",        Some(List(0))),    // CK
      ("QUERY3ORDERS1_P_2",        Some(List(0))),
      ("QUERY3CUSTOMER1",          Some(List(0))),    // CK 
      ("QUERY3LINEITEM1_DELTA",    Some(List(0))),
      ("QUERY3ORDERS1_DELTA",      Some(List(0))),
      ("QUERY3CUSTOMER1_DELTA",    Some(List(0)))
  ).toMap

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
      val (bStmts, bTransformer) = ivc.map(e => {
        val (bStmts, bExpr) = prepareExpression(e)
        (bStmts, Some(DefaultTransformer(bExpr)))
      }).getOrElse((Nil, None))
      val execMode = aTransformer.expr.locality match {
        case Some(LocalExp) | None => LocalMode
        case Some(DistByKeyExp(_)) | Some(DistRandomExp) => DistributedMode
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

  // SPARK CODE GENERATION - HERE WE PRODUCE SOME STRINGS

  override def apply(s0: System): String = {
    val tables = s0.sources.filterNot(_.stream).map(_.schema.name).toSet
    // Create MapInfo definitions and load partitioning information
    mapInfo ++= s0.maps.map { case MapDef(name, tp, keys, expr, loc) =>
      // All static tables are local
      val locality = if (!tables.contains(name)) loc else LocalExp
      val mapInfo = MapInfo(name, tp, keys, expr, locality, IndexedStore)
      (mapInfo.name, mapInfo)
    }
    // Create delta MapInfo definitions
    deltaMapInfo = s0.triggers.flatMap { _.evt match {
      case EvtBatchUpdate(s @ Schema(name, _)) => 
        val keys = s0.sources.filter(_.schema.name == name)(0).schema.fields
        val mapInfo = MapInfo(s.deltaName, TypeLong, keys, DeltaMapRefConst(name, keys), LocalExp, IndexedStore)
        List((mapInfo.name, mapInfo))        
      case EvtAdd(_) | EvtDel(_) => 
        sys.error("Distributed programs run only in batch mode.")
      case _ => Nil
    }}    
    mapInfo ++= deltaMapInfo

    val updateStmts = reorderTriggers(s0.triggers).flatMap { 
      case Trigger(EvtBatchUpdate(_), stmts) => stmts.flatMap(prepareStatement)
      case _ => Nil
    }
    val systemReadyStmts = s0.triggers.flatMap { 
      case Trigger(EvtReady, stmts) => stmts.flatMap(prepareStatement)
      case _ => Nil
    }

    // Optimize statements
    val optUpdateStmts = Optimizer.optimize(updateStmts)
    val optSystemReadyStmts = Optimizer.optimize(systemReadyStmts)

    // Create statement blocks 
    val updateBlocks = createBlocks(optUpdateStmts)
    val systemReadyBlocks = createBlocks(optSystemReadyStmts)

    // Optimize statement blocks
    val optUpdateBlocks = Optimizer.optBlockFusion(updateBlocks)
    optUpdateBlocks.map(b => java.lang.System.err.println("UPDATE\n" + b.toString))
    val optSystemReadyBlocks = Optimizer.optBlockFusion(systemReadyBlocks)
    optSystemReadyBlocks.map(b => java.lang.System.err.println("SYSREADY\n" + b.toString))

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
    val sProgram = sMainClass + sDataStructures + sMapContext + sActorClass
    freshClear()
    clearOut
    sProgram
  }

  def emitBlocks(blocks: List[StatementBlock]): String = {
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
              |  .mapPartitions(_.map { w =>
              |    (
              |${ind(unwrap, 3)}
              |    )
              |  }, true)""".stripMargin
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
              |${ind(wrap, 2)}
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
            |${ind(strRenaming, 2)}
            |${ind(strDistBlock, 2)}
            |}""".stripMargin
    }.mkString("\n")
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
      "import org.apache.spark.SparkContext._"
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
      "println(\"%s:\\n\" + M3Map.toStr(res(%d)) + \"\\n\")".format(q.name, i)
    }.mkString("\n")

  protected def emitMainClass(s0: System): String = {
    val sSources = ind(emitSources(s0.sources), 4)
    val sQueryResult = ind(emitQueryResults(s0.queries), 4)
    s"""|import ddbt.lib._ 
        |import akka.actor.Actor
        |$additionalImports
        |
        |object $sSparkObject {
        |  import Helper._
        |
        |  var configFile: String = "/spark.config"
        |  var batchSize: Int = 0
        |  var noOutput: Boolean = false
        |  var logCount: Int = 0
        |  var numPartitions: Int = 0
        |
        |  // Spark related variables
        |  private var cfg: SparkConfig = null
        |  private var sc: SparkContext = null
        |  var ctx: ${sGlobalMapContextClass} = null
        |
        |  def execute(args: Array[String], f: List[Any] => Unit) =
        |    bench(args, (dataset: String, parallelMode: Int, timeout: Long, batchSize: Int) =>
        |      run[$sSparkObject](
        |$sSources, 
        |        parallelMode, timeout, batchSize), f)
        | 
        |  def initContext(sc: SparkContext, numPartitions: Int) {
        |    ctx = new ${sGlobalMapContextClass}(sc, numPartitions,
        |      (id => new ${sLocalMapContextClass}(id, numPartitions)))
        |    ctx.init()
        |  }
        |
        |  def destroyContext() = ctx.destroy()
        |
        |  def main(args: Array[String]) {
        |    val argMap = parseArgs(args)
        |    configFile = argMap.get("configFile").map(_.asInstanceOf[String]).getOrElse(configFile)
        |    batchSize = argMap.get("batchSize").map(_.asInstanceOf[Int]).getOrElse(batchSize)
        |    noOutput = argMap.get("noOutput").map(_.asInstanceOf[Boolean]).getOrElse(noOutput)
        |    logCount = argMap.get("logCount").map(_.asInstanceOf[Int]).getOrElse(logCount)
        |
        |    if (configFile == null) { sys.error("Config file is missing.") }
        |    if (batchSize == 0) { sys.error("Invalid batch size.") }
        |
        |    cfg = new SparkConfig(getClass().getResourceAsStream(configFile))
        |    sc = new SparkContext(cfg.sparkConf.setAppName("$sSparkObject"))
        |    numPartitions = cfg.sparkNumPartitions
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
    val sDistributedMaps = ind(emitMaps(emitDistributedMap, distributedMaps))
    s"""|class $sLocalMapContextClass(val partitionId: Int, numPartitions: Int) {
        |$sDistributedMaps
        |}
        |""".stripMargin
  }
  
  def schemaToArgList(schema: Schema): String = 
    schema.fields.zipWithIndex.map { case ((_, _), i) => "v" + i }.mkString(", ")

  def schemaToParamList(schema: Schema): String = 
    schema.fields.zipWithIndex.map { case ((_, tp), i) => s"v$i: ${tp.toScala}" }.mkString(", ")

  protected def emitEventHandlers(s0: System, skipExec: Boolean): String = {
    val step = 128 // periodicity of timeout verification, must be a power of 2
    val (batchEvents, otherEvents) = s0.triggers.map(_.evt).partition {
      case EvtBatchUpdate(_) => true
      case _ => false
    }
    val sBatchEventHandler = if (batchEvents.size == 0) "" 
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
          case EvtBatchUpdate(s) =>
            val schema = s0.sources.filter(_.schema.name == s.name)(0).schema
            val deltaName = schema.deltaName
            val params = schemaToParamList(schema)
            val addBatchTuple = ind(genAddBatchTuple(deltaName, schema.fields, "vv"), 2)
            s"""|case ("${schema.name}", dataList) => 
                |  dataList.foreach { case List(${params}, vv: TupleOp) =>
                |$addBatchTuple
                |  }""".stripMargin
          case _ => ""
        }.mkString("\n")
        val deltaNames = batchEvents.flatMap {
          case EvtBatchUpdate(s) => List(s.deltaName)
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
            |    Console.println(tuplesProcessed + " tuples processed at " + 
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
        case EvtAdd(schema) => if (skipExec) {
            s"""|case TupleEvent(TupleInsert, "${schema.name}", _) =>
                |  tuplesSkipped += 1
                |""".stripMargin
          }
          else {
            s"""|case TupleEvent(TupleInsert, "${schema.name}", List(${schemaToParamList(schema)})) =>
                |%s
                |  tuplesProcessed += 1
                |  onAdd${schema.name}(${schemaToArgList(schema)})  
                |""".stripMargin
          }
        case EvtDel(schema) =>  if (skipExec) {
            s"""|case TupleEvent(TupleDelete, "${schema.name}", _) =>
                |  tuplesSkipped += 1
                |""".stripMargin
          }
          else {
            """|case TupleEvent(TupleDelete, "${schema.name}", List(${schemaToParamList(schema)})) =>
               |%s
               |  tuplesProcessed += 1
               |  onDel${schema.name}(${schemaToArgList(schema)})  
               |""".stripMargin
          }
        case _ => ""
      }.mkString("\n") 
    }
    (sTupleEventHandler + sBatchEventHandler)
  }

  protected def emitLoadTables(sources: List[Source]): String = 
    sources.filterNot { _.stream }.map { table => {
      val keys = table.schema.fields.zipWithIndex.map { case ((_, t), i) => ("v" + i, t) }
      val tuple = genTuple(keys.map { case (v, t) => (t, v) })
      val (inputStream, adaptor, split) = genStream(table)
      s"""|SourceMux({ 
          |  case TupleEvent(TupleInsert, _, List(${schemaToParamList(table.schema)})) =>
          |${ind(genInitializationFor(table.schema.name, keys, tuple), 2)}
          |  }, Seq((
          |    $inputStream,
          |    $adaptor,
          |    $split
          |))).read""".stripMargin
    }}.mkString("\n")

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

  protected def emitGetSnapshot(queries: List[Query]): String = {
    val sCreateHashMap = queries.map(q => 
      if (q.keys.size > 0) toMapFunction(q) else q.name
    ).mkString(", ")
    s"""|(StreamStat(endTime - startTime, tuplesProcessed, tuplesSkipped), List(
        |${ind(sCreateHashMap)}
        |))""".stripMargin    
  }

  protected def emitActorClass(s0: System, updateBlocks: List[StatementBlock], 
      systemReadyBlocks: List[StatementBlock]): String = {
    // The order of these statements is important
    val sEventHandlersSkip = ind(emitEventHandlers(s0, true), 2)
    val sEventHandler = ind(emitEventHandlers(s0, false), 2)
    val sLoadTables = ind(emitLoadTables(s0.sources), 2)
    val sEmitBody = ind(emitActorBody(updateBlocks, systemReadyBlocks))
    val sGetSnapshot = ind(emitGetSnapshot(s0.queries), 2)
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
        |  def loadTables() = { ${block(sLoadTables)} }
        |
        |  def getSnapshot = { ${block(sGetSnapshot)} }
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
        |      startTime = System.nanoTime
        |      if (timeout > 0) endTime = startTime + timeout * 1000000L
        |    case EndOfStream => 
        |      endTime = System.nanoTime
        |      sender ! getSnapshot
        |      destroyContext()
        |    case GetSnapshot(_) => 
        |      sender ! getSnapshot
        |$sEventHandler
        |  }
        | 
        |$sConstants
        |}
        |""".stripMargin
  }

  protected def emitActorBody(updateBlocks: List[StatementBlock],
      systemReadyBlocks: List[StatementBlock]): String = {
    
    val sUpdateBatchArgs = 
      deltaMapInfo.map { case (name, _) =>
        s"${name}: ${impl.codegen.storeType(ctx0(name)._1)}"
      }.mkString(", ")

    val sSystemReadyBlocks = ind(emitBlocks(systemReadyBlocks))    
    val sUpdateBlocks = ind(emitBlocks(updateBlocks))
    val sLocalMaps = emitMaps(emitLocalMap, localMaps.toSeq)
    s"""|$sLocalMaps
        |
        |def onBatchUpdate($sUpdateBatchArgs) = { ${block(sUpdateBlocks)} } 
        | 
        |def onSystemReady() = { ${block(sSystemReadyBlocks)} }
        |""".stripMargin
  }
}
