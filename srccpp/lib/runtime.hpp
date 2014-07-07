#ifndef DBTOASTER_RUNTIME_H
#define DBTOASTER_RUNTIME_H

#include <iostream>

#include <string>
#include <vector>

#include <boost/unordered_set.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/positional_options.hpp>

#include "event.hpp"
#include "hpds/pstring.hpp"

#ifndef STRING_TYPE
#define STRING_TYPE std::string
#endif //STRING_TYPE

#ifndef STRING_TYPE_STR
#define STRING(s) #s
#define STRING_TYPE_STR STRING(STRING_TYPE)
#endif //STRING_TYPE_STR

namespace dbtoaster {
  namespace runtime {

    // using namespace std;
    using namespace boost;
    using namespace boost::filesystem;
    using namespace boost::program_options;
    
    struct runtime_options {
      std::shared_ptr<options_description> opt_desc;
      variables_map opt_map;
      positional_options_description pos_options;

      std::vector<std::string> output_maps;
      std::vector<std::string> logged_streams_v;
      std::set<std::string> logged_streams;

      // Tracing
      std::string trace_opts;
      bool traced;
      int trace_counter, trace_step;
      unordered_set<std::string> traced_maps;
      unsigned int log_tuple_count_every;

      // Verbose
      static bool _verbose;
	  static bool verbose(){ return _verbose; }

      // Execution mode
      bool async;

      runtime_options(int argc = 0, char* argv[] = 0);

      void init_options(options_description& desc);
      void init_positional_options(positional_options_description& p);
	  
      void process_options(int argc, char* argv[],
                           options_description& o,
                           positional_options_description& p,
                           variables_map& m);
      void setup_tracing(options_description& o);

      void init(int argc, char* argv[]);
      bool help();

      // Result output.
      std::string get_output_file();
      bool is_output_map(std::string map_name);
      void add_output_map(std::string map_name);

      // Trigger logging.
      bool global();
      bool unified();

      path get_log_file(std::string stream_name, event_type t);
      path get_log_file(std::string stream_name);
      path get_log_file(std::string stream_name, std::string ftype, bool prefix);

      // Statistics
      // Number of samples to collect per statitics period.
      unsigned int get_stats_window_size();

      // Period size, in terms of the number of trigger invocations.
      unsigned int get_stats_period();
      std::string get_stats_file();

      // Tracing.
      void parse_tracing(const std::string& opts);
      bool is_traced_map(std::string map_name);
      bool is_traced();
      path get_trace_file();
    };

    struct orderbook_options : public runtime_options {
      std::vector<std::string> orderbook_params;
      orderbook_options() {}
      orderbook_options(int argc, char* argv[]) { init(argc, argv); }

      void init(int argc, char* argv[]);
      std::string order_book_file();
      std::string order_book_params();
    };
  }
}

#endif
