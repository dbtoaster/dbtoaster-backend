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
  
  struct PROMOTION_entry {
    long PROMOTION_P_PROMO_SK; STRING_TYPE PROMOTION_P_PROMO_ID; long PROMOTION_P_START_DATE_SK; long PROMOTION_P_END_DATE_SK; long PROMOTION_P_ITEM_SK; DOUBLE_TYPE PROMOTION_P_COST; long PROMOTION_P_RESPONSE_TARGET; STRING_TYPE PROMOTION_P_PROMO_NAME; STRING_TYPE PROMOTION_P_CHANNEL_DMAIL; STRING_TYPE PROMOTION_P_CHANNEL_EMAIL; STRING_TYPE PROMOTION_P_CHANNEL_CATALOG; STRING_TYPE PROMOTION_P_CHANNEL_TV; STRING_TYPE PROMOTION_P_CHANNEL_RADIO; STRING_TYPE PROMOTION_P_CHANNEL_PRESS; STRING_TYPE PROMOTION_P_CHANNEL_EVENT; STRING_TYPE PROMOTION_P_CHANNEL_DEMO; STRING_TYPE PROMOTION_P_CHANNEL_DETAILS; STRING_TYPE PROMOTION_P_PURPOSE; STRING_TYPE PROMOTION_P_DISCOUNT_ACTIVE; long __av; 
    explicit PROMOTION_entry() { /*PROMOTION_P_PROMO_SK = 0L; PROMOTION_P_PROMO_ID = ""; PROMOTION_P_START_DATE_SK = 0L; PROMOTION_P_END_DATE_SK = 0L; PROMOTION_P_ITEM_SK = 0L; PROMOTION_P_COST = 0.0; PROMOTION_P_RESPONSE_TARGET = 0L; PROMOTION_P_PROMO_NAME = ""; PROMOTION_P_CHANNEL_DMAIL = ""; PROMOTION_P_CHANNEL_EMAIL = ""; PROMOTION_P_CHANNEL_CATALOG = ""; PROMOTION_P_CHANNEL_TV = ""; PROMOTION_P_CHANNEL_RADIO = ""; PROMOTION_P_CHANNEL_PRESS = ""; PROMOTION_P_CHANNEL_EVENT = ""; PROMOTION_P_CHANNEL_DEMO = ""; PROMOTION_P_CHANNEL_DETAILS = ""; PROMOTION_P_PURPOSE = ""; PROMOTION_P_DISCOUNT_ACTIVE = ""; __av = 0L; */ }
    explicit PROMOTION_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3, const long c4, const DOUBLE_TYPE c5, const long c6, const STRING_TYPE& c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const STRING_TYPE& c10, const STRING_TYPE& c11, const STRING_TYPE& c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const long c19) { PROMOTION_P_PROMO_SK = c0; PROMOTION_P_PROMO_ID = c1; PROMOTION_P_START_DATE_SK = c2; PROMOTION_P_END_DATE_SK = c3; PROMOTION_P_ITEM_SK = c4; PROMOTION_P_COST = c5; PROMOTION_P_RESPONSE_TARGET = c6; PROMOTION_P_PROMO_NAME = c7; PROMOTION_P_CHANNEL_DMAIL = c8; PROMOTION_P_CHANNEL_EMAIL = c9; PROMOTION_P_CHANNEL_CATALOG = c10; PROMOTION_P_CHANNEL_TV = c11; PROMOTION_P_CHANNEL_RADIO = c12; PROMOTION_P_CHANNEL_PRESS = c13; PROMOTION_P_CHANNEL_EVENT = c14; PROMOTION_P_CHANNEL_DEMO = c15; PROMOTION_P_CHANNEL_DETAILS = c16; PROMOTION_P_PURPOSE = c17; PROMOTION_P_DISCOUNT_ACTIVE = c18; __av = c19; }
    PROMOTION_entry(const PROMOTION_entry& other) : PROMOTION_P_PROMO_SK( other.PROMOTION_P_PROMO_SK ), PROMOTION_P_PROMO_ID( other.PROMOTION_P_PROMO_ID ), PROMOTION_P_START_DATE_SK( other.PROMOTION_P_START_DATE_SK ), PROMOTION_P_END_DATE_SK( other.PROMOTION_P_END_DATE_SK ), PROMOTION_P_ITEM_SK( other.PROMOTION_P_ITEM_SK ), PROMOTION_P_COST( other.PROMOTION_P_COST ), PROMOTION_P_RESPONSE_TARGET( other.PROMOTION_P_RESPONSE_TARGET ), PROMOTION_P_PROMO_NAME( other.PROMOTION_P_PROMO_NAME ), PROMOTION_P_CHANNEL_DMAIL( other.PROMOTION_P_CHANNEL_DMAIL ), PROMOTION_P_CHANNEL_EMAIL( other.PROMOTION_P_CHANNEL_EMAIL ), PROMOTION_P_CHANNEL_CATALOG( other.PROMOTION_P_CHANNEL_CATALOG ), PROMOTION_P_CHANNEL_TV( other.PROMOTION_P_CHANNEL_TV ), PROMOTION_P_CHANNEL_RADIO( other.PROMOTION_P_CHANNEL_RADIO ), PROMOTION_P_CHANNEL_PRESS( other.PROMOTION_P_CHANNEL_PRESS ), PROMOTION_P_CHANNEL_EVENT( other.PROMOTION_P_CHANNEL_EVENT ), PROMOTION_P_CHANNEL_DEMO( other.PROMOTION_P_CHANNEL_DEMO ), PROMOTION_P_CHANNEL_DETAILS( other.PROMOTION_P_CHANNEL_DETAILS ), PROMOTION_P_PURPOSE( other.PROMOTION_P_PURPOSE ), PROMOTION_P_DISCOUNT_ACTIVE( other.PROMOTION_P_DISCOUNT_ACTIVE ), __av( other.__av ) {}
    FORCE_INLINE PROMOTION_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const long c3, const long c4, const DOUBLE_TYPE c5, const long c6, const STRING_TYPE& c7, const STRING_TYPE& c8, const STRING_TYPE& c9, const STRING_TYPE& c10, const STRING_TYPE& c11, const STRING_TYPE& c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18) { PROMOTION_P_PROMO_SK = c0; PROMOTION_P_PROMO_ID = c1; PROMOTION_P_START_DATE_SK = c2; PROMOTION_P_END_DATE_SK = c3; PROMOTION_P_ITEM_SK = c4; PROMOTION_P_COST = c5; PROMOTION_P_RESPONSE_TARGET = c6; PROMOTION_P_PROMO_NAME = c7; PROMOTION_P_CHANNEL_DMAIL = c8; PROMOTION_P_CHANNEL_EMAIL = c9; PROMOTION_P_CHANNEL_CATALOG = c10; PROMOTION_P_CHANNEL_TV = c11; PROMOTION_P_CHANNEL_RADIO = c12; PROMOTION_P_CHANNEL_PRESS = c13; PROMOTION_P_CHANNEL_EVENT = c14; PROMOTION_P_CHANNEL_DEMO = c15; PROMOTION_P_CHANNEL_DETAILS = c16; PROMOTION_P_PURPOSE = c17; PROMOTION_P_DISCOUNT_ACTIVE = c18;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_PROMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_PROMO_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_START_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_END_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_COST);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_RESPONSE_TARGET);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_PROMO_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_DMAIL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_EMAIL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_CATALOG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_TV);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_RADIO);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_PRESS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_EVENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_DEMO);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_CHANNEL_DETAILS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_PURPOSE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PROMOTION_P_DISCOUNT_ACTIVE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct PROMOTION_mapkey0123456789101112131415161718_idxfn {
    FORCE_INLINE static size_t hash(const PROMOTION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.PROMOTION_P_PROMO_SK);
      hash_combine(h, e.PROMOTION_P_PROMO_ID);
      hash_combine(h, e.PROMOTION_P_START_DATE_SK);
      hash_combine(h, e.PROMOTION_P_END_DATE_SK);
      hash_combine(h, e.PROMOTION_P_ITEM_SK);
      hash_combine(h, e.PROMOTION_P_COST);
      hash_combine(h, e.PROMOTION_P_RESPONSE_TARGET);
      hash_combine(h, e.PROMOTION_P_PROMO_NAME);
      hash_combine(h, e.PROMOTION_P_CHANNEL_DMAIL);
      hash_combine(h, e.PROMOTION_P_CHANNEL_EMAIL);
      hash_combine(h, e.PROMOTION_P_CHANNEL_CATALOG);
      hash_combine(h, e.PROMOTION_P_CHANNEL_TV);
      hash_combine(h, e.PROMOTION_P_CHANNEL_RADIO);
      hash_combine(h, e.PROMOTION_P_CHANNEL_PRESS);
      hash_combine(h, e.PROMOTION_P_CHANNEL_EVENT);
      hash_combine(h, e.PROMOTION_P_CHANNEL_DEMO);
      hash_combine(h, e.PROMOTION_P_CHANNEL_DETAILS);
      hash_combine(h, e.PROMOTION_P_PURPOSE);
      hash_combine(h, e.PROMOTION_P_DISCOUNT_ACTIVE);
      return h;
    }
    FORCE_INLINE static bool equals(const PROMOTION_entry& x, const PROMOTION_entry& y) {
      return x.PROMOTION_P_PROMO_SK == y.PROMOTION_P_PROMO_SK && x.PROMOTION_P_PROMO_ID == y.PROMOTION_P_PROMO_ID && x.PROMOTION_P_START_DATE_SK == y.PROMOTION_P_START_DATE_SK && x.PROMOTION_P_END_DATE_SK == y.PROMOTION_P_END_DATE_SK && x.PROMOTION_P_ITEM_SK == y.PROMOTION_P_ITEM_SK && x.PROMOTION_P_COST == y.PROMOTION_P_COST && x.PROMOTION_P_RESPONSE_TARGET == y.PROMOTION_P_RESPONSE_TARGET && x.PROMOTION_P_PROMO_NAME == y.PROMOTION_P_PROMO_NAME && x.PROMOTION_P_CHANNEL_DMAIL == y.PROMOTION_P_CHANNEL_DMAIL && x.PROMOTION_P_CHANNEL_EMAIL == y.PROMOTION_P_CHANNEL_EMAIL && x.PROMOTION_P_CHANNEL_CATALOG == y.PROMOTION_P_CHANNEL_CATALOG && x.PROMOTION_P_CHANNEL_TV == y.PROMOTION_P_CHANNEL_TV && x.PROMOTION_P_CHANNEL_RADIO == y.PROMOTION_P_CHANNEL_RADIO && x.PROMOTION_P_CHANNEL_PRESS == y.PROMOTION_P_CHANNEL_PRESS && x.PROMOTION_P_CHANNEL_EVENT == y.PROMOTION_P_CHANNEL_EVENT && x.PROMOTION_P_CHANNEL_DEMO == y.PROMOTION_P_CHANNEL_DEMO && x.PROMOTION_P_CHANNEL_DETAILS == y.PROMOTION_P_CHANNEL_DETAILS && x.PROMOTION_P_PURPOSE == y.PROMOTION_P_PURPOSE && x.PROMOTION_P_DISCOUNT_ACTIVE == y.PROMOTION_P_DISCOUNT_ACTIVE;
    }
  };
  
  typedef MultiHashMap<PROMOTION_entry,long,
    HashIndex<PROMOTION_entry,long,PROMOTION_mapkey0123456789101112131415161718_idxfn,true>
  > PROMOTION_map;
  typedef HashIndex<PROMOTION_entry,long,PROMOTION_mapkey0123456789101112131415161718_idxfn,true> HashIndex_PROMOTION_map_0123456789101112131415161718;
  
  struct AGG1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG1_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG1_entry(const AGG1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1_entry& x, const AGG1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1_entry,DOUBLE_TYPE,
    HashIndex<AGG1_entry,DOUBLE_TYPE,AGG1_mapkey0_idxfn,true>
  > AGG1_map;
  typedef HashIndex<AGG1_entry,DOUBLE_TYPE,AGG1_mapkey0_idxfn,true> HashIndex_AGG1_map_0;
  
  struct AGG1ITEM1_DELTA_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1ITEM1_DELTA_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1ITEM1_DELTA_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1ITEM1_DELTA_entry(const AGG1ITEM1_DELTA_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_DELTA_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_DELTA_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
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
  struct AGG1ITEM1_DELTA_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_DELTA_entry& x, const AGG1ITEM1_DELTA_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1ITEM1_DELTA_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_DELTA_entry& x, const AGG1ITEM1_DELTA_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_DELTA_entry,long,
    HashIndex<AGG1ITEM1_DELTA_entry,long,AGG1ITEM1_DELTA_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_DELTA_entry,long,AGG1ITEM1_DELTA_mapkey1_idxfn,false>
  > AGG1ITEM1_DELTA_map;
  typedef HashIndex<AGG1ITEM1_DELTA_entry,long,AGG1ITEM1_DELTA_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_DELTA_map_01;
  typedef HashIndex<AGG1ITEM1_DELTA_entry,long,AGG1ITEM1_DELTA_mapkey1_idxfn,false> HashIndex_AGG1ITEM1_DELTA_map_1;
  
  struct AGG1ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; long __av; 
    explicit AGG1ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_entry(const long c0, const long c1) { STORE_SALES_SS_ITEM_SK = c0; __av = c1; }
    AGG1ITEM1_entry(const AGG1ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_entry& modify(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_entry& x, const AGG1ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_entry,long,
    HashIndex<AGG1ITEM1_entry,long,AGG1ITEM1_mapkey0_idxfn,true>
  > AGG1ITEM1_map;
  typedef HashIndex<AGG1ITEM1_entry,long,AGG1ITEM1_mapkey0_idxfn,true> HashIndex_AGG1ITEM1_map_0;
  
  struct AGG1ITEM1STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_PROMO_SK; long __av; 
    explicit AGG1ITEM1STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_PROMO_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3; __av = c4; }
    AGG1ITEM1STORE_SALES1_DELTA_entry(const AGG1ITEM1STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_PROMO_SK( other.STORE_SALES_SS_PROMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_PROMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_PROMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1STORE_SALES1_DELTA_entry& x, const AGG1ITEM1STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_PROMO_SK == y.STORE_SALES_SS_PROMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1STORE_SALES1_DELTA_entry,long,
    HashIndex<AGG1ITEM1STORE_SALES1_DELTA_entry,long,AGG1ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG1ITEM1STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG1ITEM1STORE_SALES1_DELTA_entry,long,AGG1ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG1ITEM1STORE_SALES1_DELTA_map_0123;
  
  struct AGG1ITEM1STORE_SALES1_P_1_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit AGG1ITEM1STORE_SALES1_P_1_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1STORE_SALES1_P_1_entry(const long c0, const long c1) { STORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    AGG1ITEM1STORE_SALES1_P_1_entry(const AGG1ITEM1STORE_SALES1_P_1_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1STORE_SALES1_P_1_entry& modify(const long c0) { STORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1STORE_SALES1_P_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1STORE_SALES1_P_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1STORE_SALES1_P_1_entry& x, const AGG1ITEM1STORE_SALES1_P_1_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1STORE_SALES1_P_1_entry,long,
    HashIndex<AGG1ITEM1STORE_SALES1_P_1_entry,long,AGG1ITEM1STORE_SALES1_P_1_mapkey0_idxfn,true>
  > AGG1ITEM1STORE_SALES1_P_1_map;
  typedef HashIndex<AGG1ITEM1STORE_SALES1_P_1_entry,long,AGG1ITEM1STORE_SALES1_P_1_mapkey0_idxfn,true> HashIndex_AGG1ITEM1STORE_SALES1_P_1_map_0;
  
  struct AGG1ITEM1STORE_SALES1_P_2_entry {
    long STORE_SALES_SS_CDEMO_SK; long __av; 
    explicit AGG1ITEM1STORE_SALES1_P_2_entry() { /*STORE_SALES_SS_CDEMO_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1STORE_SALES1_P_2_entry(const long c0, const long c1) { STORE_SALES_SS_CDEMO_SK = c0; __av = c1; }
    AGG1ITEM1STORE_SALES1_P_2_entry(const AGG1ITEM1STORE_SALES1_P_2_entry& other) : STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1STORE_SALES1_P_2_entry& modify(const long c0) { STORE_SALES_SS_CDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1STORE_SALES1_P_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1STORE_SALES1_P_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1STORE_SALES1_P_2_entry& x, const AGG1ITEM1STORE_SALES1_P_2_entry& y) {
      return x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1STORE_SALES1_P_2_entry,long,
    HashIndex<AGG1ITEM1STORE_SALES1_P_2_entry,long,AGG1ITEM1STORE_SALES1_P_2_mapkey0_idxfn,true>
  > AGG1ITEM1STORE_SALES1_P_2_map;
  typedef HashIndex<AGG1ITEM1STORE_SALES1_P_2_entry,long,AGG1ITEM1STORE_SALES1_P_2_mapkey0_idxfn,true> HashIndex_AGG1ITEM1STORE_SALES1_P_2_map_0;
  
  struct AGG1ITEM1STORE_SALES1_P_3_entry {
    long STORE_SALES_SS_PROMO_SK; long __av; 
    explicit AGG1ITEM1STORE_SALES1_P_3_entry() { /*STORE_SALES_SS_PROMO_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1STORE_SALES1_P_3_entry(const long c0, const long c1) { STORE_SALES_SS_PROMO_SK = c0; __av = c1; }
    AGG1ITEM1STORE_SALES1_P_3_entry(const AGG1ITEM1STORE_SALES1_P_3_entry& other) : STORE_SALES_SS_PROMO_SK( other.STORE_SALES_SS_PROMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1STORE_SALES1_P_3_entry& modify(const long c0) { STORE_SALES_SS_PROMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_PROMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1STORE_SALES1_P_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1STORE_SALES1_P_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_PROMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1STORE_SALES1_P_3_entry& x, const AGG1ITEM1STORE_SALES1_P_3_entry& y) {
      return x.STORE_SALES_SS_PROMO_SK == y.STORE_SALES_SS_PROMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1STORE_SALES1_P_3_entry,long,
    HashIndex<AGG1ITEM1STORE_SALES1_P_3_entry,long,AGG1ITEM1STORE_SALES1_P_3_mapkey0_idxfn,true>
  > AGG1ITEM1STORE_SALES1_P_3_map;
  typedef HashIndex<AGG1ITEM1STORE_SALES1_P_3_entry,long,AGG1ITEM1STORE_SALES1_P_3_mapkey0_idxfn,true> HashIndex_AGG1ITEM1STORE_SALES1_P_3_map_0;
  
  struct AGG1ITEM2_DOMAIN1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1ITEM2_DOMAIN1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1ITEM2_DOMAIN1_entry(const STRING_TYPE& c0, const long c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG1ITEM2_DOMAIN1_entry(const AGG1ITEM2_DOMAIN1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM2_DOMAIN1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM2_DOMAIN1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM2_DOMAIN1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM2_DOMAIN1_entry& x, const AGG1ITEM2_DOMAIN1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM2_DOMAIN1_entry,long,
    HashIndex<AGG1ITEM2_DOMAIN1_entry,long,AGG1ITEM2_DOMAIN1_mapkey0_idxfn,true>
  > AGG1ITEM2_DOMAIN1_map;
  typedef HashIndex<AGG1ITEM2_DOMAIN1_entry,long,AGG1ITEM2_DOMAIN1_mapkey0_idxfn,true> HashIndex_AGG1ITEM2_DOMAIN1_map_0;
  
  struct AGG1ITEM2_L1_2_entry {
    long STORE_SALES_SS_ITEM_SK; long __av; 
    explicit AGG1ITEM2_L1_2_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM2_L1_2_entry(const long c0, const long c1) { STORE_SALES_SS_ITEM_SK = c0; __av = c1; }
    AGG1ITEM2_L1_2_entry(const AGG1ITEM2_L1_2_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM2_L1_2_entry& modify(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM2_L1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM2_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM2_L1_2_entry& x, const AGG1ITEM2_L1_2_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM2_L1_2_entry,long,
    HashIndex<AGG1ITEM2_L1_2_entry,long,AGG1ITEM2_L1_2_mapkey0_idxfn,true>
  > AGG1ITEM2_L1_2_map;
  typedef HashIndex<AGG1ITEM2_L1_2_entry,long,AGG1ITEM2_L1_2_mapkey0_idxfn,true> HashIndex_AGG1ITEM2_L1_2_map_0;
  
  struct AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_PROMO_SK; long __av; 
    explicit AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_PROMO_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3; __av = c4; }
    AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry(const AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_PROMO_SK( other.STORE_SALES_SS_PROMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_PROMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM2_L1_2STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_PROMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry& x, const AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_PROMO_SK == y.STORE_SALES_SS_PROMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry,long,
    HashIndex<AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry,long,AGG1ITEM2_L1_2STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG1ITEM2_L1_2STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry,long,AGG1ITEM2_L1_2STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG1ITEM2_L1_2STORE_SALES1_DELTA_map_0123;
  
  struct AGG1STORE_SALES1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE_SALES1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE_SALES1_entry(const STRING_TYPE& c0, const long c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG1STORE_SALES1_entry(const AGG1STORE_SALES1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE_SALES1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE_SALES1_mapkey0_idxfn {
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
    HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey0_idxfn,true>
  > AGG1STORE_SALES1_map;
  typedef HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey0_idxfn,true> HashIndex_AGG1STORE_SALES1_map_0;
  
  struct AGG1STORE_SALES1STORE_SALES1_P_4_entry {
    long STORE_SALES_SS_ITEM_SK; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE_SALES1STORE_SALES1_P_4_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE_SALES1STORE_SALES1_P_4_entry(const long c0, const STRING_TYPE& c1, const long c2) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE_SALES1STORE_SALES1_P_4_entry(const AGG1STORE_SALES1STORE_SALES1_P_4_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE_SALES1STORE_SALES1_P_4_entry& modify(const long c0, const STRING_TYPE& c1) { STORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE_SALES1STORE_SALES1_P_4_entry& modify0(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
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
  struct AGG1STORE_SALES1STORE_SALES1_P_4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1STORE_SALES1_P_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1STORE_SALES1_P_4_entry& x, const AGG1STORE_SALES1STORE_SALES1_P_4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1STORE_SALES1_P_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1STORE_SALES1_P_4_entry& x, const AGG1STORE_SALES1STORE_SALES1_P_4_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE_SALES1STORE_SALES1_P_4_entry,long,
    HashIndex<AGG1STORE_SALES1STORE_SALES1_P_4_entry,long,AGG1STORE_SALES1STORE_SALES1_P_4_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE_SALES1STORE_SALES1_P_4_entry,long,AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn,false>
  > AGG1STORE_SALES1STORE_SALES1_P_4_map;
  typedef HashIndex<AGG1STORE_SALES1STORE_SALES1_P_4_entry,long,AGG1STORE_SALES1STORE_SALES1_P_4_mapkey01_idxfn,true> HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_01;
  typedef HashIndex<AGG1STORE_SALES1STORE_SALES1_P_4_entry,long,AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn,false> HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0;
  
  struct AGG1STORE_SALES1_L1_1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE_SALES1_L1_1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE_SALES1_L1_1_entry(const STRING_TYPE& c0, const long c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG1STORE_SALES1_L1_1_entry(const AGG1STORE_SALES1_L1_1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE_SALES1_L1_1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE_SALES1_L1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1_L1_1_entry& x, const AGG1STORE_SALES1_L1_1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1STORE_SALES1_L1_1_entry,long,
    HashIndex<AGG1STORE_SALES1_L1_1_entry,long,AGG1STORE_SALES1_L1_1_mapkey0_idxfn,true>
  > AGG1STORE_SALES1_L1_1_map;
  typedef HashIndex<AGG1STORE_SALES1_L1_1_entry,long,AGG1STORE_SALES1_L1_1_mapkey0_idxfn,true> HashIndex_AGG1STORE_SALES1_L1_1_map_0;
  
  struct AGG2_entry {
    STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG2_entry(const AGG2_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2_entry& x, const AGG2_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG2_entry,DOUBLE_TYPE,
    HashIndex<AGG2_entry,DOUBLE_TYPE,AGG2_mapkey0_idxfn,true>
  > AGG2_map;
  typedef HashIndex<AGG2_entry,DOUBLE_TYPE,AGG2_mapkey0_idxfn,true> HashIndex_AGG2_map_0;
  
  struct AGG2ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit AGG2ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit AGG2ITEM1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_ITEM_SK = c0; __av = c1; }
    AGG2ITEM1_entry(const AGG2ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG2ITEM1_entry& modify(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM1_entry& x, const AGG2ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG2ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG2ITEM1_entry,DOUBLE_TYPE,AGG2ITEM1_mapkey0_idxfn,true>
  > AGG2ITEM1_map;
  typedef HashIndex<AGG2ITEM1_entry,DOUBLE_TYPE,AGG2ITEM1_mapkey0_idxfn,true> HashIndex_AGG2ITEM1_map_0;
  
  struct AGG2ITEM1STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_PROMO_SK; DOUBLE_TYPE __av; 
    explicit AGG2ITEM1STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_PROMO_SK = 0L; __av = 0.0; */ }
    explicit AGG2ITEM1STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3; __av = c4; }
    AGG2ITEM1STORE_SALES1_DELTA_entry(const AGG2ITEM1STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_PROMO_SK( other.STORE_SALES_SS_PROMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG2ITEM1STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_PROMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM1STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_PROMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM1STORE_SALES1_DELTA_entry& x, const AGG2ITEM1STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_PROMO_SK == y.STORE_SALES_SS_PROMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG2ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AGG2ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG2ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG2ITEM1STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG2ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG2ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG2ITEM1STORE_SALES1_DELTA_map_0123;
  
  struct AGG2STORE_SALES1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2STORE_SALES1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2STORE_SALES1_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG2STORE_SALES1_entry(const AGG2STORE_SALES1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE_SALES1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE_SALES1_mapkey0_idxfn {
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
    HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey0_idxfn,true>
  > AGG2STORE_SALES1_map;
  typedef HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey0_idxfn,true> HashIndex_AGG2STORE_SALES1_map_0;
  
  struct AGG3_entry {
    STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG3_entry(const AGG3_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3_entry& x, const AGG3_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG3_entry,DOUBLE_TYPE,
    HashIndex<AGG3_entry,DOUBLE_TYPE,AGG3_mapkey0_idxfn,true>
  > AGG3_map;
  typedef HashIndex<AGG3_entry,DOUBLE_TYPE,AGG3_mapkey0_idxfn,true> HashIndex_AGG3_map_0;
  
  struct AGG3ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit AGG3ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit AGG3ITEM1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_ITEM_SK = c0; __av = c1; }
    AGG3ITEM1_entry(const AGG3ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG3ITEM1_entry& modify(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM1_entry& x, const AGG3ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG3ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG3ITEM1_entry,DOUBLE_TYPE,AGG3ITEM1_mapkey0_idxfn,true>
  > AGG3ITEM1_map;
  typedef HashIndex<AGG3ITEM1_entry,DOUBLE_TYPE,AGG3ITEM1_mapkey0_idxfn,true> HashIndex_AGG3ITEM1_map_0;
  
  struct AGG3ITEM1STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_PROMO_SK; DOUBLE_TYPE __av; 
    explicit AGG3ITEM1STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_PROMO_SK = 0L; __av = 0.0; */ }
    explicit AGG3ITEM1STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3; __av = c4; }
    AGG3ITEM1STORE_SALES1_DELTA_entry(const AGG3ITEM1STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_PROMO_SK( other.STORE_SALES_SS_PROMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG3ITEM1STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_PROMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM1STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_PROMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM1STORE_SALES1_DELTA_entry& x, const AGG3ITEM1STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_PROMO_SK == y.STORE_SALES_SS_PROMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG3ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AGG3ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG3ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG3ITEM1STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG3ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG3ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG3ITEM1STORE_SALES1_DELTA_map_0123;
  
  struct AGG3STORE_SALES1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3STORE_SALES1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3STORE_SALES1_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG3STORE_SALES1_entry(const AGG3STORE_SALES1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE_SALES1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE_SALES1_mapkey0_idxfn {
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
    HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey0_idxfn,true>
  > AGG3STORE_SALES1_map;
  typedef HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey0_idxfn,true> HashIndex_AGG3STORE_SALES1_map_0;
  
  struct AGG4_entry {
    STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG4_entry(const AGG4_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4_entry& x, const AGG4_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG4_entry,DOUBLE_TYPE,
    HashIndex<AGG4_entry,DOUBLE_TYPE,AGG4_mapkey0_idxfn,true>
  > AGG4_map;
  typedef HashIndex<AGG4_entry,DOUBLE_TYPE,AGG4_mapkey0_idxfn,true> HashIndex_AGG4_map_0;
  
  struct AGG4ITEM1_entry {
    long STORE_SALES_SS_ITEM_SK; DOUBLE_TYPE __av; 
    explicit AGG4ITEM1_entry() { /*STORE_SALES_SS_ITEM_SK = 0L; __av = 0.0; */ }
    explicit AGG4ITEM1_entry(const long c0, const DOUBLE_TYPE c1) { STORE_SALES_SS_ITEM_SK = c0; __av = c1; }
    AGG4ITEM1_entry(const AGG4ITEM1_entry& other) : STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG4ITEM1_entry& modify(const long c0) { STORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM1_entry& x, const AGG4ITEM1_entry& y) {
      return x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG4ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG4ITEM1_entry,DOUBLE_TYPE,AGG4ITEM1_mapkey0_idxfn,true>
  > AGG4ITEM1_map;
  typedef HashIndex<AGG4ITEM1_entry,DOUBLE_TYPE,AGG4ITEM1_mapkey0_idxfn,true> HashIndex_AGG4ITEM1_map_0;
  
  struct AGG4ITEM1STORE_SALES1_DELTA_entry {
    long STORE_SALES_SS_SOLD_DATE_SK; long STORE_SALES_SS_ITEM_SK; long STORE_SALES_SS_CDEMO_SK; long STORE_SALES_SS_PROMO_SK; DOUBLE_TYPE __av; 
    explicit AGG4ITEM1STORE_SALES1_DELTA_entry() { /*STORE_SALES_SS_SOLD_DATE_SK = 0L; STORE_SALES_SS_ITEM_SK = 0L; STORE_SALES_SS_CDEMO_SK = 0L; STORE_SALES_SS_PROMO_SK = 0L; __av = 0.0; */ }
    explicit AGG4ITEM1STORE_SALES1_DELTA_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3; __av = c4; }
    AGG4ITEM1STORE_SALES1_DELTA_entry(const AGG4ITEM1STORE_SALES1_DELTA_entry& other) : STORE_SALES_SS_SOLD_DATE_SK( other.STORE_SALES_SS_SOLD_DATE_SK ), STORE_SALES_SS_ITEM_SK( other.STORE_SALES_SS_ITEM_SK ), STORE_SALES_SS_CDEMO_SK( other.STORE_SALES_SS_CDEMO_SK ), STORE_SALES_SS_PROMO_SK( other.STORE_SALES_SS_PROMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG4ITEM1STORE_SALES1_DELTA_entry& modify(const long c0, const long c1, const long c2, const long c3) { STORE_SALES_SS_SOLD_DATE_SK = c0; STORE_SALES_SS_ITEM_SK = c1; STORE_SALES_SS_CDEMO_SK = c2; STORE_SALES_SS_PROMO_SK = c3;  return *this; }
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
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_PROMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM1STORE_SALES1_DELTA_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.STORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.STORE_SALES_SS_CDEMO_SK);
      hash_combine(h, e.STORE_SALES_SS_PROMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM1STORE_SALES1_DELTA_entry& x, const AGG4ITEM1STORE_SALES1_DELTA_entry& y) {
      return x.STORE_SALES_SS_SOLD_DATE_SK == y.STORE_SALES_SS_SOLD_DATE_SK && x.STORE_SALES_SS_ITEM_SK == y.STORE_SALES_SS_ITEM_SK && x.STORE_SALES_SS_CDEMO_SK == y.STORE_SALES_SS_CDEMO_SK && x.STORE_SALES_SS_PROMO_SK == y.STORE_SALES_SS_PROMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG4ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,
    HashIndex<AGG4ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG4ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true>
  > AGG4ITEM1STORE_SALES1_DELTA_map;
  typedef HashIndex<AGG4ITEM1STORE_SALES1_DELTA_entry,DOUBLE_TYPE,AGG4ITEM1STORE_SALES1_DELTA_mapkey0123_idxfn,true> HashIndex_AGG4ITEM1STORE_SALES1_DELTA_map_0123;
  
  struct AGG4STORE_SALES1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4STORE_SALES1_entry() { /*ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4STORE_SALES1_entry(const STRING_TYPE& c0, const DOUBLE_TYPE c1) { ITEM_I_ITEM_ID = c0; __av = c1; }
    AGG4STORE_SALES1_entry(const AGG4STORE_SALES1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE_SALES1_entry& modify(const STRING_TYPE& c0) { ITEM_I_ITEM_ID = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE_SALES1_mapkey0_idxfn {
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
    HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey0_idxfn,true>
  > AGG4STORE_SALES1_map;
  typedef HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey0_idxfn,true> HashIndex_AGG4STORE_SALES1_map_0;
  
  
  
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
    data_t(): tlq_t() {
      c3 = STRING_TYPE("F");
      c4 = STRING_TYPE("N");
      c2 = STRING_TYPE("W");
      c1 = STRING_TYPE("Primary");
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
    
    void on_insert_PROMOTION(const long promotion_p_promo_sk, const STRING_TYPE promotion_p_promo_id, const long promotion_p_start_date_sk, const long promotion_p_end_date_sk, const long promotion_p_item_sk, const DOUBLE_TYPE promotion_p_cost, const long promotion_p_response_target, const STRING_TYPE promotion_p_promo_name, const STRING_TYPE promotion_p_channel_dmail, const STRING_TYPE promotion_p_channel_email, const STRING_TYPE promotion_p_channel_catalog, const STRING_TYPE promotion_p_channel_tv, const STRING_TYPE promotion_p_channel_radio, const STRING_TYPE promotion_p_channel_press, const STRING_TYPE promotion_p_channel_event, const STRING_TYPE promotion_p_channel_demo, const STRING_TYPE promotion_p_channel_details, const STRING_TYPE promotion_p_purpose, const STRING_TYPE promotion_p_discount_active) {
      PROMOTION_entry e(promotion_p_promo_sk, promotion_p_promo_id, promotion_p_start_date_sk, promotion_p_end_date_sk, promotion_p_item_sk, promotion_p_cost, promotion_p_response_target, promotion_p_promo_name, promotion_p_channel_dmail, promotion_p_channel_email, promotion_p_channel_catalog, promotion_p_channel_tv, promotion_p_channel_radio, promotion_p_channel_press, promotion_p_channel_event, promotion_p_channel_demo, promotion_p_channel_details, promotion_p_purpose, promotion_p_discount_active, 1L);
      PROMOTION.addOrDelOnZero(e,1L);
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

        AGG1ITEM1STORE_SALES1_DELTA.clear();
        AGG1ITEM2_L1_2STORE_SALES1_DELTA.clear();        
        AGG2ITEM1STORE_SALES1_DELTA.clear();
        AGG3ITEM1STORE_SALES1_DELTA.clear();
        AGG4ITEM1STORE_SALES1_DELTA.clear();
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
                // long store_sales_ss_store_sk = DELTA_STORE_SALES.ss_store_sk[i];
                long store_sales_ss_promo_sk = DELTA_STORE_SALES.ss_promo_sk[i];
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
                AGG1ITEM1STORE_SALES1_DELTA.addOrDelOnZero(se1.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_promo_sk),(v1 * store_sales_ss_quantity));
                long v2 = 1L;
                AGG1ITEM2_L1_2STORE_SALES1_DELTA.addOrDelOnZero(se2.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_promo_sk),v2);
                long v3 = 1L;
                AGG2ITEM1STORE_SALES1_DELTA.addOrDelOnZero(se3.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_promo_sk),(v3 * store_sales_ss_list_price));
                long v4 = 1L;
                AGG3ITEM1STORE_SALES1_DELTA.addOrDelOnZero(se4.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_promo_sk),(v4 * store_sales_ss_coupon_amt));
                long v5 = 1L;
                AGG4ITEM1STORE_SALES1_DELTA.addOrDelOnZero(se5.modify(store_sales_ss_sold_date_sk,store_sales_ss_item_sk,store_sales_ss_cdemo_sk,store_sales_ss_promo_sk),(v5 * store_sales_ss_sales_price));

          }
        }

        {  // foreach
          const HashIndex_AGG1ITEM1STORE_SALES1_DELTA_map_0123* i6 = static_cast<HashIndex_AGG1ITEM1STORE_SALES1_DELTA_map_0123*>(AGG1ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n6; 
          AGG1ITEM1STORE_SALES1_DELTA_entry* e6;
        
          for (size_t i = 0; i < i6->size_; i++)
          {
            n6 = i6->buckets_ + i;
            while (n6 && (e6 = n6->obj))
            {
                long store_sales_ss_sold_date_sk = e6->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e6->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e6->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e6->STORE_SALES_SS_PROMO_SK;
                long v6 = e6->__av;
                AGG1ITEM1.addOrDelOnZero(se6.modify(store_sales_ss_item_sk),(v6 * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se7.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se8.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se9.modify(store_sales_ss_promo_sk))))));
              n6 = n6->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM2_L1_2STORE_SALES1_DELTA_map_0123* i7 = static_cast<HashIndex_AGG1ITEM2_L1_2STORE_SALES1_DELTA_map_0123*>(AGG1ITEM2_L1_2STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM2_L1_2STORE_SALES1_DELTA_map_0123::IdxNode* n7; 
          AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long store_sales_ss_sold_date_sk = e7->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e7->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e7->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e7->STORE_SALES_SS_PROMO_SK;
                long v7 = e7->__av;
                AGG1ITEM2_L1_2.addOrDelOnZero(se10.modify(store_sales_ss_item_sk),(v7 * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se11.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se12.modify(store_sales_ss_sold_date_sk)) * AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se13.modify(store_sales_ss_promo_sk))))));
              n7 = n7->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1STORE_SALES1_DELTA_map_0123* i8 = static_cast<HashIndex_AGG1ITEM1STORE_SALES1_DELTA_map_0123*>(AGG1ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n8; 
          AGG1ITEM1STORE_SALES1_DELTA_entry* e8;
        
          for (size_t i = 0; i < i8->size_; i++)
          {
            n8 = i8->buckets_ + i;
            while (n8 && (e8 = n8->obj))
            {
                long store_sales_ss_sold_date_sk = e8->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e8->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e8->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e8->STORE_SALES_SS_PROMO_SK;
                long v8 = e8->__av;
                { //slice 
                  const HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0* i9 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0*>(AGG1STORE_SALES1STORE_SALES1_P_4.index[1]);
                  const HASH_RES_t h1 = AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::hash(se18.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode* n9 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode*>(i9->slice(se18, h1));
                  AGG1STORE_SALES1STORE_SALES1_P_4_entry* e9;
                 
                  if (n9 && (e9 = n9->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e9->ITEM_I_ITEM_ID;
                      long v9 = e9->__av;
                      AGG1STORE_SALES1.addOrDelOnZero(se14.modify(item_i_item_id),(v8 * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se15.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se16.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se17.modify(store_sales_ss_promo_sk)) * v9)))));
                      n9 = n9->nxt;
                    } while (n9 && (e9 = n9->obj) && h1 == n9->hash &&  AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::equals(se18, *e9)); 
                  }
                }
              n8 = n8->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM2_L1_2STORE_SALES1_DELTA_map_0123* i10 = static_cast<HashIndex_AGG1ITEM2_L1_2STORE_SALES1_DELTA_map_0123*>(AGG1ITEM2_L1_2STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG1ITEM2_L1_2STORE_SALES1_DELTA_map_0123::IdxNode* n10; 
          AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long store_sales_ss_sold_date_sk = e10->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e10->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e10->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e10->STORE_SALES_SS_PROMO_SK;
                long v10 = e10->__av;
                { //slice 
                  const HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0* i11 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0*>(AGG1STORE_SALES1STORE_SALES1_P_4.index[1]);
                  const HASH_RES_t h2 = AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::hash(se23.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode* n11 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode*>(i11->slice(se23, h2));
                  AGG1STORE_SALES1STORE_SALES1_P_4_entry* e11;
                 
                  if (n11 && (e11 = n11->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e11->ITEM_I_ITEM_ID;
                      long v11 = e11->__av;
                      AGG1STORE_SALES1_L1_1.addOrDelOnZero(se19.modify(item_i_item_id),(v10 * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se20.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se21.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se22.modify(store_sales_ss_promo_sk)) * v11)))));
                      n11 = n11->nxt;
                    } while (n11 && (e11 = n11->obj) && h2 == n11->hash &&  AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::equals(se23, *e11)); 
                  }
                }
              n10 = n10->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM1STORE_SALES1_DELTA_map_0123* i12 = static_cast<HashIndex_AGG2ITEM1STORE_SALES1_DELTA_map_0123*>(AGG2ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n12; 
          AGG2ITEM1STORE_SALES1_DELTA_entry* e12;
        
          for (size_t i = 0; i < i12->size_; i++)
          {
            n12 = i12->buckets_ + i;
            while (n12 && (e12 = n12->obj))
            {
                long store_sales_ss_sold_date_sk = e12->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e12->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e12->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e12->STORE_SALES_SS_PROMO_SK;
                DOUBLE_TYPE v12 = e12->__av;
                AGG2ITEM1.addOrDelOnZero(se24.modify(store_sales_ss_item_sk),(v12 * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se25.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se26.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se27.modify(store_sales_ss_promo_sk))))));
              n12 = n12->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG2ITEM1STORE_SALES1_DELTA_map_0123* i13 = static_cast<HashIndex_AGG2ITEM1STORE_SALES1_DELTA_map_0123*>(AGG2ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG2ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n13; 
          AGG2ITEM1STORE_SALES1_DELTA_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long store_sales_ss_sold_date_sk = e13->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e13->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e13->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e13->STORE_SALES_SS_PROMO_SK;
                DOUBLE_TYPE v13 = e13->__av;
                { //slice 
                  const HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0* i14 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0*>(AGG1STORE_SALES1STORE_SALES1_P_4.index[1]);
                  const HASH_RES_t h3 = AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::hash(se32.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode* n14 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode*>(i14->slice(se32, h3));
                  AGG1STORE_SALES1STORE_SALES1_P_4_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e14->ITEM_I_ITEM_ID;
                      long v14 = e14->__av;
                      AGG2STORE_SALES1.addOrDelOnZero(se28.modify(item_i_item_id),(v13 * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se29.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se30.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se31.modify(store_sales_ss_promo_sk)) * v14)))));
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h3 == n14->hash &&  AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::equals(se32, *e14)); 
                  }
                }
              n13 = n13->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM1STORE_SALES1_DELTA_map_0123* i15 = static_cast<HashIndex_AGG3ITEM1STORE_SALES1_DELTA_map_0123*>(AGG3ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n15; 
          AGG3ITEM1STORE_SALES1_DELTA_entry* e15;
        
          for (size_t i = 0; i < i15->size_; i++)
          {
            n15 = i15->buckets_ + i;
            while (n15 && (e15 = n15->obj))
            {
                long store_sales_ss_sold_date_sk = e15->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e15->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e15->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e15->STORE_SALES_SS_PROMO_SK;
                DOUBLE_TYPE v15 = e15->__av;
                AGG3ITEM1.addOrDelOnZero(se33.modify(store_sales_ss_item_sk),(v15 * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se34.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se35.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se36.modify(store_sales_ss_promo_sk))))));
              n15 = n15->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG3ITEM1STORE_SALES1_DELTA_map_0123* i16 = static_cast<HashIndex_AGG3ITEM1STORE_SALES1_DELTA_map_0123*>(AGG3ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG3ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n16; 
          AGG3ITEM1STORE_SALES1_DELTA_entry* e16;
        
          for (size_t i = 0; i < i16->size_; i++)
          {
            n16 = i16->buckets_ + i;
            while (n16 && (e16 = n16->obj))
            {
                long store_sales_ss_sold_date_sk = e16->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e16->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e16->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e16->STORE_SALES_SS_PROMO_SK;
                DOUBLE_TYPE v16 = e16->__av;
                { //slice 
                  const HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0* i17 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0*>(AGG1STORE_SALES1STORE_SALES1_P_4.index[1]);
                  const HASH_RES_t h4 = AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::hash(se41.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode* n17 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode*>(i17->slice(se41, h4));
                  AGG1STORE_SALES1STORE_SALES1_P_4_entry* e17;
                 
                  if (n17 && (e17 = n17->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e17->ITEM_I_ITEM_ID;
                      long v17 = e17->__av;
                      AGG3STORE_SALES1.addOrDelOnZero(se37.modify(item_i_item_id),(v16 * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se38.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se39.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se40.modify(store_sales_ss_promo_sk)) * v17)))));
                      n17 = n17->nxt;
                    } while (n17 && (e17 = n17->obj) && h4 == n17->hash &&  AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::equals(se41, *e17)); 
                  }
                }
              n16 = n16->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM1STORE_SALES1_DELTA_map_0123* i18 = static_cast<HashIndex_AGG4ITEM1STORE_SALES1_DELTA_map_0123*>(AGG4ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n18; 
          AGG4ITEM1STORE_SALES1_DELTA_entry* e18;
        
          for (size_t i = 0; i < i18->size_; i++)
          {
            n18 = i18->buckets_ + i;
            while (n18 && (e18 = n18->obj))
            {
                long store_sales_ss_sold_date_sk = e18->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e18->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e18->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e18->STORE_SALES_SS_PROMO_SK;
                DOUBLE_TYPE v18 = e18->__av;
                AGG4ITEM1.addOrDelOnZero(se42.modify(store_sales_ss_item_sk),(v18 * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se43.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se44.modify(store_sales_ss_cdemo_sk)) * AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se45.modify(store_sales_ss_promo_sk))))));
              n18 = n18->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG4ITEM1STORE_SALES1_DELTA_map_0123* i19 = static_cast<HashIndex_AGG4ITEM1STORE_SALES1_DELTA_map_0123*>(AGG4ITEM1STORE_SALES1_DELTA.index[0]);
          HashIndex_AGG4ITEM1STORE_SALES1_DELTA_map_0123::IdxNode* n19; 
          AGG4ITEM1STORE_SALES1_DELTA_entry* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
                long store_sales_ss_sold_date_sk = e19->STORE_SALES_SS_SOLD_DATE_SK;
                long store_sales_ss_item_sk = e19->STORE_SALES_SS_ITEM_SK;
                long store_sales_ss_cdemo_sk = e19->STORE_SALES_SS_CDEMO_SK;
                long store_sales_ss_promo_sk = e19->STORE_SALES_SS_PROMO_SK;
                DOUBLE_TYPE v19 = e19->__av;
                { //slice 
                  const HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0* i20 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0*>(AGG1STORE_SALES1STORE_SALES1_P_4.index[1]);
                  const HASH_RES_t h5 = AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::hash(se50.modify0(store_sales_ss_item_sk));
                  HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode* n20 = static_cast<HashIndex_AGG1STORE_SALES1STORE_SALES1_P_4_map_0::IdxNode*>(i20->slice(se50, h5));
                  AGG1STORE_SALES1STORE_SALES1_P_4_entry* e20;
                 
                  if (n20 && (e20 = n20->obj)) {
                    do {                
                      STRING_TYPE item_i_item_id = e20->ITEM_I_ITEM_ID;
                      long v20 = e20->__av;
                      AGG4STORE_SALES1.addOrDelOnZero(se46.modify(item_i_item_id),(v19 * (AGG1ITEM1STORE_SALES1_P_2.getValueOrDefault(se47.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1STORE_SALES1_P_1.getValueOrDefault(se48.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1STORE_SALES1_P_3.getValueOrDefault(se49.modify(store_sales_ss_promo_sk)) * v20)))));
                      n20 = n20->nxt;
                    } while (n20 && (e20 = n20->obj) && h5 == n20->hash &&  AGG1STORE_SALES1STORE_SALES1_P_4_mapkey0_idxfn::equals(se50, *e20)); 
                  }
                }
              n19 = n19->nxt;
            }
          }
        }AGG1.clear();
        {  // foreach
          const HashIndex_AGG1STORE_SALES1_map_0* i21 = static_cast<HashIndex_AGG1STORE_SALES1_map_0*>(AGG1STORE_SALES1.index[0]);
          HashIndex_AGG1STORE_SALES1_map_0::IdxNode* n21; 
          AGG1STORE_SALES1_entry* e21;
        
          for (size_t i = 0; i < i21->size_; i++)
          {
            n21 = i21->buckets_ + i;
            while (n21 && (e21 = n21->obj))
            {
                STRING_TYPE item_i_item_id = e21->ITEM_I_ITEM_ID;
                long v21 = e21->__av;
                DOUBLE_TYPE agg1 = 0.0;
                long l1 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se52.modify(item_i_item_id));
                (/*if */(0L != l1) ? agg1 += Udiv(Ulistmax(1L, l1)) : 0.0);
                AGG1.addOrDelOnZero(se51.modify(item_i_item_id),(v21 * agg1));
              n21 = n21->nxt;
            }
          }
        }AGG2.clear();
        {  // foreach
          const HashIndex_AGG2STORE_SALES1_map_0* i22 = static_cast<HashIndex_AGG2STORE_SALES1_map_0*>(AGG2STORE_SALES1.index[0]);
          HashIndex_AGG2STORE_SALES1_map_0::IdxNode* n22; 
          AGG2STORE_SALES1_entry* e22;
        
          for (size_t i = 0; i < i22->size_; i++)
          {
            n22 = i22->buckets_ + i;
            while (n22 && (e22 = n22->obj))
            {
                STRING_TYPE item_i_item_id = e22->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v22 = e22->__av;
                DOUBLE_TYPE agg2 = 0.0;
                long l2 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se54.modify(item_i_item_id));
                (/*if */(0L != l2) ? agg2 += Udiv(Ulistmax(1L, l2)) : 0.0);
                AGG2.addOrDelOnZero(se53.modify(item_i_item_id),(v22 * agg2));
              n22 = n22->nxt;
            }
          }
        }AGG3.clear();
        {  // foreach
          const HashIndex_AGG3STORE_SALES1_map_0* i23 = static_cast<HashIndex_AGG3STORE_SALES1_map_0*>(AGG3STORE_SALES1.index[0]);
          HashIndex_AGG3STORE_SALES1_map_0::IdxNode* n23; 
          AGG3STORE_SALES1_entry* e23;
        
          for (size_t i = 0; i < i23->size_; i++)
          {
            n23 = i23->buckets_ + i;
            while (n23 && (e23 = n23->obj))
            {
                STRING_TYPE item_i_item_id = e23->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v23 = e23->__av;
                DOUBLE_TYPE agg3 = 0.0;
                long l3 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se56.modify(item_i_item_id));
                (/*if */(0L != l3) ? agg3 += Udiv(Ulistmax(1L, l3)) : 0.0);
                AGG3.addOrDelOnZero(se55.modify(item_i_item_id),(v23 * agg3));
              n23 = n23->nxt;
            }
          }
        }AGG4.clear();
        {  // foreach
          const HashIndex_AGG4STORE_SALES1_map_0* i24 = static_cast<HashIndex_AGG4STORE_SALES1_map_0*>(AGG4STORE_SALES1.index[0]);
          HashIndex_AGG4STORE_SALES1_map_0::IdxNode* n24; 
          AGG4STORE_SALES1_entry* e24;
        
          for (size_t i = 0; i < i24->size_; i++)
          {
            n24 = i24->buckets_ + i;
            while (n24 && (e24 = n24->obj))
            {
                STRING_TYPE item_i_item_id = e24->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v24 = e24->__av;
                DOUBLE_TYPE agg4 = 0.0;
                long l4 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se58.modify(item_i_item_id));
                (/*if */(0L != l4) ? agg4 += Udiv(Ulistmax(1L, l4)) : 0.0);
                AGG4.addOrDelOnZero(se57.modify(item_i_item_id),(v24 * agg4));
              n24 = n24->nxt;
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

        AGG1ITEM2_DOMAIN1.clear();
        AGG1ITEM1_DELTA.clear();
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
                long v25 = 1L;
                AGG1ITEM2_DOMAIN1.addOrDelOnZero(se59.modify(item_i_item_id),(v25 != 0 ? 1L : 0L));
                long v26 = 1L;
                AGG1ITEM1_DELTA.addOrDelOnZero(se60.modify(store_sales_ss_item_sk,item_i_item_id),v26);

          }
        }

        {  // foreach
          const HashIndex_AGG1ITEM2_DOMAIN1_map_0* i27 = static_cast<HashIndex_AGG1ITEM2_DOMAIN1_map_0*>(AGG1ITEM2_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM2_DOMAIN1_map_0::IdxNode* n27; 
          AGG1ITEM2_DOMAIN1_entry* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
                STRING_TYPE item_i_item_id = e27->ITEM_I_ITEM_ID;
                long v27 = e27->__av;
                DOUBLE_TYPE agg5 = 0.0;
                long agg6 = 0L;
                { //slice 
                  const HashIndex_AGG1ITEM1_DELTA_map_1* i28 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1*>(AGG1ITEM1_DELTA.index[1]);
                  const HASH_RES_t h6 = AGG1ITEM1_DELTA_mapkey1_idxfn::hash(se65.modify1(item_i_item_id));
                  HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode* n28 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode*>(i28->slice(se65, h6));
                  AGG1ITEM1_DELTA_entry* e28;
                 
                  if (n28 && (e28 = n28->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e28->STORE_SALES_SS_ITEM_SK;
                      long v28 = e28->__av;
                      agg6 += (v28 * AGG1ITEM2_L1_2.getValueOrDefault(se64.modify(store_sales_ss_item_sk)));
                      n28 = n28->nxt;
                    } while (n28 && (e28 = n28->obj) && h6 == n28->hash &&  AGG1ITEM1_DELTA_mapkey1_idxfn::equals(se65, *e28)); 
                  }
                }long l5 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se63.modify(item_i_item_id)) + agg6);
                (/*if */(0L != l5) ? agg5 += Udiv(Ulistmax(1L, l5)) : 0.0);
                DOUBLE_TYPE agg7 = 0.0;
                long l6 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se66.modify(item_i_item_id));
                (/*if */(0L != l6) ? agg7 += Udiv(Ulistmax(1L, l6)) : 0.0);
                AGG1.addOrDelOnZero(se61.modify(item_i_item_id),((v27 != 0 ? 1L : 0L) * (AGG1STORE_SALES1.getValueOrDefault(se62.modify(item_i_item_id)) * (agg5 + (agg7 * -1L)))));
              n27 = n27->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i29 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n29; 
          AGG1ITEM1_DELTA_entry* e29;
        
          for (size_t i = 0; i < i29->size_; i++)
          {
            n29 = i29->buckets_ + i;
            while (n29 && (e29 = n29->obj))
            {
                long store_sales_ss_item_sk = e29->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e29->ITEM_I_ITEM_ID;
                long v29 = e29->__av;
                long agg8 = 0L;
                agg8 += (AGG1ITEM1_DELTA.getValueOrDefault(se68.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM2_L1_2.getValueOrDefault(se69.modify(store_sales_ss_item_sk)));
                long l7 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se67.modify(item_i_item_id)) + agg8);
                (/*if */(0L != l7) ? AGG1.addOrDelOnZero(se61.modify(item_i_item_id),(v29 * (AGG1ITEM1.getValueOrDefault(se70.modify(store_sales_ss_item_sk)) * Udiv(Ulistmax(1L, l7))))) : (void)0);
              n29 = n29->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i30 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n30; 
          AGG1ITEM1_DELTA_entry* e30;
        
          for (size_t i = 0; i < i30->size_; i++)
          {
            n30 = i30->buckets_ + i;
            while (n30 && (e30 = n30->obj))
            {
                long store_sales_ss_item_sk = e30->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e30->ITEM_I_ITEM_ID;
                long v30 = e30->__av;
                AGG1STORE_SALES1.addOrDelOnZero(se71.modify(item_i_item_id),(v30 * AGG1ITEM1.getValueOrDefault(se72.modify(store_sales_ss_item_sk))));
              n30 = n30->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i31 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n31; 
          AGG1ITEM1_DELTA_entry* e31;
        
          for (size_t i = 0; i < i31->size_; i++)
          {
            n31 = i31->buckets_ + i;
            while (n31 && (e31 = n31->obj))
            {
                long store_sales_ss_item_sk = e31->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e31->ITEM_I_ITEM_ID;
                long v31 = e31->__av;
                AGG1STORE_SALES1STORE_SALES1_P_4.addOrDelOnZero(se73.modify(store_sales_ss_item_sk,item_i_item_id),v31);
              n31 = n31->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM2_DOMAIN1_map_0* i32 = static_cast<HashIndex_AGG1ITEM2_DOMAIN1_map_0*>(AGG1ITEM2_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM2_DOMAIN1_map_0::IdxNode* n32; 
          AGG1ITEM2_DOMAIN1_entry* e32;
        
          for (size_t i = 0; i < i32->size_; i++)
          {
            n32 = i32->buckets_ + i;
            while (n32 && (e32 = n32->obj))
            {
                STRING_TYPE item_i_item_id = e32->ITEM_I_ITEM_ID;
                long v32 = e32->__av;
                DOUBLE_TYPE agg9 = 0.0;
                long agg10 = 0L;
                { //slice 
                  const HashIndex_AGG1ITEM1_DELTA_map_1* i33 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1*>(AGG1ITEM1_DELTA.index[1]);
                  const HASH_RES_t h7 = AGG1ITEM1_DELTA_mapkey1_idxfn::hash(se78.modify1(item_i_item_id));
                  HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode* n33 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode*>(i33->slice(se78, h7));
                  AGG1ITEM1_DELTA_entry* e33;
                 
                  if (n33 && (e33 = n33->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e33->STORE_SALES_SS_ITEM_SK;
                      long v33 = e33->__av;
                      agg10 += (v33 * AGG1ITEM2_L1_2.getValueOrDefault(se77.modify(store_sales_ss_item_sk)));
                      n33 = n33->nxt;
                    } while (n33 && (e33 = n33->obj) && h7 == n33->hash &&  AGG1ITEM1_DELTA_mapkey1_idxfn::equals(se78, *e33)); 
                  }
                }long l8 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se76.modify(item_i_item_id)) + agg10);
                (/*if */(0L != l8) ? agg9 += Udiv(Ulistmax(1L, l8)) : 0.0);
                DOUBLE_TYPE agg11 = 0.0;
                long l9 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se79.modify(item_i_item_id));
                (/*if */(0L != l9) ? agg11 += Udiv(Ulistmax(1L, l9)) : 0.0);
                AGG2.addOrDelOnZero(se74.modify(item_i_item_id),((v32 != 0 ? 1L : 0L) * (AGG2STORE_SALES1.getValueOrDefault(se75.modify(item_i_item_id)) * (agg9 + (agg11 * -1L)))));
              n32 = n32->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i34 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n34; 
          AGG1ITEM1_DELTA_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                long store_sales_ss_item_sk = e34->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e34->ITEM_I_ITEM_ID;
                long v34 = e34->__av;
                long agg12 = 0L;
                agg12 += (AGG1ITEM1_DELTA.getValueOrDefault(se81.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM2_L1_2.getValueOrDefault(se82.modify(store_sales_ss_item_sk)));
                long l10 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se80.modify(item_i_item_id)) + agg12);
                (/*if */(0L != l10) ? AGG2.addOrDelOnZero(se74.modify(item_i_item_id),(v34 * (AGG2ITEM1.getValueOrDefault(se83.modify(store_sales_ss_item_sk)) * Udiv(Ulistmax(1L, l10))))) : (void)0);
              n34 = n34->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i35 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n35; 
          AGG1ITEM1_DELTA_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                long store_sales_ss_item_sk = e35->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e35->ITEM_I_ITEM_ID;
                long v35 = e35->__av;
                AGG2STORE_SALES1.addOrDelOnZero(se84.modify(item_i_item_id),(v35 * AGG2ITEM1.getValueOrDefault(se85.modify(store_sales_ss_item_sk))));
              n35 = n35->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM2_DOMAIN1_map_0* i36 = static_cast<HashIndex_AGG1ITEM2_DOMAIN1_map_0*>(AGG1ITEM2_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM2_DOMAIN1_map_0::IdxNode* n36; 
          AGG1ITEM2_DOMAIN1_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                STRING_TYPE item_i_item_id = e36->ITEM_I_ITEM_ID;
                long v36 = e36->__av;
                DOUBLE_TYPE agg13 = 0.0;
                long agg14 = 0L;
                { //slice 
                  const HashIndex_AGG1ITEM1_DELTA_map_1* i37 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1*>(AGG1ITEM1_DELTA.index[1]);
                  const HASH_RES_t h8 = AGG1ITEM1_DELTA_mapkey1_idxfn::hash(se90.modify1(item_i_item_id));
                  HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode* n37 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode*>(i37->slice(se90, h8));
                  AGG1ITEM1_DELTA_entry* e37;
                 
                  if (n37 && (e37 = n37->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e37->STORE_SALES_SS_ITEM_SK;
                      long v37 = e37->__av;
                      agg14 += (v37 * AGG1ITEM2_L1_2.getValueOrDefault(se89.modify(store_sales_ss_item_sk)));
                      n37 = n37->nxt;
                    } while (n37 && (e37 = n37->obj) && h8 == n37->hash &&  AGG1ITEM1_DELTA_mapkey1_idxfn::equals(se90, *e37)); 
                  }
                }long l11 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se88.modify(item_i_item_id)) + agg14);
                (/*if */(0L != l11) ? agg13 += Udiv(Ulistmax(1L, l11)) : 0.0);
                DOUBLE_TYPE agg15 = 0.0;
                long l12 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se91.modify(item_i_item_id));
                (/*if */(0L != l12) ? agg15 += Udiv(Ulistmax(1L, l12)) : 0.0);
                AGG3.addOrDelOnZero(se86.modify(item_i_item_id),((v36 != 0 ? 1L : 0L) * (AGG3STORE_SALES1.getValueOrDefault(se87.modify(item_i_item_id)) * (agg13 + (agg15 * -1L)))));
              n36 = n36->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i38 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n38; 
          AGG1ITEM1_DELTA_entry* e38;
        
          for (size_t i = 0; i < i38->size_; i++)
          {
            n38 = i38->buckets_ + i;
            while (n38 && (e38 = n38->obj))
            {
                long store_sales_ss_item_sk = e38->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e38->ITEM_I_ITEM_ID;
                long v38 = e38->__av;
                long agg16 = 0L;
                agg16 += (AGG1ITEM1_DELTA.getValueOrDefault(se93.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM2_L1_2.getValueOrDefault(se94.modify(store_sales_ss_item_sk)));
                long l13 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se92.modify(item_i_item_id)) + agg16);
                (/*if */(0L != l13) ? AGG3.addOrDelOnZero(se86.modify(item_i_item_id),(v38 * (AGG3ITEM1.getValueOrDefault(se95.modify(store_sales_ss_item_sk)) * Udiv(Ulistmax(1L, l13))))) : (void)0);
              n38 = n38->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i39 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n39; 
          AGG1ITEM1_DELTA_entry* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
                long store_sales_ss_item_sk = e39->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e39->ITEM_I_ITEM_ID;
                long v39 = e39->__av;
                AGG3STORE_SALES1.addOrDelOnZero(se96.modify(item_i_item_id),(v39 * AGG3ITEM1.getValueOrDefault(se97.modify(store_sales_ss_item_sk))));
              n39 = n39->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM2_DOMAIN1_map_0* i40 = static_cast<HashIndex_AGG1ITEM2_DOMAIN1_map_0*>(AGG1ITEM2_DOMAIN1.index[0]);
          HashIndex_AGG1ITEM2_DOMAIN1_map_0::IdxNode* n40; 
          AGG1ITEM2_DOMAIN1_entry* e40;
        
          for (size_t i = 0; i < i40->size_; i++)
          {
            n40 = i40->buckets_ + i;
            while (n40 && (e40 = n40->obj))
            {
                STRING_TYPE item_i_item_id = e40->ITEM_I_ITEM_ID;
                long v40 = e40->__av;
                DOUBLE_TYPE agg17 = 0.0;
                long agg18 = 0L;
                { //slice 
                  const HashIndex_AGG1ITEM1_DELTA_map_1* i41 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1*>(AGG1ITEM1_DELTA.index[1]);
                  const HASH_RES_t h9 = AGG1ITEM1_DELTA_mapkey1_idxfn::hash(se102.modify1(item_i_item_id));
                  HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode* n41 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_1::IdxNode*>(i41->slice(se102, h9));
                  AGG1ITEM1_DELTA_entry* e41;
                 
                  if (n41 && (e41 = n41->obj)) {
                    do {                
                      long store_sales_ss_item_sk = e41->STORE_SALES_SS_ITEM_SK;
                      long v41 = e41->__av;
                      agg18 += (v41 * AGG1ITEM2_L1_2.getValueOrDefault(se101.modify(store_sales_ss_item_sk)));
                      n41 = n41->nxt;
                    } while (n41 && (e41 = n41->obj) && h9 == n41->hash &&  AGG1ITEM1_DELTA_mapkey1_idxfn::equals(se102, *e41)); 
                  }
                }long l14 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se100.modify(item_i_item_id)) + agg18);
                (/*if */(0L != l14) ? agg17 += Udiv(Ulistmax(1L, l14)) : 0.0);
                DOUBLE_TYPE agg19 = 0.0;
                long l15 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se103.modify(item_i_item_id));
                (/*if */(0L != l15) ? agg19 += Udiv(Ulistmax(1L, l15)) : 0.0);
                AGG4.addOrDelOnZero(se98.modify(item_i_item_id),((v40 != 0 ? 1L : 0L) * (AGG4STORE_SALES1.getValueOrDefault(se99.modify(item_i_item_id)) * (agg17 + (agg19 * -1L)))));
              n40 = n40->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i42 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n42; 
          AGG1ITEM1_DELTA_entry* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
                long store_sales_ss_item_sk = e42->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e42->ITEM_I_ITEM_ID;
                long v42 = e42->__av;
                long agg20 = 0L;
                agg20 += (AGG1ITEM1_DELTA.getValueOrDefault(se105.modify(store_sales_ss_item_sk,item_i_item_id)) * AGG1ITEM2_L1_2.getValueOrDefault(se106.modify(store_sales_ss_item_sk)));
                long l16 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se104.modify(item_i_item_id)) + agg20);
                (/*if */(0L != l16) ? AGG4.addOrDelOnZero(se98.modify(item_i_item_id),(v42 * (AGG4ITEM1.getValueOrDefault(se107.modify(store_sales_ss_item_sk)) * Udiv(Ulistmax(1L, l16))))) : (void)0);
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i43 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n43; 
          AGG1ITEM1_DELTA_entry* e43;
        
          for (size_t i = 0; i < i43->size_; i++)
          {
            n43 = i43->buckets_ + i;
            while (n43 && (e43 = n43->obj))
            {
                long store_sales_ss_item_sk = e43->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e43->ITEM_I_ITEM_ID;
                long v43 = e43->__av;
                AGG1STORE_SALES1_L1_1.addOrDelOnZero(se108.modify(item_i_item_id),(v43 * AGG1ITEM2_L1_2.getValueOrDefault(se109.modify(store_sales_ss_item_sk))));
              n43 = n43->nxt;
            }
          }
        }{  // foreach
          const HashIndex_AGG1ITEM1_DELTA_map_01* i44 = static_cast<HashIndex_AGG1ITEM1_DELTA_map_01*>(AGG1ITEM1_DELTA.index[0]);
          HashIndex_AGG1ITEM1_DELTA_map_01::IdxNode* n44; 
          AGG1ITEM1_DELTA_entry* e44;
        
          for (size_t i = 0; i < i44->size_; i++)
          {
            n44 = i44->buckets_ + i;
            while (n44 && (e44 = n44->obj))
            {
                long store_sales_ss_item_sk = e44->STORE_SALES_SS_ITEM_SK;
                STRING_TYPE item_i_item_id = e44->ITEM_I_ITEM_ID;
                long v44 = e44->__av;
                AGG4STORE_SALES1.addOrDelOnZero(se110.modify(item_i_item_id),(v44 * AGG4ITEM1.getValueOrDefault(se111.modify(store_sales_ss_item_sk))));
              n44 = n44->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        AGG1ITEM1STORE_SALES1_P_1.clear();
        long l17 = 1998L;
        { //slice 
          const HashIndex_DATE_DIM_map_6* i45 = static_cast<HashIndex_DATE_DIM_map_6*>(DATE_DIM.index[1]);
          const HASH_RES_t h10 = DATE_DIM_mapkey6_idxfn::hash(se113.modify6(l17));
          HashIndex_DATE_DIM_map_6::IdxNode* n45 = static_cast<HashIndex_DATE_DIM_map_6::IdxNode*>(i45->slice(se113, h10));
          DATE_DIM_entry* e45;
         
          if (n45 && (e45 = n45->obj)) {
            do {                
              long store_sales_ss_sold_date_sk = e45->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e45->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e45->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e45->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e45->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e45->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e45->DATE_DIM_D_DOW;
              long date_dim_d_moy = e45->DATE_DIM_D_MOY;
              long date_dim_d_dom = e45->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e45->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e45->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e45->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e45->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_day_name = e45->DATE_DIM_D_DAY_NAME;
              STRING_TYPE date_dim_d_quarter_name = e45->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e45->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e45->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e45->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e45->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e45->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e45->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e45->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e45->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e45->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e45->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e45->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e45->DATE_DIM_D_CURRENT_YEAR;
              long v45 = e45->__av;
              AGG1ITEM1STORE_SALES1_P_1.addOrDelOnZero(se112.modify(store_sales_ss_sold_date_sk),v45);
              n45 = n45->nxt;
            } while (n45 && (e45 = n45->obj) && h10 == n45->hash &&  DATE_DIM_mapkey6_idxfn::equals(se113, *e45)); 
          }
        }AGG1ITEM1STORE_SALES1_P_2.clear();
        STRING_TYPE l18 = c1;
        STRING_TYPE l19 = c2;
        STRING_TYPE l20 = c3;
        { //slice 
          const HashIndex_CUSTOMER_DEMOGRAPHICS_map_123* i46 = static_cast<HashIndex_CUSTOMER_DEMOGRAPHICS_map_123*>(CUSTOMER_DEMOGRAPHICS.index[1]);
          const HASH_RES_t h11 = CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn::hash(se115.modify123(l20, l19, l18));
          HashIndex_CUSTOMER_DEMOGRAPHICS_map_123::IdxNode* n46 = static_cast<HashIndex_CUSTOMER_DEMOGRAPHICS_map_123::IdxNode*>(i46->slice(se115, h11));
          CUSTOMER_DEMOGRAPHICS_entry* e46;
         
          if (n46 && (e46 = n46->obj)) {
            do {                
              long store_sales_ss_cdemo_sk = e46->CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK;
              long customer_demographics_cd_purchase_estimate = e46->CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE;
              STRING_TYPE customer_demographics_cd_credit_rating = e46->CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING;
              long customer_demographics_cd_dep_count = e46->CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT;
              long customer_demographics_cd_dep_employed_count = e46->CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT;
              long customer_demographics_cd_dep_college_count = e46->CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT;
              long v46 = e46->__av;
              AGG1ITEM1STORE_SALES1_P_2.addOrDelOnZero(se114.modify(store_sales_ss_cdemo_sk),v46);
              n46 = n46->nxt;
            } while (n46 && (e46 = n46->obj) && h11 == n46->hash &&  CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn::equals(se115, *e46)); 
          }
        }AGG1ITEM1STORE_SALES1_P_3.clear();
        {  // foreach
          const HashIndex_PROMOTION_map_0123456789101112131415161718* i47 = static_cast<HashIndex_PROMOTION_map_0123456789101112131415161718*>(PROMOTION.index[0]);
          HashIndex_PROMOTION_map_0123456789101112131415161718::IdxNode* n47; 
          PROMOTION_entry* e47;
        
          for (size_t i = 0; i < i47->size_; i++)
          {
            n47 = i47->buckets_ + i;
            while (n47 && (e47 = n47->obj))
            {
                long store_sales_ss_promo_sk = e47->PROMOTION_P_PROMO_SK;
                STRING_TYPE promotion_p_promo_id = e47->PROMOTION_P_PROMO_ID;
                long promotion_p_start_date_sk = e47->PROMOTION_P_START_DATE_SK;
                long promotion_p_end_date_sk = e47->PROMOTION_P_END_DATE_SK;
                long promotion_p_item_sk = e47->PROMOTION_P_ITEM_SK;
                DOUBLE_TYPE promotion_p_cost = e47->PROMOTION_P_COST;
                long promotion_p_response_target = e47->PROMOTION_P_RESPONSE_TARGET;
                STRING_TYPE promotion_p_promo_name = e47->PROMOTION_P_PROMO_NAME;
                STRING_TYPE promotion_p_channel_dmail = e47->PROMOTION_P_CHANNEL_DMAIL;
                STRING_TYPE promotion_p_channel_email = e47->PROMOTION_P_CHANNEL_EMAIL;
                STRING_TYPE promotion_p_channel_catalog = e47->PROMOTION_P_CHANNEL_CATALOG;
                STRING_TYPE promotion_p_channel_tv = e47->PROMOTION_P_CHANNEL_TV;
                STRING_TYPE promotion_p_channel_radio = e47->PROMOTION_P_CHANNEL_RADIO;
                STRING_TYPE promotion_p_channel_press = e47->PROMOTION_P_CHANNEL_PRESS;
                STRING_TYPE promotion_p_channel_event = e47->PROMOTION_P_CHANNEL_EVENT;
                STRING_TYPE promotion_p_channel_demo = e47->PROMOTION_P_CHANNEL_DEMO;
                STRING_TYPE promotion_p_channel_details = e47->PROMOTION_P_CHANNEL_DETAILS;
                STRING_TYPE promotion_p_purpose = e47->PROMOTION_P_PURPOSE;
                STRING_TYPE promotion_p_discount_active = e47->PROMOTION_P_DISCOUNT_ACTIVE;
                long v47 = e47->__av;
                long l21 = ((/*if */(promotion_p_channel_email == c4) ? 1L : 0L) + (/*if */(promotion_p_channel_event == c4) ? 1L : 0L));
                (/*if */(l21 > 0L) ? AGG1ITEM1STORE_SALES1_P_3.addOrDelOnZero(se116.modify(store_sales_ss_promo_sk),v47) : (void)0);
              n47 = n47->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    AGG1ITEM1STORE_SALES1_DELTA_entry se1;
    AGG1ITEM2_L1_2STORE_SALES1_DELTA_entry se2;
    AGG2ITEM1STORE_SALES1_DELTA_entry se3;
    AGG3ITEM1STORE_SALES1_DELTA_entry se4;
    AGG4ITEM1STORE_SALES1_DELTA_entry se5;
    AGG1ITEM1_entry se6;
    AGG1ITEM1STORE_SALES1_P_1_entry se7;
    AGG1ITEM1STORE_SALES1_P_2_entry se8;
    AGG1ITEM1STORE_SALES1_P_3_entry se9;
    AGG1ITEM2_L1_2_entry se10;
    AGG1ITEM1STORE_SALES1_P_2_entry se11;
    AGG1ITEM1STORE_SALES1_P_1_entry se12;
    AGG1ITEM1STORE_SALES1_P_3_entry se13;
    AGG1STORE_SALES1_entry se14;
    AGG1ITEM1STORE_SALES1_P_2_entry se15;
    AGG1ITEM1STORE_SALES1_P_1_entry se16;
    AGG1ITEM1STORE_SALES1_P_3_entry se17;
    AGG1STORE_SALES1STORE_SALES1_P_4_entry se18;
    AGG1STORE_SALES1_L1_1_entry se19;
    AGG1ITEM1STORE_SALES1_P_1_entry se20;
    AGG1ITEM1STORE_SALES1_P_2_entry se21;
    AGG1ITEM1STORE_SALES1_P_3_entry se22;
    AGG1STORE_SALES1STORE_SALES1_P_4_entry se23;
    AGG2ITEM1_entry se24;
    AGG1ITEM1STORE_SALES1_P_1_entry se25;
    AGG1ITEM1STORE_SALES1_P_2_entry se26;
    AGG1ITEM1STORE_SALES1_P_3_entry se27;
    AGG2STORE_SALES1_entry se28;
    AGG1ITEM1STORE_SALES1_P_2_entry se29;
    AGG1ITEM1STORE_SALES1_P_1_entry se30;
    AGG1ITEM1STORE_SALES1_P_3_entry se31;
    AGG1STORE_SALES1STORE_SALES1_P_4_entry se32;
    AGG3ITEM1_entry se33;
    AGG1ITEM1STORE_SALES1_P_1_entry se34;
    AGG1ITEM1STORE_SALES1_P_2_entry se35;
    AGG1ITEM1STORE_SALES1_P_3_entry se36;
    AGG3STORE_SALES1_entry se37;
    AGG1ITEM1STORE_SALES1_P_2_entry se38;
    AGG1ITEM1STORE_SALES1_P_1_entry se39;
    AGG1ITEM1STORE_SALES1_P_3_entry se40;
    AGG1STORE_SALES1STORE_SALES1_P_4_entry se41;
    AGG4ITEM1_entry se42;
    AGG1ITEM1STORE_SALES1_P_1_entry se43;
    AGG1ITEM1STORE_SALES1_P_2_entry se44;
    AGG1ITEM1STORE_SALES1_P_3_entry se45;
    AGG4STORE_SALES1_entry se46;
    AGG1ITEM1STORE_SALES1_P_2_entry se47;
    AGG1ITEM1STORE_SALES1_P_1_entry se48;
    AGG1ITEM1STORE_SALES1_P_3_entry se49;
    AGG1STORE_SALES1STORE_SALES1_P_4_entry se50;
    AGG1_entry se51;
    AGG1STORE_SALES1_L1_1_entry se52;
    AGG2_entry se53;
    AGG1STORE_SALES1_L1_1_entry se54;
    AGG3_entry se55;
    AGG1STORE_SALES1_L1_1_entry se56;
    AGG4_entry se57;
    AGG1STORE_SALES1_L1_1_entry se58;
    AGG1ITEM2_DOMAIN1_entry se59;
    AGG1ITEM1_DELTA_entry se60;
    AGG1_entry se61;
    AGG1STORE_SALES1_entry se62;
    AGG1STORE_SALES1_L1_1_entry se63;
    AGG1ITEM2_L1_2_entry se64;
    AGG1ITEM1_DELTA_entry se65;
    AGG1STORE_SALES1_L1_1_entry se66;
    AGG1STORE_SALES1_L1_1_entry se67;
    AGG1ITEM1_DELTA_entry se68;
    AGG1ITEM2_L1_2_entry se69;
    AGG1ITEM1_entry se70;
    AGG1STORE_SALES1_entry se71;
    AGG1ITEM1_entry se72;
    AGG1STORE_SALES1STORE_SALES1_P_4_entry se73;
    AGG2_entry se74;
    AGG2STORE_SALES1_entry se75;
    AGG1STORE_SALES1_L1_1_entry se76;
    AGG1ITEM2_L1_2_entry se77;
    AGG1ITEM1_DELTA_entry se78;
    AGG1STORE_SALES1_L1_1_entry se79;
    AGG1STORE_SALES1_L1_1_entry se80;
    AGG1ITEM1_DELTA_entry se81;
    AGG1ITEM2_L1_2_entry se82;
    AGG2ITEM1_entry se83;
    AGG2STORE_SALES1_entry se84;
    AGG2ITEM1_entry se85;
    AGG3_entry se86;
    AGG3STORE_SALES1_entry se87;
    AGG1STORE_SALES1_L1_1_entry se88;
    AGG1ITEM2_L1_2_entry se89;
    AGG1ITEM1_DELTA_entry se90;
    AGG1STORE_SALES1_L1_1_entry se91;
    AGG1STORE_SALES1_L1_1_entry se92;
    AGG1ITEM1_DELTA_entry se93;
    AGG1ITEM2_L1_2_entry se94;
    AGG3ITEM1_entry se95;
    AGG3STORE_SALES1_entry se96;
    AGG3ITEM1_entry se97;
    AGG4_entry se98;
    AGG4STORE_SALES1_entry se99;
    AGG1STORE_SALES1_L1_1_entry se100;
    AGG1ITEM2_L1_2_entry se101;
    AGG1ITEM1_DELTA_entry se102;
    AGG1STORE_SALES1_L1_1_entry se103;
    AGG1STORE_SALES1_L1_1_entry se104;
    AGG1ITEM1_DELTA_entry se105;
    AGG1ITEM2_L1_2_entry se106;
    AGG4ITEM1_entry se107;
    AGG1STORE_SALES1_L1_1_entry se108;
    AGG1ITEM2_L1_2_entry se109;
    AGG4STORE_SALES1_entry se110;
    AGG4ITEM1_entry se111;
    AGG1ITEM1STORE_SALES1_P_1_entry se112;
    DATE_DIM_entry se113;
    AGG1ITEM1STORE_SALES1_P_2_entry se114;
    CUSTOMER_DEMOGRAPHICS_entry se115;
    AGG1ITEM1STORE_SALES1_P_3_entry se116;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    CUSTOMER_DEMOGRAPHICS_map CUSTOMER_DEMOGRAPHICS;
    PROMOTION_map PROMOTION;
    AGG1ITEM1_DELTA_map AGG1ITEM1_DELTA;
    AGG1ITEM1_map AGG1ITEM1;
    AGG1ITEM1STORE_SALES1_DELTA_map AGG1ITEM1STORE_SALES1_DELTA;
    AGG1ITEM1STORE_SALES1_P_1_map AGG1ITEM1STORE_SALES1_P_1;
    AGG1ITEM1STORE_SALES1_P_2_map AGG1ITEM1STORE_SALES1_P_2;
    AGG1ITEM1STORE_SALES1_P_3_map AGG1ITEM1STORE_SALES1_P_3;
    AGG1ITEM2_DOMAIN1_map AGG1ITEM2_DOMAIN1;
    AGG1ITEM2_L1_2_map AGG1ITEM2_L1_2;
    AGG1ITEM2_L1_2STORE_SALES1_DELTA_map AGG1ITEM2_L1_2STORE_SALES1_DELTA;
    AGG1STORE_SALES1_map AGG1STORE_SALES1;
    AGG1STORE_SALES1STORE_SALES1_P_4_map AGG1STORE_SALES1STORE_SALES1_P_4;
    AGG1STORE_SALES1_L1_1_map AGG1STORE_SALES1_L1_1;
    AGG2ITEM1_map AGG2ITEM1;
    AGG2ITEM1STORE_SALES1_DELTA_map AGG2ITEM1STORE_SALES1_DELTA;
    AGG2STORE_SALES1_map AGG2STORE_SALES1;
    AGG3ITEM1_map AGG3ITEM1;
    AGG3ITEM1STORE_SALES1_DELTA_map AGG3ITEM1STORE_SALES1_DELTA;
    AGG3STORE_SALES1_map AGG3STORE_SALES1;
    AGG4ITEM1_map AGG4ITEM1;
    AGG4ITEM1STORE_SALES1_DELTA_map AGG4ITEM1STORE_SALES1_DELTA;
    AGG4STORE_SALES1_map AGG4STORE_SALES1;
    DELTA_STORE_SALES_map DELTA_STORE_SALES;
    DELTA_ITEM_map DELTA_ITEM;
    
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
  
  };

}
