package ddbt.test.perf;
import java.util.*;
import scala.Tuple2;
import scala.Tuple3;

/*
---- @TCK ----
Add       : 0.195297
Clear     : 0.000778
Aggr      : 0.017181
Update    : 0.041245
Update2   : 0.344619

No specialization (using scala.Tuple*)
Add       : 0.215072
Clear     : 0.000783
Aggr      : 0.021762
Update    : 0.072890
Update2   : 0.337194

*/

class Key {
  long _1,_2; String _3;
  Key(long l1_, long l2_, String s3_) { _1=l1_; _2=l2_; _3=s3_; }
}

class Val {
  double _1,_2;
  Val(double d1_, double d2_) { _1=d1_; _2=d2_; }
}


class HashMapPerf {
  static final int N = 1000000;

  static long t() { return System.nanoTime(); }
  static void time(String n, long[] t) {
    java.util.Arrays.sort(t); long t0=t[3]; long us=t0/1000; // little bias towards minimum due to warm-up
    System.out.printf("%-10s: %d.%06d\n",n,us/1000000,us%1000000);
  }

  static HashMap<Key,Val> map = new HashMap<Key,Val>();
  static HashMap<Key,Val> map2 = new HashMap<Key,Val>();

  static void load() {
    for (long i=0;i<N;++i) {
      Key k = new Key(i,i+1,"Hello world");
      Val v = new Val(i*3.0,i*4.0);
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
        Key k2 = (Key)pairs.getKey();
        Val v1 = (Val)pairs.getValue();
        acc += v1._1*2.0+v1._2*0.5;
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
        Key k2 = (Key)pairs.getKey();
        Val v1 = (Val)pairs.getValue();
        Val v2 = new Val(v1._1*2.0,v1._2*0.5);
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
        Key k1 = (Key)pairs.getKey();
        Val v1 = (Val)pairs.getValue();
        Key k2 = new Key(k1._1-3,k1._2+3,"Hello world2");
        Val v2 = new Val(v1._1*2.0,v1._2*0.5);
        (z%2==0 ? map2 : map).put(k2,v2);
        it.remove();
      }
      long t1=t();
      t_up2[z]=t1-t0;
    }
    time("Update2",t_up2);

  }
}
