package ddbt.lib

/** Stream event messages sent by sources to the system. */
object Messages {
  // Tuple operations
  type TupleOp = Byte
  final val TupleDelete : TupleOp = 0x00
  final val TupleInsert : TupleOp = 0x01

  abstract sealed class StreamEvent
  case class TupleEvent(op:TupleOp,stream:String,data:List[Any]) extends StreamEvent // XXX: stream name as Byte/Int(hashCode?)
  case object SystemInit extends StreamEvent
  case object EndOfStream extends StreamEvent // get snapshot(0) and shut the system down
  case class GetSnapshot(view:Int) extends StreamEvent // request a snapshot of some maps
}
