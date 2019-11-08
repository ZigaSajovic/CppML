//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_REVERSE_HPP
#define CPPML_REVERSE_HPP
#include "../Functional/Map.hpp"
#include "../Pack/PackExtractor.hpp"
#include "../Pack/Range.hpp"
namespace ml {
/*
 * # Reverse:
 * Reverses a parameter pack
 */
template <typename Pipe = ml::ToList> struct Reverse {
  template <typename... Ts>
  using f = typename ml::Range<ml::Map<ml::PackExtractor<Ts...>, Pipe>>::
      template f<sizeof...(Ts) - 1, -1, -1>;
};
} // namespace ml
#endif
