#include "CppML/CppML.hpp"

namespace IsConvertibleTest {
struct Converted {};
struct Class {
  operator Converted() { return Converted{}; };
};
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::IsConvertible<ml::F<R>>, Class, Converted>;
    static_assert(
        std::is_same<
            T,
            R<ml::Bool<std::is_convertible<Class, Converted>::value>>>::value,
        "IsConvertible Test True.");
  }
  {
    using T = ml::f<ml::IsConvertible<ml::F<R>>, Class, int *>;
    static_assert(
        std::is_same<
            T, R<ml::Bool<std::is_convertible<Class, int *>::value>>>::value,
        "IsConvertible Test False.");
  }
}
} // namespace IsConvertibleTest
