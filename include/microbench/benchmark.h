#pragma once

#include <string>
#include <functional>
#include "microbench/state.h"

namespace microbench {

struct Benchmark {
    std::string_view name; 

    // Stores any function or lambda that returns void and accepts a State reference
    std::function<void(State&)> testLambda; 

    // Default that the user can override
    double targetDurationSec = 1.0; 

    size_t repetitions = 10;
};

}