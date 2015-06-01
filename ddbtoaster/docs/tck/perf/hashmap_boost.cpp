// FLAGS:= -I/opt/local/boost/include/ -L/opt/local/boost/lib/ -O3
#include <stdio.h>
#include <sys/time.h>

/*
---- @TCK ----
Add       : 0.309122
Clear     : 0.400807
Aggr      : 0.090225
Update    : 0.107135
Update2   : 0.496113
*/

#include <boost/fusion/tuple.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>

using namespace ::std;
using namespace ::boost;
using namespace ::boost::serialization;
using namespace ::boost::fusion;
using namespace ::boost::lambda;
using namespace ::boost::multi_index;

// http://stackoverflow.com/questions/1250599/how-to-unordered-settupleint-int

// Tuples hashing function
struct tuple_fusion_hash { typedef std::size_t result_type; template<typename T> std::size_t operator()(std::size_t seed, const T& arg) { boost::hash_combine(seed, arg); return seed; } };
struct tuple_hash { template<typename T> size_t operator()(const T& t) const { return boost::fusion::fold(t, 0, tuple_fusion_hash()); } };

// Secondary indices
//struct Idx0 {}; struct Idx1 {}; struct Idx2 {}; struct Idx3 {}; struct Idx4 {};

// My map definition
typedef boost::fusion::tuple<long,long,string> Key;
typedef boost::fusion::tuple<double,double> Val;

struct Rec {
  Key key; Val val;
  Rec(long c0,long c1,string c2, double c3, double c4) { key=Key(c0,c1,c2); val=Val(c3,c4); }
  Rec(const Key& k, const Val& v) { key=k; val=v; }
  Rec(std::pair<const Key,const Val>& p) { key=p.first; val=p.second; }
  // operator const std::pair<const Key, long>() const { return std::make_pair(key,val); }
  //long idx0() const { return get<0>(key); } // secondary indices
};

typedef multi_index_container<Rec, indexed_by<
  hashed_unique<member<Rec,Key,&Rec::key>,tuple_hash> //,
  //hashed_non_unique<tag<Idx0>, const_mem_fun<Rec,long,&Rec::idx0> > // secondary indices
> > MapBase;

class Map : public MapBase {
public:
  //typedef index<Idx0>::type::iterator it0;
  void clear() { MapBase::clear_(); }
};

Map map1;
Map map2;
static long N = 1000000;

void load() { for (long i=0;i<N;++i) map1.insert(Rec(i,i+1,"Hello world", i*3.0,i*4.0)); }
void clear() { map1.clear(); map2.clear(); }

int dcmp(const void *x, const void *y) { double xx = *(double*)x, yy = *(double*)y; return (xx<yy) ? -1 : ((xx > yy) ? 1 : 0); }

struct Timer {
  int n;
  double res[20];
  struct timeval t0,t1;
  Timer() { n=0; }
  void start() { gettimeofday (&t0,NULL); }
  void stop() {
    gettimeofday (&t1,NULL);
    res[n]=(t1.tv_sec-t0.tv_sec)+((double)(t1.tv_usec-t0.tv_usec))/1000000L;
    if (n<19) ++n;
  }
  void reset() { n=0; }
  void pr(const char* name) { qsort(res,n,sizeof(double),dcmp); printf("%-10s: %0.6f\n",name,res[n/2]); }
};

struct Fun_xx {
  void operator()(Rec &r) {
    r.val = Val(get<0>(r.val)*2.0,get<1>(r.val)*0.5);
  }
};

int main() {
  // 1. Add/clear
  Timer t_add;
  Timer t_clear;
  for (int z=0;z<10;++z) {
    t_add.start(); load(); t_add.stop();
    t_clear.start(); clear(); t_clear.stop();
  }
  t_add.pr("Add");
  t_clear.pr("Clear");
  load();

  // 2. Loop/aggregate
  Timer t_aggr;
  double acc=0;
  for (int z=0;z<10;++z) {
    t_aggr.start();
    Map::iterator it,end;
    it=map1.begin(); end=map1.end();
    if (it!=end) do {
      //map1.erase(it);
      acc += get<0>(it->val)*2.0+get<1>(it->val)*0.5;
    } while (++it!=end);
    t_aggr.stop();
  }
  t_aggr.pr("Aggr");

  // 3. Loop update
  Timer t_updt;
  for (int z=0;z<10;++z) {
    t_updt.start();
    Map::iterator it,end;
    it=map1.begin(); end=map1.end();
    if (it!=end) do {
      Fun_xx x;
      map1.modify(it,x);
    } while (++it!=end);
    t_updt.stop();
  }
  t_updt.pr("Update");

  // 4. Loop add/delete
  Timer t_up2;
  for (int z=0;z<10;++z) {
    t_up2.start();
    Map::iterator it,end;
    if (z%2==0) {
      it=map1.begin(); end=map1.end();
    } else {
      it=map2.begin(); end=map2.end();
    }
    if (it!=end) do {
      Rec r( get<0>(it->key)-3, get<1>(it->key)+3, "Hello world2", get<0>(it->val)*2.0, get<1>(it->key)*0.5  );
      if (z%2==0) {
        map2.insert(r);
        map1.erase(it);
      } else {
        map1.insert(r);
        map2.erase(it);
      }
    } while (++it!=end);
    t_up2.stop();
  }
  t_up2.pr("Update2");

  return 0;
}
