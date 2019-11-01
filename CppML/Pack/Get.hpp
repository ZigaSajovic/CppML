//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_GET_HPP
#define CPPML_GET_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Identity.hpp"
#include "Drop.hpp"
#include "Head.hpp"
namespace ml {
/*
 * Get:
 * Retrives the N-th element in a pack.
 */
template <int N, typename Pipe = ml::Identity> struct Get {
  template <typename... Ts>
  using f = ml::DelayedEval<ml::Pivot<N, ml::Head<1>>, sizeof...(Ts), Ts...>;
};
} // namespace ml
#endif
