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
	source
******************************************************************************/
source::source(frame_descriptor& f, shared_ptr<stream_adaptor> a) : frame_info(f), adaptor(a) {
}

/******************************************************************************
	dbt_file_source
******************************************************************************/
dbt_file_source::dbt_file_source(
		const std::string& path, frame_descriptor& f, shared_ptr<stream_adaptor> a): source(f,a)
{
	if ( boost::filesystem::exists( path ) )
	{
		source_stream = boost::shared_ptr<file_stream>(new file_stream(path.c_str(), file_stream::in));
		if( runtime_options::verbose() )
			cerr << "reading from " << path
				 << " with 1 adaptors" << endl;
	}
	else
		cerr << "File not found: " << path << endl;
	// buffer = boost::shared_ptr<std::string>(new std::string());
}

void dbt_file_source::read_source_events(shared_ptr<list<event_t> > eventList, shared_ptr<priority_queue<event_t, deque<event_t>, event_timestamp_order> > eventQue) {
	//read the whole file
	// string buffer;
	source_stream->seekg(0, std::ios::end);
	size_t bufferLength = source_stream->tellg();
	char* buffer = new char[bufferLength+1];
	char* buffer_end = buffer + bufferLength;
	source_stream->seekg(0, std::ios::beg);
	source_stream->read(buffer,bufferLength);
	source_stream->close();

	char* start_event_pos = buffer;
	char* end_event_pos = buffer;
	if (frame_info.type == fixed_size) {
		size_t frame_size = frame_info.size;
		char tmp;
		for(; start_event_pos != buffer_end; start_event_pos = end_event_pos) {
			end_event_pos = start_event_pos+frame_size;
			tmp = *end_event_pos;
			*end_event_pos = '\0';
			adaptor->read_adaptor_events(start_event_pos,eventList,eventQue);
			*end_event_pos = tmp;
		}
		// std::string::iterator buffer_end = buffer->end();
		// for(std::string::iterator buffer_it = buffer->begin();
		// 	buffer_it != buffer_end;
		// 	buffer_it += frame_info.size) {
		// 	std::string event_str(buffer_it,buffer_it+frame_info.size);
		// 	adaptor->read_adaptor_events(event_str,eventList,eventQue);
		// }
	}
	else if ( frame_info.type == delimited ) {
		const char* delim = frame_info.delimiter.c_str();
		size_t delim_size = frame_info.delimiter.size();
		while(start_event_pos) {
			end_event_pos = strstr(start_event_pos, delim);
			if(!end_event_pos || end_event_pos == buffer_end) break;
			*end_event_pos = '\0';
			// cerr << "processing " << start_event_pos << endl;
			adaptor->read_adaptor_events(start_event_pos,eventList,eventQue);
			start_event_pos = end_event_pos + delim_size;
		}
		// split_iterator<std::string::const_iterator> events_end;
		// for (split_iterator<std::string::const_iterator> event_it =
		// 		make_split_iterator((*buffer), first_finder(frame_info.delimiter, is_equal()));
		// 	 event_it != events_end;
		// 	 ++event_it)
		// {
		// 	std::string event_str = copy_range<std::string>(*event_it);
		// 	adaptor->read_adaptor_events(event_str,eventList,eventQue);
		// }

	}
	else if ( frame_info.type == variable_size ) {
		cerr << "variable size frames not supported" << endl;
	}
	else {
		cerr << "invalid frame type" << endl;
	}
	delete[] buffer;
}
// bool dbt_file_source::has_frame() {
// 	bool r = false;
// 	if ( frame_info.type == fixed_size ) {
// 		r = buffer && (buffer->size()-bufferPos) > frame_info.size;
// 	} else if ( frame_info.type == delimited ) {
// 		r = buffer && (buffer->find(frame_info.delimiter, bufferPos) != string::npos);
// 	}
// 	return r;
// }

// boost::shared_ptr<string> dbt_file_source::frame_from_buffer() {
// 	boost::shared_ptr<string> r;
// 	if (frame_info.type == fixed_size) {
// 		r = boost::shared_ptr<string>(
// 				new string(buffer->substr(bufferPos,frame_info.size)));
// 		bufferPos += frame_info.size;
// 		// buffer = boost::shared_ptr<string>(
// 		// 		new string(buffer->substr(frame_info.size, string::npos)));
// 	} else if ( frame_info.type == delimited ) {
// 		size_t delim_pos = buffer->find(frame_info.delimiter,bufferPos);
// 		r = boost::shared_ptr<string>(new string(buffer->substr(bufferPos, delim_pos)));
// 		bufferPos = delim_pos+frame_info.delimiter.size();
// 		// buffer = boost::shared_ptr<string>(
// 		// 		new string(buffer->substr(
// 		// 				delim_pos+frame_info.delimiter.size(),
// 		// 				string::npos)));
// 	}
// 	return r;
// }

// boost::shared_ptr<string> dbt_file_source::next_frame() {
// 	boost::shared_ptr<string> r;

// 	int frmSize = ((frame_info.size<102400) ? (frame_info.size > 0 ? frame_info.size * 100 : 102400) : frame_info.size);
// 	char buf[frmSize];

// 	if (frame_info.type == fixed_size) {
// 		while ( source_stream->good() && !has_frame() ) {
// 			source_stream->read(buf, frame_info.size);
// 			(*buffer) += string(buf, source_stream->gcount());
// 		}
// 	}
// 	else if ( frame_info.type == delimited ) {

// 		while ( source_stream->good() && !has_frame() ) {

// 			source_stream->read(buf, sizeof(buf));
// 			(*buffer) += string(buf, source_stream->gcount());
// 		}

// 		if( !source_stream->good() &&
// 				buffer->find(frame_info.delimiter,bufferPos) != 
// 				(buffer->size()-frame_info.delimiter.size()) )
// 			(*buffer) += frame_info.delimiter;


// 		size_t dd_index = bufferPos;
// 		string ddelimiter = frame_info.delimiter+frame_info.delimiter;
// 		while ( (dd_index = buffer->find(ddelimiter,dd_index)) !=
// 				string::npos )
// 			buffer->replace( dd_index, ddelimiter.size(), 
// 							 frame_info.delimiter );

// 	}
// 	else if ( frame_info.type == variable_size ) {
// 		cerr << "variable size frames not supported" << endl;
// 	}
// 	else {
// 		cerr << "invalid frame type" << endl;
// 	}

// 	if ( has_frame() ) r = frame_from_buffer();

// 	return r;
// }

// // Process adaptors in the first stage, accumulating and returning
// // stream events
// void dbt_file_source::process_adaptor(
// 		string& data, boost::shared_ptr<list<event_t> >& r) 
// {
// 	adaptor.process(data, r);
// }

// // Finalize all adaptors, accumulating stream events.
// void dbt_file_source::finalize_adaptor(boost::shared_ptr<list<event_t> >& r) 
// {
// 	adaptor.finalize(r);
// }

// // Get buffered events from all adaptors
// void dbt_file_source::collect_buffered_events(
// 										boost::shared_ptr<list<event_t> >& r) 
// {
// 	adaptor.get_buffered_events(r);
// 	adaptor.current_order = 0;    // mark for removal 
// }


// boost::shared_ptr<list<event_t> > dbt_file_source::next_inputs() {
// 	boost::shared_ptr<list<event_t> > r;

// 	if ( has_frame_inputs() ) {
// 		// get the next frame of data based on the frame type.
// 		boost::shared_ptr<string> data = next_frame();

// 		if ( data ) {
// 			r = boost::shared_ptr<list<event_t> >(new list<event_t>());
// 			process_adaptor(*data, r);
// 		}
// 	} else if ( has_buffered_events() ) {
// 		r = boost::shared_ptr<list<event_t> >(new list<event_t>());
// 		collect_buffered_events(r);
// 	} else if ( source_stream->is_open() ) {
// 		source_stream->close();
// 		r = boost::shared_ptr<list<event_t> >(new list<event_t>());
// 		finalize_adaptor(r);
// 	}

// 	return r;
// }

/******************************************************************************
	source_multiplexer
******************************************************************************/
source_multiplexer::source_multiplexer(int seed, int st)
	: step(st), remaining(0), block(100)
{
	srandom(seed);
	eventList = boost::shared_ptr<list<event_t> >(new list<event_t>());
	eventQue = shared_ptr<priority_queue<event_t, deque<event_t>, event_timestamp_order> >(new priority_queue<event_t, deque<event_t>, event_timestamp_order>());
}

source_multiplexer::source_multiplexer(int seed, int st, 
										set<boost::shared_ptr<source> >& s)
{
	source_multiplexer(seed, st);
	set<boost::shared_ptr<source> >::iterator it = s.begin();
	set<boost::shared_ptr<source> >::iterator end = s.end();
	for(; it != end; ++it) add_source(*it);
}

void source_multiplexer::add_source(boost::shared_ptr<source> s) {
	inputs.push_back(s);
}

void source_multiplexer::remove_source(boost::shared_ptr<source> s) {
	std::vector<shared_ptr<source> >::iterator end = inputs.end();
	for (std::vector<shared_ptr<source> >::iterator it = inputs.begin(); it != end; ++it) {
		if((*it) == s) inputs.erase(it);
	}
}

void source_multiplexer::init_source() {
	std::vector<shared_ptr<source> >::iterator it = inputs.begin();
	std::vector<shared_ptr<source> >::iterator end = inputs.end();
	for (; it != end; ++it) {
		boost::shared_ptr<source> s = (*it);
		if(s) {
			s->init_source();
			s->read_source_events(eventList, eventQue);
		}
	}
}

// void source_multiplexer::process_events(ProgramBase* p, bool process_tabl) {
// 	std::list<event_t>::iterator lst_it = eventList->begin();
// 	std::list<event_t>::iterator lst_end = eventList->end();
// 	for (; lst_it != end; ++lst_it) {
// 		if(process_tabl) {
// 			progBase->process_event(&(*lst_it),process_tabl);
// 		} else {
// 			progBase->process_stream_event(&(*lst_it));
// 		}
// 	}
// 	while (!eventQue->empty())
// 	{
// 		if(process_tabl) {
// 			progBase->process_event(&(eventQue->top()),process_tabl);
// 		} else {
// 			progBase->process_stream_event(&(eventQue->top()));
// 		}
// 		eventQue->pop();
// 	}
// #ifdef DBT_PROFILE
// 	progBase->exec_stats->save_now();
// #endif // DBT_PROFILE
// }

// bool source_multiplexer::has_inputs() {
// 	bool found = false;
// 	std::vector<int>::iterator it = inputs.begin();
// 	std::vector<int>::iterator end = inputs.end();
// 	for (; it != end; ++it) {
// 		boost::shared_ptr<source> s = (*it);
// 		if ( s ) found = found || s->has_inputs();
// 	}
// 	return found;
// }

// boost::shared_ptr<list<event_t> > source_multiplexer::next_inputs()
// {
// 	boost::shared_ptr<list<event_t> > r;
// 	// pick a random stream until we find one that's not done,
// 	// and process its frame.
// 	while ( !current || remaining <= 0 ) {

// 		if ( inputs.order() < current_order ) {
// 			if(inputs.order() <= 0){ return r; }
// 			cerr << "non-monotonic source ordering "
// 				 << inputs.order() << " vs " << current_order << endl;
// 			break;
// 		}

// 		current_order = inputs.order();
// 		dynamic_poset::iterator it = inputs.find(current_order);
// 		if ( it->second && (it->second->size() > 0) ) {
// 			size_t id = (size_t) (it->second->size() * 
// 								  (rand() / (RAND_MAX + 1.0)));
// 			dynamic_poset::pset::iterator c_it = it->second->begin();
// 			advance(c_it, id);
// 			boost::shared_ptr<source> c = dynamic_pointer_cast<source>(*c_it);
// 			if ( !c || (c && !c->has_inputs()) ) {
// 				it->second->erase(c_it);
// 			} else {
// 				current = c;
// 				remaining = (int) (step > 0 ? 
// 								   step : 
// 								   block*(rand() / (RAND_MAX + 1.0)));
// 			}
// 		} else {
// 			cerr << "invalid poset class at position " << it->first << endl;
// 		}
// 	}

// 	if ( !current ) return r;

// 	r = current->next_inputs();

// 	if ( r ) remaining -= r->size();

// 	// remove the stream if its done.
// 	if ( !current->has_inputs() ) {
// 		remove_source(current);
// 		current = boost::shared_ptr<source>();
// 		remaining = 0;
// 		if( runtime_options::verbose() )
// 			cerr << "done with stream, " << inputs.size() 
// 				 << " remain" << endl;
// 	} 
// 	else if (current_order != current->order()) {
// 		current = boost::shared_ptr<source>();
// 		remaining = 0;
// 	}
// 	return r;
// }

}

}
