#include <benchmark/benchmark.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#ifndef FLAGS_LABEL
#define FLAGS_LABEL "unknown"
#endif

namespace {

struct DataSet {
  std::vector<float> a;
  std::vector<float> b;
};

DataSet makeData(std::size_t n) {
  std::mt19937 rng(42);
  std::uniform_real_distribution<float> dist(0.001f, 1.0f);

  DataSet data;
  data.a.resize(n);
  data.b.resize(n);
  for (std::size_t i = 0; i < n; ++i) {
    data.a[i] = dist(rng);
    data.b[i] = dist(rng);
  }
  return data;
}

static void BM_FlagSensitiveKernel(benchmark::State &state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const auto data = makeData(n);

  for (auto _ : state) {
    float sum = 0.0f;
    for (std::size_t i = 0; i < n; ++i) {
      const float x = data.a[i];
      const float y = data.b[i];
      // Mix arithmetic + transcendental ops to expose optimization effects.
      sum += std::sqrt(x * x + 0.0001f) / (y + 1.0001f);
      sum += std::sin(x) * std::cos(y);
    }
    benchmark::DoNotOptimize(sum);
  }

  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) *
                          static_cast<int64_t>(n * sizeof(float) * 2));
}

}  // namespace

BENCHMARK(BM_FlagSensitiveKernel)->Arg(1 << 16)->Arg(1 << 18)->Arg(1 << 20);

int main(int argc, char **argv) {
  std::cout << "Build variant: " << FLAGS_LABEL << '\n';
#ifdef __FAST_MATH__
  std::cout << "__FAST_MATH__=1\n";
#else
  std::cout << "__FAST_MATH__=0\n";
#endif

#ifdef __OPTIMIZE__
  std::cout << "__OPTIMIZE__=1\n";
#else
  std::cout << "__OPTIMIZE__=0\n";
#endif

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  return 0;
}
