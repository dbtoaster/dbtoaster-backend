#ifndef DBTOASTER_TEST_TEMPLATE_HPP
#define DBTOASTER_TEST_TEMPLATE_HPP

#include "stopwatch.hpp"
#include "csvreader.hpp"


const string dataPath = "datasets/tpch";
const string dataset = "standard";

namespace dbtoaster 
{
    #ifdef USE_TPCH_LINEITEM 
        #define IF_LINEITEM(stmt) stmt
    #else
        #define IF_LINEITEM(stmt) 
    #endif

    #ifdef USE_TPCH_ORDERS 
        #define IF_ORDERS(stmt) stmt
    #else
        #define IF_ORDERS(stmt) 
    #endif

    #ifdef USE_TPCH_CUSTOMER 
        #define IF_CUSTOMER(stmt) stmt
    #else
        #define IF_CUSTOMER(stmt) 
    #endif

    #ifdef USE_TPCH_PARTSUPP 
        #define IF_PARTSUPP(stmt) stmt
    #else
        #define IF_PARTSUPP(stmt) 
    #endif

    #ifdef USE_TPCH_PART 
        #define IF_PART(stmt) stmt
    #else
        #define IF_PART(stmt) 
    #endif

    #ifdef USE_TPCH_SUPPLIER 
        #define IF_SUPPLIER(stmt) stmt
    #else
        #define IF_SUPPLIER(stmt) 
    #endif

    #ifdef USE_TPCH_NATION
        #define IF_NATION(stmt) stmt
    #else
        #define IF_NATION(stmt) 
    #endif

    #ifdef USE_TPCH_REGION 
        #define IF_REGION(stmt) stmt
    #else
        #define IF_REGION(stmt) 
    #endif


    class data_t;

    IF_LINEITEM ( TPCHLineitemBatch* lineitemBatch; )
    IF_ORDERS ( TPCHOrdersBatch* ordersBatch; )
    IF_CUSTOMER ( TPCHCustomerBatch* customerBatch; )
    IF_PARTSUPP ( TPCHPartSuppBatch* partsuppBatch; )
    IF_PART ( TPCHPartBatch* partBatch; )    
    IF_SUPPLIER ( TPCHSupplierBatch* supplierBatch; )
    IF_NATION ( TPCHNationBatch* nationBatch; )
    IF_REGION ( TPCHRegionBatch* regionBatch; )

    void load_relations()
    {
        Stopwatch sw;

        IF_LINEITEM ({
            sw.restart();
            std::vector<TPCHLineitem> lineitems;
            //readFromBinaryFile(lineitems, dataPath + "/" + dataset + "/lineitem.bin");
            readFromFile(lineitems, dataPath + "/" + dataset + "/lineitem.csv", '|');
            //writeToBinaryFile(lineitems, dataPath + "/" + dataset + "/lineitem.bin");
            lineitemBatch = new TPCHLineitemBatch(lineitems);
            sw.stop();
            std::cout << "Loaded lineitem (" << lineitemBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_ORDERS ({
            sw.restart();
            std::vector<TPCHOrders> orders;
            //readFromBinaryFile(orders, dataPath + "/" + dataset + "./orders.bin");
            readFromFile(orders, dataPath + "/" + dataset + "/orders.csv", '|');
            //writeToBinaryFile(orders, dataPath + "/" + dataset + "/orders.bin");
            ordersBatch = new TPCHOrdersBatch(orders);
            sw.stop();
            std::cout << "Loaded orders (" << ordersBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_CUSTOMER ({
            sw.restart();
            std::vector<TPCHCustomer> customers;
            //readFromBinaryFile(customers, dataPath + "/" + dataset + "/customers.bin");
            readFromFile(customers, dataPath + "/" + dataset + "/customer.csv", '|');
            //writeToBinaryFile(customers, dataPath + "/" + dataset + "/customers.bin");
            customerBatch = new TPCHCustomerBatch(customers);            
            sw.stop();
            std::cout << "Loaded customer (" << customerBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_PARTSUPP ({
            sw.restart();
            std::vector<TPCHPartSupp> partsupps;
            //readFromBinaryFile(partsupps, dataPath + "/" + dataset + "/partsupp.bin");
            readFromFile(partsupps, dataPath + "/" + dataset + "/partsupp.csv", '|');
            //writeToBinaryFile(partsupps, dataPath + "/" + dataset + "/partsupp.bin");
            partsuppBatch = new TPCHPartSuppBatch(partsupps);            
            sw.stop();
            std::cout << "Loaded partsupp (" << partsuppBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_PART ({
            sw.restart();
            std::vector<TPCHPart> parts;
            //readFromBinaryFile(parts, dataPath + "/" + dataset + "/part.bin");
            readFromFile(parts, dataPath + "/" + dataset + "/part.csv", '|');
            //writeToBinaryFile(parts, dataPath + "/" + dataset + "/part.bin");
            partBatch = new TPCHPartBatch(parts);    
            sw.stop();
            std::cout << "Loaded part (" << partBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_SUPPLIER ({
            sw.restart();
            std::vector<TPCHSupplier> suppliers;
            //readFromBinaryFile(suppliers, dataPath + "/" + dataset + "/supplier.bin");
            readFromFile(suppliers, dataPath + "/" + dataset + "/supplier.csv", '|');
            //writeToBinaryFile(suppliers, dataPath + "/" + dataset + "/supplier.bin");
            supplierBatch = new TPCHSupplierBatch(suppliers);
            sw.stop();
            std::cout << "Loaded supplier (" << supplierBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_NATION ({
            std::vector<TPCHNation> nations;
            //readFromBinaryFile(nations, dataPath + "/" + dataset + "/nation.bin");
            readFromFile(nations, dataPath + "/" + dataset + "/nation.csv", '|');
            //writeToBinaryFile(nations, dataPath + "/" + dataset + "/nation.bin");
            nationBatch = new TPCHNationBatch(nations);
        })  

        IF_REGION ({
            std::vector<TPCHRegion> regions;
            //readFromBinaryFile(regions, dataPath + "/" + dataset + "/region.bin");
            readFromFile(regions, dataPath + "/" + dataset + "/region.csv", '|');
            //writeToBinaryFile(regions, dataPath + "/" + dataset + "/region.bin");
            regionBatch = new TPCHRegionBatch(regions);
        })    
    }

    void destroy_relations()
    {
        IF_LINEITEM( delete lineitemBatch; )
        IF_ORDERS ( delete ordersBatch; )
        IF_CUSTOMER ( delete customerBatch; )
        IF_PARTSUPP ( delete partsuppBatch; )
        IF_PART ( delete partBatch; )
        IF_SUPPLIER ( delete supplierBatch; )
        IF_NATION ( delete nationBatch; )
        IF_REGION ( delete regionBatch; )
    }


#ifdef BATCH_MODE

    // Vectors storing batch updates
    IF_LINEITEM ( std::vector<TPCHLineitemBatch> lineitemBatchList; )    
    IF_ORDERS ( std::vector<TPCHOrdersBatch> ordersBatchList; )
    IF_CUSTOMER ( std::vector<TPCHCustomerBatch> customerBatchList; )
    IF_PARTSUPP ( std::vector<TPCHPartSuppBatch> partsuppBatchList; )
    IF_PART ( std::vector<TPCHPartBatch> partBatchList; )
    IF_SUPPLIER ( std::vector<TPCHSupplierBatch> supplierBatchList; )
    IF_NATION ( std::vector<TPCHNationBatch> nationBatchList; )
    IF_REGION ( std::vector<TPCHRegionBatch> regionBatchList; )

    #define FLUSH_LINEITEM_BATCH {                      \
        TPCHLineitemBatch batch(tmpLineitemBatch);      \
        lineitemBatchList.push_back(batch);             \
        tmpLineitemBatch.size = 0;                      \
    }

    #define FLUSH_ORDERS_BATCH {                        \
        TPCHOrdersBatch batch(tmpOrdersBatch);          \
        ordersBatchList.push_back(batch);               \
        tmpOrdersBatch.size = 0;                        \
    }

    #define FLUSH_CUSTOMER_BATCH {                      \
        TPCHCustomerBatch batch(tmpCustomerBatch);      \
        customerBatchList.push_back(batch);             \
        tmpCustomerBatch.size = 0;                      \
    }

    #define FLUSH_PART_BATCH {                          \
        TPCHPartBatch batch(tmpPartBatch);              \
        partBatchList.push_back(batch);                 \
        tmpPartBatch.size = 0;                          \
    }

    #define FLUSH_PARTSUPP_BATCH {                      \
        TPCHPartSuppBatch batch(tmpPartsuppBatch);      \
        partsuppBatchList.push_back(batch);             \
        tmpPartsuppBatch.size = 0;                      \
    }

    #define FLUSH_SUPPLIER_BATCH {                      \
        TPCHSupplierBatch batch(tmpSupplierBatch);      \
        supplierBatchList.push_back(batch);             \
        tmpSupplierBatch.size = 0;                      \
    }

    #define FLUSH_NATION_BATCH {                        \
        TPCHNationBatch batch(tmpNationBatch);          \
        nationBatchList.push_back(batch);               \
        tmpNationBatch.size = 0;                        \
    }

    #define FLUSH_REGION_BATCH {                        \
        TPCHRegionBatch batch(tmpRegionBatch);          \
        regionBatchList.push_back(batch);               \
        tmpRegionBatch.size = 0;                        \
    }    

    #define FLUSH_TABLE_BATCHES {                                           \
        IF_NATION   ( if (tmpNationBatch.size > 0)   FLUSH_NATION_BATCH   ) \
        IF_REGION   ( if (tmpRegionBatch.size > 0)   FLUSH_REGION_BATCH   ) \
    }    

    #define FLUSH_STREAM_BATCHES {                                          \
        IF_LINEITEM ( if (tmpLineitemBatch.size > 0) FLUSH_LINEITEM_BATCH ) \
        IF_ORDERS   ( if (tmpOrdersBatch.size > 0)   FLUSH_ORDERS_BATCH   ) \
        IF_CUSTOMER ( if (tmpCustomerBatch.size > 0) FLUSH_CUSTOMER_BATCH ) \
        IF_PART     ( if (tmpPartBatch.size > 0)     FLUSH_PART_BATCH     ) \
        IF_PARTSUPP ( if (tmpPartsuppBatch.size > 0) FLUSH_PARTSUPP_BATCH ) \
        IF_SUPPLIER ( if (tmpSupplierBatch.size > 0) FLUSH_SUPPLIER_BATCH ) \
    }        

    #define ADD_TO_LINEITEM_BATCH {             \
        tmpLineitemBatch.add(                   \
            lineitemBatch->orderkey[i],         \
            lineitemBatch->partkey[i],          \
            lineitemBatch->suppkey[i],          \
            lineitemBatch->linenumber[i],       \
            lineitemBatch->quantity[i],         \
            lineitemBatch->extendedprice[i],    \
            lineitemBatch->discount[i],         \
            lineitemBatch->tax[i],              \
            lineitemBatch->returnflag[i],       \
            lineitemBatch->linestatus[i],       \
            lineitemBatch->shipdate[i],         \
            lineitemBatch->commitdate[i],       \
            lineitemBatch->receiptdate[i],      \
            lineitemBatch->shipinstruct[i],     \
            lineitemBatch->shipmode[i],         \
            lineitemBatch->comment[i]           \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_ORDERS_BATCH {               \
        tmpOrdersBatch.add(                     \
            ordersBatch->orderkey[i],           \
            ordersBatch->custkey[i],            \
            ordersBatch->orderstatus[i],        \
            ordersBatch->totalprice[i],         \
            ordersBatch->orderdate[i],          \
            ordersBatch->orderpriority[i],      \
            ordersBatch->clerk[i],              \
            ordersBatch->shippriority[i],       \
            ordersBatch->comment[i]             \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_CUSTOMER_BATCH {             \
        tmpCustomerBatch.add(                   \
            customerBatch->custkey[i],          \
            customerBatch->name[i],             \
            customerBatch->address[i],          \
            customerBatch->nationkey[i],        \
            customerBatch->phone[i],            \
            customerBatch->acctbal[i],          \
            customerBatch->mktsegment[i],       \
            customerBatch->comment[i]           \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_PART_BATCH {                 \
         tmpPartBatch.add(                      \
            partBatch->partkey[i],              \
            partBatch->name[i],                 \
            partBatch->mfgr[i],                 \
            partBatch->brand[i],                \
            partBatch->type[i],                 \
            partBatch->psize[i],                \
            partBatch->container[i],            \
            partBatch->retailprice[i],          \
            partBatch->comment[i]               \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
     }

    #define ADD_TO_SUPPLIER_BATCH {             \
        tmpSupplierBatch.add(                   \
            supplierBatch->suppkey[i],          \
            supplierBatch->name[i],             \
            supplierBatch->address[i],          \
            supplierBatch->nationkey[i],        \
            supplierBatch->phone[i],            \
            supplierBatch->acctbal[i],          \
            supplierBatch->comment[i]           \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_PARTSUPP_BATCH {             \
        tmpPartsuppBatch.add(                   \
            partsuppBatch->partkey[i],          \
            partsuppBatch->suppkey[i],          \
            partsuppBatch->availqty[i],         \
            partsuppBatch->supplycost[i],       \
            partsuppBatch->comment[i]           \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_NATION_BATCH {               \
        tmpNationBatch.add(                     \
            nationBatch->nationkey[i],          \
            nationBatch->name[i],               \
            nationBatch->regionkey[i],          \
            nationBatch->comment[i]             \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_TABLE_BATCHES                 \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_REGION_BATCH {               \
        tmpRegionBatch.add(                     \
            regionBatch->regionkey[i],          \
            regionBatch->name[i],               \
            regionBatch->comment[i]             \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_TABLE_BATCHES                 \
            batchCounter = 0;                   \
        }                                       \
    }

    #define INSERT_LINEITEM_BATCH {             \
        data.on_batch_update_LINEITEM(lineitemBatchList[i]); }

    #define INSERT_ORDERS_BATCH {               \
        data.on_batch_update_ORDERS(ordersBatchList[i]); }

    #define INSERT_CUSTOMER_BATCH {             \
        data.on_batch_update_CUSTOMER(customerBatchList[i]); }

    #define INSERT_PART_BATCH {             \
        data.on_batch_update_PART(partBatchList[i]); }

    #define INSERT_PARTSUPP_BATCH {             \
        data.on_batch_update_PARTSUPP(partsuppBatchList[i]); }

    #define INSERT_SUPPLIER_BATCH {             \
        data.on_batch_update_SUPPLIER(supplierBatchList[i]); }

    #define INSERT_NATION_BATCH {                               \
        TPCHNationBatch* nationBatch = &(nationBatchList[i]);   \
        for (size_t j = 0; j < nationBatch->size; j++)          \
            data.on_insert_NATION(                              \
                nationBatch->nationkey[j],                      \
                nationBatch->name[j],                           \
                nationBatch->regionkey[j],                      \
                nationBatch->comment[j]                         \
            );                                                  \
    }

    #define INSERT_REGION_BATCH {                               \
        TPCHRegionBatch* regionBatch = &(regionBatchList[i]);   \
        for (size_t j = 0; j < regionBatch->size; j++)          \
            data.on_insert_REGION(                              \
                regionBatch->regionkey[j],                      \
                regionBatch->name[j],                           \
                regionBatch->comment[j]                         \
            );                                                  \
    }

    void convert_tables_to_batches(size_t batchSize)
    { 
        size_t i = 0, count = 0, batchCounter = 0;

        IF_NATION ( TPCHNationBatch tmpNationBatch(batchSize); )
        IF_REGION ( TPCHRegionBatch tmpRegionBatch(batchSize); )

        IF_REGION ({
            count = regionBatch->size;

            for (; i < count; i++) 
            {
                IF_NATION ( ADD_TO_NATION_BATCH )
                IF_REGION ( ADD_TO_REGION_BATCH )
            }
        }) 

        IF_NATION ({
            count = nationBatch->size;
            
            for (; i < count; i++) 
            {            
                IF_NATION ( ADD_TO_NATION_BATCH ) 
            }
        })

        FLUSH_TABLE_BATCHES
    }

    void convert_streams_to_batches(size_t batchSize)
    { 
        size_t i = 0, count = 0, batchCounter = 0;

        IF_LINEITEM ( TPCHLineitemBatch tmpLineitemBatch(batchSize); )
        IF_ORDERS ( TPCHOrdersBatch tmpOrdersBatch(batchSize); )
        IF_CUSTOMER ( TPCHCustomerBatch tmpCustomerBatch(batchSize); )
        IF_PARTSUPP ( TPCHPartSuppBatch tmpPartsuppBatch(batchSize); )
        IF_PART ( TPCHPartBatch tmpPartBatch(batchSize); )    
        IF_SUPPLIER ( TPCHSupplierBatch tmpSupplierBatch(batchSize); )


        IF_SUPPLIER ({
            count = supplierBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( ADD_TO_LINEITEM_BATCH )
                IF_ORDERS ( ADD_TO_ORDERS_BATCH )
                IF_PART ( ADD_TO_PART_BATCH )
                IF_CUSTOMER ( ADD_TO_CUSTOMER_BATCH )
                IF_SUPPLIER ( ADD_TO_SUPPLIER_BATCH )
                IF_PARTSUPP ( ADD_TO_PARTSUPP_BATCH )
            }
        })

        IF_CUSTOMER ({
            count = customerBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( ADD_TO_LINEITEM_BATCH )
                IF_ORDERS ( ADD_TO_ORDERS_BATCH )
                IF_PART ( ADD_TO_PART_BATCH )
                IF_CUSTOMER ( ADD_TO_CUSTOMER_BATCH )
                IF_PARTSUPP ( ADD_TO_PARTSUPP_BATCH )
            }
        })

        IF_PART ({
            count = partBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( ADD_TO_LINEITEM_BATCH )
                IF_ORDERS ( ADD_TO_ORDERS_BATCH )
                IF_PART ( ADD_TO_PART_BATCH )
                IF_PARTSUPP ( ADD_TO_PARTSUPP_BATCH )
            }
        })

        IF_PARTSUPP ({
            count = partsuppBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( ADD_TO_LINEITEM_BATCH )
                IF_ORDERS ( ADD_TO_ORDERS_BATCH )
                IF_PARTSUPP ( ADD_TO_PARTSUPP_BATCH )
            }
        })

        IF_ORDERS ({
            count = ordersBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( ADD_TO_LINEITEM_BATCH )
                IF_ORDERS ( ADD_TO_ORDERS_BATCH )
            }
        }) 

        IF_LINEITEM ({
            count = lineitemBatch->size;
            
            for (; i < count; i++) 
            {            
                IF_LINEITEM ( ADD_TO_LINEITEM_BATCH ) 
            }
        })

        FLUSH_STREAM_BATCHES
    }

    void process_table_batches(dbtoaster::data_t& data) 
    {
        size_t i = 0, count = 0;

        IF_REGION ({
            count = regionBatchList.size();

            for (; i < count; i++) 
            {
                IF_NATION ( INSERT_NATION_BATCH )
                IF_REGION ( INSERT_REGION_BATCH )
            }
        }) 

        IF_NATION ({
            count = nationBatchList.size();

            for (; i < count; i++) 
            {
                IF_NATION ( INSERT_NATION_BATCH )
            }
        })
    }

    void process_stream_batches(dbtoaster::data_t& data) 
    {
        size_t i = 0, count = 0;

        IF_SUPPLIER ({
            count = supplierBatchList.size();

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM_BATCH )
                IF_ORDERS ( INSERT_ORDERS_BATCH )
                IF_PART ( INSERT_PART_BATCH )
                IF_CUSTOMER ( INSERT_CUSTOMER_BATCH )
                IF_SUPPLIER ( INSERT_SUPPLIER_BATCH )
                IF_PARTSUPP ( INSERT_PARTSUPP_BATCH )
            }
        })

        IF_CUSTOMER ({
            count = customerBatchList.size();

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM_BATCH )
                IF_ORDERS ( INSERT_ORDERS_BATCH )
                IF_PART ( INSERT_PART_BATCH )
                IF_CUSTOMER ( INSERT_CUSTOMER_BATCH )
                IF_PARTSUPP ( INSERT_PARTSUPP_BATCH )
            }
        })

        IF_PART ({
            count = partBatchList.size();

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM_BATCH )
                IF_ORDERS ( INSERT_ORDERS_BATCH )
                IF_PART ( INSERT_PART_BATCH )
                IF_PARTSUPP ( INSERT_PARTSUPP_BATCH )
            }
        })

        IF_PARTSUPP ({
            count = partsuppBatchList.size();

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM_BATCH )
                IF_ORDERS ( INSERT_ORDERS_BATCH )
                IF_PARTSUPP ( INSERT_PARTSUPP_BATCH )
            }
        })

        IF_ORDERS ({
            count = ordersBatchList.size();

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM_BATCH )
                IF_ORDERS ( INSERT_ORDERS_BATCH )
            }
        }) 

        IF_LINEITEM ({
            count = lineitemBatchList.size();

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM_BATCH )
            }
        })
    }

#else

    #define INSERT_LINEITEM {                   \
        data.on_insert_LINEITEM(                \
            lineitemBatch->orderkey[i],         \
            lineitemBatch->partkey[i],          \
            lineitemBatch->suppkey[i],          \
            lineitemBatch->linenumber[i],       \
            lineitemBatch->quantity[i],         \
            lineitemBatch->extendedprice[i],    \
            lineitemBatch->discount[i],         \
            lineitemBatch->tax[i],              \
            lineitemBatch->returnflag[i],       \
            lineitemBatch->linestatus[i],       \
            lineitemBatch->shipdate[i],         \
            lineitemBatch->commitdate[i],       \
            lineitemBatch->receiptdate[i],      \
            lineitemBatch->shipinstruct[i],     \
            lineitemBatch->shipmode[i],         \
            lineitemBatch->comment[i]); }

    #define INSERT_ORDERS {                 \
        data.on_insert_ORDERS(              \
            ordersBatch->orderkey[i],       \
            ordersBatch->custkey[i],        \
            ordersBatch->orderstatus[i],    \
            ordersBatch->totalprice[i],     \
            ordersBatch->orderdate[i],      \
            ordersBatch->orderpriority[i],  \
            ordersBatch->clerk[i],          \
            ordersBatch->shippriority[i],   \
            ordersBatch->comment[i]); }

    #define INSERT_PART {                   \
         data.on_insert_PART(               \
            partBatch->partkey[i],          \
            partBatch->name[i],             \
            partBatch->mfgr[i],             \
            partBatch->brand[i],            \
            partBatch->type[i],             \
            partBatch->psize[i],            \
            partBatch->container[i],        \
            partBatch->retailprice[i],      \
            partBatch->comment[i]); }

    #define INSERT_CUSTOMER {               \
        data.on_insert_CUSTOMER(            \
            customerBatch->custkey[i],      \
            customerBatch->name[i],         \
            customerBatch->address[i],      \
            customerBatch->nationkey[i],    \
            customerBatch->phone[i],        \
            customerBatch->acctbal[i],      \
            customerBatch->mktsegment[i],   \
            customerBatch->comment[i]); }

    #define INSERT_SUPPLIER {               \
        data.on_insert_SUPPLIER(            \
            supplierBatch->suppkey[i],      \
            supplierBatch->name[i],         \
            supplierBatch->address[i],      \
            supplierBatch->nationkey[i],    \
            supplierBatch->phone[i],        \
            supplierBatch->acctbal[i],      \
            supplierBatch->comment[i]); }

    #define INSERT_PARTSUPP {               \
        data.on_insert_PARTSUPP(            \
            partsuppBatch->partkey[i],      \
            partsuppBatch->suppkey[i],      \
            partsuppBatch->availqty[i],     \
            partsuppBatch->supplycost[i],   \
            partsuppBatch->comment[i]); }

    #define INSERT_NATION {                 \
        data.on_insert_NATION(              \
            nationBatch->nationkey[i],      \
            nationBatch->name[i],           \
            nationBatch->regionkey[i],      \
            nationBatch->comment[i]); }

    #define INSERT_REGION {                 \
        data.on_insert_REGION(              \
            regionBatch->regionkey[i],      \
            regionBatch->name[i],           \
            regionBatch->comment[i]); }


    void process_tables(dbtoaster::data_t& data) 
    {        
        size_t i = 0, count = 0;

        IF_REGION ({
            count = regionBatch->size;
            for (; i < count; i++) 
            {   
                IF_NATION ( INSERT_NATION )
                IF_REGION ( INSERT_REGION )
            }
        })
        
        IF_NATION ({
            count = nationBatch->size;
            for (; i < count; i++) 
            {
                IF_NATION ( INSERT_NATION )
            }
        })
    }

    void process_streams(dbtoaster::data_t& data)
    { 
        size_t i = 0, count = 0;

        IF_SUPPLIER ({
            count = supplierBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
                IF_PART ( INSERT_PART )
                IF_CUSTOMER ( INSERT_CUSTOMER )
                IF_SUPPLIER ( INSERT_SUPPLIER )
                IF_PARTSUPP ( INSERT_PARTSUPP )
            }
        })

        IF_CUSTOMER ({
            count = customerBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
                IF_PART ( INSERT_PART )
                IF_CUSTOMER ( INSERT_CUSTOMER )
                IF_PARTSUPP ( INSERT_PARTSUPP )
            }
        })

        IF_PART ({
            count = partBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
                IF_PART ( INSERT_PART )
                IF_PARTSUPP ( INSERT_PARTSUPP )
            }
        })

        IF_PARTSUPP ({
            count = partsuppBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
                IF_PARTSUPP ( INSERT_PARTSUPP )
            }
        })

        IF_ORDERS ({
            count = ordersBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
            }
        }) 

        IF_LINEITEM ({
            count = lineitemBatch->size;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
            }
        })
    }
#endif
}

#endif /* DBTOASTER_TEST_TEMPLATE_HPP */
