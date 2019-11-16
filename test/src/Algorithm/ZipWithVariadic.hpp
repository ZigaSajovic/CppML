#include "CppML/CppML.hpp"

namespace ZipWithVariadicTest {
template <typename... Ts> struct Zipper {};
void run() {
  {
    using T = ml::f<ml::ZipWithVariadic<Zipper>, ml::ListT<int, char>,
                    ml::ListT<float, double>, ml::ListT<char, bool>>;
    static_assert(std::is_same<T, ml::ListT<Zipper<int, float, char>,
                                            Zipper<char, double, bool>>>::value,
                  "ZipWithVariadic with non-empty pack");
  }
  {
    using T = ml::f<ml::ZipWithVariadic<Zipper>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "ZipWithVariadic with an empty pack");
  }
}
} // namespace ZipWithVariadicTest
