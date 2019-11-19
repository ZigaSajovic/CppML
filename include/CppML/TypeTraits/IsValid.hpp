/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_IS_VALID_HPP
#define CPPML_IS_VALID_HPP
#include "../Functional/DelayedEval.hpp"
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include "./VoidT.hpp"
namespace ml {
namespace Implementations {
template <typename, template <typename...> class T, class... Ts>
struct IsValidT_impl : ml::Bool<false> {};

template <template <typename...> class T, typename... Ts>
struct IsValidT_impl<ml::VoidT<T<Ts...>>, T, Ts...> : ml::Bool<true> {};

template <typename, class T, class... Ts>
struct IsValid_impl : ml::Bool<false> {};

template <class T, typename... Ts>
struct IsValid_impl<ml::VoidT<ml::f<ml::DelayedEval<T, sizeof...(Ts)>, Ts...>>,
                    T, Ts...> : ml::Bool<true> {};
}; // namespace Implementations

/*
 * IsValidT:
 * Checks is a template T is instantiable with Ts.
 * Can be used like:
 * template <typename T, typename U>
 * using Check = decltype(std::declval<T>().foo(std::declval<U>()));
 * constexpr bool test = IsValidT<Check, SomeType, int>::value;
 */
template <typename Pipe = ml::Identity> struct IsValidT {
  template <template <typename...> class T, class... Ts>
  using f = typename Pipe::template f<
      ml::Bool<Implementations::IsValidT_impl<void, T, Ts...>::value>>;
};

/*
 * IsValid:
 * Checks if F can be invoked on Ts...
 */
template <typename Pipe = ml::Identity> struct IsValid {
  template <class F, class... Ts>
  using f = typename Pipe::template f<
      ml::Bool<Implementations::IsValid_impl<void, F, Ts...>::value>>;
};
} // namespace ml
#endif
