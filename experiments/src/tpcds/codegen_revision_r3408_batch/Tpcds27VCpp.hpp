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
    FORCE_INLINE DATE_DIM_entry& modify6(const long c6) { DATE_DIM_D_YEAR = c6;  return *this; }
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
  
  struct DATE_DIM_mapkey6_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey6_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey6_idxfn,false> HashIndex_DATE_DIM_map_6;
  
  struct CUSTOMER_DEMOGRAPHICS_entry {
    long CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_GENDER; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS; long CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING; long CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT; long CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT; long CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT; long __av; 
    explicit CUSTOMER_DEMOGRAPHICS_entry() { /*CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK = 0L; CUSTOMER_DEMOGRAPHICS_CD_GENDER = ""; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = ""; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = ""; CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE = 0L; CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING = ""; CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT = 0L; CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT = 0L; CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT = 0L; __av = 0L; */ }
    explicit CUSTOMER_DEMOGRAPHICS_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const long c6, const long c7, const long c8, const long c9) { CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK = c0; CUSTOMER_DEMOGRAPHICS_CD_GENDER = c1; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = c2; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = c3; CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE = c4; CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING = c5; CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT = c6; CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT = c7; CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT = c8; __av = c9; }
    CUSTOMER_DEMOGRAPHICS_entry(const CUSTOMER_DEMOGRAPHICS_entry& other) : CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK( other.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK ), CUSTOMER_DEMOGRAPHICS_CD_GENDER( other.CUSTOMER_DEMOGRAPHICS_CD_GENDER ), CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS( other.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS ), CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS( other.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS ), CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE( other.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE ), CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING( other.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING ), CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT( other.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT ), CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT( other.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT ), CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT( other.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT ), __av( other.__av ) {}
    FORCE_INLINE CUSTOMER_DEMOGRAPHICS_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const long c6, const long c7, const long c8) { CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK = c0; CUSTOMER_DEMOGRAPHICS_CD_GENDER = c1; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = c2; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = c3; CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE = c4; CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING = c5; CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT = c6; CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT = c7; CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT = c8;  return *this; }
    FORCE_INLINE CUSTOMER_DEMOGRAPHICS_entry& modify123(const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { CUSTOMER_DEMOGRAPHICS_CD_GENDER = c1; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = c2; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_GENDER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTOMER_DEMOGRAPHICS_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOMER_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_GENDER);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTOMER_DEMOGRAPHICS_entry& x, const CUSTOMER_DEMOGRAPHICS_entry& y) {
      return x.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK == y.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK && x.CUSTOMER_DEMOGRAPHICS_CD_GENDER == y.CUSTOMER_DEMOGRAPHICS_CD_GENDER && x.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS && x.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS && x.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE == y.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE && x.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING == y.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING && x.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT == y.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT && x.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT == y.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT && x.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT == y.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT;
    }
  };
  
  struct CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOMER_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_GENDER);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTOMER_DEMOGRAPHICS_entry& x, const CUSTOMER_DEMOGRAPHICS_entry& y) {
      return x.CUSTOMER_DEMOGRAPHICS_CD_GENDER == y.CUSTOMER_DEMOGRAPHICS_CD_GENDER && x.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS && x.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS;
    }
  };
  
  typedef MultiHashMap<CUSTOMER_DEMOGRAPHICS_entry,long,
    HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey012345678_idxfn,true>,
    HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn,false>
  > CUSTOMER_DEMOGRAPHICS_map;
  typedef HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey012345678_idxfn,true> HashIndex_CUSTOMER_DEMOGRAPHICS_map_012345678;
  typedef HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn,false> HashIndex_CUSTOMER_DEMOGRAPHICS_map_123;
  
  struct AGG1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG1_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1_entry(const AGG1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1_entry& x, const AGG1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1_entry,DOUBLE_TYPE,
    HashIndex<AGG1_entry,DOUBLE_TYPE,AGG1_mapkey01_idxfn,true>
  > AGG1_map;
  typedef HashIndex<AGG1_entry,DOUBLE_TYPE,AGG1_mapkey01_idxfn,true> HashIndex_AGG1_map_01;
  
  struct AGG1ITEM1_DOMAIN1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1ITEM1_DOMAIN1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1ITEM1_DOMAIN1_entry(const STRING_TYPE& c0, const long c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG1ITEM1_DOMAIN1_entry(const AGG1ITEM1_DOMAIN1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_DOMAIN1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_DOMAIN1_entry& x, const AGG1ITEM1_DOMAIN1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_DOMAIN1_entry,long,
    HashIndex<AGG1ITEM1_DOMAIN1_entry,long,AGG1ITEM1_DOMAIN1_mapkey0_idxfn,true>
  > AGG1ITEM1_DOMAIN1_map;
  typedef HashIndex<AGG1ITEM1_DOMAIN1_entry,long,AGG1ITEM1_DOMAIN1_mapkey0_idxfn,true> HashIndex_AGG1ITEM1_DOMAIN1_map_0;
  
  struct AGG1ITEM1_L1_2_DELTA_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1ITEM1_L1_2_DELTA_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1ITEM1_L1_2_DELTA_entry(const AGG1ITEM1_L1_2_DELTA_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2_DELTA_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2_DELTA_entry& x, const AGG1ITEM1_L1_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2_DELTA_entry& x, const AGG1ITEM1_L1_2_DELTA_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2_DELTA_entry,long,
    HashIndex<AGG1ITEM1_L1_2_DELTA_entry,long,AGG1ITEM1_L1_2_DELTA_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_L1_2_DELTA_entry,long,AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn,false>
  > AGG1ITEM1_L1_2_DELTA_map;
  typedef HashIndex<AGG1ITEM1_L1_2_DELTA_entry,long,AGG1ITEM1_L1_2_DELTA_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_L1_2_DELTA_map_01;
  typedef HashIndex<AGG1ITEM1_L1_2_DELTA_entry,long,AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn,false> HashIndex_AGG1ITEM1_L1_2_DELTA_map_1;
  
  struct AGG1ITEM1_L1_2_entry {
    STRING_TYPE STORE_S_STATE; long STORE_SALES_SS_ITEM_SK; long __av; 
    explicit AGG1ITEM1_L1_2_entry() { /*STORE_S_STATE = ""; STORE_SALES_SS_ITEM_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2_entry(const STRING_TYPE& c0, const long c1, const long c2) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1; __av = c2; }
    AGG1ITEM1_L1_2_entry(const AGG1ITEM1_L1_2_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2_entry& modify(const STRING_TYPE& c0, const long c1) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2_entry& modify1(const long c1) { STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2_entry& x, const AGG1ITEM1_L1_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG1ITEM1_L1_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2_entry& x, const AGG1ITEM1_L1_2_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2_entry,long,
    HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey1_idxfn,false>
  > AGG1ITEM1_L1_2_map;
  typedef HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_L1_2_map_01;
  typedef HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey1_idxfn,false> HashIndex_AGG1ITEM1_L1_2_map_1;
  
  struct AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_STORE_SK; long __av; 
    explicit AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3; __av = c4; }
    AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry(const AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry& x, const AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry,long,AGG1ITEM1_L1_2STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG1ITEM1_L1_2STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry,long,AGG1ITEM1_L1_2STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123;
  
  struct AGG1ITEM1_L1_2STORE_SALES1_P_1_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit AGG1ITEM1_L1_2STORE_SALES1_P_1_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE_SALES1_P_1_entry(const long c0, const long c1) { STORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry(const AGG1ITEM1_L1_2STORE_SALES1_P_1_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES1_P_1_entry& modify(const long c0) { STORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE_SALES1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES1_P_1_entry& x, const AGG1ITEM1_L1_2STORE_SALES1_P_1_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE_SALES1_P_1_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_1_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_1_mapkey0_idxfn,true>
  > AGG1ITEM1_L1_2STORE_SALES1_P_1_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_1_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_1_mapkey0_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_1_map_0;
  
  struct AGG1ITEM1_L1_2STORE_SALES1_P_2_entry {
    long STORE_SALES_SS_CDEMO_SK; long __av; 
    explicit AGG1ITEM1_L1_2STORE_SALES1_P_2_entry() { /*STORE_SALES_SS_CDEMO_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE_SALES1_P_2_entry(const long c0, const long c1) { STORE_SALES_SS_CDEMO_SK = c0; __av = c1; }
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry(const AGG1ITEM1_L1_2STORE_SALES1_P_2_entry& other) : STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES1_P_2_entry& modify(const long c0) { STORE_SALES_SS_CDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES1_P_2_entry& x, const AGG1ITEM1_L1_2STORE_SALES1_P_2_entry& y) {
      return x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE_SALES1_P_2_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_2_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_2_mapkey0_idxfn,true>
  > AGG1ITEM1_L1_2STORE_SALES1_P_2_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_2_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_2_map_0;
  
  struct AGG1ITEM1_L1_2STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1ITEM1_L1_2STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE_SALES1_P_3_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry(const AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& x, const AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& x, const AGG1ITEM1_L1_2STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE_SALES1_P_3_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_3_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_3_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn,false>
  > AGG1ITEM1_L1_2STORE_SALES1_P_3_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_3_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_01;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES1_P_3_entry,long,AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn,false> HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0;
  
  struct AGG1ITEM1_L1_2STORE1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_STORE_SK; long __av; 
    explicit AGG1ITEM1_L1_2STORE1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE1_entry(const long c0, const long c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; __av = c2; }
    AGG1ITEM1_L1_2STORE1_entry(const AGG1ITEM1_L1_2STORE1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE1_entry& modify(const long c0, const long c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2STORE1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2STORE1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE1_entry& x, const AGG1ITEM1_L1_2STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct AGG1ITEM1_L1_2STORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE1_entry& x, const AGG1ITEM1_L1_2STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG1ITEM1_L1_2STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE1_entry& x, const AGG1ITEM1_L1_2STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE1_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey0_idxfn,false>,
    HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey1_idxfn,false>
  > AGG1ITEM1_L1_2STORE1_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE1_map_01;
  typedef HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey0_idxfn,false> HashIndex_AGG1ITEM1_L1_2STORE1_map_0;
  typedef HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey1_idxfn,false> HashIndex_AGG1ITEM1_L1_2STORE1_map_1;
  
  struct AGG1ITEM4_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1ITEM4_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1ITEM4_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1ITEM4_entry(const AGG1ITEM4_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1ITEM4_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4_entry& x, const AGG1ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4_entry& x, const AGG1ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM4_entry,long,
    HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey0_idxfn,false>
  > AGG1ITEM4_map;
  typedef HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey01_idxfn,true> HashIndex_AGG1ITEM4_map_01;
  typedef HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey0_idxfn,false> HashIndex_AGG1ITEM4_map_0;
  
  struct AGG1ITEM4STORE1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_STORE_SK; long __av; 
    explicit AGG1ITEM4STORE1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM4STORE1_entry(const long c0, const long c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; __av = c2; }
    AGG1ITEM4STORE1_entry(const AGG1ITEM4STORE1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM4STORE1_entry& modify(const long c0, const long c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG1ITEM4STORE1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG1ITEM4STORE1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM4STORE1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE1_entry& x, const AGG1ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct AGG1ITEM4STORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE1_entry& x, const AGG1ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG1ITEM4STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE1_entry& x, const AGG1ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM4STORE1_entry,long,
    HashIndex<AGG1ITEM4STORE1_entry,long,AGG1ITEM4STORE1_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM4STORE1_entry,long,AGG1ITEM4STORE1_mapkey0_idxfn,false>,
    HashIndex<AGG1ITEM4STORE1_entry,long,AGG1ITEM4STORE1_mapkey1_idxfn,false>
  > AGG1ITEM4STORE1_map;
  typedef HashIndex<AGG1ITEM4STORE1_entry,long,AGG1ITEM4STORE1_mapkey01_idxfn,true> HashIndex_AGG1ITEM4STORE1_map_01;
  typedef HashIndex<AGG1ITEM4STORE1_entry,long,AGG1ITEM4STORE1_mapkey0_idxfn,false> HashIndex_AGG1ITEM4STORE1_map_0;
  typedef HashIndex<AGG1ITEM4STORE1_entry,long,AGG1ITEM4STORE1_mapkey1_idxfn,false> HashIndex_AGG1ITEM4STORE1_map_1;
  
  struct AGG1ITEM4STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_STORE_SK; long __av; 
    explicit AGG1ITEM4STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM4STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3; __av = c4; }
    AGG1ITEM4STORE_SALES1_DELTA_entry(const AGG1ITEM4STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM4STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE_SALES1_DELTA_entry& x, const AGG1ITEM4STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM4STORE_SALES1_DELTA_entry,long,
    HashIndex<AGG1ITEM4STORE_SALES1_DELTA_entry,long,AGG1ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG1ITEM4STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG1ITEM4STORE_SALES1_DELTA_entry,long,AGG1ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123;
  
  struct AGG1ITEM4STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1ITEM4STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1ITEM4STORE_SALES1_P_3_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1ITEM4STORE_SALES1_P_3_entry(const AGG1ITEM4STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM4STORE_SALES1_P_3_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1ITEM4STORE_SALES1_P_3_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM4STORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE_SALES1_P_3_entry& x, const AGG1ITEM4STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE_SALES1_P_3_entry& x, const AGG1ITEM4STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM4STORE_SALES1_P_3_entry,long,
    HashIndex<AGG1ITEM4STORE_SALES1_P_3_entry,long,AGG1ITEM4STORE_SALES1_P_3_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM4STORE_SALES1_P_3_entry,long,AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn,false>
  > AGG1ITEM4STORE_SALES1_P_3_map;
  typedef HashIndex<AGG1ITEM4STORE_SALES1_P_3_entry,long,AGG1ITEM4STORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_01;
  typedef HashIndex<AGG1ITEM4STORE_SALES1_P_3_entry,long,AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn,false> HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0;
  
  struct AGG1STORE1_DOMAIN1_entry {
    STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1STORE1_DOMAIN1_entry() { /*STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1STORE1_DOMAIN1_entry(const STRING_TYPE& c0, const long c1) { STORE_S_STATE = c0; __av = c1; }
    AGG1STORE1_DOMAIN1_entry(const AGG1STORE1_DOMAIN1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE1_DOMAIN1_entry& modify(const STRING_TYPE& c0) { STORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE1_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_DOMAIN1_entry& x, const AGG1STORE1_DOMAIN1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1STORE1_DOMAIN1_entry,long,
    HashIndex<AGG1STORE1_DOMAIN1_entry,long,AGG1STORE1_DOMAIN1_mapkey0_idxfn,true>
  > AGG1STORE1_DOMAIN1_map;
  typedef HashIndex<AGG1STORE1_DOMAIN1_entry,long,AGG1STORE1_DOMAIN1_mapkey0_idxfn,true> HashIndex_AGG1STORE1_DOMAIN1_map_0;
  
  struct AGG1STORE1_P_2_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE1_P_2_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE1_P_2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE1_P_2_entry(const AGG1STORE1_P_2_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE1_P_2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE1_P_2_entry& modify0(const STRING_TYPE& c0) { STORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_P_2_entry& x, const AGG1STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_P_2_entry& x, const AGG1STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1STORE1_P_2_entry,long,
    HashIndex<AGG1STORE1_P_2_entry,long,AGG1STORE1_P_2_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE1_P_2_entry,long,AGG1STORE1_P_2_mapkey0_idxfn,false>
  > AGG1STORE1_P_2_map;
  typedef HashIndex<AGG1STORE1_P_2_entry,long,AGG1STORE1_P_2_mapkey01_idxfn,true> HashIndex_AGG1STORE1_P_2_map_01;
  typedef HashIndex<AGG1STORE1_P_2_entry,long,AGG1STORE1_P_2_mapkey0_idxfn,false> HashIndex_AGG1STORE1_P_2_map_0;
  
  struct AGG1STORE1_P_2ITEM1_entry {
    STRING_TYPE STORE_S_STATE; long STORE_SALES_SS_ITEM_SK; long __av; 
    explicit AGG1STORE1_P_2ITEM1_entry() { /*STORE_S_STATE = ""; STORE_SALES_SS_ITEM_SK = 0L; __av = 0L; */ }
    explicit AGG1STORE1_P_2ITEM1_entry(const STRING_TYPE& c0, const long c1, const long c2) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1; __av = c2; }
    AGG1STORE1_P_2ITEM1_entry(const AGG1STORE1_P_2ITEM1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE1_P_2ITEM1_entry& modify(const STRING_TYPE& c0, const long c1) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    FORCE_INLINE AGG1STORE1_P_2ITEM1_entry& modify1(const long c1) { STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE1_P_2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_P_2ITEM1_entry& x, const AGG1STORE1_P_2ITEM1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG1STORE1_P_2ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_P_2ITEM1_entry& x, const AGG1STORE1_P_2ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE1_P_2ITEM1_entry,long,
    HashIndex<AGG1STORE1_P_2ITEM1_entry,long,AGG1STORE1_P_2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE1_P_2ITEM1_entry,long,AGG1STORE1_P_2ITEM1_mapkey1_idxfn,false>
  > AGG1STORE1_P_2ITEM1_map;
  typedef HashIndex<AGG1STORE1_P_2ITEM1_entry,long,AGG1STORE1_P_2ITEM1_mapkey01_idxfn,true> HashIndex_AGG1STORE1_P_2ITEM1_map_01;
  typedef HashIndex<AGG1STORE1_P_2ITEM1_entry,long,AGG1STORE1_P_2ITEM1_mapkey1_idxfn,false> HashIndex_AGG1STORE1_P_2ITEM1_map_1;
  
  struct AGG1STORE1_P_2STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE1_P_2STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE1_P_2STORE_SALES1_P_3_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE1_P_2STORE_SALES1_P_3_entry(const AGG1STORE1_P_2STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE1_P_2STORE_SALES1_P_3_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE1_P_2STORE_SALES1_P_3_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE1_P_2STORE_SALES1_P_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_P_2STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_P_2STORE_SALES1_P_3_entry& x, const AGG1STORE1_P_2STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_P_2STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_P_2STORE_SALES1_P_3_entry& x, const AGG1STORE1_P_2STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE1_P_2STORE_SALES1_P_3_entry,long,
    HashIndex<AGG1STORE1_P_2STORE_SALES1_P_3_entry,long,AGG1STORE1_P_2STORE_SALES1_P_3_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE1_P_2STORE_SALES1_P_3_entry,long,AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn,false>
  > AGG1STORE1_P_2STORE_SALES1_P_3_map;
  typedef HashIndex<AGG1STORE1_P_2STORE_SALES1_P_3_entry,long,AGG1STORE1_P_2STORE_SALES1_P_3_mapkey01_idxfn,true> HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_01;
  typedef HashIndex<AGG1STORE1_P_2STORE_SALES1_P_3_entry,long,AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn,false> HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0;
  
  struct AGG1STORE1_L1_2_DELTA_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1STORE1_L1_2_DELTA_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1STORE1_L1_2_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1STORE1_L1_2_DELTA_entry(const AGG1STORE1_L1_2_DELTA_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE1_L1_2_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1STORE1_L1_2_DELTA_entry& modify1(const STRING_TYPE& c1) { STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE1_L1_2_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_L1_2_DELTA_entry& x, const AGG1STORE1_L1_2_DELTA_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1STORE1_L1_2_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_L1_2_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_L1_2_DELTA_entry& x, const AGG1STORE1_L1_2_DELTA_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1STORE1_L1_2_DELTA_entry,long,
    HashIndex<AGG1STORE1_L1_2_DELTA_entry,long,AGG1STORE1_L1_2_DELTA_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE1_L1_2_DELTA_entry,long,AGG1STORE1_L1_2_DELTA_mapkey1_idxfn,false>
  > AGG1STORE1_L1_2_DELTA_map;
  typedef HashIndex<AGG1STORE1_L1_2_DELTA_entry,long,AGG1STORE1_L1_2_DELTA_mapkey01_idxfn,true> HashIndex_AGG1STORE1_L1_2_DELTA_map_01;
  typedef HashIndex<AGG1STORE1_L1_2_DELTA_entry,long,AGG1STORE1_L1_2_DELTA_mapkey1_idxfn,false> HashIndex_AGG1STORE1_L1_2_DELTA_map_1;
  
  struct AGG1STORE1_L1_2_entry {
    STRING_TYPE ITEM_I_ITEM_ID; long STORE_SALES_SS_STORE_SK; long __av; 
    explicit AGG1STORE1_L1_2_entry() { /*ITEM_I_ITEM_ID = ""; STORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1STORE1_L1_2_entry(const STRING_TYPE& c0, const long c1, const long c2) { ITEM_I_ITEM_ID = c0; STORE_SALES_SS_STORE_SK = c1; __av = c2; }
    AGG1STORE1_L1_2_entry(const AGG1STORE1_L1_2_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE1_L1_2_entry& modify(const STRING_TYPE& c0, const long c1) { ITEM_I_ITEM_ID = c0; STORE_SALES_SS_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG1STORE1_L1_2_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE1_L1_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_L1_2_entry& x, const AGG1STORE1_L1_2_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct AGG1STORE1_L1_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE1_L1_2_entry& x, const AGG1STORE1_L1_2_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE1_L1_2_entry,long,
    HashIndex<AGG1STORE1_L1_2_entry,long,AGG1STORE1_L1_2_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE1_L1_2_entry,long,AGG1STORE1_L1_2_mapkey1_idxfn,false>
  > AGG1STORE1_L1_2_map;
  typedef HashIndex<AGG1STORE1_L1_2_entry,long,AGG1STORE1_L1_2_mapkey01_idxfn,true> HashIndex_AGG1STORE1_L1_2_map_01;
  typedef HashIndex<AGG1STORE1_L1_2_entry,long,AGG1STORE1_L1_2_mapkey1_idxfn,false> HashIndex_AGG1STORE1_L1_2_map_1;
  
  struct AGG1STORE4_DELTA_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1STORE4_DELTA_entry() { /*STORE_SALES_SS_STORE_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1STORE4_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1STORE4_DELTA_entry(const AGG1STORE4_DELTA_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE4_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1STORE4_DELTA_entry& modify1(const STRING_TYPE& c1) { STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE4_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE4_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE4_DELTA_entry& x, const AGG1STORE4_DELTA_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1STORE4_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE4_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE4_DELTA_entry& x, const AGG1STORE4_DELTA_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1STORE4_DELTA_entry,long,
    HashIndex<AGG1STORE4_DELTA_entry,long,AGG1STORE4_DELTA_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE4_DELTA_entry,long,AGG1STORE4_DELTA_mapkey1_idxfn,false>
  > AGG1STORE4_DELTA_map;
  typedef HashIndex<AGG1STORE4_DELTA_entry,long,AGG1STORE4_DELTA_mapkey01_idxfn,true> HashIndex_AGG1STORE4_DELTA_map_01;
  typedef HashIndex<AGG1STORE4_DELTA_entry,long,AGG1STORE4_DELTA_mapkey1_idxfn,false> HashIndex_AGG1STORE4_DELTA_map_1;
  
  struct AGG1STORE4_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE4_entry() { /*STORE_SALES_SS_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE4_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE4_entry(const AGG1STORE4_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE4_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE4_entry& x, const AGG1STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE4_entry& x, const AGG1STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE4_entry,long,
    HashIndex<AGG1STORE4_entry,long,AGG1STORE4_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE4_entry,long,AGG1STORE4_mapkey0_idxfn,false>
  > AGG1STORE4_map;
  typedef HashIndex<AGG1STORE4_entry,long,AGG1STORE4_mapkey01_idxfn,true> HashIndex_AGG1STORE4_map_01;
  typedef HashIndex<AGG1STORE4_entry,long,AGG1STORE4_mapkey0_idxfn,false> HashIndex_AGG1STORE4_map_0;
  
  struct AGG1STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE_SALES1_entry(const AGG1STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1_entry& x, const AGG1STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1_entry& x, const AGG1STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1STORE_SALES1_entry,long,
    HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey1_idxfn,false>
  > AGG1STORE_SALES1_map;
  typedef HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG1STORE_SALES1_map_01;
  typedef HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG1STORE_SALES1_map_1;
  
  struct AGG1STORE_SALES1_L1_1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1STORE_SALES1_L1_1_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1STORE_SALES1_L1_1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1STORE_SALES1_L1_1_entry(const AGG1STORE_SALES1_L1_1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE_SALES1_L1_1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE_SALES1_L1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1_L1_1_entry& x, const AGG1STORE_SALES1_L1_1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1STORE_SALES1_L1_1_entry,long,
    HashIndex<AGG1STORE_SALES1_L1_1_entry,long,AGG1STORE_SALES1_L1_1_mapkey01_idxfn,true>
  > AGG1STORE_SALES1_L1_1_map;
  typedef HashIndex<AGG1STORE_SALES1_L1_1_entry,long,AGG1STORE_SALES1_L1_1_mapkey01_idxfn,true> HashIndex_AGG1STORE_SALES1_L1_1_map_01;
  
  struct AGG2_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG2_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG2_entry(const AGG2_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2_entry& x, const AGG2_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG2_entry,DOUBLE_TYPE,
    HashIndex<AGG2_entry,DOUBLE_TYPE,AGG2_mapkey01_idxfn,true>
  > AGG2_map;
  typedef HashIndex<AGG2_entry,DOUBLE_TYPE,AGG2_mapkey01_idxfn,true> HashIndex_AGG2_map_01;
  
  struct AGG2ITEM4_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG2ITEM4_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG2ITEM4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG2ITEM4_entry(const AGG2ITEM4_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG2ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG2ITEM4_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4_entry& x, const AGG2ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG2ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4_entry& x, const AGG2ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG2ITEM4_entry,DOUBLE_TYPE,
    HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey0_idxfn,false>
  > AGG2ITEM4_map;
  typedef HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey01_idxfn,true> HashIndex_AGG2ITEM4_map_01;
  typedef HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey0_idxfn,false> HashIndex_AGG2ITEM4_map_0;
  
  struct AGG2ITEM4STORE1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG2ITEM4STORE1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG2ITEM4STORE1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; __av = c2; }
    AGG2ITEM4STORE1_entry(const AGG2ITEM4STORE1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG2ITEM4STORE1_entry& modify(const long c0, const long c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG2ITEM4STORE1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG2ITEM4STORE1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2ITEM4STORE1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4STORE1_entry& x, const AGG2ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct AGG2ITEM4STORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4STORE1_entry& x, const AGG2ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG2ITEM4STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4STORE1_entry& x, const AGG2ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG2ITEM4STORE1_entry,DOUBLE_TYPE,
    HashIndex<AGG2ITEM4STORE1_entry,DOUBLE_TYPE,AGG2ITEM4STORE1_mapkey01_idxfn,true>,
    HashIndex<AGG2ITEM4STORE1_entry,DOUBLE_TYPE,AGG2ITEM4STORE1_mapkey0_idxfn,false>,
    HashIndex<AGG2ITEM4STORE1_entry,DOUBLE_TYPE,AGG2ITEM4STORE1_mapkey1_idxfn,false>
  > AGG2ITEM4STORE1_map;
  typedef HashIndex<AGG2ITEM4STORE1_entry,DOUBLE_TYPE,AGG2ITEM4STORE1_mapkey01_idxfn,true> HashIndex_AGG2ITEM4STORE1_map_01;
  typedef HashIndex<AGG2ITEM4STORE1_entry,DOUBLE_TYPE,AGG2ITEM4STORE1_mapkey0_idxfn,false> HashIndex_AGG2ITEM4STORE1_map_0;
  typedef HashIndex<AGG2ITEM4STORE1_entry,DOUBLE_TYPE,AGG2ITEM4STORE1_mapkey1_idxfn,false> HashIndex_AGG2ITEM4STORE1_map_1;
  
  struct AGG2ITEM4STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG2ITEM4STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG2ITEM4STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3; __av = c4; }
    AGG2ITEM4STORE_SALES1_DELTA_entry(const AGG2ITEM4STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG2ITEM4STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4STORE_SALES1_DELTA_entry& x, const AGG2ITEM4STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG2ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AGG2ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG2ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG2ITEM4STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG2ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG2ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123;
  
  struct AGG2STORE1_P_2_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2STORE1_P_2_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2STORE1_P_2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG2STORE1_P_2_entry(const AGG2STORE1_P_2_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE1_P_2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG2STORE1_P_2_entry& modify0(const STRING_TYPE& c0) { STORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE1_P_2_entry& x, const AGG2STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG2STORE1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE1_P_2_entry& x, const AGG2STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG2STORE1_P_2_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE1_P_2_entry,DOUBLE_TYPE,AGG2STORE1_P_2_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE1_P_2_entry,DOUBLE_TYPE,AGG2STORE1_P_2_mapkey0_idxfn,false>
  > AGG2STORE1_P_2_map;
  typedef HashIndex<AGG2STORE1_P_2_entry,DOUBLE_TYPE,AGG2STORE1_P_2_mapkey01_idxfn,true> HashIndex_AGG2STORE1_P_2_map_01;
  typedef HashIndex<AGG2STORE1_P_2_entry,DOUBLE_TYPE,AGG2STORE1_P_2_mapkey0_idxfn,false> HashIndex_AGG2STORE1_P_2_map_0;
  
  struct AGG2STORE1_P_2ITEM1_entry {
    STRING_TYPE STORE_S_STATE; long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit AGG2STORE1_P_2ITEM1_entry() { /*STORE_S_STATE = ""; STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit AGG2STORE1_P_2ITEM1_entry(const STRING_TYPE& c0, const long c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1; __av = c2; }
    AGG2STORE1_P_2ITEM1_entry(const AGG2STORE1_P_2ITEM1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE1_P_2ITEM1_entry& modify(const STRING_TYPE& c0, const long c1) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    FORCE_INLINE AGG2STORE1_P_2ITEM1_entry& modify1(const long c1) { STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE1_P_2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE1_P_2ITEM1_entry& x, const AGG2STORE1_P_2ITEM1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG2STORE1_P_2ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE1_P_2ITEM1_entry& x, const AGG2STORE1_P_2ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG2STORE1_P_2ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG2STORE1_P_2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG2STORE1_P_2ITEM1_mapkey1_idxfn,false>
  > AGG2STORE1_P_2ITEM1_map;
  typedef HashIndex<AGG2STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG2STORE1_P_2ITEM1_mapkey01_idxfn,true> HashIndex_AGG2STORE1_P_2ITEM1_map_01;
  typedef HashIndex<AGG2STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG2STORE1_P_2ITEM1_mapkey1_idxfn,false> HashIndex_AGG2STORE1_P_2ITEM1_map_1;
  
  struct AGG2STORE4_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2STORE4_entry() { /*STORE_SALES_SS_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2STORE4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG2STORE4_entry(const AGG2STORE4_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG2STORE4_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE4_entry& x, const AGG2STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG2STORE4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE4_entry& x, const AGG2STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG2STORE4_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE4_entry,DOUBLE_TYPE,AGG2STORE4_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE4_entry,DOUBLE_TYPE,AGG2STORE4_mapkey0_idxfn,false>
  > AGG2STORE4_map;
  typedef HashIndex<AGG2STORE4_entry,DOUBLE_TYPE,AGG2STORE4_mapkey01_idxfn,true> HashIndex_AGG2STORE4_map_01;
  typedef HashIndex<AGG2STORE4_entry,DOUBLE_TYPE,AGG2STORE4_mapkey0_idxfn,false> HashIndex_AGG2STORE4_map_0;
  
  struct AGG2STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG2STORE_SALES1_entry(const AGG2STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG2STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE_SALES1_entry& x, const AGG2STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG2STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE_SALES1_entry& x, const AGG2STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG2STORE_SALES1_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey1_idxfn,false>
  > AGG2STORE_SALES1_map;
  typedef HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG2STORE_SALES1_map_01;
  typedef HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG2STORE_SALES1_map_1;
  
  struct AGG3_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG3_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG3_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG3_entry(const AGG3_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG3_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3_entry& x, const AGG3_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG3_entry,DOUBLE_TYPE,
    HashIndex<AGG3_entry,DOUBLE_TYPE,AGG3_mapkey01_idxfn,true>
  > AGG3_map;
  typedef HashIndex<AGG3_entry,DOUBLE_TYPE,AGG3_mapkey01_idxfn,true> HashIndex_AGG3_map_01;
  
  struct AGG3ITEM4_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG3ITEM4_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG3ITEM4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG3ITEM4_entry(const AGG3ITEM4_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG3ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG3ITEM4_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4_entry& x, const AGG3ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG3ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4_entry& x, const AGG3ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG3ITEM4_entry,DOUBLE_TYPE,
    HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey0_idxfn,false>
  > AGG3ITEM4_map;
  typedef HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey01_idxfn,true> HashIndex_AGG3ITEM4_map_01;
  typedef HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey0_idxfn,false> HashIndex_AGG3ITEM4_map_0;
  
  struct AGG3ITEM4STORE1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG3ITEM4STORE1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG3ITEM4STORE1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; __av = c2; }
    AGG3ITEM4STORE1_entry(const AGG3ITEM4STORE1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG3ITEM4STORE1_entry& modify(const long c0, const long c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG3ITEM4STORE1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG3ITEM4STORE1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3ITEM4STORE1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4STORE1_entry& x, const AGG3ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct AGG3ITEM4STORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4STORE1_entry& x, const AGG3ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG3ITEM4STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4STORE1_entry& x, const AGG3ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG3ITEM4STORE1_entry,DOUBLE_TYPE,
    HashIndex<AGG3ITEM4STORE1_entry,DOUBLE_TYPE,AGG3ITEM4STORE1_mapkey01_idxfn,true>,
    HashIndex<AGG3ITEM4STORE1_entry,DOUBLE_TYPE,AGG3ITEM4STORE1_mapkey0_idxfn,false>,
    HashIndex<AGG3ITEM4STORE1_entry,DOUBLE_TYPE,AGG3ITEM4STORE1_mapkey1_idxfn,false>
  > AGG3ITEM4STORE1_map;
  typedef HashIndex<AGG3ITEM4STORE1_entry,DOUBLE_TYPE,AGG3ITEM4STORE1_mapkey01_idxfn,true> HashIndex_AGG3ITEM4STORE1_map_01;
  typedef HashIndex<AGG3ITEM4STORE1_entry,DOUBLE_TYPE,AGG3ITEM4STORE1_mapkey0_idxfn,false> HashIndex_AGG3ITEM4STORE1_map_0;
  typedef HashIndex<AGG3ITEM4STORE1_entry,DOUBLE_TYPE,AGG3ITEM4STORE1_mapkey1_idxfn,false> HashIndex_AGG3ITEM4STORE1_map_1;
  
  struct AGG3ITEM4STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG3ITEM4STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG3ITEM4STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3; __av = c4; }
    AGG3ITEM4STORE_SALES1_DELTA_entry(const AGG3ITEM4STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG3ITEM4STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4STORE_SALES1_DELTA_entry& x, const AGG3ITEM4STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG3ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AGG3ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG3ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG3ITEM4STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG3ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG3ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123;
  
  struct AGG3STORE1_P_2_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3STORE1_P_2_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3STORE1_P_2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG3STORE1_P_2_entry(const AGG3STORE1_P_2_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE1_P_2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG3STORE1_P_2_entry& modify0(const STRING_TYPE& c0) { STORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE1_P_2_entry& x, const AGG3STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG3STORE1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE1_P_2_entry& x, const AGG3STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG3STORE1_P_2_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE1_P_2_entry,DOUBLE_TYPE,AGG3STORE1_P_2_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE1_P_2_entry,DOUBLE_TYPE,AGG3STORE1_P_2_mapkey0_idxfn,false>
  > AGG3STORE1_P_2_map;
  typedef HashIndex<AGG3STORE1_P_2_entry,DOUBLE_TYPE,AGG3STORE1_P_2_mapkey01_idxfn,true> HashIndex_AGG3STORE1_P_2_map_01;
  typedef HashIndex<AGG3STORE1_P_2_entry,DOUBLE_TYPE,AGG3STORE1_P_2_mapkey0_idxfn,false> HashIndex_AGG3STORE1_P_2_map_0;
  
  struct AGG3STORE1_P_2ITEM1_entry {
    STRING_TYPE STORE_S_STATE; long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit AGG3STORE1_P_2ITEM1_entry() { /*STORE_S_STATE = ""; STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit AGG3STORE1_P_2ITEM1_entry(const STRING_TYPE& c0, const long c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1; __av = c2; }
    AGG3STORE1_P_2ITEM1_entry(const AGG3STORE1_P_2ITEM1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE1_P_2ITEM1_entry& modify(const STRING_TYPE& c0, const long c1) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    FORCE_INLINE AGG3STORE1_P_2ITEM1_entry& modify1(const long c1) { STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE1_P_2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE1_P_2ITEM1_entry& x, const AGG3STORE1_P_2ITEM1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG3STORE1_P_2ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE1_P_2ITEM1_entry& x, const AGG3STORE1_P_2ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG3STORE1_P_2ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG3STORE1_P_2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG3STORE1_P_2ITEM1_mapkey1_idxfn,false>
  > AGG3STORE1_P_2ITEM1_map;
  typedef HashIndex<AGG3STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG3STORE1_P_2ITEM1_mapkey01_idxfn,true> HashIndex_AGG3STORE1_P_2ITEM1_map_01;
  typedef HashIndex<AGG3STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG3STORE1_P_2ITEM1_mapkey1_idxfn,false> HashIndex_AGG3STORE1_P_2ITEM1_map_1;
  
  struct AGG3STORE4_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3STORE4_entry() { /*STORE_SALES_SS_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3STORE4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG3STORE4_entry(const AGG3STORE4_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG3STORE4_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE4_entry& x, const AGG3STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG3STORE4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE4_entry& x, const AGG3STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG3STORE4_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE4_entry,DOUBLE_TYPE,AGG3STORE4_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE4_entry,DOUBLE_TYPE,AGG3STORE4_mapkey0_idxfn,false>
  > AGG3STORE4_map;
  typedef HashIndex<AGG3STORE4_entry,DOUBLE_TYPE,AGG3STORE4_mapkey01_idxfn,true> HashIndex_AGG3STORE4_map_01;
  typedef HashIndex<AGG3STORE4_entry,DOUBLE_TYPE,AGG3STORE4_mapkey0_idxfn,false> HashIndex_AGG3STORE4_map_0;
  
  struct AGG3STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG3STORE_SALES1_entry(const AGG3STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG3STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE_SALES1_entry& x, const AGG3STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG3STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE_SALES1_entry& x, const AGG3STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG3STORE_SALES1_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey1_idxfn,false>
  > AGG3STORE_SALES1_map;
  typedef HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG3STORE_SALES1_map_01;
  typedef HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG3STORE_SALES1_map_1;
  
  struct AGG4_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG4_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG4_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG4_entry(const AGG4_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG4_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4_entry& x, const AGG4_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG4_entry,DOUBLE_TYPE,
    HashIndex<AGG4_entry,DOUBLE_TYPE,AGG4_mapkey01_idxfn,true>
  > AGG4_map;
  typedef HashIndex<AGG4_entry,DOUBLE_TYPE,AGG4_mapkey01_idxfn,true> HashIndex_AGG4_map_01;
  
  struct AGG4ITEM4_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG4ITEM4_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG4ITEM4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG4ITEM4_entry(const AGG4ITEM4_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG4ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG4ITEM4_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4_entry& x, const AGG4ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG4ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4_entry& x, const AGG4ITEM4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG4ITEM4_entry,DOUBLE_TYPE,
    HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey0_idxfn,false>
  > AGG4ITEM4_map;
  typedef HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey01_idxfn,true> HashIndex_AGG4ITEM4_map_01;
  typedef HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey0_idxfn,false> HashIndex_AGG4ITEM4_map_0;
  
  struct AGG4ITEM4STORE1_entry {
    long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG4ITEM4STORE1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG4ITEM4STORE1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1; __av = c2; }
    AGG4ITEM4STORE1_entry(const AGG4ITEM4STORE1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG4ITEM4STORE1_entry& modify(const long c0, const long c1) { STORE_SALES_SS_ITEM_SK = c0; STORE_SALES_SS_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG4ITEM4STORE1_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG4ITEM4STORE1_entry& modify1(const long c1) { STORE_SALES_SS_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4ITEM4STORE1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4STORE1_entry& x, const AGG4ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  struct AGG4ITEM4STORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4STORE1_entry& x, const AGG4ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG4ITEM4STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4STORE1_entry& x, const AGG4ITEM4STORE1_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG4ITEM4STORE1_entry,DOUBLE_TYPE,
    HashIndex<AGG4ITEM4STORE1_entry,DOUBLE_TYPE,AGG4ITEM4STORE1_mapkey01_idxfn,true>,
    HashIndex<AGG4ITEM4STORE1_entry,DOUBLE_TYPE,AGG4ITEM4STORE1_mapkey0_idxfn,false>,
    HashIndex<AGG4ITEM4STORE1_entry,DOUBLE_TYPE,AGG4ITEM4STORE1_mapkey1_idxfn,false>
  > AGG4ITEM4STORE1_map;
  typedef HashIndex<AGG4ITEM4STORE1_entry,DOUBLE_TYPE,AGG4ITEM4STORE1_mapkey01_idxfn,true> HashIndex_AGG4ITEM4STORE1_map_01;
  typedef HashIndex<AGG4ITEM4STORE1_entry,DOUBLE_TYPE,AGG4ITEM4STORE1_mapkey0_idxfn,false> HashIndex_AGG4ITEM4STORE1_map_0;
  typedef HashIndex<AGG4ITEM4STORE1_entry,DOUBLE_TYPE,AGG4ITEM4STORE1_mapkey1_idxfn,false> HashIndex_AGG4ITEM4STORE1_map_1;
  
  struct AGG4ITEM4STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG4ITEM4STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG4ITEM4STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3; __av = c4; }
    AGG4ITEM4STORE_SALES1_DELTA_entry(const AGG4ITEM4STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG4ITEM4STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_STORE_SK = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4STORE_SALES1_DELTA_entry& x, const AGG4ITEM4STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG4ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AGG4ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG4ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG4ITEM4STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG4ITEM4STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG4ITEM4STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123;
  
  struct AGG4STORE1_P_2_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4STORE1_P_2_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4STORE1_P_2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG4STORE1_P_2_entry(const AGG4STORE1_P_2_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE1_P_2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG4STORE1_P_2_entry& modify0(const STRING_TYPE& c0) { STORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE1_P_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE1_P_2_entry& x, const AGG4STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG4STORE1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE1_P_2_entry& x, const AGG4STORE1_P_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG4STORE1_P_2_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE1_P_2_entry,DOUBLE_TYPE,AGG4STORE1_P_2_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE1_P_2_entry,DOUBLE_TYPE,AGG4STORE1_P_2_mapkey0_idxfn,false>
  > AGG4STORE1_P_2_map;
  typedef HashIndex<AGG4STORE1_P_2_entry,DOUBLE_TYPE,AGG4STORE1_P_2_mapkey01_idxfn,true> HashIndex_AGG4STORE1_P_2_map_01;
  typedef HashIndex<AGG4STORE1_P_2_entry,DOUBLE_TYPE,AGG4STORE1_P_2_mapkey0_idxfn,false> HashIndex_AGG4STORE1_P_2_map_0;
  
  struct AGG4STORE1_P_2ITEM1_entry {
    STRING_TYPE STORE_S_STATE; long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit AGG4STORE1_P_2ITEM1_entry() { /*STORE_S_STATE = ""; STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit AGG4STORE1_P_2ITEM1_entry(const STRING_TYPE& c0, const long c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1; __av = c2; }
    AGG4STORE1_P_2ITEM1_entry(const AGG4STORE1_P_2ITEM1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE1_P_2ITEM1_entry& modify(const STRING_TYPE& c0, const long c1) { STORE_S_STATE = c0; STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    FORCE_INLINE AGG4STORE1_P_2ITEM1_entry& modify1(const long c1) { STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE1_P_2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE1_P_2ITEM1_entry& x, const AGG4STORE1_P_2ITEM1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct AGG4STORE1_P_2ITEM1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE1_P_2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE1_P_2ITEM1_entry& x, const AGG4STORE1_P_2ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG4STORE1_P_2ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG4STORE1_P_2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG4STORE1_P_2ITEM1_mapkey1_idxfn,false>
  > AGG4STORE1_P_2ITEM1_map;
  typedef HashIndex<AGG4STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG4STORE1_P_2ITEM1_mapkey01_idxfn,true> HashIndex_AGG4STORE1_P_2ITEM1_map_01;
  typedef HashIndex<AGG4STORE1_P_2ITEM1_entry,DOUBLE_TYPE,AGG4STORE1_P_2ITEM1_mapkey1_idxfn,false> HashIndex_AGG4STORE1_P_2ITEM1_map_1;
  
  struct AGG4STORE4_entry {
    long STORE_SALES_SS_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4STORE4_entry() { /*STORE_SALES_SS_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4STORE4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG4STORE4_entry(const AGG4STORE4_entry& other) : STORE_SALES_SS_STORE_SK( other.STORE_SALES_SS_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG4STORE4_entry& modify0(const long c0) { STORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE4_entry& x, const AGG4STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG4STORE4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE4_entry& x, const AGG4STORE4_entry& y) {
      return x.STORE_SALES_SS_STORE_SK == y.STORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG4STORE4_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE4_entry,DOUBLE_TYPE,AGG4STORE4_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE4_entry,DOUBLE_TYPE,AGG4STORE4_mapkey0_idxfn,false>
  > AGG4STORE4_map;
  typedef HashIndex<AGG4STORE4_entry,DOUBLE_TYPE,AGG4STORE4_mapkey01_idxfn,true> HashIndex_AGG4STORE4_map_01;
  typedef HashIndex<AGG4STORE4_entry,DOUBLE_TYPE,AGG4STORE4_mapkey0_idxfn,false> HashIndex_AGG4STORE4_map_0;
  
  struct AGG4STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG4STORE_SALES1_entry(const AGG4STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG4STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE_SALES1_entry& x, const AGG4STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG4STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE_SALES1_entry& x, const AGG4STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG4STORE_SALES1_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey1_idxfn,false>
  > AGG4STORE_SALES1_map;
  typedef HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG4STORE_SALES1_map_01;
  typedef HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG4STORE_SALES1_map_1;
  
  struct tuple2_S_D {
    STRING_TYPE _1; DOUBLE_TYPE __av;
    explicit tuple2_S_D() { }
    explicit tuple2_S_D(const STRING_TYPE& c1, DOUBLE_TYPE c__av=0.0) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_S_D &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_S_D& modify(const STRING_TYPE& c0, DOUBLE_TYPE c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_S_D &x, const tuple2_S_D &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_S_D &e) {
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
      const AGG1_map& _AGG1 = get_AGG1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG1), _AGG1, "\t");
      ar << "\n";
      const AGG2_map& _AGG2 = get_AGG2();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG2), _AGG2, "\t");
      ar << "\n";
      const AGG3_map& _AGG3 = get_AGG3();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG3), _AGG3, "\t");
      ar << "\n";
      const AGG4_map& _AGG4 = get_AGG4();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG4), _AGG4, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const AGG1_map& get_AGG1() const {
      return AGG1;
    
    }
    const AGG2_map& get_AGG2() const {
      return AGG2;
    
    }
    const AGG3_map& get_AGG3() const {
      return AGG3;
    
    }
    const AGG4_map& get_AGG4() const {
      return AGG4;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    AGG1_map AGG1;
    AGG2_map AGG2;
    AGG3_map AGG3;
    AGG4_map AGG4;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), _c1(16U), _c4(16U), _c3(16U), _c2(16U) {
      c2 = STRING_TYPE("LA");
      c9 = STRING_TYPE("M");
      c4 = STRING_TYPE("MI");
      c6 = STRING_TYPE("OH");
      c5 = STRING_TYPE("SC");
      c3 = STRING_TYPE("GA");
      c8 = STRING_TYPE("W");
      c7 = STRING_TYPE("College");
      c1 = STRING_TYPE("MO");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_DATE_DIM(const long date_dim_d_date_sk, const STRING_TYPE date_dim_d_date_id, const date date_dim_d_date, const long date_dim_d_month_seq, const long date_dim_d_week_seq, const long date_dim_d_quarter_seq, const long date_dim_d_year, const long date_dim_d_dow, const long date_dim_d_moy, const long date_dim_d_dom, const long date_dim_d_qoy, const long date_dim_d_fy_year, const long date_dim_d_fy_quarter_seq, const long date_dim_d_fy_week_seq, const STRING_TYPE date_dim_d_day_name, const STRING_TYPE date_dim_d_quarter_name, const STRING_TYPE date_dim_d_holiday, const STRING_TYPE date_dim_d_weekend, const STRING_TYPE date_dim_d_following_holiday, const long date_dim_d_first_dom, const long date_dim_d_last_dom, const long date_dim_d_same_day_ly, const long date_dim_d_same_day_lq, const STRING_TYPE date_dim_d_current_day, const STRING_TYPE date_dim_d_current_week, const STRING_TYPE date_dim_d_current_month, const STRING_TYPE date_dim_d_current_quarter, const STRING_TYPE date_dim_d_current_year) {
      DATE_DIM_entry e(date_dim_d_date_sk, date_dim_d_date_id, date_dim_d_date, date_dim_d_month_seq, date_dim_d_week_seq, date_dim_d_quarter_seq, date_dim_d_year, date_dim_d_dow, date_dim_d_moy, date_dim_d_dom, date_dim_d_qoy, date_dim_d_fy_year, date_dim_d_fy_quarter_seq, date_dim_d_fy_week_seq, date_dim_d_day_name, date_dim_d_quarter_name, date_dim_d_holiday, date_dim_d_weekend, date_dim_d_following_holiday, date_dim_d_first_dom, date_dim_d_last_dom, date_dim_d_same_day_ly, date_dim_d_same_day_lq, date_dim_d_current_day, date_dim_d_current_week, date_dim_d_current_month, date_dim_d_current_quarter, date_dim_d_current_year, 1L);
      DATE_DIM.addOrDelOnZero(e,1L);
    }
    
    void on_insert_CUSTOMER_DEMOGRAPHICS(const long customer_demographics_cd_demo_sk, const STRING_TYPE customer_demographics_cd_gender, const STRING_TYPE customer_demographics_cd_marital_status, const STRING_TYPE customer_demographics_cd_education_status, const long customer_demographics_cd_purchase_estimate, const STRING_TYPE customer_demographics_cd_credit_rating, const long customer_demographics_cd_dep_count, const long customer_demographics_cd_dep_employed_count, const long customer_demographics_cd_dep_college_count) {
      CUSTOMER_DEMOGRAPHICS_entry e(customer_demographics_cd_demo_sk, customer_demographics_cd_gender, customer_demographics_cd_marital_status, customer_demographics_cd_education_status, customer_demographics_cd_purchase_estimate, customer_demographics_cd_credit_rating, customer_demographics_cd_dep_count, customer_demographics_cd_dep_employed_count, customer_demographics_cd_dep_college_count, 1L);
      CUSTOMER_DEMOGRAPHICS.addOrDelOnZero(e,1L);
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

        AGG1ITEM1_L1_2STORE_SALES1_DELTA.clear();
        AGG1ITEM4STORE_SALES1_DELTA.clear();
        AGG2ITEM4STORE_SALES1_DELTA.clear();
        AGG3ITEM4STORE_SALES1_DELTA.clear();
        AGG4ITEM4STORE_SALES1_DELTA.clear();
        {  
          for (size_t i = 0; i < DELTA_STORE_SALES.size; i++) 
          {
                long store_sales_ss_sold_date_sk = DELTA_STORE_SALES.ss_sold_date_sk[i];
                // long store_sales_ss_sold_time_sk = DELTA_STORE_SALES.ss_sold_time_sk[i];
                long store_sales_ss_item_sk = DELTA_STORE_SALES.ss_item_sk[i];
                // long store_sales_ss_customer_sk = DELTA_STORE_SALES.ss_customer_sk[i];
                long store_sales_ss_cdemo_sk = DELTA_STORE_SALES.ss_cdemo_sk[i];
                // long store_sales_ss_hdemo_sk = DELTA_STORE_SALES.ss_hdemo_sk[i];
                // long store_sales_ss_addr_sk = DELTA_STORE_SALES.ss_addr_sk[i];
                long store_sales_ss_store_sk = DELTA_STORE_SALES.ss_store_sk[i];
                // long store_sales_ss_promo_sk = DELTA_STORE_SALES.ss_promo_sk[i];
                // long store_sales_ss_ticket_number = DELTA_STORE_SALES.ss_ticket_number[i];
                long store_sales_ss_quantity = DELTA_STORE_SALES.ss_quantity[i];
                // DOUBLE_TYPE store_sales_ss_wholesale_cost = DELTA_STORE_SALES.ss_wholesale_cost[i];
                DOUBLE_TYPE store_sales_ss_list_price = DELTA_STORE_SALES.ss_list_price[i];
                DOUBLE_TYPE store_sales_ss_sales_price = DELTA_STORE_SALES.ss_sales_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_discount_amt = DELTA_STORE_SALES.ss_ext_discount_amt[i];
                // DOUBLE_TYPE store_sales_ss_ext_sales_price = DELTA_STORE_SALES.ss_ext_sales_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_wholesale_cost = DELTA_STORE_SALES.ss_ext_wholesale_cost[i];
                // DOUBLE_TYPE store_sales_ss_ext_list_price = DELTA_STORE_SALES.ss_ext_list_price[i];
                // DOUBLE_TYPE store_sales_ss_ext_tax = DELTA_STORE_SALES.ss_ext_tax[i];
                DOUBLE_TYPE store_sales_ss_coupon_amt = DELTA_STORE_SALES.ss_coupon_amt[i];
                // DOUBLE_TYPE store_sales_ss_net_paid = DELTA_STORE_SALES.ss_net_paid[i];
                // DOUBLE_TYPE store_sales_ss_net_paid_inc_tax = DELTA_STORE_SALES.ss_net_paid_inc_tax[i];
                // DOUBLE_TYPE store_sales_ss_net_profit = DELTA_STORE_SALES.ss_net_profit[i];
                long v1 = 1L;
                AGG1ITEM1_L1_2STORE_SALES1_DELTA.addOrDelOnZero(se1.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_store_sk),v1);
                long v2 = 1L;
                AGG1ITEM4STORE_SALES1_DELTA.addOrDelOnZero(se2.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_store_sk),(v2 * store_sales_ss_quantity));
                long v3 = 1L;
                AGG2ITEM4STORE_SALES1_DELTA.addOrDelOnZero(se3.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_store_sk),(v3 * store_sales_ss_list_price));
                long v4 = 1L;
                AGG3ITEM4STORE_SALES1_DELTA.addOrDelOnZero(se4.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_store_sk),(v4 * store_sales_ss_coupon_amt));
                long v5 = 1L;
                AGG4ITEM4STORE_SALES1_DELTA.addOrDelOnZero(se5.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_store_sk),(v5 * store_sales_ss_sales_price));

          }
        }
               
        {  // foreach
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123* i6 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123*>(AGG1ITEM1_L1_2STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123::IdxNode* n6; 
          AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long store_sales_ss_sold_date_sk = e6->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e6->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e6->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e6->STORE_SALES_SS_STORE_SK;
                long v6 = e6->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i7 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h1 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se9.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n7 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i7->slice(se9, h1));
                  AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e7;
                 
                  if (n7 && (e7 = n7->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e7->STORE_S_STATE;
                      long v7 = e7->__av;
                      AGG1ITEM1_L1_2.addOrDelOnZero(se6.modify(store_s_state,store_sales_ss_item_sk),(v6 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se7.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se8.modify(store_sales_ss_cdemo_sk)) * v7))));
                      n7 = n7->nxt;
                    } while (n7 && (e7 = n7->obj) && h1 == n7->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se9, *e7)); 
                  }
                }
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123* i8 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123*>(AGG1ITEM1_L1_2STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123::IdxNode* n8; 
          AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long store_sales_ss_sold_date_sk = e8->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e8->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e8->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e8->STORE_SALES_SS_STORE_SK;
                long v8 = e8->__av;
                AGG1ITEM1_L1_2STORE1.addOrDelOnZero(se10.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(v8 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se11.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se12.modify(store_sales_ss_sold_date_sk)))));
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123* i9 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123*>(AGG1ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n9; 
          AGG1ITEM4STORE_SALES1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long store_sales_ss_sold_date_sk = e9->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e9->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e9->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e9->STORE_SALES_SS_STORE_SK;
                long v9 = e9->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i10 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h2 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se16.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n10 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i10->slice(se16, h2));
                  AGG1ITEM4STORE_SALES1_P_3_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e10->STORE_S_STATE;
                      long v10 = e10->__av;
                      AGG1ITEM4.addOrDelOnZero(se13.modify(store_sales_ss_item_sk,store_s_state),(v9 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se14.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se15.modify(store_sales_ss_cdemo_sk)) * v10))));
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h2 == n10->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se16, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123* i11 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123*>(AGG1ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n11; 
          AGG1ITEM4STORE_SALES1_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long store_sales_ss_sold_date_sk = e11->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e11->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e11->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e11->STORE_SALES_SS_STORE_SK;
                long v11 = e11->__av;
                AGG1ITEM4STORE1.addOrDelOnZero(se17.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(v11 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se18.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se19.modify(store_sales_ss_sold_date_sk)))));
              n11 = n11->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123* i12 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123*>(AGG1ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n12; 
          AGG1ITEM4STORE_SALES1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long store_sales_ss_sold_date_sk = e12->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e12->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e12->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e12->STORE_SALES_SS_STORE_SK;
                long v12 = e12->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i13 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h4 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se24.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n13 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i13->slice(se24, h4));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e13;
                 
                  if (n13 && (e13 = n13->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e13->ITEM_I_ITEM_ID;
                      long v13 = e13->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i14 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h3 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se23.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n14 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i14->slice(se23, h3));
                        AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e14;
                       
                        if (n14 && (e14 = n14->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e14->STORE_S_STATE;
                            long v14 = e14->__av;
                            AGG1STORE1_P_2.addOrDelOnZero(se20.modify(store_s_state,item_i_item_id),(v12 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se21.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se22.modify(store_sales_ss_sold_date_sk)) * (v13 * v14)))));
                            n14 = n14->nxt;
                          } while (n14 && (e14 = n14->obj) && h3 == n14->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se23, *e14)); 
                        }
                      }
                      n13 = n13->nxt;
                    } while (n13 && (e13 = n13->obj) && h4 == n13->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se24, *e13)); 
                  }
                }
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123* i15 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123*>(AGG1ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n15; 
          AGG1ITEM4STORE_SALES1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long store_sales_ss_sold_date_sk = e15->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e15->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e15->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e15->STORE_SALES_SS_STORE_SK;
                long v15 = e15->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i16 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h5 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se28.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n16 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i16->slice(se28, h5));
                  AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e16;
                 
                  if (n16 && (e16 = n16->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e16->STORE_S_STATE;
                      long v16 = e16->__av;
                      AGG1STORE1_P_2ITEM1.addOrDelOnZero(se25.modify(store_s_state,store_sales_ss_item_sk),(v15 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se26.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se27.modify(store_sales_ss_sold_date_sk)) * v16))));
                      n16 = n16->nxt;
                    } while (n16 && (e16 = n16->obj) && h5 == n16->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se28, *e16)); 
                  }
                }
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123* i17 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123*>(AGG1ITEM1_L1_2STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123::IdxNode* n17; 
          AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry* e17;
        
          for (size_t i = 0; i < i17->size_; i++)
          {
            n17 = i17->buckets_ + i;
            while (n17 && (e17 = n17->obj))
            {
                long store_sales_ss_sold_date_sk = e17->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e17->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e17->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e17->STORE_SALES_SS_STORE_SK;
                long v17 = e17->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i18 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h6 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se32.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n18 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i18->slice(se32, h6));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e18;
                 
                  if (n18 && (e18 = n18->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e18->ITEM_I_ITEM_ID;
                      long v18 = e18->__av;
                      AGG1STORE1_L1_2.addOrDelOnZero(se29.modify(item_i_item_id,store_sales_ss_store_sk),(v17 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se30.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se31.modify(store_sales_ss_cdemo_sk)) * v18))));
                      n18 = n18->nxt;
                    } while (n18 && (e18 = n18->obj) && h6 == n18->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se32, *e18)); 
                  }
                }
              n17 = n17->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123* i19 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123*>(AGG1ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n19; 
          AGG1ITEM4STORE_SALES1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long store_sales_ss_sold_date_sk = e19->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e19->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e19->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e19->STORE_SALES_SS_STORE_SK;
                long v19 = e19->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i20 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h7 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se36.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n20 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i20->slice(se36, h7));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e20->ITEM_I_ITEM_ID;
                      long v20 = e20->__av;
                      AGG1STORE4.addOrDelOnZero(se33.modify(store_sales_ss_store_sk,item_i_item_id),(v19 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se34.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se35.modify(store_sales_ss_sold_date_sk)) * v20))));
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h7 == n20->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se36, *e20)); 
                  }
                }
              n19 = n19->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123* i21 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123*>(AGG1ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n21; 
          AGG1ITEM4STORE_SALES1_DELTA_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                long store_sales_ss_sold_date_sk = e21->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e21->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e21->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e21->STORE_SALES_SS_STORE_SK;
                long v21 = e21->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i22 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h9 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se41.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n22 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i22->slice(se41, h9));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e22;
                 
                  if (n22 && (e22 = n22->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e22->ITEM_I_ITEM_ID;
                      long v22 = e22->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i23 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h8 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se40.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n23 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i23->slice(se40, h8));
                        AGG1ITEM4STORE_SALES1_P_3_entry* e23;
                       
                        if (n23 && (e23 = n23->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e23->STORE_S_STATE;
                            long v23 = e23->__av;
                            AGG1STORE_SALES1.addOrDelOnZero(se37.modify(store_s_state,item_i_item_id),(v21 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se38.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se39.modify(store_sales_ss_cdemo_sk)) * (v22 * v23)))));
                            n23 = n23->nxt;
                          } while (n23 && (e23 = n23->obj) && h8 == n23->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se40, *e23)); 
                        }
                      }
                      n22 = n22->nxt;
                    } while (n22 && (e22 = n22->obj) && h9 == n22->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se41, *e22)); 
                  }
                }
              n21 = n21->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123* i24 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123*>(AGG1ITEM1_L1_2STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2STORE_SALES1_DELTA_map_0123::IdxNode* n24; 
          AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                long store_sales_ss_sold_date_sk = e24->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e24->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e24->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e24->STORE_SALES_SS_STORE_SK;
                long v24 = e24->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i25 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h11 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se46.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n25 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i25->slice(se46, h11));
                  AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e25;
                 
                  if (n25 && (e25 = n25->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e25->STORE_S_STATE;
                      long v25 = e25->__av;
                      { //slice 
                        const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i26 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h10 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se45.modify0(store_sales_ss_item_sk));
                        HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n26 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i26->slice(se45, h10));
                        AGG1STORE1_P_2STORE_SALES1_P_3_entry* e26;
                       
                        if (n26 && (e26 = n26->obj)) {
                          do {                
                            STRING_TYPE item_i_item_id = e26->ITEM_I_ITEM_ID;
                            long v26 = e26->__av;
                            AGG1STORE_SALES1_L1_1.addOrDelOnZero(se42.modify(item_i_item_id,store_s_state),(v24 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se43.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se44.modify(store_sales_ss_sold_date_sk)) * (v25 * v26)))));
                            n26 = n26->nxt;
                          } while (n26 && (e26 = n26->obj) && h10 == n26->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se45, *e26)); 
                        }
                      }
                      n25 = n25->nxt;
                    } while (n25 && (e25 = n25->obj) && h11 == n25->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se46, *e25)); 
                  }
                }
              n24 = n24->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123* i27 = static_cast<HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123*>(AGG2ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n27; 
          AGG2ITEM4STORE_SALES1_DELTA_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                long store_sales_ss_sold_date_sk = e27->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e27->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e27->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e27->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v27 = e27->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i28 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h12 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se50.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n28 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i28->slice(se50, h12));
                  AGG1ITEM4STORE_SALES1_P_3_entry* e28;
                 
                  if (n28 && (e28 = n28->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e28->STORE_S_STATE;
                      long v28 = e28->__av;
                      AGG2ITEM4.addOrDelOnZero(se47.modify(store_sales_ss_item_sk,store_s_state),(v27 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se48.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se49.modify(store_sales_ss_cdemo_sk)) * v28))));
                      n28 = n28->nxt;
                    } while (n28 && (e28 = n28->obj) && h12 == n28->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se50, *e28)); 
                  }
                }
              n27 = n27->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123* i29 = static_cast<HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123*>(AGG2ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n29; 
          AGG2ITEM4STORE_SALES1_DELTA_entry* e29;
        
          for (size_t i = 0; i < i29->size_; i++)
          {
            n29 = i29->buckets_ + i;
            while (n29 && (e29 = n29->obj))
            {
                long store_sales_ss_sold_date_sk = e29->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e29->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e29->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e29->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v29 = e29->__av;
                AGG2ITEM4STORE1.addOrDelOnZero(se51.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(v29 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se52.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se53.modify(store_sales_ss_sold_date_sk)))));
              n29 = n29->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123* i30 = static_cast<HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123*>(AGG2ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n30; 
          AGG2ITEM4STORE_SALES1_DELTA_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long store_sales_ss_sold_date_sk = e30->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e30->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e30->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e30->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v30 = e30->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i31 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h14 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se58.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n31 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i31->slice(se58, h14));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e31;
                 
                  if (n31 && (e31 = n31->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e31->ITEM_I_ITEM_ID;
                      long v31 = e31->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i32 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h13 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se57.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n32 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i32->slice(se57, h13));
                        AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e32;
                       
                        if (n32 && (e32 = n32->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e32->STORE_S_STATE;
                            long v32 = e32->__av;
                            AGG2STORE1_P_2.addOrDelOnZero(se54.modify(store_s_state,item_i_item_id),(v30 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se55.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se56.modify(store_sales_ss_sold_date_sk)) * (v31 * v32)))));
                            n32 = n32->nxt;
                          } while (n32 && (e32 = n32->obj) && h13 == n32->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se57, *e32)); 
                        }
                      }
                      n31 = n31->nxt;
                    } while (n31 && (e31 = n31->obj) && h14 == n31->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se58, *e31)); 
                  }
                }
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123* i33 = static_cast<HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123*>(AGG2ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n33; 
          AGG2ITEM4STORE_SALES1_DELTA_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                long store_sales_ss_sold_date_sk = e33->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e33->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e33->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e33->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v33 = e33->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i34 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h15 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se62.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n34 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i34->slice(se62, h15));
                  AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e34;
                 
                  if (n34 && (e34 = n34->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e34->STORE_S_STATE;
                      long v34 = e34->__av;
                      AGG2STORE1_P_2ITEM1.addOrDelOnZero(se59.modify(store_s_state,store_sales_ss_item_sk),(v33 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se60.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se61.modify(store_sales_ss_sold_date_sk)) * v34))));
                      n34 = n34->nxt;
                    } while (n34 && (e34 = n34->obj) && h15 == n34->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se62, *e34)); 
                  }
                }
              n33 = n33->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123* i35 = static_cast<HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123*>(AGG2ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n35; 
          AGG2ITEM4STORE_SALES1_DELTA_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                long store_sales_ss_sold_date_sk = e35->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e35->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e35->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e35->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v35 = e35->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i36 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h16 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se66.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n36 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i36->slice(se66, h16));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e36;
                 
                  if (n36 && (e36 = n36->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e36->ITEM_I_ITEM_ID;
                      long v36 = e36->__av;
                      AGG2STORE4.addOrDelOnZero(se63.modify(store_sales_ss_store_sk,item_i_item_id),(v35 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se64.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se65.modify(store_sales_ss_sold_date_sk)) * v36))));
                      n36 = n36->nxt;
                    } while (n36 && (e36 = n36->obj) && h16 == n36->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se66, *e36)); 
                  }
                }
              n35 = n35->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123* i37 = static_cast<HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123*>(AGG2ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n37; 
          AGG2ITEM4STORE_SALES1_DELTA_entry* e37;
        
          for (size_t i = 0; i < i37->size_; i++)
          {
            n37 = i37->buckets_ + i;
            while (n37 && (e37 = n37->obj))
            {
                long store_sales_ss_sold_date_sk = e37->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e37->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e37->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e37->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v37 = e37->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i38 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h18 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se71.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n38 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i38->slice(se71, h18));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e38;
                 
                  if (n38 && (e38 = n38->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e38->ITEM_I_ITEM_ID;
                      long v38 = e38->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i39 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h17 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se70.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n39 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i39->slice(se70, h17));
                        AGG1ITEM4STORE_SALES1_P_3_entry* e39;
                       
                        if (n39 && (e39 = n39->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e39->STORE_S_STATE;
                            long v39 = e39->__av;
                            AGG2STORE_SALES1.addOrDelOnZero(se67.modify(store_s_state,item_i_item_id),(v37 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se68.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se69.modify(store_sales_ss_cdemo_sk)) * (v38 * v39)))));
                            n39 = n39->nxt;
                          } while (n39 && (e39 = n39->obj) && h17 == n39->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se70, *e39)); 
                        }
                      }
                      n38 = n38->nxt;
                    } while (n38 && (e38 = n38->obj) && h18 == n38->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se71, *e38)); 
                  }
                }
              n37 = n37->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123* i40 = static_cast<HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123*>(AGG3ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n40; 
          AGG3ITEM4STORE_SALES1_DELTA_entry* e40;
        
          for (size_t i = 0; i < i40->size_; i++)
          {
            n40 = i40->buckets_ + i;
            while (n40 && (e40 = n40->obj))
            {
                long store_sales_ss_sold_date_sk = e40->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e40->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e40->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e40->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v40 = e40->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i41 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h19 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se75.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n41 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i41->slice(se75, h19));
                  AGG1ITEM4STORE_SALES1_P_3_entry* e41;
                 
                  if (n41 && (e41 = n41->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e41->STORE_S_STATE;
                      long v41 = e41->__av;
                      AGG3ITEM4.addOrDelOnZero(se72.modify(store_sales_ss_item_sk,store_s_state),(v40 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se73.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se74.modify(store_sales_ss_cdemo_sk)) * v41))));
                      n41 = n41->nxt;
                    } while (n41 && (e41 = n41->obj) && h19 == n41->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se75, *e41)); 
                  }
                }
              n40 = n40->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123* i42 = static_cast<HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123*>(AGG3ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n42; 
          AGG3ITEM4STORE_SALES1_DELTA_entry* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
                long store_sales_ss_sold_date_sk = e42->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e42->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e42->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e42->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v42 = e42->__av;
                AGG3ITEM4STORE1.addOrDelOnZero(se76.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(v42 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se77.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se78.modify(store_sales_ss_sold_date_sk)))));
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123* i43 = static_cast<HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123*>(AGG3ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n43; 
          AGG3ITEM4STORE_SALES1_DELTA_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long store_sales_ss_sold_date_sk = e43->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e43->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e43->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e43->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v43 = e43->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i44 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h21 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se83.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n44 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i44->slice(se83, h21));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e44->ITEM_I_ITEM_ID;
                      long v44 = e44->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i45 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h20 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se82.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n45 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i45->slice(se82, h20));
                        AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e45;
                       
                        if (n45 && (e45 = n45->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e45->STORE_S_STATE;
                            long v45 = e45->__av;
                            AGG3STORE1_P_2.addOrDelOnZero(se79.modify(store_s_state,item_i_item_id),(v43 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se80.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se81.modify(store_sales_ss_sold_date_sk)) * (v44 * v45)))));
                            n45 = n45->nxt;
                          } while (n45 && (e45 = n45->obj) && h20 == n45->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se82, *e45)); 
                        }
                      }
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h21 == n44->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se83, *e44)); 
                  }
                }
              n43 = n43->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123* i46 = static_cast<HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123*>(AGG3ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n46; 
          AGG3ITEM4STORE_SALES1_DELTA_entry* e46;
        
          for (size_t i = 0; i < i46->size_; i++)
          {
            n46 = i46->buckets_ + i;
            while (n46 && (e46 = n46->obj))
            {
                long store_sales_ss_sold_date_sk = e46->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e46->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e46->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e46->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v46 = e46->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i47 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h22 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se87.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n47 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i47->slice(se87, h22));
                  AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e47;
                 
                  if (n47 && (e47 = n47->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e47->STORE_S_STATE;
                      long v47 = e47->__av;
                      AGG3STORE1_P_2ITEM1.addOrDelOnZero(se84.modify(store_s_state,store_sales_ss_item_sk),(v46 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se85.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se86.modify(store_sales_ss_sold_date_sk)) * v47))));
                      n47 = n47->nxt;
                    } while (n47 && (e47 = n47->obj) && h22 == n47->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se87, *e47)); 
                  }
                }
              n46 = n46->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123* i48 = static_cast<HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123*>(AGG3ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n48; 
          AGG3ITEM4STORE_SALES1_DELTA_entry* e48;
        
          for (size_t i = 0; i < i48->size_; i++)
          {
            n48 = i48->buckets_ + i;
            while (n48 && (e48 = n48->obj))
            {
                long store_sales_ss_sold_date_sk = e48->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e48->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e48->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e48->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v48 = e48->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i49 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h23 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se91.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n49 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i49->slice(se91, h23));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e49;
                 
                  if (n49 && (e49 = n49->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e49->ITEM_I_ITEM_ID;
                      long v49 = e49->__av;
                      AGG3STORE4.addOrDelOnZero(se88.modify(store_sales_ss_store_sk,item_i_item_id),(v48 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se89.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se90.modify(store_sales_ss_sold_date_sk)) * v49))));
                      n49 = n49->nxt;
                    } while (n49 && (e49 = n49->obj) && h23 == n49->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se91, *e49)); 
                  }
                }
              n48 = n48->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123* i50 = static_cast<HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123*>(AGG3ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n50; 
          AGG3ITEM4STORE_SALES1_DELTA_entry* e50;
        
          for (size_t i = 0; i < i50->size_; i++)
          {
            n50 = i50->buckets_ + i;
            while (n50 && (e50 = n50->obj))
            {
                long store_sales_ss_sold_date_sk = e50->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e50->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e50->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e50->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v50 = e50->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i51 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h25 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se96.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n51 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i51->slice(se96, h25));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e51;
                 
                  if (n51 && (e51 = n51->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e51->ITEM_I_ITEM_ID;
                      long v51 = e51->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i52 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h24 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se95.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n52 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i52->slice(se95, h24));
                        AGG1ITEM4STORE_SALES1_P_3_entry* e52;
                       
                        if (n52 && (e52 = n52->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e52->STORE_S_STATE;
                            long v52 = e52->__av;
                            AGG3STORE_SALES1.addOrDelOnZero(se92.modify(store_s_state,item_i_item_id),(v50 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se93.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se94.modify(store_sales_ss_cdemo_sk)) * (v51 * v52)))));
                            n52 = n52->nxt;
                          } while (n52 && (e52 = n52->obj) && h24 == n52->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se95, *e52)); 
                        }
                      }
                      n51 = n51->nxt;
                    } while (n51 && (e51 = n51->obj) && h25 == n51->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se96, *e51)); 
                  }
                }
              n50 = n50->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123* i53 = static_cast<HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123*>(AGG4ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n53; 
          AGG4ITEM4STORE_SALES1_DELTA_entry* e53;
        
          for (size_t i = 0; i < i53->size_; i++)
          {
            n53 = i53->buckets_ + i;
            while (n53 && (e53 = n53->obj))
            {
                long store_sales_ss_sold_date_sk = e53->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e53->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e53->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e53->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v53 = e53->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i54 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h26 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se100.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n54 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i54->slice(se100, h26));
                  AGG1ITEM4STORE_SALES1_P_3_entry* e54;
                 
                  if (n54 && (e54 = n54->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e54->STORE_S_STATE;
                      long v54 = e54->__av;
                      AGG4ITEM4.addOrDelOnZero(se97.modify(store_sales_ss_item_sk,store_s_state),(v53 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se98.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se99.modify(store_sales_ss_cdemo_sk)) * v54))));
                      n54 = n54->nxt;
                    } while (n54 && (e54 = n54->obj) && h26 == n54->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se100, *e54)); 
                  }
                }
              n53 = n53->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123* i55 = static_cast<HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123*>(AGG4ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n55; 
          AGG4ITEM4STORE_SALES1_DELTA_entry* e55;
        
          for (size_t i = 0; i < i55->size_; i++)
          {
            n55 = i55->buckets_ + i;
            while (n55 && (e55 = n55->obj))
            {
                long store_sales_ss_sold_date_sk = e55->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e55->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e55->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e55->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v55 = e55->__av;
                AGG4ITEM4STORE1.addOrDelOnZero(se101.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(v55 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se102.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se103.modify(store_sales_ss_sold_date_sk)))));
              n55 = n55->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123* i56 = static_cast<HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123*>(AGG4ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n56; 
          AGG4ITEM4STORE_SALES1_DELTA_entry* e56;
        
          for (size_t i = 0; i < i56->size_; i++)
          {
            n56 = i56->buckets_ + i;
            while (n56 && (e56 = n56->obj))
            {
                long store_sales_ss_sold_date_sk = e56->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e56->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e56->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e56->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v56 = e56->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i57 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h28 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se108.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n57 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i57->slice(se108, h28));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e57;
                 
                  if (n57 && (e57 = n57->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e57->ITEM_I_ITEM_ID;
                      long v57 = e57->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i58 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h27 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se107.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n58 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i58->slice(se107, h27));
                        AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e58;
                       
                        if (n58 && (e58 = n58->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e58->STORE_S_STATE;
                            long v58 = e58->__av;
                            AGG4STORE1_P_2.addOrDelOnZero(se104.modify(store_s_state,item_i_item_id),(v56 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se105.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se106.modify(store_sales_ss_sold_date_sk)) * (v57 * v58)))));
                            n58 = n58->nxt;
                          } while (n58 && (e58 = n58->obj) && h27 == n58->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se107, *e58)); 
                        }
                      }
                      n57 = n57->nxt;
                    } while (n57 && (e57 = n57->obj) && h28 == n57->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se108, *e57)); 
                  }
                }
              n56 = n56->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123* i59 = static_cast<HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123*>(AGG4ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n59; 
          AGG4ITEM4STORE_SALES1_DELTA_entry* e59;
        
          for (size_t i = 0; i < i59->size_; i++)
          {
            n59 = i59->buckets_ + i;
            while (n59 && (e59 = n59->obj))
            {
                long store_sales_ss_sold_date_sk = e59->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e59->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e59->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e59->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v59 = e59->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0* i60 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0*>(AGG1ITEM1_L1_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h29 = AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se112.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode* n60 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES1_P_3_map_0::IdxNode*>(i60->slice(se112, h29));
                  AGG1ITEM1_L1_2STORE_SALES1_P_3_entry* e60;
                 
                  if (n60 && (e60 = n60->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e60->STORE_S_STATE;
                      long v60 = e60->__av;
                      AGG4STORE1_P_2ITEM1.addOrDelOnZero(se109.modify(store_s_state,store_sales_ss_item_sk),(v59 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se110.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se111.modify(store_sales_ss_sold_date_sk)) * v60))));
                      n60 = n60->nxt;
                    } while (n60 && (e60 = n60->obj) && h29 == n60->hash &&  AGG1ITEM1_L1_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se112, *e60)); 
                  }
                }
              n59 = n59->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123* i61 = static_cast<HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123*>(AGG4ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n61; 
          AGG4ITEM4STORE_SALES1_DELTA_entry* e61;
        
          for (size_t i = 0; i < i61->size_; i++)
          {
            n61 = i61->buckets_ + i;
            while (n61 && (e61 = n61->obj))
            {
                long store_sales_ss_sold_date_sk = e61->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e61->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e61->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e61->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v61 = e61->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i62 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h30 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se116.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n62 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i62->slice(se116, h30));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e62;
                 
                  if (n62 && (e62 = n62->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e62->ITEM_I_ITEM_ID;
                      long v62 = e62->__av;
                      AGG4STORE4.addOrDelOnZero(se113.modify(store_sales_ss_store_sk,item_i_item_id),(v61 * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se114.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se115.modify(store_sales_ss_sold_date_sk)) * v62))));
                      n62 = n62->nxt;
                    } while (n62 && (e62 = n62->obj) && h30 == n62->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se116, *e62)); 
                  }
                }
              n61 = n61->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123* i63 = static_cast<HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123*>(AGG4ITEM4STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM4STORE_SALES1_DELTA_map_0123::IdxNode* n63; 
          AGG4ITEM4STORE_SALES1_DELTA_entry* e63;
        
          for (size_t i = 0; i < i63->size_; i++)
          {
            n63 = i63->buckets_ + i;
            while (n63 && (e63 = n63->obj))
            {
                long store_sales_ss_sold_date_sk = e63->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e63->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e63->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_store_sk = e63->STORE_SALES_SS_STORE_SK;
                DOUBLE_TYPE v63 = e63->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0* i64 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0*>(AGG1STORE1_P_2STORE_SALES1_P_3.index[1]);
                  const HASH_RES_t h32 = AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::hash(se121.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode* n64 = static_cast<HashIndex_AGG1STORE1_P_2STORE_SALES1_P_3_map_0::IdxNode*>(i64->slice(se121, h32));
                  AGG1STORE1_P_2STORE_SALES1_P_3_entry* e64;
                 
                  if (n64 && (e64 = n64->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e64->ITEM_I_ITEM_ID;
                      long v64 = e64->__av;
                      { //slice 
                        const HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0* i65 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0*>(AGG1ITEM4STORE_SALES1_P_3.index[1]);
                        const HASH_RES_t h31 = AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::hash(se120.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode* n65 = static_cast<HashIndex_AGG1ITEM4STORE_SALES1_P_3_map_0::IdxNode*>(i65->slice(se120, h31));
                        AGG1ITEM4STORE_SALES1_P_3_entry* e65;
                       
                        if (n65 && (e65 = n65->obj)) {
                          do {                
                            STRING_TYPE store_s_state = e65->STORE_S_STATE;
                            long v65 = e65->__av;
                            AGG4STORE_SALES1.addOrDelOnZero(se117.modify(store_s_state,item_i_item_id),(v63 * (AGG1ITEM1_L1_2STORE_SALES1_P_1.getValueOrDefault(se118.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1_P_2.getValueOrDefault(se119.modify(store_sales_ss_cdemo_sk)) * (v64 * v65)))));
                            n65 = n65->nxt;
                          } while (n65 && (e65 = n65->obj) && h31 == n65->hash &&  AGG1ITEM4STORE_SALES1_P_3_mapkey0_idxfn::equals(se120, *e65)); 
                        }
                      }
                      n64 = n64->nxt;
                    } while (n64 && (e64 = n64->obj) && h32 == n64->hash &&  AGG1STORE1_P_2STORE_SALES1_P_3_mapkey0_idxfn::equals(se121, *e64)); 
                  }
                }
              n63 = n63->nxt;
            }
          }
        }AGG1.clear();
        {  // foreach
          const HashIndex_AGG1STORE_SALES1_map_01* i66 = static_cast<HashIndex_AGG1STORE_SALES1_map_01*>(AGG1STORE_SALES1.index[0]);
          HashIndex_AGG1STORE_SALES1_map_01::IdxNode* n66; 
          AGG1STORE_SALES1_entry* e66;
        
          for (size_t i = 0; i < i66->size_; i++)
          {
            n66 = i66->buckets_ + i;
            while (n66 && (e66 = n66->obj))
            {
                STRING_TYPE store_s_state = e66->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e66->ITEM_I_ITEM_ID;
                long v66 = e66->__av;
                DOUBLE_TYPE agg1 = 0.0;
                long l1 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se123.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l1) ? agg1 += Udiv(Ulistmax(1L, l1)) : 0.0);
                AGG1.addOrDelOnZero(se122.modify(item_i_item_id,store_s_state),(v66 * agg1));
              n66 = n66->nxt;
            }
          }
        }AGG2.clear();
        {  // foreach
          const HashIndex_AGG2STORE_SALES1_map_01* i67 = static_cast<HashIndex_AGG2STORE_SALES1_map_01*>(AGG2STORE_SALES1.index[0]);
          HashIndex_AGG2STORE_SALES1_map_01::IdxNode* n67; 
          AGG2STORE_SALES1_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                STRING_TYPE store_s_state = e67->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e67->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v67 = e67->__av;
                DOUBLE_TYPE agg2 = 0.0;
                long l2 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se125.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l2) ? agg2 += Udiv(Ulistmax(1L, l2)) : 0.0);
                AGG2.addOrDelOnZero(se124.modify(item_i_item_id,store_s_state),(v67 * agg2));
              n67 = n67->nxt;
            }
          }
        }AGG3.clear();
        {  // foreach
          const HashIndex_AGG3STORE_SALES1_map_01* i68 = static_cast<HashIndex_AGG3STORE_SALES1_map_01*>(AGG3STORE_SALES1.index[0]);
          HashIndex_AGG3STORE_SALES1_map_01::IdxNode* n68; 
          AGG3STORE_SALES1_entry* e68;
        
          for (size_t i = 0; i < i68->size_; i++)
          {
            n68 = i68->buckets_ + i;
            while (n68 && (e68 = n68->obj))
            {
                STRING_TYPE store_s_state = e68->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e68->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v68 = e68->__av;
                DOUBLE_TYPE agg3 = 0.0;
                long l3 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se127.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l3) ? agg3 += Udiv(Ulistmax(1L, l3)) : 0.0);
                AGG3.addOrDelOnZero(se126.modify(item_i_item_id,store_s_state),(v68 * agg3));
              n68 = n68->nxt;
            }
          }
        }AGG4.clear();
        {  // foreach
          const HashIndex_AGG4STORE_SALES1_map_01* i69 = static_cast<HashIndex_AGG4STORE_SALES1_map_01*>(AGG4STORE_SALES1.index[0]);
          HashIndex_AGG4STORE_SALES1_map_01::IdxNode* n69; 
          AGG4STORE_SALES1_entry* e69;
        
          for (size_t i = 0; i < i69->size_; i++)
          {
            n69 = i69->buckets_ + i;
            while (n69 && (e69 = n69->obj))
            {
                STRING_TYPE store_s_state = e69->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e69->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v69 = e69->__av;
                DOUBLE_TYPE agg4 = 0.0;
                long l4 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se129.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l4) ? agg4 += Udiv(Ulistmax(1L, l4)) : 0.0);
                AGG4.addOrDelOnZero(se128.modify(item_i_item_id,store_s_state),(v69 * agg4));
              n69 = n69->nxt;
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

        AGG1ITEM1_L1_2_DELTA.clear();
        AGG1ITEM1_DOMAIN1.clear();
        {  
          for (size_t i = 0; i < DELTA_ITEM.size; i++) 
          {
                long store_sales_ss_item_sk = DELTA_ITEM.i_item_sk[i];
                STRING_TYPE item_i_item_id = DELTA_ITEM.i_item_id[i];
                // date item_i_rec_start_date = DELTA_ITEM.i_rec_start_date[i];
                // date item_i_rec_end_date = DELTA_ITEM.i_rec_end_date[i];
                // STRING_TYPE item_i_item_desc = DELTA_ITEM.i_item_desc[i];
                // DOUBLE_TYPE item_i_current_price = DELTA_ITEM.i_current_price[i];
                // DOUBLE_TYPE item_i_wholesale_cost = DELTA_ITEM.i_wholesale_cost[i];
                // long item_i_brand_id = DELTA_ITEM.i_brand_id[i];
                // STRING_TYPE item_i_brand = DELTA_ITEM.i_brand[i];
                // long item_i_class_id = DELTA_ITEM.i_class_id[i];
                // STRING_TYPE item_i_class = DELTA_ITEM.i_class[i];
                // long item_i_category_id = DELTA_ITEM.i_category_id[i];
                // STRING_TYPE item_i_category = DELTA_ITEM.i_category[i];
                // long item_i_manufact_id = DELTA_ITEM.i_manufact_id[i];
                // STRING_TYPE item_i_manufact = DELTA_ITEM.i_manufact[i];
                // STRING_TYPE item_i_size = DELTA_ITEM.i_size[i];
                // STRING_TYPE item_i_formulation = DELTA_ITEM.i_formulation[i];
                // STRING_TYPE item_i_color = DELTA_ITEM.i_color[i];
                // STRING_TYPE item_i_units = DELTA_ITEM.i_units[i];
                // STRING_TYPE item_i_container = DELTA_ITEM.i_container[i];
                // long item_i_manager_id = DELTA_ITEM.i_manager_id[i];
                // STRING_TYPE item_i_product_name = DELTA_ITEM.i_product_name[i];
                long v70 = 1L;
                AGG1ITEM1_L1_2_DELTA.addOrDelOnZero(se130.modify(store_sales_ss_item_sk,item_i_item_id),v70);
                long v71 = 1L;
                AGG1ITEM1_DOMAIN1.addOrDelOnZero(se131.modify(item_i_item_id),(v71 != 0 ? 1L : 0L));
          }
        }

        {  // foreach
          const HashIndex_AGG1ITEM1_DOMAIN1_map_0* i72 = static_cast<HashIndex_AGG1ITEM1_DOMAIN1_map_0*>(AGG1ITEM1_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM1_DOMAIN1_map_0::IdxNode* n72; 
          AGG1ITEM1_DOMAIN1_entry* e72;
        
          for (size_t i = 0; i < i72->size_; i++)
          {
            n72 = i72->buckets_ + i;
            while (n72 && (e72 = n72->obj))
            {
                STRING_TYPE item_i_item_id = e72->ITEM_I_ITEM_ID;
                long v72 = e72->__av;
                { //slice 
                  const HashIndex_AGG1STORE_SALES1_map_1* i73 = static_cast<HashIndex_AGG1STORE_SALES1_map_1*>(AGG1STORE_SALES1.index[1]);
                  const HASH_RES_t h34 = AGG1STORE_SALES1_mapkey1_idxfn::hash(se137.modify1(item_i_item_id));
                  HashIndex_AGG1STORE_SALES1_map_1::IdxNode* n73 = static_cast<HashIndex_AGG1STORE_SALES1_map_1::IdxNode*>(i73->slice(se137, h34));
                  AGG1STORE_SALES1_entry* e73;
                 
                  if (n73 && (e73 = n73->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e73->STORE_S_STATE;
                      long v73 = e73->__av;
                      DOUBLE_TYPE agg5 = 0.0;
                      long agg6 = 0L;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2_DELTA_map_1* i74 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1*>(AGG1ITEM1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h33 = AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::hash(se135.modify1(item_i_item_id));
                        HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode* n74 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode*>(i74->slice(se135, h33));
                        AGG1ITEM1_L1_2_DELTA_entry* e74;
                       
                        if (n74 && (e74 = n74->obj)) {
                          do {                
                            long store_sales_ss_item_sk = e74->STORE_SALES_SS_ITEM_SK;
                            long v74 = e74->__av;
                            agg6 += (v74 * AGG1ITEM1_L1_2.getValueOrDefault(se134.modify(store_s_state,store_sales_ss_item_sk)));
                            n74 = n74->nxt;
                          } while (n74 && (e74 = n74->obj) && h33 == n74->hash &&  AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::equals(se135, *e74)); 
                        }
                      }long l5 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se133.modify(item_i_item_id,store_s_state)) + agg6);
                      (/*if */(0L != l5) ? agg5 += Udiv(Ulistmax(1L, l5)) : 0.0);
                      DOUBLE_TYPE agg7 = 0.0;
                      long l6 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se136.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l6) ? agg7 += Udiv(Ulistmax(1L, l6)) : 0.0);
                      AGG1.addOrDelOnZero(se132.modify(item_i_item_id,store_s_state),((v72 != 0 ? 1L : 0L) * (v73 * (agg5 + (agg7 * -1L)))));
                      n73 = n73->nxt;
                    } while (n73 && (e73 = n73->obj) && h34 == n73->hash &&  AGG1STORE_SALES1_mapkey1_idxfn::equals(se137, *e73)); 
                  }
                }
              n72 = n72->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i75 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n75; 
          AGG1ITEM1_L1_2_DELTA_entry* e75;
        
          for (size_t i = 0; i < i75->size_; i++)
          {
            n75 = i75->buckets_ + i;
            while (n75 && (e75 = n75->obj))
            {
                long store_sales_ss_item_sk = e75->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e75->ITEM_I_ITEM_ID;
                long v75 = e75->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4_map_0* i76 = static_cast<HashIndex_AGG1ITEM4_map_0*>(AGG1ITEM4.index[1]);
                  const HASH_RES_t h35 = AGG1ITEM4_mapkey0_idxfn::hash(se141.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1ITEM4_map_0::IdxNode* n76 = static_cast<HashIndex_AGG1ITEM4_map_0::IdxNode*>(i76->slice(se141, h35));
                  AGG1ITEM4_entry* e76;
                 
                  if (n76 && (e76 = n76->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e76->STORE_S_STATE;
                      long v76 = e76->__av;
                      long agg8 = 0L;
                      agg8 += (AGG1ITEM1_L1_2_DELTA.getValueOrDefault(se139.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM1_L1_2.getValueOrDefault(se140.modify(store_s_state,store_sales_ss_item_sk)));
                      long l7 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se138.modify(item_i_item_id,store_s_state)) + agg8);
                      (/*if */(0L != l7) ? AGG1.addOrDelOnZero(se132.modify(item_i_item_id,store_s_state),(v75 * (v76 * Udiv(Ulistmax(1L, l7))))) : (void)0);
                      n76 = n76->nxt;
                    } while (n76 && (e76 = n76->obj) && h35 == n76->hash &&  AGG1ITEM4_mapkey0_idxfn::equals(se141, *e76)); 
                  }
                }
              n75 = n75->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i77 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n77; 
          AGG1ITEM1_L1_2_DELTA_entry* e77;
        
          for (size_t i = 0; i < i77->size_; i++)
          {
            n77 = i77->buckets_ + i;
            while (n77 && (e77 = n77->obj))
            {
                long store_sales_ss_item_sk = e77->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e77->ITEM_I_ITEM_ID;
                long v77 = e77->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_P_2ITEM1_map_1* i78 = static_cast<HashIndex_AGG1STORE1_P_2ITEM1_map_1*>(AGG1STORE1_P_2ITEM1.index[1]);
                  const HASH_RES_t h36 = AGG1STORE1_P_2ITEM1_mapkey1_idxfn::hash(se143.modify1(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE1_P_2ITEM1_map_1::IdxNode* n78 = static_cast<HashIndex_AGG1STORE1_P_2ITEM1_map_1::IdxNode*>(i78->slice(se143, h36));
                  AGG1STORE1_P_2ITEM1_entry* e78;
                 
                  if (n78 && (e78 = n78->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e78->STORE_S_STATE;
                      long v78 = e78->__av;
                      AGG1STORE1_P_2.addOrDelOnZero(se142.modify(store_s_state,item_i_item_id),(v77 * v78));
                      n78 = n78->nxt;
                    } while (n78 && (e78 = n78->obj) && h36 == n78->hash &&  AGG1STORE1_P_2ITEM1_mapkey1_idxfn::equals(se143, *e78)); 
                  }
                }
              n77 = n77->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i79 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n79; 
          AGG1ITEM1_L1_2_DELTA_entry* e79;
        
          for (size_t i = 0; i < i79->size_; i++)
          {
            n79 = i79->buckets_ + i;
            while (n79 && (e79 = n79->obj))
            {
                long store_sales_ss_item_sk = e79->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e79->ITEM_I_ITEM_ID;
                long v79 = e79->__av;
                AGG1STORE1_P_2STORE_SALES1_P_3.addOrDelOnZero(se144.modify(store_sales_ss_item_sk,item_i_item_id),v79);
              n79 = n79->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i80 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n80; 
          AGG1ITEM1_L1_2_DELTA_entry* e80;
        
          for (size_t i = 0; i < i80->size_; i++)
          {
            n80 = i80->buckets_ + i;
            while (n80 && (e80 = n80->obj))
            {
                long store_sales_ss_item_sk = e80->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e80->ITEM_I_ITEM_ID;
                long v80 = e80->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE1_map_0* i81 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_0*>(AGG1ITEM1_L1_2STORE1.index[1]);
                  const HASH_RES_t h37 = AGG1ITEM1_L1_2STORE1_mapkey0_idxfn::hash(se146.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE1_map_0::IdxNode* n81 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_0::IdxNode*>(i81->slice(se146, h37));
                  AGG1ITEM1_L1_2STORE1_entry* e81;
                 
                  if (n81 && (e81 = n81->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e81->STORE_SALES_SS_STORE_SK;
                      long v81 = e81->__av;
                      AGG1STORE1_L1_2.addOrDelOnZero(se145.modify(item_i_item_id,store_sales_ss_store_sk),(v80 * v81));
                      n81 = n81->nxt;
                    } while (n81 && (e81 = n81->obj) && h37 == n81->hash &&  AGG1ITEM1_L1_2STORE1_mapkey0_idxfn::equals(se146, *e81)); 
                  }
                }
              n80 = n80->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i82 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n82; 
          AGG1ITEM1_L1_2_DELTA_entry* e82;
        
          for (size_t i = 0; i < i82->size_; i++)
          {
            n82 = i82->buckets_ + i;
            while (n82 && (e82 = n82->obj))
            {
                long store_sales_ss_item_sk = e82->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e82->ITEM_I_ITEM_ID;
                long v82 = e82->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4STORE1_map_0* i83 = static_cast<HashIndex_AGG1ITEM4STORE1_map_0*>(AGG1ITEM4STORE1.index[1]);
                  const HASH_RES_t h38 = AGG1ITEM4STORE1_mapkey0_idxfn::hash(se148.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1ITEM4STORE1_map_0::IdxNode* n83 = static_cast<HashIndex_AGG1ITEM4STORE1_map_0::IdxNode*>(i83->slice(se148, h38));
                  AGG1ITEM4STORE1_entry* e83;
                 
                  if (n83 && (e83 = n83->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e83->STORE_SALES_SS_STORE_SK;
                      long v83 = e83->__av;
                      AGG1STORE4.addOrDelOnZero(se147.modify(store_sales_ss_store_sk,item_i_item_id),(v82 * v83));
                      n83 = n83->nxt;
                    } while (n83 && (e83 = n83->obj) && h38 == n83->hash &&  AGG1ITEM4STORE1_mapkey0_idxfn::equals(se148, *e83)); 
                  }
                }
              n82 = n82->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i84 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n84; 
          AGG1ITEM1_L1_2_DELTA_entry* e84;
        
          for (size_t i = 0; i < i84->size_; i++)
          {
            n84 = i84->buckets_ + i;
            while (n84 && (e84 = n84->obj))
            {
                long store_sales_ss_item_sk = e84->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e84->ITEM_I_ITEM_ID;
                long v84 = e84->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4_map_0* i85 = static_cast<HashIndex_AGG1ITEM4_map_0*>(AGG1ITEM4.index[1]);
                  const HASH_RES_t h39 = AGG1ITEM4_mapkey0_idxfn::hash(se150.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1ITEM4_map_0::IdxNode* n85 = static_cast<HashIndex_AGG1ITEM4_map_0::IdxNode*>(i85->slice(se150, h39));
                  AGG1ITEM4_entry* e85;
                 
                  if (n85 && (e85 = n85->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e85->STORE_S_STATE;
                      long v85 = e85->__av;
                      AGG1STORE_SALES1.addOrDelOnZero(se149.modify(store_s_state,item_i_item_id),(v84 * v85));
                      n85 = n85->nxt;
                    } while (n85 && (e85 = n85->obj) && h39 == n85->hash &&  AGG1ITEM4_mapkey0_idxfn::equals(se150, *e85)); 
                  }
                }
              n84 = n84->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DOMAIN1_map_0* i86 = static_cast<HashIndex_AGG1ITEM1_DOMAIN1_map_0*>(AGG1ITEM1_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM1_DOMAIN1_map_0::IdxNode* n86; 
          AGG1ITEM1_DOMAIN1_entry* e86;
        
          for (size_t i = 0; i < i86->size_; i++)
          {
            n86 = i86->buckets_ + i;
            while (n86 && (e86 = n86->obj))
            {
                STRING_TYPE item_i_item_id = e86->ITEM_I_ITEM_ID;
                long v86 = e86->__av;
                { //slice 
                  const HashIndex_AGG2STORE_SALES1_map_1* i87 = static_cast<HashIndex_AGG2STORE_SALES1_map_1*>(AGG2STORE_SALES1.index[1]);
                  const HASH_RES_t h41 = AGG2STORE_SALES1_mapkey1_idxfn::hash(se156.modify1(item_i_item_id));
                  HashIndex_AGG2STORE_SALES1_map_1::IdxNode* n87 = static_cast<HashIndex_AGG2STORE_SALES1_map_1::IdxNode*>(i87->slice(se156, h41));
                  AGG2STORE_SALES1_entry* e87;
                 
                  if (n87 && (e87 = n87->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e87->STORE_S_STATE;
                      DOUBLE_TYPE v87 = e87->__av;
                      DOUBLE_TYPE agg9 = 0.0;
                      long agg10 = 0L;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2_DELTA_map_1* i88 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1*>(AGG1ITEM1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h40 = AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::hash(se154.modify1(item_i_item_id));
                        HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode* n88 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode*>(i88->slice(se154, h40));
                        AGG1ITEM1_L1_2_DELTA_entry* e88;
                       
                        if (n88 && (e88 = n88->obj)) {
                          do {                
                            long store_sales_ss_item_sk = e88->STORE_SALES_SS_ITEM_SK;
                            long v88 = e88->__av;
                            agg10 += (v88 * AGG1ITEM1_L1_2.getValueOrDefault(se153.modify(store_s_state,store_sales_ss_item_sk)));
                            n88 = n88->nxt;
                          } while (n88 && (e88 = n88->obj) && h40 == n88->hash &&  AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::equals(se154, *e88)); 
                        }
                      }long l8 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se152.modify(item_i_item_id,store_s_state)) + agg10);
                      (/*if */(0L != l8) ? agg9 += Udiv(Ulistmax(1L, l8)) : 0.0);
                      DOUBLE_TYPE agg11 = 0.0;
                      long l9 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se155.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l9) ? agg11 += Udiv(Ulistmax(1L, l9)) : 0.0);
                      AGG2.addOrDelOnZero(se151.modify(item_i_item_id,store_s_state),((v86 != 0 ? 1L : 0L) * (v87 * (agg9 + (agg11 * -1L)))));
                      n87 = n87->nxt;
                    } while (n87 && (e87 = n87->obj) && h41 == n87->hash &&  AGG2STORE_SALES1_mapkey1_idxfn::equals(se156, *e87)); 
                  }
                }
              n86 = n86->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i89 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n89; 
          AGG1ITEM1_L1_2_DELTA_entry* e89;
        
          for (size_t i = 0; i < i89->size_; i++)
          {
            n89 = i89->buckets_ + i;
            while (n89 && (e89 = n89->obj))
            {
                long store_sales_ss_item_sk = e89->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e89->ITEM_I_ITEM_ID;
                long v89 = e89->__av;
                { //slice 
                  const HashIndex_AGG2ITEM4_map_0* i90 = static_cast<HashIndex_AGG2ITEM4_map_0*>(AGG2ITEM4.index[1]);
                  const HASH_RES_t h42 = AGG2ITEM4_mapkey0_idxfn::hash(se160.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG2ITEM4_map_0::IdxNode* n90 = static_cast<HashIndex_AGG2ITEM4_map_0::IdxNode*>(i90->slice(se160, h42));
                  AGG2ITEM4_entry* e90;
                 
                  if (n90 && (e90 = n90->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e90->STORE_S_STATE;
                      DOUBLE_TYPE v90 = e90->__av;
                      long agg12 = 0L;
                      agg12 += (AGG1ITEM1_L1_2_DELTA.getValueOrDefault(se158.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM1_L1_2.getValueOrDefault(se159.modify(store_s_state,store_sales_ss_item_sk)));
                      long l10 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se157.modify(item_i_item_id,store_s_state)) + agg12);
                      (/*if */(0L != l10) ? AGG2.addOrDelOnZero(se151.modify(item_i_item_id,store_s_state),(v89 * (v90 * Udiv(Ulistmax(1L, l10))))) : (void)0);
                      n90 = n90->nxt;
                    } while (n90 && (e90 = n90->obj) && h42 == n90->hash &&  AGG2ITEM4_mapkey0_idxfn::equals(se160, *e90)); 
                  }
                }
              n89 = n89->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i91 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n91; 
          AGG1ITEM1_L1_2_DELTA_entry* e91;
        
          for (size_t i = 0; i < i91->size_; i++)
          {
            n91 = i91->buckets_ + i;
            while (n91 && (e91 = n91->obj))
            {
                long store_sales_ss_item_sk = e91->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e91->ITEM_I_ITEM_ID;
                long v91 = e91->__av;
                { //slice 
                  const HashIndex_AGG2STORE1_P_2ITEM1_map_1* i92 = static_cast<HashIndex_AGG2STORE1_P_2ITEM1_map_1*>(AGG2STORE1_P_2ITEM1.index[1]);
                  const HASH_RES_t h43 = AGG2STORE1_P_2ITEM1_mapkey1_idxfn::hash(se162.modify1(store_sales_ss_item_sk));
                  HashIndex_AGG2STORE1_P_2ITEM1_map_1::IdxNode* n92 = static_cast<HashIndex_AGG2STORE1_P_2ITEM1_map_1::IdxNode*>(i92->slice(se162, h43));
                  AGG2STORE1_P_2ITEM1_entry* e92;
                 
                  if (n92 && (e92 = n92->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e92->STORE_S_STATE;
                      DOUBLE_TYPE v92 = e92->__av;
                      AGG2STORE1_P_2.addOrDelOnZero(se161.modify(store_s_state,item_i_item_id),(v91 * v92));
                      n92 = n92->nxt;
                    } while (n92 && (e92 = n92->obj) && h43 == n92->hash &&  AGG2STORE1_P_2ITEM1_mapkey1_idxfn::equals(se162, *e92)); 
                  }
                }
              n91 = n91->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i93 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n93; 
          AGG1ITEM1_L1_2_DELTA_entry* e93;
        
          for (size_t i = 0; i < i93->size_; i++)
          {
            n93 = i93->buckets_ + i;
            while (n93 && (e93 = n93->obj))
            {
                long store_sales_ss_item_sk = e93->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e93->ITEM_I_ITEM_ID;
                long v93 = e93->__av;
                { //slice 
                  const HashIndex_AGG2ITEM4STORE1_map_0* i94 = static_cast<HashIndex_AGG2ITEM4STORE1_map_0*>(AGG2ITEM4STORE1.index[1]);
                  const HASH_RES_t h44 = AGG2ITEM4STORE1_mapkey0_idxfn::hash(se164.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG2ITEM4STORE1_map_0::IdxNode* n94 = static_cast<HashIndex_AGG2ITEM4STORE1_map_0::IdxNode*>(i94->slice(se164, h44));
                  AGG2ITEM4STORE1_entry* e94;
                 
                  if (n94 && (e94 = n94->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e94->STORE_SALES_SS_STORE_SK;
                      DOUBLE_TYPE v94 = e94->__av;
                      AGG2STORE4.addOrDelOnZero(se163.modify(store_sales_ss_store_sk,item_i_item_id),(v93 * v94));
                      n94 = n94->nxt;
                    } while (n94 && (e94 = n94->obj) && h44 == n94->hash &&  AGG2ITEM4STORE1_mapkey0_idxfn::equals(se164, *e94)); 
                  }
                }
              n93 = n93->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i95 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n95; 
          AGG1ITEM1_L1_2_DELTA_entry* e95;
        
          for (size_t i = 0; i < i95->size_; i++)
          {
            n95 = i95->buckets_ + i;
            while (n95 && (e95 = n95->obj))
            {
                long store_sales_ss_item_sk = e95->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e95->ITEM_I_ITEM_ID;
                long v95 = e95->__av;
                { //slice 
                  const HashIndex_AGG2ITEM4_map_0* i96 = static_cast<HashIndex_AGG2ITEM4_map_0*>(AGG2ITEM4.index[1]);
                  const HASH_RES_t h45 = AGG2ITEM4_mapkey0_idxfn::hash(se166.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG2ITEM4_map_0::IdxNode* n96 = static_cast<HashIndex_AGG2ITEM4_map_0::IdxNode*>(i96->slice(se166, h45));
                  AGG2ITEM4_entry* e96;
                 
                  if (n96 && (e96 = n96->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e96->STORE_S_STATE;
                      DOUBLE_TYPE v96 = e96->__av;
                      AGG2STORE_SALES1.addOrDelOnZero(se165.modify(store_s_state,item_i_item_id),(v95 * v96));
                      n96 = n96->nxt;
                    } while (n96 && (e96 = n96->obj) && h45 == n96->hash &&  AGG2ITEM4_mapkey0_idxfn::equals(se166, *e96)); 
                  }
                }
              n95 = n95->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DOMAIN1_map_0* i97 = static_cast<HashIndex_AGG1ITEM1_DOMAIN1_map_0*>(AGG1ITEM1_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM1_DOMAIN1_map_0::IdxNode* n97; 
          AGG1ITEM1_DOMAIN1_entry* e97;
        
          for (size_t i = 0; i < i97->size_; i++)
          {
            n97 = i97->buckets_ + i;
            while (n97 && (e97 = n97->obj))
            {
                STRING_TYPE item_i_item_id = e97->ITEM_I_ITEM_ID;
                long v97 = e97->__av;
                { //slice 
                  const HashIndex_AGG3STORE_SALES1_map_1* i98 = static_cast<HashIndex_AGG3STORE_SALES1_map_1*>(AGG3STORE_SALES1.index[1]);
                  const HASH_RES_t h47 = AGG3STORE_SALES1_mapkey1_idxfn::hash(se172.modify1(item_i_item_id));
                  HashIndex_AGG3STORE_SALES1_map_1::IdxNode* n98 = static_cast<HashIndex_AGG3STORE_SALES1_map_1::IdxNode*>(i98->slice(se172, h47));
                  AGG3STORE_SALES1_entry* e98;
                 
                  if (n98 && (e98 = n98->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e98->STORE_S_STATE;
                      DOUBLE_TYPE v98 = e98->__av;
                      DOUBLE_TYPE agg13 = 0.0;
                      long agg14 = 0L;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2_DELTA_map_1* i99 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1*>(AGG1ITEM1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h46 = AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::hash(se170.modify1(item_i_item_id));
                        HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode* n99 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode*>(i99->slice(se170, h46));
                        AGG1ITEM1_L1_2_DELTA_entry* e99;
                       
                        if (n99 && (e99 = n99->obj)) {
                          do {                
                            long store_sales_ss_item_sk = e99->STORE_SALES_SS_ITEM_SK;
                            long v99 = e99->__av;
                            agg14 += (v99 * AGG1ITEM1_L1_2.getValueOrDefault(se169.modify(store_s_state,store_sales_ss_item_sk)));
                            n99 = n99->nxt;
                          } while (n99 && (e99 = n99->obj) && h46 == n99->hash &&  AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::equals(se170, *e99)); 
                        }
                      }long l11 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se168.modify(item_i_item_id,store_s_state)) + agg14);
                      (/*if */(0L != l11) ? agg13 += Udiv(Ulistmax(1L, l11)) : 0.0);
                      DOUBLE_TYPE agg15 = 0.0;
                      long l12 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se171.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l12) ? agg15 += Udiv(Ulistmax(1L, l12)) : 0.0);
                      AGG3.addOrDelOnZero(se167.modify(item_i_item_id,store_s_state),((v97 != 0 ? 1L : 0L) * (v98 * (agg13 + (agg15 * -1L)))));
                      n98 = n98->nxt;
                    } while (n98 && (e98 = n98->obj) && h47 == n98->hash &&  AGG3STORE_SALES1_mapkey1_idxfn::equals(se172, *e98)); 
                  }
                }
              n97 = n97->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i100 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n100; 
          AGG1ITEM1_L1_2_DELTA_entry* e100;
        
          for (size_t i = 0; i < i100->size_; i++)
          {
            n100 = i100->buckets_ + i;
            while (n100 && (e100 = n100->obj))
            {
                long store_sales_ss_item_sk = e100->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e100->ITEM_I_ITEM_ID;
                long v100 = e100->__av;
                { //slice 
                  const HashIndex_AGG3ITEM4_map_0* i101 = static_cast<HashIndex_AGG3ITEM4_map_0*>(AGG3ITEM4.index[1]);
                  const HASH_RES_t h48 = AGG3ITEM4_mapkey0_idxfn::hash(se176.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG3ITEM4_map_0::IdxNode* n101 = static_cast<HashIndex_AGG3ITEM4_map_0::IdxNode*>(i101->slice(se176, h48));
                  AGG3ITEM4_entry* e101;
                 
                  if (n101 && (e101 = n101->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e101->STORE_S_STATE;
                      DOUBLE_TYPE v101 = e101->__av;
                      long agg16 = 0L;
                      agg16 += (AGG1ITEM1_L1_2_DELTA.getValueOrDefault(se174.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM1_L1_2.getValueOrDefault(se175.modify(store_s_state,store_sales_ss_item_sk)));
                      long l13 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se173.modify(item_i_item_id,store_s_state)) + agg16);
                      (/*if */(0L != l13) ? AGG3.addOrDelOnZero(se167.modify(item_i_item_id,store_s_state),(v100 * (v101 * Udiv(Ulistmax(1L, l13))))) : (void)0);
                      n101 = n101->nxt;
                    } while (n101 && (e101 = n101->obj) && h48 == n101->hash &&  AGG3ITEM4_mapkey0_idxfn::equals(se176, *e101)); 
                  }
                }
              n100 = n100->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i102 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n102; 
          AGG1ITEM1_L1_2_DELTA_entry* e102;
        
          for (size_t i = 0; i < i102->size_; i++)
          {
            n102 = i102->buckets_ + i;
            while (n102 && (e102 = n102->obj))
            {
                long store_sales_ss_item_sk = e102->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e102->ITEM_I_ITEM_ID;
                long v102 = e102->__av;
                { //slice 
                  const HashIndex_AGG3STORE1_P_2ITEM1_map_1* i103 = static_cast<HashIndex_AGG3STORE1_P_2ITEM1_map_1*>(AGG3STORE1_P_2ITEM1.index[1]);
                  const HASH_RES_t h49 = AGG3STORE1_P_2ITEM1_mapkey1_idxfn::hash(se178.modify1(store_sales_ss_item_sk));
                  HashIndex_AGG3STORE1_P_2ITEM1_map_1::IdxNode* n103 = static_cast<HashIndex_AGG3STORE1_P_2ITEM1_map_1::IdxNode*>(i103->slice(se178, h49));
                  AGG3STORE1_P_2ITEM1_entry* e103;
                 
                  if (n103 && (e103 = n103->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e103->STORE_S_STATE;
                      DOUBLE_TYPE v103 = e103->__av;
                      AGG3STORE1_P_2.addOrDelOnZero(se177.modify(store_s_state,item_i_item_id),(v102 * v103));
                      n103 = n103->nxt;
                    } while (n103 && (e103 = n103->obj) && h49 == n103->hash &&  AGG3STORE1_P_2ITEM1_mapkey1_idxfn::equals(se178, *e103)); 
                  }
                }
              n102 = n102->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i104 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n104; 
          AGG1ITEM1_L1_2_DELTA_entry* e104;
        
          for (size_t i = 0; i < i104->size_; i++)
          {
            n104 = i104->buckets_ + i;
            while (n104 && (e104 = n104->obj))
            {
                long store_sales_ss_item_sk = e104->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e104->ITEM_I_ITEM_ID;
                long v104 = e104->__av;
                { //slice 
                  const HashIndex_AGG3ITEM4STORE1_map_0* i105 = static_cast<HashIndex_AGG3ITEM4STORE1_map_0*>(AGG3ITEM4STORE1.index[1]);
                  const HASH_RES_t h50 = AGG3ITEM4STORE1_mapkey0_idxfn::hash(se180.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG3ITEM4STORE1_map_0::IdxNode* n105 = static_cast<HashIndex_AGG3ITEM4STORE1_map_0::IdxNode*>(i105->slice(se180, h50));
                  AGG3ITEM4STORE1_entry* e105;
                 
                  if (n105 && (e105 = n105->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e105->STORE_SALES_SS_STORE_SK;
                      DOUBLE_TYPE v105 = e105->__av;
                      AGG3STORE4.addOrDelOnZero(se179.modify(store_sales_ss_store_sk,item_i_item_id),(v104 * v105));
                      n105 = n105->nxt;
                    } while (n105 && (e105 = n105->obj) && h50 == n105->hash &&  AGG3ITEM4STORE1_mapkey0_idxfn::equals(se180, *e105)); 
                  }
                }
              n104 = n104->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i106 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n106; 
          AGG1ITEM1_L1_2_DELTA_entry* e106;
        
          for (size_t i = 0; i < i106->size_; i++)
          {
            n106 = i106->buckets_ + i;
            while (n106 && (e106 = n106->obj))
            {
                long store_sales_ss_item_sk = e106->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e106->ITEM_I_ITEM_ID;
                long v106 = e106->__av;
                { //slice 
                  const HashIndex_AGG3ITEM4_map_0* i107 = static_cast<HashIndex_AGG3ITEM4_map_0*>(AGG3ITEM4.index[1]);
                  const HASH_RES_t h51 = AGG3ITEM4_mapkey0_idxfn::hash(se182.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG3ITEM4_map_0::IdxNode* n107 = static_cast<HashIndex_AGG3ITEM4_map_0::IdxNode*>(i107->slice(se182, h51));
                  AGG3ITEM4_entry* e107;
                 
                  if (n107 && (e107 = n107->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e107->STORE_S_STATE;
                      DOUBLE_TYPE v107 = e107->__av;
                      AGG3STORE_SALES1.addOrDelOnZero(se181.modify(store_s_state,item_i_item_id),(v106 * v107));
                      n107 = n107->nxt;
                    } while (n107 && (e107 = n107->obj) && h51 == n107->hash &&  AGG3ITEM4_mapkey0_idxfn::equals(se182, *e107)); 
                  }
                }
              n106 = n106->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DOMAIN1_map_0* i108 = static_cast<HashIndex_AGG1ITEM1_DOMAIN1_map_0*>(AGG1ITEM1_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM1_DOMAIN1_map_0::IdxNode* n108; 
          AGG1ITEM1_DOMAIN1_entry* e108;
        
          for (size_t i = 0; i < i108->size_; i++)
          {
            n108 = i108->buckets_ + i;
            while (n108 && (e108 = n108->obj))
            {
                STRING_TYPE item_i_item_id = e108->ITEM_I_ITEM_ID;
                long v108 = e108->__av;
                { //slice 
                  const HashIndex_AGG4STORE_SALES1_map_1* i109 = static_cast<HashIndex_AGG4STORE_SALES1_map_1*>(AGG4STORE_SALES1.index[1]);
                  const HASH_RES_t h53 = AGG4STORE_SALES1_mapkey1_idxfn::hash(se188.modify1(item_i_item_id));
                  HashIndex_AGG4STORE_SALES1_map_1::IdxNode* n109 = static_cast<HashIndex_AGG4STORE_SALES1_map_1::IdxNode*>(i109->slice(se188, h53));
                  AGG4STORE_SALES1_entry* e109;
                 
                  if (n109 && (e109 = n109->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e109->STORE_S_STATE;
                      DOUBLE_TYPE v109 = e109->__av;
                      DOUBLE_TYPE agg17 = 0.0;
                      long agg18 = 0L;
                      { //slice 
                        const HashIndex_AGG1ITEM1_L1_2_DELTA_map_1* i110 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1*>(AGG1ITEM1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h52 = AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::hash(se186.modify1(item_i_item_id));
                        HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode* n110 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_1::IdxNode*>(i110->slice(se186, h52));
                        AGG1ITEM1_L1_2_DELTA_entry* e110;
                       
                        if (n110 && (e110 = n110->obj)) {
                          do {                
                            long store_sales_ss_item_sk = e110->STORE_SALES_SS_ITEM_SK;
                            long v110 = e110->__av;
                            agg18 += (v110 * AGG1ITEM1_L1_2.getValueOrDefault(se185.modify(store_s_state,store_sales_ss_item_sk)));
                            n110 = n110->nxt;
                          } while (n110 && (e110 = n110->obj) && h52 == n110->hash &&  AGG1ITEM1_L1_2_DELTA_mapkey1_idxfn::equals(se186, *e110)); 
                        }
                      }long l14 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se184.modify(item_i_item_id,store_s_state)) + agg18);
                      (/*if */(0L != l14) ? agg17 += Udiv(Ulistmax(1L, l14)) : 0.0);
                      DOUBLE_TYPE agg19 = 0.0;
                      long l15 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se187.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l15) ? agg19 += Udiv(Ulistmax(1L, l15)) : 0.0);
                      AGG4.addOrDelOnZero(se183.modify(item_i_item_id,store_s_state),((v108 != 0 ? 1L : 0L) * (v109 * (agg17 + (agg19 * -1L)))));
                      n109 = n109->nxt;
                    } while (n109 && (e109 = n109->obj) && h53 == n109->hash &&  AGG4STORE_SALES1_mapkey1_idxfn::equals(se188, *e109)); 
                  }
                }
              n108 = n108->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i111 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n111; 
          AGG1ITEM1_L1_2_DELTA_entry* e111;
        
          for (size_t i = 0; i < i111->size_; i++)
          {
            n111 = i111->buckets_ + i;
            while (n111 && (e111 = n111->obj))
            {
                long store_sales_ss_item_sk = e111->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e111->ITEM_I_ITEM_ID;
                long v111 = e111->__av;
                { //slice 
                  const HashIndex_AGG4ITEM4_map_0* i112 = static_cast<HashIndex_AGG4ITEM4_map_0*>(AGG4ITEM4.index[1]);
                  const HASH_RES_t h54 = AGG4ITEM4_mapkey0_idxfn::hash(se192.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG4ITEM4_map_0::IdxNode* n112 = static_cast<HashIndex_AGG4ITEM4_map_0::IdxNode*>(i112->slice(se192, h54));
                  AGG4ITEM4_entry* e112;
                 
                  if (n112 && (e112 = n112->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e112->STORE_S_STATE;
                      DOUBLE_TYPE v112 = e112->__av;
                      long agg20 = 0L;
                      agg20 += (AGG1ITEM1_L1_2_DELTA.getValueOrDefault(se190.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM1_L1_2.getValueOrDefault(se191.modify(store_s_state,store_sales_ss_item_sk)));
                      long l16 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se189.modify(item_i_item_id,store_s_state)) + agg20);
                      (/*if */(0L != l16) ? AGG4.addOrDelOnZero(se183.modify(item_i_item_id,store_s_state),(v111 * (v112 * Udiv(Ulistmax(1L, l16))))) : (void)0);
                      n112 = n112->nxt;
                    } while (n112 && (e112 = n112->obj) && h54 == n112->hash &&  AGG4ITEM4_mapkey0_idxfn::equals(se192, *e112)); 
                  }
                }
              n111 = n111->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i113 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n113; 
          AGG1ITEM1_L1_2_DELTA_entry* e113;
        
          for (size_t i = 0; i < i113->size_; i++)
          {
            n113 = i113->buckets_ + i;
            while (n113 && (e113 = n113->obj))
            {
                long store_sales_ss_item_sk = e113->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e113->ITEM_I_ITEM_ID;
                long v113 = e113->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2_map_1* i114 = static_cast<HashIndex_AGG1ITEM1_L1_2_map_1*>(AGG1ITEM1_L1_2.index[1]);
                  const HASH_RES_t h55 = AGG1ITEM1_L1_2_mapkey1_idxfn::hash(se194.modify1(store_sales_ss_item_sk));
                  HashIndex_AGG1ITEM1_L1_2_map_1::IdxNode* n114 = static_cast<HashIndex_AGG1ITEM1_L1_2_map_1::IdxNode*>(i114->slice(se194, h55));
                  AGG1ITEM1_L1_2_entry* e114;
                 
                  if (n114 && (e114 = n114->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e114->STORE_S_STATE;
                      long v114 = e114->__av;
                      AGG1STORE_SALES1_L1_1.addOrDelOnZero(se193.modify(item_i_item_id,store_s_state),(v113 * v114));
                      n114 = n114->nxt;
                    } while (n114 && (e114 = n114->obj) && h55 == n114->hash &&  AGG1ITEM1_L1_2_mapkey1_idxfn::equals(se194, *e114)); 
                  }
                }
              n113 = n113->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i115 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n115; 
          AGG1ITEM1_L1_2_DELTA_entry* e115;
        
          for (size_t i = 0; i < i115->size_; i++)
          {
            n115 = i115->buckets_ + i;
            while (n115 && (e115 = n115->obj))
            {
                long store_sales_ss_item_sk = e115->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e115->ITEM_I_ITEM_ID;
                long v115 = e115->__av;
                { //slice 
                  const HashIndex_AGG4STORE1_P_2ITEM1_map_1* i116 = static_cast<HashIndex_AGG4STORE1_P_2ITEM1_map_1*>(AGG4STORE1_P_2ITEM1.index[1]);
                  const HASH_RES_t h56 = AGG4STORE1_P_2ITEM1_mapkey1_idxfn::hash(se196.modify1(store_sales_ss_item_sk));
                  HashIndex_AGG4STORE1_P_2ITEM1_map_1::IdxNode* n116 = static_cast<HashIndex_AGG4STORE1_P_2ITEM1_map_1::IdxNode*>(i116->slice(se196, h56));
                  AGG4STORE1_P_2ITEM1_entry* e116;
                 
                  if (n116 && (e116 = n116->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e116->STORE_S_STATE;
                      DOUBLE_TYPE v116 = e116->__av;
                      AGG4STORE1_P_2.addOrDelOnZero(se195.modify(store_s_state,item_i_item_id),(v115 * v116));
                      n116 = n116->nxt;
                    } while (n116 && (e116 = n116->obj) && h56 == n116->hash &&  AGG4STORE1_P_2ITEM1_mapkey1_idxfn::equals(se196, *e116)); 
                  }
                }
              n115 = n115->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i117 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n117; 
          AGG1ITEM1_L1_2_DELTA_entry* e117;
        
          for (size_t i = 0; i < i117->size_; i++)
          {
            n117 = i117->buckets_ + i;
            while (n117 && (e117 = n117->obj))
            {
                long store_sales_ss_item_sk = e117->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e117->ITEM_I_ITEM_ID;
                long v117 = e117->__av;
                { //slice 
                  const HashIndex_AGG4ITEM4STORE1_map_0* i118 = static_cast<HashIndex_AGG4ITEM4STORE1_map_0*>(AGG4ITEM4STORE1.index[1]);
                  const HASH_RES_t h57 = AGG4ITEM4STORE1_mapkey0_idxfn::hash(se198.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG4ITEM4STORE1_map_0::IdxNode* n118 = static_cast<HashIndex_AGG4ITEM4STORE1_map_0::IdxNode*>(i118->slice(se198, h57));
                  AGG4ITEM4STORE1_entry* e118;
                 
                  if (n118 && (e118 = n118->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e118->STORE_SALES_SS_STORE_SK;
                      DOUBLE_TYPE v118 = e118->__av;
                      AGG4STORE4.addOrDelOnZero(se197.modify(store_sales_ss_store_sk,item_i_item_id),(v117 * v118));
                      n118 = n118->nxt;
                    } while (n118 && (e118 = n118->obj) && h57 == n118->hash &&  AGG4ITEM4STORE1_mapkey0_idxfn::equals(se198, *e118)); 
                  }
                }
              n117 = n117->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_L1_2_DELTA_map_01* i119 = static_cast<HashIndex_AGG1ITEM1_L1_2_DELTA_map_01*>(AGG1ITEM1_L1_2_DELTA.index[0]);
          HashIndex_AGG1ITEM1_L1_2_DELTA_map_01::IdxNode* n119; 
          AGG1ITEM1_L1_2_DELTA_entry* e119;
        
          for (size_t i = 0; i < i119->size_; i++)
          {
            n119 = i119->buckets_ + i;
            while (n119 && (e119 = n119->obj))
            {
                long store_sales_ss_item_sk = e119->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e119->ITEM_I_ITEM_ID;
                long v119 = e119->__av;
                { //slice 
                  const HashIndex_AGG4ITEM4_map_0* i120 = static_cast<HashIndex_AGG4ITEM4_map_0*>(AGG4ITEM4.index[1]);
                  const HASH_RES_t h58 = AGG4ITEM4_mapkey0_idxfn::hash(se200.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG4ITEM4_map_0::IdxNode* n120 = static_cast<HashIndex_AGG4ITEM4_map_0::IdxNode*>(i120->slice(se200, h58));
                  AGG4ITEM4_entry* e120;
                 
                  if (n120 && (e120 = n120->obj)) {
                    do {                
                      STRING_TYPE store_s_state = e120->STORE_S_STATE;
                      DOUBLE_TYPE v120 = e120->__av;
                      AGG4STORE_SALES1.addOrDelOnZero(se199.modify(store_s_state,item_i_item_id),(v119 * v120));
                      n120 = n120->nxt;
                    } while (n120 && (e120 = n120->obj) && h58 == n120->hash &&  AGG4ITEM4_mapkey0_idxfn::equals(se200, *e120)); 
                  }
                }
              n119 = n119->nxt;
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

        AGG1STORE4_DELTA.clear();
        AGG1STORE1_L1_2_DELTA.clear();
        AGG1STORE1_DOMAIN1.clear();
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
                STRING_TYPE store_s_state = DELTA_STORE.s_state[i];
                // STRING_TYPE store_s_zip = DELTA_STORE.s_zip[i];
                // STRING_TYPE store_s_country = DELTA_STORE.s_country[i];
                // DOUBLE_TYPE store_s_gmt_offset = DELTA_STORE.s_gmt_offset[i];
                // DOUBLE_TYPE store_s_tax_precentage = DELTA_STORE.s_tax_precentage[i];
                long v121 = 1L;
                (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG1STORE4_DELTA.addOrDelOnZero(se201.modify(store_sales_ss_store_sk,store_s_state),v121) : (void)0);
                long v122 = 1L;
                AGG1STORE1_L1_2_DELTA.addOrDelOnZero(se202.modify(store_sales_ss_store_sk,store_s_state),v122);
                long v123 = 1L;
                (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG1STORE1_DOMAIN1.addOrDelOnZero(se203.modify(store_s_state),(v123 != 0 ? 1L : 0L)) : (void)0);

          }
        }

        {  // foreach
          const HashIndex_AGG1STORE1_DOMAIN1_map_0* i124 = static_cast<HashIndex_AGG1STORE1_DOMAIN1_map_0*>(AGG1STORE1_DOMAIN1.index[0]);
          HashIndex_AGG1STORE1_DOMAIN1_map_0::IdxNode* n124; 
          AGG1STORE1_DOMAIN1_entry* e124;
        
          for (size_t i = 0; i < i124->size_; i++)
          {
            n124 = i124->buckets_ + i;
            while (n124 && (e124 = n124->obj))
            {
                STRING_TYPE store_s_state = e124->STORE_S_STATE;
                long v124 = e124->__av;
                _c1.clear();
                { //slice 
                  const HashIndex_AGG1STORE1_P_2_map_0* i125 = static_cast<HashIndex_AGG1STORE1_P_2_map_0*>(AGG1STORE1_P_2.index[1]);
                  const HASH_RES_t h60 = AGG1STORE1_P_2_mapkey0_idxfn::hash(se209.modify0(store_s_state));
                  HashIndex_AGG1STORE1_P_2_map_0::IdxNode* n125 = static_cast<HashIndex_AGG1STORE1_P_2_map_0::IdxNode*>(i125->slice(se209, h60));
                  AGG1STORE1_P_2_entry* e125;
                 
                  if (n125 && (e125 = n125->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e125->ITEM_I_ITEM_ID;
                      long v126 = e125->__av;
                      DOUBLE_TYPE agg21 = 0.0;
                      long agg22 = 0L;
                      { //slice 
                        const HashIndex_AGG1STORE1_L1_2_DELTA_map_1* i126 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1*>(AGG1STORE1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h59 = AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::hash(se207.modify1(store_s_state));
                        HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode* n126 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode*>(i126->slice(se207, h59));
                        AGG1STORE1_L1_2_DELTA_entry* e126;
                       
                        if (n126 && (e126 = n126->obj)) {
                          do {                
                            long store_sales_ss_store_sk = e126->STORE_SALES_SS_STORE_SK;
                            long v127 = e126->__av;
                            agg22 += (v127 * AGG1STORE1_L1_2.getValueOrDefault(se206.modify(item_i_item_id,store_sales_ss_store_sk)));
                            n126 = n126->nxt;
                          } while (n126 && (e126 = n126->obj) && h59 == n126->hash &&  AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::equals(se207, *e126)); 
                        }
                      }long l17 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se205.modify(item_i_item_id,store_s_state)) + agg22);
                      (/*if */(0L != l17) ? agg21 += Udiv(Ulistmax(1L, l17)) : 0.0);
                      DOUBLE_TYPE agg23 = 0.0;
                      long l18 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se208.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l18) ? agg23 += Udiv(Ulistmax(1L, l18)) : 0.0);
                      (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? _c1.addOrDelOnZero(st1.modify(item_i_item_id,(v126 * (agg21 + (agg23 * -1L)))), (v126 * (agg21 + (agg23 * -1L)))) : (void)0);
                      n125 = n125->nxt;
                    } while (n125 && (e125 = n125->obj) && h60 == n125->hash &&  AGG1STORE1_P_2_mapkey0_idxfn::equals(se209, *e125)); 
                  }
                }{ //slice 
                  const HashIndex_AGG1STORE4_DELTA_map_1* i127 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1*>(AGG1STORE4_DELTA.index[1]);
                  const HASH_RES_t h62 = AGG1STORE4_DELTA_mapkey1_idxfn::hash(se214.modify1(store_s_state));
                  HashIndex_AGG1STORE4_DELTA_map_1::IdxNode* n127 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1::IdxNode*>(i127->slice(se214, h62));
                  AGG1STORE4_DELTA_entry* e127;
                 
                  if (n127 && (e127 = n127->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e127->STORE_SALES_SS_STORE_SK;
                      long v128 = e127->__av;
                      { //slice 
                        const HashIndex_AGG1STORE4_map_0* i128 = static_cast<HashIndex_AGG1STORE4_map_0*>(AGG1STORE4.index[1]);
                        const HASH_RES_t h61 = AGG1STORE4_mapkey0_idxfn::hash(se213.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG1STORE4_map_0::IdxNode* n128 = static_cast<HashIndex_AGG1STORE4_map_0::IdxNode*>(i128->slice(se213, h61));
                        AGG1STORE4_entry* e128;
                       
                        if (n128 && (e128 = n128->obj)) {
                          do {                
                            STRING_TYPE item_i_item_id = e128->ITEM_I_ITEM_ID;
                            long v129 = e128->__av;
                            long agg24 = 0L;
                            agg24 += (AGG1STORE1_L1_2_DELTA.getValueOrDefault(se211.modify(store_sales_ss_store_sk,store_s_state)) * AGG1STORE1_L1_2.getValueOrDefault(se212.modify(item_i_item_id,store_sales_ss_store_sk)));
                            long l19 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se210.modify(item_i_item_id,store_s_state)) + agg24);
                            (/*if */(0L != l19) ? _c1.addOrDelOnZero(st2.modify(item_i_item_id,(v128 * (v129 * Udiv(Ulistmax(1L, l19))))), (v128 * (v129 * Udiv(Ulistmax(1L, l19))))) : (void)0);
                            n128 = n128->nxt;
                          } while (n128 && (e128 = n128->obj) && h61 == n128->hash &&  AGG1STORE4_mapkey0_idxfn::equals(se213, *e128)); 
                        }
                      }
                      n127 = n127->nxt;
                    } while (n127 && (e127 = n127->obj) && h62 == n127->hash &&  AGG1STORE4_DELTA_mapkey1_idxfn::equals(se214, *e127)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i129 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c1.index[0]);
                  HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n129; 
                  tuple2_S_D* e129;
                
                  for (size_t i = 0; i < i129->size_; i++)
                  {
                    n129 = i129->buckets_ + i;
                    while (n129 && (e129 = n129->obj))
                    {
                      STRING_TYPE item_i_item_id = e129->_1;  
                      DOUBLE_TYPE v130 = e129->__av; 
                    AGG1.addOrDelOnZero(se204.modify(item_i_item_id,store_s_state),((v124 != 0 ? 1L : 0L) * v130));      
                      n129 = n129->nxt;
                    }
                  }
                }
              n124 = n124->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i130 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n130; 
          AGG1STORE1_L1_2_DELTA_entry* e130;
        
          for (size_t i = 0; i < i130->size_; i++)
          {
            n130 = i130->buckets_ + i;
            while (n130 && (e130 = n130->obj))
            {
                long store_sales_ss_store_sk = e130->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e130->STORE_S_STATE;
                long v131 = e130->__av;
                { //slice 
                  const HashIndex_AGG1ITEM1_L1_2STORE1_map_1* i131 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_1*>(AGG1ITEM1_L1_2STORE1.index[2]);
                  const HASH_RES_t h63 = AGG1ITEM1_L1_2STORE1_mapkey1_idxfn::hash(se216.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM1_L1_2STORE1_map_1::IdxNode* n131 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_1::IdxNode*>(i131->slice(se216, h63));
                  AGG1ITEM1_L1_2STORE1_entry* e131;
                 
                  if (n131 && (e131 = n131->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e131->STORE_SALES_SS_ITEM_SK;
                      long v132 = e131->__av;
                      AGG1ITEM1_L1_2.addOrDelOnZero(se215.modify(store_s_state,store_sales_ss_item_sk),(v131 * v132));
                      n131 = n131->nxt;
                    } while (n131 && (e131 = n131->obj) && h63 == n131->hash &&  AGG1ITEM1_L1_2STORE1_mapkey1_idxfn::equals(se216, *e131)); 
                  }
                }
              n130 = n130->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i132 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n132; 
          AGG1STORE1_L1_2_DELTA_entry* e132;
        
          for (size_t i = 0; i < i132->size_; i++)
          {
            n132 = i132->buckets_ + i;
            while (n132 && (e132 = n132->obj))
            {
                long store_sales_ss_store_sk = e132->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e132->STORE_S_STATE;
                long v133 = e132->__av;
                AGG1ITEM1_L1_2STORE_SALES1_P_3.addOrDelOnZero(se217.modify(store_sales_ss_store_sk,store_s_state),v133);
              n132 = n132->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i133 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n133; 
          AGG1STORE4_DELTA_entry* e133;
        
          for (size_t i = 0; i < i133->size_; i++)
          {
            n133 = i133->buckets_ + i;
            while (n133 && (e133 = n133->obj))
            {
                long store_sales_ss_store_sk = e133->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e133->STORE_S_STATE;
                long v134 = e133->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4STORE1_map_1* i134 = static_cast<HashIndex_AGG1ITEM4STORE1_map_1*>(AGG1ITEM4STORE1.index[2]);
                  const HASH_RES_t h64 = AGG1ITEM4STORE1_mapkey1_idxfn::hash(se219.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM4STORE1_map_1::IdxNode* n134 = static_cast<HashIndex_AGG1ITEM4STORE1_map_1::IdxNode*>(i134->slice(se219, h64));
                  AGG1ITEM4STORE1_entry* e134;
                 
                  if (n134 && (e134 = n134->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e134->STORE_SALES_SS_ITEM_SK;
                      long v135 = e134->__av;
                      AGG1ITEM4.addOrDelOnZero(se218.modify(store_sales_ss_item_sk,store_s_state),(v134 * v135));
                      n134 = n134->nxt;
                    } while (n134 && (e134 = n134->obj) && h64 == n134->hash &&  AGG1ITEM4STORE1_mapkey1_idxfn::equals(se219, *e134)); 
                  }
                }
              n133 = n133->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i135 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n135; 
          AGG1STORE4_DELTA_entry* e135;
        
          for (size_t i = 0; i < i135->size_; i++)
          {
            n135 = i135->buckets_ + i;
            while (n135 && (e135 = n135->obj))
            {
                long store_sales_ss_store_sk = e135->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e135->STORE_S_STATE;
                long v136 = e135->__av;
                AGG1ITEM4STORE_SALES1_P_3.addOrDelOnZero(se220.modify(store_sales_ss_store_sk,store_s_state),v136);
              n135 = n135->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i136 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n136; 
          AGG1STORE1_L1_2_DELTA_entry* e136;
        
          for (size_t i = 0; i < i136->size_; i++)
          {
            n136 = i136->buckets_ + i;
            while (n136 && (e136 = n136->obj))
            {
                long store_sales_ss_store_sk = e136->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e136->STORE_S_STATE;
                long v137 = e136->__av;
                { //slice 
                  const HashIndex_AGG1STORE4_map_0* i137 = static_cast<HashIndex_AGG1STORE4_map_0*>(AGG1STORE4.index[1]);
                  const HASH_RES_t h65 = AGG1STORE4_mapkey0_idxfn::hash(se222.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1STORE4_map_0::IdxNode* n137 = static_cast<HashIndex_AGG1STORE4_map_0::IdxNode*>(i137->slice(se222, h65));
                  AGG1STORE4_entry* e137;
                 
                  if (n137 && (e137 = n137->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e137->ITEM_I_ITEM_ID;
                      long v138 = e137->__av;
                      AGG1STORE1_P_2.addOrDelOnZero(se221.modify(store_s_state,item_i_item_id),(v137 * v138));
                      n137 = n137->nxt;
                    } while (n137 && (e137 = n137->obj) && h65 == n137->hash &&  AGG1STORE4_mapkey0_idxfn::equals(se222, *e137)); 
                  }
                }
              n136 = n136->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i138 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n138; 
          AGG1STORE1_L1_2_DELTA_entry* e138;
        
          for (size_t i = 0; i < i138->size_; i++)
          {
            n138 = i138->buckets_ + i;
            while (n138 && (e138 = n138->obj))
            {
                long store_sales_ss_store_sk = e138->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e138->STORE_S_STATE;
                long v139 = e138->__av;
                { //slice 
                  const HashIndex_AGG1ITEM4STORE1_map_1* i139 = static_cast<HashIndex_AGG1ITEM4STORE1_map_1*>(AGG1ITEM4STORE1.index[2]);
                  const HASH_RES_t h66 = AGG1ITEM4STORE1_mapkey1_idxfn::hash(se224.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG1ITEM4STORE1_map_1::IdxNode* n139 = static_cast<HashIndex_AGG1ITEM4STORE1_map_1::IdxNode*>(i139->slice(se224, h66));
                  AGG1ITEM4STORE1_entry* e139;
                 
                  if (n139 && (e139 = n139->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e139->STORE_SALES_SS_ITEM_SK;
                      long v140 = e139->__av;
                      AGG1STORE1_P_2ITEM1.addOrDelOnZero(se223.modify(store_s_state,store_sales_ss_item_sk),(v139 * v140));
                      n139 = n139->nxt;
                    } while (n139 && (e139 = n139->obj) && h66 == n139->hash &&  AGG1ITEM4STORE1_mapkey1_idxfn::equals(se224, *e139)); 
                  }
                }
              n138 = n138->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i140 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n140; 
          AGG1STORE4_DELTA_entry* e140;
        
          for (size_t i = 0; i < i140->size_; i++)
          {
            n140 = i140->buckets_ + i;
            while (n140 && (e140 = n140->obj))
            {
                long store_sales_ss_store_sk = e140->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e140->STORE_S_STATE;
                long v141 = e140->__av;
                { //slice 
                  const HashIndex_AGG1STORE4_map_0* i141 = static_cast<HashIndex_AGG1STORE4_map_0*>(AGG1STORE4.index[1]);
                  const HASH_RES_t h67 = AGG1STORE4_mapkey0_idxfn::hash(se226.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG1STORE4_map_0::IdxNode* n141 = static_cast<HashIndex_AGG1STORE4_map_0::IdxNode*>(i141->slice(se226, h67));
                  AGG1STORE4_entry* e141;
                 
                  if (n141 && (e141 = n141->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e141->ITEM_I_ITEM_ID;
                      long v142 = e141->__av;
                      AGG1STORE_SALES1.addOrDelOnZero(se225.modify(store_s_state,item_i_item_id),(v141 * v142));
                      n141 = n141->nxt;
                    } while (n141 && (e141 = n141->obj) && h67 == n141->hash &&  AGG1STORE4_mapkey0_idxfn::equals(se226, *e141)); 
                  }
                }
              n140 = n140->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_DOMAIN1_map_0* i142 = static_cast<HashIndex_AGG1STORE1_DOMAIN1_map_0*>(AGG1STORE1_DOMAIN1.index[0]);
          HashIndex_AGG1STORE1_DOMAIN1_map_0::IdxNode* n142; 
          AGG1STORE1_DOMAIN1_entry* e142;
        
          for (size_t i = 0; i < i142->size_; i++)
          {
            n142 = i142->buckets_ + i;
            while (n142 && (e142 = n142->obj))
            {
                STRING_TYPE store_s_state = e142->STORE_S_STATE;
                long v143 = e142->__av;
                _c2.clear();
                { //slice 
                  const HashIndex_AGG2STORE1_P_2_map_0* i143 = static_cast<HashIndex_AGG2STORE1_P_2_map_0*>(AGG2STORE1_P_2.index[1]);
                  const HASH_RES_t h69 = AGG2STORE1_P_2_mapkey0_idxfn::hash(se232.modify0(store_s_state));
                  HashIndex_AGG2STORE1_P_2_map_0::IdxNode* n143 = static_cast<HashIndex_AGG2STORE1_P_2_map_0::IdxNode*>(i143->slice(se232, h69));
                  AGG2STORE1_P_2_entry* e143;
                 
                  if (n143 && (e143 = n143->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e143->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v145 = e143->__av;
                      DOUBLE_TYPE agg25 = 0.0;
                      long agg26 = 0L;
                      { //slice 
                        const HashIndex_AGG1STORE1_L1_2_DELTA_map_1* i144 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1*>(AGG1STORE1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h68 = AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::hash(se230.modify1(store_s_state));
                        HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode* n144 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode*>(i144->slice(se230, h68));
                        AGG1STORE1_L1_2_DELTA_entry* e144;
                       
                        if (n144 && (e144 = n144->obj)) {
                          do {                
                            long store_sales_ss_store_sk = e144->STORE_SALES_SS_STORE_SK;
                            long v146 = e144->__av;
                            agg26 += (v146 * AGG1STORE1_L1_2.getValueOrDefault(se229.modify(item_i_item_id,store_sales_ss_store_sk)));
                            n144 = n144->nxt;
                          } while (n144 && (e144 = n144->obj) && h68 == n144->hash &&  AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::equals(se230, *e144)); 
                        }
                      }long l20 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se228.modify(item_i_item_id,store_s_state)) + agg26);
                      (/*if */(0L != l20) ? agg25 += Udiv(Ulistmax(1L, l20)) : 0.0);
                      DOUBLE_TYPE agg27 = 0.0;
                      long l21 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se231.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l21) ? agg27 += Udiv(Ulistmax(1L, l21)) : 0.0);
                      (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? _c2.addOrDelOnZero(st3.modify(item_i_item_id,(v145 * (agg25 + (agg27 * -1L)))), (v145 * (agg25 + (agg27 * -1L)))) : (void)0);
                      n143 = n143->nxt;
                    } while (n143 && (e143 = n143->obj) && h69 == n143->hash &&  AGG2STORE1_P_2_mapkey0_idxfn::equals(se232, *e143)); 
                  }
                }{ //slice 
                  const HashIndex_AGG1STORE4_DELTA_map_1* i145 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1*>(AGG1STORE4_DELTA.index[1]);
                  const HASH_RES_t h71 = AGG1STORE4_DELTA_mapkey1_idxfn::hash(se237.modify1(store_s_state));
                  HashIndex_AGG1STORE4_DELTA_map_1::IdxNode* n145 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1::IdxNode*>(i145->slice(se237, h71));
                  AGG1STORE4_DELTA_entry* e145;
                 
                  if (n145 && (e145 = n145->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e145->STORE_SALES_SS_STORE_SK;
                      long v147 = e145->__av;
                      { //slice 
                        const HashIndex_AGG2STORE4_map_0* i146 = static_cast<HashIndex_AGG2STORE4_map_0*>(AGG2STORE4.index[1]);
                        const HASH_RES_t h70 = AGG2STORE4_mapkey0_idxfn::hash(se236.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG2STORE4_map_0::IdxNode* n146 = static_cast<HashIndex_AGG2STORE4_map_0::IdxNode*>(i146->slice(se236, h70));
                        AGG2STORE4_entry* e146;
                       
                        if (n146 && (e146 = n146->obj)) {
                          do {                
                            STRING_TYPE item_i_item_id = e146->ITEM_I_ITEM_ID;
                            DOUBLE_TYPE v148 = e146->__av;
                            long agg28 = 0L;
                            agg28 += (AGG1STORE1_L1_2_DELTA.getValueOrDefault(se234.modify(store_sales_ss_store_sk,store_s_state)) * AGG1STORE1_L1_2.getValueOrDefault(se235.modify(item_i_item_id,store_sales_ss_store_sk)));
                            long l22 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se233.modify(item_i_item_id,store_s_state)) + agg28);
                            (/*if */(0L != l22) ? _c2.addOrDelOnZero(st4.modify(item_i_item_id,(v147 * (v148 * Udiv(Ulistmax(1L, l22))))), (v147 * (v148 * Udiv(Ulistmax(1L, l22))))) : (void)0);
                            n146 = n146->nxt;
                          } while (n146 && (e146 = n146->obj) && h70 == n146->hash &&  AGG2STORE4_mapkey0_idxfn::equals(se236, *e146)); 
                        }
                      }
                      n145 = n145->nxt;
                    } while (n145 && (e145 = n145->obj) && h71 == n145->hash &&  AGG1STORE4_DELTA_mapkey1_idxfn::equals(se237, *e145)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i147 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c2.index[0]);
                  HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n147; 
                  tuple2_S_D* e147;
                
                  for (size_t i = 0; i < i147->size_; i++)
                  {
                    n147 = i147->buckets_ + i;
                    while (n147 && (e147 = n147->obj))
                    {
                      STRING_TYPE item_i_item_id = e147->_1;  
                      DOUBLE_TYPE v149 = e147->__av; 
                    AGG2.addOrDelOnZero(se227.modify(item_i_item_id,store_s_state),((v143 != 0 ? 1L : 0L) * v149));      
                      n147 = n147->nxt;
                    }
                  }
                }
              n142 = n142->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i148 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n148; 
          AGG1STORE4_DELTA_entry* e148;
        
          for (size_t i = 0; i < i148->size_; i++)
          {
            n148 = i148->buckets_ + i;
            while (n148 && (e148 = n148->obj))
            {
                long store_sales_ss_store_sk = e148->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e148->STORE_S_STATE;
                long v150 = e148->__av;
                { //slice 
                  const HashIndex_AGG2ITEM4STORE1_map_1* i149 = static_cast<HashIndex_AGG2ITEM4STORE1_map_1*>(AGG2ITEM4STORE1.index[2]);
                  const HASH_RES_t h72 = AGG2ITEM4STORE1_mapkey1_idxfn::hash(se239.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG2ITEM4STORE1_map_1::IdxNode* n149 = static_cast<HashIndex_AGG2ITEM4STORE1_map_1::IdxNode*>(i149->slice(se239, h72));
                  AGG2ITEM4STORE1_entry* e149;
                 
                  if (n149 && (e149 = n149->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e149->STORE_SALES_SS_ITEM_SK;
                      DOUBLE_TYPE v151 = e149->__av;
                      AGG2ITEM4.addOrDelOnZero(se238.modify(store_sales_ss_item_sk,store_s_state),(v150 * v151));
                      n149 = n149->nxt;
                    } while (n149 && (e149 = n149->obj) && h72 == n149->hash &&  AGG2ITEM4STORE1_mapkey1_idxfn::equals(se239, *e149)); 
                  }
                }
              n148 = n148->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i150 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n150; 
          AGG1STORE1_L1_2_DELTA_entry* e150;
        
          for (size_t i = 0; i < i150->size_; i++)
          {
            n150 = i150->buckets_ + i;
            while (n150 && (e150 = n150->obj))
            {
                long store_sales_ss_store_sk = e150->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e150->STORE_S_STATE;
                long v152 = e150->__av;
                { //slice 
                  const HashIndex_AGG2STORE4_map_0* i151 = static_cast<HashIndex_AGG2STORE4_map_0*>(AGG2STORE4.index[1]);
                  const HASH_RES_t h73 = AGG2STORE4_mapkey0_idxfn::hash(se241.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG2STORE4_map_0::IdxNode* n151 = static_cast<HashIndex_AGG2STORE4_map_0::IdxNode*>(i151->slice(se241, h73));
                  AGG2STORE4_entry* e151;
                 
                  if (n151 && (e151 = n151->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e151->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v153 = e151->__av;
                      AGG2STORE1_P_2.addOrDelOnZero(se240.modify(store_s_state,item_i_item_id),(v152 * v153));
                      n151 = n151->nxt;
                    } while (n151 && (e151 = n151->obj) && h73 == n151->hash &&  AGG2STORE4_mapkey0_idxfn::equals(se241, *e151)); 
                  }
                }
              n150 = n150->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i152 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n152; 
          AGG1STORE1_L1_2_DELTA_entry* e152;
        
          for (size_t i = 0; i < i152->size_; i++)
          {
            n152 = i152->buckets_ + i;
            while (n152 && (e152 = n152->obj))
            {
                long store_sales_ss_store_sk = e152->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e152->STORE_S_STATE;
                long v154 = e152->__av;
                { //slice 
                  const HashIndex_AGG2ITEM4STORE1_map_1* i153 = static_cast<HashIndex_AGG2ITEM4STORE1_map_1*>(AGG2ITEM4STORE1.index[2]);
                  const HASH_RES_t h74 = AGG2ITEM4STORE1_mapkey1_idxfn::hash(se243.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG2ITEM4STORE1_map_1::IdxNode* n153 = static_cast<HashIndex_AGG2ITEM4STORE1_map_1::IdxNode*>(i153->slice(se243, h74));
                  AGG2ITEM4STORE1_entry* e153;
                 
                  if (n153 && (e153 = n153->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e153->STORE_SALES_SS_ITEM_SK;
                      DOUBLE_TYPE v155 = e153->__av;
                      AGG2STORE1_P_2ITEM1.addOrDelOnZero(se242.modify(store_s_state,store_sales_ss_item_sk),(v154 * v155));
                      n153 = n153->nxt;
                    } while (n153 && (e153 = n153->obj) && h74 == n153->hash &&  AGG2ITEM4STORE1_mapkey1_idxfn::equals(se243, *e153)); 
                  }
                }
              n152 = n152->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i154 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n154; 
          AGG1STORE4_DELTA_entry* e154;
        
          for (size_t i = 0; i < i154->size_; i++)
          {
            n154 = i154->buckets_ + i;
            while (n154 && (e154 = n154->obj))
            {
                long store_sales_ss_store_sk = e154->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e154->STORE_S_STATE;
                long v156 = e154->__av;
                { //slice 
                  const HashIndex_AGG2STORE4_map_0* i155 = static_cast<HashIndex_AGG2STORE4_map_0*>(AGG2STORE4.index[1]);
                  const HASH_RES_t h75 = AGG2STORE4_mapkey0_idxfn::hash(se245.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG2STORE4_map_0::IdxNode* n155 = static_cast<HashIndex_AGG2STORE4_map_0::IdxNode*>(i155->slice(se245, h75));
                  AGG2STORE4_entry* e155;
                 
                  if (n155 && (e155 = n155->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e155->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v157 = e155->__av;
                      AGG2STORE_SALES1.addOrDelOnZero(se244.modify(store_s_state,item_i_item_id),(v156 * v157));
                      n155 = n155->nxt;
                    } while (n155 && (e155 = n155->obj) && h75 == n155->hash &&  AGG2STORE4_mapkey0_idxfn::equals(se245, *e155)); 
                  }
                }
              n154 = n154->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_DOMAIN1_map_0* i156 = static_cast<HashIndex_AGG1STORE1_DOMAIN1_map_0*>(AGG1STORE1_DOMAIN1.index[0]);
          HashIndex_AGG1STORE1_DOMAIN1_map_0::IdxNode* n156; 
          AGG1STORE1_DOMAIN1_entry* e156;
        
          for (size_t i = 0; i < i156->size_; i++)
          {
            n156 = i156->buckets_ + i;
            while (n156 && (e156 = n156->obj))
            {
                STRING_TYPE store_s_state = e156->STORE_S_STATE;
                long v158 = e156->__av;
                _c3.clear();
                { //slice 
                  const HashIndex_AGG3STORE1_P_2_map_0* i157 = static_cast<HashIndex_AGG3STORE1_P_2_map_0*>(AGG3STORE1_P_2.index[1]);
                  const HASH_RES_t h77 = AGG3STORE1_P_2_mapkey0_idxfn::hash(se251.modify0(store_s_state));
                  HashIndex_AGG3STORE1_P_2_map_0::IdxNode* n157 = static_cast<HashIndex_AGG3STORE1_P_2_map_0::IdxNode*>(i157->slice(se251, h77));
                  AGG3STORE1_P_2_entry* e157;
                 
                  if (n157 && (e157 = n157->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e157->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v160 = e157->__av;
                      DOUBLE_TYPE agg29 = 0.0;
                      long agg30 = 0L;
                      { //slice 
                        const HashIndex_AGG1STORE1_L1_2_DELTA_map_1* i158 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1*>(AGG1STORE1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h76 = AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::hash(se249.modify1(store_s_state));
                        HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode* n158 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode*>(i158->slice(se249, h76));
                        AGG1STORE1_L1_2_DELTA_entry* e158;
                       
                        if (n158 && (e158 = n158->obj)) {
                          do {                
                            long store_sales_ss_store_sk = e158->STORE_SALES_SS_STORE_SK;
                            long v161 = e158->__av;
                            agg30 += (v161 * AGG1STORE1_L1_2.getValueOrDefault(se248.modify(item_i_item_id,store_sales_ss_store_sk)));
                            n158 = n158->nxt;
                          } while (n158 && (e158 = n158->obj) && h76 == n158->hash &&  AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::equals(se249, *e158)); 
                        }
                      }long l23 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se247.modify(item_i_item_id,store_s_state)) + agg30);
                      (/*if */(0L != l23) ? agg29 += Udiv(Ulistmax(1L, l23)) : 0.0);
                      DOUBLE_TYPE agg31 = 0.0;
                      long l24 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se250.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l24) ? agg31 += Udiv(Ulistmax(1L, l24)) : 0.0);
                      (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? _c3.addOrDelOnZero(st5.modify(item_i_item_id,(v160 * (agg29 + (agg31 * -1L)))), (v160 * (agg29 + (agg31 * -1L)))) : (void)0);
                      n157 = n157->nxt;
                    } while (n157 && (e157 = n157->obj) && h77 == n157->hash &&  AGG3STORE1_P_2_mapkey0_idxfn::equals(se251, *e157)); 
                  }
                }{ //slice 
                  const HashIndex_AGG1STORE4_DELTA_map_1* i159 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1*>(AGG1STORE4_DELTA.index[1]);
                  const HASH_RES_t h79 = AGG1STORE4_DELTA_mapkey1_idxfn::hash(se256.modify1(store_s_state));
                  HashIndex_AGG1STORE4_DELTA_map_1::IdxNode* n159 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1::IdxNode*>(i159->slice(se256, h79));
                  AGG1STORE4_DELTA_entry* e159;
                 
                  if (n159 && (e159 = n159->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e159->STORE_SALES_SS_STORE_SK;
                      long v162 = e159->__av;
                      { //slice 
                        const HashIndex_AGG3STORE4_map_0* i160 = static_cast<HashIndex_AGG3STORE4_map_0*>(AGG3STORE4.index[1]);
                        const HASH_RES_t h78 = AGG3STORE4_mapkey0_idxfn::hash(se255.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG3STORE4_map_0::IdxNode* n160 = static_cast<HashIndex_AGG3STORE4_map_0::IdxNode*>(i160->slice(se255, h78));
                        AGG3STORE4_entry* e160;
                       
                        if (n160 && (e160 = n160->obj)) {
                          do {                
                            STRING_TYPE item_i_item_id = e160->ITEM_I_ITEM_ID;
                            DOUBLE_TYPE v163 = e160->__av;
                            long agg32 = 0L;
                            agg32 += (AGG1STORE1_L1_2_DELTA.getValueOrDefault(se253.modify(store_sales_ss_store_sk,store_s_state)) * AGG1STORE1_L1_2.getValueOrDefault(se254.modify(item_i_item_id,store_sales_ss_store_sk)));
                            long l25 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se252.modify(item_i_item_id,store_s_state)) + agg32);
                            (/*if */(0L != l25) ? _c3.addOrDelOnZero(st6.modify(item_i_item_id,(v162 * (v163 * Udiv(Ulistmax(1L, l25))))), (v162 * (v163 * Udiv(Ulistmax(1L, l25))))) : (void)0);
                            n160 = n160->nxt;
                          } while (n160 && (e160 = n160->obj) && h78 == n160->hash &&  AGG3STORE4_mapkey0_idxfn::equals(se255, *e160)); 
                        }
                      }
                      n159 = n159->nxt;
                    } while (n159 && (e159 = n159->obj) && h79 == n159->hash &&  AGG1STORE4_DELTA_mapkey1_idxfn::equals(se256, *e159)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i161 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c3.index[0]);
                  HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n161; 
                  tuple2_S_D* e161;
                
                  for (size_t i = 0; i < i161->size_; i++)
                  {
                    n161 = i161->buckets_ + i;
                    while (n161 && (e161 = n161->obj))
                    {
                      STRING_TYPE item_i_item_id = e161->_1;  
                      DOUBLE_TYPE v164 = e161->__av; 
                    AGG3.addOrDelOnZero(se246.modify(item_i_item_id,store_s_state),((v158 != 0 ? 1L : 0L) * v164));      
                      n161 = n161->nxt;
                    }
                  }
                }
              n156 = n156->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i162 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n162; 
          AGG1STORE4_DELTA_entry* e162;
        
          for (size_t i = 0; i < i162->size_; i++)
          {
            n162 = i162->buckets_ + i;
            while (n162 && (e162 = n162->obj))
            {
                long store_sales_ss_store_sk = e162->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e162->STORE_S_STATE;
                long v165 = e162->__av;
                { //slice 
                  const HashIndex_AGG3ITEM4STORE1_map_1* i163 = static_cast<HashIndex_AGG3ITEM4STORE1_map_1*>(AGG3ITEM4STORE1.index[2]);
                  const HASH_RES_t h80 = AGG3ITEM4STORE1_mapkey1_idxfn::hash(se258.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG3ITEM4STORE1_map_1::IdxNode* n163 = static_cast<HashIndex_AGG3ITEM4STORE1_map_1::IdxNode*>(i163->slice(se258, h80));
                  AGG3ITEM4STORE1_entry* e163;
                 
                  if (n163 && (e163 = n163->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e163->STORE_SALES_SS_ITEM_SK;
                      DOUBLE_TYPE v166 = e163->__av;
                      AGG3ITEM4.addOrDelOnZero(se257.modify(store_sales_ss_item_sk,store_s_state),(v165 * v166));
                      n163 = n163->nxt;
                    } while (n163 && (e163 = n163->obj) && h80 == n163->hash &&  AGG3ITEM4STORE1_mapkey1_idxfn::equals(se258, *e163)); 
                  }
                }
              n162 = n162->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i164 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n164; 
          AGG1STORE1_L1_2_DELTA_entry* e164;
        
          for (size_t i = 0; i < i164->size_; i++)
          {
            n164 = i164->buckets_ + i;
            while (n164 && (e164 = n164->obj))
            {
                long store_sales_ss_store_sk = e164->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e164->STORE_S_STATE;
                long v167 = e164->__av;
                { //slice 
                  const HashIndex_AGG3STORE4_map_0* i165 = static_cast<HashIndex_AGG3STORE4_map_0*>(AGG3STORE4.index[1]);
                  const HASH_RES_t h81 = AGG3STORE4_mapkey0_idxfn::hash(se260.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG3STORE4_map_0::IdxNode* n165 = static_cast<HashIndex_AGG3STORE4_map_0::IdxNode*>(i165->slice(se260, h81));
                  AGG3STORE4_entry* e165;
                 
                  if (n165 && (e165 = n165->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e165->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v168 = e165->__av;
                      AGG3STORE1_P_2.addOrDelOnZero(se259.modify(store_s_state,item_i_item_id),(v167 * v168));
                      n165 = n165->nxt;
                    } while (n165 && (e165 = n165->obj) && h81 == n165->hash &&  AGG3STORE4_mapkey0_idxfn::equals(se260, *e165)); 
                  }
                }
              n164 = n164->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i166 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n166; 
          AGG1STORE1_L1_2_DELTA_entry* e166;
        
          for (size_t i = 0; i < i166->size_; i++)
          {
            n166 = i166->buckets_ + i;
            while (n166 && (e166 = n166->obj))
            {
                long store_sales_ss_store_sk = e166->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e166->STORE_S_STATE;
                long v169 = e166->__av;
                { //slice 
                  const HashIndex_AGG3ITEM4STORE1_map_1* i167 = static_cast<HashIndex_AGG3ITEM4STORE1_map_1*>(AGG3ITEM4STORE1.index[2]);
                  const HASH_RES_t h82 = AGG3ITEM4STORE1_mapkey1_idxfn::hash(se262.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG3ITEM4STORE1_map_1::IdxNode* n167 = static_cast<HashIndex_AGG3ITEM4STORE1_map_1::IdxNode*>(i167->slice(se262, h82));
                  AGG3ITEM4STORE1_entry* e167;
                 
                  if (n167 && (e167 = n167->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e167->STORE_SALES_SS_ITEM_SK;
                      DOUBLE_TYPE v170 = e167->__av;
                      AGG3STORE1_P_2ITEM1.addOrDelOnZero(se261.modify(store_s_state,store_sales_ss_item_sk),(v169 * v170));
                      n167 = n167->nxt;
                    } while (n167 && (e167 = n167->obj) && h82 == n167->hash &&  AGG3ITEM4STORE1_mapkey1_idxfn::equals(se262, *e167)); 
                  }
                }
              n166 = n166->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i168 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n168; 
          AGG1STORE4_DELTA_entry* e168;
        
          for (size_t i = 0; i < i168->size_; i++)
          {
            n168 = i168->buckets_ + i;
            while (n168 && (e168 = n168->obj))
            {
                long store_sales_ss_store_sk = e168->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e168->STORE_S_STATE;
                long v171 = e168->__av;
                { //slice 
                  const HashIndex_AGG3STORE4_map_0* i169 = static_cast<HashIndex_AGG3STORE4_map_0*>(AGG3STORE4.index[1]);
                  const HASH_RES_t h83 = AGG3STORE4_mapkey0_idxfn::hash(se264.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG3STORE4_map_0::IdxNode* n169 = static_cast<HashIndex_AGG3STORE4_map_0::IdxNode*>(i169->slice(se264, h83));
                  AGG3STORE4_entry* e169;
                 
                  if (n169 && (e169 = n169->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e169->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v172 = e169->__av;
                      AGG3STORE_SALES1.addOrDelOnZero(se263.modify(store_s_state,item_i_item_id),(v171 * v172));
                      n169 = n169->nxt;
                    } while (n169 && (e169 = n169->obj) && h83 == n169->hash &&  AGG3STORE4_mapkey0_idxfn::equals(se264, *e169)); 
                  }
                }
              n168 = n168->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_DOMAIN1_map_0* i170 = static_cast<HashIndex_AGG1STORE1_DOMAIN1_map_0*>(AGG1STORE1_DOMAIN1.index[0]);
          HashIndex_AGG1STORE1_DOMAIN1_map_0::IdxNode* n170; 
          AGG1STORE1_DOMAIN1_entry* e170;
        
          for (size_t i = 0; i < i170->size_; i++)
          {
            n170 = i170->buckets_ + i;
            while (n170 && (e170 = n170->obj))
            {
                STRING_TYPE store_s_state = e170->STORE_S_STATE;
                long v173 = e170->__av;
                _c4.clear();
                { //slice 
                  const HashIndex_AGG4STORE1_P_2_map_0* i171 = static_cast<HashIndex_AGG4STORE1_P_2_map_0*>(AGG4STORE1_P_2.index[1]);
                  const HASH_RES_t h85 = AGG4STORE1_P_2_mapkey0_idxfn::hash(se270.modify0(store_s_state));
                  HashIndex_AGG4STORE1_P_2_map_0::IdxNode* n171 = static_cast<HashIndex_AGG4STORE1_P_2_map_0::IdxNode*>(i171->slice(se270, h85));
                  AGG4STORE1_P_2_entry* e171;
                 
                  if (n171 && (e171 = n171->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e171->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v175 = e171->__av;
                      DOUBLE_TYPE agg33 = 0.0;
                      long agg34 = 0L;
                      { //slice 
                        const HashIndex_AGG1STORE1_L1_2_DELTA_map_1* i172 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1*>(AGG1STORE1_L1_2_DELTA.index[1]);
                        const HASH_RES_t h84 = AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::hash(se268.modify1(store_s_state));
                        HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode* n172 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_1::IdxNode*>(i172->slice(se268, h84));
                        AGG1STORE1_L1_2_DELTA_entry* e172;
                       
                        if (n172 && (e172 = n172->obj)) {
                          do {                
                            long store_sales_ss_store_sk = e172->STORE_SALES_SS_STORE_SK;
                            long v176 = e172->__av;
                            agg34 += (v176 * AGG1STORE1_L1_2.getValueOrDefault(se267.modify(item_i_item_id,store_sales_ss_store_sk)));
                            n172 = n172->nxt;
                          } while (n172 && (e172 = n172->obj) && h84 == n172->hash &&  AGG1STORE1_L1_2_DELTA_mapkey1_idxfn::equals(se268, *e172)); 
                        }
                      }long l26 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se266.modify(item_i_item_id,store_s_state)) + agg34);
                      (/*if */(0L != l26) ? agg33 += Udiv(Ulistmax(1L, l26)) : 0.0);
                      DOUBLE_TYPE agg35 = 0.0;
                      long l27 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se269.modify(item_i_item_id,store_s_state));
                      (/*if */(0L != l27) ? agg35 += Udiv(Ulistmax(1L, l27)) : 0.0);
                      (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? _c4.addOrDelOnZero(st7.modify(item_i_item_id,(v175 * (agg33 + (agg35 * -1L)))), (v175 * (agg33 + (agg35 * -1L)))) : (void)0);
                      n171 = n171->nxt;
                    } while (n171 && (e171 = n171->obj) && h85 == n171->hash &&  AGG4STORE1_P_2_mapkey0_idxfn::equals(se270, *e171)); 
                  }
                }{ //slice 
                  const HashIndex_AGG1STORE4_DELTA_map_1* i173 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1*>(AGG1STORE4_DELTA.index[1]);
                  const HASH_RES_t h87 = AGG1STORE4_DELTA_mapkey1_idxfn::hash(se275.modify1(store_s_state));
                  HashIndex_AGG1STORE4_DELTA_map_1::IdxNode* n173 = static_cast<HashIndex_AGG1STORE4_DELTA_map_1::IdxNode*>(i173->slice(se275, h87));
                  AGG1STORE4_DELTA_entry* e173;
                 
                  if (n173 && (e173 = n173->obj)) {
                    do {                
                      long store_sales_ss_store_sk = e173->STORE_SALES_SS_STORE_SK;
                      long v177 = e173->__av;
                      { //slice 
                        const HashIndex_AGG4STORE4_map_0* i174 = static_cast<HashIndex_AGG4STORE4_map_0*>(AGG4STORE4.index[1]);
                        const HASH_RES_t h86 = AGG4STORE4_mapkey0_idxfn::hash(se274.modify0(store_sales_ss_store_sk));
                        HashIndex_AGG4STORE4_map_0::IdxNode* n174 = static_cast<HashIndex_AGG4STORE4_map_0::IdxNode*>(i174->slice(se274, h86));
                        AGG4STORE4_entry* e174;
                       
                        if (n174 && (e174 = n174->obj)) {
                          do {                
                            STRING_TYPE item_i_item_id = e174->ITEM_I_ITEM_ID;
                            DOUBLE_TYPE v178 = e174->__av;
                            long agg36 = 0L;
                            agg36 += (AGG1STORE1_L1_2_DELTA.getValueOrDefault(se272.modify(store_sales_ss_store_sk,store_s_state)) * AGG1STORE1_L1_2.getValueOrDefault(se273.modify(item_i_item_id,store_sales_ss_store_sk)));
                            long l28 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se271.modify(item_i_item_id,store_s_state)) + agg36);
                            (/*if */(0L != l28) ? _c4.addOrDelOnZero(st8.modify(item_i_item_id,(v177 * (v178 * Udiv(Ulistmax(1L, l28))))), (v177 * (v178 * Udiv(Ulistmax(1L, l28))))) : (void)0);
                            n174 = n174->nxt;
                          } while (n174 && (e174 = n174->obj) && h86 == n174->hash &&  AGG4STORE4_mapkey0_idxfn::equals(se274, *e174)); 
                        }
                      }
                      n173 = n173->nxt;
                    } while (n173 && (e173 = n173->obj) && h87 == n173->hash &&  AGG1STORE4_DELTA_mapkey1_idxfn::equals(se275, *e173)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i175 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c4.index[0]);
                  HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n175; 
                  tuple2_S_D* e175;
                
                  for (size_t i = 0; i < i175->size_; i++)
                  {
                    n175 = i175->buckets_ + i;
                    while (n175 && (e175 = n175->obj))
                    {
                      STRING_TYPE item_i_item_id = e175->_1;  
                      DOUBLE_TYPE v179 = e175->__av; 
                    AGG4.addOrDelOnZero(se265.modify(item_i_item_id,store_s_state),((v173 != 0 ? 1L : 0L) * v179));      
                      n175 = n175->nxt;
                    }
                  }
                }
              n170 = n170->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i176 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n176; 
          AGG1STORE1_L1_2_DELTA_entry* e176;
        
          for (size_t i = 0; i < i176->size_; i++)
          {
            n176 = i176->buckets_ + i;
            while (n176 && (e176 = n176->obj))
            {
                long store_sales_ss_store_sk = e176->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e176->STORE_S_STATE;
                long v180 = e176->__av;
                { //slice 
                  const HashIndex_AGG1STORE1_L1_2_map_1* i177 = static_cast<HashIndex_AGG1STORE1_L1_2_map_1*>(AGG1STORE1_L1_2.index[1]);
                  const HASH_RES_t h88 = AGG1STORE1_L1_2_mapkey1_idxfn::hash(se277.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG1STORE1_L1_2_map_1::IdxNode* n177 = static_cast<HashIndex_AGG1STORE1_L1_2_map_1::IdxNode*>(i177->slice(se277, h88));
                  AGG1STORE1_L1_2_entry* e177;
                 
                  if (n177 && (e177 = n177->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e177->ITEM_I_ITEM_ID;
                      long v181 = e177->__av;
                      AGG1STORE_SALES1_L1_1.addOrDelOnZero(se276.modify(item_i_item_id,store_s_state),(v180 * v181));
                      n177 = n177->nxt;
                    } while (n177 && (e177 = n177->obj) && h88 == n177->hash &&  AGG1STORE1_L1_2_mapkey1_idxfn::equals(se277, *e177)); 
                  }
                }
              n176 = n176->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i178 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n178; 
          AGG1STORE4_DELTA_entry* e178;
        
          for (size_t i = 0; i < i178->size_; i++)
          {
            n178 = i178->buckets_ + i;
            while (n178 && (e178 = n178->obj))
            {
                long store_sales_ss_store_sk = e178->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e178->STORE_S_STATE;
                long v182 = e178->__av;
                { //slice 
                  const HashIndex_AGG4ITEM4STORE1_map_1* i179 = static_cast<HashIndex_AGG4ITEM4STORE1_map_1*>(AGG4ITEM4STORE1.index[2]);
                  const HASH_RES_t h89 = AGG4ITEM4STORE1_mapkey1_idxfn::hash(se279.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG4ITEM4STORE1_map_1::IdxNode* n179 = static_cast<HashIndex_AGG4ITEM4STORE1_map_1::IdxNode*>(i179->slice(se279, h89));
                  AGG4ITEM4STORE1_entry* e179;
                 
                  if (n179 && (e179 = n179->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e179->STORE_SALES_SS_ITEM_SK;
                      DOUBLE_TYPE v183 = e179->__av;
                      AGG4ITEM4.addOrDelOnZero(se278.modify(store_sales_ss_item_sk,store_s_state),(v182 * v183));
                      n179 = n179->nxt;
                    } while (n179 && (e179 = n179->obj) && h89 == n179->hash &&  AGG4ITEM4STORE1_mapkey1_idxfn::equals(se279, *e179)); 
                  }
                }
              n178 = n178->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i180 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n180; 
          AGG1STORE1_L1_2_DELTA_entry* e180;
        
          for (size_t i = 0; i < i180->size_; i++)
          {
            n180 = i180->buckets_ + i;
            while (n180 && (e180 = n180->obj))
            {
                long store_sales_ss_store_sk = e180->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e180->STORE_S_STATE;
                long v184 = e180->__av;
                { //slice 
                  const HashIndex_AGG4STORE4_map_0* i181 = static_cast<HashIndex_AGG4STORE4_map_0*>(AGG4STORE4.index[1]);
                  const HASH_RES_t h90 = AGG4STORE4_mapkey0_idxfn::hash(se281.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG4STORE4_map_0::IdxNode* n181 = static_cast<HashIndex_AGG4STORE4_map_0::IdxNode*>(i181->slice(se281, h90));
                  AGG4STORE4_entry* e181;
                 
                  if (n181 && (e181 = n181->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e181->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v185 = e181->__av;
                      AGG4STORE1_P_2.addOrDelOnZero(se280.modify(store_s_state,item_i_item_id),(v184 * v185));
                      n181 = n181->nxt;
                    } while (n181 && (e181 = n181->obj) && h90 == n181->hash &&  AGG4STORE4_mapkey0_idxfn::equals(se281, *e181)); 
                  }
                }
              n180 = n180->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE1_L1_2_DELTA_map_01* i182 = static_cast<HashIndex_AGG1STORE1_L1_2_DELTA_map_01*>(AGG1STORE1_L1_2_DELTA.index[0]);
          HashIndex_AGG1STORE1_L1_2_DELTA_map_01::IdxNode* n182; 
          AGG1STORE1_L1_2_DELTA_entry* e182;
        
          for (size_t i = 0; i < i182->size_; i++)
          {
            n182 = i182->buckets_ + i;
            while (n182 && (e182 = n182->obj))
            {
                long store_sales_ss_store_sk = e182->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e182->STORE_S_STATE;
                long v186 = e182->__av;
                { //slice 
                  const HashIndex_AGG4ITEM4STORE1_map_1* i183 = static_cast<HashIndex_AGG4ITEM4STORE1_map_1*>(AGG4ITEM4STORE1.index[2]);
                  const HASH_RES_t h91 = AGG4ITEM4STORE1_mapkey1_idxfn::hash(se283.modify1(store_sales_ss_store_sk));
                  HashIndex_AGG4ITEM4STORE1_map_1::IdxNode* n183 = static_cast<HashIndex_AGG4ITEM4STORE1_map_1::IdxNode*>(i183->slice(se283, h91));
                  AGG4ITEM4STORE1_entry* e183;
                 
                  if (n183 && (e183 = n183->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e183->STORE_SALES_SS_ITEM_SK;
                      DOUBLE_TYPE v187 = e183->__av;
                      AGG4STORE1_P_2ITEM1.addOrDelOnZero(se282.modify(store_s_state,store_sales_ss_item_sk),(v186 * v187));
                      n183 = n183->nxt;
                    } while (n183 && (e183 = n183->obj) && h91 == n183->hash &&  AGG4ITEM4STORE1_mapkey1_idxfn::equals(se283, *e183)); 
                  }
                }
              n182 = n182->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1STORE4_DELTA_map_01* i184 = static_cast<HashIndex_AGG1STORE4_DELTA_map_01*>(AGG1STORE4_DELTA.index[0]);
          HashIndex_AGG1STORE4_DELTA_map_01::IdxNode* n184; 
          AGG1STORE4_DELTA_entry* e184;
        
          for (size_t i = 0; i < i184->size_; i++)
          {
            n184 = i184->buckets_ + i;
            while (n184 && (e184 = n184->obj))
            {
                long store_sales_ss_store_sk = e184->STORE_SALES_SS_STORE_SK;
                STRING_TYPE store_s_state = e184->STORE_S_STATE;
                long v188 = e184->__av;
                { //slice 
                  const HashIndex_AGG4STORE4_map_0* i185 = static_cast<HashIndex_AGG4STORE4_map_0*>(AGG4STORE4.index[1]);
                  const HASH_RES_t h92 = AGG4STORE4_mapkey0_idxfn::hash(se285.modify0(store_sales_ss_store_sk));
                  HashIndex_AGG4STORE4_map_0::IdxNode* n185 = static_cast<HashIndex_AGG4STORE4_map_0::IdxNode*>(i185->slice(se285, h92));
                  AGG4STORE4_entry* e185;
                 
                  if (n185 && (e185 = n185->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e185->ITEM_I_ITEM_ID;
                      DOUBLE_TYPE v189 = e185->__av;
                      AGG4STORE_SALES1.addOrDelOnZero(se284.modify(store_s_state,item_i_item_id),(v188 * v189));
                      n185 = n185->nxt;
                    } while (n185 && (e185 = n185->obj) && h92 == n185->hash &&  AGG4STORE4_mapkey0_idxfn::equals(se285, *e185)); 
                  }
                }
              n184 = n184->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        AGG1ITEM1_L1_2STORE_SALES1_P_1.clear();
        long l29 = 2002L;
        { //slice 
          const HashIndex_DATE_DIM_map_6* i186 = static_cast<HashIndex_DATE_DIM_map_6*>(DATE_DIM.index[1]);
          const HASH_RES_t h93 = DATE_DIM_mapkey6_idxfn::hash(se287.modify6(l29));
          HashIndex_DATE_DIM_map_6::IdxNode* n186 = static_cast<HashIndex_DATE_DIM_map_6::IdxNode*>(i186->slice(se287, h93));
          DATE_DIM_entry* e186;
         
          if (n186 && (e186 = n186->obj)) {
            do {                
              long store_sales_ss_sold_date_sk = e186->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e186->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e186->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e186->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e186->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e186->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e186->DATE_DIM_D_DOW;
              long date_dim_d_moy = e186->DATE_DIM_D_MOY;
              long date_dim_d_dom = e186->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e186->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e186->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e186->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e186->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_day_name = e186->DATE_DIM_D_DAY_NAME;
              STRING_TYPE date_dim_d_quarter_name = e186->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e186->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e186->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e186->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e186->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e186->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e186->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e186->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e186->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e186->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e186->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e186->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e186->DATE_DIM_D_CURRENT_YEAR;
              long v190 = e186->__av;
              AGG1ITEM1_L1_2STORE_SALES1_P_1.addOrDelOnZero(se286.modify(store_sales_ss_sold_date_sk),v190);
              n186 = n186->nxt;
            } while (n186 && (e186 = n186->obj) && h93 == n186->hash &&  DATE_DIM_mapkey6_idxfn::equals(se287, *e186)); 
          }
        }AGG1ITEM1_L1_2STORE_SALES1_P_2.clear();
        STRING_TYPE l30 = c7;
        STRING_TYPE l31 = c8;
        STRING_TYPE l32 = c9;
        { //slice 
          const HashIndex_CUSTOMER_DEMOGRAPHICS_map_123* i187 = static_cast<HashIndex_CUSTOMER_DEMOGRAPHICS_map_123*>(CUSTOMER_DEMOGRAPHICS.index[1]);
          const HASH_RES_t h94 = CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn::hash(se289.modify123(l32, l31, l30));
          HashIndex_CUSTOMER_DEMOGRAPHICS_map_123::IdxNode* n187 = static_cast<HashIndex_CUSTOMER_DEMOGRAPHICS_map_123::IdxNode*>(i187->slice(se289, h94));
          CUSTOMER_DEMOGRAPHICS_entry* e187;
         
          if (n187 && (e187 = n187->obj)) {
            do {                
              long store_sales_ss_cdemo_sk = e187->CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK;
              long customer_demographics_cd_purchase_estimate = e187->CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE;
              STRING_TYPE customer_demographics_cd_credit_rating = e187->CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING;
              long customer_demographics_cd_dep_count = e187->CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT;
              long customer_demographics_cd_dep_employed_count = e187->CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT;
              long customer_demographics_cd_dep_college_count = e187->CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT;
              long v191 = e187->__av;
              AGG1ITEM1_L1_2STORE_SALES1_P_2.addOrDelOnZero(se288.modify(store_sales_ss_cdemo_sk),v191);
              n187 = n187->nxt;
            } while (n187 && (e187 = n187->obj) && h94 == n187->hash &&  CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn::equals(se289, *e187)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    AGG1ITEM1_L1_2STORE_SALES1_DELTA_entry se1;
    AGG1ITEM4STORE_SALES1_DELTA_entry se2;
    AGG2ITEM4STORE_SALES1_DELTA_entry se3;
    AGG3ITEM4STORE_SALES1_DELTA_entry se4;
    AGG4ITEM4STORE_SALES1_DELTA_entry se5;
    AGG1ITEM1_L1_2_entry se6;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se7;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se8;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se9;
    AGG1ITEM1_L1_2STORE1_entry se10;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se11;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se12;
    AGG1ITEM4_entry se13;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se14;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se15;
    AGG1ITEM4STORE_SALES1_P_3_entry se16;
    AGG1ITEM4STORE1_entry se17;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se18;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se19;
    AGG1STORE1_P_2_entry se20;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se21;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se22;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se23;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se24;
    AGG1STORE1_P_2ITEM1_entry se25;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se26;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se27;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se28;
    AGG1STORE1_L1_2_entry se29;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se30;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se31;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se32;
    AGG1STORE4_entry se33;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se34;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se35;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se36;
    AGG1STORE_SALES1_entry se37;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se38;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se39;
    AGG1ITEM4STORE_SALES1_P_3_entry se40;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se41;
    AGG1STORE_SALES1_L1_1_entry se42;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se43;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se44;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se45;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se46;
    AGG2ITEM4_entry se47;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se48;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se49;
    AGG1ITEM4STORE_SALES1_P_3_entry se50;
    AGG2ITEM4STORE1_entry se51;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se52;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se53;
    AGG2STORE1_P_2_entry se54;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se55;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se56;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se57;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se58;
    AGG2STORE1_P_2ITEM1_entry se59;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se60;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se61;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se62;
    AGG2STORE4_entry se63;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se64;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se65;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se66;
    AGG2STORE_SALES1_entry se67;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se68;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se69;
    AGG1ITEM4STORE_SALES1_P_3_entry se70;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se71;
    AGG3ITEM4_entry se72;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se73;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se74;
    AGG1ITEM4STORE_SALES1_P_3_entry se75;
    AGG3ITEM4STORE1_entry se76;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se77;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se78;
    AGG3STORE1_P_2_entry se79;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se80;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se81;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se82;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se83;
    AGG3STORE1_P_2ITEM1_entry se84;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se85;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se86;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se87;
    AGG3STORE4_entry se88;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se89;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se90;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se91;
    AGG3STORE_SALES1_entry se92;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se93;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se94;
    AGG1ITEM4STORE_SALES1_P_3_entry se95;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se96;
    AGG4ITEM4_entry se97;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se98;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se99;
    AGG1ITEM4STORE_SALES1_P_3_entry se100;
    AGG4ITEM4STORE1_entry se101;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se102;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se103;
    AGG4STORE1_P_2_entry se104;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se105;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se106;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se107;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se108;
    AGG4STORE1_P_2ITEM1_entry se109;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se110;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se111;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se112;
    AGG4STORE4_entry se113;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se114;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se115;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se116;
    AGG4STORE_SALES1_entry se117;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se118;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se119;
    AGG1ITEM4STORE_SALES1_P_3_entry se120;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se121;
    AGG1_entry se122;
    AGG1STORE_SALES1_L1_1_entry se123;
    AGG2_entry se124;
    AGG1STORE_SALES1_L1_1_entry se125;
    AGG3_entry se126;
    AGG1STORE_SALES1_L1_1_entry se127;
    AGG4_entry se128;
    AGG1STORE_SALES1_L1_1_entry se129;
    AGG1ITEM1_L1_2_DELTA_entry se130;
    AGG1ITEM1_DOMAIN1_entry se131;
    AGG1_entry se132;
    AGG1STORE_SALES1_L1_1_entry se133;
    AGG1ITEM1_L1_2_entry se134;
    AGG1ITEM1_L1_2_DELTA_entry se135;
    AGG1STORE_SALES1_L1_1_entry se136;
    AGG1STORE_SALES1_entry se137;
    AGG1STORE_SALES1_L1_1_entry se138;
    AGG1ITEM1_L1_2_DELTA_entry se139;
    AGG1ITEM1_L1_2_entry se140;
    AGG1ITEM4_entry se141;
    AGG1STORE1_P_2_entry se142;
    AGG1STORE1_P_2ITEM1_entry se143;
    AGG1STORE1_P_2STORE_SALES1_P_3_entry se144;
    AGG1STORE1_L1_2_entry se145;
    AGG1ITEM1_L1_2STORE1_entry se146;
    AGG1STORE4_entry se147;
    AGG1ITEM4STORE1_entry se148;
    AGG1STORE_SALES1_entry se149;
    AGG1ITEM4_entry se150;
    AGG2_entry se151;
    AGG1STORE_SALES1_L1_1_entry se152;
    AGG1ITEM1_L1_2_entry se153;
    AGG1ITEM1_L1_2_DELTA_entry se154;
    AGG1STORE_SALES1_L1_1_entry se155;
    AGG2STORE_SALES1_entry se156;
    AGG1STORE_SALES1_L1_1_entry se157;
    AGG1ITEM1_L1_2_DELTA_entry se158;
    AGG1ITEM1_L1_2_entry se159;
    AGG2ITEM4_entry se160;
    AGG2STORE1_P_2_entry se161;
    AGG2STORE1_P_2ITEM1_entry se162;
    AGG2STORE4_entry se163;
    AGG2ITEM4STORE1_entry se164;
    AGG2STORE_SALES1_entry se165;
    AGG2ITEM4_entry se166;
    AGG3_entry se167;
    AGG1STORE_SALES1_L1_1_entry se168;
    AGG1ITEM1_L1_2_entry se169;
    AGG1ITEM1_L1_2_DELTA_entry se170;
    AGG1STORE_SALES1_L1_1_entry se171;
    AGG3STORE_SALES1_entry se172;
    AGG1STORE_SALES1_L1_1_entry se173;
    AGG1ITEM1_L1_2_DELTA_entry se174;
    AGG1ITEM1_L1_2_entry se175;
    AGG3ITEM4_entry se176;
    AGG3STORE1_P_2_entry se177;
    AGG3STORE1_P_2ITEM1_entry se178;
    AGG3STORE4_entry se179;
    AGG3ITEM4STORE1_entry se180;
    AGG3STORE_SALES1_entry se181;
    AGG3ITEM4_entry se182;
    AGG4_entry se183;
    AGG1STORE_SALES1_L1_1_entry se184;
    AGG1ITEM1_L1_2_entry se185;
    AGG1ITEM1_L1_2_DELTA_entry se186;
    AGG1STORE_SALES1_L1_1_entry se187;
    AGG4STORE_SALES1_entry se188;
    AGG1STORE_SALES1_L1_1_entry se189;
    AGG1ITEM1_L1_2_DELTA_entry se190;
    AGG1ITEM1_L1_2_entry se191;
    AGG4ITEM4_entry se192;
    AGG1STORE_SALES1_L1_1_entry se193;
    AGG1ITEM1_L1_2_entry se194;
    AGG4STORE1_P_2_entry se195;
    AGG4STORE1_P_2ITEM1_entry se196;
    AGG4STORE4_entry se197;
    AGG4ITEM4STORE1_entry se198;
    AGG4STORE_SALES1_entry se199;
    AGG4ITEM4_entry se200;
    AGG1STORE4_DELTA_entry se201;
    AGG1STORE1_L1_2_DELTA_entry se202;
    AGG1STORE1_DOMAIN1_entry se203;
    AGG1_entry se204;
    AGG1STORE_SALES1_L1_1_entry se205;
    AGG1STORE1_L1_2_entry se206;
    AGG1STORE1_L1_2_DELTA_entry se207;
    AGG1STORE_SALES1_L1_1_entry se208;
    tuple2_S_D st1;
    AGG1STORE1_P_2_entry se209;
    AGG1STORE_SALES1_L1_1_entry se210;
    AGG1STORE1_L1_2_DELTA_entry se211;
    AGG1STORE1_L1_2_entry se212;
    tuple2_S_D st2;
    AGG1STORE4_entry se213;
    AGG1STORE4_DELTA_entry se214;
    AGG1ITEM1_L1_2_entry se215;
    AGG1ITEM1_L1_2STORE1_entry se216;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_entry se217;
    AGG1ITEM4_entry se218;
    AGG1ITEM4STORE1_entry se219;
    AGG1ITEM4STORE_SALES1_P_3_entry se220;
    AGG1STORE1_P_2_entry se221;
    AGG1STORE4_entry se222;
    AGG1STORE1_P_2ITEM1_entry se223;
    AGG1ITEM4STORE1_entry se224;
    AGG1STORE_SALES1_entry se225;
    AGG1STORE4_entry se226;
    AGG2_entry se227;
    AGG1STORE_SALES1_L1_1_entry se228;
    AGG1STORE1_L1_2_entry se229;
    AGG1STORE1_L1_2_DELTA_entry se230;
    AGG1STORE_SALES1_L1_1_entry se231;
    tuple2_S_D st3;
    AGG2STORE1_P_2_entry se232;
    AGG1STORE_SALES1_L1_1_entry se233;
    AGG1STORE1_L1_2_DELTA_entry se234;
    AGG1STORE1_L1_2_entry se235;
    tuple2_S_D st4;
    AGG2STORE4_entry se236;
    AGG1STORE4_DELTA_entry se237;
    AGG2ITEM4_entry se238;
    AGG2ITEM4STORE1_entry se239;
    AGG2STORE1_P_2_entry se240;
    AGG2STORE4_entry se241;
    AGG2STORE1_P_2ITEM1_entry se242;
    AGG2ITEM4STORE1_entry se243;
    AGG2STORE_SALES1_entry se244;
    AGG2STORE4_entry se245;
    AGG3_entry se246;
    AGG1STORE_SALES1_L1_1_entry se247;
    AGG1STORE1_L1_2_entry se248;
    AGG1STORE1_L1_2_DELTA_entry se249;
    AGG1STORE_SALES1_L1_1_entry se250;
    tuple2_S_D st5;
    AGG3STORE1_P_2_entry se251;
    AGG1STORE_SALES1_L1_1_entry se252;
    AGG1STORE1_L1_2_DELTA_entry se253;
    AGG1STORE1_L1_2_entry se254;
    tuple2_S_D st6;
    AGG3STORE4_entry se255;
    AGG1STORE4_DELTA_entry se256;
    AGG3ITEM4_entry se257;
    AGG3ITEM4STORE1_entry se258;
    AGG3STORE1_P_2_entry se259;
    AGG3STORE4_entry se260;
    AGG3STORE1_P_2ITEM1_entry se261;
    AGG3ITEM4STORE1_entry se262;
    AGG3STORE_SALES1_entry se263;
    AGG3STORE4_entry se264;
    AGG4_entry se265;
    AGG1STORE_SALES1_L1_1_entry se266;
    AGG1STORE1_L1_2_entry se267;
    AGG1STORE1_L1_2_DELTA_entry se268;
    AGG1STORE_SALES1_L1_1_entry se269;
    tuple2_S_D st7;
    AGG4STORE1_P_2_entry se270;
    AGG1STORE_SALES1_L1_1_entry se271;
    AGG1STORE1_L1_2_DELTA_entry se272;
    AGG1STORE1_L1_2_entry se273;
    tuple2_S_D st8;
    AGG4STORE4_entry se274;
    AGG1STORE4_DELTA_entry se275;
    AGG1STORE_SALES1_L1_1_entry se276;
    AGG1STORE1_L1_2_entry se277;
    AGG4ITEM4_entry se278;
    AGG4ITEM4STORE1_entry se279;
    AGG4STORE1_P_2_entry se280;
    AGG4STORE4_entry se281;
    AGG4STORE1_P_2ITEM1_entry se282;
    AGG4ITEM4STORE1_entry se283;
    AGG4STORE_SALES1_entry se284;
    AGG4STORE4_entry se285;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_entry se286;
    DATE_DIM_entry se287;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_entry se288;
    CUSTOMER_DEMOGRAPHICS_entry se289;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    CUSTOMER_DEMOGRAPHICS_map CUSTOMER_DEMOGRAPHICS;
    AGG1ITEM1_DOMAIN1_map AGG1ITEM1_DOMAIN1;
    AGG1ITEM1_L1_2_DELTA_map AGG1ITEM1_L1_2_DELTA;
    AGG1ITEM1_L1_2_map AGG1ITEM1_L1_2;
    AGG1ITEM1_L1_2STORE_SALES1_DELTA_map AGG1ITEM1_L1_2STORE_SALES1_DELTA;
    AGG1ITEM1_L1_2STORE_SALES1_P_1_map AGG1ITEM1_L1_2STORE_SALES1_P_1;
    AGG1ITEM1_L1_2STORE_SALES1_P_2_map AGG1ITEM1_L1_2STORE_SALES1_P_2;
    AGG1ITEM1_L1_2STORE_SALES1_P_3_map AGG1ITEM1_L1_2STORE_SALES1_P_3;
    AGG1ITEM1_L1_2STORE1_map AGG1ITEM1_L1_2STORE1;
    AGG1ITEM4_map AGG1ITEM4;
    AGG1ITEM4STORE1_map AGG1ITEM4STORE1;
    AGG1ITEM4STORE_SALES1_DELTA_map AGG1ITEM4STORE_SALES1_DELTA;
    AGG1ITEM4STORE_SALES1_P_3_map AGG1ITEM4STORE_SALES1_P_3;
    AGG1STORE1_DOMAIN1_map AGG1STORE1_DOMAIN1;
    AGG1STORE1_P_2_map AGG1STORE1_P_2;
    AGG1STORE1_P_2ITEM1_map AGG1STORE1_P_2ITEM1;
    AGG1STORE1_P_2STORE_SALES1_P_3_map AGG1STORE1_P_2STORE_SALES1_P_3;
    AGG1STORE1_L1_2_DELTA_map AGG1STORE1_L1_2_DELTA;
    AGG1STORE1_L1_2_map AGG1STORE1_L1_2;
    AGG1STORE4_DELTA_map AGG1STORE4_DELTA;
    AGG1STORE4_map AGG1STORE4;
    AGG1STORE_SALES1_map AGG1STORE_SALES1;
    AGG1STORE_SALES1_L1_1_map AGG1STORE_SALES1_L1_1;
    AGG2ITEM4_map AGG2ITEM4;
    AGG2ITEM4STORE1_map AGG2ITEM4STORE1;
    AGG2ITEM4STORE_SALES1_DELTA_map AGG2ITEM4STORE_SALES1_DELTA;
    AGG2STORE1_P_2_map AGG2STORE1_P_2;
    AGG2STORE1_P_2ITEM1_map AGG2STORE1_P_2ITEM1;
    AGG2STORE4_map AGG2STORE4;
    AGG2STORE_SALES1_map AGG2STORE_SALES1;
    AGG3ITEM4_map AGG3ITEM4;
    AGG3ITEM4STORE1_map AGG3ITEM4STORE1;
    AGG3ITEM4STORE_SALES1_DELTA_map AGG3ITEM4STORE_SALES1_DELTA;
    AGG3STORE1_P_2_map AGG3STORE1_P_2;
    AGG3STORE1_P_2ITEM1_map AGG3STORE1_P_2ITEM1;
    AGG3STORE4_map AGG3STORE4;
    AGG3STORE_SALES1_map AGG3STORE_SALES1;
    AGG4ITEM4_map AGG4ITEM4;
    AGG4ITEM4STORE1_map AGG4ITEM4STORE1;
    AGG4ITEM4STORE_SALES1_DELTA_map AGG4ITEM4STORE_SALES1_DELTA;
    AGG4STORE1_P_2_map AGG4STORE1_P_2;
    AGG4STORE1_P_2ITEM1_map AGG4STORE1_P_2ITEM1;
    AGG4STORE4_map AGG4STORE4;
    AGG4STORE_SALES1_map AGG4STORE_SALES1;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_ITEM_map DELTA_ITEM;
    DELTA_STORE_map DELTA_STORE;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c1;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c4;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c3;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c2;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c9;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c8;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c1;
  
  };

}
