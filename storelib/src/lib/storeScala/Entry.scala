package ddbt.lib.storeScala

abstract class Entry(n: Int) {
  val data = new Array[Any](n)


  def copy(): Entry // returns a copy of the entry, for B-Trees only


  def copyFrom(e: Entry): Unit = {
    throw new UnsupportedOperationException
  }

  //copies contents of "e" into this

  var next:Entry=null

  var prev:Entry=null
}
