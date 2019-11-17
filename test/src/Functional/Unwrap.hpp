#include "CppML/CppML.hpp"

namespace UnwrapTest {
template <typename... Ts> struct List0 {};
template <typename... Ts> struct List1 {};
void run() {
  {
    using T = ml::f<ml::Unwrap<ml::F<List1>>, List0<int, char, bool>>;
    static_assert(std::is_same<T, List1<int, char, bool>>::value,
                  "Unwrap Test.");
  }
}
} // namespace Unwrap
