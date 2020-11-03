#ifndef DBTOASTER_TYPES_HPP
#define DBTOASTER_TYPES_HPP

#include <string>
#include "date_type.hpp"
#include "map_type.hpp"

namespace dbtoaster {

typedef DateType date;

typedef double DOUBLE_TYPE;

typedef std::size_t HASH_RES_t;

typedef std::string STRING_TYPE;

template<std::size_t Size>
using CStringMap = Map<const char*, const char*, Size>;

}
#endif /* DBTOASTER_TYPES_HPP */