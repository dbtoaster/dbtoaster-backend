#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SC_GENERATED 1
#define USING_GENERIC_ENTRY true
#define CONCURRENT 1

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
#include <valgrind/callgrind.h>
#include <iomanip>
#include <fstream>
#include <locale>

#include "TransactionManager.h"


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

uint failedOS = 0;
uint failedDel = 0;
uint failedNO = 0;

const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
const size_t itemTblSize = 100000 * 1.5;
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
     



struct GenericOps_3214 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(1)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(4)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if(e1.map.at(3) != e2.map.at(3) || e1.map.at(2) != e2.map.at(2) || e1.map.at(1) != e2.map.at(1) || e1.map.at(4) != e2.map.at(4))
       return 1;
    return 0;
  }
};
struct GenericOps_23 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3))
       return 1;
    return 0;
  }
};
struct GenericOps_321 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(1)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if(e1.map.at(3) != e2.map.at(3) || e1.map.at(2) != e2.map.at(2) || e1.map.at(1) != e2.map.at(1))
       return 1;
    return 0;
  }
};
struct GenericOps_236 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(6)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(6) != e2.map.at(6))
       return 1;
    return 0;
  }
};
struct GenericOps_123 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(1)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if(e1.map.at(1) != e2.map.at(1) || e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3))
       return 1;
    return 0;
  }
};
struct GenericOps_12345678 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(1)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(4)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(5)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(6)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(7)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(8)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if(e1.map.at(1) != e2.map.at(1) || e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(4) != e2.map.at(4) || e1.map.at(5) != e2.map.at(5) || e1.map.at(6) != e2.map.at(6) || e1.map.at(7) != e2.map.at(7) || e1.map.at(8) != e2.map.at(8))
       return 1;
    return 0;
  }
};
struct GenericOps_234 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(4)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { 
    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(4) != e2.map.at(4))
       return 1;
    return 0;
  }
};
struct GenericFixedRange_1f1t100002 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;  //Defined only for int fields
    h = h * 100001 + e.getInt(1) - 1; 
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_3f1t6_2f1t11_1f1t3001 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;  //Defined only for int fields
    h = h * 5 + e.getInt(3) - 1; 
    h = h * 10 + e.getInt(2) - 1; 
    h = h * 3000 + e.getInt(1) - 1; 
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_2f1t6_1f1t100001 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;  //Defined only for int fields
    h = h * 5 + e.getInt(2) - 1; 
    h = h * 100000 + e.getInt(1) - 1; 
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_1f1t6 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;  //Defined only for int fields
    h = h * 5 + e.getInt(1) - 1; 
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_2f1t6_1f1t11 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;  //Defined only for int fields
    h = h * 5 + e.getInt(2) - 1; 
    h = h * 10 + e.getInt(1) - 1; 
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericCmp_236_4 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(6)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(4)) + 0x9e3779b9 + (h<<6) + (h>>2));
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
typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_2f1t6_1f1t11, 50> districtTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,districtTblIdx0Type> districtTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_3f1t6_2f1t11_1f1t3001, 150000> customerTblIdx0Type;
typedef MedHeapIndex<GenericEntry, GenericOps_236, GenericCmp_236_4> customerTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,customerTblIdx0Type, customerTblIdx1Type> customerTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_1f1t100002, 100001> itemTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,itemTblIdx0Type> itemTblStoreType;

typedef CuckooIndex<GenericEntry, GenericOps_12345678> historyTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,historyTblIdx0Type> historyTblStoreType;

typedef CuckooIndex<GenericEntry, GenericOps_321> orderTblIdx0Type;
typedef MaxHeapIndex<GenericEntry, GenericOps_234, GenericCmp_234_1> orderTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;

typedef CuckooIndex<GenericEntry, GenericOps_321> newOrderTblIdx0Type;
typedef MinHeapIndex<GenericEntry, GenericOps_23, GenericCmp_23_1> newOrderTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_1f1t6, 5> warehouseTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,warehouseTblIdx0Type> warehouseTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_2f1t6_1f1t100001, 500000> stockTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,stockTblIdx0Type> stockTblStoreType;

typedef CuckooIndex<GenericEntry, GenericOps_3214> orderLineTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<GenericEntry, GenericOps_123> orderLineTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;

struct TPCC_Data {
  TPCC_Data(): 
  districtTbl(), districtTblIdx0(*(districtTblIdx0Type *)districtTbl.index[0]), 
  customerTbl(), customerTblIdx0(*(customerTblIdx0Type *)customerTbl.index[0]), customerTblIdx1(*(customerTblIdx1Type *)customerTbl.index[1]), 
  itemTbl(), itemTblIdx0(*(itemTblIdx0Type *)itemTbl.index[0]), 
  historyTbl(), historyTblIdx0(*(historyTblIdx0Type *)historyTbl.index[0]), 
  orderTbl(), orderTblIdx0(*(orderTblIdx0Type *)orderTbl.index[0]), orderTblIdx1(*(orderTblIdx1Type *)orderTbl.index[1]), 
  newOrderTbl(), newOrderTblIdx0(*(newOrderTblIdx0Type *)newOrderTbl.index[0]), newOrderTblIdx1(*(newOrderTblIdx1Type *)newOrderTbl.index[1]), 
  warehouseTbl(), warehouseTblIdx0(*(warehouseTblIdx0Type *)warehouseTbl.index[0]), 
  stockTbl(), stockTblIdx0(*(stockTblIdx0Type *)stockTbl.index[0]), 
  orderLineTbl(), orderLineTblIdx0(*(orderLineTblIdx0Type *)orderLineTbl.index[0]), orderLineTblIdx1(*(orderLineTblIdx1Type *)orderLineTbl.index[1]){}
  
  districtTblStoreType  districtTbl;  districtTblIdx0Type& districtTblIdx0;
  customerTblStoreType  customerTbl;  customerTblIdx0Type& customerTblIdx0;  customerTblIdx1Type& customerTblIdx1;
  itemTblStoreType  itemTbl;  itemTblIdx0Type& itemTblIdx0;
  historyTblStoreType  historyTbl;  historyTblIdx0Type& historyTblIdx0;
  orderTblStoreType  orderTbl;  orderTblIdx0Type& orderTblIdx0;  orderTblIdx1Type& orderTblIdx1;
  newOrderTblStoreType  newOrderTbl;  newOrderTblIdx0Type& newOrderTblIdx0;  newOrderTblIdx1Type& newOrderTblIdx1;
  warehouseTblStoreType  warehouseTbl;  warehouseTblIdx0Type& warehouseTblIdx0;
  stockTblStoreType  stockTbl;  stockTblIdx0Type& stockTblIdx0;
  orderLineTblStoreType  orderLineTbl;  orderLineTblIdx0Type& orderLineTblIdx0;  orderLineTblIdx1Type& orderLineTblIdx1;
};
struct ALIGN ThreadLocal { 
  
  uint8_t threadId;
  uint threadXactCounts[5];
  
  ThreadLocal(uint8_t tid, TPCC_Data& t): threadId(tid), 
  districtTbl(t.districtTbl), districtTblIdx0(t.districtTblIdx0), 
  customerTbl(t.customerTbl), customerTblIdx0(t.customerTblIdx0), customerTblIdx1(t.customerTblIdx1), 
  itemTbl(t.itemTbl), itemTblIdx0(t.itemTblIdx0), 
  historyTbl(t.historyTbl), historyTblIdx0(t.historyTblIdx0), 
  orderTbl(t.orderTbl), orderTblIdx0(t.orderTblIdx0), orderTblIdx1(t.orderTblIdx1), 
  newOrderTbl(t.newOrderTbl), newOrderTblIdx0(t.newOrderTblIdx0), newOrderTblIdx1(t.newOrderTblIdx1), 
  warehouseTbl(t.warehouseTbl), warehouseTblIdx0(t.warehouseTblIdx0), 
  stockTbl(t.stockTbl), stockTblIdx0(t.stockTblIdx0), 
  orderLineTbl(t.orderLineTbl), orderLineTblIdx0(t.orderLineTblIdx0), orderLineTblIdx1(t.orderLineTblIdx1){
     memset(threadXactCounts, 0, sizeof(uint)*5);
  }
  
  districtTblStoreType& districtTbl;  districtTblIdx0Type& districtTblIdx0;
  customerTblStoreType& customerTbl;  customerTblIdx0Type& customerTblIdx0;  customerTblIdx1Type& customerTblIdx1;
  itemTblStoreType& itemTbl;  itemTblIdx0Type& itemTblIdx0;
  historyTblStoreType& historyTbl;  historyTblIdx0Type& historyTblIdx0;
  orderTblStoreType& orderTbl;  orderTblIdx0Type& orderTblIdx0;  orderTblIdx1Type& orderTblIdx1;
  newOrderTblStoreType& newOrderTbl;  newOrderTblIdx0Type& newOrderTblIdx0;  newOrderTblIdx1Type& newOrderTblIdx1;
  warehouseTblStoreType& warehouseTbl;  warehouseTblIdx0Type& warehouseTblIdx0;
  stockTblStoreType& stockTbl;  stockTblIdx0Type& stockTblIdx0;
  orderLineTblStoreType& orderLineTbl;  orderLineTblIdx0Type& orderLineTblIdx0;  orderLineTblIdx1Type& orderLineTblIdx1;
  
  
  
  FORCE_INLINE TransactionReturnStatus NewOrderTx(Transaction& xact, double* amt266, PString* bg220, int c_id141, int d_id142, date datetime161, PString* iname116, int* itemid101, int o_ol_count74, double* price123, int* quantity189, int* stock204, int* supware91, int w_id95) {
    int x68 = 0;
    int x71 = 0;
    PString idata_$76[o_ol_count74];
    int x77 = 1;
    int x80 = 1;
    while(1) {
      
      int x85 = x68;
      int ite7364 = 0;
      if((x85<(o_ol_count74))) {
        
        int x87 = x77;
        int x7365 = x87;
        ite7364 = x7365;
      } else {
        ite7364 = 0;
      };
      int x7242 = ite7364;
      if (!(x7242)) break; 
      
      int x92 = x68;
      int x_$94 = supware91[x92];
      if((x_$94!=(w_id95))) {
        x80 = 0;
      };
      int x102 = x68;
      int x_$104 = itemid101[x102];
      GenericEntry y106(true_type(), 1, x_$104); GenericEntry* x106 = &y106;
      GenericEntry* x2780 = itemTblIdx0.get(x106, xact);
      if((x2780==(NULL))) {
        x77 = 0;
      } else {
        const PString& x_$115 = x2780->getString(3);
        int x117 = x68;
        iname116[x117] = x_$115;
        double x_$122 = x2780->getDouble(4);
        int x124 = x68;
        price123[x124] = x_$122;
        const PString& x_$129 = x2780->getString(5);
        int x130 = x68;
        idata_$76[x130] = x_$129;
      };
      int x135 = x68;
      x68 = (x135+(1));
    };
    int x298 = x77;
    if(x298) {
      GenericEntry y144(true_type(), 1, c_id141, 2, d_id142, 3, w_id95); GenericEntry* x144 = &y144;
      GenericEntry* x2800 = customerTblIdx0.get(x144, xact);
      GenericEntry y148(true_type(), 1, w_id95); GenericEntry* x148 = &y148;
      GenericEntry* x2803 = warehouseTblIdx0.get(x148, xact);
      GenericEntry y152(true_type(), 1, d_id142, 2, w_id95); GenericEntry* x152 = &y152;
      OperationReturnStatus stx3467;
      GenericEntry* x3467 =  districtTblIdx0.getForUpdate(x152, stx3467, xact);
      if(stx3467 == WW_VALUE) return WW_ABORT;
      int o_id_$156 = x3467->getInt(11);
      x3467->increase(11, 1);
      int x162 = x80;
      GenericEntry y164(false_type(), o_id_$156, d_id142, w_id95, c_id141, datetime161, -1, o_ol_count74, x162); GenericEntry* x164 = &y164;
      OperationReturnStatus st6279 = orderTbl.insert_nocheck(x164, xact);
      if(st6279 == WW_VALUE) return WW_ABORT;
      GenericEntry y167(false_type(), o_id_$156, d_id142, w_id95); GenericEntry* x167 = &y167;
      OperationReturnStatus st6282 = newOrderTbl.insert_nocheck(x167, xact);
      if(st6282 == WW_VALUE) return WW_ABORT;
      double x169 = 0.0;
      x68 = 0;
      while(1) {
        
        int x175 = x68;
        if (!((x175<(o_ol_count74)))) break; 
        
        int x179 = x68;
        int x_$181 = supware91[x179];
        int x184 = x68;
        int x_$186 = itemid101[x184];
        int x190 = x68;
        int x_$192 = quantity189[x190];
        GenericEntry y194(true_type(), 1, x_$186, 2, x_$181); GenericEntry* x194 = &y194;
        OperationReturnStatus stx3491;
        GenericEntry* x3491 =  stockTblIdx0.getForUpdate(x194, stx3491, xact);
        if(stx3491 == WW_VALUE) return WW_ABORT;
        const PString& ol_dist_info_$199 = x3491->getString((3+(d_id142)));
        int s_quantity_$201 = x3491->getInt(3);
        int x205 = x68;
        stock204[x205] = s_quantity_$201;
        int x209 = x68;
        PString& x_$211 = idata_$76[x209];
        char* x8372 = strstr(x_$211.data_, "original");
        int ite7438 = 0;
        if((x8372!=(NULL))) {
          
          const PString& x_$214 = x3491->getString(17);
          char* x8378 = strstr(x_$214.data_, "original");
          int x7439 = (x8378!=(NULL));
          ite7438 = x7439;
        } else {
          ite7438 = 0;
        };
        int x7311 = ite7438;
        if(x7311) {
          int x221 = x68;
          bg220[x221].data_[0] = 'B';
        } else {
          int x225 = x68;
          bg220[x225].data_[0] = 'G';
        };
        x3491->update(3, (s_quantity_$201-(x_$192)));
        if((s_quantity_$201<=(x_$192))) {
          x3491->increase(3, 91);
        };
        int x233 = 0;
        if((x_$181!=(w_id95))) {
          x233 = 1;
        };
        double c_discount_$241 = x2800->getDouble(16);
        double w_tax_$245 = x2803->getDouble(8);
        double d_tax_$249 = x3467->getDouble(9);
        int x254 = x68;
        double x_$256 = price123[x254];
        double sch_$262 = ((x_$192*(x_$256))*(((1.0+(w_tax_$245))+(d_tax_$249))))*((1.0-(c_discount_$241)));
        int x267 = x68;
        amt266[x267] = sch_$262;
        double x271 = x169;
        x169 = (x271+(sch_$262));
        int x276 = x68;
        GenericEntry y279(false_type(), o_id_$156, d_id142, w_id95, (x276+(1)), x_$186, x_$181, NULL, x_$192, sch_$262, ol_dist_info_$199); GenericEntry* x279 = &y279;
        OperationReturnStatus st6343 = orderLineTbl.insert_nocheck(x279, xact);
        if(st6343 == WW_VALUE) return WW_ABORT;
        int x283 = x68;
        x68 = (x283+(1));
      };
    } else {
      int x287 = 0;
      int x290 = 0;
      int x295 = x290;
      x287 = (1+(x295));
    };
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus PaymentTx(Transaction& xact, int c_by_name315, int c_d_id317, int c_id323, PString c_last_input319, int c_w_id318, int d_id308, date datetime336, double h_amount305, int w_id300) {
    GenericEntry y302(true_type(), 1, w_id300); GenericEntry* x302 = &y302;
    OperationReturnStatus stx3676;
    GenericEntry* x3676 =  warehouseTblIdx0.getForUpdate(x302, stx3676, xact);
    if(stx3676 == WW_VALUE) return WW_ABORT;
    x3676->increase(9, h_amount305);
    GenericEntry y310(true_type(), 1, d_id308, 2, w_id300); GenericEntry* x310 = &y310;
    OperationReturnStatus stx3681;
    GenericEntry* x3681 =  districtTblIdx0.getForUpdate(x310, stx3681, xact);
    if(stx3681 == WW_VALUE) return WW_ABORT;
    x3681->increase(10, h_amount305);
    GenericEntry* ite7631 = 0;
    if((c_by_name315>(0))) {
      GenericEntry y7633(true_type(), 2, c_d_id317, 3, c_w_id318, 6, c_last_input319); GenericEntry* x7633 = &y7633;
      OperationReturnStatus stx7634;
      GenericEntry* x7634 =  customerTblIdx1.getForUpdate(x7633, stx7634, xact);
      if(stx7634 == WW_VALUE) return WW_ABORT;
      ite7631 = x7634;
    } else {
      GenericEntry y7637(true_type(), 1, c_id323, 2, c_d_id317, 3, c_w_id318); GenericEntry* x7637 = &y7637;
      OperationReturnStatus stx7638;
      GenericEntry* x7638 =  customerTblIdx0.getForUpdate(x7637, stx7638, xact);
      if(stx7638 == WW_VALUE) return WW_ABORT;
      ite7631 = x7638;
    };
    GenericEntry* customerEntry_$328 = ite7631;
    const PString& c_data_$330 = customerEntry_$328->getString(21);
    const PString& x_$332 = customerEntry_$328->getString(14);
    char* x8583 = strstr(x_$332.data_, "BC");
    if((x8583!=(NULL))) {
      int x_$335 = customerEntry_$328->getInt(1);
      PString x1782 = PString(500);
      x1782.append(x_$335);
      x1782.append(' ');
      x1782.append(c_d_id317);
      x1782.append(' ');
      x1782.append(c_w_id318);
      x1782.append(' ');
      x1782.append(d_id308);
      x1782.append(' ');
      x1782.append(w_id300);
      x1782.append(' ');
      x1782.append('$');
      x1782.append(h_amount305);
      x1782.append(' ');
      x1782.appendDate(datetime336);
      x1782.append(' ');
      x1782.append('|');
      x1782.append(' ');
      x1782.append(c_data_$330.data_, 500);
      customerEntry_$328->increase(17, h_amount305);
      customerEntry_$328->update(21, x1782);
    } else {
      customerEntry_$328->increase(17, h_amount305);
    };
    const PString& w_name_$346 = x3676->getString(2);
    const PString& d_name_$348 = x3681->getString(3);
    PString x1808 = PString(24);
    x1808.append(w_name_$346.data_, 10);
    x1808.append("    ", 4);
    x1808.append(d_name_$348.data_, 10);
    int x_$353 = customerEntry_$328->getInt(1);
    GenericEntry y355(false_type(), x_$353, c_d_id317, c_w_id318, d_id308, w_id300, datetime336, h_amount305, x1808); GenericEntry* x355 = &y355;
    OperationReturnStatus st6404 = historyTbl.insert_nocheck(x355, xact);
    if(st6404 == WW_VALUE) return WW_ABORT;
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus OrderStatusTx(Transaction& xact, int c_by_name358, int c_id366, PString c_last362, int d_id360, int w_id361) {
    GenericEntry* ite7737 = 0;
    if((c_by_name358>(0))) {
      GenericEntry y7739(true_type(), 2, d_id360, 3, w_id361, 6, c_last362); GenericEntry* x7739 = &y7739;
      GenericEntry* x7740 = customerTblIdx1.get(x7739, xact);
      ite7737 = x7740;
    } else {
      GenericEntry y7743(true_type(), 1, c_id366, 2, d_id360, 3, w_id361); GenericEntry* x7743 = &y7743;
      GenericEntry* x7744 = customerTblIdx0.get(x7743, xact);
      ite7737 = x7744;
    };
    GenericEntry* customerEntry_$371 = ite7737;
    int found_c_id_$373 = customerEntry_$371->getInt(3);
    GenericEntry y375(true_type(), 2, d_id360, 3, w_id361, 4, found_c_id_$373); GenericEntry* x375 = &y375;
    GenericEntry* x3142 = orderTblIdx1.get(x375, xact);
    int ite7753 = 0;
    if((x3142==(NULL))) {
      int x7754 = 0;
      int x7755 = 0;
      int x7756 = x7755;
      x7754 = (1+(x7756));
      ite7753 = 0;
    } else {
      int x7760 = x3142->getInt(1);
      GenericEntry y7765(true_type(), 1, x7760, 2, d_id360, 3, w_id361); GenericEntry* x7765 = &y7765;
      OperationReturnStatus st7766 = orderLineTblIdx1.sliceNoUpdate(x7765, [&](GenericEntry* orderLineEntry_$395) -> TransactionReturnStatus {
        int x396 = 1;
        return SUCCESS;
      }, xact);
      if(st7766 == WW_VALUE) return WW_ABORT;
      ite7753 = 1;
    };
    int x401 = ite7753;
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus DeliveryTx(Transaction& xact, date datetime451, int o_carrier_id439, int w_id413) {
    int orderIDs_$403[10];
    int x404 = 1;
    while(1) {
      
      int x409 = x404;
      if (!((x409<=(10)))) break; 
      
      int x414 = x404;
      GenericEntry y416(true_type(), 2, x414, 3, w_id413); GenericEntry* x416 = &y416;
      OperationReturnStatus stx3885;
      GenericEntry* x3885 =  newOrderTblIdx1.getForUpdate(x416, stx3885, xact);
      if(stx3885 == WW_VALUE) return WW_ABORT;
      if((x3885!=(NULL))) {
        int no_o_id_$423 = x3885->getInt(1);
        int x426 = x404;
        orderIDs_$403[(x426-(1))] = no_o_id_$423;
        newOrderTbl.del(x3885);
        int x432 = x404;
        GenericEntry y434(true_type(), 1, no_o_id_$423, 2, x432, 3, w_id413); GenericEntry* x434 = &y434;
        OperationReturnStatus stx3896;
        GenericEntry* x3896 =  orderTblIdx0.getForUpdate(x434, stx3896, xact);
        if(stx3896 == WW_VALUE) return WW_ABORT;
        int c_id_$438 = x3896->getInt(4);
        x3896->update(6, o_carrier_id439);
        double x442 = 0.0;
        int x447 = x404;
        GenericEntry y449(true_type(), 1, no_o_id_$423, 2, x447, 3, w_id413); GenericEntry* x449 = &y449;
        OperationReturnStatus st3220 = orderLineTblIdx1.slice(x449, [&](GenericEntry* orderLineEntry_$450) -> TransactionReturnStatus {
          orderLineEntry_$450->update(7, datetime451);
          double x_$456 = orderLineEntry_$450->getDouble(9);
          double x457 = x442;
          x442 = (x457+(x_$456));
          return SUCCESS;
        }, xact);
        if(st3220 == WW_VALUE) return WW_ABORT;
        int x465 = x404;
        GenericEntry y467(true_type(), 1, c_id_$438, 2, x465, 3, w_id413); GenericEntry* x467 = &y467;
        OperationReturnStatus stx3918;
        GenericEntry* x3918 =  customerTblIdx0.getForUpdate(x467, stx3918, xact);
        if(stx3918 == WW_VALUE) return WW_ABORT;
        double x472 = x442;
        x3918->increase(17, x472);
        x3918->increase(20, 1);
      } else {
        int x476 = 0;
        int x479 = 0;
        int x484 = x479;
        x476 = (1+(x484));
        int x489 = x404;
        orderIDs_$403[(x489-(1))] = 0;
      };
      int x495 = x404;
      x404 = (x495+(1));
    };
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus StockLevelTx(Transaction& xact, int d_id499, int threshold532, int w_id500) {
    GenericEntry y502(true_type(), 1, d_id499, 2, w_id500); GenericEntry* x502 = &y502;
    GenericEntry* x3301 = districtTblIdx0.get(x502, xact);
    int o_id_$506 = x3301->getInt(11);
    int x508 = (o_id_$506-(20));
    unordered_set<int> unique_ol_i_id_$513({}); //setApply1
    while(1) {
      
      int x516 = x508;
      if (!((x516<(o_id_$506)))) break; 
      
      int x520 = x508;
      GenericEntry y522(true_type(), 1, x520, 2, d_id499, 3, w_id500); GenericEntry* x522 = &y522;
      OperationReturnStatus st4407 = orderLineTblIdx1.sliceNoUpdate(x522, [&](GenericEntry* orderLineEntry_$523) -> TransactionReturnStatus {
        int ol_i_id_$525 = orderLineEntry_$523->getInt(5);
        GenericEntry y527(true_type(), 1, ol_i_id_$525, 2, w_id500); GenericEntry* x527 = &y527;
        GenericEntry* x3315 = stockTblIdx0.get(x527, xact);
        int s_quantity_$531 = x3315->getInt(3);
        if((s_quantity_$531<(threshold532))) {
          unique_ol_i_id_$513.insert(ol_i_id_$525);
        };
        return SUCCESS;
      }, xact);
      if(st4407 == WW_VALUE) return WW_ABORT;
      int x540 = x508;
      x508 = (x540+(1));
    };
    clearTempMem();
    return SUCCESS;
  }
  
   TransactionReturnStatus runProgram(Program* prg);
};

TransactionManager xactManager;
TransactionManager& Transaction::tm(xactManager);
uint globalXactCounts[5];
uint8_t prgId7to5[] = {0, 1, 1, 2, 2, 3, 4};

volatile bool isReady[numThreads];
volatile bool startExecution, hasFinished;


TPCC_Data orig;
#ifdef VERIFY_CONC
   TPCC_Data res;
#endif
 

#include "TPCC.h"

TPCCDataGen tpcc;

TransactionReturnStatus ThreadLocal::runProgram(Program* prg) {
  TransactionReturnStatus ret = SUCCESS;
  switch (prg->id) {
    case NEWORDER:
    {
      NewOrder& p = *(NewOrder *) prg;
      ret = NewOrderTx(prg->xact, p.amt, p.bg, p.c_id, p.d_id, p.datetime, p.iname, p.itemid, p.o_ol_cnt, p.price, p.quantity, p.stock, p.supware, p.w_id);
      break;
    }
    case PAYMENTBYID:
    {
      PaymentById& p = *(PaymentById *) prg;
      ret = PaymentTx(prg->xact, 0, p.c_d_id, p.c_id, nullptr, p.c_w_id, p.d_id, p.datetime, p.h_amount, p.w_id);
      break;
    }
    case PAYMENTBYNAME:
    {
      PaymentByName& p = *(PaymentByName *) prg;
      ret = PaymentTx(prg->xact, 1, p.c_d_id, -1, p.c_last_input, p.c_w_id, p.d_id, p.datetime, p.h_amount, p.w_id);
      break;
    }
    case ORDERSTATUSBYID:
    {
      OrderStatusById &p = *(OrderStatusById *) prg;
      ret = OrderStatusTx(prg->xact, 0, p.c_id, nullptr, p.d_id, p.w_id);
      break;
    }
    case ORDERSTATUSBYNAME:
    {
      OrderStatusByName &p = *(OrderStatusByName *) prg;
      ret = OrderStatusTx(prg->xact, 1, -1, p.c_last, p.d_id, p.w_id);
      break;
    }
    case DELIVERY:
    {
      Delivery &p = *(Delivery *) prg;
      ret = DeliveryTx(prg->xact, p.datetime, p.o_carrier_id, p.w_id);
      break;
    }
    case STOCKLEVEL:
    {
      StockLevel &p = *(StockLevel *) prg;
      ret = StockLevelTx(prg->xact, p.d_id, p.threshold, p.w_id);
      break;
    }
    default: cerr << "UNKNOWN PROGRAM TYPE" << endl;

  }
  return ret;
}
      
std::atomic<uint> PC(0);
void threadFunction(uint8_t thread_id, ThreadLocal* tl) {
    setAffinity(thread_id);
    //    setSched(SCHED_FIFO);


  isReady[thread_id] = true;
  uint pid = PC++;
  Program* p;
  TransactionReturnStatus st;
  while (!startExecution);
  const uint failedProgramSize = 32;
  Program * failedPrograms[failedProgramSize];
  uint head = 0, tail = 0;
  bool full = false;
  p = tpcc.programs[pid];
  while (!hasFinished) {

    xactManager.begin(p->xact, thread_id);

    st = tl->runProgram(p);

    if (st != SUCCESS) {
      xactManager.rollback(p->xact, thread_id);
      if (!full && p->xact.failedBecauseOf != nullptr) {
        failedPrograms[tail++] = p;
        if (tail == failedProgramSize)
          tail = 0;
        if (head == tail)
          full = true;
        pid = PC++;
        if (pid >= numPrograms)
          break;
        p = tpcc.programs[pid];
      }
    } else {
      if (xactManager.validateAndCommit(p->xact, thread_id)) {   //rollback happens inside function if it fails
        tl->threadXactCounts[prgId7to5[p->id]]++;
        if (head != tail || full) {
          p = failedPrograms[head];
          if (p->xact.failedBecauseOf->commitTS != initCommitTS) {
            head++;
            full = false;
            if (head == failedProgramSize)
              head = 0;
            continue;
          }
        }
        pid = PC++;
        if(pid >= numPrograms)
          break;
        p = tpcc.programs[pid];
      }
    }
  }
  hasFinished = true;
}

       
/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  setAffinity(-1);
  #ifndef NORESIZE
  cout << "Index Resizing warning disabled" << endl;
  #endif
  
  cout  << "NumThreads = " << numThreads << endl;
  
  tpcc.loadPrograms();
  
  Transaction t0;
  xactManager.begin(t0, 0);
  tpcc.loadWare(t0);
  tpcc.loadDist(t0);
  tpcc.loadCust(t0);
  tpcc.loadItem(t0);
  tpcc.loadNewOrd(t0);
  tpcc.loadOrders(t0);
  tpcc.loadOrdLine(t0);
  tpcc.loadHist(t0);
  tpcc.loadStocks(t0);
  xactManager.commit(t0, 0);
  cout.imbue(std::locale(""));
  
  memset(globalXactCounts, 0, 5 * sizeof(uint));
  memset(xactManager.activeXactStartTS, 0xff, sizeof(xactManager.activeXactStartTS[0]) * numThreads);
  ThreadLocal *tls[numThreads];
  Timepoint startTime, endTime;
  std::thread workers[numThreads];
  
  for (uint8_t i = 0; i < numThreads; ++i) {
      tls[i] = new ThreadLocal(i, orig);
      workers[i] = std::thread(threadFunction, i, tls[i]);
  }
  bool all_ready = true;
  //check if all worker threads are ready. Execution can be started once all threads finish startup procedure
  while (true) {
      for (uint8_t i = 0; i < numThreads; ++i) {
          if (isReady[i] == false) {
              all_ready = false;
              break;
          }
      }
      if (all_ready) {
          startTime = Now;
          startExecution = true;
          break;
      }
      all_ready = true;
  }
  
  for (uint8_t i = 0; i < numThreads; ++i) {
      workers[i].join();
  }
  endTime = Now;
  auto execTime = DurationMS(endTime - startTime);
  
  for(uint i = 0; i < numThreads;  ++i) {
     for(uint j = 0; j < 5; ++j) {
        globalXactCounts[j] += tls[i]->threadXactCounts[j];
      }
  }
  
  cout << "Failed NO = " << failedNO << endl;
  cout << "Failed Del = " << failedDel << endl;
  cout << "Failed OS = " << failedOS << endl;
  cout << "Total time = " << execTime << " ms" << endl;
  cout << "Total transactions = " << numPrograms << "   NewOrder = " <<  globalXactCounts[0]  << endl;
  cout << "TpmC = " << fixed <<  (globalXactCounts[0])* 60000.0/execTime << endl;
  
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1) {
    fout << "\nCPP-ABDFGILNORXY-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << globalXactCounts[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  /*
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT(orig.newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.itemTblIdx0, info);
  info << "\n}\n";
  info.close();
  */
  
  #ifdef VERIFY_CONC
  ThreadLocal ver(-1, res);
  std::sort(tpcc.programs, tpcc.programs + numPrograms, [](const Program* a, const Program * b) {
    return a->xact.commitTS < b->xact.commitTS;
  });
  xactManager.committedXactsTail = nullptr;
  for (uint i = 0; i < numPrograms; ++i) {
    Program* p = tpcc.programs[i];
    if (p->xact.commitTS == initCommitTS)
      break;
    p->xact.reset();
    TransactionReturnStatus st;
    xactManager.begin(p->xact, 0);
    st = ver.runProgram(p);
    assert(st == SUCCESS);
    bool st2 = xactManager.validateAndCommit(p->xact, 0);
    assert(st2);
  }
  
  if (orig.warehouseTblIdx0 == res.warehouseTblIdx0) {
    cout << "Warehouse results are same as serial version" << endl;
  } else {
    cerr << "Warehouse results INCORRECT!" << endl;
  }
  if (orig.districtTblIdx0 == res.districtTblIdx0) {
    cout << "District results are same as serial version" << endl;
  } else {
    cerr << "District results INCORRECT!" << endl;
  }
  if (orig.customerTblIdx0 == res.customerTblIdx0) {
    cout << "Customer results are same as serial version" << endl;
  } else {
    cerr << "Customer results INCORRECT!" << endl;
  }
  if (orig.orderTblIdx0 == res.orderTblIdx0) {
    cout << "Order results are same as serial version" << endl;
  } else {
    cerr << "Order results INCORRECT!" << endl;
  }
  if (orig.orderLineTblIdx0 == res.orderLineTblIdx0) {
    cout << "OrderLine results are same as serial version" << endl;
  } else {
    cerr << "OrderLine results INCORRECT!" << endl;
  }
  if (orig.newOrderTblIdx0 == res.newOrderTblIdx0) {
    cout << "NewOrder results are same as serial version" << endl;
  } else {
    cerr << "NewOrder results INCORRECT!" << endl;
  }
  if (orig.itemTblIdx0 == res.itemTblIdx0) {
    cout << "Item results are same as serial version" << endl;
  } else {
    cerr << "Item results INCORRECT!" << endl;
  }
  if (orig.stockTblIdx0 == res.stockTblIdx0) {
    cout << "Stock results are same as serial version" << endl;
  } else {
    cerr << "Stock results INCORRECT!" << endl;
  }
  if (orig.historyTblIdx0 == res.historyTblIdx0) {
    cout << "History results are same as serial version" << endl;
  } else {
    cerr << "History results INCORRECT!" << endl;
  }
  #endif
  #ifdef VERIFY_TPCC
  /*
      warehouseTblIdx0.resize_(warehouseTblSize); tpcc.wareRes.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize); tpcc.distRes.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize); tpcc.custRes.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize); tpcc.ordRes.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize); tpcc.newOrdRes.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize); tpcc.ordLRes.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize); tpcc.itemRes.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize); tpcc.stockRes.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize); tpcc.histRes.resize_(historyTblSize);
  */
      if (orig.warehouseTblIdx0 == tpcc.wareRes) {
          cout << "Warehouse results are correct" << endl;
      } else {
          cerr << "Warehouse results INCORRECT!" << endl;
      }
      if (orig.districtTblIdx0 == tpcc.distRes) {
          cout << "District results are correct" << endl;
      } else {
          cerr << "District results INCORRECT!" << endl;
      }
      if (orig.customerTblIdx0 == tpcc.custRes) {
          cout << "Customer results are correct" << endl;
      } else {
          cerr << "Customer results INCORRECT!" << endl;
      }
      if (orig.orderTblIdx0 == tpcc.ordRes) {
          cout << "Order results are correct" << endl;
      } else {
          cerr << "Order results INCORRECT!" << endl;
      }
      if (orig.orderLineTblIdx0 == tpcc.ordLRes) {
          cout << "OrderLine results are correct" << endl;
      } else {
          cerr << "OrderLine results INCORRECT!" << endl;
      }
      if (orig.newOrderTblIdx0 == tpcc.newOrdRes) {
          cout << "NewOrder results are correct" << endl;
      } else {
          cerr << "NewOrder results INCORRECT!" << endl;
      }
      if (orig.itemTblIdx0 == tpcc.itemRes) {
          cout << "Item results are correct" << endl;
      } else {
          cerr << "Item results INCORRECT!" << endl;
      }
      if (orig.stockTblIdx0 == tpcc.stockRes) {
          cout << "Stock results are correct" << endl;
      } else {
          cerr << "Stock results INCORRECT!" << endl;
      }
      if (orig.historyTblIdx0 == tpcc.histRes) {
          cout << "History results are correct" << endl;
      } else {
          cerr << "History results INCORRECT!" << endl;
      }
  
  #endif
  
        
}
