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
#include <atomic>
#include <type_traits>
#include "SpinLock.h"
std::vector<void*> tempMem;

#define DEFAULT_CHUNK_SIZE 32


#ifndef DEFAULT_HEAP_SIZE
#define DEFAULT_HEAP_SIZE 16
#endif

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


    virtual OperationReturnStatus add(Version<T>* v) = 0;

    virtual void removeEntry(T* obj, EntryMV<T>* emv) = 0;
    virtual void undo(Version<T>* v) = 0;
    virtual void del(Version<T>* v) = 0;
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

template <typename T, typename IDX_FN>
struct HE_ {

    size_t operator()(const T* e) const {
        size_t h = IDX_FN::hash(*e);
        return h;
    }

    bool operator()(const T* e1, const T* e2) const {
        return IDX_FN::cmp(*e1, *e2) == 0;
    }
};

template<typename T, typename IDX_FN >
struct CuckooIndex : public IndexMV<T> {
    typedef HE_<T, IDX_FN> HE;
    cuckoohash_map<T*, EntryMV<T>*, HE, HE, std::allocator<std::pair<T, EntryMV<T>*>>> index;

    std::atomic<EntryMV<T>*> dataHead;

    CuckooIndex(int s = 0) : index((1 << 25)) { //Constructor argument is ignored
        dataHead = nullptr;
    }

    CuckooIndex(void* ptr, int s = 0) : index(1 << 25) { //Constructor argument is ignored
        dataHead = nullptr;
    }

    FORCE_INLINE bool operator==(CuckooIndex<T, IDX_FN>& that) {
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

    FORCE_INLINE void getSizeStats(std::ostream & fout) {
        fout << "{}";
    }

    //SBJ: Only for data  result loading . To be removed later

    FORCE_INLINE void add(T* obj, Transaction& xact) {
        Version<T>* v = (Version<T>*) malloc(sizeof (Version<T>));
        new(v) Version<T>(*obj, xact);
        EntryMV<T>* e = (EntryMV<T>*) malloc(sizeof (EntryMV<T>));
        new(e) EntryMV<T>(nullptr, *obj, v);
        v->e = e;
        index.insert(obj, e);
        xact.undoBufferHead = v;
    }

    FORCE_INLINE OperationReturnStatus add(Version<T>* newv) override {
        auto idxId = IndexMV<T>::idxId;
        T* keyC = &newv->obj;
        EntryMV<T> *emv = (EntryMV<T>*) newv->e;
        if (index.insert(keyC, emv)) {
            if (idxId == 0) {
                EntryMV<T>* dh = dataHead;
                emv->nxt = dh;
                while (!dataHead.compare_exchange_weak(dh, emv)) {
                    emv->nxt = dh;
                }
            }
            return OP_SUCCESS;
        } else {
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

    FORCE_INLINE void removeEntry(T* obj, EntryMV<T>* emv) override {
        EntryMV<T>* nxt = emv->nxt;
        while (!emv->nxt.compare_exchange_strong(nxt, mark(nxt))); //removing from foreach list
        //SBJ: TODO: Mark other fields as well???
        index.erase(obj);
        //SBJ: TODO:  free the memory for key store in cuckoo
    }

    FORCE_INLINE void undo(Version<T>* v) override {
        //Do nothign
    }

    FORCE_INLINE void del(Version<T>* v) override {
        //Do nothing for primary hash index
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

    FORCE_INLINE OperationReturnStatus foreach(FuncType f, Transaction& xact) override {
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

    FORCE_INLINE T* get(const T* key, Transaction& xact) const override {
        EntryMV<T>* result;
        if (index.find(key, result)) {
            Version<T>* v = result->getCorrectVersion(xact);
            if (v->obj.isInvalid)
                return nullptr;
            GetPred<T, IDX_FN>* pred = (GetPred<T, IDX_FN>*) malloc(sizeof (GetPred<T, IDX_FN>));
            new(pred) GetPred<T, IDX_FN>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            xact.predicateHead = pred;
            return &v->obj;
        } else {
            return nullptr;
        }
    }

    FORCE_INLINE T* getForUpdate(const T* key, OperationReturnStatus& st, Transaction& xact) override {
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

    FORCE_INLINE void prepareSize(size_t arrayS, size_t poolS) override {
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

template <typename T, typename IDX_FN, size_t size>
struct ConcurrentArrayIndex : public IndexMV<T> {

    template<typename A>
    struct ALIGN CacheAtomic {
        std::atomic<A> elem;
    };

    typedef CacheAtomic<EntryMV<T>*> AlignedEntry;
    AlignedEntry array[size];

    bool operator==(const ConcurrentArrayIndex<T, IDX_FN, size>& that) {
        for (size_t i = 0; i < size; ++i) {
            EntryMV<T>* e1 = array[i].elem;
            EntryMV<T>* e2 = that.array[i].elem;
            
            if ((!e1 && e2) || (e1 && !e2)) {
                cerr << "Array slots don't match" << endl;
                if(e1) 
                    cerr << e1->versionHead.load()->obj << "is extra";
                else
                    cerr << e2->versionHead.load()->obj << "is missing";
                return false;
            }
            if(!e1)
                continue;
            T& t1 = e1->versionHead.load()->obj;
            T& t2 = e2->versionHead.load()->obj;
            if(!(t1 == t2)) {
                cerr << "Found " << t1 << "  where it should have been " << t2 << endl;
                return false;
            }
        }
        return true;
    }

    ConcurrentArrayIndex(size_t s) {//ignore
        memset(array, 0, sizeof (AlignedEntry) * size);
    }
    ConcurrentArrayIndex(void* ptr, size_t s) {//ignore
        memset(array, 0, sizeof (AlignedEntry) * size);
    }

    //Data Result loading 
    FORCE_INLINE void add(T* obj, Transaction& xact) {
        Version<T>* v = (Version<T>*) malloc(sizeof (Version<T>));
        new(v) Version<T>(*obj, xact);
        EntryMV<T>* e = (EntryMV<T>*) malloc(sizeof (EntryMV<T>));
        new(e) EntryMV<T>(nullptr, *obj, v);
        v->e = e;
        size_t idx = IDX_FN::hash(v->obj);
        array[idx].elem = e;
        xact.undoBufferHead = v;
    }
    
    FORCE_INLINE OperationReturnStatus add(Version<T>* v) override {
        size_t idx = IDX_FN::hash(v->obj);
        assert(idx >= 0 && idx < size);
        EntryMV<T>* emv = (EntryMV<T>*)v->e;
        EntryMV<T>* temp = nullptr;
        emv->backptrs[IndexMV<T>::idxId] = array + idx;
        if (array[idx].elem.compare_exchange_strong(temp, emv)) {
            return OP_SUCCESS;
        } else
            return DUPLICATE_KEY;
    }

    void removeEntry(T* obj, EntryMV<T>* emv) override {

    }

    void undo(Version<T>* v) override {

    }

    FORCE_INLINE void del(Version<T>* v) override {
        //        size_t idx = IDX_FN::hash(*obj);
        EntryMV<T>* emv = (EntryMV<T>*)v->e;
        AlignedEntry* ca = (AlignedEntry*) emv->backptrs[IndexMV<T>::idxId];
        auto idx = ca - array;
        assert(idx >= 0 && idx < size);
        ca->elem.compare_exchange_strong(emv, nullptr);
    }

    FORCE_INLINE OperationReturnStatus foreach(FuncType f, Transaction& xact) override {
        //Do nothing for now
        return OP_SUCCESS;
    }

    FORCE_INLINE T* get(const T* key, Transaction& xact) const override {
        return get(*key, xact);
    }

    FORCE_INLINE T* get(const T& key, Transaction& xact) const {
        size_t idx = IDX_FN::hash(key);
        assert(idx >= 0 && idx < size);
        EntryMV<T>* e = array[idx].elem.load();
        if (!e)
            return nullptr;
        Version<T>* v = e->getCorrectVersion(xact);
        if (!v)
            return nullptr;
        else {
            GetPred<T, IDX_FN>* pred = (GetPred<T, IDX_FN>*) malloc(sizeof (GetPred<T, IDX_FN>));
            new(pred) GetPred<T, IDX_FN>(key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            xact.predicateHead = pred;
            return &v->obj;
        }
    }

    T * getForUpdate(const T* key, OperationReturnStatus& s, Transaction & xact) override {
        return getForUpdate(*key, s, xact);
    }

    T * getForUpdate(const T& key, OperationReturnStatus& s, Transaction & xact) {
        size_t idx = IDX_FN::hash(key);
        assert(idx >= 0 && idx < size);
        EntryMV<T>* e = array[idx].elem;
        if (!e) {
            s = NO_KEY;
            return nullptr;
        }
        Version<T>* resV = e->versionHead;
        if (!resV->isVisible(&xact)) {
            if (resV->xactid > initCommitTS) {
                Transaction* otherXact = TStoPTR(resV->xactid);
                xact.failedBecauseOf = otherXact;
            }
            s = WW_VALUE;
            return nullptr;
        }
        Version<T>* newv = (Version<T>*) malloc(sizeof (Version<T>));
        new (newv) Version<T>(resV, xact);
        if (!e->versionHead.compare_exchange_strong(resV, newv)) {
            if (resV->xactid > initCommitTS) {
                Transaction* otherXact = TStoPTR(resV->xactid);
                xact.failedBecauseOf = otherXact;
            }
            s = WW_VALUE;
            free(newv);
            return nullptr;
        }
        GetPred<T, IDX_FN>* pred = (GetPred<T, IDX_FN>*) malloc(sizeof (GetPred<T, IDX_FN>));
        new(pred) GetPred<T, IDX_FN>(key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
        xact.predicateHead = pred;
        xact.undoBufferHead = newv;
        s = OP_SUCCESS;
        return &newv->obj;
        return &resV->obj;
    }

    void prepareSize(size_t arrayS, size_t poolS) override {
        //do nothing
    }
};
//
//template <typename T>
//struct TreeNode {
//    uint8_t height;
//    EntryMV<T>* emv;
//    TreeNode *parent, *left, *right;
//
//    TreeNode(EntryMV<T>* e, TreeNode* p) : height(1), emv(e), parent(p), left(nullptr), right(nullptr) {
//
//    }
//};

//template<typename T, typename IDX_FN2>
//struct _Tree {
//    typedef TreeNode<T> Node;
//    Node* root;
//    SpinLock lock;
//
//    _Tree(EntryMV<T>* e) {
//        root = malloc(sizeof (Node));
//        new (root) Node(e, nullptr);
//    }
//    FORCE_INLINE Node* getNext(Node* p) {
//        Node* cur = p->right;
//        if(cur) {
//            while(cur->left)
//                cur = cur->left;
//            return cur;
//        }
//    }
//    FORCE_INLINE int bfactor(Node *p) {
//        return height(p->right) - height(p->left);
//    }
//
//    FORCE_INLINE uint8_t height(Node *p) {
//        return p ? p->height : 0;
//    }
//
//    FORCE_INLINE void fixHeight(Node *p) {
//        uint8_t hl = height(p->left);
//        uint8_t hr = height(p->right);
//        p->height = (hl > hr ? hl : hr) + 1;
//
//    }
//
//    FORCE_INLINE Node* rotateRight(Node* p) {
//        Node* q = p->left;
//        p->left = q->right;
//        q->right = p;
//
//        q->parent = p->parent;
//        p->parent = q;
//        if (p->left)
//            p->left->parent = p;
//        fixHeight(p);
//        fixHeight(q);
//        return q;
//    }
//
//    FORCE_INLINE Node* rotateLeft(Node *p) {
//        Node* q = p->right;
//        p->right = q->left;
//        q->left = p;
//
//        q->parent = p->parent;
//        p->parent = q;
//        if (p->right)
//            p->right->parent = p;
//        fixHeight(p);
//        fixHeight(q);
//        return q;
//    }
//
//    FORCE_INLINE Node* balance(Node *p) {
//        fixHeight(p);
//        if (bfactor(p) == 2) {
//            if (bfactor(p->right) < 0)
//                p->right = rotateRight(p->right);
//            return rotateLeft(p);
//        }
//        if (bfactor(p) == -2) {
//            if (bfactor(p->left) > 0)
//                p->left = rotateLeft(p->left);
//            return rotateRight(p);
//        }
//        return p;
//    }
//
//    FORCE_INLINE insert_BST(T* obj, EntryMV<T>* emv) {
//        Node* cur = root;
//        while (cur != nullptr) {
//            T& curObj = cur ->emv->versionHead.load()->obj;
//            //assumes that slice columns as well as the ord column are same across all versions of Entry
//            if (IDX_FN2::cmp(*obj, curObj) < 0) {
//                if (cur->left == nullptr) {
//                    Node* newnode = (Node*) malloc(sizeof (Node));
//                    new(newnode) Node(emv, cur);
//                    cur->left = newnode;
//
//                    Node* par;
//                    while (true) {
//                        par = cur->parent;
//                        if (par) {
//                            if (par->right == cur) {
//                                cur = balance(cur);
//                                par->right = cur;
//                            } else {
//                                cur = balance(cur);
//                                par->left = cur;
//                            }
//                        } else {
//                            root = balance(root);
//                            return;
//                        }
//                        cur = par;
//                    }
//                }
//                cur = cur->left;
//            } else {
//                if (cur->right == nullptr) {
//                    Node* newnode = (Node*) malloc(sizeof (Node));
//                    new(newnode) Node(emv, cur);
//                    cur->right = newnode;
//
//                    Node* par;
//                    while (true) {
//                        par = cur->parent;
//                        if (par) {
//                            if (par->right == cur) {
//                                cur = balance(cur);
//                                par->right = cur;
//                            } else {
//                                cur = balance(cur);
//                                par->left = cur;
//                            }
//                        } else {
//                            root = balance(root);
//                            return;
//                        }
//                        cur = par;
//                    }
//                }
//                cur = cur->right;
//            }
//
//        }
//    }
//
//    FORCE_INLINE void removeBST(T* obj, EntryMV* emv) {
//        Node* cur = root;
//        while (cur != nullptr) {
//            if (cur->emv == emv) { // found it
//                Node* temp;
//                if (cur->left && cur->right) { // 2 children case 
//                    temp = cur;
//                    cur = cur->left;
//                    while (cur->right) {
//                        cur = cur->right;
//                    }
//                    temp-> emv = cur->emv;
//                }
//                // now cur has 0 or 1 child
//                temp = (cur->left ? cur->left : cur->right);
//                Node* par = cur->parent;
//                if (!par)
//                    root = temp;
//                else if (cur == par->right)
//                    par->right = temp;
//                else
//                    par->left = temp;
//
//                if (temp)
//                    temp->parent = par;
//                free(cur);
//
//                if (par) {
//                    cur = par;
//                    while (true) {
//                        par = cur->parent;
//                        if (par) {
//                            if (par->right == cur) {
//                                cur = balance(cur);
//                                par->right = cur;
//                            } else {
//                                cur = balance(cur);
//                                par->left = cur;
//                            }
//                        } else {
//                            root = balance(cur);
//                            return;
//                        }
//                        cur = par;
//                    }
//                }
//                return;
//            }
//            T& curObj = cur->emv->versionHead.load()->obj;
//            if (IDX_FN2::cmp(*obj, curObj) < 0)
//                cur = cur->left;
//            else
//                cur = cur->right;
//        }
//    }
//};
//
//template<typename T, typename IDX_FN1, typename IDX_FN2>
//struct CuckooTreeIndex : public IndexMV<T> {
//    typedef _Tree<T, IDX_FN2> Tree;
//    struct HE {
//        size_t operator()(const T* e) const {
//            size_t h = IDX_FN1::hash(*e);
//            return h;
//        }
//        bool operator()(const T* e1, const T* e2) const {
//            return IDX_FN1::cmp(*e1, *e2) == 0;
//        }
//    };
//    cuckoohash_map<T*, Tree*, HE, HE, std::allocator<std::pair<T*, Tree*>>> index;
//
//    CuckooTreeIndex(size_t s) : index(1 << 23) {
//    }
//
//    OperationReturnStatus add(T* key, EntryMV<T>* obj) override {
//        Tree* newtr = (Tree*) malloc(sizeof (Tree));
//        new Tree(obj);
//        T* keyc = key->copy();
//        auto updatefn = [newtr, keyc](Tree* &oldtr) {
//            free(newtr);
//            free(keyc);
//            oldtr->lock.lock();
//            oldtr->insert_BST(key, obj);
//            oldtr->lock.unlock();
//        };
//        return OP_SUCCESS;
//    }
//
//    void del(T* obj, EntryMV<T>* emv) override {
//        Tree* tr;
//        if (index.find(obj, tr)) {
//            tr->lock.lock();
//            tr->removeBST(obj, emv);
//            tr->lock.unlock();
//        }
//    }
//
//    OperationReturnStatus foreach(const std::function<TransactionReturnStatus()(T*)>& f, Transaction& xact) override {
//        return OP_SUCCESS;
//    }
//
//    void prepareSize(size_t arrayS, size_t poolS) override {
//    }
//};
//
//template <typename T, typename IDX_FN1, typename IDX_FN2>
//struct CuckooMinTreeIndex : public CuckooTreeIndex<T, IDX_FN1, IDX_FN2> {
//    typedef CuckooTreeIndex<T, IDX_FN1, IDX_FN2> Super;
//    typedef _Tree<T, IDX_FN2> Tree;
//    typedef TreeNode<T> Node;
//    CuckooMinTreeIndex(size_t s ): Super(s){
//        
//    }
//    T* get(const T* key, Transaction& xact) const override {
//        Tree* tree;
//        if (index.find(key, tree)) {
//            tree->lock.lock();
//            Node* cur = tree->root;
//            
//            tree->lock.unlock();
//        } else
//            return NO_KEY;
//
//    }
//};

template <typename T, typename IDX_FN2, bool is_max>
struct Heap {
    EntryMV<T>** array;
    uint arraySize;
    uint size;
    typedef EntryMV<T>* HeapElemType;

    Heap() {
        arraySize = DEFAULT_HEAP_SIZE;
        array = new EntryMV<T>*[arraySize];
        size = 0;
    }
    //
    //        void print() {
    //            for (uint i = 1; i <= size; ++i) {
    //                if ((i & (i - 1)) == 0)
    //                    std::cout << std::endl;
    //                std::cout << array[i]->getString(4) << "\t";
    //            }
    //            std::cout << std::endl;
    //        }

    FORCE_INLINE EntryMV<T>* get() const {
        return array[1];
    }

    void checkHeap(int idx) {
        for (uint i = 1; i <= size; ++i) {
            uint l = 2 * i;
            uint r = l + 1;
            EntryMV<T>* x = array[i];

            if (is_max) {
                if (l <= size) {
                    assert(IDX_FN2::cmp(x->key, array[l]->key) == 1);
                    if (r <= size)
                        assert(IDX_FN2::cmp(x->key, array[r]->key) == 1);
                }
            } else {
                if (l <= size) {
                    assert(IDX_FN2::cmp(x->key, array[l]->key) == -1);
                    if (r <= size)
                        assert(IDX_FN2::cmp(x->key, array[r]->key) == -1);
                }
            }
            //            assert(x->backPtrs[idx] == n);
        }
    }

    FORCE_INLINE void double_() {
        uint newsize = arraySize << 1;
        EntryMV<T>** temp = new EntryMV<T>*[newsize];
        mempcpy(temp, array, arraySize * sizeof (EntryMV<T>*));
        arraySize = newsize;
        delete[] array;
        array = temp;
        assert(array);
    }

    FORCE_INLINE void percolateDown(uint holeInput) {
        uint hole = holeInput;
        uint child = hole << 1;
        EntryMV<T>* tmp = array[hole];
        while (child <= size) {
            if (child != size && IDX_FN2::cmp(array[child + 1]->key, array[child]->key) == (is_max ? 1 : -1))
                child++;
            if (IDX_FN2::cmp(array[child]->key, tmp->key) == (is_max ? 1 : -1))
                array[hole] = array[child];
            else {
                array[hole] = tmp;
                return;
            }
            hole = child;
            child = hole << 1;
        }
        array[hole] = tmp;
    }

    FORCE_INLINE void add(EntryMV<T>* e) {
        if (size == arraySize - 1) double_();
        size++;
        uint hole = size;
        uint h = size >> 1;
        while (hole > 1 && IDX_FN2::cmp(e->key, array[h]->key) == (is_max ? 1 : -1)) {
            array[hole] = array[h];
            hole = h;
            h = hole >> 1;
        }
        array[hole] = e;
    }

    //SBJ: Should only be called for a newer value that would be closer to root
    //In a max heap, the newer value must be greater
    //In a min heap, the newer value must be smaller
    //TOFIX: Not considering equal values

    FORCE_INLINE void update(EntryMV<T>* old, EntryMV<T>* nw) {
        assert(IDX_FN2::cmp(nw->key, old->key) == (is_max ? 1 : -1));
        uint p = 1;
        if (array[p] != old) {
            p++;
            while (p <= size) {
                if (array[p] == old)
                    break;
                p++;
            }
            //            if (p == size + 1)
            //                throw std::logic_error("Element not found in heap");
        }
        uint hole = p;
        uint h = p >> 1;
        while (hole > 1 && IDX_FN2::cmp(nw->key, array[h]->key) == (is_max ? 1 : -1)) {
            array[hole] = array[h];
            hole = h;
            h = hole >> 1;
        }
        array[hole] = nw;

    }

    FORCE_INLINE void remove(EntryMV<T>* e) {
        uint p = 1;
        if (array[p] != e) {
            p++;
            while (p <= size) {
                if (array[p] == e)
                    break;
                p++;
            }
            //            if (p == size + 1)
            //                throw std::logic_error("Element not found in heap");
        }

        while (p != 1) {
            uint h = p >> 1;
            array[p] = array[h];
            p = h;
        }
        array[p] = array[size];
        array[size] = nullptr;
        size--;

        if (p < size)
            percolateDown(p);
    }
};

template <typename T, typename IDX_FN2>
struct MedianHeap {
    Heap<T, IDX_FN2, true> left;
    Heap<T, IDX_FN2, false> right;
    //invariant : l.size = r.size OR l.size = r.size + 1

    void add(EntryMV<T>* obj) {
        if (left.size == 0) {
            left.add(obj);
            return;
        }
        assert(left.size > 0);
        if (IDX_FN2::cmp(obj->key, left.array[1]->key) == 1) { //obj greater than median
            if (right.size == left.size) { // right side will be unbalanced on adding
                if (IDX_FN2::cmp(obj->key, right.array[1]->key) == 1) { //obj greater than min of right
                    EntryMV<T>* obj2 = right.array[1]; //add obj to right. move min of right to left
                    right.array[1] = obj;
                    right.percolateDown(1);
                    left.add(obj2);
                } else { //object is new median 
                    left.add(obj);
                }
            } else {
                right.add(obj);
            }

        } else { //obj same or less as median
            if (left.size > right.size) { //left will be unbalanced on adding
                EntryMV<T>* obj2 = left.array[1];
                left.array[1] = obj;
                left.percolateDown(1);
                right.add(obj2);
            } else {
                left.add(obj);
            }
        }
    }

    //SBJ: May not find the right element if it is median and there are duplicates of it spread across left and right

    void remove(EntryMV<T> *obj) {
        if (IDX_FN2::cmp(obj->key, left.array[1]->key) == 1) {
            //obj in right
            if (left.size > right.size) {
                EntryMV<T> * obj2 = left.array[1];
                left.remove(obj2);
                right.update(obj, obj2); //we are decreasing value in min-heap, safe to call update
            } else {
                right.remove(obj);
            }
        } else {
            //obj in left
            if (left.size == right.size) {
                EntryMV<T>* obj2 = right.array[1];
                right.remove(obj2);
                left.update(obj, obj2); //increasing value in max-heap
            } else {
                left.remove(obj);
            }
        }
    }

    FORCE_INLINE EntryMV<T>* get() const {
        return left.array[1];
    }

    void check(int idx) {
        left.checkHeap(idx);
        right.checkHeap(idx);
        EntryMV<T>* r = right.array[1];
        EntryMV<T>* l = left.array[1];
        assert(left.size == 0 || right.size == 0 || IDX_FN2::cmp(l->key, r->key) == -1); //can be 0 too, but we want to know if there is such a case
        assert(left.size == right.size || left.size == right.size + 1);
    }
};

template<typename T, typename IDX_FN1, typename IDX_FN2, typename ST_IDX>
struct VersionedAggregator : public IndexMV<T> {
    typedef HE_<T, IDX_FN1> HE;
    typedef ST_IDX typeST;
    typedef EntryMV<T>* EntryType;

    struct VersionedContainer {
        EntryMV<T>* aggE;
        Transaction* xact;
        VersionedContainer* next;

        VersionedContainer(EntryMV<T>*e, Transaction* xact, VersionedContainer* n) : aggE(e), xact(xact), next(n) {
        }
    };

    struct VersionedSlice {
        VersionedContainer* head;
        SpinLock lock;
        ST_IDX sliceST;

        VersionedSlice() : head(nullptr), lock(), sliceST() {

        }

        FORCE_INLINE OperationReturnStatus add(Version<T>* newv) {
            EntryMV<T>* e = (EntryMV<T>*)newv->e;
            lock.lock();
            sliceST.add(e);
            EntryMV<T>* aggE = sliceST.get();

            if (head && head->xact != TStoPTR(newv->xactid) && head->xact->commitTS == initCommitTS) {
                lock.unlock();
                return WW_VALUE;
            }

            /* This is not correct for median index. For example,  if there was 
                        ab(c) de
             *          ab(c) xde
             *          aby(c) xde           
             and now if we undo x, we should have ab(y) cde. However, this would still return c
             * Each modification should create a version in median index
             */
            if (!head || head->aggE != aggE) {
                if (!head || head->xact != TStoPTR(newv->xactid)) {
                    VersionedContainer* vc = (VersionedContainer*) malloc(sizeof (VersionedContainer));
                    new(vc) VersionedContainer(aggE, TStoPTR(newv->xactid), head);
                    head = vc;
                } else {
                    head->aggE = aggE;
                }
            }
            lock.unlock();
            return OP_SUCCESS;
        }

        FORCE_INLINE OperationReturnStatus del(Version<T>* v) {
            EntryMV<T>* e = (EntryMV<T>*) v->e;
            lock.lock();
            sliceST.remove(e);
            EntryMV<T>* aggE = sliceST.get();

            if (head->xact != TStoPTR(v->xactid) && head->xact->commitTS == initCommitTS) {
                lock.unlock();
                return WW_VALUE;
            }
            if (head->aggE != aggE) {
                if (head->xact != TStoPTR(v->xactid)) {
                    VersionedContainer* vc = (VersionedContainer*) malloc(sizeof (VersionedContainer));
                    new(vc) VersionedContainer(aggE, TStoPTR(v->xactid), head);
                    head = vc;
                } else {
                    head->aggE = aggE;
                }
            }
            lock.unlock();
            return OP_SUCCESS;
        }

        FORCE_INLINE void undo(Version<T>* v) {
            EntryMV<T>*e = (EntryMV<T>*)v->e;

            lock.lock();
            if (v->obj.isInvalid) { //deleted version, to undo it, need to re-insert entry into index
                sliceST.add(e);
            } else if (v->oldV == nullptr) { //only version, inserted. Need to remove to undo
                sliceST.remove(e);
            } else { //assuming that normal updates are only to non-key fields, no impact here
                lock.unlock();
                return;
            }
//            EntryMV<T>* e_new = sliceST.get(); //to be removed in final version
            if (head->xact == TStoPTR(v->xactid)) {
                head = head->next;
                flag = true;
            }
//            assert(e_new == (head ? head->aggE : nullptr));
            lock.unlock();
        }

        FORCE_INLINE void removeEntry(EntryMV<T>* e) {
            //Do nothing?
        }

        FORCE_INLINE EntryMV<T>* get(Transaction & xact) {
            VersionedContainer* cur = head;
            while (cur && cur->xact->commitTS > xact.startTS) {
                cur = cur->next;
            }
            return cur ? cur->aggE : nullptr;
        }
    };

    cuckoohash_map<T*, VersionedSlice*, HE, HE, std::allocator<std::pair<T*, VersionedSlice*>>> index;

    VersionedAggregator(size_t s) : index(1 << 23) {
    }

    FORCE_INLINE OperationReturnStatus add(Version<T>* newv) override {
        VersionedSlice * vsnew = (VersionedSlice*) malloc(sizeof (VersionedSlice));
        new (vsnew) VersionedSlice();

        VersionedContainer* vc = (VersionedContainer*) malloc(sizeof (VersionedContainer));
        EntryMV<T>* e = (EntryMV<T>*)newv->e;
        new(vc) VersionedContainer(e, TStoPTR(newv->xactid), nullptr);
        e->backptrs[IndexMV<T>::idxId] = vsnew;
        vsnew->head = vc;
        vsnew->sliceST.add(e);
        T* keyc = newv->obj.copy();
        index.upsert(keyc, [&](VersionedSlice * vsold) {
            free(keyc);
            free(vsnew);
            free(vc);
            e->backptrs[IndexMV<T>::idxId] = vsold;
            vsold->add(newv);
        }, vsnew);
        return OP_SUCCESS;
    }

    FORCE_INLINE void del(Version<T>* newv) override {
        EntryMV<T>* emv = (EntryMV<T>*) newv->e;
        VersionedSlice* vs = (VersionedSlice*) emv->backptrs[IndexMV<T>::idxId];
        vs->del(newv);
    }

    FORCE_INLINE void removeEntry(T* obj, EntryMV<T>* emv) override {
        VersionedSlice* vs = (VersionedSlice*) emv->backptrs[IndexMV<T>::idxId];
        vs->removeEntry(emv);
    }

    FORCE_INLINE void undo(Version<T>* v) override {
        EntryMV<T>* emv = (EntryMV<T>*) v->e;
        VersionedSlice* vs = (VersionedSlice*) emv->backptrs[IndexMV<T>::idxId];
        vs->undo(v);
    }

    OperationReturnStatus foreach(FuncType f, Transaction& xact) override {
        return OP_SUCCESS;
    }

    FORCE_INLINE T* get(const T* key, Transaction& xact) const override {
        VersionedSlice * vs;
        if (index.find(key, vs)) {
            EntryMV<T>* e = vs->get(xact);
            Version<T>* v = e->getCorrectVersion(xact);
            if (!v)
                return nullptr;
            return &v->obj;
        } else {
            return nullptr;
        }
    }

    FORCE_INLINE T* getForUpdate(const T& key, OperationReturnStatus& st, Transaction& xact) {
        return getForUpdate(&key, st, xact);
    }

    FORCE_INLINE T* getForUpdate(const T* key, OperationReturnStatus& st, Transaction& xact) override {
        VersionedSlice* result;
        if (index.find(key, result)) {
            EntryMV<T>* resE = result->get(xact);
            Version<T>* resV = resE->versionHead;
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

            if (!resE->versionHead.compare_exchange_strong(resV, newv)) {
                if (resV->xactid > initCommitTS) {
                    Transaction* otherXact = TStoPTR(resV->xactid);
                    xact.failedBecauseOf = otherXact;
                }
                st = WW_VALUE;
                free(newv);
                return nullptr;
            }
            xact.undoBufferHead = newv;
            st = OP_SUCCESS;
            return &newv->obj;
        } else {
            st = NO_KEY;
            return nullptr;
        }
    }

    void prepareSize(size_t arrayS, size_t poolS) override {
    }

    virtual ~VersionedAggregator() {
    }


};


template<typename T, typename IDX_FN1, typename IDX_FN2>
struct MinHeapIndex : public VersionedAggregator<T, IDX_FN1, IDX_FN2, Heap<T, IDX_FN2, false >>
{
    typedef VersionedAggregator<T, IDX_FN1, IDX_FN2, Heap<T, IDX_FN2, false >> Super;

    MinHeapIndex(size_t s) : Super(s) {

    }

    T * get(const T& key, Transaction & xact) const {
        return get(&key, xact);
    }

    T * get(const T* key, Transaction & xact) const override {
        T* ret = Super::get(key, xact);
        if (ret) {
            //            assert(ret->_4.data_);
            MinSlicePred<T, IDX_FN1, IDX_FN2>* pred = (MinSlicePred<T, IDX_FN1, IDX_FN2>*) malloc(sizeof (MinSlicePred<T, IDX_FN1, IDX_FN2>));
            new(pred) MinSlicePred<T, IDX_FN1, IDX_FN2>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            pred->key = *ret;
            xact.predicateHead = pred;

        }
        return ret;
    }

    T * getForUpdate(const T& key, OperationReturnStatus& s, Transaction & xact) {
        T* ret = Super::getForUpdate(key, s, xact);
        if (ret) {
            //            assert(ret->_4.data_);
            MinSlicePred<T, IDX_FN1, IDX_FN2>* pred = (MinSlicePred<T, IDX_FN1, IDX_FN2>*) malloc(sizeof (MinSlicePred<T, IDX_FN1, IDX_FN2>));
            new(pred) MinSlicePred<T, IDX_FN1, IDX_FN2>(key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            pred->key = *ret;
            xact.predicateHead = pred;
        }
        return ret;
    }

};
template<typename T, typename IDX_FN1, typename IDX_FN2>
struct MaxHeapIndex : public VersionedAggregator<T, IDX_FN1, IDX_FN2, Heap<T, IDX_FN2, true >>
{
    typedef VersionedAggregator<T, IDX_FN1, IDX_FN2, Heap<T, IDX_FN2, true >> Super;

    MaxHeapIndex(size_t s) : Super(s) {

    }

    T * get(const T& key, Transaction & xact) const {
        return get(&key, xact);
    }

    T * get(const T* key, Transaction & xact) const override {
        T* ret = Super::get(key, xact);
        if (ret) {
            MaxSlicePred<T, IDX_FN1, IDX_FN2>* pred = (MaxSlicePred<T, IDX_FN1, IDX_FN2>*) malloc(sizeof (MaxSlicePred<T, IDX_FN1, IDX_FN2>));
            new(pred) MaxSlicePred<T, IDX_FN1, IDX_FN2>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            pred->key = *ret;
            xact.predicateHead = pred;

        }
        return ret;
    }

    T * getForUpdate(const T& key, OperationReturnStatus& s, Transaction & xact) {
        T* ret = Super::getForUpdate(key, s, xact);
        if (ret) {
            MaxSlicePred<T, IDX_FN1, IDX_FN2>* pred = (MaxSlicePred<T, IDX_FN1, IDX_FN2>*) malloc(sizeof (MaxSlicePred<T, IDX_FN1, IDX_FN2>));
            new(pred) MaxSlicePred<T, IDX_FN1, IDX_FN2>(key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            pred->key = *ret;
            xact.predicateHead = pred;
        }
        return ret;
    }

};
template<typename T, typename IDX_FN1, typename IDX_FN2>
struct MedHeapIndex : public VersionedAggregator<T, IDX_FN1, IDX_FN2, MedianHeap<T, IDX_FN2>>
{
    typedef VersionedAggregator<T, IDX_FN1, IDX_FN2, MedianHeap<T, IDX_FN2>> Super;

    MedHeapIndex(size_t s) : Super(s) {

    }

    T * get(const T& key, Transaction & xact) const {
        return get(&key, xact);
    }

    T * get(const T* key, Transaction & xact) const override {
        T* ret = Super::get(key, xact);
        if (ret) {
            SlicePred<T, IDX_FN1>* pred = (SlicePred<T, IDX_FN1>*) malloc(sizeof (SlicePred<T, IDX_FN1>));
            new(pred) SlicePred<T, IDX_FN1>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            xact.predicateHead = pred;

        }
        return ret;
    }

    T * getForUpdate(const T& key, OperationReturnStatus& s, Transaction & xact) {
        T* ret = Super::getForUpdate(key, s, xact);
        if (ret) {
            SlicePred<T, IDX_FN1>* pred = (SlicePred<T, IDX_FN1>*) malloc(sizeof (SlicePred<T, IDX_FN1>));
            new(pred) SlicePred<T, IDX_FN1>(key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            xact.predicateHead = pred;
        }
        return ret;
    }

};

template<typename T, typename IDX_FN>
struct ConcurrentCuckooSecondaryIndex : public IndexMV<T> {
    typedef HE_<T, IDX_FN> HE;

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

    FORCE_INLINE OperationReturnStatus add(Version<T>* newv) override {
        Container *newc = (Container *) malloc(sizeof (Container));
        EntryMV<T>* obj = (EntryMV<T>*)newv->e;
        new(newc) Container(obj);
        obj->backptrs[IndexMV<T>::idxId] = newc;
        Container *sentinel = (Container*) malloc(sizeof (Container));
        new(sentinel) Container(newc);
        T* keyc = newv->obj.copy();
        auto updatefn = [newc, sentinel, keyc](Container* &c) {
            free(sentinel);
            free(keyc);
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

    FORCE_INLINE void removeEntry(T* obj, EntryMV<T>* emv) override {
        Container *cur = (Container*) emv->backptrs[IndexMV<T>::idxId];
        Container* nxt = cur->next;
        while (!cur->next.compare_exchange_weak(nxt, mark(nxt)));
    }

    void undo(Version<T>* v) override {
        //Do nothing
    }

    FORCE_INLINE void del(Version<T>* v) override {
        //Do nothing for secondary hash index
    }

    FORCE_INLINE OperationReturnStatus slice(const T& key, FuncType f, Transaction& xact) {
        return slice(&key, f, xact);
    }

    FORCE_INLINE OperationReturnStatus slice(const T* key, FuncType f, Transaction& xact) {
        Container *sentinel;
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
                if (!cur)
                    break;
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
            SlicePred<T, IDX_FN>* pred = (SlicePred<T, IDX_FN>*) malloc(sizeof (SlicePred<T, IDX_FN>));
            new(pred) SlicePred<T, IDX_FN>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            xact.predicateHead = pred;
            return OP_SUCCESS;
        } else {
            return NO_KEY;
        }
    }

    FORCE_INLINE OperationReturnStatus sliceNoUpdate(const T& key, FuncType f, Transaction& xact) {
        return sliceNoUpdate(&key, f, xact);
    }

    FORCE_INLINE OperationReturnStatus sliceNoUpdate(const T* key, FuncType f, Transaction& xact) {
        Container *sentinel;

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
            SlicePred<T, IDX_FN>* pred = (SlicePred<T, IDX_FN>*) malloc(sizeof (SlicePred<T, IDX_FN>));
            new(pred) SlicePred<T, IDX_FN>(*key, xact.predicateHead, IndexMV<T>::mmapmv, col_type(-1));
            xact.predicateHead = pred;
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
    virtual void removeEntry(void* o, void* emv) = 0;
    virtual void undo(VBase* v) = 0;
};

template<typename T, typename...INDEXES>
class MultiHashMapMV : MBase {
private:

    bool *modified;
public:

    IndexMV<T>** index;

    MultiHashMapMV() { // by defintion index 0 is always unique
        if (sizeof...(INDEXES) > MAX_IDXES_PER_TBL) {
            cerr << "The maximum indexes per table is configured to be " << MAX_IDXES_PER_TBL << " which is less than the required indexes" << endl;
        }
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
        if (sizeof...(INDEXES) > MAX_IDXES_PER_TBL) {
            cerr << "The maximum indexes per table is configured to be " << MAX_IDXES_PER_TBL << " which is less than the required indexes" << endl;
        }
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
            new(newE) EntryMV<T>(this, *elem, newV);
            newV->e = newE;
            auto primarySt = index[0] -> add(newV);
            if (primarySt == OP_SUCCESS) {
                for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->add(newV);
                return OP_SUCCESS;
            } else {
                free(newE);
                free(newV);
                return OP_SUCCESS;
                return DUPLICATE_KEY;
            }
            xact.undoBufferHead = newV;
        } else {
            return DUPLICATE_KEY;

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
        new(newE) EntryMV<T>(this, *elem, newV);
        newV->e = newE;
        //        newV->obj.e = newE;
        auto primarySt = index[0] -> add(newV);
        if (primarySt == OP_SUCCESS) {
            xact.undoBufferHead = newV;
            for (size_t i = 1; i<sizeof...(INDEXES); ++i) index[i]->add(newV);
            return OP_SUCCESS;
        } else {
            free(newE);
            free(newV);
            return DUPLICATE_KEY;
        }
    }

    FORCE_INLINE void removeEntry(void* o, void* e) override {
        T* obj = (T*) o;
        EntryMV<T>* emv = (EntryMV<T>*) e;
        for (uint i = 0; i < sizeof...(INDEXES); ++i)
            index[i]->removeEntry(obj, emv);
    }

    FORCE_INLINE void undo(VBase *v) override {
        for (uint i = 0; i < sizeof...(INDEXES); ++i)
            index[i]->undo((Version<T>*)v);
    }

    FORCE_INLINE void del(T* elem) {
        elem->isInvalid = true;
        Version<T>* v = (Version<T>*)VBase::getVersionFromT((char*) elem);
        for (uint i = 0; i < sizeof...(INDEXES); ++i)
            index[i]->del(v);
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
