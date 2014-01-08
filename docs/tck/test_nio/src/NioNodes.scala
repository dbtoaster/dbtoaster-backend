object NioNodesTest {

  private val ctr = new java.util.concurrent.atomic.AtomicLong();
  def inc() { ctr.addAndGet(1); }

  def ns[T](f:()=>T) = { val t0=System.nanoTime; var r=f(); val t1=System.nanoTime; (t1-t0,r) }
  def time(ns:Long) = { val us=ns/1000; ("%d.%06d").format(us/1000000,us%1000000) }

  def test(num_hosts:Int,num_cores:Int,num_msg:Int=1,sleep:Int=5000) {
    (0 until 4).foreach { x=> System.gc; Thread.sleep(100) } // cleanup previously used sockets

    println("Testing "+num_hosts+" hosts X "+num_cores+" cores ("+num_msg+" messages):"); ctr.set(0)
    val peers = (0 until num_hosts).map(x=>new NPeer("127.0.0.1",8800+x,num_cores)).toArray
    val hosts = peers.map(new NHost(_))
    hosts.foreach{ h => h.peers=peers }
    hosts.foreach(_.start)
    // Now we inject hot potato (rotating among cores)
    //inject(peers(0),0,0,new TupleX())
    var i=0; while(i<num_msg) { i+=1; hosts(0).enq(new TupleX(),0,0); };
    Thread.sleep(500);
    val (t,n) = ns{()=> ctr.set(0); Thread.sleep(sleep); ctr.get()}
    hosts.foreach(_.interrupt)
    println("-> exchanged "+n+" messages in "+time(t)+"s, throughput = "+(n*1000000/(t/1000))+"msg/sec")
  }

  def main(args: Array[String]) {
    System.gc; Thread.sleep(100) // cleanup previously used sockets
    Message.register(new TupleX()) // register messages

    test(1,1,1)
    test(4,1,1)
    test(1,4,1)
    test(4,4,1)
    test(1,1,4)
    test(4,1,4)
    test(1,4,4)
    test(4,4,4)
/*
1 hosts X 1 cores (1 messages) ->  803933 messages in 5.001000s, throughput = 160'754msg/sec
4 hosts X 1 cores (1 messages) ->  131481 messages in 5.000136s, throughput =  26'295msg/sec
1 hosts X 4 cores (1 messages) ->  927626 messages in 5.001126s, throughput = 185'483msg/sec
4 hosts X 4 cores (1 messages) ->  358908 messages in 5.001123s, throughput =  71'765msg/sec
1 hosts X 1 cores (4 messages) -> 3945193 messages in 5.001136s, throughput = 788'859msg/sec
4 hosts X 1 cores (4 messages) ->  285946 messages in 5.001129s, throughput =  57'176msg/sec
1 hosts X 4 cores (4 messages) -> 4645068 messages in 5.000141s, throughput = 928'987msg/sec
4 hosts X 4 cores (4 messages) -> 1069960 messages in 5.001126s, throughput = 213'943msg/sec
*/
  }
  /*
  def inject(peer:NPeer,from:Int,to:Int,msg:Message) {
    import java.nio.ByteBuffer
    import java.nio.channels._
    val s=SocketChannel.open; s.configureBlocking(true); s.connect(peer.addr)
    if (s.isConnectionPending) s.finishConnect
    val l = msg.m_size; println("Seeding "+msg+" ("+l+" bytes)")
    val b = ByteBuffer.allocate(10+l).putShort(from.toShort).putShort(to.toShort).putInt(l).putShort(msg.m_id)
    msg.m_write(b); b.flip(); s.write(b);
    s.shutdownOutput()
  }
  */
}

// -----------------------------------------------------------------------------

import java.nio.ByteBuffer
import java.nio.channels._
import java.net.InetSocketAddress
import java.util.LinkedList
import java.io.IOException

/*
 * Message format: [from:2][to:2][length:4][type:2][payload...]
 * Message types : [from][to<0][length=0] = "hello" (advertise remote identity)
 *
 * XXX: how to achieve eventual delivery exactly once (this implies application level ack/nack)?
 * XXX: how to deal with failures and secondary nodes. Have a loop of ack through all copies?
 * XXX: maintain at host a list of messages sent but not ack'ed?
 *
 */


// Single consumer queue
class Queue[T] {
  private val a = new java.util.concurrent.atomic.AtomicReference(List[T]())
  private var r = List[T]()
  private val lock = new java.util.concurrent.locks.ReentrantLock()
  private val cond = lock.newCondition()
  def offer(el:T) = { var l=List[T](); do { l=a.get } while(!a.compareAndSet(l,el::l)); if (l==Nil) { lock.lock; cond.signal; lock.unlock } }
  def poll:T = if (r!=Nil) { val e=r.head; r=r.tail; e } else {
    var l=List[T](); do { l=a.get } while(!a.compareAndSet(l,Nil))
    r=l.reverse; if (r!=Nil) { val e=r.head; r=r.tail; e } else null.asInstanceOf[T]
  }
  def take:T = { var e=poll; if (e!=null) return e; lock.lockInterruptibly();
    try { try { cond.await(); e=poll } catch { case ie:InterruptedException => cond.signal; throw ie } } finally { lock.unlock }; e
  }
}
//import java.util.concurrent.{LinkedBlockingQueue=>Queue}

case class NPeer(host:String, port:Int, cores:Int=1) extends Message with Ordered[NPeer] {
  val addr = new InetSocketAddress(host,port)
  var base = 0 // base index of this peer's cores
  var chan:SocketChannel = null
  def copy = new NPeer(host,port,cores)
  override def toString = { val s=addr.toString; s.substring(s.indexOf('/')+1) }
  def compare(p:NPeer) = toString.compare(p.toString)
  def equals(p:NPeer) = compare(p)==0
  val m_id = 0x8000.toShort
  def m_size = 6+host.getBytes().length
  def m_write(b:ByteBuffer) { val bs=host.getBytes; b.putShort(port.toShort).putShort(cores.toShort).putShort(bs.length.toShort).put(bs); }
  def m_read(b:ByteBuffer) = { val p=b.getShort; val c=b.getShort; val bs=new Array[Byte](b.getShort); b.get(bs); val h=new String(bs); new NPeer(h,p,c) }
}
//Message.register(new NPeer("localhost",0))

class NCore(host:NHost,id:Int) extends Thread {
  private val q=new Queue[(Message,Int)]() // message, from
  private var running=false;
  override def interrupt() { running=false; super.interrupt }
  override def run() { running=true; do try { val e=q.take; recv(e._1,e._2) } catch { case e:InterruptedException => case e:Exception => e.printStackTrace } while(running) }
  def enq(msg:Message,from:Int) = q.offer((msg,from))
  // user interface
  def me = host.me.base+id
  def send(msg:Message,to:Int) = {
    val q=to-host.me.base
    if (q>=0 && q<host.core.size) host.core(q).enq(msg,me)
    else host.enq(msg,me,to)
  }
  def recv(msg:Message,from:Int) {
    val to = (me+1)%host.nodes
    //println("@["+me+"] got "+msg+" from "+from+", send to "+to)
    NioNodesTest.inc()
    send(msg,to)
  }
}

class NHost(val me:NPeer) extends Thread {
  // cores communication
  private val q=new Queue[(Message,Int,Int)]() // message, from, to
  var core = (0 until me.cores).map(i=>new NCore(this,i)).toArray
  def enq(msg:Message,from:Int,to:Int) = q.offer((msg,from,to))
  // membership management
  private var _nodes:Int = 0 // total nodes in the cluster
  private var _peers:Array[NPeer] = null
  def nodes = _nodes
  def peers = _peers
  def peers_=(ps:Array[NPeer]) { val n=ps.size; var i=0;
    while(i<n) { ps(i)=if (ps(i)==me) me else { val j=if (_peers==null) -1 else _peers.indexOf(ps(i)); if (j>=0) _peers(j) else ps(i).copy }; i+=1 }
    _peers=ps.sorted; var b=0; me.base = -me.cores; i=0; while(i<n) { var p=_peers(i); i+=1; p.base=b; b+=p.cores; }; _nodes=b
  }
  @inline private def peer(core:Int):NPeer = { // hinted linear search for the peer containing the core
    val n=_peers.size; var i=core*n/_nodes; if (i<0||i>=n) return null; var p=_peers(i)
    if (core<p.base) { do i-=1 while (core<_peers(i).base); _peers(i) }
    else { while (core>=p.base+p.cores) { i+=1; p=_peers(i) }; p }
  }
  // network connections
  private val selector = Selector.open
  private val serv = { val s=ServerSocketChannel.open; s.configureBlocking(false); s.socket.bind(me.addr); s.register(selector, SelectionKey.OP_ACCEPT); s }
  override def finalize { serv.close; selector.close }
  @inline private def concat(b1:ByteBuffer,b2:ByteBuffer) = ByteBuffer.allocate(b1.remaining+b2.remaining).put(b1).put(b2).flip().asInstanceOf[ByteBuffer]
  @inline private def chan(p:NPeer,s:SocketChannel) = if (p.chan==null) { p.chan=s; true } else { // pick deterministically one channel
    val as=Array(s.socket.getLocalSocketAddress,s.socket.getRemoteSocketAddress,p.chan.socket.getLocalSocketAddress,p.chan.socket.getRemoteSocketAddress).map{a=>val s=a.toString; val p=s.indexOf('/'); s.substring(p) }
    println("@"+me.base+" pre-close...")
    if ((as(0)<as(2) && as(0)<as(3)) || (as(1)<as(2) && as(0)<as(3))) { p.chan.shutdownOutput; p.chan=s; true } else { s.shutdownOutput; false }
  }

  // -------------
  @inline private def sendMsg(msg:Message,from:Int,to:Int,peer:NPeer) { // peer reserved for future use
    // var buf_out : ByteBuffer = null aggregated output messages (bulking)
    // XXX: to buffer output for bulk message sending, not enabled for now
    val bb = ByteBuffer.allocate(10+msg.m_size) // [from:2][to:2][len:4][type:2][payload]
    bb.putShort(from.toShort).putShort(to.toShort).putInt(msg.m_size).putShort(msg.m_id)
    msg.m_write(bb); bb.flip();
    val wr = peer.chan.write(bb)
    // XXX: keep message somewhere in case of TCP/connection failure?
  }
  // Create a new message given a type
  //var newMessage:Int=>Message = (tp:Int) => new TupleX() // to be modified

  @inline private def recvBuf(bb:ByteBuffer,cli:SocketChannel) {
    var cont = bb.remaining>=8 // loop breaker, minimum header length=8
    if (cont) do {
      bb.mark
      val from = bb.getShort.toInt
      val to = bb.getShort.toInt
      val len = bb.getInt
      if (bb.remaining<len) { bb.reset; cont=false }
      else if (to<0) { // system message to host
        if (len==0) { chan(peer(from),cli) } // hello
        // handle other internal messages
      } else { // deliver message to a core
        assert(bb.remaining>=2)
        assert (to-me.base<me.cores)
        core(to-me.base).enq(Message.create(bb),from)
      }
      cont &&= bb.remaining>=8
    } while(cont)
  }

  private var running=false
  override def interrupt() { running=false; super.interrupt }
  override def run() {
    running = true
    core.foreach(c=>if (!c.isAlive) c.start)
    val skip = new LinkedList[(Message,Int,Int)]()
    do try {
      // -------- poll the sending queue
      var e=q.poll
      if (e!=null) {
        do {
          val l = e._3-me.base
          if (l>=0 && l<me.cores) core(l).enq(e._1,e._2) // handle locally
          else { // need to send it remotely
            val p = peer(e._3); if (p==null) System.err.println("No valid peer for core "+e._3)
            else if (p.chan==null) {
              val s=SocketChannel.open; s.configureBlocking(false); s.connect(p.addr);
              s.register(selector, SelectionKey.OP_CONNECT); p.chan=s; skip.offer(e) // skip the message (and insert back later)
            }
            else if (!p.chan.isConnected) skip.offer(e)
            else sendMsg(e._1,e._2,e._3,p)
          }
          e=q.poll
        } while (e!=null)
        e=skip.poll; if (e!=null) do { q.offer(e); e=skip.poll } while (e!=null) // put back skipped elements
      }
      // -------- poll the sockets
      if (selector.selectNow>0) {
        val i=selector.selectedKeys.iterator;
        while (i.hasNext) { val key=i.next; i.remove();
          if (key.isAcceptable) { // server accept
            var cli:SocketChannel=serv.accept; cli.configureBlocking(false); cli.register(selector, SelectionKey.OP_READ)
          } else if (key.isConnectable) { // client connect
            val cli=key.channel.asInstanceOf[SocketChannel]; if (cli.isConnectionPending) cli.finishConnect
            val bb=ByteBuffer.allocate(8).putShort(me.base.toShort).putShort(-1).putInt(0); bb.flip; cli.write(bb) // hello
            key.interestOps(SelectionKey.OP_READ)
          } else if (key.isReadable) {
            val cli=key.channel.asInstanceOf[SocketChannel]
            var buf_in = key.attachment.asInstanceOf[ByteBuffer]
            var bb = ByteBuffer.allocate(BUF_SIZE)
            var rd=cli.read(bb);
            if (rd>0) {
              bb.flip; if (buf_in!=null) bb=concat(buf_in,bb)
              do {
                recvBuf(bb,cli);
                bb.clear; rd=cli.read(bb); bb.flip
              } while(rd>0)
              key.attach(if (bb.remaining>0) bb else null) // retain incomplete message
            }
            if (rd<0) { key.cancel; cli.close; peers.filter(_.chan==cli).foreach(_.chan=null) } // end of stream, close
          }
        }
      }
    } catch {
      case e:java.nio.channels.ClosedByInterruptException =>
      case e:InterruptedException =>
      case e:IOException => //e.printStackTrace
    } while(running)
    // Shutdown
    core.foreach(_.interrupt)
    //println("Terminated @"+me.base)
  }
  final val BUF_SIZE = 8192
}


/**
 * Message format: [from:2][to:2][length:4][type:2][payload...]
 * Message types : [from][to<0][length=0] = hello (advertise remote identity)
 *
 * - if (dst==0xffff) this is a system message addressed to the host
 * - length includes the 2B of the type
 * - incomplete messages are stored in the corresponding peer buffer before
 *   being decoded and delivered appropriately
 *
 */

// -----------------------------------------------------------------------------

/*
import java.io.IOException
import java.net.{InetAddress,InetSocketAddress}
import java.nio.ByteBuffer
import java.nio.channels._
import java.util.Iterator
import java.util.Set
import scala.collection.JavaConversions._

object Server { def main(args:Array[String]) { new Server().startListening(); } }
class Server {
  var serverSocketChannel : ServerSocketChannel = null;
  var selector : Selector = null;

  try {
    selector = Selector.open
    serverSocketChannel = ServerSocketChannel.open
    serverSocketChannel.configureBlocking(false)
    val add = new InetSocketAddress(InetAddress.getLocalHost(), 9999)
    serverSocketChannel.socket.bind(add)
    val key = serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT)
    System.out.println("serverSocketChannel's registered key is : " + key.channel().toString)
  } catch { case e:IOException => e.printStackTrace; }

  def startListening() {
    System.out.println("Server is listening on: "
      + serverSocketChannel.socket().getInetAddress().getHostAddress() + ":"
      + serverSocketChannel.socket().getLocalPort());
    while (true) {
      try {
        selector.select();
        selector.selectedKeys.foreach { key =>
          if (key.isAcceptable) {
            // only ServerSocketsChannels registered for OP_ACCEPT are excepted to receive an "acceptable" key
            System.out.println("Key ready to perform accept() : " + key.channel().toString());
            val client = serverSocketChannel.accept;
            if (client!=null) {
              client.configureBlocking(false);
              client.register(selector, SelectionKey.OP_READ);
            }
          } else if (key.isReadable) {
            System.out.println("Key ready to perform read() : " + key.channel().toString());
            val client = key.channel.asInstanceOf[SocketChannel];
            val bb = ByteBuffer.allocate(1024);
            client.read(bb); // read the msg sent by the client
            // display the message
            bb.flip();
            val array = new Array[Byte](bb.limit);
            bb.get(array);
            System.out.println(new String(array));
          }
          XXX remove
        }
      } catch { case e:IOException => e.printStackTrace; }
    }
  }
}

class Client(myIdentity:String) {
  def talkToServer() {
    try {
      val mySocket = SocketChannel.open;
      mySocket.configureBlocking(false);
      mySocket.connect(new InetSocketAddress(InetAddress.getLocalHost(), 9999));
      val selector = Selector.open;
      mySocket.register(selector, SelectionKey.OP_CONNECT);

      while (selector.select() > 0) {
        selector.selectedKeys.foreach { key =>
          val myChannel = key.channel().asInstanceOf[SocketChannel];
          if (key.isConnectable()) {
            if (myChannel.isConnectionPending()) {
              myChannel.finishConnect();
              System.out.println("Connection was pending but now is finished connecting.");
            }
            while (true) {
              val bb = ByteBuffer.wrap(new String("I am Client : " + myIdentity).getBytes);
              myChannel.write(bb); bb.clear(); this.synchronized { wait(3000); }
            }
          }
        }
      }
    } catch { case e:IOException => e.printStackTrace; }
  }
}
object Client { def main(args:Array[String]) { new Client(args(0)).talkToServer(); } }
*/
