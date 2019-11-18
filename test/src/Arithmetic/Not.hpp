#include "CppML/CppML.hpp"

namespace NotTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Not<ml::F<R>>, ml::Bool<true>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "Not Test False.");
  }
  {
    using T = ml::f<ml::Not<ml::F<R>>, ml::Bool<false>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value, "Not Test True.");
  }
}
} // namespace NotTest
