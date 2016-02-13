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
  struct REVENUE_mPART2_entry {
    long REVENUE_mPARTPART_PARTKEY; DOUBLE_TYPE L_QUANTITY; DOUBLE_TYPE __av; 
    explicit REVENUE_mPART2_entry() { /*REVENUE_mPARTPART_PARTKEY = 0L; L_QUANTITY = 0.0; __av = 0.0; */ }
    explicit REVENUE_mPART2_entry(const long c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { REVENUE_mPARTPART_PARTKEY = c0; L_QUANTITY = c1; __av = c2; }
    REVENUE_mPART2_entry(const REVENUE_mPART2_entry& other) : REVENUE_mPARTPART_PARTKEY( other.REVENUE_mPARTPART_PARTKEY ), L_QUANTITY( other.L_QUANTITY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mPART2_entry& modify(const long c0, const DOUBLE_TYPE c1) { REVENUE_mPARTPART_PARTKEY = c0; L_QUANTITY = c1;  return *this; }
    FORCE_INLINE REVENUE_mPART2_entry& modify0(const long c0) { REVENUE_mPARTPART_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mPARTPART_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_QUANTITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mPART2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mPARTPART_PARTKEY);
      hash_combine(h, e.L_QUANTITY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mPART2_entry& x, const REVENUE_mPART2_entry& y) {
      return x.REVENUE_mPARTPART_PARTKEY == y.REVENUE_mPARTPART_PARTKEY && x.L_QUANTITY == y.L_QUANTITY;
    }
  };
  
  struct REVENUE_mPART2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mPART2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mPARTPART_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mPART2_entry& x, const REVENUE_mPART2_entry& y) {
      return x.REVENUE_mPARTPART_PARTKEY == y.REVENUE_mPARTPART_PARTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mPART2_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mPART2_entry,DOUBLE_TYPE,REVENUE_mPART2_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mPART2_entry,DOUBLE_TYPE,REVENUE_mPART2_mapkey0_idxfn,false>
  > REVENUE_mPART2_map;
  typedef HashIndex<REVENUE_mPART2_entry,DOUBLE_TYPE,REVENUE_mPART2_mapkey01_idxfn,true> HashIndex_REVENUE_mPART2_map_01;
  typedef HashIndex<REVENUE_mPART2_entry,DOUBLE_TYPE,REVENUE_mPART2_mapkey0_idxfn,false> HashIndex_REVENUE_mPART2_map_0;
  
  struct REVENUE_mLINEITEM3_entry {
    long REVENUE_mLINEITEMLINEITEM_PARTKEY; STRING_TYPE P_BRAND; long P_SIZE; STRING_TYPE P_CONTAINER; long __av; 
    explicit REVENUE_mLINEITEM3_entry() { /*REVENUE_mLINEITEMLINEITEM_PARTKEY = 0L; P_BRAND = ""; P_SIZE = 0L; P_CONTAINER = ""; __av = 0L; */ }
    explicit REVENUE_mLINEITEM3_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4) { REVENUE_mLINEITEMLINEITEM_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3; __av = c4; }
    REVENUE_mLINEITEM3_entry(const REVENUE_mLINEITEM3_entry& other) : REVENUE_mLINEITEMLINEITEM_PARTKEY( other.REVENUE_mLINEITEMLINEITEM_PARTKEY ), P_BRAND( other.P_BRAND ), P_SIZE( other.P_SIZE ), P_CONTAINER( other.P_CONTAINER ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM3_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { REVENUE_mLINEITEMLINEITEM_PARTKEY = c0; P_BRAND = c1; P_SIZE = c2; P_CONTAINER = c3;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM3_entry& modify0(const long c0) { REVENUE_mLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mLINEITEMLINEITEM_PARTKEY);
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
  struct REVENUE_mLINEITEM3_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_PARTKEY);
      hash_combine(h, e.P_BRAND);
      hash_combine(h, e.P_SIZE);
      hash_combine(h, e.P_CONTAINER);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM3_entry& x, const REVENUE_mLINEITEM3_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_PARTKEY == y.REVENUE_mLINEITEMLINEITEM_PARTKEY && x.P_BRAND == y.P_BRAND && x.P_SIZE == y.P_SIZE && x.P_CONTAINER == y.P_CONTAINER;
    }
  };
  
  struct REVENUE_mLINEITEM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM3_entry& x, const REVENUE_mLINEITEM3_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_PARTKEY == y.REVENUE_mLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM3_entry,long,
    HashIndex<REVENUE_mLINEITEM3_entry,long,REVENUE_mLINEITEM3_mapkey0123_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM3_entry,long,REVENUE_mLINEITEM3_mapkey0_idxfn,false>
  > REVENUE_mLINEITEM3_map;
  typedef HashIndex<REVENUE_mLINEITEM3_entry,long,REVENUE_mLINEITEM3_mapkey0123_idxfn,true> HashIndex_REVENUE_mLINEITEM3_map_0123;
  typedef HashIndex<REVENUE_mLINEITEM3_entry,long,REVENUE_mLINEITEM3_mapkey0_idxfn,false> HashIndex_REVENUE_mLINEITEM3_map_0;
  
  
  
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
      c16 = STRING_TYPE("LG PACK");
      c18 = STRING_TYPE("Brand#34");
      c1 = STRING_TYPE("AIR");
      c12 = STRING_TYPE("MED PACK");
      c17 = STRING_TYPE("LG PKG");
      c11 = STRING_TYPE("MED PKG");
      c4 = STRING_TYPE("SM CASE");
      c2 = STRING_TYPE("AIR REG");
      c6 = STRING_TYPE("SM PACK");
      c10 = STRING_TYPE("MED BOX");
      c14 = STRING_TYPE("LG CASE");
      c3 = STRING_TYPE("DELIVER IN PERSON");
      c5 = STRING_TYPE("SM BOX");
      c13 = STRING_TYPE("Brand#23");
      c8 = STRING_TYPE("Brand#12");
      c15 = STRING_TYPE("LG BOX");
      c7 = STRING_TYPE("SM PKG");
      c9 = STRING_TYPE("MED BAG");
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        long agg1 = 0L;
        { //slice 
          const HashIndex_REVENUE_mLINEITEM3_map_0* i1 = static_cast<HashIndex_REVENUE_mLINEITEM3_map_0*>(REVENUE_mLINEITEM3.index[1]);
          const HASH_RES_t h1 = REVENUE_mLINEITEM3_mapkey0_idxfn::hash(se2.modify0(lineitem_partkey));
          HashIndex_REVENUE_mLINEITEM3_map_0::IdxNode* n1 = static_cast<HashIndex_REVENUE_mLINEITEM3_map_0::IdxNode*>(i1->slice(se2, h1));
          REVENUE_mLINEITEM3_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE p_brand = e1->P_BRAND;
              long p_size = e1->P_SIZE;
              STRING_TYPE p_container = e1->P_CONTAINER;
              long v1 = e1->__av;
              long l1 = ((/*if */(5L >= p_size && 11L >= lineitem_quantity && lineitem_quantity >= 1L && ((p_container == c4) || (p_container == c5) || (p_container == c6) || (p_container == c7)) && p_brand == c8) ? 1L : 0L) + ((/*if */(10L >= p_size && 20L >= lineitem_quantity && lineitem_quantity >= 10L && ((p_container == c9) || (p_container == c10) || (p_container == c11) || (p_container == c12)) && p_brand == c13) ? 1L : 0L) + (/*if */(15L >= p_size && 30L >= lineitem_quantity && lineitem_quantity >= 20L && ((p_container == c14) || (p_container == c15) || (p_container == c16) || (p_container == c17)) && p_brand == c18) ? 1L : 0L)));
              (/*if */(l1 > 0L) ? agg1 += v1 : 0L);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  REVENUE_mLINEITEM3_mapkey0_idxfn::equals(se2, *e1)); 
          }
        }(/*if */(((lineitem_shipmode == c1) || (lineitem_shipmode == c2)) && lineitem_shipinstruct == c3) ? REVENUE += (agg1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : 0L);
        (/*if */(((lineitem_shipmode == c1) || (lineitem_shipmode == c2)) && lineitem_shipinstruct == c3) ? REVENUE_mPART2.addOrDelOnZero(se3.modify(lineitem_partkey,lineitem_quantity),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        long agg2 = 0L;
        { //slice 
          const HashIndex_REVENUE_mLINEITEM3_map_0* i2 = static_cast<HashIndex_REVENUE_mLINEITEM3_map_0*>(REVENUE_mLINEITEM3.index[1]);
          const HASH_RES_t h2 = REVENUE_mLINEITEM3_mapkey0_idxfn::hash(se5.modify0(lineitem_partkey));
          HashIndex_REVENUE_mLINEITEM3_map_0::IdxNode* n2 = static_cast<HashIndex_REVENUE_mLINEITEM3_map_0::IdxNode*>(i2->slice(se5, h2));
          REVENUE_mLINEITEM3_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE p_brand = e2->P_BRAND;
              long p_size = e2->P_SIZE;
              STRING_TYPE p_container = e2->P_CONTAINER;
              long v2 = e2->__av;
              long l2 = ((/*if */(((p_container == c4) || (p_container == c5) || (p_container == c6) || (p_container == c7)) && lineitem_quantity >= 1L && 11L >= lineitem_quantity && 5L >= p_size && p_brand == c8) ? 1L : 0L) + ((/*if */(((p_container == c9) || (p_container == c10) || (p_container == c11) || (p_container == c12)) && lineitem_quantity >= 10L && 20L >= lineitem_quantity && 10L >= p_size && p_brand == c13) ? 1L : 0L) + (/*if */(((p_container == c14) || (p_container == c15) || (p_container == c16) || (p_container == c17)) && lineitem_quantity >= 20L && 30L >= lineitem_quantity && 15L >= p_size && p_brand == c18) ? 1L : 0L)));
              (/*if */(l2 > 0L) ? agg2 += v2 : 0L);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  REVENUE_mLINEITEM3_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }(/*if */(((lineitem_shipmode == c1) || (lineitem_shipmode == c2)) && lineitem_shipinstruct == c3) ? REVENUE += (agg2 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : 0L);
        (/*if */(((lineitem_shipmode == c1) || (lineitem_shipmode == c2)) && lineitem_shipinstruct == c3) ? REVENUE_mPART2.addOrDelOnZero(se6.modify(lineitem_partkey,lineitem_quantity),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        DOUBLE_TYPE agg3 = 0.0;
        { //slice 
          const HashIndex_REVENUE_mPART2_map_0* i3 = static_cast<HashIndex_REVENUE_mPART2_map_0*>(REVENUE_mPART2.index[1]);
          const HASH_RES_t h3 = REVENUE_mPART2_mapkey0_idxfn::hash(se8.modify0(part_partkey));
          HashIndex_REVENUE_mPART2_map_0::IdxNode* n3 = static_cast<HashIndex_REVENUE_mPART2_map_0::IdxNode*>(i3->slice(se8, h3));
          REVENUE_mPART2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              DOUBLE_TYPE l_quantity = e3->L_QUANTITY;
              DOUBLE_TYPE v3 = e3->__av;
              long l3 = ((/*if */(5L >= part_size && 11L >= l_quantity && l_quantity >= 1L && ((part_container == c4) || (part_container == c5) || (part_container == c6) || (part_container == c7)) && part_brand == c8) ? 1L : 0L) + ((/*if */(10L >= part_size && 20L >= l_quantity && l_quantity >= 10L && ((part_container == c9) || (part_container == c10) || (part_container == c11) || (part_container == c12)) && part_brand == c13) ? 1L : 0L) + (/*if */(15L >= part_size && 30L >= l_quantity && l_quantity >= 20L && ((part_container == c14) || (part_container == c15) || (part_container == c16) || (part_container == c17)) && part_brand == c18) ? 1L : 0L)));
              (/*if */(l3 > 0L) ? agg3 += v3 : 0.0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  REVENUE_mPART2_mapkey0_idxfn::equals(se8, *e3)); 
          }
        }(/*if */(part_size >= 1L) ? REVENUE += agg3 : 0L);
        (/*if */(part_size >= 1L) ? REVENUE_mLINEITEM3.addOrDelOnZero(se9.modify(part_partkey,part_brand,part_size,part_container),1L) : (void)0);
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  //++tN;
        DOUBLE_TYPE agg4 = 0.0;
        { //slice 
          const HashIndex_REVENUE_mPART2_map_0* i4 = static_cast<HashIndex_REVENUE_mPART2_map_0*>(REVENUE_mPART2.index[1]);
          const HASH_RES_t h4 = REVENUE_mPART2_mapkey0_idxfn::hash(se11.modify0(part_partkey));
          HashIndex_REVENUE_mPART2_map_0::IdxNode* n4 = static_cast<HashIndex_REVENUE_mPART2_map_0::IdxNode*>(i4->slice(se11, h4));
          REVENUE_mPART2_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              DOUBLE_TYPE l_quantity = e4->L_QUANTITY;
              DOUBLE_TYPE v4 = e4->__av;
              long l4 = ((/*if */(((part_container == c4) || (part_container == c5) || (part_container == c6) || (part_container == c7)) && l_quantity >= 1L && 11L >= l_quantity && 5L >= part_size && part_brand == c8) ? 1L : 0L) + ((/*if */(((part_container == c9) || (part_container == c10) || (part_container == c11) || (part_container == c12)) && l_quantity >= 10L && 20L >= l_quantity && 10L >= part_size && part_brand == c13) ? 1L : 0L) + (/*if */(((part_container == c14) || (part_container == c15) || (part_container == c16) || (part_container == c17)) && l_quantity >= 20L && 30L >= l_quantity && 15L >= part_size && part_brand == c18) ? 1L : 0L)));
              (/*if */(l4 > 0L) ? agg4 += v4 : 0.0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  REVENUE_mPART2_mapkey0_idxfn::equals(se11, *e4)); 
          }
        }(/*if */(part_size >= 1L) ? REVENUE += (agg4 * -1L) : 0L);
        (/*if */(part_size >= 1L) ? REVENUE_mLINEITEM3.addOrDelOnZero(se12.modify(part_partkey,part_brand,part_size,part_container),-1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  //
        REVENUE = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUE_mLINEITEM3_entry se2;
    REVENUE_mPART2_entry se3;
    REVENUE_mLINEITEM3_entry se5;
    REVENUE_mPART2_entry se6;
    REVENUE_mPART2_entry se8;
    REVENUE_mLINEITEM3_entry se9;
    REVENUE_mPART2_entry se11;
    REVENUE_mLINEITEM3_entry se12;
  
    /* Data structures used for storing materialized views */
    REVENUE_mPART2_map REVENUE_mPART2;
    REVENUE_mLINEITEM3_map REVENUE_mLINEITEM3;
    
    /*const static*/ STRING_TYPE c16;
    /*const static*/ STRING_TYPE c18;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c12;
    /*const static*/ STRING_TYPE c17;
    /*const static*/ STRING_TYPE c11;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c10;
    /*const static*/ STRING_TYPE c14;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c13;
    /*const static*/ STRING_TYPE c8;
    /*const static*/ STRING_TYPE c15;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c9;
  
  };

}
