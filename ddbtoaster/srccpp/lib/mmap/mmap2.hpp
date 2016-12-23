#ifndef MMAP_H
#define MMAP_H

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

    virtual bool isZero(V a) {
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
    virtual bool hashDiffers(const T& x, const T& y) = 0;

    virtual T* get(const T& key) const = 0;

    virtual T* get(const T& key, const HASH_RES_t h) const = 0;

    virtual V getValueOrDefault(const T& key) const = 0;

    virtual V getValueOrDefault(const T& key, const HASH_RES_t hash_val) const = 0;

    virtual int setOrDelOnZero(const T& k, const V& v) = 0;

    virtual int setOrDelOnZero(const T& k, const V& v, const HASH_RES_t hash_val0) = 0;

    virtual int addOrDelOnZero(const T& k, const V& v) = 0;

    virtual int addOrDelOnZero(const T& k, const V& v, const HASH_RES_t hash_val) = 0;

    virtual void add(T& obj) = 0;

    virtual void add(T* obj) = 0;

    virtual void add(T* obj, const HASH_RES_t h) = 0;

    virtual void del(const T& obj) = 0;

    virtual void del(const T& obj, const HASH_RES_t h) = 0;

    virtual void del(const T* obj) = 0;

    virtual void del(const T* obj, const HASH_RES_t h) = 0;

    virtual void foreach(std::function<void (const T&) > f) const = 0;

    virtual void slice(const T& key, std::function<void (const T&) > f) = 0;

    virtual void update(T* obj) = 0;

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
        struct __IdxNode* nxt;
    } IdxNode; //  the linked list is maintained 'compactly': if a IdxNode has a nxt, it is full.
    IdxNode* buckets_;
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
                        nw->obj = na->obj;
                        na->hash = h;
                        na->obj = n->obj;
                        nw->nxt = na->nxt;
                        na->nxt = nw;
                    } else { // space left in last IdxNode
                        na->hash = h;
                        na->obj = n->obj; //na->nxt=nullptr;
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

    HashIndex(size_t size = DEFAULT_CHUNK_SIZE, double load_factor = .75) : nodes_(size), allocated_from_pool_(false), zero(ZeroVal<V>().get()) {
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
                return false;
            }
            if (!n1->obj)
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

    FORCE_INLINE virtual bool hashDiffers(const T& x, const T& y) {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }
    // retrieves the first element equivalent to the key or nullptr if not found

    inline T* get(const T* key) const {
        return get(*key);
    }

    inline virtual T* get(const T& key) const {
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

    inline virtual T* get(const T& key, const HASH_RES_t h) const {
        IdxNode* n = &buckets_[h % size_];
        do {
            if (n->obj && h == n->hash && !IDX_FN::cmp(key, *n->obj)) return n->obj;
        } while ((n = n->nxt));
        return nullptr;
    }

    // inserts regardless of whether element exists already

    FORCE_INLINE virtual void add(T& obj) {
        add(&obj);
    }

    FORCE_INLINE virtual void add(T* obj) {
        HASH_RES_t h = IDX_FN::hash(*obj);
        add(obj, h);
    }

    FORCE_INLINE virtual void add(T* obj, const HASH_RES_t h) {
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
                nw->obj = obj;
                nw->nxt = n->nxt;
                n->nxt = nw;
            } else { // space left in last IdxNode
                n->hash = h;
                n->obj = obj; //n->nxt=nullptr;
            }
        } else {
            // ++count_;
            if (!n->obj) { // space left in last IdxNode
                ++count_;
                n->hash = h;
                n->obj = obj; //n->nxt=nullptr;
                return;
            }
            do {
                if (h == n->hash && !IDX_FN::cmp(*obj, *n->obj)) {
                    allocated_from_pool_ = true;
                    nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
                    nw->hash = h;
                    nw->obj = obj;
                    nw->nxt = n->nxt;
                    n->nxt = nw;
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
            nw->obj = n->obj;
            n->hash = h;
            n->obj = obj;
            nw->nxt = n->nxt;
            n->nxt = nw;
            // return;
            // }
        }
    }

    // deletes an existing elements (equality by pointer comparison)

    FORCE_INLINE virtual void del(const T& obj) {
        const T* ptr = get(obj);
        if (ptr) del(ptr);
    }

    FORCE_INLINE virtual void del(const T& obj, const HASH_RES_t h) {
        const T* ptr = get(obj, h);
        if (ptr) del(ptr, h);
    }

    FORCE_INLINE virtual void del(const T* obj) {
        HASH_RES_t h = IDX_FN::hash(*obj);
        del(obj, h);
    }

    FORCE_INLINE virtual void del(const T* obj, const HASH_RES_t h) {
        IdxNode *n = &buckets_[h % size_];
        IdxNode *prev = nullptr, *next; // previous and next pointers
        do {
            next = n->nxt;
            if (/*n->obj &&*/ n->obj == obj) { //we only need a pointer comparison, as all objects are stored in the pool
                if (prev) { //it is an element in the linked list (and not in the bucket itself)
                    prev->nxt = next;
                    // n->nxt = nullptr;
                    // n->obj = nullptr;
                    nodes_.del(n);
                } else if (next) { //it is the elements in the bucket, and there are other elements in linked list
                    n->obj = next->obj;
                    n->hash = next->hash;
                    n->nxt = next->nxt;
                    nodes_.del(next);
                    next = n;
                } else { //it is the only element in the bucket
                    n->obj = nullptr;
                }
                if (is_unique || !((prev && prev->obj && (h == prev->hash) && !IDX_FN::cmp(*obj, *prev->obj)) ||
                        (next && next->obj && (h == next->hash) && !IDX_FN::cmp(*obj, *next->obj)))) --count_;
                return;
            }
            prev = n;
        } while ((n = next));
    }

    inline virtual void foreach(std::function<void (const T&) > f) const {
        for (size_t b = 0; b < size_; ++b) {
            IdxNode* n = &buckets_[b];
            do {
                if (n->obj) f(*n->obj);
            } while ((n = n->nxt));
        }
    }

    inline void update(T* elem) override {
        //DO Nothing for now
    }

    inline void slice(const T* key, std::function<void (const T&) > f) {
        return slice(*key, f);
    }

    inline virtual void slice(const T& key, std::function<void (const T&) > f) {
        HASH_RES_t h = IDX_FN::hash(key);
        IdxNode* n = &(buckets_[h % size_]);
        do {
            if (n->obj && h == n->hash && !IDX_FN::cmp(key, *n->obj)) {
                do {
                    f(*n->obj);
                } while ((n = n->nxt) && (h == n->hash) && !IDX_FN::cmp(key, *n->obj));
                return;
            }
        } while ((n = n->nxt));
    }

    inline virtual void clear() {
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
    }

    FORCE_INLINE virtual size_t count() {
        return count_;
    }

    FORCE_INLINE virtual HASH_RES_t computeHash(const T& key) {
        return IDX_FN::hash(key);
    }

    inline virtual V getValueOrDefault(const T& key) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    inline virtual V getValueOrDefault(const T& key, HASH_RES_t h) const {
        throw std::logic_error("Not implemented");
        return zero;
    }

    inline virtual int setOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    inline virtual int setOrDelOnZero(const T& k, const V& v, HASH_RES_t h) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    inline virtual int addOrDelOnZero(const T& k, const V& v) {
        throw std::logic_error("Not implemented");
        return 0;
    }

    inline virtual int addOrDelOnZero(const T& k, const V& v, HASH_RES_t h) {
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

    TreeIndex(size_t size = DEFAULT_CHUNK_SIZE, double load_factor = .75) : equiv_nodes_(size), nodes_(size), zero(ZeroVal<V>().get()) {
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

    FORCE_INLINE virtual void add(T& obj) override {
        add(& obj);
    }

    FORCE_INLINE virtual void add(T* obj) override {
        HASH_RES_t h = IDX_FN1::hash(*obj);
        add(obj, h);
    }

    FORCE_INLINE virtual void add(T* obj, const HASH_RES_t h) override {
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

    FORCE_INLINE virtual void del(const T* obj) override {
        HASH_RES_t h = IDX_FN1::hash(*obj);
        del(obj, h);
    }

    FORCE_INLINE virtual void del(const T* obj, const HASH_RES_t h) override {
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

    FORCE_INLINE virtual size_t count() override {
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

    FORCE_INLINE virtual bool hashDiffers(const T& x, const T& y) override {
        return IDX_FN1::hash(x) != IDX_FN1::hash(y);
    }

    FORCE_INLINE T* get(const T* key) const {
        return get(*key);
    }

    FORCE_INLINE virtual T* get(const T& key) const override {
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

    FORCE_INLINE virtual T* get(const T& key, const HASH_RES_t h) const override {

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

    inline virtual V getValueOrDefault(const T& key) const override {
        throw std::logic_error("Not implemented");
        return zero;
    }

    V getValueOrDefault(const T& key, const size_t hash_val) const override {
        throw std::logic_error("Not implemented");
        return zero;
    }

    int setOrDelOnZero(const T& k, const V& v) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int setOrDelOnZero(const T& k, const V& v, const size_t hash_val0) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v, const size_t hash_val) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    void del(const T& obj) override {
        const T* ptr = get(obj);
        if (ptr) del(ptr);
    }

    void del(const T& obj, const size_t h) override {
        const T* ptr = get(obj, h);
        if (ptr) del(ptr);
    }

    FORCE_INLINE void foreach(std::function<void (const T&) > f) const override {
        //TODO: implement
    }

    FORCE_INLINE void update(T* elem) {
        //Do nothing for now
    }

    FORCE_INLINE void slice(const T* key, std::function<void (const T&) > f) {
        throw std::logic_error("Not implemented");
    }

    FORCE_INLINE void slice(const T& key, std::function<void (const T&) > f) override {
        throw std::logic_error("Not implemented");
        //TODO: implement.  traversal type?
    }

    void clear() override {
        throw std::logic_error("Not implemented");
    }

    size_t computeHash(const T& key) override {
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

    ArrayIndex(int s = size) : zero(ZeroVal<V>().get()) { //Constructor argument is ignored
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

    FORCE_INLINE T* get(const T* key) const override {
        return get(*key);
    }

    FORCE_INLINE virtual T* get(const T& key) const override {
        HASH_RES_t idx = IDX_FN::hash(key);
        if (idx >= 0 && idx < size && isUsed[idx]) //TODO: remove check
            return array[idx];
        return nullptr;
    }

    FORCE_INLINE virtual void foreach(std::function<void (const T&) > f) const override {
        for (size_t b = 0; b < size; ++b) {
            if (isUsed[b])
                f(*array[b]);
        }
    }

    FORCE_INLINE virtual void del(const T* obj) override {
        HASH_RES_t idx = IDX_FN::hash(*obj);
        isUsed[idx] = false;
    }

    FORCE_INLINE virtual void add(T* obj) override {
        HASH_RES_t idx = IDX_FN::hash(*obj);
        isUsed[idx] = true;
        array[idx] = obj;
    }

    bool hashDiffers(const T& x, const T& y) override {
        return IDX_FN::hash(x) != IDX_FN::hash(y);
    }

    T* get(const T& key, const size_t h) const override {
        return array[h];
    }

    V getValueOrDefault(const T& key) const override {
        throw std::logic_error("Not implemented");
        return zero;
    }

    V getValueOrDefault(const T& key, const size_t hash_val) const override {
        throw std::logic_error("Not implemented");
        return zero;
    }

    int setOrDelOnZero(const T& k, const V& v) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int setOrDelOnZero(const T& k, const V& v, const size_t hash_val0) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    int addOrDelOnZero(const T& k, const V& v, const size_t hash_val) override {
        throw std::logic_error("Not implemented");
        return 0;
    }

    void add(T* obj, const size_t h) override {
        array[h] = obj;
        isUsed[h] = true;
    }

    void add(T& obj) override {
        add(&obj);
    }

    void update(T* obj) override {
        //Do nothing
    }

    void del(const T* obj, const size_t h) override {
        isUsed[h] = false;
    }

    void del(const T& obj) override {
        const T* ptr = get(obj);
        if (ptr) del(ptr);
    }

    void del(const T& obj, const size_t h) override {
        isUsed[h] = false;
    }

    void slice(const T& key, std::function<void (const T&) > f) override {
        // ???
    }

    size_t count() override {
        return 0;
    }

    void clear() override {

    }

    size_t computeHash(const T& key) override {
        return IDX_FN::hash(key);
    }
};

template<typename T, typename V, typename...INDEXES>
class MultiHashMap {
private:
    Pool<T> pool;
public:
    Index<T, V>** index;
    T* head;

    MultiHashMap() : head(nullptr) { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES()...
        };
    }

    MultiHashMap(size_t init_capacity) : pool(init_capacity), head(nullptr) { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES(init_capacity)...
        };
    }

    MultiHashMap(const MultiHashMap& other) : head(nullptr) { // by defintion index 0 is always unique
        index = new Index<T, V>*[sizeof...(INDEXES)] {
            new INDEXES()...
        };
        other.index[0]->foreach([this] (const T & e) {
            this->insert_nocheck(e); });
    }

    virtual ~MultiHashMap() {
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) delete index[i];
        delete[] index;
    }

    FORCE_INLINE T* get(const T* key, const size_t idx = 0) const {
        return get(*key, idx);
    }
    
    FORCE_INLINE T* get(const T& key, const size_t idx = 0) const {
        return index[idx]->get(key);
    } // assume that mainIdx=0

   
    FORCE_INLINE T* get(const T& key, const HASH_RES_t h, const size_t idx) const {
        return index[idx]->get(key, h);
    }

    FORCE_INLINE void add(const T& obj) {
        add(&obj);
    }

    void add(const T* elem) {
        T* cur = index[0]->get(*elem);
        if (cur == nullptr) {
            cur = pool.add();
            // cur->~T();
            // *cur=std::move(*elem);
            new(cur) T(*elem);
            if (head) {
                cur->prv = nullptr;
                cur->nxt = head;
                head->prv = cur;
            }
            head = cur;
            for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
        } else {
            // cur->~T();
            // *cur=std::move(*elem);
            new(cur) T(*elem);
            for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
                if (index[i]->hashDiffers(*cur, *elem)) {
                    index[i]->del(cur);
                    index[i]->add(cur);
                }
            }
        }
    }

    FORCE_INLINE virtual void insert_nocheck(const T& elem) {
        T* cur = pool.add();
        // cur->~T();
        // *cur=std::move(elem);
        new(cur) T(elem);
        cur->prv = nullptr;
        cur->nxt = head;
        if (head) head->prv = cur;
        head = cur;
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
    }

    FORCE_INLINE virtual void insert_nocheck(const T& elem, HASH_RES_t h) { // assume that mainIdx=0
        T* cur = pool.add();
        // cur->~T();
        // *cur=std::move(elem);
        new(cur) T(elem);
        cur->prv = nullptr;
        cur->nxt = head;
        if (head) head->prv = cur;
        head = cur;
        index[0]->add(cur, h);
        for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
    }

    FORCE_INLINE void del(const T& key/*, int idx=0*/) { // assume that mainIdx=0
        T* elem = get(key);
        if (elem != nullptr) del(elem);
    }

    FORCE_INLINE void del(const T& key, HASH_RES_t h, int idx = 0) {
        T* elem = get(key, h, idx);
        if (elem != nullptr) del(elem, h);
    }

    void delSlice(const T& key, int idx = 0) {
        slice(idx, key, [this] (const T & e) {
            del(e); });
    }

    FORCE_INLINE void del(T* elem) { // assume that the element is already in the map
        T *elemPrv = elem->prv, *elemNxt = elem->nxt;
        if (elemPrv) elemPrv->nxt = elemNxt;
        if (elemNxt) elemNxt->prv = elemPrv;
        if (elem == head) head = elemNxt;
        elem->nxt = nullptr;
        elem->prv = nullptr;

        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
        pool.del(elem);
    }

    FORCE_INLINE void del(T* elem, HASH_RES_t h) { // assume that the element is already in the map and mainIdx=0
        T *elemPrv = elem->prv, *elemNxt = elem->nxt;
        if (elemPrv) elemPrv->nxt = elemNxt;
        if (elemNxt) elemNxt->prv = elemPrv;
        if (elem == head) head = elemNxt;
        elem->nxt = nullptr;
        elem->prv = nullptr;

        index[0]->del(elem, h);
        for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
        pool.del(elem);
    }

    inline void foreach(std::function<void (const T&) > f) const {
        // index[0]->foreach(f);
        T* tmp = head;
        while (tmp) {
            f(*tmp);
            tmp = tmp->nxt;
        }
    }

    void slice(int idx, const T* key, std::function<void (const T&) > f) {
        index[idx]->slice(*key, f);
    }

    void slice(int idx, const T& key, std::function<void (const T&) > f) {
        index[idx]->slice(key, f);
    }

    FORCE_INLINE void update(T* elem) {
        //DO NOTHING, as of now
    }

    FORCE_INLINE size_t count() const {
        return index[0]->count();
    }

    FORCE_INLINE void clear() {
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->clear();
        pool.delete_all(head);
        head = nullptr;
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
        ar << "\n\t\t";
        dbtoaster::serialize_nvp(ar, "count", count());
        foreach([&ar] (const T & e) {
            ar << "\n"; dbtoaster::serialize_nvp_tabbed(ar, "item", e, "\t\t"); });
    }

    inline virtual V getValueOrDefault(const T& key, int mainIdx = 0) const {
        return index[mainIdx]->getValueOrDefault(key);
    }

    inline virtual void setOrDelOnZero(T& k, const V& v, const int mainIdx = 0) {
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

    inline virtual void addOrDelOnZero(T& k, const V& v, const int mainIdx = 0) {
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

#endif //MMAP_H
