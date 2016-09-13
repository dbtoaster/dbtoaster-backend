#!/usr/bin/env scala
import java.io.PrintWriter
import scala.io.Source._
object HelloWorld extends App {
  val optsMap = List("" -> " ", "Entry" -> "e", "TmpVar" -> "v" , "CmpMult" -> "c", "FixedRange" -> "f" , "Online" -> "o", "Inline" -> "n" , "DeadIdx" -> "d", "Fusion full" -> "l", "CodeMotion" -> "m", "RefCnt" -> "r" , "Index" -> "i").toMap
  val lines = fromFile("out_dump.txt").getLines().mkString("\n")
  val parts = lines.split("Optimizations ::").drop(1)
  println(s"Number of parts = ${parts.size}")
  val pw = new PrintWriter("tpcc_results.csv")
  pw.println(optsMap.keys.mkString(","))
  pw.println(optsMap.values.mkString(","))
  parts.foreach(p => {
    val l = p.split("\n")
    val opts = l(0).split(", ").map(o => optsMap(o.trim)).mkString
    val res = p.split("tpmc array = ").drop(1).map(_.split("]\n")(0)).last.drop(1).dropRight(1)
    pw.println(s"$opts, $res")
  })
  pw.close()
}
HelloWorld.main(args)