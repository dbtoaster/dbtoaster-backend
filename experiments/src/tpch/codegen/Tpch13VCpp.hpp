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
    data_t(): tlq_t() {
      
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
      {  //++tN;
        long l1 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se2.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se3.modify(orders_custkey)));
        CUSTDIST.addOrDelOnZero(se1.modify(l1),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se4.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se5.modify(orders_custkey))) != 0 ? 1L : 0L) * -1L));
        long l2 = (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se6.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se7.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? 1L : 0L)));
        CUSTDIST.addOrDelOnZero(se1.modify(l2),((CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se8.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se9.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? 1L : 0L))) != 0 ? 1L : 0L));
        (/*if */(0L == Upreg_match(preg1,orders_comment)) ? CUSTDIST_mCUSTOMER1_L1_1.addOrDelOnZero(se10.modify(orders_custkey),1L) : (void)0);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        long l3 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se12.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se13.modify(orders_custkey)));
        CUSTDIST.addOrDelOnZero(se11.modify(l3),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se14.modify(orders_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se15.modify(orders_custkey))) != 0 ? 1L : 0L) * -1L));
        long l4 = (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se16.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se17.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? -1L : 0L)));
        CUSTDIST.addOrDelOnZero(se11.modify(l4),((CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se18.modify(orders_custkey)) * (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se19.modify(orders_custkey)) + (/*if */(0L == Upreg_match(preg1,orders_comment)) ? -1L : 0L))) != 0 ? 1L : 0L));
        (/*if */(0L == Upreg_match(preg1,orders_comment)) ? CUSTDIST_mCUSTOMER1_L1_1.addOrDelOnZero(se20.modify(orders_custkey),-1L) : (void)0);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        long l5 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se22.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se23.modify(customer_custkey)));
        CUSTDIST.addOrDelOnZero(se21.modify(l5),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se24.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se25.modify(customer_custkey))) != 0 ? 1L : 0L) * -1L));
        long l6 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se26.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se27.modify(customer_custkey)) + 1L));
        CUSTDIST.addOrDelOnZero(se21.modify(l6),((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se28.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se29.modify(customer_custkey)) + 1L)) != 0 ? 1L : 0L));
        CUSTDIST_mCUSTOMER1_L1_2.addOrDelOnZero(se30.modify(customer_custkey),1L);
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        long l7 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se32.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se33.modify(customer_custkey)));
        CUSTDIST.addOrDelOnZero(se31.modify(l7),(((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se34.modify(customer_custkey)) * CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se35.modify(customer_custkey))) != 0 ? 1L : 0L) * -1L));
        long l8 = (CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se36.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se37.modify(customer_custkey)) + -1L));
        CUSTDIST.addOrDelOnZero(se31.modify(l8),((CUSTDIST_mCUSTOMER1_L1_1.getValueOrDefault(se38.modify(customer_custkey)) * (CUSTDIST_mCUSTOMER1_L1_2.getValueOrDefault(se39.modify(customer_custkey)) + -1L)) != 0 ? 1L : 0L));
        CUSTDIST_mCUSTOMER1_L1_2.addOrDelOnZero(se40.modify(customer_custkey),-1L);
      }
    }
    void on_system_ready_event() {
      {  //
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    CUSTDIST_entry se1;
    CUSTDIST_mCUSTOMER1_L1_1_entry se2;
    CUSTDIST_mCUSTOMER1_L1_2_entry se3;
    CUSTDIST_mCUSTOMER1_L1_1_entry se4;
    CUSTDIST_mCUSTOMER1_L1_2_entry se5;
    CUSTDIST_mCUSTOMER1_L1_2_entry se6;
    CUSTDIST_mCUSTOMER1_L1_1_entry se7;
    CUSTDIST_mCUSTOMER1_L1_2_entry se8;
    CUSTDIST_mCUSTOMER1_L1_1_entry se9;
    CUSTDIST_mCUSTOMER1_L1_1_entry se10;
    CUSTDIST_entry se11;
    CUSTDIST_mCUSTOMER1_L1_1_entry se12;
    CUSTDIST_mCUSTOMER1_L1_2_entry se13;
    CUSTDIST_mCUSTOMER1_L1_1_entry se14;
    CUSTDIST_mCUSTOMER1_L1_2_entry se15;
    CUSTDIST_mCUSTOMER1_L1_2_entry se16;
    CUSTDIST_mCUSTOMER1_L1_1_entry se17;
    CUSTDIST_mCUSTOMER1_L1_2_entry se18;
    CUSTDIST_mCUSTOMER1_L1_1_entry se19;
    CUSTDIST_mCUSTOMER1_L1_1_entry se20;
    CUSTDIST_entry se21;
    CUSTDIST_mCUSTOMER1_L1_1_entry se22;
    CUSTDIST_mCUSTOMER1_L1_2_entry se23;
    CUSTDIST_mCUSTOMER1_L1_1_entry se24;
    CUSTDIST_mCUSTOMER1_L1_2_entry se25;
    CUSTDIST_mCUSTOMER1_L1_1_entry se26;
    CUSTDIST_mCUSTOMER1_L1_2_entry se27;
    CUSTDIST_mCUSTOMER1_L1_1_entry se28;
    CUSTDIST_mCUSTOMER1_L1_2_entry se29;
    CUSTDIST_mCUSTOMER1_L1_2_entry se30;
    CUSTDIST_entry se31;
    CUSTDIST_mCUSTOMER1_L1_1_entry se32;
    CUSTDIST_mCUSTOMER1_L1_2_entry se33;
    CUSTDIST_mCUSTOMER1_L1_1_entry se34;
    CUSTDIST_mCUSTOMER1_L1_2_entry se35;
    CUSTDIST_mCUSTOMER1_L1_1_entry se36;
    CUSTDIST_mCUSTOMER1_L1_2_entry se37;
    CUSTDIST_mCUSTOMER1_L1_1_entry se38;
    CUSTDIST_mCUSTOMER1_L1_2_entry se39;
    CUSTDIST_mCUSTOMER1_L1_2_entry se40;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    CUSTDIST_mCUSTOMER1_L1_1_map CUSTDIST_mCUSTOMER1_L1_1;
    CUSTDIST_mCUSTOMER1_L1_2_map CUSTDIST_mCUSTOMER1_L1_2;
    
    
  
  };

}
