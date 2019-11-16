#include "CppML/CppML.hpp"

namespace BranchPipeTest {
template <typename T> struct True {};
template <typename T> using TruePipe = True<T>;
template <typename T> struct False {};
template <typename T> using FalsePipe = False<T>;
template <typename T> using TruthPredicate = ml::Bool<true>;
template <typename T> using FalsePredicate = ml::Bool<false>;
void run() {
  {
    using T = ml::f<ml::BranchPipe<ml::F<TruthPredicate>, ml::F<TruePipe>,
                                   ml::F<FalsePipe>>,
                    int>;
    static_assert(std::is_same<T, True<int>>::value, "BranchPipe True");
  }
  {
    using T = ml::f<ml::BranchPipe<ml::F<FalsePredicate>, ml::F<TruePipe>,
                                   ml::F<FalsePipe>>,
                    int>;
    static_assert(std::is_same<T, False<int>>::value, "BranchPipe False");
  }
}
} // namespace BranchPipeTest
