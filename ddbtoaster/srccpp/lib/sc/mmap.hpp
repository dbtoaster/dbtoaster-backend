#ifdef SC_GENERATED  //using SC
    #include "ScExtra.h"

    #ifdef CONCURRENT
        #include "cmmap.hpp"   // For SC concurrent CPP
    #else
        #include "mmap2.hpp"   // For SC CPP
    #endif
#endif
