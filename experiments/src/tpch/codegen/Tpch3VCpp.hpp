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
  struct QUERY3_entry {
    long ORDERS_ORDERKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; DOUBLE_TYPE __av; 
    explicit QUERY3_entry() { /*ORDERS_ORDERKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0.0; */ }
    explicit QUERY3_entry(const long c0, const date c1, const long c2, const DOUBLE_TYPE c3) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2; __av = c3; }
    QUERY3_entry(const QUERY3_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_entry& modify(const long c0, const date c1, const long c2) { ORDERS_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_entry& x, const QUERY3_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  typedef MultiHashMap<QUERY3_entry,DOUBLE_TYPE,
    HashIndex<QUERY3_entry,DOUBLE_TYPE,QUERY3_mapkey012_idxfn,true>
  > QUERY3_map;
  typedef HashIndex<QUERY3_entry,DOUBLE_TYPE,QUERY3_mapkey012_idxfn,true> HashIndex_QUERY3_map_012;
  
  struct QUERY3_mLINEITEM2_entry {
    long QUERY3_mLINEITEMLINEITEM_ORDERKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3_mLINEITEM2_entry() { /*QUERY3_mLINEITEMLINEITEM_ORDERKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3_mLINEITEM2_entry(const long c0, const date c1, const long c2, const long c3) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2; __av = c3; }
    QUERY3_mLINEITEM2_entry(const QUERY3_mLINEITEM2_entry& other) : QUERY3_mLINEITEMLINEITEM_ORDERKEY( other.QUERY3_mLINEITEMLINEITEM_ORDERKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mLINEITEM2_entry& modify(const long c0, const date c1, const long c2) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2;  return *this; }
    FORCE_INLINE QUERY3_mLINEITEM2_entry& modify0(const long c0) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mLINEITEM2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM2_entry& x, const QUERY3_mLINEITEM2_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3_mLINEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM2_entry& x, const QUERY3_mLINEITEM2_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mLINEITEM2_entry,long,
    HashIndex<QUERY3_mLINEITEM2_entry,long,QUERY3_mLINEITEM2_mapkey012_idxfn,true>,
    HashIndex<QUERY3_mLINEITEM2_entry,long,QUERY3_mLINEITEM2_mapkey0_idxfn,false>
  > QUERY3_mLINEITEM2_map;
  typedef HashIndex<QUERY3_mLINEITEM2_entry,long,QUERY3_mLINEITEM2_mapkey012_idxfn,true> HashIndex_QUERY3_mLINEITEM2_map_012;
  typedef HashIndex<QUERY3_mLINEITEM2_entry,long,QUERY3_mLINEITEM2_mapkey0_idxfn,false> HashIndex_QUERY3_mLINEITEM2_map_0;
  
  struct QUERY3_mLINEITEM2_mCUSTOMER2_entry {
    long QUERY3_mLINEITEMLINEITEM_ORDERKEY; long QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3_mLINEITEM2_mCUSTOMER2_entry() { /*QUERY3_mLINEITEMLINEITEM_ORDERKEY = 0L; QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3_mLINEITEM2_mCUSTOMER2_entry(const long c0, const long c1, const date c2, const long c3, const long c4) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3_mLINEITEM2_mCUSTOMER2_entry(const QUERY3_mLINEITEM2_mCUSTOMER2_entry& other) : QUERY3_mLINEITEMLINEITEM_ORDERKEY( other.QUERY3_mLINEITEMLINEITEM_ORDERKEY ), QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY( other.QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mLINEITEM2_mCUSTOMER2_entry& modify(const long c0, const long c1, const date c2, const long c3) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    FORCE_INLINE QUERY3_mLINEITEM2_mCUSTOMER2_entry& modify0(const long c0) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE QUERY3_mLINEITEM2_mCUSTOMER2_entry& modify1(const long c1) { QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM2_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM2_mCUSTOMER2_entry& x, const QUERY3_mLINEITEM2_mCUSTOMER2_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY && x.QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM2_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM2_mCUSTOMER2_entry& x, const QUERY3_mLINEITEM2_mCUSTOMER2_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct QUERY3_mLINEITEM2_mCUSTOMER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM2_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM2_mCUSTOMER2_entry& x, const QUERY3_mLINEITEM2_mCUSTOMER2_entry& y) {
      return x.QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mLINEITEM2_mCUSTOMER2_entry,long,
    HashIndex<QUERY3_mLINEITEM2_mCUSTOMER2_entry,long,QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0123_idxfn,true>,
    HashIndex<QUERY3_mLINEITEM2_mCUSTOMER2_entry,long,QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0_idxfn,false>,
    HashIndex<QUERY3_mLINEITEM2_mCUSTOMER2_entry,long,QUERY3_mLINEITEM2_mCUSTOMER2_mapkey1_idxfn,false>
  > QUERY3_mLINEITEM2_mCUSTOMER2_map;
  typedef HashIndex<QUERY3_mLINEITEM2_mCUSTOMER2_entry,long,QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0123_idxfn,true> HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0123;
  typedef HashIndex<QUERY3_mLINEITEM2_mCUSTOMER2_entry,long,QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0_idxfn,false> HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0;
  typedef HashIndex<QUERY3_mLINEITEM2_mCUSTOMER2_entry,long,QUERY3_mLINEITEM2_mCUSTOMER2_mapkey1_idxfn,false> HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1;
  
  struct QUERY3_mORDERS2_entry {
    long QUERY3_mORDERSORDERS_CUSTKEY; long __av; 
    explicit QUERY3_mORDERS2_entry() { /*QUERY3_mORDERSORDERS_CUSTKEY = 0L; __av = 0L; */ }
    explicit QUERY3_mORDERS2_entry(const long c0, const long c1) { QUERY3_mORDERSORDERS_CUSTKEY = c0; __av = c1; }
    QUERY3_mORDERS2_entry(const QUERY3_mORDERS2_entry& other) : QUERY3_mORDERSORDERS_CUSTKEY( other.QUERY3_mORDERSORDERS_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mORDERS2_entry& modify(const long c0) { QUERY3_mORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mORDERS2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mORDERS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mORDERS2_entry& x, const QUERY3_mORDERS2_entry& y) {
      return x.QUERY3_mORDERSORDERS_CUSTKEY == y.QUERY3_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mORDERS2_entry,long,
    HashIndex<QUERY3_mORDERS2_entry,long,QUERY3_mORDERS2_mapkey0_idxfn,true>
  > QUERY3_mORDERS2_map;
  typedef HashIndex<QUERY3_mORDERS2_entry,long,QUERY3_mORDERS2_mapkey0_idxfn,true> HashIndex_QUERY3_mORDERS2_map_0;
  
  struct QUERY3_mORDERS3_entry {
    long QUERY3_mORDERSORDERS_ORDERKEY; DOUBLE_TYPE __av; 
    explicit QUERY3_mORDERS3_entry() { /*QUERY3_mORDERSORDERS_ORDERKEY = 0L; __av = 0.0; */ }
    explicit QUERY3_mORDERS3_entry(const long c0, const DOUBLE_TYPE c1) { QUERY3_mORDERSORDERS_ORDERKEY = c0; __av = c1; }
    QUERY3_mORDERS3_entry(const QUERY3_mORDERS3_entry& other) : QUERY3_mORDERSORDERS_ORDERKEY( other.QUERY3_mORDERSORDERS_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mORDERS3_entry& modify(const long c0) { QUERY3_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mORDERS3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mORDERS3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mORDERS3_entry& x, const QUERY3_mORDERS3_entry& y) {
      return x.QUERY3_mORDERSORDERS_ORDERKEY == y.QUERY3_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mORDERS3_entry,DOUBLE_TYPE,
    HashIndex<QUERY3_mORDERS3_entry,DOUBLE_TYPE,QUERY3_mORDERS3_mapkey0_idxfn,true>
  > QUERY3_mORDERS3_map;
  typedef HashIndex<QUERY3_mORDERS3_entry,DOUBLE_TYPE,QUERY3_mORDERS3_mapkey0_idxfn,true> HashIndex_QUERY3_mORDERS3_map_0;
  
  struct QUERY3_mCUSTOMER2_entry {
    long ORDERS_ORDERKEY; long QUERY3_mCUSTOMERCUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; DOUBLE_TYPE __av; 
    explicit QUERY3_mCUSTOMER2_entry() { /*ORDERS_ORDERKEY = 0L; QUERY3_mCUSTOMERCUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0.0; */ }
    explicit QUERY3_mCUSTOMER2_entry(const long c0, const long c1, const date c2, const long c3, const DOUBLE_TYPE c4) { ORDERS_ORDERKEY = c0; QUERY3_mCUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3_mCUSTOMER2_entry(const QUERY3_mCUSTOMER2_entry& other) : ORDERS_ORDERKEY( other.ORDERS_ORDERKEY ), QUERY3_mCUSTOMERCUSTOMER_CUSTKEY( other.QUERY3_mCUSTOMERCUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mCUSTOMER2_entry& modify(const long c0, const long c1, const date c2, const long c3) { ORDERS_ORDERKEY = c0; QUERY3_mCUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    FORCE_INLINE QUERY3_mCUSTOMER2_entry& modify1(const long c1) { QUERY3_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mCUSTOMER2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ORDERS_ORDERKEY);
      hash_combine(h, e.QUERY3_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mCUSTOMER2_entry& x, const QUERY3_mCUSTOMER2_entry& y) {
      return x.ORDERS_ORDERKEY == y.ORDERS_ORDERKEY && x.QUERY3_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY3_mCUSTOMERCUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3_mCUSTOMER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mCUSTOMER2_entry& x, const QUERY3_mCUSTOMER2_entry& y) {
      return x.QUERY3_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY3_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mCUSTOMER2_entry,DOUBLE_TYPE,
    HashIndex<QUERY3_mCUSTOMER2_entry,DOUBLE_TYPE,QUERY3_mCUSTOMER2_mapkey0123_idxfn,true>,
    HashIndex<QUERY3_mCUSTOMER2_entry,DOUBLE_TYPE,QUERY3_mCUSTOMER2_mapkey1_idxfn,false>
  > QUERY3_mCUSTOMER2_map;
  typedef HashIndex<QUERY3_mCUSTOMER2_entry,DOUBLE_TYPE,QUERY3_mCUSTOMER2_mapkey0123_idxfn,true> HashIndex_QUERY3_mCUSTOMER2_map_0123;
  typedef HashIndex<QUERY3_mCUSTOMER2_entry,DOUBLE_TYPE,QUERY3_mCUSTOMER2_mapkey1_idxfn,false> HashIndex_QUERY3_mCUSTOMER2_map_1;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const QUERY3_map& _QUERY3 = get_QUERY3();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(QUERY3), _QUERY3, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const QUERY3_map& get_QUERY3() const {
      return QUERY3;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    QUERY3_map QUERY3;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c2 = STRING_TYPE("BUILDING");
      c1 = Udate(STRING_TYPE("1995-3-15"));
    }
  
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_QUERY3_mLINEITEM2_map_0* i1 = static_cast<HashIndex_QUERY3_mLINEITEM2_map_0*>(QUERY3_mLINEITEM2.index[1]);
          const HASH_RES_t h1 = QUERY3_mLINEITEM2_mapkey0_idxfn::hash(se2.modify0(lineitem_orderkey));
          HashIndex_QUERY3_mLINEITEM2_map_0::IdxNode* n1 = static_cast<HashIndex_QUERY3_mLINEITEM2_map_0::IdxNode*>(i1->slice(se2, h1));
          QUERY3_mLINEITEM2_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              date orders_orderdate = e1->ORDERS_ORDERDATE;
              long orders_shippriority = e1->ORDERS_SHIPPRIORITY;
              long v1 = e1->__av;
              (/*if */(lineitem_shipdate > c1) ? QUERY3.addOrDelOnZero(se1.modify(lineitem_orderkey,orders_orderdate,orders_shippriority),(v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  QUERY3_mLINEITEM2_mapkey0_idxfn::equals(se2, *e1)); 
          }
        }(/*if */(lineitem_shipdate > c1) ? QUERY3_mORDERS3.addOrDelOnZero(se3.modify(lineitem_orderkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        { //slice 
          const HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0* i2 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0*>(QUERY3_mLINEITEM2_mCUSTOMER2.index[1]);
          const HASH_RES_t h2 = QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0_idxfn::hash(se5.modify0(lineitem_orderkey));
          HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0::IdxNode* n2 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0::IdxNode*>(i2->slice(se5, h2));
          QUERY3_mLINEITEM2_mCUSTOMER2_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long query3_mcustomercustomer_custkey = e2->QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
              date orders_orderdate = e2->ORDERS_ORDERDATE;
              long orders_shippriority = e2->ORDERS_SHIPPRIORITY;
              long v2 = e2->__av;
              (/*if */(lineitem_shipdate > c1) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se4.modify(lineitem_orderkey,query3_mcustomercustomer_custkey,orders_orderdate,orders_shippriority),(v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_QUERY3_mLINEITEM2_map_0* i3 = static_cast<HashIndex_QUERY3_mLINEITEM2_map_0*>(QUERY3_mLINEITEM2.index[1]);
          const HASH_RES_t h3 = QUERY3_mLINEITEM2_mapkey0_idxfn::hash(se7.modify0(lineitem_orderkey));
          HashIndex_QUERY3_mLINEITEM2_map_0::IdxNode* n3 = static_cast<HashIndex_QUERY3_mLINEITEM2_map_0::IdxNode*>(i3->slice(se7, h3));
          QUERY3_mLINEITEM2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              date orders_orderdate = e3->ORDERS_ORDERDATE;
              long orders_shippriority = e3->ORDERS_SHIPPRIORITY;
              long v3 = e3->__av;
              (/*if */(lineitem_shipdate > c1) ? QUERY3.addOrDelOnZero(se6.modify(lineitem_orderkey,orders_orderdate,orders_shippriority),(v3 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  QUERY3_mLINEITEM2_mapkey0_idxfn::equals(se7, *e3)); 
          }
        }(/*if */(lineitem_shipdate > c1) ? QUERY3_mORDERS3.addOrDelOnZero(se8.modify(lineitem_orderkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
        { //slice 
          const HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0* i4 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0*>(QUERY3_mLINEITEM2_mCUSTOMER2.index[1]);
          const HASH_RES_t h4 = QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0_idxfn::hash(se10.modify0(lineitem_orderkey));
          HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0::IdxNode* n4 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_0::IdxNode*>(i4->slice(se10, h4));
          QUERY3_mLINEITEM2_mCUSTOMER2_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long query3_mcustomercustomer_custkey = e4->QUERY3_mLINEITEM2_mCUSTOMERCUSTOMER_CUSTKEY;
              date orders_orderdate = e4->ORDERS_ORDERDATE;
              long orders_shippriority = e4->ORDERS_SHIPPRIORITY;
              long v4 = e4->__av;
              (/*if */(lineitem_shipdate > c1) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se9.modify(lineitem_orderkey,query3_mcustomercustomer_custkey,orders_orderdate,orders_shippriority),(v4 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  QUERY3_mLINEITEM2_mCUSTOMER2_mapkey0_idxfn::equals(se10, *e4)); 
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        (/*if */(c1 > orders_orderdate) ? QUERY3.addOrDelOnZero(se11.modify(orders_orderkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS2.getValueOrDefault(se12.modify(orders_custkey)) * QUERY3_mORDERS3.getValueOrDefault(se13.modify(orders_orderkey)))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM2.addOrDelOnZero(se14.modify(orders_orderkey,orders_orderdate,orders_shippriority),QUERY3_mORDERS2.getValueOrDefault(se15.modify(orders_custkey))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM2_mCUSTOMER2.addOrDelOnZero(se16.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),1L) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se17.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),QUERY3_mORDERS3.getValueOrDefault(se18.modify(orders_orderkey))) : (void)0);
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        (/*if */(c1 > orders_orderdate) ? QUERY3.addOrDelOnZero(se19.modify(orders_orderkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS2.getValueOrDefault(se20.modify(orders_custkey)) * (QUERY3_mORDERS3.getValueOrDefault(se21.modify(orders_orderkey)) * -1L))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM2.addOrDelOnZero(se22.modify(orders_orderkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS2.getValueOrDefault(se23.modify(orders_custkey)) * -1L)) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM2_mCUSTOMER2.addOrDelOnZero(se24.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),-1L) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se25.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS3.getValueOrDefault(se26.modify(orders_orderkey)) * -1L)) : (void)0);
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_QUERY3_mCUSTOMER2_map_1* i5 = static_cast<HashIndex_QUERY3_mCUSTOMER2_map_1*>(QUERY3_mCUSTOMER2.index[1]);
          const HASH_RES_t h5 = QUERY3_mCUSTOMER2_mapkey1_idxfn::hash(se28.modify1(customer_custkey));
          HashIndex_QUERY3_mCUSTOMER2_map_1::IdxNode* n5 = static_cast<HashIndex_QUERY3_mCUSTOMER2_map_1::IdxNode*>(i5->slice(se28, h5));
          QUERY3_mCUSTOMER2_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long orders_orderkey = e5->ORDERS_ORDERKEY;
              date orders_orderdate = e5->ORDERS_ORDERDATE;
              long orders_shippriority = e5->ORDERS_SHIPPRIORITY;
              DOUBLE_TYPE v5 = e5->__av;
              (/*if */(customer_mktsegment == c2) ? QUERY3.addOrDelOnZero(se27.modify(orders_orderkey,orders_orderdate,orders_shippriority),v5) : (void)0);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  QUERY3_mCUSTOMER2_mapkey1_idxfn::equals(se28, *e5)); 
          }
        }{ //slice 
          const HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1* i6 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1*>(QUERY3_mLINEITEM2_mCUSTOMER2.index[2]);
          const HASH_RES_t h6 = QUERY3_mLINEITEM2_mCUSTOMER2_mapkey1_idxfn::hash(se30.modify1(customer_custkey));
          HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1::IdxNode* n6 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1::IdxNode*>(i6->slice(se30, h6));
          QUERY3_mLINEITEM2_mCUSTOMER2_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long query3_mlineitemlineitem_orderkey = e6->QUERY3_mLINEITEMLINEITEM_ORDERKEY;
              date orders_orderdate = e6->ORDERS_ORDERDATE;
              long orders_shippriority = e6->ORDERS_SHIPPRIORITY;
              long v6 = e6->__av;
              (/*if */(customer_mktsegment == c2) ? QUERY3_mLINEITEM2.addOrDelOnZero(se29.modify(query3_mlineitemlineitem_orderkey,orders_orderdate,orders_shippriority),v6) : (void)0);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  QUERY3_mLINEITEM2_mCUSTOMER2_mapkey1_idxfn::equals(se30, *e6)); 
          }
        }(/*if */(customer_mktsegment == c2) ? QUERY3_mORDERS2.addOrDelOnZero(se31.modify(customer_custkey),1L) : (void)0);
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_QUERY3_mCUSTOMER2_map_1* i7 = static_cast<HashIndex_QUERY3_mCUSTOMER2_map_1*>(QUERY3_mCUSTOMER2.index[1]);
          const HASH_RES_t h7 = QUERY3_mCUSTOMER2_mapkey1_idxfn::hash(se33.modify1(customer_custkey));
          HashIndex_QUERY3_mCUSTOMER2_map_1::IdxNode* n7 = static_cast<HashIndex_QUERY3_mCUSTOMER2_map_1::IdxNode*>(i7->slice(se33, h7));
          QUERY3_mCUSTOMER2_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              long orders_orderkey = e7->ORDERS_ORDERKEY;
              date orders_orderdate = e7->ORDERS_ORDERDATE;
              long orders_shippriority = e7->ORDERS_SHIPPRIORITY;
              DOUBLE_TYPE v7 = e7->__av;
              (/*if */(customer_mktsegment == c2) ? QUERY3.addOrDelOnZero(se32.modify(orders_orderkey,orders_orderdate,orders_shippriority),(v7 * -1L)) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  QUERY3_mCUSTOMER2_mapkey1_idxfn::equals(se33, *e7)); 
          }
        }{ //slice 
          const HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1* i8 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1*>(QUERY3_mLINEITEM2_mCUSTOMER2.index[2]);
          const HASH_RES_t h8 = QUERY3_mLINEITEM2_mCUSTOMER2_mapkey1_idxfn::hash(se35.modify1(customer_custkey));
          HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1::IdxNode* n8 = static_cast<HashIndex_QUERY3_mLINEITEM2_mCUSTOMER2_map_1::IdxNode*>(i8->slice(se35, h8));
          QUERY3_mLINEITEM2_mCUSTOMER2_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long query3_mlineitemlineitem_orderkey = e8->QUERY3_mLINEITEMLINEITEM_ORDERKEY;
              date orders_orderdate = e8->ORDERS_ORDERDATE;
              long orders_shippriority = e8->ORDERS_SHIPPRIORITY;
              long v8 = e8->__av;
              (/*if */(customer_mktsegment == c2) ? QUERY3_mLINEITEM2.addOrDelOnZero(se34.modify(query3_mlineitemlineitem_orderkey,orders_orderdate,orders_shippriority),(v8 * -1L)) : (void)0);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  QUERY3_mLINEITEM2_mCUSTOMER2_mapkey1_idxfn::equals(se35, *e8)); 
          }
        }(/*if */(customer_mktsegment == c2) ? QUERY3_mORDERS2.addOrDelOnZero(se36.modify(customer_custkey),-1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  //
        
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY3_entry se1;
    QUERY3_mLINEITEM2_entry se2;
    QUERY3_mORDERS3_entry se3;
    QUERY3_mCUSTOMER2_entry se4;
    QUERY3_mLINEITEM2_mCUSTOMER2_entry se5;
    QUERY3_entry se6;
    QUERY3_mLINEITEM2_entry se7;
    QUERY3_mORDERS3_entry se8;
    QUERY3_mCUSTOMER2_entry se9;
    QUERY3_mLINEITEM2_mCUSTOMER2_entry se10;
    QUERY3_entry se11;
    QUERY3_mORDERS2_entry se12;
    QUERY3_mORDERS3_entry se13;
    QUERY3_mLINEITEM2_entry se14;
    QUERY3_mORDERS2_entry se15;
    QUERY3_mLINEITEM2_mCUSTOMER2_entry se16;
    QUERY3_mCUSTOMER2_entry se17;
    QUERY3_mORDERS3_entry se18;
    QUERY3_entry se19;
    QUERY3_mORDERS2_entry se20;
    QUERY3_mORDERS3_entry se21;
    QUERY3_mLINEITEM2_entry se22;
    QUERY3_mORDERS2_entry se23;
    QUERY3_mLINEITEM2_mCUSTOMER2_entry se24;
    QUERY3_mCUSTOMER2_entry se25;
    QUERY3_mORDERS3_entry se26;
    QUERY3_entry se27;
    QUERY3_mCUSTOMER2_entry se28;
    QUERY3_mLINEITEM2_entry se29;
    QUERY3_mLINEITEM2_mCUSTOMER2_entry se30;
    QUERY3_mORDERS2_entry se31;
    QUERY3_entry se32;
    QUERY3_mCUSTOMER2_entry se33;
    QUERY3_mLINEITEM2_entry se34;
    QUERY3_mLINEITEM2_mCUSTOMER2_entry se35;
    QUERY3_mORDERS2_entry se36;
  
    /* Data structures used for storing materialized views */
    QUERY3_mLINEITEM2_map QUERY3_mLINEITEM2;
    QUERY3_mLINEITEM2_mCUSTOMER2_map QUERY3_mLINEITEM2_mCUSTOMER2;
    QUERY3_mORDERS2_map QUERY3_mORDERS2;
    QUERY3_mORDERS3_map QUERY3_mORDERS3;
    QUERY3_mCUSTOMER2_map QUERY3_mCUSTOMER2;
    
    /*const static*/ STRING_TYPE c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
