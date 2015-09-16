#define USE_TPCH_SUPPLIER
#define USE_TPCH_NATION
#define USE_TPCH_ORDERS
#define USE_TPCH_LINEITEM

#include "../target/tmp/Tpch21VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "NUMWAIT: " << data.get_NUMWAIT().count() << std::endl;    
    }
}


