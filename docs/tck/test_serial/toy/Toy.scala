object Toy {
  def main(args: Array[String]) {
    val a = new Vec3(1,2,3)
    val b = new Vec3(3,2,1)
    val c = a.dot(b)
    System.out.println(c);
  }
}
