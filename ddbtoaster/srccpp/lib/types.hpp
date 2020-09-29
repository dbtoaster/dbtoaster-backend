#ifndef DBTOASTER_TYPES_H
#define DBTOASTER_TYPES_H

#include <cstdint>
#include <string>

#include "hpds/pstring.hpp"
#include "hpds/pstringops.hpp"
#include "hpds/KDouble.hpp"

#include "date.hpp"

namespace dbtoaster {
    // typedef int date;

    typedef DateType date;

    typedef double DOUBLE_TYPE;

    typedef size_t HASH_RES_t;

    // typedef PString STRING_TYPE;

    typedef std::string STRING_TYPE;
}

#endif /* DBTOASTER_TYPES_HPP */