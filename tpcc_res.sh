#!/usr/bin/env scala
import java.io.{PrintWriter, FileWriter}
import scala.io.Source._
object HelloWorld extends App {
  val optsMap = List("" -> " ", "Entry" -> "E", "TmpVar" -> "V" , "TmpMap" -> "M", "CmpMult" -> "T", "FixedRange" -> "G" , "Online" -> "O", "Inline" -> "N" , "DeadIdx" -> "D", "Fusion full" -> "F", "CodeMotion" -> "C", "RegexHoister" -> "X", "RefCnt" -> "R" , "Index" -> "I", "SliceInline" -> "S", "Fusion"->"P", "MultiResSplitter" -> "U", "InitialStoreSize" -> "Z", "SliceNoUpdate" -> "L", "ColdMotion" -> "Q").toMap
  val lines = fromFile("out_dump.txt").getLines().mkString("\n")
  val parts = lines.split("Optimizations ::").drop(1)
  println(s"Number of parts = ${parts.size}")
  val pw = new PrintWriter(new FileWriter("tpcc_res_scala.csv", true))
  //pw.println(optsMap.keys.mkString(","))
  //pw.println(optsMap.values.mkString(","))
  parts.foreach(p => {
    val l = p.split("\n")
    val opts = "scala-" //l(0).split(", ").map(o => optsMap(o.trim)).sortWith(_ < _).mkString("scala-","","")
    val res = p.split("tpmc array = ").drop(1).map(_.split("]\n")(0)).last.drop(1).dropRight(1)
    pw.println(s"$opts, $res")
  })
  pw.close()
}
HelloWorld.main(args)