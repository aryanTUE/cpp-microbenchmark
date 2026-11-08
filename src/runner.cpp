#include "microbench/runner.h"
#include "microbench/registry.h"
#include "microbench/state.h"
#include "microbench/stats.h"
#include <vector>

namespace microbench {

Runner::Runner(Reporter& reporter) : reporter_(reporter) {}

void Runner::run() {
    for (const Benchmark& benchmark : Registry::getInstance().getBenchmarks()) {
        std::vector<double> wallTimes;
        std::vector<double> cpuTimes;
        size_t totalItersAcrossReps = 0;

        // Run the benchmark multiple times to build a distribution dataset
        for (size_t r = 0; r < benchmark.repetitions; ++r) {
            State state(benchmark.targetDurationSec);
            benchmark.testLambda(state);
            
            size_t iterations = state.getIterations(); 
            if (iterations == 0) continue;

            totalItersAcrossReps += iterations;
            
            // Store the mean time for this specific repetition
            wallTimes.push_back(state.getTotalWallTimeNs() / static_cast<double>(iterations));
            cpuTimes.push_back(state.getTotalCpuTimeNs() / static_cast<double>(iterations));
        }

        // Protect against empty runs where all loops instantly exited
        if (wallTimes.empty() || cpuTimes.empty()) {
            continue;
        }

        Result result;
        result.benchmarkName = benchmark.name;
        result.totalIterations = totalItersAcrossReps;
        
        // Pass the raw data arrays to the reporter
        result.rawWallTimes = wallTimes; 
        result.rawCpuTimes = cpuTimes; 

        // Extract statistics using the generic template
        result.meanWallTime = stats::getMean(wallTimes);
        result.p50WallTime = stats::getPercentile(wallTimes, 50.0);
        result.p95WallTime = stats::getPercentile(wallTimes, 95.0);
        result.p99WallTime = stats::getPercentile(wallTimes, 99.0);

        result.meanCPUTime = stats::getMean(cpuTimes);
        result.p50CPUTime = stats::getPercentile(cpuTimes, 50.0);
        result.p95CpuTime = stats::getPercentile(cpuTimes, 95.0);
        result.p99CpuTime = stats::getPercentile(cpuTimes, 99.0);

        reporter_.print(result);
    }
}

} // namespace microbench
