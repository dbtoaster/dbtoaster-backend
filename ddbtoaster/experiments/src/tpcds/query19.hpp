#define USE_TPCDS_DATEDIM
#define USE_TPCDS_STORESALES
#define USE_TPCDS_ITEM
#define USE_TPCDS_CUSTOMER
#define USE_TPCDS_CUSTOMERADDRESS
#define USE_TPCDS_STORE

#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds19VCpp.hpp"
#else
    #include "codegen/Tpcds19VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY19: " << data.get_EXT_PRICE().count() << std::endl;    
    }
}


