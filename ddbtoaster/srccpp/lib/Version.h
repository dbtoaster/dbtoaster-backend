
#ifndef VERSION_H
#define VERSION_H

#include <atomic>
#include "types.h"
#include "Transaction.h"
#include "mmap/cmmap.hpp"
template <typename T>
struct EntryMV;

struct VBase {
    timestamp xactid;
    std::atomic<VBase*> oldV;
    VBase* nextInUndoBuffer;
    EntryMV<void>* e; //SBJ: Hack to avoid Entry base class
    col_type cols;

    VBase(Transaction& x) : xactid(PTRtoTS(&x)), oldV(nullptr), nextInUndoBuffer(x.undoBufferHead), cols(-1) {
       //Should not add to x.undoBuffer now. This version can still be deleted
    }

    static FORCE_INLINE VBase* getVersionFromT(char* entry) {
        return (VBase *) (entry - sizeof (VBase));
    }

    virtual void removeFromVersionChain() = 0;
};

template <typename T>
struct Version : public VBase {
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

    void removeFromVersionChain() override {
        EntryMV<T>* eptr = (EntryMV<T>*)e;
        assert(eptr->versionHead == this);
        if (oldV == nullptr) { // Only version, created by INSERT
            eptr->tbl->del(&obj, eptr);
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

template <typename T>
struct EntryMV {
    MBase* tbl;
    std::atomic<Version<T>*> versionHead;
    std::atomic<EntryMV<T>*> nxt;

    EntryMV(MBase* tbl, Version<T>* v) : tbl(tbl), versionHead(v), nxt(nullptr) {
    }

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
                oldOld = dvOld;
                dv = (Version<T>*)dvOld;
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

