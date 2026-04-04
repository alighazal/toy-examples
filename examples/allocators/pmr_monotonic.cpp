// Monotonic buffer: allocations bump a pointer in a fixed byte array.
// Fast and cache-friendly; memory is not freed piecemeal (whole buffer resets together).

#include <array>
#include <cstddef>
#include <iostream>
#include <memory_resource>
#include <vector>

int main() {
  // Fixed backing store (here on the stack); the arena hands out slices of this buffer.
  alignas(std::max_align_t) std::array<std::byte, 256> storage{};
  // Bump-pointer allocator: fast linear allocation; frees only when the whole arena is released/reset.
  std::pmr::monotonic_buffer_resource arena{storage.data(), storage.size()};

  // Container stores polymorphic_allocator<int> pointing at &arena, so growth uses the same buffer.
  std::pmr::vector<int> v{&arena};
  for (int i = 0; i < 8; ++i) {
    v.push_back(i * i);
  }

  std::cout << "values (all from the stack-backed arena): ";
  for (int x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  return 0;
}
