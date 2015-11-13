#define USE_TPCH_PART
#define USE_TPCH_LINEITEM

#include "codegen/Tpch17VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "AVG_YEARLY: " << data.get_AVG_YEARLY() << std::endl;    
    }
}


