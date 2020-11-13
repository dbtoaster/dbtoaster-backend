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
#include <cstring>
#include "smhasher/MurmurHash2.hpp"

#ifndef USE_PSTRING

typedef std::string PString;

#else

#define DEFAULT_CHAR_ARR_SIZE_MINUS_ONE (DEFAULT_CHAR_ARR_SIZE - 1)
// #define USE_POOL

struct PString {
public:
#ifdef USE_POOL
    static CharPool<> pool_;
#endif //USE_POOL
    size_t size_;
    size_t pos;
    char *data_;
    size_t *ptr_count_;

    inline static size_t getNumCells(int sz) {
        size_t num_cells = sz / DEFAULT_CHAR_ARR_SIZE;
        // if(num_cells * DEFAULT_CHAR_ARR_SIZE != sz) num_cells++;
        if (sz & DEFAULT_CHAR_ARR_SIZE_MINUS_ONE) num_cells++;
        return num_cells;
    }

protected:
    //friends
    friend bool operator==(const char *, const PString &);
    friend bool operator!=(const char *, const PString &);
    friend std::ostream &operator<<(std::ostream &o, PString const &str);
    friend size_t hash_value(PString const &str);

public:

    PString() : size_(0), pos(0), data_(nullptr), ptr_count_(nullptr) {
    }

    PString(size_t len) : size_(len + 1), pos(0), ptr_count_(new size_t(1)) {
#ifdef USE_POOL
        size_t num_cells = getNumCells(size_);
        data_ = pool_.add(num_cells);
#else
        data_ = new char[size_];
        memset(data_, 0, size_);
#endif //USE_POOL      
        //SBJ: Initialized externally
    }

    PString(const char *str) : pos(0), ptr_count_(new size_t(1)) {
        if (str != nullptr) {
            size_ = strlen(str) + 1;
#ifdef USE_POOL
            size_t num_cells = getNumCells(size_);
            data_ = pool_.add(num_cells);
#else
            data_ = new char[size_];
#endif //USE_POOL
            memcpy(data_, str, size_ * sizeof (char));
        } else {
            size_ = 0;
            data_ = nullptr;
        }
    }

    PString(const char *str, size_t strln) : pos(0) {
        if (str) {
            ptr_count_ = new size_t(1);
            size_ = strln + 1;
#ifdef USE_POOL
            size_t num_cells = getNumCells(size_);
            data_ = pool_.add(num_cells);
#else
            data_ = new char[size_];
#endif //USE_POOL
            memcpy(data_, str, strln * sizeof (char));
            data_[strln] = '\0';
        }
    }

    //   PString(const std::string &str) : ptr_count_(new size_t(1))
    //   {
    //     size_ = str.length() + 1;
    // #ifdef USE_POOL
    //     size_t num_cells = getNumCells(size_);
    //     data_ = pool_.add(num_cells);
    // #else
    //     data_ = new char[size_];
    // #endif //USE_POOL
    //     memcpy(data_, str.c_str(), size_ * sizeof(char));
    //   }

    PString(const PString &pstr) : pos(0) {
        if (pstr.data_) {
            *pstr.ptr_count_ += 1;
        }
        this->ptr_count_ = pstr.ptr_count_;
        this->data_ = pstr.data_;
        this->size_ = pstr.size_;

    }

    ~PString() {
       if (data_) {
           if ((--(*ptr_count_)) == 0) {
#ifdef USE_POOL
               pool_.del(getNumCells(size_), data_);
#else
               delete[] data_;
#endif //USE_POOL
               data_ = nullptr;
               delete ptr_count_;
               ptr_count_ = nullptr;
           }
       }
    }

    PString copy() const {
        if (data_)
           return PString(data_, size_ - 1);
        else
           return PString();
    }

    void recomputeSize() {
        if (!ptr_count_)
            ptr_count_ = new size_t(1);
        size_ = strlen(data_) + 1;
    }

    FORCE_INLINE char *c_str() {
        return data_;
    }

    FORCE_INLINE const char *c_str() const {
        return data_;
    }

    FORCE_INLINE void append(char c) {
        data_[pos++] = c;
    }

    FORCE_INLINE void appendDate(long d) {
        char *s = data_ + pos;
        s[0] = '2';
        s[1] = '0';
        s[20] = '0';
        s[19] = '.';
        s[18] = d % 10 + '0';
        d /= 10;
        s[17] = d % 10 + '0';
        d /= 10;
        s[16] = ':';
        s[15] = d % 10 + '0';
        d /= 10;
        s[14] = d % 10 + '0';
        d /= 10;
        s[13] = ':';
        s[12] = d % 10 + '0';
        d /= 10;
        s[11] = d % 10 + '0';
        d /= 10;
        s[10] = ' ';
        s[9] = d % 10 + '0';
        d /= 10;
        s[8] = d % 10 + '0';
        d /= 10;
        s[7] = '-';
        s[6] = d % 10 + '0';
        d /= 10;
        s[5] = d % 10 + '0';
        d /= 10;
        s[4] = '-';
        s[3] = d % 10 + '0';
        d /= 10;
        s[2] = d % 10 + '0';
        pos += 21;
    }

    FORCE_INLINE void append(int c) {
        int c2 = c;
        int n = 1;

        while (c2 > 9) {
            c2 /= 10;
            n *= 10;
        }

        while (n != 1) {
            data_[pos++] = (c / n) + '0';
            c = c % n;
            n /= 10;
        }
        data_[pos++] = c + '0';
    }

    FORCE_INLINE void append(double d) {
        float f = d;
        int c = f;
        int n = 1;
        while (c > 9) {
            c /= 10;
            n *= 10;
        }
        c = f;
        while (n != 1) {
            data_[pos++] = (c / n) + '0';
            c = c % n;
            n /= 10;
        }
        data_[pos++] = c + '0';
        data_[pos++] = '.';
        float f2 = f - (int) f;
        for (int i = 0; i < 6; ++i) {
            f2 *= 10;
            int c2 = int(f2);
            data_[pos++] = c2 + '0';
            f2 -= c2;
        }


    }

    FORCE_INLINE void append(const char *str, int len) {
        int remaining = size_ - pos - 1;
        int len2 = remaining > len ? len : remaining;
        int strlen = std::strlen(str);
        int len3 = len2 > strlen ? strlen : len2;
        memcpy(data_ + pos, str, len3);
        pos += len3;
    }

    inline char &operator[](const int x) {
        return data_[x];
    }

    inline const char &operator[](const int x) const {
        return data_[x];
    }

    PString &operator=(const char *str) {
#ifdef USE_POOL
        if (((--(*ptr_count_)) == 0) && data_) {
            pool_.del(getNumCells(size_), data_);
        }
        (*ptr_count_) = 1;
        size_ = strlen(str) + 1;
        size_t num_cells = getNumCells(size_);
        data_ = pool_.add(num_cells);
#else
        size_t sz = strlen(str) + 1;
        if (ptr_count_ != nullptr) {
            if (((--(*ptr_count_)) == 0) && data_ && (sz > size_)) {
                delete[] data_;
            }
            (*ptr_count_) = 1;
        } else {
            ptr_count_ = new size_t(1);
        }
        size_ = sz;
        data_ = new char[size_];
#endif //USE_POOL
        memcpy(data_, str, size_ * sizeof (char));
        return *this;
    }

    PString &operator=(const PString &pstr) {
        if (pstr.data_) {
            (*pstr.ptr_count_)++;
        }
        this->ptr_count_ = pstr.ptr_count_;
        this->data_ = pstr.data_;
        this->size_ = pstr.size_;

        return *this;
    }

    size_t length() const {
        return size_ - 1;
    }

    size_t maxsize() const {
        return getNumCells(size_) * DEFAULT_CHAR_ARR_SIZE - 1;
    }

    int end() const {
        return size_ - 1;
    }

    inline bool operator==(const PString &other) const {
        //        if (this->size_ != other.size_) return false;  Disabled due to direct operations on data after which size is incorrect
        if (data_ && other.data_)
            return (strcmp(this->data_, other.data_) == 0);
        else
            return !(data_ || other.data_); //both empty
    }

    inline bool operator!=(const PString &other) const {
        //SBJ: Not consistent with ! ==. 
        if (this->size_ != other.size_) return true;
        return (strcmp(this->data_, other.data_) != 0);
    }

    inline bool operator<(const PString &other) const {
        int i = 0;
        while (true) {
            char c1 = tolower(data_[i]);
            char c2 = tolower(other.data_[i]);
            if (!c1)
                return c2;
            else if (!c2)
                return false;
            else if (c1 == c2) {
                i++;
                continue;
            } else if (c1 < c2)
                return true;
            else return false;
        }
    }

    inline bool operator==(const char *other) {
        return (strcmp(this->data_, other) == 0);
    }

    inline bool operator!=(const char *other) {
        return (strcmp(this->data_, other) != 0);
    }

    PString substr(size_t pos) const {
        return PString(this->data_ + pos);
    }

    PString substr(size_t pos, size_t len) const {
        return PString(this->data_ + pos, len);
    }
};

#endif

#endif //POOLED_STRING_H