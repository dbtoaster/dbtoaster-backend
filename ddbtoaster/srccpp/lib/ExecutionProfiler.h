#ifndef EXECUTIONPROFILER_H
#define EXECUTIONPROFILER_H
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <fstream>

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

    FORCE_INLINE static void startProfile(const std::string& name) {
#ifdef EXEC_PROFILE
        Timepoint &st = startTimes[name];
        st = Now;
#endif
    }

    FORCE_INLINE static void endProfile(const std::string& name) {
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

    static void reset() {
#ifdef EXEC_PROFILE
        for (auto it : durations) {
            durations[it.first] = 0;
            counters[it.first] = 0;
        }
#endif
    }

    static void printProfile() {
        std::cout << "Profile Results :: " << std::endl;
#ifdef EXEC_PROFILE
        for (auto it : durations) {
            size_t c = counters[it.first];
            std::cout << it.first << "   count = " << counters[it.first] << " time = " << it.second / 1000000.0 << " ms    avg time = " << (c ? it.second / c : 0) << " ns" << std::endl;
        }
#else
        std::cout << "PROFILE DISABLED" << std::endl;
#endif
    }

    static void printProfileToFile(const std::string& name = "profile.csv") {
#ifdef EXEC_PROFILE
        std::ofstream fout(name, std::ios::app);
        fout << ",count,timeMS,avgTimeNS" << std::endl;

        for (auto it : durations) {
            size_t c = counters[it.first];
            fout << it.first << "," << counters[it.first] << "," << it.second / 1000000.0 << "," << (c ? it.second / c : 0) << std::endl;
        }
        fout.close();
#endif
    }

    static void printProfileToFilePartitioned(int partId, std::unordered_map<std::string, size_t>& DUR, std::unordered_map<std::string, size_t>& COU, const std::string& name = "profile.csv") {
#ifdef EXEC_PROFILE
        std::ofstream fout(name, std::ios::app);
        if (partId == 0)
            fout << ",count,timeMS,avgTimeNS" << std::endl;

        for (auto it : DUR) {
            size_t c = COU[it.first];
            fout << "part-" << partId << ":" << it.first << "," << COU[it.first] << "," << it.second / 1000000.0 << "," << (c ? it.second / c : 0) << std::endl;
        }
        fout.close();
#endif
    }
};

#endif /* EXECUTIONPROFILER_H */

