package ddbt.lib.store

import scala.collection.mutable

//abstract class SEntry[E<:Product:Manifest] extends Entry(manifest[E].runtimeClass.newInstance.asInstanceOf[Product].productArity)
class GenericEntry(val map: mutable.HashMap[Int,Any], val n: Int, val isSampleEntry: Boolean) extends Entry(n) {
  def this(n: Int) = this(new mutable.HashMap[Int,Any], n, false)

  def update(i: Int, v:Any) = map.put(i, v)
  def increase(i: Int, v:Any) = v match {
    case _: Int => if (map.contains(i)) map.put(i, map.get(i).asInstanceOf[Int] + v.asInstanceOf[Int]) else map.put(i, v)
    case _: Double => if (map.contains(i)) map.put(i, map.get(i).get.asInstanceOf[Double] + v.asInstanceOf[Double]) else map.put(i, v);
    case _: Long => if (map.contains(i)) map.put(i, map.get(i).asInstanceOf[Long] + v.asInstanceOf[Long]) else map.put(i, v)
    case _: String => if (map.contains(i)) map.put(i, map.get(i).asInstanceOf[String] + v.asInstanceOf[String]) else map.put(i, v)
  }

  def +=(i: Int, v:Any) = increase(i ,v)
  def decrease(i: Int, v:Any) = v match {
    case _: Int => if (map.contains(i)) map.put(i, map.get(i).asInstanceOf[Int] - v.asInstanceOf[Int]) else map.put(i, v)
    case _: Double => if (map.contains(i)) map.put(i, map.get(i).asInstanceOf[Double] - v.asInstanceOf[Double]) else map.put(i, v)
    case _: Long => if (map.contains(i)) map.put(i, map.get(i).asInstanceOf[Long] - v.asInstanceOf[Long]) else map.put(i, v)
  }
  def -=(i: Int, v:Any) = decrease(i ,v)
  def get[E](i: Int) = map.get(i).get.asInstanceOf[E]
  def copy:GenericEntry = new GenericEntry(map.clone, map.size, isSampleEntry)
  def cmp(e: GenericEntry) = GenericEntry.cmp(this, e)
}

object GenericEntry extends EntryIdx[GenericEntry] {
  def apply(ignore: Any, elems: Any*): GenericEntry = {
    val map = new mutable.HashMap[Int, Any]
    
    if (ignore == "SteSampleSEntry") {
      map.put(elems(0).asInstanceOf[Int], elems(1))
    } else {
      for((e, i) <- elems.zipWithIndex) {
        map.put(i+1, e)
      }
    }

    new GenericEntry(map, map.size, ignore == "SteSampleSEntry")
  }
  def hash(e:GenericEntry) :Int = {
    var h = 16;

    // SteSampleSEntry
    if (e.isSampleEntry) {
      return h * 41 + e.map.get(1).get.hashCode()
    } else {
      for (i <- (1 until e.map.size))
        h = h * 41  + e.map.get(i).get.hashCode()
    }
//      e.map.foreach {e => h = h * 41 + e._2.hashCode()}
    return h
  }//e.map.hashCode


  def cmp(e1:GenericEntry, e2:GenericEntry):Int = {

   // System.err.println("Start")
   //  System.err.println("********** E1 ************")
   //  for ((k, v) <- e1.map) System.err.println("   " + k + " "+ v)

   //  System.err.println("********** E2 ************")
   //  for ((k, v) <- e2.map) System.err.println("   " + k + " "+ v)
   //  System.err.println("End")


    // first element is SteSampleSEntry
    if (e1.map.size < e2.map.size) {
      for ((k, v) <- e1.map) {
        if (e2.map.get(k).get != e1.map.get(k).get) {
         //System.err.println("NOT Equals e1(%s) < e2(%s)".format(e1.map, e2.map))
          return 1
        }
      }
     //System.err.println("Equals e1(%s) < e2(%s)".format(e1.map, e2.map))
      0
    } else if (e1.map.size > e2.map.size) {
      for ((k, v) <- e2.map) {
        if (e1.map.get(k).get != e2.map.get(k).get) {
        // System.err.println("NOT Equals e1(%s) > e2(%s)".format(e1.map, e2.map))
          return 1
        }
      }
         //  System.err.println("Equals e1(%s) > e2(%s)".format(e1.map, e2.map))

      0
    } else {
      for (i <- (1 until e1.map.size)) {
        if ( e1.map.get(i).get != e2.map.get(i).get) {
          //System.err.println("NOT Equals e1 < e2")
          return 1
        }
      }
      //System.err.println("Equals e1 = e2")

      0
    }
  }
}

abstract class SEntry2 [T1:Manifest,T2:Manifest] extends Entry(2)
abstract class SEntry3 [T1:Manifest,T2:Manifest,T3:Manifest] extends Entry(3)
abstract class SEntry4 [T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest] extends Entry(4)
abstract class SEntry5 [T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest] extends Entry(5)
abstract class SEntry6 [T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest] extends Entry(6)
abstract class SEntry7 [T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest] extends Entry(7)
abstract class SEntry8 [T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest] extends Entry(8)
abstract class SEntry9 [T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest] extends Entry(9)
abstract class SEntry10[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest] extends Entry(10)
abstract class SEntry11[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest] extends Entry(11)
abstract class SEntry12[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest] extends Entry(12)
abstract class SEntry13[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest] extends Entry(13)
abstract class SEntry14[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest] extends Entry(14)
abstract class SEntry15[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest] extends Entry(15)
abstract class SEntry16[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest,T16:Manifest] extends Entry(16)
abstract class SEntry17[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest,T16:Manifest,T17:Manifest] extends Entry(17)
abstract class SEntry18[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest,T16:Manifest,T17:Manifest,T18:Manifest] extends Entry(18)
abstract class SEntry19[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest,T16:Manifest,T17:Manifest,T18:Manifest,T19:Manifest] extends Entry(19)
abstract class SEntry20[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest,T16:Manifest,T17:Manifest,T18:Manifest,T19:Manifest,T20:Manifest] extends Entry(20)
abstract class SEntry21[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest,T16:Manifest,T17:Manifest,T18:Manifest,T19:Manifest,T20:Manifest,T21:Manifest] extends Entry(21)
abstract class SEntry22[T1:Manifest,T2:Manifest,T3:Manifest,T4:Manifest,T5:Manifest,T6:Manifest,T7:Manifest,T8:Manifest,T9:Manifest,T10:Manifest,T11:Manifest,T12:Manifest,T13:Manifest,T14:Manifest,T15:Manifest,T16:Manifest,T17:Manifest,T18:Manifest,T19:Manifest,T20:Manifest,T21:Manifest,T22:Manifest] extends Entry(22)
