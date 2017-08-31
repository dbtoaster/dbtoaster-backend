#define USE_TPCH_CUSTOMER
#define USE_TPCH_ORDERS
#define USE_TPCH_LINEITEM

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch18VCpp.hpp"
#else
    #include "codegen/Tpch18VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "QUERY18: " << data.get_QUERY18().count() << std::endl;    
    }
}


