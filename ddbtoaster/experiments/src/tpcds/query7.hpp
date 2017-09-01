#define USE_TPCDS_DATEDIM
#define USE_TPCDS_CUSTOMERDEMOGRAPHICS
#define USE_TPCDS_PROMOTION
#define USE_TPCDS_STORESALES
#define USE_TPCDS_ITEM


#ifdef BATCH_MODE
    #include "codegen_batch/Tpcds7VCpp.hpp"
#else
    #include "codegen/Tpcds7VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "TPC-DS QUERY7: " << data.get_AGG1().count() 
                  << "   " << data.get_AGG1().count()  
                  << "   " << data.get_AGG2().count()  
                  << "   " << data.get_AGG3().count()  
                  << "   " << data.get_AGG4().count()  
                  << std::endl;    
    }
}


