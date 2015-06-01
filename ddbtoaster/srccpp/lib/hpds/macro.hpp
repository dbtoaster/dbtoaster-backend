#include <string>

//-----------------------------------------------------------------------------
// Microsoft Visual Studio

#if defined(_MSC_VER)

#define FORCE_INLINE  __forceinline
#define NEVER_INLINE  __declspec(noinline)

//-----------------------------------------------------------------------------
// Other compilers

#else //  defined(_MSC_VER)

#define FORCE_INLINE inline __attribute__((always_inline))
#define NEVER_INLINE __attribute__((noinline))

#endif  //  !defined(_MSC_VER)