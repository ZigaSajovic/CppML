/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_PARTIAL_R_HPP
#define CPPML_PARTIAL_R_HPP
#include "./DelayedEval.hpp"
namespace ml {
/*
 * PartialR:
 * Partial evaluation of a metafunction, from the right
 */
template <typename F, typename... Ts> struct PartialR {
  template <typename... Us>
  using f = ml::DelayedEval<F, (sizeof...(Us) + sizeof...(Ts)), Us..., Ts...>;
};
} // namespace ml
#endif
