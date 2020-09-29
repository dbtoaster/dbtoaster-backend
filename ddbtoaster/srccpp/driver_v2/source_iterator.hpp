#ifndef DRIVER_SOURCE_ITERATOR_HPP
#define DRIVER_SOURCE_ITERATOR_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "source.hpp"
#include "utils.hpp"

template <class... Types>
class SourceIterator {
  public:
    virtual ~SourceIterator() { }
    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool next(Tuple<Types...>&) = 0;
    virtual bool has_next() const = 0;
};

template <class... Types>
class FileSourceIterator : public SourceIterator<Types...> {
  public:
    FileSourceIterator(const char* path, bool binary)
      : filename(path), 
        mode(binary ? std::ifstream::in | std::ifstream::binary 
                    : std::ifstream::in) { }
    
    ~FileSourceIterator() { close(); }

    void open() {
      fs.open(filename, mode);
      if (!fs.is_open()) {
        std::cerr << "Error opening file " << filename << endl;
      }
    }
    
    void close() { fs.close(); }
    
    bool has_next() const { return !fs.eof(); }

  protected:
    const char* filename;
    const ios_base::openmode mode;
    std::ifstream fs;
};

template <class... Types>
class CSVFileSourceIterator : public FileSourceIterator<Types...> {
  public:
    CSVFileSourceIterator(CSVFileSource source)
      : FileSourceIterator<Types...>(source.path, false), delimiter(source.delimiter) { }

    bool next(Tuple<Types...>& tuple) {
      string line;
      if (std::getline(this->fs, line)) {
        fill_tuple(tuple, line, delimiter);
        return true;
      }
      return false;
    }

  protected:
    const char delimiter;
};

#endif /* DRIVER_SOURCE_ITERATOR_HPP */