/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_MAX_ELEMENT_HPP
#define CPPML_MAX_ELEMENT_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/IfElse.hpp"

namespace ml {
namespace Implementations {
template <bool Done> struct MaxElement {
  template <typename Compare, typename T0, typename T1, typename... Ts>
  using f = typename Implementations::IfElse<(
      sizeof...(Ts) <
      10000)>::template f<MaxElement<static_cast<bool>(sizeof...(Ts))>, void>::
      template f<Compare,
                 typename Implementations::IfElse<
                     Compare::template f<T0, T1>::value>::template f<T0, T1>,
                 Ts...>;
};
template <> struct MaxElement<false> {
  template <typename Compare, typename T> using f = T;
};
}; // namespace Implementations

/*
 * MaxElement:
 * Max element in a pack, given a comparison operator
 */
template <typename Compare, typename Pipe = ml::Identity> struct MaxElement {
  template <typename... Ts>
  using f = typename Pipe::template f<typename Implementations::MaxElement<(
      sizeof...(Ts) > 1)>::template f<Compare, Ts...>>;
};
} // namespace ml
#endif
