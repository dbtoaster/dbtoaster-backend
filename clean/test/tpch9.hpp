#define USE_TPCH_PART
#define USE_TPCH_SUPPLIER
#define USE_TPCH_PARTSUPP
#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS
#define USE_TPCH_NATION

#include "../target/tmp/Tpch9VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "SUM_PROFIT: " << data.get_SUM_PROFIT().count() << std::endl;    
    }
}


