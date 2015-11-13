#ifndef DBTOASTER_TEST_TPCH_HPP
#define DBTOASTER_TEST_TPCH_HPP

#include <vector>
#include "types.hpp"
#include "serialization.hpp"

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
        size_t size;
        size_t capacity;
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

        //TPCHLineitemBatch() : size(0), capacity(0) { }

        TPCHLineitemBatch(size_t c) { initCapacity(c); }            

        TPCHLineitemBatch(const TPCHLineitemBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                orderkey[i] = batch.orderkey[i];
                partkey[i] = batch.partkey[i];
                suppkey[i] = batch.suppkey[i];
                linenumber[i] = batch.linenumber[i];
                quantity[i] = batch.quantity[i];
                extendedprice[i] = batch.extendedprice[i];
                discount[i] = batch.discount[i];
                tax[i] = batch.tax[i];
                returnflag[i] = batch.returnflag[i];
                linestatus[i] = batch.linestatus[i];
                shipdate[i] = batch.shipdate[i];
                commitdate[i] = batch.commitdate[i];
                receiptdate[i] = batch.receiptdate[i];
                shipinstruct[i] = batch.shipinstruct[i];
                shipmode[i] = batch.shipmode[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHLineitemBatch(std::vector<TPCHLineitem>& lineitems)
        {
            initCapacity(lineitems.size());            
            size = lineitems.size();

            for (size_t i = 0; i < lineitems.size(); i++)
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

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;
            orderkey = new long[capacity]();
            partkey = new long[capacity]();
            suppkey = new long[capacity]();
            linenumber = new long[capacity]();
            quantity = new DOUBLE_TYPE[capacity]();
            extendedprice = new DOUBLE_TYPE[capacity]();
            discount = new DOUBLE_TYPE[capacity]();
            tax = new DOUBLE_TYPE[capacity]();
            returnflag = new STRING_TYPE[capacity]();
            linestatus = new STRING_TYPE[capacity]();
            shipdate = new DATE_TYPE[capacity]();
            commitdate = new DATE_TYPE[capacity]();
            receiptdate = new DATE_TYPE[capacity]();
            shipinstruct = new STRING_TYPE[capacity]();
            shipmode = new STRING_TYPE[capacity]();
            comment = new STRING_TYPE[capacity]();     
        }

        void add(long _orderkey, long _partkey, long _suppkey, long _linenumber, DOUBLE_TYPE _quantity, DOUBLE_TYPE _extendedprice, DOUBLE_TYPE _discount, DOUBLE_TYPE _tax, STRING_TYPE _returnflag, STRING_TYPE _linestatus, DATE_TYPE _shipdate, DATE_TYPE _commitdate, DATE_TYPE _receiptdate, STRING_TYPE _shipinstruct, STRING_TYPE _shipmode, STRING_TYPE _comment)
        {            
            assert(size < capacity);
            orderkey[size] = _orderkey;
            partkey[size] = _partkey;
            suppkey[size] = _suppkey;
            linenumber[size] = _linenumber;
            quantity[size] = _quantity;
            extendedprice[size] = _extendedprice;
            discount[size] = _discount;
            tax[size] = _tax;
            returnflag[size] = _returnflag;
            linestatus[size] = _linestatus;
            shipdate[size] = _shipdate;
            commitdate[size] = _commitdate;
            receiptdate[size] = _receiptdate;
            shipinstruct[size] = _shipinstruct;
            shipmode[size] = _shipmode;
            comment[size] = _comment;
            size++;
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
        size_t size;
        size_t capacity;
        long* orderkey;
        long* custkey;
        STRING_TYPE* orderstatus;
        DOUBLE_TYPE* totalprice;
        DATE_TYPE* orderdate;
        STRING_TYPE* orderpriority;
        STRING_TYPE* clerk;
        long* shippriority;
        STRING_TYPE* comment;

        TPCHOrdersBatch() : size(0), capacity(0) { }

        TPCHOrdersBatch(size_t c) { initCapacity(c); }

        TPCHOrdersBatch(const TPCHOrdersBatch& batch)
        {
            initCapacity(batch.size);
            size = batch.size;
            
            for (size_t i = 0; i < batch.size; i++)
            {
                orderkey[i] = batch.orderkey[i];
                custkey[i] = batch.custkey[i];
                orderstatus[i] = batch.orderstatus[i];
                totalprice[i] = batch.totalprice[i];
                orderdate[i] = batch.orderdate[i];
                orderpriority[i] = batch.orderpriority[i];
                clerk[i] = batch.clerk[i];
                shippriority[i] = batch.shippriority[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHOrdersBatch(std::vector<TPCHOrders>& orders)
        {
            initCapacity(orders.size());
            size = orders.size();
            
            for (size_t i = 0; i < orders.size(); i++)
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

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;
            orderkey = new long[capacity]();
            custkey = new long[capacity]();
            orderstatus = new STRING_TYPE[capacity]();
            totalprice = new DOUBLE_TYPE[capacity]();
            orderdate = new DATE_TYPE[capacity]();
            orderpriority = new STRING_TYPE[capacity]();
            clerk = new STRING_TYPE[capacity]();
            shippriority = new long[capacity]();
            comment = new STRING_TYPE[capacity]();
        }

        void add(long _orderkey, long _custkey, STRING_TYPE _orderstatus, DOUBLE_TYPE _totalprice, DATE_TYPE _orderdate, STRING_TYPE _orderpriority, STRING_TYPE _clerk, long _shippriority,         STRING_TYPE _comment) 
        {            
            assert(size < capacity);
            orderkey[size] = _orderkey;
            custkey[size] = _custkey;
            orderstatus[size] = _orderstatus;
            totalprice[size] = _totalprice;
            orderdate[size] = _orderdate;
            orderpriority[size] = _orderpriority;
            clerk[size] = _clerk;
            shippriority[size] = _shippriority;
            comment[size] = _comment;
            size++;
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
        size_t size;
        size_t capacity;
        long* custkey;
        STRING_TYPE* name;
        STRING_TYPE* address;
        long* nationkey;
        STRING_TYPE* phone;
        DOUBLE_TYPE* acctbal;
        STRING_TYPE* mktsegment;
        STRING_TYPE* comment;

        //TPCHCustomerBatch() : size(0), capacity(0) { }

        TPCHCustomerBatch(size_t c) { initCapacity(c); }
        
        TPCHCustomerBatch(const TPCHCustomerBatch& batch)
        {
            initCapacity(batch.size);
            size = batch.size;
            
            for (size_t i = 0; i < batch.size; i++)
            {
                custkey[i] = batch.custkey[i];
                name[i] = batch.name[i];
                address[i] = batch.address[i];
                nationkey[i] = batch.nationkey[i];
                phone[i] = batch.phone[i];
                acctbal[i] = batch.acctbal[i];
                mktsegment[i] = batch.mktsegment[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHCustomerBatch(std::vector<TPCHCustomer>& customers)
        {
            initCapacity(customers.size());
            size = customers.size();

            for (size_t i = 0; i < customers.size(); i++)
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

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;
            custkey = new long[capacity]();
            name = new STRING_TYPE[capacity]();
            address  = new STRING_TYPE[capacity]();
            nationkey = new long[capacity]();
            phone = new STRING_TYPE[capacity]();
            acctbal = new DOUBLE_TYPE[capacity]();
            mktsegment = new STRING_TYPE[capacity]();
            comment = new STRING_TYPE[capacity]();
        }

        void add(long _custkey, STRING_TYPE _name, STRING_TYPE _address, long _nationkey, STRING_TYPE _phone, DOUBLE_TYPE _acctbal,         STRING_TYPE _mktsegment, STRING_TYPE _comment) 
        {            
            assert(size < capacity);
            custkey[size] = _custkey;
            name[size] = _name;
            address[size] = _address;
            nationkey[size] = _nationkey;
            phone[size] = _phone;
            acctbal[size] = _acctbal;
            mktsegment[size] = _mktsegment;
            comment[size] = _comment;
            size++;
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
        size_t size;
        size_t capacity;
        long* partkey;
        long* suppkey;
        long* availqty;
        DOUBLE_TYPE* supplycost;
        STRING_TYPE* comment;

        // TPCHPartSuppBatch() : size(0), capacity(0) { }

        TPCHPartSuppBatch(size_t c) { initCapacity(c); } 
        
        TPCHPartSuppBatch(const TPCHPartSuppBatch& batch)
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                partkey[i] = batch.partkey[i];
                suppkey[i] = batch.suppkey[i];
                availqty[i] = batch.availqty[i];
                supplycost[i] = batch.supplycost[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHPartSuppBatch(std::vector<TPCHPartSupp>& partsupps)
        {
            initCapacity(partsupps.size());
            size = partsupps.size();

            for (size_t i = 0; i < partsupps.size(); i++)
            {
                partkey[i] = partsupps[i].partkey;
                suppkey[i] = partsupps[i].suppkey;
                availqty[i] = partsupps[i].availqty;
                supplycost[i] = partsupps[i].supplycost;
                comment[i] = partsupps[i].comment;
            }
        }

        void initCapacity(size_t c)
        {
            assert(c > 0);
            size = 0;
            capacity = c;
            partkey = new long[capacity]();
            suppkey = new long[capacity]();
            availqty = new long[capacity]();
            supplycost = new DOUBLE_TYPE[capacity]();
            comment = new STRING_TYPE[capacity]();          
        }

        void add(long _partkey, long _suppkey, long _availqty,         DOUBLE_TYPE _supplycost, STRING_TYPE _comment) 
        {            
            assert(size < capacity);
            partkey[size] = _partkey;
            suppkey[size] = _suppkey;
            availqty[size] = _availqty;
            supplycost[size] = _supplycost;
            comment[size] = _comment;
            size++;
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
        size_t size;
        size_t capacity;
        long* partkey;
        STRING_TYPE* name;
        STRING_TYPE* mfgr;
        STRING_TYPE* brand;
        STRING_TYPE* type;
        long* psize;
        STRING_TYPE* container;
        DOUBLE_TYPE* retailprice;
        STRING_TYPE* comment;

        //TPCHPartBatch() : size(0), capacity(0) { }

        TPCHPartBatch(size_t c) { initCapacity(c); } 

        TPCHPartBatch(const TPCHPartBatch& batch)
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                partkey[i] = batch.partkey[i];
                name[i] = batch.name[i];
                mfgr[i] = batch.mfgr[i];
                brand[i] = batch.brand[i];
                type[i] = batch.type[i];
                psize[i] = batch.psize[i];
                container[i] = batch.container[i];
                retailprice[i] = batch.retailprice[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHPartBatch(std::vector<TPCHPart>& parts)
        {
            initCapacity(parts.size());
            size = parts.size();
            
            for (size_t i = 0; i < parts.size(); i++)
            {
                partkey[i] = parts[i].partkey;
                name[i] = parts[i].name;
                mfgr[i] = parts[i].mfgr;
                brand[i] = parts[i].brand;
                type[i] = parts[i].type;
                psize[i] = parts[i].size;
                container[i] = parts[i].container;
                retailprice[i] = parts[i].retailprice;
                comment[i] = parts[i].comment;
            }
        }

        void initCapacity(size_t c)
        {
            assert(c > 0);
            size = 0;
            capacity = c;
            partkey = new long[capacity]();
            name = new STRING_TYPE[capacity]();
            mfgr = new STRING_TYPE[capacity]();
            brand = new STRING_TYPE[capacity]();
            type = new STRING_TYPE[capacity]();
            psize = new long[capacity]();
            container = new STRING_TYPE[capacity]();
            retailprice = new DOUBLE_TYPE[capacity]();
            comment = new STRING_TYPE[capacity]();
        }

        void add(long _partkey, STRING_TYPE _name, STRING_TYPE _mfgr,         STRING_TYPE _brand, STRING_TYPE _type, long _size,         STRING_TYPE _container, DOUBLE_TYPE _retailprice,         STRING_TYPE _comment) 
        {            
            assert(size < capacity);
            partkey[size] = _partkey;
            name[size] = _name;
            mfgr[size] = _mfgr;
            brand[size] = _brand;
            type[size] = _type;
            psize[size] = _size;
            container[size] = _container;
            retailprice[size] = _retailprice;
            comment[size] = _comment;
            size++;
        }

        ~TPCHPartBatch()
        {
            delete[] partkey;
            delete[] name;
            delete[] mfgr;
            delete[] brand;
            delete[] type;
            delete[] psize;
            delete[] container;
            delete[] retailprice;
            delete[] comment;
        }
    };

    struct TPCHSupplierBatch
    {
        size_t size;
        size_t capacity;
        long* suppkey;
        STRING_TYPE* name;
        STRING_TYPE* address;
        long* nationkey;
        STRING_TYPE* phone;
        DOUBLE_TYPE* acctbal;
        STRING_TYPE* comment;

        //TPCHSupplierBatch() : size(0), capacity(0) { }

        TPCHSupplierBatch(size_t c) { initCapacity(c); }

        TPCHSupplierBatch(const TPCHSupplierBatch& batch)
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                suppkey[i] = batch.suppkey[i];
                name[i] = batch.name[i];
                address[i] = batch.address[i];
                nationkey[i] = batch.nationkey[i];
                phone[i] = batch.phone[i];
                acctbal[i] = batch.acctbal[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHSupplierBatch(std::vector<TPCHSupplier>& suppliers)
        {
            initCapacity(suppliers.size());
            size = suppliers.size();

            for (size_t i = 0; i < suppliers.size(); i++)
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

        void initCapacity(size_t c)
        {
            assert(c > 0);
            size = 0;
            capacity = c;
            suppkey = new long[capacity]();
            name = new STRING_TYPE[capacity]();
            address = new STRING_TYPE[capacity]();
            nationkey = new long[capacity]();
            phone = new STRING_TYPE[capacity]();
            acctbal = new DOUBLE_TYPE[capacity]();
            comment = new STRING_TYPE[capacity]();            
        }

        void add(long _suppkey, STRING_TYPE _name, STRING_TYPE _address, long _nationkey, STRING_TYPE _phone, DOUBLE_TYPE _acctbal,         STRING_TYPE _comment) 
        {            
            assert(size < capacity);
            suppkey[size] = _suppkey;
            name[size] = _name;
            address[size] = _address;
            nationkey[size] = _nationkey;
            phone[size] = _phone;
            acctbal[size] = _acctbal;
            comment[size] = _comment;
            size++;
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
        size_t size;
        size_t capacity;
        long* nationkey;
        STRING_TYPE* name;
        long* regionkey;
        STRING_TYPE* comment;

        // TPCHNationBatch() : size(0), capacity(0) { }

        TPCHNationBatch(size_t c) { initCapacity(c); }

        TPCHNationBatch(const TPCHNationBatch& batch)
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                nationkey[i] = batch.nationkey[i];
                name[i] = batch.name[i];
                regionkey[i] = batch.regionkey[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHNationBatch(std::vector<TPCHNation>& nations)
        {
            initCapacity(nations.size());
            size = nations.size();

            for (size_t i = 0; i < nations.size(); i++)
            {
                nationkey[i] = nations[i].nationkey;
                name[i] = nations[i].name;
                regionkey[i] = nations[i].regionkey;
                comment[i] = nations[i].comment;
            }
        }

        void initCapacity(size_t c)
        {
            assert(c > 0);
            size = 0;
            capacity = c;
            nationkey = new long[capacity]();
            name = new STRING_TYPE[capacity]();
            regionkey = new long[capacity]();
            comment = new STRING_TYPE[capacity]();
        }

        void add(long _nationkey, STRING_TYPE _name, long _regionkey,         STRING_TYPE _comment) 
        {            
            assert(size < capacity);            
            nationkey[size] = _nationkey;
            name[size] = _name;
            regionkey[size] = _regionkey;
            comment[size] = _comment;
            size++;
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
        size_t size;
        size_t capacity;
        long* regionkey;
        STRING_TYPE* name;
        STRING_TYPE* comment;

        // TPCHRegionBatch() : size(0), capacity(0) { }

        TPCHRegionBatch(size_t c) { initCapacity(c); }

        TPCHRegionBatch(const TPCHRegionBatch& batch)
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                regionkey[i] = batch.regionkey[i];
                name[i] = batch.name[i];
                comment[i] = batch.comment[i];
            }
        }

        TPCHRegionBatch(std::vector<TPCHRegion>& regions)
        {
            initCapacity(regions.size());
            size = regions.size();

            for (size_t i = 0; i < regions.size(); i++)
            {
                regionkey[i] = regions[i].regionkey;
                name[i] = regions[i].name;
                comment[i] = regions[i].comment;
            }
        }

        void initCapacity(size_t c)
        {
            assert(c > 0);
            size = 0;
            capacity = c;
            regionkey = new long[capacity]();
            name = new STRING_TYPE[capacity]();
            comment = new STRING_TYPE[capacity]();
        }

        void add(long _regionkey, STRING_TYPE _name, STRING_TYPE _comment) 
        {
            assert(size < capacity);
            regionkey[size] = _regionkey;
            name[size] = _name;
            comment[size] = _comment;
            size++;
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
