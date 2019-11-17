#include "CppML/CppML.hpp"

namespace ComposeTest {
template <typename T> struct F0 {};
template <typename T> struct F1 {};
template <typename T> struct F2 {};
void run() {
  {
    using T = ml::f<ml::Compose<ml::F<F0>, ml::F<F1>, ml::F<F2>>, int>;
    static_assert(std::is_same<T, F0<F1<F2<int>>>>::value, "Compose Test.");
  }
}
} // namespace ComposeTest
