package ddbt.test
import org.scalatest._

// sbt 'test:run-main ddbt.test.ToastSpeed'
object ToastSpeed {
  import ddbt.UnitTest

  def time(ns:Long) = { val ms=ns/1000000; "%2d.%03d".format(ms/1000,ms%1000) }
  def main(args:Array[String]) {
    UnitTest.allM3.foreach { file =>
      //println("-------------- "+file)
      val t0=System.nanoTime()
      for (i<-0 until 5) UnitTest.toast(file,List("-O2"))
      val t1 = System.nanoTime()
      for (i<-0 until 5) UnitTest.toast(file,List("-O3"))
      val t2 = System.nanoTime()
      println("O2:"+time(t1-t0)+" O3:"+time(t2-t1)+" ==> "+"%5.1f".format(100*(t2-t1)*1.0/(t1-t0))+"% in "+file)
    }
  }
}
