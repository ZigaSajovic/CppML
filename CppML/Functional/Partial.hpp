//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PARTIAL_HPP
#define CPPML_PARTIAL_HPP
#include "DelayedEval.hpp"
#include "F.hpp"
namespace ml {
/*
 * Partial:
 * Partial evaluation of a metafunction
 */
template <typename Pipe, typename... Ts> struct Partial {
  template <typename... Us>
  using f = ml::DelayedEval<Pipe, (sizeof...(Us)+ sizeof...(Ts)), Us..., Ts...>;
};

/*
 * lPartial:
 * Partial evaluation of a metaList like
 */
template <template <class...> class Pipe, typename... Ts> struct lPartial {
  template <typename... Us> using f = Pipe<Us..., Ts...>;
};

/*
 * PrePartial:
 * Partial evaluation of a metafunction
 */
template <typename Pipe, typename... Ts> struct PrePartial {
  template <typename... Us>
  using f = DelayedEval<Pipe, (sizeof...(Us)+ sizeof...(Ts)), Ts..., Us...>;
};
/*
 * PartialA:
 * Partial evaluation of a metafunction
 */
#ifdef __cpp_nontype_template_parameter_auto
template <typename Pipe, auto... Ts> struct PartialA {
  template <typename... Us>
  using f =
      typename ml::IfElse<(sizeof...(Ts) < 10000 && sizeof...(Us) < 10000)>::
          template f<Pipe, void>::template f<Us..., Ts...>;
};
#endif
} // namespace ml
#endif
