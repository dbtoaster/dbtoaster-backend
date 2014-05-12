#include "runtime.hpp"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/find_iterator.hpp>

/******************************************************************************
	runtime_options
******************************************************************************/
namespace dbtoaster {
namespace runtime {

bool runtime_options::_verbose = false;

runtime_options::runtime_options(int argc, char* argv[]) :
  traced(false)
  , trace_step(0)
  , log_tuple_count_every(0)
  , async(false)
{
	init(argc, argv);
}

void runtime_options::init_options(options_description& desc) {
	desc.add_options()
	  ("help", "list available options")
	  ("v", "verbose")
	  ("async", "asynchronous execution mode")
	  ("log-dir", value<string>(), "logging directory")
	  ("log-triggers,l",
		value<vector<string> >(&logged_streams_v), "log stream triggers")
	  ("unified,u", value<string>(), "unified logging [stream | global]")
	  ("output-file,o", value<string>(), "output file")
	  ("maps,m", value<vector<string> >(&output_maps), "output maps")

	  // Statistics profiling parameters
	  ("samplesize", value<unsigned int>(),
		   "sample window size for trigger profiles")

	  ("sampleperiod", value<unsigned int>(),
		   "period length, as number of trigger events")

	  ("statsfile", value<string>(),
		   "output file for trigger profile statistics")

	  // Tracing parameters
	  ("trace-dir", value<string>(), "trace output dir")
	  ("trace,t", value<string>(&trace_opts), "trace query execution")
	  ("trace-step,s", value(&trace_step), "trace step size")
	  ("log-count", value<unsigned int>(&log_tuple_count_every), 
	   "log tuple count every [arg] updates");
}

void runtime_options::init_positional_options(positional_options_description& p) {
	p.add("maps", -1);
}

void runtime_options::process_options(
			int argc, char* argv[],
			options_description& o,
			positional_options_description& p,
			variables_map& m)
{
	try {
		store(command_line_parser(argc,argv).
		  options(o).positional(p).run(), m);
		notify(m);
	} catch (unknown_option& o) {
	  cerr << "unknown option: \"" 
		   << o.what() << "\"" << endl;
	  cerr << *opt_desc << endl;
	  exit(1);
	} catch (error& e) {
	  cerr << "error parsing command line options" << endl;
	  cerr << *opt_desc << endl;
	  exit(1);
	}
}

void runtime_options::setup_tracing(options_description& o) {
	try {
	  trace_counter = 0;
	  if ( trace_step <= 0 )
		  trace_step = 1000;
	  if ( trace_opts != "" )
	  {
		  if( runtime_options::verbose() )
			  cerr << "tracing: " << trace_opts << endl;
		  parse_tracing(trace_opts);
	  }
	  else traced = false;
	} catch (unknown_option& uo) {
		cerr << "unknown option: \"" 
			 << uo.what() << "\"" << endl;
		cerr << o << endl;
		exit(1);
	} catch (error& e) {
		cerr << "error parsing command line options" << endl;
		cerr << o << endl;
		exit(1);
	}
}

void runtime_options::init(int argc, char* argv[]) {
	if (argc <= 0 ) return;

	opt_desc = boost::shared_ptr<options_description>(
		new options_description("dbtoaster query options"));

	init_options(*opt_desc);
	init_positional_options(pos_options);
	process_options(argc, argv, *opt_desc, pos_options, opt_map);
	_verbose = opt_map.count("v");
	async = opt_map.count("async");
	setup_tracing(*opt_desc);
	logged_streams = set<string>(logged_streams_v.begin(),
								 logged_streams_v.end());
	logged_streams_v.clear();
}

bool runtime_options::help() {
	if ( opt_map.count("help") ) cerr << *opt_desc << endl;
	return opt_map.count("help");
}

// Result output.
string runtime_options::get_output_file() {
	if(opt_map.count("output-file")) {
	  return opt_map["output-file"].as<string>();
	} else {
	  return string("-");
	}
}

bool runtime_options::is_output_map(string map_name) {
	return find(output_maps.begin(), output_maps.end(), map_name)
			!= output_maps.end();
}

void runtime_options::add_output_map(string map_name){
	output_maps.push_back(map_name);
}

// Trigger logging.
bool runtime_options::global() {
	return opt_map.count("unified")
			 && opt_map["unified"].as<string>() == "global";
}

bool runtime_options::unified() {
	return opt_map.count("unified")
			 && opt_map["unified"].as<string>() == "stream";
}

path runtime_options::get_log_file(string stream_name, event_type t) {
	return get_log_file(stream_name, event_name[t], true);
}

path runtime_options::get_log_file(string stream_name) {
	return get_log_file(stream_name, "Events", false);
}

path runtime_options::get_log_file(string stream_name, string ftype, bool prefix) {
	path r;
	if ( opt_map.count("log-dir") ) r = opt_map["log-dir"].as<string>();
	else r = current_path();
	r /= (prefix? ftype : "") + stream_name + 
		 (prefix? "" : ftype) + ".dbtdat";
	return r.make_preferred();
}

// Statistics
// Number of samples to collect per statitics period.
unsigned int runtime_options::get_stats_window_size() {
	unsigned int r = 10000;
	if ( opt_map.count("samplesize") ) {
	  r = opt_map["samplesize"].as<unsigned int>();
	}
	return r;
}

// Period size, in terms of the number of trigger invocations.
unsigned int runtime_options::get_stats_period() {
	unsigned int r = 10000;
	if ( opt_map.count("sampleperiod") ) {
	  r = opt_map["sampleperiod"].as<unsigned int>();
	}
	return r;
}

string runtime_options::get_stats_file() {
	string r = "stats";
	if ( opt_map.count("statsfile") ) {
	  r = opt_map["statsfile"].as<string>();
	}
	return r;
}

// Tracing.
void runtime_options::parse_tracing(const string& opts) {
	split_iterator<string::const_iterator> it =
	   make_split_iterator(opts, first_finder(",", is_equal()));

	split_iterator<string::const_iterator> end;

	for (; it != end; ++it) {
	  string param = copy_range<std::string>(*it);
	  cerr << "tracing map " << param << endl;
	  traced_maps.insert(param);
	}
	traced = true;
}

bool runtime_options::is_traced_map(string map_name) {
	return traced_maps.empty()
			|| (traced_maps.find(map_name) != traced_maps.end());
}

bool runtime_options::is_traced() {
	++trace_counter;
	return traced && (trace_counter % trace_step) == 0;
}

path runtime_options::get_trace_file() {
	path p = "traces";
	if ( opt_map.count("trace-dir") ) {
	  p = opt_map["trace-dir"].as<string>();
	}
	p /= "trace"+boost::lexical_cast<std::string>(trace_counter)+".txt";
	cerr << "trace file " << p << endl;
	return p.make_preferred();
}


/******************************************************************************
	orderbook_options
******************************************************************************/	
	
void orderbook_options::init(int argc, char* argv[]) {
	runtime_options::init_options(*opt_desc);

	// Additional
	opt_desc->add_options()
	  ("input-file,i", value<string>(), "order book input data file")
	  ("orderbook-params", value<vector<string> >(&orderbook_params),
		  "order book adaptor parameters");

	// No positional parameters.
	runtime_options::process_options(argc, argv, *opt_desc, 
									 pos_options, opt_map);
	runtime_options::setup_tracing(*opt_desc);
}

string orderbook_options::order_book_file() {
	string r;
	if ( opt_map.count("input-file") ) {
	  r = opt_map["input-file"].as<string>();
	}
	return r;
}

string orderbook_options::order_book_params() {
	string r;
	vector<string>::iterator it = orderbook_params.begin();
	for (; it != orderbook_params.end(); ++it)
	  r += (r.empty()? "" : ",") + *it;
	return r;
}

}
}
