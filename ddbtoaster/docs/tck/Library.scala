package ddbt
import ddbt.ast._

/*
 * This component exposes user library methods signature to the type checker and
 * code generator (eventually also of the current runtime class/object). The
 * concern of referencing / inlining is the responsibility of code generator:
 * 1. Duplicate the runtime library with Rep[T] types
 * 2. Map Apply() into these functions
 *
 * @author TCK
 */
object Library {
  import java.lang.reflect.Modifier._

  // available functions as userName->(callName,retType,minArgs,argTypes)
  // default argument <i> of <f> is a val named <f>$default$<i> where i=1,2,3...
  private val funs = new java.util.HashMap[String,(String,Type,List[Type])]() 
  private val argm = new java.util.HashMap[String,Int]() // min # of arguments
  def typeof[T](c:Class[T]) = c.toString match {
    case /*"char"|"short"|"int"|*/ "long" => TypeLong
    case /*"float"|*/ "double" => TypeDouble
    case "class java.lang.String" => TypeString
    case "class java.util.Date" => TypeDate
    case _ => null
  }

  def inspect[T](obj:T, namePrefix:String=null, callPrefix:String=null) {
    val c = obj.getClass
    val ms0 = c.getMethods.filter(m=>(m.getModifiers()&PUBLIC)!=0);
    val ms = if (namePrefix!=null) ms0.filter{m=>m.getName.startsWith(namePrefix)} else ms0
    ms.foreach { m =>
      val rt = typeof(m.getReturnType)
      val at = m.getParameterTypes.toList.map(a=>typeof(a))
      if (rt!=null && !at.contains(null)) {
        val n = m.getName
        val un = if (namePrefix!=null) n.substring(namePrefix.length) else n
        val cn = if (callPrefix!=null) callPrefix+ "" +n else n
        val p = un.indexOf("$default$")
        if (p == -1) funs.put(un,(cn,rt,at))
        else { // min #arguments required for this function = min(in-1) forall in
          val (fn,i) = (un.substring(0,p),un.substring(p+9).toInt-1)
          argm.put(fn,if (!argm.containsKey(fn)) i else Math.min(argm.get(fn),i))
        }
      }
    }
  }
  
  def typeCheck(name:String,as:List[Type]):Type = {
    if (!funs.containsKey(name)) sys.error("Library: no such function: "+name)
    val f = funs.get(name)
    val an = as.size
    val amax = f._3.size
    val amin = if (argm.containsKey(name)) argm.get(name) else amax
    if (an<amin || an>amax) sys.error("Library: bad number of arguments: got "+an+", expected ["+amin+","+amax+"]")
    if (argm.containsKey(name) && as.size<argm.get(name) || as.size!=f._3.size) 
    (as zip f._3).zipWithIndex.foreach { case ((t1,t2),i) => if (t1!=t2) sys.error("Library: argument "+i+" of "+name+" must be a "+t2) }
    f._2
  }
  
  // Used by the CodeGen to map language function into Java (object+)function name
  def apply(name:String) = funs.get(name)._1
  
  def clear() { funs.clear; argm.clear; inspect(ddbt.lib.Functions,"U") }
  clear

  // LMS should reuse this function such that we can inline library functions
  // manually here, based on arbitrary decision (possibly inlining function
  // available in the user function library class.
  /*
  def Isubstring(vs:List[String]) = vs(0)+".substring("+vs(1)+(if (vs.size>2) ","+vs(2) else "")+")"
  def codeGen(name:String,vs:List[String]):String = {
    // XXX: say for which codegen you want : scala / C/C++?
    try {
      val m = libClass.getDeclaredMethod("I"+name, classOf[List[String]])
      assert(m.getReturnType==classOf[String]); m.invoke(libObj,vs).asInstanceOf[String]
    } catch { case _:Throwable => funs.get(name)._1+"("+vs.mkString(",")+")" }
  }
  */

  def main(args:Array[String]) {
    println("Library content:")
    
    println(typeCheck("substring",List(TypeString,TypeLong)))
    //println(codeGen("substring",List("foo","123")))
    
    
    //println(ddbt.lib.Functions.Usubstring("foo",ddbt.lib.Functions.Usubstring$default$2))
    
    import collection.JavaConversions._
    funs.toMap.foreach { case (k,v) => println("%-15s".format(k)+" -> "+v+" min="+argm.get(k)) }
  }
}

// Annotations: http://www.veebsbraindump.com/2013/01/reflecting-annotations-in-scala-2-10/
// But it seems we can only annotate classes, not methods => cannot implement arbitrary renaming from libs
