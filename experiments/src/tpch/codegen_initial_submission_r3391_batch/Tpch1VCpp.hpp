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
  
  struct SUM_QTY_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_QTY_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_QTY_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_QTY_entry(const SUM_QTY_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_QTY_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_QTY_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_QTY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_QTY_entry& x, const SUM_QTY_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_QTY_entry,DOUBLE_TYPE,
    HashIndex<SUM_QTY_entry,DOUBLE_TYPE,SUM_QTY_mapkey01_idxfn,true>
  > SUM_QTY_map;
  typedef HashIndex<SUM_QTY_entry,DOUBLE_TYPE,SUM_QTY_mapkey01_idxfn,true> HashIndex_SUM_QTY_map_01;
  
  struct SUM_QTYLINEITEM1_DELTA_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_QTYLINEITEM1_DELTA_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_QTYLINEITEM1_DELTA_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_QTYLINEITEM1_DELTA_entry(const SUM_QTYLINEITEM1_DELTA_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_QTYLINEITEM1_DELTA_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_QTYLINEITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_QTYLINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_QTYLINEITEM1_DELTA_entry& x, const SUM_QTYLINEITEM1_DELTA_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_QTYLINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUM_QTYLINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_QTYLINEITEM1_DELTA_mapkey01_idxfn,true>
  > SUM_QTYLINEITEM1_DELTA_map;
  typedef HashIndex<SUM_QTYLINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_QTYLINEITEM1_DELTA_mapkey01_idxfn,true> HashIndex_SUM_QTYLINEITEM1_DELTA_map_01;
  
  struct SUM_BASE_PRICE_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_BASE_PRICE_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_BASE_PRICE_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_BASE_PRICE_entry(const SUM_BASE_PRICE_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_BASE_PRICE_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_BASE_PRICE_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_BASE_PRICE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_BASE_PRICE_entry& x, const SUM_BASE_PRICE_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_BASE_PRICE_entry,DOUBLE_TYPE,
    HashIndex<SUM_BASE_PRICE_entry,DOUBLE_TYPE,SUM_BASE_PRICE_mapkey01_idxfn,true>
  > SUM_BASE_PRICE_map;
  typedef HashIndex<SUM_BASE_PRICE_entry,DOUBLE_TYPE,SUM_BASE_PRICE_mapkey01_idxfn,true> HashIndex_SUM_BASE_PRICE_map_01;
  
  struct SUM_BASE_PRICELINEITEM1_DELTA_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_BASE_PRICELINEITEM1_DELTA_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_BASE_PRICELINEITEM1_DELTA_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_BASE_PRICELINEITEM1_DELTA_entry(const SUM_BASE_PRICELINEITEM1_DELTA_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_BASE_PRICELINEITEM1_DELTA_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_BASE_PRICELINEITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_BASE_PRICELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_BASE_PRICELINEITEM1_DELTA_entry& x, const SUM_BASE_PRICELINEITEM1_DELTA_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_BASE_PRICELINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUM_BASE_PRICELINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_BASE_PRICELINEITEM1_DELTA_mapkey01_idxfn,true>
  > SUM_BASE_PRICELINEITEM1_DELTA_map;
  typedef HashIndex<SUM_BASE_PRICELINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_BASE_PRICELINEITEM1_DELTA_mapkey01_idxfn,true> HashIndex_SUM_BASE_PRICELINEITEM1_DELTA_map_01;
  
  struct SUM_DISC_PRICE_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_DISC_PRICE_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_DISC_PRICE_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_DISC_PRICE_entry(const SUM_DISC_PRICE_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_DISC_PRICE_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_DISC_PRICE_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_DISC_PRICE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_DISC_PRICE_entry& x, const SUM_DISC_PRICE_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_DISC_PRICE_entry,DOUBLE_TYPE,
    HashIndex<SUM_DISC_PRICE_entry,DOUBLE_TYPE,SUM_DISC_PRICE_mapkey01_idxfn,true>
  > SUM_DISC_PRICE_map;
  typedef HashIndex<SUM_DISC_PRICE_entry,DOUBLE_TYPE,SUM_DISC_PRICE_mapkey01_idxfn,true> HashIndex_SUM_DISC_PRICE_map_01;
  
  struct SUM_DISC_PRICELINEITEM1_DELTA_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_DISC_PRICELINEITEM1_DELTA_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_DISC_PRICELINEITEM1_DELTA_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_DISC_PRICELINEITEM1_DELTA_entry(const SUM_DISC_PRICELINEITEM1_DELTA_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_DISC_PRICELINEITEM1_DELTA_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_DISC_PRICELINEITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_DISC_PRICELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_DISC_PRICELINEITEM1_DELTA_entry& x, const SUM_DISC_PRICELINEITEM1_DELTA_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_DISC_PRICELINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUM_DISC_PRICELINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_DISC_PRICELINEITEM1_DELTA_mapkey01_idxfn,true>
  > SUM_DISC_PRICELINEITEM1_DELTA_map;
  typedef HashIndex<SUM_DISC_PRICELINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_DISC_PRICELINEITEM1_DELTA_mapkey01_idxfn,true> HashIndex_SUM_DISC_PRICELINEITEM1_DELTA_map_01;
  
  struct SUM_CHARGE_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_CHARGE_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_CHARGE_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_CHARGE_entry(const SUM_CHARGE_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_CHARGE_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_CHARGE_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_CHARGE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_CHARGE_entry& x, const SUM_CHARGE_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_CHARGE_entry,DOUBLE_TYPE,
    HashIndex<SUM_CHARGE_entry,DOUBLE_TYPE,SUM_CHARGE_mapkey01_idxfn,true>
  > SUM_CHARGE_map;
  typedef HashIndex<SUM_CHARGE_entry,DOUBLE_TYPE,SUM_CHARGE_mapkey01_idxfn,true> HashIndex_SUM_CHARGE_map_01;
  
  struct SUM_CHARGELINEITEM1_DELTA_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit SUM_CHARGELINEITEM1_DELTA_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit SUM_CHARGELINEITEM1_DELTA_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    SUM_CHARGELINEITEM1_DELTA_entry(const SUM_CHARGELINEITEM1_DELTA_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE SUM_CHARGELINEITEM1_DELTA_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_CHARGELINEITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_CHARGELINEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_CHARGELINEITEM1_DELTA_entry& x, const SUM_CHARGELINEITEM1_DELTA_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<SUM_CHARGELINEITEM1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUM_CHARGELINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_CHARGELINEITEM1_DELTA_mapkey01_idxfn,true>
  > SUM_CHARGELINEITEM1_DELTA_map;
  typedef HashIndex<SUM_CHARGELINEITEM1_DELTA_entry,DOUBLE_TYPE,SUM_CHARGELINEITEM1_DELTA_mapkey01_idxfn,true> HashIndex_SUM_CHARGELINEITEM1_DELTA_map_01;
  
  struct AVG_QTY_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_QTY_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_QTY_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_QTY_entry(const AVG_QTY_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_QTY_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_QTY_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_QTY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_QTY_entry& x, const AVG_QTY_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_QTY_entry,DOUBLE_TYPE,
    HashIndex<AVG_QTY_entry,DOUBLE_TYPE,AVG_QTY_mapkey01_idxfn,true>
  > AVG_QTY_map;
  typedef HashIndex<AVG_QTY_entry,DOUBLE_TYPE,AVG_QTY_mapkey01_idxfn,true> HashIndex_AVG_QTY_map_01;
  
  struct AVG_QTYLINEITEM1_DOMAIN1_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; long __av; 
    explicit AVG_QTYLINEITEM1_DOMAIN1_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0L; */ }
    explicit AVG_QTYLINEITEM1_DOMAIN1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_QTYLINEITEM1_DOMAIN1_entry(const AVG_QTYLINEITEM1_DOMAIN1_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_QTYLINEITEM1_DOMAIN1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_QTYLINEITEM1_DOMAIN1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_QTYLINEITEM1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_QTYLINEITEM1_DOMAIN1_entry& x, const AVG_QTYLINEITEM1_DOMAIN1_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_QTYLINEITEM1_DOMAIN1_entry,long,
    HashIndex<AVG_QTYLINEITEM1_DOMAIN1_entry,long,AVG_QTYLINEITEM1_DOMAIN1_mapkey01_idxfn,true>
  > AVG_QTYLINEITEM1_DOMAIN1_map;
  typedef HashIndex<AVG_QTYLINEITEM1_DOMAIN1_entry,long,AVG_QTYLINEITEM1_DOMAIN1_mapkey01_idxfn,true> HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01;
  
  struct AVG_QTYLINEITEM1_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_QTYLINEITEM1_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_QTYLINEITEM1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_QTYLINEITEM1_entry(const AVG_QTYLINEITEM1_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_QTYLINEITEM1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_QTYLINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_QTYLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_QTYLINEITEM1_entry& x, const AVG_QTYLINEITEM1_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_QTYLINEITEM1_entry,DOUBLE_TYPE,
    HashIndex<AVG_QTYLINEITEM1_entry,DOUBLE_TYPE,AVG_QTYLINEITEM1_mapkey01_idxfn,true>
  > AVG_QTYLINEITEM1_map;
  typedef HashIndex<AVG_QTYLINEITEM1_entry,DOUBLE_TYPE,AVG_QTYLINEITEM1_mapkey01_idxfn,true> HashIndex_AVG_QTYLINEITEM1_map_01;
  
  struct AVG_QTYLINEITEM1_L1_1_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; long __av; 
    explicit AVG_QTYLINEITEM1_L1_1_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0L; */ }
    explicit AVG_QTYLINEITEM1_L1_1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_QTYLINEITEM1_L1_1_entry(const AVG_QTYLINEITEM1_L1_1_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_QTYLINEITEM1_L1_1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_QTYLINEITEM1_L1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_QTYLINEITEM1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_QTYLINEITEM1_L1_1_entry& x, const AVG_QTYLINEITEM1_L1_1_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_QTYLINEITEM1_L1_1_entry,long,
    HashIndex<AVG_QTYLINEITEM1_L1_1_entry,long,AVG_QTYLINEITEM1_L1_1_mapkey01_idxfn,true>
  > AVG_QTYLINEITEM1_L1_1_map;
  typedef HashIndex<AVG_QTYLINEITEM1_L1_1_entry,long,AVG_QTYLINEITEM1_L1_1_mapkey01_idxfn,true> HashIndex_AVG_QTYLINEITEM1_L1_1_map_01;
  
  struct AVG_QTYLINEITEM1_L1_2_DELTA_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; long __av; 
    explicit AVG_QTYLINEITEM1_L1_2_DELTA_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0L; */ }
    explicit AVG_QTYLINEITEM1_L1_2_DELTA_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_QTYLINEITEM1_L1_2_DELTA_entry(const AVG_QTYLINEITEM1_L1_2_DELTA_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_QTYLINEITEM1_L1_2_DELTA_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_QTYLINEITEM1_L1_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_QTYLINEITEM1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_QTYLINEITEM1_L1_2_DELTA_entry& x, const AVG_QTYLINEITEM1_L1_2_DELTA_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_QTYLINEITEM1_L1_2_DELTA_entry,long,
    HashIndex<AVG_QTYLINEITEM1_L1_2_DELTA_entry,long,AVG_QTYLINEITEM1_L1_2_DELTA_mapkey01_idxfn,true>
  > AVG_QTYLINEITEM1_L1_2_DELTA_map;
  typedef HashIndex<AVG_QTYLINEITEM1_L1_2_DELTA_entry,long,AVG_QTYLINEITEM1_L1_2_DELTA_mapkey01_idxfn,true> HashIndex_AVG_QTYLINEITEM1_L1_2_DELTA_map_01;
  
  struct AVG_PRICE_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_PRICE_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_PRICE_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_PRICE_entry(const AVG_PRICE_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_PRICE_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_PRICE_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_PRICE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_PRICE_entry& x, const AVG_PRICE_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_PRICE_entry,DOUBLE_TYPE,
    HashIndex<AVG_PRICE_entry,DOUBLE_TYPE,AVG_PRICE_mapkey01_idxfn,true>
  > AVG_PRICE_map;
  typedef HashIndex<AVG_PRICE_entry,DOUBLE_TYPE,AVG_PRICE_mapkey01_idxfn,true> HashIndex_AVG_PRICE_map_01;
  
  struct AVG_PRICELINEITEM1_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_PRICELINEITEM1_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_PRICELINEITEM1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_PRICELINEITEM1_entry(const AVG_PRICELINEITEM1_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_PRICELINEITEM1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_PRICELINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_PRICELINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_PRICELINEITEM1_entry& x, const AVG_PRICELINEITEM1_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_PRICELINEITEM1_entry,DOUBLE_TYPE,
    HashIndex<AVG_PRICELINEITEM1_entry,DOUBLE_TYPE,AVG_PRICELINEITEM1_mapkey01_idxfn,true>
  > AVG_PRICELINEITEM1_map;
  typedef HashIndex<AVG_PRICELINEITEM1_entry,DOUBLE_TYPE,AVG_PRICELINEITEM1_mapkey01_idxfn,true> HashIndex_AVG_PRICELINEITEM1_map_01;
  
  struct AVG_DISC_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_DISC_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_DISC_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_DISC_entry(const AVG_DISC_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_DISC_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_DISC_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_DISC_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_DISC_entry& x, const AVG_DISC_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_DISC_entry,DOUBLE_TYPE,
    HashIndex<AVG_DISC_entry,DOUBLE_TYPE,AVG_DISC_mapkey01_idxfn,true>
  > AVG_DISC_map;
  typedef HashIndex<AVG_DISC_entry,DOUBLE_TYPE,AVG_DISC_mapkey01_idxfn,true> HashIndex_AVG_DISC_map_01;
  
  struct AVG_DISCLINEITEM1_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_DISCLINEITEM1_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_DISCLINEITEM1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_DISCLINEITEM1_entry(const AVG_DISCLINEITEM1_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_DISCLINEITEM1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_DISCLINEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_DISCLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_DISCLINEITEM1_entry& x, const AVG_DISCLINEITEM1_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_DISCLINEITEM1_entry,DOUBLE_TYPE,
    HashIndex<AVG_DISCLINEITEM1_entry,DOUBLE_TYPE,AVG_DISCLINEITEM1_mapkey01_idxfn,true>
  > AVG_DISCLINEITEM1_map;
  typedef HashIndex<AVG_DISCLINEITEM1_entry,DOUBLE_TYPE,AVG_DISCLINEITEM1_mapkey01_idxfn,true> HashIndex_AVG_DISCLINEITEM1_map_01;
  
  struct AVG_DISCLINEITEM4_DELTA_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_DISCLINEITEM4_DELTA_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_DISCLINEITEM4_DELTA_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_DISCLINEITEM4_DELTA_entry(const AVG_DISCLINEITEM4_DELTA_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_DISCLINEITEM4_DELTA_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_DISCLINEITEM4_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_DISCLINEITEM4_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_DISCLINEITEM4_DELTA_entry& x, const AVG_DISCLINEITEM4_DELTA_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_DISCLINEITEM4_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AVG_DISCLINEITEM4_DELTA_entry,DOUBLE_TYPE,AVG_DISCLINEITEM4_DELTA_mapkey01_idxfn,true>
  > AVG_DISCLINEITEM4_DELTA_map;
  typedef HashIndex<AVG_DISCLINEITEM4_DELTA_entry,DOUBLE_TYPE,AVG_DISCLINEITEM4_DELTA_mapkey01_idxfn,true> HashIndex_AVG_DISCLINEITEM4_DELTA_map_01;
  
  struct COUNT_ORDER_entry {
    STRING_TYPE LINEITEM_RETURNFLAG; STRING_TYPE LINEITEM_LINESTATUS; long __av; 
    explicit COUNT_ORDER_entry() { /*LINEITEM_RETURNFLAG = ""; LINEITEM_LINESTATUS = ""; __av = 0L; */ }
    explicit COUNT_ORDER_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1; __av = c2; }
    COUNT_ORDER_entry(const COUNT_ORDER_entry& other) : LINEITEM_RETURNFLAG( other.LINEITEM_RETURNFLAG ), LINEITEM_LINESTATUS( other.LINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE COUNT_ORDER_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { LINEITEM_RETURNFLAG = c0; LINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_ORDER_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_ORDER_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LINEITEM_RETURNFLAG);
      hash_combine(h, e.LINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_ORDER_entry& x, const COUNT_ORDER_entry& y) {
      return x.LINEITEM_RETURNFLAG == y.LINEITEM_RETURNFLAG && x.LINEITEM_LINESTATUS == y.LINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<COUNT_ORDER_entry,long,
    HashIndex<COUNT_ORDER_entry,long,COUNT_ORDER_mapkey01_idxfn,true>
  > COUNT_ORDER_map;
  typedef HashIndex<COUNT_ORDER_entry,long,COUNT_ORDER_mapkey01_idxfn,true> HashIndex_COUNT_ORDER_map_01;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const SUM_QTY_map& _SUM_QTY = get_SUM_QTY();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUM_QTY), _SUM_QTY, "\t");
      ar << "\n";
      const SUM_BASE_PRICE_map& _SUM_BASE_PRICE = get_SUM_BASE_PRICE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUM_BASE_PRICE), _SUM_BASE_PRICE, "\t");
      ar << "\n";
      const SUM_DISC_PRICE_map& _SUM_DISC_PRICE = get_SUM_DISC_PRICE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUM_DISC_PRICE), _SUM_DISC_PRICE, "\t");
      ar << "\n";
      const SUM_CHARGE_map& _SUM_CHARGE = get_SUM_CHARGE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUM_CHARGE), _SUM_CHARGE, "\t");
      ar << "\n";
      const AVG_QTY_map& _AVG_QTY = get_AVG_QTY();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AVG_QTY), _AVG_QTY, "\t");
      ar << "\n";
      const AVG_PRICE_map& _AVG_PRICE = get_AVG_PRICE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AVG_PRICE), _AVG_PRICE, "\t");
      ar << "\n";
      const AVG_DISC_map& _AVG_DISC = get_AVG_DISC();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AVG_DISC), _AVG_DISC, "\t");
      ar << "\n";
      const COUNT_ORDER_map& _COUNT_ORDER = get_COUNT_ORDER();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(COUNT_ORDER), _COUNT_ORDER, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const SUM_QTY_map& get_SUM_QTY() const {
      return SUM_QTY;
    
    }
    const SUM_BASE_PRICE_map& get_SUM_BASE_PRICE() const {
      return SUM_BASE_PRICE;
    
    }
    const SUM_DISC_PRICE_map& get_SUM_DISC_PRICE() const {
      return SUM_DISC_PRICE;
    
    }
    const SUM_CHARGE_map& get_SUM_CHARGE() const {
      return SUM_CHARGE;
    
    }
    const AVG_QTY_map& get_AVG_QTY() const {
      return AVG_QTY;
    
    }
    const AVG_PRICE_map& get_AVG_PRICE() const {
      return AVG_PRICE;
    
    }
    const AVG_DISC_map& get_AVG_DISC() const {
      return AVG_DISC;
    
    }
    const COUNT_ORDER_map& get_COUNT_ORDER() const {
      return COUNT_ORDER;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    SUM_QTY_map SUM_QTY;
    SUM_BASE_PRICE_map SUM_BASE_PRICE;
    SUM_DISC_PRICE_map SUM_DISC_PRICE;
    SUM_CHARGE_map SUM_CHARGE;
    AVG_QTY_map AVG_QTY;
    AVG_PRICE_map AVG_PRICE;
    AVG_DISC_map AVG_DISC;
    COUNT_ORDER_map COUNT_ORDER;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c1 = Udate(STRING_TYPE("1997-9-1"));
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

        SUM_QTYLINEITEM1_DELTA.clear();
        SUM_BASE_PRICELINEITEM1_DELTA.clear();
        SUM_DISC_PRICELINEITEM1_DELTA.clear();
        SUM_CHARGELINEITEM1_DELTA.clear();
        AVG_QTYLINEITEM1_L1_2_DELTA.clear();
        AVG_QTYLINEITEM1_DOMAIN1.clear();
        AVG_DISCLINEITEM4_DELTA.clear();

        {  
          for (size_t i = 0; i < DELTA_LINEITEM.size; i++) 
          {
                //long lineitem_orderkey = DELTA_LINEITEM.orderkey[i];
                //long lineitem_partkey = DELTA_LINEITEM.partkey[i];
                //long lineitem_suppkey = DELTA_LINEITEM.suppkey[i];
                //long lineitem_linenumber = DELTA_LINEITEM.linenumber[i];
                DOUBLE_TYPE lineitem_quantity = DELTA_LINEITEM.quantity[i];
                DOUBLE_TYPE lineitem_extendedprice = DELTA_LINEITEM.extendedprice[i];
                DOUBLE_TYPE lineitem_discount = DELTA_LINEITEM.discount[i];
                DOUBLE_TYPE lineitem_tax = DELTA_LINEITEM.tax[i];
                STRING_TYPE lineitem_returnflag = DELTA_LINEITEM.returnflag[i];
                STRING_TYPE lineitem_linestatus = DELTA_LINEITEM.linestatus[i];
                date lineitem_shipdate = DELTA_LINEITEM.shipdate[i];
                // date lineitem_commitdate = DELTA_LINEITEM.commitdate[i];
                // date lineitem_receiptdate = DELTA_LINEITEM.receiptdate[i];
                // STRING_TYPE lineitem_shipinstruct = DELTA_LINEITEM.shipinstruct[i];
                // STRING_TYPE lineitem_shipmode = DELTA_LINEITEM.shipmode[i];
                // STRING_TYPE lineitem_comment = DELTA_LINEITEM.comment[i];
                long v1 = 1L;
                (/*if */(c1 >= lineitem_shipdate) ? SUM_QTYLINEITEM1_DELTA.addOrDelOnZero(se1.modify(lineitem_returnflag,lineitem_linestatus),(v1 * lineitem_quantity)) : (void)0);
                long v2 = 1L;
                (/*if */(c1 >= lineitem_shipdate) ? SUM_BASE_PRICELINEITEM1_DELTA.addOrDelOnZero(se2.modify(lineitem_returnflag,lineitem_linestatus),(v2 * lineitem_extendedprice)) : (void)0);
                long v3 = 1L;
                (/*if */(c1 >= lineitem_shipdate) ? SUM_DISC_PRICELINEITEM1_DELTA.addOrDelOnZero(se3.modify(lineitem_returnflag,lineitem_linestatus),(v3 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);              
                long v4 = 1L;
                (/*if */(c1 >= lineitem_shipdate) ? SUM_CHARGELINEITEM1_DELTA.addOrDelOnZero(se4.modify(lineitem_returnflag,lineitem_linestatus),(v4 * (lineitem_extendedprice * ((1L + (-1L * lineitem_discount)) * (1L + lineitem_tax))))) : (void)0);
                long v5 = 1L;
                (/*if */(c1 >= lineitem_shipdate) ? AVG_QTYLINEITEM1_L1_2_DELTA.addOrDelOnZero(se5.modify(lineitem_returnflag,lineitem_linestatus),v5) : (void)0);
                long v6 = 1L;
                (/*if */(c1 >= lineitem_shipdate) ? AVG_QTYLINEITEM1_DOMAIN1.addOrDelOnZero(se6.modify(lineitem_returnflag,lineitem_linestatus),(v6 != 0 ? 1L : 0L)) : (void)0);
                long v7 = 1L;
                (/*if */(c1 >= lineitem_shipdate) ? AVG_DISCLINEITEM4_DELTA.addOrDelOnZero(se7.modify(lineitem_returnflag,lineitem_linestatus),(v7 * lineitem_discount)) : (void)0);
          }
        }
        
        
        {  // foreach
          const HashIndex_SUM_QTYLINEITEM1_DELTA_map_01* i8 = static_cast<HashIndex_SUM_QTYLINEITEM1_DELTA_map_01*>(SUM_QTYLINEITEM1_DELTA.index[0]);
          HashIndex_SUM_QTYLINEITEM1_DELTA_map_01::IdxNode* n8; 
          SUM_QTYLINEITEM1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                STRING_TYPE lineitem_returnflag = e8->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e8->LINEITEM_LINESTATUS;
                DOUBLE_TYPE v8 = e8->__av;
                SUM_QTY.addOrDelOnZero(se8.modify(lineitem_returnflag,lineitem_linestatus),v8);
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_BASE_PRICELINEITEM1_DELTA_map_01* i9 = static_cast<HashIndex_SUM_BASE_PRICELINEITEM1_DELTA_map_01*>(SUM_BASE_PRICELINEITEM1_DELTA.index[0]);
          HashIndex_SUM_BASE_PRICELINEITEM1_DELTA_map_01::IdxNode* n9; 
          SUM_BASE_PRICELINEITEM1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                STRING_TYPE lineitem_returnflag = e9->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e9->LINEITEM_LINESTATUS;
                DOUBLE_TYPE v9 = e9->__av;
                SUM_BASE_PRICE.addOrDelOnZero(se9.modify(lineitem_returnflag,lineitem_linestatus),v9);
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_DISC_PRICELINEITEM1_DELTA_map_01* i10 = static_cast<HashIndex_SUM_DISC_PRICELINEITEM1_DELTA_map_01*>(SUM_DISC_PRICELINEITEM1_DELTA.index[0]);
          HashIndex_SUM_DISC_PRICELINEITEM1_DELTA_map_01::IdxNode* n10; 
          SUM_DISC_PRICELINEITEM1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                STRING_TYPE lineitem_returnflag = e10->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e10->LINEITEM_LINESTATUS;
                DOUBLE_TYPE v10 = e10->__av;
                SUM_DISC_PRICE.addOrDelOnZero(se10.modify(lineitem_returnflag,lineitem_linestatus),v10);
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_CHARGELINEITEM1_DELTA_map_01* i11 = static_cast<HashIndex_SUM_CHARGELINEITEM1_DELTA_map_01*>(SUM_CHARGELINEITEM1_DELTA.index[0]);
          HashIndex_SUM_CHARGELINEITEM1_DELTA_map_01::IdxNode* n11; 
          SUM_CHARGELINEITEM1_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                STRING_TYPE lineitem_returnflag = e11->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e11->LINEITEM_LINESTATUS;
                DOUBLE_TYPE v11 = e11->__av;
                SUM_CHARGE.addOrDelOnZero(se11.modify(lineitem_returnflag,lineitem_linestatus),v11);
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01* i12 = static_cast<HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01*>(AVG_QTYLINEITEM1_DOMAIN1.index[0]);
          HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01::IdxNode* n12; 
          AVG_QTYLINEITEM1_DOMAIN1_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                STRING_TYPE lineitem_returnflag = e12->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e12->LINEITEM_LINESTATUS;
                long v12 = e12->__av;
                DOUBLE_TYPE agg1 = 0.0;
                long l1 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se14.modify(lineitem_returnflag,lineitem_linestatus)) + AVG_QTYLINEITEM1_L1_2_DELTA.getValueOrDefault(se15.modify(lineitem_returnflag,lineitem_linestatus)));
                (/*if */(0L != l1) ? agg1 += Udiv(Ulistmax(1L, l1)) : 0.0);
                DOUBLE_TYPE agg2 = 0.0;
                long l2 = AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se16.modify(lineitem_returnflag,lineitem_linestatus));
                (/*if */(0L != l2) ? agg2 += Udiv(Ulistmax(1L, l2)) : 0.0);
                DOUBLE_TYPE agg3 = 0.0;
                long l3 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se18.modify(lineitem_returnflag,lineitem_linestatus)) + AVG_QTYLINEITEM1_L1_2_DELTA.getValueOrDefault(se19.modify(lineitem_returnflag,lineitem_linestatus)));
                (/*if */(0L != l3) ? agg3 += Udiv(Ulistmax(1L, l3)) : 0.0);
                AVG_QTY.addOrDelOnZero(se12.modify(lineitem_returnflag,lineitem_linestatus),((v12 != 0 ? 1L : 0L) * ((AVG_QTYLINEITEM1.getValueOrDefault(se13.modify(lineitem_returnflag,lineitem_linestatus)) * (agg1 + (agg2 * -1L))) + (SUM_QTYLINEITEM1_DELTA.getValueOrDefault(se17.modify(lineitem_returnflag,lineitem_linestatus)) * agg3))));
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_QTYLINEITEM1_DELTA_map_01* i13 = static_cast<HashIndex_SUM_QTYLINEITEM1_DELTA_map_01*>(SUM_QTYLINEITEM1_DELTA.index[0]);
          HashIndex_SUM_QTYLINEITEM1_DELTA_map_01::IdxNode* n13; 
          SUM_QTYLINEITEM1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                STRING_TYPE lineitem_returnflag = e13->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e13->LINEITEM_LINESTATUS;
                DOUBLE_TYPE v13 = e13->__av;
                AVG_QTYLINEITEM1.addOrDelOnZero(se20.modify(lineitem_returnflag,lineitem_linestatus),v13);
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01* i14 = static_cast<HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01*>(AVG_QTYLINEITEM1_DOMAIN1.index[0]);
          HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01::IdxNode* n14; 
          AVG_QTYLINEITEM1_DOMAIN1_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                STRING_TYPE lineitem_returnflag = e14->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e14->LINEITEM_LINESTATUS;
                long v14 = e14->__av;
                DOUBLE_TYPE agg4 = 0.0;
                long l4 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se23.modify(lineitem_returnflag,lineitem_linestatus)) + AVG_QTYLINEITEM1_L1_2_DELTA.getValueOrDefault(se24.modify(lineitem_returnflag,lineitem_linestatus)));
                (/*if */(0L != l4) ? agg4 += Udiv(Ulistmax(1L, l4)) : 0.0);
                DOUBLE_TYPE agg5 = 0.0;
                long l5 = AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se25.modify(lineitem_returnflag,lineitem_linestatus));
                (/*if */(0L != l5) ? agg5 += Udiv(Ulistmax(1L, l5)) : 0.0);
                DOUBLE_TYPE agg6 = 0.0;
                long l6 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se27.modify(lineitem_returnflag,lineitem_linestatus)) + AVG_QTYLINEITEM1_L1_2_DELTA.getValueOrDefault(se28.modify(lineitem_returnflag,lineitem_linestatus)));
                (/*if */(0L != l6) ? agg6 += Udiv(Ulistmax(1L, l6)) : 0.0);
                AVG_PRICE.addOrDelOnZero(se21.modify(lineitem_returnflag,lineitem_linestatus),((v14 != 0 ? 1L : 0L) * ((AVG_PRICELINEITEM1.getValueOrDefault(se22.modify(lineitem_returnflag,lineitem_linestatus)) * (agg4 + (agg5 * -1L))) + (SUM_BASE_PRICELINEITEM1_DELTA.getValueOrDefault(se26.modify(lineitem_returnflag,lineitem_linestatus)) * agg6))));
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUM_BASE_PRICELINEITEM1_DELTA_map_01* i15 = static_cast<HashIndex_SUM_BASE_PRICELINEITEM1_DELTA_map_01*>(SUM_BASE_PRICELINEITEM1_DELTA.index[0]);
          HashIndex_SUM_BASE_PRICELINEITEM1_DELTA_map_01::IdxNode* n15; 
          SUM_BASE_PRICELINEITEM1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                STRING_TYPE lineitem_returnflag = e15->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e15->LINEITEM_LINESTATUS;
                DOUBLE_TYPE v15 = e15->__av;
                AVG_PRICELINEITEM1.addOrDelOnZero(se29.modify(lineitem_returnflag,lineitem_linestatus),v15);
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01* i16 = static_cast<HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01*>(AVG_QTYLINEITEM1_DOMAIN1.index[0]);
          HashIndex_AVG_QTYLINEITEM1_DOMAIN1_map_01::IdxNode* n16; 
          AVG_QTYLINEITEM1_DOMAIN1_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                STRING_TYPE lineitem_returnflag = e16->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e16->LINEITEM_LINESTATUS;
                long v16 = e16->__av;
                DOUBLE_TYPE agg7 = 0.0;
                long l7 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se32.modify(lineitem_returnflag,lineitem_linestatus)) + AVG_QTYLINEITEM1_L1_2_DELTA.getValueOrDefault(se33.modify(lineitem_returnflag,lineitem_linestatus)));
                (/*if */(0L != l7) ? agg7 += Udiv(Ulistmax(1L, l7)) : 0.0);
                DOUBLE_TYPE agg8 = 0.0;
                long l8 = AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se34.modify(lineitem_returnflag,lineitem_linestatus));
                (/*if */(0L != l8) ? agg8 += Udiv(Ulistmax(1L, l8)) : 0.0);
                DOUBLE_TYPE agg9 = 0.0;
                long l9 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se36.modify(lineitem_returnflag,lineitem_linestatus)) + AVG_QTYLINEITEM1_L1_2_DELTA.getValueOrDefault(se37.modify(lineitem_returnflag,lineitem_linestatus)));
                (/*if */(0L != l9) ? agg9 += Udiv(Ulistmax(1L, l9)) : 0.0);
                AVG_DISC.addOrDelOnZero(se30.modify(lineitem_returnflag,lineitem_linestatus),((v16 != 0 ? 1L : 0L) * ((AVG_DISCLINEITEM1.getValueOrDefault(se31.modify(lineitem_returnflag,lineitem_linestatus)) * (agg7 + (agg8 * -1L))) + (AVG_DISCLINEITEM4_DELTA.getValueOrDefault(se35.modify(lineitem_returnflag,lineitem_linestatus)) * agg9))));
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_QTYLINEITEM1_L1_2_DELTA_map_01* i17 = static_cast<HashIndex_AVG_QTYLINEITEM1_L1_2_DELTA_map_01*>(AVG_QTYLINEITEM1_L1_2_DELTA.index[0]);
          HashIndex_AVG_QTYLINEITEM1_L1_2_DELTA_map_01::IdxNode* n17; 
          AVG_QTYLINEITEM1_L1_2_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                STRING_TYPE lineitem_returnflag = e17->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e17->LINEITEM_LINESTATUS;
                long v17 = e17->__av;
                AVG_QTYLINEITEM1_L1_1.addOrDelOnZero(se38.modify(lineitem_returnflag,lineitem_linestatus),v17);
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_DISCLINEITEM4_DELTA_map_01* i18 = static_cast<HashIndex_AVG_DISCLINEITEM4_DELTA_map_01*>(AVG_DISCLINEITEM4_DELTA.index[0]);
          HashIndex_AVG_DISCLINEITEM4_DELTA_map_01::IdxNode* n18; 
          AVG_DISCLINEITEM4_DELTA_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                STRING_TYPE lineitem_returnflag = e18->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e18->LINEITEM_LINESTATUS;
                DOUBLE_TYPE v18 = e18->__av;
                AVG_DISCLINEITEM1.addOrDelOnZero(se39.modify(lineitem_returnflag,lineitem_linestatus),v18);
              n18 = n18->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AVG_QTYLINEITEM1_L1_2_DELTA_map_01* i19 = static_cast<HashIndex_AVG_QTYLINEITEM1_L1_2_DELTA_map_01*>(AVG_QTYLINEITEM1_L1_2_DELTA.index[0]);
          HashIndex_AVG_QTYLINEITEM1_L1_2_DELTA_map_01::IdxNode* n19; 
          AVG_QTYLINEITEM1_L1_2_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                STRING_TYPE lineitem_returnflag = e19->LINEITEM_RETURNFLAG;
                STRING_TYPE lineitem_linestatus = e19->LINEITEM_LINESTATUS;
                long v19 = e19->__av;
                COUNT_ORDER.addOrDelOnZero(se40.modify(lineitem_returnflag,lineitem_linestatus),v19);
              n19 = n19->nxt;
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
    SUM_QTYLINEITEM1_DELTA_entry se1;
    SUM_BASE_PRICELINEITEM1_DELTA_entry se2;
    SUM_DISC_PRICELINEITEM1_DELTA_entry se3;
    SUM_CHARGELINEITEM1_DELTA_entry se4;
    AVG_QTYLINEITEM1_L1_2_DELTA_entry se5;
    AVG_QTYLINEITEM1_DOMAIN1_entry se6;
    AVG_DISCLINEITEM4_DELTA_entry se7;
    SUM_QTY_entry se8;
    SUM_BASE_PRICE_entry se9;
    SUM_DISC_PRICE_entry se10;
    SUM_CHARGE_entry se11;
    AVG_QTY_entry se12;
    AVG_QTYLINEITEM1_entry se13;
    AVG_QTYLINEITEM1_L1_1_entry se14;
    AVG_QTYLINEITEM1_L1_2_DELTA_entry se15;
    AVG_QTYLINEITEM1_L1_1_entry se16;
    SUM_QTYLINEITEM1_DELTA_entry se17;
    AVG_QTYLINEITEM1_L1_1_entry se18;
    AVG_QTYLINEITEM1_L1_2_DELTA_entry se19;
    AVG_QTYLINEITEM1_entry se20;
    AVG_PRICE_entry se21;
    AVG_PRICELINEITEM1_entry se22;
    AVG_QTYLINEITEM1_L1_1_entry se23;
    AVG_QTYLINEITEM1_L1_2_DELTA_entry se24;
    AVG_QTYLINEITEM1_L1_1_entry se25;
    SUM_BASE_PRICELINEITEM1_DELTA_entry se26;
    AVG_QTYLINEITEM1_L1_1_entry se27;
    AVG_QTYLINEITEM1_L1_2_DELTA_entry se28;
    AVG_PRICELINEITEM1_entry se29;
    AVG_DISC_entry se30;
    AVG_DISCLINEITEM1_entry se31;
    AVG_QTYLINEITEM1_L1_1_entry se32;
    AVG_QTYLINEITEM1_L1_2_DELTA_entry se33;
    AVG_QTYLINEITEM1_L1_1_entry se34;
    AVG_DISCLINEITEM4_DELTA_entry se35;
    AVG_QTYLINEITEM1_L1_1_entry se36;
    AVG_QTYLINEITEM1_L1_2_DELTA_entry se37;
    AVG_QTYLINEITEM1_L1_1_entry se38;
    AVG_DISCLINEITEM1_entry se39;
    COUNT_ORDER_entry se40;
  
    /* Data structures used for storing materialized views */
    SUM_QTYLINEITEM1_DELTA_map SUM_QTYLINEITEM1_DELTA;
    SUM_BASE_PRICELINEITEM1_DELTA_map SUM_BASE_PRICELINEITEM1_DELTA;
    SUM_DISC_PRICELINEITEM1_DELTA_map SUM_DISC_PRICELINEITEM1_DELTA;
    SUM_CHARGELINEITEM1_DELTA_map SUM_CHARGELINEITEM1_DELTA;
    AVG_QTYLINEITEM1_DOMAIN1_map AVG_QTYLINEITEM1_DOMAIN1;
    AVG_QTYLINEITEM1_map AVG_QTYLINEITEM1;
    AVG_QTYLINEITEM1_L1_1_map AVG_QTYLINEITEM1_L1_1;
    AVG_QTYLINEITEM1_L1_2_DELTA_map AVG_QTYLINEITEM1_L1_2_DELTA;
    AVG_PRICELINEITEM1_map AVG_PRICELINEITEM1;
    AVG_DISCLINEITEM1_map AVG_DISCLINEITEM1;
    AVG_DISCLINEITEM4_DELTA_map AVG_DISCLINEITEM4_DELTA;
    DELTA_LINEITEM_map DELTA_LINEITEM;
    
    /*const static*/ long c1;
  
  };

}
