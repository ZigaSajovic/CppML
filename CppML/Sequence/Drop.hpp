//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_DROP_HPP
#define CPPML_DROP_HPP
#include "../Functional/ToList.hpp"

namespace ml {
/*
 * Implementation of Drop. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Countinue> struct Drop {
  template <int i, typename Pipe, typename T, typename... Ts>
  using f = typename Drop<static_cast<bool>(sizeof...(Ts)) &&
                          (i > 1)>::template f<i - 1, Pipe, Ts...>;
};
template <> struct Drop<false> {
  template <int i, typename Pipe, typename... Ts>
  using f = typename Pipe::template f<Ts...>;
};
} // namespace Implementations
/*
 * # Drop:
 * Drop first N elements of a parameter pack.
 */
template <int N, typename Pipe = ml::ToList> struct Drop {
  template <typename... Ts>
  using f = typename Implementations::Drop<static_cast<bool>(sizeof...(Ts)) &&
                                           (N > 0)>::template f<N, Pipe, Ts...>;
};

} // namespace ml
#endif
