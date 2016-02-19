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
  
  struct DELTA_CUSTOMER_ADDRESS_entry {
    long customer_address_ca_address_sk; STRING_TYPE customer_address_ca_address_id; STRING_TYPE customer_address_ca_street_number; STRING_TYPE customer_address_ca_street_name; STRING_TYPE customer_address_ca_street_type; STRING_TYPE customer_address_ca_suite_number; STRING_TYPE customer_address_ca_city; STRING_TYPE customer_address_ca_county; STRING_TYPE customer_address_ca_state; STRING_TYPE customer_address_ca_zip; STRING_TYPE customer_address_ca_country; DOUBLE_TYPE customer_address_ca_gmt_offset; STRING_TYPE customer_address_ca_location_type; long __av; 
    explicit DELTA_CUSTOMER_ADDRESS_entry() { /*customer_address_ca_address_sk = 0L; customer_address_ca_address_id = ""; customer_address_ca_street_number = ""; customer_address_ca_street_name = ""; customer_address_ca_street_type = ""; customer_address_ca_suite_number = ""; customer_address_ca_city = ""; customer_address_ca_county = ""; customer_address_ca_state = ""; customer_address_ca_zip = ""; customer_address_ca_country = ""; customer_address_ca_gmt_offset = 0.0; customer_address_ca_location_type = ""; __av = 0L; */ }
    explicit DELTA_CUSTOMER_ADDRESS_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const STRING_TYPE& c10, const DOUBLE_TYPE c11, const STRING_TYPE& c12, const long c13) { customer_address_ca_address_sk = c0; customer_address_ca_address_id = c1; customer_address_ca_street_number = c2; customer_address_ca_street_name = c3; customer_address_ca_street_type = c4; customer_address_ca_suite_number = c5; customer_address_ca_city = c6; customer_address_ca_county = c7; customer_address_ca_state = c8; customer_address_ca_zip = c9; customer_address_ca_country = c10; customer_address_ca_gmt_offset = c11; customer_address_ca_location_type = c12; __av = c13; }
    DELTA_CUSTOMER_ADDRESS_entry(const DELTA_CUSTOMER_ADDRESS_entry& other) : customer_address_ca_address_sk( other.customer_address_ca_address_sk ), customer_address_ca_address_id( other.customer_address_ca_address_id ), customer_address_ca_street_number( other.customer_address_ca_street_number ), customer_address_ca_street_name( other.customer_address_ca_street_name ), customer_address_ca_street_type( other.customer_address_ca_street_type ), customer_address_ca_suite_number( other.customer_address_ca_suite_number ), customer_address_ca_city( other.customer_address_ca_city ), customer_address_ca_county( other.customer_address_ca_county ), customer_address_ca_state( other.customer_address_ca_state ), customer_address_ca_zip( other.customer_address_ca_zip ), customer_address_ca_country( other.customer_address_ca_country ), customer_address_ca_gmt_offset( other.customer_address_ca_gmt_offset ), customer_address_ca_location_type( other.customer_address_ca_location_type ), __av( other.__av ) {}
    FORCE_INLINE DELTA_CUSTOMER_ADDRESS_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const STRING_TYPE& c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const STRING_TYPE& c10, const DOUBLE_TYPE c11, const STRING_TYPE& c12) { customer_address_ca_address_sk = c0; customer_address_ca_address_id = c1; customer_address_ca_street_number = c2; customer_address_ca_street_name = c3; customer_address_ca_street_type = c4; customer_address_ca_suite_number = c5; customer_address_ca_city = c6; customer_address_ca_county = c7; customer_address_ca_state = c8; customer_address_ca_zip = c9; customer_address_ca_country = c10; customer_address_ca_gmt_offset = c11; customer_address_ca_location_type = c12;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_address_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_address_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_street_number);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_street_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_street_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_suite_number);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_city);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_county);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_state);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_country);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_gmt_offset);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, customer_address_ca_location_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_CUSTOMER_ADDRESS_mapkey0123456789101112_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_CUSTOMER_ADDRESS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.customer_address_ca_address_sk);
      hash_combine(h, e.customer_address_ca_address_id);
      hash_combine(h, e.customer_address_ca_street_number);
      hash_combine(h, e.customer_address_ca_street_name);
      hash_combine(h, e.customer_address_ca_street_type);
      hash_combine(h, e.customer_address_ca_suite_number);
      hash_combine(h, e.customer_address_ca_city);
      hash_combine(h, e.customer_address_ca_county);
      hash_combine(h, e.customer_address_ca_state);
      hash_combine(h, e.customer_address_ca_zip);
      hash_combine(h, e.customer_address_ca_country);
      hash_combine(h, e.customer_address_ca_gmt_offset);
      hash_combine(h, e.customer_address_ca_location_type);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_CUSTOMER_ADDRESS_entry& x, const DELTA_CUSTOMER_ADDRESS_entry& y) {
      return x.customer_address_ca_address_sk == y.customer_address_ca_address_sk && x.customer_address_ca_address_id == y.customer_address_ca_address_id && x.customer_address_ca_street_number == y.customer_address_ca_street_number && x.customer_address_ca_street_name == y.customer_address_ca_street_name && x.customer_address_ca_street_type == y.customer_address_ca_street_type && x.customer_address_ca_suite_number == y.customer_address_ca_suite_number && x.customer_address_ca_city == y.customer_address_ca_city && x.customer_address_ca_county == y.customer_address_ca_county && x.customer_address_ca_state == y.customer_address_ca_state && x.customer_address_ca_zip == y.customer_address_ca_zip && x.customer_address_ca_country == y.customer_address_ca_country && x.customer_address_ca_gmt_offset == y.customer_address_ca_gmt_offset && x.customer_address_ca_location_type == y.customer_address_ca_location_type;
    }
  };
  
  typedef MultiHashMap<DELTA_CUSTOMER_ADDRESS_entry,long,
    HashIndex<DELTA_CUSTOMER_ADDRESS_entry,long,DELTA_CUSTOMER_ADDRESS_mapkey0123456789101112_idxfn,true>
  > DELTA_CUSTOMER_ADDRESS_map;
  typedef HashIndex<DELTA_CUSTOMER_ADDRESS_entry,long,DELTA_CUSTOMER_ADDRESS_mapkey0123456789101112_idxfn,true> HashIndex_DELTA_CUSTOMER_ADDRESS_map_0123456789101112;
  
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
    STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CURRENT_ADDR_CA_CITY; STRING_TYPE DN_BOUGHT_CITY; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE DN_AMT; DOUBLE_TYPE DN_PROFIT; long __av; 
    explicit COUNT_entry() { /*CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_FIRST_NAME = ""; CURRENT_ADDR_CA_CITY = ""; DN_BOUGHT_CITY = ""; DN_SS_TICKET_NUMBER = 0L; DN_AMT = 0.0; DN_PROFIT = 0.0; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const long c7) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CURRENT_ADDR_CA_CITY = c2; DN_BOUGHT_CITY = c3; DN_SS_TICKET_NUMBER = c4; DN_AMT = c5; DN_PROFIT = c6; __av = c7; }
    COUNT_entry(const COUNT_entry& other) : CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CURRENT_ADDR_CA_CITY( other.CURRENT_ADDR_CA_CITY ), DN_BOUGHT_CITY( other.DN_BOUGHT_CITY ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), DN_AMT( other.DN_AMT ), DN_PROFIT( other.DN_PROFIT ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CURRENT_ADDR_CA_CITY = c2; DN_BOUGHT_CITY = c3; DN_SS_TICKET_NUMBER = c4; DN_AMT = c5; DN_PROFIT = c6;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CURRENT_ADDR_CA_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_BOUGHT_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_AMT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_PROFIT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey0123456_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CURRENT_ADDR_CA_CITY);
      hash_combine(h, e.DN_BOUGHT_CITY);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      hash_combine(h, e.DN_AMT);
      hash_combine(h, e.DN_PROFIT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CURRENT_ADDR_CA_CITY == y.CURRENT_ADDR_CA_CITY && x.DN_BOUGHT_CITY == y.DN_BOUGHT_CITY && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER && x.DN_AMT == y.DN_AMT && x.DN_PROFIT == y.DN_PROFIT;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey0123456_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey0123456_idxfn,true> HashIndex_COUNT_map_0123456;
  
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
  
  struct COUNTSTORE_SALES1_E1_2_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const long c6) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5; __av = c6; }
    COUNTSTORE_SALES1_E1_2_DELTA_entry(const COUNTSTORE_SALES1_E1_2_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_DELTA_entry& modify5(const long c5) { DN_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_DELTA_entry& modify135(const long c1, const long c3, const long c5) { CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c3; DN_SS_TICKET_NUMBER = c5;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
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
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_DELTA_entry& x, const COUNTSTORE_SALES1_E1_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_DELTA_entry& x, const COUNTSTORE_SALES1_E1_2_DELTA_entry& y) {
      return x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_DELTA_entry& x, const COUNTSTORE_SALES1_E1_2_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
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
    long STORE_SALES_SS_HDEMO_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_P_1_entry() { /*STORE_SALES_SS_HDEMO_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_P_1_entry(const long c0, const long c1) { STORE_SALES_SS_HDEMO_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_2_P_1_entry(const COUNTSTORE_SALES1_E1_2_P_1_entry& other) : STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_1_entry& modify(const long c0) { STORE_SALES_SS_HDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_1_entry& x, const COUNTSTORE_SALES1_E1_2_P_1_entry& y) {
      return x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_P_1_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_1_entry,long,COUNTSTORE_SALES1_E1_2_P_1_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_2_P_1_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_1_entry,long,COUNTSTORE_SALES1_E1_2_P_1_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_P_1_map_0;
  
  struct COUNTSTORE_SALES1_E1_2_P_2_entry {
    long STORE_SALES_SS_STORE_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_P_2_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_P_2_entry(const long c0, const long c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_2_P_2_entry(const COUNTSTORE_SALES1_E1_2_P_2_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_2_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_2_entry& x, const COUNTSTORE_SALES1_E1_2_P_2_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_P_2_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_2_entry,long,COUNTSTORE_SALES1_E1_2_P_2_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_2_P_2_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_2_entry,long,COUNTSTORE_SALES1_E1_2_P_2_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_P_2_map_0;
  
  struct COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry {
    long STORE_SALES_SS_STORE_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry(const long c0, const long c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry(const COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry& x, const COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry,long,COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0;
  
  struct COUNTSTORE_SALES1_E1_2_P_3_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_P_3_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_P_3_entry(const long c0, const long c1) { STORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_2_P_3_entry(const COUNTSTORE_SALES1_E1_2_P_3_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_P_3_entry& modify(const long c0) { STORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_P_3_entry& x, const COUNTSTORE_SALES1_E1_2_P_3_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_P_3_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_P_3_entry,long,COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_2_P_3_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_P_3_entry,long,COUNTSTORE_SALES1_E1_2_P_3_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_P_3_map_0;
  
  struct COUNTSTORE_SALES6_DOMAIN1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE_SALES6_DOMAIN1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES6_DOMAIN1_entry(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTSTORE_SALES6_DOMAIN1_entry(const COUNTSTORE_SALES6_DOMAIN1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES6_DOMAIN1_entry& modify(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES6_DOMAIN1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES6_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES6_DOMAIN1_entry& x, const COUNTSTORE_SALES6_DOMAIN1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES6_DOMAIN1_entry,long,
    HashIndex<COUNTSTORE_SALES6_DOMAIN1_entry,long,COUNTSTORE_SALES6_DOMAIN1_mapkey012_idxfn,true>
  > COUNTSTORE_SALES6_DOMAIN1_map;
  typedef HashIndex<COUNTSTORE_SALES6_DOMAIN1_entry,long,COUNTSTORE_SALES6_DOMAIN1_mapkey012_idxfn,true> HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012;
  
  struct COUNTSTORE_SALES9_L2_3_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE_SALES9_L2_3_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE_SALES9_L2_3_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5; __av = c6; }
    COUNTSTORE_SALES9_L2_3_DELTA_entry(const COUNTSTORE_SALES9_L2_3_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES9_L2_3_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES9_L2_3_DELTA_entry& modify135(const long c1, const long c3, const long c5) { CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c3; DN_SS_TICKET_NUMBER = c5;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES9_L2_3_DELTA_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L2_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L2_3_DELTA_entry& x, const COUNTSTORE_SALES9_L2_3_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L2_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L2_3_DELTA_entry& x, const COUNTSTORE_SALES9_L2_3_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES9_L2_3_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE_SALES9_L2_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_3_DELTA_mapkey012345_idxfn,true>,
    HashIndex<COUNTSTORE_SALES9_L2_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn,false>
  > COUNTSTORE_SALES9_L2_3_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES9_L2_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_3_DELTA_mapkey012345_idxfn,true> HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345;
  typedef HashIndex<COUNTSTORE_SALES9_L2_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn,false> HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135;
  
  struct COUNTSTORE_SALES9_L3_3_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE_SALES9_L3_3_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE_SALES9_L3_3_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5; __av = c6; }
    COUNTSTORE_SALES9_L3_3_DELTA_entry(const COUNTSTORE_SALES9_L3_3_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES9_L3_3_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES9_L3_3_DELTA_entry& modify135(const long c1, const long c3, const long c5) { CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c3; DN_SS_TICKET_NUMBER = c5;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES9_L3_3_DELTA_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L3_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L3_3_DELTA_entry& x, const COUNTSTORE_SALES9_L3_3_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L3_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L3_3_DELTA_entry& x, const COUNTSTORE_SALES9_L3_3_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES9_L3_3_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE_SALES9_L3_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_3_DELTA_mapkey012345_idxfn,true>,
    HashIndex<COUNTSTORE_SALES9_L3_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn,false>
  > COUNTSTORE_SALES9_L3_3_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES9_L3_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_3_DELTA_mapkey012345_idxfn,true> HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345;
  typedef HashIndex<COUNTSTORE_SALES9_L3_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn,false> HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135;
  
  struct COUNTCUSTOMER_ADDRESS1_DELTA_entry {
    long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE CURRENT_ADDR_CA_CITY; long __av; 
    explicit COUNTCUSTOMER_ADDRESS1_DELTA_entry() { /*CUSTOMER_C_CURRENT_ADDR_SK = 0L; CURRENT_ADDR_CA_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER_ADDRESS1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CURRENT_ADDR_CA_CITY = c1; __av = c2; }
    COUNTCUSTOMER_ADDRESS1_DELTA_entry(const COUNTCUSTOMER_ADDRESS1_DELTA_entry& other) : CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), CURRENT_ADDR_CA_CITY( other.CURRENT_ADDR_CA_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER_ADDRESS1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CURRENT_ADDR_CA_CITY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CURRENT_ADDR_CA_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER_ADDRESS1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.CURRENT_ADDR_CA_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS1_DELTA_entry& x, const COUNTCUSTOMER_ADDRESS1_DELTA_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.CURRENT_ADDR_CA_CITY == y.CURRENT_ADDR_CA_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER_ADDRESS1_DELTA_entry,long,
    HashIndex<COUNTCUSTOMER_ADDRESS1_DELTA_entry,long,COUNTCUSTOMER_ADDRESS1_DELTA_mapkey01_idxfn,true>
  > COUNTCUSTOMER_ADDRESS1_DELTA_map;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS1_DELTA_entry,long,COUNTCUSTOMER_ADDRESS1_DELTA_mapkey01_idxfn,true> HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01;
  
  struct COUNTCUSTOMER_ADDRESS1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; long __av; 
    explicit COUNTCUSTOMER_ADDRESS1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER_ADDRESS1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; __av = c4; }
    COUNTCUSTOMER_ADDRESS1_entry(const COUNTCUSTOMER_ADDRESS1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER_ADDRESS1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER_ADDRESS1_entry& modify1(const long c1) { CUSTOMER_C_CURRENT_ADDR_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER_ADDRESS1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS1_entry& x, const COUNTCUSTOMER_ADDRESS1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME;
    }
  };
  
  struct COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS1_entry& x, const COUNTCUSTOMER_ADDRESS1_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER_ADDRESS1_entry,long,
    HashIndex<COUNTCUSTOMER_ADDRESS1_entry,long,COUNTCUSTOMER_ADDRESS1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER_ADDRESS1_entry,long,COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn,false>
  > COUNTCUSTOMER_ADDRESS1_map;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS1_entry,long,COUNTCUSTOMER_ADDRESS1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER_ADDRESS1_map_0123;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS1_entry,long,COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn,false> HashIndex_COUNTCUSTOMER_ADDRESS1_map_1;
  
  struct COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry {
    long STORE_SALES_SS_ADDR_SK; STRING_TYPE DN_BOUGHT_CITY; long __av; 
    explicit COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry() { /*STORE_SALES_SS_ADDR_SK = 0L; DN_BOUGHT_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ADDR_SK = c0; DN_BOUGHT_CITY = c1; __av = c2; }
    COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry(const COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry& other) : STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_BOUGHT_CITY( other.DN_BOUGHT_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ADDR_SK = c0; DN_BOUGHT_CITY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_BOUGHT_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER_ADDRESS2_DOMAIN1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_BOUGHT_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry& x, const COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry& y) {
      return x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_BOUGHT_CITY == y.DN_BOUGHT_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry,long,
    HashIndex<COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry,long,COUNTCUSTOMER_ADDRESS2_DOMAIN1_mapkey01_idxfn,true>
  > COUNTCUSTOMER_ADDRESS2_DOMAIN1_map;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry,long,COUNTCUSTOMER_ADDRESS2_DOMAIN1_mapkey01_idxfn,true> HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01;
  
  struct COUNTCUSTOMER_ADDRESS2_entry {
    long CUSTOMER_C_CUSTOMER_SK; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CURRENT_ADDR_CA_CITY; long __av; 
    explicit COUNTCUSTOMER_ADDRESS2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; CURRENT_ADDR_CA_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER_ADDRESS2_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2; CURRENT_ADDR_CA_CITY = c3; __av = c4; }
    COUNTCUSTOMER_ADDRESS2_entry(const COUNTCUSTOMER_ADDRESS2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CURRENT_ADDR_CA_CITY( other.CURRENT_ADDR_CA_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2; CURRENT_ADDR_CA_CITY = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, CURRENT_ADDR_CA_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER_ADDRESS2_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CURRENT_ADDR_CA_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_entry& x, const COUNTCUSTOMER_ADDRESS2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CURRENT_ADDR_CA_CITY == y.CURRENT_ADDR_CA_CITY;
    }
  };
  
  struct COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_entry& x, const COUNTCUSTOMER_ADDRESS2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER_ADDRESS2_entry,long,
    HashIndex<COUNTCUSTOMER_ADDRESS2_entry,long,COUNTCUSTOMER_ADDRESS2_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER_ADDRESS2_entry,long,COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn,false>
  > COUNTCUSTOMER_ADDRESS2_map;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_entry,long,COUNTCUSTOMER_ADDRESS2_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_entry,long,COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER_ADDRESS2_map_0;
  
  struct COUNTCUSTOMER_ADDRESS2_E1_2_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTCUSTOMER_ADDRESS2_E1_2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTCUSTOMER_ADDRESS2_E1_2_entry(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTCUSTOMER_ADDRESS2_E1_2_entry(const COUNTCUSTOMER_ADDRESS2_E1_2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_E1_2_entry& modify(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_E1_2_entry& modify01(const long c0, const long c1) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_E1_2_entry& modify1(const long c1) { STORE_SALES_SS_ADDR_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER_ADDRESS2_E1_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_E1_2_entry& x, const COUNTCUSTOMER_ADDRESS2_E1_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_E1_2_entry& x, const COUNTCUSTOMER_ADDRESS2_E1_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK;
    }
  };
  
  struct COUNTCUSTOMER_ADDRESS2_E1_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_E1_2_entry& x, const COUNTCUSTOMER_ADDRESS2_E1_2_entry& y) {
      return x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER_ADDRESS2_E1_2_entry,long,
    HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2_mapkey012_idxfn,true>,
    HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn,false>,
    HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2_mapkey1_idxfn,false>
  > COUNTCUSTOMER_ADDRESS2_E1_2_map;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2_mapkey012_idxfn,true> HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_012;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn,false> HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2_mapkey1_idxfn,false> HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1;
  
  struct COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry(const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& modify1(const long c1) { STORE_SALES_SS_ADDR_SK = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& x, const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& x, const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& y) {
      return x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK;
    }
  };
  
  struct COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& x, const COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry,long,
    HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey1_idxfn,false>,
    HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey2_idxfn,false>
  > COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_0123;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey1_idxfn,false> HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry,long,COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2;
  
  struct COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry {
    long STORE_SALES_SS_ADDR_SK; STRING_TYPE DN_BOUGHT_CITY; long __av; 
    explicit COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry() { /*STORE_SALES_SS_ADDR_SK = 0L; DN_BOUGHT_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ADDR_SK = c0; DN_BOUGHT_CITY = c1; __av = c2; }
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry(const COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry& other) : STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_BOUGHT_CITY( other.DN_BOUGHT_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ADDR_SK = c0; DN_BOUGHT_CITY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_BOUGHT_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_BOUGHT_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry& x, const COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry& y) {
      return x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_BOUGHT_CITY == y.DN_BOUGHT_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry,long,
    HashIndex<COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry,long,COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_mapkey01_idxfn,true>
  > COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map;
  typedef HashIndex<COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry,long,COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_mapkey01_idxfn,true> HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01;
  
  struct COUNTCUSTOMER1_DELTA_entry {
    long CUSTOMER_C_CUSTOMER_SK; long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; long __av; 
    explicit COUNTCUSTOMER1_DELTA_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_DELTA_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; __av = c4; }
    COUNTCUSTOMER1_DELTA_entry(const COUNTCUSTOMER1_DELTA_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_DELTA_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_DELTA_entry& x, const COUNTCUSTOMER1_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_DELTA_entry,long,
    HashIndex<COUNTCUSTOMER1_DELTA_entry,long,COUNTCUSTOMER1_DELTA_mapkey0123_idxfn,true>
  > COUNTCUSTOMER1_DELTA_map;
  typedef HashIndex<COUNTCUSTOMER1_DELTA_entry,long,COUNTCUSTOMER1_DELTA_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_DELTA_map_0123;
  
  struct COUNTCUSTOMER1_entry {
    long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE CURRENT_ADDR_CA_CITY; long __av; 
    explicit COUNTCUSTOMER1_entry() { /*CUSTOMER_C_CURRENT_ADDR_SK = 0L; CURRENT_ADDR_CA_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_entry(const long c0, const STRING_TYPE& c1, const long c2) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CURRENT_ADDR_CA_CITY = c1; __av = c2; }
    COUNTCUSTOMER1_entry(const COUNTCUSTOMER1_entry& other) : CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), CURRENT_ADDR_CA_CITY( other.CURRENT_ADDR_CA_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_entry& modify(const long c0, const STRING_TYPE& c1) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CURRENT_ADDR_CA_CITY = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_entry& modify0(const long c0) { CUSTOMER_C_CURRENT_ADDR_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CURRENT_ADDR_CA_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.CURRENT_ADDR_CA_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_entry& x, const COUNTCUSTOMER1_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.CURRENT_ADDR_CA_CITY == y.CURRENT_ADDR_CA_CITY;
    }
  };
  
  struct COUNTCUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_entry& x, const COUNTCUSTOMER1_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_entry,long,
    HashIndex<COUNTCUSTOMER1_entry,long,COUNTCUSTOMER1_mapkey01_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_entry,long,COUNTCUSTOMER1_mapkey0_idxfn,false>
  > COUNTCUSTOMER1_map;
  typedef HashIndex<COUNTCUSTOMER1_entry,long,COUNTCUSTOMER1_mapkey01_idxfn,true> HashIndex_COUNTCUSTOMER1_map_01;
  typedef HashIndex<COUNTCUSTOMER1_entry,long,COUNTCUSTOMER1_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER1_map_0;
  
  struct COUNTCUSTOMER1_E1_1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long DN_SS_TICKET_NUMBER; STRING_TYPE DN_BOUGHT_CITY; long __av; 
    explicit COUNTCUSTOMER1_E1_1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; DN_SS_TICKET_NUMBER = 0L; DN_BOUGHT_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2; DN_BOUGHT_CITY = c3; __av = c4; }
    COUNTCUSTOMER1_E1_1_entry(const COUNTCUSTOMER1_E1_1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), DN_BOUGHT_CITY( other.DN_BOUGHT_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2; DN_BOUGHT_CITY = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify2(const long c2) { DN_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_BOUGHT_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      hash_combine(h, e.DN_BOUGHT_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER && x.DN_BOUGHT_CITY == y.DN_BOUGHT_CITY;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey2_idxfn {
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
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey2_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false>
  > COUNTCUSTOMER1_E1_1_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1_map_0123;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_2;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_0;
  
  struct COUNTCUSTOMER1_E1_1STORE1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; STRING_TYPE DN_BOUGHT_CITY; long __av; 
    explicit COUNTCUSTOMER1_E1_1STORE1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; DN_BOUGHT_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1STORE1_entry(const long c0, const long c1, const long c2, const long c3, const STRING_TYPE& c4, const long c5) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3; DN_BOUGHT_CITY = c4; __av = c5; }
    COUNTCUSTOMER1_E1_1STORE1_entry(const COUNTCUSTOMER1_E1_1STORE1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), DN_BOUGHT_CITY( other.DN_BOUGHT_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1STORE1_entry& modify(const long c0, const long c1, const long c2, const long c3, const STRING_TYPE& c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3; DN_BOUGHT_CITY = c4;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1STORE1_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_BOUGHT_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1STORE1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      hash_combine(h, e.DN_BOUGHT_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1STORE1_entry& x, const COUNTCUSTOMER1_E1_1STORE1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER && x.DN_BOUGHT_CITY == y.DN_BOUGHT_CITY;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1STORE1_mapkey2_idxfn {
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
    HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey01234_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey2_idxfn,false>
  > COUNTCUSTOMER1_E1_1STORE1_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey01234_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_01234;
  typedef HashIndex<COUNTCUSTOMER1_E1_1STORE1_entry,long,COUNTCUSTOMER1_E1_1STORE1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2;
  
  struct COUNTCUSTOMER1_L2_1_entry {
    long STORE_SALES_SS_ADDR_SK; STRING_TYPE DN_BOUGHT_CITY; long __av; 
    explicit COUNTCUSTOMER1_L2_1_entry() { /*STORE_SALES_SS_ADDR_SK = 0L; DN_BOUGHT_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_L2_1_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ADDR_SK = c0; DN_BOUGHT_CITY = c1; __av = c2; }
    COUNTCUSTOMER1_L2_1_entry(const COUNTCUSTOMER1_L2_1_entry& other) : STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_BOUGHT_CITY( other.DN_BOUGHT_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L2_1_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ADDR_SK = c0; DN_BOUGHT_CITY = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_L2_1_entry& modify0(const long c0) { STORE_SALES_SS_ADDR_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_BOUGHT_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L2_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_BOUGHT_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L2_1_entry& x, const COUNTCUSTOMER1_L2_1_entry& y) {
      return x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_BOUGHT_CITY == y.DN_BOUGHT_CITY;
    }
  };
  
  struct COUNTCUSTOMER1_L2_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L2_1_entry& x, const COUNTCUSTOMER1_L2_1_entry& y) {
      return x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L2_1_entry,long,
    HashIndex<COUNTCUSTOMER1_L2_1_entry,long,COUNTCUSTOMER1_L2_1_mapkey01_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_L2_1_entry,long,COUNTCUSTOMER1_L2_1_mapkey0_idxfn,false>
  > COUNTCUSTOMER1_L2_1_map;
  typedef HashIndex<COUNTCUSTOMER1_L2_1_entry,long,COUNTCUSTOMER1_L2_1_mapkey01_idxfn,true> HashIndex_COUNTCUSTOMER1_L2_1_map_01;
  typedef HashIndex<COUNTCUSTOMER1_L2_1_entry,long,COUNTCUSTOMER1_L2_1_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER1_L2_1_map_0;
  
  struct COUNTCUSTOMER1_L2_2_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L2_2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L2_2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTCUSTOMER1_L2_2_entry(const COUNTCUSTOMER1_L2_2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L2_2_entry& modify(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L2_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L2_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L2_2_entry& x, const COUNTCUSTOMER1_L2_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L2_2_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L2_2_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L2_2_mapkey012_idxfn,true>
  > COUNTCUSTOMER1_L2_2_map;
  typedef HashIndex<COUNTCUSTOMER1_L2_2_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L2_2_mapkey012_idxfn,true> HashIndex_COUNTCUSTOMER1_L2_2_map_012;
  
  struct COUNTCUSTOMER1_L2_2STORE1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L2_2STORE1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L2_2STORE1_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTCUSTOMER1_L2_2STORE1_entry(const COUNTCUSTOMER1_L2_2STORE1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L2_2STORE1_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_L2_2STORE1_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L2_2STORE1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L2_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L2_2STORE1_entry& x, const COUNTCUSTOMER1_L2_2STORE1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_L2_2STORE1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L2_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L2_2STORE1_entry& x, const COUNTCUSTOMER1_L2_2STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L2_2STORE1_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L2_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L2_2STORE1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_L2_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L2_2STORE1_mapkey2_idxfn,false>
  > COUNTCUSTOMER1_L2_2STORE1_map;
  typedef HashIndex<COUNTCUSTOMER1_L2_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L2_2STORE1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_0123;
  typedef HashIndex<COUNTCUSTOMER1_L2_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L2_2STORE1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2;
  
  struct COUNTCUSTOMER1_L3_2_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L3_2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L3_2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTCUSTOMER1_L3_2_entry(const COUNTCUSTOMER1_L3_2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L3_2_entry& modify(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L3_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L3_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L3_2_entry& x, const COUNTCUSTOMER1_L3_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L3_2_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L3_2_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_2_mapkey012_idxfn,true>
  > COUNTCUSTOMER1_L3_2_map;
  typedef HashIndex<COUNTCUSTOMER1_L3_2_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_2_mapkey012_idxfn,true> HashIndex_COUNTCUSTOMER1_L3_2_map_012;
  
  struct COUNTCUSTOMER1_L3_2STORE1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L3_2STORE1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L3_2STORE1_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTCUSTOMER1_L3_2STORE1_entry(const COUNTCUSTOMER1_L3_2STORE1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L3_2STORE1_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_L3_2STORE1_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L3_2STORE1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L3_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L3_2STORE1_entry& x, const COUNTCUSTOMER1_L3_2STORE1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_L3_2STORE1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L3_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L3_2STORE1_entry& x, const COUNTCUSTOMER1_L3_2STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L3_2STORE1_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L3_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_2STORE1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_L3_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_2STORE1_mapkey2_idxfn,false>
  > COUNTCUSTOMER1_L3_2STORE1_map;
  typedef HashIndex<COUNTCUSTOMER1_L3_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_2STORE1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_0123;
  typedef HashIndex<COUNTCUSTOMER1_L3_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_2STORE1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2;
  
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
  struct tuple7_SDDSSS_L {
    STRING_TYPE _1; DOUBLE_TYPE _2; DOUBLE_TYPE _3; STRING_TYPE _4; STRING_TYPE _5; STRING_TYPE _6; long __av;
    explicit tuple7_SDDSSS_L() { }
    explicit tuple7_SDDSSS_L(const STRING_TYPE& c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; _6 = c6; __av = c__av;}
    int operator==(const tuple7_SDDSSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5) && (this->_6==rhs._6)); }
    FORCE_INLINE tuple7_SDDSSS_L& modify(const STRING_TYPE& c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; _6 = c5; __av = c__av; return *this; }
    static bool equals(const tuple7_SDDSSS_L &x, const tuple7_SDDSSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5) && (x._6==y._6)); }
    static long hash(const tuple7_SDDSSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      hash_combine(h, e._6);
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
    data_t(): tlq_t(), _c1(16U), _c4(16U), _c6(16U), _c3(16U), _c2(16U), _c5(16U) {
      c1 = STRING_TYPE("Oakland");
      c4 = STRING_TYPE("Salem");
      c2 = STRING_TYPE("Riverside");
      c3 = STRING_TYPE("Union");
      c5 = STRING_TYPE("Greenwood");
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

        COUNTSTORE_SALES9_L3_3_DELTA.clear();
        COUNTSTORE_SALES9_L2_3_DELTA.clear();
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
                COUNTSTORE_SALES9_L3_3_DELTA.addOrDelOnZero(se1.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(v1 * store_sales_ss_coupon_amt));
                long v2 = 1L;
                COUNTSTORE_SALES9_L2_3_DELTA.addOrDelOnZero(se2.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(v2 * store_sales_ss_net_profit));
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
                long dn_ss_ticket_number = e6->DN_SS_TICKET_NUMBER;
                long v6 = e6->__av;
                _c1.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i7 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h2 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se12.modify2(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n7 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i7->slice(se12, h2));
                  COUNTCUSTOMER1_E1_1_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      long customer_c_customer_sk = e7->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e7->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE dn_bought_city = e7->DN_BOUGHT_CITY;
                      long v8 = e7->__av;
                      DOUBLE_TYPE l1 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se7.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se8.modify(store_sales_ss_addr_sk,dn_bought_city)));
                      DOUBLE_TYPE l2 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se9.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se10.modify(store_sales_ss_addr_sk,dn_bought_city)));
                      { //slice 
                        const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i8 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                        const HASH_RES_t h1 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se11.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n8 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i8->slice(se11, h1));
                        COUNTCUSTOMER_ADDRESS2_entry* e8;
                       
                        if (n8 && (e8 = n8->obj)) {
                          do {                
                            STRING_TYPE customer_c_first_name = e8->CUSTOMER_C_FIRST_NAME;
                            STRING_TYPE customer_c_last_name = e8->CUSTOMER_C_LAST_NAME;
                            STRING_TYPE current_addr_ca_city = e8->CURRENT_ADDR_CA_CITY;
                            long v9 = e8->__av;
                            (/*if */(current_addr_ca_city != dn_bought_city) ? _c1.addOrDelOnZero(st1.modify(dn_bought_city,l2,l1,customer_c_first_name,customer_c_last_name,current_addr_ca_city,(((v8 != 0 ? 1L : 0L) * v9) * -2L)), (((v8 != 0 ? 1L : 0L) * v9) * -2L)) : (void)0);
                            n8 = n8->nxt;
                          } while (n8 && (e8 = n8->obj) && h1 == n8->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se11, *e8)); 
                        }
                      }
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h2 == n7->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se12, *e7)); 
                  }
                }_c2.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i9 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h3 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se13.modify2(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n9 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i9->slice(se13, h3));
                  COUNTCUSTOMER1_E1_1_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      long customer_c_customer_sk = e9->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e9->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE dn_bought_city = e9->DN_BOUGHT_CITY;
                      long v11 = e9->__av;
                      _c2.addOrDelOnZero(st2.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_bought_city,v11), v11);
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h3 == n9->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se13, *e9)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5* i10 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5*>(COUNTSTORE_SALES1_E1_2_DELTA.index[1]);
                  const HASH_RES_t h5 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn::hash(se18.modify5(dn_ss_ticket_number));
                  HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5::IdxNode* n10 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5::IdxNode*>(i10->slice(se18, h5));
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
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i11 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h4 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se17.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n11 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i11->slice(se17, h4));
                        COUNTCUSTOMER1_L2_1_entry* e11;
                       
                        if (n11 && (e11 = n11->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e11->DN_BOUGHT_CITY;
                            long v13 = e11->__av;
                            _c2.addOrDelOnZero(st3.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_bought_city,(v12 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se14.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se15.modify(store_sales_ss_store_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se16.modify(store_sales_ss_sold_date_sk)) * v13))))), (v12 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se14.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se15.modify(store_sales_ss_store_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se16.modify(store_sales_ss_sold_date_sk)) * v13)))));
                            n11 = n11->nxt;
                          } while (n11 && (e11 = n11->obj) && h4 == n11->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se17, *e11)); 
                        }
                      }
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h5 == n10->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn::equals(se18, *e10)); 
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
                      STRING_TYPE dn_bought_city = e12->_3;  
                      long v14 = e12->__av; 
                    DOUBLE_TYPE l3 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se19.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se20.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                    DOUBLE_TYPE l4 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se21.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se22.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                    { //slice 
                      const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i13 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                      const HASH_RES_t h6 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se23.modify0(customer_c_customer_sk));
                      HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n13 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i13->slice(se23, h6));
                      COUNTCUSTOMER_ADDRESS2_entry* e13;
                     
                      if (n13 && (e13 = n13->obj)) {
                        do {                
                          STRING_TYPE customer_c_first_name = e13->CUSTOMER_C_FIRST_NAME;
                          STRING_TYPE customer_c_last_name = e13->CUSTOMER_C_LAST_NAME;
                          STRING_TYPE current_addr_ca_city = e13->CURRENT_ADDR_CA_CITY;
                          long v15 = e13->__av;
                          (/*if */(current_addr_ca_city != dn_bought_city) ? _c1.addOrDelOnZero(st4.modify(dn_bought_city,l3,l4,customer_c_first_name,customer_c_last_name,current_addr_ca_city,((v14 != 0 ? 1L : 0L) * v15)), ((v14 != 0 ? 1L : 0L) * v15)) : (void)0);
                          n13 = n13->nxt;
                        } while (n13 && (e13 = n13->obj) && h6 == n13->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se23, *e13)); 
                      }
                    }      
                      n12 = n12->nxt;
                    }
                  }
                }{ //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i14 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h10 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se39.modify2(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n14 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i14->slice(se39, h10));
                  COUNTCUSTOMER1_E1_1_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      long customer_c_customer_sk = e14->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e14->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE dn_bought_city = e14->DN_BOUGHT_CITY;
                      long v16 = e14->__av;
                      DOUBLE_TYPE agg1 = 0.0;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135* i15 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135*>(COUNTSTORE_SALES9_L2_3_DELTA.index[1]);
                        const HASH_RES_t h7 = COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::hash(se29.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode* n15 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode*>(i15->slice(se29, h7));
                        COUNTSTORE_SALES9_L2_3_DELTA_entry* e15;
                       
                        if (n15 && (e15 = n15->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e15->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e15->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e15->STORE_SALES_SS_STORE_SK;
                            DOUBLE_TYPE v17 = e15->__av;
                            agg1 += (v17 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se26.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se27.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se28.modify(store_sales_ss_sold_date_sk)))));
                            n15 = n15->nxt;
                          } while (n15 && (e15 = n15->obj) && h7 == n15->hash &&  COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::equals(se29, *e15)); 
                        }
                      }DOUBLE_TYPE l5 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se24.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se25.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg1 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se30.modify(store_sales_ss_addr_sk,dn_bought_city))));
                      DOUBLE_TYPE agg2 = 0.0;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135* i16 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135*>(COUNTSTORE_SALES9_L3_3_DELTA.index[1]);
                        const HASH_RES_t h8 = COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::hash(se36.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode* n16 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode*>(i16->slice(se36, h8));
                        COUNTSTORE_SALES9_L3_3_DELTA_entry* e16;
                       
                        if (n16 && (e16 = n16->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e16->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e16->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e16->STORE_SALES_SS_STORE_SK;
                            DOUBLE_TYPE v18 = e16->__av;
                            agg2 += (v18 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se33.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se34.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se35.modify(store_sales_ss_sold_date_sk)))));
                            n16 = n16->nxt;
                          } while (n16 && (e16 = n16->obj) && h8 == n16->hash &&  COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::equals(se36, *e16)); 
                        }
                      }DOUBLE_TYPE l6 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se31.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se32.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg2 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se37.modify(store_sales_ss_addr_sk,dn_bought_city))));
                      { //slice 
                        const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i17 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                        const HASH_RES_t h9 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se38.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n17 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i17->slice(se38, h9));
                        COUNTCUSTOMER_ADDRESS2_entry* e17;
                       
                        if (n17 && (e17 = n17->obj)) {
                          do {                
                            STRING_TYPE customer_c_first_name = e17->CUSTOMER_C_FIRST_NAME;
                            STRING_TYPE customer_c_last_name = e17->CUSTOMER_C_LAST_NAME;
                            STRING_TYPE current_addr_ca_city = e17->CURRENT_ADDR_CA_CITY;
                            long v19 = e17->__av;
                            (/*if */(current_addr_ca_city != dn_bought_city) ? _c1.addOrDelOnZero(st5.modify(dn_bought_city,l5,l6,customer_c_first_name,customer_c_last_name,current_addr_ca_city,((v16 != 0 ? 1L : 0L) * v19)), ((v16 != 0 ? 1L : 0L) * v19)) : (void)0);
                            n17 = n17->nxt;
                          } while (n17 && (e17 = n17->obj) && h9 == n17->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se38, *e17)); 
                        }
                      }
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h10 == n14->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se39, *e14)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple7_SDDSSS_L, long>* i18 = static_cast<HashIndex<tuple7_SDDSSS_L, long>*>(_c1.index[0]);
                  HashIndex<tuple7_SDDSSS_L, long>::IdxNode* n18; 
                  tuple7_SDDSSS_L* e18;
                
                  for (size_t i = 0; i < i18->size_; i++)
                  {
                    n18 = i18->buckets_ + i;
                    while (n18 && (e18 = n18->obj))
                    {
                      STRING_TYPE dn_bought_city = e18->_1;
                      DOUBLE_TYPE dn_profit = e18->_2;
                      DOUBLE_TYPE dn_amt = e18->_3;
                      STRING_TYPE customer_c_first_name = e18->_4;
                      STRING_TYPE customer_c_last_name = e18->_5;
                      STRING_TYPE current_addr_ca_city = e18->_6;  
                      long v20 = e18->__av; 
                    COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,dn_amt,dn_profit),((v6 != 0 ? 1L : 0L) * v20));      
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
                long dn_ss_ticket_number = e19->DN_SS_TICKET_NUMBER;
                long v21 = e19->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i20 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h14 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se51.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n20 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i20->slice(se51, h14));
                  COUNTCUSTOMER_ADDRESS2_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e20->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e20->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e20->CURRENT_ADDR_CA_CITY;
                      long v22 = e20->__av;
                      _c3.clear();
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i21 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h11 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se41.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n21 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i21->slice(se41, h11));
                        COUNTCUSTOMER1_L2_1_entry* e21;
                       
                        if (n21 && (e21 = n21->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e21->DN_BOUGHT_CITY;
                            long v24 = e21->__av;
                            _c3.addOrDelOnZero(st6.modify(dn_bought_city,(COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se40.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v24)), (COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se40.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v24));
                            n21 = n21->nxt;
                          } while (n21 && (e21 = n21->obj) && h11 == n21->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se41, *e21)); 
                        }
                      }long agg3 = 0L;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135* i22 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135*>(COUNTSTORE_SALES1_E1_2_DELTA.index[2]);
                        const HASH_RES_t h12 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::hash(se45.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode* n22 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode*>(i22->slice(se45, h12));
                        COUNTSTORE_SALES1_E1_2_DELTA_entry* e22;
                       
                        if (n22 && (e22 = n22->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e22->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e22->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e22->STORE_SALES_SS_STORE_SK;
                            long v25 = e22->__av;
                            agg3 += (v25 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se42.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se43.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se44.modify(store_sales_ss_sold_date_sk)))));
                            n22 = n22->nxt;
                          } while (n22 && (e22 = n22->obj) && h12 == n22->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::equals(se45, *e22)); 
                        }
                      }{ //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i23 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h13 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se46.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n23 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i23->slice(se46, h13));
                        COUNTCUSTOMER1_L2_1_entry* e23;
                       
                        if (n23 && (e23 = n23->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e23->DN_BOUGHT_CITY;
                            long v26 = e23->__av;
                            _c3.addOrDelOnZero(st7.modify(dn_bought_city,(agg3 * v26)), (agg3 * v26));
                            n23 = n23->nxt;
                          } while (n23 && (e23 = n23->obj) && h13 == n23->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se46, *e23)); 
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
                            STRING_TYPE dn_bought_city = e24->_1;  
                            long v27 = e24->__av; 
                          DOUBLE_TYPE l7 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se47.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se48.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                          DOUBLE_TYPE l8 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se49.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se50.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                          (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l8,l7),(((v21 != 0 ? 1L : 0L) * (v22 * (v27 != 0 ? 1L : 0L))) * -1L)) : (void)0);      
                            n24 = n24->nxt;
                          }
                        }
                      }
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h14 == n20->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se51, *e20)); 
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
                long dn_ss_ticket_number = e25->DN_SS_TICKET_NUMBER;
                long v28 = e25->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i26 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h16 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se58.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n26 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i26->slice(se58, h16));
                  COUNTCUSTOMER_ADDRESS2_entry* e26;
                 
                  if (n26 && (e26 = n26->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e26->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e26->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e26->CURRENT_ADDR_CA_CITY;
                      long v29 = e26->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i27 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h15 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se57.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n27 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i27->slice(se57, h15));
                        COUNTCUSTOMER1_L2_1_entry* e27;
                       
                        if (n27 && (e27 = n27->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e27->DN_BOUGHT_CITY;
                            long v30 = e27->__av;
                            DOUBLE_TYPE l9 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se53.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se54.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            DOUBLE_TYPE l10 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se55.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se56.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l10,l9),((v28 != 0 ? 1L : 0L) * (v29 * ((COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se52.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v30) != 0 ? 1L : 0L)))) : (void)0);
                            n27 = n27->nxt;
                          } while (n27 && (e27 = n27->obj) && h15 == n27->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se57, *e27)); 
                        }
                      }
                      n26 = n26->nxt;
                    } while (n26 && (e26 = n26->obj) && h16 == n26->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se58, *e26)); 
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
                long dn_ss_ticket_number = e28->DN_SS_TICKET_NUMBER;
                long v31 = e28->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i29 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h22 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se80.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n29 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i29->slice(se80, h22));
                  COUNTCUSTOMER_ADDRESS2_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e29->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e29->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e29->CURRENT_ADDR_CA_CITY;
                      long v32 = e29->__av;
                      _c4.clear();
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i30 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h17 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se60.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n30 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i30->slice(se60, h17));
                        COUNTCUSTOMER1_L2_1_entry* e30;
                       
                        if (n30 && (e30 = n30->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e30->DN_BOUGHT_CITY;
                            long v34 = e30->__av;
                            _c4.addOrDelOnZero(st8.modify(dn_bought_city,(COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se59.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v34)), (COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se59.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v34));
                            n30 = n30->nxt;
                          } while (n30 && (e30 = n30->obj) && h17 == n30->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se60, *e30)); 
                        }
                      }long agg4 = 0L;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135* i31 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135*>(COUNTSTORE_SALES1_E1_2_DELTA.index[2]);
                        const HASH_RES_t h18 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::hash(se64.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode* n31 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode*>(i31->slice(se64, h18));
                        COUNTSTORE_SALES1_E1_2_DELTA_entry* e31;
                       
                        if (n31 && (e31 = n31->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e31->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e31->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e31->STORE_SALES_SS_STORE_SK;
                            long v35 = e31->__av;
                            agg4 += (v35 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se61.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se62.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se63.modify(store_sales_ss_sold_date_sk)))));
                            n31 = n31->nxt;
                          } while (n31 && (e31 = n31->obj) && h18 == n31->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::equals(se64, *e31)); 
                        }
                      }{ //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i32 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h19 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se65.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n32 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i32->slice(se65, h19));
                        COUNTCUSTOMER1_L2_1_entry* e32;
                       
                        if (n32 && (e32 = n32->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e32->DN_BOUGHT_CITY;
                            long v36 = e32->__av;
                            _c4.addOrDelOnZero(st9.modify(dn_bought_city,(agg4 * v36)), (agg4 * v36));
                            n32 = n32->nxt;
                          } while (n32 && (e32 = n32->obj) && h19 == n32->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se65, *e32)); 
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
                            STRING_TYPE dn_bought_city = e33->_1;  
                            long v37 = e33->__av; 
                          DOUBLE_TYPE agg5 = 0.0;
                          { //slice 
                            const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135* i34 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135*>(COUNTSTORE_SALES9_L2_3_DELTA.index[1]);
                            const HASH_RES_t h20 = COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::hash(se71.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                            HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode* n34 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode*>(i34->slice(se71, h20));
                            COUNTSTORE_SALES9_L2_3_DELTA_entry* e34;
                           
                            if (n34 && (e34 = n34->obj)) {
                              do {                
                                long store_sales_ss_sold_date_sk = e34->STORE_SALES_SS_SOLD_DATE_SK;
                                long store_sales_ss_hdemo_sk = e34->STORE_SALES_SS_HDEMO_SK;
                                long store_sales_ss_store_sk = e34->STORE_SALES_SS_STORE_SK;
                                DOUBLE_TYPE v38 = e34->__av;
                                agg5 += (v38 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se68.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se69.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se70.modify(store_sales_ss_sold_date_sk)))));
                                n34 = n34->nxt;
                              } while (n34 && (e34 = n34->obj) && h20 == n34->hash &&  COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::equals(se71, *e34)); 
                            }
                          }DOUBLE_TYPE l11 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se66.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se67.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg5 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se72.modify(store_sales_ss_addr_sk,dn_bought_city))));
                          DOUBLE_TYPE agg6 = 0.0;
                          { //slice 
                            const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135* i35 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135*>(COUNTSTORE_SALES9_L3_3_DELTA.index[1]);
                            const HASH_RES_t h21 = COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::hash(se78.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                            HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode* n35 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode*>(i35->slice(se78, h21));
                            COUNTSTORE_SALES9_L3_3_DELTA_entry* e35;
                           
                            if (n35 && (e35 = n35->obj)) {
                              do {                
                                long store_sales_ss_sold_date_sk = e35->STORE_SALES_SS_SOLD_DATE_SK;
                                long store_sales_ss_hdemo_sk = e35->STORE_SALES_SS_HDEMO_SK;
                                long store_sales_ss_store_sk = e35->STORE_SALES_SS_STORE_SK;
                                DOUBLE_TYPE v39 = e35->__av;
                                agg6 += (v39 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se75.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se76.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se77.modify(store_sales_ss_sold_date_sk)))));
                                n35 = n35->nxt;
                              } while (n35 && (e35 = n35->obj) && h21 == n35->hash &&  COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::equals(se78, *e35)); 
                            }
                          }DOUBLE_TYPE l12 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se73.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se74.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg6 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se79.modify(store_sales_ss_addr_sk,dn_bought_city))));
                          (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l12,l11),((v31 != 0 ? 1L : 0L) * (v32 * (v37 != 0 ? 1L : 0L)))) : (void)0);      
                            n33 = n33->nxt;
                          }
                        }
                      }
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h22 == n29->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se80, *e29)); 
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
                long dn_ss_ticket_number = e36->DN_SS_TICKET_NUMBER;
                long v40 = e36->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i37 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h26 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se97.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n37 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i37->slice(se97, h26));
                  COUNTCUSTOMER_ADDRESS2_entry* e37;
                 
                  if (n37 && (e37 = n37->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e37->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e37->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e37->CURRENT_ADDR_CA_CITY;
                      long v41 = e37->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i38 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h25 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se96.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n38 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i38->slice(se96, h25));
                        COUNTCUSTOMER1_L2_1_entry* e38;
                       
                        if (n38 && (e38 = n38->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e38->DN_BOUGHT_CITY;
                            long v42 = e38->__av;
                            DOUBLE_TYPE agg7 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135* i39 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135*>(COUNTSTORE_SALES9_L2_3_DELTA.index[1]);
                              const HASH_RES_t h23 = COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::hash(se87.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                              HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode* n39 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode*>(i39->slice(se87, h23));
                              COUNTSTORE_SALES9_L2_3_DELTA_entry* e39;
                             
                              if (n39 && (e39 = n39->obj)) {
                                do {                
                                  long store_sales_ss_sold_date_sk = e39->STORE_SALES_SS_SOLD_DATE_SK;
                                  long store_sales_ss_hdemo_sk = e39->STORE_SALES_SS_HDEMO_SK;
                                  long store_sales_ss_store_sk = e39->STORE_SALES_SS_STORE_SK;
                                  DOUBLE_TYPE v43 = e39->__av;
                                  agg7 += (v43 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se84.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se85.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se86.modify(store_sales_ss_sold_date_sk)))));
                                  n39 = n39->nxt;
                                } while (n39 && (e39 = n39->obj) && h23 == n39->hash &&  COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::equals(se87, *e39)); 
                              }
                            }DOUBLE_TYPE l13 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se82.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se83.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg7 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se88.modify(store_sales_ss_addr_sk,dn_bought_city))));
                            DOUBLE_TYPE agg8 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135* i40 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135*>(COUNTSTORE_SALES9_L3_3_DELTA.index[1]);
                              const HASH_RES_t h24 = COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::hash(se94.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                              HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode* n40 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode*>(i40->slice(se94, h24));
                              COUNTSTORE_SALES9_L3_3_DELTA_entry* e40;
                             
                              if (n40 && (e40 = n40->obj)) {
                                do {                
                                  long store_sales_ss_sold_date_sk = e40->STORE_SALES_SS_SOLD_DATE_SK;
                                  long store_sales_ss_hdemo_sk = e40->STORE_SALES_SS_HDEMO_SK;
                                  long store_sales_ss_store_sk = e40->STORE_SALES_SS_STORE_SK;
                                  DOUBLE_TYPE v44 = e40->__av;
                                  agg8 += (v44 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se91.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se92.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se93.modify(store_sales_ss_sold_date_sk)))));
                                  n40 = n40->nxt;
                                } while (n40 && (e40 = n40->obj) && h24 == n40->hash &&  COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::equals(se94, *e40)); 
                              }
                            }DOUBLE_TYPE l14 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se89.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se90.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg8 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se95.modify(store_sales_ss_addr_sk,dn_bought_city))));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se6.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l14,l13),(((v40 != 0 ? 1L : 0L) * (v41 * ((COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se81.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v42) != 0 ? 1L : 0L))) * -1L)) : (void)0);
                            n38 = n38->nxt;
                          } while (n38 && (e38 = n38->obj) && h25 == n38->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se96, *e38)); 
                        }
                      }
                      n37 = n37->nxt;
                    } while (n37 && (e37 = n37->obj) && h26 == n37->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se97, *e37)); 
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
                long dn_ss_ticket_number = e41->DN_SS_TICKET_NUMBER;
                long v45 = e41->__av;
                COUNTCUSTOMER_ADDRESS2_E1_2.addOrDelOnZero(se98.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v45 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se99.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se100.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se101.modify(store_sales_ss_sold_date_sk))))));
              n41 = n41->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i42 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n42; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e42;
        
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
                long dn_ss_ticket_number = e42->DN_SS_TICKET_NUMBER;
                long v46 = e42->__av;
                COUNTCUSTOMER_ADDRESS2_E1_2STORE1.addOrDelOnZero(se102.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v46 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se103.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se104.modify(store_sales_ss_sold_date_sk)))));
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i43 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n43; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e43;
        
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
                long dn_ss_ticket_number = e43->DN_SS_TICKET_NUMBER;
                long v47 = e43->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i44 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                  const HASH_RES_t h27 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se109.modify0(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n44 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i44->slice(se109, h27));
                  COUNTCUSTOMER1_L2_1_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      STRING_TYPE dn_bought_city = e44->DN_BOUGHT_CITY;
                      long v48 = e44->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se105.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number,dn_bought_city),(v47 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se106.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se107.modify(store_sales_ss_store_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se108.modify(store_sales_ss_sold_date_sk)) * v48)))));
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h27 == n44->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se109, *e44)); 
                  }
                }
              n43 = n43->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i45 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n45; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e45;
        
          for (size_t i = 0; i < i45->size_; i++)
          {
            n45 = i45->buckets_ + i;
            while (n45 && (e45 = n45->obj))
            {
                long store_sales_ss_sold_date_sk = e45->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e45->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e45->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e45->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e45->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e45->DN_SS_TICKET_NUMBER;
                long v49 = e45->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i46 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                  const HASH_RES_t h28 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se113.modify0(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n46 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i46->slice(se113, h28));
                  COUNTCUSTOMER1_L2_1_entry* e46;
                 
                  if (n46 && (e46 = n46->obj)) {
                    do {                
                      STRING_TYPE dn_bought_city = e46->DN_BOUGHT_CITY;
                      long v50 = e46->__av;
                      COUNTCUSTOMER1_E1_1STORE1.addOrDelOnZero(se110.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number,dn_bought_city),(v49 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se111.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se112.modify(store_sales_ss_sold_date_sk)) * v50))));
                      n46 = n46->nxt;
                    } while (n46 && (e46 = n46->obj) && h28 == n46->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se113, *e46)); 
                  }
                }
              n45 = n45->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345* i47 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L2_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345::IdxNode* n47; 
          COUNTSTORE_SALES9_L2_3_DELTA_entry* e47;
        
          for (size_t i = 0; i < i47->size_; i++)
          {
            n47 = i47->buckets_ + i;
            while (n47 && (e47 = n47->obj))
            {
                long store_sales_ss_sold_date_sk = e47->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e47->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e47->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e47->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e47->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e47->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v51 = e47->__av;
                COUNTCUSTOMER1_L2_2.addOrDelOnZero(se114.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v51 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se115.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se116.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se117.modify(store_sales_ss_sold_date_sk))))));
              n47 = n47->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345* i48 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L2_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345::IdxNode* n48; 
          COUNTSTORE_SALES9_L2_3_DELTA_entry* e48;
        
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
                long dn_ss_ticket_number = e48->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v52 = e48->__av;
                COUNTCUSTOMER1_L2_2STORE1.addOrDelOnZero(se118.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v52 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se119.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se120.modify(store_sales_ss_sold_date_sk)))));
              n48 = n48->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345* i49 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L3_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345::IdxNode* n49; 
          COUNTSTORE_SALES9_L3_3_DELTA_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long store_sales_ss_sold_date_sk = e49->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e49->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e49->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e49->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e49->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e49->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v53 = e49->__av;
                COUNTCUSTOMER1_L3_2.addOrDelOnZero(se121.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v53 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se122.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se123.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se124.modify(store_sales_ss_sold_date_sk))))));
              n49 = n49->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345* i50 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L3_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345::IdxNode* n50; 
          COUNTSTORE_SALES9_L3_3_DELTA_entry* e50;
        
          for (size_t i = 0; i < i50->size_; i++)
          {
            n50 = i50->buckets_ + i;
            while (n50 && (e50 = n50->obj))
            {
                long store_sales_ss_sold_date_sk = e50->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e50->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e50->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e50->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e50->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e50->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v54 = e50->__av;
                COUNTCUSTOMER1_L3_2STORE1.addOrDelOnZero(se125.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v54 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se126.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se127.modify(store_sales_ss_sold_date_sk)))));
              n50 = n50->nxt;
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
                long customer_c_current_addr_sk = DELTA_CUSTOMER.c_current_addr_sk[i];
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
                long v55 = 1L;
                COUNTCUSTOMER1_DELTA.addOrDelOnZero(se128.modify(customer_c_customer_sk,customer_c_current_addr_sk,customer_c_first_name,customer_c_last_name),v55);
          }
        }

        {  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_0123* i52 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_0123*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_0123::IdxNode* n52; 
          COUNTCUSTOMER1_DELTA_entry* e52;
        
          for (size_t i = 0; i < i52->size_; i++)
          {
            n52 = i52->buckets_ + i;
            while (n52 && (e52 = n52->obj))
            {
                long customer_c_customer_sk = e52->CUSTOMER_C_CUSTOMER_SK;
                long customer_c_current_addr_sk = e52->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_c_first_name = e52->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e52->CUSTOMER_C_LAST_NAME;
                long v56 = e52->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_map_0* i53 = static_cast<HashIndex_COUNTCUSTOMER1_map_0*>(COUNTCUSTOMER1.index[1]);
                  const HASH_RES_t h30 = COUNTCUSTOMER1_mapkey0_idxfn::hash(se135.modify0(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER1_map_0::IdxNode* n53 = static_cast<HashIndex_COUNTCUSTOMER1_map_0::IdxNode*>(i53->slice(se135, h30));
                  COUNTCUSTOMER1_entry* e53;
                 
                  if (n53 && (e53 = n53->obj)) {
                    do {                
                      STRING_TYPE current_addr_ca_city = e53->CURRENT_ADDR_CA_CITY;
                      long v57 = e53->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i54 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h29 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se134.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n54 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i54->slice(se134, h29));
                        COUNTCUSTOMER1_E1_1_entry* e54;
                       
                        if (n54 && (e54 = n54->obj)) {
                          do {                
                            long store_sales_ss_addr_sk = e54->STORE_SALES_SS_ADDR_SK;
                            long dn_ss_ticket_number = e54->DN_SS_TICKET_NUMBER;
                            STRING_TYPE dn_bought_city = e54->DN_BOUGHT_CITY;
                            long v58 = e54->__av;
                            DOUBLE_TYPE l15 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se130.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se131.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            DOUBLE_TYPE l16 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se132.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se133.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se129.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l15,l16),(v56 * (v57 * (v58 != 0 ? 1L : 0L)))) : (void)0);
                            n54 = n54->nxt;
                          } while (n54 && (e54 = n54->obj) && h29 == n54->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se134, *e54)); 
                        }
                      }
                      n53 = n53->nxt;
                    } while (n53 && (e53 = n53->obj) && h30 == n53->hash &&  COUNTCUSTOMER1_mapkey0_idxfn::equals(se135, *e53)); 
                  }
                }
              n52 = n52->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_0123* i55 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_0123*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_0123::IdxNode* n55; 
          COUNTCUSTOMER1_DELTA_entry* e55;
        
          for (size_t i = 0; i < i55->size_; i++)
          {
            n55 = i55->buckets_ + i;
            while (n55 && (e55 = n55->obj))
            {
                long customer_c_customer_sk = e55->CUSTOMER_C_CUSTOMER_SK;
                long customer_c_current_addr_sk = e55->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_c_first_name = e55->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e55->CUSTOMER_C_LAST_NAME;
                long v59 = e55->__av;
                COUNTCUSTOMER_ADDRESS1.addOrDelOnZero(se136.modify(customer_c_customer_sk,customer_c_current_addr_sk,customer_c_first_name,customer_c_last_name),v59);
              n55 = n55->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_0123* i56 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_0123*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_0123::IdxNode* n56; 
          COUNTCUSTOMER1_DELTA_entry* e56;
        
          for (size_t i = 0; i < i56->size_; i++)
          {
            n56 = i56->buckets_ + i;
            while (n56 && (e56 = n56->obj))
            {
                long customer_c_customer_sk = e56->CUSTOMER_C_CUSTOMER_SK;
                long customer_c_current_addr_sk = e56->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_c_first_name = e56->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e56->CUSTOMER_C_LAST_NAME;
                long v60 = e56->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_map_0* i57 = static_cast<HashIndex_COUNTCUSTOMER1_map_0*>(COUNTCUSTOMER1.index[1]);
                  const HASH_RES_t h31 = COUNTCUSTOMER1_mapkey0_idxfn::hash(se138.modify0(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER1_map_0::IdxNode* n57 = static_cast<HashIndex_COUNTCUSTOMER1_map_0::IdxNode*>(i57->slice(se138, h31));
                  COUNTCUSTOMER1_entry* e57;
                 
                  if (n57 && (e57 = n57->obj)) {
                    do {                
                      STRING_TYPE current_addr_ca_city = e57->CURRENT_ADDR_CA_CITY;
                      long v61 = e57->__av;
                      COUNTCUSTOMER_ADDRESS2.addOrDelOnZero(se137.modify(customer_c_customer_sk,customer_c_first_name,customer_c_last_name,current_addr_ca_city),(v60 * v61));
                      n57 = n57->nxt;
                    } while (n57 && (e57 = n57->obj) && h31 == n57->hash &&  COUNTCUSTOMER1_mapkey0_idxfn::equals(se138, *e57)); 
                  }
                }
              n56 = n56->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_CUSTOMER_ADDRESS(TPCDSCustomerAddressBatch& DELTA_CUSTOMER_ADDRESS) {
      {  
        if (tS > 0) { tS += DELTA_CUSTOMER_ADDRESS.size; return; }         
        tLastN += DELTA_CUSTOMER_ADDRESS.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_CUSTOMER_ADDRESS.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_CUSTOMER_ADDRESS.size;

        COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.clear();
        COUNTCUSTOMER_ADDRESS2_DOMAIN1.clear();
        COUNTCUSTOMER_ADDRESS1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_CUSTOMER_ADDRESS.size; i++) 
          {
                long store_sales_ss_addr_sk = DELTA_CUSTOMER_ADDRESS.ca_address_sk[i];
                // STRING_TYPE customer_address_ca_address_id = DELTA_CUSTOMER_ADDRESS.ca_address_id[i];
                // STRING_TYPE customer_address_ca_street_number = DELTA_CUSTOMER_ADDRESS.ca_street_number[i];
                // STRING_TYPE customer_address_ca_street_name = DELTA_CUSTOMER_ADDRESS.ca_street_name[i];
                // STRING_TYPE customer_address_ca_street_type = DELTA_CUSTOMER_ADDRESS.ca_street_type[i];
                // STRING_TYPE customer_address_ca_suite_number = DELTA_CUSTOMER_ADDRESS.ca_suite_number[i];
                STRING_TYPE customer_address_ca_city = DELTA_CUSTOMER_ADDRESS.ca_city[i];
                // STRING_TYPE customer_address_ca_county = DELTA_CUSTOMER_ADDRESS.ca_county[i];
                // STRING_TYPE customer_address_ca_state = DELTA_CUSTOMER_ADDRESS.ca_state[i];
                // STRING_TYPE customer_address_ca_zip = DELTA_CUSTOMER_ADDRESS.ca_zip[i];
                // STRING_TYPE customer_address_ca_country = DELTA_CUSTOMER_ADDRESS.ca_country[i];
                // DOUBLE_TYPE customer_address_ca_gmt_offset = DELTA_CUSTOMER_ADDRESS.ca_gmt_offset[i];
                // STRING_TYPE customer_address_ca_location_type = DELTA_CUSTOMER_ADDRESS.ca_location_type[i];
                long v62 = 1L;
                COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.addOrDelOnZero(se139.modify(store_sales_ss_addr_sk,customer_address_ca_city),v62);            
                long v63 = 1L;
                COUNTCUSTOMER_ADDRESS2_DOMAIN1.addOrDelOnZero(se140.modify(store_sales_ss_addr_sk,customer_address_ca_city),(v63 != 0 ? 1L : 0L));
                long v64 = 1L;
                COUNTCUSTOMER_ADDRESS1_DELTA.addOrDelOnZero(se141.modify(store_sales_ss_addr_sk,customer_address_ca_city),v64);
          }
        }

        {  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i61 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n61; 
          COUNTCUSTOMER_ADDRESS1_DELTA_entry* e61;
        
          for (size_t i = 0; i < i61->size_; i++)
          {
            n61 = i61->buckets_ + i;
            while (n61 && (e61 = n61->obj))
            {
                long customer_c_current_addr_sk = e61->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE current_addr_ca_city = e61->CURRENT_ADDR_CA_CITY;
                long v65 = e61->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i62 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                  const HASH_RES_t h33 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se148.modify1(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n62 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i62->slice(se148, h33));
                  COUNTCUSTOMER_ADDRESS1_entry* e62;
                 
                  if (n62 && (e62 = n62->obj)) {
                    do {                
                      long customer_c_customer_sk = e62->CUSTOMER_C_CUSTOMER_SK;
                      STRING_TYPE customer_c_first_name = e62->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e62->CUSTOMER_C_LAST_NAME;
                      long v66 = e62->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i63 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h32 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se147.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n63 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i63->slice(se147, h32));
                        COUNTCUSTOMER1_E1_1_entry* e63;
                       
                        if (n63 && (e63 = n63->obj)) {
                          do {                
                            long store_sales_ss_addr_sk = e63->STORE_SALES_SS_ADDR_SK;
                            long dn_ss_ticket_number = e63->DN_SS_TICKET_NUMBER;
                            STRING_TYPE dn_bought_city = e63->DN_BOUGHT_CITY;
                            long v67 = e63->__av;
                            DOUBLE_TYPE l17 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se143.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se144.modify(store_sales_ss_addr_sk,dn_bought_city)));
                            DOUBLE_TYPE l18 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se145.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se146.modify(store_sales_ss_addr_sk,dn_bought_city)));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se142.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l18,l17),(v65 * (v66 * (v67 != 0 ? 1L : 0L)))) : (void)0);
                            n63 = n63->nxt;
                          } while (n63 && (e63 = n63->obj) && h32 == n63->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se147, *e63)); 
                        }
                      }
                      n62 = n62->nxt;
                    } while (n62 && (e62 = n62->obj) && h33 == n62->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se148, *e62)); 
                  }
                }
              n61 = n61->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i64 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n64; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e64;
        
          for (size_t i = 0; i < i64->size_; i++)
          {
            n64 = i64->buckets_ + i;
            while (n64 && (e64 = n64->obj))
            {
                long store_sales_ss_addr_sk = e64->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e64->DN_BOUGHT_CITY;
                long v68 = e64->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123* i65 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123*>(COUNTCUSTOMER_ADDRESS2.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123::IdxNode* n65; 
                  COUNTCUSTOMER_ADDRESS2_entry* e65;
                
                  for (size_t i = 0; i < i65->size_; i++)
                  {
                    n65 = i65->buckets_ + i;
                    while (n65 && (e65 = n65->obj))
                    {
                        long customer_c_customer_sk = e65->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e65->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e65->CUSTOMER_C_LAST_NAME;
                        STRING_TYPE current_addr_ca_city = e65->CURRENT_ADDR_CA_CITY;
                        long v69 = e65->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i66 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                          const HASH_RES_t h34 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se154.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n66 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i66->slice(se154, h34));
                          COUNTCUSTOMER_ADDRESS2_E1_2_entry* e66;
                         
                          if (n66 && (e66 = n66->obj)) {
                            do {                
                              long dn_ss_ticket_number = e66->DN_SS_TICKET_NUMBER;
                              long v70 = e66->__av;
                              DOUBLE_TYPE l19 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se150.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se151.modify(store_sales_ss_addr_sk,dn_bought_city)));
                              DOUBLE_TYPE l20 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se152.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se153.modify(store_sales_ss_addr_sk,dn_bought_city)));
                              (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se142.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l20,l19),(((v68 != 0 ? 1L : 0L) * (v69 * ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se149.modify(store_sales_ss_addr_sk,dn_bought_city)) * v70) != 0 ? 1L : 0L))) * -1L)) : (void)0);
                              n66 = n66->nxt;
                            } while (n66 && (e66 = n66->obj) && h34 == n66->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se154, *e66)); 
                          }
                        }
                      n65 = n65->nxt;
                    }
                  }
                }
              n64 = n64->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i67 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n67; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long store_sales_ss_addr_sk = e67->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e67->DN_BOUGHT_CITY;
                long v71 = e67->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i68 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n68; 
                  COUNTCUSTOMER_ADDRESS1_DELTA_entry* e68;
                
                  for (size_t i = 0; i < i68->size_; i++)
                  {
                    n68 = i68->buckets_ + i;
                    while (n68 && (e68 = n68->obj))
                    {
                        long customer_c_current_addr_sk = e68->CUSTOMER_C_CURRENT_ADDR_SK;
                        STRING_TYPE current_addr_ca_city = e68->CURRENT_ADDR_CA_CITY;
                        long v72 = e68->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i69 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                          const HASH_RES_t h36 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se161.modify1(customer_c_current_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n69 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i69->slice(se161, h36));
                          COUNTCUSTOMER_ADDRESS1_entry* e69;
                         
                          if (n69 && (e69 = n69->obj)) {
                            do {                
                              long customer_c_customer_sk = e69->CUSTOMER_C_CUSTOMER_SK;
                              STRING_TYPE customer_c_first_name = e69->CUSTOMER_C_FIRST_NAME;
                              STRING_TYPE customer_c_last_name = e69->CUSTOMER_C_LAST_NAME;
                              long v73 = e69->__av;
                              { //slice 
                                const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i70 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                                const HASH_RES_t h35 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se160.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                                HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n70 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i70->slice(se160, h35));
                                COUNTCUSTOMER_ADDRESS2_E1_2_entry* e70;
                               
                                if (n70 && (e70 = n70->obj)) {
                                  do {                
                                    long dn_ss_ticket_number = e70->DN_SS_TICKET_NUMBER;
                                    long v74 = e70->__av;
                                    DOUBLE_TYPE l21 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se156.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se157.modify(store_sales_ss_addr_sk,dn_bought_city)));
                                    DOUBLE_TYPE l22 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se158.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se159.modify(store_sales_ss_addr_sk,dn_bought_city)));
                                    (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se142.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l22,l21),(((v71 != 0 ? 1L : 0L) * (v72 * (v73 * ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se155.modify(store_sales_ss_addr_sk,dn_bought_city)) * v74) != 0 ? 1L : 0L)))) * -1L)) : (void)0);
                                    n70 = n70->nxt;
                                  } while (n70 && (e70 = n70->obj) && h35 == n70->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se160, *e70)); 
                                }
                              }
                              n69 = n69->nxt;
                            } while (n69 && (e69 = n69->obj) && h36 == n69->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se161, *e69)); 
                          }
                        }
                      n68 = n68->nxt;
                    }
                  }
                }
              n67 = n67->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i71 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n71; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e71;
        
          for (size_t i = 0; i < i71->size_; i++)
          {
            n71 = i71->buckets_ + i;
            while (n71 && (e71 = n71->obj))
            {
                long store_sales_ss_addr_sk = e71->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e71->DN_BOUGHT_CITY;
                long v75 = e71->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123* i72 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123*>(COUNTCUSTOMER_ADDRESS2.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123::IdxNode* n72; 
                  COUNTCUSTOMER_ADDRESS2_entry* e72;
                
                  for (size_t i = 0; i < i72->size_; i++)
                  {
                    n72 = i72->buckets_ + i;
                    while (n72 && (e72 = n72->obj))
                    {
                        long customer_c_customer_sk = e72->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e72->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e72->CUSTOMER_C_LAST_NAME;
                        STRING_TYPE current_addr_ca_city = e72->CURRENT_ADDR_CA_CITY;
                        long v76 = e72->__av;
                        _c5.clear();
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i73 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                          const HASH_RES_t h37 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se163.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n73 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i73->slice(se163, h37));
                          COUNTCUSTOMER_ADDRESS2_E1_2_entry* e73;
                         
                          if (n73 && (e73 = n73->obj)) {
                            do {                
                              long dn_ss_ticket_number = e73->DN_SS_TICKET_NUMBER;
                              long v78 = e73->__av;
                              _c5.addOrDelOnZero(st10.modify(dn_ss_ticket_number,(COUNTCUSTOMER1_L2_1.getValueOrDefault(se162.modify(store_sales_ss_addr_sk,dn_bought_city)) * v78)), (COUNTCUSTOMER1_L2_1.getValueOrDefault(se162.modify(store_sales_ss_addr_sk,dn_bought_city)) * v78));
                              n73 = n73->nxt;
                            } while (n73 && (e73 = n73->obj) && h37 == n73->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se163, *e73)); 
                          }
                        }{ //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i74 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                          const HASH_RES_t h38 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se165.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n74 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i74->slice(se165, h38));
                          COUNTCUSTOMER_ADDRESS2_E1_2_entry* e74;
                         
                          if (n74 && (e74 = n74->obj)) {
                            do {                
                              long dn_ss_ticket_number = e74->DN_SS_TICKET_NUMBER;
                              long v79 = e74->__av;
                              _c5.addOrDelOnZero(st11.modify(dn_ss_ticket_number,(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se164.modify(store_sales_ss_addr_sk,dn_bought_city)) * v79)), (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se164.modify(store_sales_ss_addr_sk,dn_bought_city)) * v79));
                              n74 = n74->nxt;
                            } while (n74 && (e74 = n74->obj) && h38 == n74->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se165, *e74)); 
                          }
                        }{  // temp foreach
                          const HashIndex<tuple2_L_L, long>* i75 = static_cast<HashIndex<tuple2_L_L, long>*>(_c5.index[0]);
                          HashIndex<tuple2_L_L, long>::IdxNode* n75; 
                          tuple2_L_L* e75;
                        
                          for (size_t i = 0; i < i75->size_; i++)
                          {
                            n75 = i75->buckets_ + i;
                            while (n75 && (e75 = n75->obj))
                            {
                              long dn_ss_ticket_number = e75->_1;  
                              long v80 = e75->__av; 
                            DOUBLE_TYPE l23 = ((COUNTCUSTOMER1_L2_2.getValueOrDefault(se166.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se167.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se168.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se169.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                            DOUBLE_TYPE l24 = ((COUNTCUSTOMER1_L3_2.getValueOrDefault(se170.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se171.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se172.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se173.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se142.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l24,l23),((v75 != 0 ? 1L : 0L) * (v76 * (v80 != 0 ? 1L : 0L)))) : (void)0);      
                              n75 = n75->nxt;
                            }
                          }
                        }
                      n72 = n72->nxt;
                    }
                  }
                }
              n71 = n71->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i76 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n76; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e76;
        
          for (size_t i = 0; i < i76->size_; i++)
          {
            n76 = i76->buckets_ + i;
            while (n76 && (e76 = n76->obj))
            {
                long store_sales_ss_addr_sk = e76->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e76->DN_BOUGHT_CITY;
                long v81 = e76->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i77 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n77; 
                  COUNTCUSTOMER_ADDRESS1_DELTA_entry* e77;
                
                  for (size_t i = 0; i < i77->size_; i++)
                  {
                    n77 = i77->buckets_ + i;
                    while (n77 && (e77 = n77->obj))
                    {
                        long customer_c_current_addr_sk = e77->CUSTOMER_C_CURRENT_ADDR_SK;
                        STRING_TYPE current_addr_ca_city = e77->CURRENT_ADDR_CA_CITY;
                        long v82 = e77->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i78 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                          const HASH_RES_t h41 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se186.modify1(customer_c_current_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n78 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i78->slice(se186, h41));
                          COUNTCUSTOMER_ADDRESS1_entry* e78;
                         
                          if (n78 && (e78 = n78->obj)) {
                            do {                
                              long customer_c_customer_sk = e78->CUSTOMER_C_CUSTOMER_SK;
                              STRING_TYPE customer_c_first_name = e78->CUSTOMER_C_FIRST_NAME;
                              STRING_TYPE customer_c_last_name = e78->CUSTOMER_C_LAST_NAME;
                              long v83 = e78->__av;
                              _c6.clear();
                              { //slice 
                                const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i79 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                                const HASH_RES_t h39 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se175.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                                HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n79 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i79->slice(se175, h39));
                                COUNTCUSTOMER_ADDRESS2_E1_2_entry* e79;
                               
                                if (n79 && (e79 = n79->obj)) {
                                  do {                
                                    long dn_ss_ticket_number = e79->DN_SS_TICKET_NUMBER;
                                    long v85 = e79->__av;
                                    _c6.addOrDelOnZero(st12.modify(dn_ss_ticket_number,(COUNTCUSTOMER1_L2_1.getValueOrDefault(se174.modify(store_sales_ss_addr_sk,dn_bought_city)) * v85)), (COUNTCUSTOMER1_L2_1.getValueOrDefault(se174.modify(store_sales_ss_addr_sk,dn_bought_city)) * v85));
                                    n79 = n79->nxt;
                                  } while (n79 && (e79 = n79->obj) && h39 == n79->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se175, *e79)); 
                                }
                              }{ //slice 
                                const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i80 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                                const HASH_RES_t h40 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se177.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                                HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n80 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i80->slice(se177, h40));
                                COUNTCUSTOMER_ADDRESS2_E1_2_entry* e80;
                               
                                if (n80 && (e80 = n80->obj)) {
                                  do {                
                                    long dn_ss_ticket_number = e80->DN_SS_TICKET_NUMBER;
                                    long v86 = e80->__av;
                                    _c6.addOrDelOnZero(st13.modify(dn_ss_ticket_number,(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se176.modify(store_sales_ss_addr_sk,dn_bought_city)) * v86)), (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se176.modify(store_sales_ss_addr_sk,dn_bought_city)) * v86));
                                    n80 = n80->nxt;
                                  } while (n80 && (e80 = n80->obj) && h40 == n80->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se177, *e80)); 
                                }
                              }{  // temp foreach
                                const HashIndex<tuple2_L_L, long>* i81 = static_cast<HashIndex<tuple2_L_L, long>*>(_c6.index[0]);
                                HashIndex<tuple2_L_L, long>::IdxNode* n81; 
                                tuple2_L_L* e81;
                              
                                for (size_t i = 0; i < i81->size_; i++)
                                {
                                  n81 = i81->buckets_ + i;
                                  while (n81 && (e81 = n81->obj))
                                  {
                                    long dn_ss_ticket_number = e81->_1;  
                                    long v87 = e81->__av; 
                                  DOUBLE_TYPE l25 = ((COUNTCUSTOMER1_L2_2.getValueOrDefault(se178.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se179.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se180.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se181.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                                  DOUBLE_TYPE l26 = ((COUNTCUSTOMER1_L3_2.getValueOrDefault(se182.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se183.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se184.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se185.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                                  (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se142.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l26,l25),((v81 != 0 ? 1L : 0L) * (v82 * (v83 * (v87 != 0 ? 1L : 0L))))) : (void)0);      
                                    n81 = n81->nxt;
                                  }
                                }
                              }
                              n78 = n78->nxt;
                            } while (n78 && (e78 = n78->obj) && h41 == n78->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se186, *e78)); 
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
          const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i82 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n82; 
          COUNTCUSTOMER_ADDRESS1_DELTA_entry* e82;
        
          for (size_t i = 0; i < i82->size_; i++)
          {
            n82 = i82->buckets_ + i;
            while (n82 && (e82 = n82->obj))
            {
                long customer_c_current_addr_sk = e82->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE current_addr_ca_city = e82->CURRENT_ADDR_CA_CITY;
                long v88 = e82->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i83 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                  const HASH_RES_t h42 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se188.modify1(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n83 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i83->slice(se188, h42));
                  COUNTCUSTOMER_ADDRESS1_entry* e83;
                 
                  if (n83 && (e83 = n83->obj)) {
                    do {                
                      long customer_c_customer_sk = e83->CUSTOMER_C_CUSTOMER_SK;
                      STRING_TYPE customer_c_first_name = e83->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e83->CUSTOMER_C_LAST_NAME;
                      long v89 = e83->__av;
                      COUNTCUSTOMER_ADDRESS2.addOrDelOnZero(se187.modify(customer_c_customer_sk,customer_c_first_name,customer_c_last_name,current_addr_ca_city),(v88 * v89));
                      n83 = n83->nxt;
                    } while (n83 && (e83 = n83->obj) && h42 == n83->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se188, *e83)); 
                  }
                }
              n82 = n82->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i84 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n84; 
          COUNTCUSTOMER_ADDRESS1_DELTA_entry* e84;
        
          for (size_t i = 0; i < i84->size_; i++)
          {
            n84 = i84->buckets_ + i;
            while (n84 && (e84 = n84->obj))
            {
                long customer_c_current_addr_sk = e84->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE current_addr_ca_city = e84->CURRENT_ADDR_CA_CITY;
                long v90 = e84->__av;
                COUNTCUSTOMER1.addOrDelOnZero(se189.modify(customer_c_current_addr_sk,current_addr_ca_city),v90);
              n84 = n84->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01* i85 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01::IdxNode* n85; 
          COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry* e85;
        
          for (size_t i = 0; i < i85->size_; i++)
          {
            n85 = i85->buckets_ + i;
            while (n85 && (e85 = n85->obj))
            {
                long store_sales_ss_addr_sk = e85->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e85->DN_BOUGHT_CITY;
                long v91 = e85->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1* i86 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[2]);
                  const HASH_RES_t h43 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey1_idxfn::hash(se191.modify1(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1::IdxNode* n86 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1::IdxNode*>(i86->slice(se191, h43));
                  COUNTCUSTOMER_ADDRESS2_E1_2_entry* e86;
                 
                  if (n86 && (e86 = n86->obj)) {
                    do {                
                      long customer_c_customer_sk = e86->CUSTOMER_C_CUSTOMER_SK;
                      long dn_ss_ticket_number = e86->DN_SS_TICKET_NUMBER;
                      long v92 = e86->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se190.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number,dn_bought_city),(v91 * v92));
                      n86 = n86->nxt;
                    } while (n86 && (e86 = n86->obj) && h43 == n86->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey1_idxfn::equals(se191, *e86)); 
                  }
                }
              n85 = n85->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01* i87 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01::IdxNode* n87; 
          COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry* e87;
        
          for (size_t i = 0; i < i87->size_; i++)
          {
            n87 = i87->buckets_ + i;
            while (n87 && (e87 = n87->obj))
            {
                long store_sales_ss_addr_sk = e87->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e87->DN_BOUGHT_CITY;
                long v93 = e87->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1* i88 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1*>(COUNTCUSTOMER_ADDRESS2_E1_2STORE1.index[1]);
                  const HASH_RES_t h44 = COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey1_idxfn::hash(se193.modify1(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1::IdxNode* n88 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1::IdxNode*>(i88->slice(se193, h44));
                  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry* e88;
                 
                  if (n88 && (e88 = n88->obj)) {
                    do {                
                      long customer_c_customer_sk = e88->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_store_sk = e88->STORE_SALES_SS_STORE_SK;
                      long dn_ss_ticket_number = e88->DN_SS_TICKET_NUMBER;
                      long v94 = e88->__av;
                      COUNTCUSTOMER1_E1_1STORE1.addOrDelOnZero(se192.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number,dn_bought_city),(v93 * v94));
                      n88 = n88->nxt;
                    } while (n88 && (e88 = n88->obj) && h44 == n88->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey1_idxfn::equals(se193, *e88)); 
                  }
                }
              n87 = n87->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01* i89 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01::IdxNode* n89; 
          COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry* e89;
        
          for (size_t i = 0; i < i89->size_; i++)
          {
            n89 = i89->buckets_ + i;
            while (n89 && (e89 = n89->obj))
            {
                long store_sales_ss_addr_sk = e89->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e89->DN_BOUGHT_CITY;
                long v95 = e89->__av;
                COUNTCUSTOMER1_L2_1.addOrDelOnZero(se194.modify(store_sales_ss_addr_sk,dn_bought_city),v95);
              n89 = n89->nxt;
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

        COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.clear();
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
                STRING_TYPE store_s_city = DELTA_STORE.s_city[i];
                // STRING_TYPE store_s_county = DELTA_STORE.s_county[i];
                // STRING_TYPE store_s_state = DELTA_STORE.s_state[i];
                // STRING_TYPE store_s_zip = DELTA_STORE.s_zip[i];
                // STRING_TYPE store_s_country = DELTA_STORE.s_country[i];
                // DOUBLE_TYPE store_s_gmt_offset = DELTA_STORE.s_gmt_offset[i];
                // DOUBLE_TYPE store_s_tax_precentage = DELTA_STORE.s_tax_precentage[i];
                long v96 = 1L;
                (/*if */(((store_s_city == c1) || (store_s_city == c2) || (store_s_city == c3) || (store_s_city == c4) || (store_s_city == c5))) ? COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.addOrDelOnZero(se195.modify(store_sales_ss_store_sk),v96) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i91 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n91; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long store_sales_ss_store_sk = e91->STORE_SALES_SS_STORE_SK;
                long v97 = e91->__av;
                COUNTSTORE_SALES1_E1_2_P_2.addOrDelOnZero(se196.modify(store_sales_ss_store_sk),v97);
              n91 = n91->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i92 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n92; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e92;
        
          for (size_t i = 0; i < i92->size_; i++)
          {
            n92 = i92->buckets_ + i;
            while (n92 && (e92 = n92->obj))
            {
                long store_sales_ss_store_sk = e92->STORE_SALES_SS_STORE_SK;
                long v98 = e92->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2* i93 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2*>(COUNTCUSTOMER_ADDRESS2_E1_2STORE1.index[2]);
                  const HASH_RES_t h45 = COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey2_idxfn::hash(se198.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2::IdxNode* n93 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2::IdxNode*>(i93->slice(se198, h45));
                  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry* e93;
                 
                  if (n93 && (e93 = n93->obj)) {
                    do {                
                      long customer_c_customer_sk = e93->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e93->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e93->DN_SS_TICKET_NUMBER;
                      long v99 = e93->__av;
                      COUNTCUSTOMER_ADDRESS2_E1_2.addOrDelOnZero(se197.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v98 * v99));
                      n93 = n93->nxt;
                    } while (n93 && (e93 = n93->obj) && h45 == n93->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey2_idxfn::equals(se198, *e93)); 
                  }
                }
              n92 = n92->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i94 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n94; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e94;
        
          for (size_t i = 0; i < i94->size_; i++)
          {
            n94 = i94->buckets_ + i;
            while (n94 && (e94 = n94->obj))
            {
                long store_sales_ss_store_sk = e94->STORE_SALES_SS_STORE_SK;
                long v100 = e94->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2* i95 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2*>(COUNTCUSTOMER1_E1_1STORE1.index[1]);
                  const HASH_RES_t h46 = COUNTCUSTOMER1_E1_1STORE1_mapkey2_idxfn::hash(se200.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2::IdxNode* n95 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2::IdxNode*>(i95->slice(se200, h46));
                  COUNTCUSTOMER1_E1_1STORE1_entry* e95;
                 
                  if (n95 && (e95 = n95->obj)) {
                    do {                
                      long customer_c_customer_sk = e95->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e95->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e95->DN_SS_TICKET_NUMBER;
                      STRING_TYPE dn_bought_city = e95->DN_BOUGHT_CITY;
                      long v101 = e95->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se199.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number,dn_bought_city),(v100 * v101));
                      n95 = n95->nxt;
                    } while (n95 && (e95 = n95->obj) && h46 == n95->hash &&  COUNTCUSTOMER1_E1_1STORE1_mapkey2_idxfn::equals(se200, *e95)); 
                  }
                }
              n94 = n94->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i96 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n96; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e96;
        
          for (size_t i = 0; i < i96->size_; i++)
          {
            n96 = i96->buckets_ + i;
            while (n96 && (e96 = n96->obj))
            {
                long store_sales_ss_store_sk = e96->STORE_SALES_SS_STORE_SK;
                long v102 = e96->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2* i97 = static_cast<HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2*>(COUNTCUSTOMER1_L2_2STORE1.index[1]);
                  const HASH_RES_t h47 = COUNTCUSTOMER1_L2_2STORE1_mapkey2_idxfn::hash(se202.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2::IdxNode* n97 = static_cast<HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2::IdxNode*>(i97->slice(se202, h47));
                  COUNTCUSTOMER1_L2_2STORE1_entry* e97;
                 
                  if (n97 && (e97 = n97->obj)) {
                    do {                
                      long customer_c_customer_sk = e97->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e97->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e97->DN_SS_TICKET_NUMBER;
                      DOUBLE_TYPE v103 = e97->__av;
                      COUNTCUSTOMER1_L2_2.addOrDelOnZero(se201.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v102 * v103));
                      n97 = n97->nxt;
                    } while (n97 && (e97 = n97->obj) && h47 == n97->hash &&  COUNTCUSTOMER1_L2_2STORE1_mapkey2_idxfn::equals(se202, *e97)); 
                  }
                }
              n96 = n96->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i98 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n98; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e98;
        
          for (size_t i = 0; i < i98->size_; i++)
          {
            n98 = i98->buckets_ + i;
            while (n98 && (e98 = n98->obj))
            {
                long store_sales_ss_store_sk = e98->STORE_SALES_SS_STORE_SK;
                long v104 = e98->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2* i99 = static_cast<HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2*>(COUNTCUSTOMER1_L3_2STORE1.index[1]);
                  const HASH_RES_t h48 = COUNTCUSTOMER1_L3_2STORE1_mapkey2_idxfn::hash(se204.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2::IdxNode* n99 = static_cast<HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2::IdxNode*>(i99->slice(se204, h48));
                  COUNTCUSTOMER1_L3_2STORE1_entry* e99;
                 
                  if (n99 && (e99 = n99->obj)) {
                    do {                
                      long customer_c_customer_sk = e99->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e99->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e99->DN_SS_TICKET_NUMBER;
                      DOUBLE_TYPE v105 = e99->__av;
                      COUNTCUSTOMER1_L3_2.addOrDelOnZero(se203.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v104 * v105));
                      n99 = n99->nxt;
                    } while (n99 && (e99 = n99->obj) && h48 == n99->hash &&  COUNTCUSTOMER1_L3_2STORE1_mapkey2_idxfn::equals(se204, *e99)); 
                  }
                }
              n98 = n98->nxt;
            }
          }
        }COUNT.clear();
        {  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123* i100 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123*>(COUNTCUSTOMER_ADDRESS2.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123::IdxNode* n100; 
          COUNTCUSTOMER_ADDRESS2_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long customer_c_customer_sk = e100->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e100->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e100->CUSTOMER_C_LAST_NAME;
                STRING_TYPE current_addr_ca_city = e100->CURRENT_ADDR_CA_CITY;
                long v106 = e100->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i101 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                  const HASH_RES_t h49 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se210.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n101 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i101->slice(se210, h49));
                  COUNTCUSTOMER1_E1_1_entry* e101;
                 
                  if (n101 && (e101 = n101->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e101->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e101->DN_SS_TICKET_NUMBER;
                      STRING_TYPE dn_bought_city = e101->DN_BOUGHT_CITY;
                      long v107 = e101->__av;
                      DOUBLE_TYPE l27 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se206.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se207.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                      DOUBLE_TYPE l28 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se208.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se209.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                      (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se205.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l27,l28),(v106 * (v107 != 0 ? 1L : 0L))) : (void)0);
                      n101 = n101->nxt;
                    } while (n101 && (e101 = n101->obj) && h49 == n101->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se210, *e101)); 
                  }
                }
              n100 = n100->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTSTORE_SALES1_E1_2_P_1.clear();
        {  // foreach
          const HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234* i102 = static_cast<HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234*>(HOUSEHOLD_DEMOGRAPHICS.index[0]);
          HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234::IdxNode* n102; 
          HOUSEHOLD_DEMOGRAPHICS_entry* e102;
        
          for (size_t i = 0; i < i102->size_; i++)
          {
            n102 = i102->buckets_ + i;
            while (n102 && (e102 = n102->obj))
            {
                long store_sales_ss_hdemo_sk = e102->HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK;
                long household_demographics_hd_income_band_sk = e102->HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK;
                STRING_TYPE household_demographics_hd_buy_potential = e102->HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL;
                long household_demographics_hd_dep_count = e102->HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT;
                long household_demographics_hd_vehicle_count = e102->HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
                long v108 = e102->__av;
                long l29 = ((/*if */(household_demographics_hd_dep_count == 6L) ? 1L : 0L) + (/*if */(household_demographics_hd_vehicle_count == 3L) ? 1L : 0L));
                (/*if */(l29 > 0L) ? COUNTSTORE_SALES1_E1_2_P_1.addOrDelOnZero(se211.modify(store_sales_ss_hdemo_sk),v108) : (void)0);
              n102 = n102->nxt;
            }
          }
        }COUNTSTORE_SALES1_E1_2_P_3.clear();
        {  // foreach
          const HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627* i103 = static_cast<HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627*>(DATE_DIM.index[0]);
          HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627::IdxNode* n103; 
          DATE_DIM_entry* e103;
        
          for (size_t i = 0; i < i103->size_; i++)
          {
            n103 = i103->buckets_ + i;
            while (n103 && (e103 = n103->obj))
            {
                long store_sales_ss_sold_date_sk = e103->DATE_DIM_D_DATE_SK;
                STRING_TYPE date_dim_d_date_id = e103->DATE_DIM_D_DATE_ID;
                date date_dim_d_date = e103->DATE_DIM_D_DATE;
                long date_dim_d_month_seq = e103->DATE_DIM_D_MONTH_SEQ;
                long date_dim_d_week_seq = e103->DATE_DIM_D_WEEK_SEQ;
                long date_dim_d_quarter_seq = e103->DATE_DIM_D_QUARTER_SEQ;
                long date_dim_d_year = e103->DATE_DIM_D_YEAR;
                long date_dim_d_dow = e103->DATE_DIM_D_DOW;
                long date_dim_d_moy = e103->DATE_DIM_D_MOY;
                long date_dim_d_dom = e103->DATE_DIM_D_DOM;
                long date_dim_d_qoy = e103->DATE_DIM_D_QOY;
                long date_dim_d_fy_year = e103->DATE_DIM_D_FY_YEAR;
                long date_dim_d_fy_quarter_seq = e103->DATE_DIM_D_FY_QUARTER_SEQ;
                long date_dim_d_fy_week_seq = e103->DATE_DIM_D_FY_WEEK_SEQ;
                STRING_TYPE date_dim_d_day_name = e103->DATE_DIM_D_DAY_NAME;
                STRING_TYPE date_dim_d_quarter_name = e103->DATE_DIM_D_QUARTER_NAME;
                STRING_TYPE date_dim_d_holiday = e103->DATE_DIM_D_HOLIDAY;
                STRING_TYPE date_dim_d_weekend = e103->DATE_DIM_D_WEEKEND;
                STRING_TYPE date_dim_d_following_holiday = e103->DATE_DIM_D_FOLLOWING_HOLIDAY;
                long date_dim_d_first_dom = e103->DATE_DIM_D_FIRST_DOM;
                long date_dim_d_last_dom = e103->DATE_DIM_D_LAST_DOM;
                long date_dim_d_same_day_ly = e103->DATE_DIM_D_SAME_DAY_LY;
                long date_dim_d_same_day_lq = e103->DATE_DIM_D_SAME_DAY_LQ;
                STRING_TYPE date_dim_d_current_day = e103->DATE_DIM_D_CURRENT_DAY;
                STRING_TYPE date_dim_d_current_week = e103->DATE_DIM_D_CURRENT_WEEK;
                STRING_TYPE date_dim_d_current_month = e103->DATE_DIM_D_CURRENT_MONTH;
                STRING_TYPE date_dim_d_current_quarter = e103->DATE_DIM_D_CURRENT_QUARTER;
                STRING_TYPE date_dim_d_current_year = e103->DATE_DIM_D_CURRENT_YEAR;
                long v109 = e103->__av;
                (/*if */(((date_dim_d_year == 1999L) || (date_dim_d_year == 2000L) || (date_dim_d_year == 2001L)) && ((date_dim_d_dow == 6L) || (date_dim_d_dow == 0L))) ? COUNTSTORE_SALES1_E1_2_P_3.addOrDelOnZero(se212.modify(store_sales_ss_sold_date_sk),v109) : (void)0);
              n103 = n103->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTSTORE_SALES9_L3_3_DELTA_entry se1;
    COUNTSTORE_SALES9_L2_3_DELTA_entry se2;
    COUNTSTORE_SALES6_DOMAIN1_entry se3;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se4;
    COUNTSTORE_SALES1_DOMAIN1_entry se5;
    COUNT_entry se6;
    COUNTCUSTOMER1_L3_2_entry se7;
    COUNTCUSTOMER1_L2_1_entry se8;
    COUNTCUSTOMER1_L2_2_entry se9;
    COUNTCUSTOMER1_L2_1_entry se10;
    tuple7_SDDSSS_L st1;
    COUNTCUSTOMER_ADDRESS2_entry se11;
    COUNTCUSTOMER1_E1_1_entry se12;
    tuple4_LLS_L st2;
    COUNTCUSTOMER1_E1_1_entry se13;
    COUNTSTORE_SALES1_E1_2_P_1_entry se14;
    COUNTSTORE_SALES1_E1_2_P_2_entry se15;
    COUNTSTORE_SALES1_E1_2_P_3_entry se16;
    tuple4_LLS_L st3;
    COUNTCUSTOMER1_L2_1_entry se17;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se18;
    COUNTCUSTOMER1_L2_1_entry se19;
    COUNTCUSTOMER1_L2_2_entry se20;
    COUNTCUSTOMER1_L2_1_entry se21;
    COUNTCUSTOMER1_L3_2_entry se22;
    tuple7_SDDSSS_L st4;
    COUNTCUSTOMER_ADDRESS2_entry se23;
    COUNTCUSTOMER1_L2_1_entry se24;
    COUNTCUSTOMER1_L2_2_entry se25;
    COUNTSTORE_SALES1_E1_2_P_1_entry se26;
    COUNTSTORE_SALES1_E1_2_P_2_entry se27;
    COUNTSTORE_SALES1_E1_2_P_3_entry se28;
    COUNTSTORE_SALES9_L2_3_DELTA_entry se29;
    COUNTCUSTOMER1_L2_1_entry se30;
    COUNTCUSTOMER1_L2_1_entry se31;
    COUNTCUSTOMER1_L3_2_entry se32;
    COUNTSTORE_SALES1_E1_2_P_1_entry se33;
    COUNTSTORE_SALES1_E1_2_P_2_entry se34;
    COUNTSTORE_SALES1_E1_2_P_3_entry se35;
    COUNTSTORE_SALES9_L3_3_DELTA_entry se36;
    COUNTCUSTOMER1_L2_1_entry se37;
    tuple7_SDDSSS_L st5;
    COUNTCUSTOMER_ADDRESS2_entry se38;
    COUNTCUSTOMER1_E1_1_entry se39;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se40;
    tuple2_S_L st6;
    COUNTCUSTOMER1_L2_1_entry se41;
    COUNTSTORE_SALES1_E1_2_P_1_entry se42;
    COUNTSTORE_SALES1_E1_2_P_2_entry se43;
    COUNTSTORE_SALES1_E1_2_P_3_entry se44;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se45;
    tuple2_S_L st7;
    COUNTCUSTOMER1_L2_1_entry se46;
    COUNTCUSTOMER1_L2_1_entry se47;
    COUNTCUSTOMER1_L2_2_entry se48;
    COUNTCUSTOMER1_L2_1_entry se49;
    COUNTCUSTOMER1_L3_2_entry se50;
    COUNTCUSTOMER_ADDRESS2_entry se51;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se52;
    COUNTCUSTOMER1_L2_1_entry se53;
    COUNTCUSTOMER1_L2_2_entry se54;
    COUNTCUSTOMER1_L2_1_entry se55;
    COUNTCUSTOMER1_L3_2_entry se56;
    COUNTCUSTOMER1_L2_1_entry se57;
    COUNTCUSTOMER_ADDRESS2_entry se58;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se59;
    tuple2_S_L st8;
    COUNTCUSTOMER1_L2_1_entry se60;
    COUNTSTORE_SALES1_E1_2_P_1_entry se61;
    COUNTSTORE_SALES1_E1_2_P_2_entry se62;
    COUNTSTORE_SALES1_E1_2_P_3_entry se63;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se64;
    tuple2_S_L st9;
    COUNTCUSTOMER1_L2_1_entry se65;
    COUNTCUSTOMER1_L2_1_entry se66;
    COUNTCUSTOMER1_L2_2_entry se67;
    COUNTSTORE_SALES1_E1_2_P_1_entry se68;
    COUNTSTORE_SALES1_E1_2_P_2_entry se69;
    COUNTSTORE_SALES1_E1_2_P_3_entry se70;
    COUNTSTORE_SALES9_L2_3_DELTA_entry se71;
    COUNTCUSTOMER1_L2_1_entry se72;
    COUNTCUSTOMER1_L2_1_entry se73;
    COUNTCUSTOMER1_L3_2_entry se74;
    COUNTSTORE_SALES1_E1_2_P_1_entry se75;
    COUNTSTORE_SALES1_E1_2_P_2_entry se76;
    COUNTSTORE_SALES1_E1_2_P_3_entry se77;
    COUNTSTORE_SALES9_L3_3_DELTA_entry se78;
    COUNTCUSTOMER1_L2_1_entry se79;
    COUNTCUSTOMER_ADDRESS2_entry se80;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se81;
    COUNTCUSTOMER1_L2_1_entry se82;
    COUNTCUSTOMER1_L2_2_entry se83;
    COUNTSTORE_SALES1_E1_2_P_1_entry se84;
    COUNTSTORE_SALES1_E1_2_P_2_entry se85;
    COUNTSTORE_SALES1_E1_2_P_3_entry se86;
    COUNTSTORE_SALES9_L2_3_DELTA_entry se87;
    COUNTCUSTOMER1_L2_1_entry se88;
    COUNTCUSTOMER1_L2_1_entry se89;
    COUNTCUSTOMER1_L3_2_entry se90;
    COUNTSTORE_SALES1_E1_2_P_1_entry se91;
    COUNTSTORE_SALES1_E1_2_P_2_entry se92;
    COUNTSTORE_SALES1_E1_2_P_3_entry se93;
    COUNTSTORE_SALES9_L3_3_DELTA_entry se94;
    COUNTCUSTOMER1_L2_1_entry se95;
    COUNTCUSTOMER1_L2_1_entry se96;
    COUNTCUSTOMER_ADDRESS2_entry se97;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se98;
    COUNTSTORE_SALES1_E1_2_P_1_entry se99;
    COUNTSTORE_SALES1_E1_2_P_2_entry se100;
    COUNTSTORE_SALES1_E1_2_P_3_entry se101;
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry se102;
    COUNTSTORE_SALES1_E1_2_P_1_entry se103;
    COUNTSTORE_SALES1_E1_2_P_3_entry se104;
    COUNTCUSTOMER1_E1_1_entry se105;
    COUNTSTORE_SALES1_E1_2_P_1_entry se106;
    COUNTSTORE_SALES1_E1_2_P_2_entry se107;
    COUNTSTORE_SALES1_E1_2_P_3_entry se108;
    COUNTCUSTOMER1_L2_1_entry se109;
    COUNTCUSTOMER1_E1_1STORE1_entry se110;
    COUNTSTORE_SALES1_E1_2_P_1_entry se111;
    COUNTSTORE_SALES1_E1_2_P_3_entry se112;
    COUNTCUSTOMER1_L2_1_entry se113;
    COUNTCUSTOMER1_L2_2_entry se114;
    COUNTSTORE_SALES1_E1_2_P_1_entry se115;
    COUNTSTORE_SALES1_E1_2_P_2_entry se116;
    COUNTSTORE_SALES1_E1_2_P_3_entry se117;
    COUNTCUSTOMER1_L2_2STORE1_entry se118;
    COUNTSTORE_SALES1_E1_2_P_1_entry se119;
    COUNTSTORE_SALES1_E1_2_P_3_entry se120;
    COUNTCUSTOMER1_L3_2_entry se121;
    COUNTSTORE_SALES1_E1_2_P_1_entry se122;
    COUNTSTORE_SALES1_E1_2_P_2_entry se123;
    COUNTSTORE_SALES1_E1_2_P_3_entry se124;
    COUNTCUSTOMER1_L3_2STORE1_entry se125;
    COUNTSTORE_SALES1_E1_2_P_1_entry se126;
    COUNTSTORE_SALES1_E1_2_P_3_entry se127;
    COUNTCUSTOMER1_DELTA_entry se128;
    COUNT_entry se129;
    COUNTCUSTOMER1_L2_1_entry se130;
    COUNTCUSTOMER1_L3_2_entry se131;
    COUNTCUSTOMER1_L2_1_entry se132;
    COUNTCUSTOMER1_L2_2_entry se133;
    COUNTCUSTOMER1_E1_1_entry se134;
    COUNTCUSTOMER1_entry se135;
    COUNTCUSTOMER_ADDRESS1_entry se136;
    COUNTCUSTOMER_ADDRESS2_entry se137;
    COUNTCUSTOMER1_entry se138;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se139;
    COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry se140;
    COUNTCUSTOMER_ADDRESS1_DELTA_entry se141;
    COUNT_entry se142;
    COUNTCUSTOMER1_L2_2_entry se143;
    COUNTCUSTOMER1_L2_1_entry se144;
    COUNTCUSTOMER1_L3_2_entry se145;
    COUNTCUSTOMER1_L2_1_entry se146;
    COUNTCUSTOMER1_E1_1_entry se147;
    COUNTCUSTOMER_ADDRESS1_entry se148;
    COUNTCUSTOMER1_L2_1_entry se149;
    COUNTCUSTOMER1_L2_2_entry se150;
    COUNTCUSTOMER1_L2_1_entry se151;
    COUNTCUSTOMER1_L3_2_entry se152;
    COUNTCUSTOMER1_L2_1_entry se153;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se154;
    COUNTCUSTOMER1_L2_1_entry se155;
    COUNTCUSTOMER1_L2_2_entry se156;
    COUNTCUSTOMER1_L2_1_entry se157;
    COUNTCUSTOMER1_L3_2_entry se158;
    COUNTCUSTOMER1_L2_1_entry se159;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se160;
    COUNTCUSTOMER_ADDRESS1_entry se161;
    COUNTCUSTOMER1_L2_1_entry se162;
    tuple2_L_L st10;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se163;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se164;
    tuple2_L_L st11;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se165;
    COUNTCUSTOMER1_L2_2_entry se166;
    COUNTCUSTOMER1_L2_1_entry se167;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se168;
    COUNTCUSTOMER1_L2_2_entry se169;
    COUNTCUSTOMER1_L3_2_entry se170;
    COUNTCUSTOMER1_L2_1_entry se171;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se172;
    COUNTCUSTOMER1_L3_2_entry se173;
    COUNTCUSTOMER1_L2_1_entry se174;
    tuple2_L_L st12;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se175;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se176;
    tuple2_L_L st13;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se177;
    COUNTCUSTOMER1_L2_2_entry se178;
    COUNTCUSTOMER1_L2_1_entry se179;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se180;
    COUNTCUSTOMER1_L2_2_entry se181;
    COUNTCUSTOMER1_L3_2_entry se182;
    COUNTCUSTOMER1_L2_1_entry se183;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se184;
    COUNTCUSTOMER1_L3_2_entry se185;
    COUNTCUSTOMER_ADDRESS1_entry se186;
    COUNTCUSTOMER_ADDRESS2_entry se187;
    COUNTCUSTOMER_ADDRESS1_entry se188;
    COUNTCUSTOMER1_entry se189;
    COUNTCUSTOMER1_E1_1_entry se190;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se191;
    COUNTCUSTOMER1_E1_1STORE1_entry se192;
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry se193;
    COUNTCUSTOMER1_L2_1_entry se194;
    COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry se195;
    COUNTSTORE_SALES1_E1_2_P_2_entry se196;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se197;
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry se198;
    COUNTCUSTOMER1_E1_1_entry se199;
    COUNTCUSTOMER1_E1_1STORE1_entry se200;
    COUNTCUSTOMER1_L2_2_entry se201;
    COUNTCUSTOMER1_L2_2STORE1_entry se202;
    COUNTCUSTOMER1_L3_2_entry se203;
    COUNTCUSTOMER1_L3_2STORE1_entry se204;
    COUNT_entry se205;
    COUNTCUSTOMER1_L2_1_entry se206;
    COUNTCUSTOMER1_L3_2_entry se207;
    COUNTCUSTOMER1_L2_1_entry se208;
    COUNTCUSTOMER1_L2_2_entry se209;
    COUNTCUSTOMER1_E1_1_entry se210;
    COUNTSTORE_SALES1_E1_2_P_1_entry se211;
    COUNTSTORE_SALES1_E1_2_P_3_entry se212;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    HOUSEHOLD_DEMOGRAPHICS_map HOUSEHOLD_DEMOGRAPHICS;
    COUNTSTORE_SALES1_DOMAIN1_map COUNTSTORE_SALES1_DOMAIN1;
    COUNTSTORE_SALES1_E1_2_DELTA_map COUNTSTORE_SALES1_E1_2_DELTA;
    COUNTSTORE_SALES1_E1_2_P_1_map COUNTSTORE_SALES1_E1_2_P_1;
    COUNTSTORE_SALES1_E1_2_P_2_map COUNTSTORE_SALES1_E1_2_P_2;
    COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA;
    COUNTSTORE_SALES1_E1_2_P_3_map COUNTSTORE_SALES1_E1_2_P_3;
    COUNTSTORE_SALES6_DOMAIN1_map COUNTSTORE_SALES6_DOMAIN1;
    COUNTSTORE_SALES9_L2_3_DELTA_map COUNTSTORE_SALES9_L2_3_DELTA;
    COUNTSTORE_SALES9_L3_3_DELTA_map COUNTSTORE_SALES9_L3_3_DELTA;
    COUNTCUSTOMER_ADDRESS1_DELTA_map COUNTCUSTOMER_ADDRESS1_DELTA;
    COUNTCUSTOMER_ADDRESS1_map COUNTCUSTOMER_ADDRESS1;
    COUNTCUSTOMER_ADDRESS2_DOMAIN1_map COUNTCUSTOMER_ADDRESS2_DOMAIN1;
    COUNTCUSTOMER_ADDRESS2_map COUNTCUSTOMER_ADDRESS2;
    COUNTCUSTOMER_ADDRESS2_E1_2_map COUNTCUSTOMER_ADDRESS2_E1_2;
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map COUNTCUSTOMER_ADDRESS2_E1_2STORE1;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map COUNTCUSTOMER_ADDRESS6_E1_3_DELTA;
    COUNTCUSTOMER1_DELTA_map COUNTCUSTOMER1_DELTA;
    COUNTCUSTOMER1_map COUNTCUSTOMER1;
    COUNTCUSTOMER1_E1_1_map COUNTCUSTOMER1_E1_1;
    COUNTCUSTOMER1_E1_1STORE1_map COUNTCUSTOMER1_E1_1STORE1;
    COUNTCUSTOMER1_L2_1_map COUNTCUSTOMER1_L2_1;
    COUNTCUSTOMER1_L2_2_map COUNTCUSTOMER1_L2_2;
    COUNTCUSTOMER1_L2_2STORE1_map COUNTCUSTOMER1_L2_2STORE1;
    COUNTCUSTOMER1_L3_2_map COUNTCUSTOMER1_L3_2;
    COUNTCUSTOMER1_L3_2STORE1_map COUNTCUSTOMER1_L3_2STORE1;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_CUSTOMER_ADDRESS_map DELTA_CUSTOMER_ADDRESS;
    DELTA_STORE_map DELTA_STORE;
    MultiHashMap<tuple7_SDDSSS_L,long,HashIndex<tuple7_SDDSSS_L,long> > _c1;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c4;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > _c6;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c3;
    MultiHashMap<tuple4_LLS_L,long,HashIndex<tuple4_LLS_L,long> > _c2;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > _c5;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c5;
  
  };

}
