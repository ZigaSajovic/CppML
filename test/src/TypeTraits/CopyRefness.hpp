#include "CppML/CppML.hpp"

namespace CopyRefnessTest {
struct Type0 {};
struct Type1 {};
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0, Type1>;
    static_assert(std::is_same<T, R<Type1>>::value, "CopyRefness _, _");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0, Type1 &>;
    static_assert(std::is_same<T, R<Type1>>::value, "CopyRefness _, &");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0, Type1 &&>;
    static_assert(std::is_same<T, R<Type1>>::value, "CopyRefness _, &&");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0 &, Type1>;
    static_assert(std::is_same<T, R<Type1 &>>::value, "CopyRefness &, _");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0 &, Type1 &>;
    static_assert(std::is_same<T, R<Type1 &>>::value, "CopyRefness &, &");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0 &, Type1 &&>;
    static_assert(std::is_same<T, R<Type1 &>>::value, "CopyRefness &, &&");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0 &&, Type1>;
    static_assert(std::is_same<T, R<Type1 &&>>::value, "CopyRefness &&, _");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0 &&, Type1 &>;
    static_assert(std::is_same<T, R<Type1 &&>>::value, "CopyRefness &&, &");
  }
  {
    using T = ml::f<ml::CopyRefness<ml::F<R>>, Type0 &&, Type1 &&>;
    static_assert(std::is_same<T, R<Type1 &&>>::value, "CopyRefness &&, &&");
  }
}
} // namespace CopyRefnessTest
