#include "CppML/CppML.hpp"

namespace IncrementTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Increment<ml::F<R>>, ml::Int<0>>;
    static_assert(std::is_same<T, R<ml::Int<1>>>::value, "Increment Test.");
  }
}
} // namespace IncrementTest
