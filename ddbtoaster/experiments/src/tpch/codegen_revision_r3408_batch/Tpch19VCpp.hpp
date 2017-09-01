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
  
  struct DELTA_PART_entry {
    long part_partkey; STRING_TYPE part_name; STRING_TYPE part_mfgr; STRING_TYPE part_brand; STRING_TYPE part_type; long part_size; STRING_TYPE part_container; DOUBLE_TYPE part_retailprice; STRING_TYPE part_comment; long __av; 
    explicit DELTA_PART_entry() { /*part_partkey = 0L; part_name = ""; part_mfgr = ""; part_brand = ""; part_type = ""; part_size = 0L; part_container = ""; part_retailprice = 0.0; part_comment = ""; __av = 0L; */ }
    explicit DELTA_PART_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const long c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const long c9) { part_partkey = c0; part_name = c1; part_mfgr = c2; part_brand = c3; part_type = c4; part_size = c5; part_container = c6; part_retailprice = c7; part_comment = c8; __av = c9; }
    DELTA_PART_entry(const DELTA_PART_entry& other) : part_partkey( other.part_partkey ), part_name( other.part_name ), part_mfgr( other.part_mfgr ), part_brand( other.part_brand ), part_type( other.part_type ), part_size( other.part_size ), part_container( other.part_container ), part_retailprice( other.part_retailprice ), part_comment( other.part_comment ), __av( other.__av ) {}
    FORCE_INLINE DELTA_PART_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const long c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8) { part_partkey = c0; part_name = c1; part_mfgr = c2; part_brand = c3; part_type = c4; part_size = c5; part_container = c6; part_retailprice = c7; part_comment = c8;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_mfgr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_brand);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_size);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_container);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_retailprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, part_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_PART_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_PART_entry& e) {
      size_t h = 0;
      hash_combine(h, e.part_partkey);
      hash_combine(h, e.part_name);
      hash_combine(h, e.part_mfgr);
      hash_combine(h, e.part_brand);
      hash_combine(h, e.part_type);
      hash_combine(h, e.part_size);
      hash_combine(h, e.part_container);
      hash_combine(h, e.part_retailprice);
      hash_combine(h, e.part_comment);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_PART_entry& x, const DELTA_PART_entry& y) {
      return x.part_partkey == y.part_partkey && x.part_name == y.part_name && x.part_mfgr == y.part_mfgr && x.part_brand == y.part_brand && x.part_type == y.part_type && x.part_size == y.part_size && x.part_container == y.part_container && x.part_retailprice == y.part_retailprice && x.part_comment == y.part_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_PART_entry,long,
    HashIndex<DELTA_PART_entry,long,DELTA_PART_mapkey012345678_idxfn,true>
  > DELTA_PART_map;
  typedef HashIndex<DELTA_PART_entry,long,DELTA_PART_mapkey012345678_idxfn,true> HashIndex_DELTA_PART_map_012345678;
  
  struct REVENUEPART1_DELTA_entry {
    long L_PARTKEY; STRING_TYPE P_BRAND; long P_SIZE; STRING_TYPE P_CONTAINER; long __av; 
    explicit REVENUEPART1_DELTA_entry() { /*L_PARTKEY = 0L; P_BRAND = ""; P_SIZE = 0L; P_CONTAINER = ""; __av = 0L; */ }
    explicit REVENUEPART1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4) { L_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3; __av = c4; }
    REVENUEPART1_DELTA_entry(const REVENUEPART1_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), P_BRAND( other.P_BRAND ), P_SIZE( other.P_SIZE ), P_CONTAINER( other.P_CONTAINER ), __av( other.__av ) {}
    FORCE_INLINE REVENUEPART1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { L_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_CONTAINER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEPART1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEPART1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_SIZE);
      hash_combine(h, e.P_CONTAINER);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEPART1_DELTA_entry& x, const REVENUEPART1_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_SIZE == y.P_SIZE && x.P_CONTAINER == y.P_CONTAINER;
    }
  };
  
  typedef MultiHashMap<REVENUEPART1_DELTA_entry,long,
    HashIndex<REVENUEPART1_DELTA_entry,long,REVENUEPART1_DELTA_mapkey0123_idxfn,true>
  > REVENUEPART1_DELTA_map;
  typedef HashIndex<REVENUEPART1_DELTA_entry,long,REVENUEPART1_DELTA_mapkey0123_idxfn,true> HashIndex_REVENUEPART1_DELTA_map_0123;
  
  struct REVENUEPART1_entry {
    long L_PARTKEY; DOUBLE_TYPE L_QUANTITY; DOUBLE_TYPE __av; 
    explicit REVENUEPART1_entry() { /*L_PARTKEY = 0L; L_QUANTITY = 0.0; __av = 0.0; */ }
    explicit REVENUEPART1_entry(const long c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { L_PARTKEY = c0; L_QUANTITY = c1; __av = c2; }
    REVENUEPART1_entry(const REVENUEPART1_entry& other) : L_PARTKEY( other.L_PARTKEY ), L_QUANTITY( other.L_QUANTITY ), __av( other.__av ) {}
    FORCE_INLINE REVENUEPART1_entry& modify(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; L_QUANTITY = c1;  return *this; }
    FORCE_INLINE REVENUEPART1_entry& modify0(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_QUANTITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUEPART1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.L_QUANTITY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEPART1_entry& x, const REVENUEPART1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.L_QUANTITY == y.L_QUANTITY;
    }
  };
  
  struct REVENUEPART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUEPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUEPART1_entry& x, const REVENUEPART1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUEPART1_entry,DOUBLE_TYPE,
    HashIndex<REVENUEPART1_entry,DOUBLE_TYPE,REVENUEPART1_mapkey01_idxfn,true>,
    HashIndex<REVENUEPART1_entry,DOUBLE_TYPE,REVENUEPART1_mapkey0_idxfn,false>
  > REVENUEPART1_map;
  typedef HashIndex<REVENUEPART1_entry,DOUBLE_TYPE,REVENUEPART1_mapkey01_idxfn,true> HashIndex_REVENUEPART1_map_01;
  typedef HashIndex<REVENUEPART1_entry,DOUBLE_TYPE,REVENUEPART1_mapkey0_idxfn,false> HashIndex_REVENUEPART1_map_0;
  
  struct REVENUELINEITEM1_DELTA_entry {
    long L_PARTKEY; DOUBLE_TYPE L_QUANTITY; DOUBLE_TYPE __av; 
    explicit REVENUELINEITEM1_DELTA_entry() { /*L_PARTKEY = 0L; L_QUANTITY = 0.0; __av = 0.0; */ }
    explicit REVENUELINEITEM1_DELTA_entry(const long c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { L_PARTKEY = c0; L_QUANTITY = c1; __av = c2; }
    REVENUELINEITEM1_DELTA_entry(const REVENUELINEITEM1_DELTA_entry& other) : L_PARTKEY( other.L_PARTKEY ), L_QUANTITY( other.L_QUANTITY ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_DELTA_entry& modify(const long c0, const DOUBLE_TYPE c1) { L_PARTKEY = c0; L_QUANTITY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_QUANTITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.L_QUANTITY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_DELTA_entry& x, const REVENUELINEITEM1_DELTA_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.L_QUANTITY == y.L_QUANTITY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey01_idxfn,true>
  > REVENUELINEITEM1_DELTA_map;
  typedef HashIndex<REVENUELINEITEM1_DELTA_entry,DOUBLE_TYPE,REVENUELINEITEM1_DELTA_mapkey01_idxfn,true> HashIndex_REVENUELINEITEM1_DELTA_map_01;
  
  struct REVENUELINEITEM1_entry {
    long L_PARTKEY; STRING_TYPE P_BRAND; long P_SIZE; STRING_TYPE P_CONTAINER; long __av; 
    explicit REVENUELINEITEM1_entry() { /*L_PARTKEY = 0L; P_BRAND = ""; P_SIZE = 0L; P_CONTAINER = ""; __av = 0L; */ }
    explicit REVENUELINEITEM1_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4) { L_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3; __av = c4; }
    REVENUELINEITEM1_entry(const REVENUELINEITEM1_entry& other) : L_PARTKEY( other.L_PARTKEY ), P_BRAND( other.P_BRAND ), P_SIZE( other.P_SIZE ), P_CONTAINER( other.P_CONTAINER ), __av( other.__av ) {}
    FORCE_INLINE REVENUELINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { L_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3;  return *this; }
    FORCE_INLINE REVENUELINEITEM1_entry& modify0(const long c0) { L_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_CONTAINER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUELINEITEM1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_SIZE);
      hash_combine(h, e.P_CONTAINER);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_entry& x, const REVENUELINEITEM1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_SIZE == y.P_SIZE && x.P_CONTAINER == y.P_CONTAINER;
    }
  };
  
  struct REVENUELINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUELINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUELINEITEM1_entry& x, const REVENUELINEITEM1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUELINEITEM1_entry,long,
    HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey0123_idxfn,true>,
    HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey0_idxfn,false>
  > REVENUELINEITEM1_map;
  typedef HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey0123_idxfn,true> HashIndex_REVENUELINEITEM1_map_0123;
  typedef HashIndex<REVENUELINEITEM1_entry,long,REVENUELINEITEM1_mapkey0_idxfn,false> HashIndex_REVENUELINEITEM1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0), REVENUE(0.0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const DOUBLE_TYPE _REVENUE = get_REVENUE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(REVENUE), _REVENUE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const DOUBLE_TYPE get_REVENUE() const {
      return REVENUE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    DOUBLE_TYPE REVENUE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c16 = STRING_TYPE("LG PACK");
      c18 = STRING_TYPE("Brand#34");
      c2 = STRING_TYPE("AIR");
      c12 = STRING_TYPE("MED PACK");
      c17 = STRING_TYPE("LG PKG");
      c11 = STRING_TYPE("MED PKG");
      c4 = STRING_TYPE("SM CASE");
      c3 = STRING_TYPE("AIR REG");
      c6 = STRING_TYPE("SM PACK");
      c10 = STRING_TYPE("MED BOX");
      c14 = STRING_TYPE("LG CASE");
      c1 = STRING_TYPE("DELIVER IN PERSON");
      c5 = STRING_TYPE("SM BOX");
      c13 = STRING_TYPE("Brand#23");
      c8 = STRING_TYPE("Brand#12");
      c15 = STRING_TYPE("LG BOX");
      c7 = STRING_TYPE("SM PKG");
      c9 = STRING_TYPE("MED BAG");
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

        REVENUELINEITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                // long l_orderkey = DELTA_LINEITEM.orderkey[i];
                long l_partkey = DELTA_LINEITEM.partkey[i];
                // long l_suppkey = DELTA_LINEITEM.suppkey[i];
                // long l_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE l_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE l_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE l_discount = DELTA_LINEITEM.discount[i];
                // DOUBLE_TYPE l_tax = DELTA_LINEITEM.tax[i];
                // STRING_TYPE l_returnflag = DELTA_LINEITEM.returnflag[i];
                // STRING_TYPE l_linestatus = DELTA_LINEITEM.linestatus[i];
                // date l_shipdate = DELTA_LINEITEM.shipdate[i];
                // date l_commitdate = DELTA_LINEITEM.commitdate[i];
                // date l_receiptdate = DELTA_LINEITEM.receiptdate[i];
                STRING_TYPE lift1 = DELTA_LINEITEM.shipinstruct[i];
                STRING_TYPE l_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE l_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(lift1 == c1 && ((l_shipmode == c2) || (l_shipmode == c3))) ? REVENUELINEITEM1_DELTA.addOrDelOnZero(se1.modify(l_partkey,l_quantity),(v1 * (l_extendedprice * (1L + (-1L * l_discount))))) : (void)0);            
          }
        }

        DOUBLE_TYPE agg1 = 0.0;
        {  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i2 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n2; 
          REVENUELINEITEM1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long l_partkey = e2->L_PARTKEY;
                DOUBLE_TYPE l_quantity = e2->L_QUANTITY;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_REVENUELINEITEM1_map_0* i3 = static_cast<HashIndex_REVENUELINEITEM1_map_0*>(REVENUELINEITEM1.index[1]);
                  const HASH_RES_t h1 = REVENUELINEITEM1_mapkey0_idxfn::hash(se3.modify0(l_partkey));
                  HashIndex_REVENUELINEITEM1_map_0::IdxNode* n3 = static_cast<HashIndex_REVENUELINEITEM1_map_0::IdxNode*>(i3->slice(se3, h1));
                  REVENUELINEITEM1_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      STRING_TYPE p_brand = e3->P_BRAND;
                      long p_size = e3->P_SIZE;
                      STRING_TYPE p_container = e3->P_CONTAINER;
                      long v3 = e3->__av;
                      long l1 = ((/*if */(5L >= p_size && 11L >= l_quantity && l_quantity >= 1L && ((p_container == c4) || (p_container == c5) || (p_container == c6) || (p_container == c7)) && p_brand == c8) ? 1L : 0L) + ((/*if */(10L >= p_size && 20L >= l_quantity && l_quantity >= 10L && ((p_container == c9) || (p_container == c10) || (p_container == c11) || (p_container == c12)) && p_brand == c13) ? 1L : 0L) + (/*if */(15L >= p_size && 30L >= l_quantity && l_quantity >= 20L && ((p_container == c14) || (p_container == c15) || (p_container == c16) || (p_container == c17)) && p_brand == c18) ? 1L : 0L)));
                      (/*if */(l1 > 0L) ? agg1 += (v2 * v3) : 0.0);
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h1 == n3->hash &&  REVENUELINEITEM1_mapkey0_idxfn::equals(se3, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }REVENUE += agg1;
        {  // foreach
          const HashIndex_REVENUELINEITEM1_DELTA_map_01* i4 = static_cast<HashIndex_REVENUELINEITEM1_DELTA_map_01*>(REVENUELINEITEM1_DELTA.index[0]);
          HashIndex_REVENUELINEITEM1_DELTA_map_01::IdxNode* n4; 
          REVENUELINEITEM1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long l_partkey = e4->L_PARTKEY;
                DOUBLE_TYPE l_quantity = e4->L_QUANTITY;
                DOUBLE_TYPE v4 = e4->__av;
                REVENUEPART1.addOrDelOnZero(se4.modify(l_partkey,l_quantity),v4);
              n4 = n4->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_PART(TPCHPartBatch& DELTA_PART) {
      { 
        if (tS > 0) { tS += DELTA_PART.size; return; }         
        tLastN += DELTA_PART.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_PART.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_PART.size;

        REVENUEPART1_DELTA.clear();
        { 
          for (size_t i = 0; i < DELTA_PART.size; i++) 
          {
                long l_partkey = DELTA_PART.partkey[i];
                // STRING_TYPE p_name = DELTA_PART.name[i];
                // STRING_TYPE p_mfgr = DELTA_PART.mfgr[i];
                STRING_TYPE p_brand = DELTA_PART.brand[i];
                // STRING_TYPE p_type = DELTA_PART.type[i];
                long p_size = DELTA_PART.psize[i];
                STRING_TYPE p_container = DELTA_PART.container[i];
                // DOUBLE_TYPE p_retailprice = DELTA_PART.retailprice[i];
                // STRING_TYPE p_comment = DELTA_PART.comment[i];
                long v5 = 1L;
                (/*if */(p_size >= 1L) ? REVENUEPART1_DELTA.addOrDelOnZero(se5.modify(l_partkey,p_brand,p_size,p_container),v5) : (void)0);            
          }
        }

        DOUBLE_TYPE agg2 = 0.0;
        {  // foreach
          const HashIndex_REVENUEPART1_DELTA_map_0123* i6 = static_cast<HashIndex_REVENUEPART1_DELTA_map_0123*>(REVENUEPART1_DELTA.index[0]);
          HashIndex_REVENUEPART1_DELTA_map_0123::IdxNode* n6; 
          REVENUEPART1_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long l_partkey = e6->L_PARTKEY;
                STRING_TYPE p_brand = e6->P_BRAND;
                long p_size = e6->P_SIZE;
                STRING_TYPE p_container = e6->P_CONTAINER;
                long v6 = e6->__av;
                { //slice 
                  const HashIndex_REVENUEPART1_map_0* i7 = static_cast<HashIndex_REVENUEPART1_map_0*>(REVENUEPART1.index[1]);
                  const HASH_RES_t h2 = REVENUEPART1_mapkey0_idxfn::hash(se7.modify0(l_partkey));
                  HashIndex_REVENUEPART1_map_0::IdxNode* n7 = static_cast<HashIndex_REVENUEPART1_map_0::IdxNode*>(i7->slice(se7, h2));
                  REVENUEPART1_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      DOUBLE_TYPE l_quantity = e7->L_QUANTITY;
                      DOUBLE_TYPE v7 = e7->__av;
                      long l2 = ((/*if */(((p_container == c4) || (p_container == c5) || (p_container == c6) || (p_container == c7)) && l_quantity >= 1L && 11L >= l_quantity && 5L >= p_size && p_brand == c8) ? 1L : 0L) + ((/*if */(((p_container == c9) || (p_container == c10) || (p_container == c11) || (p_container == c12)) && l_quantity >= 10L && 20L >= l_quantity && 10L >= p_size && p_brand == c13) ? 1L : 0L) + (/*if */(((p_container == c14) || (p_container == c15) || (p_container == c16) || (p_container == c17)) && l_quantity >= 20L && 30L >= l_quantity && 15L >= p_size && p_brand == c18) ? 1L : 0L)));
                      (/*if */(l2 > 0L) ? agg2 += (v6 * v7) : 0.0);
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h2 == n7->hash &&  REVENUEPART1_mapkey0_idxfn::equals(se7, *e7)); 
                  }
                }
              n6 = n6->nxt;
            }
          }
        }REVENUE += agg2;
        {  // foreach
          const HashIndex_REVENUEPART1_DELTA_map_0123* i8 = static_cast<HashIndex_REVENUEPART1_DELTA_map_0123*>(REVENUEPART1_DELTA.index[0]);
          HashIndex_REVENUEPART1_DELTA_map_0123::IdxNode* n8; 
          REVENUEPART1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long l_partkey = e8->L_PARTKEY;
                STRING_TYPE p_brand = e8->P_BRAND;
                long p_size = e8->P_SIZE;
                STRING_TYPE p_container = e8->P_CONTAINER;
                long v8 = e8->__av;
                REVENUELINEITEM1.addOrDelOnZero(se8.modify(l_partkey,p_brand,p_size,p_container),v8);
              n8 = n8->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        REVENUE = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUELINEITEM1_DELTA_entry se1;
    REVENUELINEITEM1_entry se3;
    REVENUEPART1_entry se4;
    REVENUEPART1_DELTA_entry se5;
    REVENUEPART1_entry se7;
    REVENUELINEITEM1_entry se8;
  
    /* Data structures used for storing materialized views */
    REVENUEPART1_DELTA_map REVENUEPART1_DELTA;
    REVENUEPART1_map REVENUEPART1;
    REVENUELINEITEM1_DELTA_map REVENUELINEITEM1_DELTA;
    REVENUELINEITEM1_map REVENUELINEITEM1;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    DELTA_PART_map DELTA_PART;
    
    /*const static*/ STRING_TYPE c16;
    /*const static*/ STRING_TYPE c18;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c12;
    /*const static*/ STRING_TYPE c17;
    /*const static*/ STRING_TYPE c11;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c10;
    /*const static*/ STRING_TYPE c14;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c13;
    /*const static*/ STRING_TYPE c8;
    /*const static*/ STRING_TYPE c15;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c9;
  
  };

}
