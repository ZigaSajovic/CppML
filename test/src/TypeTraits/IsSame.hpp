#include "CppML/CppML.hpp"

namespace IsSameTest {
template <typename T> struct R {};
struct Type0 {};
struct Type1 {};
void run() {
  {
    using T = ml::f<ml::IsSame<ml::F<R>>, Type0, Type0>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value, "IsSame 0");
  }
  {
    using T = ml::f<ml::IsSame<ml::F<R>>, Type0, Type1>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsSame 1");
  }
  {
    using T = ml::f<ml::IsSame<ml::F<R>>, Type1, Type0>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsSame 2");
  }
}
} // namespace IsSameTest
