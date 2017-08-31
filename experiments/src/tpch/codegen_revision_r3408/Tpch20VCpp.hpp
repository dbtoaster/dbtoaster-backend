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
  
  struct COUNTPARTSUPP1_entry {
    long COUNTPARTSUPPPARTSUPP_SUPPKEY; STRING_TYPE S_NAME; STRING_TYPE S_ADDRESS; long __av; 
    explicit COUNTPARTSUPP1_entry() { /*COUNTPARTSUPPPARTSUPP_SUPPKEY = 0L; S_NAME = ""; S_ADDRESS = ""; __av = 0L; */ }
    explicit COUNTPARTSUPP1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2; __av = c3; }
    COUNTPARTSUPP1_entry(const COUNTPARTSUPP1_entry& other) : COUNTPARTSUPPPARTSUPP_SUPPKEY( other.COUNTPARTSUPPPARTSUPP_SUPPKEY ), S_NAME( other.S_NAME ), S_ADDRESS( other.S_ADDRESS ), __av( other.__av ) {}
    FORCE_INLINE COUNTPARTSUPP1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0; S_NAME = c1; S_ADDRESS = c2;  return *this; }
    FORCE_INLINE COUNTPARTSUPP1_entry& modify0(const long c0) { COUNTPARTSUPPPARTSUPP_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTPARTSUPPPARTSUPP_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_ADDRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTPARTSUPP1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPPPARTSUPP_SUPPKEY);
      hash_combine(h, e.S_NAME);
      hash_combine(h, e.S_ADDRESS);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_entry& x, const COUNTPARTSUPP1_entry& y) {
      return x.COUNTPARTSUPPPARTSUPP_SUPPKEY == y.COUNTPARTSUPPPARTSUPP_SUPPKEY && x.S_NAME == y.S_NAME && x.S_ADDRESS == y.S_ADDRESS;
    }
  };
  
  struct COUNTPARTSUPP1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTPARTSUPP1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTPARTSUPPPARTSUPP_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTPARTSUPP1_entry& x, const COUNTPARTSUPP1_entry& y) {
      return x.COUNTPARTSUPPPARTSUPP_SUPPKEY == y.COUNTPARTSUPPPARTSUPP_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTPARTSUPP1_entry,long,
    HashIndex<COUNTPARTSUPP1_entry,long,COUNTPARTSUPP1_mapkey012_idxfn,true>,
    HashIndex<COUNTPARTSUPP1_entry,long,COUNTPARTSUPP1_mapkey0_idxfn,false>
  > COUNTPARTSUPP1_map;
  typedef HashIndex<COUNTPARTSUPP1_entry,long,COUNTPARTSUPP1_mapkey012_idxfn,true> HashIndex_COUNTPARTSUPP1_map_012;
  typedef HashIndex<COUNTPARTSUPP1_entry,long,COUNTPARTSUPP1_mapkey0_idxfn,false> HashIndex_COUNTPARTSUPP1_map_0;
  
  struct COUNTSUPPLIER1_entry {
    long COUNTSUPPLIERSUPPLIER_NATIONKEY; long __av; 
    explicit COUNTSUPPLIER1_entry() { /*COUNTSUPPLIERSUPPLIER_NATIONKEY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER1_entry(const long c0, const long c1) { COUNTSUPPLIERSUPPLIER_NATIONKEY = c0; __av = c1; }
    COUNTSUPPLIER1_entry(const COUNTSUPPLIER1_entry& other) : COUNTSUPPLIERSUPPLIER_NATIONKEY( other.COUNTSUPPLIERSUPPLIER_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER1_entry& modify(const long c0) { COUNTSUPPLIERSUPPLIER_NATIONKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER1_entry& x, const COUNTSUPPLIER1_entry& y) {
      return x.COUNTSUPPLIERSUPPLIER_NATIONKEY == y.COUNTSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER1_entry,long,
    HashIndex<COUNTSUPPLIER1_entry,long,COUNTSUPPLIER1_mapkey0_idxfn,true>
  > COUNTSUPPLIER1_map;
  typedef HashIndex<COUNTSUPPLIER1_entry,long,COUNTSUPPLIER1_mapkey0_idxfn,true> HashIndex_COUNTSUPPLIER1_map_0;
  
  struct COUNTSUPPLIER2_E1_1_entry {
    long PS_PARTKEY; long COUNTSUPPLIERSUPPLIER_SUPPKEY; long PS_AVAILQTY; long __av; 
    explicit COUNTSUPPLIER2_E1_1_entry() { /*PS_PARTKEY = 0L; COUNTSUPPLIERSUPPLIER_SUPPKEY = 0L; PS_AVAILQTY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER2_E1_1_entry(const long c0, const long c1, const long c2, const long c3) { PS_PARTKEY = c0; COUNTSUPPLIERSUPPLIER_SUPPKEY = c1; PS_AVAILQTY = c2; __av = c3; }
    COUNTSUPPLIER2_E1_1_entry(const COUNTSUPPLIER2_E1_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), COUNTSUPPLIERSUPPLIER_SUPPKEY( other.COUNTSUPPLIERSUPPLIER_SUPPKEY ), PS_AVAILQTY( other.PS_AVAILQTY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER2_E1_1_entry& modify(const long c0, const long c1, const long c2) { PS_PARTKEY = c0; COUNTSUPPLIERSUPPLIER_SUPPKEY = c1; PS_AVAILQTY = c2;  return *this; }
    FORCE_INLINE COUNTSUPPLIER2_E1_1_entry& modify01(const long c0, const long c1) { PS_PARTKEY = c0; COUNTSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    FORCE_INLINE COUNTSUPPLIER2_E1_1_entry& modify1(const long c1) { COUNTSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_AVAILQTY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER2_E1_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER2_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.COUNTSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.PS_AVAILQTY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER2_E1_1_entry& x, const COUNTSUPPLIER2_E1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.COUNTSUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIERSUPPLIER_SUPPKEY && x.PS_AVAILQTY == y.PS_AVAILQTY;
    }
  };
  
  struct COUNTSUPPLIER2_E1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER2_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.COUNTSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER2_E1_1_entry& x, const COUNTSUPPLIER2_E1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.COUNTSUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  struct COUNTSUPPLIER2_E1_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER2_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER2_E1_1_entry& x, const COUNTSUPPLIER2_E1_1_entry& y) {
      return x.COUNTSUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER2_E1_1_entry,long,
    HashIndex<COUNTSUPPLIER2_E1_1_entry,long,COUNTSUPPLIER2_E1_1_mapkey012_idxfn,true>,
    HashIndex<COUNTSUPPLIER2_E1_1_entry,long,COUNTSUPPLIER2_E1_1_mapkey01_idxfn,false>,
    HashIndex<COUNTSUPPLIER2_E1_1_entry,long,COUNTSUPPLIER2_E1_1_mapkey1_idxfn,false>
  > COUNTSUPPLIER2_E1_1_map;
  typedef HashIndex<COUNTSUPPLIER2_E1_1_entry,long,COUNTSUPPLIER2_E1_1_mapkey012_idxfn,true> HashIndex_COUNTSUPPLIER2_E1_1_map_012;
  typedef HashIndex<COUNTSUPPLIER2_E1_1_entry,long,COUNTSUPPLIER2_E1_1_mapkey01_idxfn,false> HashIndex_COUNTSUPPLIER2_E1_1_map_01;
  typedef HashIndex<COUNTSUPPLIER2_E1_1_entry,long,COUNTSUPPLIER2_E1_1_mapkey1_idxfn,false> HashIndex_COUNTSUPPLIER2_E1_1_map_1;
  
  struct COUNTSUPPLIER2_E1_1_L1_1_entry {
    long PS_PARTKEY; long COUNTSUPPLIERSUPPLIER_SUPPKEY; DOUBLE_TYPE __av; 
    explicit COUNTSUPPLIER2_E1_1_L1_1_entry() { /*PS_PARTKEY = 0L; COUNTSUPPLIERSUPPLIER_SUPPKEY = 0L; __av = 0.0; */ }
    explicit COUNTSUPPLIER2_E1_1_L1_1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { PS_PARTKEY = c0; COUNTSUPPLIERSUPPLIER_SUPPKEY = c1; __av = c2; }
    COUNTSUPPLIER2_E1_1_L1_1_entry(const COUNTSUPPLIER2_E1_1_L1_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), COUNTSUPPLIERSUPPLIER_SUPPKEY( other.COUNTSUPPLIERSUPPLIER_SUPPKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER2_E1_1_L1_1_entry& modify(const long c0, const long c1) { PS_PARTKEY = c0; COUNTSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER2_E1_1_L1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER2_E1_1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      hash_combine(h, e.COUNTSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER2_E1_1_L1_1_entry& x, const COUNTSUPPLIER2_E1_1_L1_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY && x.COUNTSUPPLIERSUPPLIER_SUPPKEY == y.COUNTSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER2_E1_1_L1_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTSUPPLIER2_E1_1_L1_1_entry,DOUBLE_TYPE,COUNTSUPPLIER2_E1_1_L1_1_mapkey01_idxfn,true>
  > COUNTSUPPLIER2_E1_1_L1_1_map;
  typedef HashIndex<COUNTSUPPLIER2_E1_1_L1_1_entry,DOUBLE_TYPE,COUNTSUPPLIER2_E1_1_L1_1_mapkey01_idxfn,true> HashIndex_COUNTSUPPLIER2_E1_1_L1_1_map_01;
  
  struct COUNTSUPPLIER2_E1_1_E2_1_entry {
    long PS_PARTKEY; long __av; 
    explicit COUNTSUPPLIER2_E1_1_E2_1_entry() { /*PS_PARTKEY = 0L; __av = 0L; */ }
    explicit COUNTSUPPLIER2_E1_1_E2_1_entry(const long c0, const long c1) { PS_PARTKEY = c0; __av = c1; }
    COUNTSUPPLIER2_E1_1_E2_1_entry(const COUNTSUPPLIER2_E1_1_E2_1_entry& other) : PS_PARTKEY( other.PS_PARTKEY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSUPPLIER2_E1_1_E2_1_entry& modify(const long c0) { PS_PARTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PS_PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSUPPLIER2_E1_1_E2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSUPPLIER2_E1_1_E2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PS_PARTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSUPPLIER2_E1_1_E2_1_entry& x, const COUNTSUPPLIER2_E1_1_E2_1_entry& y) {
      return x.PS_PARTKEY == y.PS_PARTKEY;
    }
  };
  
  typedef MultiHashMap<COUNTSUPPLIER2_E1_1_E2_1_entry,long,
    HashIndex<COUNTSUPPLIER2_E1_1_E2_1_entry,long,COUNTSUPPLIER2_E1_1_E2_1_mapkey0_idxfn,true>
  > COUNTSUPPLIER2_E1_1_E2_1_map;
  typedef HashIndex<COUNTSUPPLIER2_E1_1_E2_1_entry,long,COUNTSUPPLIER2_E1_1_E2_1_mapkey0_idxfn,true> HashIndex_COUNTSUPPLIER2_E1_1_E2_1_map_0;
  
  
  
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
        long agg1 = 0L;
        DOUBLE_TYPE l1 = ((COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se2.modify(lineitem_partkey,lineitem_suppkey)) + (/*if */(lineitem_shipdate >= c1 && c2 > lineitem_shipdate) ? lineitem_quantity : 0.0)) * 0.5);
        { //slice 
          const HashIndex_COUNTSUPPLIER2_E1_1_map_01* i1 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_01*>(COUNTSUPPLIER2_E1_1.index[1]);
          const HASH_RES_t h1 = COUNTSUPPLIER2_E1_1_mapkey01_idxfn::hash(se3.modify01(lineitem_partkey, lineitem_suppkey));
          HashIndex_COUNTSUPPLIER2_E1_1_map_01::IdxNode* n1 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_01::IdxNode*>(i1->slice(se3, h1));
          COUNTSUPPLIER2_E1_1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long ps_availqty = e1->PS_AVAILQTY;
              long v1 = e1->__av;
              (/*if */(ps_availqty > l1) ? agg1 += v1 : 0L);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  COUNTSUPPLIER2_E1_1_mapkey01_idxfn::equals(se3, *e1)); 
          }
        }long agg2 = 0L;
        DOUBLE_TYPE l2 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se4.modify(lineitem_partkey,lineitem_suppkey)) * 0.5);
        { //slice 
          const HashIndex_COUNTSUPPLIER2_E1_1_map_01* i2 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_01*>(COUNTSUPPLIER2_E1_1.index[1]);
          const HASH_RES_t h2 = COUNTSUPPLIER2_E1_1_mapkey01_idxfn::hash(se5.modify01(lineitem_partkey, lineitem_suppkey));
          HashIndex_COUNTSUPPLIER2_E1_1_map_01::IdxNode* n2 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_01::IdxNode*>(i2->slice(se5, h2));
          COUNTSUPPLIER2_E1_1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long ps_availqty = e2->PS_AVAILQTY;
              long v2 = e2->__av;
              (/*if */(ps_availqty > l2) ? agg2 += v2 : 0L);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  COUNTSUPPLIER2_E1_1_mapkey01_idxfn::equals(se5, *e2)); 
          }
        }long agg3 = 0L;
        { //slice 
          const HashIndex_COUNTSUPPLIER2_E1_1_map_1* i3 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1*>(COUNTSUPPLIER2_E1_1.index[2]);
          const HASH_RES_t h3 = COUNTSUPPLIER2_E1_1_mapkey1_idxfn::hash(se9.modify1(lineitem_suppkey));
          HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode* n3 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode*>(i3->slice(se9, h3));
          COUNTSUPPLIER2_E1_1_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long ps_partkey = e3->PS_PARTKEY;
              long ps_availqty = e3->PS_AVAILQTY;
              long v3 = e3->__av;
              DOUBLE_TYPE l3 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se7.modify(ps_partkey,lineitem_suppkey)) * 0.5);
              (/*if */(ps_availqty > l3) ? agg3 += (v3 * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se8.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  COUNTSUPPLIER2_E1_1_mapkey1_idxfn::equals(se9, *e3)); 
          }
        }long agg4 = 0L;
        { //slice 
          const HashIndex_COUNTSUPPLIER2_E1_1_map_1* i4 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1*>(COUNTSUPPLIER2_E1_1.index[2]);
          const HASH_RES_t h4 = COUNTSUPPLIER2_E1_1_mapkey1_idxfn::hash(se12.modify1(lineitem_suppkey));
          HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode* n4 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode*>(i4->slice(se12, h4));
          COUNTSUPPLIER2_E1_1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long ps_partkey = e4->PS_PARTKEY;
              long ps_availqty = e4->PS_AVAILQTY;
              long v4 = e4->__av;
              DOUBLE_TYPE l4 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se10.modify(ps_partkey,lineitem_suppkey)) * 0.5);
              (/*if */(ps_availqty > l4) ? agg4 += (v4 * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se11.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  COUNTSUPPLIER2_E1_1_mapkey1_idxfn::equals(se12, *e4)); 
          }
        }{ //slice 
          const HashIndex_COUNTPARTSUPP1_map_0* i5 = static_cast<HashIndex_COUNTPARTSUPP1_map_0*>(COUNTPARTSUPP1.index[1]);
          const HASH_RES_t h5 = COUNTPARTSUPP1_mapkey0_idxfn::hash(se13.modify0(lineitem_suppkey));
          HashIndex_COUNTPARTSUPP1_map_0::IdxNode* n5 = static_cast<HashIndex_COUNTPARTSUPP1_map_0::IdxNode*>(i5->slice(se13, h5));
          COUNTPARTSUPP1_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE s_name = e5->S_NAME;
              STRING_TYPE s_address = e5->S_ADDRESS;
              long v5 = e5->__av;
              COUNT.addOrDelOnZero(se1.modify(s_name,s_address),((((((agg1 + (agg2 * -1L)) * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se6.modify(lineitem_partkey)) != 0 ? 1L : 0L)) + agg3) != 0 ? 1L : 0L) + ((agg4 != 0 ? 1L : 0L) * -1L)) * v5));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  COUNTPARTSUPP1_mapkey0_idxfn::equals(se13, *e5)); 
          }
        }(/*if */(c2 > lineitem_shipdate && lineitem_shipdate >= c1) ? COUNTSUPPLIER2_E1_1_L1_1.addOrDelOnZero(se14.modify(lineitem_partkey,lineitem_suppkey),lineitem_quantity) : (void)0);
      }
    }
    void on_insert_PART(const long part_partkey, const STRING_TYPE& part_name, const STRING_TYPE& part_mfgr, const STRING_TYPE& part_brand, const STRING_TYPE& part_type, const long part_size, const STRING_TYPE& part_container, const DOUBLE_TYPE part_retailprice, const STRING_TYPE& part_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(0L != Upreg_match(preg1,part_name)) ? COUNTSUPPLIER2_E1_1_E2_1.addOrDelOnZero(se15.modify(part_partkey),1L) : (void)0);
        COUNT.clear();
        {  // foreach
          const HashIndex_COUNTPARTSUPP1_map_012* i6 = static_cast<HashIndex_COUNTPARTSUPP1_map_012*>(COUNTPARTSUPP1.index[0]);
          HashIndex_COUNTPARTSUPP1_map_012::IdxNode* n6; 
          COUNTPARTSUPP1_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long s_suppkey = e6->COUNTPARTSUPPPARTSUPP_SUPPKEY;
                STRING_TYPE s_name = e6->S_NAME;
                STRING_TYPE s_address = e6->S_ADDRESS;
                long v6 = e6->__av;
                long agg5 = 0L;
                { //slice 
                  const HashIndex_COUNTSUPPLIER2_E1_1_map_1* i7 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1*>(COUNTSUPPLIER2_E1_1.index[2]);
                  const HASH_RES_t h6 = COUNTSUPPLIER2_E1_1_mapkey1_idxfn::hash(se19.modify1(s_suppkey));
                  HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode* n7 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode*>(i7->slice(se19, h6));
                  COUNTSUPPLIER2_E1_1_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      long ps_partkey = e7->PS_PARTKEY;
                      long ps_availqty = e7->PS_AVAILQTY;
                      long v7 = e7->__av;
                      DOUBLE_TYPE l5 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se17.modify(ps_partkey,s_suppkey)) * 0.5);
                      (/*if */(ps_availqty > l5) ? agg5 += (v7 * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se18.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h6 == n7->hash &&  COUNTSUPPLIER2_E1_1_mapkey1_idxfn::equals(se19, *e7)); 
                  }
                }COUNT.addOrDelOnZero(se16.modify(s_name,s_address),(v6 * (agg5 != 0 ? 1L : 0L)));
              n6 = n6->nxt;
            }
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg6 = 0L;
        { //slice 
          const HashIndex_COUNTSUPPLIER2_E1_1_map_1* i8 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1*>(COUNTSUPPLIER2_E1_1.index[2]);
          const HASH_RES_t h7 = COUNTSUPPLIER2_E1_1_mapkey1_idxfn::hash(se24.modify1(supplier_suppkey));
          HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode* n8 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode*>(i8->slice(se24, h7));
          COUNTSUPPLIER2_E1_1_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long ps_partkey = e8->PS_PARTKEY;
              long ps_availqty = e8->PS_AVAILQTY;
              long v8 = e8->__av;
              DOUBLE_TYPE l6 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se22.modify(ps_partkey,supplier_suppkey)) * 0.5);
              (/*if */(ps_availqty > l6) ? agg6 += (v8 * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se23.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h7 == n8->hash &&  COUNTSUPPLIER2_E1_1_mapkey1_idxfn::equals(se24, *e8)); 
          }
        }COUNT.addOrDelOnZero(se20.modify(supplier_name,supplier_address),(COUNTSUPPLIER1.getValueOrDefault(se21.modify(supplier_nationkey)) * (agg6 != 0 ? 1L : 0L)));
        COUNTPARTSUPP1.addOrDelOnZero(se25.modify(supplier_suppkey,supplier_name,supplier_address),COUNTSUPPLIER1.getValueOrDefault(se26.modify(supplier_nationkey)));
      }
    }
    void on_insert_PARTSUPP(const long partsupp_partkey, const long partsupp_suppkey, const long partsupp_availqty, const DOUBLE_TYPE partsupp_supplycost, const STRING_TYPE& partsupp_comment) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        long agg7 = 0L;
        { //slice 
          const HashIndex_COUNTSUPPLIER2_E1_1_map_1* i9 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1*>(COUNTSUPPLIER2_E1_1.index[2]);
          const HASH_RES_t h8 = COUNTSUPPLIER2_E1_1_mapkey1_idxfn::hash(se30.modify1(partsupp_suppkey));
          HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode* n9 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode*>(i9->slice(se30, h8));
          COUNTSUPPLIER2_E1_1_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long ps_partkey = e9->PS_PARTKEY;
              long ps_availqty = e9->PS_AVAILQTY;
              long v9 = e9->__av;
              DOUBLE_TYPE l7 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se28.modify(ps_partkey,partsupp_suppkey)) * 0.5);
              (/*if */(ps_availqty > l7) ? agg7 += (v9 * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se29.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  COUNTSUPPLIER2_E1_1_mapkey1_idxfn::equals(se30, *e9)); 
          }
        }long agg8 = 0L;
        DOUBLE_TYPE l8 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se31.modify(partsupp_partkey,partsupp_suppkey)) * 0.5);
        (/*if */(partsupp_availqty > l8) ? agg8 += 1L : 0L);
        long agg9 = 0L;
        { //slice 
          const HashIndex_COUNTSUPPLIER2_E1_1_map_1* i10 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1*>(COUNTSUPPLIER2_E1_1.index[2]);
          const HASH_RES_t h9 = COUNTSUPPLIER2_E1_1_mapkey1_idxfn::hash(se35.modify1(partsupp_suppkey));
          HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode* n10 = static_cast<HashIndex_COUNTSUPPLIER2_E1_1_map_1::IdxNode*>(i10->slice(se35, h9));
          COUNTSUPPLIER2_E1_1_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long ps_partkey = e10->PS_PARTKEY;
              long ps_availqty = e10->PS_AVAILQTY;
              long v10 = e10->__av;
              DOUBLE_TYPE l9 = (COUNTSUPPLIER2_E1_1_L1_1.getValueOrDefault(se33.modify(ps_partkey,partsupp_suppkey)) * 0.5);
              (/*if */(ps_availqty > l9) ? agg9 += (v10 * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se34.modify(ps_partkey)) != 0 ? 1L : 0L)) : 0L);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h9 == n10->hash &&  COUNTSUPPLIER2_E1_1_mapkey1_idxfn::equals(se35, *e10)); 
          }
        }{ //slice 
          const HashIndex_COUNTPARTSUPP1_map_0* i11 = static_cast<HashIndex_COUNTPARTSUPP1_map_0*>(COUNTPARTSUPP1.index[1]);
          const HASH_RES_t h10 = COUNTPARTSUPP1_mapkey0_idxfn::hash(se36.modify0(partsupp_suppkey));
          HashIndex_COUNTPARTSUPP1_map_0::IdxNode* n11 = static_cast<HashIndex_COUNTPARTSUPP1_map_0::IdxNode*>(i11->slice(se36, h10));
          COUNTPARTSUPP1_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              STRING_TYPE s_name = e11->S_NAME;
              STRING_TYPE s_address = e11->S_ADDRESS;
              long v11 = e11->__av;
              COUNT.addOrDelOnZero(se27.modify(s_name,s_address),((((agg7 + (agg8 * (COUNTSUPPLIER2_E1_1_E2_1.getValueOrDefault(se32.modify(partsupp_partkey)) != 0 ? 1L : 0L))) != 0 ? 1L : 0L) + ((agg9 != 0 ? 1L : 0L) * -1L)) * v11));
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h10 == n11->hash &&  COUNTPARTSUPP1_mapkey0_idxfn::equals(se36, *e11)); 
          }
        }COUNTSUPPLIER2_E1_1.addOrDelOnZero(se37.modify(partsupp_partkey,partsupp_suppkey,partsupp_availqty),1L);
      }
    }
    void on_system_ready_event() {
      {  
        COUNTSUPPLIER1.clear();
        STRING_TYPE l10 = c3;
        { //slice 
          const HashIndex_NATION_map_1* i12 = static_cast<HashIndex_NATION_map_1*>(NATION.index[1]);
          const HASH_RES_t h11 = NATION_mapkey1_idxfn::hash(se39.modify1(l10));
          HashIndex_NATION_map_1::IdxNode* n12 = static_cast<HashIndex_NATION_map_1::IdxNode*>(i12->slice(se39, h11));
          NATION_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long countsuppliersupplier_nationkey = e12->NATION_NATIONKEY;
              long n_regionkey = e12->NATION_REGIONKEY;
              STRING_TYPE n_comment = e12->NATION_COMMENT;
              long v12 = e12->__av;
              COUNTSUPPLIER1.addOrDelOnZero(se38.modify(countsuppliersupplier_nationkey),v12);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h11 == n12->hash &&  NATION_mapkey1_idxfn::equals(se39, *e12)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNT_entry se1;
    COUNTSUPPLIER2_E1_1_L1_1_entry se2;
    COUNTSUPPLIER2_E1_1_entry se3;
    COUNTSUPPLIER2_E1_1_L1_1_entry se4;
    COUNTSUPPLIER2_E1_1_entry se5;
    COUNTSUPPLIER2_E1_1_E2_1_entry se6;
    COUNTSUPPLIER2_E1_1_L1_1_entry se7;
    COUNTSUPPLIER2_E1_1_E2_1_entry se8;
    COUNTSUPPLIER2_E1_1_entry se9;
    COUNTSUPPLIER2_E1_1_L1_1_entry se10;
    COUNTSUPPLIER2_E1_1_E2_1_entry se11;
    COUNTSUPPLIER2_E1_1_entry se12;
    COUNTPARTSUPP1_entry se13;
    COUNTSUPPLIER2_E1_1_L1_1_entry se14;
    COUNTSUPPLIER2_E1_1_E2_1_entry se15;
    COUNT_entry se16;
    COUNTSUPPLIER2_E1_1_L1_1_entry se17;
    COUNTSUPPLIER2_E1_1_E2_1_entry se18;
    COUNTSUPPLIER2_E1_1_entry se19;
    COUNT_entry se20;
    COUNTSUPPLIER1_entry se21;
    COUNTSUPPLIER2_E1_1_L1_1_entry se22;
    COUNTSUPPLIER2_E1_1_E2_1_entry se23;
    COUNTSUPPLIER2_E1_1_entry se24;
    COUNTPARTSUPP1_entry se25;
    COUNTSUPPLIER1_entry se26;
    COUNT_entry se27;
    COUNTSUPPLIER2_E1_1_L1_1_entry se28;
    COUNTSUPPLIER2_E1_1_E2_1_entry se29;
    COUNTSUPPLIER2_E1_1_entry se30;
    COUNTSUPPLIER2_E1_1_L1_1_entry se31;
    COUNTSUPPLIER2_E1_1_E2_1_entry se32;
    COUNTSUPPLIER2_E1_1_L1_1_entry se33;
    COUNTSUPPLIER2_E1_1_E2_1_entry se34;
    COUNTSUPPLIER2_E1_1_entry se35;
    COUNTPARTSUPP1_entry se36;
    COUNTSUPPLIER2_E1_1_entry se37;
    COUNTSUPPLIER1_entry se38;
    NATION_entry se39;
    /* regex_t temporary objects */
    regex_t preg1;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    COUNTPARTSUPP1_map COUNTPARTSUPP1;
    COUNTSUPPLIER1_map COUNTSUPPLIER1;
    COUNTSUPPLIER2_E1_1_map COUNTSUPPLIER2_E1_1;
    COUNTSUPPLIER2_E1_1_L1_1_map COUNTSUPPLIER2_E1_1_L1_1;
    COUNTSUPPLIER2_E1_1_E2_1_map COUNTSUPPLIER2_E1_1_E2_1;
    
    /*const static*/ long c2;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
  
  };

}
