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
  
  struct ORDER_COUNT_mLINEITEM1_entry {
    long ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY; STRING_TYPE O_ORDERPRIORITY; long __av; 
    explicit ORDER_COUNT_mLINEITEM1_entry() { /*ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY = 0L; O_ORDERPRIORITY = ""; __av = 0L; */ }
    explicit ORDER_COUNT_mLINEITEM1_entry(const long c0, const STRING_TYPE& c1, const long c2) { ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0; O_ORDERPRIORITY = c1; __av = c2; }
    ORDER_COUNT_mLINEITEM1_entry(const ORDER_COUNT_mLINEITEM1_entry& other) : ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY( other.ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY ), O_ORDERPRIORITY( other.O_ORDERPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNT_mLINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0; O_ORDERPRIORITY = c1;  return *this; }
    FORCE_INLINE ORDER_COUNT_mLINEITEM1_entry& modify0(const long c0) { ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNT_mLINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNT_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.O_ORDERPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNT_mLINEITEM1_entry& x, const ORDER_COUNT_mLINEITEM1_entry& y) {
      return x.ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY == y.ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY && x.O_ORDERPRIORITY == y.O_ORDERPRIORITY;
    }
  };
  
  struct ORDER_COUNT_mLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNT_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNT_mLINEITEM1_entry& x, const ORDER_COUNT_mLINEITEM1_entry& y) {
      return x.ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY == y.ORDER_COUNT_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNT_mLINEITEM1_entry,long,
    HashIndex<ORDER_COUNT_mLINEITEM1_entry,long,ORDER_COUNT_mLINEITEM1_mapkey01_idxfn,true>,
    HashIndex<ORDER_COUNT_mLINEITEM1_entry,long,ORDER_COUNT_mLINEITEM1_mapkey0_idxfn,false>
  > ORDER_COUNT_mLINEITEM1_map;
  typedef HashIndex<ORDER_COUNT_mLINEITEM1_entry,long,ORDER_COUNT_mLINEITEM1_mapkey01_idxfn,true> HashIndex_ORDER_COUNT_mLINEITEM1_map_01;
  typedef HashIndex<ORDER_COUNT_mLINEITEM1_entry,long,ORDER_COUNT_mLINEITEM1_mapkey0_idxfn,false> HashIndex_ORDER_COUNT_mLINEITEM1_map_0;
  
  struct ORDER_COUNT_mORDERS3_E1_1_entry {
    long ORDER_COUNT_mORDERSORDERS_ORDERKEY; long __av; 
    explicit ORDER_COUNT_mORDERS3_E1_1_entry() { /*ORDER_COUNT_mORDERSORDERS_ORDERKEY = 0L; __av = 0L; */ }
    explicit ORDER_COUNT_mORDERS3_E1_1_entry(const long c0, const long c1) { ORDER_COUNT_mORDERSORDERS_ORDERKEY = c0; __av = c1; }
    ORDER_COUNT_mORDERS3_E1_1_entry(const ORDER_COUNT_mORDERS3_E1_1_entry& other) : ORDER_COUNT_mORDERSORDERS_ORDERKEY( other.ORDER_COUNT_mORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE ORDER_COUNT_mORDERS3_E1_1_entry& modify(const long c0) { ORDER_COUNT_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDER_COUNT_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct ORDER_COUNT_mORDERS3_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const ORDER_COUNT_mORDERS3_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDER_COUNT_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const ORDER_COUNT_mORDERS3_E1_1_entry& x, const ORDER_COUNT_mORDERS3_E1_1_entry& y) {
      return x.ORDER_COUNT_mORDERSORDERS_ORDERKEY == y.ORDER_COUNT_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<ORDER_COUNT_mORDERS3_E1_1_entry,long,
    HashIndex<ORDER_COUNT_mORDERS3_E1_1_entry,long,ORDER_COUNT_mORDERS3_E1_1_mapkey0_idxfn,true>
  > ORDER_COUNT_mORDERS3_E1_1_map;
  typedef HashIndex<ORDER_COUNT_mORDERS3_E1_1_entry,long,ORDER_COUNT_mORDERS3_E1_1_mapkey0_idxfn,true> HashIndex_ORDER_COUNT_mORDERS3_E1_1_map_0;
  
  
  
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
      {  //++tN;
        { //slice 
          const HashIndex_ORDER_COUNT_mLINEITEM1_map_0* i1 = static_cast<HashIndex_ORDER_COUNT_mLINEITEM1_map_0*>(ORDER_COUNT_mLINEITEM1.index[1]);
          const HASH_RES_t h1 = ORDER_COUNT_mLINEITEM1_mapkey0_idxfn::hash(se4.modify0(lineitem_orderkey));
          HashIndex_ORDER_COUNT_mLINEITEM1_map_0::IdxNode* n1 = static_cast<HashIndex_ORDER_COUNT_mLINEITEM1_map_0::IdxNode*>(i1->slice(se4, h1));
          ORDER_COUNT_mLINEITEM1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE o_orderpriority = e1->O_ORDERPRIORITY;
              long v1 = e1->__av;
              ORDER_COUNT.addOrDelOnZero(se1.modify(o_orderpriority),((((ORDER_COUNT_mORDERS3_E1_1.getValueOrDefault(se2.modify(lineitem_orderkey)) + (/*if */(lineitem_receiptdate > lineitem_commitdate) ? 1L : 0L)) != 0 ? 1L : 0L) + ((ORDER_COUNT_mORDERS3_E1_1.getValueOrDefault(se3.modify(lineitem_orderkey)) != 0 ? 1L : 0L) * -1L)) * v1));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  ORDER_COUNT_mLINEITEM1_mapkey0_idxfn::equals(se4, *e1)); 
          }
        }(/*if */(lineitem_receiptdate > lineitem_commitdate) ? ORDER_COUNT_mORDERS3_E1_1.addOrDelOnZero(se5.modify(lineitem_orderkey),1L) : (void)0);
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_ORDER_COUNT_mLINEITEM1_map_0* i2 = static_cast<HashIndex_ORDER_COUNT_mLINEITEM1_map_0*>(ORDER_COUNT_mLINEITEM1.index[1]);
          const HASH_RES_t h2 = ORDER_COUNT_mLINEITEM1_mapkey0_idxfn::hash(se9.modify0(lineitem_orderkey));
          HashIndex_ORDER_COUNT_mLINEITEM1_map_0::IdxNode* n2 = static_cast<HashIndex_ORDER_COUNT_mLINEITEM1_map_0::IdxNode*>(i2->slice(se9, h2));
          ORDER_COUNT_mLINEITEM1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE o_orderpriority = e2->O_ORDERPRIORITY;
              long v2 = e2->__av;
              ORDER_COUNT.addOrDelOnZero(se6.modify(o_orderpriority),((((ORDER_COUNT_mORDERS3_E1_1.getValueOrDefault(se7.modify(lineitem_orderkey)) + (/*if */(lineitem_receiptdate > lineitem_commitdate) ? -1L : 0L)) != 0 ? 1L : 0L) + ((ORDER_COUNT_mORDERS3_E1_1.getValueOrDefault(se8.modify(lineitem_orderkey)) != 0 ? 1L : 0L) * -1L)) * v2));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  ORDER_COUNT_mLINEITEM1_mapkey0_idxfn::equals(se9, *e2)); 
          }
        }(/*if */(lineitem_receiptdate > lineitem_commitdate) ? ORDER_COUNT_mORDERS3_E1_1.addOrDelOnZero(se10.modify(lineitem_orderkey),-1L) : (void)0);
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? ORDER_COUNT.addOrDelOnZero(se11.modify(orders_orderpriority),(ORDER_COUNT_mORDERS3_E1_1.getValueOrDefault(se12.modify(orders_orderkey)) != 0 ? 1L : 0L)) : (void)0);
        (/*if */(c2 > orders_orderdate && orders_orderdate >= c1) ? ORDER_COUNT_mLINEITEM1.addOrDelOnZero(se13.modify(orders_orderkey,orders_orderpriority),1L) : (void)0);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        (/*if */(orders_orderdate >= c1 && c2 > orders_orderdate) ? ORDER_COUNT.addOrDelOnZero(se14.modify(orders_orderpriority),((ORDER_COUNT_mORDERS3_E1_1.getValueOrDefault(se15.modify(orders_orderkey)) != 0 ? 1L : 0L) * -1L)) : (void)0);
        (/*if */(c2 > orders_orderdate && orders_orderdate >= c1) ? ORDER_COUNT_mLINEITEM1.addOrDelOnZero(se16.modify(orders_orderkey,orders_orderpriority),-1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  //
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    ORDER_COUNT_entry se1;
    ORDER_COUNT_mORDERS3_E1_1_entry se2;
    ORDER_COUNT_mORDERS3_E1_1_entry se3;
    ORDER_COUNT_mLINEITEM1_entry se4;
    ORDER_COUNT_mORDERS3_E1_1_entry se5;
    ORDER_COUNT_entry se6;
    ORDER_COUNT_mORDERS3_E1_1_entry se7;
    ORDER_COUNT_mORDERS3_E1_1_entry se8;
    ORDER_COUNT_mLINEITEM1_entry se9;
    ORDER_COUNT_mORDERS3_E1_1_entry se10;
    ORDER_COUNT_entry se11;
    ORDER_COUNT_mORDERS3_E1_1_entry se12;
    ORDER_COUNT_mLINEITEM1_entry se13;
    ORDER_COUNT_entry se14;
    ORDER_COUNT_mORDERS3_E1_1_entry se15;
    ORDER_COUNT_mLINEITEM1_entry se16;
  
    /* Data structures used for storing materialized views */
    ORDER_COUNT_mLINEITEM1_map ORDER_COUNT_mLINEITEM1;
    ORDER_COUNT_mORDERS3_E1_1_map ORDER_COUNT_mORDERS3_E1_1;
    
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ long c1;
  
  };

}
