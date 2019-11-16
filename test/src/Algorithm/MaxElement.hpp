#include "CppML/CppML.hpp"

namespace MaxElementTest {
template <typename T, typename U>
using Compare = ml::Bool<(alignof(T) > alignof(U))>;
void run() {
  {
    using T = ml::f<ml::MaxElement<ml::F<Compare>>, int, double, bool>;
    static_assert(std::is_same<T, double>::value,
                  "MaxElement with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::MaxElement<ml::F<Compare>>, int, bool, double>;
    static_assert(std::is_same<T, double>::value,
                  "MaxElement with a non-empty pack 1");
  }
}
} // namespace MaxElementTest
