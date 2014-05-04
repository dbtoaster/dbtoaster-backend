#ifndef DBTOASTER_STREAMS_H
#define DBTOASTER_STREAMS_H

#include <map>
#include <set>
#include <list>
#include <vector>
#include <sys/time.h>

#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file.hpp>

#include "event.hpp"


using namespace ::std;
using namespace ::boost;
using namespace boost::iostreams;


namespace dbtoaster {

// These need to be placed here as C++ doesn't search for overloaded
// << operators in all the available namespaces
std::ostream& operator<<(std::ostream &strm, const boost::any &a);
std::ostream& operator<<(std::ostream &strm, const vector<boost::any> &args);

namespace streams {

struct ordered {
    virtual unsigned int order() = 0;
};

// Adaptor and stream interfaces.
struct stream_adaptor : public ordered
{
    // All adaptors have an internal ordering for input stream synchronization.
    unsigned int current_order;
    stream_adaptor() : current_order(0) {}

    // The default ordering function.
    virtual unsigned int order() { return current_order; }

    // processes the data, adding all stream events generated to the list.
    virtual void process(const string& data,
            boost::shared_ptr<list<event_t> > dest) = 0;

    virtual void finalize(boost::shared_ptr<list<event_t> > dest) = 0;
    
    virtual bool has_buffered_events() = 0;
    
    virtual void get_buffered_events(boost::shared_ptr<list<event_t> > dest) = 0;

};

// Framing
enum frame_type { fixed_size, delimited, variable_size };
struct frame_descriptor {
    frame_type type;
    int size;
    string delimiter;
    int off_to_size;
    int off_to_end;
    frame_descriptor() : type(delimited), size(0), delimiter("\n") {}
    frame_descriptor(string d) : type(delimited), size(0), delimiter(d) {}
    frame_descriptor(int sz) : type(fixed_size), size(sz) {}
    frame_descriptor(int os, int oe)
    : type(variable_size), size(0), off_to_size(os), off_to_end(oe)
    {}
};

struct dynamic_poset {
    typedef set<boost::shared_ptr<ordered> > pset;
    typedef map<unsigned int, boost::shared_ptr<pset> > repr;
    typedef repr::iterator iterator;
    typedef pair<pset::iterator, pset::iterator> class_range;
    repr poset;

    dynamic_poset() {}
    dynamic_poset(pset& elements);

    inline void clear() { poset.clear(); }
    inline bool empty() { return poset.empty(); }
    inline iterator find(unsigned int o) { return poset.find(o); }
    inline iterator begin() { return poset.begin(); }
    inline iterator end() { return poset.end(); }

    // Returns the total number of elements in the poset.
    size_t size();

    unsigned int order();

    boost::shared_ptr<class_range> range(unsigned int order);

    void add_element(boost::shared_ptr<ordered> e);
    void remove_element(boost::shared_ptr<ordered> e);

    // Helper to update an element's position, by removing it from a
    // specific stage.
    void remove_element(unsigned int order, boost::shared_ptr<ordered> e);
    void reorder_elements(unsigned int order);
};

// Sources
struct source : public ordered
{
    typedef list<boost::shared_ptr<stream_adaptor> > adaptor_list;
    frame_descriptor frame_info;
    dynamic_poset adaptors;

    source(frame_descriptor& f, adaptor_list& a);

    unsigned int order() { return adaptors.order(); }

    void add_adaptor(boost::shared_ptr<stream_adaptor> a);

    void remove_adaptor(unsigned int order, boost::shared_ptr<stream_adaptor> a);
    
    bool has_buffered_events();

    virtual void init_source() = 0;
    virtual bool has_inputs() = 0;
    virtual boost::shared_ptr<list<event_t> > next_inputs() = 0;
};

struct dbt_file_source : public source
{
    typedef stream<file_source> file_stream;
    boost::shared_ptr<file_stream> source_stream;
    boost::shared_ptr<string> buffer;
    size_t bufferPos;
	
    dbt_file_source(const string& path, frame_descriptor& f, adaptor_list& a);

    void init_source() {}

    bool has_inputs() { 
        return has_frame_inputs() || has_buffered_events(); 
    }
    
    bool has_frame_inputs() {
        return has_frame() || (source_stream && source_stream->good());
    }

    bool has_frame();

    boost::shared_ptr<string> frame_from_buffer();
    boost::shared_ptr<string> next_frame();

    // Process adaptors in the first stage, accumulating and returning
    // stream events
    void process_adaptors(string& data, boost::shared_ptr<list<event_t> >& r);

    // Finalize all adaptors, accumulating stream events.
    void finalize_adaptors(boost::shared_ptr<list<event_t> >& r);

    // Get buffered events from all adaptors
    void collect_buffered_events(boost::shared_ptr<list<event_t> >& r);
    boost::shared_ptr<list<event_t> > next_inputs();
};

struct source_multiplexer
{
    dynamic_poset inputs;
    boost::shared_ptr<source> current;
    unsigned int current_order;
    int step, remaining, block;

    source_multiplexer(int seed, int st);
    source_multiplexer(int seed, int st, set<boost::shared_ptr<source> >& s);

    void add_source(boost::shared_ptr<source> s);
    void remove_source(boost::shared_ptr<source> s);

    void init_source();
    bool has_inputs();
    boost::shared_ptr<list<event_t> > next_inputs();
};

struct stream_registry {
    boost::shared_ptr<source_multiplexer> multiplexer;
    map<string, boost::shared_ptr<source> > data_sources;
    map<string, list<boost::shared_ptr<stream_adaptor> > > source_adaptors;

    stream_registry(boost::shared_ptr<source_multiplexer> m) : multiplexer(m) {}

    void register_adaptor(string source_name, boost::shared_ptr<stream_adaptor> a);
    void register_source(string name, boost::shared_ptr<source> src);

    boost::shared_ptr<dbt_file_source> initialize_file_source(
            string stream_name, string file_name, frame_descriptor& f);
    void register_multiplexer(boost::shared_ptr<source_multiplexer> m);
};

}
}

#endif

