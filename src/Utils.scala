package ddbt
import java.io._

/**
 * This class contains useful functions and variables that are shared across
 * different compiler parts.
 * @author TCK
 */
object Utils {
  // Paths related to DBToaster
  val path_base = "dbtoaster/compiler/alpha5"
  val (path_repo,path_bin) = {
    val prop = new java.util.Properties()
    try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable =>
      println("@@@\n@@@ Warning: conf/ddbt.properties does not exist.\n@@@ Please configure at least ddbt.dbtoaster to dbtoaster_release binary path.")
      println("@@@ Set ddbt.base_repo if you have access to DBToaster's repository.\n@@@")
    }
    val repo = prop.getProperty("ddbt.base_repo","")
    val bin  = prop.getProperty("ddbt.dbtoaster","bin/dbtoaster_release")
    (repo,if (repo!="") repo+"/"+path_base+"/bin/dbtoaster_release" else bin)
  }

  // Gobbles an input stream, used for external processes and loadMain
  private def gobble(in:InputStream) = new Runnable {
    var out = new StringBuilder
    var thr = new Thread(this); thr.start
    override def toString = { thr.join; out.toString.trim }
    override def run {
      val r = new BufferedReader(new InputStreamReader(in))
      var l = r.readLine; while(l != null) { out.append(l+"\n"); l = r.readLine }; r.close
    }
  }

  // Execute arbitrary command, return (out,err)
  def exec(cmd:String):(String,String) = exec(cmd.split(" "))
  def exec(cmd:Array[String],dir:File=null,env:Array[String]=null,fatal:Boolean=true):(String,String) = {
    val p = Runtime.getRuntime.exec(cmd,env,dir)
    val out=gobble(p.getInputStream); val err=gobble(p.getErrorStream); p.waitFor
    val o=out.toString; val e=err.toString
    if (e.trim!="") { println("Execution error in: "+cmd.mkString(" ")); print(o); System.err.print(e); if (fatal) System.exit(1) }
    (o,e)
  }
  
  // Capture console/default output and error streams in two strings
  def captureOut[R](f:()=>R) : (R,String,String) = {
    val o0=scala.Console.out; val so0=System.out; val po=new PipedOutputStream; scala.Console.setOut(new PrintStream(po)); System.setOut(new PrintStream(po)); val out=gobble(new PipedInputStream(po));
    val e0=scala.Console.err; val se0=System.err; val pe=new PipedOutputStream; scala.Console.setErr(new PrintStream(pe)); System.setErr(new PrintStream(pe)); val err=gobble(new PipedInputStream(pe));
    val r = f()
    scala.Console.setOut(o0); System.setOut(so0); po.close
    scala.Console.setErr(e0); System.setErr(se0); pe.close
    (r,out.toString,err.toString)
  }
  
  // Class loader to run a class with main(args:Array[String]) within the same VM
  def loadMain(cp:File,cls:String,args:Array[String]=Array()) = {
    val r = captureOut(()=>{
      try { val l=new CPLoader(cp); val c=l.loadClass(cls); val m = c.getMethod("main",args.getClass); m.invoke(null,args) }
      catch { case t:Throwable => t.printStackTrace(scala.Console.err) }
    })
    System.gc(); Thread.sleep(50); System.gc() // call finalize on class loader
    (r._2,r._3)
  }

  import java.net.{URL,URLClassLoader}
  private class CPLoader(cp:File) extends URLClassLoader(Array(cp.toURI.toURL),null) {
    override def loadClass(name:String, resolve:Boolean) : Class[_] = {
      try { return super.loadClass(name, resolve); }
      catch { case e:ClassNotFoundException => Class.forName(name, resolve, Utils.getClass.getClassLoader); }
    }
  }

  // Files I/O
  def read(file:String) = scala.io.Source.fromFile(file).mkString
  def write(dir:File,name:String,data:String) {
    if (!dir.exists) dir.mkdirs; val f=new File(dir,name)
    val o = new PrintWriter(f); o.write(data); o.close();
  }

  // String manipulation
  def ind(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll("\n? *$","").replaceAll("\n","\n"+i) }
  def tup(vs:List[String]) = { val v=vs.mkString(","); if (vs.size>1) "("+v+")" else v }

  // Fresh variables name provider
  private val counter = scala.collection.mutable.HashMap[String,Int]()
  def fresh(name:String="x") = { val c = counter.getOrElse(name,0)+1; counter.put(name,c); name+c }
  def freshClear() = counter.clear

  // Create a temporary directory that will be removed at shutdown
  def makeTempDir(path:String=null):File = {
    val tmp = if (path!=null) new File(path) else new File("target/tmp") //File.createTempFile("ddbt",null) deletes folder too early on OracleJVM7/MacOS
    def del(f:File) {
      if (f.isDirectory()) f.listFiles().foreach{c=>del(c)}
      if (!f.delete()) sys.error("Failed to delete file: " + f)
    }
    if (tmp.exists) del(tmp); tmp.mkdirs // have a fresh folder
    Runtime.getRuntime.addShutdownHook(new Thread{ override def run() = del(tmp) });
    tmp
  }

  // Time measurement
  def time(ns:Long,n:Int=2) = { val ms=ns/1000000; ("%"+(if (n==0)"" else n)+"d.%03d").format(ms/1000,ms%1000) }
  def ns[T](f:()=>T) = { val t0=System.nanoTime(); var r=f(); val t1=System.nanoTime(); (t1-t0,r) }
}
