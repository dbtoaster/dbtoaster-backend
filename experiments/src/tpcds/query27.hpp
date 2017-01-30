#define USE_TPCDS_DATEDIM
#define USE_TPCDS_CUSTOMERDEMOGRAPHICS
#define USE_TPCDS_STORESALES
#define USE_TPCDS_ITEM
#define USE_TPCDS_STORE

#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds27VCpp.hpp"
#else
    #include "codegen/Tpcds27VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY27: " << data.get_AGG1().count() 
                  << "   " << data.get_AGG2().count() 
                  << "   " << data.get_AGG3().count() 
                  << "   " << data.get_AGG4().count() 
                  << std::endl;    
    }
}


