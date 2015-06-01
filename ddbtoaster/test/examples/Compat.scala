package ddbt.test.examples
import ddbt.lib._

object Compat {
  // Stream definitions (used for manual debugging only)
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
