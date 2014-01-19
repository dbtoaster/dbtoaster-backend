package ddbt.test
import org.scalatest._
import ddbt.lib._
import Messages._

class SerializerSpec extends FunSpec {
  val s = { val sys=Helper.actorSys("Test"); val r=akka.serialization.SerializationExtension(sys).findSerializerFor(new Get(0,null)); sys.shutdown; r }

  def test(msg:Msg) = it("serialize "+msg) {
    val bs = s.toBinary(msg);
    val m2 = s.fromBinary(bs);
    if (msg!=m2) System.err.println("Failed: "+msg+" != "+m2)
  }

  test(Get(123,10))
  test(Val(123,(1.001,456789L,-10),"FooX"))
  val t = M3Map.temp[Long,Double]()
  t.add(1L,2.0); t.add(4L,8.0);
  test(AggPart(456,t))

/*
  case class Get[K](map:MapRef,key:K) extends Msg // => Val[K,V]
  case class Val[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Add[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Set[K,V](map:MapRef,key:K,value:V) extends Msg
  case class Clear[P](map:MapRef,part:Int,partKey:P) extends Msg
  case class Foreach(f:FunRef,args:Array[Any]) extends Msg
  case class Agg(id:Int,f:FunRef,args:Array[Any]) extends Msg // => AggPart(id,_)
  case class AggPart[R](id:Int,res:R) extends Msg
  case class Ack(to:Array[NodeRef],num:Array[Int]) extends Msg // workers->master
*/
}
