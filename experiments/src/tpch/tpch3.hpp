#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS
#define USE_TPCH_CUSTOMER

#include "codegen/Tpch3VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "QUERY3: " << data.get_QUERY3().count() << std::endl;    
    }
}


