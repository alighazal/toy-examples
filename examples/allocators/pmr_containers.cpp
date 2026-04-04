// Nested PMR types: vector of pmr::string shares one memory_resource when you
// construct elements through the vector (e.g. emplace_back).

#include <cstdio>
#include <memory_resource>
#include <string>
#include <vector>

int main() {
  // Where bytes come from; new_delete_resource() is the usual process heap.
  std::pmr::memory_resource* res = std::pmr::new_delete_resource();
  // Outer vector and inner strings are allocator-aware: they use pmr allocators, not std::allocator.
  std::pmr::vector<std::pmr::string> lines{res};

  // emplace_back builds each string with the vector’s allocator so nested storage matches res.
  lines.emplace_back("hello");
  lines.emplace_back("pmr");

  for (const std::pmr::string& s : lines) {
    std::puts(s.c_str());
  }

  return 0;
}
