#include "CppML/CppML.hpp"

namespace IfElseTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::IfElse<ml::Bool<true>, ml::F<R>>, int, char>;
    static_assert(std::is_same<T, R<int>>::value, "IfElse true");
  }
  {
    using T = ml::f<ml::IfElse<ml::Bool<false>, ml::F<R>>, int, char>;
    static_assert(std::is_same<T, R<char>>::value, "IfElse true");
  }
}
} // namespace IfElseTest
