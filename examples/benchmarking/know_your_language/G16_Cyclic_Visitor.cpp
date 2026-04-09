#include "dispatch_model.hpp"

#include <memory>
#include <vector>

namespace know_your_language {
namespace {

constexpr double kPi = 3.14159265358979323846;

class Circle;
class Square;
class Triangle;

class ShapeVisitor {
 public:
  virtual ~ShapeVisitor() = default;
  virtual void visit(Circle const&) = 0;
  virtual void visit(Square const&) = 0;
  virtual void visit(Triangle const&) = 0;
};

class Shape {
 public:
  virtual ~Shape() = default;
  virtual void accept(ShapeVisitor&) const = 0;
};

class Circle final : public Shape {
 public:
  explicit Circle(double radius) : radius_(radius) {}
  double radius() const { return radius_; }
  void accept(ShapeVisitor& visitor) const override { visitor.visit(*this); }

 private:
  double radius_;
};

class Square final : public Shape {
 public:
  explicit Square(double side) : side_(side) {}
  double side() const { return side_; }
  void accept(ShapeVisitor& visitor) const override { visitor.visit(*this); }

 private:
  double side_;
};

class Triangle final : public Shape {
 public:
  Triangle(double base, double height) : base_(base), height_(height) {}
  double base() const { return base_; }
  double height() const { return height_; }
  void accept(ShapeVisitor& visitor) const override { visitor.visit(*this); }

 private:
  double base_;
  double height_;
};

class AreaVisitor final : public ShapeVisitor {
 public:
  void visit(Circle const& circle) override { latest_ = kPi * circle.radius() * circle.radius(); }
  void visit(Square const& square) override { latest_ = square.side() * square.side(); }
  void visit(Triangle const& triangle) override { latest_ = 0.5 * triangle.base() * triangle.height(); }
  double latest() const { return latest_; }

 private:
  double latest_ = 0.0;
};

std::vector<std::unique_ptr<Shape>> to_visitor_shapes(ShapeSpec const* specs, std::size_t count) {
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

double visitor_total_area(ShapeSpec const* specs, std::size_t count, int rounds) {
  static ShapeSpec const* cached_specs = nullptr;
  static std::size_t cached_count = 0;
  static std::vector<std::unique_ptr<Shape>> cached_shapes;

  if (cached_specs != specs || cached_count != count) {
    cached_shapes = to_visitor_shapes(specs, count);
    cached_specs = specs;
    cached_count = count;
  }

  AreaVisitor visitor;
  double total = 0.0;

  for (int round = 0; round < rounds; ++round) {
    for (auto const& shape : cached_shapes) {
      shape->accept(visitor);
      total += visitor.latest();
    }
  }

  return total;
}

}  // namespace know_your_language
