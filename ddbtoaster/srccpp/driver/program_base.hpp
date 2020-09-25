/*
 * program_base.hpp
 *
 *  Created on: May 8, 2012
 *      Author: daniel
 */

#ifndef DBTOASTER_PROGRAM_BASE_H
#define DBTOASTER_PROGRAM_BASE_H

#define FUSION_MAX_VECTOR_SIZE 50

#include <map>
#include <functional>
#include <iostream>
#include <fstream>
#include <limits>

#include "filepath.hpp"
#include "runtime.hpp"
#include "iprogram.hpp"
#include "streams.hpp"
#include "standard_adaptors.hpp"    
#include "standard_functions.hpp"
#include "hpds/macro.hpp"
#include "serialization.hpp"

using namespace ::dbtoaster;
using namespace ::dbtoaster::adaptors;
using namespace ::dbtoaster::datasets;
using namespace ::dbtoaster::streams;

#ifdef DBT_PROFILE
#include "statistics.hpp"

#define   BEGIN_PROBE(_class,_key) (_class)->begin_probe  (_key);
#define     END_PROBE(_class,_key) (_class)->end_probe    (_key);
#define BEGIN_TRIGGER(_class,_key) (_class)->begin_trigger(_key);
#define   END_TRIGGER(_class,_key) (_class)->begin_trigger(_key);

using namespace ::dbtoaster::statistics;

#else

#define   BEGIN_PROBE(_class,_key) 
#define     END_PROBE(_class,_key) 
#define BEGIN_TRIGGER(_class,_key) 
#define   END_TRIGGER(_class,_key) 

#endif

#ifdef DBT_TRACE_ALL
#define DBT_TRACE
#endif

namespace dbtoaster {
namespace runtime {
	struct runtime_options;
}

/**
 * Class that provides common functionality for running a program as 
 * specified by the sql input file.
 *
 * It implements the process_streams() and process_stream_event() virtual
 * functions of IProgram. Only take_snapshot() remains to be implemented in a
 * derived class in order to get a completely specified IProgram class.
 *
 * Configuration is performed through the following functions:
 *  - add_map : used for specifying the maps used by the program;
 *  - add_stream : used for specifying the streams that might generate events
 *                 during the execution of the program;
 *  - add_trigger : used for specifying the trigger functions that need to be 
 *                  executed for handling different events;
 *  - add_table_source : used for specifying sources of events for static table
 *                       relations;
 *  - add_stream_source : used for specifying sources of events for stream
 *                        relations.
 */
class ProgramBase: public IProgram {
public:

    typedef std::function<dbtoaster::xml_oarchive&(dbtoaster::xml_oarchive&)> serialize_fn_t;
    struct serializer {
        template<class T>
        static dbtoaster::xml_oarchive& fn(
                dbtoaster::xml_oarchive& oa, const char* name, T* t) {
            return serialize_nvp(oa, name, *t);
        }
    };

    struct map_t {
        serialize_fn_t serialize_fn;
        bool isOutput;
        bool isTraced;

        map_t(serialize_fn_t _serialize_fn);
    };
    typedef std::shared_ptr<map_t> map_ptr_t;

    typedef std::function<void(const event_args_t&)> trigger_fn_t;

    struct logger_t {
        typedef ofstream file_stream_t;

        std::shared_ptr<file_stream_t> log_stream;
        bool log_relation_name;
        bool log_event_type;

        logger_t(const path& fp, bool ln = false, bool le = false);
        void log(string& relation_name, const event_t& evt);
    };

    struct trigger_t {
        string name;
        trigger_fn_t fn;
        std::shared_ptr<logger_t> logger;

        trigger_t(string r_name, event_type ev_type, trigger_fn_t t_fn,
                    std::shared_ptr<logger_t> t_logger);
        void log(string& relation_name, const event_t& evt);
    };

    struct relation_t {
        string name;
        bool is_table;
        relation_id_t id;

        std::shared_ptr<trigger_t> trigger[3];

        relation_t(string r_name, bool r_is_table, relation_id_t r_id,
                trigger_fn_t ins_trigger_fn = 0, 
                trigger_fn_t del_trigger_fn = 0,
                std::shared_ptr<logger_t> ins_logger = std::shared_ptr<logger_t>(),
                std::shared_ptr<logger_t> del_logger = std::shared_ptr<logger_t>());
    };
    typedef std::shared_ptr<relation_t> relation_ptr_t;

    relation_id_t get_relation_id(string r_name);
    string        get_relation_name(relation_id_t s_id);

    template<class T>
	void add_map(string m_name, T& t) {
		if (maps_by_name.find(m_name) != maps_by_name.end()) {
			cerr << "Found existing map " << m_name << endl;
			return;
		}

		serialize_fn_t fn = 
			std::bind(&serializer::template fn<T>,
						std::placeholders::_1, m_name.c_str(), &t);
		map_ptr_t m = std::shared_ptr<map_t>(new map_t(fn));
		maps_by_name[m_name] = m;
		return;
	}

    void add_relation(string r_name, bool is_table = false, 
                      relation_id_t s_id = -1);
    void add_trigger(string r_name, event_type ev_type, trigger_fn_t fn);
    void add_source(std::shared_ptr<streams::source> source, 
                    bool is_table_source = false);

    ProgramBase(int argc = 0, char* argv[] = 0);

    void process_streams();
    void process_tables();

    bool is_async();
    bool is_no_output();

protected:
	void set_log_count_every(unsigned int _log_count_every);
	
    void process_event(const event_t& evt, const bool process_table);
    void process_stream_event(const event_t& evt);
	void process_remaining_events();
	
    std::shared_ptr<runtime::runtime_options> run_opts;
    source_multiplexer stream_multiplexer;
    source_multiplexer table_multiplexer;

    map<string, map_ptr_t> maps_by_name;

    map<string, relation_ptr_t> relations_by_name;
    map<relation_id_t, relation_ptr_t> relations_by_id;
    int next_relation_id;

    unsigned int tuple_count;
    unsigned int log_count_every;

private:
    void trace(const path& trace_file, bool debug);
    void trace(std::ostream &ofs, bool debug);

#ifdef DBT_PROFILE
public:
    unsigned int window_size;
    unsigned int stats_period;
    string stats_file;

    std::shared_ptr<trigger_exec_stats> exec_stats;
    std::shared_ptr<trigger_exec_stats> ivc_stats;
    std::shared_ptr<delta_size_stats> delta_stats;
#endif // DBT_PROFILE

};

FORCE_INLINE void voidFunc() { }

}

#endif /* DBTOASTER_DBT_PROGRAM_BASE_H */
