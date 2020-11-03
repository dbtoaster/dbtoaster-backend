#ifndef DBTOASTER_POOL_HPP
#define DBTOASTER_POOL_HPP

#include <cassert>
#include <type_traits>

namespace dbtoaster {
    
#define DEFAULT_POOL_CHUNK_SIZE 32     // 2^N

template<class T, class Enable = void>
struct Elem {
  Elem() : next(nullptr), used(false) { }

  ~Elem() { deactivate(); }

  void activate() {
    used = true;
  }

  void deactivate() {
    if (used) { 
      obj.~T();
      used = false;
    }
  }

  union {
    struct Elem* next; 
    T obj;
  };
  bool used;
};

template <class T>
struct Elem<T, typename std::enable_if<std::is_trivially_destructible<T>::value>::type> {
  Elem() : next(nullptr) { }

  void activate() { }

  void deactivate() { }

  union {
    struct Elem* next;
    T obj;
  };
};

template<typename T>
class Pool {
 public:
  Pool(size_t chunk_size = DEFAULT_POOL_CHUNK_SIZE)
      : free_(nullptr), data_(nullptr), size_(0) {
    add_chunk(chunk_size);
  }

  ~Pool();

  T* add() {
    if (free_ == nullptr) {
      add_chunk(size_ << 1);
    }

    Elem<T>* el = free_;
    free_ = free_->next;
    el->activate();
    // el->next = nullptr;
    return &(el->obj);
  }

  void del(T* obj) { 
    if (obj == nullptr) { return; }

    Elem<T>* el = reinterpret_cast<Elem<T>*>(obj);
    el->deactivate();
    el->next = free_;
    free_ = el; 
  }

  void delete_all(T* current_data) {
    if (current_data == nullptr) { return; }

    T* tmp = current_data;
    do 
    {
      T* tmpNext = tmp->nxt;
      Elem<T>* tmpEl = reinterpret_cast<Elem<T>*>(tmp);
      tmpEl->deactivate();
      tmpEl->next = (tmpNext != nullptr ? reinterpret_cast<Elem<T>*>(tmpNext) : free_);
      tmp = tmpNext;
    } while (tmp != nullptr);
    free_ = reinterpret_cast<Elem<T>*>(current_data);
  }

  void clear();

 private:
  void add_chunk(size_t new_size);

  Elem<T>* free_;
  Elem<T>* data_;
  size_t size_;
};

template<typename T>
Pool<T>::~Pool() {
  size_t sz = size_;
  while (data_ != nullptr) {
    Elem<T>* el = data_[sz].next;
    delete[] data_;
    data_ = el;
    sz = sz >> 1;
  }
}

template<typename T>
void Pool<T>::add_chunk(size_t new_size) {
  // precondition: no available elements
  assert(free_ == nullptr);

  size_ = new_size;
  Elem<T>* chunk = new Elem<T>[size_ + 1];
  for (size_t i = 0; i < size_ - 1; ++i) {
    chunk[i].next = &chunk[i + 1];
  }
  chunk[size_ - 1].next = nullptr;
  chunk[size_].next = data_;
  data_ = chunk;
  free_ = chunk;
}

template<typename T>
void Pool<T>::clear() {
  Elem<T>* prevChunk = nullptr;
  Elem<T>* chunk = data_;
  size_t sz = size_;
  size_t doubleSz = sz << 1;

  while (chunk != nullptr) {
    if (prevChunk != nullptr) {
      prevChunk[doubleSz - 1].next = chunk;
    }
    for (size_t i = 0; i < sz - 1; ++i) {
      chunk[i].deactivate();
      chunk[i].next = &chunk[i + 1];
    }
    chunk[sz - 1].deactivate();
    chunk[sz - 1].next = nullptr;                    
    prevChunk = chunk;
    chunk = chunk[sz].next;
    doubleSz = sz;
    sz = sz >> 1;
  }
  free_ = data_;
}

}

#endif /* DBTOASTER_POOL_HPP */