#include "CppML/CppML.hpp"

namespace CurryTest {
template <typename T0, typename T1, typename T2, typename T3> struct MF {};
void run() {
  {
    using F0 = ml::f<ml::Curry<ml::F<MF>>, int, char>;
    using T = ml::f<F0, bool, float>;
    static_assert(std::is_same<T, MF<int, char, bool, float>>::value,
                  "Curry Test.");
  }
}
}; // namespace CurryTest
