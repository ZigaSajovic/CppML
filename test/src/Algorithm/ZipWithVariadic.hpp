#include "CppML/CppML.hpp"

namespace ZipWithVariadicTest {
template <typename... Ts> struct Zipper {};
template <typename... Ts> struct List {};
void run() {
  {
    using T =
        ml::f<ml::ZipWithVariadic<Zipper, ml::F<List>>, ml::ListT<int, char>,
              ml::ListT<float, double>, ml::ListT<char, bool>>;
    static_assert(std::is_same<T, List<Zipper<int, float, char>,
                                       Zipper<char, double, bool>>>::value,
                  "ZipWithVariadic with non-empty pack");
  }
  {
    using T = ml::f<ml::ZipWithVariadic<Zipper, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value,
                  "ZipWithVariadic with an empty pack");
  }
}
} // namespace ZipWithVariadicTest
