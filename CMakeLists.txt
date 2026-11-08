cmake_minimum_required(VERSION 3.15)
# Renamed the project from SweWorkspace to something professional
project(MicroBench VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile the .cpp files into a library named "microbench"
add_library(microbench 
    src/state.cpp 
    src/timer.cpp
    src/runner.cpp
    src/console_reporter.cpp    
)

# Tell the compiler where the public header files are
target_include_directories(microbench PUBLIC include/)

# Enforce strict compiler warnings for quality
target_compile_options(microbench PRIVATE -Wall -Wextra -Wpedantic)

# Build a test executable to try out your framework
add_executable(demo examples/demo.cpp)
target_link_libraries(demo PRIVATE microbench)
