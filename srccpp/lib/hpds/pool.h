// The MIT License (MIT)

// Copyright (c) 2014 Mohammad Dashti
// (www.mdashti.com - mohammad.dashti [at] epfl [dot] ch - mdashti [at] gmail [dot] com)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <string.h>
#include "macro.h"

#define DEFAULT_CHUNK_SIZE 1024
#define DEFAULT_FORCE_CLEAR true

template<typename T>
class Pool
{
private:
  typedef union __El
  {
    __El() {};
    T obj;
    union __El *next;
    ~__El() {};
  } El;
  El *free_;
  El *data_;
  size_t size_;
  bool forceClear;
  void add_chunk()   // precondition: no available elements
  {
    size_ = size_ << 1;
    El *chunk = new El[size_ + 1];
    for (size_t i = 0; i < size_ - 1; ++i)
      chunk[i].next = &chunk[i + 1];
    chunk[size_ - 1].next = nullptr;
    chunk[size_].next = data_;
    data_ = chunk;
    free_ = chunk;
  }
public:
  Pool(size_t chunk_size = DEFAULT_CHUNK_SIZE) : data_(nullptr), size_(chunk_size >> 1), forceClear(false)
  {
    add_chunk();
  }
  ~Pool()
  {
    size_t sz = size_;
    while (data_ != nullptr)
    {
      El *el = data_[sz].next;
      delete[] data_;
      data_ = el;
      sz = sz >> 1;
    }
  }
  FORCE_INLINE T *add()
  {
    if (!free_)
    {
      forceClear = true;
      add_chunk();
    } El *el = free_;
    free_ = free_->next;
    return &(el->obj);
  }
  FORCE_INLINE void del(T *obj)
  {
    ((El *)obj)->next = free_;
    free_ = (El *)obj;
  }
  void clear(bool force = DEFAULT_FORCE_CLEAR)
  {
    if (force || forceClear)
    {
      El *prevChunk = nullptr;
      El *chunk = data_;
      size_t sz = size_;
      size_t doubleSz = sz << 1;
      while (chunk)
      {
        if (prevChunk)
        {
          prevChunk[doubleSz - 1].next = chunk;
        }
        for (size_t i = 0; i < sz - 1; ++i) chunk[i].next = &chunk[i + 1];
        chunk[sz - 1].next = nullptr; // did not change
        prevChunk = chunk;
        chunk = chunk[sz].next;
        doubleSz = sz;
        sz = sz >> 1;
      }
      free_ = data_;
      forceClear = false;
    }
  }
};