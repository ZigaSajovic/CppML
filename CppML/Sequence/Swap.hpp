//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_SWAP_HPP
#define CPPML_SWAP_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/ToList.hpp"
#include "../Vocabulary/Const.hpp"
#include "PackExtractor.hpp"
namespace ml {
namespace Implementations {
/*
 * Implementation of Swap. It only ever instantiates 2 types.
 */
template <bool Continue> struct SwapImpl {
  template <typename M, typename N, typename start, typename end, typename Pipe,
            typename Getter, typename... Ts>
  using f = typename ml::DelayedEval<
      SwapImpl<(start::value + 1 < end::value)>, sizeof...(Ts), M, N,
      ml::Int<start::value + 1>, end, Pipe, Getter, Ts...,
      typename Getter::template f<
          ml::Int<(start::value != M::value && start::value != N::value) *
                      start::value +
                  (start::value == N::value) * M::value +
                  (start::value == M::value) * N::value>>>;
};

template <> struct SwapImpl<false> {
  template <typename M, typename N, typename start, typename end, typename Pipe,
            typename Getter, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
struct Swap {
  template <int M, int N, typename Pipe, typename... Ts>
  using f = typename Implementations::SwapImpl<static_cast<bool>(sizeof...(
      Ts))>::template f<ml::Int<M>, ml::Int<N>, ml::Int<0>,
                        ml::Int<sizeof...(Ts)>, Pipe, ml::PackExtractor<Ts...>>;
};
}; // namespace Implementations
/*
 * # Swap:
 * Swaps `M`-th and `N`-th element of the paramater pack.
 */
template <int M, int N, typename Pipe = ml::ToList> struct Swap {
  template <typename... Ts>
  using f = typename Implementations::SwapImpl<static_cast<bool>(sizeof...(
      Ts))>::template f<ml::Int<M>, ml::Int<N>, ml::Int<0>,
                        ml::Int<sizeof...(Ts)>, Pipe, ml::PackExtractor<Ts...>>;
};
} // namespace ml
#endif
