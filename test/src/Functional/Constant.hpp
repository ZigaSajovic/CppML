#include "CppML/CppML.hpp"

namespace ConstantTest {
struct Const {};
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Constant<Const, ml::F<R>>, int, char, bool>;
    static_assert(std::is_same<T, R<Const>>::value, "Compose Test.");
  }
}
} // namespace ConstantTest
