#include "CppML/CppML.hpp"

namespace PivotTest {
template <typename... Ts> struct List {};
void run() {
  {
    using T = ml::f<ml::Pivot<2, ml::F<List>>, int, char, int>;
    static_assert(std::is_same<T, List<int, int, char>>::value,
                  "Pivot with a non-empty pack");
  }
  {
    using T =
        ml::f<ml::Pivot<34, ml::F<List>>, ml::Int<0>, ml::Int<1>, ml::Int<2>,
              ml::Int<3>, ml::Int<4>, ml::Int<5>, ml::Int<6>, ml::Int<7>,
              ml::Int<8>, ml::Int<9>, ml::Int<10>, ml::Int<11>, ml::Int<12>,
              ml::Int<13>, ml::Int<14>, ml::Int<15>, ml::Int<16>, ml::Int<17>,
              ml::Int<18>, ml::Int<19>, ml::Int<20>, ml::Int<21>, ml::Int<22>,
              ml::Int<23>, ml::Int<24>, ml::Int<25>, ml::Int<26>, ml::Int<27>,
              ml::Int<28>, ml::Int<29>, ml::Int<30>, ml::Int<31>, ml::Int<32>,
              ml::Int<33>, ml::Int<34>, ml::Int<35>, ml::Int<36>, ml::Int<37>,
              ml::Int<38>>;
    static_assert(
        std::is_same<T, List<ml::Int<34>, ml::Int<35>, ml::Int<36>, ml::Int<37>,
                             ml::Int<38>, ml::Int<0>, ml::Int<1>, ml::Int<2>,
                             ml::Int<3>, ml::Int<4>, ml::Int<5>, ml::Int<6>,
                             ml::Int<7>, ml::Int<8>, ml::Int<9>, ml::Int<10>,
                             ml::Int<11>, ml::Int<12>, ml::Int<13>, ml::Int<14>,
                             ml::Int<15>, ml::Int<16>, ml::Int<17>, ml::Int<18>,
                             ml::Int<19>, ml::Int<20>, ml::Int<21>, ml::Int<22>,
                             ml::Int<23>, ml::Int<24>, ml::Int<25>, ml::Int<26>,
                             ml::Int<27>, ml::Int<28>, ml::Int<29>, ml::Int<30>,
                             ml::Int<31>, ml::Int<32>, ml::Int<33>>>::value,
        "Pivot with a non-empty pack 31");
  }
  {
    using T =
        ml::f<ml::Pivot<63, ml::F<List>>, ml::Int<0>, ml::Int<1>, ml::Int<2>,
              ml::Int<3>, ml::Int<4>, ml::Int<5>, ml::Int<6>, ml::Int<7>,
              ml::Int<8>, ml::Int<9>, ml::Int<10>, ml::Int<11>, ml::Int<12>,
              ml::Int<13>, ml::Int<14>, ml::Int<5>, ml::Int<16>, ml::Int<17>,
              ml::Int<18>, ml::Int<19>, ml::Int<20>, ml::Int<21>, ml::Int<22>,
              ml::Int<23>, ml::Int<24>, ml::Int<25>, ml::Int<26>, ml::Int<27>,
              ml::Int<28>, ml::Int<29>, ml::Int<30>, ml::Int<31>, ml::Int<32>,
              ml::Int<33>, ml::Int<34>, ml::Int<35>, ml::Int<36>, ml::Int<37>,
              ml::Int<38>, ml::Int<39>, ml::Int<40>, ml::Int<41>, ml::Int<42>,
              ml::Int<43>, ml::Int<44>, ml::Int<45>, ml::Int<46>, ml::Int<47>,
              ml::Int<48>, ml::Int<49>, ml::Int<50>, ml::Int<51>, ml::Int<52>,
              ml::Int<53>, ml::Int<54>, ml::Int<55>, ml::Int<56>, ml::Int<57>,
              ml::Int<58>, ml::Int<59>, ml::Int<60>, ml::Int<61>, ml::Int<62>,
              ml::Int<63>, ml::Int<64>>;
    static_assert(
        std::is_same<
            T,
            List<
                ml::Int<63>, ml::Int<64>, ml::Int<0>, ml::Int<1>, ml::Int<2>,
                ml::Int<3>, ml::Int<4>, ml::Int<5>, ml::Int<6>, ml::Int<7>,
                ml::Int<8>, ml::Int<9>, ml::Int<10>, ml::Int<11>, ml::Int<12>,
                ml::Int<13>, ml::Int<14>, ml::Int<5>, ml::Int<16>, ml::Int<17>,
                ml::Int<18>, ml::Int<19>, ml::Int<20>, ml::Int<21>, ml::Int<22>,
                ml::Int<23>, ml::Int<24>, ml::Int<25>, ml::Int<26>, ml::Int<27>,
                ml::Int<28>, ml::Int<29>, ml::Int<30>, ml::Int<31>, ml::Int<32>,
                ml::Int<33>, ml::Int<34>, ml::Int<35>, ml::Int<36>, ml::Int<37>,
                ml::Int<38>, ml::Int<39>, ml::Int<40>, ml::Int<41>, ml::Int<42>,
                ml::Int<43>, ml::Int<44>, ml::Int<45>, ml::Int<46>, ml::Int<47>,
                ml::Int<48>, ml::Int<49>, ml::Int<50>, ml::Int<51>, ml::Int<52>,
                ml::Int<53>, ml::Int<54>, ml::Int<55>, ml::Int<56>, ml::Int<57>,
                ml::Int<58>, ml::Int<59>, ml::Int<60>, ml::Int<61>,
                ml::Int<62>>>::value,
        "Pivot with 63");
  }
  {
    using T = ml::f<ml::Pivot<0, ml::F<List>>, int, char, float>;
    static_assert(std::is_same<T, List<int, char, float>>::value,
                  "Pivot with a non-empty pack: 0");
  }
}
} // namespace PivotTest
