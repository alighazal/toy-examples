cmake_minimum_required(VERSION 3.14)
project(virtual_dispatch_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make compilation flags explicit by build type.
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

include(FetchContent)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3
)
FetchContent_MakeAvailable(googlebenchmark)

set(KNOW_YOUR_HARDWARE_BIN_DIR "${CMAKE_BINARY_DIR}/know_your_hardware")
set(BRANCHLESS_BIN_DIR "${KNOW_YOUR_HARDWARE_BIN_DIR}/Branchless_computing")

add_executable(cache_ben "know_your_hardware/cache_ben.cpp")
target_compile_options(cache_ben PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(cache_ben PRIVATE benchmark::benchmark_main)
set_target_properties(cache_ben PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${KNOW_YOUR_HARDWARE_BIN_DIR}")

add_executable(vf "know_your_hardware/vf.cpp")
target_compile_options(vf PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(vf PRIVATE benchmark::benchmark_main)
set_target_properties(vf PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${KNOW_YOUR_HARDWARE_BIN_DIR}")

add_executable(DoD "know_your_hardware/DoD.cpp")
target_compile_options(DoD PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(DoD PRIVATE benchmark::benchmark_main)
set_target_properties(DoD PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${KNOW_YOUR_HARDWARE_BIN_DIR}")

file(GLOB BRANCHLESS_SOURCES
  "know_your_hardware/Branchless_computing/*.C"
)

foreach(branchless_source IN LISTS BRANCHLESS_SOURCES)
  get_filename_component(branchless_name "${branchless_source}" NAME_WE)
  string(REGEX REPLACE "[^A-Za-z0-9_]" "_" branchless_target "${branchless_name}")
  set(branchless_target "bc_${branchless_target}")

  add_executable("${branchless_target}" "${branchless_source}")
  target_compile_options("${branchless_target}" PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries("${branchless_target}" PRIVATE benchmark::benchmark)
  set_target_properties("${branchless_target}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BRANCHLESS_BIN_DIR}")
endforeach()

set(COMPILE_FLAGS_BIN_DIR "${CMAKE_BINARY_DIR}/know_your_tools")

add_executable(flags_O0 "know_your_tools/compile_flags_impact.cpp")
target_compile_options(flags_O0 PRIVATE -Wall -Wextra -Wpedantic -O0)
target_compile_definitions(flags_O0 PRIVATE FLAGS_LABEL="O0")
target_link_libraries(flags_O0 PRIVATE benchmark::benchmark)
set_target_properties(flags_O0 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMPILE_FLAGS_BIN_DIR}")

add_executable(flags_O1 "know_your_tools/compile_flags_impact.cpp")
target_compile_options(flags_O1 PRIVATE -Wall -Wextra -Wpedantic -O1)
target_compile_definitions(flags_O1 PRIVATE FLAGS_LABEL="O1")
target_link_libraries(flags_O1 PRIVATE benchmark::benchmark)
set_target_properties(flags_O1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMPILE_FLAGS_BIN_DIR}")

add_executable(flags_O2 "know_your_tools/compile_flags_impact.cpp")
target_compile_options(flags_O2 PRIVATE -Wall -Wextra -Wpedantic -O2)
target_compile_definitions(flags_O2 PRIVATE FLAGS_LABEL="O2")
target_link_libraries(flags_O2 PRIVATE benchmark::benchmark)
set_target_properties(flags_O2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMPILE_FLAGS_BIN_DIR}")

add_executable(flags_O3 "know_your_tools/compile_flags_impact.cpp")
target_compile_options(flags_O3 PRIVATE -Wall -Wextra -Wpedantic -O3)
target_compile_definitions(flags_O3 PRIVATE FLAGS_LABEL="O3")
target_link_libraries(flags_O3 PRIVATE benchmark::benchmark)
set_target_properties(flags_O3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMPILE_FLAGS_BIN_DIR}")

add_executable(flags_O3_fast_math "know_your_tools/compile_flags_impact.cpp")
target_compile_options(flags_O3_fast_math PRIVATE -Wall -Wextra -Wpedantic -O3 -ffast-math)
target_compile_definitions(flags_O3_fast_math PRIVATE FLAGS_LABEL="O3+ffast-math")
target_link_libraries(flags_O3_fast_math PRIVATE benchmark::benchmark)
set_target_properties(flags_O3_fast_math PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMPILE_FLAGS_BIN_DIR}")

add_executable(flags_O3_march_native "know_your_tools/compile_flags_impact.cpp")
target_compile_options(flags_O3_march_native PRIVATE -Wall -Wextra -Wpedantic -O3 -march=native)
target_compile_definitions(flags_O3_march_native PRIVATE FLAGS_LABEL="O3+march=native")
target_link_libraries(flags_O3_march_native PRIVATE benchmark::benchmark)
set_target_properties(flags_O3_march_native PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMPILE_FLAGS_BIN_DIR}")

add_executable(flags_O3_fast_math_march_native "know_your_tools/compile_flags_impact.cpp")
target_compile_options(flags_O3_fast_math_march_native PRIVATE -Wall -Wextra -Wpedantic -O3 -ffast-math -march=native)
target_compile_definitions(flags_O3_fast_math_march_native PRIVATE FLAGS_LABEL="O3+ffast-math+march=native")
target_link_libraries(flags_O3_fast_math_march_native PRIVATE benchmark::benchmark)
set_target_properties(flags_O3_fast_math_march_native PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMPILE_FLAGS_BIN_DIR}")

set(KNOW_YOUR_LANGUAGE_BIN_DIR "${CMAKE_BINARY_DIR}/know_your_language")

add_executable(ky_language_dispatch
  "know_your_language/dispatch_benchmark.cpp"
  "know_your_language/G15_Procedural_Solution.cpp"
  "know_your_language/G15_Object_Oriented_Solution.cpp"
  "know_your_language/G16_Cyclic_Visitor.cpp"
  "know_your_language/G17_Visitor.cpp"
)
target_compile_options(ky_language_dispatch PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(ky_language_dispatch PRIVATE benchmark::benchmark_main)
set_target_properties(ky_language_dispatch PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${KNOW_YOUR_LANGUAGE_BIN_DIR}")

set(GOOGLE_BENCHMARK_BASICS_BIN_DIR "${CMAKE_BINARY_DIR}/google_benchmark_basics")

add_executable(gb_basic_01
  "google_benchmark_basics/01_minimal_benchmark.cpp"
)
target_compile_options(gb_basic_01 PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(gb_basic_01 PRIVATE benchmark::benchmark_main)
set_target_properties(gb_basic_01 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GOOGLE_BENCHMARK_BASICS_BIN_DIR}")

add_executable(gb_basic_02
  "google_benchmark_basics/02_measure_work_and_avoid_optimization.cpp"
)
target_compile_options(gb_basic_02 PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(gb_basic_02 PRIVATE benchmark::benchmark_main)
set_target_properties(gb_basic_02 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GOOGLE_BENCHMARK_BASICS_BIN_DIR}")

add_executable(gb_basic_03
  "google_benchmark_basics/03_parameterize_input_size.cpp"
)
target_compile_options(gb_basic_03 PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(gb_basic_03 PRIVATE benchmark::benchmark_main)
set_target_properties(gb_basic_03 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GOOGLE_BENCHMARK_BASICS_BIN_DIR}")

add_executable(gb_basic_04
  "google_benchmark_basics/04_compare_two_approaches.cpp"
)
target_compile_options(gb_basic_04 PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(gb_basic_04 PRIVATE benchmark::benchmark_main)
set_target_properties(gb_basic_04 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GOOGLE_BENCHMARK_BASICS_BIN_DIR}")

add_executable(gb_basic_05
  "google_benchmark_basics/05_compare_numeric_types.cpp"
)
target_compile_options(gb_basic_05 PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(gb_basic_05 PRIVATE benchmark::benchmark_main)
set_target_properties(gb_basic_05 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GOOGLE_BENCHMARK_BASICS_BIN_DIR}")
