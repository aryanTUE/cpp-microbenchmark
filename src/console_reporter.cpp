#include "microbench/console_reporter.h"
#include <iostream>
#include <iomanip>

namespace microbench {

void ConsoleReporter::print(const Result& result) {
    if (!headerPrinted_) {
        std::cout << std::left << std::setw(25) << "Benchmark"
                  << std::right << std::setw(12) << "Mean Wall"
                  << std::setw(12) << "p50 Wall"
                  << std::setw(12) << "p95 Wall"
                  << std::setw(12) << "p99 Wall"
                  << std::setw(12) << "Mean CPU"
                  << std::setw(12) << "p50 CPU"
                  << std::setw(12) << "p95 CPU"
                  << std::setw(12) << "p99 CPU"
                  << std::setw(15) << "Iters" << "\n";
        
        std::cout << std::string(136, '-') << "\n";
        headerPrinted_ = true;
    }

    std::cout << std::left << std::setw(25) << result.benchmarkName
              << std::right 
              << std::setw(9) << result.meanWallTime << " ns"
              << std::setw(9) << result.p50WallTime << " ns"
              << std::setw(9) << result.p95WallTime << " ns"
              << std::setw(9) << result.p99WallTime << " ns"
              << std::setw(9) << result.meanCPUTime << " ns"
              << std::setw(9) << result.p50CPUTime << " ns"
              << std::setw(9) << result.p95CpuTime << " ns"
              << std::setw(9) << result.p99CpuTime << " ns"
              << std::setw(15) << result.totalIterations << "\n";
}

} // namespace microbench
