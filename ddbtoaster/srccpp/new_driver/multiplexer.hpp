#ifndef DRIVER_MULTIPLEXER_HPP
#define DRIVER_MULTIPLEXER_HPP

#include <vector>
#include <queue>
#include <memory>
#include "event.hpp"
#include "source_iterator.hpp"

using namespace std;

typedef SourceIterator<OrderedEvent> EventIterator;
typedef unique_ptr<EventIterator> EventIteratorPtr;

class RoundRobinMultiplexer {
 public:
  RoundRobinMultiplexer(vector<EventIteratorPtr> iters)
      : iterators(std::move(iters)), current(0) { 
    active_iterators.reserve(iterators.size());
  }

  void open() {
    current = 0;
    active_iterators.clear();
    for (auto& it : iterators) {
      it->close();
      it->open();
      active_iterators.push_back(it.get());
    }
  }

  void close() {
    current = 0;
    active_iterators.clear();
    for (auto& it : iterators) {
      it->close();
    }
  }

  Event next() {
    size_t sz = active_iterators.size();
    if (sz == 1) return active_iterators[0]->next();     // hot path optimization

    if (sz == 0) return Event();

    if (current >= sz) { current = 0; }

    OrderedEvent evt = active_iterators[current]->next();
    if (!evt.isEmpty()) {
      current++;
      return std::move(evt);
    }
    active_iterators.erase(active_iterators.begin() + current);
    return next();
  }

 private:
  const vector<EventIteratorPtr> iterators;
  vector<EventIterator*> active_iterators;
  size_t current;
};

class OrderedMultiplexer {
 private:
  struct ActiveEvent : OrderedEvent {
    ActiveEvent(OrderedEvent e, EventIterator* it)
        : OrderedEvent(std::move(e)), iterator(it) { }
    EventIterator* iterator;

    bool operator<(const ActiveEvent& other) const {
      return this->order > other.order;     // min priority queue
    }
  };

  using Queue = priority_queue<ActiveEvent>;

public:
  OrderedMultiplexer(vector<EventIteratorPtr> iters)
      : iterators(std::move(iters)) { }

  void open() {
    queue = Queue();
    for (auto& it : iterators) { 
      it->close();
      it->open();
      queue.push(ActiveEvent(it->next(), it.get()));
    }
  }

  void close() {
    queue = Queue();
    for (auto& it : iterators) {
      it->close();
    }
  }

  Event next() {
    if (queue.size() == 0) return Event();
    ActiveEvent current = std::move(const_cast<ActiveEvent&>(queue.top()));
    queue.pop();
    queue.push(ActiveEvent(current.iterator->next(), current.iterator));
    return std::move(current);
  }

 private:
  vector<EventIteratorPtr> iterators;
  Queue queue;
};

#endif /* DRIVER_MULTIPLEXER_HPP */