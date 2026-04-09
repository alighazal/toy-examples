#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdint>
#include <unordered_set>
#include <vector>

namespace {

std::vector<int> make_values(std::size_t n) {
  std::vector<int> values(n);
  for (std::size_t i = 0; i < n; ++i) {
    values[i] = static_cast<int>(i);
  }
  return values;
}

void BM_LinearSearch(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const std::vector<int> values = make_values(n);

  for (auto _ : state) {
    bool found = std::find(values.begin(), values.end(), static_cast<int>(n - 1)) != values.end();
    benchmark::DoNotOptimize(found);
  }
}

void BM_HashLookup(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const std::vector<int> values = make_values(n);
  const std::unordered_set<int> index(values.begin(), values.end());

  for (auto _ : state) {
    bool found = index.find(static_cast<int>(n - 1)) != index.end();
    benchmark::DoNotOptimize(found);
  }
}

}  // namespace

BENCHMARK(BM_LinearSearch)->RangeMultiplier(4)->Range(1 << 8, 1 << 16);
BENCHMARK(BM_HashLookup)->RangeMultiplier(4)->Range(1 << 8, 1 << 16);
