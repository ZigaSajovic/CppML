//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_IS_VALID_HPP
#define CPPML_IS_VALID_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
#include <type_traits>
namespace ml {
namespace Implementations {
template <typename, template <typename...> class T, class... Ts>
struct IsValidT_impl : ml::Bool<false> {};

template <template <typename...> class T, typename... Ts>
struct IsValidT_impl<std::void_t<T<Ts...>>, T, Ts...> : ml::Bool<true> {};

template <typename, class T, class... Ts>
struct IsValid_impl : ml::Bool<false> {};

template <class T, typename... Ts>
struct IsValid_impl<std::void_t<typename T::template f<Ts...>>, T, Ts...>
    : ml::Bool<true> {};

template <typename T> struct R { using f = T; };

template <typename, class U, class T, class... Ts>
struct IfValidOr_impl : R<U> {};

template <class U, class T, typename... Ts>
struct IfValidOr_impl<std::void_t<typename T::template f<Ts...>>, U, T, Ts...>
    : R<typename T::template f<Ts...>> {};
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
  using f =
      typename Pipe::template f<Implementations::IsValidT_impl<void, T, Ts...>>;
};

/*
 * IsValid:
 * See IsValidT. This is equivalent, but T is a metafunction.
 */
template <typename Pipe = ml::Identity> struct IsValid {
  template <class T, class... Ts>
  using f =
      typename Pipe::template f<Implementations::IsValid_impl<void, T, Ts...>>;
};
/*
 * IfValidOr:
 * If the metafunction T is valid, evaluate to its result,
 * else evaluate to U.
 */
template <typename Pipe = ml::Identity> struct IfValidOr {
  template <class U, class T, class... Ts>
  using f = typename Pipe::template f<
      typename Implementations::IfValidOr_impl<void, U, T, Ts...>::f>;
};

} // namespace ml
#endif
