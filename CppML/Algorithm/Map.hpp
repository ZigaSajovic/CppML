//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_MAP_HPP
#define CPPML_MAP_HPP
#include "../Functional/ToList.hpp"
#include "../Vocabulary/IfElse.hpp"
namespace ml {
/*
 * # Map:
 * Maps each element using `F`
 */
template <typename F, typename Pipe = ToList> struct Map {
  template <typename... Ts>
  using f = typename IfElse<(sizeof...(Ts) < 10000)>::template f<
      Pipe, void>::template f<typename F::template f<Ts>...>;
};
} // namespace ml
#endif
