#ifndef DBTOASTER_TEST_TPCDS_HPP
#define DBTOASTER_TEST_TPCDS_HPP

#include <vector>
#include "types.hpp"
#include "serialization.hpp"

namespace dbtoaster 
{

    struct TPCDSDateDim
    {
        long d_date_sk;
        STRING_TYPE d_date_id;
        date d_date;
        long d_month_seq;
        long d_week_seq;
        long d_quarter_seq;
        long d_year;
        long d_dow;
        long d_moy;
        long d_dom;
        long d_qoy;
        long d_fy_year;
        long d_fy_quarter_seq;
        long d_fy_week_seq;
        STRING_TYPE d_day_name;
        STRING_TYPE d_quarter_name;
        STRING_TYPE d_holiday;
        STRING_TYPE d_weekend;
        STRING_TYPE d_following_holiday;
        long d_first_dom;
        long d_last_dom;
        long d_same_day_ly;
        long d_same_day_lq;
        STRING_TYPE d_current_day;
        STRING_TYPE d_current_week;
        STRING_TYPE d_current_month;
        STRING_TYPE d_current_quarter;
        STRING_TYPE d_current_year;

        TPCDSDateDim() { }

        TPCDSDateDim(std::vector<std::string>& fields)
        {
            if (fields.size() < 28) return;
            d_date_sk = std::stol(fields[0]);
            d_date_id = fields[1];
            d_date = str2date(fields[2]);
            d_month_seq = std::stol(fields[3]);
            d_week_seq  = std::stol(fields[4]);
            d_quarter_seq = std::stol(fields[5]);
            d_year = std::stol(fields[6]); 
            d_dow = std::stol(fields[7]);
            d_moy = std::stol(fields[8]);
            d_dom = std::stol(fields[9]);
            d_qoy = std::stol(fields[10]);
            d_fy_year = std::stol(fields[11]);
            d_fy_quarter_seq = std::stol(fields[12]);
            d_fy_week_seq = std::stol(fields[13]);
            d_day_name = fields[14];
            d_quarter_name = fields[15];
            d_holiday = fields[16];
            d_weekend = fields[17];
            d_following_holiday = fields[18];
            d_first_dom = std::stol(fields[19]);
            d_last_dom = std::stol(fields[20]);
            d_same_day_ly = std::stol(fields[21]);
            d_same_day_lq = std::stol(fields[22]);
            d_current_day = fields[23];
            d_current_week = fields[24];
            d_current_month = fields[25];
            d_current_quarter = fields[26];
            d_current_year = fields[27];
        }
    };

    struct TPCDSStoreSales 
    {
        long ss_sold_date_sk;
        long ss_sold_time_sk;
        long ss_item_sk;
        long ss_customer_sk;
        long ss_cdemo_sk;
        long ss_hdemo_sk;
        long ss_addr_sk;
        long ss_store_sk;
        long ss_promo_sk;
        long ss_ticket_number;
        long ss_quantity;
        DOUBLE_TYPE ss_wholesale_cost;
        DOUBLE_TYPE ss_list_price;
        DOUBLE_TYPE ss_sales_price;
        DOUBLE_TYPE ss_ext_discount_amt;
        DOUBLE_TYPE ss_ext_sales_price;
        DOUBLE_TYPE ss_ext_wholesale_cost;
        DOUBLE_TYPE ss_ext_list_price;
        DOUBLE_TYPE ss_ext_tax;
        DOUBLE_TYPE ss_coupon_amt;
        DOUBLE_TYPE ss_net_paid;
        DOUBLE_TYPE ss_net_paid_inc_tax;
        DOUBLE_TYPE ss_net_profit;

        TPCDSStoreSales() { }

        TPCDSStoreSales(std::vector<std::string>& fields)
        {
            if (fields.size() < 23) return;
            ss_sold_date_sk = std::stol(fields[0]);    
            ss_sold_time_sk = std::stol(fields[1]);
            ss_item_sk = std::stol(fields[2]);
            ss_customer_sk = std::stol(fields[3]);
            ss_cdemo_sk = std::stol(fields[4]);
            ss_hdemo_sk = std::stol(fields[5]);
            ss_addr_sk = std::stol(fields[6]);
            ss_store_sk = std::stol(fields[7]);
            ss_promo_sk = std::stol(fields[8]);
            ss_ticket_number = std::stol(fields[9]);
            ss_quantity = std::stol(fields[10]);
            ss_wholesale_cost = std::stol(fields[11]);
            ss_list_price = std::stod(fields[12]);      
            ss_sales_price = std::stod(fields[13]);
            ss_ext_discount_amt = std::stod(fields[14]);
            ss_ext_sales_price = std::stod(fields[15]);
            ss_ext_wholesale_cost = std::stod(fields[16]);
            ss_ext_list_price = std::stod(fields[17]);
            ss_ext_tax = std::stod(fields[18]);
            ss_coupon_amt = std::stod(fields[19]);
            ss_net_paid = std::stod(fields[20]);
            ss_net_paid_inc_tax = std::stod(fields[21]);
            ss_net_profit = std::stod(fields[22]);
        }
    };

    struct TPCDSItem 
    {
        long i_item_sk;
        STRING_TYPE i_item_id;
        date i_rec_start_date;
        date i_rec_end_date;
        STRING_TYPE i_item_desc;
        DOUBLE_TYPE i_current_price;
        DOUBLE_TYPE i_wholesale_cost;
        long i_brand_id;
        STRING_TYPE i_brand;
        long i_class_id;
        STRING_TYPE i_class;
        long i_category_id;
        STRING_TYPE i_category;
        long i_manufact_id;
        STRING_TYPE i_manufact;
        STRING_TYPE i_size;
        STRING_TYPE i_formulation;
        STRING_TYPE i_color;
        STRING_TYPE i_units;
        STRING_TYPE i_container;
        long i_manager_id;
        STRING_TYPE i_product_name;


        TPCDSItem() { }

        TPCDSItem(std::vector<std::string>& fields)
        {
            if (fields.size() < 22) return;
            i_item_sk = std::stol(fields[0]); 
            i_item_id = fields[1];
            i_rec_start_date = str2date(fields[2]);
            i_rec_end_date = str2date(fields[3]);
            i_item_desc = fields[4];
            i_current_price = std::stod(fields[5]);  
            i_wholesale_cost = std::stod(fields[6]);
            i_brand_id = std::stol(fields[7]);
            i_brand = fields[8];
            i_class_id = std::stol(fields[9]);
            i_class = fields[10];
            i_category_id = std::stol(fields[11]);
            i_category = fields[12];
            i_manufact_id = std::stol(fields[13]);
            i_manufact = fields[14];
            i_size = fields[15];
            i_formulation = fields[16];
            i_color = fields[17];
            i_units = fields[18];
            i_container = fields[19];
            i_manager_id = std::stol(fields[20]);
            i_product_name = fields[21];
        }        
    };

    struct TPCDSCustomer
    {
        long c_customer_sk;
        STRING_TYPE c_customer_id;
        long c_current_cdemo_sk;
        long c_current_hdemo_sk;
        long c_current_addr_sk;
        long c_first_shipto_date_sk;
        long c_first_sales_date_sk;
        STRING_TYPE c_salutation;
        STRING_TYPE c_first_name;
        STRING_TYPE c_last_name;
        STRING_TYPE c_preferred_cust_flag;
        long c_birth_day;
        long c_birth_month;
        long c_birth_year;
        STRING_TYPE c_birth_country;
        STRING_TYPE c_login;
        STRING_TYPE c_email_address;
        STRING_TYPE c_last_review_date;

        TPCDSCustomer() { }  

        TPCDSCustomer(std::vector<std::string>& fields) 
        {
            if (fields.size() < 18) return;
            c_customer_sk = std::stol(fields[0]); 
            c_customer_id = fields[1];
            c_current_cdemo_sk = std::stol(fields[2]); 
            c_current_hdemo_sk = std::stol(fields[3]); 
            c_current_addr_sk = std::stol(fields[4]); 
            c_first_shipto_date_sk = std::stol(fields[5]); 
            c_first_sales_date_sk = std::stol(fields[6]); 
            c_salutation = fields[7];
            c_first_name = fields[8];
            c_last_name = fields[9];
            c_preferred_cust_flag = fields[10];
            c_birth_day = std::stol(fields[11]); 
            c_birth_month = std::stol(fields[12]); 
            c_birth_year = std::stol(fields[13]); 
            c_birth_country = fields[14]; 
            c_login = fields[15];
            c_email_address = fields[16];
            c_last_review_date = fields[17];
        }
    };

    struct TPCDSCustomerAddress 
    {
        long ca_address_sk;
        STRING_TYPE ca_address_id;
        STRING_TYPE ca_street_number;
        STRING_TYPE ca_street_name;
        STRING_TYPE ca_street_type;
        STRING_TYPE ca_suite_number;
        STRING_TYPE ca_city;
        STRING_TYPE ca_county;
        STRING_TYPE ca_state;
        STRING_TYPE ca_zip;
        STRING_TYPE ca_country;
        DOUBLE_TYPE ca_gmt_offset;
        STRING_TYPE ca_location_type;

        TPCDSCustomerAddress() { }

        TPCDSCustomerAddress(std::vector<std::string>& fields) 
        {
            if (fields.size() < 13) return;            
            ca_address_sk = std::stol(fields[0]); 
            ca_address_id = fields[1];
            ca_street_number = fields[2];
            ca_street_name = fields[3];
            ca_street_type = fields[4];
            ca_suite_number = fields[5];
            ca_city = fields[6];
            ca_county = fields[7];
            ca_state = fields[8];
            ca_zip = fields[9];
            ca_country = fields[10];
            ca_gmt_offset = std::stod(fields[11]); 
            ca_location_type = fields[12];
        }
    };

    struct TPCDSStore
    {
        long s_store_sk;
        STRING_TYPE s_store_id;
        date s_rec_start_date;
        date s_rec_end_date;
        long s_closed_date_sk;
        STRING_TYPE s_store_name;
        long s_number_employees;
        long s_floor_space;
        STRING_TYPE s_hours;
        STRING_TYPE s_manager;
        long s_market_id;
        STRING_TYPE s_geography_class;
        STRING_TYPE s_market_desc;
        STRING_TYPE s_market_manager;
        long s_division_id;
        STRING_TYPE s_division_name;
        long s_company_id;
        STRING_TYPE s_company_name;
        STRING_TYPE s_street_number;
        STRING_TYPE s_street_name;
        STRING_TYPE s_street_type;
        STRING_TYPE s_suite_number;
        STRING_TYPE s_city;
        STRING_TYPE s_county;
        STRING_TYPE s_state;
        STRING_TYPE s_zip;
        STRING_TYPE s_country;
        DOUBLE_TYPE s_gmt_offset;
        DOUBLE_TYPE s_tax_precentage;

        TPCDSStore() { }

        TPCDSStore(std::vector<std::string>& fields) 
        {
            if (fields.size() < 29) return;        
            s_store_sk = std::stol(fields[0]); 
            s_store_id = fields[1];
            s_rec_start_date = str2date(fields[2]);
            s_rec_end_date = str2date(fields[3]);
            s_closed_date_sk = std::stol(fields[4]); 
            s_store_name = fields[5];
            s_number_employees = std::stol(fields[6]);
            s_floor_space = std::stol(fields[7]);
            s_hours = fields[8];
            s_manager = fields[9];
            s_market_id = std::stol(fields[10]); 
            s_geography_class = fields[11];
            s_market_desc = fields[12];
            s_market_manager = fields[13];
            s_division_id = std::stol(fields[14]); 
            s_division_name = fields[15];
            s_company_id = std::stol(fields[16]); 
            s_company_name = fields[17];
            s_street_number = fields[18];
            s_street_name = fields[19];
            s_street_type = fields[20];
            s_suite_number = fields[21];
            s_city = fields[22];
            s_county = fields[23];
            s_state = fields[24];
            s_zip = fields[25];
            s_country = fields[26];
            s_gmt_offset = std::stod(fields[27]); 
            s_tax_precentage = std::stod(fields[28]); 
        }
    };

    struct TPCDSHouseholdDemographics
    {
        long hd_demo_sk;
        long hd_income_band_sk;
        STRING_TYPE hd_buy_potential;
        long hd_dep_count;
        long hd_vehicle_count;

        TPCDSHouseholdDemographics() { }

        TPCDSHouseholdDemographics(std::vector<std::string>& fields) 
        {
            if (fields.size() < 5) return;  
             hd_demo_sk = std::stol(fields[0]); 
             hd_income_band_sk = std::stol(fields[1]);
             hd_buy_potential = fields[2];
             hd_dep_count = std::stol(fields[3]); 
             hd_vehicle_count = std::stol(fields[4]); 
        }
    };

    struct TPCDSCustomerDemographics
    {
        long cd_demo_sk;
        STRING_TYPE cd_gender;
        STRING_TYPE cd_marital_status;
        STRING_TYPE cd_education_status;
        long cd_purchase_estimate;
        STRING_TYPE cd_credit_rating;
        long cd_dep_count;
        long cd_dep_employed_count;
        long cd_dep_college_count;

        TPCDSCustomerDemographics() { }

        TPCDSCustomerDemographics(std::vector<std::string>& fields)
        {
            if (fields.size() < 9) return;  
            cd_demo_sk = std::stol(fields[0]); 
            cd_gender = fields[1];
            cd_marital_status = fields[2];
            cd_education_status = fields[3];
            cd_purchase_estimate = std::stol(fields[4]); 
            cd_credit_rating = fields[5];
            cd_dep_count = std::stol(fields[6]); 
            cd_dep_employed_count = std::stol(fields[7]); 
            cd_dep_college_count = std::stol(fields[8]); 
        }
    };

    struct TPCDSPromotion
    {
        long p_promo_sk;
        STRING_TYPE p_promo_id;
        long p_start_date_sk;
        long p_end_date_sk;
        long p_item_sk;
        DOUBLE_TYPE p_cost;
        long p_response_target;
        STRING_TYPE p_promo_name;
        STRING_TYPE p_channel_dmail;
        STRING_TYPE p_channel_email;
        STRING_TYPE p_channel_catalog;
        STRING_TYPE p_channel_tv;
        STRING_TYPE p_channel_radio;
        STRING_TYPE p_channel_press;
        STRING_TYPE p_channel_event;
        STRING_TYPE p_channel_demo;
        STRING_TYPE p_channel_details;
        STRING_TYPE p_purpose;
        STRING_TYPE p_discount_active;

        TPCDSPromotion() { }

        TPCDSPromotion(std::vector<std::string>& fields)
        {
            if (fields.size() < 19) return;  
            p_promo_sk = std::stol(fields[0]); 
            p_promo_id = fields[1];
            p_start_date_sk = std::stol(fields[2]); 
            p_end_date_sk = std::stol(fields[3]); 
            p_item_sk = std::stol(fields[4]); 
            p_cost = std::stod(fields[5]); 
            p_response_target = std::stol(fields[6]); 
            p_promo_name = fields[7];
            p_channel_dmail = fields[8];
            p_channel_email = fields[9];
            p_channel_catalog = fields[10];
            p_channel_tv = fields[11];
            p_channel_radio = fields[12];
            p_channel_press = fields[13];
            p_channel_event = fields[14];
            p_channel_demo = fields[15];
            p_channel_details = fields[16];
            p_purpose = fields[17];
            p_discount_active = fields[18];
        }
    };


    struct TPCDSDateDimBatch
    {
        size_t size;
        size_t capacity;

        long* d_date_sk;
        STRING_TYPE* d_date_id;
        date* d_date;
        long* d_month_seq;
        long* d_week_seq;
        long* d_quarter_seq;
        long* d_year;
        long* d_dow;
        long* d_moy;
        long* d_dom;
        long* d_qoy;
        long* d_fy_year;
        long* d_fy_quarter_seq;
        long* d_fy_week_seq;
        STRING_TYPE* d_day_name;
        STRING_TYPE* d_quarter_name;
        STRING_TYPE* d_holiday;
        STRING_TYPE* d_weekend;
        STRING_TYPE* d_following_holiday;
        long* d_first_dom;
        long* d_last_dom;
        long* d_same_day_ly;
        long* d_same_day_lq;
        STRING_TYPE* d_current_day;
        STRING_TYPE* d_current_week;
        STRING_TYPE* d_current_month;
        STRING_TYPE* d_current_quarter;
        STRING_TYPE* d_current_year;


        TPCDSDateDimBatch(size_t c) { initCapacity(c); }

        TPCDSDateDimBatch(const TPCDSDateDimBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                d_date_sk[i] = batch.d_date_sk[i];
                d_date_id[i] = batch.d_date_id[i];
                d_date[i] = batch.d_date[i];
                d_month_seq[i] = batch.d_month_seq[i];
                d_week_seq[i] = batch.d_week_seq[i];
                d_quarter_seq[i] = batch.d_quarter_seq[i];
                d_year[i] = batch.d_year[i];
                d_dow[i] = batch.d_dow[i];
                d_moy[i] = batch.d_moy[i];
                d_dom[i] = batch.d_dom[i];
                d_qoy[i] = batch.d_qoy[i];
                d_fy_year[i] = batch.d_fy_year[i];
                d_fy_quarter_seq[i] = batch.d_fy_quarter_seq[i];
                d_fy_week_seq[i] = batch.d_fy_week_seq[i];
                d_day_name[i] = batch.d_day_name[i];
                d_quarter_name[i] = batch.d_quarter_name[i];
                d_holiday[i] = batch.d_holiday[i];
                d_weekend[i] = batch.d_weekend[i];
                d_following_holiday[i] = batch.d_following_holiday[i];
                d_first_dom[i] = batch.d_first_dom[i];
                d_last_dom[i] = batch.d_last_dom[i];
                d_same_day_ly[i] = batch.d_same_day_ly[i];
                d_same_day_lq[i] = batch.d_same_day_lq[i];
                d_current_day[i] = batch.d_current_day[i];
                d_current_week[i] = batch.d_current_week[i];
                d_current_month[i] = batch.d_current_month[i];
                d_current_quarter[i] = batch.d_current_quarter[i];
                d_current_year[i] = batch.d_current_year[i];
            }
        }

        TPCDSDateDimBatch(std::vector<TPCDSDateDim>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                d_date_sk[i] = items[i].d_date_sk;
                d_date_id[i] = items[i].d_date_id;
                d_date[i] = items[i].d_date;
                d_month_seq[i] = items[i].d_month_seq;
                d_week_seq[i] = items[i].d_week_seq;
                d_quarter_seq[i] = items[i].d_quarter_seq;
                d_year[i] = items[i].d_year;
                d_dow[i] = items[i].d_dow;
                d_moy[i] = items[i].d_moy;
                d_dom[i] = items[i].d_dom;
                d_qoy[i] = items[i].d_qoy;
                d_fy_year[i] = items[i].d_fy_year;
                d_fy_quarter_seq[i] = items[i].d_fy_quarter_seq;
                d_fy_week_seq[i] = items[i].d_fy_week_seq;
                d_day_name[i] = items[i].d_day_name;
                d_quarter_name[i] = items[i].d_quarter_name;
                d_holiday[i] = items[i].d_holiday;
                d_weekend[i] = items[i].d_weekend;
                d_following_holiday[i] = items[i].d_following_holiday;
                d_first_dom[i] = items[i].d_first_dom;
                d_last_dom[i] = items[i].d_last_dom;
                d_same_day_ly[i] = items[i].d_same_day_ly;
                d_same_day_lq[i] = items[i].d_same_day_lq;
                d_current_day[i] = items[i].d_current_day;
                d_current_week[i] = items[i].d_current_week;
                d_current_month[i] = items[i].d_current_month;
                d_current_quarter[i] = items[i].d_current_quarter;
                d_current_year[i] = items[i].d_current_year;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            d_date_sk = new long[capacity]();
            d_date_id = new STRING_TYPE[capacity]();
            d_date = new date[capacity]();
            d_month_seq = new long[capacity]();
            d_week_seq = new long[capacity]();
            d_quarter_seq = new long[capacity]();
            d_year = new long[capacity]();
            d_dow = new long[capacity]();
            d_moy = new long[capacity]();
            d_dom = new long[capacity]();
            d_qoy = new long[capacity]();
            d_fy_year = new long[capacity]();
            d_fy_quarter_seq = new long[capacity]();
            d_fy_week_seq = new long[capacity]();
            d_day_name = new STRING_TYPE[capacity]();
            d_quarter_name = new STRING_TYPE[capacity]();
            d_holiday = new STRING_TYPE[capacity]();
            d_weekend = new STRING_TYPE[capacity]();
            d_following_holiday = new STRING_TYPE[capacity]();
            d_first_dom = new long[capacity]();
            d_last_dom = new long[capacity]();
            d_same_day_ly = new long[capacity]();
            d_same_day_lq = new long[capacity]();
            d_current_day = new STRING_TYPE[capacity]();
            d_current_week = new STRING_TYPE[capacity]();
            d_current_month = new STRING_TYPE[capacity]();
            d_current_quarter = new STRING_TYPE[capacity]();
            d_current_year = new STRING_TYPE[capacity]();
        }

        void add(long _d_date_sk, STRING_TYPE _d_date_id, date _d_date, long _d_month_seq, long _d_week_seq, long _d_quarter_seq, long _d_year, long _d_dow, long _d_moy, long _d_dom, long _d_qoy, long _d_fy_year, long _d_fy_quarter_seq, long _d_fy_week_seq, STRING_TYPE _d_day_name, STRING_TYPE _d_quarter_name, STRING_TYPE _d_holiday, STRING_TYPE _d_weekend, STRING_TYPE _d_following_holiday, long _d_first_dom, long _d_last_dom, long _d_same_day_ly, long _d_same_day_lq, STRING_TYPE _d_current_day, STRING_TYPE _d_current_week, STRING_TYPE _d_current_month, STRING_TYPE _d_current_quarter, STRING_TYPE _d_current_year)
        {            
            assert(size < capacity);
            d_date_sk[size] = _d_date_sk;
            d_date_id[size] = _d_date_id;
            d_date[size] = _d_date;
            d_month_seq[size] = _d_month_seq;
            d_week_seq[size] = _d_week_seq;
            d_quarter_seq[size] = _d_quarter_seq;
            d_year[size] = _d_year;
            d_dow[size] = _d_dow;
            d_moy[size] = _d_moy;
            d_dom[size] = _d_dom;
            d_qoy[size] = _d_qoy;
            d_fy_year[size] = _d_fy_year;
            d_fy_quarter_seq[size] = _d_fy_quarter_seq;
            d_fy_week_seq[size] = _d_fy_week_seq;
            d_day_name[size] = _d_day_name;
            d_quarter_name[size] = _d_quarter_name;
            d_holiday[size] = _d_holiday;
            d_weekend[size] = _d_weekend;
            d_following_holiday[size] = _d_following_holiday;
            d_first_dom[size] = _d_first_dom;
            d_last_dom[size] = _d_last_dom;
            d_same_day_ly[size] = _d_same_day_ly;
            d_same_day_lq[size] = _d_same_day_lq;
            d_current_day[size] = _d_current_day;
            d_current_week[size] = _d_current_week;
            d_current_month[size] = _d_current_month;
            d_current_quarter[size] = _d_current_quarter;
            d_current_year[size] = _d_current_year;
            size++;
        }

        ~TPCDSDateDimBatch()
        {
            delete[] d_date_sk;
            delete[] d_date_id;
            delete[] d_date;
            delete[] d_month_seq;
            delete[] d_week_seq;
            delete[] d_quarter_seq;
            delete[] d_year;
            delete[] d_dow;
            delete[] d_moy;
            delete[] d_dom;
            delete[] d_qoy;
            delete[] d_fy_year;
            delete[] d_fy_quarter_seq;
            delete[] d_fy_week_seq;
            delete[] d_day_name;
            delete[] d_quarter_name;
            delete[] d_holiday;
            delete[] d_weekend;
            delete[] d_following_holiday;
            delete[] d_first_dom;
            delete[] d_last_dom;
            delete[] d_same_day_ly;
            delete[] d_same_day_lq;
            delete[] d_current_day;
            delete[] d_current_week;
            delete[] d_current_month;
            delete[] d_current_quarter;
            delete[] d_current_year;
        }
    };


    struct TPCDSStoreSalesBatch
    {
        size_t size;
        size_t capacity;

        long* ss_sold_date_sk;
        long* ss_sold_time_sk;
        long* ss_item_sk;
        long* ss_customer_sk;
        long* ss_cdemo_sk;
        long* ss_hdemo_sk;
        long* ss_addr_sk;
        long* ss_store_sk;
        long* ss_promo_sk;
        long* ss_ticket_number;
        long* ss_quantity;
        DOUBLE_TYPE* ss_wholesale_cost;
        DOUBLE_TYPE* ss_list_price;
        DOUBLE_TYPE* ss_sales_price;
        DOUBLE_TYPE* ss_ext_discount_amt;
        DOUBLE_TYPE* ss_ext_sales_price;
        DOUBLE_TYPE* ss_ext_wholesale_cost;
        DOUBLE_TYPE* ss_ext_list_price;
        DOUBLE_TYPE* ss_ext_tax;
        DOUBLE_TYPE* ss_coupon_amt;
        DOUBLE_TYPE* ss_net_paid;
        DOUBLE_TYPE* ss_net_paid_inc_tax;
        DOUBLE_TYPE* ss_net_profit;

        TPCDSStoreSalesBatch(size_t c) { initCapacity(c); }

        TPCDSStoreSalesBatch(const TPCDSStoreSalesBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                ss_sold_date_sk[i] = batch.ss_sold_date_sk[i];
                ss_sold_time_sk[i] = batch.ss_sold_time_sk[i];
                ss_item_sk[i] = batch.ss_item_sk[i];
                ss_customer_sk[i] = batch.ss_customer_sk[i];
                ss_cdemo_sk[i] = batch.ss_cdemo_sk[i];
                ss_hdemo_sk[i] = batch.ss_hdemo_sk[i];
                ss_addr_sk[i] = batch.ss_addr_sk[i];
                ss_store_sk[i] = batch.ss_store_sk[i];
                ss_promo_sk[i] = batch.ss_promo_sk[i];
                ss_ticket_number[i] = batch.ss_ticket_number[i];
                ss_quantity[i] = batch.ss_quantity[i];
                ss_wholesale_cost[i] = batch.ss_wholesale_cost[i];
                ss_list_price[i] = batch.ss_list_price[i];
                ss_sales_price[i] = batch.ss_sales_price[i];
                ss_ext_discount_amt[i] = batch.ss_ext_discount_amt[i];
                ss_ext_sales_price[i] = batch.ss_ext_sales_price[i];
                ss_ext_wholesale_cost[i] = batch.ss_ext_wholesale_cost[i];
                ss_ext_list_price[i] = batch.ss_ext_list_price[i];
                ss_ext_tax[i] = batch.ss_ext_tax[i];
                ss_coupon_amt[i] = batch.ss_coupon_amt[i];
                ss_net_paid[i] = batch.ss_net_paid[i];
                ss_net_paid_inc_tax[i] = batch.ss_net_paid_inc_tax[i];
                ss_net_profit[i] = batch.ss_net_profit[i];
            }
        }

        TPCDSStoreSalesBatch(std::vector<TPCDSStoreSales>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                ss_sold_date_sk[i] = items[i].ss_sold_date_sk;
                ss_sold_time_sk[i] = items[i].ss_sold_time_sk;
                ss_item_sk[i] = items[i].ss_item_sk;
                ss_customer_sk[i] = items[i].ss_customer_sk;
                ss_cdemo_sk[i] = items[i].ss_cdemo_sk;
                ss_hdemo_sk[i] = items[i].ss_hdemo_sk;
                ss_addr_sk[i] = items[i].ss_addr_sk;
                ss_store_sk[i] = items[i].ss_store_sk;
                ss_promo_sk[i] = items[i].ss_promo_sk;
                ss_ticket_number[i] = items[i].ss_ticket_number;
                ss_quantity[i] = items[i].ss_quantity;
                ss_wholesale_cost[i] = items[i].ss_wholesale_cost;
                ss_list_price[i] = items[i].ss_list_price;
                ss_sales_price[i] = items[i].ss_sales_price;
                ss_ext_discount_amt[i] = items[i].ss_ext_discount_amt;
                ss_ext_sales_price[i] = items[i].ss_ext_sales_price;
                ss_ext_wholesale_cost[i] = items[i].ss_ext_wholesale_cost;
                ss_ext_list_price[i] = items[i].ss_ext_list_price;
                ss_ext_tax[i] = items[i].ss_ext_tax;
                ss_coupon_amt[i] = items[i].ss_coupon_amt;
                ss_net_paid[i] = items[i].ss_net_paid;
                ss_net_paid_inc_tax[i] = items[i].ss_net_paid_inc_tax;
                ss_net_profit[i] = items[i].ss_net_profit;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            ss_sold_date_sk = new long[capacity]();
            ss_sold_time_sk = new long[capacity]();
            ss_item_sk = new long[capacity]();
            ss_customer_sk = new long[capacity]();
            ss_cdemo_sk = new long[capacity]();
            ss_hdemo_sk = new long[capacity]();
            ss_addr_sk = new long[capacity]();
            ss_store_sk = new long[capacity]();
            ss_promo_sk = new long[capacity]();
            ss_ticket_number = new long[capacity]();
            ss_quantity = new long[capacity]();
            ss_wholesale_cost = new DOUBLE_TYPE[capacity]();
            ss_list_price = new DOUBLE_TYPE[capacity]();
            ss_sales_price = new DOUBLE_TYPE[capacity]();
            ss_ext_discount_amt = new DOUBLE_TYPE[capacity]();
            ss_ext_sales_price = new DOUBLE_TYPE[capacity]();
            ss_ext_wholesale_cost = new DOUBLE_TYPE[capacity]();
            ss_ext_list_price = new DOUBLE_TYPE[capacity]();
            ss_ext_tax = new DOUBLE_TYPE[capacity]();
            ss_coupon_amt = new DOUBLE_TYPE[capacity]();
            ss_net_paid = new DOUBLE_TYPE[capacity]();
            ss_net_paid_inc_tax = new DOUBLE_TYPE[capacity]();
            ss_net_profit = new DOUBLE_TYPE[capacity]();
        }

        void add(long _ss_sold_date_sk, long _ss_sold_time_sk, long _ss_item_sk, long _ss_customer_sk, long _ss_cdemo_sk, long _ss_hdemo_sk, long _ss_addr_sk, long _ss_store_sk, long _ss_promo_sk, long _ss_ticket_number, long _ss_quantity, DOUBLE_TYPE _ss_wholesale_cost, DOUBLE_TYPE _ss_list_price, DOUBLE_TYPE _ss_sales_price, DOUBLE_TYPE _ss_ext_discount_amt, DOUBLE_TYPE _ss_ext_sales_price, DOUBLE_TYPE _ss_ext_wholesale_cost, DOUBLE_TYPE _ss_ext_list_price, DOUBLE_TYPE _ss_ext_tax, DOUBLE_TYPE _ss_coupon_amt, DOUBLE_TYPE _ss_net_paid, DOUBLE_TYPE _ss_net_paid_inc_tax, DOUBLE_TYPE _ss_net_profit)
        {            
            assert(size < capacity);
            ss_sold_date_sk[size] = _ss_sold_date_sk;
            ss_sold_time_sk[size] = _ss_sold_time_sk;
            ss_item_sk[size] = _ss_item_sk;
            ss_customer_sk[size] = _ss_customer_sk;
            ss_cdemo_sk[size] = _ss_cdemo_sk;
            ss_hdemo_sk[size] = _ss_hdemo_sk;
            ss_addr_sk[size] = _ss_addr_sk;
            ss_store_sk[size] = _ss_store_sk;
            ss_promo_sk[size] = _ss_promo_sk;
            ss_ticket_number[size] = _ss_ticket_number;
            ss_quantity[size] = _ss_quantity;
            ss_wholesale_cost[size] = _ss_wholesale_cost;
            ss_list_price[size] = _ss_list_price;
            ss_sales_price[size] = _ss_sales_price;
            ss_ext_discount_amt[size] = _ss_ext_discount_amt;
            ss_ext_sales_price[size] = _ss_ext_sales_price;
            ss_ext_wholesale_cost[size] = _ss_ext_wholesale_cost;
            ss_ext_list_price[size] = _ss_ext_list_price;
            ss_ext_tax[size] = _ss_ext_tax;
            ss_coupon_amt[size] = _ss_coupon_amt;
            ss_net_paid[size] = _ss_net_paid;
            ss_net_paid_inc_tax[size] = _ss_net_paid_inc_tax;
            ss_net_profit[size] = _ss_net_profit;
            size++;
        }

        ~TPCDSStoreSalesBatch()
        {
            delete[] ss_sold_date_sk;
            delete[] ss_sold_time_sk;
            delete[] ss_item_sk;
            delete[] ss_customer_sk;
            delete[] ss_cdemo_sk;
            delete[] ss_hdemo_sk;
            delete[] ss_addr_sk;
            delete[] ss_store_sk;
            delete[] ss_promo_sk;
            delete[] ss_ticket_number;
            delete[] ss_quantity;
            delete[] ss_wholesale_cost;
            delete[] ss_list_price;
            delete[] ss_sales_price;
            delete[] ss_ext_discount_amt;
            delete[] ss_ext_sales_price;
            delete[] ss_ext_wholesale_cost;
            delete[] ss_ext_list_price;
            delete[] ss_ext_tax;
            delete[] ss_coupon_amt;
            delete[] ss_net_paid;
            delete[] ss_net_paid_inc_tax;
            delete[] ss_net_profit;
        }
    };


    struct TPCDSItemBatch
    {
        size_t size;
        size_t capacity;

        long* i_item_sk;
        STRING_TYPE* i_item_id;
        date* i_rec_start_date;
        date* i_rec_end_date;
        STRING_TYPE* i_item_desc;
        DOUBLE_TYPE* i_current_price;
        DOUBLE_TYPE* i_wholesale_cost;
        long* i_brand_id;
        STRING_TYPE* i_brand;
        long* i_class_id;
        STRING_TYPE* i_class;
        long* i_category_id;
        STRING_TYPE* i_category;
        long* i_manufact_id;
        STRING_TYPE* i_manufact;
        STRING_TYPE* i_size;
        STRING_TYPE* i_formulation;
        STRING_TYPE* i_color;
        STRING_TYPE* i_units;
        STRING_TYPE* i_container;
        long* i_manager_id;
        STRING_TYPE* i_product_name;

        TPCDSItemBatch(size_t c) { initCapacity(c); }

        TPCDSItemBatch(const TPCDSItemBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                i_item_sk[i] = batch.i_item_sk[i];
                i_item_id[i] = batch.i_item_id[i];
                i_rec_start_date[i] = batch.i_rec_start_date[i];
                i_rec_end_date[i] = batch.i_rec_end_date[i];
                i_item_desc[i] = batch.i_item_desc[i];
                i_current_price[i] = batch.i_current_price[i];
                i_wholesale_cost[i] = batch.i_wholesale_cost[i];
                i_brand_id[i] = batch.i_brand_id[i];
                i_brand[i] = batch.i_brand[i];
                i_class_id[i] = batch.i_class_id[i];
                i_class[i] = batch.i_class[i];
                i_category_id[i] = batch.i_category_id[i];
                i_category[i] = batch.i_category[i];
                i_manufact_id[i] = batch.i_manufact_id[i];
                i_manufact[i] = batch.i_manufact[i];
                i_size[i] = batch.i_size[i];
                i_formulation[i] = batch.i_formulation[i];
                i_color[i] = batch.i_color[i];
                i_units[i] = batch.i_units[i];
                i_container[i] = batch.i_container[i];
                i_manager_id[i] = batch.i_manager_id[i];
                i_product_name[i] = batch.i_product_name[i];
            }
        }

        TPCDSItemBatch(std::vector<TPCDSItem>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                i_item_sk[i] = items[i].i_item_sk;
                i_item_id[i] = items[i].i_item_id;
                i_rec_start_date[i] = items[i].i_rec_start_date;
                i_rec_end_date[i] = items[i].i_rec_end_date;
                i_item_desc[i] = items[i].i_item_desc;
                i_current_price[i] = items[i].i_current_price;
                i_wholesale_cost[i] = items[i].i_wholesale_cost;
                i_brand_id[i] = items[i].i_brand_id;
                i_brand[i] = items[i].i_brand;
                i_class_id[i] = items[i].i_class_id;
                i_class[i] = items[i].i_class;
                i_category_id[i] = items[i].i_category_id;
                i_category[i] = items[i].i_category;
                i_manufact_id[i] = items[i].i_manufact_id;
                i_manufact[i] = items[i].i_manufact;
                i_size[i] = items[i].i_size;
                i_formulation[i] = items[i].i_formulation;
                i_color[i] = items[i].i_color;
                i_units[i] = items[i].i_units;
                i_container[i] = items[i].i_container;
                i_manager_id[i] = items[i].i_manager_id;
                i_product_name[i] = items[i].i_product_name;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            i_item_sk = new long[capacity]();
            i_item_id = new STRING_TYPE[capacity]();
            i_rec_start_date = new date[capacity]();
            i_rec_end_date = new date[capacity]();
            i_item_desc = new STRING_TYPE[capacity]();
            i_current_price = new DOUBLE_TYPE[capacity]();
            i_wholesale_cost = new DOUBLE_TYPE[capacity]();
            i_brand_id = new long[capacity]();
            i_brand = new STRING_TYPE[capacity]();
            i_class_id = new long[capacity]();
            i_class = new STRING_TYPE[capacity]();
            i_category_id = new long[capacity]();
            i_category = new STRING_TYPE[capacity]();
            i_manufact_id = new long[capacity]();
            i_manufact = new STRING_TYPE[capacity]();
            i_size = new STRING_TYPE[capacity]();
            i_formulation = new STRING_TYPE[capacity]();
            i_color = new STRING_TYPE[capacity]();
            i_units = new STRING_TYPE[capacity]();
            i_container = new STRING_TYPE[capacity]();
            i_manager_id = new long[capacity]();
            i_product_name = new STRING_TYPE[capacity]();
        }

        void add(long _i_item_sk, STRING_TYPE _i_item_id, date _i_rec_start_date, date _i_rec_end_date, STRING_TYPE _i_item_desc, DOUBLE_TYPE _i_current_price, DOUBLE_TYPE _i_wholesale_cost, long _i_brand_id, STRING_TYPE _i_brand, long _i_class_id, STRING_TYPE _i_class, long _i_category_id, STRING_TYPE _i_category, long _i_manufact_id, STRING_TYPE _i_manufact, STRING_TYPE _i_size, STRING_TYPE _i_formulation, STRING_TYPE _i_color, STRING_TYPE _i_units, STRING_TYPE _i_container, long _i_manager_id, STRING_TYPE _i_product_name)
        {            
            assert(size < capacity);
            i_item_sk[size] = _i_item_sk;
            i_item_id[size] = _i_item_id;
            i_rec_start_date[size] = _i_rec_start_date;
            i_rec_end_date[size] = _i_rec_end_date;
            i_item_desc[size] = _i_item_desc;
            i_current_price[size] = _i_current_price;
            i_wholesale_cost[size] = _i_wholesale_cost;
            i_brand_id[size] = _i_brand_id;
            i_brand[size] = _i_brand;
            i_class_id[size] = _i_class_id;
            i_class[size] = _i_class;
            i_category_id[size] = _i_category_id;
            i_category[size] = _i_category;
            i_manufact_id[size] = _i_manufact_id;
            i_manufact[size] = _i_manufact;
            i_size[size] = _i_size;
            i_formulation[size] = _i_formulation;
            i_color[size] = _i_color;
            i_units[size] = _i_units;
            i_container[size] = _i_container;
            i_manager_id[size] = _i_manager_id;
            i_product_name[size] = _i_product_name;            
            size++;
        }

        ~TPCDSItemBatch()
        {
            delete[] i_item_sk;
            delete[] i_item_id;
            delete[] i_rec_start_date;
            delete[] i_rec_end_date;
            delete[] i_item_desc;
            delete[] i_current_price;
            delete[] i_wholesale_cost;
            delete[] i_brand_id;
            delete[] i_brand;
            delete[] i_class_id;
            delete[] i_class;
            delete[] i_category_id;
            delete[] i_category;
            delete[] i_manufact_id;
            delete[] i_manufact;
            delete[] i_size;
            delete[] i_formulation;
            delete[] i_color;
            delete[] i_units;
            delete[] i_container;
            delete[] i_manager_id;
            delete[] i_product_name;
        }

    };


  struct TPCDSCustomerBatch
    {
        size_t size;
        size_t capacity;

        long* c_customer_sk;
        STRING_TYPE* c_customer_id;
        long* c_current_cdemo_sk;
        long* c_current_hdemo_sk;
        long* c_current_addr_sk;
        long* c_first_shipto_date_sk;
        long* c_first_sales_date_sk;
        STRING_TYPE* c_salutation;
        STRING_TYPE* c_first_name;
        STRING_TYPE* c_last_name;
        STRING_TYPE* c_preferred_cust_flag;
        long* c_birth_day;
        long* c_birth_month;
        long* c_birth_year;
        STRING_TYPE* c_birth_country;
        STRING_TYPE* c_login;
        STRING_TYPE* c_email_address;
        STRING_TYPE* c_last_review_date;        

        TPCDSCustomerBatch(size_t c) { initCapacity(c); }

        TPCDSCustomerBatch(const TPCDSCustomerBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                c_customer_sk[i] = batch.c_customer_sk[i];
                c_customer_id[i] = batch.c_customer_id[i];
                c_current_cdemo_sk[i] = batch.c_current_cdemo_sk[i];
                c_current_hdemo_sk[i] = batch.c_current_hdemo_sk[i];
                c_current_addr_sk[i] = batch.c_current_addr_sk[i];
                c_first_shipto_date_sk[i] = batch.c_first_shipto_date_sk[i];
                c_first_sales_date_sk[i] = batch.c_first_sales_date_sk[i];
                c_salutation[i] = batch.c_salutation[i];
                c_first_name[i] = batch.c_first_name[i];
                c_last_name[i] = batch.c_last_name[i];
                c_preferred_cust_flag[i] = batch.c_preferred_cust_flag[i];
                c_birth_day[i] = batch.c_birth_day[i];
                c_birth_month[i] = batch.c_birth_month[i];
                c_birth_year[i] = batch.c_birth_year[i];
                c_birth_country[i] = batch.c_birth_country[i];
                c_login[i] = batch.c_login[i];
                c_email_address[i] = batch.c_email_address[i];
                c_last_review_date[i] = batch.c_last_review_date[i];           
            }
        }

        TPCDSCustomerBatch(std::vector<TPCDSCustomer>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                c_customer_sk[i] = items[i].c_customer_sk;
                c_customer_id[i] = items[i].c_customer_id;
                c_current_cdemo_sk[i] = items[i].c_current_cdemo_sk;
                c_current_hdemo_sk[i] = items[i].c_current_hdemo_sk;
                c_current_addr_sk[i] = items[i].c_current_addr_sk;
                c_first_shipto_date_sk[i] = items[i].c_first_shipto_date_sk;
                c_first_sales_date_sk[i] = items[i].c_first_sales_date_sk;
                c_salutation[i] = items[i].c_salutation;
                c_first_name[i] = items[i].c_first_name;
                c_last_name[i] = items[i].c_last_name;
                c_preferred_cust_flag[i] = items[i].c_preferred_cust_flag;
                c_birth_day[i] = items[i].c_birth_day;
                c_birth_month[i] = items[i].c_birth_month;
                c_birth_year[i] = items[i].c_birth_year;
                c_birth_country[i] = items[i].c_birth_country;
                c_login[i] = items[i].c_login;
                c_email_address[i] = items[i].c_email_address;
                c_last_review_date[i] = items[i].c_last_review_date;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            c_customer_sk = new long[capacity]();
            c_customer_id = new STRING_TYPE[capacity]();
            c_current_cdemo_sk = new long[capacity]();
            c_current_hdemo_sk = new long[capacity]();
            c_current_addr_sk = new long[capacity]();
            c_first_shipto_date_sk = new long[capacity]();
            c_first_sales_date_sk = new long[capacity]();
            c_salutation = new STRING_TYPE[capacity]();
            c_first_name = new STRING_TYPE[capacity]();
            c_last_name = new STRING_TYPE[capacity]();
            c_preferred_cust_flag = new STRING_TYPE[capacity]();
            c_birth_day = new long[capacity]();
            c_birth_month = new long[capacity]();
            c_birth_year = new long[capacity]();
            c_birth_country = new STRING_TYPE[capacity]();
            c_login = new STRING_TYPE[capacity]();
            c_email_address = new STRING_TYPE[capacity]();
            c_last_review_date = new STRING_TYPE[capacity]();
        }

        void add(long _c_customer_sk, STRING_TYPE _c_customer_id, long _c_current_cdemo_sk, long _c_current_hdemo_sk, long _c_current_addr_sk, long _c_first_shipto_date_sk, long _c_first_sales_date_sk, STRING_TYPE _c_salutation, STRING_TYPE _c_first_name, STRING_TYPE _c_last_name, STRING_TYPE _c_preferred_cust_flag, long _c_birth_day, long _c_birth_month, long _c_birth_year, STRING_TYPE _c_birth_country, STRING_TYPE _c_login, STRING_TYPE _c_email_address, STRING_TYPE _c_last_review_date)
        {            
            assert(size < capacity);
            c_customer_sk[size] = _c_customer_sk;
            c_customer_id[size] = _c_customer_id;
            c_current_cdemo_sk[size] = _c_current_cdemo_sk;
            c_current_hdemo_sk[size] = _c_current_hdemo_sk;
            c_current_addr_sk[size] = _c_current_addr_sk;
            c_first_shipto_date_sk[size] = _c_first_shipto_date_sk;
            c_first_sales_date_sk[size] = _c_first_sales_date_sk;
            c_salutation[size] = _c_salutation;
            c_first_name[size] = _c_first_name;
            c_last_name[size] = _c_last_name;
            c_preferred_cust_flag[size] = _c_preferred_cust_flag;
            c_birth_day[size] = _c_birth_day;
            c_birth_month[size] = _c_birth_month;
            c_birth_year[size] = _c_birth_year;
            c_birth_country[size] = _c_birth_country;
            c_login[size] = _c_login;
            c_email_address[size] = _c_email_address;
            c_last_review_date[size] = _c_last_review_date;            
            size++;
        }

        ~TPCDSCustomerBatch()
        {
            delete[] c_customer_sk;
            delete[] c_customer_id;
            delete[] c_current_cdemo_sk;
            delete[] c_current_hdemo_sk;
            delete[] c_current_addr_sk;
            delete[] c_first_shipto_date_sk;
            delete[] c_first_sales_date_sk;
            delete[] c_salutation;
            delete[] c_first_name;
            delete[] c_last_name;
            delete[] c_preferred_cust_flag;
            delete[] c_birth_day;
            delete[] c_birth_month;
            delete[] c_birth_year;
            delete[] c_birth_country;
            delete[] c_login;
            delete[] c_email_address;
            delete[] c_last_review_date;        
        }
    };   

    struct TPCDSCustomerAddressBatch
    {
        size_t size;
        size_t capacity;

        long* ca_address_sk;
        STRING_TYPE* ca_address_id;
        STRING_TYPE* ca_street_number;
        STRING_TYPE* ca_street_name;
        STRING_TYPE* ca_street_type;
        STRING_TYPE* ca_suite_number;
        STRING_TYPE* ca_city;
        STRING_TYPE* ca_county;
        STRING_TYPE* ca_state;
        STRING_TYPE* ca_zip;
        STRING_TYPE* ca_country;
        DOUBLE_TYPE* ca_gmt_offset;
        STRING_TYPE* ca_location_type;        

        TPCDSCustomerAddressBatch(size_t c) { initCapacity(c); }

        TPCDSCustomerAddressBatch(const TPCDSCustomerAddressBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                ca_address_sk[i] = batch.ca_address_sk[i];
                ca_address_id[i] = batch.ca_address_id[i];
                ca_street_number[i] = batch.ca_street_number[i];
                ca_street_name[i] = batch.ca_street_name[i];
                ca_street_type[i] = batch.ca_street_type[i];
                ca_suite_number[i] = batch.ca_suite_number[i];
                ca_city[i] = batch.ca_city[i];
                ca_county[i] = batch.ca_county[i];
                ca_state[i] = batch.ca_state[i];
                ca_zip[i] = batch.ca_zip[i];
                ca_country[i] = batch.ca_country[i];
                ca_gmt_offset[i] = batch.ca_gmt_offset[i];
                ca_location_type[i] = batch.ca_location_type[i];
            }
        }

        TPCDSCustomerAddressBatch(std::vector<TPCDSCustomerAddress>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                ca_address_sk[i] = items[i].ca_address_sk;
                ca_address_id[i] = items[i].ca_address_id;
                ca_street_number[i] = items[i].ca_street_number;
                ca_street_name[i] = items[i].ca_street_name;
                ca_street_type[i] = items[i].ca_street_type;
                ca_suite_number[i] = items[i].ca_suite_number;
                ca_city[i] = items[i].ca_city;
                ca_county[i] = items[i].ca_county;
                ca_state[i] = items[i].ca_state;
                ca_zip[i] = items[i].ca_zip;
                ca_country[i] = items[i].ca_country;
                ca_gmt_offset[i] = items[i].ca_gmt_offset;
                ca_location_type[i] = items[i].ca_location_type;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            ca_address_sk = new long[capacity]();
            ca_address_id = new STRING_TYPE[capacity]();
            ca_street_number = new STRING_TYPE[capacity]();
            ca_street_name = new STRING_TYPE[capacity]();
            ca_street_type = new STRING_TYPE[capacity]();
            ca_suite_number = new STRING_TYPE[capacity]();
            ca_city = new STRING_TYPE[capacity]();
            ca_county = new STRING_TYPE[capacity]();
            ca_state = new STRING_TYPE[capacity]();
            ca_zip = new STRING_TYPE[capacity]();
            ca_country = new STRING_TYPE[capacity]();
            ca_gmt_offset = new DOUBLE_TYPE[capacity]();
            ca_location_type = new STRING_TYPE[capacity]();
        }

        void add(long _ca_address_sk, STRING_TYPE _ca_address_id, STRING_TYPE _ca_street_number, STRING_TYPE _ca_street_name, STRING_TYPE _ca_street_type, STRING_TYPE _ca_suite_number, STRING_TYPE _ca_city, STRING_TYPE _ca_county, STRING_TYPE _ca_state, STRING_TYPE _ca_zip, STRING_TYPE _ca_country, DOUBLE_TYPE _ca_gmt_offset, STRING_TYPE _ca_location_type)
        {            
            assert(size < capacity);
            ca_address_sk[size] = _ca_address_sk;
            ca_address_id[size] = _ca_address_id;
            ca_street_number[size] = _ca_street_number;
            ca_street_name[size] = _ca_street_name;
            ca_street_type[size] = _ca_street_type;
            ca_suite_number[size] = _ca_suite_number;
            ca_city[size] = _ca_city;
            ca_county[size] = _ca_county;
            ca_state[size] = _ca_state;
            ca_zip[size] = _ca_zip;
            ca_country[size] = _ca_country;
            ca_gmt_offset[size] = _ca_gmt_offset;
            ca_location_type[size] = _ca_location_type;            
            size++;
        }

        ~TPCDSCustomerAddressBatch()
        {
            delete[] ca_address_sk;
            delete[] ca_address_id;
            delete[] ca_street_number;
            delete[] ca_street_name;
            delete[] ca_street_type;
            delete[] ca_suite_number;
            delete[] ca_city;
            delete[] ca_county;
            delete[] ca_state;
            delete[] ca_zip;
            delete[] ca_country;
            delete[] ca_gmt_offset;
            delete[] ca_location_type;
        }
    };     


    struct TPCDSStoreBatch
    {
        size_t size;
        size_t capacity;

        long* s_store_sk;
        STRING_TYPE* s_store_id;
        date* s_rec_start_date;
        date* s_rec_end_date;
        long* s_closed_date_sk;
        STRING_TYPE* s_store_name;
        long* s_number_employees;
        long* s_floor_space;
        STRING_TYPE* s_hours;
        STRING_TYPE* s_manager;
        long* s_market_id;
        STRING_TYPE* s_geography_class;
        STRING_TYPE* s_market_desc;
        STRING_TYPE* s_market_manager;
        long* s_division_id;
        STRING_TYPE* s_division_name;
        long* s_company_id;
        STRING_TYPE* s_company_name;
        STRING_TYPE* s_street_number;
        STRING_TYPE* s_street_name;
        STRING_TYPE* s_street_type;
        STRING_TYPE* s_suite_number;
        STRING_TYPE* s_city;
        STRING_TYPE* s_county;
        STRING_TYPE* s_state;
        STRING_TYPE* s_zip;
        STRING_TYPE* s_country;
        DOUBLE_TYPE* s_gmt_offset;
        DOUBLE_TYPE* s_tax_precentage;        

        TPCDSStoreBatch(size_t c) { initCapacity(c); }

        TPCDSStoreBatch(const TPCDSStoreBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                s_store_sk[i] = batch.s_store_sk[i];
                s_store_id[i] = batch.s_store_id[i];
                s_rec_start_date[i] = batch.s_rec_start_date[i];
                s_rec_end_date[i] = batch.s_rec_end_date[i];
                s_closed_date_sk[i] = batch.s_closed_date_sk[i];
                s_store_name[i] = batch.s_store_name[i];
                s_number_employees[i] = batch.s_number_employees[i];
                s_floor_space[i] = batch.s_floor_space[i];
                s_hours[i] = batch.s_hours[i];
                s_manager[i] = batch.s_manager[i];
                s_market_id[i] = batch.s_market_id[i];
                s_geography_class[i] = batch.s_geography_class[i];
                s_market_desc[i] = batch.s_market_desc[i];
                s_market_manager[i] = batch.s_market_manager[i];
                s_division_id[i] = batch.s_division_id[i];
                s_division_name[i] = batch.s_division_name[i];
                s_company_id[i] = batch.s_company_id[i];
                s_company_name[i] = batch.s_company_name[i];
                s_street_number[i] = batch.s_street_number[i];
                s_street_name[i] = batch.s_street_name[i];
                s_street_type[i] = batch.s_street_type[i];
                s_suite_number[i] = batch.s_suite_number[i];
                s_city[i] = batch.s_city[i];
                s_county[i] = batch.s_county[i];
                s_state[i] = batch.s_state[i];
                s_zip[i] = batch.s_zip[i];
                s_country[i] = batch.s_country[i];
                s_gmt_offset[i] = batch.s_gmt_offset[i];
                s_tax_precentage[i] = batch.s_tax_precentage[i];
            }
        }

        TPCDSStoreBatch(std::vector<TPCDSStore>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                s_store_sk[i] = items[i].s_store_sk;
                s_store_id[i] = items[i].s_store_id;
                s_rec_start_date[i] = items[i].s_rec_start_date;
                s_rec_end_date[i] = items[i].s_rec_end_date;
                s_closed_date_sk[i] = items[i].s_closed_date_sk;
                s_store_name[i] = items[i].s_store_name;
                s_number_employees[i] = items[i].s_number_employees;
                s_floor_space[i] = items[i].s_floor_space;
                s_hours[i] = items[i].s_hours;
                s_manager[i] = items[i].s_manager;
                s_market_id[i] = items[i].s_market_id;
                s_geography_class[i] = items[i].s_geography_class;
                s_market_desc[i] = items[i].s_market_desc;
                s_market_manager[i] = items[i].s_market_manager;
                s_division_id[i] = items[i].s_division_id;
                s_division_name[i] = items[i].s_division_name;
                s_company_id[i] = items[i].s_company_id;
                s_company_name[i] = items[i].s_company_name;
                s_street_number[i] = items[i].s_street_number;
                s_street_name[i] = items[i].s_street_name;
                s_street_type[i] = items[i].s_street_type;
                s_suite_number[i] = items[i].s_suite_number;
                s_city[i] = items[i].s_city;
                s_county[i] = items[i].s_county;
                s_state[i] = items[i].s_state;
                s_zip[i] = items[i].s_zip;
                s_country[i] = items[i].s_country;
                s_gmt_offset[i] = items[i].s_gmt_offset;
                s_tax_precentage[i] = items[i].s_tax_precentage;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            s_store_sk = new long[capacity]();
            s_store_id = new STRING_TYPE[capacity]();
            s_rec_start_date = new date[capacity]();
            s_rec_end_date = new date[capacity]();
            s_closed_date_sk = new long[capacity]();
            s_store_name = new STRING_TYPE[capacity]();
            s_number_employees = new long[capacity]();
            s_floor_space = new long[capacity]();
            s_hours = new STRING_TYPE[capacity]();
            s_manager = new STRING_TYPE[capacity]();
            s_market_id = new long[capacity]();
            s_geography_class = new STRING_TYPE[capacity]();
            s_market_desc = new STRING_TYPE[capacity]();
            s_market_manager = new STRING_TYPE[capacity]();
            s_division_id = new long[capacity]();
            s_division_name = new STRING_TYPE[capacity]();
            s_company_id = new long[capacity]();
            s_company_name = new STRING_TYPE[capacity]();
            s_street_number = new STRING_TYPE[capacity]();
            s_street_name = new STRING_TYPE[capacity]();
            s_street_type = new STRING_TYPE[capacity]();
            s_suite_number = new STRING_TYPE[capacity]();
            s_city = new STRING_TYPE[capacity]();
            s_county = new STRING_TYPE[capacity]();
            s_state = new STRING_TYPE[capacity]();
            s_zip = new STRING_TYPE[capacity]();
            s_country = new STRING_TYPE[capacity]();
            s_gmt_offset = new DOUBLE_TYPE[capacity]();
            s_tax_precentage = new DOUBLE_TYPE[capacity]();
        }

        void add(long _s_store_sk, STRING_TYPE _s_store_id, date _s_rec_start_date, date _s_rec_end_date, long _s_closed_date_sk, STRING_TYPE _s_store_name, long _s_number_employees, long _s_floor_space, STRING_TYPE _s_hours, STRING_TYPE _s_manager, long _s_market_id, STRING_TYPE _s_geography_class, STRING_TYPE _s_market_desc, STRING_TYPE _s_market_manager, long _s_division_id, STRING_TYPE _s_division_name, long _s_company_id, STRING_TYPE _s_company_name, STRING_TYPE _s_street_number, STRING_TYPE _s_street_name, STRING_TYPE _s_street_type, STRING_TYPE _s_suite_number, STRING_TYPE _s_city, STRING_TYPE _s_county, STRING_TYPE _s_state, STRING_TYPE _s_zip, STRING_TYPE _s_country, DOUBLE_TYPE _s_gmt_offset, DOUBLE_TYPE _s_tax_precentage)
        {            
            assert(size < capacity);
            s_store_sk[size] = _s_store_sk;
            s_store_id[size] = _s_store_id;
            s_rec_start_date[size] = _s_rec_start_date;
            s_rec_end_date[size] = _s_rec_end_date;
            s_closed_date_sk[size] = _s_closed_date_sk;
            s_store_name[size] = _s_store_name;
            s_number_employees[size] = _s_number_employees;
            s_floor_space[size] = _s_floor_space;
            s_hours[size] = _s_hours;
            s_manager[size] = _s_manager;
            s_market_id[size] = _s_market_id;
            s_geography_class[size] = _s_geography_class;
            s_market_desc[size] = _s_market_desc;
            s_market_manager[size] = _s_market_manager;
            s_division_id[size] = _s_division_id;
            s_division_name[size] = _s_division_name;
            s_company_id[size] = _s_company_id;
            s_company_name[size] = _s_company_name;
            s_street_number[size] = _s_street_number;
            s_street_name[size] = _s_street_name;
            s_street_type[size] = _s_street_type;
            s_suite_number[size] = _s_suite_number;
            s_city[size] = _s_city;
            s_county[size] = _s_county;
            s_state[size] = _s_state;
            s_zip[size] = _s_zip;
            s_country[size] = _s_country;
            s_gmt_offset[size] = _s_gmt_offset;
            s_tax_precentage[size] = _s_tax_precentage;            
            size++;
        }

        ~TPCDSStoreBatch()
        {
            delete[] s_store_sk;
            delete[] s_store_id;
            delete[] s_rec_start_date;
            delete[] s_rec_end_date;
            delete[] s_closed_date_sk;
            delete[] s_store_name;
            delete[] s_number_employees;
            delete[] s_floor_space;
            delete[] s_hours;
            delete[] s_manager;
            delete[] s_market_id;
            delete[] s_geography_class;
            delete[] s_market_desc;
            delete[] s_market_manager;
            delete[] s_division_id;
            delete[] s_division_name;
            delete[] s_company_id;
            delete[] s_company_name;
            delete[] s_street_number;
            delete[] s_street_name;
            delete[] s_street_type;
            delete[] s_suite_number;
            delete[] s_city;
            delete[] s_county;
            delete[] s_state;
            delete[] s_zip;
            delete[] s_country;
            delete[] s_gmt_offset;
            delete[] s_tax_precentage;
        }
    };    


  struct TPCDSHouseholdDemographicsBatch
    {
        size_t size;
        size_t capacity;

        long* hd_demo_sk;
        long* hd_income_band_sk;
        STRING_TYPE* hd_buy_potential;
        long* hd_dep_count;
        long* hd_vehicle_count;        

        TPCDSHouseholdDemographicsBatch(size_t c) { initCapacity(c); }

        TPCDSHouseholdDemographicsBatch(const TPCDSHouseholdDemographicsBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                hd_demo_sk[i] = batch.hd_demo_sk[i];
                hd_income_band_sk[i] = batch.hd_income_band_sk[i];
                hd_buy_potential[i] = batch.hd_buy_potential[i];
                hd_dep_count[i] = batch.hd_dep_count[i];
                hd_vehicle_count[i] = batch.hd_vehicle_count[i];
            }
        }

        TPCDSHouseholdDemographicsBatch(std::vector<TPCDSHouseholdDemographics>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                hd_demo_sk[i] = items[i].hd_demo_sk;
                hd_income_band_sk[i] = items[i].hd_income_band_sk;
                hd_buy_potential[i] = items[i].hd_buy_potential;
                hd_dep_count[i] = items[i].hd_dep_count;
                hd_vehicle_count[i] = items[i].hd_vehicle_count;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            hd_demo_sk = new long[capacity]();
            hd_income_band_sk = new long[capacity]();
            hd_buy_potential = new STRING_TYPE[capacity]();
            hd_dep_count = new long[capacity]();
            hd_vehicle_count = new long[capacity]();
        }

        void add(long _hd_demo_sk, long _hd_income_band_sk, STRING_TYPE _hd_buy_potential, long _hd_dep_count, long _hd_vehicle_count)
        {            
            assert(size < capacity);
            hd_demo_sk[size] = _hd_demo_sk;
            hd_income_band_sk[size] = _hd_income_band_sk;
            hd_buy_potential[size] = _hd_buy_potential;
            hd_dep_count[size] = _hd_dep_count;
            hd_vehicle_count[size] = _hd_vehicle_count;            
            size++;
        }

        ~TPCDSHouseholdDemographicsBatch()
        {
            delete[] hd_demo_sk;
            delete[] hd_income_band_sk;
            delete[] hd_buy_potential;
            delete[] hd_dep_count;
            delete[] hd_vehicle_count;        
        }
    };


  struct TPCDSCustomerDemographicsBatch
    {
        size_t size;
        size_t capacity;

        long* cd_demo_sk;
        STRING_TYPE* cd_gender;
        STRING_TYPE* cd_marital_status;
        STRING_TYPE* cd_education_status;
        long* cd_purchase_estimate;
        STRING_TYPE* cd_credit_rating;
        long* cd_dep_count;
        long* cd_dep_employed_count;
        long* cd_dep_college_count;        

        TPCDSCustomerDemographicsBatch(size_t c) { initCapacity(c); }

        TPCDSCustomerDemographicsBatch(const TPCDSCustomerDemographicsBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                cd_demo_sk[i] = batch.cd_demo_sk[i];
                cd_gender[i] = batch.cd_gender[i];
                cd_marital_status[i] = batch.cd_marital_status[i];
                cd_education_status[i] = batch.cd_education_status[i];
                cd_purchase_estimate[i] = batch.cd_purchase_estimate[i];
                cd_credit_rating[i] = batch.cd_credit_rating[i];
                cd_dep_count[i] = batch.cd_dep_count[i];
                cd_dep_employed_count[i] = batch.cd_dep_employed_count[i];
                cd_dep_college_count[i] = batch.cd_dep_college_count[i];
            }
        }

        TPCDSCustomerDemographicsBatch(std::vector<TPCDSCustomerDemographics>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                cd_demo_sk[i] = items[i].cd_demo_sk;
                cd_gender[i] = items[i].cd_gender;
                cd_marital_status[i] = items[i].cd_marital_status;
                cd_education_status[i] = items[i].cd_education_status;
                cd_purchase_estimate[i] = items[i].cd_purchase_estimate;
                cd_credit_rating[i] = items[i].cd_credit_rating;
                cd_dep_count[i] = items[i].cd_dep_count;
                cd_dep_employed_count[i] = items[i].cd_dep_employed_count;
                cd_dep_college_count[i] = items[i].cd_dep_college_count;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            cd_demo_sk = new long[capacity]();
            cd_gender = new STRING_TYPE[capacity]();
            cd_marital_status = new STRING_TYPE[capacity]();
            cd_education_status = new STRING_TYPE[capacity]();
            cd_purchase_estimate = new long[capacity]();
            cd_credit_rating = new STRING_TYPE[capacity]();
            cd_dep_count = new long[capacity]();
            cd_dep_employed_count = new long[capacity]();
            cd_dep_college_count = new long[capacity]();
        }

        void add(long _cd_demo_sk, STRING_TYPE _cd_gender, STRING_TYPE _cd_marital_status, STRING_TYPE _cd_education_status, long _cd_purchase_estimate, STRING_TYPE _cd_credit_rating, long _cd_dep_count, long _cd_dep_employed_count, long _cd_dep_college_count)
        {            
            assert(size < capacity);
            cd_demo_sk[size] = _cd_demo_sk;
            cd_gender[size] = _cd_gender;
            cd_marital_status[size] = _cd_marital_status;
            cd_education_status[size] = _cd_education_status;
            cd_purchase_estimate[size] = _cd_purchase_estimate;
            cd_credit_rating[size] = _cd_credit_rating;
            cd_dep_count[size] = _cd_dep_count;
            cd_dep_employed_count[size] = _cd_dep_employed_count;
            cd_dep_college_count[size] = _cd_dep_college_count;            
            size++;
        }

        ~TPCDSCustomerDemographicsBatch()
        {
            delete[] cd_demo_sk;
            delete[] cd_gender;
            delete[] cd_marital_status;
            delete[] cd_education_status;
            delete[] cd_purchase_estimate;
            delete[] cd_credit_rating;
            delete[] cd_dep_count;
            delete[] cd_dep_employed_count;
            delete[] cd_dep_college_count;
        }

    };    

    struct TPCDSPromotionBatch
    {
        size_t size;
        size_t capacity;

        long* p_promo_sk;
        STRING_TYPE* p_promo_id;
        long* p_start_date_sk;
        long* p_end_date_sk;
        long* p_item_sk;
        DOUBLE_TYPE* p_cost;
        long* p_response_target;
        STRING_TYPE* p_promo_name;
        STRING_TYPE* p_channel_dmail;
        STRING_TYPE* p_channel_email;
        STRING_TYPE* p_channel_catalog;
        STRING_TYPE* p_channel_tv;
        STRING_TYPE* p_channel_radio;
        STRING_TYPE* p_channel_press;
        STRING_TYPE* p_channel_event;
        STRING_TYPE* p_channel_demo;
        STRING_TYPE* p_channel_details;
        STRING_TYPE* p_purpose;
        STRING_TYPE* p_discount_active;        

        TPCDSPromotionBatch(size_t c) { initCapacity(c); }

        TPCDSPromotionBatch(const TPCDSPromotionBatch& batch) 
        {
            initCapacity(batch.size);
            size = batch.size;

            for (size_t i = 0; i < batch.size; i++)
            {
                p_promo_sk[i] = batch.p_promo_sk[i];
                p_promo_id[i] = batch.p_promo_id[i];
                p_start_date_sk[i] = batch.p_start_date_sk[i];
                p_end_date_sk[i] = batch.p_end_date_sk[i];
                p_item_sk[i] = batch.p_item_sk[i];
                p_cost[i] = batch.p_cost[i];
                p_response_target[i] = batch.p_response_target[i];
                p_promo_name[i] = batch.p_promo_name[i];
                p_channel_dmail[i] = batch.p_channel_dmail[i];
                p_channel_email[i] = batch.p_channel_email[i];
                p_channel_catalog[i] = batch.p_channel_catalog[i];
                p_channel_tv[i] = batch.p_channel_tv[i];
                p_channel_radio[i] = batch.p_channel_radio[i];
                p_channel_press[i] = batch.p_channel_press[i];
                p_channel_event[i] = batch.p_channel_event[i];
                p_channel_demo[i] = batch.p_channel_demo[i];
                p_channel_details[i] = batch.p_channel_details[i];
                p_purpose[i] = batch.p_purpose[i];
                p_discount_active[i] = batch.p_discount_active[i];
            }
        }

        TPCDSPromotionBatch(std::vector<TPCDSPromotion>& items)
        {
            initCapacity(items.size());            
            size = items.size();

            for (size_t i = 0; i < items.size(); i++)
            {
                p_promo_sk[i] = items[i].p_promo_sk;
                p_promo_id[i] = items[i].p_promo_id;
                p_start_date_sk[i] = items[i].p_start_date_sk;
                p_end_date_sk[i] = items[i].p_end_date_sk;
                p_item_sk[i] = items[i].p_item_sk;
                p_cost[i] = items[i].p_cost;
                p_response_target[i] = items[i].p_response_target;
                p_promo_name[i] = items[i].p_promo_name;
                p_channel_dmail[i] = items[i].p_channel_dmail;
                p_channel_email[i] = items[i].p_channel_email;
                p_channel_catalog[i] = items[i].p_channel_catalog;
                p_channel_tv[i] = items[i].p_channel_tv;
                p_channel_radio[i] = items[i].p_channel_radio;
                p_channel_press[i] = items[i].p_channel_press;
                p_channel_event[i] = items[i].p_channel_event;
                p_channel_demo[i] = items[i].p_channel_demo;
                p_channel_details[i] = items[i].p_channel_details;
                p_purpose[i] = items[i].p_purpose;
                p_discount_active[i] = items[i].p_discount_active;
            }
        }

        void initCapacity(size_t c) 
        {           
            assert(c > 0);
            size = 0;
            capacity = c;

            p_promo_sk = new long[capacity]();
            p_promo_id = new STRING_TYPE[capacity]();
            p_start_date_sk = new long[capacity]();
            p_end_date_sk = new long[capacity]();
            p_item_sk = new long[capacity]();
            p_cost = new DOUBLE_TYPE[capacity]();
            p_response_target = new long[capacity]();
            p_promo_name = new STRING_TYPE[capacity]();
            p_channel_dmail = new STRING_TYPE[capacity]();
            p_channel_email = new STRING_TYPE[capacity]();
            p_channel_catalog = new STRING_TYPE[capacity]();
            p_channel_tv = new STRING_TYPE[capacity]();
            p_channel_radio = new STRING_TYPE[capacity]();
            p_channel_press = new STRING_TYPE[capacity]();
            p_channel_event = new STRING_TYPE[capacity]();
            p_channel_demo = new STRING_TYPE[capacity]();
            p_channel_details = new STRING_TYPE[capacity]();
            p_purpose = new STRING_TYPE[capacity]();
            p_discount_active = new STRING_TYPE[capacity]();
        }

        void add(long _p_promo_sk, STRING_TYPE _p_promo_id, long _p_start_date_sk, long _p_end_date_sk, long _p_item_sk, DOUBLE_TYPE _p_cost, long _p_response_target, STRING_TYPE _p_promo_name, STRING_TYPE _p_channel_dmail, STRING_TYPE _p_channel_email, STRING_TYPE _p_channel_catalog, STRING_TYPE _p_channel_tv, STRING_TYPE _p_channel_radio, STRING_TYPE _p_channel_press, STRING_TYPE _p_channel_event, STRING_TYPE _p_channel_demo, STRING_TYPE _p_channel_details, STRING_TYPE _p_purpose, STRING_TYPE _p_discount_active)
        {            
            assert(size < capacity);
            p_promo_sk[size] = _p_promo_sk;
            p_promo_id[size] = _p_promo_id;
            p_start_date_sk[size] = _p_start_date_sk;
            p_end_date_sk[size] = _p_end_date_sk;
            p_item_sk[size] = _p_item_sk;
            p_cost[size] = _p_cost;
            p_response_target[size] = _p_response_target;
            p_promo_name[size] = _p_promo_name;
            p_channel_dmail[size] = _p_channel_dmail;
            p_channel_email[size] = _p_channel_email;
            p_channel_catalog[size] = _p_channel_catalog;
            p_channel_tv[size] = _p_channel_tv;
            p_channel_radio[size] = _p_channel_radio;
            p_channel_press[size] = _p_channel_press;
            p_channel_event[size] = _p_channel_event;
            p_channel_demo[size] = _p_channel_demo;
            p_channel_details[size] = _p_channel_details;
            p_purpose[size] = _p_purpose;
            p_discount_active[size] = _p_discount_active;            
            size++;
        }

        ~TPCDSPromotionBatch()
        {
            delete[] p_promo_sk;
            delete[] p_promo_id;
            delete[] p_start_date_sk;
            delete[] p_end_date_sk;
            delete[] p_item_sk;
            delete[] p_cost;
            delete[] p_response_target;
            delete[] p_promo_name;
            delete[] p_channel_dmail;
            delete[] p_channel_email;
            delete[] p_channel_catalog;
            delete[] p_channel_tv;
            delete[] p_channel_radio;
            delete[] p_channel_press;
            delete[] p_channel_event;
            delete[] p_channel_demo;
            delete[] p_channel_details;
            delete[] p_purpose;
            delete[] p_discount_active;
        }

    };    
}

#endif /* DBTOASTER_TEST_TPCDS_HPP */
