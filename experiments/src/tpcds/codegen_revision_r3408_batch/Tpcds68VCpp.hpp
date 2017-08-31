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
    STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CURRENT_ADDR_CA_CITY; STRING_TYPE DN_BOUGHT_CITY; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE DN_EXTENDED_PRICE; DOUBLE_TYPE DN_EXTENDED_TAX; DOUBLE_TYPE DN_LIST_PRICE; long __av; 
    explicit COUNT_entry() { /*CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_FIRST_NAME = ""; CURRENT_ADDR_CA_CITY = ""; DN_BOUGHT_CITY = ""; DN_SS_TICKET_NUMBER = 0L; DN_EXTENDED_PRICE = 0.0; DN_EXTENDED_TAX = 0.0; DN_LIST_PRICE = 0.0; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const long c8) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CURRENT_ADDR_CA_CITY = c2; DN_BOUGHT_CITY = c3; DN_SS_TICKET_NUMBER = c4; DN_EXTENDED_PRICE = c5; DN_EXTENDED_TAX = c6; DN_LIST_PRICE = c7; __av = c8; }
    COUNT_entry(const COUNT_entry& other) : CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CURRENT_ADDR_CA_CITY( other.CURRENT_ADDR_CA_CITY ), DN_BOUGHT_CITY( other.DN_BOUGHT_CITY ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), DN_EXTENDED_PRICE( other.DN_EXTENDED_PRICE ), DN_EXTENDED_TAX( other.DN_EXTENDED_TAX ), DN_LIST_PRICE( other.DN_LIST_PRICE ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CURRENT_ADDR_CA_CITY = c2; DN_BOUGHT_CITY = c3; DN_SS_TICKET_NUMBER = c4; DN_EXTENDED_PRICE = c5; DN_EXTENDED_TAX = c6; DN_LIST_PRICE = c7;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, DN_EXTENDED_PRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_EXTENDED_TAX);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_LIST_PRICE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CURRENT_ADDR_CA_CITY);
      hash_combine(h, e.DN_BOUGHT_CITY);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      hash_combine(h, e.DN_EXTENDED_PRICE);
      hash_combine(h, e.DN_EXTENDED_TAX);
      hash_combine(h, e.DN_LIST_PRICE);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CURRENT_ADDR_CA_CITY == y.CURRENT_ADDR_CA_CITY && x.DN_BOUGHT_CITY == y.DN_BOUGHT_CITY && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER && x.DN_EXTENDED_PRICE == y.DN_EXTENDED_PRICE && x.DN_EXTENDED_TAX == y.DN_EXTENDED_TAX && x.DN_LIST_PRICE == y.DN_LIST_PRICE;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey01234567_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey01234567_idxfn,true> HashIndex_COUNT_map_01234567;
  
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
  
  struct COUNTSTORE_SALES9_L4_3_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_HDEMO_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE_SALES9_L4_3_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_HDEMO_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE_SALES9_L4_3_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5; __av = c6; }
    COUNTSTORE_SALES9_L4_3_DELTA_entry(const COUNTSTORE_SALES9_L4_3_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_HDEMO_SK( other.STORE_SALES_SS_HDEMO_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES9_L4_3_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3, const long c4, const long c5) { STORE_SALES_SS_SOLD_DATE_SK = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_HDEMO_SK = c2; STORE_SALES_SS_ADDR_SK = c3; STORE_SALES_SS_STORE_SK = c4; DN_SS_TICKET_NUMBER = c5;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES9_L4_3_DELTA_entry& modify135(const long c1, const long c3, const long c5) { CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c3; DN_SS_TICKET_NUMBER = c5;  return *this; }
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
  struct COUNTSTORE_SALES9_L4_3_DELTA_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L4_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_HDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L4_3_DELTA_entry& x, const COUNTSTORE_SALES9_L4_3_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_HDEMO_SK == y.STORE_SALES_SS_HDEMO_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES9_L4_3_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES9_L4_3_DELTA_entry& x, const COUNTSTORE_SALES9_L4_3_DELTA_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES9_L4_3_DELTA_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE_SALES9_L4_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L4_3_DELTA_mapkey012345_idxfn,true>,
    HashIndex<COUNTSTORE_SALES9_L4_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn,false>
  > COUNTSTORE_SALES9_L4_3_DELTA_map;
  typedef HashIndex<COUNTSTORE_SALES9_L4_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L4_3_DELTA_mapkey012345_idxfn,true> HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_012345;
  typedef HashIndex<COUNTSTORE_SALES9_L4_3_DELTA_entry,DOUBLE_TYPE,COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn,false> HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135;
  
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
  
  struct COUNTCUSTOMER1_L4_2_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L4_2_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L4_2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTCUSTOMER1_L4_2_entry(const COUNTCUSTOMER1_L4_2_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L4_2_entry& modify(const long c0, const long c1, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; DN_SS_TICKET_NUMBER = c2;  return *this; }
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
  struct COUNTCUSTOMER1_L4_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L4_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L4_2_entry& x, const COUNTCUSTOMER1_L4_2_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L4_2_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L4_2_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_2_mapkey012_idxfn,true>
  > COUNTCUSTOMER1_L4_2_map;
  typedef HashIndex<COUNTCUSTOMER1_L4_2_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_2_mapkey012_idxfn,true> HashIndex_COUNTCUSTOMER1_L4_2_map_012;
  
  struct COUNTCUSTOMER1_L4_2STORE1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long STORE_SALES_SS_STORE_SK; long DN_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L4_2STORE1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L4_2STORE1_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTCUSTOMER1_L4_2STORE1_entry(const COUNTCUSTOMER1_L4_2STORE1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L4_2STORE1_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; STORE_SALES_SS_STORE_SK = c2; DN_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_L4_2STORE1_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
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
  struct COUNTCUSTOMER1_L4_2STORE1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L4_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L4_2STORE1_entry& x, const COUNTCUSTOMER1_L4_2STORE1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_L4_2STORE1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L4_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L4_2STORE1_entry& x, const COUNTCUSTOMER1_L4_2STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L4_2STORE1_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L4_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_2STORE1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_L4_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_2STORE1_mapkey2_idxfn,false>
  > COUNTCUSTOMER1_L4_2STORE1_map;
  typedef HashIndex<COUNTCUSTOMER1_L4_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_2STORE1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_L4_2STORE1_map_0123;
  typedef HashIndex<COUNTCUSTOMER1_L4_2STORE1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_2STORE1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER1_L4_2STORE1_map_2;
  
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
  struct tuple8_SDDDSSS_L {
    STRING_TYPE _1; DOUBLE_TYPE _2; DOUBLE_TYPE _3; DOUBLE_TYPE _4; STRING_TYPE _5; STRING_TYPE _6; STRING_TYPE _7; long __av;
    explicit tuple8_SDDDSSS_L() { }
    explicit tuple8_SDDDSSS_L(const STRING_TYPE& c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const STRING_TYPE& c7, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; _6 = c6; _7 = c7; __av = c__av;}
    int operator==(const tuple8_SDDDSSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5) && (this->_6==rhs._6) && (this->_7==rhs._7)); }
    FORCE_INLINE tuple8_SDDDSSS_L& modify(const STRING_TYPE& c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; _6 = c5; _7 = c6; __av = c__av; return *this; }
    static bool equals(const tuple8_SDDDSSS_L &x, const tuple8_SDDDSSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5) && (x._6==y._6) && (x._7==y._7)); }
    static long hash(const tuple8_SDDDSSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      hash_combine(h, e._6);
      hash_combine(h, e._7);
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
      c2 = STRING_TYPE("Riverside");
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

        COUNTSTORE_SALES9_L4_3_DELTA.clear();
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
                DOUBLE_TYPE store_sales_ss_ext_sales_price = DELTA_STORE_SALES.ss_ext_sales_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_wholesale_cost = DELTA_STORE_SALES.ss_ext_wholesale_cost[i];
                DOUBLE_TYPE store_sales_ss_ext_list_price = DELTA_STORE_SALES.ss_ext_list_price[i];
                DOUBLE_TYPE store_sales_ss_ext_tax = DELTA_STORE_SALES.ss_ext_tax[i];
                // DOUBLE_TYPE store_sales_ss_coupon_amt = DELTA_STORE_SALES.ss_coupon_amt[i];
                // DOUBLE_TYPE store_sales_ss_net_paid = DELTA_STORE_SALES.ss_net_paid[i];
                // DOUBLE_TYPE store_sales_ss_net_paid_inc_tax = DELTA_STORE_SALES.ss_net_paid_inc_tax[i];
                // DOUBLE_TYPE store_sales_ss_net_profit = DELTA_STORE_SALES.ss_net_profit[i];
                long v1 = 1L;
                COUNTSTORE_SALES9_L4_3_DELTA.addOrDelOnZero(se1.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(v1 * store_sales_ss_ext_sales_price));
                long v2 = 1L;
                COUNTSTORE_SALES9_L3_3_DELTA.addOrDelOnZero(se2.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(v2 * store_sales_ss_ext_list_price));
                long v3 = 1L;
                COUNTSTORE_SALES9_L2_3_DELTA.addOrDelOnZero(se3.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(v3 * store_sales_ss_ext_tax));
                long v4 = 1L;
                COUNTSTORE_SALES6_DOMAIN1.addOrDelOnZero(se4.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number),(v4 != 0 ? 1L : 0L));
                long v5 = 1L;
                COUNTSTORE_SALES1_E1_2_DELTA.addOrDelOnZero(se5.modify(store_sales_ss_sold_date_sk,customer_c_customer_sk,store_sales_ss_hdemo_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),v5);
                long v6 = 1L;
                COUNTSTORE_SALES1_DOMAIN1.addOrDelOnZero(se6.modify(store_sales_ss_ticket_number),(v6 != 0 ? 1L : 0L));
          }
        }

        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0* i7 = static_cast<HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0*>(COUNTSTORE_SALES1_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES1_DOMAIN1_map_0::IdxNode* n7; 
          COUNTSTORE_SALES1_DOMAIN1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long dn_ss_ticket_number = e7->DN_SS_TICKET_NUMBER;
                long v7 = e7->__av;
                _c1.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i8 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h2 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se15.modify2(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n8 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i8->slice(se15, h2));
                  COUNTCUSTOMER1_E1_1_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      long customer_c_customer_sk = e8->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e8->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE dn_bought_city = e8->DN_BOUGHT_CITY;
                      long v9 = e8->__av;
                      DOUBLE_TYPE l1 = (COUNTCUSTOMER1_L4_2.getValueOrDefault(se8.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se9.modify(store_sales_ss_addr_sk,dn_bought_city)));
                      DOUBLE_TYPE l2 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se10.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se11.modify(store_sales_ss_addr_sk,dn_bought_city)));
                      DOUBLE_TYPE l3 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se12.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se13.modify(store_sales_ss_addr_sk,dn_bought_city)));
                      { //slice 
                        const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i9 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                        const HASH_RES_t h1 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se14.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n9 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i9->slice(se14, h1));
                        COUNTCUSTOMER_ADDRESS2_entry* e9;
                       
                        if (n9 && (e9 = n9->obj)) {
                          do {                
                            STRING_TYPE customer_c_first_name = e9->CUSTOMER_C_FIRST_NAME;
                            STRING_TYPE customer_c_last_name = e9->CUSTOMER_C_LAST_NAME;
                            STRING_TYPE current_addr_ca_city = e9->CURRENT_ADDR_CA_CITY;
                            long v10 = e9->__av;
                            (/*if */(current_addr_ca_city != dn_bought_city) ? _c1.addOrDelOnZero(st1.modify(dn_bought_city,l3,l2,l1,customer_c_first_name,customer_c_last_name,current_addr_ca_city,(((v9 != 0 ? 1L : 0L) * v10) * -2L)), (((v9 != 0 ? 1L : 0L) * v10) * -2L)) : (void)0);
                            n9 = n9->nxt;
                          } while (n9 && (e9 = n9->obj) && h1 == n9->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se14, *e9)); 
                        }
                      }
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h2 == n8->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se15, *e8)); 
                  }
                }_c2.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i10 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h3 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se16.modify2(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n10 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i10->slice(se16, h3));
                  COUNTCUSTOMER1_E1_1_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      long customer_c_customer_sk = e10->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e10->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE dn_bought_city = e10->DN_BOUGHT_CITY;
                      long v12 = e10->__av;
                      _c2.addOrDelOnZero(st2.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_bought_city,v12), v12);
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h3 == n10->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se16, *e10)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5* i11 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5*>(COUNTSTORE_SALES1_E1_2_DELTA.index[1]);
                  const HASH_RES_t h5 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn::hash(se21.modify5(dn_ss_ticket_number));
                  HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5::IdxNode* n11 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_5::IdxNode*>(i11->slice(se21, h5));
                  COUNTSTORE_SALES1_E1_2_DELTA_entry* e11;
                 
                  if (n11 && (e11 = n11->obj)) {
                    do {                
                      long store_sales_ss_sold_date_sk = e11->STORE_SALES_SS_SOLD_DATE_SK;
                      long customer_c_customer_sk = e11->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_hdemo_sk = e11->STORE_SALES_SS_HDEMO_SK;
                      long store_sales_ss_addr_sk = e11->STORE_SALES_SS_ADDR_SK;
                      long store_sales_ss_store_sk = e11->STORE_SALES_SS_STORE_SK;
                      long v13 = e11->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i12 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h4 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se20.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n12 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i12->slice(se20, h4));
                        COUNTCUSTOMER1_L2_1_entry* e12;
                       
                        if (n12 && (e12 = n12->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e12->DN_BOUGHT_CITY;
                            long v14 = e12->__av;
                            _c2.addOrDelOnZero(st3.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_bought_city,(v13 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se17.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se18.modify(store_sales_ss_store_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se19.modify(store_sales_ss_sold_date_sk)) * v14))))), (v13 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se17.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se18.modify(store_sales_ss_store_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se19.modify(store_sales_ss_sold_date_sk)) * v14)))));
                            n12 = n12->nxt;
                          } while (n12 && (e12 = n12->obj) && h4 == n12->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se20, *e12)); 
                        }
                      }
                      n11 = n11->nxt;
                    } while (n11 && (e11 = n11->obj) && h5 == n11->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey5_idxfn::equals(se21, *e11)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_LLS_L, long>* i13 = static_cast<HashIndex<tuple4_LLS_L, long>*>(_c2.index[0]);
                  HashIndex<tuple4_LLS_L, long>::IdxNode* n13; 
                  tuple4_LLS_L* e13;
                
                  for (size_t i = 0; i < i13->size_; i++)
                  {
                    n13 = i13->buckets_ + i;
                    while (n13 && (e13 = n13->obj))
                    {
                      long customer_c_customer_sk = e13->_1;
                      long store_sales_ss_addr_sk = e13->_2;
                      STRING_TYPE dn_bought_city = e13->_3;  
                      long v15 = e13->__av; 
                    DOUBLE_TYPE l4 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se22.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se23.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                    DOUBLE_TYPE l5 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se24.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se25.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                    DOUBLE_TYPE l6 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se26.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se27.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                    { //slice 
                      const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i14 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                      const HASH_RES_t h6 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se28.modify0(customer_c_customer_sk));
                      HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n14 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i14->slice(se28, h6));
                      COUNTCUSTOMER_ADDRESS2_entry* e14;
                     
                      if (n14 && (e14 = n14->obj)) {
                        do {                
                          STRING_TYPE customer_c_first_name = e14->CUSTOMER_C_FIRST_NAME;
                          STRING_TYPE customer_c_last_name = e14->CUSTOMER_C_LAST_NAME;
                          STRING_TYPE current_addr_ca_city = e14->CURRENT_ADDR_CA_CITY;
                          long v16 = e14->__av;
                          (/*if */(current_addr_ca_city != dn_bought_city) ? _c1.addOrDelOnZero(st4.modify(dn_bought_city,l4,l5,l6,customer_c_first_name,customer_c_last_name,current_addr_ca_city,((v15 != 0 ? 1L : 0L) * v16)), ((v15 != 0 ? 1L : 0L) * v16)) : (void)0);
                          n14 = n14->nxt;
                        } while (n14 && (e14 = n14->obj) && h6 == n14->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se28, *e14)); 
                      }
                    }      
                      n13 = n13->nxt;
                    }
                  }
                }{ //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i15 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[1]);
                  const HASH_RES_t h11 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se51.modify2(dn_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n15 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i15->slice(se51, h11));
                  COUNTCUSTOMER1_E1_1_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      long customer_c_customer_sk = e15->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e15->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE dn_bought_city = e15->DN_BOUGHT_CITY;
                      long v17 = e15->__av;
                      DOUBLE_TYPE agg1 = 0.0;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135* i16 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135*>(COUNTSTORE_SALES9_L2_3_DELTA.index[1]);
                        const HASH_RES_t h7 = COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::hash(se34.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode* n16 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode*>(i16->slice(se34, h7));
                        COUNTSTORE_SALES9_L2_3_DELTA_entry* e16;
                       
                        if (n16 && (e16 = n16->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e16->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e16->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e16->STORE_SALES_SS_STORE_SK;
                            DOUBLE_TYPE v18 = e16->__av;
                            agg1 += (v18 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se31.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se32.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se33.modify(store_sales_ss_sold_date_sk)))));
                            n16 = n16->nxt;
                          } while (n16 && (e16 = n16->obj) && h7 == n16->hash &&  COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::equals(se34, *e16)); 
                        }
                      }DOUBLE_TYPE l7 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se29.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se30.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg1 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se35.modify(store_sales_ss_addr_sk,dn_bought_city))));
                      DOUBLE_TYPE agg2 = 0.0;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135* i17 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135*>(COUNTSTORE_SALES9_L3_3_DELTA.index[1]);
                        const HASH_RES_t h8 = COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::hash(se41.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode* n17 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode*>(i17->slice(se41, h8));
                        COUNTSTORE_SALES9_L3_3_DELTA_entry* e17;
                       
                        if (n17 && (e17 = n17->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e17->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e17->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e17->STORE_SALES_SS_STORE_SK;
                            DOUBLE_TYPE v19 = e17->__av;
                            agg2 += (v19 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se38.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se39.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se40.modify(store_sales_ss_sold_date_sk)))));
                            n17 = n17->nxt;
                          } while (n17 && (e17 = n17->obj) && h8 == n17->hash &&  COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::equals(se41, *e17)); 
                        }
                      }DOUBLE_TYPE l8 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se36.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se37.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg2 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se42.modify(store_sales_ss_addr_sk,dn_bought_city))));
                      DOUBLE_TYPE agg3 = 0.0;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135* i18 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135*>(COUNTSTORE_SALES9_L4_3_DELTA.index[1]);
                        const HASH_RES_t h9 = COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn::hash(se48.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135::IdxNode* n18 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135::IdxNode*>(i18->slice(se48, h9));
                        COUNTSTORE_SALES9_L4_3_DELTA_entry* e18;
                       
                        if (n18 && (e18 = n18->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e18->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e18->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e18->STORE_SALES_SS_STORE_SK;
                            DOUBLE_TYPE v20 = e18->__av;
                            agg3 += (v20 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se45.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se46.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se47.modify(store_sales_ss_sold_date_sk)))));
                            n18 = n18->nxt;
                          } while (n18 && (e18 = n18->obj) && h9 == n18->hash &&  COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn::equals(se48, *e18)); 
                        }
                      }DOUBLE_TYPE l9 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se43.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se44.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg3 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se49.modify(store_sales_ss_addr_sk,dn_bought_city))));
                      { //slice 
                        const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i19 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                        const HASH_RES_t h10 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se50.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n19 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i19->slice(se50, h10));
                        COUNTCUSTOMER_ADDRESS2_entry* e19;
                       
                        if (n19 && (e19 = n19->obj)) {
                          do {                
                            STRING_TYPE customer_c_first_name = e19->CUSTOMER_C_FIRST_NAME;
                            STRING_TYPE customer_c_last_name = e19->CUSTOMER_C_LAST_NAME;
                            STRING_TYPE current_addr_ca_city = e19->CURRENT_ADDR_CA_CITY;
                            long v21 = e19->__av;
                            (/*if */(current_addr_ca_city != dn_bought_city) ? _c1.addOrDelOnZero(st5.modify(dn_bought_city,l7,l8,l9,customer_c_first_name,customer_c_last_name,current_addr_ca_city,((v17 != 0 ? 1L : 0L) * v21)), ((v17 != 0 ? 1L : 0L) * v21)) : (void)0);
                            n19 = n19->nxt;
                          } while (n19 && (e19 = n19->obj) && h10 == n19->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se50, *e19)); 
                        }
                      }
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h11 == n15->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se51, *e15)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple8_SDDDSSS_L, long>* i20 = static_cast<HashIndex<tuple8_SDDDSSS_L, long>*>(_c1.index[0]);
                  HashIndex<tuple8_SDDDSSS_L, long>::IdxNode* n20; 
                  tuple8_SDDDSSS_L* e20;
                
                  for (size_t i = 0; i < i20->size_; i++)
                  {
                    n20 = i20->buckets_ + i;
                    while (n20 && (e20 = n20->obj))
                    {
                      STRING_TYPE dn_bought_city = e20->_1;
                      DOUBLE_TYPE dn_extended_tax = e20->_2;
                      DOUBLE_TYPE dn_list_price = e20->_3;
                      DOUBLE_TYPE dn_extended_price = e20->_4;
                      STRING_TYPE customer_c_first_name = e20->_5;
                      STRING_TYPE customer_c_last_name = e20->_6;
                      STRING_TYPE current_addr_ca_city = e20->_7;  
                      long v22 = e20->__av; 
                    COUNT.addOrDelOnZero(se7.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,dn_extended_price,dn_extended_tax,dn_list_price),((v7 != 0 ? 1L : 0L) * v22));      
                      n20 = n20->nxt;
                    }
                  }
                }
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i21 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n21; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long customer_c_customer_sk = e21->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e21->STORE_SALES_SS_ADDR_SK;
                long dn_ss_ticket_number = e21->DN_SS_TICKET_NUMBER;
                long v23 = e21->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i22 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h15 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se65.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n22 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i22->slice(se65, h15));
                  COUNTCUSTOMER_ADDRESS2_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e22->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e22->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e22->CURRENT_ADDR_CA_CITY;
                      long v24 = e22->__av;
                      _c3.clear();
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i23 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h12 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se53.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n23 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i23->slice(se53, h12));
                        COUNTCUSTOMER1_L2_1_entry* e23;
                       
                        if (n23 && (e23 = n23->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e23->DN_BOUGHT_CITY;
                            long v26 = e23->__av;
                            _c3.addOrDelOnZero(st6.modify(dn_bought_city,(COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se52.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v26)), (COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se52.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v26));
                            n23 = n23->nxt;
                          } while (n23 && (e23 = n23->obj) && h12 == n23->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se53, *e23)); 
                        }
                      }long agg4 = 0L;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135* i24 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135*>(COUNTSTORE_SALES1_E1_2_DELTA.index[2]);
                        const HASH_RES_t h13 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::hash(se57.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode* n24 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode*>(i24->slice(se57, h13));
                        COUNTSTORE_SALES1_E1_2_DELTA_entry* e24;
                       
                        if (n24 && (e24 = n24->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e24->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e24->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e24->STORE_SALES_SS_STORE_SK;
                            long v27 = e24->__av;
                            agg4 += (v27 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se54.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se55.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se56.modify(store_sales_ss_sold_date_sk)))));
                            n24 = n24->nxt;
                          } while (n24 && (e24 = n24->obj) && h13 == n24->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::equals(se57, *e24)); 
                        }
                      }{ //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i25 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h14 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se58.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n25 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i25->slice(se58, h14));
                        COUNTCUSTOMER1_L2_1_entry* e25;
                       
                        if (n25 && (e25 = n25->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e25->DN_BOUGHT_CITY;
                            long v28 = e25->__av;
                            _c3.addOrDelOnZero(st7.modify(dn_bought_city,(agg4 * v28)), (agg4 * v28));
                            n25 = n25->nxt;
                          } while (n25 && (e25 = n25->obj) && h14 == n25->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se58, *e25)); 
                        }
                      }{  // temp foreach
                        const HashIndex<tuple2_S_L, long>* i26 = static_cast<HashIndex<tuple2_S_L, long>*>(_c3.index[0]);
                        HashIndex<tuple2_S_L, long>::IdxNode* n26; 
                        tuple2_S_L* e26;
                      
                        for (size_t i = 0; i < i26->size_; i++)
                        {
                          n26 = i26->buckets_ + i;
                          while (n26 && (e26 = n26->obj))
                          {
                            STRING_TYPE dn_bought_city = e26->_1;  
                            long v29 = e26->__av; 
                          DOUBLE_TYPE l10 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se59.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se60.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                          DOUBLE_TYPE l11 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se61.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se62.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                          DOUBLE_TYPE l12 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se63.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se64.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                          (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se7.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l12,l10,l11),(((v23 != 0 ? 1L : 0L) * (v24 * (v29 != 0 ? 1L : 0L))) * -1L)) : (void)0);      
                            n26 = n26->nxt;
                          }
                        }
                      }
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h15 == n22->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se65, *e22)); 
                  }
                }
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i27 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n27; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                long customer_c_customer_sk = e27->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e27->STORE_SALES_SS_ADDR_SK;
                long dn_ss_ticket_number = e27->DN_SS_TICKET_NUMBER;
                long v30 = e27->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i28 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h17 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se74.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n28 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i28->slice(se74, h17));
                  COUNTCUSTOMER_ADDRESS2_entry* e28;
                 
                  if (n28 && (e28 = n28->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e28->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e28->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e28->CURRENT_ADDR_CA_CITY;
                      long v31 = e28->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i29 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h16 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se73.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n29 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i29->slice(se73, h16));
                        COUNTCUSTOMER1_L2_1_entry* e29;
                       
                        if (n29 && (e29 = n29->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e29->DN_BOUGHT_CITY;
                            long v32 = e29->__av;
                            DOUBLE_TYPE l13 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se67.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se68.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            DOUBLE_TYPE l14 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se69.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se70.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            DOUBLE_TYPE l15 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se71.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se72.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se7.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l15,l13,l14),((v30 != 0 ? 1L : 0L) * (v31 * ((COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se66.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v32) != 0 ? 1L : 0L)))) : (void)0);
                            n29 = n29->nxt;
                          } while (n29 && (e29 = n29->obj) && h16 == n29->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se73, *e29)); 
                        }
                      }
                      n28 = n28->nxt;
                    } while (n28 && (e28 = n28->obj) && h17 == n28->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se74, *e28)); 
                  }
                }
              n27 = n27->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i30 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n30; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long customer_c_customer_sk = e30->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e30->STORE_SALES_SS_ADDR_SK;
                long dn_ss_ticket_number = e30->DN_SS_TICKET_NUMBER;
                long v33 = e30->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i31 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h24 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se103.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n31 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i31->slice(se103, h24));
                  COUNTCUSTOMER_ADDRESS2_entry* e31;
                 
                  if (n31 && (e31 = n31->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e31->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e31->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e31->CURRENT_ADDR_CA_CITY;
                      long v34 = e31->__av;
                      _c4.clear();
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i32 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h18 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se76.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n32 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i32->slice(se76, h18));
                        COUNTCUSTOMER1_L2_1_entry* e32;
                       
                        if (n32 && (e32 = n32->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e32->DN_BOUGHT_CITY;
                            long v36 = e32->__av;
                            _c4.addOrDelOnZero(st8.modify(dn_bought_city,(COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se75.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v36)), (COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se75.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v36));
                            n32 = n32->nxt;
                          } while (n32 && (e32 = n32->obj) && h18 == n32->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se76, *e32)); 
                        }
                      }long agg5 = 0L;
                      { //slice 
                        const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135* i33 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135*>(COUNTSTORE_SALES1_E1_2_DELTA.index[2]);
                        const HASH_RES_t h19 = COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::hash(se80.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                        HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode* n33 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_135::IdxNode*>(i33->slice(se80, h19));
                        COUNTSTORE_SALES1_E1_2_DELTA_entry* e33;
                       
                        if (n33 && (e33 = n33->obj)) {
                          do {                
                            long store_sales_ss_sold_date_sk = e33->STORE_SALES_SS_SOLD_DATE_SK;
                            long store_sales_ss_hdemo_sk = e33->STORE_SALES_SS_HDEMO_SK;
                            long store_sales_ss_store_sk = e33->STORE_SALES_SS_STORE_SK;
                            long v37 = e33->__av;
                            agg5 += (v37 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se77.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se78.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se79.modify(store_sales_ss_sold_date_sk)))));
                            n33 = n33->nxt;
                          } while (n33 && (e33 = n33->obj) && h19 == n33->hash &&  COUNTSTORE_SALES1_E1_2_DELTA_mapkey135_idxfn::equals(se80, *e33)); 
                        }
                      }{ //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i34 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h20 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se81.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n34 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i34->slice(se81, h20));
                        COUNTCUSTOMER1_L2_1_entry* e34;
                       
                        if (n34 && (e34 = n34->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e34->DN_BOUGHT_CITY;
                            long v38 = e34->__av;
                            _c4.addOrDelOnZero(st9.modify(dn_bought_city,(agg5 * v38)), (agg5 * v38));
                            n34 = n34->nxt;
                          } while (n34 && (e34 = n34->obj) && h20 == n34->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se81, *e34)); 
                        }
                      }{  // temp foreach
                        const HashIndex<tuple2_S_L, long>* i35 = static_cast<HashIndex<tuple2_S_L, long>*>(_c4.index[0]);
                        HashIndex<tuple2_S_L, long>::IdxNode* n35; 
                        tuple2_S_L* e35;
                      
                        for (size_t i = 0; i < i35->size_; i++)
                        {
                          n35 = i35->buckets_ + i;
                          while (n35 && (e35 = n35->obj))
                          {
                            STRING_TYPE dn_bought_city = e35->_1;  
                            long v39 = e35->__av; 
                          DOUBLE_TYPE agg6 = 0.0;
                          { //slice 
                            const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135* i36 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135*>(COUNTSTORE_SALES9_L2_3_DELTA.index[1]);
                            const HASH_RES_t h21 = COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::hash(se87.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                            HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode* n36 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode*>(i36->slice(se87, h21));
                            COUNTSTORE_SALES9_L2_3_DELTA_entry* e36;
                           
                            if (n36 && (e36 = n36->obj)) {
                              do {                
                                long store_sales_ss_sold_date_sk = e36->STORE_SALES_SS_SOLD_DATE_SK;
                                long store_sales_ss_hdemo_sk = e36->STORE_SALES_SS_HDEMO_SK;
                                long store_sales_ss_store_sk = e36->STORE_SALES_SS_STORE_SK;
                                DOUBLE_TYPE v40 = e36->__av;
                                agg6 += (v40 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se84.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se85.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se86.modify(store_sales_ss_sold_date_sk)))));
                                n36 = n36->nxt;
                              } while (n36 && (e36 = n36->obj) && h21 == n36->hash &&  COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::equals(se87, *e36)); 
                            }
                          }DOUBLE_TYPE l16 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se82.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se83.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg6 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se88.modify(store_sales_ss_addr_sk,dn_bought_city))));
                          DOUBLE_TYPE agg7 = 0.0;
                          { //slice 
                            const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135* i37 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135*>(COUNTSTORE_SALES9_L3_3_DELTA.index[1]);
                            const HASH_RES_t h22 = COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::hash(se94.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                            HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode* n37 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode*>(i37->slice(se94, h22));
                            COUNTSTORE_SALES9_L3_3_DELTA_entry* e37;
                           
                            if (n37 && (e37 = n37->obj)) {
                              do {                
                                long store_sales_ss_sold_date_sk = e37->STORE_SALES_SS_SOLD_DATE_SK;
                                long store_sales_ss_hdemo_sk = e37->STORE_SALES_SS_HDEMO_SK;
                                long store_sales_ss_store_sk = e37->STORE_SALES_SS_STORE_SK;
                                DOUBLE_TYPE v41 = e37->__av;
                                agg7 += (v41 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se91.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se92.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se93.modify(store_sales_ss_sold_date_sk)))));
                                n37 = n37->nxt;
                              } while (n37 && (e37 = n37->obj) && h22 == n37->hash &&  COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::equals(se94, *e37)); 
                            }
                          }DOUBLE_TYPE l17 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se89.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se90.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg7 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se95.modify(store_sales_ss_addr_sk,dn_bought_city))));
                          DOUBLE_TYPE agg8 = 0.0;
                          { //slice 
                            const HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135* i38 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135*>(COUNTSTORE_SALES9_L4_3_DELTA.index[1]);
                            const HASH_RES_t h23 = COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn::hash(se101.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                            HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135::IdxNode* n38 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135::IdxNode*>(i38->slice(se101, h23));
                            COUNTSTORE_SALES9_L4_3_DELTA_entry* e38;
                           
                            if (n38 && (e38 = n38->obj)) {
                              do {                
                                long store_sales_ss_sold_date_sk = e38->STORE_SALES_SS_SOLD_DATE_SK;
                                long store_sales_ss_hdemo_sk = e38->STORE_SALES_SS_HDEMO_SK;
                                long store_sales_ss_store_sk = e38->STORE_SALES_SS_STORE_SK;
                                DOUBLE_TYPE v42 = e38->__av;
                                agg8 += (v42 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se98.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se99.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se100.modify(store_sales_ss_sold_date_sk)))));
                                n38 = n38->nxt;
                              } while (n38 && (e38 = n38->obj) && h23 == n38->hash &&  COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn::equals(se101, *e38)); 
                            }
                          }DOUBLE_TYPE l18 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se96.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se97.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg8 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se102.modify(store_sales_ss_addr_sk,dn_bought_city))));
                          (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se7.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l18,l16,l17),((v33 != 0 ? 1L : 0L) * (v34 * (v39 != 0 ? 1L : 0L)))) : (void)0);      
                            n35 = n35->nxt;
                          }
                        }
                      }
                      n31 = n31->nxt;
                    } while (n31 && (e31 = n31->obj) && h24 == n31->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se103, *e31)); 
                  }
                }
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012* i39 = static_cast<HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012*>(COUNTSTORE_SALES6_DOMAIN1.index[0]);
          HashIndex_COUNTSTORE_SALES6_DOMAIN1_map_012::IdxNode* n39; 
          COUNTSTORE_SALES6_DOMAIN1_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long customer_c_customer_sk = e39->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_addr_sk = e39->STORE_SALES_SS_ADDR_SK;
                long dn_ss_ticket_number = e39->DN_SS_TICKET_NUMBER;
                long v43 = e39->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0* i40 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0*>(COUNTCUSTOMER_ADDRESS2.index[1]);
                  const HASH_RES_t h29 = COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::hash(se127.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode* n40 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0::IdxNode*>(i40->slice(se127, h29));
                  COUNTCUSTOMER_ADDRESS2_entry* e40;
                 
                  if (n40 && (e40 = n40->obj)) {
                    do {                
                      STRING_TYPE customer_c_first_name = e40->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e40->CUSTOMER_C_LAST_NAME;
                      STRING_TYPE current_addr_ca_city = e40->CURRENT_ADDR_CA_CITY;
                      long v44 = e40->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i41 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                        const HASH_RES_t h28 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se126.modify0(store_sales_ss_addr_sk));
                        HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n41 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i41->slice(se126, h28));
                        COUNTCUSTOMER1_L2_1_entry* e41;
                       
                        if (n41 && (e41 = n41->obj)) {
                          do {                
                            STRING_TYPE dn_bought_city = e41->DN_BOUGHT_CITY;
                            long v45 = e41->__av;
                            DOUBLE_TYPE agg9 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135* i42 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135*>(COUNTSTORE_SALES9_L2_3_DELTA.index[1]);
                              const HASH_RES_t h25 = COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::hash(se110.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                              HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode* n42 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_135::IdxNode*>(i42->slice(se110, h25));
                              COUNTSTORE_SALES9_L2_3_DELTA_entry* e42;
                             
                              if (n42 && (e42 = n42->obj)) {
                                do {                
                                  long store_sales_ss_sold_date_sk = e42->STORE_SALES_SS_SOLD_DATE_SK;
                                  long store_sales_ss_hdemo_sk = e42->STORE_SALES_SS_HDEMO_SK;
                                  long store_sales_ss_store_sk = e42->STORE_SALES_SS_STORE_SK;
                                  DOUBLE_TYPE v46 = e42->__av;
                                  agg9 += (v46 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se107.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se108.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se109.modify(store_sales_ss_sold_date_sk)))));
                                  n42 = n42->nxt;
                                } while (n42 && (e42 = n42->obj) && h25 == n42->hash &&  COUNTSTORE_SALES9_L2_3_DELTA_mapkey135_idxfn::equals(se110, *e42)); 
                              }
                            }DOUBLE_TYPE l19 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se105.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se106.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg9 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se111.modify(store_sales_ss_addr_sk,dn_bought_city))));
                            DOUBLE_TYPE agg10 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135* i43 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135*>(COUNTSTORE_SALES9_L3_3_DELTA.index[1]);
                              const HASH_RES_t h26 = COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::hash(se117.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                              HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode* n43 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_135::IdxNode*>(i43->slice(se117, h26));
                              COUNTSTORE_SALES9_L3_3_DELTA_entry* e43;
                             
                              if (n43 && (e43 = n43->obj)) {
                                do {                
                                  long store_sales_ss_sold_date_sk = e43->STORE_SALES_SS_SOLD_DATE_SK;
                                  long store_sales_ss_hdemo_sk = e43->STORE_SALES_SS_HDEMO_SK;
                                  long store_sales_ss_store_sk = e43->STORE_SALES_SS_STORE_SK;
                                  DOUBLE_TYPE v47 = e43->__av;
                                  agg10 += (v47 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se114.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se115.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se116.modify(store_sales_ss_sold_date_sk)))));
                                  n43 = n43->nxt;
                                } while (n43 && (e43 = n43->obj) && h26 == n43->hash &&  COUNTSTORE_SALES9_L3_3_DELTA_mapkey135_idxfn::equals(se117, *e43)); 
                              }
                            }DOUBLE_TYPE l20 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se112.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se113.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg10 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se118.modify(store_sales_ss_addr_sk,dn_bought_city))));
                            DOUBLE_TYPE agg11 = 0.0;
                            { //slice 
                              const HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135* i44 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135*>(COUNTSTORE_SALES9_L4_3_DELTA.index[1]);
                              const HASH_RES_t h27 = COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn::hash(se124.modify135(customer_c_customer_sk, store_sales_ss_addr_sk, dn_ss_ticket_number));
                              HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135::IdxNode* n44 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_135::IdxNode*>(i44->slice(se124, h27));
                              COUNTSTORE_SALES9_L4_3_DELTA_entry* e44;
                             
                              if (n44 && (e44 = n44->obj)) {
                                do {                
                                  long store_sales_ss_sold_date_sk = e44->STORE_SALES_SS_SOLD_DATE_SK;
                                  long store_sales_ss_hdemo_sk = e44->STORE_SALES_SS_HDEMO_SK;
                                  long store_sales_ss_store_sk = e44->STORE_SALES_SS_STORE_SK;
                                  DOUBLE_TYPE v48 = e44->__av;
                                  agg11 += (v48 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se121.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se122.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se123.modify(store_sales_ss_sold_date_sk)))));
                                  n44 = n44->nxt;
                                } while (n44 && (e44 = n44->obj) && h27 == n44->hash &&  COUNTSTORE_SALES9_L4_3_DELTA_mapkey135_idxfn::equals(se124, *e44)); 
                              }
                            }DOUBLE_TYPE l21 = ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se119.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se120.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))) + (agg11 * COUNTCUSTOMER1_L2_1.getValueOrDefault(se125.modify(store_sales_ss_addr_sk,dn_bought_city))));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se7.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l21,l19,l20),(((v43 != 0 ? 1L : 0L) * (v44 * ((COUNTCUSTOMER_ADDRESS2_E1_2.getValueOrDefault(se104.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * v45) != 0 ? 1L : 0L))) * -1L)) : (void)0);
                            n41 = n41->nxt;
                          } while (n41 && (e41 = n41->obj) && h28 == n41->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se126, *e41)); 
                        }
                      }
                      n40 = n40->nxt;
                    } while (n40 && (e40 = n40->obj) && h29 == n40->hash &&  COUNTCUSTOMER_ADDRESS2_mapkey0_idxfn::equals(se127, *e40)); 
                  }
                }
              n39 = n39->nxt;
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
                COUNTCUSTOMER_ADDRESS2_E1_2.addOrDelOnZero(se128.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v49 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se129.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se130.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se131.modify(store_sales_ss_sold_date_sk))))));
              n45 = n45->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i46 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n46; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e46;
        
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
                long dn_ss_ticket_number = e46->DN_SS_TICKET_NUMBER;
                long v50 = e46->__av;
                COUNTCUSTOMER_ADDRESS2_E1_2STORE1.addOrDelOnZero(se132.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v50 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se133.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se134.modify(store_sales_ss_sold_date_sk)))));
              n46 = n46->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i47 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n47; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e47;
        
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
                long v51 = e47->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i48 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                  const HASH_RES_t h30 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se139.modify0(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n48 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i48->slice(se139, h30));
                  COUNTCUSTOMER1_L2_1_entry* e48;
                 
                  if (n48 && (e48 = n48->obj)) {
                    do {                
                      STRING_TYPE dn_bought_city = e48->DN_BOUGHT_CITY;
                      long v52 = e48->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se135.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number,dn_bought_city),(v51 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se136.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se137.modify(store_sales_ss_store_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se138.modify(store_sales_ss_sold_date_sk)) * v52)))));
                      n48 = n48->nxt;
                    } while (n48 && (e48 = n48->obj) && h30 == n48->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se139, *e48)); 
                  }
                }
              n47 = n47->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345* i49 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345*>(COUNTSTORE_SALES1_E1_2_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_DELTA_map_012345::IdxNode* n49; 
          COUNTSTORE_SALES1_E1_2_DELTA_entry* e49;
        
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
                long v53 = e49->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L2_1_map_0* i50 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0*>(COUNTCUSTOMER1_L2_1.index[1]);
                  const HASH_RES_t h31 = COUNTCUSTOMER1_L2_1_mapkey0_idxfn::hash(se143.modify0(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode* n50 = static_cast<HashIndex_COUNTCUSTOMER1_L2_1_map_0::IdxNode*>(i50->slice(se143, h31));
                  COUNTCUSTOMER1_L2_1_entry* e50;
                 
                  if (n50 && (e50 = n50->obj)) {
                    do {                
                      STRING_TYPE dn_bought_city = e50->DN_BOUGHT_CITY;
                      long v54 = e50->__av;
                      COUNTCUSTOMER1_E1_1STORE1.addOrDelOnZero(se140.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number,dn_bought_city),(v53 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se141.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se142.modify(store_sales_ss_sold_date_sk)) * v54))));
                      n50 = n50->nxt;
                    } while (n50 && (e50 = n50->obj) && h31 == n50->hash &&  COUNTCUSTOMER1_L2_1_mapkey0_idxfn::equals(se143, *e50)); 
                  }
                }
              n49 = n49->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345* i51 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L2_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345::IdxNode* n51; 
          COUNTSTORE_SALES9_L2_3_DELTA_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long store_sales_ss_sold_date_sk = e51->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e51->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e51->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e51->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e51->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e51->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v55 = e51->__av;
                COUNTCUSTOMER1_L2_2.addOrDelOnZero(se144.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v55 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se145.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se146.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se147.modify(store_sales_ss_sold_date_sk))))));
              n51 = n51->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345* i52 = static_cast<HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L2_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L2_3_DELTA_map_012345::IdxNode* n52; 
          COUNTSTORE_SALES9_L2_3_DELTA_entry* e52;
        
          for (size_t i = 0; i < i52->size_; i++)
          {
            n52 = i52->buckets_ + i;
            while (n52 && (e52 = n52->obj))
            {
                long store_sales_ss_sold_date_sk = e52->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e52->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e52->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e52->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e52->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e52->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v56 = e52->__av;
                COUNTCUSTOMER1_L2_2STORE1.addOrDelOnZero(se148.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v56 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se149.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se150.modify(store_sales_ss_sold_date_sk)))));
              n52 = n52->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345* i53 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L3_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345::IdxNode* n53; 
          COUNTSTORE_SALES9_L3_3_DELTA_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long store_sales_ss_sold_date_sk = e53->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e53->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e53->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e53->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e53->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e53->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v57 = e53->__av;
                COUNTCUSTOMER1_L3_2.addOrDelOnZero(se151.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v57 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se152.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se153.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se154.modify(store_sales_ss_sold_date_sk))))));
              n53 = n53->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345* i54 = static_cast<HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L3_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L3_3_DELTA_map_012345::IdxNode* n54; 
          COUNTSTORE_SALES9_L3_3_DELTA_entry* e54;
        
          for (size_t i = 0; i < i54->size_; i++)
          {
            n54 = i54->buckets_ + i;
            while (n54 && (e54 = n54->obj))
            {
                long store_sales_ss_sold_date_sk = e54->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e54->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e54->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e54->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e54->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e54->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v58 = e54->__av;
                COUNTCUSTOMER1_L3_2STORE1.addOrDelOnZero(se155.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v58 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se156.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se157.modify(store_sales_ss_sold_date_sk)))));
              n54 = n54->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_012345* i55 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L4_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_012345::IdxNode* n55; 
          COUNTSTORE_SALES9_L4_3_DELTA_entry* e55;
        
          for (size_t i = 0; i < i55->size_; i++)
          {
            n55 = i55->buckets_ + i;
            while (n55 && (e55 = n55->obj))
            {
                long store_sales_ss_sold_date_sk = e55->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e55->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e55->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e55->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e55->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e55->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v59 = e55->__av;
                COUNTCUSTOMER1_L4_2.addOrDelOnZero(se158.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v59 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se159.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_2_P_2.getValueOrDefault(se160.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se161.modify(store_sales_ss_sold_date_sk))))));
              n55 = n55->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_012345* i56 = static_cast<HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_012345*>(COUNTSTORE_SALES9_L4_3_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES9_L4_3_DELTA_map_012345::IdxNode* n56; 
          COUNTSTORE_SALES9_L4_3_DELTA_entry* e56;
        
          for (size_t i = 0; i < i56->size_; i++)
          {
            n56 = i56->buckets_ + i;
            while (n56 && (e56 = n56->obj))
            {
                long store_sales_ss_sold_date_sk = e56->STORE_SALES_SS_SOLD_DATE_SK;
                long customer_c_customer_sk = e56->CUSTOMER_C_CUSTOMER_SK;
                long store_sales_ss_hdemo_sk = e56->STORE_SALES_SS_HDEMO_SK;
                long store_sales_ss_addr_sk = e56->STORE_SALES_SS_ADDR_SK;
                long store_sales_ss_store_sk = e56->STORE_SALES_SS_STORE_SK;
                long dn_ss_ticket_number = e56->DN_SS_TICKET_NUMBER;
                DOUBLE_TYPE v60 = e56->__av;
                COUNTCUSTOMER1_L4_2STORE1.addOrDelOnZero(se162.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number),(v60 * (COUNTSTORE_SALES1_E1_2_P_1.getValueOrDefault(se163.modify(store_sales_ss_hdemo_sk)) * COUNTSTORE_SALES1_E1_2_P_3.getValueOrDefault(se164.modify(store_sales_ss_sold_date_sk)))));
              n56 = n56->nxt;
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
                long v61 = 1L;
                COUNTCUSTOMER1_DELTA.addOrDelOnZero(se165.modify(customer_c_customer_sk,customer_c_current_addr_sk,customer_c_first_name,customer_c_last_name),v61);            
          }
        }

        {  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_0123* i58 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_0123*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_0123::IdxNode* n58; 
          COUNTCUSTOMER1_DELTA_entry* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
                long customer_c_customer_sk = e58->CUSTOMER_C_CUSTOMER_SK;
                long customer_c_current_addr_sk = e58->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_c_first_name = e58->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e58->CUSTOMER_C_LAST_NAME;
                long v62 = e58->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_map_0* i59 = static_cast<HashIndex_COUNTCUSTOMER1_map_0*>(COUNTCUSTOMER1.index[1]);
                  const HASH_RES_t h33 = COUNTCUSTOMER1_mapkey0_idxfn::hash(se174.modify0(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER1_map_0::IdxNode* n59 = static_cast<HashIndex_COUNTCUSTOMER1_map_0::IdxNode*>(i59->slice(se174, h33));
                  COUNTCUSTOMER1_entry* e59;
                 
                  if (n59 && (e59 = n59->obj)) {
                    do {                
                      STRING_TYPE current_addr_ca_city = e59->CURRENT_ADDR_CA_CITY;
                      long v63 = e59->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i60 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h32 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se173.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n60 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i60->slice(se173, h32));
                        COUNTCUSTOMER1_E1_1_entry* e60;
                       
                        if (n60 && (e60 = n60->obj)) {
                          do {                
                            long store_sales_ss_addr_sk = e60->STORE_SALES_SS_ADDR_SK;
                            long dn_ss_ticket_number = e60->DN_SS_TICKET_NUMBER;
                            STRING_TYPE dn_bought_city = e60->DN_BOUGHT_CITY;
                            long v64 = e60->__av;
                            DOUBLE_TYPE l22 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se167.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se168.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            DOUBLE_TYPE l23 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se169.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se170.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            DOUBLE_TYPE l24 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se171.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se172.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se166.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l22,l24,l23),(v62 * (v63 * (v64 != 0 ? 1L : 0L)))) : (void)0);
                            n60 = n60->nxt;
                          } while (n60 && (e60 = n60->obj) && h32 == n60->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se173, *e60)); 
                        }
                      }
                      n59 = n59->nxt;
                    } while (n59 && (e59 = n59->obj) && h33 == n59->hash &&  COUNTCUSTOMER1_mapkey0_idxfn::equals(se174, *e59)); 
                  }
                }
              n58 = n58->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_0123* i61 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_0123*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_0123::IdxNode* n61; 
          COUNTCUSTOMER1_DELTA_entry* e61;
        
          for (size_t i = 0; i < i61->size_; i++)
          {
            n61 = i61->buckets_ + i;
            while (n61 && (e61 = n61->obj))
            {
                long customer_c_customer_sk = e61->CUSTOMER_C_CUSTOMER_SK;
                long customer_c_current_addr_sk = e61->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_c_first_name = e61->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e61->CUSTOMER_C_LAST_NAME;
                long v65 = e61->__av;
                COUNTCUSTOMER_ADDRESS1.addOrDelOnZero(se175.modify(customer_c_customer_sk,customer_c_current_addr_sk,customer_c_first_name,customer_c_last_name),v65);
              n61 = n61->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER1_DELTA_map_0123* i62 = static_cast<HashIndex_COUNTCUSTOMER1_DELTA_map_0123*>(COUNTCUSTOMER1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER1_DELTA_map_0123::IdxNode* n62; 
          COUNTCUSTOMER1_DELTA_entry* e62;
        
          for (size_t i = 0; i < i62->size_; i++)
          {
            n62 = i62->buckets_ + i;
            while (n62 && (e62 = n62->obj))
            {
                long customer_c_customer_sk = e62->CUSTOMER_C_CUSTOMER_SK;
                long customer_c_current_addr_sk = e62->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_c_first_name = e62->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e62->CUSTOMER_C_LAST_NAME;
                long v66 = e62->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_map_0* i63 = static_cast<HashIndex_COUNTCUSTOMER1_map_0*>(COUNTCUSTOMER1.index[1]);
                  const HASH_RES_t h34 = COUNTCUSTOMER1_mapkey0_idxfn::hash(se177.modify0(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER1_map_0::IdxNode* n63 = static_cast<HashIndex_COUNTCUSTOMER1_map_0::IdxNode*>(i63->slice(se177, h34));
                  COUNTCUSTOMER1_entry* e63;
                 
                  if (n63 && (e63 = n63->obj)) {
                    do {                
                      STRING_TYPE current_addr_ca_city = e63->CURRENT_ADDR_CA_CITY;
                      long v67 = e63->__av;
                      COUNTCUSTOMER_ADDRESS2.addOrDelOnZero(se176.modify(customer_c_customer_sk,customer_c_first_name,customer_c_last_name,current_addr_ca_city),(v66 * v67));
                      n63 = n63->nxt;
                    } while (n63 && (e63 = n63->obj) && h34 == n63->hash &&  COUNTCUSTOMER1_mapkey0_idxfn::equals(se177, *e63)); 
                  }
                }
              n62 = n62->nxt;
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
                long v68 = 1L;
                COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.addOrDelOnZero(se178.modify(store_sales_ss_addr_sk,customer_address_ca_city),v68);            
                long v69 = 1L;
                COUNTCUSTOMER_ADDRESS2_DOMAIN1.addOrDelOnZero(se179.modify(store_sales_ss_addr_sk,customer_address_ca_city),(v69 != 0 ? 1L : 0L));
                long v70 = 1L;
                COUNTCUSTOMER_ADDRESS1_DELTA.addOrDelOnZero(se180.modify(store_sales_ss_addr_sk,customer_address_ca_city),v70);
          }
        }

        {  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i67 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n67; 
          COUNTCUSTOMER_ADDRESS1_DELTA_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long customer_c_current_addr_sk = e67->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE current_addr_ca_city = e67->CURRENT_ADDR_CA_CITY;
                long v71 = e67->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i68 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                  const HASH_RES_t h36 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se189.modify1(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n68 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i68->slice(se189, h36));
                  COUNTCUSTOMER_ADDRESS1_entry* e68;
                 
                  if (n68 && (e68 = n68->obj)) {
                    do {                
                      long customer_c_customer_sk = e68->CUSTOMER_C_CUSTOMER_SK;
                      STRING_TYPE customer_c_first_name = e68->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e68->CUSTOMER_C_LAST_NAME;
                      long v72 = e68->__av;
                      { //slice 
                        const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i69 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                        const HASH_RES_t h35 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se188.modify0(customer_c_customer_sk));
                        HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n69 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i69->slice(se188, h35));
                        COUNTCUSTOMER1_E1_1_entry* e69;
                       
                        if (n69 && (e69 = n69->obj)) {
                          do {                
                            long store_sales_ss_addr_sk = e69->STORE_SALES_SS_ADDR_SK;
                            long dn_ss_ticket_number = e69->DN_SS_TICKET_NUMBER;
                            STRING_TYPE dn_bought_city = e69->DN_BOUGHT_CITY;
                            long v73 = e69->__av;
                            DOUBLE_TYPE l25 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se182.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se183.modify(store_sales_ss_addr_sk,dn_bought_city)));
                            DOUBLE_TYPE l26 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se184.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se185.modify(store_sales_ss_addr_sk,dn_bought_city)));
                            DOUBLE_TYPE l27 = (COUNTCUSTOMER1_L4_2.getValueOrDefault(se186.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se187.modify(store_sales_ss_addr_sk,dn_bought_city)));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se181.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l27,l25,l26),(v71 * (v72 * (v73 != 0 ? 1L : 0L)))) : (void)0);
                            n69 = n69->nxt;
                          } while (n69 && (e69 = n69->obj) && h35 == n69->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se188, *e69)); 
                        }
                      }
                      n68 = n68->nxt;
                    } while (n68 && (e68 = n68->obj) && h36 == n68->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se189, *e68)); 
                  }
                }
              n67 = n67->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i70 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n70; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e70;
        
          for (size_t i = 0; i < i70->size_; i++)
          {
            n70 = i70->buckets_ + i;
            while (n70 && (e70 = n70->obj))
            {
                long store_sales_ss_addr_sk = e70->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e70->DN_BOUGHT_CITY;
                long v74 = e70->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123* i71 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123*>(COUNTCUSTOMER_ADDRESS2.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123::IdxNode* n71; 
                  COUNTCUSTOMER_ADDRESS2_entry* e71;
                
                  for (size_t i = 0; i < i71->size_; i++)
                  {
                    n71 = i71->buckets_ + i;
                    while (n71 && (e71 = n71->obj))
                    {
                        long customer_c_customer_sk = e71->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e71->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e71->CUSTOMER_C_LAST_NAME;
                        STRING_TYPE current_addr_ca_city = e71->CURRENT_ADDR_CA_CITY;
                        long v75 = e71->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i72 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                          const HASH_RES_t h37 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se197.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n72 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i72->slice(se197, h37));
                          COUNTCUSTOMER_ADDRESS2_E1_2_entry* e72;
                         
                          if (n72 && (e72 = n72->obj)) {
                            do {                
                              long dn_ss_ticket_number = e72->DN_SS_TICKET_NUMBER;
                              long v76 = e72->__av;
                              DOUBLE_TYPE l28 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se191.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se192.modify(store_sales_ss_addr_sk,dn_bought_city)));
                              DOUBLE_TYPE l29 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se193.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se194.modify(store_sales_ss_addr_sk,dn_bought_city)));
                              DOUBLE_TYPE l30 = (COUNTCUSTOMER1_L4_2.getValueOrDefault(se195.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se196.modify(store_sales_ss_addr_sk,dn_bought_city)));
                              (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se181.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l30,l28,l29),(((v74 != 0 ? 1L : 0L) * (v75 * ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se190.modify(store_sales_ss_addr_sk,dn_bought_city)) * v76) != 0 ? 1L : 0L))) * -1L)) : (void)0);
                              n72 = n72->nxt;
                            } while (n72 && (e72 = n72->obj) && h37 == n72->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se197, *e72)); 
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
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i73 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n73; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e73;
        
          for (size_t i = 0; i < i73->size_; i++)
          {
            n73 = i73->buckets_ + i;
            while (n73 && (e73 = n73->obj))
            {
                long store_sales_ss_addr_sk = e73->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e73->DN_BOUGHT_CITY;
                long v77 = e73->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i74 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n74; 
                  COUNTCUSTOMER_ADDRESS1_DELTA_entry* e74;
                
                  for (size_t i = 0; i < i74->size_; i++)
                  {
                    n74 = i74->buckets_ + i;
                    while (n74 && (e74 = n74->obj))
                    {
                        long customer_c_current_addr_sk = e74->CUSTOMER_C_CURRENT_ADDR_SK;
                        STRING_TYPE current_addr_ca_city = e74->CURRENT_ADDR_CA_CITY;
                        long v78 = e74->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i75 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                          const HASH_RES_t h39 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se206.modify1(customer_c_current_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n75 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i75->slice(se206, h39));
                          COUNTCUSTOMER_ADDRESS1_entry* e75;
                         
                          if (n75 && (e75 = n75->obj)) {
                            do {                
                              long customer_c_customer_sk = e75->CUSTOMER_C_CUSTOMER_SK;
                              STRING_TYPE customer_c_first_name = e75->CUSTOMER_C_FIRST_NAME;
                              STRING_TYPE customer_c_last_name = e75->CUSTOMER_C_LAST_NAME;
                              long v79 = e75->__av;
                              { //slice 
                                const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i76 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                                const HASH_RES_t h38 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se205.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                                HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n76 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i76->slice(se205, h38));
                                COUNTCUSTOMER_ADDRESS2_E1_2_entry* e76;
                               
                                if (n76 && (e76 = n76->obj)) {
                                  do {                
                                    long dn_ss_ticket_number = e76->DN_SS_TICKET_NUMBER;
                                    long v80 = e76->__av;
                                    DOUBLE_TYPE l31 = (COUNTCUSTOMER1_L2_2.getValueOrDefault(se199.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se200.modify(store_sales_ss_addr_sk,dn_bought_city)));
                                    DOUBLE_TYPE l32 = (COUNTCUSTOMER1_L3_2.getValueOrDefault(se201.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se202.modify(store_sales_ss_addr_sk,dn_bought_city)));
                                    DOUBLE_TYPE l33 = (COUNTCUSTOMER1_L4_2.getValueOrDefault(se203.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se204.modify(store_sales_ss_addr_sk,dn_bought_city)));
                                    (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se181.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l33,l31,l32),(((v77 != 0 ? 1L : 0L) * (v78 * (v79 * ((COUNTCUSTOMER1_L2_1.getValueOrDefault(se198.modify(store_sales_ss_addr_sk,dn_bought_city)) * v80) != 0 ? 1L : 0L)))) * -1L)) : (void)0);
                                    n76 = n76->nxt;
                                  } while (n76 && (e76 = n76->obj) && h38 == n76->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se205, *e76)); 
                                }
                              }
                              n75 = n75->nxt;
                            } while (n75 && (e75 = n75->obj) && h39 == n75->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se206, *e75)); 
                          }
                        }
                      n74 = n74->nxt;
                    }
                  }
                }
              n73 = n73->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i77 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n77; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e77;
        
          for (size_t i = 0; i < i77->size_; i++)
          {
            n77 = i77->buckets_ + i;
            while (n77 && (e77 = n77->obj))
            {
                long store_sales_ss_addr_sk = e77->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e77->DN_BOUGHT_CITY;
                long v81 = e77->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123* i78 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123*>(COUNTCUSTOMER_ADDRESS2.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123::IdxNode* n78; 
                  COUNTCUSTOMER_ADDRESS2_entry* e78;
                
                  for (size_t i = 0; i < i78->size_; i++)
                  {
                    n78 = i78->buckets_ + i;
                    while (n78 && (e78 = n78->obj))
                    {
                        long customer_c_customer_sk = e78->CUSTOMER_C_CUSTOMER_SK;
                        STRING_TYPE customer_c_first_name = e78->CUSTOMER_C_FIRST_NAME;
                        STRING_TYPE customer_c_last_name = e78->CUSTOMER_C_LAST_NAME;
                        STRING_TYPE current_addr_ca_city = e78->CURRENT_ADDR_CA_CITY;
                        long v82 = e78->__av;
                        _c5.clear();
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i79 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                          const HASH_RES_t h40 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se208.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n79 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i79->slice(se208, h40));
                          COUNTCUSTOMER_ADDRESS2_E1_2_entry* e79;
                         
                          if (n79 && (e79 = n79->obj)) {
                            do {                
                              long dn_ss_ticket_number = e79->DN_SS_TICKET_NUMBER;
                              long v84 = e79->__av;
                              _c5.addOrDelOnZero(st10.modify(dn_ss_ticket_number,(COUNTCUSTOMER1_L2_1.getValueOrDefault(se207.modify(store_sales_ss_addr_sk,dn_bought_city)) * v84)), (COUNTCUSTOMER1_L2_1.getValueOrDefault(se207.modify(store_sales_ss_addr_sk,dn_bought_city)) * v84));
                              n79 = n79->nxt;
                            } while (n79 && (e79 = n79->obj) && h40 == n79->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se208, *e79)); 
                          }
                        }{ //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i80 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                          const HASH_RES_t h41 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se210.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n80 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i80->slice(se210, h41));
                          COUNTCUSTOMER_ADDRESS2_E1_2_entry* e80;
                         
                          if (n80 && (e80 = n80->obj)) {
                            do {                
                              long dn_ss_ticket_number = e80->DN_SS_TICKET_NUMBER;
                              long v85 = e80->__av;
                              _c5.addOrDelOnZero(st11.modify(dn_ss_ticket_number,(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se209.modify(store_sales_ss_addr_sk,dn_bought_city)) * v85)), (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se209.modify(store_sales_ss_addr_sk,dn_bought_city)) * v85));
                              n80 = n80->nxt;
                            } while (n80 && (e80 = n80->obj) && h41 == n80->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se210, *e80)); 
                          }
                        }{  // temp foreach
                          const HashIndex<tuple2_L_L, long>* i81 = static_cast<HashIndex<tuple2_L_L, long>*>(_c5.index[0]);
                          HashIndex<tuple2_L_L, long>::IdxNode* n81; 
                          tuple2_L_L* e81;
                        
                          for (size_t i = 0; i < i81->size_; i++)
                          {
                            n81 = i81->buckets_ + i;
                            while (n81 && (e81 = n81->obj))
                            {
                              long dn_ss_ticket_number = e81->_1;  
                              long v86 = e81->__av; 
                            DOUBLE_TYPE l34 = ((COUNTCUSTOMER1_L2_2.getValueOrDefault(se211.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se212.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se213.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se214.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                            DOUBLE_TYPE l35 = ((COUNTCUSTOMER1_L3_2.getValueOrDefault(se215.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se216.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se217.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se218.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                            DOUBLE_TYPE l36 = ((COUNTCUSTOMER1_L4_2.getValueOrDefault(se219.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se220.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se221.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se222.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                            (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se181.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l36,l34,l35),((v81 != 0 ? 1L : 0L) * (v82 * (v86 != 0 ? 1L : 0L)))) : (void)0);      
                              n81 = n81->nxt;
                            }
                          }
                        }
                      n78 = n78->nxt;
                    }
                  }
                }
              n77 = n77->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01* i82 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01*>(COUNTCUSTOMER_ADDRESS2_DOMAIN1.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_DOMAIN1_map_01::IdxNode* n82; 
          COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry* e82;
        
          for (size_t i = 0; i < i82->size_; i++)
          {
            n82 = i82->buckets_ + i;
            while (n82 && (e82 = n82->obj))
            {
                long store_sales_ss_addr_sk = e82->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e82->DN_BOUGHT_CITY;
                long v87 = e82->__av;
                {  // foreach
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i83 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
                  HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n83; 
                  COUNTCUSTOMER_ADDRESS1_DELTA_entry* e83;
                
                  for (size_t i = 0; i < i83->size_; i++)
                  {
                    n83 = i83->buckets_ + i;
                    while (n83 && (e83 = n83->obj))
                    {
                        long customer_c_current_addr_sk = e83->CUSTOMER_C_CURRENT_ADDR_SK;
                        STRING_TYPE current_addr_ca_city = e83->CURRENT_ADDR_CA_CITY;
                        long v88 = e83->__av;
                        { //slice 
                          const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i84 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                          const HASH_RES_t h44 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se239.modify1(customer_c_current_addr_sk));
                          HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n84 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i84->slice(se239, h44));
                          COUNTCUSTOMER_ADDRESS1_entry* e84;
                         
                          if (n84 && (e84 = n84->obj)) {
                            do {                
                              long customer_c_customer_sk = e84->CUSTOMER_C_CUSTOMER_SK;
                              STRING_TYPE customer_c_first_name = e84->CUSTOMER_C_FIRST_NAME;
                              STRING_TYPE customer_c_last_name = e84->CUSTOMER_C_LAST_NAME;
                              long v89 = e84->__av;
                              _c6.clear();
                              { //slice 
                                const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i85 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                                const HASH_RES_t h42 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se224.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                                HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n85 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i85->slice(se224, h42));
                                COUNTCUSTOMER_ADDRESS2_E1_2_entry* e85;
                               
                                if (n85 && (e85 = n85->obj)) {
                                  do {                
                                    long dn_ss_ticket_number = e85->DN_SS_TICKET_NUMBER;
                                    long v91 = e85->__av;
                                    _c6.addOrDelOnZero(st12.modify(dn_ss_ticket_number,(COUNTCUSTOMER1_L2_1.getValueOrDefault(se223.modify(store_sales_ss_addr_sk,dn_bought_city)) * v91)), (COUNTCUSTOMER1_L2_1.getValueOrDefault(se223.modify(store_sales_ss_addr_sk,dn_bought_city)) * v91));
                                    n85 = n85->nxt;
                                  } while (n85 && (e85 = n85->obj) && h42 == n85->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se224, *e85)); 
                                }
                              }{ //slice 
                                const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01* i86 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[1]);
                                const HASH_RES_t h43 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::hash(se226.modify01(customer_c_customer_sk, store_sales_ss_addr_sk));
                                HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode* n86 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_01::IdxNode*>(i86->slice(se226, h43));
                                COUNTCUSTOMER_ADDRESS2_E1_2_entry* e86;
                               
                                if (n86 && (e86 = n86->obj)) {
                                  do {                
                                    long dn_ss_ticket_number = e86->DN_SS_TICKET_NUMBER;
                                    long v92 = e86->__av;
                                    _c6.addOrDelOnZero(st13.modify(dn_ss_ticket_number,(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se225.modify(store_sales_ss_addr_sk,dn_bought_city)) * v92)), (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se225.modify(store_sales_ss_addr_sk,dn_bought_city)) * v92));
                                    n86 = n86->nxt;
                                  } while (n86 && (e86 = n86->obj) && h43 == n86->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey01_idxfn::equals(se226, *e86)); 
                                }
                              }{  // temp foreach
                                const HashIndex<tuple2_L_L, long>* i87 = static_cast<HashIndex<tuple2_L_L, long>*>(_c6.index[0]);
                                HashIndex<tuple2_L_L, long>::IdxNode* n87; 
                                tuple2_L_L* e87;
                              
                                for (size_t i = 0; i < i87->size_; i++)
                                {
                                  n87 = i87->buckets_ + i;
                                  while (n87 && (e87 = n87->obj))
                                  {
                                    long dn_ss_ticket_number = e87->_1;  
                                    long v93 = e87->__av; 
                                  DOUBLE_TYPE l37 = ((COUNTCUSTOMER1_L2_2.getValueOrDefault(se227.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se228.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se229.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se230.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                                  DOUBLE_TYPE l38 = ((COUNTCUSTOMER1_L3_2.getValueOrDefault(se231.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se232.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se233.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se234.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                                  DOUBLE_TYPE l39 = ((COUNTCUSTOMER1_L4_2.getValueOrDefault(se235.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)) * COUNTCUSTOMER1_L2_1.getValueOrDefault(se236.modify(store_sales_ss_addr_sk,dn_bought_city))) + (COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.getValueOrDefault(se237.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se238.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number))));
                                  (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se181.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l39,l37,l38),((v87 != 0 ? 1L : 0L) * (v88 * (v89 * (v93 != 0 ? 1L : 0L))))) : (void)0);      
                                    n87 = n87->nxt;
                                  }
                                }
                              }
                              n84 = n84->nxt;
                            } while (n84 && (e84 = n84->obj) && h44 == n84->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se239, *e84)); 
                          }
                        }
                      n83 = n83->nxt;
                    }
                  }
                }
              n82 = n82->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i88 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n88; 
          COUNTCUSTOMER_ADDRESS1_DELTA_entry* e88;
        
          for (size_t i = 0; i < i88->size_; i++)
          {
            n88 = i88->buckets_ + i;
            while (n88 && (e88 = n88->obj))
            {
                long customer_c_current_addr_sk = e88->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE current_addr_ca_city = e88->CURRENT_ADDR_CA_CITY;
                long v94 = e88->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS1_map_1* i89 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1*>(COUNTCUSTOMER_ADDRESS1.index[1]);
                  const HASH_RES_t h45 = COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::hash(se241.modify1(customer_c_current_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode* n89 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_map_1::IdxNode*>(i89->slice(se241, h45));
                  COUNTCUSTOMER_ADDRESS1_entry* e89;
                 
                  if (n89 && (e89 = n89->obj)) {
                    do {                
                      long customer_c_customer_sk = e89->CUSTOMER_C_CUSTOMER_SK;
                      STRING_TYPE customer_c_first_name = e89->CUSTOMER_C_FIRST_NAME;
                      STRING_TYPE customer_c_last_name = e89->CUSTOMER_C_LAST_NAME;
                      long v95 = e89->__av;
                      COUNTCUSTOMER_ADDRESS2.addOrDelOnZero(se240.modify(customer_c_customer_sk,customer_c_first_name,customer_c_last_name,current_addr_ca_city),(v94 * v95));
                      n89 = n89->nxt;
                    } while (n89 && (e89 = n89->obj) && h45 == n89->hash &&  COUNTCUSTOMER_ADDRESS1_mapkey1_idxfn::equals(se241, *e89)); 
                  }
                }
              n88 = n88->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01* i90 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n90; 
          COUNTCUSTOMER_ADDRESS1_DELTA_entry* e90;
        
          for (size_t i = 0; i < i90->size_; i++)
          {
            n90 = i90->buckets_ + i;
            while (n90 && (e90 = n90->obj))
            {
                long customer_c_current_addr_sk = e90->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE current_addr_ca_city = e90->CURRENT_ADDR_CA_CITY;
                long v96 = e90->__av;
                COUNTCUSTOMER1.addOrDelOnZero(se242.modify(customer_c_current_addr_sk,current_addr_ca_city),v96);
              n90 = n90->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01* i91 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01::IdxNode* n91; 
          COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long store_sales_ss_addr_sk = e91->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e91->DN_BOUGHT_CITY;
                long v97 = e91->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1* i92 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1*>(COUNTCUSTOMER_ADDRESS2_E1_2.index[2]);
                  const HASH_RES_t h46 = COUNTCUSTOMER_ADDRESS2_E1_2_mapkey1_idxfn::hash(se244.modify1(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1::IdxNode* n92 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2_map_1::IdxNode*>(i92->slice(se244, h46));
                  COUNTCUSTOMER_ADDRESS2_E1_2_entry* e92;
                 
                  if (n92 && (e92 = n92->obj)) {
                    do {                
                      long customer_c_customer_sk = e92->CUSTOMER_C_CUSTOMER_SK;
                      long dn_ss_ticket_number = e92->DN_SS_TICKET_NUMBER;
                      long v98 = e92->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se243.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number,dn_bought_city),(v97 * v98));
                      n92 = n92->nxt;
                    } while (n92 && (e92 = n92->obj) && h46 == n92->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2_mapkey1_idxfn::equals(se244, *e92)); 
                  }
                }
              n91 = n91->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01* i93 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01::IdxNode* n93; 
          COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry* e93;
        
          for (size_t i = 0; i < i93->size_; i++)
          {
            n93 = i93->buckets_ + i;
            while (n93 && (e93 = n93->obj))
            {
                long store_sales_ss_addr_sk = e93->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e93->DN_BOUGHT_CITY;
                long v99 = e93->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1* i94 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1*>(COUNTCUSTOMER_ADDRESS2_E1_2STORE1.index[1]);
                  const HASH_RES_t h47 = COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey1_idxfn::hash(se246.modify1(store_sales_ss_addr_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1::IdxNode* n94 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_1::IdxNode*>(i94->slice(se246, h47));
                  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry* e94;
                 
                  if (n94 && (e94 = n94->obj)) {
                    do {                
                      long customer_c_customer_sk = e94->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_store_sk = e94->STORE_SALES_SS_STORE_SK;
                      long dn_ss_ticket_number = e94->DN_SS_TICKET_NUMBER;
                      long v100 = e94->__av;
                      COUNTCUSTOMER1_E1_1STORE1.addOrDelOnZero(se245.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,dn_ss_ticket_number,dn_bought_city),(v99 * v100));
                      n94 = n94->nxt;
                    } while (n94 && (e94 = n94->obj) && h47 == n94->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey1_idxfn::equals(se246, *e94)); 
                  }
                }
              n93 = n93->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01* i95 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01*>(COUNTCUSTOMER_ADDRESS6_E1_3_DELTA.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_map_01::IdxNode* n95; 
          COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry* e95;
        
          for (size_t i = 0; i < i95->size_; i++)
          {
            n95 = i95->buckets_ + i;
            while (n95 && (e95 = n95->obj))
            {
                long store_sales_ss_addr_sk = e95->STORE_SALES_SS_ADDR_SK;
                STRING_TYPE dn_bought_city = e95->DN_BOUGHT_CITY;
                long v101 = e95->__av;
                COUNTCUSTOMER1_L2_1.addOrDelOnZero(se247.modify(store_sales_ss_addr_sk,dn_bought_city),v101);
              n95 = n95->nxt;
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
                long v102 = 1L;
                (/*if */(((store_s_city == c1) || (store_s_city == c2))) ? COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.addOrDelOnZero(se248.modify(store_sales_ss_store_sk),v102) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i97 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n97; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
                long store_sales_ss_store_sk = e97->STORE_SALES_SS_STORE_SK;
                long v103 = e97->__av;
                COUNTSTORE_SALES1_E1_2_P_2.addOrDelOnZero(se249.modify(store_sales_ss_store_sk),v103);
              n97 = n97->nxt;
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
                  const HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2* i99 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2*>(COUNTCUSTOMER_ADDRESS2_E1_2STORE1.index[2]);
                  const HASH_RES_t h48 = COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey2_idxfn::hash(se251.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2::IdxNode* n99 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_E1_2STORE1_map_2::IdxNode*>(i99->slice(se251, h48));
                  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry* e99;
                 
                  if (n99 && (e99 = n99->obj)) {
                    do {                
                      long customer_c_customer_sk = e99->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e99->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e99->DN_SS_TICKET_NUMBER;
                      long v105 = e99->__av;
                      COUNTCUSTOMER_ADDRESS2_E1_2.addOrDelOnZero(se250.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v104 * v105));
                      n99 = n99->nxt;
                    } while (n99 && (e99 = n99->obj) && h48 == n99->hash &&  COUNTCUSTOMER_ADDRESS2_E1_2STORE1_mapkey2_idxfn::equals(se251, *e99)); 
                  }
                }
              n98 = n98->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i100 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n100; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long store_sales_ss_store_sk = e100->STORE_SALES_SS_STORE_SK;
                long v106 = e100->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2* i101 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2*>(COUNTCUSTOMER1_E1_1STORE1.index[1]);
                  const HASH_RES_t h49 = COUNTCUSTOMER1_E1_1STORE1_mapkey2_idxfn::hash(se253.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2::IdxNode* n101 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE1_map_2::IdxNode*>(i101->slice(se253, h49));
                  COUNTCUSTOMER1_E1_1STORE1_entry* e101;
                 
                  if (n101 && (e101 = n101->obj)) {
                    do {                
                      long customer_c_customer_sk = e101->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e101->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e101->DN_SS_TICKET_NUMBER;
                      STRING_TYPE dn_bought_city = e101->DN_BOUGHT_CITY;
                      long v107 = e101->__av;
                      COUNTCUSTOMER1_E1_1.addOrDelOnZero(se252.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number,dn_bought_city),(v106 * v107));
                      n101 = n101->nxt;
                    } while (n101 && (e101 = n101->obj) && h49 == n101->hash &&  COUNTCUSTOMER1_E1_1STORE1_mapkey2_idxfn::equals(se253, *e101)); 
                  }
                }
              n100 = n100->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i102 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n102; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e102;
        
          for (size_t i = 0; i < i102->size_; i++)
          {
            n102 = i102->buckets_ + i;
            while (n102 && (e102 = n102->obj))
            {
                long store_sales_ss_store_sk = e102->STORE_SALES_SS_STORE_SK;
                long v108 = e102->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2* i103 = static_cast<HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2*>(COUNTCUSTOMER1_L2_2STORE1.index[1]);
                  const HASH_RES_t h50 = COUNTCUSTOMER1_L2_2STORE1_mapkey2_idxfn::hash(se255.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2::IdxNode* n103 = static_cast<HashIndex_COUNTCUSTOMER1_L2_2STORE1_map_2::IdxNode*>(i103->slice(se255, h50));
                  COUNTCUSTOMER1_L2_2STORE1_entry* e103;
                 
                  if (n103 && (e103 = n103->obj)) {
                    do {                
                      long customer_c_customer_sk = e103->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e103->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e103->DN_SS_TICKET_NUMBER;
                      DOUBLE_TYPE v109 = e103->__av;
                      COUNTCUSTOMER1_L2_2.addOrDelOnZero(se254.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v108 * v109));
                      n103 = n103->nxt;
                    } while (n103 && (e103 = n103->obj) && h50 == n103->hash &&  COUNTCUSTOMER1_L2_2STORE1_mapkey2_idxfn::equals(se255, *e103)); 
                  }
                }
              n102 = n102->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i104 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n104; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e104;
        
          for (size_t i = 0; i < i104->size_; i++)
          {
            n104 = i104->buckets_ + i;
            while (n104 && (e104 = n104->obj))
            {
                long store_sales_ss_store_sk = e104->STORE_SALES_SS_STORE_SK;
                long v110 = e104->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2* i105 = static_cast<HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2*>(COUNTCUSTOMER1_L3_2STORE1.index[1]);
                  const HASH_RES_t h51 = COUNTCUSTOMER1_L3_2STORE1_mapkey2_idxfn::hash(se257.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2::IdxNode* n105 = static_cast<HashIndex_COUNTCUSTOMER1_L3_2STORE1_map_2::IdxNode*>(i105->slice(se257, h51));
                  COUNTCUSTOMER1_L3_2STORE1_entry* e105;
                 
                  if (n105 && (e105 = n105->obj)) {
                    do {                
                      long customer_c_customer_sk = e105->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e105->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e105->DN_SS_TICKET_NUMBER;
                      DOUBLE_TYPE v111 = e105->__av;
                      COUNTCUSTOMER1_L3_2.addOrDelOnZero(se256.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v110 * v111));
                      n105 = n105->nxt;
                    } while (n105 && (e105 = n105->obj) && h51 == n105->hash &&  COUNTCUSTOMER1_L3_2STORE1_mapkey2_idxfn::equals(se257, *e105)); 
                  }
                }
              n104 = n104->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0* i106 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0*>(COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA.index[0]);
          HashIndex_COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_map_0::IdxNode* n106; 
          COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry* e106;
        
          for (size_t i = 0; i < i106->size_; i++)
          {
            n106 = i106->buckets_ + i;
            while (n106 && (e106 = n106->obj))
            {
                long store_sales_ss_store_sk = e106->STORE_SALES_SS_STORE_SK;
                long v112 = e106->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_L4_2STORE1_map_2* i107 = static_cast<HashIndex_COUNTCUSTOMER1_L4_2STORE1_map_2*>(COUNTCUSTOMER1_L4_2STORE1.index[1]);
                  const HASH_RES_t h52 = COUNTCUSTOMER1_L4_2STORE1_mapkey2_idxfn::hash(se259.modify2(store_sales_ss_store_sk));
                  HashIndex_COUNTCUSTOMER1_L4_2STORE1_map_2::IdxNode* n107 = static_cast<HashIndex_COUNTCUSTOMER1_L4_2STORE1_map_2::IdxNode*>(i107->slice(se259, h52));
                  COUNTCUSTOMER1_L4_2STORE1_entry* e107;
                 
                  if (n107 && (e107 = n107->obj)) {
                    do {                
                      long customer_c_customer_sk = e107->CUSTOMER_C_CUSTOMER_SK;
                      long store_sales_ss_addr_sk = e107->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e107->DN_SS_TICKET_NUMBER;
                      DOUBLE_TYPE v113 = e107->__av;
                      COUNTCUSTOMER1_L4_2.addOrDelOnZero(se258.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number),(v112 * v113));
                      n107 = n107->nxt;
                    } while (n107 && (e107 = n107->obj) && h52 == n107->hash &&  COUNTCUSTOMER1_L4_2STORE1_mapkey2_idxfn::equals(se259, *e107)); 
                  }
                }
              n106 = n106->nxt;
            }
          }
        }COUNT.clear();
        {  // foreach
          const HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123* i108 = static_cast<HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123*>(COUNTCUSTOMER_ADDRESS2.index[0]);
          HashIndex_COUNTCUSTOMER_ADDRESS2_map_0123::IdxNode* n108; 
          COUNTCUSTOMER_ADDRESS2_entry* e108;
        
          for (size_t i = 0; i < i108->size_; i++)
          {
            n108 = i108->buckets_ + i;
            while (n108 && (e108 = n108->obj))
            {
                long customer_c_customer_sk = e108->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e108->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e108->CUSTOMER_C_LAST_NAME;
                STRING_TYPE current_addr_ca_city = e108->CURRENT_ADDR_CA_CITY;
                long v114 = e108->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i109 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                  const HASH_RES_t h53 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se267.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n109 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i109->slice(se267, h53));
                  COUNTCUSTOMER1_E1_1_entry* e109;
                 
                  if (n109 && (e109 = n109->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e109->STORE_SALES_SS_ADDR_SK;
                      long dn_ss_ticket_number = e109->DN_SS_TICKET_NUMBER;
                      STRING_TYPE dn_bought_city = e109->DN_BOUGHT_CITY;
                      long v115 = e109->__av;
                      DOUBLE_TYPE l40 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se261.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L4_2.getValueOrDefault(se262.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                      DOUBLE_TYPE l41 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se263.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L3_2.getValueOrDefault(se264.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                      DOUBLE_TYPE l42 = (COUNTCUSTOMER1_L2_1.getValueOrDefault(se265.modify(store_sales_ss_addr_sk,dn_bought_city)) * COUNTCUSTOMER1_L2_2.getValueOrDefault(se266.modify(customer_c_customer_sk,store_sales_ss_addr_sk,dn_ss_ticket_number)));
                      (/*if */(current_addr_ca_city != dn_bought_city) ? COUNT.addOrDelOnZero(se260.modify(customer_c_last_name,customer_c_first_name,current_addr_ca_city,dn_bought_city,dn_ss_ticket_number,l40,l42,l41),(v114 * (v115 != 0 ? 1L : 0L))) : (void)0);
                      n109 = n109->nxt;
                    } while (n109 && (e109 = n109->obj) && h53 == n109->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se267, *e109)); 
                  }
                }
              n108 = n108->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTSTORE_SALES1_E1_2_P_1.clear();
        {  // foreach
          const HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234* i110 = static_cast<HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234*>(HOUSEHOLD_DEMOGRAPHICS.index[0]);
          HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234::IdxNode* n110; 
          HOUSEHOLD_DEMOGRAPHICS_entry* e110;
        
          for (size_t i = 0; i < i110->size_; i++)
          {
            n110 = i110->buckets_ + i;
            while (n110 && (e110 = n110->obj))
            {
                long store_sales_ss_hdemo_sk = e110->HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK;
                long household_demographics_hd_income_band_sk = e110->HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK;
                STRING_TYPE household_demographics_hd_buy_potential = e110->HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL;
                long household_demographics_hd_dep_count = e110->HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT;
                long household_demographics_hd_vehicle_count = e110->HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
                long v116 = e110->__av;
                long l43 = ((/*if */(household_demographics_hd_dep_count == 6L) ? 1L : 0L) + (/*if */(household_demographics_hd_vehicle_count == 3L) ? 1L : 0L));
                (/*if */(l43 > 0L) ? COUNTSTORE_SALES1_E1_2_P_1.addOrDelOnZero(se268.modify(store_sales_ss_hdemo_sk),v116) : (void)0);
              n110 = n110->nxt;
            }
          }
        }COUNTSTORE_SALES1_E1_2_P_3.clear();
        {  // foreach
          const HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627* i111 = static_cast<HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627*>(DATE_DIM.index[0]);
          HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627::IdxNode* n111; 
          DATE_DIM_entry* e111;
        
          for (size_t i = 0; i < i111->size_; i++)
          {
            n111 = i111->buckets_ + i;
            while (n111 && (e111 = n111->obj))
            {
                long store_sales_ss_sold_date_sk = e111->DATE_DIM_D_DATE_SK;
                STRING_TYPE date_dim_d_date_id = e111->DATE_DIM_D_DATE_ID;
                date date_dim_d_date = e111->DATE_DIM_D_DATE;
                long date_dim_d_month_seq = e111->DATE_DIM_D_MONTH_SEQ;
                long date_dim_d_week_seq = e111->DATE_DIM_D_WEEK_SEQ;
                long date_dim_d_quarter_seq = e111->DATE_DIM_D_QUARTER_SEQ;
                long date_dim_d_year = e111->DATE_DIM_D_YEAR;
                long date_dim_d_dow = e111->DATE_DIM_D_DOW;
                long date_dim_d_moy = e111->DATE_DIM_D_MOY;
                long date_dim_d_dom = e111->DATE_DIM_D_DOM;
                long date_dim_d_qoy = e111->DATE_DIM_D_QOY;
                long date_dim_d_fy_year = e111->DATE_DIM_D_FY_YEAR;
                long date_dim_d_fy_quarter_seq = e111->DATE_DIM_D_FY_QUARTER_SEQ;
                long date_dim_d_fy_week_seq = e111->DATE_DIM_D_FY_WEEK_SEQ;
                STRING_TYPE date_dim_d_day_name = e111->DATE_DIM_D_DAY_NAME;
                STRING_TYPE date_dim_d_quarter_name = e111->DATE_DIM_D_QUARTER_NAME;
                STRING_TYPE date_dim_d_holiday = e111->DATE_DIM_D_HOLIDAY;
                STRING_TYPE date_dim_d_weekend = e111->DATE_DIM_D_WEEKEND;
                STRING_TYPE date_dim_d_following_holiday = e111->DATE_DIM_D_FOLLOWING_HOLIDAY;
                long date_dim_d_first_dom = e111->DATE_DIM_D_FIRST_DOM;
                long date_dim_d_last_dom = e111->DATE_DIM_D_LAST_DOM;
                long date_dim_d_same_day_ly = e111->DATE_DIM_D_SAME_DAY_LY;
                long date_dim_d_same_day_lq = e111->DATE_DIM_D_SAME_DAY_LQ;
                STRING_TYPE date_dim_d_current_day = e111->DATE_DIM_D_CURRENT_DAY;
                STRING_TYPE date_dim_d_current_week = e111->DATE_DIM_D_CURRENT_WEEK;
                STRING_TYPE date_dim_d_current_month = e111->DATE_DIM_D_CURRENT_MONTH;
                STRING_TYPE date_dim_d_current_quarter = e111->DATE_DIM_D_CURRENT_QUARTER;
                STRING_TYPE date_dim_d_current_year = e111->DATE_DIM_D_CURRENT_YEAR;
                long v117 = e111->__av;
                (/*if */(((date_dim_d_year == 1999L) || (date_dim_d_year == 2000L) || (date_dim_d_year == 2001L)) && 2L >= date_dim_d_dom && date_dim_d_dom >= 1L) ? COUNTSTORE_SALES1_E1_2_P_3.addOrDelOnZero(se269.modify(store_sales_ss_sold_date_sk),v117) : (void)0);
              n111 = n111->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNTSTORE_SALES9_L4_3_DELTA_entry se1;
    COUNTSTORE_SALES9_L3_3_DELTA_entry se2;
    COUNTSTORE_SALES9_L2_3_DELTA_entry se3;
    COUNTSTORE_SALES6_DOMAIN1_entry se4;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se5;
    COUNTSTORE_SALES1_DOMAIN1_entry se6;
    COUNT_entry se7;
    COUNTCUSTOMER1_L4_2_entry se8;
    COUNTCUSTOMER1_L2_1_entry se9;
    COUNTCUSTOMER1_L3_2_entry se10;
    COUNTCUSTOMER1_L2_1_entry se11;
    COUNTCUSTOMER1_L2_2_entry se12;
    COUNTCUSTOMER1_L2_1_entry se13;
    tuple8_SDDDSSS_L st1;
    COUNTCUSTOMER_ADDRESS2_entry se14;
    COUNTCUSTOMER1_E1_1_entry se15;
    tuple4_LLS_L st2;
    COUNTCUSTOMER1_E1_1_entry se16;
    COUNTSTORE_SALES1_E1_2_P_1_entry se17;
    COUNTSTORE_SALES1_E1_2_P_2_entry se18;
    COUNTSTORE_SALES1_E1_2_P_3_entry se19;
    tuple4_LLS_L st3;
    COUNTCUSTOMER1_L2_1_entry se20;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se21;
    COUNTCUSTOMER1_L2_1_entry se22;
    COUNTCUSTOMER1_L2_2_entry se23;
    COUNTCUSTOMER1_L2_1_entry se24;
    COUNTCUSTOMER1_L3_2_entry se25;
    COUNTCUSTOMER1_L2_1_entry se26;
    COUNTCUSTOMER1_L4_2_entry se27;
    tuple8_SDDDSSS_L st4;
    COUNTCUSTOMER_ADDRESS2_entry se28;
    COUNTCUSTOMER1_L2_1_entry se29;
    COUNTCUSTOMER1_L2_2_entry se30;
    COUNTSTORE_SALES1_E1_2_P_1_entry se31;
    COUNTSTORE_SALES1_E1_2_P_2_entry se32;
    COUNTSTORE_SALES1_E1_2_P_3_entry se33;
    COUNTSTORE_SALES9_L2_3_DELTA_entry se34;
    COUNTCUSTOMER1_L2_1_entry se35;
    COUNTCUSTOMER1_L2_1_entry se36;
    COUNTCUSTOMER1_L3_2_entry se37;
    COUNTSTORE_SALES1_E1_2_P_1_entry se38;
    COUNTSTORE_SALES1_E1_2_P_2_entry se39;
    COUNTSTORE_SALES1_E1_2_P_3_entry se40;
    COUNTSTORE_SALES9_L3_3_DELTA_entry se41;
    COUNTCUSTOMER1_L2_1_entry se42;
    COUNTCUSTOMER1_L2_1_entry se43;
    COUNTCUSTOMER1_L4_2_entry se44;
    COUNTSTORE_SALES1_E1_2_P_1_entry se45;
    COUNTSTORE_SALES1_E1_2_P_2_entry se46;
    COUNTSTORE_SALES1_E1_2_P_3_entry se47;
    COUNTSTORE_SALES9_L4_3_DELTA_entry se48;
    COUNTCUSTOMER1_L2_1_entry se49;
    tuple8_SDDDSSS_L st5;
    COUNTCUSTOMER_ADDRESS2_entry se50;
    COUNTCUSTOMER1_E1_1_entry se51;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se52;
    tuple2_S_L st6;
    COUNTCUSTOMER1_L2_1_entry se53;
    COUNTSTORE_SALES1_E1_2_P_1_entry se54;
    COUNTSTORE_SALES1_E1_2_P_2_entry se55;
    COUNTSTORE_SALES1_E1_2_P_3_entry se56;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se57;
    tuple2_S_L st7;
    COUNTCUSTOMER1_L2_1_entry se58;
    COUNTCUSTOMER1_L2_1_entry se59;
    COUNTCUSTOMER1_L2_2_entry se60;
    COUNTCUSTOMER1_L2_1_entry se61;
    COUNTCUSTOMER1_L3_2_entry se62;
    COUNTCUSTOMER1_L2_1_entry se63;
    COUNTCUSTOMER1_L4_2_entry se64;
    COUNTCUSTOMER_ADDRESS2_entry se65;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se66;
    COUNTCUSTOMER1_L2_1_entry se67;
    COUNTCUSTOMER1_L2_2_entry se68;
    COUNTCUSTOMER1_L2_1_entry se69;
    COUNTCUSTOMER1_L3_2_entry se70;
    COUNTCUSTOMER1_L2_1_entry se71;
    COUNTCUSTOMER1_L4_2_entry se72;
    COUNTCUSTOMER1_L2_1_entry se73;
    COUNTCUSTOMER_ADDRESS2_entry se74;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se75;
    tuple2_S_L st8;
    COUNTCUSTOMER1_L2_1_entry se76;
    COUNTSTORE_SALES1_E1_2_P_1_entry se77;
    COUNTSTORE_SALES1_E1_2_P_2_entry se78;
    COUNTSTORE_SALES1_E1_2_P_3_entry se79;
    COUNTSTORE_SALES1_E1_2_DELTA_entry se80;
    tuple2_S_L st9;
    COUNTCUSTOMER1_L2_1_entry se81;
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
    COUNTCUSTOMER1_L4_2_entry se97;
    COUNTSTORE_SALES1_E1_2_P_1_entry se98;
    COUNTSTORE_SALES1_E1_2_P_2_entry se99;
    COUNTSTORE_SALES1_E1_2_P_3_entry se100;
    COUNTSTORE_SALES9_L4_3_DELTA_entry se101;
    COUNTCUSTOMER1_L2_1_entry se102;
    COUNTCUSTOMER_ADDRESS2_entry se103;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se104;
    COUNTCUSTOMER1_L2_1_entry se105;
    COUNTCUSTOMER1_L2_2_entry se106;
    COUNTSTORE_SALES1_E1_2_P_1_entry se107;
    COUNTSTORE_SALES1_E1_2_P_2_entry se108;
    COUNTSTORE_SALES1_E1_2_P_3_entry se109;
    COUNTSTORE_SALES9_L2_3_DELTA_entry se110;
    COUNTCUSTOMER1_L2_1_entry se111;
    COUNTCUSTOMER1_L2_1_entry se112;
    COUNTCUSTOMER1_L3_2_entry se113;
    COUNTSTORE_SALES1_E1_2_P_1_entry se114;
    COUNTSTORE_SALES1_E1_2_P_2_entry se115;
    COUNTSTORE_SALES1_E1_2_P_3_entry se116;
    COUNTSTORE_SALES9_L3_3_DELTA_entry se117;
    COUNTCUSTOMER1_L2_1_entry se118;
    COUNTCUSTOMER1_L2_1_entry se119;
    COUNTCUSTOMER1_L4_2_entry se120;
    COUNTSTORE_SALES1_E1_2_P_1_entry se121;
    COUNTSTORE_SALES1_E1_2_P_2_entry se122;
    COUNTSTORE_SALES1_E1_2_P_3_entry se123;
    COUNTSTORE_SALES9_L4_3_DELTA_entry se124;
    COUNTCUSTOMER1_L2_1_entry se125;
    COUNTCUSTOMER1_L2_1_entry se126;
    COUNTCUSTOMER_ADDRESS2_entry se127;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se128;
    COUNTSTORE_SALES1_E1_2_P_1_entry se129;
    COUNTSTORE_SALES1_E1_2_P_2_entry se130;
    COUNTSTORE_SALES1_E1_2_P_3_entry se131;
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry se132;
    COUNTSTORE_SALES1_E1_2_P_1_entry se133;
    COUNTSTORE_SALES1_E1_2_P_3_entry se134;
    COUNTCUSTOMER1_E1_1_entry se135;
    COUNTSTORE_SALES1_E1_2_P_1_entry se136;
    COUNTSTORE_SALES1_E1_2_P_2_entry se137;
    COUNTSTORE_SALES1_E1_2_P_3_entry se138;
    COUNTCUSTOMER1_L2_1_entry se139;
    COUNTCUSTOMER1_E1_1STORE1_entry se140;
    COUNTSTORE_SALES1_E1_2_P_1_entry se141;
    COUNTSTORE_SALES1_E1_2_P_3_entry se142;
    COUNTCUSTOMER1_L2_1_entry se143;
    COUNTCUSTOMER1_L2_2_entry se144;
    COUNTSTORE_SALES1_E1_2_P_1_entry se145;
    COUNTSTORE_SALES1_E1_2_P_2_entry se146;
    COUNTSTORE_SALES1_E1_2_P_3_entry se147;
    COUNTCUSTOMER1_L2_2STORE1_entry se148;
    COUNTSTORE_SALES1_E1_2_P_1_entry se149;
    COUNTSTORE_SALES1_E1_2_P_3_entry se150;
    COUNTCUSTOMER1_L3_2_entry se151;
    COUNTSTORE_SALES1_E1_2_P_1_entry se152;
    COUNTSTORE_SALES1_E1_2_P_2_entry se153;
    COUNTSTORE_SALES1_E1_2_P_3_entry se154;
    COUNTCUSTOMER1_L3_2STORE1_entry se155;
    COUNTSTORE_SALES1_E1_2_P_1_entry se156;
    COUNTSTORE_SALES1_E1_2_P_3_entry se157;
    COUNTCUSTOMER1_L4_2_entry se158;
    COUNTSTORE_SALES1_E1_2_P_1_entry se159;
    COUNTSTORE_SALES1_E1_2_P_2_entry se160;
    COUNTSTORE_SALES1_E1_2_P_3_entry se161;
    COUNTCUSTOMER1_L4_2STORE1_entry se162;
    COUNTSTORE_SALES1_E1_2_P_1_entry se163;
    COUNTSTORE_SALES1_E1_2_P_3_entry se164;
    COUNTCUSTOMER1_DELTA_entry se165;
    COUNT_entry se166;
    COUNTCUSTOMER1_L2_1_entry se167;
    COUNTCUSTOMER1_L4_2_entry se168;
    COUNTCUSTOMER1_L2_1_entry se169;
    COUNTCUSTOMER1_L3_2_entry se170;
    COUNTCUSTOMER1_L2_1_entry se171;
    COUNTCUSTOMER1_L2_2_entry se172;
    COUNTCUSTOMER1_E1_1_entry se173;
    COUNTCUSTOMER1_entry se174;
    COUNTCUSTOMER_ADDRESS1_entry se175;
    COUNTCUSTOMER_ADDRESS2_entry se176;
    COUNTCUSTOMER1_entry se177;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se178;
    COUNTCUSTOMER_ADDRESS2_DOMAIN1_entry se179;
    COUNTCUSTOMER_ADDRESS1_DELTA_entry se180;
    COUNT_entry se181;
    COUNTCUSTOMER1_L2_2_entry se182;
    COUNTCUSTOMER1_L2_1_entry se183;
    COUNTCUSTOMER1_L3_2_entry se184;
    COUNTCUSTOMER1_L2_1_entry se185;
    COUNTCUSTOMER1_L4_2_entry se186;
    COUNTCUSTOMER1_L2_1_entry se187;
    COUNTCUSTOMER1_E1_1_entry se188;
    COUNTCUSTOMER_ADDRESS1_entry se189;
    COUNTCUSTOMER1_L2_1_entry se190;
    COUNTCUSTOMER1_L2_2_entry se191;
    COUNTCUSTOMER1_L2_1_entry se192;
    COUNTCUSTOMER1_L3_2_entry se193;
    COUNTCUSTOMER1_L2_1_entry se194;
    COUNTCUSTOMER1_L4_2_entry se195;
    COUNTCUSTOMER1_L2_1_entry se196;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se197;
    COUNTCUSTOMER1_L2_1_entry se198;
    COUNTCUSTOMER1_L2_2_entry se199;
    COUNTCUSTOMER1_L2_1_entry se200;
    COUNTCUSTOMER1_L3_2_entry se201;
    COUNTCUSTOMER1_L2_1_entry se202;
    COUNTCUSTOMER1_L4_2_entry se203;
    COUNTCUSTOMER1_L2_1_entry se204;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se205;
    COUNTCUSTOMER_ADDRESS1_entry se206;
    COUNTCUSTOMER1_L2_1_entry se207;
    tuple2_L_L st10;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se208;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se209;
    tuple2_L_L st11;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se210;
    COUNTCUSTOMER1_L2_2_entry se211;
    COUNTCUSTOMER1_L2_1_entry se212;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se213;
    COUNTCUSTOMER1_L2_2_entry se214;
    COUNTCUSTOMER1_L3_2_entry se215;
    COUNTCUSTOMER1_L2_1_entry se216;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se217;
    COUNTCUSTOMER1_L3_2_entry se218;
    COUNTCUSTOMER1_L4_2_entry se219;
    COUNTCUSTOMER1_L2_1_entry se220;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se221;
    COUNTCUSTOMER1_L4_2_entry se222;
    COUNTCUSTOMER1_L2_1_entry se223;
    tuple2_L_L st12;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se224;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se225;
    tuple2_L_L st13;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se226;
    COUNTCUSTOMER1_L2_2_entry se227;
    COUNTCUSTOMER1_L2_1_entry se228;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se229;
    COUNTCUSTOMER1_L2_2_entry se230;
    COUNTCUSTOMER1_L3_2_entry se231;
    COUNTCUSTOMER1_L2_1_entry se232;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se233;
    COUNTCUSTOMER1_L3_2_entry se234;
    COUNTCUSTOMER1_L4_2_entry se235;
    COUNTCUSTOMER1_L2_1_entry se236;
    COUNTCUSTOMER_ADDRESS6_E1_3_DELTA_entry se237;
    COUNTCUSTOMER1_L4_2_entry se238;
    COUNTCUSTOMER_ADDRESS1_entry se239;
    COUNTCUSTOMER_ADDRESS2_entry se240;
    COUNTCUSTOMER_ADDRESS1_entry se241;
    COUNTCUSTOMER1_entry se242;
    COUNTCUSTOMER1_E1_1_entry se243;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se244;
    COUNTCUSTOMER1_E1_1STORE1_entry se245;
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry se246;
    COUNTCUSTOMER1_L2_1_entry se247;
    COUNTSTORE_SALES1_E1_2_P_2STORE1_DELTA_entry se248;
    COUNTSTORE_SALES1_E1_2_P_2_entry se249;
    COUNTCUSTOMER_ADDRESS2_E1_2_entry se250;
    COUNTCUSTOMER_ADDRESS2_E1_2STORE1_entry se251;
    COUNTCUSTOMER1_E1_1_entry se252;
    COUNTCUSTOMER1_E1_1STORE1_entry se253;
    COUNTCUSTOMER1_L2_2_entry se254;
    COUNTCUSTOMER1_L2_2STORE1_entry se255;
    COUNTCUSTOMER1_L3_2_entry se256;
    COUNTCUSTOMER1_L3_2STORE1_entry se257;
    COUNTCUSTOMER1_L4_2_entry se258;
    COUNTCUSTOMER1_L4_2STORE1_entry se259;
    COUNT_entry se260;
    COUNTCUSTOMER1_L2_1_entry se261;
    COUNTCUSTOMER1_L4_2_entry se262;
    COUNTCUSTOMER1_L2_1_entry se263;
    COUNTCUSTOMER1_L3_2_entry se264;
    COUNTCUSTOMER1_L2_1_entry se265;
    COUNTCUSTOMER1_L2_2_entry se266;
    COUNTCUSTOMER1_E1_1_entry se267;
    COUNTSTORE_SALES1_E1_2_P_1_entry se268;
    COUNTSTORE_SALES1_E1_2_P_3_entry se269;
  
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
    COUNTSTORE_SALES9_L4_3_DELTA_map COUNTSTORE_SALES9_L4_3_DELTA;
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
    COUNTCUSTOMER1_L4_2_map COUNTCUSTOMER1_L4_2;
    COUNTCUSTOMER1_L4_2STORE1_map COUNTCUSTOMER1_L4_2STORE1;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_CUSTOMER_ADDRESS_map DELTA_CUSTOMER_ADDRESS;
    DELTA_STORE_map DELTA_STORE;
    MultiHashMap<tuple8_SDDDSSS_L,long,HashIndex<tuple8_SDDDSSS_L,long> > _c1;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c4;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > _c6;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c3;
    MultiHashMap<tuple4_LLS_L,long,HashIndex<tuple4_LLS_L,long> > _c2;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > _c5;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c2;
  
  };

}
