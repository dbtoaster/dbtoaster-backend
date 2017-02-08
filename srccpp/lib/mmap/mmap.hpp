#ifndef DBTOASTER_MMAP_HPP
#define DBTOASTER_MMAP_HPP

#include <iostream>
#include <functional>
#include <string>

#include <string.h>
#include "pool.hpp"
#include "../serialization.hpp"
#include "../hpds/pstring.hpp"
#include "../hpds/macro.hpp"

namespace dbtoaster {

#define DEFAULT_CHUNK_SIZE 32   // 2^N

#define HASH_RES_t size_t

// #define DOUBLE_ZERO_APPROXIMATED
// #define DOUBLE_ZERO_THRESHOLD 1e-8

template<typename V>
struct ZeroValue 
{
    V get() { return V(); }
    FORCE_INLINE bool isZero(V a) { return (a == V()); }
};

template<>
struct ZeroValue<int> 
{
    int get() { return 0; }
    FORCE_INLINE bool isZero(int a) { return (a == 0); }
};

template<>
struct ZeroValue<long> 
{
    long get() { return 0L; }
    FORCE_INLINE bool isZero(long a) { return (a == 0L); }
};

template<>
struct ZeroValue<float> 
{
    float get() { return 0.0f; }
    FORCE_INLINE bool isZero(float a) { return (a == 0.0f); }
};

template<>
struct ZeroValue<double> 
{
    double get() { return 0.0; }
#ifdef DOUBLE_ZERO_APPROXIMATED
    FORCE_INLINE bool isZero(double a) { return (a >= -DOUBLE_ZERO_THRESHOLD && a <= DOUBLE_ZERO_THRESHOLD); }
#else
    FORCE_INLINE bool isZero(double a) { return (a == 0.0); }
#endif
};

#ifndef USE_OLD_MAP

template <typename T>
struct PrimaryIdxNode {
    T* obj;
    HASH_RES_t hash;
    struct PrimaryIdxNode* nxt;
};

template <typename T>
struct SecondaryIdxNode {
    T* obj;
    HASH_RES_t hash;
    struct SecondaryIdxNode* nxt;       // next slice
    struct SecondaryIdxNode* child;     // next elem in slice
};

template <typename T, typename IDX_FN = T>
class PrimaryHashIndex {
private: 
    typedef PrimaryIdxNode<T> IdxNode;
    
    ValuePool<IdxNode> pool_;
    IdxNode* buckets_;

    size_t size_;
    size_t index_mask_;
    double load_factor_;
    size_t threshold_;
    size_t count_;

    void resize_(size_t new_size) {
        IdxNode* old_buckets = buckets_;
        size_t old_size = size_;

        buckets_ = new IdxNode[new_size];
        memset(buckets_, 0, sizeof(IdxNode) * new_size);
        size_ = new_size;
        index_mask_ = size_ - 1;
        threshold_ = size_ * load_factor_;

        for (size_t i = 0; i < old_size; i++) {
            IdxNode* src = old_buckets + i;
            bool pooled = false;
            do {
                if (src->obj != nullptr) {
                    IdxNode* dst = buckets_ + (src->hash & index_mask_);
                    if (dst->obj != nullptr) {
                        IdxNode* new_node = pool_.add(); 
                        new_node->obj = dst->obj;
                        new_node->hash = dst->hash; 
                        new_node->nxt = dst->nxt; 
                        dst->obj = src->obj;
                        dst->hash = src->hash; 
                        dst->nxt = new_node;
                    } 
                    else {
                        dst->obj = src->obj;
                        dst->hash = src->hash;
                        assert(dst->nxt == nullptr);
                    }
                }
                if (pooled) {
                    IdxNode* tmp = src;
                    src = src->nxt;
                    pool_.del(tmp);
                } 
                else src = src->nxt;
                pooled = true;
            } 
            while (src != nullptr);
        }
        if (old_buckets != nullptr) delete[] old_buckets;
    }

public:

    PrimaryHashIndex(size_t size = DEFAULT_CHUNK_SIZE, double load_factor = 0.75) : pool_(size) {
        buckets_ = nullptr;
        size_ = 0;
        load_factor_ = load_factor;
        count_ = 0;
        resize_(size);
    }

    virtual ~PrimaryHashIndex() {
        pool_.clear();
        if (buckets_ != nullptr) {
            delete[] buckets_;
            buckets_ = nullptr;
        }        
    }

    FORCE_INLINE size_t count() const { 
        return count_; 
    }    

    FORCE_INLINE HASH_RES_t computeHash(const T& key) { 
        return IDX_FN::hash(key); 
    }

    // returns the first matching element or nullptr if not found
    FORCE_INLINE T* get(const T& key, const HASH_RES_t h) const {
        IdxNode* n = buckets_ + (h & index_mask_);
        do {
            if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj)) {
                return n->obj;
            }
        } while ((n = n->nxt));
        return nullptr;
    }

    FORCE_INLINE T* get(const T& key) const {
        return get(key, IDX_FN::hash(key));
    }

    // inserts regardless of whether element already exists
    FORCE_INLINE void insert(T* obj, const HASH_RES_t h) {
        assert(obj != nullptr);

        if (count_ > threshold_) { resize_(size_ << 1); }

        IdxNode* dst = buckets_ + (h & index_mask_);
        if (dst->obj != nullptr) {
            IdxNode* new_node = pool_.add();
            new_node->obj = obj;
            new_node->hash = h;
            new_node->nxt = dst->nxt;
            dst->nxt = new_node;
        }
        else {
            dst->obj = obj;
            dst->hash = h;
            assert(dst->nxt == nullptr);
        }
        count_++;
    }

    FORCE_INLINE void insert(T* obj) {
        if (obj != nullptr) { insert(obj, IDX_FN::hash(*obj)); }
    }        

    // deletes an existing elements (equality by pointer comparison)
    FORCE_INLINE void del(const T* obj, const HASH_RES_t h) {
        assert(obj != nullptr);

        IdxNode *dst = buckets_ + (h & index_mask_);
        IdxNode *prev = nullptr;
        IdxNode *next;

        do {
            next = dst->nxt;
            // pointer comparison is sufficient as all objects are stored in pool
            if (dst->obj == obj) {
                if (prev != nullptr) {  // element in linked list (and not in bucket itself)
                    prev->nxt = next;
                    pool_.del(dst);
                } 
                else if (next != nullptr) {  // element in bucket, and there are other elements in linked list
                    dst->obj = next->obj;
                    dst->hash = next->hash;
                    dst->nxt = next->nxt;
                    pool_.del(next);
                } 
                else {   // only element in bucket
                    dst->obj = nullptr;
                    dst->hash = 0;
                    dst->nxt = nullptr;
                }
                count_--;
                return;
            }
            prev = dst;
        } while ((dst = next));
    }

    FORCE_INLINE void del(const T* obj) {
        if (obj != nullptr) { del(obj, IDX_FN::hash(*obj)); }
    }

    FORCE_INLINE void clear() {
        if (count_ == 0) return;

        for (size_t i = 0; i < size_; i++) {
            buckets_[i].obj = nullptr;
            buckets_[i].hash = 0;
            if (buckets_[i].nxt != nullptr) {
                pool_.delete_all(buckets_[i].nxt);
                buckets_[i].nxt = nullptr;
            }
        }
        count_ = 0;
    }
};

template <typename T> 
class SecondaryIndex {
  public:
    virtual const SecondaryIdxNode<T>* slice(const T& key) const = 0;

    virtual void insert(T* obj) = 0;

    virtual void del(const T* obj) = 0;

    virtual void clear() = 0;

    virtual ~SecondaryIndex() { }
};


template <typename T, typename IDX_FN = T>
class SecondaryHashIndex : public SecondaryIndex<T> {
private:
    typedef SecondaryIdxNode<T> IdxNode;

    ValuePool<IdxNode> pool_;
    IdxNode* buckets_;

    size_t size_;
    size_t index_mask_;
    double load_factor_;
    size_t threshold_;
    size_t count_;

    void resize_(size_t new_size) {
        IdxNode* old_buckets = buckets_;
        size_t old_size = size_;

        buckets_ = new IdxNode[new_size];
        memset(buckets_, 0, sizeof(IdxNode) * new_size);
        size_ = new_size;
        index_mask_ = size_ - 1;
        threshold_ = size_ * load_factor_;

        for (size_t i = 0; i < old_size; i++) {
            IdxNode* src = old_buckets + i;
            bool pooled = false;
            do {
                if (src->obj != nullptr) {
                    IdxNode* dst = buckets_ + (src->hash & index_mask_);
                    if (dst->obj != nullptr) {
                        IdxNode* new_node = pool_.add();
                        new_node->obj = dst->obj;
                        new_node->hash = dst->hash; 
                        new_node->nxt = dst->nxt; 
                        new_node->child = dst->child;
                        dst->obj = src->obj;
                        dst->hash = src->hash; 
                        dst->nxt = new_node;
                        dst->child = src->child;
                    } 
                    else {
                        dst->obj = src->obj;
                        dst->hash = src->hash;
                        assert(dst->nxt == nullptr);
                        dst->child = src->child;
                    }
                }
                if (pooled) {
                    IdxNode* tmp = src;
                    src = src->nxt;
                    pool_.del(tmp);
                } 
                else src = src->nxt;
                pooled = true;
            } 
            while (src != nullptr);
        }
        if (old_buckets != nullptr) delete[] old_buckets;
    }    

public:

    SecondaryHashIndex(size_t size = DEFAULT_CHUNK_SIZE, double load_factor = 0.75) {
        buckets_ = nullptr;
        size_ = 0;
        load_factor_ = load_factor;
        count_ = 0;
        resize_(size);        
    }

    virtual ~SecondaryHashIndex() {
        pool_.clear();
        if (buckets_ != nullptr) {
            delete[] buckets_;
            buckets_ = nullptr;
        }        
    }

    FORCE_INLINE size_t count() const { 
        return count_; 
    }    

    // returns the first matching node or nullptr if not found
    FORCE_INLINE IdxNode* slice(const T& key, const HASH_RES_t h) const {
        IdxNode* n = buckets_ + (h & index_mask_);
        do {
            if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj)) {
                return n;
            }
        } while ((n = n->nxt));
        return nullptr;
    }

    FORCE_INLINE const IdxNode* slice(const T& key) const {
        return slice(key, IDX_FN::hash(key));
    }

    // inserts regardless of whether element already exists
    FORCE_INLINE void insert(T* obj, const HASH_RES_t h) {
        assert(obj != nullptr);

        if (count_ > threshold_) { resize_(size_ << 1); }

        IdxNode* dst = buckets_ + (h & index_mask_);
    
        if (dst->obj == nullptr) {
            dst->obj = obj;
            dst->hash = h;  
            assert(dst->nxt == nullptr);
            assert(dst->child == nullptr);
            count_++;
        }
        else {
            IdxNode* idx_node = slice(*obj, h);
            if (idx_node != nullptr) {
                IdxNode* new_node = pool_.add();
                new_node->obj = obj;
                new_node->hash = h;
                new_node->nxt = idx_node->child;
                new_node->child = nullptr;
                idx_node->child = new_node;
            }
            else {
                IdxNode* new_node = pool_.add();
                new_node->obj = dst->obj;
                new_node->hash = dst->hash;
                new_node->nxt = dst->nxt;
                new_node->child = dst->child;
                dst->obj = obj;
                dst->hash = h;
                dst->nxt = new_node;
                dst->child = nullptr;
                count_++;       // Count only distinct elements for non-unique index
            }
        }
    }

    FORCE_INLINE void insert(T* obj) {
        if (obj != nullptr) insert(obj, IDX_FN::hash(*obj));
    }

    // deletes an existing elements (equality by pointer comparison)
    FORCE_INLINE void del(const T* obj, const HASH_RES_t h) {
        assert(obj != nullptr);

        IdxNode* dst = buckets_ + (h & index_mask_);
        IdxNode* prev = nullptr;
        IdxNode* next;

        do {
            next = dst->nxt;
            if (dst->obj && h == dst->hash && IDX_FN::equals(*obj, *dst->obj)) {

                // pointer comparison is sufficient as all objects are stored in pool
                if (dst->obj == obj) {
                    // delete the first element of slice
                    IdxNode* child = dst->child;
                    if (child != nullptr) {
                        dst->obj = child->obj;
                        dst->hash = child->hash;
                        // dst->nxt remains unchanged
                        dst->child = child->nxt;
                        assert(child->child == nullptr);
                        pool_.del(child);
                    }
                    else {
                        if (prev != nullptr) {  // element in linked list (and not in bucket itself)
                            prev->nxt = next;
                            pool_.del(dst);
                        }
                        else if (next != nullptr) {  // element in bucket, and there are other elements in linked list
                            dst->obj = next->obj;
                            dst->hash = next->hash;
                            dst->nxt = next->nxt;
                            dst->child = next->child;
                            pool_.del(next);
                        }
                        else {   // the only element in bucket
                            dst->obj = nullptr;
                            dst->hash = 0;
                            dst->nxt = nullptr;
                            dst->child = nullptr;
                        }
                        count_--;
                    }
                }
                else {
                    IdxNode* head = dst;
                    prev = dst;
                    dst = dst->child;
                    while (dst != nullptr) {
                        if (dst->obj == obj) {
                            if (prev == head) { head->child = dst->nxt; }
                            else { prev->nxt = dst->nxt; }
                            pool_.del(dst);
                            return;
                        }
                        prev = dst;
                        dst = dst->nxt;
                    }
                }
                return;
            }
            prev = dst;
        } while ((dst = next));
    }

    FORCE_INLINE void del(const T* obj) {
        if (obj != nullptr) { del(obj, IDX_FN::hash(*obj)); }
    }

    FORCE_INLINE void clear() {
        if (count_ == 0) return;

        for (size_t i = 0; i < size_; i++) {
            buckets_[i].obj = nullptr;
            buckets_[i].hash = 0;
            if (buckets_[i].nxt != nullptr) {                
                // Delete all children
                IdxNode* dst = buckets_[i].nxt;
                do {
                    if (dst->child != nullptr) {
                        pool_.delete_all(dst->child);
                        // dst->child = nullptr;
                    }
                } while ((dst = dst->nxt));
                pool_.delete_all(buckets_[i].nxt);
                buckets_[i].nxt = nullptr;
            }
            if (buckets_[i].child != nullptr) {
                pool_.delete_all(buckets_[i].child);
                buckets_[i].child = nullptr;
            }
        }
        count_ = 0;
    }
};

template <typename T, typename V, typename PRIMARY_INDEX, typename... SECONDARY_INDEXES> 
class MultiHashMap {
  private:
    Pool<T> pool;
    PRIMARY_INDEX* primary_index;
    SecondaryIndex<T>** secondary_indexes;

    const V Zero = ZeroValue<V>().get();

    FORCE_INLINE void insert(const T& elem, HASH_RES_t h) {
        T *cur = pool.add();
        new (cur) T(elem);

        cur->prv = nullptr;
        cur->nxt = head;
        if (head != nullptr) { head->prv = cur; }
        head = cur;

        primary_index->insert(cur, h);
        for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); i++)
            secondary_indexes[i]->insert(cur);
    }


    FORCE_INLINE void del(T* elem, HASH_RES_t h) { // assume the element is already in the map and mainIdx=0
        assert(elem != nullptr);    // and elem is in the map

        T* elemPrv = elem->prv;
        T* elemNxt = elem->nxt;

        if (elemPrv) { elemPrv->nxt = elemNxt; }
        if (elemNxt) { elemNxt->prv = elemPrv; }
        if (elem == head) { head = elemNxt; }
        elem->nxt = nullptr;
        elem->prv = nullptr;

        primary_index->del(elem, h);
        for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); i++)
            secondary_indexes[i]->del(elem);
        pool.del(elem);
    }    

  public:

    T *head;

    MultiHashMap() : head(nullptr) { 
        primary_index = new PRIMARY_INDEX();
        secondary_indexes = new SecondaryIndex<T>*[sizeof...(SECONDARY_INDEXES)] { new SECONDARY_INDEXES()...};
    }

    MultiHashMap(size_t init_capacity) : head(nullptr) {
        primary_index = new PRIMARY_INDEX(init_capacity);
        secondary_indexes = new SecondaryIndex<T>*[sizeof...(SECONDARY_INDEXES)] { new SECONDARY_INDEXES(init_capacity)...};
    }

    MultiHashMap(const MultiHashMap &other) : MultiHashMap() {
        T *tmp = other.head;
        while (tmp) {
            insert(*tmp);
            tmp = tmp->nxt;
        }
    }

    virtual ~MultiHashMap() {
        pool.clear();
        if (primary_index != nullptr) {
            delete primary_index;
            primary_index = nullptr;    
        }
        for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); i++) {
            if (secondary_indexes[i] != nullptr) {
                delete secondary_indexes[i];
            }            
        }
        delete[] secondary_indexes;
        secondary_indexes = nullptr;
    }

    FORCE_INLINE size_t count() const {
        return primary_index->count();
    }

    FORCE_INLINE const T* get(const T& key) const {
      return primary_index->get(key);
    }

    FORCE_INLINE const V& getValueOrDefault(const T& key) const {
        T* elem = primary_index->get(key);
        return (elem != nullptr ? elem->__av : Zero);
    }

    FORCE_INLINE const SecondaryIdxNode<T>* slice(const T& k, size_t idx) {
        return secondary_indexes[idx]->slice(k);
    }    
    
    FORCE_INLINE void del(const T& k) {
        HASH_RES_t h = primary_index->computeHash(k);
        T *elem = get(k, h);
        if (elem != nullptr) { del(elem, h); }
    }

    FORCE_INLINE void insert(const T& k) {
        insert(k, primary_index->computeHash(k));
    }

    FORCE_INLINE void add(T& k, const V& v) {
        if (ZeroValue<V>().isZero(v)) { return; }

        HASH_RES_t h = primary_index->computeHash(k);
        T* elem = primary_index->get(k, h);
        if (elem != nullptr) { 
            elem->__av += v; 
        }
        else {
            k.__av = v;
            insert(k, h);
        }
    }

    FORCE_INLINE void addOrDelOnZero(T& k, const V& v) {
        if (ZeroValue<V>().isZero(v)) { return; }

        HASH_RES_t h = primary_index->computeHash(k);
        T* elem = primary_index->get(k, h);
        if (elem != nullptr) {
            elem->__av += v;
            if (ZeroValue<V>().isZero(elem->__av)) { del(elem, h); }
        }
        else {
            k.__av = v;
            insert(k, h);
        }
    }

    FORCE_INLINE void setOrDelOnZero(T& k, const V& v) {
        HASH_RES_t h = primary_index->computeHash(k);
        T* elem = primary_index->get(k, h);
        if (elem != nullptr) {
            if (ZeroValue<V>().isZero(v)) { del(elem, h); }
            else { elem->__av = v; }
        }
        else if (!ZeroValue<V>().isZero(v)) {
            k.__av = v;
            insert(k, h);
        }
    }

    FORCE_INLINE void clear() {
        if (primary_index->count() == 0) return;

        primary_index->clear();
        for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); i++)
            secondary_indexes[i]->clear();
        pool.delete_all(head);
        head = nullptr;
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
        ar << "\n\t\t";
        dbtoaster::serialize_nvp(ar, "count", count());
        T* elem = head;
        while (elem) {
            ar << "\n";
            dbtoaster::serialize_nvp_tabbed(ar, "item", *elem, "\t\t");
            elem = elem->nxt;
        }
    }
};

#else

#define INSERT_INTO_MMAP 1
#define DELETE_FROM_MMAP -1

template <typename T, typename V> 
class Index {
  public:
    virtual bool hashDiffers(const T &x, const T &y) = 0;

    virtual T *get(const T &key) const = 0;

    virtual T *get(const T &key, const HASH_RES_t h) const = 0;

    virtual const V& getValueOrDefault(const T &key) const = 0;

    virtual const V& getValueOrDefault(const T &key, const HASH_RES_t hash_val) const = 0;

    virtual int setOrDelOnZero(const T &k, const V &v) = 0;

    virtual int setOrDelOnZero(const T &k, const V &v, const HASH_RES_t hash_val0) = 0;

    virtual int addOrDelOnZero(const T &k, const V &v) = 0;

    virtual int addOrDelOnZero(const T &k, const V &v, const HASH_RES_t hash_val) = 0;

    virtual void add(T &obj) = 0;

    virtual void add(T *obj) = 0;

    virtual void add(T *obj, const HASH_RES_t h) = 0;

    virtual void del(const T &obj) = 0;

    virtual void del(const T &obj, const HASH_RES_t h) = 0;

    virtual void del(const T *obj) = 0;

    virtual void del(const T *obj, const HASH_RES_t h) = 0;

    virtual void foreach (std::function<void(const T &)> f) const = 0;

    virtual void slice(const T &key, std::function<void(const T &)> f) = 0;

    virtual size_t count() = 0;

    virtual void clear() = 0;

    virtual HASH_RES_t computeHash(const T &key) = 0;

    virtual ~Index(){};
};
template <typename T, typename V, typename IDX_FN = T, bool is_unique = true>
class HashIndex : public Index<T, V> 
{
  public:
    typedef struct __IdxNode 
    {
      HASH_RES_t hash;
      T *obj;
      struct __IdxNode *nxt;
      // struct __IdxNode *child;
    } IdxNode; //  the linked list is maintained 'compactly': 
               // if a IdxNode has a nxt, it is full.
    IdxNode *buckets_;
    size_t size_;
    size_t mask_;

  private:
    Pool<IdxNode> nodes_;
    bool allocated_from_pool_;
    size_t count_, threshold_;
    double load_factor_;
    const V zero;

    // void add_(T* obj) { // does not resize the bucket array, does not maintain
    // count
    //   HASH_RES_t h = IDX_FN::hash(*obj);
    //   IdxNode* n = &buckets_[h & mask_];
    //   if (n->obj) {
    //     IdxNode* nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a
    //     node
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
      memset(buckets_, 0, sizeof(IdxNode) * new_size);
      size_ = new_size;
      mask_ = size_ - 1;
      threshold_ = size_ * load_factor_;
      bool tmp_allocated_from_pool = false;
      for (size_t b = 0; b < sz; ++b) {
        n = &old[b];
        bool pooled = false;
        do {
          if (n->obj) { // add_(n->obj); // does not resize the bucket array,
                        // does not maintain count
            h = n->hash;
            na = &buckets_[h & mask_];
            if (na->obj) {
              tmp_allocated_from_pool = true;
              nw = nodes_.add(); // memset(nw, 0, sizeof(IdxNode)); // add a node
              // in addition to adding nw, we also change the place of nw with na
              // to preserve the order of elements, as it is required for
              // non-unique hash maps
              nw->hash = na->hash;
              nw->obj = na->obj;
              na->hash = h;
              na->obj = n->obj;
              nw->nxt = na->nxt;
              na->nxt = nw;
            } else { // space left in last IdxNode
              na->hash = h;
              na->obj = n->obj; // na->nxt=nullptr;
            }
          }
          if (pooled) {
            d = n;
            n = n->nxt;
            nodes_.del(d);
          } else
            n = n->nxt;
          pooled = true;
        } while (n);
      }
      allocated_from_pool_ = tmp_allocated_from_pool;
      if (old)
        delete[] old;
    }

  public:
    HashIndex(size_t size = DEFAULT_CHUNK_SIZE, double load_factor = .75)
        : nodes_(size), allocated_from_pool_(false), zero(ZeroValue<V>().get()) {
      load_factor_ = load_factor;
      size_ = 0;
      mask_ = 0;
      count_ = 0;
      buckets_ = nullptr;
      resize_(size);
    }

    ~HashIndex() {
      if (buckets_ != nullptr)
        delete[] buckets_;
    }

    T &operator[](const T &key) { return *get(key); }
    FORCE_INLINE virtual bool hashDiffers(const T &x, const T &y) {
      return IDX_FN::hash(x) != IDX_FN::hash(y);
    }

    // retrieves the first element equivalent to the key or nullptr if not found
    inline virtual T *get(const T &key) const {
      HASH_RES_t h = IDX_FN::hash(key);
      IdxNode *n = &buckets_[h & mask_];
      do {
        if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj))
          return n->obj;
      } while ((n = n->nxt));
      return nullptr;
    }

    inline virtual T *get(const T &key, const HASH_RES_t h) const {
      IdxNode *n = &buckets_[h & mask_];
      do {
        if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj))
          return n->obj;
      } while ((n = n->nxt));
      return nullptr;
    }

    // inserts regardless of whether element exists already
    FORCE_INLINE virtual void add(T &obj) { add(&obj); }

    FORCE_INLINE virtual void add(T *obj) {
      HASH_RES_t h = IDX_FN::hash(*obj);
      add(obj, h);
    }

    FORCE_INLINE virtual void add(T *obj, const HASH_RES_t h) {
      if (count_ > threshold_)
        resize_(size_ << 1);
      size_t b = h & mask_;
      IdxNode *n = &buckets_[b];
      IdxNode *nw;

      if (is_unique) {
        ++count_;
        if (n->obj) {
          allocated_from_pool_ = true;
          nw = nodes_.add(); // memset(nw, 0, sizeof(IdxNode)); // add a node
          nw->hash = h;
          nw->obj = obj;
          nw->nxt = n->nxt;
          n->nxt = nw;
        } else { // space left in last IdxNode
          n->hash = h;
          n->obj = obj; // n->nxt=nullptr;
        }
      } else {
        // ++count_;
        if (!n->obj) { // space left in last IdxNode
          ++count_;
          n->hash = h;
          n->obj = obj;
          n->nxt = nullptr;
          // n->child = nullptr;
          return;
        }
        do {
          if (h == n->hash && IDX_FN::equals(*obj, *n->obj)) {
            allocated_from_pool_ = true;
            nw = nodes_.add(); // memset(nw, 0, sizeof(IdxNode)); // add a node
            nw->hash = h;
            nw->obj = obj;
            // nw->nxt = n->child;
            // nw->child = nullptr;
            // n->child = nw;
            nw->nxt = n->nxt;
            n->nxt = nw;
            return;
          } 
          /*else {
            //go ahead, and look for an element in the same slice
            //or reach the end of linked list of IdxNodes
          }*/
        } while ((n = n->nxt));
        // if(!n) {
        ++count_;
        n = &buckets_[b];
        allocated_from_pool_ = true;
        nw = nodes_.add(); // memset(nw, 0, sizeof(IdxNode)); // add a node
        // in addition to adding nw, we also change the place of nw with n
        // to preserve the order of elements, as it is required for
        // non-unique hash maps (as the first element might be the start of)
        // a chain of non-unique elements belonging to the same slice
        nw->hash = n->hash;
        nw->obj = n->obj;
        nw->nxt = n->nxt;
        // nw->child = n->child;

        n->hash = h;
        n->obj = obj;
        n->nxt = nw;
        // n->child = nullptr;
        // return;
        // }
      }
    }

    // deletes an existing elements (equality by pointer comparison)
    FORCE_INLINE virtual void del(const T &obj) {
      const T *ptr = get(obj);
      if (ptr)
        del(ptr);
    }
    FORCE_INLINE virtual void del(const T &obj, const HASH_RES_t h) {
      const T *ptr = get(obj, h);
      if (ptr)
        del(ptr, h);
    }
    FORCE_INLINE virtual void del(const T *obj) {
      HASH_RES_t h = IDX_FN::hash(*obj);
      del(obj, h);
    }
    FORCE_INLINE virtual void del(const T *obj, const HASH_RES_t h) {
      IdxNode *n = &buckets_[h & mask_];
      IdxNode *prev = nullptr, *next; // previous and next pointers
      do {
        next = n->nxt;
        if (/*n->obj &&*/ n->obj == obj) { // we only need a pointer comparison,
                                           // as all objects are stored in the
                                           // pool
          if (prev) { // it is an element in the linked list (and not in the
                      // bucket itself)
            prev->nxt = next;
            // n->nxt = nullptr;
            // n->obj = nullptr;
            nodes_.del(n);
          } else if (next) { // it is the elements in the bucket, and there are
                             // other elements in linked list
            n->obj = next->obj;
            n->hash = next->hash;
            n->nxt = next->nxt;
            nodes_.del(next);
            next = n;
          } else { // it is the only element in the bucket
            n->obj = nullptr;
          }
          if (is_unique ||
              !((prev && prev->obj && (h == prev->hash) &&
                 IDX_FN::equals(*obj, *prev->obj)) ||
                (next && next->obj && (h == next->hash) &&
                 IDX_FN::equals(*obj, *next->obj))))
            --count_;
          return;
        }
        prev = n;
      } while ((n = next));
    }

    inline virtual void foreach (std::function<void(const T &)> f) const {
      for (size_t b = 0; b < size_; ++b) {
        IdxNode *n = &buckets_[b];
        do {
          if (n->obj)
            f(*n->obj);
        } while ((n = n->nxt));
      }
    }

    inline virtual void slice(const T &key, std::function<void(const T &)> f) {
      HASH_RES_t h = IDX_FN::hash(key);
      IdxNode *n = &(buckets_[h & mask_]);
      do {
        if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj)) {
          do {
            f(*n->obj);
          } while ((n = n->nxt) && (h == n->hash) &&
                   IDX_FN::equals(key, *n->obj));
          return;
        }
      } while ((n = n->nxt));
    }

    inline virtual void clear() {
      if (allocated_from_pool_) {
        IdxNode *head = nullptr;
        for (size_t b = 0; b < size_; ++b) {
          IdxNode *n = buckets_[b].nxt;
          if (n) {
            IdxNode *tmp = n;
            if (head) {
              while (n->nxt)
                n = n->nxt;
              n->nxt = head;
              head = tmp;
            } else
              head = n;
          }
        }
        nodes_.delete_all(head);
      }
      allocated_from_pool_ = false;
      count_ = 0;
      memset(buckets_, 0, sizeof(IdxNode) * size_);
    }

    FORCE_INLINE virtual size_t count() { return count_; }

    FORCE_INLINE virtual HASH_RES_t computeHash(const T &key) {
      return IDX_FN::hash(key);
    }

    inline virtual const V& getValueOrDefault(const T &key) const {
      HASH_RES_t h = IDX_FN::hash(key);
      IdxNode *n = &buckets_[h & mask_];
      do {
        T *lkup = n->obj;
        if (lkup && h == n->hash && IDX_FN::equals(key, *lkup))
          return lkup->__av;
      } while ((n = n->nxt));
      return zero;
    }

    inline virtual const V& getValueOrDefault(const T &key, HASH_RES_t h) const {
      IdxNode *n = &buckets_[h & mask_];
      do {
        T *lkup = n->obj;
        if (lkup && h == n->hash && IDX_FN::equals(key, *lkup))
          return lkup->__av;
      } while ((n = n->nxt));
      return zero;
    }

    inline virtual int setOrDelOnZero(const T &k, const V &v) {
      HASH_RES_t h = IDX_FN::hash(k);
      IdxNode *n = &buckets_[h & mask_];
      do {
        T *lkup = n->obj;
        if (lkup && h == n->hash && IDX_FN::equals(k, *lkup)) {
          if (ZeroValue<V>().isZero(v)) {
            return DELETE_FROM_MMAP;
          }
          lkup->__av = v;
          return 0;
        }
      } while ((n = n->nxt));
      // not found
      if (!ZeroValue<V>().isZero(v))
        return INSERT_INTO_MMAP; // insert it into the map
      return 0;
    }

    inline virtual int setOrDelOnZero(const T &k, const V &v, HASH_RES_t h) {
      IdxNode *n = &buckets_[h & mask_];
      do {
        T *lkup = n->obj;
        if (lkup && h == n->hash && IDX_FN::equals(k, *lkup)) {
          if (ZeroValue<V>().isZero(v)) {
            return DELETE_FROM_MMAP;
          }
          lkup->__av = v;
          return 0;
        }
      } while ((n = n->nxt));
      // not found
      if (!ZeroValue<V>().isZero(v))
        return INSERT_INTO_MMAP; // insert it into the map
      return 0;
    }

    inline virtual int addOrDelOnZero(const T &k, const V &v) {
      if (!ZeroValue<V>().isZero(v)) {
        HASH_RES_t h = IDX_FN::hash(k);
        IdxNode *n = &buckets_[h & mask_];
        do {
          T *lkup = n->obj;
          if (lkup && h == n->hash && IDX_FN::equals(k, *lkup)) {
            lkup->__av += v;
            if (ZeroValue<V>().isZero(lkup->__av)) {
              return DELETE_FROM_MMAP;
            }
            return 0;
          }
        } while ((n = n->nxt));
        // not found
        return INSERT_INTO_MMAP; // insert it into the map
      }
      return 0;
    }

    inline virtual int addOrDelOnZero(const T &k, const V &v, HASH_RES_t h) {
      if (!ZeroValue<V>().isZero(v)) {
        IdxNode *n = &buckets_[h & mask_];
        do {
          T *lkup = n->obj;
          if (lkup && h == n->hash && IDX_FN::equals(k, *lkup)) {
            lkup->__av += v;
            if (ZeroValue<V>().isZero(lkup->__av)) {
              return DELETE_FROM_MMAP;
            }
            return 0;
          }
        } while ((n = n->nxt));
        // not found
        return INSERT_INTO_MMAP; // insert it into the map
      }
      return 0;
    }

    template <typename TP, typename VP, typename... INDEXES>
    friend class MultiHashMap;
};

template <typename T, typename V, typename... INDEXES> 
class MultiHashMap {
  private:
    Pool<T> pool;

  public:
    Index<T, V> **index;
    T *head;

    MultiHashMap() : head(nullptr) { // by defintion index 0 is always unique
      index = new Index<T, V> *[sizeof...(INDEXES)]{new INDEXES()...};
    }

    MultiHashMap(size_t init_capacity): head(nullptr) { // by defintion index 0 is always unique
      index = new Index<T, V> *[sizeof...(INDEXES)]{new INDEXES(init_capacity)...};
    }

    MultiHashMap(const MultiHashMap &other) : head(nullptr) { // by defintion index 0 is always unique
      index = new Index<T, V> *[sizeof...(INDEXES)]{new INDEXES()...};
      other.index[0]->foreach ([this](const T &e) { this->insert_nocheck(e); });
    }

    virtual ~MultiHashMap() {
      for (size_t i = 0; i < sizeof...(INDEXES); ++i)
        delete index[i];
      delete[] index;
    }

    FORCE_INLINE T *get(const T &key /*, const size_t idx=0*/) const {
      return index[0]->get(key);
    } // assume mainIdx=0

    FORCE_INLINE T *get(const T &key, const HASH_RES_t h, const size_t idx = 0) const {
      return index[idx]->get(key, h);
    }

    FORCE_INLINE void add(const T &obj) { add(&obj); }

    void add(const T *elem) {
      T *cur = index[0]->get(*elem);
      if (cur == nullptr) {
        cur = pool.add();
        // cur->~T();
        // *cur=std::move(*elem);
        new (cur) T(*elem);
        if (head) {
          cur->prv = nullptr;
          cur->nxt = head;
          head->prv = cur;
        }
        head = cur;
        for (size_t i = 0; i < sizeof...(INDEXES); ++i)
          index[i]->add(cur);
      } else {
        // cur->~T();
        // *cur=std::move(*elem);
        new (cur) T(*elem);
        for (size_t i = 0; i < sizeof...(INDEXES); ++i) {
          if (index[i]->hashDiffers(*cur, *elem)) {
            index[i]->del(cur);
            index[i]->add(cur);
          }
        }
      }
    }

    FORCE_INLINE virtual void insert_nocheck(const T &elem) {
      T *cur = pool.add();
      // cur->~T();
      // *cur=std::move(elem);
      new (cur) T(elem);
      cur->prv = nullptr;
      cur->nxt = head;
      if (head)
        head->prv = cur;
      head = cur;
      for (size_t i = 0; i < sizeof...(INDEXES); ++i)
        index[i]->add(cur);
    }
    
    FORCE_INLINE virtual void insert_nocheck(const T &elem, HASH_RES_t h) { // assume mainIdx=0
      T *cur = pool.add();
      // cur->~T();
      // *cur=std::move(elem);
      new (cur) T(elem);
      cur->prv = nullptr;
      cur->nxt = head;
      if (head)
        head->prv = cur;
      head = cur;
      index[0]->add(cur, h);
      for (size_t i = 1; i < sizeof...(INDEXES); ++i)
        index[i]->add(cur);
    }

    FORCE_INLINE void del(const T &key /*, int idx=0*/) { // assume mainIdx=0
      T *elem = get(key);
      if (elem != nullptr)
        del(elem);
    }

    FORCE_INLINE void del(const T &key, HASH_RES_t h, int idx = 0) {
      T *elem = get(key, h, idx);
      if (elem != nullptr)
        del(elem, h);
    }

    void delSlice(const T &key, int idx = 0) {
      slice(idx, key, [](const T &e) { del(e); });
    }

    FORCE_INLINE void del(T *elem) { // assume the element is already in the map
      T *elemPrv = elem->prv, *elemNxt = elem->nxt;
      if (elemPrv)
        elemPrv->nxt = elemNxt;
      if (elemNxt)
        elemNxt->prv = elemPrv;
      if (elem == head)
        head = elemNxt;
      elem->nxt = nullptr;
      elem->prv = nullptr;

      for (size_t i = 0; i < sizeof...(INDEXES); ++i)
        index[i]->del(elem);
      pool.del(elem);
    }

    FORCE_INLINE void del(T *elem, HASH_RES_t h) { // assume the element is already in the map and mainIdx=0
      T *elemPrv = elem->prv, *elemNxt = elem->nxt;
      if (elemPrv)
        elemPrv->nxt = elemNxt;
      if (elemNxt)
        elemNxt->prv = elemPrv;
      if (elem == head)
        head = elemNxt;
      elem->nxt = nullptr;
      elem->prv = nullptr;

      index[0]->del(elem, h);
      for (size_t i = 1; i < sizeof...(INDEXES); ++i)
        index[i]->del(elem);
      pool.del(elem);
    }

    inline void foreach (std::function<void(const T &)> f) const {
      // index[0]->foreach(f);
      T *tmp = head;
      while (tmp) {
        f(*tmp);
        tmp = tmp->nxt;
      }
    }

    void slice(int idx, const T &key, std::function<void(const T &)> f) {
      index[idx]->slice(key, f);
    }

    FORCE_INLINE size_t count() const { return index[0]->count(); }

    FORCE_INLINE void clear() {
      for (size_t i = 0; i < sizeof...(INDEXES); ++i)
        index[i]->clear();
      pool.delete_all(head);
      head = nullptr;
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const {
      ar << "\n\t\t";
      dbtoaster::serialize_nvp(ar, "count", count());
      foreach ([&ar](const T &e) {
        ar << "\n";
        dbtoaster::serialize_nvp_tabbed(ar, "item", e, "\t\t");
      });
    }

    inline virtual const V& getValueOrDefault(const T &key, int mainIdx = 0) const {
      return index[mainIdx]->getValueOrDefault(key);
    }

    inline virtual void setOrDelOnZero(T &k, const V &v, const int mainIdx = 0) {
      HASH_RES_t h = index[mainIdx]->computeHash(k);
      switch (index[mainIdx]->setOrDelOnZero(k, v, h)) {
      case INSERT_INTO_MMAP:
        k.__av = v;
        insert_nocheck(k, h);
        break;
      case DELETE_FROM_MMAP:
        del(k, h);
        break;
      default:
        break;
      }
    }

    inline virtual void addOrDelOnZero(T &k, const V &v, const int mainIdx = 0) {
      HASH_RES_t h = index[mainIdx]->computeHash(k);
      switch (index[mainIdx]->addOrDelOnZero(k, v, h)) {
      case INSERT_INTO_MMAP:
        k.__av = v;
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

template<typename T, typename V>
FORCE_INLINE void add_to_temp_map(MultiHashMap<T, V, HashIndex<T, V> >& m, const T& k)
{
    if (ZeroValue<V>().isZero(k.__av)) return;
    T* lkup = m.get(k);
    if (lkup != nullptr) lkup->__av += k.__av;
    else /*k.__av = v;*/ m.insert_nocheck(k);
}

#endif

}

#endif /* DBTOASTER_MMAP_HPP */
