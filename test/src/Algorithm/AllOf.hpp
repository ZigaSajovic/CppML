#include "CppML/CppML.hpp"
#include <string>
#include <vector>

namespace AllOfTest {
template <typename T> using Predicate = std::is_class<T>;
void run() {
  {
    using T = ml::f<ml::AllOf<ml::F<Predicate>>, int, char, std::string>;
    static_assert(std::is_same<T, ml::Bool<false>>::value,
                  "AllOf with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::AllOf<ml::F<Predicate>>, std::vector<int>, std::string>;
    static_assert(std::is_same<T, ml::Bool<true>>::value,
                  "AllOf with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::AllOf<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::Bool<true>>::value,
                  "AllOf with empty pack");
  }
}
} // namespace AllOfTest
