#include "CppML/CppML.hpp"

namespace InvokeWithTest {
template <typename... Ts> struct MF {};
void run() {
  {
    using T = ml::f<ml::InvokeWith<int, char, bool>, ml::F<MF>>;
    static_assert(std::is_same<T, MF<int, char, bool>>::value,
                  "InvokeWith Test");
  }
}
} // namespace InvokeWithTest
