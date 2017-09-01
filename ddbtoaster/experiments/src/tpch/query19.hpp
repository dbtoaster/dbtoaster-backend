#define USE_TPCH_PART
#define USE_TPCH_LINEITEM

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch19VCpp.hpp"
#else
    #include "codegen/Tpch19VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "REVENUE: " << data.get_REVENUE() << std::endl;    
    }
}


