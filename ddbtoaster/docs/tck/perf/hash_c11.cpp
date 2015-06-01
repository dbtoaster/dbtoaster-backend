#include <iostream>
#ifdef __APPLE__
#include <tr1/unordered_map>
#include <tr1/tuple>
#else
#include <unordered_map>
#include <tuple>
#endif

// http://stackoverflow.com/questions/7222143/unordered-map-hash-function-c
// http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set
// http://stackoverflow.com/questions/15103975/my-stdhash-for-stdtuples-any-improvements

using namespace std;
using namespace tr1;

template <class T> // hash_combine
inline void __hc(std::size_t & seed, const T & v) { hash<T> hasher; seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2); }
namespace std {
  namespace tr1 {
    template<typename S, typename T> struct hash<pair<S, T> > {
      inline size_t operator()(const pair<S, T> & v) const { size_t s=0; __hc(s,v.first); __hc(s,v.second); return s; }
    };
    template<typename S, typename T> struct hash<tuple<S, T> > {
      inline size_t operator()(const tuple<S, T> & v) const { size_t s=0; __hc(s,v(0)); __hc(s,v(1)); return s; }
    };
    template<typename S, typename T, typename U> struct hash<tuple<S, T, U> > {
      inline size_t operator()(const tuple<S, T, U> & v) const { size_t s=0; __hc(s,v(0)); __hc(s,v(1)); __hc(s,v(2)); return s; }
    };
  }
}

typedef unordered_map<tuple<long,long,string>,tuple<double,double> > MyMap;

const int N = 1000000;

MyMap map;
MyMap map2;

void time() {
}

void load() {
  for (long i=0;i<N;++i) {
    tuple<long,long,string> k(i,i+1,"Hello world");
    tuple<double,double> v(i*3.0,i*4.0);
/*
    map.insert(k,v);
*/
  }
}

int main (int argc, char** argv) {

  /*


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
    */

  return 0;
}


/*
template <class T>
inline void hash_combine(std::size_t & seed, const T & v) {
  hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
  namespace tr1 {
    template<typename S, typename T> struct hash<pair<S, T> > {
      inline size_t operator()(const pair<S, T> & v) const {
        size_t seed = 0;
        ::hash_combine(seed, v.first);
        ::hash_combine(seed, v.second);
        return seed;
      }
    };
/ *
    template<typename ... TTypes>
    class hash<tuple<TTypes...> >
    {
    private:
        typedef tuple<TTypes...> Tuple;

        template<int N>
        size_t operator()(Tuple value) const { return 0; }

        template<int N, typename THead, typename... TTail>
        size_t operator()(Tuple value) const
        {
            constexpr int Index = N - sizeof...(TTail) - 1;
            return hash<THead>()(get<Index>(value)) ^ operator()<N, TTail...>(value);
        }

    public:
        size_t operator()(Tuple value) const
        {
            return operator()<sizeof...(TTypes), TTypes...>(value);
        }
    };
* /
  }
}




typedef unordered_map<pair<long, double>, double> MyMap; 
*/

/*
  MyMap m1;
  for (int i=0;i<100;++i) {
    tuple<long,double> t = make_tuple((long)i*2,(double)(i*3));

    pair<long,double> p = make_pair((long)i*2,(double)(i*3));
    m1.insert(MyMap::value_type(p, 25.0));
  }
  
*/
  

/*

    Mymap c1; 
 
    c1.insert(Mymap::value_type('a', 1)); 
    c1.insert(Mymap::value_type('b', 2)); 
    c1.insert(Mymap::value_type('c', 3)); 
 
// display contents " [c 3] [b 2] [a 1]" 
    for (Mymap::const_iterator it = c1.begin(); 
        it != c1.end(); ++it) 
        std::cout << " [" << it->first << ", " << it->second << "]"; 
    std::cout << std::endl; 
 
    Mymap c2(8, 
        std::tr1::hash<char>(), 
        std::equal_to<char>(), 
        std::allocator<std::pair<const char, int> >()); 
 
    c2.insert(Mymap::value_type('d', 4)); 
    c2.insert(Mymap::value_type('e', 5)); 
    c2.insert(Mymap::value_type('f', 6)); 
 
// display contents " [f 6] [e 5] [d 4]" 
    for (Mymap::const_iterator it = c2.begin(); 
        it != c2.end(); ++it) 
        std::cout << " [" << it->first << ", " << it->second << "]"; 
    std::cout << std::endl; 
 
    Mymap c3(c1.begin(), 
        c1.end(), 
        8, 
        std::tr1::hash<char>(), 
        std::equal_to<char>(), 
        std::allocator<std::pair<const char, int> >()); 
 
// display contents " [c 3] [b 2] [a 1]" 
    for (Mymap::const_iterator it = c3.begin(); 
        it != c3.end(); ++it) 
        std::cout << " [" << it->first << ", " << it->second << "]"; 
    std::cout << std::endl; 
*/
/*
    Mymap c4(move(c3));

// display contents " [c 3] [b 2] [a 1]" 
    for (Mymap::const_iterator it = c4.begin(); 
        it != c4.end(); ++it) 
        std::cout << " [" << it->first << ", " << it->second << "]"; 
    std::cout << std::endl; 
*/ 
