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
  
  struct COUNT_mLINEITEM1_entry {
    long S_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; STRING_TYPE S_PHONE; long __av; 
    explicit COUNT_mLINEITEM1_entry() { /*S_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; S_PHONE = ""; __av = 0L; */ }
    explicit COUNT_mLINEITEM1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3; __av = c4; }
    COUNT_mLINEITEM1_entry(const COUNT_mLINEITEM1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), S_PHONE( other.S_PHONE ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mLINEITEM1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { S_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; S_PHONE = c3;  return *this; }
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
  struct COUNT_mLINEITEM1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      hash_combine(h, e.S_PHONE);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mLINEITEM1_entry& x, const COUNT_mLINEITEM1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS && x.S_PHONE == y.S_PHONE;
    }
  };
  
  typedef MultiHashMap<COUNT_mLINEITEM1_entry,long,
    HashIndex<COUNT_mLINEITEM1_entry,long,COUNT_mLINEITEM1_mapkey0123_idxfn,true>
  > COUNT_mLINEITEM1_map;
  typedef HashIndex<COUNT_mLINEITEM1_entry,long,COUNT_mLINEITEM1_mapkey0123_idxfn,true> HashIndex_COUNT_mLINEITEM1_map_0123;
  
  struct COUNT_mLINEITEM1_E2_1_entry {
    long S_SUPPKEY; long __av; 
    explicit COUNT_mLINEITEM1_E2_1_entry() { /*S_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNT_mLINEITEM1_E2_1_entry(const long c0, const long c1) { S_SUPPKEY = c0; __av = c1; }
    COUNT_mLINEITEM1_E2_1_entry(const COUNT_mLINEITEM1_E2_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mLINEITEM1_E2_1_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mLINEITEM1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mLINEITEM1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mLINEITEM1_E2_1_entry& x, const COUNT_mLINEITEM1_E2_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mLINEITEM1_E2_1_entry,long,
    HashIndex<COUNT_mLINEITEM1_E2_1_entry,long,COUNT_mLINEITEM1_E2_1_mapkey0_idxfn,true>
  > COUNT_mLINEITEM1_E2_1_map;
  typedef HashIndex<COUNT_mLINEITEM1_E2_1_entry,long,COUNT_mLINEITEM1_E2_1_mapkey0_idxfn,true> HashIndex_COUNT_mLINEITEM1_E2_1_map_0;
  
  struct COUNT_mLINEITEM1_L3_1_entry {
    long S_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNT_mLINEITEM1_L3_1_entry() { /*S_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNT_mLINEITEM1_L3_1_entry(const long c0, const DOUBLE_TYPE c1) { S_SUPPKEY = c0; __av = c1; }
    COUNT_mLINEITEM1_L3_1_entry(const COUNT_mLINEITEM1_L3_1_entry& other) : S_SUPPKEY( other.S_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mLINEITEM1_L3_1_entry& modify(const long c0) { S_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mLINEITEM1_L3_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mLINEITEM1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mLINEITEM1_L3_1_entry& x, const COUNT_mLINEITEM1_L3_1_entry& y) {
      return x.S_SUPPKEY == y.S_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mLINEITEM1_L3_1_entry,DOUBLE_TYPE,
    HashIndex<COUNT_mLINEITEM1_L3_1_entry,DOUBLE_TYPE,COUNT_mLINEITEM1_L3_1_mapkey0_idxfn,true>
  > COUNT_mLINEITEM1_L3_1_map;
  typedef HashIndex<COUNT_mLINEITEM1_L3_1_entry,DOUBLE_TYPE,COUNT_mLINEITEM1_L3_1_mapkey0_idxfn,true> HashIndex_COUNT_mLINEITEM1_L3_1_map_0;
  
  struct COUNT_mLINEITEM1_L4_1_E1_1_entry {
    long R2_SUPPKEY; long __av; 
    explicit COUNT_mLINEITEM1_L4_1_E1_1_entry() { /*R2_SUPPKEY = 0L; __av = 0L; */ }
    explicit COUNT_mLINEITEM1_L4_1_E1_1_entry(const long c0, const long c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNT_mLINEITEM1_L4_1_E1_1_entry(const COUNT_mLINEITEM1_L4_1_E1_1_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mLINEITEM1_L4_1_E1_1_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mLINEITEM1_L4_1_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mLINEITEM1_L4_1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mLINEITEM1_L4_1_E1_1_entry& x, const COUNT_mLINEITEM1_L4_1_E1_1_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mLINEITEM1_L4_1_E1_1_entry,long,
    HashIndex<COUNT_mLINEITEM1_L4_1_E1_1_entry,long,COUNT_mLINEITEM1_L4_1_E1_1_mapkey0_idxfn,true>
  > COUNT_mLINEITEM1_L4_1_E1_1_map;
  typedef HashIndex<COUNT_mLINEITEM1_L4_1_E1_1_entry,long,COUNT_mLINEITEM1_L4_1_E1_1_mapkey0_idxfn,true> HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0;
  
  struct COUNT_mLINEITEM1_L4_1_L2_1_entry {
    long R2_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNT_mLINEITEM1_L4_1_L2_1_entry() { /*R2_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNT_mLINEITEM1_L4_1_L2_1_entry(const long c0, const DOUBLE_TYPE c1) { R2_SUPPKEY = c0; __av = c1; }
    COUNT_mLINEITEM1_L4_1_L2_1_entry(const COUNT_mLINEITEM1_L4_1_L2_1_entry& other) : R2_SUPPKEY( other.R2_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mLINEITEM1_L4_1_L2_1_entry& modify(const long c0) { R2_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, R2_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mLINEITEM1_L4_1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mLINEITEM1_L4_1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.R2_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mLINEITEM1_L4_1_L2_1_entry& x, const COUNT_mLINEITEM1_L4_1_L2_1_entry& y) {
      return x.R2_SUPPKEY == y.R2_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,
    HashIndex<COUNT_mLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,COUNT_mLINEITEM1_L4_1_L2_1_mapkey0_idxfn,true>
  > COUNT_mLINEITEM1_L4_1_L2_1_map;
  typedef HashIndex<COUNT_mLINEITEM1_L4_1_L2_1_entry,DOUBLE_TYPE,COUNT_mLINEITEM1_L4_1_L2_1_mapkey0_idxfn,true> HashIndex_COUNT_mLINEITEM1_L4_1_L2_1_map_0;
  
  
  
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
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_E2_1.addOrDelOnZero(se1.modify(lineitem_suppkey),1L) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_L3_1.addOrDelOnZero(se2.modify(lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_L4_1_E1_1.addOrDelOnZero(se3.modify(lineitem_suppkey),1L) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_L4_1_L2_1.addOrDelOnZero(se4.modify(lineitem_suppkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        COUNT.clear();
        {  // foreach
          const HashIndex_COUNT_mLINEITEM1_map_0123* i1 = static_cast<HashIndex_COUNT_mLINEITEM1_map_0123*>(COUNT_mLINEITEM1.index[0]);
          HashIndex_COUNT_mLINEITEM1_map_0123::IdxNode* n1; 
          COUNT_mLINEITEM1_entry* e1;
        
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
                DOUBLE_TYPE l1 = COUNT_mLINEITEM1_L3_1.getValueOrDefault(se6.modify(s_suppkey));
                long agg1 = 0L;
                long agg2 = 0L;
                {  // foreach
                  const HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0* i2 = static_cast<HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0*>(COUNT_mLINEITEM1_L4_1_E1_1.index[0]);
                  HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0::IdxNode* n2; 
                  COUNT_mLINEITEM1_L4_1_E1_1_entry* e2;
                
                  for (size_t i = 0; i < i2->size_; i++)
                  {
                    n2 = i2->buckets_ + i;
                    while (n2 && (e2 = n2->obj))
                    {
                        long r2_suppkey = e2->R2_SUPPKEY;
                        long v2 = e2->__av;
                        DOUBLE_TYPE l3 = COUNT_mLINEITEM1_L4_1_L2_1.getValueOrDefault(se8.modify(r2_suppkey));
                        (/*if */(l3 > l1) ? agg2 += (v2 != 0 ? 1L : 0L) : 0L);
                      n2 = n2->nxt;
                    }
                  }
                }long l2 = agg2;
                (/*if */(l2 == 0L) ? agg1 += 1L : 0L);
                COUNT.addOrDelOnZero(se5.modify(s_suppkey,s_name,s_address,s_phone,l1),(v1 * ((COUNT_mLINEITEM1_E2_1.getValueOrDefault(se7.modify(s_suppkey)) != 0 ? 1L : 0L) * agg1)));
              n1 = n1->nxt;
            }
          }
        }
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_E2_1.addOrDelOnZero(se9.modify(lineitem_suppkey),-1L) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_L3_1.addOrDelOnZero(se10.modify(lineitem_suppkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_L4_1_E1_1.addOrDelOnZero(se11.modify(lineitem_suppkey),-1L) : (void)0);
        (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mLINEITEM1_L4_1_L2_1.addOrDelOnZero(se12.modify(lineitem_suppkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
        COUNT.clear();
        {  // foreach
          const HashIndex_COUNT_mLINEITEM1_map_0123* i3 = static_cast<HashIndex_COUNT_mLINEITEM1_map_0123*>(COUNT_mLINEITEM1.index[0]);
          HashIndex_COUNT_mLINEITEM1_map_0123::IdxNode* n3; 
          COUNT_mLINEITEM1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long s_suppkey = e3->S_SUPPKEY;
                STRING_TYPE s_name = e3->S_NAME;
                STRING_TYPE s_address = e3->S_ADDRESS;
                STRING_TYPE s_phone = e3->S_PHONE;
                long v3 = e3->__av;
                DOUBLE_TYPE l4 = COUNT_mLINEITEM1_L3_1.getValueOrDefault(se14.modify(s_suppkey));
                long agg3 = 0L;
                long agg4 = 0L;
                {  // foreach
                  const HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0* i4 = static_cast<HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0*>(COUNT_mLINEITEM1_L4_1_E1_1.index[0]);
                  HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0::IdxNode* n4; 
                  COUNT_mLINEITEM1_L4_1_E1_1_entry* e4;
                
                  for (size_t i = 0; i < i4->size_; i++)
                  {
                    n4 = i4->buckets_ + i;
                    while (n4 && (e4 = n4->obj))
                    {
                        long r2_suppkey = e4->R2_SUPPKEY;
                        long v4 = e4->__av;
                        DOUBLE_TYPE l6 = COUNT_mLINEITEM1_L4_1_L2_1.getValueOrDefault(se16.modify(r2_suppkey));
                        (/*if */(l6 > l4) ? agg4 += (v4 != 0 ? 1L : 0L) : 0L);
                      n4 = n4->nxt;
                    }
                  }
                }long l5 = agg4;
                (/*if */(l5 == 0L) ? agg3 += 1L : 0L);
                COUNT.addOrDelOnZero(se13.modify(s_suppkey,s_name,s_address,s_phone,l4),(v3 * ((COUNT_mLINEITEM1_E2_1.getValueOrDefault(se15.modify(s_suppkey)) != 0 ? 1L : 0L) * agg3)));
              n3 = n3->nxt;
            }
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        DOUBLE_TYPE l7 = COUNT_mLINEITEM1_L3_1.getValueOrDefault(se18.modify(supplier_suppkey));
        long agg5 = 0L;
        long agg6 = 0L;
        {  // foreach
          const HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0* i5 = static_cast<HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0*>(COUNT_mLINEITEM1_L4_1_E1_1.index[0]);
          HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0::IdxNode* n5; 
          COUNT_mLINEITEM1_L4_1_E1_1_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long r2_suppkey = e5->R2_SUPPKEY;
                long v5 = e5->__av;
                DOUBLE_TYPE l9 = COUNT_mLINEITEM1_L4_1_L2_1.getValueOrDefault(se19.modify(r2_suppkey));
                (/*if */(l9 > l7) ? agg6 += (v5 != 0 ? 1L : 0L) : 0L);
              n5 = n5->nxt;
            }
          }
        }long l8 = agg6;
        (/*if */(l8 == 0L) ? agg5 += 1L : 0L);
        COUNT.addOrDelOnZero(se17.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone,l7),(agg5 * (COUNT_mLINEITEM1_E2_1.getValueOrDefault(se20.modify(supplier_suppkey)) != 0 ? 1L : 0L)));
        COUNT_mLINEITEM1.addOrDelOnZero(se21.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone),1L);
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        DOUBLE_TYPE l10 = COUNT_mLINEITEM1_L3_1.getValueOrDefault(se23.modify(supplier_suppkey));
        long agg7 = 0L;
        long agg8 = 0L;
        {  // foreach
          const HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0* i6 = static_cast<HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0*>(COUNT_mLINEITEM1_L4_1_E1_1.index[0]);
          HashIndex_COUNT_mLINEITEM1_L4_1_E1_1_map_0::IdxNode* n6; 
          COUNT_mLINEITEM1_L4_1_E1_1_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long r2_suppkey = e6->R2_SUPPKEY;
                long v6 = e6->__av;
                DOUBLE_TYPE l12 = COUNT_mLINEITEM1_L4_1_L2_1.getValueOrDefault(se24.modify(r2_suppkey));
                (/*if */(l12 > l10) ? agg8 += (v6 != 0 ? 1L : 0L) : 0L);
              n6 = n6->nxt;
            }
          }
        }long l11 = agg8;
        (/*if */(l11 == 0L) ? agg7 += 1L : 0L);
        COUNT.addOrDelOnZero(se22.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone,l10),(agg7 * ((COUNT_mLINEITEM1_E2_1.getValueOrDefault(se25.modify(supplier_suppkey)) != 0 ? 1L : 0L) * -1L)));
        COUNT_mLINEITEM1.addOrDelOnZero(se26.modify(supplier_suppkey,supplier_name,supplier_address,supplier_phone),-1L);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNT_mLINEITEM1_E2_1_entry se1;
    COUNT_mLINEITEM1_L3_1_entry se2;
    COUNT_mLINEITEM1_L4_1_E1_1_entry se3;
    COUNT_mLINEITEM1_L4_1_L2_1_entry se4;
    COUNT_entry se5;
    COUNT_mLINEITEM1_L3_1_entry se6;
    COUNT_mLINEITEM1_E2_1_entry se7;
    COUNT_mLINEITEM1_L4_1_L2_1_entry se8;
    COUNT_mLINEITEM1_E2_1_entry se9;
    COUNT_mLINEITEM1_L3_1_entry se10;
    COUNT_mLINEITEM1_L4_1_E1_1_entry se11;
    COUNT_mLINEITEM1_L4_1_L2_1_entry se12;
    COUNT_entry se13;
    COUNT_mLINEITEM1_L3_1_entry se14;
    COUNT_mLINEITEM1_E2_1_entry se15;
    COUNT_mLINEITEM1_L4_1_L2_1_entry se16;
    COUNT_entry se17;
    COUNT_mLINEITEM1_L3_1_entry se18;
    COUNT_mLINEITEM1_L4_1_L2_1_entry se19;
    COUNT_mLINEITEM1_E2_1_entry se20;
    COUNT_mLINEITEM1_entry se21;
    COUNT_entry se22;
    COUNT_mLINEITEM1_L3_1_entry se23;
    COUNT_mLINEITEM1_L4_1_L2_1_entry se24;
    COUNT_mLINEITEM1_E2_1_entry se25;
    COUNT_mLINEITEM1_entry se26;
  
    /* Data structures used for storing materialized views */
    COUNT_mLINEITEM1_map COUNT_mLINEITEM1;
    COUNT_mLINEITEM1_E2_1_map COUNT_mLINEITEM1_E2_1;
    COUNT_mLINEITEM1_L3_1_map COUNT_mLINEITEM1_L3_1;
    COUNT_mLINEITEM1_L4_1_E1_1_map COUNT_mLINEITEM1_L4_1_E1_1;
    COUNT_mLINEITEM1_L4_1_L2_1_map COUNT_mLINEITEM1_L4_1_L2_1;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
  
  };

}
