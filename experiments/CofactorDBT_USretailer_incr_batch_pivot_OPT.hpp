#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#define RELATION_INVENTORY_DYNAMIC
#define RELATION_LOCATION_STATIC
#define RELATION_CENSUS_STATIC
#define RELATION_ITEM_STATIC
#define RELATION_WEATHER_STATIC
#define RELATION_DEGREE15_STATIC
#define RELATION_DEGREE13_STATIC
#define RELATION_DEGREE6_STATIC
#define RELATION_DEGREE4_STATIC
#define RELATION_DEGREE1_STATIC

#define CUSTOM_AGG_INVENTORY_SIZE 1
#define CUSTOM_AGG_LOCATION_SIZE 13
#define CUSTOM_AGG_CENSUS_SIZE 15
#define CUSTOM_AGG_ITEM_SIZE 4
#define CUSTOM_AGG_WEATHER_SIZE 6
#define CUSTOM_AGG_LC_SIZE 29
#define CUSTOM_AGG_INVITEM_SIZE 6
#define CUSTOM_AGG_INVITEMWEAT_SIZE 13
#define CUSTOM_AGG_SIZE 43

namespace dbtoaster {
 
  // CUSTOM DATA STRUCTURES
  template<int SUM_SIZE, int COFACTOR_SIZE = (SUM_SIZE * (SUM_SIZE + 1)) / 2>
  struct CUSTOM_AGG_value {
    int count;
    DOUBLE_TYPE sums[SUM_SIZE];
    DOUBLE_TYPE cofactors[COFACTOR_SIZE];

    explicit CUSTOM_AGG_value() {
      count = 0;
      memset(sums, 0, SUM_SIZE * sizeof(DOUBLE_TYPE));
      memset(cofactors, 0, COFACTOR_SIZE * sizeof(DOUBLE_TYPE));
    }

    ~CUSTOM_AGG_value() {
      count = 0;
      memset(sums, 0, SUM_SIZE * sizeof(DOUBLE_TYPE));
      memset(cofactors, 0, COFACTOR_SIZE * sizeof(DOUBLE_TYPE));
    }

    FORCE_INLINE CUSTOM_AGG_value& operator +=(const CUSTOM_AGG_value &obj) {
      count += obj.count;
      for (size_t i = 0; i < SUM_SIZE; i++) sums[i] += obj.sums[i];
      for (size_t i = 0; i < COFACTOR_SIZE; i++) cofactors[i] += obj.cofactors[i];
      return *this;
    }

    FORCE_INLINE bool operator ==(const CUSTOM_AGG_value &obj) {
      return (count == obj.count && sums == obj.sums && cofactors == obj.cofactors);
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, count);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP_OF_ARRAY(ar, sums, SUM_SIZE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP_OF_ARRAY(ar, cofactors, COFACTOR_SIZE);
    }
  };

  typedef CUSTOM_AGG_value<CUSTOM_AGG_LOCATION_SIZE> CUSTOM_AGG_Location_value;
  struct CUSTOM_AGG_Location_entry {
    long locn; 
    long zip; 
    CUSTOM_AGG_Location_value __av;  
    CUSTOM_AGG_Location_entry* nxt; 
    CUSTOM_AGG_Location_entry* prv;

    explicit CUSTOM_AGG_Location_entry() : nxt(nullptr), prv(nullptr) { }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct CUSTOM_AGG_Location_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_AGG_Location_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_AGG_Location_entry& x, const CUSTOM_AGG_Location_entry& y) {
      return x.locn == y.locn && x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<CUSTOM_AGG_Location_entry, CUSTOM_AGG_Location_value,
    HashIndex<CUSTOM_AGG_Location_entry, CUSTOM_AGG_Location_value, CUSTOM_AGG_Location_mapkey01234567891011121314_idxfn, true>
  > CUSTOM_AGG_Location_map;


  typedef CUSTOM_AGG_value<CUSTOM_AGG_CENSUS_SIZE> CUSTOM_AGG_Census_value;
  struct CUSTOM_AGG_Census_entry {
    long zip; 
    CUSTOM_AGG_Census_value __av;  
    CUSTOM_AGG_Census_entry* nxt; 
    CUSTOM_AGG_Census_entry* prv;

    explicit CUSTOM_AGG_Census_entry() : nxt(nullptr), prv(nullptr) {  }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTOM_AGG_Census_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_AGG_Census_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_AGG_Census_entry& x, const CUSTOM_AGG_Census_entry& y) {
      return x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<CUSTOM_AGG_Census_entry, CUSTOM_AGG_Census_value,
    HashIndex<CUSTOM_AGG_Census_entry, CUSTOM_AGG_Census_value, CUSTOM_AGG_Census_mapkey0123456789101112131415_idxfn, true>
  > CUSTOM_AGG_Census_map;


  typedef CUSTOM_AGG_value<CUSTOM_AGG_ITEM_SIZE> CUSTOM_AGG_Item_value;
  struct CUSTOM_AGG_Item_entry {
    DOUBLE_TYPE ksn;     
    CUSTOM_AGG_Item_value __av;  
    CUSTOM_AGG_Item_entry* nxt; 
    CUSTOM_AGG_Item_entry* prv;

    explicit CUSTOM_AGG_Item_entry() : nxt(nullptr), prv(nullptr) { }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct CUSTOM_AGG_Item_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_AGG_Item_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_AGG_Item_entry& x, const CUSTOM_AGG_Item_entry& y) {
      return x.ksn == y.ksn;
    }
  };
   
  typedef MultiHashMap<CUSTOM_AGG_Item_entry, CUSTOM_AGG_Item_value,
    HashIndex<CUSTOM_AGG_Item_entry, CUSTOM_AGG_Item_value, CUSTOM_AGG_Item_mapkey01234_idxfn,true>
  > CUSTOM_AGG_Item_map;
  

  typedef CUSTOM_AGG_value<CUSTOM_AGG_WEATHER_SIZE> CUSTOM_AGG_Weather_value;
  struct CUSTOM_AGG_Weather_entry {
    long locn; 
    long dateid; 
    CUSTOM_AGG_Weather_value __av;  
    CUSTOM_AGG_Weather_entry* nxt; 
    CUSTOM_AGG_Weather_entry* prv;

    explicit CUSTOM_AGG_Weather_entry() : nxt(nullptr), prv(nullptr) { }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct CUSTOM_AGG_Weather_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_AGG_Weather_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_AGG_Weather_entry& x, const CUSTOM_AGG_Weather_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<CUSTOM_AGG_Weather_entry, CUSTOM_AGG_Weather_value,
    HashIndex<CUSTOM_AGG_Weather_entry, CUSTOM_AGG_Weather_value, CUSTOM_AGG_Weather_mapkey01234567_idxfn, true>
  > CUSTOM_AGG_Weather_map;


  typedef CUSTOM_AGG_value<CUSTOM_AGG_LC_SIZE> CUSTOM_AGG_LC_value;
  struct CUSTOM_AGG_LC_entry {
    long locn; 
    CUSTOM_AGG_LC_value __av;  
    CUSTOM_AGG_LC_entry* nxt; 
    CUSTOM_AGG_LC_entry* prv;

    explicit CUSTOM_AGG_LC_entry() : nxt(nullptr), prv(nullptr) { }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct CUSTOM_AGG_LC_mapkey01234567891011121314151617181920212223242526272829_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_AGG_LC_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_AGG_LC_entry& x, const CUSTOM_AGG_LC_entry& y) {
      return x.locn == y.locn;
    }
  };
   
  typedef MultiHashMap<CUSTOM_AGG_LC_entry, CUSTOM_AGG_LC_value,
    HashIndex<CUSTOM_AGG_LC_entry, CUSTOM_AGG_LC_value, CUSTOM_AGG_LC_mapkey01234567891011121314151617181920212223242526272829_idxfn, true>
  > CUSTOM_AGG_LC_map;






  /* Definitions of auxiliary maps for storing materialized views. */  
  struct Location_entry {
    long locn; long zip; DOUBLE_TYPE rgn_cd; DOUBLE_TYPE clim_zn_nbr; DOUBLE_TYPE tot_area_sq_ft; DOUBLE_TYPE sell_area_sq_ft; DOUBLE_TYPE avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; long __av;  Location_entry* nxt; Location_entry* prv;
    explicit Location_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; zip = 0L; rgn_cd = 0.0; clim_zn_nbr = 0.0; tot_area_sq_ft = 0.0; sell_area_sq_ft = 0.0; avghhi = 0.0; supertargetdistance = 0.0; supertargetdrivetime = 0.0; targetdistance = 0.0; targetdrivetime = 0.0; walmartdistance = 0.0; walmartdrivetime = 0.0; walmartsupercenterdistance = 0.0; walmartsupercenterdrivetime = 0.0; __av = 0L; */ }
    explicit Location_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const long c15) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14; __av = c15; }
    Location_entry(const Location_entry& other) : locn( other.locn ), zip( other.zip ), rgn_cd( other.rgn_cd ), clim_zn_nbr( other.clim_zn_nbr ), tot_area_sq_ft( other.tot_area_sq_ft ), sell_area_sq_ft( other.sell_area_sq_ft ), avghhi( other.avghhi ), supertargetdistance( other.supertargetdistance ), supertargetdrivetime( other.supertargetdrivetime ), targetdistance( other.targetdistance ), targetdrivetime( other.targetdrivetime ), walmartdistance( other.walmartdistance ), walmartdrivetime( other.walmartdrivetime ), walmartsupercenterdistance( other.walmartsupercenterdistance ), walmartsupercenterdrivetime( other.walmartsupercenterdrivetime ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Location_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rgn_cd);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, clim_zn_nbr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, tot_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sell_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, avghhi);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Location_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const Location_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      hash_combine(h, e.rgn_cd);
      hash_combine(h, e.clim_zn_nbr);
      hash_combine(h, e.tot_area_sq_ft);
      hash_combine(h, e.sell_area_sq_ft);
      hash_combine(h, e.avghhi);
      hash_combine(h, e.supertargetdistance);
      hash_combine(h, e.supertargetdrivetime);
      hash_combine(h, e.targetdistance);
      hash_combine(h, e.targetdrivetime);
      hash_combine(h, e.walmartdistance);
      hash_combine(h, e.walmartdrivetime);
      hash_combine(h, e.walmartsupercenterdistance);
      hash_combine(h, e.walmartsupercenterdrivetime);
      return h;
    }
    FORCE_INLINE static bool equals(const Location_entry& x, const Location_entry& y) {
      return x.locn == y.locn && x.zip == y.zip && x.rgn_cd == y.rgn_cd && x.clim_zn_nbr == y.clim_zn_nbr && x.tot_area_sq_ft == y.tot_area_sq_ft && x.sell_area_sq_ft == y.sell_area_sq_ft && x.avghhi == y.avghhi && x.supertargetdistance == y.supertargetdistance && x.supertargetdrivetime == y.supertargetdrivetime && x.targetdistance == y.targetdistance && x.targetdrivetime == y.targetdrivetime && x.walmartdistance == y.walmartdistance && x.walmartdrivetime == y.walmartdrivetime && x.walmartsupercenterdistance == y.walmartsupercenterdistance && x.walmartsupercenterdrivetime == y.walmartsupercenterdrivetime;
    }
  };
  
  typedef MultiHashMap<Location_entry, long, 
    HashIndex<Location_entry, long, Location_mapkey01234567891011121314_idxfn, true>
  > Location_map;
  typedef HashIndex<Location_entry, long, Location_mapkey01234567891011121314_idxfn, true> HashIndex_Location_map_01234567891011121314;
  
  struct Census_entry {
    long zip; long population; long white; long asian; long pacific; long blackafrican; DOUBLE_TYPE medianage; long occupiedhouseunits; long houseunits; long families; long households; long husbwife; long males; long females; long householdschildren; long hispanic; long __av;  Census_entry* nxt; Census_entry* prv;
    explicit Census_entry() : nxt(nullptr), prv(nullptr) { /*zip = 0L; population = 0L; white = 0L; asian = 0L; pacific = 0L; blackafrican = 0L; medianage = 0.0; occupiedhouseunits = 0L; houseunits = 0L; families = 0L; households = 0L; husbwife = 0L; males = 0L; females = 0L; householdschildren = 0L; hispanic = 0L; __av = 0L; */ }
    explicit Census_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15, const long c16) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15; __av = c16; }
    Census_entry(const Census_entry& other) : zip( other.zip ), population( other.population ), white( other.white ), asian( other.asian ), pacific( other.pacific ), blackafrican( other.blackafrican ), medianage( other.medianage ), occupiedhouseunits( other.occupiedhouseunits ), houseunits( other.houseunits ), families( other.families ), households( other.households ), husbwife( other.husbwife ), males( other.males ), females( other.females ), householdschildren( other.householdschildren ), hispanic( other.hispanic ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Census_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, population);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, white);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, asian);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pacific);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, blackafrican);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, medianage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, occupiedhouseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, houseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, families);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, husbwife);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, males);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, females);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, householdschildren);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, hispanic);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Census_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const Census_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      hash_combine(h, e.population);
      hash_combine(h, e.white);
      hash_combine(h, e.asian);
      hash_combine(h, e.pacific);
      hash_combine(h, e.blackafrican);
      hash_combine(h, e.medianage);
      hash_combine(h, e.occupiedhouseunits);
      hash_combine(h, e.houseunits);
      hash_combine(h, e.families);
      hash_combine(h, e.households);
      hash_combine(h, e.husbwife);
      hash_combine(h, e.males);
      hash_combine(h, e.females);
      hash_combine(h, e.householdschildren);
      hash_combine(h, e.hispanic);
      return h;
    }
    FORCE_INLINE static bool equals(const Census_entry& x, const Census_entry& y) {
      return x.zip == y.zip && x.population == y.population && x.white == y.white && x.asian == y.asian && x.pacific == y.pacific && x.blackafrican == y.blackafrican && x.medianage == y.medianage && x.occupiedhouseunits == y.occupiedhouseunits && x.houseunits == y.houseunits && x.families == y.families && x.households == y.households && x.husbwife == y.husbwife && x.males == y.males && x.females == y.females && x.householdschildren == y.householdschildren && x.hispanic == y.hispanic;
    }
  };
  
  typedef MultiHashMap<Census_entry, long, 
    HashIndex<Census_entry, long, Census_mapkey0123456789101112131415_idxfn, true>
  > Census_map;
  typedef HashIndex<Census_entry, long, Census_mapkey0123456789101112131415_idxfn, true> HashIndex_Census_map_0123456789101112131415;
  
  struct Item_entry {
    DOUBLE_TYPE ksn; long subcategory; long category; long categoryCluster; DOUBLE_TYPE prize; long __av;  Item_entry* nxt; Item_entry* prv;
    explicit Item_entry() : nxt(nullptr), prv(nullptr) { /*ksn = 0.0; subcategory = 0L; category = 0L; categoryCluster = 0L; prize = 0.0; __av = 0L; */ }
    explicit Item_entry(const DOUBLE_TYPE c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4, const long c5) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4; __av = c5; }
    Item_entry(const Item_entry& other) : ksn( other.ksn ), subcategory( other.subcategory ), category( other.category ), categoryCluster( other.categoryCluster ), prize( other.prize ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Item_entry& modify(const DOUBLE_TYPE c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, categoryCluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Item_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const Item_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      hash_combine(h, e.subcategory);
      hash_combine(h, e.category);
      hash_combine(h, e.categoryCluster);
      hash_combine(h, e.prize);
      return h;
    }
    FORCE_INLINE static bool equals(const Item_entry& x, const Item_entry& y) {
      return x.ksn == y.ksn && x.subcategory == y.subcategory && x.category == y.category && x.categoryCluster == y.categoryCluster && x.prize == y.prize;
    }
  };
  
  typedef MultiHashMap<Item_entry, long, 
    HashIndex<Item_entry, long, Item_mapkey01234_idxfn, true>
  > Item_map;
  typedef HashIndex<Item_entry, long, Item_mapkey01234_idxfn, true> HashIndex_Item_map_01234;
  
  struct Weather_entry {
    long locn; long dateid; long rain; long snow; long maxtemp; long mintemp; DOUBLE_TYPE meanwind; long thunder; long __av;  Weather_entry* nxt; Weather_entry* prv;
    explicit Weather_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; dateid = 0L; rain = 0L; snow = 0L; maxtemp = 0L; mintemp = 0L; meanwind = 0.0; thunder = 0L; __av = 0L; */ }
    explicit Weather_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7, const long c8) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7; __av = c8; }
    Weather_entry(const Weather_entry& other) : locn( other.locn ), dateid( other.dateid ), rain( other.rain ), snow( other.snow ), maxtemp( other.maxtemp ), mintemp( other.mintemp ), meanwind( other.meanwind ), thunder( other.thunder ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Weather_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, snow);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, maxtemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, mintemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, meanwind);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, thunder);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Weather_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const Weather_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.rain);
      hash_combine(h, e.snow);
      hash_combine(h, e.maxtemp);
      hash_combine(h, e.mintemp);
      hash_combine(h, e.meanwind);
      hash_combine(h, e.thunder);
      return h;
    }
    FORCE_INLINE static bool equals(const Weather_entry& x, const Weather_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.rain == y.rain && x.snow == y.snow && x.maxtemp == y.maxtemp && x.mintemp == y.mintemp && x.meanwind == y.meanwind && x.thunder == y.thunder;
    }
  };
  
  typedef MultiHashMap<Weather_entry, long, 
    HashIndex<Weather_entry, long, Weather_mapkey01234567_idxfn, true>
  > Weather_map;
  typedef HashIndex<Weather_entry, long, Weather_mapkey01234567_idxfn, true> HashIndex_Weather_map_01234567;
  
  struct Degree15_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long Deg5; long Deg6; long Deg7; long Deg8; long Deg9; long Deg10; long Deg11; long Deg12; long Deg13; long Deg14; long Deg15; long __av;  Degree15_entry* nxt; Degree15_entry* prv;
    explicit Degree15_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; Deg5 = 0L; Deg6 = 0L; Deg7 = 0L; Deg8 = 0L; Deg9 = 0L; Deg10 = 0L; Deg11 = 0L; Deg12 = 0L; Deg13 = 0L; Deg14 = 0L; Deg15 = 0L; __av = 0L; */ }
    explicit Degree15_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12; Deg14 = c13; Deg15 = c14; __av = c15; }
    Degree15_entry(const Degree15_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), Deg5( other.Deg5 ), Deg6( other.Deg6 ), Deg7( other.Deg7 ), Deg8( other.Deg8 ), Deg9( other.Deg9 ), Deg10( other.Deg10 ), Deg11( other.Deg11 ), Deg12( other.Deg12 ), Deg13( other.Deg13 ), Deg14( other.Deg14 ), Deg15( other.Deg15 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Degree15_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12; Deg14 = c13; Deg15 = c14;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg1);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg2);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg3);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg4);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg5);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg6);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg7);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg8);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg9);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg10);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg11);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg12);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg13);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg14);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg15);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Degree15_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const Degree15_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg1);
      hash_combine(h, e.Deg2);
      hash_combine(h, e.Deg3);
      hash_combine(h, e.Deg4);
      hash_combine(h, e.Deg5);
      hash_combine(h, e.Deg6);
      hash_combine(h, e.Deg7);
      hash_combine(h, e.Deg8);
      hash_combine(h, e.Deg9);
      hash_combine(h, e.Deg10);
      hash_combine(h, e.Deg11);
      hash_combine(h, e.Deg12);
      hash_combine(h, e.Deg13);
      hash_combine(h, e.Deg14);
      hash_combine(h, e.Deg15);
      return h;
    }
    FORCE_INLINE static bool equals(const Degree15_entry& x, const Degree15_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4 && x.Deg5 == y.Deg5 && x.Deg6 == y.Deg6 && x.Deg7 == y.Deg7 && x.Deg8 == y.Deg8 && x.Deg9 == y.Deg9 && x.Deg10 == y.Deg10 && x.Deg11 == y.Deg11 && x.Deg12 == y.Deg12 && x.Deg13 == y.Deg13 && x.Deg14 == y.Deg14 && x.Deg15 == y.Deg15;
    }
  };
  
  typedef MultiHashMap<Degree15_entry, long, 
    HashIndex<Degree15_entry, long, Degree15_mapkey01234567891011121314_idxfn, true>
  > Degree15_map;
  typedef HashIndex<Degree15_entry, long, Degree15_mapkey01234567891011121314_idxfn, true> HashIndex_Degree15_map_01234567891011121314;
  
  struct Degree13_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long Deg5; long Deg6; long Deg7; long Deg8; long Deg9; long Deg10; long Deg11; long Deg12; long Deg13; long __av;  Degree13_entry* nxt; Degree13_entry* prv;
    explicit Degree13_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; Deg5 = 0L; Deg6 = 0L; Deg7 = 0L; Deg8 = 0L; Deg9 = 0L; Deg10 = 0L; Deg11 = 0L; Deg12 = 0L; Deg13 = 0L; __av = 0L; */ }
    explicit Degree13_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12; __av = c13; }
    Degree13_entry(const Degree13_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), Deg5( other.Deg5 ), Deg6( other.Deg6 ), Deg7( other.Deg7 ), Deg8( other.Deg8 ), Deg9( other.Deg9 ), Deg10( other.Deg10 ), Deg11( other.Deg11 ), Deg12( other.Deg12 ), Deg13( other.Deg13 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Degree13_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg1);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg2);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg3);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg4);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg5);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg6);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg7);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg8);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg9);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg10);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg11);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg12);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg13);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Degree13_mapkey0123456789101112_idxfn {
    FORCE_INLINE static size_t hash(const Degree13_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg1);
      hash_combine(h, e.Deg2);
      hash_combine(h, e.Deg3);
      hash_combine(h, e.Deg4);
      hash_combine(h, e.Deg5);
      hash_combine(h, e.Deg6);
      hash_combine(h, e.Deg7);
      hash_combine(h, e.Deg8);
      hash_combine(h, e.Deg9);
      hash_combine(h, e.Deg10);
      hash_combine(h, e.Deg11);
      hash_combine(h, e.Deg12);
      hash_combine(h, e.Deg13);
      return h;
    }
    FORCE_INLINE static bool equals(const Degree13_entry& x, const Degree13_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4 && x.Deg5 == y.Deg5 && x.Deg6 == y.Deg6 && x.Deg7 == y.Deg7 && x.Deg8 == y.Deg8 && x.Deg9 == y.Deg9 && x.Deg10 == y.Deg10 && x.Deg11 == y.Deg11 && x.Deg12 == y.Deg12 && x.Deg13 == y.Deg13;
    }
  };
  
  typedef MultiHashMap<Degree13_entry, long, 
    HashIndex<Degree13_entry, long, Degree13_mapkey0123456789101112_idxfn, true>
  > Degree13_map;
  typedef HashIndex<Degree13_entry, long, Degree13_mapkey0123456789101112_idxfn, true> HashIndex_Degree13_map_0123456789101112;
  
  struct Degree6_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long Deg5; long Deg6; long __av;  Degree6_entry* nxt; Degree6_entry* prv;
    explicit Degree6_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; Deg5 = 0L; Deg6 = 0L; __av = 0L; */ }
    explicit Degree6_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; __av = c6; }
    Degree6_entry(const Degree6_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), Deg5( other.Deg5 ), Deg6( other.Deg6 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Degree6_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg1);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg2);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg3);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg4);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg5);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg6);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Degree6_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const Degree6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg1);
      hash_combine(h, e.Deg2);
      hash_combine(h, e.Deg3);
      hash_combine(h, e.Deg4);
      hash_combine(h, e.Deg5);
      hash_combine(h, e.Deg6);
      return h;
    }
    FORCE_INLINE static bool equals(const Degree6_entry& x, const Degree6_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4 && x.Deg5 == y.Deg5 && x.Deg6 == y.Deg6;
    }
  };
  
  typedef MultiHashMap<Degree6_entry, long, 
    HashIndex<Degree6_entry, long, Degree6_mapkey012345_idxfn, true>
  > Degree6_map;
  typedef HashIndex<Degree6_entry, long, Degree6_mapkey012345_idxfn, true> HashIndex_Degree6_map_012345;
  
  struct Degree4_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long __av;  Degree4_entry* nxt; Degree4_entry* prv;
    explicit Degree4_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; __av = 0L; */ }
    explicit Degree4_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; __av = c4; }
    Degree4_entry(const Degree4_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Degree4_entry& modify(const long c0, const long c1, const long c2, const long c3) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg1);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg2);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg3);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg4);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Degree4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const Degree4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg1);
      hash_combine(h, e.Deg2);
      hash_combine(h, e.Deg3);
      hash_combine(h, e.Deg4);
      return h;
    }
    FORCE_INLINE static bool equals(const Degree4_entry& x, const Degree4_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4;
    }
  };
  
  typedef MultiHashMap<Degree4_entry, long, 
    HashIndex<Degree4_entry, long, Degree4_mapkey0123_idxfn, true>
  > Degree4_map;
  typedef HashIndex<Degree4_entry, long, Degree4_mapkey0123_idxfn, true> HashIndex_Degree4_map_0123;
  
  struct Degree1_entry {
    long Deg; long __av;  Degree1_entry* nxt; Degree1_entry* prv;
    explicit Degree1_entry() : nxt(nullptr), prv(nullptr) { /*Deg = 0L; __av = 0L; */ }
    explicit Degree1_entry(const long c0, const long c1) { Deg = c0; __av = c1; }
    Degree1_entry(const Degree1_entry& other) : Deg( other.Deg ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE Degree1_entry& modify(const long c0) { Deg = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct Degree1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const Degree1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg);
      return h;
    }
    FORCE_INLINE static bool equals(const Degree1_entry& x, const Degree1_entry& y) {
      return x.Deg == y.Deg;
    }
  };
  
  typedef MultiHashMap<Degree1_entry, long, 
    HashIndex<Degree1_entry, long, Degree1_mapkey0_idxfn, true>
  > Degree1_map;
  typedef HashIndex<Degree1_entry, long, Degree1_mapkey0_idxfn, true> HashIndex_Degree1_map_0;
  

  // CUSTOM VECTOR-BASED DATA STRUCTURES

  typedef CUSTOM_AGG_value<CUSTOM_AGG_INVENTORY_SIZE> CUSTOM_DELTA_AGG_Inventory_value;
  struct CUSTOM_DELTA_AGG_Inventory_entry {
    long locn; 
    long dateid; 
    DOUBLE_TYPE ksn; 
    CUSTOM_DELTA_AGG_Inventory_value __av;
    CUSTOM_DELTA_AGG_Inventory_entry* nxt; 
    CUSTOM_DELTA_AGG_Inventory_entry* prv;

    explicit CUSTOM_DELTA_AGG_Inventory_entry() : nxt(nullptr), prv(nullptr) { }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct CUSTOM_DELTA_AGG_Inventory_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_DELTA_AGG_Inventory_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_DELTA_AGG_Inventory_entry& x, const CUSTOM_DELTA_AGG_Inventory_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn;
    }
  };

  typedef MultiHashMap<CUSTOM_DELTA_AGG_Inventory_entry, CUSTOM_DELTA_AGG_Inventory_value,
    HashIndex<CUSTOM_DELTA_AGG_Inventory_entry, CUSTOM_DELTA_AGG_Inventory_value, CUSTOM_DELTA_AGG_Inventory_mapkey0123_idxfn, true>
  > CUSTOM_DELTA_AGG_Inventory_map;


  typedef CUSTOM_AGG_value<CUSTOM_AGG_INVITEM_SIZE> CUSTOM_DELTA_AGG_InvItem_value;
  struct CUSTOM_DELTA_AGG_InvItem_entry {
    long locn; 
    long dateid;
    CUSTOM_DELTA_AGG_InvItem_value __av;  
    CUSTOM_DELTA_AGG_InvItem_entry* nxt; 
    CUSTOM_DELTA_AGG_InvItem_entry* prv;

    explicit CUSTOM_DELTA_AGG_InvItem_entry() : nxt(nullptr), prv(nullptr) { }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct CUSTOM_DELTA_AGG_InvItem_mapkey01234567891011121314151617181920212223242526272829_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_DELTA_AGG_InvItem_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_DELTA_AGG_InvItem_entry& x, const CUSTOM_DELTA_AGG_InvItem_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
   
  typedef MultiHashMap<CUSTOM_DELTA_AGG_InvItem_entry, CUSTOM_DELTA_AGG_InvItem_value,
    HashIndex<CUSTOM_DELTA_AGG_InvItem_entry, CUSTOM_DELTA_AGG_InvItem_value, CUSTOM_DELTA_AGG_InvItem_mapkey01234567891011121314151617181920212223242526272829_idxfn, true>
  > CUSTOM_DELTA_AGG_InvItem_map;


  typedef CUSTOM_AGG_value<CUSTOM_AGG_INVITEMWEAT_SIZE> CUSTOM_DELTA_AGG_InvItemWeat_value;
  struct CUSTOM_DELTA_AGG_InvItemWeat_entry {
    long locn; 
    CUSTOM_DELTA_AGG_InvItemWeat_value __av;  
    CUSTOM_DELTA_AGG_InvItemWeat_entry* nxt; 
    CUSTOM_DELTA_AGG_InvItemWeat_entry* prv;

    explicit CUSTOM_DELTA_AGG_InvItemWeat_entry() : nxt(nullptr), prv(nullptr) { }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct CUSTOM_DELTA_AGG_InvItemWeat_mapkey01234567891011121314151617181920212223242526272829_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOM_DELTA_AGG_InvItemWeat_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }

    FORCE_INLINE static bool equals(const CUSTOM_DELTA_AGG_InvItemWeat_entry& x, const CUSTOM_DELTA_AGG_InvItemWeat_entry& y) {
      return x.locn == y.locn;
    }
  };
   
  typedef MultiHashMap<CUSTOM_DELTA_AGG_InvItemWeat_entry, CUSTOM_DELTA_AGG_InvItemWeat_value,
    HashIndex<CUSTOM_DELTA_AGG_InvItemWeat_entry, CUSTOM_DELTA_AGG_InvItemWeat_value, CUSTOM_DELTA_AGG_InvItemWeat_mapkey01234567891011121314151617181920212223242526272829_idxfn, true>
  > CUSTOM_DELTA_AGG_InvItemWeat_map;

  typedef CUSTOM_AGG_value<CUSTOM_AGG_SIZE> CUSTOM_AGG_Output_value;  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0)  { gettimeofday(&t0, NULL); }
  
    /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      dbtoaster::serialize_nvp_tabbed(ar, STRING(CUSTOM_AGG_Output), CUSTOM_AGG_Output, "\t"); 
    }
    
  protected:
    /* Data structures used for storing / computing top level queries */
    CUSTOM_AGG_Output_value CUSTOM_AGG_Output;
  
  };

  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_Location(const long locn, const long zip, const DOUBLE_TYPE rgn_cd, const DOUBLE_TYPE clim_zn_nbr, const DOUBLE_TYPE tot_area_sq_ft, const DOUBLE_TYPE sell_area_sq_ft, const DOUBLE_TYPE avghhi, const DOUBLE_TYPE supertargetdistance, const DOUBLE_TYPE supertargetdrivetime, const DOUBLE_TYPE targetdistance, const DOUBLE_TYPE targetdrivetime, const DOUBLE_TYPE walmartdistance, const DOUBLE_TYPE walmartdrivetime, const DOUBLE_TYPE walmartsupercenterdistance, const DOUBLE_TYPE walmartsupercenterdrivetime) {
      Location_entry e(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime, 1L);
      Location.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Census(const long zip, const long population, const long white, const long asian, const long pacific, const long blackafrican, const DOUBLE_TYPE medianage, const long occupiedhouseunits, const long houseunits, const long families, const long households, const long husbwife, const long males, const long females, const long householdschildren, const long hispanic) {
      Census_entry e(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic, 1L);
      Census.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Item(const DOUBLE_TYPE ksn, const long subcategory, const long category, const long categorycluster, const DOUBLE_TYPE prize) {
      Item_entry e(ksn, subcategory, category, categorycluster, prize, 1L);
      Item.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Weather(const long locn, const long dateid, const long rain, const long snow, const long maxtemp, const long mintemp, const DOUBLE_TYPE meanwind, const long thunder) {
      Weather_entry e(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder, 1L);
      Weather.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Degree15(const long deg1, const long deg2, const long deg3, const long deg4, const long deg5, const long deg6, const long deg7, const long deg8, const long deg9, const long deg10, const long deg11, const long deg12, const long deg13, const long deg14, const long deg15) {
      Degree15_entry e(deg1, deg2, deg3, deg4, deg5, deg6, deg7, deg8, deg9, deg10, deg11, deg12, deg13, deg14, deg15, 1L);
      Degree15.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Degree13(const long deg1, const long deg2, const long deg3, const long deg4, const long deg5, const long deg6, const long deg7, const long deg8, const long deg9, const long deg10, const long deg11, const long deg12, const long deg13) {
      Degree13_entry e(deg1, deg2, deg3, deg4, deg5, deg6, deg7, deg8, deg9, deg10, deg11, deg12, deg13, 1L);
      Degree13.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Degree6(const long deg1, const long deg2, const long deg3, const long deg4, const long deg5, const long deg6) {
      Degree6_entry e(deg1, deg2, deg3, deg4, deg5, deg6, 1L);
      Degree6.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Degree4(const long deg1, const long deg2, const long deg3, const long deg4) {
      Degree4_entry e(deg1, deg2, deg3, deg4, 1L);
      Degree4.addOrDelOnZero(e,1L);
    }
    
    void on_insert_Degree1(const long deg) {
      Degree1_entry e(deg, 1L);
      Degree1.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    template<typename T>
    void on_batch_update_Inventory(const typename std::vector<T>::iterator &begin, const typename std::vector<T>::iterator &end) {
      tN += std::distance(begin, end);
      CUSTOM_DELTA_AGG_Inventory.clear();
      { //foreach
        for (typename std::vector<T>::iterator e1 = begin; e1 != end; e1++) {
          long locn = e1->locn;
          long dateid = e1->dateid;
          DOUBLE_TYPE ksn = e1->ksn;
          DOUBLE_TYPE inventoryunits = e1->inventoryunits;
          long count = e1->__av;

          custom_se1.locn = locn;
          custom_se1.dateid = dateid;
          custom_se1.ksn = ksn;

          custom_sv1.count = count;
          custom_sv1.sums[0] = count * inventoryunits;
          custom_sv1.cofactors[0] = count * inventoryunits * inventoryunits;

          CUSTOM_DELTA_AGG_Inventory.addOrDelOnZero(custom_se1, custom_sv1);
        }
      }

      CUSTOM_DELTA_AGG_InvItem.clear();
      { //foreach
        CUSTOM_DELTA_AGG_Inventory_entry* e20 = CUSTOM_DELTA_AGG_Inventory.head;
        while(e20){
          long locn = e20->locn;
          long dateid = e20->dateid;
          long ksn = e20->ksn;            
          const CUSTOM_DELTA_AGG_Inventory_value &vInventory = e20->__av;

          custom_se4.ksn = ksn;
          const CUSTOM_AGG_Item_value &vItem = CUSTOM_AGG_Item.getValueOrDefault(custom_se4);

          long count1 = vInventory.count;
          long count2 = vItem.count;
          long count = count1 * count2;

          custom_se7.locn = locn;
          custom_se7.dateid = dateid;
          
          size_t indexOutput = 0;
          custom_sv7.count = count;            
          custom_sv7.sums[indexOutput++] = count * ksn;            
          for (size_t i = 0; i < CUSTOM_AGG_INVENTORY_SIZE; i++) {
            custom_sv7.sums[indexOutput++] = count2 * vInventory.sums[i];
          }
          for (size_t i = 0; i < CUSTOM_AGG_ITEM_SIZE; i++) {
            custom_sv7.sums[indexOutput++] = count1 * vItem.sums[i];
          }
         
          indexOutput = 0;
          custom_sv7.cofactors[indexOutput++] = count * ksn * ksn;
          for (int i = 0; i < CUSTOM_AGG_INVENTORY_SIZE; i++) {
            custom_sv7.cofactors[indexOutput++] = count2 * ksn * vInventory.sums[i];
          }
          for (int i = 0; i < CUSTOM_AGG_ITEM_SIZE; i++) {
            custom_sv7.cofactors[indexOutput++] = count1 * ksn * vItem.sums[i];
          }

          size_t indexInput = 0;
          for (int i = 0; i < CUSTOM_AGG_INVENTORY_SIZE; i++) {
            for (int j = i; j < CUSTOM_AGG_INVENTORY_SIZE; j++) {
              custom_sv7.cofactors[indexOutput++] = count2 * vInventory.cofactors[indexInput++];
            }

            for (int j = 0; j < CUSTOM_AGG_ITEM_SIZE; j++) {
              custom_sv7.cofactors[indexOutput++] = vInventory.sums[i] * vItem.sums[j];
            }
          }

          indexInput = 0;
          for (int i = 0; i < CUSTOM_AGG_ITEM_SIZE; i++) {
            for (int j = i; j < CUSTOM_AGG_ITEM_SIZE; j++) {
              custom_sv7.cofactors[indexOutput++] = count1 * vItem.cofactors[indexInput++];
            }
          }

          CUSTOM_DELTA_AGG_InvItem.addOrDelOnZero(custom_se7, custom_sv7);

          e20 = e20->nxt;            
        }
      }

      CUSTOM_DELTA_AGG_InvItemWeat.clear();
      { //foreach
        CUSTOM_DELTA_AGG_InvItem_entry* e20 = CUSTOM_DELTA_AGG_InvItem.head;
        while(e20){
          long locn = e20->locn;
          long dateid = e20->dateid;
          const CUSTOM_DELTA_AGG_InvItem_value &vInvItem = e20->__av;

          custom_se5.locn = locn;
          custom_se5.dateid = dateid;
          const CUSTOM_AGG_Weather_value &vWeather = CUSTOM_AGG_Weather.getValueOrDefault(custom_se5);

          long count1 = vInvItem.count;
          long count2 = vWeather.count;
          long count = count1 * count2;

          custom_se8.locn = locn;
          
          size_t indexOutput = 0;
          custom_sv8.count = count;            
          custom_sv8.sums[indexOutput++] = count * dateid;            
          for (size_t i = 0; i < CUSTOM_AGG_INVITEM_SIZE; i++) {
            custom_sv8.sums[indexOutput++] = count2 * vInvItem.sums[i];
          }
          for (size_t i = 0; i < CUSTOM_AGG_WEATHER_SIZE; i++) {
            custom_sv8.sums[indexOutput++] = count1 * vWeather.sums[i];
          }
         
          indexOutput = 0;
          custom_sv8.cofactors[indexOutput++] = count * dateid * dateid;
          for (int i = 0; i < CUSTOM_AGG_INVITEM_SIZE; i++) {
            custom_sv8.cofactors[indexOutput++] = count2 * dateid * vInvItem.sums[i];
          }
          for (int i = 0; i < CUSTOM_AGG_WEATHER_SIZE; i++) {
            custom_sv8.cofactors[indexOutput++] = count1 * dateid * vWeather.sums[i];
          }

          size_t indexInput = 0;
          for (int i = 0; i < CUSTOM_AGG_INVITEM_SIZE; i++) {
            for (int j = i; j < CUSTOM_AGG_INVITEM_SIZE; j++) {
              custom_sv8.cofactors[indexOutput++] = count2 * vInvItem.cofactors[indexInput++];
            }

            for (int j = 0; j < CUSTOM_AGG_WEATHER_SIZE; j++) {
              custom_sv8.cofactors[indexOutput++] = vInvItem.sums[i] * vWeather.sums[j];
            }
          }

          indexInput = 0;
          for (int i = 0; i < CUSTOM_AGG_WEATHER_SIZE; i++) {
            for (int j = i; j < CUSTOM_AGG_WEATHER_SIZE; j++) {
              custom_sv8.cofactors[indexOutput++] = count1 * vWeather.cofactors[indexInput++];
            }
          }

          CUSTOM_DELTA_AGG_InvItemWeat.addOrDelOnZero(custom_se8, custom_sv8);

          e20 = e20->nxt;            
        }
      }

      { //foreach
        CUSTOM_DELTA_AGG_InvItemWeat_entry* e20 = CUSTOM_DELTA_AGG_InvItemWeat.head;
        while(e20){
          long locn = e20->locn;
          const CUSTOM_DELTA_AGG_InvItemWeat_value &vInvItemWeat = e20->__av;

          custom_se6.locn = locn;
          const CUSTOM_AGG_LC_value &vLC = CUSTOM_AGG_LC.getValueOrDefault(custom_se6);

          long count1 = vInvItemWeat.count;
          long count2 = vLC.count;
          long count = count1 * count2;
          
          CUSTOM_AGG_Output.count += count;
          
          size_t indexOutput = 0;
          CUSTOM_AGG_Output.cofactors[indexOutput++] += count * locn * locn;
          for (int i = 0; i < CUSTOM_AGG_INVITEMWEAT_SIZE; i++) {
            CUSTOM_AGG_Output.cofactors[indexOutput++] += count2 * locn * vInvItemWeat.sums[i];
          }
          for (int i = 0; i < CUSTOM_AGG_LC_SIZE; i++) {
            CUSTOM_AGG_Output.cofactors[indexOutput++] += count1 * locn * vLC.sums[i];
          }

          size_t indexInput = 0;
          for (int i = 0; i < CUSTOM_AGG_INVITEMWEAT_SIZE; i++) {
            for (int j = i; j < CUSTOM_AGG_INVITEMWEAT_SIZE; j++) {
              CUSTOM_AGG_Output.cofactors[indexOutput++] += count2 * vInvItemWeat.cofactors[indexInput++];
            }

            for (int j = 0; j < CUSTOM_AGG_LC_SIZE; j++) {
              CUSTOM_AGG_Output.cofactors[indexOutput++] += vInvItemWeat.sums[i] * vLC.sums[j];
            }
          }

          indexInput = 0;
          for (int i = 0; i < CUSTOM_AGG_LC_SIZE; i++) {
            for (int j = i; j < CUSTOM_AGG_LC_SIZE; j++) {
              CUSTOM_AGG_Output.cofactors[indexOutput++] += count1 * vLC.cofactors[indexInput++];
            }
          }

          e20 = e20->nxt;
        }
      }
    }
    
    void on_system_ready_event() {

        CUSTOM_AGG_Location.clear();
        { //foreach
          DOUBLE_TYPE fields[CUSTOM_AGG_LOCATION_SIZE];
          Location_entry* e3 = Location.head;
          while(e3){
            long locn = e3->locn;
            long zip = e3->zip;
            DOUBLE_TYPE rgn_cd = e3->rgn_cd;
            DOUBLE_TYPE clim_zn_nbr = e3->clim_zn_nbr;
            DOUBLE_TYPE tot_area_sq_ft = e3->tot_area_sq_ft;
            DOUBLE_TYPE sell_area_sq_ft = e3->sell_area_sq_ft;
            DOUBLE_TYPE avghhi = e3->avghhi;
            DOUBLE_TYPE supertargetdistance = e3->supertargetdistance;
            DOUBLE_TYPE supertargetdrivetime = e3->supertargetdrivetime;
            DOUBLE_TYPE targetdistance = e3->targetdistance;
            DOUBLE_TYPE targetdrivetime = e3->targetdrivetime;
            DOUBLE_TYPE walmartdistance = e3->walmartdistance;
            DOUBLE_TYPE walmartdrivetime = e3->walmartdrivetime;
            DOUBLE_TYPE walmartsupercenterdistance = e3->walmartsupercenterdistance;
            DOUBLE_TYPE walmartsupercenterdrivetime = e3->walmartsupercenterdrivetime;
            long count = e3->__av;

            fields[0] = rgn_cd;
            fields[1] = clim_zn_nbr;
            fields[2] = tot_area_sq_ft;
            fields[3] = sell_area_sq_ft;
            fields[4] = avghhi;
            fields[5] = supertargetdistance;
            fields[6] = supertargetdrivetime;
            fields[7] = targetdistance;
            fields[8] = targetdrivetime;
            fields[9] = walmartdistance;
            fields[10] = walmartdrivetime;
            fields[11] = walmartsupercenterdistance;
            fields[12] = walmartsupercenterdrivetime;

            // KEY
            custom_se2.locn = locn;
            custom_se2.zip = zip;

            // VALUE
            custom_sv2.count = count;
            size_t indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_LOCATION_SIZE; i++) {
              custom_sv2.sums[indexOutput++] = count * fields[i];
            }
            indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_LOCATION_SIZE; i++) {
              for (size_t j = i; j < CUSTOM_AGG_LOCATION_SIZE; j++) {
                custom_sv2.cofactors[indexOutput++] = count * fields[i] * fields[j];;
              }
            }

            CUSTOM_AGG_Location.addOrDelOnZero(custom_se2, custom_sv2);

            e3 = e3->nxt;
          }
        }

        CUSTOM_AGG_Census.clear();
        { //foreach
          DOUBLE_TYPE fields[CUSTOM_AGG_CENSUS_SIZE];
          Census_entry* e5 = Census.head;
          while(e5){
            long zip = e5->zip;
            long population = e5->population;
            long white = e5->white;
            long asian = e5->asian;
            long pacific = e5->pacific;
            long blackafrican = e5->blackafrican;
            DOUBLE_TYPE medianage = e5->medianage;
            long occupiedhouseunits = e5->occupiedhouseunits;
            long houseunits = e5->houseunits;
            long families = e5->families;
            long households = e5->households;
            long husbwife = e5->husbwife;
            long males = e5->males;
            long females = e5->females;
            long householdschildren = e5->householdschildren;
            long hispanic = e5->hispanic;
            long count = e5->__av;

            fields[0] = population;
            fields[1] = white;
            fields[2] = asian;
            fields[3] = pacific;
            fields[4] = blackafrican;
            fields[5] = medianage;
            fields[6] = occupiedhouseunits;
            fields[7] = houseunits;
            fields[8] = families;
            fields[9] = households;
            fields[10] = husbwife;
            fields[11] = males;
            fields[12] = females;
            fields[13] = householdschildren;
            fields[14] = hispanic;

            // KEY
            custom_se3.zip = zip;

            // VALUE
            custom_sv3.count = count;
            size_t indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_CENSUS_SIZE; i++) {
              custom_sv3.sums[indexOutput++] = count * fields[i];
            }
            indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_CENSUS_SIZE; i++) {
              for (size_t j = i; j < CUSTOM_AGG_CENSUS_SIZE; j++) {
                custom_sv3.cofactors[indexOutput++] = count * fields[i] * fields[j];;
              }
            }

            CUSTOM_AGG_Census.addOrDelOnZero(custom_se3, custom_sv3);
            
            e5 = e5->nxt;
          }
        }

        CUSTOM_AGG_Item.clear();
        { //foreach
          DOUBLE_TYPE fields[CUSTOM_AGG_ITEM_SIZE];          
          Item_entry* e7 = Item.head;
          while(e7){
            DOUBLE_TYPE ksn = e7->ksn;
            long subcategory = e7->subcategory;
            long category = e7->category;
            long categorycluster = e7->categoryCluster;
            DOUBLE_TYPE prize = e7->prize;
            long count = e7->__av;

            fields[0] = subcategory;
            fields[1] = category;
            fields[2] = categorycluster;
            fields[3] = prize;

            // KEY
            custom_se4.ksn = ksn;

            // VALUE
            custom_sv4.count = count;
            size_t indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_ITEM_SIZE; i++) {
              custom_sv4.sums[indexOutput++] = count * fields[i];
            }
            indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_ITEM_SIZE; i++) {
              for (size_t j = i; j < CUSTOM_AGG_ITEM_SIZE; j++) {
                custom_sv4.cofactors[indexOutput++] = count * fields[i] * fields[j];;
              }
            }

            CUSTOM_AGG_Item.addOrDelOnZero(custom_se4, custom_sv4);

            e7 = e7->nxt;
          }
        }

        CUSTOM_AGG_Weather.clear();
        { //foreach
          DOUBLE_TYPE fields[CUSTOM_AGG_WEATHER_SIZE];
          Weather_entry* e9 = Weather.head;
          while(e9){
            long locn = e9->locn;
            long dateid = e9->dateid;
            long rain = e9->rain;
            long snow = e9->snow;
            long maxtemp = e9->maxtemp;
            long mintemp = e9->mintemp;
            DOUBLE_TYPE meanwind = e9->meanwind;
            long thunder = e9->thunder;
            long count = e9->__av;

            fields[0] = rain;
            fields[1] = snow;
            fields[2] = maxtemp;
            fields[3] = mintemp;
            fields[4] = meanwind;
            fields[5] = thunder;

            // KEY
            custom_se5.locn = locn;
            custom_se5.dateid = dateid;

            // VALUE
            custom_sv5.count = count;
            size_t indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_WEATHER_SIZE; i++) {
              custom_sv5.sums[indexOutput++] = count * fields[i];
            }
            indexOutput = 0;
            for (size_t i = 0; i < CUSTOM_AGG_WEATHER_SIZE; i++) {
              for (size_t j = i; j < CUSTOM_AGG_WEATHER_SIZE; j++) {
                custom_sv5.cofactors[indexOutput++] = count * fields[i] * fields[j];;
              }
            }

            CUSTOM_AGG_Weather.addOrDelOnZero(custom_se5, custom_sv5);
            
            e9 = e9->nxt;
          }
        }

        CUSTOM_AGG_LC.clear();
        { //foreach
          CUSTOM_AGG_Location_entry* e11 = CUSTOM_AGG_Location.head;
          while(e11){
            long locn = e11->locn;
            long zip = e11->zip;
            
            const CUSTOM_AGG_Location_value &vLocation = e11->__av;          
            custom_se3.zip = zip;            
            const CUSTOM_AGG_Census_value &vCensus = CUSTOM_AGG_Census.getValueOrDefault(custom_se3);

            long count1 = vLocation.count;
            long count2 = vCensus.count;
            long count = count1 * count2;

            custom_se6.locn = locn;
            
            size_t indexOutput = 0;
            custom_sv6.count = count;            
            custom_sv6.sums[indexOutput++] = count * zip;            
            for (size_t i = 0; i < CUSTOM_AGG_LOCATION_SIZE; i++) {
              custom_sv6.sums[indexOutput++] = count2 * vLocation.sums[i];
            }
            for (size_t i = 0; i < CUSTOM_AGG_CENSUS_SIZE; i++) {
              custom_sv6.sums[indexOutput++] = count1 * vCensus.sums[i];
            }
           
            indexOutput = 0;
            custom_sv6.cofactors[indexOutput++] = count * zip * zip;
            for (int i = 0; i < CUSTOM_AGG_LOCATION_SIZE; i++) {
              custom_sv6.cofactors[indexOutput++] = count2 * zip * vLocation.sums[i];
            }
            for (int i = 0; i < CUSTOM_AGG_CENSUS_SIZE; i++) {
              custom_sv6.cofactors[indexOutput++] = count1 * zip * vCensus.sums[i];
            }

            size_t indexInput = 0;
            for (int i = 0; i < CUSTOM_AGG_LOCATION_SIZE; i++) {
              for (int j = i; j < CUSTOM_AGG_LOCATION_SIZE; j++) {
                custom_sv6.cofactors[indexOutput++] = count2 * vLocation.cofactors[indexInput++];
              }

              for (int j = 0; j < CUSTOM_AGG_CENSUS_SIZE; j++) {
                custom_sv6.cofactors[indexOutput++] = vLocation.sums[i] * vCensus.sums[j];
              }
            }

            indexInput = 0;
            for (int i = 0; i < CUSTOM_AGG_CENSUS_SIZE; i++) {
              for (int j = i; j < CUSTOM_AGG_CENSUS_SIZE; j++) {
                custom_sv6.cofactors[indexOutput++] = count1 * vCensus.cofactors[indexInput++];
              }
            }

            CUSTOM_AGG_LC.addOrDelOnZero(custom_se6, custom_sv6);

            e11 = e11->nxt;
          }
        }      
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    CUSTOM_DELTA_AGG_Inventory_entry custom_se1;
    CUSTOM_AGG_Location_entry custom_se2;
    CUSTOM_AGG_Census_entry custom_se3;
    CUSTOM_AGG_Item_entry custom_se4;
    CUSTOM_AGG_Weather_entry custom_se5;
    CUSTOM_AGG_LC_entry custom_se6;
    CUSTOM_DELTA_AGG_InvItem_entry custom_se7;
    CUSTOM_DELTA_AGG_InvItemWeat_entry custom_se8;

    CUSTOM_DELTA_AGG_Inventory_value custom_sv1;
    CUSTOM_AGG_Location_value custom_sv2;
    CUSTOM_AGG_Census_value custom_sv3;
    CUSTOM_AGG_Item_value custom_sv4;
    CUSTOM_AGG_Weather_value custom_sv5;
    CUSTOM_AGG_LC_value custom_sv6;
    CUSTOM_DELTA_AGG_InvItem_value custom_sv7;
    CUSTOM_DELTA_AGG_InvItemWeat_value custom_sv8;

    /* Data structures used for storing materialized views */
    Location_map Location;
    Census_map Census;
    Item_map Item;
    Weather_map Weather;
    Degree15_map Degree15;
    Degree13_map Degree13;
    Degree6_map Degree6;
    Degree4_map Degree4;
    Degree1_map Degree1;
 
    CUSTOM_AGG_Location_map CUSTOM_AGG_Location;
    CUSTOM_AGG_Census_map CUSTOM_AGG_Census;
    CUSTOM_AGG_Item_map CUSTOM_AGG_Item;
    CUSTOM_AGG_Weather_map CUSTOM_AGG_Weather;
    CUSTOM_AGG_LC_map CUSTOM_AGG_LC;
    CUSTOM_DELTA_AGG_Inventory_map CUSTOM_DELTA_AGG_Inventory;
    CUSTOM_DELTA_AGG_InvItem_map CUSTOM_DELTA_AGG_InvItem;
    CUSTOM_DELTA_AGG_InvItemWeat_map CUSTOM_DELTA_AGG_InvItemWeat;
  };
}