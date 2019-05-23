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
template <typename T, template <class...> class Template>
struct InheritsFromTemplate
    : InheritsFromTemplateDetail::InheritsFromTemplateBase<T, Template> {};

namespace BaseConstructableDetail {
template <typename Base> struct T : Base {
  template <typename... Args>
  T(Args &&... args) : Base{static_cast<Args &&>(args)...} {};
};
}; // namespace BaseConstructableDetail

/*
 * BaseConstructable:
 * Checks if a class with a proctected destructor (that can only be
 * a base class) is constructable from arguments.
 */
template <typename T> struct BaseConstructable {
  template <typename... Args>
  using f =
      std::is_constructible<typename ml::IfElse<std::is_class_v<T>>::template f<
                                BaseConstructableDetail::T<T>, T>,
                            Args...>;
};
}; // namespace ml
#endif
