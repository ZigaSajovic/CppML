#include "CppML/CppML.hpp"

namespace MapTest {
template <typename T> struct R {};
template <typename T> using MF = R<T>;
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::Map<ml::F<MF>, ml::F<List>>, char, bool, double>;
    static_assert(std::is_same<T, List<R<char>, R<bool>, R<double>>>::value,
                  "Map Test.");
  }
}
} // namespace MapTest
