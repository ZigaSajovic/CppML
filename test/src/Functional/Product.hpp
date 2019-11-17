#include "CppML/CppML.hpp"

namespace ProductTest {
template <typename... Ts> struct List0 {};
template <typename... Ts> struct List1 {};
template <typename... Ts> struct List2 {};
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<
        ml::Product<ml::F<List0>, ml::F<List1>, ml::F<List2>, ml::F<List>>,
        char, bool, double>;
    static_assert(
        std::is_same<T,
                     List<List0<char, bool, double>, List1<char, bool, double>,
                          List2<char, bool, double>>>::value,
        "Product Test.");
  }
}
} // namespace ProductTest
