/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_PRODUCT_MAP_HPP
#define CPPML_PRODUCT_MAP_HPP
#include "../Algorithm/Pivot.hpp"
#include "./DelayedEval.hpp"
#include "./F.hpp"
#include "./Invoke.hpp"

namespace ml {
namespace Implementations {
template <typename Pipe, typename... Fs> struct ProductMap {
  template <typename... Ts>
  using f = ml::f<ml::DelayedEval<
      Pipe, sizeof...(Ts)>,
      typename ml::Implementations::IfElse<(sizeof...(Ts) + sizeof...(Fs) <
                           10000)>::template f<Fs, void>::template f<Ts>...>;
};
} // namespace Implementations
/*
 * ProductMap:
 * Creates a map product of metafunctions. Meaning:
 * ```
 * F_i: T -> U
 * ProductMap : Ts ... -> U... -> (Pipe); |U...| = |F_i...|
 * ```
 * **Note** that the last
 * metafunction will be treated as **Pipe**.
 */
template <typename... Fs>
struct ProductMap
    : ml::Invoke<
          ml::Pivot<sizeof...(Fs) - 1, ml::F<Implementations::ProductMap>>,
          Fs...> {};
} // namespace ml
#endif
