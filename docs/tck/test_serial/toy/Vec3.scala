object Loader {
  val libs = new scala.collection.mutable.HashSet[String]()
  val paths = (this.getClass.getClassLoader match {
    case ctx: java.net.URLClassLoader => ctx.getURLs.map(_.getPath)
    case _ => System.getProperty("java.class.path").split(":")
  }).reverse.toList

  def load(lib:String) {
    def ld(pl:List[String]):Unit = pl match {
      case p::ps => val f = new java.io.File(p+"/lib"+lib+".jnilib")
        if (f.exists) System.load(f.getCanonicalPath()) else ld(ps);
      case Nil => throw new Exception("JNI Library "+lib+" not found");
    }
    if (! libs.contains(lib)) { ld(paths); libs+=lib; }
  }
}

class Vec3(val x:Int, val y:Int, val z:Int) {
  Loader.load("Vec3")

  def +:(v: Vec3) = new Vec3(x+v.x,y+v.y,z+v.z)
  def -:(v: Vec3) = new Vec3(x-v.x,y-v.y,z-v.z)
  override def toString() = "("+x+","+y+","+z+")"
  @native def dot(v: Vec3):Vec3; //= new Vec3(x*v.x,y*v.y,z*v.z)
}
