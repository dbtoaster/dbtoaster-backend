#include "pstring.hpp"


inline bool operator==(const char *str1, const PString &str2)
{
  return (strcmp(str1,str2.data_) == 0);
}

inline bool operator!=(const char *str1, const PString &str2)
{
  return (strcmp(str1,str2.data_) != 0);
}

std::ostream& operator<< (std::ostream& o, PString const& str)
{
  return o << "\"" << str.data_ << "\"";
}

FORCE_INLINE size_t hash_value(PString const& str)
{
    return MurmurHash2(str.data_,(str.size_-1)*sizeof(char),0);
}