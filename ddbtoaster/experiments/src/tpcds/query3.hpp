#define USE_TPCDS_DATEDIM
#define USE_TPCDS_STORESALES
#define USE_TPCDS_ITEM

#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds3VCpp.hpp"
#else
    #include "codegen/Tpcds3VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY3: " << data.get_SUM_AGG().count() << std::endl;    
    }
}


