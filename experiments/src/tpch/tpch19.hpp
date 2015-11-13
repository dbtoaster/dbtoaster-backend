#define USE_TPCH_PART
#define USE_TPCH_LINEITEM

#include "codegen/Tpch19VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "REVENUE: " << data.get_REVENUE() << std::endl;    
    }
}


