import java.lang.reflect.Constructor;

public class T {
  public static void main(String[] args) throws Exception {
    doRegular(); doReflection();
    doRegular(); doReflection();
    doRegular(); doReflection();
    doRegular(); doReflection();
    doRegular(); doReflection();
  }

  public static void doRegular() throws Exception {
    long start = System.nanoTime();
    for (int i=0; i<1000000; i++) {
        new X().nop();
    }
    System.out.println("Regular: "+(System.nanoTime() - start));
  }

  public static void doReflection() throws Exception {
    long start = System.nanoTime();
    Class<X> cl = X.class;
    //Constructor<X> co = (Constructor<X>)(cl.getConstructor(Object.class));
    for (int i=0; i<1000000; i++) {
        cl.newInstance().nop();
    }
    System.out.println("Reflect: "+(System.nanoTime() - start));
  }

}

class X {
  public static int ctr=0;
  public X() {}
  public X(Object o) { }
  public void nop() { ctr+=1; }
}
