#define USE_TPCH_PART
#define USE_TPCH_SUPPLIER
#define USE_TPCH_LINEITEM
#define USE_TPCH_ORDERS
#define USE_TPCH_CUSTOMER
#define USE_TPCH_NATION
#define USE_TPCH_REGION

#ifdef BATCH_MODE
    #include "codegen_batch/Tpch8VCpp.hpp"
#else
    #include "codegen/Tpch8VCpp.hpp"
#endif


namespace dbtoaster
{
    class data_t;

    void print_result(data_t& data)
    {
        std::cout << "MKT_SHARE: " << data.get_MKT_SHARE().count() << std::endl;    
    }
}


