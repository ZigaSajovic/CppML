//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PRODUCT_HPP
#define CPPML_PRODUCT_HPP
#include "../Algorithm/Pivot.hpp"
#include "DelayedEval.hpp"
#include "F.hpp"
#include "Invoke.hpp"

namespace ml {
namespace Implementations {
template <typename Pipe, typename... Fs> struct Product {
  template <typename... Ts>
  using f = ml::DelayedEval<Pipe, sizeof...(Ts), ml::Invoke<Fs, Ts...>...>;
};
} // namespace Implementations
/*
 * Product:
 * Creates a product of metafunctions. Meaning:
 * ```
 * F_i: Ts... -> U
 * Product : Ts ... -> U... -> (Pipe) ; |U...| = |F_i...|
 * ```
 * **Note** that the last
 * metafunction will be treated as **Pipe**.
 */
template <typename... Fs>
struct Product
    : ml::Invoke<ml::Pivot<sizeof...(Fs) - 1, ml::F<Implementations::Product>>,
                 Fs...> {};
} // namespace ml
#endif
