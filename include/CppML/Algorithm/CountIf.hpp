/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_COUNT_IF_HPP
#define CPPML_COUNT_IF_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
/*
 * Implementation of CountIf. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct CountIf {
  template <int i, typename Predicate, typename T, typename... Ts>
  using f = typename Implementations::CountIf<static_cast<bool>(sizeof...(
      Ts))>::template f<i + ml::Invoke<Predicate, T>::value, Predicate, Ts...>;
};
template <> struct CountIf<false> {
  template <int i, typename Predicate, typename... Ts> using f = ml::Int<i>;
};
} // namespace Implementations

/*
 * # CountIf:
 * Counts the number of elements satisfying a predicate.
 */
template <typename Predicate, typename Pipe = ml::Identity> struct CountIf {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, typename Implementations::CountIf<static_cast<bool>(
                           sizeof...(Ts))>::template f<0, Predicate, Ts...>>;
};

} // namespace ml
#endif
