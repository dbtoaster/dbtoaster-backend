#define USE_TPCH_LINEITEM
#define USE_TPCH_SUPPLIER

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch15VCpp.hpp"
#else
    #include "codegen/Tpch15VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "COUNT: " << data.get_COUNT().count() << std::endl;    
    }
}


