#define USE_TPCH_SUPPLIER
#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS
#define USE_TPCH_CUSTOMER
#define USE_TPCH_NATION

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch7VCpp.hpp"
#else
    #include "codegen/Tpch7VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "REVENUE: " << data.get_REVENUE().count() << std::endl;    
    }
}


