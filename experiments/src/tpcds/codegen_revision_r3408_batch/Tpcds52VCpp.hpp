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
    long DT_D_YEAR; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICE_entry() { /*DT_D_YEAR = 0L; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICE_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { DT_D_YEAR = c0; BRAND_ID = c1; BRAND = c2; __av = c3; }
    EXT_PRICE_entry(const EXT_PRICE_entry& other) : DT_D_YEAR( other.DT_D_YEAR ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICE_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { DT_D_YEAR = c0; BRAND_ID = c1; BRAND = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICE_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DT_D_YEAR);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICE_entry& x, const EXT_PRICE_entry& y) {
      return x.DT_D_YEAR == y.DT_D_YEAR && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  typedef MultiHashMap<EXT_PRICE_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICE_entry,DOUBLE_TYPE,EXT_PRICE_mapkey012_idxfn,true>
  > EXT_PRICE_map;
  typedef HashIndex<EXT_PRICE_entry,DOUBLE_TYPE,EXT_PRICE_mapkey012_idxfn,true> HashIndex_EXT_PRICE_map_012;
  
  struct EXT_PRICEITEM1_DELTA_entry {
    long STORE_SALES_SS_ITEM_SK; long BRAND_ID; STRING_TYPE BRAND; long __av; 
    explicit EXT_PRICEITEM1_DELTA_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; BRAND_ID = 0L; BRAND = ""; __av = 0L; */ }
    explicit EXT_PRICEITEM1_DELTA_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3) { STORE_SALES_SS_ITEM_SK = c0; BRAND_ID = c1; BRAND = c2; __av = c3; }
    EXT_PRICEITEM1_DELTA_entry(const EXT_PRICEITEM1_DELTA_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICEITEM1_DELTA_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { STORE_SALES_SS_ITEM_SK = c0; BRAND_ID = c1; BRAND = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICEITEM1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICEITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICEITEM1_DELTA_entry& x, const EXT_PRICEITEM1_DELTA_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  typedef MultiHashMap<EXT_PRICEITEM1_DELTA_entry,long,
    HashIndex<EXT_PRICEITEM1_DELTA_entry,long,EXT_PRICEITEM1_DELTA_mapkey012_idxfn,true>
  > EXT_PRICEITEM1_DELTA_map;
  typedef HashIndex<EXT_PRICEITEM1_DELTA_entry,long,EXT_PRICEITEM1_DELTA_mapkey012_idxfn,true> HashIndex_EXT_PRICEITEM1_DELTA_map_012;
  
  struct EXT_PRICEITEM1_entry {
    long DT_D_YEAR; long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICEITEM1_entry() { /*DT_D_YEAR = 0L; STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICEITEM1_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { DT_D_YEAR = c0; STORE_SALES_SS_ITEM_SK = c1; __av = c2; }
    EXT_PRICEITEM1_entry(const EXT_PRICEITEM1_entry& other) : DT_D_YEAR( other.DT_D_YEAR ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICEITEM1_entry& modify(const long c0, const long c1) { DT_D_YEAR = c0; STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    FORCE_INLINE EXT_PRICEITEM1_entry& modify1(const long c1) { STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICEITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICEITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DT_D_YEAR);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICEITEM1_entry& x, const EXT_PRICEITEM1_entry& y) {
      return x.DT_D_YEAR == y.DT_D_YEAR && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  struct EXT_PRICEITEM1_mapkey1_idxfn {
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
    HashIndex<EXT_PRICEITEM1_entry,DOUBLE_TYPE,EXT_PRICEITEM1_mapkey01_idxfn,true>,
    HashIndex<EXT_PRICEITEM1_entry,DOUBLE_TYPE,EXT_PRICEITEM1_mapkey1_idxfn,false>
  > EXT_PRICEITEM1_map;
  typedef HashIndex<EXT_PRICEITEM1_entry,DOUBLE_TYPE,EXT_PRICEITEM1_mapkey01_idxfn,true> HashIndex_EXT_PRICEITEM1_map_01;
  typedef HashIndex<EXT_PRICEITEM1_entry,DOUBLE_TYPE,EXT_PRICEITEM1_mapkey1_idxfn,false> HashIndex_EXT_PRICEITEM1_map_1;
  
  struct EXT_PRICESTORE_SALES1_DELTA_entry {
    long DT_D_DATE_SK; long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICESTORE_SALES1_DELTA_entry() { /*DT_D_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICESTORE_SALES1_DELTA_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { DT_D_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; __av = c2; }
    EXT_PRICESTORE_SALES1_DELTA_entry(const EXT_PRICESTORE_SALES1_DELTA_entry& other) : DT_D_DATE_SK( other.DT_D_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_DELTA_entry& modify(const long c0, const long c1) { DT_D_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DT_D_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_DELTA_entry& x, const EXT_PRICESTORE_SALES1_DELTA_entry& y) {
      return x.DT_D_DATE_SK == y.DT_D_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICESTORE_SALES1_DELTA_entry,DOUBLE_TYPE,EXT_PRICESTORE_SALES1_DELTA_mapkey01_idxfn,true>
  > EXT_PRICESTORE_SALES1_DELTA_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_DELTA_entry,DOUBLE_TYPE,EXT_PRICESTORE_SALES1_DELTA_mapkey01_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_01;
  
  struct EXT_PRICESTORE_SALES1_P_1_entry {
    long DT_D_DATE_SK; long DT_D_YEAR; long __av; 
    explicit EXT_PRICESTORE_SALES1_P_1_entry() { /*DT_D_DATE_SK = 0L; DT_D_YEAR = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES1_P_1_entry(const long c0, const long c1, const long c2) { DT_D_DATE_SK = c0; DT_D_YEAR = c1; __av = c2; }
    EXT_PRICESTORE_SALES1_P_1_entry(const EXT_PRICESTORE_SALES1_P_1_entry& other) : DT_D_DATE_SK( other.DT_D_DATE_SK ), DT_D_YEAR( other.DT_D_YEAR ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_1_entry& modify(const long c0, const long c1) { DT_D_DATE_SK = c0; DT_D_YEAR = c1;  return *this; }
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_1_entry& modify0(const long c0) { DT_D_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_P_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DT_D_DATE_SK);
      hash_combine(h, e.DT_D_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_1_entry& x, const EXT_PRICESTORE_SALES1_P_1_entry& y) {
      return x.DT_D_DATE_SK == y.DT_D_DATE_SK && x.DT_D_YEAR == y.DT_D_YEAR;
    }
  };
  
  struct EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DT_D_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_1_entry& x, const EXT_PRICESTORE_SALES1_P_1_entry& y) {
      return x.DT_D_DATE_SK == y.DT_D_DATE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_P_1_entry,long,
    HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey01_idxfn,true>,
    HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn,false>
  > EXT_PRICESTORE_SALES1_P_1_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey01_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_P_1_map_01;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_1_entry,long,EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0;
  
  struct EXT_PRICESTORE_SALES1_P_2_entry {
    long STORE_SALES_SS_ITEM_SK; long BRAND_ID; STRING_TYPE BRAND; long __av; 
    explicit EXT_PRICESTORE_SALES1_P_2_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; BRAND_ID = 0L; BRAND = ""; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES1_P_2_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3) { STORE_SALES_SS_ITEM_SK = c0; BRAND_ID = c1; BRAND = c2; __av = c3; }
    EXT_PRICESTORE_SALES1_P_2_entry(const EXT_PRICESTORE_SALES1_P_2_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_2_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { STORE_SALES_SS_ITEM_SK = c0; BRAND_ID = c1; BRAND = c2;  return *this; }
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_2_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_P_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_2_entry& x, const EXT_PRICESTORE_SALES1_P_2_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  struct EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_2_entry& x, const EXT_PRICESTORE_SALES1_P_2_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_P_2_entry,long,
    HashIndex<EXT_PRICESTORE_SALES1_P_2_entry,long,EXT_PRICESTORE_SALES1_P_2_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICESTORE_SALES1_P_2_entry,long,EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn,false>
  > EXT_PRICESTORE_SALES1_P_2_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_2_entry,long,EXT_PRICESTORE_SALES1_P_2_mapkey012_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_P_2_map_012;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_2_entry,long,EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE_SALES1_P_2_map_0;
  
  struct EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE BRAND; long BRAND_ID; long __av; 
    explicit EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; BRAND = ""; BRAND_ID = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3) { STORE_SALES_SS_ITEM_SK = c0; BRAND = c1; BRAND_ID = c2; __av = c3; }
    EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry(const EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), BRAND( other.BRAND ), BRAND_ID( other.BRAND_ID ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; BRAND = c1; BRAND_ID = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.BRAND);
      hash_combine(h, e.BRAND_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry& x, const EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.BRAND == y.BRAND && x.BRAND_ID == y.BRAND_ID;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry,long,
    HashIndex<EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry,long,EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_mapkey012_idxfn,true>
  > EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry,long,EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_mapkey012_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_map_012;
  
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
    data_t(): tlq_t(), agg1(16U) {
      
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
                long dt_d_date_sk = DELTA_STORE_SALES.ss_sold_date_sk[i];
                // long store_sales_ss_sold_time_sk = DELTA_STORE_SALES.ss_sold_time_sk[i];
                long store_sales_ss_item_sk = DELTA_STORE_SALES.ss_item_sk[i];
                // long store_sales_ss_customer_sk = DELTA_STORE_SALES.ss_customer_sk[i];
                // long store_sales_ss_cdemo_sk = DELTA_STORE_SALES.ss_cdemo_sk[i];
                // long store_sales_ss_hdemo_sk = DELTA_STORE_SALES.ss_hdemo_sk[i];
                // long store_sales_ss_addr_sk = DELTA_STORE_SALES.ss_addr_sk[i];
                // long store_sales_ss_store_sk = DELTA_STORE_SALES.ss_store_sk[i];
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
                EXT_PRICESTORE_SALES1_DELTA.addOrDelOnZero(se1.modify(dt_d_date_sk,store_sales_ss_item_sk),(v1 * store_sales_ss_ext_sales_price));
          }
        }

        {  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_01* i2 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_01*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_01::IdxNode* n2; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e2;
        
          for (size_t i = 0; i < i2->size_; i++)
          {
            n2 = i2->buckets_ + i;
            while (n2 && (e2 = n2->obj))
            {
                long dt_d_date_sk = e2->DT_D_DATE_SK;
                long store_sales_ss_item_sk = e2->STORE_SALES_SS_ITEM_SK;
                DOUBLE_TYPE v2 = e2->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0* i3 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0*>(EXT_PRICESTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h2 = EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn::hash(se4.modify0(dt_d_date_sk));
                  HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0::IdxNode* n3 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0::IdxNode*>(i3->slice(se4, h2));
                  EXT_PRICESTORE_SALES1_P_1_entry* e3;
                 
                  if (n3 && (e3 = n3->obj)) {
                    do {                
                      long dt_d_year = e3->DT_D_YEAR;
                      long v3 = e3->__av;
                      { //slice 
                        const HashIndex_EXT_PRICESTORE_SALES1_P_2_map_0* i4 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_2_map_0*>(EXT_PRICESTORE_SALES1_P_2.index[1]);
                        const HASH_RES_t h1 = EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn::hash(se3.modify0(store_sales_ss_item_sk));
                        HashIndex_EXT_PRICESTORE_SALES1_P_2_map_0::IdxNode* n4 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_2_map_0::IdxNode*>(i4->slice(se3, h1));
                        EXT_PRICESTORE_SALES1_P_2_entry* e4;
                       
                        if (n4 && (e4 = n4->obj)) {
                          do {                
                            long brand_id = e4->BRAND_ID;
                            STRING_TYPE brand = e4->BRAND;
                            long v4 = e4->__av;
                            EXT_PRICE.addOrDelOnZero(se2.modify(dt_d_year,brand_id,brand),(v2 * (v3 * v4)));
                            n4 = n4->nxt;
                          } while (n4 && (e4 = n4->obj) && h1 == n4->hash &&  EXT_PRICESTORE_SALES1_P_2_mapkey0_idxfn::equals(se3, *e4)); 
                        }
                      }
                      n3 = n3->nxt;
                    } while (n3 && (e3 = n3->obj) && h2 == n3->hash &&  EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn::equals(se4, *e3)); 
                  }
                }
              n2 = n2->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_01* i5 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_01*>(EXT_PRICESTORE_SALES1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_DELTA_map_01::IdxNode* n5; 
          EXT_PRICESTORE_SALES1_DELTA_entry* e5;
        
          for (size_t i = 0; i < i5->size_; i++)
          {
            n5 = i5->buckets_ + i;
            while (n5 && (e5 = n5->obj))
            {
                long dt_d_date_sk = e5->DT_D_DATE_SK;
                long store_sales_ss_item_sk = e5->STORE_SALES_SS_ITEM_SK;
                DOUBLE_TYPE v5 = e5->__av;
                { //slice 
                  const HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0* i6 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0*>(EXT_PRICESTORE_SALES1_P_1.index[1]);
                  const HASH_RES_t h3 = EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn::hash(se6.modify0(dt_d_date_sk));
                  HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0::IdxNode* n6 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_1_map_0::IdxNode*>(i6->slice(se6, h3));
                  EXT_PRICESTORE_SALES1_P_1_entry* e6;
                 
                  if (n6 && (e6 = n6->obj)) {
                    do {                
                      long dt_d_year = e6->DT_D_YEAR;
                      long v6 = e6->__av;
                      EXT_PRICEITEM1.addOrDelOnZero(se5.modify(dt_d_year,store_sales_ss_item_sk),(v5 * v6));
                      n6 = n6->nxt;
                    } while (n6 && (e6 = n6->obj) && h3 == n6->hash &&  EXT_PRICESTORE_SALES1_P_1_mapkey0_idxfn::equals(se6, *e6)); 
                  }
                }
              n5 = n5->nxt;
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
        EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA.clear();
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
                // long item_i_manufact_id = DELTA_ITEM.i_manufact_id[i];
                // STRING_TYPE item_i_manufact = DELTA_ITEM.i_manufact[i];
                // STRING_TYPE item_i_size = DELTA_ITEM.i_size[i];
                // STRING_TYPE item_i_formulation = DELTA_ITEM.i_formulation[i];
                // STRING_TYPE item_i_color = DELTA_ITEM.i_color[i];
                // STRING_TYPE item_i_units = DELTA_ITEM.i_units[i];
                // STRING_TYPE item_i_container = DELTA_ITEM.i_container[i];
                long lift1 = DELTA_ITEM.i_manager_id[i];
                // STRING_TYPE item_i_product_name = DELTA_ITEM.i_product_name[i];
                long v7 = 1L;
                (/*if */(lift1 == 1L) ? EXT_PRICEITEM1_DELTA.addOrDelOnZero(se7.modify(store_sales_ss_item_sk,item_i_brand_id,item_i_brand),v7) : (void)0);
                long v8 = 1L;
                (/*if */(lift1 == 1L) ? EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA.addOrDelOnZero(se8.modify(store_sales_ss_item_sk,item_i_brand,item_i_brand_id),v8) : (void)0);
          }
        }

        {  // foreach
          const HashIndex_EXT_PRICEITEM1_DELTA_map_012* i9 = static_cast<HashIndex_EXT_PRICEITEM1_DELTA_map_012*>(EXT_PRICEITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICEITEM1_DELTA_map_012::IdxNode* n9; 
          EXT_PRICEITEM1_DELTA_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long store_sales_ss_item_sk = e9->STORE_SALES_SS_ITEM_SK;
                long brand_id = e9->BRAND_ID;
                STRING_TYPE brand = e9->BRAND;
                long v9 = e9->__av;
                { //slice 
                  const HashIndex_EXT_PRICEITEM1_map_1* i10 = static_cast<HashIndex_EXT_PRICEITEM1_map_1*>(EXT_PRICEITEM1.index[1]);
                  const HASH_RES_t h4 = EXT_PRICEITEM1_mapkey1_idxfn::hash(se10.modify1(store_sales_ss_item_sk));
                  HashIndex_EXT_PRICEITEM1_map_1::IdxNode* n10 = static_cast<HashIndex_EXT_PRICEITEM1_map_1::IdxNode*>(i10->slice(se10, h4));
                  EXT_PRICEITEM1_entry* e10;
                 
                  if (n10 && (e10 = n10->obj)) {
                    do {                
                      long dt_d_year = e10->DT_D_YEAR;
                      DOUBLE_TYPE v10 = e10->__av;
                      EXT_PRICE.addOrDelOnZero(se9.modify(dt_d_year,brand_id,brand),(v9 * v10));
                      n10 = n10->nxt;
                    } while (n10 && (e10 = n10->obj) && h4 == n10->hash &&  EXT_PRICEITEM1_mapkey1_idxfn::equals(se10, *e10)); 
                  }
                }
              n9 = n9->nxt;
            }
          }
        }{  // foreach
          const HashIndex_EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_map_012* i11 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_map_012*>(EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA.index[0]);
          HashIndex_EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_map_012::IdxNode* n11; 
          EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry* e11;
        
          for (size_t i = 0; i < i11->size_; i++)
          {
            n11 = i11->buckets_ + i;
            while (n11 && (e11 = n11->obj))
            {
                long store_sales_ss_item_sk = e11->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE brand = e11->BRAND;
                long brand_id = e11->BRAND_ID;
                long v11 = e11->__av;
                EXT_PRICESTORE_SALES1_P_2.addOrDelOnZero(se11.modify(store_sales_ss_item_sk,brand_id,brand),v11);
              n11 = n11->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        EXT_PRICESTORE_SALES1_P_1.clear();
        long l1 = 1998L;
        agg1.clear();
        
        long l2 = 12L;
        { //slice 
          const HashIndex_DATE_DIM_map_68* i12 = static_cast<HashIndex_DATE_DIM_map_68*>(DATE_DIM.index[1]);
          const HASH_RES_t h5 = DATE_DIM_mapkey68_idxfn::hash(se13.modify68(l1, l2));
          HashIndex_DATE_DIM_map_68::IdxNode* n12 = static_cast<HashIndex_DATE_DIM_map_68::IdxNode*>(i12->slice(se13, h5));
          DATE_DIM_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long dt_d_date_sk = e12->DATE_DIM_D_DATE_SK;
              STRING_TYPE dt_d_date_id = e12->DATE_DIM_D_DATE_ID;
              date dt_d_date = e12->DATE_DIM_D_DATE;
              long dt_d_month_seq = e12->DATE_DIM_D_MONTH_SEQ;
              long dt_d_week_seq = e12->DATE_DIM_D_WEEK_SEQ;
              long dt_d_quarter_seq = e12->DATE_DIM_D_QUARTER_SEQ;
              long dt_d_dow = e12->DATE_DIM_D_DOW;
              long dt_d_dom = e12->DATE_DIM_D_DOM;
              long dt_d_qoy = e12->DATE_DIM_D_QOY;
              long dt_d_fy_year = e12->DATE_DIM_D_FY_YEAR;
              long dt_d_fy_quarter_seq = e12->DATE_DIM_D_FY_QUARTER_SEQ;
              long dt_d_fy_week_seq = e12->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE dt_d_day_name = e12->DATE_DIM_D_DAY_NAME;
              STRING_TYPE dt_d_quarter_name = e12->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE dt_d_holiday = e12->DATE_DIM_D_HOLIDAY;
              STRING_TYPE dt_d_weekend = e12->DATE_DIM_D_WEEKEND;
              STRING_TYPE dt_d_following_holiday = e12->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long dt_d_first_dom = e12->DATE_DIM_D_FIRST_DOM;
              long dt_d_last_dom = e12->DATE_DIM_D_LAST_DOM;
              long dt_d_same_day_ly = e12->DATE_DIM_D_SAME_DAY_LY;
              long dt_d_same_day_lq = e12->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE dt_d_current_day = e12->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE dt_d_current_week = e12->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE dt_d_current_month = e12->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE dt_d_current_quarter = e12->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE dt_d_current_year = e12->DATE_DIM_D_CURRENT_YEAR;
              long v12 = e12->__av;
              agg1.addOrDelOnZero(st1.modify(dt_d_date_sk,v12), v12);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h5 == n12->hash &&  DATE_DIM_mapkey68_idxfn::equals(se13, *e12)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_L_L, long>* i13 = static_cast<HashIndex<tuple2_L_L, long>*>(agg1.index[0]);
          HashIndex<tuple2_L_L, long>::IdxNode* n13; 
          tuple2_L_L* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
              long dt_d_date_sk = e13->_1;  
              long v13 = e13->__av; 
            EXT_PRICESTORE_SALES1_P_1.addOrDelOnZero(se12.modify(dt_d_date_sk,l1),v13);      
              n13 = n13->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    EXT_PRICESTORE_SALES1_DELTA_entry se1;
    EXT_PRICE_entry se2;
    EXT_PRICESTORE_SALES1_P_2_entry se3;
    EXT_PRICESTORE_SALES1_P_1_entry se4;
    EXT_PRICEITEM1_entry se5;
    EXT_PRICESTORE_SALES1_P_1_entry se6;
    EXT_PRICEITEM1_DELTA_entry se7;
    EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_entry se8;
    EXT_PRICE_entry se9;
    EXT_PRICEITEM1_entry se10;
    EXT_PRICESTORE_SALES1_P_2_entry se11;
    EXT_PRICESTORE_SALES1_P_1_entry se12;
    tuple2_L_L st1;
    DATE_DIM_entry se13;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    EXT_PRICEITEM1_DELTA_map EXT_PRICEITEM1_DELTA;
    EXT_PRICEITEM1_map EXT_PRICEITEM1;
    EXT_PRICESTORE_SALES1_DELTA_map EXT_PRICESTORE_SALES1_DELTA;
    EXT_PRICESTORE_SALES1_P_1_map EXT_PRICESTORE_SALES1_P_1;
    EXT_PRICESTORE_SALES1_P_2_map EXT_PRICESTORE_SALES1_P_2;
    EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA_map EXT_PRICESTORE_SALES1_P_2ITEM1_DELTA;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_ITEM_map DELTA_ITEM;
    MultiHashMap<tuple2_L_L,long,HashIndex<tuple2_L_L,long> > agg1;
    
  
  };

}
