#include "microbench/registry.h"
#include "microbench/runner.h"
#include "microbench/console_reporter.h"
#include "microbench/state.h"
#include <vector>

void testVectorPushBack(microbench::State& state) {
    while (state.keepRunning()) {
        std::vector<int> v;
        for (int i = 0; i < 1000; ++i) {
            v.push_back(i);
        }
    }
}

// 1. Default: 1.0s duration, 10 repetitions
BENCHMARK(testVectorPushBack);

// 2. Custom Duration: 2.5s duration, 10 repetitions
BENCHMARK_WITH_DURATION(testVectorPushBack, 2.5);

// 3. Advanced: 0.5s duration, 50 repetitions (Tests percentile accuracy)
BENCHMARK_ADVANCED(testVectorPushBack, 0.5, 50);

int main() {
    microbench::ConsoleReporter reporter;
    microbench::Runner runner(reporter);
    runner.run();
    return 0;
}