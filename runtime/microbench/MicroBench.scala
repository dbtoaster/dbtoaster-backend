
package ddbt.micro
import ddbt.lib.store._
 

class SCExecutor {

            
  val x211 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1)))
  val customerTbl = new Store[GenericEntry](1, x211);
  val customerTblIdx0 = customerTbl.index(0, IHash, true, -1)
  

   
  class fun1(customerTbl : Store[GenericEntry]) extends (() => Int ) {
    def apply() = {      
      var x181: Int = 0;
      customerTbl.foreach(({ x182: GenericEntry => {
          val x183 = x182.get[Double](4);
          val x184 = x182.get[Double](3);
          val x186 = x182.get[String](2);
          val x188 = GenericEntry.apply("SteNewSEntry", (x183.-(x184)), x186);
          val x189 = x188.get[Double](1);
          if((x189.<((1000.toDouble)))) {
            val x192 = x182.get[Double](4);
            val x193 = x182.get[Double](3);
            val x195 = x182.get[String](2);
            val x197 = GenericEntry.apply("SteNewSEntry", (x192.-(x193)), x195);
            val x198 = x197.get[String](2);
            val x200 = GenericEntry.apply("SteNewSEntry", x198);
            val x201 = x181;
            x181 = (x201.+(1))
          } else {
          }
          ()
        }
      }))
      val x207 = x181;
      var x29: Int = x207;
      1
    }
  }

}
