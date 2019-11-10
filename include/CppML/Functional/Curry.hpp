//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_CURRY_HPP
#define CPPML_CURRY_HPP
#include "F.hpp"
#include "Partial.hpp"
namespace ml {
/*
 * # Curry:
 * Curries a metafunction.
 * **NOTE** that it can curry a variadic amount.
 */
template <typename F> struct Curry : ml::Partial<ml::F<ml::Partial>, F> {};
} // namespace ml
#endif
