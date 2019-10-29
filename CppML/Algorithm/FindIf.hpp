//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FIND_IF_HPP
#define CPPML_FIND_IF_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Const.hpp"
#include "../Vocabulary/IfElse.hpp"

namespace ml {
/*
 * Implementation of FindIf. Only ever instantiates two types.
 */
namespace Implementations {
template <bool Continue> struct FindIf {
  template <int i, typename Predicate, typename T, typename... Ts>
  using f = typename ml::IfElse<Predicate::template f<T>::value>::template f<
      ml::Int<i>, typename FindIf<static_cast<bool>(
                      sizeof...(Ts) > 1)>::template f<i + 1, Predicate, Ts...>>;
};

template <> struct FindIf<false> {
  template <int i, typename Predicate, typename T>
  using f = typename ml::IfElse<Predicate::template f<T>::value>::template f<
      ml::Int<i>, ml::Int<i + 1>>;
};
}; // namespace Implementations

/*
 * # FindIf:
 * Returns index of the element matching the predicate
 */
template <typename Predicate, typename Pipe = ml::Identity> struct FindIf {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe,
                 typename Implementations::FindIf<static_cast<bool>(
                     sizeof...(Ts) > 1)>::template f<0, Predicate, Ts...>>;
};
} // namespace ml
#endif
