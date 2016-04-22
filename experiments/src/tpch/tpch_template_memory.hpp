#ifndef DBTOASTER_TEST_MEMORY_TEMPLATE_HPP
#define DBTOASTER_TEST_MEMORY_TEMPLATE_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

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

    class CSVReader
    {
        private:
            std::ifstream ifs;
            char delimiter;

        public:
            std::vector<std::string> data;

            CSVReader(const std::string path, char del) : delimiter(del) 
            { 
                ifs.open(path.c_str(), std::ifstream::in);
            }

            ~CSVReader() 
            { 
                data.clear();
                ifs.close();
            }

            bool hasMore() 
            {
                return ifs.good() && !ifs.eof();
            }

            void readNextRow()
            {
                assert(hasMore());
                
                data.clear();

                std::string line;
                std::getline(ifs, line);

                std::string cell;
                std::stringstream ls(line);
                while (std::getline(ls, cell, delimiter))
                {
                    data.push_back(cell);
                }
            }
    };


    IF_LINEITEM ( CSVReader lineitemReader(dataPath + "/" + dataset + "/lineitem.csv", '|'); )
    IF_ORDERS ( CSVReader ordersReader(dataPath + "/" + dataset + "/orders.csv", '|'); )
    IF_CUSTOMER ( CSVReader customerReader(dataPath + "/" + dataset + "/customer.csv", '|'); )
    IF_PARTSUPP ( CSVReader partsuppReader(dataPath + "/" + dataset + "/partsupp.csv", '|'); )
    IF_PART ( CSVReader partReader(dataPath + "/" + dataset + "/part.csv", '|'); )    
    IF_SUPPLIER ( CSVReader supplierReader(dataPath + "/" + dataset + "/supplier.csv", '|'); )
    IF_NATION ( CSVReader nationReader(dataPath + "/" + dataset + "/nation.csv", '|'); )
    IF_REGION ( CSVReader regionReader(dataPath + "/" + dataset + "/region.csv", '|'); )

    #define INSERT_LINEITEM {                                   \
        if (lineitemReader.hasMore())                           \
        {                                                       \
            lineitemReader.readNextRow();                       \
            if (lineitemReader.data.size() > 0) {               \
                consumedSources++;                              \
                data.on_insert_LINEITEM(                        \
                    std::stol(lineitemReader.data[0]),          \
                    std::stol(lineitemReader.data[1]),          \
                    std::stol(lineitemReader.data[2]),          \
                    std::stol(lineitemReader.data[3]),          \
                    std::stod(lineitemReader.data[4]),          \
                    std::stod(lineitemReader.data[5]),          \
                    std::stod(lineitemReader.data[6]),          \
                    std::stod(lineitemReader.data[7]),          \
                    lineitemReader.data[8],                     \
                    lineitemReader.data[9],                     \
                    str2date(lineitemReader.data[10]),          \
                    str2date(lineitemReader.data[11]),          \
                    str2date(lineitemReader.data[12]),          \
                    lineitemReader.data[13],                    \
                    lineitemReader.data[14],                    \
                    lineitemReader.data[15]                     \
                );                                              \
            }                                                   \
        }                                                       \
    }

    #define INSERT_ORDERS {                                   \
        if (ordersReader.hasMore())                           \
        {                                                     \
            ordersReader.readNextRow();                       \
            if (ordersReader.data.size() > 0) {               \
                consumedSources++;                            \
                data.on_insert_ORDERS(                        \
                    std::stol(ordersReader.data[0]),          \
                    std::stol(ordersReader.data[1]),          \
                    ordersReader.data[2],                     \
                    std::stod(ordersReader.data[3]),          \
                    str2date(ordersReader.data[4]),           \
                    ordersReader.data[5],                     \
                    ordersReader.data[6],                     \
                    std::stol(ordersReader.data[7]),          \
                    ordersReader.data[8]                      \
                );                                            \
            }                                                 \
        }                                                     \
    }

    #define INSERT_CUSTOMER {                                   \
        if (customerReader.hasMore())                           \
        {                                                       \
            customerReader.readNextRow();                       \
            if (customerReader.data.size() > 0) {               \
                consumedSources++;                              \
                data.on_insert_CUSTOMER(                        \
                    std::stol(customerReader.data[0]),          \
                    customerReader.data[1],                     \
                    customerReader.data[2],                     \
                    std::stol(customerReader.data[3]),          \
                    customerReader.data[4],                     \
                    std::stod(customerReader.data[5]),          \
                    customerReader.data[6],                     \
                    customerReader.data[7]                      \
                );                                              \
            }                                                   \
        }                                                       \
    }

    #define INSERT_PART {                                       \
        if (partReader.hasMore())                               \
        {                                                       \
            partReader.readNextRow();                           \
            if (partReader.data.size() > 0) {                   \
                consumedSources++;                              \
                data.on_insert_PART(                            \
                    std::stol(partReader.data[0]),              \
                    partReader.data[1],                         \
                    partReader.data[2],                         \
                    partReader.data[3],                         \
                    partReader.data[4],                         \
                    std::stol(partReader.data[5]),              \
                    partReader.data[6],                         \
                    std::stod(partReader.data[7]),              \
                    partReader.data[8]                          \
                );                                              \
            }                                                   \
        }                                                       \
    }

    #define INSERT_PARTSUPP {                                   \
        if (partsuppReader.hasMore())                           \
        {                                                       \
            partsuppReader.readNextRow();                       \
            if (partsuppReader.data.size() > 0) {               \
                consumedSources++;                              \
                data.on_insert_PARTSUPP(                        \
                    std::stol(partsuppReader.data[0]),          \
                    std::stol(partsuppReader.data[1]),          \
                    std::stol(partsuppReader.data[2]),          \
                    std::stod(partsuppReader.data[3]),          \
                    partsuppReader.data[4]                      \
                );                                              \
            }                                                   \
        }                                                       \
    }

    #define INSERT_SUPPLIER {                                   \
        if (supplierReader.hasMore())                           \
        {                                                       \
            supplierReader.readNextRow();                       \
            if (supplierReader.data.size() > 0) {               \
                consumedSources++;                              \
                data.on_insert_SUPPLIER(                        \
                    std::stol(supplierReader.data[0]),          \
                    supplierReader.data[1],                     \
                    supplierReader.data[2],                     \
                    std::stol(supplierReader.data[3]),          \
                    supplierReader.data[4],                     \
                    std::stod(supplierReader.data[5]),          \
                    supplierReader.data[6]                      \
                );                                              \
            }                                                   \
        }                                                       \
    }

    #define INSERT_NATION {                                     \
        if (nationReader.hasMore())                             \
        {                                                       \
            nationReader.readNextRow();                         \
            if (nationReader.data.size() > 0) {                 \
                consumedSources++;                              \
                data.on_insert_NATION(                          \
                    std::stol(nationReader.data[0]),            \
                    nationReader.data[1],                       \
                    std::stol(nationReader.data[2]),            \
                    nationReader.data[3]                        \
                );                                              \
            }                                                   \
        }                                                       \
    }

    #define INSERT_REGION {                                     \
        if (regionReader.hasMore())                             \
        {                                                       \
            regionReader.readNextRow();                         \
            if (regionReader.data.size() > 0) {                 \
                consumedSources++;                              \
                data.on_insert_REGION(                          \
                    std::stol(regionReader.data[0]),            \
                    regionReader.data[1],                       \
                    regionReader.data[2]                        \
                );                                              \
            }                                                   \
        }                                                       \
    }

    void load_relations() { }

    void destroy_relations() { }   

    void process_tables(dbtoaster::data_t& data) 
    {       
        int consumedSources; 
        do 
        {
            consumedSources = 0;
            IF_NATION ( INSERT_NATION )
            IF_REGION ( INSERT_REGION )
        }
        while (consumedSources != 0);
    }

    void process_streams(dbtoaster::data_t& data) 
    {      
        int consumedSources;   
        do 
        {
            consumedSources = 0;
            IF_LINEITEM ( INSERT_LINEITEM )
            IF_ORDERS ( INSERT_ORDERS )
            IF_PART ( INSERT_PART )
            IF_CUSTOMER ( INSERT_CUSTOMER )
            IF_SUPPLIER ( INSERT_SUPPLIER )
            IF_PARTSUPP ( INSERT_PARTSUPP )
        }
        while (consumedSources != 0);
    }

}

#endif /* DBTOASTER_TEST_MEMORY_TEMPLATE_HPP */
