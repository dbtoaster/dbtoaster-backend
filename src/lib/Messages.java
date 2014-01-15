package ddbt.lib;
import ddbt.lib.Messages.*;
import akka.serialization.JSerializer;
import java.nio.ByteBuffer;
import java.util.Date;
import java.io.*;

/*
 * This is a manual efficient serializer for ddbt.lib.Message subclasses.
 * It need to be synchronized with the Scala counterpart.
 *
 * @author TCK
 */
class MessageSerializer extends JSerializer {
  public static final String conf() { return
    "akka.actor {\n"+
    //"  serialize-messages = on\n"+
    "  serializers { ddbtmsg = \"ddbt.lib.MessageSerializer\" }\n"+
    "  serialization-bindings { \"ddbt.lib.Msg\" = ddbtmsg }\n"+
    "}\n";
  }

  public boolean includeManifest() { return false; }
  public int identifier() { return 54321; }

  private static class BBInputStream extends InputStream {
    private ByteBuffer buf;
    public BBInputStream(ByteBuffer buf) { this.buf=buf; }
    public int read() throws IOException { if (!buf.hasRemaining()) { return -1; } return buf.get() & 0xFF; }
    public int read(byte[] bytes, int off, int len) throws IOException { if (!buf.hasRemaining()) return -1;
        len=Math.min(len,buf.remaining()); buf.get(bytes,off,len); return len;
    }
  }
  private static class BBOutputStream extends OutputStream {
    private ByteBuffer buf;
    public BBOutputStream(ByteBuffer buf) { this.buf=buf; }
    public void write(int b) throws IOException { buf.put((byte) b); }
    public void write(byte[] bytes, int off, int len) throws IOException { buf.put(bytes, off, len); }
  }

  private static class Sz { int s; };
  private int sz(Object obj) {
    if (obj==null) return 1;
    else if (obj instanceof Long || obj instanceof Double || obj instanceof Date) return 9;
    else if (obj instanceof String) return 5+((String)obj).getBytes().length;
    else if (obj instanceof Object[]) { Object[]a=(Object[])obj; int n=a.length; int s=5; for (int i=0;i<n;++i) s+=sz(a[i]); return s; }
    else if (obj instanceof M3MapBase) {
      @SuppressWarnings("unchecked") M3MapBase<Object,Object> m=(M3MapBase<Object,Object>)obj;
      final Sz s=new Sz(); s.s=5+sz(m.zero()); m.foreach(m.new Fun2() { public void apply(Object k, Object v) { s.s+=sz(k)+sz(v); }}); return s.s;
    }
    if (obj instanceof scala.Product) { scala.Product p=(scala.Product)obj; int a=p.productArity(); if (a<=10) { int s=1; for (int i=0;i<a;++i) s+=sz(p.productElement(i)); return s; } }
    try { ByteArrayOutputStream s=new ByteArrayOutputStream(); ObjectOutputStream os=new ObjectOutputStream(s); os.writeObject(obj); os.close(); return 1+s.toByteArray().length; } catch(Exception e) { return -1; }
  }
  private void wr(final ByteBuffer bb, Object obj) {
    if (obj==null) bb.put((byte)'N');
    else if (obj instanceof Long) bb.put((byte)'L').putLong(((Long)obj).longValue());
    else if (obj instanceof Double) bb.put((byte)'F').putDouble(((Double)obj).doubleValue());
    else if (obj instanceof Date) bb.put((byte)'D').putLong(((Date)obj).getTime());
    else if (obj instanceof String) { byte[] bs=((String)obj).getBytes(); bb.put((byte)'S').putInt(bs.length).put(bs); }
    else if (obj instanceof Object[]) { Object[]a=(Object[])obj; int n=a.length; bb.put((byte)'A').putInt(n); for (int i=0;i<n;++i) wr(bb,a[i]); }
    else if (obj instanceof M3MapBase) {
      @SuppressWarnings("unchecked") M3MapBase<Object,Object> m=(M3MapBase<Object,Object>)obj;
      bb.put((byte)'M'); wr(bb,m.zero()); bb.putInt(m.size());
      m.foreach(m.new Fun2() { public void apply(Object k, Object v) { wr(bb,k); wr(bb,v); }});
    } else {
      if (obj instanceof scala.Product) { scala.Product p=(scala.Product)obj; int a=p.productArity(); if (a<=10) { bb.put((byte)a); for (int i=0;i<a;++i) wr(bb,p.productElement(i)); return; } }
      bb.put((byte)'O'); try { new ObjectOutputStream(new BBOutputStream(bb)).writeObject(obj); } catch(Exception e) {}
    }
  }

  private Object rd(ByteBuffer bb) {
    int tp = bb.get();
    if (tp=='N') return null;
    if (tp=='L') return bb.getLong();
    if (tp=='F') return bb.getDouble();
    if (tp=='D') return new Date(bb.getLong());
    if (tp=='S') { byte[] bs=new byte[bb.getInt()]; bb.get(bs); return new String(bs); }
    if (tp=='A') { int n=bb.getInt(); Object[] a=new Object[n]; for (int i=0;i<n;++i) a[i]=rd(bb); return a; }
    if (tp=='M') { Object z=rd(bb); M3MapBase<Object,Object> m=new M3MapBase<Object,Object>(z,false,null); int n=bb.getInt(); for (int i=0;i<n;++i) m.put(rd(bb),rd(bb)); return m; }
    if (tp=='O') { Object o=null; try { o=new ObjectInputStream(new BBInputStream(bb)).readObject(); } catch(Exception e) { System.err.println(e); } return o; }
    switch(tp) {
      //(1 to 10).foreach(i=> println("      case "+i+": return new scala.Tuple"+i+"<"+(0 until i).map(x=>"Object").mkString(",")+">("+(0 until i).map(x=>"rd(bb)").mkString(",")+");"))
      case 1: return new scala.Tuple1<Object>(rd(bb));
      case 2: return new scala.Tuple2<Object,Object>(rd(bb),rd(bb));
      case 3: return new scala.Tuple3<Object,Object,Object>(rd(bb),rd(bb),rd(bb));
      case 4: return new scala.Tuple4<Object,Object,Object,Object>(rd(bb),rd(bb),rd(bb),rd(bb));
      case 5: return new scala.Tuple5<Object,Object,Object,Object,Object>(rd(bb),rd(bb),rd(bb),rd(bb),rd(bb));
      case 6: return new scala.Tuple6<Object,Object,Object,Object,Object,Object>(rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb));
      case 7: return new scala.Tuple7<Object,Object,Object,Object,Object,Object,Object>(rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb));
      case 8: return new scala.Tuple8<Object,Object,Object,Object,Object,Object,Object,Object>(rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb));
      case 9: return new scala.Tuple9<Object,Object,Object,Object,Object,Object,Object,Object,Object>(rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb));
      case 10: return new scala.Tuple10<Object,Object,Object,Object,Object,Object,Object,Object,Object,Object>(rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb),rd(bb));
    }
    System.err.println("Bad type:"+tp);
    return null;
  }
  public byte[] toBinary(Object obj) {
    if (obj instanceof Get) { Get o=(Get)obj; Object k=o.key(); ByteBuffer bb=ByteBuffer.allocate(3+sz(k)).put((byte)'g').putShort((short)o.map()); wr(bb,k); return bb.array(); }
    if (obj instanceof Val) { Val o=(Val)obj; Object k=o.key(); Object v=o.value(); ByteBuffer bb=ByteBuffer.allocate(3+sz(k)+sz(v)).put((byte)'v').putShort((short)o.map()); wr(bb,k); wr(bb,v); return bb.array(); }
    if (obj instanceof Add) { Add o=(Add)obj; Object k=o.key(); Object v=o.value(); ByteBuffer bb=ByteBuffer.allocate(3+sz(k)+sz(v)).put((byte)'a').putShort((short)o.map()); wr(bb,k); wr(bb,v); return bb.array(); }
    if (obj instanceof Set) { Set o=(Set)obj; Object k=o.key(); Object v=o.value(); ByteBuffer bb=ByteBuffer.allocate(3+sz(k)+sz(v)).put((byte)'s').putShort((short)o.map()); wr(bb,k); wr(bb,v); return bb.array(); }
    if (obj instanceof Clear) { Clear o=(Clear)obj; Object p=o.partKey(); ByteBuffer bb=ByteBuffer.allocate(4+sz(p)).put((byte)'c').putShort((short)o.map()).put((byte)o.part()); wr(bb,p); return bb.array(); }
    if (obj instanceof Foreach) { Foreach o=(Foreach)obj; Object[] as=o.args(); ByteBuffer bb=ByteBuffer.allocate(3+sz(as)).put((byte)'f').putShort((short)o.f()); wr(bb,as); return bb.array(); }
    if (obj instanceof Agg) { Agg o=(Agg)obj; Object[] as=o.args(); ByteBuffer bb=ByteBuffer.allocate(7+sz(as)).put((byte)'x').putInt(o.id()).putShort((short)o.f()); wr(bb,as); return bb.array(); }
    if (obj instanceof AggPart) { AggPart o=(AggPart)obj; Object r=o.res(); ByteBuffer bb=ByteBuffer.allocate(5+sz(r)).put((byte)'p').putInt(o.id()); wr(bb,r); return bb.array(); }
    if (obj instanceof Ack) { Ack o=(Ack)obj; int[] ts=o.to(); int[] ns=o.num(); int n=ts.length; ByteBuffer bb=ByteBuffer.allocate(5+6*n).put((byte)'k').putInt(n); for (int i=0;i<n;++i) bb.putShort((short)ts[i]).putInt(ns[i]); return bb.array(); }
    System.err.println("Unsupported serialization: "+obj); return null;
  }
  public Object fromBinaryJava(byte[] bytes, Class<?> clazz) {
    ByteBuffer bb=ByteBuffer.wrap(bytes); byte h=bb.get();
    switch(h) {
      case 'g': return new Get<Object>(bb.getShort(),rd(bb));
      case 'v': return new Val<Object,Object>(bb.getShort(),rd(bb),rd(bb));
      case 'a': return new Add<Object,Object>(bb.getShort(),rd(bb),rd(bb));
      case 's': return new Set<Object,Object>(bb.getShort(),rd(bb),rd(bb));
      case 'c': return new Clear<Object>(bb.getShort(),bb.get(),rd(bb));
      case 'f': return new Foreach(bb.getShort(),(Object[])rd(bb));
      case 'x': return new Agg(bb.getInt(),bb.getShort(),(Object[])rd(bb));
      case 'p': return new AggPart<Object>(bb.getInt(),rd(bb));
      case 'k': int l=bb.getInt(); int[] ts=new int[l]; int[] ns=new int[l]; for (int i=0;i<l;++i) { ts[i]=bb.getShort(); ns[i]=bb.getInt(); } return new Ack(ts,ns);
      default: System.err.println("Unsupported deserialization: "+h); return null;
    }
  }
  /** Message accumulator for batching and custom and serialization for internal messages. */
  /*
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
  */

  /**
   * Messages manager for the cluster. For a cluster with N workers, the
   * workers are indexed from 0 to N-1 and the master has index N.
   * Counters represent the number of unacknowledged messages.
   * Note: ack to master ignored, its counter is only present for uniformity
   */
  /*
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
  */
}
