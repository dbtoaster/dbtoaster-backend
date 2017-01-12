#ifndef GENTRY_HPP
#define GENTRY_HPP
#include<unordered_map>
#include "hpds/pstring.hpp"
#include "program_base.hpp"
#define ELEM_SEPARATOR "\n\t\t\t"
using dbtoaster::date;

template <class GE, typename T>
void processSampleEntry(GE* e, const int& col, const T& arg) {
    e->update(col, arg);
    e->backPtrs = new void*[col + 1];
    for (int i = 0; i < col + 1; i++)
        e->backPtrs[i] = nullptr;
}

template <class GE, typename T, typename... Args>
void processSampleEntry(GE* e, const int& col, const T& arg, const Args&... args) {
    e->update(col, arg);
    processSampleEntry(e, args...);
}

template <class GE, typename T>
void processFullEntry(GE* e, int col, const T& arg) {
    e->update(col, arg);
    e->backPtrs = new void*[col + 1];
    for (int i = 0; i < col + 1; i++)
        e->backPtrs[i] = nullptr;
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
            case DOUBLE: return fabs(data.d - that.data.d) < 0.01;
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

    GenericEntry(const std::unordered_map<int, Any> & m) : map(m), nxt(nullptr), prv(nullptr) {        
        int s = m.size() + 1;
        backPtrs = new void*[s];
        for (int i = 0; i < s; i++)
            backPtrs[i] = nullptr;
        isSampleEntry = false;
    }
    friend class GenericOps;
public:
    std::unordered_map<int, Any> map;
    void** backPtrs;
    bool isSampleEntry;
    GenericEntry *nxt;
    GenericEntry *prv;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
        for (uint i = 1; i <= map.size(); ++i) {
            ar << ELEM_SEPARATOR;
            std::string name = "_" + std::to_string(i);
            const Any& a = map.at(i);
            switch (a.type) {
                case INT: dbtoaster::serialize_nvp(ar, name.c_str(), a.data.i);
                    break;
                case DATE: dbtoaster::serialize_nvp(ar, name.c_str(), a.data.t);
                    break;
                case STRING: dbtoaster::serialize_nvp(ar, name.c_str(), a.data.s);
                    break;
                case DOUBLE: dbtoaster::serialize_nvp(ar, name.c_str(), a.data.d);
                    break;
                default: throw std::logic_error("Cannot serialize AnyType");
            }
        }
    }

    template <typename... Args>
    GenericEntry(true_type isSampleEntry, const Args&... args) : map() {
        this->isSampleEntry = true;
        processSampleEntry(this, args...);
    }

    template <typename... Args>
    GenericEntry(false_type isSampleEntry, const Args&... args) : map() {
        this->isSampleEntry = false;
        processFullEntry(this, 1, args...);

    }

    GenericEntry(int maxIdx = 10) : nxt(nullptr), prv(nullptr) {
        backPtrs = new void*[maxIdx];
        for (int i = 0; i < maxIdx; i++)
            backPtrs[i] = nullptr;
        isSampleEntry = false;
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

    int getInt(int i) const {
        return map.at(i).data.i;
    }

    date getDate(int i) const {
        return map.at(i).data.t;
    }

    //Assuming long is same as date type

    long getLong(int i) const {
        return map.at(i).data.t;
    }

    double getDouble(int i) const {
        return map.at(i).data.d;
    }

    const PString& getString(int i) const {
        return map.at(i).data.s;
    }

    GenericEntry* copy() const {
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