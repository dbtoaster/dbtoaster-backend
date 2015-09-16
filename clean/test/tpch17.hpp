#define USE_TPCH_PART
#define USE_TPCH_LINEITEM

#include "../target/tmp/Tpch17VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "AVG_YEARLY: " << data.get_AVG_YEARLY() << std::endl;    
    }
}


