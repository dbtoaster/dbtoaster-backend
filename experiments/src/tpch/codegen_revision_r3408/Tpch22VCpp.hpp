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
  
  struct NUMCUSTCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; long __av; 
    explicit NUMCUSTCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const long c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    NUMCUSTCUSTOMER1_entry(const NUMCUSTCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE NUMCUSTCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct NUMCUSTCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER1_entry& x, const NUMCUSTCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct NUMCUSTCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER1_entry& x, const NUMCUSTCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER1_entry,long,
    HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey0_idxfn,false>
  > NUMCUSTCUSTOMER1_map;
  typedef HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey012_idxfn,true> HashIndex_NUMCUSTCUSTOMER1_map_012;
  typedef HashIndex<NUMCUSTCUSTOMER1_entry,long,NUMCUSTCUSTOMER1_mapkey0_idxfn,false> HashIndex_NUMCUSTCUSTOMER1_map_0;
  
  struct NUMCUSTCUSTOMER1_L3_1_entry {
    long C_CUSTKEY; long __av; 
    explicit NUMCUSTCUSTOMER1_L3_1_entry() { /*C_CUSTKEY = 0L; __av = 0L; */ }
    explicit NUMCUSTCUSTOMER1_L3_1_entry(const long c0, const long c1) { C_CUSTKEY = c0; __av = c1; }
    NUMCUSTCUSTOMER1_L3_1_entry(const NUMCUSTCUSTOMER1_L3_1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE NUMCUSTCUSTOMER1_L3_1_entry& modify(const long c0) { C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NUMCUSTCUSTOMER1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const NUMCUSTCUSTOMER1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const NUMCUSTCUSTOMER1_L3_1_entry& x, const NUMCUSTCUSTOMER1_L3_1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<NUMCUSTCUSTOMER1_L3_1_entry,long,
    HashIndex<NUMCUSTCUSTOMER1_L3_1_entry,long,NUMCUSTCUSTOMER1_L3_1_mapkey0_idxfn,true>
  > NUMCUSTCUSTOMER1_L3_1_map;
  typedef HashIndex<NUMCUSTCUSTOMER1_L3_1_entry,long,NUMCUSTCUSTOMER1_L3_1_mapkey0_idxfn,true> HashIndex_NUMCUSTCUSTOMER1_L3_1_map_0;
  
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
  
  struct TOTALACCTBALCUSTOMER1_entry {
    long C_CUSTKEY; DOUBLE_TYPE C_ACCTBAL; STRING_TYPE CUSTSALE_CNTRYCODE; DOUBLE_TYPE __av; 
    explicit TOTALACCTBALCUSTOMER1_entry() { /*C_CUSTKEY = 0L; C_ACCTBAL = 0.0; CUSTSALE_CNTRYCODE = ""; __av = 0.0; */ }
    explicit TOTALACCTBALCUSTOMER1_entry(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2; __av = c3; }
    TOTALACCTBALCUSTOMER1_entry(const TOTALACCTBALCUSTOMER1_entry& other) : C_CUSTKEY( other.C_CUSTKEY ), C_ACCTBAL( other.C_ACCTBAL ), CUSTSALE_CNTRYCODE( other.CUSTSALE_CNTRYCODE ), __av( other.__av ) {}
    FORCE_INLINE TOTALACCTBALCUSTOMER1_entry& modify(const long c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2) { C_CUSTKEY = c0; C_ACCTBAL = c1; CUSTSALE_CNTRYCODE = c2;  return *this; }
    FORCE_INLINE TOTALACCTBALCUSTOMER1_entry& modify0(const long c0) { C_CUSTKEY = c0;  return *this; }
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
  struct TOTALACCTBALCUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      hash_combine(h, e.C_ACCTBAL);
      hash_combine(h, e.CUSTSALE_CNTRYCODE);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER1_entry& x, const TOTALACCTBALCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY && x.C_ACCTBAL == y.C_ACCTBAL && x.CUSTSALE_CNTRYCODE == y.CUSTSALE_CNTRYCODE;
    }
  };
  
  struct TOTALACCTBALCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TOTALACCTBALCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const TOTALACCTBALCUSTOMER1_entry& x, const TOTALACCTBALCUSTOMER1_entry& y) {
      return x.C_CUSTKEY == y.C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey0_idxfn,false>
  > TOTALACCTBALCUSTOMER1_map;
  typedef HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey012_idxfn,true> HashIndex_TOTALACCTBALCUSTOMER1_map_012;
  typedef HashIndex<TOTALACCTBALCUSTOMER1_entry,DOUBLE_TYPE,TOTALACCTBALCUSTOMER1_mapkey0_idxfn,false> HashIndex_TOTALACCTBALCUSTOMER1_map_0;
  
  
  
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
    data_t(): tlq_t(), NUMCUSTCUSTOMER1_L2_1_L1_1(0L), NUMCUSTCUSTOMER1_L2_2(0.0) {
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
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg1 = 0L;
        long l1 = (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se2.modify(orders_custkey)) + 1L);
        (/*if */(l1 == 0L) ? agg1 += 1L : 0L);
        long agg2 = 0L;
        long l2 = NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se3.modify(orders_custkey));
        (/*if */(l2 == 0L) ? agg2 += 1L : 0L);
        DOUBLE_TYPE agg3 = 0.0;
        long l4 = NUMCUSTCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l4) ? agg3 += Udiv(Ulistmax(1L, l4)) : 0.0);
        DOUBLE_TYPE l3 = (NUMCUSTCUSTOMER1_L2_2 * agg3);
        { //slice 
          const HashIndex_NUMCUSTCUSTOMER1_map_0* i1 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0*>(NUMCUSTCUSTOMER1.index[1]);
          const HASH_RES_t h1 = NUMCUSTCUSTOMER1_mapkey0_idxfn::hash(se4.modify0(orders_custkey));
          HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode* n1 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_0::IdxNode*>(i1->slice(se4, h1));
          NUMCUSTCUSTOMER1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e1->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e1->CUSTSALE_CNTRYCODE;
              long v1 = e1->__av;
              (/*if */(c_acctbal > l3) ? NUMCUST.addOrDelOnZero(se1.modify(custsale_cntrycode),((agg1 + (agg2 * -1L)) * v1)) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  NUMCUSTCUSTOMER1_mapkey0_idxfn::equals(se4, *e1)); 
          }
        }long agg4 = 0L;
        long l5 = (NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se6.modify(orders_custkey)) + 1L);
        (/*if */(l5 == 0L) ? agg4 += 1L : 0L);
        long agg5 = 0L;
        long l6 = NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se7.modify(orders_custkey));
        (/*if */(l6 == 0L) ? agg5 += 1L : 0L);
        DOUBLE_TYPE agg6 = 0.0;
        long l8 = NUMCUSTCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l8) ? agg6 += Udiv(Ulistmax(1L, l8)) : 0.0);
        DOUBLE_TYPE l7 = (NUMCUSTCUSTOMER1_L2_2 * agg6);
        { //slice 
          const HashIndex_TOTALACCTBALCUSTOMER1_map_0* i2 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0*>(TOTALACCTBALCUSTOMER1.index[1]);
          const HASH_RES_t h2 = TOTALACCTBALCUSTOMER1_mapkey0_idxfn::hash(se8.modify0(orders_custkey));
          HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode* n2 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_0::IdxNode*>(i2->slice(se8, h2));
          TOTALACCTBALCUSTOMER1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              DOUBLE_TYPE c_acctbal = e2->C_ACCTBAL;
              STRING_TYPE custsale_cntrycode = e2->CUSTSALE_CNTRYCODE;
              DOUBLE_TYPE v2 = e2->__av;
              (/*if */(c_acctbal > l7) ? TOTALACCTBAL.addOrDelOnZero(se5.modify(custsale_cntrycode),((agg4 + (agg5 * -1L)) * v2)) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  TOTALACCTBALCUSTOMER1_mapkey0_idxfn::equals(se8, *e2)); 
          }
        }NUMCUSTCUSTOMER1_L3_1.addOrDelOnZero(se9.modify(orders_custkey),1L);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        STRING_TYPE l9 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUSTCUSTOMER1.addOrDelOnZero(se10.modify(customer_custkey,customer_acctbal,l9),1L) : (void)0);
        (/*if */(customer_acctbal > 0.0 && ((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUSTCUSTOMER1_L2_1_L1_1 += 1L : 0L);
        (/*if */(customer_acctbal > 0.0 && ((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? NUMCUSTCUSTOMER1_L2_2 += customer_acctbal : 0L);
        STRING_TYPE l10 = Usubstring(customer_phone, 0L, 2L);
        (/*if */(((Usubstring(customer_phone, 0L, 2L) == c1) || (Usubstring(customer_phone, 0L, 2L) == c2) || (Usubstring(customer_phone, 0L, 2L) == c3) || (Usubstring(customer_phone, 0L, 2L) == c4) || (Usubstring(customer_phone, 0L, 2L) == c5) || (Usubstring(customer_phone, 0L, 2L) == c6) || (Usubstring(customer_phone, 0L, 2L) == c7))) ? TOTALACCTBALCUSTOMER1.addOrDelOnZero(se13.modify(customer_custkey,customer_acctbal,l10),customer_acctbal) : (void)0);
        NUMCUST.clear();
        DOUBLE_TYPE agg7 = 0.0;
        long l12 = NUMCUSTCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l12) ? agg7 += Udiv(Ulistmax(1L, l12)) : 0.0);
        DOUBLE_TYPE l11 = (NUMCUSTCUSTOMER1_L2_2 * agg7);
        long l13 = 0L;
        {  // foreach
          const HashIndex_NUMCUSTCUSTOMER1_map_012* i3 = static_cast<HashIndex_NUMCUSTCUSTOMER1_map_012*>(NUMCUSTCUSTOMER1.index[0]);
          HashIndex_NUMCUSTCUSTOMER1_map_012::IdxNode* n3; 
          NUMCUSTCUSTOMER1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long c_custkey = e3->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e3->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e3->CUSTSALE_CNTRYCODE;
                long v3 = e3->__av;
                (/*if */(c_acctbal > l11 && l13 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se15.modify(c_custkey))) ? NUMCUST.addOrDelOnZero(se14.modify(custsale_cntrycode),v3) : (void)0);
              n3 = n3->nxt;
            }
          }
        }TOTALACCTBAL.clear();
        DOUBLE_TYPE agg8 = 0.0;
        long l15 = NUMCUSTCUSTOMER1_L2_1_L1_1;
        (/*if */(0L != l15) ? agg8 += Udiv(Ulistmax(1L, l15)) : 0.0);
        DOUBLE_TYPE l14 = (NUMCUSTCUSTOMER1_L2_2 * agg8);
        long l16 = 0L;
        {  // foreach
          const HashIndex_TOTALACCTBALCUSTOMER1_map_012* i4 = static_cast<HashIndex_TOTALACCTBALCUSTOMER1_map_012*>(TOTALACCTBALCUSTOMER1.index[0]);
          HashIndex_TOTALACCTBALCUSTOMER1_map_012::IdxNode* n4; 
          TOTALACCTBALCUSTOMER1_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long c_custkey = e4->C_CUSTKEY;
                DOUBLE_TYPE c_acctbal = e4->C_ACCTBAL;
                STRING_TYPE custsale_cntrycode = e4->CUSTSALE_CNTRYCODE;
                DOUBLE_TYPE v4 = e4->__av;
                (/*if */(c_acctbal > l14 && l16 == NUMCUSTCUSTOMER1_L3_1.getValueOrDefault(se17.modify(c_custkey))) ? TOTALACCTBAL.addOrDelOnZero(se16.modify(custsale_cntrycode),v4) : (void)0);
              n4 = n4->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        NUMCUSTCUSTOMER1_L2_2 = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    NUMCUST_entry se1;
    NUMCUSTCUSTOMER1_L3_1_entry se2;
    NUMCUSTCUSTOMER1_L3_1_entry se3;
    NUMCUSTCUSTOMER1_entry se4;
    TOTALACCTBAL_entry se5;
    NUMCUSTCUSTOMER1_L3_1_entry se6;
    NUMCUSTCUSTOMER1_L3_1_entry se7;
    TOTALACCTBALCUSTOMER1_entry se8;
    NUMCUSTCUSTOMER1_L3_1_entry se9;
    NUMCUSTCUSTOMER1_entry se10;
    TOTALACCTBALCUSTOMER1_entry se13;
    NUMCUST_entry se14;
    NUMCUSTCUSTOMER1_L3_1_entry se15;
    TOTALACCTBAL_entry se16;
    NUMCUSTCUSTOMER1_L3_1_entry se17;
  
    /* Data structures used for storing materialized views */
    NUMCUSTCUSTOMER1_map NUMCUSTCUSTOMER1;
    long NUMCUSTCUSTOMER1_L2_1_L1_1;
    DOUBLE_TYPE NUMCUSTCUSTOMER1_L2_2;
    NUMCUSTCUSTOMER1_L3_1_map NUMCUSTCUSTOMER1_L3_1;
    TOTALACCTBALCUSTOMER1_map TOTALACCTBALCUSTOMER1;
    
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c5;
  
  };

}
