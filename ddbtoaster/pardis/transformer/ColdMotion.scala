package ddbt.transformer


import ch.epfl.data.sc.pardis.ir.{PardisStructArg, PardisStruct, PardisLambda, PardisLambdaDef}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.{Optimizer, RuleBasedTransformer, Traverser}
import ch.epfl.data.sc.pardis.effects._
import ch.epfl.data.sc.pardis.utils.Graph
import ddbt.lib.store.deep.StoreDSL

/**
 * Moves statements into cold regions whenever possible.
 * For example, if there are some statements that can be moved inside a conditional
 * branch, this transformer will move them inside that branch.
 */
class ColdMotion(override val IR: StoreDSL)  extends Optimizer[StoreDSL](IR) {
  import IR._

  val debugger = false

  def debug(msg: => Any): Unit = {
    if(debugger)
      System.err.println(msg)
  }

  val effectAnalysis = new SideEffectsAnalysis(IR)
  val coldRegionAnalysis = new ColdRegionAnalysis(IR)
  val countingAnalysis = new CountingAnalysisLocal(IR)
  type ColdRegion = coldRegionAnalysis.ColdRegion

  /**
   * First, it performs side effect analysis to have more precise effect information.
   * Second, it identifes the colde regions inside which some statements should be injected. 
   * Then, for each cold region specifies the list of statements that should
   * be injected. Finally, it performs the transformation to rewrite the cold regions
   * to include the injected statements, instead of reifying them before that cold region.
   */
  def optimize[T: TypeRep](node: Block[T]): to.Block[T] = {
    effectAnalysis.optimize(node)
    coldRegionAnalysis.optimize(node)
    countingAnalysis.optimize(node)
    for((_, currentRegion) <- coldRegionAnalysis.coldRegions) {
      currentHoistedStatements = Nil
      for(stm <- currentRegion.block.stmts.reverse) {
        for(v <- getFreeVars(stm.rhs)) {
          backwardAnalysis(v)
        }
      }
      if (currentHoistedStatements.nonEmpty) {
        hoistedRegionStatements(currentRegion) = currentHoistedStatements.reverse
      }
    }
    transformProgram(node)
  }

  /**
   * Recursively goes backwards through the symbols so that it finds the dependent
   * statements that can be moved inside the cold regions.
   */
  def backwardAnalysis[T](sym: Rep[T]): Unit = {
    sym match {
      case Def(node) if countingAnalysis.symCounts(sym) == 1 && effectAnalysis.isPure(sym) => {
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
   * The list of statements should be injected in the current cold region.
   */
  var currentHoistedStatements = List[Stm[_]]()


  /**
   * Mapping between cold regions and the statements should be inject inside that region. 
   */
  val hoistedRegionStatements = collection.mutable.Map[ColdRegion, List[Stm[_]]]()

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
   * Removes the hoisted statements from their previous region, so that it can
   * be reified inside the cold region as implemented in `transformBlockTyped`.
   */
  override def transformStmToMultiple(stm: Stm[_]): List[to.Stm[_]] =
    if (hoistedRegionStatements.exists(_._2.contains(stm.asInstanceOf[Stm[Any]])))
      Nil
    else 
      super.transformStmToMultiple(stm)

  /**
   * Reifies the statements that can be injected in the cold region. 
   */
  override protected def transformBlockTyped[T: TypeRep, S: TypeRep](block: Block[T]): Block[S] = 
    if(hoistedRegionStatements.exists(_._1.block == block)) {
      val coldRegion = hoistedRegionStatements.find(_._1.block == block).get._1
      val newStmts = hoistedRegionStatements(coldRegion)
      reifyBlock[S] {
        for(st <- newStmts) {
          reflectStm(st)
        }
        block.stmts.foreach(transformStmToMultiple)
        transformExp[T, S](block.res)
      }
    } else {
      super.transformBlockTyped(block)
    }
}

class ColdRegionAnalysis(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {
  import IR._
  import scala.language.existentials

  case class ColdRegion(symbol: Rep[_], block: Block[_], boundSymbols: List[Rep[_]], 
    lambda: Option[(Rep[_], Def[_] with PardisLambdaDef)])

  val coldRegions = scala.collection.mutable.Map[Rep[_], ColdRegion]()

  def isColdSymbol(s: Rep[_]): Boolean = coldRegions.exists(_._1 == s)

  def getColdRegion(s: Rep[_]): ColdRegion = coldRegions(s)

  /** 
   * Specifies whether the given block should be considered as cold or not. 
   */
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
class CountingAnalysisLocal(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {
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
