#define USE_TPCH_CUSTOMER
#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS
#define USE_TPCH_NATION

#include "../target/tmp/Tpch10VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "REVENUE: " << data.get_REVENUE().count() << std::endl;    
    }
}


