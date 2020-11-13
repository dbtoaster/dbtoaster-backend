#ifndef MB1_H
#define MB1_H

#include <cinttypes>
#include <cstring>
#include <functional>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <string>

#include "mmap.hpp"



#define EXPAND(x) #x
#define STRINGIFY(x) EXPAND(x)

const std::string TStore = PROJECT_ROOT;
const std::string inputTableDir = TStore + "bench/systems/tpcc/mysql/db" STRINGIFY(NUMWARE) "innodb/";


#if USING_GENERIC_ENTRY
typedef GenericEntry CustomerEntry;
#else
typedef struct SEntry21_IIISSSSSSSSSTSDDDDIIS CustomerEntry;
std::ostream &operator<<(std::ostream &os, const CustomerEntry &m) {
    return os << m._1 << " " << m._2 << "  " << m._3 << "  " << m._4 << "  " << m._5 << "  " << m._6 << "  " << m._7 << "  " << m._8 << "  " << m._9 << "  " << m._10 << "  " << m._11 << "  " << m._12 << "  " << m._13 << "  " << m._14 << "  " << m._15 << "  " << m._16 << "  " << m._17 << "  " << m._18 << "  " << m._19 << "  " << m._20 << "  " << m._21;
}
#endif
//------------
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

struct MB1 {
#define STR "\"%[^\"]\""
    //#define u64 "%" SCNu64
#define DATE STR    
#define u32 "%" SCNi32
#define u16 "%" SCNi32
#define u8 "%" SCNi32
#define fp "%lf"
#define dp "%lf"
#define nullable "%[^,]"   

    void loadCust() {
        std::ifstream fin(TStore + "../customerRes.txt");
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
    }
};


#endif /* MB1_H */

