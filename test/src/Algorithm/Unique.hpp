#include "CppML/CppML.hpp"

namespace UniqueTest {
template <typename... Ts> struct List {};
void run() {
  {
    using T =
        ml::f<ml::Unique<ml::F<List>>, int, bool, double, bool, int, long, int>;
    static_assert(std::is_same<T, List<int, bool, double, long>>::value,
                  "Unique with a non-empty pack");
  }
  {
    using T = ml::f<ml::Unique<ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value, "Unique with an empty pack");
  }
}
} // namespace UniqueTest
