package ddbt.lib
//import akka.actor.ActorRef

object Messages {
  // Tuple operations
  type TupleOp = Byte
  final val TupleDelete : TupleOp = 0x00
  final val TupleInsert : TupleOp = 0x01
  
  // Input stream
  abstract sealed class StreamEvent
  case object EndOfStream extends StreamEvent
  case class TupleEvent(op:TupleOp,stream:String,tx:Long,data:List[Any]) extends StreamEvent

  // System messages
  abstract sealed class SystemEvent
  case object SystemInit extends SystemEvent
  case object GetResult extends SystemEvent
}

/**

ARCHITECTURE OVERVIEW (push-based flow)
---------------------------------------------------

                  Source (streams)
                     |
                     v      
Supervisor <---> Serializer -----> Storage
    ^          (broadcasting) <--- (setup tables)
    |                |
    |                v
    |             /+-+-+\
    |            / | | | \
    +---------- W W W W W Workers (partitioned)
                 \ | | | /
                  \+-+-+/
                     |
                     v
                  Display (query result)


The SOURCE represents the input stream, conceptually external to the system. It
could be: reading a file or receiving binary data from the network.

The SERIALIZER is the entry point all messages to the system. Its only duty is
to serialize and broacast all messages it receive: from source and from other
nodes that need to communicate.

The STORAGE has two roles:
- storage (database) for static relations (used at initialization)
- traditional database (preferably: compactness, easy recovery) or (WAL) log
  storing the stream. Purpose: recover from nodes crash, if necessary. 

The work is distributed to WORKERS that are responsible for processing the tuple
applying the deltas it generates to their local storage and exchange messages
with peers, if the peer computation requires their internal state. More
specifically, each node compute foreach modified map whether they own the slice
in which modification should happen. If:
- Yes: compute the delta, possibly waiting data from other nodes
- No : find owner, send it all _aggregated_ data related to modification

Example: SELECT COUNT(*) FROM R,S where R.r=S.s ==> maps mCOUNT,mR(r),mS(s)
	Assume 2 workers W1,W2 partitionned using modulo 2 on id, and mCOUNT on W1.
	When tuple <serial,+R(3)> arrives, owner=W1: mR is updated on W1.
	To compute mCOUNT+=1[R(3)]*COUNT(mS),
	- W1 does 1[R(3)]*COUNT(mS%2==1) and wait data from W2
	- W2 detects that its map is used, compute 1[R(3)]*COUNT(mS%2==0) and sends
	  it to W1
	- W1 receive data from W2, completes its computation and update mCOUNT
The key here is to notice that since W1,W2 receive +R(3), they can pre aggregate
locally before agregating between nodes.

The DISPLAY is the receiver of the query maps, these can be send by all workers
whenever requested (request message needs to go through serializer).

Finally the SUPERVISOR coordinates all the nodes by handling failures and
checkpointing. To do that, all system messages are passed to the serializer.
This guarantees a coherent snapshot of the system.

FAULT TOLERANCE
---------------------------------------------------
Gap property: the application can sustain a gap in the stream without affecting
too much the result. Gap can be measured in time, #tuples, relative size, ...

Checkpointing: broadcast message for all workers and storage
- Workers write their map to permanent local storage.
- Storage as relations: make a snapshot (lock tables, ...)
- Storage as stream: if checkpoiting succeeds, discard stream up to check point

Failures
- Serializer fails: system waits for recovery. If the source does not enqueue
  messages and not Gap, system is stale and need to be reset.
- Storage fails: recovery of system becomes impossible.
  When detected, if has Gap property and worth it checkpoint (else useless).
- Supervisor or display fails: does not affect computation
- Worker fails: if Gap property or system could sustain a burst 
  1. Enqueue all message at serializer
  2.a If storage holds the stream
      - Restore worker from its stable storage (tx_old)
      - Replay the stream (tx_old->tx_current) with help of storage and coworkers
  2.b If storage holds the relations
      - Recompute all the maps from the relations (we do not need local storage here)     
  3. Release queue at serializer (burst), continue processing

**/

  // ---------- Operations on tuples
  // case class TupleTransfer extends TupleOp // exchange tuple between two workers

// ---------- Message passed between nodes


/*
abstract sealed class Msg 
// Data
case object MsgEndOfStream extends Msg
case class MsgTuple(op:TupleOp,tx:Long,data:List[Any]) extends Msg
//case class MsgEndOfTrx(tx:Long,s:Long) extends Msg // all tuples have been exchanged between two workers for the sth statement of transaction tx
//case class MsgBulk(op:TupleOp,tx:Long,s:Long,data:List[List[Any]]) extends Msg // bulk transfer between two workers

// System
case object MsgNodeUp extends Msg    // worker is initialized
case object MsgNodeReady extends Msg // worker has received all tables content
case object MsgNodeDone extends Msg  // worker has received end of stream from all its sources
case class MsgState(num:Long,mem:Long) extends Msg // worker status (#processed tuples, memory usage)
case class MsgRate(state:Long,view:Long) extends Msg // how often nodes send state (to supervisor) and result (to display)
// case class MsgCheckpoint extends Msg
*/
// ----------

/*
Input
InputFile
InputPort
--->
Delimiter (line, separator, fixed-size, prefix-size)

abstract class Adaptor
case class AdaptorCSV extends Adaptor
case class AdaptorOrderbook extends Adaptor

-- multiplexed -->

in a single actor
*/
