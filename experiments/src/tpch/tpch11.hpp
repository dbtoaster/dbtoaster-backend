#define USE_TPCH_PARTSUPP
#define USE_TPCH_SUPPLIER
#define USE_TPCH_NATION

#include "codegen/Tpch11VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "QUERY11: " << data.get_QUERY11().count() << std::endl;    
    }
}


