/*
 * iprogram.hpp
 *
 *  Created on: May 8, 2012
 *      Author: daniel
 */

#ifndef DBTOASTER_SERIALIZATION_H
#define DBTOASTER_SERIALIZATION_H

#include <iostream>
#include <iomanip>

#define DBT_SERIALIZATION_NVP_OF_PTR( ar , name )  \
    dbtoaster::serialize_nvp(ar, STRING(name), *name)

#define DBT_SERIALIZATION_NVP( ar , name )  \
    dbtoaster::serialize_nvp(ar, STRING(name), name)

#define ELEM_SEPARATOR "\n\t\t\t"

namespace dbtoaster {

typedef std::ostream xml_oarchive;

template<typename T, class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const T & t){
    t.serialize(ar, version);
    ar << "\n";
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const long & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const int & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const size_t & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const char & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const STRING_TYPE & t){
    ar << t.c_str();
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const DateType & t){
    ar << 10000 * t.get_year() + 100 * t.get_month() + t.get_day();
    return ar;
}

template<typename T, class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const T & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << tab << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const long & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const int & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const size_t & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const STRING_TYPE & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const float & t){
    ar << std::setprecision(15) << t;
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const float & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << "</" << name << ">";
    return ar;
}


// #if DOUBLE_TYPE_SYM == DOUBLE_TYPE_KAHAN_DOUBLE

// template<class Archive>
// inline Archive & serialize(Archive & ar, const unsigned int version, const KDouble & t){
//     ar << std::setprecision(15) << t;
//     return ar;
// }

// template<class Archive>
// inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const KDouble & t, const char* tab){
//     ar << tab << "<"  << name << ">";
//     serialize(ar, 0, t);
//     ar << "</" << name << ">";
//     return ar;
// }

// #elif DOUBLE_TYPE_SYM == DOUBLE_TYPE_BOOST

// template<class Archive>
// inline Archive & serialize(Archive & ar, const unsigned int version, const cpp_dec_float_1000 & t){
//     ar << std::setprecision(15) << t;
//     return ar;
// }

// template<class Archive>
// inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const boost::multiprecision::cpp_dec_float_100 & t, const char* tab){
//     ar << tab << "<"  << name << ">";
//     serialize(ar, 0, t);
//     ar << "</" << name << ">";
//     return ar;
// }

// #elif DOUBLE_TYPE_SYM == DOUBLE_TYPE_STD_LONG_DOUBLE

// template<class Archive>
// inline Archive & serialize(Archive & ar, const unsigned int version, const long double & t){
//     ar << std::setprecision(15) << t;
//     return ar;
// }

// template<class Archive>
// inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const long double & t, const char* tab){
//     ar << tab << "<"  << name << ">";
//     serialize(ar, 0, t);
//     ar << "</" << name << ">";
//     return ar;
// }

// #else

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const double & t){
    ar << std::setprecision(15) << t;
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const double & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << "</" << name << ">";
    return ar;
}

// #endif

template<typename T, class Archive>
inline Archive & serialize_nvp(Archive & ar, const char * name, const T & t){
    ar << "<"  << name << ">";
    serialize(ar, 0, t);
    ar << "</" << name << ">";
    return ar;
}

}

#endif /* DBTOASTER_SERIALIZATION_H */
