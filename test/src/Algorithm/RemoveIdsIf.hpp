#include "CppML/CppML.hpp"

namespace RemoveIdsIfTest {
template <typename T> using Predicate = ml::Bool<!std::is_same<int, T>::value>;
void run() {
  {
    using T = ml::f<ml::RemoveIdsIf<ml::F<Predicate>>, int, char, int>;
    static_assert(std::is_same<T, ml::ListT<ml::Int<0>, ml::Int<2>>>::value,
                  "RemoveIdsIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::RemoveIdsIf<ml::F<Predicate>>, float, char, bool>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "RemoveIdsIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::RemoveIdsIf<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "RemoveIdsIf with a non-empty pack");
  }
}
} // namespace RemoveIdsIfTest
