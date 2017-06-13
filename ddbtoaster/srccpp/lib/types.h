
#ifndef TYPES_H
#define TYPES_H
struct Transaction;
struct TransactionManager;
struct PRED;
struct VBase;
struct MBase;

#ifdef NDEBUG
#define  FORCEINLINE  __attribute__((always_inline))
#define NOINLINE __attribute__ ((noinline))
#else
#define NOINLINE __attribute__ ((noinline))
#define FORCEINLINE   __attribute__ ((noinline))
#endif 

typedef uint64_t timestamp;
const timestamp mask = 1LL << 63;
const timestamp nonAccessibleMemory = mask + 100;
const timestamp initCommitTS = mask + 5;

#define isTempTS(ts) (ts&mask)  //to check if timestamp is temporary or a proper commit ts
#define PTRtoTS(t) ((timestamp) t ^ mask) // generate temporary timestamp for transaction from its pointer
#define TStoPTR(ts) ((Transaction*) (ts ^ mask)) //get transaction pointer from its temporary timestamp

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

typedef std::bitset<32> col_type;

enum TransactionReturnStatus : char {
    SUCCESS, ABORT, WW_ABORT, COMMIT_FAILURE
};

//enum Operation : char {
//    NOOP, INSERT, DELETE, UPDATE, INVALID
//};

enum OperationReturnStatus : char {
    OP_SUCCESS, NO_KEY, DUPLICATE_KEY, WW_VALUE
};

FORCE_INLINE TransactionReturnStatus TR(OperationReturnStatus op) {
    return op == NO_KEY ? ABORT : WW_ABORT;
}
FORCE_INLINE OperationReturnStatus OR(TransactionReturnStatus op) {
    return op == WW_ABORT ? WW_VALUE : NO_KEY;
}
#endif /* TYPES_H */

