
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

#include "mmap/mmap.hpp"



#define EXPAND(x) #x
#define STRINGIFY(x) EXPAND(x)

//#define VERIFY_TPCC 1
const std::string TStore = PROJECT_ROOT;
const std::string commandfile = TStore + "commands.txt";
//const std::string inputTableDir = "/home/sachin/sem3/Project/test/input/";
//const std::string outputTableDir = "/home/sachin/sem3/Project/test/output/";
const std::string inputTableDir = TStore + "bench/systems/tpcc/mysql/db" STRINGIFY(NUMWARE) "innodb/";
const std::string outputTableDir = TStore + "bench/systems/tpcc/mysql/results_db" STRINGIFY(NUMWARE) "innodb/";


#if USING_GENERIC_ENTRY
typedef GenericEntry ItemEntry;
typedef GenericEntry DistrictEntry;
typedef GenericEntry CustomerEntry;
typedef GenericEntry OrderEntry;
typedef GenericEntry NewOrderEntry;
typedef GenericEntry HistoryEntry;
typedef GenericEntry StockEntry;
typedef GenericEntry OrderLineEntry;
typedef GenericEntry WarehouseEntry;
#else
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
#endif
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

    virtual ~Program() {
    }

    Program(short i) : id(i) {
    }
};

enum TPCC_Programs {
    NEWORDER, PAYMENTBYID, PAYMENTBYNAME, ORDERSTATUSBYID, ORDERSTATUSBYNAME, DELIVERY, STOCKLEVEL
};

struct NewOrder : public Program {
    int c_id;
    int d_id, w_id, o_ol_cnt;
    date datetime;

    int itemid[15];
    int quantity[15], supware[15];

    //NOT INPUT PARAMATERS   
    bool o_all_local;
    int stock[15];
    double price[15];
    PString iname[15];
    PString bg[15];
    double amt[15];

    virtual ~NewOrder() {
    }

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
    date datetime;
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
    date datetime;
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
    date datetime;

    Delivery() : Program(DELIVERY) {
    }

    virtual std::ostream& print(std::ostream & s) {
        s << "Delivery  " << datetime << "  " << w_id << "  " << o_carrier_id << std::endl;
        return s;
    }


};

date StrToIntdate(const char* s) {
    date d = s[2] - '0';
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

char* IntToStrdate(date d) {
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
    return s;
}
////////////

struct TPCCDataGen {
    Program* programs[numPrograms];
#ifdef VERIFY_TPCC
    warehouseTblIdx0Type wareRes;
    districtTblIdx0Type distRes;
    customerTblIdx0Type custRes;
    orderTblIdx0Type ordRes;
    orderLineTblIdx0Type ordLRes;
    newOrderTblIdx0Type newOrdRes;
    itemTblIdx0Type itemRes;
    stockTblIdx0Type stockRes;
    historyTblIdx0Type histRes;
#endif
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
#ifdef VERIFY_TPCC

    TPCCDataGen() : wareRes(nullptr, warehouseTblSize), distRes(nullptr, districtTblSize), custRes(nullptr, customerTblSize), ordRes(nullptr, orderTblSize), ordLRes(nullptr, orderLineTblSize), newOrdRes(nullptr, newOrderTblSize), itemRes(nullptr, itemTblSize), stockRes(nullptr, stockTblSize), histRes(nullptr, historyTblSize) {
        wareRes.idxId = 0;
        distRes.idxId = 0;
        custRes.idxId = 0;
        ordRes.idxId = 0;
        ordLRes.idxId = 0;
        newOrdRes.idxId = 0;
        itemRes.idxId = 0;
        stockRes.idxId = 0;
        histRes.idxId = 0;
    }
#endif

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

    void loadCust() {
        std::ifstream fin(inputTableDir + "customer.txt");
        std::string line;
        CustomerEntry c;
        char datestr[20];

        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int c_1;
            int c_2;
            int c_3;
            char c_4[17];
            char c_5[3];
            char c_6[17];
            char c_7[21];
            char c_8[21];
            char c_9[21];
            char c_10[3];
            char c_11[10];
            char c_12[17];
            date c_13;
            char c_14[3];
            double c_15;
            double c_16;
            double c_17;
            double c_18;
            int c_19;
            int c_20;
            char c_21[501];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," DATE "," STR "," dp "," fp "," dp "," dp "," u16 "," u16 "," STR, &c_1, &c_2, &c_3, c_4, c_5, c_6, c_7, c_8, c_9, c_10, c_11, c_12, datestr, c_14, &c_15, &c_16, &c_17, &c_18, &c_19, &c_20, c_21);
            c_13 = StrToIntdate(datestr);
            customerTbl.insert_nocheck(CustomerEntry(false_type(), c_1, c_2, c_3, PString(c_4), PString(c_5), PString(c_6), PString(c_7), PString(c_8), PString(c_9), PString(c_10), PString(c_11), PString(c_12), c_13, PString(c_14), c_15, c_16, c_17, c_18, c_19, c_20, PString(c_21)));
#else
            c._4.data_ = new char[17];
            c._5.data_ = new char[3];
            c._6.data_ = new char[17];
            c._7.data_ = new char[21];
            c._8.data_ = new char[21];
            c._9.data_ = new char[21];
            c._10.data_ = new char[3];
            c._11.data_ = new char[10];
            c._12.data_ = new char[17];
            c._14.data_ = new char[3];
            c._21.data_ = new char[501];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," DATE "," STR "," dp "," fp "," dp "," dp "," u16 "," u16 "," STR, &c._1, &c._2, &c._3, c._4.data_, c._5.data_, c._6.data_, c._7.data_, c._8.data_, c._9.data_, c._10.data_, c._11.data_, c._12.data_, datestr, c._14.data_, &c._15, &c._16, &c._17, &c._18, &c._19, &c._20, c._21.data_);
            c._13 = StrToIntdate(datestr);
            c._4.recomputeSize();
            c._5.recomputeSize();
            c._6.recomputeSize();
            c._7.recomputeSize();
            c._8.recomputeSize();
            c._9.recomputeSize();
            c._10.recomputeSize();
            c._11.recomputeSize();
            c._12.recomputeSize();
            c._14.recomputeSize();
            c._21.recomputeSize();
            customerTbl.insert_nocheck(c);
#endif
        }
        fin.close();
        std::cout << "Customer Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "customer.txt");
        while (std::getline(fin, line)) {

#if USING_GENERIC_ENTRY
            int c_1;
            int c_2;
            int c_3;
            char c_4[17];
            char c_5[3];
            char c_6[17];
            char c_7[21];
            char c_8[21];
            char c_9[21];
            char c_10[3];
            char c_11[10];
            char c_12[17];
            date c_13;
            char c_14[3];
            double c_15;
            double c_16;
            double c_17;
            double c_18;
            int c_19;
            int c_20;
            char c_21[501];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," DATE "," STR "," dp "," fp "," dp "," dp "," u16 "," u16 "," STR, &c_1, &c_2, &c_3, c_4, c_5, c_6, c_7, c_8, c_9, c_10, c_11, c_12, datestr, c_14, &c_15, &c_16, &c_17, &c_18, &c_19, &c_20, c_21);
            c_13 = StrToIntdate(datestr);
            custRes.insert_nocheck(new CustomerEntry(false_type(), c_1, c_2, c_3, PString(c_4), PString(c_5), PString(c_6), PString(c_7), PString(c_8), PString(c_9), PString(c_10), PString(c_11), PString(c_12), c_13, PString(c_14), c_15, c_16, c_17, c_18, c_19, c_20, PString(c_21)));
#else
            CustomerEntry *cR = new CustomerEntry();
            cR->_4.data_ = new char[17];
            cR->_5.data_ = new char[3];
            cR->_6.data_ = new char[17];
            cR->_7.data_ = new char[21];
            cR->_8.data_ = new char[21];
            cR->_9.data_ = new char[21];
            cR->_10.data_ = new char[3];
            cR->_11.data_ = new char[10];
            cR->_12.data_ = new char[17];
            cR->_14.data_ = new char[3];
            cR->_21.data_ = new char[501];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," DATE "," STR "," dp "," fp "," dp "," dp "," u16 "," u16 "," STR, &cR->_1, &cR->_2, &cR->_3, cR->_4.data_, cR->_5.data_, cR->_6.data_, cR->_7.data_, cR->_8.data_, cR->_9.data_, cR->_10.data_, cR->_11.data_, cR->_12.data_, datestr, cR->_14.data_, &cR->_15, &cR->_16, &cR->_17, &cR->_18, &cR->_19, &cR->_20, cR->_21.data_);
            cR->_13 = StrToIntdate(datestr);
            cR->_4.recomputeSize();
            cR->_5.recomputeSize();
            cR->_6.recomputeSize();
            cR->_7.recomputeSize();
            cR->_8.recomputeSize();
            cR->_9.recomputeSize();
            cR->_10.recomputeSize();
            cR->_11.recomputeSize();
            cR->_12.recomputeSize();
            cR->_14.recomputeSize();
            cR->_21.recomputeSize();
            custRes.insert_nocheck(cR);
#endif
        }
        fin.close();
        std::cout << "Customer Table Results loaded" << std::endl;
#endif
    }

    void loadDist() {
        std::string line;
        std::ifstream fin(inputTableDir + "district.txt");

        DistrictEntry d;

        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int d_1;
            int d_2;
            char d_3[11];
            char d_4[21];
            char d_5[21];
            char d_6[21];
            char d_7[3];
            char d_8[10];
            double d_9;
            double d_10;
            int d_11;
            sscanf(line.c_str(), u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp "," u32, &d_1, &d_2, d_3, d_4, d_5, d_6, d_7, d_8, &d_9, &d_10, &d_11);
            districtTbl.insert_nocheck(DistrictEntry(false_type(), d_1, d_2, PString(d_3), PString(d_4), PString(d_5), PString(d_6), PString(d_7), PString(d_8), d_9, d_10, d_11));
#else
            d._3.data_ = new char[11];
            d._4.data_ = new char[21];
            d._5.data_ = new char[21];
            d._6.data_ = new char[21];
            d._7.data_ = new char[3];
            d._8.data_ = new char[10];
            sscanf(line.c_str(), u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp "," u32, &d._1, &d._2, d._3.data_, d._4.data_, d._5.data_, d._6.data_, d._7.data_, d._8.data_, &d._9, &d._10, &d._11);
            d._3.recomputeSize();
            d._4.recomputeSize();
            d._5.recomputeSize();
            d._6.recomputeSize();
            d._7.recomputeSize();
            d._8.recomputeSize();
            districtTbl.insert_nocheck(d);
#endif
        }
        fin.close();
        std::cout << "District Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "district.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int d_1;
            int d_2;
            char d_3[11];
            char d_4[21];
            char d_5[21];
            char d_6[21];
            char d_7[3];
            char d_8[10];
            double d_9;
            double d_10;
            int d_11;
            sscanf(line.c_str(), u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp "," u32, &d_1, &d_2, d_3, d_4, d_5, d_6, d_7, d_8, &d_9, &d_10, &d_11);
            distRes.insert_nocheck(new DistrictEntry(false_type(), d_1, d_2, PString(d_3), PString(d_4), PString(d_5), PString(d_6), PString(d_7), PString(d_8), d_9, d_10, d_11));

#else
            DistrictEntry *dR = new DistrictEntry();
            dR->_3.data_ = new char[11];
            dR->_4.data_ = new char[21];
            dR->_5.data_ = new char[21];
            dR->_6.data_ = new char[21];
            dR->_7.data_ = new char[3];
            dR->_8.data_ = new char[10];
            sscanf(line.c_str(), u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp "," u32, &dR->_1, &dR->_2, dR->_3.data_, dR->_4.data_, dR->_5.data_, dR->_6.data_, dR->_7.data_, dR->_8.data_, &dR->_9, &dR->_10, &dR->_11);
            dR->_3.recomputeSize();
            dR->_4.recomputeSize();
            dR->_5.recomputeSize();
            dR->_6.recomputeSize();
            dR->_7.recomputeSize();
            dR->_8.recomputeSize();
            distRes.insert_nocheck(dR);
#endif
        }
        fin.close();
        std::cout << "District Table Results loaded" << std::endl;
#endif
    }

    void loadHist() {

        std::string line;
        std::ifstream fin;
        char datestr[20];
        HistoryEntry h;

        fin.open(inputTableDir + "history.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int h_1;
            int h_2;
            int h_3;
            int h_4;
            int h_5;
            date h_6;
            double h_7;
            char h_8[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," DATE "," fp "," STR, &h_1, &h_2, &h_3, &h_4, &h_5, datestr, &h_7, h_8);
            h_6 = StrToIntdate(datestr);
            historyTbl.insert_nocheck(HistoryEntry(false_type(), h_1, h_2, h_3, h_4, h_5, h_6, h_7, PString(h_8)));

#else
            h._8.data_ = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," DATE "," fp "," STR, &h._1, &h._2, &h._3, &h._4, &h._5, datestr, &h._7, h._8.data_);
            h._6 = StrToIntdate(datestr);
            h._8.recomputeSize();
            historyTbl.insert_nocheck(h);
#endif
        }
        fin.close();
        std::cout << "History Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "history.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int h_1;
            int h_2;
            int h_3;
            int h_4;
            int h_5;
            date h_6;
            double h_7;
            char h_8[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," DATE "," fp "," STR, &h_1, &h_2, &h_3, &h_4, &h_5, datestr, &h_7, h_8);
            h_6 = StrToIntdate(datestr);
            histRes.insert_nocheck(new HistoryEntry(false_type(), h_1, h_2, h_3, h_4, h_5, h_6, h_7, PString(h_8)));
#else
            HistoryEntry *hR = new HistoryEntry();
            hR->_8.data_ = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," DATE "," fp "," STR, &hR->_1, &hR->_2, &hR->_3, &hR->_4, &hR->_5, datestr, &hR->_7, hR->_8.data_);
            hR->_6 = StrToIntdate(datestr);
            hR->_8.recomputeSize();
            histRes.insert_nocheck(hR);
#endif
        }
        fin.close();
        std::cout << "History Table Results loaded" << std::endl;
#endif
    }

    void loadItem() {

        std::string line;
        std::ifstream fin;
        ItemEntry i;

        fin.open(inputTableDir + "item.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int i_1;
            int i_2;
            char i_3[25];
            double i_4;
            char i_5[51];
            sscanf(line.c_str(), u32 "," u32 "," STR "," fp "," STR, &i_1, &i_2, i_3, &i_4, i_5);
            itemTbl.insert_nocheck(ItemEntry(false_type(), i_1, i_2, PString(i_3), i_4, i_5));
#else
            i._3.data_ = new char[25];
            i._5.data_ = new char[51];
            sscanf(line.c_str(), u32 "," u32 "," STR "," fp "," STR, &i._1, &i._2, i._3.data_, &i._4, i._5.data_);
            i._3.recomputeSize();
            i._5.recomputeSize();
            itemTbl.insert_nocheck(i);
#endif
        }
        fin.close();
        std::cout << "Item Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "item.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int i_1;
            int i_2;
            char i_3[25];
            double i_4;
            char i_5[51];
            sscanf(line.c_str(), u32 "," u32 "," STR "," fp "," STR, &i_1, &i_2, i_3, &i_4, i_5);
            itemRes.insert_nocheck(new ItemEntry(false_type(), i_1, i_2, PString(i_3), i_4, i_5));
#else
            ItemEntry *iR = new ItemEntry();
            iR->_3.data_ = new char[25];
            iR->_5.data_ = new char[51];
            sscanf(line.c_str(), u32 "," u32 "," STR "," fp "," STR, &iR->_1, &iR->_2, iR->_3.data_, &iR->_4, iR->_5.data_);
            iR->_3.recomputeSize();
            iR->_5.recomputeSize();
            itemRes.insert_nocheck(iR);
#endif
        }
        fin.close();
        std::cout << "Item Table results loaded" << std::endl;
#endif
    }

    void loadNewOrd() {
        std::string line;
        std::ifstream fin;

        NewOrderEntry n;

        fin.open(inputTableDir + "new_orders.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int n_1;
            int n_2;
            int n_3;
            sscanf(line.c_str(), u32 "," u8 "," u8, &n_1, &n_2, &n_3);
            newOrderTbl.insert_nocheck(NewOrderEntry(false_type(), n_1, n_2, n_3));
#else
            sscanf(line.c_str(), u32 "," u8 "," u8, &n._1, &n._2, &n._3);
            newOrderTbl.insert_nocheck(n);
#endif
        }
        fin.close();
        std::cout << "NewOrder Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "new_orders.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int n_1;
            int n_2;
            int n_3;
            sscanf(line.c_str(), u32 "," u8 "," u8, &n_1, &n_2, &n_3);
            newOrdRes.insert_nocheck(new NewOrderEntry(false_type(), n_1, n_2, n_3));
#else
            NewOrderEntry *nR = new NewOrderEntry();
            sscanf(line.c_str(), u32 "," u8 "," u8, &nR->_1, &nR->_2, &nR->_3);
            newOrdRes.insert_nocheck(nR);
#endif
        }
        fin.close();
        std::cout << "NewOrder Table Results loaded" << std::endl;
#endif
    }

    void loadOrdLine() {

        std::string line;
        std::ifstream fin;
        char datestr[20];
        OrderLineEntry e;

        fin.open(inputTableDir + "order_line.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int e_1;
            int e_2;
            int e_3;
            int e_4;
            int e_5;
            int e_6;
            date e_7;
            int e_8;
            double e_9;
            char e_10[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," u8 "," nullable "," u8 "," fp "," STR, &e_1, &e_2, &e_3, &e_4, &e_5, &e_6, datestr, &e_8, &e_9, e_10);
            e_7 = strcmp(datestr, "\\N") == 0 ? 0 : StrToIntdate(datestr + 1);
            orderLineTbl.insert_nocheck(OrderLineEntry(false_type(), e_1, e_2, e_3, e_4, e_5, e_6, e_7, e_8, e_9, PString(e_10)));
#else
            e._10.data_ = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," u8 "," nullable "," u8 "," fp "," STR, &e._1, &e._2, &e._3, &e._4, &e._5, &e._6, datestr, &e._8, &e._9, e._10.data_);
            e._7 = strcmp(datestr, "\\N") == 0 ? 0 : StrToIntdate(datestr + 1);
            e._10.recomputeSize();
            orderLineTbl.insert_nocheck(e);
#endif
        }
        fin.close();
        std::cout << "OrderLine Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "order_line.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int e_1;
            int e_2;
            int e_3;
            int e_4;
            int e_5;
            int e_6;
            date e_7;
            int e_8;
            double e_9;
            char e_10[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," u8 "," nullable "," u8 "," fp "," STR, &e_1, &e_2, &e_3, &e_4, &e_5, &e_6, datestr, &e_8, &e_9, e_10);
            e_7 = strcmp(datestr, "\\N") == 0 ? 0 : StrToIntdate(datestr + 1);
            ordLRes.insert_nocheck(new OrderLineEntry(false_type(), e_1, e_2, e_3, e_4, e_5, e_6, e_7, e_8, e_9, PString(e_10)));
#else
            OrderLineEntry * eR = new OrderLineEntry();
            eR->_10.data_ = new char[25];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u8 "," u32 "," u8 "," nullable "," u8 "," fp "," STR, &eR->_1, &eR->_2, &eR->_3, &eR->_4, &eR->_5, &eR->_6, datestr, &eR->_8, &eR->_9, eR->_10.data_);
            eR->_7 = strcmp(datestr, "\\N") == 0 ? 0 : StrToIntdate(datestr + 1);
            eR->_10.recomputeSize();
            ordLRes.insert_nocheck(eR);
#endif
        }
        fin.close();
        std::cout << "OrderLine Table Results loaded" << std::endl;
#endif
    }

    void loadOrders() {

        std::string line;
        std::ifstream fin;
        char datestr[20];

        OrderEntry o;

        char carrier[5];
        int local; //uint8_t 
        fin.open(inputTableDir + "orders.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int o_1;
            int o_2;
            int o_3;
            int o_4;
            date o_5;
            int o_6;
            int o_7;
            int o_8;
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u32 "," DATE "," nullable "," u8 "," u8, &o_1, &o_2, &o_3, &o_4, datestr, carrier, &o_7, &local);
            o_5 = StrToIntdate(datestr);
            o_6 = strcmp(carrier, "\\N") == 0 ? -1 : atoi(carrier);
            o_8 = local;
            orderTbl.insert_nocheck(OrderEntry(false_type(), o_1, o_2, o_3, o_4, o_5, o_6, o_7, o_8));
#else
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u32 "," DATE "," nullable "," u8 "," u8, &o._1, &o._2, &o._3, &o._4, datestr, carrier, &o._7, &local);
            o._5 = StrToIntdate(datestr);
            o._6 = strcmp(carrier, "\\N") == 0 ? -1 : atoi(carrier);
            o._8 = local;
            orderTbl.insert_nocheck(o);
#endif
        }
        fin.close();
        std::cout << "Order Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "orders.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int o_1;
            int o_2;
            int o_3;
            int o_4;
            date o_5;
            int o_6;
            int o_7;
            int o_8;
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u32 "," DATE "," nullable "," u8 "," u8, &o_1, &o_2, &o_3, &o_4, datestr, carrier, &o_7, &local);
            o_5 = StrToIntdate(datestr);
            o_6 = strcmp(carrier, "\\N") == 0 ? -1 : atoi(carrier);
            o_8 = local;
            ordRes.insert_nocheck(new OrderEntry(false_type(), o_1, o_2, o_3, o_4, o_5, o_6, o_7, o_8));
#else
            OrderEntry *oR = new OrderEntry();
            sscanf(line.c_str(), u32 "," u8 "," u8 "," u32 "," DATE "," nullable "," u8 "," u8, &oR->_1, &oR->_2, &oR->_3, &oR->_4, datestr, carrier, &oR->_7, &local);
            oR->_5 = StrToIntdate(datestr);
            oR->_6 = strcmp(carrier, "\\N") == 0 ? -1 : atoi(carrier);
            oR->_8 = local;
            ordRes.insert_nocheck(oR);
#endif
        }
        fin.close();
        std::cout << "Order Table results loaded" << std::endl;
#endif
    }

    void loadStocks() {

        std::string line;
        std::ifstream fin;
        StockEntry s;

        fin.open(inputTableDir + "stock.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY

            int s_1;
            int s_2;
            int s_3;
            char s_4[25];
            char s_5[25];
            char s_6[25];
            char s_7[25];
            char s_8[25];
            char s_9[25];
            char s_10[25];
            char s_11[25];
            char s_12[25];
            char s_13[25];
            int s_14;
            int s_15;
            int s_16;
            char s_17[51];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," u32 "," u16 "," u16 "," STR, &s_1, &s_2, &s_3, s_4, s_5, s_6, s_7, s_8, s_9, s_10, s_11, s_12, s_13, &s_14, &s_15, &s_16, s_17);
            stockTbl.insert_nocheck(StockEntry(false_type(), s_1, s_2, s_3, PString(s_4), PString(s_5), PString(s_6), PString(s_7), PString(s_8), PString(s_9), PString(s_10), PString(s_11), PString(s_12), PString(s_13), s_14, s_15, s_16, PString(s_17)));
#else
            s._4.data_ = new char[25];
            s._5.data_ = new char[25];
            s._6.data_ = new char[25];
            s._7.data_ = new char[25];
            s._8.data_ = new char[25];
            s._9.data_ = new char[25];
            s._10.data_ = new char[25];
            s._11.data_ = new char[25];
            s._12.data_ = new char[25];
            s._13.data_ = new char[25];
            s._17.data_ = new char[51];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," u32 "," u16 "," u16 "," STR, &s._1, &s._2, &s._3, s._4.data_, s._5.data_, s._6.data_, s._7.data_, s._8.data_, s._9.data_, s._10.data_, s._11.data_, s._12.data_, s._13.data_, &s._14, &s._15, &s._16, s._17.data_);
            s._4.recomputeSize();
            s._5.recomputeSize();
            s._6.recomputeSize();
            s._7.recomputeSize();
            s._8.recomputeSize();
            s._9.recomputeSize();
            s._10.recomputeSize();
            s._11.recomputeSize();
            s._12.recomputeSize();
            s._13.recomputeSize();
            s._17.recomputeSize();
            stockTbl.insert_nocheck(s);
#endif
        }
        fin.close();
        std::cout << "Stock Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "stock.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int s_1;
            int s_2;
            int s_3;
            char s_4[25];
            char s_5[25];
            char s_6[25];
            char s_7[25];
            char s_8[25];
            char s_9[25];
            char s_10[25];
            char s_11[25];
            char s_12[25];
            char s_13[25];
            int s_14;
            int s_15;
            int s_16;
            char s_17[51];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," u32 "," u16 "," u16 "," STR, &s_1, &s_2, &s_3, s_4, s_5, s_6, s_7, s_8, s_9, s_10, s_11, s_12, s_13, &s_14, &s_15, &s_16, s_17);
            stockRes.insert_nocheck(new StockEntry(false_type(), s_1, s_2, s_3, PString(s_4), PString(s_5), PString(s_6), PString(s_7), PString(s_8), PString(s_9), PString(s_10), PString(s_11), PString(s_12), PString(s_13), s_14, s_15, s_16, PString(s_17)));
#else
            StockEntry *sR = new StockEntry();
            sR->_4.data_ = new char[25];
            sR->_5.data_ = new char[25];
            sR->_6.data_ = new char[25];
            sR->_7.data_ = new char[25];
            sR->_8.data_ = new char[25];
            sR->_9.data_ = new char[25];
            sR->_10.data_ = new char[25];
            sR->_11.data_ = new char[25];
            sR->_12.data_ = new char[25];
            sR->_13.data_ = new char[25];
            sR->_17.data_ = new char[51];
            sscanf(line.c_str(), u32 "," u8 "," u8 "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," STR "," u32 "," u16 "," u16 "," STR, &sR->_1, &sR->_2, &sR->_3, sR->_4.data_, sR->_5.data_, sR->_6.data_, sR->_7.data_, sR->_8.data_, sR->_9.data_, sR->_10.data_, sR->_11.data_, sR->_12.data_, sR->_13.data_, &sR->_14, &sR->_15, &sR->_16, sR->_17.data_);
            sR->_4.recomputeSize();
            sR->_5.recomputeSize();
            sR->_6.recomputeSize();
            sR->_7.recomputeSize();
            sR->_8.recomputeSize();
            sR->_9.recomputeSize();
            sR->_10.recomputeSize();
            sR->_11.recomputeSize();
            sR->_12.recomputeSize();
            sR->_13.recomputeSize();
            sR->_17.recomputeSize();
            stockRes.insert_nocheck(sR);
#endif
        }
        fin.close();
        std::cout << "Stock Table results loaded" << std::endl;
#endif
    }

    void loadWare() {

        std::string line;
        std::ifstream fin;
        WarehouseEntry w;
        fin.open(inputTableDir + "warehouse.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int w_1;
            char w_2[11];
            char w_3[21];
            char w_4[21];
            char w_5[21];
            char w_6[3];
            char w_7[10];
            double w_8;
            double w_9;
            sscanf(line.c_str(), u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp, &w_1, w_2, w_3, w_4, w_5, w_6, w_7, &w_8, &w_9);
            warehouseTbl.insert_nocheck(WarehouseEntry(false_type(), w_1, PString(w_2), PString(w_3), PString(w_4), PString(w_5), PString(w_6), PString(w_7), w_8, w_9));
#else
            w._2.data_ = new char[11];
            w._3.data_ = new char[21];
            w._4.data_ = new char[21];
            w._5.data_ = new char[21];
            w._6.data_ = new char[3];
            w._7.data_ = new char[10];
            sscanf(line.c_str(), u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp, &w._1, w._2.data_, w._3.data_, w._4.data_, w._5.data_, w._6.data_, w._7.data_, &w._8, &w._9);
            w._2.recomputeSize();
            w._3.recomputeSize();
            w._4.recomputeSize();
            w._5.recomputeSize();
            w._6.recomputeSize();
            w._7.recomputeSize();
            warehouseTbl.insert_nocheck(w);
#endif
        }
        fin.close();
        std::cout << "Warehouse Table loaded" << std::endl;
#ifdef VERIFY_TPCC
        fin.open(outputTableDir + "warehouse.txt");
        while (std::getline(fin, line)) {
#if USING_GENERIC_ENTRY
            int w_1;
            char w_2[11];
            char w_3[21];
            char w_4[21];
            char w_5[21];
            char w_6[3];
            char w_7[10];
            double w_8;
            double w_9;
            sscanf(line.c_str(), u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp, &w_1, w_2, w_3, w_4, w_5, w_6, w_7, &w_8, &w_9);
            wareRes.insert_nocheck(new WarehouseEntry(false_type(), w_1, PString(w_2), PString(w_3), PString(w_4), PString(w_5), PString(w_6), PString(w_7), w_8, w_9));
#else
            WarehouseEntry *wR = new WarehouseEntry();
            wR->_2.data_ = new char[11];
            wR->_3.data_ = new char[21];
            wR->_4.data_ = new char[21];
            wR->_5.data_ = new char[21];
            wR->_6.data_ = new char[3];
            wR->_7.data_ = new char[10];
            sscanf(line.c_str(), u8 "," STR "," STR "," STR "," STR "," STR "," STR "," fp "," dp, &wR->_1, wR->_2.data_, wR->_3.data_, wR->_4.data_, wR->_5.data_, wR->_6.data_, wR->_7.data_, &wR->_8, &wR->_9);
            wR->_2.recomputeSize();
            wR->_3.recomputeSize();
            wR->_4.recomputeSize();
            wR->_5.recomputeSize();
            wR->_6.recomputeSize();
            wR->_7.recomputeSize();
            wareRes.insert_nocheck(wR);
#endif
        }
        fin.close();
        std::cout << "Warehouse Table results loaded" << std::endl;
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

