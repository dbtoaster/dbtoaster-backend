#define USE_TPCH_LINEITEM

#include "../target/tmp/Tpch1VCpp.hpp"


namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "AVG_DISC: " << data.get_AVG_DISC().count() << std::endl;    
    }
}


