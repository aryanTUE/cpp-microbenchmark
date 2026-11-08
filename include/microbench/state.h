#pragma once

#include <cstddef> // Required for size_t

namespace microbench {

class State {
public:
    // Runner passes user's target duration when creating the state
    explicit State(double targetDurationSec);

    // Single API method the user calls
    bool keepRunning();

    // Allows the Runner to extract final tally after loop finishes
    size_t getIterations() const; 

    // New getters for the Runner to pull clean, post-warmup times
    double getTotalWallTimeNs() const;
    double getTotalCpuTimeNs() const;

private:
    double targetDurationSec_;
    size_t iterations_ = 0; 

    // Phase management for CPU cache warm-up
    bool isWarmup_ = true; 
    size_t warmupIterations_ = 0;
    const size_t MAX_WARMUP_ITERATIONS = 100; // Sensible default

    // Track starts
    double startWallTimeNs_ = 0.0;
    double startCpuTimeNs_ = 0.0;
    
    // Store final results
    double totalWallTimeNs_ = 0.0;
    double totalCpuTimeNs_ = 0.0; 
};

}