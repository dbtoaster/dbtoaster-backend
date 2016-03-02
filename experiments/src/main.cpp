#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <sched.h>

#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "stopwatch.hpp"
#include "serialization.hpp"

using namespace std;

// #include "tpch/tpch.hpp"
// #include "tpch/tpch_template.hpp"

#include "tpcds/tpcds.hpp"
#include "tpcds/tpcds_template.hpp"

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
    for (int run = 0; run < 3; run++) 
    {
    //    std::cout << "Press ENTER...";
    //    char ch;
    //    std::cin >> ch;

        data_t data;

        std::cout << "Processing tables ... " << std::flush;
        process_table_batches(data);
        std::cout << "Done! " << std::endl;

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

    Stopwatch sw;
    for (int run = 0; run < 3; run++) 
    {
    //    std::cout << "Press ENTER...";
    //    char ch;
    //    std::cin >> ch;

        data_t data;

        std::cout << "Processing tables... " << std::flush;
        process_tables(data);
        std::cout << "Done! " << std::endl;

        sw.restart();

        std::cout << "OnSystemReady... " << std::flush;
        data.on_system_ready_event();        
        std::cout << "Done! " << std::endl;

        std::cout << "Processing streams... " << std::flush;;
        process_streams(data);
        std::cout << "Done! " << std::endl;

        sw.stop();

        print_result(data);
        
        std::cout << "Processed: " << data.tN 
                  << "    Skipped: " << data.tS 
                  << "    Execution time: " << sw.elapsedTimeInMilliSeconds() << " ms" 
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
