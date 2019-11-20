#include "CppML/CppML.hpp"

namespace NoneOfTest {
template <typename T> using Predicate = std::is_class<T>;
template <typename T> struct R {};
struct Type0 {};
struct Type1 {};
void run() {
  {
    using T = ml::f<ml::NoneOf<ml::F<Predicate>, ml::F<R>>, int, char, Type0>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value,
                  "NoneOf with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::NoneOf<ml::F<Predicate>, ml::F<R>>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value,
                  "NoneOf with empty pack");
  }
}
} // namespace NoneOfTest
