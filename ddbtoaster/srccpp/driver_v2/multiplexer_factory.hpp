#ifndef DRIVER_MULTIPLEXER_BUILDER_HPP
#define DRIVER_MULTIPLEXER_BUILDER_HPP

#include <memory>
#include <vector>
#include <functional>

using namespace std;

template <class Dispatcher, class Multiplexer>
class MultiplexerFactory {
  public:
    static constexpr int INSERT_EVENT = 1;
    static constexpr int DELETE_EVENT = 0;

    template <class... Types>
    using Callback = void (dbtoaster::data_t::*)(Types...);

    using Functor = function<unique_ptr<Dispatcher>(dbtoaster::data_t&, bool)>;

    unique_ptr<Multiplexer> create_static_multiplexer(dbtoaster::data_t& data, bool buffer_source) {
      vector<unique_ptr<Dispatcher>> v;
      v.reserve(static_functors.size());
      for (auto& f : static_functors) {
        v.push_back(f(data, buffer_source));
      }
      return make_unique<Multiplexer>(std::move(v));
    }

    unique_ptr<Multiplexer> create_dynamic_multiplexer(dbtoaster::data_t& data, bool buffer_source) {
      vector<unique_ptr<Dispatcher>> v;
      v.reserve(dynamic_functors.size());
      for (auto& f : dynamic_functors) {
        v.push_back(f(data, buffer_source));
      }
      return make_unique<Multiplexer>(std::move(v));
    }

  protected:
    vector<Functor> static_functors;
    vector<Functor> dynamic_functors;
};

class RoundRobinMultiplexerFactory 
    : public MultiplexerFactory<Dispatcher, RoundRobinMultiplexer> {
  public:
    template <class... In, class... Out>
    void dispatch(CSVFileSource source, Schema<In...>, Callback<Out...> fn) {
      auto f = [source, fn](dbtoaster::data_t& data, bool buffer_source) {
        SourceIteratorPtr<In...> it = 
          make_unique<CSVFileSourceIterator<In...>>(source);
        auto data_fn = [&, fn](In... args) {
          (data.*fn)(forward<In>(args)...); 
        };
        return create_dispatcher(std::move(it), data_fn, buffer_source);
      };
      if (source.isTable())
        static_functors.push_back(std::move(f));
      else
        dynamic_functors.push_back(std::move(f));
    }

    template <class... In, class... Out>
    void dispatch(CSVFileSource source, Schema<int, In...>, Callback<Out...> on_insert_fn, Callback<Out...> on_delete_fn) {
      auto f = [source, on_insert_fn, on_delete_fn](dbtoaster::data_t& data, bool buffer_source) {
        SourceIteratorPtr<int, In...> it =
          make_unique<CSVFileSourceIterator<int, In...>>(source);
        auto mixed_fn = [&, on_insert_fn, on_delete_fn](int event, In... args) {
          if (event == INSERT_EVENT)
            (data.*on_insert_fn)(forward<In>(args)...);
          else
            (data.*on_delete_fn)(forward<In>(args)...);
        };
        return create_dispatcher(std::move(it), mixed_fn, buffer_source);
      };
      if (source.isTable())
        static_functors.push_back(std::move(f));
      else
        dynamic_functors.push_back(std::move(f));
    }
};

class OrderedMultiplexerFactory 
    : public MultiplexerFactory<OrderedDispatcher, OrderedMultiplexer> {
  public:
    template <class... In, class... Out>
    void dispatch(CSVFileSource source, Schema<size_t, In...>, Callback<Out...> fn) {
      auto f = [source, fn](dbtoaster::data_t& data, bool buffer_source) {
        SourceIteratorPtr<size_t, In...> it =
          make_unique<CSVFileSourceIterator<size_t, In...>>(source);
        auto order_fn = [&, fn](size_t, In... args) {
          (data.*fn)(forward<In>(args)...);
        };
        return create_ordered_dispatcher(std::move(it), order_fn, buffer_source);
      };
      if (source.isTable())
        static_functors.push_back(std::move(f));
      else
        dynamic_functors.push_back(std::move(f));
    }

    template <class... In, class... Out>
    void dispatch(CSVFileSource source, Schema<size_t, int, In...>, Callback<Out...> on_insert_fn, Callback<Out...> on_delete_fn) {
      auto f = [source, on_insert_fn, on_delete_fn](dbtoaster::data_t& data, bool buffer_source) {
        SourceIteratorPtr<size_t, int, In...> it =
          make_unique<CSVFileSourceIterator<size_t, int, In...>>(source);
        auto order_mixed_fn = [&, on_insert_fn, on_delete_fn](size_t, int event, In... args) {
          if (event == INSERT_EVENT)
            (data.*on_insert_fn)(forward<In>(args)...);
          else
            (data.*on_delete_fn)(forward<In>(args)...);
        };
        return create_ordered_dispatcher(std::move(it), order_mixed_fn, buffer_source);
      };
      if (source.isTable())
        static_functors.push_back(std::move(f));
      else
        dynamic_functors.push_back(std::move(f));
    }
};

#endif /* DRIVER_MULTIPLEXER_BUILDER_HPP */