#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H
#include <atomic>
#include "types.h"
#include "Transaction.h"
#include "Predicate.h"
#include "Version.h"
#include "SpinLock.h"

struct TransactionManager {
    std::atomic<timestamp> timestampGen;
    SpinLock commitLock, counterLock;
    std::atomic<Transaction *> committedXactsTail;

    TransactionManager() : timestampGen(0) {
        committedXactsTail = nullptr;
    }

    FORCE_INLINE void begin(Transaction& xact) {
        counterLock.lock();
        auto ts = timestampGen++;
        xact.startTS = ts;
        counterLock.unlock();
    }

    FORCE_INLINE void rollback(Transaction& xact) {
        auto dv = xact.undoBufferHead;
        while (dv) {
            assert(TStoPTR(dv->xactid) == &xact);
            dv->removeFromVersionChain();
            dv = dv->nextInUndoBuffer;
        }
        PRED* p;
        while (xact.predicateHead) {
            p = xact.predicateHead;
            xact.predicateHead = xact.predicateHead->next;
            free(p);
        }
        xact.undoBufferHead = nullptr;
        xact.predicateHead = nullptr;
    }

    //Validate transaction by matching its predicates with versions of recently committed transactions 

    FORCE_INLINE bool validate(Transaction& xact, Transaction *currentXact) {
        auto pred = xact.predicateHead;
        while (pred != nullptr) {
            //go through predicates
            bool predMatches = pred->matchesAny(currentXact);
            if (predMatches) {
                //we stop as soon as one predicate matches, and there is no point in continuing validation
                rollback(xact);
                return false;
                //Will do full rollback
                //Rollback takes care of versions
            }
            pred = pred->next;
        }
        return true;
    }

    FORCE_INLINE void commit(Transaction& xact) {
        auto dv = xact.undoBufferHead;
        counterLock.lock();
        xact.commitTS = timestampGen.fetch_add(1);
        counterLock.unlock();

        commitLock.unlock();

        while (dv) {
            assert(dv->xactid == PTRtoTS(&xact));
            dv->xactid = xact.commitTS; //TODO: DOES NOT SET CommitTS on the moved version
            //This is still correct , as the getCorrectDV looks up commit TS of transaction even if not set in version
            // BUt this has performance overhead as in almost all cases, it will lookup transaction un necessarily
            dv = dv->nextInUndoBuffer;
        }
        PRED* p;
        while (xact.predicateHead) {
            p = xact.predicateHead;
            xact.predicateHead = xact.predicateHead->next;
            free(p);
        }
    }

    FORCE_INLINE bool validateAndCommit(Transaction& xact) {
        if (xact.undoBufferHead == nullptr) { //Read only transaction
            PRED* p;
            while (xact.predicateHead) {
                p = xact.predicateHead;
                xact.predicateHead = xact.predicateHead->next;
                free(p);
            }
            xact.commitTS = xact.startTS;
            return true;
        }


        Transaction *startXact = committedXactsTail, *endXact = nullptr, *currentXact;

        /*
         We validate in rounds. We start from the most recently committed transaction and go backwards until
             we reach nullptr, 
             or transaction that committed before this transaction began,
             or whatever was most recent transaction in the previous round.
        For example, if we have a commit list .. 6 - 7 - 8 - 9 (tail)
        and the current transaction began at 5, a possible validation order is 
        9 - 8 - 7 - 6 - 12 - 11 -10 - 16 - 15 - 14 - 13, and so on
         */

        do {
            if (startXact != nullptr) {
                currentXact = startXact;
                //wait until committed??  current->xact->status == COMMITTED
                //                while (currentXact->commitTS == initCommitTS);
                //Required only when we have slice on value, as the final value may not be ready(copy from previous committed etc)

                //go until end of recently committed list
                while (currentXact != nullptr && currentXact != endXact && currentXact->commitTS > xact.startTS) {

                    //in OMVCC, if validate returns false, we abort and do full restart
                    if (!validate(xact, currentXact))
                        return false;
                    currentXact = currentXact->prevCommitted;
                }
            }
            endXact = startXact;

            //If either the tail changed or if we cannot get commit lock, then there are new transactions that we should validate against
            if (committedXactsTail != startXact || !commitLock.try_lock()) {
                startXact = committedXactsTail;
                continue;
            }
            //we have the lock here

            xact.prevCommitted = startXact;
            //try adding this transaction as the latest committed
            if (!committedXactsTail.compare_exchange_strong(startXact, &xact)) {
                commitLock.unlock();
                continue;
            }

            commit(xact); //will release commitLock internally
            return true;
        } while (true);
    }
};


#endif /* TRANSACTIONMANAGER_H */

