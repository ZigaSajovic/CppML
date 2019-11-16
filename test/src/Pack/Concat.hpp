#include "CppML/CppML.hpp"

namespace ConcatTest {
template <typename T> struct R {};
template <typename... Ts> struct Hold {};
void run() {
  {
    using T = ml::f<ml::Concat<ml::F<R>>, Hold<int, char>, Hold<bool>,
                    Hold<float, double>>;
    static_assert(
        std::is_same<T, R<Hold<int, char, bool, float, double>>>::value,
        "Concat with a non-empty pack");
  }
}
} // namespace ConcatTest
