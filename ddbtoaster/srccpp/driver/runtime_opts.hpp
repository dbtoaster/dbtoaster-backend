#ifndef DRIVER_RUNTIME_OPTS_HPP
#define DRIVER_RUNTIME_OPTS_HPP

struct RuntimeOpts {
  RuntimeOpts() : num_runs(1), 
                  batch_size(0),
                  print_result(true),
                  preload_input(false),
                  log_count(0) { }

  size_t num_runs;
  size_t batch_size;
  bool print_result;
  bool preload_input;
  size_t log_count;
};

#endif /* DRIVER_RUNTIME_OPTS_HPP */