#include "runtime.hpp"

#include <stdio.h>
#include <stdlib.h>
#include "filepath.hpp"
#include <algorithm>
#include <string>
#include <sstream>

/******************************************************************************
	runtime_options
******************************************************************************/

namespace patch {
    template < typename T > std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

namespace dbtoaster {
namespace runtime {

bool runtime_options::_verbose = false;

runtime_options::runtime_options(int argc, char* argv[]) :
  sample_size(0)
  , sample_period(0)
  , traced(false)
  , trace_counter(0)
  , trace_step(0)
  , log_tuple_count_every(0)
  , async(false)
{
	init(argc, argv);
}

void runtime_options::process_options(int argc, char* argv[])
{
	argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
	option::Stats stats(usage, argc, argv);

#ifdef __GNUC__
	// GCC supports C99 VLAs for C++ with proper constructor calls.
	option::Option options[stats.options_max], buffer[stats.buffer_max];
#else
	// use calloc() to allocate 0-initialized memory. It's not the same
	// as properly constructed elements, but good enough. Obviously in an
	// ordinary C++ program you'd use new[], but this file demonstrates that
	// TLMC++OP can be used without any dependency on the C++ standard library.
	option::Option* options = (option::Option*)calloc(stats.options_max, sizeof(option::Option));
	option::Option* buffer  = (option::Option*)calloc(stats.buffer_max,  sizeof(option::Option));
#endif

	option::Parser parse(usage, argc, argv, options, buffer);

	if (parse.error()) exit(1);

	if (options[HELP])
	{
		int columns = getenv("COLUMNS")? atoi(getenv("COLUMNS")) : 80;
		option::printUsage(fwrite, stdout, usage, columns);
		exit(0);
	}

	for (int i = 0; i < parse.optionsCount(); ++i)
	{
		option::Option& opt = buffer[i];
		switch (opt.index())
		{
			case HELP: // not possible, because handled further above and exits the program
				break;
			case VERBOSE:
				_verbose = true;
				break;
			case ASYNC:
				async = true;
				break;
			case LOGDIR:
				log_dir = std::string(opt.arg);
				break;
			case LOGTRIG:
				logged_streams_v.push_back(std::string(opt.arg));
				break;
			case UNIFIED:
				_unified = std::string(opt.arg);
				break;
			case OUTFILE:
				out_file = std::string(opt.arg);
				break;
			case SAMPLESZ:
				sample_size = std::atoi(opt.arg);
				break;
			case SAMPLEPRD:
				sample_period = std::atoi(opt.arg);
				break;
			case STATSFILE:
				stats_file = std::string(opt.arg);
				break;
			case TRACE:
				trace_opts = std::string(opt.arg);
				break;
			case TRACEDIR:
				trace_dir = std::string(opt.arg);
				break;
			case TRACESTEP:
				trace_step = std::atoi(opt.arg);
				break;
			case LOGCOUNT:
				log_tuple_count_every = std::atoi(opt.arg);
				break;
			case UNKNOWN:
				// not possible because Arg::Unknown returns ARG_ILLEGAL
				// which aborts the parse with an error
				break;
		}
	}

	for (int i = 0; i < parse.nonOptionsCount(); ++i)
		fprintf(stdout, "Unknown option: %s\n", parse.nonOption(i));
	if(parse.nonOptionsCount() != 0) exit(1);
}

void runtime_options::setup_tracing() {
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
}

void runtime_options::init(int argc, char* argv[]) {
	if (argc <= 0 ) return;

	process_options(argc, argv);
	setup_tracing();
	logged_streams = std::set<std::string>(logged_streams_v.begin(),
								 logged_streams_v.end());
	logged_streams_v.clear();
}

// Result output.
std::string runtime_options::get_output_file() {
	if(!out_file.empty()) {
	  return out_file;
	} else {
	  return std::string("-");
	}
}

// Trigger logging.
bool runtime_options::global() {
	return _unified == "global";
}

bool runtime_options::unified() {
	return _unified == "stream";
}

path runtime_options::get_log_file(std::string stream_name, event_type t) {
	return get_log_file(stream_name, event_name[t], true);
}

path runtime_options::get_log_file(std::string stream_name) {
	return get_log_file(stream_name, "Events", false);
}

path runtime_options::get_log_file(std::string stream_name, std::string ftype, bool prefix) {
	path r;
	if ( !log_dir.empty() ) r = log_dir;
	else r = current_path();
	r /= (prefix? ftype : "") + stream_name + 
		 (prefix? "" : ftype) + ".dbtdat";
	return r.make_preferred();
}

// Statistics
// Number of samples to collect per statitics period.
unsigned int runtime_options::get_stats_window_size() {
	unsigned int r = 10000;
	if ( sample_size > 0 ) {
	  r = sample_size;
	}
	return r;
}

// Period size, in terms of the number of trigger invocations.
unsigned int runtime_options::get_stats_period() {
	unsigned int r = 10000;
	if ( sample_period > 0 ) {
	  r = sample_period;
	}
	return r;
}

std::string runtime_options::get_stats_file() {
	std::string r = "stats";
	if ( !stats_file.empty() ) {
	  r = stats_file;
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
	if ( !trace_dir.empty() ) {
	  p = trace_dir;
	}
	p /= "trace"+patch::to_string(trace_counter)+".txt";
	std::cerr << "trace file " << p << std::endl;
	return p.make_preferred();
}

}
}
