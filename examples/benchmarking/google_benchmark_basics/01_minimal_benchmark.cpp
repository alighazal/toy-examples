#include <benchmark/benchmark.h>

namespace {

void BM_EmptyLoop(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(state.iterations());
  }
}

}  // namespace

BENCHMARK(BM_EmptyLoop);
