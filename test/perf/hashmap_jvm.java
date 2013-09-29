package ddbt.test.perf;
import java.util.*;
import scala.Tuple2;
import scala.Tuple3;

class HashMap {
  static final int N = 1000000;

  static long t() { return System.nanoTime(); }
  static void time(String n, long[] t) {
    java.util.Arrays.sort(t); long t0=t[3]; long us=t0/1000; // little bias towards minimum due to warm-up
    System.out.printf("%-10s: %d.%06d\n",n,us/1000000,us%1000000);
  }

  static HashMap<Tuple3<Long,Long,String>,Tuple2<Double,Double>> map = new HashMap<Tuple3<Long,Long,String>,Tuple2<Double,Double>>();
  static HashMap<Tuple3<Long,Long,String>,Tuple2<Double,Double>> map2 = new HashMap<Tuple3<Long,Long,String>,Tuple2<Double,Double>>();

  static void load() {
    for (long i=0;i<N;++i) {
      Tuple3<Long,Long,String> k = new Tuple3<Long,Long,String>(i,i+1,"Hello world");
      Tuple2<Double,Double> v = new Tuple2<Double,Double>(i*3.0,i*4.0);
      map.put(k,v);
    }
  }

  @SuppressWarnings("unchecked")
  public static void main(String[] args) {
    
    // 1. Add/clear
    long[] t_add=new long[10];
    long[] t_clear= new long[10];
    for (int z=0;z<10;++z) {
      long t0=t();
      load();
      long t1=t();
      map.clear();
      long t2=t();
      t_add[z]=t1-t0;
      t_clear[z]=t2-t1;
    }
    time("Add",t_add);
    time("Clear",t_clear);

    load();
    System.gc();

    // 2. Loop/aggregate
    long[] t_aggr=new long[10];
    double acc=0;
    for (int z=0;z<10;++z) {
      long t0=t();
      Iterator it = map.entrySet().iterator();
      while (it.hasNext()) {
        Map.Entry pairs = (Map.Entry)it.next();
        Tuple3<Long,Long,String> k2 = (Tuple3<Long,Long,String>)pairs.getKey();
        Tuple2<Double,Double> v1 = (Tuple2<Double,Double>)pairs.getValue();
        acc += v1._1()*2.0+v1._2()*0.5;
      }
      long t1=t();
      t_aggr[z]=t1-t0;
    }
    time("Aggr",t_aggr);
    System.gc();
    
    // 3. Loop update
    long[] t_updt=new long[10];
    for (int z=0;z<10;++z) {
      long t0=t();
      Iterator it = map.entrySet().iterator();
      while (it.hasNext()) {
        Map.Entry pairs = (Map.Entry)it.next();
        Tuple3<Long,Long,String> k2 = (Tuple3<Long,Long,String>)pairs.getKey();
        Tuple2<Double,Double> v1 = (Tuple2<Double,Double>)pairs.getValue();
        Tuple2<Double,Double> v2 = new Tuple2<Double,Double>(v1._1()*2.0,v1._2()*0.5);
        map.put(k2,v2);
      }
      long t1=t();
      t_updt[z]=t1-t0;
    }
    time("Update",t_updt);
    System.gc();
    
    // 4. Loop add/delete
    long[] t_up2=new long[10];
    for (int z=0;z<10;++z) {
      long t0=t();
      Iterator it = (z%2==0? map : map2).entrySet().iterator();
      while (it.hasNext()) {
        Map.Entry pairs = (Map.Entry)it.next();
        Tuple3<Long,Long,String> k1 = (Tuple3<Long,Long,String>)pairs.getKey();
        Tuple2<Double,Double> v1 = (Tuple2<Double,Double>)pairs.getValue();
        Tuple3<Long,Long,String> k2 = new Tuple3<Long,Long,String>(k1._1()-3,k1._2()+3,"Hello world2");
        Tuple2<Double,Double> v2 = new Tuple2<Double,Double>(v1._1()*2.0,v1._2()*0.5);
        (z%2==0 ? map2 : map).put(k2,v2);
        it.remove();
      }
      long t1=t();
      t_up2[z]=t1-t0;
    }
    time("Update2",t_up2);

  }
}
