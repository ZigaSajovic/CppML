#include "CppML/CppML.hpp"

namespace GroupIdsByTest {
template <typename T> using AlignOf = ml::Int<alignof(T)>;
void run() {
  {
    using T =
        ml::f<ml::GroupIdsBy<ml::F<AlignOf>>, int, char, float, bool, double>;
    static_assert(std::is_same<T, ml::ListT<ml::ListT<ml::Int<0>, ml::Int<2>>,
                                            ml::ListT<ml::Int<1>, ml::Int<3>>,
                                            ml::ListT<ml::Int<4>>>>::value,
                  "GroupIdsBy with a non-empty pack");
  }
  {
    using T = ml::f<ml::GroupIdsBy<ml::F<AlignOf>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "GroupIdsBy with an empty pack");
  }
}
} // namespace GroupIdsByTest
