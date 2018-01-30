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
#include <memory>

namespace dbtoaster {

typedef int date;

/**
 * Type definitions of data-structures used for representing events.
 */

enum event_type { 
    delete_tuple = 0, 
    insert_tuple, 
    batch_update, 
    system_ready_event 
};

typedef int relation_id_t;
typedef std::vector<std::shared_ptr<void>> event_args_t;

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
    unsigned int event_order;
    event_args_t data;

    event_t(const event_t& other)
    : type(other.type), id(other.id), event_order(other.event_order), data(other.data)
    {}

    event_t(event_type t, relation_id_t i, unsigned int ord, event_args_t& d)
    : type(t), id(i), event_order(ord), data(d)
    {}
};

bool compare_event_timestamp_order (event_t const & p1, event_t const & p2);

struct event_timestamp_order
{
	bool operator()(event_t const & p1, event_t const & p2) {
        return compare_event_timestamp_order(p1, p2);
    }
};


}

#endif /* DBTOASTER_DBT_EVENT_H */
