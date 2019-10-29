//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ANY_HPP
#define CPPML_ANY_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Const.hpp"
#include "../Vocabulary/IfElse.hpp"
namespace ml {
/*
 * Any:
 * Checks if any value satisfies the predicate
 */
#ifdef __cpp_fold_expressions
template <typename Predicate, typename Pipe = Identity> struct Any {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value || ...)>>;
};
#else
/*
 * Implementation of Any for c++14 and ower.
 * It only ever instantiates 4 types.
 */
namespace Implementations {
template <bool Continue> struct AnyImpl {
  template <typename Predicate, typename T>
  using f = ml::Bool<Predicate::template f<T>::value>;
};
template <> struct AnyImpl<true> {
  template <typename Predicate, typename T, typename... Ts>
  using f = typename ml::IfElse<Predicate::template f<T>::value>::template f<
      ml::Bool<true>,
      typename AnyImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>>;
};
template <bool Zero> struct AnyBase {
  template <typename Predicate, typename... Ts>
  using f = typename AnyImpl<(sizeof...(Ts) > 1)>::template f<Predicate, Ts...>;
};
template <> struct AnyBase<true> {
  template <typename Predicate, typename... Ts> using f = ml::Bool<false>;
};
}; // namespace Implementations

template <typename Predicate, typename Pipe = ml::Identity> struct Any {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, typename Implementations::AnyBase<
                           sizeof...(Ts) == 0>::template f<Predicate, Ts...>>;
};
#endif

} // namespace ml
#endif
