package ddbt.lms.oltp.opt.lifters

object SEntryGen {
  def main(args: Array[String]): Unit = {
  	val out = new StringBuilder
    for(i <- 2 to 22) {
    	out.append(genSEntryClass(i)).append('\n')
    }
    for(i <- 2 to 22) {
    	out.append(genSEntry2Tuple(i)).append('\n')
    }
    println(out.toString)
  }
  def genTemplate1(begin:Int, end:Int, template:String) = (begin to end).map(template.format(_)).mkString(",") 
  def genTemplate2(begin:Int, end:Int, template:String) = (begin to end).map{x => template.format(x,x)}.mkString(",") 
  def genSEntryClass(i:Int) = "abstract class SEntry%d[%s] extends SEntry[(%s)]".format(i, genTemplate1(1,i,"T%d:Manifest"), genTemplate1(1,i,"T%d"))
  def genSEntry2Tuple(i:Int) = ("  implicit def conv2SEntry%d[%s](x: Rep[SEntry%d[%s]])(implicit pos: SourceContext) =\n" +
  "    (%s)").format(i, genTemplate1(1,i,"T%d:Manifest"), i, genTemplate1(1,i,"T%d"), genTemplate2(1,i, "x.get(unit(%d)).asInstanceOf[Rep[T%d]]"))
}