package ddbt.test
import ddbt.Utils._
import ddbt.lib.store._
import ddbt.lib._

// Compares the performance of Store VS M3Map for (Long,Double) => Long

case class ELDL(var _1:Long, var _2:Double, var _3:Long) extends Entry(2) {
  def cmp(i:Int, e0:Entry) = {
    val e=e0.asInstanceOf[ELDL];
    if (i==0) (if (_1<e._1) -1 else if (_1==e._1) (if (_2<e._2) -1 else if (_2==e._2) 0 else 1) else 1)
    else if (i==1) (if (_1<e._1) -1 else if (_1==e._1) 0 else 1)
    else 0
  }
  def hash(i:Int) = if (i==0) ((_1 << 16) + (_1 >>> 5) ^ _2.toLong).toInt else if (i==1) _1.toInt else 0
  def copy = ELDL(_1,_2,_3)
}

object M3Store {
  val s = new Store[ELDL](2); s.index(0,IHash,true); s.index(1,IHash,false)
  val m = M3Map.make[(Long,Double),Long]((x:(Long,Double))=>x._1)

  val N = 300000
  val S = 30

  def t(s:String)(f: =>Unit) = {
    val r = (0 until S).map(x=>ns(()=>f)._1).sorted.map(x=>time(x,false))
    println(s+": "+r(0)+", "+r((S+1)/2)+", "+r(S-1))
  }

  def main(args: Array[String]) {
    println("Distinct add:")
    t("- Store") { var i=0; while (i<N) { s.insert(ELDL(i,i,i)); i+=1 } }; s.clear
    t("- Map") { var i=0; while (i<N) { m.add((i,i),i); i+=1 } }; m.clear

    println("Cumulative add:")
    t("- Store") { var i=0; while (i<N) {
      val e = ELDL(i%10,i%100,i)
      if (e._3!=0) {
        val c = s.get(0,e)
        if (c==null) s.insert(e); else { c._3+=e._3; if (c._3==0) s.delete(c); }
      }
      i+=1 } }
    t("- Map") { var i=0; while (i<N) { m.add((i%10,i%100),i); i+=1 } }

    println("Foreach:"); val ff=50
    t("- Store") { var a=0; var i=0; while(i<ff) { i+=1; s.foreach{ e => a+=e._3.toInt }; }; a }
    t("- Map") { var a=0; var i=0; while(i<ff) { i+=1; m.foreach{ (k,v) => a+=v.toInt; }; }; a }

    println("Slice:"); val sf=5000
    t("- Store") { var a=0; var i=0; while(i<sf) { i+=1; s.slice(1,ELDL(2,2,2),{ e => a+=e._3.toInt }); }; a }
    t("- Map") { var a=0; var i=0; while(i<sf) { i+=1; m.slice(0,2L).foreach{ (k,v) => a+=v.toInt }; }; a }

    println("Cumulative deletion:")
    t("- Store") { var i=0; while (i<N) {
      val e = ELDL(i%10,i%100,-i)
      if (e._3!=0) {
        val c = s.get(0,e)
        if (c==null) s.insert(e); else { c._3+=e._3; if (c._3==0L) s.delete(c); }
      }
      i+=1 } }
    t("- Map") { var i=0; while (i<N) { m.add((i%10,i%100),-i); i+=1 } }

    println(m.size+" == "+s.size)




    // (0 until N*N) foreach { x => s.insert(if (uniq) E(x,x,"foo") else E(x%N,x/N,"foo")) }

  }
}
