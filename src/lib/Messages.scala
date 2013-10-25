package ddbt.lib

/**
 * This object encapsulates all the function that are related to messages:
 * 1. External events: streams events, and collecting result
 * 2. Internal messages exchanged between peers using batching,
 *    acknowledgements and custom serialization.
 *
 * @author TCK
 */
object Messages {
  // --------------- External messages
  type TupleOp = Int
  final val TupleDelete : TupleOp = 0x00
  final val TupleInsert : TupleOp = 0x01

  /** Stream event messages sent by sources to the system. */
  abstract sealed class StreamEvent
  case class TupleEvent(op:TupleOp,stream:String,data:List[Any]) extends StreamEvent // XXX: serialize stream name as Byte/Int(hashCode?)
  case object SystemInit extends StreamEvent
  case object EndOfStream extends StreamEvent // get snapshot(0) and shut the system down
  case class GetSnapshot(view:List[Int]) extends StreamEvent // request a snapshot of some maps

  // --------------- Internal cluster messages
  import java.io._
  import java.util.Date

  // Internal types are integer (for performance) but must be in Short range for serialization
  type MapRef = Int  // map reference
  type FunRef = Int  // function reference
  type NodeRef = Int // node reference: workers are 0..N-1, master_ref = # workers
  def FunRef0(i:Int):FunRef = java.lang.Short.MIN_VALUE+i // for internal functions

  // Note: by using NodeRef instead of ActorRef, we decouple from Akka architecture
  // and possibly allow replication by having virtual nodes spanning over multiple
  // hosts (this can also be achieved using Akka Routing).
  // XXX: find a way to support duplicate responses for AggPart

  /** Data (internal) messages */
  abstract sealed class Msg // data message (can be batched)
  case class Get[K](map:MapRef,key:K) extends Msg // => Val[K,V]
  case class Val[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Add[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Set[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Clear[P](map:MapRef,part:Int,partKey:P) extends Msg
  case class Foreach(f:FunRef,args:Array[Any]) extends Msg
  case class Agg(id:Int,f:FunRef,args:Array[Any]) extends Msg // => AggPart(id,_)
  case class AggPart[R](id:Int,res:R) extends Msg
  case class Ack(to:Array[NodeRef],num:Array[Int]) extends Msg // workers->master

  /** Message accumulator for batching and custom and serialization for internal messages. */
  class Batch() {
    private val data = new java.util.LinkedList[Msg]()
    private var os : ObjectOutputStream = null
    private var is : ObjectInputStream = null
    private def wr(obj:Any):Unit = obj match {
      case null => os.writeByte('N')
      case l:Long => os.writeByte('L'); os.writeLong(l)
      case d:Double => os.writeByte('F'); os.writeDouble(d)
      case d:Date => os.writeByte('D'); os.writeLong(d.getTime)
      case s:String => os.writeByte('S'); os.writeUTF(s)
      case a:Array[_] => os.writeByte('A'); os.writeInt(a.size); a.foreach(wr)
      case Tuple1(a) => os.writeByte('1'); wr(a);
      case Tuple2(a,b) => os.writeByte('2'); wr(a); wr(b);
      case Tuple3(a,b,c) => os.writeByte('3'); wr(a); wr(b); wr(c);
      case Tuple4(a,b,c,d) => os.writeByte('4'); wr(a); wr(b); wr(c); wr(d);
      case Tuple5(a,b,c,d,e) => os.writeByte('5'); wr(a); wr(b); wr(c); wr(d); wr(e);
      case Tuple6(a,b,c,d,e,f) => os.writeByte('6'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f);
      case Tuple7(a,b,c,d,e,f,g) => os.writeByte('7'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f); wr(g);
      case Tuple8(a,b,c,d,e,f,g,h) => os.writeByte('8'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f); wr(g); wr(h);
      case Tuple9(a,b,c,d,e,f,g,h,i) => os.writeByte('9'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f); wr(g); wr(h); wr(i);
      case m:M3MapBase[_,_] => os.writeByte('M'); wr(m.zero); os.writeInt(m.size); m.foreach{(k:Any,v:Any)=>wr(k);wr(v)}
      case o => os.writeByte('O'); os.writeObject(o)
    }
    private def rd():Any = is.readByte match {
      case 'N' => null
      case 'L' => is.readLong
      case 'F' => is.readDouble
      case 'D' => new Date(is.readLong)
      case 'S' => is.readUTF
      case 'A' => val n=is.readInt; (0 until n).map(x=>rd()).toArray
      case '1' => Tuple1(rd())
      case '2' => Tuple2(rd(),rd())
      case '3' => Tuple3(rd(),rd(),rd())
      case '4' => Tuple4(rd(),rd(),rd(),rd())
      case '5' => Tuple5(rd(),rd(),rd(),rd(),rd())
      case '6' => Tuple6(rd(),rd(),rd(),rd(),rd(),rd())
      case '7' => Tuple7(rd(),rd(),rd(),rd(),rd(),rd(),rd())
      case '8' => Tuple8(rd(),rd(),rd(),rd(),rd(),rd(),rd(),rd())
      case '9' => Tuple9(rd(),rd(),rd(),rd(),rd(),rd(),rd(),rd(),rd())
      case 'M' => val m=new M3MapBase[Any,Any](rd(),false,null); var n=is.readInt; if (n>0) do { m.put(rd(),rd()); n-=1 } while (n>0); m
      case 'O' => is.readObject
      case _ => sys.error("Encoding error")
    }

    // Accumulate and serialize
    def add(msg:Msg) = data.add(msg)
    def size = data.size
    def clear = data.clear
    def pack():Array[Byte] = {
      val s=new ByteArrayOutputStream; os=new ObjectOutputStream(s); var n=data.size; os.writeInt(n)
      if (n>0) do { data.remove match { 
        case Get(m,k) => os.writeByte('g'); os.writeShort(m); wr(k)
        case Val(m,k,v) => os.writeByte('v'); os.writeShort(m); wr(k); wr(v)
        case Add(m,k,v) => os.writeByte('a'); os.writeShort(m); wr(k); wr(v)
        case Set(m,k,v) => os.writeByte('s'); os.writeShort(m); wr(k); wr(v)
        case Clear(m,p,k) => os.writeByte('c'); os.writeShort(m); os.writeInt(p); wr(k)
        case Foreach(f,as) => os.writeByte('f'); os.writeShort(f); wr(as)
        case Agg(id,f,as) => os.writeByte('x'); os.writeInt(id); os.writeShort(f); wr(as)
        case AggPart(id,r) => os.writeByte('p'); os.writeInt(id); wr(r)
        case Ack(ts,ns) => os.writeByte('k'); os.writeInt(ts.size); ts.foreach(t=>os.writeShort(t)); ns.foreach(n=>os.writeInt(n))
      }; n-=1 } while (n>0); os.close; os=null; s.toByteArray
    }
    // Deserialize
    def unpack(bytes:Array[Byte]):Array[Msg] =  {
      is=new java.io.ObjectInputStream(new ByteArrayInputStream(bytes));
      val n=is.readInt; val res=new Array[Msg](n)
      var i=0; if (i<n) do { res(i)=is.readByte match {
        case 'g' => Get(is.readShort,rd)
        case 'v' => Val(is.readShort,rd,rd)
        case 'a' => Add(is.readShort,rd,rd)
        case 's' => Set(is.readShort,rd,rd)
        case 'c' => Clear(is.readShort,is.readInt,rd)
        case 'f' => Foreach(is.readShort,rd.asInstanceOf[Array[Any]])
        case 'x' => Agg(is.readInt,is.readShort,rd.asInstanceOf[Array[Any]])
        case 'p' => AggPart(is.readInt,rd)
        case 'k' => val c=is.readInt; val ts=new Array[NodeRef](c); val ns=new Array[Int](c); var i=0;
                    if (n>0) { do { ts(i)=is.readShort; i+=1 } while (i<n); i=0; do { ns(i)=is.readInt; i+=1 } while (i<n); }; Ack(ts,ns)
        case _ => sys.error("Encoding error")
      }; i+=1; } while (i<n); is.close; is=null; res
    }
  }

  /**
   * Messages manager for the cluster. For a cluster with N workers, the
   * workers are indexed from 0 to N-1 and the master has index N.
   * Counters represent the number of unacknowledged messages.
   * Note: ack to master ignored, its counter is only present for uniformity
   */
  class MsgBuffer(N:Int,me:NodeRef,send_f:(NodeRef,Array[Byte])=>Unit) {
    val buf = new Array[Batch](N+1)
    val ctr = new Array[Int](N+1)
    def unpack(payload:Array[Byte]) = buf(0).unpack(payload)
    def ack { ctr(me) -= 1 }
    def send(to:NodeRef,msg:Msg) { buf(to).add(msg); if (!msg.isInstanceOf[Get[_]] && !msg.isInstanceOf[Agg]) ctr(to)+=1; }
    def flush() {
      // send to all workers
      var i=0; var n=0; do { if (buf(i).size>0) { send_f(i,buf(i).pack) }; if (ctr(i)!=0) n+=1; } while (i<N)
      // piggyback acknowledgements for master 
      if (n>0) {
        val to=new Array[NodeRef](n); val num=new Array[NodeRef](n)
        i=0; var j=0; do { val c=ctr(i); if (c!=0) { ctr(i)=0; to(j)=i; num(j)=c; j+=1 } } while (i<n)
        buf(N).add(Ack(to,num))
      }
      // send messages+ack to the master
      if (buf(N).size>0) send_f(N,buf(N).pack)
    }
  }
}
