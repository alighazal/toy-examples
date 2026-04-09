#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace know_your_language {

enum class ShapeKind : std::uint8_t {
  Circle,
  Square,
  Triangle
};

struct ShapeSpec {
  ShapeKind kind;
  double a;
  double b;
};

std::vector<ShapeSpec> make_shape_workload(std::size_t count);

double procedural_total_area(ShapeSpec const* specs, std::size_t count, int rounds);
double oop_total_area(ShapeSpec const* specs, std::size_t count, int rounds);
double visitor_total_area(ShapeSpec const* specs, std::size_t count, int rounds);
double variant_total_area(ShapeSpec const* specs, std::size_t count, int rounds);

}  // namespace know_your_language
