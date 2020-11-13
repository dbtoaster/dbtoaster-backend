#ifndef DRIVER_RELATION_ITERATOR_HPP
#define DRIVER_RELATION_ITERATOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <queue>
#include <type_traits>
#include <cassert>
#include "ordered_event.hpp"
#include "compatibility.hpp"
#include "utils.hpp"

using namespace std;
using namespace dbtoaster;

constexpr size_t kMaxBatchSize = 100000000;

template <class T>
class RelationIterator {
 public:
  RelationIterator() : batch_size(0) { }
  
  virtual ~RelationIterator() = default;
  
  virtual void open() = 0;
  
  virtual void close() = 0;
  
  virtual T next() = 0;
  
  virtual bool hasNext() const = 0;
  
  void setBatchSize(size_t sz) {
    if (sz > kMaxBatchSize) {
      std::cerr << "Maximum batch size is " << kMaxBatchSize << std::endl;
      return;
    }
    batch_size = sz;
  }
 protected:
  size_t batch_size;
};

template <class T>
class FileIterator : public RelationIterator<T> {
 public:
  FileIterator(string path, bool binary)
      : filename(path), mode(binary ? std::ifstream::in | std::ifstream::binary
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
  CSVFileIterator(RelationId rid, FileSource source, char delim)
      : FileIterator<OrderedEvent>(source.filename, false),
        id(rid), delimiter(delim) { }

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
      fill_tuple(msg->content, line, delimiter, start);
      
      return OrderedEvent(order, id, type, unique_ptr<Message>(msg));
    }
    return OrderedEvent();
  }

  OrderedEvent nextBatchEvent() {
    assert(batch_size > 0 && batch_size <= kMaxBatchSize);

    auto msg = make_unique<BatchMessage<Message, int>>();
    msg->content.reserve(batch_size);

    OrderType order = kInvalidOrder;
    for (size_t i = 0; i < batch_size; ++i) {
      OrderedEvent event = nextEvent();    
      if (event.isEmpty()) {
        break;
      }
      if (HasOrder && order == kInvalidOrder) {
        order = event.order;
      }
      msg->append(
        *static_cast<Message*>(event.message.get()),
        (!HasDeletions || event.event_type == EventType::kInsertTuple ? 1 : -1)
      );
    }

    if (msg->content.size() > 0) {
      return OrderedEvent(order, id, EventType::kBatchUpdate, std::move(msg));
    }
    return OrderedEvent();
  }

  const RelationId id;
  const char delimiter;
};

enum class OrderbookType { kBids = 0, kAsks, kBoth };

struct OrderBookInputMessage : Message<std::tuple<double, long, string, double, double>> {
  double timestamp() const { return get<0>(content); }
  long id() const { return get<1>(content); }
  string action() const { return get<2>(content); }
  double volume() const { return get<3>(content); }
  double price() const { return get<4>(content); }
};

struct OrderBookOutputMessage : Message<std::tuple<double, long, long, double, double>> {
  explicit OrderBookOutputMessage() { }
  OrderBookOutputMessage(double t_timestamp, long t_id, long t_broker_id, 
                         double t_volume, double t_price) {
    content = make_tuple(t_timestamp, t_id, t_broker_id, t_volume, t_price);
  }

  double timestamp() const { return get<0>(content); }
  long id() const { return get<1>(content); }
  long brokerId() const { return get<2>(content); }
  double volume() const { return get<3>(content); }
  double price() const { return get<4>(content); }

  double& volume() { return get<3>(content); }
};

template <bool BatchMode>
class OrderbookFileIterator : public FileIterator<OrderedEvent> {
 public:
  using InputMessage = OrderBookInputMessage;
  using OutputMessage = OrderBookOutputMessage;
  using OrderBook = std::map<long, OutputMessage>;
  using Queue = priority_queue<OrderedEvent>;

  OrderbookFileIterator(RelationId bids_id, RelationId asks_id, 
                        FileSource source, char delim,
                        long t_num_brokers, bool t_deterministic,
                        OrderbookType t_type, bool t_insert_only)
      : FileIterator<OrderedEvent>(source.filename, false),
        bids_relation_id(bids_id), asks_relation_id(asks_id),
        delimiter(delim), num_brokers(t_num_brokers),
        deterministic(t_deterministic), type(t_type),
        insert_only(t_insert_only) { }

  OrderedEvent next() {
    return (BatchMode ? nextBatchEvent() : nextEvent());
  }

 protected:
  OrderedEvent nextEvent() {
    string line;
    while (std::getline(this->fs, line)) {
      InputMessage msg;
      fill_tuple(msg.content, line, delimiter, 0);
      OrderType order = 2 * msg.timestamp();
          
      if (msg.action() == "B") {
        if (type == OrderbookType::kBids || type == OrderbookType::kBoth) {
          long broker_id = (deterministic ? msg.id() : rand()) % num_brokers;
          OutputMessage* out = new OutputMessage(msg.timestamp(), msg.id(), broker_id, msg.volume(), msg.price());
          bids_book[msg.id()] = *out;
          queue.push(OrderedEvent(order, bids_relation_id, EventType::kInsertTuple,
                                  unique_ptr<OutputMessage>(out)));
        }
      }
      else if (msg.action() == "S") {
        if (type == OrderbookType::kAsks || type == OrderbookType::kBoth) {
          long broker_id = (deterministic ? msg.id() : rand()) % num_brokers;
          OutputMessage* out = new OutputMessage(msg.timestamp(), msg.id(), broker_id, msg.volume(), msg.price());
          asks_book[msg.id()] = *out;
          queue.push(OrderedEvent(order, asks_relation_id, EventType::kInsertTuple,
                                  unique_ptr<OutputMessage>(out)));
        }
      }
      else if (msg.action() == "E") {
        // Find matching bid order
        auto bid_it = bids_book.find(msg.id());
        if (bid_it != bids_book.end()) {
          if (!insert_only) {
            // Delete old bid order
            queue.push(OrderedEvent(order - 1, bids_relation_id, EventType::kDeleteTuple, 
                                    make_unique<OutputMessage>(bid_it->second)));
          }          
          bid_it->second.volume() -= msg.volume();
          if (bid_it->second.volume() <= 0.0) {
            bids_book.erase(bid_it);
          }
          else {
            // Insert updated bid order
            queue.push(OrderedEvent(order, bids_relation_id, EventType::kInsertTuple,
                                    make_unique<OutputMessage>(bid_it->second)));
          }
        }
        else {
          // Find matching ask order
          auto ask_it = asks_book.find(msg.id());
          if (ask_it != asks_book.end()) {
            if (!insert_only) {
              // Delete old ask order
              queue.push(OrderedEvent(order - 1, asks_relation_id, EventType::kDeleteTuple,
                                      make_unique<OutputMessage>(ask_it->second)));
            }
            ask_it->second.volume() -= msg.volume();
            if (ask_it->second.volume() <= 0.0) {
              asks_book.erase(ask_it);
            }
            else {
              // Insert updated ask order
              queue.push(OrderedEvent(order, asks_relation_id, EventType::kInsertTuple,
                                      make_unique<OutputMessage>(ask_it->second)));
            }
          }
          else {
            // std::cerr << "unknown order id " << msg.id()
            //           << " (neither bid nor ask)" << std::endl;
          }
        }
      }
      else if (msg.action() == "D" || msg.action() == "F") {
        // Find matching bid order
        auto bid_it = bids_book.find(msg.id());
        if (bid_it != bids_book.end()) {
          if (!insert_only) {
            // Delete bid order
            queue.push(OrderedEvent(order, bids_relation_id, EventType::kDeleteTuple,
                                    make_unique<OutputMessage>(bid_it->second)));
          }
          bids_book.erase(bid_it);
        }
        else {
          // Find matching ask order
          auto ask_it = asks_book.find(msg.id());
          if (ask_it != asks_book.end()) {
            if (!insert_only) {
              // Delete ask order
              queue.push(OrderedEvent(order, asks_relation_id, EventType::kDeleteTuple,
                                      make_unique<OutputMessage>(ask_it->second)));
            }
            asks_book.erase(ask_it);
          }
          else {
            // std::cerr << "unknown order id " << msg.id()
            //           << " (neither bid nor ask)" << std::endl;
          }
        }
      }
      /*
       // ignore for now...
      else if (action == "X")
      else if (action == "C")
      else if (action == "T")
      */
      if (!queue.empty()) break;
    }
    return dequeue();
  }

  OrderedEvent nextBatchEvent() {
    assert(batch_size > 0 && batch_size <= kMaxBatchSize);

    if (bids_batch_event.isEmpty() && asks_batch_event.isEmpty()) {
      readNextBatch();
    }
    if (!bids_batch_event.isEmpty()) {
      return std::move(bids_batch_event);
    }
    if (!asks_batch_event.isEmpty()) {
      return std::move(asks_batch_event);
    }
    return OrderedEvent();
  }

  OrderedEvent dequeue() {
    if (queue.empty()) return OrderedEvent();
    OrderedEvent evt = std::move(const_cast<OrderedEvent&>(queue.top()));
    queue.pop();
    return evt;
  }

 protected:
  void readNextBatch() {
    assert(bids_batch_event.isEmpty() && asks_batch_event.isEmpty());

    auto bids_msg = make_unique<BatchMessage<OutputMessage, int>>();
    bids_msg->content.reserve(batch_size);
    auto asks_msg = make_unique<BatchMessage<OutputMessage, int>>();
    asks_msg->content.reserve(batch_size);
    
    OrderType bid_order = kInvalidOrder;
    OrderType ask_order = kInvalidOrder;
    for (size_t i = 0; i < batch_size; ++i) {
      OrderedEvent event = nextEvent();
      if (event.isEmpty()) {
        break;
      }    
      if (event.relation_id == bids_relation_id) {
        if (bid_order == kInvalidOrder) {
          bid_order = event.order;
        }
        bids_msg->append(
          *static_cast<OutputMessage*>(event.message.get()),
          (insert_only || event.event_type == EventType::kInsertTuple ? 1 : -1)
        );
      }
      else if (event.relation_id == asks_relation_id) {
        if (ask_order == kInvalidOrder) {
          ask_order = event.order;
        }
        asks_msg->append(
          *static_cast<OutputMessage*>(event.message.get()),
          (insert_only || event.event_type == EventType::kInsertTuple ? 1 : -1)
        );
      }      
    }
    if (bids_msg->content.size() > 0) {
      bids_batch_event = OrderedEvent(bid_order, bids_relation_id, EventType::kBatchUpdate, std::move(bids_msg));
    }
    if (asks_msg->content.size() > 0) {
      asks_batch_event = OrderedEvent(ask_order, asks_relation_id, EventType::kBatchUpdate, std::move(asks_msg));
    }
  }

  const RelationId bids_relation_id;
  const RelationId asks_relation_id;
  const char delimiter;
  const long num_brokers;
  const bool deterministic;
  const OrderbookType type;
  const bool insert_only;

  OrderBook bids_book;
  OrderBook asks_book;
  Queue queue;
  OrderedEvent bids_batch_event;
  OrderedEvent asks_batch_event;
};



#endif /* DRIVER_RELATION_ITERATOR_HPP */