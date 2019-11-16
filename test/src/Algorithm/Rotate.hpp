#include "CppML/CppML.hpp"

namespace RotateTest {
template <typename... Ts> struct List {};
void run() {
  {
    using T =
        ml::f<ml::Rotate<1, 3, 4, ml::F<List>>, int, char, bool, double, float>;
    static_assert(std::is_same<T, List<int, double, char, bool, float>>::value,
                  "Rotate with a non-empty pack");
  }
  {
    using T =
        ml::f<ml::Rotate<0, 2, 4, ml::F<List>>, int, char, bool, double, float>;
    static_assert(std::is_same<T, List<bool, double, int, char, float>>::value,
                  "Rotate with a non-empty pack: 0");
  }
}
} // namespace RotateTest
