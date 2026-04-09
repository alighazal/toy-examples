#include "dispatch_model.hpp"

#include <benchmark/benchmark.h>

#include <vector>

namespace kyl = know_your_language;

namespace {

constexpr int kRoundsPerIteration = 32;

void benchmark_procedural(benchmark::State& state) {
  const std::size_t shape_count = static_cast<std::size_t>(state.range(0));
  const std::vector<kyl::ShapeSpec> shapes = kyl::make_shape_workload(shape_count);

  for (auto _ : state) {
    double total = kyl::procedural_total_area(shapes.data(), shapes.size(), kRoundsPerIteration);
    benchmark::DoNotOptimize(total);
  }

  state.SetItemsProcessed(
      static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(shape_count) * kRoundsPerIteration);
}

void benchmark_oop(benchmark::State& state) {
  const std::size_t shape_count = static_cast<std::size_t>(state.range(0));
  const std::vector<kyl::ShapeSpec> shapes = kyl::make_shape_workload(shape_count);

  for (auto _ : state) {
    double total = kyl::oop_total_area(shapes.data(), shapes.size(), kRoundsPerIteration);
    benchmark::DoNotOptimize(total);
  }

  state.SetItemsProcessed(
      static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(shape_count) * kRoundsPerIteration);
}

void benchmark_visitor(benchmark::State& state) {
  const std::size_t shape_count = static_cast<std::size_t>(state.range(0));
  const std::vector<kyl::ShapeSpec> shapes = kyl::make_shape_workload(shape_count);

  for (auto _ : state) {
    double total = kyl::visitor_total_area(shapes.data(), shapes.size(), kRoundsPerIteration);
    benchmark::DoNotOptimize(total);
  }

  state.SetItemsProcessed(
      static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(shape_count) * kRoundsPerIteration);
}

void benchmark_variant(benchmark::State& state) {
  const std::size_t shape_count = static_cast<std::size_t>(state.range(0));
  const std::vector<kyl::ShapeSpec> shapes = kyl::make_shape_workload(shape_count);

  for (auto _ : state) {
    double total = kyl::variant_total_area(shapes.data(), shapes.size(), kRoundsPerIteration);
    benchmark::DoNotOptimize(total);
  }

  state.SetItemsProcessed(
      static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(shape_count) * kRoundsPerIteration);
}

}  // namespace

BENCHMARK(benchmark_procedural)->Arg(128)->Arg(1024)->Arg(8192);
BENCHMARK(benchmark_oop)->Arg(128)->Arg(1024)->Arg(8192);
BENCHMARK(benchmark_visitor)->Arg(128)->Arg(1024)->Arg(8192);
BENCHMARK(benchmark_variant)->Arg(128)->Arg(1024)->Arg(8192);
