package ddbt.test.cperf;
import java.util.*;
import scala.Tuple2;
import scala.Tuple3;

class HashMapOld {
  static Random r = new Random();
  static final int N = 1000000;
  static final double F = 1.5;

  @SuppressWarnings("unchecked")
  public static void main(String[] args) {
    HashMap<Tuple3<Long,Long,String>,Tuple2<Double,Double>> map = new HashMap<Tuple3<Long,Long,String>,Tuple2<Double,Double>>();
   
    for (int z=0;z<10;++z) {
      long t0 = System.nanoTime();
      long i,j;
      for (i=0;i<N;++i) {
        Tuple3<Long,Long,String> k = new Tuple3<Long,Long,String>(i,i+1,"Hello world");
        Tuple2<Double,Double> v = new Tuple2<Double,Double>(i*3.0,i*4.0);
        map.put(k,v);
      }
      for (j=0;j<N;++j) {
        i=r.nextLong()%(long)(N*F);
        Tuple3<Long,Long,String> k = new Tuple3<Long,Long,String>(i,i+1,"Hello world");
        Tuple2<Double,Double> v = new Tuple2<Double,Double>(i*1.0,i*1.0);
        if (!map.containsKey(k)) map.put(k,v);
        if (i%10==0) {
          Iterator it = map.entrySet().iterator();
          while (it.hasNext()) {
            Map.Entry pairs = (Map.Entry)it.next();
            Tuple3<Long,Long,String> k2 = (Tuple3<Long,Long,String>)pairs.getKey();
            Tuple2<Double,Double> v1 = (Tuple2<Double,Double>)pairs.getValue();
            Tuple2<Double,Double> v2 = new Tuple2<Double,Double>(v1._1()*2.0,v1._2()*0.5);
            map.put(k2,v2);
          }
        }
      }
        
      long t1 = System.nanoTime();
      long us = (t1-t0)/1000;
      map.clear();
      System.out.printf("Time = %.6f\n",us/1000000.0);
    }
  }
}
