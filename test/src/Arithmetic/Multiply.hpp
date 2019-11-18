#include "CppML/CppML.hpp"

namespace MultiplyTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Multiply<ml::F<R>>, ml::Int<2>, ml::Int<3>>;
    static_assert(std::is_same<T, R<ml::Int<6>>>::value, "Multiply Test.");
  }
}
} // namespace MultiplyTest
