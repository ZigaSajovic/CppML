//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_F_HPP
#define CPPML_F_HPP
#include "DelayedEval.hpp"
#include "Identity.hpp"
#include "Invoke.hpp"

namespace ml {
/*
 * F:
 * Creates a metafunction out of a template
 */
template <template <class...> class F_, typename Pipe = ml::Identity> struct F {
  template <typename... Args>
  using f = ml::f<Pipe, ml::DelayedAliasEval<F_, sizeof...(Args), Args...>>;
};
} // namespace ml
#endif
