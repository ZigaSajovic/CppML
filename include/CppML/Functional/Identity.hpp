//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IDENTITY_HPP
#define CPPML_IDENTITY_HPP
namespace ml {
/*
 * Identity:
 * Returns self
 */
struct Identity {
  template <typename T> using f = T;
};
}; // namespace ml
#endif
