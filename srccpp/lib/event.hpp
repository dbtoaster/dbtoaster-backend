/*
 * event.hpp
 *
 *  Created on: May 8, 2012
 *      Author: daniel
 */

#ifndef DBTOASTER_EVENT_H
#define DBTOASTER_EVENT_H

#include <string>
#include <vector>

#include <boost/any.hpp>

namespace dbtoaster {

typedef long date;

/**
 * Type definitions of data-structures used for representing events.
 */

enum event_type { delete_tuple=0, insert_tuple, system_ready_event };
typedef int relation_id_t;
typedef std::vector<boost::any> event_args_t;

extern std::string event_name[];

/**
 * Data-structure used for representing a event consisting of: event type,
 * relation identifier corresponding to the stream/table it relates to and
 * finally, the tuple associated with event.
 */
struct event_t
{
    event_type type;
    relation_id_t id;
    event_args_t data;

    event_t(event_type t, relation_id_t i, event_args_t& d)
    : type(t), id(i), data(d)
    {}
};


}

#endif /* DBTOASTER_DBT_EVENT_H */
