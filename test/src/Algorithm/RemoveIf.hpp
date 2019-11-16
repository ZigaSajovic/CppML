#include "CppML/CppML.hpp"

namespace RemoveIfTest {
template <typename T> using Predicate = ml::Bool<!std::is_same<int, T>::value>;
void run() {
  {
    using T = ml::f<ml::RemoveIf<ml::F<Predicate>>, int, char, int>;
    static_assert(std::is_same<T, ml::ListT<int, int>>::value,
                  "RemoveIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::RemoveIf<ml::F<Predicate>>, float, char, bool>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "RemoveIf with a non-empty pack");
  }
  {
    using T = ml::f<ml::RemoveIf<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "RemoveIf with a non-empty pack");
  }
}
} // namespace RemoveIfTest
