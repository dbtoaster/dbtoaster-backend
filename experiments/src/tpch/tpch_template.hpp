#ifndef DBTOASTER_TEST_TEMPLATE_HPP
#define DBTOASTER_TEST_TEMPLATE_HPP

#include "stopwatch.hpp"

const string dataPath = "datasets";
const string dataset = "5GB";

namespace dbtoaster 
{
    class data_t;

    class CSVAdaptor
    {
        public:
            CSVAdaptor(char del) : delimiter(del) { }

            std::string const& operator[](std::size_t index) const
            {
                return data[index];
            }

            std::size_t size() const
            {
                return data.size();
            }

            void readNextRow(std::istream& str)
            {
                data.clear();
        
                std::string line;
                std::getline(str, line);

                std::stringstream lineStream(line);
                std::string cell;

                while (std::getline(lineStream, cell, delimiter))
                {
                    data.push_back(cell);
                }
            }

            std::vector<std::string> data;

        private:
            char delimiter;
    };

    std::istream& operator>>(std::istream& str, CSVAdaptor& data)
    {
        data.readNextRow(str);
        return str;
    }   

    template <typename T>
    void readFromFile(std::vector<T>& data, const std::string& path, char delimiter)
    {            
        data.clear();
        
        std::ifstream file(path);

        CSVAdaptor row(delimiter);
        while (file >> row)
        {
            T tmp(row.data);
            data.push_back(tmp);
        }

        file.close();
    }

    template <typename T>
    void readFromBinaryFile(std::vector<T>& data, const std::string& path)
    {                        
        data.clear();

        std::ifstream file(path, std::ios::in | std::ios::binary);

        size_t length;
        file.read((char*) &length, sizeof(size_t));    
        data.reserve(length);

        T tmp;
        for (size_t i = 0; i < length; i++) 
        {
            tmp.readFrom(file);
            data.push_back(tmp);
        }

        file.close();
    }

    template <typename T>
    void writeToBinaryFile(std::vector<T>& data, const std::string& path)
    {
        std::ofstream file(path, std::ios::out | std::ios::binary);

        size_t length = data.size();
        file.write((char*) &length, sizeof(size_t));
        for (T t : data) t.writeTo(file);

        file.close();
    }

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

    IF_LINEITEM ( TPCHLineitemBatch* lineitemBatch; )
    IF_ORDERS ( TPCHOrdersBatch* ordersBatch; )
    IF_CUSTOMER ( TPCHCustomerBatch* customerBatch; )
    IF_PARTSUPP ( TPCHPartSuppBatch* partsuppBatch; )
    IF_PART ( TPCHPartBatch* partBatch; )    
    IF_SUPPLIER ( TPCHSupplierBatch* supplierBatch; )
    IF_NATION ( TPCHNationBatch* nationBatch; )
    IF_REGION ( TPCHRegionBatch* regionBatch; )

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
            partBatch->size[i],             \
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
            std::cout << "Loaded lineitem (" << lineitemBatch->length << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_ORDERS ({
            sw.restart();
            std::vector<TPCHOrders> orders;
            //readFromBinaryFile(orders, dataPath + "/" + dataset + "./orders.bin");
            readFromFile(orders, dataPath + "/" + dataset + "/orders.csv", '|');
            //writeToBinaryFile(orders, dataPath + "/" + dataset + "/orders.bin");
            ordersBatch = new TPCHOrdersBatch(orders);
            sw.stop();
            std::cout << "Loaded orders (" << ordersBatch->length << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_CUSTOMER ({
            sw.restart();
            std::vector<TPCHCustomer> customers;
            //readFromBinaryFile(customers, dataPath + "/" + dataset + "/customers.bin");
            readFromFile(customers, dataPath + "/" + dataset + "/customer.csv", '|');
            //writeToBinaryFile(customers, dataPath + "/" + dataset + "/customers.bin");
            customerBatch = new TPCHCustomerBatch(customers);            
            sw.stop();
            std::cout << "Loaded customer (" << customerBatch->length << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_PARTSUPP ({
            sw.restart();
            std::vector<TPCHPartSupp> partsupps;
            //readFromBinaryFile(customers, dataPath + "/" + dataset + "/partsupp.bin");
            readFromFile(partsupps, dataPath + "/" + dataset + "/partsupp.csv", '|');
            //writeToBinaryFile(customers, dataPath + "/" + dataset + "/partsupp.bin");
            partsuppBatch = new TPCHPartSuppBatch(partsupps);            
            sw.stop();
            std::cout << "Loaded partsupp (" << partsuppBatch->length << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_PART ({
            sw.restart();
            std::vector<TPCHPart> parts;
            //readFromBinaryFile(customers, dataPath + "/" + dataset + "/part.bin");
            readFromFile(parts, dataPath + "/" + dataset + "/part.csv", '|');
            //writeToBinaryFile(customers, dataPath + "/" + dataset + "/part.bin");
            partBatch = new TPCHPartBatch(parts);    
            sw.stop();
            std::cout << "Loaded part (" << partBatch->length << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_SUPPLIER ({
            sw.restart();
            std::vector<TPCHSupplier> suppliers;
            //readFromBinaryFile(customers, dataPath + "/" + dataset + "/supplier.bin");
            readFromFile(suppliers, dataPath + "/" + dataset + "/supplier.csv", '|');
            //writeToBinaryFile(customers, dataPath + "/" + dataset + "/supplier.bin");
            supplierBatch = new TPCHSupplierBatch(suppliers);
            sw.stop();
            std::cout << "Loaded supplier (" << supplierBatch->length << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_NATION ({
            std::vector<TPCHNation> nations;
            //readFromBinaryFile(customers, dataPath + "/" + dataset + "/nation.bin");
            readFromFile(nations, dataPath + "/" + dataset + "/nation.csv", '|');
            //writeToBinaryFile(customers, dataPath + "/" + dataset + "/nation.bin");
            nationBatch = new TPCHNationBatch(nations);
        })  

        IF_REGION ({
            std::vector<TPCHRegion> regions;
            //readFromBinaryFile(customers, dataPath + "/" + dataset + "/region.bin");
            readFromFile(regions, dataPath + "/" + dataset + "/region.csv", '|');
            //writeToBinaryFile(customers, dataPath + "/" + dataset + "/region.bin");
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

    void process_tables(dbtoaster::data_t& data) 
    {        
        size_t i = 0, count = 0;

        IF_REGION ({
            count = regionBatch->length;
            for (; i < count; i++) 
            {   
                IF_NATION ( INSERT_NATION )
                IF_REGION ( INSERT_REGION )
            }
        })
        
        IF_NATION ({
            count = nationBatch->length;
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
            count = supplierBatch->length;

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
            count = customerBatch->length;

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
            count = partBatch->length;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
                IF_PART ( INSERT_PART )
                IF_PARTSUPP ( INSERT_PARTSUPP )
            }
        })

        IF_PARTSUPP ({
            count = partsuppBatch->length;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
                IF_PARTSUPP ( INSERT_PARTSUPP )
            }
        })

        IF_ORDERS ({
            count = ordersBatch->length;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
                IF_ORDERS ( INSERT_ORDERS )
            }
        }) 

        IF_LINEITEM ({
            count = lineitemBatch->length;

            for (; i < count; i++) 
            {
                IF_LINEITEM ( INSERT_LINEITEM )
            }
        })
    }
}

#endif /* DBTOASTER_TEST_TEMPLATE_HPP */
