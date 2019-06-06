//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_LIST_H
#define CPPML_LIST_H
namespace ml {
/*
 * ListT:
 * Represents a list of types
 */
template <typename... Ts> struct ListT {};

/*
 * ListA:
 * Represents a list of auto (values)
 */
template <auto... As> struct ListA {};
};
#endif
