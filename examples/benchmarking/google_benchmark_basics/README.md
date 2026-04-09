# Google Benchmark Basics

These examples are intentionally minimal and build on each other:

1. `01_minimal_benchmark.cpp`
   - Smallest useful benchmark setup.
2. `02_measure_work_and_avoid_optimization.cpp`
   - Measures real work and uses `benchmark::DoNotOptimize`.
3. `03_parameterize_input_size.cpp`
   - Adds input-size ranges and reports throughput (`items` and `bytes`).
4. `04_compare_two_approaches.cpp`
   - Benchmarks two implementations side-by-side on the same ranges.
5. `05_compare_numeric_types.cpp`
   - Compares summing `int`, `float`, and `double` across input sizes.

From `examples/benchmarking`, you can build and run:

```bash
cmake -S . -B build-host -DCMAKE_BUILD_TYPE=Release
cmake --build build-host --target gb_basic_01 gb_basic_02 gb_basic_03 gb_basic_04 gb_basic_05

./build-host/google_benchmark_basics/gb_basic_01
./build-host/google_benchmark_basics/gb_basic_02
./build-host/google_benchmark_basics/gb_basic_03
./build-host/google_benchmark_basics/gb_basic_04
./build-host/google_benchmark_basics/gb_basic_05
```
