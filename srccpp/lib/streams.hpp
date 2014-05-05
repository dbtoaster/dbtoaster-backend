#ifndef DBTOASTER_STREAMS_H
#define DBTOASTER_STREAMS_H

#include <map>
#include <set>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <streambuf>
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

// Adaptor and stream interfaces.

struct stream_adaptor
{
    stream_adaptor() {}

    virtual void read_adaptor_events(char* data, shared_ptr<list<event_t> > eventList, shared_ptr<list<event_t> > eventQue) = 0;
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

// Sources
struct source
{
    frame_descriptor frame_info;
    shared_ptr<stream_adaptor> adaptor;

    source(frame_descriptor& f, shared_ptr<stream_adaptor> a);
    
    // Process adaptors in the first stage, accumulating and returning
    // stream events
    virtual void read_source_events(shared_ptr<list<event_t> > eventList, shared_ptr<list<event_t> > eventQue) = 0;

    virtual void init_source() = 0;
};

struct dbt_file_source : public source
{
    typedef std::ifstream file_stream;
    shared_ptr<file_stream> source_stream;

    dbt_file_source(const string& path, frame_descriptor& f, shared_ptr<stream_adaptor> a);

    void read_source_events(shared_ptr<list<event_t> > eventList, shared_ptr<list<event_t> > eventQue);

    void init_source() {}
};

struct source_multiplexer
{
    std::vector<shared_ptr<source> > inputs;
    shared_ptr<source> current;
    int step, remaining, block;
    shared_ptr<list<event_t> > eventList;
    shared_ptr<list<event_t> > eventQue;

    source_multiplexer(int seed, int st);
    source_multiplexer(int seed, int st, set<shared_ptr<source> >& s);

    void add_source(shared_ptr<source> s);
    void remove_source(shared_ptr<source> s);

    void init_source();
};

}
}

#endif

