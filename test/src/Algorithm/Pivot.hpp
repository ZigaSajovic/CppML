#include "CppML/CppML.hpp"

namespace PivotTest {
void run() {
  {
    using T = ml::f<ml::Pivot<2>, int, char, int>;
    static_assert(std::is_same<T, ml::ListT<int, int, char>>::value,
                  "Pivot with a non-empty pack");
  }
  {
    using T = ml::f<ml::Pivot<0>, int, char, float>;
    static_assert(std::is_same<T, ml::ListT<int, char, float>>::value,
                  "Pivot with a non-empty pack: 0");
  }
}
} // namespace FilterTest
