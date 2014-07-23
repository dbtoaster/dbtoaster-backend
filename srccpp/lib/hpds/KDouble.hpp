// The MIT License (MIT)

// Copyright (c) 2014 Mohammad Dashti
// (www.mdashti.com - mohammad.dashti [at] epfl [dot] ch - mdashti [at] gmail [dot] com)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef KDOUBLE_H
#define KDOUBLE_H
#include <cmath>
#include <iostream>

#ifndef DOUBLE_TYPE
#define DOUBLE_TYPE double
#endif //DOUBLE_TYPE

namespace dbtoaster {

class KDouble
{
private:
  double sum;
  double c;

protected:
  //friends
  friend bool operator==(const double, const KDouble &);
  friend bool operator!=(const double, const KDouble &);
  friend bool operator<(const double, const KDouble &);
  friend bool operator<=(const double, const KDouble &);
  friend bool operator>(const double, const KDouble &);
  friend bool operator>=(const double, const KDouble &);
  // friend size_t hash_value(KDouble const &v);
  template <class T>
  friend void hash_combine(std::size_t& seed, const T& v);
  friend KDouble abs(const KDouble &dbl);

public:
  static double diff_p;
  KDouble() : sum(0.0), c(0.0)
  {
  }

  KDouble(const KDouble &init) : sum(init.sum), c(init.c)
  {
  }

  KDouble(const double &init) : sum(init), c(0.0)
  {
  }

  ~KDouble()
  {
  }

  inline KDouble &operator=(const KDouble &other) { sum = other.sum; c = other.c; return *this; }
  inline KDouble &operator=(const double &other) { sum = other; c = 0.0; return *this; }
  inline KDouble &operator-=(const KDouble &other) {
    double y = -other.sum-c;
    double t = sum+y;
    c = static_cast<double>(t-sum)-y;
    sum = t;
    return *this;
  }
  inline KDouble &operator-=(const double &other) {
    double y = -other-c;
    double t = sum+y;
    c = static_cast<double>(t-sum)-y;
    sum = t;
    return *this;
  }
  inline KDouble &operator+=(const KDouble &other) {
    double y = other.sum-c;
    double t = sum+y;
    c = static_cast<double>(t-sum)-y;
    sum = t;
    return *this;
  }
  inline KDouble &operator+=(const double &other) {
    double y = other-c;
    double t = sum+y;
    c = static_cast<double>(t-sum)-y;
    sum = t;
    return *this;
  }

  //TODO Is this the right implementation?
  inline KDouble &operator*=(const KDouble &other) { sum *= other.sum; c *= other.sum; return *this; }
  inline KDouble &operator*=(const double &other) { sum *= other; c *= other; return *this; }
  inline KDouble &operator/=(const KDouble &other) { sum /= other.sum; c /= other.sum; return *this; }
  inline KDouble &operator/=(const double &other) { sum /= other; c /= other; return *this; }

  friend std::ostream &operator<<(std::ostream &out, const KDouble &kd) {
      return out << kd.sum;
  }

  //inline operator double() const { return sum; }
  // operator int() const { return static_cast<int>(sum); }
  // operator long() const { return static_cast<long>(sum); }

  inline bool operator==(const KDouble &other) const
  {
    return abs(sum-other.sum) < diff_p;
  }

  inline bool operator!=(const KDouble &other) const
  {
    return abs(sum-other.sum) >= diff_p;
  }

  // inline bool operator==(const double &other)
  // {
  //   return abs(sum-other) < diff_p;
  // }

  // inline bool operator!=(const double &other)
  // {
  //   return abs(sum-other) >= diff_p;
  // }

  inline bool operator<(const KDouble &other) const
  {
    return sum < other.sum;
  }

  inline bool operator<=(const KDouble &other) const
  {
    return sum <= other.sum;
  }

  inline bool operator>(const KDouble &other) const
  {
    return sum > other.sum;
  }

  inline bool operator>=(const KDouble &other) const
  {
    return sum >= other.sum;
  }
};

inline bool operator==(const double sum, const KDouble & other)
{
  return abs(sum-other.sum) < KDouble::diff_p;
}
inline bool operator!=(const double sum, const KDouble & other)
{
  return abs(sum-other.sum) >= KDouble::diff_p;
}

inline bool operator<(const double sum, const KDouble &other)
{
  return sum < other.sum;
}

inline bool operator<=(const double sum, const KDouble &other)
{
  return sum <= other.sum;
}

inline bool operator>(const double sum, const KDouble &other)
{
  return sum > other.sum;
}

inline bool operator>=(const double sum, const KDouble &other)
{
  return sum >= other.sum;
}

inline KDouble operator-(const KDouble &g1, const KDouble &g2)
{
    KDouble result(g1);
    result -= g2;
    return result;
}

inline KDouble operator+(const KDouble &g1, const KDouble &g2)
{
    KDouble result(g1);
    result += g2;
    return result;
}

inline KDouble operator*(const KDouble &g1, const KDouble &g2)
{
    KDouble result(g1);
    result *= g2;
    return result;
}

inline KDouble operator/(const KDouble &g1, const KDouble &g2)
{
    KDouble result(g1);
    result /= g2;
    return result;
}

inline KDouble operator-(const double &g1, const KDouble &g2)
{
    KDouble result(g1);
    result -= g2;
    return result;
}

inline KDouble operator+(const double &g1, const KDouble &g2)
{
    KDouble result(g1);
    result += g2;
    return result;
}

inline KDouble operator/(const double &g1, const KDouble &g2)
{
    KDouble result(g1);
    result /= g2;
    return result;
}

inline KDouble operator-(const long &g1, const KDouble &g2)
{
    KDouble result(g1);
    result -= g2;
    return result;
}

inline KDouble operator+(const long &g1, const KDouble &g2)
{
    KDouble result(g1);
    result += g2;
    return result;
}

inline KDouble operator/(const long &g1, const KDouble &g2)
{
    KDouble result(g1);
    result /= g2;
    return result;
}

inline KDouble operator-(const int &g1, const KDouble &g2)
{
    KDouble result(g1);
    result -= g2;
    return result;
}

inline KDouble operator+(const int &g1, const KDouble &g2)
{
    KDouble result(g1);
    result += g2;
    return result;
}

inline KDouble operator*(const int &g1, const KDouble &g2)
{
    KDouble result(g1);
    result *= g2;
    return result;
}

inline KDouble operator/(const int &g1, const KDouble &g2)
{
    KDouble result(g1);
    result /= g2;
    return result;
}

inline KDouble operator-(const KDouble &g1, const double &g2)
{
    KDouble result(g1);
    result -= g2;
    return result;
}

inline KDouble operator+(const KDouble &g1, const double &g2)
{
    KDouble result(g1);
    result += g2;
    return result;
}

inline KDouble operator*(const KDouble &g1, const double &g2)
{
    KDouble result(g1);
    result *= g2;
    return result;
}

inline KDouble operator/(const KDouble &g1, const double &g2)
{
    KDouble result(g1);
    result /= g2;
    return result;
}

inline KDouble operator-(const KDouble &g1, const long &g2)
{
    KDouble result(g1);
    result -= g2;
    return result;
}

inline KDouble operator+(const KDouble &g1, const long &g2)
{
    KDouble result(g1);
    result += g2;
    return result;
}

inline KDouble operator*(const KDouble &g1, const long &g2)
{
    KDouble result(g1);
    result *= g2;
    return result;
}

inline KDouble operator/(const KDouble &g1, const long &g2)
{
    KDouble result(g1);
    result /= g2;
    return result;
}

inline KDouble operator-(const KDouble &g1, const int &g2)
{
    KDouble result(g1);
    result -= g2;
    return result;
}

inline KDouble operator+(const KDouble &g1, const int &g2)
{
    KDouble result(g1);
    result += g2;
    return result;
}

inline KDouble operator*(const KDouble &g1, const int &g2)
{
    KDouble result(g1);
    result *= g2;
    return result;
}

inline KDouble operator/(const KDouble &g1, const int &g2)
{
    KDouble result(g1);
    result /= g2;
    return result;
}

inline KDouble abs(const KDouble &dbl)
{
    KDouble result(dbl);
    if(result.sum < 0.0) result.sum = -result.sum;
    return result;
}

}
#endif //KDOUBLE_H