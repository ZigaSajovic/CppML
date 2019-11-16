#include "CppML/CppML.hpp"

namespace InclusiveScanTest {
template <typename T, typename U> struct MF {};
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::InclusiveScan<ml::F<MF>, ml::F<List>>, int, char, bool>;
    static_assert(
        std::is_same<T,
                     List<int, MF<int, char>, MF<MF<int, char>, bool>>>::value,
        "InclusiveScan with a non-empty pack");
  }
  {
    using T = ml::f<ml::InclusiveScan<ml::F<MF>, ml::F<List>>>;
    static_assert(std::is_same<T, List<>>::value,
                  "InclusiveScan with a non-empty pack");
  }
}
} // namespace InclusiveScanTest
