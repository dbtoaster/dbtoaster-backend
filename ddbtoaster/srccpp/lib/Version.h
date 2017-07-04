
#ifndef VERSION_H
#define VERSION_H

#include <atomic>
#include "types.h"
#include "Transaction.h"
#include "mmap/cmmap.hpp"
template <typename T>
struct alignas(64)EntryMV;

struct alignas(64) VBase {
    timestamp xactid;
    std::atomic<VBase*> oldV;
    VBase* nextInUndoBuffer;
    EBase* e; 
    col_type cols;

    VBase(Transaction& x) : xactid(PTRtoTS(&x)), oldV(nullptr), nextInUndoBuffer(x.undoBufferHead), cols(-1) {
       //Should not add to x.undoBuffer now. This version can still be deleted
    }

    static FORCE_INLINE VBase* getVersionFromT(char* entry) {
        return (VBase *) ((size_t)entry & (~63));
    }
    virtual VBase* getVersionAfter(timestamp oldest) = 0;
    virtual void removeFromVersionChain() = 0;
};

template <typename T>
 struct alignas(64) Version : public VBase {
    T obj;

    Version(Version* that, Transaction& x) : VBase(x), obj(that->obj) {
        e = that->e;
        oldV = that;
    }

    Version(const T&o, Transaction& x) : VBase(x), obj(o) {
    }
    //    template <typename... Args>
    //    Version(bool ignore, const Args&... args): obj(args...), entry(nullptr), xactid(mask), oldV(nullptr){
    //    }

    VBase* getVersionAfter(timestamp oldest) override {
        EntryMV<T>* e = (EntryMV<T>*)this->e;
        Version<T>* dv = e->versionHead.load(); //dv != nullptr as there will always be one version
        if (dv == nullptr) //Can happen if GC removes version but not the EntryMV
            return nullptr;
        VBase* dvOld = dv->oldV;
        VBase *old = nullptr;
        VBase *oldOld = dv;
        while (isMarked(dvOld) || dv->xactid > oldest) {
            if (!isMarked(dvOld)) {
                if (oldOld != dv) {
                    if (old == nullptr) {
                        Version<T> * oldOldKV = (Version<T>*) oldOld;
                        e->versionHead.compare_exchange_strong(oldOldKV, dv); //dont care abt result
                    } else
                        old->oldV.compare_exchange_strong(oldOld, dv); //dont care abt result
                }
                old = dv;
                dv = (Version<T>*)dvOld;
                assert(!dv || dv->e == this->e);
                oldOld = dvOld;
            } else {
                dv = (Version<T>*)unmark(dvOld);
            }
            if (!dv)
                break;
            dvOld = dv->oldV.load();
        }
        if (oldOld != dv) {
            if (old == nullptr) {
                Version<T> * oldOldKV = (Version<T> *) oldOld;
                e->versionHead.compare_exchange_strong(oldOldKV, (Version<T> *) dv); //dont care abt result
            } else
                old->oldV.compare_exchange_strong(oldOld, dv); //dont care abt result
        }
        if (!dv)
            return nullptr;
        if (old == nullptr) {  //latest version
            if (dv->obj.isInvalid)
                e->tbl->removeEntry(&dv->obj, e);
            //Not really safe to delete dv here. But assuming that it takes a while after this return for dv to be deleted, it is safe
            return dv->oldV;
        } else if (old->xactid >= initCommitTS) //dv is the first committed version, cannot be deleted
            return dv->oldV;
        else
            return dv;
    }

    void removeFromVersionChain() override {
        EntryMV<T>* eptr = (EntryMV<T>*)e;
        assert(eptr->versionHead == this);
        eptr->tbl->undo(this);
        if (oldV == nullptr) { // Only version, created by INSERT
            eptr->tbl->removeEntry(&obj, eptr);
            //            free(eptr);
            //            free(this);
        } else {
            Version<T>* dv = this;
            auto dvOld = (Version<T>*)oldV.load();
            if (!eptr->versionHead.compare_exchange_strong(dv, dvOld)) {
                cerr << "DV being removed is not the first version" << endl;
            }
        }
    }

    FORCE_INLINE bool isVisible(Transaction* xact) {
        timestamp ts = xactid;
        if (isTempTS(ts)) {
            Transaction* t = TStoPTR(ts);
            if (t == xact || t->commitTS < xact->startTS) //What if commitTS == startTS ?
                return true;
        } else { //transaction that wrote DV is definitely committed   dv->xactId == t->commitTS
            if (ts < xact->startTS)
                return true;
        }
        return false;
    }

};

struct alignas(64) EBase {
    MBase* tbl;
    EBase(MBase* tbl) : tbl(tbl) {      
    }
};
template <typename T>
 struct alignas(64) EntryMV : public EBase{
    const T key;  //to avoid looking up versionHead to do key comparison for ordering. Assumes indexed columns same across all versions
    std::atomic<Version<T>*> versionHead;
    std::atomic<EntryMV<T>*> nxt;
    void* backptrs[MAX_IDXES_PER_TBL];
    EntryMV(MBase* tbl, T& k, Version<T>* v) : EBase(tbl), key(k), versionHead(v), nxt(nullptr) {
    }

    //Returns the first version with cts > oldest AND not the only first committed version
    Version<T>* getCorrectVersion(Transaction& xact) {
        Version<T>* dv = (Version<T>*)versionHead.load(); //dv != nullptr as there will always be one version
        if (dv == nullptr) //Can happen if GC removes version but not the EntryMV
            return nullptr;
        VBase* dvOld = dv->oldV;
        VBase *old = nullptr;
        VBase *oldOld = dv;
        while (isMarked(dvOld) || !dv->isVisible(&xact)) {
            if (!isMarked(dvOld)) {
                if (oldOld != dv) {
                    if (old == nullptr) {
                        Version<T> * oldOldKV = (Version<T>*) oldOld;
                        versionHead.compare_exchange_strong(oldOldKV, dv); //dont care abt result
                    } else
                        old->oldV.compare_exchange_strong(oldOld, dv); //dont care abt result
                }
                old = dv;
                dv = (Version<T>*)dvOld;
                assert(!dv || dv->e == this);
                oldOld = dvOld;
            } else {
                dv = (Version<T>*) unmark(dvOld);
            }
            if (!dv)
                break;
            dvOld = dv->oldV.load();
        }
        if (oldOld != dv) {
            if (old == nullptr) {
                Version<T> * oldOldKV = (Version<T> *) oldOld;
                versionHead.compare_exchange_strong(oldOldKV, (Version<T> *) dv); //dont care abt result
            } else
                old->oldV.compare_exchange_strong(oldOld, dv); //dont care abt result
        }
        return dv;
    }

};
#endif /* VERSION_H */

