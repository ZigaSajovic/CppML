#include "CppML/CppML.hpp"

namespace AllOfTest {
template <typename T> using Predicate = std::is_class<T>;
template <typename T> struct R {};
struct Type0 {};
struct Type1 {};
void run() {
  {
    using T = ml::f<ml::AllOf<ml::F<Predicate>, ml::F<R>>, int, char, Type0>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "AllOf with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::AllOf<ml::F<Predicate>, ml::F<R>>, Type1, Type0>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value,
                  "AllOf with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::AllOf<ml::F<Predicate>, ml::F<R>>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value,
                  "AllOf with empty pack");
  }
}
} // namespace AllOfTest
