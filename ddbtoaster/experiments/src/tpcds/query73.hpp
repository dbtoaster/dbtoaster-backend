#define USE_TPCDS_DATEDIM
#define USE_TPCDS_HOUSEHOLDDEMOGRAPHICS
#define USE_TPCDS_STORESALES
#define USE_TPCDS_CUSTOMER
#define USE_TPCDS_STORE

#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds73VCpp.hpp"
#else
    #include "codegen/Tpcds73VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY73: " << data.get_COUNT().count() << std::endl;    
    }
}


