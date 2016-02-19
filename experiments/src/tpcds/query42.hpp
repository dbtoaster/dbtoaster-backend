#define USE_TPCDS_DATEDIM
#define USE_TPCDS_STORESALES
#define USE_TPCDS_ITEM

#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds42VCpp.hpp"
#else
    #include "codegen/Tpcds42VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY42: " << data.get___SQL_SUM_AGGREGATE_1().count() << std::endl;    
    }
}


