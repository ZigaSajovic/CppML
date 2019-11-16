#include "CppML/CppML.hpp"

namespace FrontTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Front<ml::F<R>>, int, float, char, bool>;
    static_assert(std::is_same<T, R<int>>::value,
                  "Front with a non-empty pack 1");
  }
}
}; // namespace FrontTest
