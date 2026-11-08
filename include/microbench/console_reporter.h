#pragma once

#include "microbench/reporter.h" // Assumes Reporter has: virtual void print(const Result&) = 0;
#include <iostream>
#include <iomanip>

namespace microbench {

class ConsoleReporter : public Reporter {
public:
    void print(const Result& result) override;

private:
    bool headerPrinted_ = false;
};

}