cmake_minimum_required(VERSION 3.14)
project(allocators_pmr_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(pmr_basic pmr_basic.cpp)
add_executable(pmr_monotonic pmr_monotonic.cpp)
add_executable(pmr_containers pmr_containers.cpp)

# --- Google Benchmark (for pmr_benchmark only) ---
include(FetchContent)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3
)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(pmr_benchmark pmr_benchmark.cpp)
target_link_libraries(pmr_benchmark PRIVATE benchmark::benchmark_main)
