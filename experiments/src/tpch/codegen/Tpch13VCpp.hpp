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
  struct CUSTDIST_entry {
    long C_ORDERS_C_COUNT; long __av; 
    explicit CUSTDIST_entry() { /*C_ORDERS_C_COUNT = 0L; __av = 0L; */ }
    explicit CUSTDIST_entry(const long c0, const long c1) { C_ORDERS_C_COUNT = c0; __av = c1; }
    CUSTDIST_entry(const CUSTDIST_entry& other) : C_ORDERS_C_COUNT( other.C_ORDERS_C_COUNT ), __av( other.__av ) {}
    FORCE_INLINE CUSTDIST_entry& modify(const long c0) { C_ORDERS_C_COUNT = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDIST_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDIST_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_COUNT);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDIST_entry& x, const CUSTDIST_entry& y) {
      return x.C_ORDERS_C_COUNT == y.C_ORDERS_C_COUNT;
    }
  };
  
  typedef MultiHashMap<CUSTDIST_entry,long,
    HashIndex<CUSTDIST_entry,long,CUSTDIST_mapkey0_idxfn,true>
  > CUSTDIST_map;
  typedef HashIndex<CUSTDIST_entry,long,CUSTDIST_mapkey0_idxfn,true> HashIndex_CUSTDIST_map_0;
  
  struct CUSTDIST_mCUSTOMER_IVC1_E1_1_entry {
    long C_ORDERS_C_CUSTKEY; long __av; 
    explicit CUSTDIST_mCUSTOMER_IVC1_E1_1_entry() { /*C_ORDERS_C_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDIST_mCUSTOMER_IVC1_E1_1_entry(const long c0, const long c1) { C_ORDERS_C_CUSTKEY = c0; __av = c1; }
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry(const CUSTDIST_mCUSTOMER_IVC1_E1_1_entry& other) : C_ORDERS_C_CUSTKEY( other.C_ORDERS_C_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDIST_mCUSTOMER_IVC1_E1_1_entry& modify(const long c0) { C_ORDERS_C_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_ORDERS_C_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDIST_mCUSTOMER_IVC1_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDIST_mCUSTOMER_IVC1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_ORDERS_C_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDIST_mCUSTOMER_IVC1_E1_1_entry& x, const CUSTDIST_mCUSTOMER_IVC1_E1_1_entry& y) {
      return x.C_ORDERS_C_CUSTKEY == y.C_ORDERS_C_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDIST_mCUSTOMER_IVC1_E1_1_entry,long,
    HashIndex<CUSTDIST_mCUSTOMER_IVC1_E1_1_entry,long,CUSTDIST_mCUSTOMER_IVC1_E1_1_mapkey0_idxfn,true>
  > CUSTDIST_mCUSTOMER_IVC1_E1_1_map;
  typedef HashIndex<CUSTDIST_mCUSTOMER_IVC1_E1_1_entry,long,CUSTDIST_mCUSTOMER_IVC1_E1_1_mapkey0_idxfn,true> HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0;
  
  struct CUSTDIST_mCUSTOMER1_L1_1_entry {
    long CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY; long __av; 
    explicit CUSTDIST_mCUSTOMER1_L1_1_entry() { /*CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDIST_mCUSTOMER1_L1_1_entry(const long c0, const long c1) { CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY = c0; __av = c1; }
    CUSTDIST_mCUSTOMER1_L1_1_entry(const CUSTDIST_mCUSTOMER1_L1_1_entry& other) : CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY( other.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDIST_mCUSTOMER1_L1_1_entry& modify(const long c0) { CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDIST_mCUSTOMER1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDIST_mCUSTOMER1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDIST_mCUSTOMER1_L1_1_entry& x, const CUSTDIST_mCUSTOMER1_L1_1_entry& y) {
      return x.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY == y.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDIST_mCUSTOMER1_L1_1_entry,long,
    HashIndex<CUSTDIST_mCUSTOMER1_L1_1_entry,long,CUSTDIST_mCUSTOMER1_L1_1_mapkey0_idxfn,true>
  > CUSTDIST_mCUSTOMER1_L1_1_map;
  typedef HashIndex<CUSTDIST_mCUSTOMER1_L1_1_entry,long,CUSTDIST_mCUSTOMER1_L1_1_mapkey0_idxfn,true> HashIndex_CUSTDIST_mCUSTOMER1_L1_1_map_0;
  
  struct CUSTDIST_mCUSTOMER1_L1_2_entry {
    long CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY; long __av; 
    explicit CUSTDIST_mCUSTOMER1_L1_2_entry() { /*CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit CUSTDIST_mCUSTOMER1_L1_2_entry(const long c0, const long c1) { CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY = c0; __av = c1; }
    CUSTDIST_mCUSTOMER1_L1_2_entry(const CUSTDIST_mCUSTOMER1_L1_2_entry& other) : CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY( other.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE CUSTDIST_mCUSTOMER1_L1_2_entry& modify(const long c0) { CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTDIST_mCUSTOMER1_L1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const CUSTDIST_mCUSTOMER1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTDIST_mCUSTOMER1_L1_2_entry& x, const CUSTDIST_mCUSTOMER1_L1_2_entry& y) {
      return x.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY == y.CUSTDIST_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<CUSTDIST_mCUSTOMER1_L1_2_entry,long,
    HashIndex<CUSTDIST_mCUSTOMER1_L1_2_entry,long,CUSTDIST_mCUSTOMER1_L1_2_mapkey0_idxfn,true>
  > CUSTDIST_mCUSTOMER1_L1_2_map;
  typedef HashIndex<CUSTDIST_mCUSTOMER1_L1_2_entry,long,CUSTDIST_mCUSTOMER1_L1_2_mapkey0_idxfn,true> HashIndex_CUSTDIST_mCUSTOMER1_L1_2_map_0;
  
  struct tuple2_L_L {
    long _1; long __av;
    explicit tuple2_L_L() { }
    explicit tuple2_L_L(const long c1, long c__av=0L) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_L_L &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_L_L& modify(const long c0, long c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_L_L &x, const tuple2_L_L &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_L_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      return h;
    }
  };
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const CUSTDIST_map& _CUSTDIST = get_CUSTDIST();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(CUSTDIST), _CUSTDIST, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const CUSTDIST_map& get_CUSTDIST() const {
      return CUSTDIST;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    CUSTDIST_map CUSTDIST;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), agg2(16U), agg4(16U), agg1(16U), agg3(16U) {
      
      /* regex_t init */
      if(regcomp(&preg1, "^.*special.*requests.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^.*special.*requests.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg1);
    }
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg1.clear();
        
        {  // foreach
          const HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0* i1 = static_cast<HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0*>(CUSTDIST_mCUSTOMER_IVC1_E1_1.index[0]);
          HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0::IdxNode* n1; 
          CUSTDIST_mCUSTOMER_IVC1_E1_1_entry* e1;
        
          for (size_t i = 0; i < i1->size_; i++)
          {
            n1 = i1->buckets_ + i;
            while (n1 && (e1 = n1->obj))
            {
                long c_orders_c_custkey = e1->C_ORDERS_C_CUSTKEY;
                long v1 = e1->__av;
                long l1 = CUSTDIST_mCUSTOMER_IVC1_E1_1.getValueOrDefault(se2.modify(c_orders_c_custkey));
                agg1.addOrDelOnZero(st1.modify(l1,(v1 != 0 ? 1L : 0L)), (v1 != 0 ? 1L : 0L));
              n1 = n1->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i2 = static_cast<HashIndex<tuple2_L_L, long>*>(agg1.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n2; 
          tuple2_L_L* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
              long c_orders_c_count = e2->_1;  
              long v2 = e2->__av; 
            if (CUSTDIST.getValueOrDefault(se1.modify(c_orders_c_count))==0) CUSTDIST.setOrDelOnZero(se1, v2);      
              n2 = n2->nxt;
            }
          }
        }long l2 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se3.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se4.modify(orders_custkey)));
        CUSTDIST.addOrDelOnZero(se1.modify(l2),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se5.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se6.modify(orders_custkey))) != 0 ? 1L : 0L) * -1L));
        long l3 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se7.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se8.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? 1L : 0L)));
        CUSTDIST.addOrDelOnZero(se1.modify(l3),((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se9.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se10.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? 1L : 0L))) != 0 ? 1L : 0L));
        (/*if */(0L == Upreg_match(preg1,orders_comment)) ? CUSTDIST_mCUSTOMER_IVC1_E1_1.addOrDelOnZero(se11.modify(orders_custkey),CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se12.modify(orders_custkey))) : (void)0);
        (/*if */(0L == Upreg_match(preg1,orders_comment)) ? CUSTDIST_mCUSTOMER1_L1_2.addOrDelOnZero(se13.modify(orders_custkey),1L) : (void)0);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg2.clear();
        
        {  // foreach
          const HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0* i3 = static_cast<HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0*>(CUSTDIST_mCUSTOMER_IVC1_E1_1.index[0]);
          HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0::IdxNode* n3; 
          CUSTDIST_mCUSTOMER_IVC1_E1_1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long c_orders_c_custkey = e3->C_ORDERS_C_CUSTKEY;
                long v3 = e3->__av;
                long l4 = CUSTDIST_mCUSTOMER_IVC1_E1_1.getValueOrDefault(se15.modify(c_orders_c_custkey));
                agg2.addOrDelOnZero(st2.modify(l4,(v3 != 0 ? 1L : 0L)), (v3 != 0 ? 1L : 0L));
              n3 = n3->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i4 = static_cast<HashIndex<tuple2_L_L, long>*>(agg2.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n4; 
          tuple2_L_L* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
              long c_orders_c_count = e4->_1;  
              long v4 = e4->__av; 
            if (CUSTDIST.getValueOrDefault(se14.modify(c_orders_c_count))==0) CUSTDIST.setOrDelOnZero(se14, v4);      
              n4 = n4->nxt;
            }
          }
        }long l5 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se16.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se17.modify(orders_custkey)));
        CUSTDIST.addOrDelOnZero(se14.modify(l5),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se18.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se19.modify(orders_custkey))) != 0 ? 1L : 0L) * -1L));
        long l6 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se20.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se21.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? -1L : 0L)));
        CUSTDIST.addOrDelOnZero(se14.modify(l6),((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se22.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se23.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? -1L : 0L))) != 0 ? 1L : 0L));
        (/*if */(0L == Upreg_match(preg1,orders_comment)) ? CUSTDIST_mCUSTOMER_IVC1_E1_1.addOrDelOnZero(se24.modify(orders_custkey),(CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se25.modify(orders_custkey)) * -1L)) : (void)0);
        (/*if */(0L == Upreg_match(preg1,orders_comment)) ? CUSTDIST_mCUSTOMER1_L1_2.addOrDelOnZero(se26.modify(orders_custkey),-1L) : (void)0);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg3.clear();
        
        {  // foreach
          const HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0* i5 = static_cast<HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0*>(CUSTDIST_mCUSTOMER_IVC1_E1_1.index[0]);
          HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0::IdxNode* n5; 
          CUSTDIST_mCUSTOMER_IVC1_E1_1_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long c_orders_c_custkey = e5->C_ORDERS_C_CUSTKEY;
                long v5 = e5->__av;
                long l7 = CUSTDIST_mCUSTOMER_IVC1_E1_1.getValueOrDefault(se28.modify(c_orders_c_custkey));
                agg3.addOrDelOnZero(st3.modify(l7,(v5 != 0 ? 1L : 0L)), (v5 != 0 ? 1L : 0L));
              n5 = n5->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i6 = static_cast<HashIndex<tuple2_L_L, long>*>(agg3.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n6; 
          tuple2_L_L* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
              long c_orders_c_count = e6->_1;  
              long v6 = e6->__av; 
            if (CUSTDIST.getValueOrDefault(se27.modify(c_orders_c_count))==0) CUSTDIST.setOrDelOnZero(se27, v6);      
              n6 = n6->nxt;
            }
          }
        }long l8 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se29.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se30.modify(customer_custkey)));
        CUSTDIST.addOrDelOnZero(se27.modify(l8),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se31.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se32.modify(customer_custkey))) != 0 ? 1L : 0L) * -1L));
        long l9 = (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se33.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se34.modify(customer_custkey)) + 1L));
        CUSTDIST.addOrDelOnZero(se27.modify(l9),((CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se35.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se36.modify(customer_custkey)) + 1L)) != 0 ? 1L : 0L));
        CUSTDIST_mCUSTOMER_IVC1_E1_1.addOrDelOnZero(se37.modify(customer_custkey),CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se38.modify(customer_custkey)));
        CUSTDIST_mCUSTOMER1_L1_1.addOrDelOnZero(se39.modify(customer_custkey),1L);
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg4.clear();
        
        {  // foreach
          const HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0* i7 = static_cast<HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0*>(CUSTDIST_mCUSTOMER_IVC1_E1_1.index[0]);
          HashIndex_CUSTDIST_mCUSTOMER_IVC1_E1_1_map_0::IdxNode* n7; 
          CUSTDIST_mCUSTOMER_IVC1_E1_1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long c_orders_c_custkey = e7->C_ORDERS_C_CUSTKEY;
                long v7 = e7->__av;
                long l10 = CUSTDIST_mCUSTOMER_IVC1_E1_1.getValueOrDefault(se41.modify(c_orders_c_custkey));
                agg4.addOrDelOnZero(st4.modify(l10,(v7 != 0 ? 1L : 0L)), (v7 != 0 ? 1L : 0L));
              n7 = n7->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i8 = static_cast<HashIndex<tuple2_L_L, long>*>(agg4.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n8; 
          tuple2_L_L* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
              long c_orders_c_count = e8->_1;  
              long v8 = e8->__av; 
            if (CUSTDIST.getValueOrDefault(se40.modify(c_orders_c_count))==0) CUSTDIST.setOrDelOnZero(se40, v8);      
              n8 = n8->nxt;
            }
          }
        }long l11 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se42.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se43.modify(customer_custkey)));
        CUSTDIST.addOrDelOnZero(se40.modify(l11),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se44.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se45.modify(customer_custkey))) != 0 ? 1L : 0L) * -1L));
        long l12 = (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se46.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se47.modify(customer_custkey)) + -1L));
        CUSTDIST.addOrDelOnZero(se40.modify(l12),((CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se48.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se49.modify(customer_custkey)) + -1L)) != 0 ? 1L : 0L));
        CUSTDIST_mCUSTOMER_IVC1_E1_1.addOrDelOnZero(se50.modify(customer_custkey),(CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se51.modify(customer_custkey)) * -1L));
        CUSTDIST_mCUSTOMER1_L1_1.addOrDelOnZero(se52.modify(customer_custkey),-1L);
      }
    }
    void on_system_ready_event() {
      {  
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    CUSTDIST_entry se1;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se2;
    tuple2_L_L st1;
    CUSTDIST_mCUSTOMER1_L1_1_entry se3;
    CUSTDIST_mCUSTOMER1_L1_2_entry se4;
    CUSTDIST_mCUSTOMER1_L1_1_entry se5;
    CUSTDIST_mCUSTOMER1_L1_2_entry se6;
    CUSTDIST_mCUSTOMER1_L1_1_entry se7;
    CUSTDIST_mCUSTOMER1_L1_2_entry se8;
    CUSTDIST_mCUSTOMER1_L1_1_entry se9;
    CUSTDIST_mCUSTOMER1_L1_2_entry se10;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se11;
    CUSTDIST_mCUSTOMER1_L1_1_entry se12;
    CUSTDIST_mCUSTOMER1_L1_2_entry se13;
    CUSTDIST_entry se14;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se15;
    tuple2_L_L st2;
    CUSTDIST_mCUSTOMER1_L1_1_entry se16;
    CUSTDIST_mCUSTOMER1_L1_2_entry se17;
    CUSTDIST_mCUSTOMER1_L1_1_entry se18;
    CUSTDIST_mCUSTOMER1_L1_2_entry se19;
    CUSTDIST_mCUSTOMER1_L1_1_entry se20;
    CUSTDIST_mCUSTOMER1_L1_2_entry se21;
    CUSTDIST_mCUSTOMER1_L1_1_entry se22;
    CUSTDIST_mCUSTOMER1_L1_2_entry se23;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se24;
    CUSTDIST_mCUSTOMER1_L1_1_entry se25;
    CUSTDIST_mCUSTOMER1_L1_2_entry se26;
    CUSTDIST_entry se27;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se28;
    tuple2_L_L st3;
    CUSTDIST_mCUSTOMER1_L1_1_entry se29;
    CUSTDIST_mCUSTOMER1_L1_2_entry se30;
    CUSTDIST_mCUSTOMER1_L1_1_entry se31;
    CUSTDIST_mCUSTOMER1_L1_2_entry se32;
    CUSTDIST_mCUSTOMER1_L1_2_entry se33;
    CUSTDIST_mCUSTOMER1_L1_1_entry se34;
    CUSTDIST_mCUSTOMER1_L1_2_entry se35;
    CUSTDIST_mCUSTOMER1_L1_1_entry se36;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se37;
    CUSTDIST_mCUSTOMER1_L1_2_entry se38;
    CUSTDIST_mCUSTOMER1_L1_1_entry se39;
    CUSTDIST_entry se40;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se41;
    tuple2_L_L st4;
    CUSTDIST_mCUSTOMER1_L1_1_entry se42;
    CUSTDIST_mCUSTOMER1_L1_2_entry se43;
    CUSTDIST_mCUSTOMER1_L1_1_entry se44;
    CUSTDIST_mCUSTOMER1_L1_2_entry se45;
    CUSTDIST_mCUSTOMER1_L1_2_entry se46;
    CUSTDIST_mCUSTOMER1_L1_1_entry se47;
    CUSTDIST_mCUSTOMER1_L1_2_entry se48;
    CUSTDIST_mCUSTOMER1_L1_1_entry se49;
    CUSTDIST_mCUSTOMER_IVC1_E1_1_entry se50;
    CUSTDIST_mCUSTOMER1_L1_2_entry se51;
    CUSTDIST_mCUSTOMER1_L1_1_entry se52;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    CUSTDIST_mCUSTOMER_IVC1_E1_1_map CUSTDIST_mCUSTOMER_IVC1_E1_1;
    CUSTDIST_mCUSTOMER1_L1_1_map CUSTDIST_mCUSTOMER1_L1_1;
    CUSTDIST_mCUSTOMER1_L1_2_map CUSTDIST_mCUSTOMER1_L1_2;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg2;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg4;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg1;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg3;
    
  
  };

}
