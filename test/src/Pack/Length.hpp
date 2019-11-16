#include "CppML/CppML.hpp"

namespace LengthTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Length<ml::F<R>>, int, char, bool>;
    static_assert(std::is_same<T, R<ml::Int<3>>>::value,
                  "Get with a non-empty pack 0");
  }
}
} // namespace LengthTest
