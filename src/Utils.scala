package ddbt
import java.io._

/**
 * This class contains useful functions and variables that are shared across
 * different compiler parts.
 * @author TCK
 */
object Utils {
  // Display a warning to the user
  def warning(msg:String) = {
    val sb=new StringBuilder(("@"*80)+"\n@"+(" "*78)+"@\n")
    ("WARNING: "+msg).split("\n").foreach { l => sb.append("@  %-74s  @\n".format(l)) }
    sb.append("@"+(" "*78)+"@\n"+("@"*80)); System.err.println(sb.toString)
  }

  private val prop_ = new java.util.Properties
  try { prop_.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => warning("conf/ddbt.properties does not exist.\n"+
        "Please configure at least ddbt.dbtoaster to dbtoaster_release binary path.\nSet ddbt.base_repo if you have access to DBToaster's repository.") }
  def prop(name:String,d:String="") = prop_.getProperty("ddbt."+name,d)
  //val scalaVersion = util.Properties.versionString.replaceAll("^.* ([0-9]+\\.[0-9]+).*$","$1")

  // Paths related to DBToaster
  val path_base = "dbtoaster/compiler/alpha5"
  val path_repo = prop("base_repo",null)
  val path_bin  = if (path_repo!=null) path_repo+"/"+path_base+"/bin/dbtoaster_release" else prop("dbtoaster","bin/dbtoaster_release")
  private lazy val (path_cp,path_jvm) = {
    val deps = System.getProperty("sbt.classpath",System.getProperty("sun.java.command").replaceAll(".*-classpath | .*","")+":"+System.getProperty("sun.boot.class.path")).split(":")
    val cp = deps /**/ .filter(_.matches("(.*)/(\\.(sbt|ivy2)|target)/.*")).filter(_.indexOf("virtualized")== -1) /**/ .mkString(":")
    val boot_cp=cp.split(":").filter(_.matches(".*scala-(library|compiler|reflect).*")).mkString(":")
    (cp,"java "+prop("jvm")+" -Xbootclasspath/a:"+boot_cp)
  }

  // Scala compiler wrapper
  def scalaCompiler(dir:File,classpath:String=null,external:Boolean=false) : List[String]=>Unit = {
    val path_dir=dir.getAbsolutePath; val cp=(if(classpath!=null) classpath+":" else "")+path_cp
    val opts=prop("scalac").split(" +").toList
    if (!external) { // Embedded Scala compiler
      val s=new scala.tools.nsc.Settings(); s.processArguments(opts,true)
      s.classpath.value=cp; s.outputDirs.setSingleOutput(path_dir); val g=new scala.tools.nsc.Global(s)
      (fs:List[String]) => try { (new g.Run).compile(fs) } catch { case t:Throwable => t.printStackTrace }
    } else { // FSC external processes
      def execOut(cmd:String) {
        def gob(i:InputStream,o:PrintStream) = new Thread() { val r=new BufferedReader(new InputStreamReader(i)); override def run() { var l=r.readLine; while(l!=null) { o.println(l); l=r.readLine }; } }.start
        val p = Runtime.getRuntime.exec(cmd.split(" +"),null,null); gob(p.getInputStream,scala.Console.out); gob(p.getErrorStream,scala.Console.err); p.waitFor
      }
      val args="-cp "+cp+" -d "+path_dir+" "+opts.mkString(" ")+" "
      val fsc="fsc "+prop("jvm").split(" +").map("-J"+_).mkString(" ")+" "+args
      (fs:List[String]) => try { execOut(fsc+fs.mkString(" ")) } catch { case _:IOException => execOut(path_jvm+" scala.tools.nsc.Main "+args+fs.mkString(" ")) }
    }
  }

  // Execute Scala a program
  def scalaExec(cp:List[File],cls:String,args:Array[String]=Array(),external:Boolean=false) = {
    if (!external) loadMain(cp,cls,args)
    else exec(path_jvm+" -cp "+cp.map(p=>p.getAbsolutePath).mkString(":")+":"+path_cp+" "+cls+" "+args.mkString(" "))
  }

  // Gobbles an input stream (used for external processes by loadMain)
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
  def exec(cmd:String):(String,String) = exec(cmd.split(" +"))
  def exec(cmd:Array[String],dir:File=null,env:Array[String]=null,fatal:Boolean=true):(String,String) = {
    val p = Runtime.getRuntime.exec(cmd,env,dir)
    val out=gobble(p.getInputStream); val err=gobble(p.getErrorStream); p.waitFor
    val o=out.toString; val e=err.toString
    if (e.trim!="") { println("Execution error in: "+cmd.mkString(" ")); scala.Console.out.print(o); scala.Console.err.print(e); if (fatal) System.exit(1) }
    (o,e)
  }

  // Capture console/default output and error streams in two strings
  def captureOut[R](f:()=>R) : (R,String,String) = { val c=scala.Console;
    val o0=c.out; val so0=System.out; val po=new PipedOutputStream; c.setOut(new PrintStream(po)); System.setOut(new PrintStream(po)); val out=gobble(new PipedInputStream(po));
    val e0=c.err; val se0=System.err; val pe=new PipedOutputStream; c.setErr(new PrintStream(pe)); System.setErr(new PrintStream(pe)); val err=gobble(new PipedInputStream(pe));
    val r = try { f() } finally { c.setOut(o0); System.setOut(so0); po.close; c.setErr(e0); System.setErr(se0); pe.close }
    (r,out.toString,err.toString)
  }

  // Class loader to run a class with main(args:Array[String]) within the same VM
  def loadMain(cp:List[File],cls:String,args:Array[String]=Array()) = {
    val r = captureOut(()=>{
      try { val l=new CPLoader(cp); val c=l.loadClass(cls); val m = c.getMethod("main",args.getClass); m.invoke(null,args) }
      catch { case t:Throwable => val c=t.getCause; (if (c!=null) c else t).printStackTrace(scala.Console.err) }
    })
    System.gc; Thread.sleep(50); System.gc; (r._2,r._3) // call finalize on class loader
  }
  import java.net.{URL,URLClassLoader}
  private class CPLoader(cp:List[File]) extends URLClassLoader(cp.map(_.toURI.toURL).toArray,null) {
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
