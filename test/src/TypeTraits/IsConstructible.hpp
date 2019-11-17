#include "CppML/CppML.hpp"

namespace IsConstructibleTest {
struct Class {
  int x;
  Class(int x) : x{x} {}
};
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::IsConstructible<ml::F<R>>, Class, int>;
    static_assert(
        std::is_same<
            T, R<ml::Bool<std::is_constructible<Class, int>::value>>>::value,
        "IsConstructible Test True.");
  }
  {
    using T = ml::f<ml::IsConstructible<ml::F<R>>, Class, int *>;
    static_assert(
        std::is_same<
            T, R<ml::Bool<std::is_constructible<Class, int *>::value>>>::value,
        "IsConstructible Test False.");
  }
}
} // namespace IsConstructibleTest
