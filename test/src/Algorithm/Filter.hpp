#include "CppML/CppML.hpp"

namespace FilterTest {
template <typename T> using Predicate = ml::f<ml::IsSame<>, int, T>;
void run() {
  {
    using T = ml::f<ml::Filter<ml::F<Predicate>>, int, char, int>;
    static_assert(std::is_same<T, ml::ListT<int, int>>::value,
                  "Filter with a non-empty pack");
  }
  {
    using T =
        ml::f<ml::Filter<ml::F<Predicate>>, float, char, bool>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "Filter with a non-empty pack");
  }
  {
    using T = ml::f<ml::Filter<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "Filter with a non-empty pack");
  }
}
} // namespace FilterTest
