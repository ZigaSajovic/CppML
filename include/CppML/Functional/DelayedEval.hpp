/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_DELAYED_EVAL_HPP
#define CPPML_DELAYED_EVAL_HPP
#include "./IfElse.hpp"
namespace ml {
/*
 * # DelayedEval:
 * Delays a call, so compiler knows the number of arguments.
 */
template <typename F, int N>
using DelayedEval =
    typename ml::Implementations::IfElse<(N < 10000)>::template f<F, void>;

namespace Implementations {
template <bool> struct DelayTemplateEval {
  template <template <class...> class F0, typename... Ts> using f = F0<Ts...>;
};
template <> struct DelayTemplateEval<false> {
  template <template <class...> class F0, typename... Ts> using f = F0<>;
};
} // namespace Implementations
/*
 * # DelayedAliasEval:
 * Delays an alias call, so compiler knows the number of arguments.
 */
template <template <class...> class F, int N, typename... Ts>
using DelayedAliasEval = typename Implementations::DelayTemplateEval<(
    N < 100000)>::template f<F, Ts...>;
} // namespace ml
#endif
