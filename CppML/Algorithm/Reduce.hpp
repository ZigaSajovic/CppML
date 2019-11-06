//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_REDUCE_HPP
#define CPPML_REDUCE_HPP
#include "../Functional/Identity.hpp"

namespace ml {
/*
 * Implementation of Reduce. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct Reduce {
  template <typename Result, typename F, typename T, typename... Ts>
  using f = typename Reduce<static_cast<bool>(
      sizeof...(Ts))>::template f<typename F::template f<Result, T>, F, Ts...>;
};
template <> struct Reduce<false> {
  template <typename Result, typename F> using f = Result;
};
} // namespace Implementations

/*
 * # Reduce:
 * Reduces the parameter pack, as dictated by F, where
 *  * Init: initial type
 *  * F: maps (Init, T) -> Init
 *  * Ts... : parameter pack to execute on
 */
template <typename F, typename Pipe = ml::Identity> struct Reduce {
  template <typename Init, typename... Ts>
  using f = typename Pipe::template f<typename Implementations::Reduce<
      static_cast<bool>(sizeof...(Ts))>::template f<Init, F, Ts...>>;
};
} // namespace ml
#endif
