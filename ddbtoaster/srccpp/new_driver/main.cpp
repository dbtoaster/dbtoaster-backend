#include <iostream>
#include <cstring>
#include "runtime_opts.hpp"
#include "application.hpp"

using namespace std;

void showHelp() {
  cout << "\nRuntime options:\n";
  cout << "---------------\n";
  cout << "  --help | -h \t\t show help message\n"; 
  cout << "  --num-runs <arg> \t number of runs (short -r)\n";
  cout << "  --batch-size <arg> \t update batch size (short -b)\n";
  cout << "  --no-output \t\t omit printing final result\n";
  cout << "  --preload \t\t preload input into memory before streaming\n";
  cout << "  --snapshot-interval <arg> \t snapshot frequency\n";
  cout << endl;
}

int main(int argc, char** argv) {

  RuntimeOpts opts;
    
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      showHelp();
      exit(0);
    }
    else if ((strcmp(argv[i], "--num-runs") == 0 ||
              strcmp(argv[i], "-r") == 0) && i + 1 < argc) {
      opts.num_runs = atoi(argv[++i]);
    }
    else if ((strcmp(argv[i], "--batch-size") == 0 ||
              strcmp(argv[i], "-b") == 0) && i + 1 < argc) {
      opts.batch_size = atoi(argv[++i]);
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