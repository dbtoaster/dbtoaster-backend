#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SC_GENERATED 1
#define USING_GENERIC_ENTRY true

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
#include <iomanip>
#include <fstream>
#include <locale>

#include "ExecutionProfiler.h"

using namespace std;
#include "hpds/pstring.hpp"
#include "hpds/pstringops.hpp"
#include "program_base.hpp"

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

const size_t districtTblArrayLengths[] = {1};
const size_t customerTblArrayLengths[] = {1,1};
const size_t itemTblArrayLengths[] = {1};
const size_t historyTblArrayLengths[] = {1};
const size_t orderTblArrayLengths[] = {1,1};
const size_t newOrderTblArrayLengths[] = {1,1};
const size_t warehouseTblArrayLengths[] = {1};
const size_t stockTblArrayLengths[] = {1};
const size_t orderLineTblArrayLengths[] = {1,1};

const size_t warehouseTblPoolSizes[] = {8, 0};
const size_t itemTblPoolSizes[] = {65536*2, 0};
const size_t districtTblPoolSizes[] = {16, 0};
const size_t customerTblPoolSizes[] = {16384*2, 0, 16384};
const size_t orderTblPoolSizes[] = {262144*2, 65536, 0};
const size_t newOrderTblPoolSizes[] = {8192*2, 2048, 0};
const size_t orderLineTblPoolSizes[] = {4194304*2, 1048576, 2097152};
const size_t stockTblPoolSizes[] = {65536*2, 0};
const size_t historyTblPoolSizes[] = {262144*2, 65536};
     


struct GenericOps_23 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    for(int c : {2, 3})
      h = h ^ (HASH(e.map.at(c)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
      for(int c : {2, 3})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};
struct GenericOps_236 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    for(int c : {2, 3, 6})
      h = h ^ (HASH(e.map.at(c)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
      for(int c : {2, 3, 6})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};
struct GenericOps_1234 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    for(int c : {1, 2, 3, 4})
      h = h ^ (HASH(e.map.at(c)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
struct GenericOps_12345678 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    for(int c : {1, 2, 3, 4, 5, 6, 7, 8})
      h = h ^ (HASH(e.map.at(c)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
      for(int c : {1, 2, 3, 4, 5, 6, 7, 8})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};
struct GenericOps_123 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    for(int c : {1, 2, 3})
      h = h ^ (HASH(e.map.at(c)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
struct GenericOps_234 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    for(int c : {2, 3, 4})
      h = h ^ (HASH(e.map.at(c)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
      for(int c : {2, 3, 4})
        if(e1.map.at(c) != e2.map.at(c))
          return 1;
    }
    return 0;
  }
};
struct GenericCmp_236_4 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 16;
    for(int c : {236})
      h = h * 41 + HASH(e.map.at(c));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    const Any &r1 = e1.map.at(4);
    const Any &r2 = e2.map.at(4);
    if (r1 == r2)
      return 0;
    else if( r1 < r2)
      return -1;
    else
      return 1;
          
  }
};
struct GenericCmp_23_1 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 16;
    for(int c : {23})
      h = h * 41 + HASH(e.map.at(c));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    const Any &r1 = e1.map.at(1);
    const Any &r2 = e2.map.at(1);
    if (r1 == r2)
      return 0;
    else if( r1 < r2)
      return -1;
    else
      return 1;
          
  }
};
struct GenericCmp_234_1 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 16;
    for(int c : {234})
      h = h * 41 + HASH(e.map.at(c));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    const Any &r1 = e1.map.at(1);
    const Any &r2 = e2.map.at(1);
    if (r1 == r2)
      return 0;
    else if( r1 < r2)
      return -1;
    else
      return 1;
          
  }
};
struct GenericFixedRange_1f1t100001 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    int cols[] = {1};
    int lower[] = {1};
    int upper[] = {100001};
    for(int i = 0; i < 1; ++i)
      h = h * (upper[i] - lower[i]) + e.getInt(cols[i]) - lower[i];  //Defined only for int
    return h;
            
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_1f1t3001_2f1t11_3f1t2 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    int cols[] = {1, 2, 3};
    int lower[] = {1, 1, 1};
    int upper[] = {3001, 11, 2};
    for(int i = 0; i < 3; ++i)
      h = h * (upper[i] - lower[i]) + e.getInt(cols[i]) - lower[i];  //Defined only for int
    return h;
            
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_1f1t11_2f1t2 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    int cols[] = {1, 2};
    int lower[] = {1, 1};
    int upper[] = {11, 2};
    for(int i = 0; i < 2; ++i)
      h = h * (upper[i] - lower[i]) + e.getInt(cols[i]) - lower[i];  //Defined only for int
    return h;
            
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_1f1t2 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    int cols[] = {1};
    int lower[] = {1};
    int upper[] = {2};
    for(int i = 0; i < 1; ++i)
      h = h * (upper[i] - lower[i]) + e.getInt(cols[i]) - lower[i];  //Defined only for int
    return h;
            
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_1f1t100001_2f1t2 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    size_t h = 0;
    int cols[] = {1, 2};
    int lower[] = {1, 1};
    int upper[] = {100001, 2};
    for(int i = 0; i < 2; ++i)
      h = h * (upper[i] - lower[i]) + e.getInt(cols[i]) - lower[i];  //Defined only for int
    return h;
            
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};

typedef HashIndex<GenericEntry, char, GenericOps_123, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<GenericEntry, char, GenericOps_23, GenericCmp_23_1, 0> newOrderTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps_123, 1>,
   SlicedHeapIndex<GenericEntry, char, GenericOps_23, GenericCmp_23_1, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl;
newOrderTblIdx0Type& newOrderTblIdx0 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& newOrderTblIdx1 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];


typedef HashIndex<GenericEntry, char, GenericOps_12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps_12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl;
historyTblIdx0Type& historyTblIdx0 = * (historyTblIdx0Type *)historyTbl.index[0];


typedef ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl;
warehouseTblIdx0Type& warehouseTblIdx0 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];


typedef ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl;
itemTblIdx0Type& itemTblIdx0 = * (itemTblIdx0Type *)itemTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps_123, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<GenericEntry, char, GenericOps_234, GenericCmp_234_1, 1> orderTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps_123, 1>,
   SlicedHeapIndex<GenericEntry, char, GenericOps_234, GenericCmp_234_1, 1>> orderTblStoreType;
orderTblStoreType  orderTbl;
orderTblIdx0Type& orderTblIdx0 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& orderTblIdx1 = * (orderTblIdx1Type *)orderTbl.index[1];


typedef ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl;
districtTblIdx0Type& districtTblIdx0 = * (districtTblIdx0Type *)districtTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps_1234, 1> orderLineTblIdx0Type;
typedef HashIndex<GenericEntry, char, GenericOps_123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps_1234, 1>,
   HashIndex<GenericEntry, char, GenericOps_123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl;
orderLineTblIdx0Type& orderLineTblIdx0 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& orderLineTblIdx1 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];


typedef ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef SlicedMedHeapIndex<GenericEntry, char, GenericOps_236, GenericCmp_236_4> customerTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t3001_2f1t11_3f1t2, 30000>,
   SlicedMedHeapIndex<GenericEntry, char, GenericOps_236, GenericCmp_236_4>> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& customerTblIdx1 = * (customerTblIdx1Type *)customerTbl.index[1];


typedef ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   ArrayIndex<GenericEntry, char, GenericFixedRange_1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl;
stockTblIdx0Type& stockTblIdx0 = * (stockTblIdx0Type *)stockTbl.index[0];




void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[10];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    GenericEntry* x29 = new GenericEntry(true_type(), 2, x27, 3, x12);
    GenericEntry* x2897 = newOrderTblIdx1.getCopy(x29);
    if((x2897!=(NULL))) {
      int no_o_id = x2897->getInt(1);
      int x36 = x18;
      orderIDs[(x36-(1))] = no_o_id;
      newOrderTbl.delCopy(x2897);
      int x41 = x18;
      GenericEntry* x43 = new GenericEntry(true_type(), 1, no_o_id, 2, x41, 3, x12);
      GenericEntry* x2908 = orderTblIdx0.getCopy(x43);
      int c_id = x2908->getInt(4);
      x2908->update(6, x13);
      GenericEntry* x2911 = orderTbl.copyIntoPool(x2908);
      orderTblIdx1.updateCopy(x2911, &orderTblIdx0);
      orderTblIdx0.updateCopy(x2911, &orderTblIdx0);
      double x50 = 0.0;
      int x52 = x18;
      GenericEntry* x54 = new GenericEntry(true_type(), 1, no_o_id, 2, x52, 3, x12);
      orderLineTblIdx1.sliceCopy(x54, ([&](GenericEntry* orderLineEntry) {
        orderLineEntry->update(7, x11);
        double x57 = x50;
        double x58 = orderLineEntry->getDouble(9);
        x50 = (x57+(x58));
        GenericEntry* x2922 = orderLineTbl.copyIntoPool(orderLineEntry);
        orderLineTblIdx1.updateCopy(x2922, &orderLineTblIdx0);
        orderLineTblIdx0.updateCopy(x2922, &orderLineTblIdx0);
      
      }));
      int x65 = x18;
      GenericEntry* x67 = new GenericEntry(true_type(), 1, c_id, 2, x65, 3, x12);
      GenericEntry* x2932 = customerTblIdx0.getCopy(x67);
      double x69 = x50;
      x2932->increase(17, x69);
      x2932->increase(20, 1);
      GenericEntry* x2936 = customerTbl.copyIntoPool(x2932);
     customerTblIdx1.updateCopy(x2936, &customerTblIdx0);
      customerTblIdx0.updateCopy(x2936, &customerTblIdx0);
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
  GenericEntry* x3003 = districtTblIdx0.getCopy(x89);
  int o_id = x3003->getInt(11);
  int x95 = (o_id-(20));
  unordered_set<int> unique_ol_i_id; //setApply2
  while(1) {
    
    int x99 = x95;
    if (!((x99<(o_id)))) break; 
    
    int x101 = x95;
    GenericEntry* x103 = new GenericEntry(true_type(), 1, x101, 2, x85, 3, x84);
    orderLineTblIdx1.sliceCopy(x103, ([&](GenericEntry* orderLineEntry) {
      int ol_i_id = orderLineEntry->getInt(5);
      GenericEntry* x109 = new GenericEntry(true_type(), 1, ol_i_id, 2, x84);
      GenericEntry* x3016 = stockTblIdx0.getCopy(x109);
      int s_quantity = x3016->getInt(3);
      if((s_quantity<(x86))) {
        unique_ol_i_id.insert(ol_i_id);
      };
    
    }));
    int x118 = x95;
    x95 = (x118+(1));
  };
}
void OrderStatusTx(int x124, date x125, int x126, int x127, int x128, int x129, int x130, PString x131) {
  GenericEntry* ite5302 = NULL;
  if((x129>(0))) {
    GenericEntry* x5304 = new GenericEntry(true_type(), 2, x128, 3, x127, 6, x131);
    GenericEntry* x5305 = customerTblIdx1.getCopy(x5304);
    ite5302 = x5305;
  } else {
    GenericEntry* x5308 = new GenericEntry(true_type(), 1, x130, 2, x128, 3, x127);
    GenericEntry* x5309 = customerTblIdx0.getCopy(x5308);
    ite5302 = x5309;
  };
  GenericEntry* customerEntry = ite5302;
  int found_c_id = customerEntry->getInt(3);
  GenericEntry* x155 = new GenericEntry(true_type(), 2, x128, 3, x127, 4, found_c_id);
  GenericEntry* x3066 = orderTblIdx1.getCopy(x155);
  int x160 = 0;
  int x162 = x3066->getInt(1);
  x160 = x162;
}
void PaymentTx(int x164, date x165, int x166, int x167, int x168, int x169, int x170, int x171, int x172, PString x173, double x174) {
  GenericEntry* x177 = new GenericEntry(true_type(), 1, x167);
  GenericEntry* x3087 = warehouseTblIdx0.getCopy(x177);
  x3087->increase(9, x174);
  GenericEntry* x3089 = warehouseTbl.copyIntoPool(x3087);
  warehouseTblIdx0.updateCopy(x3089, &warehouseTblIdx0);
  GenericEntry* x183 = new GenericEntry(true_type(), 1, x168, 2, x167);
  GenericEntry* x3093 = districtTblIdx0.getCopy(x183);
  x3093->increase(10, x174);
  GenericEntry* x3095 = districtTbl.copyIntoPool(x3093);
  districtTblIdx0.updateCopy(x3095, &districtTblIdx0);
  GenericEntry* ite5352 = NULL;
  if((x169>(0))) {
    GenericEntry* x5354 = new GenericEntry(true_type(), 2, x171, 3, x170, 6, x173);
    GenericEntry* x5355 = customerTblIdx1.getCopy(x5354);
    ite5352 = x5355;
  } else {
    GenericEntry* x5358 = new GenericEntry(true_type(), 1, x172, 2, x171, 3, x170);
    GenericEntry* x5359 = customerTblIdx0.getCopy(x5358);
    ite5352 = x5359;
  };
  GenericEntry* customerEntry = ite5352;
  const PString& c_data = customerEntry->getString(21);
  const PString& x204 = customerEntry->getString(14);
  char* x6548 = strstr(x204.data_, "BC");
  if((x6548!=(NULL))) {
    int x207 = customerEntry->getInt(1);
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x207, x171, x170, x168, x167, x174, IntToStrdate(x165), c_data.data_);
    customerEntry->increase(17, x174);
    customerEntry->update(21, c_new_data);
  } else {
    customerEntry->increase(17, x174);
  };
  GenericEntry* x3115 = customerTbl.copyIntoPool(customerEntry);
  customerTblIdx1.updateCopy(x3115, &customerTblIdx0);
  customerTblIdx0.updateCopy(x3115, &customerTblIdx0);
  const PString& w_name = x3087->getString(2);
  const PString& d_name = x3093->getString(3);
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", w_name.data_, d_name.data_);
  int x222 = customerEntry->getInt(1);
  GenericEntry* x224 = new GenericEntry(false_type(), x222, x171, x170, x168, x167, x165, x174, h_data);
  historyTbl.insert_nocheck(x224);
}
void NewOrderTx(int x226, date x227, int x228, int x229, int x230, int x231, int x232, int x233, int* x234, int* x235, int* x236, double* x237, PString* x238, int* x239, PString* x240, double* x241) {
  int x243 = 0;
  int x246 = 0;
  PString idata[x232];
  int x251 = 1;
  while(1) {
    
    int x253 = x243;
    int ite5613 = NULL;
    if((x253<(x232))) {
      
      int x255 = x251;
      int x5614 = x255;
      ite5613 = x5614;
    } else {
      ite5613 = 0;
    };
    int x5436 = ite5613;
    if (!(x5436)) break; 
    
    int x258 = x243;
    int x259 = x234[x258];
    GenericEntry* x261 = new GenericEntry(true_type(), 1, x259);
    GenericEntry* x3180 = itemTblIdx0.getCopy(x261);
    if((x3180==(NULL))) {
      x251 = 0;
    } else {
      int x265 = x243;
      const PString& x266 = x3180->getString(3);
      x238[x265] = x266;
      int x268 = x243;
      double x269 = x3180->getDouble(4);
      x237[x268] = x269;
      int x271 = x243;
      const PString& x272 = x3180->getString(5);
      idata[x271] = x272;
    };
    int x275 = x243;
    x243 = (x275+(1));
  };
  int x279 = x251;
  if(x279) {
    GenericEntry* x282 = new GenericEntry(true_type(), 1, x231, 2, x230, 3, x229);
    GenericEntry* x3200 = customerTblIdx0.getCopy(x282);
    GenericEntry* x286 = new GenericEntry(true_type(), 1, x229);
    GenericEntry* x3203 = warehouseTblIdx0.getCopy(x286);
    GenericEntry* x290 = new GenericEntry(true_type(), 1, x230, 2, x229);
    GenericEntry* x3206 = districtTblIdx0.getCopy(x290);
    int o_id = x3206->getInt(11);
    x3206->increase(11, 1);
    GenericEntry* x3209 = districtTbl.copyIntoPool(x3206);
    districtTblIdx0.updateCopy(x3209, &districtTblIdx0);
    GenericEntry* x298 = new GenericEntry(false_type(), o_id, x230, x229, x231, x227, -1, x232, (x233>(0)));
    orderTbl.insert_nocheck(x298);
    GenericEntry* x301 = new GenericEntry(false_type(), o_id, x230, x229);
    newOrderTbl.insert_nocheck(x301);
    double x304 = 0.0;
    x243 = 0;
    while(1) {
      
      int x307 = x243;
      if (!((x307<(x232)))) break; 
      
      int x310 = x243;
      int ol_supply_w_id = x235[x310];
      int x313 = x243;
      int ol_i_id = x234[x313];
      int x316 = x243;
      int ol_quantity = x236[x316];
      GenericEntry* x320 = new GenericEntry(true_type(), 1, ol_i_id, 2, ol_supply_w_id);
      GenericEntry* x3231 = stockTblIdx0.getCopy(x320);
      PString ite5495 = PString();
      if((x230==(1))) {
        const PString& x5496 = x3231->getString(4);
        ite5495 = x5496;
      } else {
        PString ite5500 = PString();
        if((x230==(2))) {
          const PString& x5501 = x3231->getString(5);
          ite5500 = x5501;
        } else {
          PString ite5505 = PString();
          if((x230==(3))) {
            const PString& x5506 = x3231->getString(6);
            ite5505 = x5506;
          } else {
            PString ite5510 = PString();
            if((x230==(4))) {
              const PString& x5511 = x3231->getString(7);
              ite5510 = x5511;
            } else {
              PString ite5515 = PString();
              if((x230==(5))) {
                const PString& x5516 = x3231->getString(8);
                ite5515 = x5516;
              } else {
                PString ite5520 = PString();
                if((x230==(6))) {
                  const PString& x5521 = x3231->getString(9);
                  ite5520 = x5521;
                } else {
                  PString ite5525 = PString();
                  if((x230==(7))) {
                    const PString& x5526 = x3231->getString(10);
                    ite5525 = x5526;
                  } else {
                    PString ite5530 = PString();
                    if((x230==(8))) {
                      const PString& x5531 = x3231->getString(11);
                      ite5530 = x5531;
                    } else {
                      PString ite5535 = PString();
                      if((x230==(9))) {
                        const PString& x5536 = x3231->getString(12);
                        ite5535 = x5536;
                      } else {
                        const PString& x5538 = x3231->getString(13);
                        ite5535 = x5538;
                      };
                      PString x5534 = ite5535;
                      ite5530 = x5534;
                    };
                    PString x5529 = ite5530;
                    ite5525 = x5529;
                  };
                  PString x5524 = ite5525;
                  ite5520 = x5524;
                };
                PString x5519 = ite5520;
                ite5515 = x5519;
              };
              PString x5514 = ite5515;
              ite5510 = x5514;
            };
            PString x5509 = ite5510;
            ite5505 = x5509;
          };
          PString x5504 = ite5505;
          ite5500 = x5504;
        };
        PString x5499 = ite5500;
        ite5495 = x5499;
      };
      PString ol_dist_info = ite5495;
      int s_quantity = x3231->getInt(3);
      int x353 = x243;
      x239[x353] = s_quantity;
      int x355 = x243;
      PString& x356 = idata[x355];
      char* x6753 = strstr(x356.data_, "original");
      int ite5746 = NULL;
      if((x6753!=(NULL))) {
        
        const PString& x358 = x3231->getString(17);
        char* x6759 = strstr(x358.data_, "original");
        int x5747 = (x6759!=(NULL));
        ite5746 = x5747;
      } else {
        ite5746 = 0;
      };
      int x5564 = ite5746;
      if(x5564) {
        int x361 = x243;
        x240[x361] = "B";
      } else {
        int x363 = x243;
        x240[x363] = "G";
      };
      x3231->update(3, (s_quantity-(ol_quantity)));
      if((s_quantity<=(ol_quantity))) {
        x3231->increase(3, 91);
      };
      int x372 = 0;
      if((ol_supply_w_id!=(x229))) {
        x372 = 1;
      };
      GenericEntry* x3283 = stockTbl.copyIntoPool(x3231);
      stockTblIdx0.updateCopy(x3283, &stockTblIdx0);
      double c_discount = x3200->getDouble(16);
      double w_tax = x3203->getDouble(8);
      double d_tax = x3206->getDouble(9);
      int x385 = x243;
      double x386 = x237[x385];
      double ol_amount = ((ol_quantity*(x386))*(((1.0+(w_tax))+(d_tax))))*((1.0-(c_discount)));
      int x394 = x243;
      x241[x394] = ol_amount;
      double x396 = x304;
      x304 = (x396+(ol_amount));
      int x399 = x243;
      GenericEntry* x402 = new GenericEntry(false_type(), o_id, x230, x229, (x399+(1)), ol_i_id, ol_supply_w_id, NULL, ol_quantity, ol_amount, ol_dist_info);
      orderLineTbl.insert_nocheck(x402);
      int x404 = x243;
      x243 = (x404+(1));
    };
  };
}
#include "TPCC.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  #ifndef NORESIZE
  cout << "Index Resizing warning disabled" << endl;
  #endif
  
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
  
  uint xactCounts[5] = {0, 0, 0, 0, 0};
  auto start = Now;
  for(size_t i = 0; i < numPrograms; ++i){
    Program *prg = tpcc.programs[i];
    switch(prg->id){
       case NEWORDER :
        {
           NewOrder& p = *(NewOrder *)prg;
           xactCounts[0]++;
           NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
           break;
        }
      case PAYMENTBYID :
        {
           PaymentById& p = *(PaymentById *) prg;
           xactCounts[1]++;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
           break;
        }
      case PAYMENTBYNAME :
        {
           PaymentByName& p = *(PaymentByName *) prg;
           xactCounts[1]++;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
           break;
        }
      case ORDERSTATUSBYID :
        {
           OrderStatusById &p = *(OrderStatusById *) prg;
           xactCounts[2]++;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
           break;
        }
      case ORDERSTATUSBYNAME :
        {
           OrderStatusByName &p = *(OrderStatusByName *) prg;
           xactCounts[2]++;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
           break;
        }
      case DELIVERY :
        {
           Delivery &p = *(Delivery *) prg;
           xactCounts[3]++;
           DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
           break;
        }
      case STOCKLEVEL :
       {
         StockLevel &p = *(StockLevel *) prg;
         xactCounts[4]++;
         StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
         break;
       }
       default : cerr << "UNKNOWN PROGRAM TYPE" << endl;
  
    }
  }
  auto end = Now;
  auto execTime = DurationMS(end - start);
  cout << "Total time = " << execTime << " ms" << endl;
  cout << "Total transactions = " << numPrograms << "   NewOrder = " <<  xactCounts[0]  << endl;
  cout << "TpmC = " << fixed <<  xactCounts[0] * 60000.0/execTime << endl;
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1)
    fout << "\nCPP-CGIMNORTX-" << numPrograms << ",";
  fout << fixed << xactCounts[0] * 60000.0/execTime << ",";
  fout.close();
  
  
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(districtTblIdx0, info);
  info << "\n}\n";
  info.close();
  
  
  #ifdef VERIFY_TPCC
      warehouseTblIdx0.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize);
  
      if (warehouseTblIdx0 == tpcc.wareRes) {
          cout << "Warehouse results are correct" << endl;
      } else {
          cerr << "Warehouse results INCORRECT!" << endl;
      }
      if (districtTblIdx0 == tpcc.distRes) {
          cout << "District results are correct" << endl;
      } else {
          cerr << "District results INCORRECT!" << endl;
      }
      if (customerTblIdx0 == tpcc.custRes) {
          cout << "Customer results are correct" << endl;
      } else {
          cerr << "Customer results INCORRECT!" << endl;
      }
      if (orderTblIdx0 == tpcc.ordRes) {
          cout << "Order results are correct" << endl;
      } else {
          cerr << "Order results INCORRECT!" << endl;
      }
      if (orderLineTblIdx0 == tpcc.ordLRes) {
          cout << "OrderLine results are correct" << endl;
      } else {
          cerr << "OrderLine results INCORRECT!" << endl;
      }
      if (newOrderTblIdx0 == tpcc.newOrdRes) {
          cout << "NewOrder results are correct" << endl;
      } else {
          cerr << "NewOrder results INCORRECT!" << endl;
      }
      if (itemTblIdx0 == tpcc.itemRes) {
          cout << "Item results are correct" << endl;
      } else {
          cerr << "Item results INCORRECT!" << endl;
      }
      if (stockTblIdx0 == tpcc.stockRes) {
          cout << "Stock results are correct" << endl;
      } else {
          cerr << "Stock results INCORRECT!" << endl;
      }
      if (historyTblIdx0 == tpcc.histRes) {
          cout << "History results are correct" << endl;
      } else {
          cerr << "History results INCORRECT!" << endl;
      }
  
  #endif
  
        
}
/* ----------- FUNCTIONS ----------- */
