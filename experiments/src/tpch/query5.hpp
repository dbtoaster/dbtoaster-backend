#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS
#define USE_TPCH_CUSTOMER
#define USE_TPCH_SUPPLIER
#define USE_TPCH_NATION
#define USE_TPCH_REGION

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch5VCpp.hpp"
#else
    #include "codegen/Tpch5VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "REVENUE: " << data.get_REVENUE().count() << std::endl;    
    }
}


