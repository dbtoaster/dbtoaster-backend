#ifndef DRIVER_DISPATCHER_HPP
#define DRIVER_DISPATCHER_HPP

#include <vector>
#include <memory>
#include <tuple>
#include "utils.hpp"
#include "source_iterator.hpp"

class Dispatcher {
  public:
    virtual ~Dispatcher() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool next() = 0;
    virtual bool has_next() const = 0;
};

template <class... Types> 
using SourceIteratorPtr = unique_ptr<SourceIterator<Types...>>;

template <class Tuple, class... Functions>
class LookaheadEventDispatcher { };

template <class Function, class... Types>
class LookaheadEventDispatcher<Tuple<Types...>, Function> : public virtual Dispatcher {
  public:
    LookaheadEventDispatcher(SourceIteratorPtr<Types...> _it, Function _fn)
      : it(std::move(_it)), fn(_fn), _has_next(false) { }

    void open() {
      close();
      it->open();
      _has_next = it->next(t);
    }

    void close() {
      it->close();
      _has_next = false;
    }

    bool next() {
      if (_has_next) {
        invoke(t, fn);
        _has_next = it->next(t);
        return true;
      }
      return false;
    }

    bool has_next() const { return _has_next; }

    template <size_t Idx>
    bool peek(tuple_element_t<Idx, Tuple<Types...>>& e) const {
      if (_has_next) {
        e = get<Idx>(t);
        return true;
      }
      return false;
    }

    bool peek(Tuple<Types...>& target) const {
      if (_has_next) {
        target = t;
        return true;
      }
      return false;
    }

  protected:
    const SourceIteratorPtr<Types...> it;
    const Function fn;
    bool _has_next;
    Tuple<Types...> t;
};

template <class Tuple, class... Functions>
class BufferedEventDispatcher;

template <class Function, class... Types>
class BufferedEventDispatcher<Tuple<Types...>, Function> : public virtual Dispatcher {
  public:
    BufferedEventDispatcher(SourceIteratorPtr<Types...> _it, Function _fn)
      : it(std::move(_it)), fn(_fn), current(0) { }

    void open() {
      close();
      it->open();
      Tuple<Types...> t;
      while (it->next(t)) {
        buffer.push_back(t);
      }
      it->close();
    }

    void close() {
      buffer.clear();
      current = 0;    
    }

    bool next() {
      if (current < buffer.size()) {
        invoke(buffer[current++], fn);
        return true;
      }
      return false;
    }

    bool has_next() const { return current < buffer.size(); }

    template <size_t Idx>
    bool peek(tuple_element_t<Idx, Tuple<Types...>>& e) const {
      if (current < buffer.size()) {
        e = get<Idx>(buffer[current]);
        return true;
      }
      return false;
    }

    bool peek(Tuple<Types...>& target) const {
      if (current < buffer.size()) {
        target = buffer[current];
        return true;
      }
      return false;
    }

  protected:
    const SourceIteratorPtr<Types...> it;
    const Function fn;
    vector<Tuple<Types...>> buffer;
    size_t current;    
};

class OrderedDispatcher : public virtual Dispatcher {
  public:
    virtual bool order(size_t &e) const = 0;
};

template <class Function, class... Types>
class OrderedEventDispatcher 
    : public LookaheadEventDispatcher<Tuple<size_t, Types...>, Function>,
      public OrderedDispatcher {
  public:
    OrderedEventDispatcher(SourceIteratorPtr<size_t, Types...> it, Function fn)
      : LookaheadEventDispatcher<Tuple<size_t, Types...>, Function>(std::move(it), fn) { }

    bool order(size_t& e) const { return this->template peek<0>(e); }
};

template <class Function, class... Types>
class OrderedBufferedEventDispatcher 
    : public BufferedEventDispatcher<Tuple<size_t, Types...>, Function>,
      public OrderedDispatcher { 
  public:
    OrderedBufferedEventDispatcher(SourceIteratorPtr<size_t, Types...> it, Function fn)
      : BufferedEventDispatcher<Tuple<size_t, Types...>, Function>(std::move(it), fn) { }

    bool order(size_t& e) const { return this->template peek<0>(e); }
};

//
// Factory methods
//

template <class Function, class... Types>
unique_ptr<Dispatcher> create_dispatcher(SourceIteratorPtr<Types...> it, Function fn, bool buffer_source) {
  if (buffer_source) 
    return make_unique<BufferedEventDispatcher<Tuple<Types...>, Function>>(std::move(it), fn);
  else
    return make_unique<LookaheadEventDispatcher<Tuple<Types...>, Function>>(std::move(it), fn);
}

template <class Function, class... Types>
unique_ptr<OrderedDispatcher> create_ordered_dispatcher(SourceIteratorPtr<size_t, Types...> it, Function fn, bool buffer_source) {
  if (buffer_source)
    return make_unique<OrderedBufferedEventDispatcher<Function, Types...>>(std::move(it), fn);
  else
    return make_unique<OrderedEventDispatcher<Function, Types...>>(std::move(it), fn);
}

#endif /* DRIVER_DISPATCHER_HPP */