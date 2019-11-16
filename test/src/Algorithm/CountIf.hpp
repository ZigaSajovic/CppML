#include "CppML/CppML.hpp"
#include <string>
#include <vector>

namespace CountIfTest {
template <typename T> using Predicate = ml::f<ml::IsSame<>, int, T>;
void run() {
  {
    using T = ml::f<ml::CountIf<ml::F<Predicate>>, int, char, std::string>;
    static_assert(std::is_same<T, ml::Int<1>>::value,
                  "CountIf with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::CountIf<ml::F<Predicate>>, int, char, std::string, int>;
    static_assert(std::is_same<T, ml::Int<2>>::value,
                  "CountIf with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::CountIf<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::Int<0>>::value,
                  "CountIf with empty pack");
  }
}
} // namespace CountIfTest
