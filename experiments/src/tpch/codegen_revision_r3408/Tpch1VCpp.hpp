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
  
  struct AVG_QTYLINEITEM1_L1_1_entry {
    STRING_TYPE AVG_QTYLINEITEMLINEITEM_RETURNFLAG; STRING_TYPE AVG_QTYLINEITEMLINEITEM_LINESTATUS; long __av; 
    explicit AVG_QTYLINEITEM1_L1_1_entry() { /*AVG_QTYLINEITEMLINEITEM_RETURNFLAG = ""; AVG_QTYLINEITEMLINEITEM_LINESTATUS = ""; __av = 0L; */ }
    explicit AVG_QTYLINEITEM1_L1_1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { AVG_QTYLINEITEMLINEITEM_RETURNFLAG = c0; AVG_QTYLINEITEMLINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_QTYLINEITEM1_L1_1_entry(const AVG_QTYLINEITEM1_L1_1_entry& other) : AVG_QTYLINEITEMLINEITEM_RETURNFLAG( other.AVG_QTYLINEITEMLINEITEM_RETURNFLAG ), AVG_QTYLINEITEMLINEITEM_LINESTATUS( other.AVG_QTYLINEITEMLINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_QTYLINEITEM1_L1_1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AVG_QTYLINEITEMLINEITEM_RETURNFLAG = c0; AVG_QTYLINEITEMLINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_QTYLINEITEMLINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_QTYLINEITEMLINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_QTYLINEITEM1_L1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_QTYLINEITEM1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_QTYLINEITEMLINEITEM_RETURNFLAG);
      hash_combine(h, e.AVG_QTYLINEITEMLINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_QTYLINEITEM1_L1_1_entry& x, const AVG_QTYLINEITEM1_L1_1_entry& y) {
      return x.AVG_QTYLINEITEMLINEITEM_RETURNFLAG == y.AVG_QTYLINEITEMLINEITEM_RETURNFLAG && x.AVG_QTYLINEITEMLINEITEM_LINESTATUS == y.AVG_QTYLINEITEMLINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_QTYLINEITEM1_L1_1_entry,long,
    HashIndex<AVG_QTYLINEITEM1_L1_1_entry,long,AVG_QTYLINEITEM1_L1_1_mapkey01_idxfn,true>
  > AVG_QTYLINEITEM1_L1_1_map;
  typedef HashIndex<AVG_QTYLINEITEM1_L1_1_entry,long,AVG_QTYLINEITEM1_L1_1_mapkey01_idxfn,true> HashIndex_AVG_QTYLINEITEM1_L1_1_map_01;
  
  struct AVG_QTYLINEITEM2_entry {
    STRING_TYPE AVG_QTYLINEITEMLINEITEM_RETURNFLAG; STRING_TYPE AVG_QTYLINEITEMLINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_QTYLINEITEM2_entry() { /*AVG_QTYLINEITEMLINEITEM_RETURNFLAG = ""; AVG_QTYLINEITEMLINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_QTYLINEITEM2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AVG_QTYLINEITEMLINEITEM_RETURNFLAG = c0; AVG_QTYLINEITEMLINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_QTYLINEITEM2_entry(const AVG_QTYLINEITEM2_entry& other) : AVG_QTYLINEITEMLINEITEM_RETURNFLAG( other.AVG_QTYLINEITEMLINEITEM_RETURNFLAG ), AVG_QTYLINEITEMLINEITEM_LINESTATUS( other.AVG_QTYLINEITEMLINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_QTYLINEITEM2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AVG_QTYLINEITEMLINEITEM_RETURNFLAG = c0; AVG_QTYLINEITEMLINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_QTYLINEITEMLINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_QTYLINEITEMLINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_QTYLINEITEM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_QTYLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_QTYLINEITEMLINEITEM_RETURNFLAG);
      hash_combine(h, e.AVG_QTYLINEITEMLINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_QTYLINEITEM2_entry& x, const AVG_QTYLINEITEM2_entry& y) {
      return x.AVG_QTYLINEITEMLINEITEM_RETURNFLAG == y.AVG_QTYLINEITEMLINEITEM_RETURNFLAG && x.AVG_QTYLINEITEMLINEITEM_LINESTATUS == y.AVG_QTYLINEITEMLINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_QTYLINEITEM2_entry,DOUBLE_TYPE,
    HashIndex<AVG_QTYLINEITEM2_entry,DOUBLE_TYPE,AVG_QTYLINEITEM2_mapkey01_idxfn,true>
  > AVG_QTYLINEITEM2_map;
  typedef HashIndex<AVG_QTYLINEITEM2_entry,DOUBLE_TYPE,AVG_QTYLINEITEM2_mapkey01_idxfn,true> HashIndex_AVG_QTYLINEITEM2_map_01;
  
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
  
  struct AVG_PRICELINEITEM2_entry {
    STRING_TYPE AVG_PRICELINEITEMLINEITEM_RETURNFLAG; STRING_TYPE AVG_PRICELINEITEMLINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_PRICELINEITEM2_entry() { /*AVG_PRICELINEITEMLINEITEM_RETURNFLAG = ""; AVG_PRICELINEITEMLINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_PRICELINEITEM2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AVG_PRICELINEITEMLINEITEM_RETURNFLAG = c0; AVG_PRICELINEITEMLINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_PRICELINEITEM2_entry(const AVG_PRICELINEITEM2_entry& other) : AVG_PRICELINEITEMLINEITEM_RETURNFLAG( other.AVG_PRICELINEITEMLINEITEM_RETURNFLAG ), AVG_PRICELINEITEMLINEITEM_LINESTATUS( other.AVG_PRICELINEITEMLINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_PRICELINEITEM2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AVG_PRICELINEITEMLINEITEM_RETURNFLAG = c0; AVG_PRICELINEITEMLINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_PRICELINEITEMLINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_PRICELINEITEMLINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_PRICELINEITEM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_PRICELINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_PRICELINEITEMLINEITEM_RETURNFLAG);
      hash_combine(h, e.AVG_PRICELINEITEMLINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_PRICELINEITEM2_entry& x, const AVG_PRICELINEITEM2_entry& y) {
      return x.AVG_PRICELINEITEMLINEITEM_RETURNFLAG == y.AVG_PRICELINEITEMLINEITEM_RETURNFLAG && x.AVG_PRICELINEITEMLINEITEM_LINESTATUS == y.AVG_PRICELINEITEMLINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_PRICELINEITEM2_entry,DOUBLE_TYPE,
    HashIndex<AVG_PRICELINEITEM2_entry,DOUBLE_TYPE,AVG_PRICELINEITEM2_mapkey01_idxfn,true>
  > AVG_PRICELINEITEM2_map;
  typedef HashIndex<AVG_PRICELINEITEM2_entry,DOUBLE_TYPE,AVG_PRICELINEITEM2_mapkey01_idxfn,true> HashIndex_AVG_PRICELINEITEM2_map_01;
  
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
  
  struct AVG_DISCLINEITEM2_entry {
    STRING_TYPE AVG_DISCLINEITEMLINEITEM_RETURNFLAG; STRING_TYPE AVG_DISCLINEITEMLINEITEM_LINESTATUS; DOUBLE_TYPE __av; 
    explicit AVG_DISCLINEITEM2_entry() { /*AVG_DISCLINEITEMLINEITEM_RETURNFLAG = ""; AVG_DISCLINEITEMLINEITEM_LINESTATUS = ""; __av = 0.0; */ }
    explicit AVG_DISCLINEITEM2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AVG_DISCLINEITEMLINEITEM_RETURNFLAG = c0; AVG_DISCLINEITEMLINEITEM_LINESTATUS = c1; __av = c2; }
    AVG_DISCLINEITEM2_entry(const AVG_DISCLINEITEM2_entry& other) : AVG_DISCLINEITEMLINEITEM_RETURNFLAG( other.AVG_DISCLINEITEMLINEITEM_RETURNFLAG ), AVG_DISCLINEITEMLINEITEM_LINESTATUS( other.AVG_DISCLINEITEMLINEITEM_LINESTATUS ), __av( other.__av ) {}
    FORCE_INLINE AVG_DISCLINEITEM2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AVG_DISCLINEITEMLINEITEM_RETURNFLAG = c0; AVG_DISCLINEITEMLINEITEM_LINESTATUS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_DISCLINEITEMLINEITEM_RETURNFLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_DISCLINEITEMLINEITEM_LINESTATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_DISCLINEITEM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_DISCLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_DISCLINEITEMLINEITEM_RETURNFLAG);
      hash_combine(h, e.AVG_DISCLINEITEMLINEITEM_LINESTATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_DISCLINEITEM2_entry& x, const AVG_DISCLINEITEM2_entry& y) {
      return x.AVG_DISCLINEITEMLINEITEM_RETURNFLAG == y.AVG_DISCLINEITEMLINEITEM_RETURNFLAG && x.AVG_DISCLINEITEMLINEITEM_LINESTATUS == y.AVG_DISCLINEITEMLINEITEM_LINESTATUS;
    }
  };
  
  typedef MultiHashMap<AVG_DISCLINEITEM2_entry,DOUBLE_TYPE,
    HashIndex<AVG_DISCLINEITEM2_entry,DOUBLE_TYPE,AVG_DISCLINEITEM2_mapkey01_idxfn,true>
  > AVG_DISCLINEITEM2_map;
  typedef HashIndex<AVG_DISCLINEITEM2_entry,DOUBLE_TYPE,AVG_DISCLINEITEM2_mapkey01_idxfn,true> HashIndex_AVG_DISCLINEITEM2_map_01;
  
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
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
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
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(c1 >= lineitem_shipdate) ? SUM_QTY.addOrDelOnZero(se1.modify(lineitem_returnflag,lineitem_linestatus),lineitem_quantity) : (void)0);
        (/*if */(c1 >= lineitem_shipdate) ? SUM_BASE_PRICE.addOrDelOnZero(se2.modify(lineitem_returnflag,lineitem_linestatus),lineitem_extendedprice) : (void)0);
        (/*if */(c1 >= lineitem_shipdate) ? SUM_DISC_PRICE.addOrDelOnZero(se3.modify(lineitem_returnflag,lineitem_linestatus),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        (/*if */(c1 >= lineitem_shipdate) ? SUM_CHARGE.addOrDelOnZero(se4.modify(lineitem_returnflag,lineitem_linestatus),(lineitem_extendedprice * ((1L + (-1L * lineitem_discount)) * (1L + lineitem_tax)))) : (void)0);
        DOUBLE_TYPE agg1 = 0.0;
        long l1 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se7.modify(lineitem_returnflag,lineitem_linestatus)) + (/*if */(c1 >= lineitem_shipdate) ? 1L : 0L));
        (/*if */(0L != l1) ? agg1 += Udiv(Ulistmax(1L, l1)) : 0.0);
        DOUBLE_TYPE agg2 = 0.0;
        long l2 = AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se8.modify(lineitem_returnflag,lineitem_linestatus));
        (/*if */(0L != l2) ? agg2 += Udiv(Ulistmax(1L, l2)) : 0.0);
        DOUBLE_TYPE agg3 = 0.0;
        long l3 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se9.modify(lineitem_returnflag,lineitem_linestatus)) + 1L);
        (/*if */(0L != l3) ? agg3 += Udiv(Ulistmax(1L, l3)) : 0.0);
        AVG_QTY.addOrDelOnZero(se5.modify(lineitem_returnflag,lineitem_linestatus),((AVG_QTYLINEITEM2.getValueOrDefault(se6.modify(lineitem_returnflag,lineitem_linestatus)) * (agg1 + (agg2 * -1L))) + (/*if */(c1 >= lineitem_shipdate) ? (agg3 * lineitem_quantity) : 0.0)));
        (/*if */(c1 >= lineitem_shipdate) ? AVG_QTYLINEITEM2.addOrDelOnZero(se10.modify(lineitem_returnflag,lineitem_linestatus),lineitem_quantity) : (void)0);
        DOUBLE_TYPE agg4 = 0.0;
        long l4 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se13.modify(lineitem_returnflag,lineitem_linestatus)) + (/*if */(c1 >= lineitem_shipdate) ? 1L : 0L));
        (/*if */(0L != l4) ? agg4 += Udiv(Ulistmax(1L, l4)) : 0.0);
        DOUBLE_TYPE agg5 = 0.0;
        long l5 = AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se14.modify(lineitem_returnflag,lineitem_linestatus));
        (/*if */(0L != l5) ? agg5 += Udiv(Ulistmax(1L, l5)) : 0.0);
        DOUBLE_TYPE agg6 = 0.0;
        long l6 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se15.modify(lineitem_returnflag,lineitem_linestatus)) + 1L);
        (/*if */(0L != l6) ? agg6 += Udiv(Ulistmax(1L, l6)) : 0.0);
        AVG_PRICE.addOrDelOnZero(se11.modify(lineitem_returnflag,lineitem_linestatus),((AVG_PRICELINEITEM2.getValueOrDefault(se12.modify(lineitem_returnflag,lineitem_linestatus)) * (agg4 + (agg5 * -1L))) + (/*if */(c1 >= lineitem_shipdate) ? (agg6 * lineitem_extendedprice) : 0.0)));
        (/*if */(c1 >= lineitem_shipdate) ? AVG_PRICELINEITEM2.addOrDelOnZero(se16.modify(lineitem_returnflag,lineitem_linestatus),lineitem_extendedprice) : (void)0);
        DOUBLE_TYPE agg7 = 0.0;
        long l7 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se19.modify(lineitem_returnflag,lineitem_linestatus)) + (/*if */(c1 >= lineitem_shipdate) ? 1L : 0L));
        (/*if */(0L != l7) ? agg7 += Udiv(Ulistmax(1L, l7)) : 0.0);
        DOUBLE_TYPE agg8 = 0.0;
        long l8 = AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se20.modify(lineitem_returnflag,lineitem_linestatus));
        (/*if */(0L != l8) ? agg8 += Udiv(Ulistmax(1L, l8)) : 0.0);
        DOUBLE_TYPE agg9 = 0.0;
        long l9 = (AVG_QTYLINEITEM1_L1_1.getValueOrDefault(se21.modify(lineitem_returnflag,lineitem_linestatus)) + 1L);
        (/*if */(0L != l9) ? agg9 += Udiv(Ulistmax(1L, l9)) : 0.0);
        AVG_DISC.addOrDelOnZero(se17.modify(lineitem_returnflag,lineitem_linestatus),((AVG_DISCLINEITEM2.getValueOrDefault(se18.modify(lineitem_returnflag,lineitem_linestatus)) * (agg7 + (agg8 * -1L))) + (/*if */(c1 >= lineitem_shipdate) ? (agg9 * lineitem_discount) : 0.0)));
        (/*if */(c1 >= lineitem_shipdate) ? AVG_QTYLINEITEM1_L1_1.addOrDelOnZero(se22.modify(lineitem_returnflag,lineitem_linestatus),1L) : (void)0);
        (/*if */(c1 >= lineitem_shipdate) ? AVG_DISCLINEITEM2.addOrDelOnZero(se23.modify(lineitem_returnflag,lineitem_linestatus),lineitem_discount) : (void)0);
        (/*if */(c1 >= lineitem_shipdate) ? COUNT_ORDER.addOrDelOnZero(se24.modify(lineitem_returnflag,lineitem_linestatus),1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    SUM_QTY_entry se1;
    SUM_BASE_PRICE_entry se2;
    SUM_DISC_PRICE_entry se3;
    SUM_CHARGE_entry se4;
    AVG_QTY_entry se5;
    AVG_QTYLINEITEM2_entry se6;
    AVG_QTYLINEITEM1_L1_1_entry se7;
    AVG_QTYLINEITEM1_L1_1_entry se8;
    AVG_QTYLINEITEM1_L1_1_entry se9;
    AVG_QTYLINEITEM2_entry se10;
    AVG_PRICE_entry se11;
    AVG_PRICELINEITEM2_entry se12;
    AVG_QTYLINEITEM1_L1_1_entry se13;
    AVG_QTYLINEITEM1_L1_1_entry se14;
    AVG_QTYLINEITEM1_L1_1_entry se15;
    AVG_PRICELINEITEM2_entry se16;
    AVG_DISC_entry se17;
    AVG_DISCLINEITEM2_entry se18;
    AVG_QTYLINEITEM1_L1_1_entry se19;
    AVG_QTYLINEITEM1_L1_1_entry se20;
    AVG_QTYLINEITEM1_L1_1_entry se21;
    AVG_QTYLINEITEM1_L1_1_entry se22;
    AVG_DISCLINEITEM2_entry se23;
    COUNT_ORDER_entry se24;
  
    /* Data structures used for storing materialized views */
    AVG_QTYLINEITEM1_L1_1_map AVG_QTYLINEITEM1_L1_1;
    AVG_QTYLINEITEM2_map AVG_QTYLINEITEM2;
    AVG_PRICELINEITEM2_map AVG_PRICELINEITEM2;
    AVG_DISCLINEITEM2_map AVG_DISCLINEITEM2;
    
    /*const static*/ long c1;
  
  };

}
