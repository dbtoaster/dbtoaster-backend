package ddbt.tpcc.loadtest.load

import java.util.Arrays
import java.util.Date
import scala.beans.{BeanProperty, BooleanBeanProperty}

/**
 * Simple object to represent a single row of data being loaded to the database (or written to a CSV file).
 */
class Record(columnCount: Int) {

  /**
   * Column values.
   */
  @BeanProperty
  val field = new Array[Any](columnCount)

  /**
   * Index of next column to write value to.
   */
  private var index: Int = 0

  /**
   * Re-usable buffer for building string representations of the row.
   */
  private val toStringBuilder = {
    val str = new StringBuilder("[")
    var i = 0;
    while( i < index ) {
      str.append(field(i))

    }
    str.append("]")
  }

  def reset() {
    index = 0
  }

  def add(value: Any) {
    field(index) = value
    index += 1
  }

  def getField(i: Int): Any = field(i)

  def getColumnCount(): Int = field.length

  override def toString(): String = Arrays.toString(field.asInstanceOf[Array[Object]])
}
