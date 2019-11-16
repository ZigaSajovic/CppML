#include "CppML/CppML.hpp"

namespace FilterIdsTest {
template <typename T> using Predicate = ml::f<ml::IsSame<>, int, T>;
void run() {
  {
    using T = ml::f<ml::FilterIds<ml::F<Predicate>>, int, char, int>;
    static_assert(std::is_same<T, ml::ListT<ml::Int<0>, ml::Int<2>>>::value,
                  "FilterIds with a non-empty pack");
  }
  {
    using T = ml::f<ml::FilterIds<ml::F<Predicate>>, float, char, bool>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "FilterIds with a non-empty pack");
  }
  {
    using T = ml::f<ml::FilterIds<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "FilterIds with a non-empty pack");
  }
}
} // namespace FilterIdsTest
