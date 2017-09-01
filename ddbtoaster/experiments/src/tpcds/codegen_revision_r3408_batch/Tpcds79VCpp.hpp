#include <sys/time.h>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "hashmap.hpp"
#include "serialization.hpp"
#include "tpcds.hpp"

#define ELEM_SEPARATOR "\n\t\t\t"

namespace dbtoaster {
  
  /* Definitions of auxiliary maps for storing materialized views. */
  struct DELTA_STORE_SALES_entry {
    long store_sales_ss_sold_date_sk; long store_sales_ss_sold_time_sk; long store_sales_ss_item_sk; long store_sales_ss_customer_sk; long store_sales_ss_cdemo_sk; long store_sales_ss_hdemo_sk; long store_sales_ss_addr_sk; long store_sales_ss_store_sk; long store_sales_ss_promo_sk; long store_sales_ss_ticket_number; long store_sales_ss_quantity; DOUBLE_TYPE store_sales_ss_wholesale_cost; DOUBLE_TYPE store_sales_ss_list_price; DOUBLE_TYPE store_sales_ss_sales_price; DOUBLE_TYPE store_sales_ss_ext_discount_amt; DOUBLE_TYPE store_sales_ss_ext_sales_price; DOUBLE_TYPE store_sales_ss_ext_wholesale_cost; DOUBLE_TYPE store_sales_ss_ext_list_price; DOUBLE_TYPE store_sales_ss_ext_tax; DOUBLE_TYPE store_sales_ss_coupon_amt; DOUBLE_TYPE store_sales_ss_net_paid; DOUBLE_TYPE store_sales_ss_net_paid_inc_tax; DOUBLE_TYPE store_sales_ss_net_profit; long __av; 
    explicit DELTA_STORE_SALES_entry() { /*store_sales_ss_sold_date_sk = 0L; store_sales_ss_sold_time_sk = 0L; store_sales_ss_item_sk = 0L; store_sales_ss_customer_sk = 0L; store_sales_ss_cdemo_sk = 0L; store_sales_ss_hdemo_sk = 0L; store_sales_ss_addr_sk = 0L; store_sales_ss_store_sk = 0L; store_sales_ss_promo_sk = 0L; store_sales_ss_ticket_number = 0L; store_sales_ss_quantity = 0L; store_sales_ss_wholesale_cost = 0.0; store_sales_ss_list_price = 0.0; store_sales_ss_sales_price = 0.0; store_sales_ss_ext_discount_amt = 0.0; store_sales_ss_ext_sales_price = 0.0; store_sales_ss_ext_wholesale_cost = 0.0; store_sales_ss_ext_list_price = 0.0; store_sales_ss_ext_tax = 0.0; store_sales_ss_coupon_amt = 0.0; store_sales_ss_net_paid = 0.0; store_sales_ss_net_paid_inc_tax = 0.0; store_sales_ss_net_profit = 0.0; __av = 0L; */ }
    explicit DELTA_STORE_SALES_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const DOUBLE_TYPE c15, const DOUBLE_TYPE c16, const DOUBLE_TYPE c17, const DOUBLE_TYPE c18, const DOUBLE_TYPE c19, const DOUBLE_TYPE c20, const DOUBLE_TYPE c21, const DOUBLE_TYPE c22, const long c23) { store_sales_ss_sold_date_sk = c0; store_sales_ss_sold_time_sk = c1; store_sales_ss_item_sk = c2; store_sales_ss_customer_sk = c3; store_sales_ss_cdemo_sk = c4; store_sales_ss_hdemo_sk = c5; store_sales_ss_addr_sk = c6; store_sales_ss_store_sk = c7; store_sales_ss_promo_sk = c8; store_sales_ss_ticket_number = c9; store_sales_ss_quantity = c10; store_sales_ss_wholesale_cost = c11; store_sales_ss_list_price = c12; store_sales_ss_sales_price = c13; store_sales_ss_ext_discount_amt = c14; store_sales_ss_ext_sales_price = c15; store_sales_ss_ext_wholesale_cost = c16; store_sales_ss_ext_list_price = c17; store_sales_ss_ext_tax = c18; store_sales_ss_coupon_amt = c19; store_sales_ss_net_paid = c20; store_sales_ss_net_paid_inc_tax = c21; store_sales_ss_net_profit = c22; __av = c23; }
    DELTA_STORE_SALES_entry(const DELTA_STORE_SALES_entry& other) : store_sales_ss_sold_date_sk( other.store_sales_ss_sold_date_sk ), store_sales_ss_sold_time_sk( other.store_sales_ss_sold_time_sk ), store_sales_ss_item_sk( other.store_sales_ss_item_sk ), store_sales_ss_customer_sk( other.store_sales_ss_customer_sk ), store_sales_ss_cdemo_sk( other.store_sales_ss_cdemo_sk ), store_sales_ss_hdemo_sk( other.store_sales_ss_hdemo_sk ), store_sales_ss_addr_sk( other.store_sales_ss_addr_sk ), store_sales_ss_store_sk( other.store_sales_ss_store_sk ), store_sales_ss_promo_sk( other.store_sales_ss_promo_sk ), store_sales_ss_ticket_number( other.store_sales_ss_ticket_number ), store_sales_ss_quantity( other.store_sales_ss_quantity ), store_sales_ss_wholesale_cost( other.store_sales_ss_wholesale_cost ), store_sales_ss_list_price( other.store_sales_ss_list_price ), store_sales_ss_sales_price( other.store_sales_ss_sales_price ), store_sales_ss_ext_discount_amt( other.store_sales_ss_ext_discount_amt ), store_sales_ss_ext_sales_price( other.store_sales_ss_ext_sales_price ), store_sales_ss_ext_wholesale_cost( other.store_sales_ss_ext_wholesale_cost ), store_sales_ss_ext_list_price( other.store_sales_ss_ext_list_price ), store_sales_ss_ext_tax( other.store_sales_ss_ext_tax ), store_sales_ss_coupon_amt( other.store_sales_ss_coupon_amt ), store_sales_ss_net_paid( other.store_sales_ss_net_paid ), store_sales_ss_net_paid_inc_tax( other.store_sales_ss_net_paid_inc_tax ), store_sales_ss_net_profit( other.store_sales_ss_net_profit ), __av( other.__av ) {}
    FORCE_INLINE DELTA_STORE_SALES_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const DOUBLE_TYPE c15, const DOUBLE_TYPE c16, const DOUBLE_TYPE c17, const DOUBLE_TYPE c18, const DOUBLE_TYPE c19, const DOUBLE_TYPE c20, const DOUBLE_TYPE c21, const DOUBLE_TYPE c22) { store_sales_ss_sold_date_sk = c0; store_sales_ss_sold_time_sk = c1; store_sales_ss_item_sk = c2; store_sales_ss_customer_sk = c3; store_sales_ss_cdemo_sk = c4; store_sales_ss_hdemo_sk = c5; store_sales_ss_addr_sk = c6; store_sales_ss_store_sk = c7; store_sales_ss_promo_sk = c8; store_sales_ss_ticket_number = c9; store_sales_ss_quantity = c10; store_sales_ss_wholesale_cost = c11; store_sales_ss_list_price = c12; store_sales_ss_sales_price = c13; store_sales_ss_ext_discount_amt = c14; store_sales_ss_ext_sales_price = c15; store_sales_ss_ext_wholesale_cost = c16; store_sales_ss_ext_list_price = c17; store_sales_ss_ext_tax = c18; store_sales_ss_coupon_amt = c19; store_sales_ss_net_paid = c20; store_sales_ss_net_paid_inc_tax = c21; store_sales_ss_net_profit = c22;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_sold_date_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_sold_time_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_item_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_customer_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_cdemo_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_hdemo_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_addr_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_store_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_promo_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_ticket_number);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_quantity);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_wholesale_cost);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_list_price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_sales_price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_ext_discount_amt);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_ext_sales_price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_ext_wholesale_cost);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_ext_list_price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_ext_tax);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_coupon_amt);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_net_paid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_net_paid_inc_tax);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_sales_ss_net_profit);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_STORE_SALES_mapkey012345678910111213141516171819202122_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_STORE_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.store_sales_ss_sold_date_sk);
      hash_combine(h, e.store_sales_ss_sold_time_sk);
      hash_combine(h, e.store_sales_ss_item_sk);
      hash_combine(h, e.store_sales_ss_customer_sk);
      hash_combine(h, e.store_sales_ss_cdemo_sk);
      hash_combine(h, e.store_sales_ss_hdemo_sk);
      hash_combine(h, e.store_sales_ss_addr_sk);
      hash_combine(h, e.store_sales_ss_store_sk);
      hash_combine(h, e.store_sales_ss_promo_sk);
      hash_combine(h, e.store_sales_ss_ticket_number);
      hash_combine(h, e.store_sales_ss_quantity);
      hash_combine(h, e.store_sales_ss_wholesale_cost);
      hash_combine(h, e.store_sales_ss_list_price);
      hash_combine(h, e.store_sales_ss_sales_price);
      hash_combine(h, e.store_sales_ss_ext_discount_amt);
      hash_combine(h, e.store_sales_ss_ext_sales_price);
      hash_combine(h, e.store_sales_ss_ext_wholesale_cost);
      hash_combine(h, e.store_sales_ss_ext_list_price);
      hash_combine(h, e.store_sales_ss_ext_tax);
      hash_combine(h, e.store_sales_ss_coupon_amt);
      hash_combine(h, e.store_sales_ss_net_paid);
      hash_combine(h, e.store_sales_ss_net_paid_inc_tax);
      hash_combine(h, e.store_sales_ss_net_profit);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_STORE_SALES_entry& x, const DELTA_STORE_SALES_entry& y) {
      return x.store_sales_ss_sold_date_sk == y.store_sales_ss_sold_date_sk && x.store_sales_ss_sold_time_sk == y.store_sales_ss_sold_time_sk && x.store_sales_ss_item_sk == y.store_sales_ss_item_sk && x.store_sales_ss_customer_sk == y.store_sales_ss_customer_sk && x.store_sales_ss_cdemo_sk == y.store_sales_ss_cdemo_sk && x.store_sales_ss_hdemo_sk == y.store_sales_ss_hdemo_sk && x.store_sales_ss_addr_sk == y.store_sales_ss_addr_sk && x.store_sales_ss_store_sk == y.store_sales_ss_store_sk && x.store_sales_ss_promo_sk == y.store_sales_ss_promo_sk && x.store_sales_ss_ticket_number == y.store_sales_ss_ticket_number && x.store_sales_ss_quantity == y.store_sales_ss_quantity && x.store_sales_ss_wholesale_cost == y.store_sales_ss_wholesale_cost && x.store_sales_ss_list_price == y.store_sales_ss_list_price && x.store_sales_ss_sales_price == y.store_sales_ss_sales_price && x.store_sales_ss_ext_discount_amt == y.store_sales_ss_ext_discount_amt && x.store_sales_ss_ext_sales_price == y.store_sales_ss_ext_sales_price && x.store_sales_ss_ext_wholesale_cost == y.store_sales_ss_ext_wholesale_cost && x.store_sales_ss_ext_list_price == y.store_sales_ss_ext_list_price && x.store_sales_ss_ext_tax == y.store_sales_ss_ext_tax && x.store_sales_ss_coupon_amt == y.store_sales_ss_coupon_amt && x.store_sales_ss_net_paid == y.store_sales_ss_net_paid && x.store_sales_ss_net_paid_inc_tax == y.store_sales_ss_net_paid_inc_tax && x.store_sales_ss_net_profit == y.store_sales_ss_net_profit;
    }
  };
  
  typedef MultiHashMap<DELTA_STORE_SALES_entry,long,
    HashIndex<DELTA_STORE_SALES_entry,long,DELTA_STORE_SALES_mapkey012345678910111213141516171819202122_idxfn,true>
  > DELTA_STORE_SALES_map;
  typedef HashIndex<DELTA_STORE_SALES_entry,long,DELTA_STORE_SALES_mapkey012345678910111213141516171819202122_idxfn,true> HashIndex_DELTA_STORE_SALES_map_012345678910111213141516171819202122;
  
  struct DELTA_CUSTOMER_entry {
    long customer_c_customer_sk; STRING_TYPE customer_c_customer_id; long customer_c_current_cdemo_sk; long customer_c_current_hdemo_sk; long customer_c_current_addr_sk; long customer_c_first_shipto_date_sk; long customer_c_first_sales_date_sk; STRING_TYPE customer_c_salutation; STRING_TYPE customer_c_first_name; STRING_TYPE customer_c_last_name; STRING_TYPE customer_c_preferred_cust_flag; long customer_c_birth_day; long customer_c_birth_month; long customer_c_birth_year; STRING_TYPE customer_c_birth_country; STRING_TYPE customer_c_login; STRING_TYPE customer_c_email_address; STRING_TYPE customer_c_last_review_date; long __av; 
    explicit DELTA_CUSTOMER_entry() { /*customer_c_customer_sk = 0L; customer_c_customer_id = ""; customer_c_current_cdemo_sk = 0L; customer_c_current_hdemo_sk = 0L; customer_c_current_addr_sk = 0L; customer_c_first_shipto_date_sk = 0L; customer_c_first_sales_date_sk = 0L; customer_c_salutation = ""; customer_c_first_name = ""; customer_c_last_name = ""; customer_c_preferred_cust_flag = ""; customer_c_birth_day = 0L; customer_c_birth_month = 0L; customer_c_birth_year = 0L; customer_c_birth_country = ""; customer_c_login = ""; customer_c_email_address = ""; customer_c_last_review_date = ""; __av = 0L; */ }
    explicit DELTA_CUSTOMER_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3, const long c4, const long c5, const long c6, const STRING_TYPE& c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const STRING_TYPE& c10, const long c11, const long c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const long c18) { customer_c_customer_sk = c0; customer_c_customer_id = c1; customer_c_current_cdemo_sk = c2; customer_c_current_hdemo_sk = c3; customer_c_current_addr_sk = c4; customer_c_first_shipto_date_sk = c5; customer_c_first_sales_date_sk = c6; customer_c_salutation = c7; customer_c_first_name = c8; customer_c_last_name = c9; customer_c_preferred_cust_flag = c10; customer_c_birth_day = c11; customer_c_birth_month = c12; customer_c_birth_year = c13; customer_c_birth_country = c14; customer_c_login = c15; customer_c_email_address = c16; customer_c_last_review_date = c17; __av = c18; }
    DELTA_CUSTOMER_entry(const DELTA_CUSTOMER_entry& other) : customer_c_customer_sk( other.customer_c_customer_sk ), customer_c_customer_id( other.customer_c_customer_id ), customer_c_current_cdemo_sk( other.customer_c_current_cdemo_sk ), customer_c_current_hdemo_sk( other.customer_c_current_hdemo_sk ), customer_c_current_addr_sk( other.customer_c_current_addr_sk ), customer_c_first_shipto_date_sk( other.customer_c_first_shipto_date_sk ), customer_c_first_sales_date_sk( other.customer_c_first_sales_date_sk ), customer_c_salutation( other.customer_c_salutation ), customer_c_first_name( other.customer_c_first_name ), customer_c_last_name( other.customer_c_last_name ), customer_c_preferred_cust_flag( other.customer_c_preferred_cust_flag ), customer_c_birth_day( other.customer_c_birth_day ), customer_c_birth_month( other.customer_c_birth_month ), customer_c_birth_year( other.customer_c_birth_year ), customer_c_birth_country( other.customer_c_birth_country ), customer_c_login( other.customer_c_login ), customer_c_email_address( other.customer_c_email_address ), customer_c_last_review_date( other.customer_c_last_review_date ), __av( other.__av ) {}
    FORCE_INLINE DELTA_CUSTOMER_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const long c3, const long c4, const long c5, const long c6, const STRING_TYPE& c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const STRING_TYPE& c10, const long c11, const long c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17) { customer_c_customer_sk = c0; customer_c_customer_id = c1; customer_c_current_cdemo_sk = c2; customer_c_current_hdemo_sk = c3; customer_c_current_addr_sk = c4; customer_c_first_shipto_date_sk = c5; customer_c_first_sales_date_sk = c6; customer_c_salutation = c7; customer_c_first_name = c8; customer_c_last_name = c9; customer_c_preferred_cust_flag = c10; customer_c_birth_day = c11; customer_c_birth_month = c12; customer_c_birth_year = c13; customer_c_birth_country = c14; customer_c_login = c15; customer_c_email_address = c16; customer_c_last_review_date = c17;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_customer_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_customer_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_current_cdemo_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_current_hdemo_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_current_addr_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_first_shipto_date_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_first_sales_date_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_salutation);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_first_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_last_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_preferred_cust_flag);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_birth_day);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_birth_month);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_birth_year);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_birth_country);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_login);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_email_address);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_c_last_review_date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_CUSTOMER_mapkey01234567891011121314151617_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_CUSTOMER_entry& e) {
      size_t h = 0;
      hash_combine(h, e.customer_c_customer_sk);
      hash_combine(h, e.customer_c_customer_id);
      hash_combine(h, e.customer_c_current_cdemo_sk);
      hash_combine(h, e.customer_c_current_hdemo_sk);
      hash_combine(h, e.customer_c_current_addr_sk);
      hash_combine(h, e.customer_c_first_shipto_date_sk);
      hash_combine(h, e.customer_c_first_sales_date_sk);
      hash_combine(h, e.customer_c_salutation);
      hash_combine(h, e.customer_c_first_name);
      hash_combine(h, e.customer_c_last_name);
      hash_combine(h, e.customer_c_preferred_cust_flag);
      hash_combine(h, e.customer_c_birth_day);
      hash_combine(h, e.customer_c_birth_month);
      hash_combine(h, e.customer_c_birth_year);
      hash_combine(h, e.customer_c_birth_country);
      hash_combine(h, e.customer_c_login);
      hash_combine(h, e.customer_c_email_address);
      hash_combine(h, e.customer_c_last_review_date);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_CUSTOMER_entry& x, const DELTA_CUSTOMER_entry& y) {
      return x.customer_c_customer_sk == y.customer_c_customer_sk && x.customer_c_customer_id == y.customer_c_customer_id && x.customer_c_current_cdemo_sk == y.customer_c_current_cdemo_sk && x.customer_c_current_hdemo_sk == y.customer_c_current_hdemo_sk && x.customer_c_current_addr_sk == y.customer_c_current_addr_sk && x.customer_c_first_shipto_date_sk == y.customer_c_first_shipto_date_sk && x.customer_c_first_sales_date_sk == y.customer_c_first_sales_date_sk && x.customer_c_salutation == y.customer_c_salutation && x.customer_c_first_name == y.customer_c_first_name && x.customer_c_last_name == y.customer_c_last_name && x.customer_c_preferred_cust_flag == y.customer_c_preferred_cust_flag && x.customer_c_birth_day == y.customer_c_birth_day && x.customer_c_birth_month == y.customer_c_birth_month && x.customer_c_birth_year == y.customer_c_birth_year && x.customer_c_birth_country == y.customer_c_birth_country && x.customer_c_login == y.customer_c_login && x.customer_c_email_address == y.customer_c_email_address && x.customer_c_last_review_date == y.customer_c_last_review_date;
    }
  };
  
  typedef MultiHashMap<DELTA_CUSTOMER_entry,long,
    HashIndex<DELTA_CUSTOMER_entry,long,DELTA_CUSTOMER_mapkey01234567891011121314151617_idxfn,true>
  > DELTA_CUSTOMER_map;
  typedef HashIndex<DELTA_CUSTOMER_entry,long,DELTA_CUSTOMER_mapkey01234567891011121314151617_idxfn,true> HashIndex_DELTA_CUSTOMER_map_01234567891011121314151617;
  
  struct DELTA_STORE_entry {
    long store_s_store_sk; STRING_TYPE store_s_store_id; date store_s_rec_start_date; date store_s_rec_end_date; long store_s_closed_date_sk; STRING_TYPE store_s_store_name; long store_s_number_employees; long store_s_floor_space; STRING_TYPE store_s_hours; STRING_TYPE store_s_manager; long store_s_market_id; STRING_TYPE store_s_geography_class; STRING_TYPE store_s_market_desc; STRING_TYPE store_s_market_manager; long store_s_division_id; STRING_TYPE store_s_division_name; long store_s_company_id; STRING_TYPE store_s_company_name; STRING_TYPE store_s_street_number; STRING_TYPE store_s_street_name; STRING_TYPE store_s_street_type; STRING_TYPE store_s_suite_number; STRING_TYPE store_s_city; STRING_TYPE store_s_county; STRING_TYPE store_s_state; STRING_TYPE store_s_zip; STRING_TYPE store_s_country; DOUBLE_TYPE store_s_gmt_offset; DOUBLE_TYPE store_s_tax_precentage; long __av; 
    explicit DELTA_STORE_entry() { /*store_s_store_sk = 0L; store_s_store_id = ""; store_s_rec_start_date = 00000000; store_s_rec_end_date = 00000000; store_s_closed_date_sk = 0L; store_s_store_name = ""; store_s_number_employees = 0L; store_s_floor_space = 0L; store_s_hours = ""; store_s_manager = ""; store_s_market_id = 0L; store_s_geography_class = ""; store_s_market_desc = ""; store_s_market_manager = ""; store_s_division_id = 0L; store_s_division_name = ""; store_s_company_id = 0L; store_s_company_name = ""; store_s_street_number = ""; store_s_street_name = ""; store_s_street_type = ""; store_s_suite_number = ""; store_s_city = ""; store_s_county = ""; store_s_state = ""; store_s_zip = ""; store_s_country = ""; store_s_gmt_offset = 0.0; store_s_tax_precentage = 0.0; __av = 0L; */ }
    explicit DELTA_STORE_entry(const long c0, const STRING_TYPE& c1, const date c2, const date c3, const long c4, const STRING_TYPE& c5, const long c6, const long c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const long c10, const STRING_TYPE& c11, const STRING_TYPE& c12, const STRING_TYPE& c13, const long c14, const STRING_TYPE& c15, const long c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const STRING_TYPE& c19, const STRING_TYPE& c20, const STRING_TYPE& c21, const STRING_TYPE& c22, const STRING_TYPE& c23, const STRING_TYPE& c24, const STRING_TYPE& c25, const STRING_TYPE& c26, const DOUBLE_TYPE c27, const DOUBLE_TYPE c28, const long c29) { store_s_store_sk = c0; store_s_store_id = c1; store_s_rec_start_date = c2; store_s_rec_end_date = c3; store_s_closed_date_sk = c4; store_s_store_name = c5; store_s_number_employees = c6; store_s_floor_space = c7; store_s_hours = c8; store_s_manager = c9; store_s_market_id = c10; store_s_geography_class = c11; store_s_market_desc = c12; store_s_market_manager = c13; store_s_division_id = c14; store_s_division_name = c15; store_s_company_id = c16; store_s_company_name = c17; store_s_street_number = c18; store_s_street_name = c19; store_s_street_type = c20; store_s_suite_number = c21; store_s_city = c22; store_s_county = c23; store_s_state = c24; store_s_zip = c25; store_s_country = c26; store_s_gmt_offset = c27; store_s_tax_precentage = c28; __av = c29; }
    DELTA_STORE_entry(const DELTA_STORE_entry& other) : store_s_store_sk( other.store_s_store_sk ), store_s_store_id( other.store_s_store_id ), store_s_rec_start_date( other.store_s_rec_start_date ), store_s_rec_end_date( other.store_s_rec_end_date ), store_s_closed_date_sk( other.store_s_closed_date_sk ), store_s_store_name( other.store_s_store_name ), store_s_number_employees( other.store_s_number_employees ), store_s_floor_space( other.store_s_floor_space ), store_s_hours( other.store_s_hours ), store_s_manager( other.store_s_manager ), store_s_market_id( other.store_s_market_id ), store_s_geography_class( other.store_s_geography_class ), store_s_market_desc( other.store_s_market_desc ), store_s_market_manager( other.store_s_market_manager ), store_s_division_id( other.store_s_division_id ), store_s_division_name( other.store_s_division_name ), store_s_company_id( other.store_s_company_id ), store_s_company_name( other.store_s_company_name ), store_s_street_number( other.store_s_street_number ), store_s_street_name( other.store_s_street_name ), store_s_street_type( other.store_s_street_type ), store_s_suite_number( other.store_s_suite_number ), store_s_city( other.store_s_city ), store_s_county( other.store_s_county ), store_s_state( other.store_s_state ), store_s_zip( other.store_s_zip ), store_s_country( other.store_s_country ), store_s_gmt_offset( other.store_s_gmt_offset ), store_s_tax_precentage( other.store_s_tax_precentage ), __av( other.__av ) {}
    FORCE_INLINE DELTA_STORE_entry& modify(const long c0, const STRING_TYPE& c1, const date c2, const date c3, const long c4, const STRING_TYPE& c5, const long c6, const long c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const long c10, const STRING_TYPE& c11, const STRING_TYPE& c12, const STRING_TYPE& c13, const long c14, const STRING_TYPE& c15, const long c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const STRING_TYPE& c19, const STRING_TYPE& c20, const STRING_TYPE& c21, const STRING_TYPE& c22, const STRING_TYPE& c23, const STRING_TYPE& c24, const STRING_TYPE& c25, const STRING_TYPE& c26, const DOUBLE_TYPE c27, const DOUBLE_TYPE c28) { store_s_store_sk = c0; store_s_store_id = c1; store_s_rec_start_date = c2; store_s_rec_end_date = c3; store_s_closed_date_sk = c4; store_s_store_name = c5; store_s_number_employees = c6; store_s_floor_space = c7; store_s_hours = c8; store_s_manager = c9; store_s_market_id = c10; store_s_geography_class = c11; store_s_market_desc = c12; store_s_market_manager = c13; store_s_division_id = c14; store_s_division_name = c15; store_s_company_id = c16; store_s_company_name = c17; store_s_street_number = c18; store_s_street_name = c19; store_s_street_type = c20; store_s_suite_number = c21; store_s_city = c22; store_s_county = c23; store_s_state = c24; store_s_zip = c25; store_s_country = c26; store_s_gmt_offset = c27; store_s_tax_precentage = c28;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_store_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_store_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_rec_start_date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_rec_end_date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_closed_date_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_store_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_number_employees);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_floor_space);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_hours);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_manager);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_market_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_geography_class);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_market_desc);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_market_manager);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_division_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_division_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_company_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_company_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_street_number);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_street_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_street_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_suite_number);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_city);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_county);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_state);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_country);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_gmt_offset);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_s_tax_precentage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_STORE_mapkey012345678910111213141516171819202122232425262728_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_STORE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.store_s_store_sk);
      hash_combine(h, e.store_s_store_id);
      hash_combine(h, e.store_s_rec_start_date);
      hash_combine(h, e.store_s_rec_end_date);
      hash_combine(h, e.store_s_closed_date_sk);
      hash_combine(h, e.store_s_store_name);
      hash_combine(h, e.store_s_number_employees);
      hash_combine(h, e.store_s_floor_space);
      hash_combine(h, e.store_s_hours);
      hash_combine(h, e.store_s_manager);
      hash_combine(h, e.store_s_market_id);
      hash_combine(h, e.store_s_geography_class);
      hash_combine(h, e.store_s_market_desc);
      hash_combine(h, e.store_s_market_manager);
      hash_combine(h, e.store_s_division_id);
      hash_combine(h, e.store_s_division_name);
      hash_combine(h, e.store_s_company_id);
      hash_combine(h, e.store_s_company_name);
      hash_combine(h, e.store_s_street_number);
      hash_combine(h, e.store_s_street_name);
      hash_combine(h, e.store_s_street_type);
      hash_combine(h, e.store_s_suite_number);
      hash_combine(h, e.store_s_city);
      hash_combine(h, e.store_s_county);
      hash_combine(h, e.store_s_state);
      hash_combine(h, e.store_s_zip);
      hash_combine(h, e.store_s_country);
      hash_combine(h, e.store_s_gmt_offset);
      hash_combine(h, e.store_s_tax_precentage);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_STORE_entry& x, const DELTA_STORE_entry& y) {
      return x.store_s_store_sk == y.store_s_store_sk && x.store_s_store_id == y.store_s_store_id && x.store_s_rec_start_date == y.store_s_rec_start_date && x.store_s_rec_end_date == y.store_s_rec_end_date && x.store_s_closed_date_sk == y.store_s_closed_date_sk && x.store_s_store_name == y.store_s_store_name && x.store_s_number_employees == y.store_s_number_employees && x.store_s_floor_space == y.store_s_floor_space && x.store_s_hours == y.store_s_hours && x.store_s_manager == y.store_s_manager && x.store_s_market_id == y.store_s_market_id && x.store_s_geography_class == y.store_s_geography_class && x.store_s_market_desc == y.store_s_market_desc && x.store_s_market_manager == y.store_s_market_manager && x.store_s_division_id == y.store_s_division_id && x.store_s_division_name == y.store_s_division_name && x.store_s_company_id == y.store_s_company_id && x.store_s_company_name == y.store_s_company_name && x.store_s_street_number == y.store_s_street_number && x.store_s_street_name == y.store_s_street_name && x.store_s_street_type == y.store_s_street_type && x.store_s_suite_number == y.store_s_suite_number && x.store_s_city == y.store_s_city && x.store_s_county == y.store_s_county && x.store_s_state == y.store_s_state && x.store_s_zip == y.store_s_zip && x.store_s_country == y.store_s_country && x.store_s_gmt_offset == y.store_s_gmt_offset && x.store_s_tax_precentage == y.store_s_tax_precentage;
    }
  };
  
  typedef MultiHashMap<DELTA_STORE_entry,long,
    HashIndex<DELTA_STORE_entry,long,DELTA_STORE_mapkey012345678910111213141516171819202122232425262728_idxfn,true>
  > DELTA_STORE_map;
  typedef HashIndex<DELTA_STORE_entry,long,DELTA_STORE_mapkey012345678910111213141516171819202122232425262728_idxfn,true> HashIndex_DELTA_STORE_map_012345678910111213141516171819202122232425262728;
  
  struct DATE_DIM_entry {
    long DATE_DIM_D_DATE_SK; STRING_TYPE DATE_DIM_D_DATE_ID; date DATE_DIM_D_DATE; long DATE_DIM_D_MONTH_SEQ; long DATE_DIM_D_WEEK_SEQ; long DATE_DIM_D_QUARTER_SEQ; long DATE_DIM_D_YEAR; long DATE_DIM_D_DOW; long DATE_DIM_D_MOY; long DATE_DIM_D_DOM; long DATE_DIM_D_QOY; long DATE_DIM_D_FY_YEAR; long DATE_DIM_D_FY_QUARTER_SEQ; long DATE_DIM_D_FY_WEEK_SEQ; STRING_TYPE DATE_DIM_D_DAY_NAME; STRING_TYPE DATE_DIM_D_QUARTER_NAME; STRING_TYPE DATE_DIM_D_HOLIDAY; STRING_TYPE DATE_DIM_D_WEEKEND; STRING_TYPE DATE_DIM_D_FOLLOWING_HOLIDAY; long DATE_DIM_D_FIRST_DOM; long DATE_DIM_D_LAST_DOM; long DATE_DIM_D_SAME_DAY_LY; long DATE_DIM_D_SAME_DAY_LQ; STRING_TYPE DATE_DIM_D_CURRENT_DAY; STRING_TYPE DATE_DIM_D_CURRENT_WEEK; STRING_TYPE DATE_DIM_D_CURRENT_MONTH; STRING_TYPE DATE_DIM_D_CURRENT_QUARTER; STRING_TYPE DATE_DIM_D_CURRENT_YEAR; long __av; 
    explicit DATE_DIM_entry() { /*DATE_DIM_D_DATE_SK = 0L; DATE_DIM_D_DATE_ID = ""; DATE_DIM_D_DATE = 00000000; DATE_DIM_D_MONTH_SEQ = 0L; DATE_DIM_D_WEEK_SEQ = 0L; DATE_DIM_D_QUARTER_SEQ = 0L; DATE_DIM_D_YEAR = 0L; DATE_DIM_D_DOW = 0L; DATE_DIM_D_MOY = 0L; DATE_DIM_D_DOM = 0L; DATE_DIM_D_QOY = 0L; DATE_DIM_D_FY_YEAR = 0L; DATE_DIM_D_FY_QUARTER_SEQ = 0L; DATE_DIM_D_FY_WEEK_SEQ = 0L; DATE_DIM_D_DAY_NAME = ""; DATE_DIM_D_QUARTER_NAME = ""; DATE_DIM_D_HOLIDAY = ""; DATE_DIM_D_WEEKEND = ""; DATE_DIM_D_FOLLOWING_HOLIDAY = ""; DATE_DIM_D_FIRST_DOM = 0L; DATE_DIM_D_LAST_DOM = 0L; DATE_DIM_D_SAME_DAY_LY = 0L; DATE_DIM_D_SAME_DAY_LQ = 0L; DATE_DIM_D_CURRENT_DAY = ""; DATE_DIM_D_CURRENT_WEEK = ""; DATE_DIM_D_CURRENT_MONTH = ""; DATE_DIM_D_CURRENT_QUARTER = ""; DATE_DIM_D_CURRENT_YEAR = ""; __av = 0L; */ }
    explicit DATE_DIM_entry(const long c0, const STRING_TYPE& c1, const date c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const long c19, const long c20, const long c21, const long c22, const STRING_TYPE& c23, const STRING_TYPE& c24, const STRING_TYPE& c25, const STRING_TYPE& c26, const STRING_TYPE& c27, const long c28) { DATE_DIM_D_DATE_SK = c0; DATE_DIM_D_DATE_ID = c1; DATE_DIM_D_DATE = c2; DATE_DIM_D_MONTH_SEQ = c3; DATE_DIM_D_WEEK_SEQ = c4; DATE_DIM_D_QUARTER_SEQ = c5; DATE_DIM_D_YEAR = c6; DATE_DIM_D_DOW = c7; DATE_DIM_D_MOY = c8; DATE_DIM_D_DOM = c9; DATE_DIM_D_QOY = c10; DATE_DIM_D_FY_YEAR = c11; DATE_DIM_D_FY_QUARTER_SEQ = c12; DATE_DIM_D_FY_WEEK_SEQ = c13; DATE_DIM_D_DAY_NAME = c14; DATE_DIM_D_QUARTER_NAME = c15; DATE_DIM_D_HOLIDAY = c16; DATE_DIM_D_WEEKEND = c17; DATE_DIM_D_FOLLOWING_HOLIDAY = c18; DATE_DIM_D_FIRST_DOM = c19; DATE_DIM_D_LAST_DOM = c20; DATE_DIM_D_SAME_DAY_LY = c21; DATE_DIM_D_SAME_DAY_LQ = c22; DATE_DIM_D_CURRENT_DAY = c23; DATE_DIM_D_CURRENT_WEEK = c24; DATE_DIM_D_CURRENT_MONTH = c25; DATE_DIM_D_CURRENT_QUARTER = c26; DATE_DIM_D_CURRENT_YEAR = c27; __av = c28; }
    DATE_DIM_entry(const DATE_DIM_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), DATE_DIM_D_DATE_ID( other.DATE_DIM_D_DATE_ID ), DATE_DIM_D_DATE( other.DATE_DIM_D_DATE ), DATE_DIM_D_MONTH_SEQ( other.DATE_DIM_D_MONTH_SEQ ), DATE_DIM_D_WEEK_SEQ( other.DATE_DIM_D_WEEK_SEQ ), DATE_DIM_D_QUARTER_SEQ( other.DATE_DIM_D_QUARTER_SEQ ), DATE_DIM_D_YEAR( other.DATE_DIM_D_YEAR ), DATE_DIM_D_DOW( other.DATE_DIM_D_DOW ), DATE_DIM_D_MOY( other.DATE_DIM_D_MOY ), DATE_DIM_D_DOM( other.DATE_DIM_D_DOM ), DATE_DIM_D_QOY( other.DATE_DIM_D_QOY ), DATE_DIM_D_FY_YEAR( other.DATE_DIM_D_FY_YEAR ), DATE_DIM_D_FY_QUARTER_SEQ( other.DATE_DIM_D_FY_QUARTER_SEQ ), DATE_DIM_D_FY_WEEK_SEQ( other.DATE_DIM_D_FY_WEEK_SEQ ), DATE_DIM_D_DAY_NAME( other.DATE_DIM_D_DAY_NAME ), DATE_DIM_D_QUARTER_NAME( other.DATE_DIM_D_QUARTER_NAME ), DATE_DIM_D_HOLIDAY( other.DATE_DIM_D_HOLIDAY ), DATE_DIM_D_WEEKEND( other.DATE_DIM_D_WEEKEND ), DATE_DIM_D_FOLLOWING_HOLIDAY( other.DATE_DIM_D_FOLLOWING_HOLIDAY ), DATE_DIM_D_FIRST_DOM( other.DATE_DIM_D_FIRST_DOM ), DATE_DIM_D_LAST_DOM( other.DATE_DIM_D_LAST_DOM ), DATE_DIM_D_SAME_DAY_LY( other.DATE_DIM_D_SAME_DAY_LY ), DATE_DIM_D_SAME_DAY_LQ( other.DATE_DIM_D_SAME_DAY_LQ ), DATE_DIM_D_CURRENT_DAY( other.DATE_DIM_D_CURRENT_DAY ), DATE_DIM_D_CURRENT_WEEK( other.DATE_DIM_D_CURRENT_WEEK ), DATE_DIM_D_CURRENT_MONTH( other.DATE_DIM_D_CURRENT_MONTH ), DATE_DIM_D_CURRENT_QUARTER( other.DATE_DIM_D_CURRENT_QUARTER ), DATE_DIM_D_CURRENT_YEAR( other.DATE_DIM_D_CURRENT_YEAR ), __av( other.__av ) {}
    FORCE_INLINE DATE_DIM_entry& modify(const long c0, const STRING_TYPE& c1, const date c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const long c19, const long c20, const long c21, const long c22, const STRING_TYPE& c23, const STRING_TYPE& c24, const STRING_TYPE& c25, const STRING_TYPE& c26, const STRING_TYPE& c27) { DATE_DIM_D_DATE_SK = c0; DATE_DIM_D_DATE_ID = c1; DATE_DIM_D_DATE = c2; DATE_DIM_D_MONTH_SEQ = c3; DATE_DIM_D_WEEK_SEQ = c4; DATE_DIM_D_QUARTER_SEQ = c5; DATE_DIM_D_YEAR = c6; DATE_DIM_D_DOW = c7; DATE_DIM_D_MOY = c8; DATE_DIM_D_DOM = c9; DATE_DIM_D_QOY = c10; DATE_DIM_D_FY_YEAR = c11; DATE_DIM_D_FY_QUARTER_SEQ = c12; DATE_DIM_D_FY_WEEK_SEQ = c13; DATE_DIM_D_DAY_NAME = c14; DATE_DIM_D_QUARTER_NAME = c15; DATE_DIM_D_HOLIDAY = c16; DATE_DIM_D_WEEKEND = c17; DATE_DIM_D_FOLLOWING_HOLIDAY = c18; DATE_DIM_D_FIRST_DOM = c19; DATE_DIM_D_LAST_DOM = c20; DATE_DIM_D_SAME_DAY_LY = c21; DATE_DIM_D_SAME_DAY_LQ = c22; DATE_DIM_D_CURRENT_DAY = c23; DATE_DIM_D_CURRENT_WEEK = c24; DATE_DIM_D_CURRENT_MONTH = c25; DATE_DIM_D_CURRENT_QUARTER = c26; DATE_DIM_D_CURRENT_YEAR = c27;  return *this; }
    FORCE_INLINE DATE_DIM_entry& modify7(const long c7) { DATE_DIM_D_DOW = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_MONTH_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_WEEK_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_QUARTER_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DOW);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_MOY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DOM);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_QOY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FY_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FY_QUARTER_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FY_WEEK_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DAY_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_QUARTER_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_HOLIDAY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_WEEKEND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FOLLOWING_HOLIDAY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FIRST_DOM);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_LAST_DOM);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_SAME_DAY_LY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_SAME_DAY_LQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_DAY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_WEEK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_MONTH);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_QUARTER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      hash_combine(h, e.DATE_DIM_D_DATE_ID);
      hash_combine(h, e.DATE_DIM_D_DATE);
      hash_combine(h, e.DATE_DIM_D_MONTH_SEQ);
      hash_combine(h, e.DATE_DIM_D_WEEK_SEQ);
      hash_combine(h, e.DATE_DIM_D_QUARTER_SEQ);
      hash_combine(h, e.DATE_DIM_D_YEAR);
      hash_combine(h, e.DATE_DIM_D_DOW);
      hash_combine(h, e.DATE_DIM_D_MOY);
      hash_combine(h, e.DATE_DIM_D_DOM);
      hash_combine(h, e.DATE_DIM_D_QOY);
      hash_combine(h, e.DATE_DIM_D_FY_YEAR);
      hash_combine(h, e.DATE_DIM_D_FY_QUARTER_SEQ);
      hash_combine(h, e.DATE_DIM_D_FY_WEEK_SEQ);
      hash_combine(h, e.DATE_DIM_D_DAY_NAME);
      hash_combine(h, e.DATE_DIM_D_QUARTER_NAME);
      hash_combine(h, e.DATE_DIM_D_HOLIDAY);
      hash_combine(h, e.DATE_DIM_D_WEEKEND);
      hash_combine(h, e.DATE_DIM_D_FOLLOWING_HOLIDAY);
      hash_combine(h, e.DATE_DIM_D_FIRST_DOM);
      hash_combine(h, e.DATE_DIM_D_LAST_DOM);
      hash_combine(h, e.DATE_DIM_D_SAME_DAY_LY);
      hash_combine(h, e.DATE_DIM_D_SAME_DAY_LQ);
      hash_combine(h, e.DATE_DIM_D_CURRENT_DAY);
      hash_combine(h, e.DATE_DIM_D_CURRENT_WEEK);
      hash_combine(h, e.DATE_DIM_D_CURRENT_MONTH);
      hash_combine(h, e.DATE_DIM_D_CURRENT_QUARTER);
      hash_combine(h, e.DATE_DIM_D_CURRENT_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK && x.DATE_DIM_D_DATE_ID == y.DATE_DIM_D_DATE_ID && x.DATE_DIM_D_DATE == y.DATE_DIM_D_DATE && x.DATE_DIM_D_MONTH_SEQ == y.DATE_DIM_D_MONTH_SEQ && x.DATE_DIM_D_WEEK_SEQ == y.DATE_DIM_D_WEEK_SEQ && x.DATE_DIM_D_QUARTER_SEQ == y.DATE_DIM_D_QUARTER_SEQ && x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR && x.DATE_DIM_D_DOW == y.DATE_DIM_D_DOW && x.DATE_DIM_D_MOY == y.DATE_DIM_D_MOY && x.DATE_DIM_D_DOM == y.DATE_DIM_D_DOM && x.DATE_DIM_D_QOY == y.DATE_DIM_D_QOY && x.DATE_DIM_D_FY_YEAR == y.DATE_DIM_D_FY_YEAR && x.DATE_DIM_D_FY_QUARTER_SEQ == y.DATE_DIM_D_FY_QUARTER_SEQ && x.DATE_DIM_D_FY_WEEK_SEQ == y.DATE_DIM_D_FY_WEEK_SEQ && x.DATE_DIM_D_DAY_NAME == y.DATE_DIM_D_DAY_NAME && x.DATE_DIM_D_QUARTER_NAME == y.DATE_DIM_D_QUARTER_NAME && x.DATE_DIM_D_HOLIDAY == y.DATE_DIM_D_HOLIDAY && x.DATE_DIM_D_WEEKEND == y.DATE_DIM_D_WEEKEND && x.DATE_DIM_D_FOLLOWING_HOLIDAY == y.DATE_DIM_D_FOLLOWING_HOLIDAY && x.DATE_DIM_D_FIRST_DOM == y.DATE_DIM_D_FIRST_DOM && x.DATE_DIM_D_LAST_DOM == y.DATE_DIM_D_LAST_DOM && x.DATE_DIM_D_SAME_DAY_LY == y.DATE_DIM_D_SAME_DAY_LY && x.DATE_DIM_D_SAME_DAY_LQ == y.DATE_DIM_D_SAME_DAY_LQ && x.DATE_DIM_D_CURRENT_DAY == y.DATE_DIM_D_CURRENT_DAY && x.DATE_DIM_D_CURRENT_WEEK == y.DATE_DIM_D_CURRENT_WEEK && x.DATE_DIM_D_CURRENT_MONTH == y.DATE_DIM_D_CURRENT_MONTH && x.DATE_DIM_D_CURRENT_QUARTER == y.DATE_DIM_D_CURRENT_QUARTER && x.DATE_DIM_D_CURRENT_YEAR == y.DATE_DIM_D_CURRENT_YEAR;
    }
  };
  
  struct DATE_DIM_mapkey7_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DOW);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_DOW == y.DATE_DIM_D_DOW;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey7_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey7_idxfn,false> HashIndex_DATE_DIM_map_7;
  
  struct HOUSEHOLD_DEMOGRAPHICS_entry {
    long HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK; long HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK; STRING_TYPE HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL; long HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT; long HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT; long __av; 
    explicit HOUSEHOLD_DEMOGRAPHICS_entry() { /*HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK = 0L; HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK = 0L; HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL = ""; HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT = 0L; HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT = 0L; __av = 0L; */ }
    explicit HOUSEHOLD_DEMOGRAPHICS_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4, const long c5) { HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK = c0; HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK = c1; HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL = c2; HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT = c3; HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT = c4; __av = c5; }
    HOUSEHOLD_DEMOGRAPHICS_entry(const HOUSEHOLD_DEMOGRAPHICS_entry& other) : HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK( other.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK ), HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK( other.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK ), HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL( other.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL ), HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT( other.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT ), HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT( other.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT ), __av( other.__av ) {}
    FORCE_INLINE HOUSEHOLD_DEMOGRAPHICS_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4) { HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK = c0; HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK = c1; HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL = c2; HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT = c3; HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HOUSEHOLD_DEMOGRAPHICS_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const HOUSEHOLD_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT);
      return h;
    }
    FORCE_INLINE static bool equals(const HOUSEHOLD_DEMOGRAPHICS_entry& x, const HOUSEHOLD_DEMOGRAPHICS_entry& y) {
      return x.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK == y.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK && x.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK == y.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK && x.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL == y.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL && x.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT == y.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT && x.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT == y.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
    }
  };
  
  typedef MultiHashMap<HOUSEHOLD_DEMOGRAPHICS_entry,long,
    HashIndex<HOUSEHOLD_DEMOGRAPHICS_entry,long,HOUSEHOLD_DEMOGRAPHICS_mapkey01234_idxfn,true>
  > HOUSEHOLD_DEMOGRAPHICS_map;
  typedef HashIndex<HOUSEHOLD_DEMOGRAPHICS_entry,long,HOUSEHOLD_DEMOGRAPHICS_mapkey01234_idxfn,true> HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234;
  
  struct COUNT_entry {
    STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE __SQL_EXPRESSION_1; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE MS_AMT; DOUBLE_TYPE MS_PROFIT; long __av; 
    explicit COUNT_entry() { /*CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_FIRST_NAME = ""; __SQL_EXPRESSION_1 = ""; MS_SS_TICKET_NUMBER = 0L; MS_AMT = 0.0; MS_PROFIT = 0.0; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const long c6) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; __SQL_EXPRESSION_1 = c2; MS_SS_TICKET_NUMBER = c3; MS_AMT = c4; MS_PROFIT = c5; __av = c6; }
    COUNT_entry(const COUNT_entry& other) : CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), __SQL_EXPRESSION_1( other.__SQL_EXPRESSION_1 ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_AMT( other.MS_AMT ), MS_PROFIT( other.MS_PROFIT ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; __SQL_EXPRESSION_1 = c2; MS_SS_TICKET_NUMBER = c3; MS_AMT = c4; MS_PROFIT = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __SQL_EXPRESSION_1);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_AMT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_PROFIT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.__SQL_EXPRESSION_1);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_AMT);
      hash_combine(h, e.MS_PROFIT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.__SQL_EXPRESSION_1 == y.__SQL_EXPRESSION_1 && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_AMT == y.MS_AMT && x.MS_PROFIT == y.MS_PROFIT;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true> HashIndex_COUNT_map_012345;
  
  struct COUNTSTORE1_DOMAIN1_entry {
    STRING_TYPE __SQL_EXPRESSION_1; long __av; 
    explicit COUNTSTORE1_DOMAIN1_entry() { /*__SQL_EXPRESSION_1 = ""; __av = 0L; */ }
    explicit COUNTSTORE1_DOMAIN1_entry(const STRING_TYPE& c0, const long c1) { __SQL_EXPRESSION_1 = c0; __av = c1; }
    COUNTSTORE1_DOMAIN1_entry(const COUNTSTORE1_DOMAIN1_entry& other) : __SQL_EXPRESSION_1( other.__SQL_EXPRESSION_1 ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE1_DOMAIN1_entry& modify(const STRING_TYPE& c0) { __SQL_EXPRESSION_1 = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __SQL_EXPRESSION_1);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.__SQL_EXPRESSION_1);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_DOMAIN1_entry& x, const COUNTSTORE1_DOMAIN1_entry& y) {
      return x.__SQL_EXPRESSION_1 == y.__SQL_EXPRESSION_1;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE1_DOMAIN1_entry,long,
    HashIndex<COUNTSTORE1_DOMAIN1_entry,long,COUNTSTORE1_DOMAIN1_mapkey0_idxfn,true>
  > COUNTSTORE1_DOMAIN1_map;
  typedef HashIndex<COUNTSTORE1_DOMAIN1_entry,long,COUNTSTORE1_DOMAIN1_mapkey0_idxfn,true> HashIndex_COUNTSTORE1_DOMAIN1_map_0;
  
  struct COUNTSTORE1_E1_2_DELTA_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE MS_S_CITY; long __av; 
    explicit COUNTSTORE1_E1_2_DELTA_entry() { /*STORE_SALES_SS_STORE_SK = 0L; MS_S_CITY = ""; __av = 0L; */ }
    explicit COUNTSTORE1_E1_2_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; MS_S_CITY = c1; __av = c2; }
    COUNTSTORE1_E1_2_DELTA_entry(const COUNTSTORE1_E1_2_DELTA_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE1_E1_2_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; MS_S_CITY = c1;  return *this; }
    FORCE_INLINE COUNTSTORE1_E1_2_DELTA_entry& modify1(const STRING_TYPE& c1) { MS_S_CITY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE1_E1_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E1_2_DELTA_entry& x, const COUNTSTORE1_E1_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  struct COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E1_2_DELTA_entry& x, const COUNTSTORE1_E1_2_DELTA_entry& y) {
      return x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE1_E1_2_DELTA_entry,long,
    HashIndex<COUNTSTORE1_E1_2_DELTA_entry,long,COUNTSTORE1_E1_2_DELTA_mapkey01_idxfn,true>,
    HashIndex<COUNTSTORE1_E1_2_DELTA_entry,long,COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn,false>
  > COUNTSTORE1_E1_2_DELTA_map;
  typedef HashIndex<COUNTSTORE1_E1_2_DELTA_entry,long,COUNTSTORE1_E1_2_DELTA_mapkey01_idxfn,true> HashIndex_COUNTSTORE1_E1_2_DELTA_map_01;
  typedef HashIndex<COUNTSTORE1_E1_2_DELTA_entry,long,COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn,false> HashIndex_COUNTSTORE1_E1_2_DELTA_map_1;
  
  struct COUNTSTORE1_E1_2_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long MS_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE1_E1_2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE1_E1_2_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE1_E1_2_entry(const COUNTSTORE1_E1_2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE1_E1_2_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTSTORE1_E1_2_entry& modify02(const long c0, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_STORE_SK = c2;  return *this; }
    FORCE_INLINE COUNTSTORE1_E1_2_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE1_E1_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E1_2_entry& x, const COUNTSTORE1_E1_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE1_E1_2_mapkey02_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E1_2_entry& x, const COUNTSTORE1_E1_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct COUNTSTORE1_E1_2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E1_2_entry& x, const COUNTSTORE1_E1_2_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE1_E1_2_entry,long,
    HashIndex<COUNTSTORE1_E1_2_entry,long,COUNTSTORE1_E1_2_mapkey0123_idxfn,true>,
    HashIndex<COUNTSTORE1_E1_2_entry,long,COUNTSTORE1_E1_2_mapkey02_idxfn,false>,
    HashIndex<COUNTSTORE1_E1_2_entry,long,COUNTSTORE1_E1_2_mapkey2_idxfn,false>
  > COUNTSTORE1_E1_2_map;
  typedef HashIndex<COUNTSTORE1_E1_2_entry,long,COUNTSTORE1_E1_2_mapkey0123_idxfn,true> HashIndex_COUNTSTORE1_E1_2_map_0123;
  typedef HashIndex<COUNTSTORE1_E1_2_entry,long,COUNTSTORE1_E1_2_mapkey02_idxfn,false> HashIndex_COUNTSTORE1_E1_2_map_02;
  typedef HashIndex<COUNTSTORE1_E1_2_entry,long,COUNTSTORE1_E1_2_mapkey2_idxfn,false> HashIndex_COUNTSTORE1_E1_2_map_2;
  
  struct COUNTSTORE6_DOMAIN1_entry {
    STRING_TYPE MS_S_CITY; long __av; 
    explicit COUNTSTORE6_DOMAIN1_entry() { /*MS_S_CITY = ""; __av = 0L; */ }
    explicit COUNTSTORE6_DOMAIN1_entry(const STRING_TYPE& c0, const long c1) { MS_S_CITY = c0; __av = c1; }
    COUNTSTORE6_DOMAIN1_entry(const COUNTSTORE6_DOMAIN1_entry& other) : MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE6_DOMAIN1_entry& modify(const STRING_TYPE& c0) { MS_S_CITY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE6_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE6_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE6_DOMAIN1_entry& x, const COUNTSTORE6_DOMAIN1_entry& y) {
      return x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE6_DOMAIN1_entry,long,
    HashIndex<COUNTSTORE6_DOMAIN1_entry,long,COUNTSTORE6_DOMAIN1_mapkey0_idxfn,true>
  > COUNTSTORE6_DOMAIN1_map;
  typedef HashIndex<COUNTSTORE6_DOMAIN1_entry,long,COUNTSTORE6_DOMAIN1_mapkey0_idxfn,true> HashIndex_COUNTSTORE6_DOMAIN1_map_0;
  
  struct COUNTSTORE9_L2_2_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE9_L2_2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE9_L2_2_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE9_L2_2_entry(const COUNTSTORE9_L2_2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE9_L2_2_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTSTORE9_L2_2_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE9_L2_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE9_L2_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE9_L2_2_entry& x, const COUNTSTORE9_L2_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE9_L2_2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE9_L2_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE9_L2_2_entry& x, const COUNTSTORE9_L2_2_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE9_L2_2_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE9_L2_2_entry,DOUBLE_TYPE,COUNTSTORE9_L2_2_mapkey0123_idxfn,true>,
    HashIndex<COUNTSTORE9_L2_2_entry,DOUBLE_TYPE,COUNTSTORE9_L2_2_mapkey2_idxfn,false>
  > COUNTSTORE9_L2_2_map;
  typedef HashIndex<COUNTSTORE9_L2_2_entry,DOUBLE_TYPE,COUNTSTORE9_L2_2_mapkey0123_idxfn,true> HashIndex_COUNTSTORE9_L2_2_map_0123;
  typedef HashIndex<COUNTSTORE9_L2_2_entry,DOUBLE_TYPE,COUNTSTORE9_L2_2_mapkey2_idxfn,false> HashIndex_COUNTSTORE9_L2_2_map_2;
  
  struct COUNTSTORE9_L3_2_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE9_L3_2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE9_L3_2_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE9_L3_2_entry(const COUNTSTORE9_L3_2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE9_L3_2_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTSTORE9_L3_2_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE9_L3_2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE9_L3_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE9_L3_2_entry& x, const COUNTSTORE9_L3_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE9_L3_2_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE9_L3_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE9_L3_2_entry& x, const COUNTSTORE9_L3_2_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE9_L3_2_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE9_L3_2_entry,DOUBLE_TYPE,COUNTSTORE9_L3_2_mapkey0123_idxfn,true>,
    HashIndex<COUNTSTORE9_L3_2_entry,DOUBLE_TYPE,COUNTSTORE9_L3_2_mapkey2_idxfn,false>
  > COUNTSTORE9_L3_2_map;
  typedef HashIndex<COUNTSTORE9_L3_2_entry,DOUBLE_TYPE,COUNTSTORE9_L3_2_mapkey0123_idxfn,true> HashIndex_COUNTSTORE9_L3_2_map_0123;
  typedef HashIndex<COUNTSTORE9_L3_2_entry,DOUBLE_TYPE,COUNTSTORE9_L3_2_mapkey2_idxfn,false> HashIndex_COUNTSTORE9_L3_2_map_2;
  
  struct COUNTSTORE_SALES1_DOMAIN1_entry {
    long MS_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE_SALES1_DOMAIN1_entry() { /*MS_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_DOMAIN1_entry(const long c0, const long c1) { MS_SS_TICKET_NUMBER = c0; __av = c1; }
    COUNTSTORE_SALES1_DOMAIN1_entry(const COUNTSTORE_SALES1_DOMAIN1_entry& other) : MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_DOMAIN1_entry& modify(const long c0) { MS_SS_TICKET_NUMBER = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_DOMAIN1_entry& x, const COUNTSTORE_SALES1_DOMAIN1_entry& y) {
      return x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_DOMAIN1_entry,long,
    HashIndex<COUNTSTORE_SALES1_DOMAIN1_entry,long,COUNTSTORE_SALES1_DOMAIN1_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_DOMAIN1_map;
  typedef HashIndex<COUNTSTORE_SALES1_DOMAIN1_entry,long,COUNTSTORE_SALES1_DOMAIN1_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0;
  
  struct COUNTSTORE_SALES1_entry {
    long CUSTOMER_C_CUSTOMER_SK; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; long __av; 
    explicit COUNTSTORE_SALES1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2; __av = c3; }
    COUNTSTORE_SALES1_entry(const COUNTSTORE_SALES1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_entry& x, const COUNTSTORE_SALES1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME;
    }
  };
  
  struct COUNTSTORE_SALES1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_entry& x, const COUNTSTORE_SALES1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_entry,long,
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey012_idxfn,true>,
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false>
  > COUNTSTORE_SALES1_map;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey012_idxfn,true> HashIndex_COUNTSTORE_SALES1_map_012;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false> HashIndex_COUNTSTORE_SALES1_map_0;
  
  struct COUNTSTORE_SALES1_E1_2_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long MS_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; MS_SS_TICKET_NUMBER = c5; __av = c6; }
    COUNTSTORE_SALES1_E1_2_DELTA_entry(const COUNTSTORE_SALES1_E1_2_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; MS_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_DELTA_entry& modify5(const long c5) { MS_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_DELTA_entry& modify135(const long c1, const long c3, const long c5) { CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c3; MS_SS_TICKET_NUMBER = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_DELTA_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_DELTA_entry& x, const COUNTSTORE_SALES1_E1_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_DELTA_entry& x, const COUNTSTORE_SALES1_E1_2_DELTA_entry& y) {
      return x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_DELTA_entry& x, const COUNTSTORE_SALES1_E1_2_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_DELTA_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_DELTA_mapkey012345_idxfn,true>,
    HashIndex<COUNTSTORE_SALES1_E1_2_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn,false>,
    HashIndex<COUNTSTORE_SALES1_E1_2_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn,false>
  > COUNTSTORE_SALES1_E1_2_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_DELTA_mapkey012345_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn,false> HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn,false> HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135;
  
  struct COUNTSTORE_SALES1_E1_2_P_1_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_P_1_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_P_1_entry(const long c0, const long c1) { STORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_2_P_1_entry(const COUNTSTORE_SALES1_E1_2_P_1_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_1_entry& modify(const long c0) { STORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_1_entry& x, const COUNTSTORE_SALES1_E1_2_P_1_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_P_1_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_1_entry,long,COUNTSTORE_SALES1_E1_2_P_1_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_2_P_1_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_1_entry,long,COUNTSTORE_SALES1_E1_2_P_1_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_P_1_map_0;
  
  struct COUNTSTORE_SALES1_E1_2_P_2_entry {
    long STORE_SALES_SS_HDEMO_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_P_2_entry() { /*STORE_SALES_SS_HDEMO_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_P_2_entry(const long c0, const long c1) { STORE_SALES_SS_HDEMO_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_2_P_2_entry(const COUNTSTORE_SALES1_E1_2_P_2_entry& other) : STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_2_entry& modify(const long c0) { STORE_SALES_SS_HDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_2_entry& x, const COUNTSTORE_SALES1_E1_2_P_2_entry& y) {
      return x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_P_2_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_2_entry,long,COUNTSTORE_SALES1_E1_2_P_2_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_2_P_2_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_2_entry,long,COUNTSTORE_SALES1_E1_2_P_2_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_P_2_map_0;
  
  struct COUNTSTORE_SALES1_E1_2_P_3_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE MS_S_CITY; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_P_3_entry() { /*STORE_SALES_SS_STORE_SK = 0L; MS_S_CITY = ""; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_P_3_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; MS_S_CITY = c1; __av = c2; }
    COUNTSTORE_SALES1_E1_2_P_3_entry(const COUNTSTORE_SALES1_E1_2_P_3_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_3_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; MS_S_CITY = c1;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_3_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_3_entry& x, const COUNTSTORE_SALES1_E1_2_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  struct COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_3_entry& x, const COUNTSTORE_SALES1_E1_2_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_P_3_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_3_entry,long,COUNTSTORE_SALES1_E1_2_P_3_mapkey01_idxfn,true>,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_3_entry,long,COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn,false>
  > COUNTSTORE_SALES1_E1_2_P_3_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_3_entry,long,COUNTSTORE_SALES1_E1_2_P_3_mapkey01_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_01;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_3_entry,long,COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn,false> HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0;
  
  struct COUNTSTORE_SALES6_DOMAIN1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE_SALES6_DOMAIN1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES6_DOMAIN1_entry(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTSTORE_SALES6_DOMAIN1_entry(const COUNTSTORE_SALES6_DOMAIN1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES6_DOMAIN1_entry& modify(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES6_DOMAIN1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES6_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES6_DOMAIN1_entry& x, const COUNTSTORE_SALES6_DOMAIN1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES6_DOMAIN1_entry,long,
    HashIndex<COUNTSTORE_SALES6_DOMAIN1_entry,long,COUNTSTORE_SALES6_DOMAIN1_mapkey012_idxfn,true>
  > COUNTSTORE_SALES6_DOMAIN1_map;
  typedef HashIndex<COUNTSTORE_SALES6_DOMAIN1_entry,long,COUNTSTORE_SALES6_DOMAIN1_mapkey012_idxfn,true> HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012;
  
  struct COUNTSTORE_SALES9_L2_2_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE_SALES9_L2_2_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE_SALES9_L2_2_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; MS_SS_TICKET_NUMBER = c5; __av = c6; }
    COUNTSTORE_SALES9_L2_2_DELTA_entry(const COUNTSTORE_SALES9_L2_2_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES9_L2_2_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; MS_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES9_L2_2_DELTA_entry& modify135(const long c1, const long c3, const long c5) { CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c3; MS_SS_TICKET_NUMBER = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES9_L2_2_DELTA_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L2_2_DELTA_entry& x, const COUNTSTORE_SALES9_L2_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L2_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L2_2_DELTA_entry& x, const COUNTSTORE_SALES9_L2_2_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES9_L2_2_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE_SALES9_L2_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_2_DELTA_mapkey012345_idxfn,true>,
    HashIndex<COUNTSTORE_SALES9_L2_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn,false>
  > COUNTSTORE_SALES9_L2_2_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES9_L2_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_2_DELTA_mapkey012345_idxfn,true> HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_012345;
  typedef HashIndex<COUNTSTORE_SALES9_L2_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn,false> HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135;
  
  struct COUNTSTORE_SALES9_L3_2_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE_SALES9_L3_2_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE_SALES9_L3_2_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; MS_SS_TICKET_NUMBER = c5; __av = c6; }
    COUNTSTORE_SALES9_L3_2_DELTA_entry(const COUNTSTORE_SALES9_L3_2_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES9_L3_2_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; MS_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES9_L3_2_DELTA_entry& modify135(const long c1, const long c3, const long c5) { CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c3; MS_SS_TICKET_NUMBER = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES9_L3_2_DELTA_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L3_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L3_2_DELTA_entry& x, const COUNTSTORE_SALES9_L3_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L3_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L3_2_DELTA_entry& x, const COUNTSTORE_SALES9_L3_2_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES9_L3_2_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE_SALES9_L3_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_2_DELTA_mapkey012345_idxfn,true>,
    HashIndex<COUNTSTORE_SALES9_L3_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn,false>
  > COUNTSTORE_SALES9_L3_2_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES9_L3_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_2_DELTA_mapkey012345_idxfn,true> HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_012345;
  typedef HashIndex<COUNTSTORE_SALES9_L3_2_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn,false> HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135;
  
  struct COUNTCUSTOMER1_DELTA_entry {
    long CUSTOMER_C_CUSTOMER_SK; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; long __av; 
    explicit COUNTCUSTOMER1_DELTA_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2; __av = c3; }
    COUNTCUSTOMER1_DELTA_entry(const COUNTCUSTOMER1_DELTA_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_DELTA_entry& x, const COUNTCUSTOMER1_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_DELTA_entry,long,
    HashIndex<COUNTCUSTOMER1_DELTA_entry,long,COUNTCUSTOMER1_DELTA_mapkey012_idxfn,true>
  > COUNTCUSTOMER1_DELTA_map;
  typedef HashIndex<COUNTCUSTOMER1_DELTA_entry,long,COUNTCUSTOMER1_DELTA_mapkey012_idxfn,true> HashIndex_COUNTCUSTOMER1_DELTA_map_012;
  
  struct COUNTCUSTOMER1_E1_1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; STRING_TYPE MS_S_CITY; long __av; 
    explicit COUNTCUSTOMER1_E1_1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; MS_S_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3; __av = c4; }
    COUNTCUSTOMER1_E1_1_entry(const COUNTCUSTOMER1_E1_1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify2(const long c2) { MS_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify012(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify03(const long c0, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; MS_S_CITY = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey03_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_E1_1_entry,long,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey2_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey012_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey03_idxfn,false>
  > COUNTCUSTOMER1_E1_1_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1_map_0123;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_2;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey012_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_012;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_0;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey03_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_03;
  
  struct COUNTCUSTOMER1_L3_1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; STRING_TYPE MS_S_CITY; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L3_1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; MS_S_CITY = ""; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L3_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3; __av = c4; }
    COUNTCUSTOMER1_L3_1_entry(const COUNTCUSTOMER1_L3_1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L3_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L3_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L3_1_entry& x, const COUNTCUSTOMER1_L3_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L3_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L3_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_1_mapkey0123_idxfn,true>
  > COUNTCUSTOMER1_L3_1_map;
  typedef HashIndex<COUNTCUSTOMER1_L3_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_L3_1_map_0123;
  
  struct COUNTCUSTOMER1_L4_1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; STRING_TYPE MS_S_CITY; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L4_1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; MS_S_CITY = ""; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L4_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3; __av = c4; }
    COUNTCUSTOMER1_L4_1_entry(const COUNTCUSTOMER1_L4_1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L4_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L4_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L4_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L4_1_entry& x, const COUNTCUSTOMER1_L4_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L4_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L4_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_1_mapkey0123_idxfn,true>
  > COUNTCUSTOMER1_L4_1_map;
  typedef HashIndex<COUNTCUSTOMER1_L4_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_L4_1_map_0123;
  
  struct tuple6_DDSSS_L {
    DOUBLE_TYPE _1; DOUBLE_TYPE _2; STRING_TYPE _3; STRING_TYPE _4; STRING_TYPE _5; long __av;
    explicit tuple6_DDSSS_L() { }
    explicit tuple6_DDSSS_L(const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; __av = c__av;}
    int operator==(const tuple6_DDSSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5)); }
    FORCE_INLINE tuple6_DDSSS_L& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; __av = c__av; return *this; }
    static bool equals(const tuple6_DDSSS_L &x, const tuple6_DDSSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5)); }
    static long hash(const tuple6_DDSSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      return h;
    }
  };
  struct tuple6_SSLDD_L {
    STRING_TYPE _1; STRING_TYPE _2; long _3; DOUBLE_TYPE _4; DOUBLE_TYPE _5; long __av;
    explicit tuple6_SSLDD_L() { }
    explicit tuple6_SSLDD_L(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; __av = c__av;}
    int operator==(const tuple6_SSLDD_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5)); }
    FORCE_INLINE tuple6_SSLDD_L& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; __av = c__av; return *this; }
    static bool equals(const tuple6_SSLDD_L &x, const tuple6_SSLDD_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5)); }
    static long hash(const tuple6_SSLDD_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      return h;
    }
  };
  struct tuple2_S_L {
    STRING_TYPE _1; long __av;
    explicit tuple2_S_L() { }
    explicit tuple2_S_L(const STRING_TYPE& c1, long c__av=0L) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_S_L &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_S_L& modify(const STRING_TYPE& c0, long c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_S_L &x, const tuple2_S_L &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_S_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      return h;
    }
  };
  struct tuple4_LLS_L {
    long _1; long _2; STRING_TYPE _3; long __av;
    explicit tuple4_LLS_L() { }
    explicit tuple4_LLS_L(const long c1, const long c2, const STRING_TYPE& c3, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; __av = c__av;}
    int operator==(const tuple4_LLS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3)); }
    FORCE_INLINE tuple4_LLS_L& modify(const long c0, const long c1, const STRING_TYPE& c2, long c__av) { _1 = c0; _2 = c1; _3 = c2; __av = c__av; return *this; }
    static bool equals(const tuple4_LLS_L &x, const tuple4_LLS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3)); }
    static long hash(const tuple4_LLS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      return h;
    }
  };
  struct tuple3_LL_L {
    long _1; long _2; long __av;
    explicit tuple3_LL_L() { }
    explicit tuple3_LL_L(const long c1, const long c2, long c__av=0L) { _1 = c1; _2 = c2; __av = c__av;}
    int operator==(const tuple3_LL_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2)); }
    FORCE_INLINE tuple3_LL_L& modify(const long c0, const long c1, long c__av) { _1 = c0; _2 = c1; __av = c__av; return *this; }
    static bool equals(const tuple3_LL_L &x, const tuple3_LL_L &y) { return ((x._1==y._1) && (x._2==y._2)); }
    static long hash(const tuple3_LL_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      return h;
    }
  };
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const COUNT_map& _COUNT = get_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(COUNT), _COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const COUNT_map& get_COUNT() const {
      return COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    COUNT_map COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), _c1(16U), _c4(16U), _c7(16U), _c6(16U), _c3(16U), _c2(16U), _c5(16U), _c8(16U) {
      
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_DATE_DIM(const long date_dim_d_date_sk, const STRING_TYPE date_dim_d_date_id, const date date_dim_d_date, const long date_dim_d_month_seq, const long date_dim_d_week_seq, const long date_dim_d_quarter_seq, const long date_dim_d_year, const long date_dim_d_dow, const long date_dim_d_moy, const long date_dim_d_dom, const long date_dim_d_qoy, const long date_dim_d_fy_year, const long date_dim_d_fy_quarter_seq, const long date_dim_d_fy_week_seq, const STRING_TYPE date_dim_d_day_name, const STRING_TYPE date_dim_d_quarter_name, const STRING_TYPE date_dim_d_holiday, const STRING_TYPE date_dim_d_weekend, const STRING_TYPE date_dim_d_following_holiday, const long date_dim_d_first_dom, const long date_dim_d_last_dom, const long date_dim_d_same_day_ly, const long date_dim_d_same_day_lq, const STRING_TYPE date_dim_d_current_day, const STRING_TYPE date_dim_d_current_week, const STRING_TYPE date_dim_d_current_month, const STRING_TYPE date_dim_d_current_quarter, const STRING_TYPE date_dim_d_current_year) {
      DATE_DIM_entry e(date_dim_d_date_sk, date_dim_d_date_id, date_dim_d_date, date_dim_d_month_seq, date_dim_d_week_seq, date_dim_d_quarter_seq, date_dim_d_year, date_dim_d_dow, date_dim_d_moy, date_dim_d_dom, date_dim_d_qoy, date_dim_d_fy_year, date_dim_d_fy_quarter_seq, date_dim_d_fy_week_seq, date_dim_d_day_name, date_dim_d_quarter_name, date_dim_d_holiday, date_dim_d_weekend, date_dim_d_following_holiday, date_dim_d_first_dom, date_dim_d_last_dom, date_dim_d_same_day_ly, date_dim_d_same_day_lq, date_dim_d_current_day, date_dim_d_current_week, date_dim_d_current_month, date_dim_d_current_quarter, date_dim_d_current_year, 1L);
      DATE_DIM.addOrDelOnZero(e,1L);
    }
    
    void on_insert_HOUSEHOLD_DEMOGRAPHICS(const long household_demographics_hd_demo_sk, const long household_demographics_hd_income_band_sk, const STRING_TYPE household_demographics_hd_buy_potential, const long household_demographics_hd_dep_count, const long household_demographics_hd_vehicle_count) {
      HOUSEHOLD_DEMOGRAPHICS_entry e(household_demographics_hd_demo_sk, household_demographics_hd_income_band_sk, household_demographics_hd_buy_potential, household_demographics_hd_dep_count, household_demographics_hd_vehicle_count, 1L);
      HOUSEHOLD_DEMOGRAPHICS.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_STORE_SALES(TPCDSStoreSalesBatch& DELTA_STORE_SALES) {
      { 
        if (tS > 0) { tS += DELTA_STORE_SALES.size; return; }         
        tLastN += DELTA_STORE_SALES.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_STORE_SALES.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_STORE_SALES.size;

        COUNTSTORE_SALES9_L3_2_DELTA.clear();
        COUNTSTORE_SALES9_L2_2_DELTA.clear();
        COUNTSTORE_SALES6_DOMAIN1.clear();
        COUNTSTORE_SALES1_E1_2_DELTA.clear();
        COUNTSTORE_SALES1_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_STORE_SALES.size; i++) 
          {
                long store_sales_ss_sold_date_sk = DELTA_STORE_SALES.ss_sold_date_sk[i];
                // long store_sales_ss_sold_time_sk = DELTA_STORE_SALES.ss_sold_time_sk[i];
                // long store_sales_ss_item_sk = DELTA_STORE_SALES.ss_item_sk[i];
                long customer_c_customer_sk = DELTA_STORE_SALES.ss_customer_sk[i];
                // long store_sales_ss_cdemo_sk = DELTA_STORE_SALES.ss_cdemo_sk[i];
                long store_sales_ss_hdemo_sk = DELTA_STORE_SALES.ss_hdemo_sk[i];
                long store_sales_ss_addr_sk = DELTA_STORE_SALES.ss_addr_sk[i];
                long store_sales_ss_store_sk = DELTA_STORE_SALES.ss_store_sk[i];
                // long store_sales_ss_promo_sk = DELTA_STORE_SALES.ss_promo_sk[i];
                long store_sales_ss_ticket_number = DELTA_STORE_SALES.ss_ticket_number[i];
                // long store_sales_ss_quantity = DELTA_STORE_SALES.ss_quantity[i];
                // DOUBLE_TYPE store_sales_ss_wholesale_cost = DELTA_STORE_SALES.ss_wholesale_cost[i];
                // DOUBLE_TYPE store_sales_ss_list_price = DELTA_STORE_SALES.ss_list_price[i];
                // DOUBLE_TYPE store_sales_ss_sales_price = DELTA_STORE_SALES.ss_sales_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_discount_amt = DELTA_STORE_SALES.ss_ext_discount_amt[i];
                // DOUBLE_TYPE store_sales_ss_ext_sales_price = DELTA_STORE_SALES.ss_ext_sales_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_wholesale_cost = DELTA_STORE_SALES.ss_ext_wholesale_cost[i];
                // DOUBLE_TYPE store_sales_ss_ext_list_price = DELTA_STORE_SALES.ss_ext_list_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_tax = DELTA_STORE_SALES.ss_ext_tax[i];
                DOUBLE_TYPE store_sales_ss_coupon_amt = DELTA_STORE_SALES.ss_coupon_amt[i];
                // DOUBLE_TYPE store_sales_ss_net_paid = DELTA_STORE_SALES.ss_net_paid[i];
                // DOUBLE_TYPE store_sales_ss_net_paid_inc_tax = DELTA_STORE_SALES.ss_net_paid_inc_tax[i];
                DOUBLE_TYPE store_sales_ss_net_profit = DELTA_STORE_SALES.ss_net_profit[i];
                long v1 = 1L;
                COUNTSTORE_SALES9_L3_2_DELTA.addOrDelOnZero(se1.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(v1 * store_sales_ss_coupon_amt));            
                long v2 = 1L;
                COUNTSTORE_SALES9_L2_2_DELTA.addOrDelOnZero(se2.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(v2 * store_sales_ss_net_profit));
                long v3 = 1L;
                COUNTSTORE_SALES6_DOMAIN1.addOrDelOnZero(se3.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number),(v3 != 0 ? 1L : 0L));
                long v4 = 1L;
                COUNTSTORE_SALES1_E1_2_DELTA.addOrDelOnZero(se4.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),v4);
                long v5 = 1L;
                COUNTSTORE_SALES1_DOMAIN1.addOrDelOnZero(se5.modify(store_sales_ss_ticket_number),(v5 != 0 ? 1L : 0L));
          }
        }
        
        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0* i6 = static_cast<HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0*>(COUNTSTORE_SALES1_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0::IdxNode* n6; 
          COUNTSTORE_SALES1_DOMAIN1_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long ms_ss_ticket_number = e6->MS_SS_TICKET_NUMBER;
                long v6 = e6->__av;
                _c1.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i7 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h2 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se10.modify2(ms_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n7 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i7->slice(se10, h2));
                  COUNTCUSTOMER1_E1_1_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      long customer_c_customer_sk = e7->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e7->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE ms_s_city = e7->MS_S_CITY;
                      long v8 = e7->__av;
                      STRING_TYPE l1 = Usubstring(ms_s_city, 1L, 30L);
                      DOUBLE_TYPE l2 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se7.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                      DOUBLE_TYPE l3 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se8.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_map_0* i8 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                        const HASH_RES_t h1 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se9.modify0(customer_c_customer_sk));
                        HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n8 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i8->slice(se9, h1));
                        COUNTSTORE_SALES1_entry* e8;
                       
                        if (n8 && (e8 = n8->obj)) {
                          do {                
                            STRING_TYPE customer_c_first_name = e8->CUSTOMER_C_FIRST_NAME;
                            STRING_TYPE customer_c_last_name = e8->CUSTOMER_C_LAST_NAME;
                            long v9 = e8->__av;
                            _c1.addOrDelOnZero(st1.modify(l3,l2,l1,customer_c_first_name,customer_c_last_name,(((v8 != 0 ? 1L : 0L) * v9) * -2L)), (((v8 != 0 ? 1L : 0L) * v9) * -2L));
                            n8 = n8->nxt;
                          } while (n8 && (e8 = n8->obj) && h1 == n8->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se9, *e8)); 
                        }
                      }
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h2 == n7->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se10, *e7)); 
                  }
                }_c2.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i9 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h3 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se11.modify2(ms_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n9 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i9->slice(se11, h3));
                  COUNTCUSTOMER1_E1_1_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      long customer_c_customer_sk = e9->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e9->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE ms_s_city = e9->MS_S_CITY;
                      long v11 = e9->__av;
                      _c2.addOrDelOnZero(st2.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_s_city,v11), v11);
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h3 == n9->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se11, *e9)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5* i10 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5*>(COUNTSTORE_SALES1_E1_2_DELTA.index[1]);
                  const HASH_RES_t h5 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn::hash(se15.modify5(ms_ss_ticket_number));
                  HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5::IdxNode* n10 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5::IdxNode*>(i10->slice(se15, h5));
                  COUNTSTORE_SALES1_E1_2_DELTA_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      long store_sales_ss_sold_date_sk = e10->STORE_SALES_SS_SOLD_DATE_SK;
                      long customer_c_customer_sk = e10->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_hdemo_sk = e10->STORE_SALES_SS_HDEMO_SK;
                      long store_sales_ss_addr_sk = e10->STORE_SALES_SS_ADDR_SK;
                      long store_sales_ss_store_sk = e10->STORE_SALES_SS_STORE_SK;
                      long v12 = e10->__av;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0* i11 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0*>(COUNTSTORE_SALES1_E1_2_P_3.index[1]);
                        const HASH_RES_t h4 = COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::hash(se14.modify0(store_sales_ss_store_sk));
                        HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode* n11 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode*>(i11->slice(se14, h4));
                        COUNTSTORE_SALES1_E1_2_P_3_entry* e11;
                       
                        if (n11 && (e11 = n11->obj)) {
                          do {                
                            STRING_TYPE ms_s_city = e11->MS_S_CITY;
                            long v13 = e11->__av;
                            _c2.addOrDelOnZero(st3.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_s_city,(v12 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se12.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se13.modify(store_sales_ss_hdemo_sk)) * v13)))), (v12 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se12.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se13.modify(store_sales_ss_hdemo_sk)) * v13))));
                            n11 = n11->nxt;
                          } while (n11 && (e11 = n11->obj) && h4 == n11->hash &&  COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::equals(se14, *e11)); 
                        }
                      }
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h5 == n10->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn::equals(se15, *e10)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_LLS_L, long>* i12 = static_cast<HashIndex<tuple4_LLS_L, long>*>(_c2.index[0]);
                  HashIndex<tuple4_LLS_L, long>::IdxNode* n12; 
                  tuple4_LLS_L* e12;
                
                  for (size_t i = 0; i < i12->size_; i++)
                  {
                    n12 = i12->buckets_ + i;
                    while (n12 && (e12 = n12->obj))
                    {
                      long customer_c_customer_sk = e12->_1;
                      long store_sales_ss_addr_sk = e12->_2;
                      STRING_TYPE ms_s_city = e12->_3;  
                      long v14 = e12->__av; 
                    DOUBLE_TYPE l4 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se16.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                    DOUBLE_TYPE l5 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se17.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                    STRING_TYPE l6 = Usubstring(ms_s_city, 1L, 30L);
                    { //slice 
                      const HashIndex_COUNTSTORE_SALES1_map_0* i13 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                      const HASH_RES_t h6 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se18.modify0(customer_c_customer_sk));
                      HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n13 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i13->slice(se18, h6));
                      COUNTSTORE_SALES1_entry* e13;
                     
                      if (n13 && (e13 = n13->obj)) {
                        do {                
                          STRING_TYPE customer_c_first_name = e13->CUSTOMER_C_FIRST_NAME;
                          STRING_TYPE customer_c_last_name = e13->CUSTOMER_C_LAST_NAME;
                          long v15 = e13->__av;
                          _c1.addOrDelOnZero(st4.modify(l4,l5,l6,customer_c_first_name,customer_c_last_name,((v14 != 0 ? 1L : 0L) * v15)), ((v14 != 0 ? 1L : 0L) * v15));
                          n13 = n13->nxt;
                        } while (n13 && (e13 = n13->obj) && h6 == n13->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se18, *e13)); 
                      }
                    }      
                      n12 = n12->nxt;
                    }
                  }
                }{ //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i14 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h10 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se30.modify2(ms_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n14 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i14->slice(se30, h10));
                  COUNTCUSTOMER1_E1_1_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      long customer_c_customer_sk = e14->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e14->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE ms_s_city = e14->MS_S_CITY;
                      long v16 = e14->__av;
                      DOUBLE_TYPE agg1 = 0.0;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135* i15 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135*>(COUNTSTORE_SALES9_L2_2_DELTA.index[1]);
                        const HASH_RES_t h7 = COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn::hash(se23.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135::IdxNode* n15 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135::IdxNode*>(i15->slice(se23, h7));
                        COUNTSTORE_SALES9_L2_2_DELTA_entry* e15;
                       
                        if (n15 && (e15 = n15->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e15->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e15->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e15->STORE_SALES_SS_STORE_SK;
                            DOUBLE_TYPE v17 = e15->__av;
                            agg1 += (v17 * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se20.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se21.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se22.modify(store_sales_ss_hdemo_sk)))));
                            n15 = n15->nxt;
                          } while (n15 && (e15 = n15->obj) && h7 == n15->hash &&  COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn::equals(se23, *e15)); 
                        }
                      }DOUBLE_TYPE l7 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se19.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg1);
                      DOUBLE_TYPE agg2 = 0.0;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135* i16 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135*>(COUNTSTORE_SALES9_L3_2_DELTA.index[1]);
                        const HASH_RES_t h8 = COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn::hash(se28.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135::IdxNode* n16 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135::IdxNode*>(i16->slice(se28, h8));
                        COUNTSTORE_SALES9_L3_2_DELTA_entry* e16;
                       
                        if (n16 && (e16 = n16->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e16->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e16->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e16->STORE_SALES_SS_STORE_SK;
                            DOUBLE_TYPE v18 = e16->__av;
                            agg2 += (v18 * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se25.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se26.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se27.modify(store_sales_ss_hdemo_sk)))));
                            n16 = n16->nxt;
                          } while (n16 && (e16 = n16->obj) && h8 == n16->hash &&  COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn::equals(se28, *e16)); 
                        }
                      }DOUBLE_TYPE l8 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se24.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg2);
                      STRING_TYPE l9 = Usubstring(ms_s_city, 1L, 30L);
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_map_0* i17 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                        const HASH_RES_t h9 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se29.modify0(customer_c_customer_sk));
                        HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n17 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i17->slice(se29, h9));
                        COUNTSTORE_SALES1_entry* e17;
                       
                        if (n17 && (e17 = n17->obj)) {
                          do {                
                            STRING_TYPE customer_c_first_name = e17->CUSTOMER_C_FIRST_NAME;
                            STRING_TYPE customer_c_last_name = e17->CUSTOMER_C_LAST_NAME;
                            long v19 = e17->__av;
                            _c1.addOrDelOnZero(st5.modify(l7,l8,l9,customer_c_first_name,customer_c_last_name,((v16 != 0 ? 1L : 0L) * v19)), ((v16 != 0 ? 1L : 0L) * v19));
                            n17 = n17->nxt;
                          } while (n17 && (e17 = n17->obj) && h9 == n17->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se29, *e17)); 
                        }
                      }
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h10 == n14->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se30, *e14)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple6_DDSSS_L, long>* i18 = static_cast<HashIndex<tuple6_DDSSS_L, long>*>(_c1.index[0]);
                  HashIndex<tuple6_DDSSS_L, long>::IdxNode* n18; 
                  tuple6_DDSSS_L* e18;
                
                  for (size_t i = 0; i < i18->size_; i++)
                  {
                    n18 = i18->buckets_ + i;
                    while (n18 && (e18 = n18->obj))
                    {
                      DOUBLE_TYPE ms_profit = e18->_1;
                      DOUBLE_TYPE ms_amt = e18->_2;
                      STRING_TYPE __sql_expression_1 = e18->_3;
                      STRING_TYPE customer_c_first_name = e18->_4;
                      STRING_TYPE customer_c_last_name = e18->_5;  
                      long v20 = e18->__av; 
                    COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,__sql_expression_1,ms_ss_ticket_number,ms_amt,ms_profit),((v6 != 0 ? 1L : 0L) * v20));      
                      n18 = n18->nxt;
                    }
                  }
                }
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i19 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n19; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long customer_c_customer_sk = e19->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e19->STORE_SALES_SS_ADDR_SK;
                long ms_ss_ticket_number = e19->MS_SS_TICKET_NUMBER;
                long v21 = e19->__av;
                { //slice 
                  const HashIndex_COUNTSTORE_SALES1_map_0* i20 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                  const HASH_RES_t h14 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se38.modify0(customer_c_customer_sk));
                  HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n20 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i20->slice(se38, h14));
                  COUNTSTORE_SALES1_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e20->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e20->CUSTOMER_C_LAST_NAME;
                      long v22 = e20->__av;
                      _c3.clear();
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i21 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h11 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se31.modify012(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n21 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i21->slice(se31, h11));
                        COUNTCUSTOMER1_E1_1_entry* e21;
                       
                        if (n21 && (e21 = n21->obj)) {
                          do {                
                            STRING_TYPE ms_s_city = e21->MS_S_CITY;
                            long v24 = e21->__av;
                            _c3.addOrDelOnZero(st6.modify(ms_s_city,v24), v24);
                            n21 = n21->nxt;
                          } while (n21 && (e21 = n21->obj) && h11 == n21->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se31, *e21)); 
                        }
                      }{ //slice 
                        const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135* i22 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135*>(COUNTSTORE_SALES1_E1_2_DELTA.index[2]);
                        const HASH_RES_t h13 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::hash(se35.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode* n22 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode*>(i22->slice(se35, h13));
                        COUNTSTORE_SALES1_E1_2_DELTA_entry* e22;
                       
                        if (n22 && (e22 = n22->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e22->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e22->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e22->STORE_SALES_SS_STORE_SK;
                            long v25 = e22->__av;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0* i23 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0*>(COUNTSTORE_SALES1_E1_2_P_3.index[1]);
                              const HASH_RES_t h12 = COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::hash(se34.modify0(store_sales_ss_store_sk));
                              HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode* n23 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode*>(i23->slice(se34, h12));
                              COUNTSTORE_SALES1_E1_2_P_3_entry* e23;
                             
                              if (n23 && (e23 = n23->obj)) {
                                do {                
                                  STRING_TYPE ms_s_city = e23->MS_S_CITY;
                                  long v26 = e23->__av;
                                  _c3.addOrDelOnZero(st7.modify(ms_s_city,(v25 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se32.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se33.modify(store_sales_ss_hdemo_sk)) * v26)))), (v25 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se32.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se33.modify(store_sales_ss_hdemo_sk)) * v26))));
                                  n23 = n23->nxt;
                                } while (n23 && (e23 = n23->obj) && h12 == n23->hash &&  COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::equals(se34, *e23)); 
                              }
                            }
                            n22 = n22->nxt;
                          } while (n22 && (e22 = n22->obj) && h13 == n22->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::equals(se35, *e22)); 
                        }
                      }{  // temp foreach
                        const HashIndex<tuple2_S_L, long>* i24 = static_cast<HashIndex<tuple2_S_L, long>*>(_c3.index[0]);
                        HashIndex<tuple2_S_L, long>::IdxNode* n24; 
                        tuple2_S_L* e24;
                      
                        for (size_t i = 0; i < i24->size_; i++)
                        {
                          n24 = i24->buckets_ + i;
                          while (n24 && (e24 = n24->obj))
                          {
                            STRING_TYPE ms_s_city = e24->_1;  
                            long v27 = e24->__av; 
                          DOUBLE_TYPE l10 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se36.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                          DOUBLE_TYPE l11 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se37.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                          STRING_TYPE l12 = Usubstring(ms_s_city, 1L, 30L);
                          COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,l12,ms_ss_ticket_number,l11,l10),(((v21 != 0 ? 1L : 0L) * (v22 * (v27 != 0 ? 1L : 0L))) * -1L));      
                            n24 = n24->nxt;
                          }
                        }
                      }
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h14 == n20->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se38, *e20)); 
                  }
                }
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i25 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n25; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long customer_c_customer_sk = e25->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e25->STORE_SALES_SS_ADDR_SK;
                long ms_ss_ticket_number = e25->MS_SS_TICKET_NUMBER;
                long v28 = e25->__av;
                { //slice 
                  const HashIndex_COUNTSTORE_SALES1_map_0* i26 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                  const HASH_RES_t h16 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se42.modify0(customer_c_customer_sk));
                  HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n26 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i26->slice(se42, h16));
                  COUNTSTORE_SALES1_entry* e26;
                 
                  if (n26 && (e26 = n26->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e26->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e26->CUSTOMER_C_LAST_NAME;
                      long v29 = e26->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i27 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h15 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se41.modify012(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n27 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i27->slice(se41, h15));
                        COUNTCUSTOMER1_E1_1_entry* e27;
                       
                        if (n27 && (e27 = n27->obj)) {
                          do {                
                            STRING_TYPE ms_s_city = e27->MS_S_CITY;
                            long v30 = e27->__av;
                            DOUBLE_TYPE l13 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se39.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                            DOUBLE_TYPE l14 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se40.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                            STRING_TYPE l15 = Usubstring(ms_s_city, 1L, 30L);
                            COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,l15,ms_ss_ticket_number,l14,l13),((v28 != 0 ? 1L : 0L) * (v29 * (v30 != 0 ? 1L : 0L))));
                            n27 = n27->nxt;
                          } while (n27 && (e27 = n27->obj) && h15 == n27->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se41, *e27)); 
                        }
                      }
                      n26 = n26->nxt;
                    } while (n26 && (e26 = n26->obj) && h16 == n26->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se42, *e26)); 
                  }
                }
              n25 = n25->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i28 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n28; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long customer_c_customer_sk = e28->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e28->STORE_SALES_SS_ADDR_SK;
                long ms_ss_ticket_number = e28->MS_SS_TICKET_NUMBER;
                long v31 = e28->__av;
                { //slice 
                  const HashIndex_COUNTSTORE_SALES1_map_0* i29 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                  const HASH_RES_t h22 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se58.modify0(customer_c_customer_sk));
                  HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n29 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i29->slice(se58, h22));
                  COUNTSTORE_SALES1_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e29->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e29->CUSTOMER_C_LAST_NAME;
                      long v32 = e29->__av;
                      _c4.clear();
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i30 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h17 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se43.modify012(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n30 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i30->slice(se43, h17));
                        COUNTCUSTOMER1_E1_1_entry* e30;
                       
                        if (n30 && (e30 = n30->obj)) {
                          do {                
                            STRING_TYPE ms_s_city = e30->MS_S_CITY;
                            long v34 = e30->__av;
                            _c4.addOrDelOnZero(st8.modify(ms_s_city,v34), v34);
                            n30 = n30->nxt;
                          } while (n30 && (e30 = n30->obj) && h17 == n30->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se43, *e30)); 
                        }
                      }{ //slice 
                        const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135* i31 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135*>(COUNTSTORE_SALES1_E1_2_DELTA.index[2]);
                        const HASH_RES_t h19 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::hash(se47.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode* n31 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode*>(i31->slice(se47, h19));
                        COUNTSTORE_SALES1_E1_2_DELTA_entry* e31;
                       
                        if (n31 && (e31 = n31->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e31->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e31->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e31->STORE_SALES_SS_STORE_SK;
                            long v35 = e31->__av;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0* i32 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0*>(COUNTSTORE_SALES1_E1_2_P_3.index[1]);
                              const HASH_RES_t h18 = COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::hash(se46.modify0(store_sales_ss_store_sk));
                              HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode* n32 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode*>(i32->slice(se46, h18));
                              COUNTSTORE_SALES1_E1_2_P_3_entry* e32;
                             
                              if (n32 && (e32 = n32->obj)) {
                                do {                
                                  STRING_TYPE ms_s_city = e32->MS_S_CITY;
                                  long v36 = e32->__av;
                                  _c4.addOrDelOnZero(st9.modify(ms_s_city,(v35 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se44.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se45.modify(store_sales_ss_hdemo_sk)) * v36)))), (v35 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se44.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se45.modify(store_sales_ss_hdemo_sk)) * v36))));
                                  n32 = n32->nxt;
                                } while (n32 && (e32 = n32->obj) && h18 == n32->hash &&  COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::equals(se46, *e32)); 
                              }
                            }
                            n31 = n31->nxt;
                          } while (n31 && (e31 = n31->obj) && h19 == n31->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::equals(se47, *e31)); 
                        }
                      }{  // temp foreach
                        const HashIndex<tuple2_S_L, long>* i33 = static_cast<HashIndex<tuple2_S_L, long>*>(_c4.index[0]);
                        HashIndex<tuple2_S_L, long>::IdxNode* n33; 
                        tuple2_S_L* e33;
                      
                        for (size_t i = 0; i < i33->size_; i++)
                        {
                          n33 = i33->buckets_ + i;
                          while (n33 && (e33 = n33->obj))
                          {
                            STRING_TYPE ms_s_city = e33->_1;  
                            long v37 = e33->__av; 
                          DOUBLE_TYPE agg3 = 0.0;
                          { //slice 
                            const HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135* i34 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135*>(COUNTSTORE_SALES9_L2_2_DELTA.index[1]);
                            const HASH_RES_t h20 = COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn::hash(se52.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                            HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135::IdxNode* n34 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135::IdxNode*>(i34->slice(se52, h20));
                            COUNTSTORE_SALES9_L2_2_DELTA_entry* e34;
                           
                            if (n34 && (e34 = n34->obj)) {
                              do {                
                                long store_sales_ss_sold_date_sk = e34->STORE_SALES_SS_SOLD_DATE_SK;
                                long store_sales_ss_hdemo_sk = e34->STORE_SALES_SS_HDEMO_SK;
                                long store_sales_ss_store_sk = e34->STORE_SALES_SS_STORE_SK;
                                DOUBLE_TYPE v38 = e34->__av;
                                agg3 += (v38 * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se49.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se50.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se51.modify(store_sales_ss_hdemo_sk)))));
                                n34 = n34->nxt;
                              } while (n34 && (e34 = n34->obj) && h20 == n34->hash &&  COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn::equals(se52, *e34)); 
                            }
                          }DOUBLE_TYPE l16 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se48.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg3);
                          DOUBLE_TYPE agg4 = 0.0;
                          { //slice 
                            const HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135* i35 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135*>(COUNTSTORE_SALES9_L3_2_DELTA.index[1]);
                            const HASH_RES_t h21 = COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn::hash(se57.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                            HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135::IdxNode* n35 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135::IdxNode*>(i35->slice(se57, h21));
                            COUNTSTORE_SALES9_L3_2_DELTA_entry* e35;
                           
                            if (n35 && (e35 = n35->obj)) {
                              do {                
                                long store_sales_ss_sold_date_sk = e35->STORE_SALES_SS_SOLD_DATE_SK;
                                long store_sales_ss_hdemo_sk = e35->STORE_SALES_SS_HDEMO_SK;
                                long store_sales_ss_store_sk = e35->STORE_SALES_SS_STORE_SK;
                                DOUBLE_TYPE v39 = e35->__av;
                                agg4 += (v39 * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se54.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se55.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se56.modify(store_sales_ss_hdemo_sk)))));
                                n35 = n35->nxt;
                              } while (n35 && (e35 = n35->obj) && h21 == n35->hash &&  COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn::equals(se57, *e35)); 
                            }
                          }DOUBLE_TYPE l17 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se53.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg4);
                          STRING_TYPE l18 = Usubstring(ms_s_city, 1L, 30L);
                          COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,l18,ms_ss_ticket_number,l17,l16),((v31 != 0 ? 1L : 0L) * (v32 * (v37 != 0 ? 1L : 0L))));      
                            n33 = n33->nxt;
                          }
                        }
                      }
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h22 == n29->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se58, *e29)); 
                  }
                }
              n28 = n28->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i36 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n36; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                long customer_c_customer_sk = e36->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e36->STORE_SALES_SS_ADDR_SK;
                long ms_ss_ticket_number = e36->MS_SS_TICKET_NUMBER;
                long v40 = e36->__av;
                { //slice 
                  const HashIndex_COUNTSTORE_SALES1_map_0* i37 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                  const HASH_RES_t h26 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se70.modify0(customer_c_customer_sk));
                  HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n37 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i37->slice(se70, h26));
                  COUNTSTORE_SALES1_entry* e37;
                 
                  if (n37 && (e37 = n37->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e37->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e37->CUSTOMER_C_LAST_NAME;
                      long v41 = e37->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i38 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h25 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se69.modify012(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n38 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i38->slice(se69, h25));
                        COUNTCUSTOMER1_E1_1_entry* e38;
                       
                        if (n38 && (e38 = n38->obj)) {
                          do {                
                            STRING_TYPE ms_s_city = e38->MS_S_CITY;
                            long v42 = e38->__av;
                            DOUBLE_TYPE agg5 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135* i39 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135*>(COUNTSTORE_SALES9_L2_2_DELTA.index[1]);
                              const HASH_RES_t h23 = COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn::hash(se63.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                              HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135::IdxNode* n39 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_135::IdxNode*>(i39->slice(se63, h23));
                              COUNTSTORE_SALES9_L2_2_DELTA_entry* e39;
                             
                              if (n39 && (e39 = n39->obj)) {
                                do {                
                                  long store_sales_ss_sold_date_sk = e39->STORE_SALES_SS_SOLD_DATE_SK;
                                  long store_sales_ss_hdemo_sk = e39->STORE_SALES_SS_HDEMO_SK;
                                  long store_sales_ss_store_sk = e39->STORE_SALES_SS_STORE_SK;
                                  DOUBLE_TYPE v43 = e39->__av;
                                  agg5 += (v43 * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se60.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se61.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se62.modify(store_sales_ss_hdemo_sk)))));
                                  n39 = n39->nxt;
                                } while (n39 && (e39 = n39->obj) && h23 == n39->hash &&  COUNTSTORE_SALES9_L2_2_DELTA_mapkey135_idxfn::equals(se63, *e39)); 
                              }
                            }DOUBLE_TYPE l19 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se59.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg5);
                            DOUBLE_TYPE agg6 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135* i40 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135*>(COUNTSTORE_SALES9_L3_2_DELTA.index[1]);
                              const HASH_RES_t h24 = COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn::hash(se68.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, ms_ss_ticket_number));
                              HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135::IdxNode* n40 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_135::IdxNode*>(i40->slice(se68, h24));
                              COUNTSTORE_SALES9_L3_2_DELTA_entry* e40;
                             
                              if (n40 && (e40 = n40->obj)) {
                                do {                
                                  long store_sales_ss_sold_date_sk = e40->STORE_SALES_SS_SOLD_DATE_SK;
                                  long store_sales_ss_hdemo_sk = e40->STORE_SALES_SS_HDEMO_SK;
                                  long store_sales_ss_store_sk = e40->STORE_SALES_SS_STORE_SK;
                                  DOUBLE_TYPE v44 = e40->__av;
                                  agg6 += (v44 * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se65.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se66.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se67.modify(store_sales_ss_hdemo_sk)))));
                                  n40 = n40->nxt;
                                } while (n40 && (e40 = n40->obj) && h24 == n40->hash &&  COUNTSTORE_SALES9_L3_2_DELTA_mapkey135_idxfn::equals(se68, *e40)); 
                              }
                            }DOUBLE_TYPE l20 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se64.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg6);
                            STRING_TYPE l21 = Usubstring(ms_s_city, 1L, 30L);
                            COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,l21,ms_ss_ticket_number,l20,l19),(((v40 != 0 ? 1L : 0L) * (v41 * (v42 != 0 ? 1L : 0L))) * -1L));
                            n38 = n38->nxt;
                          } while (n38 && (e38 = n38->obj) && h25 == n38->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se69, *e38)); 
                        }
                      }
                      n37 = n37->nxt;
                    } while (n37 && (e37 = n37->obj) && h26 == n37->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se70, *e37)); 
                  }
                }
              n36 = n36->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i41 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n41; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e41;
        
          for (size_t i = 0; i < i41->size_; i++)
          {
            n41 = i41->buckets_ + i;
            while (n41 && (e41 = n41->obj))
            {
                long store_sales_ss_sold_date_sk = e41->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e41->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e41->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e41->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e41->STORE_SALES_SS_STORE_SK;
                long ms_ss_ticket_number = e41->MS_SS_TICKET_NUMBER;
                long v45 = e41->__av;
                COUNTSTORE1_E1_2.addOrDelOnZero(se71.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number),(v45 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se72.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se73.modify(store_sales_ss_hdemo_sk)))));
              n41 = n41->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_012345* i42 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_012345*>(COUNTSTORE_SALES9_L2_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_012345::IdxNode* n42; 
          COUNTSTORE_SALES9_L2_2_DELTA_entry* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
                long store_sales_ss_sold_date_sk = e42->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e42->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e42->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e42->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e42->STORE_SALES_SS_STORE_SK;
                long ms_ss_ticket_number = e42->MS_SS_TICKET_NUMBER;
                DOUBLE_TYPE v46 = e42->__av;
                COUNTSTORE9_L2_2.addOrDelOnZero(se74.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number),(v46 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se75.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se76.modify(store_sales_ss_hdemo_sk)))));
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_012345* i43 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_012345*>(COUNTSTORE_SALES9_L3_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_012345::IdxNode* n43; 
          COUNTSTORE_SALES9_L3_2_DELTA_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long store_sales_ss_sold_date_sk = e43->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e43->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e43->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e43->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e43->STORE_SALES_SS_STORE_SK;
                long ms_ss_ticket_number = e43->MS_SS_TICKET_NUMBER;
                DOUBLE_TYPE v47 = e43->__av;
                COUNTSTORE9_L3_2.addOrDelOnZero(se77.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number),(v47 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se78.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se79.modify(store_sales_ss_hdemo_sk)))));
              n43 = n43->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i44 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n44; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e44;
        
          for (size_t i = 0; i < i44->size_; i++)
          {
            n44 = i44->buckets_ + i;
            while (n44 && (e44 = n44->obj))
            {
                long store_sales_ss_sold_date_sk = e44->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e44->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e44->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e44->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e44->STORE_SALES_SS_STORE_SK;
                long ms_ss_ticket_number = e44->MS_SS_TICKET_NUMBER;
                long v48 = e44->__av;
                { //slice 
                  const HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0* i45 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0*>(COUNTSTORE_SALES1_E1_2_P_3.index[1]);
                  const HASH_RES_t h27 = COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::hash(se83.modify0(store_sales_ss_store_sk));
                  HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode* n45 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode*>(i45->slice(se83, h27));
                  COUNTSTORE_SALES1_E1_2_P_3_entry* e45;
                 
                  if (n45 && (e45 = n45->obj)) {
                    do {                
                      STRING_TYPE ms_s_city = e45->MS_S_CITY;
                      long v49 = e45->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se80.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city),(v48 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se81.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se82.modify(store_sales_ss_hdemo_sk)) * v49))));
                      n45 = n45->nxt;
                    } while (n45 && (e45 = n45->obj) && h27 == n45->hash &&  COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::equals(se83, *e45)); 
                  }
                }
              n44 = n44->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_012345* i46 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_012345*>(COUNTSTORE_SALES9_L2_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L2_2_DELTA_map_012345::IdxNode* n46; 
          COUNTSTORE_SALES9_L2_2_DELTA_entry* e46;
        
          for (size_t i = 0; i < i46->size_; i++)
          {
            n46 = i46->buckets_ + i;
            while (n46 && (e46 = n46->obj))
            {
                long store_sales_ss_sold_date_sk = e46->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e46->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e46->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e46->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e46->STORE_SALES_SS_STORE_SK;
                long ms_ss_ticket_number = e46->MS_SS_TICKET_NUMBER;
                DOUBLE_TYPE v50 = e46->__av;
                { //slice 
                  const HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0* i47 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0*>(COUNTSTORE_SALES1_E1_2_P_3.index[1]);
                  const HASH_RES_t h28 = COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::hash(se87.modify0(store_sales_ss_store_sk));
                  HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode* n47 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode*>(i47->slice(se87, h28));
                  COUNTSTORE_SALES1_E1_2_P_3_entry* e47;
                 
                  if (n47 && (e47 = n47->obj)) {
                    do {                
                      STRING_TYPE ms_s_city = e47->MS_S_CITY;
                      long v51 = e47->__av;
                      COUNTCUSTOMER1_L3_1.addOrDelOnZero(se84.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city),(v50 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se85.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se86.modify(store_sales_ss_hdemo_sk)) * v51))));
                      n47 = n47->nxt;
                    } while (n47 && (e47 = n47->obj) && h28 == n47->hash &&  COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::equals(se87, *e47)); 
                  }
                }
              n46 = n46->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_012345* i48 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_012345*>(COUNTSTORE_SALES9_L3_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L3_2_DELTA_map_012345::IdxNode* n48; 
          COUNTSTORE_SALES9_L3_2_DELTA_entry* e48;
        
          for (size_t i = 0; i < i48->size_; i++)
          {
            n48 = i48->buckets_ + i;
            while (n48 && (e48 = n48->obj))
            {
                long store_sales_ss_sold_date_sk = e48->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e48->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e48->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e48->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e48->STORE_SALES_SS_STORE_SK;
                long ms_ss_ticket_number = e48->MS_SS_TICKET_NUMBER;
                DOUBLE_TYPE v52 = e48->__av;
                { //slice 
                  const HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0* i49 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0*>(COUNTSTORE_SALES1_E1_2_P_3.index[1]);
                  const HASH_RES_t h29 = COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::hash(se91.modify0(store_sales_ss_store_sk));
                  HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode* n49 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0::IdxNode*>(i49->slice(se91, h29));
                  COUNTSTORE_SALES1_E1_2_P_3_entry* e49;
                 
                  if (n49 && (e49 = n49->obj)) {
                    do {                
                      STRING_TYPE ms_s_city = e49->MS_S_CITY;
                      long v53 = e49->__av;
                      COUNTCUSTOMER1_L4_1.addOrDelOnZero(se88.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city),(v52 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se89.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se90.modify(store_sales_ss_hdemo_sk)) * v53))));
                      n49 = n49->nxt;
                    } while (n49 && (e49 = n49->obj) && h29 == n49->hash &&  COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn::equals(se91, *e49)); 
                  }
                }
              n48 = n48->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_CUSTOMER(TPCDSCustomerBatch& DELTA_CUSTOMER) {
      {  
        if (tS > 0) { tS += DELTA_CUSTOMER.size; return; }         
        tLastN += DELTA_CUSTOMER.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_CUSTOMER.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_CUSTOMER.size;

        COUNTCUSTOMER1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_CUSTOMER.size; i++) 
          {
                long customer_c_customer_sk = DELTA_CUSTOMER.c_customer_sk[i];
                // STRING_TYPE customer_c_customer_id = DELTA_CUSTOMER.c_customer_id[i];
                // long customer_c_current_cdemo_sk = DELTA_CUSTOMER.c_current_cdemo_sk[i];
                // long customer_c_current_hdemo_sk = DELTA_CUSTOMER.c_current_hdemo_sk[i];
                // long customer_c_current_addr_sk = DELTA_CUSTOMER.c_current_addr_sk[i];
                // long customer_c_first_shipto_date_sk = DELTA_CUSTOMER.c_first_shipto_date_sk[i];
                // long customer_c_first_sales_date_sk = DELTA_CUSTOMER.c_first_sales_date_sk[i];
                // STRING_TYPE customer_c_salutation = DELTA_CUSTOMER.c_salutation[i];
                STRING_TYPE customer_c_first_name = DELTA_CUSTOMER.c_first_name[i];
                STRING_TYPE customer_c_last_name = DELTA_CUSTOMER.c_last_name[i];
                // STRING_TYPE customer_c_preferred_cust_flag = DELTA_CUSTOMER.c_preferred_cust_flag[i];
                // long customer_c_birth_day = DELTA_CUSTOMER.c_birth_day[i];
                // long customer_c_birth_month = DELTA_CUSTOMER.c_birth_month[i];
                // long customer_c_birth_year = DELTA_CUSTOMER.c_birth_year[i];
                // STRING_TYPE customer_c_birth_country = DELTA_CUSTOMER.c_birth_country[i];
                // STRING_TYPE customer_c_login = DELTA_CUSTOMER.c_login[i];
                // STRING_TYPE customer_c_email_address = DELTA_CUSTOMER.c_email_address[i];
                // STRING_TYPE customer_c_last_review_date = DELTA_CUSTOMER.c_last_review_date[i];
                long v54 = 1L;
                COUNTCUSTOMER1_DELTA.addOrDelOnZero(se92.modify(customer_c_customer_sk,customer_c_first_name,customer_c_last_name),v54);
          }
        }

        {  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_012* i51 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_012*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_012::IdxNode* n51; 
          COUNTCUSTOMER1_DELTA_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long customer_c_customer_sk = e51->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e51->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e51->CUSTOMER_C_LAST_NAME;
                long v55 = e51->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i52 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[3]);
                  const HASH_RES_t h30 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se96.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n52 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i52->slice(se96, h30));
                  COUNTCUSTOMER1_E1_1_entry* e52;
                 
                  if (n52 && (e52 = n52->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e52->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e52->MS_SS_TICKET_NUMBER;
                      STRING_TYPE ms_s_city = e52->MS_S_CITY;
                      long v56 = e52->__av;
                      STRING_TYPE l22 = Usubstring(ms_s_city, 1L, 30L);
                      DOUBLE_TYPE l23 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se94.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                      DOUBLE_TYPE l24 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se95.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                      COUNT.addOrDelOnZero(se93.modify(customer_c_last_name,customer_c_first_name,l22,ms_ss_ticket_number,l24,l23),(v55 * (v56 != 0 ? 1L : 0L)));
                      n52 = n52->nxt;
                    } while (n52 && (e52 = n52->obj) && h30 == n52->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se96, *e52)); 
                  }
                }
              n51 = n51->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_012* i53 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_012*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_012::IdxNode* n53; 
          COUNTCUSTOMER1_DELTA_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long customer_c_customer_sk = e53->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e53->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e53->CUSTOMER_C_LAST_NAME;
                long v57 = e53->__av;
                COUNTSTORE_SALES1.addOrDelOnZero(se97.modify(customer_c_customer_sk,customer_c_first_name,customer_c_last_name),v57);
              n53 = n53->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_STORE(TPCDSStoreBatch& DELTA_STORE) {
      { 
        if (tS > 0) { tS += DELTA_STORE.size; return; }         
        tLastN += DELTA_STORE.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_STORE.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_STORE.size;

        COUNTSTORE6_DOMAIN1.clear();
        COUNTSTORE1_E1_2_DELTA.clear();
        COUNTSTORE1_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_STORE.size; i++) 
          {
                long store_sales_ss_store_sk = DELTA_STORE.s_store_sk[i];
                // STRING_TYPE store_s_store_id = DELTA_STORE.s_store_id[i];
                // date store_s_rec_start_date = DELTA_STORE.s_rec_start_date[i];
                // date store_s_rec_end_date = DELTA_STORE.s_rec_end_date[i];
                // long store_s_closed_date_sk = DELTA_STORE.s_closed_date_sk[i];
                // STRING_TYPE store_s_store_name = DELTA_STORE.s_store_name[i];
                long store_s_number_employees = DELTA_STORE.s_number_employees[i];
                // long store_s_floor_space = DELTA_STORE.s_floor_space[i];
                // STRING_TYPE store_s_hours = DELTA_STORE.s_hours[i];
                // STRING_TYPE store_s_manager = DELTA_STORE.s_manager[i];
                // long store_s_market_id = DELTA_STORE.s_market_id[i];
                // STRING_TYPE store_s_geography_class = DELTA_STORE.s_geography_class[i];
                // STRING_TYPE store_s_market_desc = DELTA_STORE.s_market_desc[i];
                // STRING_TYPE store_s_market_manager = DELTA_STORE.s_market_manager[i];
                // long store_s_division_id = DELTA_STORE.s_division_id[i];
                // STRING_TYPE store_s_division_name = DELTA_STORE.s_division_name[i];
                // long store_s_company_id = DELTA_STORE.s_company_id[i];
                // STRING_TYPE store_s_company_name = DELTA_STORE.s_company_name[i];
                // STRING_TYPE store_s_street_number = DELTA_STORE.s_street_number[i];
                // STRING_TYPE store_s_street_name = DELTA_STORE.s_street_name[i];
                // STRING_TYPE store_s_street_type = DELTA_STORE.s_street_type[i];
                // STRING_TYPE store_s_suite_number = DELTA_STORE.s_suite_number[i];
                STRING_TYPE store_s_city = DELTA_STORE.s_city[i];
                // STRING_TYPE store_s_county = DELTA_STORE.s_county[i];
                // STRING_TYPE store_s_state = DELTA_STORE.s_state[i];
                // STRING_TYPE store_s_zip = DELTA_STORE.s_zip[i];
                // STRING_TYPE store_s_country = DELTA_STORE.s_country[i];
                // DOUBLE_TYPE store_s_gmt_offset = DELTA_STORE.s_gmt_offset[i];
                // DOUBLE_TYPE store_s_tax_precentage = DELTA_STORE.s_tax_precentage[i];
                long v58 = 1L;
                (/*if */(295L >= store_s_number_employees && store_s_number_employees >= 200L) ? COUNTSTORE6_DOMAIN1.addOrDelOnZero(se98.modify(store_s_city),(v58 != 0 ? 1L : 0L)) : (void)0);
                long v59 = 1L;
                (/*if */(295L >= store_s_number_employees && store_s_number_employees >= 200L) ? COUNTSTORE1_E1_2_DELTA.addOrDelOnZero(se99.modify(store_sales_ss_store_sk,store_s_city),v59) : (void)0);
                long v60 = 1L;
                STRING_TYPE l25 = Usubstring(store_s_city, 1L, 30L);
                (/*if */(295L >= store_s_number_employees && store_s_number_employees >= 200L) ? COUNTSTORE1_DOMAIN1.addOrDelOnZero(se100.modify(l25),(v60 != 0 ? 1L : 0L)) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_COUNTSTORE1_DOMAIN1_map_0* i57 = static_cast<HashIndex_COUNTSTORE1_DOMAIN1_map_0*>(COUNTSTORE1_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE1_DOMAIN1_map_0::IdxNode* n57; 
          COUNTSTORE1_DOMAIN1_entry* e57;
        
          for (size_t i = 0; i < i57->size_; i++)
          {
            n57 = i57->buckets_ + i;
            while (n57 && (e57 = n57->obj))
            {
                STRING_TYPE __sql_expression_1 = e57->__SQL_EXPRESSION_1;
                long v61 = e57->__av;
                _c5.clear();
                {  // foreach
                  const HashIndex_COUNTSTORE_SALES1_map_012* i58 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
                  HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n58; 
                  COUNTSTORE_SALES1_entry* e58;
                
                  for (size_t i = 0; i < i58->size_; i++)
                  {
                    n58 = i58->buckets_ + i;
                    while (n58 && (e58 = n58->obj))
                    {
                        long customer_c_customer_sk = e58->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e58->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e58->CUSTOMER_C_LAST_NAME;
                        long v63 = e58->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i59 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[3]);
                          const HASH_RES_t h31 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se104.modify0(customer_c_customer_sk));
                          HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n59 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i59->slice(se104, h31));
                          COUNTCUSTOMER1_E1_1_entry* e59;
                         
                          if (n59 && (e59 = n59->obj)) {
                            do {                
                              long store_sales_ss_addr_sk = e59->STORE_SALES_SS_ADDR_SK;
                              long ms_ss_ticket_number = e59->MS_SS_TICKET_NUMBER;
                              STRING_TYPE ms_s_city = e59->MS_S_CITY;
                              long v64 = e59->__av;
                              DOUBLE_TYPE l26 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se102.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                              DOUBLE_TYPE l27 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se103.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                              (/*if */(__sql_expression_1 == Usubstring(ms_s_city, 1L, 30L)) ? _c5.addOrDelOnZero(st10.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l27,l26,((v63 * (v64 != 0 ? 1L : 0L)) * -2L)), ((v63 * (v64 != 0 ? 1L : 0L)) * -2L)) : (void)0);
                              n59 = n59->nxt;
                            } while (n59 && (e59 = n59->obj) && h31 == n59->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se104, *e59)); 
                          }
                        }
                      n58 = n58->nxt;
                    }
                  }
                }{  // foreach
                  const HashIndex_COUNTSTORE_SALES1_map_012* i60 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
                  HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n60; 
                  COUNTSTORE_SALES1_entry* e60;
                
                  for (size_t i = 0; i < i60->size_; i++)
                  {
                    n60 = i60->buckets_ + i;
                    while (n60 && (e60 = n60->obj))
                    {
                        long customer_c_customer_sk = e60->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e60->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e60->CUSTOMER_C_LAST_NAME;
                        long v65 = e60->__av;
                        _c6.clear();
                        { //slice 
                          const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i61 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[3]);
                          const HASH_RES_t h32 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se105.modify0(customer_c_customer_sk));
                          HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n61 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i61->slice(se105, h32));
                          COUNTCUSTOMER1_E1_1_entry* e61;
                         
                          if (n61 && (e61 = n61->obj)) {
                            do {                
                              long store_sales_ss_addr_sk = e61->STORE_SALES_SS_ADDR_SK;
                              long ms_ss_ticket_number = e61->MS_SS_TICKET_NUMBER;
                              STRING_TYPE ms_s_city = e61->MS_S_CITY;
                              long v67 = e61->__av;
                              _c6.addOrDelOnZero(st11.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city,v67), v67);
                              n61 = n61->nxt;
                            } while (n61 && (e61 = n61->obj) && h32 == n61->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se105, *e61)); 
                          }
                        }{  // foreach
                          const HashIndex_COUNTSTORE1_E1_2_DELTA_map_01* i62 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_01*>(COUNTSTORE1_E1_2_DELTA.index[0]);
                          HashIndex_COUNTSTORE1_E1_2_DELTA_map_01::IdxNode* n62; 
                          COUNTSTORE1_E1_2_DELTA_entry* e62;
                        
                          for (size_t i = 0; i < i62->size_; i++)
                          {
                            n62 = i62->buckets_ + i;
                            while (n62 && (e62 = n62->obj))
                            {
                                long store_sales_ss_store_sk = e62->STORE_SALES_SS_STORE_SK;
                                STRING_TYPE ms_s_city = e62->MS_S_CITY;
                                long v68 = e62->__av;
                                { //slice 
                                  const HashIndex_COUNTSTORE1_E1_2_map_02* i63 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_02*>(COUNTSTORE1_E1_2.index[1]);
                                  const HASH_RES_t h33 = COUNTSTORE1_E1_2_mapkey02_idxfn::hash(se106.modify02(customer_c_customer_sk, store_sales_ss_store_sk));
                                  HashIndex_COUNTSTORE1_E1_2_map_02::IdxNode* n63 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_02::IdxNode*>(i63->slice(se106, h33));
                                  COUNTSTORE1_E1_2_entry* e63;
                                 
                                  if (n63 && (e63 = n63->obj)) {
                                    do {                
                                      long store_sales_ss_addr_sk = e63->STORE_SALES_SS_ADDR_SK;
                                      long ms_ss_ticket_number = e63->MS_SS_TICKET_NUMBER;
                                      long v69 = e63->__av;
                                      _c6.addOrDelOnZero(st12.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city,(v68 * v69)), (v68 * v69));
                                      n63 = n63->nxt;
                                    } while (n63 && (e63 = n63->obj) && h33 == n63->hash &&  COUNTSTORE1_E1_2_mapkey02_idxfn::equals(se106, *e63)); 
                                  }
                                }
                              n62 = n62->nxt;
                            }
                          }
                        }{  // temp foreach
                          const HashIndex<tuple4_LLS_L, long>* i64 = static_cast<HashIndex<tuple4_LLS_L, long>*>(_c6.index[0]);
                          HashIndex<tuple4_LLS_L, long>::IdxNode* n64; 
                          tuple4_LLS_L* e64;
                        
                          for (size_t i = 0; i < i64->size_; i++)
                          {
                            n64 = i64->buckets_ + i;
                            while (n64 && (e64 = n64->obj))
                            {
                              long store_sales_ss_addr_sk = e64->_1;
                              long ms_ss_ticket_number = e64->_2;
                              STRING_TYPE ms_s_city = e64->_3;  
                              long v70 = e64->__av; 
                            DOUBLE_TYPE l28 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se107.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                            DOUBLE_TYPE l29 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se108.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                            (/*if */(__sql_expression_1 == Usubstring(ms_s_city, 1L, 30L)) ? _c5.addOrDelOnZero(st13.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l28,l29,(v65 * (v70 != 0 ? 1L : 0L))), (v65 * (v70 != 0 ? 1L : 0L))) : (void)0);      
                              n64 = n64->nxt;
                            }
                          }
                        }
                      n60 = n60->nxt;
                    }
                  }
                }{  // foreach
                  const HashIndex_COUNTSTORE_SALES1_map_012* i65 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
                  HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n65; 
                  COUNTSTORE_SALES1_entry* e65;
                
                  for (size_t i = 0; i < i65->size_; i++)
                  {
                    n65 = i65->buckets_ + i;
                    while (n65 && (e65 = n65->obj))
                    {
                        long customer_c_customer_sk = e65->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e65->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e65->CUSTOMER_C_LAST_NAME;
                        long v71 = e65->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i66 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[3]);
                          const HASH_RES_t h36 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se115.modify0(customer_c_customer_sk));
                          HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n66 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i66->slice(se115, h36));
                          COUNTCUSTOMER1_E1_1_entry* e66;
                         
                          if (n66 && (e66 = n66->obj)) {
                            do {                
                              long store_sales_ss_addr_sk = e66->STORE_SALES_SS_ADDR_SK;
                              long ms_ss_ticket_number = e66->MS_SS_TICKET_NUMBER;
                              STRING_TYPE ms_s_city = e66->MS_S_CITY;
                              long v72 = e66->__av;
                              DOUBLE_TYPE agg7 = 0.0;
                              { //slice 
                                const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i67 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                                const HASH_RES_t h34 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se111.modify1(ms_s_city));
                                HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n67 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i67->slice(se111, h34));
                                COUNTSTORE1_E1_2_DELTA_entry* e67;
                               
                                if (n67 && (e67 = n67->obj)) {
                                  do {                
                                    long store_sales_ss_store_sk = e67->STORE_SALES_SS_STORE_SK;
                                    long v73 = e67->__av;
                                    agg7 += (v73 * COUNTSTORE9_L2_2.getValueOrDefault(se110.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number)));
                                    n67 = n67->nxt;
                                  } while (n67 && (e67 = n67->obj) && h34 == n67->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se111, *e67)); 
                                }
                              }DOUBLE_TYPE l30 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se109.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg7);
                              DOUBLE_TYPE agg8 = 0.0;
                              { //slice 
                                const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i68 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                                const HASH_RES_t h35 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se114.modify1(ms_s_city));
                                HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n68 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i68->slice(se114, h35));
                                COUNTSTORE1_E1_2_DELTA_entry* e68;
                               
                                if (n68 && (e68 = n68->obj)) {
                                  do {                
                                    long store_sales_ss_store_sk = e68->STORE_SALES_SS_STORE_SK;
                                    long v74 = e68->__av;
                                    agg8 += (v74 * COUNTSTORE9_L3_2.getValueOrDefault(se113.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number)));
                                    n68 = n68->nxt;
                                  } while (n68 && (e68 = n68->obj) && h35 == n68->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se114, *e68)); 
                                }
                              }DOUBLE_TYPE l31 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se112.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg8);
                              (/*if */(__sql_expression_1 == Usubstring(ms_s_city, 1L, 30L)) ? _c5.addOrDelOnZero(st14.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l30,l31,(v71 * (v72 != 0 ? 1L : 0L))), (v71 * (v72 != 0 ? 1L : 0L))) : (void)0);
                              n66 = n66->nxt;
                            } while (n66 && (e66 = n66->obj) && h36 == n66->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se115, *e66)); 
                          }
                        }
                      n65 = n65->nxt;
                    }
                  }
                }{  // temp foreach
                  const HashIndex<tuple6_SSLDD_L, long>* i69 = static_cast<HashIndex<tuple6_SSLDD_L, long>*>(_c5.index[0]);
                  HashIndex<tuple6_SSLDD_L, long>::IdxNode* n69; 
                  tuple6_SSLDD_L* e69;
                
                  for (size_t i = 0; i < i69->size_; i++)
                  {
                    n69 = i69->buckets_ + i;
                    while (n69 && (e69 = n69->obj))
                    {
                      STRING_TYPE customer_c_first_name = e69->_1;
                      STRING_TYPE customer_c_last_name = e69->_2;
                      long ms_ss_ticket_number = e69->_3;
                      DOUBLE_TYPE ms_profit = e69->_4;
                      DOUBLE_TYPE ms_amt = e69->_5;  
                      long v75 = e69->__av; 
                    COUNT.addOrDelOnZero(se101.modify(customer_c_last_name,customer_c_first_name,__sql_expression_1,ms_ss_ticket_number,ms_amt,ms_profit),((v61 != 0 ? 1L : 0L) * v75));      
                      n69 = n69->nxt;
                    }
                  }
                }
              n57 = n57->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE6_DOMAIN1_map_0* i70 = static_cast<HashIndex_COUNTSTORE6_DOMAIN1_map_0*>(COUNTSTORE6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE6_DOMAIN1_map_0::IdxNode* n70; 
          COUNTSTORE6_DOMAIN1_entry* e70;
        
          for (size_t i = 0; i < i70->size_; i++)
          {
            n70 = i70->buckets_ + i;
            while (n70 && (e70 = n70->obj))
            {
                STRING_TYPE ms_s_city = e70->MS_S_CITY;
                long v76 = e70->__av;
                STRING_TYPE l32 = Usubstring(ms_s_city, 1L, 30L);
                {  // foreach
                  const HashIndex_COUNTSTORE_SALES1_map_012* i71 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
                  HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n71; 
                  COUNTSTORE_SALES1_entry* e71;
                
                  for (size_t i = 0; i < i71->size_; i++)
                  {
                    n71 = i71->buckets_ + i;
                    while (n71 && (e71 = n71->obj))
                    {
                        long customer_c_customer_sk = e71->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e71->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e71->CUSTOMER_C_LAST_NAME;
                        long v77 = e71->__av;
                        _c7.clear();
                        { //slice 
                          const HashIndex_COUNTCUSTOMER1_E1_1_map_03* i72 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03*>(COUNTCUSTOMER1_E1_1.index[4]);
                          const HASH_RES_t h37 = COUNTCUSTOMER1_E1_1_mapkey03_idxfn::hash(se116.modify03(customer_c_customer_sk, ms_s_city));
                          HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode* n72 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode*>(i72->slice(se116, h37));
                          COUNTCUSTOMER1_E1_1_entry* e72;
                         
                          if (n72 && (e72 = n72->obj)) {
                            do {                
                              long store_sales_ss_addr_sk = e72->STORE_SALES_SS_ADDR_SK;
                              long ms_ss_ticket_number = e72->MS_SS_TICKET_NUMBER;
                              long v79 = e72->__av;
                              _c7.addOrDelOnZero(st15.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,v79), v79);
                              n72 = n72->nxt;
                            } while (n72 && (e72 = n72->obj) && h37 == n72->hash &&  COUNTCUSTOMER1_E1_1_mapkey03_idxfn::equals(se116, *e72)); 
                          }
                        }{ //slice 
                          const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i73 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                          const HASH_RES_t h39 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se118.modify1(ms_s_city));
                          HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n73 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i73->slice(se118, h39));
                          COUNTSTORE1_E1_2_DELTA_entry* e73;
                         
                          if (n73 && (e73 = n73->obj)) {
                            do {                
                              long store_sales_ss_store_sk = e73->STORE_SALES_SS_STORE_SK;
                              long v80 = e73->__av;
                              { //slice 
                                const HashIndex_COUNTSTORE1_E1_2_map_02* i74 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_02*>(COUNTSTORE1_E1_2.index[1]);
                                const HASH_RES_t h38 = COUNTSTORE1_E1_2_mapkey02_idxfn::hash(se117.modify02(customer_c_customer_sk, store_sales_ss_store_sk));
                                HashIndex_COUNTSTORE1_E1_2_map_02::IdxNode* n74 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_02::IdxNode*>(i74->slice(se117, h38));
                                COUNTSTORE1_E1_2_entry* e74;
                               
                                if (n74 && (e74 = n74->obj)) {
                                  do {                
                                    long store_sales_ss_addr_sk = e74->STORE_SALES_SS_ADDR_SK;
                                    long ms_ss_ticket_number = e74->MS_SS_TICKET_NUMBER;
                                    long v81 = e74->__av;
                                    _c7.addOrDelOnZero(st16.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,(v80 * v81)), (v80 * v81));
                                    n74 = n74->nxt;
                                  } while (n74 && (e74 = n74->obj) && h38 == n74->hash &&  COUNTSTORE1_E1_2_mapkey02_idxfn::equals(se117, *e74)); 
                                }
                              }
                              n73 = n73->nxt;
                            } while (n73 && (e73 = n73->obj) && h39 == n73->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se118, *e73)); 
                          }
                        }{  // temp foreach
                          const HashIndex<tuple3_LL_L, long>* i75 = static_cast<HashIndex<tuple3_LL_L, long>*>(_c7.index[0]);
                          HashIndex<tuple3_LL_L, long>::IdxNode* n75; 
                          tuple3_LL_L* e75;
                        
                          for (size_t i = 0; i < i75->size_; i++)
                          {
                            n75 = i75->buckets_ + i;
                            while (n75 && (e75 = n75->obj))
                            {
                              long store_sales_ss_addr_sk = e75->_1;
                              long ms_ss_ticket_number = e75->_2;  
                              long v82 = e75->__av; 
                            DOUBLE_TYPE l33 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se119.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                            DOUBLE_TYPE l34 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se120.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                            COUNT.addOrDelOnZero(se101.modify(customer_c_last_name,customer_c_first_name,l32,ms_ss_ticket_number,l34,l33),(((v76 != 0 ? 1L : 0L) * (v77 * (v82 != 0 ? 1L : 0L))) * -1L));      
                              n75 = n75->nxt;
                            }
                          }
                        }
                      n71 = n71->nxt;
                    }
                  }
                }
              n70 = n70->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE6_DOMAIN1_map_0* i76 = static_cast<HashIndex_COUNTSTORE6_DOMAIN1_map_0*>(COUNTSTORE6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE6_DOMAIN1_map_0::IdxNode* n76; 
          COUNTSTORE6_DOMAIN1_entry* e76;
        
          for (size_t i = 0; i < i76->size_; i++)
          {
            n76 = i76->buckets_ + i;
            while (n76 && (e76 = n76->obj))
            {
                STRING_TYPE ms_s_city = e76->MS_S_CITY;
                long v83 = e76->__av;
                STRING_TYPE l35 = Usubstring(ms_s_city, 1L, 30L);
                {  // foreach
                  const HashIndex_COUNTSTORE_SALES1_map_012* i77 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
                  HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n77; 
                  COUNTSTORE_SALES1_entry* e77;
                
                  for (size_t i = 0; i < i77->size_; i++)
                  {
                    n77 = i77->buckets_ + i;
                    while (n77 && (e77 = n77->obj))
                    {
                        long customer_c_customer_sk = e77->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e77->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e77->CUSTOMER_C_LAST_NAME;
                        long v84 = e77->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER1_E1_1_map_03* i78 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03*>(COUNTCUSTOMER1_E1_1.index[4]);
                          const HASH_RES_t h40 = COUNTCUSTOMER1_E1_1_mapkey03_idxfn::hash(se123.modify03(customer_c_customer_sk, ms_s_city));
                          HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode* n78 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode*>(i78->slice(se123, h40));
                          COUNTCUSTOMER1_E1_1_entry* e78;
                         
                          if (n78 && (e78 = n78->obj)) {
                            do {                
                              long store_sales_ss_addr_sk = e78->STORE_SALES_SS_ADDR_SK;
                              long ms_ss_ticket_number = e78->MS_SS_TICKET_NUMBER;
                              long v85 = e78->__av;
                              DOUBLE_TYPE l36 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se121.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                              DOUBLE_TYPE l37 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se122.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                              COUNT.addOrDelOnZero(se101.modify(customer_c_last_name,customer_c_first_name,l35,ms_ss_ticket_number,l37,l36),((v83 != 0 ? 1L : 0L) * (v84 * (v85 != 0 ? 1L : 0L))));
                              n78 = n78->nxt;
                            } while (n78 && (e78 = n78->obj) && h40 == n78->hash &&  COUNTCUSTOMER1_E1_1_mapkey03_idxfn::equals(se123, *e78)); 
                          }
                        }
                      n77 = n77->nxt;
                    }
                  }
                }
              n76 = n76->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE6_DOMAIN1_map_0* i79 = static_cast<HashIndex_COUNTSTORE6_DOMAIN1_map_0*>(COUNTSTORE6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE6_DOMAIN1_map_0::IdxNode* n79; 
          COUNTSTORE6_DOMAIN1_entry* e79;
        
          for (size_t i = 0; i < i79->size_; i++)
          {
            n79 = i79->buckets_ + i;
            while (n79 && (e79 = n79->obj))
            {
                STRING_TYPE ms_s_city = e79->MS_S_CITY;
                long v86 = e79->__av;
                STRING_TYPE l38 = Usubstring(ms_s_city, 1L, 30L);
                {  // foreach
                  const HashIndex_COUNTSTORE_SALES1_map_012* i80 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
                  HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n80; 
                  COUNTSTORE_SALES1_entry* e80;
                
                  for (size_t i = 0; i < i80->size_; i++)
                  {
                    n80 = i80->buckets_ + i;
                    while (n80 && (e80 = n80->obj))
                    {
                        long customer_c_customer_sk = e80->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e80->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e80->CUSTOMER_C_LAST_NAME;
                        long v87 = e80->__av;
                        _c8.clear();
                        { //slice 
                          const HashIndex_COUNTCUSTOMER1_E1_1_map_03* i81 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03*>(COUNTCUSTOMER1_E1_1.index[4]);
                          const HASH_RES_t h41 = COUNTCUSTOMER1_E1_1_mapkey03_idxfn::hash(se124.modify03(customer_c_customer_sk, ms_s_city));
                          HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode* n81 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode*>(i81->slice(se124, h41));
                          COUNTCUSTOMER1_E1_1_entry* e81;
                         
                          if (n81 && (e81 = n81->obj)) {
                            do {                
                              long store_sales_ss_addr_sk = e81->STORE_SALES_SS_ADDR_SK;
                              long ms_ss_ticket_number = e81->MS_SS_TICKET_NUMBER;
                              long v89 = e81->__av;
                              _c8.addOrDelOnZero(st17.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,v89), v89);
                              n81 = n81->nxt;
                            } while (n81 && (e81 = n81->obj) && h41 == n81->hash &&  COUNTCUSTOMER1_E1_1_mapkey03_idxfn::equals(se124, *e81)); 
                          }
                        }{ //slice 
                          const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i82 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                          const HASH_RES_t h43 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se126.modify1(ms_s_city));
                          HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n82 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i82->slice(se126, h43));
                          COUNTSTORE1_E1_2_DELTA_entry* e82;
                         
                          if (n82 && (e82 = n82->obj)) {
                            do {                
                              long store_sales_ss_store_sk = e82->STORE_SALES_SS_STORE_SK;
                              long v90 = e82->__av;
                              { //slice 
                                const HashIndex_COUNTSTORE1_E1_2_map_02* i83 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_02*>(COUNTSTORE1_E1_2.index[1]);
                                const HASH_RES_t h42 = COUNTSTORE1_E1_2_mapkey02_idxfn::hash(se125.modify02(customer_c_customer_sk, store_sales_ss_store_sk));
                                HashIndex_COUNTSTORE1_E1_2_map_02::IdxNode* n83 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_02::IdxNode*>(i83->slice(se125, h42));
                                COUNTSTORE1_E1_2_entry* e83;
                               
                                if (n83 && (e83 = n83->obj)) {
                                  do {                
                                    long store_sales_ss_addr_sk = e83->STORE_SALES_SS_ADDR_SK;
                                    long ms_ss_ticket_number = e83->MS_SS_TICKET_NUMBER;
                                    long v91 = e83->__av;
                                    _c8.addOrDelOnZero(st18.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,(v90 * v91)), (v90 * v91));
                                    n83 = n83->nxt;
                                  } while (n83 && (e83 = n83->obj) && h42 == n83->hash &&  COUNTSTORE1_E1_2_mapkey02_idxfn::equals(se125, *e83)); 
                                }
                              }
                              n82 = n82->nxt;
                            } while (n82 && (e82 = n82->obj) && h43 == n82->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se126, *e82)); 
                          }
                        }{  // temp foreach
                          const HashIndex<tuple3_LL_L, long>* i84 = static_cast<HashIndex<tuple3_LL_L, long>*>(_c8.index[0]);
                          HashIndex<tuple3_LL_L, long>::IdxNode* n84; 
                          tuple3_LL_L* e84;
                        
                          for (size_t i = 0; i < i84->size_; i++)
                          {
                            n84 = i84->buckets_ + i;
                            while (n84 && (e84 = n84->obj))
                            {
                              long store_sales_ss_addr_sk = e84->_1;
                              long ms_ss_ticket_number = e84->_2;  
                              long v92 = e84->__av; 
                            DOUBLE_TYPE agg9 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i85 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                              const HASH_RES_t h44 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se129.modify1(ms_s_city));
                              HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n85 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i85->slice(se129, h44));
                              COUNTSTORE1_E1_2_DELTA_entry* e85;
                             
                              if (n85 && (e85 = n85->obj)) {
                                do {                
                                  long store_sales_ss_store_sk = e85->STORE_SALES_SS_STORE_SK;
                                  long v93 = e85->__av;
                                  agg9 += (v93 * COUNTSTORE9_L2_2.getValueOrDefault(se128.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number)));
                                  n85 = n85->nxt;
                                } while (n85 && (e85 = n85->obj) && h44 == n85->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se129, *e85)); 
                              }
                            }DOUBLE_TYPE l39 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se127.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg9);
                            DOUBLE_TYPE agg10 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i86 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                              const HASH_RES_t h45 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se132.modify1(ms_s_city));
                              HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n86 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i86->slice(se132, h45));
                              COUNTSTORE1_E1_2_DELTA_entry* e86;
                             
                              if (n86 && (e86 = n86->obj)) {
                                do {                
                                  long store_sales_ss_store_sk = e86->STORE_SALES_SS_STORE_SK;
                                  long v94 = e86->__av;
                                  agg10 += (v94 * COUNTSTORE9_L3_2.getValueOrDefault(se131.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number)));
                                  n86 = n86->nxt;
                                } while (n86 && (e86 = n86->obj) && h45 == n86->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se132, *e86)); 
                              }
                            }DOUBLE_TYPE l40 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se130.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg10);
                            COUNT.addOrDelOnZero(se101.modify(customer_c_last_name,customer_c_first_name,l38,ms_ss_ticket_number,l40,l39),((v86 != 0 ? 1L : 0L) * (v87 * (v92 != 0 ? 1L : 0L))));      
                              n84 = n84->nxt;
                            }
                          }
                        }
                      n80 = n80->nxt;
                    }
                  }
                }
              n79 = n79->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE6_DOMAIN1_map_0* i87 = static_cast<HashIndex_COUNTSTORE6_DOMAIN1_map_0*>(COUNTSTORE6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE6_DOMAIN1_map_0::IdxNode* n87; 
          COUNTSTORE6_DOMAIN1_entry* e87;
        
          for (size_t i = 0; i < i87->size_; i++)
          {
            n87 = i87->buckets_ + i;
            while (n87 && (e87 = n87->obj))
            {
                STRING_TYPE ms_s_city = e87->MS_S_CITY;
                long v95 = e87->__av;
                STRING_TYPE l41 = Usubstring(ms_s_city, 1L, 30L);
                {  // foreach
                  const HashIndex_COUNTSTORE_SALES1_map_012* i88 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
                  HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n88; 
                  COUNTSTORE_SALES1_entry* e88;
                
                  for (size_t i = 0; i < i88->size_; i++)
                  {
                    n88 = i88->buckets_ + i;
                    while (n88 && (e88 = n88->obj))
                    {
                        long customer_c_customer_sk = e88->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e88->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e88->CUSTOMER_C_LAST_NAME;
                        long v96 = e88->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER1_E1_1_map_03* i89 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03*>(COUNTCUSTOMER1_E1_1.index[4]);
                          const HASH_RES_t h48 = COUNTCUSTOMER1_E1_1_mapkey03_idxfn::hash(se139.modify03(customer_c_customer_sk, ms_s_city));
                          HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode* n89 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_03::IdxNode*>(i89->slice(se139, h48));
                          COUNTCUSTOMER1_E1_1_entry* e89;
                         
                          if (n89 && (e89 = n89->obj)) {
                            do {                
                              long store_sales_ss_addr_sk = e89->STORE_SALES_SS_ADDR_SK;
                              long ms_ss_ticket_number = e89->MS_SS_TICKET_NUMBER;
                              long v97 = e89->__av;
                              DOUBLE_TYPE agg11 = 0.0;
                              { //slice 
                                const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i90 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                                const HASH_RES_t h46 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se135.modify1(ms_s_city));
                                HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n90 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i90->slice(se135, h46));
                                COUNTSTORE1_E1_2_DELTA_entry* e90;
                               
                                if (n90 && (e90 = n90->obj)) {
                                  do {                
                                    long store_sales_ss_store_sk = e90->STORE_SALES_SS_STORE_SK;
                                    long v98 = e90->__av;
                                    agg11 += (v98 * COUNTSTORE9_L2_2.getValueOrDefault(se134.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number)));
                                    n90 = n90->nxt;
                                  } while (n90 && (e90 = n90->obj) && h46 == n90->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se135, *e90)); 
                                }
                              }DOUBLE_TYPE l42 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se133.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg11);
                              DOUBLE_TYPE agg12 = 0.0;
                              { //slice 
                                const HashIndex_COUNTSTORE1_E1_2_DELTA_map_1* i91 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1*>(COUNTSTORE1_E1_2_DELTA.index[1]);
                                const HASH_RES_t h47 = COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::hash(se138.modify1(ms_s_city));
                                HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode* n91 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_1::IdxNode*>(i91->slice(se138, h47));
                                COUNTSTORE1_E1_2_DELTA_entry* e91;
                               
                                if (n91 && (e91 = n91->obj)) {
                                  do {                
                                    long store_sales_ss_store_sk = e91->STORE_SALES_SS_STORE_SK;
                                    long v99 = e91->__av;
                                    agg12 += (v99 * COUNTSTORE9_L3_2.getValueOrDefault(se137.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,ms_ss_ticket_number)));
                                    n91 = n91->nxt;
                                  } while (n91 && (e91 = n91->obj) && h47 == n91->hash &&  COUNTSTORE1_E1_2_DELTA_mapkey1_idxfn::equals(se138, *e91)); 
                                }
                              }DOUBLE_TYPE l43 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se136.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + agg12);
                              COUNT.addOrDelOnZero(se101.modify(customer_c_last_name,customer_c_first_name,l41,ms_ss_ticket_number,l43,l42),(((v95 != 0 ? 1L : 0L) * (v96 * (v97 != 0 ? 1L : 0L))) * -1L));
                              n89 = n89->nxt;
                            } while (n89 && (e89 = n89->obj) && h48 == n89->hash &&  COUNTCUSTOMER1_E1_1_mapkey03_idxfn::equals(se139, *e89)); 
                          }
                        }
                      n88 = n88->nxt;
                    }
                  }
                }
              n87 = n87->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE1_E1_2_DELTA_map_01* i92 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_01*>(COUNTSTORE1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE1_E1_2_DELTA_map_01::IdxNode* n92; 
          COUNTSTORE1_E1_2_DELTA_entry* e92;
        
          for (size_t i = 0; i < i92->size_; i++)
          {
            n92 = i92->buckets_ + i;
            while (n92 && (e92 = n92->obj))
            {
                long store_sales_ss_store_sk = e92->STORE_SALES_SS_STORE_SK;
                STRING_TYPE ms_s_city = e92->MS_S_CITY;
                long v100 = e92->__av;
                COUNTSTORE_SALES1_E1_2_P_3.addOrDelOnZero(se140.modify(store_sales_ss_store_sk,ms_s_city),v100);
              n92 = n92->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE1_E1_2_DELTA_map_01* i93 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_01*>(COUNTSTORE1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE1_E1_2_DELTA_map_01::IdxNode* n93; 
          COUNTSTORE1_E1_2_DELTA_entry* e93;
        
          for (size_t i = 0; i < i93->size_; i++)
          {
            n93 = i93->buckets_ + i;
            while (n93 && (e93 = n93->obj))
            {
                long store_sales_ss_store_sk = e93->STORE_SALES_SS_STORE_SK;
                STRING_TYPE ms_s_city = e93->MS_S_CITY;
                long v101 = e93->__av;
                { //slice 
                  const HashIndex_COUNTSTORE1_E1_2_map_2* i94 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_2*>(COUNTSTORE1_E1_2.index[2]);
                  const HASH_RES_t h49 = COUNTSTORE1_E1_2_mapkey2_idxfn::hash(se142.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTSTORE1_E1_2_map_2::IdxNode* n94 = static_cast<HashIndex_COUNTSTORE1_E1_2_map_2::IdxNode*>(i94->slice(se142, h49));
                  COUNTSTORE1_E1_2_entry* e94;
                 
                  if (n94 && (e94 = n94->obj)) {
                    do {                
                      long customer_c_customer_sk = e94->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e94->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e94->MS_SS_TICKET_NUMBER;
                      long v102 = e94->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se141.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city),(v101 * v102));
                      n94 = n94->nxt;
                    } while (n94 && (e94 = n94->obj) && h49 == n94->hash &&  COUNTSTORE1_E1_2_mapkey2_idxfn::equals(se142, *e94)); 
                  }
                }
              n93 = n93->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE1_E1_2_DELTA_map_01* i95 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_01*>(COUNTSTORE1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE1_E1_2_DELTA_map_01::IdxNode* n95; 
          COUNTSTORE1_E1_2_DELTA_entry* e95;
        
          for (size_t i = 0; i < i95->size_; i++)
          {
            n95 = i95->buckets_ + i;
            while (n95 && (e95 = n95->obj))
            {
                long store_sales_ss_store_sk = e95->STORE_SALES_SS_STORE_SK;
                STRING_TYPE ms_s_city = e95->MS_S_CITY;
                long v103 = e95->__av;
                { //slice 
                  const HashIndex_COUNTSTORE9_L2_2_map_2* i96 = static_cast<HashIndex_COUNTSTORE9_L2_2_map_2*>(COUNTSTORE9_L2_2.index[1]);
                  const HASH_RES_t h50 = COUNTSTORE9_L2_2_mapkey2_idxfn::hash(se144.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTSTORE9_L2_2_map_2::IdxNode* n96 = static_cast<HashIndex_COUNTSTORE9_L2_2_map_2::IdxNode*>(i96->slice(se144, h50));
                  COUNTSTORE9_L2_2_entry* e96;
                 
                  if (n96 && (e96 = n96->obj)) {
                    do {                
                      long customer_c_customer_sk = e96->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e96->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e96->MS_SS_TICKET_NUMBER;
                      DOUBLE_TYPE v104 = e96->__av;
                      COUNTCUSTOMER1_L3_1.addOrDelOnZero(se143.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city),(v103 * v104));
                      n96 = n96->nxt;
                    } while (n96 && (e96 = n96->obj) && h50 == n96->hash &&  COUNTSTORE9_L2_2_mapkey2_idxfn::equals(se144, *e96)); 
                  }
                }
              n95 = n95->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE1_E1_2_DELTA_map_01* i97 = static_cast<HashIndex_COUNTSTORE1_E1_2_DELTA_map_01*>(COUNTSTORE1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE1_E1_2_DELTA_map_01::IdxNode* n97; 
          COUNTSTORE1_E1_2_DELTA_entry* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
                long store_sales_ss_store_sk = e97->STORE_SALES_SS_STORE_SK;
                STRING_TYPE ms_s_city = e97->MS_S_CITY;
                long v105 = e97->__av;
                { //slice 
                  const HashIndex_COUNTSTORE9_L3_2_map_2* i98 = static_cast<HashIndex_COUNTSTORE9_L3_2_map_2*>(COUNTSTORE9_L3_2.index[1]);
                  const HASH_RES_t h51 = COUNTSTORE9_L3_2_mapkey2_idxfn::hash(se146.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTSTORE9_L3_2_map_2::IdxNode* n98 = static_cast<HashIndex_COUNTSTORE9_L3_2_map_2::IdxNode*>(i98->slice(se146, h51));
                  COUNTSTORE9_L3_2_entry* e98;
                 
                  if (n98 && (e98 = n98->obj)) {
                    do {                
                      long customer_c_customer_sk = e98->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e98->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e98->MS_SS_TICKET_NUMBER;
                      DOUBLE_TYPE v106 = e98->__av;
                      COUNTCUSTOMER1_L4_1.addOrDelOnZero(se145.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city),(v105 * v106));
                      n98 = n98->nxt;
                    } while (n98 && (e98 = n98->obj) && h51 == n98->hash &&  COUNTSTORE9_L3_2_mapkey2_idxfn::equals(se146, *e98)); 
                  }
                }
              n97 = n97->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTSTORE_SALES1_E1_2_P_1.clear();
        long l44 = 1L;
        { //slice 
          const HashIndex_DATE_DIM_map_7* i99 = static_cast<HashIndex_DATE_DIM_map_7*>(DATE_DIM.index[1]);
          const HASH_RES_t h52 = DATE_DIM_mapkey7_idxfn::hash(se148.modify7(l44));
          HashIndex_DATE_DIM_map_7::IdxNode* n99 = static_cast<HashIndex_DATE_DIM_map_7::IdxNode*>(i99->slice(se148, h52));
          DATE_DIM_entry* e99;
         
          if (n99 && (e99 = n99->obj)) {
            do {                
              long store_sales_ss_sold_date_sk = e99->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e99->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e99->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e99->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e99->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e99->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_year = e99->DATE_DIM_D_YEAR;
              long date_dim_d_moy = e99->DATE_DIM_D_MOY;
              long date_dim_d_dom = e99->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e99->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e99->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e99->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e99->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_day_name = e99->DATE_DIM_D_DAY_NAME;
              STRING_TYPE date_dim_d_quarter_name = e99->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e99->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e99->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e99->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e99->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e99->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e99->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e99->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e99->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e99->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e99->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e99->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e99->DATE_DIM_D_CURRENT_YEAR;
              long v107 = e99->__av;
              (/*if */(((date_dim_d_year == 1998L) || (date_dim_d_year == 1999L) || (date_dim_d_year == 2000L))) ? COUNTSTORE_SALES1_E1_2_P_1.addOrDelOnZero(se147.modify(store_sales_ss_sold_date_sk),v107) : (void)0);
              n99 = n99->nxt;
            } while (n99 && (e99 = n99->obj) && h52 == n99->hash &&  DATE_DIM_mapkey7_idxfn::equals(se148, *e99)); 
          }
        }COUNTSTORE_SALES1_E1_2_P_2.clear();
        {  // foreach
          const HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234* i100 = static_cast<HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234*>(HOUSEHOLD_DEMOGRAPHICS.index[0]);
          HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234::IdxNode* n100; 
          HOUSEHOLD_DEMOGRAPHICS_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long store_sales_ss_hdemo_sk = e100->HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK;
                long household_demographics_hd_income_band_sk = e100->HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK;
                STRING_TYPE household_demographics_hd_buy_potential = e100->HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL;
                long household_demographics_hd_dep_count = e100->HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT;
                long household_demographics_hd_vehicle_count = e100->HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
                long v108 = e100->__av;
                long l45 = ((/*if */(household_demographics_hd_dep_count == 8L) ? 1L : 0L) + (/*if */(household_demographics_hd_vehicle_count > 0L) ? 1L : 0L));
                (/*if */(l45 > 0L) ? COUNTSTORE_SALES1_E1_2_P_2.addOrDelOnZero(se149.modify(store_sales_ss_hdemo_sk),v108) : (void)0);
              n100 = n100->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTSTORE_SALES9_L3_2_DELTA_entry se1;
    COUNTSTORE_SALES9_L2_2_DELTA_entry se2;
    COUNTSTORE_SALES6_DOMAIN1_entry se3;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se4;
    COUNTSTORE_SALES1_DOMAIN1_entry se5;
    COUNT_entry se6;
    COUNTCUSTOMER1_L4_1_entry se7;
    COUNTCUSTOMER1_L3_1_entry se8;
    tuple6_DDSSS_L st1;
    COUNTSTORE_SALES1_entry se9;
    COUNTCUSTOMER1_E1_1_entry se10;
    tuple4_LLS_L st2;
    COUNTCUSTOMER1_E1_1_entry se11;
    COUNTSTORE_SALES1_E1_2_P_1_entry se12;
    COUNTSTORE_SALES1_E1_2_P_2_entry se13;
    tuple4_LLS_L st3;
    COUNTSTORE_SALES1_E1_2_P_3_entry se14;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se15;
    COUNTCUSTOMER1_L3_1_entry se16;
    COUNTCUSTOMER1_L4_1_entry se17;
    tuple6_DDSSS_L st4;
    COUNTSTORE_SALES1_entry se18;
    COUNTCUSTOMER1_L3_1_entry se19;
    COUNTSTORE_SALES1_E1_2_P_3_entry se20;
    COUNTSTORE_SALES1_E1_2_P_1_entry se21;
    COUNTSTORE_SALES1_E1_2_P_2_entry se22;
    COUNTSTORE_SALES9_L2_2_DELTA_entry se23;
    COUNTCUSTOMER1_L4_1_entry se24;
    COUNTSTORE_SALES1_E1_2_P_3_entry se25;
    COUNTSTORE_SALES1_E1_2_P_1_entry se26;
    COUNTSTORE_SALES1_E1_2_P_2_entry se27;
    COUNTSTORE_SALES9_L3_2_DELTA_entry se28;
    tuple6_DDSSS_L st5;
    COUNTSTORE_SALES1_entry se29;
    COUNTCUSTOMER1_E1_1_entry se30;
    tuple2_S_L st6;
    COUNTCUSTOMER1_E1_1_entry se31;
    COUNTSTORE_SALES1_E1_2_P_1_entry se32;
    COUNTSTORE_SALES1_E1_2_P_2_entry se33;
    tuple2_S_L st7;
    COUNTSTORE_SALES1_E1_2_P_3_entry se34;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se35;
    COUNTCUSTOMER1_L3_1_entry se36;
    COUNTCUSTOMER1_L4_1_entry se37;
    COUNTSTORE_SALES1_entry se38;
    COUNTCUSTOMER1_L3_1_entry se39;
    COUNTCUSTOMER1_L4_1_entry se40;
    COUNTCUSTOMER1_E1_1_entry se41;
    COUNTSTORE_SALES1_entry se42;
    tuple2_S_L st8;
    COUNTCUSTOMER1_E1_1_entry se43;
    COUNTSTORE_SALES1_E1_2_P_1_entry se44;
    COUNTSTORE_SALES1_E1_2_P_2_entry se45;
    tuple2_S_L st9;
    COUNTSTORE_SALES1_E1_2_P_3_entry se46;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se47;
    COUNTCUSTOMER1_L3_1_entry se48;
    COUNTSTORE_SALES1_E1_2_P_3_entry se49;
    COUNTSTORE_SALES1_E1_2_P_1_entry se50;
    COUNTSTORE_SALES1_E1_2_P_2_entry se51;
    COUNTSTORE_SALES9_L2_2_DELTA_entry se52;
    COUNTCUSTOMER1_L4_1_entry se53;
    COUNTSTORE_SALES1_E1_2_P_3_entry se54;
    COUNTSTORE_SALES1_E1_2_P_1_entry se55;
    COUNTSTORE_SALES1_E1_2_P_2_entry se56;
    COUNTSTORE_SALES9_L3_2_DELTA_entry se57;
    COUNTSTORE_SALES1_entry se58;
    COUNTCUSTOMER1_L3_1_entry se59;
    COUNTSTORE_SALES1_E1_2_P_3_entry se60;
    COUNTSTORE_SALES1_E1_2_P_1_entry se61;
    COUNTSTORE_SALES1_E1_2_P_2_entry se62;
    COUNTSTORE_SALES9_L2_2_DELTA_entry se63;
    COUNTCUSTOMER1_L4_1_entry se64;
    COUNTSTORE_SALES1_E1_2_P_3_entry se65;
    COUNTSTORE_SALES1_E1_2_P_1_entry se66;
    COUNTSTORE_SALES1_E1_2_P_2_entry se67;
    COUNTSTORE_SALES9_L3_2_DELTA_entry se68;
    COUNTCUSTOMER1_E1_1_entry se69;
    COUNTSTORE_SALES1_entry se70;
    COUNTSTORE1_E1_2_entry se71;
    COUNTSTORE_SALES1_E1_2_P_1_entry se72;
    COUNTSTORE_SALES1_E1_2_P_2_entry se73;
    COUNTSTORE9_L2_2_entry se74;
    COUNTSTORE_SALES1_E1_2_P_1_entry se75;
    COUNTSTORE_SALES1_E1_2_P_2_entry se76;
    COUNTSTORE9_L3_2_entry se77;
    COUNTSTORE_SALES1_E1_2_P_1_entry se78;
    COUNTSTORE_SALES1_E1_2_P_2_entry se79;
    COUNTCUSTOMER1_E1_1_entry se80;
    COUNTSTORE_SALES1_E1_2_P_1_entry se81;
    COUNTSTORE_SALES1_E1_2_P_2_entry se82;
    COUNTSTORE_SALES1_E1_2_P_3_entry se83;
    COUNTCUSTOMER1_L3_1_entry se84;
    COUNTSTORE_SALES1_E1_2_P_1_entry se85;
    COUNTSTORE_SALES1_E1_2_P_2_entry se86;
    COUNTSTORE_SALES1_E1_2_P_3_entry se87;
    COUNTCUSTOMER1_L4_1_entry se88;
    COUNTSTORE_SALES1_E1_2_P_1_entry se89;
    COUNTSTORE_SALES1_E1_2_P_2_entry se90;
    COUNTSTORE_SALES1_E1_2_P_3_entry se91;
    COUNTCUSTOMER1_DELTA_entry se92;
    COUNT_entry se93;
    COUNTCUSTOMER1_L3_1_entry se94;
    COUNTCUSTOMER1_L4_1_entry se95;
    COUNTCUSTOMER1_E1_1_entry se96;
    COUNTSTORE_SALES1_entry se97;
    COUNTSTORE6_DOMAIN1_entry se98;
    COUNTSTORE1_E1_2_DELTA_entry se99;
    COUNTSTORE1_DOMAIN1_entry se100;
    COUNT_entry se101;
    COUNTCUSTOMER1_L4_1_entry se102;
    COUNTCUSTOMER1_L3_1_entry se103;
    tuple6_SSLDD_L st10;
    COUNTCUSTOMER1_E1_1_entry se104;
    tuple4_LLS_L st11;
    COUNTCUSTOMER1_E1_1_entry se105;
    tuple4_LLS_L st12;
    COUNTSTORE1_E1_2_entry se106;
    COUNTCUSTOMER1_L3_1_entry se107;
    COUNTCUSTOMER1_L4_1_entry se108;
    tuple6_SSLDD_L st13;
    COUNTCUSTOMER1_L3_1_entry se109;
    COUNTSTORE9_L2_2_entry se110;
    COUNTSTORE1_E1_2_DELTA_entry se111;
    COUNTCUSTOMER1_L4_1_entry se112;
    COUNTSTORE9_L3_2_entry se113;
    COUNTSTORE1_E1_2_DELTA_entry se114;
    tuple6_SSLDD_L st14;
    COUNTCUSTOMER1_E1_1_entry se115;
    tuple3_LL_L st15;
    COUNTCUSTOMER1_E1_1_entry se116;
    tuple3_LL_L st16;
    COUNTSTORE1_E1_2_entry se117;
    COUNTSTORE1_E1_2_DELTA_entry se118;
    COUNTCUSTOMER1_L3_1_entry se119;
    COUNTCUSTOMER1_L4_1_entry se120;
    COUNTCUSTOMER1_L3_1_entry se121;
    COUNTCUSTOMER1_L4_1_entry se122;
    COUNTCUSTOMER1_E1_1_entry se123;
    tuple3_LL_L st17;
    COUNTCUSTOMER1_E1_1_entry se124;
    tuple3_LL_L st18;
    COUNTSTORE1_E1_2_entry se125;
    COUNTSTORE1_E1_2_DELTA_entry se126;
    COUNTCUSTOMER1_L3_1_entry se127;
    COUNTSTORE9_L2_2_entry se128;
    COUNTSTORE1_E1_2_DELTA_entry se129;
    COUNTCUSTOMER1_L4_1_entry se130;
    COUNTSTORE9_L3_2_entry se131;
    COUNTSTORE1_E1_2_DELTA_entry se132;
    COUNTCUSTOMER1_L3_1_entry se133;
    COUNTSTORE9_L2_2_entry se134;
    COUNTSTORE1_E1_2_DELTA_entry se135;
    COUNTCUSTOMER1_L4_1_entry se136;
    COUNTSTORE9_L3_2_entry se137;
    COUNTSTORE1_E1_2_DELTA_entry se138;
    COUNTCUSTOMER1_E1_1_entry se139;
    COUNTSTORE_SALES1_E1_2_P_3_entry se140;
    COUNTCUSTOMER1_E1_1_entry se141;
    COUNTSTORE1_E1_2_entry se142;
    COUNTCUSTOMER1_L3_1_entry se143;
    COUNTSTORE9_L2_2_entry se144;
    COUNTCUSTOMER1_L4_1_entry se145;
    COUNTSTORE9_L3_2_entry se146;
    COUNTSTORE_SALES1_E1_2_P_1_entry se147;
    DATE_DIM_entry se148;
    COUNTSTORE_SALES1_E1_2_P_2_entry se149;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    HOUSEHOLD_DEMOGRAPHICS_map HOUSEHOLD_DEMOGRAPHICS;
    COUNTSTORE1_DOMAIN1_map COUNTSTORE1_DOMAIN1;
    COUNTSTORE1_E1_2_DELTA_map COUNTSTORE1_E1_2_DELTA;
    COUNTSTORE1_E1_2_map COUNTSTORE1_E1_2;
    COUNTSTORE6_DOMAIN1_map COUNTSTORE6_DOMAIN1;
    COUNTSTORE9_L2_2_map COUNTSTORE9_L2_2;
    COUNTSTORE9_L3_2_map COUNTSTORE9_L3_2;
    COUNTSTORE_SALES1_DOMAIN1_map COUNTSTORE_SALES1_DOMAIN1;
    COUNTSTORE_SALES1_map COUNTSTORE_SALES1;
    COUNTSTORE_SALES1_E1_2_DELTA_map COUNTSTORE_SALES1_E1_2_DELTA;
    COUNTSTORE_SALES1_E1_2_P_1_map COUNTSTORE_SALES1_E1_2_P_1;
    COUNTSTORE_SALES1_E1_2_P_2_map COUNTSTORE_SALES1_E1_2_P_2;
    COUNTSTORE_SALES1_E1_2_P_3_map COUNTSTORE_SALES1_E1_2_P_3;
    COUNTSTORE_SALES6_DOMAIN1_map COUNTSTORE_SALES6_DOMAIN1;
    COUNTSTORE_SALES9_L2_2_DELTA_map COUNTSTORE_SALES9_L2_2_DELTA;
    COUNTSTORE_SALES9_L3_2_DELTA_map COUNTSTORE_SALES9_L3_2_DELTA;
    COUNTCUSTOMER1_DELTA_map COUNTCUSTOMER1_DELTA;
    COUNTCUSTOMER1_E1_1_map COUNTCUSTOMER1_E1_1;
    COUNTCUSTOMER1_L3_1_map COUNTCUSTOMER1_L3_1;
    COUNTCUSTOMER1_L4_1_map COUNTCUSTOMER1_L4_1;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_STORE_map DELTA_STORE;
    MultiHashMap<tuple6_DDSSS_L,long,HashIndex<tuple6_DDSSS_L,long> > _c1;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c4;
    MultiHashMap<tuple3_LL_L,long,HashIndex<tuple3_LL_L,long> > _c7;
    MultiHashMap<tuple4_LLS_L,long,HashIndex<tuple4_LLS_L,long> > _c6;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c3;
    MultiHashMap<tuple4_LLS_L,long,HashIndex<tuple4_LLS_L,long> > _c2;
    MultiHashMap<tuple6_SSLDD_L,long,HashIndex<tuple6_SSLDD_L,long> > _c5;
    MultiHashMap<tuple3_LL_L,long,HashIndex<tuple3_LL_L,long> > _c8;
    
  
  };

}
