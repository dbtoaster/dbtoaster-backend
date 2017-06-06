
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

#endif /* TYPES_H */

