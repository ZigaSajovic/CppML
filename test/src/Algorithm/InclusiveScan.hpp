#include "CppML/CppML.hpp"

namespace InclusiveScanTest {
template <typename T, typename U> struct MF {};
void run() {
  {
    using T = ml::f<ml::InclusiveScan<ml::F<MF>>, int, char, bool>;
    static_assert(
        std::is_same<
            T, ml::ListT<int, MF<int, char>, MF<MF<int, char>, bool>>>::value,
        "InclusiveScan with a non-empty pack");
  }
  {
    using T = ml::f<ml::InclusiveScan<ml::F<MF>>>;
    static_assert(std::is_same<T, ml::ListT<>>::value,
                  "InclusiveScan with a non-empty pack");
  }
}
} // namespace InclusiveScanTest
