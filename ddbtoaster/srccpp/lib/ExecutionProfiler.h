#ifndef EXECUTIONPROFILER_H
#define EXECUTIONPROFILER_H
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <fstream>
#define EXEC_PROFILE 1
using std::chrono::high_resolution_clock;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::nanoseconds;
typedef system_clock::time_point Timepoint;
#ifdef DTIMER
#define DNow high_resolution_clock::now()
#define DDurationMS(x) std::chrono::duration_cast<milliseconds>(x).count()
#define DDurationUS(x) std::chrono::duration_cast<microseconds>(x).count()
#define DDurationNS(x) std::chrono::duration_cast<nanoseconds>(x).count()
#else
#define DNow 0
#define DDurationMS(x) 0
#define DDurationUS(x) 0
#define DDurationNS(x) 0
#endif

#define Now high_resolution_clock::now()
#define DurationMS(x) std::chrono::duration_cast<milliseconds>(x).count()
#define DurationUS(x) std::chrono::duration_cast<microseconds>(x).count()
#define DurationNS(x) std::chrono::duration_cast<nanoseconds>(x).count()
#include <string>
#pragma once

#ifdef EXEC_PROFILE
extern std::unordered_map<std::string, Timepoint> startTimes;
extern std::unordered_map<std::string, size_t> durations;
extern std::unordered_map<std::string, size_t> counters;
#endif

struct ExecutionProfiler {

    static void startProfile(std::string name) {
#ifdef EXEC_PROFILE
        Timepoint &st = startTimes[name];
        st = Now;
#endif
    }

    static void endProfile(std::string name) {
#ifdef EXEC_PROFILE
        auto end = Now;
        auto start = startTimes[name];
        if (durations.find(name) == durations.end()) {
            durations[name] = DurationNS(end - start);
            counters[name] = 1;
        } else {
            durations[name] += DurationNS(end - start);
            counters[name]++;
        }
#endif
    }

    static void printProfile() {
        std::cout << "Profile Results :: " << std::endl;
#ifdef EXEC_PROFILE
        for (auto it : durations) {
            std::cout << it.first << "   count = " << counters[it.first] << " time = " << it.second / 1000000.0 << " ms    avg time = " << it.second / counters[it.first] << " ns" << std::endl;
        }

#endif
    }

    static void printProfileToFile() {
#ifdef EXEC_PROFILE
        std::ofstream fout("profile.csv", std::ios::app);
        fout << ",count,timeMS,avgTimeNS" << std::endl;

        for (auto it : durations) {
            fout << it.first << "," << counters[it.first] << "," << it.second / 1000000.0 << "," << it.second / counters[it.first] << std::endl;
        }
        fout.close();
#endif
    }
};

#endif /* EXECUTIONPROFILER_H */

