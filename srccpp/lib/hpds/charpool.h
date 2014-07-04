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

#ifndef CHARPOOL_H
#define CHARPOOL_H

#include <iostream>
#include <string.h>
#include "macro.h"

#define DEFAULT_CHUNK_SIZE 128U
#define DEFAULT_CHAR_ARR_SIZE 8U //should be a power of two
#define DEFAULT_NUM_RESERVED_CELLS 128U
#define DEFAULT_FORCE_CLEAR true
#define DEFAULT_NUM_MOST_USED_CELLS 16U

template<size_t char_arr_size=DEFAULT_CHAR_ARR_SIZE,size_t num_reserved_cell=DEFAULT_NUM_RESERVED_CELLS, size_t num_most_used_cells=DEFAULT_NUM_MOST_USED_CELLS>
class CharPool
{
private:
  typedef union __El
  {
    __El() {}; ~__El() {};
    char obj[char_arr_size];
    union __El *next;
  } El;
  El *free_[num_reserved_cell + 1];
  El *data_;
  size_t size_;
  bool forceClear_;
  size_t num_cell_left_in_index0_;

  inline size_t getPowerOfTwo(size_t size)
  {
    return 1 << getPowerOfTwoBitShifts(size);
  }

  inline size_t getPowerOfTwoBitShifts(size_t size)
  {
    size_t n = 0;
    while ((size >> n) > 0) ++n;
    return (((size_t)(1 << (n - 1))) == size) ? (n - 1) : n;
  }
  
  void add_chunk()   // precondition: no available elements
  {
    size_ = size_ << 1;
    El *chunk = new El[size_ + 1];
    chunk[size_].next = data_;
    data_ = chunk;
    
    useRemainingMemoryInIdx0();

    num_cell_left_in_index0_ = size_;
    free_[0] = data_;
  }

  FORCE_INLINE void useRemainingMemoryInIdx0() {
    while(num_cell_left_in_index0_ > num_most_used_cells) {
      for(size_t i=1; i<=num_most_used_cells; ++i) {
        if(num_cell_left_in_index0_ >= i) {
          free_[0]->next = free_[i];
          free_[i] = free_[0];
          free_[0] += i;
          num_cell_left_in_index0_ -= i;
        } else {
          break;
        }
      }
    }
    if(num_cell_left_in_index0_) {
      free_[0]->next = free_[num_cell_left_in_index0_];
      free_[num_cell_left_in_index0_] = free_[0];
    }
  }
public:
  CharPool(size_t chunk_size = DEFAULT_CHUNK_SIZE) : data_(nullptr), size_(getPowerOfTwo(chunk_size) >> 1), forceClear_(false), num_cell_left_in_index0_(0)
  {
    memset(free_, 0, (num_reserved_cell + 1) * sizeof(El*));
    add_chunk();
  }
  ~CharPool()
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

  // pre-condition: num_cells should be greater than 0
  // size_t str_size = num_cells * char_arr_size
  // count for \0 char at the end in str_size
  //
  // size_t num_cells = str_size / char_arr_size;
  // if(num_cells * char_arr_size != str_size) num_cells++;
  FORCE_INLINE char* add(size_t num_cells)
  {
    if(num_cells > num_reserved_cell) return new char[num_cells * char_arr_size];

    El *el;
    if ((el = free_[num_cells]))
    {
      free_[num_cells] = el->next;
    } else if((el = free_[0]) && num_cell_left_in_index0_ >= num_cells) {
      num_cell_left_in_index0_ -= num_cells;
      if(num_cell_left_in_index0_) free_[0] += num_cells;
      else free_[0] = nullptr;
    } else {
      forceClear_ = true;
      while(num_cell_left_in_index0_ < num_cells) add_chunk();
      if ((el = free_[num_cells]))
      {
        free_[num_cells] = el->next;
      } else {
        el = free_[0];
        num_cell_left_in_index0_ -= num_cells;
        if(num_cell_left_in_index0_) free_[0] += num_cells;
        else free_[0] = nullptr;
      }
    }
    return el->obj;
  }
  FORCE_INLINE void del(size_t num_cells, char* obj)
  {
    if(num_cells > num_reserved_cell) delete[] obj;
    else {
      ((El *)obj)->next = free_[num_cells];
      free_[num_cells] = (El *)obj;
    }
  }
  void clear(bool force = DEFAULT_FORCE_CLEAR)
  {
    if (force || forceClear_)
    {
      memset(free_,0,(num_reserved_cell + 1) * sizeof(El*));
      size_t sz = size_;
      El *chunk = data_;
      while ((chunk = chunk[sz].next))
      {
        free_[0] = chunk;
        num_cell_left_in_index0_ = sz;
        useRemainingMemoryInIdx0();
        chunk = chunk[sz].next;
        sz = sz >> 1;
      }
      free_[0] = data_;
      num_cell_left_in_index0_ = size_;
      forceClear_ = false;
    }
  }
};

#endif //CHARPOOL_H