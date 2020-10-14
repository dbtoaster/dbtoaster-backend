#ifndef DRIVER_SOURCE_ITERATOR_HPP
#define DRIVER_SOURCE_ITERATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <type_traits>
#include <cassert>
#include "ordered_event.hpp"
#include "utils.hpp"

using namespace std;
using namespace dbtoaster;

constexpr size_t kMaxBatchSize = 100000000;

template <class T>
class SourceIterator {
 public:
  SourceIterator(SourceId id_) : id(id_), batch_size(0) { }
  
  virtual ~SourceIterator() = default;
  
  virtual void open() = 0;
  
  virtual void close() = 0;
  
  virtual T next() = 0;
  
  virtual bool hasNext() const = 0;
  
  void setBatchSize(size_t sz) {
    if (sz > kMaxBatchSize) {
      std::cerr << "Maximum batch size is " << kMaxBatchSize << endl;
      return;
    }
    batch_size = sz;
  }
 protected:
  SourceId id;
  size_t batch_size;
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

template <class Message, 
          bool HasOrder,
          bool HasDeletions,
          bool BatchMode,
          typename enable_if<is_base_of<MessageBase, Message>::value>::type* = nullptr>
class CSVFileIterator : public FileIterator<OrderedEvent> {
 public:
  CSVFileIterator(FileSource src, char delim)
      : FileIterator<OrderedEvent>(src.id, src.filename, false),
        delimiter(delim) { }

  OrderedEvent next() {
    return (BatchMode ? nextBatchEvent() : nextEvent());
  }

 protected:
  OrderedEvent nextEvent() {
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

  OrderedEvent nextBatchEvent() {
    assert(batch_size > 0 && batch_size <= kMaxBatchSize);

    auto msg = unique_ptr<BatchMessage<Message, int>>(new BatchMessage<Message, int>());
    msg->batch.reserve(batch_size);

    OrderType order = kInvalidOrder;
    for (size_t i = 0; i < batch_size; i++) {
      OrderedEvent event = nextEvent();    
      if (event.isEmpty()) {
        break;
      }
      if (HasOrder && order == kInvalidOrder) {
        order = event.order;
      }
      msg->batch.push_back({
        .key = *static_cast<Message*>(event.message.get()),
        .value = (!HasDeletions || event.event_type == EventType::kInsertTuple ? 1 : -1)
      });
    }

    if (msg->batch.size() > 0) {
      return OrderedEvent(order, id, EventType::kBatchUpdate, std::move(msg));
    }
    return OrderedEvent();
  }

  const char delimiter;
};


#endif /* DRIVER_SOURCE_ITERATOR_HPP */