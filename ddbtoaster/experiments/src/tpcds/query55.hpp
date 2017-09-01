#define USE_TPCDS_DATEDIM
#define USE_TPCDS_STORESALES
#define USE_TPCDS_ITEM

#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds55VCpp.hpp"
#else
    #include "codegen/Tpcds55VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY55: " << data.get_EXT_PRICE().count() << std::endl;    
    }
}


