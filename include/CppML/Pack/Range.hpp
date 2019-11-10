//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_RANGE_HPP
#define CPPML_RANGE_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/ToList.hpp"
#include "../Vocabulary/List.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
namespace Implementations {
template <bool shouldContinue, typename Pipe> struct RangeBase;

template <typename Pipe> struct RangeBase<true, Pipe> {
  template <typename From, typename To, typename Step, typename... Us>
  using f = ml::DelayedEval<
      RangeBase<(Step::value > 0 ? From::value + Step::value < To::value
                                 : To::value < From::value + Step::value),
                Pipe>,
      sizeof...(Us), Int<From::value + Step::value>, To, Step, Us..., From>;
};

template <typename Pipe> struct RangeBase<false, Pipe> {
  template <typename From, typename To, typename step, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
}; // namespace Implementations
/*
 * Range:
 * Creates a range of Int types
 */
template <typename Pipe = ToList> struct Range {
  template <int From, int To, int Step = 1>
  using f =
      typename Implementations::RangeBase<(Step > 0 ? From < To : To < From),
                                          Pipe>::template f<Int<From>, Int<To>,
                                                            Int<Step>>;
};
}; // namespace ml
#endif