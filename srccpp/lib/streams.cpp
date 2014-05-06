#include "streams.hpp"

#include "runtime.hpp"

#include <boost/filesystem.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

using namespace boost::filesystem;
using namespace boost::lambda;


using namespace ::dbtoaster::runtime;

namespace dbtoaster {

std::ostream& operator<<(std::ostream &strm, const boost::any &a) {
    try{
        if( a.type() == typeid(int) )
            return strm << any_cast<int>(a);

        else if( a.type() == typeid(long) )
            return strm << any_cast<long>(a);

        else if( a.type() == typeid(double) )
            return strm << any_cast<double>(a);

        else if( a.type() == typeid(std::string) )
            return strm << any_cast<std::string>(a);
        else
            cerr << "event_arg: Unrecognized type in <<: " 
                 << a.type().name() << endl;
    } catch (boost::bad_any_cast& bc) {
        cerr << "bad cast on <<: " << bc.what() << endl;
    }
    return strm;
}

std::ostream& operator<<(std::ostream &strm, const vector<boost::any> &args) {
    if( !args.empty() )
    {
        strm << args[0];
        for( size_t i = 1; i < args.size(); i++ )
            strm << ", " << args[i];
    }
    return strm;
}


namespace streams {

/******************************************************************************
	dynamic_poset
******************************************************************************/
dynamic_poset::dynamic_poset(pset& elements) {
	for (pset::iterator it = elements.begin(); it != elements.end(); ++it) {
		add_element(*it);
	}
}

// Returns the total number of elements in the poset.
size_t dynamic_poset::size() {
	size_t r = 0;
	for (iterator it = begin(); it != end(); ++it) {
		r += it->second? it->second->size(): 0;
	}
	return r;
}

unsigned int dynamic_poset::order() { 
	return poset.empty()? (0) : poset.begin()->first; 
}

boost::shared_ptr<dynamic_poset::class_range> dynamic_poset::range(unsigned int order) {
	boost::shared_ptr<dynamic_poset::class_range> r;
	iterator it = find(order);
	if ( it == end() || !(it->second) ) return r;
	r = boost::shared_ptr<dynamic_poset::class_range>(
			new dynamic_poset::class_range( it->second->begin(), 
											it->second->end()));
	return r;
}

void dynamic_poset::add_element(boost::shared_ptr<ordered> e) {
	//        cerr << "Adding element at " << e->order() << endl;
	if ( !poset[e->order()] ) {
		poset[e->order()] = boost::shared_ptr<pset>(new pset());
		poset[e->order()]->insert(e);
	} else {
		poset[e->order()]->insert(e);
	}
}

void dynamic_poset::remove_element(boost::shared_ptr<ordered> e) {
	unsigned int o = e->order();
	iterator it = find(o);
	//        cerr << "Removing element at " << e->order() 
	//             << " out of " << it->second->size() << endl;
	if ( it != end() ) it->second->erase(e);
	if ( it->second->empty() ) poset.erase(o);
}

// Helper to update an element's position, by removing it from a
// specific stage.
void dynamic_poset::remove_element(unsigned int order, boost::shared_ptr<ordered> e) {
	iterator it = poset.find(order);
	if ( it != poset.end() ) it->second->erase(e);
}

void dynamic_poset::reorder_elements(unsigned int order) {
	//        cerr << "Reordering elements at " << order << endl;
	iterator it = find(order);
	if ( it == end() ) return;
	boost::shared_ptr<pset> ps = it->second;
	pset removals;

	// Process adaptors, tracking those that have changed their position.
	for(pset::iterator it = ps->begin(); it != ps->end(); ++it) {
		if ( (*it) && (*it)->order() != order ) removals.insert(*it);
	}

	pset::iterator rm_it = removals.begin();
	pset::iterator rm_end = removals.end();
	for (; rm_it != rm_end; ++rm_it) {
		// Re-add the adaptor at its new stage.
		if ( (*rm_it)->order() > 0) {
			if ( (*rm_it)->order() > order ) add_element(*rm_it);
			else if ( (*rm_it)->order() < order ) {
				cerr << "invalid adaptor order ... removing" << endl;
			}
		}
		ps->erase(*rm_it);
	}
	//        cerr << "Size is now " << ps->size() 
	//             << "; empty: " << ps->empty() << endl;
	if ( ps->empty() ) {
		poset.erase(order);
		//          cerr << "Moving from " << order 
		//               << " to " << this->order() << endl;
	}

}


/******************************************************************************
	source
******************************************************************************/
source::source(frame_descriptor& f, adaptor_list& a) : frame_info(f) {
	for(adaptor_list::iterator it = a.begin(); it != a.end(); ++it) {
		add_adaptor(*it);
	}
}

void source::add_adaptor(boost::shared_ptr<stream_adaptor> a) {
	adaptors.add_element(dynamic_pointer_cast<ordered>(a));
}

void source::remove_adaptor(unsigned int order, boost::shared_ptr<stream_adaptor> a) {
	adaptors.remove_element(order, dynamic_pointer_cast<ordered>(a));
}

bool source::has_buffered_events() {    
	dynamic_poset::iterator it = adaptors.begin();
	dynamic_poset::iterator end = adaptors.end();
	bool found = false;

	for (; it != end; ++it)
	{
		if ( it->second ) {
			for (dynamic_poset::pset::iterator a_it = it->second->begin();
					a_it != it->second->end(); ++a_it)
			{
				boost::shared_ptr<stream_adaptor> a =
						dynamic_pointer_cast<stream_adaptor>(*a_it);
				if ( a ) found = found || a->has_buffered_events();
			}
		} else {
			cerr << "invalid adaptors poset class at position "
					<< it->first << endl;
		}
	}
	return found;
}


/******************************************************************************
	dbt_file_source
******************************************************************************/
dbt_file_source::dbt_file_source(
		const string& path, frame_descriptor& f, adaptor_list& a): source(f,a)
{
	if ( boost::filesystem::exists( path ) )
	{
		source_stream = boost::shared_ptr<file_stream>(new file_stream(path));
		if( runtime_options::verbose() )
			cerr << "reading from " << path
				 << " with " << a.size() << " adaptors" << endl;
	}
	else
		cerr << "File not found: " << path << endl;
	buffer = boost::shared_ptr<string>(new string());
}

bool dbt_file_source::has_frame() {
	bool r = false;
	if ( frame_info.type == fixed_size ) {
		r = buffer && buffer->size() >= frame_info.size;
	} else if ( frame_info.type == delimited ) {
		r = buffer && (buffer->find(frame_info.delimiter) != string::npos);
	}
	return r;
}

boost::shared_ptr<string> dbt_file_source::frame_from_buffer() {
	boost::shared_ptr<string> r;
	if (frame_info.type == fixed_size) {
		r = boost::shared_ptr<string>(
				new string(buffer->substr(0,frame_info.size)));
		buffer = boost::shared_ptr<string>(
				new string(buffer->substr(frame_info.size, string::npos)));
	} else if ( frame_info.type == delimited ) {
		size_t delim_pos = buffer->find(frame_info.delimiter);
		r = boost::shared_ptr<string>(new string(buffer->substr(0, delim_pos)));
		buffer = boost::shared_ptr<string>(
				new string(buffer->substr(
						delim_pos+frame_info.delimiter.size(),
						string::npos)));
	}
	return r;
}

boost::shared_ptr<string> dbt_file_source::next_frame() {
	boost::shared_ptr<string> r;

	char buf[((frame_info.size<1024) ? 1024 : frame_info.size)];

	if (frame_info.type == fixed_size) {
		while ( source_stream->good() && !has_frame() ) {
			source_stream->read(buf, frame_info.size);
			(*buffer) += string(buf, source_stream->gcount());
		}
	}
	else if ( frame_info.type == delimited ) {

		while ( source_stream->good() && !has_frame() ) {

			source_stream->read(buf, sizeof(buf));
			(*buffer) += string(buf, source_stream->gcount());
		}

		if( !source_stream->good() &&
				buffer->find(frame_info.delimiter) != 
				(buffer->size()-frame_info.delimiter.size()) )
			(*buffer) += frame_info.delimiter;


		size_t dd_index = 0;
		string ddelimiter = frame_info.delimiter+frame_info.delimiter;
		while ( (dd_index = buffer->find(ddelimiter,dd_index)) !=
				string::npos )
			buffer->replace( dd_index, ddelimiter.size(), 
							 frame_info.delimiter );

	}
	else if ( frame_info.type == variable_size ) {
		cerr << "variable size frames not supported" << endl;
	}
	else {
		cerr << "invalid frame type" << endl;
	}

	if ( has_frame() ) r = frame_from_buffer();

	return r;
}

// Process adaptors in the first stage, accumulating and returning
// stream events
void dbt_file_source::process_adaptors(
		string& data, boost::shared_ptr<list<event_t> >& r) 
{
	unsigned int min_order = adaptors.order();
	boost::shared_ptr<dynamic_poset::class_range> range = 
			adaptors.range(min_order);
	if ( !range ) {
		cerr << "invalid min order at source with empty range" << endl;
		return;
	}

	for(dynamic_poset::pset::iterator it = range->first;
			it != range->second; ++it)
	{
		boost::shared_ptr<stream_adaptor> adaptor =
				dynamic_pointer_cast<stream_adaptor>(*it);
		if ( adaptor ) adaptor->process(data, r);
	}
	adaptors.reorder_elements(min_order);
}

// Finalize all adaptors, accumulating stream events.
void dbt_file_source::finalize_adaptors(boost::shared_ptr<list<event_t> >& r) 
{
	dynamic_poset::iterator it = adaptors.begin();
	dynamic_poset::iterator end = adaptors.end();

	for (; it != end; ++it)
	{
		if ( it->second ) {
			for (dynamic_poset::pset::iterator a_it = it->second->begin();
					a_it != it->second->end(); ++a_it)
			{
				boost::shared_ptr<stream_adaptor> a =
						dynamic_pointer_cast<stream_adaptor>(*a_it);
				if ( a ) a->finalize(r);
			}
		} else {
			cerr << "invalid adaptors poset class at position "
					<< it->first << endl;
		}
	}

	adaptors.clear();
}

// Get buffered events from all adaptors
void dbt_file_source::collect_buffered_events(
										boost::shared_ptr<list<event_t> >& r) 
{
	unsigned int min_order = adaptors.order();
	boost::shared_ptr<dynamic_poset::class_range> range = 
			adaptors.range(min_order);
	if ( !range ) {
		cerr << "invalid min order at source with empty range" << endl;
		return;
	}

	for(dynamic_poset::pset::iterator it = range->first;
			it != range->second; ++it)
	{
		boost::shared_ptr<stream_adaptor> adaptor =
				dynamic_pointer_cast<stream_adaptor>(*it);
		if ( adaptor ) { 
			adaptor->get_buffered_events(r);
			adaptor->current_order = 0;    // mark for removal  
		}
		
	}
	adaptors.reorder_elements(min_order);
}


boost::shared_ptr<list<event_t> > dbt_file_source::next_inputs() {
	boost::shared_ptr<list<event_t> > r;

	if ( adaptors.empty() ) return r;


	if ( has_frame_inputs() ) {
		// get the next frame of data based on the frame type.
		boost::shared_ptr<string> data = next_frame();

		if ( data ) {
			r = boost::shared_ptr<list<event_t> >(new list<event_t>());
			process_adaptors(*data, r);
		}
	} else if ( has_buffered_events() ) {
		r = boost::shared_ptr<list<event_t> >(new list<event_t>());
		collect_buffered_events(r);
	} else if ( source_stream->is_open() ) {
		source_stream->close();
		r = boost::shared_ptr<list<event_t> >(new list<event_t>());
		finalize_adaptors(r);
	}

	return r;
}

/******************************************************************************
	source_multiplexer
******************************************************************************/
source_multiplexer::source_multiplexer(int seed, int st)
	: current_order(0), step(st), remaining(0), block(100)
{
	srandom(seed);
}

source_multiplexer::source_multiplexer( int seed, int st, 
										set<boost::shared_ptr<source> >& s)
{
	source_multiplexer(seed, st);
	set<boost::shared_ptr<source> >::iterator it = s.begin();
	set<boost::shared_ptr<source> >::iterator end = s.end();
	for(; it != end; ++it) add_source(*it);
	current_order = inputs.order();
}

void source_multiplexer::add_source(boost::shared_ptr<source> s) {
	inputs.add_element(dynamic_pointer_cast<ordered>(s));
}

void source_multiplexer::remove_source(boost::shared_ptr<source> s) {
	inputs.remove_element(dynamic_pointer_cast<ordered>(s));
}

void source_multiplexer::init_source() {
	dynamic_poset::iterator it = inputs.begin();
	dynamic_poset::iterator end = inputs.end();
	for (; it != end; ++it) {
		boost::shared_ptr<dynamic_poset::class_range> r = inputs.range(it->first);
		if ( r ) {
			for (dynamic_poset::pset::iterator it = r->first; 
				 it != r->second; ++it) {
				boost::shared_ptr<source> s = dynamic_pointer_cast<source>(*it);
				if ( s ) s->init_source();
			}
		} else {
			cerr << "invalid source poset class at position " 
				 << it->first << endl;
		}
	}
}

bool source_multiplexer::has_inputs() {
	bool found = false;
	dynamic_poset::iterator it = inputs.begin();
	dynamic_poset::iterator end = inputs.end();
	for (; it != end && !found; ++it) {
		boost::shared_ptr<dynamic_poset::class_range> r = inputs.range(it->first);
		if ( r ) {
			for (dynamic_poset::pset::iterator it = r->first;
					it != r->second && !found; ++it)
			{
				boost::shared_ptr<source> s = dynamic_pointer_cast<source>(*it);
				if ( s ) found = found || s->has_inputs();
			}
		} else {
			cerr << "invalid source poset class at position " 
				 << it->first << endl;
		}
	}
	return found;
}

boost::shared_ptr<list<event_t> > source_multiplexer::next_inputs()
{
	boost::shared_ptr<list<event_t> > r;
	// pick a random stream until we find one that's not done,
	// and process its frame.
	while ( !current || remaining <= 0 ) {

		if ( inputs.order() < current_order ) {
			if(inputs.order() <= 0){ return r; }
			cerr << "non-monotonic source ordering "
				 << inputs.order() << " vs " << current_order << endl;
			break;
		}

		current_order = inputs.order();
		dynamic_poset::iterator it = inputs.find(current_order);
		if ( it->second && (it->second->size() > 0) ) {
			size_t id = (size_t) (it->second->size() * 
								  (rand() / (RAND_MAX + 1.0)));
			dynamic_poset::pset::iterator c_it = it->second->begin();
			advance(c_it, id);
			boost::shared_ptr<source> c = dynamic_pointer_cast<source>(*c_it);
			if ( !c || (c && !c->has_inputs()) ) {
				it->second->erase(c_it);
			} else {
				current = c;
				remaining = (int) (step > 0 ? 
								   step : 
								   block*(rand() / (RAND_MAX + 1.0)));
			}
		} else {
			cerr << "invalid poset class at position " << it->first << endl;
		}
	}

	if ( !current ) return r;

	r = current->next_inputs();

	if ( r ) remaining -= r->size();
	// cerr << "Preparing to reorder multiplexer elements for " 
	//      << current_order << endl;
	inputs.reorder_elements(current_order);
	// cerr << "Done reordering multiplexer elements for " 
	//      << current_order << "; order is now " 
	//      << inputs.order() << endl;

	// remove the stream if its done.
	if ( !current->has_inputs() ) {
		remove_source(current);
		current = boost::shared_ptr<source>();
		remaining = 0;
		if( runtime_options::verbose() )
			cerr << "done with stream, " << inputs.size() 
				 << " remain" << endl;
	} 
	else if (current_order != current->order()) {
		current = boost::shared_ptr<source>();
		remaining = 0;
	}
	return r;
}


/******************************************************************************
	stream_registry
******************************************************************************/
void stream_registry::register_adaptor( string source_name, 
									    boost::shared_ptr<stream_adaptor> a) 
{
	source_adaptors[source_name].push_back(a);
}

void stream_registry::register_source(string name, boost::shared_ptr<source> src) {
	if (data_sources.find(name) != data_sources.end()) {
		cerr << "Re-registering source \"" << name << "\"" << endl;
	}
	data_sources[name] = src;
	if ( multiplexer ) { multiplexer->add_source(src); }
}

boost::shared_ptr<dbt_file_source> stream_registry::initialize_file_source(
		string stream_name, string file_name, frame_descriptor& f)
{
	boost::shared_ptr<dbt_file_source> s;
	if ( source_adaptors.find(stream_name) != source_adaptors.end() ) {
		s = boost::shared_ptr<dbt_file_source>(new dbt_file_source(
				stream_name, f, source_adaptors[stream_name]));
		register_source(stream_name, s);
	}
	return s;
}

void stream_registry::register_multiplexer(boost::shared_ptr<source_multiplexer> m) {
	multiplexer = m;
	if ( data_sources.size() > 0 ) {
		map<string, boost::shared_ptr<source> >::iterator src_it =
				data_sources.begin();
		for (; src_it != data_sources.end(); ++src_it) {
			multiplexer->add_source(src_it->second);
		}
	}
}


}

}
