#ifndef DRIVER_SOURCE_ITERATOR_HPP
#define DRIVER_SOURCE_ITERATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <type_traits>
#include "ordered_event.hpp"
#include "utils.hpp"

using namespace std;
using namespace dbtoaster;

template <class T>
class SourceIterator {
 public:
  SourceIterator(SourceId id_) : id(id_) { }
  virtual ~SourceIterator() = default;
  virtual void open() = 0;
  virtual void close() = 0;
  virtual T next() = 0;
  virtual bool hasNext() const = 0;
 protected:
  SourceId id;
};

template <class T>
class FileIterator : public SourceIterator<T> {
 public:
  FileIterator(const FileSource& src) 
      : FileIterator(src.id, src.filename, src.binary) { }

  FileIterator(SourceId id, string path, bool binary)
      : SourceIterator<T>(id), filename(path), 
        mode(binary ? std::ifstream::in | std::ifstream::binary
                    : std::ifstream::in) { }

  void open() {
    fs.open(filename, mode);
    if (!fs.is_open()) {
      std::cerr << "Error opening file " << filename << endl;
    }
  }
  
  void close() { fs.close(); }
  
  bool hasNext() const { return !fs.eof(); }

 protected:
  const string filename;
  const ios_base::openmode mode;
  std::ifstream fs;
};

template <class Message, bool HasOrder, bool HasDeletions,
          typename enable_if<is_base_of<MessageBase, Message>::value>::type* = nullptr>
class CSVFileIterator : public FileIterator<OrderedEvent> {
 public:
  CSVFileIterator(FileSource src, char delim)
      : FileIterator<OrderedEvent>(src.id, src.filename, false),
        delimiter(delim) { }

  OrderedEvent next() {
    string line;
    if (std::getline(this->fs, line)) {
      size_t start = 0;

      OrderType order = kInvalidOrder;
      if (HasOrder) {
        size_t found = line.find(delimiter, start);
        order = convert<OrderType>(line.substr(start, found - start));
        start = found + 1;
      }
      
      EventType type = EventType::kInsertTuple;
      if (HasDeletions) {
        size_t found = line.find(delimiter, start);
        int op = convert<int>(line.substr(start, found - start));
        if (op == 0) { type = EventType::kDeleteTuple; }
        start = found + 1;    
      }
      
      Message* msg = new Message();
      fill_tuple(msg->tpl, line, delimiter, start);
      
      return OrderedEvent(order, id, type, unique_ptr<Message>(msg));
    }
    return OrderedEvent();
  }

 protected:
  const char delimiter;
};


#endif /* DRIVER_SOURCE_ITERATOR_HPP */