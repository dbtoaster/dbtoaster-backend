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
  
  struct DELTA_ITEM_entry {
    long item_i_item_sk; STRING_TYPE item_i_item_id; date item_i_rec_start_date; date item_i_rec_end_date; STRING_TYPE item_i_item_desc; DOUBLE_TYPE item_i_current_price; DOUBLE_TYPE item_i_wholesale_cost; long item_i_brand_id; STRING_TYPE item_i_brand; long item_i_class_id; STRING_TYPE item_i_class; long item_i_category_id; STRING_TYPE item_i_category; long item_i_manufact_id; STRING_TYPE item_i_manufact; STRING_TYPE item_i_size; STRING_TYPE item_i_formulation; STRING_TYPE item_i_color; STRING_TYPE item_i_units; STRING_TYPE item_i_container; long item_i_manager_id; STRING_TYPE item_i_product_name; long __av; 
    explicit DELTA_ITEM_entry() { /*item_i_item_sk = 0L; item_i_item_id = ""; item_i_rec_start_date = 00000000; item_i_rec_end_date = 00000000; item_i_item_desc = ""; item_i_current_price = 0.0; item_i_wholesale_cost = 0.0; item_i_brand_id = 0L; item_i_brand = ""; item_i_class_id = 0L; item_i_class = ""; item_i_category_id = 0L; item_i_category = ""; item_i_manufact_id = 0L; item_i_manufact = ""; item_i_size = ""; item_i_formulation = ""; item_i_color = ""; item_i_units = ""; item_i_container = ""; item_i_manager_id = 0L; item_i_product_name = ""; __av = 0L; */ }
    explicit DELTA_ITEM_entry(const long c0, const STRING_TYPE& c1, const date c2, const date c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const long c7, const STRING_TYPE& c8, const long c9, const STRING_TYPE& c10, const long c11, const STRING_TYPE& c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const STRING_TYPE& c19, const long c20, const STRING_TYPE& c21, const long c22) { item_i_item_sk = c0; item_i_item_id = c1; item_i_rec_start_date = c2; item_i_rec_end_date = c3; item_i_item_desc = c4; item_i_current_price = c5; item_i_wholesale_cost = c6; item_i_brand_id = c7; item_i_brand = c8; item_i_class_id = c9; item_i_class = c10; item_i_category_id = c11; item_i_category = c12; item_i_manufact_id = c13; item_i_manufact = c14; item_i_size = c15; item_i_formulation = c16; item_i_color = c17; item_i_units = c18; item_i_container = c19; item_i_manager_id = c20; item_i_product_name = c21; __av = c22; }
    DELTA_ITEM_entry(const DELTA_ITEM_entry& other) : item_i_item_sk( other.item_i_item_sk ), item_i_item_id( other.item_i_item_id ), item_i_rec_start_date( other.item_i_rec_start_date ), item_i_rec_end_date( other.item_i_rec_end_date ), item_i_item_desc( other.item_i_item_desc ), item_i_current_price( other.item_i_current_price ), item_i_wholesale_cost( other.item_i_wholesale_cost ), item_i_brand_id( other.item_i_brand_id ), item_i_brand( other.item_i_brand ), item_i_class_id( other.item_i_class_id ), item_i_class( other.item_i_class ), item_i_category_id( other.item_i_category_id ), item_i_category( other.item_i_category ), item_i_manufact_id( other.item_i_manufact_id ), item_i_manufact( other.item_i_manufact ), item_i_size( other.item_i_size ), item_i_formulation( other.item_i_formulation ), item_i_color( other.item_i_color ), item_i_units( other.item_i_units ), item_i_container( other.item_i_container ), item_i_manager_id( other.item_i_manager_id ), item_i_product_name( other.item_i_product_name ), __av( other.__av ) {}
    FORCE_INLINE DELTA_ITEM_entry& modify(const long c0, const STRING_TYPE& c1, const date c2, const date c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const long c7, const STRING_TYPE& c8, const long c9, const STRING_TYPE& c10, const long c11, const STRING_TYPE& c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const STRING_TYPE& c19, const long c20, const STRING_TYPE& c21) { item_i_item_sk = c0; item_i_item_id = c1; item_i_rec_start_date = c2; item_i_rec_end_date = c3; item_i_item_desc = c4; item_i_current_price = c5; item_i_wholesale_cost = c6; item_i_brand_id = c7; item_i_brand = c8; item_i_class_id = c9; item_i_class = c10; item_i_category_id = c11; item_i_category = c12; item_i_manufact_id = c13; item_i_manufact = c14; item_i_size = c15; item_i_formulation = c16; item_i_color = c17; item_i_units = c18; item_i_container = c19; item_i_manager_id = c20; item_i_product_name = c21;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_item_sk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_item_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_rec_start_date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_rec_end_date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_item_desc);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_current_price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_wholesale_cost);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_brand_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_brand);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_class_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_class);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_category_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_manufact_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_manufact);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_size);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_formulation);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_color);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_units);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_container);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_manager_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item_i_product_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DELTA_ITEM_mapkey0123456789101112131415161718192021_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_ITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.item_i_item_sk);
      hash_combine(h, e.item_i_item_id);
      hash_combine(h, e.item_i_rec_start_date);
      hash_combine(h, e.item_i_rec_end_date);
      hash_combine(h, e.item_i_item_desc);
      hash_combine(h, e.item_i_current_price);
      hash_combine(h, e.item_i_wholesale_cost);
      hash_combine(h, e.item_i_brand_id);
      hash_combine(h, e.item_i_brand);
      hash_combine(h, e.item_i_class_id);
      hash_combine(h, e.item_i_class);
      hash_combine(h, e.item_i_category_id);
      hash_combine(h, e.item_i_category);
      hash_combine(h, e.item_i_manufact_id);
      hash_combine(h, e.item_i_manufact);
      hash_combine(h, e.item_i_size);
      hash_combine(h, e.item_i_formulation);
      hash_combine(h, e.item_i_color);
      hash_combine(h, e.item_i_units);
      hash_combine(h, e.item_i_container);
      hash_combine(h, e.item_i_manager_id);
      hash_combine(h, e.item_i_product_name);
      return h;
    }
    FORCE_INLINE static bool equals(const DELTA_ITEM_entry& x, const DELTA_ITEM_entry& y) {
      return x.item_i_item_sk == y.item_i_item_sk && x.item_i_item_id == y.item_i_item_id && x.item_i_rec_start_date == y.item_i_rec_start_date && x.item_i_rec_end_date == y.item_i_rec_end_date && x.item_i_item_desc == y.item_i_item_desc && x.item_i_current_price == y.item_i_current_price && x.item_i_wholesale_cost == y.item_i_wholesale_cost && x.item_i_brand_id == y.item_i_brand_id && x.item_i_brand == y.item_i_brand && x.item_i_class_id == y.item_i_class_id && x.item_i_class == y.item_i_class && x.item_i_category_id == y.item_i_category_id && x.item_i_category == y.item_i_category && x.item_i_manufact_id == y.item_i_manufact_id && x.item_i_manufact == y.item_i_manufact && x.item_i_size == y.item_i_size && x.item_i_formulation == y.item_i_formulation && x.item_i_color == y.item_i_color && x.item_i_units == y.item_i_units && x.item_i_container == y.item_i_container && x.item_i_manager_id == y.item_i_manager_id && x.item_i_product_name == y.item_i_product_name;
    }
  };
  
  typedef MultiHashMap<DELTA_ITEM_entry,long,
    HashIndex<DELTA_ITEM_entry,long,DELTA_ITEM_mapkey0123456789101112131415161718192021_idxfn,true>
  > DELTA_ITEM_map;
  typedef HashIndex<DELTA_ITEM_entry,long,DELTA_ITEM_mapkey0123456789101112131415161718192021_idxfn,true> HashIndex_DELTA_ITEM_map_0123456789101112131415161718192021;
  
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
    FORCE_INLINE DATE_DIM_entry& modify68(const long c6, const long c8) { DATE_DIM_D_YEAR = c6; DATE_DIM_D_MOY = c8;  return *this; }
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
  
  struct DATE_DIM_mapkey68_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_YEAR);
      hash_combine(h, e.DATE_DIM_D_MOY);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR && x.DATE_DIM_D_MOY == y.DATE_DIM_D_MOY;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey68_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey68_idxfn,false> HashIndex_DATE_DIM_map_68;
  
  struct EXT_PRICE_entry {
    long BRAND_ID; STRING_TYPE BRAND; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; DOUBLE_TYPE __av; 
    explicit EXT_PRICE_entry() { /*BRAND_ID = 0L; BRAND = ""; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; __av = 0.0; */ }
    explicit EXT_PRICE_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { BRAND_ID = c0; BRAND = c1; ITEM_I_MANUFACT_ID = c2; ITEM_I_MANUFACT = c3; __av = c4; }
    EXT_PRICE_entry(const EXT_PRICE_entry& other) : BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICE_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { BRAND_ID = c0; BRAND = c1; ITEM_I_MANUFACT_ID = c2; ITEM_I_MANUFACT = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICE_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICE_entry& x, const EXT_PRICE_entry& y) {
      return x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT;
    }
  };
  
  typedef MultiHashMap<EXT_PRICE_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICE_entry,DOUBLE_TYPE,EXT_PRICE_mapkey0123_idxfn,true>
  > EXT_PRICE_map;
  typedef HashIndex<EXT_PRICE_entry,DOUBLE_TYPE,EXT_PRICE_mapkey0123_idxfn,true> HashIndex_EXT_PRICE_map_0123;
  
  struct EXT_PRICESTORE1_DELTA_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_ZIP; long __av; 
    explicit EXT_PRICESTORE1_DELTA_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_ZIP = ""; __av = 0L; */ }
    explicit EXT_PRICESTORE1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_ZIP = c1; __av = c2; }
    EXT_PRICESTORE1_DELTA_entry(const EXT_PRICESTORE1_DELTA_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_ZIP( other.STORE_S_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; STORE_S_ZIP = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1_DELTA_entry& x, const EXT_PRICESTORE1_DELTA_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_ZIP == y.STORE_S_ZIP;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1_DELTA_entry,long,
    HashIndex<EXT_PRICESTORE1_DELTA_entry,long,EXT_PRICESTORE1_DELTA_mapkey01_idxfn,true>
  > EXT_PRICESTORE1_DELTA_map;
  typedef HashIndex<EXT_PRICESTORE1_DELTA_entry,long,EXT_PRICESTORE1_DELTA_mapkey01_idxfn,true> HashIndex_EXT_PRICESTORE1_DELTA_map_01;
  
  struct EXT_PRICESTORE1_entry {
    long STORE_SALES_SS_STORE_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; STRING_TYPE CUSTOMER_ADDRESS_CA_ZIP; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; CUSTOMER_ADDRESS_CA_ZIP = ""; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICESTORE1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; CUSTOMER_ADDRESS_CA_ZIP = c3; BRAND_ID = c4; BRAND = c5; __av = c6; }
    EXT_PRICESTORE1_entry(const EXT_PRICESTORE1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), CUSTOMER_ADDRESS_CA_ZIP( other.CUSTOMER_ADDRESS_CA_ZIP ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; CUSTOMER_ADDRESS_CA_ZIP = c3; BRAND_ID = c4; BRAND = c5;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_ADDRESS_CA_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.CUSTOMER_ADDRESS_CA_ZIP);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1_entry& x, const EXT_PRICESTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.CUSTOMER_ADDRESS_CA_ZIP == y.CUSTOMER_ADDRESS_CA_ZIP && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICESTORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1_entry& x, const EXT_PRICESTORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE1_entry,DOUBLE_TYPE,EXT_PRICESTORE1_mapkey012345_idxfn,true>,
    HashIndex<EXT_PRICESTORE1_entry,DOUBLE_TYPE,EXT_PRICESTORE1_mapkey0_idxfn,false>
  > EXT_PRICESTORE1_map;
  typedef HashIndex<EXT_PRICESTORE1_entry,DOUBLE_TYPE,EXT_PRICESTORE1_mapkey012345_idxfn,true> HashIndex_EXT_PRICESTORE1_map_012345;
  typedef HashIndex<EXT_PRICESTORE1_entry,DOUBLE_TYPE,EXT_PRICESTORE1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1_map_0;
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry {
    long STORE_SALES_SS_STORE_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; long CUSTOMER_C_CURRENT_ADDR_SK; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry() { /*STORE_SALES_SS_STORE_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; CUSTOMER_C_CURRENT_ADDR_SK = 0L; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4, const STRING_TYPE& c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; CUSTOMER_C_CURRENT_ADDR_SK = c3; BRAND_ID = c4; BRAND = c5; __av = c6; }
    EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry(const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4, const STRING_TYPE& c5) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; CUSTOMER_C_CURRENT_ADDR_SK = c3; BRAND_ID = c4; BRAND = c5;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& modify3(const long c3) { CUSTOMER_C_CURRENT_ADDR_SK = c3;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey3_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey012345_idxfn,true>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey3_idxfn,false>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey0_idxfn,false>
  > EXT_PRICESTORE1CUSTOMER_ADDRESS1_map;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey012345_idxfn,true> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_012345;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey3_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_3;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_0;
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_STORE_SK; long CUSTOMER_C_CURRENT_ADDR_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; CUSTOMER_C_CURRENT_ADDR_SK = c2; __av = c3; }
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& modify(const long c0, const long c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; CUSTOMER_C_CURRENT_ADDR_SK = c2;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& modify2(const long c2) { CUSTOMER_C_CURRENT_ADDR_SK = c2;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey2_idxfn,false>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn,false>
  > EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey012_idxfn,true> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_012;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_0;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey2_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_2;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_1;
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CUSTOMER_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CUSTOMER_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1; STORE_SALES_SS_STORE_SK = c2; __av = c3; }
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& modify(const long c0, const long c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1; STORE_SALES_SS_STORE_SK = c2;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& modify1(const long c1) { STORE_SALES_SS_CUSTOMER_SK = c1;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& modify2(const long c2) { STORE_SALES_SS_STORE_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey1_idxfn,false>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey2_idxfn,false>
  > EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey012_idxfn,true> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_012;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_0;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey1_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey2_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2;
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_CUSTOMER_SK; long CUSTOMER_C_CURRENT_ADDR_SK; long __av; 
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_CUSTOMER_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry(const long c0, const long c1, const long c2) { STORE_SALES_SS_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; __av = c2; }
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry(const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& modify(const long c0, const long c1) { STORE_SALES_SS_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& modify0(const long c0) { STORE_SALES_SS_CUSTOMER_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& modify1(const long c1) { CUSTOMER_C_CURRENT_ADDR_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& x, const EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey01_idxfn,true>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey1_idxfn,false>
  > EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey1_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1;
  
  struct EXT_PRICESTORE1CUSTOMER1_P_1_entry {
    long STORE_SALES_SS_CUSTOMER_SK; long STORE_SALES_SS_STORE_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE1CUSTOMER1_P_1_entry() { /*STORE_SALES_SS_CUSTOMER_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICESTORE1CUSTOMER1_P_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_CUSTOMER_SK = c0; STORE_SALES_SS_STORE_SK = c1; ITEM_I_MANUFACT_ID = c2; ITEM_I_MANUFACT = c3; BRAND_ID = c4; BRAND = c5; __av = c6; }
    EXT_PRICESTORE1CUSTOMER1_P_1_entry(const EXT_PRICESTORE1CUSTOMER1_P_1_entry& other) : STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER1_P_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5) { STORE_SALES_SS_CUSTOMER_SK = c0; STORE_SALES_SS_STORE_SK = c1; ITEM_I_MANUFACT_ID = c2; ITEM_I_MANUFACT = c3; BRAND_ID = c4; BRAND = c5;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER1_P_1_entry& modify0(const long c0) { STORE_SALES_SS_CUSTOMER_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER1_P_1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1CUSTOMER1_P_1_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER1_P_1_entry& x, const EXT_PRICESTORE1CUSTOMER1_P_1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER1_P_1_entry& x, const EXT_PRICESTORE1CUSTOMER1_P_1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER1_P_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER1_P_1_entry& x, const EXT_PRICESTORE1CUSTOMER1_P_1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1CUSTOMER1_P_1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER1_P_1_mapkey012345_idxfn,true>,
    HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER1_P_1_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER1_P_1_mapkey1_idxfn,false>
  > EXT_PRICESTORE1CUSTOMER1_P_1_map;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER1_P_1_mapkey012345_idxfn,true> HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_012345;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER1_P_1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1_entry,DOUBLE_TYPE,EXT_PRICESTORE1CUSTOMER1_P_1_mapkey1_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1;
  
  struct EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry {
    long STORE_SALES_SS_ITEM_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; STRING_TYPE BRAND; long BRAND_ID; long __av; 
    explicit EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; BRAND = ""; BRAND_ID = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const long c5) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND = c3; BRAND_ID = c4; __av = c5; }
    EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry(const EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), BRAND( other.BRAND ), BRAND_ID( other.BRAND_ID ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND = c3; BRAND_ID = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.BRAND);
      hash_combine(h, e.BRAND_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry& x, const EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.BRAND == y.BRAND && x.BRAND_ID == y.BRAND_ID;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry,long,
    HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry,long,EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_mapkey01234_idxfn,true>
  > EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry,long,EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_mapkey01234_idxfn,true> HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234;
  
  struct EXT_PRICESTORE1CUSTOMER1_P_2_entry {
    long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE CUSTOMER_ADDRESS_CA_ZIP; long __av; 
    explicit EXT_PRICESTORE1CUSTOMER1_P_2_entry() { /*CUSTOMER_C_CURRENT_ADDR_SK = 0L; CUSTOMER_ADDRESS_CA_ZIP = ""; __av = 0L; */ }
    explicit EXT_PRICESTORE1CUSTOMER1_P_2_entry(const long c0, const STRING_TYPE& c1, const long c2) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CUSTOMER_ADDRESS_CA_ZIP = c1; __av = c2; }
    EXT_PRICESTORE1CUSTOMER1_P_2_entry(const EXT_PRICESTORE1CUSTOMER1_P_2_entry& other) : CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), CUSTOMER_ADDRESS_CA_ZIP( other.CUSTOMER_ADDRESS_CA_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER1_P_2_entry& modify(const long c0, const STRING_TYPE& c1) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CUSTOMER_ADDRESS_CA_ZIP = c1;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1CUSTOMER1_P_2_entry& modify0(const long c0) { CUSTOMER_C_CURRENT_ADDR_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_ADDRESS_CA_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1CUSTOMER1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.CUSTOMER_ADDRESS_CA_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER1_P_2_entry& x, const EXT_PRICESTORE1CUSTOMER1_P_2_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.CUSTOMER_ADDRESS_CA_ZIP == y.CUSTOMER_ADDRESS_CA_ZIP;
    }
  };
  
  struct EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1CUSTOMER1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1CUSTOMER1_P_2_entry& x, const EXT_PRICESTORE1CUSTOMER1_P_2_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1CUSTOMER1_P_2_entry,long,
    HashIndex<EXT_PRICESTORE1CUSTOMER1_P_2_entry,long,EXT_PRICESTORE1CUSTOMER1_P_2_mapkey01_idxfn,true>,
    HashIndex<EXT_PRICESTORE1CUSTOMER1_P_2_entry,long,EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn,false>
  > EXT_PRICESTORE1CUSTOMER1_P_2_map;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER1_P_2_entry,long,EXT_PRICESTORE1CUSTOMER1_P_2_mapkey01_idxfn,true> HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01;
  typedef HashIndex<EXT_PRICESTORE1CUSTOMER1_P_2_entry,long,EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0;
  
  struct EXT_PRICESTORE1ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_STORE_SK; STRING_TYPE CUSTOMER_ADDRESS_CA_ZIP; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE1ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; CUSTOMER_ADDRESS_CA_ZIP = ""; __av = 0.0; */ }
    explicit EXT_PRICESTORE1ITEM1_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; CUSTOMER_ADDRESS_CA_ZIP = c2; __av = c3; }
    EXT_PRICESTORE1ITEM1_entry(const EXT_PRICESTORE1ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), CUSTOMER_ADDRESS_CA_ZIP( other.CUSTOMER_ADDRESS_CA_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1ITEM1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; CUSTOMER_ADDRESS_CA_ZIP = c2;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1ITEM1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1ITEM1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_ADDRESS_CA_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1ITEM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.CUSTOMER_ADDRESS_CA_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1ITEM1_entry& x, const EXT_PRICESTORE1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.CUSTOMER_ADDRESS_CA_ZIP == y.CUSTOMER_ADDRESS_CA_ZIP;
    }
  };
  
  struct EXT_PRICESTORE1ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1ITEM1_entry& x, const EXT_PRICESTORE1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct EXT_PRICESTORE1ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1ITEM1_entry& x, const EXT_PRICESTORE1ITEM1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1ITEM1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1ITEM1_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICESTORE1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1ITEM1_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICESTORE1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1ITEM1_mapkey1_idxfn,false>
  > EXT_PRICESTORE1ITEM1_map;
  typedef HashIndex<EXT_PRICESTORE1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1ITEM1_mapkey012_idxfn,true> HashIndex_EXT_PRICESTORE1ITEM1_map_012;
  typedef HashIndex<EXT_PRICESTORE1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1ITEM1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1ITEM1_map_0;
  typedef HashIndex<EXT_PRICESTORE1ITEM1_entry,DOUBLE_TYPE,EXT_PRICESTORE1ITEM1_mapkey1_idxfn,false> HashIndex_EXT_PRICESTORE1ITEM1_map_1;
  
  struct EXT_PRICESTORE1STORE_SALES1_P_2_entry {
    long STORE_SALES_SS_ITEM_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; long BRAND_ID; STRING_TYPE BRAND; long __av; 
    explicit EXT_PRICESTORE1STORE_SALES1_P_2_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; BRAND_ID = 0L; BRAND = ""; __av = 0L; */ }
    explicit EXT_PRICESTORE1STORE_SALES1_P_2_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const long c5) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND_ID = c3; BRAND = c4; __av = c5; }
    EXT_PRICESTORE1STORE_SALES1_P_2_entry(const EXT_PRICESTORE1STORE_SALES1_P_2_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1STORE_SALES1_P_2_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND_ID = c3; BRAND = c4;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1STORE_SALES1_P_2_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1STORE_SALES1_P_2_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1STORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1STORE_SALES1_P_2_entry& x, const EXT_PRICESTORE1STORE_SALES1_P_2_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1STORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1STORE_SALES1_P_2_entry& x, const EXT_PRICESTORE1STORE_SALES1_P_2_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1STORE_SALES1_P_2_entry,long,
    HashIndex<EXT_PRICESTORE1STORE_SALES1_P_2_entry,long,EXT_PRICESTORE1STORE_SALES1_P_2_mapkey01234_idxfn,true>,
    HashIndex<EXT_PRICESTORE1STORE_SALES1_P_2_entry,long,EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn,false>
  > EXT_PRICESTORE1STORE_SALES1_P_2_map;
  typedef HashIndex<EXT_PRICESTORE1STORE_SALES1_P_2_entry,long,EXT_PRICESTORE1STORE_SALES1_P_2_mapkey01234_idxfn,true> HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_01234;
  typedef HashIndex<EXT_PRICESTORE1STORE_SALES1_P_2_entry,long,EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0;
  
  struct EXT_PRICESTORE1STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_CUSTOMER_SK; STRING_TYPE CUSTOMER_ADDRESS_CA_ZIP; long __av; 
    explicit EXT_PRICESTORE1STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_CUSTOMER_SK = 0L; CUSTOMER_ADDRESS_CA_ZIP = ""; __av = 0L; */ }
    explicit EXT_PRICESTORE1STORE_SALES1_P_3_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_CUSTOMER_SK = c0; CUSTOMER_ADDRESS_CA_ZIP = c1; __av = c2; }
    EXT_PRICESTORE1STORE_SALES1_P_3_entry(const EXT_PRICESTORE1STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), CUSTOMER_ADDRESS_CA_ZIP( other.CUSTOMER_ADDRESS_CA_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE1STORE_SALES1_P_3_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_CUSTOMER_SK = c0; CUSTOMER_ADDRESS_CA_ZIP = c1;  return *this; }
    FORCE_INLINE EXT_PRICESTORE1STORE_SALES1_P_3_entry& modify0(const long c0) { STORE_SALES_SS_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_ADDRESS_CA_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE1STORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_ADDRESS_CA_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1STORE_SALES1_P_3_entry& x, const EXT_PRICESTORE1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.CUSTOMER_ADDRESS_CA_ZIP == y.CUSTOMER_ADDRESS_CA_ZIP;
    }
  };
  
  struct EXT_PRICESTORE1STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE1STORE_SALES1_P_3_entry& x, const EXT_PRICESTORE1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE1STORE_SALES1_P_3_entry,long,
    HashIndex<EXT_PRICESTORE1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1STORE_SALES1_P_3_mapkey01_idxfn,true>,
    HashIndex<EXT_PRICESTORE1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1STORE_SALES1_P_3_mapkey0_idxfn,false>
  > EXT_PRICESTORE1STORE_SALES1_P_3_map;
  typedef HashIndex<EXT_PRICESTORE1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1STORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_01;
  typedef HashIndex<EXT_PRICESTORE1STORE_SALES1_P_3_entry,long,EXT_PRICESTORE1STORE_SALES1_P_3_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0;
  
  struct EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry {
    long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE CUSTOMER_ADDRESS_CA_ZIP; long __av; 
    explicit EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry() { /*CUSTOMER_C_CURRENT_ADDR_SK = 0L; CUSTOMER_ADDRESS_CA_ZIP = ""; __av = 0L; */ }
    explicit EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CUSTOMER_ADDRESS_CA_ZIP = c1; __av = c2; }
    EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry(const EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry& other) : CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), CUSTOMER_ADDRESS_CA_ZIP( other.CUSTOMER_ADDRESS_CA_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { CUSTOMER_C_CURRENT_ADDR_SK = c0; CUSTOMER_ADDRESS_CA_ZIP = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_ADDRESS_CA_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER_ADDRESS1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.CUSTOMER_ADDRESS_CA_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry& x, const EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.CUSTOMER_ADDRESS_CA_ZIP == y.CUSTOMER_ADDRESS_CA_ZIP;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry,long,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry,long,EXT_PRICECUSTOMER_ADDRESS1_DELTA_mapkey01_idxfn,true>
  > EXT_PRICECUSTOMER_ADDRESS1_DELTA_map;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry,long,EXT_PRICECUSTOMER_ADDRESS1_DELTA_mapkey01_idxfn,true> HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01;
  
  struct EXT_PRICECUSTOMER_ADDRESS1_entry {
    long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE STORE_S_ZIP; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICECUSTOMER_ADDRESS1_entry() { /*ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; CUSTOMER_C_CURRENT_ADDR_SK = 0L; STORE_S_ZIP = ""; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICECUSTOMER_ADDRESS1_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const DOUBLE_TYPE c6) { ITEM_I_MANUFACT_ID = c0; ITEM_I_MANUFACT = c1; CUSTOMER_C_CURRENT_ADDR_SK = c2; STORE_S_ZIP = c3; BRAND_ID = c4; BRAND = c5; __av = c6; }
    EXT_PRICECUSTOMER_ADDRESS1_entry(const EXT_PRICECUSTOMER_ADDRESS1_entry& other) : ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), STORE_S_ZIP( other.STORE_S_ZIP ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5) { ITEM_I_MANUFACT_ID = c0; ITEM_I_MANUFACT = c1; CUSTOMER_C_CURRENT_ADDR_SK = c2; STORE_S_ZIP = c3; BRAND_ID = c4; BRAND = c5;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1_entry& modify2(const long c2) { CUSTOMER_C_CURRENT_ADDR_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER_ADDRESS1_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.STORE_S_ZIP);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1_entry& y) {
      return x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.STORE_S_ZIP == y.STORE_S_ZIP && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICECUSTOMER_ADDRESS1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1_mapkey012345_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1_mapkey2_idxfn,false>
  > EXT_PRICECUSTOMER_ADDRESS1_map;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1_mapkey012345_idxfn,true> HashIndex_EXT_PRICECUSTOMER_ADDRESS1_map_012345;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1_mapkey2_idxfn,false> HashIndex_EXT_PRICECUSTOMER_ADDRESS1_map_2;
  
  struct EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry {
    long STORE_SALES_SS_CUSTOMER_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; STRING_TYPE STORE_S_ZIP; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry() { /*STORE_SALES_SS_CUSTOMER_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; STORE_S_ZIP = ""; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_CUSTOMER_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; STORE_S_ZIP = c3; BRAND_ID = c4; BRAND = c5; __av = c6; }
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& other) : STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), STORE_S_ZIP( other.STORE_S_ZIP ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5) { STORE_SALES_SS_CUSTOMER_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; STORE_S_ZIP = c3; BRAND_ID = c4; BRAND = c5;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& modify0(const long c0) { STORE_SALES_SS_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.STORE_S_ZIP);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.STORE_S_ZIP == y.STORE_S_ZIP && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey012345_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey0_idxfn,false>
  > EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey012345_idxfn,true> HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_012345;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey0_idxfn,false> HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_0;
  
  struct EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CUSTOMER_SK; STRING_TYPE STORE_S_ZIP; DOUBLE_TYPE __av; 
    explicit EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CUSTOMER_SK = 0L; STORE_S_ZIP = ""; __av = 0.0; */ }
    explicit EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1; STORE_S_ZIP = c2; __av = c3; }
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), STORE_S_ZIP( other.STORE_S_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1; STORE_S_ZIP = c2;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& modify1(const long c1) { STORE_SALES_SS_CUSTOMER_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.STORE_S_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.STORE_S_ZIP == y.STORE_S_ZIP;
    }
  };
  
  struct EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey1_idxfn,false>
  > EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey012_idxfn,true> HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_012;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey0_idxfn,false> HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_0;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey1_idxfn,false> HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_1;
  
  struct EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; long CUSTOMER_C_CURRENT_ADDR_SK; STRING_TYPE STORE_S_ZIP; DOUBLE_TYPE __av; 
    explicit EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; STORE_S_ZIP = ""; __av = 0.0; */ }
    explicit EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { STORE_SALES_SS_ITEM_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; STORE_S_ZIP = c2; __av = c3; }
    EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry(const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), STORE_S_ZIP( other.STORE_S_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { STORE_SALES_SS_ITEM_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; STORE_S_ZIP = c2;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& modify1(const long c1) { CUSTOMER_C_CURRENT_ADDR_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.STORE_S_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.STORE_S_ZIP == y.STORE_S_ZIP;
    }
  };
  
  struct EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& x, const EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn,false>
  > EXT_PRICECUSTOMER_ADDRESS1ITEM1_map;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey012_idxfn,true> HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_012;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn,false> HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_0;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn,false> HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_1;
  
  struct EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_ZIP; long __av; 
    explicit EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_ZIP = ""; __av = 0L; */ }
    explicit EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_ZIP = c1; __av = c2; }
    EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry(const EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_ZIP( other.STORE_S_ZIP ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; STORE_S_ZIP = c1;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_ZIP);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_ZIP);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& x, const EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_ZIP == y.STORE_S_ZIP;
    }
  };
  
  struct EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& x, const EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey01_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn,false>
  > EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01;
  typedef HashIndex<EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn,false> HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0;
  
  struct EXT_PRICECUSTOMER1_DELTA_entry {
    long STORE_SALES_SS_CUSTOMER_SK; long CUSTOMER_C_CURRENT_ADDR_SK; long __av; 
    explicit EXT_PRICECUSTOMER1_DELTA_entry() { /*STORE_SALES_SS_CUSTOMER_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; __av = 0L; */ }
    explicit EXT_PRICECUSTOMER1_DELTA_entry(const long c0, const long c1, const long c2) { STORE_SALES_SS_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; __av = c2; }
    EXT_PRICECUSTOMER1_DELTA_entry(const EXT_PRICECUSTOMER1_DELTA_entry& other) : STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER1_DELTA_entry& modify(const long c0, const long c1) { STORE_SALES_SS_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1_DELTA_entry& x, const EXT_PRICECUSTOMER1_DELTA_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER1_DELTA_entry,long,
    HashIndex<EXT_PRICECUSTOMER1_DELTA_entry,long,EXT_PRICECUSTOMER1_DELTA_mapkey01_idxfn,true>
  > EXT_PRICECUSTOMER1_DELTA_map;
  typedef HashIndex<EXT_PRICECUSTOMER1_DELTA_entry,long,EXT_PRICECUSTOMER1_DELTA_mapkey01_idxfn,true> HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01;
  
  struct EXT_PRICECUSTOMER1_entry {
    long STORE_SALES_SS_CUSTOMER_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; long CUSTOMER_C_CURRENT_ADDR_SK; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICECUSTOMER1_entry() { /*STORE_SALES_SS_CUSTOMER_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; CUSTOMER_C_CURRENT_ADDR_SK = 0L; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICECUSTOMER1_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4, const STRING_TYPE& c5, const DOUBLE_TYPE c6) { STORE_SALES_SS_CUSTOMER_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; CUSTOMER_C_CURRENT_ADDR_SK = c3; BRAND_ID = c4; BRAND = c5; __av = c6; }
    EXT_PRICECUSTOMER1_entry(const EXT_PRICECUSTOMER1_entry& other) : STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4, const STRING_TYPE& c5) { STORE_SALES_SS_CUSTOMER_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; CUSTOMER_C_CURRENT_ADDR_SK = c3; BRAND_ID = c4; BRAND = c5;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER1_entry& modify03(const long c0, const long c3) { STORE_SALES_SS_CUSTOMER_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER1_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1_entry& x, const EXT_PRICECUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICECUSTOMER1_mapkey03_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1_entry& x, const EXT_PRICECUSTOMER1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICECUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1_mapkey012345_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1_mapkey03_idxfn,false>
  > EXT_PRICECUSTOMER1_map;
  typedef HashIndex<EXT_PRICECUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1_mapkey012345_idxfn,true> HashIndex_EXT_PRICECUSTOMER1_map_012345;
  typedef HashIndex<EXT_PRICECUSTOMER1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1_mapkey03_idxfn,false> HashIndex_EXT_PRICECUSTOMER1_map_03;
  
  struct EXT_PRICECUSTOMER1ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CUSTOMER_SK; long CUSTOMER_C_CURRENT_ADDR_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICECUSTOMER1ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CUSTOMER_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICECUSTOMER1ITEM1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1; CUSTOMER_C_CURRENT_ADDR_SK = c2; __av = c3; }
    EXT_PRICECUSTOMER1ITEM1_entry(const EXT_PRICECUSTOMER1ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER1ITEM1_entry& modify(const long c0, const long c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1; CUSTOMER_C_CURRENT_ADDR_SK = c2;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER1ITEM1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER1ITEM1_entry& modify12(const long c1, const long c2) { STORE_SALES_SS_CUSTOMER_SK = c1; CUSTOMER_C_CURRENT_ADDR_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER1ITEM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1ITEM1_entry& x, const EXT_PRICECUSTOMER1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  struct EXT_PRICECUSTOMER1ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1ITEM1_entry& x, const EXT_PRICECUSTOMER1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct EXT_PRICECUSTOMER1ITEM1_mapkey12_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1ITEM1_entry& x, const EXT_PRICECUSTOMER1ITEM1_entry& y) {
      return x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER1ITEM1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICECUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1ITEM1_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1ITEM1_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICECUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1ITEM1_mapkey12_idxfn,false>
  > EXT_PRICECUSTOMER1ITEM1_map;
  typedef HashIndex<EXT_PRICECUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1ITEM1_mapkey012_idxfn,true> HashIndex_EXT_PRICECUSTOMER1ITEM1_map_012;
  typedef HashIndex<EXT_PRICECUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1ITEM1_mapkey0_idxfn,false> HashIndex_EXT_PRICECUSTOMER1ITEM1_map_0;
  typedef HashIndex<EXT_PRICECUSTOMER1ITEM1_entry,DOUBLE_TYPE,EXT_PRICECUSTOMER1ITEM1_mapkey12_idxfn,false> HashIndex_EXT_PRICECUSTOMER1ITEM1_map_12;
  
  struct EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_STORE_SK; long CUSTOMER_C_CURRENT_ADDR_SK; long __av; 
    explicit EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_STORE_SK = 0L; CUSTOMER_C_CURRENT_ADDR_SK = 0L; __av = 0L; */ }
    explicit EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry(const long c0, const long c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1; __av = c2; }
    EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry(const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), CUSTOMER_C_CURRENT_ADDR_SK( other.CUSTOMER_C_CURRENT_ADDR_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& modify(const long c0, const long c1) { STORE_SALES_SS_STORE_SK = c0; CUSTOMER_C_CURRENT_ADDR_SK = c1;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    FORCE_INLINE EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& modify1(const long c1) { CUSTOMER_C_CURRENT_ADDR_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CURRENT_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& x, const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  struct EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& x, const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CURRENT_ADDR_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& x, const EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry& y) {
      return x.CUSTOMER_C_CURRENT_ADDR_SK == y.CUSTOMER_C_CURRENT_ADDR_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry,long,
    HashIndex<EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey01_idxfn,true>,
    HashIndex<EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey0_idxfn,false>,
    HashIndex<EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey1_idxfn,false>
  > EXT_PRICECUSTOMER1STORE_SALES1_P_3_map;
  typedef HashIndex<EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_01;
  typedef HashIndex<EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey0_idxfn,false> HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0;
  typedef HashIndex<EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry,long,EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey1_idxfn,false> HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_1;
  
  struct EXT_PRICEITEM1_DELTA_entry {
    long STORE_SALES_SS_ITEM_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; long BRAND_ID; STRING_TYPE BRAND; long __av; 
    explicit EXT_PRICEITEM1_DELTA_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; BRAND_ID = 0L; BRAND = ""; __av = 0L; */ }
    explicit EXT_PRICEITEM1_DELTA_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const long c5) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND_ID = c3; BRAND = c4; __av = c5; }
    EXT_PRICEITEM1_DELTA_entry(const EXT_PRICEITEM1_DELTA_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICEITEM1_DELTA_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND_ID = c3; BRAND = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICEITEM1_DELTA_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICEITEM1_DELTA_entry& x, const EXT_PRICEITEM1_DELTA_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  typedef MultiHashMap<EXT_PRICEITEM1_DELTA_entry,long,
    HashIndex<EXT_PRICEITEM1_DELTA_entry,long,EXT_PRICEITEM1_DELTA_mapkey01234_idxfn,true>
  > EXT_PRICEITEM1_DELTA_map;
  typedef HashIndex<EXT_PRICEITEM1_DELTA_entry,long,EXT_PRICEITEM1_DELTA_mapkey01234_idxfn,true> HashIndex_EXT_PRICEITEM1_DELTA_map_01234;
  
  struct EXT_PRICEITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICEITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICEITEM1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_ITEM_SK = c0; __av = c1; }
    EXT_PRICEITEM1_entry(const EXT_PRICEITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICEITEM1_entry& modify(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICEITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICEITEM1_entry& x, const EXT_PRICEITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICEITEM1_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICEITEM1_entry,DOUBLE_TYPE,EXT_PRICEITEM1_mapkey0_idxfn,true>
  > EXT_PRICEITEM1_map;
  typedef HashIndex<EXT_PRICEITEM1_entry,DOUBLE_TYPE,EXT_PRICEITEM1_mapkey0_idxfn,true> HashIndex_EXT_PRICEITEM1_map_0;
  
  struct EXT_PRICESTORE_SALES1_DELTA_entry {
    long DATE_DIM_D_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CUSTOMER_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE_SALES1_DELTA_entry() { /*DATE_DIM_D_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CUSTOMER_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICESTORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { DATE_DIM_D_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CUSTOMER_SK = c2; STORE_SALES_SS_STORE_SK = c3; __av = c4; }
    EXT_PRICESTORE_SALES1_DELTA_entry(const EXT_PRICESTORE_SALES1_DELTA_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { DATE_DIM_D_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CUSTOMER_SK = c2; STORE_SALES_SS_STORE_SK = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_DELTA_entry& x, const EXT_PRICESTORE_SALES1_DELTA_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE_SALES1_DELTA_entry,DOUBLE_TYPE,EXT_PRICESTORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > EXT_PRICESTORE_SALES1_DELTA_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_DELTA_entry,DOUBLE_TYPE,EXT_PRICESTORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123;
  
  struct EXT_PRICESTORE_SALES1_P_1_entry {
    long STORE_SALES_SS_ITEM_SK; long ITEM_I_MANUFACT_ID; STRING_TYPE ITEM_I_MANUFACT; STRING_TYPE BRAND; long BRAND_ID; long __av; 
    explicit EXT_PRICESTORE_SALES1_P_1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_MANUFACT_ID = 0L; ITEM_I_MANUFACT = ""; BRAND = ""; BRAND_ID = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES1_P_1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const long c5) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND = c3; BRAND_ID = c4; __av = c5; }
    EXT_PRICESTORE_SALES1_P_1_entry(const EXT_PRICESTORE_SALES1_P_1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_MANUFACT_ID( other.ITEM_I_MANUFACT_ID ), ITEM_I_MANUFACT( other.ITEM_I_MANUFACT ), BRAND( other.BRAND ), BRAND_ID( other.BRAND_ID ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_MANUFACT_ID = c1; ITEM_I_MANUFACT = c2; BRAND = c3; BRAND_ID = c4;  return *this; }
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_MANUFACT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_P_1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_MANUFACT_ID);
      hash_combine(h, e.ITEM_I_MANUFACT);
      hash_combine(h, e.BRAND);
      hash_combine(h, e.BRAND_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_1_entry& x, const EXT_PRICESTORE_SALES1_P_1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_MANUFACT_ID == y.ITEM_I_MANUFACT_ID && x.ITEM_I_MANUFACT == y.ITEM_I_MANUFACT && x.BRAND == y.BRAND && x.BRAND_ID == y.BRAND_ID;
    }
  };
  
  struct EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_1_entry& x, const EXT_PRICESTORE_SALES1_P_1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_P_1_entry,long,
    HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey01234_idxfn,true>,
    HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn,false>
  > EXT_PRICESTORE_SALES1_P_1_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey01234_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_P_1_map_01234;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0;
  
  struct EXT_PRICESTORE_SALES1_P_2_entry {
    long DATE_DIM_D_DATE_SK; long __av; 
    explicit EXT_PRICESTORE_SALES1_P_2_entry() { /*DATE_DIM_D_DATE_SK = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES1_P_2_entry(const long c0, const long c1) { DATE_DIM_D_DATE_SK = c0; __av = c1; }
    EXT_PRICESTORE_SALES1_P_2_entry(const EXT_PRICESTORE_SALES1_P_2_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_2_entry& modify(const long c0) { DATE_DIM_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_2_entry& x, const EXT_PRICESTORE_SALES1_P_2_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_P_2_entry,long,
    HashIndex<EXT_PRICESTORE_SALES1_P_2_entry,long,EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn,true>
  > EXT_PRICESTORE_SALES1_P_2_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_2_entry,long,EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_P_2_map_0;
  
  struct EXT_PRICESTORE_SALES1_P_3_entry {
    long STORE_SALES_SS_STORE_SK; long STORE_SALES_SS_CUSTOMER_SK; long __av; 
    explicit EXT_PRICESTORE_SALES1_P_3_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_SALES_SS_CUSTOMER_SK = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES1_P_3_entry(const long c0, const long c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1; __av = c2; }
    EXT_PRICESTORE_SALES1_P_3_entry(const EXT_PRICESTORE_SALES1_P_3_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_SALES_SS_CUSTOMER_SK( other.STORE_SALES_SS_CUSTOMER_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_3_entry& modify(const long c0, const long c1) { STORE_SALES_SS_STORE_SK = c0; STORE_SALES_SS_CUSTOMER_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_SALES_SS_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_3_entry& x, const EXT_PRICESTORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_SALES_SS_CUSTOMER_SK == y.STORE_SALES_SS_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_P_3_entry,long,
    HashIndex<EXT_PRICESTORE_SALES1_P_3_entry,long,EXT_PRICESTORE_SALES1_P_3_mapkey01_idxfn,true>
  > EXT_PRICESTORE_SALES1_P_3_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_3_entry,long,EXT_PRICESTORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_P_3_map_01;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS,tLastN;
    tlq_t(): tN(0), tS(0), tLastN(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const EXT_PRICE_map& _EXT_PRICE = get_EXT_PRICE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(EXT_PRICE), _EXT_PRICE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const EXT_PRICE_map& get_EXT_PRICE() const {
      return EXT_PRICE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    EXT_PRICE_map EXT_PRICE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      
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

        EXT_PRICESTORE_SALES1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_STORE_SALES.size; i++) 
          {
                long date_dim_d_date_sk = DELTA_STORE_SALES.ss_sold_date_sk[i];
                // long store_sales_ss_sold_time_sk = DELTA_STORE_SALES.ss_sold_time_sk[i];
                long store_sales_ss_item_sk = DELTA_STORE_SALES.ss_item_sk[i];
                long store_sales_ss_customer_sk = DELTA_STORE_SALES.ss_customer_sk[i];
                // long store_sales_ss_cdemo_sk = DELTA_STORE_SALES.ss_cdemo_sk[i];
                // long store_sales_ss_hdemo_sk = DELTA_STORE_SALES.ss_hdemo_sk[i];
                // long store_sales_ss_addr_sk = DELTA_STORE_SALES.ss_addr_sk[i];
                long store_sales_ss_store_sk = DELTA_STORE_SALES.ss_store_sk[i];
                // long store_sales_ss_promo_sk = DELTA_STORE_SALES.ss_promo_sk[i];
                // long store_sales_ss_ticket_number = DELTA_STORE_SALES.ss_ticket_number[i];
                // long store_sales_ss_quantity = DELTA_STORE_SALES.ss_quantity[i];
                // DOUBLE_TYPE store_sales_ss_wholesale_cost = DELTA_STORE_SALES.ss_wholesale_cost[i];
                // DOUBLE_TYPE store_sales_ss_list_price = DELTA_STORE_SALES.ss_list_price[i];
                // DOUBLE_TYPE store_sales_ss_sales_price = DELTA_STORE_SALES.ss_sales_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_discount_amt = DELTA_STORE_SALES.ss_ext_discount_amt[i];
                DOUBLE_TYPE store_sales_ss_ext_sales_price = DELTA_STORE_SALES.ss_ext_sales_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_wholesale_cost = DELTA_STORE_SALES.ss_ext_wholesale_cost[i];
                // DOUBLE_TYPE store_sales_ss_ext_list_price = DELTA_STORE_SALES.ss_ext_list_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_tax = DELTA_STORE_SALES.ss_ext_tax[i];
                // DOUBLE_TYPE store_sales_ss_coupon_amt = DELTA_STORE_SALES.ss_coupon_amt[i];
                // DOUBLE_TYPE store_sales_ss_net_paid = DELTA_STORE_SALES.ss_net_paid[i];
                // DOUBLE_TYPE store_sales_ss_net_paid_inc_tax = DELTA_STORE_SALES.ss_net_paid_inc_tax[i];
                // DOUBLE_TYPE store_sales_ss_net_profit = DELTA_STORE_SALES.ss_net_profit[i];
                long v1 = 1L;
                EXT_PRICESTORE_SALES1_DELTA.addOrDelOnZero(se1.modify(date_dim_d_date_sk,store_sales_ss_item_sk,store_sales_ss_customer_sk,store_sales_ss_store_sk),(v1 * store_sales_ss_ext_sales_price));
          }
        }

        {  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i2 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n2; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long date_dim_d_date_sk = e2->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e2->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e2->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e2->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0* i3 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0*>(EXT_PRICESTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h1 = EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn::hash(se5.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0::IdxNode* n3 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0::IdxNode*>(i3->slice(se5, h1));
                  EXT_PRICESTORE_SALES1_P_1_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      long item_i_manufact_id = e3->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e3->ITEM_I_MANUFACT;
                      STRING_TYPE brand = e3->BRAND;
                      long brand_id = e3->BRAND_ID;
                      long v3 = e3->__av;
                      EXT_PRICE.addOrDelOnZero(se2.modify(brand_id,brand,item_i_manufact_id,item_i_manufact),(v2 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se3.modify(date_dim_d_date_sk)) * (EXT_PRICESTORE_SALES1_P_3.getValueOrDefault(se4.modify(store_sales_ss_store_sk,store_sales_ss_customer_sk)) * v3))));
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h1 == n3->hash &&  EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn::equals(se5, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i4 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n4; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
                long date_dim_d_date_sk = e4->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e4->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e4->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e4->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v4 = e4->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0* i5 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_2.index[1]);
                  const HASH_RES_t h3 = EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::hash(se9.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode* n5 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode*>(i5->slice(se9, h3));
                  EXT_PRICESTORE1STORE_SALES1_P_2_entry* e5;
                 
                  if (n5 && (e5 = n5->obj)) {
                    do {                
                      long item_i_manufact_id = e5->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e5->ITEM_I_MANUFACT;
                      long brand_id = e5->BRAND_ID;
                      STRING_TYPE brand = e5->BRAND;
                      long v5 = e5->__av;
                      { //slice 
                        const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0* i6 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h2 = EXT_PRICESTORE1STORE_SALES1_P_3_mapkey0_idxfn::hash(se8.modify0(store_sales_ss_customer_sk));
                        HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0::IdxNode* n6 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0::IdxNode*>(i6->slice(se8, h2));
                        EXT_PRICESTORE1STORE_SALES1_P_3_entry* e6;
                       
                        if (n6 && (e6 = n6->obj)) {
                          do {                
                            STRING_TYPE customer_address_ca_zip = e6->CUSTOMER_ADDRESS_CA_ZIP;
                            long v6 = e6->__av;
                            EXT_PRICESTORE1.addOrDelOnZero(se6.modify(store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,customer_address_ca_zip,brand_id,brand),(v4 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se7.modify(date_dim_d_date_sk)) * (v5 * v6))));
                            n6 = n6->nxt;
                          } while (n6 && (e6 = n6->obj) && h2 == n6->hash &&  EXT_PRICESTORE1STORE_SALES1_P_3_mapkey0_idxfn::equals(se8, *e6)); 
                        }
                      }
                      n5 = n5->nxt;
                    } while (n5 && (e5 = n5->obj) && h3 == n5->hash &&  EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::equals(se9, *e5)); 
                  }
                }
              n4 = n4->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i7 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n7; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long date_dim_d_date_sk = e7->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e7->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e7->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e7->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v7 = e7->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0* i8 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_2.index[1]);
                  const HASH_RES_t h5 = EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::hash(se13.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode* n8 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode*>(i8->slice(se13, h5));
                  EXT_PRICESTORE1STORE_SALES1_P_2_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      long item_i_manufact_id = e8->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e8->ITEM_I_MANUFACT;
                      long brand_id = e8->BRAND_ID;
                      STRING_TYPE brand = e8->BRAND;
                      long v8 = e8->__av;
                      { //slice 
                        const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i9 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h4 = EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se12.modify0(store_sales_ss_customer_sk));
                        HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n9 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i9->slice(se12, h4));
                        EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e9;
                       
                        if (n9 && (e9 = n9->obj)) {
                          do {                
                            long customer_c_current_addr_sk = e9->CUSTOMER_C_CURRENT_ADDR_SK;
                            long v9 = e9->__av;
                            EXT_PRICESTORE1CUSTOMER_ADDRESS1.addOrDelOnZero(se10.modify(store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,brand_id,brand),(v7 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se11.modify(date_dim_d_date_sk)) * (v8 * v9))));
                            n9 = n9->nxt;
                          } while (n9 && (e9 = n9->obj) && h4 == n9->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se12, *e9)); 
                        }
                      }
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h5 == n8->hash &&  EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::equals(se13, *e8)); 
                  }
                }
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i10 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n10; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long date_dim_d_date_sk = e10->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e10->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e10->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e10->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v10 = e10->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i11 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h6 = EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se16.modify0(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n11 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i11->slice(se16, h6));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e11;
                 
                  if (n11 && (e11 = n11->obj)) {
                    do {                
                      long customer_c_current_addr_sk = e11->CUSTOMER_C_CURRENT_ADDR_SK;
                      long v11 = e11->__av;
                      EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1.addOrDelOnZero(se14.modify(store_sales_ss_item_sk,store_sales_ss_store_sk,customer_c_current_addr_sk),(v10 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se15.modify(date_dim_d_date_sk)) * v11)));
                      n11 = n11->nxt;
                    } while (n11 && (e11 = n11->obj) && h6 == n11->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se16, *e11)); 
                  }
                }
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i12 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n12; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long date_dim_d_date_sk = e12->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e12->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e12->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e12->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v12 = e12->__av;
                EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1.addOrDelOnZero(se17.modify(store_sales_ss_item_sk,store_sales_ss_customer_sk,store_sales_ss_store_sk),(v12 * EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se18.modify(date_dim_d_date_sk))));
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i13 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n13; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long date_dim_d_date_sk = e13->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e13->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e13->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e13->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v13 = e13->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0* i14 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_2.index[1]);
                  const HASH_RES_t h7 = EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::hash(se21.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode* n14 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode*>(i14->slice(se21, h7));
                  EXT_PRICESTORE1STORE_SALES1_P_2_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      long item_i_manufact_id = e14->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e14->ITEM_I_MANUFACT;
                      long brand_id = e14->BRAND_ID;
                      STRING_TYPE brand = e14->BRAND;
                      long v14 = e14->__av;
                      EXT_PRICESTORE1CUSTOMER1_P_1.addOrDelOnZero(se19.modify(store_sales_ss_customer_sk,store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,brand_id,brand),(v13 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se20.modify(date_dim_d_date_sk)) * v14)));
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h7 == n14->hash &&  EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::equals(se21, *e14)); 
                  }
                }
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i15 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n15; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long date_dim_d_date_sk = e15->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e15->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e15->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e15->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v15 = e15->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0* i16 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h8 = EXT_PRICESTORE1STORE_SALES1_P_3_mapkey0_idxfn::hash(se24.modify0(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0::IdxNode* n16 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_0::IdxNode*>(i16->slice(se24, h8));
                  EXT_PRICESTORE1STORE_SALES1_P_3_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      STRING_TYPE customer_address_ca_zip = e16->CUSTOMER_ADDRESS_CA_ZIP;
                      long v16 = e16->__av;
                      EXT_PRICESTORE1ITEM1.addOrDelOnZero(se22.modify(store_sales_ss_item_sk,store_sales_ss_store_sk,customer_address_ca_zip),(v15 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se23.modify(date_dim_d_date_sk)) * v16)));
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h8 == n16->hash &&  EXT_PRICESTORE1STORE_SALES1_P_3_mapkey0_idxfn::equals(se24, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i17 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n17; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long date_dim_d_date_sk = e17->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e17->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e17->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e17->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v17 = e17->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0* i18 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_2.index[1]);
                  const HASH_RES_t h11 = EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::hash(se29.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode* n18 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode*>(i18->slice(se29, h11));
                  EXT_PRICESTORE1STORE_SALES1_P_2_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      long item_i_manufact_id = e18->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e18->ITEM_I_MANUFACT;
                      long brand_id = e18->BRAND_ID;
                      STRING_TYPE brand = e18->BRAND;
                      long v18 = e18->__av;
                      { //slice 
                        const HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i19 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h10 = EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se28.modify0(store_sales_ss_store_sk));
                        HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n19 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i19->slice(se28, h10));
                        EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e19;
                       
                        if (n19 && (e19 = n19->obj)) {
                          do {                
                            STRING_TYPE store_s_zip = e19->STORE_S_ZIP;
                            long v19 = e19->__av;
                            { //slice 
                              const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i20 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                              const HASH_RES_t h9 = EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se27.modify0(store_sales_ss_customer_sk));
                              HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n20 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i20->slice(se27, h9));
                              EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e20;
                             
                              if (n20 && (e20 = n20->obj)) {
                                do {                
                                  long customer_c_current_addr_sk = e20->CUSTOMER_C_CURRENT_ADDR_SK;
                                  long v20 = e20->__av;
                                  EXT_PRICECUSTOMER_ADDRESS1.addOrDelOnZero(se25.modify(item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,store_s_zip,brand_id,brand),(v17 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se26.modify(date_dim_d_date_sk)) * (v18 * (v19 * v20)))));
                                  n20 = n20->nxt;
                                } while (n20 && (e20 = n20->obj) && h9 == n20->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se27, *e20)); 
                              }
                            }
                            n19 = n19->nxt;
                          } while (n19 && (e19 = n19->obj) && h10 == n19->hash &&  EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se28, *e19)); 
                        }
                      }
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h11 == n18->hash &&  EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::equals(se29, *e18)); 
                  }
                }
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i21 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n21; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long date_dim_d_date_sk = e21->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e21->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e21->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e21->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v21 = e21->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0* i22 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_2.index[1]);
                  const HASH_RES_t h13 = EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::hash(se33.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode* n22 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode*>(i22->slice(se33, h13));
                  EXT_PRICESTORE1STORE_SALES1_P_2_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      long item_i_manufact_id = e22->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e22->ITEM_I_MANUFACT;
                      long brand_id = e22->BRAND_ID;
                      STRING_TYPE brand = e22->BRAND;
                      long v22 = e22->__av;
                      { //slice 
                        const HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i23 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h12 = EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se32.modify0(store_sales_ss_store_sk));
                        HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n23 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i23->slice(se32, h12));
                        EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e23;
                       
                        if (n23 && (e23 = n23->obj)) {
                          do {                
                            STRING_TYPE store_s_zip = e23->STORE_S_ZIP;
                            long v23 = e23->__av;
                            EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1.addOrDelOnZero(se30.modify(store_sales_ss_customer_sk,item_i_manufact_id,item_i_manufact,store_s_zip,brand_id,brand),(v21 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se31.modify(date_dim_d_date_sk)) * (v22 * v23))));
                            n23 = n23->nxt;
                          } while (n23 && (e23 = n23->obj) && h12 == n23->hash &&  EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se32, *e23)); 
                        }
                      }
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h13 == n22->hash &&  EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::equals(se33, *e22)); 
                  }
                }
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i24 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n24; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long date_dim_d_date_sk = e24->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e24->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e24->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e24->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v24 = e24->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i25 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h14 = EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se36.modify0(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n25 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i25->slice(se36, h14));
                  EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e25;
                 
                  if (n25 && (e25 = n25->obj)) {
                    do {                
                      STRING_TYPE store_s_zip = e25->STORE_S_ZIP;
                      long v25 = e25->__av;
                      EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1.addOrDelOnZero(se34.modify(store_sales_ss_item_sk,store_sales_ss_customer_sk,store_s_zip),(v24 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se35.modify(date_dim_d_date_sk)) * v25)));
                      n25 = n25->nxt;
                    } while (n25 && (e25 = n25->obj) && h14 == n25->hash &&  EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se36, *e25)); 
                  }
                }
              n24 = n24->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i26 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n26; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e26;
        
          for (size_t i = 0; i < i26->size_; i++)
          {
            n26 = i26->buckets_ + i;
            while (n26 && (e26 = n26->obj))
            {
                long date_dim_d_date_sk = e26->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e26->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e26->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e26->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v26 = e26->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i27 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h16 = EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se40.modify0(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n27 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i27->slice(se40, h16));
                  EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e27;
                 
                  if (n27 && (e27 = n27->obj)) {
                    do {                
                      STRING_TYPE store_s_zip = e27->STORE_S_ZIP;
                      long v27 = e27->__av;
                      { //slice 
                        const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0* i28 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h15 = EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::hash(se39.modify0(store_sales_ss_customer_sk));
                        HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode* n28 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_0::IdxNode*>(i28->slice(se39, h15));
                        EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e28;
                       
                        if (n28 && (e28 = n28->obj)) {
                          do {                
                            long customer_c_current_addr_sk = e28->CUSTOMER_C_CURRENT_ADDR_SK;
                            long v28 = e28->__av;
                            EXT_PRICECUSTOMER_ADDRESS1ITEM1.addOrDelOnZero(se37.modify(store_sales_ss_item_sk,customer_c_current_addr_sk,store_s_zip),(v26 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se38.modify(date_dim_d_date_sk)) * (v27 * v28))));
                            n28 = n28->nxt;
                          } while (n28 && (e28 = n28->obj) && h15 == n28->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se39, *e28)); 
                        }
                      }
                      n27 = n27->nxt;
                    } while (n27 && (e27 = n27->obj) && h16 == n27->hash &&  EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey0_idxfn::equals(se40, *e27)); 
                  }
                }
              n26 = n26->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i29 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n29; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e29;
        
          for (size_t i = 0; i < i29->size_; i++)
          {
            n29 = i29->buckets_ + i;
            while (n29 && (e29 = n29->obj))
            {
                long date_dim_d_date_sk = e29->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e29->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e29->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e29->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v29 = e29->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0* i30 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0*>(EXT_PRICESTORE1STORE_SALES1_P_2.index[1]);
                  const HASH_RES_t h18 = EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::hash(se44.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode* n30 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_2_map_0::IdxNode*>(i30->slice(se44, h18));
                  EXT_PRICESTORE1STORE_SALES1_P_2_entry* e30;
                 
                  if (n30 && (e30 = n30->obj)) {
                    do {                
                      long item_i_manufact_id = e30->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e30->ITEM_I_MANUFACT;
                      long brand_id = e30->BRAND_ID;
                      STRING_TYPE brand = e30->BRAND;
                      long v30 = e30->__av;
                      { //slice 
                        const HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0* i31 = static_cast<HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0*>(EXT_PRICECUSTOMER1STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h17 = EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey0_idxfn::hash(se43.modify0(store_sales_ss_store_sk));
                        HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0::IdxNode* n31 = static_cast<HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0::IdxNode*>(i31->slice(se43, h17));
                        EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry* e31;
                       
                        if (n31 && (e31 = n31->obj)) {
                          do {                
                            long customer_c_current_addr_sk = e31->CUSTOMER_C_CURRENT_ADDR_SK;
                            long v31 = e31->__av;
                            EXT_PRICECUSTOMER1.addOrDelOnZero(se41.modify(store_sales_ss_customer_sk,item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,brand_id,brand),(v29 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se42.modify(date_dim_d_date_sk)) * (v30 * v31))));
                            n31 = n31->nxt;
                          } while (n31 && (e31 = n31->obj) && h17 == n31->hash &&  EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey0_idxfn::equals(se43, *e31)); 
                        }
                      }
                      n30 = n30->nxt;
                    } while (n30 && (e30 = n30->obj) && h18 == n30->hash &&  EXT_PRICESTORE1STORE_SALES1_P_2_mapkey0_idxfn::equals(se44, *e30)); 
                  }
                }
              n29 = n29->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i32 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n32; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e32;
        
          for (size_t i = 0; i < i32->size_; i++)
          {
            n32 = i32->buckets_ + i;
            while (n32 && (e32 = n32->obj))
            {
                long date_dim_d_date_sk = e32->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e32->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e32->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e32->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v32 = e32->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0* i33 = static_cast<HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0*>(EXT_PRICECUSTOMER1STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h19 = EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey0_idxfn::hash(se47.modify0(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0::IdxNode* n33 = static_cast<HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_0::IdxNode*>(i33->slice(se47, h19));
                  EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry* e33;
                 
                  if (n33 && (e33 = n33->obj)) {
                    do {                
                      long customer_c_current_addr_sk = e33->CUSTOMER_C_CURRENT_ADDR_SK;
                      long v33 = e33->__av;
                      EXT_PRICECUSTOMER1ITEM1.addOrDelOnZero(se45.modify(store_sales_ss_item_sk,store_sales_ss_customer_sk,customer_c_current_addr_sk),(v32 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se46.modify(date_dim_d_date_sk)) * v33)));
                      n33 = n33->nxt;
                    } while (n33 && (e33 = n33->obj) && h19 == n33->hash &&  EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey0_idxfn::equals(se47, *e33)); 
                  }
                }
              n32 = n32->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123* i34 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_0123::IdxNode* n34; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                long date_dim_d_date_sk = e34->DATE_DIM_D_DATE_SK;
                long store_sales_ss_item_sk = e34->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_customer_sk = e34->STORE_SALES_SS_CUSTOMER_SK;
                long store_sales_ss_store_sk = e34->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v34 = e34->__av;
                EXT_PRICEITEM1.addOrDelOnZero(se48.modify(store_sales_ss_item_sk),(v34 * (EXT_PRICESTORE_SALES1_P_2.getValueOrDefault(se49.modify(date_dim_d_date_sk)) * EXT_PRICESTORE_SALES1_P_3.getValueOrDefault(se50.modify(store_sales_ss_store_sk,store_sales_ss_customer_sk)))));
              n34 = n34->nxt;
            }
          }
        }
      }
    }
    void on_batch_update_ITEM(TPCDSItemBatch& DELTA_ITEM) {
      { 
        if (tS > 0) { tS += DELTA_ITEM.size; return; }         
        tLastN += DELTA_ITEM.size;        
        if (tLastN > 127) { 
          gettimeofday(&(t),NULL); 
          tT = (t.tv_sec - t0.tv_sec) * 1000000L + (t.tv_usec - t0.tv_usec); 
          if (tT > 3600000000L) { tS = DELTA_ITEM.size; return; } 
          tLastN = 0;
        }
        tN += DELTA_ITEM.size;

        EXT_PRICEITEM1_DELTA.clear();
        EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_ITEM.size; i++) 
          {
                long store_sales_ss_item_sk = DELTA_ITEM.i_item_sk[i];
                // STRING_TYPE item_i_item_id = DELTA_ITEM.i_item_id[i];
                // date item_i_rec_start_date = DELTA_ITEM.i_rec_start_date[i];
                // date item_i_rec_end_date = DELTA_ITEM.i_rec_end_date[i];
                // STRING_TYPE item_i_item_desc = DELTA_ITEM.i_item_desc[i];
                // DOUBLE_TYPE item_i_current_price = DELTA_ITEM.i_current_price[i];
                // DOUBLE_TYPE item_i_wholesale_cost = DELTA_ITEM.i_wholesale_cost[i];
                long item_i_brand_id = DELTA_ITEM.i_brand_id[i];
                STRING_TYPE item_i_brand = DELTA_ITEM.i_brand[i];
                // long item_i_class_id = DELTA_ITEM.i_class_id[i];
                // STRING_TYPE item_i_class = DELTA_ITEM.i_class[i];
                // long item_i_category_id = DELTA_ITEM.i_category_id[i];
                // STRING_TYPE item_i_category = DELTA_ITEM.i_category[i];
                long item_i_manufact_id = DELTA_ITEM.i_manufact_id[i];
                STRING_TYPE item_i_manufact = DELTA_ITEM.i_manufact[i];
                // STRING_TYPE item_i_size = DELTA_ITEM.i_size[i];
                // STRING_TYPE item_i_formulation = DELTA_ITEM.i_formulation[i];
                // STRING_TYPE item_i_color = DELTA_ITEM.i_color[i];
                // STRING_TYPE item_i_units = DELTA_ITEM.i_units[i];
                // STRING_TYPE item_i_container = DELTA_ITEM.i_container[i];
                long lift1 = DELTA_ITEM.i_manager_id[i];
                // STRING_TYPE item_i_product_name = DELTA_ITEM.i_product_name[i];
                long v35 = 1L;
                (/*if */(lift1 == 7L) ? EXT_PRICEITEM1_DELTA.addOrDelOnZero(se51.modify(store_sales_ss_item_sk,item_i_manufact_id,item_i_manufact,item_i_brand_id,item_i_brand),v35) : (void)0);
                long v36 = 1L;
                (/*if */(lift1 == 7L) ? EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA.addOrDelOnZero(se52.modify(store_sales_ss_item_sk,item_i_manufact_id,item_i_manufact,item_i_brand,item_i_brand_id),v36) : (void)0);

          }
        }

        {  // foreach
          const HashIndex_EXT_PRICEITEM1_DELTA_map_01234* i37 = static_cast<HashIndex_EXT_PRICEITEM1_DELTA_map_01234*>(EXT_PRICEITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICEITEM1_DELTA_map_01234::IdxNode* n37; 
          EXT_PRICEITEM1_DELTA_entry* e37;
        
          for (size_t i = 0; i < i37->size_; i++)
          {
            n37 = i37->buckets_ + i;
            while (n37 && (e37 = n37->obj))
            {
                long store_sales_ss_item_sk = e37->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e37->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e37->ITEM_I_MANUFACT;
                long brand_id = e37->BRAND_ID;
                STRING_TYPE brand = e37->BRAND;
                long v37 = e37->__av;
                EXT_PRICE.addOrDelOnZero(se53.modify(brand_id,brand,item_i_manufact_id,item_i_manufact),(v37 * EXT_PRICEITEM1.getValueOrDefault(se54.modify(store_sales_ss_item_sk))));
              n37 = n37->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICEITEM1_DELTA_map_01234* i38 = static_cast<HashIndex_EXT_PRICEITEM1_DELTA_map_01234*>(EXT_PRICEITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICEITEM1_DELTA_map_01234::IdxNode* n38; 
          EXT_PRICEITEM1_DELTA_entry* e38;
        
          for (size_t i = 0; i < i38->size_; i++)
          {
            n38 = i38->buckets_ + i;
            while (n38 && (e38 = n38->obj))
            {
                long store_sales_ss_item_sk = e38->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e38->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e38->ITEM_I_MANUFACT;
                long brand_id = e38->BRAND_ID;
                STRING_TYPE brand = e38->BRAND;
                long v38 = e38->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1ITEM1_map_0* i39 = static_cast<HashIndex_EXT_PRICESTORE1ITEM1_map_0*>(EXT_PRICESTORE1ITEM1.index[1]);
                  const HASH_RES_t h20 = EXT_PRICESTORE1ITEM1_mapkey0_idxfn::hash(se56.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1ITEM1_map_0::IdxNode* n39 = static_cast<HashIndex_EXT_PRICESTORE1ITEM1_map_0::IdxNode*>(i39->slice(se56, h20));
                  EXT_PRICESTORE1ITEM1_entry* e39;
                 
                  if (n39 && (e39 = n39->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e39->STORE_SALES_SS_STORE_SK;
                      STRING_TYPE customer_address_ca_zip = e39->CUSTOMER_ADDRESS_CA_ZIP;
                      DOUBLE_TYPE v39 = e39->__av;
                      EXT_PRICESTORE1.addOrDelOnZero(se55.modify(store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,customer_address_ca_zip,brand_id,brand),(v38 * v39));
                      n39 = n39->nxt;
                    } while (n39 && (e39 = n39->obj) && h20 == n39->hash &&  EXT_PRICESTORE1ITEM1_mapkey0_idxfn::equals(se56, *e39)); 
                  }
                }
              n38 = n38->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICEITEM1_DELTA_map_01234* i40 = static_cast<HashIndex_EXT_PRICEITEM1_DELTA_map_01234*>(EXT_PRICEITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICEITEM1_DELTA_map_01234::IdxNode* n40; 
          EXT_PRICEITEM1_DELTA_entry* e40;
        
          for (size_t i = 0; i < i40->size_; i++)
          {
            n40 = i40->buckets_ + i;
            while (n40 && (e40 = n40->obj))
            {
                long store_sales_ss_item_sk = e40->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e40->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e40->ITEM_I_MANUFACT;
                long brand_id = e40->BRAND_ID;
                STRING_TYPE brand = e40->BRAND;
                long v40 = e40->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_0* i41 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_0*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1.index[1]);
                  const HASH_RES_t h21 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn::hash(se58.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_0::IdxNode* n41 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_0::IdxNode*>(i41->slice(se58, h21));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry* e41;
                 
                  if (n41 && (e41 = n41->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e41->STORE_SALES_SS_STORE_SK;
                      long customer_c_current_addr_sk = e41->CUSTOMER_C_CURRENT_ADDR_SK;
                      DOUBLE_TYPE v41 = e41->__av;
                      EXT_PRICESTORE1CUSTOMER_ADDRESS1.addOrDelOnZero(se57.modify(store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,brand_id,brand),(v40 * v41));
                      n41 = n41->nxt;
                    } while (n41 && (e41 = n41->obj) && h21 == n41->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn::equals(se58, *e41)); 
                  }
                }
              n40 = n40->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234* i42 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234*>(EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234::IdxNode* n42; 
          EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
                long store_sales_ss_item_sk = e42->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e42->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e42->ITEM_I_MANUFACT;
                STRING_TYPE brand = e42->BRAND;
                long brand_id = e42->BRAND_ID;
                long v42 = e42->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_0* i43 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_0*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1.index[1]);
                  const HASH_RES_t h22 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey0_idxfn::hash(se60.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_0::IdxNode* n43 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_0::IdxNode*>(i43->slice(se60, h22));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry* e43;
                 
                  if (n43 && (e43 = n43->obj)) {
                    do {                
                      long store_sales_ss_customer_sk = e43->STORE_SALES_SS_CUSTOMER_SK;
                      long store_sales_ss_store_sk = e43->STORE_SALES_SS_STORE_SK;
                      DOUBLE_TYPE v43 = e43->__av;
                      EXT_PRICESTORE1CUSTOMER1_P_1.addOrDelOnZero(se59.modify(store_sales_ss_customer_sk,store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,brand_id,brand),(v42 * v43));
                      n43 = n43->nxt;
                    } while (n43 && (e43 = n43->obj) && h22 == n43->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey0_idxfn::equals(se60, *e43)); 
                  }
                }
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234* i44 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234*>(EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234::IdxNode* n44; 
          EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry* e44;
        
          for (size_t i = 0; i < i44->size_; i++)
          {
            n44 = i44->buckets_ + i;
            while (n44 && (e44 = n44->obj))
            {
                long store_sales_ss_item_sk = e44->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e44->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e44->ITEM_I_MANUFACT;
                STRING_TYPE brand = e44->BRAND;
                long brand_id = e44->BRAND_ID;
                long v44 = e44->__av;
                EXT_PRICESTORE1STORE_SALES1_P_2.addOrDelOnZero(se61.modify(store_sales_ss_item_sk,item_i_manufact_id,item_i_manufact,brand_id,brand),v44);
              n44 = n44->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234* i45 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234*>(EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map_01234::IdxNode* n45; 
          EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry* e45;
        
          for (size_t i = 0; i < i45->size_; i++)
          {
            n45 = i45->buckets_ + i;
            while (n45 && (e45 = n45->obj))
            {
                long store_sales_ss_item_sk = e45->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e45->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e45->ITEM_I_MANUFACT;
                STRING_TYPE brand = e45->BRAND;
                long brand_id = e45->BRAND_ID;
                long v45 = e45->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_0* i46 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_0*>(EXT_PRICECUSTOMER_ADDRESS1ITEM1.index[1]);
                  const HASH_RES_t h23 = EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn::hash(se63.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_0::IdxNode* n46 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_0::IdxNode*>(i46->slice(se63, h23));
                  EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry* e46;
                 
                  if (n46 && (e46 = n46->obj)) {
                    do {                
                      long customer_c_current_addr_sk = e46->CUSTOMER_C_CURRENT_ADDR_SK;
                      STRING_TYPE store_s_zip = e46->STORE_S_ZIP;
                      DOUBLE_TYPE v46 = e46->__av;
                      EXT_PRICECUSTOMER_ADDRESS1.addOrDelOnZero(se62.modify(item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,store_s_zip,brand_id,brand),(v45 * v46));
                      n46 = n46->nxt;
                    } while (n46 && (e46 = n46->obj) && h23 == n46->hash &&  EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey0_idxfn::equals(se63, *e46)); 
                  }
                }
              n45 = n45->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICEITEM1_DELTA_map_01234* i47 = static_cast<HashIndex_EXT_PRICEITEM1_DELTA_map_01234*>(EXT_PRICEITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICEITEM1_DELTA_map_01234::IdxNode* n47; 
          EXT_PRICEITEM1_DELTA_entry* e47;
        
          for (size_t i = 0; i < i47->size_; i++)
          {
            n47 = i47->buckets_ + i;
            while (n47 && (e47 = n47->obj))
            {
                long store_sales_ss_item_sk = e47->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e47->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e47->ITEM_I_MANUFACT;
                long brand_id = e47->BRAND_ID;
                STRING_TYPE brand = e47->BRAND;
                long v47 = e47->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_0* i48 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_0*>(EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1.index[1]);
                  const HASH_RES_t h24 = EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey0_idxfn::hash(se65.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_0::IdxNode* n48 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_0::IdxNode*>(i48->slice(se65, h24));
                  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry* e48;
                 
                  if (n48 && (e48 = n48->obj)) {
                    do {                
                      long store_sales_ss_customer_sk = e48->STORE_SALES_SS_CUSTOMER_SK;
                      STRING_TYPE store_s_zip = e48->STORE_S_ZIP;
                      DOUBLE_TYPE v48 = e48->__av;
                      EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1.addOrDelOnZero(se64.modify(store_sales_ss_customer_sk,item_i_manufact_id,item_i_manufact,store_s_zip,brand_id,brand),(v47 * v48));
                      n48 = n48->nxt;
                    } while (n48 && (e48 = n48->obj) && h24 == n48->hash &&  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey0_idxfn::equals(se65, *e48)); 
                  }
                }
              n47 = n47->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICEITEM1_DELTA_map_01234* i49 = static_cast<HashIndex_EXT_PRICEITEM1_DELTA_map_01234*>(EXT_PRICEITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICEITEM1_DELTA_map_01234::IdxNode* n49; 
          EXT_PRICEITEM1_DELTA_entry* e49;
        
          for (size_t i = 0; i < i49->size_; i++)
          {
            n49 = i49->buckets_ + i;
            while (n49 && (e49 = n49->obj))
            {
                long store_sales_ss_item_sk = e49->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e49->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e49->ITEM_I_MANUFACT;
                long brand_id = e49->BRAND_ID;
                STRING_TYPE brand = e49->BRAND;
                long v49 = e49->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER1ITEM1_map_0* i50 = static_cast<HashIndex_EXT_PRICECUSTOMER1ITEM1_map_0*>(EXT_PRICECUSTOMER1ITEM1.index[1]);
                  const HASH_RES_t h25 = EXT_PRICECUSTOMER1ITEM1_mapkey0_idxfn::hash(se67.modify0(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICECUSTOMER1ITEM1_map_0::IdxNode* n50 = static_cast<HashIndex_EXT_PRICECUSTOMER1ITEM1_map_0::IdxNode*>(i50->slice(se67, h25));
                  EXT_PRICECUSTOMER1ITEM1_entry* e50;
                 
                  if (n50 && (e50 = n50->obj)) {
                    do {                
                      long store_sales_ss_customer_sk = e50->STORE_SALES_SS_CUSTOMER_SK;
                      long customer_c_current_addr_sk = e50->CUSTOMER_C_CURRENT_ADDR_SK;
                      DOUBLE_TYPE v50 = e50->__av;
                      EXT_PRICECUSTOMER1.addOrDelOnZero(se66.modify(store_sales_ss_customer_sk,item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,brand_id,brand),(v49 * v50));
                      n50 = n50->nxt;
                    } while (n50 && (e50 = n50->obj) && h25 == n50->hash &&  EXT_PRICECUSTOMER1ITEM1_mapkey0_idxfn::equals(se67, *e50)); 
                  }
                }
              n49 = n49->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICEITEM1_DELTA_map_01234* i51 = static_cast<HashIndex_EXT_PRICEITEM1_DELTA_map_01234*>(EXT_PRICEITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICEITEM1_DELTA_map_01234::IdxNode* n51; 
          EXT_PRICEITEM1_DELTA_entry* e51;
        
          for (size_t i = 0; i < i51->size_; i++)
          {
            n51 = i51->buckets_ + i;
            while (n51 && (e51 = n51->obj))
            {
                long store_sales_ss_item_sk = e51->STORE_SALES_SS_ITEM_SK;
                long item_i_manufact_id = e51->ITEM_I_MANUFACT_ID;
                STRING_TYPE item_i_manufact = e51->ITEM_I_MANUFACT;
                long brand_id = e51->BRAND_ID;
                STRING_TYPE brand = e51->BRAND;
                long v51 = e51->__av;
                EXT_PRICESTORE_SALES1_P_1.addOrDelOnZero(se68.modify(store_sales_ss_item_sk,item_i_manufact_id,item_i_manufact,brand,brand_id),v51);
              n51 = n51->nxt;
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

        EXT_PRICECUSTOMER1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_CUSTOMER.size; i++) 
          {
                long store_sales_ss_customer_sk = DELTA_CUSTOMER.c_customer_sk[i];
                // STRING_TYPE customer_c_customer_id = DELTA_CUSTOMER.c_customer_id[i];
                // long customer_c_current_cdemo_sk = DELTA_CUSTOMER.c_current_cdemo_sk[i];
                // long customer_c_current_hdemo_sk = DELTA_CUSTOMER.c_current_hdemo_sk[i];
                long customer_c_current_addr_sk = DELTA_CUSTOMER.c_current_addr_sk[i];
                // long customer_c_first_shipto_date_sk = DELTA_CUSTOMER.c_first_shipto_date_sk[i];
                // long customer_c_first_sales_date_sk = DELTA_CUSTOMER.c_first_sales_date_sk[i];
                // STRING_TYPE customer_c_salutation = DELTA_CUSTOMER.c_salutation[i];
                // STRING_TYPE customer_c_first_name = DELTA_CUSTOMER.c_first_name[i];
                // STRING_TYPE customer_c_last_name = DELTA_CUSTOMER.c_last_name[i];
                // STRING_TYPE customer_c_preferred_cust_flag = DELTA_CUSTOMER.c_preferred_cust_flag[i];
                // long customer_c_birth_day = DELTA_CUSTOMER.c_birth_day[i];
                // long customer_c_birth_month = DELTA_CUSTOMER.c_birth_month[i];
                // long customer_c_birth_year = DELTA_CUSTOMER.c_birth_year[i];
                // STRING_TYPE customer_c_birth_country = DELTA_CUSTOMER.c_birth_country[i];
                // STRING_TYPE customer_c_login = DELTA_CUSTOMER.c_login[i];
                // STRING_TYPE customer_c_email_address = DELTA_CUSTOMER.c_email_address[i];
                // STRING_TYPE customer_c_last_review_date = DELTA_CUSTOMER.c_last_review_date[i];
                long v52 = 1L;
                EXT_PRICECUSTOMER1_DELTA.addOrDelOnZero(se69.modify(store_sales_ss_customer_sk,customer_c_current_addr_sk),v52);
          }
        }

        {  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i53 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n53; 
          EXT_PRICECUSTOMER1_DELTA_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long store_sales_ss_customer_sk = e53->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e53->CUSTOMER_C_CURRENT_ADDR_SK;
                long v53 = e53->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER1_map_03* i54 = static_cast<HashIndex_EXT_PRICECUSTOMER1_map_03*>(EXT_PRICECUSTOMER1.index[1]);
                  const HASH_RES_t h26 = EXT_PRICECUSTOMER1_mapkey03_idxfn::hash(se71.modify03(store_sales_ss_customer_sk, customer_c_current_addr_sk));
                  HashIndex_EXT_PRICECUSTOMER1_map_03::IdxNode* n54 = static_cast<HashIndex_EXT_PRICECUSTOMER1_map_03::IdxNode*>(i54->slice(se71, h26));
                  EXT_PRICECUSTOMER1_entry* e54;
                 
                  if (n54 && (e54 = n54->obj)) {
                    do {                
                      long item_i_manufact_id = e54->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e54->ITEM_I_MANUFACT;
                      long brand_id = e54->BRAND_ID;
                      STRING_TYPE brand = e54->BRAND;
                      DOUBLE_TYPE v54 = e54->__av;
                      EXT_PRICE.addOrDelOnZero(se70.modify(brand_id,brand,item_i_manufact_id,item_i_manufact),(v53 * v54));
                      n54 = n54->nxt;
                    } while (n54 && (e54 = n54->obj) && h26 == n54->hash &&  EXT_PRICECUSTOMER1_mapkey03_idxfn::equals(se71, *e54)); 
                  }
                }
              n53 = n53->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i55 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n55; 
          EXT_PRICECUSTOMER1_DELTA_entry* e55;
        
          for (size_t i = 0; i < i55->size_; i++)
          {
            n55 = i55->buckets_ + i;
            while (n55 && (e55 = n55->obj))
            {
                long store_sales_ss_customer_sk = e55->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e55->CUSTOMER_C_CURRENT_ADDR_SK;
                long v55 = e55->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0* i56 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0*>(EXT_PRICESTORE1CUSTOMER1_P_1.index[1]);
                  const HASH_RES_t h28 = EXT_PRICESTORE1CUSTOMER1_P_1_mapkey0_idxfn::hash(se74.modify0(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0::IdxNode* n56 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0::IdxNode*>(i56->slice(se74, h28));
                  EXT_PRICESTORE1CUSTOMER1_P_1_entry* e56;
                 
                  if (n56 && (e56 = n56->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e56->STORE_SALES_SS_STORE_SK;
                      long item_i_manufact_id = e56->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e56->ITEM_I_MANUFACT;
                      long brand_id = e56->BRAND_ID;
                      STRING_TYPE brand = e56->BRAND;
                      DOUBLE_TYPE v56 = e56->__av;
                      { //slice 
                        const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0* i57 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0*>(EXT_PRICESTORE1CUSTOMER1_P_2.index[1]);
                        const HASH_RES_t h27 = EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn::hash(se73.modify0(customer_c_current_addr_sk));
                        HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0::IdxNode* n57 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0::IdxNode*>(i57->slice(se73, h27));
                        EXT_PRICESTORE1CUSTOMER1_P_2_entry* e57;
                       
                        if (n57 && (e57 = n57->obj)) {
                          do {                
                            STRING_TYPE customer_address_ca_zip = e57->CUSTOMER_ADDRESS_CA_ZIP;
                            long v57 = e57->__av;
                            EXT_PRICESTORE1.addOrDelOnZero(se72.modify(store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,customer_address_ca_zip,brand_id,brand),(v55 * (v56 * v57)));
                            n57 = n57->nxt;
                          } while (n57 && (e57 = n57->obj) && h27 == n57->hash &&  EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn::equals(se73, *e57)); 
                        }
                      }
                      n56 = n56->nxt;
                    } while (n56 && (e56 = n56->obj) && h28 == n56->hash &&  EXT_PRICESTORE1CUSTOMER1_P_1_mapkey0_idxfn::equals(se74, *e56)); 
                  }
                }
              n55 = n55->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i58 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n58; 
          EXT_PRICECUSTOMER1_DELTA_entry* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
                long store_sales_ss_customer_sk = e58->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e58->CUSTOMER_C_CURRENT_ADDR_SK;
                long v58 = e58->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0* i59 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0*>(EXT_PRICESTORE1CUSTOMER1_P_1.index[1]);
                  const HASH_RES_t h29 = EXT_PRICESTORE1CUSTOMER1_P_1_mapkey0_idxfn::hash(se76.modify0(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0::IdxNode* n59 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_0::IdxNode*>(i59->slice(se76, h29));
                  EXT_PRICESTORE1CUSTOMER1_P_1_entry* e59;
                 
                  if (n59 && (e59 = n59->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e59->STORE_SALES_SS_STORE_SK;
                      long item_i_manufact_id = e59->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e59->ITEM_I_MANUFACT;
                      long brand_id = e59->BRAND_ID;
                      STRING_TYPE brand = e59->BRAND;
                      DOUBLE_TYPE v59 = e59->__av;
                      EXT_PRICESTORE1CUSTOMER_ADDRESS1.addOrDelOnZero(se75.modify(store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,brand_id,brand),(v58 * v59));
                      n59 = n59->nxt;
                    } while (n59 && (e59 = n59->obj) && h29 == n59->hash &&  EXT_PRICESTORE1CUSTOMER1_P_1_mapkey0_idxfn::equals(se76, *e59)); 
                  }
                }
              n58 = n58->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i60 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n60; 
          EXT_PRICECUSTOMER1_DELTA_entry* e60;
        
          for (size_t i = 0; i < i60->size_; i++)
          {
            n60 = i60->buckets_ + i;
            while (n60 && (e60 = n60->obj))
            {
                long store_sales_ss_customer_sk = e60->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e60->CUSTOMER_C_CURRENT_ADDR_SK;
                long v60 = e60->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1* i61 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1.index[2]);
                  const HASH_RES_t h30 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey1_idxfn::hash(se78.modify1(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1::IdxNode* n61 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1::IdxNode*>(i61->slice(se78, h30));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry* e61;
                 
                  if (n61 && (e61 = n61->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e61->STORE_SALES_SS_ITEM_SK;
                      long store_sales_ss_store_sk = e61->STORE_SALES_SS_STORE_SK;
                      DOUBLE_TYPE v61 = e61->__av;
                      EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1.addOrDelOnZero(se77.modify(store_sales_ss_item_sk,store_sales_ss_store_sk,customer_c_current_addr_sk),(v60 * v61));
                      n61 = n61->nxt;
                    } while (n61 && (e61 = n61->obj) && h30 == n61->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey1_idxfn::equals(se78, *e61)); 
                  }
                }
              n60 = n60->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i62 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n62; 
          EXT_PRICECUSTOMER1_DELTA_entry* e62;
        
          for (size_t i = 0; i < i62->size_; i++)
          {
            n62 = i62->buckets_ + i;
            while (n62 && (e62 = n62->obj))
            {
                long store_sales_ss_customer_sk = e62->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e62->CUSTOMER_C_CURRENT_ADDR_SK;
                long v62 = e62->__av;
                EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3.addOrDelOnZero(se79.modify(store_sales_ss_customer_sk,customer_c_current_addr_sk),v62);
              n62 = n62->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i63 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n63; 
          EXT_PRICECUSTOMER1_DELTA_entry* e63;
        
          for (size_t i = 0; i < i63->size_; i++)
          {
            n63 = i63->buckets_ + i;
            while (n63 && (e63 = n63->obj))
            {
                long store_sales_ss_customer_sk = e63->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e63->CUSTOMER_C_CURRENT_ADDR_SK;
                long v63 = e63->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1* i64 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1.index[2]);
                  const HASH_RES_t h32 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey1_idxfn::hash(se82.modify1(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1::IdxNode* n64 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_1::IdxNode*>(i64->slice(se82, h32));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry* e64;
                 
                  if (n64 && (e64 = n64->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e64->STORE_SALES_SS_ITEM_SK;
                      long store_sales_ss_store_sk = e64->STORE_SALES_SS_STORE_SK;
                      DOUBLE_TYPE v64 = e64->__av;
                      { //slice 
                        const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0* i65 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0*>(EXT_PRICESTORE1CUSTOMER1_P_2.index[1]);
                        const HASH_RES_t h31 = EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn::hash(se81.modify0(customer_c_current_addr_sk));
                        HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0::IdxNode* n65 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0::IdxNode*>(i65->slice(se81, h31));
                        EXT_PRICESTORE1CUSTOMER1_P_2_entry* e65;
                       
                        if (n65 && (e65 = n65->obj)) {
                          do {                
                            STRING_TYPE customer_address_ca_zip = e65->CUSTOMER_ADDRESS_CA_ZIP;
                            long v65 = e65->__av;
                            EXT_PRICESTORE1ITEM1.addOrDelOnZero(se80.modify(store_sales_ss_item_sk,store_sales_ss_store_sk,customer_address_ca_zip),(v63 * (v64 * v65)));
                            n65 = n65->nxt;
                          } while (n65 && (e65 = n65->obj) && h31 == n65->hash &&  EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn::equals(se81, *e65)); 
                        }
                      }
                      n64 = n64->nxt;
                    } while (n64 && (e64 = n64->obj) && h32 == n64->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey1_idxfn::equals(se82, *e64)); 
                  }
                }
              n63 = n63->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i66 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n66; 
          EXT_PRICECUSTOMER1_DELTA_entry* e66;
        
          for (size_t i = 0; i < i66->size_; i++)
          {
            n66 = i66->buckets_ + i;
            while (n66 && (e66 = n66->obj))
            {
                long store_sales_ss_customer_sk = e66->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e66->CUSTOMER_C_CURRENT_ADDR_SK;
                long v66 = e66->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0* i67 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0*>(EXT_PRICESTORE1CUSTOMER1_P_2.index[1]);
                  const HASH_RES_t h33 = EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn::hash(se84.modify0(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0::IdxNode* n67 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_0::IdxNode*>(i67->slice(se84, h33));
                  EXT_PRICESTORE1CUSTOMER1_P_2_entry* e67;
                 
                  if (n67 && (e67 = n67->obj)) {
                    do {                
                      STRING_TYPE customer_address_ca_zip = e67->CUSTOMER_ADDRESS_CA_ZIP;
                      long v67 = e67->__av;
                      EXT_PRICESTORE1STORE_SALES1_P_3.addOrDelOnZero(se83.modify(store_sales_ss_customer_sk,customer_address_ca_zip),(v66 * v67));
                      n67 = n67->nxt;
                    } while (n67 && (e67 = n67->obj) && h33 == n67->hash &&  EXT_PRICESTORE1CUSTOMER1_P_2_mapkey0_idxfn::equals(se84, *e67)); 
                  }
                }
              n66 = n66->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i68 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n68; 
          EXT_PRICECUSTOMER1_DELTA_entry* e68;
        
          for (size_t i = 0; i < i68->size_; i++)
          {
            n68 = i68->buckets_ + i;
            while (n68 && (e68 = n68->obj))
            {
                long store_sales_ss_customer_sk = e68->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e68->CUSTOMER_C_CURRENT_ADDR_SK;
                long v68 = e68->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_0* i69 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_0*>(EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1.index[1]);
                  const HASH_RES_t h34 = EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey0_idxfn::hash(se86.modify0(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_0::IdxNode* n69 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_0::IdxNode*>(i69->slice(se86, h34));
                  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry* e69;
                 
                  if (n69 && (e69 = n69->obj)) {
                    do {                
                      long item_i_manufact_id = e69->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e69->ITEM_I_MANUFACT;
                      STRING_TYPE store_s_zip = e69->STORE_S_ZIP;
                      long brand_id = e69->BRAND_ID;
                      STRING_TYPE brand = e69->BRAND;
                      DOUBLE_TYPE v69 = e69->__av;
                      EXT_PRICECUSTOMER_ADDRESS1.addOrDelOnZero(se85.modify(item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,store_s_zip,brand_id,brand),(v68 * v69));
                      n69 = n69->nxt;
                    } while (n69 && (e69 = n69->obj) && h34 == n69->hash &&  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_mapkey0_idxfn::equals(se86, *e69)); 
                  }
                }
              n68 = n68->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i70 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n70; 
          EXT_PRICECUSTOMER1_DELTA_entry* e70;
        
          for (size_t i = 0; i < i70->size_; i++)
          {
            n70 = i70->buckets_ + i;
            while (n70 && (e70 = n70->obj))
            {
                long store_sales_ss_customer_sk = e70->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e70->CUSTOMER_C_CURRENT_ADDR_SK;
                long v70 = e70->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_1* i71 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_1*>(EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1.index[2]);
                  const HASH_RES_t h35 = EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey1_idxfn::hash(se88.modify1(store_sales_ss_customer_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_1::IdxNode* n71 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_1::IdxNode*>(i71->slice(se88, h35));
                  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry* e71;
                 
                  if (n71 && (e71 = n71->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e71->STORE_SALES_SS_ITEM_SK;
                      STRING_TYPE store_s_zip = e71->STORE_S_ZIP;
                      DOUBLE_TYPE v71 = e71->__av;
                      EXT_PRICECUSTOMER_ADDRESS1ITEM1.addOrDelOnZero(se87.modify(store_sales_ss_item_sk,customer_c_current_addr_sk,store_s_zip),(v70 * v71));
                      n71 = n71->nxt;
                    } while (n71 && (e71 = n71->obj) && h35 == n71->hash &&  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_mapkey1_idxfn::equals(se88, *e71)); 
                  }
                }
              n70 = n70->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i72 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n72; 
          EXT_PRICECUSTOMER1_DELTA_entry* e72;
        
          for (size_t i = 0; i < i72->size_; i++)
          {
            n72 = i72->buckets_ + i;
            while (n72 && (e72 = n72->obj))
            {
                long store_sales_ss_customer_sk = e72->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e72->CUSTOMER_C_CURRENT_ADDR_SK;
                long v72 = e72->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER1ITEM1_map_12* i73 = static_cast<HashIndex_EXT_PRICECUSTOMER1ITEM1_map_12*>(EXT_PRICECUSTOMER1ITEM1.index[2]);
                  const HASH_RES_t h36 = EXT_PRICECUSTOMER1ITEM1_mapkey12_idxfn::hash(se90.modify12(store_sales_ss_customer_sk, customer_c_current_addr_sk));
                  HashIndex_EXT_PRICECUSTOMER1ITEM1_map_12::IdxNode* n73 = static_cast<HashIndex_EXT_PRICECUSTOMER1ITEM1_map_12::IdxNode*>(i73->slice(se90, h36));
                  EXT_PRICECUSTOMER1ITEM1_entry* e73;
                 
                  if (n73 && (e73 = n73->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e73->STORE_SALES_SS_ITEM_SK;
                      DOUBLE_TYPE v73 = e73->__av;
                      EXT_PRICEITEM1.addOrDelOnZero(se89.modify(store_sales_ss_item_sk),(v72 * v73));
                      n73 = n73->nxt;
                    } while (n73 && (e73 = n73->obj) && h36 == n73->hash &&  EXT_PRICECUSTOMER1ITEM1_mapkey12_idxfn::equals(se90, *e73)); 
                  }
                }
              n72 = n72->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01* i74 = static_cast<HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01*>(EXT_PRICECUSTOMER1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER1_DELTA_map_01::IdxNode* n74; 
          EXT_PRICECUSTOMER1_DELTA_entry* e74;
        
          for (size_t i = 0; i < i74->size_; i++)
          {
            n74 = i74->buckets_ + i;
            while (n74 && (e74 = n74->obj))
            {
                long store_sales_ss_customer_sk = e74->STORE_SALES_SS_CUSTOMER_SK;
                long customer_c_current_addr_sk = e74->CUSTOMER_C_CURRENT_ADDR_SK;
                long v74 = e74->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_1* i75 = static_cast<HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_1*>(EXT_PRICECUSTOMER1STORE_SALES1_P_3.index[2]);
                  const HASH_RES_t h37 = EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey1_idxfn::hash(se92.modify1(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_1::IdxNode* n75 = static_cast<HashIndex_EXT_PRICECUSTOMER1STORE_SALES1_P_3_map_1::IdxNode*>(i75->slice(se92, h37));
                  EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry* e75;
                 
                  if (n75 && (e75 = n75->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e75->STORE_SALES_SS_STORE_SK;
                      long v75 = e75->__av;
                      EXT_PRICESTORE_SALES1_P_3.addOrDelOnZero(se91.modify(store_sales_ss_store_sk,store_sales_ss_customer_sk),(v74 * v75));
                      n75 = n75->nxt;
                    } while (n75 && (e75 = n75->obj) && h37 == n75->hash &&  EXT_PRICECUSTOMER1STORE_SALES1_P_3_mapkey1_idxfn::equals(se92, *e75)); 
                  }
                }
              n74 = n74->nxt;
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

        EXT_PRICECUSTOMER_ADDRESS1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_CUSTOMER_ADDRESS.size; i++) 
          {
                long customer_c_current_addr_sk = DELTA_CUSTOMER_ADDRESS.ca_address_sk[i];
                // STRING_TYPE customer_address_ca_address_id = DELTA_CUSTOMER_ADDRESS.ca_address_id[i];
                // STRING_TYPE customer_address_ca_street_number = DELTA_CUSTOMER_ADDRESS.ca_street_number[i];
                // STRING_TYPE customer_address_ca_street_name = DELTA_CUSTOMER_ADDRESS.ca_street_name[i];
                // STRING_TYPE customer_address_ca_street_type = DELTA_CUSTOMER_ADDRESS.ca_street_type[i];
                // STRING_TYPE customer_address_ca_suite_number = DELTA_CUSTOMER_ADDRESS.ca_suite_number[i];
                // STRING_TYPE customer_address_ca_city = DELTA_CUSTOMER_ADDRESS.ca_city[i];
                // STRING_TYPE customer_address_ca_county = DELTA_CUSTOMER_ADDRESS.ca_county[i];
                // STRING_TYPE customer_address_ca_state = DELTA_CUSTOMER_ADDRESS.ca_state[i];
                STRING_TYPE customer_address_ca_zip = DELTA_CUSTOMER_ADDRESS.ca_zip[i];
                // STRING_TYPE customer_address_ca_country = DELTA_CUSTOMER_ADDRESS.ca_country[i];
                // DOUBLE_TYPE customer_address_ca_gmt_offset = DELTA_CUSTOMER_ADDRESS.ca_gmt_offset[i];
                // STRING_TYPE customer_address_ca_location_type = DELTA_CUSTOMER_ADDRESS.ca_location_type[i];
                long v76 = 1L;
                EXT_PRICECUSTOMER_ADDRESS1_DELTA.addOrDelOnZero(se93.modify(customer_c_current_addr_sk,customer_address_ca_zip),v76);

          }
        }

        {  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i77 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n77; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e77;
        
          for (size_t i = 0; i < i77->size_; i++)
          {
            n77 = i77->buckets_ + i;
            while (n77 && (e77 = n77->obj))
            {
                long customer_c_current_addr_sk = e77->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e77->CUSTOMER_ADDRESS_CA_ZIP;
                long v77 = e77->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_map_2* i78 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_map_2*>(EXT_PRICECUSTOMER_ADDRESS1.index[1]);
                  const HASH_RES_t h38 = EXT_PRICECUSTOMER_ADDRESS1_mapkey2_idxfn::hash(se95.modify2(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1_map_2::IdxNode* n78 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_map_2::IdxNode*>(i78->slice(se95, h38));
                  EXT_PRICECUSTOMER_ADDRESS1_entry* e78;
                 
                  if (n78 && (e78 = n78->obj)) {
                    do {                
                      long item_i_manufact_id = e78->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e78->ITEM_I_MANUFACT;
                      STRING_TYPE store_s_zip = e78->STORE_S_ZIP;
                      long brand_id = e78->BRAND_ID;
                      STRING_TYPE brand = e78->BRAND;
                      DOUBLE_TYPE v78 = e78->__av;
                      (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICE.addOrDelOnZero(se94.modify(brand_id,brand,item_i_manufact_id,item_i_manufact),(v77 * v78)) : (void)0);
                      n78 = n78->nxt;
                    } while (n78 && (e78 = n78->obj) && h38 == n78->hash &&  EXT_PRICECUSTOMER_ADDRESS1_mapkey2_idxfn::equals(se95, *e78)); 
                  }
                }
              n77 = n77->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i79 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n79; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e79;
        
          for (size_t i = 0; i < i79->size_; i++)
          {
            n79 = i79->buckets_ + i;
            while (n79 && (e79 = n79->obj))
            {
                long customer_c_current_addr_sk = e79->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e79->CUSTOMER_ADDRESS_CA_ZIP;
                long v79 = e79->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_3* i80 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_3*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1.index[1]);
                  const HASH_RES_t h39 = EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey3_idxfn::hash(se97.modify3(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_3::IdxNode* n80 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_3::IdxNode*>(i80->slice(se97, h39));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry* e80;
                 
                  if (n80 && (e80 = n80->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e80->STORE_SALES_SS_STORE_SK;
                      long item_i_manufact_id = e80->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e80->ITEM_I_MANUFACT;
                      long brand_id = e80->BRAND_ID;
                      STRING_TYPE brand = e80->BRAND;
                      DOUBLE_TYPE v80 = e80->__av;
                      EXT_PRICESTORE1.addOrDelOnZero(se96.modify(store_sales_ss_store_sk,item_i_manufact_id,item_i_manufact,customer_address_ca_zip,brand_id,brand),(v79 * v80));
                      n80 = n80->nxt;
                    } while (n80 && (e80 = n80->obj) && h39 == n80->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey3_idxfn::equals(se97, *e80)); 
                  }
                }
              n79 = n79->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i81 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n81; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e81;
        
          for (size_t i = 0; i < i81->size_; i++)
          {
            n81 = i81->buckets_ + i;
            while (n81 && (e81 = n81->obj))
            {
                long customer_c_current_addr_sk = e81->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e81->CUSTOMER_ADDRESS_CA_ZIP;
                long v81 = e81->__av;
                EXT_PRICESTORE1CUSTOMER1_P_2.addOrDelOnZero(se98.modify(customer_c_current_addr_sk,customer_address_ca_zip),v81);
              n81 = n81->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i82 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n82; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e82;
        
          for (size_t i = 0; i < i82->size_; i++)
          {
            n82 = i82->buckets_ + i;
            while (n82 && (e82 = n82->obj))
            {
                long customer_c_current_addr_sk = e82->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e82->CUSTOMER_ADDRESS_CA_ZIP;
                long v82 = e82->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_2* i83 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_2*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1.index[2]);
                  const HASH_RES_t h40 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey2_idxfn::hash(se100.modify2(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_2::IdxNode* n83 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_2::IdxNode*>(i83->slice(se100, h40));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry* e83;
                 
                  if (n83 && (e83 = n83->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e83->STORE_SALES_SS_ITEM_SK;
                      long store_sales_ss_store_sk = e83->STORE_SALES_SS_STORE_SK;
                      DOUBLE_TYPE v83 = e83->__av;
                      EXT_PRICESTORE1ITEM1.addOrDelOnZero(se99.modify(store_sales_ss_item_sk,store_sales_ss_store_sk,customer_address_ca_zip),(v82 * v83));
                      n83 = n83->nxt;
                    } while (n83 && (e83 = n83->obj) && h40 == n83->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey2_idxfn::equals(se100, *e83)); 
                  }
                }
              n82 = n82->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i84 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n84; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e84;
        
          for (size_t i = 0; i < i84->size_; i++)
          {
            n84 = i84->buckets_ + i;
            while (n84 && (e84 = n84->obj))
            {
                long customer_c_current_addr_sk = e84->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e84->CUSTOMER_ADDRESS_CA_ZIP;
                long v84 = e84->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1* i85 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3.index[2]);
                  const HASH_RES_t h41 = EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey1_idxfn::hash(se102.modify1(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1::IdxNode* n85 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1::IdxNode*>(i85->slice(se102, h41));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e85;
                 
                  if (n85 && (e85 = n85->obj)) {
                    do {                
                      long store_sales_ss_customer_sk = e85->STORE_SALES_SS_CUSTOMER_SK;
                      long v85 = e85->__av;
                      EXT_PRICESTORE1STORE_SALES1_P_3.addOrDelOnZero(se101.modify(store_sales_ss_customer_sk,customer_address_ca_zip),(v84 * v85));
                      n85 = n85->nxt;
                    } while (n85 && (e85 = n85->obj) && h41 == n85->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey1_idxfn::equals(se102, *e85)); 
                  }
                }
              n84 = n84->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i86 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n86; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e86;
        
          for (size_t i = 0; i < i86->size_; i++)
          {
            n86 = i86->buckets_ + i;
            while (n86 && (e86 = n86->obj))
            {
                long customer_c_current_addr_sk = e86->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e86->CUSTOMER_ADDRESS_CA_ZIP;
                long v86 = e86->__av;
                {  // foreach
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_012345* i87 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_012345*>(EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1.index[0]);
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map_012345::IdxNode* n87; 
                  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry* e87;
                
                  for (size_t i = 0; i < i87->size_; i++)
                  {
                    n87 = i87->buckets_ + i;
                    while (n87 && (e87 = n87->obj))
                    {
                        long store_sales_ss_customer_sk = e87->STORE_SALES_SS_CUSTOMER_SK;
                        long item_i_manufact_id = e87->ITEM_I_MANUFACT_ID;
                        STRING_TYPE item_i_manufact = e87->ITEM_I_MANUFACT;
                        STRING_TYPE store_s_zip = e87->STORE_S_ZIP;
                        long brand_id = e87->BRAND_ID;
                        STRING_TYPE brand = e87->BRAND;
                        DOUBLE_TYPE v87 = e87->__av;
                        (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICECUSTOMER1.addOrDelOnZero(se103.modify(store_sales_ss_customer_sk,item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,brand_id,brand),(v86 * v87)) : (void)0);
                      n87 = n87->nxt;
                    }
                  }
                }
              n86 = n86->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i88 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n88; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e88;
        
          for (size_t i = 0; i < i88->size_; i++)
          {
            n88 = i88->buckets_ + i;
            while (n88 && (e88 = n88->obj))
            {
                long customer_c_current_addr_sk = e88->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e88->CUSTOMER_ADDRESS_CA_ZIP;
                long v88 = e88->__av;
                {  // foreach
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_012* i89 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_012*>(EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1.index[0]);
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map_012::IdxNode* n89; 
                  EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry* e89;
                
                  for (size_t i = 0; i < i89->size_; i++)
                  {
                    n89 = i89->buckets_ + i;
                    while (n89 && (e89 = n89->obj))
                    {
                        long store_sales_ss_item_sk = e89->STORE_SALES_SS_ITEM_SK;
                        long store_sales_ss_customer_sk = e89->STORE_SALES_SS_CUSTOMER_SK;
                        STRING_TYPE store_s_zip = e89->STORE_S_ZIP;
                        DOUBLE_TYPE v89 = e89->__av;
                        (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICECUSTOMER1ITEM1.addOrDelOnZero(se104.modify(store_sales_ss_item_sk,store_sales_ss_customer_sk,customer_c_current_addr_sk),(v88 * v89)) : (void)0);
                      n89 = n89->nxt;
                    }
                  }
                }
              n88 = n88->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i90 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n90; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e90;
        
          for (size_t i = 0; i < i90->size_; i++)
          {
            n90 = i90->buckets_ + i;
            while (n90 && (e90 = n90->obj))
            {
                long customer_c_current_addr_sk = e90->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e90->CUSTOMER_ADDRESS_CA_ZIP;
                long v90 = e90->__av;
                {  // foreach
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01* i91 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01*>(EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3.index[0]);
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01::IdxNode* n91; 
                  EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e91;
                
                  for (size_t i = 0; i < i91->size_; i++)
                  {
                    n91 = i91->buckets_ + i;
                    while (n91 && (e91 = n91->obj))
                    {
                        long store_sales_ss_store_sk = e91->STORE_SALES_SS_STORE_SK;
                        STRING_TYPE store_s_zip = e91->STORE_S_ZIP;
                        long v91 = e91->__av;
                        (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICECUSTOMER1STORE_SALES1_P_3.addOrDelOnZero(se105.modify(store_sales_ss_store_sk,customer_c_current_addr_sk),(v90 * v91)) : (void)0);
                      n91 = n91->nxt;
                    }
                  }
                }
              n90 = n90->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i92 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n92; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e92;
        
          for (size_t i = 0; i < i92->size_; i++)
          {
            n92 = i92->buckets_ + i;
            while (n92 && (e92 = n92->obj))
            {
                long customer_c_current_addr_sk = e92->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e92->CUSTOMER_ADDRESS_CA_ZIP;
                long v92 = e92->__av;
                { //slice 
                  const HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_1* i93 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_1*>(EXT_PRICECUSTOMER_ADDRESS1ITEM1.index[2]);
                  const HASH_RES_t h42 = EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn::hash(se107.modify1(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_1::IdxNode* n93 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1ITEM1_map_1::IdxNode*>(i93->slice(se107, h42));
                  EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry* e93;
                 
                  if (n93 && (e93 = n93->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e93->STORE_SALES_SS_ITEM_SK;
                      STRING_TYPE store_s_zip = e93->STORE_S_ZIP;
                      DOUBLE_TYPE v93 = e93->__av;
                      (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICEITEM1.addOrDelOnZero(se106.modify(store_sales_ss_item_sk),(v92 * v93)) : (void)0);
                      n93 = n93->nxt;
                    } while (n93 && (e93 = n93->obj) && h42 == n93->hash &&  EXT_PRICECUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn::equals(se107, *e93)); 
                  }
                }
              n92 = n92->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01* i94 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01*>(EXT_PRICECUSTOMER_ADDRESS1_DELTA.index[0]);
          HashIndex_EXT_PRICECUSTOMER_ADDRESS1_DELTA_map_01::IdxNode* n94; 
          EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry* e94;
        
          for (size_t i = 0; i < i94->size_; i++)
          {
            n94 = i94->buckets_ + i;
            while (n94 && (e94 = n94->obj))
            {
                long customer_c_current_addr_sk = e94->CUSTOMER_C_CURRENT_ADDR_SK;
                STRING_TYPE customer_address_ca_zip = e94->CUSTOMER_ADDRESS_CA_ZIP;
                long v94 = e94->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1* i95 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3.index[2]);
                  const HASH_RES_t h43 = EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey1_idxfn::hash(se109.modify1(customer_c_current_addr_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1::IdxNode* n95 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map_1::IdxNode*>(i95->slice(se109, h43));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e95;
                 
                  if (n95 && (e95 = n95->obj)) {
                    do {                
                      long store_sales_ss_customer_sk = e95->STORE_SALES_SS_CUSTOMER_SK;
                      long v95 = e95->__av;
                      {  // foreach
                        const HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01* i96 = static_cast<HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01*>(EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3.index[0]);
                        HashIndex_EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map_01::IdxNode* n96; 
                        EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry* e96;
                      
                        for (size_t i = 0; i < i96->size_; i++)
                        {
                          n96 = i96->buckets_ + i;
                          while (n96 && (e96 = n96->obj))
                          {
                              long store_sales_ss_store_sk = e96->STORE_SALES_SS_STORE_SK;
                              STRING_TYPE store_s_zip = e96->STORE_S_ZIP;
                              long v96 = e96->__av;
                              (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICESTORE_SALES1_P_3.addOrDelOnZero(se108.modify(store_sales_ss_store_sk,store_sales_ss_customer_sk),(v94 * (v95 * v96))) : (void)0);
                            n96 = n96->nxt;
                          }
                        }
                      }
                      n95 = n95->nxt;
                    } while (n95 && (e95 = n95->obj) && h43 == n95->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_mapkey1_idxfn::equals(se109, *e95)); 
                  }
                }
              n94 = n94->nxt;
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

        EXT_PRICESTORE1_DELTA.clear();
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
                // STRING_TYPE store_s_county = DELTA_STORE.s_county[i];
                // STRING_TYPE store_s_state = DELTA_STORE.s_state[i];
                STRING_TYPE store_s_zip = DELTA_STORE.s_zip[i];
                // STRING_TYPE store_s_country = DELTA_STORE.s_country[i];
                // DOUBLE_TYPE store_s_gmt_offset = DELTA_STORE.s_gmt_offset[i];
                // DOUBLE_TYPE store_s_tax_precentage = DELTA_STORE.s_tax_precentage[i];
                long v97 = 1L;
                EXT_PRICESTORE1_DELTA.addOrDelOnZero(se110.modify(store_sales_ss_store_sk,store_s_zip),v97);

          }
        }

        {  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i98 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n98; 
          EXT_PRICESTORE1_DELTA_entry* e98;
        
          for (size_t i = 0; i < i98->size_; i++)
          {
            n98 = i98->buckets_ + i;
            while (n98 && (e98 = n98->obj))
            {
                long store_sales_ss_store_sk = e98->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e98->STORE_S_ZIP;
                long v98 = e98->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1_map_0* i99 = static_cast<HashIndex_EXT_PRICESTORE1_map_0*>(EXT_PRICESTORE1.index[1]);
                  const HASH_RES_t h44 = EXT_PRICESTORE1_mapkey0_idxfn::hash(se112.modify0(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1_map_0::IdxNode* n99 = static_cast<HashIndex_EXT_PRICESTORE1_map_0::IdxNode*>(i99->slice(se112, h44));
                  EXT_PRICESTORE1_entry* e99;
                 
                  if (n99 && (e99 = n99->obj)) {
                    do {                
                      long item_i_manufact_id = e99->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e99->ITEM_I_MANUFACT;
                      STRING_TYPE customer_address_ca_zip = e99->CUSTOMER_ADDRESS_CA_ZIP;
                      long brand_id = e99->BRAND_ID;
                      STRING_TYPE brand = e99->BRAND;
                      DOUBLE_TYPE v99 = e99->__av;
                      (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICE.addOrDelOnZero(se111.modify(brand_id,brand,item_i_manufact_id,item_i_manufact),(v98 * v99)) : (void)0);
                      n99 = n99->nxt;
                    } while (n99 && (e99 = n99->obj) && h44 == n99->hash &&  EXT_PRICESTORE1_mapkey0_idxfn::equals(se112, *e99)); 
                  }
                }
              n98 = n98->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i100 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n100; 
          EXT_PRICESTORE1_DELTA_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long store_sales_ss_store_sk = e100->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e100->STORE_S_ZIP;
                long v100 = e100->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_0* i101 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_0*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1.index[2]);
                  const HASH_RES_t h45 = EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey0_idxfn::hash(se114.modify0(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_0::IdxNode* n101 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1_map_0::IdxNode*>(i101->slice(se114, h45));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry* e101;
                 
                  if (n101 && (e101 = n101->obj)) {
                    do {                
                      long item_i_manufact_id = e101->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e101->ITEM_I_MANUFACT;
                      long customer_c_current_addr_sk = e101->CUSTOMER_C_CURRENT_ADDR_SK;
                      long brand_id = e101->BRAND_ID;
                      STRING_TYPE brand = e101->BRAND;
                      DOUBLE_TYPE v101 = e101->__av;
                      EXT_PRICECUSTOMER_ADDRESS1.addOrDelOnZero(se113.modify(item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,store_s_zip,brand_id,brand),(v100 * v101));
                      n101 = n101->nxt;
                    } while (n101 && (e101 = n101->obj) && h45 == n101->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1_mapkey0_idxfn::equals(se114, *e101)); 
                  }
                }
              n100 = n100->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i102 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n102; 
          EXT_PRICESTORE1_DELTA_entry* e102;
        
          for (size_t i = 0; i < i102->size_; i++)
          {
            n102 = i102->buckets_ + i;
            while (n102 && (e102 = n102->obj))
            {
                long store_sales_ss_store_sk = e102->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e102->STORE_S_ZIP;
                long v102 = e102->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1* i103 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1*>(EXT_PRICESTORE1CUSTOMER1_P_1.index[2]);
                  const HASH_RES_t h46 = EXT_PRICESTORE1CUSTOMER1_P_1_mapkey1_idxfn::hash(se116.modify1(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1::IdxNode* n103 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1::IdxNode*>(i103->slice(se116, h46));
                  EXT_PRICESTORE1CUSTOMER1_P_1_entry* e103;
                 
                  if (n103 && (e103 = n103->obj)) {
                    do {                
                      long store_sales_ss_customer_sk = e103->STORE_SALES_SS_CUSTOMER_SK;
                      long item_i_manufact_id = e103->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e103->ITEM_I_MANUFACT;
                      long brand_id = e103->BRAND_ID;
                      STRING_TYPE brand = e103->BRAND;
                      DOUBLE_TYPE v103 = e103->__av;
                      EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1.addOrDelOnZero(se115.modify(store_sales_ss_customer_sk,item_i_manufact_id,item_i_manufact,store_s_zip,brand_id,brand),(v102 * v103));
                      n103 = n103->nxt;
                    } while (n103 && (e103 = n103->obj) && h46 == n103->hash &&  EXT_PRICESTORE1CUSTOMER1_P_1_mapkey1_idxfn::equals(se116, *e103)); 
                  }
                }
              n102 = n102->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i104 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n104; 
          EXT_PRICESTORE1_DELTA_entry* e104;
        
          for (size_t i = 0; i < i104->size_; i++)
          {
            n104 = i104->buckets_ + i;
            while (n104 && (e104 = n104->obj))
            {
                long store_sales_ss_store_sk = e104->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e104->STORE_S_ZIP;
                long v104 = e104->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2* i105 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1.index[3]);
                  const HASH_RES_t h47 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey2_idxfn::hash(se118.modify2(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2::IdxNode* n105 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2::IdxNode*>(i105->slice(se118, h47));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry* e105;
                 
                  if (n105 && (e105 = n105->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e105->STORE_SALES_SS_ITEM_SK;
                      long store_sales_ss_customer_sk = e105->STORE_SALES_SS_CUSTOMER_SK;
                      DOUBLE_TYPE v105 = e105->__av;
                      EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1.addOrDelOnZero(se117.modify(store_sales_ss_item_sk,store_sales_ss_customer_sk,store_s_zip),(v104 * v105));
                      n105 = n105->nxt;
                    } while (n105 && (e105 = n105->obj) && h47 == n105->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey2_idxfn::equals(se118, *e105)); 
                  }
                }
              n104 = n104->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i106 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n106; 
          EXT_PRICESTORE1_DELTA_entry* e106;
        
          for (size_t i = 0; i < i106->size_; i++)
          {
            n106 = i106->buckets_ + i;
            while (n106 && (e106 = n106->obj))
            {
                long store_sales_ss_store_sk = e106->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e106->STORE_S_ZIP;
                long v106 = e106->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_1* i107 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_1*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1.index[3]);
                  const HASH_RES_t h48 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn::hash(se120.modify1(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_1::IdxNode* n107 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map_1::IdxNode*>(i107->slice(se120, h48));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry* e107;
                 
                  if (n107 && (e107 = n107->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e107->STORE_SALES_SS_ITEM_SK;
                      long customer_c_current_addr_sk = e107->CUSTOMER_C_CURRENT_ADDR_SK;
                      DOUBLE_TYPE v107 = e107->__av;
                      EXT_PRICECUSTOMER_ADDRESS1ITEM1.addOrDelOnZero(se119.modify(store_sales_ss_item_sk,customer_c_current_addr_sk,store_s_zip),(v106 * v107));
                      n107 = n107->nxt;
                    } while (n107 && (e107 = n107->obj) && h48 == n107->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_mapkey1_idxfn::equals(se120, *e107)); 
                  }
                }
              n106 = n106->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i108 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n108; 
          EXT_PRICESTORE1_DELTA_entry* e108;
        
          for (size_t i = 0; i < i108->size_; i++)
          {
            n108 = i108->buckets_ + i;
            while (n108 && (e108 = n108->obj))
            {
                long store_sales_ss_store_sk = e108->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e108->STORE_S_ZIP;
                long v108 = e108->__av;
                EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3.addOrDelOnZero(se121.modify(store_sales_ss_store_sk,store_s_zip),v108);
              n108 = n108->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i109 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n109; 
          EXT_PRICESTORE1_DELTA_entry* e109;
        
          for (size_t i = 0; i < i109->size_; i++)
          {
            n109 = i109->buckets_ + i;
            while (n109 && (e109 = n109->obj))
            {
                long store_sales_ss_store_sk = e109->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e109->STORE_S_ZIP;
                long v109 = e109->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1* i110 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1*>(EXT_PRICESTORE1CUSTOMER1_P_1.index[2]);
                  const HASH_RES_t h49 = EXT_PRICESTORE1CUSTOMER1_P_1_mapkey1_idxfn::hash(se123.modify1(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1::IdxNode* n110 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_1_map_1::IdxNode*>(i110->slice(se123, h49));
                  EXT_PRICESTORE1CUSTOMER1_P_1_entry* e110;
                 
                  if (n110 && (e110 = n110->obj)) {
                    do {                
                      long store_sales_ss_customer_sk = e110->STORE_SALES_SS_CUSTOMER_SK;
                      long item_i_manufact_id = e110->ITEM_I_MANUFACT_ID;
                      STRING_TYPE item_i_manufact = e110->ITEM_I_MANUFACT;
                      long brand_id = e110->BRAND_ID;
                      STRING_TYPE brand = e110->BRAND;
                      DOUBLE_TYPE v110 = e110->__av;
                      {  // foreach
                        const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01* i111 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01*>(EXT_PRICESTORE1CUSTOMER1_P_2.index[0]);
                        HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01::IdxNode* n111; 
                        EXT_PRICESTORE1CUSTOMER1_P_2_entry* e111;
                      
                        for (size_t i = 0; i < i111->size_; i++)
                        {
                          n111 = i111->buckets_ + i;
                          while (n111 && (e111 = n111->obj))
                          {
                              long customer_c_current_addr_sk = e111->CUSTOMER_C_CURRENT_ADDR_SK;
                              STRING_TYPE customer_address_ca_zip = e111->CUSTOMER_ADDRESS_CA_ZIP;
                              long v111 = e111->__av;
                              (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICECUSTOMER1.addOrDelOnZero(se122.modify(store_sales_ss_customer_sk,item_i_manufact_id,item_i_manufact,customer_c_current_addr_sk,brand_id,brand),(v109 * (v110 * v111))) : (void)0);
                            n111 = n111->nxt;
                          }
                        }
                      }
                      n110 = n110->nxt;
                    } while (n110 && (e110 = n110->obj) && h49 == n110->hash &&  EXT_PRICESTORE1CUSTOMER1_P_1_mapkey1_idxfn::equals(se123, *e110)); 
                  }
                }
              n109 = n109->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i112 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n112; 
          EXT_PRICESTORE1_DELTA_entry* e112;
        
          for (size_t i = 0; i < i112->size_; i++)
          {
            n112 = i112->buckets_ + i;
            while (n112 && (e112 = n112->obj))
            {
                long store_sales_ss_store_sk = e112->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e112->STORE_S_ZIP;
                long v112 = e112->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2* i113 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2*>(EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1.index[3]);
                  const HASH_RES_t h50 = EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey2_idxfn::hash(se125.modify2(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2::IdxNode* n113 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map_2::IdxNode*>(i113->slice(se125, h50));
                  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry* e113;
                 
                  if (n113 && (e113 = n113->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e113->STORE_SALES_SS_ITEM_SK;
                      long store_sales_ss_customer_sk = e113->STORE_SALES_SS_CUSTOMER_SK;
                      DOUBLE_TYPE v113 = e113->__av;
                      {  // foreach
                        const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01* i114 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01*>(EXT_PRICESTORE1CUSTOMER1_P_2.index[0]);
                        HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01::IdxNode* n114; 
                        EXT_PRICESTORE1CUSTOMER1_P_2_entry* e114;
                      
                        for (size_t i = 0; i < i114->size_; i++)
                        {
                          n114 = i114->buckets_ + i;
                          while (n114 && (e114 = n114->obj))
                          {
                              long customer_c_current_addr_sk = e114->CUSTOMER_C_CURRENT_ADDR_SK;
                              STRING_TYPE customer_address_ca_zip = e114->CUSTOMER_ADDRESS_CA_ZIP;
                              long v114 = e114->__av;
                              (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICECUSTOMER1ITEM1.addOrDelOnZero(se124.modify(store_sales_ss_item_sk,store_sales_ss_customer_sk,customer_c_current_addr_sk),(v112 * (v113 * v114))) : (void)0);
                            n114 = n114->nxt;
                          }
                        }
                      }
                      n113 = n113->nxt;
                    } while (n113 && (e113 = n113->obj) && h50 == n113->hash &&  EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_mapkey2_idxfn::equals(se125, *e113)); 
                  }
                }
              n112 = n112->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i115 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n115; 
          EXT_PRICESTORE1_DELTA_entry* e115;
        
          for (size_t i = 0; i < i115->size_; i++)
          {
            n115 = i115->buckets_ + i;
            while (n115 && (e115 = n115->obj))
            {
                long store_sales_ss_store_sk = e115->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e115->STORE_S_ZIP;
                long v115 = e115->__av;
                {  // foreach
                  const HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01* i116 = static_cast<HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01*>(EXT_PRICESTORE1CUSTOMER1_P_2.index[0]);
                  HashIndex_EXT_PRICESTORE1CUSTOMER1_P_2_map_01::IdxNode* n116; 
                  EXT_PRICESTORE1CUSTOMER1_P_2_entry* e116;
                
                  for (size_t i = 0; i < i116->size_; i++)
                  {
                    n116 = i116->buckets_ + i;
                    while (n116 && (e116 = n116->obj))
                    {
                        long customer_c_current_addr_sk = e116->CUSTOMER_C_CURRENT_ADDR_SK;
                        STRING_TYPE customer_address_ca_zip = e116->CUSTOMER_ADDRESS_CA_ZIP;
                        long v116 = e116->__av;
                        (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICECUSTOMER1STORE_SALES1_P_3.addOrDelOnZero(se126.modify(store_sales_ss_store_sk,customer_c_current_addr_sk),(v115 * v116)) : (void)0);
                      n116 = n116->nxt;
                    }
                  }
                }
              n115 = n115->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i117 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n117; 
          EXT_PRICESTORE1_DELTA_entry* e117;
        
          for (size_t i = 0; i < i117->size_; i++)
          {
            n117 = i117->buckets_ + i;
            while (n117 && (e117 = n117->obj))
            {
                long store_sales_ss_store_sk = e117->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e117->STORE_S_ZIP;
                long v117 = e117->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE1ITEM1_map_1* i118 = static_cast<HashIndex_EXT_PRICESTORE1ITEM1_map_1*>(EXT_PRICESTORE1ITEM1.index[2]);
                  const HASH_RES_t h51 = EXT_PRICESTORE1ITEM1_mapkey1_idxfn::hash(se128.modify1(store_sales_ss_store_sk));
                  HashIndex_EXT_PRICESTORE1ITEM1_map_1::IdxNode* n118 = static_cast<HashIndex_EXT_PRICESTORE1ITEM1_map_1::IdxNode*>(i118->slice(se128, h51));
                  EXT_PRICESTORE1ITEM1_entry* e118;
                 
                  if (n118 && (e118 = n118->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e118->STORE_SALES_SS_ITEM_SK;
                      STRING_TYPE customer_address_ca_zip = e118->CUSTOMER_ADDRESS_CA_ZIP;
                      DOUBLE_TYPE v118 = e118->__av;
                      (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICEITEM1.addOrDelOnZero(se127.modify(store_sales_ss_item_sk),(v117 * v118)) : (void)0);
                      n118 = n118->nxt;
                    } while (n118 && (e118 = n118->obj) && h51 == n118->hash &&  EXT_PRICESTORE1ITEM1_mapkey1_idxfn::equals(se128, *e118)); 
                  }
                }
              n117 = n117->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE1_DELTA_map_01* i119 = static_cast<HashIndex_EXT_PRICESTORE1_DELTA_map_01*>(EXT_PRICESTORE1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE1_DELTA_map_01::IdxNode* n119; 
          EXT_PRICESTORE1_DELTA_entry* e119;
        
          for (size_t i = 0; i < i119->size_; i++)
          {
            n119 = i119->buckets_ + i;
            while (n119 && (e119 = n119->obj))
            {
                long store_sales_ss_store_sk = e119->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_zip = e119->STORE_S_ZIP;
                long v119 = e119->__av;
                {  // foreach
                  const HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_01* i120 = static_cast<HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_01*>(EXT_PRICESTORE1STORE_SALES1_P_3.index[0]);
                  HashIndex_EXT_PRICESTORE1STORE_SALES1_P_3_map_01::IdxNode* n120; 
                  EXT_PRICESTORE1STORE_SALES1_P_3_entry* e120;
                
                  for (size_t i = 0; i < i120->size_; i++)
                  {
                    n120 = i120->buckets_ + i;
                    while (n120 && (e120 = n120->obj))
                    {
                        long store_sales_ss_customer_sk = e120->STORE_SALES_SS_CUSTOMER_SK;
                        STRING_TYPE customer_address_ca_zip = e120->CUSTOMER_ADDRESS_CA_ZIP;
                        long v120 = e120->__av;
                        (/*if */(Usubstring(customer_address_ca_zip, 1L, 5L) != Usubstring(store_s_zip, 1L, 5L)) ? EXT_PRICESTORE_SALES1_P_3.addOrDelOnZero(se129.modify(store_sales_ss_store_sk,store_sales_ss_customer_sk),(v119 * v120)) : (void)0);
                      n120 = n120->nxt;
                    }
                  }
                }
              n119 = n119->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        EXT_PRICESTORE_SALES1_P_2.clear();
        long l1 = 1999L;
        long l2 = 11L;
        { //slice 
          const HashIndex_DATE_DIM_map_68* i121 = static_cast<HashIndex_DATE_DIM_map_68*>(DATE_DIM.index[1]);
          const HASH_RES_t h52 = DATE_DIM_mapkey68_idxfn::hash(se131.modify68(l1, l2));
          HashIndex_DATE_DIM_map_68::IdxNode* n121 = static_cast<HashIndex_DATE_DIM_map_68::IdxNode*>(i121->slice(se131, h52));
          DATE_DIM_entry* e121;
         
          if (n121 && (e121 = n121->obj)) {
            do {                
              long date_dim_d_date_sk = e121->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e121->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e121->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e121->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e121->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e121->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e121->DATE_DIM_D_DOW;
              long date_dim_d_dom = e121->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e121->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e121->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e121->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e121->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_day_name = e121->DATE_DIM_D_DAY_NAME;
              STRING_TYPE date_dim_d_quarter_name = e121->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e121->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e121->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e121->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e121->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e121->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e121->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e121->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e121->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e121->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e121->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e121->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e121->DATE_DIM_D_CURRENT_YEAR;
              long v121 = e121->__av;
              EXT_PRICESTORE_SALES1_P_2.addOrDelOnZero(se130.modify(date_dim_d_date_sk),v121);
              n121 = n121->nxt;
            } while (n121 && (e121 = n121->obj) && h52 == n121->hash &&  DATE_DIM_mapkey68_idxfn::equals(se131, *e121)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    EXT_PRICESTORE_SALES1_DELTA_entry se1;
    EXT_PRICE_entry se2;
    EXT_PRICESTORE_SALES1_P_2_entry se3;
    EXT_PRICESTORE_SALES1_P_3_entry se4;
    EXT_PRICESTORE_SALES1_P_1_entry se5;
    EXT_PRICESTORE1_entry se6;
    EXT_PRICESTORE_SALES1_P_2_entry se7;
    EXT_PRICESTORE1STORE_SALES1_P_3_entry se8;
    EXT_PRICESTORE1STORE_SALES1_P_2_entry se9;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry se10;
    EXT_PRICESTORE_SALES1_P_2_entry se11;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se12;
    EXT_PRICESTORE1STORE_SALES1_P_2_entry se13;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry se14;
    EXT_PRICESTORE_SALES1_P_2_entry se15;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se16;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry se17;
    EXT_PRICESTORE_SALES1_P_2_entry se18;
    EXT_PRICESTORE1CUSTOMER1_P_1_entry se19;
    EXT_PRICESTORE_SALES1_P_2_entry se20;
    EXT_PRICESTORE1STORE_SALES1_P_2_entry se21;
    EXT_PRICESTORE1ITEM1_entry se22;
    EXT_PRICESTORE_SALES1_P_2_entry se23;
    EXT_PRICESTORE1STORE_SALES1_P_3_entry se24;
    EXT_PRICECUSTOMER_ADDRESS1_entry se25;
    EXT_PRICESTORE_SALES1_P_2_entry se26;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se27;
    EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se28;
    EXT_PRICESTORE1STORE_SALES1_P_2_entry se29;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry se30;
    EXT_PRICESTORE_SALES1_P_2_entry se31;
    EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se32;
    EXT_PRICESTORE1STORE_SALES1_P_2_entry se33;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry se34;
    EXT_PRICESTORE_SALES1_P_2_entry se35;
    EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se36;
    EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry se37;
    EXT_PRICESTORE_SALES1_P_2_entry se38;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se39;
    EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se40;
    EXT_PRICECUSTOMER1_entry se41;
    EXT_PRICESTORE_SALES1_P_2_entry se42;
    EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry se43;
    EXT_PRICESTORE1STORE_SALES1_P_2_entry se44;
    EXT_PRICECUSTOMER1ITEM1_entry se45;
    EXT_PRICESTORE_SALES1_P_2_entry se46;
    EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry se47;
    EXT_PRICEITEM1_entry se48;
    EXT_PRICESTORE_SALES1_P_2_entry se49;
    EXT_PRICESTORE_SALES1_P_3_entry se50;
    EXT_PRICEITEM1_DELTA_entry se51;
    EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_entry se52;
    EXT_PRICE_entry se53;
    EXT_PRICEITEM1_entry se54;
    EXT_PRICESTORE1_entry se55;
    EXT_PRICESTORE1ITEM1_entry se56;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry se57;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry se58;
    EXT_PRICESTORE1CUSTOMER1_P_1_entry se59;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry se60;
    EXT_PRICESTORE1STORE_SALES1_P_2_entry se61;
    EXT_PRICECUSTOMER_ADDRESS1_entry se62;
    EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry se63;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry se64;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry se65;
    EXT_PRICECUSTOMER1_entry se66;
    EXT_PRICECUSTOMER1ITEM1_entry se67;
    EXT_PRICESTORE_SALES1_P_1_entry se68;
    EXT_PRICECUSTOMER1_DELTA_entry se69;
    EXT_PRICE_entry se70;
    EXT_PRICECUSTOMER1_entry se71;
    EXT_PRICESTORE1_entry se72;
    EXT_PRICESTORE1CUSTOMER1_P_2_entry se73;
    EXT_PRICESTORE1CUSTOMER1_P_1_entry se74;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry se75;
    EXT_PRICESTORE1CUSTOMER1_P_1_entry se76;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry se77;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry se78;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se79;
    EXT_PRICESTORE1ITEM1_entry se80;
    EXT_PRICESTORE1CUSTOMER1_P_2_entry se81;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry se82;
    EXT_PRICESTORE1STORE_SALES1_P_3_entry se83;
    EXT_PRICESTORE1CUSTOMER1_P_2_entry se84;
    EXT_PRICECUSTOMER_ADDRESS1_entry se85;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry se86;
    EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry se87;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry se88;
    EXT_PRICEITEM1_entry se89;
    EXT_PRICECUSTOMER1ITEM1_entry se90;
    EXT_PRICESTORE_SALES1_P_3_entry se91;
    EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry se92;
    EXT_PRICECUSTOMER_ADDRESS1_DELTA_entry se93;
    EXT_PRICE_entry se94;
    EXT_PRICECUSTOMER_ADDRESS1_entry se95;
    EXT_PRICESTORE1_entry se96;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry se97;
    EXT_PRICESTORE1CUSTOMER1_P_2_entry se98;
    EXT_PRICESTORE1ITEM1_entry se99;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry se100;
    EXT_PRICESTORE1STORE_SALES1_P_3_entry se101;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se102;
    EXT_PRICECUSTOMER1_entry se103;
    EXT_PRICECUSTOMER1ITEM1_entry se104;
    EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry se105;
    EXT_PRICEITEM1_entry se106;
    EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry se107;
    EXT_PRICESTORE_SALES1_P_3_entry se108;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se109;
    EXT_PRICESTORE1_DELTA_entry se110;
    EXT_PRICE_entry se111;
    EXT_PRICESTORE1_entry se112;
    EXT_PRICECUSTOMER_ADDRESS1_entry se113;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1_entry se114;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_entry se115;
    EXT_PRICESTORE1CUSTOMER1_P_1_entry se116;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_entry se117;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry se118;
    EXT_PRICECUSTOMER_ADDRESS1ITEM1_entry se119;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_entry se120;
    EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_entry se121;
    EXT_PRICECUSTOMER1_entry se122;
    EXT_PRICESTORE1CUSTOMER1_P_1_entry se123;
    EXT_PRICECUSTOMER1ITEM1_entry se124;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_entry se125;
    EXT_PRICECUSTOMER1STORE_SALES1_P_3_entry se126;
    EXT_PRICEITEM1_entry se127;
    EXT_PRICESTORE1ITEM1_entry se128;
    EXT_PRICESTORE_SALES1_P_3_entry se129;
    EXT_PRICESTORE_SALES1_P_2_entry se130;
    DATE_DIM_entry se131;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    EXT_PRICESTORE1_DELTA_map EXT_PRICESTORE1_DELTA;
    EXT_PRICESTORE1_map EXT_PRICESTORE1;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1_map EXT_PRICESTORE1CUSTOMER_ADDRESS1;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1_map EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1_map EXT_PRICESTORE1CUSTOMER_ADDRESS1ITEM1CUSTOMER1;
    EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3_map EXT_PRICESTORE1CUSTOMER_ADDRESS1STORE_SALES1_P_3;
    EXT_PRICESTORE1CUSTOMER1_P_1_map EXT_PRICESTORE1CUSTOMER1_P_1;
    EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA_map EXT_PRICESTORE1CUSTOMER1_P_1ITEM1_DELTA;
    EXT_PRICESTORE1CUSTOMER1_P_2_map EXT_PRICESTORE1CUSTOMER1_P_2;
    EXT_PRICESTORE1ITEM1_map EXT_PRICESTORE1ITEM1;
    EXT_PRICESTORE1STORE_SALES1_P_2_map EXT_PRICESTORE1STORE_SALES1_P_2;
    EXT_PRICESTORE1STORE_SALES1_P_3_map EXT_PRICESTORE1STORE_SALES1_P_3;
    EXT_PRICECUSTOMER_ADDRESS1_DELTA_map EXT_PRICECUSTOMER_ADDRESS1_DELTA;
    EXT_PRICECUSTOMER_ADDRESS1_map EXT_PRICECUSTOMER_ADDRESS1;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1_map EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1;
    EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1_map EXT_PRICECUSTOMER_ADDRESS1CUSTOMER1ITEM1;
    EXT_PRICECUSTOMER_ADDRESS1ITEM1_map EXT_PRICECUSTOMER_ADDRESS1ITEM1;
    EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3_map EXT_PRICECUSTOMER_ADDRESS1STORE_SALES1_P_3;
    EXT_PRICECUSTOMER1_DELTA_map EXT_PRICECUSTOMER1_DELTA;
    EXT_PRICECUSTOMER1_map EXT_PRICECUSTOMER1;
    EXT_PRICECUSTOMER1ITEM1_map EXT_PRICECUSTOMER1ITEM1;
    EXT_PRICECUSTOMER1STORE_SALES1_P_3_map EXT_PRICECUSTOMER1STORE_SALES1_P_3;
    EXT_PRICEITEM1_DELTA_map EXT_PRICEITEM1_DELTA;
    EXT_PRICEITEM1_map EXT_PRICEITEM1;
    EXT_PRICESTORE_SALES1_DELTA_map EXT_PRICESTORE_SALES1_DELTA;
    EXT_PRICESTORE_SALES1_P_1_map EXT_PRICESTORE_SALES1_P_1;
    EXT_PRICESTORE_SALES1_P_2_map EXT_PRICESTORE_SALES1_P_2;
    EXT_PRICESTORE_SALES1_P_3_map EXT_PRICESTORE_SALES1_P_3;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_ITEM_map DELTA_ITEM;
    DELTA_CUSTOMER_map DELTA_CUSTOMER;
    DELTA_CUSTOMER_ADDRESS_map DELTA_CUSTOMER_ADDRESS;
    DELTA_STORE_map DELTA_STORE;
    
    
  
  };

}
