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
  struct NATION_entry {
    long NATION_NATIONKEY; STRING_TYPE NATION_NAME; long NATION_REGIONKEY; STRING_TYPE NATION_COMMENT; long __av; 
    explicit NATION_entry() { /*NATION_NATIONKEY = 0L; NATION_NAME = ""; NATION_REGIONKEY = 0L; NATION_COMMENT = ""; __av = 0L; */ }
    explicit NATION_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4) { NATION_NATIONKEY = c0; NATION_NAME = c1; NATION_REGIONKEY = c2; NATION_COMMENT = c3; __av = c4; }
    NATION_entry(const NATION_entry& other) : NATION_NATIONKEY( other.NATION_NATIONKEY ), NATION_NAME( other.NATION_NAME ), NATION_REGIONKEY( other.NATION_REGIONKEY ), NATION_COMMENT( other.NATION_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE NATION_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { NATION_NATIONKEY = c0; NATION_NAME = c1; NATION_REGIONKEY = c2; NATION_COMMENT = c3;  return *this; }
    FORCE_INLINE NATION_entry& modify1(const STRING_TYPE& c1) { NATION_NAME = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_REGIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NATION_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const NATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NATION_NATIONKEY);
      hash_combine(h, e.NATION_NAME);
      hash_combine(h, e.NATION_REGIONKEY);
      hash_combine(h, e.NATION_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const NATION_entry& x, const NATION_entry& y) {
      return x.NATION_NATIONKEY == y.NATION_NATIONKEY && x.NATION_NAME == y.NATION_NAME && x.NATION_REGIONKEY == y.NATION_REGIONKEY && x.NATION_COMMENT == y.NATION_COMMENT;
    }
  };
  
  struct NATION_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const NATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NATION_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const NATION_entry& x, const NATION_entry& y) {
      return x.NATION_NAME == y.NATION_NAME;
    }
  };
  
  typedef MultiHashMap<NATION_entry,long,
    HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true>,
    HashIndex<NATION_entry,long,NATION_mapkey1_idxfn,false>
  > NATION_map;
  typedef HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true> HashIndex_NATION_map_0123;
  typedef HashIndex<NATION_entry,long,NATION_mapkey1_idxfn,false> HashIndex_NATION_map_1;
  
  struct COUNT_entry {
    STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; long __av; 
    explicit COUNT_entry() { /*S_NAME = ""; S_ADDRESS = ""; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { S_NAME = c0; S_ADDRESS = c1; __av = c2; }
    COUNT_entry(const COUNT_entry& other) : S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { S_NAME = c0; S_ADDRESS = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey01_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey01_idxfn,true> HashIndex_COUNT_map_01;
  
  struct COUNT_mPARTSUPP1_entry {
    long COUNT_mPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; long __av; 
    explicit COUNT_mPARTSUPP1_entry() { /*COUNT_mPARTSUPPPARTSUPP_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; __av = 0L; */ }
    explicit COUNT_mPARTSUPP1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; __av = c3; }
    COUNT_mPARTSUPP1_entry(const COUNT_mPARTSUPP1_entry& other) : COUNT_mPARTSUPPPARTSUPP_SUPPKEY( other.COUNT_mPARTSUPPPARTSUPP_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mPARTSUPP1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2;  return *this; }
    FORCE_INLINE COUNT_mPARTSUPP1_entry& modify0(const long c0) { COUNT_mPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mPARTSUPP1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP1_entry& x, const COUNT_mPARTSUPP1_entry& y) {
      return x.COUNT_mPARTSUPPPARTSUPP_SUPPKEY == y.COUNT_mPARTSUPPPARTSUPP_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS;
    }
  };
  
  struct COUNT_mPARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mPARTSUPP1_entry& x, const COUNT_mPARTSUPP1_entry& y) {
      return x.COUNT_mPARTSUPPPARTSUPP_SUPPKEY == y.COUNT_mPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mPARTSUPP1_entry,long,
    HashIndex<COUNT_mPARTSUPP1_entry,long,COUNT_mPARTSUPP1_mapkey012_idxfn,true>,
    HashIndex<COUNT_mPARTSUPP1_entry,long,COUNT_mPARTSUPP1_mapkey0_idxfn,false>
  > COUNT_mPARTSUPP1_map;
  typedef HashIndex<COUNT_mPARTSUPP1_entry,long,COUNT_mPARTSUPP1_mapkey012_idxfn,true> HashIndex_COUNT_mPARTSUPP1_map_012;
  typedef HashIndex<COUNT_mPARTSUPP1_entry,long,COUNT_mPARTSUPP1_mapkey0_idxfn,false> HashIndex_COUNT_mPARTSUPP1_map_0;
  
  struct COUNT_mSUPPLIER1_entry {
    long COUNT_mSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit COUNT_mSUPPLIER1_entry() { /*COUNT_mSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNT_mSUPPLIER1_entry(const long c0, const long c1) { COUNT_mSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    COUNT_mSUPPLIER1_entry(const COUNT_mSUPPLIER1_entry& other) : COUNT_mSUPPLIERSUPPLIER_NATIONKEY( other.COUNT_mSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mSUPPLIER1_entry& modify(const long c0) { COUNT_mSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER1_entry& x, const COUNT_mSUPPLIER1_entry& y) {
      return x.COUNT_mSUPPLIERSUPPLIER_NATIONKEY == y.COUNT_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mSUPPLIER1_entry,long,
    HashIndex<COUNT_mSUPPLIER1_entry,long,COUNT_mSUPPLIER1_mapkey0_idxfn,true>
  > COUNT_mSUPPLIER1_map;
  typedef HashIndex<COUNT_mSUPPLIER1_entry,long,COUNT_mSUPPLIER1_mapkey0_idxfn,true> HashIndex_COUNT_mSUPPLIER1_map_0;
  
  struct COUNT_mSUPPLIER2_E1_1_entry {
    long PS_PARTKEY; long COUNT_mSUPPLIERSUPPLIER_SUPPKEY; long PS_AVAILQTY; long __av; 
    explicit COUNT_mSUPPLIER2_E1_1_entry() { /*PS_PARTKEY = 0L; COUNT_mSUPPLIERSUPPLIER_SUPPKEY = 0L; PS_AVAILQTY = 0L; __av = 0L; */ }
    explicit COUNT_mSUPPLIER2_E1_1_entry(const long c0, const long c1, const long c2, const long c3) { PS_PARTKEY = c0; COUNT_mSUPPLIERSUPPLIER_SUPPKEY = c1; PS_AVAILQTY = c2; __av = c3; }
    COUNT_mSUPPLIER2_E1_1_entry(const COUNT_mSUPPLIER2_E1_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), COUNT_mSUPPLIERSUPPLIER_SUPPKEY( other.COUNT_mSUPPLIERSUPPLIER_SUPPKEY ), PS_AVAILQTY( other.PS_AVAILQTY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mSUPPLIER2_E1_1_entry& modify(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; COUNT_mSUPPLIERSUPPLIER_SUPPKEY = c1; PS_AVAILQTY = c2;  return *this; }
    FORCE_INLINE COUNT_mSUPPLIER2_E1_1_entry& modify01(const long c0, const long c1) { PS_PARTKEY = c0; COUNT_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE COUNT_mSUPPLIER2_E1_1_entry& modify1(const long c1) { COUNT_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_AVAILQTY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mSUPPLIER2_E1_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER2_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.COUNT_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.PS_AVAILQTY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER2_E1_1_entry& x, const COUNT_mSUPPLIER2_E1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.COUNT_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIERSUPPLIER_SUPPKEY && x.PS_AVAILQTY == y.PS_AVAILQTY;
    }
  };
  
  struct COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER2_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.COUNT_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER2_E1_1_entry& x, const COUNT_mSUPPLIER2_E1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.COUNT_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER2_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNT_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER2_E1_1_entry& x, const COUNT_mSUPPLIER2_E1_1_entry& y) {
      return x.COUNT_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mSUPPLIER2_E1_1_entry,long,
    HashIndex<COUNT_mSUPPLIER2_E1_1_entry,long,COUNT_mSUPPLIER2_E1_1_mapkey012_idxfn,true>,
    HashIndex<COUNT_mSUPPLIER2_E1_1_entry,long,COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn,false>,
    HashIndex<COUNT_mSUPPLIER2_E1_1_entry,long,COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn,false>
  > COUNT_mSUPPLIER2_E1_1_map;
  typedef HashIndex<COUNT_mSUPPLIER2_E1_1_entry,long,COUNT_mSUPPLIER2_E1_1_mapkey012_idxfn,true> HashIndex_COUNT_mSUPPLIER2_E1_1_map_012;
  typedef HashIndex<COUNT_mSUPPLIER2_E1_1_entry,long,COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn,false> HashIndex_COUNT_mSUPPLIER2_E1_1_map_01;
  typedef HashIndex<COUNT_mSUPPLIER2_E1_1_entry,long,COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn,false> HashIndex_COUNT_mSUPPLIER2_E1_1_map_1;
  
  struct COUNT_mSUPPLIER2_E1_1_L1_1_entry {
    long PS_PARTKEY; long COUNT_mSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNT_mSUPPLIER2_E1_1_L1_1_entry() { /*PS_PARTKEY = 0L; COUNT_mSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNT_mSUPPLIER2_E1_1_L1_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { PS_PARTKEY = c0; COUNT_mSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    COUNT_mSUPPLIER2_E1_1_L1_1_entry(const COUNT_mSUPPLIER2_E1_1_L1_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), COUNT_mSUPPLIERSUPPLIER_SUPPKEY( other.COUNT_mSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mSUPPLIER2_E1_1_L1_1_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; COUNT_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNT_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mSUPPLIER2_E1_1_L1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER2_E1_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.COUNT_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER2_E1_1_L1_1_entry& x, const COUNT_mSUPPLIER2_E1_1_L1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.COUNT_mSUPPLIERSUPPLIER_SUPPKEY == y.COUNT_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mSUPPLIER2_E1_1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<COUNT_mSUPPLIER2_E1_1_L1_1_entry,DOUBLE_TYPE,COUNT_mSUPPLIER2_E1_1_L1_1_mapkey01_idxfn,true>
  > COUNT_mSUPPLIER2_E1_1_L1_1_map;
  typedef HashIndex<COUNT_mSUPPLIER2_E1_1_L1_1_entry,DOUBLE_TYPE,COUNT_mSUPPLIER2_E1_1_L1_1_mapkey01_idxfn,true> HashIndex_COUNT_mSUPPLIER2_E1_1_L1_1_map_01;
  
  struct COUNT_mSUPPLIER2_E1_1_E2_1_entry {
    long PS_PARTKEY; long __av; 
    explicit COUNT_mSUPPLIER2_E1_1_E2_1_entry() { /*PS_PARTKEY = 0L; __av = 0L; */ }
    explicit COUNT_mSUPPLIER2_E1_1_E2_1_entry(const long c0, const long c1) { PS_PARTKEY = c0; __av = c1; }
    COUNT_mSUPPLIER2_E1_1_E2_1_entry(const COUNT_mSUPPLIER2_E1_1_E2_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNT_mSUPPLIER2_E1_1_E2_1_entry& modify(const long c0) { PS_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mSUPPLIER2_E1_1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_mSUPPLIER2_E1_1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_mSUPPLIER2_E1_1_E2_1_entry& x, const COUNT_mSUPPLIER2_E1_1_E2_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNT_mSUPPLIER2_E1_1_E2_1_entry,long,
    HashIndex<COUNT_mSUPPLIER2_E1_1_E2_1_entry,long,COUNT_mSUPPLIER2_E1_1_E2_1_mapkey0_idxfn,true>
  > COUNT_mSUPPLIER2_E1_1_E2_1_map;
  typedef HashIndex<COUNT_mSUPPLIER2_E1_1_E2_1_entry,long,COUNT_mSUPPLIER2_E1_1_E2_1_mapkey0_idxfn,true> HashIndex_COUNT_mSUPPLIER2_E1_1_E2_1_map_0;
  
  
  
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
      c2 = Udate(STRING_TYPE("1995-1-1"));
      c1 = Udate(STRING_TYPE("1994-1-1"));
      c3 = STRING_TYPE("CANADA");
      /* regex_t init */
      if(regcomp(&preg1, "^forest.*$", REG_EXTENDED | REG_NOSUB)){
        cerr << "Error compiling regular expression: /^forest.*$/" << endl;
        exit(-1);
      }
    }
  
    ~data_t() {
      regfree(&preg1);
    }
  
    /* Trigger functions for table relations */
    void on_insert_NATION(const long nation_nationkey, const STRING_TYPE nation_name, const long nation_regionkey, const STRING_TYPE nation_comment) {
      NATION_entry e(nation_nationkey, nation_name, nation_regionkey, nation_comment, 1L);
      NATION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_COUNT_mPARTSUPP1_map_0* i1 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0*>(COUNT_mPARTSUPP1.index[1]);
          const HASH_RES_t h5 = COUNT_mPARTSUPP1_mapkey0_idxfn::hash(se13.modify0(lineitem_suppkey));
          HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode* n1 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode*>(i1->slice(se13, h5));
          COUNT_mPARTSUPP1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE s_name = e1->S_NAME;
              STRING_TYPE s_address = e1->S_ADDRESS;
              long v1 = e1->__av;
              long agg1 = 0L;
              DOUBLE_TYPE l1 = ((COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se3.modify(lineitem_partkey,lineitem_suppkey)) + (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? lineitem_quantity : 0.0)) * 0.5);
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_01* i2 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01*>(COUNT_mSUPPLIER2_E1_1.index[1]);
                const HASH_RES_t h1 = COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::hash(se4.modify01(lineitem_partkey, lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode* n2 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode*>(i2->slice(se4, h1));
                COUNT_mSUPPLIER2_E1_1_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    long ps_availqty = e2->PS_AVAILQTY;
                    long v2 = e2->__av;
                    (/*if */(ps_availqty > l1) ? agg1 += v2 : 0L);
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::equals(se4, *e2)); 
                }
              }long agg2 = 0L;
              DOUBLE_TYPE l2 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se5.modify(lineitem_partkey,lineitem_suppkey)) * 0.5);
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_01* i3 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01*>(COUNT_mSUPPLIER2_E1_1.index[1]);
                const HASH_RES_t h2 = COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::hash(se6.modify01(lineitem_partkey, lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode* n3 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode*>(i3->slice(se6, h2));
                COUNT_mSUPPLIER2_E1_1_entry* e3;
               
                if (n3 && (e3 = n3->obj)) {
                  do {                
                    long ps_availqty = e3->PS_AVAILQTY;
                    long v3 = e3->__av;
                    (/*if */(ps_availqty > l2) ? agg2 += v3 : 0L);
                    n3 = n3->nxt;
                  } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::equals(se6, *e3)); 
                }
              }long agg3 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i4 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h3 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se9.modify1(lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n4 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i4->slice(se9, h3));
                COUNT_mSUPPLIER2_E1_1_entry* e4;
               
                if (n4 && (e4 = n4->obj)) {
                  do {                
                    long ps_partkey = e4->PS_PARTKEY;
                    long ps_availqty = e4->PS_AVAILQTY;
                    long v4 = e4->__av;
                    DOUBLE_TYPE l3 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se7.modify(ps_partkey,lineitem_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l3) ? agg3 += (v4 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se8.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n4 = n4->nxt;
                  } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se9, *e4)); 
                }
              }long agg4 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i5 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h4 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se12.modify1(lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n5 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i5->slice(se12, h4));
                COUNT_mSUPPLIER2_E1_1_entry* e5;
               
                if (n5 && (e5 = n5->obj)) {
                  do {                
                    long ps_partkey = e5->PS_PARTKEY;
                    long ps_availqty = e5->PS_AVAILQTY;
                    long v5 = e5->__av;
                    DOUBLE_TYPE l4 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se10.modify(ps_partkey,lineitem_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l4) ? agg4 += (v5 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se11.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n5 = n5->nxt;
                  } while (n5 && (e5 = n5->obj) && h4 == n5->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se12, *e5)); 
                }
              }COUNT.addOrDelOnZero(se1.modify(s_name,s_address),(v1 * (((((COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se2.modify(lineitem_partkey)) != 0 ? 1L : 0L) * (agg1 + (agg2 * -1L))) + agg3) != 0 ? 1L : 0L) + ((agg4 != 0 ? 1L : 0L) * -1L))));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h5 == n1->hash &&  COUNT_mPARTSUPP1_mapkey0_idxfn::equals(se13, *e1)); 
          }
        }(/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mSUPPLIER2_E1_1_L1_1.addOrDelOnZero(se14.modify(lineitem_partkey,lineitem_suppkey),lineitem_quantity) : (void)0);
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_COUNT_mPARTSUPP1_map_0* i6 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0*>(COUNT_mPARTSUPP1.index[1]);
          const HASH_RES_t h10 = COUNT_mPARTSUPP1_mapkey0_idxfn::hash(se27.modify0(lineitem_suppkey));
          HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode* n6 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode*>(i6->slice(se27, h10));
          COUNT_mPARTSUPP1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE s_name = e6->S_NAME;
              STRING_TYPE s_address = e6->S_ADDRESS;
              long v6 = e6->__av;
              long agg5 = 0L;
              DOUBLE_TYPE l5 = ((COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se17.modify(lineitem_partkey,lineitem_suppkey)) + (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? (-1L * lineitem_quantity) : 0.0)) * 0.5);
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_01* i7 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01*>(COUNT_mSUPPLIER2_E1_1.index[1]);
                const HASH_RES_t h6 = COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::hash(se18.modify01(lineitem_partkey, lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode* n7 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode*>(i7->slice(se18, h6));
                COUNT_mSUPPLIER2_E1_1_entry* e7;
               
                if (n7 && (e7 = n7->obj)) {
                  do {                
                    long ps_availqty = e7->PS_AVAILQTY;
                    long v7 = e7->__av;
                    (/*if */(ps_availqty > l5) ? agg5 += v7 : 0L);
                    n7 = n7->nxt;
                  } while (n7 && (e7 = n7->obj) && h6 == n7->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::equals(se18, *e7)); 
                }
              }long agg6 = 0L;
              DOUBLE_TYPE l6 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se19.modify(lineitem_partkey,lineitem_suppkey)) * 0.5);
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_01* i8 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01*>(COUNT_mSUPPLIER2_E1_1.index[1]);
                const HASH_RES_t h7 = COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::hash(se20.modify01(lineitem_partkey, lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode* n8 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_01::IdxNode*>(i8->slice(se20, h7));
                COUNT_mSUPPLIER2_E1_1_entry* e8;
               
                if (n8 && (e8 = n8->obj)) {
                  do {                
                    long ps_availqty = e8->PS_AVAILQTY;
                    long v8 = e8->__av;
                    (/*if */(ps_availqty > l6) ? agg6 += v8 : 0L);
                    n8 = n8->nxt;
                  } while (n8 && (e8 = n8->obj) && h7 == n8->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey01_idxfn::equals(se20, *e8)); 
                }
              }long agg7 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i9 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h8 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se23.modify1(lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n9 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i9->slice(se23, h8));
                COUNT_mSUPPLIER2_E1_1_entry* e9;
               
                if (n9 && (e9 = n9->obj)) {
                  do {                
                    long ps_partkey = e9->PS_PARTKEY;
                    long ps_availqty = e9->PS_AVAILQTY;
                    long v9 = e9->__av;
                    DOUBLE_TYPE l7 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se21.modify(ps_partkey,lineitem_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l7) ? agg7 += (v9 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se22.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n9 = n9->nxt;
                  } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se23, *e9)); 
                }
              }long agg8 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i10 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h9 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se26.modify1(lineitem_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n10 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i10->slice(se26, h9));
                COUNT_mSUPPLIER2_E1_1_entry* e10;
               
                if (n10 && (e10 = n10->obj)) {
                  do {                
                    long ps_partkey = e10->PS_PARTKEY;
                    long ps_availqty = e10->PS_AVAILQTY;
                    long v10 = e10->__av;
                    DOUBLE_TYPE l8 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se24.modify(ps_partkey,lineitem_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l8) ? agg8 += (v10 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se25.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n10 = n10->nxt;
                  } while (n10 && (e10 = n10->obj) && h9 == n10->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se26, *e10)); 
                }
              }COUNT.addOrDelOnZero(se15.modify(s_name,s_address),(v6 * (((((COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se16.modify(lineitem_partkey)) != 0 ? 1L : 0L) * (agg5 + (agg6 * -1L))) + agg7) != 0 ? 1L : 0L) + ((agg8 != 0 ? 1L : 0L) * -1L))));
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h10 == n6->hash &&  COUNT_mPARTSUPP1_mapkey0_idxfn::equals(se27, *e6)); 
          }
        }(/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? COUNT_mSUPPLIER2_E1_1_L1_1.addOrDelOnZero(se28.modify(lineitem_partkey,lineitem_suppkey),(-1L * lineitem_quantity)) : (void)0);
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(0L != Upreg_match(preg1,part_name)) ? COUNT_mSUPPLIER2_E1_1_E2_1.addOrDelOnZero(se29.modify(part_partkey),1L) : (void)0);
        COUNT.clear();
        {  // foreach
          const HashIndex_COUNT_mPARTSUPP1_map_012* i11 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_012*>(COUNT_mPARTSUPP1.index[0]);
          HashIndex_COUNT_mPARTSUPP1_map_012::IdxNode* n11; 
          COUNT_mPARTSUPP1_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long s_suppkey = e11->COUNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE s_name = e11->S_NAME;
                STRING_TYPE s_address = e11->S_ADDRESS;
                long v11 = e11->__av;
                long agg9 = 0L;
                { //slice 
                  const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i12 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                  const HASH_RES_t h11 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se33.modify1(s_suppkey));
                  HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n12 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i12->slice(se33, h11));
                  COUNT_mSUPPLIER2_E1_1_entry* e12;
                 
                  if (n12 && (e12 = n12->obj)) {
                    do {                
                      long ps_partkey = e12->PS_PARTKEY;
                      long ps_availqty = e12->PS_AVAILQTY;
                      long v12 = e12->__av;
                      DOUBLE_TYPE l9 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se31.modify(ps_partkey,s_suppkey)) * 0.5);
                      (/*if */(ps_availqty > l9) ? agg9 += (v12 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se32.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                      n12 = n12->nxt;
                    } while (n12 && (e12 = n12->obj) && h11 == n12->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se33, *e12)); 
                  }
                }COUNT.addOrDelOnZero(se30.modify(s_name,s_address),(v11 * (agg9 != 0 ? 1L : 0L)));
              n11 = n11->nxt;
            }
          }
        }
      }
    }
    void on_delete_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(0L != Upreg_match(preg1,part_name)) ? COUNT_mSUPPLIER2_E1_1_E2_1.addOrDelOnZero(se34.modify(part_partkey),-1L) : (void)0);
        COUNT.clear();
        {  // foreach
          const HashIndex_COUNT_mPARTSUPP1_map_012* i13 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_012*>(COUNT_mPARTSUPP1.index[0]);
          HashIndex_COUNT_mPARTSUPP1_map_012::IdxNode* n13; 
          COUNT_mPARTSUPP1_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long s_suppkey = e13->COUNT_mPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE s_name = e13->S_NAME;
                STRING_TYPE s_address = e13->S_ADDRESS;
                long v13 = e13->__av;
                long agg10 = 0L;
                { //slice 
                  const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i14 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                  const HASH_RES_t h12 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se38.modify1(s_suppkey));
                  HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n14 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i14->slice(se38, h12));
                  COUNT_mSUPPLIER2_E1_1_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      long ps_partkey = e14->PS_PARTKEY;
                      long ps_availqty = e14->PS_AVAILQTY;
                      long v14 = e14->__av;
                      DOUBLE_TYPE l10 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se36.modify(ps_partkey,s_suppkey)) * 0.5);
                      (/*if */(ps_availqty > l10) ? agg10 += (v14 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se37.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h12 == n14->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se38, *e14)); 
                  }
                }COUNT.addOrDelOnZero(se35.modify(s_name,s_address),(v13 * (agg10 != 0 ? 1L : 0L)));
              n13 = n13->nxt;
            }
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg11 = 0L;
        { //slice 
          const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i15 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
          const HASH_RES_t h13 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se43.modify1(supplier_suppkey));
          HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n15 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i15->slice(se43, h13));
          COUNT_mSUPPLIER2_E1_1_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              long ps_partkey = e15->PS_PARTKEY;
              long ps_availqty = e15->PS_AVAILQTY;
              long v15 = e15->__av;
              DOUBLE_TYPE l11 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se41.modify(ps_partkey,supplier_suppkey)) * 0.5);
              (/*if */(ps_availqty > l11) ? agg11 += (v15 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se42.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h13 == n15->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se43, *e15)); 
          }
        }COUNT.addOrDelOnZero(se39.modify(supplier_name,supplier_address),(COUNT_mSUPPLIER1.getValueOrDefault(se40.modify(supplier_nationkey)) * (agg11 != 0 ? 1L : 0L)));
        COUNT_mPARTSUPP1.addOrDelOnZero(se44.modify(supplier_suppkey,supplier_name,supplier_address),COUNT_mSUPPLIER1.getValueOrDefault(se45.modify(supplier_nationkey)));
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg12 = 0L;
        { //slice 
          const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i16 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
          const HASH_RES_t h14 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se50.modify1(supplier_suppkey));
          HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n16 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i16->slice(se50, h14));
          COUNT_mSUPPLIER2_E1_1_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              long ps_partkey = e16->PS_PARTKEY;
              long ps_availqty = e16->PS_AVAILQTY;
              long v16 = e16->__av;
              DOUBLE_TYPE l12 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se48.modify(ps_partkey,supplier_suppkey)) * 0.5);
              (/*if */(ps_availqty > l12) ? agg12 += (v16 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se49.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h14 == n16->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se50, *e16)); 
          }
        }COUNT.addOrDelOnZero(se46.modify(supplier_name,supplier_address),(COUNT_mSUPPLIER1.getValueOrDefault(se47.modify(supplier_nationkey)) * ((agg12 != 0 ? 1L : 0L) * -1L)));
        COUNT_mPARTSUPP1.addOrDelOnZero(se51.modify(supplier_suppkey,supplier_name,supplier_address),(COUNT_mSUPPLIER1.getValueOrDefault(se52.modify(supplier_nationkey)) * -1L));
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_COUNT_mPARTSUPP1_map_0* i17 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0*>(COUNT_mPARTSUPP1.index[1]);
          const HASH_RES_t h17 = COUNT_mPARTSUPP1_mapkey0_idxfn::hash(se62.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode* n17 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode*>(i17->slice(se62, h17));
          COUNT_mPARTSUPP1_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              STRING_TYPE s_name = e17->S_NAME;
              STRING_TYPE s_address = e17->S_ADDRESS;
              long v17 = e17->__av;
              long agg13 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i18 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h15 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se56.modify1(partsupp_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n18 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i18->slice(se56, h15));
                COUNT_mSUPPLIER2_E1_1_entry* e18;
               
                if (n18 && (e18 = n18->obj)) {
                  do {                
                    long ps_partkey = e18->PS_PARTKEY;
                    long ps_availqty = e18->PS_AVAILQTY;
                    long v18 = e18->__av;
                    DOUBLE_TYPE l13 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se54.modify(ps_partkey,partsupp_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l13) ? agg13 += (v18 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se55.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n18 = n18->nxt;
                  } while (n18 && (e18 = n18->obj) && h15 == n18->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se56, *e18)); 
                }
              }long agg14 = 0L;
              DOUBLE_TYPE l14 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se57.modify(partsupp_partkey,partsupp_suppkey)) * 0.5);
              (/*if */(partsupp_availqty > l14) ? agg14 += 1L : 0L);
              long agg15 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i19 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h16 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se61.modify1(partsupp_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n19 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i19->slice(se61, h16));
                COUNT_mSUPPLIER2_E1_1_entry* e19;
               
                if (n19 && (e19 = n19->obj)) {
                  do {                
                    long ps_partkey = e19->PS_PARTKEY;
                    long ps_availqty = e19->PS_AVAILQTY;
                    long v19 = e19->__av;
                    DOUBLE_TYPE l15 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se59.modify(ps_partkey,partsupp_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l15) ? agg15 += (v19 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se60.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n19 = n19->nxt;
                  } while (n19 && (e19 = n19->obj) && h16 == n19->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se61, *e19)); 
                }
              }COUNT.addOrDelOnZero(se53.modify(s_name,s_address),(v17 * (((agg13 + (agg14 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se58.modify(partsupp_partkey)) != 0 ? 1L : 0L))) != 0 ? 1L : 0L) + ((agg15 != 0 ? 1L : 0L) * -1L))));
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h17 == n17->hash &&  COUNT_mPARTSUPP1_mapkey0_idxfn::equals(se62, *e17)); 
          }
        }COUNT_mSUPPLIER2_E1_1.addOrDelOnZero(se63.modify(partsupp_partkey,partsupp_suppkey,partsupp_availqty),1L);
      }
    }
    void on_delete_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_COUNT_mPARTSUPP1_map_0* i20 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0*>(COUNT_mPARTSUPP1.index[1]);
          const HASH_RES_t h20 = COUNT_mPARTSUPP1_mapkey0_idxfn::hash(se73.modify0(partsupp_suppkey));
          HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode* n20 = static_cast<HashIndex_COUNT_mPARTSUPP1_map_0::IdxNode*>(i20->slice(se73, h20));
          COUNT_mPARTSUPP1_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              STRING_TYPE s_name = e20->S_NAME;
              STRING_TYPE s_address = e20->S_ADDRESS;
              long v20 = e20->__av;
              long agg16 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i21 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h18 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se67.modify1(partsupp_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n21 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i21->slice(se67, h18));
                COUNT_mSUPPLIER2_E1_1_entry* e21;
               
                if (n21 && (e21 = n21->obj)) {
                  do {                
                    long ps_partkey = e21->PS_PARTKEY;
                    long ps_availqty = e21->PS_AVAILQTY;
                    long v21 = e21->__av;
                    DOUBLE_TYPE l16 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se65.modify(ps_partkey,partsupp_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l16) ? agg16 += (v21 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se66.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n21 = n21->nxt;
                  } while (n21 && (e21 = n21->obj) && h18 == n21->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se67, *e21)); 
                }
              }long agg17 = 0L;
              DOUBLE_TYPE l17 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se68.modify(partsupp_partkey,partsupp_suppkey)) * 0.5);
              (/*if */(partsupp_availqty > l17) ? agg17 += 1L : 0L);
              long agg18 = 0L;
              { //slice 
                const HashIndex_COUNT_mSUPPLIER2_E1_1_map_1* i22 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1*>(COUNT_mSUPPLIER2_E1_1.index[2]);
                const HASH_RES_t h19 = COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::hash(se72.modify1(partsupp_suppkey));
                HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode* n22 = static_cast<HashIndex_COUNT_mSUPPLIER2_E1_1_map_1::IdxNode*>(i22->slice(se72, h19));
                COUNT_mSUPPLIER2_E1_1_entry* e22;
               
                if (n22 && (e22 = n22->obj)) {
                  do {                
                    long ps_partkey = e22->PS_PARTKEY;
                    long ps_availqty = e22->PS_AVAILQTY;
                    long v22 = e22->__av;
                    DOUBLE_TYPE l18 = (COUNT_mSUPPLIER2_E1_1_L1_1.getValueOrDefault(se70.modify(ps_partkey,partsupp_suppkey)) * 0.5);
                    (/*if */(ps_availqty > l18) ? agg18 += (v22 * (COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se71.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                    n22 = n22->nxt;
                  } while (n22 && (e22 = n22->obj) && h19 == n22->hash &&  COUNT_mSUPPLIER2_E1_1_mapkey1_idxfn::equals(se72, *e22)); 
                }
              }COUNT.addOrDelOnZero(se64.modify(s_name,s_address),(v20 * (((agg16 + (agg17 * ((COUNT_mSUPPLIER2_E1_1_E2_1.getValueOrDefault(se69.modify(partsupp_partkey)) != 0 ? 1L : 0L) * -1L))) != 0 ? 1L : 0L) + ((agg18 != 0 ? 1L : 0L) * -1L))));
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h20 == n20->hash &&  COUNT_mPARTSUPP1_mapkey0_idxfn::equals(se73, *e20)); 
          }
        }COUNT_mSUPPLIER2_E1_1.addOrDelOnZero(se74.modify(partsupp_partkey,partsupp_suppkey,partsupp_availqty),-1L);
      }
    }
    void on_system_ready_event() {
      {  
        COUNT_mSUPPLIER1.clear();
        STRING_TYPE l19 = c3;
        { //slice 
          const HashIndex_NATION_map_1* i23 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h21 = NATION_mapkey1_idxfn::hash(se76.modify1(l19));
          HashIndex_NATION_map_1::IdxNode* n23 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i23->slice(se76, h21));
          NATION_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              long count_msuppliersupplier_nationkey = e23->NATION_NATIONKEY;
              long n_regionkey = e23->NATION_REGIONKEY;
              STRING_TYPE n_comment = e23->NATION_COMMENT;
              long v23 = e23->__av;
              COUNT_mSUPPLIER1.addOrDelOnZero(se75.modify(count_msuppliersupplier_nationkey),v23);
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h21 == n23->hash &&  NATION_mapkey1_idxfn::equals(se76, *e23)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNT_entry se1;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se2;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se3;
    COUNT_mSUPPLIER2_E1_1_entry se4;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se5;
    COUNT_mSUPPLIER2_E1_1_entry se6;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se7;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se8;
    COUNT_mSUPPLIER2_E1_1_entry se9;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se10;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se11;
    COUNT_mSUPPLIER2_E1_1_entry se12;
    COUNT_mPARTSUPP1_entry se13;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se14;
    COUNT_entry se15;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se16;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se17;
    COUNT_mSUPPLIER2_E1_1_entry se18;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se19;
    COUNT_mSUPPLIER2_E1_1_entry se20;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se21;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se22;
    COUNT_mSUPPLIER2_E1_1_entry se23;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se24;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se25;
    COUNT_mSUPPLIER2_E1_1_entry se26;
    COUNT_mPARTSUPP1_entry se27;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se28;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se29;
    COUNT_entry se30;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se31;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se32;
    COUNT_mSUPPLIER2_E1_1_entry se33;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se34;
    COUNT_entry se35;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se36;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se37;
    COUNT_mSUPPLIER2_E1_1_entry se38;
    COUNT_entry se39;
    COUNT_mSUPPLIER1_entry se40;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se41;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se42;
    COUNT_mSUPPLIER2_E1_1_entry se43;
    COUNT_mPARTSUPP1_entry se44;
    COUNT_mSUPPLIER1_entry se45;
    COUNT_entry se46;
    COUNT_mSUPPLIER1_entry se47;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se48;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se49;
    COUNT_mSUPPLIER2_E1_1_entry se50;
    COUNT_mPARTSUPP1_entry se51;
    COUNT_mSUPPLIER1_entry se52;
    COUNT_entry se53;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se54;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se55;
    COUNT_mSUPPLIER2_E1_1_entry se56;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se57;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se58;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se59;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se60;
    COUNT_mSUPPLIER2_E1_1_entry se61;
    COUNT_mPARTSUPP1_entry se62;
    COUNT_mSUPPLIER2_E1_1_entry se63;
    COUNT_entry se64;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se65;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se66;
    COUNT_mSUPPLIER2_E1_1_entry se67;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se68;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se69;
    COUNT_mSUPPLIER2_E1_1_L1_1_entry se70;
    COUNT_mSUPPLIER2_E1_1_E2_1_entry se71;
    COUNT_mSUPPLIER2_E1_1_entry se72;
    COUNT_mPARTSUPP1_entry se73;
    COUNT_mSUPPLIER2_E1_1_entry se74;
    COUNT_mSUPPLIER1_entry se75;
    NATION_entry se76;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    COUNT_mPARTSUPP1_map COUNT_mPARTSUPP1;
    COUNT_mSUPPLIER1_map COUNT_mSUPPLIER1;
    COUNT_mSUPPLIER2_E1_1_map COUNT_mSUPPLIER2_E1_1;
    COUNT_mSUPPLIER2_E1_1_L1_1_map COUNT_mSUPPLIER2_E1_1_L1_1;
    COUNT_mSUPPLIER2_E1_1_E2_1_map COUNT_mSUPPLIER2_E1_1_E2_1;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
