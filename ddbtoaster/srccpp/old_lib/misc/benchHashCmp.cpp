#include <cstdlib>
#include <random>
#include <fstream>
#include <vector>
#include <climits>
#include "hpds/KDouble.hpp"
#include "hash.hpp"
#include "hpds/pstring.hpp"
#include "hpds/pstringops.hpp"
#include "sc/mmap.hpp"
#include "sc/ScExtra.h"
#include "sc/ExecutionProfiler.h"
using namespace std;
std::unordered_map<std::string, Timepoint> startTimes;
std::unordered_map<std::string, size_t> durations;
std::unordered_map<std::string, size_t> counters;

struct SEntry {
    long _1;
    double _2;
    PString _3;

    SEntry(long l, double d, const PString& s) : _1(l), _2(d), _3(s) {
    }
    SEntry() = default;
};

struct DBTHash {

    FORCE_INLINE static size_t hash(const struct SEntry& e) {
        size_t h = 0;
        hash_combine(h, e._1);
        hash_combine(h, e._2);
//                hash_combine(h, e._3);
        return h;
    }

    //    FORCE_INLINE static char equals(const struct SEntry& x45033, const struct SEntry& x45034) {
    //        long x45035 = x45033._1;
    //        long x45036 = x45034._1;
    //        int x45037 = x45035 == (x45036);
    //        int ite139270 = 0;
    //        if (x45037) {
    //
    //            double x45038 = x45033._2;
    //            double x45039 = x45034._2;
    //            int x45040 = x45038 == (x45039);
    //            int x139271 = x45040;
    //            ite139270 = x139271;
    //        } else {
    //
    //            ite139270 = 0;
    //        };
    //        int x139262 = ite139270;
    //        int ite139279 = 0;
    //        if (x139262) {
    //
    //            PString x45042 = x45033._3;
    //            PString x45043 = x45034._3;
    //            int x45044 = x45042 == (x45043);
    //            int x139280 = x45044;
    //            ite139279 = x139280;
    //        } else {
    //
    //            ite139279 = 0;
    //        };
    //        int x139264 = ite139279;
    //        int x45046 = x139264 ? 0 : 1;
    //        return x45046;
    //    }

    FORCE_INLINE static bool equals(const struct SEntry& x, const struct SEntry& y) {
        return x._1 == y._1 && x._2 == y._2 && x._3 == y._3;
    }
};

struct SCHash {
#define int unsigned int

    FORCE_INLINE static size_t hash(const struct SEntry& x43278) {
        int x43279 = -889275714;
        long x43280 = x43278._1;
        int x43282 = -862048943 * ((HASH(x43280)));
        int x43287 = x43279;
        int x43288 = (((x43282 << (15)) | ((x43282 >> 17)))*(461845907))^(x43287);
        x43279 = ((((x43288 << (13)) | ((x43288 >> 19)))*(5))+(-430675100));
        double x43295 = x43278._2;
        int x43297 = -862048943 * ((HASH(x43295)));
        int x43302 = x43279;
        int x43303 = (((x43297 << (15)) | ((x43297 >> 17)))*(461845907))^(x43302);
        x43279 = ((((x43303 << (13)) | ((x43303 >> 19)))*(5))+(-430675100));
//        const PString& x43310 = x43278._3;
//        int x43312 = -862048943 * ((HASH(x43310)));
//        int x43317 = x43279;
//        int x43318 = (((x43312 << (15)) | ((x43312 >> 17)))*(461845907))^(x43317);
//        x43279 = ((((x43318 << (13)) | ((x43318 >> 19)))*(5))+(-430675100));
        int x43325 = x43279;
        int x43326 = x43325^(2);
        int x43329 = (x43326^((x43326 >> 16)))*(-2048144789);
        int x43332 = (x43329^((x43329 >> 13)))*(-1028477387);
        return (x43332^((x43332 >> 16)));
    }
#undef int

    FORCE_INLINE static char cmp(const struct SEntry& x3572, const struct SEntry& x3573) {
        int x3574 = 0;
        int x3575 = x3572._1;
        int x3576 = x3573._1;
        int x3577 = x3575 == (x3576);
        if (x3577) {
            double x3578 = x3572._2;
            double x3579 = x3573._2;
            int x3580 = x3578 == (x3579);
            if (x3580) {
                const PString& x3581 = x3572._3;
                const PString& x3582 = x3573._3;
                int x3583 = x3581 == (x3582);
                if (x3583) {
                    x3574 = 0;
                } else {

                    x3574 = 1;
                };
            } else {

                x3574 = 1;
            };
        } else {

            x3574 = 1;
        };
        int x3591 = x3574;
        return !x3591;
    }
};

int main(int argc, char** argv) {
    ifstream namesFile("/home/sachin/names.txt");
    vector<PString> names;
    while (namesFile.good()) {
        char n[30];
        namesFile.getline(n, 30);
        names.emplace_back(n);
    }
    vector<SEntry> eq_entries;
    vector<SEntry> h_entries;
    default_random_engine r(time(NULL));
    uniform_int_distribution<int> intgen(1, INT_MAX);
    uniform_real_distribution<double> doublegen(1, 100.0);
    uniform_int_distribution<int> namegen(0, 2999);
    size_t h1 = 0, h2 = 0;

    for (int i = 0; i < 1000000; ++i) {
        h_entries.emplace_back(intgen(r), doublegen(r), names[namegen(r)]);
    }

    ExecutionProfiler::startProfile("hash-DBT");

    for (int x = 0; x < 100; x++)
        for (auto e : h_entries) {
            h1 += DBTHash::hash(e);
        }
    ExecutionProfiler::endProfile("hash-DBT");
    ExecutionProfiler::startProfile("hash-SC");
    for (int x = 0; x < 100; x++)
        for (auto e : h_entries) {
            h2 += SCHash::hash(e);
        }
    ExecutionProfiler::endProfile("hash-SC");
    vector<int> a1, a2;
    uniform_int_distribution<int> agen(0, 99999);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                for (int x = 0; x < 100; ++x) {
                    eq_entries.emplace_back(i, (double) j, names[k]);
                }
            }
        }
    }
    for (size_t i = 0; i < 100000000; ++i) {
        a1.push_back(agen(r));
        a2.push_back(agen(r));
    }
    cout << "Starting Cmp-DBT" << endl;
    ExecutionProfiler::startProfile("cmp-DBT");

    for (size_t i = 0; i < 100000000; ++i) {
        int left = a1[i];
        int right = a2[i];
        h1 += DBTHash::equals(eq_entries[left], eq_entries[right]);
    }
    ExecutionProfiler::endProfile("cmp-DBT");
    cout << "ending Cmp-DBT" << endl;

    cout << "Starting CmpSC" << endl;
    ExecutionProfiler::startProfile("cmp-SC");

    for (size_t i = 0; i < 100000000; ++i) {
        int left = a1[i];
        int right = a2[i];
        h2 += SCHash::cmp(eq_entries[left], eq_entries[right]);
    }

    ExecutionProfiler::endProfile("cmp-SC");
    cout << "ending Cmp-SC" << endl;
    cout << "h1 = " << h1 << " h2 =" << h2 << endl;
    ExecutionProfiler::printProfile();
    return 0;
}
