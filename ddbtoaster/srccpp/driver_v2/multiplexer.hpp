#ifndef DRIVER_MULTIPLEXER_HPP
#define DRIVER_MULTIPLEXER_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include "dispatcher.hpp"

using namespace std;

class RoundRobinMultiplexer {
  public: 
    RoundRobinMultiplexer(vector<unique_ptr<Dispatcher>> d)
        : current(0), dispatchers(std::move(d)) { 
      active_dispatchers.reserve(dispatchers.size());
    }

    void open() {
      current = 0;
      active_dispatchers.clear();
      for (auto& d : dispatchers) { 
        d->close();
        d->open();
        active_dispatchers.push_back(d.get());
      }
    }

    void close() {
      current = 0;
      active_dispatchers.clear();
      for (auto& d : dispatchers) {
        d->close();
      }
    }

    bool next() {
      size_t sz = active_dispatchers.size();
      if (sz == 1) return active_dispatchers[0]->next();     // hot path optimization

      if (sz == 0) return false;

      if (current >= sz) { current = 0; }

      if (active_dispatchers[current]->next()) {
        current++;
        return true;
      }
      active_dispatchers.erase(active_dispatchers.cbegin() + current);
      return next();
    }

    size_t size() const { return dispatchers.size(); }

    size_t active_size() const { return active_dispatchers.size(); }

  private:
    vector<unique_ptr<Dispatcher>> dispatchers;
    vector<Dispatcher*> active_dispatchers;
    size_t current;
};

inline bool order_leq(const unique_ptr<OrderedDispatcher>& d1, const unique_ptr<OrderedDispatcher>& d2) {
  size_t o1 = SIZE_MAX, o2 = SIZE_MAX;
  d1->order(o1);
  d2->order(o2);
  return o1 <= o2;
}

class OrderedMultiplexer {
  public:
    OrderedMultiplexer(vector<unique_ptr<OrderedDispatcher>> d)
      : active(0), dispatchers(std::move(d)) { }

    void open() {
      for (auto& d : dispatchers) { 
        d->close();
        d->open(); 
      }
      sort(dispatchers.begin(), dispatchers.end(), order_leq);
      active = dispatchers.size();
    }

    void close() {
      active = 0;
      for (auto& d : dispatchers) {
        d->close();
      }
    }

    bool next() {
      if (active == 1) return dispatchers[0]->next();     // hot path optimization

      if (active == 0) return false;

      if (dispatchers[0]->next()) {
        bool has_more = dispatchers[0]->has_next();
        // resort active elements
        for (size_t i = 0; i < active - 1; i++) {
          if (order_leq(dispatchers[i], dispatchers[i+1]))
            break;
          else 
            dispatchers[i].swap(dispatchers[i+1]);
        }
        if (!has_more) { active--; }
        return true;
      }
      return false;
    }

    bool next_slower() {
      if (dispatchers.size() == 1) return dispatchers[0]->next();     // hot path optimization

      size_t minOrd = SIZE_MAX;
      auto minIt = dispatchers.end();
      for (auto it = dispatchers.begin(); it != dispatchers.end(); ) {
        size_t ord = 0;
        if ((*it)->order(ord)) {
          if (ord < minOrd) {
            minOrd = ord;
            minIt = it;
          }
          ++it;
        }
        else {
          it = dispatchers.erase(it);
        }
      }
      if (minOrd < SIZE_MAX) {
        return (*minIt)->next();
      }
      return false;
    }

    size_t size() const { return dispatchers.size(); }

    size_t active_size() const { return active; }

  private:
    vector<unique_ptr<OrderedDispatcher>> dispatchers;
    size_t active;
};

#endif /* DRIVER_MULTIPLEXER_HPP */