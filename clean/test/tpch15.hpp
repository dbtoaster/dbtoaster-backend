#define USE_TPCH_LINEITEM
#define USE_TPCH_SUPPLIER

#include "../target/tmp/Tpch15VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "COUNT: " << data.get_COUNT().count() << std::endl;    
    }
}


