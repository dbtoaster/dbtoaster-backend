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

namespace dbtoaster {

typedef std::ostream xml_oarchive;

template<typename T, class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const T & t){
    t.serialize(ar, version);
    ar << "\n";
    return ar;
}

template<class Archive>
inline Archive & serialize(Archive & ar, const unsigned int version, const double & t){
    ar << std::setprecision(15) << t;
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

template<typename T, class Archive>
inline Archive & serialize_nvp(Archive & ar, const char * name, const T & t){
    ar << "<";
    ar << name;
    ar << ">";
    serialize(ar, 0, t);
    ar << "</";
    ar << name;
    ar << ">";
    return ar;
}

template<typename T, class Archive>
inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const T & t, const char* tab){
    ar << tab << "<";
    ar << name;
    ar << ">";
    serialize(ar, 0, t);
    ar << tab << "</";
    ar << name;
    ar << ">";
    return ar;
}

}

#endif /* DBTOASTER_SERIALIZATION_H */
