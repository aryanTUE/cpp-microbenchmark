#include "microbench/state.h"
#include "microbench/timer.h" // for GetWallTimeNs()

namespace microbench {

State::State(double targetDurationSec) : targetDurationSec_(targetDurationSec) {}

bool State::keepRunning() {
    // Phase 1: Warm-up, i.e. run a fixed number of iterations without tracking
    if (isWarmup_) {
        warmupIterations_++;
        if (warmupIterations_ >= MAX_WARMUP_ITERATIONS) {
            isWarmup_ = false; 
            // Warm up is complete; start actual timer
            startWallTimeNs_ = timer::getWallTimeNs();
            startCpuTimeNs_  = timer::getCPUTimeNs(); 
        }

        return true; 
    }

    // Increment iterations at the start of the timing phase
    iterations_++;

    // BATCHING: Only query the slow OS clock every so many iterations
    constexpr size_t BATCH_SIZE = 1000;
    if (iterations_ % BATCH_SIZE != 0) {
        return true; 
    }

    // Phase 2: Timing, calculate how much time has passed
    double currentWallTimeNs = timer::getWallTimeNs();
    double currentCpuTimeNs = timer::getCPUTimeNs();
    double elapsedSec = (currentWallTimeNs - startWallTimeNs_) / 1e9; 
    
    // Terminate when target duration is reached
    if (elapsedSec >= targetDurationSec_) {
        // Time is up. Freeze the final totals before exiting.
        totalWallTimeNs_ = currentWallTimeNs - startWallTimeNs_;
        totalCpuTimeNs_  = currentCpuTimeNs - startCpuTimeNs_;
        return false; 
    }

    return true; 
}

size_t State::getIterations() const { return iterations_; }
double State::getTotalWallTimeNs() const { return totalWallTimeNs_; }
double State::getTotalCpuTimeNs() const { return totalCpuTimeNs_; }

}
