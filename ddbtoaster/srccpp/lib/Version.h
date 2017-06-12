
#ifndef VERSION_H
#define VERSION_H

#include <atomic>
#include "types.h"
#include "Transaction.h"
template <typename T>
struct EntryMV;

struct VBase {
    timestamp xactid;
    std::atomic<VBase*> oldV;
    VBase* nextInUndoBuffer;
    col_type cols;

    VBase(Transaction& x) : xactid(PTRtoTS(&x)), oldV(nullptr), nextInUndoBuffer(nullptr), cols(-1) {
    }
    virtual void removeFromVersionChain() = 0;
};

template <typename T>
struct Version : public VBase {
    T obj;

    Version(const Version& that, Transaction& x) : VBase(x), obj(that.obj) {
    }

    Version(const T&o, Transaction& x) : VBase(x), obj(o) {
    }
    //    template <typename... Args>
    //    Version(bool ignore, const Args&... args): obj(args...), entry(nullptr), xactid(mask), oldV(nullptr){
    //    }

    void removeFromVersionChain() override {
        EntryMV<T>* e = obj.e;
        assert(e->versionHead == this);
        Version<T>* dv = this;
        auto dvOld = (Version<T>*)oldV.load();
        if (!e->versionHead.compare_exchange_strong(dv, dvOld)) {

            cerr << "DV being removed is not the first version" << endl;
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
    void* tbl;
    std::atomic<Version<T>*> versionHead;
    std::atomic<EntryMV<T>*> nxt;

    EntryMV() : versionHead(nullptr), nxt(nullptr) {
    }

    EntryMV(Version<T>* v) : versionHead(v), nxt(nullptr) {
    }

    Version<T>* getCorrectVersion(Transaction& xact) {
        Version<T>* dv = (Version<T>*)versionHead.load(); //dv != nullptr as there will always be one version
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

