#ifndef DBTOASTER_STDADAPTORS_H
#define DBTOASTER_STDADAPTORS_H

#include <string>
#include <list>
#include <map>

#include <boost/shared_ptr.hpp>
#include "boost/tuple/tuple.hpp"

#include "streams.hpp"

namespace dbtoaster {
  namespace adaptors {

    using namespace std;
    using namespace boost;
    using namespace dbtoaster;
    using namespace dbtoaster::streams;

    struct csv_adaptor : public stream_adaptor
    {
      relation_id_t id;
      event_type type;
      string schema;
      string delimiter;
      
      boost::shared_ptr<event_t> saved_event;

      csv_adaptor(relation_id_t _id);
      csv_adaptor(relation_id_t _id, string sch);
      csv_adaptor(relation_id_t i, int num_params,
                  const pair<string,string> params[]);

      void parse_params(int num_params, const pair<string, string> params[]);
      virtual string parse_schema(string s);
      void validate_schema();

      // Interpret the schema.
      tuple<bool, bool, event_args_t> interpret_event(const string& schema,
                                                      const string& data);
      void process(const string& data, boost::shared_ptr<list<event_t> > dest);

      void finalize(boost::shared_ptr<list<event_t> > dest);      
      bool has_buffered_events();      
      void get_buffered_events(boost::shared_ptr<list<event_t> > dest);
      
    };

    // Replay adaptors are CSV adaptors prepended with an integer denoting the
    // event type. The adaptor internally adjusts the schema, allowing it to
    // be used with the same parameters as a standard CSV adaptor.
    struct replay_adaptor : public csv_adaptor {
		replay_adaptor(relation_id_t i);
		replay_adaptor(relation_id_t i, string sch);
		replay_adaptor(relation_id_t i, int num_params,
					 const pair<string,string> params[]);

		string parse_schema(string s);
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
          string action;
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

      typedef map<int, order_book_tuple> order_book;

      struct order_book_adaptor : public stream_adaptor {
        relation_id_t id;
        int num_brokers;
        order_book_type type;
        boost::shared_ptr<order_book> bids;
        boost::shared_ptr<order_book> asks;
        bool deterministic;
        bool insert_only;


        order_book_adaptor(relation_id_t sid, int nb, order_book_type t);
        order_book_adaptor(relation_id_t sid, int num_params,
                           pair<string, string> params[]);
						   
        bool parse_error(const string& data, int field);

        // Expected message format: t, id, action, volume, price
        bool parse_message(const string& data, order_book_message& r);
        void process_message(const order_book_message& msg,
                             boost::shared_ptr<list<event_t> > dest);
        void process(const string& data, boost::shared_ptr<list<event_t> > dest);

        void finalize(boost::shared_ptr<list<event_t> > dest) {}        
        bool has_buffered_events() { return false; }        
        void get_buffered_events(boost::shared_ptr<list<event_t> > dest) {}         
      };

      // Command line initialization of orderbook datasets.
      struct order_book_streams {
        // stream name, adaptor params
        typedef pair<string, vector<pair<string, string> > > stream_params;
        stream_registry r;
        map<string, int> stream_identifiers;
        int sid;
        string data_file;

        order_book_streams(string file_name, string params,
                           boost::shared_ptr<source_multiplexer> m);

        vector<stream_params> parse_params(string params);
        void init(vector<stream_params> params);

        int get_stream_id(string name);

        int get_bids_stream_id() { return get_stream_id("bids"); }
        int get_asks_stream_id() { return get_stream_id("asks"); }
		
		map<string, int>& get_stream_identifiers() { 
          return stream_identifiers;
        }
        
      };
    }
  }
}

#endif
