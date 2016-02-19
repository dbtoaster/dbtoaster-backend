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
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  
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
    STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_SALUTATION; STRING_TYPE CUSTOMER_C_PREFERRED_CUST_FLAG; long DN_SS_TICKET_NUMBER; long DN_CNT; long __av; 
    explicit COUNT_entry() { /*CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_SALUTATION = ""; CUSTOMER_C_PREFERRED_CUST_FLAG = ""; DN_SS_TICKET_NUMBER = 0L; DN_CNT = 0L; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const long c5, const long c6) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_SALUTATION = c2; CUSTOMER_C_PREFERRED_CUST_FLAG = c3; DN_SS_TICKET_NUMBER = c4; DN_CNT = c5; __av = c6; }
    COUNT_entry(const COUNT_entry& other) : CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_SALUTATION( other.CUSTOMER_C_SALUTATION ), CUSTOMER_C_PREFERRED_CUST_FLAG( other.CUSTOMER_C_PREFERRED_CUST_FLAG ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), DN_CNT( other.DN_CNT ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const long c5) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_SALUTATION = c2; CUSTOMER_C_PREFERRED_CUST_FLAG = c3; DN_SS_TICKET_NUMBER = c4; DN_CNT = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_SALUTATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_PREFERRED_CUST_FLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_CNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_SALUTATION);
      hash_combine(h, e.CUSTOMER_C_PREFERRED_CUST_FLAG);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      hash_combine(h, e.DN_CNT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_SALUTATION == y.CUSTOMER_C_SALUTATION && x.CUSTOMER_C_PREFERRED_CUST_FLAG == y.CUSTOMER_C_PREFERRED_CUST_FLAG && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER && x.DN_CNT == y.DN_CNT;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true> HashIndex_COUNT_map_012345;
  
  struct COUNTSTORE_SALES1_DOMAIN1_entry {
    long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE_SALES1_DOMAIN1_entry() { /*DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_DOMAIN1_entry(const long c0, const long c1) { DN_SS_TICKET_NUMBER = c0; __av = c1; }
    COUNTSTORE_SALES1_DOMAIN1_entry(const COUNTSTORE_SALES1_DOMAIN1_entry& other) : DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_DOMAIN1_entry& modify(const long c0) { DN_SS_TICKET_NUMBER = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_DOMAIN1_entry& x, const COUNTSTORE_SALES1_DOMAIN1_entry& y) {
      return x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_DOMAIN1_entry,long,
    HashIndex<COUNTSTORE_SALES1_DOMAIN1_entry,long,COUNTSTORE_SALES1_DOMAIN1_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_DOMAIN1_map;
  typedef HashIndex<COUNTSTORE_SALES1_DOMAIN1_entry,long,COUNTSTORE_SALES1_DOMAIN1_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0;
  
  struct COUNTSTORE_SALES1_entry {
    long CUSTOMER_C_CUSTOMER_SK; STRING_TYPE CUSTOMER_C_SALUTATION; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_PREFERRED_CUST_FLAG; long __av; 
    explicit COUNTSTORE_SALES1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_SALUTATION = ""; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_PREFERRED_CUST_FLAG = ""; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const long c5) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_SALUTATION = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; CUSTOMER_C_PREFERRED_CUST_FLAG = c4; __av = c5; }
    COUNTSTORE_SALES1_entry(const COUNTSTORE_SALES1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_SALUTATION( other.CUSTOMER_C_SALUTATION ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_PREFERRED_CUST_FLAG( other.CUSTOMER_C_PREFERRED_CUST_FLAG ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_SALUTATION = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; CUSTOMER_C_PREFERRED_CUST_FLAG = c4;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_SALUTATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_PREFERRED_CUST_FLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_SALUTATION);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_PREFERRED_CUST_FLAG);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_entry& x, const COUNTSTORE_SALES1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_SALUTATION == y.CUSTOMER_C_SALUTATION && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_PREFERRED_CUST_FLAG == y.CUSTOMER_C_PREFERRED_CUST_FLAG;
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
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey01234_idxfn,true>,
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false>
  > COUNTSTORE_SALES1_map;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey01234_idxfn,true> HashIndex_COUNTSTORE_SALES1_map_01234;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false> HashIndex_COUNTSTORE_SALES1_map_0;
  
  struct COUNTSTORE_SALES3_L1_2_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE_SALES3_L1_2_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_2_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3; DN_SS_TICKET_NUMBER = c4; __av = c5; }
    COUNTSTORE_SALES3_L1_2_DELTA_entry(const COUNTSTORE_SALES3_L1_2_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_2_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3; DN_SS_TICKET_NUMBER = c4;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES3_L1_2_DELTA_entry& modify4(const long c4) { DN_SS_TICKET_NUMBER = c4;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES3_L1_2_DELTA_entry& modify14(const long c1, const long c4) { CUSTOMER_C_CUSTOMER_SK = c1; DN_SS_TICKET_NUMBER = c4;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_2_DELTA_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_2_DELTA_entry& x, const COUNTSTORE_SALES3_L1_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES3_L1_2_DELTA_mapkey4_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_2_DELTA_entry& x, const COUNTSTORE_SALES3_L1_2_DELTA_entry& y) {
      return x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES3_L1_2_DELTA_mapkey14_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_2_DELTA_entry& x, const COUNTSTORE_SALES3_L1_2_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_2_DELTA_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_2_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_DELTA_mapkey01234_idxfn,true>,
    HashIndex<COUNTSTORE_SALES3_L1_2_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_DELTA_mapkey4_idxfn,false>,
    HashIndex<COUNTSTORE_SALES3_L1_2_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_DELTA_mapkey14_idxfn,false>
  > COUNTSTORE_SALES3_L1_2_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_2_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_DELTA_mapkey01234_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_01234;
  typedef HashIndex<COUNTSTORE_SALES3_L1_2_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_DELTA_mapkey4_idxfn,false> HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_4;
  typedef HashIndex<COUNTSTORE_SALES3_L1_2_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_DELTA_mapkey14_idxfn,false> HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_14;
  
  struct COUNTSTORE_SALES3_L1_2_P_1_entry {
    long STORE_SALES_SS_HDEMO_SK; long __av; 
    explicit COUNTSTORE_SALES3_L1_2_P_1_entry() { /*STORE_SALES_SS_HDEMO_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_2_P_1_entry(const long c0, const long c1) { STORE_SALES_SS_HDEMO_SK = c0; __av = c1; }
    COUNTSTORE_SALES3_L1_2_P_1_entry(const COUNTSTORE_SALES3_L1_2_P_1_entry& other) : STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_2_P_1_entry& modify(const long c0) { STORE_SALES_SS_HDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_2_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_2_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_2_P_1_entry& x, const COUNTSTORE_SALES3_L1_2_P_1_entry& y) {
      return x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_2_P_1_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_2_P_1_entry,long,COUNTSTORE_SALES3_L1_2_P_1_mapkey0_idxfn,true>
  > COUNTSTORE_SALES3_L1_2_P_1_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_2_P_1_entry,long,COUNTSTORE_SALES3_L1_2_P_1_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_2_P_1_map_0;
  
  struct COUNTSTORE_SALES3_L1_2_P_2_entry {
    long STORE_SALES_SS_STORE_SK; long __av; 
    explicit COUNTSTORE_SALES3_L1_2_P_2_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_2_P_2_entry(const long c0, const long c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    COUNTSTORE_SALES3_L1_2_P_2_entry(const COUNTSTORE_SALES3_L1_2_P_2_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_2_P_2_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_2_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_2_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_2_P_2_entry& x, const COUNTSTORE_SALES3_L1_2_P_2_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_2_P_2_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_2_P_2_entry,long,COUNTSTORE_SALES3_L1_2_P_2_mapkey0_idxfn,true>
  > COUNTSTORE_SALES3_L1_2_P_2_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_2_P_2_entry,long,COUNTSTORE_SALES3_L1_2_P_2_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_2_P_2_map_0;
  
  struct COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry {
    long STORE_SALES_SS_STORE_SK; long __av; 
    explicit COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry(const long c0, const long c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry(const COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry& x, const COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_mapkey0_idxfn,true>
  > COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry,long,COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map_0;
  
  struct COUNTSTORE_SALES3_L1_2_P_3_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit COUNTSTORE_SALES3_L1_2_P_3_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_2_P_3_entry(const long c0, const long c1) { STORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    COUNTSTORE_SALES3_L1_2_P_3_entry(const COUNTSTORE_SALES3_L1_2_P_3_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_2_P_3_entry& modify(const long c0) { STORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_2_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_2_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_2_P_3_entry& x, const COUNTSTORE_SALES3_L1_2_P_3_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_2_P_3_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_2_P_3_entry,long,COUNTSTORE_SALES3_L1_2_P_3_mapkey0_idxfn,true>
  > COUNTSTORE_SALES3_L1_2_P_3_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_2_P_3_entry,long,COUNTSTORE_SALES3_L1_2_P_3_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_2_P_3_map_0;
  
  struct COUNTCUSTOMER1_DELTA_entry {
    long CUSTOMER_C_CUSTOMER_SK; STRING_TYPE CUSTOMER_C_SALUTATION; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_PREFERRED_CUST_FLAG; long __av; 
    explicit COUNTCUSTOMER1_DELTA_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_SALUTATION = ""; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_PREFERRED_CUST_FLAG = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const long c5) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_SALUTATION = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; CUSTOMER_C_PREFERRED_CUST_FLAG = c4; __av = c5; }
    COUNTCUSTOMER1_DELTA_entry(const COUNTCUSTOMER1_DELTA_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_SALUTATION( other.CUSTOMER_C_SALUTATION ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_PREFERRED_CUST_FLAG( other.CUSTOMER_C_PREFERRED_CUST_FLAG ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_SALUTATION = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; CUSTOMER_C_PREFERRED_CUST_FLAG = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_SALUTATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_PREFERRED_CUST_FLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_DELTA_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_SALUTATION);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_PREFERRED_CUST_FLAG);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_DELTA_entry& x, const COUNTCUSTOMER1_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_SALUTATION == y.CUSTOMER_C_SALUTATION && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_PREFERRED_CUST_FLAG == y.CUSTOMER_C_PREFERRED_CUST_FLAG;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_DELTA_entry,long,
    HashIndex<COUNTCUSTOMER1_DELTA_entry,long,COUNTCUSTOMER1_DELTA_mapkey01234_idxfn,true>
  > COUNTCUSTOMER1_DELTA_map;
  typedef HashIndex<COUNTCUSTOMER1_DELTA_entry,long,COUNTCUSTOMER1_DELTA_mapkey01234_idxfn,true> HashIndex_COUNTCUSTOMER1_DELTA_map_01234;
  
  struct COUNTCUSTOMER1_E1_1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTCUSTOMER1_E1_1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1_entry(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; DN_SS_TICKET_NUMBER = c1; __av = c2; }
    COUNTCUSTOMER1_E1_1_entry(const COUNTCUSTOMER1_E1_1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify(const long c0, const long c1) { CUSTOMER_C_CUSTOMER_SK = c0; DN_SS_TICKET_NUMBER = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify1(const long c1) { DN_SS_TICKET_NUMBER = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
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
  
  typedef MultiHashMap<COUNTCUSTOMER1_E1_1_entry,long,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey01_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey1_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false>
  > COUNTCUSTOMER1_E1_1_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey01_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1_map_01;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey1_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_1;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_0;
  
  struct COUNTCUSTOMER1_E1_1STORE1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTCUSTOMER1_E1_1STORE1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1STORE1_entry(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_STORE_SK = c1; DN_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTCUSTOMER1_E1_1STORE1_entry(const COUNTCUSTOMER1_E1_1STORE1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1STORE1_entry& modify(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_STORE_SK = c1; DN_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1STORE1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1STORE1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1STORE1_entry& x, const COUNTCUSTOMER1_E1_1STORE1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1STORE1_entry& x, const COUNTCUSTOMER1_E1_1STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_E1_1STORE1_entry,long,
    HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey012_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey1_idxfn,false>
  > COUNTCUSTOMER1_E1_1STORE1_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey012_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_012;
  typedef HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey1_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_1;
  
  struct tuple6_LSSSS_L {
    long _1; STRING_TYPE _2; STRING_TYPE _3; STRING_TYPE _4; STRING_TYPE _5; long __av;
    explicit tuple6_LSSSS_L() { }
    explicit tuple6_LSSSS_L(const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; __av = c__av;}
    int operator==(const tuple6_LSSSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5)); }
    FORCE_INLINE tuple6_LSSSS_L& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; __av = c__av; return *this; }
    static bool equals(const tuple6_LSSSS_L &x, const tuple6_LSSSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5)); }
    static long hash(const tuple6_LSSSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      return h;
    }
  };
  struct tuple2_L_L {
    long _1; long __av;
    explicit tuple2_L_L() { }
    explicit tuple2_L_L(const long c1, long c__av=0L) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_L_L &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_L_L& modify(const long c0, long c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_L_L &x, const tuple2_L_L &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_L_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
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
    data_t(): tlq_t(), _c1(16U), _c2(16U) {
      c7 = STRING_TYPE("Ziebach County");
      c8 = STRING_TYPE("Walker County");
      c4 = STRING_TYPE("Luce County");
      c3 = STRING_TYPE("Barrow County");
      c9 = STRING_TYPE(">10000");
      c5 = STRING_TYPE("Fairfield County");
      c10 = STRING_TYPE("5001-10000");
      c6 = STRING_TYPE("Richland County");
      c2 = STRING_TYPE("Franklin Parish");
      c1 = STRING_TYPE("Daviess County");
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

        COUNTSTORE_SALES3_L1_2_DELTA.clear();
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
                // long store_sales_ss_addr_sk = DELTA_STORE_SALES.ss_addr_sk[i];
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
                // DOUBLE_TYPE store_sales_ss_coupon_amt = DELTA_STORE_SALES.ss_coupon_amt[i];
                // DOUBLE_TYPE store_sales_ss_net_paid = DELTA_STORE_SALES.ss_net_paid[i];
                // DOUBLE_TYPE store_sales_ss_net_paid_inc_tax = DELTA_STORE_SALES.ss_net_paid_inc_tax[i];
                // DOUBLE_TYPE store_sales_ss_net_profit = DELTA_STORE_SALES.ss_net_profit[i];
                long v1 = 1L;
                COUNTSTORE_SALES3_L1_2_DELTA.addOrDelOnZero(se1.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),v1);
                long v2 = 1L;
                COUNTSTORE_SALES1_DOMAIN1.addOrDelOnZero(se2.modify(store_sales_ss_ticket_number),(v2 != 0 ? 1L : 0L));
          }
        }

        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0* i3 = static_cast<HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0*>(COUNTSTORE_SALES1_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0::IdxNode* n3; 
          COUNTSTORE_SALES1_DOMAIN1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long dn_ss_ticket_number = e3->DN_SS_TICKET_NUMBER;
                long v3 = e3->__av;
                _c1.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_1* i4 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_1*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h2 = COUNTCUSTOMER1_E1_1_mapkey1_idxfn::hash(se6.modify1(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_1::IdxNode* n4 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_1::IdxNode*>(i4->slice(se6, h2));
                  COUNTCUSTOMER1_E1_1_entry* e4;
                 
                  if (n4 && (e4 = n4->obj)) {
                    do {                
                      long customer_c_customer_sk = e4->CUSTOMER_C_CUSTOMER_SK;
                      long v5 = e4->__av;
                      long l1 = COUNTCUSTOMER1_E1_1.getValueOrDefault(se4.modify(customer_c_customer_sk,dn_ss_ticket_number));
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_map_0* i5 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                        const HASH_RES_t h1 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se5.modify0(customer_c_customer_sk));
                        HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n5 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i5->slice(se5, h1));
                        COUNTSTORE_SALES1_entry* e5;
                       
                        if (n5 && (e5 = n5->obj)) {
                          do {                
                            STRING_TYPE customer_c_salutation = e5->CUSTOMER_C_SALUTATION;
                            STRING_TYPE customer_c_first_name = e5->CUSTOMER_C_FIRST_NAME;
                            STRING_TYPE customer_c_last_name = e5->CUSTOMER_C_LAST_NAME;
                            STRING_TYPE customer_c_preferred_cust_flag = e5->CUSTOMER_C_PREFERRED_CUST_FLAG;
                            long v6 = e5->__av;
                            (/*if */(20L >= l1 && l1 >= 15L) ? _c1.addOrDelOnZero(st1.modify(l1,customer_c_salutation,customer_c_first_name,customer_c_last_name,customer_c_preferred_cust_flag,(((v5 != 0 ? 1L : 0L) * v6) * -1L)), (((v5 != 0 ? 1L : 0L) * v6) * -1L)) : (void)0);
                            n5 = n5->nxt;
                          } while (n5 && (e5 = n5->obj) && h1 == n5->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se5, *e5)); 
                        }
                      }
                      n4 = n4->nxt;
                    } while (n4 && (e4 = n4->obj) && h2 == n4->hash &&  COUNTCUSTOMER1_E1_1_mapkey1_idxfn::equals(se6, *e4)); 
                  }
                }_c2.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_1* i6 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_1*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h3 = COUNTCUSTOMER1_E1_1_mapkey1_idxfn::hash(se7.modify1(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_1::IdxNode* n6 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_1::IdxNode*>(i6->slice(se7, h3));
                  COUNTCUSTOMER1_E1_1_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      long customer_c_customer_sk = e6->CUSTOMER_C_CUSTOMER_SK;
                      long v8 = e6->__av;
                      _c2.addOrDelOnZero(st2.modify(customer_c_customer_sk,v8), v8);
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h3 == n6->hash &&  COUNTCUSTOMER1_E1_1_mapkey1_idxfn::equals(se7, *e6)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_4* i7 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_4*>(COUNTSTORE_SALES3_L1_2_DELTA.index[1]);
                  const HASH_RES_t h4 = COUNTSTORE_SALES3_L1_2_DELTA_mapkey4_idxfn::hash(se11.modify4(dn_ss_ticket_number));
                  HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_4::IdxNode* n7 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_4::IdxNode*>(i7->slice(se11, h4));
                  COUNTSTORE_SALES3_L1_2_DELTA_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      long store_sales_ss_sold_date_sk = e7->STORE_SALES_SS_SOLD_DATE_SK;
                      long customer_c_customer_sk = e7->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_hdemo_sk = e7->STORE_SALES_SS_HDEMO_SK;
                      long store_sales_ss_store_sk = e7->STORE_SALES_SS_STORE_SK;
                      long v9 = e7->__av;
                      _c2.addOrDelOnZero(st3.modify(customer_c_customer_sk,(v9 * (COUNTSTORE_SALES3_L1_2_P_1.getValueOrDefault(se8.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES3_L1_2_P_2.getValueOrDefault(se9.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_2_P_3.getValueOrDefault(se10.modify(store_sales_ss_sold_date_sk)))))), (v9 * (COUNTSTORE_SALES3_L1_2_P_1.getValueOrDefault(se8.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES3_L1_2_P_2.getValueOrDefault(se9.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_2_P_3.getValueOrDefault(se10.modify(store_sales_ss_sold_date_sk))))));
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h4 == n7->hash &&  COUNTSTORE_SALES3_L1_2_DELTA_mapkey4_idxfn::equals(se11, *e7)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_L_L, long>* i8 = static_cast<HashIndex<tuple2_L_L, long>*>(_c2.index[0]);
                  HashIndex<tuple2_L_L, long>::IdxNode* n8; 
                  tuple2_L_L* e8;
                
                  for (size_t i = 0; i < i8->size_; i++)
                  {
                    n8 = i8->buckets_ + i;
                    while (n8 && (e8 = n8->obj))
                    {
                      long customer_c_customer_sk = e8->_1;  
                      long v10 = e8->__av; 
                    long agg1 = 0L;
                    { //slice 
                      const HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_14* i9 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_14*>(COUNTSTORE_SALES3_L1_2_DELTA.index[2]);
                      const HASH_RES_t h5 = COUNTSTORE_SALES3_L1_2_DELTA_mapkey14_idxfn::hash(se16.modify14(customer_c_customer_sk, dn_ss_ticket_number));
                      HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_14::IdxNode* n9 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_14::IdxNode*>(i9->slice(se16, h5));
                      COUNTSTORE_SALES3_L1_2_DELTA_entry* e9;
                     
                      if (n9 && (e9 = n9->obj)) {
                        do {                
                          long store_sales_ss_sold_date_sk = e9->STORE_SALES_SS_SOLD_DATE_SK;
                          long store_sales_ss_hdemo_sk = e9->STORE_SALES_SS_HDEMO_SK;
                          long store_sales_ss_store_sk = e9->STORE_SALES_SS_STORE_SK;
                          long v11 = e9->__av;
                          agg1 += (v11 * (COUNTSTORE_SALES3_L1_2_P_1.getValueOrDefault(se13.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES3_L1_2_P_2.getValueOrDefault(se14.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_2_P_3.getValueOrDefault(se15.modify(store_sales_ss_sold_date_sk)))));
                          n9 = n9->nxt;
                        } while (n9 && (e9 = n9->obj) && h5 == n9->hash &&  COUNTSTORE_SALES3_L1_2_DELTA_mapkey14_idxfn::equals(se16, *e9)); 
                      }
                    }long l2 = (COUNTCUSTOMER1_E1_1.getValueOrDefault(se12.modify(customer_c_customer_sk,dn_ss_ticket_number)) + agg1);
                    { //slice 
                      const HashIndex_COUNTSTORE_SALES1_map_0* i10 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                      const HASH_RES_t h6 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se17.modify0(customer_c_customer_sk));
                      HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n10 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i10->slice(se17, h6));
                      COUNTSTORE_SALES1_entry* e10;
                     
                      if (n10 && (e10 = n10->obj)) {
                        do {                
                          STRING_TYPE customer_c_salutation = e10->CUSTOMER_C_SALUTATION;
                          STRING_TYPE customer_c_first_name = e10->CUSTOMER_C_FIRST_NAME;
                          STRING_TYPE customer_c_last_name = e10->CUSTOMER_C_LAST_NAME;
                          STRING_TYPE customer_c_preferred_cust_flag = e10->CUSTOMER_C_PREFERRED_CUST_FLAG;
                          long v12 = e10->__av;
                          (/*if */(20L >= l2 && l2 >= 15L) ? _c1.addOrDelOnZero(st4.modify(l2,customer_c_salutation,customer_c_first_name,customer_c_last_name,customer_c_preferred_cust_flag,((v10 != 0 ? 1L : 0L) * v12)), ((v10 != 0 ? 1L : 0L) * v12)) : (void)0);
                          n10 = n10->nxt;
                        } while (n10 && (e10 = n10->obj) && h6 == n10->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se17, *e10)); 
                      }
                    }      
                      n8 = n8->nxt;
                    }
                  }
                }{  // temp foreach
                  const HashIndex<tuple6_LSSSS_L, long>* i11 = static_cast<HashIndex<tuple6_LSSSS_L, long>*>(_c1.index[0]);
                  HashIndex<tuple6_LSSSS_L, long>::IdxNode* n11; 
                  tuple6_LSSSS_L* e11;
                
                  for (size_t i = 0; i < i11->size_; i++)
                  {
                    n11 = i11->buckets_ + i;
                    while (n11 && (e11 = n11->obj))
                    {
                      long dn_cnt = e11->_1;
                      STRING_TYPE customer_c_salutation = e11->_2;
                      STRING_TYPE customer_c_first_name = e11->_3;
                      STRING_TYPE customer_c_last_name = e11->_4;
                      STRING_TYPE customer_c_preferred_cust_flag = e11->_5;  
                      long v13 = e11->__av; 
                    COUNT.addOrDelOnZero(se3.modify(customer_c_last_name,customer_c_first_name,customer_c_salutation,customer_c_preferred_cust_flag,dn_ss_ticket_number,dn_cnt),((v3 != 0 ? 1L : 0L) * v13));      
                      n11 = n11->nxt;
                    }
                  }
                }
              n3 = n3->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_01234* i12 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_01234*>(COUNTSTORE_SALES3_L1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_01234::IdxNode* n12; 
          COUNTSTORE_SALES3_L1_2_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long store_sales_ss_sold_date_sk = e12->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e12->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e12->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_store_sk = e12->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e12->DN_SS_TICKET_NUMBER;
                long v14 = e12->__av;
                COUNTCUSTOMER1_E1_1.addOrDelOnZero(se18.modify(customer_c_customer_sk,dn_ss_ticket_number),(v14 * (COUNTSTORE_SALES3_L1_2_P_1.getValueOrDefault(se19.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES3_L1_2_P_2.getValueOrDefault(se20.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_2_P_3.getValueOrDefault(se21.modify(store_sales_ss_sold_date_sk))))));
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_01234* i13 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_01234*>(COUNTSTORE_SALES3_L1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES3_L1_2_DELTA_map_01234::IdxNode* n13; 
          COUNTSTORE_SALES3_L1_2_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long store_sales_ss_sold_date_sk = e13->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e13->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e13->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_store_sk = e13->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e13->DN_SS_TICKET_NUMBER;
                long v15 = e13->__av;
                COUNTCUSTOMER1_E1_1STORE1.addOrDelOnZero(se22.modify(customer_c_customer_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v15 * (COUNTSTORE_SALES3_L1_2_P_1.getValueOrDefault(se23.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES3_L1_2_P_3.getValueOrDefault(se24.modify(store_sales_ss_sold_date_sk)))));
              n13 = n13->nxt;
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
                STRING_TYPE customer_c_salutation = DELTA_CUSTOMER.c_salutation[i];
                STRING_TYPE customer_c_first_name = DELTA_CUSTOMER.c_first_name[i];
                STRING_TYPE customer_c_last_name = DELTA_CUSTOMER.c_last_name[i];
                STRING_TYPE customer_c_preferred_cust_flag = DELTA_CUSTOMER.c_preferred_cust_flag[i];
                // long customer_c_birth_day = DELTA_CUSTOMER.c_birth_day[i];
                // long customer_c_birth_month = DELTA_CUSTOMER.c_birth_month[i];
                // long customer_c_birth_year = DELTA_CUSTOMER.c_birth_year[i];
                // STRING_TYPE customer_c_birth_country = DELTA_CUSTOMER.c_birth_country[i];
                // STRING_TYPE customer_c_login = DELTA_CUSTOMER.c_login[i];
                // STRING_TYPE customer_c_email_address = DELTA_CUSTOMER.c_email_address[i];
                // STRING_TYPE customer_c_last_review_date = DELTA_CUSTOMER.c_last_review_date[i];
                long v16 = 1L;
                COUNTCUSTOMER1_DELTA.addOrDelOnZero(se25.modify(customer_c_customer_sk,customer_c_salutation,customer_c_first_name,customer_c_last_name,customer_c_preferred_cust_flag),v16);
          }
        }

        {  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_01234* i15 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_01234*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_01234::IdxNode* n15; 
          COUNTCUSTOMER1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long customer_c_customer_sk = e15->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_salutation = e15->CUSTOMER_C_SALUTATION;
                STRING_TYPE customer_c_first_name = e15->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e15->CUSTOMER_C_LAST_NAME;
                STRING_TYPE customer_c_preferred_cust_flag = e15->CUSTOMER_C_PREFERRED_CUST_FLAG;
                long v17 = e15->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i16 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                  const HASH_RES_t h7 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se28.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n16 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i16->slice(se28, h7));
                  COUNTCUSTOMER1_E1_1_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      long dn_ss_ticket_number = e16->DN_SS_TICKET_NUMBER;
                      long v18 = e16->__av;
                      long l3 = COUNTCUSTOMER1_E1_1.getValueOrDefault(se27.modify(customer_c_customer_sk,dn_ss_ticket_number));
                      (/*if */(20L >= l3 && l3 >= 15L) ? COUNT.addOrDelOnZero(se26.modify(customer_c_last_name,customer_c_first_name,customer_c_salutation,customer_c_preferred_cust_flag,dn_ss_ticket_number,l3),(v17 * (v18 != 0 ? 1L : 0L))) : (void)0);
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h7 == n16->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se28, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_01234* i17 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_01234*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_01234::IdxNode* n17; 
          COUNTCUSTOMER1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long customer_c_customer_sk = e17->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_salutation = e17->CUSTOMER_C_SALUTATION;
                STRING_TYPE customer_c_first_name = e17->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e17->CUSTOMER_C_LAST_NAME;
                STRING_TYPE customer_c_preferred_cust_flag = e17->CUSTOMER_C_PREFERRED_CUST_FLAG;
                long v19 = e17->__av;
                COUNTSTORE_SALES1.addOrDelOnZero(se29.modify(customer_c_customer_sk,customer_c_salutation,customer_c_first_name,customer_c_last_name,customer_c_preferred_cust_flag),v19);
              n17 = n17->nxt;
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

        COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_STORE.size; i++) 
          {
                long store_sales_ss_store_sk = DELTA_STORE.s_store_sk[i];
                // STRING_TYPE store_s_store_id = DELTA_STORE.s_store_id[i];
                // date store_s_rec_start_date = DELTA_STORE.s_rec_start_date[i];
                // date store_s_rec_end_date = DELTA_STORE.s_rec_end_date[i];
                // long store_s_closed_date_sk = DELTA_STORE.s_closed_date_sk[i];
                // STRING_TYPE store_s_store_name = DELTA_STORE.s_store_name[i];
                // long store_s_number_employees = DELTA_STORE.s_number_employees[i];
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
                // STRING_TYPE store_s_city = DELTA_STORE.s_city[i];
                STRING_TYPE store_s_county = DELTA_STORE.s_county[i];
                // STRING_TYPE store_s_state = DELTA_STORE.s_state[i];
                // STRING_TYPE store_s_zip = DELTA_STORE.s_zip[i];
                // STRING_TYPE store_s_country = DELTA_STORE.s_country[i];
                // DOUBLE_TYPE store_s_gmt_offset = DELTA_STORE.s_gmt_offset[i];
                // DOUBLE_TYPE store_s_tax_precentage = DELTA_STORE.s_tax_precentage[i];
                long v20 = 1L;
                (/*if */(((store_s_county == c1) || (store_s_county == c2) || (store_s_county == c3) || (store_s_county == c4) || (store_s_county == c5) || (store_s_county == c6) || (store_s_county == c7) || (store_s_county == c8))) ? COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA.addOrDelOnZero(se30.modify(store_sales_ss_store_sk),v20) : (void)0);

          }
        }

        {  // foreach
          const HashIndex_COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map_0* i19 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map_0::IdxNode* n19; 
          COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long store_sales_ss_store_sk = e19->STORE_SALES_SS_STORE_SK;
                long v21 = e19->__av;
                COUNTSTORE_SALES3_L1_2_P_2.addOrDelOnZero(se31.modify(store_sales_ss_store_sk),v21);
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map_0* i20 = static_cast<HashIndex_COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map_0::IdxNode* n20; 
          COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
                long store_sales_ss_store_sk = e20->STORE_SALES_SS_STORE_SK;
                long v22 = e20->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_1* i21 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_1*>(COUNTCUSTOMER1_E1_1STORE1.index[1]);
                  const HASH_RES_t h8 = COUNTCUSTOMER1_E1_1STORE1_mapkey1_idxfn::hash(se33.modify1(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_1::IdxNode* n21 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_1::IdxNode*>(i21->slice(se33, h8));
                  COUNTCUSTOMER1_E1_1STORE1_entry* e21;
                 
                  if (n21 && (e21 = n21->obj)) {
                    do {                
                      long customer_c_customer_sk = e21->CUSTOMER_C_CUSTOMER_SK;
                      long dn_ss_ticket_number = e21->DN_SS_TICKET_NUMBER;
                      long v23 = e21->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se32.modify(customer_c_customer_sk,dn_ss_ticket_number),(v22 * v23));
                      n21 = n21->nxt;
                    } while (n21 && (e21 = n21->obj) && h8 == n21->hash &&  COUNTCUSTOMER1_E1_1STORE1_mapkey1_idxfn::equals(se33, *e21)); 
                  }
                }
              n20 = n20->nxt;
            }
          }
        }COUNT.clear();
        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_01234* i22 = static_cast<HashIndex_COUNTSTORE_SALES1_map_01234*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_01234::IdxNode* n22; 
          COUNTSTORE_SALES1_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long customer_c_customer_sk = e22->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_salutation = e22->CUSTOMER_C_SALUTATION;
                STRING_TYPE customer_c_first_name = e22->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e22->CUSTOMER_C_LAST_NAME;
                STRING_TYPE customer_c_preferred_cust_flag = e22->CUSTOMER_C_PREFERRED_CUST_FLAG;
                long v24 = e22->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i23 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                  const HASH_RES_t h9 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se36.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n23 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i23->slice(se36, h9));
                  COUNTCUSTOMER1_E1_1_entry* e23;
                 
                  if (n23 && (e23 = n23->obj)) {
                    do {                
                      long dn_ss_ticket_number = e23->DN_SS_TICKET_NUMBER;
                      long v25 = e23->__av;
                      long l4 = COUNTCUSTOMER1_E1_1.getValueOrDefault(se35.modify(customer_c_customer_sk,dn_ss_ticket_number));
                      (/*if */(20L >= l4 && l4 >= 15L) ? COUNT.addOrDelOnZero(se34.modify(customer_c_last_name,customer_c_first_name,customer_c_salutation,customer_c_preferred_cust_flag,dn_ss_ticket_number,l4),(v24 * (v25 != 0 ? 1L : 0L))) : (void)0);
                      n23 = n23->nxt;
                    } while (n23 && (e23 = n23->obj) && h9 == n23->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se36, *e23)); 
                  }
                }
              n22 = n22->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTSTORE_SALES3_L1_2_P_1.clear();
        {  // foreach
          const HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234* i24 = static_cast<HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234*>(HOUSEHOLD_DEMOGRAPHICS.index[0]);
          HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234::IdxNode* n24; 
          HOUSEHOLD_DEMOGRAPHICS_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long store_sales_ss_hdemo_sk = e24->HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK;
                long household_demographics_hd_income_band_sk = e24->HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK;
                STRING_TYPE household_demographics_hd_buy_potential = e24->HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL;
                long household_demographics_hd_dep_count = e24->HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT;
                long household_demographics_hd_vehicle_count = e24->HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
                long v26 = e24->__av;
                DOUBLE_TYPE l5 = (household_demographics_hd_dep_count * Udiv(household_demographics_hd_vehicle_count));
                long l6 = ((/*if */(household_demographics_hd_buy_potential == c9) ? 1L : 0L) + (/*if */(household_demographics_hd_buy_potential == c10) ? 1L : 0L));
                (/*if */(household_demographics_hd_vehicle_count > 0L && l5 > 1.2 && l6 > 0L) ? COUNTSTORE_SALES3_L1_2_P_1.addOrDelOnZero(se37.modify(store_sales_ss_hdemo_sk),v26) : (void)0);
              n24 = n24->nxt;
            }
          }
        }COUNTSTORE_SALES3_L1_2_P_3.clear();
        {  // foreach
          const HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627* i25 = static_cast<HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627*>(DATE_DIM.index[0]);
          HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627::IdxNode* n25; 
          DATE_DIM_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long store_sales_ss_sold_date_sk = e25->DATE_DIM_D_DATE_SK;
                STRING_TYPE date_dim_d_date_id = e25->DATE_DIM_D_DATE_ID;
                date date_dim_d_date = e25->DATE_DIM_D_DATE;
                long date_dim_d_month_seq = e25->DATE_DIM_D_MONTH_SEQ;
                long date_dim_d_week_seq = e25->DATE_DIM_D_WEEK_SEQ;
                long date_dim_d_quarter_seq = e25->DATE_DIM_D_QUARTER_SEQ;
                long date_dim_d_year = e25->DATE_DIM_D_YEAR;
                long date_dim_d_dow = e25->DATE_DIM_D_DOW;
                long date_dim_d_moy = e25->DATE_DIM_D_MOY;
                long date_dim_d_dom = e25->DATE_DIM_D_DOM;
                long date_dim_d_qoy = e25->DATE_DIM_D_QOY;
                long date_dim_d_fy_year = e25->DATE_DIM_D_FY_YEAR;
                long date_dim_d_fy_quarter_seq = e25->DATE_DIM_D_FY_QUARTER_SEQ;
                long date_dim_d_fy_week_seq = e25->DATE_DIM_D_FY_WEEK_SEQ;
                STRING_TYPE date_dim_d_day_name = e25->DATE_DIM_D_DAY_NAME;
                STRING_TYPE date_dim_d_quarter_name = e25->DATE_DIM_D_QUARTER_NAME;
                STRING_TYPE date_dim_d_holiday = e25->DATE_DIM_D_HOLIDAY;
                STRING_TYPE date_dim_d_weekend = e25->DATE_DIM_D_WEEKEND;
                STRING_TYPE date_dim_d_following_holiday = e25->DATE_DIM_D_FOLLOWING_HOLIDAY;
                long date_dim_d_first_dom = e25->DATE_DIM_D_FIRST_DOM;
                long date_dim_d_last_dom = e25->DATE_DIM_D_LAST_DOM;
                long date_dim_d_same_day_ly = e25->DATE_DIM_D_SAME_DAY_LY;
                long date_dim_d_same_day_lq = e25->DATE_DIM_D_SAME_DAY_LQ;
                STRING_TYPE date_dim_d_current_day = e25->DATE_DIM_D_CURRENT_DAY;
                STRING_TYPE date_dim_d_current_week = e25->DATE_DIM_D_CURRENT_WEEK;
                STRING_TYPE date_dim_d_current_month = e25->DATE_DIM_D_CURRENT_MONTH;
                STRING_TYPE date_dim_d_current_quarter = e25->DATE_DIM_D_CURRENT_QUARTER;
                STRING_TYPE date_dim_d_current_year = e25->DATE_DIM_D_CURRENT_YEAR;
                long v27 = e25->__av;
                long l7 = ((/*if */(date_dim_d_dom >= 1L && 3L >= date_dim_d_dom) ? 1L : 0L) + (/*if */(date_dim_d_dom >= 25L && 28L >= date_dim_d_dom) ? 1L : 0L));
                (/*if */(((date_dim_d_year == 1999L) || (date_dim_d_year == 2000L) || (date_dim_d_year == 2001L)) && l7 > 0L) ? COUNTSTORE_SALES3_L1_2_P_3.addOrDelOnZero(se38.modify(store_sales_ss_sold_date_sk),v27) : (void)0);
              n25 = n25->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTSTORE_SALES3_L1_2_DELTA_entry se1;
    COUNTSTORE_SALES1_DOMAIN1_entry se2;
    COUNT_entry se3;
    COUNTCUSTOMER1_E1_1_entry se4;
    tuple6_LSSSS_L st1;
    COUNTSTORE_SALES1_entry se5;
    COUNTCUSTOMER1_E1_1_entry se6;
    tuple2_L_L st2;
    COUNTCUSTOMER1_E1_1_entry se7;
    COUNTSTORE_SALES3_L1_2_P_1_entry se8;
    COUNTSTORE_SALES3_L1_2_P_2_entry se9;
    COUNTSTORE_SALES3_L1_2_P_3_entry se10;
    tuple2_L_L st3;
    COUNTSTORE_SALES3_L1_2_DELTA_entry se11;
    COUNTCUSTOMER1_E1_1_entry se12;
    COUNTSTORE_SALES3_L1_2_P_1_entry se13;
    COUNTSTORE_SALES3_L1_2_P_2_entry se14;
    COUNTSTORE_SALES3_L1_2_P_3_entry se15;
    COUNTSTORE_SALES3_L1_2_DELTA_entry se16;
    tuple6_LSSSS_L st4;
    COUNTSTORE_SALES1_entry se17;
    COUNTCUSTOMER1_E1_1_entry se18;
    COUNTSTORE_SALES3_L1_2_P_1_entry se19;
    COUNTSTORE_SALES3_L1_2_P_2_entry se20;
    COUNTSTORE_SALES3_L1_2_P_3_entry se21;
    COUNTCUSTOMER1_E1_1STORE1_entry se22;
    COUNTSTORE_SALES3_L1_2_P_1_entry se23;
    COUNTSTORE_SALES3_L1_2_P_3_entry se24;
    COUNTCUSTOMER1_DELTA_entry se25;
    COUNT_entry se26;
    COUNTCUSTOMER1_E1_1_entry se27;
    COUNTCUSTOMER1_E1_1_entry se28;
    COUNTSTORE_SALES1_entry se29;
    COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_entry se30;
    COUNTSTORE_SALES3_L1_2_P_2_entry se31;
    COUNTCUSTOMER1_E1_1_entry se32;
    COUNTCUSTOMER1_E1_1STORE1_entry se33;
    COUNT_entry se34;
    COUNTCUSTOMER1_E1_1_entry se35;
    COUNTCUSTOMER1_E1_1_entry se36;
    COUNTSTORE_SALES3_L1_2_P_1_entry se37;
    COUNTSTORE_SALES3_L1_2_P_3_entry se38;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    HOUSEHOLD_DEMOGRAPHICS_map HOUSEHOLD_DEMOGRAPHICS;
    COUNTSTORE_SALES1_DOMAIN1_map COUNTSTORE_SALES1_DOMAIN1;
    COUNTSTORE_SALES1_map COUNTSTORE_SALES1;
    COUNTSTORE_SALES3_L1_2_DELTA_map COUNTSTORE_SALES3_L1_2_DELTA;
    COUNTSTORE_SALES3_L1_2_P_1_map COUNTSTORE_SALES3_L1_2_P_1;
    COUNTSTORE_SALES3_L1_2_P_2_map COUNTSTORE_SALES3_L1_2_P_2;
    COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA_map COUNTSTORE_SALES3_L1_2_P_2STORE1_DELTA;
    COUNTSTORE_SALES3_L1_2_P_3_map COUNTSTORE_SALES3_L1_2_P_3;
    COUNTCUSTOMER1_DELTA_map COUNTCUSTOMER1_DELTA;
    COUNTCUSTOMER1_E1_1_map COUNTCUSTOMER1_E1_1;
    COUNTCUSTOMER1_E1_1STORE1_map COUNTCUSTOMER1_E1_1STORE1;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_STORE_map DELTA_STORE;
    MultiHashMap<tuple6_LSSSS_L,long,HashIndex<tuple6_LSSSS_L,long> > _c1;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > _c2;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c8;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c9;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c10;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
  
  };

}
