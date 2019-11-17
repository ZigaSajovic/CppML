#include "CppML/CppML.hpp"

namespace AlignOfTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::AlignOf<ml::F<R>>, double>;
    static_assert(std::is_same<T, R<ml::Int<alignof(double)>>>::value,
                  "AlignOf Test.");
  }
}
} // namespace AlignOfTest
