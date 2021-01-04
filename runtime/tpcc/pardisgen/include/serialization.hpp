/*
 * iprogram.hpp
 *
 *  Created on: May 8, 2012
 *      Author: daniel
 */

#ifndef DBTOASTER_SERIALIZATION_H
#define DBTOASTER_SERIALIZATION_H

#include "hpds/pstring.hpp"
#include "hpds/KDouble.hpp"
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
inline Archive & serialize(Archive & ar, const T & t){
    t.serialize(ar);
    ar << "\n";
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const long & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const int & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const size_t & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const char & t){
    ar << t;
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const STRING_TYPE & t){
    ar << t.c_str();
    return ar;
}

// template<class Archive>
// inline Archive & serialize(Archive & ar, const DateType & t){
//     ar << 10000 * t.getYear() + 100 * t.getMonth() + t.getDay();
//     return ar;
// }

template<typename T, class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const T & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << tab << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const long & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const int & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const size_t & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const STRING_TYPE & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const float & t){
    ar << std::setprecision(15) << t;
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const float & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}


#if DOUBLE_TYPE_SYM == DOUBLE_TYPE_KAHAN_DOUBLE

template<class Archive>
inline Archive & serialize(Archive & ar, const KDouble & t){
    ar << std::setprecision(15) << t;
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const KDouble & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

#elif DOUBLE_TYPE_SYM == DOUBLE_TYPE_BOOST

template<class Archive>
inline Archive & serialize(Archive & ar, const cpp_dec_float_1000 & t){
    ar << std::setprecision(15) << t;
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const boost::multiprecision::cpp_dec_float_100 & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

#elif DOUBLE_TYPE_SYM == DOUBLE_TYPE_STD_LONG_DOUBLE

template<class Archive>
inline Archive & serialize(Archive & ar, const long double & t){
    ar << std::setprecision(15) << t;
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const long double & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

#else

template<class Archive>
inline Archive & serialize(Archive & ar, const double & t){
    ar << std::setprecision(15) << t;
    return ar;
}

template<class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const double & t, const char* tab){
    ar << tab << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

#endif

template<typename T, class Archive>
inline Archive & serialize_nvp(Archive & ar, const char * name, const T & t){
    ar << "<"  << name << ">";
    serialize(ar, t);
    ar << "</" << name << ">";
    return ar;
}

}

#endif /* DBTOASTER_SERIALIZATION_H */
