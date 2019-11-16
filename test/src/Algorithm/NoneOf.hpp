#include "CppML/CppML.hpp"
#include <string>
#include <vector>

namespace NoneOfTest {
template <typename T> using Predicate = std::is_class<T>;
void run() {
  {
    using T = ml::f<ml::NoneOf<ml::F<Predicate>>, int, char, std::string>;
    static_assert(std::is_same<T, ml::Bool<false>>::value,
                  "NoneOf with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::NoneOf<ml::F<Predicate, ml::Not<>>>, std::vector<int>,
                    std::string>;
    static_assert(std::is_same<T, ml::Bool<true>>::value,
                  "NoneOf with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::NoneOf<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::Bool<true>>::value,
                  "NoneOf with empty pack");
  }
}
} // namespace NoneOfTest
