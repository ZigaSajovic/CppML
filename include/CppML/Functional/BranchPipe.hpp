/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_BRANCH_PIPE_HPP
#define CPPML_BRANCH_PIPE_HPP
#include "./DelayedEval.hpp"
#include "./IfElse.hpp"

namespace ml {
/*
 * # BranchPipe:
 * Passes Ts... to either pipe, given a predicate
 */
template <typename Predicate, typename IfPipe, typename ElsePipe>
struct BranchPipe {
  template <typename... Ts>
  using f =
      ml::f<ml::DelayedEval<
                ml::f<ml::IfElse<ml::f<
                          ml::DelayedEval<Predicate, sizeof...(Ts)>, Ts...>>,
                      IfPipe, ElsePipe>,
                sizeof...(Ts)>,
            Ts...>;
};
} // namespace ml
#endif
