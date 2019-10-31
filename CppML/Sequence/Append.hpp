//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_APPEND_HPP
#define CPPML_APPEND_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/ToList.hpp"
namespace ml {
/*
 * Append:
 * Appends elements to a list-like structure
 */
template <typename T, typename Pipe = ml::ToList> struct Append {
  template <typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), Ts..., T>;
};
} // namespace ml
#endif
