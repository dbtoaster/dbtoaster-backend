#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <sys/time.h>

class Stopwatch {
    private:
        long startTime;
        long endTime;

    public:
        Stopwatch() : startTime(0), endTime(0) { }

        void restart() 
        {
            timeval start_time;
            gettimeofday(&start_time, NULL);
            startTime = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
        }

        void stop() 
        {
            timeval end_time;
            gettimeofday(&end_time, NULL);
            endTime = end_time.tv_sec * 1000 + end_time.tv_usec / 1000;
        }

        long elapsedTimeInMilliSeconds() 
        {
            return endTime - startTime;
        }
};

#endif /* STOPWATCH_HPP */
