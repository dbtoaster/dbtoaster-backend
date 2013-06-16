import java.io._
object Compiler {
  import ddbt.frontend._

  def main(args: Array[String]) {
    val files=exec(Array("find","resources/queries","-name","*.sql","-and","-not","-name","schemas.sql"))._1.split("\n")
    for (f <- files) test(f)
  }

  def test(path:String) {
    println("========= TEST: "+path)
    val t = System.currentTimeMillis;
    val s=Parser.loadSQL(path)
    val t1 = System.currentTimeMillis-t;
    val m3=exec(Array("resources/dbtoaster","-l","M3",path))._1
    //println(m3);
    val t2 = System.currentTimeMillis;
    val m=Parser.parseM3(m3)
    val t3 = System.currentTimeMillis-t2;
    println("Parse time: SQL:"+t1+" M3:"+t3)
  }

  def makeTemp(path:String) {
    def del(f:File) {
      if (f.isDirectory()) f.listFiles().foreach{c=>del(c)}
      if (!f.delete()) sys.error("Failed to delete file: " + f)
    }
    val tmp=new File(path);
    if (tmp.exists) del(tmp)
    if (!tmp.mkdirs()) sys.error("Dir creation failed")
  }
  
  // execute arbitrary command, return (out,err)
  def exec(cmd:String):(String,String) = exec(cmd.split(" "))
  def exec(cmd:Array[String]):(String,String) = {
    val p = Runtime.getRuntime.exec(cmd /*,null,new File(outPath)*/)
    /*
    val p = cmd match {
      case a:Array[String] => Runtime.getRuntime.exec(a / *,null,new File(outPath)* /)
      case s:String => Runtime.getRuntime.exec(s / *,null,new File(outPath)* /)
      case _ => sys.error("Bad exec argument")
    }
    */
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
    if (!e.equals("")) println("\nExec: "+cmd+"\n- Out: "+o+"\n- Err: "+e+"\n")
    (o,e)
  }
  
}

/*

1. frontend
	- create temp directory
	- generate the m3 file
	- parse the m3
	- parse the SQL

2. type the AST (?)
	- make sure we have enough information to output scala

==> obtain an AST

3. optimize the AST
	- high level optimization like replacing List

4. prepare for distributed system
	- add node conditionals in the code
	- replace some read operations by send/receive (depending node)
	
5. generate code with LMS

6. Distribute over nodes

7. Evaluate query

*/
