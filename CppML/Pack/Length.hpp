//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_LENGTH_HPP
#define CPPML_LENGTH_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
/*
 * Length:
 * Length of a List-like
 */
template <typename Pipe = ml::Identity> struct Length {
  template <typename... Ts> using f = ml::Int<sizeof...(Ts)>;
};
} // namespace ml
#endif
