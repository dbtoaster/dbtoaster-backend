
#ifndef PREDICATE_H
#define PREDICATE_H
#include <iostream>
#include <types.h>
#include "Transaction.h"
#include "Version.h"
struct PRED {
    MBase* tbl;
    PRED* next;

    PRED(MBase* mmapPtr, PRED* n) : tbl(mmapPtr), next(n) {
    }
    virtual bool matchesAny(Transaction *t) = 0;

    virtual ~PRED() {
    }
};

template<typename T>
struct ForEachPred : public PRED {
#ifdef ATTRIB_LEVEL
    col_type colsToBeChecked;

    ForEachPred(PRED* n, MBase* mmapPtr, const col_type& cols) : PRED(mmapPtr, n), colsToBeChecked(cols) {
    }
#else

    ForEachPred(PRED* n, MBase* mmapPtr, const col_type& cols) : PRED(mmapPtr, n) {
    }
#endif

    virtual bool matchesAny(Transaction *t) {

        VBase* dv = t->undoBufferHead;
        while (dv != nullptr) {
            if (matches(dv))
                return true;
            dv = dv->nextInUndoBuffer;
        }

        return false;
    }

    FORCE_INLINE bool matches(VBase* V) {
        Version<T>* dv = (Version<T>*)V;
#ifdef ATTRIB_LEVEL
        if ((colsToBeChecked & dv->cols).none())
            return false;
#endif
        return dv->e->tbl == tbl;
    }

    virtual ~ForEachPred() {
    }
};

template<typename T, typename IDX_FN>
struct GetPred : public PRED {
    const T key;
#ifdef ATTRIB_LEVEL
    col_type colsToBeChecked;

    GetPred(const T& k, PRED* n, MBase* mmapPtr, const col_type& cols) : PRED(mmapPtr, n), key(k), colsToBeChecked(cols) {
    }
#else

    GetPred(const T& k, PRED* n, MBase* mmapPtr, const col_type& cols) : PRED(mmapPtr, n), key(k) {
    }
#endif

    virtual bool matchesAny(Transaction *t) {

        VBase* dv = t->undoBufferHead;
        while (dv != nullptr) {
            if (matches(dv))
                return true;
            dv = dv->nextInUndoBuffer;
        }

        return false;
    }

    FORCE_INLINE bool matches(VBase* V) {
        EntryMV<T>* e = (EntryMV<T>*)V->e; //dv->obj.e;
        if (e->tbl != tbl)
            return false;
        Version<T>*dv = (Version<T>*)V;
        
#ifdef ATTRIB_LEVEL
        if ((colsToBeChecked & dv->cols).none())
            return false;
#endif
        const T& k = dv->obj;
        return IDX_FN::cmp(k, key) == 0;
    }

    virtual ~GetPred() {
    }
};

template <typename T, typename IDX_FN>
struct SlicePred : public PRED {
    const T key;

#ifdef ATTRIB_LEVEL
    col_type colsToBeChecked;

    SlicePred(const T& k, PRED* n, MBase* mmapPtr, const col_type& cols) : PRED(mmapPtr, n), key(k), colsToBeChecked(cols) {
    }
#else

    SlicePred(const T& k, PRED* n, MBase* mmapPtr, const col_type& cols) : PRED(mmapPtr, n), key(k) {
    }
#endif

    virtual bool matchesAny(Transaction *t) {
        VBase* dv = t->undoBufferHead;
        while (dv != nullptr) {
            if (matches(dv))
                return true;
            dv = dv->nextInUndoBuffer;
        }
        return false;
    }

    FORCE_INLINE bool matches(VBase* V) {
        EntryMV<T>*e = (EntryMV<T>*)V->e;
        if (e->tbl != tbl)
            return false;
         Version<T>*dv = (Version<T>*)V;
#ifdef ATTRIB_LEVEL
        if ((colsToBeChecked & dv->cols).none())
            return false;
#endif

        Version<T>* dv2 = (Version<T>*) dv->oldV.load();

        const T& k1 = dv->obj;

        if (!k1.isInvalid && IDX_FN::cmp(k1, key) == 0)
            return true;
        
        if (dv2 != nullptr) {
            const T& k2 = dv2->obj;
            if (!k2.isInvalid && IDX_FN::cmp(k2, key) == 0)
                return true;
        }
        return false;
    }

    virtual ~SlicePred() {
    }
};

#endif /* PREDICATE_H */
