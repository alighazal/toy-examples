#include <benchmark/benchmark.h>

#include <cstddef>
#include <cstdint>
#include <vector>

namespace {

template <typename T>
std::vector<T> make_values(std::size_t n) {
  std::vector<T> values(n);
  for (std::size_t i = 0; i < n; ++i) {
    values[i] = static_cast<T>((i % 101) + 1);
  }
  return values;
}

template <typename T>
void sum_values(const std::vector<T>& values, benchmark::State& state) {
  for (auto _ : state) {
    T sum = T{0};
    for (T value : values) {
      sum += value;
    }
    benchmark::DoNotOptimize(sum);
  }

  state.SetItemsProcessed(
      static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(values.size()));
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) *
                          static_cast<int64_t>(values.size() * sizeof(T)));
}

void BM_SumInt(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const std::vector<int> values = make_values<int>(n);
  sum_values(values, state);
}

void BM_SumFloat(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const std::vector<float> values = make_values<float>(n);
  sum_values(values, state);
}

void BM_SumDouble(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const std::vector<double> values = make_values<double>(n);
  sum_values(values, state);
}

}  // namespace

BENCHMARK(BM_SumInt)->RangeMultiplier(8)->Range(1 << 10, 1 << 20);
BENCHMARK(BM_SumFloat)->RangeMultiplier(8)->Range(1 << 10, 1 << 20);
BENCHMARK(BM_SumDouble)->RangeMultiplier(8)->Range(1 << 10, 1 << 20);
