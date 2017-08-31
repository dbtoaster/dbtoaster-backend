#include <sys/time.h>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "hashmap.hpp"
#include "serialization.hpp"

#define ELEM_SEPARATOR "\n\t\t\t"

namespace dbtoaster {
  
  /* Definitions of auxiliary maps for storing materialized views. */
  struct ORDER_COUNT_entry {
    STRING_TYPE O_ORDERPRIORITY; long __av; 
    explicit ORDER_COUNT_entry() { /*O_ORDERPRIORITY = ""; __av = 0L; */ }
    explicit ORDER_COUNT_entry(const STRING_TYPE& c0, const long c1) { O_ORDERPRIORITY = c0; __av = c1; }
    ORDER_COUNT_entry(const ORDER_COUNT_entry& other) : O_ORDERPRIORITY( other.O_ORDERPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNT_entry& modify(const STRING_TYPE& c0) { O_ORDERPRIORITY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNT_entry& x, const ORDER_COUNT_entry& y) {
      return x.O_ORDERPRIORITY == y.O_ORDERPRIORITY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNT_entry,long,
    HashIndex<ORDER_COUNT_entry,long,ORDER_COUNT_mapkey0_idxfn,true>
  > ORDER_COUNT_map;
  typedef HashIndex<ORDER_COUNT_entry,long,ORDER_COUNT_mapkey0_idxfn,true> HashIndex_ORDER_COUNT_map_0;
  
  struct ORDER_COUNTLINEITEM1_entry {
    long ORDER_COUNTLINEITEMLINEITEM_ORDERKEY; STRING_TYPE O_ORDERPRIORITY; long __av; 
    explicit ORDER_COUNTLINEITEM1_entry() { /*ORDER_COUNTLINEITEMLINEITEM_ORDERKEY = 0L; O_ORDERPRIORITY = ""; __av = 0L; */ }
    explicit ORDER_COUNTLINEITEM1_entry(const long c0, const STRING_TYPE& c1, const long c2) { ORDER_COUNTLINEITEMLINEITEM_ORDERKEY = c0; O_ORDERPRIORITY = c1; __av = c2; }
    ORDER_COUNTLINEITEM1_entry(const ORDER_COUNTLINEITEM1_entry& other) : ORDER_COUNTLINEITEMLINEITEM_ORDERKEY( other.ORDER_COUNTLINEITEMLINEITEM_ORDERKEY ), O_ORDERPRIORITY( other.O_ORDERPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNTLINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { ORDER_COUNTLINEITEMLINEITEM_ORDERKEY = c0; O_ORDERPRIORITY = c1;  return *this; }
    FORCE_INLINE ORDER_COUNTLINEITEM1_entry& modify0(const long c0) { ORDER_COUNTLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDER_COUNTLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNTLINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDER_COUNTLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.O_ORDERPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTLINEITEM1_entry& x, const ORDER_COUNTLINEITEM1_entry& y) {
      return x.ORDER_COUNTLINEITEMLINEITEM_ORDERKEY == y.ORDER_COUNTLINEITEMLINEITEM_ORDERKEY && x.O_ORDERPRIORITY == y.O_ORDERPRIORITY;
    }
  };
  
  struct ORDER_COUNTLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDER_COUNTLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTLINEITEM1_entry& x, const ORDER_COUNTLINEITEM1_entry& y) {
      return x.ORDER_COUNTLINEITEMLINEITEM_ORDERKEY == y.ORDER_COUNTLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNTLINEITEM1_entry,long,
    HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey01_idxfn,true>,
    HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey0_idxfn,false>
  > ORDER_COUNTLINEITEM1_map;
  typedef HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey01_idxfn,true> HashIndex_ORDER_COUNTLINEITEM1_map_01;
  typedef HashIndex<ORDER_COUNTLINEITEM1_entry,long,ORDER_COUNTLINEITEM1_mapkey0_idxfn,false> HashIndex_ORDER_COUNTLINEITEM1_map_0;
  
  struct ORDER_COUNTORDERS3_E1_1_entry {
    long ORDER_COUNTORDERSORDERS_ORDERKEY; long __av; 
    explicit ORDER_COUNTORDERS3_E1_1_entry() { /*ORDER_COUNTORDERSORDERS_ORDERKEY = 0L; __av = 0L; */ }
    explicit ORDER_COUNTORDERS3_E1_1_entry(const long c0, const long c1) { ORDER_COUNTORDERSORDERS_ORDERKEY = c0; __av = c1; }
    ORDER_COUNTORDERS3_E1_1_entry(const ORDER_COUNTORDERS3_E1_1_entry& other) : ORDER_COUNTORDERSORDERS_ORDERKEY( other.ORDER_COUNTORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNTORDERS3_E1_1_entry& modify(const long c0) { ORDER_COUNTORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDER_COUNTORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNTORDERS3_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNTORDERS3_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDER_COUNTORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNTORDERS3_E1_1_entry& x, const ORDER_COUNTORDERS3_E1_1_entry& y) {
      return x.ORDER_COUNTORDERSORDERS_ORDERKEY == y.ORDER_COUNTORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNTORDERS3_E1_1_entry,long,
    HashIndex<ORDER_COUNTORDERS3_E1_1_entry,long,ORDER_COUNTORDERS3_E1_1_mapkey0_idxfn,true>
  > ORDER_COUNTORDERS3_E1_1_map;
  typedef HashIndex<ORDER_COUNTORDERS3_E1_1_entry,long,ORDER_COUNTORDERS3_E1_1_mapkey0_idxfn,true> HashIndex_ORDER_COUNTORDERS3_E1_1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const ORDER_COUNT_map& _ORDER_COUNT = get_ORDER_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(ORDER_COUNT), _ORDER_COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const ORDER_COUNT_map& get_ORDER_COUNT() const {
      return ORDER_COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    ORDER_COUNT_map ORDER_COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = Udate(STRING_TYPE("1993-10-1"));
      c1 = Udate(STRING_TYPE("1993-7-1"));
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_ORDER_COUNTLINEITEM1_map_0* i1 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_map_0*>(ORDER_COUNTLINEITEM1.index[1]);
          const HASH_RES_t h1 = ORDER_COUNTLINEITEM1_mapkey0_idxfn::hash(se4.modify0(lineitem_orderkey));
          HashIndex_ORDER_COUNTLINEITEM1_map_0::IdxNode* n1 = static_cast<HashIndex_ORDER_COUNTLINEITEM1_map_0::IdxNode*>(i1->slice(se4, h1));
          ORDER_COUNTLINEITEM1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE o_orderpriority = e1->O_ORDERPRIORITY;
              long v1 = e1->__av;
              ORDER_COUNT.addOrDelOnZero(se1.modify(o_orderpriority),((((ORDER_COUNTORDERS3_E1_1.getValueOrDefault(se2.modify(lineitem_orderkey)) + (/*if */(lineitem_receiptdate > lineitem_commitdate) ? 1L : 0L)) != 0 ? 1L : 0L) + ((ORDER_COUNTORDERS3_E1_1.getValueOrDefault(se3.modify(lineitem_orderkey)) != 0 ? 1L : 0L) * -1L)) * v1));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  ORDER_COUNTLINEITEM1_mapkey0_idxfn::equals(se4, *e1)); 
          }
        }(/*if */(lineitem_receiptdate > lineitem_commitdate) ? ORDER_COUNTORDERS3_E1_1.addOrDelOnZero(se5.modify(lineitem_orderkey),1L) : (void)0);
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? ORDER_COUNT.addOrDelOnZero(se6.modify(orders_orderpriority),(ORDER_COUNTORDERS3_E1_1.getValueOrDefault(se7.modify(orders_orderkey)) != 0 ? 1L : 0L)) : (void)0);
        (/*if */(c2 > orders_orderdate && orders_orderdate >= c1) ? ORDER_COUNTLINEITEM1.addOrDelOnZero(se8.modify(orders_orderkey,orders_orderpriority),1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    ORDER_COUNT_entry se1;
    ORDER_COUNTORDERS3_E1_1_entry se2;
    ORDER_COUNTORDERS3_E1_1_entry se3;
    ORDER_COUNTLINEITEM1_entry se4;
    ORDER_COUNTORDERS3_E1_1_entry se5;
    ORDER_COUNT_entry se6;
    ORDER_COUNTORDERS3_E1_1_entry se7;
    ORDER_COUNTLINEITEM1_entry se8;
  
    /* Data structures used for storing materialized views */
    ORDER_COUNTLINEITEM1_map ORDER_COUNTLINEITEM1;
    ORDER_COUNTORDERS3_E1_1_map ORDER_COUNTORDERS3_E1_1;
    
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ long c1;
  
  };

}
