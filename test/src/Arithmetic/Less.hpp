#include "CppML/CppML.hpp"

namespace LessTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Less<ml::F<R>>, ml::Int<2>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "Less Test False.");
  }
  {
    using T = ml::f<ml::Less<ml::F<R>>, ml::Int<3>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "Less Test False.");
  }
  {
    using T = ml::f<ml::Less<ml::F<R>>, ml::Int<2>, ml::Int<3>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value,
                  "Less Test True.");
  }
}
} // namespace LessTest
