//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ALL_HPP
#define CPPML_ALL_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Const.hpp"
#include "../Vocabulary/IfElse.hpp"
namespace ml {
/*
 * All:
 * Checks if all values satisfy the predicate
 */
#ifdef __cpp_fold_expressions
template <typename Predicate, typename Pipe = Identity> struct All {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value && ...)>>;
};
#else
/*
 * Implementation of All for C++14 and lower.
 * It only ever instantiates 4 types.
 */
namespace Implementations {
template <bool Continue> struct AllImpl {
  template <typename Predicate, typename T>
  using f = ml::Bool<Predicate::template f<T>::value>;
};
template <> struct AllImpl<true> {
  template <typename Predicate, typename T, typename... Ts>
  using f = typename ml::IfElse<!Predicate::template f<T>::value>::template f<
      ml::Bool<false>,
      typename AllImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>>;
};
template <bool Zero> struct AllBase {
  template <typename Predicate, typename... Ts>
  using f = typename AllImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>;
};
template <> struct AllBase<true> {
  template <typename Predicate, typename... Ts> using f = ml::Bool<true>;
};
}; // namespace Implementations

template <typename Predicate, typename Pipe = ml::Identity> struct All {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, typename Implementations::AllBase<!static_cast<bool>(
                           sizeof...(Ts))>::template f<Predicate, Ts...>>;
};
#endif
} // namespace ml
#endif
