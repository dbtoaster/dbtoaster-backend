#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/functional/hash.hpp>

#include "standard_adaptors.hpp"

#include "runtime.hpp"
using namespace ::dbtoaster::runtime;

namespace dbtoaster {
namespace adaptors {

/******************************************************************************
	csv_adaptor
******************************************************************************/

csv_adaptor::csv_adaptor(relation_id_t _id) 
		: id(_id), type(insert_tuple), schema(""), delimiter(",") 
{}

csv_adaptor::csv_adaptor(relation_id_t _id, string sch)
		: id(_id), type(insert_tuple), schema(sch), delimiter(",")
{
	validate_schema();
}

csv_adaptor::csv_adaptor(relation_id_t i, int num_params,
						const pair<string,string> params[])
		: id(i), type(insert_tuple), delimiter(",")
{
	parse_params(num_params,params);
	validate_schema();
}

void csv_adaptor::parse_params(int num_params, 
							   const pair<string, string> params[]) {
	string param_schema = "";
	string param_schema_prefix = "";
	for (int i = 0; i< num_params; ++i) {
	  string k = params[i].first;
	  string v = params[i].second;
	  if( runtime_options::verbose() )
		cerr << "csv params: " << k << ": " << v << endl;

	  if ( k == "delimiter" ) {
		delimiter = v;
	  } else if ( k == "schema" ) {
		param_schema = v;
	  } else if ( k == "eventtype" ) {
		type = ( v == "insert" ? insert_tuple : delete_tuple);
	  } else if ( k == "deletions" ) {
		param_schema_prefix = ( v == "true" ? "order,event," : "" );
	  }
	  // TODO: handle parameterized events, via 'triggers' key as seen
	  // in OCaml adaptors.
	}
	schema = parse_schema(param_schema_prefix + param_schema);
}

string csv_adaptor::parse_schema(string s)
{
	string r = "";
	split_iterator<string::iterator> end;
	for (split_iterator<string::iterator> it =
		 make_split_iterator(s, first_finder(",", is_equal()));
		 it != end; ++it)
	{
	  string ty = copy_range<std::string>(*it);
	  if ( ty == "event" )          r += "e";
	  else if ( ty == "order" )     r += "o";
	  else if ( ty == "int" )       r += "l";
	  else if ( ty == "long" )      r += "l";
	  else if ( ty == "float" )     r += "f";
	  else if ( ty == "double" )    r += "f";
	  else if ( ty == "date" )      r += "d";
	  else if ( ty == "hash" )      r += "h";
	  else if ( ty == "string" )    r += "s";          
	  else {
		cerr << "invalid csv schema type " << ty << endl;
		r = "";
		break;
	  }
	}
	return r;
}

void csv_adaptor::validate_schema() {
	bool valid = true;
	string::iterator it = schema.begin();
	for (; valid && it != schema.end(); ++it) {
	  switch(*it) {
		case 'e':  // event type
		case 'o':  // order field type
		case 'l':
		case 'f':
		case 'd':
		case 'h':
		case 's': break;
		default: valid = false; break;
	  }
	}
	if ( !valid ) schema = "";
}

// Interpret the schema.
tuple<bool, bool, event_args_t> 
csv_adaptor::interpret_event(const string& schema, const string& data)
{
	boost::hash<std::string> field_hash;
	
	event_args_t tuple;
	string::const_iterator schema_it = schema.begin();
	bool valid = true;

	// Default to the adaptor's event type, and override with an event
	// field in the schema.
	bool insert = type == insert_tuple;

	split_iterator<string::const_iterator> field_end;
	for (split_iterator<string::const_iterator> field_it =
			make_split_iterator(data, first_finder(delimiter, is_equal()));
		 valid && schema_it != schema.end() && field_it != field_end;
		 ++schema_it, ++field_it)
	{
	  string field = copy_range<std::string>(*field_it);
	  istringstream iss(field);
	  bool ins; unsigned int o; int y,m,d; double f; long l;
	  vector<string> date_fields;
	  switch (*schema_it) {
		case 'e': iss >> ins; insert = ins; break;
		case 'l': iss >> l; tuple.push_back(l); break;
		case 'f': iss >> f; tuple.push_back(f); break;
		case 'h': tuple.push_back(static_cast<int>(field_hash(field)));
				  break;
		case 'd': 
		  split(date_fields, field, is_any_of("-"));
		  valid = false;
		  if ( date_fields.size() == 3 ) {
			y = atoi(date_fields[0].c_str());
			m = atoi(date_fields[1].c_str());
			d = atoi(date_fields[2].c_str());
			if ( 0 < m && m < 13 && 0 < d && d <= 31) {
			  tuple.push_back(date(y*10000+m*100+d)); valid = true;
			}
		  } 
		  break;
		case 'o':
			iss >> o;
			if ( o < current_order ) {
			  cerr << "invalid adaptor order " << o
				   << " (current " << current_order << ")" << endl;
			} else {
			  current_order = o;
			}
			break;
		case 's': tuple.push_back(field);   break;
		default: valid = false; break;
	  }
	  valid = valid && !iss.fail();
	}
	return make_tuple(valid, insert, tuple);
}

void csv_adaptor::process(const string& data, boost::shared_ptr<list<event_t> > dest)
{
	// Flush any buffered tuple.
	get_buffered_events(dest);

	if ( dest && schema != "" ) {
	  // Interpret the schema.
	  unsigned int order_before = current_order;
	  tuple<bool, bool, event_args_t> evt = interpret_event(schema, data);
	  bool valid = get<0>(evt);
	  bool insert = get<1>(evt);

	  if ( valid )  {
		event_t e(insert? insert_tuple : delete_tuple, id, get<2>(evt));
		// Buffer on change of order.
		if ( current_order > order_before ) {
		  saved_event = boost::shared_ptr<event_t>(new event_t(e));
		} else {
		  dest->push_back(e);
		}
	  } else {
		cerr << "adaptor could not process " << data << endl;
		cerr << "schema: " << schema << endl;
	  }
	} else if ( runtime_options::verbose() ) {
	   cerr << "Skipping event, no "
			<< (schema == ""? "schema" : "buffer") << " found." << endl;
	}
}

void csv_adaptor::finalize(boost::shared_ptr<list<event_t> > dest) { }

bool csv_adaptor::has_buffered_events() {
	return (saved_event ? true : false);
}

void csv_adaptor::get_buffered_events(boost::shared_ptr<list<event_t> > dest) {
	// Flush any buffered tuple.
	if ( saved_event ) {
		dest->push_back(*saved_event);
		saved_event = boost::shared_ptr<event_t>();
	}
}
      

/******************************************************************************
	replay_adaptor
******************************************************************************/
// Replay adaptors are CSV adaptors prepended with an integer denoting the
// event type. The adaptor internally adjusts the schema, allowing it to
// be used with the same parameters as a standard CSV adaptor.

replay_adaptor::replay_adaptor(relation_id_t i) : csv_adaptor(i) {}

replay_adaptor::replay_adaptor(relation_id_t i, string sch) : csv_adaptor(i) {
	type = insert_tuple;
	schema = "e,"+sch;
	validate_schema();
}

replay_adaptor::replay_adaptor(relation_id_t i, int num_params,
							   const pair<string,string> params[])
		: csv_adaptor(i,num_params,params)
{}

string replay_adaptor::parse_schema(string s) {
	return csv_adaptor::parse_schema("event,"+s);
}

}

namespace datasets
{

namespace order_books
{

/******************************************************************************
	order_book_tuple
******************************************************************************/
order_book_tuple::order_book_tuple(const order_book_message& msg) {
	t = msg.t;
	id = msg.id;
	volume = msg.volume;
	price = msg.price;
        broker_id = 0;
}

order_book_tuple& order_book_tuple::operator=(order_book_tuple& other) {
	t = other.t;
	id = other.id;
	broker_id = other.broker_id;
	volume = other.volume;
	price = other.price;
	return *this;
}

void order_book_tuple::operator()(event_args_t& e) {
	if (e.size() > 0) e[0] = t; else e.push_back(t);
	if (e.size() > 1) e[1] = id; else e.push_back(id);
	if (e.size() > 2) e[2] = broker_id; else e.push_back(broker_id);
	if (e.size() > 3) e[3] = volume; else e.push_back(volume);
	if (e.size() > 4) e[4] = price; else e.push_back(price);
}

/******************************************************************************
	order_book_adaptor
******************************************************************************/
order_book_adaptor::order_book_adaptor(
		relation_id_t sid, int nb, order_book_type t)
          : id(sid), num_brokers(nb), type(t)
{
	bids = boost::shared_ptr<order_book>(new order_book());
	asks = boost::shared_ptr<order_book>(new order_book());
	deterministic = false;
	insert_only = false;
}

order_book_adaptor::order_book_adaptor(relation_id_t sid, int num_params,
				   pair<string, string> params[])
{
	id = sid;
	bids = boost::shared_ptr<order_book>(new order_book());
	asks = boost::shared_ptr<order_book>(new order_book());
	deterministic = false;
        insert_only = false;
	num_brokers = 10;
        type = tbids;

	for (int i = 0; i < num_params; ++i) {
		string k = params[i].first;
		string v = params[i].second;
		if( runtime_options::verbose() )
		   cerr << "order book adaptor params: "
				<< params[i].first << ", " << params[i].second << endl;

		if ( k == "book" ) {
		  type = (v == "bids"? tbids : tasks);
		} else if ( k == "brokers" ) {
		  num_brokers = atoi(v.c_str());
		} else if ( k == "validate" ) { // Ignore.
		} else if ( k == "deterministic" ) {
		  deterministic = (v == "yes");
		} else if ( k == "insert-only" ) {
		  insert_only = true;
		} else if ( k == "schema" ) {
		  // simply ignore this parameter since it is hard-coded
		  // it should be always "double,long,long,double,double"
		} else {
		  cerr << "Invalid order book param " << k << ", " << v << endl;
		}
	}
}

bool order_book_adaptor::parse_error(const string& data, int field) {
	cerr << "Invalid field " << field << " message " << data << endl;
	return false;
}

// Expected message format: t, id, action, volume, price
bool order_book_adaptor::parse_message(const string& data, order_book_message& r) {
	string msg = data;
	char* start = &(msg[0]);
	char* end = start;
	char action;

	for (int i = 0; i < 5; ++i)
	{
	  while ( *end && *end != ',' ) ++end;
	  if ( start == end ) { return parse_error(data, i); }
	  if ( *end == '\0' && i != 4 ) { return parse_error(data, i); }
	  *end = '\0';

	  switch (i) {
	  case 0: r.t = atof(start); break;
	  case 1: r.id = atol(start); break;
	  case 2:
		  action = *start;
		  if ( !(action == 'B' || action == 'S' ||
				 action == 'E' || action == 'F' ||
				 action == 'D' || action == 'X' ||
				 action == 'C' || action == 'T') )
		  {
			 return parse_error(data, i);
		  }

		  r.action = action;
		  break;

	  case 3: r.volume = atof(start); break;
	  case 4: r.price = atof(start); break;
	  default: return parse_error(data, i);
	  }

	  start = ++end;
	}
	return true;
}

void order_book_adaptor::process_message(const order_book_message& msg,
					 boost::shared_ptr<list<event_t> > dest)
{
	bool valid = true;
	order_book_tuple r(msg);
	event_type t = insert_tuple;

	if ( msg.action == "B" ) {
	  if (type == tbids || type == both) {
		r.broker_id = (deterministic ? msg.id : rand()) % num_brokers;
		(*bids)[msg.id] = r;
		t = insert_tuple;
	  } else valid = false;
	}
	else if ( msg.action == "S" ) {
	  if (type == tasks || type == both) {
		r.broker_id = (deterministic ? msg.id : rand()) % num_brokers;
		(*asks)[msg.id] = r;
		t = insert_tuple;
	  } else valid = false;
	}

	else if ( msg.action == "E" ) {
	  order_book_tuple x;
	  bool x_valid = true;
	  order_book::iterator bid_it = bids->find(msg.id);
	  if ( bid_it != bids->end() ) {
		x = r = bid_it->second;
		r.volume -= msg.volume;
		if ( r.volume <= 0.0 ) { bids->erase(bid_it); valid = false; }
		else { (*bids)[msg.id] = r; }
	  } else {
		order_book::iterator ask_it = asks->find(msg.id);
		if ( ask_it != asks->end() ) {
		  x = r = ask_it->second;
		  r.volume -= msg.volume;
		  if ( r.volume <= 0.0 ) { asks->erase(ask_it); valid = false; }
		  else { (*asks)[msg.id] = r; }
		} else {
		  //cerr << "unknown order id " << msg.id
		  //     << " (neither bid nor ask)" << endl;
		  valid = false;
		  x_valid = false;
		}
	  }
	  if ( x_valid && !insert_only ) {
		event_args_t fields(5);
		x(fields);
		event_t y(delete_tuple, id, fields);
		dest->push_back(y);
	  }
	  t = insert_tuple;
	}

	else if ( msg.action == "F" )
	{
	  order_book::iterator bid_it = bids->find(msg.id);
	  if ( bid_it != bids->end() ) {
		r = bid_it->second;
		bids->erase(bid_it);
	  } else {
		order_book::iterator ask_it = asks->find(msg.id);
		if ( ask_it != asks->end() ) {
		  r = ask_it->second;
		  asks->erase(ask_it);
		} else {
		  //cerr << "unknown order id " << msg.id
		  //     << " (neither bid nor ask)" << endl;
		  valid = false;
		}
	  }
	  t = delete_tuple;
	}

	else if ( msg.action == "D" )
	{
	  order_book::iterator bid_it = bids->find(msg.id);
	  if ( bid_it != bids->end() ) {
		r = bid_it->second;
		bids->erase(bid_it);
	  } else {
		order_book::iterator ask_it = asks->find(msg.id);
		if ( ask_it != asks->end() ) {
		  r = ask_it->second;
		  asks->erase(ask_it);
		} else {
		  //cerr << "unknown order id " << msg.id
		  //     << " (neither bid nor ask)" << endl;
		  valid = false;
		}
	  }
	  t = delete_tuple;
	}

	/*
	// ignore for now...
	else if ( v->action == "X")
	else if ( v->action == "C")
	else if ( v->action == "T")
	*/
	else { valid = false; }


	if ( valid ) {
	  event_args_t fields(5);
	  r(fields);
	  if ( !(t == delete_tuple && insert_only) ) {
		event_t e(t, id, fields);
		dest->push_back(e);
	  }
	}
}

void order_book_adaptor::process(const string& data, boost::shared_ptr<list<event_t> > dest)
{
	// Grab a message from the data.
	order_book_message r;
	bool valid = parse_message(data, r);
	  
	if ( valid ) {
	  // Process its action, updating the internal book.
	  process_message(r, dest);
	}
}

		
/******************************************************************************
	order_book_streams
******************************************************************************/

order_book_streams::order_book_streams(string file_name, string params,
				   boost::shared_ptr<source_multiplexer> m)
  : r(m), sid(0), data_file(file_name)
{
	init(parse_params(params));
}

vector<order_book_streams::stream_params> order_book_streams::parse_params(
			string params) 
{
	vector<order_book_streams::stream_params> r;
	boost::shared_ptr<order_book_streams::stream_params> current;

	vector<string> tmp; split(tmp, params, is_any_of(","));
	for (vector<string>::iterator it = tmp.begin(); 
	   it != tmp.end(); ++it) {
		string p = *it;
		vector<string> p_parts; split(p_parts, p, is_any_of(":"));
		if ( p_parts.size() == 2 ) {
		  if ( p_parts[0] == "book" ) {
			if ( current ) r.push_back(*current);
			current = boost::shared_ptr<order_book_streams::stream_params>(
								new order_book_streams::stream_params());
			to_lower(p_parts[1]);
			current->first = p_parts[1];
			current->second.push_back(make_pair(p_parts[0], p_parts[1]));
		  } else if ( current ){
			current->second.push_back(make_pair(p_parts[0], p_parts[1]));
		  } else {
			cerr << "must declare order book before parameter " 
				 << p << endl;
		  }
		} else {
		  cerr << "invalid order book adaptor parameter " << p << endl;
		}
	}

	return r;
}

void order_book_streams::init(vector<order_book_streams::stream_params> params) {
	if ( !data_file.empty() ) {
		for (int i = 0; i < params.size(); ++i) {
		  order_book_streams::stream_params& p = params[i];
		  frame_descriptor fdesc("\n");
		  boost::shared_ptr<order_book_adaptor> a = boost::shared_ptr<order_book_adaptor>(
			new order_book_adaptor(sid, p.second.size(), &(p.second[0])));
		  if ( a ) {
			r.register_adaptor(p.first, a);
			boost::shared_ptr<source> s = r.initialize_file_source(p.first,
															data_file,
															fdesc);
			if ( s ) {
			  stream_identifiers[p.first] = sid;
			  ++sid;
			} else {
			  cerr << "failed to initialize source for " << p.first << endl;
			}
		  } else {
			cerr << "failed to create adaptor for " << p.first << endl;
		  }
		}
	} else {
		cerr << "No data file specified for order book streams" << endl;
	}
}

int order_book_streams::get_stream_id(string name) {
	int r = -1;
	if ( stream_identifiers.find(name) != stream_identifiers.end() )
		r = stream_identifiers[name];
	return r;
}

}
}
}
