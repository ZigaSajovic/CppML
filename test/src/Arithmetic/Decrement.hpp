#include "CppML/CppML.hpp"

namespace DecrementTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Decrement<ml::F<R>>, ml::Int<1>>;
    static_assert(std::is_same<T, R<ml::Int<0>>>::value, "Decrement Test.");
  }
}
} // namespace DecrementTest
