#include "CppML/CppML.hpp"

namespace ZipWithTest {
template <typename T0, typename T1, typename T2> struct Zipper {};
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::ZipWith<Zipper, ml::F<List>>, ml::ListT<int, char>,
                    ml::ListT<float, double>, ml::ListT<char, bool>>;
    static_assert(std::is_same<T, List<Zipper<int, float, char>,
                                       Zipper<char, double, bool>>>::value,
                  "ZipWith with non-empty pack");
  }
  {
    using T = ml::f<ml::ZipWith<Zipper, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value, "ZipWith with an empty pack");
  }
}
} // namespace ZipWithTest
