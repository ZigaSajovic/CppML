//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PARTIAL_HPP
#define CPPML_PARTIAL_HPP
#include "DelayedEval.hpp"
namespace ml {
/*
 * Partial:
 * Partial evaluation of a metafunction
 */
template <typename F, typename... Ts> struct Partial {
  template <typename... Us>
  using f = DelayedEval<F, (sizeof...(Us) + sizeof...(Ts)), Ts..., Us...>;
};
} // namespace ml
#endif
