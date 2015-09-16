#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS

#include "../target/tmp/Tpch4VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "ORDER_COUNT: " << data.get_ORDER_COUNT().count() << std::endl;    
    }
}


