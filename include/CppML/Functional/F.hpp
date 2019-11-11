/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
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
