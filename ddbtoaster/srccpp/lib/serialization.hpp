#ifndef DBTOASTER_SERIALIZATION_H
#define DBTOASTER_SERIALIZATION_H

#include <iomanip>
#include <type_traits>
#include <string>
#include "macro.hpp"
#include "date_type.hpp"
#include "rings/numeric_ring.hpp"

namespace dbtoaster {

namespace serialization {

constexpr const char* kElemSeparator = "\n\t\t\t";

template<class Output, class T, class Enable = void>
struct XmlSerializer {
  void operator()(Output& out, const T& t) {
    t.serialize(out);
  }

  void operator()(Output& out, const T& t, const char* name, const char* tab) {
    out << tab << "<" << name << ">";
    this->operator()(out, t);
    out << '\n' << tab << "</" << name << ">";
  }
}; // primary template

template<class Output, class T>
struct XmlSerializer<Output, T, typename std::enable_if<std::is_integral<T>::value>::type> {
  void operator()(Output& out, const T& t) {
    out << t;
  }

  void operator()(Output& out, const T& t, const char* name, const char* tab) {
    out << tab << "<" << name << ">";
    this->operator()(out, t);
    out << "</" << name << ">";
  }  
}; // specialization for integral types

template<class Output, class T>
struct XmlSerializer<Output, T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
  void operator()(Output& out, const T& t) {
    out << std::setprecision(15) << t;
  }

  void operator()(Output& out, const T& t, const char* name, const char* tab) {
    out << tab << "<" << name << ">";
    this->operator()(out, t);
    out << "</" << name << ">";
  }
}; // specialization for floating-point types

template<class Output>
struct XmlSerializer<Output, std::string> {
  void operator()(Output& out, const std::string& t) {
    out << t.c_str();
  }

  void operator()(Output& out, const std::string& t, const char* name, const char* tab) {
    out << tab << "<" << name << ">";
    this->operator()(out, t);
    out << "</" << name << ">";
  }
}; // specialization for string type

template<class Output>
struct XmlSerializer<Output, DateType> {
  void operator()(Output& out, const DateType& t) {
    out << 10000 * t.getYear() + 100 * t.getMonth() + t.getDay();
  }

  void operator()(Output& out, const DateType& t, const char* name, const char* tab) {
    out << tab << "<" << name << ">";
    this->operator()(out, t);
    out << "</" << name << ">";
  }
}; // specialization for date type

template<class Output, class T>
struct XmlSerializer<Output, T, typename std::enable_if<std::is_base_of<dbtoaster::standard_rings::NumericRing, T>::value>::type> {
  void operator()(Output& out, const T& t) {
    out << t.result();
  }

  void operator()(Output& out, const T& t, const char* name, const char* tab) {
    out << tab << "<" << name << ">";
    this->operator()(out, t);
    out << "</" << name << ">";
  }
}; // specialization for numeric struct

template<class Output, class T>
void serialize(Output& s, const T& t) {
  XmlSerializer<Output, T>{}(s, t);
}

template<class Output, class T>
void serialize(Output& s, const T& t, const char* name, const char* tab = "") {
  XmlSerializer<Output, T>{}(s, t, name, tab);
}

}

}
#endif /* DBTOASTER_SERIALIZATION_H */
