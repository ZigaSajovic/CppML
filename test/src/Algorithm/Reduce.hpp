#include "CppML/CppML.hpp"

namespace ReduceTest {
template <typename T, typename U> struct MF {};
struct Init {};
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Reduce<ml::F<MF>, ml::F<R>>, Init, int, char, bool>;
    static_assert(std::is_same<T, R<MF<MF<MF<Init, int>, char>, bool>>>::value,
                  "Reduce with a non-empty pack");
  }
  {
    using T = ml::f<ml::Reduce<ml::F<MF>, ml::F<R>>, Init>;
    static_assert(std::is_same<T, R<Init>>::value,
                  "Reduce with a non-empty pack");
  }
}
} // namespace ReduceTest
