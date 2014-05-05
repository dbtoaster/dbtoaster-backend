// --------- Project informations
Seq(
  name := "DistributedDBtoaster",
  organization := "ch.epfl.data",
  version := "0.1"
)

// --------- Paths
Seq(
  scalaSource in Compile <<= baseDirectory / "src",
  javaSource in Compile <<= baseDirectory / "src",
  sourceDirectory in Compile <<= baseDirectory / "src",
  scalaSource in Test <<= baseDirectory / "test",
  javaSource in Test <<= baseDirectory / "test",
  sourceDirectory in Test <<= baseDirectory / "test",
  resourceDirectory in Compile <<= baseDirectory / "conf"
)

resolvers += "Sonatype OSS Snapshots" at
  "https://oss.sonatype.org/content/repositories/snapshots"

// --------- Dependencies
libraryDependencies ++= Seq(
  "com.typesafe.akka" %% "akka-actor"     % "2.2.3",
  "com.typesafe.akka" %% "akka-remote"    % "2.2.3",
  "org.scala-lang"     % "scala-actors"   % scalaVersion.value, // to compile legacy Scala
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value,
  "org.scalatest"     %% "scalatest"      % "2.0" % "test",
  "com.github.axel22" %% "scalameter" % "0.4"
)

testFrameworks += new TestFramework(
  "org.scalameter.ScalaMeterFramework")

logBuffered := false

// --------- Compilation options
Seq(
  scalaVersion := "2.10.3",
  scalacOptions ++= Seq("-deprecation","-unchecked","-feature","-optimise","-Yinline-warnings"), // ,"-target:jvm-1.7"
  javacOptions ++= Seq("-Xlint:unchecked","-Xlint:-options","-source","1.6","-target","1.6") // forces JVM 1.6 compatibility with JDK 1.7 compiler
)

// --------- Execution options
Seq(
  fork := true, // required to enable javaOptions
  //javaOptions ++= Seq("-agentpath:"+"/Applications/Tools/YourKit Profiler.app/bin/mac/libyjpagent.jnilib"+"=sampling,onexit=snapshot,builtinprobes=all"),
  javaOptions ++= Seq("-Xss128m","-XX:-DontCompileHugeMethods","-XX:+CMSClassUnloadingEnabled"), // ,"-Xss512m","-XX:MaxPermSize=2G"
  javaOptions ++= Seq("-Xmx14G","-Xms14G"/*,"-verbose:gc"*/), parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath="+cp.files.absString) // propagate paths
)

// --------- Custom tasks
addCommandAlias("toast", ";run-main ddbt.Compiler ") ++
addCommandAlias("unit", ";run-main ddbt.UnitTest ") ++
addCommandAlias("queries", "unit -dd -v -x -s 0 -l scala ") ++
addCommandAlias("queries-lms", "unit -dd -v -x -s 0 -l lms -xsc ") ++
addCommandAlias("queries-akka", "unit -dd -v -x -s 0 -l akka -qx mddb/query2 -qx tpch/query21 ") // too long to compile/execute

// Akka individual queries testing
addCommandAlias("aq","unit -dd -v -x -s 0 -l akka -q ")

addCommandAlias("bench", ";unit -v -x -xsc -xvm -csv bench.csv -l ") ++ // usage: sbt 'bench lms'
addCommandAlias("bench-all", ";unit -v -x -xsc -xvm -csv bench-all.csv -l scala -l lms -l lscala -l llms ") ++ // usage: sbt 'bench-all'
//addCommandAlias("bench-all-tpch", ";unit -p 2 -x -xsc -xvm -csv bench-all.csv -dump bench-all-dump.txt -l lscala -l llms -l scala -l lms_0 -l lms_spec -l lcpp -w 2 -s 3 -t 60000 -d big_del -q tpch.*query[0-9]+.sql ")
addCommandAlias("bench-all-tpch", ";unit -x -xsc -xvm -p 2 -w 2 -s 3 -t 60000 -csv bench-all.csv -dump bench-all-dump.txt -l scala -l lms_0 -l lms_spec -d big_del -q tpch.*query[0-9]+ ")

// --------- Packaging: fake (to use SBT paths for debugging), full (packages all dependencies), dist (ship on all cluster hosts)
InputKey[Unit]("pkg") <<= InputTask(_ => Def.spaceDelimited("<args>")) { result =>
 (result, baseDirectory, classDirectory in Compile, classDirectory in Test, fullClasspath in Runtime, scalaVersion, compile in Compile, compile in Test, copyResources in Compile) map {
  (args,base,cls,test,cp,vers,_,_,_) =>
    val prop=new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
    def pr(n:String,d:String="") = prop.getProperty("ddbt."+n,d)
    import scala.collection.JavaConversions._
    import scala.sys.process._
    // Packaging
    val dir=base/"pkg"; if (!dir.exists) dir.mkdirs
    val jars = cp.files.absString.split(":").filter(_!=cls.toString).distinct.sorted // all dependencies
    def mk_jar(name:String,root:File,path:String*) { Process(Seq("jar","-cMf",(dir/(name+".jar")).getPath) ++ path.flatMap(p=>Seq("-C",root.getPath,p)) ).!; print(".") }
    def mk_script(name:String,args:String) {
      val out=dir/name; IO.write(out,"#!/bin/sh\ncd `dirname $0`\nCP_DEPS=\""+jars.mkString(":")+"\"\n"+
      "if [ -f ddbt_deps.jar ]; then CP_DEPS=\"ddbt_deps.jar\"; fi\n"+{ val x=pr("cmd_extra").trim; if (x!="") x+"\n" else "" }+
      "exec "+pr("cmd_java","java")+" "+args+"\n"); out.setExecutable(true)
    }
    if (args.contains("fake")) { // fake runner for debug
      val cp0="../target/scala-"+vers.replaceAll(".[0-9]$","")+"/"
      mk_script("run","-classpath \"$CP_DEPS:"+cp0+"classes:"+cp0+"test-classes\" \"$@\"")
    } else {
      print("Packaging DDBT libraries: ")
      mk_jar("ddbt_lib",cls,"ddbt/lib","ddbt.properties") // runtime libraries
      mk_jar("ddbt_gen",test,"ddbt/test/gen") // tests
      mk_script("run","-classpath \"$CP_DEPS:ddbt_lib.jar:ddbt_gen.jar\" \"$@\"")
      if (args.contains("full")) { mk_jar("ddbt",cls,".") // compiler
        val tmp=base/"target"/"pkg_tmp"; tmp.mkdirs; val r=tmp/"reference.conf"; val rs=tmp/"refs.conf"; IO.write(rs,"")
        jars.foreach { j => Process(Seq("jar","-xf",j),tmp).!; if (r.exists) IO.append(rs,IO.read(r)); print(".") }
        if (r.exists) r.delete; rs.renameTo(r); mk_jar("ddbt_deps",tmp,"."); IO.delete(tmp)
        mk_script("toast","-classpath \"$CP_DEPS:ddbt.jar\" ddbt.Compiler \"$@\"")
        mk_script("unit","-classpath \"$CP_DEPS:ddbt.jar\" ddbt.UnitTest \"$@\"")
      }
      println
      // Distribution over cluster nodes
      if (args.contains("dist")) { print("Distribution: ")
        val hs=(prop.stringPropertyNames.filter(_.matches("^ddbt.host[0-9]+$")).map(x=>prop.getProperty(x,null))+pr("master","127.0.0.1")).map(_.split(":")(0)).toSet
        val (cmd,path)=(pr("cmd_scp","rsync -av")+" "+dir+"/ "+pr("cmd_user","root")+"@",":"+pr("cmd_path","")+"/")
        hs.foreach { h => print(h); print(if ( (cmd+h+path).!(ProcessLogger(l=>(),l=>println("\nTransfer to "+h+" error: "+l.trim))) ==0) "." else "<!>") }; println
      }
    }
  }
}

// --------- Cluster execution
// XXX: this needs to be integrated in UnitTest.scala instead
// -H = local host:port
// -M = master host:port
// -W = number of (local@worker/total@master) workers
// -C = cluster_mode:hosts_count
commands += Command.args("exec","")((state:State, args:Seq[String]) => {
  val prop=new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
  def pr(n:String,d:String) = prop.getProperty("ddbt."+n,d)
  import scala.collection.JavaConversions._
  import scala.sys.process._
  val lo="127.0.0.1"
  val cl=pr("cluster","2").toInt; val w=pr("workers","1").toInt; val m={ val m=pr("master",lo).split(":"); (m(0),if (m.length>1) m(1).toInt else 8800) }
  val hosts=prop.stringPropertyNames.filter(x=>x.matches("^ddbt.host[0-9]+$")).toList.sorted.zipWithIndex.map{ case (x,i)=> val h=prop.getProperty(x,null).split(":")
    (h(0),if (h.length>1 && h(1)!="") h(1).toInt else m._2+1+i,if (h.length>2) h(2).toInt else w,x.substring(9).toInt)
  }
  val hn=pr("hosts","1").toInt
  if (args.size<1) println("Usage: exec <class>") else cl match {
    case 0|1 => ("pkg/run "+args.mkString(" ")+" -H"+m._1+":"+m._2+" -W"+w+" -C"+cl+":"+hn).! // launch in the same JVM
    case 2 => // launch all JVMs locally
      def exec(as:String,p:String) = { val t=new Thread(){ override def run() { ("pkg/run "+args.mkString(" ")+" "+as) ! ProcessLogger(l=>println(p+": "+l),l=>System.err.println(p+": "+l)) }}; t.start; t }
      val nh=pr("hosts","1").toInt
      val tm=exec("-H"+lo+":"+m._2+" -W"+(nh*w),"M"); Thread.sleep(100) // launch master
      val ths=(0 until nh) map { i=> exec("-H"+lo+":"+(m._2+1+i)+" -W"+w+" -M"+lo+":"+m._2,""+(i+1)) }
      (ths:+tm).foreach(_.join)
    case 3 => // launch remotely with SSH
      val (cmd,path)=(pr("cmd_ssh","ssh")+" "+pr("cmd_user","root")+"@"," "+pr("cmd_path","")+"/run "+args.mkString(" "))
      def exec(host:String,as:String,p:String) = { val t=new Thread(){ override def run() { (cmd+host+path+" "+as) ! ProcessLogger(l=>println(p+": "+l),l=>System.err.println(p+": "+l)) }}; t.start; t }
      val tm=exec(m._1,"-H"+m._1+":"+m._2+" -W"+hosts.map(_._3).sum,"M"); Thread.sleep(100) // launch master
      val ths=hosts.map { h => exec(h._1,"-H"+h._1+":"+h._2+" -W"+h._3+" -M"+m._1+":"+m._2,""+h._4) } // launch workers
      (ths:+tm).foreach(_.join)
    case _ => System.err.println("Unrecognized 'ddbt.cluster' value")
  }
  state
})

// --------- LMS codegen, enabled with ddbt.lms = 1 in conf/ddbt.properties
{
  val prop=new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
  if (prop.getProperty("ddbt.lms","0")!="1") Seq() else Seq(
    sources in Compile ~= (fs => fs.filter(f=> !f.toString.endsWith("codegen/LMSGen.scala"))), // ++ (new java.io.File("lms") ** "*.scala").get
    scalaSource in Compile <<= baseDirectory / "lms", // incorrect; but fixes dependency and allows incremental compilation (SBT 0.13.0)
    //unmanagedSourceDirectories in Compile += file("lms"),
    // LMS-specific options
    scalaOrganization := "org.scala-lang.virtualized",
    scalaVersion := "2.10.2-RC1",
    libraryDependencies ++= Seq(
      "org.scala-lang.virtualized" % "scala-library" % scalaVersion.value,
      "org.scala-lang.virtualized" % "scala-compiler" % scalaVersion.value,
      "org.apache.logging.log4j" % "log4j-api" % "2.0-rc1",
      "org.apache.logging.log4j" % "log4j-core" % "2.0-rc1",
      "org.slf4j" % "slf4j-api" % "1.7.2",
      "org.slf4j" % "slf4j-ext" % "1.7.2",
      "mysql" % "mysql-connector-java" % "5.1.28",
      "org.scalariform" %% "scalariform" % "0.1.4",
      "org.scalatest" %% "scalatest" % "2.0",
      "EPFL" %% "lms" % "0.3-SNAPSHOT"
    ),
    scalacOptions ++= List("-Yvirtualize")
  )
}

// show full-classpath
//commands += Command.args("cmd","")((state: State, args: Seq[String]) => { println(args.toList); state })
//javaHome := Some(file("/System/Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Home"))
//javaHome := Some(file("/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home"))
//{
//  val t=TaskKey[Unit]("queries-gen2")
//  val q=TaskKey[Unit]("queries-test2")
//  Seq(
//    fullRunTask(t in Compile, Compile, "ddbt.UnitTest", "tiny","tiny_del","standard","standard_del"),
//    q <<= (t in Compile) map { x => scala.sys.process.Process(Seq("sbt", "test-only ddbt.test.gen.*")).!; }
//    //(test in Test) <<= (test in Test) dependsOn (t in Compile),   // force tests to rebuild
//    //testOptions in Test += Tests.Argument("-l", "ddbt.SlowTest"), // execute only non-tagged tests
//  )
//}
// jar -cf foo.jar -C target/scala-2.10/classes ddbt/lib
// TaskKey[Unit]("test-queries") := { scala.sys.process.Process(Seq("sbt", "test-only ddbt.test.gen.*")).! }
//
// Seq(
//   autoCompilerPlugins := true,
//   libraryDependencies <+= scalaVersion(v=>compilerPlugin("org.scala-lang.plugins" % "continuations" % v)),
//   scalacOptions += "-P:continuations:enable"
// )
//
// http://grokbase.com/t/gg/simple-build-tool/133xb2khew/sbt-external-process-syntax-in-build-sbt
// http://stackoverflow.com/questions/15494508/bash-vs-scala-sys-process-process-with-command-line-arguments
//compile in Compile <<= (compile in Compile) map { x => ("src/librna/make target/scala-2.10/classes").run.exitValue; x }
//	"org.scala-lang" % "scala-reflect" % v,
//	"ch.epfl" %% "lms" % "0.4-SNAPSHOT",
//	"org.scalariform" %% "scalariform" % "0.1.4",
//parallelExecution in Test := false
//scalaOrganization := "org.scala-lang.virtualized"
//scalaVersion := Option(System.getenv("SCALA_VIRTUALIZED_VERSION")).getOrElse("2.10.2-RC1")
//resolvers ++= Seq(
//    ScalaToolsSnapshots,
//    "Sonatype Public" at "https://oss.sonatype.org/content/groups/public",
//	Classpaths.typesafeSnapshots
//)
// disable publishing of main docs
//publishArtifact in (Compile, packageDoc) := false
//mainClass := Some("Main")
//selectMainClass := Some("Main")
// Storm dependencies:
//resolvers ++= Seq(
//  "clojars" at "http://clojars.org/repo/",
//  "clojure-releases" at "http://build.clojure.org/releases"
//)
//
  //"com.esotericsoftware.kryo" % "kryo"  % "2.21",
  //"com.twitter"       %% "chill"        % "0.3.1",
  //"org.spark-project" %% "spark-core"   % "0.8.0-SNAPSHOT",
  //"com.github.velvia" %% "scala-storm"  % "0.2.3-SNAPSHOT",
  //"storm"              % "storm"        % "0.8.2"
