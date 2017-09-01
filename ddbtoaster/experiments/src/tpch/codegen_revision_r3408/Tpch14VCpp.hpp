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
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry {
    long PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY; DOUBLE_TYPE __av; 
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry() { /*PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY = 0L; __av = 0.0; */ }
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry(const long c0, const DOUBLE_TYPE c1) { PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& other) : PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY( other.PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& modify(const long c0) { PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& x, const PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry& y) {
      return x.PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY == y.PROMO_REVENUELINEITEM1_L1_1_L1_1PARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry,DOUBLE_TYPE,
    HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry,DOUBLE_TYPE,PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_map;
  typedef HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry,DOUBLE_TYPE,PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_map_0;
  
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry {
    long PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY; long __av; 
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry() { /*PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry(const long c0, const long c1) { PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry& other) : PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY( other.PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry& modify(const long c0) { PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry& x, const PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry& y) {
      return x.PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY == y.PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry,long,
    HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry,long,PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_map;
  typedef HashIndex<PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry,long,PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_map_0;
  
  struct PROMO_REVENUELINEITEM2LINEITEM3_entry {
    long PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY; long __av; 
    explicit PROMO_REVENUELINEITEM2LINEITEM3_entry() { /*PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUELINEITEM2LINEITEM3_entry(const long c0, const long c1) { PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    PROMO_REVENUELINEITEM2LINEITEM3_entry(const PROMO_REVENUELINEITEM2LINEITEM3_entry& other) : PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY( other.PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUELINEITEM2LINEITEM3_entry& modify(const long c0) { PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUELINEITEM2LINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUELINEITEM2LINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUELINEITEM2LINEITEM3_entry& x, const PROMO_REVENUELINEITEM2LINEITEM3_entry& y) {
      return x.PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY == y.PROMO_REVENUELINEITEM2LINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUELINEITEM2LINEITEM3_entry,long,
    HashIndex<PROMO_REVENUELINEITEM2LINEITEM3_entry,long,PROMO_REVENUELINEITEM2LINEITEM3_mapkey0_idxfn,true>
  > PROMO_REVENUELINEITEM2LINEITEM3_map;
  typedef HashIndex<PROMO_REVENUELINEITEM2LINEITEM3_entry,long,PROMO_REVENUELINEITEM2LINEITEM3_mapkey0_idxfn,true> HashIndex_PROMO_REVENUELINEITEM2LINEITEM3_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0), PROMO_REVENUE(0.0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const DOUBLE_TYPE _PROMO_REVENUE = get_PROMO_REVENUE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(PROMO_REVENUE), _PROMO_REVENUE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const DOUBLE_TYPE get_PROMO_REVENUE() const {
      return PROMO_REVENUE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    DOUBLE_TYPE PROMO_REVENUE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), PROMO_REVENUELINEITEM1_L1_1_L1_1(0.0), PROMO_REVENUELINEITEM2(0.0) {
      c2 = Udate(STRING_TYPE("1995-9-1"));
      c1 = Udate(STRING_TYPE("1995-10-1"));
      /* regex_t init */
      if(regcomp(&preg1, "^PROMO.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^PROMO.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg1);
    }
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(c1 > lineitem_shipdate && lineitem_shipdate >= c2) ? PROMO_REVENUELINEITEM1_L1_1_L1_1 += (PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3.getValueOrDefault(se2.modify(lineitem_partkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : 0L);
        (/*if */(c1 > lineitem_shipdate && lineitem_shipdate >= c2) ? PROMO_REVENUELINEITEM1_L1_1_L1_1PART1.addOrDelOnZero(se3.modify(lineitem_partkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        (/*if */(c1 > lineitem_shipdate && lineitem_shipdate >= c2) ? PROMO_REVENUELINEITEM2 += (PROMO_REVENUELINEITEM2LINEITEM3.getValueOrDefault(se5.modify(lineitem_partkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : 0L);
        DOUBLE_TYPE agg1 = 0.0;
        DOUBLE_TYPE agg2 = 0.0;
        DOUBLE_TYPE l2 = PROMO_REVENUELINEITEM1_L1_1_L1_1;
        agg2 += Ulistmax(1L, l2);
        DOUBLE_TYPE l1 = agg2;
        agg1 += Udiv(l1);
        PROMO_REVENUE = (PROMO_REVENUELINEITEM2 * (agg1 * 100.0));
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        PROMO_REVENUELINEITEM1_L1_1_L1_1 += PROMO_REVENUELINEITEM1_L1_1_L1_1PART1.getValueOrDefault(se8.modify(part_partkey));
        PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3.addOrDelOnZero(se9.modify(part_partkey),1L);
        (/*if */(0L != Upreg_match(preg1,part_type)) ? PROMO_REVENUELINEITEM2 += PROMO_REVENUELINEITEM1_L1_1_L1_1PART1.getValueOrDefault(se11.modify(part_partkey)) : 0L);
        (/*if */(0L != Upreg_match(preg1,part_type)) ? PROMO_REVENUELINEITEM2LINEITEM3.addOrDelOnZero(se12.modify(part_partkey),1L) : (void)0);
        DOUBLE_TYPE agg3 = 0.0;
        DOUBLE_TYPE agg4 = 0.0;
        DOUBLE_TYPE l4 = PROMO_REVENUELINEITEM1_L1_1_L1_1;
        agg4 += Ulistmax(1L, l4);
        DOUBLE_TYPE l3 = agg4;
        agg3 += Udiv(l3);
        PROMO_REVENUE = (PROMO_REVENUELINEITEM2 * (agg3 * 100.0));
      }
    }
    void on_system_ready_event() {
      {  
        PROMO_REVENUE = 0.0;
        PROMO_REVENUELINEITEM1_L1_1_L1_1 = 0.0;
        PROMO_REVENUELINEITEM2 = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry se2;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry se3;
    PROMO_REVENUELINEITEM2LINEITEM3_entry se5;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry se8;
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_entry se9;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_entry se11;
    PROMO_REVENUELINEITEM2LINEITEM3_entry se12;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    DOUBLE_TYPE PROMO_REVENUELINEITEM1_L1_1_L1_1;
    PROMO_REVENUELINEITEM1_L1_1_L1_1PART1_map PROMO_REVENUELINEITEM1_L1_1_L1_1PART1;
    PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3_map PROMO_REVENUELINEITEM1_L1_1_L1_1LINEITEM3;
    DOUBLE_TYPE PROMO_REVENUELINEITEM2;
    PROMO_REVENUELINEITEM2LINEITEM3_map PROMO_REVENUELINEITEM2LINEITEM3;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
  
  };

}
