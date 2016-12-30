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

#undef int

typedef HashIndex<GenericEntry, char, GenericOps, 1> newOrderTblIdx0Type;
typedef TreeIndex<GenericEntry, char, GenericOps, GenericCmp, 0> newOrderTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>,
   TreeIndex<GenericEntry, char, GenericOps, GenericCmp, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblStoreType& x805 = newOrderTbl;
newOrderTblIdx0Type& x806 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x807 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 0> historyTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblStoreType& x812 = historyTbl;
historyTblIdx0Type& x813 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 1> warehouseTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblStoreType& x817 = warehouseTbl;
warehouseTblIdx0Type& x818 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 1> itemTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblStoreType& x820 = itemTbl;
itemTblIdx0Type& x821 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 1> orderTblIdx0Type;
typedef TreeIndex<GenericEntry, char, GenericOps, GenericCmp, 1> orderTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>,
   TreeIndex<GenericEntry, char, GenericOps, GenericCmp, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblStoreType& x827 = orderTbl;
orderTblIdx0Type& x828 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x829 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 1> districtTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblStoreType& x834 = districtTbl;
districtTblIdx0Type& x835 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 1> orderLineTblIdx0Type;
typedef HashIndex<GenericEntry, char, GenericOps, 0> orderLineTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>,
   HashIndex<GenericEntry, char, GenericOps, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblStoreType& x839 = orderLineTbl;
orderLineTblIdx0Type& x840 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x841 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 1> customerTblIdx0Type;
typedef HashIndex<GenericEntry, char, GenericOps, 0> customerTblIdx1Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>,
   HashIndex<GenericEntry, char, GenericOps, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblStoreType& x845 = customerTbl;
customerTblIdx0Type& x846 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x847 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef HashIndex<GenericEntry, char, GenericOps, 1> stockTblIdx0Type;
typedef MultiHashMap<GenericEntry, char,
   HashIndex<GenericEntry, char, GenericOps, 1>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblStoreType& x849 = stockTbl;
stockTblIdx0Type& x850 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];




void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    GenericEntry* x29 = new GenericEntry(true_type(), 2, x27, 3, x12);
    GenericEntry* x1700 = x805.getCopyDependent(x29, 1);
    if((x1700!=(NULL))) {
      int no_o_id = x1700->getInt(1);
      int x36 = x18;
      orderIDs[(x36-(1))] = no_o_id;
      x805.delCopyDependent(x1700);
      int x41 = x18;
      GenericEntry* x43 = new GenericEntry(true_type(), 1, no_o_id, 2, x41, 3, x12);
      GenericEntry* x1712 = x827.getCopyDependent(x43, 0);
      int c_id = x1712->getInt(4);
      x1712->update(6, x13);
      x827.updateCopyDependent(x1712);
      double x51 = 0.0;
      int x53 = x18;
      GenericEntry* x55 = new GenericEntry(true_type(), 1, no_o_id, 2, x53, 3, x12);
      x839.sliceCopyDependent(1, x55, ([&](const GenericEntry&  sliceVar) {
        GenericEntry* orderLineEntry = const_cast<GenericEntry*>(&sliceVar);
        orderLineEntry->update(7, x11);
        double x58 = x51;
        double x59 = orderLineEntry->getDouble(9);
        x51 = (x58+(x59));
        x839.updateCopyDependent(orderLineEntry);
      
      }));
      int x66 = x18;
      GenericEntry* x68 = new GenericEntry(true_type(), 1, c_id, 2, x66, 3, x12);
      GenericEntry* x1732 = x845.getCopyDependent(x68, 0);
      double x70 = x51;
      x1732->increase(17, x70);
      x1732->increase(20, 1);
      x845.updateCopyDependent(x1732);
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
  GenericEntry* x1802 = x834.getCopyDependent(x90, 0);
  int o_id = x1802->getInt(11);
  int x97 = (o_id-(20));
  unordered_set<int> unique_ol_i_id;
  while(1) {
    
    int x101 = x97;
    if (!((x101<(o_id)))) break; 
    
    int x103 = x97;
    GenericEntry* x105 = new GenericEntry(true_type(), 1, x103, 2, x86, 3, x85);
    x839.sliceCopyDependent(1, x105, ([&](const GenericEntry&  sliceVar) {
      GenericEntry* orderLineEntry = const_cast<GenericEntry*>(&sliceVar);
      int ol_i_id = orderLineEntry->getInt(5);
      GenericEntry* x111 = new GenericEntry(true_type(), 1, ol_i_id, 2, x85);
      GenericEntry* x1815 = x849.getCopyDependent(x111, 0);
      int s_quantity = x1815->getInt(3);
      if((s_quantity<(x87))) {
        unique_ol_i_id.insert(ol_i_id);
      };
    
    }));
    int x120 = x97;
    x97 = (x120+(1));
  };
}
void OrderStatusTx(int x126, date x127, int x128, int x129, int x130, int x131, int x132, PString x133) {
  GenericEntry* ite3609 = NULL;
  if((x131>(0))) {
    vector<GenericEntry*> x3610;
    GenericEntry* x3615 = new GenericEntry(true_type(), 2, x130, 3, x129, 6, x133);
    x845.sliceCopyDependent(1, x3615, ([&](const GenericEntry&  sliceVar) {
      GenericEntry* custEntry = const_cast<GenericEntry*>(&sliceVar);
      x3610.push_back(custEntry);
    
    }));
    int x3617 = x3610.size();
    int x3619 = (x3617/(2));
    int x3627 = x3610.size();
    if(((x3627%(2))==(0))) {
      int x152 = x3619;
      x3619 = (x152-(1));
    };
    sort(x3610.begin(), x3610.end(), ([&](GenericEntry* c1, GenericEntry* c2) {
      
      PString x158 = c1->getString(4);
      PString x159 = c2->getString(4);
      return ((strcmpi(x158.data_, x159.data_))<(0)); 
    }));
    int x3635 = x3619;
    GenericEntry* x3636 = x3610[x3635];
    ite3609 = x3636;
  } else {
    
    GenericEntry* x3639 = new GenericEntry(true_type(), 1, x132, 2, x130, 3, x129);
    GenericEntry* x3640 = x845.getCopyDependent(x3639, 0);
    ite3609 = x3640;
  };
  GenericEntry* customerEntry = ite3609;
  int found_c_id = customerEntry->getInt(3);
  GenericEntry* x179 = new GenericEntry(true_type(), 2, x130, 3, x129, 4, found_c_id);
  GenericEntry* x1898 = x827.getCopyDependent(x179, 1);
  int x184 = 0;
  int x186 = x1898->getInt(1);
  x184 = x186;
}
void PaymentTx(int x188, date x189, int x190, int x191, int x192, int x193, int x194, int x195, int x196, PString x197, double x198) {
  GenericEntry* x201 = new GenericEntry(true_type(), 1, x191);
  GenericEntry* x1950 = x817.getCopyDependent(x201, 0);
  x1950->increase(9, x198);
  x817.updateCopyDependent(x1950);
  GenericEntry* x208 = new GenericEntry(true_type(), 1, x192, 2, x191);
  GenericEntry* x1955 = x834.getCopyDependent(x208, 0);
  x1955->increase(10, x198);
  x834.updateCopyDependent(x1955);
  GenericEntry* ite3705 = NULL;
  if((x193>(0))) {
    vector<GenericEntry*> x3706;
    GenericEntry* x3711 = new GenericEntry(true_type(), 2, x195, 3, x194, 6, x197);
    x845.sliceCopyDependent(1, x3711, ([&](const GenericEntry&  sliceVar) {
      GenericEntry* custEntry = const_cast<GenericEntry*>(&sliceVar);
      x3706.push_back(custEntry);
    
    }));
    int x3713 = x3706.size();
    int x3715 = (x3713/(2));
    int x3723 = x3706.size();
    if(((x3723%(2))==(0))) {
      int x230 = x3715;
      x3715 = (x230-(1));
    };
    sort(x3706.begin(), x3706.end(), ([&](GenericEntry* c1, GenericEntry* c2) {
      
      PString x236 = c1->getString(4);
      PString x237 = c2->getString(4);
      return ((strcmpi(x236.data_, x237.data_))<(0)); 
    }));
    int x3731 = x3715;
    GenericEntry* x3732 = x3706[x3731];
    ite3705 = x3732;
  } else {
    
    GenericEntry* x3735 = new GenericEntry(true_type(), 1, x196, 2, x195, 3, x194);
    GenericEntry* x3736 = x845.getCopyDependent(x3735, 0);
    ite3705 = x3736;
  };
  GenericEntry* customerEntry = ite3705;
  PString c_data = customerEntry->getString(21);
  PString x250 = customerEntry->getString(14);
  char* x5017 = strstr(x250.data_, "BC");
  if((x5017!=(NULL))) {
    int x253 = customerEntry->getInt(1);
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x253, x195, x194, x192, x191, x198, IntToStrdate(x189), c_data.data_);
    customerEntry->increase(17, x198);
    customerEntry->update(21, c_new_data);
  } else {
    
    customerEntry->increase(17, x198);
  };
  x845.updateCopyDependent(customerEntry);
  PString w_name = x1950->getString(2);
  PString d_name = x1955->getString(3);
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", w_name.data_, d_name.data_);
  int x268 = customerEntry->getInt(1);
  GenericEntry* x270 = new GenericEntry(false_type(), x268, x195, x194, x192, x191, x189, x198, h_data);
  x812.add(x270);
}
void NewOrderTx(int x272, date x273, int x274, int x275, int x276, int x277, int x278, int x279, int* x280, int* x281, int* x282, double* x283, PString* x284, int* x285, PString* x286, double* x287) {
  int x289 = 0;
  int x292 = 0;
  PString idata[x278];
  int x297 = 1;
  while(1) {
    
    int x299 = x289;
    int ite4005 = 0;
    if((x299<(x278))) {
      
      int x301 = x297;
      int x4006 = x301;
      ite4005 = x4006;
    } else {
      
      ite4005 = 0;
    };
    int x3831 = ite4005;
    if (!(x3831)) break; 
    
    int x304 = x289;
    int x305 = x280[x304];
    GenericEntry* x307 = new GenericEntry(true_type(), 1, x305);
    GenericEntry* x2085 = x820.getCopyDependent(x307, 0);
    if((x2085==(NULL))) {
      x297 = 0;
    } else {
      
      int x312 = x289;
      PString x313 = x2085->getString(3);
      x284[x312] = x313;
      int x315 = x289;
      double x316 = x2085->getDouble(4);
      x283[x315] = x316;
      int x318 = x289;
      PString x319 = x2085->getString(5);
      idata[x318] = x319;
    };
    int x322 = x289;
    x289 = (x322+(1));
  };
  int x326 = x297;
  if(x326) {
    GenericEntry* x329 = new GenericEntry(true_type(), 1, x277, 2, x276, 3, x275);
    GenericEntry* x2106 = x845.getCopyDependent(x329, 0);
    GenericEntry* x334 = new GenericEntry(true_type(), 1, x275);
    GenericEntry* x2109 = x817.getCopyDependent(x334, 0);
    GenericEntry* x338 = new GenericEntry(true_type(), 1, x276, 2, x275);
    GenericEntry* x2112 = x834.getCopyDependent(x338, 0);
    int o_id = x2112->getInt(11);
    x2112->increase(11, 1);
    x834.updateCopyDependent(x2112);
    GenericEntry* x346 = new GenericEntry(false_type(), o_id, x276, x275, x277, x273, -1, x278, (x279>(0)));
    x827.add(x346);
    GenericEntry* x349 = new GenericEntry(false_type(), o_id, x276, x275);
    x805.add(x349);
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
      GenericEntry* x2136 = x849.getCopyDependent(x368, 0);
      PString ite3889 = PString();
      if((x276==(1))) {
        PString x3890 = x2136->getString(4);
        ite3889 = x3890;
      } else {
        
        PString ite3894 = PString();
        if((x276==(2))) {
          PString x3895 = x2136->getString(5);
          ite3894 = x3895;
        } else {
          
          PString ite3899 = PString();
          if((x276==(3))) {
            PString x3900 = x2136->getString(6);
            ite3899 = x3900;
          } else {
            
            PString ite3904 = PString();
            if((x276==(4))) {
              PString x3905 = x2136->getString(7);
              ite3904 = x3905;
            } else {
              
              PString ite3909 = PString();
              if((x276==(5))) {
                PString x3910 = x2136->getString(8);
                ite3909 = x3910;
              } else {
                
                PString ite3914 = PString();
                if((x276==(6))) {
                  PString x3915 = x2136->getString(9);
                  ite3914 = x3915;
                } else {
                  
                  PString ite3919 = PString();
                  if((x276==(7))) {
                    PString x3920 = x2136->getString(10);
                    ite3919 = x3920;
                  } else {
                    
                    PString ite3924 = PString();
                    if((x276==(8))) {
                      PString x3925 = x2136->getString(11);
                      ite3924 = x3925;
                    } else {
                      
                      PString ite3929 = PString();
                      if((x276==(9))) {
                        PString x3930 = x2136->getString(12);
                        ite3929 = x3930;
                      } else {
                        
                        PString x3932 = x2136->getString(13);
                        ite3929 = x3932;
                      };
                      PString x3928 = ite3929;
                      ite3924 = x3928;
                    };
                    PString x3923 = ite3924;
                    ite3919 = x3923;
                  };
                  PString x3918 = ite3919;
                  ite3914 = x3918;
                };
                PString x3913 = ite3914;
                ite3909 = x3913;
              };
              PString x3908 = ite3909;
              ite3904 = x3908;
            };
            PString x3903 = ite3904;
            ite3899 = x3903;
          };
          PString x3898 = ite3899;
          ite3894 = x3898;
        };
        PString x3893 = ite3894;
        ite3889 = x3893;
      };
      PString ol_dist_info = ite3889;
      int s_quantity = x2136->getInt(3);
      int x401 = x289;
      x285[x401] = s_quantity;
      PString x403 = x2106->getString(14);
      char* x5238 = strstr(x403.data_, "original");
      int ite4136 = 0;
      if((x5238!=(NULL))) {
        
        PString x405 = x2136->getString(17);
        char* x5244 = strstr(x405.data_, "original");
        int x4137 = (x5244!=(NULL));
        ite4136 = x4137;
      } else {
        
        ite4136 = 0;
      };
      int x3957 = ite4136;
      if(x3957) {
        int x408 = x289;
        x286[x408] = "B";
      } else {
        
        int x410 = x289;
        x286[x410] = "G";
      };
      x2136->update(3, (s_quantity-(ol_quantity)));
      if((s_quantity<=(ol_quantity))) {
        x2136->increase(3, 91);
      };
      int x419 = 0;
      if((ol_supply_w_id!=(x275))) {
        x419 = 1;
      };
      x849.updateCopyDependent(x2136);
      double c_discount = x2106->getDouble(16);
      double w_tax = x2109->getDouble(8);
      double d_tax = x2112->getDouble(9);
      int x432 = x289;
      double x433 = x283[x432];
      double ol_amount = ((ol_quantity*(x433))*(((1.0+(w_tax))+(d_tax))))*((1.0-(c_discount)));
      int x441 = x289;
      x287[x441] = ol_amount;
      double x443 = x352;
      x352 = (x443+(ol_amount));
      int x446 = x289;
      GenericEntry* x449 = new GenericEntry(false_type(), o_id, x276, x275, (x446+(1)), ol_i_id, ol_supply_w_id, NULL, ol_quantity, ol_amount, ol_dist_info);
      x839.add(x449);
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
    if(warehouseTblPrimaryIdx == tpcc.wareRes){
       cout << "Warehouse results are correct" << endl;
    }
    if(districtTblPrimaryIdx == tpcc.distRes){
       cout << "District results are correct" << endl;
    }
    if(customerTblPrimaryIdx == tpcc.custRes){
       cout << "Customer results are correct" << endl;
    }
    if(orderTblPrimaryIdx == tpcc.ordRes){
       cout << "Order results are correct" << endl;
    }
    if(orderLineTblPrimaryIdx == tpcc.ordLRes){
       cout << "OrderLine results are correct" << endl;
    }
    if(newOrderTblPrimaryIdx == tpcc.newOrdRes){
       cout << "NewOrder results are correct" << endl;
    }
    if(itemTblPrimaryIdx == tpcc.itemRes){
       cout << "Item results are correct" << endl;
    }
    if(stockTblPrimaryIdx == tpcc.stockRes){
       cout << "Stock results are correct" << endl;
    }
    if(historyTblPrimaryIdx == tpcc.histRes){
       cout << "History results are correct" << endl;
    }
  
  #endif
  
        
}
/* ----------- FUNCTIONS ----------- */
