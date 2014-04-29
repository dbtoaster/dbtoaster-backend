package ddbt.lib
import Messages._

/**
 * These class helps creating a stream of events from a record data.
 * The data format is defined in terms of records and fields in the record:
 * - Records are separated according to Split (usually by a new line).
 * - Records are parsed then using an Adaptor:
 *   - OrderBook : a special adaptor to create finance streams
 *   - CSV       : decodes CSV records, format needs to be specified
 *
 * To read from any buffered data source, a Decoder is used. It appends data
 * from a buffer and produces TupleEvents that are passed to a callback.
 *
 * Finally, to read from multiple sources and hide buffering details, SourceMux
 * uses multiple InputStream/Decoder pairs and takes care of generating streams.
 *
 * @author TCK
 */

/* Decode a tuple by splitting binary data, decoding it and calling f on each generated event */
case class Decoder(f:TupleEvent=>Unit,adaptor:Adaptor=Adaptor("ORDERBOOK",Nil),splitter:Split=Split()) {
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
  def eof() { if(data.length>0) adaptor(data,0,data.length).foreach(e=>f(e)) }
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
  def apply(n:Int):Split = new Split { def apply(buf:Array[Byte],off:Int=0) = { val l=buf.length-off; if (l < n) (-1,-1,-1) else (off,n+off,n+off) } }
  def p(bytes:Int=4):Split = new Split { def apply(buf:Array[Byte],off:Int=0) = { val l=buf.length; if (l < bytes) (-1,-1,-1) else {
    var i=off+bytes-1; var n:Int=0; while(i >= off) { n=(n << 8)|buf(i); i=i-1; }; if (l-off-bytes < n) (-1,-1,-1) else (off+bytes,off+bytes+n,off+bytes+n)
  }}}
  // Knuth-Morris-Pratt algorithm (O(data)+O(pattern))
  private def find(pattern:Array[Byte], data:Array[Byte], off:Int=0):Int = if (data.length==0 || pattern.length==0) -1 else { val skip=failure(pattern); var i=off; var j=0;
    while (i < data.length) { val di=data(i); while (j>0 && pattern(j)!=di) j=skip(j-1); if (pattern(j)==di) j=j+1; if (j==pattern.length) return i-pattern.length+1; i=i+1 }; -1
  }
  private def failure(pattern:Array[Byte]):Array[Int] = { val skip=new Array[Int](pattern.length); var i=1; var j=0;
    while (i < pattern.length) { val pi=pattern(i); while (j>0 && pattern(j)!=pi) j=skip(j-1); if (pattern(j)==pi) j=j+1; skip(i)=j; i=i+1 }; skip
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
 *               delimiter = ","
 *               action = "insert" | "delete" | "both" => col(0):Int=order, col(1):Int=is_insert
 */
abstract class Adaptor extends Function3[Array[Byte],Int,Int,List[TupleEvent]] // buffer,start,end => events
object Adaptor {
  def apply(name:String,options:Map[String,String]):Adaptor = apply(name,options.toList)
  def apply(name:String,options:List[(String,String)]):Adaptor = {
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

  class CSV(name:String,schema:String,delimiter:String=",",action:String="insert") extends Adaptor {
    private val dfp = new java.text.SimpleDateFormat("yyyy-MM-dd")
    val tfs:Array[String=>_]=schema.split(",").map{
      case "int"|"long" => (c:String) => java.lang.Long.parseLong(c)
      case "float"|"double" => (c:String) => java.lang.Double.parseDouble(c)
      case "date" => (c:String) => dfp.parse(c)
      case "string" => (c:String) => if (c.length==0) "" else c(0) match {
        case '\'' => c.substring(1,c.length-1).replaceAll("\\\\'","'")
        case '"' => c.substring(1,c.length-1).replaceAll("\\\\\"","\"")
        case _ => c
      }
      case _ => (c:String) => c
    }
    val ev : Array[String] => (TupleOp,Array[String]) = action.toLowerCase match {
      case "insert" => (rec:Array[String]) => (TupleInsert,rec)
      case "delete" => (rec:Array[String]) => (TupleDelete,rec)
      case _        => (rec:Array[String]) => (if (rec(1)=="1") TupleInsert else TupleDelete, rec.drop(2)) // tx=java.lang.Long.parseLong(rec(0))
    }
    def apply(data:Array[Byte],off:Int,len:Int): List[TupleEvent] = {
      val (op:TupleOp,rec:Array[String]) = ev(new String(data,off,len,"UTF-8").split(delimiter))
      List(TupleEvent(op,name,rec.zipWithIndex.map{ case(x,i) => tfs(i)(x) }.toList))
    }
  }

  class OrderBook(brokers:Int=10,bids:String="BIDS",asks:String="ASKS",deterministic:Boolean=true) extends Adaptor {
    case class BookRow(t:Long, id:Long, brokerId:Long, volume:Double, price:Double) {
      def pack = List[Any](t.toDouble, id, brokerId, volume, price) // XXX: t as Double is a legacy from DBToaster
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
          TupleEvent(TupleDelete, rel, x.pack) :: (if (nv <= 0.0) Nil else {
            val r = BookRow(x.t, id, x.brokerId, nv, x.price); h.put(id,r)
            List(TupleEvent(TupleInsert, rel, r.pack))
          })
        }
      }
      col(2) match {
        case "B" if (bids!=null) => // place bid
          val brokerId = (if (deterministic) id else scala.util.Random.nextInt) % brokers
          val row = BookRow(t, id, brokerId, volume, price); bidsMap.put(id,row)
          List(TupleEvent(TupleInsert, bids, row.pack))
        case "S" if (asks!=null) => // place ask
          val brokerId = (if (deterministic) id else scala.util.Random.nextInt) % brokers
          val row = BookRow(t, id, brokerId, volume, price); asksMap.put(id,row)
          List(TupleEvent(TupleInsert, asks, row.pack))
        case "E" => // match
          red(bidsMap,bids) ::: red(asksMap,asks)
        case "D" => // | "F" cancel
          if (bidsMap.containsKey(id)) List(TupleEvent(TupleDelete, bids, bidsMap.remove(id).pack)) else
          if (asksMap.containsKey(id)) List(TupleEvent(TupleDelete, asks, asksMap.remove(id).pack)) else Nil
        case _ => Nil
      }
    }
  }
}

/*
 * SourceMux reads from multiple inputs, decodes and forward data to one Actor.
 * Discussion: thread are used as there is no non-blocking interface for both
 *   sockets and file I/O in Java. Additionally, the number of stream is fixed,
 *   and usually small, so thread switching penalty should be low.
 */
import java.io.InputStream
case class SourceMux(streams:Seq[(InputStream,Decoder)],parallel:Int=0,bufferSize:Int=32*1024) {
  private def read1(in:InputStream,d:Decoder) {
    val buf = new Array[Byte](bufferSize)
    var n:Int = 0
    do { n=in.read(buf); d.add(buf,n); } while (n>0);
    d.eof(); in.close()
  }

  // Preload in deterministic alternating order
  import java.util.LinkedList
  private var q : LinkedList[TupleEvent] = null
  if (parallel==2) {
    q=new LinkedList[TupleEvent]()
    val qq = new LinkedList[LinkedList[TupleEvent]]()
    streams.foreach { case (in,d) => val iq=new LinkedList[TupleEvent]; read1(in,Decoder((e:TupleEvent)=>iq.offer(e),d.adaptor,d.splitter)); qq.offer(iq) }
    var p=qq.poll; while (p!=null) { val e=p.poll; if (e!=null) { q.offer(e); qq.offer(p) }; p=qq.poll }
  }

  def read() = parallel match {
    case 0 => streams.foreach { case(in,d) => read1(in,d) }
    case 1 => val ts = streams.map { case (in,d) => new Thread{ override def run() { read1(in,d) }} }
              ts.foreach(_.start); ts.foreach(_.join)
    case 2 => if (streams.size>0) { val f=streams(0)._2.f; var e=q.poll; while (e!=null) { f(e); e=q.poll } }
    case _ => sys.error("Unsupported parallel mode")
  }
}

/*
 * SourceMuxPull is similar to SourceMux but tuples are explicitly requested by
 * calling the next() function. next() returns either the next TupleEvent or
 * EndOfStream if all streams have been exhausted.
 */
/*
case class SourceMuxPull(streams:Seq[(InputStream,Adaptor,Split)],parallel:Int=0,bufferSize:Int=32*1024) {
  type TQueue = scala.collection.mutable.Queue[TupleEvent]
  case class State(buf:Array[Byte],q:TQueue,in:InputStream,d:Decoder)
  private val st = streams.map { s=> val q=new TQueue; State(new Array[Byte](bufferSize),q,s._1,Decoder((ev:TupleEvent)=>{ q.enqueue(ev) },s._2, s._3)) }.toArray
  private var valid:Int = streams.size // number of valid streams
  private val r = new scala.util.Random
  private def read(i:Int):StreamEvent = {
    if (i>=valid) EndOfStream
    else if (!st(i).q.isEmpty) st(i).q.dequeue()
    else {
      val s = st(i)
      var n:Int = 0
      do { n=s.in.read(s.buf); s.d.add(s.buf,n); } while (n>0 && s.q.isEmpty);
      if (n<=0) { s.d.eof(); close(i); read(0) } else s.q.dequeue()
    }
  }
  private def close(i:Int) { st(i).in.close; valid=valid-1; if (i<valid) st(i)=st(valid); st(valid)=null; }
  def next():StreamEvent = read(if (parallel!=0) r.nextInt(valid) else 0)
}
*/

// http://www.cafeaulait.org/slides/javapolis/toptenmyths/14.html
// http://docs.oracle.com/javase/7/docs/api/java/nio/channels/AsynchronousFileChannel.html
