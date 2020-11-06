#ifndef DRIVER_PLATFORM_HPP
#define DRIVER_PLATFORM_HPP

#include <iostream>

void setAffinity(int cpu);

//-----------------------------------------------------------------------------
// Microsoft Visual Studio

#if defined(_MSC_VER)

#include <windows.h>

void setAffinity(int cpu) {
  SetProcessAffinityMask(GetCurrentProcess(), cpu);
  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
}

//-----------------------------------------------------------------------------
// Other compilers

#else //  defined(_MSC_VER)

#include <sched.h>

void setAffinity(int cpu) {
#if !defined(__CYGWIN__) && !defined(__APPLE__)
  cpu_set_t mask;
    
  CPU_ZERO(&mask);
    
  CPU_SET(cpu, &mask);
    
  if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
    std::err << "WARNING: Could not set CPU affinity" << std::endl;
  }
#endif
}

#endif  //  !defined(_MSC_VER)

#endif /* DRIVER_PLATFORM_HPP */