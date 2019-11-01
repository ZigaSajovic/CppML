//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ROTATE_HPP
#define CPPML_ROTATE_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Partial.hpp"
#include "../Functional/ToList.hpp"
#include "../Pack/Drop.hpp"
#include "../Pack/Head.hpp"
namespace ml {
/*
 * # Rotate:
 * Rotates a pack, so that the subpack `[First, Last)`, is pivoted around
 * Middle.
 * ```
 * (Start, ..., First, ..., M',  Middle, ..., L', Last, ... End)
 * ->
 *  (Start, ..., Middle, ..., L', First, ... M', Last, ...End)
 *  ```
 */
template <int First, int Middle, int Last, typename Pipe = ml::ToList>
struct Rotate {
  template <typename... Ts>
  using f = ml::DelayedEval<
      ml::Drop<
          First,
          ml::Head<
              Last - First,
              ml::Pivot<
                  Middle - First,
                  ml::DelayedEval<
                      ml::Head<First,
                               ml::PrePartialEvaluator<ml::DelayedEval<
                                   ml::Drop<Last, ml::PartialEvaluator<Pipe>>,
                                   sizeof...(Ts), Ts...>>>,
                      sizeof...(Ts), Ts...>>>>,
      sizeof...(Ts), Ts...>;
};

template <int N, typename Pipe> struct Rotate<N, N, N + 1, Pipe> {
  template <typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
} // namespace ml
#endif
