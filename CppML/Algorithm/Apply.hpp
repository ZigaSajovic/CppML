//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_APPLY_HPP
#define CPPML_APPLY_HPP
#include "../Functional/ToList.hpp"
#include "../Vocabulary/IfElse.hpp"
namespace ml {
/*
 * Apply:
 * Applies the function to all types
 */
template <typename F, typename Pipe = ToList> struct Apply {
  template <typename... Ts>
  using f = typename IfElse<(sizeof...(Ts) < 10000)>::template f<
      Pipe, void>::template f<typename F::template f<Ts>...>;
};
} // namespace ml
#endif
