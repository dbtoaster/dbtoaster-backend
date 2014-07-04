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

#include "pstring.hpp"
#include "../smhasher/MurmurHash2.hpp"

CharPool<> PString::pool_;

//global operators
bool operator==(const PString &str1, const PString &str2)
{
  if (str1.size_ != str2.size_)
  {
    return false;
  }
  char *tmp1 = str1.data_;
  char *tmp2 = str2.data_;
  while (*tmp1 != 0)
  {
    if (*tmp1 != *tmp2)
    {
      return false;
    }
    ++tmp1;
    ++tmp2;
  }
  return true;
}

bool operator==(const PString &str1, const char *str2)
{
  size_t size = strlen(str2) + 1;
  if (str1.size_ != size)
  {
    return false;
  }
  char *tmp = str1.data_;
  while (*tmp != 0)
  {
    if (*tmp != *str2)
    {
      return false;
    }
    ++tmp;
    ++str2;
  }
  return true;
}

bool operator==(const char *str1, const PString &str2)
{
  size_t size = strlen(str1) + 1;
  if (str2.size_ != size)
  {
    return false;
  }
  char *tmp = str2.data_;
  while (*tmp != 0)
  {
    if (*tmp != *str1)
    {
      return false;
    }
    ++tmp;
    ++str1;
  }
  return true;
}

bool operator!=(const PString &str1, const PString &str2)
{
  return !(str1 == str2);
}

bool operator!=(const PString &str1, const char *str2)
{
  return !(str1 == str2);
}

bool operator!=(const char *str1, const PString &str2)
{
  return !(str1 == str2);
}

std::ostream& operator<< (std::ostream& o, PString const& str)
{
  return o << str.data_;
}

size_t hash_value(PString const& str)
{
    return MurmurHash2(str.data_,(str.size_-1)*sizeof(char),0);
}
