#define USE_TPCH_LINEITEM
#define USE_TPCH_PART

#include "codegen/Tpch14VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "PROMO_REVENUE: " << data.get_PROMO_REVENUE() << std::endl;    
    }
}


