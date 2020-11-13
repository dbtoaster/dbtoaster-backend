#include "pstring.hpp"


inline bool operator==(const char *str1, const PString &str2)
{
  return (strcmp(str1, str2.c_str()) == 0);
}

inline bool operator!=(const char *str1, const PString &str2)
{
  return (strcmp(str1, str2.c_str()) != 0);
}

std::ostream& operator<< (std::ostream& o, PString const& str);

FORCE_INLINE size_t hash_value(PString const& str)
{
    return MurmurHash2(str.c_str(), str.length() * sizeof(char), 0);
}