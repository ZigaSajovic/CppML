#include "CppML/CppML.hpp"

namespace ReplaceIfTest {
template <typename T> using Predicate = std::is_same<int, T>;
template <typename... Ts> struct List {};
struct Replacement {};
void run() {
  {
    using T = ml::f<ml::ReplaceIf<ml::F<Predicate>, Replacement, ml::F<List>>,
                    int, char, int>;
    static_assert(std::is_same<T, List<Replacement, char, Replacement>>::value,
                  "ReplaceIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::ReplaceIf<ml::F<Predicate>, Replacement, ml::F<List>>,
                    float, char, bool>;
    static_assert(std::is_same<T, List<float, char, bool>>::value,
                  "ReplaceIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::ReplaceIf<ml::F<Predicate>, Replacement, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value,
                  "ReplaceIf with a non-empty pack");
  }
}
} // namespace ReplaceIfTest
