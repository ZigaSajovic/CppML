//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PREPEND_HPP
#define CPPML_PREPEND_HPP

namespace ml {
/*
 * Prepend:
 * Prepends elements to a list-like structure
 */
template <typename> struct Prepend;
template <template <class...> class List, typename... Ts>
struct Prepend<List<Ts...>> {
  template <typename... Us> using f = List<Us..., Ts...>;
};
} // namespace ml
#endif
