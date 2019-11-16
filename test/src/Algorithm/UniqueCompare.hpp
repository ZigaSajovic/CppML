#include "CppML/CppML.hpp"

namespace UniqueCompareTest {
template <typename T, typename U> using Compare = std::is_same<T, U>;
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::UniqueCompare<ml::F<Compare>, ml::F<List>>, int, bool,
                    double, bool, int, long, int>;
    static_assert(std::is_same<T, List<int, bool, double, long>>::value,
                  "UniqueCompare with a non-empty pack");
  }
  {
    using T = ml::f<ml::UniqueCompare<ml::F<Compare>, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value,
                  "UniqueCompare with an empty pack");
  }
}
} // namespace UniqueCompareTest
