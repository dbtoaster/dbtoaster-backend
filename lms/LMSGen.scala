package ddbt.codegen
import ddbt.ast._

case class LMSGen(cls:String="Query") extends (M3.System => String) {
  def apply(sys:M3.System) = "implemented"
}
