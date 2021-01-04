#ifndef DBTOASTER_MULTIMAP_HPP
#define DBTOASTER_MULTIMAP_HPP

#include <iostream>
#include <functional>
#include <string>

#include "macro.hpp"
#include "types.hpp"
#include "serialization.hpp"
#include "pool.hpp"

using namespace dbtoaster;

namespace dbtoaster {

#define DEFAULT_CHUNK_SIZE 32   // 2^N

// #define HashType size_t

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

template <typename T>
struct PrimaryIdxNode {
    T* obj;
    HashType hash;
    struct PrimaryIdxNode* nxt;
};

template <typename T>
struct SecondaryIdxNode {
    T* obj;
    HashType hash;
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

    FORCE_INLINE HashType computeHash(const T& key) { 
        return IDX_FN::hash(key); 
    }

    // returns the first matching element or nullptr if not found
    FORCE_INLINE T* get(const T& key, const HashType h) const {
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
    FORCE_INLINE void insert(T* obj, const HashType h) {
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
    FORCE_INLINE void del(const T* obj, const HashType h) {
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
    FORCE_INLINE IdxNode* slice(const T& key, const HashType h) const {
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
    FORCE_INLINE void insert(T* obj, const HashType h) {
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
    FORCE_INLINE void del(const T* obj, const HashType h) {
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

    FORCE_INLINE void insert(const T& elem, HashType h) {
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


    FORCE_INLINE void del(T* elem, HashType h) { // assume the element is already in the map and mainIdx=0
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
        if (elem != nullptr) return elem->__av;
        return Zero;
    }

    FORCE_INLINE const SecondaryIdxNode<T>* slice(const T& k, size_t idx) {
        return secondary_indexes[idx]->slice(k);
    }    
    
    FORCE_INLINE void del(const T& k) {
        HashType h = primary_index->computeHash(k);
        T *elem = get(k, h);
        if (elem != nullptr) { del(elem, h); }
    }

    FORCE_INLINE void insert(const T& k) {
        insert(k, primary_index->computeHash(k));
    }

    FORCE_INLINE void add(T& k, const V& v) {
        if (ZeroValue<V>().isZero(v)) { return; }

        HashType h = primary_index->computeHash(k);
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

        HashType h = primary_index->computeHash(k);
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
        HashType h = primary_index->computeHash(k);
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
    void serialize(Archive &ar) const {
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

}

#endif /* DBTOASTER_MULTIMAP_HPP */
