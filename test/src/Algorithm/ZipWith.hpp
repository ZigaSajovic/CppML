#include "CppML/CppML.hpp"

namespace ZipWithTest {
template <typename T0, typename T1> struct Zipper {};
void run() {
  {
    using T = ml::f<ml::ZipWith<Zipper>, ml::ListT<int, char>,
                    ml::ListT<float, double>>;
    static_assert(
        std::is_same<
            T, ml::ListT<Zipper<int, float>, Zipper<char, double>>>::value,
        "ZipWith with non-empty pack");
  }
}
} // namespace ZipWithTest
