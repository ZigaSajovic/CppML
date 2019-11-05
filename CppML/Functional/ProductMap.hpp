//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PRODUCT_MAP_HPP
#define CPPML_PRODUCT_MAP_HPP
#include "../Algorithm/Pivot.hpp"
#include "DelayedEval.hpp"
#include "F.hpp"
#include "Invoke.hpp"

namespace ml {
namespace Implementations {
template <typename Pipe, typename... Fs> struct ProductMap {
  template <typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), ml::Invoke<Fs, Ts...>...>;
};
} // namespace Implementations
/*
 * ProductMap:
 * Creates a map product of metafunctions. Meaning:
 * ```
 * F_i: Ts... -> U
 * ProductMap : Ts ... -> U... ; |U...| = |F_i...|
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
