#pragma once 

#include <vector>
#include <string>

namespace microbench {

struct Result {
    std::string benchmarkName;

    std::vector<double> rawWallTimes;
    std::vector<double> rawCpuTimes; 
    
    double meanWallTime;
    double p50WallTime;
    double meanCPUTime;
    double p50CPUTime;
    double p95WallTime;
    double p99WallTime;
    double p95CpuTime;
    double p99CpuTime;

    int totalIterations;
};


class Reporter {
    public:

    // Crucial to provide virtual destructor for abstract base classes
    virtual ~Reporter() {}

    virtual void print(const Result& result) = 0;
};

}
