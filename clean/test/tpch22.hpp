#define USE_TPCH_CUSTOMER
#define USE_TPCH_ORDERS

#include "../target/tmp/Tpch22VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "NUMCUST: " << data.get_NUMCUST().count() << std::endl;    
    }
}


