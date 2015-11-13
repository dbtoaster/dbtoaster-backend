#define USE_TPCH_SUPPLIER
#define USE_TPCH_NATION
#define USE_TPCH_PARTSUPP
#define USE_TPCH_PART
#define USE_TPCH_LINEITEM

#include "codegen/Tpch20VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "COUNT: " << data.get_COUNT().count() << std::endl;    
    }
}


