/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_HEAD_HPP
#define CPPML_HEAD_HPP
#include "../Algorithm/Pivot.hpp"
#include "../Functional/ToList.hpp"
#include "../Pack/Drop.hpp"
namespace ml {
/*
 * # Head:
 * Returns the first N elements
 */
template <int N, typename Pipe = ml::ToList> struct Head {
  template <typename... Ts>
  using f =
      typename ml::Pivot<N,
                         ml::Drop<sizeof...(Ts) - N, Pipe>>::template f<Ts...>;
};
} // namespace ml
#endif
