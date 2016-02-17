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
  struct HIGH_LINE_COUNT_entry {
    STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNT_entry() { /*L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNT_entry(const STRING_TYPE& c0, const long c1) { L_SHIPMODE = c0; __av = c1; }
    HIGH_LINE_COUNT_entry(const HIGH_LINE_COUNT_entry& other) : L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNT_entry& modify(const STRING_TYPE& c0) { L_SHIPMODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_entry& x, const HIGH_LINE_COUNT_entry& y) {
      return x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNT_entry,long,
    HashIndex<HIGH_LINE_COUNT_entry,long,HIGH_LINE_COUNT_mapkey0_idxfn,true>
  > HIGH_LINE_COUNT_map;
  typedef HashIndex<HIGH_LINE_COUNT_entry,long,HIGH_LINE_COUNT_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNT_map_0;
  
  struct HIGH_LINE_COUNTLINEITEM6_entry {
    long HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit HIGH_LINE_COUNTLINEITEM6_entry() { /*HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit HIGH_LINE_COUNTLINEITEM6_entry(const long c0, const long c1) { HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY = c0; __av = c1; }
    HIGH_LINE_COUNTLINEITEM6_entry(const HIGH_LINE_COUNTLINEITEM6_entry& other) : HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY( other.HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTLINEITEM6_entry& modify(const long c0) { HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTLINEITEM6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTLINEITEM6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTLINEITEM6_entry& x, const HIGH_LINE_COUNTLINEITEM6_entry& y) {
      return x.HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY == y.HIGH_LINE_COUNTLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTLINEITEM6_entry,long,
    HashIndex<HIGH_LINE_COUNTLINEITEM6_entry,long,HIGH_LINE_COUNTLINEITEM6_mapkey0_idxfn,true>
  > HIGH_LINE_COUNTLINEITEM6_map;
  typedef HashIndex<HIGH_LINE_COUNTLINEITEM6_entry,long,HIGH_LINE_COUNTLINEITEM6_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNTLINEITEM6_map_0;
  
  struct HIGH_LINE_COUNTORDERS2_entry {
    long HIGH_LINE_COUNTORDERSORDERS_ORDERKEY; STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNTORDERS2_entry() { /*HIGH_LINE_COUNTORDERSORDERS_ORDERKEY = 0L; L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNTORDERS2_entry(const long c0, const STRING_TYPE& c1, const long c2) { HIGH_LINE_COUNTORDERSORDERS_ORDERKEY = c0; L_SHIPMODE = c1; __av = c2; }
    HIGH_LINE_COUNTORDERS2_entry(const HIGH_LINE_COUNTORDERS2_entry& other) : HIGH_LINE_COUNTORDERSORDERS_ORDERKEY( other.HIGH_LINE_COUNTORDERSORDERS_ORDERKEY ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNTORDERS2_entry& modify(const long c0, const STRING_TYPE& c1) { HIGH_LINE_COUNTORDERSORDERS_ORDERKEY = c0; L_SHIPMODE = c1;  return *this; }
    FORCE_INLINE HIGH_LINE_COUNTORDERS2_entry& modify0(const long c0) { HIGH_LINE_COUNTORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HIGH_LINE_COUNTORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNTORDERS2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNTORDERSORDERS_ORDERKEY);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS2_entry& x, const HIGH_LINE_COUNTORDERS2_entry& y) {
      return x.HIGH_LINE_COUNTORDERSORDERS_ORDERKEY == y.HIGH_LINE_COUNTORDERSORDERS_ORDERKEY && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  struct HIGH_LINE_COUNTORDERS2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNTORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNTORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNTORDERS2_entry& x, const HIGH_LINE_COUNTORDERS2_entry& y) {
      return x.HIGH_LINE_COUNTORDERSORDERS_ORDERKEY == y.HIGH_LINE_COUNTORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNTORDERS2_entry,long,
    HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey01_idxfn,true>,
    HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey0_idxfn,false>
  > HIGH_LINE_COUNTORDERS2_map;
  typedef HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey01_idxfn,true> HashIndex_HIGH_LINE_COUNTORDERS2_map_01;
  typedef HashIndex<HIGH_LINE_COUNTORDERS2_entry,long,HIGH_LINE_COUNTORDERS2_mapkey0_idxfn,false> HashIndex_HIGH_LINE_COUNTORDERS2_map_0;
  
  struct LOW_LINE_COUNT_entry {
    STRING_TYPE L_SHIPMODE; long __av; 
    explicit LOW_LINE_COUNT_entry() { /*L_SHIPMODE = ""; __av = 0L; */ }
    explicit LOW_LINE_COUNT_entry(const STRING_TYPE& c0, const long c1) { L_SHIPMODE = c0; __av = c1; }
    LOW_LINE_COUNT_entry(const LOW_LINE_COUNT_entry& other) : L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE LOW_LINE_COUNT_entry& modify(const STRING_TYPE& c0) { L_SHIPMODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct LOW_LINE_COUNT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const LOW_LINE_COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const LOW_LINE_COUNT_entry& x, const LOW_LINE_COUNT_entry& y) {
      return x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  typedef MultiHashMap<LOW_LINE_COUNT_entry,long,
    HashIndex<LOW_LINE_COUNT_entry,long,LOW_LINE_COUNT_mapkey0_idxfn,true>
  > LOW_LINE_COUNT_map;
  typedef HashIndex<LOW_LINE_COUNT_entry,long,LOW_LINE_COUNT_mapkey0_idxfn,true> HashIndex_LOW_LINE_COUNT_map_0;
  
  struct LOW_LINE_COUNTLINEITEM6_entry {
    long LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit LOW_LINE_COUNTLINEITEM6_entry() { /*LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit LOW_LINE_COUNTLINEITEM6_entry(const long c0, const long c1) { LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY = c0; __av = c1; }
    LOW_LINE_COUNTLINEITEM6_entry(const LOW_LINE_COUNTLINEITEM6_entry& other) : LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY( other.LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE LOW_LINE_COUNTLINEITEM6_entry& modify(const long c0) { LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct LOW_LINE_COUNTLINEITEM6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const LOW_LINE_COUNTLINEITEM6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const LOW_LINE_COUNTLINEITEM6_entry& x, const LOW_LINE_COUNTLINEITEM6_entry& y) {
      return x.LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY == y.LOW_LINE_COUNTLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<LOW_LINE_COUNTLINEITEM6_entry,long,
    HashIndex<LOW_LINE_COUNTLINEITEM6_entry,long,LOW_LINE_COUNTLINEITEM6_mapkey0_idxfn,true>
  > LOW_LINE_COUNTLINEITEM6_map;
  typedef HashIndex<LOW_LINE_COUNTLINEITEM6_entry,long,LOW_LINE_COUNTLINEITEM6_mapkey0_idxfn,true> HashIndex_LOW_LINE_COUNTLINEITEM6_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const HIGH_LINE_COUNT_map& _HIGH_LINE_COUNT = get_HIGH_LINE_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(HIGH_LINE_COUNT), _HIGH_LINE_COUNT, "\t");
      ar << "\n";
      const LOW_LINE_COUNT_map& _LOW_LINE_COUNT = get_LOW_LINE_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(LOW_LINE_COUNT), _LOW_LINE_COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const HIGH_LINE_COUNT_map& get_HIGH_LINE_COUNT() const {
      return HIGH_LINE_COUNT;
    
    }
    const LOW_LINE_COUNT_map& get_LOW_LINE_COUNT() const {
      return LOW_LINE_COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    HIGH_LINE_COUNT_map HIGH_LINE_COUNT;
    LOW_LINE_COUNT_map LOW_LINE_COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c6 = STRING_TYPE("2-HIGH");
      c5 = STRING_TYPE("1-URGENT");
      c4 = STRING_TYPE("SHIP");
      c2 = Udate(STRING_TYPE("1994-1-1"));
      c1 = Udate(STRING_TYPE("1995-1-1"));
      c3 = STRING_TYPE("MAIL");
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(c1 > lineitem_receiptdate && lineitem_receiptdate >= c2 && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate > lineitem_commitdate && ((lineitem_shipmode == c3) || (lineitem_shipmode == c4))) ? HIGH_LINE_COUNT.addOrDelOnZero(se1.modify(lineitem_shipmode),HIGH_LINE_COUNTLINEITEM6.getValueOrDefault(se2.modify(lineitem_orderkey))) : (void)0);
        (/*if */(lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c2 && c1 > lineitem_receiptdate && ((lineitem_shipmode == c3) || (lineitem_shipmode == c4))) ? HIGH_LINE_COUNTORDERS2.addOrDelOnZero(se3.modify(lineitem_orderkey,lineitem_shipmode),1L) : (void)0);
        (/*if */(c1 > lineitem_receiptdate && lineitem_receiptdate >= c2 && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate > lineitem_commitdate && ((lineitem_shipmode == c3) || (lineitem_shipmode == c4))) ? LOW_LINE_COUNT.addOrDelOnZero(se4.modify(lineitem_shipmode),LOW_LINE_COUNTLINEITEM6.getValueOrDefault(se5.modify(lineitem_orderkey))) : (void)0);
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_HIGH_LINE_COUNTORDERS2_map_0* i1 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0*>(HIGH_LINE_COUNTORDERS2.index[1]);
          const HASH_RES_t h1 = HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::hash(se7.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode* n1 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode*>(i1->slice(se7, h1));
          HIGH_LINE_COUNTORDERS2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE l_shipmode = e1->L_SHIPMODE;
              long v1 = e1->__av;
              (/*if */(((orders_orderpriority == c5) || (orders_orderpriority == c6))) ? HIGH_LINE_COUNT.addOrDelOnZero(se6.modify(l_shipmode),v1) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::equals(se7, *e1)); 
          }
        }(/*if */(((orders_orderpriority == c5) || (orders_orderpriority == c6))) ? HIGH_LINE_COUNTLINEITEM6.addOrDelOnZero(se8.modify(orders_orderkey),1L) : (void)0);
        { //slice 
          const HashIndex_HIGH_LINE_COUNTORDERS2_map_0* i2 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0*>(HIGH_LINE_COUNTORDERS2.index[1]);
          const HASH_RES_t h2 = HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::hash(se10.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode* n2 = static_cast<HashIndex_HIGH_LINE_COUNTORDERS2_map_0::IdxNode*>(i2->slice(se10, h2));
          HIGH_LINE_COUNTORDERS2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE l_shipmode = e2->L_SHIPMODE;
              long v2 = e2->__av;
              (/*if */(c6 != orders_orderpriority && c5 != orders_orderpriority) ? LOW_LINE_COUNT.addOrDelOnZero(se9.modify(l_shipmode),v2) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  HIGH_LINE_COUNTORDERS2_mapkey0_idxfn::equals(se10, *e2)); 
          }
        }(/*if */(c5 != orders_orderpriority && c6 != orders_orderpriority) ? LOW_LINE_COUNTLINEITEM6.addOrDelOnZero(se11.modify(orders_orderkey),1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    HIGH_LINE_COUNT_entry se1;
    HIGH_LINE_COUNTLINEITEM6_entry se2;
    HIGH_LINE_COUNTORDERS2_entry se3;
    LOW_LINE_COUNT_entry se4;
    LOW_LINE_COUNTLINEITEM6_entry se5;
    HIGH_LINE_COUNT_entry se6;
    HIGH_LINE_COUNTORDERS2_entry se7;
    HIGH_LINE_COUNTLINEITEM6_entry se8;
    LOW_LINE_COUNT_entry se9;
    HIGH_LINE_COUNTORDERS2_entry se10;
    LOW_LINE_COUNTLINEITEM6_entry se11;
  
    /* Data structures used for storing materialized views */
    HIGH_LINE_COUNTLINEITEM6_map HIGH_LINE_COUNTLINEITEM6;
    HIGH_LINE_COUNTORDERS2_map HIGH_LINE_COUNTORDERS2;
    LOW_LINE_COUNTLINEITEM6_map LOW_LINE_COUNTLINEITEM6;
    
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
