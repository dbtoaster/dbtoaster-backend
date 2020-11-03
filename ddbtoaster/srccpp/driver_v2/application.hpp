#ifndef DRIVER_APPLICATION_HPP
#define DRIVER_APPLICATION_HPP

#include <iostream>
#include <memory>
#include <type_traits>
#include "runtime_opts.hpp"
#include "stopwatch.hpp"
#include "source.hpp"
#include "dispatcher.hpp"
#include "multiplexer.hpp"
#include "multiplexer_factory.hpp"

class Application {
  public:
    Application(const RuntimeOpts& _opts) : opts(_opts) { }

    ~Application() { close_multiplexers(); }

    void run();
    
  protected:
    using Multiplexer = std::conditional<data_sources_t::ordered_dataset,
                                         OrderedMultiplexer,
                                         RoundRobinMultiplexer>::type;

    using MultiplexerFactory = std::conditional<data_sources_t::ordered_dataset,
                                                OrderedMultiplexerFactory,
                                                RoundRobinMultiplexerFactory>::type;

    void open_multiplexers(dbtoaster::data_t& data) {
        MultiplexerFactory factory;
        dbtoaster::data_sources_t::visit_triggers(factory);
        static_multiplexer = factory.create_static_multiplexer(data, opts.preload_input);
        dynamic_multiplexer = factory.create_dynamic_multiplexer(data, opts.preload_input);
        static_multiplexer->open();
        dynamic_multiplexer->open();
    }

    void close_multiplexers() {
        static_multiplexer->close();
        dynamic_multiplexer->close();
    }

    void process_tables(dbtoaster::data_t& data) {
        while (static_multiplexer->next()) { }
    }

    void process_on_system_ready(dbtoaster::data_t& data) {
        data.on_system_ready_event();
    }

    void process_streams(dbtoaster::data_t& data) {
        if (opts.snapshot_interval > 0)
            process_streams_snapshot(data, opts.snapshot_interval);
        else
            process_streams_no_snapshot(data);
    }

    void process_streams_snapshot(dbtoaster::data_t& data, long snapshot_interval) {
        long next_snapshot = 0;

        while (dynamic_multiplexer->next()) {

            if (data.tN >= next_snapshot) {
                on_snapshot(data);
                next_snapshot = data.tN + snapshot_interval;
            }
        }

        if (next_snapshot != data.tN + snapshot_interval) {
            on_snapshot(data);
        }
    }

    void process_streams_no_snapshot(dbtoaster::data_t& data) {
        while (dynamic_multiplexer->next()) { }
    }

    void on_snapshot(dbtoaster::data_t& data) {
        on_end_processing(data, false);
    }

    void on_begin_processing(dbtoaster::data_t& data) {

    }

    void on_end_processing(dbtoaster::data_t& data, bool print_result) {
        if (print_result) {
            cout << "<snap>\n";
            data.serialize(std::cout);
            cout << "\n</snap>" << endl;
        }    
    }

    RuntimeOpts opts;
    unique_ptr<Multiplexer> static_multiplexer;
    unique_ptr<Multiplexer> dynamic_multiplexer;
};

void Application::run() {
    Stopwatch local_time, total_time;

    for (size_t run = 0; run < opts.num_runs; run++) {

        dbtoaster::data_t data;

        std::cout << "-------------" << std::endl;

        open_multiplexers(data);

        std::cout << "1. On begin of processing... " << std::flush;
        local_time.restart();
        on_begin_processing(data);
        local_time.stop();
        std::cout << local_time.elapsed_time_ms() << " ms" << std::endl;

        std::cout << "2. Processing tables... " << std::flush;
        local_time.restart();
        process_tables(data);
        local_time.stop();
        std::cout << local_time.elapsed_time_ms() << " ms" << std::endl;
        
        total_time.restart();

        std::cout << "3. On system ready... " << std::flush;
        local_time.restart();
        process_on_system_ready(data);
        local_time.stop();
        std::cout << local_time.elapsed_time_ms() << " ms" << std::endl;

        std::cout << "4. Processing streams... " << std::flush;;
        local_time.restart();
        process_streams(data);
        local_time.stop();
        std::cout << local_time.elapsed_time_ms() << " ms" << std::endl;

        std::cout << "5. On end of processing... " << std::flush;
        local_time.restart();
        on_end_processing(data, opts.print_result);
        local_time.stop();
        std::cout << local_time.elapsed_time_ms() << " ms" << std::endl;

        total_time.stop();

        std::cout << "    Run: " << run
                  << "    Processed: " << data.tN
                  << "    Skipped: " << data.tS
                  << "    Execution time: " << total_time.elapsed_time_ms() << " ms"
#ifdef BATCH_SIZE
                  << "    Batch size: " << BATCH_SIZE
#endif
                  << std::endl
                  << "-------------"
                  << std::endl;

        std::cout << "SAMPLE = "
                  << run << ", " 
                  << total_time.elapsed_time_ms() * 1000 << ", " 
                  << data.tN << ", " 
                  << data.tS << std::endl;

        close_multiplexers();
    }
}

#endif /* DRIVER_APPLICATION_HPP */