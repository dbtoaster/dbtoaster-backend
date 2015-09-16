#include <sys/time.h>
#include "macro.hpp"
#include "types.hpp"
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
  
  struct QUERY3_mLINEITEM1_entry {
    long QUERY3_mLINEITEMLINEITEM_ORDERKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av;  
    explicit QUERY3_mLINEITEM1_entry() { /*QUERY3_mLINEITEMLINEITEM_ORDERKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3_mLINEITEM1_entry(const long c0, const date c1, const long c2, const long c3) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2; __av = c3; }
    QUERY3_mLINEITEM1_entry(const QUERY3_mLINEITEM1_entry& other) : QUERY3_mLINEITEMLINEITEM_ORDERKEY( other.QUERY3_mLINEITEMLINEITEM_ORDERKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mLINEITEM1_entry& modify(const long c0, const date c1, const long c2) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; ORDERS_ORDERDATE = c1; ORDERS_SHIPPRIORITY = c2;  return *this; }
    FORCE_INLINE QUERY3_mLINEITEM1_entry& modify0(const long c0) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
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
  struct QUERY3_mLINEITEM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM1_entry& x, const QUERY3_mLINEITEM1_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3_mLINEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM1_entry& x, const QUERY3_mLINEITEM1_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mLINEITEM1_entry,long,
    HashIndex<QUERY3_mLINEITEM1_entry,long,QUERY3_mLINEITEM1_mapkey012_idxfn,true>,
    HashIndex<QUERY3_mLINEITEM1_entry,long,QUERY3_mLINEITEM1_mapkey0_idxfn,false>
  > QUERY3_mLINEITEM1_map;
  typedef HashIndex<QUERY3_mLINEITEM1_entry,long,QUERY3_mLINEITEM1_mapkey012_idxfn,true> HashIndex_QUERY3_mLINEITEM1_map_012;
  typedef HashIndex<QUERY3_mLINEITEM1_entry,long,QUERY3_mLINEITEM1_mapkey0_idxfn,false> HashIndex_QUERY3_mLINEITEM1_map_0;
  
  struct QUERY3_mLINEITEM1_mCUSTOMER2_entry {
    long QUERY3_mLINEITEMLINEITEM_ORDERKEY; long QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY; date ORDERS_ORDERDATE; long ORDERS_SHIPPRIORITY; long __av; 
    explicit QUERY3_mLINEITEM1_mCUSTOMER2_entry() { /*QUERY3_mLINEITEMLINEITEM_ORDERKEY = 0L; QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY = 0L; ORDERS_ORDERDATE = 00000000; ORDERS_SHIPPRIORITY = 0L; __av = 0L; */ }
    explicit QUERY3_mLINEITEM1_mCUSTOMER2_entry(const long c0, const long c1, const date c2, const long c3, const long c4) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3; __av = c4; }
    QUERY3_mLINEITEM1_mCUSTOMER2_entry(const QUERY3_mLINEITEM1_mCUSTOMER2_entry& other) : QUERY3_mLINEITEMLINEITEM_ORDERKEY( other.QUERY3_mLINEITEMLINEITEM_ORDERKEY ), QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY( other.QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY ), ORDERS_ORDERDATE( other.ORDERS_ORDERDATE ), ORDERS_SHIPPRIORITY( other.ORDERS_SHIPPRIORITY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mLINEITEM1_mCUSTOMER2_entry& modify(const long c0, const long c1, const date c2, const long c3) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0; QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY = c1; ORDERS_ORDERDATE = c2; ORDERS_SHIPPRIORITY = c3;  return *this; }
    FORCE_INLINE QUERY3_mLINEITEM1_mCUSTOMER2_entry& modify0(const long c0) { QUERY3_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE QUERY3_mLINEITEM1_mCUSTOMER2_entry& modify1(const long c1) { QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_ORDERDATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERS_SHIPPRIORITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM1_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.ORDERS_ORDERDATE);
      hash_combine(h, e.ORDERS_SHIPPRIORITY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM1_mCUSTOMER2_entry& x, const QUERY3_mLINEITEM1_mCUSTOMER2_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY && x.QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY && x.ORDERS_ORDERDATE == y.ORDERS_ORDERDATE && x.ORDERS_SHIPPRIORITY == y.ORDERS_SHIPPRIORITY;
    }
  };
  
  struct QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM1_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM1_mCUSTOMER2_entry& x, const QUERY3_mLINEITEM1_mCUSTOMER2_entry& y) {
      return x.QUERY3_mLINEITEMLINEITEM_ORDERKEY == y.QUERY3_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct QUERY3_mLINEITEM1_mCUSTOMER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mLINEITEM1_mCUSTOMER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mLINEITEM1_mCUSTOMER2_entry& x, const QUERY3_mLINEITEM1_mCUSTOMER2_entry& y) {
      return x.QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY == y.QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mLINEITEM1_mCUSTOMER2_entry,long,
    HashIndex<QUERY3_mLINEITEM1_mCUSTOMER2_entry,long,QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0123_idxfn,true>,
    HashIndex<QUERY3_mLINEITEM1_mCUSTOMER2_entry,long,QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0_idxfn,false>,
    HashIndex<QUERY3_mLINEITEM1_mCUSTOMER2_entry,long,QUERY3_mLINEITEM1_mCUSTOMER2_mapkey1_idxfn,false>
  > QUERY3_mLINEITEM1_mCUSTOMER2_map;
  typedef HashIndex<QUERY3_mLINEITEM1_mCUSTOMER2_entry,long,QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0123_idxfn,true> HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0123;
  typedef HashIndex<QUERY3_mLINEITEM1_mCUSTOMER2_entry,long,QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0_idxfn,false> HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0;
  typedef HashIndex<QUERY3_mLINEITEM1_mCUSTOMER2_entry,long,QUERY3_mLINEITEM1_mCUSTOMER2_mapkey1_idxfn,false> HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1;
  
  struct QUERY3_mORDERS1_entry {
    long QUERY3_mORDERSORDERS_CUSTKEY; long __av;  
    explicit QUERY3_mORDERS1_entry() { /*QUERY3_mORDERSORDERS_CUSTKEY = 0L; __av = 0L; */ }
    explicit QUERY3_mORDERS1_entry(const long c0, const long c1) { QUERY3_mORDERSORDERS_CUSTKEY = c0; __av = c1; }
    QUERY3_mORDERS1_entry(const QUERY3_mORDERS1_entry& other) : QUERY3_mORDERSORDERS_CUSTKEY( other.QUERY3_mORDERSORDERS_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE QUERY3_mORDERS1_entry& modify(const long c0) { QUERY3_mORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, QUERY3_mORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct QUERY3_mORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const QUERY3_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.QUERY3_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const QUERY3_mORDERS1_entry& x, const QUERY3_mORDERS1_entry& y) {
      return x.QUERY3_mORDERSORDERS_CUSTKEY == y.QUERY3_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<QUERY3_mORDERS1_entry,long,
    HashIndex<QUERY3_mORDERS1_entry,long,QUERY3_mORDERS1_mapkey0_idxfn,true>
  > QUERY3_mORDERS1_map;
  typedef HashIndex<QUERY3_mORDERS1_entry,long,QUERY3_mORDERS1_mapkey0_idxfn,true> HashIndex_QUERY3_mORDERS1_map_0;
  
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
      c1 = str2date("1995-3-15");
    }
  
    // #ifdef DBT_PROFILE
    // std::shared_ptr<dbtoaster::statistics::trigger_exec_stats> exec_stats;
    // std::shared_ptr<dbtoaster::statistics::trigger_exec_stats> ivc_stats;
    // #endif
  
    // /* Registering relations and trigger functions */
    // ProgramBase* program_base;
    // void register_data(ProgramBase& pb) {
    // program_base = &pb;
  
    //   pb.add_map<QUERY3_map>( "QUERY3", QUERY3 );
    //   pb.add_map<QUERY3_mLINEITEM1_map>( "QUERY3_mLINEITEM1", QUERY3_mLINEITEM1 );
    //   pb.add_map<QUERY3_mLINEITEM1_mCUSTOMER2_map>( "QUERY3_mLINEITEM1_mCUSTOMER2", QUERY3_mLINEITEM1_mCUSTOMER2 );
    //   pb.add_map<QUERY3_mORDERS1_map>( "QUERY3_mORDERS1", QUERY3_mORDERS1 );
    //   pb.add_map<QUERY3_mORDERS3_map>( "QUERY3_mORDERS3", QUERY3_mORDERS3 );
    //   pb.add_map<QUERY3_mCUSTOMER2_map>( "QUERY3_mCUSTOMER2", QUERY3_mCUSTOMER2 );
  
    //   pb.add_relation("LINEITEM");
    //   pb.add_relation("ORDERS");
    //   pb.add_relation("CUSTOMER");
  
      
  
    //   pb.add_trigger("LINEITEM", insert_tuple, std::bind(&data_t::unwrap_insert_LINEITEM, this, std::placeholders::_1));
    //   pb.add_trigger("LINEITEM", delete_tuple, std::bind(&data_t::unwrap_delete_LINEITEM, this, std::placeholders::_1));
    //   pb.add_trigger("ORDERS", insert_tuple, std::bind(&data_t::unwrap_insert_ORDERS, this, std::placeholders::_1));
    //   pb.add_trigger("ORDERS", delete_tuple, std::bind(&data_t::unwrap_delete_ORDERS, this, std::placeholders::_1));
    //   pb.add_trigger("CUSTOMER", insert_tuple, std::bind(&data_t::unwrap_insert_CUSTOMER, this, std::placeholders::_1));
    //   pb.add_trigger("CUSTOMER", delete_tuple, std::bind(&data_t::unwrap_delete_CUSTOMER, this, std::placeholders::_1));
  
    //   #ifdef DBT_PROFILE
    //   exec_stats = pb.exec_stats;
    //   ivc_stats = pb.ivc_stats;
    //   exec_stats->register_probe(0, "insert_LINEITEM_s0");
    //   exec_stats->register_probe(1, "insert_LINEITEM_s1");
    //   exec_stats->register_probe(2, "insert_LINEITEM_s2");
    //   exec_stats->register_probe(3, "delete_LINEITEM_s0");
    //   exec_stats->register_probe(4, "delete_LINEITEM_s1");
    //   exec_stats->register_probe(5, "delete_LINEITEM_s2");
    //   exec_stats->register_probe(6, "insert_ORDERS_s0");
    //   exec_stats->register_probe(7, "insert_ORDERS_s1");
    //   exec_stats->register_probe(8, "insert_ORDERS_s2");
    //   exec_stats->register_probe(9, "insert_ORDERS_s3");
    //   exec_stats->register_probe(10, "delete_ORDERS_s0");
    //   exec_stats->register_probe(11, "delete_ORDERS_s1");
    //   exec_stats->register_probe(12, "delete_ORDERS_s2");
    //   exec_stats->register_probe(13, "delete_ORDERS_s3");
    //   exec_stats->register_probe(14, "insert_CUSTOMER_s0");
    //   exec_stats->register_probe(15, "insert_CUSTOMER_s1");
    //   exec_stats->register_probe(16, "insert_CUSTOMER_s2");
    //   exec_stats->register_probe(17, "delete_CUSTOMER_s0");
    //   exec_stats->register_probe(18, "delete_CUSTOMER_s1");
    //   exec_stats->register_probe(19, "delete_CUSTOMER_s2");
    //   #endif // DBT_PROFILE
  
    // }
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    FORCE_INLINE
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      // BEGIN_TRIGGER(exec_stats,"insert_LINEITEM")
      // BEGIN_TRIGGER(ivc_stats,"insert_LINEITEM")
      {  ++tN;
        { //slice
          const HashIndex_QUERY3_mLINEITEM1_map_0* i1 = static_cast<HashIndex_QUERY3_mLINEITEM1_map_0*>(QUERY3_mLINEITEM1.index[1]);
          const HASH_RES_t h1 = QUERY3_mLINEITEM1_mapkey0_idxfn::hash(se2.modify0(lineitem_orderkey));
          HashIndex_QUERY3_mLINEITEM1_map_0::IdxNode* n1 = static_cast<HashIndex_QUERY3_mLINEITEM1_map_0::IdxNode*>(i1->slice(se2, h1));
          QUERY3_mLINEITEM1_entry* e1;

          while (n1 && (e1 = n1->obj) && h1 == n1->hash && QUERY3_mLINEITEM1_mapkey0_idxfn::equals(se2, *e1))
          {
            DATE_TYPE orders_orderdate = e1->ORDERS_ORDERDATE;
            long orders_shippriority = e1->ORDERS_SHIPPRIORITY;
            long v1 = e1->__av;
            (/*if */(lineitem_shipdate > c1) ? QUERY3.addOrDelOnZero(se1.modify(lineitem_orderkey,orders_orderdate,orders_shippriority),(v1 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
            n1 = n1->nxt;
          }
        }
        (/*if */(lineitem_shipdate > c1) ? QUERY3_mORDERS3.addOrDelOnZero(se3.modify(lineitem_orderkey),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        { //slice
          const HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0* i2 = static_cast<HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0*>(QUERY3_mLINEITEM1_mCUSTOMER2.index[1]);
          const HASH_RES_t h2 = QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0_idxfn::hash(se5.modify0(lineitem_orderkey));
          HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0::IdxNode* n2 =
              static_cast<HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0::IdxNode*>(i2->slice(se5, h2));
          QUERY3_mLINEITEM1_mCUSTOMER2_entry* e2;

          while (n2 && (e2 = n2->obj) && h2 == n2->hash && QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0_idxfn::equals(se5, *e2))
          {
            long query3_mcustomercustomer_custkey = e2->QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY;
            DATE_TYPE orders_orderdate = e2->ORDERS_ORDERDATE;
            long orders_shippriority = e2->ORDERS_SHIPPRIORITY;
            long v2 = e2->__av;
            (/*if */(lineitem_shipdate > c1) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se4.modify(lineitem_orderkey,query3_mcustomercustomer_custkey,orders_orderdate,orders_shippriority),(v2 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
            n2 = n2->nxt;
          }
        }
      }
      // END_TRIGGER(exec_stats,"insert_LINEITEM")
      // END_TRIGGER(ivc_stats,"insert_LINEITEM")
    }
    // void unwrap_insert_LINEITEM(const event_args_t& ea) {
    //   on_insert_LINEITEM(*(reinterpret_cast<long*>(ea[0].get())), *(reinterpret_cast<long*>(ea[1].get())), *(reinterpret_cast<long*>(ea[2].get())), *(reinterpret_cast<long*>(ea[3].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[4].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[5].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[6].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[7].get())), *(reinterpret_cast<STRING_TYPE*>(ea[8].get())), *(reinterpret_cast<STRING_TYPE*>(ea[9].get())), *(reinterpret_cast<date*>(ea[10].get())), *(reinterpret_cast<date*>(ea[11].get())), *(reinterpret_cast<date*>(ea[12].get())), *(reinterpret_cast<STRING_TYPE*>(ea[13].get())), *(reinterpret_cast<STRING_TYPE*>(ea[14].get())), *(reinterpret_cast<STRING_TYPE*>(ea[15].get())));
    // }
    
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      // BEGIN_TRIGGER(exec_stats,"delete_LINEITEM")
      // BEGIN_TRIGGER(ivc_stats,"delete_LINEITEM")
      {  ++tN;
        { //slice
          const HASH_RES_t h3 = QUERY3_mLINEITEM1_mapkey0_idxfn::hash(se7.modify0(lineitem_orderkey));
          const HashIndex_QUERY3_mLINEITEM1_map_0* i3 = static_cast<HashIndex_QUERY3_mLINEITEM1_map_0*>(QUERY3_mLINEITEM1.index[1]);
          HashIndex_QUERY3_mLINEITEM1_map_0::IdxNode* n3 = &(i3->buckets_[h3 & i3->index_mask_]);
          QUERY3_mLINEITEM1_entry* e3;
          do if ((e3=n3->obj) && h3 == n3->hash && QUERY3_mLINEITEM1_mapkey0_idxfn::equals(se7, *e3)) {
            date orders_orderdate = e3->ORDERS_ORDERDATE;
            long orders_shippriority = e3->ORDERS_SHIPPRIORITY;
            long v3 = e3->__av;
            (/*if */(lineitem_shipdate > c1) ? QUERY3.addOrDelOnZero(se6.modify(lineitem_orderkey,orders_orderdate,orders_shippriority),(v3 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
          } while ((n3=n3->nxt));
        }
        (/*if */(lineitem_shipdate > c1) ? QUERY3_mORDERS3.addOrDelOnZero(se8.modify(lineitem_orderkey),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
        { //slice
          const HASH_RES_t h4 = QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0_idxfn::hash(se10.modify0(lineitem_orderkey));
          const HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0* i4 = static_cast<HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0*>(QUERY3_mLINEITEM1_mCUSTOMER2.index[1]);
          HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_0::IdxNode* n4 = &(i4->buckets_[h4 & i4->index_mask_]);
          QUERY3_mLINEITEM1_mCUSTOMER2_entry* e4;
          do if ((e4=n4->obj) && h4 == n4->hash && QUERY3_mLINEITEM1_mCUSTOMER2_mapkey0_idxfn::equals(se10, *e4)) {
            long query3_mcustomercustomer_custkey = e4->QUERY3_mLINEITEM1_mCUSTOMERCUSTOMER_CUSTKEY;
            date orders_orderdate = e4->ORDERS_ORDERDATE;
            long orders_shippriority = e4->ORDERS_SHIPPRIORITY;
            long v4 = e4->__av;
            (/*if */(lineitem_shipdate > c1) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se9.modify(lineitem_orderkey,query3_mcustomercustomer_custkey,orders_orderdate,orders_shippriority),(v4 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
          } while ((n4=n4->nxt));
        }
      }
      // END_TRIGGER(exec_stats,"delete_LINEITEM")
      // END_TRIGGER(ivc_stats,"delete_LINEITEM")
    }
    // void unwrap_delete_LINEITEM(const event_args_t& ea) {
    //   on_delete_LINEITEM(*(reinterpret_cast<long*>(ea[0].get())), *(reinterpret_cast<long*>(ea[1].get())), *(reinterpret_cast<long*>(ea[2].get())), *(reinterpret_cast<long*>(ea[3].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[4].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[5].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[6].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[7].get())), *(reinterpret_cast<STRING_TYPE*>(ea[8].get())), *(reinterpret_cast<STRING_TYPE*>(ea[9].get())), *(reinterpret_cast<date*>(ea[10].get())), *(reinterpret_cast<date*>(ea[11].get())), *(reinterpret_cast<date*>(ea[12].get())), *(reinterpret_cast<STRING_TYPE*>(ea[13].get())), *(reinterpret_cast<STRING_TYPE*>(ea[14].get())), *(reinterpret_cast<STRING_TYPE*>(ea[15].get())));
    // }
    
    FORCE_INLINE
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      // BEGIN_TRIGGER(exec_stats,"insert_ORDERS")
      // BEGIN_TRIGGER(ivc_stats,"insert_ORDERS")
      {  ++tN;
        (/*if */(c1 > orders_orderdate) ? QUERY3.addOrDelOnZero(se11.modify(orders_orderkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS1.getValueOrDefault(se12.modify(orders_custkey)) * QUERY3_mORDERS3.getValueOrDefault(se13.modify(orders_orderkey)))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM1.addOrDelOnZero(se14.modify(orders_orderkey,orders_orderdate,orders_shippriority),QUERY3_mORDERS1.getValueOrDefault(se15.modify(orders_custkey))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM1_mCUSTOMER2.addOrDelOnZero(se16.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),1L) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se17.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),QUERY3_mORDERS3.getValueOrDefault(se18.modify(orders_orderkey))) : (void)0);
      }
      // END_TRIGGER(exec_stats,"insert_ORDERS")
      // END_TRIGGER(ivc_stats,"insert_ORDERS")
    }
    // void unwrap_insert_ORDERS(const event_args_t& ea) {
    //   on_insert_ORDERS(*(reinterpret_cast<long*>(ea[0].get())), *(reinterpret_cast<long*>(ea[1].get())), *(reinterpret_cast<STRING_TYPE*>(ea[2].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[3].get())), *(reinterpret_cast<date*>(ea[4].get())), *(reinterpret_cast<STRING_TYPE*>(ea[5].get())), *(reinterpret_cast<STRING_TYPE*>(ea[6].get())), *(reinterpret_cast<long*>(ea[7].get())), *(reinterpret_cast<STRING_TYPE*>(ea[8].get())));
    // }
    
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      // BEGIN_TRIGGER(exec_stats,"delete_ORDERS")
      // BEGIN_TRIGGER(ivc_stats,"delete_ORDERS")
      {  ++tN;
        (/*if */(c1 > orders_orderdate) ? QUERY3.addOrDelOnZero(se19.modify(orders_orderkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS1.getValueOrDefault(se20.modify(orders_custkey)) * (QUERY3_mORDERS3.getValueOrDefault(se21.modify(orders_orderkey)) * -1L))) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM1.addOrDelOnZero(se22.modify(orders_orderkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS1.getValueOrDefault(se23.modify(orders_custkey)) * -1L)) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mLINEITEM1_mCUSTOMER2.addOrDelOnZero(se24.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),-1L) : (void)0);
        (/*if */(c1 > orders_orderdate) ? QUERY3_mCUSTOMER2.addOrDelOnZero(se25.modify(orders_orderkey,orders_custkey,orders_orderdate,orders_shippriority),(QUERY3_mORDERS3.getValueOrDefault(se26.modify(orders_orderkey)) * -1L)) : (void)0);
      }
      // END_TRIGGER(exec_stats,"delete_ORDERS")
      // END_TRIGGER(ivc_stats,"delete_ORDERS")
    }
    // void unwrap_delete_ORDERS(const event_args_t& ea) {
    //   on_delete_ORDERS(*(reinterpret_cast<long*>(ea[0].get())), *(reinterpret_cast<long*>(ea[1].get())), *(reinterpret_cast<STRING_TYPE*>(ea[2].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[3].get())), *(reinterpret_cast<date*>(ea[4].get())), *(reinterpret_cast<STRING_TYPE*>(ea[5].get())), *(reinterpret_cast<STRING_TYPE*>(ea[6].get())), *(reinterpret_cast<long*>(ea[7].get())), *(reinterpret_cast<STRING_TYPE*>(ea[8].get())));
    // }
    
    FORCE_INLINE
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      // BEGIN_TRIGGER(exec_stats,"insert_CUSTOMER")
      // BEGIN_TRIGGER(ivc_stats,"insert_CUSTOMER")
      {  ++tN;
        { //slice
          const HashIndex_QUERY3_mCUSTOMER2_map_1* i5 = static_cast<HashIndex_QUERY3_mCUSTOMER2_map_1*>(QUERY3_mCUSTOMER2.index[1]);
          const HASH_RES_t h5 = QUERY3_mCUSTOMER2_mapkey1_idxfn::hash(se28.modify1(customer_custkey));
          HashIndex_QUERY3_mCUSTOMER2_map_1::IdxNode* n5 = static_cast<HashIndex_QUERY3_mCUSTOMER2_map_1::IdxNode*>(i5->slice(se28, h5));
          QUERY3_mCUSTOMER2_entry* e5;

          while (n5 && (e5 = n5->obj) && h5 == n5->hash && QUERY3_mCUSTOMER2_mapkey1_idxfn::equals(se28, *e5))
          {
            long orders_orderkey = e5->ORDERS_ORDERKEY;
            DATE_TYPE orders_orderdate = e5->ORDERS_ORDERDATE;
            long orders_shippriority = e5->ORDERS_SHIPPRIORITY;
            DOUBLE_TYPE v5 = e5->__av;
            (/*if */(customer_mktsegment == c2) ? QUERY3.addOrDelOnZero(se27.modify(orders_orderkey,orders_orderdate,orders_shippriority),v5) : (void)0);
            n5 = n5->nxt;
          }
        }
        { //slice
          const HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1* i6 = static_cast<HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1*>(QUERY3_mLINEITEM1_mCUSTOMER2.index[2]);
          const HASH_RES_t h6 = QUERY3_mLINEITEM1_mCUSTOMER2_mapkey1_idxfn::hash(se30.modify1(customer_custkey));
          HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1::IdxNode* n6 = static_cast<HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1::IdxNode*>(i6->slice(se30, h6));
          QUERY3_mLINEITEM1_mCUSTOMER2_entry* e6;

          while (n6 && (e6 = n6->obj) && h6 == n6->hash && QUERY3_mLINEITEM1_mCUSTOMER2_mapkey1_idxfn::equals(se30, *e6))
          {
            long query3_mlineitemlineitem_orderkey = e6->QUERY3_mLINEITEMLINEITEM_ORDERKEY;
            DATE_TYPE orders_orderdate = e6->ORDERS_ORDERDATE;
            long orders_shippriority = e6->ORDERS_SHIPPRIORITY;
            long v6 = e6->__av;
            (/*if */(customer_mktsegment == c2) ? QUERY3_mLINEITEM1.addOrDelOnZero(se29.modify(query3_mlineitemlineitem_orderkey,orders_orderdate,orders_shippriority),v6) : (void)0);
            n6 = n6->nxt;
          }
        }
        (/*if */(customer_mktsegment == c2) ? QUERY3_mORDERS1.addOrDelOnZero(se31.modify(customer_custkey),1L) : (void)0);
      }
      // END_TRIGGER(exec_stats,"insert_CUSTOMER")
      // END_TRIGGER(ivc_stats,"insert_CUSTOMER")
    }
    // void unwrap_insert_CUSTOMER(const event_args_t& ea) {
    //   on_insert_CUSTOMER(*(reinterpret_cast<long*>(ea[0].get())), *(reinterpret_cast<STRING_TYPE*>(ea[1].get())), *(reinterpret_cast<STRING_TYPE*>(ea[2].get())), *(reinterpret_cast<long*>(ea[3].get())), *(reinterpret_cast<STRING_TYPE*>(ea[4].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[5].get())), *(reinterpret_cast<STRING_TYPE*>(ea[6].get())), *(reinterpret_cast<STRING_TYPE*>(ea[7].get())));
    // }
    
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      // BEGIN_TRIGGER(exec_stats,"delete_CUSTOMER")
      // BEGIN_TRIGGER(ivc_stats,"delete_CUSTOMER")
      {  ++tN;
        { //slice
          const HASH_RES_t h7 = QUERY3_mCUSTOMER2_mapkey1_idxfn::hash(se33.modify1(customer_custkey));
          const HashIndex_QUERY3_mCUSTOMER2_map_1* i7 = static_cast<HashIndex_QUERY3_mCUSTOMER2_map_1*>(QUERY3_mCUSTOMER2.index[1]);
          HashIndex_QUERY3_mCUSTOMER2_map_1::IdxNode* n7 = &(i7->buckets_[h7 & i7->index_mask_]);
          QUERY3_mCUSTOMER2_entry* e7;
          do if ((e7=n7->obj) && h7 == n7->hash && QUERY3_mCUSTOMER2_mapkey1_idxfn::equals(se33, *e7)) {
            long orders_orderkey = e7->ORDERS_ORDERKEY;
            date orders_orderdate = e7->ORDERS_ORDERDATE;
            long orders_shippriority = e7->ORDERS_SHIPPRIORITY;
            DOUBLE_TYPE v7 = e7->__av;
            (/*if */(customer_mktsegment == c2) ? QUERY3.addOrDelOnZero(se32.modify(orders_orderkey,orders_orderdate,orders_shippriority),(v7 * -1L)) : (void)0);
          } while ((n7=n7->nxt));
        }
        { //slice
          const HASH_RES_t h8 = QUERY3_mLINEITEM1_mCUSTOMER2_mapkey1_idxfn::hash(se35.modify1(customer_custkey));
          const HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1* i8 = static_cast<HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1*>(QUERY3_mLINEITEM1_mCUSTOMER2.index[2]);
          HashIndex_QUERY3_mLINEITEM1_mCUSTOMER2_map_1::IdxNode* n8 = &(i8->buckets_[h8 & i8->index_mask_]);
          QUERY3_mLINEITEM1_mCUSTOMER2_entry* e8;
          do if ((e8=n8->obj) && h8 == n8->hash && QUERY3_mLINEITEM1_mCUSTOMER2_mapkey1_idxfn::equals(se35, *e8)) {
            long query3_mlineitemlineitem_orderkey = e8->QUERY3_mLINEITEMLINEITEM_ORDERKEY;
            date orders_orderdate = e8->ORDERS_ORDERDATE;
            long orders_shippriority = e8->ORDERS_SHIPPRIORITY;
            long v8 = e8->__av;
            (/*if */(customer_mktsegment == c2) ? QUERY3_mLINEITEM1.addOrDelOnZero(se34.modify(query3_mlineitemlineitem_orderkey,orders_orderdate,orders_shippriority),(v8 * -1L)) : (void)0);
          } while ((n8=n8->nxt));
        }
        (/*if */(customer_mktsegment == c2) ? QUERY3_mORDERS1.addOrDelOnZero(se36.modify(customer_custkey),-1L) : (void)0);
      }
      // END_TRIGGER(exec_stats,"delete_CUSTOMER")
      // END_TRIGGER(ivc_stats,"delete_CUSTOMER")
    }
    // void unwrap_delete_CUSTOMER(const event_args_t& ea) {
    //   on_delete_CUSTOMER(*(reinterpret_cast<long*>(ea[0].get())), *(reinterpret_cast<STRING_TYPE*>(ea[1].get())), *(reinterpret_cast<STRING_TYPE*>(ea[2].get())), *(reinterpret_cast<long*>(ea[3].get())), *(reinterpret_cast<STRING_TYPE*>(ea[4].get())), *(reinterpret_cast<DOUBLE_TYPE*>(ea[5].get())), *(reinterpret_cast<STRING_TYPE*>(ea[6].get())), *(reinterpret_cast<STRING_TYPE*>(ea[7].get())));
    // }
    
    void on_system_ready_event() {
      // BEGIN_TRIGGER(exec_stats,"system_ready_event")
      // BEGIN_TRIGGER(ivc_stats,"system_ready_event")
      {  
        
      }
      // END_TRIGGER(exec_stats,"system_ready_event")
      // END_TRIGGER(ivc_stats,"system_ready_event")
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    QUERY3_entry se1;
    QUERY3_mLINEITEM1_entry se2;
    QUERY3_mORDERS3_entry se3;
    QUERY3_mCUSTOMER2_entry se4;
    QUERY3_mLINEITEM1_mCUSTOMER2_entry se5;
    QUERY3_entry se6;
    QUERY3_mLINEITEM1_entry se7;
    QUERY3_mORDERS3_entry se8;
    QUERY3_mCUSTOMER2_entry se9;
    QUERY3_mLINEITEM1_mCUSTOMER2_entry se10;
    QUERY3_entry se11;
    QUERY3_mORDERS1_entry se12;
    QUERY3_mORDERS3_entry se13;
    QUERY3_mLINEITEM1_entry se14;
    QUERY3_mORDERS1_entry se15;
    QUERY3_mLINEITEM1_mCUSTOMER2_entry se16;
    QUERY3_mCUSTOMER2_entry se17;
    QUERY3_mORDERS3_entry se18;
    QUERY3_entry se19;
    QUERY3_mORDERS1_entry se20;
    QUERY3_mORDERS3_entry se21;
    QUERY3_mLINEITEM1_entry se22;
    QUERY3_mORDERS1_entry se23;
    QUERY3_mLINEITEM1_mCUSTOMER2_entry se24;
    QUERY3_mCUSTOMER2_entry se25;
    QUERY3_mORDERS3_entry se26;
    QUERY3_entry se27;
    QUERY3_mCUSTOMER2_entry se28;
    QUERY3_mLINEITEM1_entry se29;
    QUERY3_mLINEITEM1_mCUSTOMER2_entry se30;
    QUERY3_mORDERS1_entry se31;
    QUERY3_entry se32;
    QUERY3_mCUSTOMER2_entry se33;
    QUERY3_mLINEITEM1_entry se34;
    QUERY3_mLINEITEM1_mCUSTOMER2_entry se35;
    QUERY3_mORDERS1_entry se36;
  
    /* Data structures used for storing materialized views */
    QUERY3_mLINEITEM1_map QUERY3_mLINEITEM1;
    QUERY3_mLINEITEM1_mCUSTOMER2_map QUERY3_mLINEITEM1_mCUSTOMER2;
    QUERY3_mORDERS1_map QUERY3_mORDERS1;
    QUERY3_mORDERS3_map QUERY3_mORDERS3;
    QUERY3_mCUSTOMER2_map QUERY3_mCUSTOMER2;
    
    /*const static*/ STRING_TYPE c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };
  

  // /* Type definition providing a way to execute the sql program */
  // class Program : public ProgramBase
  // {
  //   public:
  //     Program(int argc = 0, char* argv[] = 0) : ProgramBase(argc,argv) {
  //       data.register_data(*this);
        
  //       /* Specifying data sources */
        
        
  //       pair<string,string> source1_adaptor_params[] = { make_pair("delimiter","|"), make_pair("schema","long,long,long,long,double,double,double,double,string,string,date,date,date,string,string,string") };
  //       std::shared_ptr<csv_adaptor> source1_adaptor(new csv_adaptor(get_relation_id("LINEITEM"),2,source1_adaptor_params));
  //       frame_descriptor source1_fd("\n");
  //       std::shared_ptr<dbt_file_source> source1_file(new dbt_file_source("/Users/nikolic/EPFL/Projects/DBToaster/cornell_db_maybms/dbtoaster/experiments/data/tpch/standard/lineitem.csv",source1_fd,source1_adaptor));
  //       add_source(source1_file);
        
  //       pair<string,string> source2_adaptor_params[] = { make_pair("delimiter","|"), make_pair("schema","long,long,string,double,date,string,string,long,string") };
  //       std::shared_ptr<csv_adaptor> source2_adaptor(new csv_adaptor(get_relation_id("ORDERS"),2,source2_adaptor_params));
  //       frame_descriptor source2_fd("\n");
  //       std::shared_ptr<dbt_file_source> source2_file(new dbt_file_source("/Users/nikolic/EPFL/Projects/DBToaster/cornell_db_maybms/dbtoaster/experiments/data/tpch/standard/orders.csv",source2_fd,source2_adaptor));
  //       add_source(source2_file);
        
  //       pair<string,string> source3_adaptor_params[] = { make_pair("delimiter","|"), make_pair("schema","long,string,string,long,string,double,string,string") };
  //       std::shared_ptr<csv_adaptor> source3_adaptor(new csv_adaptor(get_relation_id("CUSTOMER"),2,source3_adaptor_params));
  //       frame_descriptor source3_fd("\n");
  //       std::shared_ptr<dbt_file_source> source3_file(new dbt_file_source("/Users/nikolic/EPFL/Projects/DBToaster/cornell_db_maybms/dbtoaster/experiments/data/tpch/standard/customer.csv",source3_fd,source3_adaptor));
  //       add_source(source3_file);
  
  //     }
  
  //     /* Imports data for static tables and performs view initialization based on it. */
  //     void init() {
  //         //P0_PLACE_HOLDER
  //         table_multiplexer.init_source(run_opts->batch_size, run_opts->parallel, true);
  //         stream_multiplexer.init_source(run_opts->batch_size, run_opts->parallel, false);
  //         process_tables();
  //         data.on_system_ready_event();
  //         struct timeval t0;
  //         gettimeofday(&t0,NULL);
  //         data.t0 = t0;

  //     }
  
  //     /* Saves a snapshot of the data required to obtain the results of top level queries. */
  //     snapshot_t take_snapshot(){
  //         tlq_t* d = new tlq_t((tlq_t&)data);
  //         if (d->tS==0) { gettimeofday(&(d->t),NULL); d->tT=((d->t).tv_sec-(d->t0).tv_sec)*1000000L+((d->t).tv_usec-(d->t0).tv_usec); } printf("SAMPLE=standard,%ld,%ld,%ld\n",d->tT,d->tN,d->tS);
  //         return snapshot_t( d );
  //     }
  
  //   protected:
  //     data_t data;
  // };
  // class Tpch3VCpp : public Program
  // {
  //   public:
  //     Tpch3VCpp(int argc = 0, char* argv[] = 0) : Program(argc,argv) {
  //     }
  // };

}
