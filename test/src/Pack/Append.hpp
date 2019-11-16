#include "CppML/CppML.hpp"

namespace AppendTest {
template <typename... Ts> struct List {};
struct Type {};
void run() {
  {
    using T = ml::f<ml::Append<Type, ml::F<List>>, int, char>;
    static_assert(std::is_same<T, List<int, char, Type>>::value,
                  "Append with a non-empty pack");
  }
  {
    using T = ml::f<ml::Append<Type, ml::F<List>>>;
    static_assert(std::is_same<T, List<Type>>::value,
                  "Append with an empty pack");
  }
}
}; // namespace AppendTest
