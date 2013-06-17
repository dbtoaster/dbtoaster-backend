package ddbt

import java.io._
object Compiler {
  import ddbt.frontend._

  def main(args: Array[String]) {
  
    val m3 = toast("resources/queries/finance/axfinder.sql");
    
    
    val m3p=M3Parser.parse(m3)
    //println(m3p)
    
    val m3pp=M3Parser.parse(m3p.toString)
    if (m3p==m3pp) println("Equal") else println("Differ")
    

    /*
    val m3c=m3.replaceAll("\\s","")
    val m3pc=m3p.toString.replaceAll("\\s","")
    
    println(m3c)
    println(m3pc)
    */

    /*
    println(m3)
    println
    println("--------------------------------------------------------------------")
    println
    println(m3p)
    */
  
    //println("Hello world")    
    
    
   // val files=exec(Array("find","resources/queries","-name","*.sql","-and","-not","-name","schemas.sql"))._1.split("\n")
   // for (f <- files) test(f)
  }
/*
  def test(path:String) {
    println("========= TEST: "+path)
    val t = System.currentTimeMillis;
    val s=SQLParser.load(path)
    val t1 = System.currentTimeMillis-t;

    val os=System.getProperty("os.name").toLowerCase
    val fam = List("win","lin","mac").filter{os.contains(_)}.head
    val m3=exec(Array("resources/dbtoaster_"+fam,"-l","M3",path))._1
    //println(m3);
    val t2 = System.currentTimeMillis;
    val m=M3Parser.parse(m3)
    val t3 = System.currentTimeMillis-t2;
    println("Parse time:  SQL:"+t1+"ms      M3:"+t3+"ms")
    println
  }
*/

  // UTILITIES -----------------------------------------------------------------

  def toast(path:String) = {
    val os=System.getProperty("os.name").toLowerCase
    val fam = List("win","lin","mac").filter{os.contains(_)}.head
    exec(Array("resources/dbtoaster_"+fam,"-l","M3",path))._1
  }
  
  // execute arbitrary command, return (out,err)
  def exec(cmd:String):(String,String) = exec(cmd.split(" "))
  def exec(cmd:Array[String]):(String,String) = {
    val p = Runtime.getRuntime.exec(cmd /*,null,new File(outPath)*/)
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

  /*
  def makeTemp(path:String) {
    def del(f:File) {
      if (f.isDirectory()) f.listFiles().foreach{c=>del(c)}
      if (!f.delete()) sys.error("Failed to delete file: " + f)
    }
    val tmp=new File(path);
    if (tmp.exists) del(tmp)
    if (!tmp.mkdirs()) sys.error("Dir creation failed")
  }
  */
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
