//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_GREATER_HPP
#define CPPML_GREATER_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
namespace ml {
/*
 * Greater:
 * Greater than meta function
 */
template <typename Pipe = Identity> struct Greater {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<Bool<(T1::value > T2::value)>>;
};

} // namespace ml
#endif
