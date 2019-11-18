#include "CppML/CppML.hpp"

namespace GreaterTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Greater<ml::F<R>>, ml::Int<2>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "Greater Test False.");
  }
  {
    using T = ml::f<ml::Greater<ml::F<R>>, ml::Int<2>, ml::Int<3>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "Greater Test False.");
  }
  {
    using T = ml::f<ml::Greater<ml::F<R>>, ml::Int<3>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value,
                  "Greater Test True.");
  }
}
} // namespace GreaterTest
