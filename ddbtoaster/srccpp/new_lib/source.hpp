#ifndef DBTOASTER_SOURCE_HPP
#define DBTOASTER_SOURCE_HPP

#include <string>

namespace dbtoaster {

struct Source { };

struct FileSource : Source {
  FileSource(std::string t_filename, bool t_binary = false)
    : filename(t_filename), binary(t_binary) { }

  std::string filename;
  bool binary;
};

}

#endif /* DBTOASTER_SOURCE_HPP */