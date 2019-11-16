#include "CppML/CppML.hpp"

namespace ReplaceIfTest {
template <typename T> using Predicate = std::is_same<int, T>;
struct Replacement {};
void run() {
  {
    using T =
        ml::f<ml::ReplaceIf<ml::F<Predicate>, Replacement>, int, char, int>;
    static_assert(
        std::is_same<T, ml::ListT<Replacement, char, Replacement>>::value,
        "ReplaceIf with a non-empty pack");
  }
  {
    using T =
        ml::f<ml::ReplaceIf<ml::F<Predicate>, Replacement>, float, char, bool>;
    static_assert(std::is_same<T, ml::ListT<float, char, bool>>::value,
                  "ReplaceIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::ReplaceIf<ml::F<Predicate>, Replacement>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "ReplaceIf with a non-empty pack");
  }
}
} // namespace ReplaceIfTest
