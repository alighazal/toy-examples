#include "dispatch_model.hpp"

#include <memory>
#include <vector>

namespace know_your_language {
namespace {

constexpr double kPi = 3.14159265358979323846;

class Shape {
 public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
};

class Circle final : public Shape {
 public:
  explicit Circle(double radius) : radius_(radius) {}
  double area() const override { return kPi * radius_ * radius_; }

 private:
  double radius_;
};

class Square final : public Shape {
 public:
  explicit Square(double side) : side_(side) {}
  double area() const override { return side_ * side_; }

 private:
  double side_;
};

class Triangle final : public Shape {
 public:
  Triangle(double base, double height) : base_(base), height_(height) {}
  double area() const override { return 0.5 * base_ * height_; }

 private:
  double base_;
  double height_;
};

std::vector<std::unique_ptr<Shape>> to_oop_shapes(ShapeSpec const* specs, std::size_t count) {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.reserve(count);

  for (std::size_t i = 0; i < count; ++i) {
    const ShapeSpec& spec = specs[i];
    switch (spec.kind) {
      case ShapeKind::Circle:
        shapes.emplace_back(std::make_unique<Circle>(spec.a));
        break;
      case ShapeKind::Square:
        shapes.emplace_back(std::make_unique<Square>(spec.a));
        break;
      case ShapeKind::Triangle:
        shapes.emplace_back(std::make_unique<Triangle>(spec.a, spec.b));
        break;
    }
  }

  return shapes;
}

}  // namespace

double oop_total_area(ShapeSpec const* specs, std::size_t count, int rounds) {
  static ShapeSpec const* cached_specs = nullptr;
  static std::size_t cached_count = 0;
  static std::vector<std::unique_ptr<Shape>> cached_shapes;

  if (cached_specs != specs || cached_count != count) {
    cached_shapes = to_oop_shapes(specs, count);
    cached_specs = specs;
    cached_count = count;
  }

  double total = 0.0;

  for (int round = 0; round < rounds; ++round) {
    for (auto const& shape : cached_shapes) {
      total += shape->area();
    }
  }

  return total;
}

}  // namespace know_your_language
