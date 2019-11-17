#include "CppML/CppML.hpp"

namespace IsValidTest {
template <typename T> struct R {};
struct Return {};
struct Type {};
struct A {
  using ValueType = Type;
  Return function() { return {}; };
};
struct B {};
template <typename T> using Getter0 = typename T::ValueType;
template <typename T> using Getter1 = decltype(T().function());
void run() {
  {
    using T = ml::f<ml::IsValid<ml::F<R>>, ml::F<Getter0>, A>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value, "IsValid 0");
  }
  {
    using T = ml::f<ml::IsValid<ml::F<R>>, ml::F<Getter0>, B>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsValid 1");
  }
  {
    using T = ml::f<ml::IsValid<ml::F<R>>, ml::F<Getter1>, A>;
    static_assert(std::is_same<T, R<ml::Bool<true>>>::value, "IsValid 2");
  }
  {
    using T = ml::f<ml::IsValid<ml::F<R>>, ml::F<Getter1>, B>;
    static_assert(std::is_same<T, R<ml::Bool<false>>>::value, "IsValid 3");
  }
}
} // namespace IsValidTest
