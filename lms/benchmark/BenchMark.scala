package benchmark

import dbtoptimizer._
import scala.concurrent.Lock
import scala.xml._
import scala.xml.Utility.trim

object BenchMark {
  val warmUpRounds = 0;
  def main(args: Array[String]): Unit = {
    val inputFilesFinance = List("data/finance.csv", "data/finance-standard.csv", "data/finance-large.csv", "data/finance-huge.csv")
    val queryClasses = List(
        /*("TestQ1-ChrissedTrades-PartA", List("experiments.finance.tq1.gen.Query"    , "experiments.finance.tq1.k3opt.Query"  , "experiments.finance.tq1.orig.Query"  /*, "experiments.finance.tq1.heuropt.Query"*/  ))
        ,("BrokerSpread", List("experiments.finance.brokerspread.gen.Query"    , "experiments.finance.brokerspread.k3opt.Query"  , "experiments.finance.brokerspread.orig.Query"  /*, "experiments.finance.brokerspread.heuropt.Query"*/  ))
        ,("AxFinder", List("experiments.finance.axfinder.gen.Query"            , "experiments.finance.axfinder.k3opt.Query"      , "experiments.finance.axfinder.orig.Query"      /*, "experiments.finance.axfinder.heuropt.Query"*/      ))
        ,("PriceSpread",    List("experiments.finance.pricespread.gen.Query"   , "experiments.finance.pricespread.k3opt.Query"   , "experiments.finance.pricespread.orig.Query"   /*, "experiments.finance.pricespread.heuropt.Query"*/   ))
        ,("BrokerVariance", List("experiments.finance.brokervariance.gen.Query", "experiments.finance.brokervariance.k3opt.Query", "experiments.finance.brokervariance.orig.Query"/*, "experiments.finance.brokervariance.heuropt.Query"*/))
        ,("MissedTrades",   List("experiments.finance.missedtrades.gen.Query"  , "experiments.finance.missedtrades.k3opt.Query"  , "experiments.finance.missedtrades.orig.Query"  /*, "experiments.finance.missedtrades.heuropt.Query"*/  ))
        ,("VWAP",           List("experiments.finance.vwap.gen.Query"          , "experiments.finance.vwap.k3opt.Query"          , "experiments.finance.vwap.orig.Query"          /*, "experiments.finance.vwap.heuropt.Query"*/          ))
        ,("ChrissedTrades", List("experiments.finance.chrissedtrades.gen.Query", "experiments.finance.chrissedtrades.k3opt.Query", "experiments.finance.chrissedtrades.orig.Query"/*, "experiments.finance.chrissedtrades.heuropt.Query"*/))
        */
    );
    executeBenchmarkFor(inputFilesFinance, queryClasses)
  }
  /** Execute benchmark for corresponding query classes over given input files.
  *
  * queryClasses: List of groups of query classes. Each group consists of a Tuple3:
  *    1- Group Name 2- Optimized Query class 3- Original DBT Class
  * inputFiles: List of input file paths that Query is being examined on them
  */
  def executeBenchmarkFor(inputFiles: List[String], queryClasses: List[Tuple2[String, List[String]]]): Unit = {
    var execAll = true
    var execOrig = true
    var execLMS = true
    var lock = new Lock
    var counter = 0;
    var failedTests = List[String]()

    def printSeparator = println("==================================")

    def printFailedTests = {
      printSeparator
      println("FailedTests: " + failedTests)
      printSeparator
    }
    var warmupRoundCounter = 0
    for (inputFile <- inputFiles) yield { 
      for (clazz_tupple <- queryClasses) yield {
        var resultsList = List[String]()
        while ( warmupRoundCounter < (warmUpRounds + 1) ) {
          for(clazz <- clazz_tupple._2) yield {
            if(execAll || ((clazz.contains("orig.") || clazz.contains("opt.")) && execOrig) || ((!clazz.contains("orig.") && !clazz.contains("opt.")) && execLMS)) {
              lock.acquire
    	        val queryCls = Class.forName(clazz)
    	        val queryClsConstructor = queryCls.getConstructors()(0);
    	        val queryInst = queryClsConstructor.newInstance(Array[AnyRef](inputFile):_*).asInstanceOf[DBTOptimizerQuery];
    	        val timeStart = System.nanoTime()
    	        val onTupleProc: Unit => Unit = Unit => {
    	          
    	        };
    	        val onQDone: Unit => Unit = Unit => {
    	          val runtime = (System.nanoTime() - timeStart) / 1000000000.0
                counter = counter + 1;
    	          println(counter + ", " + clazz_tupple._1 + ", " + clazz + ", " + inputFile + ", " + runtime)
                printSeparator
                val ostream: java.io.ByteArrayOutputStream = new java.io.ByteArrayOutputStream()
                Console.withOut(ostream) {
    	             queryInst.printResults()
                }
                val outputStr = new String(ostream.toByteArray(),"UTF-8")
                resultsList = outputStr :: resultsList
                print(outputStr)
                printFailedTests
    	          lock.release
    	        };
    	        val exec = new MainExec(queryInst, onTupleProc, onQDone)
              exec.main(new Array[String](0))
            }
          }
          warmupRoundCounter += 1
        }
        lock.acquire
        val firstOutput = resultsList.head
        val firstOutputXML = trim(XML.loadString(firstOutput))
        val testPassed = resultsList.forall { elem => 
          if(elem == firstOutput) true 
          else {
            val elemXML = trim(XML.loadString(elem))
            isEqual(elemXML, firstOutputXML)
          }
        }
        if(!testPassed) failedTests = (clazz_tupple._1 + " on " + inputFile) :: failedTests
        println((if(testPassed) "+ TEST PASSED" else "####### ???? ##### TEST FAILED!!!") + ", "+clazz_tupple._1 + ", " + inputFile)
        printFailedTests
        lock.release
      }
    }
  }

  def isEqual(x1: Node, x2: Node): Boolean = {
    if(x1 == x2) {
      true
    } else {
      if(x1.child.size != x2.child.size || x1.child.size <= 1) {
        false
      } else {
        x1.child.forall{ x1Child =>
          x2.child.filter { x2Child =>
            isEqual(x1Child, x2Child)
          }.size > 0
        }
      }
    }
  }
}