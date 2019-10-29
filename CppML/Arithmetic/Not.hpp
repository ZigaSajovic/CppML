//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_NOT_HPP
#define CPPML_NOT_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
namespace ml {
/*
 * Not:
 * Negation
 */
template <typename Pipe = Identity> struct Not {
  template <typename T>
  using f = typename Pipe::template f<Bool<!static_cast<bool>(T::value)>>;
};

} // namespace ml
#endif
