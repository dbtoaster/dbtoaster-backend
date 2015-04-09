package ddbt.lib.store

/**
 * Created by khayyam on 4/9/15.
 */
import ch.epfl.data.pardis.annotations._

@needs[Long]
@deep
@noImplementation
@reflect[java.util.Date]
class MirrorDate(longValue: Long) {
  def getTime(): Long = ???
}
