#include "microbench/timer.h"
#include <time.h> // Low-level POSIX time API

namespace microbench::timer {

double getWallTimeNs() {
    // timespec holds whole seconds (tv_sec) and left over nanoseconds (tv_nsec)
    struct timespec ts;

    // CLOCK_MONOTONIC is a stopwatch that only ticks forward
    clock_gettime(CLOCK_MONOTONIC, &ts); 

    // Convert seconds to nanoseconds and add the leftover nanoseconds
    return (static_cast<double>(ts.tv_sec) * 1e9) + static_cast<double>(ts.tv_nsec);
}

double getCPUTimeNs() {
    // timespec holds whole seconds (tv_sec) and left over nanoseconds (tv_nsec)
    struct timespec ts; 

    // CLOCK_THREAD_CPUTIME_ID only ticks when THIS specific thread is executing instructions
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts); 

    // Convert seconds to nanoseconds and add the leftover nanoseconds
    return (static_cast<double>(ts.tv_sec) * 1e9) + static_cast<double>(ts.tv_nsec);
}

}