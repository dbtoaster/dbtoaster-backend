#include <iostream>
#include <assert.h>
#include <functional>
#include <string.h>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>

#define DEFAULT_CHUNK_SIZE 1024
#define DEFAULT_LIST_SIZE 8

template<typename T>
class Pool {
private:
  typedef union __El { __El(){}; T obj;  union __El* next; ~__El() {}; } El;
  El* free_;
  El* data_;
  size_t size_;
  void add_chunk() { // precondition: no available elements
    El* chunk = new El[size_+1]; for (size_t i=0; i<size_-1; ++i) chunk[i].next = &chunk[i+1];
    chunk[size_-1].next = nullptr; chunk[size_].next = data_; data_ = chunk; free_ = chunk;
  }
public:
  Pool(size_t chunk_size=DEFAULT_CHUNK_SIZE) : data_(nullptr), size_(chunk_size) { add_chunk(); }
  ~Pool() { while (data_ != nullptr) { El* el = data_[size_].next; delete[] data_; data_ = el; } }
  T* add() { if (!free_) add_chunk(); El* el = free_; free_ = free_->next; return &(el->obj); }
  void del(T* obj) { ((El*)obj)->next = free_; free_ = (El*)obj; }
};

template<typename T>
struct GenericIndexFn {
  static long hash(const T& e) {
    return 0;
  }
  static bool equals(const T& x,const T& y) {
    return false;
  }
};

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

  virtual ~Index(){};
};

template<typename T, typename IDX_FN = GenericIndexFn<T>, int list_size=DEFAULT_LIST_SIZE>
class HashIndex : public Index<T> {
public:
  typedef struct __IdxNode {
    long hash[list_size];
    T* obj[list_size];
    struct __IdxNode* next;
  } IdxNode;  //  the linked list is maintained 'compactly': if a IdxNode has a next, it is full.
  IdxNode* buckets_;
private:
  Pool<IdxNode> nodes_;
  size_t size_, count_, threshold_;
  double load_factor_;

  void add_(T* obj) { // does not resize the bucket array, does not maintain count
    long h = IDX_FN::hash(*obj);
    IdxNode* n = &buckets_[h % size_];
    while (n->next) n=n->next;
    int i=0; while(i < list_size && n->obj[i]) ++i;
    if (i < list_size) { n->hash[i] = h; n->obj[i] = obj; return; } // space left in last IdxNode
    IdxNode* next = nodes_.add(); memset(next, 0, sizeof(IdxNode)); // add a node
    next->hash[0] = h; next->obj[0] = obj; n->next = next;
  }

  void resize_(size_t new_size) {
    IdxNode* old = buckets_;
    size_t sz = size_;
    buckets_ = new IdxNode[new_size];
    memset(buckets_, 0, sizeof(IdxNode) * new_size);
    size_ = new_size;
    threshold_ = size_ * load_factor_;
    for (size_t b=0; b<sz; ++b) {
      IdxNode* n = &buckets_[b];
      bool pooled = false;
      do {
        for (int i=0; i<list_size && n->obj[i]; ++i) add_(n->obj[i]);
        if (pooled) { IdxNode* d=n; n=n->next; nodes_.del(d); } else n=n->next; pooled = true;
      } while(n);
    }
    if(old != nullptr) delete[] old;
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
  inline virtual bool hashDiffers(const T& x, const T& y) {
    return IDX_FN::hash(x) != IDX_FN::hash(y);
  }
  // retrieves the first element equivalent to the key or nullptr if not found
  inline virtual T* get(const T& key) const {
    long h = IDX_FN::hash(key);
    IdxNode* n = &buckets_[h % size_];
    do for (int i=0; i<list_size && n->obj[i]; ++i) {
      if (h == n->hash[i] && IDX_FN::equals(key, *n->obj[i])) return n->obj[i];
    } while ((n=n->next));
    return nullptr;
  }

  // inserts regardless of whether element exists already
  inline virtual void add(T& obj) { add(&obj); }
  inline virtual void add(T* obj) { ++count_; if (count_>threshold_) resize_(size_<<1); add_(obj); }

  // deletes an existing elements (equality by pointer comparison)
  inline virtual void del(const T& obj) { const T* ptr = get(obj); if (ptr!=nullptr) del(ptr); }
  virtual void del(const T* obj) {
    long h = IDX_FN::hash(*obj);
    IdxNode* n = &buckets_[h % size_];
    IdxNode* prev = nullptr; // previous
    do {
      for (int i=0; i<list_size && n->obj[i]; ++i) {
        if (n->obj[i] == obj) { --count_;
          IdxNode* last=n; while (last->next) { prev=last; last=last->next; }
          int l=1; while (l<list_size && last->obj[l]) ++l; --l; // find the last element at last[l]
          n->hash[i] = last->hash[l]; n->obj[i] = last->obj[l]; last->obj[l] = nullptr; // swap & delete
          if (l==0 && prev) { prev->next=nullptr; nodes_.del(last); } return; // drop IdxNode if empty
        }
      }
      prev = n;
    } while ((n=n->next));
  }

  inline virtual void foreach(std::function<void (const T&)> f) {
    for (size_t b=0; b<size_; ++b) {
      IdxNode* n = &buckets_[b];
      do { for (size_t i=0; i<list_size && n->obj[i]; ++i) f(*n->obj[i]); } while((n=n->next));
    }
  }

  inline virtual void slice(const T& key, std::function<void (const T&)> f) {
    long h = IDX_FN::hash(key);
    IdxNode* n = &(buckets_[h % size_]);
    do for (size_t i=0; i<list_size && n->obj[i]; ++i) {
      if (h == n->hash[i] && IDX_FN::equals(key, *n->obj[i])) f(*n->obj[i]);
    } while ((n=n->next));
  }

  inline virtual size_t count() { return count_; }
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
  
  T* get(const T& key,int idx=0) const { return index[idx]->get(key); }

  inline void add(const T& obj) { add(&obj); }
  void add(const T* elem) {
    T* cur = index[0]->get(*elem);
    if (cur==nullptr) {
      cur=pool.add();
      memcpy(cur, elem, sizeof(T));
      for (size_t i=0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
    } else {
      memcpy(cur, elem, sizeof(T));
      for (size_t i=0; i<sizeof...(INDEXES); ++i) {
        if (index[i]->hashDiffers(*cur,*elem)) {
          index[i]->del(cur);   
          index[i]->add(cur);
        }
      }
    }
  }
  inline virtual void insert_nocheck(const T& elem) {
    T* cur = pool.add();
    memcpy(cur, &elem, sizeof(T));
    for (size_t i=0; i<sizeof...(INDEXES); ++i) index[i]->add(cur);
  }

  void del(const T& key, int idx=0) {
    T* elem = get(key,idx); if (elem!=nullptr) del(elem);
  }
  void delSlice(const T& key, int idx=0) {
    slice(idx, key,[] (const T& e) { del(e); });
  }
  void del(T* elem) { // assume that the element is already in the map
    for (size_t i=0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
    pool.del(elem);
  }
  inline void foreach(std::function<void (const T&)> f) {
    index[0]->foreach(f);
  }

  void slice(int idx, const T& key, std::function<void (const T&)> f) {
    index[idx]->slice(key, f);
  }

  inline size_t count() { return index[0]->count(); }

  inline void clear(){
    //TODO
  }

  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    int cnt = count();
    ar << boost::serialization::make_nvp("count", cnt);
    foreach([&ar] (const T& e) { ar << boost::serialization::make_nvp("item", e); });
  }
};