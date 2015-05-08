#include "event.hpp"

namespace dbtoaster {

	std::string event_name[] = {
	    std::string("insert"), 
	    std::string("delete"), 
	    std::string("batch_update"), 
	    std::string("system_ready")
	};
	bool compare_event_timestamp_order (event_t const & p1, event_t const & p2)
	{
	    return p1.event_order < p2.event_order;
	}
}