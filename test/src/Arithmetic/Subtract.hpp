#include "CppML/CppML.hpp"

namespace SubtractTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Subtract<ml::F<R>>, ml::Int<3>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Int<1>>>::value, "Subtract Test.");
  }
}
} // namespace SubtractTest
