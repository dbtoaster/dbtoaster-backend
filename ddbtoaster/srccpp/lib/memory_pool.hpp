#ifndef DBTOASTER_MEMORY_POOL_HPP
#define DBTOASTER_MEMORY_POOL_HPP

#include "macro.hpp"
#include <iostream>
#include <cassert>

namespace dbtoaster {

namespace memory_pool {
  
constexpr size_t kDefaultChunkSize = 32;
constexpr size_t kMaxPoolChunkSize = 1048576;     // 2^20

template <typename T>
class MemoryPool {
 public:
  MemoryPool(size_t sz = kDefaultChunkSize)
      : lastChunk_(nullptr), currentSlot_(nullptr), 
        lastSlot_(nullptr), freeSlots_(nullptr) { 
    assert(sz > 1);
    allocateChunk(sz);
  }

  ~MemoryPool() {
    Slot_* curr = lastChunk_;
    while (curr != nullptr) {
      Slot_* next = curr->next;
      free(curr);
      curr = next;        
    }
  }

  FORCE_INLINE T* acquire() {
    if (freeSlots_ != nullptr) {
      T* result = reinterpret_cast<T*>(freeSlots_);
      freeSlots_ = freeSlots_->next;
      return result;
    }
    if (currentSlot_ > lastSlot_) {
      allocateChunk(static_cast<size_t>(lastSlot_ - lastChunk_ + 1) << 1);
    }
    return reinterpret_cast<T*>(currentSlot_++);
  }

  template <class... Args>
  FORCE_INLINE T* acquire(Args&&... args) {
    T* result = acquire();
    new (result) T(std::forward<Args>(args)...);
    return result;
  }

  FORCE_INLINE void release(T* obj) {
    if (obj != nullptr) {
      obj->~T();
      reinterpret_cast<Slot_*>(obj)->next = freeSlots_;
      freeSlots_ = reinterpret_cast<Slot_*>(obj);
    }
  }

  template <class NextFn>
  FORCE_INLINE void releaseChain(T* head, NextFn next_fn) {
    T* curr = head;
    while (curr != nullptr) {
      T* next = next_fn(curr);
      release(curr);
      curr = next;
    }
  }

 private:
  union Slot_ {
    T obj;
    Slot_* next;
  };

  Slot_* lastChunk_;
  Slot_* currentSlot_;
  Slot_* lastSlot_;
  Slot_* freeSlots_;

  void allocateChunk(size_t sz);
};

template <typename T>
void MemoryPool<T>::allocateChunk(size_t sz) {
  // precondition: no available elements
  assert(freeSlots_ == nullptr);

  size_t size = (sz < kMaxPoolChunkSize ? sz : kMaxPoolChunkSize);
  Slot_* chunk = reinterpret_cast<Slot_*>(malloc(size * sizeof(Slot_)));
  if (chunk == nullptr) {
    std::cerr << "Memory allocation error in memory pool" << std::endl;
    exit(-1);
  }
  chunk->next = lastChunk_;
  lastChunk_ = chunk;
  currentSlot_ = chunk + 1;
  lastSlot_ = chunk + size - 1;
}

}

}

#endif /* DBTOASTER_MEMORY_POOL_HPP */