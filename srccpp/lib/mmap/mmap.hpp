#include <iostream>
#include <assert.h>
#include <functional>
#include <string.h>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <mmap/PMurHash.hpp>

#define DEFAULT_CHUNK_SIZE 1024
#define DEFAULT_LIST_SIZE 8

#define HASH_RES_t size_t

template<typename T>
class Pool {
private:
  typedef union __El { __El(){}; T obj;  union __El* next; ~__El() {}; } El;
  El* free_;
  El* data_;
  size_t size_;
  bool forceClear;
  void add_chunk() { // precondition: no available elements
    size_ = size_ << 1;
    El* chunk = new El[size_+1]; for (size_t i=0; i<size_-1; ++i) chunk[i].next = &chunk[i+1];
    chunk[size_-1].next = nullptr; chunk[size_].next = data_; data_ = chunk; free_ = chunk;
  }
public:
  Pool(size_t chunk_size=DEFAULT_CHUNK_SIZE) : data_(nullptr), size_(chunk_size >> 1), forceClear(false) { add_chunk(); }
  ~Pool() { size_t sz=size_; while (data_ != nullptr) { El* el = data_[sz].next; delete[] data_; data_ = el; sz=sz >> 1; } }
  FORCE_INLINE T* add() { if (!free_) { forceClear=true; add_chunk(); } El* el = free_; free_ = free_->next; return &(el->obj); }
  FORCE_INLINE void del(T* obj) { ((El*)obj)->next = free_; free_ = (El*)obj; }
  inline void clear(){
    if(forceClear) {
      El* prevChunk = nullptr;
      El* chunk = data_;
      size_t sz = size_;
      size_t doubleSz = sz << 1;
      while (chunk) {
        if(prevChunk) {
          prevChunk[doubleSz-1].next=chunk;
        }
        for (size_t i=0; i<sz-1; ++i) chunk[i].next = &chunk[i+1];
        chunk[sz-1].next = nullptr; // did not change
        prevChunk = chunk;
        chunk = chunk[sz].next;
        doubleSz=sz;
        sz=sz>>1;
      }
      free_ = data_;
      forceClear = false;
    }
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

template<typename T>
class Index {
public:
  virtual bool hashDiffers(const T& x, const T& y) = 0;

  virtual T* get(const T& key) const = 0;

  virtual void add(T& obj) = 0;

  virtual void add(T* obj) = 0;

  virtual void del(const T& obj) = 0;

  virtual void del(const T* obj) = 0;

  virtual void foreach(std::function<void (const T&)> f) = 0;

  virtual void slice(const T& key, std::function<void (const T&)> f) = 0;

  virtual size_t count() = 0;

  virtual void clear() = 0;

  virtual ~Index(){};
};

template<typename T, typename IDX_FN/* = GenericIndexFn<T>*/ >
class HashIndex : public Index<T> {
public:
  typedef struct __IdxNode {
    HASH_RES_t hash;
    T* obj;
    struct __IdxNode* next;
  } IdxNode;  //  the linked list is maintained 'compactly': if a IdxNode has a next, it is full.
  IdxNode* buckets_;
  size_t size_;
private:
  Pool<IdxNode> nodes_;
  size_t count_, threshold_;
  double load_factor_;

  void add_(T* obj) { // does not resize the bucket array, does not maintain count
    HASH_RES_t h = IDX_FN::hash(*obj);
    IdxNode* n = &buckets_[h % size_];
    if (n->obj) {
      IdxNode* nw = nodes_.add(); //memset(nw, 0, sizeof(IdxNode)); // add a node
      nw->hash = h; nw->obj = obj;
      nw->next = n->next; n->next=nw;
    } else {  // space left in last IdxNode
      n->hash = h; n->obj = obj; //n->next=nullptr;
    }
  }

  void resize_(size_t new_size) {
    IdxNode* old = buckets_;
    size_t sz = size_;
    buckets_ = new IdxNode[new_size];
    memset(buckets_, 0, sizeof(IdxNode) * new_size);
    size_ = new_size;
    threshold_ = size_ * load_factor_;
    for (size_t b=0; b<sz; ++b) {
      IdxNode* n = &old[b];
      bool pooled = false;
      do {
        if(n->obj) add_(n->obj);
        if (pooled) { IdxNode* d=n; n=n->next; nodes_.del(d); } else n=n->next;
        pooled = true;
      } while(n);
    }
    if(old) delete[] old;
  }

public:
  HashIndex(size_t size=DEFAULT_CHUNK_SIZE, double load_factor=.75) : nodes_(size) {
    load_factor_ = load_factor;
    size_ = 0;
    count_ = 0;
    buckets_ = nullptr;
    resize_(size);
  }

  ~HashIndex() { if(buckets_ != nullptr) delete[] buckets_; }

  T& operator[](const T& key) {
    return *get(key);
  }
  FORCE_INLINE virtual bool hashDiffers(const T& x, const T& y) {
    return IDX_FN::hash(x) != IDX_FN::hash(y);
  }
  // retrieves the first element equivalent to the key or nullptr if not found
  inline virtual T* get(const T& key) const {
    HASH_RES_t h = IDX_FN::hash(key);
    IdxNode* n = &buckets_[h % size_];
    do {
      if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj)) return n->obj;
    } while ((n=n->next));
    return nullptr;
  }

  // inserts regardless of whether element exists already
  FORCE_INLINE virtual void add(T& obj) { add(&obj); }
  inline virtual void add(T* obj) { ++count_; if (count_>threshold_) resize_(size_<<1); add_(obj); }

  // deletes an existing elements (equality by pointer comparison)
  FORCE_INLINE virtual void del(const T& obj) { const T* ptr = get(obj); if (ptr) del(ptr); }
  virtual void del(const T* obj) {
    HASH_RES_t h = IDX_FN::hash(*obj);
    IdxNode* n = &buckets_[h % size_];
    IdxNode* prev = nullptr; // previous
    do {
      if (/*n->obj &&*/ n->obj == obj) {
        --count_;
        if(prev) {
          prev->next=n->next;
          // n->next = nullptr;
          // n->obj = nullptr;
          nodes_.del(n);
        } else {
          n->obj = nullptr;
        }
        return;
      }
      prev = n;
    } while ((n=n->next));
  }

  inline virtual void foreach(std::function<void (const T&)> f) {
    for (size_t b=0; b<size_; ++b) {
      IdxNode* n = &buckets_[b];
      do { if(n->obj) f(*n->obj); } while((n=n->next));
    }
  }

  inline virtual void slice(const T& key, std::function<void (const T&)> f) {
    HASH_RES_t h = IDX_FN::hash(key);
    IdxNode* n = &(buckets_[h % size_]);
    do {
      if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj)) f(*n->obj);
    } while ((n=n->next));
  }
  inline virtual void clear(){
    count_ = 0;
    for (size_t b=0; b<size_; ++b) {
      IdxNode* n = &buckets_[b];
      IdxNode* next;
      do {
        n->obj = nullptr;
        // n->hash = 0L;
        next = n->next;
        n->next = nullptr;
      } while ((n=next));
    }
    nodes_.clear();
  }

  FORCE_INLINE virtual size_t count() { return count_; }
  template<typename TP, typename...INDEXES> friend class MultiHashMap;
};

template<typename T, typename...INDEXES>
class MultiHashMap {
private:
  Pool<T> pool;
public:
  Index<T>** index;

  MultiHashMap() { // by defintion index 0 is always unique
    index = new Index<T>*[sizeof...(INDEXES)]{ new INDEXES()... };
  }
  MultiHashMap(const MultiHashMap& other) { // by defintion index 0 is always unique
    index = new Index<T>*[sizeof...(INDEXES)]{ new INDEXES()... };
    other.index[0]->foreach([this] (const T& e) { this->insert_nocheck(e); });
  }
  virtual ~MultiHashMap() {
    for (size_t i=0; i<sizeof...(INDEXES); ++i) delete index[i];
    delete[] index;
  }
  
  FORCE_INLINE T* get(const T& key,int idx=0) const { return index[idx]->get(key); }

  FORCE_INLINE void add(const T& obj) { add(&obj); }
  void add(const T* elem) {
    T* cur = index[0]->get(*elem);
    if (cur==nullptr) {
      cur=pool.add();
      // cur->~T();
      // *cur=std::move(*elem);
      new(cur) T(*elem);
      for (size_t i=0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
    } else {
      // cur->~T();
      // *cur=std::move(*elem);
      new(cur) T(*elem);
      for (size_t i=0; i<sizeof...(INDEXES); ++i) {
        if (index[i]->hashDiffers(*cur,*elem)) {
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
    for (size_t i=0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
  }

  FORCE_INLINE void del(const T& key, int idx=0) {
    T* elem = get(key,idx); if (elem!=nullptr) del(elem);
  }
  void delSlice(const T& key, int idx=0) {
    slice(idx, key,[] (const T& e) { del(e); });
  }
  FORCE_INLINE void del(T* elem) { // assume that the element is already in the map
    for (size_t i=0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
    pool.del(elem);
  }
  inline void foreach(std::function<void (const T&)> f) {
    index[0]->foreach(f);
  }

  void slice(int idx, const T& key, std::function<void (const T&)> f) {
    index[idx]->slice(key, f);
  }

  FORCE_INLINE size_t count() { return index[0]->count(); }

  FORCE_INLINE void clear(){
    for (size_t i=0; i<sizeof...(INDEXES); ++i) index[i]->clear();
    pool.clear();
  }

  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    int cnt = count();
    ar << boost::serialization::make_nvp("count", cnt);
    foreach([&ar] (const T& e) { ar << boost::serialization::make_nvp("item", e); });
  }
};