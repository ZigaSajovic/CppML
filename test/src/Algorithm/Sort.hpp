#include "CppML/CppML.hpp"

namespace SortTest {
template <typename T, typename U>
using Compare = ml::Bool<(alignof(T) > alignof(U))>;
template <typename... Ts> struct List {};
void run() {
  {
    using T =
        ml::f<ml::Sort<ml::F<Compare>, ml::F<List>>, int, double, bool, long>;
    static_assert(std::is_same<T, List<long, double, int, bool>>::value,
                  "Sort with a non-empty pack");
  }
  {
    using T = ml::f<ml::Sort<ml::F<Compare>, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value, "Sort with an empty pack");
  }
}
} // namespace SortTest
