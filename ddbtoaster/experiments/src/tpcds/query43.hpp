#define USE_TPCDS_DATEDIM
#define USE_TPCDS_STORESALES
#define USE_TPCDS_STORE

#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds43VCpp.hpp"
#else
    #include "codegen/Tpcds43VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY43: " 
                  << "    "  << data.get_SUN_SALES().count() 
                  << "    "  << data.get_MON_SALES().count() 
                  << "    "  << data.get_TUE_SALES().count() 
                  << "    "  << data.get_WED_SALES().count() 
                  << "    "  << data.get_THU_SALES().count() 
                  << "    "  << data.get_FRI_SALES().count() 
                  << "    "  << data.get_SAT_SALES().count() 
                  << std::endl;    
    }
}


