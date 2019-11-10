//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_TO_LIST_HPP
#define CPPML_TO_LIST_HPP
#include "../Vocabulary/List.hpp"
#include "F.hpp"
namespace ml {
/*
 * ToList:
 * Wraps the pack in a list
 */
using ToList = ml::F<ListT>;
} // namespace ml
#endif
