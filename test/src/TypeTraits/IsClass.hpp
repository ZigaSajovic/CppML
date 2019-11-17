#include "CppML/CppML.hpp"

namespace IsClassTest {
struct Class {};
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::IsClass<ml::F<R>>, double>;
    static_assert(
        std::is_same<T, R<ml::Bool<std::is_class<double>::value>>>::value,
        "IsClass Test False.");
  }
  {
    using T = ml::f<ml::IsClass<ml::F<R>>, Class>;
    static_assert(
        std::is_same<T, R<ml::Bool<std::is_class<Class>::value>>>::value,
        "IsClass Test True.");
  }
}
} // namespace IsClassTest
