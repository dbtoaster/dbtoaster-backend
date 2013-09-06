package ddbt.test
import org.scalatest._

// sbt 'test:run-main ddbt.test.ToastSpeed'
object ToastSpeed {
  import ddbt.Utils._
  import ddbt.UnitTest.{sqlFiles,toast}

  def main(args:Array[String]) {
    sqlFiles()._2.foreach { file =>
      //println("-------------- "+file)
      val t2 = ns(()=>for (i<-0 until 5) toast(file,List("-O2")))._1
      val t3 = ns(()=>for (i<-0 until 5) toast(file,List("-O3")))._1
      println("O2:"+time(t2)+" O3:"+time(t3)+" ==> "+"%5.1f".format(100*(t3)*1.0/(t2))+"% in "+file)
    }
  }
}
