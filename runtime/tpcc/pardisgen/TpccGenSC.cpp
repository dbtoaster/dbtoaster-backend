#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
using namespace std;
#include "hpds/pstring.hpp"
#include "hpds/pstringops.hpp"
#include "program_base.hpp"

#define USING_GENERIC_ENTRY true

#ifdef NUMWARE
  const int numWare = NUMWARE;
#else
  const int numWare = 2;
#endif
#ifdef NUMPROG
  const size_t numPrograms = NUMPROG;
#else
  const size_t numPrograms = 100;
#endif

const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
const size_t itemTblSize = 100000;
const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
const size_t customerTblSize = districtTblSize * 3000;
const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
const size_t orderLineTblSize = orderTblSize * 12;
const size_t stockTblSize = numWare * itemTblSize;
const size_t historyTblSize = orderTblSize;

     


struct GenericOps_1 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 16;
    for(int c : {1})
      h = h * 41 + HASH(e.map.at(c));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if (e1.isSampleEntry) {
      for (auto it : e1.map) {
        if (e2.map.at(it.first) != it.second)
            return 1;
      }
    } else if (e2.isSampleEntry) {
     for (auto it : e2.map) {
         if (e1.map.at(it.first) != it.second)
             return 1;
      }
    }else {
      for(int c : {1})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};
struct GenericOps_1234 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 16;
    for(int c : {1, 2, 3, 4})
      h = h * 41 + HASH(e.map.at(c));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if (e1.isSampleEntry) {
      for (auto it : e1.map) {
        if (e2.map.at(it.first) != it.second)
            return 1;
      }
    } else if (e2.isSampleEntry) {
     for (auto it : e2.map) {
         if (e1.map.at(it.first) != it.second)
             return 1;
      }
    }else {
      for(int c : {1, 2, 3, 4})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};
struct GenericOps_12 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 16;
    for(int c : {1, 2})
      h = h * 41 + HASH(e.map.at(c));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if (e1.isSampleEntry) {
      for (auto it : e1.map) {
        if (e2.map.at(it.first) != it.second)
            return 1;
      }
    } else if (e2.isSampleEntry) {
     for (auto it : e2.map) {
         if (e1.map.at(it.first) != it.second)
             return 1;
      }
    }else {
      for(int c : {1, 2})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};
struct GenericOps_123 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 16;
    for(int c : {1, 2, 3})
      h = h * 41 + HASH(e.map.at(c));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if (e1.isSampleEntry) {
      for (auto it : e1.map) {
        if (e2.map.at(it.first) != it.second)
            return 1;
      }
    } else if (e2.isSampleEntry) {
     for (auto it : e2.map) {
         if (e1.map.at(it.first) != it.second)
             return 1;
      }
    }else {
      for(int c : {1, 2, 3})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};

typedef ListIndex<GenericEntry, char, GenericOps_123, 0> newOrderTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_123, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblIdx0Type& x455 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps, 0> historyTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblIdx0Type& x460 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_1, 0> warehouseTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_1, 0>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblIdx0Type& x465 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_1, 0> itemTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_1, 0>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblIdx0Type& x468 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_123, 0> orderTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_123, 0>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblIdx0Type& x471 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_12, 0> districtTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_12, 0>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblIdx0Type& x476 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_1234, 0> orderLineTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_1234, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblIdx0Type& x481 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_123, 0> customerTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_123, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblIdx0Type& x484 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_12, 0> stockTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_12, 0>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblIdx0Type& x487 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];




void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    GenericEntry* aggresult;
    MinAggregator<GenericEntry, int> agg(([&](GenericEntry* e) {
      int x24 = e->getInt(1);
      return x24; 
    }), &aggresult);
    int x27 = x18;
    GenericEntry* x29 = new GenericEntry(true_type(), 2, x27, 3, x12);
    newOrderTbl.sliceCopy(0, x29, agg);
    GenericEntry* firstOrderEntry = aggresult;
    if((firstOrderEntry!=(NULL))) {
      int no_o_id = firstOrderEntry->getInt(1);
      int x36 = x18;
      orderIDs[(x36-(1))] = no_o_id;
      newOrderTbl.delCopy(firstOrderEntry);
      int x41 = x18;
      GenericEntry* x43 = new GenericEntry(true_type(), 1, no_o_id, 2, x41, 3, x12);
      GenericEntry* orderEntry = orderTbl.getCopy(x43, 0);
      int c_id = orderEntry->getInt(4);
      orderEntry->update(6, x13);
      orderTbl.updateCopy(orderEntry);
      double x50 = 0.0;
      int x52 = x18;
      GenericEntry* x54 = new GenericEntry(true_type(), 1, no_o_id, 2, x52, 3, x12);
      orderLineTbl.sliceCopy(0, x54, ([&](GenericEntry* orderLineEntry) {
        orderLineEntry->update(7, x11);
        double x57 = x50;
        double x58 = orderLineEntry->getDouble(9);
        x50 = (x57+(x58));
        orderLineTbl.updateCopy(orderLineEntry);
      
      }));
      int x65 = x18;
      GenericEntry* x67 = new GenericEntry(true_type(), 1, c_id, 2, x65, 3, x12);
      GenericEntry* customerEntry = customerTbl.getCopy(x67, 0);
      double x69 = x50;
      customerEntry->increase(17, x69);
      customerEntry->increase(20, 1);
      customerTbl.updateCopy(customerEntry);
    } else {
      
      int x73 = x18;
      orderIDs[(x73-(1))] = 0;
    };
    int x77 = x18;
    x18 = (x77+(1));
  };
}
void StockLevelTx(int x81, date x82, int x83, int x84, int x85, int x86) {
  GenericEntry* x89 = new GenericEntry(true_type(), 1, x85, 2, x84);
  GenericEntry* districtEntry = districtTbl.getCopy(x89, 0);
  int o_id = districtEntry->getInt(11);
  int x95 = (o_id-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x100 = x95;
    if (!((x100<(o_id)))) break; 
    
    int x102 = x95;
    GenericEntry* x104 = new GenericEntry(true_type(), 1, x102, 2, x85, 3, x84);
    orderLineTbl.sliceCopy(0, x104, ([&](GenericEntry* orderLineEntry) {
      int ol_i_id = orderLineEntry->getInt(5);
      GenericEntry* x110 = new GenericEntry(true_type(), 1, ol_i_id, 2, x84);
      GenericEntry* stockEntry = stockTbl.getCopy(x110, 0);
      int s_quantity = stockEntry->getInt(3);
      if((s_quantity<(x86))) {
        unique_ol_i_id.insert(ol_i_id);
      };
    
    }));
    int x119 = x95;
    x95 = (x119+(1));
  };
}
void OrderStatusTx(int x125, date x126, int x127, int x128, int x129, int x130, int x131, PString x132) {
  GenericEntry* ite2061 = NULL;
  if((x130>(0))) {
    vector<GenericEntry*> x2062;
    GenericEntry* x2067 = new GenericEntry(true_type(), 2, x129, 3, x128, 6, x132);
    customerTbl.sliceCopy(0, x2067, ([&](GenericEntry* custEntry) {
      x2062.push_back(custEntry);
    
    }));
    int x2069 = x2062.size();
    int x2071 = (x2069/(2));
    int x2079 = x2062.size();
    if(((x2079%(2))==(0))) {
      int x151 = x2071;
      x2071 = (x151-(1));
    };
    sort(x2062.begin(), x2062.end(), ([&](GenericEntry* c1, GenericEntry* c2) {
      
      PString x157 = c1->getString(4);
      PString x158 = c2->getString(4);
      return ((strcmpi(x157.data_, x158.data_))<(0)); 
    }));
    int x2087 = x2071;
    GenericEntry* x2088 = x2062[x2087];
    ite2061 = x2088;
  } else {
    
    GenericEntry* x2091 = new GenericEntry(true_type(), 1, x131, 2, x129, 3, x128);
    GenericEntry* x2092 = customerTbl.getCopy(x2091, 0);
    ite2061 = x2092;
  };
  GenericEntry* customerEntry = ite2061;
  int found_c_id = customerEntry->getInt(3);
  GenericEntry* aggresult;
  MaxAggregator<GenericEntry, int> agg(([&](GenericEntry* e) {
    int x173 = e->getInt(1);
    return x173; 
  }), &aggresult);
  GenericEntry* x177 = new GenericEntry(true_type(), 2, x129, 3, x128, 4, found_c_id);
  orderTbl.sliceCopy(0, x177, agg);
  GenericEntry* newestOrderEntry = aggresult;
  int x182 = 0;
  int x184 = newestOrderEntry->getInt(1);
  x182 = x184;
}
void PaymentTx(int x186, date x187, int x188, int x189, int x190, int x191, int x192, int x193, int x194, PString x195, double x196) {
  GenericEntry* x199 = new GenericEntry(true_type(), 1, x189);
  GenericEntry* warehouseEntry = warehouseTbl.getCopy(x199, 0);
  warehouseEntry->increase(9, x196);
  warehouseTbl.updateCopy(warehouseEntry);
  GenericEntry* x205 = new GenericEntry(true_type(), 1, x190, 2, x189);
  GenericEntry* districtEntry = districtTbl.getCopy(x205, 0);
  districtEntry->increase(10, x196);
  districtTbl.updateCopy(districtEntry);
  GenericEntry* ite2167 = NULL;
  if((x191>(0))) {
    vector<GenericEntry*> x2168;
    GenericEntry* x2173 = new GenericEntry(true_type(), 2, x193, 3, x192, 6, x195);
    customerTbl.sliceCopy(0, x2173, ([&](GenericEntry* custEntry) {
      x2168.push_back(custEntry);
    
    }));
    int x2175 = x2168.size();
    int x2177 = (x2175/(2));
    int x2185 = x2168.size();
    if(((x2185%(2))==(0))) {
      int x227 = x2177;
      x2177 = (x227-(1));
    };
    sort(x2168.begin(), x2168.end(), ([&](GenericEntry* c1, GenericEntry* c2) {
      
      PString x233 = c1->getString(4);
      PString x234 = c2->getString(4);
      return ((strcmpi(x233.data_, x234.data_))<(0)); 
    }));
    int x2193 = x2177;
    GenericEntry* x2194 = x2168[x2193];
    ite2167 = x2194;
  } else {
    
    GenericEntry* x2197 = new GenericEntry(true_type(), 1, x194, 2, x193, 3, x192);
    GenericEntry* x2198 = customerTbl.getCopy(x2197, 0);
    ite2167 = x2198;
  };
  GenericEntry* customerEntry = ite2167;
  PString c_data = customerEntry->getString(21);
  PString x247 = customerEntry->getString(14);
  char* x3453 = strstr(x247.data_, "BC");
  if((x3453!=(NULL))) {
    int x250 = customerEntry->getInt(1);
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x250, x193, x192, x190, x189, x196, IntToStrdate(x187), c_data.data_);
    customerEntry->increase(17, x196);
    customerEntry->update(21, c_new_data);
  } else {
    
    customerEntry->increase(17, x196);
  };
  customerTbl.updateCopy(customerEntry);
  PString w_name = warehouseEntry->getString(2);
  PString d_name = districtEntry->getString(3);
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", w_name.data_, d_name.data_);
  int x265 = customerEntry->getInt(1);
  GenericEntry* x267 = new GenericEntry(false_type(), x265, x193, x192, x190, x189, x187, x196, h_data);
  historyTbl.add(x267);
}
void NewOrderTx(int x269, date x270, int x271, int x272, int x273, int x274, int x275, int x276, int* x277, int* x278, int* x279, double* x280, PString* x281, int* x282, PString* x283, double* x284) {
  int x286 = 0;
  int x289 = 0;
  PString idata[x275];
  int x294 = 1;
  while(1) {
    
    int x296 = x286;
    int ite2467 = 0;
    if((x296<(x275))) {
      
      int x298 = x294;
      int x2468 = x298;
      ite2467 = x2468;
    } else {
      
      ite2467 = 0;
    };
    int x2293 = ite2467;
    if (!(x2293)) break; 
    
    int x301 = x286;
    int x302 = x277[x301];
    GenericEntry* x304 = new GenericEntry(true_type(), 1, x302);
    GenericEntry* itemEntry = itemTbl.getCopy(x304, 0);
    if((itemEntry==(NULL))) {
      x294 = 0;
    } else {
      
      int x308 = x286;
      PString x309 = itemEntry->getString(3);
      x281[x308] = x309;
      int x311 = x286;
      double x312 = itemEntry->getDouble(4);
      x280[x311] = x312;
      int x314 = x286;
      PString x315 = itemEntry->getString(5);
      idata[x314] = x315;
    };
    int x318 = x286;
    x286 = (x318+(1));
  };
  int x322 = x294;
  if(x322) {
    GenericEntry* x325 = new GenericEntry(true_type(), 1, x274, 2, x273, 3, x272);
    GenericEntry* customerEntry = customerTbl.getCopy(x325, 0);
    GenericEntry* x329 = new GenericEntry(true_type(), 1, x272);
    GenericEntry* warehouseEntry = warehouseTbl.getCopy(x329, 0);
    GenericEntry* x333 = new GenericEntry(true_type(), 1, x273, 2, x272);
    GenericEntry* districtEntry = districtTbl.getCopy(x333, 0);
    int o_id = districtEntry->getInt(11);
    districtEntry->increase(11, 1);
    districtTbl.updateCopy(districtEntry);
    GenericEntry* x341 = new GenericEntry(false_type(), o_id, x273, x272, x274, x270, -1, x275, (x276>(0)));
    orderTbl.add(x341);
    GenericEntry* x344 = new GenericEntry(false_type(), o_id, x273, x272);
    newOrderTbl.add(x344);
    double x347 = 0.0;
    x286 = 0;
    while(1) {
      
      int x350 = x286;
      if (!((x350<(x275)))) break; 
      
      int x353 = x286;
      int ol_supply_w_id = x278[x353];
      int x356 = x286;
      int ol_i_id = x277[x356];
      int x359 = x286;
      int ol_quantity = x279[x359];
      GenericEntry* x363 = new GenericEntry(true_type(), 1, ol_i_id, 2, ol_supply_w_id);
      GenericEntry* stockEntry = stockTbl.getCopy(x363, 0);
      PString ite2351 = PString();
      if((x273==(1))) {
        PString x2352 = stockEntry->getString(4);
        ite2351 = x2352;
      } else {
        
        PString ite2356 = PString();
        if((x273==(2))) {
          PString x2357 = stockEntry->getString(5);
          ite2356 = x2357;
        } else {
          
          PString ite2361 = PString();
          if((x273==(3))) {
            PString x2362 = stockEntry->getString(6);
            ite2361 = x2362;
          } else {
            
            PString ite2366 = PString();
            if((x273==(4))) {
              PString x2367 = stockEntry->getString(7);
              ite2366 = x2367;
            } else {
              
              PString ite2371 = PString();
              if((x273==(5))) {
                PString x2372 = stockEntry->getString(8);
                ite2371 = x2372;
              } else {
                
                PString ite2376 = PString();
                if((x273==(6))) {
                  PString x2377 = stockEntry->getString(9);
                  ite2376 = x2377;
                } else {
                  
                  PString ite2381 = PString();
                  if((x273==(7))) {
                    PString x2382 = stockEntry->getString(10);
                    ite2381 = x2382;
                  } else {
                    
                    PString ite2386 = PString();
                    if((x273==(8))) {
                      PString x2387 = stockEntry->getString(11);
                      ite2386 = x2387;
                    } else {
                      
                      PString ite2391 = PString();
                      if((x273==(9))) {
                        PString x2392 = stockEntry->getString(12);
                        ite2391 = x2392;
                      } else {
                        
                        PString x2394 = stockEntry->getString(13);
                        ite2391 = x2394;
                      };
                      PString x2390 = ite2391;
                      ite2386 = x2390;
                    };
                    PString x2385 = ite2386;
                    ite2381 = x2385;
                  };
                  PString x2380 = ite2381;
                  ite2376 = x2380;
                };
                PString x2375 = ite2376;
                ite2371 = x2375;
              };
              PString x2370 = ite2371;
              ite2366 = x2370;
            };
            PString x2365 = ite2366;
            ite2361 = x2365;
          };
          PString x2360 = ite2361;
          ite2356 = x2360;
        };
        PString x2355 = ite2356;
        ite2351 = x2355;
      };
      PString ol_dist_info = ite2351;
      int s_quantity = stockEntry->getInt(3);
      int x396 = x286;
      x282[x396] = s_quantity;
      PString x398 = customerEntry->getString(14);
      char* x3674 = strstr(x398.data_, "original");
      int ite2598 = 0;
      if((x3674!=(NULL))) {
        
        PString x400 = stockEntry->getString(17);
        char* x3680 = strstr(x400.data_, "original");
        int x2599 = (x3680!=(NULL));
        ite2598 = x2599;
      } else {
        
        ite2598 = 0;
      };
      int x2419 = ite2598;
      if(x2419) {
        int x403 = x286;
        x283[x403] = "B";
      } else {
        
        int x405 = x286;
        x283[x405] = "G";
      };
      stockEntry->update(3, (s_quantity-(ol_quantity)));
      if((s_quantity<=(ol_quantity))) {
        stockEntry->increase(3, 91);
      };
      int x414 = 0;
      if((ol_supply_w_id!=(x272))) {
        x414 = 1;
      };
      stockTbl.updateCopy(stockEntry);
      double c_discount = customerEntry->getDouble(16);
      double w_tax = warehouseEntry->getDouble(8);
      double d_tax = districtEntry->getDouble(9);
      int x427 = x286;
      double x428 = x280[x427];
      double ol_amount = ((ol_quantity*(x428))*(((1.0+(w_tax))+(d_tax))))*((1.0-(c_discount)));
      int x436 = x286;
      x284[x436] = ol_amount;
      double x438 = x347;
      x347 = (x438+(ol_amount));
      int x441 = x286;
      GenericEntry* x444 = new GenericEntry(false_type(), o_id, x273, x272, (x441+(1)), ol_i_id, ol_supply_w_id, NULL, ol_quantity, ol_amount, ol_dist_info);
      orderLineTbl.add(x444);
      int x446 = x286;
      x286 = (x446+(1));
    };
  };
}
#include "TPCC.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  TPCCDataGen tpcc;
  tpcc.loadPrograms();
  tpcc.loadWare();
  tpcc.loadDist();
  tpcc.loadCust();
  tpcc.loadItem();
  tpcc.loadNewOrd();
  tpcc.loadOrders();
  tpcc.loadOrdLine();
  tpcc.loadHist();
  tpcc.loadStocks();
  
  for(size_t i = 0; i < numPrograms; ++i){
    Program *prg = tpcc.programs[i];
    switch(prg->id){
       case NEWORDER :
        {
           NewOrder& p = *(NewOrder *)prg;
           NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
           break;
        }
      case PAYMENTBYID :
        {
           PaymentById& p = *(PaymentById *) prg;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
           break;
        }
      case PAYMENTBYNAME :
        {
           PaymentByName& p = *(PaymentByName *) prg;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
           break;
        }
      case ORDERSTATUSBYID :
        {
           OrderStatusById &p = *(OrderStatusById *) prg;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
           break;
        }
      case ORDERSTATUSBYNAME :
        {
           OrderStatusByName &p = *(OrderStatusByName *) prg;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
           break;
        }
      case DELIVERY :
        {
           Delivery &p = *(Delivery *) prg;
           DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
           break;
        }
      case STOCKLEVEL :
       {
         StockLevel &p = *(StockLevel *) prg;
         StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
         break;
       }
       default : cerr << "UNKNOWN PROGRAM TYPE" << endl;
  
    }
  }
  
  #ifdef VERIFY_TPCC
      if (warehouseTblPrimaryIdx == tpcc.wareRes) {
          cout << "Warehouse results are correct" << endl;
      } else {
          cerr << "Warehouse results INCORRECT!" << endl;
      }
      if (districtTblPrimaryIdx == tpcc.distRes) {
          cout << "District results are correct" << endl;
      } else {
          cerr << "District results INCORRECT!" << endl;
      }
      if (customerTblPrimaryIdx == tpcc.custRes) {
          cout << "Customer results are correct" << endl;
      } else {
          cerr << "Customer results INCORRECT!" << endl;
      }
      if (orderTblPrimaryIdx == tpcc.ordRes) {
          cout << "Order results are correct" << endl;
      } else {
          cerr << "Order results INCORRECT!" << endl;
      }
      if (orderLineTblPrimaryIdx == tpcc.ordLRes) {
          cout << "OrderLine results are correct" << endl;
      } else {
          cerr << "OrderLine results INCORRECT!" << endl;
      }
      if (newOrderTblPrimaryIdx == tpcc.newOrdRes) {
          cout << "NewOrder results are correct" << endl;
      } else {
          cerr << "NewOrder results INCORRECT!" << endl;
      }
      if (itemTblPrimaryIdx == tpcc.itemRes) {
          cout << "Item results are correct" << endl;
      } else {
          cerr << "Item results INCORRECT!" << endl;
      }
      if (stockTblPrimaryIdx == tpcc.stockRes) {
          cout << "Stock results are correct" << endl;
      } else {
          cerr << "Stock results INCORRECT!" << endl;
      }
      if (historyTblPrimaryIdx == tpcc.histRes) {
          cout << "History results are correct" << endl;
      } else {
          cerr << "History results INCORRECT!" << endl;
      }
  
  #endif
  
        
}
/* ----------- FUNCTIONS ----------- */
