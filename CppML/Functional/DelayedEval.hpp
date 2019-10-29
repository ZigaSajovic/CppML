//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_DELAYED_EVAL_HPP
#define CPPML_DELAYED_EVAL_HPP
#include "../Vocabulary/IfElse.hpp"
namespace ml {
/*
 * # DelayedEval:
 * Delays a call, so compiler knows the number of arguments.
 */
struct DelayedEval {
  template <typename F, typename... Ts>
  using f = typename ml::IfElse<(
      sizeof...(Ts) < 10000)>::template f<F, void>::template f<Ts...>;
};
} // namespace ml
#endif
