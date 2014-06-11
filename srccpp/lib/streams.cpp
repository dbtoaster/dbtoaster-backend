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
            std::cerr << "event_arg: Unrecognized type in <<: " 
                 << a.type().name() << std::endl;
    } catch (boost::bad_any_cast& bc) {
        std::cerr << "bad cast on <<: " << bc.what() << std::endl;
    }
    return strm;
}

std::ostream& operator<<(std::ostream &strm, const std::vector<boost::any> &args) {
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
			std::cerr << "reading from " << path
				 << " with 1 adaptors" << std::endl;
	}
	else
		std::cerr << "File not found: " << path << std::endl;
}

void dbt_file_source::read_source_events(shared_ptr<std::list<event_t> > eventList, shared_ptr<std::list<event_t> > eventQue) {
	//read the whole file
	source_stream->seekg(0, std::ios::end);
	size_t bufferLength = source_stream->tellg();
	size_t extra_buffer = 0;
	//reserving some buffer for a possible missing delimiter at the end
	if ( frame_info.type == delimited ) {
		extra_buffer = frame_info.delimiter.size();
	}
	char* buffer = new char[bufferLength+1+extra_buffer];
	char* buffer_end = buffer + bufferLength;
	*buffer_end = '\0';
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
	}
	else if ( frame_info.type == delimited ) {
		const char* delim = frame_info.delimiter.c_str();
		size_t delim_size = frame_info.delimiter.size();

		//add delimeter at the end, is it does not exist
		for(size_t delim_idx = 0; delim_idx < delim_size; delim_idx++) {
			if(*(buffer_end-1-delim_idx) != *(delim+delim_size-1)) {
				for(delim_idx = 0; delim_idx < delim_size; delim_idx++) {
					*buffer_end = *(delim+delim_idx);
					buffer_end+=1;
				}
				*buffer_end = '\0';
				break;
			}
		}

		while(start_event_pos) {
			end_event_pos = strstr(start_event_pos, delim);
			if(!end_event_pos || end_event_pos == buffer_end) break;
			*end_event_pos = '\0';
			adaptor->read_adaptor_events(start_event_pos,eventList,eventQue);
			start_event_pos = end_event_pos + delim_size;
		}

	}
	else if ( frame_info.type == variable_size ) {
		std::cerr << "variable size frames not supported" << std::endl;
	}
	else {
		std::cerr << "invalid frame type" << std::endl;
	}
	delete[] buffer;
}
/******************************************************************************
	source_multiplexer
******************************************************************************/
source_multiplexer::source_multiplexer(int seed, int st)
	: step(st), remaining(0), block(100)
{
	srandom(seed);
	eventList = boost::shared_ptr<std::list<event_t> >(new std::list<event_t>());
	eventQue = shared_ptr<std::list<event_t> >(new std::list<event_t>());
}

source_multiplexer::source_multiplexer(int seed, int st, 
										std::set<boost::shared_ptr<source> >& s)
{
	source_multiplexer(seed, st);
	std::set<boost::shared_ptr<source> >::iterator it = s.begin();
	std::set<boost::shared_ptr<source> >::iterator end = s.end();
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

}

}
