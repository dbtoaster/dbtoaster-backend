#ifndef DBTOASTER_STDADAPTORS_H
#define DBTOASTER_STDADAPTORS_H

#include <string>
#include <list>
#include <map>

#include <tuple>

#include "streams.hpp"

namespace dbtoaster {
  namespace adaptors {
    using namespace dbtoaster;
    using namespace dbtoaster::streams;

    struct csv_adaptor : public stream_adaptor
    {
      relation_id_t id;
      event_type type;
      char* schema;
      size_t schema_size;
      std::string delimiter;
      
      std::shared_ptr<event_t> saved_event;

      csv_adaptor(relation_id_t _id);
      csv_adaptor(relation_id_t _id, std::string sch);
      csv_adaptor(relation_id_t i, int num_params,
                  const std::pair<std::string,std::string> params[]);


      void read_adaptor_events(char* data, std::shared_ptr<std::list<event_t> > eventList, std::shared_ptr<std::list<event_t> > eventQue);
      void parse_params(int num_params, const std::pair<std::string, std::string> params[]);
      virtual std::string parse_schema(std::string s);
      void validate_schema();

      // Interpret the schema.
      std::tuple<bool, bool, unsigned int, event_args_t> interpret_event(const char* schema,
                                                       char* data);
    };
  }

  namespace datasets {

    //////////////////////////////
    //
    // Order books

    namespace order_books
    {
      using namespace dbtoaster::adaptors;

      enum order_book_type { tbids, tasks, both };

      // Struct to represent messages coming off a socket/historical file
      struct order_book_message {
          double t;
          long id;
          std::string action;
          double volume;
          double price;
      };

      // Struct for internal storage, i.e. a message without the action or
      // order id.
      struct order_book_tuple {
          double t;
          long id;
          long broker_id;
          double volume;
          double price;
          order_book_tuple() {}

          order_book_tuple(const order_book_message& msg);
          order_book_tuple& operator=(order_book_tuple& other);
          void operator()(event_args_t& e);
      };

      typedef std::map<int, order_book_tuple> order_book;

      struct order_book_adaptor : public stream_adaptor {
        relation_id_t bids_rel_id;
        relation_id_t asks_rel_id;
        int num_brokers;
        order_book_type type;
        std::shared_ptr<order_book> bids;
        std::shared_ptr<order_book> asks;
        bool deterministic;
        bool insert_only;


        order_book_adaptor(relation_id_t bids_rel_sid, relation_id_t asks_rel_sid, int nb, order_book_type t);
        order_book_adaptor(relation_id_t bids_rel_sid, relation_id_t asks_rel_sid, int num_params,
                           std::pair<std::string, std::string> params[]);

        void read_adaptor_events(char* data, std::shared_ptr<std::list<event_t> > eventList, std::shared_ptr<std::list<event_t> > eventQue);						   
        bool parse_error(const char* data, int field);

        // Expected message format: t, id, action, volume, price
        bool parse_message(char* data, order_book_message& r);
        void process_message(const order_book_message& msg,
                             std::shared_ptr<std::list<event_t> > dest);
      };
    }
  }
}

#endif
