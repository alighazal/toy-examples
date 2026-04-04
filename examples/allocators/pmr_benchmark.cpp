// Compare allocator strategies for the same workload: reserve + push_back into a vector of ints.
// We reserve() first so a monotonic arena fits; unbounded growth would exhaust the arena quickly.
// Built with Google Benchmark (see CMakeLists.txt).

#include <array>
#include <benchmark/benchmark.h>
#include <cstddef>
#include <memory_resource>
#include <vector>

namespace {

constexpr int kElements = 100'000;

template <class Vec>
void touch(const Vec& v) {
  benchmark::DoNotOptimize(v.data());
  // Non-const lvalue uses the non-deprecated DoNotOptimize(T&) overload.
  int check = v.front() + v.back();
  benchmark::DoNotOptimize(check);
}

}  // namespace

static void BM_std_vector(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(kElements);
    for (int i = 0; i < kElements; ++i) {
      v.push_back(i);
    }
    touch(v);
  }
}
BENCHMARK(BM_std_vector);

static void BM_pmr_default(benchmark::State& state) {
  for (auto _ : state) {
    std::pmr::vector<int> v;
    v.reserve(kElements);
    for (int i = 0; i < kElements; ++i) {
      v.push_back(i);
    }
    touch(v);
  }
}
BENCHMARK(BM_pmr_default);

static void BM_pmr_monotonic(benchmark::State& state) {
  for (auto _ : state) {
    alignas(std::max_align_t) std::array<std::byte, 512 * 1024> storage{};
    std::pmr::monotonic_buffer_resource arena{storage.data(), storage.size()};
    std::pmr::vector<int> v{&arena};
    v.reserve(kElements);
    for (int i = 0; i < kElements; ++i) {
      v.push_back(i);
    }
    touch(v);
  }
}
BENCHMARK(BM_pmr_monotonic);

static void BM_pmr_pool(benchmark::State& state) {
  for (auto _ : state) {
    std::pmr::unsynchronized_pool_resource pool{std::pmr::new_delete_resource()};
    std::pmr::vector<int> v{&pool};
    v.reserve(kElements);
    for (int i = 0; i < kElements; ++i) {
      v.push_back(i);
    }
    touch(v);
  }
}
BENCHMARK(BM_pmr_pool);

BENCHMARK_MAIN();
