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

    Transaction() {
        threadId = 0;
        commitTS = initCommitTS;
        undoBufferHead = nullptr;
        predicateHead = nullptr;
    }
};

#endif /* TRANSACTION_H */

