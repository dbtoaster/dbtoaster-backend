#ifndef DRIVER_RUNTIME_OPTS_HPP
#define DRIVER_RUNTIME_OPTS_HPP

struct RuntimeOpts {
  RuntimeOpts() : num_runs(1), 
                  print_result(true),
                  preload_input(false),
                  snapshot_interval(0) { }

  size_t num_runs;
  bool print_result;
  bool preload_input;
  long snapshot_interval;
};

#endif /* DRIVER_RUNTIME_OPTS_HPP */