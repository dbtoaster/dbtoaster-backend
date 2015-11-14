#ifndef DBTOASTER_STRING_HPP
#define DBTOASTER_STRING_HPP

#include <cstring>
#include "pool.hpp"

namespace dbtoaster
{
    template <uint64_t SIZE>
    struct FixedLengthString 
    {
        uint64_t size_;
        char data_[SIZE + 1];

        FixedLengthString() { size_ = 0; data_[0] = 0; }

        FixedLengthString(const char* str) : FixedLengthString(str, strlen(str)) { }

        FixedLengthString(const char* str, uint64_t length) 
        {    
            size_ = (length > SIZE ? SIZE : length);
            memcpy(data_, str, sizeof(char) * size_);
            data_[size_] = 0;
        }

        FixedLengthString(const std::string& str) : FixedLengthString(str.c_str(), str.size()) { }

        FixedLengthString(const FixedLengthString& str) 
        {
            size_ = str.size_;
            memcpy(data_, str.data_, sizeof(char) * str.size_);
            data_[size_] = 0;   
        }

        FORCE_INLINE uint64_t size() const
        {
            return size_;
        }

        FORCE_INLINE const char* c_str() const 
        {
            return data_;
        }

        FORCE_INLINE bool operator==(const char* other) const 
        {
            return (other != nullptr && data_[0] == other[0] && strcmp(data_, other) == 0);
        }

        FORCE_INLINE bool operator==(const FixedLengthString& other) const 
        {            
            return (size_ == other.size_ && 
                    (size_ == 0 || (data_[0] == other.data_[0] && memcmp(data_, other.data_, sizeof(char) * size_) == 0)));
        }

        FORCE_INLINE bool operator!=(const char* other) const 
        {
            return !(this->operator==(other));
        }

        FORCE_INLINE bool operator!=(const FixedLengthString& other) const 
        {
            return !(this->operator==(other));
        }

        FORCE_INLINE FixedLengthString& operator=(const char* str)
        {
            uint64_t length = strlen(str); 
            size_ = (length > SIZE ? SIZE : length);
            memcpy(data_, str, sizeof(char) * size_);
            data_[size_] = 0;
            return *this;            
        }

        FORCE_INLINE FixedLengthString& operator=(const FixedLengthString& other)
        {
            if (this != &other)
            {
                size_ = other.size_;                
                memcpy(data_, other.data_, sizeof(char) * size_);
                data_[size_] = 0;
            }
            return *this;
        }        

        FORCE_INLINE FixedLengthString substr(uint64_t pos, uint64_t len) const
        {
            return FixedLengthString(this->data_ + pos, len);
        }

        template <uint64_t SZ>
        friend std::ostream& operator<<(std::ostream& o, FixedLengthString<SZ> const& str);
    };

    struct VariableLengthString
    {
        uint64_t size_;
        char* data_;

        VariableLengthString() : size_(0), data_(nullptr) { }

        VariableLengthString(const char* str) : VariableLengthString(str, strlen(str)) { }

        VariableLengthString(const char* str, uint64_t length) 
        {    
            size_ = length;
            data_ = new char[size_ + 1];
            memcpy(data_, str, sizeof(char) * size_);
            data_[size_] = 0;
        }

        VariableLengthString(const std::string& str) : VariableLengthString(str.c_str(), str.size()) { }

        VariableLengthString(const VariableLengthString& str) : VariableLengthString(str.data_, str.size_) { }

        ~VariableLengthString()
        {
            if (data_ != nullptr) 
            {
                delete[] data_; 
                data_ = nullptr;
            }
        }

        FORCE_INLINE uint64_t size() const
        {
            return size_;
        }

        FORCE_INLINE const char* c_str() const 
        {
            return data_;
        }

        FORCE_INLINE bool operator==(const char* other) const 
        {
            return (data_[0] == other[0] && strcmp(data_, other) == 0);
        }

        FORCE_INLINE bool operator==(const VariableLengthString& other) const 
        {            
            return (size_ == other.size_ && 
                    (size_ == 0 || (data_[0] == other.data_[0] && memcmp(data_, other.data_, sizeof(char) * size_) == 0)));
        }

        FORCE_INLINE bool operator!=(const char* other) const 
        {
            return !(this->operator==(other));
        }

        FORCE_INLINE bool operator!=(const VariableLengthString& other) const 
        {
            return !(this->operator==(other));
        }

        FORCE_INLINE VariableLengthString& operator=(const char* str)
        {
            if (data_ != nullptr) { delete[] data_; }
            size_ = strlen(str);                
            data_ = new char[size_ + 1];
            memcpy(data_, str, sizeof(char) * size_);
            data_[size_] = 0;
            return *this;            
        }

        FORCE_INLINE VariableLengthString& operator=(const VariableLengthString& other)
        {
            if (this != &other)
            {
                if (data_ != nullptr) { delete[] data_; }
                size_ = other.size_;                
                data_ = new char[size_ + 1];
                memcpy(data_, other.data_, sizeof(char) * size_);
                data_[size_] = 0;                
            }
            return *this;
        }

        FORCE_INLINE VariableLengthString substr(uint64_t pos, uint64_t len) const
        {
            return VariableLengthString(this->data_ + pos, len);
        }        

        friend std::ostream& operator<<(std::ostream& o, VariableLengthString const& str);
    };

    struct RefCountedString : VariableLengthString
    {
        uint64_t* ptr_count_;

        RefCountedString() : VariableLengthString(), ptr_count_(new uint64_t(1)) { }

        RefCountedString(const char* str) : VariableLengthString(str, strlen(str)), ptr_count_(new uint64_t(1)) { }
        
        RefCountedString(const char* str, uint64_t length) : VariableLengthString(str, length), ptr_count_(new uint64_t(1)) { }
        
        RefCountedString(const std::string& str) : VariableLengthString(str.c_str(), str.size()), ptr_count_(new uint64_t(1)) { }

        RefCountedString(const RefCountedString& str) 
        {
            (*str.ptr_count_)++;
            ptr_count_ = str.ptr_count_;
            size_ = str.size_;
            data_ = str.data_;
        }

        ~RefCountedString()
        {
            if (ptr_count_ && (--(*ptr_count_)) == 0) 
            {
                delete ptr_count_;
                if (data_ != nullptr) delete[] data_;
            }
            ptr_count_ = nullptr;
            data_ = nullptr;
        }

        RefCountedString& operator=(const char* str)
        {
            if ((--(*ptr_count_)) == 0) 
            {   
                *ptr_count_ = 1;        // re-use ptr_count_
                if (data_ != nullptr) delete[] data_;                
            }
            else 
            {   
                ptr_count_ = new uint64_t(1);                
            }
            size_ = strlen(str);
            data_ = new char[size_ + 1];
            memcpy(data_, str, sizeof(char) * size_);
            data_[size_] = 0;
            return *this;
        }

        RefCountedString& operator=(const RefCountedString& str)
        {
            if ((--(*ptr_count_)) == 0) 
            {   
                delete ptr_count_;                
                if (data_ != nullptr) delete[] data_;                
            }
            (*str.ptr_count_)++;
            ptr_count_ = str.ptr_count_;
            size_ = str.size_;
            data_ = str.data_;
            return *this;
        }

        FORCE_INLINE RefCountedString substr(uint64_t pos, uint64_t len) const
        {
            return RefCountedString(this->data_ + pos, len);
        }        
    };


    ValuePool<uint64_t> pool;   

    struct PooledRefCountedString 
    {
        uint64_t* ptr_count_;
        uint64_t size_;
        char* data_;


        FORCE_INLINE PooledRefCountedString() 
        { 
            ptr_count_ = pool.add();
            *ptr_count_ = 1;
            size_ = 0;
            data_ = nullptr;
        }

        FORCE_INLINE PooledRefCountedString(const char* str, uint64_t length)
        {
            ptr_count_ = pool.add();
            *ptr_count_ = 1;
            size_ = length;
            data_ = new char[size_ + 1];
            memcpy(data_, str, sizeof(char) * size_);
            data_[size_] = 0;
        }

        FORCE_INLINE PooledRefCountedString(const char* str) : PooledRefCountedString(str, strlen(str)) { }

        FORCE_INLINE PooledRefCountedString(const std::string& str) : PooledRefCountedString(str.c_str(), str.size()) { }

        FORCE_INLINE PooledRefCountedString(const PooledRefCountedString& str) 
        {
            (*str.ptr_count_)++;
            ptr_count_ = str.ptr_count_;
            size_ = str.size_;
            data_ = str.data_;
        }

        ~PooledRefCountedString()
        {
            if (ptr_count_ && (--(*ptr_count_)) == 0) 
            {
                pool.del(ptr_count_);
                if (data_ != nullptr) delete[] data_;
            }
            ptr_count_ = nullptr;
            data_ = nullptr;
        }

        FORCE_INLINE uint64_t size() const
        {
            return size_;
        }

        FORCE_INLINE const char* c_str() const 
        {
            return data_;
        }

        FORCE_INLINE bool operator==(const char* other) const 
        {
            return (strcmp(data_, other) == 0);
        }

        FORCE_INLINE bool operator==(const PooledRefCountedString& other) const 
        {            
            return (size_ == other.size_ && 
                    (size_ == 0 || (data_[0] == other.data_[0] && memcmp(data_, other.data_, sizeof(char) * size_) == 0)));
        }

        FORCE_INLINE bool operator!=(const char* other) const 
        {
            return !(this->operator==(other));
        }

        FORCE_INLINE bool operator!=(const PooledRefCountedString& other) const 
        {
            return !(this->operator==(other));
        }        

        FORCE_INLINE PooledRefCountedString& operator=(const char* str)
        {
            if ((--(*ptr_count_)) == 0) 
            {   
                *ptr_count_ = 1;        // re-use ptr_count_
                if (data_ != nullptr) delete[] data_;                
            }
            else 
            {   
                ptr_count_ = pool.add();
                *ptr_count_ = 1;
            }
            size_ = strlen(str);
            data_ = new char[size_ + 1];
            memcpy(data_, str, sizeof(char) * size_);
            data_[size_] = 0;
            return *this;
        }

        FORCE_INLINE PooledRefCountedString& operator=(const PooledRefCountedString& str)
        {
            if ((--(*ptr_count_)) == 0) 
            {   
                pool.del(ptr_count_);
                if (data_ != nullptr) delete[] data_;                
            }
            (*str.ptr_count_)++;
            ptr_count_ = str.ptr_count_;
            size_ = str.size_;
            data_ = str.data_;
            return *this;
        }

        FORCE_INLINE PooledRefCountedString substr(uint64_t pos, uint64_t len) const
        {
            return PooledRefCountedString(this->data_ + pos, len);
        }        
    };
}

#endif /* DBTOASTER_STRING_HPP */
