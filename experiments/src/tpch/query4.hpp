#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch4VCpp.hpp"
#else
    #include "codegen/Tpch4VCpp.hpp"
#endif


namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "ORDER_COUNT: " << data.get_ORDER_COUNT().count() << std::endl;    
    }
}


