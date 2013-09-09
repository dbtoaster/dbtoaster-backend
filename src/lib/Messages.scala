package ddbt.lib

/** Stream event messages sent by sources to the system. */
object Messages {
  // Tuple operations
  type TupleOp = Byte
  final val TupleDelete : TupleOp = 0x00
  final val TupleInsert : TupleOp = 0x01

  // Input stream
  abstract sealed class StreamEvent
  case object SystemInit extends StreamEvent
  case object EndOfStream extends StreamEvent
  case object GetSnapshot extends StreamEvent // similar as EndOfStream but does not shut system down
  case class TupleEvent(op:TupleOp,stream:String,tx:Long,data:List[Any]) extends StreamEvent
  // XXX: CollectMap(m:MapRef)
}
