#ifndef DBTOASTER_TEST_TEMPLATE_HPP
#define DBTOASTER_TEST_TEMPLATE_HPP

#include "stopwatch.hpp"

const string dataPath = "datasets/tpcds";
const string dataset = "1GB";

namespace dbtoaster 
{

    #ifdef USE_TPCDS_DATEDIM 
        #define IF_DATEDIM(stmt) stmt
    #else
        #define IF_DATEDIM(stmt) 
    #endif

    #ifdef USE_TPCDS_STORESALES 
        #define IF_STORESALES(stmt) stmt
    #else
        #define IF_STORESALES(stmt) 
    #endif

    #ifdef USE_TPCDS_ITEM 
        #define IF_ITEM(stmt) stmt
    #else
        #define IF_ITEM(stmt) 
    #endif

    #ifdef USE_TPCDS_CUSTOMER
        #define IF_CUSTOMER(stmt) stmt
    #else
        #define IF_CUSTOMER(stmt) 
    #endif

    #ifdef USE_TPCDS_CUSTOMERADDRESS
        #define IF_CUSTOMERADDRESS(stmt) stmt
    #else
        #define IF_CUSTOMERADDRESS(stmt) 
    #endif

    #ifdef USE_TPCDS_STORE
        #define IF_STORE(stmt) stmt
    #else
        #define IF_STORE(stmt) 
    #endif

    #ifdef USE_TPCDS_HOUSEHOLDDEMOGRAPHICS
        #define IF_HOUSEHOLDDEMOGRAPHICS(stmt) stmt
    #else
        #define IF_HOUSEHOLDDEMOGRAPHICS(stmt) 
    #endif

    #ifdef USE_TPCDS_CUSTOMERDEMOGRAPHICS 
        #define IF_CUSTOMERDEMOGRAPHICS(stmt) stmt
    #else
        #define IF_CUSTOMERDEMOGRAPHICS(stmt) 
    #endif

    #ifdef USE_TPCDS_PROMOTION
        #define IF_PROMOTION(stmt) stmt
    #else
        #define IF_PROMOTION(stmt) 
    #endif

    class data_t;

    IF_DATEDIM ( TPCDSDateDimBatch* dateDimBatch; )
    IF_STORESALES ( TPCDSStoreSalesBatch* storeSalesBatch; )
    IF_ITEM ( TPCDSItemBatch* itemBatch; )
    IF_CUSTOMER ( TPCDSCustomerBatch* customerBatch; )
    IF_CUSTOMERADDRESS ( TPCDSCustomerAddressBatch* customerAddressBatch; )
    IF_STORE ( TPCDSStoreBatch* storeBatch; )
    IF_HOUSEHOLDDEMOGRAPHICS  ( TPCDSHouseholdDemographicsBatch*  householdDemographicsBatch; )
    IF_CUSTOMERDEMOGRAPHICS ( TPCDSCustomerDemographicsBatch* customerDemographicsBatch; )
    IF_PROMOTION ( TPCDSPromotionBatch* promotionBatch; )


    void load_relations()
    {
        Stopwatch sw;

        IF_DATEDIM ({
            sw.restart();
            std::vector<TPCDSDateDim> vDateDim;
            //readFromBinaryFile(vDateDim, dataPath + "/" + dataset + "/date_dim.bin");
            readFromFile(vDateDim, dataPath + "/" + dataset + "/date_dim.dat", '|');
            //writeToBinaryFile(vDateDim, dataPath + "/" + dataset + "/date_dim.bin");
            dateDimBatch = new TPCDSDateDimBatch(vDateDim);
            sw.stop();
            std::cout << "Loaded date_dim (" << dateDimBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_STORESALES ({
            sw.restart();
            std::vector<TPCDSStoreSales> vStoreSales;
            //readFromBinaryFile(vStoreSales, dataPath + "/" + dataset + "/store_sales.bin");
            readFromFile(vStoreSales, dataPath + "/" + dataset + "/store_sales.dat", '|');
            //writeToBinaryFile(vStoreSales, dataPath + "/" + dataset + "/store_sales.bin");
            storeSalesBatch = new TPCDSStoreSalesBatch(vStoreSales);
            sw.stop();
            std::cout << "Loaded store_sales (" << storeSalesBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_ITEM ({
            sw.restart();
            std::vector<TPCDSItem> vItem;
            //readFromBinaryFile(vItem, dataPath + "/" + dataset + "/item.bin");
            readFromFile(vItem, dataPath + "/" + dataset + "/item.dat", '|');
            //writeToBinaryFile(vItem, dataPath + "/" + dataset + "/item.bin");
            itemBatch = new TPCDSItemBatch(vItem);
            sw.stop();
            std::cout << "Loaded item (" << itemBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_CUSTOMER ({
            sw.restart();
            std::vector<TPCDSCustomer> vCustomer;
            //readFromBinaryFile(vCustomer, dataPath + "/" + dataset + "/customer.bin");
            readFromFile(vCustomer, dataPath + "/" + dataset + "/customer.dat", '|');
            //writeToBinaryFile(vCustomer, dataPath + "/" + dataset + "/customer.bin");
            customerBatch = new TPCDSCustomerBatch(vCustomer);
            sw.stop();
            std::cout << "Loaded Customer (" << customerBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_CUSTOMERADDRESS ({
            sw.restart();
            std::vector<TPCDSCustomerAddress> vCustomerAddress;
            //readFromBinaryFile(vCustomerAddress, dataPath + "/" + dataset + "/customer_address.bin");
            readFromFile(vCustomerAddress, dataPath + "/" + dataset + "/customer_address.dat", '|');
            //writeToBinaryFile(vCustomerAddress, dataPath + "/" + dataset + "/customer_address.bin");
            customerAddressBatch = new TPCDSCustomerAddressBatch(vCustomerAddress);
            sw.stop();
            std::cout << "Loaded customer_address (" << customerAddressBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_STORE ({
            sw.restart();
            std::vector<TPCDSStore> vStore;
            //readFromBinaryFile(vStore, dataPath + "/" + dataset + "/store.bin");
            readFromFile(vStore, dataPath + "/" + dataset + "/store.dat", '|');
            //writeToBinaryFile(vStore, dataPath + "/" + dataset + "/store.bin");
            storeBatch = new TPCDSStoreBatch(vStore);
            sw.stop();
            std::cout << "Loaded store (" << storeBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_HOUSEHOLDDEMOGRAPHICS ({
            sw.restart();
            std::vector<TPCDSHouseholdDemographics> vHouseholdDemographics;
            //readFromBinaryFile(vHouseholdDemographics, dataPath + "/" + dataset + "/household_demographics.bin");
            readFromFile(vHouseholdDemographics, dataPath + "/" + dataset + "/household_demographics.dat", '|');
            //writeToBinaryFile(vHouseholdDemographics, dataPath + "/" + dataset + "/household_demographics.bin");
            householdDemographicsBatch = new TPCDSHouseholdDemographicsBatch(vHouseholdDemographics);
            sw.stop();
            std::cout << "Loaded household_demographics (" << householdDemographicsBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_CUSTOMERDEMOGRAPHICS ({
            sw.restart();
            std::vector<TPCDSCustomerDemographics> vCustomerDemographics;
            //readFromBinaryFile(vCustomerDemographics, dataPath + "/" + dataset + "/customer_demographics.bin");
            readFromFile(vCustomerDemographics, dataPath + "/" + dataset + "/customer_demographics.dat", '|');
            //writeToBinaryFile(vCustomerDemographics, dataPath + "/" + dataset + "/customer_demographics.bin");
            customerDemographicsBatch = new TPCDSCustomerDemographicsBatch(vCustomerDemographics);
            sw.stop();
            std::cout << "Loaded customer_demographics (" << customerDemographicsBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

        IF_PROMOTION ({
            sw.restart();
            std::vector<TPCDSPromotion> vPromotion;
            //readFromBinaryFile(vPromotion, dataPath + "/" + dataset + "/promotion.bin");
            readFromFile(vPromotion, dataPath + "/" + dataset + "/promotion.dat", '|');
            //writeToBinaryFile(vPromotion, dataPath + "/" + dataset + "/promotion.bin");
            promotionBatch = new TPCDSPromotionBatch(vPromotion);
            sw.stop();
            std::cout << "Loaded promotion (" << promotionBatch->size << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        })

    }

    void destroy_relations()
    {
        IF_DATEDIM ( delete dateDimBatch; )
        IF_STORESALES ( delete storeSalesBatch; )
        IF_ITEM ( delete itemBatch; )
        IF_CUSTOMER ( delete customerBatch; )
        IF_CUSTOMERADDRESS ( delete customerAddressBatch; )
        IF_STORE ( delete storeBatch; )
        IF_HOUSEHOLDDEMOGRAPHICS  ( delete householdDemographicsBatch; )
        IF_CUSTOMERDEMOGRAPHICS ( delete customerDemographicsBatch; )
        IF_PROMOTION ( delete promotionBatch; )
    }


#ifdef BATCH_MODE

    // Vectors storing batch updates
    IF_DATEDIM( std::vector<TPCDSDateDimBatch> dateDimBatchList; )
    IF_STORESALES( std::vector<TPCDSStoreSalesBatch> storeSalesBatchList; )
    IF_ITEM( std::vector<TPCDSItemBatch> itemBatchList; )
    IF_CUSTOMER( std::vector<TPCDSCustomerBatch> customerBatchList; )
    IF_CUSTOMERADDRESS( std::vector<TPCDSCustomerAddressBatch> customerAddressBatchList; )
    IF_STORE( std::vector<TPCDSStoreBatch> storeBatchList; )
    IF_HOUSEHOLDDEMOGRAPHICS( std::vector<TPCDSHouseholdDemographicsBatch> householdDemographicsBatchList; )
    IF_CUSTOMERDEMOGRAPHICS( std::vector<TPCDSCustomerDemographicsBatch> customerDemographicsBatchList; )
    IF_PROMOTION( std::vector<TPCDSPromotionBatch> promotionBatchList; )


    #define FLUSH_DATEDIM_BATCH {                      \
        TPCDSDateDimBatch batch(tmpDateDimBatch);      \
        dateDimBatchList.push_back(batch);             \
        tmpDateDimBatch.size = 0;                      \
    }

    #define FLUSH_STORESALES_BATCH {                      \
        TPCDSStoreSalesBatch batch(tmpStoreSalesBatch);   \
        storeSalesBatchList.push_back(batch);             \
        tmpStoreSalesBatch.size = 0;                      \
    }

    #define FLUSH_ITEM_BATCH {                      \
        TPCDSItemBatch batch(tmpItemBatch);         \
        itemBatchList.push_back(batch);             \
        tmpItemBatch.size = 0;                      \
    }

    #define FLUSH_CUSTOMER_BATCH {                      \
        TPCDSCustomerBatch batch(tmpCustomerBatch);     \
        customerBatchList.push_back(batch);             \
        tmpCustomerBatch.size = 0;                      \
    }

    #define FLUSH_CUSTOMERADDRESS_BATCH {                           \
        TPCDSCustomerAddressBatch batch(tmpCustomerAddressBatch);   \
        customerAddressBatchList.push_back(batch);                  \
        tmpCustomerAddressBatch.size = 0;                           \
    }

    #define FLUSH_STORE_BATCH {                      \
        TPCDSStoreBatch batch(tmpStoreBatch);        \
        storeBatchList.push_back(batch);             \
        tmpStoreBatch.size = 0;                      \
    }

    #define FLUSH_HOUSEHOLDDEMOGRAPHICS_BATCH {                      \
        TPCDSHouseholdDemographicsBatch batch(tmpHouseholdDemographicsBatch);   \
        householdDemographicsBatchList.push_back(batch);             \
        tmpHouseholdDemographicsBatch.size = 0;                      \
    }

    #define FLUSH_CUSTOMERDEMOGRAPHICS_BATCH {                      \
        TPCDSCustomerDemographicsBatch batch(tmpCustomerDemographicsBatch);   \
        customerDemographicsBatchList.push_back(batch);             \
        tmpCustomerDemographicsBatch.size = 0;                      \
    }

    #define FLUSH_PROMOTION_BATCH {                      \
        TPCDSPromotionBatch batch(tmpPromotionBatch);    \
        promotionBatchList.push_back(batch);             \
        tmpPromotionBatch.size = 0;                      \
    }

    #define FLUSH_TABLE_BATCHES {                                              \
        IF_DATEDIM ( if (tmpDateDimBatch.size > 0)  FLUSH_DATEDIM_BATCH      ) \
        IF_HOUSEHOLDDEMOGRAPHICS ( if (tmpHouseholdDemographicsBatch.size > 0) FLUSH_HOUSEHOLDDEMOGRAPHICS_BATCH ) \
        IF_CUSTOMERDEMOGRAPHICS  ( if (tmpCustomerDemographicsBatch.size > 0)  FLUSH_CUSTOMERDEMOGRAPHICS_BATCH  ) \
        IF_PROMOTION ( if (tmpPromotionBatch.size > 0) FLUSH_PROMOTION_BATCH ) \
    }    

    #define FLUSH_STREAM_BATCHES {                                                \
        IF_STORESALES ( if (tmpStoreSalesBatch.size > 0) FLUSH_STORESALES_BATCH ) \
        IF_ITEM       ( if (tmpItemBatch.size > 0)       FLUSH_ITEM_BATCH   )     \
        IF_CUSTOMER   ( if (tmpCustomerBatch.size > 0)   FLUSH_CUSTOMER_BATCH )   \
        IF_CUSTOMERADDRESS ( if (tmpCustomerAddressBatch.size > 0) FLUSH_CUSTOMERADDRESS_BATCH )   \
        IF_STORE      ( if (tmpStoreBatch.size > 0)   FLUSH_STORE_BATCH )   \
    }        

    #define ADD_TO_STORESALES_BATCH {                       \
        tmpStoreSalesBatch.add(                             \
            storeSalesBatch->ss_sold_date_sk[i],            \
            storeSalesBatch->ss_sold_time_sk[i],            \
            storeSalesBatch->ss_item_sk[i],                 \
            storeSalesBatch->ss_customer_sk[i],             \
            storeSalesBatch->ss_cdemo_sk[i],                \
            storeSalesBatch->ss_hdemo_sk[i],                \
            storeSalesBatch->ss_addr_sk[i],                 \
            storeSalesBatch->ss_store_sk[i],                \
            storeSalesBatch->ss_promo_sk[i],                \
            storeSalesBatch->ss_ticket_number[i],           \
            storeSalesBatch->ss_quantity[i],                \
            storeSalesBatch->ss_wholesale_cost[i],          \
            storeSalesBatch->ss_list_price[i],              \
            storeSalesBatch->ss_sales_price[i],             \
            storeSalesBatch->ss_ext_discount_amt[i],        \
            storeSalesBatch->ss_ext_sales_price[i],         \
            storeSalesBatch->ss_ext_wholesale_cost[i],      \
            storeSalesBatch->ss_ext_list_price[i],          \
            storeSalesBatch->ss_ext_tax[i],                 \
            storeSalesBatch->ss_coupon_amt[i],              \
            storeSalesBatch->ss_net_paid[i],                \
            storeSalesBatch->ss_net_paid_inc_tax[i],        \
            storeSalesBatch->ss_net_profit[i]               \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_ITEM_BATCH {               \
        tmpItemBatch.add(                     \
            itemBatch->i_item_sk[i],                    \
            itemBatch->i_item_id[i],                    \
            itemBatch->i_rec_start_date[i],             \
            itemBatch->i_rec_end_date[i],               \
            itemBatch->i_item_desc[i],                  \
            itemBatch->i_current_price[i],              \
            itemBatch->i_wholesale_cost[i],             \
            itemBatch->i_brand_id[i],                   \
            itemBatch->i_brand[i],                      \
            itemBatch->i_class_id[i],                   \
            itemBatch->i_class[i],                      \
            itemBatch->i_category_id[i],                \
            itemBatch->i_category[i],                   \
            itemBatch->i_manufact_id[i],                \
            itemBatch->i_manufact[i],                   \
            itemBatch->i_size[i],                       \
            itemBatch->i_formulation[i],                \
            itemBatch->i_color[i],                      \
            itemBatch->i_units[i],                      \
            itemBatch->i_container[i],                  \
            itemBatch->i_manager_id[i],                 \
            itemBatch->i_product_name[i]                \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_CUSTOMER_BATCH {                         \
        tmpCustomerBatch.add(                               \
            customerBatch->c_customer_sk[i],                \
            customerBatch->c_customer_id[i],                \
            customerBatch->c_current_cdemo_sk[i],           \
            customerBatch->c_current_hdemo_sk[i],           \
            customerBatch->c_current_addr_sk[i],            \
            customerBatch->c_first_shipto_date_sk[i],       \
            customerBatch->c_first_sales_date_sk[i],        \
            customerBatch->c_salutation[i],                 \
            customerBatch->c_first_name[i],                 \
            customerBatch->c_last_name[i],                  \
            customerBatch->c_preferred_cust_flag[i],        \
            customerBatch->c_birth_day[i],                  \
            customerBatch->c_birth_month[i],                \
            customerBatch->c_birth_year[i],                 \
            customerBatch->c_birth_country[i],              \
            customerBatch->c_login[i],                      \
            customerBatch->c_email_address[i],              \
            customerBatch->c_last_review_date[i]            \
        );                                                  \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_CUSTOMERADDRESS_BATCH {                   \
        tmpCustomerAddressBatch.add(                         \
            customerAddressBatch->ca_address_sk[i],          \
            customerAddressBatch->ca_address_id[i],          \
            customerAddressBatch->ca_street_number[i],       \
            customerAddressBatch->ca_street_name[i],         \
            customerAddressBatch->ca_street_type[i],         \
            customerAddressBatch->ca_suite_number[i],        \
            customerAddressBatch->ca_city[i],                \
            customerAddressBatch->ca_county[i],              \
            customerAddressBatch->ca_state[i],               \
            customerAddressBatch->ca_zip[i],                 \
            customerAddressBatch->ca_country[i],             \
            customerAddressBatch->ca_gmt_offset[i],          \
            customerAddressBatch->ca_location_type[i]        \
        );                                                   \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
    }


    #define ADD_TO_STORE_BATCH {                    \
         tmpStoreBatch.add(                         \
            storeBatch->s_store_sk[i],              \
            storeBatch->s_store_id[i],              \
            storeBatch->s_rec_start_date[i],        \
            storeBatch->s_rec_end_date[i],          \
            storeBatch->s_closed_date_sk[i],        \
            storeBatch->s_store_name[i],            \
            storeBatch->s_number_employees[i],      \
            storeBatch->s_floor_space[i],           \
            storeBatch->s_hours[i],                 \
            storeBatch->s_manager[i],               \
            storeBatch->s_market_id[i],             \
            storeBatch->s_geography_class[i],       \
            storeBatch->s_market_desc[i],           \
            storeBatch->s_market_manager[i],        \
            storeBatch->s_division_id[i],           \
            storeBatch->s_division_name[i],         \
            storeBatch->s_company_id[i],            \
            storeBatch->s_company_name[i],          \
            storeBatch->s_street_number[i],         \
            storeBatch->s_street_name[i],           \
            storeBatch->s_street_type[i],           \
            storeBatch->s_suite_number[i],          \
            storeBatch->s_city[i],                  \
            storeBatch->s_county[i],                \
            storeBatch->s_state[i],                 \
            storeBatch->s_zip[i],                   \
            storeBatch->s_country[i],               \
            storeBatch->s_gmt_offset[i],            \
            storeBatch->s_tax_precentage[i]         \
        );                                          \
        if (++batchCounter == batchSize) {      \
            FLUSH_STREAM_BATCHES                \
            batchCounter = 0;                   \
        }                                       \
     }

    #define ADD_TO_DATEDIM_BATCH {                    \
        tmpDateDimBatch.add(                          \
           dateDimBatch->d_date_sk[i],                \
           dateDimBatch->d_date_id[i],                \
           dateDimBatch->d_date[i],                   \
           dateDimBatch->d_month_seq[i],              \
           dateDimBatch->d_week_seq[i],               \
           dateDimBatch->d_quarter_seq[i],            \
           dateDimBatch->d_year[i],                   \
           dateDimBatch->d_dow[i],                    \
           dateDimBatch->d_moy[i],                    \
           dateDimBatch->d_dom[i],                    \
           dateDimBatch->d_qoy[i],                    \
           dateDimBatch->d_fy_year[i],                \
           dateDimBatch->d_fy_quarter_seq[i],         \
           dateDimBatch->d_fy_week_seq[i],            \
           dateDimBatch->d_day_name[i],               \
           dateDimBatch->d_quarter_name[i],           \
           dateDimBatch->d_holiday[i],                \
           dateDimBatch->d_weekend[i],                \
           dateDimBatch->d_following_holiday[i],      \
           dateDimBatch->d_first_dom[i],              \
           dateDimBatch->d_last_dom[i],               \
           dateDimBatch->d_same_day_ly[i],            \
           dateDimBatch->d_same_day_lq[i],            \
           dateDimBatch->d_current_day[i],            \
           dateDimBatch->d_current_week[i],           \
           dateDimBatch->d_current_month[i],          \
           dateDimBatch->d_current_quarter[i],        \
           dateDimBatch->d_current_year[i]            \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_TABLE_BATCHES                 \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_HOUSEHOLDDEMOGRAPHICS_BATCH {                  \
        tmpHouseholdDemographicsBatch.add(                        \
            householdDemographicsBatch->hd_demo_sk[i],             \
            householdDemographicsBatch->hd_income_band_sk[i],      \
            householdDemographicsBatch->hd_buy_potential[i],       \
            householdDemographicsBatch->hd_dep_count[i],           \
            householdDemographicsBatch->hd_vehicle_count[i]        \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_TABLE_BATCHES                 \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_CUSTOMERDEMOGRAPHICS_BATCH {                 \
        tmpCustomerDemographicsBatch.add(                       \
            customerDemographicsBatch->cd_demo_sk[i],                \
            customerDemographicsBatch->cd_gender[i],                 \
            customerDemographicsBatch->cd_marital_status[i],         \
            customerDemographicsBatch->cd_education_status[i],       \
            customerDemographicsBatch->cd_purchase_estimate[i],      \
            customerDemographicsBatch->cd_credit_rating[i],          \
            customerDemographicsBatch->cd_dep_count[i],              \
            customerDemographicsBatch->cd_dep_employed_count[i],     \
            customerDemographicsBatch->cd_dep_college_count[i]       \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_TABLE_BATCHES                 \
            batchCounter = 0;                   \
        }                                       \
    }

    #define ADD_TO_PROMOTION_BATCH {                  \
        tmpPromotionBatch.add(                        \
           promotionBatch->p_promo_sk[i],             \
           promotionBatch->p_promo_id[i],             \
           promotionBatch->p_start_date_sk[i],        \
           promotionBatch->p_end_date_sk[i],          \
           promotionBatch->p_item_sk[i],              \
           promotionBatch->p_cost[i],                 \
           promotionBatch->p_response_target[i],      \
           promotionBatch->p_promo_name[i],           \
           promotionBatch->p_channel_dmail[i],        \
           promotionBatch->p_channel_email[i],        \
           promotionBatch->p_channel_catalog[i],      \
           promotionBatch->p_channel_tv[i],           \
           promotionBatch->p_channel_radio[i],        \
           promotionBatch->p_channel_press[i],        \
           promotionBatch->p_channel_event[i],        \
           promotionBatch->p_channel_demo[i],         \
           promotionBatch->p_channel_details[i],      \
           promotionBatch->p_purpose[i],              \
           promotionBatch->p_discount_active[i]       \
        );                                      \
        if (++batchCounter == batchSize) {      \
            FLUSH_TABLE_BATCHES                 \
            batchCounter = 0;                   \
        }                                       \
    }

    #define INSERT_STORESALES_BATCH {             \
        data.on_batch_update_STORE_SALES(storeSalesBatchList[i]); }

    #define INSERT_ITEM_BATCH {                   \
        data.on_batch_update_ITEM(itemBatchList[i]); }

    #define INSERT_CUSTOMER_BATCH {               \
        data.on_batch_update_CUSTOMER(customerBatchList[i]); }

    #define INSERT_CUSTOMERADDRESS_BATCH {        \
        data.on_batch_update_CUSTOMER_ADDRESS(customerAddressBatchList[i]); }

    #define INSERT_STORE_BATCH {                  \
        data.on_batch_update_STORE(storeBatchList[i]); }

    #define INSERT_DATEDIM_BATCH {                                \
        TPCDSDateDimBatch* dateDimBatch = &(dateDimBatchList[i]); \
        for (size_t j = 0; j < dateDimBatch->size; j++)           \
            data.on_insert_DATE_DIM(                              \
                dateDimBatch->d_date_sk[j],                       \
                dateDimBatch->d_date_id[j],                       \
                dateDimBatch->d_date[j],                          \
                dateDimBatch->d_month_seq[j],                     \
                dateDimBatch->d_week_seq[j],                      \
                dateDimBatch->d_quarter_seq[j],                   \
                dateDimBatch->d_year[j],                          \
                dateDimBatch->d_dow[j],                           \
                dateDimBatch->d_moy[j],                           \
                dateDimBatch->d_dom[j],                           \
                dateDimBatch->d_qoy[j],                           \
                dateDimBatch->d_fy_year[j],                       \
                dateDimBatch->d_fy_quarter_seq[j],                \
                dateDimBatch->d_fy_week_seq[j],                   \
                dateDimBatch->d_day_name[j],                      \
                dateDimBatch->d_quarter_name[j],                  \
                dateDimBatch->d_holiday[j],                       \
                dateDimBatch->d_weekend[j],                       \
                dateDimBatch->d_following_holiday[j],             \
                dateDimBatch->d_first_dom[j],                     \
                dateDimBatch->d_last_dom[j],                      \
                dateDimBatch->d_same_day_ly[j],                   \
                dateDimBatch->d_same_day_lq[j],                   \
                dateDimBatch->d_current_day[j],                   \
                dateDimBatch->d_current_week[j],                  \
                dateDimBatch->d_current_month[j],                 \
                dateDimBatch->d_current_quarter[j],               \
                dateDimBatch->d_current_year[j]                   \
            );                                                    \
    }

    #define INSERT_HOUSEHOLDDEMOGRAPHICS_BATCH {                       \
        TPCDSHouseholdDemographicsBatch* householdDemographicsBatch = &(householdDemographicsBatchList[i]);   \
        for (size_t j = 0; j < householdDemographicsBatch->size; j++)  \
            data.on_insert_HOUSEHOLD_DEMOGRAPHICS(                     \
                householdDemographicsBatch->hd_demo_sk[j],             \
                householdDemographicsBatch->hd_income_band_sk[j],      \
                householdDemographicsBatch->hd_buy_potential[j],       \
                householdDemographicsBatch->hd_dep_count[j],           \
                householdDemographicsBatch->hd_vehicle_count[j]        \
            );                                                         \
    }

    #define INSERT_CUSTOMERDEMOGRAPHICS_BATCH {                        \
        TPCDSCustomerDemographicsBatch* customerDemographicsBatch = &(customerDemographicsBatchList[i]);   \
        for (size_t j = 0; j < customerDemographicsBatch->size; j++) \
            data.on_insert_CUSTOMER_DEMOGRAPHICS(                    \
                customerDemographicsBatch->cd_demo_sk[j],            \
                customerDemographicsBatch->cd_gender[j],             \
                customerDemographicsBatch->cd_marital_status[j],     \
                customerDemographicsBatch->cd_education_status[j],   \
                customerDemographicsBatch->cd_purchase_estimate[j],  \
                customerDemographicsBatch->cd_credit_rating[j],      \
                customerDemographicsBatch->cd_dep_count[j],          \
                customerDemographicsBatch->cd_dep_employed_count[j], \
                customerDemographicsBatch->cd_dep_college_count[j]   \
            );                                                       \
    }

    #define INSERT_PROMOTION_BATCH {                         \
        TPCDSPromotionBatch* promotionBatch = &(promotionBatchList[i]);   \
        for (size_t j = 0; j < promotionBatch->size; j++)    \
            data.on_insert_PROMOTION(                        \
                promotionBatch->p_promo_sk[j],               \
                promotionBatch->p_promo_id[j],               \
                promotionBatch->p_start_date_sk[j],          \
                promotionBatch->p_end_date_sk[j],            \
                promotionBatch->p_item_sk[j],                \
                promotionBatch->p_cost[j],                   \
                promotionBatch->p_response_target[j],        \
                promotionBatch->p_promo_name[j],             \
                promotionBatch->p_channel_dmail[j],          \
                promotionBatch->p_channel_email[j],          \
                promotionBatch->p_channel_catalog[j],        \
                promotionBatch->p_channel_tv[j],             \
                promotionBatch->p_channel_radio[j],          \
                promotionBatch->p_channel_press[j],          \
                promotionBatch->p_channel_event[j],          \
                promotionBatch->p_channel_demo[j],           \
                promotionBatch->p_channel_details[j],        \
                promotionBatch->p_purpose[j],                \
                promotionBatch->p_discount_active[j]         \
            );                                               \
    }

    void convert_tables_to_batches(size_t batchSize)
    { 
        size_t i = 0, count = 0, batchCounter = 0;

        IF_CUSTOMERDEMOGRAPHICS ( TPCDSCustomerDemographicsBatch tmpCustomerDemographicsBatch(batchSize); )
        IF_DATEDIM ( TPCDSDateDimBatch tmpDateDimBatch(batchSize); )
        IF_HOUSEHOLDDEMOGRAPHICS ( TPCDSHouseholdDemographicsBatch tmpHouseholdDemographicsBatch(batchSize); )
        IF_PROMOTION ( TPCDSPromotionBatch tmpPromotionBatch(batchSize); )

        IF_PROMOTION ({
            count = promotionBatch->size;

            for (; i < count; i++) 
            {
                IF_CUSTOMERDEMOGRAPHICS ( ADD_TO_CUSTOMERDEMOGRAPHICS_BATCH )
                IF_DATEDIM ( ADD_TO_DATEDIM_BATCH )
                IF_HOUSEHOLDDEMOGRAPHICS ( ADD_TO_HOUSEHOLDDEMOGRAPHICS_BATCH )
                IF_PROMOTION ( ADD_TO_PROMOTION_BATCH )
            }            
        })

        IF_HOUSEHOLDDEMOGRAPHICS ({
            count = householdDemographicsBatch->size;

            for (; i < count; i++) 
            {
                IF_CUSTOMERDEMOGRAPHICS ( ADD_TO_CUSTOMERDEMOGRAPHICS_BATCH )
                IF_DATEDIM ( ADD_TO_DATEDIM_BATCH )
                IF_HOUSEHOLDDEMOGRAPHICS ( ADD_TO_HOUSEHOLDDEMOGRAPHICS_BATCH )
            }                        
        })

        IF_DATEDIM ({
            count = dateDimBatch->size;

            for (; i < count; i++) 
            {
                IF_CUSTOMERDEMOGRAPHICS ( ADD_TO_CUSTOMERDEMOGRAPHICS_BATCH )
                IF_DATEDIM ( ADD_TO_DATEDIM_BATCH )
            }                        
        })

        IF_CUSTOMERDEMOGRAPHICS ({
            count = customerDemographicsBatch->size;

            for (; i < count; i++) 
            {
                IF_CUSTOMERDEMOGRAPHICS ( ADD_TO_CUSTOMERDEMOGRAPHICS_BATCH )
            }                        
        })

        FLUSH_TABLE_BATCHES
    }

    void convert_streams_to_batches(size_t batchSize)
    { 
        size_t i = 0, count = 0, batchCounter = 0;

        IF_STORESALES ( TPCDSStoreSalesBatch tmpStoreSalesBatch(batchSize); )
        IF_CUSTOMER ( TPCDSCustomerBatch tmpCustomerBatch(batchSize); )
        IF_CUSTOMERADDRESS ( TPCDSCustomerAddressBatch tmpCustomerAddressBatch(batchSize); )
        IF_ITEM ( TPCDSItemBatch tmpItemBatch(batchSize); )
        IF_STORE ( TPCDSStoreBatch tmpStoreBatch(batchSize); )    


        IF_STORE ({
            count = storeBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( ADD_TO_STORESALES_BATCH )
                IF_CUSTOMER ( ADD_TO_CUSTOMER_BATCH )
                IF_CUSTOMERADDRESS ( ADD_TO_CUSTOMERADDRESS_BATCH )
                IF_ITEM ( ADD_TO_ITEM_BATCH )
                IF_STORE ( ADD_TO_STORE_BATCH )
            }
        })

        IF_ITEM ({
            count = itemBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( ADD_TO_STORESALES_BATCH )
                IF_CUSTOMER ( ADD_TO_CUSTOMER_BATCH )
                IF_CUSTOMERADDRESS ( ADD_TO_CUSTOMERADDRESS_BATCH )
                IF_ITEM ( ADD_TO_ITEM_BATCH )
            }
        })

        IF_CUSTOMERADDRESS ({
            count = customerAddressBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( ADD_TO_STORESALES_BATCH )
                IF_CUSTOMER ( ADD_TO_CUSTOMER_BATCH )
                IF_CUSTOMERADDRESS ( ADD_TO_CUSTOMERADDRESS_BATCH )
            }
        })        

        IF_CUSTOMER ({
            count = customerBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( ADD_TO_STORESALES_BATCH )
                IF_CUSTOMER ( ADD_TO_CUSTOMER_BATCH )
            }
        })                

        IF_STORESALES ({
            count = storeSalesBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( ADD_TO_STORESALES_BATCH )
            }
        })                

        FLUSH_STREAM_BATCHES
    }

    void process_table_batches(dbtoaster::data_t& data) 
    {
        size_t i = 0, count = 0;

        IF_CUSTOMERDEMOGRAPHICS ({
            count = customerDemographicsBatchList.size();

            for (; i < count; i++) 
            {
                INSERT_CUSTOMERDEMOGRAPHICS_BATCH
            }                        
        })

        IF_DATEDIM ({
            count = dateDimBatchList.size();

            for (; i < count; i++) 
            {
                INSERT_DATEDIM_BATCH
            }                        
        })

        IF_HOUSEHOLDDEMOGRAPHICS ({
            count = householdDemographicsBatchList.size();

            for (; i < count; i++) 
            {
                INSERT_HOUSEHOLDDEMOGRAPHICS_BATCH
            }                        
        })

        IF_PROMOTION ({
            count = promotionBatchList.size();

            for (; i < count; i++) 
            {
                INSERT_PROMOTION_BATCH
            }            
        })
    }

    void process_stream_batches(dbtoaster::data_t& data) 
    {
        size_t i = 0, count = 0;

        IF_STORE ({
            count = storeBatchList.size();

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES_BATCH )
                IF_CUSTOMER ( INSERT_CUSTOMER_BATCH )
                IF_CUSTOMERADDRESS ( INSERT_CUSTOMERADDRESS_BATCH )
                IF_ITEM ( INSERT_ITEM_BATCH )
                IF_STORE ( INSERT_STORE_BATCH )
            }
        })

        IF_ITEM ({
            count = itemBatchList.size();

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES_BATCH )
                IF_CUSTOMER ( INSERT_CUSTOMER_BATCH )
                IF_CUSTOMERADDRESS ( INSERT_CUSTOMERADDRESS_BATCH )
                IF_ITEM ( INSERT_ITEM_BATCH )
            }
        })

        IF_CUSTOMERADDRESS ({
            count = customerAddressBatchList.size();

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES_BATCH )
                IF_CUSTOMER ( INSERT_CUSTOMER_BATCH )
                IF_CUSTOMERADDRESS ( INSERT_CUSTOMERADDRESS_BATCH )
            }
        })        

        IF_CUSTOMER ({
            count = customerBatchList.size();

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES_BATCH )
                IF_CUSTOMER ( INSERT_CUSTOMER_BATCH )
            }
        })                

        IF_STORESALES ({
            count = storeSalesBatchList.size();

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES_BATCH )
            }
        })
    }

#else

    #define INSERT_DATEDIM {                   \
        data.on_insert_DATE_DIM(                \
           dateDimBatch->d_date_sk[i],             \
           dateDimBatch->d_date_id[i],             \
           dateDimBatch->d_date[i],                \
           dateDimBatch->d_month_seq[i],           \
           dateDimBatch->d_week_seq[i],            \
           dateDimBatch->d_quarter_seq[i],         \
           dateDimBatch->d_year[i],                \
           dateDimBatch->d_dow[i],                 \
           dateDimBatch->d_moy[i],                 \
           dateDimBatch->d_dom[i],                 \
           dateDimBatch->d_qoy[i],                 \
           dateDimBatch->d_fy_year[i],             \
           dateDimBatch->d_fy_quarter_seq[i],      \
           dateDimBatch->d_fy_week_seq[i],         \
           dateDimBatch->d_day_name[i],            \
           dateDimBatch->d_quarter_name[i],        \
           dateDimBatch->d_holiday[i],             \
           dateDimBatch->d_weekend[i],             \
           dateDimBatch->d_following_holiday[i],   \
           dateDimBatch->d_first_dom[i],           \
           dateDimBatch->d_last_dom[i],            \
           dateDimBatch->d_same_day_ly[i],         \
           dateDimBatch->d_same_day_lq[i],         \
           dateDimBatch->d_current_day[i],         \
           dateDimBatch->d_current_week[i],        \
           dateDimBatch->d_current_month[i],       \
           dateDimBatch->d_current_quarter[i],     \
           dateDimBatch->d_current_year[i]); }

    #define INSERT_STORESALES {                 \
        data.on_insert_STORE_SALES(              \
            storeSalesBatch->ss_sold_date_sk[i],            \
            storeSalesBatch->ss_sold_time_sk[i],            \
            storeSalesBatch->ss_item_sk[i],                 \
            storeSalesBatch->ss_customer_sk[i],             \
            storeSalesBatch->ss_cdemo_sk[i],                \
            storeSalesBatch->ss_hdemo_sk[i],                \
            storeSalesBatch->ss_addr_sk[i],                 \
            storeSalesBatch->ss_store_sk[i],                \
            storeSalesBatch->ss_promo_sk[i],                \
            storeSalesBatch->ss_ticket_number[i],           \
            storeSalesBatch->ss_quantity[i],                \
            storeSalesBatch->ss_wholesale_cost[i],          \
            storeSalesBatch->ss_list_price[i],              \
            storeSalesBatch->ss_sales_price[i],             \
            storeSalesBatch->ss_ext_discount_amt[i],        \
            storeSalesBatch->ss_ext_sales_price[i],         \
            storeSalesBatch->ss_ext_wholesale_cost[i],      \
            storeSalesBatch->ss_ext_list_price[i],          \
            storeSalesBatch->ss_ext_tax[i],                 \
            storeSalesBatch->ss_coupon_amt[i],              \
            storeSalesBatch->ss_net_paid[i],                \
            storeSalesBatch->ss_net_paid_inc_tax[i],        \
            storeSalesBatch->ss_net_profit[i]); }

    #define INSERT_ITEM {                   \
         data.on_insert_ITEM(               \
            itemBatch->i_item_sk[i],            \
            itemBatch->i_item_id[i],            \
            itemBatch->i_rec_start_date[i],     \
            itemBatch->i_rec_end_date[i],       \
            itemBatch->i_item_desc[i],          \
            itemBatch->i_current_price[i],      \
            itemBatch->i_wholesale_cost[i],     \
            itemBatch->i_brand_id[i],           \
            itemBatch->i_brand[i],              \
            itemBatch->i_class_id[i],           \
            itemBatch->i_class[i],              \
            itemBatch->i_category_id[i],        \
            itemBatch->i_category[i],           \
            itemBatch->i_manufact_id[i],        \
            itemBatch->i_manufact[i],           \
            itemBatch->i_size[i],               \
            itemBatch->i_formulation[i],        \
            itemBatch->i_color[i],              \
            itemBatch->i_units[i],              \
            itemBatch->i_container[i],          \
            itemBatch->i_manager_id[i],         \
            itemBatch->i_product_name[i]); }

    #define INSERT_CUSTOMER {               \
        data.on_insert_CUSTOMER(            \
           customerBatch->c_customer_sk[i],             \
           customerBatch->c_customer_id[i],             \
           customerBatch->c_current_cdemo_sk[i],        \
           customerBatch->c_current_hdemo_sk[i],        \
           customerBatch->c_current_addr_sk[i],         \
           customerBatch->c_first_shipto_date_sk[i],    \
           customerBatch->c_first_sales_date_sk[i],     \
           customerBatch->c_salutation[i],              \
           customerBatch->c_first_name[i],              \
           customerBatch->c_last_name[i],               \
           customerBatch->c_preferred_cust_flag[i],     \
           customerBatch->c_birth_day[i],               \
           customerBatch->c_birth_month[i],             \
           customerBatch->c_birth_year[i],              \
           customerBatch->c_birth_country[i],           \
           customerBatch->c_login[i],                   \
           customerBatch->c_email_address[i],           \
           customerBatch->c_last_review_date[i]); }

    #define INSERT_CUSTOMERADDRESS {                \
        data.on_insert_CUSTOMER_ADDRESS(            \
            customerAddressBatch->ca_address_sk[i],         \
            customerAddressBatch->ca_address_id[i],         \
            customerAddressBatch->ca_street_number[i],      \
            customerAddressBatch->ca_street_name[i],        \
            customerAddressBatch->ca_street_type[i],        \
            customerAddressBatch->ca_suite_number[i],       \
            customerAddressBatch->ca_city[i],               \
            customerAddressBatch->ca_county[i],             \
            customerAddressBatch->ca_state[i],              \
            customerAddressBatch->ca_zip[i],                \
            customerAddressBatch->ca_country[i],            \
            customerAddressBatch->ca_gmt_offset[i],         \
            customerAddressBatch->ca_location_type[i]); }

    #define INSERT_STORE {               \
        data.on_insert_STORE(            \
            storeBatch->s_store_sk[i],              \
            storeBatch->s_store_id[i],              \
            storeBatch->s_rec_start_date[i],        \
            storeBatch->s_rec_end_date[i],          \
            storeBatch->s_closed_date_sk[i],        \
            storeBatch->s_store_name[i],            \
            storeBatch->s_number_employees[i],      \
            storeBatch->s_floor_space[i],           \
            storeBatch->s_hours[i],                 \
            storeBatch->s_manager[i],               \
            storeBatch->s_market_id[i],             \
            storeBatch->s_geography_class[i],       \
            storeBatch->s_market_desc[i],           \
            storeBatch->s_market_manager[i],        \
            storeBatch->s_division_id[i],           \
            storeBatch->s_division_name[i],         \
            storeBatch->s_company_id[i],            \
            storeBatch->s_company_name[i],          \
            storeBatch->s_street_number[i],         \
            storeBatch->s_street_name[i],           \
            storeBatch->s_street_type[i],           \
            storeBatch->s_suite_number[i],          \
            storeBatch->s_city[i],                  \
            storeBatch->s_county[i],                \
            storeBatch->s_state[i],                 \
            storeBatch->s_zip[i],                   \
            storeBatch->s_country[i],               \
            storeBatch->s_gmt_offset[i],            \
            storeBatch->s_tax_precentage[i]); }

    #define INSERT_HOUSEHOLDDEMOGRAPHICS {                         \
        data.on_insert_HOUSEHOLD_DEMOGRAPHICS(                     \
            householdDemographicsBatch->hd_demo_sk[i],             \
            householdDemographicsBatch->hd_income_band_sk[i],      \
            householdDemographicsBatch->hd_buy_potential[i],       \
            householdDemographicsBatch->hd_dep_count[i],           \
            householdDemographicsBatch->hd_vehicle_count[i]); }

    #define INSERT_CUSTOMERDEMOGRAPHICS {                 \
        data.on_insert_CUSTOMER_DEMOGRAPHICS(              \
            customerDemographicsBatch->cd_demo_sk[i],                \
            customerDemographicsBatch->cd_gender[i],                 \
            customerDemographicsBatch->cd_marital_status[i],         \
            customerDemographicsBatch->cd_education_status[i],       \
            customerDemographicsBatch->cd_purchase_estimate[i],      \
            customerDemographicsBatch->cd_credit_rating[i],          \
            customerDemographicsBatch->cd_dep_count[i],              \
            customerDemographicsBatch->cd_dep_employed_count[i],     \
            customerDemographicsBatch->cd_dep_college_count[i]); }

    #define INSERT_PROMOTION {                 \
        data.on_insert_PROMOTION(              \
            promotionBatch->p_promo_sk[i],              \
            promotionBatch->p_promo_id[i],              \
            promotionBatch->p_start_date_sk[i],         \
            promotionBatch->p_end_date_sk[i],           \
            promotionBatch->p_item_sk[i],               \
            promotionBatch->p_cost[i],                  \
            promotionBatch->p_response_target[i],       \
            promotionBatch->p_promo_name[i],            \
            promotionBatch->p_channel_dmail[i],         \
            promotionBatch->p_channel_email[i],         \
            promotionBatch->p_channel_catalog[i],       \
            promotionBatch->p_channel_tv[i],            \
            promotionBatch->p_channel_radio[i],         \
            promotionBatch->p_channel_press[i],         \
            promotionBatch->p_channel_event[i],         \
            promotionBatch->p_channel_demo[i],          \
            promotionBatch->p_channel_details[i],       \
            promotionBatch->p_purpose[i],               \
            promotionBatch->p_discount_active[i]); }

    void process_tables(dbtoaster::data_t& data) 
    {        
        size_t i = 0, count = 0;

        IF_CUSTOMERDEMOGRAPHICS ({
            count = customerDemographicsBatch->size;

            for (i = 0; i < count; i++) 
            {
                INSERT_CUSTOMERDEMOGRAPHICS
            }                        
        })        

        IF_DATEDIM ({
            count = dateDimBatch->size;

            for (i = 0; i < count; i++) 
            {
                INSERT_DATEDIM
            }                        
        })

        IF_HOUSEHOLDDEMOGRAPHICS ({
            count = householdDemographicsBatch->size;

            for (i = 0; i < count; i++) 
            {
                INSERT_HOUSEHOLDDEMOGRAPHICS
            }                        
        })

        IF_PROMOTION ({
            count = promotionBatch->size;

            for (; i < count; i++) 
            {
                INSERT_PROMOTION
            }
        })
    }

    void process_streams(dbtoaster::data_t& data)
    { 
        size_t i = 0, count = 0;

        IF_STORE ({
            count = storeBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES )
                IF_CUSTOMER ( INSERT_CUSTOMER )
                IF_CUSTOMERADDRESS ( INSERT_CUSTOMERADDRESS )
                IF_ITEM ( INSERT_ITEM )
                IF_STORE ( INSERT_STORE )
            }
        })

        IF_ITEM ({
            count = itemBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES )
                IF_CUSTOMER ( INSERT_CUSTOMER )
                IF_CUSTOMERADDRESS ( INSERT_CUSTOMERADDRESS )
                IF_ITEM ( INSERT_ITEM )
            }
        })

        IF_CUSTOMERADDRESS ({
            count = customerAddressBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES )
                IF_CUSTOMER ( INSERT_CUSTOMER )
                IF_CUSTOMERADDRESS ( INSERT_CUSTOMERADDRESS )
            }
        })        

        IF_CUSTOMER ({
            count = customerBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES )
                IF_CUSTOMER ( INSERT_CUSTOMER )
            }
        })                

        IF_STORESALES ({
            count = storeSalesBatch->size;

            for (; i < count; i++) 
            {
                IF_STORESALES ( INSERT_STORESALES )
            }
        })
    }
#endif
}

#endif /* DBTOASTER_TEST_TEMPLATE_HPP */
