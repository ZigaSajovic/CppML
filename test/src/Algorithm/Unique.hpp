#include "CppML/CppML.hpp"

namespace UniqueTest {
void run() {
  {
    using T = ml::f<ml::Unique<>, int, bool, double, bool, int, long, int>;
    static_assert(std::is_same<T, ml::ListT<int, bool, double, long>>::value,
                  "Unique with a non-empty pack");
  }
  {
    using T = ml::f<ml::Unique<>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "Unique with an empty pack");
  }
}
} // namespace UniqueTest
