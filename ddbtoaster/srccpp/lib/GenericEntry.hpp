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

enum AnyType : char {
    UNDEFINED, INT, DOUBLE, DATE, STRING
};

union AnyUnion {
    int i;
    double d;
    date t;
    PString s;

    AnyUnion() {
        memset(this, 0, sizeof (AnyUnion));
    }

    AnyUnion(const AnyUnion& a) {
        memcpy(this, &a, sizeof (AnyUnion));
    }

    ~AnyUnion() {

    }

    bool operator==(const AnyUnion& right) const {
        return memcmp(this, &right, sizeof (AnyUnion)) == 0;
    }

};

struct Any {
    AnyUnion data;
    AnyType type;

    friend std::ostream& operator<<(std::ostream& os, const Any& obj) {
        switch (obj.type) {
            case INT: os << obj.data.i;
                break;
            case DOUBLE: os << obj.data.d;
                break;
            case DATE: os << obj.data.t;
                break;
            case STRING: os << obj.data.s;
                break;
            default: os << "????";

        }
        return os;
    }

    Any() : data(), type(UNDEFINED) {

    }

    Any(const Any& that) : data(that.data), type(that.type) {
    }

    bool operator==(const Any& that) const {
        if (type == UNDEFINED || that.type == UNDEFINED) throw std::logic_error("UNDEFINED Type in Any ");
        if (type != that.type) return false;
        switch (type) {
            case INT: return data.i == that.data.i;
                break;
            case DOUBLE: return data.d == that.data.d;
                break;
            case DATE: return data.t == that.data.t;
                break;
            case STRING: return data.s == that.data.s;
                break;
            default: throw std::logic_error("Unknown type");
        }
    }

    bool operator!=(const Any& that) const {
        if (type == UNDEFINED || that.type == UNDEFINED) throw std::logic_error("UNDEFINED Type in Any ");
        if (type != that.type) return true;
        switch (type) {
            case INT: return data.i != that.data.i;
                break;
            case DOUBLE: return data.d != that.data.d;
                break;
            case DATE: return data.t != that.data.t;
                break;
            case STRING: return data.s != that.data.s;
                break;
            default: throw std::logic_error("Unknown type");
        }
    }

    bool operator<(const Any& that) const {
        if (type == UNDEFINED || that.type == UNDEFINED) throw std::logic_error("UNDEFINED Type in Any ");
        if (type != that.type) throw std::logic_error("Cannot compare different types in Any");
        switch (type) {
            case INT: return data.i < that.data.i;
                break;
            case DOUBLE: return data.d < that.data.d;
                break;
            case DATE: return data.t < that.data.t;
                break;
            case STRING: return data.s < that.data.s;
                break;
            default: throw std::logic_error("Unknown type");
        }
    }
};

class GenericEntry {
    std::unordered_map<int, Any> map;

    GenericEntry(const std::unordered_map<int, Any> & m) : map(m), nxt(nullptr), prv(nullptr) {
    }
    friend class GenericOps;
public:
    bool isSampleEntry;
    GenericEntry *nxt;
    GenericEntry *prv;

    template <typename... Args>
    GenericEntry(true_type isSampleEntry, const Args&... args) {
        this->isSampleEntry = true;
        processSampleEntry(this, args...);
    }

    template <typename... Args>
    GenericEntry(false_type isSampleEntry, const Args&... args) {
        this->isSampleEntry = false;
        processFullEntry(this, 0, args...);

    }

    GenericEntry() : nxt(nullptr), prv(nullptr) {
    }

    FORCE_INLINE void update(int i, int v) {
        map[i].type = INT;
        map[i].data.i = v;
    }

    FORCE_INLINE void update(int i, double v) {
        map[i].type = DOUBLE;
        map[i].data.d = v;
    }

    FORCE_INLINE void update(int i, date v) {
        map[i].type = DATE;
        map[i].data.t = v;
    }

    FORCE_INLINE void update(int i, const PString& v) {
        map[i].type = STRING;
        map[i].data.s = v;
    }

    FORCE_INLINE void increase(int i, int v) {
        map[i].data.i += v;
    }

    FORCE_INLINE void increase(int i, double v) {
        map[i].data.d += v;
    }

    FORCE_INLINE void increase(int i, date v) {
        map[i].data.t += v;
    }

    FORCE_INLINE void decrease(int i, int v) {
        map[i].data.i -= v;
    }

    FORCE_INLINE void decrease(int i, double v) {
        map[i].data.d -= v;
    }

    FORCE_INLINE void decrease(int i, date v) {
        map[i].data.t -= v;
    }

    int getInt(int i) {
        return map[i].data.i;
    }

    date getDate(int i) {
        return map[i].data.t;
    }

    double getDouble(int i) {
        return map[i].data.d;
    }

    PString& getString(int i) {
        return map[i].data.s;
    }

    GenericEntry* copy() {
        //ONLY SHALLOW COPY for PString.            
        return new GenericEntry(map);
    }

    bool operator==(const GenericEntry& right) const {
        return map == right.map;
    }

    friend std::ostream& operator<<(std::ostream& os, const GenericEntry& obj) {
        for (auto it : obj.map) {
            os << it.first << "->" << it.second << ", ";
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