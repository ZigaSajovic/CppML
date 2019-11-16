#include "CppML/CppML.hpp"

namespace RemoveIfTest {
template <typename T> using Predicate = ml::Bool<!std::is_same<int, T>::value>;
template <typename... Ts> struct List {};
void run() {
  {
    using T =
        ml::f<ml::RemoveIf<ml::F<Predicate>, ml::F<List>>, int, char, int>;
    static_assert(std::is_same<T, List<int, int>>::value,
                  "RemoveIf with a non-empty pack");
  }
  {
    using T =
        ml::f<ml::RemoveIf<ml::F<Predicate>, ml::F<List>>, float, char, bool>;
    static_assert(std::is_same<T, List<>>::value,
                  "RemoveIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::RemoveIf<ml::F<Predicate>, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value,
                  "RemoveIf with a non-empty pack");
  }
}
} // namespace RemoveIfTest
