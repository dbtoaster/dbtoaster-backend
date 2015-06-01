package ddbt.lib.store
import scala.reflect._

import ddbt.Utils.ind
import scala.collection.mutable.HashMap

class Container[E<:Entry]()(implicit cE:ClassTag[E])
