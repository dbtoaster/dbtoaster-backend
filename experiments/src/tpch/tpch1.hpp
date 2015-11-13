#define USE_TPCH_LINEITEM

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch1VCpp.hpp"
#else
    #include "codegen/Tpch1VCpp.hpp"
#endif


namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "AVG_DISC: " << data.get_AVG_DISC().count() << std::endl;    
    }
}


