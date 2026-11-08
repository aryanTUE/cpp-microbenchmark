#pragma once

#include <vector>
#include "microbench/benchmark.h"

namespace microbench {

class Registry {
public:
    // Global access point for single memory instance
    static Registry& getInstance() {
        static Registry instance;
        return instance; 
    }

    // Delete copy/move constructors to strictly enforce the Singleton pattern (Meyers' Singleton)
    Registry(const Registry&) = delete; 
    Registry& operator=(const Registry&) = delete; 

    // Adds a new test to the list
    void registerBenchmark(const Benchmark& benchmark) {
        benchmarks_.push_back(benchmark); 
    }

    // Provides the Runner with the complete list of tests to execute
    const std::vector<Benchmark>& getBenchmarks() const {
        return benchmarks_;
    }

private:
    // Private constructor prevents calls like 'new Registry()'
    Registry() = default; 

    std::vector<Benchmark> benchmarks_;
};


// Helper class whose only role is to call the Registry in its constructor
class BenchmarkRegisterer {
public:
    BenchmarkRegisterer(const Benchmark& benchmark) {
        Registry::getInstance().registerBenchmark(benchmark); 
    }    
};

}

// 1. Helper macros required to expand __LINE__ into an actual number
#define MICROBENCH_CONCAT_INTERNAL(a, b) a##b
#define MICROBENCH_CONCAT(a, b) MICROBENCH_CONCAT_INTERNAL(a, b)

// 2. Updated macros appending the line number to ensure unique variable names
#define BENCHMARK(FuncName) \
    static ::microbench::BenchmarkRegisterer \
    MICROBENCH_CONCAT(benchmark_registerer_, __LINE__)(::microbench::Benchmark{#FuncName, FuncName, 1.0})

#define BENCHMARK_WITH_DURATION(FuncName, DurationSec) \
    static ::microbench::BenchmarkRegisterer \
    MICROBENCH_CONCAT(benchmark_registerer_, __LINE__)(::microbench::Benchmark{#FuncName, FuncName, DurationSec})

#define BENCHMARK_ADVANCED(FuncName, DurationSec, Repetitions) \
    static ::microbench::BenchmarkRegisterer \
    MICROBENCH_CONCAT(benchmark_registerer_, __LINE__)(::microbench::Benchmark{#FuncName, FuncName, DurationSec, Repetitions})