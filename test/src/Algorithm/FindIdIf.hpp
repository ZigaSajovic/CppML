#include "CppML/CppML.hpp"

namespace FindIdIfTest {
template <typename T> using Predicate = ml::f<ml::IsSame<>, char, T>;
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::FindIdIf<ml::F<Predicate>, ml::F<R>>, int, char, bool>;
    static_assert(std::is_same<T, R<ml::Int<1>>>::value,
                  "FindIdIf with a non-empty pack 1");
  }
  {
    using T =
        ml::f<ml::FindIdIf<ml::F<Predicate>, ml::F<R>>, int, double, int, char>;
    static_assert(std::is_same<T, R<ml::Int<3>>>::value,
                  "FindIdIf with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::FindIdIf<ml::F<Predicate>, ml::F<R>>>;
    static_assert(std::is_same<T, R<ml::Int<0>>>::value,
                  "FindIf with empty pack");
  }
}
} // namespace FindIfTest
