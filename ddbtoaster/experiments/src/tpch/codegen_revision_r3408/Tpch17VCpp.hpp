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
  struct AVG_YEARLYLINEITEM1_L1_1_L1_1_entry {
    long AVG_YEARLYLINEITEMLINEITEM_PARTKEY; long __av; 
    explicit AVG_YEARLYLINEITEM1_L1_1_L1_1_entry() { /*AVG_YEARLYLINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit AVG_YEARLYLINEITEM1_L1_1_L1_1_entry(const long c0, const long c1) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry(const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& other) : AVG_YEARLYLINEITEMLINEITEM_PARTKEY( other.AVG_YEARLYLINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& modify(const long c0) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_L1_1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& x, const AVG_YEARLYLINEITEM1_L1_1_L1_1_entry& y) {
      return x.AVG_YEARLYLINEITEMLINEITEM_PARTKEY == y.AVG_YEARLYLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_L1_1_L1_1_entry,long,
    HashIndex<AVG_YEARLYLINEITEM1_L1_1_L1_1_entry,long,AVG_YEARLYLINEITEM1_L1_1_L1_1_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM1_L1_1_L1_1_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_L1_1_L1_1_entry,long,AVG_YEARLYLINEITEM1_L1_1_L1_1_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_L1_1_L1_1_map_0;
  
  struct AVG_YEARLYLINEITEM1_L1_2_entry {
    long AVG_YEARLYLINEITEMLINEITEM_PARTKEY; DOUBLE_TYPE __av; 
    explicit AVG_YEARLYLINEITEM1_L1_2_entry() { /*AVG_YEARLYLINEITEMLINEITEM_PARTKEY = 0L; __av = 0.0; */ }
    explicit AVG_YEARLYLINEITEM1_L1_2_entry(const long c0, const DOUBLE_TYPE c1) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM1_L1_2_entry(const AVG_YEARLYLINEITEM1_L1_2_entry& other) : AVG_YEARLYLINEITEMLINEITEM_PARTKEY( other.AVG_YEARLYLINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM1_L1_2_entry& modify(const long c0) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM1_L1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM1_L1_2_entry& x, const AVG_YEARLYLINEITEM1_L1_2_entry& y) {
      return x.AVG_YEARLYLINEITEMLINEITEM_PARTKEY == y.AVG_YEARLYLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM1_L1_2_entry,DOUBLE_TYPE,
    HashIndex<AVG_YEARLYLINEITEM1_L1_2_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_L1_2_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM1_L1_2_map;
  typedef HashIndex<AVG_YEARLYLINEITEM1_L1_2_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM1_L1_2_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM1_L1_2_map_0;
  
  struct AVG_YEARLYLINEITEM2_entry {
    long AVG_YEARLYLINEITEMLINEITEM_PARTKEY; long __av; 
    explicit AVG_YEARLYLINEITEM2_entry() { /*AVG_YEARLYLINEITEMLINEITEM_PARTKEY = 0L; __av = 0L; */ }
    explicit AVG_YEARLYLINEITEM2_entry(const long c0, const long c1) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0; __av = c1; }
    AVG_YEARLYLINEITEM2_entry(const AVG_YEARLYLINEITEM2_entry& other) : AVG_YEARLYLINEITEMLINEITEM_PARTKEY( other.AVG_YEARLYLINEITEMLINEITEM_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM2_entry& modify(const long c0) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM2_entry& x, const AVG_YEARLYLINEITEM2_entry& y) {
      return x.AVG_YEARLYLINEITEMLINEITEM_PARTKEY == y.AVG_YEARLYLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM2_entry,long,
    HashIndex<AVG_YEARLYLINEITEM2_entry,long,AVG_YEARLYLINEITEM2_mapkey0_idxfn,true>
  > AVG_YEARLYLINEITEM2_map;
  typedef HashIndex<AVG_YEARLYLINEITEM2_entry,long,AVG_YEARLYLINEITEM2_mapkey0_idxfn,true> HashIndex_AVG_YEARLYLINEITEM2_map_0;
  
  struct AVG_YEARLYLINEITEM5_entry {
    long AVG_YEARLYLINEITEMLINEITEM_PARTKEY; DOUBLE_TYPE L_QUANTITY; DOUBLE_TYPE __av; 
    explicit AVG_YEARLYLINEITEM5_entry() { /*AVG_YEARLYLINEITEMLINEITEM_PARTKEY = 0L; L_QUANTITY = 0.0; __av = 0.0; */ }
    explicit AVG_YEARLYLINEITEM5_entry(const long c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0; L_QUANTITY = c1; __av = c2; }
    AVG_YEARLYLINEITEM5_entry(const AVG_YEARLYLINEITEM5_entry& other) : AVG_YEARLYLINEITEMLINEITEM_PARTKEY( other.AVG_YEARLYLINEITEMLINEITEM_PARTKEY ), L_QUANTITY( other.L_QUANTITY ), __av( other.__av ) {}
    FORCE_INLINE AVG_YEARLYLINEITEM5_entry& modify(const long c0, const DOUBLE_TYPE c1) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0; L_QUANTITY = c1;  return *this; }
    FORCE_INLINE AVG_YEARLYLINEITEM5_entry& modify0(const long c0) { AVG_YEARLYLINEITEMLINEITEM_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, L_QUANTITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AVG_YEARLYLINEITEM5_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      hash_combine(h, e.L_QUANTITY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM5_entry& x, const AVG_YEARLYLINEITEM5_entry& y) {
      return x.AVG_YEARLYLINEITEMLINEITEM_PARTKEY == y.AVG_YEARLYLINEITEMLINEITEM_PARTKEY && x.L_QUANTITY == y.L_QUANTITY;
    }
  };
  
  struct AVG_YEARLYLINEITEM5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AVG_YEARLYLINEITEM5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AVG_YEARLYLINEITEMLINEITEM_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const AVG_YEARLYLINEITEM5_entry& x, const AVG_YEARLYLINEITEM5_entry& y) {
      return x.AVG_YEARLYLINEITEMLINEITEM_PARTKEY == y.AVG_YEARLYLINEITEMLINEITEM_PARTKEY;
    }
  };
  
  typedef MultiHashMap<AVG_YEARLYLINEITEM5_entry,DOUBLE_TYPE,
    HashIndex<AVG_YEARLYLINEITEM5_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_mapkey01_idxfn,true>,
    HashIndex<AVG_YEARLYLINEITEM5_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_mapkey0_idxfn,false>
  > AVG_YEARLYLINEITEM5_map;
  typedef HashIndex<AVG_YEARLYLINEITEM5_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_mapkey01_idxfn,true> HashIndex_AVG_YEARLYLINEITEM5_map_01;
  typedef HashIndex<AVG_YEARLYLINEITEM5_entry,DOUBLE_TYPE,AVG_YEARLYLINEITEM5_mapkey0_idxfn,false> HashIndex_AVG_YEARLYLINEITEM5_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0), AVG_YEARLY(0.0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const DOUBLE_TYPE _AVG_YEARLY = get_AVG_YEARLY();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AVG_YEARLY), _AVG_YEARLY, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const DOUBLE_TYPE get_AVG_YEARLY() const {
      return AVG_YEARLY;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    DOUBLE_TYPE AVG_YEARLY;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = STRING_TYPE("MED BOX");
      c1 = STRING_TYPE("Brand#23");
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        DOUBLE_TYPE agg1 = 0.0;
        DOUBLE_TYPE agg2 = 0.0;
        long l2 = (AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se4.modify(lineitem_partkey)) + 1L);
        (/*if */(0L != l2) ? agg2 += Udiv(Ulistmax(1L, l2)) : 0.0);
        DOUBLE_TYPE l1 = ((AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se3.modify(lineitem_partkey)) + lineitem_quantity) * (agg2 * 0.2));
        { //slice 
          const HashIndex_AVG_YEARLYLINEITEM5_map_0* i1 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_map_0*>(AVG_YEARLYLINEITEM5.index[1]);
          const HASH_RES_t h1 = AVG_YEARLYLINEITEM5_mapkey0_idxfn::hash(se5.modify0(lineitem_partkey));
          HashIndex_AVG_YEARLYLINEITEM5_map_0::IdxNode* n1 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_map_0::IdxNode*>(i1->slice(se5, h1));
          AVG_YEARLYLINEITEM5_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              DOUBLE_TYPE l_quantity = e1->L_QUANTITY;
              DOUBLE_TYPE v1 = e1->__av;
              (/*if */(l1 > l_quantity) ? agg1 += v1 : 0.0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  AVG_YEARLYLINEITEM5_mapkey0_idxfn::equals(se5, *e1)); 
          }
        }DOUBLE_TYPE agg3 = 0.0;
        DOUBLE_TYPE agg4 = 0.0;
        long l4 = AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se7.modify(lineitem_partkey));
        (/*if */(0L != l4) ? agg4 += Udiv(Ulistmax(1L, l4)) : 0.0);
        DOUBLE_TYPE l3 = (AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se6.modify(lineitem_partkey)) * (agg4 * 0.2));
        { //slice 
          const HashIndex_AVG_YEARLYLINEITEM5_map_0* i2 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_map_0*>(AVG_YEARLYLINEITEM5.index[1]);
          const HASH_RES_t h2 = AVG_YEARLYLINEITEM5_mapkey0_idxfn::hash(se8.modify0(lineitem_partkey));
          HashIndex_AVG_YEARLYLINEITEM5_map_0::IdxNode* n2 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_map_0::IdxNode*>(i2->slice(se8, h2));
          AVG_YEARLYLINEITEM5_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              DOUBLE_TYPE l_quantity = e2->L_QUANTITY;
              DOUBLE_TYPE v2 = e2->__av;
              (/*if */(l3 > l_quantity) ? agg3 += v2 : 0.0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  AVG_YEARLYLINEITEM5_mapkey0_idxfn::equals(se8, *e2)); 
          }
        }long agg5 = 0L;
        DOUBLE_TYPE agg6 = 0.0;
        long l6 = (AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se10.modify(lineitem_partkey)) + 1L);
        (/*if */(0L != l6) ? agg6 += Udiv(Ulistmax(1L, l6)) : 0.0);
        DOUBLE_TYPE l5 = ((AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se9.modify(lineitem_partkey)) + lineitem_quantity) * (agg6 * 0.2));
        (/*if */(l5 > lineitem_quantity) ? agg5 += AVG_YEARLYLINEITEM2.getValueOrDefault(se11.modify(lineitem_partkey)) : 0L);
        AVG_YEARLY += (((AVG_YEARLYLINEITEM2.getValueOrDefault(se2.modify(lineitem_partkey)) * (agg1 + (agg3 * -1L))) + (agg5 * lineitem_extendedprice)) * 0.142857142857);
        AVG_YEARLYLINEITEM1_L1_1_L1_1.addOrDelOnZero(se12.modify(lineitem_partkey),1L);
        AVG_YEARLYLINEITEM1_L1_2.addOrDelOnZero(se13.modify(lineitem_partkey),lineitem_quantity);
        AVG_YEARLYLINEITEM5.addOrDelOnZero(se14.modify(lineitem_partkey,lineitem_quantity),lineitem_extendedprice);
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        DOUBLE_TYPE agg7 = 0.0;
        DOUBLE_TYPE agg8 = 0.0;
        long l8 = AVG_YEARLYLINEITEM1_L1_1_L1_1.getValueOrDefault(se17.modify(part_partkey));
        (/*if */(0L != l8) ? agg8 += Udiv(Ulistmax(1L, l8)) : 0.0);
        DOUBLE_TYPE l7 = (AVG_YEARLYLINEITEM1_L1_2.getValueOrDefault(se16.modify(part_partkey)) * (agg8 * 0.2));
        { //slice 
          const HashIndex_AVG_YEARLYLINEITEM5_map_0* i3 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_map_0*>(AVG_YEARLYLINEITEM5.index[1]);
          const HASH_RES_t h3 = AVG_YEARLYLINEITEM5_mapkey0_idxfn::hash(se18.modify0(part_partkey));
          HashIndex_AVG_YEARLYLINEITEM5_map_0::IdxNode* n3 = static_cast<HashIndex_AVG_YEARLYLINEITEM5_map_0::IdxNode*>(i3->slice(se18, h3));
          AVG_YEARLYLINEITEM5_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              DOUBLE_TYPE l_quantity = e3->L_QUANTITY;
              DOUBLE_TYPE v3 = e3->__av;
              (/*if */(l7 > l_quantity) ? agg7 += v3 : 0.0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  AVG_YEARLYLINEITEM5_mapkey0_idxfn::equals(se18, *e3)); 
          }
        }(/*if */(part_brand == c1 && part_container == c2) ? AVG_YEARLY += (agg7 * 0.142857142857) : 0L);
        (/*if */(part_brand == c1 && part_container == c2) ? AVG_YEARLYLINEITEM2.addOrDelOnZero(se19.modify(part_partkey),1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        AVG_YEARLY = 0.0;
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    AVG_YEARLYLINEITEM2_entry se2;
    AVG_YEARLYLINEITEM1_L1_2_entry se3;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se4;
    AVG_YEARLYLINEITEM5_entry se5;
    AVG_YEARLYLINEITEM1_L1_2_entry se6;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se7;
    AVG_YEARLYLINEITEM5_entry se8;
    AVG_YEARLYLINEITEM1_L1_2_entry se9;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se10;
    AVG_YEARLYLINEITEM2_entry se11;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se12;
    AVG_YEARLYLINEITEM1_L1_2_entry se13;
    AVG_YEARLYLINEITEM5_entry se14;
    AVG_YEARLYLINEITEM1_L1_2_entry se16;
    AVG_YEARLYLINEITEM1_L1_1_L1_1_entry se17;
    AVG_YEARLYLINEITEM5_entry se18;
    AVG_YEARLYLINEITEM2_entry se19;
  
    /* Data structures used for storing materialized views */
    AVG_YEARLYLINEITEM1_L1_1_L1_1_map AVG_YEARLYLINEITEM1_L1_1_L1_1;
    AVG_YEARLYLINEITEM1_L1_2_map AVG_YEARLYLINEITEM1_L1_2;
    AVG_YEARLYLINEITEM2_map AVG_YEARLYLINEITEM2;
    AVG_YEARLYLINEITEM5_map AVG_YEARLYLINEITEM5;
    
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
  
  };

}
