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
 * IsSame:
 * Checks if two types are equivalent
 */
template <typename Pipe = Identity> struct IsSame {
  template <typename T, typename U>
  using f = typename Pipe::template f<Bool<std::is_same<T, U>::value>>;
};
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
  using f = typename IfElse<!std::is_reference_v<From>>::template f<
      std::remove_reference_t<To>,
      typename IfElse<std::is_rvalue_reference_v<From>>::template f<
          std::remove_reference_t<To> &&, To &>>;
};
namespace HasCRTPAsBaseDetail {
template <typename Derived, template <class...> class Template, class... Ts>
void test(Template<Derived, Ts...> *);

template <typename T, template <class...> class Template, typename = void>
struct InheritsFromTemplateBase : Bool<false> {};

template <typename Derived, template <class...> class Template>
struct InheritsFromTemplateBase<
    Derived, Template,
    std::void_t<decltype(test<Derived, Template>(std::declval<Derived *>()))>>
    : Bool<true> {};

}; // namespace HasCRTPAsBaseDetail
/*
 * HasCRTPAsBase:
 * Checks if a class inherits from a template.
 */
struct HasCRTPAsBase {
  template <typename Derived, template <class...> class Template>
  using f = HasCRTPAsBaseDetail::InheritsFromTemplateBase<Derived, Template>;
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
