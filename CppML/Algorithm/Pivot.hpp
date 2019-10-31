//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PIVOT_HPP
#define CPPML_PIVOT_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/ToList.hpp"
#include "../Vocabulary/Const.hpp"
namespace ml {
namespace Implementations {
struct GetNext {
  template <int i>
  using f = ml::Int<
      i >= 32
          ? 32
          : i >= 16 ? 16
                    : i >= 8 ? 8 : i >= 4 ? 4 : i >= 2 ? 2 : i >= 1 ? 1 : 0>;
};

template <int i> struct Pivot;

template <> struct Pivot<0> {
  template <typename Pipe, typename N, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};

template <> struct Pivot<1> {
  template <typename Pipe, typename N, typename T0, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts..., T0>;
};

template <> struct Pivot<2> {
  template <typename Pipe, typename N, typename T0, typename T1, typename... Ts>
  using f =
      ml::DelayedEval<Pivot<GetNext::f<N::value - 2>::value>, sizeof...(Ts),
                      Pipe, ml::Int<N::value - 2>, Ts..., T0, T1>;
};

template <> struct Pivot<4> {
  template <typename Pipe, typename N, typename T0, typename T1, typename T2,
            typename T3, typename... Ts>
  using f =
      ml::DelayedEval<Pivot<GetNext::f<N::value - 4>::value>, sizeof...(Ts),
                      Pipe, ml::Int<N::value - 4>, Ts..., T0, T1, T2, T3>;
};

template <> struct Pivot<8> {
  template <typename Pipe, typename N, typename T0, typename T1, typename T2,
            typename T3, typename T4, typename T5, typename T6, typename T7,
            typename... Ts>
  using f = ml::DelayedEval<Pivot<GetNext::f<N::value - 8>::value>,
                            sizeof...(Ts), Pipe, ml::Int<N::value - 8>, Ts...,
                            T0, T1, T2, T3, T4, T5, T6, T7>;
};

template <> struct Pivot<16> {
  template <typename Pipe, typename N, typename T0, typename T1, typename T2,
            typename T3, typename T4, typename T5, typename T6, typename T7,
            typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename... Ts>
  using f = ml::DelayedEval<Pivot<get_i(N::value - 16)>, sizeof...(Ts), Pipe,
                            ml::Int<N::value - 16>, Ts..., T0, T1, T2, T3, T4,
                            T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>;
};

template <> struct Pivot<32> {
  template <typename Pipe, typename N, typename T0, typename T1, typename T2,
            typename T3, typename T4, typename T5, typename T6, typename T7,
            typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16,
            typename T17, typename T18, typename T19, typename T20,
            typename T21, typename T22, typename T23, typename T24,
            typename T25, typename T26, typename T27, typename T28,
            typename T29, typename T30, typename T31, typename... Ts>
  using f = ml::DelayedEval<Pivot<GetNext::f<N::value - 32>::value>,
                            sizeof...(Ts), Pipe, ml::Int<N::value - 32>, Ts...,
                            T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                            T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                            T22, T23, T24, T25, T26, T27, T28, T29, T30, T31>;
};
} // namespace Implementations

template <int i, typename Pipe = ml::ToList> struct Pivot {
  template <typename... Ts>
  using f = ml::DelayedEval<
      Implementations::Pivot<Implementations::GetNext::f<i>::value>,
      sizeof...(Ts), Pipe, ml::Int<i>, Ts...>;
};
} // namespace ml
