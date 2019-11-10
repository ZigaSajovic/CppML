//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_CONSTANT_HPP
#define CPPML_CONSTANT_HPP

namespace ml {
/*
 * # Constant:
 * Constant function
 */
template <typename T> struct Constant { template <typename...> using f = T; };
} // namespace ml
#endif
