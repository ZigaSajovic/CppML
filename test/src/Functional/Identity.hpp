#include "CppML/CppML.hpp"

namespace IdentityTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Identity, int>;
    static_assert(std::is_same<T, int>::value, "Identity");
  }
}
} // namespace IdentityTest
