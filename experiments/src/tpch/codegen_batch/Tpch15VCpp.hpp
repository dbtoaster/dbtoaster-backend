#include <sys/time.h>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "hashmap.hpp"
#include "serialization.hpp"
#include "tpch.hpp"

#define ELEM_SEPARATOR "\n\t\t\t"

namespace dbtoaster {
  
  /* Definitions of auxiliary maps for storing materialized views. */
  struct DELTA_LINEITEM_entry {
    long lineitem_orderkey; long lineitem_partkey; long lineitem_suppkey; long lineitem_linenumber; DOUBLE_TYPE lineitem_quantity; DOUBLE_TYPE lineitem_extendedprice; DOUBLE_TYPE lineitem_discount; DOUBLE_TYPE lineitem_tax; STRING_TYPE lineitem_returnflag; STRING_TYPE lineitem_linestatus; date lineitem_shipdate; date lineitem_commitdate; date lineitem_receiptdate; STRING_TYPE lineitem_shipinstruct; STRING_TYPE lineitem_shipmode; STRING_TYPE lineitem_comment; long __av; 
    explicit DELTA_LINEITEM_entry() { /*lineitem_orderkey = 0L; lineitem_partkey = 0L; lineitem_suppkey = 0L; lineitem_linenumber = 0L; lineitem_quantity = 0.0; lineitem_extendedprice = 0.0; lineitem_discount = 0.0; lineitem_tax = 0.0; lineitem_returnflag = ""; lineitem_linestatus = ""; lineitem_shipdate = 00000000; lineitem_commitdate = 00000000; lineitem_receiptdate = 00000000; lineitem_shipinstruct = ""; lineitem_shipmode = ""; lineitem_comment = ""; __av = 0L; */ }
    explicit DELTA_LINEITEM_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const date c10, const date c11, const date c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const long c16) { lineitem_orderkey = c0; lineitem_partkey = c1; lineitem_suppkey = c2; lineitem_linenumber = c3; lineitem_quantity = c4; lineitem_extendedprice = c5; lineitem_discount = c6; lineitem_tax = c7; lineitem_returnflag = c8; lineitem_linestatus = c9; lineitem_shipdate = c10; lineitem_commitdate = c11; lineitem_receiptdate = c12; lineitem_shipinstruct = c13; lineitem_shipmode = c14; lineitem_comment = c15; __av = c16; }
    DELTA_LINEITEM_entry(const DELTA_LINEITEM_entry& other) : lineitem_orderkey( other.lineitem_orderkey ), lineitem_partkey( other.lineitem_partkey ), lineitem_suppkey( other.lineitem_suppkey ), lineitem_linenumber( other.lineitem_linenumber ), lineitem_quantity( other.lineitem_quantity ), lineitem_extendedprice( other.lineitem_extendedprice ), lineitem_discount( other.lineitem_discount ), lineitem_tax( other.lineitem_tax ), lineitem_returnflag( other.lineitem_returnflag ), lineitem_linestatus( other.lineitem_linestatus ), lineitem_shipdate( other.lineitem_shipdate ), lineitem_commitdate( other.lineitem_commitdate ), lineitem_receiptdate( other.lineitem_receiptdate ), lineitem_shipinstruct( other.lineitem_shipinstruct ), lineitem_shipmode( other.lineitem_shipmode ), lineitem_comment( other.lineitem_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_LINEITEM_entry& modify(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const date c10, const date c11, const date c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15) { lineitem_orderkey = c0; lineitem_partkey = c1; lineitem_suppkey = c2; lineitem_linenumber = c3; lineitem_quantity = c4; lineitem_extendedprice = c5; lineitem_discount = c6; lineitem_tax = c7; lineitem_returnflag = c8; lineitem_linestatus = c9; lineitem_shipdate = c10; lineitem_commitdate = c11; lineitem_receiptdate = c12; lineitem_shipinstruct = c13; lineitem_shipmode = c14; lineitem_comment = c15;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_linenumber);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_quantity);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_extendedprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_discount);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_tax);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_returnflag);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_linestatus);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_shipdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_commitdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_receiptdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_shipinstruct);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_shipmode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, lineitem_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_LINEITEM_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_LINEITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.lineitem_orderkey);
      hash_combine(h, e.lineitem_partkey);
      hash_combine(h, e.lineitem_suppkey);
      hash_combine(h, e.lineitem_linenumber);
      hash_combine(h, e.lineitem_quantity);
      hash_combine(h, e.lineitem_extendedprice);
      hash_combine(h, e.lineitem_discount);
      hash_combine(h, e.lineitem_tax);
      hash_combine(h, e.lineitem_returnflag);
      hash_combine(h, e.lineitem_linestatus);
      hash_combine(h, e.lineitem_shipdate);
      hash_combine(h, e.lineitem_commitdate);
      hash_combine(h, e.lineitem_receiptdate);
      hash_combine(h, e.lineitem_shipinstruct);
      hash_combine(h, e.lineitem_shipmode);
      hash_combine(h, e.lineitem_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_LINEITEM_entry& x, const DELTA_LINEITEM_entry& y) {
      return x.lineitem_orderkey == y.lineitem_orderkey && x.lineitem_partkey == y.lineitem_partkey && x.lineitem_suppkey == y.lineitem_suppkey && x.lineitem_linenumber == y.lineitem_linenumber && x.lineitem_quantity == y.lineitem_quantity && x.lineitem_extendedprice == y.lineitem_extendedprice && x.lineitem_discount == y.lineitem_discount && x.lineitem_tax == y.lineitem_tax && x.lineitem_returnflag == y.lineitem_returnflag && x.lineitem_linestatus == y.lineitem_linestatus && x.lineitem_shipdate == y.lineitem_shipdate && x.lineitem_commitdate == y.lineitem_commitdate && x.lineitem_receiptdate == y.lineitem_receiptdate && x.lineitem_shipinstruct == y.lineitem_shipinstruct && x.lineitem_shipmode == y.lineitem_shipmode && x.lineitem_comment == y.lineitem_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_LINEITEM_entry,long,
    HashIndex<DELTA_LINEITEM_entry,long,DELTA_LINEITEM_mapkey0123456789101112131415_idxfn,true>
  > DELTA_LINEITEM_map;
  typedef HashIndex<DELTA_LINEITEM_entry,long,DELTA_LINEITEM_mapkey0123456789101112131415_idxfn,true> HashIndex_DELTA_LINEITEM_map_0123456789101112131415;
  
  struct DELTA_SUPPLIER_entry {
    long supplier_suppkey; STRING_TYPE supplier_name; STRING_TYPE supplier_address; long supplier_nationkey; STRING_TYPE supplier_phone; DOUBLE_TYPE supplier_acctbal; STRING_TYPE supplier_comment; long __av; 
    explicit DELTA_SUPPLIER_entry() { /*supplier_suppkey = 0L; supplier_name = ""; supplier_address = ""; supplier_nationkey = 0L; supplier_phone = ""; supplier_acctbal = 0.0; supplier_comment = ""; __av = 0L; */ }
    explicit DELTA_SUPPLIER_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6, const long c7) { supplier_suppkey = c0; supplier_name = c1; supplier_address = c2; supplier_nationkey = c3; supplier_phone = c4; supplier_acctbal = c5; supplier_comment = c6; __av = c7; }
    DELTA_SUPPLIER_entry(const DELTA_SUPPLIER_entry& other) : supplier_suppkey( other.supplier_suppkey ), supplier_name( other.supplier_name ), supplier_address( other.supplier_address ), supplier_nationkey( other.supplier_nationkey ), supplier_phone( other.supplier_phone ), supplier_acctbal( other.supplier_acctbal ), supplier_comment( other.supplier_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_SUPPLIER_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const STRING_TYPE& c6) { supplier_suppkey = c0; supplier_name = c1; supplier_address = c2; supplier_nationkey = c3; supplier_phone = c4; supplier_acctbal = c5; supplier_comment = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_address);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_nationkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_phone);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_acctbal);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supplier_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_SUPPLIER_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_SUPPLIER_entry& e) {
      size_t h = 0;
      hash_combine(h, e.supplier_suppkey);
      hash_combine(h, e.supplier_name);
      hash_combine(h, e.supplier_address);
      hash_combine(h, e.supplier_nationkey);
      hash_combine(h, e.supplier_phone);
      hash_combine(h, e.supplier_acctbal);
      hash_combine(h, e.supplier_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_SUPPLIER_entry& x, const DELTA_SUPPLIER_entry& y) {
      return x.supplier_suppkey == y.supplier_suppkey && x.supplier_name == y.supplier_name && x.supplier_address == y.supplier_address && x.supplier_nationkey == y.supplier_nationkey && x.supplier_phone == y.supplier_phone && x.supplier_acctbal == y.supplier_acctbal && x.supplier_comment == y.supplier_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_SUPPLIER_entry,long,
    HashIndex<DELTA_SUPPLIER_entry,long,DELTA_SUPPLIER_mapkey0123456_idxfn,true>
  > DELTA_SUPPLIER_map;
  typedef HashIndex<DELTA_SUPPLIER_entry,long,DELTA_SUPPLIER_mapkey0123456_idxfn,true> HashIndex_DELTA_SUPPLIER_map_0123456;
  
  struct COUNT_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE R1_TOTAL_REVENUE; long __av; 
    explicit COUNT_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; R1_TOTAL_REVENUE = 0.0; __av = 0L; */ }
    explicit COUNT_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const long c5) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; R1_TOTAL_REVENUE = c4; __av = c5; }
    COUNT_entry(const COUNT_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), R1_TOTAL_REVENUE( other.R1_TOTAL_REVENUE ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; R1_TOTAL_REVENUE = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R1_TOTAL_REVENUE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.R1_TOTAL_REVENUE);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.R1_TOTAL_REVENUE == y.R1_TOTAL_REVENUE;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey01234_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey01234_idxfn,true> HashIndex_COUNT_map_01234;
  
  struct COUNTSUPPLIER1_DELTA_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; long __av; 
    explicit COUNTSUPPLIER1_DELTA_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; __av = 0L; */ }
    explicit COUNTSUPPLIER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; __av = c4; }
    COUNTSUPPLIER1_DELTA_entry(const COUNTSUPPLIER1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_DELTA_entry& x, const COUNTSUPPLIER1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_DELTA_entry,long,
    HashIndex<COUNTSUPPLIER1_DELTA_entry,long,COUNTSUPPLIER1_DELTA_mapkey0123_idxfn,true>
  > COUNTSUPPLIER1_DELTA_map;
  typedef HashIndex<COUNTSUPPLIER1_DELTA_entry,long,COUNTSUPPLIER1_DELTA_mapkey0123_idxfn,true> HashIndex_COUNTSUPPLIER1_DELTA_map_0123;
  
  struct COUNTLINEITEM1_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; long __av; 
    explicit COUNTLINEITEM1_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; __av = 0L; */ }
    explicit COUNTLINEITEM1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; __av = c4; }
    COUNTLINEITEM1_entry(const COUNTLINEITEM1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_entry& x, const COUNTLINEITEM1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_entry,long,
    HashIndex<COUNTLINEITEM1_entry,long,COUNTLINEITEM1_mapkey0123_idxfn,true>
  > COUNTLINEITEM1_map;
  typedef HashIndex<COUNTLINEITEM1_entry,long,COUNTLINEITEM1_mapkey0123_idxfn,true> HashIndex_COUNTLINEITEM1_map_0123;
  
  struct COUNTLINEITEM1_E2_1_entry {
    long S_SUPPKEY; long __av; 
    explicit COUNTLINEITEM1_E2_1_entry() { /*S_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTLINEITEM1_E2_1_entry(const long c0, const long c1) { S_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_E2_1_entry(const COUNTLINEITEM1_E2_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_E2_1_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_E2_1_entry& x, const COUNTLINEITEM1_E2_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_E2_1_entry,long,
    HashIndex<COUNTLINEITEM1_E2_1_entry,long,COUNTLINEITEM1_E2_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_E2_1_map;
  typedef HashIndex<COUNTLINEITEM1_E2_1_entry,long,COUNTLINEITEM1_E2_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_E2_1_map_0;
  
  struct COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry {
    long S_SUPPKEY; long __av; 
    explicit COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry() { /*S_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry(const long c0, const long c1) { S_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry(const COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_E2_1LINEITEM1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry& x, const COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry,long,
    HashIndex<COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry,long,COUNTLINEITEM1_E2_1LINEITEM1_DELTA_mapkey0_idxfn,true>
  > COUNTLINEITEM1_E2_1LINEITEM1_DELTA_map;
  typedef HashIndex<COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry,long,COUNTLINEITEM1_E2_1LINEITEM1_DELTA_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_E2_1LINEITEM1_DELTA_map_0;
  
  struct COUNTLINEITEM1_L3_1_entry {
    long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTLINEITEM1_L3_1_entry() { /*S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTLINEITEM1_L3_1_entry(const long c0, const DOUBLE_TYPE c1) { S_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L3_1_entry(const COUNTLINEITEM1_L3_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L3_1_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L3_1_entry& x, const COUNTLINEITEM1_L3_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L3_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTLINEITEM1_L3_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L3_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L3_1_map;
  typedef HashIndex<COUNTLINEITEM1_L3_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L3_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L3_1_map_0;
  
  struct COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry {
    long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry() { /*S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { S_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry(const COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L3_1LINEITEM1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry& x, const COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,COUNTLINEITEM1_L3_1LINEITEM1_DELTA_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L3_1LINEITEM1_DELTA_map;
  typedef HashIndex<COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,COUNTLINEITEM1_L3_1LINEITEM1_DELTA_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L3_1LINEITEM1_DELTA_map_0;
  
  struct COUNTLINEITEM1_L4_1_E1_1_entry {
    long R2_SUPPKEY; long __av; 
    explicit COUNTLINEITEM1_L4_1_E1_1_entry() { /*R2_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTLINEITEM1_L4_1_E1_1_entry(const long c0, const long c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L4_1_E1_1_entry(const COUNTLINEITEM1_L4_1_E1_1_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L4_1_E1_1_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L4_1_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L4_1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L4_1_E1_1_entry& x, const COUNTLINEITEM1_L4_1_E1_1_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L4_1_E1_1_entry,long,
    HashIndex<COUNTLINEITEM1_L4_1_E1_1_entry,long,COUNTLINEITEM1_L4_1_E1_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L4_1_E1_1_map;
  typedef HashIndex<COUNTLINEITEM1_L4_1_E1_1_entry,long,COUNTLINEITEM1_L4_1_E1_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0;
  
  struct COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry {
    long R2_SUPPKEY; long __av; 
    explicit COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry() { /*R2_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry(const long c0, const long c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry(const COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry& x, const COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry,long,
    HashIndex<COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry,long,COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_map;
  typedef HashIndex<COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry,long,COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_map_0;
  
  struct COUNTLINEITEM1_L4_1_L2_1_entry {
    long R2_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTLINEITEM1_L4_1_L2_1_entry() { /*R2_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTLINEITEM1_L4_1_L2_1_entry(const long c0, const DOUBLE_TYPE c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L4_1_L2_1_entry(const COUNTLINEITEM1_L4_1_L2_1_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L4_1_L2_1_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L4_1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L4_1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L4_1_L2_1_entry& x, const COUNTLINEITEM1_L4_1_L2_1_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L4_1_L2_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L4_1_L2_1_map;
  typedef HashIndex<COUNTLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L4_1_L2_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L4_1_L2_1_map_0;
  
  struct COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry {
    long R2_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry() { /*R2_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry(const long c0, const DOUBLE_TYPE c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry(const COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry& x, const COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_map;
  typedef HashIndex<COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry,DOUBLE_TYPE,COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const COUNT_map& _COUNT = get_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(COUNT), _COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const COUNT_map& get_COUNT() const {
      return COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    COUNT_map COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = Udate(STRING_TYPE("1996-4-1"));
      c1 = Udate(STRING_TYPE("1996-1-1"));
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_LINEITEM(TPCHLineitemBatch& DELTA_LINEITEM) {
      { 
        if (tS > 0) { tS += DELTA_LINEITEM.size; return; }         
        tLastN += DELTA_LINEITEM.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_LINEITEM.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_LINEITEM.size;

        COUNTLINEITEM1_E2_1LINEITEM1_DELTA.clear();
        COUNTLINEITEM1_L3_1LINEITEM1_DELTA.clear();
        COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA.clear();
        COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                long l_orderkey = DELTA_LINEITEM.orderkey[i];
                long l_partkey = DELTA_LINEITEM.partkey[i];
                long s_suppkey = DELTA_LINEITEM.suppkey[i];
                long l_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                STRING_TYPE l_returnflag = DELTA_LINEITEM.returnflag[i];
                STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                date l_shipdate = DELTA_LINEITEM.shipdate[i];
                date l_commitdate = DELTA_LINEITEM.commitdate[i];
                date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                STRING_TYPE l_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(l_shipdate >= c1 && c2 > l_shipdate) ? COUNTLINEITEM1_E2_1LINEITEM1_DELTA.addOrDelOnZero(se1.modify(s_suppkey),v1) : (void)0);     
                long v2 = 1L;
                (/*if */(l_shipdate >= c1 && c2 > l_shipdate) ? COUNTLINEITEM1_L3_1LINEITEM1_DELTA.addOrDelOnZero(se2.modify(s_suppkey),(v2 * (l_extendedprice * (1L + (-1L * l_discount))))) : (void)0);     
                long v3 = 1L;
                (/*if */(l_shipdate >= c1 && c2 > l_shipdate) ? COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA.addOrDelOnZero(se3.modify(s_suppkey),v3) : (void)0); 
                long v4 = 1L;
                (/*if */(l_shipdate >= c1 && c2 > l_shipdate) ? COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA.addOrDelOnZero(se4.modify(s_suppkey),(v4 * (l_extendedprice * (1L + (-1L * l_discount))))) : (void)0);
          }          
        }

        {  // foreach
          const HashIndex_COUNTLINEITEM1_E2_1LINEITEM1_DELTA_map_0* i5 = static_cast<HashIndex_COUNTLINEITEM1_E2_1LINEITEM1_DELTA_map_0*>(COUNTLINEITEM1_E2_1LINEITEM1_DELTA.index[0]);
          HashIndex_COUNTLINEITEM1_E2_1LINEITEM1_DELTA_map_0::IdxNode* n5; 
          COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long s_suppkey = e5->S_SUPPKEY;
                long v5 = e5->__av;
                COUNTLINEITEM1_E2_1.addOrDelOnZero(se5.modify(s_suppkey),v5);
              n5 = n5->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTLINEITEM1_L3_1LINEITEM1_DELTA_map_0* i6 = static_cast<HashIndex_COUNTLINEITEM1_L3_1LINEITEM1_DELTA_map_0*>(COUNTLINEITEM1_L3_1LINEITEM1_DELTA.index[0]);
          HashIndex_COUNTLINEITEM1_L3_1LINEITEM1_DELTA_map_0::IdxNode* n6; 
          COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long s_suppkey = e6->S_SUPPKEY;
                DOUBLE_TYPE v6 = e6->__av;
                COUNTLINEITEM1_L3_1.addOrDelOnZero(se6.modify(s_suppkey),v6);
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_map_0* i7 = static_cast<HashIndex_COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_map_0*>(COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA.index[0]);
          HashIndex_COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_map_0::IdxNode* n7; 
          COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long r2_suppkey = e7->R2_SUPPKEY;
                long v7 = e7->__av;
                COUNTLINEITEM1_L4_1_E1_1.addOrDelOnZero(se7.modify(r2_suppkey),v7);
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_map_0* i8 = static_cast<HashIndex_COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_map_0*>(COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA.index[0]);
          HashIndex_COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_map_0::IdxNode* n8; 
          COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long r2_suppkey = e8->R2_SUPPKEY;
                DOUBLE_TYPE v8 = e8->__av;
                COUNTLINEITEM1_L4_1_L2_1.addOrDelOnZero(se8.modify(r2_suppkey),v8);
              n8 = n8->nxt;
            }
          }
        }COUNT.clear();
        {  // foreach
          const HashIndex_COUNTLINEITEM1_map_0123* i9 = static_cast<HashIndex_COUNTLINEITEM1_map_0123*>(COUNTLINEITEM1.index[0]);
          HashIndex_COUNTLINEITEM1_map_0123::IdxNode* n9; 
          COUNTLINEITEM1_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long s_suppkey = e9->S_SUPPKEY;
                STRING_TYPE s_name = e9->S_NAME;
                STRING_TYPE s_address = e9->S_ADDRESS;
                STRING_TYPE s_phone = e9->S_PHONE;
                long v9 = e9->__av;
                DOUBLE_TYPE l1 = COUNTLINEITEM1_L3_1.getValueOrDefault(se10.modify(s_suppkey));
                long agg1 = 0L;
                long agg2 = 0L;
                {  // foreach
                  const HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0* i10 = static_cast<HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0*>(COUNTLINEITEM1_L4_1_E1_1.index[0]);
                  HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0::IdxNode* n10; 
                  COUNTLINEITEM1_L4_1_E1_1_entry* e10;
                
                  for (size_t i = 0; i < i10->size_; i++)
                  {
                    n10 = i10->buckets_ + i;
                    while (n10 && (e10 = n10->obj))
                    {
                        long r2_suppkey = e10->R2_SUPPKEY;
                        long v10 = e10->__av;
                        DOUBLE_TYPE l3 = COUNTLINEITEM1_L4_1_L2_1.getValueOrDefault(se12.modify(r2_suppkey));
                        (/*if */(l3 > l1) ? agg2 += (v10 != 0 ? 1L : 0L) : 0L);
                      n10 = n10->nxt;
                    }
                  }
                }long l2 = agg2;
                (/*if */(l2 == 0L) ? agg1 += 1L : 0L);
                COUNT.addOrDelOnZero(se9.modify(s_suppkey,s_name,s_address,s_phone,l1),(v9 * ((COUNTLINEITEM1_E2_1.getValueOrDefault(se11.modify(s_suppkey)) != 0 ? 1L : 0L) * agg1)));
              n9 = n9->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_SUPPLIER(TPCHSupplierBatch& DELTA_SUPPLIER) {
      {  
        if (tS > 0) { tS += DELTA_SUPPLIER.size; return; }         
        tLastN += DELTA_SUPPLIER.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_SUPPLIER.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_SUPPLIER.size;

        COUNTSUPPLIER1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_SUPPLIER.size; i++) 
          {
                long s_suppkey = DELTA_SUPPLIER.suppkey[i];
                STRING_TYPE s_name = DELTA_SUPPLIER.name[i];
                STRING_TYPE s_address = DELTA_SUPPLIER.address[i];
                long s_nationkey = DELTA_SUPPLIER.nationkey[i];
                STRING_TYPE s_phone = DELTA_SUPPLIER.phone[i];
                DOUBLE_TYPE s_acctbal = DELTA_SUPPLIER.acctbal[i];
                STRING_TYPE s_comment = DELTA_SUPPLIER.comment[i];
                long v11 = 1L;
                COUNTSUPPLIER1_DELTA.addOrDelOnZero(se13.modify(s_suppkey,s_name,s_address,s_phone),v11);            
          }
        }{  // foreach
          const HashIndex_COUNTSUPPLIER1_DELTA_map_0123* i12 = static_cast<HashIndex_COUNTSUPPLIER1_DELTA_map_0123*>(COUNTSUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTSUPPLIER1_DELTA_map_0123::IdxNode* n12; 
          COUNTSUPPLIER1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long s_suppkey = e12->S_SUPPKEY;
                STRING_TYPE s_name = e12->S_NAME;
                STRING_TYPE s_address = e12->S_ADDRESS;
                STRING_TYPE s_phone = e12->S_PHONE;
                long v12 = e12->__av;
                DOUBLE_TYPE l4 = COUNTLINEITEM1_L3_1.getValueOrDefault(se15.modify(s_suppkey));
                long agg3 = 0L;
                long agg4 = 0L;
                {  // foreach
                  const HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0* i13 = static_cast<HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0*>(COUNTLINEITEM1_L4_1_E1_1.index[0]);
                  HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0::IdxNode* n13; 
                  COUNTLINEITEM1_L4_1_E1_1_entry* e13;
                
                  for (size_t i = 0; i < i13->size_; i++)
                  {
                    n13 = i13->buckets_ + i;
                    while (n13 && (e13 = n13->obj))
                    {
                        long r2_suppkey = e13->R2_SUPPKEY;
                        long v13 = e13->__av;
                        DOUBLE_TYPE l6 = COUNTLINEITEM1_L4_1_L2_1.getValueOrDefault(se17.modify(r2_suppkey));
                        (/*if */(l6 > l4) ? agg4 += (v13 != 0 ? 1L : 0L) : 0L);
                      n13 = n13->nxt;
                    }
                  }
                }long l5 = agg4;
                (/*if */(l5 == 0L) ? agg3 += 1L : 0L);
                COUNT.addOrDelOnZero(se14.modify(s_suppkey,s_name,s_address,s_phone,l4),(v12 * ((COUNTLINEITEM1_E2_1.getValueOrDefault(se16.modify(s_suppkey)) != 0 ? 1L : 0L) * agg3)));
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSUPPLIER1_DELTA_map_0123* i14 = static_cast<HashIndex_COUNTSUPPLIER1_DELTA_map_0123*>(COUNTSUPPLIER1_DELTA.index[0]);
          HashIndex_COUNTSUPPLIER1_DELTA_map_0123::IdxNode* n14; 
          COUNTSUPPLIER1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long s_suppkey = e14->S_SUPPKEY;
                STRING_TYPE s_name = e14->S_NAME;
                STRING_TYPE s_address = e14->S_ADDRESS;
                STRING_TYPE s_phone = e14->S_PHONE;
                long v14 = e14->__av;
                COUNTLINEITEM1.addOrDelOnZero(se18.modify(s_suppkey,s_name,s_address,s_phone),v14);
              n14 = n14->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTLINEITEM1_E2_1LINEITEM1_DELTA_entry se1;
    COUNTLINEITEM1_L3_1LINEITEM1_DELTA_entry se2;
    COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_entry se3;
    COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_entry se4;
    COUNTLINEITEM1_E2_1_entry se5;
    COUNTLINEITEM1_L3_1_entry se6;
    COUNTLINEITEM1_L4_1_E1_1_entry se7;
    COUNTLINEITEM1_L4_1_L2_1_entry se8;
    COUNT_entry se9;
    COUNTLINEITEM1_L3_1_entry se10;
    COUNTLINEITEM1_E2_1_entry se11;
    COUNTLINEITEM1_L4_1_L2_1_entry se12;
    COUNTSUPPLIER1_DELTA_entry se13;
    COUNT_entry se14;
    COUNTLINEITEM1_L3_1_entry se15;
    COUNTLINEITEM1_E2_1_entry se16;
    COUNTLINEITEM1_L4_1_L2_1_entry se17;
    COUNTLINEITEM1_entry se18;
  
    /* Data structures used for storing materialized views */
    COUNTSUPPLIER1_DELTA_map COUNTSUPPLIER1_DELTA;
    COUNTLINEITEM1_map COUNTLINEITEM1;
    COUNTLINEITEM1_E2_1_map COUNTLINEITEM1_E2_1;
    COUNTLINEITEM1_E2_1LINEITEM1_DELTA_map COUNTLINEITEM1_E2_1LINEITEM1_DELTA;
    COUNTLINEITEM1_L3_1_map COUNTLINEITEM1_L3_1;
    COUNTLINEITEM1_L3_1LINEITEM1_DELTA_map COUNTLINEITEM1_L3_1LINEITEM1_DELTA;
    COUNTLINEITEM1_L4_1_E1_1_map COUNTLINEITEM1_L4_1_E1_1;
    COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA_map COUNTLINEITEM1_L4_1_E1_1LINEITEM1_DELTA;
    COUNTLINEITEM1_L4_1_L2_1_map COUNTLINEITEM1_L4_1_L2_1;
    COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA_map COUNTLINEITEM1_L4_1_L2_1LINEITEM1_DELTA;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_SUPPLIER_map DELTA_SUPPLIER;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
  
  };

}
