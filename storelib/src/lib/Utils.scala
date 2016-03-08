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
  try { prop_.load(this.getClass.getResource("/ddbt.properties").openStream()) } catch { case _:Throwable => warning("conf/ddbt.properties does not exist.\n"+
        "Please configure at least ddbt.dbtoaster to dbtoaster_frontend binary path.\nSet ddbt.base_repo if you have access to DBToaster's repository.") }
  def prop(name:String,d:String="") = prop_.getProperty("ddbt."+name,d)

  val LMS_PROPERTY = "lms"
  def isLMSTurnedOn = prop(LMS_PROPERTY)=="1"

  val find_bin=prop("find_bin","find");
  val cppOpts=prop("cpp_opts","").split(" ").toList
  
  // Paths related to DBToaster
  val path_repo = { val r=prop("base_repo",null); if (r==null) null else r+"/dbtoaster/compiler/alpha5" }
  val path_bin  = (if (path_repo!=null) path_repo+ "/" else "")+prop("dbtoaster.frontend","bin/dbtoaster_frontend")
  private lazy val path_jdk = { var p=prop("jdk",null); if (p!=null) { val r=prop(p,null); if (r!=null) p=r; }; if (p==null) System.getProperty("java.home") else p }
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
      def execOut(cmd:String) = exec(cmd.split(" +"),prefix="")
      val args="-cp "+cp+" -d "+path_dir+" "+opts.mkString(" ")+" "
      val fsc="fsc "+prop("jvm").split(" +").map("-J"+_).mkString(" ")+" "+args
      (fs:List[String]) => try { execOut(fsc+fs.mkString(" ")) } catch { case _:IOException => execOut(path_jvm+" scala.tools.nsc.Main "+args+fs.mkString(" ")) }
    }
  }

  // C++ compiler wrapper
  def cppCompiler(out:String,cPath:String,boost:String,cppLibDir:String) = {
    val as = (List(prop("gpp","g++"),cppLibDir+"/main.cpp","-Wall","-Wno-unused-variable","-Wno-strict-overflow","-std=c++11","-include",out,"-o",cPath,"-O3","-lpthread","-ldbtoaster","-I"+cppLibDir,"-L"+cppLibDir) :::
             (if (boost==null) Nil else List("program_options","serialization","system","filesystem","chrono","thread").map("-lboost_"+_+Utils.prop("lib_boost_thread","")) ::: List("-I"+boost+"/include","-L"+boost+ "/lib")) :::
             cppOpts).filter(_!="")
    //make DBT c++ library
    Utils.exec(Array("make","-C",cppLibDir))
    Utils.exec(as.toArray)
  }

  // Executes a Scala program
  def scalaExec(cp:List[File],cls:String,args:Array[String]=Array(),external:Boolean=false) {
    if (!external) runMain(cp,cls,args)
    else {
      val env = ("JAVA_HOME="+path_jdk :: scala.collection.JavaConversions.mapAsScalaMap(System.getenv).filter(x=>x._1.toUpperCase!="JAVA_HOME").map(x=>x._1+"="+x._2).toList).toArray
      exec((path_jvm+" -cp "+cp.map(_.getAbsolutePath).mkString(":")+":"+path_cp+" "+cls+" "+args.mkString(" ")).split(" +"),env=env,fatal=true,prefix="")
    }
  }

  // XXX: use scala.sys.process.Process and scala.sys.process.ProcessLogger instead
  // Gobbles an input stream (lines not matching prefix are sent to out, null matches all, "" matches none)
  private def gobble(in:InputStream,out:PrintStream=null,prefix:String=null) = new Thread {
    private var buf = new StringBuilder
    override def toString = { join; buf.toString.trim }
    override def run {
      val r = new BufferedReader(new InputStreamReader(in)); var l=r.readLine
      val n = if (prefix==null || out==null) -1 else prefix.length
      while(l!=null) {
        if (n== -1) buf.append(l+"\n")
        else if (n>0 && l.startsWith(prefix)) buf.append(l.substring(n)+"\n")
        else if (out!=null) out.println(l)
        l = r.readLine
      }
      r.close
    }
    start
  }

  // Execute arbitrary command, return (out,err)
  def exec(cmd:String,fatal:Boolean):(String,String) = exec(cmd.split(" +"),null,null,fatal)
  def exec(cmd:Array[String],dir:File=null,env:Array[String]=null,fatal:Boolean=true,prefix:String=null):(String,String) = {
//    java.lang.System.err.println(cmd.mkString(" "))
    val p = Runtime.getRuntime.exec(cmd,env,dir)
    val out=gobble(p.getInputStream,scala.Console.out,prefix); val err=gobble(p.getErrorStream,scala.Console.err,prefix); val exitVal=p.waitFor; val o=out.toString; val e=err.toString
    if (fatal && (e.trim!="" || exitVal!=0)) {
      if(e.trim!="") {
        println("Execution error in: "+cmd.mkString(" "))
        scala.Console.out.print(o)
        scala.Console.err.print(e)
      } else {
        scala.Console.err.print("Error: exit value is " + exitVal)
      }
      // System.exit(if(exitVal!=0) exitVal else 1)
    }
    (o,e)
  }

  // Capture console/default output and error streams in two strings
  def captureOut[R](f:()=>R,prefix:String=null) : (R,String,String) = { val c=scala.Console
    val o0=c.out; val so0=System.out; val po=new PipedOutputStream; c.setOut(new PrintStream(po)); System.setOut(new PrintStream(po)); val out=gobble(new PipedInputStream(po),o0,prefix)
    val e0=c.err; val se0=System.err; val pe=new PipedOutputStream; c.setErr(new PrintStream(pe)); System.setErr(new PrintStream(pe)); val err=gobble(new PipedInputStream(pe),e0,prefix)
    val r = try { f() } finally { c.setOut(o0); System.setOut(so0); po.close; c.setErr(e0); System.setErr(se0); pe.close }
    (r,out.toString,err.toString)
  }

  // Class loader to run a class with main(args:Array[String]) within the same VM
  def runMain(cp:List[File],cls:String,args:Array[String]=Array()) = {
    try { val l=new CPLoader(cp); val c=l.loadClass(cls); val m = c.getMethod("main",args.getClass); m.invoke(null,args) }
    catch { case t:Throwable => val c=t.getCause; (if (c!=null) c else t).printStackTrace(scala.Console.err) }
    finally { System.gc; Thread.sleep(50); System.gc }
  }
  import java.net.{URL,URLClassLoader}
  private class CPLoader(cp:List[File]) extends URLClassLoader(cp.map(_.toURI.toURL).toArray,null) {
    override def loadClass(name:String, resolve:Boolean) : Class[_] = {
      try { return super.loadClass(name, resolve); }
      catch { case e:ClassNotFoundException => Class.forName(name, resolve, Utils.getClass.getClassLoader); }
    }
  }

  // Files I/O
  def read(file:String) = { val f=new File(file); val cs=new Array[Char](f.length.toInt); val r=new FileReader(f); r.read(cs); r.close; new String(cs) }
  def write(file:String,data:String) { val f=new File(file); val dir=f.getParentFile; if (dir!=null && !dir.exists) dir.mkdirs; val o=new PrintWriter(f); o.write(data); o.close() }

  // String manipulation
  def ind(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll("\n? *$","").replaceAll("\n","\n"+i) }
  def tup(vs:List[String]) = { val v=vs.mkString(","); if (vs.size>1) "("+v+")" else v }

  // Fresh variables name provider
  private val counter = scala.collection.mutable.HashMap[String,Int]()
  def fresh(name:String="x") = { val c = counter.getOrElse(name,0)+1; counter.put(name,c); name+c }
  def freshClear() = counter.clear

  // Create a temporary directory that will be removed at shutdown
  def makeTempDir(path:String=null,auto_delete:Boolean=false):File = {
    val tmp = if (path!=null) new File(path) else new File("target/tmp") //File.createTempFile("ddbt",null) deletes folder too early on OracleJVM7/MacOS
    def del(f:File) {
      if (f.isDirectory()) f.listFiles().foreach{c=>del(c)}
      if (!f.delete()) sys.error("Failed to delete file: " + f)
    }
    if (tmp.exists) del(tmp); tmp.mkdirs // have a fresh folder
    if (auto_delete) Runtime.getRuntime.addShutdownHook(new Thread{ override def run() = del(tmp) });
    tmp
  }

  // Time measurement
  def ns[T](f:()=>T) = { val t0=System.nanoTime; var r=f(); val t1=System.nanoTime; (t1-t0,r) }
  def time(ns:Long,p:Boolean=true) = if (p) { val us=ns/1000; ("%d.%06d").format(us/1000000,us%1000000) } else { val ms=math.round(ns/1000000.0); ("%d.%03d").format(ms/1000,ms%1000) }

  def generateNewFileName(qName:String, pathTemplate:String) = {
    var queryName = qName
    var f = new java.io.File(pathTemplate.format(queryName))
    var couldLock = false
    while(!couldLock) {
      var i = 1
      while(f.exists) {
        queryName = qName + "_" + i
        i += 1
        f = new java.io.File(pathTemplate.format(queryName))
      }
      var channel:java.nio.channels.FileChannel = null;
      var lock: java.nio.channels.FileLock = null;
      try {
        channel = new java.io.RandomAccessFile(f, "rw").getChannel();

        // Use the file channel to create a lock on the file.
        // This method blocks until it can retrieve the lock.
        lock = channel.lock

        // Try acquiring the lock without blocking. This method returns
        // null or throws an exception if the file is already locked.
        try {
          lock = channel.tryLock
        } catch {
          case e: java.nio.channels.OverlappingFileLockException =>
          // File is already locked in this thread or virtual machine
        }

        if(lock != null) {

          f.createNewFile

          // Release the lock
          lock.release

          couldLock = true
        }
      } catch {
          case e: Exception => //...
      } finally {
        if(lock != null && lock.isValid) lock.release();
        if(channel != null) channel.close();
      }
    }
    queryName
  }
}
