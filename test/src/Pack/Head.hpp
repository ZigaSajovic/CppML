#include "CppML/CppML.hpp"

namespace HeadTest {
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::Head<1, ml::F<List>>, ml::Int<0>, ml::Int<1>,
                    ml::Int<2>, ml::Int<3>, ml::Int<4>>;
    static_assert(std::is_same<T, List<ml::Int<0>>>::value,
                  "Head with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::Head<2, ml::F<List>>, ml::Int<0>, ml::Int<1>,
                    ml::Int<2>, ml::Int<3>, ml::Int<4>>;
    static_assert(std::is_same<T, List<ml::Int<0>, ml::Int<1>>>::value,
                  "Head with a non-empty pack 2");
  }
  {
    using T =
        ml::f<ml::Head<37, ml::F<List>>, ml::Int<0>, ml::Int<1>, ml::Int<2>,
              ml::Int<3>, ml::Int<4>, ml::Int<5>, ml::Int<6>, ml::Int<7>,
              ml::Int<8>, ml::Int<9>, ml::Int<10>, ml::Int<11>, ml::Int<12>,
              ml::Int<13>, ml::Int<14>, ml::Int<15>, ml::Int<16>, ml::Int<17>,
              ml::Int<18>, ml::Int<19>, ml::Int<20>, ml::Int<21>, ml::Int<22>,
              ml::Int<23>, ml::Int<24>, ml::Int<25>, ml::Int<26>, ml::Int<27>,
              ml::Int<28>, ml::Int<29>, ml::Int<30>, ml::Int<31>, ml::Int<32>,
              ml::Int<33>, ml::Int<34>, ml::Int<35>, ml::Int<36>, ml::Int<37>,
              ml::Int<38>>;
    static_assert(
        std::is_same<
            T, List<ml::Int<0>, ml::Int<1>, ml::Int<2>, ml::Int<3>, ml::Int<4>,
                    ml::Int<5>, ml::Int<6>, ml::Int<7>, ml::Int<8>, ml::Int<9>,
                    ml::Int<10>, ml::Int<11>, ml::Int<12>, ml::Int<13>,
                    ml::Int<14>, ml::Int<15>, ml::Int<16>, ml::Int<17>,
                    ml::Int<18>, ml::Int<19>, ml::Int<20>, ml::Int<21>,
                    ml::Int<22>, ml::Int<23>, ml::Int<24>, ml::Int<25>,
                    ml::Int<26>, ml::Int<27>, ml::Int<28>, ml::Int<29>,
                    ml::Int<30>, ml::Int<31>, ml::Int<32>, ml::Int<33>,
                    ml::Int<34>, ml::Int<35>, ml::Int<36>>>::value,
        "Head with a non-empty pack 37");
  }
}
}; // namespace HeadTest
