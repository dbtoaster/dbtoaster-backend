package serial

object SerialTest {

  val node = Loader.load[NodeIO]("serial.NodeIOImpl",args=Seq((msg:Any,from:Int)=>println("Received "+msg+" from "+from),8008))
  node.encInit(new TupleX())

  def ns[T](f:()=>T) = { val t0=System.nanoTime; var r=f(); val t1=System.nanoTime; (t1-t0,r) }
  def time(ns:Long) = { val us=ns/1000; ("%3d.%06d").format(us/1000000,us%1000000) }

  def bench() {
    val N = 10000
    val loops = 10
    var t = new TupleX();
    (0 until loops).foreach { x=>
      println("Java  : "+time(ns(()=>{ var i=0; do { t=TupleX.deser(t.ser); i+=1; } while (i<N); })._1))
      println("Stream: "+time(ns(()=>{ var i=0; do { t=TupleX.unpack(t.pack); i+=1; } while (i<N); })._1))
      println("Buffer: "+time(ns(()=>{ var i=0; do { t=TupleX.fromBytes(t.toBytes); i+=1; } while (i<N); })._1))
      println("Native: "+time(ns(()=>{ var i=0; do { t=node.encDec(t); i+=1; } while (i<N); })._1))
    }
    println("Java  : "+t.ser.size);
    println("Stream: "+t.pack.size);
    println("Buffer: "+t.toBytes.size);
  }

  def main(args: Array[String]) {
    //println("Hello, world!")
    bench

    /*
    val tt=ns(()=>{
      val t0=System.nanoTime;
      var t=new TupleX(); var i=0; do { t=node.encDec(t); i+=1; } while (i<10000);
      val t1=System.nanoTime;
      println(time(t1-t0))
    })
    */


    /*
    node.setPeers(Array(NodeIOPeer("127.0.0.1",8008,2),NodeIOPeer("127.0.0.1",8009,4)))
    node.setTypes(Array(classOf[TupleX]))
    node.send(new TupleX(),0);
    node.poll
    */
    //println("Done")
  }
}

// Low-level network interface, encoding and decoding is provided
// by the (generated) C implementation.
case class NodeIOPeer(host:String,port:Int,num_cores:Int)
abstract class NodeIO(var recv:(Any,Int)=>Unit,port:Int) {
  def setPeers(peers:Array[NodeIOPeer]):Unit; // cluster membership (@init)
  def setTypes(cls:Array[Class[_]]):Unit; // setup serializer (@init) XXX: dynamic or hardcoded?
  def send(msg:Any,to:Int):Unit; // prepare a message to be sent
  def poll():Unit; // bulk send, poll messages (invokes recv)

  // Testing:
  def encInit(t:TupleX):Unit;
  def encDec(t:TupleX):TupleX;
}

class NodeIOImpl(recv:(Any,Int)=>Unit,port:Int) extends NodeIO(recv,port) {
  private var ptr:Long = 0L // C structures
  override def finalize() { free() } // invoked by System.gc()
  @native def free():Unit; // cleanup
  @native def setPeers(nodes:Array[NodeIOPeer]):Unit;
  @native def setTypes(cls:Array[Class[_]]):Unit;
  @native def send(msg:Any,to:Int):Unit;
  @native def poll():Unit;

  // Testing:
  @native def encInit(t:TupleX):Unit;
  @native def encDec(t:TupleX):TupleX;
}

// Dynamic class+JNI loader
object Loader {
  import java.net.{URL,URLClassLoader}
  import java.io.File
  def load[T](cls:String,args:Seq[Any]=Seq(),path:String=null):T = {
    System.gc() // detach previous classes/JNI libs
    val l0 = this.getClass.getClassLoader
    val p=(if (path!=null) Array(path) else (l0 match {
      case ctx: URLClassLoader => ctx.getURLs.map(_.getPath)
      case _ => System.getProperty("java.class.path").split(":")
    })).filter(p=>new File(p+ "/" +cls.replace("", "/")+".class").exists)
    if (p.size==0) { System.err.println("Class not found "+cls); return null.asInstanceOf[T] }
    val l1=new URLClassLoader(Array(new File(p(0)).toURI.toURL),l0)
    try {
      val cl = l1.loadClass(cls);
      val cs = cl.getConstructors().filter { c=> val ps=c.getParameterTypes;
        if (ps.size!=args.size) false else (true /: (ps zip args)) { case (r,(t,a)) => r && (t.isInstance(a) || a.getClass.getName.toLowerCase.startsWith("java.lang."+t.toString)) }
      }
      if (cs.size!=1) { System.err.println("No matching constructors: "+cs.toList); return null.asInstanceOf[T] }
      // JNI loading
      val f=new File(p(0)+ "/" +cls.replace("", "/")+".jnilib")
      if (f.exists) try { System.load(f.getCanonicalPath) } catch { case t:Throwable=> }
      cs(0).newInstance(args.asInstanceOf[Seq[Object]]:_*).asInstanceOf[T]
      //null.asInstanceOf[T]
    }
    catch { case t:Throwable => val c=t.getCause; (if (c!=null) c else t).printStackTrace; return null.asInstanceOf[T] }
    finally { System.gc; Thread.sleep(50); System.gc }
  }
}

// http://www.codethesis.com/blog/unload-java-jni-dll
// http://tutorials.jenkov.com/java-reflection/dynamic-class-loading-reloading.html
// http://tutorials.jenkov.com/java-reflection/constructors.html
// http://docs.oracle.com/javase/6/docs/technotes/guides/jni/spec/functions.html#NewGlobalRef
// http://www.accordess.com/wpblog/an-overview-of-java-compilation-api-jsr-199/
