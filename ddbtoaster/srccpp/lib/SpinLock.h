#pragma once
#ifndef __COMMON_SPIN_LOCK_H__
#define __COMMON_SPIN_LOCK_H__
#include <atomic>

class SpinLock {
    std::atomic_flag lock_;
public:

    SpinLock() {
        lock_.clear();
    }

    inline void lock() {
        while (lock_.test_and_set(std::memory_order_acquire));
    }

    inline void unlock() {
        lock_.clear(std::memory_order_release);
    }

    inline bool try_lock() {
        return !lock_.test_and_set(std::memory_order_acquire);
    }

};

#endif
