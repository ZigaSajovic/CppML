#include "CppML/CppML.hpp"

namespace PartitionIdsTest {
template <typename T> using AlignPart = ml::Bool<(alignof(T) > 4)>;
void run() {
  {
    using T =
        ml::f<ml::PartitionIds<ml::F<AlignPart>>, int, long, char, double>;
    static_assert(
        std::is_same<T, ml::ListT<ml::ListT<ml::Int<1>, ml::Int<3>>,
                                  ml::ListT<ml::Int<0>, ml::Int<2>>>>::value,
        "PartitionIds with a non-empty pack");
  }
  {
    using T = ml::f<ml::PartitionIds<ml::F<AlignPart>>>;
    static_assert(std::is_same<T, ml::ListT<ml::ListT<>, ml::ListT<>>>::value,
                  "PartitionIds with an empty pack");
  }
}
} // namespace PartitionIdsTest
