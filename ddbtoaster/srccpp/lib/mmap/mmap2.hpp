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

#ifndef DEFAULT_HEAP_SIZE
#define DEFAULT_HEAP_SIZE 16
#endif

#define INSERT_INTO_MMAP 1
#define DELETE_FROM_MMAP -1

#define HASH_RES_t size_t

//#define DOUBLE_ZERO_APPROXIMATED
#define DOUBLE_ZERO_THRESHOLD 1e-8

#define FuncType const std::function<void (T*)>&

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
public:
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

    Pool(bool donotallocate): free_(nullptr), data_(nullptr) {

    }

    void initialize(size_t chunk_size) {
        size_ = chunk_size;
        add_chunk();
    }

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
    virtual bool hashDiffers(const T& x, const T& y) const = 0;

    virtual T* get(const T* key) const = 0;

    virtual void add(T* obj) = 0;

    virtual void del(T* obj) = 0;

    virtual void delCopy(const T* obj, Index<T, V>* primary) = 0;

    virtual void foreach(FuncType f) = 0;

    virtual void slice(const T* key, FuncType f) = 0;

    virtual void sliceCopy(const T* key, FuncType f) = 0;

    virtual void update(T* obj) = 0;

    virtual void updateCopy(T* obj, Index<T, V>* primary) = 0;

    virtual void updateCopyDependent(T* obj, T* elem) = 0;

    virtual size_t count() const = 0;

    virtual void clear() = 0;

    virtual void prepareSize(size_t arrayS, size_t poolS) = 0;

    virtual ~Index() {
    };
};

template<typename T, typename V, typename IDX_FN = T/* = GenericIndexFn<T>*/, bool is_unique = true >
class HashIndex : public Index<T, V> {
public:
    typedef IDX_FN IFN;

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
public:
    
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
                    na = &buckets_[h & (size_ - 1)];

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



    HashIndex(Pool<T>* stPool, size_t size, double load_factor = .75) : nodes_(size), allocated_from_pool_(false), zero(ZeroVal<V>().get()) {
        storePool = stPool;
        dataHead = nullptr;
        load_factor_ = 0.75;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
        resize_(size);
    }

    HashIndex(Pool<T>* stPool = nullptr) : nodes_(false), allocated_from_pool_(false), zero(ZeroVal<V>().get()) {
        storePool = stPool;
        dataHead = nullptr;
        load_factor_ = 0.75;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
    }

    void prepareSize(size_t arrayS, size_t poolS) override {
        resize_(arrayS);
        nodes_.initialize(poolS);
    }

    ~HashIndex() {
        if (buckets_ != nullptr) delete[] buckets_;
    }

    T& operator[](const T& key) {
        return *get(key);
    }

    void getSizeStats() {
        cout << "  array length  = " << size_;
        cout << "  pool size = " << nodes_.size_;
        cout << "  numElements = " << count_;
        cout << "  threshold = " << threshold_;
        size_t numInArray = 0;
        for (uint i = 0; i < size_; ++i) {
            if (buckets_[i].obj)
                numInArray++;
        }
        cout << "  numInArray = " << numInArray << endl;
    }

    void getBucketStats() {
        uint maxEntries = 0;
        uint maxSlices = 0;
        uint numBuckets = 0;
        uint numSlices = 0;
        uint numEntries = 0;

        for (size_t b = 0; b < size_; ++b) {
            IdxNode* n1 = &buckets_[b];
            if (!n1 -> obj)
                continue;
            numBuckets++;
            uint ns = 0;
            uint es = 0;
            IdxNode *n2 = n1;
            do {
                do {
                    ++es;
                } while ((n2 = n2->nxt) && n2->hash == n1->hash && !IDX_FN::cmp(*n1->obj, *n2->obj));
                ++ns;
            } while ((n1 = n2));
            if (es > maxEntries)
                maxEntries = es;
            if (ns > maxSlices)
                maxSlices = ns;
            numSlices += ns;
            numEntries += es;
        }
        assert(numEntries == count_);
        if (numBuckets == 0) {
            cerr << "Empty" << endl;
        } else {
            cerr << "IDX = " << Index<T, V>::idxId;
            cerr << "    Entries : total = " << numEntries << "  avg = " << numEntries / (1.0 * numBuckets) << " max = " << maxEntries;
            cerr << "    Slices : total = " << numSlices << "  avg = " << numSlices / (1.0 * numBuckets) << "  max = " << maxSlices << "!" << endl;
            //            cerr << "   count_ = " << count_

        }
    }

    bool operator==(const HashIndex<T, V, IDX_FN, is_unique> & that) const {
        bool check = true;
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
                check = false;
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
                    check = false;
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
                    check = false;
                    //                    return false;
                }
            } while ((n2 = n2->nxt));
        }
        return check;
    }

    FORCE_INLINE IdxNode* sliceRes(const T* key) {
        return sliceRes(*key);
    }

    FORCE_INLINE IdxNode* sliceRes(const T& key) {
        HASH_RES_t h = IDX_FN::hash(key);
        IdxNode* n = &(buckets_[h & (size_ - 1)]);
        if (n->obj)
            do {
                if (h == n->hash && !IDX_FN::cmp(key, *n->obj)) {
                    return n;
                }
            } while ((n = n->nxt));
        return nullptr;
    }

    FORCE_INLINE void sliceResMap(const T* key, FuncType f, IdxNode* n) {
        sliceResMap(*key, f, n);
    }

    FORCE_INLINE void sliceResMap(const T& key, FuncType f, IdxNode* n) {
        HASH_RES_t h = n->hash;
        do {
            if (h == n->hash && !IDX_FN::cmp(key, *n->obj))
                f(n->obj);
        } while ((n = n->nxt));
    }

    FORCE_INLINE T* foreachRes() {
        return dataHead;
    }

    FORCE_INLINE void foreachResMap(FuncType f, T* cur) {
        while (cur) {
            f(cur);
            cur = cur->nxt;
        }
    }

    /********************    virtual functions *******************************/

    FORCE_INLINE bool hashDiffers(const T& x, const T& y) const override {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }

    // retrieves the first element equivalent to the key or nullptr if not found

    FORCE_INLINE T* get(const T* key) const override {
        HASH_RES_t h = IDX_FN::hash(*key);
        IdxNode* n = &buckets_[h & (size_ - 1)];
        do {
            if (n->obj && h == n->hash && !IDX_FN::cmp(*key, *n->obj)) return n->obj;
        } while ((n = n->nxt));
        return nullptr;
    }

    FORCE_INLINE void add(T* obj) override {
        HASH_RES_t h = IDX_FN::hash(*obj);
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
        size_t b = h & (size_ - 1);
        IdxNode* n = &buckets_[b];
        IdxNode* nw;
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

    }

    // deletes an existing element (equality by pointer comparison)

    FORCE_INLINE void del(T* obj) override {
        auto idxId = Index<T, V>::idxId;
        if (idxId == 0) {
            T *elemPrv = obj->prv, *elemNxt = obj->nxt;
            if (elemPrv)
                elemPrv->nxt = elemNxt;
            else
                dataHead = elemNxt;
            if (elemNxt) elemNxt->prv = elemPrv;

            obj->nxt = nullptr;
            obj->prv = nullptr;
        }
        IdxNode *n = (IdxNode *) obj->backPtrs[idxId];
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
        --count_;

    }

    FORCE_INLINE void delCopy(const T* obj, Index<T, V>* primary) override {
        T* orig = primary->get(obj);
        del(orig);
    }

    FORCE_INLINE void foreach(FuncType f) override {
        T* cur = dataHead;
        while (cur) {
            f(cur);
            cur = cur->nxt;
        }
    }

    FORCE_INLINE void slice(const T* key, FuncType f) override {
        HASH_RES_t h = IDX_FN::hash(*key);
        IdxNode* n = &(buckets_[h & (size_ - 1)]);
        if (n->obj)
            do {
                if (h == n->hash && !IDX_FN::cmp(*key, *n->obj)) {
                    f(n->obj);
                }
            } while ((n = n->nxt));
    }

    FORCE_INLINE void sliceCopy(const T* key, FuncType f) override {
        HASH_RES_t h = IDX_FN::hash(*key);
        std::vector<T*> entries;
        IdxNode* n = &(buckets_[h & (size_ - 1)]);
        if (n->obj)
            do {
                if (h == n->hash && !IDX_FN::cmp(*key, *n->obj)) {
                    T* temp = n->obj->copy();
                    entries.push_back(temp);
                }
            } while ((n = n->nxt));
        for (auto it : entries) {
            f(it);
        }
    }

    FORCE_INLINE void update(T* elem) override {
        //        HASH_RES_t h = IDX_FN::hash(*elem);
        //        IdxNode* n = &(buckets_[h & (size_ - 1)]);
        if (is_unique) {
            // ???
        } else {
            // ???
        }
    }

    /*Ideally, we should check if the hash changes and then delete and insert.
     *  However, in the cases where we use it, hash does not change, so to have
     *   an impact, deleted and insert in all cases  */
    FORCE_INLINE void updateCopyDependent(T* obj, T* orig) override {
        del(orig);
        add(obj);
    }

    FORCE_INLINE void updateCopy(T* obj, Index<T, V>* primaryIdx) override {
        T* orig = primaryIdx->get(obj);
        del(orig);
        add(obj);
    }

    FORCE_INLINE size_t count() const override {
        return count_;
    }

    FORCE_INLINE void clear() override {
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

    /******************* non-virtual function wrappers ************************/

    FORCE_INLINE T* get(const T& key) const {
        return get(&key);
    }

    FORCE_INLINE T* getCopy(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopy(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE void slice(const T& key, FuncType f) {
        slice(&key, f);
    }

    FORCE_INLINE void sliceCopy(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T* key, FuncType f) {
        sliceCopy(key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void delCopyDependent(const T* obj) {
        del(obj);
    }

    template<typename TP, typename VP, typename...INDEXES> friend class MultiHashMap;
};

template<typename T, typename V, typename IDX_FN1, typename IDX_FN2, bool is_max>
class SlicedHeapIndex : public Index<T, V> {

    struct __IdxHeapNode {
        T** array;
        uint arraySize;
        uint size;
        HASH_RES_t hash;
        __IdxHeapNode * nxt;

        __IdxHeapNode() {
            arraySize = DEFAULT_HEAP_SIZE;
            array = new T*[arraySize];
            size = 0;
        }

        void checkHeap(int idx) {
            for (uint i = 1; i <= size; ++i) {
                uint l = 2 * i;
                uint r = l + 1;
                T* x = array[i];

                if (is_max) {
                    if (l <= size) {
                        assert(IDX_FN2::cmp(*x, *array[l]) == 1);
                        if (r <= size)
                            assert(IDX_FN2::cmp(*x, *array[r]) == 1);
                    }
                } else {
                    if (l <= size) {
                        assert(IDX_FN2::cmp(*x, *array[l]) == -1);
                        if (r <= size)
                            assert(IDX_FN2::cmp(*x, *array[r]) == -1);
                    }
                }
                assert(x->backPtrs[idx] == this);
            }
        }

        FORCE_INLINE void double_() {

            uint newsize = arraySize << 1;
            T** temp = new T*[newsize];
            mempcpy(temp, array, arraySize * sizeof (T*));
            arraySize = newsize;
            delete[] array;
            array = temp;
        }

        FORCE_INLINE void percolateDown(uint holeInput) {
            uint hole = holeInput;
            uint child = hole << 1;
            T* tmp = array[hole];
            while (child <= size) {
                if (child != size && IDX_FN2::cmp(*array[child + 1], *array[child]) == (is_max ? 1 : -1))
                    child++;
                if (IDX_FN2::cmp(*array[child], *tmp) == (is_max ? 1 : -1))
                    array[hole] = array[child];
                else {
                    array[hole] = tmp;

                    return;
                }
                hole = child;
                child = hole << 1;
            }
            array[hole] = tmp;
        }

        FORCE_INLINE void add(T* e) {
            if (size == arraySize - 1) double_();
            size++;
            uint hole = size;
            uint h = size >> 1;
            while (hole > 1 && IDX_FN2::cmp(*e, *array[h]) == (is_max ? 1 : -1)) {

                array[hole] = array[h];
                hole = h;
                h = hole >> 1;
            }
            array[hole] = e;
        }

        FORCE_INLINE void remove(T* e) {
            uint p = 1;
            if (array[p] != e) {
                p++;
                while (p <= size) {
                    if (array[p] == e)
                        break;
                    p++;
                }
                if (p == size + 1)
                    return;
            }
            array[p] = array[size];
            array[size] = nullptr;
            size--;

            if (p < size)
                percolateDown(p);
        }
    };

    typedef __IdxHeapNode* IdxNode;

    //    Pool<IdxEquivNode> equiv_nodes_;
    //    Pool<__IdxHeapNode> nodes_;
    const V zero;
    size_t count_, threshold_;
    double load_factor_;

    void resize_(size_t new_size) {
        IdxNode *old = buckets_;
        size_t sz = size_;
        buckets_ = new IdxNode[new_size];
        memset(buckets_, 0, sizeof (IdxNode) * new_size);
        size_ = new_size;
        threshold_ = size_ * load_factor_;
        for (size_t b = 0; b < sz; ++b) {
            IdxNode q = old[b];
            while (q != nullptr) {
                IdxNode nq = q->nxt;
                uint b = q->hash & (size_ - 1);
                q->nxt = buckets_[b];
                buckets_[b] = q;
                q = nq;
            }
        }

        if (old) delete[] old;
    }
public:

    void getSizeStats() {
        cout << "  array length = " << size_;
        uint maxSize = 0;
        uint numHeaps = 0;
        uint numInArray = 0;
        uint nE = 0;
        for (uint i = 0; i < size_; ++i) {
            if (buckets_[i]) {
                numInArray++;
                auto cur = buckets_[i];
                do {
                    if (cur->arraySize > maxSize)
                        maxSize = cur->arraySize;
                    numHeaps++;
                    nE += cur->size;
                } while ((cur = cur->nxt));
            }
        }
        cout << "  num Heaps = " << numHeaps;
        cout << "  count = " << count_;
        cout << "  numElements = " << nE;
        cout << "  numInArray = " << numInArray;
        cout << "  maxHeapSize = " << maxSize << endl;
    }

    SlicedHeapIndex(Pool<T>* stPool, size_t size , double load_factor = .75) : zero(ZeroVal<V>().get()) {

        load_factor_ = load_factor;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
        resize_(size);

    }

    SlicedHeapIndex(Pool<T>* stPool = nullptr) : zero(ZeroVal<V>().get()) {
        load_factor_ = 0.75;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
    }

    void prepareSize(size_t arrayS, size_t poolS) override {
        resize_(arrayS);
    }

    IdxNode* buckets_;
    size_t size_;

    /********************    virtual functions *******************************/

    FORCE_INLINE bool hashDiffers(const T& x, const T& y) const override {
        return IDX_FN1::hash(x) != IDX_FN1::hash(y);
    }

    FORCE_INLINE T* get(const T* key) const override {
        HASH_RES_t h = IDX_FN1::hash(*key);
        IdxNode n = buckets_[h & (size_ - 1)];
        //        if (n) n->checkHeap(Index<T, V>::idxId);
        while (n != nullptr) {
            T* obj;
            if (n->hash == h && IDX_FN1::cmp(*key, *(obj = n->array[1])) == 0) {
                return obj;
            }
            n = n->nxt;
        }
        return nullptr;
    }

    FORCE_INLINE void add(T* obj) override {
        HASH_RES_t h = IDX_FN1::hash(*obj);
        if (count_ > threshold_) {
            //            std::cerr << "  Index resize count=" << count_ << "  size=" << size_ << std::endl;
            //            exit(1);
            resize_(size_ << 1);
        }
        size_t b = h & (size_ - 1);
        IdxNode q = buckets_[b];
        while (q != nullptr) {
            if (q->hash == h && IDX_FN1::cmp(*obj, *q->array[1]) == 0) {
                //                q->checkHeap(Index<T, V>::idxId);
                q->add(obj);
                obj->backPtrs[Index<T, V>::idxId] = q;
                //                q->checkHeap(Index<T, V>::idxId);
                return;
            }
            q = q->nxt;
        }
        q = new __IdxHeapNode();
        q->hash = h;
        q->nxt = buckets_[b];
        q->add(obj);
        obj->backPtrs[Index<T, V>::idxId] = q;
        //        q->checkHeap(Index<T, V>::idxId);
        buckets_[b] = q;
        count_++;
    }

    FORCE_INLINE void del(T* obj) override {
        IdxNode q = (IdxNode) obj->backPtrs[Index<T, V>::idxId];
        //        q->checkHeap(Index<T, V>::idxId);
        q->remove(obj);
        //        q->checkHeap(Index<T, V>::idxId);
        if (q->size == 0) {
            assert(q->array[1] == nullptr);
            auto h = q->hash;
            size_t b = h & (size_ - 1);
            IdxNode p = buckets_[b];
            if (p == q) {
                buckets_[b] = q->nxt;
                count_--;
                delete q;
                return;
            } else {
                while (p != nullptr) {
                    if (p->nxt == q) {
                        p->nxt = q->nxt;
                        count_--;
                        delete q;

                        return;
                    }
                    p = p->nxt;
                }
            }

        }

    }

    FORCE_INLINE void delCopy(const T* obj, Index<T, V>* primary) override {
        T* orig = primary->get(obj);
        del(orig);
    }

    FORCE_INLINE void foreach(FuncType f) override {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void slice(const T* key, FuncType f) override {
        throw std::logic_error("Not implemented");
        //TODO: implement.  traversal type?
    }

    FORCE_INLINE void sliceCopy(const T* key, FuncType f) override {

        throw std::logic_error("Not implemented");
        //TODO: implement.  traversal type?
    }

    FORCE_INLINE void update(T* elem) override {
        //Do nothing for now
    }

    /*Ideally, we should check if the hash changes and then delete and insert.
     *  However, in the cases where we use it, hash does not change, so to have
     *   an impact, deleted and insert in all cases  */
    FORCE_INLINE void updateCopyDependent(T* obj, T* orig) override {
        del(orig);
        add(obj);
    }

    FORCE_INLINE void updateCopy(T* obj, Index<T, V>* primaryIdx) override {
        T* orig = primaryIdx->get(obj);
        del(orig);
        add(obj);

    }

    FORCE_INLINE size_t count() const override {
        return count_;
    }

    FORCE_INLINE void clear() override {
        throw std::logic_error("Not implemented");
    }

    /******************* non-virtual function wrappers ************************/

    FORCE_INLINE T* get(const T& key) const {
        return get(&key);
    }

    FORCE_INLINE T* getCopy(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopy(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE void slice(const T& key, FuncType f) {
        slice(&key, f);
    }

    FORCE_INLINE void sliceCopy(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T* key, FuncType f) {
        sliceCopy(key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void delCopyDependent(const T* obj) {
        del(obj);
    }
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
                    na = &buckets_[h & (size_ - 1)];
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

    TreeIndex(Pool<T>* stPool , size_t size , double load_factor = .75) : equiv_nodes_(size), nodes_(size), zero(ZeroVal<V>().get()) {
        load_factor_ = load_factor;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
        resize_(size);

    }

    TreeIndex(Pool<T>* stPool = nullptr) : equiv_nodes_(false), nodes_(false), zero(ZeroVal<V>().get()) {
        load_factor_ = 0.75;
        size_ = 0;
        count_ = 0;
        buckets_ = nullptr;
    }

    void prepareSize(size_t arrayS, size_t poolS) override {
        nodes_.initialize(poolS);
        equiv_nodes_.initialize(poolS);
        resize_(arrayS);
    }

    ~TreeIndex() {
        if (buckets_ != nullptr) delete[] buckets_;
    }

    void printTree(const T& key) {
        std::cout << "--------------------------" << std::endl;
        HASH_RES_t h = IDX_FN1::hash(key);
        IdxNode* n = &(buckets_[h & (size_ - 1)]);

        do {
            if (n->equivNodes && h == n->hash && !IDX_FN1::cmp(key, *n->equivNodes->obj)) {
                IdxEquivNode* curr = n->equivNodes;

                printTreePreorder(curr, 0);
                return;
            }
        } while ((n = n->nxt));
        std::cout << "--------------------------" << std::endl;
    }

    /********************    virtual functions *******************************/

    FORCE_INLINE bool hashDiffers(const T& x, const T& y) const override {
        return IDX_FN1::hash(x) != IDX_FN1::hash(y);
    }

    FORCE_INLINE T* get(const T* key) const override {
        HASH_RES_t h = IDX_FN1::hash(key);
        IdxNode* n = &(buckets_[h & (size_ - 1)]);

        do {
            if (n->equivNodes && h == n->hash && !IDX_FN1::cmp(*key, *n->equivNodes->obj)) {
                IdxEquivNode* curr = n->equivNodes;
                while (curr->left) curr = curr->left;
                return curr->obj;
            }
        } while ((n = n->nxt));
        return nullptr;
    }

    // inserts regardless of whether element exists already

    FORCE_INLINE void add(T* obj) override {
        HASH_RES_t h = IDX_FN1::hash(*obj);
        if (count_ > threshold_) {
            std::cerr << "  Index resize count=" << count_ << "  size=" << size_ << std::endl;
            exit(1);
            //resize_(size_ << 1);
        }
        size_t b = h & (size_ - 1);
        IdxNode* n = &buckets_[b];
        IdxNode* nw;

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

    FORCE_INLINE void del(T* obj) override {
        HASH_RES_t h = IDX_FN1::hash(*obj);
        IdxNode *n = &buckets_[h & (size_ - 1)];
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

    FORCE_INLINE void delCopy(const T* obj, Index<T, V>* primary) override {
        T* orig = primary->get(obj);
        del(orig);
    }

    FORCE_INLINE void foreach(FuncType f) override {
        throw std::logic_error("Not implemented");
        //TODO: implement
    }

    FORCE_INLINE void slice(const T* key, FuncType f) override {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void sliceCopy(const T* key, FuncType f) override {
        throw std::logic_error("Not implemented");
        //TODO: implement.  traversal type?
    }

    FORCE_INLINE void update(T* elem) override {
        //Do nothing for now
    }

    /*Ideally, we should check if the hash changes and then delete and insert.
     *  However, in the cases where we use it, hash does not change, so to have
     *   an impact, deleted and insert in all cases  */
    FORCE_INLINE void updateCopyDependent(T* obj, T* orig) {
        del(orig);
        add(obj);
    }

    FORCE_INLINE void updateCopy(T* obj, Index<T, V>* primaryIdx) {
        T* orig = primaryIdx->get(obj);
        del(orig);
        add(obj);
    }

    FORCE_INLINE size_t count() const override {
        return count_;
    }

    FORCE_INLINE void clear() override {
        throw std::logic_error("Not implemented");
    }

    /******************* non-virtual function wrappers ************************/

    FORCE_INLINE T* get(const T& key) const {
        return get(&key);
    }

    FORCE_INLINE T* getCopy(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopy(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE void slice(const T& key, FuncType f) {
        slice(&key, f);
    }

    FORCE_INLINE void sliceCopy(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T* key, FuncType f) {
        sliceCopy(key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void delCopyDependent(const T* obj) {
        del(obj);
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

    void prepareSize(size_t arrayS, size_t poolS) override {
        //DO NOTHING
    }

    void resize_( size_t newsize) {
        //DO NOTHING
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

    /********************    virtual functions *******************************/

    FORCE_INLINE bool hashDiffers(const T& x, const T& y) const override {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }

    FORCE_INLINE T* get(const T* key) const override {
        HASH_RES_t idx = IDX_FN::hash(*key);
        if (idx >= 0 && idx < size && isUsed[idx]) //TODO: remove check
            return array[idx];
        return nullptr;
    }

    FORCE_INLINE void add(T* obj) override {
        auto idxId = Index<T, V>::idxId;
        HASH_RES_t idx = IDX_FN::hash(*obj);
        isUsed[idx] = true;
        obj->backPtrs[idxId] = (void *) &(array[idx]);
        array[idx] = obj;
    }

    FORCE_INLINE void del(T* obj) override {
        HASH_RES_t idx = IDX_FN::hash(*obj);
        isUsed[idx] = false;
    }

    FORCE_INLINE void delCopy(const T* obj, Index<T, V>* primary) override {
        T* orig = primary->get(obj);
        del(orig);
    }

    FORCE_INLINE void foreach(FuncType f) override {
        for (size_t b = 0; b < size; ++b) {
            if (isUsed[b])
                f(array[b]);
        }
    }

    FORCE_INLINE void slice(const T* key, FuncType f) override {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void sliceCopy(const T* key, FuncType f) override {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void update(T* obj) override {
        //Do nothing
    }

    /*Ideally, we should check if the hash changes and then delete and insert.
     *  However, in the cases where we use it, hash does not change, so to have
     *   an impact, deleted and insert in all cases  */
    FORCE_INLINE void updateCopyDependent(T* obj, T* orig) {
        del(orig);
        add(obj);
    }

    FORCE_INLINE void updateCopy(T* obj, Index<T, V>* primaryIdx) {
        T* orig = primaryIdx->get(obj);
        del(orig);
        add(obj);
    }

    FORCE_INLINE size_t count() const override {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void clear() override {
        for (size_t b = 0; b < size; ++b)
            isUsed[b] = false;
    }

    /******************* non-virtual function wrappers ************************/

    FORCE_INLINE T* get(const T& key) const {
        return get(&key);
    }

    FORCE_INLINE T* getCopy(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopy(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE void slice(const T& key, FuncType f) {
        slice(&key, f);
    }

    FORCE_INLINE void sliceCopy(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T* key, FuncType f) {
        sliceCopy(key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void delCopyDependent(const T* obj) {
        del(obj);
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

    ListIndex(Pool<T>* stPool, size_t size) : head(nullptr), tail(nullptr), nodes_(size) {

    }

    ListIndex(Pool<T>* stPool = nullptr) : head(nullptr), tail(nullptr), nodes_(false) {

    }
    void prepareSize(size_t arrayS, size_t poolS) override {
        nodes_->initialize(poolS);
    }

    bool operator==(const ListIndex<T, V, IDX_FN, is_unique>& right) const {
        HashIndex<T, V, IDX_FN, true> h1, h2;
        h1.idxId = h2.idxId = 0;
        foreach([&](const T * e) {
            h1.add(const_cast<T *> (e));
        });
        right.foreach([&](const T * e) {
            h2.add(const_cast<T *> (e));
        });
        return h1 == h2;
    }

    ~ListIndex() {
    }
    //Not overloaded; const foreach

    FORCE_INLINE void foreach(std::function<void (const T*) > f) const {
        Container *cur = head;
        while (cur != nullptr) {
            f(cur->obj);
            cur = cur->next;
        }
    }

    /********************    virtual functions *******************************/
    FORCE_INLINE bool hashDiffers(const T& x, const T& y) const override {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }

    FORCE_INLINE T* get(const T* key) const override {
        Container *cur = head;
        while (cur != nullptr) {
            if (IDX_FN::cmp(*key, *cur->obj) == 0)
                return cur->obj;
            cur = cur->next;
        }
        return nullptr;
    }

    FORCE_INLINE void add(T* obj) override {
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

    FORCE_INLINE void del(T* obj) override {
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

    FORCE_INLINE void delCopy(const T* obj, Index<T, V>* primary) override {
        T* orig = primary->get(obj);
        del(orig);
    }

    FORCE_INLINE void foreach(FuncType f) override {
        Container *cur = head;
        while (cur != nullptr) {
            f(cur->obj);
            cur = cur->next;
        }
    }

    FORCE_INLINE void slice(const T* key, FuncType f) override {
        Container *cur = head;
        while (cur != nullptr) {
            if (IDX_FN::cmp(*key, *cur->obj) == 0)
                f(cur->obj);
            cur = cur->next;
        }
    }

    FORCE_INLINE void sliceCopy(const T* key, FuncType f) override {

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

    FORCE_INLINE void update(T* obj) override {
        //TODO: SBJ: Check
        if (is_unique) {

            del(obj);
            add(obj);
        }
    }

    /*Ideally, we should check if the hash changes and then delete and insert.
     *  However, in the cases where we use it, hash does not change, so to have
     *   an impact, deleted and insert in all cases  */
    FORCE_INLINE void updateCopyDependent(T* obj, T* orig) {
        del(orig);
        add(obj);
    }

    FORCE_INLINE void updateCopy(T* obj, Index<T, V>* primaryIdx) {
        T* orig = primaryIdx->get(obj);
        del(orig);
        add(obj);
    }

    FORCE_INLINE size_t count() const override {
        Container *cur = head;
        size_t cnt = 0;
        while (cur != nullptr) {
            cnt++;
            cur = cur->next;
        }
        return cnt;
    }

    FORCE_INLINE void clear() override {
        Container *cur = head, *next;
        while (cur != nullptr) {
            next = cur->next;
            nodes_.del(cur);
            cur = next;
        }

        head = tail = nullptr;
    }

    /******************* non-virtual function wrappers ************************/

    FORCE_INLINE T* get(const T& key) const {
        return get(&key);
    }

    FORCE_INLINE T* getCopy(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopy(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T* key) const {
        T* obj = get(key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T& key) const {
        T* obj = get(&key);
        return obj ? obj->copy() : nullptr;
    }

    FORCE_INLINE void slice(const T& key, FuncType f) {
        slice(&key, f);
    }

    FORCE_INLINE void sliceCopy(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T* key, FuncType f) {
        sliceCopy(key, f);
    }

    FORCE_INLINE void sliceCopyDependent(const T& key, FuncType f) {
        sliceCopy(&key, f);
    }

    FORCE_INLINE void delCopyDependent(const T* obj) {
        del(obj);
    }

};

template<typename T, typename V, typename...INDEXES>
class MultiHashMap {
private:

    bool *modified;
public:
    Pool<T> pool;
    Index<T, V>** index;

    MultiHashMap() { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES(&pool, DEFAULT_CHUNK_SIZE)...
        };
        modified = new bool[sizeof...(INDEXES)];
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            index[i]->idxId = i;
            modified[i] = false;
        }
    }

    MultiHashMap(const size_t* arrayLengths, const size_t* poolSizes) : pool(poolSizes[0]) { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES(&pool)...
        };
        modified = new bool[sizeof...(INDEXES)];
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            index[i]->prepareSize(arrayLengths[i], poolSizes[i + 1]);
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

    FORCE_INLINE T* get(const T& key, const size_t idx = 0) const {
        return index[idx]->get(&key);
    }

    FORCE_INLINE T* get(const T* key, const size_t idx = 0) const {
        return index[idx]->get(key);
    }

    FORCE_INLINE T* getCopy(const T& key, const size_t idx = 0) const {
        T* ref = index[idx]->get(&key);
        return ref ? ref->copy() : nullptr;
    }

    FORCE_INLINE T* getCopy(const T* key, const size_t idx = 0) const {
        T* ref = index[idx]->get(key);
        return ref ? ref->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T* key, const size_t idx = 0) const {
        T* ref = index[idx]->get(key);
        return ref ? ref->copy() : nullptr;
    }

    FORCE_INLINE T* getCopyDependent(const T& key, const size_t idx = 0) const {
        T* ref = index[idx]->get(&key);
        return ref ? ref->copy() : nullptr;
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

    FORCE_INLINE void add(const T* elem) {
        T* cur = index[0]->get(elem);
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

    FORCE_INLINE void insert_nocheck(const T& elem) {
        insert_nocheck(&elem);
    }

    FORCE_INLINE void insert_nocheck(const T* elem) {
        T* cur = copyIntoPool(elem);
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
    }

    FORCE_INLINE void del(T* elem) { // assume that the element is already in the map
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
        pool.del(elem);
    }

    FORCE_INLINE void delCopyDependent(T* obj) {
        T* elem = index[0]->get(obj);
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
        pool.del(elem);
    }

    FORCE_INLINE void delCopy(T* obj) {
        T* elem = index[0]->get(obj);
        for (size_t i = sizeof...(INDEXES) - 1; i != 0; --i)
            index[i]->delCopy(obj, index[0]);
        index[0]->delCopy(obj, index[0]);
        pool.del(elem);
    }

    FORCE_INLINE void foreach(FuncType f) {
        index[0]->foreach(f);
    }

    void slice(int idx, const T* key, FuncType f) {
        index[idx]->slice(key, f);
    }

    void slice(int idx, const T& key, FuncType f) {
        index[idx]->slice(&key, f);
    }

    void sliceCopy(int idx, const T* key, FuncType f) {
        index[idx]->sliceCopy(key, f);
    }

    void sliceCopy(int idx, const T& key, FuncType f) {
        index[idx]->sliceCopy(&key, f);
    }

    void sliceCopyDependent(int idx, const T* key, FuncType f) {
        index[idx]->sliceCopy(key, f);
    }

    void sliceCopyDependent(int idx, const T& key, FuncType f) {
        index[idx]->sliceCopy(&key, f);
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
        T* elem = index[0]->get(obj2);
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
};

#endif //MMAP_H
