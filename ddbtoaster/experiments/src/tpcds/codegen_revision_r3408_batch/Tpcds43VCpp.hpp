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
    FORCE_INLINE DATE_DIM_entry& modify614(const long c6, const STRING_TYPE& c14) { DATE_DIM_D_YEAR = c6; DATE_DIM_D_DAY_NAME = c14;  return *this; }
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
  
  struct DATE_DIM_mapkey614_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_YEAR);
      hash_combine(h, e.DATE_DIM_D_DAY_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR && x.DATE_DIM_D_DAY_NAME == y.DATE_DIM_D_DAY_NAME;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey614_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey614_idxfn,false> HashIndex_DATE_DIM_map_614;
  
  struct SUN_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit SUN_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit SUN_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    SUN_SALES_entry(const SUN_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALES_entry& x, const SUN_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<SUN_SALES_entry,DOUBLE_TYPE,
    HashIndex<SUN_SALES_entry,DOUBLE_TYPE,SUN_SALES_mapkey01_idxfn,true>
  > SUN_SALES_map;
  typedef HashIndex<SUN_SALES_entry,DOUBLE_TYPE,SUN_SALES_mapkey01_idxfn,true> HashIndex_SUN_SALES_map_01;
  
  struct SUN_SALESSTORE1_DELTA_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STORE_ID; STRING_TYPE STORE_S_STORE_NAME; long __av; 
    explicit SUN_SALESSTORE1_DELTA_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_STORE_ID = ""; STORE_S_STORE_NAME = ""; __av = 0L; */ }
    explicit SUN_SALESSTORE1_DELTA_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STORE_ID = c1; STORE_S_STORE_NAME = c2; __av = c3; }
    SUN_SALESSTORE1_DELTA_entry(const SUN_SALESSTORE1_DELTA_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STORE_ID = c1; STORE_S_STORE_NAME = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STORE_ID);
      hash_combine(h, e.STORE_S_STORE_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE1_DELTA_entry& x, const SUN_SALESSTORE1_DELTA_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID && x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE1_DELTA_entry,long,
    HashIndex<SUN_SALESSTORE1_DELTA_entry,long,SUN_SALESSTORE1_DELTA_mapkey012_idxfn,true>
  > SUN_SALESSTORE1_DELTA_map;
  typedef HashIndex<SUN_SALESSTORE1_DELTA_entry,long,SUN_SALESSTORE1_DELTA_mapkey012_idxfn,true> HashIndex_SUN_SALESSTORE1_DELTA_map_012;
  
  struct SUN_SALESSTORE1_entry {
    long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit SUN_SALESSTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit SUN_SALESSTORE1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    SUN_SALESSTORE1_entry(const SUN_SALESSTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE1_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE1_entry& x, const SUN_SALESSTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE1_entry,DOUBLE_TYPE,
    HashIndex<SUN_SALESSTORE1_entry,DOUBLE_TYPE,SUN_SALESSTORE1_mapkey0_idxfn,true>
  > SUN_SALESSTORE1_map;
  typedef HashIndex<SUN_SALESSTORE1_entry,DOUBLE_TYPE,SUN_SALESSTORE1_mapkey0_idxfn,true> HashIndex_SUN_SALESSTORE1_map_0;
  
  struct SUN_SALESSTORE_SALES1_DELTA_entry {
    long DATE_DIM_D_DATE_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit SUN_SALESSTORE_SALES1_DELTA_entry() { /*DATE_DIM_D_DATE_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit SUN_SALESSTORE_SALES1_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { DATE_DIM_D_DATE_SK = c0; STORE_SALES_SS_STORE_SK = c1; __av = c2; }
    SUN_SALESSTORE_SALES1_DELTA_entry(const SUN_SALESSTORE_SALES1_DELTA_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE_SALES1_DELTA_entry& modify(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE_SALES1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE_SALES1_DELTA_entry& x, const SUN_SALESSTORE_SALES1_DELTA_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<SUN_SALESSTORE_SALES1_DELTA_entry,DOUBLE_TYPE,SUN_SALESSTORE_SALES1_DELTA_mapkey01_idxfn,true>
  > SUN_SALESSTORE_SALES1_DELTA_map;
  typedef HashIndex<SUN_SALESSTORE_SALES1_DELTA_entry,DOUBLE_TYPE,SUN_SALESSTORE_SALES1_DELTA_mapkey01_idxfn,true> HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01;
  
  struct SUN_SALESSTORE_SALES1_P_1_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STORE_ID; STRING_TYPE STORE_S_STORE_NAME; long __av; 
    explicit SUN_SALESSTORE_SALES1_P_1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_STORE_ID = ""; STORE_S_STORE_NAME = ""; __av = 0L; */ }
    explicit SUN_SALESSTORE_SALES1_P_1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STORE_ID = c1; STORE_S_STORE_NAME = c2; __av = c3; }
    SUN_SALESSTORE_SALES1_P_1_entry(const SUN_SALESSTORE_SALES1_P_1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE_SALES1_P_1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STORE_ID = c1; STORE_S_STORE_NAME = c2;  return *this; }
    FORCE_INLINE SUN_SALESSTORE_SALES1_P_1_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE_SALES1_P_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STORE_ID);
      hash_combine(h, e.STORE_S_STORE_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE_SALES1_P_1_entry& x, const SUN_SALESSTORE_SALES1_P_1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID && x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME;
    }
  };
  
  struct SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE_SALES1_P_1_entry& x, const SUN_SALESSTORE_SALES1_P_1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE_SALES1_P_1_entry,long,
    HashIndex<SUN_SALESSTORE_SALES1_P_1_entry,long,SUN_SALESSTORE_SALES1_P_1_mapkey012_idxfn,true>,
    HashIndex<SUN_SALESSTORE_SALES1_P_1_entry,long,SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn,false>
  > SUN_SALESSTORE_SALES1_P_1_map;
  typedef HashIndex<SUN_SALESSTORE_SALES1_P_1_entry,long,SUN_SALESSTORE_SALES1_P_1_mapkey012_idxfn,true> HashIndex_SUN_SALESSTORE_SALES1_P_1_map_012;
  typedef HashIndex<SUN_SALESSTORE_SALES1_P_1_entry,long,SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn,false> HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0;
  
  struct SUN_SALESSTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit SUN_SALESSTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit SUN_SALESSTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    SUN_SALESSTORE_SALES1_P_2_entry(const SUN_SALESSTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE_SALES1_P_2_entry& x, const SUN_SALESSTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE_SALES1_P_2_entry,long,
    HashIndex<SUN_SALESSTORE_SALES1_P_2_entry,long,SUN_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true>
  > SUN_SALESSTORE_SALES1_P_2_map;
  typedef HashIndex<SUN_SALESSTORE_SALES1_P_2_entry,long,SUN_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_SUN_SALESSTORE_SALES1_P_2_map_0;
  
  struct MON_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit MON_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit MON_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    MON_SALES_entry(const MON_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE MON_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MON_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MON_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const MON_SALES_entry& x, const MON_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<MON_SALES_entry,DOUBLE_TYPE,
    HashIndex<MON_SALES_entry,DOUBLE_TYPE,MON_SALES_mapkey01_idxfn,true>
  > MON_SALES_map;
  typedef HashIndex<MON_SALES_entry,DOUBLE_TYPE,MON_SALES_mapkey01_idxfn,true> HashIndex_MON_SALES_map_01;
  
  struct MON_SALESSTORE1_entry {
    long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit MON_SALESSTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit MON_SALESSTORE1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    MON_SALESSTORE1_entry(const MON_SALESSTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE MON_SALESSTORE1_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MON_SALESSTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MON_SALESSTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const MON_SALESSTORE1_entry& x, const MON_SALESSTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<MON_SALESSTORE1_entry,DOUBLE_TYPE,
    HashIndex<MON_SALESSTORE1_entry,DOUBLE_TYPE,MON_SALESSTORE1_mapkey0_idxfn,true>
  > MON_SALESSTORE1_map;
  typedef HashIndex<MON_SALESSTORE1_entry,DOUBLE_TYPE,MON_SALESSTORE1_mapkey0_idxfn,true> HashIndex_MON_SALESSTORE1_map_0;
  
  struct MON_SALESSTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit MON_SALESSTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit MON_SALESSTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    MON_SALESSTORE_SALES1_P_2_entry(const MON_SALESSTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE MON_SALESSTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MON_SALESSTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MON_SALESSTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const MON_SALESSTORE_SALES1_P_2_entry& x, const MON_SALESSTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<MON_SALESSTORE_SALES1_P_2_entry,long,
    HashIndex<MON_SALESSTORE_SALES1_P_2_entry,long,MON_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true>
  > MON_SALESSTORE_SALES1_P_2_map;
  typedef HashIndex<MON_SALESSTORE_SALES1_P_2_entry,long,MON_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_MON_SALESSTORE_SALES1_P_2_map_0;
  
  struct TUE_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit TUE_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit TUE_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    TUE_SALES_entry(const TUE_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE TUE_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TUE_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TUE_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const TUE_SALES_entry& x, const TUE_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<TUE_SALES_entry,DOUBLE_TYPE,
    HashIndex<TUE_SALES_entry,DOUBLE_TYPE,TUE_SALES_mapkey01_idxfn,true>
  > TUE_SALES_map;
  typedef HashIndex<TUE_SALES_entry,DOUBLE_TYPE,TUE_SALES_mapkey01_idxfn,true> HashIndex_TUE_SALES_map_01;
  
  struct TUE_SALESSTORE1_entry {
    long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit TUE_SALESSTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit TUE_SALESSTORE1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    TUE_SALESSTORE1_entry(const TUE_SALESSTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE TUE_SALESSTORE1_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TUE_SALESSTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TUE_SALESSTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const TUE_SALESSTORE1_entry& x, const TUE_SALESSTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<TUE_SALESSTORE1_entry,DOUBLE_TYPE,
    HashIndex<TUE_SALESSTORE1_entry,DOUBLE_TYPE,TUE_SALESSTORE1_mapkey0_idxfn,true>
  > TUE_SALESSTORE1_map;
  typedef HashIndex<TUE_SALESSTORE1_entry,DOUBLE_TYPE,TUE_SALESSTORE1_mapkey0_idxfn,true> HashIndex_TUE_SALESSTORE1_map_0;
  
  struct TUE_SALESSTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit TUE_SALESSTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit TUE_SALESSTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    TUE_SALESSTORE_SALES1_P_2_entry(const TUE_SALESSTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE TUE_SALESSTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TUE_SALESSTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TUE_SALESSTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const TUE_SALESSTORE_SALES1_P_2_entry& x, const TUE_SALESSTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<TUE_SALESSTORE_SALES1_P_2_entry,long,
    HashIndex<TUE_SALESSTORE_SALES1_P_2_entry,long,TUE_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true>
  > TUE_SALESSTORE_SALES1_P_2_map;
  typedef HashIndex<TUE_SALESSTORE_SALES1_P_2_entry,long,TUE_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_TUE_SALESSTORE_SALES1_P_2_map_0;
  
  struct WED_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit WED_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit WED_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    WED_SALES_entry(const WED_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE WED_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct WED_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const WED_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const WED_SALES_entry& x, const WED_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<WED_SALES_entry,DOUBLE_TYPE,
    HashIndex<WED_SALES_entry,DOUBLE_TYPE,WED_SALES_mapkey01_idxfn,true>
  > WED_SALES_map;
  typedef HashIndex<WED_SALES_entry,DOUBLE_TYPE,WED_SALES_mapkey01_idxfn,true> HashIndex_WED_SALES_map_01;
  
  struct WED_SALESSTORE1_entry {
    long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit WED_SALESSTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit WED_SALESSTORE1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    WED_SALESSTORE1_entry(const WED_SALESSTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE WED_SALESSTORE1_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct WED_SALESSTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const WED_SALESSTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const WED_SALESSTORE1_entry& x, const WED_SALESSTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<WED_SALESSTORE1_entry,DOUBLE_TYPE,
    HashIndex<WED_SALESSTORE1_entry,DOUBLE_TYPE,WED_SALESSTORE1_mapkey0_idxfn,true>
  > WED_SALESSTORE1_map;
  typedef HashIndex<WED_SALESSTORE1_entry,DOUBLE_TYPE,WED_SALESSTORE1_mapkey0_idxfn,true> HashIndex_WED_SALESSTORE1_map_0;
  
  struct WED_SALESSTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit WED_SALESSTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit WED_SALESSTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    WED_SALESSTORE_SALES1_P_2_entry(const WED_SALESSTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE WED_SALESSTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct WED_SALESSTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const WED_SALESSTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const WED_SALESSTORE_SALES1_P_2_entry& x, const WED_SALESSTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<WED_SALESSTORE_SALES1_P_2_entry,long,
    HashIndex<WED_SALESSTORE_SALES1_P_2_entry,long,WED_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true>
  > WED_SALESSTORE_SALES1_P_2_map;
  typedef HashIndex<WED_SALESSTORE_SALES1_P_2_entry,long,WED_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_WED_SALESSTORE_SALES1_P_2_map_0;
  
  struct THU_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit THU_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit THU_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    THU_SALES_entry(const THU_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE THU_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct THU_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const THU_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const THU_SALES_entry& x, const THU_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<THU_SALES_entry,DOUBLE_TYPE,
    HashIndex<THU_SALES_entry,DOUBLE_TYPE,THU_SALES_mapkey01_idxfn,true>
  > THU_SALES_map;
  typedef HashIndex<THU_SALES_entry,DOUBLE_TYPE,THU_SALES_mapkey01_idxfn,true> HashIndex_THU_SALES_map_01;
  
  struct THU_SALESSTORE1_entry {
    long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit THU_SALESSTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit THU_SALESSTORE1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    THU_SALESSTORE1_entry(const THU_SALESSTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE THU_SALESSTORE1_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct THU_SALESSTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const THU_SALESSTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const THU_SALESSTORE1_entry& x, const THU_SALESSTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<THU_SALESSTORE1_entry,DOUBLE_TYPE,
    HashIndex<THU_SALESSTORE1_entry,DOUBLE_TYPE,THU_SALESSTORE1_mapkey0_idxfn,true>
  > THU_SALESSTORE1_map;
  typedef HashIndex<THU_SALESSTORE1_entry,DOUBLE_TYPE,THU_SALESSTORE1_mapkey0_idxfn,true> HashIndex_THU_SALESSTORE1_map_0;
  
  struct THU_SALESSTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit THU_SALESSTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit THU_SALESSTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    THU_SALESSTORE_SALES1_P_2_entry(const THU_SALESSTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE THU_SALESSTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct THU_SALESSTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const THU_SALESSTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const THU_SALESSTORE_SALES1_P_2_entry& x, const THU_SALESSTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<THU_SALESSTORE_SALES1_P_2_entry,long,
    HashIndex<THU_SALESSTORE_SALES1_P_2_entry,long,THU_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true>
  > THU_SALESSTORE_SALES1_P_2_map;
  typedef HashIndex<THU_SALESSTORE_SALES1_P_2_entry,long,THU_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_THU_SALESSTORE_SALES1_P_2_map_0;
  
  struct FRI_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit FRI_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit FRI_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    FRI_SALES_entry(const FRI_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE FRI_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct FRI_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const FRI_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const FRI_SALES_entry& x, const FRI_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<FRI_SALES_entry,DOUBLE_TYPE,
    HashIndex<FRI_SALES_entry,DOUBLE_TYPE,FRI_SALES_mapkey01_idxfn,true>
  > FRI_SALES_map;
  typedef HashIndex<FRI_SALES_entry,DOUBLE_TYPE,FRI_SALES_mapkey01_idxfn,true> HashIndex_FRI_SALES_map_01;
  
  struct FRI_SALESSTORE1_entry {
    long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit FRI_SALESSTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit FRI_SALESSTORE1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    FRI_SALESSTORE1_entry(const FRI_SALESSTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE FRI_SALESSTORE1_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct FRI_SALESSTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const FRI_SALESSTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const FRI_SALESSTORE1_entry& x, const FRI_SALESSTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<FRI_SALESSTORE1_entry,DOUBLE_TYPE,
    HashIndex<FRI_SALESSTORE1_entry,DOUBLE_TYPE,FRI_SALESSTORE1_mapkey0_idxfn,true>
  > FRI_SALESSTORE1_map;
  typedef HashIndex<FRI_SALESSTORE1_entry,DOUBLE_TYPE,FRI_SALESSTORE1_mapkey0_idxfn,true> HashIndex_FRI_SALESSTORE1_map_0;
  
  struct FRI_SALESSTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit FRI_SALESSTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit FRI_SALESSTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    FRI_SALESSTORE_SALES1_P_2_entry(const FRI_SALESSTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE FRI_SALESSTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct FRI_SALESSTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const FRI_SALESSTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const FRI_SALESSTORE_SALES1_P_2_entry& x, const FRI_SALESSTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<FRI_SALESSTORE_SALES1_P_2_entry,long,
    HashIndex<FRI_SALESSTORE_SALES1_P_2_entry,long,FRI_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true>
  > FRI_SALESSTORE_SALES1_P_2_map;
  typedef HashIndex<FRI_SALESSTORE_SALES1_P_2_entry,long,FRI_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_FRI_SALESSTORE_SALES1_P_2_map_0;
  
  struct SAT_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit SAT_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit SAT_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    SAT_SALES_entry(const SAT_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE SAT_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SAT_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SAT_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const SAT_SALES_entry& x, const SAT_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<SAT_SALES_entry,DOUBLE_TYPE,
    HashIndex<SAT_SALES_entry,DOUBLE_TYPE,SAT_SALES_mapkey01_idxfn,true>
  > SAT_SALES_map;
  typedef HashIndex<SAT_SALES_entry,DOUBLE_TYPE,SAT_SALES_mapkey01_idxfn,true> HashIndex_SAT_SALES_map_01;
  
  struct SAT_SALESSTORE1_entry {
    long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit SAT_SALESSTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit SAT_SALESSTORE1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_STORE_SK = c0; __av = c1; }
    SAT_SALESSTORE1_entry(const SAT_SALESSTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE SAT_SALESSTORE1_entry& modify(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SAT_SALESSTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SAT_SALESSTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SAT_SALESSTORE1_entry& x, const SAT_SALESSTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<SAT_SALESSTORE1_entry,DOUBLE_TYPE,
    HashIndex<SAT_SALESSTORE1_entry,DOUBLE_TYPE,SAT_SALESSTORE1_mapkey0_idxfn,true>
  > SAT_SALESSTORE1_map;
  typedef HashIndex<SAT_SALESSTORE1_entry,DOUBLE_TYPE,SAT_SALESSTORE1_mapkey0_idxfn,true> HashIndex_SAT_SALESSTORE1_map_0;
  
  struct SAT_SALESSTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit SAT_SALESSTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit SAT_SALESSTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    SAT_SALESSTORE_SALES1_P_2_entry(const SAT_SALESSTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE SAT_SALESSTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SAT_SALESSTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SAT_SALESSTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SAT_SALESSTORE_SALES1_P_2_entry& x, const SAT_SALESSTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<SAT_SALESSTORE_SALES1_P_2_entry,long,
    HashIndex<SAT_SALESSTORE_SALES1_P_2_entry,long,SAT_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true>
  > SAT_SALESSTORE_SALES1_P_2_map;
  typedef HashIndex<SAT_SALESSTORE_SALES1_P_2_entry,long,SAT_SALESSTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_SAT_SALESSTORE_SALES1_P_2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const SUN_SALES_map& _SUN_SALES = get_SUN_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUN_SALES), _SUN_SALES, "\t");
      ar << "\n";
      const MON_SALES_map& _MON_SALES = get_MON_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(MON_SALES), _MON_SALES, "\t");
      ar << "\n";
      const TUE_SALES_map& _TUE_SALES = get_TUE_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(TUE_SALES), _TUE_SALES, "\t");
      ar << "\n";
      const WED_SALES_map& _WED_SALES = get_WED_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(WED_SALES), _WED_SALES, "\t");
      ar << "\n";
      const THU_SALES_map& _THU_SALES = get_THU_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(THU_SALES), _THU_SALES, "\t");
      ar << "\n";
      const FRI_SALES_map& _FRI_SALES = get_FRI_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(FRI_SALES), _FRI_SALES, "\t");
      ar << "\n";
      const SAT_SALES_map& _SAT_SALES = get_SAT_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SAT_SALES), _SAT_SALES, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const SUN_SALES_map& get_SUN_SALES() const {
      return SUN_SALES;
    
    }
    const MON_SALES_map& get_MON_SALES() const {
      return MON_SALES;
    
    }
    const TUE_SALES_map& get_TUE_SALES() const {
      return TUE_SALES;
    
    }
    const WED_SALES_map& get_WED_SALES() const {
      return WED_SALES;
    
    }
    const THU_SALES_map& get_THU_SALES() const {
      return THU_SALES;
    
    }
    const FRI_SALES_map& get_FRI_SALES() const {
      return FRI_SALES;
    
    }
    const SAT_SALES_map& get_SAT_SALES() const {
      return SAT_SALES;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    SUN_SALES_map SUN_SALES;
    MON_SALES_map MON_SALES;
    TUE_SALES_map TUE_SALES;
    WED_SALES_map WED_SALES;
    THU_SALES_map THU_SALES;
    FRI_SALES_map FRI_SALES;
    SAT_SALES_map SAT_SALES;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c6 = STRING_TYPE("Friday");
      c5 = STRING_TYPE("Thursday");
      c2 = STRING_TYPE("Monday");
      c7 = STRING_TYPE("Saturday");
      c1 = STRING_TYPE("Sunday");
      c4 = STRING_TYPE("Wednesday");
      c3 = STRING_TYPE("Tuesday");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_DATE_DIM(const long date_dim_d_date_sk, const STRING_TYPE date_dim_d_date_id, const date date_dim_d_date, const long date_dim_d_month_seq, const long date_dim_d_week_seq, const long date_dim_d_quarter_seq, const long date_dim_d_year, const long date_dim_d_dow, const long date_dim_d_moy, const long date_dim_d_dom, const long date_dim_d_qoy, const long date_dim_d_fy_year, const long date_dim_d_fy_quarter_seq, const long date_dim_d_fy_week_seq, const STRING_TYPE date_dim_d_day_name, const STRING_TYPE date_dim_d_quarter_name, const STRING_TYPE date_dim_d_holiday, const STRING_TYPE date_dim_d_weekend, const STRING_TYPE date_dim_d_following_holiday, const long date_dim_d_first_dom, const long date_dim_d_last_dom, const long date_dim_d_same_day_ly, const long date_dim_d_same_day_lq, const STRING_TYPE date_dim_d_current_day, const STRING_TYPE date_dim_d_current_week, const STRING_TYPE date_dim_d_current_month, const STRING_TYPE date_dim_d_current_quarter, const STRING_TYPE date_dim_d_current_year) {
      DATE_DIM_entry e(date_dim_d_date_sk, date_dim_d_date_id, date_dim_d_date, date_dim_d_month_seq, date_dim_d_week_seq, date_dim_d_quarter_seq, date_dim_d_year, date_dim_d_dow, date_dim_d_moy, date_dim_d_dom, date_dim_d_qoy, date_dim_d_fy_year, date_dim_d_fy_quarter_seq, date_dim_d_fy_week_seq, date_dim_d_day_name, date_dim_d_quarter_name, date_dim_d_holiday, date_dim_d_weekend, date_dim_d_following_holiday, date_dim_d_first_dom, date_dim_d_last_dom, date_dim_d_same_day_ly, date_dim_d_same_day_lq, date_dim_d_current_day, date_dim_d_current_week, date_dim_d_current_month, date_dim_d_current_quarter, date_dim_d_current_year, 1L);
      DATE_DIM.addOrDelOnZero(e,1L);
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

        SUN_SALESSTORE_SALES1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_STORE_SALES.size; i++) 
          {
                long date_dim_d_date_sk = DELTA_STORE_SALES.ss_sold_date_sk[i];
                // long store_sales_ss_sold_time_sk = DELTA_STORE_SALES.ss_sold_time_sk[i];
                // long store_sales_ss_item_sk = DELTA_STORE_SALES.ss_item_sk[i];
                // long store_sales_ss_customer_sk = DELTA_STORE_SALES.ss_customer_sk[i];
                // long store_sales_ss_cdemo_sk = DELTA_STORE_SALES.ss_cdemo_sk[i];
                // long store_sales_ss_hdemo_sk = DELTA_STORE_SALES.ss_hdemo_sk[i];
                // long store_sales_ss_addr_sk = DELTA_STORE_SALES.ss_addr_sk[i];
                long store_sales_ss_store_sk = DELTA_STORE_SALES.ss_store_sk[i];
                // long store_sales_ss_promo_sk = DELTA_STORE_SALES.ss_promo_sk[i];
                // long store_sales_ss_ticket_number = DELTA_STORE_SALES.ss_ticket_number[i];
                // long store_sales_ss_quantity = DELTA_STORE_SALES.ss_quantity[i];
                // DOUBLE_TYPE store_sales_ss_wholesale_cost = DELTA_STORE_SALES.ss_wholesale_cost[i];
                // DOUBLE_TYPE store_sales_ss_list_price = DELTA_STORE_SALES.ss_list_price[i];
                DOUBLE_TYPE store_sales_ss_sales_price = DELTA_STORE_SALES.ss_sales_price[i];
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
                SUN_SALESSTORE_SALES1_DELTA.addOrDelOnZero(se1.modify(date_dim_d_date_sk,store_sales_ss_store_sk),(v1 * store_sales_ss_sales_price));
          }
        }

        {  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i2 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n2; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long date_dim_d_date_sk = e2->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e2->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0* i3 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0*>(SUN_SALESSTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h1 = SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::hash(se4.modify0(store_sales_ss_store_sk));
                  HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode* n3 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode*>(i3->slice(se4, h1));
                  SUN_SALESSTORE_SALES1_P_1_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      STRING_TYPE store_s_store_id = e3->STORE_S_STORE_ID;
                      STRING_TYPE store_s_store_name = e3->STORE_S_STORE_NAME;
                      long v3 = e3->__av;
                      SUN_SALES.addOrDelOnZero(se2.modify(store_s_store_name,store_s_store_id),(v2 * (SUN_SALESSTORE_SALES1_P_2.getValueOrDefault(se3.modify(date_dim_d_date_sk)) * v3)));
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h1 == n3->hash &&  SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::equals(se4, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i4 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n4; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long date_dim_d_date_sk = e4->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e4->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v4 = e4->__av;
                SUN_SALESSTORE1.addOrDelOnZero(se5.modify(store_sales_ss_store_sk),(v4 * SUN_SALESSTORE_SALES1_P_2.getValueOrDefault(se6.modify(date_dim_d_date_sk))));
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i5 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n5; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long date_dim_d_date_sk = e5->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e5->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v5 = e5->__av;
                { //slice 
                  const HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0* i6 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0*>(SUN_SALESSTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h2 = SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::hash(se9.modify0(store_sales_ss_store_sk));
                  HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode* n6 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode*>(i6->slice(se9, h2));
                  SUN_SALESSTORE_SALES1_P_1_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      STRING_TYPE store_s_store_id = e6->STORE_S_STORE_ID;
                      STRING_TYPE store_s_store_name = e6->STORE_S_STORE_NAME;
                      long v6 = e6->__av;
                      MON_SALES.addOrDelOnZero(se7.modify(store_s_store_name,store_s_store_id),(v5 * (MON_SALESSTORE_SALES1_P_2.getValueOrDefault(se8.modify(date_dim_d_date_sk)) * v6)));
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::equals(se9, *e6)); 
                  }
                }
              n5 = n5->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i7 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n7; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long date_dim_d_date_sk = e7->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e7->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v7 = e7->__av;
                MON_SALESSTORE1.addOrDelOnZero(se10.modify(store_sales_ss_store_sk),(v7 * MON_SALESSTORE_SALES1_P_2.getValueOrDefault(se11.modify(date_dim_d_date_sk))));
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i8 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n8; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long date_dim_d_date_sk = e8->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e8->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v8 = e8->__av;
                { //slice 
                  const HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0* i9 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0*>(SUN_SALESSTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h3 = SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::hash(se14.modify0(store_sales_ss_store_sk));
                  HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode* n9 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode*>(i9->slice(se14, h3));
                  SUN_SALESSTORE_SALES1_P_1_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      STRING_TYPE store_s_store_id = e9->STORE_S_STORE_ID;
                      STRING_TYPE store_s_store_name = e9->STORE_S_STORE_NAME;
                      long v9 = e9->__av;
                      TUE_SALES.addOrDelOnZero(se12.modify(store_s_store_name,store_s_store_id),(v8 * (TUE_SALESSTORE_SALES1_P_2.getValueOrDefault(se13.modify(date_dim_d_date_sk)) * v9)));
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h3 == n9->hash &&  SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::equals(se14, *e9)); 
                  }
                }
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i10 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n10; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long date_dim_d_date_sk = e10->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e10->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v10 = e10->__av;
                TUE_SALESSTORE1.addOrDelOnZero(se15.modify(store_sales_ss_store_sk),(v10 * TUE_SALESSTORE_SALES1_P_2.getValueOrDefault(se16.modify(date_dim_d_date_sk))));
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i11 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n11; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long date_dim_d_date_sk = e11->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e11->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v11 = e11->__av;
                { //slice 
                  const HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0* i12 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0*>(SUN_SALESSTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h4 = SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::hash(se19.modify0(store_sales_ss_store_sk));
                  HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode* n12 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode*>(i12->slice(se19, h4));
                  SUN_SALESSTORE_SALES1_P_1_entry* e12;
                 
                  if (n12 && (e12 = n12->obj)) {
                    do {                
                      STRING_TYPE store_s_store_id = e12->STORE_S_STORE_ID;
                      STRING_TYPE store_s_store_name = e12->STORE_S_STORE_NAME;
                      long v12 = e12->__av;
                      WED_SALES.addOrDelOnZero(se17.modify(store_s_store_name,store_s_store_id),(v11 * (WED_SALESSTORE_SALES1_P_2.getValueOrDefault(se18.modify(date_dim_d_date_sk)) * v12)));
                      n12 = n12->nxt;
                    } while (n12 && (e12 = n12->obj) && h4 == n12->hash &&  SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::equals(se19, *e12)); 
                  }
                }
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i13 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n13; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long date_dim_d_date_sk = e13->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e13->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v13 = e13->__av;
                WED_SALESSTORE1.addOrDelOnZero(se20.modify(store_sales_ss_store_sk),(v13 * WED_SALESSTORE_SALES1_P_2.getValueOrDefault(se21.modify(date_dim_d_date_sk))));
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i14 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n14; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
                long date_dim_d_date_sk = e14->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e14->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v14 = e14->__av;
                { //slice 
                  const HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0* i15 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0*>(SUN_SALESSTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h5 = SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::hash(se24.modify0(store_sales_ss_store_sk));
                  HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode* n15 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode*>(i15->slice(se24, h5));
                  SUN_SALESSTORE_SALES1_P_1_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      STRING_TYPE store_s_store_id = e15->STORE_S_STORE_ID;
                      STRING_TYPE store_s_store_name = e15->STORE_S_STORE_NAME;
                      long v15 = e15->__av;
                      THU_SALES.addOrDelOnZero(se22.modify(store_s_store_name,store_s_store_id),(v14 * (THU_SALESSTORE_SALES1_P_2.getValueOrDefault(se23.modify(date_dim_d_date_sk)) * v15)));
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h5 == n15->hash &&  SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::equals(se24, *e15)); 
                  }
                }
              n14 = n14->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i16 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n16; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long date_dim_d_date_sk = e16->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e16->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v16 = e16->__av;
                THU_SALESSTORE1.addOrDelOnZero(se25.modify(store_sales_ss_store_sk),(v16 * THU_SALESSTORE_SALES1_P_2.getValueOrDefault(se26.modify(date_dim_d_date_sk))));
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i17 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n17; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long date_dim_d_date_sk = e17->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e17->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v17 = e17->__av;
                { //slice 
                  const HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0* i18 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0*>(SUN_SALESSTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h6 = SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::hash(se29.modify0(store_sales_ss_store_sk));
                  HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode* n18 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode*>(i18->slice(se29, h6));
                  SUN_SALESSTORE_SALES1_P_1_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      STRING_TYPE store_s_store_id = e18->STORE_S_STORE_ID;
                      STRING_TYPE store_s_store_name = e18->STORE_S_STORE_NAME;
                      long v18 = e18->__av;
                      FRI_SALES.addOrDelOnZero(se27.modify(store_s_store_name,store_s_store_id),(v17 * (FRI_SALESSTORE_SALES1_P_2.getValueOrDefault(se28.modify(date_dim_d_date_sk)) * v18)));
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h6 == n18->hash &&  SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::equals(se29, *e18)); 
                  }
                }
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i19 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n19; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long date_dim_d_date_sk = e19->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e19->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v19 = e19->__av;
                FRI_SALESSTORE1.addOrDelOnZero(se30.modify(store_sales_ss_store_sk),(v19 * FRI_SALESSTORE_SALES1_P_2.getValueOrDefault(se31.modify(date_dim_d_date_sk))));
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i20 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n20; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e20;
        
          for (size_t i = 0; i < i20->size_; i++)
          {
            n20 = i20->buckets_ + i;
            while (n20 && (e20 = n20->obj))
            {
                long date_dim_d_date_sk = e20->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e20->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v20 = e20->__av;
                { //slice 
                  const HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0* i21 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0*>(SUN_SALESSTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h7 = SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::hash(se34.modify0(store_sales_ss_store_sk));
                  HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode* n21 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_P_1_map_0::IdxNode*>(i21->slice(se34, h7));
                  SUN_SALESSTORE_SALES1_P_1_entry* e21;
                 
                  if (n21 && (e21 = n21->obj)) {
                    do {                
                      STRING_TYPE store_s_store_id = e21->STORE_S_STORE_ID;
                      STRING_TYPE store_s_store_name = e21->STORE_S_STORE_NAME;
                      long v21 = e21->__av;
                      SAT_SALES.addOrDelOnZero(se32.modify(store_s_store_name,store_s_store_id),(v20 * (SAT_SALESSTORE_SALES1_P_2.getValueOrDefault(se33.modify(date_dim_d_date_sk)) * v21)));
                      n21 = n21->nxt;
                    } while (n21 && (e21 = n21->obj) && h7 == n21->hash &&  SUN_SALESSTORE_SALES1_P_1_mapkey0_idxfn::equals(se34, *e21)); 
                  }
                }
              n20 = n20->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01* i22 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01*>(SUN_SALESSTORE_SALES1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE_SALES1_DELTA_map_01::IdxNode* n22; 
          SUN_SALESSTORE_SALES1_DELTA_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                long date_dim_d_date_sk = e22->DATE_DIM_D_DATE_SK;
                long store_sales_ss_store_sk = e22->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v22 = e22->__av;
                SAT_SALESSTORE1.addOrDelOnZero(se35.modify(store_sales_ss_store_sk),(v22 * SAT_SALESSTORE_SALES1_P_2.getValueOrDefault(se36.modify(date_dim_d_date_sk))));
              n22 = n22->nxt;
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

        SUN_SALESSTORE1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_STORE.size; i++) 
          {
                long store_sales_ss_store_sk = DELTA_STORE.s_store_sk[i];
                STRING_TYPE store_s_store_id = DELTA_STORE.s_store_id[i];
                // date store_s_rec_start_date = DELTA_STORE.s_rec_start_date[i];
                // date store_s_rec_end_date = DELTA_STORE.s_rec_end_date[i];
                // long store_s_closed_date_sk = DELTA_STORE.s_closed_date_sk[i];
                STRING_TYPE store_s_store_name = DELTA_STORE.s_store_name[i];
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
                // STRING_TYPE store_s_county = DELTA_STORE.s_county[i];
                // STRING_TYPE store_s_state = DELTA_STORE.s_state[i];
                // STRING_TYPE store_s_zip = DELTA_STORE.s_zip[i];
                // STRING_TYPE store_s_country = DELTA_STORE.s_country[i];
                DOUBLE_TYPE lift1 = DELTA_STORE.s_gmt_offset[i];
                // DOUBLE_TYPE store_s_tax_precentage = DELTA_STORE.s_tax_precentage[i];
                long v23 = 1L;
                (/*if */(lift1 == -6L) ? SUN_SALESSTORE1_DELTA.addOrDelOnZero(se37.modify(store_sales_ss_store_sk,store_s_store_id,store_s_store_name),v23) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i24 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n24; 
          SUN_SALESSTORE1_DELTA_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long store_sales_ss_store_sk = e24->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e24->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e24->STORE_S_STORE_NAME;
                long v24 = e24->__av;
                SUN_SALES.addOrDelOnZero(se38.modify(store_s_store_name,store_s_store_id),(v24 * SUN_SALESSTORE1.getValueOrDefault(se39.modify(store_sales_ss_store_sk))));
              n24 = n24->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i25 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n25; 
          SUN_SALESSTORE1_DELTA_entry* e25;
        
          for (size_t i = 0; i < i25->size_; i++)
          {
            n25 = i25->buckets_ + i;
            while (n25 && (e25 = n25->obj))
            {
                long store_sales_ss_store_sk = e25->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e25->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e25->STORE_S_STORE_NAME;
                long v25 = e25->__av;
                SUN_SALESSTORE_SALES1_P_1.addOrDelOnZero(se40.modify(store_sales_ss_store_sk,store_s_store_id,store_s_store_name),v25);
              n25 = n25->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i26 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n26; 
          SUN_SALESSTORE1_DELTA_entry* e26;
        
          for (size_t i = 0; i < i26->size_; i++)
          {
            n26 = i26->buckets_ + i;
            while (n26 && (e26 = n26->obj))
            {
                long store_sales_ss_store_sk = e26->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e26->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e26->STORE_S_STORE_NAME;
                long v26 = e26->__av;
                MON_SALES.addOrDelOnZero(se41.modify(store_s_store_name,store_s_store_id),(v26 * MON_SALESSTORE1.getValueOrDefault(se42.modify(store_sales_ss_store_sk))));
              n26 = n26->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i27 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n27; 
          SUN_SALESSTORE1_DELTA_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                long store_sales_ss_store_sk = e27->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e27->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e27->STORE_S_STORE_NAME;
                long v27 = e27->__av;
                TUE_SALES.addOrDelOnZero(se43.modify(store_s_store_name,store_s_store_id),(v27 * TUE_SALESSTORE1.getValueOrDefault(se44.modify(store_sales_ss_store_sk))));
              n27 = n27->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i28 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n28; 
          SUN_SALESSTORE1_DELTA_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long store_sales_ss_store_sk = e28->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e28->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e28->STORE_S_STORE_NAME;
                long v28 = e28->__av;
                WED_SALES.addOrDelOnZero(se45.modify(store_s_store_name,store_s_store_id),(v28 * WED_SALESSTORE1.getValueOrDefault(se46.modify(store_sales_ss_store_sk))));
              n28 = n28->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i29 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n29; 
          SUN_SALESSTORE1_DELTA_entry* e29;
        
          for (size_t i = 0; i < i29->size_; i++)
          {
            n29 = i29->buckets_ + i;
            while (n29 && (e29 = n29->obj))
            {
                long store_sales_ss_store_sk = e29->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e29->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e29->STORE_S_STORE_NAME;
                long v29 = e29->__av;
                THU_SALES.addOrDelOnZero(se47.modify(store_s_store_name,store_s_store_id),(v29 * THU_SALESSTORE1.getValueOrDefault(se48.modify(store_sales_ss_store_sk))));
              n29 = n29->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i30 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n30; 
          SUN_SALESSTORE1_DELTA_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long store_sales_ss_store_sk = e30->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e30->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e30->STORE_S_STORE_NAME;
                long v30 = e30->__av;
                FRI_SALES.addOrDelOnZero(se49.modify(store_s_store_name,store_s_store_id),(v30 * FRI_SALESSTORE1.getValueOrDefault(se50.modify(store_sales_ss_store_sk))));
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_SUN_SALESSTORE1_DELTA_map_012* i31 = static_cast<HashIndex_SUN_SALESSTORE1_DELTA_map_012*>(SUN_SALESSTORE1_DELTA.index[0]);
          HashIndex_SUN_SALESSTORE1_DELTA_map_012::IdxNode* n31; 
          SUN_SALESSTORE1_DELTA_entry* e31;
        
          for (size_t i = 0; i < i31->size_; i++)
          {
            n31 = i31->buckets_ + i;
            while (n31 && (e31 = n31->obj))
            {
                long store_sales_ss_store_sk = e31->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_store_id = e31->STORE_S_STORE_ID;
                STRING_TYPE store_s_store_name = e31->STORE_S_STORE_NAME;
                long v31 = e31->__av;
                SAT_SALES.addOrDelOnZero(se51.modify(store_s_store_name,store_s_store_id),(v31 * SAT_SALESSTORE1.getValueOrDefault(se52.modify(store_sales_ss_store_sk))));
              n31 = n31->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        SUN_SALESSTORE_SALES1_P_2.clear();
        long l1 = 1998L;
        STRING_TYPE l2 = c1;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i32 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h8 = DATE_DIM_mapkey614_idxfn::hash(se54.modify614(l1, l2));
          HashIndex_DATE_DIM_map_614::IdxNode* n32 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i32->slice(se54, h8));
          DATE_DIM_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              long date_dim_d_date_sk = e32->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e32->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e32->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e32->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e32->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e32->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e32->DATE_DIM_D_DOW;
              long date_dim_d_moy = e32->DATE_DIM_D_MOY;
              long date_dim_d_dom = e32->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e32->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e32->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e32->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e32->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e32->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e32->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e32->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e32->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e32->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e32->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e32->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e32->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e32->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e32->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e32->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e32->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e32->DATE_DIM_D_CURRENT_YEAR;
              long v32 = e32->__av;
              SUN_SALESSTORE_SALES1_P_2.addOrDelOnZero(se53.modify(date_dim_d_date_sk),v32);
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h8 == n32->hash &&  DATE_DIM_mapkey614_idxfn::equals(se54, *e32)); 
          }
        }MON_SALESSTORE_SALES1_P_2.clear();
        long l3 = 1998L;
        STRING_TYPE l4 = c2;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i33 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h9 = DATE_DIM_mapkey614_idxfn::hash(se56.modify614(l3, l4));
          HashIndex_DATE_DIM_map_614::IdxNode* n33 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i33->slice(se56, h9));
          DATE_DIM_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              long date_dim_d_date_sk = e33->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e33->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e33->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e33->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e33->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e33->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e33->DATE_DIM_D_DOW;
              long date_dim_d_moy = e33->DATE_DIM_D_MOY;
              long date_dim_d_dom = e33->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e33->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e33->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e33->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e33->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e33->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e33->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e33->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e33->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e33->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e33->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e33->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e33->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e33->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e33->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e33->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e33->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e33->DATE_DIM_D_CURRENT_YEAR;
              long v33 = e33->__av;
              MON_SALESSTORE_SALES1_P_2.addOrDelOnZero(se55.modify(date_dim_d_date_sk),v33);
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h9 == n33->hash &&  DATE_DIM_mapkey614_idxfn::equals(se56, *e33)); 
          }
        }TUE_SALESSTORE_SALES1_P_2.clear();
        long l5 = 1998L;
        STRING_TYPE l6 = c3;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i34 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h10 = DATE_DIM_mapkey614_idxfn::hash(se58.modify614(l5, l6));
          HashIndex_DATE_DIM_map_614::IdxNode* n34 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i34->slice(se58, h10));
          DATE_DIM_entry* e34;
         
          if (n34 && (e34 = n34->obj)) {
            do {                
              long date_dim_d_date_sk = e34->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e34->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e34->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e34->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e34->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e34->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e34->DATE_DIM_D_DOW;
              long date_dim_d_moy = e34->DATE_DIM_D_MOY;
              long date_dim_d_dom = e34->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e34->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e34->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e34->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e34->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e34->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e34->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e34->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e34->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e34->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e34->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e34->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e34->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e34->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e34->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e34->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e34->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e34->DATE_DIM_D_CURRENT_YEAR;
              long v34 = e34->__av;
              TUE_SALESSTORE_SALES1_P_2.addOrDelOnZero(se57.modify(date_dim_d_date_sk),v34);
              n34 = n34->nxt;
            } while (n34 && (e34 = n34->obj) && h10 == n34->hash &&  DATE_DIM_mapkey614_idxfn::equals(se58, *e34)); 
          }
        }WED_SALESSTORE_SALES1_P_2.clear();
        long l7 = 1998L;
        STRING_TYPE l8 = c4;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i35 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h11 = DATE_DIM_mapkey614_idxfn::hash(se60.modify614(l7, l8));
          HashIndex_DATE_DIM_map_614::IdxNode* n35 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i35->slice(se60, h11));
          DATE_DIM_entry* e35;
         
          if (n35 && (e35 = n35->obj)) {
            do {                
              long date_dim_d_date_sk = e35->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e35->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e35->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e35->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e35->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e35->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e35->DATE_DIM_D_DOW;
              long date_dim_d_moy = e35->DATE_DIM_D_MOY;
              long date_dim_d_dom = e35->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e35->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e35->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e35->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e35->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e35->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e35->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e35->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e35->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e35->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e35->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e35->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e35->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e35->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e35->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e35->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e35->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e35->DATE_DIM_D_CURRENT_YEAR;
              long v35 = e35->__av;
              WED_SALESSTORE_SALES1_P_2.addOrDelOnZero(se59.modify(date_dim_d_date_sk),v35);
              n35 = n35->nxt;
            } while (n35 && (e35 = n35->obj) && h11 == n35->hash &&  DATE_DIM_mapkey614_idxfn::equals(se60, *e35)); 
          }
        }THU_SALESSTORE_SALES1_P_2.clear();
        long l9 = 1998L;
        STRING_TYPE l10 = c5;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i36 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h12 = DATE_DIM_mapkey614_idxfn::hash(se62.modify614(l9, l10));
          HashIndex_DATE_DIM_map_614::IdxNode* n36 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i36->slice(se62, h12));
          DATE_DIM_entry* e36;
         
          if (n36 && (e36 = n36->obj)) {
            do {                
              long date_dim_d_date_sk = e36->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e36->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e36->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e36->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e36->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e36->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e36->DATE_DIM_D_DOW;
              long date_dim_d_moy = e36->DATE_DIM_D_MOY;
              long date_dim_d_dom = e36->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e36->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e36->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e36->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e36->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e36->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e36->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e36->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e36->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e36->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e36->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e36->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e36->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e36->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e36->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e36->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e36->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e36->DATE_DIM_D_CURRENT_YEAR;
              long v36 = e36->__av;
              THU_SALESSTORE_SALES1_P_2.addOrDelOnZero(se61.modify(date_dim_d_date_sk),v36);
              n36 = n36->nxt;
            } while (n36 && (e36 = n36->obj) && h12 == n36->hash &&  DATE_DIM_mapkey614_idxfn::equals(se62, *e36)); 
          }
        }FRI_SALESSTORE_SALES1_P_2.clear();
        long l11 = 1998L;
        STRING_TYPE l12 = c6;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i37 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h13 = DATE_DIM_mapkey614_idxfn::hash(se64.modify614(l11, l12));
          HashIndex_DATE_DIM_map_614::IdxNode* n37 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i37->slice(se64, h13));
          DATE_DIM_entry* e37;
         
          if (n37 && (e37 = n37->obj)) {
            do {                
              long date_dim_d_date_sk = e37->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e37->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e37->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e37->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e37->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e37->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e37->DATE_DIM_D_DOW;
              long date_dim_d_moy = e37->DATE_DIM_D_MOY;
              long date_dim_d_dom = e37->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e37->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e37->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e37->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e37->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e37->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e37->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e37->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e37->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e37->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e37->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e37->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e37->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e37->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e37->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e37->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e37->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e37->DATE_DIM_D_CURRENT_YEAR;
              long v37 = e37->__av;
              FRI_SALESSTORE_SALES1_P_2.addOrDelOnZero(se63.modify(date_dim_d_date_sk),v37);
              n37 = n37->nxt;
            } while (n37 && (e37 = n37->obj) && h13 == n37->hash &&  DATE_DIM_mapkey614_idxfn::equals(se64, *e37)); 
          }
        }SAT_SALESSTORE_SALES1_P_2.clear();
        long l13 = 1998L;
        STRING_TYPE l14 = c7;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i38 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h14 = DATE_DIM_mapkey614_idxfn::hash(se66.modify614(l13, l14));
          HashIndex_DATE_DIM_map_614::IdxNode* n38 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i38->slice(se66, h14));
          DATE_DIM_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              long date_dim_d_date_sk = e38->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e38->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e38->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e38->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e38->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e38->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e38->DATE_DIM_D_DOW;
              long date_dim_d_moy = e38->DATE_DIM_D_MOY;
              long date_dim_d_dom = e38->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e38->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e38->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e38->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e38->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e38->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e38->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e38->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e38->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e38->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e38->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e38->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e38->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e38->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e38->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e38->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e38->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e38->DATE_DIM_D_CURRENT_YEAR;
              long v38 = e38->__av;
              SAT_SALESSTORE_SALES1_P_2.addOrDelOnZero(se65.modify(date_dim_d_date_sk),v38);
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h14 == n38->hash &&  DATE_DIM_mapkey614_idxfn::equals(se66, *e38)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    SUN_SALESSTORE_SALES1_DELTA_entry se1;
    SUN_SALES_entry se2;
    SUN_SALESSTORE_SALES1_P_2_entry se3;
    SUN_SALESSTORE_SALES1_P_1_entry se4;
    SUN_SALESSTORE1_entry se5;
    SUN_SALESSTORE_SALES1_P_2_entry se6;
    MON_SALES_entry se7;
    MON_SALESSTORE_SALES1_P_2_entry se8;
    SUN_SALESSTORE_SALES1_P_1_entry se9;
    MON_SALESSTORE1_entry se10;
    MON_SALESSTORE_SALES1_P_2_entry se11;
    TUE_SALES_entry se12;
    TUE_SALESSTORE_SALES1_P_2_entry se13;
    SUN_SALESSTORE_SALES1_P_1_entry se14;
    TUE_SALESSTORE1_entry se15;
    TUE_SALESSTORE_SALES1_P_2_entry se16;
    WED_SALES_entry se17;
    WED_SALESSTORE_SALES1_P_2_entry se18;
    SUN_SALESSTORE_SALES1_P_1_entry se19;
    WED_SALESSTORE1_entry se20;
    WED_SALESSTORE_SALES1_P_2_entry se21;
    THU_SALES_entry se22;
    THU_SALESSTORE_SALES1_P_2_entry se23;
    SUN_SALESSTORE_SALES1_P_1_entry se24;
    THU_SALESSTORE1_entry se25;
    THU_SALESSTORE_SALES1_P_2_entry se26;
    FRI_SALES_entry se27;
    FRI_SALESSTORE_SALES1_P_2_entry se28;
    SUN_SALESSTORE_SALES1_P_1_entry se29;
    FRI_SALESSTORE1_entry se30;
    FRI_SALESSTORE_SALES1_P_2_entry se31;
    SAT_SALES_entry se32;
    SAT_SALESSTORE_SALES1_P_2_entry se33;
    SUN_SALESSTORE_SALES1_P_1_entry se34;
    SAT_SALESSTORE1_entry se35;
    SAT_SALESSTORE_SALES1_P_2_entry se36;
    SUN_SALESSTORE1_DELTA_entry se37;
    SUN_SALES_entry se38;
    SUN_SALESSTORE1_entry se39;
    SUN_SALESSTORE_SALES1_P_1_entry se40;
    MON_SALES_entry se41;
    MON_SALESSTORE1_entry se42;
    TUE_SALES_entry se43;
    TUE_SALESSTORE1_entry se44;
    WED_SALES_entry se45;
    WED_SALESSTORE1_entry se46;
    THU_SALES_entry se47;
    THU_SALESSTORE1_entry se48;
    FRI_SALES_entry se49;
    FRI_SALESSTORE1_entry se50;
    SAT_SALES_entry se51;
    SAT_SALESSTORE1_entry se52;
    SUN_SALESSTORE_SALES1_P_2_entry se53;
    DATE_DIM_entry se54;
    MON_SALESSTORE_SALES1_P_2_entry se55;
    DATE_DIM_entry se56;
    TUE_SALESSTORE_SALES1_P_2_entry se57;
    DATE_DIM_entry se58;
    WED_SALESSTORE_SALES1_P_2_entry se59;
    DATE_DIM_entry se60;
    THU_SALESSTORE_SALES1_P_2_entry se61;
    DATE_DIM_entry se62;
    FRI_SALESSTORE_SALES1_P_2_entry se63;
    DATE_DIM_entry se64;
    SAT_SALESSTORE_SALES1_P_2_entry se65;
    DATE_DIM_entry se66;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    SUN_SALESSTORE1_DELTA_map SUN_SALESSTORE1_DELTA;
    SUN_SALESSTORE1_map SUN_SALESSTORE1;
    SUN_SALESSTORE_SALES1_DELTA_map SUN_SALESSTORE_SALES1_DELTA;
    SUN_SALESSTORE_SALES1_P_1_map SUN_SALESSTORE_SALES1_P_1;
    SUN_SALESSTORE_SALES1_P_2_map SUN_SALESSTORE_SALES1_P_2;
    MON_SALESSTORE1_map MON_SALESSTORE1;
    MON_SALESSTORE_SALES1_P_2_map MON_SALESSTORE_SALES1_P_2;
    TUE_SALESSTORE1_map TUE_SALESSTORE1;
    TUE_SALESSTORE_SALES1_P_2_map TUE_SALESSTORE_SALES1_P_2;
    WED_SALESSTORE1_map WED_SALESSTORE1;
    WED_SALESSTORE_SALES1_P_2_map WED_SALESSTORE_SALES1_P_2;
    THU_SALESSTORE1_map THU_SALESSTORE1;
    THU_SALESSTORE_SALES1_P_2_map THU_SALESSTORE_SALES1_P_2;
    FRI_SALESSTORE1_map FRI_SALESSTORE1;
    FRI_SALESSTORE_SALES1_P_2_map FRI_SALESSTORE_SALES1_P_2;
    SAT_SALESSTORE1_map SAT_SALESSTORE1;
    SAT_SALESSTORE_SALES1_P_2_map SAT_SALESSTORE_SALES1_P_2;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_STORE_map DELTA_STORE;
    
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
  
  };

}
