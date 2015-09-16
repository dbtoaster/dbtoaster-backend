#ifndef DBTOASTER_TEST_TPCH_HPP
#define DBTOASTER_TEST_TPCH_HPP

#include "../types.hpp"
#include "../serialization.hpp"

namespace dbtoaster 
{
    struct TPCHLineitem
    {
        long orderkey;
        long partkey;
        long suppkey;
        long linenumber;
        DOUBLE_TYPE quantity;
        DOUBLE_TYPE extendedprice;
        DOUBLE_TYPE discount;
        DOUBLE_TYPE tax;
        STRING_TYPE returnflag;
        STRING_TYPE linestatus;
        date shipdate;
        date commitdate;
        date receiptdate;
        STRING_TYPE shipinstruct;
        STRING_TYPE shipmode;
        STRING_TYPE comment;

        TPCHLineitem() { }

        TPCHLineitem(std::vector<std::string>& fields)
        {
            if (fields.size() < 16) return;
            orderkey = std::stol(fields[0]);
            partkey = std::stol(fields[1]);
            suppkey = std::stol(fields[2]);
            linenumber = std::stol(fields[3]);
            quantity = std::stod(fields[4]);
            extendedprice = std::stod(fields[5]);
            discount = std::stod(fields[6]);
            tax = std::stod(fields[7]);
            returnflag = fields[8];
            linestatus = fields[9];
            shipdate = str2date(fields[10]);
            commitdate = str2date(fields[11]);
            receiptdate = str2date(fields[12]);
            shipinstruct = fields[13];
            shipmode = fields[14];
            comment = fields[15];
        }

        void writeTo(std::ostream& o)
        {
            write(o, orderkey);
            write(o, partkey);
            write(o, suppkey);
            write(o, linenumber);
            write(o, quantity);
            write(o, extendedprice);
            write(o, discount);
            write(o, tax);
            write(o, returnflag);
            write(o, linestatus);
            write(o, shipdate);
            write(o, commitdate);
            write(o, receiptdate);
            write(o, shipinstruct);
            write(o, shipmode);
            write(o, comment);
        }

        void readFrom(std::istream& i)
        {
            read(i, orderkey);
            read(i, partkey);
            read(i, suppkey);
            read(i, linenumber);
            read(i, quantity);
            read(i, extendedprice);
            read(i, discount);
            read(i, tax);
            read(i, returnflag);
            read(i, linestatus);
            read(i, shipdate);
            read(i, commitdate);
            read(i, receiptdate);
            read(i, shipinstruct);
            read(i, shipmode);
            read(i, comment);
        }
    };

    struct TPCHOrders
    {
        long orderkey;
        long custkey;
        STRING_TYPE orderstatus;
        DOUBLE_TYPE totalprice;
        date orderdate;
        STRING_TYPE orderpriority;
        STRING_TYPE clerk;
        long shippriority;
        STRING_TYPE comment;

        TPCHOrders() { }

        TPCHOrders(std::vector<std::string>& fields) 
        {
            if (fields.size() < 9) return;
            orderkey = std::stol(fields[0]);
            custkey = std::stol(fields[1]);
            orderstatus = fields[2];
            totalprice = std::stod(fields[3]);
            orderdate = str2date(fields[4]);
            orderpriority = fields[5];
            clerk = fields[6];
            shippriority = std::stol(fields[7]);
            comment = fields[8];
        }

        void writeTo(std::ostream& o)
        {
            write(o, orderkey);
            write(o, custkey);
            write(o, orderstatus);
            write(o, totalprice);
            write(o, orderdate);
            write(o, orderpriority);
            write(o, clerk);
            write(o, shippriority);
            write(o, comment);
        }

        void readFrom(std::istream& i)
        {
            read(i, orderkey);
            read(i, custkey);
            read(i, orderstatus);
            read(i, totalprice);
            read(i, orderdate);
            read(i, orderpriority);
            read(i, clerk);
            read(i, shippriority);
            read(i, comment);
        }
    };

    struct TPCHCustomer
    {
        long custkey;
        STRING_TYPE name;
        STRING_TYPE address;
        long nationkey;
        STRING_TYPE phone;
        DOUBLE_TYPE acctbal;
        STRING_TYPE mktsegment;
        STRING_TYPE comment;

        TPCHCustomer() { }

        TPCHCustomer(std::vector<std::string>& fields) 
        {
            if (fields.size() < 8) return;        
            custkey = std::stol(fields[0]);
            name = fields[1];
            address = fields[2];
            nationkey = std::stol(fields[3]);
            phone = fields[4];
            acctbal = std::stod(fields[5]);
            mktsegment = fields[6];
            comment = fields[7];
        }

        void writeTo(std::ostream& o)
        {
            write(o, custkey);
            write(o, name);
            write(o, address);
            write(o, nationkey);
            write(o, phone);
            write(o, acctbal);
            write(o, mktsegment);
            write(o, comment);
        }

        void readFrom(std::istream& i) 
        {
            read(i, custkey);
            read(i, name);
            read(i, address);
            read(i, nationkey);
            read(i, phone);
            read(i, acctbal);
            read(i, mktsegment);
            read(i, comment);
        }
    };

    struct TPCHPartSupp
    {
        long partkey;
        long suppkey;
        long availqty;
        DOUBLE_TYPE supplycost;
        STRING_TYPE comment;

        TPCHPartSupp() { }

        TPCHPartSupp(std::vector<std::string>& fields)
        {
            if (fields.size() < 5) return;
            partkey = std::stol(fields[0]);
            suppkey = std::stol(fields[1]);
            availqty = std::stol(fields[2]);
            supplycost = std::stod(fields[3]);
            comment = fields[4];
        }

        void writeTo(std::ostream& o)
        {
            write(o, partkey);
            write(o, suppkey);
            write(o, availqty);
            write(o, supplycost);
            write(o, comment);
        }

        void readFrom(std::istream& i)
        {
            read(i, partkey);
            read(i, suppkey);
            read(i, availqty);
            read(i, supplycost);
            read(i, comment);
        }
    };

    struct TPCHPart
    {
        long partkey;
        STRING_TYPE name;
        STRING_TYPE mfgr;
        STRING_TYPE brand;
        STRING_TYPE type;
        long size;
        STRING_TYPE container;
        DOUBLE_TYPE retailprice;
        STRING_TYPE comment;

        TPCHPart() { }

        TPCHPart(std::vector<std::string>& fields)
        {
            if (fields.size() < 9) return;
            partkey = std::stol(fields[0]);
            name = fields[1];
            mfgr = fields[2];
            brand = fields[3];
            type = fields[4];
            size = std::stol(fields[5]);
            container = fields[6];
            retailprice = std::stod(fields[7]);
            comment = fields[8];
        }

        void writeTo(std::ostream& o)
        {
            write(o, partkey);
            write(o, name);
            write(o, mfgr);
            write(o, brand);
            write(o, type);
            write(o, size);
            write(o, container);
            write(o, retailprice);
            write(o, comment);
        }

        void readFrom(std::istream& i)
        {
            read(i, partkey);
            read(i, name);
            read(i, mfgr);
            read(i, brand);
            read(i, type);
            read(i, size);
            read(i, container);
            read(i, retailprice);
            read(i, comment);
        }
    };

    struct TPCHSupplier
    {
        long suppkey;
        STRING_TYPE name;
        STRING_TYPE address;
        long nationkey;
        STRING_TYPE phone;
        DOUBLE_TYPE acctbal;
        STRING_TYPE comment;

        TPCHSupplier() { }

        TPCHSupplier(std::vector<std::string>& fields)
        {
            if (fields.size() < 7) return;
            suppkey = std::stol(fields[0]);
            name = fields[1];
            address = fields[2];        
            nationkey = std::stol(fields[3]);
            phone = fields[4];
            acctbal = std::stod(fields[5]);        
            comment = fields[6];
        }

        void writeTo(std::ostream& o)
        {
            write(o, suppkey);
            write(o, name);
            write(o, address);
            write(o, nationkey);
            write(o, phone);
            write(o, acctbal);
            write(o, comment);
        }

        void readFrom(std::istream& i)
        {
            read(i, suppkey);
            read(i, name);
            read(i, address);
            read(i, nationkey);
            read(i, phone);
            read(i, acctbal);
            read(i, comment);
        }
    };

    struct TPCHNation
    {
        long nationkey;
        STRING_TYPE name;
        long regionkey;
        STRING_TYPE comment;

        TPCHNation() { }

        TPCHNation(std::vector<std::string>& fields)
        {
            if (fields.size() < 4) return;
            nationkey = std::stol(fields[0]);
            name = fields[1];
            regionkey = std::stol(fields[2]);
            comment = fields[3];
        }

        void writeTo(std::ostream& o)
        {
            write(o, nationkey);
            write(o, name);
            write(o, regionkey);
            write(o, comment);
        }

        void readFrom(std::istream& i)
        {
            read(i, nationkey);
            read(i, name);
            read(i, regionkey);
            read(i, comment);
        }
    };

    struct TPCHRegion
    {
        long regionkey;
        STRING_TYPE name;
        STRING_TYPE comment;

        TPCHRegion() { }

        TPCHRegion(std::vector<std::string>& fields)
        {
            if (fields.size() < 3) return;
            regionkey = std::stol(fields[0]);
            name = fields[1];
            comment = fields[2];
        }

        void writeTo(std::ostream& o)
        {
            write(o, regionkey);
            write(o, name);
            write(o, comment);
        }

        void readFrom(std::istream& i)
        {
            read(i, regionkey);
            read(i, name);
            read(i, comment);
        }
    };
    struct TPCHLineitemBatch
    {
        size_t length;
        long* orderkey;
        long* partkey;
        long* suppkey;
        long* linenumber;
        DOUBLE_TYPE* quantity;
        DOUBLE_TYPE* extendedprice;
        DOUBLE_TYPE* discount;
        DOUBLE_TYPE* tax;
        STRING_TYPE* returnflag;
        STRING_TYPE* linestatus;
        DATE_TYPE* shipdate;
        DATE_TYPE* commitdate;
        DATE_TYPE* receiptdate;
        STRING_TYPE* shipinstruct;
        STRING_TYPE* shipmode;
        STRING_TYPE* comment;

        TPCHLineitemBatch() : length(0) { }

        TPCHLineitemBatch(std::vector<TPCHLineitem>& lineitems)
        {
            length = lineitems.size();
            orderkey = new long[length];
            partkey = new long[length];
            suppkey = new long[length];
            linenumber = new long[length];
            quantity = new DOUBLE_TYPE[length];
            extendedprice = new DOUBLE_TYPE[length];
            discount = new DOUBLE_TYPE[length];
            tax = new DOUBLE_TYPE[length];
            returnflag = new STRING_TYPE[length]();
            linestatus = new STRING_TYPE[length]();
            shipdate = new DATE_TYPE[length];
            commitdate = new DATE_TYPE[length];
            receiptdate = new DATE_TYPE[length];
            shipinstruct = new STRING_TYPE[length]();
            shipmode = new STRING_TYPE[length]();
            comment = new STRING_TYPE[length]();

            for (size_t i = 0; i < length; i++)
            {
                orderkey[i] = lineitems[i].orderkey;
                partkey[i] = lineitems[i].partkey;
                suppkey[i] = lineitems[i].suppkey;
                linenumber[i] = lineitems[i].linenumber;
                quantity[i] = lineitems[i].quantity;
                extendedprice[i] = lineitems[i].extendedprice;
                discount[i] = lineitems[i].discount;
                tax[i] = lineitems[i].tax;
                returnflag[i] = lineitems[i].returnflag;
                linestatus[i] = lineitems[i].linestatus;
                shipdate[i] = lineitems[i].shipdate;
                commitdate[i] = lineitems[i].commitdate;
                receiptdate[i] = lineitems[i].receiptdate;
                shipinstruct[i] = lineitems[i].shipinstruct;
                shipmode[i] = lineitems[i].shipmode;
                comment[i] = lineitems[i].comment;
            }
        }

        ~TPCHLineitemBatch()
        {
            delete[] orderkey;
            delete[] partkey;
            delete[] suppkey;
            delete[] linenumber;
            delete[] quantity;
            delete[] extendedprice;
            delete[] discount;
            delete[] tax;
            delete[] returnflag;
            delete[] linestatus;
            delete[] shipdate;
            delete[] commitdate;
            delete[] receiptdate;
            delete[] shipinstruct;
            delete[] shipmode;
            delete[] comment;
        }
    };

    struct TPCHOrdersBatch
    {
        size_t length;
        long* orderkey;
        long* custkey;
        STRING_TYPE* orderstatus;
        DOUBLE_TYPE* totalprice;
        DATE_TYPE* orderdate;
        STRING_TYPE* orderpriority;
        STRING_TYPE* clerk;
        long* shippriority;
        STRING_TYPE* comment;

        TPCHOrdersBatch() : length(0) { }

        TPCHOrdersBatch(std::vector<TPCHOrders>& orders)
        {
            length = orders.size();
            orderkey = new long[length];
            custkey = new long[length];
            orderstatus = new STRING_TYPE[length];
            totalprice = new DOUBLE_TYPE[length];
            orderdate = new DATE_TYPE[length];
            orderpriority = new STRING_TYPE[length];
            clerk = new STRING_TYPE[length];
            shippriority = new long[length];
            comment = new STRING_TYPE[length];

            for (size_t i = 0; i < length; i++)
            {
                orderkey[i] = orders[i].orderkey;
                custkey[i] = orders[i].custkey;
                orderstatus[i] = orders[i].orderstatus;
                totalprice[i] = orders[i].totalprice;
                orderdate[i] = orders[i].orderdate;
                orderpriority[i] = orders[i].orderpriority;
                clerk[i] = orders[i].clerk;
                shippriority[i] = orders[i].shippriority;
                comment[i] = orders[i].comment;
            }
        }
        ~TPCHOrdersBatch()
        {
            delete[] orderkey;
            delete[] custkey;
            delete[] orderstatus;
            delete[] totalprice;
            delete[] orderdate;
            delete[] orderpriority;
            delete[] clerk;
            delete[] shippriority;
            delete[] comment;
        }
    };

    struct TPCHCustomerBatch
    {
        size_t length;
        long* custkey;
        STRING_TYPE* name;
        STRING_TYPE* address;
        long* nationkey;
        STRING_TYPE* phone;
        DOUBLE_TYPE* acctbal;
        STRING_TYPE* mktsegment;
        STRING_TYPE* comment;

        TPCHCustomerBatch() : length(0) { }

        TPCHCustomerBatch(std::vector<TPCHCustomer>& customers)
        {
            length = customers.size();
            custkey = new long[length];
            name = new STRING_TYPE[length];
            address  = new STRING_TYPE[length];
            nationkey = new long[length];
            phone = new STRING_TYPE[length];
            acctbal = new DOUBLE_TYPE[length];
            mktsegment = new STRING_TYPE[length];
            comment = new STRING_TYPE[length];

            for (size_t i = 0; i < length; i++)
            {
                custkey[i] = customers[i].custkey;
                name[i] = customers[i].name;
                address[i] = customers[i].address;
                nationkey[i] = customers[i].nationkey;
                phone[i] = customers[i].phone;
                acctbal[i] = customers[i].acctbal;
                mktsegment[i] = customers[i].mktsegment;
                comment[i] = customers[i].comment;
            }
        }

        ~TPCHCustomerBatch()
        {
            delete[] custkey;
            delete[] name;
            delete[] address;
            delete[] nationkey;
            delete[] phone;
            delete[] acctbal;
            delete[] mktsegment;
            delete[] comment;
        }
    };

    struct TPCHPartSuppBatch
    {
        size_t length;
        long* partkey;
        long* suppkey;
        long* availqty;
        DOUBLE_TYPE* supplycost;
        STRING_TYPE* comment;

        TPCHPartSuppBatch() : length(0) { }

        TPCHPartSuppBatch(std::vector<TPCHPartSupp>& partsupps)
        {
            length = partsupps.size();
            partkey = new long[length];
            suppkey = new long[length];
            availqty = new long[length];
            supplycost = new DOUBLE_TYPE[length];
            comment = new STRING_TYPE[length];

            for (size_t i = 0; i < length; i++)
            {
                partkey[i] = partsupps[i].partkey;
                suppkey[i] = partsupps[i].suppkey;
                availqty[i] = partsupps[i].availqty;
                supplycost[i] = partsupps[i].supplycost;
                comment[i] = partsupps[i].comment;
            }
        }

        ~TPCHPartSuppBatch()
        {
            delete[] partkey;
            delete[] suppkey;
            delete[] availqty;
            delete[] supplycost;
            delete[] comment;
        }
    };

    struct TPCHPartBatch
    {
        size_t length;
        long* partkey;
        STRING_TYPE* name;
        STRING_TYPE* mfgr;
        STRING_TYPE* brand;
        STRING_TYPE* type;
        long* size;
        STRING_TYPE* container;
        DOUBLE_TYPE* retailprice;
        STRING_TYPE* comment;

        TPCHPartBatch() : length(0) { }

        TPCHPartBatch(std::vector<TPCHPart>& parts)
        {
            length = parts.size();
            partkey = new long[length];
            name = new STRING_TYPE[length];
            mfgr = new STRING_TYPE[length];
            brand = new STRING_TYPE[length];
            type = new STRING_TYPE[length];
            size = new long[length];
            container = new STRING_TYPE[length];
            retailprice = new DOUBLE_TYPE[length];
            comment = new STRING_TYPE[length];

            for (size_t i = 0; i < length; i++)
            {
                partkey[i] = parts[i].partkey;
                name[i] = parts[i].name;
                mfgr[i] = parts[i].mfgr;
                brand[i] = parts[i].brand;
                type[i] = parts[i].type;
                size[i] = parts[i].size;
                container[i] = parts[i].container;
                retailprice[i] = parts[i].retailprice;
                comment[i] = parts[i].comment;
            }
        }

        ~TPCHPartBatch()
        {
            delete[] partkey;
            delete[] name;
            delete[] mfgr;
            delete[] brand;
            delete[] type;
            delete[] size;
            delete[] container;
            delete[] retailprice;
            delete[] comment;
        }
    };

    struct TPCHSupplierBatch
    {
        size_t length;
        long* suppkey;
        STRING_TYPE* name;
        STRING_TYPE* address;
        long* nationkey;
        STRING_TYPE* phone;
        DOUBLE_TYPE* acctbal;
        STRING_TYPE* comment;

        TPCHSupplierBatch() : length(0) { }

        TPCHSupplierBatch(std::vector<TPCHSupplier>& suppliers)
        {
            length = suppliers.size();
            suppkey = new long[length];
            name = new STRING_TYPE[length];
            address = new STRING_TYPE[length];
            nationkey = new long[length];
            phone = new STRING_TYPE[length];
            acctbal = new DOUBLE_TYPE[length];
            comment = new STRING_TYPE[length];

            for (size_t i = 0; i < length; i++)
            {
                suppkey[i] = suppliers[i].suppkey;
                name[i] = suppliers[i].name;
                address[i] = suppliers[i].address;
                nationkey[i] = suppliers[i].nationkey;
                phone[i] = suppliers[i].phone;
                acctbal[i] = suppliers[i].acctbal;
                comment[i] = suppliers[i].comment;
            }
        }

        ~TPCHSupplierBatch()
        {
            delete[] suppkey;
            delete[] name;
            delete[] address;
            delete[] nationkey;
            delete[] phone;
            delete[] acctbal;
            delete[] comment;
        }  
    };

    struct TPCHNationBatch
    {
        size_t length;
        long* nationkey;
        STRING_TYPE* name;
        long* regionkey;
        STRING_TYPE* comment;

        TPCHNationBatch() : length(0) { }

        TPCHNationBatch(std::vector<TPCHNation>& nations)
        {
            length = nations.size();
            nationkey = new long[length];
            name = new STRING_TYPE[length];
            regionkey = new long[length];
            comment = new STRING_TYPE[length];

            for (size_t i = 0; i < length; i++)
            {
                nationkey[i] = nations[i].nationkey;
                name[i] = nations[i].name;
                regionkey[i] = nations[i].regionkey;
                comment[i] = nations[i].comment;
            }
        }

        ~TPCHNationBatch()
        {
            delete[] nationkey;
            delete[] name;
            delete[] regionkey;
            delete[] comment;
        }
    };

    struct TPCHRegionBatch
    {
        size_t length;
        long* regionkey;
        STRING_TYPE* name;
        STRING_TYPE* comment;

        TPCHRegionBatch() : length(0) { }

        TPCHRegionBatch(std::vector<TPCHRegion>& regions)
        {
            length = regions.size();
            regionkey = new long[length];
            name = new STRING_TYPE[length];
            comment = new STRING_TYPE[length];

            for (size_t i = 0; i < length; i++)
            {
                regionkey[i] = regions[i].regionkey;
                name[i] = regions[i].name;
                comment[i] = regions[i].comment;
            }
        }

        ~TPCHRegionBatch()
        {
            delete[] regionkey;
            delete[] name;
            delete[] comment;
        }
    };
}

#endif /* DBTOASTER_TEST_TPCH_HPP */
