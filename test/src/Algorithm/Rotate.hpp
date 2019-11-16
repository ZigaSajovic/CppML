#include "CppML/CppML.hpp"

namespace RotateTest {
void run() {
  {
    using T = ml::f<ml::Rotate<1, 3, 4>, int, char, bool, double, float>;
    static_assert(
        std::is_same<T, ml::ListT<int, double, char, bool, float>>::value,
        "Rotate with a non-empty pack");
  }
  {
    using T = ml::f<ml::Rotate<0, 2, 4>, int, char, bool, double, float>;
    static_assert(
        std::is_same<T, ml::ListT<bool, double, int, char, float>>::value,
        "Rotate with a non-empty pack: 0");
  }
}
} // namespace RotateTest
