#include "CppML/CppML.hpp"

namespace ToListTest {
void run() {
  {
    using T = ml::f<ml::ToList, int, char, bool>;
    static_assert(std::is_same<T, ml::ListT<int, char, bool>>::value,
                  "ToList Test.");
  }
}
} // namespace ToListTest
