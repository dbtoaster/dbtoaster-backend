package ddbt.lib.storeScala

import java.util

abstract class Idx[E <: Entry] {
  protected var dataHead: Entry = null
  protected var ops: EntryIdx[E] = null
  protected var idx = 0
  protected var unique = false
  var size = 0//GS investigate why it cannot be protected

  def this(st: Store[E], idx: Int, unique: Boolean) {
    this()
    this.ops = st.ops(idx)
    this.idx = idx
    this.unique = unique
  }

  def w(n: String) {
    throw new NotImplementedError(this.getClass().getName() + ": " + n + " not supported");
  }

  def unsafeInsert(e: E): Unit = {
    w("unsafeInsert")
  }

  def getSizeStat = ""

  def delete(e: E): Unit = {
    w("delete")
  }

  def deleteCopy(e: E, primary: Idx[E]) {
    val ref = primary.get(e)
    delete(ref)
  }

  def deleteCopyDependent(e: E): Unit = {
    delete(e)
  }

  def update(e: E): Unit = {
    w("update")
    // reposition the entry if key/hash modified}
  }

  def updateCopy(e: E, primary: Idx[E]) {
    val ref = primary.get(e);
    delete(ref);
    unsafeInsert(e);
  }

  def updateCopyDependent(e: E, ref: E): Unit = {
    delete(ref)
    unsafeInsert(e)
  }

  def get(key: E): E = {
    w("get")
    null.asInstanceOf[E]
  }

  def getCopy(key: E): E = {
    val e = get(key)
    (if (e != null) e.copy else null).asInstanceOf[E]

  }

  def getCopyDependent(key: E): E = {
    val e = get(key)
    (if (e != null) e.copy else null).asInstanceOf[E]

  }

  def foreach(f: Function1[E, Unit]) = w {
    "foreach"
  }

  def foreachCopy(f: Function1[E, Unit]): Unit = {
    w("foreachCopy")
  }

  def foreachRes(): MultiRes = {
    //TODO: Fix later
    new ForEachRes[E](null.asInstanceOf[E])
  }

  def foreachResMap(f: Function1[E, Unit], res: MultiRes): Unit = {
    //TODO :Fix later
    foreach(f)
  }

  def slice(key: E, f: Function1[E, Unit]) = w("slice")

  def sliceCopy(key: E, f: Function1[E, Unit]) = w("sliceCopy")

  def sliceCopyDependent(key: E, f: Function1[E, Unit]) = sliceCopy(key, f)

  def sliceRes(key: E): MultiRes = {
    w("sliceRes"); null
  }

  def sliceResMapNoUpd(key: E, f: Function1[E, Unit], res: MultiRes): Unit = {
    w("sliceResMapNoUpd")
  }

  def range(min: E, max: E, withMin: Boolean, withMax: Boolean, f: Function1[E, Unit]): Unit = {
    w("range")
  }

  def clear(): Unit = {
    w("clear")
  }

  def compact(): Unit = {
    w("compact")
  }
  def hash(e1:E)=ops.hash(e1)
  def hashDiffers(e1: E, e2: E): Boolean = ops.hash(e1) != ops.hash(e2)

  def info: String = this.getClass.getName + "(" + idx + "," + (if (unique) "unique" else "multiple") + ")"
}

class IdxHashEntry[E <: Entry](var hash: Int, var data: E, var next: IdxHashEntry[E] = null, var prev: IdxHashEntry[E] = null) {
}

class IdxHash[E <: Entry](st: Store[E], idx: Int, unique: Boolean) extends Idx[E](st, idx, unique) {
  //TODO: Check if this would work
  private val init_capacity = 16
  private val max_capacity = 1 << 30
  private val compact_factor = 0.05f
  private var load_factor = 0.75f
  protected var data = new Array[IdxHashEntry[E]](init_capacity)
  protected var threshold = init_capacity * load_factor.round
  private val allowResize = true

  def _resize(): Unit = {
    //GS investigate why it cannot be protected
    val n = data.length
    if (n == max_capacity) threshold = Integer.MAX_VALUE
    else _resize(n * 10)
  }

  def _resize(new_capacity: Int): Unit = {
    //GS investigate why it cannot be protected
    val d = new Array[IdxHashEntry[E]](new_capacity)
    var i = 0

    while (i < data.length) {
      var e = data(i)
      var en = null.asInstanceOf[IdxHashEntry[E]]
      while (e != null) {
        en = e.next
        val b = (if (e.hash > 0) e.hash
        else -e.hash) % new_capacity
        e.next = d(b)
        if (d(b) != null) d(b).prev = e
        d(b) = e
        e.prev = null
        e = en
      }
      i += 1
    }
    data = d
    threshold = Math.min(new_capacity * load_factor.round, max_capacity + 1)
  }

  override def unsafeInsert(e: E): Unit = {
    if (size == threshold) {
      _resize()
      if (!allowResize) throw new IllegalStateException("Heap resize")
    }
    val h = ops.hash(e)
    val b = (if (h > 0) h else -h) % data.length
    if (idx == 0) {
      e.prev = null
      e.next = dataHead
      if (dataHead != null) dataHead.prev = e
      dataHead = e
    }

    val i = new IdxHashEntry[E](h, e)
    e.data(idx) = i
    i.next = data(b)
    if (data(b) != null) data(b).prev = i
    data(b) = i
    size += 1
  }

  protected def _del(e: E, i: IdxHashEntry[E]): Unit = {
    if (idx == 0) {
      val elemPrev = e.prev
      val elemNext = e.next
      if (elemPrev != null) elemPrev.next = elemNext
      else dataHead = elemNext
      if (elemNext != null) elemNext.prev = elemPrev
      e.next = null
      e.prev = null
    }
    val nxt = i.next
    val prv = i.prev
    if (prv != null) { //not head
      prv.next = nxt
      if (nxt != null) nxt.prev = prv
    }
    else if (nxt != null) { //head and has other elements
      i.hash = nxt.hash
      i.next = nxt.next
      if (nxt.next != null) nxt.next.prev = i
      i.data = nxt.data
      nxt.data.data(idx) = i
    }
    else { //head and the only element
      val h = i.hash
      val b = (if (h > 0) h
      else -h) % data.length
      if (data(b) eq i) data(b) = null
      else throw new IllegalStateException
    }
  }
  override def delete(e: E): Unit = {
    val i = e.data(idx).asInstanceOf[IdxHashEntry[E]]
    if (i != null) {
      _del(e, i)
      e.data(idx) = null
      size -= 1
    }
  }
  override def get(key: E): E = {
    val h = ops.hash(key)
    var e = data((if (h > 0) h else -h) % data.length)
    while (e != null && (e.hash != h || (ops.cmp(key, e.data) != 0))) e = e.next //TODO:don't know what's wrong here
    (if (e != null) e.data else null).asInstanceOf[E]
  }

  override def foreach(f: Function1[E, Unit]): Unit = {
    var cur = dataHead
    while (cur != null) {
      f.apply(cur.asInstanceOf[E])
      cur = cur.next
    }
  }

  override def slice(key: E, f: Function1[E, Unit]): Unit = {
    //val entries = collection.mutable.ListBuffer[E]()//Apparently ArrayList exists in Scala.js as well, but I was having trouble with it (But also set isn't working)
    val entries = new util.ArrayList[E]()
    if (idx == 0) { //Can't use primary hash fn for slice
      var e = dataHead
      while (e != null) {
        if (ops.cmp(key, e.asInstanceOf[E]) == 0) entries.add(e.asInstanceOf[E])
        e = e.next
      }
    }
    else {
      val h = ops.hash(key)
      var e = data((if (h > 0) h else -h) % data.length)
      if (e != null) do {
        if (e.hash == h && (ops.cmp(key, e.data) == 0)) entries.add(e.data)
        e = e.next
      } while (e != null)
    }
    //    for (e_ <- entries) {
    //      f.apply(e_)
    //    }
    while (entries.iterator().hasNext) {
      f.apply(entries.iterator().next())
    }
  }


  override def sliceRes(key: E): MultiRes =
    if (idx == 0) { //Can't use primary hash fn for slice
      throw new NotImplementedError("slice res not implemented for primary idx")
    }
    else {
      val h = ops.hash(key)
      var e = data((if (h > 0) h else -h) % data.length)
      if (e != null)
        do {
          if ((e.hash == h) && (ops.cmp(key, e.data) == 0)) return new SliceRes[E](e)
          e = e.next
        } while (e != null)
      new SliceRes[E](null)
    }


  override def sliceResMapNoUpd(key: E, f: Function1[E, Unit], res: MultiRes): Unit = {
    if (idx == 0) { //Can't use primary hash fn for slice
      throw new NotImplementedError("sliceresMapNoUpd not implemented for primary idx")
    }
    else {
      var e = res.asInstanceOf[SliceRes[E]].sliceHead
      val h = e.hash
      do {
        if ((e.hash == h) && (ops.cmp(key, e.data) == 0)) f.apply(e.data)
        e = e.next
      } while (e != null)
    }
  }

  override def clear(): Unit = {
    val z = null
    dataHead = null
    var i = 0
    val n = data.length
    while (i < n) {
      data(i) = z
      i += 1
    }
    size = 0
  }

}
