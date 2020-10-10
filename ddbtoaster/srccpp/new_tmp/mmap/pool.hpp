#ifndef DBTOASTER_POOL_HPP
#define DBTOASTER_POOL_HPP

#include <assert.h>

namespace dbtoaster
{
    #define DEFAULT_POOL_CHUNK_SIZE 32     // 2^N

    template<typename T>
    struct Elem 
    {  
        union 
        {
            T obj;
            struct Elem* next; 
        };
        bool used;
      
        Elem() : next(nullptr), used(false) { }
      
        ~Elem() { deactivate(); }

        FORCE_INLINE void deactivate() 
        {
            if (used) { obj.~T(); used = false; }
            next = nullptr;
        }
    };

    template<typename T>
    struct ValueElem 
    {  
        union 
        {
            T obj;
            struct ValueElem* next; 
        };
      
        ValueElem()  { next = nullptr; }     
        ~ValueElem() { next = nullptr; }
    };

    template<typename T>
    class Pool 
    {
        private:
            Elem<T>* free_;
            Elem<T>* data_;
            size_t size_;

            void add_chunk(size_t new_size) 
            {   // precondition: no available elements
                assert(free_ == nullptr);

                size_ = new_size;
                Elem<T>* chunk = new Elem<T>[size_ + 1];
                for (size_t i = 0; i < size_ - 1; i++) 
                {
                    chunk[i].next = &chunk[i + 1];
                }
                chunk[size_ - 1].next = nullptr;
                chunk[size_].next = data_;
                data_ = chunk;
                free_ = chunk;
            }

        public:
            Pool(size_t chunk_size = DEFAULT_POOL_CHUNK_SIZE) : free_(nullptr), data_(nullptr) 
            {
                add_chunk(chunk_size);
            }

            ~Pool() {
                size_t sz = size_;
                while (data_ != nullptr) 
                {
                    Elem<T>* el = data_[sz].next;
                    delete[] data_;
                    data_ = el;
                    sz = sz >> 1;
                } 
            }

            FORCE_INLINE T* add() 
            {
                if (free_ == nullptr) { add_chunk(size_ << 1); }

                Elem<T>* el = free_;
                free_ = free_->next;
                el->used = true;
                // el->next = nullptr;
                return &(el->obj);
            }

            FORCE_INLINE void del(T* obj) 
            { 
                if (obj == nullptr) { return; }

                Elem<T>* el = reinterpret_cast<Elem<T>*>(obj);
                el->deactivate();
                el->next = free_;
                free_ = el; 
            }

            FORCE_INLINE void delete_all(T* current_data)
            {
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

            FORCE_INLINE void clear()
            {
                Elem<T>* prevChunk = nullptr;
                Elem<T>* chunk = data_;
                size_t sz = size_;
                size_t doubleSz = sz << 1;

                while (chunk != nullptr) 
                {
                    if (prevChunk != nullptr) 
                    {
                        prevChunk[doubleSz - 1].next = chunk;
                    }
                    for (size_t i = 0; i < sz - 1; i++) 
                    {
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
    };

    template<typename T>
    class ValuePool 
    {
        private:
            ValueElem<T>* free_;
            ValueElem<T>* data_;
            size_t size_;

            void add_chunk(size_t new_size) 
            {   // precondition: no available elements
                assert(free_ == nullptr);

                size_ = new_size;
                ValueElem<T>* chunk = new ValueElem<T>[size_ + 1];
                for (size_t i = 0; i < size_ - 1; i++) 
                {
                    chunk[i].next = &chunk[i + 1];
                }
                chunk[size_ - 1].next = nullptr;
                chunk[size_].next = data_;
                data_ = chunk;
                free_ = chunk;
            }

        public:
            ValuePool(size_t chunk_size = DEFAULT_POOL_CHUNK_SIZE) : free_(nullptr), data_(nullptr) 
            {
                add_chunk(chunk_size);
            }

            ~ValuePool() {
                size_t sz = size_;
                while (data_ != nullptr) 
                {
                    ValueElem<T>* el = data_[sz].next;
                    delete[] data_;
                    data_ = el;
                    sz = sz >> 1;
                } 
            }

            FORCE_INLINE T* add() 
            {
                if (free_ == nullptr) { add_chunk(size_ << 1); }

                ValueElem<T>* el = free_;
                free_ = free_->next;
                // el->next = nullptr;
                return &(el->obj);
            }

            FORCE_INLINE void del(T* obj) 
            { 
                if (obj == nullptr) { return; }

                ValueElem<T>* el = reinterpret_cast<ValueElem<T>*>(obj);
                el->next = free_; 
                free_ = el;
            }

            FORCE_INLINE void delete_all(T* current_data)
            {
                if (current_data == nullptr) { return; }
            
                T* tmp = current_data;
                do 
                {
                    T* tmpNext = tmp->nxt;   
                    ValueElem<T>* tmpEl = reinterpret_cast<ValueElem<T>*>(tmp);
                    tmpEl->next = (tmpNext != nullptr ? reinterpret_cast<ValueElem<T>*>(tmpNext) : free_);
                    tmp = tmpNext;
                } while (tmp != nullptr);
                free_ = reinterpret_cast<ValueElem<T>*>(current_data);
            }

            FORCE_INLINE void clear()
            {
                ValueElem<T>* prevChunk = nullptr;
                ValueElem<T>* chunk = data_;
                size_t sz = size_;
                size_t doubleSz = sz << 1;

                while (chunk != nullptr) 
                {
                    if (prevChunk != nullptr) 
                    {
                        prevChunk[doubleSz - 1].next = chunk;
                    }
                    for (size_t i = 0; i < sz - 1; i++) 
                    {
                        chunk[i].next = &chunk[i + 1];
                    }
                    chunk[sz - 1].next = nullptr;                    
                    prevChunk = chunk;
                    chunk = chunk[sz].next;
                    doubleSz = sz;
                    sz = sz >> 1;
                }
                free_ = data_;
            }
    };

}

#endif /* DBTOASTER_POOL_HPP */