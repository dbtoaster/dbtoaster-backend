package ddbt.codegen
import ddbt.ast._

/**
 * AkkaGen is responsible to transform a typed AST into distributed Akka code.
 * The main difference with ScalaGen is that every closure (i.e. the body of
 * foreach loops and add/set operations need to be distributed:
 *
 * Add/Set: the corresponding message op(key,value) is sent to the owner
 * of the map's partition
 *
 * Void closures: (closures with no return) the message CID(var1, var2, .. varN)
 * is broadcasted, where CID is the unique closure id and var1..varN are the
 * context variables at the point of call. CID encodes (map,slicing,continuation).
 * - At calling site: broadcast the message
 * - At workers receive: add a special handler for the message that is the
 *   iterating over the local portion of the map/slice and executing the continuation
 *   after the context variables var1..varN have been bound.
 *
 * Modifying closures (aggregate, group by, fetch map): two messages (forward and
 * result reply need to be created: one at workers and the other only at sender
 * (that is workers+master/master only or workers only depending where the call
 * happens).
 * - At workers: the continuation needs to create a return variable (aggregate,
 *   group) in it and reply to its parent with the result once the continuation
 *   has produced its result.
 * - At caller: the caller must register locally a special aggregation continuation
 *   that will be executed when it received _exactly_ N responses (where N is the
 *   number of nodes in the cluster.
 *
 * @author TCK
 */
class AkkaGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._

/*
Little problems to solve:
1. multiple queries => GetSnapshot(Int)
2. system I/O: returns (time,List[Map[_,_]])
3. cluster initialization and maps distribution => workers tell master they want to join with their maps (all local but null maps)

4. join and leave cluster => just output message
*/


// 1. before each statement, add pre computation
// 2. at each foreach point, transform into a remote continuation, possibly with a local aggregation continuation

/*
  map messages
  map master triggers
  map worker continuations triggers
*/
/*
  def genRemote(e:Expr,ctx:Map[String,Type],co:String=>String) // this is the only thing we need to insert ?
  def genExpr(e:Expr,co:Continuation)
  def genWorker
*/

/*

From ScalaGen, methods to modify
- respond to more events (receive method)
- cpsExpr to support remote continuations
- Tag continuations with 'needs to respond to sender' when needed

- Generate 2 classes:
  - Master, handles global events streams
  - Workers: only handle internal messages

- Declare all messages/types in some common place

- Generate coherency information with list of read(option) and written(list) maps

==> move lazy map slicing into the TypeChecking ?

- move a good part of the test generator directly in the code generator
- move test AST into ddbt.ast package ?


*/

  override def apply(s:System) = "// unimplemented"
  override def helper(s:System,numSamples:Int=10) = "// helper"
}
