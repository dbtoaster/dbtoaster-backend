#include "program_base.hpp"

#include "runtime.hpp"

namespace dbtoaster {

/******************************************************************************
	map_t
******************************************************************************/

ProgramBase::map_t::map_t(ProgramBase::serialize_fn_t _serialize_fn) :
        serialize_fn(_serialize_fn)
		, isOutput(false)
		, isTraced(false)
{}

/******************************************************************************
	logger_t
******************************************************************************/

ProgramBase::logger_t::logger_t(const path& fp, bool ln, bool le) :
		log_stream(new ProgramBase::logger_t::file_stream_t(fp.filename().c_str()))
		, log_relation_name(ln)
		, log_event_type(le) 
{
	if (!log_stream) {
		cerr << "failed to open file path " << fp << endl;
	} else {
		cout << "logging to " << fp << endl;
	}
}

void ProgramBase::logger_t::log(string& relation_name, const event_t& evt) {
	if (!log_stream)
		return;

    if (log_relation_name)
        (*log_stream) << relation_name << "|";
    if (log_event_type)
        (*log_stream) << evt.type << "|";
//  (*log_stream) << setprecision(15) << evt.data << endl;  
    for(size_t i = 0 ; i < evt.data.size(); ++i) {
        (*log_stream) << setprecision(15) << evt.data[i];
        if (i < evt.data.size() - 1) (*log_stream) << "|";
    }
    (*log_stream) << endl;
}

/******************************************************************************
	trigger_t
******************************************************************************/

ProgramBase::trigger_t::trigger_t(
			string r_name, 
			event_type ev_type, 
			ProgramBase::trigger_fn_t t_fn,
			boost::shared_ptr<ProgramBase::logger_t> t_logger) :
	name(string(event_name[ev_type]) + "_" + r_name)
	,fn(t_fn)
	,logger(t_logger)
{}

void ProgramBase::trigger_t::trigger_t::log(
			string& relation_name, 
			const event_t& evt) {
	if (!logger)
		return;
	logger->log(relation_name, evt);
}

/******************************************************************************
	relation_t
******************************************************************************/

ProgramBase::relation_t::relation_t(
			string r_name, 
			bool r_is_table, 
			relation_id_t r_id,
			ProgramBase::trigger_fn_t ins_trigger_fn, 
			ProgramBase::trigger_fn_t del_trigger_fn,
			boost::shared_ptr<ProgramBase::logger_t> ins_logger,
			boost::shared_ptr<ProgramBase::logger_t> del_logger) :
	name(r_name)
	, is_table(r_is_table)
	, id(r_id) 
{
	trigger[insert_tuple] =
			ins_trigger_fn ?
				boost::shared_ptr<ProgramBase::trigger_t>(
					new ProgramBase::trigger_t(r_name, insert_tuple,
									ins_trigger_fn, ins_logger)) :
				boost::shared_ptr<ProgramBase::trigger_t>();
	trigger[delete_tuple] =
			del_trigger_fn ?
				boost::shared_ptr<ProgramBase::trigger_t>(
					new ProgramBase::trigger_t(r_name, delete_tuple,
									del_trigger_fn, del_logger)) :
					boost::shared_ptr<ProgramBase::trigger_t>();
}

/******************************************************************************
	ProgramBase
******************************************************************************/

relation_id_t ProgramBase::get_relation_id(string r_name) {
	map<string, boost::shared_ptr<relation_t> >::iterator it =
			relations_by_name.find(r_name);
	return (it != relations_by_name.end()) ? it->second->id : -1;
}

string ProgramBase::get_relation_name(relation_id_t s_id) {
	map<relation_id_t, boost::shared_ptr<relation_t> >::iterator it =
			relations_by_id.find(s_id);
	return (it != relations_by_id.end()) ? it->second->name : "";
}

void ProgramBase::add_relation(
			string r_name, 
			bool is_table, 
			relation_id_t s_id) {
	if (relations_by_name.find(r_name) != relations_by_name.end()) {
		cerr << "Found existing relation " << r_name << endl;
		return;
	}

	relation_id_t id = (s_id != -1) ? s_id : next_relation_id++;
	if (relations_by_id.find(id) != relations_by_id.end()) {
		cerr << "Found existing relation " << r_name << " with id " << id
				<< endl;
		return;
	}

	ProgramBase::relation_ptr_t r = 
			boost::shared_ptr<ProgramBase::relation_t>(
				new ProgramBase::relation_t(r_name, is_table, id));
	relations_by_name[r_name] = r;
	relations_by_id[id] = r;
}

void ProgramBase::add_trigger( 
			string r_name, 
			event_type ev_type, 
			ProgramBase::trigger_fn_t fn) {
	map<string, ProgramBase::relation_ptr_t>::iterator it =
			relations_by_name.find(r_name);
	if (it == relations_by_name.end()) {
		cerr << "Relation not found: " << r_name << endl;
		return;
	}
	ProgramBase::relation_ptr_t r = it->second;

	static boost::shared_ptr<ProgramBase::logger_t> g_log = 
			boost::shared_ptr<ProgramBase::logger_t>();
	boost::shared_ptr<ProgramBase::logger_t> log = 
			boost::shared_ptr<ProgramBase::logger_t>();
	if (run_opts->global()) {
		if (!g_log) {
			path global_file = run_opts->get_log_file("", "Events", true);
			g_log = boost::shared_ptr<ProgramBase::logger_t>(
					new ProgramBase::logger_t(global_file, true, true));
		}
		log = g_log;
	} else if (run_opts->logged_streams.find(r_name)
			!= run_opts->logged_streams.end()) {
		if (run_opts->unified()) {
			event_type other_type =
					ev_type == insert_tuple ? delete_tuple : insert_tuple;
			boost::shared_ptr<ProgramBase::logger_t> other_log = 
					r->trigger[other_type]->logger;

			if (other_log)
				log = other_log;
			else
				log = boost::shared_ptr<ProgramBase::logger_t>(
						new ProgramBase::logger_t(
								run_opts->get_log_file(r->name),	
								false, true));
		} else {
			log = boost::shared_ptr<ProgramBase::logger_t>(
						new ProgramBase::logger_t(
								run_opts->get_log_file(r->name, ev_type),
								false, false));
		}
	}

	r->trigger[ev_type] = 
		boost::shared_ptr<ProgramBase::trigger_t>(
			new ProgramBase::trigger_t(r->name, ev_type, fn, log));
}

void ProgramBase::add_source(
				boost::shared_ptr<streams::source> source, 
				bool is_table_source) {
	if( is_table_source )   table_multiplexer.add_source(source);
	else                    stream_multiplexer.add_source(source);
}

ProgramBase::ProgramBase(int argc, char* argv[]) :
	run_opts(new runtime::runtime_options(argc, argv))
	, stream_multiplexer(12345, 10)
	, table_multiplexer(12345, 10)
	, next_relation_id(0)
	, tuple_count(0)
	, log_count_every(run_opts->log_tuple_count_every)
#ifdef DBT_PROFILE
	, window_size( run_opts->get_stats_window_size() )
	, stats_period( run_opts->get_stats_period() )
	, stats_file( run_opts->get_stats_file() )
	, exec_stats(new trigger_exec_stats("exec", window_size, 
										stats_period, stats_file))
	, ivc_stats(new trigger_exec_stats("ivc", window_size, 
									   stats_period, stats_file))
	, delta_stats(new delta_size_stats("delta_sz", window_size,
									   stats_period, stats_file))
#endif // DBT_PROFILE
{
	if (run_opts->help()) {
		exit(1);
	};
}

void ProgramBase::process_streams() {
	std::list<event_t>::iterator it = stream_multiplexer.eventList->begin();
	std::list<event_t>::iterator it_end = stream_multiplexer.eventList->end();
	for(;it != it_end; ++it) {
		process_event(*it,false);
	}
	if(!stream_multiplexer.eventQue->empty()) {
		stream_multiplexer.eventQue->sort(compare_event_timestamp_order);
		it = stream_multiplexer.eventQue->begin();
		it_end = stream_multiplexer.eventQue->end();
		for(;it != it_end; ++it) {
			process_event(*it,false);
		}
	}
	// XXX memory leak
	// but if we assume that program finishes at this point
	// we can ignore it
	// stream_multiplexer.eventList->clear();
	// stream_multiplexer.eventQue->clear();
#ifdef DBT_PROFILE
	exec_stats->save_now();
#endif // DBT_PROFILE
}

void ProgramBase::process_tables() {
	std::list<event_t>::iterator it = table_multiplexer.eventList->begin();
	std::list<event_t>::iterator it_end = table_multiplexer.eventList->end();
	for(;it != it_end; ++it) {
		process_event(*it,true);
	}
	if(!table_multiplexer.eventQue->empty()) {
		table_multiplexer.eventQue->sort(compare_event_timestamp_order);
		it = table_multiplexer.eventQue->begin();
		it_end = table_multiplexer.eventQue->end();
		for(;it != it_end; ++it) {
			process_event(*it,true);
		}
	}
	// XXX memory leak
	// but if we assume that program finishes at this point
	// we can ignore it
	// table_multiplexer.eventList->clear();
	// table_multiplexer.eventQue->clear();
}

void ProgramBase::set_log_count_every(
			unsigned int _log_count_every) {
	log_count_every = _log_count_every;
}

void ProgramBase::process_event(const event_t& evt, bool process_table) {
	map<relation_id_t, 
				 boost::shared_ptr<ProgramBase::relation_t> >::iterator r_it =
			relations_by_id.find(evt.id);
	if( r_it != relations_by_id.end() &&
		r_it->second->is_table == process_table &&
		r_it->second->trigger[evt.type] )
	{
		boost::shared_ptr<ProgramBase::trigger_t> trig = 
			r_it->second->trigger[evt.type];

		try {
			#ifdef DBT_TRACE
			cout << trig->name << ": " << evt.data << endl;
			#endif // DBT_TRACE
			trig->log(r_it->second->name, evt);

			(trig->fn)(evt.data);
		} catch (boost::bad_any_cast& bc) {
			cout << "bad cast on " << trig->name << ": " << bc.what()
					<< endl;
		}
	} else {
		cerr << "Could not find " << event_name[evt.type]
				<< " handler for relation " << evt.id << endl;
	}
}

void ProgramBase::process_stream_event(const event_t& _evt) {
	#ifdef DBT_TRACE
	trace(cout, false);
	#else
	if (run_opts->is_traced())
		trace(run_opts->get_trace_file(), true);
	#endif // DBT_TRACE

	process_event(_evt, false);

	if (log_count_every && (tuple_count % log_count_every == 0)) {
		struct timeval tp;
		gettimeofday(&tp, NULL);
		cout << tuple_count << " tuples processed at " << tp.tv_sec << "s+"
				<< tp.tv_usec << "us" << endl;
	}
	tuple_count += 1;

	// IProgram::process_stream_event(_evt);
}

void ProgramBase::trace(const path& trace_file, bool debug) {
	if (strcmp(trace_file.filename().c_str(), "-")) {
		std::ofstream ofs(trace_file.filename().c_str());
		trace(ofs, debug);
	} else {
		trace(cout, debug);
	}
}

void ProgramBase::trace(std::ostream &ofs, bool debug) {
	std::auto_ptr<boost::archive::xml_oarchive> oa;

	map<string, ProgramBase::map_ptr_t>::iterator it = 
			maps_by_name.begin();
	for (; it != maps_by_name.end(); it++)
	#ifndef DBT_TRACE_ALL
	if ((!debug && it->second->isOutput) || (debug && it->second->isTraced)) 
	#endif
	{
		if (!oa.get())
			oa = std::auto_ptr<boost::archive::xml_oarchive>(
					new boost::archive::xml_oarchive(ofs, 0));
		it->second->serialize_fn(*oa);
	}
}

}

namespace boost {namespace serialization {

/******************************************************************************
	serialize_tuple
******************************************************************************/

template<class Archive>
serialize_tuple<Archive>::serialize_tuple(Archive& _ar) : ar(_ar)
{}

template<class Archive>
template<typename T>
void serialize_tuple<Archive>::operator()(T& t) const
{
	ar & BOOST_SERIALIZATION_NVP(t);
}

/******************************************************************************
	serialize
******************************************************************************/

template <class Archive, BOOST_PP_ENUM_PARAMS (FUSION_MAX_VECTOR_SIZE, 
                                               typename T)>
void serialize (Archive& ar, 
        boost::fusion::tuple <BOOST_PP_ENUM_PARAMS (FUSION_MAX_VECTOR_SIZE, 
                                                    T) >& p, 
        const unsigned int/* file_version */)
{
    boost::fusion::for_each( p, serialize_tuple<Archive>(ar) );
}

}} //namespace serialization, namespace boost
