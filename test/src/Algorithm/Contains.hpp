#include "CppML/CppML.hpp"
#include <string>
#include <vector>

namespace ContainsTest {
void run() {
  {
    using T = ml::f<ml::Contains<char>, int, char, std::string>;
    static_assert(std::is_same<T, ml::Bool<true>>::value,
                  "Contains with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::Contains<std::string>, int, char, std::string>;
    static_assert(std::is_same<T, ml::Bool<true>>::value,
                  "Contains with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::Contains<float>, int, char>;
    static_assert(std::is_same<T, ml::Bool<false>>::value,
                  "Contains with a non-empty pack 3");
  }
  {
    using T = ml::f<ml::Contains<char>>;
    static_assert(std::is_same<T, ml::Bool<false>>::value,
                  "Contains with empty pack");
  }
}
} // namespace Contains_Test
