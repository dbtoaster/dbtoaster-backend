#ifndef DRIVER_STOPWATCH_HPP
#define DRIVER_STOPWATCH_HPP

#include <sys/time.h>
#include <cmath>

class Stopwatch {
  public:
    Stopwatch() : start_time(0), end_time(0) { }

    void restart() {
      timeval curr_time;
      gettimeofday(&curr_time, NULL);
      start_time = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
    }

    void stop() {
      timeval curr_time;
      gettimeofday(&curr_time, NULL);
      end_time = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
    }

    long elapsedMilliSec() {
      return end_time - start_time;
    }

    long elapsedSec() {
      return std::lround((end_time - start_time) / 1000.0);
    }

  private:
    long start_time;
    long end_time;
};
#endif /* DRIVER_STOPWATCH_HPP */