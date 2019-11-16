#include "CppML/CppML.hpp"

namespace ReduceTest {
template <typename T, typename U> struct MF {};
struct Init {};
void run() {
  {
    using T = ml::f<ml::Reduce<ml::F<MF>>, Init, int, char, bool>;
    static_assert(std::is_same<T, MF<MF<MF<Init, int>, char>, bool>>::value,
                  "Reduce with a non-empty pack");
  }
  {
    using T = ml::f<ml::Reduce<ml::F<MF>>, Init>;
    static_assert(std::is_same<T, Init>::value, "Reduce with a non-empty pack");
  }
}
} // namespace ReduceTest
