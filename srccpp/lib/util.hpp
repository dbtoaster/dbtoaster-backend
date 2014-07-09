#ifndef DBTOASTER_UTIL_H
#define DBTOASTER_UTIL_H

#include <cstddef>

namespace dbtoaster {
  namespace util {
    // Misc function object helpers.
    struct fold_hash {
      typedef std::size_t result_type;
      template<class T>
      std::size_t operator()(std::size_t current, const T& arg) {
        hash_combine(current, arg);
        return(current);
      }
    };
  }
  
  template<class T> 
  std::list<T> singleton(T elem) {
    std::list<T> sing;
    sing.push_back(elem);
    return sing;
  }
}

#endif
