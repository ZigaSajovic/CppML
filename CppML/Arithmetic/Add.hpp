//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ADD_HPP
#define CPPML_ADD_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Const.hpp"
namespace ml {
/*
 * Add:
 * Adds the underlying values
 */
template <typename Pipe = Identity> struct Add {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<ml::Int<(T1::value + T2::value)>>;
};

} // namespace ml
#endif
