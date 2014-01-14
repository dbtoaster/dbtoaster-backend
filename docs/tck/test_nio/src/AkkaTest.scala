import akka.actor._

import akka.actor.{ ActorRef, ActorSystem }
import akka.serialization._
import com.typesafe.config.ConfigFactory

import java.nio.ByteBuffer

class MessageSerializer extends Serializer {
  def includeManifest: Boolean = false
  def identifier = 0xfeed
  Message.register(new TupleX())
  def toBinary(obj: AnyRef): Array[Byte] = {
    val m = obj.asInstanceOf[Message]
    val bs=new Array[Byte](2+m.m_size)
    val bb = ByteBuffer.wrap(bs)
    bb.putShort(m.m_id())
    m.m_write(bb)
    return bs;
  }
  def fromBinary(bytes: Array[Byte], clazz: Option[Class[_]]): AnyRef = {
    Message.create(ByteBuffer.wrap(bytes))
  }
}

import akka.actor.ActorRef
import akka.actor.ActorSystem
import akka.dispatch.Envelope
import akka.dispatch.MailboxType
import akka.dispatch.MessageQueue
import akka.dispatch.ProducesMessageQueue
import com.typesafe.config.Config
import java.util.concurrent.ConcurrentLinkedQueue
//import scala.Option

// Marker trait used for mailbox requirements mapping
trait MyUnboundedMessageQueueSemantics
object MyUnboundedMailbox {

  class MyMessageQueue extends MessageQueue with akka.dispatch.UnboundedMessageQueueSemantics {
    private val a = new java.util.concurrent.atomic.AtomicReference(List[Envelope]())
    private var r = List[Envelope]()
    @inline private def pop = { var l=List[Envelope](); do { l=a.get } while(!a.compareAndSet(l,Nil)); r=l.reverse }
    def enqueue(receiver: ActorRef, handle: Envelope): Unit = { var l=List[Envelope](); do { l=a.get } while(!a.compareAndSet(l,handle::l)) }
    def dequeue:Envelope = if (r!=Nil) { val e=r.head; r=r.tail; e } else { pop; if (r!=Nil) { val e=r.head; r=r.tail; e } else null.asInstanceOf[Envelope]
    }
    def numberOfMessages: Int = r.size + a.get.size
    def hasMessages: Boolean = (r.size>0) || { pop; r.size>0 }
    def cleanUp(owner: ActorRef, deadLetters: MessageQueue) {
      while (hasMessages) deadLetters.enqueue(owner, dequeue())
    }
  }
  /*
  class MyMessageQueue extends MessageQueue with akka.dispatch.UnboundedMessageQueueSemantics {
    private final val queue = new ConcurrentLinkedQueue[Envelope]()
    def enqueue(receiver: ActorRef, handle: Envelope): Unit = queue.offer(handle)
    def dequeue(): Envelope = queue.poll()
    def numberOfMessages: Int = queue.size
    def hasMessages: Boolean = !queue.isEmpty
    def cleanUp(owner: ActorRef, deadLetters: MessageQueue) {
      while (hasMessages) deadLetters.enqueue(owner, dequeue())
    }
  }
  */
}

// This is the Mailbox implementation
class MyUnboundedMailbox extends MailboxType with ProducesMessageQueue[MyUnboundedMailbox.MyMessageQueue] {
  import MyUnboundedMailbox._
  def this(settings: ActorSystem.Settings, config: Config) = this()
  final override def create(owner: Option[ActorRef], system: Option[ActorSystem]): MessageQueue = new MyMessageQueue()
}


object AkkaTest {
  def actorSys(name:String,host:String=null,port:Int=0) = ActorSystem(name, com.typesafe.config.ConfigFactory.parseString(
    "akka.loglevel=ERROR\nakka.log-dead-letters-during-shutdown=off\n"+
"akka.actor {\n"+
"  serialize-messages = on\n"+
//"  serializers { msg = \"MessageSerializer\" }\n"+
//"  serialization-bindings { \"Message\" = msg }\n"+
"}\n"+
/*
"akka.actor.default-mailbox {\n"+
"  mailbox-type = \"MyUnboundedMailbox\"\n"+
"}\n"+
*/
    (if (host!=null) "akka {\nactor.provider=\"akka.remote.RemoteActorRefProvider\"\nremote {\n"+
    "enabled-transports=[\"akka.remote.netty.tcp\"]\nnetty.tcp {\nhostname=\""+host+"\"\nport="+port+"\n}\n"+"}\n}\n" else "")
  ))

  private val ctr = new java.util.concurrent.atomic.AtomicLong();
  def inc() { ctr.addAndGet(1); }

  def ns[T](f:()=>T) = { val t0=System.nanoTime; var r=f(); val t1=System.nanoTime; (t1-t0,r) }
  def time(ns:Long) = { val us=ns/1000; ("%d.%06d").format(us/1000000,us%1000000) }

  def test(num_hosts:Int,num_cores:Int,num_msg:Int=1,sleep:Int=5000) {
    (0 until 4).foreach { x=> System.gc; Thread.sleep(100) } // cleanup previously used sockets

    println("Testing "+num_hosts+" hosts X "+num_cores+" cores ("+num_msg+" messages):"); ctr.set(0)

    val hosts = (0 until num_hosts).map(i=>actorSys("Host"+i,"127.0.0.1",8800+i)).toArray
    val cores = hosts.flatMap { h => (0 until num_cores).map(x=>h.actorOf(Props[Worker]())) }
    (0 until cores.size-1).foreach { i=> cores(i) ! cores(i+1) }; cores(cores.size-1) ! cores(0)
    var i=0; while(i<num_msg) { cores(0) ! new TupleX(); i+=1; };
    Thread.sleep(500);
    val (t,n) = ns{()=> ctr.set(0); Thread.sleep(sleep); ctr.get() }
    hosts.foreach(_.shutdown)

    println("-> exchanged "+n+" messages in "+time(t)+"s, throughput = "+(n*1000000/(t/1000))+"msg/sec")
  }

  def main(args:Array[String]) {
    test(2,2,1,2000)
    test(2,2,1,2000)

/*
Custom:
4 hosts X 1 cores:throughput = 133'227msg/sec
1 hosts X 4 cores:throughput = 546'062msg/sec
Default:
4 hosts X 1 cores:throughput = 24'387msg/sec
1 hosts X 4 cores:throughput = 33'138msg/sec
*/

    test(4,1,1,2000)
    test(1,4,1,2000)
    test(4,1,1,2000)
    test(1,4,1,2000)
    return

    test(1,1,1)
    println("----------------------------")
    test(1,1,1)
    test(4,1,1)
    test(1,4,1)
    test(4,4,1)
    test(1,1,4)
    test(4,1,4)
    test(1,4,4)
    test(4,4,4)
/*
Testing 1 hosts X 1 cores (1 messages) -> 16289790 messages in 5.001109s, throughput = 3'257'235msg/sec
Testing 4 hosts X 1 cores (1 messages) ->   577038 messages in 5.000211s, throughput =   115'402msg/sec
Testing 1 hosts X 4 cores (1 messages) ->  9595966 messages in 5.001200s, throughput = 1'918'732msg/sec
Testing 4 hosts X 4 cores (1 messages) ->  1348243 messages in 5.000175s, throughput =   269'639msg/sec
Testing 1 hosts X 1 cores (4 messages) -> 20627137 messages in 5.000200s, throughput = 4'125'262msg/sec
Testing 4 hosts X 1 cores (4 messages) ->  2507844 messages in 5.000317s, throughput =   501'537msg/sec
Testing 1 hosts X 4 cores (4 messages) -> 28675260 messages in 5.000654s, throughput = 5'734'301msg/sec
Testing 4 hosts X 4 cores (4 messages) ->  5175961 messages in 5.000150s, throughput = 1'035'161msg/sec

Custom serialization:
Testing 1 hosts X 1 cores (1 messages) -> 16617594 messages in 5.000192s, throughput = 3'323'391msg/sec
Testing 4 hosts X 1 cores (1 messages) ->   763681 messages in 5.000188s, throughput =   152'730msg/sec <--
Testing 1 hosts X 4 cores (1 messages) ->  9282788 messages in 5.001179s, throughput = 1'856'119msg/sec
Testing 4 hosts X 4 cores (1 messages) ->  1348917 messages in 5.000138s, throughput =   269'775msg/sec <--
Testing 1 hosts X 1 cores (4 messages) -> 19698950 messages in 5.000922s, throughput = 3'939'063msg/sec
Testing 4 hosts X 1 cores (4 messages) ->  3020028 messages in 5.000146s, throughput =   603'987msg/sec <--
Testing 1 hosts X 4 cores (4 messages) -> 27250716 messages in 5.000739s, throughput = 5'449'337msg/sec
Testing 4 hosts X 4 cores (4 messages) ->  5208597 messages in 5.000198s, throughput = 1'041'678msg/sec <--
*/
  }
}

class Worker extends Actor {
  var next:ActorRef = null
  def receive = {
    case a:ActorRef => next=a
    case t:TupleX => AkkaTest.inc(); next!t
  }
}
