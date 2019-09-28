//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_TYPE_TRAITS_HPP
#define CPPML_TYPE_TRAITS_HPP
#include "Const.hpp"
#include "ControlFlow.hpp"
#include "Identity.hpp"
#include <type_traits>

namespace ml {
/*
 * void_tt:
 * void_t for template templates
 */
template <template <class...> class...> using void_tt = void;
/*
 * IsClass:
 * Checks if a type is a class
 */
template <typename Pipe = Identity> struct IsClass {
  template <typename T>
  using f = typename Pipe::template f<Bool<std::is_class<T>::value>>;
};
/*
 * IsConstrucitble:
 * Checks if a type is constructable from given arguments
 */
template <typename Pipe = Identity> struct IsConstrucitble {
  template <typename T, typename... Args>
  using f =
      typename Pipe::template f<Bool<std::is_constructible<T, Args...>::value>>;
};
/*
 * IsConvertible:
 * Checks if one type is convertible to the other
 */
template <typename Pipe = Identity> struct IsConvertible {
  template <typename T, typename U>
  using f = typename Pipe::template f<Bool<std::is_convertible<T, U>::value>>;
};
/*
 * AligmentOf:
 * Returns an Int type of aligment of T
 */
template <typename Pipe = Identity> struct AligmentOf {
  template <typename T> using f = typename Pipe::template f<Int<alignof(T)>>;
};
/*
 * CopyRefness:
 * Returns type To, with the same refness as From.
 */
struct CopyRefness {
  template <typename From, typename To>
  using f = typename IfElse<!std::is_reference<From>::value>::template f<
      std::remove_reference_t<To>,
      typename IfElse<std::is_rvalue_reference<From>::value>::template f<
          std::remove_reference_t<To> &&, To &>>;
};
namespace TypeTraitsImplementations {
template <typename T> struct IsSameHelper {
  static ml::Bool<true> test(const volatile IsSameHelper<T> *);
  static ml::Bool<false> test(const volatile void *);
  template <typename U>
  using f = decltype(IsSameHelper<T>::test(std::declval<IsSameHelper<U> *>()));
};
} // namespace TypeTraitsImplementations
/*
 * IsSame:
 * Check if two types are equal. Note that this creates linear number
 * of types, not quadratic, like std::is_same.
 */
struct IsSame {
  template <typename T1, typename T2>
  using f =
      typename TypeTraitsImplementations::IsSameHelper<T1>::template f<T2>;
};

namespace IsValidDetail {
template <typename, template <typename...> class T, class... Ts>
struct IsValidT_impl : ml::Bool<false> {};

template <template <typename...> class T, typename... Ts>
struct IsValidT_impl<std::void_t<T<Ts...>>, T, Ts...> : ml::Bool<true> {};

template <typename, class T, class... Ts>
struct IsValid_impl : ml::Bool<false> {};

template <class T, typename... Ts>
struct IsValid_impl<std::void_t<typename T::template f<Ts...>>, T, Ts...>
    : ml::Bool<true> {};

template <typename, class U, class T, class... Ts> struct IfValidOr_impl : U {};

template <class U, class T, typename... Ts>
struct IfValidOr_impl<std::void_t<typename T::template f<Ts...>>, U, T, Ts...>
    : T::template f<Ts...> {};
}; // namespace IsValidDetail

/*
 * IsValidT:
 * Checks is a template T is instantiable with Ts.
 * Can be used like:
 * template <typename T, typename U>
 * using Check = decltype(std::declval<T>().foo(std::declval<U>()));
 * constexpr bool test = IsValidT<Check, SomeType, int>::value;
 */
struct IsValidT {
  template <template <typename...> class T, class... Ts>
  using f = IsValidDetail::IsValidT_impl<void, T, Ts...>;
};

/*
 * IsValid:
 * See IsValidT. This is equivalent, but T is a metafunction.
 */
struct IsValid {
  template <class T, class... Ts>
  using f = IsValidDetail::IsValid_impl<void, T, Ts...>;
};
/*
 * IfValidOr:
 * If the metafunction T is valid, evaluate to its result,
 * else evaluate to U.
 */
struct IfValidOr {
  template <class U, class T, class... Ts>
  using f = IsValidDetail::IfValidOr_impl<void, U, T, Ts...>;
};

namespace Types {
template <typename T, typename I = int>
using BracketType = decltype(std::declval<T>()[std::declval<I>()]);

template <typename T>
using ArrowOperatorType = decltype(std::declval<T>().operator->());
}; // namespace Types
/*
 * HasBracket:
 * Checks if T defines the arrow operator.
 */
struct HasBracket {
  template <typename T, typename I = int>
  using f = IsValidT::template f<Types::BracketType, T, I>;
};
/*
 * HasArrow:
 * Checks if T defines the arrow operator.
 */
struct HasArrow {
  template <typename T>
  using f = IsValidT::template f<Types::ArrowOperatorType, T>;
};
}; // namespace ml
#endif
