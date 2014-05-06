#ifndef DBTOASTER_STATISTICS_H
#define DBTOASTER_STATISTICS_H

#include <cstdlib>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <boost/circular_buffer.hpp>
#include <boost/chrono/system_clocks.hpp>

namespace dbtoaster {
  namespace statistics {

    using namespace std;
    using namespace boost;

    // Sample buffer.
    template<typename value, typename window = circular_buffer<value> >
    class statistics_window {
    protected:
      window win;

    public:
      typedef typename window::iterator iterator;
      typedef typename window::size_type size_type;

      statistics_window();
      statistics_window(size_type s);

      virtual void append(value sample);
      void clear();
      iterator begin();
      iterator end();
      void save(ostream& out);
      size_type size();
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

      statistics_map(shared_ptr<nmap> kn, typename window_type::size_type s);

      void append(key k, value sample);
      void clear();
      void save(ostream& out);

    private:
      typename window_type::size_type num_samples;
      shared_ptr<smap> samples;
      shared_ptr<nmap> key_names;
    };

    // File sequences.
    struct file_sequence {
      uint64_t i;
      string prefix, suffix;
      shared_ptr<ofstream> current;
      file_sequence(string p, string s = ".txt") : prefix(p), suffix(s), i(0) {}

      shared_ptr<ostream> next();
    };

    // File sequences with periodic construction.
    struct periodic_file_sequence : public file_sequence {
      uint64_t n_firings;
      uint64_t period;

      periodic_file_sequence(uint64_t pd, string p, string s = ".txt")
        : file_sequence(p,s), n_firings(0), period(pd)
      {}

      shared_ptr<ostream> next();

      shared_ptr<ostream> next_now() { return file_sequence::next(); }
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
      shared_ptr<names_map> probe_ids;
      shared_ptr<meta_map> meta;
      shared_ptr<stats_map> stats;
      measure_f probe_f;

      shared_ptr<periodic_file_sequence> out;

    public:
      interval_statistics(
        index_id id, typename stats_map::window_type::size_type sz, measure_f f,
        uint64_t period, string fn_prefix);

      void register_probe(probe_id id, string name);

      void begin_probe(probe_id id, metadata mt);

      void end_probe(probe_id id);

      // Periodic saving.
      void save();

      // Immediate saving.
      void save_now();
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
      typedef map<index_id, shared_ptr<stats> > tsmap;
      typedef map<index_id, pair<uint64_t, uint32_t> > idpmap;

    protected:
      tsmap trigger_stats;
      index_id current_id;

    public:
      multi_trigger_stats(idpmap id_periods,
                          boost::function<measure (metadata)> f, 
                          string fn_prefix);

      void begin_probe(probe_id pid, metadata m);
      void begin_trigger(index_id id);
      void end_trigger(index_id id);
    };

    // Execution statistics
    class trigger_exec_stats : public trigger_stats<
          string, int, boost::chrono::high_resolution_clock::time_point, int>
    {
      typedef boost::chrono::high_resolution_clock hrc;
      typedef trigger_stats<string, int, hrc::time_point, int> tstats;

    public:
      trigger_exec_stats(string stats_id, stats_map::window_type::size_type sz,
                         uint64_t period, string fn_prefix);

      void begin_probe(int probe_id);
      int probe(hrc::time_point start);
    };

    class multi_trigger_exec_stats : multi_trigger_stats<
        string, int, boost::chrono::high_resolution_clock::time_point, int>
    {
      typedef boost::chrono::high_resolution_clock hrc;
      typedef multi_trigger_stats<string, int, hrc::time_point, int> mtstats;

    public:
      multi_trigger_exec_stats(
        map<string, pair<uint64_t, uint32_t> > id_periods, string fn_prefix);

      int probe(hrc::time_point start);
    };

    // Number of entries updated per statement.
    class delta_size_stats : public trigger_stats<string, int, int, int>
    {
      typedef trigger_stats<string, int, int, int> tstats;
      map<int, int> update_counts;

    public:
      delta_size_stats(string stats_id, stats_map::window_type::size_type sz,
                       uint64_t period, string fn_prefix);

      void begin_probe(int id);

      int probe(int id);

      void update(int id);
      void update(int id, int sz);
    };
  }
}

#endif
