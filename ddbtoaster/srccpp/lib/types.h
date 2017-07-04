
#ifndef TYPES_H
#define TYPES_H
struct alignas(64) Transaction;
struct alignas(64) TransactionManager;
struct PRED;
struct alignas(64) VBase;
struct alignas(64) MBase;
struct alignas(64) EBase;
struct Program;

#ifdef NDEBUG
#define  FORCE_INLINE  __attribute__((always_inline))
#define NOINLINE __attribute__ ((noinline))
#else
#define NOINLINE __attribute__ ((noinline))
#define FORCE_INLINE  __attribute__((always_inline))
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

#define setAffinity(thread_id)\
    cpu_set_t cpuset;\
    CPU_ZERO(&cpuset);\
    CPU_SET(thread_id+1, &cpuset);\
    auto s = sched_setaffinity(0, sizeof (cpu_set_t), &cpuset);\
    if (s != 0)\
        throw std::runtime_error("Cannot set affinity");

#define setSched(type)\
    sched_param param;\
    param.__sched_priority =  sched_get_priority_max(type);\
    s = sched_setscheduler(0, type, &param);\
    if (s != 0)\
        cerr << "Cannot set scheduler" << endl;

#ifndef NUMTHREADS
#define NUMTHREADS 4
#endif 

#define MAX_IDXES_PER_TBL 3

const uint numThreads = NUMTHREADS;
#endif /* TYPES_H */

