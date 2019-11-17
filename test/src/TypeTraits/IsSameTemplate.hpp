#include "CppML/CppML.hpp"

namespace IsSameTemplateTest {
template <typename T> struct R {};
template <typename T> struct Template0 {};
template <typename T> struct Template1 {};
struct Type0 {};
struct Type1 {};
void run() {
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Template0<Type0>, Template0<Type0>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value, "IsSameTemplate 0");
  }
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Template0<Type0>, Template0<Type1>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value, "IsSameTemplate 1");
  }
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Template0<Type1>, Template0<Type0>>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value, "IsSameTemplate 2");
  }
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Template1<Type0>, Template0<Type0>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsSameTemplate 3");
  }
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Template0<Type0>, Template1<Type0>>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsSameTemplate 4");
  }
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Type0, Type0>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsSameTemplate 5");
  }
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Type0, Type1>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsSameTemplate 6");
  }
  {
    using T = ml::f<ml::IsSameTemplate<ml::F<R>>, Type1, Type0>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsSameTemplate 7");
  }
}
} // namespace IsSameTest
