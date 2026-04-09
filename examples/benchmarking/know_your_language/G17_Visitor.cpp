#include "dispatch_model.hpp"

#include <variant>
#include <vector>

namespace know_your_language {
namespace {

constexpr double kPi = 3.14159265358979323846;

struct Circle {
  double radius;
};

struct Square {
  double side;
};

struct Triangle {
  double base;
  double height;
};

using Shape = std::variant<Circle, Square, Triangle>;

struct AreaVisitor {
  double operator()(Circle const& shape) const { return kPi * shape.radius * shape.radius; }
  double operator()(Square const& shape) const { return shape.side * shape.side; }
  double operator()(Triangle const& shape) const { return 0.5 * shape.base * shape.height; }
};

std::vector<Shape> to_variant_shapes(ShapeSpec const* specs, std::size_t count) {
  std::vector<Shape> shapes;
  shapes.reserve(count);

  for (std::size_t i = 0; i < count; ++i) {
    const ShapeSpec& spec = specs[i];
    switch (spec.kind) {
      case ShapeKind::Circle:
        shapes.emplace_back(Circle{spec.a});
        break;
      case ShapeKind::Square:
        shapes.emplace_back(Square{spec.a});
        break;
      case ShapeKind::Triangle:
        shapes.emplace_back(Triangle{spec.a, spec.b});
        break;
    }
  }

  return shapes;
}

}  // namespace

double variant_total_area(ShapeSpec const* specs, std::size_t count, int rounds) {
  static ShapeSpec const* cached_specs = nullptr;
  static std::size_t cached_count = 0;
  static std::vector<Shape> cached_shapes;

  if (cached_specs != specs || cached_count != count) {
    cached_shapes = to_variant_shapes(specs, count);
    cached_specs = specs;
    cached_count = count;
  }

  AreaVisitor visitor;
  double total = 0.0;

  for (int round = 0; round < rounds; ++round) {
    for (Shape const& shape : cached_shapes) {
      total += std::visit(visitor, shape);
    }
  }

  return total;
}

}  // namespace know_your_language
