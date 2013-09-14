package ddbt.test

object AllQueries {
  import ddbt.Utils._
  import ddbt.UnitTest.{toast,load,filtered}
  import ddbt.frontend._
  import ddbt.codegen._
  import ddbt.test.Benchmark.{tmp,scalac}
  def main(args:Array[String]) {
    val rbase = new java.io.File(path_repo+"/"+path_base)
    val all = try { exec(Array("find","test","-type","f","-and","-name","*.sql","-and","-not","-name","schemas*",
                      "-and","-not","-path","*/.*","-and","-not","-path","*/postgres/*"),rbase)._1.split("\n") }
              catch { case e:Exception => println("Repository not configured"); Array[String]() }
    val tested = filtered.map(f=>load(f).sql).toSet
    val untested = all.filter(!tested.contains(_)).filter(!_.contains("mddb/query3"))
    untested.foreach { t => 
      println("----------- "+t)
      val (t0,m3) = ns(()=>toast(t,List("-l","M3")))
      println("SQL -> M3      : "+time(t0))
      if (m3!="" && m3!=null) {
        val (t1,sc) = ns(()=>(M3Parser andThen TypeCheck andThen ScalaGen("NewQuery"))(m3))
        write(tmp,"NewQuery.scala",sc) // bad paths, but we ignore this here
        println("Scala codegen  : "+time(t1))
        val t2 = ns(()=>scalac("NewQuery"))._1
        println("Scalac compile : "+time(t2))
      }
    }
  }
}
