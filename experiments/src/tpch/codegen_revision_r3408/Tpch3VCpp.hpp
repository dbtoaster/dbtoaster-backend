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
  struct QUERY3_entry {
    long ORDERS_ORDERKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; DOUBLE_TYPE __av; 
    explicit QUERY3_entry() { /*ORDERS_ORDERKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0.0; */ }
    explicit QUERY3_entry(const long c0, const date c1, const long c2, const DOUBLE_TYPE c3) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2; __av = c3; }
    QUERY3_entry(const QUERY3_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_entry& modify(const long c0, const date c1, const long c2) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_entry& x, const QUERY3_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  typedef MultiHashMap<QUERY3_entry,DOUBLE_TYPE,
    HashIndex<QUERY3_entry,DOUBLE_TYPE,QUERY3_mapkey012_idxfn,true>
  > QUERY3_map;
  typedef HashIndex<QUERY3_entry,DOUBLE_TYPE,QUERY3_mapkey012_idxfn,true> HashIndex_QUERY3_map_012;
  
  struct QUERY3LINEITEM2_entry {
    long QUERY3LINEITEMLINEITEM_ORDERKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3LINEITEM2_entry() { /*QUERY3LINEITEMLINEITEM_ORDERKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3LINEITEM2_entry(const long c0, const date c1, const long c2, const long c3) { QUERY3LINEITEMLINEITEM_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2; __av = c3; }
    QUERY3LINEITEM2_entry(const QUERY3LINEITEM2_entry& other) : QUERY3LINEITEMLINEITEM_ORDERKEY( other.QUERY3LINEITEMLINEITEM_ORDERKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3LINEITEM2_entry& modify(const long c0, const date c1, const long c2) { QUERY3LINEITEMLINEITEM_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2;  return *this; }
    FORCE_INLINE QUERY3LINEITEM2_entry& modify0(const long c0) { QUERY3LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3LINEITEM2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM2_entry& x, const QUERY3LINEITEM2_entry& y) {
      return x.QUERY3LINEITEMLINEITEM_ORDERKEY == y.QUERY3LINEITEMLINEITEM_ORDERKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3LINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM2_entry& x, const QUERY3LINEITEM2_entry& y) {
      return x.QUERY3LINEITEMLINEITEM_ORDERKEY == y.QUERY3LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3LINEITEM2_entry,long,
    HashIndex<QUERY3LINEITEM2_entry,long,QUERY3LINEITEM2_mapkey012_idxfn,true>,
    HashIndex<QUERY3LINEITEM2_entry,long,QUERY3LINEITEM2_mapkey0_idxfn,false>
  > QUERY3LINEITEM2_map;
  typedef HashIndex<QUERY3LINEITEM2_entry,long,QUERY3LINEITEM2_mapkey012_idxfn,true> HashIndex_QUERY3LINEITEM2_map_012;
  typedef HashIndex<QUERY3LINEITEM2_entry,long,QUERY3LINEITEM2_mapkey0_idxfn,false> HashIndex_QUERY3LINEITEM2_map_0;
  
  struct QUERY3LINEITEM2CUSTOMER2_entry {
    long QUERY3LINEITEMLINEITEM_ORDERKEY; long QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3LINEITEM2CUSTOMER2_entry() { /*QUERY3LINEITEMLINEITEM_ORDERKEY = 0L; QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3LINEITEM2CUSTOMER2_entry(const long c0, const long c1, const date c2, const long c3, const long c4) { QUERY3LINEITEMLINEITEM_ORDERKEY = c0; QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3LINEITEM2CUSTOMER2_entry(const QUERY3LINEITEM2CUSTOMER2_entry& other) : QUERY3LINEITEMLINEITEM_ORDERKEY( other.QUERY3LINEITEMLINEITEM_ORDERKEY ), QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY( other.QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3LINEITEM2CUSTOMER2_entry& modify(const long c0, const long c1, const date c2, const long c3) { QUERY3LINEITEMLINEITEM_ORDERKEY = c0; QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    FORCE_INLINE QUERY3LINEITEM2CUSTOMER2_entry& modify0(const long c0) { QUERY3LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE QUERY3LINEITEM2CUSTOMER2_entry& modify1(const long c1) { QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3LINEITEM2CUSTOMER2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM2CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM2CUSTOMER2_entry& x, const QUERY3LINEITEM2CUSTOMER2_entry& y) {
      return x.QUERY3LINEITEMLINEITEM_ORDERKEY == y.QUERY3LINEITEMLINEITEM_ORDERKEY && x.QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY == y.QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3LINEITEM2CUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM2CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM2CUSTOMER2_entry& x, const QUERY3LINEITEM2CUSTOMER2_entry& y) {
      return x.QUERY3LINEITEMLINEITEM_ORDERKEY == y.QUERY3LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct QUERY3LINEITEM2CUSTOMER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3LINEITEM2CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3LINEITEM2CUSTOMER2_entry& x, const QUERY3LINEITEM2CUSTOMER2_entry& y) {
      return x.QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY == y.QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3LINEITEM2CUSTOMER2_entry,long,
    HashIndex<QUERY3LINEITEM2CUSTOMER2_entry,long,QUERY3LINEITEM2CUSTOMER2_mapkey0123_idxfn,true>,
    HashIndex<QUERY3LINEITEM2CUSTOMER2_entry,long,QUERY3LINEITEM2CUSTOMER2_mapkey0_idxfn,false>,
    HashIndex<QUERY3LINEITEM2CUSTOMER2_entry,long,QUERY3LINEITEM2CUSTOMER2_mapkey1_idxfn,false>
  > QUERY3LINEITEM2CUSTOMER2_map;
  typedef HashIndex<QUERY3LINEITEM2CUSTOMER2_entry,long,QUERY3LINEITEM2CUSTOMER2_mapkey0123_idxfn,true> HashIndex_QUERY3LINEITEM2CUSTOMER2_map_0123;
  typedef HashIndex<QUERY3LINEITEM2CUSTOMER2_entry,long,QUERY3LINEITEM2CUSTOMER2_mapkey0_idxfn,false> HashIndex_QUERY3LINEITEM2CUSTOMER2_map_0;
  typedef HashIndex<QUERY3LINEITEM2CUSTOMER2_entry,long,QUERY3LINEITEM2CUSTOMER2_mapkey1_idxfn,false> HashIndex_QUERY3LINEITEM2CUSTOMER2_map_1;
  
  struct QUERY3ORDERS2_entry {
    long QUERY3ORDERSORDERS_CUSTKEY; long __av; 
    explicit QUERY3ORDERS2_entry() { /*QUERY3ORDERSORDERS_CUSTKEY = 0L; __av = 0L; */ }
    explicit QUERY3ORDERS2_entry(const long c0, const long c1) { QUERY3ORDERSORDERS_CUSTKEY = c0; __av = c1; }
    QUERY3ORDERS2_entry(const QUERY3ORDERS2_entry& other) : QUERY3ORDERSORDERS_CUSTKEY( other.QUERY3ORDERSORDERS_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3ORDERS2_entry& modify(const long c0) { QUERY3ORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3ORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3ORDERS2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3ORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3ORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3ORDERS2_entry& x, const QUERY3ORDERS2_entry& y) {
      return x.QUERY3ORDERSORDERS_CUSTKEY == y.QUERY3ORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3ORDERS2_entry,long,
    HashIndex<QUERY3ORDERS2_entry,long,QUERY3ORDERS2_mapkey0_idxfn,true>
  > QUERY3ORDERS2_map;
  typedef HashIndex<QUERY3ORDERS2_entry,long,QUERY3ORDERS2_mapkey0_idxfn,true> HashIndex_QUERY3ORDERS2_map_0;
  
  struct QUERY3ORDERS3_entry {
    long QUERY3ORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY3ORDERS3_entry() { /*QUERY3ORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY3ORDERS3_entry(const long c0, const DOUBLE_TYPE c1) { QUERY3ORDERSORDERS_ORDERKEY = c0; __av = c1; }
    QUERY3ORDERS3_entry(const QUERY3ORDERS3_entry& other) : QUERY3ORDERSORDERS_ORDERKEY( other.QUERY3ORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3ORDERS3_entry& modify(const long c0) { QUERY3ORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3ORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3ORDERS3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3ORDERS3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3ORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3ORDERS3_entry& x, const QUERY3ORDERS3_entry& y) {
      return x.QUERY3ORDERSORDERS_ORDERKEY == y.QUERY3ORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3ORDERS3_entry,DOUBLE_TYPE,
    HashIndex<QUERY3ORDERS3_entry,DOUBLE_TYPE,QUERY3ORDERS3_mapkey0_idxfn,true>
  > QUERY3ORDERS3_map;
  typedef HashIndex<QUERY3ORDERS3_entry,DOUBLE_TYPE,QUERY3ORDERS3_mapkey0_idxfn,true> HashIndex_QUERY3ORDERS3_map_0;
  
  struct QUERY3CUSTOMER2_entry {
    long ORDERS_ORDERKEY; long QUERY3CUSTOMERCUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; DOUBLE_TYPE __av; 
    explicit QUERY3CUSTOMER2_entry() { /*ORDERS_ORDERKEY = 0L; QUERY3CUSTOMERCUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0.0; */ }
    explicit QUERY3CUSTOMER2_entry(const long c0, const long c1, const date c2, const long c3, const DOUBLE_TYPE c4) { ORDERS_ORDERKEY = c0; QUERY3CUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3CUSTOMER2_entry(const QUERY3CUSTOMER2_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), QUERY3CUSTOMERCUSTOMER_CUSTKEY( other.QUERY3CUSTOMERCUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3CUSTOMER2_entry& modify(const long c0, const long c1, const date c2, const long c3) { ORDERS_ORDERKEY = c0; QUERY3CUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    FORCE_INLINE QUERY3CUSTOMER2_entry& modify1(const long c1) { QUERY3CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3CUSTOMER2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.QUERY3CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3CUSTOMER2_entry& x, const QUERY3CUSTOMER2_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.QUERY3CUSTOMERCUSTOMER_CUSTKEY == y.QUERY3CUSTOMERCUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3CUSTOMER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3CUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3CUSTOMER2_entry& x, const QUERY3CUSTOMER2_entry& y) {
      return x.QUERY3CUSTOMERCUSTOMER_CUSTKEY == y.QUERY3CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3CUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<QUERY3CUSTOMER2_entry,DOUBLE_TYPE,QUERY3CUSTOMER2_mapkey0123_idxfn,true>,
    HashIndex<QUERY3CUSTOMER2_entry,DOUBLE_TYPE,QUERY3CUSTOMER2_mapkey1_idxfn,false>
  > QUERY3CUSTOMER2_map;
  typedef HashIndex<QUERY3CUSTOMER2_entry,DOUBLE_TYPE,QUERY3CUSTOMER2_mapkey0123_idxfn,true> HashIndex_QUERY3CUSTOMER2_map_0123;
  typedef HashIndex<QUERY3CUSTOMER2_entry,DOUBLE_TYPE,QUERY3CUSTOMER2_mapkey1_idxfn,false> HashIndex_QUERY3CUSTOMER2_map_1;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const QUERY3_map& _QUERY3 = get_QUERY3();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(QUERY3), _QUERY3, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const QUERY3_map& get_QUERY3() const {
      return QUERY3;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    QUERY3_map QUERY3;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = STRING_TYPE("BUILDING");
      c1 = Udate(STRING_TYPE("1995-3-15"));
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_QUERY3LINEITEM2_map_0* i1 = static_cast<HashIndex_QUERY3LINEITEM2_map_0*>(QUERY3LINEITEM2.index[1]);
          const HASH_RES_t h1 = QUERY3LINEITEM2_mapkey0_idxfn::hash(se2.modify0(lineitem_orderkey));
          HashIndex_QUERY3LINEITEM2_map_0::IdxNode* n1 = static_cast<HashIndex_QUERY3LINEITEM2_map_0::IdxNode*>(i1->slice(se2, h1));
          QUERY3LINEITEM2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              date orders_orderdate = e1->ORDERS_ORDERDATE;
              long orders_shippriority = e1->ORDERS_SHIPPRIORITY;
              long v1 = e1->__av;
              (/*if */(lineitem_shipdate > c1) ? QUERY3.addOrDelOnZero(se1.modify(lineitem_orderkey,orders_orderdate,orders_shippriority),(v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  QUERY3LINEITEM2_mapkey0_idxfn::equals(se2, *e1)); 
          }
        }(/*if */(lineitem_shipdate > c1) ? QUERY3ORDERS3.addOrDelOnZero(se3.modify(lineitem_orderkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        { //slice 
          const HashIndex_QUERY3LINEITEM2CUSTOMER2_map_0* i2 = static_cast<HashIndex_QUERY3LINEITEM2CUSTOMER2_map_0*>(QUERY3LINEITEM2CUSTOMER2.index[1]);
          const HASH_RES_t h2 = QUERY3LINEITEM2CUSTOMER2_mapkey0_idxfn::hash(se5.modify0(lineitem_orderkey));
          HashIndex_QUERY3LINEITEM2CUSTOMER2_map_0::IdxNode* n2 = static_cast<HashIndex_QUERY3LINEITEM2CUSTOMER2_map_0::IdxNode*>(i2->slice(se5, h2));
          QUERY3LINEITEM2CUSTOMER2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long query3customercustomer_custkey = e2->QUERY3LINEITEM2CUSTOMERCUSTOMER_CUSTKEY;
              date orders_orderdate = e2->ORDERS_ORDERDATE;
              long orders_shippriority = e2->ORDERS_SHIPPRIORITY;
              long v2 = e2->__av;
              (/*if */(lineitem_shipdate > c1) ? QUERY3CUSTOMER2.addOrDelOnZero(se4.modify(lineitem_orderkey,query3customercustomer_custkey,orders_orderdate,orders_shippriority),(v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  QUERY3LINEITEM2CUSTOMER2_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(c1 > orders_orderdate) ? QUERY3.addOrDelOnZero(se6.modify(orders_orderkey,orders_orderdate,orders_shippriority),(QUERY3ORDERS2.getValueOrDefault(se7.modify(orders_custkey)) * QUERY3ORDERS3.getValueOrDefault(se8.modify(orders_orderkey)))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3LINEITEM2.addOrDelOnZero(se9.modify(orders_orderkey,orders_orderdate,orders_shippriority),QUERY3ORDERS2.getValueOrDefault(se10.modify(orders_custkey))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3LINEITEM2CUSTOMER2.addOrDelOnZero(se11.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),1L) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3CUSTOMER2.addOrDelOnZero(se12.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),QUERY3ORDERS3.getValueOrDefault(se13.modify(orders_orderkey))) : (void)0);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_QUERY3CUSTOMER2_map_1* i3 = static_cast<HashIndex_QUERY3CUSTOMER2_map_1*>(QUERY3CUSTOMER2.index[1]);
          const HASH_RES_t h3 = QUERY3CUSTOMER2_mapkey1_idxfn::hash(se15.modify1(customer_custkey));
          HashIndex_QUERY3CUSTOMER2_map_1::IdxNode* n3 = static_cast<HashIndex_QUERY3CUSTOMER2_map_1::IdxNode*>(i3->slice(se15, h3));
          QUERY3CUSTOMER2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long orders_orderkey = e3->ORDERS_ORDERKEY;
              date orders_orderdate = e3->ORDERS_ORDERDATE;
              long orders_shippriority = e3->ORDERS_SHIPPRIORITY;
              DOUBLE_TYPE v3 = e3->__av;
              (/*if */(customer_mktsegment == c2) ? QUERY3.addOrDelOnZero(se14.modify(orders_orderkey,orders_orderdate,orders_shippriority),v3) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  QUERY3CUSTOMER2_mapkey1_idxfn::equals(se15, *e3)); 
          }
        }{ //slice 
          const HashIndex_QUERY3LINEITEM2CUSTOMER2_map_1* i4 = static_cast<HashIndex_QUERY3LINEITEM2CUSTOMER2_map_1*>(QUERY3LINEITEM2CUSTOMER2.index[2]);
          const HASH_RES_t h4 = QUERY3LINEITEM2CUSTOMER2_mapkey1_idxfn::hash(se17.modify1(customer_custkey));
          HashIndex_QUERY3LINEITEM2CUSTOMER2_map_1::IdxNode* n4 = static_cast<HashIndex_QUERY3LINEITEM2CUSTOMER2_map_1::IdxNode*>(i4->slice(se17, h4));
          QUERY3LINEITEM2CUSTOMER2_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long query3lineitemlineitem_orderkey = e4->QUERY3LINEITEMLINEITEM_ORDERKEY;
              date orders_orderdate = e4->ORDERS_ORDERDATE;
              long orders_shippriority = e4->ORDERS_SHIPPRIORITY;
              long v4 = e4->__av;
              (/*if */(customer_mktsegment == c2) ? QUERY3LINEITEM2.addOrDelOnZero(se16.modify(query3lineitemlineitem_orderkey,orders_orderdate,orders_shippriority),v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  QUERY3LINEITEM2CUSTOMER2_mapkey1_idxfn::equals(se17, *e4)); 
          }
        }(/*if */(customer_mktsegment == c2) ? QUERY3ORDERS2.addOrDelOnZero(se18.modify(customer_custkey),1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY3_entry se1;
    QUERY3LINEITEM2_entry se2;
    QUERY3ORDERS3_entry se3;
    QUERY3CUSTOMER2_entry se4;
    QUERY3LINEITEM2CUSTOMER2_entry se5;
    QUERY3_entry se6;
    QUERY3ORDERS2_entry se7;
    QUERY3ORDERS3_entry se8;
    QUERY3LINEITEM2_entry se9;
    QUERY3ORDERS2_entry se10;
    QUERY3LINEITEM2CUSTOMER2_entry se11;
    QUERY3CUSTOMER2_entry se12;
    QUERY3ORDERS3_entry se13;
    QUERY3_entry se14;
    QUERY3CUSTOMER2_entry se15;
    QUERY3LINEITEM2_entry se16;
    QUERY3LINEITEM2CUSTOMER2_entry se17;
    QUERY3ORDERS2_entry se18;
  
    /* Data structures used for storing materialized views */
    QUERY3LINEITEM2_map QUERY3LINEITEM2;
    QUERY3LINEITEM2CUSTOMER2_map QUERY3LINEITEM2CUSTOMER2;
    QUERY3ORDERS2_map QUERY3ORDERS2;
    QUERY3ORDERS3_map QUERY3ORDERS3;
    QUERY3CUSTOMER2_map QUERY3CUSTOMER2;
    
    /*const static*/ STRING_TYPE c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
