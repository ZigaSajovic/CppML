//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_TYPE_TRAITS_H
#define CPPML_TYPE_TRAITS_H
#include "Const.h"
#include "ControlFlow.h"
#include "Identity.h"
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
namespace InheritsFromTemplateDetail {
template <typename T, template <class...> class Template>
struct InheritsFromTemplateImpl {
  template <typename... Ts> static void test(Template<Ts...> *);
};

template <typename T, template <class...> class Template, typename = void>
struct InheritsFromTemplateBase : Bool<false> {};

template <typename T, template <class...> class Template>
struct InheritsFromTemplateBase<
    T, Template,
    std::void_t<decltype(InheritsFromTemplateImpl<T, Template>::test(
        std::declval<T *>()))>> : Bool<true> {};
}; // namespace InheritsFromTemplateDetail
/*
 * InheritsFromTemplate:
 * Checks if a class inherits from a template.
 */
struct InheritsFromTemplate {
  template <typename T, template <class...> class Template>
  using f = InheritsFromTemplateDetail::InheritsFromTemplateBase<T, Template>;
};

namespace TraitsDetail {
template <class T, class = void> struct HasArrow_impl : ml::Bool<false> {};
template <class T>
struct HasArrow_impl<T, std::void_t<decltype(std::declval<T>().operator->())>>
    : ml::Bool<true> {};
template <class T, class = void> struct HasBracket_impl : ml::Bool<false> {};
template <class T>
struct HasBracket_impl<T, std::void_t<decltype(std::declval<T>().operator[](3))>>
    : ml::Bool<true> {};
}; // namespace TraitsDetail

/*
 * HasArrow:
 * Checks if T defines the arrow operator.
 */
struct HasArrow {
  template <typename T> using f = TraitsDetail::HasArrow_impl<T, void>;
};
/*
 * HasBracket:
 * Checks if T defines the arrow operator.
 */
struct HasBracket {
  template <typename T> using f = TraitsDetail::HasBracket_impl<T, void>;
};
}; // namespace ml
#endif
