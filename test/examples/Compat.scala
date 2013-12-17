// Legacy fuctions used by tests, to be migrated
package ddbt.test.examples
import ddbt.lib._

object Compat {
/*
  def time(ns:Long) = { val us=ns/1000; ("%d.%06d").format(us/1000000,us%1000000) }
  def bench[T](name:String,count:Int,f:()=>(Long,T)):T = {
    val out = (0 until math.max(1,count)).map { x => f() }
    val res = out.map(_._2).toList; res.tail.foreach(r=> assert(r==res.head,"Inconsistent results: "+res.head+" != "+r))
    val ts = out.map(_._1).sorted;
    println(name+": "+time(if (count%2==0) (ts(count/2)+ts(count/2-1))/2 else ts(count/2))+" ["+time(ts(0))+", "+time(ts(count-1))+"] (sec)"); res.head
  }

  // Query benchmark, supported arguments:
  //   -n<num>       number of samples (default=1)
  //   -d<set>       dataset selection (can be repeated), (default=standard)
  //   -h            hide the benchmark time
  //   -s            silent the query output
  //   -np           do not use parallel streams
  def bench2(args:Array[String],run:(String,Boolean)=>(StreamStat,List[Any]),print:List[Any]=>Unit=null) {
    val parallel=args.contains("-np")
    var count:Int=1; args.filter(a=>a.startsWith("-n")).foreach { a=>count=a.substring(2).toInt }
    var ds=List[String](); args.filter(a=>a.startsWith("-d")).foreach { a=>ds=ds:::List(a.substring(2)) }; if (ds.size==0) ds=List("standard")
    ds.foreach { d=> var res0:List[Any]=null; var ts:List[StreamStat]=Nil;
       // XXX: fix this
      val warm = 2
      (0 until math.max(1,count)).foreach { x => val ((t,finished,tupProc),res)=run(d,parallel);
        if(x >= warm && count > warm) { ts=(t,finished,tupProc)::ts; }; if (res0==null) res0=res //else assert(res0==res,"Inconsistent results: "+res0+" != "+res)
      }
      ts = ts.sorted // scala.util.Sorting.stableSort(ts, (e1: StreamStat, e2: StreamStat) => e1._3.asInstanceOf[Double]/e1._1.asInstanceOf[Double] < e2._3.asInstanceOf[Double]/e2._1.asInstanceOf[Double]).toList
      val tsMed = ddbt.Utils.med3(ts)
      if (!args.contains("-h")) println(d+": ("+time(tsMed._1)+","+tsMed._2+","+tsMed._3+") [("+time(ts(0)._1)+","+ts(0)._2+","+ts(0)._3+"), ("+time(ts(ts.size-1)._1)+","+ts(ts.size-1)._2+","+ts(ts.size-1)._3+")] (sec, "+ts.size+" samples)")
      if (!args.contains("-s") && res0!=null && print!=null) print(res0)
    }
  }
*/
  // ---------------------------------------------------------------------------
  // Stream definitions (used for manual debugging only)
  // XXX: remove this

  private def str(file:String,a:Adaptor) = (new java.io.FileInputStream("examples/data/"+file+".csv"),a,Split())
  def streamsFinance(s:String="") = Seq(str("finance"+(if (s!="") "-"+s else ""),Adaptor("orderbook",Nil)))
  def streamsRST(ss:Seq[String]=Seq("r")) = ss.map { s=> str("simple/"+s,new Adaptor.CSV(s.toUpperCase,"int,int")) }

  private def tpch(ss:Seq[String]) = ss.map{ n=>str("tpch/"+n,new Adaptor.CSV(n.toUpperCase,n match {
    case "orders" => "int,int,string,float,date,string,string,int,string"
    case "customer" => "int,string,string,int,string,float,string,string"
    case "supplier" => "int,string,string,int,string,float,string"
    case "lineitem" => "int,int,int,int,float,float,float,float,string,string,date,date,date,string,string,string"
  },"\\|")) }
  def streamsTPCH1() = tpch(Seq("lineitem"))
  def streamsTPCH13() = tpch(Seq("orders","customer"))
  def streamsTPCH15() = tpch(Seq("lineitem","supplier"))
  def streamsTPCH18() = tpch(Seq("lineitem","orders","customer"))

}
