#ifndef CMMAP_H
#define CMMAP_H

#include <iostream>
#include <assert.h>
#include <functional>
#include <string.h>
#include <libcuckoo/cuckoohash_map.hh>
#include "types.h"
#include "Version.h"
#include "../serialization.hpp"
#include "../hpds/pstring.hpp"
#include "../hpds/macro.hpp"
#include <vector>
#include "Predicate.h"
std::vector<void*> tempMem;

#define DEFAULT_CHUNK_SIZE 32

FORCE_INLINE void clearTempMem() {
    for (auto ptr : tempMem)
        free(ptr);
    tempMem.clear();
}

#define FuncType const std::function<TransactionReturnStatus (T*)>&

template<typename T>
class IndexMV {
public:
    int idxId; //SBJ: Check if it can be removed
    MBase* mmapmv;
    //    virtual bool hashDiffers(const T& x, const T& y) const = 0;

    virtual T* get(const T* key, Transaction& xact) const = 0;

    virtual T* getForUpdate(const T* key, OperationReturnStatus& s, Transaction& xact) = 0;


    virtual OperationReturnStatus add(T* key, EntryMV<T>* obj) = 0;

    virtual void del(T* obj, EntryMV<T>* emv) = 0;

    //    virtual void delCopy(const T* obj, Index<T>* primary) = 0;

    virtual OperationReturnStatus foreach(FuncType f, Transaction& xact) = 0;

    //    virtual void foreachCopy(FuncType f) = 0;

    //    virtual void slice(const T* key, FuncType f) = 0;

    //    virtual void sliceCopy(const T* key, FuncType f) = 0;

    //    virtual void update(T* obj) = 0;
    //
    //    virtual void updateCopy(T* obj, Index<T, V>* primary) = 0;
    //
    //    virtual void updateCopyDependent(T* obj, T* elem) = 0;

    //    virtual size_t count() const = 0;

    //    virtual void clear() = 0;

    virtual void prepareSize(size_t arrayS, size_t poolS) = 0;

    virtual ~IndexMV() {
    };
};

template<typename T, typename IDX_FN >
struct CuckooIndex : public IndexMV<T> {

    struct HE {

        size_t operator()(const T* e) const {
            size_t h = IDX_FN::hash(*e);
            return h;
        }

        bool operator()(const T* e1, const T* e2) const {
            return IDX_FN::cmp(*e1, *e2) == 0;
        }
    };
    cuckoohash_map<T*, EntryMV<T>*, HE, HE, std::allocator<std::pair<T, EntryMV<T>*>>> index;

    std::atomic<EntryMV<T>*> dataHead;

    CuckooIndex(int s = 0) : index((1 << 25)) { //Constructor argument is ignored
        dataHead = nullptr;
    }

    CuckooIndex(void* ptr, int s = 0) : index(1 << 25) { //Constructor argument is ignored
        dataHead = nullptr;
    }

    bool operator==(CuckooIndex<T, IDX_FN>& that) {
        auto t1 = index.lock_table();
        bool flag = true;
        Version<T>* v1, *v2;
        for (auto e1 = t1.cbegin(); e1 != t1.cend(); ++e1) {
            EntryMV<T>* e2;
            v1 = e1->second->versionHead;
            //SBJ: v1 cannot be nullptr if rollback removes EntryMV if all versions are gone
            if (!v1 || v1->obj.isInvalid)
                continue;
            if (!that.index.find(e1->first, e2)) {
                std::cerr << v1->obj << "is extra in table" << std::endl;
                flag = false;
            } else {
                v2 = e2->versionHead;
                if (!(v2->obj == v1->obj)) {
                    std::cerr << "Found " << v1->obj << " where it should have been " << v2->obj << std::endl;
                    flag = false;
                }
            }
        }
        t1.release();
        auto t2 = that.index.lock_table();
        for (auto e2 = t2.cbegin(); e2 != t2.cend(); ++e2) {
            EntryMV<T>* e1;
            v2 = e2->second->versionHead;
            if (!index.find(e2->first, e1)) {
                std::cerr << v2->obj << " is missing from table " << std::endl;
                flag = false;
            } else {
                v1 = e1->versionHead;
                if (!(v1->obj == v2->obj)) {
                    std::cerr << "Found" << v1->obj << " where it should have been " << v2->obj << std::endl;
                    flag = false;
                }
            }
        }
        return flag;
    }

    void getSizeStats(std::ostream & fout) {
        fout << "{}";
    }

    //SBJ: Only for data  result loading . To be removed later

    void add(T* obj, Transaction& xact) {
        Version<T>* v = (Version<T>*) malloc(sizeof (Version<T>));
        new(v) Version<T>(*obj, xact);
        EntryMV<T>* e = (EntryMV<T>*) malloc(sizeof (EntryMV<T>));
        new(e) EntryMV<T>(nullptr, v);
        v->e = (EntryMV<void>*)e;
        index.insert(*obj, e);
        xact.undoBufferHead = v;
    }

    OperationReturnStatus add(T* key, EntryMV<T>* obj) override {
        auto idxId = IndexMV<T>::idxId;
        T* keyC = key->copy();
        //need to pass copy as key is sampleEntry that is hoisted
        if (index.insert(keyC, obj)) {
            if (idxId == 0) {
                EntryMV<T>* dh = dataHead;
                obj->nxt = dh;
                while (!dataHead.compare_exchange_weak(dh, obj)) {
                    obj->nxt = dh;
                }
            }
            return OP_SUCCESS;
        } else {
            free(keyC);
            return OP_SUCCESS;
            return DUPLICATE_KEY;
        }
    }

    //SBJ: what should a multiversion clear be?
    //    void clear() override {
    //        index.clear();
    //        if (dataHead) {
    //            EntryMV<T>* tmp;
    //            Version<T>* VH, *tmpV;
    //            while (dataHead != nullptr) {
    //                tmp = dataHead;
    //                dataHead = dataHead->nxt;
    //                VH = tmp->versionHead;
    //                free(tmp);
    //                while (VH != nullptr) {
    //                    tmpV = VH;
    //                    VH = VH->oldV;
    //                    free(tmpV);
    //                }
    //            }
    //        }
    //    }

    //    size_t count() const override {
    //        return -1;
    //    }

    void del(T* obj, EntryMV<T>* emv) override {
        EntryMV<T>* nxt = emv->nxt;
        while (!emv->nxt.compare_exchange_strong(nxt, mark(nxt))); //removing from foreach list
        //SBJ: TODO: Mark other fields as well???
        index.erase(obj);
        //SBJ: TODO:  free the memory for key store in cuckoo
    }

    //        void del(T* obj) override {
    //            
    //            if (idxId == 0) {
    //                EntryMV< *elemPrv = obj->prv, *elemNxt = obj->nxt;
    //                if (elemPrv)
    //                    elemPrv->nxt = elemNxt;
    //                else
    //                    dataHead = elemNxt;
    //    
    //                if (elemNxt) elemNxt->prv = elemPrv;
    //    
    //                obj->nxt = nullptr;
    //                obj->prv = nullptr;
    //            }
    //    
    //            if (index.erase(obj)) {
    //                count_--;
    //            } else {
    //                throw std::logic_error("Delete failed");
    //            }
    //        }

    //    void delCopy(const T* obj, Index<T, V>* primary) override {
    //        T* orig = primary->get(obj);
    //        del(orig);
    //    }

    OperationReturnStatus foreach(FuncType f, Transaction& xact) override {
        EntryMV<T>* cur = dataHead;
        ForEachPred<T>* pred = (ForEachPred<T>*) malloc(sizeof (ForEachPred<T>));
        new(pred) ForEachPred<T>(xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
        xact.predicateHead = pred;
        while (cur) {
            //SBJ: TODO check for tombstoned entries and delete them
            Version<T>* v = cur->getCorrectVersion(xact);
            auto st = f(&v->obj);
            if (st != SUCCESS)
                return OR(st);
            cur = cur->nxt;
        }
        return OP_SUCCESS;
    }

    //    void foreachCopy(FuncType f) override {
    //        std::vector<T*> entries;
    //        T* cur = dataHead;
    //        while (cur) {
    //            entries.push_back(cur->copy());
    //            cur = cur->nxt;
    //        }
    //        for (auto it : entries) {
    //            f(it);
    //            free(it); //Not calling destructor
    //        }
    //    }

    T* get(const T* key, Transaction& xact) const override {
        EntryMV<T>* result;
        GetPred<T, IDX_FN>* pred = (GetPred<T, IDX_FN>*) malloc(sizeof (GetPred<T, IDX_FN>));
        new(pred) GetPred<T, IDX_FN>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
        xact.predicateHead = pred;
        if (index.find(key, result)) {
            Version<T>* v = result->getCorrectVersion(xact);
            if (v->obj.isInvalid)
                return nullptr;
            return &v->obj;
        } else {
            return nullptr;
        }
    }

    T* getForUpdate(const T* key, OperationReturnStatus& st, Transaction& xact) override {
        EntryMV<T>* result;
        if (index.find(key, result)) {
            Version<T>* resV = result->versionHead;

            if (!resV->isVisible(&xact)) {
                if (resV->xactid > initCommitTS) {
                    Transaction* otherXact = TStoPTR(resV->xactid);
                    xact.failedBecauseOf = otherXact;
                }
                st = WW_VALUE;
                return nullptr;
            }

            if (resV->obj.isInvalid) {
                st = NO_KEY;
                return nullptr;
            }

            Version<T> *newv = (Version<T> *) malloc(sizeof (Version<T>));
            new(newv) Version<T>(resV, xact);
            
            if (!result->versionHead.compare_exchange_strong(resV, newv)) {
                if (resV->xactid > initCommitTS) {
                    Transaction* otherXact = TStoPTR(resV->xactid);
                    xact.failedBecauseOf = otherXact;
                }
                st = WW_VALUE;
                free(newv);
                return nullptr;
            }


            GetPred<T, IDX_FN>* pred = (GetPred<T, IDX_FN>*) malloc(sizeof (GetPred<T, IDX_FN>));
            new(pred) GetPred<T, IDX_FN>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            xact.predicateHead = pred;
            xact.undoBufferHead = newv;
            st = OP_SUCCESS;
            return &newv->obj;
        } else {
            st = NO_KEY;
            return nullptr;
        }
    }

    void prepareSize(size_t arrayS, size_t poolS) override {
        index.reserve(arrayS);
    }
    //
    //    void slice(const T* key, FuncType f) override {
    //    }

    //    void sliceCopy(const T* key, FuncType f) override {
    //    }

    //    void update(T* obj) override {
    //    }
    //
    //    void updateCopy(T* obj, Index<T, V>* primary) override {
    //    }
    //
    //    void updateCopyDependent(T* obj, T* elem) override {
    //    }
    //
    //    bool getOrInsert(T*& entry) override {
    //
    //        return false;
    //    }

    virtual ~CuckooIndex() {

    }

    /******************* non-virtual function wrappers ************************/
    FORCE_INLINE T* get(const T& key, Transaction& xact) const {
        return get(&key, xact);
    }

    FORCE_INLINE T* getForUpdate(const T& key, OperationReturnStatus& st, Transaction& xact) {
        return getForUpdate(&key, st, xact);
    }
    //    FORCE_INLINE T* getCopy(const T* key) const {
    //        T* obj = get(key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE T* getCopy(const T& key) const {
    //        T* obj = get(&key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE T* getCopyDependent(const T* key) const {
    //        T* obj = get(key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE T* getCopyDependent(const T& key) const {
    //        T* obj = get(&key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }

    //    FORCE_INLINE void slice(const T& key, FuncType f) {
    //        slice(&key, f);
    //    }

    //    FORCE_INLINE void sliceCopy(const T& key, FuncType f) {
    //        sliceCopy(&key, f);
    //    }
    //
    //    FORCE_INLINE void sliceCopyDependent(const T* key, FuncType f) {
    //        sliceCopy(key, f);
    //    }
    //
    //    FORCE_INLINE void sliceCopyDependent(const T& key, FuncType f) {
    //        sliceCopy(&key, f);
    //    }
    //
    //    FORCE_INLINE void delCopyDependent(const T* obj) {
    //        del(obj);
    //    }

};

template<typename T, typename IDX_FN>
struct ConcurrentCuckooSecondaryIndex : public IndexMV<T> {

    struct HE {

        size_t operator()(const T* e) const {
            size_t h = IDX_FN::hash(*e);

            return h;
        }

        bool operator()(const T* e1, const T* e2) const {

            return IDX_FN::cmp(*e1, *e2) == 0;
        }
    };

    struct Container {
        EntryMV<T>* e;
        std::atomic<Container *> next;

        Container(EntryMV<T>* e) :
        e(e), next(nullptr) {
        }

        Container(Container *nxt) : e(nullptr), next(nxt) {

        }
    };

    cuckoohash_map<T*, Container*, HE, HE, std::allocator<std::pair<T*, Container*>>> index;

    ConcurrentCuckooSecondaryIndex(size_t size = 100000) : index((1 << 25)) {
    }
    // Inserts an entry into the secondary index.
    //Uses cuckoo hashmap as backend
    //Inserts the entry if it does not exist already in cuckoo index, otherwise if it exists,updates it
    //Cuckoo points towards a sentinel to protect against concurrent insertions/deletions

    OperationReturnStatus add(T* key, EntryMV<T>* obj) override {
        Container *newc = (Container *) malloc(sizeof (Container));
        new(newc) Container(obj);
        Container *sentinel = (Container*) malloc(sizeof (Container));
        new(sentinel) Container(newc);
        T* keyc = key->copy();
        auto updatefn = [newc, sentinel](Container* &c) {
            free(sentinel);
            Container *nxt = c->next;
            do {
                newc->next = nxt;
            } while (!c->next.compare_exchange_weak(nxt, newc));
        };
        index.upsert(keyc, updatefn, sentinel);

        return OP_SUCCESS;
        //SBJ: Mem leak if update happens instead of insert for key->copy 
    }

    //Marks an entry for removal from concurrent list
    //Will be actually removed only by a later traversal
    //Removes other nodes marked for removal during its traversal
    // Loop focus on cur. prev is before cur, curNext is afterCur. prevNext is node after prev (ideally, cur)
    // ..... prev -> prevNext (....) cur -> curNext ...
    // a node is said to be marked for removal if its next pointer is marked.
    //For example, to see if cur is deleted, we check isMarked(curNext)

    void del(T* obj, EntryMV<T>* emv) override {
        Container *sentinel, *cur;
        if (index.find(obj, sentinel) && ((cur = sentinel->next) != nullptr)) {
            Container* prev = sentinel, *curNext = cur->next, *prevNext = cur;
            //while cur is a deleted node or not what we are looking for
            while (isMarked(curNext) || cur->e != emv) {
                //if cur is not a deleted node, we can remove everything between prev and cur
                if (!isMarked(curNext)) {
                    if (prevNext != cur) { //if prevNext is same as cur, there is nothing in between
                        prev->next.compare_exchange_strong(prevNext, cur);
                    }
                    //cur becomes prev and the new value of cur comes from curNext                    
                    prev = cur;
                    prevNext = curNext;
                    cur = curNext;
                } else {
                    //curNext is marked, so we get the unmarked version
                    cur = unmark(curNext);
                }
                if (!cur) //stop at nullptr
                    break;
                curNext = cur->next;
            }
            if (cur == nullptr) {
                //Element not present
                //Remove any marked nodes from prev until here
                if (prevNext != cur) {
                    prev->next.compare_exchange_strong(prevNext, cur);
                }

            } else {
                //mark cur for deletion by marking its next pointer 
                while (!cur->next.compare_exchange_weak(curNext, mark(curNext)));

                //attempt to fix prev, if it fails, we dont care
                prev->next.compare_exchange_strong(prevNext, curNext);
            }
        } else {
            throw std::logic_error("Entry to be deleted not in Secondary Index");
        }

    }

    FORCE_INLINE OperationReturnStatus slice(const T& key, FuncType f, Transaction& xact) {
        return slice(&key, f, xact);
    }

    FORCE_INLINE OperationReturnStatus slice(const T* key, FuncType f, Transaction& xact) {
        Container *sentinel;
        SlicePred<T, IDX_FN>* pred = (SlicePred<T, IDX_FN>*) malloc(sizeof (SlicePred<T, IDX_FN>));
        new(pred) SlicePred<T, IDX_FN>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
        xact.predicateHead = pred;
        if (index.find(key, sentinel)) {
            Container *prev = sentinel, *prevNext = sentinel->next, *cur = prevNext, *curNext;
            //SBJ: TODO: Skip all deleted nodes and remove them

            do {
                curNext = cur -> next;
                while (isMarked(curNext)) {
                    cur = unmark(curNext);
                    if (!cur)
                        break;
                    curNext = cur->next;
                }
                prev->next.compare_exchange_strong(prevNext, cur);
                Version<T>* v = cur->e->versionHead;
                if (!v->isVisible(&xact)) {
                    if (v->xactid > initCommitTS) {
                        Transaction* otherXact = TStoPTR(v->xactid);
                        xact.failedBecauseOf = otherXact;
                    }
                    return WW_VALUE;
                }
                if (v && !v->obj.isInvalid) {
                    Version<T> * newV = (Version<T>*)malloc(sizeof (Version<T>));
                    new(newV) Version<T>(v, xact);
                 
                    if (!cur->e->versionHead.compare_exchange_strong(v, newV)) {
                        if (v->xactid > initCommitTS) {
                            Transaction* otherXact = TStoPTR(v->xactid);
                            xact.failedBecauseOf = otherXact;
                        }
                        free(newV);
                        return WW_VALUE;
                    }
                    xact.undoBufferHead = newV;
                    auto st = f(&newV->obj);
                    if (st != SUCCESS)
                        return OR(st);
                }
                prev = cur;
                prevNext = curNext;
                cur = curNext;
            } while (cur);
            return OP_SUCCESS;
        } else {
            throw std::logic_error("Empty slice");
            return NO_KEY;
        }
    }

    FORCE_INLINE OperationReturnStatus sliceNoUpdate(const T& key, FuncType f, Transaction& xact) {
        return sliceNoUpdate(&key, f, xact);
    }

    FORCE_INLINE OperationReturnStatus sliceNoUpdate(const T* key, FuncType f, Transaction& xact) {
        Container *sentinel;
        SlicePred<T, IDX_FN>* pred = (SlicePred<T, IDX_FN>*) malloc(sizeof (SlicePred<T, IDX_FN>));
        new(pred) SlicePred<T, IDX_FN>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
        xact.predicateHead = pred;
        if (index.find(key, sentinel)) {
            Container *prev = sentinel, *prevNext = sentinel->next, *cur = prevNext, *curNext;
            //SBJ: TODO: Skip all deleted nodes and remove them

            do {
                curNext = cur -> next;
                while (isMarked(curNext)) {
                    cur = unmark(curNext);
                    if (!cur)
                        break;
                    curNext = cur->next;
                }
                prev->next.compare_exchange_strong(prevNext, cur);
                if (!cur)
                    break;
                
                Version<T>* v = cur->e->getCorrectVersion(xact);

                if (v && !v->obj.isInvalid) {
                    auto st = f(&v->obj);
                    if (st != SUCCESS)
                        return OR(st);
                }
                prev = cur;
                prevNext = curNext;
                cur = curNext;
            } while (cur);
            return OP_SUCCESS;
        } else {
            return NO_KEY;
        }
    }

    //    void clear() override {
    //        index.clear();
    //    }
    //
    //    size_t count() const override {
    //        return -1;
    //    }

    //    void delCopy(const T* obj, Index<T, V>* primary) override {
    //        T* orig = primary->get(obj);
    //        del(orig);
    //    }

    OperationReturnStatus foreach(FuncType f, Transaction& xact) override {
        return NO_KEY;
    }

    //    void foreachCopy(FuncType f) override {
    //
    //    }

    T* get(const T* key, Transaction& xact) const override {
        return nullptr;
    }

    T* getForUpdate(const T* key, OperationReturnStatus& st, Transaction& xact) override {
        st = NO_KEY;
        return nullptr;
    }

    //    bool hashDiffers(const T& x, const T& y) const override {
    //        return IDX_FN::hash(x) != IDX_FN::hash(y);
    //    }

    void prepareSize(size_t arrayS, size_t poolS) override {
        index.reserve(arrayS);
    }

    //    void sliceCopy(const T* key, FuncType f) override {
    //
    //    }
    //
    //    void update(T* obj) override {
    //
    //    }
    //
    //    void updateCopy(T* obj, Index<T, V>* primary) override {
    //
    //    }
    //
    //    void updateCopyDependent(T* obj, T* elem) override {
    //
    //    }
    //

    virtual ~ConcurrentCuckooSecondaryIndex() {

    }

    void getSizeStats(std::ostream & fout) {

        fout << "{}";
    }

    /******************* non-virtual function wrappers ************************/
    FORCE_INLINE T* get(const T& key, Transaction& xact) const {
        return get(&key, xact);
    }

    //    FORCE_INLINE T* getCopy(const T* key) const {
    //        T* obj = get(key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE T* getCopy(const T& key) const {
    //        T* obj = get(&key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE T* getCopyDependent(const T* key) const {
    //        T* obj = get(key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE T* getCopyDependent(const T& key) const {
    //        T* obj = get(&key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE void slice(const T& key, FuncType f) {
    //        slice(&key, f);
    //    }

    //    FORCE_INLINE void sliceCopy(const T& key, FuncType f) {
    //        sliceCopy(&key, f);
    //    }
    //
    //    FORCE_INLINE void sliceCopyDependent(const T* key, FuncType f) {
    //        sliceCopy(key, f);
    //    }
    //
    //    FORCE_INLINE void sliceCopyDependent(const T& key, FuncType f) {
    //        sliceCopy(&key, f);
    //    }
    //
    //    FORCE_INLINE void delCopyDependent(const T* obj) {
    //        del(obj);
    //    }

};

struct MBase {
    virtual void del(void *obj, void* emv) = 0;
};

template<typename T, typename...INDEXES>
class MultiHashMapMV : MBase {
private:

    bool *modified;
public:

    IndexMV<T>** index;

    MultiHashMapMV() { // by defintion index 0 is always unique
        index = new IndexMV<T>*[sizeof...(INDEXES)] {
            new INDEXES(DEFAULT_CHUNK_SIZE)...
        };
        modified = new bool[sizeof...(INDEXES)];
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            index[i]->mmapmv = this;
            index[i]->idxId = i;
            modified[i] = false;
        }
    }

    MultiHashMapMV(const size_t* arrayLengths, const size_t* poolSizes) { // by defintion index 0 is always unique
        index = new IndexMV<T>*[sizeof...(INDEXES)] {
            new INDEXES()...
        };
        modified = new bool[sizeof...(INDEXES)];
        for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            index[i]->mmapmv = this;
            index[i]->prepareSize(arrayLengths[i], poolSizes[i + 1]);
            index[i]->idxId = i;
            modified[i] = false;
        }
    }

    ~MultiHashMapMV() {

        for (size_t i = 0; i<sizeof...(INDEXES); ++i) delete index[i];
        delete[] index;
        delete[] modified;
    }

    FORCE_INLINE T* get(const T& key, const size_t idx, Transaction& xact) const {
        return index[idx]->get(&key, xact);
    }

    FORCE_INLINE T* get(const T* key, const size_t idx, Transaction& xact) const {
        return index[idx]->get(key, xact);
    }

    //    FORCE_INLINE T* getCopy(const T& key, const size_t idx = 0) const {
    //        T* obj = index[idx]->get(&key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }

    //    FORCE_INLINE T* getCopy(const T* key, const size_t idx = 0) const {
    //        T* obj = index[idx]->get(key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }

    //    FORCE_INLINE T* getCopyDependent(const T* key, const size_t idx = 0) const {
    //        T* obj = index[idx]->get(key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }
    //
    //    FORCE_INLINE T* getCopyDependent(const T& key, const size_t idx = 0) const {
    //        T* obj = index[idx]->get(&key);
    //        if (obj) {
    //            T* ptr = obj->copy();
    //            tempMem.push_back(ptr);
    //            return ptr;
    //        } else
    //            return nullptr;
    //    }

    //    FORCE_INLINE T* copyIntoPool(const T* e) {
    //        T* copy = (T*) malloc(sizeof(T));
    //        new(copy) T(*e);
    //        return copy;
    //    }
    //
    //    FORCE_INLINE T* copyIntoPool(const T& e) {
    //        T* copy = (T*) malloc(sizeof(T));
    //        new(copy) T(e);
    //        return copy;
    //    }

    FORCE_INLINE OperationReturnStatus add(T& obj, Transaction& xact) {
        return add(&obj, xact);
    }

    FORCE_INLINE OperationReturnStatus add(T* elem, Transaction& xact) {
        T* cur = index[0]->get(elem);
        if (cur == nullptr) {
            Version<T>* newV = (Version<T>*) malloc(sizeof (Version<T>));
            new(newV) Version<T>(*cur, xact);
            newV->xactid = PTRtoTS(xact);
            EntryMV<T> * newE = (EntryMV<T> *) malloc(sizeof (EntryMV<T>));
            new(newE) EntryMV<T>(this, newV);
            newV->e = (EntryMV<void>*) newE;
            auto primarySt = index[0] -> add(elem, newE);
            if (primarySt == OP_SUCCESS) {
                for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->add(elem, newE);
                return OP_SUCCESS;
            } else {
                free(newE);
                free(newV);
                return OP_SUCCESS;
                return DUPLICATE_KEY;
            }
            xact.undoBufferHead = newV;
        } else {
            return OP_SUCCESS;
            return DUPLICATE_KEY;
            throw std::logic_error("Element already exists");
            // cur->~T();
            // *cur=std::move(*elem);

            //            for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            //                if (index[i]->hashDiffers(*cur, *elem)) {
            //                    index[i]->del(cur);
            //                    modified[i] = true;
            //                }
            //            }
            //            new(cur) T(*elem);
            //            for (size_t i = 0; i<sizeof...(INDEXES); ++i) {
            //                if (modified[i]) {
            //                    index[i]->add(cur);
            //                    modified[i] = false;
            //                }
            //            }
        }
    }

    FORCE_INLINE OperationReturnStatus insert_nocheck(T& elem, Transaction& xact) {
        return insert_nocheck(&elem, xact);
    }

    FORCE_INLINE OperationReturnStatus insert_nocheck(T* elem, Transaction& xact) {
        Version<T>* newV = (Version<T>*) malloc(sizeof (Version<T>));
        new(newV) Version<T>(*elem, xact);
        EntryMV<T>* newE = (EntryMV<T>*) malloc(sizeof (EntryMV<T>));
        new(newE) EntryMV<T>(this, newV);
        newV->e = (EntryMV<void>*) newE;
        //        newV->obj.e = newE;
        auto primarySt = index[0] -> add(elem, newE);
        if (primarySt == OP_SUCCESS) {
            xact.undoBufferHead = newV;
            for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->add(elem, newE);
            return OP_SUCCESS;
        } else {
            free(newE);
            free(newV);
            return DUPLICATE_KEY;
        }
    }

    FORCE_INLINE void del(void* o, void* e) override {
        T* obj = (T*) o;
        EntryMV<T>* emv = (EntryMV<T>*) e;
        for (uint i = 0; i < sizeof...(INDEXES); ++i)
            index[i]->del(obj, emv);
    }

    //    FORCE_INLINE void del(T* elem) { // assume that the element is already in the map
    //        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
    //        pool.del(elem);
    //    }
    //
    //    FORCE_INLINE void delCopyDependent(T* obj) {
    //        T* elem = index[0]->get(obj);
    //        for (size_t i = 0; i<sizeof...(INDEXES); ++i) index[i]->del(elem);
    //        pool.del(elem);
    //    }
    //
    //    FORCE_INLINE void delCopy(T* obj) {
    //        T* elem = index[0]->get(obj);
    //        for (size_t i = sizeof...(INDEXES) - 1; i != 0; --i)
    //            index[i]->delCopy(obj, index[0]);
    //        index[0]->delCopy(obj, index[0]);
    //        pool.del(elem);
    //    }

    FORCE_INLINE OperationReturnStatus foreach(FuncType f, Transaction& xact) {
        return index[0]->foreach(f, xact);
    }

    //    FORCE_INLINE void foreachCopy(FuncType f) {
    //        index[0]->foreachCopy(f);
    //    }
    //
    //    void slice(int idx, const T* key, FuncType f) {
    //        index[idx]->slice(key, f);
    //    }
    //
    //    void slice(int idx, const T& key, FuncType f) {
    //        index[idx]->slice(&key, f);
    //    }

    //    void sliceCopy(int idx, const T* key, FuncType f) {
    //        index[idx]->sliceCopy(key, f);
    //    }
    //
    //    void sliceCopy(int idx, const T& key, FuncType f) {
    //        index[idx]->sliceCopy(&key, f);
    //    }
    //
    //    void sliceCopyDependent(int idx, const T* key, FuncType f) {
    //        index[idx]->sliceCopy(key, f);
    //    }
    //
    //    void sliceCopyDependent(int idx, const T& key, FuncType f) {
    //        index[idx]->sliceCopy(&key, f);
    //    }
    //
    //    FORCE_INLINE void update(T* elem) {
    //        if (elem == nullptr)
    //            return;
    //        for (size_t i = 0; i < sizeof...(INDEXES); ++i) {
    //            index[i]->update(elem);
    //        }
    //    }
    //
    //    FORCE_INLINE void updateCopyDependent(T* obj2) {
    //        if (obj2 == nullptr)
    //            return;
    //        T* elem = index[0]->get(obj2);
    //        T* obj = copyIntoPool(obj2);
    //        for (size_t i = 0; i < sizeof...(INDEXES); ++i) {
    //            index[i]->updateCopyDependent(obj, elem);
    //        }
    //    }
    //
    //    FORCE_INLINE void updateCopy(T* obj2) {
    //        if (obj2 == nullptr)
    //            return;
    //
    //        T* obj = copyIntoPool(obj2);
    //        //i >= 0 cant be used with unsigned type
    //        for (size_t i = sizeof...(INDEXES) - 1; i != 0; --i) {
    //            index[i]->updateCopy(obj, index[0]);
    //        }
    //        index[0]->updateCopy(obj, index[0]);
    //    }

    //    FORCE_INLINE size_t count() const {
    //        return index[0]->count();
    //    }
    //
    //    FORCE_INLINE void clear() {
    //        for (size_t i = sizeof...(INDEXES) - 1; i != 0; --i)
    //            index[i]->clear();
    //        index[0]->clear();
    //    }

    //    template<class Archive>
    //    void serialize(Archive& ar, const unsigned int version) const {
    //        ar << "\n\t\t";
    //        dbtoaster::serialize_nvp(ar, "count", count());
    //        //SBJ: Hack! fix it!  Cannot use store.foreach directly , as the last index may not be ListIndex created
    //        auto idx = const_cast<Index<T, V> *> (index[0]);
    //        idx->foreach([&ar] (T * e) {
    //            ar << "\n"; dbtoaster::serialize_nvp_tabbed(ar, "item", *e, "\t\t"); });
    //    }
};

#endif //MMAP_H
