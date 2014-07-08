#include "pstring.hpp"

//global operators
CharPool<> PString::pool_;

inline bool operator==(const char *str1, const PString &str2)
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

inline bool operator!=(const char *str1, const PString &str2)
{
  return !(str1 == str2);
}

std::ostream& operator<< (std::ostream& o, PString const& str)
{
  return o << str.data_;
}

FORCE_INLINE size_t hash_value(PString const& str)
{
    return MurmurHash2(str.data_,(str.size_-1)*sizeof(char),0);
}