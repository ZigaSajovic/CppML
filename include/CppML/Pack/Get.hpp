/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_GET_HPP
#define CPPML_GET_HPP
#include "../Algorithm/Pivot.hpp"
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Identity.hpp"
#include "./Drop.hpp"
#include "./Front.hpp"
namespace ml {
/*
 * Get:
 * Retrives the N-th element in a pack.
 */
template <int N, typename Pipe = ml::Identity> struct Get {
  template <typename... Ts>
  using f =
      ml::DelayedEval<ml::Pivot<N, ml::Front<Pipe>>, sizeof...(Ts), Ts...>;
};
} // namespace ml
#endif
