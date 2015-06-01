#include <stdio.h>
#include <string.h>
#include <iostream>
#include <functional>
#include "hashmap/sparse_hash_map"

using namespace std;
using std::tr1::hash;
using dbtoaster::sparse_hash_map;      // namespace where class lives by default

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
      if (s1 && s2)
          return strcmp(s1, s2) == 0;
      else
          return s1 == NULL && s2 == NULL;
  }
};

int main()
{
  sparse_hash_map<const char*, int, hash<const char*>, eqstr> months;
  
  // months.set_empty_key(NULL);
  months["january"] = 31;
  months["february"] = 28;
  months["march"] = 31;
  months["april"] = 30;
  months["may"] = 31;
  months["june"] = 30;
  months["july"] = 31;
  months["august"] = 31;
  months["september"] = 30;
  months["october"] = 31;
  months["november"] = 30;
  months["december"] = 31;
  
  cout << "february  -> " << months["february"] << endl;
  cout << "april     -> " << months["april"] << endl;
  cout << "july      -> " << months["july"] << endl;
  cout << "november  -> " << months["november"] << endl;

  return 0;
}