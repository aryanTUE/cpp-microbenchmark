#pragma once

#include "microbench/reporter.h"

namespace microbench {

class Runner {
public:
    // Dependency injection: Runner requires a Reporter to exist
    explicit Runner(Reporter& reporter);

    // Iterates through registry, runs the tests, reports the math
    void run();

private:
    // Stored as a reference because a Runner must ALWAYS have a Reporter 
    Reporter& reporter_;
};

}