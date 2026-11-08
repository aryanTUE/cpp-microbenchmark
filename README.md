# C++17 Micro-Benchmarking Framework
A lightweight, zero-boilerplate C++17 micro-benchmarking framework designed for precise, sub-microsecond performance measurement. It automatically separates CPU time from Wall time and tracks p99 tail latencies to capture real-world system interference. [Read the full system design document](system_design.md).

## Features
- **Zero-Boilerplate:** Use the `BENCHMARK()` macro for automatic static registration.
- **Statistical Precision:** Automated Mean and percentile tracking.
- **Separated Timers:** Tracks both Wall Time and pure CPU Time via POSIX APIs.
- **Extensible Reporting**: Decoupled `Reporter` interface for terminal tables and can be extended to other formats such as CSV and JSON. 

## Quick Start
Simply write your function and wrap it with the `BENCHMARK()` macro. The framework handles the warmup phases, timing loops and statistical aggregations automatically. 
```
#include "microbench/benchmark.h"
#include <vector>

void testVectorPushBack(microbench::State& state) {
    while (state.keepRunning()) {
        std::vector<int> v;
        for (int i = 0; i < 1000; ++i) {
            v.push_back(i);
        }
    }
}
BENCHMARK(testVectorPushBack);
BENCHMARK_WITH_DURATION(testVectorPushBack, 2.5);
BENCHMARK_ADVANCED(testVectorPushBack, 0.5, 50);
```

### Sample Output
```
Benchmark                   Mean Wall    p50 Wall    p95 Wall    p99 Wall    Mean CPU     p50 CPU     p95 CPU     p99 CPU          Iters
----------------------------------------------------------------------------------------------------------------------------------------
testVectorPushBack         3616.22 ns  3603.73 ns  3709.59 ns  3709.59 ns  3524.11 ns  3503.85 ns  3644.66 ns  3644.66 ns        2767700
testVectorPushBack            3517 ns  3508.15 ns  3535.26 ns  3535.26 ns  3470.58 ns  3463.94 ns  3503.36 ns  3503.36 ns        7109200
testVectorPushBack         3637.63 ns  3637.81 ns  3685.36 ns  3694.21 ns  3490.56 ns  3477.21 ns  3644.31 ns     3663 ns        6876000
```

## Build Instructions
This project uses CMake. To ensure accurate benchmarking, the framework **must** be compiled in `Release` mode. This enables aggressive compiler optimizations, strips out debugging and inlines functions to measure true production performance. 

### Linux / macOS
You must specify the Release type during the configuration step.
```
# 1. Configure in Release mode
cmake -DCMAKE_BUILD_TYPE=Release -B build -S .

# 2. Compile the code
cmake --build build

# 3. Run the executable
./build/micro_benchmark/demo
```

### Windows
You must specify the Release type during the build step. 
```
# 1. Configure the build files
cmake -B build -S .

# 2. Compile in Release mode
cmake --build build --config Release

# 3. Run the executable
.\build\micro_benchmark\Release\demo.exe
```
*Note: Using the MinGW/GCC toolchain is highly recommended on Windows to natively support the POSIX timer implementations.*

## Architecture & Performance Characteristics
This framework was built to measure code at the nanosecond level, which inevitably means measuring the underlying Operating System and hardware. During development, several cross-platform realities were documented:

### 1. The Timer Trap & Iteration Batching
Initially the framework queried `clock.gettime()` on every single iteration. On Linux, this leverages a fast vDSO userspace read. However, on Windows using MinGW, this call is translated into Windows system calls, taking significantly longer and skewing the results.

**Solution:** The `State::keepRunning()` implementation uses iteration batching, only querying the OS clock every 100 or 1000 loops. This amortizes the OS system call penalty to near zero. This did reduce the performance discrepancies but they still exist as explained further.

### 2. OS Memory Allocator Bottleneck
Older Linux hardware often outperformed modern Windows hardware. This exposes the difference between standard library memory allocators. Linux's `glibc` allocator is historically highly optimized, while the default Windows heap manager is heavier. So, to a certain extent this framework is capable of demonstrating that it is able to capture OS-level memory management overhead. 
