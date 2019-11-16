#include "CppML/CppML.hpp"

namespace GetTest {
template <typename T> struct R {};
void run() {
  {
    using T = ml::f<ml::Get<0, ml::F<R>>, char, int, int, int, int, int, int,
                    int, int>;
    static_assert(std::is_same<T, R<char>>::value,
                  "Get with a non-empty pack 0");
  }
  {
    using T = ml::f<ml::Get<1, ml::F<R>>, int, char, int, int, int, int, int,
                    int, int>;
    static_assert(std::is_same<T, R<char>>::value,
                  "Get with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::Get<2, ml::F<R>>, int, int, char, int, int, int, int,
                    int, int>;
    static_assert(std::is_same<T, R<char>>::value,
                  "Get with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::Get<3, ml::F<R>>, int, int, int, char, int, int, int,
                    int, int>;
    static_assert(std::is_same<T, R<char>>::value,
                  "Get with a non-empty pack 3");
  }
  {
    using T = ml::f<ml::Get<4, ml::F<R>>, int, int, int, int, char, int, int,
                    int, int>;
    static_assert(std::is_same<T, R<char>>::value,
                  "Get with a non-empty pack 4");
  }
  {
    using T = ml::f<ml::Get<7, ml::F<R>>, int, int, int, int, int, int, int,
                    char, int>;
    static_assert(std::is_same<T, R<char>>::value,
                  "Get with a non-empty pack 4");
  }
  {
    using T = ml::f<ml::Get<37, ml::F<R>>, int, int, int, int, int, int, int,
                    int, int, int, int, int, int, int, int, int, int, int, int,
                    int, int, int, int, int, int, int, int, int, int, int, int,
                    int, int, int, int, int, int, char, int>;
    static_assert(std::is_same<T, R<char>>::value,
                  "Get with a non-empty pack 37");
  }
}
}; // namespace GetTest
