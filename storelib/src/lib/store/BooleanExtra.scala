package ddbt.lib.store

/**
  * Created by sachin on 22.04.16.
  */
trait BooleanExtra
object BooleanExtra{
  def conditional[T](cond: Boolean, ift :T , iff: T) = if(cond) ift else iff
}