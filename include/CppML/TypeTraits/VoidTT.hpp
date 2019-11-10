//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_VOID_TT_HPP
#define CPPML_VOID_TT_HPP

namespace ml {
/*
 * void_tt:
 * void_t for template templates
 */
template <template <class...> class...> using void_tt = void;
}
#endif
