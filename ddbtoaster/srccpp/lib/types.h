
#ifndef TYPES_H
#define TYPES_H
struct Transaction;
struct TransactionManager;


#ifdef NDEBUG
#define  FORCEINLINE  __attribute__((always_inline))
#define NOINLINE __attribute__ ((noinline))
#else
#define NOINLINE __attribute__ ((noinline))
#define FORCEINLINE  
#endif 

typedef uint64_t timestamp;
const timestamp mask = 1LL << 63;
const timestamp nonAccessibleMemory = mask + 100;
const timestamp initCommitTS = mask + 5;

template<typename T>
FORCE_INLINE bool isMarked(T t) {
    return ((size_t) t & mask);
}

template<typename T>
FORCE_INLINE T mark(T t) {
    return (T) ((size_t) t | mask);
}

template<typename T>
FORCE_INLINE T unmark(T t) {
    return (T) ((size_t) t & ~mask);
}

enum TransactionReturnStatus : char {
    SUCCESS, ABORT, WW_ABORT, COMMIT_FAILURE
};

enum Operation : char {
    NOOP, INSERT, DELETE, UPDATE, INVALID
};

enum OperationReturnStatus : char {
    OP_SUCCESS, NO_KEY, DUPLICATE_KEY, WW_VALUE
};

FORCE_INLINE TransactionReturnStatus TR(OperationReturnStatus op) {
    return op == WW_VALUE ? WW_ABORT : ABORT;
}
FORCE_INLINE OperationReturnStatus OR(TransactionReturnStatus op) {
    return op == WW_ABORT ? WW_VALUE : NO_KEY;
}
#endif /* TYPES_H */

