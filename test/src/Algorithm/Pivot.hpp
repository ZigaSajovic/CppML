#include "CppML/CppML.hpp"

namespace PivotTest {
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::Pivot<2, ml::F<List>>, int, char, int>;
    static_assert(std::is_same<T, List<int, int, char>>::value,
                  "Pivot with a non-empty pack");
  }
  {
    using T = ml::f<ml::Pivot<0, ml::F<List>>, int, char, float>;
    static_assert(std::is_same<T, List<int, char, float>>::value,
                  "Pivot with a non-empty pack: 0");
  }
}
} // namespace PivotTest
