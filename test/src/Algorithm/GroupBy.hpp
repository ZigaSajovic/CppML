#include "CppML/CppML.hpp"

namespace GroupByTest {
template <typename T> using AlignOf = ml::Int<alignof(T)>;
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::GroupBy<ml::F<AlignOf>, ml::F<List>>, int, char, float,
                    bool, double>;
    static_assert(
        std::is_same<T, List<ml::ListT<int, float>, ml::ListT<char, bool>,
                             ml::ListT<double>>>::value,
        "GroupBy with a non-empty pack");
  }
  {
    using T = ml::f<ml::GroupBy<ml::F<AlignOf>, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value, "GroupBy with an empty pack");
  }
}
} // namespace GroupByTest
