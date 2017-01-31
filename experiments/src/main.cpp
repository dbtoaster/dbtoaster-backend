#include <sched.h>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "stopwatch.hpp"
#include "serialization.hpp"

using namespace std;
using namespace dbtoaster;

#ifdef BATCH_MODE

void RunQuery() 
{
    std::cout << "-------------" << std::endl;

    size_t batchSize = BATCH_SIZE;

    load_relations();    

    std::cout << "Forming batches... " << std::flush;
    convert_tables_to_batches(batchSize);    
    convert_streams_to_batches(batchSize);    
    std::cout << "Done!" << std::endl;

    destroy_relations();

    Stopwatch sw;
    for (int run = 0; run < NUMBER_OF_RUNS; run++) 
    {
    //    std::cout << "Press ENTER...";
    //    char ch;
    //    std::cin >> ch;

        data_t data;

        std::cout << "Processing tables ... " << std::flush;
        process_table_batches(data);
        std::cout << "Done! " << std::endl;

        gettimeofday(&data.t0,NULL);

        sw.restart();

        std::cout << "OnSystemReady... " << std::flush;
        data.on_system_ready_event();
        std::cout << "Done! " << std::endl;

        std::cout << "Processing streams... " << std::flush;
        process_stream_batches(data);
        std::cout << "Done! " << std::endl;

        sw.stop();

        print_result(data);

        std::cout << "Processed: " << data.tN 
                  << "    Skipped: " << data.tS 
                  << "    Execution time: " << sw.elapsedTimeInMilliSeconds() << " ms" 
                  << "    Batch size: " << batchSize
                  << std::endl;        
    }   
}

#else

void RunQuery() 
{
    std::cout << "-------------" << std::endl;

    load_relations();

    Stopwatch sw, local_sw;
    for (int run = 0; run < NUMBER_OF_RUNS; run++) 
    {
    //    std::cout << "Press ENTER...";
    //    char ch;
    //    std::cin >> ch;

        data_t data;

        std::cout << "-------------" << std::endl;

        local_sw.restart();
        std::cout << "1. Processing tables... " << std::flush;
        process_tables(data);
        local_sw.stop();
        std::cout << local_sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        gettimeofday(&data.t0,NULL);

        sw.restart();

        local_sw.restart();
        std::cout << "2. OnSystemReady... " << std::flush;
        data.on_system_ready_event();
        local_sw.stop();
        std::cout << local_sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        local_sw.restart();
        std::cout << "3. Processing streams... " << std::flush;;
        process_streams(data);
        local_sw.stop();
        std::cout << local_sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        sw.stop();

        print_result(data);
        
        std::cout << "Run: " << run 
                  << "    Processed: " << data.tN 
                  << "    Skipped: " << data.tS 
                  << "    Execution time: " << sw.elapsedTimeInMilliSeconds() << " ms" 
                  << std::endl
                  << "-------------"
                  << std::endl;
    }

    destroy_relations();
}

#endif

int main()
{

#ifndef __APPLE__
    cpu_set_t  mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
#endif

    RunQuery();
    return 0;
}
    