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
  struct COUNT_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; DOUBLE_TYPE R1_TOTAL_REVENUE; long __av; 
    explicit COUNT_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; R1_TOTAL_REVENUE = 0.0; __av = 0L; */ }
    explicit COUNT_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4, const long c5) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; R1_TOTAL_REVENUE = c4; __av = c5; }
    COUNT_entry(const COUNT_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), R1_TOTAL_REVENUE( other.R1_TOTAL_REVENUE ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; R1_TOTAL_REVENUE = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R1_TOTAL_REVENUE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      hash_combine(h, e.R1_TOTAL_REVENUE);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE && x.R1_TOTAL_REVENUE == y.R1_TOTAL_REVENUE;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey01234_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey01234_idxfn,true> HashIndex_COUNT_map_01234;
  
  struct COUNTLINEITEM1_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; long __av; 
    explicit COUNTLINEITEM1_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; __av = 0L; */ }
    explicit COUNTLINEITEM1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; __av = c4; }
    COUNTLINEITEM1_entry(const COUNTLINEITEM1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_PHONE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_entry& x, const COUNTLINEITEM1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_entry,long,
    HashIndex<COUNTLINEITEM1_entry,long,COUNTLINEITEM1_mapkey0123_idxfn,true>
  > COUNTLINEITEM1_map;
  typedef HashIndex<COUNTLINEITEM1_entry,long,COUNTLINEITEM1_mapkey0123_idxfn,true> HashIndex_COUNTLINEITEM1_map_0123;
  
  struct COUNTLINEITEM1_E2_1_entry {
    long S_SUPPKEY; long __av; 
    explicit COUNTLINEITEM1_E2_1_entry() { /*S_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTLINEITEM1_E2_1_entry(const long c0, const long c1) { S_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_E2_1_entry(const COUNTLINEITEM1_E2_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_E2_1_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_E2_1_entry& x, const COUNTLINEITEM1_E2_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_E2_1_entry,long,
    HashIndex<COUNTLINEITEM1_E2_1_entry,long,COUNTLINEITEM1_E2_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_E2_1_map;
  typedef HashIndex<COUNTLINEITEM1_E2_1_entry,long,COUNTLINEITEM1_E2_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_E2_1_map_0;
  
  struct COUNTLINEITEM1_L3_1_entry {
    long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTLINEITEM1_L3_1_entry() { /*S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTLINEITEM1_L3_1_entry(const long c0, const DOUBLE_TYPE c1) { S_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L3_1_entry(const COUNTLINEITEM1_L3_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L3_1_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L3_1_entry& x, const COUNTLINEITEM1_L3_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L3_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTLINEITEM1_L3_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L3_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L3_1_map;
  typedef HashIndex<COUNTLINEITEM1_L3_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L3_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L3_1_map_0;
  
  struct COUNTLINEITEM1_L4_1_E1_1_entry {
    long R2_SUPPKEY; long __av; 
    explicit COUNTLINEITEM1_L4_1_E1_1_entry() { /*R2_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNTLINEITEM1_L4_1_E1_1_entry(const long c0, const long c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L4_1_E1_1_entry(const COUNTLINEITEM1_L4_1_E1_1_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L4_1_E1_1_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L4_1_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L4_1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L4_1_E1_1_entry& x, const COUNTLINEITEM1_L4_1_E1_1_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L4_1_E1_1_entry,long,
    HashIndex<COUNTLINEITEM1_L4_1_E1_1_entry,long,COUNTLINEITEM1_L4_1_E1_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L4_1_E1_1_map;
  typedef HashIndex<COUNTLINEITEM1_L4_1_E1_1_entry,long,COUNTLINEITEM1_L4_1_E1_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0;
  
  struct COUNTLINEITEM1_L4_1_L2_1_entry {
    long R2_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTLINEITEM1_L4_1_L2_1_entry() { /*R2_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTLINEITEM1_L4_1_L2_1_entry(const long c0, const DOUBLE_TYPE c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNTLINEITEM1_L4_1_L2_1_entry(const COUNTLINEITEM1_L4_1_L2_1_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTLINEITEM1_L4_1_L2_1_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTLINEITEM1_L4_1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTLINEITEM1_L4_1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTLINEITEM1_L4_1_L2_1_entry& x, const COUNTLINEITEM1_L4_1_L2_1_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L4_1_L2_1_mapkey0_idxfn,true>
  > COUNTLINEITEM1_L4_1_L2_1_map;
  typedef HashIndex<COUNTLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,COUNTLINEITEM1_L4_1_L2_1_mapkey0_idxfn,true> HashIndex_COUNTLINEITEM1_L4_1_L2_1_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const COUNT_map& _COUNT = get_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(COUNT), _COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const COUNT_map& get_COUNT() const {
      return COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    COUNT_map COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = Udate(STRING_TYPE("1996-4-1"));
      c1 = Udate(STRING_TYPE("1996-1-1"));
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNTLINEITEM1_E2_1.addOrDelOnZero(se1.modify(lineitem_suppkey),1L) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNTLINEITEM1_L3_1.addOrDelOnZero(se2.modify(lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNTLINEITEM1_L4_1_E1_1.addOrDelOnZero(se3.modify(lineitem_suppkey),1L) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNTLINEITEM1_L4_1_L2_1.addOrDelOnZero(se4.modify(lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        COUNT.clear();
        {  // foreach
          const HashIndex_COUNTLINEITEM1_map_0123* i1 = static_cast<HashIndex_COUNTLINEITEM1_map_0123*>(COUNTLINEITEM1.index[0]);
          HashIndex_COUNTLINEITEM1_map_0123::IdxNode* n1; 
          COUNTLINEITEM1_entry* e1;
        
          for (size_t i = 0; i < i1->size_; i++)
          {
            n1 = i1->buckets_ + i;
            while (n1 && (e1 = n1->obj))
            {
                long s_suppkey = e1->S_SUPPKEY;
                STRING_TYPE s_name = e1->S_NAME;
                STRING_TYPE s_address = e1->S_ADDRESS;
                STRING_TYPE s_phone = e1->S_PHONE;
                long v1 = e1->__av;
                DOUBLE_TYPE l1 = COUNTLINEITEM1_L3_1.getValueOrDefault(se6.modify(s_suppkey));
                long agg1 = 0L;
                long agg2 = 0L;
                {  // foreach
                  const HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0* i2 = static_cast<HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0*>(COUNTLINEITEM1_L4_1_E1_1.index[0]);
                  HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0::IdxNode* n2; 
                  COUNTLINEITEM1_L4_1_E1_1_entry* e2;
                
                  for (size_t i = 0; i < i2->size_; i++)
                  {
                    n2 = i2->buckets_ + i;
                    while (n2 && (e2 = n2->obj))
                    {
                        long r2_suppkey = e2->R2_SUPPKEY;
                        long v2 = e2->__av;
                        DOUBLE_TYPE l3 = COUNTLINEITEM1_L4_1_L2_1.getValueOrDefault(se8.modify(r2_suppkey));
                        (/*if */(l3 > l1) ? agg2 += (v2 != 0 ? 1L : 0L) : 0L);
                      n2 = n2->nxt;
                    }
                  }
                }long l2 = agg2;
                (/*if */(l2 == 0L) ? agg1 += 1L : 0L);
                COUNT.addOrDelOnZero(se5.modify(s_suppkey,s_name,s_address,s_phone,l1),(v1 * ((COUNTLINEITEM1_E2_1.getValueOrDefault(se7.modify(s_suppkey)) != 0 ? 1L : 0L) * agg1)));
              n1 = n1->nxt;
            }
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        DOUBLE_TYPE l4 = COUNTLINEITEM1_L3_1.getValueOrDefault(se10.modify(supplier_suppkey));
        long agg3 = 0L;
        long agg4 = 0L;
        {  // foreach
          const HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0* i3 = static_cast<HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0*>(COUNTLINEITEM1_L4_1_E1_1.index[0]);
          HashIndex_COUNTLINEITEM1_L4_1_E1_1_map_0::IdxNode* n3; 
          COUNTLINEITEM1_L4_1_E1_1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long r2_suppkey = e3->R2_SUPPKEY;
                long v3 = e3->__av;
                DOUBLE_TYPE l6 = COUNTLINEITEM1_L4_1_L2_1.getValueOrDefault(se12.modify(r2_suppkey));
                (/*if */(l6 > l4) ? agg4 += (v3 != 0 ? 1L : 0L) : 0L);
              n3 = n3->nxt;
            }
          }
        }long l5 = agg4;
        (/*if */(l5 == 0L) ? agg3 += 1L : 0L);
        COUNT.addOrDelOnZero(se9.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone,l4),((COUNTLINEITEM1_E2_1.getValueOrDefault(se11.modify(supplier_suppkey)) != 0 ? 1L : 0L) * agg3));
        COUNTLINEITEM1.addOrDelOnZero(se13.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone),1L);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTLINEITEM1_E2_1_entry se1;
    COUNTLINEITEM1_L3_1_entry se2;
    COUNTLINEITEM1_L4_1_E1_1_entry se3;
    COUNTLINEITEM1_L4_1_L2_1_entry se4;
    COUNT_entry se5;
    COUNTLINEITEM1_L3_1_entry se6;
    COUNTLINEITEM1_E2_1_entry se7;
    COUNTLINEITEM1_L4_1_L2_1_entry se8;
    COUNT_entry se9;
    COUNTLINEITEM1_L3_1_entry se10;
    COUNTLINEITEM1_E2_1_entry se11;
    COUNTLINEITEM1_L4_1_L2_1_entry se12;
    COUNTLINEITEM1_entry se13;
  
    /* Data structures used for storing materialized views */
    COUNTLINEITEM1_map COUNTLINEITEM1;
    COUNTLINEITEM1_E2_1_map COUNTLINEITEM1_E2_1;
    COUNTLINEITEM1_L3_1_map COUNTLINEITEM1_L3_1;
    COUNTLINEITEM1_L4_1_E1_1_map COUNTLINEITEM1_L4_1_E1_1;
    COUNTLINEITEM1_L4_1_L2_1_map COUNTLINEITEM1_L4_1_L2_1;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
  
  };

}
