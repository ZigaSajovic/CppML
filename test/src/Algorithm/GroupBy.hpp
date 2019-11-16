#include "CppML/CppML.hpp"

namespace GroupByTest {
template <typename T> using AlignOf = ml::Int<alignof(T)>;
void run() {
  {
    using T =
        ml::f<ml::GroupBy<ml::F<AlignOf>>, int, char, float, bool, double>;
    static_assert(
        std::is_same<T, ml::ListT<ml::ListT<int, float>, ml::ListT<char, bool>,
                                  ml::ListT<double>>>::value,
        "GroupBy with a non-empty pack");
  }
  {
    using T = ml::f<ml::GroupBy<ml::F<AlignOf>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "GroupBy with an empty pack");
  }
}
} // namespace GroupByTest
