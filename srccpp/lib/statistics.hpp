#ifndef DBTOASTER_STATISTICS_H
#define DBTOASTER_STATISTICS_H

#include <cstdlib>
#include <map>
#include <utility>
#include <boost/circular_buffer.hpp>
#include <boost/chrono.hpp>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/bind.hpp>

namespace dbtoaster {
  namespace statistics {

    using namespace std;
    using namespace boost;
    //using namespace boost::phoenix;
    using namespace boost::chrono;
    using boost::phoenix::arg_names::arg1;
    using boost::chrono::high_resolution_clock;

    // Sample buffer.
    template<typename value, typename window = circular_buffer<value> >
    class statistics_window {
    protected:
      window win;

    public:
      typedef typename window::iterator iterator;
      typedef typename window::size_type size_type;

      statistics_window() : win(100) {}
      statistics_window(size_type s) : win(s) {}

      virtual void append(value sample) { win.push_back(sample); }
      void clear() { win.clear(); }
      iterator begin() { return win.begin(); }
      iterator end() { return win.end(); }
      void save(ostream& out) {
        for_each(begin(), end(), out << arg1 << ",");
        out << endl;
      }
      size_type size() { return win.size(); }
    };

    // Named object statistics
    template<typename key, typename value,
             typename window = statistics_window<value> >
    class statistics_map {
    private:
      typedef map<key, window> smap; // sample map
      typedef map<key, string> nmap; // key name map

    public:
      typedef window window_type;

      statistics_map(std::shared_ptr<nmap> kn, typename window_type::size_type s)
        : num_samples(s)
      {
        samples = std::shared_ptr<smap>(new smap());
        key_names = kn;
      }

      void append(key k, value sample) {
        if ( samples ) {
          if (samples->find(k) == samples->end()) {
            window w(num_samples);
            samples->insert(make_pair(k,w));
          }
          (*samples)[k].append(sample);
        }
      }

      void clear() {
        if ( samples ) {
          for_each(samples->begin(), samples->end(),
            bind(&smap::value_type::second,arg1).clear());
        }
      }

      void save(ostream& out) {
        typename smap::iterator it = samples->begin();
        for (; it != samples->end(); ++it) {
          out << (*key_names)[it->first] << ",";
          it->second.save(out);
        }
        out.flush();
      }

    private:
      typename window_type::size_type num_samples;
      std::shared_ptr<smap> samples;
      std::shared_ptr<nmap> key_names;
    };

    // File sequences.
    struct file_sequence {
      uint64_t i;
      string prefix, suffix;
      std::shared_ptr<ofstream> current;
      file_sequence(string p, string s = ".txt") : prefix(p), suffix(s), i(0) {}

      std::shared_ptr<ostream> next() {
        if ( current ) current->close();
        ++i;
        string fn = prefix+boost::lexical_cast<string>(i)+suffix;
        current = std::shared_ptr<ofstream>(new ofstream(fn.c_str()));
        return dynamic_pointer_cast<ostream,ofstream>(current);
      }
    };

    // File sequences with periodic construction.
    struct periodic_file_sequence : public file_sequence {
      uint64_t n_firings;
      uint64_t period;

      periodic_file_sequence(uint64_t pd, string p, string s = ".txt")
        : file_sequence(p,s), n_firings(0), period(pd)
      {}

      std::shared_ptr<ostream> next() {
        n_firings++;
        std::shared_ptr<ostream> r;
        if ( period > 0 && n_firings % period == 0 ) r = file_sequence::next();
        return r;
      }

      std::shared_ptr<ostream> next_now() { return file_sequence::next(); }
    };

    // Interval statistics
    template<typename index_id, typename probe_id,
             typename metadata, typename measure>
    class interval_statistics {
    protected:
      typedef map<probe_id, string> names_map;
      typedef map<probe_id, metadata> meta_map;
      typedef dbtoaster::statistics::statistics_map<probe_id, measure>
              stats_map;

      typedef typename boost::function<measure (metadata)> measure_f;

      index_id stats_id;
      std::shared_ptr<names_map> probe_ids;
      std::shared_ptr<meta_map> meta;
      std::shared_ptr<stats_map> stats;
      measure_f probe_f;

      std::shared_ptr<periodic_file_sequence> out;

    public:
      interval_statistics(
        index_id id, typename stats_map::window_type::size_type sz, measure_f f,
        uint64_t period, string fn_prefix)
        : stats_id(id)
      {
        probe_ids = std::shared_ptr<names_map>(new names_map());
        meta = std::shared_ptr<meta_map>(new meta_map());
        stats = std::shared_ptr<stats_map>(new stats_map(probe_ids, sz));
        probe_f = f;

        out = std::shared_ptr<periodic_file_sequence>(
                new periodic_file_sequence(period, fn_prefix));
      }

      void register_probe(probe_id id, string name) {
        if ( probe_ids ) (*probe_ids)[id] = name;
      }

      void begin_probe(probe_id id, metadata mt) { 
        if ( meta ) (*meta)[id] = mt; 
      }

      void end_probe(probe_id id) {
        if ( meta && stats ) stats->append(id, probe_f((*meta)[id]));
      }

      // Periodic saving.
      void save() {
        if ( stats && out ) {
          std::shared_ptr<ostream> s = out->next();
          if ( s ) stats->save(*s);
        }
      }

      // Immediate saving.
      void save_now() {
        if ( stats && out ) {
          std::shared_ptr<ostream> s = out->next_now();
          if ( s ) stats->save(*s);
        }
      }
    };


    // Global, and per-trigger level saves
    template<typename index_id, typename probe_id,
             typename metadata, typename measure>
    class trigger_stats
      : public interval_statistics<index_id, probe_id, metadata, measure>
    {
      typedef interval_statistics<index_id, probe_id, metadata, measure> stats;
    public:
      trigger_stats(index_id id,
                    typename stats::stats_map::window_type::size_type sz,
                    boost::function<measure (metadata)> f,
                    uint64_t period, string fn_prefix)
        : stats(id, sz, f, period, fn_prefix)
      {}

      void begin_trigger(index_id id) {}
      void end_trigger(index_id id) { stats::save(); }
    };

    template<typename index_id, typename probe_id,
             typename metadata, typename measure>
    class multi_trigger_stats
    {
      typedef interval_statistics<index_id, probe_id, metadata, measure> stats;
      typedef map<index_id, std::shared_ptr<stats> > tsmap;
      typedef map<index_id, pair<uint64_t, uint32_t> > idpmap;

    protected:
      tsmap trigger_stats;
      index_id current_id;

    public:
      multi_trigger_stats(idpmap id_periods,
                          boost::function<measure (metadata)> f, 
                          string fn_prefix)
      {
        typename idpmap::iterator it = id_periods.begin();
        typename idpmap::iterator end = id_periods.end();
        for (; it != end; ++it) {
          trigger_stats[it->first] = std::shared_ptr<stats>(
            new stats(it->first, it->second.second, f, 
                      it->second.first, fn_prefix));
        };
      }

      void begin_probe(probe_id pid, metadata m) {
        trigger_stats[current_id]->begin_probe(pid, m);
      }

      void begin_trigger(index_id id) { current_id = id; }

      void end_trigger(index_id id) {
        if ( current_id == id ) {
          if ( trigger_stats.find(id) != trigger_stats.end() )
            trigger_stats[id]->save();
        }
      }
    };

    // Execution statistics
    class trigger_exec_stats : public trigger_stats<
          string, int, boost::chrono::high_resolution_clock::time_point, int>
    {
      typedef boost::chrono::high_resolution_clock hrc;
      typedef trigger_stats<string, int, hrc::time_point, int> tstats;

    public:
      trigger_exec_stats(string stats_id, stats_map::window_type::size_type sz,
                         uint64_t period, string fn_prefix)
        : tstats(
          stats_id, sz,
          boost::phoenix::bind(
            &trigger_exec_stats::probe, this, boost::phoenix::arg_names::arg1),
          period, fn_prefix)
      {}

      void begin_probe(int probe_id) {
        tstats::begin_probe(probe_id, hrc::now());
      }

      int probe(hrc::time_point start) {
        hrc::duration d = hrc::now() - start;
        return d.count();
      }
    };

    class multi_trigger_exec_stats : multi_trigger_stats<
        string, int, boost::chrono::high_resolution_clock::time_point, int>
    {
      typedef boost::chrono::high_resolution_clock hrc;
      typedef multi_trigger_stats<string, int, hrc::time_point, int> mtstats;

    public:
      multi_trigger_exec_stats(
        map<string, pair<uint64_t, uint32_t> > id_periods, string fn_prefix)
        : mtstats(id_periods,
            boost::phoenix::bind(
              &multi_trigger_exec_stats::probe, this,
              boost::phoenix::arg_names::arg1),
            fn_prefix)
      {}

      int probe(hrc::time_point start) {
        hrc::duration d = hrc::now() - start;
        return d.count();
      }
    };

    // Number of entries updated per statement.
    class delta_size_stats : public trigger_stats<string, int, int, int>
    {
      typedef trigger_stats<string, int, int, int> tstats;
      map<int, int> update_counts;

    public:
      delta_size_stats(string stats_id, stats_map::window_type::size_type sz,
                       uint64_t period, string fn_prefix)
      : tstats(
          stats_id, sz,
          boost::phoenix::bind(
            &delta_size_stats::probe, this, boost::phoenix::arg_names::arg1),
          period, fn_prefix)
      {}

      void begin_probe(int id) {
        update_counts[id] = 0;
        tstats::begin_probe(id, id);
      }

      int probe(int id) { return update_counts[id]; }

      void update(int id) { update_counts[id] += 1; }
      void update(int id, int sz) { update_counts[id] += sz; }
    };
  }
}

#endif
