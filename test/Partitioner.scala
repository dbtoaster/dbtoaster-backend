package ddbt.test
import ddbt.frontend._

object Partitioner {
  import ddbt.Utils._
  def main(args: Array[String]) {
    // Dirty front-end
    if (path_repo==null) return printf("DBT repository must be configured.")
    if (args.size<1) return printf("Usage: ddbt.Parititoner <query_pattern>")
    val qs = exec(Array("find","test/queries","-type","f","-and","-not","-path","*/.*"),new java.io.File(path_repo))._1.split("\n").filter(x=>x.matches(".*"+args(0)+"(\\.sql)?")).sorted
    if (qs.size==0) return printf("No query selected, relax your pattern")
    qs.foreach{ q =>
      println("------ "+q)
      val m3_src = ddbt.Compiler.toast("m3",q)._2
      val m3 = (M3Parser andThen TypeCheck)(m3_src)
      val (p,h)=Partitioning(m3)
      println(p)
      //println(h)
    }
  }
}

/*
 * Idead of new algorithm:
 * 1. Detect pairwise co-partitioning pairs, and count them
 * 2. Group non-colliding co-partitioning
 * 3. Key reduction: duplicate-reduce all multi-key co-partitioning
 * 4. We obtain several cluster of co-partitioning. For all cluster in descending order:
 *    - Find conflicting subset with next cluster << THIS IS PRETTY HARD AND MIGHT SPLIT IN 2 DISJOINT PARTS THE CLUSTER
 *      and compare benefit of replacing subset with next cluster
 *    - If so, swap subset and next cluster and continue
 *    - Group disjoint co-clusters
 *    - Repeat until the list has not changed
 * 5. Cleanup: reduce the following co-partitions (unique map partitioning)
 * 6. To find if co-partitioned
 *    - State = paritioning set + current map + current partitioning key's names
 *    - If next map in the same set and the corresponding keys are matching, then we keep in the same set, otherwise non local and change set
 */
