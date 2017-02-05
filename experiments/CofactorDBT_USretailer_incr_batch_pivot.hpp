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

namespace dbtoaster {
  
  /* Definitions of auxiliary maps for storing materialized views. */
  struct DELTA_INVENTORY_entry {
    long locn; long dateid; DOUBLE_TYPE ksn; DOUBLE_TYPE inventoryunits; long __av;  DELTA_INVENTORY_entry* nxt; DELTA_INVENTORY_entry* prv;
    explicit DELTA_INVENTORY_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; dateid = 0L; ksn = 0.0; inventoryunits = 0.0; __av = 0L; */ }
    explicit DELTA_INVENTORY_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const long c4) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3; __av = c4; }
    DELTA_INVENTORY_entry(const DELTA_INVENTORY_entry& other) : locn( other.locn ), dateid( other.dateid ), ksn( other.ksn ), inventoryunits( other.inventoryunits ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DELTA_INVENTORY_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_INVENTORY_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_INVENTORY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      hash_combine(h, e.inventoryunits);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_INVENTORY_entry& x, const DELTA_INVENTORY_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.inventoryunits == y.inventoryunits;
    }
  };
  
  typedef MultiHashMap<DELTA_INVENTORY_entry, long, 
    HashIndex<DELTA_INVENTORY_entry, long, DELTA_INVENTORY_mapkey0123_idxfn, true>
  > DELTA_INVENTORY_map;
  typedef HashIndex<DELTA_INVENTORY_entry, long, DELTA_INVENTORY_mapkey0123_idxfn, true> HashIndex_DELTA_INVENTORY_map_0123;
  
  struct LOCATION_entry {
    long locn; long zip; DOUBLE_TYPE rgn_cd; DOUBLE_TYPE clim_zn_nbr; DOUBLE_TYPE tot_area_sq_ft; DOUBLE_TYPE sell_area_sq_ft; DOUBLE_TYPE avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; long __av;  LOCATION_entry* nxt; LOCATION_entry* prv;
    explicit LOCATION_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; zip = 0L; rgn_cd = 0.0; clim_zn_nbr = 0.0; tot_area_sq_ft = 0.0; sell_area_sq_ft = 0.0; avghhi = 0.0; supertargetdistance = 0.0; supertargetdrivetime = 0.0; targetdistance = 0.0; targetdrivetime = 0.0; walmartdistance = 0.0; walmartdrivetime = 0.0; walmartsupercenterdistance = 0.0; walmartsupercenterdrivetime = 0.0; __av = 0L; */ }
    explicit LOCATION_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const long c15) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14; __av = c15; }
    LOCATION_entry(const LOCATION_entry& other) : locn( other.locn ), zip( other.zip ), rgn_cd( other.rgn_cd ), clim_zn_nbr( other.clim_zn_nbr ), tot_area_sq_ft( other.tot_area_sq_ft ), sell_area_sq_ft( other.sell_area_sq_ft ), avghhi( other.avghhi ), supertargetdistance( other.supertargetdistance ), supertargetdrivetime( other.supertargetdrivetime ), targetdistance( other.targetdistance ), targetdrivetime( other.targetdrivetime ), walmartdistance( other.walmartdistance ), walmartdrivetime( other.walmartdrivetime ), walmartsupercenterdistance( other.walmartsupercenterdistance ), walmartsupercenterdrivetime( other.walmartsupercenterdrivetime ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE LOCATION_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14;  return *this; }
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
  struct LOCATION_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const LOCATION_entry& e) {
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
    FORCE_INLINE static bool equals(const LOCATION_entry& x, const LOCATION_entry& y) {
      return x.locn == y.locn && x.zip == y.zip && x.rgn_cd == y.rgn_cd && x.clim_zn_nbr == y.clim_zn_nbr && x.tot_area_sq_ft == y.tot_area_sq_ft && x.sell_area_sq_ft == y.sell_area_sq_ft && x.avghhi == y.avghhi && x.supertargetdistance == y.supertargetdistance && x.supertargetdrivetime == y.supertargetdrivetime && x.targetdistance == y.targetdistance && x.targetdrivetime == y.targetdrivetime && x.walmartdistance == y.walmartdistance && x.walmartdrivetime == y.walmartdrivetime && x.walmartsupercenterdistance == y.walmartsupercenterdistance && x.walmartsupercenterdrivetime == y.walmartsupercenterdrivetime;
    }
  };
  
  typedef MultiHashMap<LOCATION_entry, long, 
    HashIndex<LOCATION_entry, long, LOCATION_mapkey01234567891011121314_idxfn, true>
  > LOCATION_map;
  typedef HashIndex<LOCATION_entry, long, LOCATION_mapkey01234567891011121314_idxfn, true> HashIndex_LOCATION_map_01234567891011121314;
  
  struct CENSUS_entry {
    long zip; long population; long white; long asian; long pacific; long blackafrican; DOUBLE_TYPE medianage; long occupiedhouseunits; long houseunits; long families; long households; long husbwife; long males; long females; long householdschildren; long hispanic; long __av;  CENSUS_entry* nxt; CENSUS_entry* prv;
    explicit CENSUS_entry() : nxt(nullptr), prv(nullptr) { /*zip = 0L; population = 0L; white = 0L; asian = 0L; pacific = 0L; blackafrican = 0L; medianage = 0.0; occupiedhouseunits = 0L; houseunits = 0L; families = 0L; households = 0L; husbwife = 0L; males = 0L; females = 0L; householdschildren = 0L; hispanic = 0L; __av = 0L; */ }
    explicit CENSUS_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15, const long c16) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15; __av = c16; }
    CENSUS_entry(const CENSUS_entry& other) : zip( other.zip ), population( other.population ), white( other.white ), asian( other.asian ), pacific( other.pacific ), blackafrican( other.blackafrican ), medianage( other.medianage ), occupiedhouseunits( other.occupiedhouseunits ), houseunits( other.houseunits ), families( other.families ), households( other.households ), husbwife( other.husbwife ), males( other.males ), females( other.females ), householdschildren( other.householdschildren ), hispanic( other.hispanic ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE CENSUS_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15;  return *this; }
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
  struct CENSUS_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const CENSUS_entry& e) {
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
    FORCE_INLINE static bool equals(const CENSUS_entry& x, const CENSUS_entry& y) {
      return x.zip == y.zip && x.population == y.population && x.white == y.white && x.asian == y.asian && x.pacific == y.pacific && x.blackafrican == y.blackafrican && x.medianage == y.medianage && x.occupiedhouseunits == y.occupiedhouseunits && x.houseunits == y.houseunits && x.families == y.families && x.households == y.households && x.husbwife == y.husbwife && x.males == y.males && x.females == y.females && x.householdschildren == y.householdschildren && x.hispanic == y.hispanic;
    }
  };
  
  typedef MultiHashMap<CENSUS_entry, long, 
    HashIndex<CENSUS_entry, long, CENSUS_mapkey0123456789101112131415_idxfn, true>
  > CENSUS_map;
  typedef HashIndex<CENSUS_entry, long, CENSUS_mapkey0123456789101112131415_idxfn, true> HashIndex_CENSUS_map_0123456789101112131415;
  
  struct ITEM_entry {
    DOUBLE_TYPE ksn; long subcategory; long category; long categoryCluster; DOUBLE_TYPE prize; long __av;  ITEM_entry* nxt; ITEM_entry* prv;
    explicit ITEM_entry() : nxt(nullptr), prv(nullptr) { /*ksn = 0.0; subcategory = 0L; category = 0L; categoryCluster = 0L; prize = 0.0; __av = 0L; */ }
    explicit ITEM_entry(const DOUBLE_TYPE c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4, const long c5) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4; __av = c5; }
    ITEM_entry(const ITEM_entry& other) : ksn( other.ksn ), subcategory( other.subcategory ), category( other.category ), categoryCluster( other.categoryCluster ), prize( other.prize ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE ITEM_entry& modify(const DOUBLE_TYPE c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4;  return *this; }
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
  struct ITEM_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const ITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      hash_combine(h, e.subcategory);
      hash_combine(h, e.category);
      hash_combine(h, e.categoryCluster);
      hash_combine(h, e.prize);
      return h;
    }
    FORCE_INLINE static bool equals(const ITEM_entry& x, const ITEM_entry& y) {
      return x.ksn == y.ksn && x.subcategory == y.subcategory && x.category == y.category && x.categoryCluster == y.categoryCluster && x.prize == y.prize;
    }
  };
  
  typedef MultiHashMap<ITEM_entry, long, 
    HashIndex<ITEM_entry, long, ITEM_mapkey01234_idxfn, true>
  > ITEM_map;
  typedef HashIndex<ITEM_entry, long, ITEM_mapkey01234_idxfn, true> HashIndex_ITEM_map_01234;
  
  struct WEATHER_entry {
    long locn; long dateid; long rain; long snow; long maxtemp; long mintemp; DOUBLE_TYPE meanwind; long thunder; long __av;  WEATHER_entry* nxt; WEATHER_entry* prv;
    explicit WEATHER_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; dateid = 0L; rain = 0L; snow = 0L; maxtemp = 0L; mintemp = 0L; meanwind = 0.0; thunder = 0L; __av = 0L; */ }
    explicit WEATHER_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7, const long c8) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7; __av = c8; }
    WEATHER_entry(const WEATHER_entry& other) : locn( other.locn ), dateid( other.dateid ), rain( other.rain ), snow( other.snow ), maxtemp( other.maxtemp ), mintemp( other.mintemp ), meanwind( other.meanwind ), thunder( other.thunder ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE WEATHER_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6, const long c7) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7;  return *this; }
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
  struct WEATHER_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const WEATHER_entry& e) {
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
    FORCE_INLINE static bool equals(const WEATHER_entry& x, const WEATHER_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.rain == y.rain && x.snow == y.snow && x.maxtemp == y.maxtemp && x.mintemp == y.mintemp && x.meanwind == y.meanwind && x.thunder == y.thunder;
    }
  };
  
  typedef MultiHashMap<WEATHER_entry, long, 
    HashIndex<WEATHER_entry, long, WEATHER_mapkey01234567_idxfn, true>
  > WEATHER_map;
  typedef HashIndex<WEATHER_entry, long, WEATHER_mapkey01234567_idxfn, true> HashIndex_WEATHER_map_01234567;
  
  struct DEGREE15_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long Deg5; long Deg6; long Deg7; long Deg8; long Deg9; long Deg10; long Deg11; long Deg12; long Deg13; long Deg14; long Deg15; long __av;  DEGREE15_entry* nxt; DEGREE15_entry* prv;
    explicit DEGREE15_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; Deg5 = 0L; Deg6 = 0L; Deg7 = 0L; Deg8 = 0L; Deg9 = 0L; Deg10 = 0L; Deg11 = 0L; Deg12 = 0L; Deg13 = 0L; Deg14 = 0L; Deg15 = 0L; __av = 0L; */ }
    explicit DEGREE15_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12; Deg14 = c13; Deg15 = c14; __av = c15; }
    DEGREE15_entry(const DEGREE15_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), Deg5( other.Deg5 ), Deg6( other.Deg6 ), Deg7( other.Deg7 ), Deg8( other.Deg8 ), Deg9( other.Deg9 ), Deg10( other.Deg10 ), Deg11( other.Deg11 ), Deg12( other.Deg12 ), Deg13( other.Deg13 ), Deg14( other.Deg14 ), Deg15( other.Deg15 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DEGREE15_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12; Deg14 = c13; Deg15 = c14;  return *this; }
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
  struct DEGREE15_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const DEGREE15_entry& e) {
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
    FORCE_INLINE static bool equals(const DEGREE15_entry& x, const DEGREE15_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4 && x.Deg5 == y.Deg5 && x.Deg6 == y.Deg6 && x.Deg7 == y.Deg7 && x.Deg8 == y.Deg8 && x.Deg9 == y.Deg9 && x.Deg10 == y.Deg10 && x.Deg11 == y.Deg11 && x.Deg12 == y.Deg12 && x.Deg13 == y.Deg13 && x.Deg14 == y.Deg14 && x.Deg15 == y.Deg15;
    }
  };
  
  typedef MultiHashMap<DEGREE15_entry, long, 
    HashIndex<DEGREE15_entry, long, DEGREE15_mapkey01234567891011121314_idxfn, true>
  > DEGREE15_map;
  typedef HashIndex<DEGREE15_entry, long, DEGREE15_mapkey01234567891011121314_idxfn, true> HashIndex_DEGREE15_map_01234567891011121314;
  
  struct DEGREE13_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long Deg5; long Deg6; long Deg7; long Deg8; long Deg9; long Deg10; long Deg11; long Deg12; long Deg13; long __av;  DEGREE13_entry* nxt; DEGREE13_entry* prv;
    explicit DEGREE13_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; Deg5 = 0L; Deg6 = 0L; Deg7 = 0L; Deg8 = 0L; Deg9 = 0L; Deg10 = 0L; Deg11 = 0L; Deg12 = 0L; Deg13 = 0L; __av = 0L; */ }
    explicit DEGREE13_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12; __av = c13; }
    DEGREE13_entry(const DEGREE13_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), Deg5( other.Deg5 ), Deg6( other.Deg6 ), Deg7( other.Deg7 ), Deg8( other.Deg8 ), Deg9( other.Deg9 ), Deg10( other.Deg10 ), Deg11( other.Deg11 ), Deg12( other.Deg12 ), Deg13( other.Deg13 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DEGREE13_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; Deg7 = c6; Deg8 = c7; Deg9 = c8; Deg10 = c9; Deg11 = c10; Deg12 = c11; Deg13 = c12;  return *this; }
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
  struct DEGREE13_mapkey0123456789101112_idxfn {
    FORCE_INLINE static size_t hash(const DEGREE13_entry& e) {
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
    FORCE_INLINE static bool equals(const DEGREE13_entry& x, const DEGREE13_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4 && x.Deg5 == y.Deg5 && x.Deg6 == y.Deg6 && x.Deg7 == y.Deg7 && x.Deg8 == y.Deg8 && x.Deg9 == y.Deg9 && x.Deg10 == y.Deg10 && x.Deg11 == y.Deg11 && x.Deg12 == y.Deg12 && x.Deg13 == y.Deg13;
    }
  };
  
  typedef MultiHashMap<DEGREE13_entry, long, 
    HashIndex<DEGREE13_entry, long, DEGREE13_mapkey0123456789101112_idxfn, true>
  > DEGREE13_map;
  typedef HashIndex<DEGREE13_entry, long, DEGREE13_mapkey0123456789101112_idxfn, true> HashIndex_DEGREE13_map_0123456789101112;
  
  struct DEGREE6_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long Deg5; long Deg6; long __av;  DEGREE6_entry* nxt; DEGREE6_entry* prv;
    explicit DEGREE6_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; Deg5 = 0L; Deg6 = 0L; __av = 0L; */ }
    explicit DEGREE6_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5; __av = c6; }
    DEGREE6_entry(const DEGREE6_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), Deg5( other.Deg5 ), Deg6( other.Deg6 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DEGREE6_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; Deg5 = c4; Deg6 = c5;  return *this; }
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
  struct DEGREE6_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const DEGREE6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg1);
      hash_combine(h, e.Deg2);
      hash_combine(h, e.Deg3);
      hash_combine(h, e.Deg4);
      hash_combine(h, e.Deg5);
      hash_combine(h, e.Deg6);
      return h;
    }
    FORCE_INLINE static bool equals(const DEGREE6_entry& x, const DEGREE6_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4 && x.Deg5 == y.Deg5 && x.Deg6 == y.Deg6;
    }
  };
  
  typedef MultiHashMap<DEGREE6_entry, long, 
    HashIndex<DEGREE6_entry, long, DEGREE6_mapkey012345_idxfn, true>
  > DEGREE6_map;
  typedef HashIndex<DEGREE6_entry, long, DEGREE6_mapkey012345_idxfn, true> HashIndex_DEGREE6_map_012345;
  
  struct DEGREE4_entry {
    long Deg1; long Deg2; long Deg3; long Deg4; long __av;  DEGREE4_entry* nxt; DEGREE4_entry* prv;
    explicit DEGREE4_entry() : nxt(nullptr), prv(nullptr) { /*Deg1 = 0L; Deg2 = 0L; Deg3 = 0L; Deg4 = 0L; __av = 0L; */ }
    explicit DEGREE4_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3; __av = c4; }
    DEGREE4_entry(const DEGREE4_entry& other) : Deg1( other.Deg1 ), Deg2( other.Deg2 ), Deg3( other.Deg3 ), Deg4( other.Deg4 ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DEGREE4_entry& modify(const long c0, const long c1, const long c2, const long c3) { Deg1 = c0; Deg2 = c1; Deg3 = c2; Deg4 = c3;  return *this; }
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
  struct DEGREE4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const DEGREE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg1);
      hash_combine(h, e.Deg2);
      hash_combine(h, e.Deg3);
      hash_combine(h, e.Deg4);
      return h;
    }
    FORCE_INLINE static bool equals(const DEGREE4_entry& x, const DEGREE4_entry& y) {
      return x.Deg1 == y.Deg1 && x.Deg2 == y.Deg2 && x.Deg3 == y.Deg3 && x.Deg4 == y.Deg4;
    }
  };
  
  typedef MultiHashMap<DEGREE4_entry, long, 
    HashIndex<DEGREE4_entry, long, DEGREE4_mapkey0123_idxfn, true>
  > DEGREE4_map;
  typedef HashIndex<DEGREE4_entry, long, DEGREE4_mapkey0123_idxfn, true> HashIndex_DEGREE4_map_0123;
  
  struct DEGREE1_entry {
    long Deg; long __av;  DEGREE1_entry* nxt; DEGREE1_entry* prv;
    explicit DEGREE1_entry() : nxt(nullptr), prv(nullptr) { /*Deg = 0L; __av = 0L; */ }
    explicit DEGREE1_entry(const long c0, const long c1) { Deg = c0; __av = c1; }
    DEGREE1_entry(const DEGREE1_entry& other) : Deg( other.Deg ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DEGREE1_entry& modify(const long c0) { Deg = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DEGREE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const DEGREE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg);
      return h;
    }
    FORCE_INLINE static bool equals(const DEGREE1_entry& x, const DEGREE1_entry& y) {
      return x.Deg == y.Deg;
    }
  };
  
  typedef MultiHashMap<DEGREE1_entry, long, 
    HashIndex<DEGREE1_entry, long, DEGREE1_mapkey0_idxfn, true>
  > DEGREE1_map;
  typedef HashIndex<DEGREE1_entry, long, DEGREE1_mapkey0_idxfn, true> HashIndex_DEGREE1_map_0;
  
  struct AGG_Location_entry {
    long locn; long zip; long Deg_rgn_cd; long Deg_clim_zn_nbr; long Deg_tot_area_sq_ft; long Deg_sell_area_sq_ft; long Deg_avghhi; long Deg_supertargetdistance; long Deg_supertargetdrivetime; long Deg_targetdistance; long Deg_targetdrivetime; long Deg_walmartdistance; long Deg_walmartdrivetime; long Deg_walmartsupercenterdistance; long Deg_walmartsupercenterdrivetime; DOUBLE_TYPE __av;  AGG_Location_entry* nxt; AGG_Location_entry* prv;
    explicit AGG_Location_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; zip = 0L; Deg_rgn_cd = 0L; Deg_clim_zn_nbr = 0L; Deg_tot_area_sq_ft = 0L; Deg_sell_area_sq_ft = 0L; Deg_avghhi = 0L; Deg_supertargetdistance = 0L; Deg_supertargetdrivetime = 0L; Deg_targetdistance = 0L; Deg_targetdrivetime = 0L; Deg_walmartdistance = 0L; Deg_walmartdrivetime = 0L; Deg_walmartsupercenterdistance = 0L; Deg_walmartsupercenterdrivetime = 0L; __av = 0.0; */ }
    explicit AGG_Location_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const DOUBLE_TYPE c15) { locn = c0; zip = c1; Deg_rgn_cd = c2; Deg_clim_zn_nbr = c3; Deg_tot_area_sq_ft = c4; Deg_sell_area_sq_ft = c5; Deg_avghhi = c6; Deg_supertargetdistance = c7; Deg_supertargetdrivetime = c8; Deg_targetdistance = c9; Deg_targetdrivetime = c10; Deg_walmartdistance = c11; Deg_walmartdrivetime = c12; Deg_walmartsupercenterdistance = c13; Deg_walmartsupercenterdrivetime = c14; __av = c15; }
    AGG_Location_entry(const AGG_Location_entry& other) : locn( other.locn ), zip( other.zip ), Deg_rgn_cd( other.Deg_rgn_cd ), Deg_clim_zn_nbr( other.Deg_clim_zn_nbr ), Deg_tot_area_sq_ft( other.Deg_tot_area_sq_ft ), Deg_sell_area_sq_ft( other.Deg_sell_area_sq_ft ), Deg_avghhi( other.Deg_avghhi ), Deg_supertargetdistance( other.Deg_supertargetdistance ), Deg_supertargetdrivetime( other.Deg_supertargetdrivetime ), Deg_targetdistance( other.Deg_targetdistance ), Deg_targetdrivetime( other.Deg_targetdrivetime ), Deg_walmartdistance( other.Deg_walmartdistance ), Deg_walmartdrivetime( other.Deg_walmartdrivetime ), Deg_walmartsupercenterdistance( other.Deg_walmartsupercenterdistance ), Deg_walmartsupercenterdrivetime( other.Deg_walmartsupercenterdrivetime ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE AGG_Location_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14) { locn = c0; zip = c1; Deg_rgn_cd = c2; Deg_clim_zn_nbr = c3; Deg_tot_area_sq_ft = c4; Deg_sell_area_sq_ft = c5; Deg_avghhi = c6; Deg_supertargetdistance = c7; Deg_supertargetdrivetime = c8; Deg_targetdistance = c9; Deg_targetdrivetime = c10; Deg_walmartdistance = c11; Deg_walmartdrivetime = c12; Deg_walmartsupercenterdistance = c13; Deg_walmartsupercenterdrivetime = c14;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_rgn_cd);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_clim_zn_nbr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_tot_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_sell_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_avghhi);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_supertargetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_supertargetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_targetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_targetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartsupercenterdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartsupercenterdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG_Location_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const AGG_Location_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      hash_combine(h, e.Deg_rgn_cd);
      hash_combine(h, e.Deg_clim_zn_nbr);
      hash_combine(h, e.Deg_tot_area_sq_ft);
      hash_combine(h, e.Deg_sell_area_sq_ft);
      hash_combine(h, e.Deg_avghhi);
      hash_combine(h, e.Deg_supertargetdistance);
      hash_combine(h, e.Deg_supertargetdrivetime);
      hash_combine(h, e.Deg_targetdistance);
      hash_combine(h, e.Deg_targetdrivetime);
      hash_combine(h, e.Deg_walmartdistance);
      hash_combine(h, e.Deg_walmartdrivetime);
      hash_combine(h, e.Deg_walmartsupercenterdistance);
      hash_combine(h, e.Deg_walmartsupercenterdrivetime);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_Location_entry& x, const AGG_Location_entry& y) {
      return x.locn == y.locn && x.zip == y.zip && x.Deg_rgn_cd == y.Deg_rgn_cd && x.Deg_clim_zn_nbr == y.Deg_clim_zn_nbr && x.Deg_tot_area_sq_ft == y.Deg_tot_area_sq_ft && x.Deg_sell_area_sq_ft == y.Deg_sell_area_sq_ft && x.Deg_avghhi == y.Deg_avghhi && x.Deg_supertargetdistance == y.Deg_supertargetdistance && x.Deg_supertargetdrivetime == y.Deg_supertargetdrivetime && x.Deg_targetdistance == y.Deg_targetdistance && x.Deg_targetdrivetime == y.Deg_targetdrivetime && x.Deg_walmartdistance == y.Deg_walmartdistance && x.Deg_walmartdrivetime == y.Deg_walmartdrivetime && x.Deg_walmartsupercenterdistance == y.Deg_walmartsupercenterdistance && x.Deg_walmartsupercenterdrivetime == y.Deg_walmartsupercenterdrivetime;
    }
  };
  
  typedef MultiHashMap<AGG_Location_entry, DOUBLE_TYPE, 
    HashIndex<AGG_Location_entry, DOUBLE_TYPE, AGG_Location_mapkey01234567891011121314_idxfn, true>
  > AGG_Location_map;
  typedef HashIndex<AGG_Location_entry, DOUBLE_TYPE, AGG_Location_mapkey01234567891011121314_idxfn, true> HashIndex_AGG_Location_map_01234567891011121314;
  
  struct AGG_Census_entry {
    long zip; long Deg_population; long Deg_white; long Deg_asian; long Deg_pacific; long Deg_blackafrican; long Deg_medianage; long Deg_occupiedhouseunits; long Deg_houseunits; long Deg_families; long Deg_households; long Deg_husbwife; long Deg_males; long Deg_females; long Deg_householdschildren; long Deg_hispanic; DOUBLE_TYPE __av;  AGG_Census_entry* nxt; AGG_Census_entry* prv;
    explicit AGG_Census_entry() : nxt(nullptr), prv(nullptr) { /*zip = 0L; Deg_population = 0L; Deg_white = 0L; Deg_asian = 0L; Deg_pacific = 0L; Deg_blackafrican = 0L; Deg_medianage = 0L; Deg_occupiedhouseunits = 0L; Deg_houseunits = 0L; Deg_families = 0L; Deg_households = 0L; Deg_husbwife = 0L; Deg_males = 0L; Deg_females = 0L; Deg_householdschildren = 0L; Deg_hispanic = 0L; __av = 0.0; */ }
    explicit AGG_Census_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15, const DOUBLE_TYPE c16) { zip = c0; Deg_population = c1; Deg_white = c2; Deg_asian = c3; Deg_pacific = c4; Deg_blackafrican = c5; Deg_medianage = c6; Deg_occupiedhouseunits = c7; Deg_houseunits = c8; Deg_families = c9; Deg_households = c10; Deg_husbwife = c11; Deg_males = c12; Deg_females = c13; Deg_householdschildren = c14; Deg_hispanic = c15; __av = c16; }
    AGG_Census_entry(const AGG_Census_entry& other) : zip( other.zip ), Deg_population( other.Deg_population ), Deg_white( other.Deg_white ), Deg_asian( other.Deg_asian ), Deg_pacific( other.Deg_pacific ), Deg_blackafrican( other.Deg_blackafrican ), Deg_medianage( other.Deg_medianage ), Deg_occupiedhouseunits( other.Deg_occupiedhouseunits ), Deg_houseunits( other.Deg_houseunits ), Deg_families( other.Deg_families ), Deg_households( other.Deg_households ), Deg_husbwife( other.Deg_husbwife ), Deg_males( other.Deg_males ), Deg_females( other.Deg_females ), Deg_householdschildren( other.Deg_householdschildren ), Deg_hispanic( other.Deg_hispanic ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE AGG_Census_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15) { zip = c0; Deg_population = c1; Deg_white = c2; Deg_asian = c3; Deg_pacific = c4; Deg_blackafrican = c5; Deg_medianage = c6; Deg_occupiedhouseunits = c7; Deg_houseunits = c8; Deg_families = c9; Deg_households = c10; Deg_husbwife = c11; Deg_males = c12; Deg_females = c13; Deg_householdschildren = c14; Deg_hispanic = c15;  return *this; }
    FORCE_INLINE AGG_Census_entry& modify0(const long c0) { zip = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_population);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_white);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_asian);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_pacific);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_blackafrican);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_medianage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_occupiedhouseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_houseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_families);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_husbwife);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_males);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_females);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_householdschildren);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_hispanic);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG_Census_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const AGG_Census_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      hash_combine(h, e.Deg_population);
      hash_combine(h, e.Deg_white);
      hash_combine(h, e.Deg_asian);
      hash_combine(h, e.Deg_pacific);
      hash_combine(h, e.Deg_blackafrican);
      hash_combine(h, e.Deg_medianage);
      hash_combine(h, e.Deg_occupiedhouseunits);
      hash_combine(h, e.Deg_houseunits);
      hash_combine(h, e.Deg_families);
      hash_combine(h, e.Deg_households);
      hash_combine(h, e.Deg_husbwife);
      hash_combine(h, e.Deg_males);
      hash_combine(h, e.Deg_females);
      hash_combine(h, e.Deg_householdschildren);
      hash_combine(h, e.Deg_hispanic);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_Census_entry& x, const AGG_Census_entry& y) {
      return x.zip == y.zip && x.Deg_population == y.Deg_population && x.Deg_white == y.Deg_white && x.Deg_asian == y.Deg_asian && x.Deg_pacific == y.Deg_pacific && x.Deg_blackafrican == y.Deg_blackafrican && x.Deg_medianage == y.Deg_medianage && x.Deg_occupiedhouseunits == y.Deg_occupiedhouseunits && x.Deg_houseunits == y.Deg_houseunits && x.Deg_families == y.Deg_families && x.Deg_households == y.Deg_households && x.Deg_husbwife == y.Deg_husbwife && x.Deg_males == y.Deg_males && x.Deg_females == y.Deg_females && x.Deg_householdschildren == y.Deg_householdschildren && x.Deg_hispanic == y.Deg_hispanic;
    }
  };
  
  struct AGG_Census_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG_Census_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_Census_entry& x, const AGG_Census_entry& y) {
      return x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<AGG_Census_entry, DOUBLE_TYPE, 
    HashIndex<AGG_Census_entry, DOUBLE_TYPE, AGG_Census_mapkey0123456789101112131415_idxfn, true>,
    HashIndex<AGG_Census_entry, DOUBLE_TYPE, AGG_Census_mapkey0_idxfn, false>
  > AGG_Census_map;
  typedef HashIndex<AGG_Census_entry, DOUBLE_TYPE, AGG_Census_mapkey0123456789101112131415_idxfn, true> HashIndex_AGG_Census_map_0123456789101112131415;
  typedef HashIndex<AGG_Census_entry, DOUBLE_TYPE, AGG_Census_mapkey0_idxfn, false> HashIndex_AGG_Census_map_0;
  
  struct AGG_Item_entry {
    DOUBLE_TYPE ksn; long Deg_subcategory; long Deg_category; long Deg_categoryCluster; long Deg_prize; DOUBLE_TYPE __av;  AGG_Item_entry* nxt; AGG_Item_entry* prv;
    explicit AGG_Item_entry() : nxt(nullptr), prv(nullptr) { /*ksn = 0.0; Deg_subcategory = 0L; Deg_category = 0L; Deg_categoryCluster = 0L; Deg_prize = 0L; __av = 0.0; */ }
    explicit AGG_Item_entry(const DOUBLE_TYPE c0, const long c1, const long c2, const long c3, const long c4, const DOUBLE_TYPE c5) { ksn = c0; Deg_subcategory = c1; Deg_category = c2; Deg_categoryCluster = c3; Deg_prize = c4; __av = c5; }
    AGG_Item_entry(const AGG_Item_entry& other) : ksn( other.ksn ), Deg_subcategory( other.Deg_subcategory ), Deg_category( other.Deg_category ), Deg_categoryCluster( other.Deg_categoryCluster ), Deg_prize( other.Deg_prize ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE AGG_Item_entry& modify(const DOUBLE_TYPE c0, const long c1, const long c2, const long c3, const long c4) { ksn = c0; Deg_subcategory = c1; Deg_category = c2; Deg_categoryCluster = c3; Deg_prize = c4;  return *this; }
    FORCE_INLINE AGG_Item_entry& modify0(const DOUBLE_TYPE c0) { ksn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_categoryCluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG_Item_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const AGG_Item_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      hash_combine(h, e.Deg_subcategory);
      hash_combine(h, e.Deg_category);
      hash_combine(h, e.Deg_categoryCluster);
      hash_combine(h, e.Deg_prize);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_Item_entry& x, const AGG_Item_entry& y) {
      return x.ksn == y.ksn && x.Deg_subcategory == y.Deg_subcategory && x.Deg_category == y.Deg_category && x.Deg_categoryCluster == y.Deg_categoryCluster && x.Deg_prize == y.Deg_prize;
    }
  };
  
  struct AGG_Item_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG_Item_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_Item_entry& x, const AGG_Item_entry& y) {
      return x.ksn == y.ksn;
    }
  };
  
  typedef MultiHashMap<AGG_Item_entry, DOUBLE_TYPE, 
    HashIndex<AGG_Item_entry, DOUBLE_TYPE, AGG_Item_mapkey01234_idxfn, true>,
    HashIndex<AGG_Item_entry, DOUBLE_TYPE, AGG_Item_mapkey0_idxfn, false>
  > AGG_Item_map;
  typedef HashIndex<AGG_Item_entry, DOUBLE_TYPE, AGG_Item_mapkey01234_idxfn, true> HashIndex_AGG_Item_map_01234;
  typedef HashIndex<AGG_Item_entry, DOUBLE_TYPE, AGG_Item_mapkey0_idxfn, false> HashIndex_AGG_Item_map_0;
  
  struct AGG_Weather_entry {
    long locn; long dateid; long Deg_rain; long Deg_snow; long Deg_maxtemp; long Deg_mintemp; long Deg_meanwind; long Deg_thunder; DOUBLE_TYPE __av;  AGG_Weather_entry* nxt; AGG_Weather_entry* prv;
    explicit AGG_Weather_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; dateid = 0L; Deg_rain = 0L; Deg_snow = 0L; Deg_maxtemp = 0L; Deg_mintemp = 0L; Deg_meanwind = 0L; Deg_thunder = 0L; __av = 0.0; */ }
    explicit AGG_Weather_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const DOUBLE_TYPE c8) { locn = c0; dateid = c1; Deg_rain = c2; Deg_snow = c3; Deg_maxtemp = c4; Deg_mintemp = c5; Deg_meanwind = c6; Deg_thunder = c7; __av = c8; }
    AGG_Weather_entry(const AGG_Weather_entry& other) : locn( other.locn ), dateid( other.dateid ), Deg_rain( other.Deg_rain ), Deg_snow( other.Deg_snow ), Deg_maxtemp( other.Deg_maxtemp ), Deg_mintemp( other.Deg_mintemp ), Deg_meanwind( other.Deg_meanwind ), Deg_thunder( other.Deg_thunder ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE AGG_Weather_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7) { locn = c0; dateid = c1; Deg_rain = c2; Deg_snow = c3; Deg_maxtemp = c4; Deg_mintemp = c5; Deg_meanwind = c6; Deg_thunder = c7;  return *this; }
    FORCE_INLINE AGG_Weather_entry& modify01(const long c0, const long c1) { locn = c0; dateid = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_snow);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_maxtemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_mintemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_meanwind);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_thunder);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG_Weather_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const AGG_Weather_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.Deg_rain);
      hash_combine(h, e.Deg_snow);
      hash_combine(h, e.Deg_maxtemp);
      hash_combine(h, e.Deg_mintemp);
      hash_combine(h, e.Deg_meanwind);
      hash_combine(h, e.Deg_thunder);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_Weather_entry& x, const AGG_Weather_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.Deg_rain == y.Deg_rain && x.Deg_snow == y.Deg_snow && x.Deg_maxtemp == y.Deg_maxtemp && x.Deg_mintemp == y.Deg_mintemp && x.Deg_meanwind == y.Deg_meanwind && x.Deg_thunder == y.Deg_thunder;
    }
  };
  
  struct AGG_Weather_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG_Weather_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_Weather_entry& x, const AGG_Weather_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<AGG_Weather_entry, DOUBLE_TYPE, 
    HashIndex<AGG_Weather_entry, DOUBLE_TYPE, AGG_Weather_mapkey01234567_idxfn, true>,
    HashIndex<AGG_Weather_entry, DOUBLE_TYPE, AGG_Weather_mapkey01_idxfn, false>
  > AGG_Weather_map;
  typedef HashIndex<AGG_Weather_entry, DOUBLE_TYPE, AGG_Weather_mapkey01234567_idxfn, true> HashIndex_AGG_Weather_map_01234567;
  typedef HashIndex<AGG_Weather_entry, DOUBLE_TYPE, AGG_Weather_mapkey01_idxfn, false> HashIndex_AGG_Weather_map_01;
  
  struct AGG_LC_entry {
    long locn; long Deg_zip; long Deg_rgn_cd; long Deg_clim_zn_nbr; long Deg_tot_area_sq_ft; long Deg_sell_area_sq_ft; long Deg_avghhi; long Deg_supertargetdistance; long Deg_supertargetdrivetime; long Deg_targetdistance; long Deg_targetdrivetime; long Deg_walmartdistance; long Deg_walmartdrivetime; long Deg_walmartsupercenterdistance; long Deg_walmartsupercenterdrivetime; long Deg_population; long Deg_white; long Deg_asian; long Deg_pacific; long Deg_blackafrican; long Deg_medianage; long Deg_occupiedhouseunits; long Deg_houseunits; long Deg_families; long Deg_households; long Deg_husbwife; long Deg_males; long Deg_females; long Deg_householdschildren; long Deg_hispanic; DOUBLE_TYPE __av;  AGG_LC_entry* nxt; AGG_LC_entry* prv;
    explicit AGG_LC_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; Deg_zip = 0L; Deg_rgn_cd = 0L; Deg_clim_zn_nbr = 0L; Deg_tot_area_sq_ft = 0L; Deg_sell_area_sq_ft = 0L; Deg_avghhi = 0L; Deg_supertargetdistance = 0L; Deg_supertargetdrivetime = 0L; Deg_targetdistance = 0L; Deg_targetdrivetime = 0L; Deg_walmartdistance = 0L; Deg_walmartdrivetime = 0L; Deg_walmartsupercenterdistance = 0L; Deg_walmartsupercenterdrivetime = 0L; Deg_population = 0L; Deg_white = 0L; Deg_asian = 0L; Deg_pacific = 0L; Deg_blackafrican = 0L; Deg_medianage = 0L; Deg_occupiedhouseunits = 0L; Deg_houseunits = 0L; Deg_families = 0L; Deg_households = 0L; Deg_husbwife = 0L; Deg_males = 0L; Deg_females = 0L; Deg_householdschildren = 0L; Deg_hispanic = 0L; __av = 0.0; */ }
    explicit AGG_LC_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15, const long c16, const long c17, const long c18, const long c19, const long c20, const long c21, const long c22, const long c23, const long c24, const long c25, const long c26, const long c27, const long c28, const long c29, const DOUBLE_TYPE c30) { locn = c0; Deg_zip = c1; Deg_rgn_cd = c2; Deg_clim_zn_nbr = c3; Deg_tot_area_sq_ft = c4; Deg_sell_area_sq_ft = c5; Deg_avghhi = c6; Deg_supertargetdistance = c7; Deg_supertargetdrivetime = c8; Deg_targetdistance = c9; Deg_targetdrivetime = c10; Deg_walmartdistance = c11; Deg_walmartdrivetime = c12; Deg_walmartsupercenterdistance = c13; Deg_walmartsupercenterdrivetime = c14; Deg_population = c15; Deg_white = c16; Deg_asian = c17; Deg_pacific = c18; Deg_blackafrican = c19; Deg_medianage = c20; Deg_occupiedhouseunits = c21; Deg_houseunits = c22; Deg_families = c23; Deg_households = c24; Deg_husbwife = c25; Deg_males = c26; Deg_females = c27; Deg_householdschildren = c28; Deg_hispanic = c29; __av = c30; }
    AGG_LC_entry(const AGG_LC_entry& other) : locn( other.locn ), Deg_zip( other.Deg_zip ), Deg_rgn_cd( other.Deg_rgn_cd ), Deg_clim_zn_nbr( other.Deg_clim_zn_nbr ), Deg_tot_area_sq_ft( other.Deg_tot_area_sq_ft ), Deg_sell_area_sq_ft( other.Deg_sell_area_sq_ft ), Deg_avghhi( other.Deg_avghhi ), Deg_supertargetdistance( other.Deg_supertargetdistance ), Deg_supertargetdrivetime( other.Deg_supertargetdrivetime ), Deg_targetdistance( other.Deg_targetdistance ), Deg_targetdrivetime( other.Deg_targetdrivetime ), Deg_walmartdistance( other.Deg_walmartdistance ), Deg_walmartdrivetime( other.Deg_walmartdrivetime ), Deg_walmartsupercenterdistance( other.Deg_walmartsupercenterdistance ), Deg_walmartsupercenterdrivetime( other.Deg_walmartsupercenterdrivetime ), Deg_population( other.Deg_population ), Deg_white( other.Deg_white ), Deg_asian( other.Deg_asian ), Deg_pacific( other.Deg_pacific ), Deg_blackafrican( other.Deg_blackafrican ), Deg_medianage( other.Deg_medianage ), Deg_occupiedhouseunits( other.Deg_occupiedhouseunits ), Deg_houseunits( other.Deg_houseunits ), Deg_families( other.Deg_families ), Deg_households( other.Deg_households ), Deg_husbwife( other.Deg_husbwife ), Deg_males( other.Deg_males ), Deg_females( other.Deg_females ), Deg_householdschildren( other.Deg_householdschildren ), Deg_hispanic( other.Deg_hispanic ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE AGG_LC_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15, const long c16, const long c17, const long c18, const long c19, const long c20, const long c21, const long c22, const long c23, const long c24, const long c25, const long c26, const long c27, const long c28, const long c29) { locn = c0; Deg_zip = c1; Deg_rgn_cd = c2; Deg_clim_zn_nbr = c3; Deg_tot_area_sq_ft = c4; Deg_sell_area_sq_ft = c5; Deg_avghhi = c6; Deg_supertargetdistance = c7; Deg_supertargetdrivetime = c8; Deg_targetdistance = c9; Deg_targetdrivetime = c10; Deg_walmartdistance = c11; Deg_walmartdrivetime = c12; Deg_walmartsupercenterdistance = c13; Deg_walmartsupercenterdrivetime = c14; Deg_population = c15; Deg_white = c16; Deg_asian = c17; Deg_pacific = c18; Deg_blackafrican = c19; Deg_medianage = c20; Deg_occupiedhouseunits = c21; Deg_houseunits = c22; Deg_families = c23; Deg_households = c24; Deg_husbwife = c25; Deg_males = c26; Deg_females = c27; Deg_householdschildren = c28; Deg_hispanic = c29;  return *this; }
    FORCE_INLINE AGG_LC_entry& modify0(const long c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_rgn_cd);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_clim_zn_nbr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_tot_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_sell_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_avghhi);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_supertargetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_supertargetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_targetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_targetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartsupercenterdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartsupercenterdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_population);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_white);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_asian);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_pacific);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_blackafrican);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_medianage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_occupiedhouseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_houseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_families);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_husbwife);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_males);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_females);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_householdschildren);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_hispanic);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG_LC_mapkey01234567891011121314151617181920212223242526272829_idxfn {
    FORCE_INLINE static size_t hash(const AGG_LC_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.Deg_zip);
      hash_combine(h, e.Deg_rgn_cd);
      hash_combine(h, e.Deg_clim_zn_nbr);
      hash_combine(h, e.Deg_tot_area_sq_ft);
      hash_combine(h, e.Deg_sell_area_sq_ft);
      hash_combine(h, e.Deg_avghhi);
      hash_combine(h, e.Deg_supertargetdistance);
      hash_combine(h, e.Deg_supertargetdrivetime);
      hash_combine(h, e.Deg_targetdistance);
      hash_combine(h, e.Deg_targetdrivetime);
      hash_combine(h, e.Deg_walmartdistance);
      hash_combine(h, e.Deg_walmartdrivetime);
      hash_combine(h, e.Deg_walmartsupercenterdistance);
      hash_combine(h, e.Deg_walmartsupercenterdrivetime);
      hash_combine(h, e.Deg_population);
      hash_combine(h, e.Deg_white);
      hash_combine(h, e.Deg_asian);
      hash_combine(h, e.Deg_pacific);
      hash_combine(h, e.Deg_blackafrican);
      hash_combine(h, e.Deg_medianage);
      hash_combine(h, e.Deg_occupiedhouseunits);
      hash_combine(h, e.Deg_houseunits);
      hash_combine(h, e.Deg_families);
      hash_combine(h, e.Deg_households);
      hash_combine(h, e.Deg_husbwife);
      hash_combine(h, e.Deg_males);
      hash_combine(h, e.Deg_females);
      hash_combine(h, e.Deg_householdschildren);
      hash_combine(h, e.Deg_hispanic);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_LC_entry& x, const AGG_LC_entry& y) {
      return x.locn == y.locn && x.Deg_zip == y.Deg_zip && x.Deg_rgn_cd == y.Deg_rgn_cd && x.Deg_clim_zn_nbr == y.Deg_clim_zn_nbr && x.Deg_tot_area_sq_ft == y.Deg_tot_area_sq_ft && x.Deg_sell_area_sq_ft == y.Deg_sell_area_sq_ft && x.Deg_avghhi == y.Deg_avghhi && x.Deg_supertargetdistance == y.Deg_supertargetdistance && x.Deg_supertargetdrivetime == y.Deg_supertargetdrivetime && x.Deg_targetdistance == y.Deg_targetdistance && x.Deg_targetdrivetime == y.Deg_targetdrivetime && x.Deg_walmartdistance == y.Deg_walmartdistance && x.Deg_walmartdrivetime == y.Deg_walmartdrivetime && x.Deg_walmartsupercenterdistance == y.Deg_walmartsupercenterdistance && x.Deg_walmartsupercenterdrivetime == y.Deg_walmartsupercenterdrivetime && x.Deg_population == y.Deg_population && x.Deg_white == y.Deg_white && x.Deg_asian == y.Deg_asian && x.Deg_pacific == y.Deg_pacific && x.Deg_blackafrican == y.Deg_blackafrican && x.Deg_medianage == y.Deg_medianage && x.Deg_occupiedhouseunits == y.Deg_occupiedhouseunits && x.Deg_houseunits == y.Deg_houseunits && x.Deg_families == y.Deg_families && x.Deg_households == y.Deg_households && x.Deg_husbwife == y.Deg_husbwife && x.Deg_males == y.Deg_males && x.Deg_females == y.Deg_females && x.Deg_householdschildren == y.Deg_householdschildren && x.Deg_hispanic == y.Deg_hispanic;
    }
  };
  
  struct AGG_LC_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG_LC_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_LC_entry& x, const AGG_LC_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<AGG_LC_entry, DOUBLE_TYPE, 
    HashIndex<AGG_LC_entry, DOUBLE_TYPE, AGG_LC_mapkey01234567891011121314151617181920212223242526272829_idxfn, true>,
    HashIndex<AGG_LC_entry, DOUBLE_TYPE, AGG_LC_mapkey0_idxfn, false>
  > AGG_LC_map;
  typedef HashIndex<AGG_LC_entry, DOUBLE_TYPE, AGG_LC_mapkey01234567891011121314151617181920212223242526272829_idxfn, true> HashIndex_AGG_LC_map_01234567891011121314151617181920212223242526272829;
  typedef HashIndex<AGG_LC_entry, DOUBLE_TYPE, AGG_LC_mapkey0_idxfn, false> HashIndex_AGG_LC_map_0;
  
  struct AGG_entry {
    long Deg_locn; long Deg_dateid; long Deg_ksn; long Deg_inventoryunits; long Deg_subcategory; long Deg_category; long Deg_categoryCluster; long Deg_prize; long Deg_rain; long Deg_snow; long Deg_maxtemp; long Deg_mintemp; long Deg_meanwind; long Deg_thunder; long Deg_zip; long Deg_rgn_cd; long Deg_clim_zn_nbr; long Deg_tot_area_sq_ft; long Deg_sell_area_sq_ft; long Deg_avghhi; long Deg_supertargetdistance; long Deg_supertargetdrivetime; long Deg_targetdistance; long Deg_targetdrivetime; long Deg_walmartdistance; long Deg_walmartdrivetime; long Deg_walmartsupercenterdistance; long Deg_walmartsupercenterdrivetime; long Deg_population; long Deg_white; long Deg_asian; long Deg_pacific; long Deg_blackafrican; long Deg_medianage; long Deg_occupiedhouseunits; long Deg_houseunits; long Deg_families; long Deg_households; long Deg_husbwife; long Deg_males; long Deg_females; long Deg_householdschildren; long Deg_hispanic; DOUBLE_TYPE __av;  AGG_entry* nxt; AGG_entry* prv;
    explicit AGG_entry() : nxt(nullptr), prv(nullptr) { /*Deg_locn = 0L; Deg_dateid = 0L; Deg_ksn = 0L; Deg_inventoryunits = 0L; Deg_subcategory = 0L; Deg_category = 0L; Deg_categoryCluster = 0L; Deg_prize = 0L; Deg_rain = 0L; Deg_snow = 0L; Deg_maxtemp = 0L; Deg_mintemp = 0L; Deg_meanwind = 0L; Deg_thunder = 0L; Deg_zip = 0L; Deg_rgn_cd = 0L; Deg_clim_zn_nbr = 0L; Deg_tot_area_sq_ft = 0L; Deg_sell_area_sq_ft = 0L; Deg_avghhi = 0L; Deg_supertargetdistance = 0L; Deg_supertargetdrivetime = 0L; Deg_targetdistance = 0L; Deg_targetdrivetime = 0L; Deg_walmartdistance = 0L; Deg_walmartdrivetime = 0L; Deg_walmartsupercenterdistance = 0L; Deg_walmartsupercenterdrivetime = 0L; Deg_population = 0L; Deg_white = 0L; Deg_asian = 0L; Deg_pacific = 0L; Deg_blackafrican = 0L; Deg_medianage = 0L; Deg_occupiedhouseunits = 0L; Deg_houseunits = 0L; Deg_families = 0L; Deg_households = 0L; Deg_husbwife = 0L; Deg_males = 0L; Deg_females = 0L; Deg_householdschildren = 0L; Deg_hispanic = 0L; __av = 0.0; */ }
    explicit AGG_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15, const long c16, const long c17, const long c18, const long c19, const long c20, const long c21, const long c22, const long c23, const long c24, const long c25, const long c26, const long c27, const long c28, const long c29, const long c30, const long c31, const long c32, const long c33, const long c34, const long c35, const long c36, const long c37, const long c38, const long c39, const long c40, const long c41, const long c42, const DOUBLE_TYPE c43) { Deg_locn = c0; Deg_dateid = c1; Deg_ksn = c2; Deg_inventoryunits = c3; Deg_subcategory = c4; Deg_category = c5; Deg_categoryCluster = c6; Deg_prize = c7; Deg_rain = c8; Deg_snow = c9; Deg_maxtemp = c10; Deg_mintemp = c11; Deg_meanwind = c12; Deg_thunder = c13; Deg_zip = c14; Deg_rgn_cd = c15; Deg_clim_zn_nbr = c16; Deg_tot_area_sq_ft = c17; Deg_sell_area_sq_ft = c18; Deg_avghhi = c19; Deg_supertargetdistance = c20; Deg_supertargetdrivetime = c21; Deg_targetdistance = c22; Deg_targetdrivetime = c23; Deg_walmartdistance = c24; Deg_walmartdrivetime = c25; Deg_walmartsupercenterdistance = c26; Deg_walmartsupercenterdrivetime = c27; Deg_population = c28; Deg_white = c29; Deg_asian = c30; Deg_pacific = c31; Deg_blackafrican = c32; Deg_medianage = c33; Deg_occupiedhouseunits = c34; Deg_houseunits = c35; Deg_families = c36; Deg_households = c37; Deg_husbwife = c38; Deg_males = c39; Deg_females = c40; Deg_householdschildren = c41; Deg_hispanic = c42; __av = c43; }
    AGG_entry(const AGG_entry& other) : Deg_locn( other.Deg_locn ), Deg_dateid( other.Deg_dateid ), Deg_ksn( other.Deg_ksn ), Deg_inventoryunits( other.Deg_inventoryunits ), Deg_subcategory( other.Deg_subcategory ), Deg_category( other.Deg_category ), Deg_categoryCluster( other.Deg_categoryCluster ), Deg_prize( other.Deg_prize ), Deg_rain( other.Deg_rain ), Deg_snow( other.Deg_snow ), Deg_maxtemp( other.Deg_maxtemp ), Deg_mintemp( other.Deg_mintemp ), Deg_meanwind( other.Deg_meanwind ), Deg_thunder( other.Deg_thunder ), Deg_zip( other.Deg_zip ), Deg_rgn_cd( other.Deg_rgn_cd ), Deg_clim_zn_nbr( other.Deg_clim_zn_nbr ), Deg_tot_area_sq_ft( other.Deg_tot_area_sq_ft ), Deg_sell_area_sq_ft( other.Deg_sell_area_sq_ft ), Deg_avghhi( other.Deg_avghhi ), Deg_supertargetdistance( other.Deg_supertargetdistance ), Deg_supertargetdrivetime( other.Deg_supertargetdrivetime ), Deg_targetdistance( other.Deg_targetdistance ), Deg_targetdrivetime( other.Deg_targetdrivetime ), Deg_walmartdistance( other.Deg_walmartdistance ), Deg_walmartdrivetime( other.Deg_walmartdrivetime ), Deg_walmartsupercenterdistance( other.Deg_walmartsupercenterdistance ), Deg_walmartsupercenterdrivetime( other.Deg_walmartsupercenterdrivetime ), Deg_population( other.Deg_population ), Deg_white( other.Deg_white ), Deg_asian( other.Deg_asian ), Deg_pacific( other.Deg_pacific ), Deg_blackafrican( other.Deg_blackafrican ), Deg_medianage( other.Deg_medianage ), Deg_occupiedhouseunits( other.Deg_occupiedhouseunits ), Deg_houseunits( other.Deg_houseunits ), Deg_families( other.Deg_families ), Deg_households( other.Deg_households ), Deg_husbwife( other.Deg_husbwife ), Deg_males( other.Deg_males ), Deg_females( other.Deg_females ), Deg_householdschildren( other.Deg_householdschildren ), Deg_hispanic( other.Deg_hispanic ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE AGG_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const long c14, const long c15, const long c16, const long c17, const long c18, const long c19, const long c20, const long c21, const long c22, const long c23, const long c24, const long c25, const long c26, const long c27, const long c28, const long c29, const long c30, const long c31, const long c32, const long c33, const long c34, const long c35, const long c36, const long c37, const long c38, const long c39, const long c40, const long c41, const long c42) { Deg_locn = c0; Deg_dateid = c1; Deg_ksn = c2; Deg_inventoryunits = c3; Deg_subcategory = c4; Deg_category = c5; Deg_categoryCluster = c6; Deg_prize = c7; Deg_rain = c8; Deg_snow = c9; Deg_maxtemp = c10; Deg_mintemp = c11; Deg_meanwind = c12; Deg_thunder = c13; Deg_zip = c14; Deg_rgn_cd = c15; Deg_clim_zn_nbr = c16; Deg_tot_area_sq_ft = c17; Deg_sell_area_sq_ft = c18; Deg_avghhi = c19; Deg_supertargetdistance = c20; Deg_supertargetdrivetime = c21; Deg_targetdistance = c22; Deg_targetdrivetime = c23; Deg_walmartdistance = c24; Deg_walmartdrivetime = c25; Deg_walmartsupercenterdistance = c26; Deg_walmartsupercenterdrivetime = c27; Deg_population = c28; Deg_white = c29; Deg_asian = c30; Deg_pacific = c31; Deg_blackafrican = c32; Deg_medianage = c33; Deg_occupiedhouseunits = c34; Deg_houseunits = c35; Deg_families = c36; Deg_households = c37; Deg_husbwife = c38; Deg_males = c39; Deg_females = c40; Deg_householdschildren = c41; Deg_hispanic = c42;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_categoryCluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_snow);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_maxtemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_mintemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_meanwind);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_thunder);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_rgn_cd);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_clim_zn_nbr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_tot_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_sell_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_avghhi);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_supertargetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_supertargetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_targetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_targetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartsupercenterdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_walmartsupercenterdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_population);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_white);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_asian);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_pacific);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_blackafrican);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_medianage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_occupiedhouseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_houseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_families);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_husbwife);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_males);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_females);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_householdschildren);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_hispanic);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG_mapkey0123456789101112131415161718192021222324252627282930313233343536373839404142_idxfn {
    FORCE_INLINE static size_t hash(const AGG_entry& e) {
      size_t h = 0;
      hash_combine(h, e.Deg_locn);
      hash_combine(h, e.Deg_dateid);
      hash_combine(h, e.Deg_ksn);
      hash_combine(h, e.Deg_inventoryunits);
      hash_combine(h, e.Deg_subcategory);
      hash_combine(h, e.Deg_category);
      hash_combine(h, e.Deg_categoryCluster);
      hash_combine(h, e.Deg_prize);
      hash_combine(h, e.Deg_rain);
      hash_combine(h, e.Deg_snow);
      hash_combine(h, e.Deg_maxtemp);
      hash_combine(h, e.Deg_mintemp);
      hash_combine(h, e.Deg_meanwind);
      hash_combine(h, e.Deg_thunder);
      hash_combine(h, e.Deg_zip);
      hash_combine(h, e.Deg_rgn_cd);
      hash_combine(h, e.Deg_clim_zn_nbr);
      hash_combine(h, e.Deg_tot_area_sq_ft);
      hash_combine(h, e.Deg_sell_area_sq_ft);
      hash_combine(h, e.Deg_avghhi);
      hash_combine(h, e.Deg_supertargetdistance);
      hash_combine(h, e.Deg_supertargetdrivetime);
      hash_combine(h, e.Deg_targetdistance);
      hash_combine(h, e.Deg_targetdrivetime);
      hash_combine(h, e.Deg_walmartdistance);
      hash_combine(h, e.Deg_walmartdrivetime);
      hash_combine(h, e.Deg_walmartsupercenterdistance);
      hash_combine(h, e.Deg_walmartsupercenterdrivetime);
      hash_combine(h, e.Deg_population);
      hash_combine(h, e.Deg_white);
      hash_combine(h, e.Deg_asian);
      hash_combine(h, e.Deg_pacific);
      hash_combine(h, e.Deg_blackafrican);
      hash_combine(h, e.Deg_medianage);
      hash_combine(h, e.Deg_occupiedhouseunits);
      hash_combine(h, e.Deg_houseunits);
      hash_combine(h, e.Deg_families);
      hash_combine(h, e.Deg_households);
      hash_combine(h, e.Deg_husbwife);
      hash_combine(h, e.Deg_males);
      hash_combine(h, e.Deg_females);
      hash_combine(h, e.Deg_householdschildren);
      hash_combine(h, e.Deg_hispanic);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG_entry& x, const AGG_entry& y) {
      return x.Deg_locn == y.Deg_locn && x.Deg_dateid == y.Deg_dateid && x.Deg_ksn == y.Deg_ksn && x.Deg_inventoryunits == y.Deg_inventoryunits && x.Deg_subcategory == y.Deg_subcategory && x.Deg_category == y.Deg_category && x.Deg_categoryCluster == y.Deg_categoryCluster && x.Deg_prize == y.Deg_prize && x.Deg_rain == y.Deg_rain && x.Deg_snow == y.Deg_snow && x.Deg_maxtemp == y.Deg_maxtemp && x.Deg_mintemp == y.Deg_mintemp && x.Deg_meanwind == y.Deg_meanwind && x.Deg_thunder == y.Deg_thunder && x.Deg_zip == y.Deg_zip && x.Deg_rgn_cd == y.Deg_rgn_cd && x.Deg_clim_zn_nbr == y.Deg_clim_zn_nbr && x.Deg_tot_area_sq_ft == y.Deg_tot_area_sq_ft && x.Deg_sell_area_sq_ft == y.Deg_sell_area_sq_ft && x.Deg_avghhi == y.Deg_avghhi && x.Deg_supertargetdistance == y.Deg_supertargetdistance && x.Deg_supertargetdrivetime == y.Deg_supertargetdrivetime && x.Deg_targetdistance == y.Deg_targetdistance && x.Deg_targetdrivetime == y.Deg_targetdrivetime && x.Deg_walmartdistance == y.Deg_walmartdistance && x.Deg_walmartdrivetime == y.Deg_walmartdrivetime && x.Deg_walmartsupercenterdistance == y.Deg_walmartsupercenterdistance && x.Deg_walmartsupercenterdrivetime == y.Deg_walmartsupercenterdrivetime && x.Deg_population == y.Deg_population && x.Deg_white == y.Deg_white && x.Deg_asian == y.Deg_asian && x.Deg_pacific == y.Deg_pacific && x.Deg_blackafrican == y.Deg_blackafrican && x.Deg_medianage == y.Deg_medianage && x.Deg_occupiedhouseunits == y.Deg_occupiedhouseunits && x.Deg_houseunits == y.Deg_houseunits && x.Deg_families == y.Deg_families && x.Deg_households == y.Deg_households && x.Deg_husbwife == y.Deg_husbwife && x.Deg_males == y.Deg_males && x.Deg_females == y.Deg_females && x.Deg_householdschildren == y.Deg_householdschildren && x.Deg_hispanic == y.Deg_hispanic;
    }
  };
  
  typedef MultiHashMap<AGG_entry, DOUBLE_TYPE, 
    HashIndex<AGG_entry, DOUBLE_TYPE, AGG_mapkey0123456789101112131415161718192021222324252627282930313233343536373839404142_idxfn, true>
  > AGG_map;
  typedef HashIndex<AGG_entry, DOUBLE_TYPE, AGG_mapkey0123456789101112131415161718192021222324252627282930313233343536373839404142_idxfn, true> HashIndex_AGG_map_0123456789101112131415161718192021222324252627282930313233343536373839404142;
  
  struct DELTA_AGG_Inventory_entry {
    long locn; long dateid; DOUBLE_TYPE ksn; long Deg_inventoryunits; DOUBLE_TYPE __av;  DELTA_AGG_Inventory_entry* nxt; DELTA_AGG_Inventory_entry* prv;
    explicit DELTA_AGG_Inventory_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; dateid = 0L; ksn = 0.0; Deg_inventoryunits = 0L; __av = 0.0; */ }
    explicit DELTA_AGG_Inventory_entry(const long c0, const long c1, const DOUBLE_TYPE c2, const long c3, const DOUBLE_TYPE c4) { locn = c0; dateid = c1; ksn = c2; Deg_inventoryunits = c3; __av = c4; }
    DELTA_AGG_Inventory_entry(const DELTA_AGG_Inventory_entry& other) : locn( other.locn ), dateid( other.dateid ), ksn( other.ksn ), Deg_inventoryunits( other.Deg_inventoryunits ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DELTA_AGG_Inventory_entry& modify(const long c0, const long c1, const DOUBLE_TYPE c2, const long c3) { locn = c0; dateid = c1; ksn = c2; Deg_inventoryunits = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, Deg_inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_AGG_Inventory_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_AGG_Inventory_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      hash_combine(h, e.Deg_inventoryunits);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_AGG_Inventory_entry& x, const DELTA_AGG_Inventory_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.Deg_inventoryunits == y.Deg_inventoryunits;
    }
  };
  
  typedef MultiHashMap<DELTA_AGG_Inventory_entry, DOUBLE_TYPE, 
    HashIndex<DELTA_AGG_Inventory_entry, DOUBLE_TYPE, DELTA_AGG_Inventory_mapkey0123_idxfn, true>
  > DELTA_AGG_Inventory_map;
  typedef HashIndex<DELTA_AGG_Inventory_entry, DOUBLE_TYPE, DELTA_AGG_Inventory_mapkey0123_idxfn, true> HashIndex_DELTA_AGG_Inventory_map_0123;
  
  struct DELTA_AGG_InIt_entry {
    long locn; long dateid; long Deg_ksn; long Deg_inventoryunits; long Deg_subcategory; long Deg_category; long Deg_categoryCluster; long Deg_prize; DOUBLE_TYPE __av;  DELTA_AGG_InIt_entry* nxt; DELTA_AGG_InIt_entry* prv;
    explicit DELTA_AGG_InIt_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; dateid = 0L; Deg_ksn = 0L; Deg_inventoryunits = 0L; Deg_subcategory = 0L; Deg_category = 0L; Deg_categoryCluster = 0L; Deg_prize = 0L; __av = 0.0; */ }
    explicit DELTA_AGG_InIt_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const DOUBLE_TYPE c8) { locn = c0; dateid = c1; Deg_ksn = c2; Deg_inventoryunits = c3; Deg_subcategory = c4; Deg_category = c5; Deg_categoryCluster = c6; Deg_prize = c7; __av = c8; }
    DELTA_AGG_InIt_entry(const DELTA_AGG_InIt_entry& other) : locn( other.locn ), dateid( other.dateid ), Deg_ksn( other.Deg_ksn ), Deg_inventoryunits( other.Deg_inventoryunits ), Deg_subcategory( other.Deg_subcategory ), Deg_category( other.Deg_category ), Deg_categoryCluster( other.Deg_categoryCluster ), Deg_prize( other.Deg_prize ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DELTA_AGG_InIt_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7) { locn = c0; dateid = c1; Deg_ksn = c2; Deg_inventoryunits = c3; Deg_subcategory = c4; Deg_category = c5; Deg_categoryCluster = c6; Deg_prize = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_categoryCluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_AGG_InIt_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_AGG_InIt_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.Deg_ksn);
      hash_combine(h, e.Deg_inventoryunits);
      hash_combine(h, e.Deg_subcategory);
      hash_combine(h, e.Deg_category);
      hash_combine(h, e.Deg_categoryCluster);
      hash_combine(h, e.Deg_prize);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_AGG_InIt_entry& x, const DELTA_AGG_InIt_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.Deg_ksn == y.Deg_ksn && x.Deg_inventoryunits == y.Deg_inventoryunits && x.Deg_subcategory == y.Deg_subcategory && x.Deg_category == y.Deg_category && x.Deg_categoryCluster == y.Deg_categoryCluster && x.Deg_prize == y.Deg_prize;
    }
  };
  
  typedef MultiHashMap<DELTA_AGG_InIt_entry, DOUBLE_TYPE, 
    HashIndex<DELTA_AGG_InIt_entry, DOUBLE_TYPE, DELTA_AGG_InIt_mapkey01234567_idxfn, true>
  > DELTA_AGG_InIt_map;
  typedef HashIndex<DELTA_AGG_InIt_entry, DOUBLE_TYPE, DELTA_AGG_InIt_mapkey01234567_idxfn, true> HashIndex_DELTA_AGG_InIt_map_01234567;
  
  struct DELTA_AGG_InItW_entry {
    long locn; long Deg_dateid; long Deg_ksn; long Deg_inventoryunits; long Deg_subcategory; long Deg_category; long Deg_categoryCluster; long Deg_prize; long Deg_rain; long Deg_snow; long Deg_maxtemp; long Deg_mintemp; long Deg_meanwind; long Deg_thunder; DOUBLE_TYPE __av;  DELTA_AGG_InItW_entry* nxt; DELTA_AGG_InItW_entry* prv;
    explicit DELTA_AGG_InItW_entry() : nxt(nullptr), prv(nullptr) { /*locn = 0L; Deg_dateid = 0L; Deg_ksn = 0L; Deg_inventoryunits = 0L; Deg_subcategory = 0L; Deg_category = 0L; Deg_categoryCluster = 0L; Deg_prize = 0L; Deg_rain = 0L; Deg_snow = 0L; Deg_maxtemp = 0L; Deg_mintemp = 0L; Deg_meanwind = 0L; Deg_thunder = 0L; __av = 0.0; */ }
    explicit DELTA_AGG_InItW_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const DOUBLE_TYPE c14) { locn = c0; Deg_dateid = c1; Deg_ksn = c2; Deg_inventoryunits = c3; Deg_subcategory = c4; Deg_category = c5; Deg_categoryCluster = c6; Deg_prize = c7; Deg_rain = c8; Deg_snow = c9; Deg_maxtemp = c10; Deg_mintemp = c11; Deg_meanwind = c12; Deg_thunder = c13; __av = c14; }
    DELTA_AGG_InItW_entry(const DELTA_AGG_InItW_entry& other) : locn( other.locn ), Deg_dateid( other.Deg_dateid ), Deg_ksn( other.Deg_ksn ), Deg_inventoryunits( other.Deg_inventoryunits ), Deg_subcategory( other.Deg_subcategory ), Deg_category( other.Deg_category ), Deg_categoryCluster( other.Deg_categoryCluster ), Deg_prize( other.Deg_prize ), Deg_rain( other.Deg_rain ), Deg_snow( other.Deg_snow ), Deg_maxtemp( other.Deg_maxtemp ), Deg_mintemp( other.Deg_mintemp ), Deg_meanwind( other.Deg_meanwind ), Deg_thunder( other.Deg_thunder ), __av( other.__av ), nxt( nullptr ), prv( nullptr ) {}
    FORCE_INLINE DELTA_AGG_InItW_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13) { locn = c0; Deg_dateid = c1; Deg_ksn = c2; Deg_inventoryunits = c3; Deg_subcategory = c4; Deg_category = c5; Deg_categoryCluster = c6; Deg_prize = c7; Deg_rain = c8; Deg_snow = c9; Deg_maxtemp = c10; Deg_mintemp = c11; Deg_meanwind = c12; Deg_thunder = c13;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_categoryCluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_snow);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_maxtemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_mintemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_meanwind);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, Deg_thunder);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_AGG_InItW_mapkey012345678910111213_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_AGG_InItW_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.Deg_dateid);
      hash_combine(h, e.Deg_ksn);
      hash_combine(h, e.Deg_inventoryunits);
      hash_combine(h, e.Deg_subcategory);
      hash_combine(h, e.Deg_category);
      hash_combine(h, e.Deg_categoryCluster);
      hash_combine(h, e.Deg_prize);
      hash_combine(h, e.Deg_rain);
      hash_combine(h, e.Deg_snow);
      hash_combine(h, e.Deg_maxtemp);
      hash_combine(h, e.Deg_mintemp);
      hash_combine(h, e.Deg_meanwind);
      hash_combine(h, e.Deg_thunder);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_AGG_InItW_entry& x, const DELTA_AGG_InItW_entry& y) {
      return x.locn == y.locn && x.Deg_dateid == y.Deg_dateid && x.Deg_ksn == y.Deg_ksn && x.Deg_inventoryunits == y.Deg_inventoryunits && x.Deg_subcategory == y.Deg_subcategory && x.Deg_category == y.Deg_category && x.Deg_categoryCluster == y.Deg_categoryCluster && x.Deg_prize == y.Deg_prize && x.Deg_rain == y.Deg_rain && x.Deg_snow == y.Deg_snow && x.Deg_maxtemp == y.Deg_maxtemp && x.Deg_mintemp == y.Deg_mintemp && x.Deg_meanwind == y.Deg_meanwind && x.Deg_thunder == y.Deg_thunder;
    }
  };
  
  typedef MultiHashMap<DELTA_AGG_InItW_entry, DOUBLE_TYPE, 
    HashIndex<DELTA_AGG_InItW_entry, DOUBLE_TYPE, DELTA_AGG_InItW_mapkey012345678910111213_idxfn, true>
  > DELTA_AGG_InItW_map;
  typedef HashIndex<DELTA_AGG_InItW_entry, DOUBLE_TYPE, DELTA_AGG_InItW_mapkey012345678910111213_idxfn, true> HashIndex_DELTA_AGG_InItW_map_012345678910111213;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0)  { gettimeofday(&t0, NULL); }
  
    /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const AGG_map& _AGG = get_AGG();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(AGG), _AGG, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const AGG_map& get_AGG() const {
      return AGG;
    }
  
  protected:
    /* Data structures used for storing / computing top level queries */
    AGG_map AGG;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_LOCATION(const long locn, const long zip, const DOUBLE_TYPE rgn_cd, const DOUBLE_TYPE clim_zn_nbr, const DOUBLE_TYPE tot_area_sq_ft, const DOUBLE_TYPE sell_area_sq_ft, const DOUBLE_TYPE avghhi, const DOUBLE_TYPE supertargetdistance, const DOUBLE_TYPE supertargetdrivetime, const DOUBLE_TYPE targetdistance, const DOUBLE_TYPE targetdrivetime, const DOUBLE_TYPE walmartdistance, const DOUBLE_TYPE walmartdrivetime, const DOUBLE_TYPE walmartsupercenterdistance, const DOUBLE_TYPE walmartsupercenterdrivetime) {
      LOCATION_entry e(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime, 1L);
      LOCATION.addOrDelOnZero(e,1L);
    }
    
    void on_insert_CENSUS(const long zip, const long population, const long white, const long asian, const long pacific, const long blackafrican, const DOUBLE_TYPE medianage, const long occupiedhouseunits, const long houseunits, const long families, const long households, const long husbwife, const long males, const long females, const long householdschildren, const long hispanic) {
      CENSUS_entry e(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic, 1L);
      CENSUS.addOrDelOnZero(e,1L);
    }
    
    void on_insert_ITEM(const DOUBLE_TYPE ksn, const long subcategory, const long category, const long categorycluster, const DOUBLE_TYPE prize) {
      ITEM_entry e(ksn, subcategory, category, categorycluster, prize, 1L);
      ITEM.addOrDelOnZero(e,1L);
    }
    
    void on_insert_WEATHER(const long locn, const long dateid, const long rain, const long snow, const long maxtemp, const long mintemp, const DOUBLE_TYPE meanwind, const long thunder) {
      WEATHER_entry e(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder, 1L);
      WEATHER.addOrDelOnZero(e,1L);
    }
    
    void on_insert_DEGREE15(const long deg1, const long deg2, const long deg3, const long deg4, const long deg5, const long deg6, const long deg7, const long deg8, const long deg9, const long deg10, const long deg11, const long deg12, const long deg13, const long deg14, const long deg15) {
      DEGREE15_entry e(deg1, deg2, deg3, deg4, deg5, deg6, deg7, deg8, deg9, deg10, deg11, deg12, deg13, deg14, deg15, 1L);
      DEGREE15.addOrDelOnZero(e,1L);
    }
    
    void on_insert_DEGREE13(const long deg1, const long deg2, const long deg3, const long deg4, const long deg5, const long deg6, const long deg7, const long deg8, const long deg9, const long deg10, const long deg11, const long deg12, const long deg13) {
      DEGREE13_entry e(deg1, deg2, deg3, deg4, deg5, deg6, deg7, deg8, deg9, deg10, deg11, deg12, deg13, 1L);
      DEGREE13.addOrDelOnZero(e,1L);
    }
    
    void on_insert_DEGREE6(const long deg1, const long deg2, const long deg3, const long deg4, const long deg5, const long deg6) {
      DEGREE6_entry e(deg1, deg2, deg3, deg4, deg5, deg6, 1L);
      DEGREE6.addOrDelOnZero(e,1L);
    }
    
    void on_insert_DEGREE4(const long deg1, const long deg2, const long deg3, const long deg4) {
      DEGREE4_entry e(deg1, deg2, deg3, deg4, 1L);
      DEGREE4.addOrDelOnZero(e,1L);
    }
    
    void on_insert_DEGREE1(const long deg) {
      DEGREE1_entry e(deg, 1L);
      DEGREE1.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    template<typename T>
    void on_batch_update_INVENTORY(const typename std::vector<T>::iterator &begin, const typename std::vector<T>::iterator &end) {
      tN += std::distance(begin, end);
      DELTA_AGG_Inventory.clear();
      { //foreach
        for (typename std::vector<T>::iterator e1 = begin; e1 != end; e1++) {
          long locn = e1->locn;
          long dateid = e1->dateid;
          DOUBLE_TYPE ksn = e1->ksn;
          DOUBLE_TYPE inventoryunits = e1->inventoryunits;
          long v1 = e1->__av;
          { //foreach
            DEGREE1_entry* e2 = DEGREE1.head;
            while (e2) {
              long deg_inventoryunits = e2->Deg;
              long v2 = e2->__av;
              DELTA_AGG_Inventory.addOrDelOnZero(se1.modify(locn, dateid, ksn, deg_inventoryunits), (v1 * (v2 * ((/*if */(deg_inventoryunits == 0L) ? 1L : 0L) + ((/*if */(deg_inventoryunits == 1L) ? inventoryunits : 0.0) + (/*if */(deg_inventoryunits == 2L) ? (inventoryunits * inventoryunits) : 0.0))))));
              e2 = e2->nxt;
            }
          }
        }
      }
      DELTA_AGG_InIt.clear();
      { //foreach
        DELTA_AGG_Inventory_entry* e3 = DELTA_AGG_Inventory.head;
        while (e3) {
          long locn = e3->locn;
          long dateid = e3->dateid;
          DOUBLE_TYPE ksn = e3->ksn;
          long deg_inventoryunits = e3->Deg_inventoryunits;
          DOUBLE_TYPE v3 = e3->__av;
          { //slice
            const HASH_RES_t h1 = AGG_Item_mapkey0_idxfn::hash(se3.modify0(ksn));
            const HashIndex_AGG_Item_map_0* i4 = static_cast<HashIndex_AGG_Item_map_0*>(AGG_Item.index[1]);
            HashIndex_AGG_Item_map_0::IdxNode* n4 = &(i4->buckets_[h1 % i4->size_]);
            AGG_Item_entry* e4;
            do if ((e4 = n4->obj) && h1 == n4->hash && AGG_Item_mapkey0_idxfn::equals(se3, *e4)) {
              long deg_subcategory = e4->Deg_subcategory;
              long deg_category = e4->Deg_category;
              long deg_categorycluster = e4->Deg_categoryCluster;
              long deg_prize = e4->Deg_prize;
              DOUBLE_TYPE v4 = e4->__av;
              { //foreach
                DEGREE1_entry* e5 = DEGREE1.head;
                while (e5) {
                  long deg_ksn = e5->Deg;
                  long v5 = e5->__av;
                  (/*if */(2L >= (deg_ksn + (deg_inventoryunits + (deg_subcategory + (deg_category + (deg_categorycluster + deg_prize)))))) ? DELTA_AGG_InIt.addOrDelOnZero(se2.modify(locn, dateid, deg_ksn, deg_inventoryunits, deg_subcategory, deg_category, deg_categorycluster, deg_prize), (v3 * (v4 * (v5 * ((/*if */(deg_ksn == 0L) ? 1L : 0L) + ((/*if */(deg_ksn == 1L) ? ksn : 0.0) + (/*if */(deg_ksn == 2L) ? (ksn * ksn) : 0.0))))))) : (void)0);
                  e5 = e5->nxt;
                }
              }
            } while ((n4 = n4->nxt));
          }
          e3 = e3->nxt;
        }
      }
      DELTA_AGG_InItW.clear();
      { //foreach
        DELTA_AGG_InIt_entry* e6 = DELTA_AGG_InIt.head;
        while (e6) {
          long locn = e6->locn;
          long dateid = e6->dateid;
          long deg_ksn = e6->Deg_ksn;
          long deg_inventoryunits = e6->Deg_inventoryunits;
          long deg_subcategory = e6->Deg_subcategory;
          long deg_category = e6->Deg_category;
          long deg_categorycluster = e6->Deg_categoryCluster;
          long deg_prize = e6->Deg_prize;
          DOUBLE_TYPE v6 = e6->__av;
          { //slice
            const HASH_RES_t h2 = AGG_Weather_mapkey01_idxfn::hash(se5.modify01(locn, dateid));
            const HashIndex_AGG_Weather_map_01* i7 = static_cast<HashIndex_AGG_Weather_map_01*>(AGG_Weather.index[1]);
            HashIndex_AGG_Weather_map_01::IdxNode* n7 = &(i7->buckets_[h2 % i7->size_]);
            AGG_Weather_entry* e7;
            do if ((e7 = n7->obj) && h2 == n7->hash && AGG_Weather_mapkey01_idxfn::equals(se5, *e7)) {
              long deg_rain = e7->Deg_rain;
              long deg_snow = e7->Deg_snow;
              long deg_maxtemp = e7->Deg_maxtemp;
              long deg_mintemp = e7->Deg_mintemp;
              long deg_meanwind = e7->Deg_meanwind;
              long deg_thunder = e7->Deg_thunder;
              DOUBLE_TYPE v7 = e7->__av;
              { //foreach
                DEGREE1_entry* e8 = DEGREE1.head;
                while (e8) {
                  long deg_dateid = e8->Deg;
                  long v8 = e8->__av;
                  (/*if */(2L >= (deg_dateid + (deg_ksn + (deg_inventoryunits + (deg_subcategory + (deg_category + (deg_categorycluster + (deg_prize + (deg_rain + (deg_snow + (deg_maxtemp + (deg_mintemp + (deg_meanwind + deg_thunder))))))))))))) ? DELTA_AGG_InItW.addOrDelOnZero(se4.modify(locn, deg_dateid, deg_ksn, deg_inventoryunits, deg_subcategory, deg_category, deg_categorycluster, deg_prize, deg_rain, deg_snow, deg_maxtemp, deg_mintemp, deg_meanwind, deg_thunder), (v6 * (v7 * (v8 * ((/*if */(deg_dateid == 0L) ? 1L : 0L) + ((/*if */(deg_dateid == 1L) ? dateid : 0L) + (/*if */(deg_dateid == 2L) ? (dateid * dateid) : 0L))))))) : (void)0);
                  e8 = e8->nxt;
                }
              }
            } while ((n7 = n7->nxt));
          }
          e6 = e6->nxt;
        }
      }
      { //foreach
        DELTA_AGG_InItW_entry* e9 = DELTA_AGG_InItW.head;
        while (e9) {
          long locn = e9->locn;
          long deg_dateid = e9->Deg_dateid;
          long deg_ksn = e9->Deg_ksn;
          long deg_inventoryunits = e9->Deg_inventoryunits;
          long deg_subcategory = e9->Deg_subcategory;
          long deg_category = e9->Deg_category;
          long deg_categorycluster = e9->Deg_categoryCluster;
          long deg_prize = e9->Deg_prize;
          long deg_rain = e9->Deg_rain;
          long deg_snow = e9->Deg_snow;
          long deg_maxtemp = e9->Deg_maxtemp;
          long deg_mintemp = e9->Deg_mintemp;
          long deg_meanwind = e9->Deg_meanwind;
          long deg_thunder = e9->Deg_thunder;
          DOUBLE_TYPE v9 = e9->__av;
          { //slice
            const HASH_RES_t h3 = AGG_LC_mapkey0_idxfn::hash(se7.modify0(locn));
            const HashIndex_AGG_LC_map_0* i10 = static_cast<HashIndex_AGG_LC_map_0*>(AGG_LC.index[1]);
            HashIndex_AGG_LC_map_0::IdxNode* n10 = &(i10->buckets_[h3 % i10->size_]);
            AGG_LC_entry* e10;
            do if ((e10 = n10->obj) && h3 == n10->hash && AGG_LC_mapkey0_idxfn::equals(se7, *e10)) {
              long deg_zip = e10->Deg_zip;
              long deg_rgn_cd = e10->Deg_rgn_cd;
              long deg_clim_zn_nbr = e10->Deg_clim_zn_nbr;
              long deg_tot_area_sq_ft = e10->Deg_tot_area_sq_ft;
              long deg_sell_area_sq_ft = e10->Deg_sell_area_sq_ft;
              long deg_avghhi = e10->Deg_avghhi;
              long deg_supertargetdistance = e10->Deg_supertargetdistance;
              long deg_supertargetdrivetime = e10->Deg_supertargetdrivetime;
              long deg_targetdistance = e10->Deg_targetdistance;
              long deg_targetdrivetime = e10->Deg_targetdrivetime;
              long deg_walmartdistance = e10->Deg_walmartdistance;
              long deg_walmartdrivetime = e10->Deg_walmartdrivetime;
              long deg_walmartsupercenterdistance = e10->Deg_walmartsupercenterdistance;
              long deg_walmartsupercenterdrivetime = e10->Deg_walmartsupercenterdrivetime;
              long deg_population = e10->Deg_population;
              long deg_white = e10->Deg_white;
              long deg_asian = e10->Deg_asian;
              long deg_pacific = e10->Deg_pacific;
              long deg_blackafrican = e10->Deg_blackafrican;
              long deg_medianage = e10->Deg_medianage;
              long deg_occupiedhouseunits = e10->Deg_occupiedhouseunits;
              long deg_houseunits = e10->Deg_houseunits;
              long deg_families = e10->Deg_families;
              long deg_households = e10->Deg_households;
              long deg_husbwife = e10->Deg_husbwife;
              long deg_males = e10->Deg_males;
              long deg_females = e10->Deg_females;
              long deg_householdschildren = e10->Deg_householdschildren;
              long deg_hispanic = e10->Deg_hispanic;
              DOUBLE_TYPE v10 = e10->__av;
              { //foreach
                DEGREE1_entry* e11 = DEGREE1.head;
                while (e11) {
                  long deg_locn = e11->Deg;
                  long v11 = e11->__av;
                  (/*if */((deg_locn + (deg_dateid + (deg_ksn + (deg_inventoryunits + (deg_subcategory + (deg_category + (deg_categorycluster + (deg_prize + (deg_rain + (deg_snow + (deg_maxtemp + (deg_mintemp + (deg_meanwind + (deg_thunder + (deg_zip + (deg_rgn_cd + (deg_clim_zn_nbr + (deg_tot_area_sq_ft + (deg_sell_area_sq_ft + (deg_avghhi + (deg_supertargetdistance + (deg_supertargetdrivetime + (deg_targetdistance + (deg_targetdrivetime + (deg_walmartdistance + (deg_walmartdrivetime + (deg_walmartsupercenterdistance + (deg_walmartsupercenterdrivetime + (deg_population + (deg_white + (deg_asian + (deg_pacific + (deg_blackafrican + (deg_medianage + (deg_occupiedhouseunits + (deg_houseunits + (deg_families + (deg_households + (deg_husbwife + (deg_males + (deg_females + (deg_householdschildren + deg_hispanic)))))))))))))))))))))))))))))))))))))))))) == 2L) ? AGG.addOrDelOnZero(se6.modify(deg_locn, deg_dateid, deg_ksn, deg_inventoryunits, deg_subcategory, deg_category, deg_categorycluster, deg_prize, deg_rain, deg_snow, deg_maxtemp, deg_mintemp, deg_meanwind, deg_thunder, deg_zip, deg_rgn_cd, deg_clim_zn_nbr, deg_tot_area_sq_ft, deg_sell_area_sq_ft, deg_avghhi, deg_supertargetdistance, deg_supertargetdrivetime, deg_targetdistance, deg_targetdrivetime, deg_walmartdistance, deg_walmartdrivetime, deg_walmartsupercenterdistance, deg_walmartsupercenterdrivetime, deg_population, deg_white, deg_asian, deg_pacific, deg_blackafrican, deg_medianage, deg_occupiedhouseunits, deg_houseunits, deg_families, deg_households, deg_husbwife, deg_males, deg_females, deg_householdschildren, deg_hispanic), (v9 * (v10 * (v11 * ((/*if */(deg_locn == 0L) ? 1L : 0L) + ((/*if */(deg_locn == 1L) ? locn : 0L) + (/*if */(deg_locn == 2L) ? (locn * locn) : 0L))))))) : (void)0);
                  e11 = e11->nxt;
                }
              }
            } while ((n10 = n10->nxt));
          }
          e9 = e9->nxt;
        }
      }
    }
    
    void on_system_ready_event() {
      
      AGG_Location.clear();
      { //foreach
        LOCATION_entry* e12 = LOCATION.head;
        while (e12) {
          long locn = e12->locn;
          long zip = e12->zip;
          DOUBLE_TYPE rgn_cd = e12->rgn_cd;
          DOUBLE_TYPE clim_zn_nbr = e12->clim_zn_nbr;
          DOUBLE_TYPE tot_area_sq_ft = e12->tot_area_sq_ft;
          DOUBLE_TYPE sell_area_sq_ft = e12->sell_area_sq_ft;
          DOUBLE_TYPE avghhi = e12->avghhi;
          DOUBLE_TYPE supertargetdistance = e12->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e12->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e12->targetdistance;
          DOUBLE_TYPE targetdrivetime = e12->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e12->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e12->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e12->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e12->walmartsupercenterdrivetime;
          long v12 = e12->__av;
          { //foreach
            DEGREE13_entry* e13 = DEGREE13.head;
            while (e13) {
              long deg_rgn_cd = e13->Deg1;
              long deg_clim_zn_nbr = e13->Deg2;
              long deg_tot_area_sq_ft = e13->Deg3;
              long deg_sell_area_sq_ft = e13->Deg4;
              long deg_avghhi = e13->Deg5;
              long deg_supertargetdistance = e13->Deg6;
              long deg_supertargetdrivetime = e13->Deg7;
              long deg_targetdistance = e13->Deg8;
              long deg_targetdrivetime = e13->Deg9;
              long deg_walmartdistance = e13->Deg10;
              long deg_walmartdrivetime = e13->Deg11;
              long deg_walmartsupercenterdistance = e13->Deg12;
              long deg_walmartsupercenterdrivetime = e13->Deg13;
              long v13 = e13->__av;
              AGG_Location.addOrDelOnZero(se8.modify(locn, zip, deg_rgn_cd, deg_clim_zn_nbr, deg_tot_area_sq_ft, deg_sell_area_sq_ft, deg_avghhi, deg_supertargetdistance, deg_supertargetdrivetime, deg_targetdistance, deg_targetdrivetime, deg_walmartdistance, deg_walmartdrivetime, deg_walmartsupercenterdistance, deg_walmartsupercenterdrivetime), (v12 * (v13 * (((/*if */(deg_rgn_cd == 0L) ? 1L : 0L) + ((/*if */(deg_rgn_cd == 1L) ? rgn_cd : 0.0) + (/*if */(deg_rgn_cd == 2L) ? (rgn_cd * rgn_cd) : 0.0))) * (((/*if */(deg_clim_zn_nbr == 0L) ? 1L : 0L) + ((/*if */(deg_clim_zn_nbr == 1L) ? clim_zn_nbr : 0.0) + (/*if */(deg_clim_zn_nbr == 2L) ? (clim_zn_nbr * clim_zn_nbr) : 0.0))) * (((/*if */(deg_tot_area_sq_ft == 0L) ? 1L : 0L) + ((/*if */(deg_tot_area_sq_ft == 1L) ? tot_area_sq_ft : 0.0) + (/*if */(deg_tot_area_sq_ft == 2L) ? (tot_area_sq_ft * tot_area_sq_ft) : 0.0))) * (((/*if */(deg_sell_area_sq_ft == 0L) ? 1L : 0L) + ((/*if */(deg_sell_area_sq_ft == 1L) ? sell_area_sq_ft : 0.0) + (/*if */(deg_sell_area_sq_ft == 2L) ? (sell_area_sq_ft * sell_area_sq_ft) : 0.0))) * (((/*if */(deg_avghhi == 0L) ? 1L : 0L) + ((/*if */(deg_avghhi == 1L) ? avghhi : 0.0) + (/*if */(deg_avghhi == 2L) ? (avghhi * avghhi) : 0.0))) * (((/*if */(deg_supertargetdistance == 0L) ? 1L : 0L) + ((/*if */(deg_supertargetdistance == 1L) ? supertargetdistance : 0.0) + (/*if */(deg_supertargetdistance == 2L) ? (supertargetdistance * supertargetdistance) : 0.0))) * (((/*if */(deg_supertargetdrivetime == 0L) ? 1L : 0L) + ((/*if */(deg_supertargetdrivetime == 1L) ? supertargetdrivetime : 0.0) + (/*if */(deg_supertargetdrivetime == 2L) ? (supertargetdrivetime * supertargetdrivetime) : 0.0))) * (((/*if */(deg_targetdistance == 0L) ? 1L : 0L) + ((/*if */(deg_targetdistance == 1L) ? targetdistance : 0.0) + (/*if */(deg_targetdistance == 2L) ? (targetdistance * targetdistance) : 0.0))) * (((/*if */(deg_targetdrivetime == 0L) ? 1L : 0L) + ((/*if */(deg_targetdrivetime == 1L) ? targetdrivetime : 0.0) + (/*if */(deg_targetdrivetime == 2L) ? (targetdrivetime * targetdrivetime) : 0.0))) * (((/*if */(deg_walmartdistance == 0L) ? 1L : 0L) + ((/*if */(deg_walmartdistance == 1L) ? walmartdistance : 0.0) + (/*if */(deg_walmartdistance == 2L) ? (walmartdistance * walmartdistance) : 0.0))) * (((/*if */(deg_walmartdrivetime == 0L) ? 1L : 0L) + ((/*if */(deg_walmartdrivetime == 1L) ? walmartdrivetime : 0.0) + (/*if */(deg_walmartdrivetime == 2L) ? (walmartdrivetime * walmartdrivetime) : 0.0))) * (((/*if */(deg_walmartsupercenterdistance == 0L) ? 1L : 0L) + ((/*if */(deg_walmartsupercenterdistance == 1L) ? walmartsupercenterdistance : 0.0) + (/*if */(deg_walmartsupercenterdistance == 2L) ? (walmartsupercenterdistance * walmartsupercenterdistance) : 0.0))) * ((/*if */(deg_walmartsupercenterdrivetime == 0L) ? 1L : 0L) + ((/*if */(deg_walmartsupercenterdrivetime == 1L) ? walmartsupercenterdrivetime : 0.0) + (/*if */(deg_walmartsupercenterdrivetime == 2L) ? (walmartsupercenterdrivetime * walmartsupercenterdrivetime) : 0.0))))))))))))))))));
              e13 = e13->nxt;
            }
          }
          e12 = e12->nxt;
        }
      }
      AGG_Census.clear();
      { //foreach
        CENSUS_entry* e14 = CENSUS.head;
        while (e14) {
          long zip = e14->zip;
          long population = e14->population;
          long white = e14->white;
          long asian = e14->asian;
          long pacific = e14->pacific;
          long blackafrican = e14->blackafrican;
          DOUBLE_TYPE medianage = e14->medianage;
          long occupiedhouseunits = e14->occupiedhouseunits;
          long houseunits = e14->houseunits;
          long families = e14->families;
          long households = e14->households;
          long husbwife = e14->husbwife;
          long males = e14->males;
          long females = e14->females;
          long householdschildren = e14->householdschildren;
          long hispanic = e14->hispanic;
          long v14 = e14->__av;
          { //foreach
            DEGREE15_entry* e15 = DEGREE15.head;
            while (e15) {
              long deg_population = e15->Deg1;
              long deg_white = e15->Deg2;
              long deg_asian = e15->Deg3;
              long deg_pacific = e15->Deg4;
              long deg_blackafrican = e15->Deg5;
              long deg_medianage = e15->Deg6;
              long deg_occupiedhouseunits = e15->Deg7;
              long deg_houseunits = e15->Deg8;
              long deg_families = e15->Deg9;
              long deg_households = e15->Deg10;
              long deg_husbwife = e15->Deg11;
              long deg_males = e15->Deg12;
              long deg_females = e15->Deg13;
              long deg_householdschildren = e15->Deg14;
              long deg_hispanic = e15->Deg15;
              long v15 = e15->__av;
              AGG_Census.addOrDelOnZero(se9.modify(zip, deg_population, deg_white, deg_asian, deg_pacific, deg_blackafrican, deg_medianage, deg_occupiedhouseunits, deg_houseunits, deg_families, deg_households, deg_husbwife, deg_males, deg_females, deg_householdschildren, deg_hispanic), (v14 * (v15 * (((/*if */(deg_population == 0L) ? 1L : 0L) + ((/*if */(deg_population == 1L) ? population : 0L) + (/*if */(deg_population == 2L) ? (population * population) : 0L))) * (((/*if */(deg_white == 0L) ? 1L : 0L) + ((/*if */(deg_white == 1L) ? white : 0L) + (/*if */(deg_white == 2L) ? (white * white) : 0L))) * (((/*if */(deg_asian == 0L) ? 1L : 0L) + ((/*if */(deg_asian == 1L) ? asian : 0L) + (/*if */(deg_asian == 2L) ? (asian * asian) : 0L))) * (((/*if */(deg_pacific == 0L) ? 1L : 0L) + ((/*if */(deg_pacific == 1L) ? pacific : 0L) + (/*if */(deg_pacific == 2L) ? (pacific * pacific) : 0L))) * (((/*if */(deg_blackafrican == 0L) ? 1L : 0L) + ((/*if */(deg_blackafrican == 1L) ? blackafrican : 0L) + (/*if */(deg_blackafrican == 2L) ? (blackafrican * blackafrican) : 0L))) * (((/*if */(deg_medianage == 0L) ? 1L : 0L) + ((/*if */(deg_medianage == 1L) ? medianage : 0.0) + (/*if */(deg_medianage == 2L) ? (medianage * medianage) : 0.0))) * (((/*if */(deg_occupiedhouseunits == 0L) ? 1L : 0L) + ((/*if */(deg_occupiedhouseunits == 1L) ? occupiedhouseunits : 0L) + (/*if */(deg_occupiedhouseunits == 2L) ? (occupiedhouseunits * occupiedhouseunits) : 0L))) * (((/*if */(deg_houseunits == 0L) ? 1L : 0L) + ((/*if */(deg_houseunits == 1L) ? houseunits : 0L) + (/*if */(deg_houseunits == 2L) ? (houseunits * houseunits) : 0L))) * (((/*if */(deg_families == 0L) ? 1L : 0L) + ((/*if */(deg_families == 1L) ? families : 0L) + (/*if */(deg_families == 2L) ? (families * families) : 0L))) * (((/*if */(deg_households == 0L) ? 1L : 0L) + ((/*if */(deg_households == 1L) ? households : 0L) + (/*if */(deg_households == 2L) ? (households * households) : 0L))) * (((/*if */(deg_husbwife == 0L) ? 1L : 0L) + ((/*if */(deg_husbwife == 1L) ? husbwife : 0L) + (/*if */(deg_husbwife == 2L) ? (husbwife * husbwife) : 0L))) * (((/*if */(deg_males == 0L) ? 1L : 0L) + ((/*if */(deg_males == 1L) ? males : 0L) + (/*if */(deg_males == 2L) ? (males * males) : 0L))) * (((/*if */(deg_females == 0L) ? 1L : 0L) + ((/*if */(deg_females == 1L) ? females : 0L) + (/*if */(deg_females == 2L) ? (females * females) : 0L))) * (((/*if */(deg_householdschildren == 0L) ? 1L : 0L) + ((/*if */(deg_householdschildren == 1L) ? householdschildren : 0L) + (/*if */(deg_householdschildren == 2L) ? (householdschildren * householdschildren) : 0L))) * ((/*if */(deg_hispanic == 0L) ? 1L : 0L) + ((/*if */(deg_hispanic == 1L) ? hispanic : 0L) + (/*if */(deg_hispanic == 2L) ? (hispanic * hispanic) : 0L))))))))))))))))))));
              e15 = e15->nxt;
            }
          }
          e14 = e14->nxt;
        }
      }
      AGG_Item.clear();
      { //foreach
        ITEM_entry* e16 = ITEM.head;
        while (e16) {
          DOUBLE_TYPE ksn = e16->ksn;
          long subcategory = e16->subcategory;
          long category = e16->category;
          long categorycluster = e16->categoryCluster;
          DOUBLE_TYPE prize = e16->prize;
          long v16 = e16->__av;
          { //foreach
            DEGREE4_entry* e17 = DEGREE4.head;
            while (e17) {
              long deg_subcategory = e17->Deg1;
              long deg_category = e17->Deg2;
              long deg_categorycluster = e17->Deg3;
              long deg_prize = e17->Deg4;
              long v17 = e17->__av;
              AGG_Item.addOrDelOnZero(se10.modify(ksn, deg_subcategory, deg_category, deg_categorycluster, deg_prize), (v16 * (v17 * (((/*if */(deg_subcategory == 0L) ? 1L : 0L) + ((/*if */(deg_subcategory == 1L) ? subcategory : 0L) + (/*if */(deg_subcategory == 2L) ? (subcategory * subcategory) : 0L))) * (((/*if */(deg_category == 0L) ? 1L : 0L) + ((/*if */(deg_category == 1L) ? category : 0L) + (/*if */(deg_category == 2L) ? (category * category) : 0L))) * (((/*if */(deg_categorycluster == 0L) ? 1L : 0L) + ((/*if */(deg_categorycluster == 1L) ? categorycluster : 0L) + (/*if */(deg_categorycluster == 2L) ? (categorycluster * categorycluster) : 0L))) * ((/*if */(deg_prize == 0L) ? 1L : 0L) + ((/*if */(deg_prize == 1L) ? prize : 0.0) + (/*if */(deg_prize == 2L) ? (prize * prize) : 0.0)))))))));
              e17 = e17->nxt;
            }
          }
          e16 = e16->nxt;
        }
      }
      AGG_Weather.clear();
      { //foreach
        WEATHER_entry* e18 = WEATHER.head;
        while (e18) {
          long locn = e18->locn;
          long dateid = e18->dateid;
          long rain = e18->rain;
          long snow = e18->snow;
          long maxtemp = e18->maxtemp;
          long mintemp = e18->mintemp;
          DOUBLE_TYPE meanwind = e18->meanwind;
          long thunder = e18->thunder;
          long v18 = e18->__av;
          { //foreach
            DEGREE6_entry* e19 = DEGREE6.head;
            while (e19) {
              long deg_rain = e19->Deg1;
              long deg_snow = e19->Deg2;
              long deg_maxtemp = e19->Deg3;
              long deg_mintemp = e19->Deg4;
              long deg_meanwind = e19->Deg5;
              long deg_thunder = e19->Deg6;
              long v19 = e19->__av;
              AGG_Weather.addOrDelOnZero(se11.modify(locn, dateid, deg_rain, deg_snow, deg_maxtemp, deg_mintemp, deg_meanwind, deg_thunder), (v18 * (v19 * (((/*if */(deg_rain == 0L) ? 1L : 0L) + ((/*if */(deg_rain == 1L) ? rain : 0L) + (/*if */(deg_rain == 2L) ? (rain * rain) : 0L))) * (((/*if */(deg_snow == 0L) ? 1L : 0L) + ((/*if */(deg_snow == 1L) ? snow : 0L) + (/*if */(deg_snow == 2L) ? (snow * snow) : 0L))) * (((/*if */(deg_maxtemp == 0L) ? 1L : 0L) + ((/*if */(deg_maxtemp == 1L) ? maxtemp : 0L) + (/*if */(deg_maxtemp == 2L) ? (maxtemp * maxtemp) : 0L))) * (((/*if */(deg_mintemp == 0L) ? 1L : 0L) + ((/*if */(deg_mintemp == 1L) ? mintemp : 0L) + (/*if */(deg_mintemp == 2L) ? (mintemp * mintemp) : 0L))) * (((/*if */(deg_meanwind == 0L) ? 1L : 0L) + ((/*if */(deg_meanwind == 1L) ? meanwind : 0.0) + (/*if */(deg_meanwind == 2L) ? (meanwind * meanwind) : 0.0))) * ((/*if */(deg_thunder == 0L) ? 1L : 0L) + ((/*if */(deg_thunder == 1L) ? thunder : 0L) + (/*if */(deg_thunder == 2L) ? (thunder * thunder) : 0L)))))))))));
              e19 = e19->nxt;
            }
          }
          e18 = e18->nxt;
        }
      }
      AGG_LC.clear();
      { //foreach
        AGG_Location_entry* e20 = AGG_Location.head;
        while (e20) {
          long locn = e20->locn;
          long zip = e20->zip;
          long deg_rgn_cd = e20->Deg_rgn_cd;
          long deg_clim_zn_nbr = e20->Deg_clim_zn_nbr;
          long deg_tot_area_sq_ft = e20->Deg_tot_area_sq_ft;
          long deg_sell_area_sq_ft = e20->Deg_sell_area_sq_ft;
          long deg_avghhi = e20->Deg_avghhi;
          long deg_supertargetdistance = e20->Deg_supertargetdistance;
          long deg_supertargetdrivetime = e20->Deg_supertargetdrivetime;
          long deg_targetdistance = e20->Deg_targetdistance;
          long deg_targetdrivetime = e20->Deg_targetdrivetime;
          long deg_walmartdistance = e20->Deg_walmartdistance;
          long deg_walmartdrivetime = e20->Deg_walmartdrivetime;
          long deg_walmartsupercenterdistance = e20->Deg_walmartsupercenterdistance;
          long deg_walmartsupercenterdrivetime = e20->Deg_walmartsupercenterdrivetime;
          DOUBLE_TYPE v20 = e20->__av;
          { //slice
            const HASH_RES_t h4 = AGG_Census_mapkey0_idxfn::hash(se13.modify0(zip));
            const HashIndex_AGG_Census_map_0* i21 = static_cast<HashIndex_AGG_Census_map_0*>(AGG_Census.index[1]);
            HashIndex_AGG_Census_map_0::IdxNode* n21 = &(i21->buckets_[h4 % i21->size_]);
            AGG_Census_entry* e21;
            do if ((e21 = n21->obj) && h4 == n21->hash && AGG_Census_mapkey0_idxfn::equals(se13, *e21)) {
              long deg_population = e21->Deg_population;
              long deg_white = e21->Deg_white;
              long deg_asian = e21->Deg_asian;
              long deg_pacific = e21->Deg_pacific;
              long deg_blackafrican = e21->Deg_blackafrican;
              long deg_medianage = e21->Deg_medianage;
              long deg_occupiedhouseunits = e21->Deg_occupiedhouseunits;
              long deg_houseunits = e21->Deg_houseunits;
              long deg_families = e21->Deg_families;
              long deg_households = e21->Deg_households;
              long deg_husbwife = e21->Deg_husbwife;
              long deg_males = e21->Deg_males;
              long deg_females = e21->Deg_females;
              long deg_householdschildren = e21->Deg_householdschildren;
              long deg_hispanic = e21->Deg_hispanic;
              DOUBLE_TYPE v21 = e21->__av;
              { //foreach
                DEGREE1_entry* e22 = DEGREE1.head;
                while (e22) {
                  long deg_zip = e22->Deg;
                  long v22 = e22->__av;
                  (/*if */(2L >= (deg_zip + (deg_rgn_cd + (deg_clim_zn_nbr + (deg_tot_area_sq_ft + (deg_sell_area_sq_ft + (deg_avghhi + (deg_supertargetdistance + (deg_supertargetdrivetime + (deg_targetdistance + (deg_targetdrivetime + (deg_walmartdistance + (deg_walmartdrivetime + (deg_walmartsupercenterdistance + (deg_walmartsupercenterdrivetime + (deg_population + (deg_white + (deg_asian + (deg_pacific + (deg_blackafrican + (deg_medianage + (deg_occupiedhouseunits + (deg_houseunits + (deg_families + (deg_households + (deg_husbwife + (deg_males + (deg_females + (deg_householdschildren + deg_hispanic))))))))))))))))))))))))))))) ? AGG_LC.addOrDelOnZero(se12.modify(locn, deg_zip, deg_rgn_cd, deg_clim_zn_nbr, deg_tot_area_sq_ft, deg_sell_area_sq_ft, deg_avghhi, deg_supertargetdistance, deg_supertargetdrivetime, deg_targetdistance, deg_targetdrivetime, deg_walmartdistance, deg_walmartdrivetime, deg_walmartsupercenterdistance, deg_walmartsupercenterdrivetime, deg_population, deg_white, deg_asian, deg_pacific, deg_blackafrican, deg_medianage, deg_occupiedhouseunits, deg_houseunits, deg_families, deg_households, deg_husbwife, deg_males, deg_females, deg_householdschildren, deg_hispanic), (v20 * (v21 * (v22 * ((/*if */(deg_zip == 0L) ? 1L : 0L) + ((/*if */(deg_zip == 1L) ? zip : 0L) + (/*if */(deg_zip == 2L) ? (zip * zip) : 0L))))))) : (void)0);
                  e22 = e22->nxt;
                }
              }
            } while ((n21 = n21->nxt));
          }
          e20 = e20->nxt;
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    DELTA_AGG_Inventory_entry se1;
    DELTA_AGG_InIt_entry se2;
    AGG_Item_entry se3;
    DELTA_AGG_InItW_entry se4;
    AGG_Weather_entry se5;
    AGG_entry se6;
    AGG_LC_entry se7;
    AGG_Location_entry se8;
    AGG_Census_entry se9;
    AGG_Item_entry se10;
    AGG_Weather_entry se11;
    AGG_LC_entry se12;
    AGG_Census_entry se13;
  
    /* Data structures used for storing materialized views */
    LOCATION_map LOCATION;
    CENSUS_map CENSUS;
    ITEM_map ITEM;
    WEATHER_map WEATHER;
    DEGREE15_map DEGREE15;
    DEGREE13_map DEGREE13;
    DEGREE6_map DEGREE6;
    DEGREE4_map DEGREE4;
    DEGREE1_map DEGREE1;
    AGG_Location_map AGG_Location;
    AGG_Census_map AGG_Census;
    AGG_Item_map AGG_Item;
    AGG_Weather_map AGG_Weather;
    AGG_LC_map AGG_LC;
    DELTA_AGG_Inventory_map DELTA_AGG_Inventory;
    DELTA_AGG_InIt_map DELTA_AGG_InIt;
    DELTA_AGG_InItW_map DELTA_AGG_InItW;
    DELTA_INVENTORY_map DELTA_INVENTORY;
    
    
  
  };
}
        