package ddbt.lib

// Decode a tuple by splitting binary data, decoding it and calling f on each generated event
case class Decoder(f:TupleEvent=>Unit,adaptor:Adaptor=Adaptor("orderbook",Nil),splitter:Split=Split()) {
  private var data=Array[Byte]()
  def add(b:Array[Byte],n:Int) { if (n<=0) return;
    val l=data.length; val d=new Array[Byte](l+n);
    System.arraycopy(data,0,d,0,l); System.arraycopy(b,0,d,l,n); data=d
    var o:Int=0
    var s=splitter(data,o);
    while (s._1 != -1) {
      adaptor(data,s._1,s._2-s._1).foreach(e=>f(e))
      o=s._3; s=splitter(data,o)
    }
    if (o>0) {
      val l2 = data.length;
      val d2 = new Array[Byte](l2-o)
      System.arraycopy(data,o,d2,0,l2-o); data=d2
    }
  }
}

/*
 * Split defines how records are separated in the stream
 * - Explicit separator : Split(sep="\n")  sep as String or Array[Byte]
 * - Fixed size         : Split(n)         n the number of bytes per record
 * - Prefixed with size : Split.p(n=4)     n the prefix size in bytes
 */
abstract class Split extends Function2[Array[Byte],Int,(Int,Int,Int)] // buffer,offset => start,end,next_offset
object Split {
  def apply(p:Array[Byte]) = new Split { def apply(buf:Array[Byte],off:Int=0) = find(p,buf,off) match { case -1 => (-1,-1,-1) case x => (off,x,x+p.length) } }
  def apply(s:String="\n"):Split = apply(s.getBytes)
  def apply(n:Int):Split = new Split { def apply(buf:Array[Byte],off:Int=0) = { val l=buf.length-off; if (l<n) (-1,-1,-1) else (off,n+off,n+off) } }
  def p(bytes:Int=4):Split = new Split { def apply(buf:Array[Byte],off:Int=0) = { val l=buf.length; if (l<bytes) (-1,-1,-1) else {
    var i=off+bytes-1; var n:Int=0; while(i>=off) { n=(n<<8)|buf(i); i=i-1; }; if (l-off-bytes<n) (-1,-1,-1) else (off+bytes,off+bytes+n,off+bytes+n)
  }}}
  // Knuth-Morris-Pratt algorithm (O(data)+O(pattern))
  private def find(pattern:Array[Byte], data:Array[Byte], off:Int=0):Int = if (data.length==0 || pattern.length==0) -1 else { val skip=failure(pattern); var i=off; var j=0;
    while (i<data.length) { val di=data(i); while (j>0 && pattern(j)!=di) j=skip(j-1); if (pattern(j)==di) j=j+1; if (j==pattern.length) return i-pattern.length+1; i=i+1 }; -1
  }
  private def failure(pattern:Array[Byte]):Array[Int] = { val skip=new Array[Int](pattern.length); var i=1; var j=0;
    while (i<pattern.length) { val pi=pattern(i); while (j>0 && pattern(j)!=pi) j=skip(j-1); if (pattern(j)==pi) j=j+1; skip(i)=j; i=i+1 }; skip
  }
}

/*
 * Adaptor defines how a record is converted into tuples.
 * Usage: Adaptor(type,((op1,val1),(op2,val2),...))
 * - OrderBook : brokers = number of brokers
 *               bids, asks = relation names, null to disable
 *               deterministic = whether broker id is assigned randomly
 * - CSV       : name = string(schema name)
 *               schema = comma-separated types (see Parser types)
 *               delimited = ","
 *               action = "insert" | "delete" | "both" => col(0):Int=order, col(1):Int=is_insert
 */
abstract class Adaptor extends Function3[Array[Byte],Int,Int,List[TupleEvent]] // buffer,start,end => events
object Adaptor {
  def apply(name:String,options:List[(String,String)]) = {
    val m=options.map{case (k,v)=>(k.toLowerCase,v)}.toMap
    def i(k:String,v:Int) = m.get(k) match { case Some(x)=>Integer.parseInt(x) case None => v }
    def b(k:String,v:Boolean) = m.get(k) match { case Some(x)=>x.toLowerCase=="yes"||x.toLowerCase=="true"||x=="1" case None => v }
    def s(k:String,v:String) = m.get(k) match { case Some(x)=>x.toUpperCase case None => v }
    name.toUpperCase match {
      case "ORDERBOOK" => new OrderBook(i("brokers",10),s("bids","BIDS"),s("asks","ASKS"),b("deterministic",true))
      case "CSV" => new CSV(s("name","CSV"),s("schema","string"),s("delimiter",","),s("action","insert"))
      case x => sys.error("Adaptor '"+x+"' not found")
    }
  }

  class CSV(name:String,schema:String,delimiter:String=",",action:String) extends Adaptor {
    val dfp = new java.text.SimpleDateFormat("yyyy-MM-dd")
    val tfs:Array[String=>_]=schema.split(",").map{
      case "int"|"long" => (c:String) => java.lang.Long.parseLong(c)
      case "float"|"double" => (c:String) => java.lang.Double.parseDouble(c)
      case "date" => (c:String) => dfp.parse(c)
      case _ => (c:String) => c
    }
    val act:Int = action.toLowerCase match { case "insert"=>0 case "delete"=>1 case _=>2 }
    def apply(data:Array[Byte],off:Int,len:Int): List[TupleEvent] = {
      val rec = new String(data,off,len,"UTF-8").split(delimiter).zipWithIndex.map{ case(x,i) => tfs(i)(x) }.toList
      val ev = act match {
        case 0 => TupleEvent(TupleInsert, name, 0, rec)
        case 1 => TupleEvent(TupleDelete, name, 0, rec)
        case _ => TupleEvent(if (rec(1)==1) TupleInsert else TupleDelete, name, rec(0).asInstanceOf[Long], rec.drop(2))
      }
      List(ev)
    }
  }

  class OrderBook(brokers:Int=10,bids:String="BIDS",asks:String="ASKS",deterministic:Boolean=true) extends Adaptor {
    case class BookRow(t:Long, id:Long, brokerId:Long, volume:Double, price:Double) {
      def toList = List[Any](t.toDouble, id, brokerId, volume, price)
    }
    type Hist = java.util.HashMap[Long,BookRow]
    val asksMap = new Hist()
    val bidsMap = new Hist()

    def apply(data:Array[Byte],off:Int,len:Int): List[TupleEvent] = {
      val col = new String(data,off,len,"UTF-8").split(",")
      val t = java.lang.Long.parseLong(col(0))
      val id = java.lang.Long.parseLong(col(1))
      val volume = java.lang.Double.parseDouble(col(3))
      val price = java.lang.Double.parseDouble(col(4))
      def red(h:Hist,rel:String) = { val x=h.remove(id)
        if (x==null) Nil else { val nv = x.volume-volume
          TupleEvent(TupleDelete, rel, t, x.toList) :: (if (nv <= 0.0) Nil else {
            val r = BookRow(t, id, x.brokerId, nv, x.price); h.put(id,r)
            List(TupleEvent(TupleInsert, rel, t, r.toList))
          })
        }
      }
      col(2) match {
        case "B" if (bids!=null) => // place bid
          val brokerId = (if (deterministic) id else scala.util.Random.nextInt) % brokers
          val row = BookRow(t, id, brokerId, volume, price); bidsMap.put(id,row)
          List(TupleEvent(TupleInsert, bids, t, row.toList))
        case "S" if (asks!=null) => // place ask
          val brokerId = (if (deterministic) id else scala.util.Random.nextInt) % brokers
          val row = BookRow(t, id, brokerId, volume, price); asksMap.put(id,row)
          List(TupleEvent(TupleInsert, asks, t, row.toList))
        case "E" => // match
          red(bidsMap,bids) ::: red(asksMap,asks)
        case "D" => // | "F" cancel
          if (bidsMap.containsKey(id)) List(TupleEvent(TupleDelete, bids, t, bidsMap.remove(id).toList)) else
          if (asksMap.containsKey(id)) List(TupleEvent(TupleDelete, asks, t, asksMap.remove(id).toList)) else Nil
        case _ => Nil
      }
    }
  }
}

// ------------------- to be moved into general messages
/*
abstract sealed class DBTEvent
case object EndOfStream extends DBTEvent
case class TupleEvent(op:TupleOp,stream:String,tx:Long,data:List[Any]) extends DBTEvent

abstract sealed class TupleOp
case object TupleInsert extends TupleOp
case object TupleDelete extends TupleOp
*/
// -------------------
/*
object Decoder {
  def main(args:Array[String]) {
    def f(e:TupleEvent) {
      val op = if (e.op==TupleInsert) "+" else "-"
      println(e.stream+" "+op+"("+e.tx+") : "+e.data);
    }
    val d = Decoder(f)
  
    val in = new java.io.FileInputStream("resources/data/finance.csv")
    val buf = new Array[Byte](4)
    var n:Int = 0
    do {
      n=in.read(buf)
      d.add(buf,n);
    } while (n>0);
  }
}
*/
