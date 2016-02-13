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
  
  struct HIGH_LINE_COUNT_mLINEITEM1_entry {
    long HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit HIGH_LINE_COUNT_mLINEITEM1_entry() { /*HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit HIGH_LINE_COUNT_mLINEITEM1_entry(const long c0, const long c1) { HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0; __av = c1; }
    HIGH_LINE_COUNT_mLINEITEM1_entry(const HIGH_LINE_COUNT_mLINEITEM1_entry& other) : HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY( other.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNT_mLINEITEM1_entry& modify(const long c0) { HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNT_mLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_mLINEITEM1_entry& x, const HIGH_LINE_COUNT_mLINEITEM1_entry& y) {
      return x.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY == y.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNT_mLINEITEM1_entry,long,
    HashIndex<HIGH_LINE_COUNT_mLINEITEM1_entry,long,HIGH_LINE_COUNT_mLINEITEM1_mapkey0_idxfn,true>
  > HIGH_LINE_COUNT_mLINEITEM1_map;
  typedef HashIndex<HIGH_LINE_COUNT_mLINEITEM1_entry,long,HIGH_LINE_COUNT_mLINEITEM1_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNT_mLINEITEM1_map_0;
  
  struct HIGH_LINE_COUNT_mLINEITEM8_entry {
    long HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit HIGH_LINE_COUNT_mLINEITEM8_entry() { /*HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit HIGH_LINE_COUNT_mLINEITEM8_entry(const long c0, const long c1) { HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0; __av = c1; }
    HIGH_LINE_COUNT_mLINEITEM8_entry(const HIGH_LINE_COUNT_mLINEITEM8_entry& other) : HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY( other.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNT_mLINEITEM8_entry& modify(const long c0) { HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNT_mLINEITEM8_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_mLINEITEM8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_mLINEITEM8_entry& x, const HIGH_LINE_COUNT_mLINEITEM8_entry& y) {
      return x.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY == y.HIGH_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNT_mLINEITEM8_entry,long,
    HashIndex<HIGH_LINE_COUNT_mLINEITEM8_entry,long,HIGH_LINE_COUNT_mLINEITEM8_mapkey0_idxfn,true>
  > HIGH_LINE_COUNT_mLINEITEM8_map;
  typedef HashIndex<HIGH_LINE_COUNT_mLINEITEM8_entry,long,HIGH_LINE_COUNT_mLINEITEM8_mapkey0_idxfn,true> HashIndex_HIGH_LINE_COUNT_mLINEITEM8_map_0;
  
  struct HIGH_LINE_COUNT_mORDERS1_entry {
    long HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY; STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNT_mORDERS1_entry() { /*HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = 0L; L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNT_mORDERS1_entry(const long c0, const STRING_TYPE& c1, const long c2) { HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = c0; L_SHIPMODE = c1; __av = c2; }
    HIGH_LINE_COUNT_mORDERS1_entry(const HIGH_LINE_COUNT_mORDERS1_entry& other) : HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY( other.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNT_mORDERS1_entry& modify(const long c0, const STRING_TYPE& c1) { HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = c0; L_SHIPMODE = c1;  return *this; }
    FORCE_INLINE HIGH_LINE_COUNT_mORDERS1_entry& modify0(const long c0) { HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNT_mORDERS1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_mORDERS1_entry& x, const HIGH_LINE_COUNT_mORDERS1_entry& y) {
      return x.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY == y.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  struct HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_mORDERS1_entry& x, const HIGH_LINE_COUNT_mORDERS1_entry& y) {
      return x.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY == y.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNT_mORDERS1_entry,long,
    HashIndex<HIGH_LINE_COUNT_mORDERS1_entry,long,HIGH_LINE_COUNT_mORDERS1_mapkey01_idxfn,true>,
    HashIndex<HIGH_LINE_COUNT_mORDERS1_entry,long,HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn,false>
  > HIGH_LINE_COUNT_mORDERS1_map;
  typedef HashIndex<HIGH_LINE_COUNT_mORDERS1_entry,long,HIGH_LINE_COUNT_mORDERS1_mapkey01_idxfn,true> HashIndex_HIGH_LINE_COUNT_mORDERS1_map_01;
  typedef HashIndex<HIGH_LINE_COUNT_mORDERS1_entry,long,HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn,false> HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0;
  
  struct HIGH_LINE_COUNT_mORDERS4_entry {
    long HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY; STRING_TYPE L_SHIPMODE; long __av; 
    explicit HIGH_LINE_COUNT_mORDERS4_entry() { /*HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = 0L; L_SHIPMODE = ""; __av = 0L; */ }
    explicit HIGH_LINE_COUNT_mORDERS4_entry(const long c0, const STRING_TYPE& c1, const long c2) { HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = c0; L_SHIPMODE = c1; __av = c2; }
    HIGH_LINE_COUNT_mORDERS4_entry(const HIGH_LINE_COUNT_mORDERS4_entry& other) : HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY( other.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE HIGH_LINE_COUNT_mORDERS4_entry& modify(const long c0, const STRING_TYPE& c1) { HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = c0; L_SHIPMODE = c1;  return *this; }
    FORCE_INLINE HIGH_LINE_COUNT_mORDERS4_entry& modify0(const long c0) { HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HIGH_LINE_COUNT_mORDERS4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_mORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_mORDERS4_entry& x, const HIGH_LINE_COUNT_mORDERS4_entry& y) {
      return x.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY == y.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  struct HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const HIGH_LINE_COUNT_mORDERS4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const HIGH_LINE_COUNT_mORDERS4_entry& x, const HIGH_LINE_COUNT_mORDERS4_entry& y) {
      return x.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY == y.HIGH_LINE_COUNT_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<HIGH_LINE_COUNT_mORDERS4_entry,long,
    HashIndex<HIGH_LINE_COUNT_mORDERS4_entry,long,HIGH_LINE_COUNT_mORDERS4_mapkey01_idxfn,true>,
    HashIndex<HIGH_LINE_COUNT_mORDERS4_entry,long,HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn,false>
  > HIGH_LINE_COUNT_mORDERS4_map;
  typedef HashIndex<HIGH_LINE_COUNT_mORDERS4_entry,long,HIGH_LINE_COUNT_mORDERS4_mapkey01_idxfn,true> HashIndex_HIGH_LINE_COUNT_mORDERS4_map_01;
  typedef HashIndex<HIGH_LINE_COUNT_mORDERS4_entry,long,HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn,false> HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0;
  
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
  
  struct LOW_LINE_COUNT_mLINEITEM6_entry {
    long LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit LOW_LINE_COUNT_mLINEITEM6_entry() { /*LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit LOW_LINE_COUNT_mLINEITEM6_entry(const long c0, const long c1) { LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0; __av = c1; }
    LOW_LINE_COUNT_mLINEITEM6_entry(const LOW_LINE_COUNT_mLINEITEM6_entry& other) : LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY( other.LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE LOW_LINE_COUNT_mLINEITEM6_entry& modify(const long c0) { LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct LOW_LINE_COUNT_mLINEITEM6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const LOW_LINE_COUNT_mLINEITEM6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const LOW_LINE_COUNT_mLINEITEM6_entry& x, const LOW_LINE_COUNT_mLINEITEM6_entry& y) {
      return x.LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY == y.LOW_LINE_COUNT_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<LOW_LINE_COUNT_mLINEITEM6_entry,long,
    HashIndex<LOW_LINE_COUNT_mLINEITEM6_entry,long,LOW_LINE_COUNT_mLINEITEM6_mapkey0_idxfn,true>
  > LOW_LINE_COUNT_mLINEITEM6_map;
  typedef HashIndex<LOW_LINE_COUNT_mLINEITEM6_entry,long,LOW_LINE_COUNT_mLINEITEM6_mapkey0_idxfn,true> HashIndex_LOW_LINE_COUNT_mLINEITEM6_map_0;
  
  
  
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
      c2 = Udate(STRING_TYPE("1995-1-1"));
      c1 = Udate(STRING_TYPE("1994-1-1"));
      c3 = STRING_TYPE("MAIL");
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? HIGH_LINE_COUNT.addOrDelOnZero(se1.modify(lineitem_shipmode),(((/*if */(lineitem_shipmode == c3) ? 1L : 0L) + (/*if */(lineitem_shipmode == c4) ? 1L : 0L)) * (HIGH_LINE_COUNT_mLINEITEM1.getValueOrDefault(se2.modify(lineitem_orderkey)) + HIGH_LINE_COUNT_mLINEITEM8.getValueOrDefault(se3.modify(lineitem_orderkey))))) : (void)0);
        (/*if */(lineitem_shipmode == c3 && lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? HIGH_LINE_COUNT_mORDERS1.addOrDelOnZero(se4.modify(lineitem_orderkey,lineitem_shipmode),1L) : (void)0);
        (/*if */(lineitem_shipmode == c4 && lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? HIGH_LINE_COUNT_mORDERS4.addOrDelOnZero(se5.modify(lineitem_orderkey,lineitem_shipmode),1L) : (void)0);
        (/*if */(lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? LOW_LINE_COUNT.addOrDelOnZero(se6.modify(lineitem_shipmode),(LOW_LINE_COUNT_mLINEITEM6.getValueOrDefault(se7.modify(lineitem_orderkey)) * ((/*if */(lineitem_shipmode == c3) ? 1L : 0L) + (/*if */(lineitem_shipmode == c4) ? 1L : 0L)))) : (void)0);
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? HIGH_LINE_COUNT.addOrDelOnZero(se8.modify(lineitem_shipmode),(((/*if */(lineitem_shipmode == c3) ? -1L : 0L) + (/*if */(lineitem_shipmode == c4) ? -1L : 0L)) * (HIGH_LINE_COUNT_mLINEITEM1.getValueOrDefault(se9.modify(lineitem_orderkey)) + HIGH_LINE_COUNT_mLINEITEM8.getValueOrDefault(se10.modify(lineitem_orderkey))))) : (void)0);
        (/*if */(lineitem_shipmode == c3 && lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? HIGH_LINE_COUNT_mORDERS1.addOrDelOnZero(se11.modify(lineitem_orderkey,lineitem_shipmode),-1L) : (void)0);
        (/*if */(lineitem_shipmode == c4 && lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? HIGH_LINE_COUNT_mORDERS4.addOrDelOnZero(se12.modify(lineitem_orderkey,lineitem_shipmode),-1L) : (void)0);
        (/*if */(lineitem_receiptdate > lineitem_commitdate && lineitem_commitdate > lineitem_shipdate && lineitem_receiptdate >= c1 && c2 > lineitem_receiptdate) ? LOW_LINE_COUNT.addOrDelOnZero(se13.modify(lineitem_shipmode),(LOW_LINE_COUNT_mLINEITEM6.getValueOrDefault(se14.modify(lineitem_orderkey)) * ((/*if */(lineitem_shipmode == c3) ? -1L : 0L) + (/*if */(lineitem_shipmode == c4) ? -1L : 0L)))) : (void)0);
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0* i1 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0*>(HIGH_LINE_COUNT_mORDERS1.index[1]);
          const HASH_RES_t h1 = HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::hash(se16.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode* n1 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode*>(i1->slice(se16, h1));
          HIGH_LINE_COUNT_mORDERS1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE l_shipmode = e1->L_SHIPMODE;
              long v1 = e1->__av;
              HIGH_LINE_COUNT.addOrDelOnZero(se15.modify(l_shipmode),(((/*if */(orders_orderpriority == c5) ? 1L : 0L) + (/*if */(orders_orderpriority == c6) ? 1L : 0L)) * v1));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::equals(se16, *e1)); 
          }
        }{ //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0* i2 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0*>(HIGH_LINE_COUNT_mORDERS4.index[1]);
          const HASH_RES_t h2 = HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::hash(se17.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode* n2 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode*>(i2->slice(se17, h2));
          HIGH_LINE_COUNT_mORDERS4_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE l_shipmode = e2->L_SHIPMODE;
              long v2 = e2->__av;
              HIGH_LINE_COUNT.addOrDelOnZero(se15.modify(l_shipmode),(((/*if */(orders_orderpriority == c5) ? 1L : 0L) + (/*if */(orders_orderpriority == c6) ? 1L : 0L)) * v2));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::equals(se17, *e2)); 
          }
        }(/*if */(orders_orderpriority == c5) ? HIGH_LINE_COUNT_mLINEITEM1.addOrDelOnZero(se18.modify(orders_orderkey),1L) : (void)0);
        (/*if */(orders_orderpriority == c6) ? HIGH_LINE_COUNT_mLINEITEM8.addOrDelOnZero(se19.modify(orders_orderkey),1L) : (void)0);
        { //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0* i3 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0*>(HIGH_LINE_COUNT_mORDERS1.index[1]);
          const HASH_RES_t h3 = HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::hash(se21.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode* n3 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode*>(i3->slice(se21, h3));
          HIGH_LINE_COUNT_mORDERS1_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              STRING_TYPE l_shipmode = e3->L_SHIPMODE;
              long v3 = e3->__av;
              (/*if */(c5 != orders_orderpriority && c6 != orders_orderpriority) ? LOW_LINE_COUNT.addOrDelOnZero(se20.modify(l_shipmode),v3) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::equals(se21, *e3)); 
          }
        }{ //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0* i4 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0*>(HIGH_LINE_COUNT_mORDERS4.index[1]);
          const HASH_RES_t h4 = HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::hash(se22.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode* n4 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode*>(i4->slice(se22, h4));
          HIGH_LINE_COUNT_mORDERS4_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              STRING_TYPE l_shipmode = e4->L_SHIPMODE;
              long v4 = e4->__av;
              (/*if */(c5 != orders_orderpriority && c6 != orders_orderpriority) ? LOW_LINE_COUNT.addOrDelOnZero(se20.modify(l_shipmode),v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::equals(se22, *e4)); 
          }
        }(/*if */(c5 != orders_orderpriority && c6 != orders_orderpriority) ? LOW_LINE_COUNT_mLINEITEM6.addOrDelOnZero(se23.modify(orders_orderkey),1L) : (void)0);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0* i5 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0*>(HIGH_LINE_COUNT_mORDERS1.index[1]);
          const HASH_RES_t h5 = HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::hash(se25.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode* n5 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode*>(i5->slice(se25, h5));
          HIGH_LINE_COUNT_mORDERS1_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE l_shipmode = e5->L_SHIPMODE;
              long v5 = e5->__av;
              HIGH_LINE_COUNT.addOrDelOnZero(se24.modify(l_shipmode),(((/*if */(orders_orderpriority == c5) ? -1L : 0L) + (/*if */(orders_orderpriority == c6) ? -1L : 0L)) * v5));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::equals(se25, *e5)); 
          }
        }{ //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0* i6 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0*>(HIGH_LINE_COUNT_mORDERS4.index[1]);
          const HASH_RES_t h6 = HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::hash(se26.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode* n6 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode*>(i6->slice(se26, h6));
          HIGH_LINE_COUNT_mORDERS4_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE l_shipmode = e6->L_SHIPMODE;
              long v6 = e6->__av;
              HIGH_LINE_COUNT.addOrDelOnZero(se24.modify(l_shipmode),(((/*if */(orders_orderpriority == c5) ? -1L : 0L) + (/*if */(orders_orderpriority == c6) ? -1L : 0L)) * v6));
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::equals(se26, *e6)); 
          }
        }(/*if */(orders_orderpriority == c5) ? HIGH_LINE_COUNT_mLINEITEM1.addOrDelOnZero(se27.modify(orders_orderkey),-1L) : (void)0);
        (/*if */(orders_orderpriority == c6) ? HIGH_LINE_COUNT_mLINEITEM8.addOrDelOnZero(se28.modify(orders_orderkey),-1L) : (void)0);
        { //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0* i7 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0*>(HIGH_LINE_COUNT_mORDERS1.index[1]);
          const HASH_RES_t h7 = HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::hash(se30.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode* n7 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS1_map_0::IdxNode*>(i7->slice(se30, h7));
          HIGH_LINE_COUNT_mORDERS1_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              STRING_TYPE l_shipmode = e7->L_SHIPMODE;
              long v7 = e7->__av;
              (/*if */(c5 != orders_orderpriority && c6 != orders_orderpriority) ? LOW_LINE_COUNT.addOrDelOnZero(se29.modify(l_shipmode),(v7 * -1L)) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  HIGH_LINE_COUNT_mORDERS1_mapkey0_idxfn::equals(se30, *e7)); 
          }
        }{ //slice 
          const HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0* i8 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0*>(HIGH_LINE_COUNT_mORDERS4.index[1]);
          const HASH_RES_t h8 = HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::hash(se31.modify0(orders_orderkey));
          HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode* n8 = static_cast<HashIndex_HIGH_LINE_COUNT_mORDERS4_map_0::IdxNode*>(i8->slice(se31, h8));
          HIGH_LINE_COUNT_mORDERS4_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              STRING_TYPE l_shipmode = e8->L_SHIPMODE;
              long v8 = e8->__av;
              (/*if */(c5 != orders_orderpriority && c6 != orders_orderpriority) ? LOW_LINE_COUNT.addOrDelOnZero(se29.modify(l_shipmode),(v8 * -1L)) : (void)0);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  HIGH_LINE_COUNT_mORDERS4_mapkey0_idxfn::equals(se31, *e8)); 
          }
        }(/*if */(c5 != orders_orderpriority && c6 != orders_orderpriority) ? LOW_LINE_COUNT_mLINEITEM6.addOrDelOnZero(se32.modify(orders_orderkey),-1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    HIGH_LINE_COUNT_entry se1;
    HIGH_LINE_COUNT_mLINEITEM1_entry se2;
    HIGH_LINE_COUNT_mLINEITEM8_entry se3;
    HIGH_LINE_COUNT_mORDERS1_entry se4;
    HIGH_LINE_COUNT_mORDERS4_entry se5;
    LOW_LINE_COUNT_entry se6;
    LOW_LINE_COUNT_mLINEITEM6_entry se7;
    HIGH_LINE_COUNT_entry se8;
    HIGH_LINE_COUNT_mLINEITEM1_entry se9;
    HIGH_LINE_COUNT_mLINEITEM8_entry se10;
    HIGH_LINE_COUNT_mORDERS1_entry se11;
    HIGH_LINE_COUNT_mORDERS4_entry se12;
    LOW_LINE_COUNT_entry se13;
    LOW_LINE_COUNT_mLINEITEM6_entry se14;
    HIGH_LINE_COUNT_entry se15;
    HIGH_LINE_COUNT_mORDERS1_entry se16;
    HIGH_LINE_COUNT_mORDERS4_entry se17;
    HIGH_LINE_COUNT_mLINEITEM1_entry se18;
    HIGH_LINE_COUNT_mLINEITEM8_entry se19;
    LOW_LINE_COUNT_entry se20;
    HIGH_LINE_COUNT_mORDERS1_entry se21;
    HIGH_LINE_COUNT_mORDERS4_entry se22;
    LOW_LINE_COUNT_mLINEITEM6_entry se23;
    HIGH_LINE_COUNT_entry se24;
    HIGH_LINE_COUNT_mORDERS1_entry se25;
    HIGH_LINE_COUNT_mORDERS4_entry se26;
    HIGH_LINE_COUNT_mLINEITEM1_entry se27;
    HIGH_LINE_COUNT_mLINEITEM8_entry se28;
    LOW_LINE_COUNT_entry se29;
    HIGH_LINE_COUNT_mORDERS1_entry se30;
    HIGH_LINE_COUNT_mORDERS4_entry se31;
    LOW_LINE_COUNT_mLINEITEM6_entry se32;
  
    /* Data structures used for storing materialized views */
    HIGH_LINE_COUNT_mLINEITEM1_map HIGH_LINE_COUNT_mLINEITEM1;
    HIGH_LINE_COUNT_mLINEITEM8_map HIGH_LINE_COUNT_mLINEITEM8;
    HIGH_LINE_COUNT_mORDERS1_map HIGH_LINE_COUNT_mORDERS1;
    HIGH_LINE_COUNT_mORDERS4_map HIGH_LINE_COUNT_mORDERS4;
    LOW_LINE_COUNT_mLINEITEM6_map LOW_LINE_COUNT_mLINEITEM6;
    
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
