
object BatchApp {
  type MapRef = Int // but assumed to be <32K
  type FunRef = Int // but assumed to be <32K
  
  // Data messages
  abstract sealed class Msg // data message (can be batched)
  case class Get[K](map:MapRef,key:K) extends Msg // => Val[K,V]
  case class Val[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Add[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Set[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Clear[P](map:MapRef,part:Int,partKey:P) extends Msg
  case class Foreach(f:FunRef,args:Array[Any]) extends Msg
  case class Aggr(id:Int,f:FunRef,args:Array[Any]) extends Msg // => AggrPart(id,_)
  case class AggrPart[R](id:Int,res:R) extends Msg

  import java.io._
  import java.util.Date

  private var is : ObjectInputStream = null
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
    case 'O' => is.readObject
    case _ => sys.error("Encoding error")
  }
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
      case 'x' => Aggr(is.readInt,is.readShort,rd.asInstanceOf[Array[Any]])
      case 'p' => AggrPart(is.readInt,rd)
      case _ => sys.error("Encoding error")
    }; i+=1; } while (i<n); is.close; is=null; res
  }
  
  // per worker
  class Batch() {
    private val data = new java.util.LinkedList[Msg]()
    private var os : ObjectOutputStream = null
    private def wr(obj:Any):Unit = obj match {
      case null => os.writeByte('N')
      case o:Long => os.writeByte('L'); os.writeLong(o)
      case o:Double => os.writeByte('F'); os.writeDouble(o)
      case o:Date => os.writeByte('D'); os.writeLong(o.getTime)
      case o:String => os.writeByte('S'); os.writeUTF(o)
      case o:Array[_] => os.writeByte('A'); os.writeInt(o.size); o.foreach(wr)
      case Tuple1(a) => os.writeByte('1'); wr(a);
      case Tuple2(a,b) => os.writeByte('2'); wr(a); wr(b);
      case Tuple3(a,b,c) => os.writeByte('3'); wr(a); wr(b); wr(c);
      case Tuple4(a,b,c,d) => os.writeByte('4'); wr(a); wr(b); wr(c); wr(d);
      case Tuple5(a,b,c,d,e) => os.writeByte('5'); wr(a); wr(b); wr(c); wr(d); wr(e);
      case Tuple6(a,b,c,d,e,f) => os.writeByte('6'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f);
      case Tuple7(a,b,c,d,e,f,g) => os.writeByte('7'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f); wr(g);
      case Tuple8(a,b,c,d,e,f,g,h) => os.writeByte('8'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f); wr(g); wr(h);
      case Tuple9(a,b,c,d,e,f,g,h,i) => os.writeByte('9'); wr(a); wr(b); wr(c); wr(d); wr(e); wr(f); wr(g); wr(h); wr(i);
      case o => os.writeByte('O'); os.writeObject(o)
    }
    def add(msg:Msg) = data.add(msg)
    def size = data.size
    def clear = data.clear
    def pack():Array[Byte] = {
      val s=new ByteArrayOutputStream; os=new ObjectOutputStream(s); var n=data.size
      os.writeInt(n)
      if (n>0) do { data.remove match { 
        case Get(m,k) => os.writeByte('g'); os.writeShort(m); wr(k)
        case Val(m,k,v) => os.writeByte('v'); os.writeShort(m); wr(k); wr(v)
        case Add(m,k,v) => os.writeByte('a'); os.writeShort(m); wr(k); wr(v)
        case Set(m,k,v) => os.writeByte('s'); os.writeShort(m); wr(k); wr(v)
        case Clear(m,p,k) => os.writeByte('c'); os.writeShort(m); os.writeInt(p); wr(k)
        case Foreach(f,as) => os.writeByte('f'); os.writeShort(f); wr(as)
        case Aggr(id,f,as) => os.writeByte('x'); os.writeInt(id); os.writeShort(f); wr(as)
        case AggrPart(id,r) => os.writeByte('p'); os.writeInt(id); wr(r)
      }; n-=1 } while (n>0)
      os.close; os=null; s.toByteArray
    }
  }


  def main(args:Array[String]) {
    val b=new Batch()
    b.add(Get(1,33L))
    b.add(Get(2,66L))
    b.add(Set(2,(2.0,3L,"foo"),new Date(3000)))
    println(unpack(b.pack).mkString("\n"))
    
  }
}
