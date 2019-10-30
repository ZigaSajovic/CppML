//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_TAIL_HPP
#define CPPML_TAIL_HPP
#include "../Functional/ToList.hpp"
#include "../Vocabulary/IfElse.hpp"

namespace ml {
/*
 * Implementation of Tail. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct TailImpl {
  template <int N, typename Pipe, typename T, typename... Ts>
  using f = typename TailImpl<(sizeof...(Ts) > N)>::template f<N, Pipe, Ts...>;
};

template <> struct TailImpl<false> {
  template <int N, typename Pipe, typename... Ts>
  using f = typename ml::IfElse<(
      sizeof...(Ts) < 100000)>::template f<Pipe, void>::template f<Ts...>;
};
struct Tail {
  template <int N, typename Pipe, typename... Ts>
  using f = typename Implementations::TailImpl<(sizeof...(Ts) >
                                                N)>::template f<N, Pipe, Ts...>;
};
}; // namespace Implementations

/*
 * # Tail:
 * Returns last N elements
 */
template <int N, typename Pipe = ml::ToList> struct Tail {
  template <typename... Ts>
  using f = typename Implementations::TailImpl<(sizeof...(Ts) >
                                                N)>::template f<N, Pipe, Ts...>;
};
} // namespace ml
#endif
