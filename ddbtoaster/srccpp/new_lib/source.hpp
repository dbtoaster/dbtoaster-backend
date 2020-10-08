#ifndef DBTOASTER_SOURCE_HPP
#define DBTOASTER_SOURCE_HPP

#include <limits>
#include <string>
#include <map>

using namespace std;

namespace dbtoaster {

typedef uint32_t SourceId;

constexpr SourceId kInvalidSourceId = std::numeric_limits<SourceId>::max();

enum class SourceType {
  kTable = 0,
  kStream 
};

struct Source {
  Source(SourceId id_, string name_, SourceType type_)
    : id(id_), name(name_), type(type_) { }

  bool isTable() const { return type == SourceType::kTable; }

  SourceId id;
  string name;
  SourceType type;
};

struct FileSource : Source {
  FileSource(SourceId sid, string name, SourceType tp, 
             string path, bool bin = false)
    : Source(sid, name, tp), filename(path), binary(bin) { }

  string filename;
  bool binary;
};

struct SourceFormat {
  SourceFormat(string name_, map<string, string> params_)
      : name(name_), params(params_) { }

  string name;
  map<string, string> params;
};

}

#endif /* DBTOASTER_SOURCE_HPP */