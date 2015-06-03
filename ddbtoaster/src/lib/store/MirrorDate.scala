package ddbt.lib.store

/**
 * Created by khayyam on 4/9/15.
 */
import ch.epfl.data.sc.pardis.annotations._

@needs[Numeric[_]]
@deep
@noImplementation
@reflect[java.util.Date]
class MirrorDate(longValue: Long) {
  def getTime(): Long = ???
}
