#define USE_TPCH_CUSTOMER
#define USE_TPCH_ORDERS
#define USE_TPCH_LINEITEM

#include "codegen/Tpch18VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "QUERY18: " << data.get_QUERY18().count() << std::endl;    
    }
}


