#define USE_TPCH_ORDERS
#define USE_TPCH_CUSTOMER

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch13VCpp.hpp"
#else
    #include "codegen/Tpch13VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "CUSTDIST: " << data.get_CUSTDIST().count() << std::endl;    
    }
}


