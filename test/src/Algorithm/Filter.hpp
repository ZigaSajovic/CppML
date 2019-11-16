#include "CppML/CppML.hpp"

namespace FilterTest {
template <typename T> using Predicate = std::is_same<int, T>;
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::Filter<ml::F<Predicate>, ml::F<List>>, int, char, int>;
    static_assert(std::is_same<T, List<int, int>>::value,
                  "Filter with a non-empty pack");
  }
  {
    using T =
        ml::f<ml::Filter<ml::F<Predicate>, ml::F<List>>, float, char, bool>;
    static_assert(std::is_same<T, List<>>::value,
                  "Filter with a non-empty pack");
  }
  {
    using T = ml::f<ml::Filter<ml::F<Predicate>, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value,
                  "Filter with a non-empty pack");
  }
}
} // namespace FilterTest
