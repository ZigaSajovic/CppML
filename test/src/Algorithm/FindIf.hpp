#include "CppML/CppML.hpp"

namespace FindIfTest {
template <typename T> using Predicate = ml::f<ml::IsSame<>, char, T>;
void run() {
  {
    using T = ml::f<ml::FindIf<ml::F<Predicate>>, int, char, bool>;
    static_assert(std::is_same<T, ml::Int<1>>::value,
                  "FindIf with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::FindIf<ml::F<Predicate>>, int, double, int, char>;
    static_assert(std::is_same<T, ml::Int<3>>::value,
                  "FindIf with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::FindIf<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::Int<0>>::value,
                  "FindIf with empty pack");
  }
}
} // namespace CountIfTest
