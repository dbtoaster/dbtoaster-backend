#include "runtime.hpp"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <algorithm>

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
	  ("log-dir", value<std::string>(), "logging directory")
	  ("log-triggers,l",
		value<std::vector<std::string> >(&logged_streams_v), "log stream triggers")
	  ("unified,u", value<std::string>(), "unified logging [stream | global]")
	  ("output-file,o", value<std::string>(), "output file")
	  ("maps,m", value<std::vector<std::string> >(&output_maps), "output maps")

	  // Statistics profiling parameters
	  ("samplesize", value<unsigned int>(),
		   "sample window size for trigger profiles")

	  ("sampleperiod", value<unsigned int>(),
		   "period length, as number of trigger events")

	  ("statsfile", value<std::string>(),
		   "output file for trigger profile statistics")

	  // Tracing parameters
	  ("trace-dir", value<std::string>(), "trace output dir")
	  ("trace,t", value<std::string>(&trace_opts), "trace query execution")
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
	  std::cerr << "unknown option: \"" 
		   << o.what() << "\"" << std::endl;
	  std::cerr << *opt_desc << std::endl;
	  exit(1);
	} catch (error& e) {
	  std::cerr << "error parsing command line options" << std::endl;
	  std::cerr << *opt_desc << std::endl;
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
			  std::cerr << "tracing: " << trace_opts << std::endl;
		  parse_tracing(trace_opts);
	  }
	  else traced = false;
	} catch (unknown_option& uo) {
		std::cerr << "unknown option: \"" 
			 << uo.what() << "\"" << std::endl;
		std::cerr << o << std::endl;
		exit(1);
	} catch (error& e) {
		std::cerr << "error parsing command line options" << std::endl;
		std::cerr << o << std::endl;
		exit(1);
	}
}

void runtime_options::init(int argc, char* argv[]) {
	if (argc <= 0 ) return;

	opt_desc = std::shared_ptr<options_description>(
		new options_description("dbtoaster query options"));

	init_options(*opt_desc);
	init_positional_options(pos_options);
	process_options(argc, argv, *opt_desc, pos_options, opt_map);
	_verbose = opt_map.count("v");
	async = opt_map.count("async");
	setup_tracing(*opt_desc);
	logged_streams = std::set<std::string>(logged_streams_v.begin(),
								 logged_streams_v.end());
	logged_streams_v.clear();
}

bool runtime_options::help() {
	if ( opt_map.count("help") ) std::cerr << *opt_desc << std::endl;
	return opt_map.count("help");
}

// Result output.
std::string runtime_options::get_output_file() {
	if(opt_map.count("output-file")) {
	  return opt_map["output-file"].as<std::string>();
	} else {
	  return std::string("-");
	}
}

bool runtime_options::is_output_map(std::string map_name) {
	return find(output_maps.begin(), output_maps.end(), map_name)
			!= output_maps.end();
}

void runtime_options::add_output_map(std::string map_name){
	output_maps.push_back(map_name);
}

// Trigger logging.
bool runtime_options::global() {
	return opt_map.count("unified")
			 && opt_map["unified"].as<std::string>() == "global";
}

bool runtime_options::unified() {
	return opt_map.count("unified")
			 && opt_map["unified"].as<std::string>() == "stream";
}

path runtime_options::get_log_file(std::string stream_name, event_type t) {
	return get_log_file(stream_name, event_name[t], true);
}

path runtime_options::get_log_file(std::string stream_name) {
	return get_log_file(stream_name, "Events", false);
}

path runtime_options::get_log_file(std::string stream_name, std::string ftype, bool prefix) {
	path r;
	if ( opt_map.count("log-dir") ) r = opt_map["log-dir"].as<std::string>();
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

std::string runtime_options::get_stats_file() {
	std::string r = "stats";
	if ( opt_map.count("statsfile") ) {
	  r = opt_map["statsfile"].as<std::string>();
	}
	return r;
}

// Tracing.
void runtime_options::parse_tracing(const std::string& opts) {
	typedef std::string::const_iterator iter;
    iter beg = opts.begin();
    iter end = opts.end();
    while(beg != end) {
        iter temp = std::find(beg, end, ',');
        if(beg != end) {
            std::string param(beg, temp);
            std::cerr << "tracing map " << param << std::endl;
            traced_maps.insert(param);
        }
        beg = temp;
        while ((beg != end) && (*beg == ','))
            beg++;
    }
	traced = true;
}

bool runtime_options::is_traced_map(std::string map_name) {
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
	  p = opt_map["trace-dir"].as<std::string>();
	}
	p /= "trace"+std::to_string(trace_counter)+".txt";
	std::cerr << "trace file " << p << std::endl;
	return p.make_preferred();
}


/******************************************************************************
	orderbook_options
******************************************************************************/	
	
void orderbook_options::init(int argc, char* argv[]) {
	runtime_options::init_options(*opt_desc);

	// Additional
	opt_desc->add_options()
	  ("input-file,i", value<std::string>(), "order book input data file")
	  ("orderbook-params", value<std::vector<std::string> >(&orderbook_params),
		  "order book adaptor parameters");

	// No positional parameters.
	runtime_options::process_options(argc, argv, *opt_desc, 
									 pos_options, opt_map);
	runtime_options::setup_tracing(*opt_desc);
}

std::string orderbook_options::order_book_file() {
	std::string r;
	if ( opt_map.count("input-file") ) {
	  r = opt_map["input-file"].as<std::string>();
	}
	return r;
}

std::string orderbook_options::order_book_params() {
	std::string r;
	std::vector<std::string>::iterator it = orderbook_params.begin();
	for (; it != orderbook_params.end(); ++it)
	  r += (r.empty()? "" : ",") + *it;
	return r;
}

}
}
