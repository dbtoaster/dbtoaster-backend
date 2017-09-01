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
  struct QUERY18_entry {
    STRING_TYPE C_NAME; long C_CUSTKEY; long O_ORDERKEY; date O_ORDERDATE; DOUBLE_TYPE O_TOTALPRICE; DOUBLE_TYPE __av; 
    explicit QUERY18_entry() { /*C_NAME = ""; C_CUSTKEY = 0L; O_ORDERKEY = 0L; O_ORDERDATE = 00000000; O_TOTALPRICE = 0.0; __av = 0.0; */ }
    explicit QUERY18_entry(const STRING_TYPE& c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { C_NAME = c0; C_CUSTKEY = c1; O_ORDERKEY = c2; O_ORDERDATE = c3; O_TOTALPRICE = c4; __av = c5; }
    QUERY18_entry(const QUERY18_entry& other) : C_NAME( other.C_NAME ), C_CUSTKEY( other.C_CUSTKEY ), O_ORDERKEY( other.O_ORDERKEY ), O_ORDERDATE( other.O_ORDERDATE ), O_TOTALPRICE( other.O_TOTALPRICE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18_entry& modify(const STRING_TYPE& c0, const long c1, const long c2, const date c3, const DOUBLE_TYPE c4) { C_NAME = c0; C_CUSTKEY = c1; O_ORDERKEY = c2; O_ORDERDATE = c3; O_TOTALPRICE = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NAME);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.O_ORDERDATE);
      hash_combine(h, e.O_TOTALPRICE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18_entry& x, const QUERY18_entry& y) {
      return x.C_NAME == y.C_NAME && x.C_CUSTKEY == y.C_CUSTKEY && x.O_ORDERKEY == y.O_ORDERKEY && x.O_ORDERDATE == y.O_ORDERDATE && x.O_TOTALPRICE == y.O_TOTALPRICE;
    }
  };
  
  typedef MultiHashMap<QUERY18_entry,DOUBLE_TYPE,
    HashIndex<QUERY18_entry,DOUBLE_TYPE,QUERY18_mapkey01234_idxfn,true>
  > QUERY18_map;
  typedef HashIndex<QUERY18_entry,DOUBLE_TYPE,QUERY18_mapkey01234_idxfn,true> HashIndex_QUERY18_map_01234;
  
  struct QUERY18LINEITEM3_entry {
    long QUERY18LINEITEMLINEITEM_ORDERKEY; long C_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; STRING_TYPE C_NAME; long __av; 
    explicit QUERY18LINEITEM3_entry() { /*QUERY18LINEITEMLINEITEM_ORDERKEY = 0L; C_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; C_NAME = ""; __av = 0L; */ }
    explicit QUERY18LINEITEM3_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const STRING_TYPE& c4, const long c5) { QUERY18LINEITEMLINEITEM_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; C_NAME = c4; __av = c5; }
    QUERY18LINEITEM3_entry(const QUERY18LINEITEM3_entry& other) : QUERY18LINEITEMLINEITEM_ORDERKEY( other.QUERY18LINEITEMLINEITEM_ORDERKEY ), C_CUSTKEY( other.C_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), C_NAME( other.C_NAME ), __av( other.__av ) {}
    FORCE_INLINE QUERY18LINEITEM3_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const STRING_TYPE& c4) { QUERY18LINEITEMLINEITEM_ORDERKEY = c0; C_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; C_NAME = c4;  return *this; }
    FORCE_INLINE QUERY18LINEITEM3_entry& modify0(const long c0) { QUERY18LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18LINEITEM3_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      hash_combine(h, e.C_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM3_entry& x, const QUERY18LINEITEM3_entry& y) {
      return x.QUERY18LINEITEMLINEITEM_ORDERKEY == y.QUERY18LINEITEMLINEITEM_ORDERKEY && x.C_CUSTKEY == y.C_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE && x.C_NAME == y.C_NAME;
    }
  };
  
  struct QUERY18LINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM3_entry& x, const QUERY18LINEITEM3_entry& y) {
      return x.QUERY18LINEITEMLINEITEM_ORDERKEY == y.QUERY18LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18LINEITEM3_entry,long,
    HashIndex<QUERY18LINEITEM3_entry,long,QUERY18LINEITEM3_mapkey01234_idxfn,true>,
    HashIndex<QUERY18LINEITEM3_entry,long,QUERY18LINEITEM3_mapkey0_idxfn,false>
  > QUERY18LINEITEM3_map;
  typedef HashIndex<QUERY18LINEITEM3_entry,long,QUERY18LINEITEM3_mapkey01234_idxfn,true> HashIndex_QUERY18LINEITEM3_map_01234;
  typedef HashIndex<QUERY18LINEITEM3_entry,long,QUERY18LINEITEM3_mapkey0_idxfn,false> HashIndex_QUERY18LINEITEM3_map_0;
  
  struct QUERY18LINEITEM3CUSTOMER1_entry {
    long QUERY18LINEITEMLINEITEM_ORDERKEY; long QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; long __av; 
    explicit QUERY18LINEITEM3CUSTOMER1_entry() { /*QUERY18LINEITEMLINEITEM_ORDERKEY = 0L; QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0L; */ }
    explicit QUERY18LINEITEM3CUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const long c4) { QUERY18LINEITEMLINEITEM_ORDERKEY = c0; QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; __av = c4; }
    QUERY18LINEITEM3CUSTOMER1_entry(const QUERY18LINEITEM3CUSTOMER1_entry& other) : QUERY18LINEITEMLINEITEM_ORDERKEY( other.QUERY18LINEITEMLINEITEM_ORDERKEY ), QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY( other.QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18LINEITEM3CUSTOMER1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3) { QUERY18LINEITEMLINEITEM_ORDERKEY = c0; QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE QUERY18LINEITEM3CUSTOMER1_entry& modify0(const long c0) { QUERY18LINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE QUERY18LINEITEM3CUSTOMER1_entry& modify1(const long c1) { QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18LINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18LINEITEM3CUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM3CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18LINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM3CUSTOMER1_entry& x, const QUERY18LINEITEM3CUSTOMER1_entry& y) {
      return x.QUERY18LINEITEMLINEITEM_ORDERKEY == y.QUERY18LINEITEMLINEITEM_ORDERKEY && x.QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY == y.QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18LINEITEM3CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM3CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18LINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM3CUSTOMER1_entry& x, const QUERY18LINEITEM3CUSTOMER1_entry& y) {
      return x.QUERY18LINEITEMLINEITEM_ORDERKEY == y.QUERY18LINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct QUERY18LINEITEM3CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18LINEITEM3CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18LINEITEM3CUSTOMER1_entry& x, const QUERY18LINEITEM3CUSTOMER1_entry& y) {
      return x.QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY == y.QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18LINEITEM3CUSTOMER1_entry,long,
    HashIndex<QUERY18LINEITEM3CUSTOMER1_entry,long,QUERY18LINEITEM3CUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY18LINEITEM3CUSTOMER1_entry,long,QUERY18LINEITEM3CUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<QUERY18LINEITEM3CUSTOMER1_entry,long,QUERY18LINEITEM3CUSTOMER1_mapkey1_idxfn,false>
  > QUERY18LINEITEM3CUSTOMER1_map;
  typedef HashIndex<QUERY18LINEITEM3CUSTOMER1_entry,long,QUERY18LINEITEM3CUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY18LINEITEM3CUSTOMER1_map_0123;
  typedef HashIndex<QUERY18LINEITEM3CUSTOMER1_entry,long,QUERY18LINEITEM3CUSTOMER1_mapkey0_idxfn,false> HashIndex_QUERY18LINEITEM3CUSTOMER1_map_0;
  typedef HashIndex<QUERY18LINEITEM3CUSTOMER1_entry,long,QUERY18LINEITEM3CUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY18LINEITEM3CUSTOMER1_map_1;
  
  struct QUERY18ORDERS2_entry {
    long QUERY18ORDERSORDERS_CUSTKEY; STRING_TYPE C_NAME; long __av; 
    explicit QUERY18ORDERS2_entry() { /*QUERY18ORDERSORDERS_CUSTKEY = 0L; C_NAME = ""; __av = 0L; */ }
    explicit QUERY18ORDERS2_entry(const long c0, const STRING_TYPE& c1, const long c2) { QUERY18ORDERSORDERS_CUSTKEY = c0; C_NAME = c1; __av = c2; }
    QUERY18ORDERS2_entry(const QUERY18ORDERS2_entry& other) : QUERY18ORDERSORDERS_CUSTKEY( other.QUERY18ORDERSORDERS_CUSTKEY ), C_NAME( other.C_NAME ), __av( other.__av ) {}
    FORCE_INLINE QUERY18ORDERS2_entry& modify(const long c0, const STRING_TYPE& c1) { QUERY18ORDERSORDERS_CUSTKEY = c0; C_NAME = c1;  return *this; }
    FORCE_INLINE QUERY18ORDERS2_entry& modify0(const long c0) { QUERY18ORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18ORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18ORDERS2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18ORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18ORDERSORDERS_CUSTKEY);
      hash_combine(h, e.C_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18ORDERS2_entry& x, const QUERY18ORDERS2_entry& y) {
      return x.QUERY18ORDERSORDERS_CUSTKEY == y.QUERY18ORDERSORDERS_CUSTKEY && x.C_NAME == y.C_NAME;
    }
  };
  
  struct QUERY18ORDERS2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18ORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18ORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18ORDERS2_entry& x, const QUERY18ORDERS2_entry& y) {
      return x.QUERY18ORDERSORDERS_CUSTKEY == y.QUERY18ORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18ORDERS2_entry,long,
    HashIndex<QUERY18ORDERS2_entry,long,QUERY18ORDERS2_mapkey01_idxfn,true>,
    HashIndex<QUERY18ORDERS2_entry,long,QUERY18ORDERS2_mapkey0_idxfn,false>
  > QUERY18ORDERS2_map;
  typedef HashIndex<QUERY18ORDERS2_entry,long,QUERY18ORDERS2_mapkey01_idxfn,true> HashIndex_QUERY18ORDERS2_map_01;
  typedef HashIndex<QUERY18ORDERS2_entry,long,QUERY18ORDERS2_mapkey0_idxfn,false> HashIndex_QUERY18ORDERS2_map_0;
  
  struct QUERY18CUSTOMER1_entry {
    long O_ORDERKEY; long QUERY18CUSTOMERCUSTOMER_CUSTKEY; DOUBLE_TYPE O_TOTALPRICE; date O_ORDERDATE; DOUBLE_TYPE __av; 
    explicit QUERY18CUSTOMER1_entry() { /*O_ORDERKEY = 0L; QUERY18CUSTOMERCUSTOMER_CUSTKEY = 0L; O_TOTALPRICE = 0.0; O_ORDERDATE = 00000000; __av = 0.0; */ }
    explicit QUERY18CUSTOMER1_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3, const DOUBLE_TYPE c4) { O_ORDERKEY = c0; QUERY18CUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3; __av = c4; }
    QUERY18CUSTOMER1_entry(const QUERY18CUSTOMER1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), QUERY18CUSTOMERCUSTOMER_CUSTKEY( other.QUERY18CUSTOMERCUSTOMER_CUSTKEY ), O_TOTALPRICE( other.O_TOTALPRICE ), O_ORDERDATE( other.O_ORDERDATE ), __av( other.__av ) {}
    FORCE_INLINE QUERY18CUSTOMER1_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const date c3) { O_ORDERKEY = c0; QUERY18CUSTOMERCUSTOMER_CUSTKEY = c1; O_TOTALPRICE = c2; O_ORDERDATE = c3;  return *this; }
    FORCE_INLINE QUERY18CUSTOMER1_entry& modify1(const long c1) { QUERY18CUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY18CUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_TOTALPRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18CUSTOMER1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      hash_combine(h, e.QUERY18CUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.O_TOTALPRICE);
      hash_combine(h, e.O_ORDERDATE);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18CUSTOMER1_entry& x, const QUERY18CUSTOMER1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY && x.QUERY18CUSTOMERCUSTOMER_CUSTKEY == y.QUERY18CUSTOMERCUSTOMER_CUSTKEY && x.O_TOTALPRICE == y.O_TOTALPRICE && x.O_ORDERDATE == y.O_ORDERDATE;
    }
  };
  
  struct QUERY18CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY18CUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18CUSTOMER1_entry& x, const QUERY18CUSTOMER1_entry& y) {
      return x.QUERY18CUSTOMERCUSTOMER_CUSTKEY == y.QUERY18CUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey0123_idxfn,true>,
    HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey1_idxfn,false>
  > QUERY18CUSTOMER1_map;
  typedef HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey0123_idxfn,true> HashIndex_QUERY18CUSTOMER1_map_0123;
  typedef HashIndex<QUERY18CUSTOMER1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_mapkey1_idxfn,false> HashIndex_QUERY18CUSTOMER1_map_1;
  
  struct QUERY18CUSTOMER1_L1_1_entry {
    long O_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY18CUSTOMER1_L1_1_entry() { /*O_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY18CUSTOMER1_L1_1_entry(const long c0, const DOUBLE_TYPE c1) { O_ORDERKEY = c0; __av = c1; }
    QUERY18CUSTOMER1_L1_1_entry(const QUERY18CUSTOMER1_L1_1_entry& other) : O_ORDERKEY( other.O_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY18CUSTOMER1_L1_1_entry& modify(const long c0) { O_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, O_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY18CUSTOMER1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY18CUSTOMER1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.O_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY18CUSTOMER1_L1_1_entry& x, const QUERY18CUSTOMER1_L1_1_entry& y) {
      return x.O_ORDERKEY == y.O_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY18CUSTOMER1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<QUERY18CUSTOMER1_L1_1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_L1_1_mapkey0_idxfn,true>
  > QUERY18CUSTOMER1_L1_1_map;
  typedef HashIndex<QUERY18CUSTOMER1_L1_1_entry,DOUBLE_TYPE,QUERY18CUSTOMER1_L1_1_mapkey0_idxfn,true> HashIndex_QUERY18CUSTOMER1_L1_1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const QUERY18_map& _QUERY18 = get_QUERY18();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(QUERY18), _QUERY18, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const QUERY18_map& get_QUERY18() const {
      return QUERY18;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    QUERY18_map QUERY18;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg1 = 0L;
        DOUBLE_TYPE l1 = (QUERY18CUSTOMER1_L1_1.getValueOrDefault(se3.modify(lineitem_orderkey)) + lineitem_quantity);
        (/*if */(l1 > 100L) ? agg1 += 1L : 0L);
        long agg2 = 0L;
        DOUBLE_TYPE l2 = QUERY18CUSTOMER1_L1_1.getValueOrDefault(se5.modify(lineitem_orderkey));
        (/*if */(l2 > 100L) ? agg2 += 1L : 0L);
        { //slice 
          const HashIndex_QUERY18LINEITEM3_map_0* i1 = static_cast<HashIndex_QUERY18LINEITEM3_map_0*>(QUERY18LINEITEM3.index[1]);
          const HASH_RES_t h1 = QUERY18LINEITEM3_mapkey0_idxfn::hash(se6.modify0(lineitem_orderkey));
          HashIndex_QUERY18LINEITEM3_map_0::IdxNode* n1 = static_cast<HashIndex_QUERY18LINEITEM3_map_0::IdxNode*>(i1->slice(se6, h1));
          QUERY18LINEITEM3_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long c_custkey = e1->C_CUSTKEY;
              DOUBLE_TYPE o_totalprice = e1->O_TOTALPRICE;
              date o_orderdate = e1->O_ORDERDATE;
              STRING_TYPE c_name = e1->C_NAME;
              long v1 = e1->__av;
              QUERY18.addOrDelOnZero(se1.modify(c_name,c_custkey,lineitem_orderkey,o_orderdate,o_totalprice),((((QUERY18CUSTOMER1_L1_1.getValueOrDefault(se2.modify(lineitem_orderkey)) + lineitem_quantity) * agg1) + (QUERY18CUSTOMER1_L1_1.getValueOrDefault(se4.modify(lineitem_orderkey)) * (agg2 * -1L))) * v1));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  QUERY18LINEITEM3_mapkey0_idxfn::equals(se6, *e1)); 
          }
        }{ //slice 
          const HashIndex_QUERY18LINEITEM3CUSTOMER1_map_0* i2 = static_cast<HashIndex_QUERY18LINEITEM3CUSTOMER1_map_0*>(QUERY18LINEITEM3CUSTOMER1.index[1]);
          const HASH_RES_t h2 = QUERY18LINEITEM3CUSTOMER1_mapkey0_idxfn::hash(se8.modify0(lineitem_orderkey));
          HashIndex_QUERY18LINEITEM3CUSTOMER1_map_0::IdxNode* n2 = static_cast<HashIndex_QUERY18LINEITEM3CUSTOMER1_map_0::IdxNode*>(i2->slice(se8, h2));
          QUERY18LINEITEM3CUSTOMER1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long query18customercustomer_custkey = e2->QUERY18LINEITEM3CUSTOMERCUSTOMER_CUSTKEY;
              DOUBLE_TYPE o_totalprice = e2->O_TOTALPRICE;
              date o_orderdate = e2->O_ORDERDATE;
              long v2 = e2->__av;
              QUERY18CUSTOMER1.addOrDelOnZero(se7.modify(lineitem_orderkey,query18customercustomer_custkey,o_totalprice,o_orderdate),(v2 * lineitem_quantity));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  QUERY18LINEITEM3CUSTOMER1_mapkey0_idxfn::equals(se8, *e2)); 
          }
        }QUERY18CUSTOMER1_L1_1.addOrDelOnZero(se9.modify(lineitem_orderkey),lineitem_quantity);
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg3 = 0L;
        DOUBLE_TYPE l3 = QUERY18CUSTOMER1_L1_1.getValueOrDefault(se12.modify(orders_orderkey));
        (/*if */(l3 > 100L) ? agg3 += 1L : 0L);
        { //slice 
          const HashIndex_QUERY18ORDERS2_map_0* i3 = static_cast<HashIndex_QUERY18ORDERS2_map_0*>(QUERY18ORDERS2.index[1]);
          const HASH_RES_t h3 = QUERY18ORDERS2_mapkey0_idxfn::hash(se13.modify0(orders_custkey));
          HashIndex_QUERY18ORDERS2_map_0::IdxNode* n3 = static_cast<HashIndex_QUERY18ORDERS2_map_0::IdxNode*>(i3->slice(se13, h3));
          QUERY18ORDERS2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              STRING_TYPE c_name = e3->C_NAME;
              long v3 = e3->__av;
              QUERY18.addOrDelOnZero(se10.modify(c_name,orders_custkey,orders_orderkey,orders_orderdate,orders_totalprice),(QUERY18CUSTOMER1_L1_1.getValueOrDefault(se11.modify(orders_orderkey)) * (agg3 * v3)));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  QUERY18ORDERS2_mapkey0_idxfn::equals(se13, *e3)); 
          }
        }{ //slice 
          const HashIndex_QUERY18ORDERS2_map_0* i4 = static_cast<HashIndex_QUERY18ORDERS2_map_0*>(QUERY18ORDERS2.index[1]);
          const HASH_RES_t h4 = QUERY18ORDERS2_mapkey0_idxfn::hash(se15.modify0(orders_custkey));
          HashIndex_QUERY18ORDERS2_map_0::IdxNode* n4 = static_cast<HashIndex_QUERY18ORDERS2_map_0::IdxNode*>(i4->slice(se15, h4));
          QUERY18ORDERS2_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              STRING_TYPE c_name = e4->C_NAME;
              long v4 = e4->__av;
              QUERY18LINEITEM3.addOrDelOnZero(se14.modify(orders_orderkey,orders_custkey,orders_totalprice,orders_orderdate,c_name),v4);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  QUERY18ORDERS2_mapkey0_idxfn::equals(se15, *e4)); 
          }
        }QUERY18LINEITEM3CUSTOMER1.addOrDelOnZero(se16.modify(orders_orderkey,orders_custkey,orders_totalprice,orders_orderdate),1L);
        QUERY18CUSTOMER1.addOrDelOnZero(se17.modify(orders_orderkey,orders_custkey,orders_totalprice,orders_orderdate),QUERY18CUSTOMER1_L1_1.getValueOrDefault(se18.modify(orders_orderkey)));
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_QUERY18CUSTOMER1_map_1* i5 = static_cast<HashIndex_QUERY18CUSTOMER1_map_1*>(QUERY18CUSTOMER1.index[1]);
          const HASH_RES_t h5 = QUERY18CUSTOMER1_mapkey1_idxfn::hash(se21.modify1(customer_custkey));
          HashIndex_QUERY18CUSTOMER1_map_1::IdxNode* n5 = static_cast<HashIndex_QUERY18CUSTOMER1_map_1::IdxNode*>(i5->slice(se21, h5));
          QUERY18CUSTOMER1_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long o_orderkey = e5->O_ORDERKEY;
              DOUBLE_TYPE o_totalprice = e5->O_TOTALPRICE;
              date o_orderdate = e5->O_ORDERDATE;
              DOUBLE_TYPE v5 = e5->__av;
              long agg4 = 0L;
              DOUBLE_TYPE l4 = QUERY18CUSTOMER1_L1_1.getValueOrDefault(se20.modify(o_orderkey));
              (/*if */(l4 > 100L) ? agg4 += 1L : 0L);
              QUERY18.addOrDelOnZero(se19.modify(customer_name,customer_custkey,o_orderkey,o_orderdate,o_totalprice),(v5 * agg4));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  QUERY18CUSTOMER1_mapkey1_idxfn::equals(se21, *e5)); 
          }
        }{ //slice 
          const HashIndex_QUERY18LINEITEM3CUSTOMER1_map_1* i6 = static_cast<HashIndex_QUERY18LINEITEM3CUSTOMER1_map_1*>(QUERY18LINEITEM3CUSTOMER1.index[2]);
          const HASH_RES_t h6 = QUERY18LINEITEM3CUSTOMER1_mapkey1_idxfn::hash(se23.modify1(customer_custkey));
          HashIndex_QUERY18LINEITEM3CUSTOMER1_map_1::IdxNode* n6 = static_cast<HashIndex_QUERY18LINEITEM3CUSTOMER1_map_1::IdxNode*>(i6->slice(se23, h6));
          QUERY18LINEITEM3CUSTOMER1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long query18lineitemlineitem_orderkey = e6->QUERY18LINEITEMLINEITEM_ORDERKEY;
              DOUBLE_TYPE o_totalprice = e6->O_TOTALPRICE;
              date o_orderdate = e6->O_ORDERDATE;
              long v6 = e6->__av;
              QUERY18LINEITEM3.addOrDelOnZero(se22.modify(query18lineitemlineitem_orderkey,customer_custkey,o_totalprice,o_orderdate,customer_name),v6);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  QUERY18LINEITEM3CUSTOMER1_mapkey1_idxfn::equals(se23, *e6)); 
          }
        }QUERY18ORDERS2.addOrDelOnZero(se24.modify(customer_custkey,customer_name),1L);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY18_entry se1;
    QUERY18CUSTOMER1_L1_1_entry se2;
    QUERY18CUSTOMER1_L1_1_entry se3;
    QUERY18CUSTOMER1_L1_1_entry se4;
    QUERY18CUSTOMER1_L1_1_entry se5;
    QUERY18LINEITEM3_entry se6;
    QUERY18CUSTOMER1_entry se7;
    QUERY18LINEITEM3CUSTOMER1_entry se8;
    QUERY18CUSTOMER1_L1_1_entry se9;
    QUERY18_entry se10;
    QUERY18CUSTOMER1_L1_1_entry se11;
    QUERY18CUSTOMER1_L1_1_entry se12;
    QUERY18ORDERS2_entry se13;
    QUERY18LINEITEM3_entry se14;
    QUERY18ORDERS2_entry se15;
    QUERY18LINEITEM3CUSTOMER1_entry se16;
    QUERY18CUSTOMER1_entry se17;
    QUERY18CUSTOMER1_L1_1_entry se18;
    QUERY18_entry se19;
    QUERY18CUSTOMER1_L1_1_entry se20;
    QUERY18CUSTOMER1_entry se21;
    QUERY18LINEITEM3_entry se22;
    QUERY18LINEITEM3CUSTOMER1_entry se23;
    QUERY18ORDERS2_entry se24;
  
    /* Data structures used for storing materialized views */
    QUERY18LINEITEM3_map QUERY18LINEITEM3;
    QUERY18LINEITEM3CUSTOMER1_map QUERY18LINEITEM3CUSTOMER1;
    QUERY18ORDERS2_map QUERY18ORDERS2;
    QUERY18CUSTOMER1_map QUERY18CUSTOMER1;
    QUERY18CUSTOMER1_L1_1_map QUERY18CUSTOMER1_L1_1;
    
    
  
  };

}
