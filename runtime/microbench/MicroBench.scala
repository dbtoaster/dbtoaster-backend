
package ddbt.micro
import ddbt.lib.store._
 
case class SEntry4_DDSD(var _1: Double, var _2: Double, var _3: String, var _4: Double) extends Entry(4) {def this() = this(-1.7976931348623157E308, -1.7976931348623157E308, null, -1.7976931348623157E308) ; def copy = SEntry4_DDSD(_1, _2, _3, _4); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry4_DDSD]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4} }
class SCExecutor {

            
  val x366 = Array[EntryIdx[SEntry4_DDSD]](SEntry4_DDSD_Idx1)
  val customerTbl = new Store[SEntry4_DDSD](1, x366);
  val customerTblIdx0 = customerTbl.index(0, IHash, true, -1)
  

   object SEntry4_DDSD_Idx1 extends EntryIdx[SEntry4_DDSD] {
    override def hash(x339 : SEntry4_DDSD) = {
      var x340: Int = 0;
      val x341 = x340;
      x340 = (x341.^((((((x339._1).hashCode()).+(-1640531527)).+((x341.<<(6)))).+((x341.>>(2))))))
      val x351 = x340;
      x351
    }
    override def cmp(x353 : SEntry4_DDSD , x354 : SEntry4_DDSD) = {
      var x355: Int = 0;
      if(((x353._1).==((x354._1)))) {
        x355 = 0
      } else {
        x355 = 1
      }
      val x362 = x355;
      x362
    }
  }

  class fun1(customerTbl : Store[SEntry4_DDSD]) extends (() => Int ) {
    def apply() = {      
      var x148: Int = 0;
      customerTbl.foreach(({ x149: SEntry4_DDSD => {
          val x152 = (x149._4).-((x149._3));
          val x413 = SEntry2_DS(x152, (x149._2));
          if((x152.<((1000.toDouble)))) {
            val x168 = x148;
            x148 = (x168.+(1))
          } else {
          }
          ()
        }
      }))
      val x174 = x148;
      var x29: Int = x174;
      1
    }
  }

}
