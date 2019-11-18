#include "CppML/CppML.hpp"

namespace AddTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Add<ml::F<R>>, ml::Int<1>, ml::Int<2>>;
    static_assert(std::is_same<T, R<ml::Int<3>>>::value, "Add Test.");
  }
}
} // namespace AddTest
