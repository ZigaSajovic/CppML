#include "CppML/CppML.hpp"

namespace IfValidOrTest {
template <typename T> struct R {};
struct Return {};
struct Default {};
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
    using T = ml::f<ml::IfValidOr<ml::F<R>>, Default, ml::F<Getter0>, A>;
    static_assert(std::is_same<T, R<Type>>::value, "IfValidOr 0");
  }
  {
    using T = ml::f<ml::IfValidOr<ml::F<R>>, Default, ml::F<Getter0>, B>;
    static_assert(std::is_same<T, R<Default>>::value, "IfValidOr 1");
  }
  {
    using T = ml::f<ml::IfValidOr<ml::F<R>>, Default, ml::F<Getter1>, A>;
    static_assert(std::is_same<T, R<Return>>::value, "IfValidOr 2");
  }
  {
    using T = ml::f<ml::IfValidOr<ml::F<R>>, Default, ml::F<Getter1>, B>;
    static_assert(std::is_same<T, R<Default>>::value, "IfValidOr 3");
  }
}
} // namespace IfValidOrTest
