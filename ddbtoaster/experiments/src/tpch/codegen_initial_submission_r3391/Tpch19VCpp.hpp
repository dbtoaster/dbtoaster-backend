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
  struct REVENUE_mPART1_entry {
    long L_PARTKEY; DOUBLE_TYPE L_QUANTITY; STRING_TYPE L_SHIPINSTRUCT; STRING_TYPE L_SHIPMODE; DOUBLE_TYPE __av; 
    explicit REVENUE_mPART1_entry() { /*L_PARTKEY = 0L; L_QUANTITY = 0.0; L_SHIPINSTRUCT = ""; L_SHIPMODE = ""; __av = 0.0; */ }
    explicit REVENUE_mPART1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { L_PARTKEY = c0; L_QUANTITY = c1; L_SHIPINSTRUCT = c2; L_SHIPMODE = c3; __av = c4; }
    REVENUE_mPART1_entry(const REVENUE_mPART1_entry& other) : L_PARTKEY( other.L_PARTKEY ), L_QUANTITY( other.L_QUANTITY ), L_SHIPINSTRUCT( other.L_SHIPINSTRUCT ), L_SHIPMODE( other.L_SHIPMODE ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mPART1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { L_PARTKEY = c0; L_QUANTITY = c1; L_SHIPINSTRUCT = c2; L_SHIPMODE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_QUANTITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPINSTRUCT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_SHIPMODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mPART1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mPART1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.L_PARTKEY);
      hash_combine(h, e.L_QUANTITY);
      hash_combine(h, e.L_SHIPINSTRUCT);
      hash_combine(h, e.L_SHIPMODE);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mPART1_entry& x, const REVENUE_mPART1_entry& y) {
      return x.L_PARTKEY == y.L_PARTKEY && x.L_QUANTITY == y.L_QUANTITY && x.L_SHIPINSTRUCT == y.L_SHIPINSTRUCT && x.L_SHIPMODE == y.L_SHIPMODE;
    }
  };
  
  typedef MultiHashMap<REVENUE_mPART1_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mPART1_entry,DOUBLE_TYPE,REVENUE_mPART1_mapkey0123_idxfn,true>
  > REVENUE_mPART1_map;
  typedef HashIndex<REVENUE_mPART1_entry,DOUBLE_TYPE,REVENUE_mPART1_mapkey0123_idxfn,true> HashIndex_REVENUE_mPART1_map_0123;
  
  struct REVENUE_mLINEITEM1_entry {
    long P_PARTKEY; STRING_TYPE P_BRAND; long P_SIZE; STRING_TYPE P_CONTAINER; long __av; 
    explicit REVENUE_mLINEITEM1_entry() { /*P_PARTKEY = 0L; P_BRAND = ""; P_SIZE = 0L; P_CONTAINER = ""; __av = 0L; */ }
    explicit REVENUE_mLINEITEM1_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4) { P_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3; __av = c4; }
    REVENUE_mLINEITEM1_entry(const REVENUE_mLINEITEM1_entry& other) : P_PARTKEY( other.P_PARTKEY ), P_BRAND( other.P_BRAND ), P_SIZE( other.P_SIZE ), P_CONTAINER( other.P_CONTAINER ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { P_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, P_PARTKEY);
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
  struct REVENUE_mLINEITEM1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.P_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_SIZE);
      hash_combine(h, e.P_CONTAINER);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM1_entry& x, const REVENUE_mLINEITEM1_entry& y) {
      return x.P_PARTKEY == y.P_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_SIZE == y.P_SIZE && x.P_CONTAINER == y.P_CONTAINER;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM1_entry,long,
    HashIndex<REVENUE_mLINEITEM1_entry,long,REVENUE_mLINEITEM1_mapkey0123_idxfn,true>
  > REVENUE_mLINEITEM1_map;
  typedef HashIndex<REVENUE_mLINEITEM1_entry,long,REVENUE_mLINEITEM1_mapkey0123_idxfn,true> HashIndex_REVENUE_mLINEITEM1_map_0123;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0), REVENUE(0.0) { gettimeofday(&t0,NULL); }
  
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
      c17 = STRING_TYPE("LG PACK");
      c14 = STRING_TYPE("Brand#34");
      c2 = STRING_TYPE("AIR");
      c13 = STRING_TYPE("MED PACK");
      c18 = STRING_TYPE("LG PKG");
      c12 = STRING_TYPE("MED PKG");
      c5 = STRING_TYPE("SM CASE");
      c3 = STRING_TYPE("AIR REG");
      c7 = STRING_TYPE("SM PACK");
      c11 = STRING_TYPE("MED BOX");
      c15 = STRING_TYPE("LG CASE");
      c1 = STRING_TYPE("DELIVER IN PERSON");
      c6 = STRING_TYPE("SM BOX");
      c9 = STRING_TYPE("Brand#23");
      c4 = STRING_TYPE("Brand#12");
      c16 = STRING_TYPE("LG BOX");
      c8 = STRING_TYPE("SM PKG");
      c10 = STRING_TYPE("MED BAG");
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg1 = 0L;
        {  // foreach
          const HashIndex_REVENUE_mLINEITEM1_map_0123* i1 = static_cast<HashIndex_REVENUE_mLINEITEM1_map_0123*>(REVENUE_mLINEITEM1.index[0]);
          HashIndex_REVENUE_mLINEITEM1_map_0123::IdxNode* n1; 
          REVENUE_mLINEITEM1_entry* e1;
        
          for (size_t i = 0; i < i1->size_; i++)
          {
            n1 = i1->buckets_ + i;
            while (n1 && (e1 = n1->obj))
            {
                long p_partkey = e1->P_PARTKEY;
                STRING_TYPE p_brand = e1->P_BRAND;
                long p_size = e1->P_SIZE;
                STRING_TYPE p_container = e1->P_CONTAINER;
                long v1 = e1->__av;
                long l1 = (/*if */(p_partkey == lineitem_partkey && lineitem_shipinstruct == c1 && p_size >= 1L) ? (((/*if */(lineitem_shipmode == c2) ? 1L : 0L) + (/*if */(lineitem_shipmode == c3) ? 1L : 0L)) * ((/*if */(p_brand == c4 && lineitem_quantity >= 1L && 11L >= lineitem_quantity && 5L >= p_size) ? ((/*if */(p_container == c5) ? 1L : 0L) + ((/*if */(p_container == c6) ? 1L : 0L) + ((/*if */(p_container == c7) ? 1L : 0L) + (/*if */(p_container == c8) ? 1L : 0L)))) : 0L) + ((/*if */(p_brand == c9 && lineitem_quantity >= 10L && 20L >= lineitem_quantity && 10L >= p_size) ? ((/*if */(p_container == c10) ? 1L : 0L) + ((/*if */(p_container == c11) ? 1L : 0L) + ((/*if */(p_container == c12) ? 1L : 0L) + (/*if */(p_container == c13) ? 1L : 0L)))) : 0L) + (/*if */(p_brand == c14 && lineitem_quantity >= 20L && 30L >= lineitem_quantity && 15L >= p_size) ? ((/*if */(p_container == c15) ? 1L : 0L) + ((/*if */(p_container == c16) ? 1L : 0L) + ((/*if */(p_container == c17) ? 1L : 0L) + (/*if */(p_container == c18) ? 1L : 0L)))) : 0L)))) : 0L);
                (/*if */(l1 > 0L) ? agg1 += v1 : 0L);
              n1 = n1->nxt;
            }
          }
        }REVENUE += (agg1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))));
        REVENUE_mPART1.addOrDelOnZero(se2.modify(lineitem_partkey,lineitem_quantity,lineitem_shipinstruct,lineitem_shipmode),(lineitem_extendedprice * (1L + (-1L * lineitem_discount))));
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg2 = 0L;
        {  // foreach
          const HashIndex_REVENUE_mLINEITEM1_map_0123* i2 = static_cast<HashIndex_REVENUE_mLINEITEM1_map_0123*>(REVENUE_mLINEITEM1.index[0]);
          HashIndex_REVENUE_mLINEITEM1_map_0123::IdxNode* n2; 
          REVENUE_mLINEITEM1_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long p_partkey = e2->P_PARTKEY;
                STRING_TYPE p_brand = e2->P_BRAND;
                long p_size = e2->P_SIZE;
                STRING_TYPE p_container = e2->P_CONTAINER;
                long v2 = e2->__av;
                long l2 = (/*if */(p_partkey == lineitem_partkey && lineitem_shipinstruct == c1 && p_size >= 1L) ? (((/*if */(lineitem_shipmode == c2) ? 1L : 0L) + (/*if */(lineitem_shipmode == c3) ? 1L : 0L)) * ((/*if */(p_brand == c4 && lineitem_quantity >= 1L && 11L >= lineitem_quantity && 5L >= p_size) ? ((/*if */(p_container == c5) ? 1L : 0L) + ((/*if */(p_container == c6) ? 1L : 0L) + ((/*if */(p_container == c7) ? 1L : 0L) + (/*if */(p_container == c8) ? 1L : 0L)))) : 0L) + ((/*if */(p_brand == c9 && lineitem_quantity >= 10L && 20L >= lineitem_quantity && 10L >= p_size) ? ((/*if */(p_container == c10) ? 1L : 0L) + ((/*if */(p_container == c11) ? 1L : 0L) + ((/*if */(p_container == c12) ? 1L : 0L) + (/*if */(p_container == c13) ? 1L : 0L)))) : 0L) + (/*if */(p_brand == c14 && lineitem_quantity >= 20L && 30L >= lineitem_quantity && 15L >= p_size) ? ((/*if */(p_container == c15) ? 1L : 0L) + ((/*if */(p_container == c16) ? 1L : 0L) + ((/*if */(p_container == c17) ? 1L : 0L) + (/*if */(p_container == c18) ? 1L : 0L)))) : 0L)))) : 0L);
                (/*if */(l2 > 0L) ? agg2 += v2 : 0L);
              n2 = n2->nxt;
            }
          }
        }REVENUE += (agg2 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
        REVENUE_mPART1.addOrDelOnZero(se4.modify(lineitem_partkey,lineitem_quantity,lineitem_shipinstruct,lineitem_shipmode),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))));
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        DOUBLE_TYPE agg3 = 0.0;
        {  // foreach
          const HashIndex_REVENUE_mPART1_map_0123* i3 = static_cast<HashIndex_REVENUE_mPART1_map_0123*>(REVENUE_mPART1.index[0]);
          HashIndex_REVENUE_mPART1_map_0123::IdxNode* n3; 
          REVENUE_mPART1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long l_partkey = e3->L_PARTKEY;
                DOUBLE_TYPE l_quantity = e3->L_QUANTITY;
                STRING_TYPE l_shipinstruct = e3->L_SHIPINSTRUCT;
                STRING_TYPE l_shipmode = e3->L_SHIPMODE;
                DOUBLE_TYPE v3 = e3->__av;
                long l3 = (/*if */(part_partkey == l_partkey && l_shipinstruct == c1 && part_size >= 1L) ? (((/*if */(l_shipmode == c2) ? 1L : 0L) + (/*if */(l_shipmode == c3) ? 1L : 0L)) * ((/*if */(part_brand == c4 && l_quantity >= 1L && 11L >= l_quantity && 5L >= part_size) ? ((/*if */(part_container == c5) ? 1L : 0L) + ((/*if */(part_container == c6) ? 1L : 0L) + ((/*if */(part_container == c7) ? 1L : 0L) + (/*if */(part_container == c8) ? 1L : 0L)))) : 0L) + ((/*if */(part_brand == c9 && l_quantity >= 10L && 20L >= l_quantity && 10L >= part_size) ? ((/*if */(part_container == c10) ? 1L : 0L) + ((/*if */(part_container == c11) ? 1L : 0L) + ((/*if */(part_container == c12) ? 1L : 0L) + (/*if */(part_container == c13) ? 1L : 0L)))) : 0L) + (/*if */(part_brand == c14 && l_quantity >= 20L && 30L >= l_quantity && 15L >= part_size) ? ((/*if */(part_container == c15) ? 1L : 0L) + ((/*if */(part_container == c16) ? 1L : 0L) + ((/*if */(part_container == c17) ? 1L : 0L) + (/*if */(part_container == c18) ? 1L : 0L)))) : 0L)))) : 0L);
                (/*if */(l3 > 0L) ? agg3 += v3 : 0.0);
              n3 = n3->nxt;
            }
          }
        }REVENUE += agg3;
        REVENUE_mLINEITEM1.addOrDelOnZero(se6.modify(part_partkey,part_brand,part_size,part_container),1L);
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        DOUBLE_TYPE agg4 = 0.0;
        {  // foreach
          const HashIndex_REVENUE_mPART1_map_0123* i4 = static_cast<HashIndex_REVENUE_mPART1_map_0123*>(REVENUE_mPART1.index[0]);
          HashIndex_REVENUE_mPART1_map_0123::IdxNode* n4; 
          REVENUE_mPART1_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long l_partkey = e4->L_PARTKEY;
                DOUBLE_TYPE l_quantity = e4->L_QUANTITY;
                STRING_TYPE l_shipinstruct = e4->L_SHIPINSTRUCT;
                STRING_TYPE l_shipmode = e4->L_SHIPMODE;
                DOUBLE_TYPE v4 = e4->__av;
                long l4 = (/*if */(part_partkey == l_partkey && l_shipinstruct == c1 && part_size >= 1L) ? (((/*if */(l_shipmode == c2) ? 1L : 0L) + (/*if */(l_shipmode == c3) ? 1L : 0L)) * ((/*if */(part_brand == c4 && l_quantity >= 1L && 11L >= l_quantity && 5L >= part_size) ? ((/*if */(part_container == c5) ? 1L : 0L) + ((/*if */(part_container == c6) ? 1L : 0L) + ((/*if */(part_container == c7) ? 1L : 0L) + (/*if */(part_container == c8) ? 1L : 0L)))) : 0L) + ((/*if */(part_brand == c9 && l_quantity >= 10L && 20L >= l_quantity && 10L >= part_size) ? ((/*if */(part_container == c10) ? 1L : 0L) + ((/*if */(part_container == c11) ? 1L : 0L) + ((/*if */(part_container == c12) ? 1L : 0L) + (/*if */(part_container == c13) ? 1L : 0L)))) : 0L) + (/*if */(part_brand == c14 && l_quantity >= 20L && 30L >= l_quantity && 15L >= part_size) ? ((/*if */(part_container == c15) ? 1L : 0L) + ((/*if */(part_container == c16) ? 1L : 0L) + ((/*if */(part_container == c17) ? 1L : 0L) + (/*if */(part_container == c18) ? 1L : 0L)))) : 0L)))) : 0L);
                (/*if */(l4 > 0L) ? agg4 += v4 : 0.0);
              n4 = n4->nxt;
            }
          }
        }REVENUE += (agg4 * -1L);
        REVENUE_mLINEITEM1.addOrDelOnZero(se8.modify(part_partkey,part_brand,part_size,part_container),-1L);
      }
    }
    void on_system_ready_event() {
      {  
        REVENUE = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUE_mPART1_entry se2;
    REVENUE_mPART1_entry se4;
    REVENUE_mLINEITEM1_entry se6;
    REVENUE_mLINEITEM1_entry se8;
  
    /* Data structures used for storing materialized views */
    REVENUE_mPART1_map REVENUE_mPART1;
    REVENUE_mLINEITEM1_map REVENUE_mLINEITEM1;
    
    /*const static*/ STRING_TYPE c17;
    /*const static*/ STRING_TYPE c14;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c13;
    /*const static*/ STRING_TYPE c18;
    /*const static*/ STRING_TYPE c12;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c11;
    /*const static*/ STRING_TYPE c15;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c9;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c16;
    /*const static*/ STRING_TYPE c8;
    /*const static*/ STRING_TYPE c10;
  
  };

}
