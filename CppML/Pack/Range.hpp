//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_RANGE_HPP
#define CPPML_RANGE_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/ToList.hpp"
#include "../Vocabulary/Const.hpp"
#include "../Vocabulary/List.hpp"
namespace ml {
namespace Implementations {
template <bool shouldContinue, typename Pipe> struct TypeRangeBase;

template <typename Pipe> struct TypeRangeBase<true, Pipe> {
  template <typename From, typename To, typename step, typename... Us>
  using f = ml::DelayedEval<
      TypeRangeBase<(step::value > 0 ? From::value + step::value < To::value
                                     : To::value < From::value + step::value),
                    Pipe>,
      sizeof...(Us), Int<From::value + step::value>, To, step, Us..., From>;
};

template <typename Pipe> struct TypeRangeBase<false, Pipe> {
  template <typename From, typename To, typename step, typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts...>;
};
}; // namespace Implementations
/*
 * TypeRange:
 * Creates a range of Int types
 */
template <typename Pipe = ToList> struct TypeRange {
  template <int From, int To, int step = 1>
  using f = typename Implementations::TypeRangeBase<
      (step > 0 ? From < To : To < From), Pipe>::template f<Int<From>, Int<To>,
                                                            Int<step>>;
};
}; // namespace ml
#endif
