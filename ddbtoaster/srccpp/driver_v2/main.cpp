#include <iostream>
#include "runtime_opts.hpp"
#include "application.hpp"

using namespace std;

void show_help() {
    cout << endl;
    cout << "Runtime options:" << endl;
    cout << "---------------" << endl;
    cout << "  --help | -h \t\t show help message" << endl; 
    cout << "  --num-runs <arg> \t number of runs (short -r)" << endl; 
    cout << "  --no-output \t\t omit printing final result" << endl;
    cout << "  --preload \t\t preload input into memory before streaming" << endl;
    cout << "  --snapshot-interval <arg> \t snapshot frequency" << endl;
    cout << endl;
}

int main(int argc, char** argv) {

    RuntimeOpts opts;
    
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            show_help();
            exit(0);
        }
        else if ((strcmp(argv[i], "--num-runs") == 0 || strcmp(argv[i], "-r") == 0) && i + 1 < argc) {
            opts.num_runs = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--no-output") == 0) {
            opts.print_result = false;
        }
        else if (strcmp(argv[i], "--preload") == 0) {
            opts.preload_input = true;
        }
        else if (strcmp(argv[i], "--snapshot-interval") == 0 && i + 1 < argc) {
            opts.snapshot_interval = atol(argv[++i]);
        }
    }

    Application app(opts);
    app.run();

    return 0;
}