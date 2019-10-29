//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_APPEND_HPP
#define CPPML_APPEND_HPP

namespace ml {
/*
 * Append:
 * Appends elements to a list-like structure
 */
template <typename> struct Append;
template <template <class...> class List, typename... Ts>
struct Append<List<Ts...>> {
  template <typename... Us> using f = List<Ts..., Us...>;
};
} // namespace ml
#endif
