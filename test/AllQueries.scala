package ddbt.test

/**
 * Automated "unsupported queries" testing.
 *
 * sbt 'test:run-main ddbt.test.AllQueries [opts]'
 *
 *    -z <num>  : enable Zeus random queries testing (100)
 *    -s <seed> : test a single Zeus query with given seed
 *    -v        : enable verbose errors
 *    -x        : attempt to run after compilation
 *
 */

object AllQueries {
  import ddbt.Utils._
  import ddbt.UnitTest.{toast,load,filtered}
  import ddbt.frontend.{M3Parser,TypeCheck}
  import ddbt.codegen._
  import ddbt.test.Benchmark.{tmp,scalac,scalax}
  val rbase = new java.io.File(path_repo+"/"+path_base)

  var verbose = false
  var zeus = false
  var run = false
  var seed:Long = 0
  var num = 100

  def main(args:Array[String]) {
    var i=0; val l=args.length
    while(i<l) {
      args(i) match {
        case "-z" if (i<l+1) => zeus=true;run=true; if (i<l+1) try { num=args(i+1).toInt; i+=1; } catch { case _:Throwable => }
        case "-s" if (i<l+1) => zeus=true;run=true; i+=1; seed=args(i).toLong; num=1;
        case "-v" => verbose = true
        case "-x" => run = true
      }
      i+=1
    }

    // 89938332 front-end: translated to different type (int) from its expected type (float)
    // 36688054 front-end: translated to different type (int) from its expected type (float) 
    // 18817471 front-end: generate syntactically correct M3, but not semantically correct: unbound variable
    if (zeus) {
      if (seed!=0) zeus(seed)
      else { var i=0; while(i<num) { i=i+1; zeus() } }
    } else moreTests()
  }

  def genTest(query:String,toast_f:()=>String,name:String="Query") = {
    def info(msg:String) = scala.Console.out.println(query+": "+msg)
    def err(msg:String) = scala.Console.err.println(query+": "+msg)
    def dump(out:String,err:String) = if (verbose) { if (out!="") println(out); if (err!="") scala.Console.err.println(err) }

    val (t0,(m3,o0,e0)) = ns(()=>captureOut(toast_f)); dump(o0,e0)
    if (m3=="" || m3==null) err("front-end failed")
    else try {
      import ddbt.ast.M3
      def gen(m3:M3.System):String = { val g=new ScalaGen(name); g.helper(m3,1)+g(m3) }
      val (t1,sc) = ns(()=> (M3Parser andThen TypeCheck andThen gen _)(m3)); write(tmp,name+".scala",sc)
      val (t2,(u2,o2,e2)) = ns(()=>captureOut(()=>scalac(name))); dump(o2,e2)
      if (e2!="") err("scalac: "+e2)
      else {
        val msg="toM3:"+time(t0)+", compile:"+time(t1)+", scalac:"+time(t2)
        if (!run) info(msg)
        else { val (t3,out) = ns(()=>scalax("ddbt.generated."+name)); info(msg+", run:"+time(t3)) }
      }
    } catch { case t:Throwable => err("compiler: "+t.getMessage) }
  }

  def zeus(s:Long=0) {
    val sql = exec("scripts/zeus.rb"+(if (s!=0) " -s "+s else ""))._1.replaceAll("@@DATA@@",path_repo+"/dbtoaster/experiments/data/simple/tiny")
    val ma = java.util.regex.Pattern.compile(".*seed *= *([0-9]+).*").matcher(sql.split("\n")(0))
    val seed = if (ma.matches) ma.group(1).toLong else sys.error("No seed")
    val sql_file = tmp.getPath+"/zeus.sql"; write(tmp,"zeus.sql",sql)
    println("Seed = "+seed)
    genTest("Zeus"+seed,()=>exec(Array(path_bin,"-l","m3",sql_file))._1,"Zeus")
  }

  /* Lookup for all SQL files in dbt repository tests and try to compile it */
  def moreTests() {
    val all = try { exec(Array("find","test","-type","f","-and","-name","*.sql","-and","-not","-name","schemas*",
                      "-and","-not","-path","*/.*",
                      "-and","-not","-path","*/postgres/*",
                      "-and","-not","-path","*/agendas/*"
                      ),rbase)._1.split("\n") }
              catch { case e:Exception => println("Repository not configured"); Array[String]() }
    val tested = filtered.map(f=>load(f).sql).toSet

    val excl = List(
      "mddb/query3",
      "mddb/query2_full" // very slow
    )

    val untested = all.filter(!tested.contains(_)).filter(x=>excl.forall(!x.contains(_))).sorted
    untested.foreach { t => genTest(t,()=>toast(t,List("-l","M3")),"NewQuery") }
  }
}

/*
POSSIBLE FUTURE TEST CASES:

employee/query00.sql: toM3: 0.011, compile: 0.202, scalac: 3.654
employee/query00a.sql: toM3: 0.011, compile: 0.039, scalac: 0.650
employee/query15.sql: toM3: 0.018, compile: 0.068, scalac: 0.723
employee/query35b.sql: toM3: 0.030, compile: 0.097, scalac: 1.044
employee/query36b.sql: toM3: 0.025, compile: 0.078, scalac: 0.827
employee/query43.sql: toM3: 0.024, compile: 0.062, scalac: 0.544
finance/chrissedtrades.sql: toM3: 6.758, compile: 1.227, scalac: 5.252
mddb/query1.sql: toM3: 1.356, compile: 0.242, scalac: 0.712
mddb/query2.sql: toM3:14.785, compile: 2.981, scalac:14.323
mddb/query2_inner_simple.sql: toM3: 0.709, compile: 0.410, scalac: 1.583
mddb/query2_simplified.sql: toM3:13.971, compile: 0.753, scalac: 2.318
simple/case01/r_adivb.sql: toM3: 0.012, compile: 0.016, scalac: 0.137
simple/case01/r_adivconst.sql: toM3: 0.011, compile: 0.012, scalac: 0.125
simple/case01/r_anotb.sql: toM3: 0.010, compile: 0.008, scalac: 0.128
simple/case01/r_anotorb.sql: toM3: 0.010, compile: 0.014, scalac: 0.128
simple/case01/r_aorb.sql: toM3: 0.014, compile: 0.017, scalac: 0.134
simple/case01/r_aorb_div.sql: toM3: 0.017, compile: 0.023, scalac: 0.127
simple/case01/r_exists.sql: toM3: 0.012, compile: 0.007, scalac: 0.118
simple/case01/r_exists_nested.sql: toM3: 0.039, compile: 0.016, scalac: 0.144
simple/case01/r_inequal.sql: toM3: 0.010, compile: 0.010, scalac: 0.132
simple/case01/r_inequal_ab.sql: toM3: 0.010, compile: 0.013, scalac: 0.115
simple/case01/r_inequal_empty.sql: toM3: 0.010, compile: 0.008, scalac: 0.109
simple/case01/r_lessthan.sql: toM3: 0.010, compile: 0.005, scalac: 0.109
simple/case01/r_multi_tlq.sql: toM3: 0.010, compile: 0.010, scalac: 0.116
simple/case01/r_nested_inequal.sql: toM3: 0.013, compile: 0.010, scalac: 0.107
simple/case01/r_newcolumn.sql: toM3: 0.011, compile: 0.008, scalac: 0.105
[error] simple/case01/r_notexists.sql: compiler: key not found: COUNT
simple/case01/r_simplenested.sql: toM3: 0.019, compile: 0.009, scalac: 0.130
simple/case01/r_simplenested2.sql: toM3: 0.011, compile: 0.012, scalac: 0.136
simple/case01/r_simplenested_empty.sql: toM3: 0.011, compile: 0.010, scalac: 0.108
simple/case01/r_sumab.sql: toM3: 0.009, compile: 0.007, scalac: 0.105
simple/case01/r_sumab3.sql: toM3: 0.009, compile: 0.007, scalac: 0.103
simple/cust_renaming.sql: toM3: 0.034, compile: 0.026, scalac: 0.179
simple/employee_initials.sql: toM3: 0.019, compile: 0.021, scalac: 0.151
simple/employee_names_with_j.sql: toM3: 0.016, compile: 0.018, scalac: 0.142
[error] simple/external_fn_test.sql: compiler: Library: no such function: ATOI
simple/matrixmult.sql: toM3: 0.012, compile: 0.020, scalac: 0.184
simple/order_date_parts.sql: toM3: 0.017, compile: 0.017, scalac: 0.136
simple/r_distinct.sql: toM3: 0.008, compile: 0.013, scalac: 0.126
simple/r_distincttest.sql: toM3: 0.010, compile: 0.024, scalac: 0.156
simple/r_inlist.sql: toM3: 0.014, compile: 0.018, scalac: 0.121
simple/r_nestedrename.sql: toM3: 0.011, compile: 0.012, scalac: 0.127
simple/rs_example1.sql: toM3: 0.015, compile: 0.010, scalac: 0.124
simple/rs_example2.sql: toM3: 0.016, compile: 0.031, scalac: 0.147
simple/rs_natjoinnooverlap.sql: toM3: 0.012, compile: 0.015, scalac: 0.151
simple/rs_streamvtable.sql: toM3: 0.010, compile: 0.009, scalac: 0.137
[error] simple/type_mappings.sql: compiler: [4.3] failure: Expected 'FROM'
[error] simple/zeroes.sql: compiler: key not found: QUERY_1_COUNT
tpch/query11_1.sql: toM3: 2.136, compile: 0.173, scalac: 0.439
tpch/query11_2.sql: toM3: 1.884, compile: 0.192, scalac: 0.453
tpch/query11_2nest_1.sql: toM3: 1.192, compile: 0.329, scalac: 0.677
tpch/query11_3.sql: toM3: 2.430, compile: 0.477, scalac: 0.975
tpch/query11_4.sql: toM3: 2.755, compile: 0.516, scalac: 1.026
tpch/query11_6.sql: toM3: 1.197, compile: 0.324, scalac: 0.631
tpch/query11b.sql: toM3: 0.016, compile: 0.018, scalac: 0.159
*/
