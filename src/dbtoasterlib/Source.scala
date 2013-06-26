import java.util.Scanner
import java.io._
import scala.collection.mutable.Queue
import scala.collection.mutable.PriorityQueue
import scala.collection.mutable.Map
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._
import org.dbtoaster.dbtoasterlib.StreamAdaptor._
import scala.actors.Actor
import scala.actors.Actor._

package org.dbtoaster.dbtoasterlib {
  /**
   * This object contains the implementation for sources which emit tuples
   *
   */
  object Source {
    /**
     * Description of which framing type is being used
     *
     */
    abstract class FramingType
    case class FixedSize(len: Int) extends FramingType
    case class Delimited(delim: String) extends FramingType

    case class EventMessage(s: Source, e: DBTEvent)

    /**
     * Abstract definition of a Source
     */
    abstract class Source() extends Actor {
      /**
       * Initializes the source
       */
      def init(receiver: Actor): Unit

      /**
       * Checks whether a source has more input
       * @return True if there is more input, false otherwise
       */
      def hasInput(): Boolean

      /**
       * Returns the next event of this source
       * @return The next event
       */
      def nextInput(): DBTEvent

      /**
       * Do something for all events of this source
       *
       * Note: this is used to fill static tables
       *
       * @param f The function that should be applied to all events
       */
      def forEachEvent(f: DBTEvent => Unit): Unit = {
        val event = nextInput()
        event match {
          case StreamEvent(_, _, _, _) => f(event); forEachEvent(f)
          case EndOfStream => ()
        }
      }
    }

    /**
     * Returns a source from an input stream
     *
     * @param in The input stream
     * @param adaptors The adaptors that use this source
     * @param framingType The framing type that should be used
     * @return The source
     */
    def createInputStreamSource(in: InputStreamReader, 
                                adaptors: List[StreamAdaptor],
                                framingType: FramingType) = {
      framingType match {
        case Delimited(delim) => DelimitedStreamSource(in, adaptors, delim)
        case _ => throw new DBTNotImplementedException(
                    "Framing type not supported (yet): " + framingType)
      }
    }

    /**
     * Reads events from an InputStream, assumes that the events are ordered
     *
     */
    case class DelimitedStreamSource(in: InputStreamReader, 
                                     adaptors: List[StreamAdaptor], 
                                     delim: String) extends Source {
      val eventQueue = new Queue[StreamEvent]()
      val scanner: Scanner = new Scanner(in).useDelimiter(delim)
      var recvr: Actor = null;

      def init(receiver: Actor): Unit = {
        recvr = receiver
      }

      def hasInput(): Boolean = scanner.hasNextLine() || !eventQueue.isEmpty

      def nextInput(): DBTEvent = {
        if (eventQueue.isEmpty && scanner.hasNextLine()) {
          val eventStr: String = scanner.nextLine()
          adaptors.foreach(adaptor => 
            adaptor.processTuple(eventStr).foreach(x => eventQueue.enqueue(x)))
        }

        if (eventQueue.isEmpty)
          EndOfStream
        else
          eventQueue.dequeue()
      }

      def act() {
        while(scanner.hasNextLine()) {
          val eventStr: String = scanner.nextLine()

          adaptors.foreach(adaptor => 
            adaptor.processTuple(eventStr).foreach(x => recvr ! EventMessage(this, x)))
        }

        recvr ! EventMessage(this, EndOfStream)
      }
    }

    /**
     * Multiplexes a list of sources while preserving the order of events 
     * (assuming that the sources themselves are ordered)
     *
     */
    class SourceMultiplexer(query: Actor, sources: List[Source]) extends Actor {
      var counter = 0
      val queues: Map[Source, PriorityQueue[StreamEvent]] = 
        Map() ++= sources.map(x => (x, PriorityQueue[StreamEvent]()))
      val queueDone: PriorityQueue[StreamEvent] = PriorityQueue()
      var currMax = 0L

      def sendEvent(): Unit = {
        if(queues.isEmpty) {
          queueDone.foreach(e => query ! e)
          query ! EndOfStream
          exit()
        }
        else if(queues.forall { case (_, q) => !q.isEmpty }) {
          val minQueues = (queues.values ++ (
            if(queueDone.isEmpty) 
              List() 
            else 
              List(queueDone))).reduceLeft((a, b) => 
                if(a.head.order < b.head.order) a else b)
          
          val r = minQueues.dequeue

          // Check the ordering of tuples
          if(r.order >= currMax)
            currMax = r.order
          else if(r.order < currMax)
            throw new DBTFatalError("Ordering not correct: " + r.order + " < " + currMax)

          query ! r
        }
      }

  	  def act() {
        if(sources.isEmpty) {
          query ! EndOfStream
          exit() 
        }

        sources.foreach(x => { x.init(this); x.start })

  		  while(true) {
          receive {
            case EventMessage(s, EndOfStream) => {
              queueDone ++= queues(s)
              queues -= s
              sendEvent
            }
            case EventMessage(s, e: StreamEvent) => {
              queues(s).enqueue(e)
              sendEvent
            }
          }
  			}
  		}
    }
  }
}