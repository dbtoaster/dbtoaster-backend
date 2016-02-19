#define USE_TPCH_PARTSUPP
#define USE_TPCH_PART
#define USE_TPCH_SUPPLIER

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch16VCpp.hpp"
#else
    #include "codegen/Tpch16VCpp.hpp"
#endif

namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "SUPPLIER_CNT: " << data.get_SUPPLIER_CNT().count() << std::endl;    
    }
}


