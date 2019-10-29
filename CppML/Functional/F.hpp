//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_F_HPP
#define CPPML_F_HPP

namespace ml {
/*
 * F:
 * Creates a metafunction out of a template
 */
template <template <class...> class F_> struct F {
  template <typename... Args> using f = F_<Args...>;
};
} // namespace ml
#endif
