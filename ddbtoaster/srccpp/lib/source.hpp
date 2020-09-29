#ifndef DBTOASTER_SOURCE_HPP
#define DBTOASTER_SOURCE_HPP

namespace dbtoaster {
  template <class... Types> struct Schema { };

  enum class SourceType { kTable = 0, kStream };

  struct Source {
    const char* name;
    const SourceType type;
    constexpr Source(const char* _name, SourceType _type) : name(_name), type(_type) { }
    bool isTable() const { return type == SourceType::kTable; }
  };

  struct FileSource : Source {
    const char* path;
    const bool binary;
    constexpr FileSource(const char* _name, SourceType _type, const char* _path, bool _binary)
      : Source(_name, _type), path(_path), binary(_binary) { }
  };

  struct CSVFileSource : FileSource {
    const char delimiter;
    constexpr CSVFileSource(const char* _name, SourceType _type, const char* _path, char _delimiter)
      : FileSource(_name, _type, _path, false), delimiter(_delimiter) { }
  };

  struct OrderbookFileSource : CSVFileSource {
    // TODO: unified stream
  };
}

#endif /* DBTOASTER_SOURCE_HPP */