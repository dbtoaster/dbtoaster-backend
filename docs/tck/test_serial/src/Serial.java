package serial;
import java.nio.ByteBuffer;

import java.io.*;

// Constructed at schema definition
// Let X be the relation name

interface HashTupleX { int nodeX(TupleX t); int hashX(TupleX t, int idx); }

/*public*/ class TupleX implements Serializable {
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
  //java.math.BigInteger bi;
  public TupleX() { s="sample"; d=new java.util.Date(); }

  // Custom NIO serialization
  public byte[] toBytes() {
    int len = 40 + (s==null?0:s.length()<<1);
    ByteBuffer bb = ByteBuffer.allocate(len);
    bb.put((byte)(b?1:0)).put(i1).putChar(i2).putShort(i3).putInt(i4).putLong(i5);
    bb.putFloat(f1).putDouble(f2).putShort((short)s.length()).put(s.getBytes()).putLong(d.getTime());
    return bb.array();
  }
  static public TupleX fromBytes(byte[] bytes) {
    ByteBuffer bb = ByteBuffer.wrap(bytes);
    TupleX t = new TupleX();
    t.b = bb.get()==0;
    t.i1 = bb.get();
    t.i2 = bb.getChar();
    t.i3 = bb.getShort();
    t.i4 = bb.getInt();
    t.i5 = bb.getLong();
    t.f1 = bb.getFloat();
    t.f2 = bb.getDouble();
    byte[] b = new byte[(int)bb.getShort()]; bb.get(b);
    t.s = new String(b);
    t.d = new java.util.Date(bb.getLong());
    return t;
  }

  // Java serialization
  public byte[] ser() throws Exception {
    ByteArrayOutputStream ss = new ByteArrayOutputStream();
    ObjectOutputStream os = new ObjectOutputStream(ss);
    os.writeObject(this); os.close(); return ss.toByteArray();
  }
  public static TupleX deser(byte[] bytes) throws Exception {
    ObjectInputStream is=new ObjectInputStream(new ByteArrayInputStream(bytes));
    TupleX t = (TupleX)is.readObject(); is.close(); return t;
  }

  // Generic serialization
  public byte[] pack() throws Exception {
    ByteArrayOutputStream ss = new ByteArrayOutputStream();
    ObjectOutputStream os = new ObjectOutputStream(ss);
    os.writeByte((byte)(b?1:0));
    os.writeByte(i1);
    os.writeChar(i2);
    os.writeShort(i3);
    os.writeInt(i4);
    os.writeLong(i5);
    os.writeFloat(f1);
    os.writeDouble(f2);
    os.writeUTF(s);
    os.writeLong(d.getTime());
    os.close(); return ss.toByteArray();
  }
  public static TupleX unpack(byte[] bytes) throws Exception {
    ObjectInputStream is=new ObjectInputStream(new ByteArrayInputStream(bytes));
    TupleX t = new TupleX();
    t.b = is.readByte()==0;
    t.i1 = is.readByte();
    t.i2 = is.readChar();
    t.i3 = is.readShort();
    t.i4 = is.readInt();
    t.i5 = is.readLong();
    t.f1 = is.readFloat();
    t.f2 = is.readDouble();
    t.s = is.readUTF();
    t.d = new java.util.Date(is.readLong());
    is.close();
    return t;
  }
}

// Constructed at each phase change
// Let N a unique sequence number
/*public*/ class PhaseN implements HashTupleX {
  public int nodeX(TupleX t) { return t.i1; } // partitioning of data on different nodes
  public int hashX(TupleX t, int idx) { return t.i4; } // indexing hash function
  // hash for other involved relation tuples
}
