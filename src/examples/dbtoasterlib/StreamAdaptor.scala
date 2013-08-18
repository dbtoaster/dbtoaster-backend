import java.io.InputStream
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._
import scala.util.Random
import scala.collection.mutable.Map
import java.text.SimpleDateFormat

package org.dbtoaster.dbtoasterlib {
/**
 * This object contains the differen stream adaptors supported
 * by DBToaster
 *
 */
object StreamAdaptor {
    /**
     * The type of an orderbook stream adaptor
     */
    abstract trait OrderbookType
    
    /**
     * The adaptor looks for asks
     *
     */
    case object Asks extends OrderbookType
    
    /**
     * The adaptor looks for bids
     */
    case object Bids extends OrderbookType

    /**
     * Describes the type of an event
     */
    abstract trait EventType
    
    /**
     * Insertion of a tuple
     */
    case object InsertTuple extends EventType
    
    /**
     * Deletion of a tuple
     */
    case object DeleteTuple extends EventType
    
    /**
     * This type of event is fired only once when 
     * the system has been initialized
     */
    case object SystemInitialized extends EventType

    /**
     * Describes the type of a column
     */
    abstract trait ColumnType
    case object IntColumn extends ColumnType
    case object FloatColumn extends ColumnType
    case object OrderColumn extends ColumnType
    case object DateColumn extends ColumnType
    case object StringColumn extends ColumnType

    /**
     * An DBToaster event
     */
    abstract trait DBTEvent
    
    /**
     * A stream event representing some data that has been updated
     */
    case class StreamEvent(eventType: EventType, order: Long, 
                           relation: String, vals: List[Any])
      extends Ordered[StreamEvent] with DBTEvent {
      def compare(other: StreamEvent) = other.order.compareTo(this.order)
    }
    
    /**
     * This event is generated when there is no more tuples on
     * this stream
     */
    case object EndOfStream extends DBTEvent

    /**
     * Creates an adaptor from the parameters passed
     * 
     * @param adaptorType The type of the adaptor
     * @param relation The relation that the adaptor belongs to
     * @param params The paramaters for the adaptor
     * @return The created adaptor
     */
    def createAdaptor(adaptorType: String, relation: String, 
                      params: List[(String, String)]): StreamAdaptor = {
      adaptorType match {
        case "orderbook" => createOrderbookAdaptor(relation, params)
        case _ => throw new IllegalArgumentException(
                                "No adaptor for: " + adaptorType)
      }
    }

    /**
     * Creates an orderbook stream adaptor
     * 
     * @param relation The relation that the adaptor belongs to
     * @param params The parameters for this adapter
     * @return The created orderbook adaptor
     */
    def createOrderbookAdaptor(relation: String, 
                params: List[(String, String)]): OrderbookAdaptor = {
      // Standard values for the parameters
      var orderbookType: OrderbookType = Asks
      var brokers: Int = 10
      var deterministic: Boolean = false
      var insertOnly: Boolean = false

      def parseParams(params: List[(String, String)]): 
               OrderbookAdaptor = params match {
        case x :: xs =>
          x match {
            case ("book", b) => orderbookType = if (b == "bids") Bids else Asks
            case ("brokers", n) => brokers = n.toInt
            case ("deterministic", b) => deterministic = (b == "yes")
            case ("insertOnly", b) => insertOnly = (b == "yes")
          }
          parseParams(xs)
        case Nil => new OrderbookAdaptor(relation, orderbookType, 
                                         brokers, deterministic, 
                                         insertOnly)
      }

      parseParams(params)
    }

    /**
     * Abstract definition of a stream adaptor
     *
     */
    abstract class StreamAdaptor {
      /**
       * Processes some row and generates events
     * @param row The row
     * @return The list of events generated based on the row
     */
    def processTuple(row: String): List[StreamEvent]
    }

    /**
     * This adaptor parses CSV data
     *
     */
    class CSVAdaptor(relation: String, schemaTypes: List[ColumnType], 
                     eventtype: String = "insert", deletions: String = "false",
                     schema: String = "", delimiter: String = ",") 
                     extends StreamAdaptor {
      val eventType = if (eventtype == "insert") InsertTuple else DeleteTuple
      val hasDeletions = (deletions == "true")
      val dateFormatParser = new SimpleDateFormat("yyyy-MM-dd")
      
      def parseColType(col: String): ColumnType = {
        col match {
          case "int" => IntColumn
          case "float" => FloatColumn
          case "order" => OrderColumn
          case "date" => DateColumn
          case "hash" => StringColumn
          case "string" => StringColumn
        }
      }

      val colTypes: Array[ColumnType] = 
        if(schemaTypes.isEmpty) 
          schema.split(",").map(x => parseColType(x)) 
        else
          schemaTypes.toArray

      def processTuple(row: String): List[StreamEvent] = {
        val cols = row.split(delimiter)

        val (valCols, insDel, order) = (if (hasDeletions) {
          (cols.drop(2), (if (cols(1) == "1") InsertTuple 
                          else DeleteTuple), cols(0).toInt)
        } else (cols, eventType, 0))

        val vals2: Array[Any] = (valCols, colTypes).zipped.map {
          case (v, t) =>
            t match {
              case IntColumn => v.toLong
              case FloatColumn => v.toDouble
              case OrderColumn => v.toLong
              case DateColumn => dateFormatParser.parse(v)
              case StringColumn => v
              case _ => v
            }
        }
        val vals3 = vals2.toList
        val vals = List[Any]()
        List(StreamEvent(insDel, order, relation, vals3))
      }
    }

    /**
     * This adaptor parses orderbook data
     *
     */
    class OrderbookAdaptor(relation: String, orderbookType: OrderbookType,
                           brokers: Long, deterministic: Boolean, 
                           insertOnly: Boolean) extends StreamAdaptor {
      val asks: Map[Long, OrderbookRow] = Map()
      val bids: Map[Long, OrderbookRow] = Map()

      case class OrderbookRow(t: Long, id: Long, brokerId: Long, 
                              volume: Double, price: Double) {
        def toList: List[Any] = List[Any](t.toDouble, id, brokerId, 
                                          volume, price)
      }

      def processTuple(row: String): List[StreamEvent] = {
        val rows = row.split(",")
        val t = rows(0).toLong
        val id = rows(1).toLong
        val volume = rows(3).toDouble
        val price = rows(4).toDouble

        rows(2) match {
          case "B" if orderbookType == Bids => {
            val brokerId = (if (deterministic) id 
                            else Random.nextInt) % brokers
            val row = OrderbookRow(t, id, brokerId, volume, price)
            bids += ((id, row))
            List(StreamEvent(InsertTuple, t, relation, row.toList))
          }

          case "S" if orderbookType == Asks => {
            val brokerId = (if (deterministic) id 
                            else Random.nextInt) % brokers
            val row = OrderbookRow(t, id, brokerId, volume, price)
            asks += ((id, row))
            List(StreamEvent(InsertTuple, t, relation, row.toList))
          }

          case "E" => {
            // TODO: Make code more readable/maintainable
            bids.get(id) match {
              case Some(x @ OrderbookRow(_, id, b, v, p)) => {
                val newVolume = v - volume

                List(StreamEvent(DeleteTuple, t, relation, x.toList)) :::
                  (if (newVolume <= 0.0) { bids -= id; Nil }
                  else {
                    val newRow = OrderbookRow(t, id, b, newVolume, p)
                    bids += ((id, newRow))
                    List(StreamEvent(InsertTuple, t, relation, newRow.toList))
                  })
              }
              case None => asks.get(id) match {
                case Some(x @ OrderbookRow(_, id, b, v, p)) => {
                  val newVolume = v - volume

                  List(StreamEvent(DeleteTuple, t, relation, x.toList)) :::
                    (if (newVolume <= 0.0) { asks -= id; Nil }
                    else {
                      val newRow = OrderbookRow(t, id, b, newVolume, p)
                      asks += ((id, newRow))
                      List(StreamEvent(InsertTuple, t, relation, 
                                       newRow.toList))
                    })
                }
                case None => Nil
              }
            }
          }

          case "D" | "F" => {
            bids.get(id) match {
              case Some(x) => { bids -= id; 
                                List(StreamEvent(DeleteTuple, t, 
                                                 relation, x.toList)) }
              case None => asks.get(id) match {
                case Some(x) => { asks -= id; 
                                  List(StreamEvent(DeleteTuple, t, 
                                                   relation, x.toList)) }
                case None => Nil
              }
            }
          }

          case _ => Nil
        }
      }
    }
  }
}
