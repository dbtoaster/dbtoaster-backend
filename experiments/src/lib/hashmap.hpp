#ifndef DBTOASTER_HASHMAP_HPP
#define DBTOASTER_HASHMAP_HPP

#include <iostream>
#include <assert.h>
#include <functional>
#include <string.h>

#include "macro.hpp"
#include "types.hpp"
#include "hash.hpp"
#include "pool.hpp"
#include "serialization.hpp"

namespace dbtoaster 
{
    #define DEFAULT_CHUNK_SIZE 16     // 2^N
    #define INSERT_INTO_MMAP 1
    #define DELETE_FROM_MMAP -1

    template<typename T, typename V>
    class Index 
    {
        public:
            virtual HASH_RES_t computeHash(const T& key) = 0;

            virtual int addOrDelOnZero(const T& k, const V& v) = 0;

            virtual int addOrDelOnZero(const T& k, const V& v, HASH_RES_t h) = 0;

            virtual int setOrDelOnZero(const T& k, const V& v) = 0;

            virtual int setOrDelOnZero(const T& k, const V& v, HASH_RES_t h) = 0;

            virtual void insert(T* obj) = 0;

            virtual void insert(T* obj, const HASH_RES_t h) = 0;

            virtual void del(const T* obj) = 0;

            virtual void del(const T* obj, const HASH_RES_t h) = 0;

            virtual T* get(const T& key, const HASH_RES_t h) const = 0;

            virtual const V& getValueOrDefault(const T& key) const = 0;

            virtual size_t count() const = 0;

            virtual void clear() = 0;

            virtual ~Index() { }
    };


    template<typename T, typename V, typename IDX_FN = T, bool is_unique = true>
    class HashIndex : public Index<T,V>
    {
        public:
            typedef struct __IdxNode 
            {
                T* obj;
                HASH_RES_t hash;            
                struct __IdxNode* nxt;
            } IdxNode;  //  the linked list is maintained 'compactly': 
                        //  if a IdxNode has a nxt, it is full.
            IdxNode* buckets_;
            size_t size_;

        private:
            const V Zero = ZeroValue<V>().get();
            Pool<IdxNode> pool_;
            bool allocated_from_pool_;
            size_t index_mask_;
            size_t count_;
            size_t threshold_;
            double load_factor_;
                      
            void resize_(size_t new_size) 
            {
                IdxNode* old_buckets = buckets_;
                size_t old_size = size_;

                buckets_ = new IdxNode[new_size];
                memset(buckets_, 0, sizeof(IdxNode) * new_size);
                size_ = new_size;
                index_mask_ = size_ - 1;
                threshold_ = size_ * load_factor_;

                bool tmp_allocated_from_pool = false;
                for (size_t i = 0; i < old_size; i++) 
                {
                    IdxNode *src = old_buckets + i;
                    bool pooled = false;
                    do 
                    {
                        if (src->obj != nullptr) 
                        { 
                            HASH_RES_t h = src->hash;
                            IdxNode *dst = buckets_ + (h & index_mask_);
                            if (dst->obj != nullptr) 
                            {
                                tmp_allocated_from_pool = true;
                                IdxNode *new_node = pool_.add(); 
                                
                                //in addition to adding new_node, we also change the place of new_node with dst
                                //to preserve the order of elements, as it is required for
                                //non-unique hash maps
                                new_node->obj = dst->obj;
                                new_node->hash = dst->hash; 
                                new_node->nxt = dst->nxt; 
                                dst->obj = src->obj;
                                dst->hash = h; 
                                dst->nxt = new_node;
                            } 
                            else 
                            {  // space left in last IdxNode
                                dst->obj = src->obj;
                                dst->hash = h; 
                                assert(dst->nxt == nullptr);
                            }
                        }
                        if (pooled) 
                        {
                            IdxNode *d = src;
                            src = src->nxt; 
                            pool_.del(d); 
                        } 
                        else src = src->nxt;
                        pooled = true;
                    } 
                    while (src != nullptr);
                }
                allocated_from_pool_ = tmp_allocated_from_pool;
                if (old_buckets != nullptr) delete[] old_buckets;        
            }

        public:
            HashIndex(size_t size = DEFAULT_CHUNK_SIZE, double load_factor = 0.75) : pool_(size), allocated_from_pool_(false) 
            {
                load_factor_ = load_factor;
                size_ = 0;
                count_ = 0;
                buckets_ = nullptr;
                resize_(size);
            }

            virtual ~HashIndex() { if (buckets_ != nullptr) delete[] buckets_; }

            T& operator[](const T& key) { return *get(key); }
      
            
            FORCE_INLINE T* get(const T& key) const 
            {
                return get(key, IDX_FN::hash(key));
            }

            // returns the first matching element or nullptr if not found  
            FORCE_INLINE T* get(const T& key, const HASH_RES_t h) const 
            {
                IdxNode* n = buckets_ + (h & index_mask_);
                do 
                {
                    if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj)) 
                        return n->obj;
                } while ((n = n->nxt));
                return nullptr;
            }

            FORCE_INLINE const V& getValueOrDefault(const T& key) const 
            {
                return getValueOrDefault(key, IDX_FN::hash(key));
            }

            FORCE_INLINE const V& getValueOrDefault(const T& key, HASH_RES_t h) const 
            {
                IdxNode* n = buckets_ + (h & index_mask_);
                do 
                {
                    if (n->obj && h == n->hash && IDX_FN::equals(key, *n->obj)) 
                    {
                        return n->obj->__av;
                    }
                } while ((n = n->nxt));
                
                return Zero;
            }

            // inserts regardless of whether element  already exists
            FORCE_INLINE void insert(T* obj) 
            {
                insert(obj, IDX_FN::hash(*obj));
            }        

            FORCE_INLINE void insert(T* obj, const HASH_RES_t h) 
            {        
                if (obj == nullptr) return;        
                if (count_ > threshold_) resize_(size_ << 1);

                if (is_unique) insert_unique_nocheck(obj, h);
                else insert_nonunique_nocheck(obj, h);
            }

            FORCE_INLINE void insert_unique_nocheck(T* obj, const HASH_RES_t h) 
            {
                assert(is_unique);

                size_t bucketId = h & index_mask_;
                IdxNode* dst = buckets_ + bucketId;
            
                ++count_;
                if (dst->obj != nullptr) 
                {
                    allocated_from_pool_ = true;
                    IdxNode* new_node = pool_.add(); 
                    new_node->obj = obj;
                    new_node->hash = h; 
                    new_node->nxt = dst->nxt; 
                    dst->nxt = new_node;
                } 
                else 
                {   // space left in last IdxNode
                    dst->obj = obj;
                    dst->hash = h;  
                    assert(dst->nxt == nullptr);
                }
            }

            FORCE_INLINE void insert_nonunique_nocheck(T* obj, const HASH_RES_t h) 
            {
                assert(!is_unique);

                size_t bucketId = h & index_mask_;
                IdxNode* dst = buckets_ + bucketId;
            
                if (dst->obj == nullptr) 
                {   // space left in last IdxNode
                    ++count_;
                    dst->obj = obj;
                    dst->hash = h;  
                    assert(dst->nxt == nullptr);
                    return;
                }
                
                do 
                {
                    if (h == dst->hash && IDX_FN::equals(*obj, *dst->obj)) 
                    {
                        allocated_from_pool_ = true;
                        IdxNode* new_node = pool_.add(); 
                        new_node->obj = obj;
                        new_node->hash = h; 
                        new_node->nxt = dst->nxt; 
                        dst->nxt = new_node;
                        return;
                    }
                    /*
                    else {
                        //go ahead, and look for an element in the same slice
                        //or reach the end of linked list of IdxNodes
                    }
                    */
                } while ((dst = dst->nxt));
              
                assert(dst == nullptr);
                dst = buckets_ + bucketId;
                
                ++count_;       // Count only distinct elements for non-unique index
                
                allocated_from_pool_ = true;
                IdxNode* new_node = pool_.add();
                new_node->obj = dst->obj;
                new_node->hash = dst->hash; 
                new_node->nxt = dst->nxt;
                dst->obj = obj;
                dst->hash = h;            
                dst->nxt = new_node;
            }

            // deletes an existing elements (equality by pointer comparison)
            FORCE_INLINE void del(const T* obj) 
            {
                del(obj, IDX_FN::hash(*obj));
            }

            FORCE_INLINE void del(const T* obj, const HASH_RES_t h) 
            {
                if (obj == nullptr) return;

                IdxNode *dst = buckets_ + (h & index_mask_);
                IdxNode *prev = nullptr;
                IdxNode *next; 

                do 
                {
                    next = dst->nxt;
                    if (dst->obj == obj) //we only need a pointer comparison, as all objects are stored in the pool
                    {
                        if (prev != nullptr) 
                        {   //it is an element in the linked list (and not in the bucket itself)
                            prev->nxt = next;
                            pool_.del(dst);
                        } 
                        else if (next != nullptr) 
                        {   //it is the elements in the bucket, and there are other elements in linked list
                            dst->obj = next->obj;
                            dst->hash = next->hash;
                            dst->nxt = next->nxt;
                            pool_.del(next);
                            next = dst;             // to update count
                        } 
                        else 
                        {   //it is the only element in the bucket
                            dst->obj = nullptr;
                        }

                        if (is_unique || 
                            !((prev && prev->obj && (h == prev->hash) && IDX_FN::equals(*obj, *prev->obj)) || 
                              (next && next->obj && (h == next->hash) && IDX_FN::equals(*obj, *next->obj))))
                        {
                            count_--;
                        }
                        return;
                    }
                    prev = dst;
                } while ((dst = next));
            }

            FORCE_INLINE void clear()
            {
                if (allocated_from_pool_) 
                {                
                    for (size_t i = 0; i < size_; i++) 
                    {
                        pool_.delete_all(buckets_[i].nxt);
                    }
                    allocated_from_pool_ = false;
                }        
                count_ = 0;
                memset(buckets_, 0, sizeof(IdxNode) * size_);
            }

            FORCE_INLINE size_t count() const { return count_; }

            FORCE_INLINE HASH_RES_t computeHash(const T& key) { return IDX_FN::hash(key); }

            FORCE_INLINE int addOrDelOnZero(const T& k, const V& v)
            {
                if (ZeroValue<V>().isZero(v)) { return 0; }
                return addOrDelOnZero(k, v, IDX_FN::hash(k));
            }

            FORCE_INLINE int addOrDelOnZero(const T& k, const V& v, HASH_RES_t h) 
            {
                assert(is_unique);
                if (ZeroValue<V>().isZero(v)) { return 0; }

                IdxNode* n = buckets_ + (h & index_mask_);
                do 
                {
                    if (n->obj && h == n->hash && IDX_FN::equals(k, *n->obj)) 
                    {                    
                        n->obj->__av += v;
                        if (ZeroValue<V>().isZero(n->obj->__av)) 
                        {
                            return DELETE_FROM_MMAP;
                        }
                        return 0;
                    }
                } while ((n = n->nxt));

                // not found
                return INSERT_INTO_MMAP;
            }

            FORCE_INLINE int setOrDelOnZero(const T& k, const V& v)
            {
                return setOrDelOnZero(k, v, IDX_FN::hash(k));
            }

            FORCE_INLINE int setOrDelOnZero(const T& k, const V& v, HASH_RES_t h) 
            {
                assert(is_unique);

                IdxNode* n = buckets_ + (h & index_mask_);
                do 
                {
                    if (n->obj && h == n->hash && IDX_FN::equals(k, *n->obj)) 
                    {                    
                        if (ZeroValue<V>().isZero(v)) 
                        {
                            return DELETE_FROM_MMAP;
                        }
                        n->obj->__av = v;
                        return 0;
                    }
                } while ((n = n->nxt));

                // not found
                return INSERT_INTO_MMAP;
            }

            FORCE_INLINE void* slice(const T& k, HASH_RES_t h) const 
            {
                IdxNode* n = buckets_ + (h & index_mask_);
                do 
                {
                    if (n->obj && h == n->hash && IDX_FN::equals(k, *n->obj)) 
                    {
                        return n;
                    }
                } while ((n = n->nxt));

                // not found
                return nullptr;
            }

            template<class Archive>
            void serialize(Archive& ar, const unsigned int version) const
            {
                ar << "\n\t\t";
                dbtoaster::serialize_nvp(ar, "count", count());
                T* elem;
                for (size_t i = 0; i < size_; i++) 
                {
                    IdxNode* n = buckets_ + i;
                    while (n && (elem = n->obj))
                    {
                        ar << "\n"; dbtoaster::serialize_nvp_tabbed(ar, "item", *elem, "\t\t"); 
                        n = n->nxt;
                    }
                }
            }
    };

    template<typename T, typename V, typename...INDEXES> 
    class MultiHashMap;


    template<typename T, typename V, typename PRIMARY_INDEX>
    class MultiHashMap<T, V, PRIMARY_INDEX>
    {
        private:
            Pool<T> pool;

        public:
            PRIMARY_INDEX* primary_index;
            Index<T,V>** index;

            MultiHashMap() 
            {
                primary_index = new PRIMARY_INDEX();
                index = new Index<T,V>*[1] { primary_index };
            }

            MultiHashMap(size_t init_capacity) 
            {
                primary_index = new PRIMARY_INDEX(init_capacity);
                index = new Index<T,V>*[1] { primary_index };
            }

            ~MultiHashMap() 
            {
                delete primary_index;
                delete[] index;
            }
      
            FORCE_INLINE void insert_nocheck(const T& k) 
            { 
                insert_nocheck(k, primary_index->computeHash(k));
            }

            FORCE_INLINE void insert_nocheck(const T& elem, HASH_RES_t h) 
            { 
                T* cur = pool.add();
                new(cur) T(elem);
                primary_index->insert(cur, h);
            }

            FORCE_INLINE void del(const T& key, HASH_RES_t h) 
            {
                T* elem = primary_index->get(key, h); 
                if (elem == nullptr) return;
                primary_index->del(elem, h);
                pool.del(elem);
            }

            FORCE_INLINE size_t count() const 
            { 
                return primary_index->count(); 
            }

            FORCE_INLINE void clear()
            {
                primary_index->clear();
                pool.clear();
            }

            FORCE_INLINE const V& getValueOrDefault(const T& key) const 
            { 
                return primary_index->getValueOrDefault(key); 
            }

            FORCE_INLINE void addOrDelOnZero(T& k, const V& v) 
            {
                HASH_RES_t h = primary_index->computeHash(k);
                int res = primary_index->addOrDelOnZero(k, v, h);
                if (res == INSERT_INTO_MMAP)
                {
                    k.__av = v;
                    insert_nocheck(k, h);
                }
                else if (res == DELETE_FROM_MMAP)
                {
                    del(k, h);
                }
            }

            FORCE_INLINE void setOrDelOnZero(T& k, const V& v) 
            {
                HASH_RES_t h = primary_index->computeHash(k);
                int res = primary_index->setOrDelOnZero(k, v, h);
                if (res == INSERT_INTO_MMAP)
                {
                    k.__av = v;
                    insert_nocheck(k, h);
                }
                else if (res == DELETE_FROM_MMAP)
                {
                    del(k, h);
                }
            }

            template<class Archive>
            void serialize(Archive& ar, const unsigned int version) const
            {
                primary_index->serialize(ar, version);
            }
    };

    template<typename T, typename V, typename PRIMARY_INDEX, typename SECONDARY_INDEX>
    class MultiHashMap<T, V, PRIMARY_INDEX, SECONDARY_INDEX>
    {
        private:
            Pool<T> pool;

        public:
            PRIMARY_INDEX* primary_index;
            SECONDARY_INDEX* secondary_index;
            Index<T,V>** index;

            MultiHashMap() 
            {   
                primary_index = new PRIMARY_INDEX();
                secondary_index = new SECONDARY_INDEX();
                index = new Index<T,V>*[2]{ primary_index, secondary_index };
            }

            MultiHashMap(size_t init_capacity) 
            {   
                primary_index = new PRIMARY_INDEX(init_capacity);
                secondary_index = new SECONDARY_INDEX(init_capacity);
                index = new Index<T,V>*[2]{ primary_index, secondary_index };
            }

            ~MultiHashMap() 
            {
                delete primary_index;
                delete secondary_index;
                delete[] index;
            }
      
            FORCE_INLINE void insert_nocheck(const T& k) 
            { 
                insert_nocheck(k, primary_index->computeHash(k));
            }

            FORCE_INLINE void insert_nocheck(const T& elem, HASH_RES_t h) 
            { 
                T* cur = pool.add();
                new(cur) T(elem);
                primary_index->insert(cur, h);
                secondary_index->insert(cur);
            }

            FORCE_INLINE void del(const T& key, HASH_RES_t h) 
            {
                T* elem = primary_index->get(key, h); 
                if (elem == nullptr) return;
                primary_index->del(elem, h);
                secondary_index->del(elem);
                pool.del(elem);
            }

            FORCE_INLINE size_t count() const 
            { 
                return primary_index->count(); 
            }

            FORCE_INLINE void clear()
            {
                primary_index->clear();            
                secondary_index->clear();
                pool.clear();
            }

            FORCE_INLINE const V& getValueOrDefault(const T& key) const 
            { 
                return primary_index->getValueOrDefault(key); 
            }

            FORCE_INLINE void addOrDelOnZero(T& k, const V& v) 
            {
                HASH_RES_t h = primary_index->computeHash(k);
                int res = primary_index->addOrDelOnZero(k, v, h);
                if (res == INSERT_INTO_MMAP)
                {
                    k.__av = v;
                    insert_nocheck(k, h);
                }
                else if (res == DELETE_FROM_MMAP)
                {
                    del(k, h);
                }
            }

            FORCE_INLINE void setOrDelOnZero(T& k, const V& v) 
            {
                HASH_RES_t h = primary_index->computeHash(k);
                int res = primary_index->setOrDelOnZero(k, v, h);
                if (res == INSERT_INTO_MMAP)
                {
                    k.__av = v;
                    insert_nocheck(k, h);
                }
                else if (res == DELETE_FROM_MMAP)
                {
                    del(k, h);
                }
            }

            template<class Archive>
            void serialize(Archive& ar, const unsigned int version) const
            {
                primary_index->serialize(ar, version);
            }            
    };


    template<typename T, typename V, typename PRIMARY_INDEX, typename SECONDARY_INDEX1, typename SECONDARY_INDEX2, typename...SECONDARY_INDEXES_REST>
    class MultiHashMap<T, V, PRIMARY_INDEX, SECONDARY_INDEX1, SECONDARY_INDEX2, SECONDARY_INDEXES_REST...>
    {
        private:
            Pool<T> pool;

        public:
            PRIMARY_INDEX* primary_index;
            SECONDARY_INDEX1* secondary_index_1;
            SECONDARY_INDEX2* secondary_index_2;
            Index<T,V>** index;

            MultiHashMap() 
            {   
                primary_index = new PRIMARY_INDEX();
                secondary_index_1 = new SECONDARY_INDEX1();
                secondary_index_2 = new SECONDARY_INDEX2();
                index = new Index<T,V>*[sizeof...(SECONDARY_INDEXES_REST) + 3] { 
                    primary_index, secondary_index_1, secondary_index_2, new SECONDARY_INDEXES_REST()... 
                };
            }

            MultiHashMap(size_t init_capacity) 
            {   
                primary_index = new PRIMARY_INDEX(init_capacity);
                secondary_index_1 = new SECONDARY_INDEX1(init_capacity);
                secondary_index_2 = new SECONDARY_INDEX2(init_capacity);
                index = new Index<T,V>*[sizeof...(SECONDARY_INDEXES_REST) + 3]{ 
                    primary_index, secondary_index_1, secondary_index_2, new SECONDARY_INDEXES_REST()... 
                };
            }

            ~MultiHashMap() 
            {
                delete primary_index;
                delete secondary_index_1;
                for (size_t i = 0;  i < sizeof...(SECONDARY_INDEXES_REST); i++) 
                    delete index[i + 2];
                delete[] index;
            }

            FORCE_INLINE void insert_nocheck(const T& k) 
            { 
                insert_nocheck(k, primary_index->computeHash(k));
            }
      
            FORCE_INLINE void insert_nocheck(const T& elem, HASH_RES_t h) 
            { 
                T* cur = pool.add();
                new(cur) T(elem);
                primary_index->insert(cur, h);
                secondary_index_1->insert(cur);
                secondary_index_2->insert(cur);
                for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES_REST); i++) 
                {
                    index[i + 3]->insert(cur);
                }
            }

            FORCE_INLINE void del(const T& key, HASH_RES_t h) 
            {
                T* elem = primary_index->get(key, h); 
                if (elem == nullptr) return;
                primary_index->del(elem, h);
                secondary_index_1->del(elem);
                secondary_index_2->del(elem);
                for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES_REST); i++) 
                {
                    index[i + 3]->del(elem);
                }
                pool.del(elem);
            }

            FORCE_INLINE size_t count() const 
            {
                return primary_index->count(); 
            }

            FORCE_INLINE void clear()
            {
                primary_index->clear();            
                secondary_index_1->clear();
                secondary_index_2->clear();
                for (size_t i = 0; i < sizeof...(SECONDARY_INDEXES_REST); i++) 
                {
                    index[i + 3]->clear();
                }
                pool.clear();
            }

            FORCE_INLINE const V& getValueOrDefault(const T& key) const 
            { 
                return primary_index->getValueOrDefault(key); 
            }

            FORCE_INLINE void addOrDelOnZero(T& k, const V& v) 
            {
                HASH_RES_t h = primary_index->computeHash(k);
                int res = primary_index->addOrDelOnZero(k, v, h);
                if (res == INSERT_INTO_MMAP)
                {
                    k.__av = v;
                    insert_nocheck(k, h);
                }
                else if (res == DELETE_FROM_MMAP)
                {
                    del(k, h);
                }
            }

            FORCE_INLINE void setOrDelOnZero(T& k, const V& v) 
            {
                HASH_RES_t h = primary_index->computeHash(k);
                int res = primary_index->setOrDelOnZero(k, v, h);
                if (res == INSERT_INTO_MMAP)
                {
                    k.__av = v;
                    insert_nocheck(k, h);
                }
                else if (res == DELETE_FROM_MMAP)
                {
                    del(k, h);
                }
            }

            template<class Archive>
            void serialize(Archive& ar, const unsigned int version) const
            {
                primary_index->serialize(ar, version);
            }            
    };
}

#endif /* DBTOASTER_HASHMAP_HPP */