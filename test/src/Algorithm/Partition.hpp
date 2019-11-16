#include "CppML/CppML.hpp"

namespace PartitionTest {
template <typename T> using AlignPart = ml::Bool<(alignof(T) > 4)>;
void run() {
  {
    using T = ml::f<ml::Partition<ml::F<AlignPart>>, int, long, char, double>;
    static_assert(
        std::is_same<
            T, ml::ListT<ml::ListT<long, double>, ml::ListT<int, char>>>::value,
        "Partition with a non-empty pack");
  }
  {
    using T = ml::f<ml::Partition<ml::F<AlignPart>>>;
    static_assert(std::is_same<T, ml::ListT<ml::ListT<>, ml::ListT<>>>::value,
                  "Partition with an empty pack");
  }
}
} // namespace PartitionTest
