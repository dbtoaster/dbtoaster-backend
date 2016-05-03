package ddbt.transformer


import ch.epfl.data.sc.pardis.ir.{PardisStructArg, PardisStruct, PardisLambda, PardisLambdaDef}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.{Optimizer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.effects._
import ch.epfl.data.sc.pardis.utils.Graph
import ddbt.lib.store.deep.StoreDSL

class CodeMotion(override val IR: StoreDSL)  extends Optimizer[StoreDSL](IR) {
  import IR._

  val effectAnalysis = new SideEffectsAnalysis(IR)
  val hotRegionAnalysis = new HotRegionAnalysis(IR)
  type HotRegion = hotRegionAnalysis.HotRegion

  /**
   * First, in the analysis phase, it collects the statements constructing a HashMap
   * or MultiMap. Furthermore, it looks for the dependent statements, since hoisting
   * statements without hoisting the dependent statements makes the program incorrect.
   * Second, all hoisted statements are scheduled in the right order.
   * Finally, the scheduled statements are moved to the loading part and are removed
   * from the query processing time.
   */
  def optimize[T: TypeRep](node: Block[T]): to.Block[T] = {
    effectAnalysis.optimize(node)
    hotRegionAnalysis.optimize(node)
    // do {
    //   newStatementHoisted = false
    //   traverseBlock(node)
    // } while (newStatementHoisted)
    // scheduleHoistedStatements()
    // transformProgram(node)
    traverseBlock(node)
    for((region, stmts) <- hoistedRegionStatements) {
      System.err.println(s"${region.boundSymbols}: ${stmts.mkString("****")}")
    }
    node
  }

  var currentRegion: HotRegion = _
  // var newStatementHoisted = false
  /**
   * Specifies the nesting level of the statements that we are traversing over.
   */
  // var depthLevel = 0
  val hoistedStatements = collection.mutable.ArrayBuffer[Stm[Any]]()
  // TODO check if we can remove this one?
  var currentHoistedStatements = List[Stm[_]]()
  /**
   * Contains the list of symbols that we should find their dependency in the next
   * analysis iteration.
   */
  val workList = collection.mutable.Set[Sym[Any]]()

  var currentBoundSymbols = collection.Set[Rep[_]]()

  val hoistedRegionStatements = collection.mutable.Map[HotRegion, List[Stm[_]]]()

  /**
   * Schedules the statments that should be hoisted.
   */
  def scheduleHoistedStatements() {
    val result = Graph.schedule(hoistedStatements.toList, (stm1: Stm[Any], stm2: Stm[Any]) =>
      getDependencies(stm2.rhs).contains(stm1.sym))
    hoistedStatements.clear()
    hoistedStatements ++= result
  }

  /**
   * Returns the symbols that the given definition is dependent on them.
   */
  def getDependencies(node: Def[_]): List[Sym[Any]] =
    node.funArgs.filter(_.isInstanceOf[Sym[Any]]).map(_.asInstanceOf[Sym[Any]])

  // override def traverseDef(node: Def[_]): Unit = node match {
  //   case GenericEngineRunQueryObject(b) => {
  //     startCollecting = true
  //     depthLevel = 0
  //     currentHoistedStatements.clear()
  //     traverseBlock(b)
  //     hoistedStatements.prependAll(currentHoistedStatements)
  //     startCollecting = false
  //   }
  //   case _ => super.traverseDef(node)
  // }

  def isFloating(stm: Stm[_]): Boolean = {
    effectAnalysis.isPure(stm.sym) && !stm.rhs.isInstanceOf[PardisLambdaDef] && 
    getDependencies(stm.rhs).forall(x => !currentBoundSymbols.contains(x))
  }

  def isInMotionableContext(): Boolean = currentRegion != null

  def getStatements(n: Def[_]): List[Stm[_]] = n match {
    case Block(stmts, res) => stmts ++ stmts.flatMap(x => getStatements(x.rhs))
    case n if n.funArgs.exists(_.isInstanceOf[Block[_]]) => n.funArgs.collect({ case b: Block[_] =>
      getStatements(b)
    }).flatten
    case _ => Nil
  }

  def isContextAlreadyHoisted(stm: Stm[_]): Boolean = {
    currentHoistedStatements.exists(cstm => getStatements(cstm.rhs).contains(stm))
  }

  var first = false

  def filterReptitiveStatements(stmts: List[Stm[_]]): List[Stm[_]] = {
    val sorted = Graph.schedule(stmts, (stm1: Stm[_], stm2: Stm[_]) =>
      getStatements(stm1.rhs).contains(stm2))
    if(first) {
      System.err.println(stmts)
      System.err.println(sorted)
      // first = false
    }
    val result = collection.mutable.ArrayBuffer[Stm[_]]()
    result ++= sorted
    // TODO should iterate and check if it does not already exist then add it.
    result.toList
  }

  override def traverseStm(stm: Stm[_]): Unit = stm match {
    case Stm(sym, rhs) if hotRegionAnalysis.isHotSymbol(sym) => {
      val previousRegion = currentRegion
      currentRegion = hotRegionAnalysis.getHotRegion(sym)
      val previousBoundSymbols = currentBoundSymbols
      currentBoundSymbols = currentBoundSymbols ++ currentRegion.boundSymbols
      val previousStatements = currentHoistedStatements
      currentHoistedStatements = List()
      traverseBlock(currentRegion.block)
      // hoistedStatements.prependAll(currentHoistedStatements)
      hoistedRegionStatements(currentRegion) = filterReptitiveStatements(currentHoistedStatements)
      currentRegion = previousRegion
      currentBoundSymbols = previousBoundSymbols
      currentHoistedStatements = previousStatements
    }
    case Stm(sym, rhs) if isInMotionableContext() => {
      if(isFloating(stm)) {
        if(!isContextAlreadyHoisted(stm))
          currentHoistedStatements +:= stm
      } else {
        currentBoundSymbols = currentBoundSymbols + sym
      }
      super.traverseStm(stm)
    }
    case _ => super.traverseStm(stm)
  }

  override def traverseBlock(block: Block[_]): Unit = {
    val previousBoundSymbols = currentBoundSymbols
    // depthLevel += 1
    super.traverseBlock(block)
    // depthLevel -= 1
    currentBoundSymbols = previousBoundSymbols
  }

  // def isDependentOnMutation(exp: Rep[_]): Boolean = exp match {
  //   case Def(node) => node match {
  //     case ReadVar(_) => true
  //     case _ => node.funArgs.collect({
  //       case e: Rep[_] => isDependentOnMutation(e)
  //     }).exists(identity)
  //   }
  //   case _ => false
  // }

  /**
   * Gathers the statements that should be hoisted.
   */
  // override def traverseStm(stm: Stm[_]): Unit = stm match {
  //   case Stm(sym, rhs) => {
  //     def hoistStatement() {
  //       currentHoistedStatements += stm.asInstanceOf[Stm[Any]]
  //       workList ++= getDependencies(rhs)
  //       newStatementHoisted = true
  //     }
  //     rhs match {
  //       case HashMapNew() if startCollecting && !hoistedStatements.contains(stm) => {
  //         hoistStatement()
  //       }
  //       case MultiMapNew() if startCollecting && !hoistedStatements.contains(stm) => {
  //         hoistStatement()
  //       }
  //       case ArrayNew(size) if isDependentOnMutation(size) =>
  //         super.traverseStm(stm)
  //       case ArrayNew(_) if startCollecting && depthLevel == 1 && !hoistedStatements.contains(stm) => {
  //         hoistStatement()
  //       }
  //       case _ if startCollecting && workList.contains(sym) && !hoistedStatements.contains(stm) => {
  //         hoistStatement()
  //         workList -= sym
  //       }
  //       case _ => super.traverseStm(stm)
  //     }
  //   }
  // }

  /**
   * Removes the hoisted statements from the query processing time.
   */
  override def transformStmToMultiple(stm: Stm[_]): List[to.Stm[_]] =
    if (hoistedStatements.contains(stm.asInstanceOf[Stm[Any]]))
      Nil
    else
      super.transformStmToMultiple(stm)

  /**
   * Reifies the hoisted statements in the loading time.
   */
  // override def transformDef[T: PardisType](node: Def[T]): to.Def[T] = (node match {
  //   case GenericEngineRunQueryObject(b) =>
  //     for (stm <- hoistedStatements) {
  //       reflectStm(stm)
  //     }
  //     val newBlock = transformBlock(b)
  //     GenericEngineRunQueryObject(newBlock)(newBlock.tp)
  //   case _ => super.transformDef(node)
  // }).asInstanceOf[to.Def[T]]
}

class SideEffectsAnalysis(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {
  import IR._

  var currentContext: Block[_] = _

  val symEffectsInfo = scala.collection.mutable.Map[Rep[_], Effect]()
  val blockEffectsInfo = scala.collection.mutable.Map[Block[_], Effect]()

  def getEffectOfStm(stm: Stm[_]): Effect = {
    symEffectsInfo.getOrElseUpdate(stm.sym, if(stm.rhs.isPure) Pure else IO)
  }

  def isPure(sym: Rep[_]): Boolean = symEffectsInfo(sym) == Pure

  def getEffectOfBlock(block: Block[_]): Effect = {
    blockEffectsInfo.getOrElseUpdate(block, if(block.stmts.map(getEffectOfStm).forall(_ == Pure)) Pure else IO)
  }

  override def postAnalyseProgram[T: TypeRep](node: Block[T]): Unit = {
    // System.err.println(s"Done with effect analysis!")
    // blockEffectsInfo.foreach(x => System.err.println(s"block ${x._1.res}: ${x._2}"))
  }


  analysis += statement {
    case sym -> IfThenElse(cond, thenp, elsep) => {
      traverseBlock(thenp)
      traverseBlock(elsep)
      val eff = if (getEffectOfBlock(thenp) == Pure && getEffectOfBlock(elsep) == Pure)
        Pure
      else
        IO
      symEffectsInfo += sym -> eff
      ()
    }
  }

  analysis += rule {
    case block: Block[_] => {
      val oldContext = currentContext
      currentContext = block
      traverseBlock(block)
      getEffectOfBlock(block) // forces the effect to be added to the Map
      currentContext = oldContext
    }
  }
}

class HotRegionAnalysis(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {
  import IR._

  case class HotRegion(symbol: Rep[_], block: Block[_], boundSymbols: List[Rep[_]])

  val hotRegions = scala.collection.mutable.Map[Rep[_], HotRegion]()

  override def postAnalyseProgram[T: TypeRep](node: Block[T]): Unit = {
    // System.err.println(s"Done with HotRegionAnalysis: $hotSymbols")
  }

  def isHotSymbol(s: Rep[_]): Boolean = hotRegions.exists(_._1 == s)
  def isHotBlock(b: Block[_]): Boolean = hotRegions.exists(_._2.block == b)

  def getHotRegion(s: Rep[_]): HotRegion = hotRegions(s)

  analysis += statement {
    case sym -> StoreSlice(self, idx, key, Def(PardisLambda(f, i, o))) => 
      hotRegions += sym -> HotRegion(sym, o, List(i))
      ()
  }
}
