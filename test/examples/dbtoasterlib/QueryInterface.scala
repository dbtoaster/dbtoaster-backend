import scala.actors.Actor
import scala.actors.Actor._
import xml._

package org.dbtoaster.dbtoasterlib {
	object QueryInterface {
		trait DBTMessageReceiver {
			def onTupleProcessed(): Unit
			def onQueryDone(): Unit
		}

		case object DBTTupleProcessed
		case object DBTDone

		class QuerySupervisor(query: DBTQuery, msgRcv: DBTMessageReceiver) extends Actor {
			def act() {
      			query.setSupervisor(this)
				query.start
			
				while(true) {
					receive {
						case DBTDone => { 
							msgRcv.onQueryDone()
							exit()
						}
						case DBTTupleProcessed => {
							msgRcv.onTupleProcessed()
						}
					}
				}
			}
		}

		trait DBTQuery extends Actor {
			def setSupervisor(supervisor: Actor): Unit
		}

		class DBTTimer(name: String) {
			var t = 0L
			var nesting = 0

			def print(): Unit = {
				println(new PrettyPrinter(8000, 2).format(<xml>{t / 1000000000.0}</xml>.copy(label = name)))
			}

			def sampledTime(): Long = {
				val samples = 10
				var tm = 0L
				for(i <- 1 to samples) 
				   tm += System.nanoTime
				tm / samples
			}

			def time[T](f: => T): T = {
				val start = System.nanoTime
				nesting += 1
				val r = f
				nesting -= 1
				if(nesting == 0)
					t += System.nanoTime - start
				r
			}
		}
	}
}