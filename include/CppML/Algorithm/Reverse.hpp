/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
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
