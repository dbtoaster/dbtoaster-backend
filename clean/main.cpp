#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "stopwatch.hpp"
#include "serialization.hpp"

using namespace std;

#include "test/tpch.hpp"
#include "test/tpch_template.hpp"

using namespace dbtoaster;

void RunQuery() 
{
    load_relations();

    Stopwatch sw;
    for (int run = 0; run < 5; run++) 
    {
        std::cout << "Press ENTER...";
        char ch;
        std::cin >> ch;

        data_t data;

        sw.restart();

        process_tables(data);
        data.on_system_ready_event();
        process_streams(data);

        sw.stop();

        print_result(data);
        
        std::cout << "Execution time: " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;        
    }

    destroy_relations();
}

int main()
{
    RunQuery();
    return 0;
}
