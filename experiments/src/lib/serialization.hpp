/*
 * iprogram.hpp
 *
 *  Created on: May 8, 2012
 *      Author: daniel
 */

#ifndef DBTOASTER_SERIALIZATION_HPP
#define DBTOASTER_SERIALIZATION_HPP

#include <iostream>
#include <iomanip>
#include "types.hpp"

#define DBT_SERIALIZATION_NVP_OF_PTR(ar, name)  dbtoaster::serialize_nvp(ar, std::string(name), *name)
#define DBT_SERIALIZATION_NVP(ar, name)  dbtoaster::serialize_nvp(ar, std::string(name), name)

namespace dbtoaster {

    template <typename T, typename Archive>
    inline Archive & serialize(Archive & ar, const unsigned int version, const T & t)
    {
        t.serialize(ar, version);
        ar << "\n";
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize(Archive & ar, const unsigned int version, const int & t)
    {
        ar << t;
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize(Archive & ar, const unsigned int version, const size_t & t)
    {
        ar << t;
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize(Archive & ar, const unsigned int version, const long & t)
    {
        ar << t;
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize(Archive & ar, const unsigned int version, const STRING_TYPE & t)
    {
        ar << t.c_str();
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize(Archive & ar, const unsigned int version, const double & t)
    {
        ar << std::setprecision(15) << t;
        return ar;
    }

    template <typename T, typename Archive>
    inline Archive & serialize_nvp(Archive & ar, const char * name, const T & t)
    {
        ar << "<"  << name << ">";
        serialize(ar, 0, t);
        ar << "</" << name << ">";
        return ar;
    }

    template <typename T, typename Archive>
    inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const T & t, const char* tab)
    {
        ar << tab << "<"  << name << ">";
        serialize(ar, 0, t);
        ar << tab << "</" << name << ">";
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const int & t, const char* tab)
    {
        ar << tab << "<"  << name << ">";
        serialize(ar, 0, t);
        ar << "</" << name << ">";
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const size_t & t, const char* tab)
    {
        ar << tab << "<"  << name << ">";
        serialize(ar, 0, t);
        ar << "</" << name << ">";
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const long & t, const char* tab)
    {
        ar << tab << "<"  << name << ">";
        serialize(ar, 0, t);
        ar << "</" << name << ">";
        return ar;
    }

    template <typename Archive>
    inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const STRING_TYPE & t, const char* tab)
    {
        ar << tab << "<"  << name << ">";
        serialize(ar, 0, t);
        ar << "</" << name << ">";
        return ar;
    }
    
    template<class Archive>
    inline Archive & serialize_nvp_tabbed(Archive & ar, const char * name, const double & t, const char* tab)
    {
        ar << tab << "<"  << name << ">";
        serialize(ar, 0, t);
        ar << "</" << name << ">";
        return ar;
    }

    template <typename T>
    inline void write(std::ostream& o, const T& t) 
    { 
        o.write((char*) &t, sizeof(T));
    }
    
    template<>
    inline void write(std::ostream& o, const STRING_TYPE& t) 
    { 
        size_t length = t.size();
        o.write((char*) &length, sizeof(size_t));
        o.write((char*) t.c_str(), sizeof(char) * length);
    }

    template <typename T>
    inline void read(std::istream& i, T& t)
    {
        i.read((char*) &t, sizeof(T));
    }

    template <>
    inline void read(std::istream& i, STRING_TYPE& t)
    {
        size_t length;
        i.read((char*) &length, sizeof(size_t));
        char* str = new char[length + 1];
        i.read((char*) str, sizeof(char) * length);
        str[length] = 0;
        t = STRING_TYPE(str, length);
        delete[] str;
    }      
}

#endif /* DBTOASTER_SERIALIZATION_HPP */
