#include <benchmark/benchmark.h>

#include <cstdint>
#include <numeric>
#include <vector>

namespace {

void BM_VectorSum(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const std::vector<int> values(n, 1);

  for (auto _ : state) {
    int64_t sum = std::accumulate(values.begin(), values.end(), int64_t{0});
    benchmark::DoNotOptimize(sum);
  }

  state.SetItemsProcessed(static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(n));
  state.SetBytesProcessed(
      static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(n * sizeof(values[0])));
}

}  // namespace

BENCHMARK(BM_VectorSum)->RangeMultiplier(2)->Range(1 << 10, 1 << 20);
