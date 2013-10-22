package ddbt.test
import org.scalatest._

// sbt 'test:run-main ddbt.test.ToastSpeed'
object ToastSpeed {
  import ddbt.Utils._
  import ddbt.Compiler.toast
  import ddbt.unit.UnitTest.sqlFiles

  def main(args:Array[String]) {
    sqlFiles().foreach { file =>
      //println("-------------- "+file)
      val t2 = ns(()=>for (i<-0 until 5) toast("m3","-O2",file))._1
      val t3 = ns(()=>for (i<-0 until 5) toast("m3","-O3",file))._1
      println("O2:"+time(t2)+" O3:"+time(t3)+" ==> "+"%5.1f".format(100*(t3)*1.0/(t2))+"% in "+file)
    }
  }
}
