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

  // Execute arbitrary command, return (out,err)
  def exec(cmd:String):(String,String) = exec(cmd.split(" "))
  def exec(cmd:Array[String],dir:File=null):(String,String) = {
    val p = Runtime.getRuntime.exec(cmd,null,dir)
    def gobble(in:InputStream) = new Runnable {
      var out = new StringBuilder
      var thr = new Thread(this); thr.start
      override def toString = { thr.join; out.toString.trim }
      override def run {
        val r = new BufferedReader(new InputStreamReader(in))
        var l = r.readLine; while(l != null) { out.append(l+"\n"); l = r.readLine }; r.close
      }
    }
    val out=gobble(p.getInputStream); val err=gobble(p.getErrorStream); p.waitFor
    val o=out.toString; val e=err.toString
    if (e.trim!="") { println("Execution error in: "+cmd.mkString(" ")); print(o); System.err.print(e); System.exit(1) }
    (o,e)
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
    val tmp = if (path!=null) new File(path) else File.createTempFile("ddbt",null)
    def del(f:File) {
      if (f.isDirectory()) f.listFiles().foreach{c=>del(c)}
      if (!f.delete()) sys.error("Failed to delete file: " + f)
    }
    if (tmp.exists) del(tmp); tmp.mkdirs // have a fresh folder
    Runtime.getRuntime.addShutdownHook(new Thread{ override def run() = del(tmp) });
    tmp
  }
}
