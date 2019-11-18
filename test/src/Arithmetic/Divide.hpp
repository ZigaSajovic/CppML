#include "CppML/CppML.hpp"

namespace DivideTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Divide<ml::F<R>>, ml::Int<6>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Int<3>>>::value, "Divide Test.");
  }
}
} // namespace DivideTest
