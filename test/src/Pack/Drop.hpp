#include "CppML/CppML.hpp"

namespace DropTest {
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::Drop<2, ml::F<List>>, int, int, char, bool>;
    static_assert(std::is_same<T, List<char, bool>>::value,
                  "Drop with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::Drop<3, ml::F<List>>, int, int, int, char, bool>;
    static_assert(std::is_same<T, List<char, bool>>::value,
                  "Drop with a non-empty pack 2");
  }
  {
    using T =
        ml::f<ml::Drop<5, ml::F<List>>, int, int, int, int, int, char, bool>;
    static_assert(std::is_same<T, List<char, bool>>::value,
                  "Drop with a non-empty pack 3");
  }
  {
    using T = ml::f<ml::Drop<7, ml::F<List>>, int, int, int, int, int, int, int,
                    char, bool>;
    static_assert(std::is_same<T, List<char, bool>>::value,
                  "Drop with a non-empty pack 3");
  }
  {
    using T = ml::f<ml::Drop<0, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value, "Drop with an empty pack");
  }
}
}; // namespace DropTest
