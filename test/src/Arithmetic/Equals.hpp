#include "CppML/CppML.hpp"

namespace EqualsTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Equals<ml::F<R>>, ml::Int<2>, ml::Int<3>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "Equals Test False.");
  }
  {
    using T = ml::f<ml::Equals<ml::F<R>>, ml::Int<2>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value,
                  "Equals Test True.");
  }
}
} // namespace EqualsTest
