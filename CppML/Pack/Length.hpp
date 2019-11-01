//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_LENGTH_HPP
#define CPPML_LENGTH_HPP
#include "../Vocabulary/Const.hpp"
namespace ml {
/*
 * Length:
 * Length of a List-like
 */
template <typename List> struct Length;
template <template <class...> class List, typename... Args>
struct Length<List<Args...>> : ml::Int<sizeof...(Args)> {};
} // namespace ml
#endif
