#define USE_TPCH_CUSTOMER
#define USE_TPCH_ORDERS

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch22VCpp.hpp"
#else
    #include "codegen/Tpch22VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "NUMCUST: " << data.get_NUMCUST().count() << std::endl;    
    }
}


