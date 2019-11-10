//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_MAP_HPP
#define CPPML_MAP_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/ToList.hpp"
namespace ml {
/*
 * # Map:
 * Maps each element using `F`
 */
template <typename F, typename Pipe = ToList> struct Map {
  template <typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts),
                            ml::DelayedEval<F, sizeof...(Ts), Ts>...>;
};
} // namespace ml
#endif
