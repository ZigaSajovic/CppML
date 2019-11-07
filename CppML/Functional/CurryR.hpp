//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_CURRY_R_HPP
#define CPPML_CURRY_R_HPP
#include "F.hpp"
#include "Partial.hpp"
#include "PartialR.hpp"
namespace ml {
/*
 * # CurryR:
 * Curries a metafunction from the right.
 * **NOTE** that it can curry a variadic amount.
 */
template <typename F> struct CurryR : ml::Partial<ml::F<ml::PartialR>, F> {};
} // namespace ml
#endif
