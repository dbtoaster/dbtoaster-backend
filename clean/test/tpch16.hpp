#define USE_TPCH_PARTSUPP
#define USE_TPCH_PART
#define USE_TPCH_SUPPLIER

#include "../target/tmp/Tpch16VCpp.hpp"

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "SUPPLIER_CNT: " << data.get_SUPPLIER_CNT().count() << std::endl;    
    }
}


