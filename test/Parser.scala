package ddbt.test

import org.scalatest._
import java.io._

class ParserSpec extends FunSpec {
  import ddbt.Compiler._
  import ddbt.Utils._
  import ddbt.frontend._

  val files=exec(Array("find","resources/queries","-name","*.sql","-and","-not","-name","schemas.sql"))._1.split("\n")
  val t = System.currentTimeMillis;
  print("Toasting ...")
  val m3src = files.par.map { f=>toast(new File(f)) }
  println(" done ("+(System.currentTimeMillis-t)+"ms).")
  
  val num=files.size
  it("SQL testing files ("+num+")") { assert(num>0,"No SQL file") }
  
  (m3src.toList zip files).foreach{ case (src,file)=>
    describe(file) {
      it("SQL parsing") { SQLParser(file) }
      it("M3 parsing") {
        val s1=M3Parser(src)
        val s2=M3Parser(s1.toString)
        assert(s2==s1,"Double parsing does not preserve semantics")
      }
    }
  }
}
