package benchmark

import collection.mutable
import sys.process._
import java.io.File

object OltpBenchmark {
  import Statistics._

  object Config {
    val iterations = 1000000           // for iteration based benchmarks
    val time       = 60                // for time based benchmarks
    val warehouses = 2 :: Nil          // number of warehouses
    val runs       = 3//0             // we take an avarage of $runs
    val voltDBDir  = "/home/vjovanov/voltdb/"
  }

  val results: mutable.Map[String, Map[Int, Seq[Long]]] = new mutable.HashMap()

  def main(args: Array[String]): Unit = {
    println("-------------------------- VoltDB")
    results += ("VoltDB" -> runVoltDB())
    println("-------------------------- InnoDB")
    results += ("MySQL-InnoDB" -> runMySQL("innodb"))
    println("-------------------------- Memory")
    results += ("MySQL-Memory" -> runMySQL("memory"))
    println("-------------------------- HStore-tck")
    results += ("HStore-tck" -> runHStore("h-store/tck"))
    println("-------------------------- HStore-vldb2007")
    results += ("HStore-vldb2007" -> runHStore("h-store/vldb2007"))
    println("-------------------------- Naive")
    results += ("Naive" -> runScala(1))
    println("-------------------------- Scala hand-optimized")
    results += ("Scala Hand Optimized" -> runScala(5))
    println("-------------------------- S-Store")
    results += ("S-Store" -> runScala(-1))
    println("-----------------------------------------")
    println(results)
    println(results.map{case (n, m) =>
      (n, m.map{case (w, l) =>
        (w, (avg(l.map(_.toDouble)), stdev(l.map(_.toDouble))))
      })
    })
  }

  def runBenchmark(exec: Int => Long): Map[Int, Seq[Long]] = {
    import Config._
    warehouses.map { w =>
      // run a script for runs times
      val res = for (_ <- 0 until runs)
        yield exec(w)
      (w, res)
    }.toMap
  }

  def runHStore(path: String): Map[Int, Seq[Long]] = runBenchmark(warehouse => {
    Process(
      Seq("make"),
      Some(new File(path))
    ).!!
    Process(
      Seq("./run.sh", "" + warehouse),
      Some(new File(path))
    ).!!<.trim.toLong
  })

  def runMySQL(storage: String): Map[Int, Seq[Long]] = {
    import Config._
    runBenchmark { w =>
      Process(
        Seq("./run", ""+w, ""+iterations, ""+storage),
        Some(new File("mysql")),
        // "MY_INI" -> "/etc/mysql/my.cnf",
        "DBUSER" -> "root",
        "PASS" -> "ROOT"
      ).!!<.trim.toLong
    }
  }

  def runScala(number: Int): Map[Int, Seq[Long]] =
    Config.warehouses.map { w =>
      val tpccLoad = new ddbt.tpcc.loadtest.TpccLoad()
      var ret = 0
      tpccLoad.init()
      ret = tpccLoad.runLoad(true, Array("-w", ""+w))
      // run a script for runs times
      ddbt.tpcc.tx.TpccInMem.NUM_ITERATIONS = Config.runs
      val tpcc = new ddbt.tpcc.tx.TpccInMem()
      ret = 0
      tpcc.init()

      println("Using the properties file for configuration.")
      tpcc.runBenchmark(true, Array("-w", w.toString, "-i", number.toString))
      (w, tpcc.result)
    }.toMap

  def runVoltDB(): Map[Int, Seq[Long]] = {
    import Config._
    runBenchmark { w =>
      val server = Process(
        Seq("./srv"),
        //Seq("./run.sh", "server"),
        Some(new java.io.File(voltDBDir + "/tests/test_apps/tpcc"))
      )
      val serverProcess = server.run()

      //Thread.sleep(1000) // urgh, I am lazy

      val client = Process(
        Seq("./run"),
        Some(new java.io.File(voltDBDir + "/tests/test_apps/tpcc")),
        "WAREHOUSES" -> w.toString,
        "DURATION" -> time.toString
      )
      val res = client.!!<
      serverProcess.destroy()
      Thread.sleep(1000)
      res.trim.toLong
    }
  }
}


object Statistics {
  /**
   * Returns the average (arithmetic mean) of the arguments.
   * 1/n * sum(x)
   *
   * @param data population
   * @return arithmetic mean
   */
  def avg(data: Seq[Double]): Double = {
    if (data.length < 1)
      return Double.NaN
    data.sum / data.length
  }

 /**
   * Calculates the standard deviation of an Sequence of numbers.
   *
   * @param data Numbers to compute the standard deviation of.
   *             sequence must contain two or more numbers.
   * @return standard deviation estimate of population
   *         ( to get estimate of sample, use n instead of n-1 in last line )
   */
  def stdev(data: Seq[Double]): Double = {
    if (data.length < 2)
      return Double.NaN
    // average
    val mean: Double = avg(data)
    // reduce function
    def f(sum: Double, tail: Double): Double = {
      val dif = tail - mean
      sum + dif * dif
    }

    val sum = data.foldLeft(0.0)((s, t) => f(s, t))
    Math.sqrt(sum / (data.length - 1))
  }
}
