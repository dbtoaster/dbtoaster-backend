package ddbt.transformer


import ch.epfl.data.sc.pardis.ir.{PardisStructArg, PardisStruct, PardisLambda, PardisLambdaDef}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.{Optimizer, RuleBasedTransformer, Traverser}
import ch.epfl.data.sc.pardis.effects._
import ch.epfl.data.sc.pardis.utils.Graph
import ddbt.lib.store.deep.StoreDSL

class ColdMotion(override val IR: StoreDSL)  extends Optimizer[StoreDSL](IR) {
  import IR._

  val debugger = true

  def debug(msg: => Any): Unit = {
    if(debugger)
      System.err.println(msg)
  }

  val effectAnalysis = new SideEffectsAnalysis(IR)
  val coldRegionAnalysis = new ColdRegionAnalysis(IR)
  val countingAnalysis = new CountingAnalysis2(IR)
  type ColdRegion = coldRegionAnalysis.ColdRegion

  /**
   * First, it performs side effect analysis to have more precise effect information.
   * Second, it identifes the hot regions from which statements should be hoisted 
   * outside. Then, for each hot region specifies the list of statements that should
   * be hoisted. Finally, it performs the transformation to rewrite the hot region
   * to not include the hoisted statements, instead reifying them before the hot region.
   */
  def optimize[T: TypeRep](node: Block[T]): to.Block[T] = {
    effectAnalysis.optimize(node)
    coldRegionAnalysis.optimize(node)
    // debug(coldRegionAnalysis.coldRegions)
    countingAnalysis.optimize(node)
    for((_, currentRegion) <- coldRegionAnalysis.coldRegions) {
      // debug(currentRegion)
      debug(currentRegion.symbol)
      currentHoistedStatements = Nil
      for(stm <- currentRegion.block.stmts.reverse) {
        for(v <- getFreeVars(stm.rhs)) {
          backwardAnalysis(v)
        }
      }
      if (currentHoistedStatements.nonEmpty) {
        debug("injected statement symbols: " + currentHoistedStatements.reverse.map(_.sym))
        hoistedRegionStatements(currentRegion) = currentHoistedStatements.reverse
      }
      
      // debug(getFreeVars(cr.block.stmts.head.rhs).map(x => x -> countingAnalysis.symCounts(x)))
    }
    // traverseBlock(node)
    // transformProgram(node)
    node
  }

  // def backwardAnalysis[T, C](node: Def[T]): Unit = {
  //   node match {
  //     case Block(stmts, res) =>
  //       for(Stm(lhs, rhs) <- stmts.reverse) {
  //         backwardAnalysis(rhs)
  //       }
  //     case _ =>

  //   }
  // }
  def backwardAnalysis[T](sym: Rep[T]): Unit = {
    sym match {
      case Def(node) if countingAnalysis.symCounts(sym) == 1 && effectAnalysis.isPure(sym) => {
        // debug("count is 1 for " + sym + "-->" + node)
        // debug("is among cold regions " + coldRegionAnalysis.isColdSymbol(sym))
        // debug("is pure " + effectAnalysis.isPure(sym))
        // debug("freeVars: " + getFreeVars(node))
        for(s <- getFreeVars(node)) {
          backwardAnalysis(s)
        }
        val symbol = sym.asInstanceOf[Sym[Any]]
        currentHoistedStatements ::= Stm(symbol, node)(symbol.tp)
      }
      case _ =>
    }
  }

  /**
   * Specifies the cold region surrounding the current context.
   */
  // var currentRegion: ColdRegion = _
  /**
   * The list of statements should be hoisted in the current context.
   */
  var currentHoistedStatements = List[Stm[_]]()

  /**
   * The list of variables bound in the current context.
   */
  // var currentBoundSymbols = collection.Set[Rep[_]]()

  /**
   * Mapping between hot regions and the statements should be hoisted outside that region. 
   */
  val hoistedRegionStatements = collection.mutable.Map[ColdRegion, List[Stm[_]]]()

  /**
   * Returns the symbols that the given definition is dependent on them.
   */
  // def getDependencies(node: Def[_]): List[Sym[Any]] =
  //   node.funArgs.collect({
  //     case s: Sym[Any] => List(s)
  //     case b: Block[Any] => (b.res match {
  //       case s: Sym[Any] => List(s)
  //       case _ => Nil
  //     }) ++ getStatements(b).flatMap(s => s.sym :: getDependencies(s.rhs)).distinct
  //   }).flatten

  /**
   * Returns free variables occuring in a given definition.
   */
  def getFreeVars(node: Def[_]): List[Sym[Any]] =
    node.funArgs.collect({
      case s: Sym[Any] => List(s)
      case b: Block[Any] => (b.res match {
        case s: Sym[Any] => List(s)
        case _ => Nil
      }) ++ b.stmts.flatMap(s => getFreeVars(s.rhs)).distinct
    }).flatten.filterNot(s => getBoundVars(node).contains(s))

  /**
   * Returns bound variables defined in a given definition.
   */
  def getBoundVars(node: Def[_]): List[Sym[Any]] = 
    node match {
      case lambda: PardisLambdaDef => lambda.inputs.asInstanceOf[List[Sym[Any]]] ++ getBoundVars(lambda.body)
      case b: Block[Any] => b.stmts.flatMap(s => s.sym :: getBoundVars(s.rhs)).distinct
      case _ => node.funArgs.collect({
        case b: Block[Any] => getBoundVars(b)
        case _ => Nil
      }).flatten
    }

  /**
   * Specifies if the given statement can be hoisted from the current context.
   */
  // def isFloating(stm: Stm[_]): Boolean = {
  //   effectAnalysis.isPure(stm.sym) && !stm.rhs.isInstanceOf[PardisLambdaDef] && 
  //   getDependencies(stm.rhs).forall(x => !currentBoundSymbols.contains(x))
  // }

  /**
   * Specifies if we are currently in a context in which we should perform hoisting.
   */
  // def isInMotionableContext(): Boolean = currentRegion != null

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
  // def isContextAlreadyHoisted(stm: Stm[_]): Boolean = {
  //   currentHoistedStatements.exists(cstm => getStatements(cstm.rhs).contains(stm))
  // }

  /**
   * Collects the statements that should be hoisted from hot regions.
   */
  // override def traverseStm(stm: Stm[_]): Unit = stm match {
  //   case Stm(sym, rhs) if coldRegionAnalysis.isHotSymbol(sym) => {
  //     // Collecting the statements that should be hoisted for a hot region.
  //     val previousRegion = currentRegion
  //     currentRegion = coldRegionAnalysis.getColdRegion(sym)
  //     val previousBoundSymbols = currentBoundSymbols
  //     currentBoundSymbols = currentBoundSymbols ++ currentRegion.boundSymbols
  //     val previousStatements = currentHoistedStatements
  //     currentHoistedStatements = List()
  //     traverseBlock(currentRegion.block)
  //     if(currentHoistedStatements.nonEmpty)
  //       hoistedRegionStatements(currentRegion) = currentHoistedStatements
  //     currentRegion = previousRegion
  //     currentBoundSymbols = previousBoundSymbols
  //     currentHoistedStatements = previousStatements
  //   }
  //   case Stm(sym, rhs) if isInMotionableContext() => {
  //     if(isFloating(stm)) {
  //       // Gathers the statements that should be hoisted.
  //       if(!isContextAlreadyHoisted(stm))
  //         currentHoistedStatements +:= stm
  //     } else {
  //       // As it is not hoisted, everything depent on it also should not be hoisted.
  //       // So we add its symbol to the list of bound symbols.
  //       currentBoundSymbols = currentBoundSymbols + sym
  //     }
  //     super.traverseStm(stm)
  //   }
  //   case _ => super.traverseStm(stm)
  // }

  /**
   * Updating the list of bound symbols.
   */
  // override def traverseBlock(block: Block[_]): Unit = {
  //   val previousBoundSymbols = currentBoundSymbols
  //   super.traverseBlock(block)
  //   currentBoundSymbols = previousBoundSymbols
  // }

  /**
   * Removes the hoisted statements from the hot region and reifies them outside
   * the hot region.
   */
  // override def transformStmToMultiple(stm: Stm[_]): List[to.Stm[_]] =
  //   if (hoistedRegionStatements.exists(_._2.contains(stm.asInstanceOf[Stm[Any]])))
  //     Nil
  //   else stm match {
  //     // Removing the lambda expression of the hot region, as it should be reified
  //     // after the expressions
  //     case Stm(sym, rhs) if hoistedRegionStatements.exists(_._1.lambda.exists(_._1 == sym)) => 
  //       Nil
  //     case Stm(sym, rhs) if hoistedRegionStatements.exists(_._1.symbol == sym) =>
  //       val hotRegion = coldRegionAnalysis.coldRegions(sym)
  //       val stmts = hoistedRegionStatements(hotRegion)
  //       // Reifies the hoisted statements outside the hot region.
  //       for(st <- stmts.reverse) {
  //         reflectStm(st)
  //       }
  //       debug(s"${hotRegion.boundSymbols} -> ${stmts.size}")
  //       // If the hot region contains a lambda, it transforms the lambda expression.
  //       for((lambdaSym: Sym[Any], lambdaNode: Def[Any] with PardisLambdaDef) <- hotRegion.lambda) {
  //         reflectStm(Stm(lambdaSym, transformDef(lambdaNode)(lambdaNode.tp))(lambdaNode.tp))
  //       }
  //       super.transformStmToMultiple(stm)
  //     case _ =>
  //       super.transformStmToMultiple(stm)
  //   }
}

class ColdRegionAnalysis(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {
  import IR._
  import scala.language.existentials

  case class ColdRegion(symbol: Rep[_], block: Block[_], boundSymbols: List[Rep[_]], 
    lambda: Option[(Rep[_], Def[_] with PardisLambdaDef)])

  val coldRegions = scala.collection.mutable.Map[Rep[_], ColdRegion]()

  def isColdSymbol(s: Rep[_]): Boolean = coldRegions.exists(_._1 == s)

  def getColdRegion(s: Rep[_]): ColdRegion = coldRegions(s)

  def isColdBlock[T](block: Block[T]): Boolean = 
    block.stmts match {
      case List(Stm(_, definition)) => definition match {
        case IdxSliceResMap(_, _, _, _) => true
        case IdxForeachResMap(_, _, _)  => true
        case _ => false
      }
      case _ => false
    }

  def checkAndAddAsColdRegion[T](sym: Rep[T], block: Block[T]): Unit = {
    if(isColdBlock(block))
      coldRegions += sym -> ColdRegion(sym, block, Nil, None)
  }

  analysis += statement {
    case sym -> IfThenElse(cond, thenp, elsep) =>
      checkAndAddAsColdRegion(sym, thenp)
      checkAndAddAsColdRegion(sym, elsep)
      ()
  }
}

/** A version of counting analysis which uses a local hash table for
  * for maintaing the number of usages of each symbol.
  */
class CountingAnalysis2(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {
  import IR._

  val symCounts = scala.collection.mutable.Map[Rep[_], Int]()

  override def traverseExp(exp: Rep[_]): Unit = exp match {
    case s: Sym[_] => {
      val prevCount = symCounts.getOrElseUpdate(s, 0)
      symCounts(s) = prevCount + 1
    }
    case _ => super.traverseExp(exp)
  }
}
