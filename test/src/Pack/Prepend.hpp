#include "CppML/CppML.hpp"

namespace PrependTest {
template <typename... Ts> struct List {};
struct Type {};
void run() {
  {
    using T = ml::f<ml::Prepend<Type, ml::F<List>>, int, char>;
    static_assert(std::is_same<T, List<Type, int, char>>::value,
                  "Prepend with a non-empty pack");
  }
  {
    using T = ml::f<ml::Prepend<Type, ml::F<List>>>;
    static_assert(std::is_same<T, List<Type>>::value,
                  "Prepend with an empty pack");
  }
}
}; // namespace PrependTest
