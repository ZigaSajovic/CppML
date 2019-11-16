#include "CppML/CppML.hpp"

namespace UniqueCompareTest {
template <typename T, typename U> using Compare = std::is_same<T, U>;
void run() {
  {
    using T = ml::f<ml::UniqueCompare<ml::F<Compare>>, int, bool, double, bool,
                    int, long, int>;
    static_assert(std::is_same<T, ml::ListT<int, bool, double, long>>::value,
                  "UniqueCompare with a non-empty pack");
  }
  {
    using T = ml::f<ml::UniqueCompare<ml::F<Compare>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "UniqueCompare with an empty pack");
  }
}
} // namespace UniqueCompareTest
