package ddbt.test
import org.scalatest._
import java.io._

/** These tags are used to mark tests with specific features */

// To run all but tests tagged slow
// sbt 'test-only * -- -l ddbt.SlowTest'
object SlowTest extends Tag("ddbt.SlowTest")
