#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "types.h"

struct Transaction {
    VBase* undoBufferHead;
    PRED* predicateHead;
    static TransactionManager& tm;
    timestamp startTS;
    volatile timestamp commitTS;
    Transaction * prevCommitted;
    uint8_t threadId;

    uint8_t ptype;
    Transaction* failedBecauseOf;
    Transaction() {
        failedBecauseOf = nullptr;
        threadId = 0;
        commitTS = initCommitTS;
        undoBufferHead = nullptr;
        predicateHead = nullptr;
        prevCommitted = nullptr;
    }

    void reset() {
        threadId = 0;
        commitTS = initCommitTS;
        undoBufferHead = nullptr;
        predicateHead = nullptr;
        prevCommitted = nullptr;
    }
};

#endif /* TRANSACTION_H */

