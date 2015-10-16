package ddbt.lib

import scala.collection.mutable.ArrayBuffer

class Stopwatch {

  private var startTime = -1L
  private var elapsedTime = 0L
  private var running = false
  private val checkpoints = new ArrayBuffer[Long]()
  
  def start(): Stopwatch = {
    if (!running) {
      startTime = System.nanoTime
      running = true
    }
    this
  }

  def stop(checkpoint: Boolean = true): Stopwatch = {
    if (running) {
	  val lastRun = System.nanoTime - startTime
      elapsedTime += lastRun
      if (checkpoint) checkpoints += lastRun
      running = false
    }
    this 
  }
  
  def getElapsedTime: Long =
    if (!running) elapsedTime / 1000000L
    else throw new RuntimeException("Reading elapsed time of running watchstop")
  
  def reset() = {
    startTime = -1L
    elapsedTime = 0L
    checkpoints.clear
    running = false
  }

  def checkpoint() = {
    if (running) {
      val currentTime = System.nanoTime
      val lastRun = currentTime - startTime
      elapsedTime += lastRun
      checkpoints += lastRun
      startTime = currentTime
    }
  }
      
  def getCheckpoints(): ArrayBuffer[Long] = checkpoints map (_ / 1000000L) 
  
  @inline
  def time[R](block: => R, checkpoint: Boolean = true): R = {
    this.start()
    val result = block
    this.stop(checkpoint)
    result
  }      
}


object Stopwatch {
  
  def time[R](message: String, block: => R): R = {
    val sw = new Stopwatch
    val res = sw.time(block, false)
    println(message + sw.getElapsedTime + " ms")
    res
  }
}