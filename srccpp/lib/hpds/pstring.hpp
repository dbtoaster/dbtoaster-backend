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

#ifndef POOLED_STRING_H
#define POOLED_STRING_H

#include "charpool.hpp"
#include <string>
#include <iostream>

#include "../smhasher/MurmurHash2.hpp"

#ifndef STRING_TYPE
#define STRING_TYPE PString
#endif //STRING_TYPE

#define DEFAULT_CHAR_ARR_SIZE_MINUS_ONE (DEFAULT_CHAR_ARR_SIZE - 1)

struct PString
{
private:
  static CharPool<> pool_;
  size_t size_;
  char *data_;
  size_t* ptr_count_;
  inline static size_t getNumCells(int sz)
  {
    size_t num_cells = sz / DEFAULT_CHAR_ARR_SIZE;
    // if(num_cells * DEFAULT_CHAR_ARR_SIZE != sz) num_cells++;
    if (sz & DEFAULT_CHAR_ARR_SIZE_MINUS_ONE) num_cells++;
    return num_cells;
  }
protected:
  //friends
  friend bool operator==(const char *, const PString &);
  friend bool operator!=(const char *, const PString &);
  friend std::ostream& operator<< (std::ostream& o, PString const& str);
  friend size_t hash_value(PString const& str);
public:
  PString() : size_(0), data_(nullptr), ptr_count_(new size_t(1)) {
  }
  PString(const char *str) : ptr_count_(new size_t(1))
  {
    size_ = strlen(str) + 1;
    size_t num_cells = getNumCells(size_);
    data_ = pool_.add(num_cells);
    memcpy(data_, str, size_ * sizeof(char));
  }
  PString(const char *str, size_t strln) : ptr_count_(new size_t(1))
  {
    size_ = strln + 1;
    size_t num_cells = getNumCells(size_);
    data_ = pool_.add(num_cells);
    memcpy(data_, str, strln * sizeof(char));
    data_[strln] = '\0';
  }
  // PString(const std::string &str) : ptr_count_(new size_t(1))
  // {
  //   size_ = str.length() + 1;
  //   size_t num_cells = getNumCells(size_);
  //   data_ = pool_.add(num_cells);
  //   memcpy(data_, str.c_str(), size_ * sizeof(char));
  // }
  PString(const PString &pstr)
  {
    *pstr.ptr_count_ += 1;
    this->ptr_count_ = pstr.ptr_count_;
    this->data_ = pstr.data_;
    this->size_ = pstr.size_;
  }
  ~PString()
  {
    *ptr_count_ -= 1;
    if (!(*ptr_count_) && data_) { pool_.del(getNumCells(size_), data_); delete ptr_count_; ptr_count_=nullptr; }
  }
  FORCE_INLINE char *c_str()
  {
    return data_;
  }
  FORCE_INLINE const char *c_str() const
  {
    return data_;
  }
  inline char &operator[](const int x)
  {
    return data_[x];
  }
  inline const char &operator[](const int x) const
  {
    return data_[x];
  }
  PString &operator=(const char *str)
  {
    if (!(--(*ptr_count_)) && data_) { pool_.del(getNumCells(size_), data_); delete ptr_count_; }
    ptr_count_ = new size_t(1);
    size_ = strlen(str) + 1;
    size_t num_cells = getNumCells(size_);
    data_ = pool_.add(num_cells);
    memcpy(data_, str, size_ * sizeof(char));
    return *this;
  }
  PString &operator=(const PString &pstr)
  {
    (*pstr.ptr_count_)++;
    this->ptr_count_ = pstr.ptr_count_;
    this->data_ = pstr.data_;
    this->size_ = pstr.size_;
    return *this;
  }
  size_t length() const
  {
    return size_ - 1;
  }
  size_t maxsize() const
  {
    return getNumCells(size_)*DEFAULT_CHAR_ARR_SIZE - 1;
  }
  int end() const
  {
    return size_ - 1;
  }

  template<class Archive>
  void serialize(
    Archive & ar,
    const unsigned int file_version
  ) const {
    ar << this->data_;
  }

  inline bool operator==(const PString &other) const {
    if (this->size_ != other.size_) return false;
    return (strcmp(this->data_, other.data_) == 0);
  }

  inline bool operator!=(const PString &other) const {
    if (this->size_ != other.size_) return true;
    return (strcmp(this->data_, other.data_) != 0);
  }

  inline bool operator<(const PString &other) const {
    if (this->size_ != other.size_)
    {
      return (this->size_ < other.size_);
    }
    char *tmp1 = this->data_;
    char *tmp2 = other.data_;
    while (*tmp1 != 0)
    {
      if (*tmp1 != *tmp2)
      {
        return (*tmp1 < *tmp2);
      }
      ++tmp1;
      ++tmp2;
    }
    return false;
  }

  inline bool operator==(const char *other)
  {
    return (strcmp(this->data_, other) == 0);
  }

  inline bool operator!=(const char *other)
  {
    return (strcmp(this->data_, other) != 0);
  }

  PString substr (size_t pos) const {
    return PString(this->data_+pos);
  }
  PString substr (size_t pos, size_t len) const {
    return PString(this->data_+pos,len);
  }
};


template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const PString & t){
    t.serialize(ar, version);
    return ar;
}

#endif //POOLED_STRING_H