
#ifndef TPCCPARSER_H
#define TPCCPARSER_H

#include <cinttypes>
#include <cstring>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <cstdio>
#include <cassert>
#include <string>



#define EXPAND(x) #x
#define STRINGIFY(x) EXPAND(x)


const std::string TStore = PROJECT_ROOT;
const std::string commandfile = TStore + "commands.txt";
//const std::string inputTableDir = "/home/sachin/sem3/Project/test/input/";
//const std::string outputTableDir = "/home/sachin/sem3/Project/test/output/";
const std::string inputTableDir = TStore + "bench/systems/tpcc/mysql/db" STRINGIFY(NUMWARE) "innodb/";
const std::string outputTableDir = TStore + "bench/systems/tpcc/mysql/results_db" STRINGIFY(NUMWARE) "innodb/";



typedef struct SEntry5_IISDS ItemEntry;
typedef struct SEntry11_IISSSSSSDDI DistrictEntry;
typedef struct SEntry21_IIISSSSSSSSSTSDDDDIIS CustomerEntry;
typedef struct SEntry8_IIIITIIB OrderEntry;
typedef struct SEntry3_III NewOrderEntry;
typedef struct SEntry8_IIIIITDS HistoryEntry;
typedef struct SEntry17_IIISSSSSSSSSSIIIS StockEntry;
typedef struct SEntry10_IIIIIITIDS OrderLineEntry;
typedef struct SEntry9_ISSSSSSDD WarehouseEntry;

std::ostream &operator<<(std::ostream &os, const ItemEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5;
}

std::ostream &operator<<(std::ostream &os, const DistrictEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8 << "  " << m._9 << "  " << m._10 << "  " << m._11;
}

std::ostream &operator<<(std::ostream &os, const OrderLineEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8 << "  " << m._9 << "  " << m._10;
}

std::ostream &operator<<(std::ostream &os, const WarehouseEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8 << "  " << m._9;
}

std::ostream &operator<<(std::ostream &os, const CustomerEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8 << "  " << m._9 << "  " << m._10 << "  " << m._11 << "  " << m._12 << "  " << m._13 << "  " << m._14 << "  " << m._15 << "  " << m._16 << "  " << m._17 << "  " << m._18 << "  " << m._19 << "  " << m._20 << "  " << m._21;
}

std::ostream &operator<<(std::ostream &os, const StockEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8 << "  " << m._9 << "  " << m._10 << "  " << m._11 << "  " << m._12 << "  " << m._13 << "  " << m._14 << "  " << m._15 << "  " << m._16 << "  " << m._17;
}

std::ostream &operator<<(std::ostream &os, const OrderEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8;
}

std::ostream &operator<<(std::ostream &os, const HistoryEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8;
}

std::ostream &operator<<(std::ostream &os, const NewOrderEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3;
}
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------

//float rnd2(float f) {
//    float f1 = f * 100;
//    int i = f1;
//    f1 -= i;
//    if (f1 < 0.5)
//        return i / 100.0;
//    if (f1 > 0.5)
//        return (i + 1) / 100.0;
//    if (i % 2)
//        return (i + 1) / 100.0;
//    return i / 100.0;
//}

//    inline bool OLVequals(const OrderLineVal& t1, const OrderLineVal& t2) {
//        if (t1.isNull || t2.isNull) return t1.isNull && t2.isNull;
//        return t1._1 == t2._1 && t1._2 == t2._2 && t1._3 == t2._3 && t1._4 == t2._4 && fabs(t1._5 - t2._5) <= 0.01 && t1._6 == t2._6;
//    }
//
//    inline bool Custequals(const CustomerVal& t1, const CustomerVal& t2) {
//        if (t1.isNull || t2.isNull) return t1.isNull && t2.isNull;
//        return t1._1 == t2._1 && t1._2 == t2._2 && t1._3 == t2._3 && t1._4 == t2._4 && t1._5 == t2._5 && t1._6 == t2._6 && t1._7 == t2._7 && t1._8 == t2._8 && t1._9 == t2._9 && t1._10 == t2._10 && t1._11 == t2._11 && t1._12 == t2._12 && t1._13 == t2._13 && fabs(t1._14 - t2._14) <= 0.01 && t1._15 == t2._15 && t1._16 == t2._16 && t1._17 == t2._17 && t1._18 == t2._18;
//    }


//-----------------------------------------

struct Program {
    const short id;
    virtual std::ostream& print(std::ostream& s) = 0;

    Program(short i) : id(i) {
    }
};

enum TPCC_Programs {
    NEWORDER, PAYMENTBYID, PAYMENTBYNAME, ORDERSTATUSBYID, ORDERSTATUSBYNAME, DELIVERY, STOCKLEVEL
};

struct NewOrder : public Program {
    int c_id;
    int d_id, w_id, o_ol_cnt;
    Date datetime;

    int itemid[15];
    int quantity[15], supware[15];

    //NOT INPUT PARAMATERS   
    bool o_all_local;
    int stock[15];
    double price[15];
    char* iname[15];
    char* bg[15];
    double amt[15];

    NewOrder() : Program(NEWORDER) {
        for (int i = 0; i < 15; ++i) {
            bg[i] = new char[2];
        }
        o_all_local = true;
    }

    virtual std::ostream& print(std::ostream& s) {
        s << "NewOrder  " << datetime << "  " << w_id << "  " << d_id << "  " << c_id << "  " << o_ol_cnt << " ";
        for (int i = 0; i < 15; i++)
            s << " " << itemid[i];
        s << " ";
        for (int i = 0; i < 15; i++)
            s << " " << supware[i];
        s << " ";
        for (int i = 0; i < 15; i++)
            s << " " << quantity[i];
        s << std::endl;
        return s;
    }
};

struct PaymentById : public Program {
    Date datetime;
    int c_id;
    int w_id, c_w_id, d_id, c_d_id;
    double h_amount;

    PaymentById() : Program(PAYMENTBYID) {
    }

    virtual std::ostream& print(std::ostream & s) {
        s << "PaymentById  " << datetime << "  " << w_id << "  " << d_id << "  " << c_w_id << "  " << c_d_id << "  " << c_id << "  " << h_amount << std::endl;

        return s;
    }

};

struct PaymentByName : public Program {
    Date datetime;
    int w_id, c_w_id;
    int d_id, c_d_id;
    char c_last_input[17];
    double h_amount;

    PaymentByName() : Program(PAYMENTBYNAME) {
    }

    virtual std::ostream& print(std::ostream & s) {
        s << "PaymentByName  " << datetime << "  " << w_id << "  " << d_id << "  " << c_w_id << "  " << c_d_id << "  " << c_last_input << "  " << h_amount << std::endl;

        return s;
    }

};

struct OrderStatusById : public Program {
    int c_id;
    int w_id, d_id;

    OrderStatusById() : Program(ORDERSTATUSBYID) {
    }

    virtual std::ostream& print(std::ostream & s) {
        s << "OrderStatusById  " << w_id << "  " << d_id << "  " << c_id << std::endl;
        return s;
    }

};

struct OrderStatusByName : public Program {
    int w_id;
    int d_id;
    char c_last[17];

#ifdef PROFILE
    static size_t count, begintime, exectime, committime;
#endif

    OrderStatusByName() : Program(ORDERSTATUSBYNAME) {
    }

    virtual std::ostream& print(std::ostream & s) {
        s << "OrderStatusByName  " << w_id << "  " << d_id << "  " << c_last << std::endl;
        return s;
    }


};

struct StockLevel : public Program {
    int w_id;
    int d_id, threshold;

    StockLevel() : Program(STOCKLEVEL) {
    }

    virtual std::ostream& print(std::ostream & s) {
        s << "StockLevel  " << w_id << "  " << d_id << "  " << threshold << std::endl;
        return s;
    }


};

struct Delivery : public Program {
    int w_id;
    int o_carrier_id;
    Date datetime;

    Delivery() : Program(DELIVERY) {
    }

    virtual std::ostream& print(std::ostream & s) {
        s << "Delivery  " << datetime << "  " << w_id << "  " << o_carrier_id << std::endl;
        return s;
    }


};

Date StrToIntDate(const char* s) {
    Date d = s[2] - '0';
    //        d = d * 10 + s[1] - '0';
    //        d = d * 10 + s[2] - '0';
    d = d * 10 + s[3] - '0';
    d = d * 10 + s[5] - '0';
    d = d * 10 + s[6] - '0';
    d = d * 10 + s[8] - '0';
    d = d * 10 + s[9] - '0';
    d = d * 10 + s[11] - '0';
    d = d * 10 + s[12] - '0';
    d = d * 10 + s[14] - '0';
    d = d * 10 + s[15] - '0';
    d = d * 10 + s[17] - '0';
    d = d * 10 + s[18] - '0';
    return d;
}

char* IntToStrDate(Date d) {
    static char s[22];
    s[0] = '2';
    s[1] = '0';
    s[21] = 0;
    s[20] = '0';
    s[19] = '.';
    s[18] = d % 10 + '0';
    d /= 10;
    s[17] = d % 10 + '0';
    d /= 10;
    s[16] = ':';
    s[15] = d % 10 + '0';
    d /= 10;
    s[14] = d % 10 + '0';
    d /= 10;
    s[13] = ':';
    s[12] = d % 10 + '0';
    d /= 10;
    s[11] = d % 10 + '0';
    d /= 10;
    s[10] = ' ';
    s[9] = d % 10 + '0';
    d /= 10;
    s[8] = d % 10 + '0';
    d /= 10;
    s[7] = '-';
    s[6] = d % 10 + '0';
    d /= 10;
    s[5] = d % 10 + '0';
    d /= 10;
    s[4] = '-';
    s[3] = d % 10 + '0';
    d /= 10;
    s[2] = d % 10 + '0';
    d /= 10;

}
////////////

struct TPCCDataGen {
    Program* programs[numPrograms];
    //    Map(Customer) iCustomer, oCustomer, fCustomer;
    //    Map(Warehouse) iWarehouse, oWarehouse, fWarehouse;
    //    Map(District) iDistrict, oDistrict, fDistrict;
    //    Map(History) iHistory, oHistory, fHistory;
    //    Map(NewOrder) iNewOrder, oNewOrder, fNewOrder;
    //    Map(Order) iOrder, oOrder, fOrder;
    //    Map(OrderLine) iOrderLine, oOrderLine, fOrderLine;
    //    Map(Item) iItem, oItem, fItem;
    //    Map(Stock) iStock, oStock, fStock;

#define STR "\"%[^\"]\""
    //#define u64 "%" SCNu64
#define DATE STR    
#define u32 "%" SCNi32
#define u16 "%" SCNi32
#define u8 "%" SCNi32
#define fp "%lf"
#define dp "%lf"
#define nullable "%[^,]"   

    ~TPCCDataGen() {
        for (size_t i = 0; i < numPrograms; i++)
            delete programs[i];
    }

    void loadPrograms() {
        std::ifstream fin(commandfile);
        std::string line;
        size_t curPrg = 0;
        while (std::getline(fin, line) && curPrg < numPrograms) {
            std::stringstream ss(line);
            std::string type;
            ss >> type;
            if (type == "NewOrder") {
                NewOrder* o = new NewOrder();
                ss >> o->datetime >> o->w_id >> o->d_id >> o->c_id >> o->o_ol_cnt;
                for (int i = 0; i < 15; i++)
                    ss >> o->itemid[i];
                for (int i = 0; i < 15; i++)
                    ss >> o->supware[i];
                for (int i = 0; i < 15; i++)
                    ss >> o->quantity[i];
                programs[curPrg++] = o;
            } else if (type == "PaymentById") {
                PaymentById* o = new PaymentById();
                ss >> o->datetime >> o->w_id >> o->d_id >> o->c_w_id >> o->c_d_id >> o->c_id >> o->h_amount;
                programs[curPrg++] = o;
            } else if (type == "PaymentByName") {
                PaymentByName* o = new PaymentByName();
                ss >> o->datetime >> o->w_id >> o->d_id >> o->c_w_id >> o->c_d_id >> o->c_last_input >> o->h_amount;
                programs[curPrg++] = o;
            } else if (type == "OrderStatusById") {
                OrderStatusById* o = new OrderStatusById();
                ss >> o->w_id >> o->d_id >> o->c_id;
                programs[curPrg++] = o;
            } else if (type == "OrderStatusByName") {
                OrderStatusByName* o = new OrderStatusByName();
                ss >> o->w_id >> o->d_id >> o->c_last;
                programs[curPrg++] = o;
            } else if (type == "Delivery") {
                Delivery* o = new Delivery();
                ss >> o->datetime >> o->w_id >> o->o_carrier_id;
                programs[curPrg++] = o;
            } else if (type == "StockLevel") {
                StockLevel* o = new StockLevel();
                ss >> o->w_id >> o->d_id >> o->threshold;
                programs[curPrg++] = o;
            } else {
                std::cerr << "UNKNOWN PROGRAM TYPE" << type << std::endl;
            }
        }
        fin.close();
    }

    void loadCust(customerTblStoreType& cust) {
        std::ifstream fin(inputTableDir + "customer.txt");
        std::string line;
        CustomerEntry c;
        char date[20];

        while (std::getline(fin, line)) {
            c._4 = new char[17];
            c._5 = new char[3];
            c._6 = new char[17];
            c._7 = new char[21];
            c._8 = new char[21];
            c._9 = new char[21];
            c._10 = new char[3];
            c._11 = new char[10];
            c._12 = new char[17];
            c._14 = new char[3];
            c._21 = new char[501];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," DATE "," STR "," dp "," fp "," dp "," dp "," u16 "," u16 "," STR, &c._1, &c._2, &c._3, c._4, c._5, c._6, c._7, c._8, c._9, c._10, c._11, c._12, date, c._14, &c._15, &c._16, &c._17, &c._18, &c._19, &c._20, c._21);
            c._13 = StrToIntDate(date);
            cust.insert_nocheck(c);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "customer.txt");
        while (std::getline(fin, line)) {
            c._4 = new char[17];
            c._5 = new char[3];
            c._6 = new char[17];
            c._7 = new char[21];
            c._8 = new char[21];
            c._9 = new char[21];
            c._10 = new char[3];
            c._11 = new char[10];
            c._12 = new char[17];
            c._14 = new char[3];
            c._21 = new char[501];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," DATE "," STR "," dp "," fp "," dp "," dp "," u16 "," u16 "," STR, &c._1, &c._2, &c._3, c._4, c._5, c._6, c._7, c._8, c._9, c._10, c._11, c._12, date, c._14, &c._15, &c._16, &c._17, &c._18, &c._19, &c._20, c._21);
            c._13 = StrToIntDate(date);
            oCustomer.insert({ck, cv});
        }
        fin.close();
#endif
    }

    void loadDist(districtTblStoreType& dist) {
        std::string line;
        std::ifstream fin(inputTableDir + "district.txt");

        DistrictEntry d;

        while (std::getline(fin, line)) {
            d._3 = new char[11];
            d._4 = new char[21];
            d._5 = new char[21];
            d._6 = new char[21];
            d._7 = new char[3];
            d._8 = new char[10];
            sscanf(line.c_str(), u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp "," u32, &d._1, &d._2, d._3, d._4, d._5, d._6, d._7, d._8, &d._9, &d._10, &d._11);
            dist.insert_nocheck(d);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "district.txt");
        while (std::getline(fin, line)) {
            d._3 = new char[11];
            d._4 = new char[21];
            d._5 = new char[21];
            d._6 = new char[21];
            d._7 = new char[3];
            d._8 = new char[10];
            sscanf(line.c_str(), u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp "," u32, &d._1, &d._2, d._3, d._4, d._5, d._6, d._7, d._8, &d._9, &d._10, &d._11);
            oDistrict.insert({k, v});
        }
        fin.close();
#endif
    }

    void loadHist(historyTblStoreType& hist) {

        std::string line;
        std::ifstream fin;
        char date[20];
        HistoryEntry h;

        fin.open(inputTableDir + "history.txt");
        while (std::getline(fin, line)) {
            h._8 = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," DATE "," fp "," STR, &h._1, &h._2, &h._3, &h._4, &h._5, date, &h._7, h._8);
            h._6 = StrToIntDate(date);
            hist.insert_nocheck(h);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "history.txt");
        while (std::getline(fin, line)) {
            h._8 = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," DATE "," fp "," STR, &h._1, &h._2, &h._3, &h._4, &h._5, date, &h._7, h._8);
            h._6 = StrToIntDate(date);
            oHistory.insert({k, v});
        }
        fin.close();
#endif
    }

    void loadItem(itemTblStoreType& item) {

        std::string line;
        std::ifstream fin;
        ItemEntry i;

        fin.open(inputTableDir + "item.txt");
        while (std::getline(fin, line)) {
            i._3 = new char[25];
            i._5 = new char[51];
            sscanf(line.c_str(), u32 "," u32 "," STR "," fp "," STR, &i._1, &i._2, i._3, &i._4, i._5);
            item.insert_nocheck(i);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "item.txt");
        while (std::getline(fin, line)) {
            i._3 = new char[25];
            i._5 = new char[51];
            sscanf(line.c_str(), u32 "," u32 "," STR "," fp "," STR, &i._1, &i._2, i._3, &i._4, i._5);
            oItem.insert({k, v});
        }
        fin.close();
#endif
    }

    void loadNewOrd(newOrderTblStoreType& no) {
        std::string line;
        std::ifstream fin;

        NewOrderEntry n;

        fin.open(inputTableDir + "new_orders.txt");
        while (std::getline(fin, line)) {
            sscanf(line.c_str(), u32 "," u8 "," u8, &n._1, &n._2, &n._3);
            no.insert_nocheck(n);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "new_orders.txt");
        while (std::getline(fin, line)) {
            sscanf(line.c_str(), u32 "," u8 "," u8, &n._1, &n._2, &n._3);
            oNewOrder.insert({k, v});
        }
        fin.close();
#endif
    }

    void loadOrdLine(orderLineTblStoreType& olt) {

        std::string line;
        std::ifstream fin;
        char date[20];
        OrderLineEntry e;

        fin.open(inputTableDir + "order_line.txt");
        while (std::getline(fin, line)) {
            e._10 = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," u8 "," nullable "," u8 "," fp "," STR, &e._1, &e._2, &e._3, &e._4, &e._5, &e._6, date, &e._8, &e._9, e._10);
            e._7 = strcmp(date, "\\N") == 0 ? 0 : StrToIntDate(date + 1);
            olt.insert_nocheck(e);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "order_line.txt");
        while (std::getline(fin, line)) {
            e._10 = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," u8 "," nullable "," u8 "," fp "," STR, &e._1, &e._2, &e._3, &e._4, &e._5, &e._6, date, &e._8, &e._9, e._10);
            e._7 = strcmp(date, "\\N") == 0 ? 0 : StrToIntDate(date + 1);
            oOrderLine.insert({k, v});
        }
        fin.close();
#endif
    }

    void loadOrders(orderTblStoreType& ot) {

        std::string line;
        std::ifstream fin;
        char date[20];

        OrderEntry o;

        char carrier[5];
        int local; //uint8_t 
        fin.open(inputTableDir + "orders.txt");
        while (std::getline(fin, line)) {
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u32 "," DATE "," nullable "," u8 "," u8, &o._1, &o._2, &o._3, &o._4, date, carrier, &o._7, &local);
            o._5 = StrToIntDate(date);
            o._6 = strcmp(carrier, "\\N") == 0 ? 0 : atoi(carrier);
            o._8 = local;
            ot.insert_nocheck(o);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "orders.txt");
        while (std::getline(fin, line)) {
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u32 "," DATE "," nullable "," u8 "," u8, &o._1, &o._2, &o._3, &o._4, date, carrier, &o._7, &local);
            o._5 = StrToIntDate(date);
            o._6 = strcmp(carrier, "\\N") == 0 ? 0 : atoi(carrier);
            o._8 = local;
            oOrder.insert({k, v});
        }
        fin.close();
#endif
    }

    void loadStocks(stockTblStoreType& st) {

        std::string line;
        std::ifstream fin;
        StockEntry s;

        fin.open(inputTableDir + "stock.txt");
        while (std::getline(fin, line)) {
            s._4 = new char[25];
            s._5 = new char[25];
            s._6 = new char[25];
            s._7 = new char[25];
            s._8 = new char[25];
            s._9 = new char[25];
            s._10 = new char[25];
            s._11 = new char[25];
            s._12 = new char[25];
            s._13 = new char[25];
            s._17 = new char[51];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," u32 "," u16 "," u16 "," STR, &s._1, &s._2, &s._3, s._4, s._5, s._6, s._7, s._8, s._9, s._10, s._11, s._12, s._13, &s._14, &s._15, &s._16, s._17);
            st.insert_nocheck(s);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "stock.txt");
        while (std::getline(fin, line)) {
            s._4 = new char[25];
            s._5 = new char[25];
            s._6 = new char[25];
            s._7 = new char[25];
            s._8 = new char[25];
            s._9 = new char[25];
            s._10 = new char[25];
            s._11 = new char[25];
            s._12 = new char[25];
            s._13 = new char[25];
            s._17 = new char[51];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," u32 "," u16 "," u16 "," STR, &s._1, &s._2, &s._3, s._4, s._5, s._6, s._7, s._8, s._9, s._10, s._11, s._12, s._13, &s._14, &s._15, &s._16, s._17);
            oStock.insert({k, v});
        }
        fin.close();
#endif
    }

    void loadWare(warehouseTblStoreType& ware) {

        std::string line;
        std::ifstream fin;
        WarehouseEntry w;
        fin.open(inputTableDir + "warehouse.txt");
        while (std::getline(fin, line)) {
            w._2 = new char[11];
            w._3 = new char[21];
            w._4 = new char[21];
            w._5 = new char[21];
            w._6 = new char[3];
            w._7 = new char[10];
            sscanf(line.c_str(), u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp, &w._1, w._2, w._3, w._4, w._5, w._6, w._7, &w._8, &w._9);
            ware.insert_nocheck(w);
        }
        fin.close();
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "warehouse.txt");
        while (std::getline(fin, line)) {
            w._2 = new char[11];
            w._3 = new char[21];
            w._4 = new char[21];
            w._5 = new char[21];
            w._6 = new char[3];
            w._7 = new char[10];
            sscanf(line.c_str(), u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp, &w._1, w._2, w._3, w._4, w._5, w._6, w._7, &w._8, &w._9);
            //           
            oWarehouse.insert({k, v});
        }
        fin.close();
#endif
    }

    //    void checkCustomerResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oCustomer) {
    //            try {
    //                const CustomerVal& v = fCustomer.at(it.first);
    //                if (!Custequals(v, it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Customer " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Customer " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //
    //                return;
    //            }
    //        }
    //        for (const auto& it : fCustomer) {
    //            try {
    //                const CustomerVal& v = oCustomer.at(it.first);
    //                if (!Custequals(v, it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Customer " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Customer " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "Customer table results are correct" << std::endl;
    //    }
    //
    //    void checkDistrictResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oDistrict) {
    //            try {
    //                const DistrictVal& v = fDistrict.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "District " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "District " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        for (const auto& it : fDistrict) {
    //            try {
    //                const DistrictVal& v = oDistrict.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "District " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "District " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "District table results are correct" << std::endl;
    //    }
    //
    //    void checkHistoryResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oHistory) {
    //            try {
    //                const HistoryVal& v = fHistory.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "History " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "History " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        for (const auto& it : fHistory) {
    //            try {
    //                const HistoryVal& v = oHistory.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "History " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "History " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "History table results are correct" << std::endl;
    //    }
    //
    //    void checkItemResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oItem) {
    //            try {
    //                const ItemVal& v = fItem.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Item " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Item " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        for (const auto& it : fItem) {
    //            try {
    //                const ItemVal& v = oItem.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Item " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Item " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "Item table results are correct" << std::endl;
    //    }
    //
    //    void checkNewOrderResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oNewOrder) {
    //            try {
    //                const NewOrderVal& v = fNewOrder.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "NewOrder " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "NewOrder " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        for (const auto& it : fNewOrder) {
    //            try {
    //                const NewOrderVal& v = oNewOrder.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "NewOrder " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "NewOrder " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "NewOrder table results are correct" << std::endl;
    //    }
    //
    //    void checkOrderLineResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oOrderLine) {
    //            try {
    //                const OrderLineVal& v = fOrderLine.at(it.first);
    //                if (!OLVequals(v, it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "OrderLine " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "OrderLine " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        for (const auto& it : fOrderLine) {
    //            try {
    //                const OrderLineVal& v = oOrderLine.at(it.first);
    //                if (!OLVequals(v, it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "OrderLine " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "OrderLine " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "OrderLine table results are correct" << std::endl;
    //    }
    //
    //    void checkOrderResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oOrder) {
    //            try {
    //                const OrderVal& v = fOrder.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Order " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Order " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        for (const auto& it : fOrder) {
    //            try {
    //                const OrderVal& v = oOrder.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Order " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Order " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "Order table results are correct" << std::endl;
    //    }
    //
    //    void checkStockResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oStock) {
    //            try {
    //                const StockVal& v = fStock.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Stock " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Stock " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        for (const auto& it : fStock) {
    //            try {
    //                const StockVal& v = oStock.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Stock " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Stock " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "Stock table results are correct" << std::endl;
    //    }
    //
    //    void checkWarehouseResults() {
    //
    //        bool isOkay = true;
    //        for (const auto& it : oWarehouse) {
    //            try {
    //                const WarehouseVal& v = fWarehouse.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Warehouse " << it.first << "contains " << v << " which should be " << it.second << std::endl;
    //                    //                        return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Warehouse " << it.first << " not present in table" << std::endl;
    //                isOkay = false;
    //                //                    return;
    //            }
    //        }
    //        for (const auto& it : fWarehouse) {
    //            try {
    //                const WarehouseVal& v = oWarehouse.at(it.first);
    //                if (!(v == it.second)) {
    //                    isOkay = false;
    //                    std::cerr << "Warehouse " << it.first << "contains " << it.second << " which should be " << v << std::endl;
    //                    //                        return;
    //                }
    //            } catch (const std::exception &ex) {
    //                std::cerr << "Warehouse " << it.first << " is extra in table" << std::endl;
    //                isOkay = false;
    //                //                    return;
    //            }
    //        }
    //        if (isOkay)
    //            std::cout << "Warehouse table results are correct" << std::endl;
    //    }
};


#endif /* TPCCPARSER_H */

