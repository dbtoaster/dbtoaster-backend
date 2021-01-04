#include "statistics_split.hpp"

#include <fstream>

#include <cstdint>
#include <functional>

namespace dbtoaster {
namespace statistics {

using namespace std;

/******************************************************************************
	statistics_window
******************************************************************************/
template<typename value, typename window>
statistics_window<value,window>::statistics_window() : win(100) {
}
template<typename value, typename window>
statistics_window<value,window>::statistics_window(size_type s) : win(s) {
}
template<typename value, typename window>
void statistics_window<value,window>::append(value sample) { 
	win.push_back(sample); 
}
template<typename value, typename window>
void statistics_window<value,window>::clear() { 
	win.clear(); 
}

template<typename value, typename window>
typename statistics_window<value,window>::iterator 
statistics_window<value,window>::begin() { 
	return win.begin(); 
}
template<typename value, typename window>
typename statistics_window<value,window>::iterator 
statistics_window<value,window>::end() { 
	return win.end(); 
}

template<typename value, typename window>
void statistics_window<value,window>::save(ostream& out) {
	std::for_each(begin(), end(), [&out] (value &arg1) { out << arg1 << ","; });
		out << endl;
}
template<typename value, typename window>
typename statistics_window<value,window>::size_type 
statistics_window<value,window>::size() { 
	return win.size(); 
}

/******************************************************************************
	statistics_map
******************************************************************************/
template<typename key, typename value, typename window>
statistics_map<key,value,window>::statistics_map(std::shared_ptr<nmap> kn, 
											typename window_type::size_type s)
        : num_samples(s)
{
	samples = std::shared_ptr<smap>(new smap());
	key_names = kn;
}

template<typename key, typename value, typename window>
void statistics_map<key,value,window>::append(key k, value sample) {
	if ( samples ) {
	  if (samples->find(k) == samples->end()) {
		window w(num_samples);
		samples->insert(make_pair(k,w));
	  }
	  (*samples)[k].append(sample);
	}
}

template<typename key, typename value, typename window>
void statistics_map<key,value,window>::clear() {
	if ( samples ) {
	  std::for_each(samples->begin(), samples->end(),
		std::bind(&smap::value_type::second,std::placeholders::_1).clear());
	}
}

template<typename key, typename value, typename window>
void statistics_map<key,value,window>::save(ostream& out) {
	typename smap::iterator it = samples->begin();
	for (; it != samples->end(); ++it) {
	  out << (*key_names)[it->first] << ",";
	  it->second.save(out);
	}
	out.flush();
}

/******************************************************************************
	file_sequence
******************************************************************************/
std::shared_ptr<ostream> file_sequence::next() {
	if ( current ) current->close();
	++i;
	string fn = prefix+std::to_string(i)+suffix;
	current = std::shared_ptr<ofstream>(new ofstream(fn.c_str()));
	return dynamic_pointer_cast<ostream,ofstream>(current);
}

/******************************************************************************
	periodic_file_sequence
******************************************************************************/
std::shared_ptr<ostream> periodic_file_sequence::next() {
	++n_firings;
	std::shared_ptr<ostream> r;
	if ( period > 0 && n_firings % period == 0 ) r = file_sequence::next();
	return r;
}
	  
/******************************************************************************
	interval_statistics
******************************************************************************/
template<typename index_id, typename probe_id,
		 typename metadata, typename measure>
interval_statistics<index_id,probe_id,metadata,measure>::interval_statistics(
	index_id id, typename stats_map::window_type::size_type sz, measure_f f,
	uint64_t period, string fn_prefix)	: stats_id(id)
{
	probe_ids = std::shared_ptr<names_map>(new names_map());
	meta = std::shared_ptr<meta_map>(new meta_map());
	stats = std::shared_ptr<stats_map>(new stats_map(probe_ids, sz));
	probe_f = f;

	out = std::shared_ptr<periodic_file_sequence>(
			new periodic_file_sequence(period, fn_prefix));
}

template<typename index_id, typename probe_id,
		 typename metadata, typename measure>
void interval_statistics<index_id,probe_id,metadata,measure>::register_probe(
		probe_id id, string name) 
{
	if ( probe_ids ) (*probe_ids)[id] = name;
}

template<typename index_id, typename probe_id,
		 typename metadata, typename measure>
void interval_statistics<index_id,probe_id,metadata,measure>::begin_probe(
		probe_id id, metadata mt) 
{ 
	if ( meta ) (*meta)[id] = mt; 
}

template<typename index_id, typename probe_id,
		 typename metadata, typename measure>
void interval_statistics<index_id,probe_id,metadata,measure>::end_probe(
		probe_id id) 
{
	if ( meta && stats ) stats->append(id, probe_f((*meta)[id]));
}

// Periodic saving.
template<typename index_id, typename probe_id,
		 typename metadata, typename measure>
void interval_statistics<index_id,probe_id,metadata,measure>::save() {
	if ( stats && out ) {
	  std::shared_ptr<ostream> s = out->next();
	  if ( s ) stats->save(*s);
	}
}

// Immediate saving.
template<typename index_id, typename probe_id,
		 typename metadata, typename measure>
void interval_statistics<index_id,probe_id,metadata,measure>::save_now() {
	if ( stats && out ) {
	  std::shared_ptr<ostream> s = out->next_now();
	  if ( s ) stats->save(*s);
	}
}

/******************************************************************************
	multi_trigger_stats
******************************************************************************/	  
template<typename index_id, typename probe_id,
         typename metadata, typename measure>
multi_trigger_stats<index_id,probe_id,metadata,measure>::multi_trigger_stats(
		idpmap id_periods,
		std::function<measure (metadata)> f, 
		string fn_prefix)
{
	typename idpmap::iterator it = id_periods.begin();
	typename idpmap::iterator end = id_periods.end();
	for (; it != end; ++it) {
	  trigger_stats[it->first] = std::shared_ptr<stats>(
		new stats(it->first, it->second.second, f, 
				  it->second.first, fn_prefix));
	}
}

template<typename index_id, typename probe_id,
         typename metadata, typename measure>
void multi_trigger_stats<index_id,probe_id,metadata,measure>::begin_probe(
		probe_id pid, metadata m) 
{
	trigger_stats[current_id]->begin_probe(pid, m);
}

template<typename index_id, typename probe_id,
         typename metadata, typename measure>
void multi_trigger_stats<index_id,probe_id,metadata,measure>::begin_trigger(
		index_id id) 
{ 
	current_id = id; 
}

template<typename index_id, typename probe_id,
         typename metadata, typename measure>
void multi_trigger_stats<index_id,probe_id,metadata,measure>::end_trigger(
		index_id id) 
{
	if ( current_id == id ) {
	  if ( trigger_stats.find(id) != trigger_stats.end() )
		trigger_stats[id]->save();
	}
}


/******************************************************************************
	trigger_exec_stats
******************************************************************************/
trigger_exec_stats::trigger_exec_stats(
		string stats_id, stats_map::window_type::size_type sz,
        uint64_t period, string fn_prefix)
	: tstats(
		stats_id, sz,
		std::bind(
			&trigger_exec_stats::probe, this, std::placeholders::_1),
		period, fn_prefix)
{}

void trigger_exec_stats::begin_probe(int probe_id) {
	tstats::begin_probe(probe_id, hrc::now());
}

int trigger_exec_stats::probe(hrc::time_point start) {
	hrc::duration d = hrc::now() - start;
	return d.count();
}


/******************************************************************************
	multi_trigger_exec_stats
******************************************************************************/
multi_trigger_exec_stats::multi_trigger_exec_stats(
        map<string, pair<uint64_t, uint32_t> > id_periods, string fn_prefix)
        : mtstats(id_periods,
            std::bind(
              &multi_trigger_exec_stats::probe, this,
              std::placeholders::_1),
            fn_prefix)
{}

int multi_trigger_exec_stats::probe(hrc::time_point start) {
	hrc::duration d = hrc::now() - start;
	return d.count();
}

/******************************************************************************
	delta_size_stats
******************************************************************************/
delta_size_stats::delta_size_stats(string stats_id, 
					stats_map::window_type::size_type sz,
                    uint64_t period, string fn_prefix)
      : tstats(
          stats_id, sz,
          std::bind(
            &delta_size_stats::probe, this, std::placeholders::_1),
          period, fn_prefix)
{}

void delta_size_stats::begin_probe(int id) {
	update_counts[id] = 0;
	tstats::begin_probe(id, id);
}

int delta_size_stats:: probe(int id) { return update_counts[id]; }

void delta_size_stats::update(int id) { update_counts[id] += 1; }
void delta_size_stats::update(int id, int sz) { update_counts[id] += sz; }
	  
	  
}
}