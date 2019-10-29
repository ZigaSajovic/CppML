//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_GET_HPP
#define CPPML_GET_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/IfElse.hpp"

namespace ml {
/*
 * Implementation of Get. It only ever instantiates two types.
 * This means that it will not instantiate a type for each N. So
 * One can use this, when needed.
 */
namespace Implementations {
template <bool Continue> struct Get {
  template <int i, typename T, typename... Ts>
  using f = typename ml::IfElse<static_cast<bool>(
      sizeof...(Ts))>::template f<Get<(i > 1)>, void>::template f<i - 1, Ts...>;
};

template <> struct Get<false> {
  template <int i, typename T, typename... Ts> using f = T;
};
}; // namespace Implementations

/*
 * Get:
 * Retrives the N-th element in a pack. Instantiates a type
 * for each N.
 */
template <int N, typename Pipe = ml::Identity> struct Get {
  template <typename... Ts>
  using f = typename Implementations::Get<(sizeof...(Ts) >= 0) &&
                                          N != 0>::template f<N, Ts...>;
};
} // namespace ml
#endif
