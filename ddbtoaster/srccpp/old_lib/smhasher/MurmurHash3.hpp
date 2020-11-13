//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#ifndef _MURMURHASH3_H_
#define _MURMURHASH3_H_

// Check windows
#if _WIN32 || _WIN64
   #if _WIN64
     #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif

// Check GCC
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif

//-----------------------------------------------------------------------------
// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER) && (_MSC_VER < 1600)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

// Other compilers

#else	// defined(_MSC_VER)

#include <stdint.h>

#endif // !defined(_MSC_VER)

//-----------------------------------------------------------------------------
void MurmurHash3_x86_32  ( const void * key, int len, uint32_t seed, void * out );

#ifndef ENV64BIT
void MurmurHash3_128 ( const void * key, int len, uint32_t seed, void * out );
#else
void MurmurHash3_128 ( const void * key, int len, uint32_t seed, void * out );
#endif
//-----------------------------------------------------------------------------

#endif // _MURMURHASH3_H_
