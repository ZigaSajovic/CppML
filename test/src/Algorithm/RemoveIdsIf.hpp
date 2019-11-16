#include "CppML/CppML.hpp"

namespace RemoveIdsIfTest {
template <typename T> using Predicate = ml::Bool<!std::is_same<int, T>::value>;
template <typename... Ts> struct List {};
void run() {
  {
    using T =
        ml::f<ml::RemoveIdsIf<ml::F<Predicate>, ml::F<List>>, int, char, int>;
    static_assert(std::is_same<T, List<ml::Int<0>, ml::Int<2>>>::value,
                  "RemoveIdsIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::RemoveIdsIf<ml::F<Predicate>, ml::F<List>>, float, char,
                    bool>;
    static_assert(std::is_same<T, List<>>::value,
                  "RemoveIdsIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::RemoveIdsIf<ml::F<Predicate>, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value,
                  "RemoveIdsIf with a non-empty pack");
  }
}
} // namespace RemoveIdsIfTest
