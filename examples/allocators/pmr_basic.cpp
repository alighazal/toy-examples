// PMR basics: polymorphic containers use a std::pmr::memory_resource*.
// Same container type can use the heap (new/delete) or another strategy.

#include <iostream>
#include <memory_resource>
#include <vector>

int main() {
  // Heap backed by global ::operator new/delete; same resource the default allocator uses.
  std::pmr::memory_resource* upstream = std::pmr::new_delete_resource();

  // Pass the resource explicitly: allocations go through this polymorphic_allocator.
  std::pmr::vector<int> explicit_heap{upstream};
  explicit_heap.push_back(1);
  explicit_heap.push_back(2);

  // No allocator argument: uses std::pmr::get_default_resource() (usually new/delete).
  std::pmr::vector<int> uses_default;
  uses_default.push_back(10);

  std::cout << "explicit_heap: ";
  for (int x : explicit_heap) {
    std::cout << x << ' ';
  }
  std::cout << "\nuses_default: ";
  for (int x : uses_default) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  return 0;
}
