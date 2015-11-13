#define USE_TPCH_ORDERS
#define USE_TPCH_LINEITEM

#include "codegen/Tpch12VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "HIGH_LINE_COUNT: " << data.get_HIGH_LINE_COUNT().count() << std::endl;    
    }
}


