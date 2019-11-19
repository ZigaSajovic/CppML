/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_ROTATE_HPP
#define CPPML_ROTATE_HPP
#include "../Functional/Curry.hpp"
#include "../Functional/CurryR.hpp"
#include "../Functional/DelayedEval.hpp"
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
  using f = ml::f<ml::DelayedEval<
      ml::Drop<
          First,
          ml::Head<Last - First,
                   ml::Pivot<
                       Middle - First,
                       ml::f<ml::DelayedEval<
                           ml::Head<First, ml::Curry<ml::f<ml::DelayedEval<
                                               ml::Drop<Last, ml::CurryR<Pipe>>,
                                               sizeof...(Ts)>, Ts...>>>,
                           sizeof...(Ts)>, Ts...>>>>,
      sizeof...(Ts)>, Ts...>;
};

template <int First, int Last, typename Pipe>
struct Rotate<First, First, Last, Pipe> {
  template <typename... Ts>
  using f = ml::f<ml::DelayedEval<Pipe, sizeof...(Ts)>, Ts...>;
};
} // namespace ml
#endif
