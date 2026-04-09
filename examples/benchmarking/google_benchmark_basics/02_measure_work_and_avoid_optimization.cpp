#include <benchmark/benchmark.h>

#include <string>

namespace {

void BM_StringFind(benchmark::State& state) {
  const std::string haystack(1024, 'a');
  const std::string needle = "aaaab";

  for (auto _ : state) {
    std::size_t position = haystack.find(needle);
    benchmark::DoNotOptimize(position);
  }
}

}  // namespace

BENCHMARK(BM_StringFind);
