#define USE_TPCH_PART
#define USE_TPCH_SUPPLIER
#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS
#define USE_TPCH_CUSTOMER
#define USE_TPCH_NATION
#define USE_TPCH_REGION

#include "../target/tmp/Tpch8VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "MKT_SHARE: " << data.get_MKT_SHARE().count() << std::endl;    
    }
}


