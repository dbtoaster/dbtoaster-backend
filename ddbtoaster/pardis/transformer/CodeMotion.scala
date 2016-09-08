package ddbt.transformer


import ch.epfl.data.sc.pardis.ir.{PardisStructArg, PardisStruct, PardisLambda, PardisLambdaDef}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.{Optimizer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.effects._
import ch.epfl.data.sc.pardis.utils.Graph
import ddbt.lib.store.deep.StoreDSL

class CodeMotion(override val IR: StoreDSL)  extends Optimizer[StoreDSL](IR) {
  import IR._

  val debugger = false

  def debug(msg: => Any): Unit = {
    if(debugger)
      System.err.println(msg)
  }

  val effectAnalysis = new SideEffectsAnalysis(IR)
  val hotRegionAnalysis = new HotRegionAnalysis(IR)
  type HotRegion = hotRegionAnalysis.HotRegion

  /**
   * First, it performs side effect analysis to have more precise effect information.
   * Second, it identifes the hot regions from which statements should be hoisted 
   * outside. Then, for each hot region specifies the list of statements that should
   * be hoisted. Finally, it performs the transformation to rewrite the hot region
   * to not include the hoisted statements, instead reifying them before the hot region.
   */
  def optimize[T: TypeRep](node: Block[T]): to.Block[T] = {
    effectAnalysis.optimize(node)
    hotRegionAnalysis.optimize(node)
    traverseBlock(node)
    transformProgram(node)
  }
  /**
   * Specifies the hot region surrounding the current context.
   */
  var currentRegion: HotRegion = _
  /**
   * The list of statements should be hoisted in the current context.
   */
  var currentHoistedStatements = List[Stm[_]]()

  /**
   * The list of variables bound in the current context.
   */
  var currentBoundSymbols = collection.Set[Rep[_]]()

  /**
   * Mapping between hot regions and the statements should be hoisted outside that region. 
   */
  val hoistedRegionStatements = collection.mutable.Map[HotRegion, List[Stm[_]]]()

  /**
   * Returns the symbols that the given definition is dependent on them.
   */
  def getDependencies(node: Def[_]): List[Sym[Any]] =
    node.funArgs.collect({
      case s: Sym[Any] => List(s)
      case b: Block[Any] => (b.res match {
        case s: Sym[Any] => List(s)
        case _ => Nil
      }) ++ getStatements(b).flatMap(s => s.sym :: getDependencies(s.rhs)).distinct
    }).flatten

  /**
   * Specifies if the given statement can be hoisted from the current context.
   */
  def isFloating(stm: Stm[_]): Boolean = {
    effectAnalysis.isPure(stm.sym) && !stm.rhs.isInstanceOf[PardisLambdaDef] && 
    getDependencies(stm.rhs).forall(x => !currentBoundSymbols.contains(x))
  }

  /**
   * Specifies if we are currently in a context in which we should perform hoisting.
   */
  def isInMotionableContext(): Boolean = currentRegion != null

  /**
   * Extracts the statements defined in the given definition.
   */
  def getStatements(n: Def[_]): List[Stm[_]] = n match {
    case Block(stmts, res) => stmts ++ stmts.flatMap(x => getStatements(x.rhs))
    case n if n.funArgs.exists(_.isInstanceOf[Block[_]]) => n.funArgs.collect({ case b: Block[_] =>
      getStatements(b)
    }).flatten
    case _ => Nil
  }

  /**
   * Specifies if we have already hoisted a statement which contains the given statement.
   * 
   * For example, if the given statement is a statement inside an if-then-else expression
   * which is already hoisted, there is no more need for hoisting the given statement.
   * Hence, this method returns true in such cases.
   * 
   */
  def isContextAlreadyHoisted(stm: Stm[_]): Boolean = {
    currentHoistedStatements.exists(cstm => getStatements(cstm.rhs).contains(stm))
  }

  /**
   * Collects the statements that should be hoisted from hot regions.
   */
  override def traverseStm(stm: Stm[_]): Unit = stm match {
    case Stm(sym, rhs) if hotRegionAnalysis.isHotSymbol(sym) => {
      // Collecting the statements that should be hoisted for a hot region.
      val previousRegion = currentRegion
      currentRegion = hotRegionAnalysis.getHotRegion(sym)
      val previousBoundSymbols = currentBoundSymbols
      currentBoundSymbols = currentBoundSymbols ++ currentRegion.boundSymbols
      val previousStatements = currentHoistedStatements
      currentHoistedStatements = List()
      traverseBlock(currentRegion.block)
      if(currentHoistedStatements.nonEmpty)
        hoistedRegionStatements(currentRegion) = currentHoistedStatements
      currentRegion = previousRegion
      currentBoundSymbols = previousBoundSymbols
      currentHoistedStatements = previousStatements
    }
    case Stm(sym, rhs) if isInMotionableContext() => {
      if(isFloating(stm)) {
        // Gathers the statements that should be hoisted.
        if(!isContextAlreadyHoisted(stm))
          currentHoistedStatements +:= stm
      } else {
        // As it is not hoisted, everything depent on it also should not be hoisted.
        // So we add its symbol to the list of bound symbols.
        currentBoundSymbols = currentBoundSymbols + sym
      }
      super.traverseStm(stm)
    }
    case _ => super.traverseStm(stm)
  }

  /**
   * Updating the list of bound symbols.
   */
  override def traverseBlock(block: Block[_]): Unit = {
    val previousBoundSymbols = currentBoundSymbols
    super.traverseBlock(block)
    currentBoundSymbols = previousBoundSymbols
  }

  /**
   * Removes the hoisted statements from the hot region and reifies them outside
   * the hot region.
   */
  override def transformStmToMultiple(stm: Stm[_]): List[to.Stm[_]] =
    if (hoistedRegionStatements.exists(_._2.contains(stm.asInstanceOf[Stm[Any]])))
      Nil
    else stm match {
      // Removing the lambda expression of the hot region, as it should be reified
      // after the expressions
      case Stm(sym, rhs) if hoistedRegionStatements.exists(_._1.lambda.exists(_._1 == sym)) => 
        Nil
      case Stm(sym, rhs) if hoistedRegionStatements.exists(_._1.symbol == sym) =>
        val hotRegion = hotRegionAnalysis.hotRegions(sym)
        val stmts = hoistedRegionStatements(hotRegion)
        // Reifies the hoisted statements outside the hot region.
        for(st <- stmts.reverse) {
          reflectStm(st)
        }
        debug(s"${hotRegion.boundSymbols} -> ${stmts.size}")
        // If the hot region contains a lambda, it transforms the lambda expression.
        for((lambdaSym: Sym[Any], lambdaNode: Def[Any] with PardisLambdaDef) <- hotRegion.lambda) {
          reflectStm(Stm(lambdaSym, transformDef(lambdaNode)(lambdaNode.tp))(lambdaNode.tp))
        }
        super.transformStmToMultiple(stm)
      case _ =>
        super.transformStmToMultiple(stm)
    }
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
  import scala.language.existentials

  case class HotRegion(symbol: Rep[_], block: Block[_], boundSymbols: List[Rep[_]], 
    lambda: Option[(Rep[_], Def[_] with PardisLambdaDef)])

  val hotRegions = scala.collection.mutable.Map[Rep[_], HotRegion]()

  def isHotSymbol(s: Rep[_]): Boolean = hotRegions.exists(_._1 == s)
  def isHotBlock(b: Block[_]): Boolean = hotRegions.exists(_._2.block == b)

  def getHotRegion(s: Rep[_]): HotRegion = hotRegions(s)

  analysis += statement {
    case sym -> StoreSliceCopy(self, idx, key, lambda @ Def(lambdaDef @ PardisLambda(f, i, o))) =>
      hotRegions += sym -> HotRegion(sym, o, List(i), Some(lambda -> lambdaDef))
      ()
  }
  analysis += statement {
    case sym -> StoreForeach(self, lambda @ Def(lambdaDef @ PardisLambda(f, i, o))) => 
      hotRegions += sym -> HotRegion(sym, o, List(i), Some(lambda -> lambdaDef))
      ()
  }
}
