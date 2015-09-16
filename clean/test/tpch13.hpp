#define USE_TPCH_ORDERS
#define USE_TPCH_CUSTOMER

#include "../target/tmp/Tpch13VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "CUSTDIST: " << data.get_CUSTDIST().count() << std::endl;    
    }
}


