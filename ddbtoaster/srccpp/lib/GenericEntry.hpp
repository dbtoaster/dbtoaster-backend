#ifndef GENTRY_HPP
#define GENTRY_HPP
#include<unordered_map>
#include "hpds/pstring.hpp"
#include "program_base.hpp"
using dbtoaster::date;
template <class GE, typename T>
void processSampleEntry(GE* e, const int& col, const T& arg) {
    e->update(col, arg);
}

template <class GE, typename T, typename... Args>
void processSampleEntry(GE* e, const int& col, const T& arg, const Args&... args) {
    e->update(col, arg);
    processSampleEntry(e, args...);
}

template <class GE, typename T>
void processFullEntry(GE* e, int col, const T& arg) {
    e->update(col, arg);
}

template <class GE, typename T, typename... Args>
void processFullEntry(GE* e, int col, const T& arg, const Args&... args) {
    e->update(col, arg);
    processFullEntry(e, col + 1, args...);
}

union Any {
    int i;
    double d;
    date t;
    PString s;

    Any() {
        memset(this, 0, sizeof (Any));
    }

    Any(const Any& a) {
        memcpy(this, &a, sizeof (Any));
    }

    ~Any() {

    }
    bool operator==(const Any& right) const {
        return memcmp(this, &right, sizeof(Any)) == 0;
    }

};

class GenericEntry {
    std::unordered_map<int, Any> map;

    GenericEntry(const std::unordered_map<int, Any> & m) : map(m), nxt(nullptr), prv(nullptr) {
    }

public:
    GenericEntry *nxt;
    GenericEntry *prv;

    template <typename... Args>
    GenericEntry(true_type isSampleEntry, const Args&... args) {
        processSampleEntry(this, args...);
    }

    template <typename... Args>
    GenericEntry(false_type isSampleEntry, const Args&... args) {
        processFullEntry(this, 0, args...);

    }

    GenericEntry() : nxt(nullptr), prv(nullptr) {
    }

    FORCE_INLINE void update(int i, int v) {
        map[i].i = v;
    }

    FORCE_INLINE void update(int i, double v) {
        map[i].d = v;
    }

    FORCE_INLINE void update(int i, date v) {
        map[i].t = v;
    }

    FORCE_INLINE void update(int i, const PString& v) {
        map[i].s = v;
    }

    FORCE_INLINE void increase(int i, int v) {
        map[i].i += v;
    }

    FORCE_INLINE void increase(int i, double v) {
        map[i].d += v;
    }

    FORCE_INLINE void increase(int i, date v) {
        map[i].t += v;
    }

    FORCE_INLINE void decrease(int i, int v) {
        map[i].i -= v;
    }

    FORCE_INLINE void decrease(int i, double v) {
        map[i].d -= v;
    }

    FORCE_INLINE void decrease(int i, date v) {
        map[i].t -= v;
    }

    int getInt(int i) {
        return map[i].i;
    }

    date getDate(int i) {
        return map[i].t;
    }

    double getDouble(int i) {
        return map[i].d;
    }

    PString& getString(int i) {
        return map[i].s;
    }

    GenericEntry* copy() {
        //ONLY SHALLOW COPY for PString.            
        return new GenericEntry(map);
    }

    bool operator==(const GenericEntry& right) const {
        return map == right.map;
    }

    friend std::ostream& operator<<(std::ostream& os, const GenericEntry& obj) {
        for(auto it : obj.map){
            char *ptr = (char *)&it.second;
            for(uint i = 0 ; i < sizeof(Any); ++i, ++ptr){
                os << (int)(*ptr) << " ";
            }
            os << ",    ";
        }
        return os;
    }

};


//class GenericEntry {
//    std::unordered_map<int, void*> map;
//
//    GenericEntry(const std::unordered_map<int, void*> & m) : map(m), nxt(nullptr), prv(nullptr) {
//    }
//
//public:
//    GenericEntry *nxt;
//    GenericEntry *prv;
//
//    template <typename... Args>
//    GenericEntry(true_type isSampleEntry, const Args&... args) {
//        processSampleEntry(this, args...);
//    }
//
//    template <typename... Args>
//    GenericEntry(false_type isSampleEntry, const Args&... args) {
//        processFullEntry(this, 0, args...);
//
//    }
//
//    GenericEntry() : nxt(nullptr), prv(nullptr) {
//    }
//
//    template <typename T>
//    void update(int i, const T& v) {
//        auto it = map.find(i);
//        if (it == map.end()) {
//            void *ptr = (void *) new T(v);
//            map.insert({i, ptr});
//        } else {
//            *((T *) it->second) = v;
//        }
//    }
//
//    template <typename T>
//    void increase(int i, const T& v) {
//        auto it = map.find(i);
//        if (it == map.end()) {
//            void *ptr = (void *) new T(v);
//            map.insert({i, ptr});
//        } else {
//            *((T *) it->second) += v;
//        }
//    }
//
//    template <typename T>
//    void decrease(int i, const T& v) {
//        auto it = map.find(i);
//        if (it == map.end()) {
//            void *ptr = (void *) new T(-v);
//            map.insert({i, ptr});
//        } else {
//            *((T *) it->second) -= v;
//        }
//    }
//
//    template <typename T>
//    T& get(int i) {
//        return *((T*) map.at(i));
//    }
//
//    GenericEntry* copy() {
//        //ONLY SHALLOW COPY. No need of deep if incr/decr always creates new values instead of updating
//        return new GenericEntry(map);
//    }
//};
#endif