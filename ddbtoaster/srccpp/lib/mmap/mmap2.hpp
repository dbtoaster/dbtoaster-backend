#ifndef MMAP2_H
#define MMAP2_H

#include <iostream>
#include <assert.h>
#include <functional>
#include <string.h>
#include "../serialization.hpp"
#include "../hpds/pstring.hpp"
#include "../hpds/macro.hpp"

#define DEFAULT_CHUNK_SIZE 32
#define DEFAULT_LIST_SIZE 8

#define INSERT_INTO_MMAP 1
#define DELETE_FROM_MMAP -1

#define HASH_RES_t size_t

//#define DOUBLE_ZERO_APPROXIMATED
#define DOUBLE_ZERO_THRESHOLD 1e-8

template<typename T>
struct El {

    union {
        T obj;
        struct El* next;
    };

    bool used;

    El() {
        used = false;
        next = nullptr;
    }

    ~El() {
        deactivate();
    }

    void deactivate() {
        if (used) {
            obj.~T();
            used = false;
        }
        next = nullptr;
    }
};

template<typename T>
class Pool {
private:
    El<T>* free_;
    El<T>* data_;
    size_t size_;

    void add_chunk() { // precondition: no available elements
        size_ = size_ << 1;
        El<T>* chunk = new El<T>[size_ + 1];
        for (size_t i = 0; i < size_ - 1; ++i) chunk[i].next = &chunk[i + 1];
        chunk[size_ - 1].next = nullptr;
        chunk[size_].next = data_;
        data_ = chunk;
        free_ = chunk;
    }
public:

    Pool(size_t chunk_size = DEFAULT_CHUNK_SIZE) : free_(nullptr), data_(nullptr), size_(chunk_size >> 1) {
        add_chunk();
    }

    ~Pool() {
        size_t sz = size_;
        while (data_ != nullptr) {
            El<T>* el = data_[sz].next;
            delete[] data_;
            data_ = el;
            sz = sz >> 1;
        }
    }

    FORCE_INLINE T* add() {
        if (!free_) {
            //            throw std::logic_error("Pool add chunks disabled for this experiment");
            add_chunk();
        }
        El<T>* el = free_;
        free_ = free_->next;
        el->used = true;
        el->next = nullptr;
        return &(el->obj);
    }

    FORCE_INLINE void del(T* obj) {
        if (obj) {
            El<T>* el = reinterpret_cast<El<T>*> (obj);
            el->deactivate();
            el->next = free_;
            free_ = el;
        }
    }

    inline void delete_all(T* current_data) {
        if (current_data) {
            T* tmp = current_data;
            do {
                T* tmpNext = tmp->nxt;
                El<T> *tmpEl = reinterpret_cast<El<T>*> (tmp);
                tmpEl->deactivate();
                if (tmpNext) {
                    tmpEl->next = reinterpret_cast<El<T>*> (tmpNext);
                } else {
                    tmpEl->next = free_;
                }
                tmp = tmpNext;
            } while (tmp);
            free_ = reinterpret_cast<El<T>*> (current_data);
        }
    }

    inline void clear() {
        El<T>* prevChunk = nullptr;
        El<T>* chunk = data_;
        size_t sz = size_;
        size_t doubleSz = sz << 1;
        while (chunk) {
            if (prevChunk) {
                prevChunk[doubleSz - 1].next = chunk;
            }
            for (size_t i = 0; i < sz - 1; ++i) {
                chunk[i].deactivate();
                chunk[i].next = &chunk[i + 1];
            }
            chunk[sz - 1].next = nullptr; // did not change
            prevChunk = chunk;
            chunk = chunk[sz].next;
            doubleSz = sz;
            sz = sz >> 1;
        }
        free_ = data_;
    }
};

template<typename V>
struct ZeroVal {

    V get() {
        return V();
    }

    bool isZero(V a) {
        return (a == V());
    }
};

template<>
struct ZeroVal<long> {

    long get() {
        return 0L;
    }

    FORCE_INLINE bool isZero(long a) {
        return (a == 0L);
    }
};

template<>
struct ZeroVal<double> {

    double get() {
        return 0.0;
    }
#ifdef DOUBLE_ZERO_APPROXIMATED

    FORCE_INLINE bool isZero(double a) {
        return (a >= -DOUBLE_ZERO_THRESHOLD && a <= DOUBLE_ZERO_THRESHOLD);
    }
#else

    FORCE_INLINE bool isZero(double a) {
        return (a == 0.0);
    }
#endif
};

template<>
struct ZeroVal<PString> {

    PString get() {
        return PString();
    }

    FORCE_INLINE bool isZero(PString a) {
        return (a == PString());
    }
};

/*template<typename T>
struct GenericIndexFn {
  static HASH_RES_t hash(const T& e) {
    return 0;
  }
  static bool equals(const T& x,const T& y) {
    return false;
  }
};*/

template<typename T, typename V>
class Index {
public:
    int idxId;
    virtual bool hashDiffers(const T& x, const T& y) = 0;

    virtual T* get(const T& key) const = 0;

    FORCE_INLINE T* get(const T* key) {
        return get(*key);
    }

    FORCE_INLINE T* getCopy(const T& key) {
        T* ref = get(key);
        return ref ? ref->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T& key) {
        T* ref = get(key);
        return ref ? ref->copy() : nullptr;
    }

    virtual T* get(const T& key, const HASH_RES_t h) const = 0;

    virtual V getValueOrDefault(const T& key) const = 0;

    virtual V getValueOrDefault(const T& key, const HASH_RES_t hash_val) const = 0;

    virtual int setOrDelOnZero(const T& k, const V& v) = 0;

    virtual int setOrDelOnZero(const T& k, const V& v, const HASH_RES_t hash_val0) = 0;

    virtual int addOrDelOnZero(const T& k, const V& v) = 0;

    virtual int addOrDelOnZero(const T& k, const V& v, const HASH_RES_t hash_val) = 0;

    virtual void insert_nocheck(T *obj) = 0;

    virtual void add(T& obj) = 0;

    virtual void add(T* obj) = 0;

    virtual void add(T* obj, const HASH_RES_t h) = 0;


    virtual void del(T& obj) = 0;

    virtual void del(T* obj) = 0;

    FORCE_INLINE void delCopy(const T& obj, Index<T, V>* primary) {
        T* orig = primary->get(obj);
        del(orig);
    }

    FORCE_INLINE void delCopy(const T* obj, Index<T, V>* primary) {
        T* orig = primary->get(obj);
        del(orig);
    }

    FORCE_INLINE void delCopyDependent(const T* obj) {
        del(obj);
    }

    virtual void del(T& obj, const HASH_RES_t h) = 0;

    virtual void del(T* obj, const HASH_RES_t h) = 0;

    virtual void foreach(std::function<void (T*) > f) = 0;


    virtual void slice(const T& key, std::function<void (T*) > f) = 0;

    virtual void sliceCopy(const T& key, std::function<void (T*) > f) = 0;

    FORCE_INLINE void sliceCopyDependent(const T& key, std::function<void (T*) > f) {
        sliceCopy(key, f);
    }

    virtual void update(T* obj) = 0;

    /*Ideally, we should check if the hash changes and then delete and insert.
     *  However, in the cases where we use it, hash does not change, so to have 
     *   an impact, deleted and insert in all cases  */
    FORCE_INLINE void updateCopyDependent(T* obj, T* orig) {
        del(orig);
        add(obj);
    }

    FORCE_INLINE void updateCopy(T* obj, Index<T, V>* primaryIdx) {
        T* orig = primaryIdx->get(*obj);
        del(orig);
        add(obj);
    }

    virtual size_t count() = 0;

    virtual void clear() = 0;

    virtual HASH_RES_t computeHash(const T& key) = 0;

    virtual ~Index() {
    };
};

template<typename T, typename V, typename IDX_FN = T/* = GenericIndexFn<T>*/, bool is_unique = true >
class HashIndex : public Index<T, V> {
public:

    typedef struct __IdxNode {
        HASH_RES_t hash;
        T* obj;
        struct __IdxNode* nxt, *prv;
    } IdxNode; //  the linked list is maintained 'compactly': if a IdxNode has a nxt, it is full.
    IdxNode* buckets_;
    T* dataHead; //entries are linked together for efficient foreach
    Pool<T>* storePool;
    size_t size_;
private:
    Pool<IdxNode> nodes_;
    bool allocated_from_pool_;
    size_t count_, threshold_;
    double load_factor_;
    const V zero;


    // void add_(T* obj) { // does not resize the bucket array, does not maintain count
    //   HASH_RES_t h = IDX_FN::hash(*obj);
    //   IdxNode* n = &buckets_[h % size_];
    //   if (n->obj) {
    //     IdxNode* nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
    //     nw->hash = h; nw->obj = obj;
    //     nw->nxt = n->nxt; n->nxt=nw;
    //   } else {  // space left in last IdxNode
    //     n->hash = h; n->obj = obj; //n->nxt=nullptr;
    //   }
    // }

    void resize_(size_t new_size) {
        IdxNode *old = buckets_, *n, *na, *nw, *d;
        HASH_RES_t h;
        size_t sz = size_;
        buckets_ = new IdxNode[new_size];
        memset(buckets_, 0, sizeof (IdxNode) * new_size);
        size_ = new_size;
        threshold_ = size_ * load_factor_;
        bool tmp_allocated_from_pool = false;
        for (size_t b = 0; b < sz; ++b) {
            n = &old[b];
            bool pooled = false;
            do {
                if (n->obj) { //add_(n->obj); // does not resize the bucket array, does not maintain count
                    h = n->hash;
                    na = &buckets_[h % size_];

                    if (na->obj) {
                        tmp_allocated_from_pool = true;
                        nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
                        //in addition to adding nw, we also change the place of nw with na
                        //to preserve the order of elements, as it is required for
                        //non-unique hash maps
                        nw->hash = na->hash;
                        na->obj->backPtrs[Index<T, V>::idxId] = nw;
                        nw->obj = na->obj;

                        na->hash = h;
                        n->obj->backPtrs[Index<T, V>::idxId] = na;
                        na->obj = n->obj;

                        nw->nxt = na->nxt;
                        if (nw->nxt)
                            nw->nxt->prv = nw;

                        nw->prv = na;
                        na->nxt = nw;
                    } else { // space left in last IdxNode
                        na->hash = h;
                        na->obj = n->obj; //na->nxt=nullptr;
                        n->obj->backPtrs[Index<T, V>::idxId] = na;
                    }
                }
                if (pooled) {
                    d = n;
                    n = n->nxt;
                    nodes_.del(d);
                } else n = n->nxt;
                pooled = true;
            } while (n);
        }
        allocated_from_pool_ = tmp_allocated_from_pool;
        if (old) delete[] old;
    }

public:

    HashIndex(Pool<T>* stPool = nullptr, size_t size = DEFAULT_CHUNK_SIZE, double load_factor = .75) : nodes_(size), allocated_from_pool_(false), zero(ZeroVal<V>().get()) {
        storePool = stPool;
        dataHead = nullptr;
        load_factor_ = load_factor;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
        resize_(size);
    }

    ~HashIndex() {
        if (buckets_ != nullptr) delete[] buckets_;
    }

    T& operator[](const T& key) {
        return *get(key);
    }

    float avgBucketSize() {
        int denom = 0;
        int num = 0;
        for (size_t b = 0; b < size_; ++b) {
            IdxNode* n1 = &buckets_[b];
            if (!n1->obj)
                continue;
            denom++;
            do {
                num++;
            } while ((n1 = n1->nxt));
        }
        return denom ? num / denom : 0;
    }

    float maxBucketSize() {

        int max = 0;
        for (size_t b = 0; b < size_; ++b) {
            IdxNode* n1 = &buckets_[b];
            if (!n1->obj)
                continue;
            int count = 0;
            do {
                count++;
            } while ((n1 = n1->nxt));
            if (count > max)
                max = count;
        }
        return max;
    }

    bool operator==(const HashIndex<T, V, IDX_FN, is_unique> & that) const {
        for (size_t b = 0; b < size_; ++b) {
            IdxNode* n1 = &buckets_[b];
            IdxNode* n2 = &that.buckets_[b];
            if ((n1->obj && !n2->obj) || (n2->obj && !n1->obj)) {
                std::cerr << "Buckets don't match" << std::endl;
                if (n1->obj)
                    std::cerr << *n1->obj << " is extra" << std::endl;
                if (n2 -> obj)
                    std::cerr << *n2->obj << " is missing" << std::endl;
                //                return false;
            }
            if (!n1->obj || !n2->obj)
                continue;
            do {
                IdxNode *n2_iter = n2;
                do {
                    if (*n1->obj == *n2_iter->obj)
                        break;
                } while ((n2_iter = n2_iter->nxt));
                if (!n2_iter) {
                    std::cerr << *n1->obj << " is extra in table" << std::endl;
                    //                    return false;
                }
            } while ((n1 = n1->nxt));

            do {
                IdxNode *n1_iter = &buckets_[b];
                do {
                    if (*n1_iter->obj == *n2->obj)
                        break;
                } while ((n1_iter = n1_iter->nxt));
                if (!n1_iter) {
                    std::cerr << *n2->obj << " not found in table" << std::endl;
                    //                    return false;
                }
            } while ((n2 = n2->nxt));
        }
        return true;
    }

    FORCE_INLINE bool hashDiffers(const T& x, const T& y) {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }
    // retrieves the first element equivalent to the key or nullptr if not found

    inline T* get(const T* key) const {
        return get(*key);
    }

    inline T* get(const T& key) const {
        HASH_RES_t h = IDX_FN::hash(key);
        IdxNode* n = &buckets_[h % size_];
        do {
            if (n->obj && h == n->hash && !IDX_FN::cmp(key, *n->obj)) return n->obj;
        } while ((n = n->nxt));
        return nullptr;
    }

    inline T* get(const T* key, const HASH_RES_t h) const {
        return get(*key, h);
    }

    inline T* get(const T& key, const HASH_RES_t h) const {
        IdxNode* n = &buckets_[h % size_];
        do {
            if (n->obj && h == n->hash && !IDX_FN::cmp(key, *n->obj)) return n->obj;
        } while ((n = n->nxt));
        return nullptr;
    }

    inline T* getCopyDependent(const T& key) {
        T* ref = get(key);
        return ref ? ref->copy() : nullptr;
    }

    inline T* getCopyDependent(const T* key) {
        T* ref = get(key);
        return ref ? ref->copy() : nullptr;
    }

    inline T* getCopy(const T& key) {
        T* ref = get(key);
        return ref ? ref->copy() : nullptr;
    }

    inline T* getCopy(const T* key) {
        T* ref = get(key);
        return ref ? ref->copy() : nullptr;
    }

    // inserts regardless of whether element exists already

    FORCE_INLINE void add(T& obj) {
        add(&obj);
    }

    FORCE_INLINE void add(T* obj) {
        HASH_RES_t h = IDX_FN::hash(*obj);
        add(obj, h);
    }

    FORCE_INLINE void add(T* obj, const HASH_RES_t h) {
        auto idxId = Index<T, V>::idxId;
        if (idxId == 0) { //maintain usedEntry list for efficient for-each
            obj->prv = nullptr;
            obj->nxt = dataHead;
            if (dataHead) {
                dataHead->prv = obj;
            }
            dataHead = obj;
        }
        if (count_ > threshold_) {
            //            throw std::logic_error("HashIndex resize disabled for this experiment");
            resize_(size_ << 1);
        }
        size_t b = h % size_;
        IdxNode* n = &buckets_[b];
        IdxNode* nw;

        if (is_unique) {
            ++count_;
            if (n->obj) {
                allocated_from_pool_ = true;
                nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node

                nw->hash = h;
                obj->backPtrs[idxId] = nw;
                nw->obj = obj;

                nw->nxt = n->nxt;
                if (nw->nxt)
                    nw->nxt->prv = nw;

                n->nxt = nw;
                nw->prv = n;
            } else { // space left in last IdxNode
                n->hash = h;
                n->obj = obj; //n->nxt=nullptr;
                obj->backPtrs[idxId] = n;
            }
        } else {
            // ++count_;
            if (!n->obj) { // space left in last IdxNode
                ++count_;
                n->hash = h;
                n->obj = obj; //n->nxt=nullptr;
                obj->backPtrs[idxId] = n;
                return;
            }
            do {
                if (h == n->hash && !IDX_FN::cmp(*obj, *n->obj)) {
                    allocated_from_pool_ = true;
                    nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
                    nw->hash = h;
                    nw->obj = obj;
                    obj->backPtrs[idxId] = nw;

                    nw->nxt = n->nxt;
                    if (nw->nxt)
                        nw->nxt->prv = nw;

                    n->nxt = nw;
                    nw->prv = n;
                    return;
                }/*else {
          //go ahead, and look for an element in the same slice
          //or reach the end of linked list of IdxNodes
        }*/
            } while ((n = n->nxt));
            // if(!n) {
            ++count_;
            n = &buckets_[b];
            allocated_from_pool_ = true;
            nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
            //in addition to adding nw, we also change the place of nw with n
            //to preserve the order of elements, as it is required for
            //non-unique hash maps (as the first element might be the start of)
            //a chain of non-unique elements belonging to the same slice
            nw->hash = n->hash;
            n->obj->backPtrs[idxId] = nw;
            nw->obj = n->obj;

            n->hash = h;
            obj->backPtrs[idxId] = n;
            n->obj = obj;

            nw->nxt = n->nxt;
            if (nw->nxt)
                nw->nxt->prv = nw;

            n->nxt = nw;
            nw->prv = n;
            // return;
            // }
        }
    }

    FORCE_INLINE void insert_nocheck(T* obj) {
        add(obj); //FIX LATER
    }


    // deletes an existing elements (equality by pointer comparison)

    FORCE_INLINE void del(T& obj) {
        throw std::logic_error("del by reference not supported");
        T* ptr = get(obj);
        if (ptr) del(ptr);
    }

    FORCE_INLINE void del(T& obj, const HASH_RES_t h) {
        throw std::logic_error("del by reference not supported");
        T* ptr = get(obj, h);
        if (ptr) del(ptr, h);
    }

    FORCE_INLINE void del(T* obj) {
        auto idxId = Index<T, V>::idxId;
        if (idxId == 0) {
            T *elemPrv = obj->prv, *elemNxt = obj->nxt;
            if (elemPrv) elemPrv->nxt = elemNxt;
            if (elemNxt) elemNxt->prv = elemPrv;
            if (obj == dataHead) dataHead = elemNxt;
            obj->nxt = nullptr;
            obj->prv = nullptr;
        }
        IdxNode *n = (IdxNode *) obj->backPtrs[idxId];
        auto h = n->hash;
        IdxNode *prev = n->prv;
        IdxNode *next = n->nxt;
        if (prev) { //not head
            prev->nxt = next;
            if (next)
                next->prv = prev;
            nodes_.del(n);
        } else if (next) { //head and has other elements
            next->obj->backPtrs[Index<T, V>::idxId] = n;
            n->obj = next->obj;
            n->hash = next->hash;

            n->nxt = next->nxt;
            if (next->nxt)
                next->nxt->prv = n;

            nodes_.del(next);
            next = n;
        } else { //head and the only element
            n->obj = nullptr;
        }
        if (is_unique || !((prev && prev->obj && (h == prev->hash) && !IDX_FN::cmp(*obj, *prev->obj)) ||
                (next && next->obj && (h == next->hash) && !IDX_FN::cmp(*obj, *next->obj)))) --count_;
    }

    FORCE_INLINE void del(T* obj, const HASH_RES_t h) {
        del(obj);
    }

    inline void foreach(std::function<void (T*) > f) {
        for (size_t b = 0; b < size_; ++b) {
            IdxNode* n = &buckets_[b];
            do {
                if (n->obj) f(n->obj);
            } while ((n = n->nxt));
        }
    }

    inline void update(T* elem) {
        //        HASH_RES_t h = IDX_FN::hash(*elem);
        //        IdxNode* n = &(buckets_[h % size_]);
        if (is_unique) {
            // ???
        } else {
            // ???
        }
    }

    inline void slice(const T* key, std::function<void (T*) > f) {
        return slice(*key, f);
    }

    inline void slice(const T& key, std::function<void (T*) > f) {
        HASH_RES_t h = IDX_FN::hash(key);
        IdxNode* n = &(buckets_[h % size_]);
        do {
            if (n->obj && h == n->hash && !IDX_FN::cmp(key, *n->obj)) {
                do {
                    f(n->obj);
                } while ((n = n->nxt) && (h == n->hash) && !IDX_FN::cmp(key, *n->obj));
                return;
            }
        } while ((n = n->nxt));
    }

    inline void sliceCopy(const T* key, std::function<void (T*) > f) {
        sliceCopy(*key, f);
    }

    inline void sliceCopy(const T& key, std::function<void (T*) > f) {
        HASH_RES_t h = IDX_FN::hash(key);
        std::vector<T*> entries;
        IdxNode* n = &(buckets_[h % size_]);
        do {
            if (n->obj && h == n->hash && !IDX_FN::cmp(key, *n->obj)) {
                do {
                    T* temp = n->obj->copy();
                    entries.push_back(temp);
                } while ((n = n->nxt) && (h == n->hash) && !IDX_FN::cmp(key, *n->obj));
                break;
            }
        } while ((n = n->nxt));
        for (auto it : entries) {
            f(it);
        }
    }

    inline void clear() {
        if (allocated_from_pool_) {
            IdxNode* head = nullptr;
            for (size_t b = 0; b < size_; ++b) {
                IdxNode* n = buckets_[b].nxt;
                if (n) {
                    IdxNode* tmp = n;
                    if (head) {
                        while (n->nxt) n = n->nxt;
                        n->nxt = head;
                        head = tmp;
                    } else head = n;
                }
            }
            nodes_.delete_all(head);
        }
        allocated_from_pool_ = false;
        count_ = 0;
        memset(buckets_, 0, sizeof (IdxNode) * size_);
        if (dataHead != nullptr) {
            storePool->delete_all(dataHead);
            dataHead = nullptr;
        }
    }

    FORCE_INLINE size_t count() {
        return count_;
    }

    FORCE_INLINE HASH_RES_t computeHash(const T& key) {
        return IDX_FN::hash(key);
    }

    inline V getValueOrDefault(const T& key) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    inline V getValueOrDefault(const T& key, HASH_RES_t h) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    inline int setOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    inline int setOrDelOnZero(const T& k, const V& v, HASH_RES_t h) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    inline int addOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    inline int addOrDelOnZero(const T& k, const V& v, HASH_RES_t h) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    template<typename TP, typename VP, typename...INDEXES> friend class MultiHashMap;
};

template<typename T, typename V, typename IDX_FN1, typename IDX_FN2, bool is_max>
class TreeIndex : public Index<T, V> {
public:

    typedef struct __IdxTreeNode {
        unsigned char height;
        T *obj;
        struct __IdxTreeNode *parent, *left, *right;
    } IdxEquivNode;

    typedef struct __IdxNode {
        HASH_RES_t hash;
        IdxEquivNode* equivNodes;
        struct __IdxNode* nxt;
    } IdxNode; //  the linked list is maintained 'compactly': if a IdxNode has a nxt, it is full.
    IdxNode* buckets_;
    size_t size_;
private:
    const bool is_unique = false;
    Pool<IdxEquivNode> equiv_nodes_;
    Pool<IdxNode> nodes_;
    const V zero;
    size_t count_, threshold_;
    double load_factor_;

    void resize_(size_t new_size) {
        IdxNode *old = buckets_, *n, *na, *nw, *d;
        HASH_RES_t h;
        size_t sz = size_;
        buckets_ = new IdxNode[new_size];
        memset(buckets_, 0, sizeof (IdxNode) * new_size);
        size_ = new_size;
        threshold_ = size_ * load_factor_;
        for (size_t b = 0; b < sz; ++b) {
            n = &old[b];
            bool pooled = false;
            do {
                if (n->equivNodes) { //add_(n->obj); // does not resize the bucket array, does not maintain count
                    h = n->hash;
                    na = &buckets_[h % size_];
                    if (na->equivNodes) {

                        nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
                        nw->hash = h;
                        nw->equivNodes = n->equivNodes;
                        nw->nxt = na->nxt;
                        na->nxt = nw;
                    } else { // space left in last IdxNode
                        na->hash = h;
                        na->equivNodes = n->equivNodes; //na->nxt=nullptr;
                    }
                }
                if (pooled) {
                    d = n;
                    n = n->nxt;
                    nodes_.del(d);
                } else n = n->nxt;
                pooled = true;
            } while (n);
        }

        if (old) delete[] old;
    }

    FORCE_INLINE unsigned char height(IdxEquivNode* p) {
        return p ? p->height : 0;
    }

    FORCE_INLINE int bfactor(IdxEquivNode* p) {
        return height(p->right) - height(p->left);
    }

    FORCE_INLINE void fixheight(IdxEquivNode* p) {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    FORCE_INLINE IdxEquivNode* rotateright(IdxEquivNode* p) {
        IdxEquivNode* q = p->left;
        p->left = q->right;
        q->right = p;

        q->parent = p->parent;
        p->parent = q;
        if (p->left) p->left->parent = p;

        fixheight(p);
        fixheight(q);
        return q;
    }

    FORCE_INLINE IdxEquivNode* rotateleft(IdxEquivNode* q) {
        IdxEquivNode* p = q->right;
        q->right = p->left;
        p->left = q;

        p->parent = q->parent;
        q->parent = p;
        if (q->right) q->right->parent = q;

        fixheight(q);
        fixheight(p);
        return p;
    }

    FORCE_INLINE IdxEquivNode* balance(IdxEquivNode* p) // balancing the p node
    {
        fixheight(p);
        if (bfactor(p) == 2) {
            if (bfactor(p->right) < 0)
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if (bfactor(p) == -2) {
            if (bfactor(p->left) > 0)
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // balancing is not required
    }

    void printTreePreorder(IdxEquivNode* p, int indent = 0) {
        if (p != NULL) {
            if (indent) {
                for (size_t i = 0; i < indent; ++i)
                    std::cout << ' ';
            }

            //TODO: SBJ: FIXME 
            std::cout << *p->obj << "\n ";
            if (p->left) printTreePreorder(p->left, indent + 4);
            if (p->right) printTreePreorder(p->right, indent + 4);
        }
    }

    FORCE_INLINE void insertBST(T* obj, IdxEquivNode* & root) {
        //root is not null
        IdxEquivNode* curr = root;
        while (curr != nullptr) {
            T* currObj = curr->obj;
            if (currObj == obj) return; //it's already there, we do not have to do anything
            if (IDX_FN2::cmp(*obj, *currObj) == (is_max ? 1 : -1)) { // SBJ: It is the compare function
                if (curr->left == nullptr) {
                    IdxEquivNode* nw_equiv = equiv_nodes_.add(); //memset(nw, 0, sizeof(IdxEquivNode)); // add a node
                    nw_equiv->obj = obj;
                    nw_equiv->parent = curr;
                    nw_equiv->height = 1;
                    nw_equiv->left = nw_equiv->right = nullptr;
                    curr->left = nw_equiv;

                    //re-balancing the tree
                    IdxEquivNode* par;
                    while (true) {
                        par = curr->parent;
                        if (par) {
                            if (par->right == curr) {
                                curr = balance(curr);
                                par->right = curr;
                            } else {
                                curr = balance(curr);
                                par->left = curr;
                            }
                        } else {
                            root = balance(curr);
                            return;
                        }
                        curr = par;
                    }
                }
                curr = curr->left;
            } else {
                if (curr->right == nullptr) {
                    IdxEquivNode* nw_equiv = equiv_nodes_.add(); //memset(nw, 0, sizeof(IdxEquivNode)); // add a node
                    nw_equiv->obj = obj;
                    nw_equiv->parent = curr;
                    nw_equiv->left = nw_equiv->right = nullptr;
                    nw_equiv->height = 1;
                    curr->right = nw_equiv;

                    //re-balancing the tree
                    IdxEquivNode* par;
                    while (true) {
                        par = curr->parent;
                        if (par) {
                            if (par->right == curr) {
                                curr = balance(curr);
                                par->right = curr;
                            } else {
                                curr = balance(curr);
                                par->left = curr;
                            }
                        } else {
                            root = balance(curr);
                            return;
                        }
                        curr = par;
                    }
                }
                curr = curr->right; //if( IDX_FN::greaterThan(currObj->key, obj->key) ) insertBST( obj, curr->right );
            }
        }
        //obj already exists
    }

    FORCE_INLINE void removeBST(const T* obj, IdxEquivNode* & root) {
        //root is not null
        IdxEquivNode* curr = root;

        while (curr != nullptr) {
            T* currObj = curr->obj;
            if (currObj == obj) { //found it
                IdxEquivNode *tmp;
                if (curr->left && curr->right) { //2 children case
                    tmp = curr;
                    curr = curr->left;
                    while (curr->right) {
                        curr = curr->right;
                    }
                    tmp->obj = curr->obj;
                }

                //1 or 0 child case
                //curr is the element to be removed
                tmp = (curr->left ? curr->left : curr->right);

                IdxEquivNode *par = curr->parent;
                if (!par)
                    root = tmp;
                else if (curr == par->right) {
                    par->right = tmp;
                } else {
                    par->left = tmp;
                }
                if (tmp) tmp->parent = par;
                curr->left = curr->right = curr->parent = nullptr;
                equiv_nodes_.del(curr);


                if (par) {
                    curr = par;
                    //re-balancing the tree
                    while (true) {
                        par = curr->parent;
                        if (par) {
                            if (par->right == curr) {
                                curr = balance(curr);
                                par->right = curr;
                            } else {
                                curr = balance(curr);
                                par->left = curr;
                            }
                        } else {
                            root = balance(curr);
                            return;
                        }
                        curr = par;
                    }
                }
                return;
            }
            if (IDX_FN2::cmp(*currObj, *obj) == (is_max ? 1 : -1)) { //SBJ: Compare function
                curr = curr->right;
            } else { //if( IDX_FN::greaterThan(currObj->key, obj->key) ) insertBST( obj, curr->right );
                curr = curr->left;
            }
        }
        //obj does not exist
    }


public:

    //    size_t findMaxPerBucket() {
    //        size_t max = 0;
    //        for (size_t i = 0; i < size_; i++) {
    //            size_t buck_count = 0;
    //            IdxNode* n = &buckets_[i];
    //            while (n != nullptr) {
    //
    //                ++buck_count;
    //                if (is_unique)
    //                    n = n->nxt;
    //                else {
    //                    size_t h = n->hash;
    //                    const ENTRY* obj = n->obj;
    //                    //                    std::cout<<"first key is "<<key<<std::endl;
    //                    while ((n = n->nxt) && (h == n->hash) && !IDX_FN::cmp(obj, n->obj)) {
    //                        //                        std::cout<<n->obj->key<<std::endl;
    //                    }
    //                    //                    exit(1);
    //                }
    //            }
    //            if (buck_count > max) {
    //                max = buck_count;
    //            }
    //
    //        }
    //        return max;
    //    }

    //equivsize the size of Store that manages the memory for the equivalent elements that fall into the same bucket
    //          normally it is the total number of elements (not only distinct ones)
    //storesize the size of Store that manages the memory for HashMap index entries. The number of distinct index entries
    //          is an upper bound on this number

    TreeIndex(size_t size, size_t storesize, size_t equivsize, double load_factor) : equiv_nodes_(equivsize), nodes_(storesize), zero(ZeroVal<V>().get()) {
        load_factor_ = load_factor;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
        resize_(size);

    }

    TreeIndex(Pool<T>* stPool = nullptr, size_t size = DEFAULT_CHUNK_SIZE, double load_factor = .75) : equiv_nodes_(size), nodes_(size), zero(ZeroVal<V>().get()) {
        load_factor_ = load_factor;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
        resize_(size);

    }

    ~TreeIndex() {
        if (buckets_ != nullptr) delete[] buckets_;
    }

    // inserts regardless of whether element exists already

    FORCE_INLINE void add(T& obj) {
        add(& obj);
    }

    FORCE_INLINE void insert_nocheck(T* obj) {
        add(obj); //TODO: Fix later
    }

    FORCE_INLINE void add(T* obj) {
        HASH_RES_t h = IDX_FN1::hash(*obj);
        add(obj, h);
    }

    FORCE_INLINE void add(T* obj, const HASH_RES_t h) {
        if (count_ > threshold_) {
            std::cerr << "  Index resize count=" << count_ << "  size=" << size_ << std::endl;
            exit(1);
            //resize_(size_ << 1);
        }
        size_t b = h % size_;
        IdxNode* n = &buckets_[b];
        IdxNode* nw;

        //        if (is_unique) {
        //            ++count_;
        //            if (n->obj) {
        //                nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
        //                nw->hash = h;
        //                nw->obj = obj;
        //                nw->nxt = n->nxt;
        //                n->nxt = nw;
        //            } else { // space left in last IdxNode
        //                n->hash = h;
        //                n->obj = obj; //n->nxt=nullptr;
        //            }
        //        } else {
        // ++count_;
        if (!n->equivNodes) { // space left in last IdxNode
            ++count_;
            n->hash = h;
            n->equivNodes = equiv_nodes_.add();
            n->equivNodes->obj = obj; // n->equivNodes->nxt=nullptr;
            n->equivNodes->height = 1;
            n->equivNodes->parent = n->equivNodes->left = n->equivNodes->right = nullptr;

            return;
        }
        do {
            if (h == n->hash && n->equivNodes && !IDX_FN1::cmp(*obj, *n->equivNodes->obj)) {

                //insert the node in the tree, only if it is not already there
                insertBST(obj, n->equivNodes);
                return;
            }/*else {
          //go ahead, and look for an element in the same slice
          //or reach the end of linked list of IdxNodes
        }*/
        } while ((n = n->nxt));
        // if(!n) {
        ++count_;
        n = &buckets_[b];
        nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
        nw->hash = h;
        nw->equivNodes = equiv_nodes_.add(); //memset(nw, 0, sizeof(IdxEquivNode)); // add a node
        nw->equivNodes->obj = obj; //nw_equiv->nxt = null;
        nw->equivNodes->height = 1;
        nw->equivNodes->left = nw ->equivNodes ->right = nw->equivNodes->parent = nullptr;
        nw->nxt = n->nxt;
        n->nxt = nw;
        // return;
        // }
        //        }
    }

    // deletes an existing elements (equality by pointer comparison)

    FORCE_INLINE void del(T* obj) {
        HASH_RES_t h = IDX_FN1::hash(*obj);
        del(obj, h);
    }

    FORCE_INLINE void del(T* obj, const HASH_RES_t h) {
        IdxNode *n = &buckets_[h % size_];
        IdxNode *prev = nullptr, *next; // previous and next pointers
        do {
            next = n->nxt;
            if (n->hash == h && n->equivNodes && !IDX_FN1::cmp(*obj, *n->equivNodes->obj)) {
                removeBST(obj, n->equivNodes);

                if (!n->equivNodes) {
                    if (prev) { //it is an element in the linked list (and not in the bucket itself)
                        prev->nxt = next;
                        // n->nxt = nullptr;
                        // n->obj = nullptr;
                        nodes_.del(n);
                    } else if (next) { //it is the elements in the bucket, and there are other elements in linked list
                        n->equivNodes = next->equivNodes;
                        n->hash = next->hash;
                        n->nxt = next->nxt;
                        nodes_.del(next);
                        next = n;
                    } else { //it is the only element in the bucket
                        n->equivNodes = nullptr;
                    }
                    --count_;
                }
                return;
            }
            prev = n;
        } while ((n = next));
    }

    void printTree(const T& key) {
        std::cout << "--------------------------" << std::endl;
        HASH_RES_t h = IDX_FN1::hash(key);
        IdxNode* n = &(buckets_[h % size_]);

        do {
            if (n->equivNodes && h == n->hash && !IDX_FN1::cmp(key, *n->equivNodes->obj)) {
                IdxEquivNode* curr = n->equivNodes;

                printTreePreorder(curr, 0);
                return;
            }
        } while ((n = n->nxt));
        std::cout << "--------------------------" << std::endl;
    }

    FORCE_INLINE size_t count() {
        return count_;
    }

    //    class iterator {
    //    private:
    //        IdxEquivNode *n;
    //    public:
    //
    //        iterator(IdxEquivNode* ptr) : n(ptr) {
    //        }
    //
    //        iterator() : n(nullptr) {
    //        }
    //
    //        ENTRY* incr_get() {
    //            if (!n) return nullptr;
    //
    //            if (n->right) { //if current element has an element on its right
    //                n = n->right;
    //                while (n->left) n = n->left;
    //            } else {
    //                IdxEquivNode* par = n->parent;
    //                while (par && n == par->right) { //coming from right branch, we are done with the whole part of the tree, we should go upper in the tree
    //                    n = par;
    //                    par = n->parent;
    //                }
    //                n = par; //coming from left branch, now it's parent's turn
    //            }
    //            if (n)
    //                return n->obj;
    //            else
    //                return nullptr;
    //        }
    //
    //        ENTRY* get() {
    //            if (n)
    //                return n->obj;
    //            else
    //                return nullptr;
    //        };
    //
    //        ~iterator() {
    //        }
    //    };

    FORCE_INLINE bool hashDiffers(const T& x, const T& y) {
        return IDX_FN1::hash(x) != IDX_FN1::hash(y);
    }

    FORCE_INLINE T* get(const T* key) const {
        return get(*key);
    }

    FORCE_INLINE T* get(const T& key) const {
        HASH_RES_t h = IDX_FN1::hash(key);
        IdxNode* n = &(buckets_[h % size_]);

        do {
            if (n->equivNodes && h == n->hash && !IDX_FN1::cmp(key, *n->equivNodes->obj)) {
                IdxEquivNode* curr = n->equivNodes;
                while (curr->left) curr = curr->left;
                return curr->obj;
            }
        } while ((n = n->nxt));
        return nullptr;
    }

    FORCE_INLINE T* get(const T* key, const HASH_RES_t h) const {
        return get(*key, h);
    }

    FORCE_INLINE T* get(const T& key, const HASH_RES_t h) const {

        IdxNode* n = &(buckets_[h % size_]);

        do {
            if (n->equivNodes && h == n->hash && !IDX_FN1::cmp(key, *n->equivNodes->obj)) {
                IdxEquivNode* curr = n->equivNodes;
                while (curr->left) curr = curr->left;
                return curr->obj;
            }
        } while ((n = n->nxt));
        return nullptr;
    }

    inline V getValueOrDefault(const T& key) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    V getValueOrDefault(const T& key, const size_t hash_val) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    int setOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int setOrDelOnZero(const T& k, const V& v, const size_t hash_val0) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v, const size_t hash_val) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    void del(T& obj) {
        const T* ptr = get(obj);
        if (ptr) del(ptr);
    }

    void del(T& obj, const size_t h) {
        const T* ptr = get(obj, h);
        if (ptr) del(ptr);
    }

    FORCE_INLINE void foreach(std::function<void (T*) > f) {
        //TODO: implement
    }

    FORCE_INLINE void update(T* elem) {
        //Do nothing for now
    }

    FORCE_INLINE void slice(const T* key, std::function<void (T*) > f) {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void slice(const T& key, std::function<void (T*) > f) {
        throw std::logic_error("Not implemented");
        //TODO: implement.  traversal type?
    }

    FORCE_INLINE void sliceCopy(const T& key, std::function<void (T*) > f) {
        throw std::logic_error("Not implemented");
        //TODO: implement.  traversal type?
    }

    void clear() {
        throw std::logic_error("Not implemented");
    }

    size_t computeHash(const T& key) {
        return IDX_FN1::hash(key);
    }



    template<typename TP, typename VP, typename...INDEXES> friend class MultiHashMap;
};

template <typename T, typename V, typename IDX_FN, size_t size>
class ArrayIndex : public Index<T, V> {
    T* array[size];
    bool isUsed[size];
    const V zero;
public:

    ArrayIndex(Pool<T>* stPool = nullptr, int s = size) : zero(ZeroVal<V>().get()) { //Constructor argument is ignored
        memset(isUsed, 0, size);
    }

    bool operator==(const ArrayIndex<T, V, IDX_FN, size> & that) const {
        for (size_t i = 0; i < size; ++i) {
            if (isUsed[i] != that.isUsed[i]) {
                std::cerr << "Array slots don't match. ";
                if (isUsed[i])
                    std::cerr << *array[i] << " is extra" << std::endl;
                else
                    std::cerr << *that.array[i] << " is missing" << std::endl;
                return false;
            }
            if (!isUsed[i])
                continue;
            if (!(*array[i] == *that.array[i])) {
                std::cerr << "Found " << *array[i] << "  where it should have been " << *that.array[i] << std::endl;
                return false;
            }
        }
        return true;
    }

    FORCE_INLINE T* get(const T* key) const {
        return get(*key);
    }

    FORCE_INLINE T* get(const T& key) const {
        HASH_RES_t idx = IDX_FN::hash(key);
        if (idx >= 0 && idx < size && isUsed[idx]) //TODO: remove check
            return array[idx];
        return nullptr;
    }

    FORCE_INLINE void foreach(std::function<void (T*) > f) {
        for (size_t b = 0; b < size; ++b) {
            if (isUsed[b])
                f(array[b]);
        }
    }

    FORCE_INLINE void del(T* obj) {
        HASH_RES_t idx = IDX_FN::hash(*obj);
        isUsed[idx] = false;
    }

    FORCE_INLINE void add(T* obj) {
        auto idxId = Index<T, V>::idxId;
        HASH_RES_t idx = IDX_FN::hash(*obj);
        isUsed[idx] = true;
        obj->backPtrs[idxId] = (void *) &(array[idx]);
        array[idx] = obj;
    }

    FORCE_INLINE void insert_nocheck(T* obj) {
        add(obj); //TODO: Fix later
    }

    bool hashDiffers(const T& x, const T& y) {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }

    T* get(const T& key, const size_t h) const {
        return array[h];
    }

    V getValueOrDefault(const T& key) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    V getValueOrDefault(const T& key, const size_t hash_val) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    int setOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int setOrDelOnZero(const T& k, const V& v, const size_t hash_val0) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v, const size_t hash_val) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    void add(T* obj, const size_t h) {
        array[h] = obj;
        isUsed[h] = true;
    }

    void add(T& obj) {
        add(&obj);
    }

    void update(T* obj) {
        //Do nothing
    }

    void del(T* obj, const size_t h) {
        isUsed[h] = false;
    }

    void del(T& obj) {
        const T* ptr = get(obj);
        if (ptr) del(ptr);
    }

    void del(T& obj, const size_t h) {
        isUsed[h] = false;
    }

    void slice(const T& key, std::function<void (T*) > f) {
        throw std::logic_error("Not implemented");
    }

    void sliceCopy(const T& key, std::function<void (T*) > f) {
        throw std::logic_error("Not implemented");
    }

    size_t count() {
        return 0;
    }

    void clear() {

    }

    size_t computeHash(const T& key) {
        return IDX_FN::hash(key);
    }
};

template<typename T, typename V, typename...INDEXES>
class MultiHashMap {
private:
    Pool<T> pool;
    bool *modified;
public:
    Index<T, V>** index;

    MultiHashMap() { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES(&pool)...
        };
        modified = new bool[sizeof...(INDEXES)];
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            index[i]->idxId = i;
            modified[i] = false;
        }
    }

    MultiHashMap(size_t init_capacity) : pool(init_capacity) { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES(&pool, init_capacity)...
        };
        modified = new bool[sizeof...(INDEXES)];
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            index[i]->idxId = i;
            modified[i] = false;
        }
    }

    MultiHashMap(const MultiHashMap& other) { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES(&pool)...
        };
        modified = new bool[sizeof...(INDEXES)];
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            index[i]->idxId = i;
            modified[i] = false;
        }
        other.index[0]->foreach([this] (const T & e) {
            this->insert_nocheck(e); });
    }

    ~MultiHashMap() {
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) delete index[i];
        delete[] index;
        delete[] modified;
    }

    FORCE_INLINE T* get(const T* key, const size_t idx = 0) const {
        return get(*key, idx);
    }

    FORCE_INLINE T* get(const T& key, const size_t idx = 0) const {
        return index[idx]->get(key);
    }

    FORCE_INLINE T* getCopy(const T* key, const size_t idx = 0) const {
        return getCopy(*key, idx);
    }

    FORCE_INLINE T* getCopy(const T& key, const size_t idx = 0) const {
        return index[idx]->getCopy(key);
    }

    FORCE_INLINE T* getCopyDependent(const T* key, const size_t idx = 0) const {
        return getCopyDependent(*key, idx);
    }

    FORCE_INLINE T* getCopyDependent(const T& key, const size_t idx = 0) const {
        return index[idx]->getCopyDependent(key);
    }

    FORCE_INLINE T* get(const T& key, const HASH_RES_t h, const size_t idx) const {
        return index[idx]->get(key, h);
    }

    FORCE_INLINE T* copyIntoPool(const T* e) {
        T* copy = pool.add();
        new(copy) T(*e);
        return copy;
    }

    FORCE_INLINE T* copyIntoPool(const T& e) {
        T* copy = pool.add();
        new(copy) T(e);
        return copy;
    }

    FORCE_INLINE void add(const T& obj) {
        add(&obj);
    }

    void add(const T* elem) {
        T* cur = index[0]->get(*elem);
        if (cur == nullptr) {
            cur = copyIntoPool(elem);
            for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
        } else {
            // cur->~T();
            // *cur=std::move(*elem);

            for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
                if (index[i]->hashDiffers(*cur, *elem)) {
                    index[i]->del(cur);
                    modified[i] = true;
                }
            }
            new(cur) T(*elem);
            for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
                if (modified[i]) {
                    index[i]->add(cur);
                    modified[i] = false;
                }
            }
        }
    }

    FORCE_INLINE void insert_nocheck(const T* elem) {
        insert_nocheck(*elem);
    }

    FORCE_INLINE void insert_nocheck(const T& elem) {
        T* cur = copyIntoPool(elem);
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->insert_nocheck(cur);
    }

    FORCE_INLINE void insert_nocheck(const T& elem, HASH_RES_t h) { // assume that mainIdx=0
        T* cur = copyIntoPool(elem);
        index[0]->add(cur, h);
        for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
    }

    //    FORCE_INLINE void del(T& key/*, int idx=0*/) { // assume that mainIdx=0
    //        T* elem = get(key);
    //        if (elem != nullptr) del(elem);
    //    }

    FORCE_INLINE void del(T& key, HASH_RES_t h, int idx = 0) {
        throw std::logic_error("Del by reference not supported");
        T* elem = get(key, h, idx);
        if (elem != nullptr) del(elem, h);
    }

    void delSlice(const T& key, int idx = 0) {
        slice(idx, key, [this] (const T & e) {
            del(e); });
    }

    FORCE_INLINE void del(T* elem) { // assume that the element is already in the map
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
        pool.del(elem);
    }

    FORCE_INLINE void delCopyDependent(T* obj) {
        T* elem = index[0]->get(obj);
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->delCopyDependent(elem);
        pool.del(elem);
    }

    FORCE_INLINE void delCopy(T* obj) {
        T* elem = index[0]->get(obj);
        for (size_t i = sizeof...(INDEXES) - 1; i != 0; --i)
            index[i]->delCopy(obj, index[0]);
        index[0]->delCopy(obj, index[0]);
        pool.del(elem);
    }

    FORCE_INLINE void del(T* elem, HASH_RES_t h) { // assume that the element is already in the map and mainIdx=0
        index[0]->del(elem, h);
        for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
        pool.del(elem);
    }

    inline void foreach(std::function<void (T*) > f) {
        index[0]->foreach(f);
    }

    void slice(int idx, const T* key, std::function<void (T*) > f) {
        index[idx]->slice(*key, f);
    }

    void slice(int idx, const T& key, std::function<void (T*) > f) {
        index[idx]->slice(key, f);
    }

    void sliceCopy(int idx, const T* key, std::function<void (T*) > f) {
        index[idx]->sliceCopy(*key, f);
    }

    void sliceCopy(int idx, const T& key, std::function<void (T*) > f) {
        index[idx]->sliceCopy(key, f);
    }

    void sliceCopyDependent(int idx, const T* key, std::function<void (T*) > f) {
        index[idx]->sliceCopy(*key, f);
    }

    void sliceCopyDependent(int idx, const T& key, std::function<void (T*) > f) {
        index[idx]->sliceCopy(key, f);
    }

    FORCE_INLINE void update(T* elem) {
        if (elem == nullptr)
            return;
        for (size_t i = 0; i < sizeof...(INDEXES); ++i) {
            index[i]->update(elem);
        }
    }

    FORCE_INLINE void updateCopyDependent(T* obj2) {
        if (obj2 == nullptr)
            return;
        T* elem = index[0]->get(*obj2);
        T* obj = copyIntoPool(obj2);
        for (size_t i = 0; i < sizeof...(INDEXES); ++i) {
            index[i]->updateCopyDependent(obj, elem);
        }
    }

    FORCE_INLINE void updateCopy(T* obj2) {
        if (obj2 == nullptr)
            return;

        T* obj = copyIntoPool(obj2);
        //i >= 0 cant be used with unsigned type
        for (size_t i = sizeof...(INDEXES) - 1; i != 0; --i) {
            index[i]->updateCopy(obj, index[0]);
        }
        index[0]->updateCopy(obj, index[0]);
    }

    FORCE_INLINE size_t count() const {
        return index[0]->count();
    }

    FORCE_INLINE void clear() {
        for (size_t i = sizeof...(INDEXES) - 1; i != 0; --i)
            index[i]->clear();
        index[0]->clear();
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
        ar << "\n\t\t";
        dbtoaster::serialize_nvp(ar, "count", count());
        //SBJ: Hack! fix it!  Cannot use store.foreach directly , as the last index may not be ListIndex created
        auto idx = const_cast<Index<T, V> *> (index[0]);
        idx->foreach([&ar] (T * e) {
            ar << "\n"; dbtoaster::serialize_nvp_tabbed(ar, "item", *e, "\t\t"); });
    }

    inline V getValueOrDefault(const T& key, int mainIdx = 0) const {
        return index[mainIdx]->getValueOrDefault(key);
    }

    inline void setOrDelOnZero(T& k, const V& v, const int mainIdx = 0) {
        HASH_RES_t h = index[mainIdx]->computeHash(k);
        switch (index[mainIdx]->setOrDelOnZero(k, v, h)) {
            case INSERT_INTO_MMAP:
                //                k.__av = v;
                insert_nocheck(k, h);
                break;
            case DELETE_FROM_MMAP:
                del(k, h);
                break;
            default:
                break;
        }
    }

    inline void addOrDelOnZero(T& k, const V& v, const int mainIdx = 0) {
        HASH_RES_t h = index[mainIdx]->computeHash(k);
        switch (index[mainIdx]->addOrDelOnZero(k, v, h)) {
            case INSERT_INTO_MMAP:
                //                k.__av = v;
                insert_nocheck(k, h);
                break;
            case DELETE_FROM_MMAP:
                del(k, h);
                break;
            default:
                break;
        }
    }
};

template <typename T, typename V, typename IDX_FN, bool is_unique>
class ListIndex : public Index<T, V> {

    struct Container {
        T* obj;
        Container* next;

        Container(T* o) : obj(o), next(nullptr) {
        }

    };
    Container *head, *tail;
    Pool<Container> nodes_;
public:

    ListIndex(Pool<T>* stPool = nullptr, size_t size = DEFAULT_CHUNK_SIZE) : head(nullptr), tail(nullptr), nodes_(size) {

    }

    FORCE_INLINE void add(T& obj) {
        add(&obj);
    }

    FORCE_INLINE void insert_nocheck(T* obj) {
        add(obj); //TODO: Fix later
    }

    FORCE_INLINE void add(T* obj, const size_t h) {
        auto idxId = Index<T, V>::idxId;
        Container *reusable = nullptr;
        if (is_unique && head != nullptr) {
            if (head->obj == obj || IDX_FN::cmp(*obj, *head->obj) == 0) {
                reusable = head;
                if (head == tail) {
                    head = tail = nullptr;
                } else {
                    head = head->next;
                    head->obj->backPtrs[idxId] = nullptr;
                }
            } else {
                Container *prv = head;
                Container *cur = head->next;
                while (cur != nullptr) {
                    if (obj == cur->obj || IDX_FN::cmp(*obj, *cur->obj) == 0) {
                        prv->next = cur->next;
                        if (cur->next)
                            cur->next->obj->backPtrs[idxId] = (void *) prv;
                        if (tail == cur)
                            tail = prv;
                        reusable = cur;
                        break;
                    }
                    prv = cur;
                    cur = cur->next;
                }
            }
        }
        Container *newc = reusable ? reusable : nodes_.add();
        //Adding previous container as backPointer , NOT it's own container!!
        obj->backPtrs[idxId] = (void *) tail;
        new (newc) Container(obj);
        if (tail != nullptr) {
            tail->next = newc;
            tail = newc;
        } else {
            head = newc;
            tail = newc;
        }
    }

    FORCE_INLINE void add(T* obj) {
        add(obj, 0);
    }

    FORCE_INLINE int addOrDelOnZero(const T& k, const V& v, const size_t hash_val) {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE int addOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void clear() {

        Container *cur = head, *next;
        while (cur != nullptr) {
            next = cur->next;
            nodes_.del(cur);
            cur = next;
        }

        head = tail = nullptr;
    }

    FORCE_INLINE size_t computeHash(const T& key) {
        return IDX_FN::hash(key);
    }

    FORCE_INLINE size_t count() {
        Container *cur = head;
        size_t cnt = 0;
        while (cur != nullptr) {
            cnt++;
            cur = cur->next;
        }
        return cnt;
    }

    FORCE_INLINE void del(T* obj, const size_t h) {
        auto idxId = Index<T, V>::idxId;
        //Assumes isUnique behaviour even though it is false
        if (head == nullptr) return;
        Container* prev = (Container *) obj->backPtrs[idxId];
        Container* cur;
        if (prev == nullptr) {
            cur = head;
            if (head == tail)
                head = tail = nullptr;
            else {
                head = head->next;
                head->obj->backPtrs[idxId] = nullptr;
            }
        } else {
            cur = prev->next;
            prev->next = cur->next;
            if (cur->next)
                cur->next->obj->backPtrs[idxId] = (void *) prev;
            if (cur == tail)
                tail = prev;
        }
        nodes_.del(cur);
    }

    FORCE_INLINE void del(T& obj, const size_t h) {
        del(&obj, h);
    }

    FORCE_INLINE void del(T* obj) {
        del(obj, 0);
    }

    FORCE_INLINE void del(T& obj) {
        del(&obj, 0);
    }

    FORCE_INLINE void foreach(std::function<void (T*) > f) {
        Container *cur = head;
        while (cur != nullptr) {
            f(cur->obj);
            cur = cur->next;
        }
    }

    //Not overloaded; const foreach

    FORCE_INLINE void foreach(std::function<void (const T*) > f) const {
        Container *cur = head;
        while (cur != nullptr) {
            f(cur->obj);
            cur = cur->next;
        }
    }

    FORCE_INLINE T* get(const T& key) const {
        Container *cur = head;
        while (cur != nullptr) {
            if (IDX_FN::cmp(key, *cur->obj) == 0)
                return cur->obj;
            cur = cur->next;
        }
        return nullptr;
    }

    FORCE_INLINE T* get(const T& key, const size_t h) const {
        return get(key);
    }

    FORCE_INLINE V getValueOrDefault(const T& key, const size_t hash_val) const {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE V getValueOrDefault(const T& key) const {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE bool hashDiffers(const T& x, const T& y) {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }

    FORCE_INLINE int setOrDelOnZero(const T& k, const V& v, const size_t hash_val0) {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE int setOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
    }

    inline void slice(const T& key, std::function<void (T*) > f) {

        Container *cur = head;
        while (cur != nullptr) {
            if (IDX_FN::cmp(key, *cur->obj) == 0)
                f(cur->obj);
            cur = cur->next;
        }
    }

    inline void sliceCopy(const T& key, std::function<void (T*) > f) {

        std::vector<T*> entries;
        Container *cur = head;
        while (cur != nullptr) {
            if (IDX_FN::cmp(key, *cur->obj) == 0)
                entries.push_back(cur->obj->copy());
            cur = cur->next;
        }
        for (auto it : entries) {
            f(it);
        }
    }

    FORCE_INLINE void update(T* obj) {
        //TODO: SBJ: Check
        if (is_unique) {

            del(obj);
            add(obj);
        }
    }

    bool operator==(const ListIndex<T, V, IDX_FN, is_unique>& right) const {
        HashIndex<T, V, IDX_FN, true> h1, h2;
        h1.idxId = h2.idxId = 0;
        foreach([&](const T * e) {
            h1.insert_nocheck(const_cast<T *> (e));
        });
        right.foreach([&](const T * e) {
            h2.insert_nocheck(const_cast<T *> (e));
        });
        return h1 == h2;
    }

    ~ListIndex() {
    }

};
#endif //MMAP_H
