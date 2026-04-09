#include "dispatch_model.hpp"

#include <array>
#include <cmath>
#include <cstdint>

namespace know_your_language {
namespace {

constexpr double kPi = 3.14159265358979323846;

}  // namespace

std::vector<ShapeSpec> make_shape_workload(std::size_t count) {
  std::vector<ShapeSpec> specs;
  specs.reserve(count);

  std::uint64_t state = 0xD1B54A32D192ED03ULL;
  auto next_u64 = [&state]() -> std::uint64_t {
    state ^= state << 13U;
    state ^= state >> 7U;
    state ^= state << 17U;
    return state;
  };
  auto next_value = [&next_u64](double min, double max) -> double {
    constexpr double kInvMax = 1.0 / static_cast<double>(UINT64_MAX);
    const double sample = static_cast<double>(next_u64()) * kInvMax;
    return min + (max - min) * sample;
  };

  constexpr std::array<ShapeKind, 3> kPattern{
      ShapeKind::Circle, ShapeKind::Square, ShapeKind::Triangle};

  for (std::size_t i = 0; i < count; ++i) {
    const ShapeKind kind = kPattern[i % kPattern.size()];
    switch (kind) {
      case ShapeKind::Circle:
        specs.push_back({kind, next_value(0.2, 8.0), 0.0});
        break;
      case ShapeKind::Square:
        specs.push_back({kind, next_value(0.2, 8.0), 0.0});
        break;
      case ShapeKind::Triangle:
        specs.push_back({kind, next_value(0.2, 8.0), next_value(0.2, 8.0)});
        break;
    }
  }

  return specs;
}

double procedural_total_area(ShapeSpec const* specs, std::size_t count, int rounds) {
  double total = 0.0;

  for (int round = 0; round < rounds; ++round) {
    for (std::size_t i = 0; i < count; ++i) {
      const ShapeSpec& spec = specs[i];
      switch (spec.kind) {
        case ShapeKind::Circle:
          total += kPi * spec.a * spec.a;
          break;
        case ShapeKind::Square:
          total += spec.a * spec.a;
          break;
        case ShapeKind::Triangle:
          total += 0.5 * spec.a * spec.b;
          break;
      }
    }
  }

  return total;
}

}  // namespace know_your_language
