// FLAGS:= -I/opt/local/boost/include/ -L/opt/local/boost/lib/ -O3
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
struct Idx0 {}; struct Idx1 {}; struct Idx2 {}; struct Idx3 {}; struct Idx4 {};

// My map definition
typedef boost::fusion::tuple<long,double> Key;

struct Rec {
  Key key; long val;
  Rec(long c0,double c1,long c2) { key=Key(c0,c1); val=c2; }
  // Rec(std::pair<const Key,long>& p) { key=p.first; val=p.second; }
  // operator const std::pair<const Key, long>() const { return std::make_pair(key,val); }
  long idx0() const { return get<0>(key); } // secondary indices
};

class Map : public multi_index_container<Rec, indexed_by<
  hashed_unique<member<Rec,Key,&Rec::key>,tuple_hash>,
  hashed_non_unique<tag<Idx0>, const_mem_fun<Rec,long,&Rec::idx0> > // secondary indices
> > {
public:
  typedef index<Idx0>::type::iterator it0;
};

Map myMap;

int main() {
  for (long i=0;i<10;++i) {
    Rec r(i,i*2.0,i+3);
    myMap.insert(r);
  }

  long BIDS_BROKER_ID = 1;
  double BIDS_PRICE = 2.0;

  // Update / insert
  Map::iterator it = myMap.find(Key(BIDS_BROKER_ID,BIDS_PRICE));
  if (it!=myMap.end()) {
    printf("Found\n");
    myMap.modify(it,boost::lambda::bind(&Rec::val, boost::lambda::_1) = ((*myMap.find(Key(BIDS_BROKER_ID,BIDS_PRICE))).val+static_cast<long>(1)));
  } else {
    printf("Failed\n");
    Rec ___y24(BIDS_BROKER_ID,BIDS_PRICE,((*myMap.find(Key(BIDS_BROKER_ID,BIDS_PRICE))).val+static_cast<long>(1)));
    myMap.insert(___y24);
  }
  
  // Foreach/accumulate
  long ASKS_BROKER_ID = 1;
  double ASKS_PRICE = 2.0;
  
  // Main iterator:
  Map::iterator it1 = myMap.begin();
  Map::iterator ite = myMap.end();
  if (it1!=ite) do {
    printf("%ld\n",get<0>(it1->key));
  } while(++it1!=ite);
  
  // Secondary index iterator:
  long __accv_6 = static_cast<long>(0);
  std::pair<Map::it0,Map::it0> ___y63 = myMap.get<Idx0>().equal_range(ASKS_BROKER_ID);

  Map::it0 _it = ___y63.first;
  Map::it0 _end = ___y63.second;
  if (_it!=_end) do {
    long asks_broker_id = get<0>(_it->key);
    double b_price = get<1>(_it->key);
    long __map_ret__6 = (*_it).val;
    printf("%f -> %ld\n",b_price,__map_ret__6);
    __accv_6 = (__accv_6+(__map_ret__6*(0L<((1000L<(ASKS_PRICE+(-1L*b_price)))+(1000L<(b_price+(-1L*ASKS_PRICE)))))));
  } while (++_it!=_end);
  
  return 0;
}
