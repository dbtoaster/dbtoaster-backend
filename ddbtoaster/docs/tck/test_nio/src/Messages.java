import java.nio.ByteBuffer;
import java.util.HashMap;

/**
 * A serialization and deserialization using NIO buffers. Benchmarks:
 * - Serialization with ByteBuffer is the fastest: Java 155'170, streams 10'042, NIO 2'818, JNI/C 17'604
 * - Reflection (newInstance) is extremely slow: 217'384us vs 55us (1M calls)
 * - Having a creator function reconciles immutability and serialization
 */
abstract class Message implements java.io.Serializable {

  abstract public short m_id(); // unique identifier for the class (for deserialization)
  abstract public int m_size(); // data size
  abstract public void m_write(ByteBuffer buffer); // serialize in buffer
  abstract protected Message m_read(ByteBuffer buffer); // deserialize from buffer (create a new object)

  private static final HashMap<Short,Message> map = new HashMap<Short,Message>();
  public static final void register(Message dummy) throws Exception {
    short id=dummy.m_id(); Message p=map.get(id); map.put(id,dummy); if (p==null) return;
    Class<?> c1=p.getClass(),c2=dummy.getClass(); if (!c1.equals(c2)) throw new Exception("Message["+id+"] registered by both "+c1.getCanonicalName()+" and "+c2.getCanonicalName());
  }
  public static final void deregister(Message dummy) { map.remove(dummy.m_id()); }
  public static final void deregister(short id) { map.remove(id); }
  public static final Message create(ByteBuffer buffer) throws Exception { // deserialize a new object
    short id=buffer.getShort(); Message m=map.get(id); if (m!=null) return m.m_read(buffer); else throw new Exception("Message["+id+"] not found");
  }
}

// ---------------------
// Generated code below

class TupleX extends Message {
  // 30 bytes
  public boolean b; // 1
  public byte i1;   // 1
  public char i2;   // 2
  public short i3;  // 2
  public int i4;    // 4
  public long i5;   // 8
  public float f1;  // 4
  public double f2; // 8
  // 10 + length bytes
  public String s;         // 2 + length*2
  public java.util.Date d; // 8
  public TupleX() { s="sample"; d=new java.util.Date(); }

  public short m_id() { return 1; }
  public int m_size() { return 40 + (s==null?0:s.getBytes().length); }
  public void m_write(ByteBuffer buf) {
    //int p=buf.position();
    buf.put((byte)(b?1:0)).put(i1).putChar(i2).putShort(i3).putInt(i4).putLong(i5).putFloat(f1).putDouble(f2);
    byte[] sb=s.getBytes(); buf.putShort((short)sb.length).put(sb).putLong(d.getTime());
    //System.out.println("Serialized "+(buf.position()-p)+" bytes");
  }
  protected Message m_read(ByteBuffer buf) {
    TupleX t = new TupleX();
    //int p=buf.position();
    t.b=buf.get()==0; t.i1=buf.get(); t.i2=buf.getChar(); t.i3=buf.getShort(); t.i4=buf.getInt(); t.i5=buf.getLong(); t.f1=buf.getFloat(); t.f2=buf.getDouble();
    byte[] b=new byte[(int)buf.getShort()]; buf.get(b); t.s=new String(b); t.d=new java.util.Date(buf.getLong());
    //System.out.println("Deserialized "+(buf.position()-p)+" bytes");
    return t;
  }
}

/*
abstract class MessageQueue implements Runnable {
  abstract public void deq(Message msg, int from, int to);
  static class Elem { Message msg; int from; int to; Elem next; }
  private Elem q_head = null; // dequeue here
  private Elem q_tail = null; // enqueue here
  public void enq(Message msg, int from, int to) {
    Elem e=new Elem(); e.msg=msg; e.from=from; e.to=to;
    synchronized(this) { if (q_tail!=null) q_tail.next=e; else { q_head=e; q_tail=e; this.notify(); } }
  }
  // Process all pending messages and return
  void exec() {
    do {
      Elem e=null;
      synchronized(this) {
        if (q_head==null) return;
        e=q_head; q_head=e.next; if (q_head==null) q_tail=null;
      }
      deq(e.msg,e.from,e.to);
    } while(true);
  }
  // Detach a worker thread
  private boolean running = false; // terminate the thread
  public void start() { if (!running) { running=true; new Thread(this).start(); } }
  public void stop() { synchronized(this) { running=false; this.notify(); } }
  public void run() {
    Elem e=null;
    do {
      synchronized(this) {
        if (q_head==null) try { wait(); } catch (InterruptedException ex) {} // only one blocking event
        if (!running) return; e=q_head; q_head=e.next; if (q_head==null) q_tail=null;
      }
      deq(e.msg,e.from,e.to);
    } while(true);
  }
}
*/

