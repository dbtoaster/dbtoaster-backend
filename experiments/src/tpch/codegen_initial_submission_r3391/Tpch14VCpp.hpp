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
  struct PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry {
    long PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY; DOUBLE_TYPE __av; 
    explicit PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry() { /*PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY = 0L; __av = 0.0; */ }
    explicit PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry(const long c0, const DOUBLE_TYPE c1) { PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY = c0; __av = c1; }
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry(const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry& other) : PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY( other.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry& modify(const long c0) { PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry& x, const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry& y) {
      return x.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY == y.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry,DOUBLE_TYPE,
    HashIndex<PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry,DOUBLE_TYPE,PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_mapkey0_idxfn,true>
  > PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_map;
  typedef HashIndex<PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry,DOUBLE_TYPE,PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_mapkey0_idxfn,true> HashIndex_PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_map_0;
  
  struct PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry {
    long PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY; long __av; 
    explicit PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry() { /*PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry(const long c0, const long c1) { PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry(const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry& other) : PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY( other.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry& modify(const long c0) { PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry& x, const PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry& y) {
      return x.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY == y.PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry,long,
    HashIndex<PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry,long,PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_mapkey0_idxfn,true>
  > PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_map;
  typedef HashIndex<PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry,long,PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_mapkey0_idxfn,true> HashIndex_PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_map_0;
  
  struct PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry {
    long PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY; long __av; 
    explicit PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry() { /*PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry(const long c0, const long c1) { PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry(const PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry& other) : PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY( other.PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry& modify(const long c0) { PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMO_REVENUE_mLINEITEM2_mLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry& x, const PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry& y) {
      return x.PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY == y.PROMO_REVENUE_mLINEITEM2_mLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry,long,
    HashIndex<PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry,long,PROMO_REVENUE_mLINEITEM2_mLINEITEM3_mapkey0_idxfn,true>
  > PROMO_REVENUE_mLINEITEM2_mLINEITEM3_map;
  typedef HashIndex<PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry,long,PROMO_REVENUE_mLINEITEM2_mLINEITEM3_mapkey0_idxfn,true> HashIndex_PROMO_REVENUE_mLINEITEM2_mLINEITEM3_map_0;
  
  
  
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
    data_t(): tlq_t(), PROMO_REVENUE_mLINEITEM1_L1_1_L1_1(0.0), PROMO_REVENUE_mLINEITEM2(0.0) {
      c1 = Udate(STRING_TYPE("1995-9-1"));
      c2 = Udate(STRING_TYPE("1995-10-1"));
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
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? PROMO_REVENUE_mLINEITEM1_L1_1_L1_1 += (PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3.getValueOrDefault(se2.modify(lineitem_partkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : 0L);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1.addOrDelOnZero(se3.modify(lineitem_partkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? PROMO_REVENUE_mLINEITEM2 += (PROMO_REVENUE_mLINEITEM2_mLINEITEM3.getValueOrDefault(se5.modify(lineitem_partkey)) * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : 0L);
        DOUBLE_TYPE agg1 = 0.0;
        DOUBLE_TYPE agg2 = 0.0;
        DOUBLE_TYPE l2 = PROMO_REVENUE_mLINEITEM1_L1_1_L1_1;
        agg2 += Ulistmax(1L, l2);
        DOUBLE_TYPE l1 = agg2;
        agg1 += Udiv(l1);
        PROMO_REVENUE = (agg1 * (PROMO_REVENUE_mLINEITEM2 * 100.0));
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? PROMO_REVENUE_mLINEITEM1_L1_1_L1_1 += (PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3.getValueOrDefault(se8.modify(lineitem_partkey)) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : 0L);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1.addOrDelOnZero(se9.modify(lineitem_partkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? PROMO_REVENUE_mLINEITEM2 += (PROMO_REVENUE_mLINEITEM2_mLINEITEM3.getValueOrDefault(se11.modify(lineitem_partkey)) * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : 0L);
        DOUBLE_TYPE agg3 = 0.0;
        DOUBLE_TYPE agg4 = 0.0;
        DOUBLE_TYPE l4 = PROMO_REVENUE_mLINEITEM1_L1_1_L1_1;
        agg4 += Ulistmax(1L, l4);
        DOUBLE_TYPE l3 = agg4;
        agg3 += Udiv(l3);
        PROMO_REVENUE = (agg3 * (PROMO_REVENUE_mLINEITEM2 * 100.0));
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        PROMO_REVENUE_mLINEITEM1_L1_1_L1_1 += PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1.getValueOrDefault(se14.modify(part_partkey));
        PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3.addOrDelOnZero(se15.modify(part_partkey),1L);
        (/*if */(0L != Upreg_match(preg1,part_type)) ? PROMO_REVENUE_mLINEITEM2 += PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1.getValueOrDefault(se17.modify(part_partkey)) : 0L);
        (/*if */(0L != Upreg_match(preg1,part_type)) ? PROMO_REVENUE_mLINEITEM2_mLINEITEM3.addOrDelOnZero(se18.modify(part_partkey),1L) : (void)0);
        DOUBLE_TYPE agg5 = 0.0;
        DOUBLE_TYPE agg6 = 0.0;
        DOUBLE_TYPE l6 = PROMO_REVENUE_mLINEITEM1_L1_1_L1_1;
        agg6 += Ulistmax(1L, l6);
        DOUBLE_TYPE l5 = agg6;
        agg5 += Udiv(l5);
        PROMO_REVENUE = (agg5 * (PROMO_REVENUE_mLINEITEM2 * 100.0));
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        PROMO_REVENUE_mLINEITEM1_L1_1_L1_1 += (PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1.getValueOrDefault(se21.modify(part_partkey)) * -1L);
        PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3.addOrDelOnZero(se22.modify(part_partkey),-1L);
        (/*if */(0L != Upreg_match(preg1,part_type)) ? PROMO_REVENUE_mLINEITEM2 += (PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1.getValueOrDefault(se24.modify(part_partkey)) * -1L) : 0L);
        (/*if */(0L != Upreg_match(preg1,part_type)) ? PROMO_REVENUE_mLINEITEM2_mLINEITEM3.addOrDelOnZero(se25.modify(part_partkey),-1L) : (void)0);
        DOUBLE_TYPE agg7 = 0.0;
        DOUBLE_TYPE agg8 = 0.0;
        DOUBLE_TYPE l8 = PROMO_REVENUE_mLINEITEM1_L1_1_L1_1;
        agg8 += Ulistmax(1L, l8);
        DOUBLE_TYPE l7 = agg8;
        agg7 += Udiv(l7);
        PROMO_REVENUE = (agg7 * (PROMO_REVENUE_mLINEITEM2 * 100.0));
      }
    }
    void on_system_ready_event() {
      {  
        PROMO_REVENUE = 0.0;
        PROMO_REVENUE_mLINEITEM1_L1_1_L1_1 = 0.0;
        PROMO_REVENUE_mLINEITEM2 = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry se2;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry se3;
    PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry se5;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry se8;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry se9;
    PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry se11;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry se14;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry se15;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry se17;
    PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry se18;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry se21;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_entry se22;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_entry se24;
    PROMO_REVENUE_mLINEITEM2_mLINEITEM3_entry se25;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    DOUBLE_TYPE PROMO_REVENUE_mLINEITEM1_L1_1_L1_1;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1_map PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mPART1;
    PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3_map PROMO_REVENUE_mLINEITEM1_L1_1_L1_1_mLINEITEM3;
    DOUBLE_TYPE PROMO_REVENUE_mLINEITEM2;
    PROMO_REVENUE_mLINEITEM2_mLINEITEM3_map PROMO_REVENUE_mLINEITEM2_mLINEITEM3;
    
    /*const static*/ long c1;
    /*const static*/ long c2;
  
  };

}
