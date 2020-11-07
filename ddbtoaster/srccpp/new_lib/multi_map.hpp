#ifndef DBTOASTER_MULTIMAP_HPP
#define DBTOASTER_MULTIMAP_HPP

#include <iostream>
#include <functional>
#include <string>
#include <cmath>
#include "macro.hpp"
#include "types.hpp"
#include "serialization.hpp"
#include "memory_pool.hpp"
#include "singleton.hpp"

using namespace dbtoaster;

namespace dbtoaster {

template <typename T>
using MemoryPool = dbtoaster::memory_pool::MemoryPool<T>;

constexpr bool isPowerOfTwo(size_t v) {
  return v && ((v & (v - 1)) == 0);
}

constexpr size_t kDefaultChunkSize = 32;  // 2^N

struct LinkedNode {
  void* obj;
  struct LinkedNode* next;
};

template <typename T, typename IDX_FN = T>
class PrimaryHashIndex {
 private: 
  struct IdxNode {
    void* obj;
    HASH_RES_t hash;
    struct IdxNode* next;
  };
  
  MemoryPool<IdxNode>* pool_;
  IdxNode* buckets_;
  size_t bucket_count_;
  size_t entry_count_;
  size_t index_mask_;     // derived value
  size_t threshold_;      // derived value
  const double load_factor_;

  void resize(size_t new_size);

 public:
  PrimaryHashIndex(size_t init_size = kDefaultChunkSize, double load_factor = 0.75)
      : pool_(Singleton<MemoryPool<IdxNode>>().acquire()),
        buckets_(nullptr), bucket_count_(0), entry_count_(0),
        index_mask_(0), threshold_(0), load_factor_(load_factor) {
    assert(isPowerOfTwo(init_size));
    resize(init_size);
  }

  ~PrimaryHashIndex();

  void clear();

  FORCE_INLINE size_t size() const {
    return entry_count_;
  }

  FORCE_INLINE HASH_RES_t computeHash(const T& key) { 
    return IDX_FN::hash(key); 
  }

  FORCE_INLINE T* get(const T& key) const {
    return get(key, IDX_FN::hash(key));
  }

  // Returns the first matching element or nullptr if not found
  FORCE_INLINE T* get(const T& key, const HASH_RES_t h) const {
    IdxNode* n = buckets_ + (h & index_mask_);
    do {
      T* t = reinterpret_cast<T*>(n->obj);
      if (t != nullptr && h == n->hash && IDX_FN::equals(key, *t)) {
        return t;
      }
    } while ((n = n->next));
    return nullptr;
  }

  FORCE_INLINE void insert(T* obj) {
    if (obj != nullptr) insert(obj, IDX_FN::hash(*obj)); 
  }

  // Inserts regardless of whether element already exists
  FORCE_INLINE void insert(T* obj, const HASH_RES_t h) {
    assert(obj != nullptr);

    if (entry_count_ > threshold_) { resize(bucket_count_ << 1); }

    IdxNode* dst = buckets_ + (h & index_mask_);
    if (dst->obj != nullptr) {
      IdxNode* new_node = pool_->acquire();
      new_node->obj = obj;
      new_node->hash = h;
      new_node->next = dst->next;
      dst->next = new_node;
    }
    else {
      dst->obj = obj;
      dst->hash = h;
      assert(dst->next == nullptr);
    }
    entry_count_++;
  }

  void erase(const T* obj) {
    if (obj != nullptr) erase(obj, IDX_FN::hash(*obj));
  }

  // Deletes an existing elements (equality by pointer comparison)
  void erase(const T* obj, const HASH_RES_t h) {
    assert(obj != nullptr);

    IdxNode *dst = buckets_ + (h & index_mask_);
    IdxNode *prev = nullptr, *next = nullptr;

    do {
      next = dst->next;
      // pointer comparison is sufficient as all objects are stored in pool
      if (dst->obj == obj) {
        if (prev != nullptr) {  // element in linked list (and not in bucket itself)
          prev->next = next;
          pool_->release(dst);
        } 
        else if (next != nullptr) {  // element in bucket, and there are other elements in linked list
          dst->obj = next->obj;
          dst->hash = next->hash;
          dst->next = next->next;
          pool_->release(next);
        } 
        else {   // only element in bucket
          dst->obj = nullptr;
          dst->hash = 0;
          dst->next = nullptr;
        }
        entry_count_--;
        return;
      }
      prev = dst;
    } while ((dst = next));
  }

  template <typename U, typename V, typename PRIMARY_INDEX, typename... SECONDARY_INDEXES> 
  friend class MultiHashMap;

  void dumpStatistics(bool verbose = false) const;
  size_t bucketSize(size_t bucket_id) const;
  double avgEntriesPerBucket() const;
  double stdevEntriesPerBucket() const;
  size_t maxEntriesPerBucket() const;
};

template <typename T, typename IDX_FN>
PrimaryHashIndex<T, IDX_FN>::~PrimaryHashIndex() {
  clear();
  if (buckets_ != nullptr) {
    free(buckets_);
    buckets_ = nullptr;
  }
  Singleton<MemoryPool<IdxNode>>().release(pool_);
  pool_ = nullptr;  
}

template <typename T, typename IDX_FN>
void PrimaryHashIndex<T, IDX_FN>::clear() {
  if (entry_count_ == 0) return;

  for (size_t i = 0; i < bucket_count_; ++i) {
    buckets_[i].obj = nullptr;
    buckets_[i].hash = 0;
    pool_->releaseChain(buckets_[i].next, [](const IdxNode* t) { return t->next; });
    buckets_[i].next = nullptr;
  }
  entry_count_ = 0;
}

template <typename T, typename IDX_FN>
void PrimaryHashIndex<T, IDX_FN>::resize(size_t new_size) {
  IdxNode* old_buckets = buckets_;
  size_t old_bucket_count = bucket_count_;

  int r = posix_memalign(reinterpret_cast<void **>(&buckets_), 32, new_size * sizeof(IdxNode));
  if (r != 0) {
    std::cerr << "Memory allocation error in PrimaryHashIndex" << std::endl;
    exit(-1);
  }
  memset(buckets_, 0, sizeof(IdxNode) * new_size);

  bucket_count_ = new_size;
  index_mask_ = bucket_count_ - 1;
  threshold_ = bucket_count_ * load_factor_;

  for (size_t i = 0; i < old_bucket_count; ++i) {
    IdxNode* src = old_buckets + i;

    if (src->obj != nullptr) {
      // insert first node from src bucket
      IdxNode* dst = buckets_ + (src->hash & index_mask_);
      if (dst->obj != nullptr) {
        IdxNode* new_node = pool_->acquire();
        new_node->obj = src->obj;
        new_node->hash = src->hash;
        new_node->next = dst->next;
        dst->next = new_node;
      }
      else {
        dst->obj = src->obj;
        dst->hash = src->hash;
        assert(dst->next == nullptr);
      }
    
      // insert remaining nodes from src bucket
      src = src->next;
      while (src != nullptr) {
        IdxNode* dst2 = buckets_ + (src->hash & index_mask_);
        IdxNode* nxt = src->next;

        if (dst2->obj != nullptr) {
          src->next = dst2->next;
          dst2->next = src;
        }
        else {
          dst2->obj = src->obj;
          dst2->hash = src->hash;
          assert(dst2->next == nullptr);
          pool_->release(src);          
        }
        src = nxt;
      }
    }
  }

  if (old_buckets != nullptr) free(old_buckets);
}

template <typename T, typename IDX_FN>
void PrimaryHashIndex<T, IDX_FN>::dumpStatistics(bool verbose) const {
  std::cout << "# of entries: " << entry_count_ << '\n';
  std::cout << "# of buckets: " << bucket_count_ << '\n';
  std::cout << "avg # of entries per bucket " << avgEntriesPerBucket() << '\n';
  std::cout << "stdev # of entries per bucket " << stdevEntriesPerBucket() << '\n';
  std::cout << "max # of entries per bucket " << maxEntriesPerBucket() << '\n';
  if (verbose) {
    for (size_t i = 0; i < bucket_count_; ++i) {
      std::cout << "bucket[" << i << "] = " << bucketSize(i) << '\n';  
    }
  }
  std::cout << std::flush;
}

template <typename T, typename IDX_FN>
size_t PrimaryHashIndex<T, IDX_FN>::bucketSize(size_t bucket_id) const {
  assert(0 <= bucket_id && bucket_id < bucket_count_);
  size_t cnt = 0;
  IdxNode* n = buckets_ + bucket_id;
  while (n != nullptr && n->obj != nullptr) {
    ++cnt;
    n = n->next;
  }
  return cnt;
}

template <typename T, typename IDX_FN>
double PrimaryHashIndex<T, IDX_FN>::avgEntriesPerBucket() const {
  return static_cast<double>(entry_count_) / bucket_count_;
}

template <typename T, typename IDX_FN>
double PrimaryHashIndex<T, IDX_FN>::stdevEntriesPerBucket() const {
  double avg = avgEntriesPerBucket();
  double sum = 0.0;
  for (size_t i = 0; i < bucket_count_; ++i) {
    size_t cnt = bucketSize(i);
    sum += (cnt - avg) * (cnt - avg);
  }
  return sqrt(sum / bucket_count_);
}

template <typename T, typename IDX_FN>
size_t PrimaryHashIndex<T, IDX_FN>::maxEntriesPerBucket() const {
  size_t max = 0;
  for (size_t i = 0; i < bucket_count_; ++i) {
    size_t cnt = bucketSize(i);
    if (cnt > max) { max = cnt; }
  }
  return max;
}

template <typename T> 
class SecondaryIndex {
 public:
  virtual ~SecondaryIndex() { }  
  virtual const LinkedNode* slice(const T& key) const = 0;
  virtual void insert(T* obj) = 0;
  virtual void erase(const T* obj) = 0;
  virtual void clear() = 0;
};

template <typename T, typename IDX_FN = T>
class SecondaryHashIndex : public SecondaryIndex<T> {
 private:
  struct IdxNode {
    LinkedNode node;
    HASH_RES_t hash;
    struct IdxNode* next;
  };

  MemoryPool<IdxNode>* idxNodePool_;
  MemoryPool<LinkedNode>* linkedNodePool_;
  IdxNode* buckets_;
  size_t bucket_count_;
  size_t entry_count_;
  size_t index_mask_;   // derived value
  size_t threshold_;    // derived value
  double load_factor_;

  void resize(size_t new_size);
  void deleteBucket(IdxNode* bucket);

 public:
  SecondaryHashIndex(size_t size = kDefaultChunkSize, double load_factor = 0.75)
      : idxNodePool_(Singleton<MemoryPool<IdxNode>>().acquire()),
        linkedNodePool_(Singleton<MemoryPool<LinkedNode>>().acquire()),
        buckets_(nullptr), bucket_count_(0), entry_count_(0), index_mask_(0),
        threshold_(0), load_factor_(load_factor) {
    resize(size);
  }

  virtual ~SecondaryHashIndex();

  void clear();

  FORCE_INLINE size_t size() const {
    return entry_count_;
  }

  const LinkedNode* slice(const T& key) const {
    return slice(key, IDX_FN::hash(key));
  }

  // returns the first matching node or nullptr if not found
  LinkedNode* slice(const T& key, const HASH_RES_t h) const {
    IdxNode* n = buckets_ + (h & index_mask_);
    do {
      if (n->node.obj != nullptr && h == n->hash &&
          IDX_FN::equals(key, *reinterpret_cast<T*>(n->node.obj))) {
        return &(n->node);
      }
    } while ((n = n->next));
    return nullptr;
  }

  FORCE_INLINE void insert(T* obj) {
    if (obj != nullptr) insert(obj, IDX_FN::hash(*obj));
  }

  // Inserts regardless of whether element already exists
  FORCE_INLINE void insert(T* obj, const HASH_RES_t h) {
    assert(obj != nullptr);

    if (entry_count_ > threshold_) { resize(bucket_count_ << 1); }

    IdxNode* dst = buckets_ + (h & index_mask_);

    if (dst->node.obj == nullptr) {
      dst->node.obj = obj;
      assert(dst->node.next == nullptr);
      dst->hash = h;
      assert(dst->next == nullptr);
      entry_count_++;
    }
    else {
      LinkedNode* idx_node = slice(*obj, h);
      if (idx_node != nullptr) {
        LinkedNode* new_node = linkedNodePool_->acquire();
        new_node->obj = obj;
        new_node->next = idx_node->next;
        idx_node->next = new_node;
      }
      else {
        IdxNode* new_node = idxNodePool_->acquire();
        new_node->node.obj = obj;
        new_node->node.next = nullptr;
        new_node->hash = h;
        new_node->next = dst->next;
        dst->next = new_node;
        entry_count_++;       // Count only distinct elements for non-unique index
      }
    }
  }

  void erase(const T* obj) {
    if (obj != nullptr) erase(obj, IDX_FN::hash(*obj));
  }

  // Deletes an existing elements (equality by pointer comparison)
  void erase(const T* obj, const HASH_RES_t h) {
    assert(obj != nullptr);

    IdxNode* dst = buckets_ + (h & index_mask_);
    IdxNode* prv = nullptr, *nxt = nullptr;

    do {
      nxt = dst->next;

      if (dst->node.obj != nullptr && h == dst->hash &&
          IDX_FN::equals(*obj, *reinterpret_cast<T*>(dst->node.obj))) {

        // pointer comparison is sufficient as all objects are stored in pool
        if (dst->node.obj == obj) {
          
          // delete the first element of slice
          LinkedNode* child = dst->node.next;
          if (child != nullptr) {
            dst->node = *child;
            // dst->hash remains unchanged
            // dst->next remains unchanged            
            linkedNodePool_->release(child);
          }
          else {
            if (prv != nullptr) {  // element in linked list (and not in bucket itself)
              prv->next = nxt;
              idxNodePool_->release(dst);
            }
            else if (nxt != nullptr) {  // element in bucket, and there are other elements in linked list
              *dst = *nxt;
              idxNodePool_->release(nxt);
            }
            else {   // the only element in bucket
              dst->node.obj = nullptr;
              dst->node.next = nullptr;
              dst->hash = 0;
              dst->next = nullptr;
            }
            entry_count_--;
          }
        }
        else {
          // look for a matching child of slice          
          LinkedNode* prev = &dst->node;
          LinkedNode* curr = dst->node.next;
          while (curr != nullptr) {
            if (curr->obj == obj) {
              prev->next = curr->next;
              linkedNodePool_->release(curr);
              return;
            }
            prev = curr;
            curr = curr->next;
          }
        }
        return;
      }
      prv = dst;
    } while ((dst = nxt));
  }
};

template <typename T, typename IDX_FN>
SecondaryHashIndex<T, IDX_FN>::~SecondaryHashIndex() {
  clear();
  if (buckets_ != nullptr) {
    free(buckets_);
    buckets_ = nullptr;
  }
  Singleton<MemoryPool<IdxNode>>().release(idxNodePool_);
  idxNodePool_ = nullptr;
  Singleton<MemoryPool<LinkedNode>>().release(linkedNodePool_);
  linkedNodePool_ = nullptr;  
}

template <typename T, typename IDX_FN>
void SecondaryHashIndex<T, IDX_FN>::resize(size_t new_size) {
  IdxNode* old_buckets = buckets_;
  size_t old_bucket_count = bucket_count_;

  int r = posix_memalign(reinterpret_cast<void **>(&buckets_), 32, new_size * sizeof(IdxNode));
  if (r != 0) {
    std::cerr << "Memory allocation error in SecondaryHashIndex" << std::endl;
    exit(-1);
  }
  memset(buckets_, 0, sizeof(IdxNode) * new_size);

  bucket_count_ = new_size;
  index_mask_ = bucket_count_ - 1;
  threshold_ = bucket_count_ * load_factor_;

  for (size_t i = 0; i < old_bucket_count; ++i) {
    IdxNode* src = old_buckets + i;

    if (src->node.obj != nullptr) {
      // insert first node from src bucket
      IdxNode* dst = buckets_ + (src->hash & index_mask_);
      if (dst->node.obj != nullptr) {
        IdxNode* new_node = idxNodePool_->acquire();
        new_node->node = src->node;
        new_node->hash = src->hash;
        new_node->next = dst->next;
        dst->next = new_node;
      }
      else {
        dst->node = src->node;
        dst->hash = src->hash;
        assert(dst->next == nullptr);
      }

      // insert remaining nodes from src bucket
      src = src->next;
      while (src != nullptr) {
        IdxNode* dst2 = buckets_ + (src->hash & index_mask_);
        IdxNode* nxt = src->next;

        if (dst2->node.obj != nullptr) {
          src->next = dst2->next;
          dst2->next = src;
        }
        else {
          dst2->node = src->node;
          dst2->hash = src->hash;
          assert(dst2->next == nullptr);
          idxNodePool_->release(src);
        }
        src = nxt;
      }
    }
  }
  if (old_buckets != nullptr) free(old_buckets);
}

template <typename T, typename IDX_FN>
void SecondaryHashIndex<T, IDX_FN>::deleteBucket(IdxNode* bucket) {
  IdxNode* slice = bucket;
  while (slice != nullptr) {
    IdxNode* next_slice = slice->next;
    linkedNodePool_->releaseChain(slice->node.next, [](const LinkedNode* t) { return t->next; });    
    idxNodePool_->release(slice);
    slice = next_slice;
  }
}

template <typename T, typename IDX_FN>
void SecondaryHashIndex<T, IDX_FN>::clear() {
  if (entry_count_ == 0) return;

  for (size_t i = 0; i < bucket_count_; ++i) {
    buckets_[i].node.obj = nullptr;
    buckets_[i].hash = 0;
    linkedNodePool_->releaseChain(buckets_[i].node.next, [](const LinkedNode* t) { return t->next; });
    buckets_[i].node.next = nullptr;
    deleteBucket(buckets_[i].next);
    buckets_[i].next = nullptr;
  }
  entry_count_ = 0;
}

template <typename T, typename V, typename PRIMARY_INDEX, typename... SECONDARY_INDEXES> 
class MultiHashMap {
 private:
  MemoryPool<T> pool_;
  PRIMARY_INDEX* primary_index_;
  SecondaryIndex<T>** secondary_indexes_;

  FORCE_INLINE void insert(const T& elem, HASH_RES_t h) {
    T *curr = pool_.acquire(elem);
    curr->prv = nullptr;
    curr->nxt = head;
    if (head != nullptr) { head->prv = curr; }
    head = curr;

    primary_index_->insert(curr, h);
    for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); ++i) {
      secondary_indexes_[i]->insert(curr);
    }
  }

  void erase(T* elem, HASH_RES_t h) { // assume the element is already in the map and mainIdx=0
    assert(elem != nullptr);    // and elem is in the map

    T* elem_prv = elem->prv;
    T* elem_nxt = elem->nxt;

    if (elem_prv != nullptr) { elem_prv->nxt = elem_nxt; }
    if (elem_nxt != nullptr) { elem_nxt->prv = elem_prv; }
    if (elem == head) { head = elem_nxt; }
    elem->nxt = nullptr;
    elem->prv = nullptr;

    primary_index_->erase(elem, h);
    for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); ++i) {
      secondary_indexes_[i]->erase(elem);
    }
    pool_.release(elem);
  }

 public:
  T* head;

  MultiHashMap() : head(nullptr) { 
    primary_index_ = new PRIMARY_INDEX();
    secondary_indexes_ = new SecondaryIndex<T>*[sizeof...(SECONDARY_INDEXES)] { new SECONDARY_INDEXES()...};
  }

  MultiHashMap(size_t init_capacity) : head(nullptr) {
    primary_index_ = new PRIMARY_INDEX(init_capacity);
    secondary_indexes_ = new SecondaryIndex<T>*[sizeof...(SECONDARY_INDEXES)] { new SECONDARY_INDEXES(init_capacity)...};
  }

  MultiHashMap(const MultiHashMap &) = delete;

  ~MultiHashMap();

  void clear();

  FORCE_INLINE size_t size() const {
    return primary_index_->size();
  }

  FORCE_INLINE const T* get(const T& key) const {
    return primary_index_->get(key);
  }

  FORCE_INLINE const V& getValueOrDefault(const T& key) const {
    T* elem = primary_index_->get(key);
    if (elem != nullptr) return elem->__av;
    return Value<V>::zero;
  }

  const LinkedNode* slice(const T& k, size_t idx) {
    return secondary_indexes_[idx]->slice(k);
  }    
    
  void erase(const T& k) {
    HASH_RES_t h = primary_index_->computeHash(k);
    T *elem = get(k, h);
    if (elem != nullptr) erase(elem, h);
  }

  void insert(const T& k) {
    insert(k, primary_index_->computeHash(k));
  }

  void add(T& k, const V& v) {
    if (Value<V>::isZero(v)) return;

    HASH_RES_t h = primary_index_->computeHash(k);
    T* elem = primary_index_->get(k, h);
    if (elem != nullptr) { 
      elem->__av += v; 
    }
    else {
      k.__av = v;
      insert(k, h);
    }
  }

  FORCE_INLINE void addOrDelOnZero(T& k, const V& v) {
    if (Value<V>::isZero(v)) return;

    HASH_RES_t h = primary_index_->computeHash(k);
    T* elem = primary_index_->get(k, h);
    if (elem != nullptr) {
      elem->__av += v;
      if (Value<V>::isZero(elem->__av)) erase(elem, h);
    }
    else {
      k.__av = v;
      insert(k, h);
    }
  }

  FORCE_INLINE void setOrDelOnZero(T& k, const V& v) {
    HASH_RES_t h = primary_index_->computeHash(k);
    T* elem = primary_index_->get(k, h);
    if (elem != nullptr) {
      if (Value<V>::isZero(v)) { erase(elem, h); }
      else { elem->__av = v; }
    }
    else if (!Value<V>::isZero(v)) {
      k.__av = v;
      insert(k, h);
    }
  }

  template <class Output>
  void serialize(Output &out) const;
};

template <typename T, typename V, typename PRIMARY_INDEX, typename... SECONDARY_INDEXES> 
MultiHashMap<T, V, PRIMARY_INDEX, SECONDARY_INDEXES...>::~MultiHashMap() {
  clear();
  
  if (primary_index_ != nullptr) {
    delete primary_index_;
    primary_index_ = nullptr;
  }
  if (secondary_indexes_ != nullptr) {
    for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); ++i) {
      if (secondary_indexes_[i] != nullptr) {
        delete secondary_indexes_[i];
      }
    }
    delete[] secondary_indexes_;
    secondary_indexes_ = nullptr;
  }
}

template <typename T, typename V, typename PRIMARY_INDEX, typename... SECONDARY_INDEXES> 
void MultiHashMap<T, V, PRIMARY_INDEX, SECONDARY_INDEXES...>::clear() {
  if (primary_index_->size() == 0) return;

  primary_index_->clear();
  for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES); i++) {
      secondary_indexes_[i]->clear();
  }
  pool_.releaseChain(head, [](const T* t) { return t->nxt; });
  head = nullptr;  
}

template <typename T, typename V, typename PRIMARY_INDEX, typename... SECONDARY_INDEXES>
template <class Output>
void MultiHashMap<T, V, PRIMARY_INDEX, SECONDARY_INDEXES...>::serialize(Output &out) const {
  out << "\n\t\t";
  dbtoaster::serialization::serialize(out, size(),  "count");
  T* elem = head;
  while (elem) {
    out << "\n";
    dbtoaster::serialization::serialize(out, *elem, "item", "\t\t");
    elem = elem->nxt;
  }
}

}

#endif /* DBTOASTER_MULTIMAP_HPP */
