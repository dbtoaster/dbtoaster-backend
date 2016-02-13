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
  struct NUMCUST_entry {
    STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_entry() { /*CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_entry(const STRING_TYPE& c0, const long c1) { CUSTSALE_CNTRYCODE = c0; __av = c1; }
    NUMCUST_entry(const NUMCUST_entry& other) : CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_entry& modify(const STRING_TYPE& c0) { CUSTSALE_CNTRYCODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUST_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_entry& x, const NUMCUST_entry& y) {
      return x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<NUMCUST_entry,long,
    HashIndex<NUMCUST_entry,long,NUMCUST_mapkey0_idxfn,true>
  > NUMCUST_map;
  typedef HashIndex<NUMCUST_entry,long,NUMCUST_mapkey0_idxfn,true> HashIndex_NUMCUST_map_0;
  
  struct NUMCUST_mCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUST_mCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUST_mCUSTOMER1_entry(const NUMCUST_mCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUST_mCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUST_mCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER1_entry& x, const NUMCUST_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUST_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER1_entry& x, const NUMCUST_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER1_entry,long,
    HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey0_idxfn,false>
  > NUMCUST_mCUSTOMER1_map;
  typedef HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey012_idxfn,true> HashIndex_NUMCUST_mCUSTOMER1_map_012;
  typedef HashIndex<NUMCUST_mCUSTOMER1_entry,long,NUMCUST_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_NUMCUST_mCUSTOMER1_map_0;
  
  struct NUMCUST_mCUSTOMER1_L3_1_entry {
    long C_CUSTKEY; long __av; 
    explicit NUMCUST_mCUSTOMER1_L3_1_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit NUMCUST_mCUSTOMER1_L3_1_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    NUMCUST_mCUSTOMER1_L3_1_entry(const NUMCUST_mCUSTOMER1_L3_1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMCUST_mCUSTOMER1_L3_1_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUST_mCUSTOMER1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUST_mCUSTOMER1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUST_mCUSTOMER1_L3_1_entry& x, const NUMCUST_mCUSTOMER1_L3_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUST_mCUSTOMER1_L3_1_entry,long,
    HashIndex<NUMCUST_mCUSTOMER1_L3_1_entry,long,NUMCUST_mCUSTOMER1_L3_1_mapkey0_idxfn,true>
  > NUMCUST_mCUSTOMER1_L3_1_map;
  typedef HashIndex<NUMCUST_mCUSTOMER1_L3_1_entry,long,NUMCUST_mCUSTOMER1_L3_1_mapkey0_idxfn,true> HashIndex_NUMCUST_mCUSTOMER1_L3_1_map_0;
  
  struct TOTALACCTBAL_entry {
    STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_entry() { /*CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { CUSTSALE_CNTRYCODE = c0; __av = c1; }
    TOTALACCTBAL_entry(const TOTALACCTBAL_entry& other) : CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_entry& modify(const STRING_TYPE& c0) { CUSTSALE_CNTRYCODE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBAL_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_entry& x, const TOTALACCTBAL_entry& y) {
      return x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_entry,DOUBLE_TYPE,TOTALACCTBAL_mapkey0_idxfn,true>
  > TOTALACCTBAL_map;
  typedef HashIndex<TOTALACCTBAL_entry,DOUBLE_TYPE,TOTALACCTBAL_mapkey0_idxfn,true> HashIndex_TOTALACCTBAL_map_0;
  
  struct TOTALACCTBAL_mCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBAL_mCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBAL_mCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBAL_mCUSTOMER1_entry(const TOTALACCTBAL_mCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBAL_mCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ACCTBAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTSALE_CNTRYCODE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TOTALACCTBAL_mCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER1_entry& x, const TOTALACCTBAL_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBAL_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBAL_mCUSTOMER1_entry& x, const TOTALACCTBAL_mCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn,false>
  > TOTALACCTBAL_mCUSTOMER1_map;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey012_idxfn,true> HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012;
  typedef HashIndex<TOTALACCTBAL_mCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn,false> HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const NUMCUST_map& _NUMCUST = get_NUMCUST();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(NUMCUST), _NUMCUST, "\t");
      ar << "\n";
      const TOTALACCTBAL_map& _TOTALACCTBAL = get_TOTALACCTBAL();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(TOTALACCTBAL), _TOTALACCTBAL, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const NUMCUST_map& get_NUMCUST() const {
      return NUMCUST;
    
    }
    const TOTALACCTBAL_map& get_TOTALACCTBAL() const {
      return TOTALACCTBAL;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    NUMCUST_map NUMCUST;
    TOTALACCTBAL_map TOTALACCTBAL;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), NUMCUST_mCUSTOMER1_L2_1_L1_1(0L), NUMCUST_mCUSTOMER1_L2_2(0.0) {
      c7 = STRING_TYPE("17");
      c2 = STRING_TYPE("31");
      c1 = STRING_TYPE("13");
      c3 = STRING_TYPE("23");
      c6 = STRING_TYPE("18");
      c4 = STRING_TYPE("29");
      c5 = STRING_TYPE("30");
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        long agg1 = 0L;
        long l1 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se2.modify(orders_custkey)) + 1L);
        (/*if */(l1 == 0L) ? agg1 += 1L : 0L);
        long agg2 = 0L;
        long l2 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se3.modify(orders_custkey));
        (/*if */(l2 == 0L) ? agg2 += 1L : 0L);
        DOUBLE_TYPE agg3 = 0.0;
        long l4 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l4) ? agg3 += Udiv(Ulistmax(1L, l4)) : 0.0);
        DOUBLE_TYPE l3 = (NUMCUST_mCUSTOMER1_L2_2 * agg3);
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER1_map_0* i1 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0*>(NUMCUST_mCUSTOMER1.index[1]);
          const HASH_RES_t h1 = NUMCUST_mCUSTOMER1_mapkey0_idxfn::hash(se4.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode* n1 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode*>(i1->slice(se4, h1));
          NUMCUST_mCUSTOMER1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e1->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e1->CUSTSALE_CNTRYCODE;
              long v1 = e1->__av;
              (/*if */(c_acctbal > l3) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),((agg1 + (agg2 * -1L)) * v1)) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  NUMCUST_mCUSTOMER1_mapkey0_idxfn::equals(se4, *e1)); 
          }
        }long agg4 = 0L;
        long l5 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se6.modify(orders_custkey)) + 1L);
        (/*if */(l5 == 0L) ? agg4 += 1L : 0L);
        long agg5 = 0L;
        long l6 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se7.modify(orders_custkey));
        (/*if */(l6 == 0L) ? agg5 += 1L : 0L);
        DOUBLE_TYPE agg6 = 0.0;
        long l8 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l8) ? agg6 += Udiv(Ulistmax(1L, l8)) : 0.0);
        DOUBLE_TYPE l7 = (NUMCUST_mCUSTOMER1_L2_2 * agg6);
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0* i2 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0*>(TOTALACCTBAL_mCUSTOMER1.index[1]);
          const HASH_RES_t h2 = TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::hash(se8.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode* n2 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode*>(i2->slice(se8, h2));
          TOTALACCTBAL_mCUSTOMER1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e2->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e2->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v2 = e2->__av;
              (/*if */(c_acctbal > l7) ? TOTALACCTBAL.addOrDelOnZero(se5.modify(custsale_cntrycode),((agg4 + (agg5 * -1L)) * v2)) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::equals(se8, *e2)); 
          }
        }NUMCUST_mCUSTOMER1_L3_1.addOrDelOnZero(se9.modify(orders_custkey),1L);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        long agg7 = 0L;
        long l9 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se11.modify(orders_custkey)) + -1L);
        (/*if */(l9 == 0L) ? agg7 += 1L : 0L);
        long agg8 = 0L;
        long l10 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se12.modify(orders_custkey));
        (/*if */(l10 == 0L) ? agg8 += 1L : 0L);
        DOUBLE_TYPE agg9 = 0.0;
        long l12 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l12) ? agg9 += Udiv(Ulistmax(1L, l12)) : 0.0);
        DOUBLE_TYPE l11 = (NUMCUST_mCUSTOMER1_L2_2 * agg9);
        { //slice 
          const HashIndex_NUMCUST_mCUSTOMER1_map_0* i3 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0*>(NUMCUST_mCUSTOMER1.index[1]);
          const HASH_RES_t h3 = NUMCUST_mCUSTOMER1_mapkey0_idxfn::hash(se13.modify0(orders_custkey));
          HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode* n3 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_0::IdxNode*>(i3->slice(se13, h3));
          NUMCUST_mCUSTOMER1_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e3->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e3->CUSTSALE_CNTRYCODE;
              long v3 = e3->__av;
              (/*if */(c_acctbal > l11) ? NUMCUST.addOrDelOnZero(se10.modify(custsale_cntrycode),((agg7 + (agg8 * -1L)) * v3)) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  NUMCUST_mCUSTOMER1_mapkey0_idxfn::equals(se13, *e3)); 
          }
        }long agg10 = 0L;
        long l13 = (NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se15.modify(orders_custkey)) + -1L);
        (/*if */(l13 == 0L) ? agg10 += 1L : 0L);
        long agg11 = 0L;
        long l14 = NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se16.modify(orders_custkey));
        (/*if */(l14 == 0L) ? agg11 += 1L : 0L);
        DOUBLE_TYPE agg12 = 0.0;
        long l16 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l16) ? agg12 += Udiv(Ulistmax(1L, l16)) : 0.0);
        DOUBLE_TYPE l15 = (NUMCUST_mCUSTOMER1_L2_2 * agg12);
        { //slice 
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0* i4 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0*>(TOTALACCTBAL_mCUSTOMER1.index[1]);
          const HASH_RES_t h4 = TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::hash(se17.modify0(orders_custkey));
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode* n4 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_0::IdxNode*>(i4->slice(se17, h4));
          TOTALACCTBAL_mCUSTOMER1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e4->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e4->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v4 = e4->__av;
              (/*if */(c_acctbal > l15) ? TOTALACCTBAL.addOrDelOnZero(se14.modify(custsale_cntrycode),((agg10 + (agg11 * -1L)) * v4)) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  TOTALACCTBAL_mCUSTOMER1_mapkey0_idxfn::equals(se17, *e4)); 
          }
        }NUMCUST_mCUSTOMER1_L3_1.addOrDelOnZero(se18.modify(orders_custkey),-1L);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        STRING_TYPE l17 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUST_mCUSTOMER1.addOrDelOnZero(se19.modify(customer_custkey,customer_acctbal,l17),1L) : (void)0);
        (/*if */(customer_acctbal > 0.0 && ((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUST_mCUSTOMER1_L2_1_L1_1 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && ((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUST_mCUSTOMER1_L2_2 += customer_acctbal : 0L);
        STRING_TYPE l18 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? TOTALACCTBAL_mCUSTOMER1.addOrDelOnZero(se22.modify(customer_custkey,customer_acctbal,l18),customer_acctbal) : (void)0);
        NUMCUST.clear();
        DOUBLE_TYPE agg13 = 0.0;
        long l20 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l20) ? agg13 += Udiv(Ulistmax(1L, l20)) : 0.0);
        DOUBLE_TYPE l19 = (NUMCUST_mCUSTOMER1_L2_2 * agg13);
        long l21 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER1_map_012* i5 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_012*>(NUMCUST_mCUSTOMER1.index[0]);
          HashIndex_NUMCUST_mCUSTOMER1_map_012::IdxNode* n5; 
          NUMCUST_mCUSTOMER1_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long c_custkey = e5->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e5->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e5->CUSTSALE_CNTRYCODE;
                long v5 = e5->__av;
                (/*if */(c_acctbal > l19 && l21 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se24.modify(c_custkey))) ? NUMCUST.addOrDelOnZero(se23.modify(custsale_cntrycode),v5) : (void)0);
              n5 = n5->nxt;
            }
          }
        }TOTALACCTBAL.clear();
        DOUBLE_TYPE agg14 = 0.0;
        long l23 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l23) ? agg14 += Udiv(Ulistmax(1L, l23)) : 0.0);
        DOUBLE_TYPE l22 = (NUMCUST_mCUSTOMER1_L2_2 * agg14);
        long l24 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012* i6 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012*>(TOTALACCTBAL_mCUSTOMER1.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012::IdxNode* n6; 
          TOTALACCTBAL_mCUSTOMER1_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long c_custkey = e6->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e6->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e6->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v6 = e6->__av;
                (/*if */(c_acctbal > l22 && l24 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se26.modify(c_custkey))) ? TOTALACCTBAL.addOrDelOnZero(se25.modify(custsale_cntrycode),v6) : (void)0);
              n6 = n6->nxt;
            }
          }
        }
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        STRING_TYPE l25 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUST_mCUSTOMER1.addOrDelOnZero(se27.modify(customer_custkey,customer_acctbal,l25),-1L) : (void)0);
        (/*if */(customer_acctbal > 0.0 && ((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUST_mCUSTOMER1_L2_1_L1_1 += -1L : 0L);
        (/*if */(customer_acctbal > 0.0 && ((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUST_mCUSTOMER1_L2_2 += (-1L * customer_acctbal) : 0L);
        STRING_TYPE l26 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? TOTALACCTBAL_mCUSTOMER1.addOrDelOnZero(se30.modify(customer_custkey,customer_acctbal,l26),(-1L * customer_acctbal)) : (void)0);
        NUMCUST.clear();
        DOUBLE_TYPE agg15 = 0.0;
        long l28 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l28) ? agg15 += Udiv(Ulistmax(1L, l28)) : 0.0);
        DOUBLE_TYPE l27 = (NUMCUST_mCUSTOMER1_L2_2 * agg15);
        long l29 = 0L;
        {  // foreach
          const HashIndex_NUMCUST_mCUSTOMER1_map_012* i7 = static_cast<HashIndex_NUMCUST_mCUSTOMER1_map_012*>(NUMCUST_mCUSTOMER1.index[0]);
          HashIndex_NUMCUST_mCUSTOMER1_map_012::IdxNode* n7; 
          NUMCUST_mCUSTOMER1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long c_custkey = e7->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e7->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e7->CUSTSALE_CNTRYCODE;
                long v7 = e7->__av;
                (/*if */(c_acctbal > l27 && l29 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se32.modify(c_custkey))) ? NUMCUST.addOrDelOnZero(se31.modify(custsale_cntrycode),v7) : (void)0);
              n7 = n7->nxt;
            }
          }
        }TOTALACCTBAL.clear();
        DOUBLE_TYPE agg16 = 0.0;
        long l31 = NUMCUST_mCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l31) ? agg16 += Udiv(Ulistmax(1L, l31)) : 0.0);
        DOUBLE_TYPE l30 = (NUMCUST_mCUSTOMER1_L2_2 * agg16);
        long l32 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012* i8 = static_cast<HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012*>(TOTALACCTBAL_mCUSTOMER1.index[0]);
          HashIndex_TOTALACCTBAL_mCUSTOMER1_map_012::IdxNode* n8; 
          TOTALACCTBAL_mCUSTOMER1_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long c_custkey = e8->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e8->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e8->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v8 = e8->__av;
                (/*if */(c_acctbal > l30 && l32 == NUMCUST_mCUSTOMER1_L3_1.getValueOrDefault(se34.modify(c_custkey))) ? TOTALACCTBAL.addOrDelOnZero(se33.modify(custsale_cntrycode),v8) : (void)0);
              n8 = n8->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  //
        NUMCUST_mCUSTOMER1_L2_2 = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    NUMCUST_entry se1;
    NUMCUST_mCUSTOMER1_L3_1_entry se2;
    NUMCUST_mCUSTOMER1_L3_1_entry se3;
    NUMCUST_mCUSTOMER1_entry se4;
    TOTALACCTBAL_entry se5;
    NUMCUST_mCUSTOMER1_L3_1_entry se6;
    NUMCUST_mCUSTOMER1_L3_1_entry se7;
    TOTALACCTBAL_mCUSTOMER1_entry se8;
    NUMCUST_mCUSTOMER1_L3_1_entry se9;
    NUMCUST_entry se10;
    NUMCUST_mCUSTOMER1_L3_1_entry se11;
    NUMCUST_mCUSTOMER1_L3_1_entry se12;
    NUMCUST_mCUSTOMER1_entry se13;
    TOTALACCTBAL_entry se14;
    NUMCUST_mCUSTOMER1_L3_1_entry se15;
    NUMCUST_mCUSTOMER1_L3_1_entry se16;
    TOTALACCTBAL_mCUSTOMER1_entry se17;
    NUMCUST_mCUSTOMER1_L3_1_entry se18;
    NUMCUST_mCUSTOMER1_entry se19;
    TOTALACCTBAL_mCUSTOMER1_entry se22;
    NUMCUST_entry se23;
    NUMCUST_mCUSTOMER1_L3_1_entry se24;
    TOTALACCTBAL_entry se25;
    NUMCUST_mCUSTOMER1_L3_1_entry se26;
    NUMCUST_mCUSTOMER1_entry se27;
    TOTALACCTBAL_mCUSTOMER1_entry se30;
    NUMCUST_entry se31;
    NUMCUST_mCUSTOMER1_L3_1_entry se32;
    TOTALACCTBAL_entry se33;
    NUMCUST_mCUSTOMER1_L3_1_entry se34;
  
    /* Data structures used for storing materialized views */
    NUMCUST_mCUSTOMER1_map NUMCUST_mCUSTOMER1;
    long NUMCUST_mCUSTOMER1_L2_1_L1_1;
    DOUBLE_TYPE NUMCUST_mCUSTOMER1_L2_2;
    NUMCUST_mCUSTOMER1_L3_1_map NUMCUST_mCUSTOMER1_L3_1;
    TOTALACCTBAL_mCUSTOMER1_map TOTALACCTBAL_mCUSTOMER1;
    
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c5;
  
  };

}
