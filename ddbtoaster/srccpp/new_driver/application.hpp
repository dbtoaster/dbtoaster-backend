#ifndef DRIVER_APPLICATION_HPP
#define DRIVER_APPLICATION_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <type_traits>
#include "compatibility.hpp"
#include "runtime_opts.hpp"
#include "stopwatch.hpp"
#include "source.hpp"
#include "multiplexer.hpp"

using namespace std;

class Application {
 public:
  Application(const RuntimeOpts& _opts) : opts(_opts) {
    if (dbtoaster::data_t::kBatchModeActive && opts.batch_size == 0) {
      cerr << "Use -b <arg> to specify the batch size." << endl;
      exit(1);
    }
  }

  void run();

 protected:  
  using Multiplexer = std::conditional<data_t::kOrderedDataset,
                                       OrderedMultiplexer,
                                       RoundRobinMultiplexer>::type;
  using MultiplexerPtr = unique_ptr<Multiplexer>;

  class Visitor {
   public:
    template <class T>
    void addMap(string name, const T& map, bool isTopLevel) {
      cout << "Registered: " << name << " " << isTopLevel << endl;
    }

    template <class Message, bool HasDeletions>
    void addSource(FileSource source, SourceFormat format) {
      if (format.name == "CSV") {
        char delimiter = ',';
        auto it = format.params.find("delimiter");
        if (it != format.params.end()) {
          delimiter = (it->second)[0];
        }
        if (source.isTable()) {          
          table_iterators.push_back(
            make_unique<CSVFileIterator<Message, 
                                        data_t::kOrderedDataset,
                                        HasDeletions,
                                        false>>(source, delimiter));
        }
        else {
          stream_iterators.push_back(
            make_unique<CSVFileIterator<Message,
                                        data_t::kOrderedDataset,
                                        HasDeletions,
                                        data_t::kBatchModeActive>>(source, delimiter));
        }
      }
      else {
        cerr << "Adaptor type not supported: " << format.name << endl;
        exit(1);
      }
    }

    MultiplexerPtr getTableMultiplexer(size_t batch_size) {
      return make_unique<Multiplexer>(std::move(table_iterators));
    }

    MultiplexerPtr getStreamMultiplexer(size_t batch_size) {
      for (auto& it : stream_iterators) {
        it->setBatchSize(batch_size);
      }
      return make_unique<Multiplexer>(std::move(stream_iterators));
    }

   private:
    vector<EventIteratorPtr> table_iterators;
    vector<EventIteratorPtr> stream_iterators;
  };

  void init() {
    Visitor visitor;
    dbtoaster::data_t::registerSources(visitor);
    static_multiplexer = visitor.getTableMultiplexer(opts.batch_size);
    dynamic_multiplexer = visitor.getStreamMultiplexer(opts.batch_size);
    static_multiplexer->open();
    dynamic_multiplexer->open();
    static_buffer.clear();
    dynamic_buffer.clear();
  }

  void close() {
    static_multiplexer->close();
    dynamic_multiplexer->close();
    static_buffer.clear();
    dynamic_buffer.clear();
  }

  void processTables(dbtoaster::data_t& data) {
    if (opts.preload_input) {
      for (auto& e : static_buffer) {
        data.process_table_event(e);
      }
    }
    else {
      Event e = static_multiplexer->next();
      while (!e.isEmpty()) {
        data.process_table_event(std::move(e));
        e = static_multiplexer->next();
      }
    }
  }

  void processOnSystemReady(dbtoaster::data_t& data) {
    data.on_system_ready_event();
  }

  void processStreams(dbtoaster::data_t& data) {
    if (opts.snapshot_interval > 0)
      processStreamsSnapshot(data, opts.snapshot_interval);
    else
      processStreamsNoSnapshot(data);
  }

  void processStreamsSnapshot(dbtoaster::data_t& data, long snapshot_interval) {
    long next_snapshot = 0;
    if (opts.preload_input) {
      for (auto& e : dynamic_buffer) {
        data.process_stream_event(e);

        if (data.tN >= next_snapshot) {
          onSnapshot(data);
          next_snapshot = data.tN + snapshot_interval;
        }
      }
    }
    else {
      Event e = dynamic_multiplexer->next();
      while (!e.isEmpty()) {
        data.process_stream_event(std::move(e));
        e = dynamic_multiplexer->next();

        if (data.tN >= next_snapshot) {
          onSnapshot(data);
          next_snapshot = data.tN + snapshot_interval;
        }
      }
    }
  }

  void processStreamsNoSnapshot(dbtoaster::data_t& data) {
    if (opts.preload_input) {
      for (auto& e : dynamic_buffer) {
        data.process_stream_event(e);
      }
    }
    else {
      Event e = dynamic_multiplexer->next();
      while (!e.isEmpty()) {
        data.process_stream_event(std::move(e));
        e = dynamic_multiplexer->next();
      }
    }
  }

  void onSnapshot(dbtoaster::data_t& data) {
    onEndProcessing(data, false);
  }

  void onBeginProcessing(dbtoaster::data_t& data) {
    if (opts.preload_input) {
      static_buffer.clear();
      Event e = static_multiplexer->next();
      while (!e.isEmpty()) {
        static_buffer.push_back(std::move(e));
        e = static_multiplexer->next();
      }

      dynamic_buffer.clear();
      e = dynamic_multiplexer->next();
      while (!e.isEmpty()) {
        dynamic_buffer.push_back(std::move(e));
        e = dynamic_multiplexer->next();
      }
    }
  }

  void onEndProcessing(dbtoaster::data_t& data, bool print_result) {
    if (print_result) {
      cout << "<snap>\n";
      data.serialize(std::cout, 0);
      cout << "\n</snap>" << endl;
    }
  }

  RuntimeOpts opts;
  MultiplexerPtr static_multiplexer;
  MultiplexerPtr dynamic_multiplexer;
  vector<Event> static_buffer;
  vector<Event> dynamic_buffer;
};

void Application::run() {
  Stopwatch local_time, total_time;

  for (size_t run = 0; run < opts.num_runs; run++) {

    dbtoaster::data_t data;
    std::cout << "-------------" << std::endl;

    init();

    std::cout << "1. On begin of processing... " << std::flush;
    local_time.restart();
    onBeginProcessing(data);
    local_time.stop();
    std::cout << local_time.elapsedMilliSec() << " ms" << std::endl;

    std::cout << "2. Processing tables... " << std::flush;
    local_time.restart();
    processTables(data);
    local_time.stop();
    std::cout << local_time.elapsedMilliSec() << " ms" << std::endl;
    
    total_time.restart();

    std::cout << "3. On system ready... " << std::flush;
    local_time.restart();
    processOnSystemReady(data);
    local_time.stop();
    std::cout << local_time.elapsedMilliSec() << " ms" << std::endl;

    std::cout << "4. Processing streams... " << std::flush;;
    local_time.restart();
    processStreams(data);
    local_time.stop();
    std::cout << local_time.elapsedMilliSec() << " ms" << std::endl;

    std::cout << "5. On end of processing... " << std::flush;
    local_time.restart();
    onEndProcessing(data, opts.print_result);
    local_time.stop();
    std::cout << local_time.elapsedMilliSec() << " ms" << std::endl;

    total_time.stop();

    std::cout << "    Run: " << run
              << "    Processed: " << data.tN
              << "    Skipped: " << data.tS
              << "    Execution time: " << total_time.elapsedMilliSec() << " ms"
#ifdef BATCH_SIZE
              << "    Batch size: " << BATCH_SIZE
#endif
              << std::endl
              << "-------------"
              << std::endl;

    std::cout << "SAMPLE = "
              << run << ", " 
              << total_time.elapsedMilliSec() * 1000 << ", " 
              << data.tN << ", " 
              << data.tS << std::endl;

    close();
  }
}

#endif /* DRIVER_APPLICATION_HPP */