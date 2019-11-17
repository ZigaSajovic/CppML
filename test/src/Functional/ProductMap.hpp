#include "CppML/CppML.hpp"

namespace ProductMapTest {
template <typename... Ts> struct R0 {};
template <typename... Ts> struct R1 {};
template <typename... Ts> struct R2 {};
template <typename... Ts> struct List {};
void run() {
  {
    using T =
        ml::f<ml::ProductMap<ml::F<R0>, ml::F<R1>, ml::F<R2>, ml::F<List>>,
              char, bool, double>;
    static_assert(std::is_same<T, List<R0<char>, R1<bool>, R2<double>>>::value,
                  "ProductMap Test.");
  }
}
} // namespace ProductMapTest
