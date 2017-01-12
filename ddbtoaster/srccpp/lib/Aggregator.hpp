#ifndef AGGREGATOR_HPP
#define AGGREGATOR_HPP
#include <functional>

template <typename E, typename R>
struct MinAggregator {
    E** minEntry;
    R minRes;
    std::function<R(E*) > func;
    bool first;

    MinAggregator(const std::function<R(E*) >& f, E**res) : minEntry(res), func(f), first(true) {
    }

    void operator()(E* e) {
        if (first) {
            first = false;
            minRes = func(e);
            *minEntry = e;
        } else {
            R val = func(e);
            if (minRes > val) {
                minRes = val;
                *minEntry = e;

            }
        }
    }

};

template <typename E, typename R>
struct MaxAggregator {
    E** maxEntry;
    R maxRes;
    std::function<R(E*) > func;
    bool first;

    MaxAggregator(const std::function<R(E*) >& f, E**res) : maxEntry(res), func(f), first(true) {
    }

    void operator()(E* e) {
        if (first) {
            first = false;
            maxRes = func(e);
            *maxEntry = e;
        } else {
            R val = func(e);
            if (maxRes < val) {
                maxRes = val;
                *maxEntry = e;

            }
        }
    }

};
#endif