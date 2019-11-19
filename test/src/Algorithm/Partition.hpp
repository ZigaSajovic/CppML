#include "CppML/CppML.hpp"

namespace PartitionTest {
template <typename T> using Size = ml::Bool<(sizeof(T) > 4)>;
template <typename... Ts> struct List {};
struct Type0 {
  char _[4];
};
struct Type1 {
  char _[6];
};
struct Type2 {
  char _[4];
};
struct Type3 {
  char _[6];
};
void run() {
  {
    using T = ml::f<ml::Partition<ml::F<Size>, ml::F<List>>, Type0, Type1,
                    Type2, Type3>;
    static_assert(
        std::is_same<
            T, List<ml::ListT<Type1, Type3>, ml::ListT<Type0, Type2>>>::value,
        "Partition with a non-empty pack");
  }
  {
    using T = ml::f<ml::Partition<ml::F<Size>, ml::F<List>>>;
    static_assert(std::is_same<T, List<ml::ListT<>, ml::ListT<>>>::value,
                  "Partition with an empty pack");
  }
}
} // namespace PartitionTest
