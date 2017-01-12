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

     


#define int unsigned int
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
#undef int

typedef ListIndex<GenericEntry, char, GenericOps_123, 0> newOrderTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_123, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblIdx0Type& x460 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps, 0> historyTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblIdx0Type& x465 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_1, 0> warehouseTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_1, 0>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblIdx0Type& x470 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_1, 0> itemTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_1, 0>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblIdx0Type& x473 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_123, 0> orderTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_123, 0>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblIdx0Type& x476 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_12, 0> districtTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_12, 0>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblIdx0Type& x481 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_1234, 0> orderLineTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_1234, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblIdx0Type& x486 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_123, 0> customerTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_123, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblIdx0Type& x489 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ListIndex<GenericEntry, char, GenericOps_12, 0> stockTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ListIndex<GenericEntry, char, GenericOps_12, 0>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblIdx0Type& x492 = * (stockTblIdx0Type *)stockTbl.index[0];
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
      double x51 = 0.0;
      int x53 = x18;
      GenericEntry* x55 = new GenericEntry(true_type(), 1, no_o_id, 2, x53, 3, x12);
      orderLineTbl.sliceCopy(0, x55, ([&](GenericEntry* orderLineEntry) {
        orderLineEntry->update(7, x11);
        double x58 = x51;
        double x59 = orderLineEntry->getDouble(9);
        x51 = (x58+(x59));
        orderLineTbl.updateCopy(orderLineEntry);
      
      }));
      int x66 = x18;
      GenericEntry* x68 = new GenericEntry(true_type(), 1, c_id, 2, x66, 3, x12);
      GenericEntry* customerEntry = customerTbl.getCopy(x68, 0);
      double x70 = x51;
      customerEntry->increase(17, x70);
      customerEntry->increase(20, 1);
      customerTbl.updateCopy(customerEntry);
    } else {
      
      int x74 = x18;
      orderIDs[(x74-(1))] = 0;
    };
    int x78 = x18;
    x18 = (x78+(1));
  };
}
void StockLevelTx(int x82, date x83, int x84, int x85, int x86, int x87) {
  GenericEntry* x90 = new GenericEntry(true_type(), 1, x86, 2, x85);
  GenericEntry* districtEntry = districtTbl.getCopy(x90, 0);
  int o_id = districtEntry->getInt(11);
  int x97 = (o_id-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x101 = x97;
    if (!((x101<(o_id)))) break; 
    
    int x103 = x97;
    GenericEntry* x105 = new GenericEntry(true_type(), 1, x103, 2, x86, 3, x85);
    orderLineTbl.sliceCopy(0, x105, ([&](GenericEntry* orderLineEntry) {
      int ol_i_id = orderLineEntry->getInt(5);
      GenericEntry* x111 = new GenericEntry(true_type(), 1, ol_i_id, 2, x85);
      GenericEntry* stockEntry = stockTbl.getCopy(x111, 0);
      int s_quantity = stockEntry->getInt(3);
      if((s_quantity<(x87))) {
        unique_ol_i_id.insert(ol_i_id);
      };
    
    }));
    int x120 = x97;
    x97 = (x120+(1));
  };
}
void OrderStatusTx(int x126, date x127, int x128, int x129, int x130, int x131, int x132, PString x133) {
  GenericEntry* ite2097 = NULL;
  if((x131>(0))) {
    vector<GenericEntry*> x2098;
    GenericEntry* x2103 = new GenericEntry(true_type(), 2, x130, 3, x129, 6, x133);
    customerTbl.sliceCopy(0, x2103, ([&](GenericEntry* custEntry) {
      x2098.push_back(custEntry);
    
    }));
    int x2105 = x2098.size();
    int x2107 = (x2105/(2));
    int x2115 = x2098.size();
    if(((x2115%(2))==(0))) {
      int x152 = x2107;
      x2107 = (x152-(1));
    };
    sort(x2098.begin(), x2098.end(), ([&](GenericEntry* c1, GenericEntry* c2) {
      
      PString x158 = c1->getString(4);
      PString x159 = c2->getString(4);
      return ((strcmpi(x158.data_, x159.data_))<(0)); 
    }));
    int x2123 = x2107;
    GenericEntry* x2124 = x2098[x2123];
    ite2097 = x2124;
  } else {
    
    GenericEntry* x2127 = new GenericEntry(true_type(), 1, x132, 2, x130, 3, x129);
    GenericEntry* x2129 = customerTbl.getCopy(x2127, 0);
    ite2097 = x2129;
  };
  GenericEntry* customerEntry = ite2097;
  int found_c_id = customerEntry->getInt(3);
  GenericEntry* aggresult;
  MaxAggregator<GenericEntry, int> agg(([&](GenericEntry* e) {
    int x175 = e->getInt(1);
    return x175; 
  }), &aggresult);
  GenericEntry* x179 = new GenericEntry(true_type(), 2, x130, 3, x129, 4, found_c_id);
  orderTbl.sliceCopy(0, x179, agg);
  GenericEntry* newestOrderEntry = aggresult;
  int x184 = 0;
  int x186 = newestOrderEntry->getInt(1);
  x184 = x186;
}
void PaymentTx(int x188, date x189, int x190, int x191, int x192, int x193, int x194, int x195, int x196, PString x197, double x198) {
  GenericEntry* x201 = new GenericEntry(true_type(), 1, x191);
  GenericEntry* warehouseEntry = warehouseTbl.getCopy(x201, 0);
  warehouseEntry->increase(9, x198);
  warehouseTbl.updateCopy(warehouseEntry);
  GenericEntry* x208 = new GenericEntry(true_type(), 1, x192, 2, x191);
  GenericEntry* districtEntry = districtTbl.getCopy(x208, 0);
  districtEntry->increase(10, x198);
  districtTbl.updateCopy(districtEntry);
  GenericEntry* ite2206 = NULL;
  if((x193>(0))) {
    vector<GenericEntry*> x2207;
    GenericEntry* x2212 = new GenericEntry(true_type(), 2, x195, 3, x194, 6, x197);
    customerTbl.sliceCopy(0, x2212, ([&](GenericEntry* custEntry) {
      x2207.push_back(custEntry);
    
    }));
    int x2214 = x2207.size();
    int x2216 = (x2214/(2));
    int x2224 = x2207.size();
    if(((x2224%(2))==(0))) {
      int x230 = x2216;
      x2216 = (x230-(1));
    };
    sort(x2207.begin(), x2207.end(), ([&](GenericEntry* c1, GenericEntry* c2) {
      
      PString x236 = c1->getString(4);
      PString x237 = c2->getString(4);
      return ((strcmpi(x236.data_, x237.data_))<(0)); 
    }));
    int x2232 = x2216;
    GenericEntry* x2233 = x2207[x2232];
    ite2206 = x2233;
  } else {
    
    GenericEntry* x2236 = new GenericEntry(true_type(), 1, x196, 2, x195, 3, x194);
    GenericEntry* x2237 = customerTbl.getCopy(x2236, 0);
    ite2206 = x2237;
  };
  GenericEntry* customerEntry = ite2206;
  PString c_data = customerEntry->getString(21);
  PString x250 = customerEntry->getString(14);
  char* x3517 = strstr(x250.data_, "BC");
  if((x3517!=(NULL))) {
    int x253 = customerEntry->getInt(1);
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x253, x195, x194, x192, x191, x198, IntToStrdate(x189), c_data.data_);
    customerEntry->increase(17, x198);
    customerEntry->update(21, c_new_data);
  } else {
    
    customerEntry->increase(17, x198);
  };
  customerTbl.updateCopy(customerEntry);
  PString w_name = warehouseEntry->getString(2);
  PString d_name = districtEntry->getString(3);
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", w_name.data_, d_name.data_);
  int x268 = customerEntry->getInt(1);
  GenericEntry* x270 = new GenericEntry(false_type(), x268, x195, x194, x192, x191, x189, x198, h_data);
  historyTbl.add(x270);
}
void NewOrderTx(int x272, date x273, int x274, int x275, int x276, int x277, int x278, int x279, int* x280, int* x281, int* x282, double* x283, PString* x284, int* x285, PString* x286, double* x287) {
  int x289 = 0;
  int x292 = 0;
  PString idata[x278];
  int x297 = 1;
  while(1) {
    
    int x299 = x289;
    int ite2509 = 0;
    if((x299<(x278))) {
      
      int x301 = x297;
      int x2510 = x301;
      ite2509 = x2510;
    } else {
      
      ite2509 = 0;
    };
    int x2333 = ite2509;
    if (!(x2333)) break; 
    
    int x304 = x289;
    int x305 = x280[x304];
    GenericEntry* x307 = new GenericEntry(true_type(), 1, x305);
    GenericEntry* itemEntry = itemTbl.getCopy(x307, 0);
    if((itemEntry==(NULL))) {
      x297 = 0;
    } else {
      
      int x312 = x289;
      PString x313 = itemEntry->getString(3);
      x284[x312] = x313;
      int x315 = x289;
      double x316 = itemEntry->getDouble(4);
      x283[x315] = x316;
      int x318 = x289;
      PString x319 = itemEntry->getString(5);
      idata[x318] = x319;
    };
    int x322 = x289;
    x289 = (x322+(1));
  };
  int x326 = x297;
  if(x326) {
    GenericEntry* x329 = new GenericEntry(true_type(), 1, x277, 2, x276, 3, x275);
    GenericEntry* customerEntry = customerTbl.getCopy(x329, 0);
    GenericEntry* x334 = new GenericEntry(true_type(), 1, x275);
    GenericEntry* warehouseEntry = warehouseTbl.getCopy(x334, 0);
    GenericEntry* x338 = new GenericEntry(true_type(), 1, x276, 2, x275);
    GenericEntry* districtEntry = districtTbl.getCopy(x338, 0);
    int o_id = districtEntry->getInt(11);
    districtEntry->increase(11, 1);
    districtTbl.updateCopy(districtEntry);
    GenericEntry* x346 = new GenericEntry(false_type(), o_id, x276, x275, x277, x273, -1, x278, (x279>(0)));
    orderTbl.add(x346);
    GenericEntry* x349 = new GenericEntry(false_type(), o_id, x276, x275);
    newOrderTbl.add(x349);
    double x352 = 0.0;
    x289 = 0;
    while(1) {
      
      int x355 = x289;
      if (!((x355<(x278)))) break; 
      
      int x358 = x289;
      int ol_supply_w_id = x281[x358];
      int x361 = x289;
      int ol_i_id = x280[x361];
      int x364 = x289;
      int ol_quantity = x282[x364];
      GenericEntry* x368 = new GenericEntry(true_type(), 1, ol_i_id, 2, ol_supply_w_id);
      GenericEntry* stockEntry = stockTbl.getCopy(x368, 0);
      PString ite2393 = PString();
      if((x276==(1))) {
        PString x2394 = stockEntry->getString(4);
        ite2393 = x2394;
      } else {
        
        PString ite2398 = PString();
        if((x276==(2))) {
          PString x2399 = stockEntry->getString(5);
          ite2398 = x2399;
        } else {
          
          PString ite2403 = PString();
          if((x276==(3))) {
            PString x2404 = stockEntry->getString(6);
            ite2403 = x2404;
          } else {
            
            PString ite2408 = PString();
            if((x276==(4))) {
              PString x2409 = stockEntry->getString(7);
              ite2408 = x2409;
            } else {
              
              PString ite2413 = PString();
              if((x276==(5))) {
                PString x2414 = stockEntry->getString(8);
                ite2413 = x2414;
              } else {
                
                PString ite2418 = PString();
                if((x276==(6))) {
                  PString x2419 = stockEntry->getString(9);
                  ite2418 = x2419;
                } else {
                  
                  PString ite2423 = PString();
                  if((x276==(7))) {
                    PString x2424 = stockEntry->getString(10);
                    ite2423 = x2424;
                  } else {
                    
                    PString ite2428 = PString();
                    if((x276==(8))) {
                      PString x2429 = stockEntry->getString(11);
                      ite2428 = x2429;
                    } else {
                      
                      PString ite2433 = PString();
                      if((x276==(9))) {
                        PString x2434 = stockEntry->getString(12);
                        ite2433 = x2434;
                      } else {
                        
                        PString x2436 = stockEntry->getString(13);
                        ite2433 = x2436;
                      };
                      PString x2432 = ite2433;
                      ite2428 = x2432;
                    };
                    PString x2427 = ite2428;
                    ite2423 = x2427;
                  };
                  PString x2422 = ite2423;
                  ite2418 = x2422;
                };
                PString x2417 = ite2418;
                ite2413 = x2417;
              };
              PString x2412 = ite2413;
              ite2408 = x2412;
            };
            PString x2407 = ite2408;
            ite2403 = x2407;
          };
          PString x2402 = ite2403;
          ite2398 = x2402;
        };
        PString x2397 = ite2398;
        ite2393 = x2397;
      };
      PString ol_dist_info = ite2393;
      int s_quantity = stockEntry->getInt(3);
      int x401 = x289;
      x285[x401] = s_quantity;
      PString x403 = customerEntry->getString(14);
      char* x3741 = strstr(x403.data_, "original");
      int ite2642 = 0;
      if((x3741!=(NULL))) {
        
        PString x405 = stockEntry->getString(17);
        char* x3747 = strstr(x405.data_, "original");
        int x2643 = (x3747!=(NULL));
        ite2642 = x2643;
      } else {
        
        ite2642 = 0;
      };
      int x2461 = ite2642;
      if(x2461) {
        int x408 = x289;
        x286[x408] = "B";
      } else {
        
        int x410 = x289;
        x286[x410] = "G";
      };
      stockEntry->update(3, (s_quantity-(ol_quantity)));
      if((s_quantity<=(ol_quantity))) {
        stockEntry->increase(3, 91);
      };
      int x419 = 0;
      if((ol_supply_w_id!=(x275))) {
        x419 = 1;
      };
      stockTbl.updateCopy(stockEntry);
      double c_discount = customerEntry->getDouble(16);
      double w_tax = warehouseEntry->getDouble(8);
      double d_tax = districtEntry->getDouble(9);
      int x432 = x289;
      double x433 = x283[x432];
      double ol_amount = ((ol_quantity*(x433))*(((1.0+(w_tax))+(d_tax))))*((1.0-(c_discount)));
      int x441 = x289;
      x287[x441] = ol_amount;
      double x443 = x352;
      x352 = (x443+(ol_amount));
      int x446 = x289;
      GenericEntry* x449 = new GenericEntry(false_type(), o_id, x276, x275, (x446+(1)), ol_i_id, ol_supply_w_id, NULL, ol_quantity, ol_amount, ol_dist_info);
      orderLineTbl.add(x449);
      int x451 = x289;
      x289 = (x451+(1));
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
