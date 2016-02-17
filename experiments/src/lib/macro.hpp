#ifndef DBTOASTER_MACRO_HPP
#define DBTOASTER_MACRO_HPP

//-----------------------------------------------------------------------------
// Microsoft Visual Studio

#if defined(_MSC_VER)

typedef unsigned int uint32_t;

#define FORCE_INLINE  __forceinline
#define NEVER_INLINE  __declspec(noinline)

//-----------------------------------------------------------------------------
// Other compilers

#else //  defined(_MSC_VER)

#include <stdint.h>

#define FORCE_INLINE inline __attribute__((always_inline))
#define NEVER_INLINE __attribute__((noinline))

#endif  //  !defined(_MSC_VER)

#endif /* DBTOASTER_MACRO_HPP */