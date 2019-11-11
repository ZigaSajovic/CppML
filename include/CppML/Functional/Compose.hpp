/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_COMPOSE_HPP
#define CPPML_COMPOSE_HPP
#include "../ControlFlow/IfElse.hpp"
namespace ml {
/*
 * Implementation of Compose. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct Compose {
  template <int i, typename Result, typename... Ts>
  using f = typename Result::template f<typename Compose<
      (sizeof...(Ts) >= 0) && (i > 2)>::template f<i - 1, Ts...>>;
};
template <> struct Compose<false> {
  template <int i, typename Result, typename... Us>
  using f = typename ml::IfElse<(
      sizeof...(Us) < 100000)>::template f<Result, void>::template f<Us...>;
};
}; // namespace Implementations
/*
 * # Compose:
 * Composes one or more metafunctions.
 */
template <typename T, typename... Ts> struct Compose {
  template <typename... Us>
  using f = typename Implementations::Compose<(
      sizeof...(Ts) > 0)>::template f<sizeof...(Ts) + 1, T, Ts..., Us...>;
};

} // namespace ml
#endif
