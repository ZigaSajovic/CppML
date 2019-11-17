#include "CppML/CppML.hpp"

namespace CurryRTest {
template <typename T0, typename T1, typename T2, typename T3> struct MF {};
void run() {
  {
    using F0 = ml::f<ml::CurryR<ml::F<MF>>, int, char>;
    using T = ml::f<F0, bool, float>;
    static_assert(std::is_same<T, MF<bool, float, int, char>>::value,
                  "CurryR Test.");
  }
}
}; // namespace CurryRTest
