package ddbt.lib

/** Stream event messages sent by sources to the system. */
object Messages {
  // Tuple operations
  type TupleOp = Byte
  final val TupleDelete : TupleOp = 0x00
  final val TupleInsert : TupleOp = 0x01

  abstract sealed class StreamEvent
  case class TupleEvent(op:TupleOp,stream:String /*=>Byte/Int(hashCode?)*/ ,tx:Long /*XXX:UNUSED!!!*/ ,data:List[Any]) extends StreamEvent
  case object EndOfStream extends StreamEvent
  case object SystemInit extends StreamEvent
  case object GetSnapshot extends StreamEvent // similar as EndOfStream but does not shut system down
  // XXX: case object CollectMap(m:MapRef) extends SystemEvent
}
